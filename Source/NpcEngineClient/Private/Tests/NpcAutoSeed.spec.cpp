// File: NpcAutoSeed.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec — UNpcAutoSeedSubsystem gating: health-gated, once-per-session seeding.
// Net I/O: no  (health + seed seams injected synchronously; no live engine required)

#include "Misc/AutomationTest.h"
#include "NpcAutoSeedSubsystem.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcAutoSeedSpec,
    "NpcEngine.Client.AutoSeed",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FNpcAutoSeedSpec::Define()
{
    Describe("TryAutoSeed gating", [this]()
    {
        It("seeds when the engine reports healthy", [this]()
        {
            UNpcAutoSeedSubsystem* Sub = NewObject<UNpcAutoSeedSubsystem>();
            int32 SeedCount = 0;
            Sub->SetHealthCheckForTesting(
                [](TFunction<void(bool)> OnResult){ OnResult(true); });
            Sub->SetSeederForTesting(
                [&SeedCount](TFunction<void()> OnComplete, TFunction<void(const FString&)>)
                {
                    ++SeedCount;
                    OnComplete();
                });

            Sub->TryAutoSeed();

            TestEqual("seed action ran exactly once", SeedCount, 1);
            TestTrue("attempt flag set", Sub->HasAttemptedSeed());
        });

        It("does not seed when the engine is unhealthy", [this]()
        {
            UNpcAutoSeedSubsystem* Sub = NewObject<UNpcAutoSeedSubsystem>();
            int32 SeedCount = 0;
            Sub->SetHealthCheckForTesting(
                [](TFunction<void(bool)> OnResult){ OnResult(false); });
            Sub->SetSeederForTesting(
                [&SeedCount](TFunction<void()>, TFunction<void(const FString&)>){ ++SeedCount; });

            Sub->TryAutoSeed();

            TestEqual("seed action never ran", SeedCount, 0);
            TestTrue("attempt still marked (no retry this session)", Sub->HasAttemptedSeed());
        });

        It("seeds at most once across repeated triggers", [this]()
        {
            UNpcAutoSeedSubsystem* Sub = NewObject<UNpcAutoSeedSubsystem>();
            int32 SeedCount = 0;
            Sub->SetHealthCheckForTesting(
                [](TFunction<void(bool)> OnResult){ OnResult(true); });
            Sub->SetSeederForTesting(
                [&SeedCount](TFunction<void()> OnComplete, TFunction<void(const FString&)>)
                {
                    ++SeedCount;
                    OnComplete();
                });

            Sub->TryAutoSeed();
            Sub->TryAutoSeed();
            Sub->TryAutoSeed();

            TestEqual("seed action ran exactly once despite three triggers", SeedCount, 1);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
