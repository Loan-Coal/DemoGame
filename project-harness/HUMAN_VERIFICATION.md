# Human Verification

**What this file is:** End-result acceptance gates that require a live Docker engine, a live PIE
session, or a live human player. These cannot be automated headlessly.

**What this file is NOT:** Step-by-step editor instructions. All editor how-to is in
[`UNREAL_EDITOR_PLAYBOOK.md`](UNREAL_EDITOR_PLAYBOOK.md). Look there for exact clicks.

**How to use this file:** Work top-to-bottom. Docker engine must be running on `localhost:8000`.
Run `NpcEngine.SeedWorld` (console exec, in-editor) before each live-LLM gate.
Tick boxes as you go.

---

## Gate 0 — Greybox World Smoke (Phase 2)

**Prerequisite:** Phase 12 Block A merged and build green. Press Play in the default map.
Engine does NOT need to be running for this gate.

- [ ] Output Log: `GreyboxWorldSubsystem: built at base=...` and `NpcSpawnerSubsystem: spawned 5 NPCs`
- [ ] Five cube NPCs visible in level (Mira, Lira, Aldric, Captain Sorn, Old Henryk)
- [ ] Walk +X from PlayerStart: `Tick=1 Location=loc_tavern` logged on tavern trigger entry (~5 m)
- [ ] Continue +X past 15 m: `Tick=2 Location=loc_market_square` logged
- [ ] Continue +X past 30 m: `Tick=3 Location=loc_guard_barracks` logged
- [ ] Walk back to tavern: no double-tick (re-entry guard working)
- [ ] Back-room position (~10 m in -Y from PlayerStart): no tick (`bFiresTick=false`)
- [ ] Press E near any NPC: dialogue widget opens

---

## Gate 1 — Trust Gate + Live Dialogue (Phase 4)

**Prerequisite:** Docker engine running + `NpcEngine.SeedWorld` run to completion (0 errors in Output Log).

- [ ] Approach Mira → press E → `WBP_Dialogue` opens; type a message → response arrives within 30 s
- [ ] Input field locks during LLM wait; unlocks on response
- [ ] `WBP_RelationshipMeter` Trust value climbs after each exchange
- [ ] Trust passes **25** and Mira's dialogue reveals information about Aldric (no waypoint)
- [ ] `memories_recalled` badge appears at least once
- [ ] **Repeat 3× from a fresh seed** (re-run `NpcEngine.SeedWorld` to reset). Gate must clear all 3 runs.

For how to set up the live Docker engine: see [§0 of UNREAL_EDITOR_PLAYBOOK.md](UNREAL_EDITOR_PLAYBOOK.md).

---

## Gate 2 — Quest Lifecycle + Streaming Gate (Phase 5)

**Prerequisite:** Docker engine running + fresh seed. All 5 NPC actors placed (cubes or MetaHumans).

**Quest lifecycle endpoint shape verification:**
- [ ] Run `GET http://localhost:8000/openapi.json` and confirm the 6 quest endpoint shapes from DEC-027 match the live engine. If any field name differs, update `NpcQuestTypes.h` + matching serializer in `NpcEngineJsonUtils.cpp`. Record result in DECISIONS.md.

**Chain A end-to-end:**
- [ ] Fresh save → speak with Mira (trust gate 1 at 25) → identify Aldric through 2+ NPC conversations → quest log shows `find_wine_merchant` active
- [ ] `deliver_amulet` quest step appears after Aldric interaction; completes in quest log
- [ ] `aldric_confession` step appears
- [ ] Faction fork (`WBP_FactionFork`) fires; faction standing change logged to Output Log

**Streaming gate:**
- [ ] Build trust with Mira past 40 in PIE → Output Log: `TavernBack gate fired` → Lira's back room becomes accessible
- [ ] Below threshold: back room inaccessible. Above: accessible.

---

## Gate 3 — Gossip Chain 5/5 (Phase 6 — BLOCKING GATE)

**Do not mark Phase 6 complete until 5/5 pass. Do not start the Phase 7/11 editor sessions until this passes.**

**Prerequisite:** Docker engine running + fresh seed. Full golden path setup complete.

**Run the golden path 5 times from a fresh seed each time:**
Tavern (speak with Mira, ≥2 exchanges) → Barracks (build trust with Sorn until he shares war info) → Tavern (tick fires) → Market (speak with Old Henryk)

- [ ] Run 1: Henryk's dialogue contains the distorted war account
- [ ] Run 2: Henryk's dialogue contains the distorted war account
- [ ] Run 3: Henryk's dialogue contains the distorted war account
- [ ] Run 4: Henryk's dialogue contains the distorted war account
- [ ] Run 5: Henryk's dialogue contains the distorted war account

**If any run fails:** tune `gossipy` and `credulity` personality values in `Seed/DemoWorld_v1.json` and re-run `NpcEngine.SeedWorld`. Re-run the failing path before incrementing the count.

