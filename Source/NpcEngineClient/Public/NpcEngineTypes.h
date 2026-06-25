// File: NpcEngineTypes.h
// Module: NpcEngineClient
// Purpose: Contract mirror USTRUCTs and UENUMs for all NPC Engine REST boundary types.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "NpcEngineTypes.generated.h"

// ── Constants ─────────────────────────────────────────────────────────────────

namespace NpcEngine
{
    /** Maximum player message length (characters). Validated client-side before any HTTP call. */
    inline constexpr int32 MaxPlayerMessageChars = 1000;

    /** Trust threshold: Mira reveals Aldric information (Phase 4 gate 1). */
    inline constexpr int32 TrustGate1Mira = 25;

    /** Trust threshold: L_TavernBack sub-level becomes accessible (Phase 5 gate 2). */
    inline constexpr int32 TrustGate2Mira = 40;

    /** Trust threshold: Sorn unlocks patrol_duty quest (Phase 6). */
    inline constexpr int32 TrustGateSornQuest = 50;
}

/**
 * Stable NPC ID FName constants. Values must match the engine seed (DemoWorld_v1.json).
 * Use these everywhere instead of raw string literals — DemoGame source enforces this via check_rules.py.
 */
namespace NpcId
{
    inline const FName MiraInnkeeper   = TEXT("mira_innkeeper");
    inline const FName LiraFence       = TEXT("lira_fence");
    inline const FName AldricMerchant  = TEXT("aldric_merchant");
    inline const FName CaptainSorn     = TEXT("captain_sorn");
    inline const FName OldHenryk       = TEXT("old_henryk");
}

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

/** Relationship change from a single dialogue turn. Each field is -15..15. Mirrors RelationDeltas schema. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcRelationDeltas
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="trust"))
    int32 Trust = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="fear"))
    int32 Fear = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="affection"))
    int32 Affection = 0;
};

/** NPC-initiated action accompanying a dialogue response. Mirrors ActionModel schema. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcActionModel
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="type"))
    ENpcActionType Type = ENpcActionType::Speak;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="target_id"))
    FString TargetId;

    /** Raw JSON object string — parsed lazily if gameplay needs specific params. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="parameters"))
    FString ParametersJson = TEXT("{}");
};

/** Facial expression hint for animation. Intensity is 0–100. Mirrors FacialExpressionModel schema. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcFacialExpression
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="type"))
    ENpcFacialExpression Type = ENpcFacialExpression::Neutral;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="intensity"))
    int32 Intensity = 0;
};

// ── Request structs ──────────────────────────────────────────────────────────

/** Body for POST /v1/dialogue. All three required fields must be non-empty. Mirrors DialogueRequest schema. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcDialogueRequest
{
    GENERATED_BODY()

    /** Must be an existing Character node. Slice-1 default: "player_demo". */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="player_id"))
    FString PlayerId;

    /** Stable NPC seed id e.g. "mira_innkeeper". */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="npc_id"))
    FString NpcId;

    /** Free-text player input. Must be 1–1000 chars (validated before sending). */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="player_message"))
    FString PlayerMessage;

    /** Optional — pass location id for richer context. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="location_id"))
    FString LocationId;

    /** Pass back the session_id from the previous response to continue a conversation. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="session_id"))
    FString SessionId;

    /** Optional — force specific graph node ids into the LLM context window. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="explicit_node_ids"))
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
 * Mirrors DialogueResponse schema.
 */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcDialogueResponse
{
    GENERATED_BODY()

    /** The line to display. This is the only field used in slice-1. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="npc_response"))
    FString NpcResponse;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="relation_deltas"))
    FNpcRelationDeltas RelationDeltas;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="mood_update"))
    FString MoodUpdate;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="emotion"))
    FString Emotion;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="action"))
    FNpcActionModel Action;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="facial_expression"))
    FNpcFacialExpression FacialExpression;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="learned_facts"))
    TArray<FString> LearnedFacts;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="memories_recalled"))
    TArray<FString> MemoriesRecalled;

    /** Pass back on the next turn to continue this conversation. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="session_id"))
    FString SessionId;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="cached"))
    bool bCached = false;

    /** "full" = engine healthy; other values = engine self-degraded. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="degradation_level"))
    FString DegradationLevel = TEXT("full");

    /**
     * TTS audio payload.
     * Over REST this is null/unreliable (raw bytes are not valid UTF-8).
     * Over WebSocket the done message carries audio_bytes_b64 (base64 WAV).
     * TODO(TTS): Decode to PCM and pass to OnAudioReady when TTS is wired.
     */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="audio_bytes"))
    TArray<uint8> AudioBytes;

    /** True if this response was synthesised client-side due to timeout/error. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    bool bIsFallback = false;
};

// ── NPC state snapshot (GET /v1/npc/{npc_id}/state) ──────────────────────────

/** One entry from the NPC's relations array. Mirrors the relations sub-object. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcRelationEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="target_id"))
    FString TargetId;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="trust"))
    int32 Trust = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="fear"))
    int32 Fear = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="affection"))
    int32 Affection = 0;
};

/** One entry from the NPC's events array. knowledge_state tracks gossip propagation. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcEventEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="event_id"))
    FString EventId;

    /** "heard", "knows", "distorted", etc. Empty string if the NPC doesn't know. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="knowledge_state"))
    FString KnowledgeState;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine", meta=(JsonName="hop_count"))
    int32 HopCount = 0;
};

/**
 * Parsed .data from GET /v1/npc/{npc_id}/state (OkEnvelope shape B).
 * All parsing is done inside NpcEngineClient; only this typed struct crosses the module boundary.
 * bValid = false when the HTTP call failed or the parse failed.
 */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FNpcStateSnapshot
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString NpcId;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    FString Name;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    TArray<FNpcRelationEntry> Relations;

    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    TArray<FNpcEventEntry> Events;

    /** False when the HTTP call failed or the JSON envelope was malformed. */
    UPROPERTY(BlueprintReadOnly, Category = "NpcEngine")
    bool bValid = false;
};
