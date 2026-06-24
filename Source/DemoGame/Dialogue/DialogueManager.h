#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcDialogueService.h"
#include "DialogueManager.generated.h"

class ANpcActorBase;

// ── Public delegates (no NpcEngineClient types exposed in the public API) ────

/** Fires when the NPC produces a response line. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnNpcSpoke,
    const FString&, NpcResponse,
    const FString&, NpcDisplayName);

/** Fires when a dialogue call fails. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnDialogueError,
    const FString&, ErrorMessage);

/** Fires when dialogue begins (open the widget). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
    FOnDialogueBegun,
    ANpcActorBase*, Npc);

/** Fires when dialogue ends (close the widget). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

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

    // ── Delegates ────────────────────────────────────────────────────────────

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueBegun OnDialogueBegun;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnNpcSpoke OnNpcSpoke;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueError OnDialogueError;

    UPROPERTY(BlueprintAssignable, Category = "Dialogue")
    FOnDialogueEnded OnDialogueEnded;

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
