// File: NpcQuestService.h
// Module: NpcEngineClient
// Purpose: ISP boundary — async quest lifecycle service, separate from INpcDialogueService. DEC-026.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NpcQuestTypes.h"
#include "NpcDialogueService.h"   // FOnNpcEngineError (shared error delegate)
#include "NpcQuestService.generated.h"

UINTERFACE(MinimalAPI, NotBlueprintable)
class UNpcQuestService : public UInterface
{
    GENERATED_BODY()
};

/**
 * Async quest lifecycle service.
 *
 * ISP split from INpcDialogueService (DEC-026): quest-aware consumers depend on this
 * interface; dialogue-only consumers depend only on INpcDialogueService.
 *
 * All methods are non-blocking: return immediately; callback fires on the game thread.
 * On non-2xx or envelope parse failure: UE_LOG(LogNpcEngine, Error) + OnResult(false).
 * Never crashes on engine errors.
 *
 * Endpoint shapes from DEC-027 (pending live verification in Phase 5 editor session).
 */
class INpcQuestService
{
    GENERATED_BODY()

public:
    /** POST /v1/quest/offer — register quest + objectives in the engine. */
    virtual void QuestOffer(
        const FQuestOfferRequest& Request,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /** POST /v1/quest/accept — player formally accepts an offered quest. */
    virtual void QuestAccept(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /** POST /v1/quest/objective — record progress on a single objective. */
    virtual void QuestObjective(
        const FQuestObjectiveRequest& Request,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /** POST /v1/quest/evaluate — check if all objectives are satisfied. */
    virtual void QuestEvaluate(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /** POST /v1/quest/reward — deliver reward to player. */
    virtual void QuestReward(
        const FString& QuestId,
        const FString& PlayerId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /**
     * POST /v1/quest/{quest_id}/choose — faction fork branch.
     * QuestId goes in the URL path; PlayerId + ChoiceId go in the JSON body.
     */
    virtual void QuestChoose(
        const FString& QuestId,
        const FString& PlayerId,
        const FString& ChoiceId,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError OnError) = 0;
};
