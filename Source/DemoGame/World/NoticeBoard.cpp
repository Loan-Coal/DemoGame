// File: NoticeBoard.cpp
// Module: DemoGame
// Purpose: Actor that shows authored rumor-tier text based on world tick count.
// Net I/O: no

#include "NoticeBoard.h"
#include "NpcWorldSubsystem.h"
#include "DemoGame.h"

// Default tick thresholds for the three rumor tiers (pre-war / spreading / distorted).
// These are the DEFAULT values — overridden per BP_NoticeBoard instance in the editor.
namespace NoticeBoardDefaults
{
    static constexpr int32 Tier1MinTick = 0;
    static constexpr int32 Tier2MinTick = 2;
    static constexpr int32 Tier3MinTick = 4;
}

ANoticeBoard::ANoticeBoard()
{
    PrimaryActorTick.bCanEverTick = false;

    // Default tier thresholds — authored via editor on each BP_NoticeBoard instance.
    TierTickThresholds = {
        NoticeBoardDefaults::Tier1MinTick,
        NoticeBoardDefaults::Tier2MinTick,
        NoticeBoardDefaults::Tier3MinTick
    };
}

void ANoticeBoard::BeginPlay()
{
    Super::BeginPlay();

    if (RumorTiers.Num() == 0)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("ANoticeBoard: RumorTiers is empty — assign authored text in BP_NoticeBoard."));
    }

    if (UNpcWorldSubsystem* World = GetWorld()->GetSubsystem<UNpcWorldSubsystem>())
    {
        CurrentTickCount = World->GetTickCount();
        World->OnTickAdvanced.AddDynamic(this, &ANoticeBoard::OnTickAdvanced);
    }
}

void ANoticeBoard::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UNpcWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UNpcWorldSubsystem>() : nullptr)
    {
        World->OnTickAdvanced.RemoveDynamic(this, &ANoticeBoard::OnTickAdvanced);
    }
    Super::EndPlay(EndPlayReason);
}

void ANoticeBoard::OnTickAdvanced(FName /*NewLocationId*/, int32 TickCount)
{
    CurrentTickCount = TickCount;
}

int32 ANoticeBoard::GetCurrentTierIndex() const
{
    if (TierTickThresholds.Num() == 0 || RumorTiers.Num() == 0) return 0;

    int32 BestTier = 0;
    const int32 MaxTiers = FMath::Min(TierTickThresholds.Num(), RumorTiers.Num());
    for (int32 i = 0; i < MaxTiers; ++i)
    {
        if (CurrentTickCount >= TierTickThresholds[i])
        {
            BestTier = i;
        }
    }
    return BestTier;
}

FText ANoticeBoard::GetCurrentTierText() const
{
    if (RumorTiers.Num() == 0) return FText::GetEmpty();
    const int32 Idx = GetCurrentTierIndex();
    return RumorTiers.IsValidIndex(Idx) ? RumorTiers[Idx] : FText::GetEmpty();
}
