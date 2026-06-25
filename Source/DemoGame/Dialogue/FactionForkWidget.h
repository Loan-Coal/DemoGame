// File: FactionForkWidget.h
// Module: DemoGame
// Purpose: C++ base for the binary faction fork choice overlay.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FactionForkWidget.generated.h"

class UButton;
class UTextBlock;

/** Fires when the player makes a faction fork choice. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnForkChoiceMade,
    FName, QuestId, FName, ChoiceId);

/**
 * C++ base for the faction fork binary choice overlay.
 *
 * Usage: call SetForkContext(...) before displaying. Bind ChoiceAButton / ChoiceBButton
 * in WBP_FactionFork. Labels (ChoiceALabel, ChoiceBLabel) show authored option text.
 * Caller handles the OnForkChoiceMade event by routing to UFactionSubsystem::ExecuteForkChoice.
 *
 * Layout: if no designer layout is present (empty WidgetTree root), a legible default tree is
 * built in C++ (RebuildWidget). An authored WBP overrides it automatically — see DEC on UI-in-C++.
 */
UCLASS()
class DEMOGAME_API UFactionForkWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /**
     * Prime the widget before showing.
     * Sets authored labels and stores quest context.
     */
    UFUNCTION(BlueprintCallable, Category = "Faction")
    void SetForkContext(
        FName InQuestId,
        FName InChoiceAId,
        const FText& LabelA,
        FName InChoiceBId,
        const FText& LabelB);

    UPROPERTY(BlueprintAssignable, Category = "Faction")
    FOnForkChoiceMade OnForkChoiceMade;

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UButton> ChoiceAButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UButton> ChoiceBButton;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> ChoiceALabel;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> ChoiceBLabel;

private:
    /** Build the legible default tree when no designer layout exists. */
    void BuildDefaultTree();

    FName PendingQuestId;
    FName ChoiceAId;
    FName ChoiceBId;

    UFUNCTION()
    void OnChoiceAClicked();

    UFUNCTION()
    void OnChoiceBClicked();
};
