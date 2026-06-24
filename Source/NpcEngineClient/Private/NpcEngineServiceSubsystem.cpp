// File: NpcEngineServiceSubsystem.cpp
// Module: NpcEngineClient
// Purpose: Composition root — owns the concrete REST client and exposes it as INpcDialogueService.
// Net I/O: no

#include "NpcEngineServiceSubsystem.h"
#include "NpcEngineRestClient.h"
#include "NpcEngineClient.h"

void UNpcEngineServiceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    RestClient = NewObject<UNpcEngineRestClient>(this);
    UE_LOG(LogNpcEngine, Log, TEXT("NpcEngineServiceSubsystem initialised (REST client constructed)."));
}

void UNpcEngineServiceSubsystem::Deinitialize()
{
    RestClient = nullptr;
    Super::Deinitialize();
}

TScriptInterface<INpcDialogueService> UNpcEngineServiceSubsystem::GetDialogueService() const
{
    return TScriptInterface<INpcDialogueService>(RestClient);
}

TScriptInterface<INpcQuestService> UNpcEngineServiceSubsystem::GetQuestService() const
{
    // RestClient implements both INpcDialogueService and INpcQuestService (DEC-026).
    return TScriptInterface<INpcQuestService>(RestClient);
}
