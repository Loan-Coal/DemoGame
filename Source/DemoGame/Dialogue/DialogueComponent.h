// File: DialogueComponent.h
// Module: Game
// Purpose: Per-NPC actor component owning dialogue session state, trust accumulation, and fallback lookup.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NpcDialogueService.h"
#include "NpcEngineTypes.h"
#include "DialogueComponent.generated.h"

class UNpcFallbackLinesAsset;

// ── Per-NPC dialogue delegates ────────────────────────────────────────────────

/** Fires when the engine returns relationship deltas for this NPC. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueTrustChanged,
    FName, NpcId, FNpcRelationDeltas, Deltas);

/** Fires when the engine returns a non-empty memories_recalled array. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueMemoriesRecalled,
    FName, NpcId, TArray<FString>, Memories);

/** Fires when the engine returns a facial_expression hint. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnDialogueFacialExpression,
    FName, NpcId, ENpcFacialExpression, Expression, int32, Intensity);

/**
 * Fires on engine timeout or non-2xx response.
 * FallbackText comes from DA_NpcFallbackLines (may be empty if no entry is authored).
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueFallbackLine,
    FName, NpcId, FText, FallbackText);

/**
 * UDialogueComponent — attached to each ANpcActorBase.
 *
 * Owns the per-NPC dialogue session lifecycle: calls INpcDialogueService::SendDialogue directly,
 * tracks accumulated trust across turns, resolves fallback lines from UNpcFallbackLinesAsset,
 * and fires per-NPC delegates for trust, memories, expression, and fallback.
 *
 * On success: fires OnTrustChanged, OnMemoriesRecalled (if non-empty), OnFacialExpression,
 *   then notifies UDialogueManagerSubsystem to broadcast OnNpcSpoke for the widget.
 * On error:   fires OnFallbackLine; also notifies the manager for widget fallback display.
 * Never crashes on timeout or non-2xx. Never logs the API key.
 *
 * Does NOT: manage UMG widget lifecycle; touch FHttpModule; change input mode.
 * Dependencies injected: INpcDialogueService via SetDialogueService (tests) or UNpcEngineServiceSubsystem.
 */
UCLASS(ClassGroup=(NPC), meta=(BlueprintSpawnableComponent))
class DEMOGAME_API UDialogueComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDialogueComponent();

    // ── API ──────────────────────────────────────────────────────────────────

    /**
     * Begin a dialogue session with this NPC.
     * Clears AccumulatedTrust and SessionId; calls UDialogueManagerSubsystem::BeginDialogue.
     * Input mode is managed by ADemoGameCharacter — not by this component.
     * Fallback: no-op and logs a warning if owner has no NpcId set.
     */
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void StartDialogue(APlayerController* PC);

    /**
     * Submit a player message. Validates non-empty and ≤ NpcEngine::MaxPlayerMessageChars.
     * Silently drops invalid messages — no delegate fires and no HTTP call is made.
     * Non-blocking — returns immediately; callbacks fire on the game thread.
     *
     * Fallback contract: on timeout/non-2xx → fires OnFallbackLine; game continues; never crashes.
     */
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SubmitMessage(const FString& PlayerMessage);

    /** Inject the dialogue service (DIP seam). Overrides default lazy resolution — primarily for tests. */
    void SetDialogueService(TScriptInterface<INpcDialogueService> InService);

    // ── Delegates ─────────────────────────────────────────────────────────────

    UPROPERTY(BlueprintAssignable, Category = "Dialogue|Events")
    FOnDialogueTrustChanged OnTrustChanged;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue|Events")
    FOnDialogueMemoriesRecalled OnMemoriesRecalled;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue|Events")
    FOnDialogueFacialExpression OnFacialExpression;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue|Events")
    FOnDialogueFallbackLine OnFallbackLine;

    // ── Config ────────────────────────────────────────────────────────────────

    /**
     * DataAsset containing per-NPC fallback lines.
     * Assign DA_NpcFallbackLines in the editor.
     * If unset or missing an entry for this NPC, OnFallbackLine fires with an empty FText.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue|Config")
    TObjectPtr<UNpcFallbackLinesAsset> FallbackLinesAsset;

    // ── State (read-only for observability) ───────────────────────────────────

    /** Accumulated trust delta for this NPC across turns in the current session. */
    UPROPERTY(BlueprintReadOnly, Category = "Dialogue|State")
    int32 AccumulatedTrust = 0;

private:
    FString SessionId;

    UPROPERTY()
    TScriptInterface<INpcDialogueService> DialogueService;

    INpcDialogueService* ResolveService();
    FName GetOwnerNpcId() const;
    FNpcDialogueRequest BuildRequest(const FString& PlayerMessage, FName NpcId) const;
    void SendToService(const FNpcDialogueRequest& Request, INpcDialogueService* Service);

    void HandleResponse(const FNpcDialogueResponse& Response);
    void NotifyManagerOfResponse(FName NpcId, const FNpcDialogueResponse& Response);
    void NotifyGossipCache(FName NpcId, const FNpcDialogueResponse& Response);
    void HandleError(const FString& Error);
};
