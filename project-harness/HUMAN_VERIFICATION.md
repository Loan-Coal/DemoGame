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

## 🧭 2026-06-25 — Morning loop at a glance (headless-first)

The overnight loop builds the **entire playable slice in C++ — including the world itself**. After a
run, pressing Play gives a walkable greybox (procedural floor + 4 location regions + 5 cube NPCs) with
dialogue, trust, quests, and gossip all live. The only work that is genuinely yours:

1. **Live-LLM playtests** (Docker engine on `:8000`, seed via auto-seed/`NpcEngine.SeedWorld`) — the
   trust-gate climb, gossip chain 5/5, and greybox acceptance gate. These verify *runtime behaviour*,
   not assets. Detailed per phase below (Phases 4, 5, 6).
2. **Character + environment art — all OPTIONAL** (the greybox is fully playable without them): import
   MetaHumans / Fab kits and author real art levels when you choose to leave greybox.
3. **One-line swaps Claude does for you:** once a MetaHuman is imported to a known `/Game/...` path and
   you share that path, Claude flips that NPC cube → MetaHuman in `NpcAppearance.cpp` — no editor step.

**No longer your job** (now headless C++): building the 4 levels + travel triggers (procedural greybox
subsystem), placing NPCs / notice boards, widget layout, fallback lines, quest metadata, notice-board
text. The `[EDITOR SESSION]` blocks in the ROADMAP are optional art passes, not blockers.

---

## ⚙️ 2026-06-25 — Editor work automated in C++ (DEC-020)

The asset-authoring, widget-layout, NPC-placement, and data-authoring tasks below are now done
**in C++** so they need no editor work. Press Play in `Lvl_ThirdPerson` (the ThirdPerson template
level) and everything appears:
- **Widgets** build their own legible layout in C++ (`UiStyle` + each base class). No WBP needed; an
  authored WBP still overrides the C++ default for v2 art.
- **5 NPCs** spawn at begin-play as labelled cubes (`UNpcSpawnerSubsystem` + `ANpcGreyboxActor`),
  walk-up-and-press-**E** to talk. **Tab** opens the Rumor Journal. Relationship meter + quest log
  auto-mount to the HUD.
- **Fallback lines** and **notice-board rumor tiers** are C++ defaults — no `DA_NpcFallbackLines`
  authoring, no `BP_NoticeBoard`.

Boxes satisfied by C++ are ticked below with `(C++ DEC-020)`. The **live-engine playtests** (Docker on
:8000, trust-gate climbs, gossip 5/5, greybox acceptance) still require you — they verify runtime
behaviour, not assets. Optional cleanup: delete the duplicate `Content/BP_NPC_Mira.uasset` and
`Content/BP_NPC_Lira.uasset` left loose in the root.

---

## Phase 4 — Dialogue + Trust Gate (editor session)

**C++ status:** ✅ complete and committed (`feat(phase4)`). Dialogue works in PIE.

### Already done (by you, 2026-06-24)
- [x] `BP_NPC_Mira` created (parent `NpcActorBase`), cube body, `NpcId=mira_innkeeper`, `DisplayName=Mira`, `LocationId=loc_tavern`, placed in level
- [x] `WBP_Dialogue` created (parent `DialogueWidgetBase`) with `ResponseText` (Text Block), `InputText` (Editable Text), Send button → `Submit Input`
- [x] `WBP_Dialogue` assigned to `BP_ThirdPersonCharacter` → `Dialogue Widget Class`
- [x] `IA_Interact` created, mapped to **E** in the Input Mapping Context, assigned on the character

### Remaining
- [x] *(C++ DEC-020 — built-in `NpcFallbackDefaults`; DataAsset optional override)* **Author `DA_NpcFallbackLines`** — Content Browser → Miscellaneous → Data Asset → pick `NpcFallbackLinesAsset`. Name it `DA_NpcFallbackLines`. Open it, add two `FallbackLineByNpcId` entries:
  - Key `mira_innkeeper` → *"…Mira seems distracted and doesn't respond."*
  - Key `lira_fence` → *"…Lira shrugs and looks away."*
  Then on `BP_NPC_Mira` → `DialogueComponent` → set **Fallback Lines Asset** = `DA_NpcFallbackLines`. (This is what shows when the engine is down — without it the fallback line is blank.)
