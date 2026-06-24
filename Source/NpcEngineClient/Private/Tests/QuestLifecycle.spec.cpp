// File: QuestLifecycle.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec — quest lifecycle JSON body serialisation contract. DEC-027.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NpcEngineJsonUtils.h"
#include "NpcQuestTypes.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FQuestLifecycleSpec,
    "NpcEngine.Client.QuestLifecycle",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FQuestLifecycleSpec::Define()
{
    Describe("SerialiseQuestOffer", [this]()
    {
        It("body contains quest_id, player_id, title, objectives keys", [this]()
        {
            FQuestOfferRequest Req;
            Req.QuestId   = TEXT("find_wine_merchant");
            Req.PlayerId  = TEXT("player_demo");
            Req.Title     = TEXT("Find the Wine Merchant");
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestOffer(Req);
            TestTrue("quest_id",   Json.Contains(TEXT("quest_id")));
            TestTrue("player_id",  Json.Contains(TEXT("player_id")));
            TestTrue("title",      Json.Contains(TEXT("title")));
            TestTrue("objectives", Json.Contains(TEXT("objectives")));
        });

        It("objective sub-object contains required fields", [this]()
        {
            FQuestOfferRequest Req;
            Req.QuestId  = TEXT("find_wine_merchant");
            Req.PlayerId = TEXT("player_demo");
            Req.Title    = TEXT("Find the Wine Merchant");
            FQuestObjectiveData Obj;
            Obj.ObjectiveId = TEXT("speak_to_mira");
            Obj.Description = TEXT("Speak to Mira about Aldric.");
            Obj.RequiredProgress = 1;
            Req.Objectives.Add(Obj);
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestOffer(Req);
            TestTrue("objective_id",       Json.Contains(TEXT("objective_id")));
            TestTrue("description",        Json.Contains(TEXT("description")));
            TestTrue("required_progress",  Json.Contains(TEXT("required_progress")));
        });

        It("produces valid JSON", [this]()
        {
            FQuestOfferRequest Req;
            Req.QuestId  = TEXT("find_wine_merchant");
            Req.PlayerId = TEXT("player_demo");
            Req.Title    = TEXT("Test");
            TSharedPtr<FJsonObject> Obj;
            TSharedRef<TJsonReader<>> Reader =
                TJsonReaderFactory<>::Create(FNpcEngineJsonUtils::SerialiseQuestOffer(Req));
            TestTrue("parses", FJsonSerializer::Deserialize(Reader, Obj));
            TestNotNull("root", Obj.Get());
        });
    });

    Describe("SerialiseQuestAccept", [this]()
    {
        It("body contains quest_id and player_id", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestAccept(
                TEXT("find_wine_merchant"), TEXT("player_demo"));
            TestTrue("quest_id",  Json.Contains(TEXT("quest_id")));
            TestTrue("player_id", Json.Contains(TEXT("player_id")));
        });
    });

    Describe("SerialiseQuestObjective", [this]()
    {
        It("body contains all four required fields", [this]()
        {
            FQuestObjectiveRequest Req;
            Req.QuestId     = TEXT("find_wine_merchant");
            Req.PlayerId    = TEXT("player_demo");
            Req.ObjectiveId = TEXT("speak_to_mira");
            Req.ProgressDelta = 1;
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestObjective(Req);
            TestTrue("quest_id",      Json.Contains(TEXT("quest_id")));
            TestTrue("player_id",     Json.Contains(TEXT("player_id")));
            TestTrue("objective_id",  Json.Contains(TEXT("objective_id")));
            TestTrue("progress_delta",Json.Contains(TEXT("progress_delta")));
        });
    });

    Describe("SerialiseQuestEvaluate", [this]()
    {
        It("body contains quest_id and player_id", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestEvaluate(
                TEXT("find_wine_merchant"), TEXT("player_demo"));
            TestTrue("quest_id",  Json.Contains(TEXT("quest_id")));
            TestTrue("player_id", Json.Contains(TEXT("player_id")));
        });
    });

    Describe("SerialiseQuestReward", [this]()
    {
        It("body contains quest_id and player_id", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestReward(
                TEXT("find_wine_merchant"), TEXT("player_demo"));
            TestTrue("quest_id",  Json.Contains(TEXT("quest_id")));
            TestTrue("player_id", Json.Contains(TEXT("player_id")));
        });
    });

    Describe("SerialiseQuestChoose", [this]()
    {
        It("body contains player_id and choice_id but NOT quest_id (quest_id is in the URL path)", [this]()
        {
            const FString Json = FNpcEngineJsonUtils::SerialiseQuestChoose(
                TEXT("player_demo"), TEXT("deliver_to_merchant"));
            TestTrue("player_id",  Json.Contains(TEXT("player_id")));
            TestTrue("choice_id",  Json.Contains(TEXT("choice_id")));
            // quest_id goes in the URL path — must NOT appear in the body.
            TestFalse("no quest_id in body", Json.Contains(TEXT("quest_id")));
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
