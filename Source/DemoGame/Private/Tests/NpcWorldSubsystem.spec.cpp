// File: NpcWorldSubsystem.spec.cpp
// Module: DemoGame
// Purpose: Automation Spec — UNpcWorldSubsystem tick logic, re-entry guard, service wiring.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NpcWorldSubsystem.h"
#include "NpcDialogueService.h"
#include "FakeNpcDialogueService.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcWorldSubsystemSpec,
    "NpcEngine.Game.NpcWorldSubsystem",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

namespace
{
    UNpcWorldSubsystem* MakeSubsystem(UFakeNpcDialogueService* Fake)
    {
        UNpcWorldSubsystem* WS = NewObject<UNpcWorldSubsystem>(GetTransientPackage());
        WS->SetDialogueService(Fake);
        return WS;
    }
}

void FNpcWorldSubsystemSpec::Define()
{
    Describe("OnPlayerArrived", [this]()
    {
        It("calls AdvanceClock(1) when arriving at a new location with bFiresTick=true", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UNpcWorldSubsystem* WS = MakeSubsystem(Fake);

            WS->OnPlayerArrived(FName(TEXT("loc_tavern")), true);

            TestEqual("AdvanceClock called once", Fake->AdvanceClockCallCount, 1);
            TestEqual("DeltaTicks = 1", Fake->LastDeltaTicks, 1);
            TestEqual("TickCount incremented", WS->GetTickCount(), 1);
            TestEqual("CurrentLocationId updated", WS->GetCurrentLocationId(), FName(TEXT("loc_tavern")));
        });

        It("does NOT call AdvanceClock when bFiresTick=false (e.g. tavern back room)", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UNpcWorldSubsystem* WS = MakeSubsystem(Fake);

            WS->OnPlayerArrived(FName(TEXT("loc_tavern_back")), false);

            TestEqual("AdvanceClock NOT called", Fake->AdvanceClockCallCount, 0);
            TestEqual("TickCount unchanged", WS->GetTickCount(), 0);
        });

        It("re-entry guard: same location twice fires clock only once", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UNpcWorldSubsystem* WS = MakeSubsystem(Fake);

            WS->OnPlayerArrived(FName(TEXT("loc_tavern")), true);
            WS->OnPlayerArrived(FName(TEXT("loc_tavern")), true);  // re-entry — must be ignored

            TestEqual("AdvanceClock called only once", Fake->AdvanceClockCallCount, 1);
            TestEqual("TickCount = 1", WS->GetTickCount(), 1);
        });

        It("different location after first arrival fires clock again", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UNpcWorldSubsystem* WS = MakeSubsystem(Fake);

            WS->OnPlayerArrived(FName(TEXT("loc_tavern")), true);
            WS->OnPlayerArrived(FName(TEXT("loc_market_square")), true);

            TestEqual("AdvanceClock called twice", Fake->AdvanceClockCallCount, 2);
            TestEqual("TickCount = 2", WS->GetTickCount(), 2);
            TestEqual("CurrentLocationId = market", WS->GetCurrentLocationId(),
                      FName(TEXT("loc_market_square")));
        });

        It("AdvanceClock failure (non-2xx) is handled gracefully — game continues", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bAdvanceClockSucceeds = false;
            UNpcWorldSubsystem* WS = MakeSubsystem(Fake);

            // The failure path logs an Error by design; declare it expected so the framework does not
            // auto-fail the test on the logged Error.
            AddExpectedError(TEXT("ClockAdvance failed"), EAutomationExpectedErrorFlags::Contains, 0);

            // Should not crash even though the clock call fails.
            WS->OnPlayerArrived(FName(TEXT("loc_tavern")), true);

            TestEqual("AdvanceClock was attempted", Fake->AdvanceClockCallCount, 1);
            // TickCount should still NOT increment on failure.
            TestEqual("TickCount stays 0 on failure", WS->GetTickCount(), 0);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
