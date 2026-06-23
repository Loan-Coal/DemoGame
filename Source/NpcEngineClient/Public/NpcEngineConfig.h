#pragma once

#include "CoreMinimal.h"

/**
 * Reads NPC Engine connection settings from (in priority order):
 *   1. Environment variables  NPC_ENGINE_URL / NPC_ENGINE_API_KEY
 *   2. Gitignored ini file    Config/NpcEngine.ini  [NpcEngine] Url / ApiKey
 *
 * Call IsValid() before use. The game startup path should call this once and
 * fail fast (UE_LOG Fatal) if config is missing — never silently fall back to
 * a hardcoded value, as that would commit the key indirectly via compiled code.
 */
class NPCENGINECLIENT_API FNpcEngineConfig
{
public:
    /** Load config. Call once at startup (e.g. in module StartupModule or GameInstance). */
    static FNpcEngineConfig Load();

    bool IsValid() const { return bIsValid; }

    const FString& GetBaseUrl() const { return BaseUrl; }
    const FString& GetApiKey() const { return ApiKey; }

    /** Convenience: full Authorization header value. */
    FString MakeBearerHeader() const { return FString::Printf(TEXT("Bearer %s"), *ApiKey); }

private:
    FString BaseUrl;
    FString ApiKey;
    bool bIsValid = false;
};
