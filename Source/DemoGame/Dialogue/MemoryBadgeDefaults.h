// File: MemoryBadgeDefaults.h
// Module: Game
// Purpose: Built-in stub badge text for memories_recalled node IDs from Seed/DemoWorld_v1.json.
// Net I/O: no
// rules-allow-file: hardcoded_npc_id  (this is the C++ data table keyed by seed node ids; see NpcFallbackDefaults.h pattern and DEC-028)

#pragma once

#include "CoreMinimal.h"

/**
 * Stub badge display text keyed by memory node ID.
 *
 * Used by UDialogueWidgetBase when no DA_MemoryBadgeLookup DataAsset is assigned (or it
 * returns empty text for the given ID). Entries cover every stable node ID seeded in
 * Seed/DemoWorld_v1.json: events, characters, factions, quests, and locations.
 *
 * Phase 10 replaces these stubs with final authored text via C++ constants
 * (same pattern as DEC-028 quest metadata). A DA_MemoryBadgeLookup DataAsset can override
 * these at any time — DataAsset takes precedence over this header.
 *
 * Never shows raw memory node IDs to the player.
 */
namespace MemoryBadgeDefaults
{
    /** Returns stub badge text for a memory node ID, or FText::GetEmpty() if unregistered. */
    inline FText GetBadgeText(FName MemoryId)
    {
        static const TMap<FName, FText> Stubs = {
            // ── Events ──────────────────────────────────────────────────────────
            { FName(TEXT("northern_war_begins")),   FText::FromString(TEXT("The northern conflict — something Thornfield's guards won't speak of")) },

            // ── Characters ──────────────────────────────────────────────────────
            { FName(TEXT("mira_innkeeper")),        FText::FromString(TEXT("Mira — The Broken Flagon's keeper, who knows more than she tells")) },
            { FName(TEXT("lira_fence")),            FText::FromString(TEXT("Lira — the fence who operates from the shadows of the back room")) },
            { FName(TEXT("aldric_merchant")),       FText::FromString(TEXT("Aldric — the nervous wine merchant with a dangerous secret")) },
            { FName(TEXT("captain_sorn")),          FText::FromString(TEXT("Captain Sorn — Thornfield's barracks commander, a guardian of harder truths")) },
            { FName(TEXT("old_henryk")),            FText::FromString(TEXT("Old Henryk — Thornfield's most reliable rumour-monger")) },
            { FName(TEXT("player_demo")),           FText::FromString(TEXT("The Traveler's own footsteps through Thornfield")) },

            // ── Factions ─────────────────────────────────────────────────────────
            { FName(TEXT("guard_faction")),         FText::FromString(TEXT("The City Guard — Thornfield's keepers of uncomfortable order")) },
            { FName(TEXT("thieves_guild")),         FText::FromString(TEXT("The Thieves' Guild — a network operating beneath Thornfield's market")) },

            // ── Quests ───────────────────────────────────────────────────────────
            { FName(TEXT("find_wine_merchant")),    FText::FromString(TEXT("A lead on the missing wine merchant — the question that started everything")) },
            { FName(TEXT("deliver_amulet")),        FText::FromString(TEXT("The amulet — evidence of something Thornfield's garrison wants buried")) },
            { FName(TEXT("aldric_confession")),     FText::FromString(TEXT("What Aldric admitted in a low voice")) },
            { FName(TEXT("patrol_duty")),           FText::FromString(TEXT("A patrol posting along Thornfield's northern road")) },
            { FName(TEXT("captain_report")),        FText::FromString(TEXT("A report Captain Sorn needs delivered quietly")) },
            { FName(TEXT("missing_goods")),         FText::FromString(TEXT("A shipment gone missing — someone in Thornfield knows where")) },
            { FName(TEXT("fence_confrontation")),   FText::FromString(TEXT("The tense exchange with Lira in The Broken Flagon's dim back room")) },

            // ── Locations ────────────────────────────────────────────────────────
            { FName(TEXT("loc_tavern")),            FText::FromString(TEXT("The Broken Flagon — Thornfield's centre of gossip and warm ale")) },
            { FName(TEXT("loc_tavern_back")),       FText::FromString(TEXT("The dim storeroom behind The Broken Flagon's bar")) },
            { FName(TEXT("loc_market_square")),     FText::FromString(TEXT("Thornfield's market square — where rumours pass like coin")) },
            { FName(TEXT("loc_guard_barracks")),    FText::FromString(TEXT("The guard barracks on Thornfield's edge — stone walls and closed doors")) },
        };

        const FText* Found = Stubs.Find(MemoryId);
        return Found ? *Found : FText::GetEmpty();
    }
}
