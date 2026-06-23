#pragma once

#include "CoreMinimal.h"

/**
 * Generates and persists the player's unique id for the NPC Engine.
 *
 * Format: player_<8 lowercase hex chars>  e.g.  player_a3f7c012
 * Persisted to: Saved/NpcEngine/player_id.txt  (gitignored directory)
 *
 * Slice-1 always returns the fixed id "player_demo" so the smoke test passes
 * against an engine seeded by `make demo-seed` with zero extra setup.
 * The engine's seed already includes the player_demo Character node (is_player:true).
 *
 * When the game generates a NEW id in a future slice, it MUST seed that Character
 * node via POST /v1/graph/nodes/Character before the first dialogue call, or the
 * engine will return 422 CHARACTER_NOT_FOUND.
 */
class NPCENGINECLIENT_API FPlayerIdProvider
{
public:
    /** Returns "player_demo" for slice-1. Future: reads/creates player_<hex> from disk. */
    static FString GetOrCreatePlayerId();

    /** The fixed slice-1 id that matches the engine's demo seed. */
    static FString GetSlice1DefaultId() { return TEXT("player_demo"); }

private:
    /** Generate a fresh player_<8 lowercase hex> string. */
    static FString GenerateNewId();

    /** Absolute path to Saved/NpcEngine/player_id.txt */
    static FString GetSaveFilePath();
};
