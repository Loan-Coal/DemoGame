// File: NpcEngineSmokeCommand.cpp
// Module: NpcEngineClient
// Purpose: Registers the `NpcEngine.Smoke` console command — live health + one dialogue round-trip.
// Net I/O: yes
//
// GameMode-independent: runs off a console command (not a PlayerController Exec), so it works in any
// map/PIE/-game session regardless of which GameMode or PlayerController is active.

#include "NpcEngineClient.h"
#include "NpcEngineRestClient.h"
#include "NpcEngineTypes.h"
#include "HAL/IConsoleManager.h"

namespace
{
    /** Build the dialogue request used by the smoke test (slice-1 tavern fixture). */
    FNpcDialogueRequest MakeSmokeRequest()
    {
        FNpcDialogueRequest Req;
        Req.PlayerId      = TEXT("player_demo");
        Req.NpcId         = TEXT("mira_innkeeper");   // client-module dev fixture (rule scoped to Game module)
        Req.PlayerMessage = TEXT("Good evening, Mira.");
        Req.LocationId    = TEXT("loc_tavern");
        return Req;
    }

    /** Health check, then (if healthy) one live dialogue turn. All async; logs to LogNpcEngine. */
    void RunNpcEngineSmoke(UWorld* /*World*/)
    {
        UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.Smoke BEGIN ==="));

        // Rooted so it survives the async HTTP callbacks; unrooted on every terminal path.
        UNpcEngineRestClient* Client = NewObject<UNpcEngineRestClient>();
        Client->AddToRoot();

        Client->GetHealth([Client](bool bOk)
        {
            UE_LOG(LogNpcEngine, Display,
                TEXT("NpcEngine.Smoke | Health Status=%s"), bOk ? TEXT("OK") : TEXT("FAIL"));

            if (!bOk)
            {
                UE_LOG(LogNpcEngine, Warning,
                    TEXT("NpcEngine.Smoke | engine unreachable - start the docker engine first."));
                UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.Smoke END (health fail) ==="));
                Client->RemoveFromRoot();
                return;
            }

            FOnNpcDialogueComplete OnSuccess;
            OnSuccess.BindLambda([Client](const FNpcDialogueResponse& Response)
            {
                UE_LOG(LogNpcEngine, Display, TEXT("NpcEngine.Smoke | NpcId=mira_innkeeper Reply=\"%s\""),
                    *Response.NpcResponse);
                UE_LOG(LogNpcEngine, Display,
                    TEXT("NpcEngine.Smoke | DegradationLevel=%s Cached=%s Fallback=%s"),
                    *Response.DegradationLevel,
                    Response.bCached ? TEXT("true") : TEXT("false"),
                    Response.bIsFallback ? TEXT("true") : TEXT("false"));
                UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.Smoke PASS ==="));
                Client->RemoveFromRoot();
            });

            FOnNpcEngineError OnError;
            OnError.BindLambda([Client](const FString& ErrorMessage)
            {
                UE_LOG(LogNpcEngine, Error, TEXT("NpcEngine.Smoke | Dialogue Status=FAIL Error=%s"), *ErrorMessage);
                UE_LOG(LogNpcEngine, Display, TEXT("=== NpcEngine.Smoke END (dialogue fail) ==="));
                Client->RemoveFromRoot();
            });

            Client->SendDialogue(MakeSmokeRequest(), OnSuccess, OnError);
        });
    }
}

static FAutoConsoleCommandWithWorld GNpcEngineSmokeCommand(
    TEXT("NpcEngine.Smoke"),
    TEXT("NPC Engine smoke test: GET /health then one /v1/dialogue round-trip with mira_innkeeper. Logs to LogNpcEngine."),
    FConsoleCommandWithWorldDelegate::CreateStatic(&RunNpcEngineSmoke));
