// File: NpcEngineServiceSubsystem.h
// Module: NpcEngineClient
// Purpose: Composition root — owns the concrete REST client and exposes it as INpcDialogueService.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NpcDialogueService.h"
#include "NpcEngineServiceSubsystem.generated.h"

class UNpcEngineRestClient;

/**
 * GameInstance-scoped composition root for the NPC engine.
 *
 * Constructs and owns the one concrete `UNpcEngineRestClient` for the whole game instance, and hands
 * it out only as the abstract `INpcDialogueService`. Gameplay resolves the service here and never
 * names the concrete client (DIP).
 */
UCLASS()
class NPCENGINECLIENT_API UNpcEngineServiceSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /** The DIP seam: the abstract dialogue service backed by the concrete REST client. */
    TScriptInterface<INpcDialogueService> GetDialogueService() const;

private:
    /** Concrete client, owned for the GameInstance lifetime (kept alive by the UPROPERTY). */
    UPROPERTY()
    TObjectPtr<UNpcEngineRestClient> RestClient;
};
