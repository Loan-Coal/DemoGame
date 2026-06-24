// File: NpcWorldSeeder.cpp
// Module: NpcEngineClient
// Purpose: World seeder — loads DemoWorld_v1.json and upserts nodes/edges with idempotency checks.
// Net I/O: yes

#include "NpcWorldSeeder.h"
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
#include "HAL/IConsoleManager.h"

// Sections processed before edges (dependency order: no edges reference these until after
// all nodes exist).
static const TArray<FString> PRE_EDGE_SECTIONS  = {
    TEXT("locations"), TEXT("factions"), TEXT("characters"), TEXT("events")
};
// Sections processed after edges (quest nodes have no inbound edges in Phase-3 seed).
static const TArray<FString> POST_EDGE_SECTIONS = { TEXT("quests") };

static constexpr float SEED_HTTP_TIMEOUT_SECS = 10.f;

// ── Public API ────────────────────────────────────────────────────────────────

void UNpcWorldSeeder::SeedWorld(TFunction<void()> OnComplete, TFunction<void(const FString&)> OnError)
{
    const FString SeedPath = FPaths::ProjectDir() / TEXT("Seed/DemoWorld_v1.json");
    FString Json;
    if (!FFileHelper::LoadFileToString(Json, *SeedPath))
    {
        const FString Err = FString::Printf(TEXT("SeedWorld: file not found at %s"), *SeedPath);
        UE_LOG(LogNpcEngine, Error, TEXT("%s"), *Err);
        if (OnError) OnError(Err);
        return;
    }
    SeedFromJsonString(Json, MoveTemp(OnComplete), MoveTemp(OnError));
}

void UNpcWorldSeeder::SeedFromJsonString(
    const FString& JsonContent,
    TFunction<void()> OnComplete,
    TFunction<void(const FString&)> OnError)
{
    EnsureHttpExec();

    // GC-pin this UObject for the async duration.  CheckNodeExists/PostUpsert* capture
    // 'this' in lambdas; without pinning a GC cycle between two async steps would dangle it.
    AddToRoot();
    TFunction<void()> PinnedComplete = [this, OnComplete = MoveTemp(OnComplete)]()
    {
        RemoveFromRoot();
        if (OnComplete) OnComplete();
    };
    TFunction<void(const FString&)> PinnedError = [this, OnError = MoveTemp(OnError)](const FString& Err)
    {
        RemoveFromRoot();
        if (OnError) OnError(Err);
    };

    // If config was invalid EnsureHttpExec leaves HttpExec null; fail fast here.
    if (!HttpExec)
    {
        PinnedError(TEXT("SeedWorld: NpcEngineConfig invalid — missing URL or API key"));
        return;
    }

    TArray<FNodeTask> PreEdge, PostEdge;
    TArray<FEdgeTask> Edges;
    FString ParseErr;
    if (!BuildTasksFromJson(JsonContent, PreEdge, Edges, PostEdge, ParseErr))
    {
        UE_LOG(LogNpcEngine, Error, TEXT("SeedWorld: JSON parse error — %s"), *ParseErr);
        PinnedError(ParseErr);
        return;
    }

    UE_LOG(LogNpcEngine, Log,
        TEXT("SeedWorld: %d pre-edge nodes, %d edges, %d post-edge nodes."),
        PreEdge.Num(), Edges.Num(), PostEdge.Num());

    ProcessNodes(
        MoveTemp(PreEdge), 0,
        MoveTemp(Edges), MoveTemp(PostEdge),
        MoveTemp(PinnedComplete), MoveTemp(PinnedError));
}

void UNpcWorldSeeder::SetHttpExecutorForTesting(FNpcSeederHttpExec Exec)
{
    HttpExec = MoveTemp(Exec);
}

// ── Private helpers ───────────────────────────────────────────────────────────

void UNpcWorldSeeder::EnsureHttpExec()
{
    if (HttpExec) return;

    FNpcEngineConfig Config = FNpcEngineConfig::Load();
    if (!Config.IsValid())
    {
        UE_LOG(LogNpcEngine, Error, TEXT("SeedWorld: NpcEngineConfig invalid — missing URL or API key"));
        // Leave HttpExec null; SeedFromJsonString checks and fires OnError.
        return;
    }
    CachedBaseUrl = Config.GetBaseUrl();  // single source; BuildUrl uses this
    HttpExec = [Config](const FString& Verb, const FString& Url, const FString& Body,
                        TFunction<void(int32, const FString&)> OnResult)
    {
        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
        Req->SetVerb(Verb);
        Req->SetURL(Url);
        Req->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
        Req->SetHeader(TEXT("Accept"),        TEXT("application/json"));
        Req->SetHeader(TEXT("Authorization"), Config.MakeBearerHeader());
        Req->SetTimeout(SEED_HTTP_TIMEOUT_SECS);
        if (!Body.IsEmpty()) Req->SetContentAsString(Body);
        Req->OnProcessRequestComplete().BindLambda(
            [OnResult](FHttpRequestPtr, FHttpResponsePtr Resp, bool bConnected)
            {
                if (!bConnected || !Resp.IsValid()) { OnResult(-1, TEXT("")); return; }
                OnResult(Resp->GetResponseCode(), Resp->GetContentAsString());
            });
        Req->ProcessRequest();
    };
}

