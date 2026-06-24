// File: NpcEngineJsonUtils.spec.cpp
// Module: NpcEngineClient
// Purpose: Automation Spec for the contract JSON layer — parse, enum forward-compat, serialise.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "NpcEngineJsonUtils.h"
#include "NpcEngineTypes.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FNpcEngineJsonUtilsSpec,
    "NpcEngine.Client.JsonUtils",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

namespace
{
    // A representative raw /v1/dialogue body (Shape A — no OkEnvelope wrapper).
    const FString RawDialogueBody = TEXT(
        "{\"npc_response\":\"Good evening.\","
        "\"relation_deltas\":{\"trust\":1,\"fear\":0,\"affection\":2},"
        "\"mood_update\":null,\"emotion\":null,"
        "\"action\":{\"type\":\"move\",\"target_id\":\"loc_tavern\",\"parameters\":{}},"
        "\"facial_expression\":{\"type\":\"happy\",\"intensity\":40},"
        "\"learned_facts\":[\"likes_player\"],\"memories_recalled\":[],"
        "\"session_id\":\"player_demo:mira_innkeeper\",\"cached\":false,"
        "\"degradation_level\":\"full\",\"audio_bytes\":null}");

    // Same shape but with values the client does NOT know yet (forward-compat).
    const FString ForwardCompatBody = TEXT(
        "{\"npc_response\":\"...\","
        "\"action\":{\"type\":\"teleport\",\"target_id\":\"\",\"parameters\":{}},"
        "\"facial_expression\":{\"type\":\"smug\",\"intensity\":10},"
        "\"session_id\":\"s\",\"cached\":false,\"degradation_level\":\"full\"}");
}

void FNpcEngineJsonUtilsSpec::Define()
{
    Describe("ParseDialogueResponse (raw shape A)", [this]()
    {
        It("populates every modelled field from a well-formed body", [this]()
        {
            FNpcDialogueResponse Out;
            TestTrue("parse succeeds", FNpcEngineJsonUtils::ParseDialogueResponse(RawDialogueBody, Out));

            TestEqual("npc_response", Out.NpcResponse, FString(TEXT("Good evening.")));
            TestEqual("session_id", Out.SessionId, FString(TEXT("player_demo:mira_innkeeper")));
            TestEqual("degradation_level", Out.DegradationLevel, FString(TEXT("full")));
            TestFalse("not a client fallback", Out.bIsFallback);
            TestFalse("not cached", Out.bCached);

            TestEqual("relation trust", Out.RelationDeltas.Trust, 1);
            TestEqual("relation affection", Out.RelationDeltas.Affection, 2);

            TestEqual("action type", Out.Action.Type, ENpcActionType::Move);
            TestEqual("action target", Out.Action.TargetId, FString(TEXT("loc_tavern")));

            TestEqual("facial type", Out.FacialExpression.Type, ENpcFacialExpression::Happy);
            TestEqual("facial intensity", Out.FacialExpression.Intensity, 40);

            TestEqual("learned facts count", Out.LearnedFacts.Num(), 1);
        });

        It("returns false on malformed JSON", [this]()
        {
            FNpcDialogueResponse Out;
            TestFalse("garbage rejected", FNpcEngineJsonUtils::ParseDialogueResponse(TEXT("{not json"), Out));
        });
    });

    Describe("Enum forward-compatibility", [this]()
    {
        It("maps known action strings", [this]()
        {
            TestEqual("speak", FNpcEngineJsonUtils::ActionTypeFromString(TEXT("speak")), ENpcActionType::Speak);
            TestEqual("move", FNpcEngineJsonUtils::ActionTypeFromString(TEXT("move")), ENpcActionType::Move);
            TestEqual("attack", FNpcEngineJsonUtils::ActionTypeFromString(TEXT("attack")), ENpcActionType::Attack);
        });

        It("falls back to Speak on an unknown action (never crash, never drop)", [this]()
        {
            TestEqual("unknown->speak",
                FNpcEngineJsonUtils::ActionTypeFromString(TEXT("teleport")), ENpcActionType::Speak);
        });

        It("maps known expression strings", [this]()
        {
            TestEqual("neutral", FNpcEngineJsonUtils::FacialExpressionFromString(TEXT("neutral")), ENpcFacialExpression::Neutral);
            TestEqual("angry", FNpcEngineJsonUtils::FacialExpressionFromString(TEXT("angry")), ENpcFacialExpression::Angry);
        });

        It("falls back to Neutral on an unknown expression", [this]()
        {
            TestEqual("unknown->neutral",
                FNpcEngineJsonUtils::FacialExpressionFromString(TEXT("smug")), ENpcFacialExpression::Neutral);
        });

        It("parses a body full of unknown enum values without failing", [this]()
        {
            FNpcDialogueResponse Out;
            TestTrue("parse still succeeds", FNpcEngineJsonUtils::ParseDialogueResponse(ForwardCompatBody, Out));
            TestEqual("unknown action coerced to Speak", Out.Action.Type, ENpcActionType::Speak);
            TestEqual("unknown expression coerced to Neutral", Out.FacialExpression.Type, ENpcFacialExpression::Neutral);
        });
    });

    Describe("SerialiseDialogueRequest", [this]()
    {
        It("includes the three required contract fields", [this]()
        {
            FNpcDialogueRequest Req;
            Req.PlayerId = TEXT("player_demo");
            Req.NpcId = TEXT("mira_innkeeper");
            Req.PlayerMessage = TEXT("Hello there.");

            const FString Json = FNpcEngineJsonUtils::SerialiseDialogueRequest(Req);
            TestTrue("has player_id", Json.Contains(TEXT("player_demo")));
            TestTrue("has npc_id", Json.Contains(TEXT("mira_innkeeper")));
            TestTrue("has player_message", Json.Contains(TEXT("Hello there.")));
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
