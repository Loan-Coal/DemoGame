// File: QuestConfirmWidget.cpp
// Module: DemoGame
// Purpose: C++ base for quest accept/decline overlay (appears on NPC quest offer).
// Net I/O: no

#include "QuestConfirmWidget.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "DemoGame.h"

TSharedRef<SWidget> UQuestConfirmWidget::RebuildWidget()
{
    if (WidgetTree && !WidgetTree->RootWidget)
    {
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void UQuestConfirmWidget::BuildDefaultTree()
{
    UBorder* Root = DemoUi::MakeBackdrop(*WidgetTree, /*bDim*/true, HAlign_Center, VAlign_Center);
    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel);
    Root->SetContent(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    QuestTitleText = DemoUi::MakeText(*WidgetTree, FText::FromString(TEXT("New Quest")),
        DemoUi::FontTitle, DemoUi::TextPrimary, ETextJustify::Center, TEXT("QuestTitleText"));
    Box->AddChildToVerticalBox(QuestTitleText);

    UHorizontalBox* Buttons = WidgetTree->ConstructWidget<UHorizontalBox>();
    if (UVerticalBoxSlot* BtnRowSlot = Box->AddChildToVerticalBox(Buttons))
    {
        BtnRowSlot->SetPadding(FMargin(0.f, DemoUi::PadCard, 0.f, 0.f));
        BtnRowSlot->SetHorizontalAlignment(HAlign_Center);
    }

    UTextBlock* AcceptLabel = nullptr;
    UTextBlock* DeclineLabel = nullptr;
    AcceptButton = DemoUi::MakeButton(*WidgetTree, FText::FromString(TEXT("Accept")),
        AcceptLabel, TEXT("AcceptButton"));
    DeclineButton = DemoUi::MakeButton(*WidgetTree, FText::FromString(TEXT("Decline")),
        DeclineLabel, TEXT("DeclineButton"));

    for (UButton* Btn : { AcceptButton.Get(), DeclineButton.Get() })
    {
        if (UHorizontalBoxSlot* ItemSlot = Buttons->AddChildToHorizontalBox(Btn))
        {
            ItemSlot->SetPadding(FMargin(DemoUi::PadRow, 0.f));
        }
    }

    WidgetTree->RootWidget = Root;
}

void UQuestConfirmWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (AcceptButton)
    {
        AcceptButton->OnClicked.AddDynamic(this, &UQuestConfirmWidget::NativeOnAccept);
    }
    if (DeclineButton)
    {
        DeclineButton->OnClicked.AddDynamic(this, &UQuestConfirmWidget::NativeOnDecline);
    }
}

void UQuestConfirmWidget::SetPendingQuest(FName InQuestId, const FText& Title)
{
    PendingQuestId = InQuestId;
    if (QuestTitleText)
    {
        QuestTitleText->SetText(Title);
    }
}

void UQuestConfirmWidget::NativeOnAccept()
{
    UE_LOG(LogDemoGame, Log,
        TEXT("QuestConfirmWidget: player accepted QuestId=%s."), *PendingQuestId.ToString());
    OnQuestAccepted.Broadcast(PendingQuestId);
    RemoveFromParent();
}

void UQuestConfirmWidget::NativeOnDecline()
{
    UE_LOG(LogDemoGame, Log,
        TEXT("QuestConfirmWidget: player declined QuestId=%s."), *PendingQuestId.ToString());
    OnQuestDeclined.Broadcast(PendingQuestId);
    RemoveFromParent();
}
