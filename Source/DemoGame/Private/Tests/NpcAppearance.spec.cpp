// File: NpcAppearance.spec.cpp
// Module: Game
// Purpose: Verifies data-driven appearance seam: cube by default, DataAsset override, no divergent sources.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NPC/NpcAppearance.h"
#include "NPC/NpcAppearanceData.h"
#include "World/NpcSpawnerSubsystem.h"

DEFINE_SPEC(FNpcAppearanceSpec, "NpcEngine.Game.NpcAppearance",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FNpcAppearanceSpec::Define()
{
    Describe("GetAvatarClass — C++ default map", [this]()
    {
        It("returns empty for all rostered NPC ids by default (cube stand-in)", [this]()
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

    Describe("Hybrid resolver — DataAsset override tier (DEC-042)", [this]()
    {
        It("DataAsset entry overrides the C++ default map for a rostered NPC", [this]()
        {
            UNpcAppearanceData* DA = NewObject<UNpcAppearanceData>();
            DA->AddToRoot();
            const FSoftClassPath FakePath(TEXT("/Game/Test/BP_FakeMira.BP_FakeMira_C"));
            DA->AvatarByNpcId.Add(FName("mira_innkeeper"), TSoftClassPtr<AActor>(FakePath));

            const TSoftClassPtr<AActor> Result =
                NpcAppearance::GetAvatarClass(FName("mira_innkeeper"), DA);
            TestEqual("DataAsset path returned",
                Result.ToSoftObjectPath().ToString(), FakePath.ToString());
            DA->RemoveFromRoot();
        });

        It("falls through to C++ default map when DataAsset has no entry for the NPC", [this]()
        {
            UNpcAppearanceData* DA = NewObject<UNpcAppearanceData>();
            DA->AddToRoot();
            // No entry for lira_fence → falls through to C++ default (currently empty → cube)
            const TSoftClassPtr<AActor> Result =
                NpcAppearance::GetAvatarClass(FName("lira_fence"), DA);
            TestTrue("no DataAsset entry → C++ default (empty = cube)",
                Result.IsNull());
            DA->RemoveFromRoot();
        });

        It("nullptr DataAsset falls through to C++ default (backward compatible)", [this]()
        {
            TestTrue("nullptr DataAsset → C++ default (currently empty = cube)",
                NpcAppearance::GetAvatarClass(FName("captain_sorn"), nullptr).IsNull());
        });

        It("DataAsset with no entries for any NPC returns C++ default for all rostered NPCs", [this]()
        {
            UNpcAppearanceData* DA = NewObject<UNpcAppearanceData>();
            DA->AddToRoot();
            for (const FNpcSpawnRecord& Record : UNpcSpawnerSubsystem::GetRoster())
            {
                const TSoftClassPtr<AActor> Result =
                    NpcAppearance::GetAvatarClass(Record.NpcId, DA);
                TestTrue(
                    FString::Printf(TEXT("empty DA → C++ default for %s"), *Record.NpcId.ToString()),
                    Result.IsNull());
            }
            DA->RemoveFromRoot();
        });
    });
}
