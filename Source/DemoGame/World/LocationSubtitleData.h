// File: LocationSubtitleData.h
// Module: DemoGame
// Purpose: DataAsset holding per-location arrival subtitle text (DA_ prefix in the editor).
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocationSubtitleData.generated.h"

/**
 * Authored per-location subtitle text shown by UArrivalSubtitleWidget on tick advance.
 *
 * Create one DA_LocationSubtitles asset in the editor. Populate SubtitleByLocation with
 * FName keys matching the loc_* constants (e.g. "loc_tavern") and authored FText values.
 * Locations with no entry show no subtitle rather than an empty or raw-ID string.
 */
UCLASS(BlueprintType)
class DEMOGAME_API ULocationSubtitleData : public UDataAsset
{
    GENERATED_BODY()

public:
    /**
     * Map of location id FName → subtitle text shown for 3 s on arrival.
     * Keys must match the engine location id constants exactly (e.g. "loc_tavern").
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Location|Subtitles")
    TMap<FName, FText> SubtitleByLocation;
};
