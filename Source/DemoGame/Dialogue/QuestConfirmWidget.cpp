// File: QuestConfirmWidget.cpp
// Module: DemoGame
// Purpose: C++ base for quest accept/decline overlay (appears on NPC quest offer).
// Net I/O: no

#include "QuestConfirmWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DemoGame.h"

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
