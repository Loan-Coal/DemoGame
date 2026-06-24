// File: NpcWorldSeeder.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec — UNpcWorldSeeder idempotency checks, seed order, halt-on-error.
// Net I/O: no  (injectable mock HTTP fires callbacks synchronously; no live engine required)

#include "Misc/AutomationTest.h"
#include "NpcWorldSeeder.h"
#include "Algo/Count.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcWorldSeederSpec,
    "NpcEngine.Client.WorldSeeder",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

namespace
{
    // Minimal seed JSON with one Location node and no edges — sufficient to test
    // CheckNodeExists + UpsertNode behaviour without loading the real DemoWorld_v1.json.
    const FString MinimalSeedJson = TEXT(
        "{"
        "\"locations\":["
        "  {\"node_type\":\"Location\",\"properties\":{\"id\":\"loc_tavern\",\"name\":\"Test\"}}"
        "],"
        "\"edges\":[]"
        "}"
    );
}

void FNpcWorldSeederSpec::Define()
{
    Describe("Idempotency — CheckNodeExists called before UpsertNode", [this]()
    {
        It("issues GET before any POST for each node", [this]()
        {
            TArray<FString> Verbs;
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [&Verbs](const FString& Verb, const FString& /*Url*/, const FString& /*Body*/,
                         TFunction<void(int32, const FString&)> OnResult)
                {
                    Verbs.Add(Verb);
                    // GET 404 = absent → proceed with POST; POST 200 = success
                    OnResult(Verb == TEXT("GET") ? 404 : 200, TEXT("{\"data\":null}"));
                });

            bool bDone = false;
            Seeder->SeedFromJsonString(
                MinimalSeedJson,
                [&bDone]{ bDone = true; },
                [this](const FString& E){ AddError(FString::Printf(TEXT("Unexpected error: %s"), *E)); });

            TestTrue("seeder completed without error", bDone);
            TestTrue("at least one call was made", Verbs.Num() >= 1);
            TestEqual("very first call is GET (CheckNodeExists precedes UpsertNode)",
                Verbs.Num() > 0 ? Verbs[0] : FString(), FString(TEXT("GET")));
        });

        It("skips UpsertNode POST when CheckNodeExists returns 200 (node already exists)", [this]()
        {
            TArray<FString> Verbs;
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [&Verbs](const FString& Verb, const FString& /*Url*/, const FString& /*Body*/,
                         TFunction<void(int32, const FString&)> OnResult)
                {
                    Verbs.Add(Verb);
                    // GET 200 = node exists → seeder must skip the POST
                    OnResult(200, TEXT("{\"data\":{\"id\":\"loc_tavern\"}}"));
                });

            bool bDone = false;
            Seeder->SeedFromJsonString(
                MinimalSeedJson,
                [&bDone]{ bDone = true; },
                [this](const FString& E){ AddError(FString::Printf(TEXT("Unexpected error: %s"), *E)); });

            const int32 PostCount = Algo::CountIf(Verbs, [](const FString& V){ return V == TEXT("POST"); });
            TestTrue("seeder completed", bDone);
            TestEqual("zero UpsertNode POSTs when all nodes already exist", PostCount, 0);
        });

        It("calls UpsertNode POST when CheckNodeExists returns 404 (node absent)", [this]()
        {
            TArray<FString> Verbs;
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [&Verbs](const FString& Verb, const FString& /*Url*/, const FString& /*Body*/,
                         TFunction<void(int32, const FString&)> OnResult)
                {
                    Verbs.Add(Verb);
                    OnResult(Verb == TEXT("GET") ? 404 : 200, TEXT("{\"data\":null}"));
                });

            bool bDone = false;
            Seeder->SeedFromJsonString(
                MinimalSeedJson,
                [&bDone]{ bDone = true; },
                [this](const FString& E){ AddError(FString::Printf(TEXT("Unexpected error: %s"), *E)); });

            const int32 PostCount = Algo::CountIf(Verbs, [](const FString& V){ return V == TEXT("POST"); });
            TestTrue("seeder completed", bDone);
            TestTrue("at least one UpsertNode POST was made when node is absent", PostCount >= 1);
        });
    });

    Describe("Seed order — locations before characters; nodes before edges", [this]()
    {
        It("processes a Location node before a Character node", [this]()
        {
            // Seed JSON with both a location and a character — location must come first.
            const FString MultiSectionJson = TEXT(
                "{"
                "\"locations\":[{\"node_type\":\"Location\",\"properties\":{\"id\":\"loc_tavern\"}}],"
                "\"characters\":[{\"node_type\":\"Character\",\"properties\":{\"id\":\"mira_innkeeper\"}}],"
                "\"edges\":[]"
                "}"
            );

            TArray<FString> CheckUrls;  // URLs of GET (CheckNodeExists) calls in order
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [&CheckUrls](const FString& Verb, const FString& Url, const FString& /*Body*/,
                              TFunction<void(int32, const FString&)> OnResult)
                {
                    if (Verb == TEXT("GET")) CheckUrls.Add(Url);
                    OnResult(Verb == TEXT("GET") ? 404 : 200, TEXT("{\"data\":null}"));
                });

            bool bDone = false;
            Seeder->SeedFromJsonString(
                MultiSectionJson,
                [&bDone]{ bDone = true; },
                [this](const FString& E){ AddError(FString::Printf(TEXT("Unexpected error: %s"), *E)); });

            // Two GET calls expected: one for loc_tavern, one for mira_innkeeper.
            // The Location URL must appear before the Character URL.
            TestTrue("two CheckNodeExists calls made (one per node)", CheckUrls.Num() == 2);
            TestTrue("first CheckNodeExists targets the Location node",
                CheckUrls.Num() >= 1 && CheckUrls[0].Contains(TEXT("loc_tavern")));
            TestTrue("second CheckNodeExists targets the Character node",
                CheckUrls.Num() >= 2 && CheckUrls[1].Contains(TEXT("mira_innkeeper")));
            TestTrue("seeder completed", bDone);
        });
    });

    Describe("Full pipeline termination — all three phases succeed", [this]()
    {
        It("calls OnDone exactly once when pre-edge nodes, edges, and post-edge nodes all succeed", [this]()
        {
            // Regression: ProcessNodes finishing the post-edge phase with empty Edges previously
            // called ProcessEdges(empty), which called ProcessNodes(empty), looping forever.
            const FString ThreePhaseSeedJson = TEXT(
                "{"
                "\"locations\":[{\"node_type\":\"Location\",\"properties\":{\"id\":\"loc_a\"}}],"
                "\"edges\":["
                "  {\"edge_type\":\"RELATES_TO\",\"src_id\":\"char_a\",\"dst_id\":\"char_b\",\"properties\":{}}"
                "],"
                "\"quests\":[{\"node_type\":\"Quest\",\"properties\":{\"id\":\"quest_a\"}}]"
                "}"
            );

            int32 DoneCount = 0;
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [](const FString& Verb, const FString& /*Url*/, const FString& /*Body*/,
                   TFunction<void(int32, const FString&)> OnResult)
                {
                    // GET = CheckNodeExists returns 404 (absent) → POST will follow.
                    // POST = upsert succeeds.  Edge POST also succeeds.
                    OnResult(Verb == TEXT("GET") ? 404 : 200, TEXT("{\"data\":null}"));
                });

            Seeder->SeedFromJsonString(
                ThreePhaseSeedJson,
                [&DoneCount]{ ++DoneCount; },
                [this](const FString& E){ AddError(FString::Printf(TEXT("Unexpected error: %s"), *E)); });

            TestEqual("OnDone fired exactly once — no infinite recursion", DoneCount, 1);
        });
    });

    Describe("Halt on error", [this]()
    {
        It("fires OnError and stops when the first HTTP call returns non-2xx", [this]()
        {
            int32 TotalCalls = 0;
            bool bErrorFired = false;
            UNpcWorldSeeder* Seeder = NewObject<UNpcWorldSeeder>();
            Seeder->SetHttpExecutorForTesting(
                [&TotalCalls](const FString& /*Verb*/, const FString& /*Url*/, const FString& /*Body*/,
                               TFunction<void(int32, const FString&)> OnResult)
                {
                    ++TotalCalls;
                    OnResult(500, TEXT(""));  // always fail
                });

            Seeder->SeedFromJsonString(
                MinimalSeedJson,
                [this]{ AddError(TEXT("OnComplete must not fire when seeder halted on error")); },
                [&bErrorFired](const FString& /*Err*/){ bErrorFired = true; });

            TestTrue("OnError delegate was fired", bErrorFired);
            TestEqual("processing halted — no further calls after the first failure", TotalCalls, 1);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
