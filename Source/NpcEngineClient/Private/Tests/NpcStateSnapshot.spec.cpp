// File: NpcStateSnapshot.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec — FNpcStateSnapshot parse contract and error-path behaviour.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NpcEngineJsonUtils.h"
#include "NpcEngineTypes.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcStateSnapshotSpec,
    "NpcEngine.Client.NpcStateSnapshot",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FNpcStateSnapshotSpec::Define()
{
    Describe("ParseNpcStateSnapshot", [this]()
    {
        It("parses character fields, relations count, and events array from valid OkEnvelope data", [this]()
        {
            const FString Json = TEXT(R"json(
{
  "data": {
    "character": { "id": "old_henryk", "name": "Old Henryk" },
    "relations": [
      { "target_id": "player_demo", "trust": 5, "fear": 0, "affection": 1 }
    ],
    "events": [
      { "event_id": "northern_war_begins", "knowledge_state": "heard", "hop_count": 2 }
    ]
  },
  "meta": null,
  "error": null
})json");

            TSharedPtr<FJsonObject> Data;
            TestTrue("envelope unwraps", FNpcEngineJsonUtils::UnwrapEnvelopeData(Json, Data));

            FNpcStateSnapshot Snap;
            TestTrue("parse succeeds", FNpcEngineJsonUtils::ParseNpcStateSnapshot(Data, Snap));
            TestTrue("bValid is true", Snap.bValid);
            TestEqual("NpcId", Snap.NpcId, FString(TEXT("old_henryk")));
            TestEqual("Name", Snap.Name, FString(TEXT("Old Henryk")));
            TestEqual("relations count", Snap.Relations.Num(), 1);
            TestEqual("events count", Snap.Events.Num(), 1);
            TestEqual("event_id", Snap.Events[0].EventId, FString(TEXT("northern_war_begins")));
            TestEqual("knowledge_state", Snap.Events[0].KnowledgeState, FString(TEXT("heard")));
            TestEqual("hop_count", Snap.Events[0].HopCount, 2);
        });

        It("returns invalid snapshot and false on null DataObj (simulates non-2xx)", [this]()
        {
            FNpcStateSnapshot Snap;
            const bool bOk = FNpcEngineJsonUtils::ParseNpcStateSnapshot(nullptr, Snap);
            TestFalse("returns false", bOk);
            TestFalse("bValid is false", Snap.bValid);
        });

        It("returns invalid snapshot on malformed envelope (error field non-null)", [this]()
        {
            const FString BadJson = TEXT(R"json({"data":null,"meta":null,"error":{"code":"NOT_FOUND"}})json");
            TSharedPtr<FJsonObject> Data;
            TestFalse("envelope unwrap fails", FNpcEngineJsonUtils::UnwrapEnvelopeData(BadJson, Data));
            FNpcStateSnapshot Snap;
            TestFalse("parse fails on null data", FNpcEngineJsonUtils::ParseNpcStateSnapshot(Data, Snap));
            TestFalse("bValid false", Snap.bValid);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
