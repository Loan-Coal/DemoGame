# Unreal Editor Playbook — DemoGame Slice-1

> **Single authoritative source for all editor work.** Follow top-to-bottom. The C++ greybox already
> runs; this guide takes you from cube NPCs → photoreal faces, a dressed world, and a polished UI.
>
> **Easiest to modify later** is a first-class goal throughout. Every NPC avatar swap, widget restyle,
> and level redress is a data change — not a code change.

---

## Dependency Map (one screen)

```
[Phase 12 Block A — async appearance loader] ← MUST MERGE before any MetaHuman import
        │
        ▼
[§0 Project Setup] → plugins + folder layout + source control
        │
        ├──▶ [§1 Appearance & MetaHuman]
        │         │  Create faces in MetaHuman Creator
        │         │  Import to project → VRAM gate
        │         │  Register path in NpcAppearance / DA_NpcAppearance
        │         │  Add DialogueCamSocket to each skeleton
        │         ▼
        │    [§2 Animation]
        │         │  Acquire free Mixamo anims or use MetaHuman defaults
        │         │  AnimBP idle + talk blend space
        │         │  Wire UFacialExpressionMapper → morph targets
        │         ▼
        │    [§4 Levels / Environment]  ←— can start here in parallel with §1 and §2
        │         │  Acquire free Megascans kits via Fab plugin
        │         │  Dress each of the 4 levels
        │         │  Baked static lighting (no Lumen; budget rationale in §4)
        │         │  NavMesh volumes
        │         │  L_TavernBack sub-level streaming gate
        │         ▼
        │    [§5 Audio]
        │         │  Acquire free ambient + UI audio
        │         │  AudioVolumes per location
        │         │  PlaySound2D for UI events
        │         ▼
        └──▶ [§3 UI / UMG]  ←— fully independent; C++ defaults work without WBPs
                  │  Create WBP subclasses for each widget
                  │  Wire BindWidget slots (bind-name contract table below)
                  │  Assign DataAssets
                  │
                  ▼
         [§6 Final Acceptance Run — §14 checklist]
```

**Blocking rule:** Phase 12 Block A (async appearance loader in `ANpcGreyboxActor`) **must be committed
and the build green before the first MetaHuman Blueprint is imported.** Without it the avatar load path
is synchronous and will hitch. See ROADMAP Phase 12 Block A for the code task.

---

## §0 — Project Setup

### Required Plugins

Enable in **Edit → Plugins** (restart editor after enabling):

| Plugin | Why |
|--------|-----|
| **Enhanced Input** | IA_Interact / IA_Journal input actions; already enabled in ThirdPerson template |
| **MetaHuman** | In-editor MetaHuman Creator (Windows → MetaHuman) |
| **Fab** | In-editor asset acquisition (Windows → Fab); replaces the sunset Quixel Bridge |

