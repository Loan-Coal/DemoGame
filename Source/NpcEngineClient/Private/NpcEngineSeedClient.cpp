#include "NpcEngineSeedClient.h"
#include "NpcEngineClient.h"
#include "NpcEngineConfig.h"
#include "NpcEngineJsonUtils.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

FString UNpcEngineSeedClient::BuildUrl(const FString& Path) const
{
    static FNpcEngineConfig Config = FNpcEngineConfig::Load();
    return Config.GetBaseUrl() + Path;
}

void UNpcEngineSeedClient::PostJson(
    const FString& Url,
    const FString& Body,
    TFunction<void(bool, const FString&)> OnResult)
{
    static FNpcEngineConfig Config = FNpcEngineConfig::Load();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();
    Request->SetVerb(TEXT("POST"));
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
    Request->SetHeader(TEXT("Accept"),        TEXT("application/json"));
    Request->SetHeader(TEXT("Authorization"), Config.MakeBearerHeader());
    Request->SetTimeout(10.f);
    Request->SetContentAsString(Body);

    Request->OnProcessRequestComplete().BindLambda(
        [OnResult](FHttpRequestPtr /*Req*/, FHttpResponsePtr Response, bool bConnected)
        {
            if (!bConnected || !Response.IsValid())
            {
                OnResult(false, TEXT(""));
                return;
            }
            const bool bOk = Response->GetResponseCode() >= 200 &&
                             Response->GetResponseCode() < 300;
            OnResult(bOk, Response->GetContentAsString());
        });

    Request->ProcessRequest();
}

// ── Seed replay ──────────────────────────────────────────────────────────────

void UNpcEngineSeedClient::ReplaySlice1Seed(
    TFunction<void()> OnComplete,
    TFunction<void(const FString&)> OnError)
{
    const FString SeedPath = FPaths::ProjectDir() / TEXT("Seed/slice1_tavern.json");
    FString SeedJson;
    if (!FFileHelper::LoadFileToString(SeedJson, *SeedPath))
    {
        const FString Msg = FString::Printf(
            TEXT("Seed file not found at %s"), *SeedPath);
        UE_LOG(LogNpcEngine, Error, TEXT("ReplaySlice1Seed: %s"), *Msg);
        if (OnError) OnError(Msg);
        return;
    }

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(SeedJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        const FString Msg = TEXT("Failed to parse Seed/slice1_tavern.json.");
        UE_LOG(LogNpcEngine, Error, TEXT("ReplaySlice1Seed: %s"), *Msg);
        if (OnError) OnError(Msg);
        return;
    }

    TArray<FSeedOp> Ops;
    BuildOperationQueue(Root, Ops);

    UE_LOG(LogNpcEngine, Log, TEXT("ReplaySlice1Seed: %d operations queued."), Ops.Num());
    ProcessNextOp(MoveTemp(Ops), 0, OnComplete, OnError);
}

