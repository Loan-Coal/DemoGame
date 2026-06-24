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
