// File: NpcDialogueService.h
// Module: NpcEngineClient
// Purpose: DIP boundary — abstract async NPC dialogue service consumed by gameplay; hides the concrete client.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NpcEngineTypes.h"
#include "NpcDialogueService.generated.h"

// ── Shared completion delegates ──────────────────────────────────────────────
// Declared here (not in NpcEngineRestClient.h) so the interface and every implementer agree on one
// definition, and gameplay can include only this header — never the concrete client header.

DECLARE_DELEGATE_OneParam(FOnNpcDialogueComplete, const FNpcDialogueResponse& /*Response*/);
DECLARE_DELEGATE_OneParam(FOnNpcEngineError,      const FString& /*ErrorMessage*/);

UINTERFACE(MinimalAPI, NotBlueprintable)
class UNpcDialogueService : public UInterface
{
    GENERATED_BODY()
};

/**
 * Abstract async NPC-engine dialogue service.
 *
 * Gameplay depends on this interface (DIP), never on the concrete `UNpcEngineRestClient`. The
 * concrete REST client implements it by inheritance; tests use a fake. Methods are non-UFUNCTION
 * pure virtuals (they pass non-dynamic C++ delegates), so callers invoke them through the C++
 * interface pointer — never via Blueprint `Execute_` dispatch.
 */
class INpcDialogueService
{
    GENERATED_BODY()

public:
    /**
     * POST /v1/dialogue (raw response shape A).
     * On success: OnSuccess receives the full FNpcDialogueResponse.
     * On error/timeout: OnError receives a message; the caller surfaces a fallback line.
     */
    virtual void SendDialogue(
        const FNpcDialogueRequest& Request,
        FOnNpcDialogueComplete OnSuccess,
        FOnNpcEngineError OnError) = 0;

    /** POST /v1/action (raw response shape A). bSuccess == engine returned { "status": "ok" }. */
    virtual void SendActionReport(
        const FNpcActionReportRequest& Request,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /**
     * GET /v1/npc/{npc_id}/state (envelope shape B). DEC-029.
     * All JSON parsing happens inside NpcEngineClient; callback receives a typed FNpcStateSnapshot.
     * On non-2xx or parse failure: OnResult(invalid snapshot) + OnError. Never crashes.
     * Non-blocking — returns immediately; callback fires on the game thread.
     */
    virtual void GetNpcState(
        const FString& NpcId,
        TFunction<void(const FNpcStateSnapshot& /*Snapshot*/)> OnResult,
        FOnNpcEngineError OnError) = 0;

    /**
     * POST /clock/advance  (envelope shape B). DEC-014 + DEC-015.
     * Body: { "delta_ticks": DeltaTicks }.
     * OnResult(true) on 2xx; OnResult(false) + OnError on non-2xx or missing envelope.
     * Non-blocking — returns immediately; callback fires on the game thread.
     */
    virtual void AdvanceClock(
        int32 DeltaTicks,
        TFunction<void(bool /*bSuccess*/)> OnResult,
        FOnNpcEngineError OnError) = 0;
};
