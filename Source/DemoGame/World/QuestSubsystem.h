// File: QuestSubsystem.h
// Module: DemoGame
// Purpose: Tracks active quests; routes lifecycle calls through INpcQuestService.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcQuestService.h"
#include "QuestSubsystem.generated.h"

// ── Quest ID constants (DEC-028) ─────────────────────────────────────────────
namespace QuestId
{
    inline const FName FindWineMerchant   = TEXT("find_wine_merchant");
    inline const FName DeliverAmulet      = TEXT("deliver_amulet");
    inline const FName AldricConfession   = TEXT("aldric_confession");
    inline const FName PatrolDuty         = TEXT("patrol_duty");
    inline const FName CaptainReport      = TEXT("captain_report");
    inline const FName MissingGoods       = TEXT("missing_goods");
    inline const FName FenceConfrontation = TEXT("fence_confrontation");
}

/** Persisted state for one quest step; used by UNpcSaveGame (DEC-025). */
USTRUCT(BlueprintType)
struct DEMOGAME_API FQuestStepState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Quest")
    FString QuestId;

    UPROPERTY(BlueprintReadOnly, Category = "Quest")
    FString StepId;

    UPROPERTY(BlueprintReadOnly, Category = "Quest")
    bool bCompleted = false;
};

/** Fires when a quest becomes active (offer + accept succeeded). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestActivated, FName, QuestId);

/** Fires when a quest step completes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStepCompleted, FName, QuestId, FName, StepId);

/**
 * World subsystem that tracks active quests and routes lifecycle calls through INpcQuestService.
 * No HTTP, no JSON, no USTRUCTs defined here — all network I/O is in NpcEngineClient.
 */
UCLASS()
class DEMOGAME_API UQuestSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * Activate a quest: calls QuestOffer + QuestAccept through the service interface,
     * adds to active list, and broadcasts OnQuestActivated on success.
     */
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void ActivateQuest(FName QuestId);

    /**
     * Complete a single step: calls QuestObjective + QuestEvaluate through the service.
     * If quest complete: calls QuestReward; checks chain link; broadcasts OnStepCompleted.
     * Triggers save on completion.
     */
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void CompleteStep(FName QuestId, FName StepId);

    /** Inject quest service for test DI. */
    void SetQuestService(TScriptInterface<INpcQuestService> InService);

    /** Snapshot of active steps (read by NpcSaveGame). */
    const TArray<FQuestStepState>& GetActiveSteps() const { return ActiveSteps; }

    // ── Delegates ─────────────────────────────────────────────────────────────

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnQuestActivated OnQuestActivated;

    UPROPERTY(BlueprintAssignable, Category = "Quest")
    FOnStepCompleted OnStepCompleted;

private:
    INpcQuestService* ResolveQuestService();

    UPROPERTY()
    TScriptInterface<INpcQuestService> QuestService;

    TArray<FQuestStepState> ActiveSteps;
};
