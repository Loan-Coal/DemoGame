// NpcEngineClient — standalone runtime module for all NPC Engine HTTP/WS communication.
// Game code depends on this module; the module has no dependency on DemoGame.

using UnrealBuildTool;

public class NpcEngineClient : ModuleRules
{
    public NpcEngineClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "HTTP",          // FHttpModule — async REST calls
            "WebSockets",    // IWebSocket — streaming WS client (scaffolded)
            "Json",          // TJsonReader/Writer
            "JsonUtilities"  // FJsonObjectConverter
        });

        // UBT automatically adds Public/ and Private/ subdirectories for this module.
        // No explicit PublicIncludePaths needed — relying on UBT defaults.
    }
}
