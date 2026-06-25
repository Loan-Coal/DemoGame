// File: GossipCacheSubsystem.h
// Module: DemoGame
// Purpose: Caches gossip chain entries for the Rumor Journal; polls NPC state after each tick.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcDialogueService.h"
#include "GossipCacheSubsystem.generated.h"

/** Named event ID constants used by the gossip system. */
namespace GossipEventId
{
    inline const FName NorthernWarBegins = TEXT("northern_war_begins");
}

/** One hop in a gossip chain — who heard what, at which distortion level. */
USTRUCT(BlueprintType)
struct DEMOGAME_API FGossipEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Gossip")
    FName SourceNpcId;

    UPROPERTY(BlueprintReadOnly, Category = "Gossip")
    FName EventId;

    /** 0 = firsthand, 1 = rumor, 2+ = distorted. */
    UPROPERTY(BlueprintReadOnly, Category = "Gossip")
    int32 HopCount = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Gossip")
    FText DistortionText;

    /** Set by MarkPlayerSpokeToNpc; journal hides the row until true. */
    UPROPERTY(BlueprintReadOnly, Category = "Gossip")
    bool bPlayerSpokeToNpc = false;
};

/**
 * World subsystem that accumulates gossip chain entries for the Rumor Journal.
 *
 * Updated from two sources:
 *   1. MarkGossipFromDialogue() — called when dialogue response learned_facts contains a war event key.
 *   2. OnTickAdvanced() — bound to UNpcWorldSubsystem::OnTickAdvanced; polls Old Henryk's state
 *      via INpcDialogueService::GetNpcState to check if the war event knowledge_state updated.
 *
 * No FHttpModule, no JSON parsing — all net I/O routes through INpcDialogueService.
 */
UCLASS()
class DEMOGAME_API UGossipCacheSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // ── API ───────────────────────────────────────────────────────────────────

    /**
     * Add or update a gossip entry for the given NPC + event. If an entry for
     * (SourceNpcId, EventId) already exists it is replaced (dedup on source+event).
     */
    UFUNCTION(BlueprintCallable, Category = "Gossip")
    void AddGossipEntry(FName SourceNpcId, FName EventId, int32 HopCount, FText DistortionText);

    /**
     * Set bPlayerSpokeToNpc=true on all entries whose SourceNpcId matches.
     * Called by UDialogueComponent after any successful dialogue exchange.
     */
    UFUNCTION(BlueprintCallable, Category = "Gossip")
    void MarkPlayerSpokeToNpc(FName NpcId);

    /**
     * All entries for the given event, sorted by HopCount ascending.
     * Includes entries where bPlayerSpokeToNpc is false — widget decides visibility.
     */
    UFUNCTION(BlueprintCallable, Category = "Gossip")
    TArray<FGossipEntry> GetChainForEvent(FName EventId) const;

    /**
     * Called when dialogue learned_facts array contains a war-related event key.
     * SourceNpcId is the NPC who spoke; HopCount and DistortionText derived from seed data.
     */
    void MarkGossipFromDialogue(FName SourceNpcId, FName EventId);

    /** Inject the dialogue service for tests (DIP seam). */
    void SetDialogueService(TScriptInterface<INpcDialogueService> InService);

private:
    UFUNCTION()
    void OnTickAdvanced(FName NewLocationId, int32 TickCount);

    void PollHenrykState();

    INpcDialogueService* ResolveService();

    TArray<FGossipEntry> Entries;

    UPROPERTY()
    TScriptInterface<INpcDialogueService> DialogueService;
};
