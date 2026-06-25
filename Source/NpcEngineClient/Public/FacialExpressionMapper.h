// File: FacialExpressionMapper.h
// Module: NpcEngineClient
// Purpose: Maps ENpcFacialExpression values to MetaHuman morph target names and weights.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NpcEngineTypes.h"
#include "FacialExpressionMapper.generated.h"

class USkeletalMeshComponent;

/**
 * Morph target lookup entry — target name and blend scale for one expression.
 * WeightScale normalises the 0-100 intensity to a 0-1 morph weight.
 */
USTRUCT(BlueprintType)
struct NPCENGINECLIENT_API FFacialMorphEntry
{
    GENERATED_BODY()

    /** MetaHuman morph target name exactly as it appears on the SkeletalMesh. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FacialExpression")
    FName MorphTargetName;

    /** Scale applied to (Intensity / 100.0f) to get the final morph weight [0..1]. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FacialExpression")
    float WeightScale = 1.f;
};

/**
 * UFacialExpressionMapper — maps ENpcFacialExpression to morph target blend data.
 *
 * Default morph target names are C++ placeholders sized for MetaHuman ARKit shape naming.
 * Override by assigning a DA_FacialExpressionMap DataAsset once MetaHumans are imported.
 *
 * Unknown expression values → Neutral (forward-compat). Null SkeletalMeshComponent → warning only.
 * Function length ≤ 40 lines. Never crashes on bad input.
 */
UCLASS(BlueprintType)
class NPCENGINECLIENT_API UFacialExpressionMapper : public UObject
{
    GENERATED_BODY()

public:
    /**
     * Returns the morph entry for Expression. Unknown / out-of-range values → Neutral entry.
     * Never returns an entry with an empty MorphTargetName.
     */
    UFUNCTION(BlueprintPure, Category = "FacialExpression")
    FFacialMorphEntry GetMorphEntry(ENpcFacialExpression Expression) const;

    /**
     * Sets the morph target on Mesh to the weight derived from Intensity (0–100) and the entry's
     * WeightScale. No-op (with log warning) if Mesh is null.
     *
     * Fallback contract: unknown expression → Neutral; null mesh → warning; never crash.
     */
    UFUNCTION(BlueprintCallable, Category = "FacialExpression")
    void ApplyExpression(USkeletalMeshComponent* Mesh, ENpcFacialExpression Expression,
        int32 Intensity);

    /**
     * Optional DataAsset override. When set, expression lookups use the asset's map.
     * Assign DA_FacialExpressionMap in the editor after MetaHuman import.
     * Null → C++ defaults used.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FacialExpression")
    TSoftObjectPtr<UDataAsset> FacialExpressionMapAsset;

private:
    static const TMap<ENpcFacialExpression, FFacialMorphEntry>& GetDefaultMap();
};
