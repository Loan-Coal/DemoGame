#pragma once

#include "CoreMinimal.h"
#include "NpcEngineTypes.h"

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

    // ── TTS stub ─────────────────────────────────────────────────────────────

    /**
     * TODO(TTS): Decode a base64-encoded WAV string (audio_bytes_b64 from WS done message)
     * into raw PCM bytes suitable for USoundWaveProcedural.
     * Currently a no-op stub — returns false and leaves Out empty.
     */
    static bool ParseTTSAudio(const FString& Base64Wav, TArray<uint8>& Out);
};
