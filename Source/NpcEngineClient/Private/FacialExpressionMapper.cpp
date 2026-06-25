// File: FacialExpressionMapper.cpp
// Module: NpcEngineClient
// Purpose: Maps ENpcFacialExpression values to MetaHuman morph target names and weights.
// Net I/O: no

#include "FacialExpressionMapper.h"
#include "Components/SkeletalMeshComponent.h"
#include "NpcEngineClient.h"

namespace
{
    // Placeholder morph target names — replace with actual MetaHuman ARKit morph names once
    // MetaHumans are imported (Phase 7 editor session). Keeping the "CTRL_expressions_" prefix
    // as the canonical MetaHuman namespace so the names are valid once the actual mesh is set.
    static const FName MT_Neutral    = TEXT("CTRL_expressions_neutral");
    static const FName MT_Happy      = TEXT("CTRL_expressions_mouthSmile");
    static const FName MT_Sad        = TEXT("CTRL_expressions_mouthFrown");
    static const FName MT_Angry      = TEXT("CTRL_expressions_browLower");
    static const FName MT_Fearful    = TEXT("CTRL_expressions_eyeWide");
    static const FName MT_Surprised  = TEXT("CTRL_expressions_jawOpen");
    static const FName MT_Disgusted  = TEXT("CTRL_expressions_noseScrunch");
    static const FName MT_Contempt   = TEXT("CTRL_expressions_mouthCornerL");
}

const TMap<ENpcFacialExpression, FFacialMorphEntry>& UFacialExpressionMapper::GetDefaultMap()
{
    static const TMap<ENpcFacialExpression, FFacialMorphEntry> DefaultMap = {
        { ENpcFacialExpression::Neutral,   { MT_Neutral,   1.f } },
        { ENpcFacialExpression::Happy,     { MT_Happy,     1.f } },
        { ENpcFacialExpression::Sad,       { MT_Sad,       1.f } },
        { ENpcFacialExpression::Angry,     { MT_Angry,     1.f } },
        { ENpcFacialExpression::Fearful,   { MT_Fearful,   1.f } },
        { ENpcFacialExpression::Surprised, { MT_Surprised, 1.f } },
        { ENpcFacialExpression::Disgusted, { MT_Disgusted, 1.f } },
        { ENpcFacialExpression::Contempt,  { MT_Contempt,  1.f } },
    };
    return DefaultMap;
}

FFacialMorphEntry UFacialExpressionMapper::GetMorphEntry(ENpcFacialExpression Expression) const
{
    const TMap<ENpcFacialExpression, FFacialMorphEntry>& Map = GetDefaultMap();
    const FFacialMorphEntry* Found = Map.Find(Expression);
    if (Found)
    {
        return *Found;
    }

    // Forward-compat: unknown / out-of-range expression → Neutral.
    UE_LOG(LogNpcEngine, Warning,
        TEXT("FacialExpressionMapper: unknown expression value %d, falling back to Neutral"),
        static_cast<int32>(Expression));
    return *Map.Find(ENpcFacialExpression::Neutral);
}

void UFacialExpressionMapper::ApplyExpression(
    USkeletalMeshComponent* Mesh, ENpcFacialExpression Expression, int32 Intensity)
{
    if (!Mesh)
    {
        UE_LOG(LogNpcEngine, Warning,
            TEXT("ApplyExpression: null SkeletalMesh — cannot apply expression"));
        return;
    }

    const FFacialMorphEntry Entry = GetMorphEntry(Expression);
    const float Weight = FMath::Clamp(Intensity / 100.f, 0.f, 1.f) * Entry.WeightScale;
    Mesh->SetMorphTarget(Entry.MorphTargetName, Weight);
}
