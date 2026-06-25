// File: GossipCache.spec.cpp
// Module: DemoGame
// Purpose: Automation Spec — GossipCacheSubsystem storage, ordering, and spoke-to-NPC gate.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "World/GossipCacheSubsystem.h"
#include "NpcEngineTypes.h"

#if WITH_DEV_AUTOMATION_TESTS

DEFINE_SPEC(
    FGossipCacheSpec,
    "NpcEngine.Gameplay.GossipCache",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FGossipCacheSpec::Define()
{
    Describe("AddGossipEntry", [this]()
    {
        It("stores a FGossipEntry retrievable by GetChainForEvent", [this]()
        {
            UGossipCacheSubsystem* Cache = NewObject<UGossipCacheSubsystem>();
            Cache->AddGossipEntry(NpcId::CaptainSorn, GossipEventId::NorthernWarBegins, 0,
                FText::FromString(TEXT("There was a skirmish up north.")));

            const TArray<FGossipEntry> Chain =
                Cache->GetChainForEvent(GossipEventId::NorthernWarBegins);
            TestEqual("one entry returned", Chain.Num(), 1);
            TestEqual("source npc id", Chain[0].SourceNpcId, NpcId::CaptainSorn);
            TestEqual("hop count", Chain[0].HopCount, 0);
        });
    });

    Describe("GetChainForEvent", [this]()
    {
        It("returns entries in HopCount ascending order", [this]()
        {
            UGossipCacheSubsystem* Cache = NewObject<UGossipCacheSubsystem>();
            Cache->AddGossipEntry(NpcId::OldHenryk,    GossipEventId::NorthernWarBegins, 2,
                FText::FromString(TEXT("The gods have turned against the northern army!")));
            Cache->AddGossipEntry(NpcId::CaptainSorn,  GossipEventId::NorthernWarBegins, 0,
                FText::FromString(TEXT("A minor skirmish at the north pass.")));
            Cache->AddGossipEntry(NpcId::MiraInnkeeper, GossipEventId::NorthernWarBegins, 1,
                FText::FromString(TEXT("Sorn says there was fighting up north.")));

            const TArray<FGossipEntry> Chain =
                Cache->GetChainForEvent(GossipEventId::NorthernWarBegins);
            TestEqual("three entries", Chain.Num(), 3);
            TestTrue("hop 0 first",  Chain[0].HopCount == 0);
            TestTrue("hop 1 second", Chain[1].HopCount == 1);
            TestTrue("hop 2 third",  Chain[2].HopCount == 2);
        });
    });

    Describe("MarkPlayerSpokeToNpc", [this]()
    {
        It("sets bPlayerSpokeToNpc on matching entries after being called", [this]()
        {
            UGossipCacheSubsystem* Cache = NewObject<UGossipCacheSubsystem>();
            Cache->AddGossipEntry(NpcId::CaptainSorn, GossipEventId::NorthernWarBegins, 0,
                FText::FromString(TEXT("A minor skirmish.")));

            TArray<FGossipEntry> Before =
                Cache->GetChainForEvent(GossipEventId::NorthernWarBegins);
            TestFalse("spoke flag false before", Before[0].bPlayerSpokeToNpc);

            Cache->MarkPlayerSpokeToNpc(NpcId::CaptainSorn);

            TArray<FGossipEntry> After =
                Cache->GetChainForEvent(GossipEventId::NorthernWarBegins);
            TestTrue("spoke flag true after", After[0].bPlayerSpokeToNpc);
        });
    });
}

#endif // WITH_DEV_AUTOMATION_TESTS