- [x] *(C++ DEC-020 — solid panel, ThinkingIndicator, MemoriesBadge built in C++)* **Polish `WBP_Dialogue`** (from your notes): give the panel an opaque/solid background (it's currently transparent); add a `ThinkingIndicator` Text Block (BindWidgetOptional name `ThinkingIndicator`) shown during the LLM wait; optionally a `MemoriesBadge` Text Block (name `MemoriesBadge`).
- [x] *(C++ DEC-020 — built + auto-mounted to HUD)* **Create `WBP_RelationshipMeter`** — Widget Blueprint, parent class `RelationshipMeterWidget`. Add three Text Blocks named exactly `TrustText`, `FearText`, `AffectionText`. Add it to the player HUD (e.g. created + `AddToViewport` from the character, or a HUD Blueprint).
- [x] *(C++ DEC-020 — spawned by `UNpcSpawnerSubsystem`)* **Place Lira** — `BP_NPC_Lira` (parent `NpcActorBase`), `NpcId=lira_fence`, `LocationId=loc_tavern_back`. (Lira's room gating is Phase 5; placing her now is fine.)
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

## Phase 7 — MetaHuman + Dialogue Camera (editor session)

**C++ status:** ✅ complete and committed. Phase 7 headless block done 2026-06-25:
- `NpcAppearance.h/.cpp` — empty registry by default; one-line row = MetaHuman swap.
- `NpcAppearance.spec.cpp` — 3 specs: rostered NPCs default to empty, unknown → empty, roster parity.
- `FNpcSpawnRecord` gains `AvatarClass`; spawner fills from `NpcAppearance::GetAvatarClass`.
- `ANpcGreyboxActor::TrySpawnAvatar()` — loads soft class, spawns child, hides cube + label.
- `UFacialExpressionMapper` (NpcEngineClient) — spec + impl: maps `ENpcFacialExpression` → morph target name/weight; null mesh → warning; unknown → Neutral.
- `UDialogueComponent::EndDialogue(PC)` + `BlendCameraToNpc/Player` — blends 0.3s in, 0.4s out.
- `ADemoGameCharacter` tracks `ActiveNpc`; calls `EndDialogue` in `HandleDialogueEnded`.

**Why these need the editor:** MetaHuman import, skeleton socket setup, and Animation Blueprint wiring all require the Unreal Editor; VRAM profiling requires PIE.

### Instructions (copy from ROADMAP Phase 7 [EDITOR SESSION])

**VRAM gate — complete before importing Lira:**
1. Load `L_Tavern` with Mira MetaHuman placed (`BP_NPC_Mira`). Open `stat gpu`. Confirm VRAM < 10 GB.
2. Load `L_GuardBarracks` with Sorn MetaHuman placed (`BP_NPC_Sorn`). Confirm VRAM < 10 GB.
3. If either scene exceeds 10 GB: investigate (reduce texture pool, LOD settings, streaming). Record findings in DECISIONS.md before continuing. Do not import Lira until Mira scene is under budget.

**MetaHuman setup (after VRAM gate passes):**
4. Create `BP_NPC_Mira` (extends `ANpcActorBase`; prefix `BP_`): place Mira MetaHuman mesh. Set `NpcId` UPROPERTY to `mira_innkeeper` FName constant. Configure Animation Blueprint with looping thinking idle + neutral blend space.
5. Create `BP_NPC_Sorn` (extends `ANpcActorBase`): set `NpcId` = captain_sorn constant.
6. Create `BP_NPC_Lira` (extends `ANpcActorBase`): set `NpcId` = lira_fence constant. Place in `L_TavernBack` sub-level only.
7. Aldric and Old Henryk: all-MetaHuman per DEC-031. Create `BP_NPC_Aldric` and `BP_NPC_Henryk`.

**One-line swap for each NPC (after BP path is known):** Tell Claude the `/Game/...` path for each imported Blueprint → Claude adds one line to `NpcAppearance.cpp` per NPC → rebuild DemoGame → cube becomes MetaHuman. No other code or editor step required.

**DialogueCamSocket — required for all 5 NPCs:**
8. For each NPC skeleton, add a socket named exactly `DialogueCamSocket` positioned at eye level, facing outward. This is required for the camera blend to work.

**Expression setup:**
9. On each MetaHuman Animation Blueprint: add a morph target blend layer driven by `UFacialExpressionMapper` output. Wire `ENpcFacialExpression` → blend weights.

**Thinking state look-at (deferred from C++ — requires AnimBP):**
10. In each NPC's Animation Blueprint: add a "look-at" IK pass activated by a boolean `bThinking`. `UDialogueComponent` will set this flag when the LLM response is pending and clear it on response received. (The `bThinking` flag and its setter/broadcast will be added to `UDialogueComponent` in a future C++ pass once the AnimBP variable name is confirmed.)

**Checklist (manual):**
- [ ] Mira MetaHuman renders in `L_Tavern`; VRAM stat < 10 GB
- [ ] Sorn MetaHuman renders in `L_GuardBarracks`; VRAM stat < 10 GB
- [ ] Lira MetaHuman renders in `L_TavernBack`; Mira and Lira never simultaneously in GPU memory
- [ ] Aldric and Old Henryk humanoids placed in `L_MarketSquare`
- [ ] All 5 NPC actors have `DialogueCamSocket` added to their skeletons
- [ ] PIE: approach Mira → press E → camera blends smoothly (0.3 s) toward `DialogueCamSocket`
- [ ] PIE: close dialogue → camera blends back to player (0.4 s)
- [ ] `BP_NPC_Mira` expression layer changes when `ApplyExpression` is called

---

## Phase 2 — Greybox World (PIE verification)

**C++ status:** ✅ complete and committed (`feat(phase2): GreyboxWorldSubsystem + spawner layout wiring`).
**Why these need a human:** PIE play-test verifies that the procedural floor + triggers + NPC spawning work correctly at runtime with the live engine. Cannot be verified headlessly.

- [ ] **Greybox world smoke test** (press Play in `Lvl_ThirdPerson` or whatever your default map is; engine does NOT need to be running for this step):
  - [ ] Output Log shows `GreyboxWorldSubsystem: built at base=...` and `NpcSpawnerSubsystem: spawned 5 NPCs at base=...`
  - [ ] Five cube NPCs are visible in the level (labelled Mira, Lira, Aldric, Captain Sorn, Old Henryk)
  - [ ] Walk from PlayerStart toward +X: Output Log shows `Tick=1 Location=loc_tavern` when entering the tavern trigger region (within ~5 m of PlayerStart)
  - [ ] Continue along +X past 15 m: `Tick=2 Location=loc_market_square` logged on entry
  - [ ] Continue along +X past 30 m: `Tick=3 Location=loc_guard_barracks` logged on entry
  - [ ] Walk back to tavern: no double-tick (re-entry guard: same location → no additional tick)
  - [ ] Walk to the back room position (about 10 m in -Y from PlayerStart): no tick fires (`bFiresTick=false`)
  - [ ] Press E near any NPC → dialogue widget opens

---

## Phase 6 — Gossip Chain + Rumor Journal (editor session)

**C++ status:** ✅ complete and committed (`feat(phase6): GossipCacheSubsystem + FNpcStateSnapshot + RumorJournalWidget + NoticeBoard + Sorn quest gate`).
**Why these need the editor:** Fallback line authoring, widget layout (WBP_RumorJournal), BP_NoticeBoard placement, gossip chain 5/5 live verification, and greybox acceptance gate all require the Unreal Editor or a live engine.

- [x] *(C++ DEC-020 — built-in `NpcFallbackDefaults`)* **Author fallback line for Old Henryk** in `DA_NpcFallbackLines`. Open the asset (Content Browser → find `DA_NpcFallbackLines`), add one entry:
  - Key `old_henryk` → *"…Henryk squints at you and mutters something under his breath."*
  After this step, all 5 NPC fallback lines are authored (Mira + Lira from Phase 4, Aldric + Sorn from Phase 5, Henryk here).
- [x] *(C++ DEC-020 — `UNpcSpawnerSubsystem` spawns `ANoticeBoard` with these tiers + thresholds set in C++)* **Create `BP_NoticeBoard`** (Blueprint extending `ANoticeBoard` C++ base; prefix `BP_`). Open it and set the `RumorTiers` UPROPERTY array (3 entries):
  - Index 0: *"The northern roads are quiet. No news from the garrison."*
  - Index 1: *"Travelers have been talking about some skirmish up at the north pass. Hard to say what happened."*
  - Index 2: *"They say the whole northern garrison was wiped out in one night — a divine punishment, some claim."*
  Set `TierTickThresholds` to `[0, 2, 4]`.
- [x] *(C++ DEC-020 — two boards spawned by `UNpcSpawnerSubsystem`; `GetCurrentTierText()` is live for the gossip verification. NOTE: greybox boards have no visible mesh / E-examine popup yet — visual body + examine UI deferred to v2.)* **Place `BP_NoticeBoard`** actors:
  - One in `L_MarketSquare` at the notice board prop position.
  - One in `L_GuardBarracks` near the gate arch.
  Wire the E-examine trigger in Blueprint (box collision overlap → call `GetCurrentTierText()` → display in a popup UUserWidget or simple HUD text).
- [x] *(C++ DEC-020 — built in C++; `OnJournalRefreshed` populates cards in C++; opens with Tab)* **Create `WBP_RumorJournal`** — Widget Blueprint, parent class `RumorJournalWidget`. Add:
  - A `ScrollBox` named exactly `ChainScrollBox` (`BindWidgetOptional`).
  - Inside it, a `VerticalBox` named exactly `ChainContainer` (`BindWidgetOptional`).
  - Override `OnJournalRefreshed` in Blueprint: iterate `AllEntries`, skip entries where `bPlayerSpokeToNpc == false`, create a card row per entry with: NPC display name, distortion text, distortion badge (call `GetDistortionLabel(HopCount)`).
  - Bind Tab key (or `IA_Journal` input action) to toggle open/close from the player HUD or character Blueprint.
- [ ] **Gossip chain 5/5 gate** (requires Docker engine running + full golden path):
  Run the full golden path 5 times from a fresh seed:
  Tavern (speak with Mira, ≥2 exchanges) → Barracks (build trust with Sorn; he shares war info) → Tavern (tick fires) → Market (speak with Old Henryk).
  In all 5 runs: Henryk's dialogue response must contain the distorted war account (phrase from GossipText::HenrykDistorted). If any run fails: tune `gossipy` and `credulity` personality values in `Seed/DemoWorld_v1.json` and re-run `NpcEngine.SeedWorld`. Do not mark Phase 6 complete until 5/5 pass.
- [ ] **Greybox acceptance gate** — all 17 beats from §10 of `docs/game_design_roadmap.md` must be playable start-to-finish. All trust gates, quest steps, gossip chain, Rumor Journal, and faction fork must be functional. Any non-functional beat is a blocker for Phase 7.

## Phase 5 — Quest System + Faction Fork (editor session)

**C++ status:** ✅ complete and committed (`feat(phase5)`). QuestSubsystem, FactionSubsystem, NpcSaveGame, QuestLogWidget, QuestConfirmWidget, FactionForkWidget, NpcWorldSubsystem trust gate all committed.
**Why these need the editor:** Live endpoint verification, fallback line authoring, NPC capsule placement, WBP widget layout, trust-gate PIE test.

- [ ] **Verify quest lifecycle endpoint shapes** — run `GET http://localhost:8000/openapi.json` in a browser or via curl. Confirm the 6 shapes from DEC-027 match the live engine. If any field name differs, update `NpcQuestTypes.h` and the matching serializer in `NpcEngineJsonUtils.cpp`. Record confirmation (or patch notes) in DECISIONS.md as a DEC-027 update.
- [x] *(C++ DEC-020 — built-in `NpcFallbackDefaults`)* **Author fallback lines for Aldric and Captain Sorn** in `DA_NpcFallbackLines`. Open the asset (Content Browser → find `DA_NpcFallbackLines`), add two `FallbackLineByNpcId` entries:
  - Key `aldric_merchant` → *"…Aldric glances away nervously and doesn't reply."*
  - Key `captain_sorn` → *"…Sorn nods crisply but says nothing more."*
- [x] *(C++ DEC-020 — all spawned by `UNpcSpawnerSubsystem`)* **Place Slice-2 NPC capsules:**
  - `BP_NPC_Aldric` (parent `NpcActorBase`): `NpcId = aldric_merchant` FName constant, `DisplayName = "Aldric"`, `LocationId = loc_market_square`, placed in `L_MarketSquare`
  - `BP_NPC_Sorn` (parent `NpcActorBase`): `NpcId = captain_sorn` FName constant, `DisplayName = "Captain Sorn"`, `LocationId = loc_guard_barracks`, placed in `L_GuardBarracks`
  - `BP_NPC_Henryk` (parent `NpcActorBase`): `NpcId = old_henryk` FName constant, `DisplayName = "Old Henryk"`, `LocationId = loc_market_square`, placed in `L_MarketSquare`
- [x] *(C++ DEC-020 — built + auto-mounted to HUD)* **Create `WBP_QuestLog`** — Widget Blueprint, parent class `QuestLogWidget`. Add a Vertical Box named exactly `QuestList` (`BindWidget`). No Blueprint logic needed — C++ base handles population on `OnQuestActivated`.
- [x] *(C++ DEC-020 — built in C++)* **Create `WBP_QuestConfirm`** — Widget Blueprint, parent class `QuestConfirmWidget`. Add:
  - Text Block named `QuestTitleText` (`BindWidget`)
  - Button named `AcceptButton` (`BindWidget`) → calls `NativeOnAccept()`
  - Button named `DeclineButton` (`BindWidget`) → calls `NativeOnDecline()`
- [x] *(C++ DEC-020 — built in C++)* **Create `WBP_FactionFork`** — Widget Blueprint, parent class `FactionForkWidget`. Add:
  - Button named `ChoiceAButton` (`BindWidget`)
  - Button named `ChoiceBButton` (`BindWidget`)
  - Text Block named `ChoiceALabel` (`BindWidget`)
  - Text Block named `ChoiceBLabel` (`BindWidget`)
- [x] *(C++ DEC-020 — auto-mounted in `ADemoGameCharacter::BeginPlay`)* **Add `WBP_QuestLog` to the player HUD** — same pattern as `WBP_Dialogue` in Phase 4: create + `AddToViewport` from the character or a HUD Blueprint.
- [ ] **Test L_TavernBack streaming gate (PIE):**
  - Run `NpcEngine.SeedWorld` to reset engine state, then start PIE in `L_Tavern`
  - Approach Mira and exchange dialogue until accumulated trust ≥ 40 (`TRUST_GATE_2_MIRA` constant)
  - Confirm `UNpcWorldSubsystem::OnTavernBackUnlocked` fires (Output Log: `"TavernBack gate fired"`)
  - If the sub-level isn't streaming in automatically: in `L_Tavern` Level Blueprint (or player HUD), bind `OnTavernBackUnlocked` → call `ULevelStreamingDynamic::LoadLevelInstance` or make the streaming level visible. Record the wiring choice in DECISIONS.md.
- [ ] **Chain A end-to-end verification** (requires all Slice-2 NPCs placed + engine seeded + quest log wired):
  - Fresh save → investigate Mira (trust gate 1 at 25) → identify Aldric through 2+ conversations → quest log shows `find_wine_merchant` active → `deliver_amulet` appears → faction fork fires → faction standing change logged to Output Log
  - Confirm quest log shows `deliver_amulet` complete and `aldric_confession` step appears

---

## Asset import — MetaHuman clothing

**Status:** shortlist complete 2026-06-25; awaiting human shortlist approval.  
**Gate role:** Task B is the go/no-go gate for the photoreal cast (DEC-031). Do Mira first — she is the critical path. **Do not build MetaHuman faces until this skin test passes.**  
**Shortlist:** `project-harness/asset-shortlists/metahuman-clothing.md`  
**Verdict:** CONDITIONAL GO — see gate verdict at the bottom of the shortlist.

> **Pipeline note (verified 2026-06-25):** Quixel Bridge is being sunset. Do NOT use it. All asset acquisition is via the in-editor Fab plugin: **Windows → Fab**. MetaHuman Creator is also in-editor (Windows → MetaHuman Creator). Clothing lands in `/Game/Fab/MetaHumans/` after Add to Project.

---

### Pre-purchase checklist (do these BEFORE buying anything)

- [ ] Open the project in UE5.8 editor
- [ ] Windows → Fab → sign in with your Epic account
- [ ] In the Fab panel, search for each shortlist asset by name and confirm:
  - Current price matches the shortlist estimate
  - Asset page shows "Compatible with UE5.x" (click the asset listing in-editor)
  - For GrubyCommander and Medieval Priest & Nun: confirm price before committing (price unknown at research time)
  - For PolyWear Resizable Collection: confirm it includes a female-compatible tunic (browse screenshots)
  - For Medieval Priest & Nun: view screenshots to confirm the nun habit is hooded and reads as "dark commoner" for Lira
- [ ] Make your picks from the shortlist, then proceed to import steps below

---

### Path A — Fab Standard License assets (recommended picks for Mira, Aldric, Henryk, Lira)

These are purchased via Fab and use the in-editor Fab plugin. Steps apply to:  
**PolyWear Resizable Collection** (Mira), **GrubyCommander Modular** (Aldric + Henryk), **Medieval Priest & Nun** (Lira Option 1), **Meta Clothes Designer series** (any fallback).

**Step 1 — Purchase and download**
1. Windows → Fab (in-editor Fab plugin panel opens)
2. Click **Library** tab → find the purchased asset (may take 1–2 min to appear after purchase)
3. Click **Add to Project** on the asset → wait for download
4. Asset lands in `/Game/Fab/MetaHumans/<AssetName>/` — browse to it in Content Browser

**Step 2 — For PolyWear / GrubyCommander Parametric (type-a Outfit Asset)**
5. Navigate to `/Game/Fab/MetaHumans/<OutfitAssetName>/` in Content Browser
6. Open Mira's MetaHuman Blueprint (`BP_NPC_Mira` or whatever it is named in your project)
7. In the Blueprint Details, locate the **Outfit Asset** reference property (UE5.6+ MetaHuman)
8. Assign the downloaded outfit — the parametric system auto-fits to Mira's body shape
9. Hit **Compile + Save** on the BP; preview in Viewport to confirm clothing is visible

**Step 3 — For Meta Clothes Designer / Medieval Priest & Nun (type-b or type-c Skeletal Mesh)**
5. In Mira's MetaHuman Blueprint, go to the **Components** panel → click **Add Component** → select **Skeletal Mesh Component**
6. Name it (e.g. `SK_MiraOutfit`)
7. In the Details panel for the new component: **Skeletal Mesh** → assign the downloaded clothing skeletal mesh from `/Game/Fab/MetaHumans/`
8. Still on the component Details: scroll to **Leader Pose Component** → assign it to **Body** (the MetaHuman's body SkeletalMeshComponent)
9. On the **Body** component: hide body mesh sections covered by clothing. Under Materials, set material slots covered by the garment to a hidden material, OR under Mesh → Sections → disable relevant sections
10. **Compile + Save** the BP

**Step 4 — For Medieval Priest & Nun specifically (type-c: UE5 Mannequin → MetaHuman retarget)**  
*This applies ONLY if choosing Option 1 for Lira (the Nun outfit). If using Dress III or Yasin ERHAN instead, skip this.*
5. After Add to Project, note the Nun outfit's Skeletal Mesh references the UE5 Mannequin skeleton (Quinn/`SK_Mannequin_Female`)
6. Create a new **IK Retargeter**: Content Browser → right-click → Animation → IK Retargeter
7. Set **Source IK Rig** = Quinn's IK Rig (included with MetaHuman Mannequin content)
8. Set **Target IK Rig** = MetaHuman body IK Rig (from `/Game/MetaHumans/Common/`)
9. In the retargeter, tune pelvis/spine/shoulder chain mappings — MetaHuman proportions are close to Quinn so minimal adjustment is usually needed
10. Right-click the Nun Skeletal Mesh in Content Browser → **Retarget Skeletal Mesh** → use the retargeter you created → save as `SK_LiraNunOutfit_MH`
11. Attach `SK_LiraNunOutfit_MH` to Lira's MetaHuman Blueprint following Steps 5–10 in Path A / Step 3 above
12. Log your retarget quality result in DECISIONS.md (was the deformation acceptable?)

---

### Path B — DevonLux FBX assets (free CC-BY, for Sorn / Aldric fallback / Henryk fallback)

These are downloaded from Sketchfab and imported as FBX. No Epic login needed.  
Assets: **5 Piece Heavy Armor** (Sorn), **5 Piece Leather Peasant** (Aldric fallback), **4 Piece Cloth Armor** (Henryk fallback).

**Step 1 — Download from Sketchfab**
1. Open the Sketchfab listing URL (see shortlist)
2. Click **Download** (bottom of page) → select **Original format** (the pre-rigged FBX file)
3. Unzip to a staging folder: `C:\Users\lohan\Documents\hackathons\DemoGame\AssetStaging\character-clothing\DevonLux\<AssetName>\`

**Step 2 — Fix root bone name (CRITICAL — skip this and the mesh will not import correctly)**
4. You have two options:
   - **Option A (Blender, 5 min):** Open the FBX in Blender → Armature modifier → find bone named `root.00x` → rename to `root` → export FBX
   - **Option B (UE5 import dialog):** During UE5 import, check if a Bone Rename setting is available; otherwise use Blender

**Step 3 — Import as Skeletal Mesh in UE5**
5. Content Browser → right-click → **Import to Game** → select the FBX file
6. In the FBX Import dialog:
   - **Mesh Type:** Skeletal Mesh
   - **Skeleton:** click the dropdown → select `metahuman_base_skel` (found in `/Game/MetaHumans/Common/Common/` or search for it in the dialog)
   - **Import Normals:** Import Normals and Tangents
   - Uncheck **Import Materials** if you want to assign your own Megascans-based materials later
7. Click **Import All** → confirm no errors in the import log (warnings about bone count are OK; errors about missing skeleton bones indicate the rename was not done)
8. Save the resulting Skeletal Mesh asset to `/Game/Fab/MetaHumans/DevonLux/<AssetName>/` or `/Game/AssetStaging/character-clothing/`

**Step 4 — Attach to MetaHuman Blueprint**  
Same as Path A Steps 5–10 above (add Skeletal Mesh component, assign Leader Pose Component to Body, hide covered body sections).

**Attribution requirement (CC-BY):** Add the following credit to your project's credits screen or documentation:  
*"[Asset Name] by DevonLux (Sketchfab), licensed CC-BY 4.0 (https://creativecommons.org/licenses/by/4.0/)"*  
These assets are tagged `swap_for_commercial: YES` in the manifest.

---

### Skin test — Mira first (gate check)

Do this BEFORE purchasing/importing assets for the other 4 NPCs. If Mira's skin test fails, escalate before spending any budget on the others.

- [ ] Import one outfit for Mira following Path A above
- [ ] In PIE: approach Mira, press E, open dialogue — check that the outfit deforms correctly during the idle animation
- [ ] Rotate camera around Mira in close-up (dialogue cam distance): confirm clothing reads as medieval innkeeper (not sci-fi, not generic medieval)
- [ ] Zoom to face close-up: confirm no clipping between outfit and MetaHuman neck/jaw at typical dialogue cam angle
- [ ] Check Output Log for any Skeletal Mesh component errors
- [ ] ✅ **If test passes:** proceed to import remaining 4 NPC outfits (Sorn, Lira, Aldric, Henryk)
- [ ] ❌ **If test fails** (severe clipping, deformation artifacts, wrong skeleton):
  - Document the failure in DECISIONS.md
  - Try the next option from the shortlist for Mira
  - If ALL MetaHuman-native options fail: the photoreal-cast plan is at risk — escalate before building any MetaHuman faces

- [ ] Full 5-NPC outfit pass: repeat skin test for each NPC once Mira is confirmed
- [ ] Mark `- [x]` here when all 5 pass the skin test
