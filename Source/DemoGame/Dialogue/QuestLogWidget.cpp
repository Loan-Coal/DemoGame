// File: QuestLogWidget.cpp
// Module: DemoGame
// Purpose: C++ base for WBP_QuestLog — displays active quests and step checkboxes.
// Net I/O: no

#include "QuestLogWidget.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "DemoGame.h"

TSharedRef<SWidget> UQuestLogWidget::RebuildWidget()
{
    if (WidgetTree && !WidgetTree->RootWidget)
    {
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void UQuestLogWidget::BuildDefaultTree()
{
    UBorder* Root = DemoUi::MakeBackdrop(*WidgetTree, /*bDim*/false, HAlign_Right, VAlign_Top);
    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel, DemoUi::PadRow);
    Root->SetContent(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    UTextBlock* Header = DemoUi::MakeText(*WidgetTree, FText::FromString(TEXT("Quests")),
        DemoUi::FontButton, DemoUi::TextAccent);
    Box->AddChildToVerticalBox(Header);

    QuestList = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("QuestList"));
    if (UVerticalBoxSlot* ListSlot = Box->AddChildToVerticalBox(QuestList))
    {
        ListSlot->SetPadding(FMargin(0.f, DemoUi::PadRow, 0.f, 0.f));
    }

    WidgetTree->RootWidget = Root;
}

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
        const FString Label = Step.bCompleted
            ? FString::Printf(TEXT("[DONE] %s"), *Step.QuestId)
            : FString::Printf(TEXT("[    ] %s"), *Step.QuestId);
        UTextBlock* Row = DemoUi::MakeText(*WidgetTree, FText::FromString(Label),
            DemoUi::FontBody, Step.bCompleted ? DemoUi::TextMuted : DemoUi::TextPrimary);
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
