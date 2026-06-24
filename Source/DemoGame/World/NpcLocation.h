// File: NpcLocation.h
// Module: DemoGame
// Purpose: Trigger-volume actor that notifies UNpcWorldSubsystem when the player arrives.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NpcLocation.generated.h"

class USphereComponent;

/**
 * Placed once per navigable location. The trigger sphere fires OnPlayerArrived on
 * UNpcWorldSubsystem, which advances the world clock when bFiresTick is true.
 *
 * Usage: place in level, set LocationId to the matching loc_* FName constant, leave
 * bFiresTick at its default (true) or set false for rooms that should not advance the clock
 * (e.g. the tavern back room).
 */
UCLASS()
class DEMOGAME_API ANpcLocation : public AActor
{
    GENERATED_BODY()

public:
    ANpcLocation();

    /**
     * Must match the engine location id exactly (e.g. "loc_tavern").
     * Default NAME_None is invalid — set in the editor for every placed actor.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location")
    FName LocationId;

    /**
     * When true (default), overlapping the trigger fires a clock tick via UNpcWorldSubsystem.
     * Set false for sub-areas that share a parent location (e.g. loc_tavern_back).
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location")
    bool bFiresTick = true;

    /** Arrival trigger — size this to cover the walkable area in the editor. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USphereComponent> TriggerVolume;

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnTriggerOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
