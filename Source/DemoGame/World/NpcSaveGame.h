// File: NpcSaveGame.h
// Module: DemoGame
// Purpose: Persists player_id, active quest steps, faction standings across sessions. DEC-025.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "QuestSubsystem.h"   // FQuestStepState
#include "NpcSaveGame.generated.h"

/**
 * Persistence layer for the NPC Engine demo (DEC-025).
 *
 * Persisted fields:
 *   - PlayerId          — default "player_demo"
 *   - ActiveSteps       — quest step completion state
 *   - FactionStandings  — per-faction standing integers
 *
 * Save slot: "NpcSave" (index 0). UGameplayStatics saves/loads this slot.
 *
 * Save triggers (explicit): quest step complete, faction choice, application quit.
 * Load + validation happens in UQuestSubsystem::Initialize via GetOrCreate().
 */
UCLASS()
class DEMOGAME_API UNpcSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    static const FString SaveSlotName;
    static const int32   UserIndex;

    /** Slice-1 default player ID. */
    UPROPERTY(SaveGame)
    FString PlayerId = TEXT("player_demo");

    /** All tracked quest steps and their completion state. */
    UPROPERTY(SaveGame)
    TArray<FQuestStepState> ActiveSteps;

    /** Per-faction standing (keyed by FactionId FName constants). */
    UPROPERTY(SaveGame)
    TMap<FName, int32> FactionStandings;

    /**
     * Load from slot. Returns nullptr if no save file exists yet.
     * Never returns a partially-valid object — caller treats nullptr as first run.
     */
    static UNpcSaveGame* Load(UObject* WorldContext);

    /**
     * Synchronously write to slot.
     * Called on: quest step completion, faction choice, application quit.
     */
    static void Save(UNpcSaveGame* SaveGame, UObject* WorldContext);

    /**
     * Load or create a default save.
     * Safe to call at any time; never returns nullptr (creates default if missing).
     */
    static UNpcSaveGame* GetOrCreate(UObject* WorldContext);
};
