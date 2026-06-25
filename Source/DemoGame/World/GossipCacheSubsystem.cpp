// File: GossipCacheSubsystem.cpp
// Module: DemoGame
// Purpose: Caches gossip chain entries for the Rumor Journal; polls NPC state after each tick.
// Net I/O: no

#include "GossipCacheSubsystem.h"
#include "NpcWorldSubsystem.h"
#include "NpcEngineServiceSubsystem.h"
#include "NpcEngineTypes.h"
#include "DemoGame.h"
#include "Engine/GameInstance.h"

// Authored distortion texts (seed §7.2). Keyed by (NpcId, EventId).
// Greybox constants — finalised via seed in Phase 10.
namespace GossipText
{
    static const FText SornFirsthand = FText::FromString(
        TEXT("There was a skirmish at the north pass. My men are still waiting for orders."));
    static const FText MiraRumor = FText::FromString(
        TEXT("Sorn told me fighting broke out up north. He seemed worried about something."));
    static const FText HenrykDistorted = FText::FromString(
        TEXT("The gods themselves struck down the northern garrison! Hundreds dead, they say!"));
}

// ── Lifecycle ─────────────────────────────────────────────────────────────────

void UGossipCacheSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (UNpcWorldSubsystem* World = GetWorld()->GetSubsystem<UNpcWorldSubsystem>())
    {
        World->OnTickAdvanced.AddDynamic(this, &UGossipCacheSubsystem::OnTickAdvanced);
    }

    UE_LOG(LogDemoGame, Log, TEXT("GossipCacheSubsystem initialised."));
}

void UGossipCacheSubsystem::Deinitialize()
{
    if (UNpcWorldSubsystem* World = GetWorld() ? GetWorld()->GetSubsystem<UNpcWorldSubsystem>() : nullptr)
    {
        World->OnTickAdvanced.RemoveDynamic(this, &UGossipCacheSubsystem::OnTickAdvanced);
    }
    DialogueService = nullptr;
    Super::Deinitialize();
}

// ── Service resolution ────────────────────────────────────────────────────────

void UGossipCacheSubsystem::SetDialogueService(TScriptInterface<INpcDialogueService> InService)
{
    DialogueService = InService;
}

INpcDialogueService* UGossipCacheSubsystem::ResolveService()
{
    if (DialogueService.GetInterface()) return DialogueService.GetInterface();

    const UWorld* W = GetWorld();
    UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
    if (auto* SS = GI ? GI->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        DialogueService = SS->GetDialogueService();
        return DialogueService.GetInterface();
    }
    return nullptr;
}

// ── Public API ────────────────────────────────────────────────────────────────

void UGossipCacheSubsystem::AddGossipEntry(
    FName SourceNpcId, FName EventId, int32 HopCount, FText DistortionText)
{
    // Dedup on (SourceNpcId, EventId) — update hop/text if already present.
    for (FGossipEntry& E : Entries)
    {
        if (E.SourceNpcId == SourceNpcId && E.EventId == EventId)
        {
            E.HopCount = HopCount;
            E.DistortionText = DistortionText;
            return;
        }
    }
    FGossipEntry New;
    New.SourceNpcId    = SourceNpcId;
    New.EventId        = EventId;
    New.HopCount       = HopCount;
    New.DistortionText = DistortionText;
    Entries.Add(New);
}

void UGossipCacheSubsystem::MarkPlayerSpokeToNpc(FName NpcId)
{
    for (FGossipEntry& E : Entries)
    {
        if (E.SourceNpcId == NpcId)
        {
            E.bPlayerSpokeToNpc = true;
        }
    }
}

TArray<FGossipEntry> UGossipCacheSubsystem::GetChainForEvent(FName EventId) const
{
    TArray<FGossipEntry> Result;
    for (const FGossipEntry& E : Entries)
    {
        if (E.EventId == EventId) Result.Add(E);
    }
    Result.Sort([](const FGossipEntry& A, const FGossipEntry& B)
    {
        return A.HopCount < B.HopCount;
    });
    return Result;
}

void UGossipCacheSubsystem::MarkGossipFromDialogue(FName SourceNpcId, FName EventId)
{
    // Map each NPC to its authored hop position and text (greybox — finalised in Phase 10).
    if (SourceNpcId == NpcId::CaptainSorn && EventId == GossipEventId::NorthernWarBegins)
    {
        AddGossipEntry(NpcId::CaptainSorn, EventId, 0, GossipText::SornFirsthand);
    }
    else if (SourceNpcId == NpcId::MiraInnkeeper && EventId == GossipEventId::NorthernWarBegins)
    {
        AddGossipEntry(NpcId::MiraInnkeeper, EventId, 1, GossipText::MiraRumor);
    }
}

// ── Tick polling ──────────────────────────────────────────────────────────────

void UGossipCacheSubsystem::OnTickAdvanced(FName /*NewLocationId*/, int32 /*TickCount*/)
{
    PollHenrykState();
}

void UGossipCacheSubsystem::PollHenrykState()
{
    INpcDialogueService* Service = ResolveService();
    if (!Service) return;

    Service->GetNpcState(
        NpcId::OldHenryk.ToString(),
        [this](const FNpcStateSnapshot& Snap)
        {
            if (!Snap.bValid) return;

            for (const FNpcEventEntry& Ev : Snap.Events)
            {
                if (Ev.EventId == GossipEventId::NorthernWarBegins.ToString()
                    && !Ev.KnowledgeState.IsEmpty())
                {
                    // Henryk has some knowledge of the war event — ensure his hop entry is present.
                    AddGossipEntry(
                        NpcId::OldHenryk,
                        GossipEventId::NorthernWarBegins,
                        2,
                        GossipText::HenrykDistorted);
                    return;
                }
            }
        },
        FOnNpcEngineError::CreateLambda([](const FString& Err)
        {
            UE_LOG(LogDemoGame, Warning,
                TEXT("GossipCacheSubsystem: GetNpcState failed Error=%s"), *Err);
        }));
}
