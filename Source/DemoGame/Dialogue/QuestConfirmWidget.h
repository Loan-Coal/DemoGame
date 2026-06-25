// File: QuestConfirmWidget.h
// Module: DemoGame
// Purpose: C++ base for quest accept/decline overlay (appears on NPC quest offer).
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestConfirmWidget.generated.h"

class UTextBlock;
class UButton;

/** Fires when the player accepts the quest. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestAccepted, FName, QuestId);

/** Fires when the player declines the quest. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestDeclined, FName, QuestId);

/**
 * C++ base for the quest confirmation overlay.
 *
 * Usage: set PendingQuestId before showing; bind AcceptButton/DeclineButton in WBP_QuestConfirm.
 * OnQuestAccepted fires → caller invokes UQuestSubsystem::ActivateQuest.
 *
 * Layout: a legible default tree is built in C++ when no designer layout is present; an authored
 * WBP overrides it automatically.
 */
UCLASS()
class DEMOGAME_API UQuestConfirmWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual TSharedRef<SWidget> RebuildWidget() override;

    /**
     * Prime the widget before displaying.
     * Sets QuestTitleText to the authored title; stores PendingQuestId.
     */
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void SetPendingQuest(FName InQuestId, const FText& Title);

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestAccepted OnQuestAccepted;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestDeclined OnQuestDeclined;

protected:
    /** Wire in WBP_QuestConfirm: Text Block showing the quest title. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UTextBlock> QuestTitleText;

    /** Wire in WBP_QuestConfirm: Accept button. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UButton> AcceptButton;

    /** Wire in WBP_QuestConfirm: Decline button. */
    UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
    TObjectPtr<UButton> DeclineButton;

private:
    /** Build the legible default tree when no designer layout exists. */
    void BuildDefaultTree();

    FName PendingQuestId;

    UFUNCTION()
    void NativeOnAccept();

    UFUNCTION()
    void NativeOnDecline();
};
