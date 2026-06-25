// File: GreyboxWorldSubsystem.h
// Module: Game
// Purpose: Procedurally builds the greybox world at begin-play: floor slab + location triggers.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GreyboxWorldSubsystem.generated.h"

/** One navigable location in the procedural greybox world. */
USTRUCT()
struct DEMOGAME_API FGreyboxLocation
{
    GENERATED_BODY()

    /** Stable location id (matches engine seed, e.g. "loc_tavern"). */
    FName Id;

    /** Center offset relative to the world base (PlayerStart or origin). +X = forward. */
    FVector CenterOffset = FVector::ZeroVector;

    /** Radius of the ANpcLocation overlap sphere in cm. */
    float Radius = 500.f;

    /** When false the location's arrival does NOT advance the world clock (e.g. back rooms). */
    bool bFiresTick = true;
};

/**
 * Builds the slice's walkable world at begin-play with no editor work:
 * - One large floor slab (scaled engine cube)
 * - One ANpcLocation trigger actor per canonical location
 *
 * Only runs in real game worlds. Idempotent via the bBuilt guard.
 * If an ANpcLocation with a given id is already placed in the loaded level (authored art pass),
 * that location is skipped so the authored actor takes precedence.
 *
 * UNpcSpawnerSubsystem calls EnsureBuilt() before spawning NPCs, then uses
 * GetLocationCenter() to place each NPC inside its location trigger.
 */
UCLASS()
class DEMOGAME_API UGreyboxWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

    /**
     * Returns the canonical layout table (4 locations spread along +X).
     * Static — safe to call without a world or subsystem instance.
     */
    static TArray<FGreyboxLocation> GetLayout();

    /**
     * Idempotent world-build. Spawns floor + triggers on the first call, no-ops thereafter.
     * Resolves WorldBase from PlayerStart (falls back to origin).
     * Must be called before GetLocationCenter() to guarantee a valid WorldBase.
     */
    void EnsureBuilt();

    /**
     * Returns WorldBase + CenterOffset for the given location id.
     * If the id is not in the layout, returns WorldBase (the anchor point).
     * Caller must EnsureBuilt() first for a meaningful WorldBase.
     */
    FVector GetLocationCenter(FName LocationId) const;

private:
    /** World-space anchor resolved from PlayerStart. Set by EnsureBuilt(). */
    FVector WorldBase = FVector::ZeroVector;

    /** Guard: EnsureBuilt() is a no-op after the first successful call. */
    bool bBuilt = false;

    FVector ResolveWorldBase(UWorld& World) const;
    void SpawnFloor(UWorld& World);
    void SpawnLocationTrigger(UWorld& World, const FGreyboxLocation& Loc);
};
