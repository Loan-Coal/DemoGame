#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidgetBase.generated.h"

class UEditableText;
class UTextBlock;
class UScrollBox;
class ANpcActorBase;

/**
 * C++ base class for the dialogue UMG widget.
 * UMG visual layout is done in the editor tomorrow.
 * Child Blueprint widget binds the UPROPERTY(meta=BindWidgetOptional) slots.
 *
 * Player flow:
 *   1. BeginDialogue fires  → widget becomes visible.
 *   2. Player types in InputText (≤1000 chars, non-empty).
 *   3. Player presses Submit → SubmitInput() → DialogueManager.SubmitPlayerMessage().
 *   4. OnNpcResponseReceived fires → append to ResponseText.
 *   5. EndDialogue fires → widget hides.
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

    /** Called by the submit button or Enter key. Validates + forwards to DialogueManager. */
    UFUNCTION(BlueprintCallable, Category = "Dialogue|Input")
    void SubmitInput();

    // ── Engine → Widget events (implementable in Blueprint) ──────────────────

    /** Show the NPC's response line in the dialogue box. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue|Display")
    void OnNpcResponseReceived(const FString& NpcResponse, const FString& NpcDisplayName);

    /** Show an error/fallback message. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue|Display")
    void OnDialogueError(const FString& ErrorMessage);

    /** Called when the dialogue session begins — set the NPC name header. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue|Display")
    void OnDialogueBegun(ANpcActorBase* Npc);

    /** Called when the session ends — hide/reset the widget. */
    UFUNCTION(BlueprintImplementableEvent, Category = "Dialogue|Display")
    void OnDialogueEnded();

    static constexpr int32 MaxPlayerMessageChars = 1000;

protected:
    // ── Bindable widget slots (set up via BindWidgetOptional) ────────────────
    // Layout is applied in the UMG editor tomorrow; these can be null if unbound.

    /** Free-text player input field. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UEditableText> InputText;

    /** Main dialogue text display area. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> ResponseText;

    /** Scroll box wrapping the response text (for history). */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UScrollBox> ResponseScroll;

private:
    void OnNpcSpoke(const FString& Response, const FString& DisplayName);
    void OnNpcError(const FString& Error);
    void OnBegun(ANpcActorBase* Npc);
    void OnEnded();

    // Delegate handles for cleanup.
    FDelegateHandle NpcSpokeHandle;
    FDelegateHandle ErrorHandle;
    FDelegateHandle BegunHandle;
    FDelegateHandle EndedHandle;
};
