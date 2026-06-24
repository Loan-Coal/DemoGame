// File: DialogueComponent.spec.cpp
// Module: Game
// Purpose: Automation Spec — UDialogueComponent input validation, fallback-line firing, trust accumulation.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "DialogueComponent.h"
#include "NpcEngineTypes.h"
#include "NpcFallbackLinesAsset.h"
#include "FakeNpcDialogueService.h"
#include "TestNpcActor.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FDialogueComponentSpec,
    "NpcEngine.Game.DialogueComponent",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

namespace
{
    /** Create a component owned by a test NPC with the given npc_id. */
    UDialogueComponent* MakeComponent(FName NpcId = FName("test_npc"))
    {
        ATestNpcActor* Npc = NewObject<ATestNpcActor>(GetTransientPackage());
        Npc->NpcId = NpcId;
        return NewObject<UDialogueComponent>(Npc);
    }

    UNpcFallbackLinesAsset* MakeFallbackAsset(FName NpcId = FName("test_npc"),
        const FString& LineStr = TEXT("...test_npc seems distracted."))
    {
        UNpcFallbackLinesAsset* Asset = NewObject<UNpcFallbackLinesAsset>(GetTransientPackage());
        Asset->FallbackLineByNpcId.Add(NpcId, FText::FromString(LineStr));
        return Asset;
    }
}

void FDialogueComponentSpec::Define()
{
    Describe("SubmitMessage — client-side validation", [this]()
    {
        It("rejects empty string: no HTTP call, no delegate fires", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UDialogueComponent* Comp = MakeComponent();
            Comp->SetDialogueService(Fake);
            Comp->FallbackLinesAsset = MakeFallbackAsset();

            UFallbackRecorder* Rec = NewObject<UFallbackRecorder>();
            Comp->OnFallbackLine.AddDynamic(Rec, &UFallbackRecorder::OnFallback);

            Comp->SubmitMessage(TEXT(""));

            TestEqual("service not called", Fake->SendDialogueCallCount, 0);
            TestFalse("OnFallbackLine not fired", Rec->bFired);
        });

        It("rejects message over NpcEngine::MaxPlayerMessageChars: no HTTP call, no delegate fires", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UDialogueComponent* Comp = MakeComponent();
            Comp->SetDialogueService(Fake);

            UFallbackRecorder* Rec = NewObject<UFallbackRecorder>();
            Comp->OnFallbackLine.AddDynamic(Rec, &UFallbackRecorder::OnFallback);

            FString Oversized = FString::ChrN(NpcEngine::MaxPlayerMessageChars + 1, TEXT('x'));
            Comp->SubmitMessage(Oversized);

            TestEqual("service not called", Fake->SendDialogueCallCount, 0);
            TestFalse("OnFallbackLine not fired", Rec->bFired);
        });
    });

    Describe("SubmitMessage — fallback on engine error (LSP)", [this]()
    {
        It("fires OnFallbackLine with NPC-specific text when the service returns an error", [this]()
        {
            // Mock fires OnError — matching real client non-2xx behaviour (LSP).
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = false;
            Fake->CannedError = TEXT("engine unavailable");

            const FString ExpectedStr = TEXT("...test_npc seems distracted.");
            UNpcFallbackLinesAsset* Asset = MakeFallbackAsset(FName("test_npc"), ExpectedStr);

            UDialogueComponent* Comp = MakeComponent(FName("test_npc"));
            Comp->SetDialogueService(Fake);
            Comp->FallbackLinesAsset = Asset;

            UFallbackRecorder* Rec = NewObject<UFallbackRecorder>();
            Comp->OnFallbackLine.AddDynamic(Rec, &UFallbackRecorder::OnFallback);

            Comp->SubmitMessage(TEXT("Good evening."));

            TestEqual("service was called", Fake->SendDialogueCallCount, 1);
            TestTrue("OnFallbackLine fired", Rec->bFired);
            TestEqual("NpcId matches owner", Rec->LastNpcId, FName("test_npc"));
            TestEqual("fallback text matches authored line",
                Rec->LastText.ToString(), ExpectedStr);
        });

        It("fires OnFallbackLine even when FallbackLinesAsset has no entry for NpcId", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = false;

            UNpcFallbackLinesAsset* Asset = NewObject<UNpcFallbackLinesAsset>(GetTransientPackage());
            // Intentionally empty — no entry for "unknown_npc".

            UDialogueComponent* Comp = MakeComponent(FName("unknown_npc"));
            Comp->SetDialogueService(Fake);
            Comp->FallbackLinesAsset = Asset;

            UFallbackRecorder* Rec = NewObject<UFallbackRecorder>();
            Comp->OnFallbackLine.AddDynamic(Rec, &UFallbackRecorder::OnFallback);

            Comp->SubmitMessage(TEXT("Hello."));

            TestTrue("OnFallbackLine still fires with empty text", Rec->bFired);
            TestEqual("NpcId matches owner", Rec->LastNpcId, FName("unknown_npc"));
        });
    });

    Describe("SubmitMessage — trust accumulation on success", [this]()
    {
        It("fires OnTrustChanged and updates AccumulatedTrust on successful response", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = true;
            Fake->CannedResponse.RelationDeltas.Trust = 5;
            Fake->CannedResponse.RelationDeltas.Fear = -2;

            UDialogueComponent* Comp = MakeComponent();
            Comp->SetDialogueService(Fake);

            UTrustRecorder* Rec = NewObject<UTrustRecorder>();
            Comp->OnTrustChanged.AddDynamic(Rec, &UTrustRecorder::OnTrust);

            Comp->SubmitMessage(TEXT("Good evening."));

            TestTrue("OnTrustChanged fired", Rec->bFired);
            TestEqual("trust delta", Rec->LastDeltas.Trust, 5);
            TestEqual("fear delta", Rec->LastDeltas.Fear, -2);
            TestEqual("AccumulatedTrust updated", Comp->AccumulatedTrust, 5);
        });

        It("accumulates trust across multiple turns", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = true;
            Fake->CannedResponse.RelationDeltas.Trust = 3;

            UDialogueComponent* Comp = MakeComponent();
            Comp->SetDialogueService(Fake);

            Comp->SubmitMessage(TEXT("First turn."));
            Comp->SubmitMessage(TEXT("Second turn."));

            TestEqual("AccumulatedTrust sums across turns", Comp->AccumulatedTrust, 6);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
