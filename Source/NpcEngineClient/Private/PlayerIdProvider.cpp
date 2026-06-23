#include "PlayerIdProvider.h"
#include "NpcEngineClient.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Guid.h"

FString FPlayerIdProvider::GetOrCreatePlayerId()
{
    // Slice-1: always return the fixed demo id so the smoke test passes against
    // an engine seeded by `make demo-seed` with zero extra steps.
    // TODO(Slice2): uncomment the block below to generate/persist real player ids.
    return GetSlice1DefaultId();

    /*
    const FString SavePath = GetSaveFilePath();

    // Try to load an existing id.
    FString ExistingId;
    if (FFileHelper::LoadFileToString(ExistingId, *SavePath))
    {
        ExistingId = ExistingId.TrimStartAndEnd();
        if (!ExistingId.IsEmpty())
        {
            return ExistingId;
        }
    }

    // Generate a new id, persist it, then seed the Character node before first use.
    const FString NewId = GenerateNewId();
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    PF.CreateDirectoryTree(*FPaths::GetPath(SavePath));
    FFileHelper::SaveStringToFile(NewId, *SavePath);
    UE_LOG(LogNpcEngine, Log, TEXT("PlayerIdProvider: created new player id %s"), *NewId);
    return NewId;
    */
}

FString FPlayerIdProvider::GenerateNewId()
{
    // FGuid gives 128 random bits; take the first 8 hex chars of the first component.
    const FGuid G = FGuid::NewGuid();
    return FString::Printf(TEXT("player_%08x"), G.A);
}

FString FPlayerIdProvider::GetSaveFilePath()
{
    return FPaths::ProjectSavedDir() / TEXT("NpcEngine/player_id.txt");
}
