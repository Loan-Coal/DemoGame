// File: QuestLogWidget.h
// Module: DemoGame
// Purpose: C++ base for WBP_QuestLog — displays active quests and step checkboxes.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestSubsystem.h"
#include "QuestLogWidget.generated.h"

class UVerticalBox;

/**
 * C++ base for the quest log overlay widget.
 *
 * Bind `QuestList` (Vertical Box) in the WBP_QuestLog subclass.
 * Populate is called automatically on OnQuestActivated and OnStepCompleted.
 * Blueprint subclass adds visual styling only — no logic.
 *
 * Layout: a legible default HUD panel (header + QuestList) is built in C++ when no designer
 * layout is present; an authored WBP overrides it automatically.
 */
UCLASS()
class DEMOGAME_API UQuestLogWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /**
     * Rebuilds the quest list display from the current QuestSubsystem state.
     * Override in Blueprint for custom row construction.
     */
    UFUNCTION(BlueprintNativeEvent, Category = "Quest")
    void RefreshQuestList();
    virtual void RefreshQuestList_Implementation();

protected:
    /** Vertical Box for quest entry rows. Wire in the WBP_QuestLog Blueprint subclass. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UVerticalBox> QuestList;

private:
    /** Build the legible default HUD panel (header + QuestList) when no designer layout exists. */
    void BuildDefaultTree();

    UFUNCTION()
    void OnQuestActivated(FName QuestId);

    UFUNCTION()
    void OnStepCompleted(FName QuestId, FName StepId);
};
