// File: NpcFallbackLinesAsset.cpp
// Module: Game
// Purpose: DataAsset mapping NPC ID FNames to authored fallback lines shown on engine timeout/error.
// Net I/O: no

#include "NpcFallbackLinesAsset.h"

FText UNpcFallbackLinesAsset::GetFallbackLine(FName NpcId) const
{
    const FText* Found = FallbackLineByNpcId.Find(NpcId);
    return Found ? *Found : FText::GetEmpty();
}
