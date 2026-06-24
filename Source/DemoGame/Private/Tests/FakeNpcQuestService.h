// File: FakeNpcQuestService.h
// Module: DemoGame
// Purpose: Test double implementing INpcQuestService — synchronous, scriptable success/error.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcQuestService.h"
#include "NpcQuestTypes.h"
#include "FakeNpcQuestService.generated.h"

/**
 * In-memory fake of INpcQuestService for QuestSubsystem specs.
 * All callbacks fire SYNCHRONOUSLY so tests are fully deterministic.
 * LSP: failure path (bShouldSucceed=false) fires OnError then OnResult(false),
 * matching the real client's contract (never silently succeed on non-2xx).
 */
UCLASS()
class UFakeNpcQuestService : public UObject, public INpcQuestService
{
    GENERATED_BODY()

public:
    // ── Test knobs ────────────────────────────────────────────────────────────

    bool    bShouldSucceed      = true;
    FString CannedError         = TEXT("fake quest error");

    // Captured state.
    FQuestOfferRequest      LastOfferRequest;
    FQuestObjectiveRequest  LastObjectiveRequest;
    FString                 LastAcceptQuestId;
    FString                 LastEvaluateQuestId;
    FString                 LastRewardQuestId;
    FString                 LastChooseQuestId;
    FString                 LastChoiceId;
    int32                   QuestOfferCallCount    = 0;
    int32                   QuestAcceptCallCount   = 0;
    int32                   QuestObjectiveCallCount = 0;
    int32                   QuestEvaluateCallCount = 0;
    int32                   QuestRewardCallCount   = 0;
    int32                   QuestChooseCallCount   = 0;

    // ── INpcQuestService ──────────────────────────────────────────────────────

    virtual void QuestOffer(
        const FQuestOfferRequest& Request,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastOfferRequest = Request;
        ++QuestOfferCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }

    virtual void QuestAccept(
        const FString& QuestId,
        const FString& /*PlayerId*/,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastAcceptQuestId = QuestId;
        ++QuestAcceptCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }

    virtual void QuestObjective(
        const FQuestObjectiveRequest& Request,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastObjectiveRequest = Request;
        ++QuestObjectiveCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }

    virtual void QuestEvaluate(
        const FString& QuestId,
        const FString& /*PlayerId*/,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastEvaluateQuestId = QuestId;
        ++QuestEvaluateCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }

    virtual void QuestReward(
        const FString& QuestId,
        const FString& /*PlayerId*/,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastRewardQuestId = QuestId;
        ++QuestRewardCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }

    virtual void QuestChoose(
        const FString& QuestId,
        const FString& /*PlayerId*/,
        const FString& ChoiceId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) override
    {
        LastChooseQuestId = QuestId;
        LastChoiceId      = ChoiceId;
        ++QuestChooseCallCount;
        if (bShouldSucceed) { OnResult(true); }
        else { OnError.ExecuteIfBound(CannedError); OnResult(false); }
    }
};
