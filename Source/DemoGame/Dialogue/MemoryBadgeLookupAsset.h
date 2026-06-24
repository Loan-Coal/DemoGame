// File: MemoryBadgeLookupAsset.h
// Module: Game
// Purpose: DataAsset mapping memory node IDs to authored badge display text for the dialogue widget.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MemoryBadgeLookupAsset.generated.h"

/**
 * Maps memory node ID FNames to authored badge text shown in the dialogue widget.
 *
 * Assign this as DA_MemoryBadgeLookup in the editor.
 * UDialogueWidgetBase uses this when memories_recalled is non-empty to display
 * human-readable badge text instead of raw memory node IDs.
 *
 * Keys: memory node ID FNames from the NPC Engine graph.
 * Values: authored FText (human-readable; never show raw node IDs to the player).
 */
UCLASS(BlueprintType)
class DEMOGAME_API UMemoryBadgeLookupAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    /** Per-memory badge text. Key = memory node ID FName; Value = authored display FText. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Memory")
    TMap<FName, FText> BadgeTextByMemoryId;

    /**
     * Returns authored badge text for the given memory node ID.
     * Falls back to FText from the raw memory ID string if no entry exists,
     * so the badge always shows something meaningful.
     */
    UFUNCTION(BlueprintPure, Category = "Memory")
    FText GetBadgeText(FName MemoryId) const;
};
