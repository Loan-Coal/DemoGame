#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcDialogueService.h"
#include "NpcEngineTypes.h"
#include "DialogueManager.generated.h"

class ANpcActorBase;
class UDialogueComponent;

// ── Public delegates (no NpcEngineClient types exposed in the public API) ────

/** Fires when the NPC produces a response line. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnNpcSpoke,
    const FString&, NpcResponse,
    const FString&, NpcDisplayName);

/** Fires when a dialogue call fails or a fallback line is used. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnDialogueError,
    const FString&, ErrorMessage);

/** Fires when dialogue begins (open the widget). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnDialogueBegun,
    ANpcActorBase*, Npc);

/** Fires when dialogue ends (close the widget). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

/** Fires when the engine returns relationship deltas (trust/fear/affection). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnNpcRelationshipChanged,
    FName, NpcId,
    FNpcRelationDeltas, Deltas);

/** Fires when the engine returns a non-empty memories_recalled array. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnNpcMemoriesRecalled,
    FName, NpcId,
    TArray<FString>, Memories);

/** Fires when the engine returns a facial_expression hint. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
    FOnNpcFacialExpression,
    FName, NpcId,
    ENpcFacialExpression, Expression,
    int32, Intensity);

/**
 * World subsystem that owns the active NPC conversation.
 * Maintains session_id continuity across turns within a conversation.
 *
 * Usage (from player controller):
 *   auto* DM = GetWorld()->GetSubsystem<UDialogueManagerSubsystem>();
 *   DM->BeginDialogue(NpcActor);
 *   DM->SubmitPlayerMessage(TEXT("Good evening, Mira."));
 *   // Bind OnNpcSpoke to update the widget.
 *   DM->EndDialogue();
 */
UCLASS()
class DEMOGAME_API UDialogueManagerSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    // ── Lifecycle ────────────────────────────────────────────────────────────

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ── Public API ───────────────────────────────────────────────────────────

    /** Open a dialogue session with the given NPC. Fires OnDialogueBegun. */
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void BeginDialogue(ANpcActorBase* Npc);

    /** Submit a free-text player message (≤1000 chars, non-empty). Fires OnNpcSpoke or OnDialogueError. */
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void SubmitPlayerMessage(const FString& Message);

    /** Close the active dialogue session. Fires OnDialogueEnded. */
    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void EndDialogue();

    UFUNCTION(BlueprintPure, Category = "Dialogue")
    bool IsInDialogue() const { return ActiveNpc.IsValid(); }

    /**
     * Inject the dialogue service (DIP seam). Overrides the default lazy resolution from the
     * GameInstance composition root — primarily for tests, which supply a fake service.
     */
    void SetDialogueService(TScriptInterface<INpcDialogueService> InService);

    /**
     * Called by UDialogueComponent on a successful engine response.
     * Broadcasts OnNpcSpoke so existing widget subscriptions continue to work.
     */
    void NotifyNpcResponse(const FString& NpcResponse, const FString& DisplayName);

    /**
     * Called by UDialogueComponent on engine error or fallback.
     * Broadcasts OnDialogueError so the widget can surface the message.
     * Fallback: always fires — never silently swallowed.
     */
    void NotifyDialogueError(const FString& ErrorMsg);

    /**
     * Called by UDialogueComponent to bubble relationship/memory/expression events
     * to manager-level delegates (for widgets that subscribe to the manager rather
     * than the per-NPC component directly).
     */
    void NotifyRelationshipChanged(FName NpcId, const FNpcRelationDeltas& Deltas);
    void NotifyMemoriesRecalled(FName NpcId, const TArray<FString>& Memories);
    void NotifyFacialExpression(FName NpcId, ENpcFacialExpression Expression, int32 Intensity);

    // ── Delegates ────────────────────────────────────────────────────────────

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueBegun OnDialogueBegun;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNpcSpoke OnNpcSpoke;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueError OnDialogueError;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueEnded OnDialogueEnded;

    /** Fires when UDialogueComponent reports relationship deltas for the active NPC. */
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNpcRelationshipChanged OnRelationshipChanged;

    /** Fires when UDialogueComponent reports memories recalled for the active NPC. */
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNpcMemoriesRecalled OnNpcMemoriesRecalled;

    /** Fires when UDialogueComponent reports a facial expression hint for the active NPC. */
    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNpcFacialExpression OnFacialExpression;

private:
    /** Receives FNpcDialogueResponse internally — type not exposed in public header. */
    void HandleDialogueResponse(const struct FNpcDialogueResponse& Response);
    void HandleDialogueError(const FString& Error);

    /** Return the injected service, or lazily resolve it from the GameInstance composition root. */
    INpcDialogueService* ResolveService();

    TWeakObjectPtr<ANpcActorBase> ActiveNpc;
    FString ActiveSessionId;   // persists across turns in one conversation

    /** The dialogue service (abstract). Injected by tests, else resolved from the GI subsystem. */
    UPROPERTY()
    TScriptInterface<INpcDialogueService> DialogueService;
};
