// File: DialogueComponent.cpp
// Module: Game
// Purpose: Per-NPC actor component owning dialogue session state, trust accumulation, and fallback lookup.
// Net I/O: no

#include "DialogueComponent.h"
#include "NpcActorBase.h"
#include "NpcFallbackLinesAsset.h"
#include "NpcFallbackDefaults.h"
#include "DialogueManager.h"
#include "NpcEngineServiceSubsystem.h"
#include "PlayerIdProvider.h"
#include "World/GossipCacheSubsystem.h"
#include "DemoGame.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

UDialogueComponent::UDialogueComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

// ── Public API ────────────────────────────────────────────────────────────────

void UDialogueComponent::StartDialogue(APlayerController* PC)
{
    const FName NpcId = GetOwnerNpcId();
    if (NpcId.IsNone())
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("DialogueComponent: owner NpcId is not set — dialogue aborted."));
        return;
    }

    SessionId.Empty();
    AccumulatedTrust = 0;

    if (UWorld* World = GetWorld())
    {
        if (UDialogueManagerSubsystem* DM = World->GetSubsystem<UDialogueManagerSubsystem>())
        {
            if (ANpcActorBase* Npc = Cast<ANpcActorBase>(GetOwner()))
            {
                DM->BeginDialogue(Npc);
            }
        }
    }

    UE_LOG(LogDemoGame, Log,
        TEXT("DialogueComponent: session started NpcId=%s"), *NpcId.ToString());
}

void UDialogueComponent::SubmitMessage(const FString& PlayerMessage)
{
    if (PlayerMessage.IsEmpty())
    {
        UE_LOG(LogDemoGame, Verbose,
            TEXT("DialogueComponent: SubmitMessage rejected — empty message."));
        return;
    }
    if (PlayerMessage.Len() > NpcEngine::MaxPlayerMessageChars)
    {
        UE_LOG(LogDemoGame, Verbose,
            TEXT("DialogueComponent: SubmitMessage rejected — message too long (%d/%d)."),
            PlayerMessage.Len(), NpcEngine::MaxPlayerMessageChars);
        return;
    }

    INpcDialogueService* Service = ResolveService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Error,
            TEXT("DialogueComponent: no dialogue service available; firing fallback."));
        HandleError(TEXT("Dialogue service unavailable."));
        return;
    }

    const FNpcDialogueRequest Request = BuildRequest(PlayerMessage, GetOwnerNpcId());
    SendToService(Request, Service);
}

FNpcDialogueRequest UDialogueComponent::BuildRequest(
    const FString& PlayerMessage, FName NpcId) const
{
    FNpcDialogueRequest Request;
    Request.PlayerId      = FPlayerIdProvider::GetOrCreatePlayerId();
    Request.NpcId         = NpcId.ToString();
    Request.PlayerMessage = PlayerMessage;
    Request.SessionId     = SessionId;

    if (const ANpcActorBase* Npc = Cast<ANpcActorBase>(GetOwner()))
    {
        Request.LocationId = Npc->LocationId;
    }
    return Request;
}

void UDialogueComponent::SendToService(
    const FNpcDialogueRequest& Request, INpcDialogueService* Service)
{
    TWeakObjectPtr<UDialogueComponent> WeakThis = this;

    FOnNpcDialogueComplete SuccessDelegate;
    SuccessDelegate.BindLambda([WeakThis](const FNpcDialogueResponse& Response)
    {
        if (UDialogueComponent* Self = WeakThis.Get())
        {
            Self->HandleResponse(Response);
        }
    });

    FOnNpcEngineError ErrorDelegate;
    ErrorDelegate.BindLambda([WeakThis](const FString& Error)
    {
        if (UDialogueComponent* Self = WeakThis.Get())
        {
            Self->HandleError(Error);
        }
    });

    Service->SendDialogue(Request, SuccessDelegate, ErrorDelegate);
}

void UDialogueComponent::SetDialogueService(TScriptInterface<INpcDialogueService> InService)
{
    DialogueService = InService;
}

// ── Private helpers ───────────────────────────────────────────────────────────

INpcDialogueService* UDialogueComponent::ResolveService()
{
    if (DialogueService.GetInterface())
    {
        return DialogueService.GetInterface();
    }

    const UWorld* World = GetWorld();
    UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
    if (UNpcEngineServiceSubsystem* Sub =
            GI ? GI->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        DialogueService = Sub->GetDialogueService();
        return DialogueService.GetInterface();
    }

    return nullptr;
}

