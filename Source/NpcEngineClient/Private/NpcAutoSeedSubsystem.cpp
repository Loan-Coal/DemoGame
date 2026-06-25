// File: NpcAutoSeedSubsystem.cpp
// Module: NpcEngineClient
// Purpose: On world begin-play, health-gate then seed the engine graph once per session.
// Net I/O: yes

#include "NpcAutoSeedSubsystem.h"
#include "NpcEngineRestClient.h"
#include "NpcWorldSeeder.h"
#include "NpcEngineClient.h"
#include "Engine/World.h"

bool UNpcAutoSeedSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }
    // Only real game / PIE worlds — never editor previews or inactive worlds.
    const UWorld* World = Cast<UWorld>(Outer);
    return World && World->IsGameWorld();
}

void UNpcAutoSeedSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    TryAutoSeed();
}

void UNpcAutoSeedSubsystem::TryAutoSeed()
{
    if (bSeedAttempted)
    {
        UE_LOG(LogNpcEngine, Verbose,
            TEXT("AutoSeed: already attempted this session; skipping."));
        return;
    }
    bSeedAttempted = true;

    TWeakObjectPtr<UNpcAutoSeedSubsystem> WeakThis(this);
    RunHealthCheck([WeakThis](bool bHealthy)
    {
        UNpcAutoSeedSubsystem* Self = WeakThis.Get();
        if (!Self)
        {
            return;
        }
        if (!bHealthy)
        {
            UE_LOG(LogNpcEngine, Warning,
                TEXT("AutoSeed: engine /health failed — skipping auto-seed. ")
                TEXT("Start the engine and run NpcEngine.SeedWorld, or replay."));
            return;
        }
        Self->RunSeed();
    });
}

void UNpcAutoSeedSubsystem::SetHealthCheckForTesting(FNpcAutoSeedHealthFn Fn)
{
    HealthCheckOverride = MoveTemp(Fn);
}

void UNpcAutoSeedSubsystem::SetSeederForTesting(FNpcAutoSeedSeedFn Fn)
{
    SeedOverride = MoveTemp(Fn);
}

// ── Private helpers ───────────────────────────────────────────────────────────

void UNpcAutoSeedSubsystem::RunHealthCheck(TFunction<void(bool)> OnResult)
{
    if (HealthCheckOverride)
    {
        HealthCheckOverride(MoveTemp(OnResult));
        return;
    }
    if (!HealthClient)
    {
        HealthClient = NewObject<UNpcEngineRestClient>(this);
    }
    HealthClient->GetHealth(MoveTemp(OnResult));
}

void UNpcAutoSeedSubsystem::RunSeed()
{
    const TFunction<void()> OnComplete = []()
    {
        UE_LOG(LogNpcEngine, Display, TEXT("=== AutoSeed COMPLETE ==="));
    };
    const TFunction<void(const FString&)> OnError = [](const FString& Err)
    {
        UE_LOG(LogNpcEngine, Error, TEXT("AutoSeed FAILED Error=%s"), *Err);
    };

    if (SeedOverride)
    {
        SeedOverride(OnComplete, OnError);
        return;
    }
    if (!Seeder)
    {
        Seeder = NewObject<UNpcWorldSeeder>(this);
    }
    UE_LOG(LogNpcEngine, Display, TEXT("AutoSeed: engine healthy — seeding world..."));
    Seeder->SeedWorld(OnComplete, OnError);
}
