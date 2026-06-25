// File: NpcFallbackDefaults.h
// Module: Game
// Purpose: Built-in per-NPC fallback lines so engine-down dialogue never blanks without a DataAsset.
// Net I/O: no
// rules-allow-file: hardcoded_npc_id  (this IS the C++ data table keyed by npc_id; see DEC on UI/data-in-C++)

#pragma once

#include "CoreMinimal.h"

/**
 * Default fallback lines, keyed by stable engine npc_id.
 *
 * Used by UDialogueComponent when no DA_NpcFallbackLines is assigned (or it lacks an entry):
 * the line is shown when the engine times out / returns non-2xx, so the conversation never hangs.
 * An authored DataAsset still takes precedence — these are the zero-setup defaults.
 *
 * Lines mirror the authored text in project-harness/HUMAN_VERIFICATION.md (Phases 4–6).
 */
namespace NpcFallbackDefaults
{
    /** Returns the built-in fallback line for NpcId, or empty FText if none is defined. */
    inline FText GetLine(FName NpcId)
    {
        static const TMap<FName, FText> Lines = {
            { FName(TEXT("mira_innkeeper")),
                FText::FromString(TEXT("…Mira seems distracted and doesn't respond.")) },
            { FName(TEXT("lira_fence")),
                FText::FromString(TEXT("…Lira shrugs and looks away.")) },
            { FName(TEXT("aldric_merchant")),
                FText::FromString(TEXT("…Aldric glances away nervously and doesn't reply.")) },
            { FName(TEXT("captain_sorn")),
                FText::FromString(TEXT("…Sorn nods crisply but says nothing more.")) },
            { FName(TEXT("old_henryk")),
                FText::FromString(TEXT("…Henryk squints at you and mutters something under his breath.")) },
        };

        const FText* Found = Lines.Find(NpcId);
        return Found ? *Found : FText::GetEmpty();
    }
}
