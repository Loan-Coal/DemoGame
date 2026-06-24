#include "NpcEngineRestClient.h"
#include "NpcEngineClient.h"
#include "NpcEngineConfig.h"
#include "NpcEngineJsonUtils.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

const FString UNpcEngineRestClient::FallbackLine =
    TEXT("...(seems distracted and doesn't respond.)");

// ── Internal helpers ─────────────────────────────────────────────────────────

FString UNpcEngineRestClient::BuildUrl(const FString& Path) const
{
    static FNpcEngineConfig Config = FNpcEngineConfig::Load();
    return Config.GetBaseUrl() + Path;
}

void UNpcEngineRestClient::MakeAuthRequest(
    const FString& Verb,
    const FString& Url,
    const FString& Body,
    float TimeoutSecs,
    TFunction<void(int32 /*Status*/, const FString& /*Body*/)> OnComplete)
{
    static FNpcEngineConfig Config = FNpcEngineConfig::Load();

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();

    Request->SetVerb(Verb);
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Content-Type"),  TEXT("application/json"));
    Request->SetHeader(TEXT("Accept"),        TEXT("application/json"));
    Request->SetHeader(TEXT("Authorization"), Config.MakeBearerHeader());
    Request->SetTimeout(TimeoutSecs);

    if (!Body.IsEmpty())
    {
        Request->SetContentAsString(Body);
    }

    Request->OnProcessRequestComplete().BindLambda(
        [OnComplete](FHttpRequestPtr /*Req*/, FHttpResponsePtr Response, bool bConnected)
        {
            if (!bConnected || !Response.IsValid())
            {
                OnComplete(-1, TEXT(""));
                return;
            }
            OnComplete(Response->GetResponseCode(), Response->GetContentAsString());
        });

    Request->ProcessRequest();
}

// ── Public API ───────────────────────────────────────────────────────────────

void UNpcEngineRestClient::SendDialogue(
    const FNpcDialogueRequest& Request,
    FOnNpcDialogueComplete OnSuccess,
    FOnNpcEngineError OnError)
{
    // Client-side validation (contract §1).
    if (Request.PlayerMessage.IsEmpty())
    {
        OnError.ExecuteIfBound(TEXT("player_message must not be empty."));
        return;
    }
    if (Request.PlayerMessage.Len() > 1000)
    {
        OnError.ExecuteIfBound(FString::Printf(
            TEXT("player_message exceeds 1000 chars (%d)."), Request.PlayerMessage.Len()));
        return;
    }

    const FString Body = FNpcEngineJsonUtils::SerialiseDialogueRequest(Request);
    const FString Url  = BuildUrl(TEXT("/v1/dialogue"));

    MakeAuthRequest(TEXT("POST"), Url, Body, 30.f,
        [OnSuccess, OnError](int32 Status, const FString& ResponseBody)
        {
            if (Status == 200)
            {
                FNpcDialogueResponse Parsed;
                if (FNpcEngineJsonUtils::ParseDialogueResponse(ResponseBody, Parsed))
                {
                    OnSuccess.ExecuteIfBound(Parsed);
                }
                else
                {
                    UE_LOG(LogNpcEngine, Warning, TEXT("SendDialogue: 200 but parse failed."));
                    FNpcDialogueResponse Fallback;
                    Fallback.NpcResponse  = FallbackLine;
                    Fallback.bIsFallback  = true;
                    OnSuccess.ExecuteIfBound(Fallback);
                }
            }
            else if (Status == 422)
            {
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("SendDialogue 422 — player_id or npc_id not found. Body: %s"), *ResponseBody);
                OnError.ExecuteIfBound(
                    TEXT("NPC not found in engine graph. Run the seed command first."));
            }
            else if (Status == 401)
            {
                UE_LOG(LogNpcEngine, Warning, TEXT("SendDialogue 401 — check NPC_ENGINE_API_KEY."));
                OnError.ExecuteIfBound(TEXT("Authentication failed. Check your API key."));
            }
            else
            {
                // timeout (-1) or other error — surface fallback line
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("SendDialogue failed (status %d). Using fallback line."), Status);
                FNpcDialogueResponse Fallback;
                Fallback.NpcResponse = FallbackLine;
                Fallback.bIsFallback = true;
                OnSuccess.ExecuteIfBound(Fallback);
            }
        });
}

