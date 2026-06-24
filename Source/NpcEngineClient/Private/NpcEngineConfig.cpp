#include "NpcEngineConfig.h"
#include "NpcEngineClient.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

namespace
{
    /**
     * Minimal [Section]/Key=Value reader. We parse the file by hand rather than via GConfig because
     * UE's ini parser mangles values containing "//" (e.g. it truncates "http://host" to "http:").
     * Comment lines start with ';'. First matching key in the section wins.
     */
    bool ReadIniValue(const FString& Contents, const FString& Section, const FString& Key, FString& Out)
    {
        TArray<FString> Lines;
        Contents.ParseIntoArrayLines(Lines);
        bool bInSection = false;
        for (FString Line : Lines)
        {
            Line.TrimStartAndEndInline();
            if (Line.IsEmpty() || Line.StartsWith(TEXT(";")))
            {
                continue;
            }
            if (Line.StartsWith(TEXT("[")) && Line.EndsWith(TEXT("]")))
            {
                bInSection = Line.Mid(1, Line.Len() - 2).TrimStartAndEnd().Equals(Section, ESearchCase::IgnoreCase);
                continue;
            }
            int32 Eq = INDEX_NONE;
            if (bInSection && Line.FindChar(TEXT('='), Eq))
            {
                if (Line.Left(Eq).TrimStartAndEnd().Equals(Key, ESearchCase::IgnoreCase))
                {
                    Out = Line.Mid(Eq + 1).TrimStartAndEnd();
                    return true;
                }
            }
        }
        return false;
    }
}

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
    FString IniContents;
    if ((Config.BaseUrl.IsEmpty() || Config.ApiKey.IsEmpty())
        && FFileHelper::LoadFileToString(IniContents, *IniPath))
    {
        if (Config.BaseUrl.IsEmpty())
        {
            ReadIniValue(IniContents, TEXT("NpcEngine"), TEXT("Url"), Config.BaseUrl);
        }
        if (Config.ApiKey.IsEmpty())
        {
            ReadIniValue(IniContents, TEXT("NpcEngine"), TEXT("ApiKey"), Config.ApiKey);
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
