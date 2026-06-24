// File: RelationshipMeterWidget.cpp
// Module: Game
// Purpose: Accumulated trust/fear/affection display; subscribes to manager relationship delegate.
// Net I/O: no

#include "RelationshipMeterWidget.h"
#include "DialogueManager.h"
#include "NpcActorBase.h"
#include "DemoGame.h"
#include "Components/TextBlock.h"

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