void UNpcEngineRestClient::SendActionReport(
    const FNpcActionReportRequest& Request,
    TFunction<void(bool)> OnResult,
    FOnNpcEngineError OnError)
{
    const FString Body = FNpcEngineJsonUtils::SerialiseActionReportRequest(Request);
    const FString Url  = BuildUrl(TEXT("/v1/action"));

    MakeAuthRequest(TEXT("POST"), Url, Body, 10.f,
        [OnResult, OnError](int32 Status, const FString& ResponseBody)
        {
            if (Status == 200)
            {
                // Raw shape A: { "status": "ok"|"ignored", ... }
                const bool bOk = ResponseBody.Contains(TEXT("\"ok\""));
                OnResult(bOk);
            }
            else
            {
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("SendActionReport failed (status %d)."), Status);
                OnError.ExecuteIfBound(FString::Printf(
                    TEXT("Action report failed with status %d."), Status));
            }
        });
}

void UNpcEngineRestClient::GetHealth(TFunction<void(bool)> OnResult)
{
    // /health has no auth and no /v1 prefix.
    const FString Url = BuildUrl(TEXT("/health"));

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();
    Request->SetVerb(TEXT("GET"));
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Accept"), TEXT("application/json"));
    Request->SetTimeout(3.f);

    Request->OnProcessRequestComplete().BindLambda(
        [OnResult](FHttpRequestPtr /*Req*/, FHttpResponsePtr Response, bool bConnected)
        {
            const bool bOk = bConnected && Response.IsValid() &&
                             Response->GetResponseCode() == 200;
            if (!bOk)
            {
                UE_LOG(LogNpcEngine, Warning, TEXT("GetHealth: engine unreachable or non-200."));
            }
            OnResult(bOk);
        });

    Request->ProcessRequest();
}

void UNpcEngineRestClient::GetReadiness(TFunction<void(bool)> OnResult)
{
    const FString Url = BuildUrl(TEXT("/readiness"));

    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
        FHttpModule::Get().CreateRequest();
    Request->SetVerb(TEXT("GET"));
    Request->SetURL(Url);
    Request->SetHeader(TEXT("Accept"), TEXT("application/json"));
    Request->SetTimeout(3.f);

    Request->OnProcessRequestComplete().BindLambda(
        [OnResult](FHttpRequestPtr /*Req*/, FHttpResponsePtr Response, bool bConnected)
        {
            if (!bConnected || !Response.IsValid() || Response->GetResponseCode() != 200)
            {
                OnResult(false);
                return;
            }
            // { "data": { "status": "ready|degraded", "llm": "ok|unreachable" } }
            const bool bReady = !Response->GetContentAsString().Contains(TEXT("\"unreachable\""));
            OnResult(bReady);
        });

    Request->ProcessRequest();
}

void UNpcEngineRestClient::AdvanceClock(
    int32 DeltaTicks,
    TFunction<void(bool)> OnResult,
    FOnNpcEngineError OnError)
{
    const FString Body = FNpcEngineJsonUtils::SerialiseClockAdvance(DeltaTicks);
    const FString Url  = BuildUrl(TEXT("/clock/advance"));

    MakeAuthRequest(TEXT("POST"), Url, Body, 10.f,
        [OnResult, OnError](int32 Status, const FString& ResponseBody)
        {
            if (Status != 200)
            {
                UE_LOG(LogNpcEngine, Error,
                    TEXT("AdvanceClock failed Status=%d"), Status);
                OnError.ExecuteIfBound(FString::Printf(
                    TEXT("ClockAdvance failed Status=%d"), Status));
                OnResult(false);
                return;
            }
            TSharedPtr<FJsonObject> Data;
            const bool bOk = FNpcEngineJsonUtils::UnwrapEnvelopeData(ResponseBody, Data);
            if (!bOk)
            {
                UE_LOG(LogNpcEngine, Error,
                    TEXT("AdvanceClock: envelope parse failed. Body=%s"), *ResponseBody);
                OnError.ExecuteIfBound(TEXT("ClockAdvance: envelope parse failed."));
            }
            OnResult(bOk);
        });
}

void UNpcEngineRestClient::GetNpcState(
    const FString& NpcId,
    TFunction<void(const FString&)> OnResult,
    FOnNpcEngineError OnError)
{
    const FString Url = BuildUrl(FString::Printf(
        TEXT("/v1/npc/%s/state?include_relations=true&include_events=true"), *NpcId));

    MakeAuthRequest(TEXT("GET"), Url, TEXT(""), 10.f,
        [OnResult, OnError](int32 Status, const FString& ResponseBody)
        {
            if (Status != 200)
            {
                OnError.ExecuteIfBound(FString::Printf(
                    TEXT("GetNpcState failed (status %d)."), Status));
                return;
            }
            TSharedPtr<FJsonObject> Data;
            if (FNpcEngineJsonUtils::UnwrapEnvelopeData(ResponseBody, Data))
            {
                FString DataStr;
                TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&DataStr);
                FJsonSerializer::Serialize(Data.ToSharedRef(), Writer);
                OnResult(DataStr);
            }
            else
            {
                OnError.ExecuteIfBound(TEXT("GetNpcState: failed to unwrap envelope."));
            }
        });
}
