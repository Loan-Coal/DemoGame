#include "NpcEngineConfig.h"
#include "NpcEngineClient.h"
#include "Misc/ConfigCacheIni.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Paths.h"

FNpcEngineConfig FNpcEngineConfig::Load()
{
    FNpcEngineConfig Config;

    // 1. Try environment variables (highest priority).
    FString EnvUrl  = FPlatformMisc::GetEnvironmentVariable(TEXT("NPC_ENGINE_URL"));
    FString EnvKey  = FPlatformMisc::GetEnvironmentVariable(TEXT("NPC_ENGINE_API_KEY"));

    if (!EnvUrl.IsEmpty())  Config.BaseUrl = EnvUrl;
    if (!EnvKey.IsEmpty())  Config.ApiKey  = EnvKey;

    // 2. Fall back to gitignored Config/NpcEngine.ini.
    const FString IniPath = FPaths::ProjectConfigDir() / TEXT("NpcEngine.ini");
    if (FPaths::FileExists(IniPath))
    {
        if (Config.BaseUrl.IsEmpty())
        {
            GConfig->GetString(TEXT("NpcEngine"), TEXT("Url"), Config.BaseUrl, IniPath);
        }
        if (Config.ApiKey.IsEmpty())
        {
            GConfig->GetString(TEXT("NpcEngine"), TEXT("ApiKey"), Config.ApiKey, IniPath);
        }
    }

    // 3. Fail fast if either value is still missing.
    if (Config.BaseUrl.IsEmpty())
    {
        UE_LOG(LogNpcEngine, Fatal,
            TEXT("NPC Engine URL not configured. Set env var NPC_ENGINE_URL or add [NpcEngine] Url= to Config/NpcEngine.ini (gitignored)."));
        return Config;
    }
    if (Config.ApiKey.IsEmpty())
    {
        UE_LOG(LogNpcEngine, Fatal,
            TEXT("NPC Engine API key not configured. Set env var NPC_ENGINE_API_KEY or add [NpcEngine] ApiKey= to Config/NpcEngine.ini (gitignored)."));
        return Config;
    }

    // Strip trailing slash for consistent URL building.
    Config.BaseUrl = Config.BaseUrl.TrimEnd();
    if (Config.BaseUrl.EndsWith(TEXT("/")))
    {
        Config.BaseUrl = Config.BaseUrl.LeftChop(1);
    }

    Config.bIsValid = true;
    UE_LOG(LogNpcEngine, Log, TEXT("NpcEngineConfig loaded. BaseUrl=%s"), *Config.BaseUrl);
    return Config;
}
