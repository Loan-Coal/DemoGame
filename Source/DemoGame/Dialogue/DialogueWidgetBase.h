// File: DialogueWidgetBase.h
// Module: Game
// Purpose: C++ base class for the dialogue UMG widget — input lock, thinking state, memories badge.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidgetBase.generated.h"

class ANpcActorBase;
class UEditableText;
class UMemoryBadgeLookupAsset;
class UScrollBox;
class UTextBlock;

/**
 * C++ base class for the dialogue UMG widget.
 * UMG visual layout is done in the editor; child Blueprint binds BindWidgetOptional slots.
 *
 * Player flow:
 *   1. BeginDialogue fires  → widget becomes visible, input unlocked.
 *   2. Player types in InputText (≤NpcEngine::MaxPlayerMessageChars, non-empty).
 *   3. Player presses Submit → SubmitInput() → locks input, shows ThinkingIndicator.
 *   4. OnNpcSpoke fires → unlock input, hide ThinkingIndicator, append response to history.
 *   5. OnMemoriesRecalled fires → show MemoriesBadge for 5 s, then auto-hide.
 *   6. EndDialogue fires → widget hides.
 *
 * Does NOT: manage HTTP, parse JSON, hold session state, or change input mode.
 */
UCLASS(Abstract)
class DEMOGAME_API UDialogueWidgetBase : public UUserWidget
{
    GENERATED_BODY()

public:
    // ── Widget lifecycle ─────────────────────────────────────────────────────

    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

    // ── Input handling ───────────────────────────────────────────────────────

    /** Called by the submit button or Enter key. Validates, locks input, forwards to DialogueManager. */
    UFUNCTION(BlueprintCallable, Category = "Dialogue|Input")
    void SubmitInput();

    // ── Engine → Widget events (implementable in Blueprint) ──────────────────

    /** Show the NPC's response line. C++ default appends to ResponseText. */
    UFUNCTION(BlueprintNativeEvent, Category = "Dialogue|Display")
    void OnNpcResponseReceived(const FString& NpcResponse, const FString& NpcDisplayName);

    /** Show an error/fallback message. C++ default writes to ResponseText. */
    UFUNCTION(BlueprintNativeEvent, Category = "Dialogue|Display")
    void OnDialogueError(const FString& ErrorMessage);

    /** Called when the dialogue session begins. C++ default shows widget + clears history. */
    UFUNCTION(BlueprintNativeEvent, Category = "Dialogue|Display")
    void OnDialogueBegun(ANpcActorBase* Npc);

    /** Called when the session ends. C++ default hides the widget. */
    UFUNCTION(BlueprintNativeEvent, Category = "Dialogue|Display")
    void OnDialogueEnded();

    // ── Config ────────────────────────────────────────────────────────────────

    /**
     * DataAsset mapping memory_id → display badge text.
     * Assign DA_MemoryBadgeLookup in the editor. If unset, raw memory ids are shown.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue|Config")
    TObjectPtr<UMemoryBadgeLookupAsset> MemoryBadgeLookup;

protected:
    // ── Bindable widget slots (BindWidgetOptional — null if unbound in UMG editor) ─

    /** Free-text player input field. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UEditableText> InputText;

    /** Main dialogue text display / response history. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> ResponseText;

    /** Scroll box wrapping the response text. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UScrollBox> ResponseScroll;

    /** Shown while waiting for LLM response; hidden on response or error. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> ThinkingIndicator;

    /** Shown for 5 s when the engine returns memories_recalled; auto-hides. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> MemoriesBadge;

private:
    void LockInput();
    void UnlockInput();

    UFUNCTION()
    void OnNpcSpoke(const FString& Response, const FString& DisplayName);
    UFUNCTION()
    void OnNpcError(const FString& Error);
    UFUNCTION()
    void OnBegun(ANpcActorBase* Npc);
    UFUNCTION()
    void OnEnded();
    UFUNCTION()
    void OnMemoriesRecalledHandler(FName NpcId, TArray<FString> Memories);

    FTimerHandle MemoriesBadgeTimerHandle;
};
