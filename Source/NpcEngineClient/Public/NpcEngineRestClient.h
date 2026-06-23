#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcEngineTypes.h"
#include "NpcEngineRestClient.generated.h"

// ── Delegates ────────────────────────────────────────────────────────────────

DECLARE_DELEGATE_OneParam(FOnNpcDialogueComplete, const FNpcDialogueResponse& /*Response*/);
DECLARE_DELEGATE_OneParam(FOnNpcEngineError,      const FString& /*ErrorMessage*/);

/** TODO(TTS): fires when decoded audio PCM is ready to play. */
DECLARE_DELEGATE_OneParam(FOnAudioReady, const TArray<uint8>& /*PCMBytes*/);

/**
 * Async REST client for the NPC Engine.
 *
 * All calls are non-blocking: they kick an HTTP request and return immediately.
 * Callbacks are invoked on the game thread (safe to touch UObjects).
 * A client-side fallback line is returned on timeout or non-2xx errors.
 *
 * Timeouts: dialogue 30 s, health/readiness 3 s.
 * Auth: every request (except /health) carries  Authorization: Bearer <key>.
 */
UCLASS()
class NPCENGINECLIENT_API UNpcEngineRestClient : public UObject
{
    GENERATED_BODY()

public:
    // ── Primary game calls ───────────────────────────────────────────────────

    /**
     * POST /v1/dialogue  (raw response shape A).
     * Validates player_message client-side (non-empty, ≤1000 chars) before sending.
     * On success: OnSuccess receives the full FNpcDialogueResponse.
     * On error/timeout: OnError receives a description; the caller should surface
     *   a fallback line to the player rather than leaving the UI blank.
     */
    void SendDialogue(
        const FNpcDialogueRequest& Request,
        FOnNpcDialogueComplete OnSuccess,
        FOnNpcEngineError OnError);

    /**
     * POST /v1/action  (raw response shape A).
     * bSuccess = true when engine returns { "status": "ok" }.
     */
    void SendActionReport(
        const FNpcActionReportRequest& Request,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError);

    // ── Health / readiness ───────────────────────────────────────────────────

    /** GET /health  (no auth). bOk = true when status == "ok". Timeout 3 s. */
    void GetHealth(TFunction<void(bool /*bOk*/)> OnResult);

    /** GET /readiness  (no auth). bReady = true when llm status != "unreachable". Timeout 3 s. */
    void GetReadiness(TFunction<void(bool /*bReady*/)> OnResult);

    // ── Debug / state reads ──────────────────────────────────────────────────

    /**
     * GET /v1/npc/{npc_id}/state  (envelope shape B).
     * OnResult receives the raw .data JSON string for the debug overlay.
     */
    void GetNpcState(
        const FString& NpcId,
        TFunction<void(const FString& /*DataJson*/)> OnResult,
        FOnNpcEngineError OnError);

    // ── Client-side fallback ─────────────────────────────────────────────────

    static const FString FallbackLine;   // "...(seems distracted and doesn't respond.)"

private:
    void MakeAuthRequest(
        const FString& Verb,
        const FString& Url,
        const FString& Body,
        float TimeoutSecs,
        TFunction<void(int32 /*Status*/, const FString& /*Body*/)> OnComplete);

    FString BuildUrl(const FString& Path) const;
};
