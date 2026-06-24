// File: MemoryBadgeLookupAsset.cpp
// Module: Game
// Purpose: DataAsset mapping memory node IDs to authored badge display text for the dialogue widget.
// Net I/O: no

#include "MemoryBadgeLookupAsset.h"

FText UMemoryBadgeLookupAsset::GetBadgeText(FName MemoryId) const
{
    const FText* Found = BadgeTextByMemoryId.Find(MemoryId);
    if (Found)
    {
        return *Found;
    }
    return FText::FromName(MemoryId);
}
