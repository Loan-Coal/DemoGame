# Asset Acquisition Playbook

> **Status:** v1.0 · 2026-06-25
> **Purpose:** A self-contained brief a fresh Claude session can execute to *research, shortlist,
> and (where possible) download* the free art/audio assets for DemoGame.
> **Companion files:** `game_design_roadmap.md` §11 (Asset Plan), `HUMAN_VERIFICATION.md` (manual editor/browser steps).

---

## 0. How to use this file (read first)

This playbook is the **asset analog** of the roadmap's phases. A Claude session picks **one
category task** from §6 and runs it end to end. It is NOT a single mega-task — do one category
per run so each stays focused and verifiable.

**What a Claude session CAN do here (headless):**
- Live web research: find candidate assets, read specs, license, UE-version support, reviews.
- Produce a **shortlist of 2–4 options per asset, with reasoning** (the core deliverable).
- **Generate** (never auto-run) a *scoped* `curl`/`wget` script for the CC0 direct-download tier
  (Poly Haven, AmbientCG, Kenney, Freesound-with-key), targeting only **human-approved** shortlist items.
  No bulk/bundle/multi-GB downloads — cherry-pick individual files.
- Write a **license manifest** and **per-asset import instructions**.

**What a Claude session CANNOT do (must go to the human / HUMAN_VERIFICATION.md):**
- Judge how an asset *looks rendered*. **"Best looking" is always a human gate.** The session
  ranks on measurable criteria + descriptions only.
- Download anything **account-gated or editor-gated**: MetaHuman Creator (browser GUI),
  Fab / Megascans ("Add to Project" inside the editor), Mixamo (Adobe login + per-clip export).
  These become **manual steps appended to `HUMAN_VERIFICATION.md`**, written verbatim with exact clicks.

> If a session is ever tempted to claim it "downloaded the tavern kit," stop — it can't. It either
> *wrote a scoped script* for a CC0 direct download, or it wrote you instructions. Be honest about which.

**The hard gate (quality over speed):** research → shortlist → **human approves the shortlist** → only then
is any fetch script run, by the human. No download happens before a human has chosen from the options, and no
multi-GB bundles are ever pulled. This is deliberate: the user prefers slower, hand-picked, higher-quality selection.

---

## 1. Locked project context (do not re-litigate)

These decisions are settled. A session must respect them, not re-open them.