FString UNpcWorldSeeder::BuildUrl(const FString& Path) const
{
    return CachedBaseUrl + Path;
}

// [A-Za-z0-9_-] only — keeps node/edge IDs safe for URL path segments (H-2).
static bool IsValidGraphId(const FString& S)
{
    if (S.IsEmpty()) return false;
    for (TCHAR C : S)
    {
        if (!FChar::IsAlnum(C) && C != TEXT('_') && C != TEXT('-')) return false;
    }
    return true;
}

bool UNpcWorldSeeder::BuildTasksFromJson(
    const FString& Json,
    TArray<FNodeTask>& OutPreEdge,
    TArray<FEdgeTask>& OutEdges,
    TArray<FNodeTask>& OutPostEdge,
    FString& OutError)
{
    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        OutError = TEXT("Malformed JSON — could not deserialise root object.");
        return false;
    }

    auto SerialiseProps = [](const TSharedPtr<FJsonObject>& Obj) -> FString
    {
        FString S;
        TSharedRef<TJsonWriter<>> W = TJsonWriterFactory<>::Create(&S);
        FJsonSerializer::Serialize(Obj.ToSharedRef(), W);
        return S;
    };

    auto ParseNodeSection = [&](const TArray<FString>& Sections, TArray<FNodeTask>& OutNodes)
    {
        for (const FString& Section : Sections)
        {
            const TArray<TSharedPtr<FJsonValue>>* Items = nullptr;
            if (!Root->TryGetArrayField(Section, Items)) continue;
            for (const TSharedPtr<FJsonValue>& V : *Items)
            {
                const TSharedPtr<FJsonObject>* ItemObj = nullptr;
                if (!V->TryGetObject(ItemObj) || !ItemObj) continue;
                FString NodeType, NodeId;
                (*ItemObj)->TryGetStringField(TEXT("node_type"), NodeType);
                const TSharedPtr<FJsonObject>* Props = nullptr;
                if (!(*ItemObj)->TryGetObjectField(TEXT("properties"), Props) || !Props) continue;
                (*Props)->TryGetStringField(TEXT("id"), NodeId);
                OutNodes.Add({ NodeType, NodeId, SerialiseProps(*Props) });
            }
        }
    };

    ParseNodeSection(PRE_EDGE_SECTIONS,  OutPreEdge);
    ParseNodeSection(POST_EDGE_SECTIONS, OutPostEdge);

    const TArray<TSharedPtr<FJsonValue>>* EdgeArr = nullptr;
    if (Root->TryGetArrayField(TEXT("edges"), EdgeArr))
    {
        for (const TSharedPtr<FJsonValue>& V : *EdgeArr)
        {
            const TSharedPtr<FJsonObject>* E = nullptr;
            if (!V->TryGetObject(E) || !E) continue;
            FString EdgeType, SrcId, DstId, PropsJson = TEXT("{}");
            (*E)->TryGetStringField(TEXT("edge_type"), EdgeType);
            (*E)->TryGetStringField(TEXT("src_id"), SrcId);
            (*E)->TryGetStringField(TEXT("dst_id"), DstId);
            const TSharedPtr<FJsonObject>* Props = nullptr;
            if ((*E)->TryGetObjectField(TEXT("properties"), Props) && Props)
                PropsJson = SerialiseProps(*Props);
            OutEdges.Add({ EdgeType, SrcId, DstId, PropsJson });
        }
    }
    return true;
}

// ── CheckNodeExists ───────────────────────────────────────────────────────────

