// File: NpcAppearance.cpp
// Module: Game
// Purpose: Data-driven NPC appearance seam — single swap point for cube → MetaHuman.
// Net I/O: no
// rules-allow-file: hardcoded_npc_id — this IS the sanctioned appearance-data registry (analogous
// to seed JSON), not logic that hardcodes identifiers. Replace with a DataAsset in a later slice.

#include "NpcAppearance.h"

namespace NpcAppearance
{
    // Appearance registry — EMPTY by default (all NPCs are cubes).
    // To swap a single NPC: add one row here, e.g.
    //   { TEXT("mira_innkeeper"), FSoftClassPath(TEXT("/Game/MetaHumans/Mira/BP_Mira.BP_Mira_C")) }
    // This is a deliberate design point: Claude can flip a cube→MetaHuman with one line edit
    // once the human has imported the Blueprint at a known /Game/... path (DEC-039).
    static TMap<FName, FSoftClassPath> AppearanceMap;

    TSoftClassPtr<AActor> GetAvatarClass(FName NpcId)
    {
        const FSoftClassPath* Entry = AppearanceMap.Find(NpcId);
        if (Entry && !Entry->IsNull())
        {
            return TSoftClassPtr<AActor>(*Entry);
        }
        return TSoftClassPtr<AActor>();
    }
}
