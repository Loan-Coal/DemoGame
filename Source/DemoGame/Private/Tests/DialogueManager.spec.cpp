// File: DialogueManager.spec.cpp
// Module: DemoGame
// Purpose: Automation Spec — DialogueManager DIP wiring: injected service, success/error, session continuity.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "DialogueManager.h"
#include "NpcDialogueService.h"
#include "NpcEngineTypes.h"
#include "FakeNpcDialogueService.h"
#include "TestNpcActor.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FDialogueManagerSpec,
    "NpcEngine.Game.DialogueManager",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

namespace
{
    UDialogueManagerSubsystem* MakeManager(UFakeNpcDialogueService* Service)
    {
        UDialogueManagerSubsystem* DM = NewObject<UDialogueManagerSubsystem>(GetTransientPackage());
        DM->SetDialogueService(Service);   // bypass the GI composition root — no world needed
        return DM;
    }

    ATestNpcActor* MakeNpc()
    {
        ATestNpcActor* Npc = NewObject<ATestNpcActor>(GetTransientPackage());
        Npc->NpcId = FName(TEXT("test_npc"));
        Npc->LocationId = TEXT("loc_test");
        Npc->DisplayName = TEXT("Tester");
        return Npc;
    }
}

void FDialogueManagerSpec::Define()
{
    Describe("SubmitPlayerMessage with an injected service", [this]()
    {
        It("broadcasts OnNpcSpoke with the canned response on success", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = true;
            Fake->CannedResponse.NpcResponse = TEXT("Hello, traveller.");
            UDialogueManagerSubsystem* DM = MakeManager(Fake);

            ATestNpcActor* Npc = MakeNpc();
            URecorder* Rec = NewObject<URecorder>();
            DM->OnNpcSpoke.AddDynamic(Rec, &URecorder::OnSpoke);

            DM->BeginDialogue(Npc);
            DM->SubmitPlayerMessage(TEXT("Good evening."));

            TestEqual("service called once", Fake->SendDialogueCallCount, 1);
            TestEqual("request NpcId", Fake->LastRequest.NpcId, FString(TEXT("test_npc")));
            TestEqual("request LocationId", Fake->LastRequest.LocationId, FString(TEXT("loc_test")));
            TestEqual("request message", Fake->LastRequest.PlayerMessage, FString(TEXT("Good evening.")));
            TestTrue("OnNpcSpoke fired", Rec->bSpokeFired);
            TestEqual("spoken line", Rec->LastResponse, FString(TEXT("Hello, traveller.")));
            TestEqual("display name", Rec->LastName, FString(TEXT("Tester")));
        });

        It("broadcasts OnDialogueError on failure", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->bShouldSucceed = false;
            Fake->CannedError = TEXT("boom");
            UDialogueManagerSubsystem* DM = MakeManager(Fake);

            ATestNpcActor* Npc = MakeNpc();
            URecorder* Rec = NewObject<URecorder>();
            DM->OnDialogueError.AddDynamic(Rec, &URecorder::OnError);

            DM->BeginDialogue(Npc);
            DM->SubmitPlayerMessage(TEXT("Hi"));

            TestTrue("OnDialogueError fired", Rec->bErrorFired);
            TestEqual("error text", Rec->LastError, FString(TEXT("boom")));
        });

        It("does nothing when not in dialogue", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            UDialogueManagerSubsystem* DM = MakeManager(Fake);

            DM->SubmitPlayerMessage(TEXT("nobody is listening"));

            TestEqual("service not called", Fake->SendDialogueCallCount, 0);
        });

        It("carries session_id across turns", [this]()
        {
            UFakeNpcDialogueService* Fake = NewObject<UFakeNpcDialogueService>();
            Fake->CannedResponse.SessionId = TEXT("sess-42");
            UDialogueManagerSubsystem* DM = MakeManager(Fake);

            ATestNpcActor* Npc = MakeNpc();
            DM->BeginDialogue(Npc);

            DM->SubmitPlayerMessage(TEXT("first"));
            TestEqual("first turn sends empty session", Fake->LastRequest.SessionId, FString());

            DM->SubmitPlayerMessage(TEXT("second"));
            TestEqual("second turn carries session", Fake->LastRequest.SessionId, FString(TEXT("sess-42")));
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
