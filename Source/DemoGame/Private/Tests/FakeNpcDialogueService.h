// File: FakeNpcDialogueService.h
// Module: DemoGame
// Purpose: Test double implementing INpcDialogueService — synchronous, scriptable success/error.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcDialogueService.h"
#include "NpcEngineTypes.h"
#include "FakeNpcDialogueService.generated.h"

/**
 * In-memory fake of INpcDialogueService for DialogueManager specs. Invokes the success/error
 * delegate SYNCHRONOUSLY (no HTTP, no tick) so tests are fully deterministic. This is a unit double
 * for the gameplay layer — a separate concern from the HTTP-transport mock the LSP rule describes.
 */
UCLASS()
class UFakeNpcDialogueService : public UObject, public INpcDialogueService
{
    GENERATED_BODY()

public:
    // Test knobs / captured state.
    bool bShouldSucceed = true;
    FNpcDialogueResponse CannedResponse;
    FString CannedError = TEXT("fake error");
    FNpcDialogueRequest LastRequest;
    int32 SendDialogueCallCount = 0;

    virtual void SendDialogue(
        const FNpcDialogueRequest& Request,
        FOnNpcDialogueComplete OnSuccess,
        FOnNpcEngineError OnError) override
    {
        LastRequest = Request;
        ++SendDialogueCallCount;
        if (bShouldSucceed) { OnSuccess.ExecuteIfBound(CannedResponse); }
        else                { OnError.ExecuteIfBound(CannedError); }
    }

    virtual void SendActionReport(
        const FNpcActionReportRequest& /*Request*/,
        TFunction<void(bool)> OnResult,
        FOnNpcEngineError /*OnError*/) override
    {
        OnResult(bShouldSucceed);
    }

    virtual void GetNpcState(
        const FString& /*NpcId*/,
        TFunction<void(const FString&)> OnResult,
        FOnNpcEngineError /*OnError*/) override
    {
        OnResult(TEXT("{}"));
    }
};
