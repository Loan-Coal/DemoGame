# Human Verification — Unreal Editor Tasks

This file is the **morning to-do list**. The overnight autonomous runner implements all
C++/test/doc work headlessly and commits it. Anything that **requires the Unreal Editor**
(placing actors, authoring DataAssets, laying out UMG widgets, MetaHuman/material work,
level building, PIE playtests) cannot be done headlessly — the runner writes those steps
here, verbatim, with exact instructions, then continues to the next phase's C++ work.

**How to use this file:** work top-to-bottom. Each task says exactly what to click/set in
the editor. When a task is done, change `- [ ]` to `- [x]`. Tasks are grouped by the phase
that produced them. The C++ they depend on is already committed and building.

**Conventions used below:**
- `BP_` Blueprint, `WBP_` widget Blueprint, `DA_` DataAsset, `SM_` static mesh, `M_` material.
- NPC IDs are stable engine keys — type them exactly (e.g. `mira_innkeeper`).
- Bind-widget names in UMG must match the C++ `BindWidgetOptional` names exactly, and the
  widget *type* must match (Text Block → `UTextBlock`, Editable Text single-line → `UEditableText`).

---

## Phase 4 — Dialogue + Trust Gate (editor session)

**C++ status:** ✅ complete and committed (`feat(phase4)`). Dialogue works in PIE.

### Already done (by you, 2026-06-24)
- [x] `BP_NPC_Mira` created (parent `NpcActorBase`), cube body, `NpcId=mira_innkeeper`, `DisplayName=Mira`, `LocationId=loc_tavern`, placed in level
- [x] `WBP_Dialogue` created (parent `DialogueWidgetBase`) with `ResponseText` (Text Block), `InputText` (Editable Text), Send button → `Submit Input`
- [x] `WBP_Dialogue` assigned to `BP_ThirdPersonCharacter` → `Dialogue Widget Class`
- [x] `IA_Interact` created, mapped to **E** in the Input Mapping Context, assigned on the character

### Remaining
- [ ] **Author `DA_NpcFallbackLines`** — Content Browser → Miscellaneous → Data Asset → pick `NpcFallbackLinesAsset`. Name it `DA_NpcFallbackLines`. Open it, add two `FallbackLineByNpcId` entries:
  - Key `mira_innkeeper` → *"…Mira seems distracted and doesn't respond."*
  - Key `lira_fence` → *"…Lira shrugs and looks away."*
  Then on `BP_NPC_Mira` → `DialogueComponent` → set **Fallback Lines Asset** = `DA_NpcFallbackLines`. (This is what shows when the engine is down — without it the fallback line is blank.)
