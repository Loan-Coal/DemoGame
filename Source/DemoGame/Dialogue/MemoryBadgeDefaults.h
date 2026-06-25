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
            { FName(TEXT("northern_war_begins")),   FText::FromString(TEXT("Northern Conflict recalled")) },

            // ── Characters ──────────────────────────────────────────────────────
            { FName(TEXT("mira_innkeeper")),        FText::FromString(TEXT("Memory of Mira")) },
            { FName(TEXT("lira_fence")),            FText::FromString(TEXT("Memory of Lira")) },
            { FName(TEXT("aldric_merchant")),       FText::FromString(TEXT("Memory of Aldric")) },
            { FName(TEXT("captain_sorn")),          FText::FromString(TEXT("Memory of Captain Sorn")) },
            { FName(TEXT("old_henryk")),            FText::FromString(TEXT("Memory of Old Henryk")) },
            { FName(TEXT("player_demo")),           FText::FromString(TEXT("Memory of the Traveler")) },

            // ── Factions ─────────────────────────────────────────────────────────
            { FName(TEXT("guard_faction")),         FText::FromString(TEXT("City Guard connection recalled")) },
            { FName(TEXT("thieves_guild")),         FText::FromString(TEXT("Guild connection recalled")) },

            // ── Quests ───────────────────────────────────────────────────────────
            { FName(TEXT("find_wine_merchant")),    FText::FromString(TEXT("Wine merchant lead recalled")) },
            { FName(TEXT("deliver_amulet")),        FText::FromString(TEXT("Amulet delivery recalled")) },
            { FName(TEXT("aldric_confession")),     FText::FromString(TEXT("Aldric's secret recalled")) },
            { FName(TEXT("patrol_duty")),           FText::FromString(TEXT("Patrol assignment recalled")) },
            { FName(TEXT("captain_report")),        FText::FromString(TEXT("Captain's report recalled")) },
            { FName(TEXT("missing_goods")),         FText::FromString(TEXT("Missing shipment recalled")) },
            { FName(TEXT("fence_confrontation")),   FText::FromString(TEXT("Confrontation recalled")) },

            // ── Locations ────────────────────────────────────────────────────────
            { FName(TEXT("loc_tavern")),            FText::FromString(TEXT("Meeting at The Broken Flagon recalled")) },
            { FName(TEXT("loc_tavern_back")),       FText::FromString(TEXT("Back room encounter recalled")) },
            { FName(TEXT("loc_market_square")),     FText::FromString(TEXT("Market square encounter recalled")) },
            { FName(TEXT("loc_guard_barracks")),    FText::FromString(TEXT("Barracks encounter recalled")) },
        };

        const FText* Found = Stubs.Find(MemoryId);
        return Found ? *Found : FText::GetEmpty();
    }
}