void UNpcWorldSeeder::CheckNodeExists(
    const FString& NodeType, const FString& NodeId,
    TFunction<void(bool)> OnFound,
    TFunction<void(const FString&)> OnError)
{
    // H-2: reject IDs with characters that would corrupt the URL path.
    if (!IsValidGraphId(NodeType) || !IsValidGraphId(NodeId))
    {
        if (OnError) OnError(FString::Printf(
            TEXT("CheckNodeExists: invalid NodeType=%s or NodeId=%s"), *NodeType, *NodeId));
        return;
    }

    const FString Url = BuildUrl(
        FString::Printf(TEXT("/v1/graph/nodes/%s/%s"), *NodeType, *NodeId));

    HttpExec(TEXT("GET"), Url, TEXT(""),
        [OnFound, OnError, NodeType, NodeId](int32 Status, const FString& Body)
        {
            if (Status == -1)
            {
                if (OnError) OnError(FString::Printf(TEXT("CheckNodeExists: connection failed NodeId=%s"), *NodeId));
                return;
            }
            if (Status >= 500)
            {
                if (OnError) OnError(FString::Printf(TEXT("CheckNodeExists: Status=%d NodeId=%s"), Status, *NodeId));
                return;
            }
            // H-4: auth errors must not silently proceed to upsert.
            if (Status >= 400 && Status < 500 && Status != 404)
            {
                if (OnError) OnError(FString::Printf(
                    TEXT("CheckNodeExists: client error Status=%d NodeId=%s"), Status, *NodeId));
                return;
            }
            if (Status == 404)  { if (OnFound) OnFound(false); return; }
            if (Status >= 200 && Status < 300)
            {
                TSharedPtr<FJsonObject> Env;
                TSharedRef<TJsonReader<>> R = TJsonReaderFactory<>::Create(Body);
                const bool bParsed = FJsonSerializer::Deserialize(R, Env) && Env.IsValid();
                // H-1: a 200 with an unparseable body is a server anomaly — fail fast.
                if (!bParsed)
                {
                    if (OnError) OnError(FString::Printf(
                        TEXT("CheckNodeExists: malformed 200 body NodeId=%s"), *NodeId));
                    return;
                }
                const TSharedPtr<FJsonValue>* Data = Env->Values.Find(TEXT("data"));
                const bool bExists = Data && (*Data)->Type != EJson::Null;
                if (OnFound) OnFound(bExists);
                return;
            }
        });
}

// ── Upsert helpers ────────────────────────────────────────────────────────────

void UNpcWorldSeeder::PostUpsertNode(
    const FString& NodeType, const FString& PropertiesJson, TFunction<void(bool)> OnResult)
{
    if (!IsValidGraphId(NodeType))
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("PostUpsertNode: invalid NodeType=%s — skipping"), *NodeType);
        if (OnResult) OnResult(false);
        return;
    }
    const FString Body = FNpcEngineJsonUtils::SerialiseNodeWrite(PropertiesJson);
    const FString Url  = BuildUrl(FString::Printf(TEXT("/v1/graph/nodes/%s"), *NodeType));
    HttpExec(TEXT("POST"), Url, Body,
        [OnResult, NodeType](int32 Status, const FString& RespBody)
        {
            if (Status < 200 || Status >= 300)
            {
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("PostUpsertNode: Status=%d NodeType=%s Detail=%s"), Status, *NodeType, *RespBody);
            }
            if (OnResult) OnResult(Status >= 200 && Status < 300);
        });
}

void UNpcWorldSeeder::PostUpsertEdge(const FEdgeTask& Task, TFunction<void(bool)> OnResult)
{
    if (!IsValidGraphId(Task.EdgeType) || !IsValidGraphId(Task.SrcId) || !IsValidGraphId(Task.DstId))
    {
        UE_LOG(LogNpcEngine, Warning, TEXT("PostUpsertEdge: invalid edge ids EdgeType=%s Src=%s Dst=%s — skipping"),
            *Task.EdgeType, *Task.SrcId, *Task.DstId);
        if (OnResult) OnResult(false);
        return;
    }
    const FString Body = FNpcEngineJsonUtils::SerialiseEdgeWrite(Task.SrcId, Task.DstId, Task.PropertiesJson);
    const FString Url  = BuildUrl(FString::Printf(TEXT("/v1/graph/edges/%s"), *Task.EdgeType));
    HttpExec(TEXT("POST"), Url, Body,
        [OnResult, EdgeType = Task.EdgeType](int32 Status, const FString& RespBody)
        {
            if (Status < 200 || Status >= 300)
            {
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("PostUpsertEdge: Status=%d EdgeType=%s Detail=%s"), Status, *EdgeType, *RespBody);
            }
            if (OnResult) OnResult(Status >= 200 && Status < 300);
        });
}

// ── Recursive processing chains ───────────────────────────────────────────────

