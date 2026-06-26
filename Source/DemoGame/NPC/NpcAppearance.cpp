// File: NpcAppearance.cpp
// Module: Game
// Purpose: Data-driven NPC appearance seam — single swap point for cube → MetaHuman.
// Net I/O: no
// rules-allow-file: hardcoded_npc_id — this IS the sanctioned appearance-data registry (analogous
// to seed JSON), not logic that hardcodes identifiers. Replace with a DataAsset in a later slice.

#include "NpcAppearance.h"
#include "NpcAppearanceData.h"

namespace NpcAppearance
{
    // C++ default map — EMPTY until MetaHumans land; every NPC defaults to a cube stand-in.
    // To swap one NPC headlessly, add one row pointing at the imported BP class path, e.g.:
    //   AppearanceMap.Add("mira_innkeeper",
    //       FSoftClassPath(TEXT("/Game/MetaHumans/Mira/BP_Mira.BP_Mira_C")));
    // No editor step required — rebuilding DemoGame is sufficient (DEC-039).
    static TMap<FName, FSoftClassPath> AppearanceMap;

    TSoftClassPtr<AActor> GetAvatarClass(FName NpcId, const UNpcAppearanceData* DataAsset)
    {
        // Tier 1: DataAsset override (editor-assigned, no recompile required).
        if (DataAsset)
        {
            const TSoftClassPtr<AActor>* DAEntry = DataAsset->AvatarByNpcId.Find(NpcId);
            if (DAEntry && !DAEntry->IsNull())
            {
                return *DAEntry;
            }
        }
        // Tier 2: C++ default map (headless one-line swap, DEC-039/DEC-042).
        const FSoftClassPath* MapEntry = AppearanceMap.Find(NpcId);
        if (MapEntry && !MapEntry->IsNull())
        {
            return TSoftClassPtr<AActor>(*MapEntry);
        }
        return TSoftClassPtr<AActor>();
    }
}
