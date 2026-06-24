// File: NpcEngineRestClient.h
// Module: NpcEngineClient
// Purpose: Async REST client for the NPC Engine; implements INpcDialogueService and INpcQuestService.
// Net I/O: yes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcEngineTypes.h"
#include "NpcDialogueService.h"
#include "NpcQuestService.h"
#include "NpcEngineRestClient.generated.h"

// ── Delegates ────────────────────────────────────────────────────────────────
// FOnNpcDialogueComplete / FOnNpcEngineError now live in NpcDialogueService.h (included above).

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
class NPCENGINECLIENT_API UNpcEngineRestClient : public UObject,
    public INpcDialogueService,
    public INpcQuestService
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
    virtual void SendDialogue(
        const FNpcDialogueRequest& Request,
        FOnNpcDialogueComplete OnSuccess,
        FOnNpcEngineError OnError) override;

    /**
     * POST /v1/action  (raw response shape A).
     * bSuccess = true when engine returns { "status": "ok" }.
     */
    virtual void SendActionReport(
        const FNpcActionReportRequest& Request,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError) override;

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
    virtual void GetNpcState(
        const FString& NpcId,
        TFunction<void(const FString& /*DataJson*/)> OnResult,
        FOnNpcEngineError OnError) override;

    /**
     * POST /clock/advance  (envelope shape B). DEC-014.
     * Body: { "delta_ticks": DeltaTicks }.
     * OnResult(true) on 2xx; OnResult(false) + OnError on non-2xx or parse failure.
     * Non-blocking — returns immediately; callback fires on the game thread.
     */
    virtual void AdvanceClock(
        int32 DeltaTicks,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError) override;

    // ── Quest lifecycle (INpcQuestService) ───────────────────────────────────

    /** POST /v1/quest/offer — register quest + objectives. */
    virtual void QuestOffer(
        const FQuestOfferRequest& Request,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

    /** POST /v1/quest/accept — player accepts quest. */
    virtual void QuestAccept(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

    /** POST /v1/quest/objective — record objective progress. */
    virtual void QuestObjective(
        const FQuestObjectiveRequest& Request,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

    /** POST /v1/quest/evaluate — check if all objectives satisfied. */
    virtual void QuestEvaluate(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

    /** POST /v1/quest/reward — deliver reward to player. */
    virtual void QuestReward(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

    /**
     * POST /v1/quest/{quest_id}/choose — faction fork branch.
     * QuestId in URL path; PlayerId + ChoiceId in body.
     */
    virtual void QuestChoose(
        const FString& QuestId,
        const FString& PlayerId,
        const FString& ChoiceId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override;

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
