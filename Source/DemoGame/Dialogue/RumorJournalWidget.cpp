// File: RumorJournalWidget.cpp
// Module: DemoGame
// Purpose: C++ base class for the Tab-key Rumor Journal UMG widget.
// Net I/O: no

#include "RumorJournalWidget.h"
#include "World/GossipCacheSubsystem.h"
#include "DemoGame.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

void URumorJournalWidget::NativeConstruct()
{
    Super::NativeConstruct();
    RefreshJournal();
}

TSharedRef<SWidget> URumorJournalWidget::RebuildWidget()
{
    if (WidgetTree && !WidgetTree->RootWidget)
    {
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void URumorJournalWidget::BuildDefaultTree()
{
    UBorder* Root = DemoUi::MakeBackdrop(*WidgetTree, /*bDim*/true, HAlign_Center, VAlign_Center);
    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel);
    Root->SetContent(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    UTextBlock* Header = DemoUi::MakeText(*WidgetTree, FText::FromString(TEXT("Rumor Journal")),
        DemoUi::FontTitle, DemoUi::TextAccent);
    Box->AddChildToVerticalBox(Header);

    ChainScrollBox = WidgetTree->ConstructWidget<UScrollBox>(UScrollBox::StaticClass(), TEXT("ChainScrollBox"));
    if (UVerticalBoxSlot* ScrollSlot = Box->AddChildToVerticalBox(ChainScrollBox))
    {
        ScrollSlot->SetPadding(FMargin(0.f, DemoUi::PadRow, 0.f, 0.f));
    }

    ChainContainer = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), TEXT("ChainContainer"));
    ChainScrollBox->AddChild(ChainContainer);

    WidgetTree->RootWidget = Root;
}

UWidget* URumorJournalWidget::MakeChainCard(const FGossipEntry& Entry)
{
    UBorder* CardPanel = DemoUi::MakePanel(*WidgetTree, DemoUi::PanelHeader, DemoUi::PadRow);
    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    CardPanel->SetContent(Box);

    UHorizontalBox* TopLine = WidgetTree->ConstructWidget<UHorizontalBox>();
    UTextBlock* NameText = DemoUi::MakeText(*WidgetTree,
        FText::FromName(Entry.SourceNpcId), DemoUi::FontBody, DemoUi::TextPrimary);
    UTextBlock* Badge = DemoUi::MakeText(*WidgetTree,
        GetDistortionLabel(Entry.HopCount), DemoUi::FontSmall, DemoUi::TextAccent, ETextJustify::Right);
    if (UHorizontalBoxSlot* NameSlot = TopLine->AddChildToHorizontalBox(NameText))
    {
        NameSlot->SetPadding(FMargin(0.f, 0.f, DemoUi::PadRow, 0.f));
    }
    TopLine->AddChildToHorizontalBox(Badge);
    Box->AddChildToVerticalBox(TopLine);

    UTextBlock* Body = DemoUi::MakeText(*WidgetTree,
        Entry.DistortionText, DemoUi::FontSmall, DemoUi::TextMuted);
    Box->AddChildToVerticalBox(Body);
    return CardPanel;
}

void URumorJournalWidget::RefreshJournal()
{
    const UWorld* W = GetWorld();
    UGossipCacheSubsystem* Cache = W ? W->GetSubsystem<UGossipCacheSubsystem>() : nullptr;
    if (!Cache)
    {
        UE_LOG(LogDemoGame, Warning, TEXT("RumorJournalWidget: GossipCacheSubsystem unavailable."));
        return;
    }

    const TArray<FGossipEntry> All =
        Cache->GetChainForEvent(GossipEventId::NorthernWarBegins);
    OnJournalRefreshed(All);
}

void URumorJournalWidget::OnJournalRefreshed_Implementation(const TArray<FGossipEntry>& AllEntries)
{
    // Default C++ population: one card per visible hop. An authored WBP subclass may override.
    if (!ChainContainer)
    {
        return;
    }

    ChainContainer->ClearChildren();

    int32 VisibleCount = 0;
    for (const FGossipEntry& Entry : AllEntries)
    {
        if (!Entry.bPlayerSpokeToNpc)
        {
            continue;   // journal hides hops the player hasn't heard firsthand yet
        }
        if (UVerticalBoxSlot* ItemSlot = ChainContainer->AddChildToVerticalBox(MakeChainCard(Entry)))
        {
            ItemSlot->SetPadding(FMargin(0.f, 0.f, 0.f, DemoUi::PadRow));
        }
        ++VisibleCount;
    }

    if (VisibleCount == 0)
    {
        UTextBlock* Empty = DemoUi::MakeText(*WidgetTree,
            FText::FromString(TEXT("No rumors yet. Talk to the townsfolk.")),
            DemoUi::FontBody, DemoUi::TextMuted);
        ChainContainer->AddChildToVerticalBox(Empty);
    }
}

FText URumorJournalWidget::GetDistortionLabel(int32 HopCount)
{
    if (HopCount == 0) return FText::FromString(TEXT("Firsthand"));
    if (HopCount == 1) return FText::FromString(TEXT("Rumor"));
    return FText::FromString(TEXT("Distorted"));
}