FName UDialogueComponent::GetOwnerNpcId() const
{
    const ANpcActorBase* Npc = Cast<ANpcActorBase>(GetOwner());
    return Npc ? Npc->NpcId : NAME_None;
}

void UDialogueComponent::HandleResponse(const FNpcDialogueResponse& Response)
{
    const FName NpcId = GetOwnerNpcId();

    // Persist session_id for conversation continuity.
    if (!Response.SessionId.IsEmpty())
    {
        SessionId = Response.SessionId;
    }

    // Accumulate trust.
    AccumulatedTrust += Response.RelationDeltas.Trust;

    // Fire per-NPC delegates.
    OnTrustChanged.Broadcast(NpcId, Response.RelationDeltas);

    if (Response.MemoriesRecalled.Num() > 0)
    {
        OnMemoriesRecalled.Broadcast(NpcId, Response.MemoriesRecalled);
    }

    OnFacialExpression.Broadcast(NpcId,
        Response.FacialExpression.Type, Response.FacialExpression.Intensity);

    if (Response.DegradationLevel != TEXT("full"))
    {
        UE_LOG(LogDemoGame, Log,
            TEXT("DialogueComponent: Degradation=%s NpcId=%s"),
            *Response.DegradationLevel, *NpcId.ToString());
    }

    NotifyManagerOfResponse(NpcId, Response);
    NotifyGossipCache(NpcId, Response);
}

void UDialogueComponent::NotifyManagerOfResponse(
    FName NpcId, const FNpcDialogueResponse& Response)
{
    UWorld* World = GetWorld();
    UDialogueManagerSubsystem* DM = World
        ? World->GetSubsystem<UDialogueManagerSubsystem>()
        : nullptr;
    if (!DM)
    {
        return;
    }

    const FString DisplayName = [this]() -> FString
    {
        if (const ANpcActorBase* Npc = Cast<ANpcActorBase>(GetOwner()))
        {
            return Npc->DisplayName;
        }
        return TEXT("NPC");
    }();

    DM->NotifyNpcResponse(Response.NpcResponse, DisplayName);
    DM->NotifyRelationshipChanged(NpcId, Response.RelationDeltas);
    if (Response.MemoriesRecalled.Num() > 0)
    {
        DM->NotifyMemoriesRecalled(NpcId, Response.MemoriesRecalled);
    }
    DM->NotifyFacialExpression(NpcId,
        Response.FacialExpression.Type, Response.FacialExpression.Intensity);
}

void UDialogueComponent::NotifyGossipCache(
    FName NpcId, const FNpcDialogueResponse& Response)
{
    UWorld* World = GetWorld();
    UGossipCacheSubsystem* Gossip = World ? World->GetSubsystem<UGossipCacheSubsystem>() : nullptr;
    if (!Gossip) return;

    Gossip->MarkPlayerSpokeToNpc(NpcId);

    // Check learned_facts for war event — add gossip entry for this NPC's hop.
    const FString WarEventKey = GossipEventId::NorthernWarBegins.ToString();
    for (const FString& Fact : Response.LearnedFacts)
    {
        if (Fact.Contains(WarEventKey))
        {
            Gossip->MarkGossipFromDialogue(NpcId, GossipEventId::NorthernWarBegins);
            break;
        }
    }
}

void UDialogueComponent::HandleError(const FString& Error)
{
    const FName NpcId = GetOwnerNpcId();

    UE_LOG(LogDemoGame, Warning,
        TEXT("DialogueComponent: engine error NpcId=%s Error=%s"),
        *NpcId.ToString(), *Error);

    FText FallbackText;
    if (FallbackLinesAsset)
    {
        FallbackText = FallbackLinesAsset->GetFallbackLine(NpcId);
    }
    // Zero-setup default: if no DataAsset (or no entry for this NPC), use the built-in line.
    if (FallbackText.IsEmpty())
    {
        FallbackText = NpcFallbackDefaults::GetLine(NpcId);
    }

    OnFallbackLine.Broadcast(NpcId, FallbackText);

    // Also notify the manager for widget fallback display.
    if (UWorld* World = GetWorld())
    {
        if (UDialogueManagerSubsystem* DM = World->GetSubsystem<UDialogueManagerSubsystem>())
        {
            DM->NotifyDialogueError(FallbackText.IsEmpty() ? Error : FallbackText.ToString());
        }
    }
}
