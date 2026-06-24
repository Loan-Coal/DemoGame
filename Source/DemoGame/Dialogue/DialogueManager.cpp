#include "DialogueManager.h"
#include "NpcActorBase.h"
#include "DemoGame.h"
#include "NpcDialogueService.h"
#include "NpcEngineServiceSubsystem.h"
#include "NpcEngineTypes.h"
#include "PlayerIdProvider.h"
#include "Engine/GameInstance.h"

void UDialogueManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // The service is resolved lazily on first use (from the GameInstance composition root), so we
    // never reference the concrete client here. Tests inject a fake via SetDialogueService().
    UE_LOG(LogDemoGame, Log, TEXT("DialogueManagerSubsystem initialised."));
}

void UDialogueManagerSubsystem::SetDialogueService(TScriptInterface<INpcDialogueService> InService)
{
    DialogueService = InService;
}

INpcDialogueService* UDialogueManagerSubsystem::ResolveService()
{
    if (DialogueService.GetInterface())
    {
        return DialogueService.GetInterface();
    }

    const UWorld* World = GetWorld();
    UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
    if (UNpcEngineServiceSubsystem* ServiceSubsystem =
            GameInstance ? GameInstance->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        DialogueService = ServiceSubsystem->GetDialogueService();   // cache for subsequent turns
        return DialogueService.GetInterface();
    }

    UE_LOG(LogDemoGame, Error,
        TEXT("ResolveService: NpcEngineServiceSubsystem unavailable; cannot send dialogue."));
    return nullptr;
}

void UDialogueManagerSubsystem::Deinitialize()
{
    EndDialogue();
    Super::Deinitialize();
}

void UDialogueManagerSubsystem::BeginDialogue(ANpcActorBase* Npc)
{
    if (!Npc)
    {
        UE_LOG(LogDemoGame, Warning, TEXT("BeginDialogue: null NPC actor."));
        return;
    }
    if (IsInDialogue())
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("BeginDialogue: already in dialogue with %s. Ending previous session."),
            *ActiveNpc->DisplayName);
        EndDialogue();
    }

    ActiveNpc      = Npc;
    ActiveSessionId.Empty();   // fresh conversation — no session_id continuity yet
    OnDialogueBegun.Broadcast(Npc);

    UE_LOG(LogDemoGame, Log, TEXT("Dialogue begun with %s (%s)"),
        *Npc->DisplayName, *Npc->NpcId.ToString());
}

void UDialogueManagerSubsystem::SubmitPlayerMessage(const FString& Message)
{
    if (!IsInDialogue())
    {
        UE_LOG(LogDemoGame, Warning, TEXT("SubmitPlayerMessage: no active dialogue session."));
        return;
    }
    INpcDialogueService* Service = ResolveService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Error, TEXT("SubmitPlayerMessage: no dialogue service available."));
        HandleDialogueError(TEXT("Dialogue service unavailable."));
        return;
    }

    FNpcDialogueRequest Request;
    Request.PlayerId      = FPlayerIdProvider::GetOrCreatePlayerId();
    Request.NpcId         = ActiveNpc->NpcId.ToString();
    Request.PlayerMessage = Message;
    Request.LocationId    = ActiveNpc->LocationId;
    Request.SessionId     = ActiveSessionId;

    // Capture weak ptr so the lambda doesn't hold a strong ref past GC.
    TWeakObjectPtr<UDialogueManagerSubsystem> WeakThis = this;

    FOnNpcDialogueComplete SuccessDelegate;
    SuccessDelegate.BindLambda([WeakThis](const FNpcDialogueResponse& Response)
    {
        if (UDialogueManagerSubsystem* Self = WeakThis.Get())
        {
            Self->HandleDialogueResponse(Response);
        }
    });

    FOnNpcEngineError ErrorDelegate;
    ErrorDelegate.BindLambda([WeakThis](const FString& Error)
    {
        if (UDialogueManagerSubsystem* Self = WeakThis.Get())
        {
            Self->HandleDialogueError(Error);
        }
    });

    Service->SendDialogue(Request, SuccessDelegate, ErrorDelegate);
}

void UDialogueManagerSubsystem::EndDialogue()
{
    if (!IsInDialogue()) return;

    UE_LOG(LogDemoGame, Log, TEXT("Dialogue ended with %s."),
        ActiveNpc.IsValid() ? *ActiveNpc->DisplayName : TEXT("(gone)"));

    ActiveNpc = nullptr;
    ActiveSessionId.Empty();
    OnDialogueEnded.Broadcast();
}

void UDialogueManagerSubsystem::HandleDialogueResponse(const FNpcDialogueResponse& Response)
{
    // Persist session_id so the next SubmitPlayerMessage continues the same conversation.
    if (!Response.SessionId.IsEmpty())
    {
        ActiveSessionId = Response.SessionId;
    }

    const FString DisplayName = ActiveNpc.IsValid() ? ActiveNpc->DisplayName : TEXT("NPC");
    OnNpcSpoke.Broadcast(Response.NpcResponse, DisplayName);

    if (Response.bIsFallback)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("DialogueManager: showing fallback line (engine timeout or error)."));
    }

    // TODO(Slice2): forward RelationDeltas, Emotion, FacialExpression to animation/relationship system.
    // TODO(TTS): forward Response.AudioBytes to audio subsystem via OnAudioReady.
}

void UDialogueManagerSubsystem::HandleDialogueError(const FString& Error)
{
    UE_LOG(LogDemoGame, Warning, TEXT("DialogueManager error: %s"), *Error);
    OnDialogueError.Broadcast(Error);
}
