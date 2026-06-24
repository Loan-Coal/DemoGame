// File: NpcQuestTypes.h
// Module: NpcEngineClient
// Purpose: Request USTRUCTs for quest lifecycle endpoints (POST /v1/quest/*). DEC-027.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "NpcQuestTypes.generated.h"

/** A single quest objective sent in the POST /v1/quest/offer body. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FQuestObjectiveData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="objective_id"))
    FString ObjectiveId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="description"))
    FString Description;

    /** Engine default is 1; supply only when a step requires multiple actions. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="required_progress"))
    int32 RequiredProgress = 1;
};

/** Body for POST /v1/quest/offer — registers a quest with its objectives in the engine. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FQuestOfferRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="quest_id"))
    FString QuestId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="player_id"))
    FString PlayerId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="title"))
    FString Title;

    /** At least one objective required. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="objectives"))
    TArray<FQuestObjectiveData> Objectives;
};

/** Body for POST /v1/quest/objective — records progress on a single objective. */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FQuestObjectiveRequest
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="quest_id"))
    FString QuestId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="player_id"))
    FString PlayerId;

    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="objective_id"))
    FString ObjectiveId;

    /** Increment by 1 for a single completion event. */
    UPROPERTY(BlueprintReadWrite, Category = "NpcEngine", meta=(JsonName="progress_delta"))
    int32 ProgressDelta = 1;
};
