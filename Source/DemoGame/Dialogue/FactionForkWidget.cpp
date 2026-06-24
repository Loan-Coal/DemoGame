// File: FactionForkWidget.cpp
// Module: DemoGame
// Purpose: C++ base for the binary faction fork choice overlay.
// Net I/O: no

#include "FactionForkWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DemoGame.h"

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
