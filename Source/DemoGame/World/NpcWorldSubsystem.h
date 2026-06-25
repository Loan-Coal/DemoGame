// File: NpcWorldSubsystem.h
// Module: DemoGame
// Purpose: Tracks player location; fires clock-advance ticks through INpcDialogueService on arrival.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcDialogueService.h"
#include "NpcWorldSubsystem.generated.h"

/** Broadcasts when a clock tick fires (location changed, bFiresTick=true, clock advance succeeded). */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnTickAdvanced,
    FName,  NewLocationId,
    int32,  TickCount);

/** Fires once when Mira's accumulated trust crosses TrustGate2Mira (threshold=40). DEC-027. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTavernBackUnlocked);

/**
 * World subsystem that tracks which named location the player is currently in and fires
 * a clock-advance tick through INpcDialogueService when the player moves to a new location.
 *
 * Locations with bFiresTick=false (e.g. loc_tavern_back) update CurrentLocationId but do
 * not call AdvanceClock and do not broadcast OnTickAdvanced.
 *
 * Re-entry guard: arriving at the same location twice has no effect.
 */
UCLASS()
class DEMOGAME_API UNpcWorldSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    // ── Lifecycle ────────────────────────────────────────────────────────────

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ── Public API ───────────────────────────────────────────────────────────

    /**
     * Called by ANpcLocation when the player overlaps its trigger.
     *
     * @param LocationId  The FName constant for the location (e.g. "loc_tavern").
     * @param bFiresTick  If false, location is recorded but no clock advance is fired.
     */
    void OnPlayerArrived(FName LocationId, bool bFiresTick);

    /** Current FName location of the player. NAME_None until first arrival. */
    UFUNCTION(BlueprintPure, Category = "World|Location")
    FName GetCurrentLocationId() const { return CurrentLocationId; }

    /** Number of successful clock-advance ticks since session start. */
    UFUNCTION(BlueprintPure, Category = "World|Location")
    int32 GetTickCount() const { return TickCount; }

    /**
     * Inject the dialogue service (DIP seam). Overrides lazy resolution from the
     * GameInstance composition root — for tests and explicit wiring.
     */
    void SetDialogueService(TScriptInterface<INpcDialogueService> InService);

    /**
     * Called by UDialogueManagerSubsystem::NotifyRelationshipChanged to accumulate trust
     * per NPC and fire the L_TavernBack gate when Mira's trust crosses TrustGate2Mira.
     *
     * @param NpcId     The NPC whose trust changed (compare with NpcId:: constants).
     * @param TrustDelta The signed trust delta from the dialogue response RelationDeltas.
     */
    void NotifyRelationshipUpdated(FName InNpcId, int32 TrustDelta);

    // ── Delegates ────────────────────────────────────────────────────────────

    /** Fires after each successful clock advance tick. Bind UArrivalSubtitleWidget here. */
    UPROPERTY(BlueprintAssignable, Category = "World|Location")
    FOnTickAdvanced OnTickAdvanced;

    /**
     * Fires ONCE when Mira's accumulated trust crosses TrustGate2Mira (threshold=40).
     * Wire this in Level Blueprint or player HUD to stream in L_TavernBack sub-level.
     */
    UPROPERTY(BlueprintAssignable, Category = "World|Location")
    FOnTavernBackUnlocked OnTavernBackUnlocked;

private:
    /** Lazily resolved from UNpcEngineServiceSubsystem, or injected by tests. */
    UPROPERTY()
    TScriptInterface<INpcDialogueService> DialogueService;

    FName CurrentLocationId;
    int32 TickCount = 0;

    /** Accumulated trust per NPC (for gate checks). Not saved — resets on session end. */
    TMap<FName, int32> AccumulatedTrustByNpc;

    /** Set to true once OnTavernBackUnlocked fires — prevents repeat broadcasts. */
    bool bTavernBackUnlocked = false;

    /** Set to true once Sorn's patrol_duty quest fires — prevents repeat activation. */
    bool bSornQuestFired = false;

    INpcDialogueService* ResolveService();
};
