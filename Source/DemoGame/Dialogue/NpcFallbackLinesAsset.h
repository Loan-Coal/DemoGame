// File: NpcFallbackLinesAsset.h
// Module: Game
// Purpose: DataAsset mapping NPC ID FNames to authored fallback lines shown on engine timeout/error.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NpcFallbackLinesAsset.generated.h"

/**
 * Maps NPC ID FNames to authored fallback dialogue lines.
 *
 * Assign as DA_NpcFallbackLines in the editor.
 * UDialogueComponent uses this when INpcDialogueService returns non-2xx or times out —
 * the authored line is shown to the player so the conversation never hangs.
 *
 * Keys: stable NPC ID FNames matching the engine seed (e.g. FName("mira_innkeeper")).
 * Values: authored FText displayed as the NPC's response. Never show raw node IDs as text.
 *
 * Does NOT: make HTTP calls; store engine state; log.
 * Dependencies injected: none.
 */
UCLASS(BlueprintType)
class DEMOGAME_API UNpcFallbackLinesAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /** Per-NPC fallback line. Key = stable NPC ID FName; Value = authored fallback FText. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Fallback")
    TMap<FName, FText> FallbackLineByNpcId;

    /**
     * Returns the authored fallback line for NpcId.
     * Returns an empty FText if no entry exists — caller must handle empty gracefully.
     */
    UFUNCTION(BlueprintPure, Category = "Fallback")
    FText GetFallbackLine(FName NpcId) const;
};
