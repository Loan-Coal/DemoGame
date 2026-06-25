// File: GreyboxWorld.spec.cpp
// Module: DemoGame
// Purpose: Automation Spec — greybox layout table integrity + roster-layout consistency.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "World/GreyboxWorldSubsystem.h"
#include "World/NpcSpawnerSubsystem.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FGreyboxWorldSpec,
    "NpcEngine.Game.GreyboxWorld",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FGreyboxWorldSpec::Define()
{
    Describe("GetLayout", [this]()
    {
        It("contains exactly the 4 canonical locations", [this]()
        {
            const TArray<FGreyboxLocation> Layout = UGreyboxWorldSubsystem::GetLayout();
            TestEqual("layout size", Layout.Num(), 4);

            TSet<FName> Ids;
            for (const FGreyboxLocation& Loc : Layout)
            {
                Ids.Add(Loc.Id);
            }
            TestTrue("loc_tavern present",        Ids.Contains(FName(TEXT("loc_tavern"))));
            TestTrue("loc_tavern_back present",   Ids.Contains(FName(TEXT("loc_tavern_back"))));
            TestTrue("loc_market_square present", Ids.Contains(FName(TEXT("loc_market_square"))));
            TestTrue("loc_guard_barracks present",Ids.Contains(FName(TEXT("loc_guard_barracks"))));
        });

        It("only loc_tavern_back has bFiresTick=false", [this]()
        {
            for (const FGreyboxLocation& Loc : UGreyboxWorldSubsystem::GetLayout())
            {
                const bool bExpectTick = (Loc.Id != FName(TEXT("loc_tavern_back")));
                TestEqual(
                    FString::Printf(TEXT("%s bFiresTick"), *Loc.Id.ToString()),
                    Loc.bFiresTick, bExpectTick);
            }
        });

        It("every location has radius greater than zero", [this]()
        {
            for (const FGreyboxLocation& Loc : UGreyboxWorldSubsystem::GetLayout())
            {
                TestTrue(
                    FString::Printf(TEXT("%s radius > 0"), *Loc.Id.ToString()),
                    Loc.Radius > 0.f);
            }
        });

        It("every NPC LocationId from the spawner roster maps to a layout entry", [this]()
        {
            const TArray<FGreyboxLocation> Layout = UGreyboxWorldSubsystem::GetLayout();
            TSet<FName> LayoutIds;
            for (const FGreyboxLocation& Loc : Layout)
            {
                LayoutIds.Add(Loc.Id);
            }

            for (const FNpcSpawnRecord& Record : UNpcSpawnerSubsystem::GetRoster())
            {
                const FName LocationName(*Record.LocationId);
                TestTrue(
                    FString::Printf(TEXT("%s LocationId '%s' in layout"),
                        *Record.NpcId.ToString(), *Record.LocationId),
                    LayoutIds.Contains(LocationName));
            }
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
