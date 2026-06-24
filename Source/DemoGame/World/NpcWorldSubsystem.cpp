// File: NpcWorldSubsystem.cpp
// Module: DemoGame
// Purpose: Tracks player location; fires clock-advance ticks through INpcDialogueService on arrival.
// Net I/O: no

#include "NpcWorldSubsystem.h"
#include "NpcEngineServiceSubsystem.h"
#include "DemoGame.h"
#include "Engine/GameInstance.h"

// ── Lifecycle ────────────────────────────────────────────────────────────────

void UNpcWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogDemoGame, Log, TEXT("NpcWorldSubsystem initialised."));
}

void UNpcWorldSubsystem::Deinitialize()
{
    DialogueService = nullptr;
    Super::Deinitialize();
}

// ── Service resolution ───────────────────────────────────────────────────────

void UNpcWorldSubsystem::SetDialogueService(TScriptInterface<INpcDialogueService> InService)
{
    DialogueService = InService;
}

INpcDialogueService* UNpcWorldSubsystem::ResolveService()
{
    if (DialogueService.GetInterface())
    {
        return DialogueService.GetInterface();
    }

    // Lazy resolution from the GameInstance composition root (DEC-013 / DEC-015).
    const UWorld* World = GetWorld();
    UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
    if (UNpcEngineServiceSubsystem* SS =
            GameInstance ? GameInstance->GetSubsystem<UNpcEngineServiceSubsystem>() : nullptr)
    {
        DialogueService = SS->GetDialogueService();
        return DialogueService.GetInterface();
    }

    UE_LOG(LogDemoGame, Error,
        TEXT("NpcWorldSubsystem::ResolveService: NpcEngineServiceSubsystem unavailable."));
    return nullptr;
}

// ── Public API ───────────────────────────────────────────────────────────────

void UNpcWorldSubsystem::OnPlayerArrived(FName LocationId, bool bFiresTick)
{
    // Re-entry guard — same location, same tick-state: do nothing.
    if (LocationId == CurrentLocationId)
    {
        return;
    }

    CurrentLocationId = LocationId;

    if (!bFiresTick)
    {
        UE_LOG(LogDemoGame, Log,
            TEXT("NpcWorldSubsystem: arrived at %s (no tick — bFiresTick=false)."),
            *LocationId.ToString());
        return;
    }

    INpcDialogueService* Service = ResolveService();
    if (!Service)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("NpcWorldSubsystem: no INpcDialogueService available — clock advance skipped."));
        return;
    }

    // Capture for the lambda — TickCount increments only on success.
    const FName ArrivedLocation = LocationId;

    Service->AdvanceClock(
        1,
        [this, ArrivedLocation](bool bSuccess)
        {
            if (!bSuccess)
            {
                UE_LOG(LogDemoGame, Warning,
                    TEXT("NpcWorldSubsystem: AdvanceClock failed for Location=%s."),
                    *ArrivedLocation.ToString());
                return;
            }
            ++TickCount;
            UE_LOG(LogDemoGame, Log,
                TEXT("Tick=%d Location=%s"), TickCount, *ArrivedLocation.ToString());
            OnTickAdvanced.Broadcast(ArrivedLocation, TickCount);
        },
        FOnNpcEngineError::CreateLambda([ArrivedLocation](const FString& Err)
        {
            UE_LOG(LogDemoGame, Error,
                TEXT("NpcWorldSubsystem: ClockAdvance failed Location=%s Error=%s"),
                *ArrivedLocation.ToString(), *Err);
        }));
}
