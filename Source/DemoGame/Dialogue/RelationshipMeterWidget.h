// File: RelationshipMeterWidget.h
// Module: Game
// Purpose: UMG widget displaying accumulated trust/fear/affection deltas for the active NPC.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcEngineTypes.h"
#include "RelationshipMeterWidget.generated.h"

class UTextBlock;

/**
 * URelationshipMeterWidget — greybox trust/fear/affection readout.
 * Subscribes to UDialogueManagerSubsystem::OnRelationshipChanged; keeps a running session total.
 * Layout and visual polish (lerp animation, progress bars) live in the Blueprint subclass.
 *
 * Does NOT: parse JSON, hold session state beyond per-session totals, or call INpcDialogueService.
 * Dependencies injected: none — reads from UDialogueManagerSubsystem via GetWorld()->GetSubsystem.
 *
 * Layout: a legible default HUD panel is built in C++ when no designer layout is present; an
 * authored WBP overrides it automatically.
 */
UCLASS()
class DEMOGAME_API URelationshipMeterWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /** Reset accumulated totals (call when a new dialogue session begins). */
    UFUNCTION(BlueprintCallable, Category = "Relationship")
    void ResetSession();

    // ── Accumulated session totals (read-only) ─────────────────────────────────

    UPROPERTY(BlueprintReadOnly, Category = "Relationship|State")
    int32 SessionTrust = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Relationship|State")
    int32 SessionFear = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Relationship|State")
    int32 SessionAffection = 0;

protected:
    // ── BindWidgetOptional slots (set up in UMG editor) ───────────────────────

    /** Shows signed trust delta formatted as "+N" / "-N". */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> TrustText;

    /** Shows signed fear delta. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> FearText;

    /** Shows signed affection delta. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> AffectionText;

    /** Override to react to relationship changes in Blueprint (called after C++ updates). */
    UFUNCTION(BlueprintNativeEvent, Category = "Relationship")
    void OnRelationshipUpdated(int32 Trust, int32 Fear, int32 Affection);

private:
    void UpdateDisplay();

    /** Build the legible default HUD panel when no designer layout exists. */
    void BuildDefaultTree();

    UFUNCTION()
    void OnRelationshipChanged(FName NpcId, FNpcRelationDeltas Deltas);

    UFUNCTION()
    void OnDialogueBegun(class ANpcActorBase* Npc);
};
