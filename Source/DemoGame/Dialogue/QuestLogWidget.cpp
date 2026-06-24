// File: QuestLogWidget.cpp
// Module: DemoGame
// Purpose: C++ base for WBP_QuestLog — displays active quests and step checkboxes.
// Net I/O: no

#include "QuestLogWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "DemoGame.h"

void UQuestLogWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UQuestSubsystem* QS = GetWorld() ? GetWorld()->GetSubsystem<UQuestSubsystem>() : nullptr;
    if (QS)
    {
        QS->OnQuestActivated.AddDynamic(this, &UQuestLogWidget::OnQuestActivated);
        QS->OnStepCompleted.AddDynamic(this,  &UQuestLogWidget::OnStepCompleted);
    }

    RefreshQuestList();
}

void UQuestLogWidget::NativeDestruct()
{
    UQuestSubsystem* QS = GetWorld() ? GetWorld()->GetSubsystem<UQuestSubsystem>() : nullptr;
    if (QS)
    {
        QS->OnQuestActivated.RemoveDynamic(this, &UQuestLogWidget::OnQuestActivated);
        QS->OnStepCompleted.RemoveDynamic(this,  &UQuestLogWidget::OnStepCompleted);
    }
    Super::NativeDestruct();
}

void UQuestLogWidget::RefreshQuestList_Implementation()
{
    // C++ default: add one text entry per active step (quest title).
    // Blueprint subclass replaces this with a proper row widget.
    if (!QuestList) return;

    QuestList->ClearChildren();

    UQuestSubsystem* QS = GetWorld() ? GetWorld()->GetSubsystem<UQuestSubsystem>() : nullptr;
    if (!QS) return;

    for (const FQuestStepState& Step : QS->GetActiveSteps())
    {
        UTextBlock* Row = NewObject<UTextBlock>(this);
        const FString Label = Step.bCompleted
            ? FString::Printf(TEXT("[DONE] %s"), *Step.QuestId)
            : FString::Printf(TEXT("[    ] %s"), *Step.QuestId);
        Row->SetText(FText::FromString(Label));
        QuestList->AddChildToVerticalBox(Row);
    }
}

void UQuestLogWidget::OnQuestActivated(FName /*QuestId*/)
{
    RefreshQuestList();
}

void UQuestLogWidget::OnStepCompleted(FName /*QuestId*/, FName /*StepId*/)
{
    RefreshQuestList();
}