**Greybox acceptance gate (also Phase 6 blocking):**
- [ ] All 17 narrative beats from `docs/game_design_roadmap.md §10` are playable start-to-finish
- [ ] All trust gates, quest steps, gossip chain, Rumor Journal, and faction fork are functional
- [ ] Any non-functional beat is a blocker; do not advance to Phase 7/11 editor sessions until all pass

---

## Gate 4 — MetaHuman VRAM + Expression (Phase 7 editor session)

**Prerequisite:** Phase 12 Block A merged. MetaHuman import done per [UNREAL_EDITOR_PLAYBOOK.md §1](UNREAL_EDITOR_PLAYBOOK.md).

- [ ] `stat gpu` in `L_Tavern` (Mira present): < 10 GB
- [ ] `stat gpu` in `L_GuardBarracks` (Sorn present): < 10 GB
- [ ] `stat gpu` in `L_MarketSquare` (Aldric + Henryk present): < 10 GB
- [ ] Mira and Lira confirmed **never** simultaneously in GPU memory (toggle sub-level visibility and check `stat gpu`)
- [ ] Approach Mira → press E → camera blends smoothly (0.3 s) toward `DialogueCamSocket`
- [ ] Dialogue response changes Mira's MetaHuman expression visibly
- [ ] Thinking animation plays during LLM wait
- [ ] Close dialogue → camera blends back to player (0.4 s)

---

## Gate 5 — Phase 10 Content + Final Playtest

**Prerequisite:** All editor work complete (playbook §0–§5). Docker engine running + fresh seed.

### 5a — Aldric memory seeding

Seed Aldric's belief and secret **after** `NpcEngine.SeedWorld` completes (the aldric_merchant node must exist):

```powershell
$h = @{ Authorization = "Bearer $env:NPC_ENGINE_API_KEY"; "Content-Type" = "application/json" }

Invoke-RestMethod -Method Post "http://localhost:8000/v1/admin/memories/aldric_merchant" `
  -Headers $h -Body (@{
    memory_type = "belief"; key = "amulet_origin"
    content = "This amulet — I took it as trade debt in Riverwheel from a soldier passing through. He needed coin quickly; I didn't ask why. That was weeks ago. Now I have guardsmen coming to my stall asking what I know. I understand it now: that man deserted his post. He fled the northern garrison before the skirmish was reported, and this is what he left behind. I'm holding his evidence. That's what they want."
  } | ConvertTo-Json)

Invoke-RestMethod -Method Post "http://localhost:8000/v1/admin/memories/aldric_merchant" `
  -Headers $h -Body (@{
    memory_type = "secret"; key = "amulet_truth"
    content = "The amulet is evidence of a desertion from the northern garrison. The soldier who owned it sold it to Aldric to fund his flight from the northern pass before the skirmish the guards are suppressing."
  } | ConvertTo-Json)
```

> ⚠️ Verify the exact endpoint path against `GET http://localhost:8000/openapi.json` — the admin
> memory endpoint is not in `docs/openapi.json`. If the path differs, update DECISIONS.md.

- [ ] Aldric belief seeded (`amulet_origin`)
- [ ] Aldric secret seeded (`amulet_truth`)
- [ ] Speak with Aldric after Mira trust gate 1 fires: the amulet context surfaces in his dialogue

### 5b — Final gossip chain 5/5

- [ ] 5 fresh-seed runs: Henryk's dialogue contains the distorted war account in all 5
- [ ] If any run fails: tune `gossipy`/`credulity` in `Seed/DemoWorld_v1.json` → re-seed → re-run

### 5c — Distortion review

- [ ] Play as a player who heard Sorn's account, then talk to Henryk
- [ ] A neutral observer can identify Henryk's account as a corruption of Sorn's
- [ ] If not recognizable: exaggerate the authored distortion text in `Seed/DemoWorld_v1.json` (Henryk's hop-2 entry under `northern_war_begins`) and re-run `NpcEngine.SeedWorld`

### 5d — DemoWorld_v1.json reconciliation

- [ ] `Invoke-RestMethod http://localhost:8000/openapi.json` → compare all node-type field names against `Seed/DemoWorld_v1.json` and `docs/ENGINE_CONTRACT.md`
- [ ] Any drift → patch the seed → re-run `NpcEngine.SeedWorld` → record in DECISIONS.md

### 5e — Naive user playtest

- [ ] One person who has not seen the demo plays without guidance
- [ ] Observer notes every moment of confusion ("what do I do next?" moments)
- [ ] Fix every blocker before marking complete
- [ ] Player reaches beat 15 (gossip reveal) within 25 minutes

### 5f — Full §14 acceptance checklist

Run every item in the Acceptance Criteria section of [`ROADMAP.md`](ROADMAP.md). All must pass.
For the editor setup steps (DockerUp, SeedWorld, levels, MetaHumans), see
[`UNREAL_EDITOR_PLAYBOOK.md §6`](UNREAL_EDITOR_PLAYBOOK.md).

- [ ] All acceptance criteria ticked. Demo complete.