void UNpcWorldSeeder::ProcessNodes(
    TArray<FNodeTask> Tasks, int32 Index,
    TArray<FEdgeTask> Edges, TArray<FNodeTask> PostEdgeNodes,
    TFunction<void()> OnDone, TFunction<void(const FString&)> OnError)
{
    if (Index >= Tasks.Num())
    {
        // Edges empty = post-edge phase is done; call OnDone and stop.
        // Edges non-empty = pre-edge phase is done; advance to edge processing.
        // Without this guard ProcessNodes and ProcessEdges recurse infinitely.
        if (Edges.IsEmpty())
        {
            if (OnDone) OnDone();
            return;
        }
        ProcessEdges(MoveTemp(Edges), 0, MoveTemp(PostEdgeNodes),
                     MoveTemp(OnDone), MoveTemp(OnError));
        return;
    }

    const FNodeTask Task = Tasks[Index];
    CheckNodeExists(Task.NodeType, Task.NodeId,
        [this, Tasks, Index, Edges, PostEdgeNodes, OnDone, OnError, Task](bool bExists) mutable
        {
            if (bExists)
            {
                UE_LOG(LogNpcEngine, Log, TEXT("SeedWorld: Skipped NodeId=%s"), *Task.NodeId);
                ProcessNodes(MoveTemp(Tasks), Index + 1,
                             MoveTemp(Edges), MoveTemp(PostEdgeNodes),
                             MoveTemp(OnDone), MoveTemp(OnError));
                return;
            }
            PostUpsertNode(Task.NodeType, Task.PropertiesJson,
                [this, Tasks, Index, Edges, PostEdgeNodes, OnDone, OnError, Task](bool bOk) mutable
                {
                    if (!bOk)
                    {
                        const FString Msg = FString::Printf(
                            TEXT("SeedWorld halted NodeId=%s Status=fail"), *Task.NodeId);
                        UE_LOG(LogNpcEngine, Error, TEXT("%s"), *Msg);
                        if (OnError) OnError(Msg);
                        return;
                    }
                    ProcessNodes(MoveTemp(Tasks), Index + 1,
                                 MoveTemp(Edges), MoveTemp(PostEdgeNodes),
                                 MoveTemp(OnDone), MoveTemp(OnError));
                });
        },
        [OnError, Task](const FString& Err) mutable
        {
            UE_LOG(LogNpcEngine, Error,
                TEXT("SeedWorld halted NodeId=%s Reason=%s"), *Task.NodeId, *Err);
            if (OnError) OnError(Err);
        });
}

void UNpcWorldSeeder::ProcessEdges(
    TArray<FEdgeTask> Tasks, int32 Index,
    TArray<FNodeTask> PostEdgeNodes,
    TFunction<void()> OnDone, TFunction<void(const FString&)> OnError)
{
    if (Index >= Tasks.Num())
    {
        // All edges done — process post-edge nodes (quests) now.
        ProcessNodes(MoveTemp(PostEdgeNodes), 0,
                     TArray<FEdgeTask>(), TArray<FNodeTask>(),
                     MoveTemp(OnDone), MoveTemp(OnError));
        return;
    }

    const FEdgeTask Task = Tasks[Index];
    PostUpsertEdge(Task,
        [this, Tasks, Index, PostEdgeNodes, OnDone, OnError, Task](bool bOk) mutable
        {
            if (!bOk)
            {
                const FString Msg = FString::Printf(
                    TEXT("SeedWorld halted EdgeType=%s Src=%s Dst=%s"),
                    *Task.EdgeType, *Task.SrcId, *Task.DstId);
                UE_LOG(LogNpcEngine, Error, TEXT("%s"), *Msg);
                if (OnError) OnError(Msg);
                return;
            }
            ProcessEdges(MoveTemp(Tasks), Index + 1, MoveTemp(PostEdgeNodes),
                         MoveTemp(OnDone), MoveTemp(OnError));
        });
}

// ── NpcEngine.SeedWorld console command ───────────────────────────────────────

namespace
{
    // SeedFromJsonString (called via SeedWorld) pins 'this' via AddToRoot/RemoveFromRoot for the
    // async duration — no manual root management needed here.
    void RunNpcEngineSeedWorld(UWorld* /*World*/)
    {
        UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.SeedWorld BEGIN ==="));
        NewObject<UNpcWorldSeeder>()->SeedWorld(
            []() { UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.SeedWorld COMPLETE ===")); },
            [](const FString& Err)
            {
                UE_LOG(LogNpcEngine, Error, TEXT("NpcEngine.SeedWorld FAILED Error=%s"), *Err);
                UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.SeedWorld END (error) ==="));
            });
    }
}

static FAutoConsoleCommandWithWorld GNpcEngineSeedWorldCommand(
    TEXT("NpcEngine.SeedWorld"),
    TEXT("Seed the full demo world from Seed/DemoWorld_v1.json. "
         "Idempotent: existing nodes are skipped. Halts on first non-2xx."),
    FConsoleCommandWithWorldDelegate::CreateStatic(&RunNpcEngineSeedWorld));
