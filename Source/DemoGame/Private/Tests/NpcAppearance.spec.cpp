// File: NpcAppearance.spec.cpp
// Module: Game
// Purpose: Verifies data-driven appearance seam: cube by default, no divergent sources.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NPC/NpcAppearance.h"
#include "World/NpcSpawnerSubsystem.h"

DEFINE_SPEC(FNpcAppearanceSpec, "NpcEngine.Game.NpcAppearance",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FNpcAppearanceSpec::Define()
{
    Describe("GetAvatarClass", [this]()
    {
        It("returns empty for all rostered NPC ids by default", [this]()
        {
            for (const FNpcSpawnRecord& Record : UNpcSpawnerSubsystem::GetRoster())
            {
                const TSoftClassPtr<AActor> AvatarClass =
                    NpcAppearance::GetAvatarClass(Record.NpcId);
                TestTrue(
                    FString::Printf(TEXT("%s should default to empty (cube)"),
                        *Record.NpcId.ToString()),
                    AvatarClass.IsNull());
            }
        });

        It("returns empty for an unknown npc id", [this]()
        {
            TestTrue("unknown_npc_xyz → empty",
                NpcAppearance::GetAvatarClass(FName("unknown_npc_xyz_9999")).IsNull());
        });

        It("roster AvatarClass matches GetAvatarClass for every entry (no divergent source)", [this]()
        {
            // Verifies the spawner fills AvatarClass from NpcAppearance — there is exactly
            // one source of truth for appearance (NpcAppearance), not two competing ones.
            for (const FNpcSpawnRecord& Record : UNpcSpawnerSubsystem::GetRoster())
            {
                const FString Expected =
                    NpcAppearance::GetAvatarClass(Record.NpcId).ToSoftObjectPath().ToString();
                const FString Actual =
                    Record.AvatarClass.ToSoftObjectPath().ToString();
                TestEqual(
                    FString::Printf(TEXT("AvatarClass parity for %s"), *Record.NpcId.ToString()),
                    Actual, Expected);
            }
        });
    });
}
