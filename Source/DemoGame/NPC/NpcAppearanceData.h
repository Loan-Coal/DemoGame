// File: NpcAppearanceData.h
// Module: Game
// Purpose: DataAsset for per-NPC avatar Blueprint class overrides — editor-side, overrides C++ default map.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NpcAppearanceData.generated.h"

/**
 * Editor-assigned DataAsset mapping NPC ids to avatar Blueprint classes.
 *
 * Resolution order at spawn: DA_NpcAppearance entry (if set) →
 *   NpcAppearance C++ default map → empty (cube stand-in).
 *
 * Assign DA_NpcAppearance in the editor or on a thin BP data subclass — no recompile required.
 * Headless one-line swaps via the C++ default map in NpcAppearance.cpp still work.
 *
 * Does NOT: manage HTTP, parse JSON, or hold NPC session state.
 * Dependencies injected: none.
 */
UCLASS()
class DEMOGAME_API UNpcAppearanceData : public UDataAsset
{
    GENERATED_BODY()

public:
    /**
     * Per-NPC avatar Blueprint class keyed by NPC id FName (e.g. "mira_innkeeper").
     * Soft refs only — no hard refs that bloat the cooked memory graph.
     * An entry here overrides the C++ default map for that NPC.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Appearance")
    TMap<FName, TSoftClassPtr<AActor>> AvatarByNpcId;
};
