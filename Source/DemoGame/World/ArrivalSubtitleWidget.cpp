// File: ArrivalSubtitleWidget.cpp
// Module: DemoGame
// Purpose: UMG base widget that shows a location arrival subtitle for 3 s on tick advance.
// Net I/O: no

#include "ArrivalSubtitleWidget.h"
#include "NpcWorldSubsystem.h"
#include "LocationSubtitleData.h"
#include "Components/TextBlock.h"
#include "DemoGame.h"

void UArrivalSubtitleWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UNpcWorldSubsystem* WS = GetWorld()
        ? GetWorld()->GetSubsystem<UNpcWorldSubsystem>()
        : nullptr;
    if (WS)
    {
        WS->OnTickAdvanced.AddDynamic(this, &UArrivalSubtitleWidget::OnTickAdvanced);
    }
    else
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("UArrivalSubtitleWidget: NpcWorldSubsystem not found — subtitle won't fire."));
    }

    SetVisibility(ESlateVisibility::Hidden);
}

void UArrivalSubtitleWidget::NativeDestruct()
{
    if (UNpcWorldSubsystem* WS = GetWorld()
            ? GetWorld()->GetSubsystem<UNpcWorldSubsystem>()
            : nullptr)
    {
        WS->OnTickAdvanced.RemoveDynamic(this, &UArrivalSubtitleWidget::OnTickAdvanced);
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(HideTimer);
    }

    Super::NativeDestruct();
}

void UArrivalSubtitleWidget::OnTickAdvanced(FName NewLocationId, int32 /*TickCount*/)
{
    if (!SubtitleData)
    {
        return;
    }

    const FText* Found = SubtitleData->SubtitleByLocation.Find(NewLocationId);
    if (!Found || Found->IsEmpty())
    {
        return;
    }

    ShowSubtitle(*Found);
}

void UArrivalSubtitleWidget::ShowSubtitle(FText Text)
{
    if (SubtitleText)
    {
        SubtitleText->SetText(Text);
    }

    SetVisibility(ESlateVisibility::HitTestInvisible);

    if (FadeOutAnimation)
    {
        PlayAnimation(FadeOutAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
    }
    else
    {
        // No animation: just hide after the display duration.
        if (UWorld* World = GetWorld())
        {
            World->GetTimerManager().ClearTimer(HideTimer);
            World->GetTimerManager().SetTimer(
                HideTimer,
                FTimerDelegate::CreateUObject(this, &UArrivalSubtitleWidget::HideSubtitle),
                SubtitleDisplaySeconds,
                false);
        }
    }
}

void UArrivalSubtitleWidget::HideSubtitle()
{
    SetVisibility(ESlateVisibility::Hidden);
}
