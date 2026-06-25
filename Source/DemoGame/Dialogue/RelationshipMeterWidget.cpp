// File: RelationshipMeterWidget.cpp
// Module: Game
// Purpose: Accumulated trust/fear/affection display; subscribes to manager relationship delegate.
// Net I/O: no

#include "RelationshipMeterWidget.h"
#include "DialogueManager.h"
#include "NpcActorBase.h"
#include "DemoGame.h"
#include "UiStyle.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"

TSharedRef<SWidget> URelationshipMeterWidget::RebuildWidget()
{
    if (WidgetTree && !WidgetTree->RootWidget)
    {
        BuildDefaultTree();
    }
    return Super::RebuildWidget();
}

void URelationshipMeterWidget::BuildDefaultTree()
{
    UBorder* Root = DemoUi::MakeBackdrop(*WidgetTree, /*bDim*/false, HAlign_Left, VAlign_Top);
    UBorder* Card = DemoUi::MakePanel(*WidgetTree, DemoUi::Panel, DemoUi::PadRow);
    Root->SetContent(Card);

    UVerticalBox* Box = WidgetTree->ConstructWidget<UVerticalBox>();
    Card->SetContent(Box);

    auto MakeRow = [&](const FString& Caption, FName ValueName) -> UTextBlock*
    {
        UHorizontalBox* Row = WidgetTree->ConstructWidget<UHorizontalBox>();
        UTextBlock* Label = DemoUi::MakeText(*WidgetTree, FText::FromString(Caption),
            DemoUi::FontSmall, DemoUi::TextMuted);
        UTextBlock* Value = DemoUi::MakeText(*WidgetTree, FText::FromString(TEXT("+0")),
            DemoUi::FontSmall, DemoUi::TextAccent, ETextJustify::Right, ValueName);
        if (UHorizontalBoxSlot* LabelSlot = Row->AddChildToHorizontalBox(Label))
        {
            LabelSlot->SetPadding(FMargin(0.f, 0.f, DemoUi::PadRow, 0.f));
        }
        Row->AddChildToHorizontalBox(Value);
        Box->AddChildToVerticalBox(Row);
        return Value;
    };

    TrustText     = MakeRow(TEXT("Trust"),     TEXT("TrustText"));
    FearText      = MakeRow(TEXT("Fear"),      TEXT("FearText"));
    AffectionText = MakeRow(TEXT("Affection"), TEXT("AffectionText"));

    WidgetTree->RootWidget = Root;
}

void URelationshipMeterWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;

    if (!DM)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("RelationshipMeterWidget: DialogueManagerSubsystem not found."));
        return;
    }

    DM->OnRelationshipChanged.AddDynamic(this, &URelationshipMeterWidget::OnRelationshipChanged);
    DM->OnDialogueBegun.AddDynamic(this, &URelationshipMeterWidget::OnDialogueBegun);
}

void URelationshipMeterWidget::NativeDestruct()
{
    UDialogueManagerSubsystem* DM = GetWorld()
        ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;

    if (DM)
    {
        DM->OnRelationshipChanged.RemoveDynamic(this, &URelationshipMeterWidget::OnRelationshipChanged);
        DM->OnDialogueBegun.RemoveDynamic(this, &URelationshipMeterWidget::OnDialogueBegun);
    }

    Super::NativeDestruct();
}

void URelationshipMeterWidget::ResetSession()
{
    SessionTrust     = 0;
    SessionFear      = 0;
    SessionAffection = 0;
    UpdateDisplay();
}

// ── Private ───────────────────────────────────────────────────────────────────

void URelationshipMeterWidget::UpdateDisplay()
{
    auto FormatDelta = [](int32 Val) -> FText
    {
        return FText::FromString(Val >= 0
            ? FString::Printf(TEXT("+%d"), Val)
            : FString::Printf(TEXT("%d"), Val));
    };

    if (TrustText)      { TrustText->SetText(FormatDelta(SessionTrust)); }
    if (FearText)       { FearText->SetText(FormatDelta(SessionFear)); }
    if (AffectionText)  { AffectionText->SetText(FormatDelta(SessionAffection)); }
}

void URelationshipMeterWidget::OnRelationshipChanged(FName /*NpcId*/, FNpcRelationDeltas Deltas)
{
    SessionTrust     += Deltas.Trust;
    SessionFear      += Deltas.Fear;
    SessionAffection += Deltas.Affection;

    UpdateDisplay();
    OnRelationshipUpdated(SessionTrust, SessionFear, SessionAffection);
}

void URelationshipMeterWidget::OnDialogueBegun(ANpcActorBase* /*Npc*/)
{
    ResetSession();
}

void URelationshipMeterWidget::OnRelationshipUpdated_Implementation(
    int32 /*Trust*/, int32 /*Fear*/, int32 /*Affection*/)
{
    // Default: no-op. Blueprint subclass can override for animation.
}
