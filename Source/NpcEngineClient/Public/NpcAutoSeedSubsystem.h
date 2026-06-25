// File: NpcAutoSeedSubsystem.h
// Module: NpcEngineClient
// Purpose: On world begin-play, health-gate then seed the engine graph once per session.
// Net I/O: yes

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "NpcAutoSeedSubsystem.generated.h"

class UNpcEngineRestClient;
class UNpcWorldSeeder;

/**
 * Health probe seam. Production calls UNpcEngineRestClient::GetHealth; tests inject a synchronous fake.
 * OnResult(true) = engine reachable and ready to accept graph writes.
 */
using FNpcAutoSeedHealthFn = TFunction<void(TFunction<void(bool /*bHealthy*/)> /*OnResult*/)>;

/**
 * Seed-action seam. Production calls UNpcWorldSeeder::SeedWorld; tests inject a synchronous fake.
 */
using FNpcAutoSeedSeedFn = TFunction<void(
    TFunction<void()> /*OnComplete*/,
    TFunction<void(const FString& /*Error*/)> /*OnError*/)>;

/**
 * Auto-seeds the NPC Engine graph when a game world begins play, so pressing Play "just works"
 * without the manual NpcEngine.SeedWorld console command.
 *
 * Flow (once per session): begin-play → GET /health → if healthy, run UNpcWorldSeeder::SeedWorld
 * (which is idempotent — it skips nodes that already exist). If /health fails, logs a warning and
 * does nothing; the player still gets canned fallback lines and can seed manually.
 *
 * Only created for game worlds (not editor previews). The seed/health actions are injectable seams
 * (SetHealthCheckForTesting / SetSeederForTesting) so the gating logic is unit-tested without a live
 * engine. Does NOT: parse dialogue, own NPC state, or block the game thread (all I/O is async).
 */
UCLASS()
class NPCENGINECLIENT_API UNpcAutoSeedSubsystem : public UWorldSubsystem
{
    GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void OnWorldBeginPlay(UWorld& InWorld) override;

    /** Health-gated, once-per-session seed. Idempotent across repeated calls. Public for specs. */
    void TryAutoSeed();

    /** Test seam: replace the /health probe. Call before TryAutoSeed. */
    void SetHealthCheckForTesting(FNpcAutoSeedHealthFn Fn);

    /** Test seam: replace the seed action. Call before TryAutoSeed. */
    void SetSeederForTesting(FNpcAutoSeedSeedFn Fn);

    /** True once a seed attempt has started this session (read in specs). */
    bool HasAttemptedSeed() const { return bSeedAttempted; }

private:
    /** Guards once-per-session: set on first TryAutoSeed, never reset. */
    bool bSeedAttempted = false;

    /** Owned client used only for the default /health probe (kept alive by UPROPERTY). */
    UPROPERTY()
    TObjectPtr<UNpcEngineRestClient> HealthClient;

    /** Owned seeder for the default seed action (kept alive by UPROPERTY). */
    UPROPERTY()
    TObjectPtr<UNpcWorldSeeder> Seeder;

    FNpcAutoSeedHealthFn HealthCheckOverride;
    FNpcAutoSeedSeedFn SeedOverride;

    void RunHealthCheck(TFunction<void(bool /*bHealthy*/)> OnResult);
    void RunSeed();
};
