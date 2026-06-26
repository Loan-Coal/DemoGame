# Roadmap

Slice-based delivery. Check a box only when its work is merged and `Scripts/check.ps1` is green.

**Headless-first policy:** Every phase is split into a headless C++ block (the loop implements) and
a thin human tail (MetaHuman/material/level art and live-LLM playtests). The loop advances to the
next C++ block without stopping for human tails.

**Phases 0–11 complete** — archived with full C++ checklist history in
[`archive/ROADMAP_DONE.md`](archive/ROADMAP_DONE.md).

**All editor work** (levels, MetaHumans, widgets, audio, environment) lives in one place:
→ [`UNREAL_EDITOR_PLAYBOOK.md`](UNREAL_EDITOR_PLAYBOOK.md)

**Live-LLM gates and playtest** (trust-gate runs, gossip 5/5, naive user playtest, acceptance
checklist) live in:
→ [`HUMAN_VERIFICATION.md`](HUMAN_VERIFICATION.md)

---

## Bring-up — complete ✅

- [x] Build green (DemoGame + NpcEngineClient); `Scripts/check.ps1` PASS *(2026-06-23)*
- [x] `Config/NpcEngine.ini` from template; gitignored *(2026-06-23)*
- [x] Docker engine verified end-to-end via `NpcEngine.Smoke` *(2026-06-23)*
- [x] `NpcEngine.SeedWorld` + client specs green *(2026-06-23)*

---

## Phase 12 — Appearance Pipeline Hardening + Cleanup Sweep

**Goal:** Cube→MetaHuman swap fast, artist-friendly, and headless-friendly. Clears ISSUE-016/017/018/019/020.
**Independently demoable:** Stock UE5 mannequin registers as stand-in avatar and loads **asynchronously**
with no frame hitch — cube shows first, replaced by mannequin when load completes. Both swap paths
(DA_NpcAppearance row, C++ default-map line) verified to change the rendered avatar.
**Prerequisites:** Phase 7 C++ block (done). **Block A must merge before the Phase 7 editor session
first MetaHuman import** — it is the load path those assets will use.
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`
**Decisions:** DEC-042 (hybrid appearance registry), DEC-043 (retire legacy seeder).

### Block A — Appearance pipeline

- [x] `UNpcAppearanceData` DataAsset (`DA_NpcAppearance`, DemoGame module): `TMap<FName, TSoftClassPtr<AActor>> AvatarByNpcId`
- [x] Hybrid resolver (DEC-042): DA_NpcAppearance → C++ default map → empty/cube. Failing Automation Spec first.
- [x] `UPROPERTY` on `FNpcSpawnRecord` and `FGreyboxLocation` (ISSUE-018)
- [x] Async avatar load in `ANpcGreyboxActor` (ISSUE-017): `RequestAsyncLoad` replaces `LoadSynchronous`; cube → avatar progressive reveal; weak self-ptr guard; streamable handle released in `EndPlay`
  - [ ] Functional Automation test: avatar spawns + cube hides after async load; destroyed-before-load doesn't crash `[HUMAN TAIL — requires PIE world context]`
- [x] Mannequin as default humanoid (DEC-042): `SKM_Manny` / ThirdPerson BP registered in C++ default map for all 5 NPCs; name label visible above mannequin
- [x] Doc + comment fixes in `DialogueWidgetBase.h` and `NpcAppearance.h/.cpp`

### Block B — Hygiene + dead-code sweep

- [x] ISSUE-016: `NpcAppearance.spec.cpp` wrapped in `#if WITH_DEV_AUTOMATION_TESTS`; `check_rules.py` rule added
- [x] ISSUE-019: `DialogueWidgetBase::OnMemoriesRecalled` — replace raw-id terminal fallback with log Verbose + Collapsed visibility; never render raw memory key to player
- [x] ISSUE-020 (DEC-043): delete `NpcEngineSeedClient.cpp/.h` + `Seed/slice1_tavern.json`; confirm zero callers; build green

### Done when

- [x] `pwsh Scripts/check.ps1 -WithBuild -WithTests` green; new specs pass; no new warnings _(check_rules PASS; build + full test run require editor — human tail)_
- [ ] PIE: mannequin loads async (cube-first → avatar); both swap paths verified `[HUMAN TAIL]`
- [x] ISSUES 016/017/018/019/020 moved to `archive/ISSUES_RESOLVED.md` with `**Fixed:**` stamps
- [x] Block A merged before any real MetaHuman is imported

---

## Acceptance Criteria — Demo v1

> All items must pass before the demo is complete. No partial credit.
> For how to run each check, see [`UNREAL_EDITOR_PLAYBOOK.md §6`](UNREAL_EDITOR_PLAYBOOK.md) and [`HUMAN_VERIFICATION.md`](HUMAN_VERIFICATION.md).

### Setup
- [ ] Engine health check returns 200. Seeder runs to completion with 0 errors.
- [ ] `NpcEngine.Smoke` returns a non-empty `npc_response` in Output Log.

### World + Navigation
- [ ] Player navigates between all three named locations. Tick fires and arrival subtitle appears on each.
- [ ] Tavern back room does not fire a tick. Sub-level streams in without a visible hitch.
- [ ] Re-entering the same location does not fire a tick.

### Dialogue + Trust
- [ ] Player initiates dialogue with Mira. Types a message. Receives a response within 30 seconds or a graceful fallback line.
- [ ] Trust meter updates visibly after each exchange.
- [ ] The `memories_recalled` badge appears at least once during the golden path.
- [ ] MetaHuman expressions animate during dialogue in response to the `facial_expression` payload.
- [ ] Thinking animation plays during LLM wait. Input is locked during wait.

### Investigation + Trust Gates
- [ ] Gate 1 (Mira trust > 25): Mira reveals information about Aldric's situation. Gate clears in dialogue — no waypoint marker.
- [ ] Player identifies Aldric through 2+ NPC conversations. No map marker. Observer confirms social discovery.

### Quest System
- [ ] Quest log shows `find_wine_merchant` as the first active step.
- [ ] Chain A completes: quest log shows `deliver_amulet` complete; `aldric_confession` step appears.
- [ ] Faction fork fires. Faction standing changes (logged or visible in debug HUD).
- [ ] Lira's back room is inaccessible below gate 2 and accessible above it.

### Gossip Chain + Journal
- [ ] After the golden path, Old Henryk's dialogue contains the distorted war account.
- [ ] A naive observer who heard Sorn's account can identify Henryk's as a distortion of it.
- [ ] Rumor Journal (Tab) shows the Sorn → Mira → Henryk chain with distortion level labels at each hop.
- [ ] Sorn trust gate unlocks `patrol_duty`. Quest appears in the quest log.

### Stability
- [ ] No crashes across the full golden path.
- [ ] LLM timeout produces a fallback line — no hang, no freeze, no error popup.
- [ ] `DegradationLevel != "full"` is logged silently; does not break the game.

### Playtest Gate
- [ ] A naive player (who has not seen the demo) reaches beat 15 (the gossip reveal) within 25 minutes without being guided.
