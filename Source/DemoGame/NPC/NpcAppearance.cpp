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
    // C++ default map — Mannequin stand-in for all 5 NPCs (DEC-042 Phase 12 A5).
    // Each entry is overridden (DataAsset or this map) as a MetaHuman BP is imported.
    // Async load path handles missing assets gracefully (cube stays visible).
    // rules-allow: hardcoded_npc_id — these ARE the sanctioned data-definition rows.
    static const FSoftClassPath MannequinPath(
        TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter_C"));

    static TMap<FName, FSoftClassPath> AppearanceMap = {
        { FName("mira_innkeeper"),  MannequinPath },
        { FName("lira_fence"),      MannequinPath },
        { FName("aldric_merchant"), MannequinPath },
        { FName("captain_sorn"),    MannequinPath },
        { FName("old_henryk"),      MannequinPath },
    };

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