| Decision | Value |
|----------|-------|
| Engine | Unreal Engine 5.8, C++ |
| Art direction | **Photorealistic medieval throughout.** No stylized/low-poly mixing in the same scene. |
| Character pipeline | **All-MetaHuman cast** (all 5 NPCs), LOD-disciplined. No mixed-fidelity Fab humanoids. |
| Hardware budget | RTX 5070 Ti. Target ≤10 GB VRAM per scene. ≤1–2 MetaHumans co-loaded (market scene has 2). |
| License policy | **This demo is non-commercial → NC assets ALLOWED, but every NC/CC-BY asset MUST be tagged in the manifest with `swap_for_commercial: yes`.** CC0 / Epic-ecosystem preferred (no swap needed). |
| Cohesion principle | One master post-process grade + unified lighting. **Re-skin Fab-kit geometry with Megascans/AmbientCG materials** so all surfaces share one vocabulary. |
| Lighting | Indoors: **Lumen GI + reflections** (per DEC-030 — bounced warm hearth GI is the tavern's whole look; bake only if Phase 7 VRAM forces it) + stationary hero candle/hearth lights. Outdoors: HDRI sky (Poly Haven) + one directional sun **aligned to the HDRI's baked sun direction** (mismatch = double-shadows) at a **low, warm late-afternoon angle (~15–25°)**, NOT noon/overcast. Add Sky Atmosphere + Exponential Height + Volumetric Fog + light shafts. Enable DLSS/TSR to fund Lumen on the 5070 Ti. |
| Portrait lighting | **This is a dialogue game — faces in close-up are the product.** Each NPC needs a per-NPC dialogue key/eye light giving catchlights + readable subsurface skin, plus shallow DoF on the dialogue cam (cinematic + hides background greybox). Scene lighting alone leaves MetaHumans flat-and-dead in close-up. See roadmap §9 + Phase 7. |

### The cast (all MetaHuman)
| NPC | Note for asset work |
|-----|---------------------|
| Mira (innkeeper) | Most dialogue → most expression tuning. Build first. |
| Captain Sorn | Stoic, older soldier. |
| Lira (fence) | Back-room, dim. |
| Aldric (merchant) | Middle-aged wine merchant. |
| Old Henryk | **Elderly** preset. End of the gossip chain. |

### The scenes (3 levels)
| Level | Type | Lighting approach |
|-------|------|-------------------|
| `L_Tavern` (+ `L_TavernBack` sublevel) | Interior, moody | Lumen / baked GI + hero hearth & candles |
| `L_MarketSquare` | Exterior courtyard | HDRI sky + directional sun |
| `L_GuardBarracks` | Exterior courtyard | HDRI sky + directional sun (share stone with market) |

---

## 2. Selection criteria — what "best" means (the rubric)

A session ranks candidates on these measurable axes (it cannot use "looks good" — that's the human gate):

1. **License** — CC0 / Epic-ecosystem (best) > CC-BY (needs attribution) > NC (allowed, must tag swap). Reject unknown/unclear licenses.
2. **UE5 compatibility** — native UE5 asset / UASSET or clean FBX+textures. UE5.8 or "UE5.x" support stated. Avoid UE4-only without migration notes.
3. **Photoreal match** — PBR materials, scanned or high-detail. Reject obviously stylized/hand-painted for in-scene assets.
4. **Texel density / resolution** — 2K+ textures for hero surfaces; note if only 1K.
5. **Modularity** (geometry) — modular kit pieces > a single baked scene. Lets the human rebuild the 3 specific levels.
6. **Poly / VRAM sanity** — note tri counts and texture memory; flag anything that threatens the 10 GB scene budget.
7. **Completeness** — does it cover the need alone, or need supplementing (e.g. kit needs re-skinning)?

**Scoring scale (use verbatim so runs are comparable):** score each of the 7 axes **0 / 1 / 2**
(0 = fails/unknown, 1 = acceptable, 2 = strong). License is a **gate, not just a score**: an unknown or
unverifiable license caps the candidate's total at 0 regardless of other axes (reject it). Max raw score
= 14. Report each candidate as `total/14 (per-axis: L# U# P# T# M# V# C#)` plus the 1-line rationale.
A candidate with any **0 on License, UE5 compatibility, or Photoreal match** cannot be the recommended pick.

Output the per-axis vector + total + a 1-line rationale per candidate. Surface trade-offs, don't hide them.

---

## 3. Deliverables per run (what a session must produce)

For the category it ran, a session produces **all** of:

1. **Shortlist** — appended to `project-harness/asset-shortlists/<category>.md`: 2–4 options per asset, each with
   source URL, license, rubric score, pros/cons, and **two recommended picks per asset — a 🆓 top free/CC0 pick
   AND a ⭐ top overall pick** (each caveated "human confirms the look"). If the two coincide (the best option is
   also free), say so explicitly. If **no** free/CC0 option exists for that asset, the free line must say so and
   name the **cheapest paid floor** instead — never silently omit the free pick.
2. **Scoped fetch script** (CC0 tier only, **NOT auto-run**) — `project-harness/asset-scripts/fetch_<category>.sh|.ps1`
   using `curl`/`wget`, listing only the **specific human-approved** shortlist items (no bundles, no GB-scale pulls),
   writing into a staging folder (NOT directly into `Content/` — staging keeps unreviewed assets out of the project).
   Staging path: `c:\Users\lohan\Documents\hackathons\DemoGame\AssetStaging\<category>\`. The human runs this
   after approving the shortlist.
3. **Manual import steps** — appended to `HUMAN_VERIFICATION.md` under an `## Asset import — <category>` heading,
   verbatim and click-exact, for anything account/editor-gated.
4. **License manifest rows** — appended to `project-harness/ASSET_MANIFEST.md` (format in §5).

### Definition of done (a run is acceptable only if ALL hold)
- **Every cited URL was actually fetched this run and its license + UE-version text quoted from the page** —
  never recalled from memory. An unfetchable URL is dropped, not guessed. (This is the #1 failure mode: a
  shortlist of plausible-but-dead links and wrong licenses. No verification → the run is rejected.)
- **≥ 2 options per asset** (target 2–4), each scored on the §2 0/14 scale with the per-axis vector.
- Each option records: source URL (fetched), exact license string (quoted), UE5.x support (quoted/stated),
  texture resolution / tri-count where applicable, pros, cons.
- **Two picks per asset** — a 🆓 top free/CC0 pick AND a ⭐ top overall pick — each with a one-line reason,
  caveated "human confirms the look." If no free/CC0 option exists, the free line says so and names the cheapest
  paid floor.
- All four §3 deliverables produced for the category. NC/CC-BY rows tagged `swap_for_commercial: YES`.
- Explicit statement of what was *scripted* (left for the human to run) vs *only instructed*.

A session must NOT:
- **Run** a fetch script, or download any bundle / multi-GB pull. Scripts are *generated* and left for the human
  to run on approved items only.
- **Cite a URL, license, or spec it did not fetch and read this run.** No memory-sourced links.
- Drop unreviewed binaries straight into `Content/` (use staging).
- Claim a manual-tier asset was acquired (it can only instruct).
- Pick a single option when the user asked for **multiple** — always shortlist.
- Collapse the two picks into one. **Every asset ends with both a 🆓 top free pick and a ⭐ top overall pick** (or
  an explicit "no free option exists — cheapest paid floor is X"). A lone recommendation is an incomplete run.

---

## 4. The capability tiers (which sources auto vs manual)

| Source | Tier | How | License |
|--------|------|-----|---------|
| **Poly Haven** (HDRIs, textures, props) | 🟢 SCRIPTED | script targets specific approved file URLs via `curl` | CC0 |
| **AmbientCG** (PBR materials, HDRIs) | 🟢 SCRIPTED | script targets specific approved download URLs | CC0 |
| **Kenney.nl** (UI sounds, UI bits) | 🟢 SCRIPTED | script targets specific approved zip URLs | CC0 |
| **Sonniss GDC Bundle** (SFX/ambience) | ⚪ AVOID | multi-GB bundle — too large; cherry-pick Freesound/Kenney instead | Royalty-free |
| **Freesound** (one-off SFX) | 🟢 SCRIPTED* | API, individual clips (needs free API key in env `FREESOUND_API_KEY`) | CC0 / CC-BY (tag BY) |
| **MetaHuman** (the 5 faces) | 🔴 MANUAL | UE5.8 in-editor **MetaHuman plugin** and/or MetaHuman Creator → add to project. **Verify the exact 5.8 flow first (see currency note).** | Epic-ecosystem |
| **Fab** (env kits, MetaHuman clothing) | 🔴 MANUAL | Epic login + in-editor Fab plugin "Add to Project" | per-asset (filter Free/NC) |
| **Megascans** (surfaces, props) | 🔴 MANUAL | **now distributed via Fab** (free for UE); legacy Quixel Bridge is being sunset | Free for UE |
| **Mixamo** (animations) | 🔴 MANUAL | Adobe login → FBX "Without Skin" → retarget | Free, commercial-OK |
| **AI generation** (UI 2D art) | 🟡 HUMAN-RUN | local SDXL / Midjourney, human prompts | tool-dependent |

\* If `FREESOUND_API_KEY` is absent, downgrade Freesound to MANUAL and note it.

> **Pipeline-currency rule (do this first on any manual task):** the tool names above may be stale.
> The Epic ecosystem moved Megascans into **Fab** and is sunsetting Quixel Bridge; **MetaHuman** is now an
> **in-editor plugin** in UE5.6+ (not only a web creator). Before writing any HUMAN_VERIFICATION steps,
> **fetch and confirm the current UE5.8 flow** (Epic/Fab/MetaHuman docs) and write steps against what you
> verified today — do not transcribe this table's tool names on faith.

### Download size / resolution ceilings (scripted tiers — hard caps)
No multi-GB pulls (⚪). For scripted fetch scripts, cap resolution so disk and VRAM stay sane:
- **HDRIs (Poly Haven):** **4K** for hero sky, 2K acceptable for distant backdrop. Never 8K/16K. Prefer `.hdr`/`.exr`.
- **PBR materials (AmbientCG):** **2K** default; **4K only for a named hero surface**. Note format (JPG vs PNG).
- **Per-file sanity:** flag any single file > ~200 MB; the script must list each file's expected size.

All 🟢 SCRIPTED downloads are **human-gated**: the session writes the script targeting only approved shortlist
items; the human runs it. No bulk bundles, ever (⚪ AVOID).

---

## 5. License manifest format (`ASSET_MANIFEST.md`)

Append one row per acquired/selected asset. This is what makes the future commercial swap tractable.

```
| asset | category | source | url | license | tier | swap_for_commercial | local_path | notes |
|-------|----------|--------|-----|---------|------|---------------------|------------|-------|
| Oak plank material | env-material | AmbientCG | <url> | CC0 | auto | no | AssetStaging/env/... | 2K |
| Tavern interior kit | env-geometry | Fab | <url> | NC-free | manual | YES | (in-editor) | re-skin w/ Megascans |
```

Rule: **anything not CC0 and not Epic-ecosystem → `swap_for_commercial: YES`.**

---

## 6. Category tasks (run ONE per session)

Each task is independently runnable. Suggested execution order matches the roadmap's long-pole logic.

### Task A — MetaHuman cast (faces + rig) 🔴 MANUAL
- **Need:** 5 MetaHumans matching the cast in §1. Henryk from an elderly preset.
- **Session does:** write exact MetaHuman Creator steps into `HUMAN_VERIFICATION.md` (preset choice per character,
  age/feature tweaks, Quality = **Medium** for VRAM, Bridge "Add" to project, expected Blueprint output). Research any
  current UE5.8 MetaHuman import gotchas and note them.
- **Human gate:** the actual creation + import (browser + editor).

### Task B — MetaHuman medieval clothing 🔴 MANUAL — **DO THIS BEFORE committing to faces** (the go/no-go gate)
- **Need:** medieval garb that is **MetaHuman-rigged / MetaHuman-compatible**, one outfit per cast member
  (all 5 are MetaHuman per DEC-031):
  - **Mira** — innkeeper/tavern-keeper: apron over a simple kirtle/peasant dress, warm, working-class.
  - **Captain Sorn** — soldier/guard: gambeson, light leather-or-mail, a guard tabard. Stoic, older.
  - **Lira** — fence: hooded cloak / dark layered commoner garb for the dim back room.
  - **Aldric** — wine merchant: a respectable middle-class doublet/tunic, slightly finer cloth.
  - **Old Henryk** — elderly commoner: worn robe/tunic, the end-of-chain old man.
- **Session does:** shortlist (per §2 0/14 scale, per §3 definition-of-done) **2–4 options per outfit, ending
  each outfit with a 🆓 top free pick AND a ⭐ top overall pick** (or "no free option exists — cheapest paid
  floor is X"), from: (a) **Fab** (filter Free + NC; weight MetaHuman-rig/skeleton compatibility heavily),
  (b) MetaHuman-native clothing where it exists, (c) alternative routes (Marvelous Designer garments + how they
  bind to the MetaHuman body, CC0 garment scans). **Fetch and quote** each license + the rig/skeleton-compatibility
  claim from the asset page — do not assume "Fab humanoid = MetaHuman-rigged" (most are UE-Mannequin-rigged and need
  retarget/skin-wrap; call that out per option). Note per option: does it ship as a MetaHuman-groomable mesh,
  a skeletal mesh needing retarget, or a static garment needing Mesh-to-MetaHuman / cloth-binding?
- **This is the whole photoreal cast's go/no-go gate.** End the run with an explicit **GO / NO-GO / CONDITIONAL**
  verdict: can all 5 outfits plausibly be MetaHuman-rigged from free/NC sources? If the answer is "only with
  heavy manual retarget per outfit," say so loudly — that is a schedule/feasibility risk for the art plan.
- **Human gate:** import + skin test on ONE MetaHuman (recommend Mira first). If it fails, the photoreal-character
  plan is at risk — escalate before any faces are built.

### Task C — Animations (idle / talk / thinking) 🔴 MANUAL
- **Need:** idle, talking-gesture idle, subtle "thinking" idle (LLM-wait loop, see roadmap §9 Dialogue UX).
- **Session does:** identify exact Mixamo clips + write retarget-to-MetaHuman steps (FBX "Without Skin" → IK Retargeter).
- **Human gate:** Mixamo login + export + retarget.

### Task D — Environment geometry (the shapes) 🔴 MANUAL (research is headless)
- **Need:** modular kits for tavern interior, market stalls, barracks courtyard.
- **Session does:** shortlist 2–4 **modular**, UE5, photoreal kits per scene (Fab Free/NC). Rank on §2 rubric, esp.
  modularity. Note that bundled materials will be **overridden** (Task E), so weight geometry over their textures.
- **Human gate:** Fab "Add to Project" in-editor.

### Task E — Surfaces & props (the premium paint) 🟢 SCRIPTED (AmbientCG) + 🔴 MANUAL (Megascans)
- **Need:** oak, plaster, stone wall, cobblestone, fabric materials; barrels/crates/sacks props.
- **Session does:** shortlist AmbientCG CC0 materials + generate a **scoped fetch script** for the approved picks
  (human runs it); shortlist Megascans equivalents with in-editor download steps. Produce the **per-scene material
  list** (which surface goes where).
- **Human gate:** Megascans download + applying materials over the Task D kits in-editor.

### Task F — Lighting (HDRIs) 🟢 SCRIPTED (Poly Haven)
- **Need:** outdoor HDRIs for market + barracks. **Market: low warm late-afternoon / golden-hour** (matches
  the "Afternoon at the market square" cue + gives long raking shadows). **Barracks: cooler/later or thin
  overcast** so it reads as a different place. Avoid flat high-noon. Optional interior reference HDRIs.
- **Session does:** shortlist 2–4 Poly Haven HDRI options per outdoor scene (note each HDRI's **sun
  altitude/azimuth** — the directional light must be aligned to it or character shadows fight the sky) +
  generate a **scoped fetch script** for the approved picks (human runs it) + import-as-HDRI-Backdrop steps.
  Note that indoors uses Lumen per DEC-030 (no baked-HDRI lighting needed there).
- **Human gate:** placing HDRI Backdrop / Sky Light + directional sun (aligned to HDRI sun) in-editor.

### Task F2 — Portrait / dialogue-cam lighting 🔴 MANUAL (research is headless)
- **Need:** per-NPC dialogue key/eye light so MetaHuman faces read as photoreal **in the close-up that
  dominates this game** — catchlights in the eyes, subsurface skin, a rim to separate from background.
  Plus a shallow depth-of-field setup on the dialogue camera (cinematic + hides background greybox).
- **Session does:** write the in-editor recipe — a small portrait light parented to each `DialogueCamSocket`
  (or a light rig that follows the dialogue cam), target intensities/temperatures per NPC mood, and the
  post-process DoF settings (focal distance on the face, aperture for background fall-off). Cross-reference
  roadmap §9 (camera) + Phase 7 (the new portrait-lighting checklist item).
- **Human gate:** placing/tuning the portrait light + DoF per NPC in-editor under the master grade.

### Task G — Audio (ambience + SFX + UI sounds) 🟢 SCRIPTED
- **Need:** tavern (hearth, murmur, creak), market (bustle, wind, cart), barracks (drills, clank, wind); UI sounds
  (quest accept, journal rustle, trust ping, faction confirm) per roadmap §9.
- **Session does:** shortlist **individual clips** from Freesound(key) / Kenney (CC0 / single files — **NOT** the
  multi-GB Sonniss bundle) + generate a **scoped fetch script** for the approved picks (human runs it) + a mapping of
  clip → scene/event + MetaSound/SoundCue wiring notes.
- **Human gate:** import WAVs + wrap in MetaSounds in-editor.

### Task H — UI 2D art 🟡 HUMAN-RUN (generated)
- **Need:** parchment dialogue panel, rumor-journal cards, distortion badges (green/yellow/red), quest-log paper.
- **Session does:** write precise generation prompts (SDXL/Midjourney) per UI element + the UMG import/slice notes.
  Do NOT attempt to source these — generation beats sourcing for 2D.
- **Human gate:** run the prompts, export PNGs, import to UMG.

---

## 7. The human QA gate (non-negotiable)

No asset is "accepted" until the human has **looked at it in-editor under the master post-process grade**. The session's
shortlist and manifest are *candidates*. Acceptance = a human eyeball + a `- [x]` in `HUMAN_VERIFICATION.md`. A session
never marks an asset visually approved.

---

## 8. Pre-flight checklist for a session running a category task

- [ ] Read §1 (locked context) and §2 (rubric) before researching.
- [ ] Confirm the category's tier in §4 (auto vs manual) — don't try to script a manual source.
- [ ] Produce all four deliverables in §3 (shortlist, script if auto, HUMAN_VERIFICATION steps if manual, manifest rows).
- [ ] Always give **multiple options** with reasoning, never a lone pick.
- [ ] Tag every NC / CC-BY asset `swap_for_commercial: YES`.
- [ ] **Never run** a fetch script or pull a multi-GB bundle — *generate* the scoped script; the human approves the
      shortlist and runs it.
- [ ] Stage downloads in `AssetStaging/<category>/`, never straight into `Content/`.
- [ ] Be explicit about what was *scripted* (left for the human to run) vs *only instructed*.

---

*Playbook v1.0 · 2026-06-25 · Companion to game_design_roadmap.md §11*
