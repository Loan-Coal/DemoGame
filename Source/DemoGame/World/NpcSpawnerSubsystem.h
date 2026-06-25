// File: NpcSpawnerSubsystem.h
// Module: Game
// Purpose: Spawns the slice NPCs and notice boards from a C++ table at begin-play (no manual placement).
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcSpawnerSubsystem.generated.h"

class ANpcActorBase;

/**
 * One NPC's spawn record. Identity (snake_case npc_id) matches the engine seed; Offset is relative
 * to the player start so NPCs are always near the player in whatever level is loaded.
 */
USTRUCT()
struct FNpcSpawnRecord
{
    GENERATED_BODY()

    FName NpcId;
    FString DisplayName;
    FString LocationId;
    FVector Offset = FVector::ZeroVector;
};

/**
 * UNpcSpawnerSubsystem — spawns all slice NPCs (greybox cubes with name labels) and the notice
 * boards at world begin-play, so the player can walk up and talk to them with zero editor work.
 *
 * Identity, display name, location id, and spawn offset come from a C++ table; positions are
 * relative to the level's PlayerStart (falls back to world origin). Replaced/extended by data-driven
 * seed spawning in a later slice. Only runs in real game worlds (PIE / packaged), never editor preview.
 */
UCLASS()
class DEMOGAME_API UNpcSpawnerSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

    /** The NPC records spawned by this subsystem (exposed for tests). */
    static TArray<FNpcSpawnRecord> GetRoster();

private:
    FVector ResolveSpawnBase(UWorld& World) const;

    /**
     * Traces straight down at ProbeXY to find the floor Z so actors rest on the ground instead of
     * floating. Returns the hit Z, or FallbackZ (logged) if nothing is hit.
     */
    float ResolveGroundZ(UWorld& World, const FVector& ProbeXY, float FallbackZ) const;

    void SpawnNpc(UWorld& World, const FNpcSpawnRecord& Record, const FVector& Base);
    void SpawnNoticeBoards(UWorld& World, const FVector& Base);

    bool bSpawned = false;
};
