// File: FactionForkWidget.cpp
// Module: DemoGame
// Purpose: C++ base for the binary faction fork choice overlay.
// Net I/O: no

#include "FactionForkWidget.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "DemoGame.h"

TSharedRef<SWidget> UFactionForkWidget::RebuildWidget()
{
    if (WidgetTree && !WidgetTree->RootWidget)
    {
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void UFactionForkWidget::BuildDefaultTree()
{
    UBorder* Root = DemoUi::MakeBackdrop(*WidgetTree, /*bDim*/true, HAlign_Center, VAlign_Center);
    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel);
    Root->SetContent(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    UTextBlock* Title = DemoUi::MakeText(*WidgetTree,
        FText::FromString(TEXT("Choose a side")), DemoUi::FontTitle,
        DemoUi::TextPrimary, ETextJustify::Center);
    Box->AddChildToVerticalBox(Title);

    UTextBlock* LabelA = nullptr;
    UTextBlock* LabelB = nullptr;
    ChoiceAButton = DemoUi::MakeButton(*WidgetTree, FText::FromString(TEXT("Option A")),
        LabelA, TEXT("ChoiceAButton"), TEXT("ChoiceALabel"));
    ChoiceBButton = DemoUi::MakeButton(*WidgetTree, FText::FromString(TEXT("Option B")),
        LabelB, TEXT("ChoiceBButton"), TEXT("ChoiceBLabel"));
    ChoiceALabel = LabelA;
    ChoiceBLabel = LabelB;

    for (UButton* Btn : { ChoiceAButton.Get(), ChoiceBButton.Get() })
    {
        if (UVerticalBoxSlot* ItemSlot = Box->AddChildToVerticalBox(Btn))
        {
            ItemSlot->SetPadding(FMargin(0.f, DemoUi::PadRow, 0.f, 0.f));
            ItemSlot->SetHorizontalAlignment(HAlign_Fill);
        }
    }

    WidgetTree->RootWidget = Root;
}

void UFactionForkWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ChoiceAButton)
    {
        ChoiceAButton->OnClicked.AddDynamic(this, &UFactionForkWidget::OnChoiceAClicked);
    }
    if (ChoiceBButton)
    {
        ChoiceBButton->OnClicked.AddDynamic(this, &UFactionForkWidget::OnChoiceBClicked);
    }
}

void UFactionForkWidget::SetForkContext(
    FName InQuestId,
    FName InChoiceAId, const FText& LabelA,
    FName InChoiceBId, const FText& LabelB)
{
    PendingQuestId = InQuestId;
    ChoiceAId      = InChoiceAId;
    ChoiceBId      = InChoiceBId;

    if (ChoiceALabel) ChoiceALabel->SetText(LabelA);
    if (ChoiceBLabel) ChoiceBLabel->SetText(LabelB);
}

void UFactionForkWidget::OnChoiceAClicked()
{
    UE_LOG(LogDemoGame, Log,
        TEXT("FactionForkWidget: choice A QuestId=%s ChoiceId=%s"),
        *PendingQuestId.ToString(), *ChoiceAId.ToString());
    OnForkChoiceMade.Broadcast(PendingQuestId, ChoiceAId);
    RemoveFromParent();
}

void UFactionForkWidget::OnChoiceBClicked()
{
    UE_LOG(LogDemoGame, Log,
        TEXT("FactionForkWidget: choice B QuestId=%s ChoiceId=%s"),
        *PendingQuestId.ToString(), *ChoiceBId.ToString());
    OnForkChoiceMade.Broadcast(PendingQuestId, ChoiceBId);
    RemoveFromParent();
}
