#pragma once

#include "CoreMinimal.h"
#include "NpcEngineTypes.generated.h"

// ── Enums ────────────────────────────────────────────────────────────────────

/** Action the NPC intends to perform. Engine coerces unknown values → Speak. */
UENUM(BlueprintType)
enum class ENpcActionType : uint8
{
    Speak     UMETA(DisplayName = "Speak"),
    Move      UMETA(DisplayName = "Move"),
    Give      UMETA(DisplayName = "Give"),
    Take      UMETA(DisplayName = "Take"),
    Attack    UMETA(DisplayName = "Attack"),
    Flee      UMETA(DisplayName = "Flee"),
    Idle      UMETA(DisplayName = "Idle"),
    Unknown   UMETA(DisplayName = "Unknown")   // safe fallback for forward-compat
};

/** NPC facial expression. Engine uses a closed set; Unknown = safe fallback. */
UENUM(BlueprintType)
enum class ENpcFacialExpression : uint8
{
    Neutral   UMETA(DisplayName = "Neutral"),
    Happy     UMETA(DisplayName = "Happy"),
    Sad       UMETA(DisplayName = "Sad"),
    Angry     UMETA(DisplayName = "Angry"),
    Fearful   UMETA(DisplayName = "Fearful"),
    Surprised UMETA(DisplayName = "Surprised"),
    Disgusted UMETA(DisplayName = "Disgusted"),
    Contempt  UMETA(DisplayName = "Contempt"),
    Unknown   UMETA(DisplayName = "Unknown")   // safe fallback
};

// ── Sub-structs ───────────────────────────────────────────────────────────────

/** Relationship change from a single dialogue turn. Each field is -15..15. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcRelationDeltas
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    int32 Trust = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    int32 Fear = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    int32 Affection = 0;
};

/** NPC-initiated action accompanying a dialogue response. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcActionModel
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    ENpcActionType Type = ENpcActionType::Speak;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString TargetId;

    /** Raw JSON object string — parsed lazily if gameplay needs specific params. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString ParametersJson = TEXT("{}");
};

/** Facial expression hint for animation. Intensity is 0–100. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcFacialExpression
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    ENpcFacialExpression Type = ENpcFacialExpression::Neutral;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    int32 Intensity = 0;
};

// ── Request structs ──────────────────────────────────────────────────────────

/** Body for POST /v1/dialogue. All three required fields must be non-empty. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcDialogueRequest
{
    GENERATED_BODY()

    /** Must be an existing Character node. Slice-1 default: "player_demo". */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString PlayerId;

    /** Stable NPC seed id e.g. "mira_innkeeper". */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString NpcId;

    /** Free-text player input. Must be 1–1000 chars (validated before sending). */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString PlayerMessage;

    /** Optional — pass location id for richer context. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString LocationId;

    /** Pass back the session_id from the previous response to continue a conversation. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString SessionId;

    /** Optional — force specific graph node ids into the LLM context window. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    TArray<FString> ExplicitNodeIds;
};

/** Body for POST /v1/action. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcActionReportRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString ActionType;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString PlayerId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString NpcId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    int32 Intensity = 0;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString CounterpartyId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    int32 CurrencyAmount = 0;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString SessionScope;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine")
    FString CurrencyReason;
};

// ── Response structs ─────────────────────────────────────────────────────────

/**
 * Full response from POST /v1/dialogue (raw shape — no OkEnvelope wrapper).
 * Slice-1 displays only NpcResponse. All other fields are modelled now for
 * animation, relationship tracking, and TTS — wired in later slices.
 */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcDialogueResponse
{
    GENERATED_BODY()

    /** The line to display. This is the only field used in slice-1. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString NpcResponse;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FNpcRelationDeltas RelationDeltas;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString MoodUpdate;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString Emotion;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FNpcActionModel Action;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FNpcFacialExpression FacialExpression;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    TArray<FString> LearnedFacts;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    TArray<FString> MemoriesRecalled;

    /** Pass back on the next turn to continue this conversation. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString SessionId;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    bool bCached = false;

    /** "full" = engine healthy; other values = engine self-degraded. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString DegradationLevel = TEXT("full");

    /**
     * TTS audio payload.
     * Over REST this is null/unreliable (raw bytes are not valid UTF-8).
     * Over WebSocket the done message carries audio_bytes_b64 (base64 WAV).
     * TODO(TTS): Decode to PCM and pass to OnAudioReady when TTS is wired.
     */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    TArray<uint8> AudioBytes;

    /** True if this response was synthesised client-side due to timeout/error. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    bool bIsFallback = false;
};