void UNpcEngineSeedClient::BuildOperationQueue(
    const TSharedPtr<FJsonObject>& SeedRoot,
    TArray<FSeedOp>& OutOps)
{
    // Respect "seed_order" from the JSON file: locations → factions → characters → edges.
    // For each item, serialise to the REST body and push to the operation queue.

    auto SerialiseProps = [](const TSharedPtr<FJsonObject>& PropsObj) -> FString
    {
        FString Str;
        TSharedRef<TJsonWriter<>> W = TJsonWriterFactory<>::Create(&Str);
        FJsonSerializer::Serialize(PropsObj.ToSharedRef(), W);
        return Str;
    };

    // Nodes (locations, factions, characters).
    for (const FString& Section : { FString(TEXT("locations")), FString(TEXT("factions")), FString(TEXT("characters")) })
    {
        const TArray<TSharedPtr<FJsonValue>>* Items = nullptr;
        if (!SeedRoot->TryGetArrayField(Section, Items)) continue;

        for (const TSharedPtr<FJsonValue>& Item : *Items)
        {
            const TSharedPtr<FJsonObject>* ItemObj = nullptr;
            if (!Item->TryGetObject(ItemObj) || !ItemObj) continue;

            FString NodeType;
            (*ItemObj)->TryGetStringField(TEXT("node_type"), NodeType);

            const TSharedPtr<FJsonObject>* PropsField = nullptr;
            if (!(*ItemObj)->TryGetObjectField(TEXT("properties"), PropsField) || !PropsField) continue;

            const FString PropsJson = SerialiseProps(*PropsField);
            FSeedOp Op;
            Op.Endpoint = FString::Printf(TEXT("/v1/graph/nodes/%s"), *NodeType);
            Op.Body     = FNpcEngineJsonUtils::SerialiseNodeWrite(PropsJson);
            OutOps.Add(MoveTemp(Op));
        }
    }

    // Edges.
    const TArray<TSharedPtr<FJsonValue>>* Edges = nullptr;
    if (SeedRoot->TryGetArrayField(TEXT("edges"), Edges))
    {
        for (const TSharedPtr<FJsonValue>& Edge : *Edges)
        {
            const TSharedPtr<FJsonObject>* EdgeObj = nullptr;
            if (!Edge->TryGetObject(EdgeObj) || !EdgeObj) continue;

            FString EdgeType, SrcId, DstId;
            (*EdgeObj)->TryGetStringField(TEXT("edge_type"), EdgeType);
            (*EdgeObj)->TryGetStringField(TEXT("src_id"),    SrcId);
            (*EdgeObj)->TryGetStringField(TEXT("dst_id"),    DstId);

            FString PropsJson = TEXT("{}");
            const TSharedPtr<FJsonObject>* PropsField = nullptr;
            if ((*EdgeObj)->TryGetObjectField(TEXT("properties"), PropsField) && PropsField)
            {
                PropsJson = SerialiseProps(*PropsField);
            }

            FSeedOp Op;
            Op.Endpoint = FString::Printf(TEXT("/v1/graph/edges/%s"), *EdgeType);
            Op.Body     = FNpcEngineJsonUtils::SerialiseEdgeWrite(SrcId, DstId, PropsJson);
            OutOps.Add(MoveTemp(Op));
        }
    }
}

void UNpcEngineSeedClient::ProcessNextOp(
    TArray<FSeedOp> Ops,
    int32 Index,
    TFunction<void()> OnComplete,
    TFunction<void(const FString&)> OnError)
{
    if (Index >= Ops.Num())
    {
        UE_LOG(LogNpcEngine, Log, TEXT("ReplaySlice1Seed: all %d operations complete."), Ops.Num());
        if (OnComplete) OnComplete();
        return;
    }

    const FSeedOp& Op = Ops[Index];
    const FString Url = BuildUrl(Op.Endpoint);

    UE_LOG(LogNpcEngine, Verbose,
        TEXT("ReplaySlice1Seed [%d/%d]: POST %s"), Index + 1, Ops.Num(), *Url);

    // Capture Ops by value so the TArray lives until the last callback fires.
    PostJson(Url, Op.Body,
        [this, Ops = Ops, Index, OnComplete, OnError](bool bOk, const FString& /*Body*/) mutable
        {
            if (!bOk)
            {
                const FString Msg = FString::Printf(
                    TEXT("Seed operation %d failed (POST %s)."), Index, *Ops[Index].Endpoint);
                UE_LOG(LogNpcEngine, Error, TEXT("ReplaySlice1Seed: %s"), *Msg);
                // Continue despite errors (engine MERGE is idempotent; node may already exist).
                // Change to `if (OnError) { OnError(Msg); return; }` to stop on first error.
            }
            ProcessNextOp(MoveTemp(Ops), Index + 1, OnComplete, OnError);
        });
}

// ── Individual upsert helpers ────────────────────────────────────────────────

void UNpcEngineSeedClient::UpsertNode(
    const FString& NodeType,
    const FString& PropertiesJson,
    TFunction<void(bool)> OnResult)
{
    const FString Url  = BuildUrl(FString::Printf(TEXT("/v1/graph/nodes/%s"), *NodeType));
    const FString Body = FNpcEngineJsonUtils::SerialiseNodeWrite(PropertiesJson);
    PostJson(Url, Body, [OnResult](bool bOk, const FString& /*Body*/) { if (OnResult) OnResult(bOk); });
}

void UNpcEngineSeedClient::UpsertEdge(
    const FString& EdgeType,
    const FString& SrcId,
    const FString& DstId,
    const FString& PropertiesJson,
    TFunction<void(bool)> OnResult)
{
    const FString Url  = BuildUrl(FString::Printf(TEXT("/v1/graph/edges/%s"), *EdgeType));
    const FString Body = FNpcEngineJsonUtils::SerialiseEdgeWrite(SrcId, DstId, PropertiesJson);
    PostJson(Url, Body, [OnResult](bool bOk, const FString& /*Body*/) { if (OnResult) OnResult(bOk); });
}
