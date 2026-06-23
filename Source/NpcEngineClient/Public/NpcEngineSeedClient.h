#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcEngineSeedClient.generated.h"

/**
 * Replays the game-owned seed file (Seed/slice1_tavern.json) against the engine
 * via REST: POST /v1/graph/nodes/{type} and POST /v1/graph/edges/{type}.
 *
 * Both endpoints are idempotent (engine uses MERGE semantics), so replaying is safe
 * any number of times and serves as a "ensure world exists" check on connect.
 *
 * Seed order (from the seed file "seed_order" array):
 *   locations → factions → characters → edges
 *
 * Usage:
 *   SeedClient->ReplaySlice1Seed([]{ UE_LOG(..., "Seed complete"); }, [](err){ ... });
 */
UCLASS()
class NPCENGINECLIENT_API UNpcEngineSeedClient : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Load Seed/slice1_tavern.json and replay all nodes then edges sequentially.
     * OnComplete fires when the last operation finishes (or on the first error).
     */
    void ReplaySlice1Seed(
        TFunction<void()> OnComplete,
        TFunction<void(const FString& /*Error*/)> OnError);

    /** Upsert a single node. node_type e.g. "Character", "Location". */
    void UpsertNode(
        const FString& NodeType,
        const FString& PropertiesJson,
        TFunction<void(bool /*bOk*/)> OnResult);

    /** Upsert a single edge. Both endpoint nodes must already exist. */
    void UpsertEdge(
        const FString& EdgeType,
        const FString& SrcId,
        const FString& DstId,
        const FString& PropertiesJson,
        TFunction<void(bool /*bOk*/)> OnResult);

private:
    struct FSeedOp
    {
        FString Endpoint;    // e.g. "/v1/graph/nodes/Character"
        FString Body;        // JSON body
    };

    void BuildOperationQueue(const TSharedPtr<FJsonObject>& SeedRoot, TArray<FSeedOp>& OutOps);
    void ProcessNextOp(
        TArray<FSeedOp> Ops,
        int32 Index,
        TFunction<void()> OnComplete,
        TFunction<void(const FString&)> OnError);

    FString BuildUrl(const FString& Path) const;
    void PostJson(
        const FString& Url,
        const FString& Body,
        TFunction<void(bool /*bOk*/, const FString& /*ResponseBody*/)> OnResult);
};
