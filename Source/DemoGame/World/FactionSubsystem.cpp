// File: FactionSubsystem.cpp
// Module: DemoGame
// Purpose: Tracks faction standings; updated by relation_deltas for faction-affiliated NPCs.
// Net I/O: no

#include "FactionSubsystem.h"
#include "NpcEngineServiceSubsystem.h"
#include "NpcEngineTypes.h"
#include "PlayerIdProvider.h"
#include "DemoGame.h"
#include "Engine/GameInstance.h"

// ── Greybox NPC → faction membership (DEC-028) ───────────────────────────────
// Based on MEMBER_OF edges in DemoWorld_v1.json: Lira → thieves_guild, Sorn → guard_faction.

static FName GetFactionForNpc(FName InNpcId)
{
    if (InNpcId == NpcId::LiraFence)   return FactionId::ThievesGuild;
    if (InNpcId == NpcId::CaptainSorn) return FactionId::GuardFaction;
    return NAME_None;
}

// ── Lifecycle ────────────────────────────────────────────────────────────────

void UFactionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogDemoGame, Log, TEXT("FactionSubsystem initialised."));
}

void UFactionSubsystem::Deinitialize()
{
    QuestService = nullptr;
    Super::Deinitialize();
}

void UFactionSubsystem::SetQuestService(TScriptInterface<INpcQuestService> InService)
{
    QuestService = InService;
}

INpcQuestService* UFactionSubsystem::ResolveQuestService()
{
    if (QuestService.GetInterface()) return QuestService.GetInterface();

    const UWorld* World = GetWorld();
    UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
    if (UNpcEngineServiceSubsystem* SS =
            GI ? GI->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        QuestService = SS->GetQuestService();
        return QuestService.GetInterface();
    }

    UE_LOG(LogDemoGame, Error,
        TEXT("FactionSubsystem::ResolveQuestService: service unavailable."));
    return nullptr;
}

// ── Public API ───────────────────────────────────────────────────────────────

void UFactionSubsystem::OnNpcRelationUpdated(FName NpcId, int32 TrustDelta)
{
    const FName Faction = GetFactionForNpc(NpcId);
    if (Faction == NAME_None || TrustDelta == 0) return;

    int32& Standing = Standings.FindOrAdd(Faction);
    Standing += TrustDelta;

    UE_LOG(LogDemoGame, Log,
        TEXT("FactionSubsystem: NpcId=%s Faction=%s TrustDelta=%+d NewStanding=%d"),
        *NpcId.ToString(), *Faction.ToString(), TrustDelta, Standing);

    OnFactionStandingChanged.Broadcast(Faction, Standing);
}

void UFactionSubsystem::ExecuteForkChoice(FName QuestId, FName ChoiceId)
{
    INpcQuestService* Service = ResolveQuestService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("FactionSubsystem::ExecuteForkChoice: no service — skipped."));
        return;
    }

    const FString QuestIdStr = QuestId.ToString();
    const FString ChoiceIdStr = ChoiceId.ToString();
    const FString PlayerId = FPlayerIdProvider::GetOrCreatePlayerId();

    Service->QuestChoose(QuestIdStr, PlayerId, ChoiceIdStr,
        [QuestIdStr, ChoiceIdStr](bool bOk)
        {
            UE_LOG(LogDemoGame, Log,
                TEXT("FactionSubsystem: fork choice QuestId=%s ChoiceId=%s Ok=%d"),
                *QuestIdStr, *ChoiceIdStr, bOk ? 1 : 0);
        },
        FOnNpcEngineError::CreateLambda([QuestIdStr, ChoiceIdStr](const FString& Err)
        {
            UE_LOG(LogDemoGame, Error,
                TEXT("FactionSubsystem: QuestChoose error QuestId=%s ChoiceId=%s Error=%s"),
                *QuestIdStr, *ChoiceIdStr, *Err);
        }));
}

int32 UFactionSubsystem::GetStanding(FName InFactionId) const
{
    const int32* Val = Standings.Find(InFactionId);
    return Val ? *Val : 0;
}

void UFactionSubsystem::LoadStandings(const TMap<FName, int32>& Saved)
{
    Standings = Saved;
}
