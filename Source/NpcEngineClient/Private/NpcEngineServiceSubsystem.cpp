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
    // The UObject* constructor sets both the object and the interface pointer.
    return TScriptInterface<INpcDialogueService>(RestClient);
}
