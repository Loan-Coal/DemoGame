// File: NpcAppearance.h
// Module: Game
// Purpose: Data-driven NPC appearance seam — single swap point for cube → MetaHuman.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"

class AActor;
class UNpcAppearanceData;

/**
 * Data-driven NPC visual representation registry (DEC-039/DEC-042).
 *
 * Resolution order at spawn:
 *   1. DA_NpcAppearance DataAsset entry (editor-assigned, no recompile)
 *   2. NpcAppearance C++ default map (headless one-line swap in NpcAppearance.cpp)
 *   3. Empty → keep cube stand-in
 *
 * NpcSpawnerSubsystem reads this on spawn; ANpcGreyboxActor reads it in BeginPlay.
 */
namespace NpcAppearance
{
    /**
     * Named soft-path for the optional DA_NpcAppearance DataAsset.
     * Spawner loads from this path at begin-play; falls back to the C++ map when not found.
     * Lives here (one named constant) — never hardcoded in gameplay logic.
     */
    static const TCHAR* DataAssetPath =
        TEXT("/Game/NpcData/DA_NpcAppearance.DA_NpcAppearance");

    /**
     * Returns the avatar Blueprint class for NpcId using the hybrid resolution chain.
     * Pass a loaded UNpcAppearanceData* for the DataAsset tier; nullptr skips that tier.
     * Returns empty (cube stand-in) when no override is registered. Never crashes on an unknown id.
     */
    TSoftClassPtr<AActor> GetAvatarClass(FName NpcId, const UNpcAppearanceData* DataAsset = nullptr);
}
