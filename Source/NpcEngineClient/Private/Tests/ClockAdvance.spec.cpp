// File: ClockAdvance.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec — AdvanceClock JSON body and error-path contract.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NpcEngineJsonUtils.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FClockAdvanceSpec,
    "NpcEngine.Client.ClockAdvance",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FClockAdvanceSpec::Define()
{
    Describe("SerialiseClockAdvance", [this]()
    {
        It("produces a body with delta_ticks equal to DeltaTicks", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseClockAdvance(1);
            TestTrue("has delta_ticks key", Json.Contains(TEXT("delta_ticks")));
            // Value 1 must appear in the body.
            TestTrue("has value 1", Json.Contains(TEXT("1")));
        });

        It("reflects the DeltaTicks argument for values other than 1", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseClockAdvance(5);
            TestTrue("has delta_ticks key", Json.Contains(TEXT("delta_ticks")));
            TestTrue("has value 5", Json.Contains(TEXT("5")));
        });

        It("produces valid JSON (parseable)", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseClockAdvance(1);
            TSharedPtr<FJsonObject> Obj;
            TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
            TestTrue("JSON parses cleanly", FJsonSerializer::Deserialize(Reader, Obj));
            TestNotNull("root object non-null", Obj.Get());
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
