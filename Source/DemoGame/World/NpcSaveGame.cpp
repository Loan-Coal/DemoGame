// File: NpcSaveGame.cpp
// Module: DemoGame
// Purpose: Persists player_id, active quest steps, faction standings across sessions. DEC-025.
// Net I/O: no

#include "NpcSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "DemoGame.h"

const FString UNpcSaveGame::SaveSlotName = TEXT("NpcSave");
const int32   UNpcSaveGame::UserIndex    = 0;

UNpcSaveGame* UNpcSaveGame::Load(UObject* WorldContext)
{
    if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
    {
        return nullptr;
    }

    USaveGame* Raw = UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex);
    UNpcSaveGame* Loaded = Cast<UNpcSaveGame>(Raw);
    if (!Loaded)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("NpcSaveGame::Load: slot exists but cast failed — treating as first run."));
        return nullptr;
    }

    UE_LOG(LogDemoGame, Log,
        TEXT("NpcSaveGame: loaded PlayerId=%s Steps=%d Factions=%d"),
        *Loaded->PlayerId, Loaded->ActiveSteps.Num(), Loaded->FactionStandings.Num());
    return Loaded;
}

void UNpcSaveGame::Save(UNpcSaveGame* SaveGame, UObject* WorldContext)
{
    if (!SaveGame)
    {
        UE_LOG(LogDemoGame, Warning, TEXT("NpcSaveGame::Save: null save object — skipped."));
        return;
    }

    const bool bOk = UGameplayStatics::SaveGameToSlot(SaveGame, SaveSlotName, UserIndex);
    UE_LOG(LogDemoGame, Log,
        TEXT("NpcSaveGame: save %s PlayerId=%s Steps=%d Factions=%d"),
        bOk ? TEXT("OK") : TEXT("FAILED"),
        *SaveGame->PlayerId,
        SaveGame->ActiveSteps.Num(),
        SaveGame->FactionStandings.Num());
}

UNpcSaveGame* UNpcSaveGame::GetOrCreate(UObject* WorldContext)
{
    UNpcSaveGame* Existing = Load(WorldContext);
    if (Existing) return Existing;

    UNpcSaveGame* Fresh = Cast<UNpcSaveGame>(
        UGameplayStatics::CreateSaveGameObject(UNpcSaveGame::StaticClass()));
    if (!Fresh)
    {
        UE_LOG(LogDemoGame, Error, TEXT("NpcSaveGame::GetOrCreate: CreateSaveGameObject failed."));
        return nullptr;
    }

    UE_LOG(LogDemoGame, Log, TEXT("NpcSaveGame: no save found — using defaults."));
    return Fresh;
}
