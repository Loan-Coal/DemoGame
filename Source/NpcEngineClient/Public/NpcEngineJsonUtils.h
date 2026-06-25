#pragma once

#include "CoreMinimal.h"
#include "NpcEngineTypes.h"
#include "NpcQuestTypes.h"

/**
 * Static JSON helpers for NPC Engine payloads.
 *
 * The engine uses TWO response shapes — this class centralises the branching:
 *   Shape A (raw)       — POST /v1/dialogue, POST /v1/action → parse body directly.
 *   Shape B (envelope)  — everything else → unwrap .data field first.
 */
class NPCENGINECLIENT_API FNpcEngineJsonUtils
{
public:
    // ── Deserialisation ──────────────────────────────────────────────────────

    /** Shape A — parse a raw DialogueResponse JSON body directly. */
    static bool ParseDialogueResponse(const FString& JsonBody, FNpcDialogueResponse& Out);

    /** Shape B — extract the .data object from an OkEnvelope body.
     *  Returns false if .error is non-null or .data is missing. */
    static bool UnwrapEnvelopeData(const FString& JsonBody, TSharedPtr<FJsonObject>& OutData);

    // ── Enum helpers (log + fallback on unknown value) ───────────────────────

    static ENpcActionType ActionTypeFromString(const FString& Str);
    static ENpcFacialExpression FacialExpressionFromString(const FString& Str);

    // ── Serialisation ────────────────────────────────────────────────────────

    static FString SerialiseDialogueRequest(const FNpcDialogueRequest& Req);
    static FString SerialiseActionReportRequest(const FNpcActionReportRequest& Req);

    /** Serialise the /clock/advance request body: { "delta_ticks": DeltaTicks }. DEC-014. */
    static FString SerialiseClockAdvance(int32 DeltaTicks);

    /**
     * Serialise a seed node body: { "properties": { ... } }
     * The properties object is passed in as an already-serialised JSON string.
     */
    static FString SerialiseNodeWrite(const FString& PropertiesJson);

    /**
     * Serialise a seed edge body: { "src_id": ..., "dst_id": ..., "properties": { ... } }
     */
    static FString SerialiseEdgeWrite(const FString& SrcId, const FString& DstId, const FString& PropertiesJson);

    // ── Quest lifecycle serialisation (DEC-027) ──────────────────────────────

    /** POST /v1/quest/offer — body with quest_id, player_id, title, objectives array. */
    static FString SerialiseQuestOffer(const FQuestOfferRequest& Req);

    /** POST /v1/quest/accept — body with quest_id and player_id. */
    static FString SerialiseQuestAccept(const FString& QuestId, const FString& PlayerId);

    /** POST /v1/quest/objective — body with quest_id, player_id, objective_id, progress_delta. */
    static FString SerialiseQuestObjective(const FQuestObjectiveRequest& Req);

    /** POST /v1/quest/evaluate — body with quest_id and player_id. */
    static FString SerialiseQuestEvaluate(const FString& QuestId, const FString& PlayerId);

    /** POST /v1/quest/reward — body with quest_id and player_id. */
    static FString SerialiseQuestReward(const FString& QuestId, const FString& PlayerId);

    /**
     * POST /v1/quest/{quest_id}/choose body — player_id and choice_id ONLY.
     * quest_id goes in the URL path (caller's responsibility); it is NOT in the body.
     */
    static FString SerialiseQuestChoose(const FString& PlayerId, const FString& ChoiceId);

    // ── NPC state snapshot parsing (Phase 6) ─────────────────────────────────

    /**
     * Parse the `.data` object from a GetNpcState OkEnvelope into FNpcStateSnapshot.
     * Caller should call UnwrapEnvelopeData first to get the DataObj.
     * Returns false (and sets Out.bValid=false) if DataObj is null or malformed.
     */
    static bool ParseNpcStateSnapshot(
        const TSharedPtr<FJsonObject>& DataObj, FNpcStateSnapshot& Out);

    // ── TTS stub ─────────────────────────────────────────────────────────────

    /**
     * TODO(TTS): Decode a base64-encoded WAV string (audio_bytes_b64 from WS done message)
     * into raw PCM bytes suitable for USoundWaveProcedural.
     * Currently a no-op stub — returns false and leaves Out empty.
     */
    static bool ParseTTSAudio(const FString& Base64Wav, TArray<uint8>& Out);
};
