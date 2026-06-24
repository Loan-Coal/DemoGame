// File: FactionSubsystem.h
// Module: DemoGame
// Purpose: Tracks faction standings; updated by relation_deltas for faction-affiliated NPCs.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcQuestService.h"
#include "FactionSubsystem.generated.h"

// ── Faction ID constants ──────────────────────────────────────────────────────
namespace FactionId
{
    inline const FName ThievesGuild = TEXT("thieves_guild");
    inline const FName GuardFaction = TEXT("guard_faction");
}

/** Fires when any faction standing changes. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFactionStandingChanged,
    FName, FactionId, int32, NewStanding);

/**
 * World subsystem tracking faction standings and routing fork choices via INpcQuestService.
 * Faction membership data is looked up from a static greybox map (keyed by NpcId constant).
 * No HTTP, no JSON — all network calls go through INpcQuestService.
 */
UCLASS()
class DEMOGAME_API UFactionSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * Called by UDialogueComponent or UQuestSubsystem when relation_deltas arrive
     * for an NPC that may be faction-affiliated.
     * Looks up faction membership; if found, applies TrustDelta to that faction's standing.
     */
    UFUNCTION(BlueprintCallable, Category = "Faction")
    void OnNpcRelationUpdated(FName NpcId, int32 TrustDelta);

    /**
     * Execute a faction fork choice: calls QuestChoose through INpcQuestService.
     * Also saves standings after the choice.
     */
    UFUNCTION(BlueprintCallable, Category = "Faction")
    void ExecuteForkChoice(FName QuestId, FName ChoiceId);

    /** Returns current standing for a faction, or 0 if unknown. */
    UFUNCTION(BlueprintPure, Category = "Faction")
    int32 GetStanding(FName InFactionId) const;

    /** Restore standings from save data (called by NpcSaveGame on load). */
    void LoadStandings(const TMap<FName, int32>& Saved);

    /** Inject quest service for tests. */
    void SetQuestService(TScriptInterface<INpcQuestService> InService);

    UPROPERTY(BlueprintAssignable, Category = "Faction")
    FOnFactionStandingChanged OnFactionStandingChanged;

    /** Snapshot for save (DEC-025). */
    const TMap<FName, int32>& GetStandings() const { return Standings; }

private:
    INpcQuestService* ResolveQuestService();

    UPROPERTY()
    TScriptInterface<INpcQuestService> QuestService;

    TMap<FName, int32> Standings;
};