- [ ] **Polish `WBP_Dialogue`** (from your notes): give the panel an opaque/solid background (it's currently transparent); add a `ThinkingIndicator` Text Block (BindWidgetOptional name `ThinkingIndicator`) shown during the LLM wait; optionally a `MemoriesBadge` Text Block (name `MemoriesBadge`).
- [ ] **Create `WBP_RelationshipMeter`** — Widget Blueprint, parent class `RelationshipMeterWidget`. Add three Text Blocks named exactly `TrustText`, `FearText`, `AffectionText`. Add it to the player HUD (e.g. created + `AddToViewport` from the character, or a HUD Blueprint).
- [ ] **Place Lira** — `BP_NPC_Lira` (parent `NpcActorBase`), `NpcId=lira_fence`, `LocationId=loc_tavern_back`. (Lira's room gating is Phase 5; placing her now is fine.)
- [ ] **Live trust-gate verification** (needs Docker engine on `localhost:8000` + `NpcEngine.SeedWorld` run once):
  - [ ] Approach Mira → E → type messages → `WBP_RelationshipMeter` Trust climbs past **25**
  - [ ] At Trust > 25, Mira's dialogue reveals information about Aldric (no waypoint)
  - [ ] Repeat from a fresh seed 3× — gate must clear all 3 runs
  - [ ] `memories_recalled` badge appears at least once during the golden path

---

<!-- The overnight runner appends new phase sections below this line, newest last. -->
<!-- FORMAT for appended sections:
## Phase N — <title> (editor session)
**C++ status:** ✅ complete and committed (<commit hash/subject>).
**Why these need the editor:** <one line>
- [ ] <exact editor step copied from ROADMAP [EDITOR SESSION] block>
-->

## Phase 5 — Quest System + Faction Fork (editor session)

**C++ status:** ✅ complete and committed (`feat(phase5)`). QuestSubsystem, FactionSubsystem, NpcSaveGame, QuestLogWidget, QuestConfirmWidget, FactionForkWidget, NpcWorldSubsystem trust gate all committed.
**Why these need the editor:** Live endpoint verification, fallback line authoring, NPC capsule placement, WBP widget layout, trust-gate PIE test.

- [ ] **Verify quest lifecycle endpoint shapes** — run `GET http://localhost:8000/openapi.json` in a browser or via curl. Confirm the 6 shapes from DEC-027 match the live engine. If any field name differs, update `NpcQuestTypes.h` and the matching serializer in `NpcEngineJsonUtils.cpp`. Record confirmation (or patch notes) in DECISIONS.md as a DEC-027 update.
- [ ] **Author fallback lines for Aldric and Captain Sorn** in `DA_NpcFallbackLines`. Open the asset (Content Browser → find `DA_NpcFallbackLines`), add two `FallbackLineByNpcId` entries:
  - Key `aldric_merchant` → *"…Aldric glances away nervously and doesn't reply."*
  - Key `captain_sorn` → *"…Sorn nods crisply but says nothing more."*
- [ ] **Place Slice-2 NPC capsules:**
  - `BP_NPC_Aldric` (parent `NpcActorBase`): `NpcId = aldric_merchant` FName constant, `DisplayName = "Aldric"`, `LocationId = loc_market_square`, placed in `L_MarketSquare`
  - `BP_NPC_Sorn` (parent `NpcActorBase`): `NpcId = captain_sorn` FName constant, `DisplayName = "Captain Sorn"`, `LocationId = loc_guard_barracks`, placed in `L_GuardBarracks`
  - `BP_NPC_Henryk` (parent `NpcActorBase`): `NpcId = old_henryk` FName constant, `DisplayName = "Old Henryk"`, `LocationId = loc_market_square`, placed in `L_MarketSquare`
- [ ] **Create `WBP_QuestLog`** — Widget Blueprint, parent class `QuestLogWidget`. Add a Vertical Box named exactly `QuestList` (`BindWidget`). No Blueprint logic needed — C++ base handles population on `OnQuestActivated`.
- [ ] **Create `WBP_QuestConfirm`** — Widget Blueprint, parent class `QuestConfirmWidget`. Add:
  - Text Block named `QuestTitleText` (`BindWidget`)
  - Button named `AcceptButton` (`BindWidget`) → calls `NativeOnAccept()`
  - Button named `DeclineButton` (`BindWidget`) → calls `NativeOnDecline()`
- [ ] **Create `WBP_FactionFork`** — Widget Blueprint, parent class `FactionForkWidget`. Add:
  - Button named `ChoiceAButton` (`BindWidget`)
  - Button named `ChoiceBButton` (`BindWidget`)
  - Text Block named `ChoiceALabel` (`BindWidget`)
  - Text Block named `ChoiceBLabel` (`BindWidget`)
- [ ] **Add `WBP_QuestLog` to the player HUD** — same pattern as `WBP_Dialogue` in Phase 4: create + `AddToViewport` from the character or a HUD Blueprint.
- [ ] **Test L_TavernBack streaming gate (PIE):**
  - Run `NpcEngine.SeedWorld` to reset engine state, then start PIE in `L_Tavern`
  - Approach Mira and exchange dialogue until accumulated trust ≥ 40 (`TRUST_GATE_2_MIRA` constant)
  - Confirm `UNpcWorldSubsystem::OnTavernBackUnlocked` fires (Output Log: `"TavernBack gate fired"`)
  - If the sub-level isn't streaming in automatically: in `L_Tavern` Level Blueprint (or player HUD), bind `OnTavernBackUnlocked` → call `ULevelStreamingDynamic::LoadLevelInstance` or make the streaming level visible. Record the wiring choice in DECISIONS.md.
- [ ] **Chain A end-to-end verification** (requires all Slice-2 NPCs placed + engine seeded + quest log wired):
  - Fresh save → investigate Mira (trust gate 1 at 25) → identify Aldric through 2+ conversations → quest log shows `find_wine_merchant` active → `deliver_amulet` appears → faction fork fires → faction standing change logged to Output Log
  - Confirm quest log shows `deliver_amulet` complete and `aldric_confession` step appears
