// File: NpcWorldSeeder.h
// Module: NpcEngineClient
// Purpose: Seeds the full demo world from Seed/DemoWorld_v1.json with idempotency checks.
// Net I/O: yes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcWorldSeeder.generated.h"

/**
 * HTTP executor signature used by UNpcWorldSeeder.
 * Verb: "GET" or "POST". Url: fully-qualified URL. Body: request body (empty string for GET).
 * OnResult fires on the game thread in production (async FHttpModule) and synchronously in tests
 * (mock injection), so test lambdas can capture local variables safely.
 */
using FNpcSeederHttpExec = TFunction<void(
    const FString& /*Verb*/,
    const FString& /*Url*/,
    const FString& /*Body*/,
    TFunction<void(int32 /*HttpStatus*/, const FString& /*ResponseBody*/)> /*OnResult*/)>;

/**
 * World seeder for DemoGame.
 *
 * Reads Seed/DemoWorld_v1.json and upserts every node and edge against the NPC Engine
 * REST graph endpoints. Each node upsert is preceded by a CheckNodeExists GET; if the node
 * already exists the upsert is skipped and the id is logged as "Skipped". Any non-2xx response
 * halts the seeder and fires OnError — unlike UNpcEngineSeedClient which continues on failure.
 *
 * Seed order (dependency-respecting):
 *   Locations → Factions → Characters → Events (pre-edge nodes)
 *   → Edges
 *   → Quests (post-edge nodes)
 *
 * Does NOT: parse dialogue responses, manage NPC state, or perform world-clock ticks.
 * Dependencies injected: HTTP executor (real FHttpModule by default; swappable for tests via
 *   SetHttpExecutorForTesting).
 */
UCLASS()
class NPCENGINECLIENT_API UNpcWorldSeeder : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Load Seed/DemoWorld_v1.json and replay all nodes + edges with idempotency checks.
     * Halts and fires OnError on the first non-2xx response; does not continue on failure.
     * Non-blocking: returns immediately; callbacks fire on the game thread.
     */
    void SeedWorld(
        TFunction<void()>          OnComplete,
        TFunction<void(const FString& /*Error*/)> OnError);

    /**
     * Seed from an in-memory JSON string — same logic as SeedWorld without file I/O.
     * SeedWorld() loads the file and delegates here.  Also used directly by Automation Specs.
     */
    void SeedFromJsonString(
        const FString& JsonContent,
        TFunction<void()>          OnComplete,
        TFunction<void(const FString& /*Error*/)> OnError);

    /** Replace the HTTP executor. Call this before SeedWorld/SeedFromJsonString in tests. */
    void SetHttpExecutorForTesting(FNpcSeederHttpExec Exec);

private:
    struct FNodeTask { FString NodeType; FString NodeId; FString PropertiesJson; };
    struct FEdgeTask { FString EdgeType; FString SrcId; FString DstId; FString PropertiesJson; };

    FNpcSeederHttpExec HttpExec;
    FString CachedBaseUrl;  // set once in EnsureHttpExec; empty string signals invalid config

    void EnsureHttpExec();
    FString BuildUrl(const FString& Path) const;

    bool BuildTasksFromJson(
        const FString& Json,
        TArray<FNodeTask>& OutPreEdgeNodes,
        TArray<FEdgeTask>& OutEdges,
        TArray<FNodeTask>& OutPostEdgeNodes,
        FString& OutError);

    void ProcessNodes(
        TArray<FNodeTask> Tasks, int32 Index,
        TArray<FEdgeTask> Edges, TArray<FNodeTask> PostEdgeNodes,
        TFunction<void()> OnDone, TFunction<void(const FString&)> OnError);

    void ProcessEdges(
        TArray<FEdgeTask> Tasks, int32 Index,
        TArray<FNodeTask> PostEdgeNodes,
        TFunction<void()> OnDone, TFunction<void(const FString&)> OnError);

    void CheckNodeExists(
        const FString& NodeType, const FString& NodeId,
        TFunction<void(bool /*bExists*/)> OnFound,
        TFunction<void(const FString& /*Error*/)> OnError);

    void PostUpsertNode(
        const FString& NodeType, const FString& PropertiesJson,
        TFunction<void(bool /*bOk*/)> OnResult);

    void PostUpsertEdge(
        const FEdgeTask& Task,
        TFunction<void(bool /*bOk*/)> OnResult);
};
