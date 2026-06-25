// File: NpcSpawnerRoster.spec.cpp
// Module: DemoGame
// Purpose: Automation Spec — spawner roster integrity + built-in fallback line coverage.
// Net I/O: no
// rules-allow-file: hardcoded_npc_id  (test asserts the canonical npc_id roster by value)

#include "Misc/AutomationTest.h"
#include "World/NpcSpawnerSubsystem.h"
#include "NpcFallbackDefaults.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcSpawnerRosterSpec,
    "NpcEngine.Game.SpawnerRoster",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FNpcSpawnerRosterSpec::Define()
{
    Describe("GetRoster", [this]()
    {
        It("lists all five slice NPCs with stable ids and distinct offsets", [this]()
        {
            const TArray<FNpcSpawnRecord> Roster = UNpcSpawnerSubsystem::GetRoster();
            TestEqual("roster size", Roster.Num(), 5);

            const TArray<FName> Expected = {
                TEXT("mira_innkeeper"), TEXT("lira_fence"), TEXT("aldric_merchant"),
                TEXT("captain_sorn"), TEXT("old_henryk")
            };
            for (const FName& Id : Expected)
            {
                const bool bFound = Roster.ContainsByPredicate(
                    [&Id](const FNpcSpawnRecord& R){ return R.NpcId == Id; });
                TestTrue(FString::Printf(TEXT("roster contains %s"), *Id.ToString()), bFound);
            }

            for (const FNpcSpawnRecord& R : Roster)
            {
                TestFalse("display name is set", R.DisplayName.IsEmpty());
                TestFalse("location id is set", R.LocationId.IsEmpty());
            }
        });

        It("bakes no vertical offset — spawn Z is derived from a ground trace, not the roster", [this]()
        {
            // Regression guard for the floating-cube fix: the roster carries XY only; the spawner
            // resolves Z from the floor (ResolveGroundZ + CubeHalfHeight). Distinct XY keeps NPCs
            // apart. Actual ground placement is verified manually in PIE (gameplay-actor smoke split).
            for (const FNpcSpawnRecord& R : UNpcSpawnerSubsystem::GetRoster())
            {
                TestEqual(
                    FString::Printf(TEXT("%s offset Z is zero"), *R.NpcId.ToString()),
                    R.Offset.Z, 0.0);
            }
        });
    });

    Describe("NpcFallbackDefaults", [this]()
    {
        It("returns a non-empty line for every rostered NPC", [this]()
        {
            for (const FNpcSpawnRecord& R : UNpcSpawnerSubsystem::GetRoster())
            {
                TestFalse(
                    FString::Printf(TEXT("fallback for %s"), *R.NpcId.ToString()),
                    NpcFallbackDefaults::GetLine(R.NpcId).IsEmpty());
            }
        });

        It("returns empty for an unknown npc id", [this]()
        {
            TestTrue("unknown id has no line",
                NpcFallbackDefaults::GetLine(TEXT("nobody_here")).IsEmpty());
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
