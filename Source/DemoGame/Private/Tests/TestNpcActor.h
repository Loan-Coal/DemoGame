// File: TestNpcActor.h
// Module: DemoGame
// Purpose: Test-only concrete NPC actor + delegate recorders for DialogueManager and DialogueComponent specs.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcActorBase.h"
#include "NpcEngineTypes.h"
#include "TestNpcActor.generated.h"

/** Minimal concrete NPC so tests can instantiate one (ANpcActorBase is Abstract). */
UCLASS()
class ATestNpcActor : public ANpcActorBase
{
    GENERATED_BODY()
};

/** Records DialogueManager dynamic-multicast broadcasts so specs can assert on them. */
UCLASS()
class URecorder : public UObject
{
    GENERATED_BODY()

public:
    bool bSpokeFired = false;
    bool bErrorFired = false;
    FString LastResponse;
    FString LastName;
    FString LastError;

    UFUNCTION()
    void OnSpoke(const FString& Response, const FString& DisplayName)
    {
        bSpokeFired = true;
        LastResponse = Response;
        LastName = DisplayName;
    }

    UFUNCTION()
    void OnError(const FString& Error)
    {
        bErrorFired = true;
        LastError = Error;
    }
};

/** Records UDialogueComponent::OnFallbackLine broadcasts. */
UCLASS()
class UFallbackRecorder : public UObject
{
    GENERATED_BODY()

public:
    bool bFired = false;
    FName LastNpcId;
    FText LastText;

    UFUNCTION()
    void OnFallback(FName NpcId, FText Text)
    {
        bFired = true;
        LastNpcId = NpcId;
        LastText = Text;
    }
};

/** Records UDialogueComponent::OnTrustChanged broadcasts. */
UCLASS()
class UTrustRecorder : public UObject
{
    GENERATED_BODY()

public:
    bool bFired = false;
    FName LastNpcId;
    FNpcRelationDeltas LastDeltas;

    UFUNCTION()
    void OnTrust(FName NpcId, FNpcRelationDeltas Deltas)
    {
        bFired = true;
        LastNpcId = NpcId;
        LastDeltas = Deltas;
    }
};