> ⚠️ **Quixel Bridge is sunset — do not use it.** All asset acquisition (Megascans, character
> clothing, audio) goes through the in-editor Fab plugin: **Windows → Fab**.
> Source: [Buying MetaHumans from Fab](https://dev.epicgames.com/documentation/en-us/metahuman/buying-metahumans-from-fab) (verified 2026-06-25).

Optional but recommended:
- **NVIDIA DLSS** or **AMD FSR**: funds the VRAM budget for MetaHuman rendering. Search "DLSS" in
  Edit → Plugins. Enable DLSS Quality mode in Project Settings → Rendering → Scalability.
  ⚠️ Verify exact path in UE5.8 Project Settings — UI may differ across engine versions.

### Content/ Folder Layout

Create these folders in the Content Browser before importing any assets:

```
Content/
├── Blueprints/
│   ├── NPCs/            ← BP_NPC_Mira, BP_NPC_Sorn, BP_NPC_Lira, BP_NPC_Aldric, BP_NPC_Henryk
│   └── World/           ← BP_NoticeBoard (if using a BP subclass)
├── UI/                  ← WBP_Dialogue, WBP_RelationshipMeter, WBP_QuestLog, WBP_QuestConfirm,
│                           WBP_FactionFork, WBP_RumorJournal, WBP_ArrivalSubtitle
├── DataAssets/          ← DA_NpcFallbackLines, DA_MemoryBadgeLookup, DA_NpcAppearance,
│                           DA_LocationSubtitles, DA_FacialExpressionMap
├── MetaHumans/          ← auto-created by MetaHuman Creator on export
├── Fab/                 ← auto-created by Fab plugin on "Add to Project"
│   └── MetaHumans/      ← clothing assets from Fab
├── Materials/           ← M_ / MI_ prefixed
├── Textures/            ← T_ prefixed
├── StaticMeshes/        ← SM_ prefixed (environment static meshes)
├── Audio/               ← A_ prefixed (SoundCues, MetaSounds, ambient loops)
├── Animations/          ← Animation Sequences and Blend Spaces
└── Levels/              ← L_Tavern, L_TavernBack, L_MarketSquare, L_GuardBarracks
```

### Asset-Prefix Conventions (from CLAUDE.md)

| Prefix | Asset type |
|--------|-----------|
| `BP_` | Blueprint Actor |
| `WBP_` | Widget Blueprint |
| `DA_` | DataAsset |
| `SM_` | Static Mesh |
| `SK_` | Skeletal Mesh |
| `M_` | Material |
| `MI_` | Material Instance |
| `T_` | Texture |
| `A_` | Audio (SoundCue / MetaSound) |

### Source Control Hygiene

- `.gitignore` / LFS already excludes `DerivedDataCache/`, `Intermediate/`, `Binaries/`, `Saved/`.
- Git LFS covers `.uasset`, `.umap`, `.fbx`, `.png`, `.wav` and other binary types.
- Never commit `Config/NpcEngine.ini` (API key inside — already gitignored).
- Run `git lfs track` before staging any new binary file type.

**Done when:** Editor opens, all plugins enabled, folder structure visible in Content Browser.

---

## §1 — Appearance & MetaHuman

### Overview: The Hybrid Appearance Registry (DEC-039 / DEC-042)

Every NPC spawns via `UNpcSpawnerSubsystem`. Avatar resolution at spawn time:

```
DA_NpcAppearance entry (if set)
    → NpcAppearance C++ default map (headless one-line swap)
        → empty / cube stand-in
```

**Swap workflow (most common path after import):**
1. Import MetaHuman Blueprint to a known `/Game/...` path.
2. Either: edit one line in `Source/DemoGame/NPC/NpcAppearance.cpp` (headless, Claude can do this),
   OR: add a row to `Content/DataAssets/DA_NpcAppearance` in the editor (no recompile).
3. Press Play → cube → MetaHuman.

> **Phase 12 Block A prerequisite:** The async avatar load path must be in place before wiring any
> real MetaHuman. Check that `ANpcGreyboxActor::TrySpawnAvatar` uses `RequestAsyncLoad` (not
> `LoadSynchronous`). See ROADMAP Phase 12 Block A.

### Step 1a — VRAM Gate (must pass before importing Lira)

**Check VRAM with each MetaHuman scene before proceeding:**

1. Load a test level containing one MetaHuman actor.
2. Console command: `stat gpu` (type in editor viewport bottom bar or press `` ` `` to open console).
3. Confirm GPU Memory used < **10 GB** (budget for 12 GB ceiling with OS + driver overhead).
4. If > 10 GB: reduce MetaHuman LOD distance bias, lower texture pool, or enable DLSS/TSR. Record
   findings in DECISIONS.md before continuing.
5. **Do not import Lira until Mira's scene is under budget.**

### Step 1b — Create MetaHumans (in-editor MetaHuman Creator)

**Access:** Editor menu → **Windows → MetaHuman** (or search "MetaHuman" in the plugin panel).  
Source: confirmed in-editor since UE5.5+, UE5.8 release notes verified 2026-06-25.

Creation order (stagger to avoid wasted VRAM rework):

| Priority | NPC | Description | Body preset |
|----------|-----|-------------|-------------|
| P1 first | **Mira** | Late 30s–40s, warm but guarded, innkeeper | Female, medium |
| P1 parallel | **Sorn** | 45–55, stoic, weathered, military | Male, medium |
| P2 after Mira VRAM-validated | **Lira** | Early 30s, sharp, evasive, corner-booth rogue | Female, medium |
| P2 | **Aldric** | Middle-aged, respectable wine merchant | Male, medium |
| P2 | **Henryk** | Elderly preset, gossip-chain end NPC | Male, elderly |

**For each MetaHuman:**
1. Design face in MetaHuman Creator.
2. Click **Export to UE5 project** → MetaHuman is placed in `Content/MetaHumans/<Name>/`.
3. Note the Blueprint path (e.g., `/Game/MetaHumans/Mira/BP_Mira`). You'll need it for §1d.
4. Validate morph targets available for the 6 expression types (see §2 expression step).

> ⚠️ **DEC-031:** All 5 NPCs are MetaHuman. Fallback order if market scene (Aldric + Henryk) exceeds
> 10 GB VRAM: drop Henryk to Marketplace humanoid first, Lira second.

> ⚠️ **Mira + Lira VRAM isolation:** `L_TavernBack` is a sub-level of `L_Tavern`. Confirm Mira and
> Lira are **never simultaneously in GPU memory** — check `stat gpu` while toggling sub-level visibility.
> If they co-load: tighten the streaming boundary with an explicit unload call and record in DECISIONS.md.

### Step 1c — Create NPC Blueprints

For each MetaHuman, create an actor Blueprint **extending `ANpcActorBase`** (not the MetaHuman BP directly):

1. Content Browser → `Content/Blueprints/NPCs/` → right-click → Blueprint Class.
2. Search for `NpcActorBase` → Select it → Name the Blueprint with `BP_NPC_` prefix.
3. Open the Blueprint → Components panel → add the MetaHuman Skeletal Mesh component.
4. Set `NpcId` UPROPERTY to the matching FName constant:

| Blueprint | NpcId value | Location |
|-----------|------------|----------|
| `BP_NPC_Mira` | `mira_innkeeper` | `L_Tavern` |
| `BP_NPC_Sorn` | `captain_sorn` | `L_GuardBarracks` |
| `BP_NPC_Lira` | `lira_fence` | `L_TavernBack` (sub-level only) |
| `BP_NPC_Aldric` | `aldric_merchant` | `L_MarketSquare` |
| `BP_NPC_Henryk` | `old_henryk` | `L_MarketSquare` |

5. On each Blueprint's `DialogueComponent`: set **Fallback Lines Asset** = `DA_NpcFallbackLines`
   (create this DataAsset first — see §3 DataAssets).

### Step 1d — Register Avatar Path (the one-line swap)

**Option A — C++ (headless, Claude can do this):**
In `Source/DemoGame/NPC/NpcAppearance.cpp`, add one line per NPC to the default map:
```cpp
{ FName("mira_innkeeper"), FSoftClassPath("/Game/Blueprints/NPCs/BP_NPC_Mira.BP_NPC_Mira_C") },
```
Rebuild DemoGame module. The cube becomes a MetaHuman on next Play.

**Option B — DataAsset (editor, no recompile):**
1. Open `Content/DataAssets/DA_NpcAppearance` (create if missing: right-click → Miscellaneous →
   Data Asset → `NpcAppearanceData` class → name `DA_NpcAppearance`).
2. Add one row per NPC: Key = `mira_innkeeper` (FName), Value = pick `BP_NPC_Mira`.
3. Assign `DA_NpcAppearance` to `UNpcSpawnerSubsystem` — see `NpcSpawnerSubsystem.h` for the
   property name. ⚠️ Verify the UPROPERTY name in the header if this differs from expectation.

### Step 1e — Add DialogueCamSocket to Each Skeleton

The camera blend in `UDialogueComponent::StartDialogue` looks for a `UCameraComponent` attached at a
socket named exactly `DialogueCamSocket`. Without it the camera blend is a no-op (DEC-041).

**For each NPC skeleton:**
1. Content Browser → find the MetaHuman Face Skeletal Mesh (e.g., `SKM_Mira_Face`).
2. Double-click → opens the Skeleton Editor.
3. Skeleton Tree panel → find the `head` bone → right-click → **Add Socket**.
4. Name it exactly: `DialogueCamSocket` (case-sensitive, no spaces).
5. In the viewport, position the socket at eye level, facing outward (away from the face):
   - X: ~10–15 cm forward from the face
   - Z: roughly at eye bridge height
   - Rotate so the camera looks back at the NPC's face
6. Click the socket → Details panel → **Add Preview Asset** → add a camera cone mesh to visualize
   framing. The camera should frame the NPC face in a close-up from the player's perspective.
7. Save the Skeleton.

**Then add a UCameraComponent to the NPC Blueprint:**
1. Open `BP_NPC_Mira` → Components → Add → **Camera**.
2. Attach it to `DialogueCamSocket` (drag the Camera onto the socket in the Components hierarchy).
3. Adjust FOV (60–70° typical for dialogue close-up).
4. Compile + Save.

Repeat for all 5 NPC Blueprints.

**Done when:** `stat gpu` < 10 GB in each single-NPC scene; all 5 Blueprints have `DialogueCamSocket`;
PIE → approach Mira, press E → camera blends smoothly to face close-up.

---

## §2 — Animation

### 2a — Acquire Free Animations (Mixamo)

**Source:** [mixamo.com](https://www.mixamo.com) — free with Adobe account.  
Export: FBX for Unity (no skin) for animation clips, or FBX (with skin) for the first clip to get the skeleton.

**Animations to acquire:**

| Purpose | Mixamo search term | Notes |
|---------|-------------------|-------|
| Idle (standing, relaxed) | "Idle" | For conversation default |
| Talking (head nods, hand gestures) | "Talking", "Standing Talking" | Loop-friendly |
| Thinking (slight look-away, fidget) | "Thinking" | Used during LLM wait |

> ⚠️ **MetaHuman skeleton compatibility:** Mixamo animations are rigged to the Mixamo skeleton, not
> `metahuman_base_skel`. You need either (a) use the MetaHuman sample animations from Epic's
> MetaHuman Sample project (free on Fab: search "MetaHuman Sample Content"), or (b) retarget Mixamo
> anims to `metahuman_base_skel` via the IK Retargeter.
>
> **Recommended (simpler):** Use MetaHuman's built-in sample animations — search "MetaHuman Sample"
> in the Fab plugin (Windows → Fab). These are pre-fitted to the MetaHuman skeleton. If a specific
> Mixamo anim is desired, create an IK Retargeter (Content Browser → right-click → Animation →
> IK Retargeter → Source IK Rig = Mixamo IK rig → Target = MetaHuman IK rig).
>
> ⚠️ Verify current MetaHuman Sample Content availability in Fab at time of setup.

### 2b — Import Animations

1. For MetaHuman Sample: Fab plugin → search "MetaHuman Sample Content" → Add to Project → lands in
   `/Game/Fab/MetaHumans/MetaHumanSample/`.
2. For Mixamo FBX: Content Browser → `Content/Animations/` → Import → FBX Import dialog:
   - Mesh Type: **Animation Only** (if skeleton already exists)
   - Skeleton: pick `metahuman_base_skel`
   - Check "Import Animations"

### 2c — Create Animation Blueprint (AnimBP)

For each MetaHuman Blueprint, create an Animation Blueprint:

1. Content Browser → `Content/Animations/` → right-click → **Animation Blueprint**.
2. Skeleton: pick the MetaHuman face/body skeleton.
3. Name: `ABP_Mira` (no WBP_ prefix; animation blueprints use `ABP_` conventionally —
   ⚠️ the project CLAUDE.md doesn't define an AnimBP prefix; use `ABP_` as standard UE convention).
4. Open the AnimBP → AnimGraph tab:
   - Add a **Blend Space** node using the idle + talking animations.
   - Add a **Cached Pose** for the thinking idle.
   - Final Output Pose node.

**Thinking state wire (bThinking flag):**
The `UDialogueComponent` sets a `bThinking` flag when an LLM request is pending. This requires:
1. A `bool bThinking` variable in the AnimBP.
2. In the AnimBP EventGraph: bind to `UDialogueComponent::OnFacialExpression` or use a Blueprint
   interface call.
3. In the AnimGraph: when `bThinking == true`, blend to the thinking idle; reset on response received.

> The exact AnimBP variable name `bThinking` must match what `UDialogueComponent` sets. Confirm the
> UPROPERTY/function name in `DialogueComponent.h` before wiring — as of Phase 7 C++, the setter
> is deferred pending AnimBP confirmation (DEC-041).

### 2d — Wire Facial Expression Morph Targets

`UFacialExpressionMapper::ApplyExpression` sets morph target weights on the face SkeletalMeshComponent.
The mapper uses C++ default placeholder names; override via `DA_FacialExpressionMap` once you know the
actual MetaHuman morph target names.

**Step 1 — Discover morph target names:**
1. Open `BP_NPC_Mira` in the editor → select the Face component.
2. Details panel → **Morph Targets** section lists all available targets.
3. Record the names for the 6 expression types:

| Expression | What to look for on the MetaHuman |
|-----------|----------------------------------|
| `Neutral` | Default / zero pose (no morph) |
| `Happy` | `mouthSmileLeft`, `mouthSmileRight` or similar |
| `Wary` | `browDownLeft`, `browDownRight` or similar |
| `Fearful` | `eyeWideLeft`, `eyeWideRight` or similar |
| `Angry` | `browLowererLeft`, `browLowererRight` or similar |
| `Sad` | `mouthFrownLeft`, `mouthFrownRight` or similar |

> ⚠️ Exact morph target names vary by MetaHuman version and UE5.8 ARKit shape naming. Always read
> the names from the Morph Targets panel on your specific import — do not rely on memorized names.

**Step 2 — Create DA_FacialExpressionMap:**
> ⚠️ The C++ class for `DA_FacialExpressionMap` may need to be created if not already present.
> `UFacialExpressionMapper::FacialExpressionMapAsset` is declared as `TSoftObjectPtr<UDataAsset>`.
> Check `Source/NpcEngineClient/Public/FacialExpressionMapper.h` — if a dedicated UCLASS subclass
> isn't defined, create one in `NpcEngineClient` with `TMap<ENpcFacialExpression, FFacialMorphEntry>`.
> This is a Phase 12 / post-import task; the C++ defaults work until then.

**Step 3 — Wire in AnimBP:**
1. In the AnimBP AnimGraph: after the Blend Space node, add a **Set Morph Target** node.
2. Set the morph target name from a Blueprint variable (float, driven by the expression mapper).
3. In EventGraph: create a custom event `OnExpressionChanged(FName MorphTargetName, float Weight)`.
4. In `BP_NPC_Mira` Blueprint (not AnimBP): bind `UDialogueComponent::OnFacialExpression` →
   call `ApplyExpression` on the UFacialExpressionMapper instance, which sets the weight directly.

> Note: `ApplyExpression` calls `SetMorphTarget` on the SkeletalMeshComponent directly (no AnimBP
> variable needed unless you want AnimBP-driven blending). For Phase 7, direct `SetMorphTarget` is
> the implemented path.

**Done when:** PIE → initiate dialogue with Mira → `facial_expression` payload changes Mira's face
expression; `stat gpu` < 10 GB in each single-NPC scene.

---

## §3 — UI / UMG

### The Bind-Name Contract (exhaustive, exact)

All 6 widget base classes build their own legible layout in C++ when no Blueprint designer layout is
present (DEC-020). **WBP subclasses are purely additive** — you add visual art; you do not add logic.

Every `BindWidgetOptional` slot: the widget compiles and runs without binding. If you bind a slot, the
**widget type and name must match exactly** (case-sensitive). A type mismatch causes a PIE crash.

| WBP Name | C++ Parent Class | Bind Name | UMG Widget Type | Bind Kind |
|----------|-----------------|-----------|-----------------|-----------|
| `WBP_Dialogue` | `UDialogueWidgetBase` | `InputText` | **Editable Text** (`UEditableText`) | `BindWidgetOptional` |
| `WBP_Dialogue` | `UDialogueWidgetBase` | `ResponseText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_Dialogue` | `UDialogueWidgetBase` | `ResponseScroll` | **Scroll Box** (`UScrollBox`) | `BindWidgetOptional` |
| `WBP_Dialogue` | `UDialogueWidgetBase` | `ThinkingIndicator` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_Dialogue` | `UDialogueWidgetBase` | `MemoriesBadge` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_Dialogue` | `UDialogueWidgetBase` | `SendButton` | **Button** (`UButton`) | `BindWidgetOptional` |
| `WBP_RelationshipMeter` | `URelationshipMeterWidget` | `TrustText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_RelationshipMeter` | `URelationshipMeterWidget` | `FearText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_RelationshipMeter` | `URelationshipMeterWidget` | `AffectionText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_QuestLog` | `UQuestLogWidget` | `QuestList` | **Vertical Box** (`UVerticalBox`) | `BindWidgetOptional` |
| `WBP_QuestConfirm` | `UQuestConfirmWidget` | `QuestTitleText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_QuestConfirm` | `UQuestConfirmWidget` | `AcceptButton` | **Button** (`UButton`) | `BindWidgetOptional` |
| `WBP_QuestConfirm` | `UQuestConfirmWidget` | `DeclineButton` | **Button** (`UButton`) | `BindWidgetOptional` |
| `WBP_FactionFork` | `UFactionForkWidget` | `ChoiceAButton` | **Button** (`UButton`) | `BindWidgetOptional` |
| `WBP_FactionFork` | `UFactionForkWidget` | `ChoiceBButton` | **Button** (`UButton`) | `BindWidgetOptional` |
| `WBP_FactionFork` | `UFactionForkWidget` | `ChoiceALabel` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_FactionFork` | `UFactionForkWidget` | `ChoiceBLabel` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_RumorJournal` | `URumorJournalWidget` | `ChainScrollBox` | **Scroll Box** (`UScrollBox`) | `BindWidgetOptional` |
| `WBP_RumorJournal` | `URumorJournalWidget` | `ChainContainer` | **Vertical Box** (`UVerticalBox`) | `BindWidgetOptional` |
| `WBP_ArrivalSubtitle` | `UArrivalSubtitleWidget` | `SubtitleText` | **Text Block** (`UTextBlock`) | `BindWidgetOptional` |
| `WBP_ArrivalSubtitle` | `UArrivalSubtitleWidget` | `FadeOutAnimation` | **Widget Animation** | `BindWidgetAnimOptional` |

> **`FadeOutAnimation`** is a Widget Animation, not a widget slot. Create it in the Animations panel
> of `WBP_ArrivalSubtitle` (toolbar → **Animations** tab → **+Animation** → name it
> `FadeOutAnimation`). It must be named exactly `FadeOutAnimation` and bound with `BindWidgetAnimOptional`.

> **`WBP_ArrivalSubtitle` is Abstract** (`UCLASS(Abstract)`): you cannot instantiate it directly.
> You must create a Blueprint subclass with the `WBP_` prefix. All other widget C++ base classes
> dropped `Abstract` per DEC-020 and can be instantiated from C++.

### DataAssets to Create

Create each in `Content/DataAssets/` via **right-click → Miscellaneous → Data Asset → pick class**:

| Asset Name | C++ Class | Properties to fill | Who uses it |
|-----------|-----------|--------------------|------------|
| `DA_NpcFallbackLines` | `NpcFallbackLinesAsset` | `FallbackLineByNpcId` TMap — key = NPC FName, value = authored FText | `UDialogueComponent.FallbackLinesAsset` on each NPC actor |
| `DA_MemoryBadgeLookup` | `MemoryBadgeLookupAsset` | `BadgeTextByMemoryId` TMap — key = memory node ID FName, value = authored FText | `UDialogueWidgetBase.MemoryBadgeLookup` on `WBP_Dialogue` defaults |
| `DA_NpcAppearance` | `NpcAppearanceData` | `AvatarByNpcId` TMap — key = NPC FName, value = soft class path to BP | Optional override for avatar swap without recompile |
| `DA_LocationSubtitles` | `LocationSubtitleData` | `SubtitleByLocation` TMap — key = `loc_*` FName, value = authored FText | `UArrivalSubtitleWidget.SubtitleData` on `WBP_ArrivalSubtitle` |

**Fallback line authored text (enter into DA_NpcFallbackLines):**

| Key (FName) | Authored fallback text |
|------------|----------------------|
| `mira_innkeeper` | *"…Mira seems distracted and doesn't respond."* |
| `lira_fence` | *"…Lira shrugs and looks away."* |
| `aldric_merchant` | *"…Aldric glances away nervously and doesn't reply."* |
| `captain_sorn` | *"…Sorn nods crisply but says nothing more."* |
| `old_henryk` | *"…Henryk squints at you and mutters something under his breath."* |

> These are C++ defaults in `NpcFallbackDefaults.h`. The DataAsset overrides them for higher-quality
> authored lines. Creating the DataAsset is optional for the greybox; required for the art pass.

**Location subtitle text (enter into DA_LocationSubtitles):**

| Key (FName) | Subtitle text |
|------------|---------------|
| `loc_tavern` | *"The Broken Flagon"* |
| `loc_market_square` | *"Market Square"* |
| `loc_guard_barracks` | *"Guard Barracks"* |

> `loc_tavern_back` intentionally has no entry — Lira's back room has `bFiresTick=false` and no subtitle.

### How to Create a WBP Subclass

1. Content Browser → `Content/UI/` → right-click → **User Interface → Widget Blueprint**.
2. In the "Pick Parent Class" dialog, search for the C++ parent (e.g., `DialogueWidgetBase`).
3. Name it with `WBP_` prefix (e.g., `WBP_Dialogue`).
4. Open the Widget → **Designer** tab: lay out widgets with the exact names from the bind-name table.
   - Drag widgets from the Palette onto the canvas.
   - In the Details panel, set the widget's **name** field (top of Details) to match the bind name.
   - The name must be typed exactly — it's case-sensitive.
5. No Blueprint logic needed — C++ handles all behaviour.
6. Assign DataAssets in the widget **Class Defaults** (open Graph → Class Defaults panel):
   - `WBP_Dialogue` Class Defaults → `MemoryBadgeLookup` = `DA_MemoryBadgeLookup`.
   - `WBP_ArrivalSubtitle` Class Defaults → `SubtitleData` = `DA_LocationSubtitles`.

### Visual Art Pass Guidance

| Widget | Theme | Key elements |
|--------|-------|-------------|
| `WBP_Dialogue` | Parchment / dark tavern-wood | Opaque background panel; `ResponseText` scrollable history; `InputText` with send icon; `MemoriesBadge` as floating amber note |
| `WBP_RelationshipMeter` | Compact HUD overlay | NPC portrait (`TSoftObjectPtr<UTexture2D>` — soft ref only); bar or signed number display for trust/fear/affection; spring-settle animation on `OnRelationshipUpdated` |
| `WBP_QuestLog` | Parchment list | `QuestList` VerticalBox with active quest rows; completed steps show a checkmark icon (`T_Icon_Checkmark`) |
| `WBP_QuestConfirm` | Modal overlay | `QuestTitleText` legible above two buttons |
| `WBP_FactionFork` | Modal overlay | Two large buttons with `ChoiceALabel` / `ChoiceBLabel` text; choice is irreversible — make it clear |
| `WBP_RumorJournal` | Journal / parchment | Chain card rows inside `ChainContainer`; distortion badges: green (`T_Badge_Firsthand`), yellow (`T_Badge_Rumor`), red (`T_Badge_Distorted`); only show entries where `bPlayerSpokeToNpc == true` |
| `WBP_ArrivalSubtitle` | Cinematic letterbox | Centered text, serif font, `FadeOutAnimation` fades in 0.3 s then out at 2.7 s |

### HUD Mounting

`ADemoGameCharacter::BeginPlay` auto-mounts `WBP_Dialogue`, `WBP_RelationshipMeter`, `WBP_QuestLog`
and `WBP_RumorJournal` (Tab key). **You do not need to add them manually.**

`WBP_ArrivalSubtitle` must be added manually to the player HUD:
1. Open `BP_ThirdPersonCharacter` → Event Graph → BeginPlay event.
2. Create Widget → Class = `WBP_ArrivalSubtitle` → Add to Viewport.
3. Connect to the chain after the existing widget setup.

**Done when:** PIE → all widgets mount and display without error; bind-name slots are filled with
correct widget types; DataAssets assigned; arrival subtitle shows on location change.

---

## §4 — Levels / Environment

### Lighting Strategy (no Lumen — 12 GB VRAM budget)

**Decision:** No Lumen in demo v1. Baked static lightmaps for all geometry + stationary dynamic
lights (candles, hearth) for key hero sources only. DLSS/TSR funds the MetaHuman rendering budget.

**Rationale:** Lumen GI + MetaHuman textures combined may exceed the 12 GB VRAM ceiling on some
configurations. Baked lightmaps are free at runtime; the photorealistic look is carried primarily by
the MetaHuman faces in dialogue close-ups — not by global illumination across the environment.

> Note: DEC-030 explored enabling Lumen for the hearth-lit tavern interior as an upgrade path once
> VRAM profiling confirms the budget. If you want to test Lumen: Enable it in Project Settings →
> Rendering → Global Illumination → Lumen; check `stat gpu` in each scene; fall back to baked if
> > 10 GB. Record the result in DECISIONS.md.

**In Project Settings → Rendering (recommended defaults for this project):**
- Global Illumination: **Static / None** (baked lightmaps)
- Reflections: **Screen Space Reflections** or **None** (cheaper than Lumen reflections)
- Enable **DLSS** or **FSR** for upscaling

### 4a — Acquire Free Megascans Environment Kits

Via **Windows → Fab** → sign in with Epic account → search for each kit → **Add to Project**.

Megascans assets are free for Unreal Engine users (Epic Games license). Do not use Quixel Bridge.

**Search criteria — what to find (cannot verify specific pack names at time of writing; search by criteria):**

| Kit needed | Search term in Fab | Target quality |
|-----------|-------------------|----------------|
| Medieval tavern interior | `"medieval tavern interior"` or `"medieval inn"` Megascans | Stone/wood walls, ceiling beams, hearth prop, bar counter |
| Medieval exterior / cobblestone | `"medieval cobblestone"` or `"nordic village"` Megascans | Cobblestone ground material, market stalls, awnings |
| Stone walls (shared across kits) | `"stone wall medieval"` Megascans | Shareable Material Instance between indoor and outdoor |

> ⚠️ Verify each pack actually exists and is free/Megascans-licensed when you search in the Fab
> plugin. Do not assume specific pack names — Fab's catalogue changes. If a free Megascans interior
> kit is not available at search time, use individual Megascans surface materials (stone, wood planks,
> roughcast plaster) and combine them with free SM_ mesh primitives.

**After "Add to Project":** assets land in `/Game/Fab/<PackName>/`. Move or reference in place.
Use **Material Instances** (`MI_` prefix) when reusing a base material with different parameters
(e.g., same stone material with different scale/roughness for floor vs wall).

### 4b — Create the Four Levels

1. **File → New Level → Empty Level** (not World Partition — use the classic level format for sub-level streaming compatibility).
   ⚠️ In UE5.4+, new levels may default to World Partition. Check **World Settings** → **World Partition** → disable if enabled, or create a non-WP template.
2. Save to `Content/Levels/` with the name below:

| File name | LocationId | bFiresTick |
|-----------|-----------|------------|
| `L_Tavern.umap` | `loc_tavern` | `true` |
| `L_TavernBack.umap` | `loc_tavern_back` | `false` |
| `L_MarketSquare.umap` | `loc_market_square` | `true` |
| `L_GuardBarracks.umap` | `loc_guard_barracks` | `true` |

**`L_TavernBack` as a persistent sub-level of `L_Tavern`:**
1. Open `L_Tavern`.
2. Window → **Levels panel** → **+ Add Existing** → pick `L_TavernBack`.
3. Right-click `L_TavernBack` in the Levels panel → **Change Streaming Method** → **Blueprint**.
4. Set `L_TavernBack` to **Not Always Loaded** (hidden by default).
5. The C++ streaming gate in `UNpcWorldSubsystem::OnTavernBackUnlocked` fires when Mira trust ≥ 40.
   Wire that delegate to load `L_TavernBack` in the `L_Tavern` Level Blueprint:
   - Level Blueprint → Event BeginPlay → Get Game Instance Subsystem (NpcWorldSubsystem) →
     Bind Event to OnTavernBackUnlocked → call `Load Level Instance` or make sub-level visible.
   - ⚠️ Record the streaming implementation choice in DECISIONS.md (level streaming vs LoadLevelInstance).

### 4c — Dress Each Level

**`L_Tavern` — medieval interior (warm):**
- Floor: stone flag or rough wood plank material (`MI_Floor_Tavern`).
- Walls: roughcast plaster or timber-framed materials (`MI_Wall_Tavern`).
- Props: hearth (`SM_Hearth`), bar counter (`SM_Bar`), wooden tables (`SM_Table_Medieval`),
  chairs (`SM_Chair_Medieval`), candle holders (`SM_Candle`), ceiling beam (`SM_Beam`).
- Lighting: 2–3 stationary `Point Lights` (candles, hearth glow) + 1 `Rect Light` for the hearth.
  Keep hero lights stationary (not moveable) for baked indirect contribution.
- Place `BP_NPC_Mira` actor; confirm `NpcId = mira_innkeeper`.

**`L_TavernBack` — dim storeroom:**
- Props: crates (`SM_Crate`), barrels (`SM_Barrel`), rough stone wall sections.
- Post-process volume: low exposure (`Min/Max Brightness: 0.3`), desaturated (`Color Saturation: 0.7`).
- Reduce shadow map resolution: Directional Light → Shadow Map Resolution = 512.
- Place `BP_NPC_Lira` actor; confirm `NpcId = lira_fence`.

**`L_MarketSquare` — outdoor courtyard:**
- Ground: cobblestone material (`MI_Cobblestone`).
- Props: merchant stalls (`SM_MerchantStall`), awnings (`SM_Awning`), notice board prop (`SM_NoticeBoard`).
- Place `BP_NoticeBoard` actor at the SM_NoticeBoard prop position. Set `RumorTiers` + `TierTickThresholds`
  UPROPERTY arrays (or use C++ defaults already in `NpcSpawnerSubsystem`).
- Place `BP_NPC_Aldric` and `BP_NPC_Henryk`.
- Sky: **Sky Atmosphere** component + **Directional Light** (Sun) + **SkyLight** + **Exponential Height Fog**.
  Set Directional Light to **Stationary** for baked shadows + dynamic spec.

**`L_GuardBarracks` — courtyard:**
- Props: stone wall segments (`SM_StoneWall`), gate arch (`SM_GateArch`), training props (non-interactive).
- Reuse `MI_Stone_*` Material Instances from market kit to share texture memory.
- Place `BP_NPC_Sorn`; confirm `NpcId = captain_sorn`.
- Place second `BP_NoticeBoard` near the gate.

### 4d — Build Lightmaps

1. **Build All** → Build Lighting: **Build → Build All Levels → Build Lighting Only**.
2. Resolve all **Unlit** / **invalid lightmap UV** warnings in the Message Log before proceeding.
   Common fix: SM_ static mesh → Details → Lightmap Resolution = 64 or 128.
3. After build, check `stat gpu` in each level with MetaHumans placed.

### 4e — NavMesh Volumes

In each level, place a `NavMeshBoundsVolume`:
- Modes → Volumes → drag `NavMeshBoundsVolume` into the level.
- Scale to cover the playable area.
- Press **P** to visualize the NavMesh (green = navigable).

> NavMesh is not functional for NPC pathfinding in demo v1 but is required to prevent actor
> placement collision issues. NPC actors stand at spawned positions; they do not pathfind.

### 4f — Level Streaming Performance Check

Transition `L_Tavern` ↔ `L_MarketSquare` in PIE at 60 fps target:
- If frame transition causes a visible stall (> 1 frame): add a black-fade `UUserWidget` (0.15 s)
  or pre-stream `L_MarketSquare` on tavern entry.
- Record the mitigation in DECISIONS.md.

**Done when:** All 4 levels dressed; lightmaps built with no warnings; NavMesh volumes placed;
`stat gpu` < 10 GB per scene; streaming transitions smooth at 60 fps.

---

## §5 — Audio

### 5a — Acquire Free Ambient Audio

Via **Windows → Fab** → sign in → search by criteria. Audio assets must be free or Megascans-licensed.

| Location | Search criteria in Fab | Audio target |
|----------|----------------------|--------------|
| L_Tavern | `"tavern ambience"` or `"medieval inn ambient"` | Hearth crackle, low murmur, wood creak loop |
| L_MarketSquare | `"medieval market ambience"` or `"outdoor crowd"` | Bustle, wind, cart sounds |
| L_GuardBarracks | `"military barracks ambience"` or `"outdoor wind"` | Distant drills, metal clank, wind |

Alternative free source: [freesound.org](https://freesound.org) — filter by CC0 license. Download WAV/OGG.

> ⚠️ Verify each audio pack exists and is appropriately licensed before importing. Cannot confirm
> specific Fab audio pack names at this time — search in-editor.

**Import:** Content Browser → `Content/Audio/` → Import → WAV files. Create **SoundCue** or
**MetaSound** assets (prefix `A_`) wrapping the raw audio clips.

### 5b — Free UI Audio

| Sound | Search criteria | Asset name |
|-------|----------------|------------|
| Quest accept | `"confirmation chime"` or `"UI accept"` | `A_UI_QuestAccept` |
| Journal open/close | `"parchment rustle"` or `"paper scroll"` | `A_UI_JournalOpen` |
| Trust increase | `"positive ping"` or `"subtle bell"` | `A_UI_TrustIncrease` |
| Faction choice | `"weighted neutral tone"` or `"decision sound"` | `A_UI_FactionChoice` |

### 5c — Place AudioVolumes

In each level:
1. Modes → Volumes → drag **AudioVolume** into the level.
2. Scale to cover the playable area (or room area).
3. Details → **Reverb Settings** (set reverb preset: `Tavern` → small room; `MarketSquare` → open space).
4. Details → **Ambient Sound** or use a separate `AAmbientSound` actor:
   - Place an `AAmbientSound` actor → assign the `A_Amb_<Location>` SoundCue.
   - Check **Looping** on the SoundWave.
   - Attenuate (use Attenuation Settings) if needed to fade at volume edge.

> No inline audio is hardcoded in C++. All audio is fired via `UGameplayStatics::PlaySound2D` calls
> in Blueprint widget event handlers (already wired in the C++ base classes as `BlueprintNativeEvent`
> stubs — override in the WBP subclass to play the `A_UI_*` assets).

**Done when:** PIE entering each level triggers ambient audio loop; UI sounds fire on quest accept,
journal open/close, trust increase, and faction choice.

---

## §6 — Final Acceptance Run

> This section is the **only place you test.** Do all editor work first (§0–§5), then run these
> checks once. Do not test piecemeal during asset import; trust the per-section "Done when" items
> for intermediate validation.

**Prerequisites before running:**
1. Docker NPC Engine running on `localhost:8000`.
2. Run `NpcEngine.SeedWorld` in the UE4 console (or confirm auto-seed ran — check Output Log for
   `NpcAutoSeedSubsystem: seeding…`).
3. PIE (Play in Editor) active with the default/tavern level loaded.

### §14 Acceptance Criteria Checklist

All items must pass. No partial credit.

**Setup**
- [ ] Engine health check returns 200 (`NpcEngine.Smoke` exec command → Output Log shows `Health OK`).
- [ ] Seeder runs to completion with 0 errors (Output Log shows no `LogNpcEngine Error` from seeder).
- [ ] `NpcEngine.Smoke` Exec command returns a non-empty `npc_response` in Output Log.

**World + Navigation**
- [ ] Player navigates between all three named locations (Tavern → Market → Barracks). Tick fires
  and arrival subtitle (`WBP_ArrivalSubtitle`) appears on each transition.
- [ ] Tavern back room (`L_TavernBack`) does not fire a tick. Sub-level streams in without a visible hitch.
- [ ] Re-entering the same location does not fire a second tick.

**Dialogue + Trust**
- [ ] Player initiates dialogue with Mira. Types a message. Receives a response within 30 seconds
  or a graceful fallback line (not a hang or error popup).
- [ ] Trust meter (`WBP_RelationshipMeter`) updates visibly after each exchange.
- [ ] The `memories_recalled` badge (`MemoriesBadge` in `WBP_Dialogue`) appears at least once.
- [ ] MetaHuman expressions animate during dialogue in response to the `facial_expression` payload.
- [ ] Thinking animation plays during LLM wait. Input field is read-only during wait.

**Investigation + Trust Gates**
- [ ] Trust gate 1 (Mira trust > 25): Mira reveals information about Aldric's situation. Gate clears
  in dialogue — no waypoint marker required.
- [ ] Player identifies Aldric through 2+ NPC conversations. No map marker. Observer can confirm
  the player discovered Aldric socially (not via UI prompt).

**Quest System**
- [ ] Quest log (`WBP_QuestLog`) shows `find_wine_merchant` as the first active step.
- [ ] Chain A completes: quest log shows `deliver_amulet` complete; `aldric_confession` step appears.
- [ ] Faction fork fires (`WBP_FactionFork` appears). Faction standing changes (logged or visible
  in relationship meter / Output Log).
- [ ] Lira's back room (`L_TavernBack`) is inaccessible below gate 2 trust threshold and accessible
  above it.

**Gossip Chain + Journal**
- [ ] After the golden path (Tavern → Barracks → Tavern → Market with appropriate conversations),
  Old Henryk's dialogue contains the distorted war account.
- [ ] A naive observer who heard Sorn's account can identify Henryk's as a distortion of it.
- [ ] Rumor Journal (Tab) shows the Sorn → Mira → Henryk chain with distortion level labels
  ("Firsthand" / "Rumor" / "Distorted") at each hop.
- [ ] Sorn trust gate unlocks `patrol_duty`. Quest appears in the quest log.

**Stability**
- [ ] No crashes across the full golden path (all 17 narrative beats).
- [ ] LLM timeout produces a fallback line — no hang, no freeze, no error popup.
- [ ] `DegradationLevel != "full"` is logged silently; it does not break dialogue or UI.

**VRAM Budget**
- [ ] `stat gpu` < 10 GB in `L_Tavern` (Mira present).
- [ ] `stat gpu` < 10 GB in `L_GuardBarracks` (Sorn present).
- [ ] `stat gpu` < 10 GB in `L_MarketSquare` (Aldric + Henryk present — the hardest case).
- [ ] Mira and Lira confirmed never simultaneously in GPU memory.

**Playtest Gate**
- [ ] A naive player (who has not seen the demo) reaches beat 15 (the gossip reveal) within
  25 minutes without being guided.

**Done when:** Every checkbox above is ticked. This is the demo-complete state.

---

## Appendix A — Asset Quick Reference

| Asset | Source | License | Notes |
|-------|--------|---------|-------|
| MetaHuman faces | MetaHuman Creator (in-editor, Windows → MetaHuman) | Epic / MetaHuman | Free |
| DevonLux Heavy Armor (Sorn) | Sketchfab CC-BY | CC-BY 4.0 | Root bone rename required |
| DevonLux Leather Peasant (Aldric free pick) | Sketchfab CC-BY | CC-BY 4.0 | Tall-male body only |
| DevonLux Cloth Armor (Henryk free pick) | Sketchfab CC-BY | CC-BY 4.0 | Tall-male body only |
| Free CC-BY dress bases (Mira/Lira $0 path) | Sketchfab CC-BY | CC-BY 4.0 | Requires Blender skin-wrap — see `appendix-clothing-blender.md` |
| Megascans environment kits | Fab plugin (Windows → Fab) | Epic / Megascans | Free in UE |
| Mixamo animations | mixamo.com | Free with Adobe account | IK retarget may be needed |
| Free audio | freesound.org (CC0) or Fab | CC0 or Epic | Verify per-asset |

For paid clothing options (PolyWear, GrubyCommander, Medieval Priest & Nun): see
`project-harness/asset-shortlists/metahuman-clothing.md`.

## Appendix B — Swap Workflow Summary

| What you want to change | How to do it | Recompile needed? |
|------------------------|-------------|-------------------|
| Swap one NPC from cube to MetaHuman | Add row in `DA_NpcAppearance` or one line in `NpcAppearance.cpp` | C++ line: yes. DataAsset: no |
| Change a fallback line | Edit `DA_NpcFallbackLines` entry | No |
| Change a memory badge text | Edit `DA_MemoryBadgeLookup` entry | No |
| Change an arrival subtitle | Edit `DA_LocationSubtitles` entry | No |
| Change a morph target name | Edit `DA_FacialExpressionMap` (once created) | No |
| Change widget visual art | Redesign `WBP_*` layout | No (layout only) |
| Change widget logic | Edit C++ base class | Yes |
