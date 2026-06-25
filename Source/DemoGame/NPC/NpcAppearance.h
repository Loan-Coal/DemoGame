// File: NpcAppearance.h
// Module: Game
// Purpose: Data-driven NPC appearance seam — single swap point for cube → MetaHuman.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"

class AActor;

/**
 * Data-driven NPC visual representation registry.
 *
 * GetAvatarClass returns an empty soft class pointer for all NPCs by default — every NPC
 * remains a greybox cube. To swap one NPC to a MetaHuman, add one entry to AppearanceMap
 * pointing at the imported Blueprint class path, e.g.:
 *   AppearanceMap.Add("mira_innkeeper", FSoftClassPath("/Game/MetaHumans/Mira/BP_Mira.BP_Mira_C"));
 * No editor step is required for the wiring; rebuilding DemoGame is sufficient.
 *
 * NpcSpawnerSubsystem reads this on spawn; ANpcGreyboxActor reads it in BeginPlay to
 * optionally load and attach the avatar, hiding the cube stand-in.
 */
namespace NpcAppearance
{
    /**
     * Returns the avatar Blueprint class for NpcId, or empty if no override is registered.
     * Empty = keep the cube greybox stand-in. Never crashes on an unknown id.
     */
    TSoftClassPtr<AActor> GetAvatarClass(FName NpcId);
}
