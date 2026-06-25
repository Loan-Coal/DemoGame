// File: NoticeBoard.h
// Module: DemoGame
// Purpose: Actor that shows authored rumor-tier text based on world tick count.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NoticeBoard.generated.h"

/**
 * Notice board actor placed in L_MarketSquare and L_GuardBarracks.
 *
 * Listens to UNpcWorldSubsystem::OnTickAdvanced. Advances the displayed tier when
 * TickCount crosses a authored threshold. Three tiers: pre-war silence / rumors spreading /
 * distorted widely.
 *
 * Authored properties (set in editor on BP_NoticeBoard subclass):
 *   - RumorTiers   (array of 3 FText)
 *   - TierTickThresholds (array of 3 int32, e.g. [0, 2, 4])
 *
 * On E-examine the player gets the current tier text; exact UI implementation in editor session.
 */
UCLASS()
class DEMOGAME_API ANoticeBoard : public AActor
{
    GENERATED_BODY()

public:
    ANoticeBoard();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    /** The authored tier text displayed at each threshold. Index 0 = pre-war silence. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NoticeBoard")
    TArray<FText> RumorTiers;

    /**
     * Minimum tick count required to display each tier. Must be the same length as RumorTiers.
     * Default: [0, 2, 4] — constants avoid magic numbers in C++ (see .cpp).
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NoticeBoard")
    TArray<int32> TierTickThresholds;

    /** Returns the display text for the current world tick count (or empty if RumorTiers is empty). */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NoticeBoard")
    FText GetCurrentTierText() const;

    /** Returns the current tier index [0, RumorTiers.Num()-1]. */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "NoticeBoard")
    int32 GetCurrentTierIndex() const;

private:
    UFUNCTION()
    void OnTickAdvanced(FName NewLocationId, int32 TickCount);

    int32 CurrentTickCount = 0;
};
