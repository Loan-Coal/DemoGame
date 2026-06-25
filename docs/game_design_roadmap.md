# DemoGame — Game Design Roadmap

> **Status:** v1.0 · 2026-06-23  
> **Repo:** `DemoGame/` (Unreal Engine 5.8, C++, Rider IDE)  
> **Engine backend:** NPC Engine (FastAPI + Neo4j + Ollama). Contract: `docs/ENGINE_CONTRACT.md`  
> **Design constraint:** Every mechanic either showcases a named engine feature or is cut.  
> **Note on endpoints:** `/clock/advance` and quest lifecycle endpoints exist per engine CLAUDE.md but are not in the curated `openapi.json`. Verify against `GET http://localhost:8000/openapi.json` before implementing.

---

## 1. Vision & Pillars

**Vision:** A short, complete, third-person social RPG where the game world has a working brain. NPCs remember you, gossip about you, distort what they know, and gate their knowledge behind real trust. The player doesn't fight enemies — they navigate a social graph.

| Pillar | What it means in play |
|--------|-----------------------|
| **The world thinks** | NPCs propagate information between each other across world ticks, distorting it as it travels. The player can observe, seed, and trace these information chains. |
| **Trust is the currency** | Relationships aren't cosmetic. They gate information, quest access, and trade prices. Earning trust with the right NPC at the right time moves the story forward. |
| **Discovery over direction** | Quest objectives are described, not waypointed. The player uses social investigation to identify recipients, locate NPCs, and learn what is actually happening. |

**What this V1 is NOT:** A combat game. An open world. A chatbot with a camera. A simulation where the player watches NPCs interact without agency.

---

## 2. Player Fantasy / Genre

**Genre:** Relationship-driven social RPG. Third-person, single-player, medieval setting.

**Primary fantasy:** The player is a **Quest-Runner who uses social intelligence as their primary tool.** They have a job (a delivery), but the job cannot be completed via the obvious path. To complete it, they must read the social graph: talk to the right people, earn trust, notice when information has been distorted, and trace information back to its source.

**Design rule — enforced on all quest chains:** At least one step per chain must require the player to discover something socially — identify a recipient, surface a contradiction, or cross a trust threshold. "Go to waypoint and press interact" is never a valid quest in its entirety.

---

## 3. Core Loop

```
TALK → LEARN (including distorted information) → ACT → OBSERVE CONSEQUENCE → REPEAT
```

**Moment-to-moment:** The player approaches an NPC, initiates free-text dialogue, and builds or loses trust through conversation. The NPC's knowledge — shaped by gossip, personality, and relationship — determines what they share. When the player acts (delivers an item, takes a quest, chooses a faction), the world clock advances on travel, and those actions propagate through the NPC graph as distorted rumors.

**Per-session shape:** Arrive at a location → investigate → complete an objective → travel (tick fires) → observe that your actions changed what other NPCs know → begin the next objective.

---

## 4. Signature Wow + Demo Reliability

**The wow:** The player does something in Location A. They travel to Location B. An NPC there already knows — but their version is wrong. The player recognizes their own action in the distorted account.

**Concrete demo instance:**
1. Player speaks with Captain Sorn about the northern war at the barracks
2. Player travels to the market square (tick 1 fires on barracks arrival, tick 2 on market arrival)
3. Old Henryk mentions the war — but his version is exaggerated and wrong
4. The Rumor Journal (Tab) shows the chain: Sorn → Mira → Henryk, with authored distortion text at each hop

**Why this is demo-reliable (not emergent):**

| Risk | Mitigation |
|------|------------|
| Gossip propagation is stochastic | Seed personality values tuned: Mira `gossipy ≥ 82`, Henryk `credulity ≥ 90`. 5-run verification in Phase 6 before art pass. |
| Player might not talk to Henryk | Quest design requires it: a quest step is "learn what the market knows." |
| Distortion text is LLM-variable | Authored distortion text per hop, stored in seed data. `knowledge_state` field from engine determines which authored text renders. LLM shapes delivery; content is fixed. |
| Player won't recognize the distortion | Henryk's version must be obviously wrong. Exaggerate it in the seed ("the whole army fled to the hills"). If playtest reveals it's not recognizable, increase the exaggeration. |

**Mandatory verification:** Before any art pass, run the gossip chain 5 times from a fresh seed. All 5 must show propagation. If any run fails, tune personality values and rerun. Do not advance to Phase 7 until 5/5 pass.

---

## 5. Engine-Feature Map

| Engine Feature | How it is surfaced to the player |
|----------------|----------------------------------|
| **Gossip + distortion** | Rumor Journal (Tab) shows the chain with source attribution. Henryk's dialogue visibly contradicts Sorn's. |
| **Persistent memory** (`memories_recalled`) | Returning to Mira after a prior exchange: she references what was said. Small badge in dialogue panel: *"She remembers: [authored text]."* |
| **Relationships** (`relation_deltas`) | Relationship meter HUD (per-NPC). Trust gates: Mira's information, Aldric's price, Sorn's quest unlock. Meter moves after each exchange; gate text appears when threshold clears. |
| **Emotion** (`facial_expression` payload) | MetaHuman morph targets driven by `type` + `intensity`. Mira looks nervous when the war comes up. Sorn's expression hardens when trust is low. |
| **Quest chains** | Completing chain A + Sorn trust gate → `patrol_duty` appears in the quest log. "New quest available" is the direct payoff for relationship investment. |
| **World clock** | Arrival subtitle ("Evening falls over the market...") on each tick-firing location arrival. Player learns that travel = time passing. |
| **Faction standing** | The amulet delivery fork (Aldric vs. Lira) changes faction standing. Visible consequence: which next-quest appears, and how NPCs greet the player on return. |
| **Economy** (`buy_item` / `sell_item`) | Aldric's delivery reward scales with trust. Lira's offer is a `sell_item` action. Economy is the readable score of how relationships paid off. |

---

## 6. Time / Tick Model

**Rule:** One world tick fires per location arrival. Unreal calls `/clock/advance` (delta = 1) each time the player enters a new named location.

| Location | Tick fires? | Rationale |
|----------|-------------|-----------|
| `loc_tavern` (main floor) | Yes | New location, meaningful time passage |
| `loc_tavern_back` (Lira's room) | **No** | Same building; sub-level of the tavern |
| `loc_market_square` | Yes | |
| `loc_guard_barracks` | Yes | |

**Tick legibility:** A brief subtitle appears on each tick-firing arrival, derived from the engine's epoch/time-of-day field. It fades after 3 seconds. This is the player's only signal that time passed.

**Re-entry guard:** Re-entering the same location does not fire a tick. `UNpcWorldSubsystem` tracks `CurrentLocationId` and skips the clock call if it matches.

**Fast travel:** Not in demo v1. All movement is on foot. Fast travel would require a tick-cost decision; defer post-demo.

**Player stalling:** Staying in one location freezes the world clock. Gossip does not propagate. This is acceptable — quest design ensures the player must travel to progress.

---

## 7. World & Seed Design

### 7.1 Locations

| Location ID | Name | Description | NPCs |
|-------------|------|-------------|------|
| `loc_tavern` | The Broken Flagon | Main tavern floor, hearth, bar, tables. Hub of rumor. | Mira |
| `loc_tavern_back` | Back Room | Dim storeroom behind the bar. Lira operates here. Access gated by Mira's second trust threshold. | Lira |
| `loc_market_square` | Market Square | Open cobblestone courtyard, merchant stalls, notice board. | Aldric, Old Henryk |
| `loc_guard_barracks` | Guard Barracks | Courtyard outside the barracks. Sorn's territory. | Captain Sorn |

**Town name:** Thornfield. Use in all authored text (notice boards, biographies, fallback lines).

### 7.1.1 Visual & lighting direction (per room)

> A room is not its object list. Each scene is authored against five levers: **hero light** (the one
> motivated source), **fill/contrast**, **color-temperature story**, **the focal point the dialogue
> camera frames**, and **atmosphere** (haze/dust/smoke — this sells photoreal more than geometry does).
> These descriptions are the art-direction contract for Phase 8; they override a bare object list.

| Room | Hero light | Contrast / fill | Color story | Focal point | Atmosphere & one memorable detail |
|------|-----------|-----------------|-------------|-------------|-----------------------------------|
| **Tavern** | Hearth — warm, flickering, the Rembrandt key on Mira behind the bar. | **Cool window/door shafts** cutting across the warm interior — the warm-key/cool-fill split *is* the tavern look. Don't light it monochrome-orange. | Amber 2700–3200K key vs. cool ~6500K daylight slot. | Mira behind the bar, framed by hearthlight. | Volumetric haze with dust motes in the window shafts; clutter density (tankards, candle stubs, hanging utensils) so it doesn't read empty/game-y. |
| **Back room** | **One motivated hard key** — a single lantern/candle near Lira. NOT a "dark post-process volume" (global darkening reads muddy and flat). | Deep falloff into near-black; chiaroscuro. This is the contrast room — the fence *in shadow*. | Single warm pool against cold dark. | Lira's hooded face half-lit at the booth. | Low haze catching the lantern cone; crates/barrels as silhouette mass, not detail. |
| **Market** | **Low, warm late-afternoon sun (~15–25° above horizon)** — long raking shadows across the cobbles. | Cool sky-fill from the SkyLight; god-rays through awnings. | Golden-hour warmth matching the "Afternoon at the market square" cue. | Aldric at his stall; the notice board as a secondary read. | Light shafts + faint dust; **life proxies** (produce, baskets, cloth, sacks) since background NPCs are not MetaHumans — empty stalls read as a parking lot. Varied/wet cobbles for reflective break-up. |
| **Barracks** | Directional sun, but **a different time/temperature than the market** (colder, later, or thin overcast) so the player feels they traveled. | Harder, flatter mil-discipline light; less god-ray softness. | Cooler, desaturated stone-and-steel palette. | Sorn at the gate arch / training area. | Banners, weapon racks, gravel-and-mud ground (vs. market cobbles). Shares the stone *material vocabulary* with the market, not the lighting. |

**Cohesion rule (revised):** "one master grade" means **one shared LUT / tonemapper base + per-level
post-process volumes** for local mood — not a single grade forced on every scene. A grade that flatters
the warm tavern will crush the cool barracks, and vice versa. Share the base; tune locally.

### 7.2 The Propagating Event

| Hop | NPC | Version | Distortion level |
|-----|-----|---------|-----------------|
| Source | Captain Sorn | "Border soldiers are deserting their posts. A skirmish at the northern pass has been suppressed from official reports." | 0 — Firsthand |
| Hop 1 | Mira | "There's fighting up north. Someone said half the garrison moved out last week." | 1 — Rumor |
| Hop 2 | Old Henryk | "I heard the whole northern army's fled to the hills. War's already started, they say." | 2 — Distorted |

**These texts are authored verbatim in the seed.** The engine's gossip system propagates the knowledge; the authored biography/belief fields supply the display text. The Rumor Journal renders the authored version matched to the `knowledge_state` at each hop.

### 7.3 Cast

| NPC ID | Name | Personality values | Role | War angle |
|--------|------|--------------------|------|-----------|
| `mira_innkeeper` | Mira | `gossipy: 82, credulity: 60, honesty: 55` | Social hub, gatekeeper | Nervous for business. Shares under trust. |
| `lira_fence` | Lira | `gossipy: 40, credulity: 30, honesty: 20` | Faction fork, guild contact | Sees the war as leverage. Wants the amulet. |
| `aldric_merchant` | Aldric | `gossipy: 50, credulity: 50, honesty: 70` | Delivery recipient, trade gate | Was in Riverwheel. The amulet connects him to the war's origin. Biography: *"Formerly traded textiles in Riverwheel before settling in Thornfield as a wine merchant."* Confession secret: received the amulet as trade debt from a deserting garrison soldier; is now holding physical evidence of the suppressed desertion. |
| `captain_sorn` | Captain Sorn | `gossipy: 25, credulity: 20, honesty: 85` | Truth-holder, quest chain gate | Knows the real situation. Won't share without trust. Direct personality. |
| `old_henryk` | Old Henryk | `gossipy: 90, credulity: 95, honesty: 40` | End of every rumor chain | Repeats everything, embellished. The distortion showcase. |

### 7.4 Factions

| Faction | Key NPC | Player benefit of high standing |
|---------|---------|--------------------------------|
| Guard | Captain Sorn | `patrol_duty` quest chain, access to accurate war information |
| Thieves' Guild | Lira | `missing_goods` quest chain, black-market prices, underworld rumors |

**Faction fork:** The amulet delivery destination determines the player's initial alignment. Deliver to Aldric (neutral / guard lean) or sell to Lira (guild lean). Both complete chain A; faction standing changes which chain B quest activates.

### 7.5 Relationship Gates

One gate type per location. Never more than one active gate at a time within a scene.

| Gate type | NPC | Trust threshold | What unlocks |
|-----------|-----|-----------------|--------------|
| Information | Mira | `trust > 25` | "Aldric's been spooked. Soldiers were asking about him." — gates quest step progression |
| Information | Mira | `trust > 40` | "There's someone in the back who deals in private business." — gates access to Lira |
| Trade price | Aldric | `trust > 30` | Delivery reward +30% |
| Quest chain | Sorn | `trust > 50` | `patrol_duty` activates in quest log |

### 7.6 Quest Chains (seeded)

**Chain A — The Amulet Delivery**
1. `find_wine_merchant` — identify Aldric through social investigation (2+ NPC conversations minimum)
2. `deliver_amulet` — deliver to Aldric (neutral/guard) OR sell to Lira (guild fork)
3. `aldric_confession` — Aldric reveals the amulet's connection to the war; hooks chain B  
   **Authored confession:** *"This amulet — I took it as trade debt in Riverwheel from a soldier passing through. He needed coin quickly; I didn't ask why. That was weeks ago. Now I have guardsmen coming to my stall asking what I know. I understand it now: that man deserted his post. He fled the northern garrison before the skirmish was reported, and this is what he left behind. I'm holding his evidence. That's what they want."*  
   Seed fields: `aldric_merchant.belief["amulet_origin"]` = above text. `aldric_merchant.secret["amulet_truth"]` = *"The amulet is evidence of a desertion from the northern garrison. The soldier who owned it sold it to Aldric to fund his flight from the northern pass before the skirmish the guards are suppressing."*

**Chain B — Sorn's Patrol** (unlocked: Sorn trust gate)
1. `patrol_duty` — escort a route and report back
2. `captain_report` — Sorn shares the unfiltered war news as the reward

**Chain C — Missing Goods** (unlocked: Lira faction standing)
1. `missing_goods` — locate a diverted guild shipment
2. `fence_confrontation` — confront the person responsible

---

## 8. Mechanics & Player Verbs

| Verb | Input | What it does | Engine call |
|------|-------|--------------|-------------|
| **Move** | WASD / left stick | Third-person movement (UE template) | None |
| **Run** | Shift / hold stick | Sprint (UE template) | None |
| **Interact with NPC** | E / face button near NPC | Opens dialogue panel | Begins dialogue session |
| **Interact with object** | E near notice board | Shows authored text panel (static) | None |
| **Dialogue input** | Text field, turn-based | Player types → NPC responds | `POST /v1/dialogue` |
| **Quest confirm** | Button prompt | Accept or decline quest offer | Quest lifecycle endpoint |
| **Faction choice** | Binary prompt | Choose delivery target at fork | `POST /v1/action` |
| **Journal** | Tab | Opens Rumor Journal + Relationship meters | Reads local cache |

**Explicitly excluded from demo v1:** jump, inventory management, eavesdrop verb, fast travel, combat, crafting. These are post-demo additions.

---

## 9. Dialogue UX Spec

### Input model
- **Turn-based.** Player types a message (1–1000 characters). Empty input is rejected client-side before any HTTP call. Enforce the cap in `NpcEngineClient` before calling HTTP — do not rely on the engine's 422.
- Player input is **locked** while awaiting the engine response. The text field is disabled; a lock icon or subtle overlay makes this visible.
- On submit: camera cuts to NPC close-up. Thinking state begins.

### Thinking state (LLM wait)
- NPC plays a looping thinking ambient animation (idle blend, subtle head movement).
- NPC eyes look toward the player character via MetaHuman look-at target.
- Ellipsis `...` pulses in the dialogue panel.
- **No timer shown.** The wait is framed as the character formulating a response.
- Timeout: **30 seconds.** On timeout → authored fallback line per NPC appears, game continues. Fallback lines must be authored for all 5 NPCs.

### Dialogue history
- Last 4 exchanges visible in a scrollable panel below the NPC face.
- NPC response renders word-by-word (20 ms/word text reveal over REST). This creates progressive pacing without real streaming. The full text is available client-side immediately; the reveal is a deliberate animation, not a wait.
- `session_id` is passed back on every subsequent turn.

### `memories_recalled` surfacing
- When `memories_recalled` is non-empty in the engine response: a small badge appears at the top of the dialogue panel for 5 seconds, then fades.
- Badge text is authored per memory node ID (a `TMap<FName, FText>` lookup table). Do not use the raw memory node ID as display text.
- If no recalled memories: badge does not appear. Never show an empty badge.

### Camera
- On interaction: smooth blend (0.3 s) from third-person world camera to per-NPC dialogue camera (a `DialogueCamSocket` socket authored on each NPC actor's skeleton, framing the face in close-up).
- All 5 NPCs require a `DialogueCamSocket`, including non-MetaHuman characters.
- On dialogue close: blend back to player spring-arm camera (0.4 s).
- The per-NPC socket position is a required deliverable in Phase 7. Add it to the Phase 7 checklist.

### Portrait lighting + dialogue-cam DoF (the highest-leverage visual)
- **This is a dialogue game — the dialogue close-up is where ~90% of visual judgment happens.** Scene
  lighting alone leaves a MetaHuman flat and dead in close-up (no catchlights, no skin read).
- Each NPC gets a **per-NPC dialogue key / eye light** (a small light parented to `DialogueCamSocket`,
  or a rig that follows the dialogue cam) giving **catchlights in the eyes**, readable subsurface skin,
  and a rim to separate the face from the background. Intensity/temperature tuned per NPC mood.
- The dialogue camera uses **shallow depth-of-field** focused on the face — instantly cinematic *and* it
  hides background greybox/low-detail props for free. Highest visual ROI per hour in the project.
- Both are Phase 7 deliverables (see checklist). Asset/recipe research lives in ASSET_ACQUISITION Task F2.

### `facial_expression` → MetaHuman
- Engine returns `{ "type": "neutral|happy|wary|fearful|angry|sad|...", "intensity": 0..100 }`.
- Map to MetaHuman morph target blend weights via a lookup table: `EFacialExpressionType` → `(blend_target_name, weight_curve)`.
- **Unknown types:** log the unrecognized type, fall back to `neutral`. Do not crash. Do not hard-fail on forward-compat values.
- Non-MetaHuman characters (Aldric, Henryk): apply expression changes via blend space or animation Blueprint. Reduced fidelity is acceptable.

### Degradation handling
- If `degradation_level != "full"` in the response: log the value, continue normally. Do not surface to player in demo v1.
- If engine unreachable (non-2xx, connection refused, timeout): authored fallback line appears. Game continues. No crash, no hang.

### Free-text guardrails
- Client enforces the 1000-character cap and rejects empty input before any HTTP call.
- Engine prompt template constrains NPC persona. Off-topic input produces in-character deflection.
- No moderation layer needed for demo v1 (controlled demo context).

### WebSocket scaffold (slice-2 — built, not wired in slice-1)
- `FNpcEngineWebSocketClient` with `OnDialogueChunk(FString)` / `OnDialogueComplete(FDialogueResponse)` delegates.
- Auth: `Authorization: Bearer` header on WS handshake.
- Parse `token` / `done` / `error` / `proactive_line` message types. Ignore `proactive_line` in slice-1.
- All WS-specific code marked `// TODO(SLICE-2-WS)`. Route slice-1 gameplay through REST.

---

## 10. Content Arc — Tavern → Village Beats

The golden path takes approximately 20 minutes.

| Beat | Location | What happens | Engine feature |
|------|----------|--------------|----------------|
| 1. Arrival | Tavern | Player enters. Mira greets a stranger. Neutral relationship — no prior memory. | Baseline; no `memories_recalled` |
| 2. Investigate the recipient | Tavern | Player asks about "the wine merchant from Riverwheel." Mira surfaces a memory of Aldric's origin ("came from up north — textiles before wine"). | `memories_recalled` as investigation tool |
| 3. Trust building | Tavern | 2–3 exchanges. Trust delta visible in meter. Mira's expression shifts (wary → warmer). | `relation_deltas`, `facial_expression` |
| 4. Gate 1 clears | Tavern | `trust > 25`: Mira reveals guards were asking about Aldric. Player has a lead. | Information trust gate |
| 5. Gate 2 clears (optional) | Tavern | `trust > 40`: Mira mentions someone in the back. Access to Lira is now possible. | Second information gate |
| 6. Lira's offer | Back room | Lira offers to buy the amulet. Faction fork presented as a binary choice prompt. | Faction standing, `POST /v1/action` |
| 7. Travel to market | → Market | Arrival cue: "Afternoon at the market square." Tick fires. | World clock, tick legibility |
| 8. Find Aldric | Market | Player identifies Aldric through Mira's description. Aldric is cautious. | Social investigation payoff |
| 9. Trade price gate | Market | Aldric's reward scales with trust. Player who built rapport gets +30%. | Price trust gate, economy |
| 10. Fork resolution | Market | Deliver to Aldric (guard lean) or return to sell to Lira (guild lean). Chain A complete. | Quest completion, faction standing |
| 11. Travel to barracks | → Barracks | Tick fires. Notice board updated to rumor tier. | World clock, notice board |
| 12. Sorn — trust building | Barracks | Sorn is direct and cautious. His trust requires honesty and persistence. | `relation_deltas`, personality expression |
| 13. Quest chain unlock | Barracks | `trust > 50`: `patrol_duty` quest appears in quest log. | Quest chain gate (signature payoff) |
| 14. Travel to market | → Market | Third tick fires. Old Henryk is present at his usual spot. | World clock |
| 15. **The distorted rumor** | Market | Henryk mentions the northern war — his version is wrong. Player who spoke with Sorn recognizes the distortion. | **Gossip + distortion (signature wow)** |
| 16. Rumor Journal reveal | Market | Player opens Tab. Journal shows Sorn → Mira → Henryk with distortion level at each hop. | Rumor Journal UI |
| 17. Next quest hook | Varies | Based on faction choice, `patrol_duty` or `missing_goods` is active. Demo v1 ends here — the world is different because the player was in it. | Quest chains, emergent consequence |

---

## 11. Asset Plan

### Long-pole order — start parallel to code immediately

| Priority | Asset | Source | Notes |
|----------|-------|--------|-------|
| 🔴 P1 | MetaHuman: Mira | MetaHuman Creator | Most dialogue → most expressions to tune. Start first. |
| 🔴 P1 | MetaHuman: Sorn | MetaHuman Creator | Stoic face; harder trust arc. Start with Mira. |
| 🔴 P2 | MetaHuman: Lira | MetaHuman Creator | After Mira/Sorn validated to avoid wasted rework. |
| 🔴 P2 | Tavern interior environment | Quixel Megascans / Fab medieval kit | Must match MetaHuman photorealism. Acquire kit before Phase 8. |
| 🟡 P3 | Market square / courtyard | Quixel / Fab outdoor medieval | Outdoor kit; can reuse some tavern textures. |
| 🟡 P3 | Guard barracks courtyard | Quixel / Fab | Simpler than tavern; share stone textures. |
| 🟡 P3 | Aldric character | Fab — rigged medieval merchant | Non-MetaHuman humanoid actor. |
| 🟡 P3 | Old Henryk character | Fab — rigged elderly merchant type | Non-MetaHuman humanoid actor. |
| 🟢 P4 | UI art: dialogue panel, journal, relationship meter, quest log | Design in-house | Wire-frame in Phase 4; art in Phase 9. |
| 🟢 P4 | Audio: tavern ambience | Fab audio packs | Hearth, murmur, clink. |
| 🟢 P4 | Audio: outdoor ambience | Fab audio packs | Market bustle, wind, distant drills. |
| 🟢 P4 | Audio: UI sounds | Fab audio packs | Quest accept, journal open, trust increase ping, faction choice. |
| ⚪ Post-demo | Voice acting | — | Not in demo v1. |

### MetaHuman VRAM strategy
- Mira (tavern main floor) and Lira (tavern back room) are in **separate sub-levels** (`L_Tavern` and `L_TavernBack`).
- `L_TavernBack` streams in only when the player crosses the back-room threshold. Mira and Lira are never loaded simultaneously.
- Sorn (barracks) is always a separate scene — no MetaHuman VRAM conflict.
- Target: never more than 1 MetaHuman loaded at the same time in any scene. Profile before committing to the art pass.
- **Fallback:** If VRAM profiling in Phase 7 shows pressure, drop Lira to a Marketplace humanoid character and refund the MetaHuman budget to environment quality.

### Environment art direction
Quixel photorealistic medieval throughout. MetaHuman characters are photorealistic — the environment must match or the style inconsistency is worse than a unified art style in either direction. Do not mix Quixel and stylized Fab assets in the same scene.

---

## 12. Milestone Roadmap

> Each phase is independently demoable. A Claude CLI session can execute any phase from this section alone — no conversation context needed. All `NpcEngineClient` code follows TDD (failing spec first). All gameplay values are data-driven via `Content/Seed/DemoWorld_v1.json` — no constants hardcoded in C++.

---

### Phase 0 — Engine Smoke Test
**Goal:** Verify the NPC Engine is reachable and seed data is correct before writing any Unreal code.  
**Independently demoable:** PowerShell output showing `/health` 200 and a non-empty `npc_response`.  
**Prerequisites:** NPC Engine docker-compose running; `NPC_ENGINE_API_KEY` set in environment.

- [ ] Run `make demo-seed` in the NPC Engine repo (or verify that `player_demo` and `mira_innkeeper` Character nodes exist via `GET /v1/graph/nodes/Character/player_demo`)
- [ ] PowerShell smoke test:
  ```powershell
  $h = @{ Authorization = "Bearer $env:NPC_ENGINE_API_KEY" }
  Invoke-RestMethod http://localhost:8000/health
  Invoke-RestMethod -Method Post http://localhost:8000/v1/dialogue `
    -Headers $h -ContentType application/json `
    -Body (@{ player_id="player_demo"; npc_id="mira_innkeeper"; player_message="Good evening." } | ConvertTo-Json)
  ```
- [ ] Confirm `npc_response` is a non-empty string. Record it as the session's smoke-test baseline.
- [ ] Store `NPC_ENGINE_URL` (default `http://localhost:8000`) and `NPC_ENGINE_API_KEY` in a gitignored `Config/NpcEngine.ini` or environment variables. Never commit either value.

---

### Phase 1 — NpcEngineClient (TDD)
**Goal:** The sole C++ network layer for all engine communication. No Unreal gameplay code calls `FHttpModule` directly.  
**Independently demoable:** All Automation Specs green; `npc_response` appears in Unreal Output Log via Exec command `NpcSmoke`.

- [ ] Create module `Source/NpcEngineClient/` with `NpcEngineClient.h`, `NpcEngineClient.cpp`, `NpcEngineClient.Build.cs`
- [ ] Module docstring on every file: Layer, Purpose, Dependencies, Public surface
- [ ] **Write failing Automation Specs first** (`NpcEngineClientSpec.cpp`):
  - [ ] `GetHealth()` parses `OkEnvelope`, returns `FHealthResponse { status, version }`
  - [ ] `PostDialogue(FDialogueRequest)` parses raw `DialogueResponse`, returns populated `FDialogueResponse`
  - [ ] `PostDialogue` with empty `player_message` returns `ERequestError::InvalidInput` — no HTTP call made
  - [ ] `PostDialogue` with `player_message` > 1000 chars returns `ERequestError::InvalidInput` — no HTTP call made
  - [ ] `PostDialogue` when engine returns non-2xx returns `ERequestError::NetworkError`; `npc_response` set to authored fallback text
  - [ ] `PostClockAdvance(int32 Delta)` calls `/clock/advance` with `{ "delta_ticks": Delta }`, returns `bool` success
  - [ ] `PostAction(FActionReportRequest)` calls `/v1/action`, returns raw status string
  - [ ] `UpsertNode(FString NodeType, TMap<FString, FString> Properties)` calls `POST /v1/graph/nodes/{NodeType}`, returns bool
  - [ ] `UpsertEdge(FString EdgeType, FString SrcId, FString DstId, TMap<FString, FString> Properties)` calls `POST /v1/graph/edges/{EdgeType}`, returns bool
  - [ ] `CheckNodeExists(FString NodeType, FString NodeId)` calls `GET /v1/graph/nodes/{NodeType}/{NodeId}`, returns bool
- [ ] **Implement `NpcEngineClient` to pass all specs:**
  - [ ] Read `NPC_ENGINE_URL` and `NPC_ENGINE_API_KEY` from environment or `Config/NpcEngine.ini` at startup. `UE_LOG(LogNpcEngine, Fatal, ...)` if either is missing — fail fast.
  - [ ] All HTTP via `FHttpModule`. All callbacks fire on game thread (safe to touch UObjects).
  - [ ] Response shape branch: raw JSON body for `/v1/dialogue` and `/v1/action`; read `.data` field for all other endpoints (OkEnvelope).
  - [ ] `FDialogueResponse` USTRUCT: `NpcResponse (FString)`, `RelationDeltas (FRelationDeltas)`, `MoodUpdate`, `Emotion`, `Action (FActionModel)`, `FacialExpression (FFacialExpressionModel)`, `LearnedFacts (TArray<FString>)`, `MemoriesRecalled (TArray<FString>)`, `SessionId`, `Cached (bool)`, `DegradationLevel (FString)`, `AudioBytes (optional TArray<uint8>, stub only)`.
  - [ ] `EFacialExpressionType` enum: `Neutral, Happy, Wary, Fearful, Angry, Sad`. Unknown string values: `UE_LOG` the value, return `Neutral`. Never crash on forward-compat values.
  - [ ] `EActionType` enum: `Speak` as default. Unknown values coerce to `Speak` and log.
  - [ ] Dialogue timeout: 30 s. Health timeout: 3 s. Both configurable via `Config/NpcEngine.ini`.
  - [ ] Authored fallback lines: `TMap<FName /* npc_id */, FText>` in a data asset. Used on timeout or non-2xx.
- [ ] Scaffold `FNpcEngineWebSocketClient`: `OnDialogueChunk(FString)` / `OnDialogueComplete(FDialogueResponse)` delegates, parse `token` / `done` / `error` / `proactive_line` types. Mark all methods `// TODO(SLICE-2-WS)`. Do not wire.
- [ ] Exec command `NpcSmoke` calls `GetHealth()` and one `PostDialogue` for `mira_innkeeper` and logs `npc_response`.
- [ ] All specs green. No file exceeds 300 lines.

---

### Phase 2 — World Skeleton + Tick
**Goal:** Three navigable locations in box geometry. Location arrival fires a world tick.  
**Independently demoable:** Player walks between three rooms; Output Log shows tick number incrementing on each arrival.

- [ ] Confirm UE5 third-person template is the project base (character movement, spring-arm, WASD)
- [ ] Create `ANpcLocation` Actor: `FName LocationId` property (e.g., `loc_tavern`), `bool bFiresTick` (default true)
- [ ] `loc_tavern_back`: `bFiresTick = false`
- [ ] Create `UNpcWorldSubsystem` (World Subsystem):
  - [ ] `OnPlayerArrived(FName LocationId)`: if `LocationId != CurrentLocationId` AND `bFiresTick` → call `NpcEngineClient->PostClockAdvance(1)` → increment local `TickCount` → log `LogNpcEngine: Tick {N} at {LocationId}` → broadcast `FOnTickAdvanced`
  - [ ] `CurrentLocationId` getter
- [ ] Player character calls `UNpcWorldSubsystem::OnPlayerArrived` on overlap with each `ANpcLocation`'s trigger volume
- [ ] Arrival subtitle widget: `UUserWidget` that shows `FText` for 3 seconds on `FOnTickAdvanced`, then fades. Authored per location for now (e.g., "Afternoon at the market square").
- [ ] Create three box-geometry levels: `L_Tavern`, `L_MarketSquare`, `L_GuardBarracks`. Travel between them via trigger volumes or door actors (simple level streaming or direct level load — pick one and stick with it).
- [ ] `L_TavernBack`: persistent sub-level in `L_Tavern`. Hidden by default. Streamed in / made visible when player passes the back-room threshold.
- [ ] Verify: Tavern → Market → Barracks → Market → Tavern. Log shows 4 ticks. Re-entering the same location shows no tick. Tavern back room entrance shows no tick.

---

### Phase 3 — Seeder + Seed Data
**Goal:** DemoGame owns all world seeding. Running the seeder against a fresh engine builds the complete demo world.  
**Independently demoable:** Seeder runs to completion with 0 errors against a fresh engine.

- [ ] Author `Content/Seed/DemoWorld_v1.json` — the single source of truth for all demo content:
  - [ ] Locations: `loc_tavern`, `loc_tavern_back`, `loc_market_square`, `loc_guard_barracks` (node_type `Location`)
  - [ ] Characters: all 5 NPCs with personality values per §7.3, biographies, `is_player: false`, `is_active: true`
  - [ ] Aldric biography must contain: *"Formerly traded textiles in Riverwheel before settling in Thornfield as a wine merchant."*
  - [ ] Authored distortion text per hop in NPC biography / belief fields (exact text per §7.2)
  - [ ] Player node: `player_demo`, `is_player: true`, `currency_balance: 60`, `name: "Traveler"`
  - [ ] Factions: Guard faction, Thieves' Guild faction
  - [ ] Edges: `LOCATED_AT` (each NPC → home location), `MEMBER_OF` (Lira → Thieves' Guild, Sorn → Guard), `RELATES_TO` (initial neutral stubs between NPCs who would know each other)
  - [ ] Event node: `northern_war_begins` with full authored text
  - [ ] `KNOWS_ABOUT` edge: Sorn → `northern_war_begins`
  - [ ] Quest nodes: `find_wine_merchant`, `deliver_amulet`, `aldric_confession`, `patrol_duty`, `captain_report`, `missing_goods`, `fence_confrontation` with objective text and chain links
  - [ ] Memory badge lookup: authored display strings per memory node ID (used by `memories_recalled` badge)
- [ ] Implement `UNpcWorldSeeder` (Game Instance Subsystem or utility Blueprint):
  - [ ] Reads `DemoWorld_v1.json`
  - [ ] For each node: `CheckNodeExists` → skip if found, else `UpsertNode`
  - [ ] For each edge: `UpsertEdge` (MERGE semantics — idempotent)
  - [ ] Seed order enforced: Locations → Factions → Characters → Edges → Quest nodes
  - [ ] Log each upsert. On any failure (non-2xx): `UE_LOG(LogNpcEngine, Error, ...)` and halt — do not silently continue
- [ ] Exec command `NpcSeedWorld` triggers seeder from console
- [ ] Verify: run seeder twice against a live engine. Second run logs 0 new nodes created (all skipped by idempotency check).
- [ ] Reconcile `DemoWorld_v1.json` with `docs/ENGINE_CONTRACT.md`. Any property shape drift → patch the seed.

---

### Phase 4 — Dialogue + Trust Gate (Greybox)
**Goal:** One complete investigation step playable: approach Mira, build trust, cross gate 1, learn Aldric's situation.  
**Independently demoable:** Approach a capsule, press E, type a message, receive a response, watch the trust meter move.

- [ ] `ANpcActor` base class: `FName NpcId`, `FName LocationId`, `USphereComponent` proximity trigger, interact prompt ("Press E to talk")
- [ ] `UDialogueComponent` on `ANpcActor`:
  - [ ] `StartDialogue(APlayerController*)`: begins a session, clears history
  - [ ] `SubmitMessage(FString PlayerMessage)`: validates non-empty and ≤ 1000 chars, calls `NpcEngineClient->PostDialogue`, passes `SessionId` if active
  - [ ] On response: caches `SessionId`, updates local `TrustDelta` accumulator, broadcasts `OnTrustChanged(FName NpcId, FRelationDeltas Deltas)`, fires `OnMemoriesRecalled(TArray<FString>)` if non-empty
  - [ ] On timeout / error: fires `OnFallbackLine(FName NpcId, FText FallbackText)`
- [ ] `UDialogueWidget` (added to player HUD):
  - [ ] Text input field. Locked (read-only) during LLM wait.
  - [ ] Dialogue history panel: last 4 exchanges, scrollable
  - [ ] Thinking state: `...` ellipsis animated during wait
  - [ ] `memories_recalled` badge: appears above history for 5 s on `OnMemoriesRecalled`. Text from authored memory badge lookup (see Phase 3 seed). Hidden when array is empty.
  - [ ] No art — white panels, legible fonts
  - [ ] Word-by-word text reveal: 20 ms/word animation on NPC response text. Full string available immediately; reveal is cosmetic animation.
- [ ] `URelationshipMeterWidget`: always-visible debug overlay. Shows `trust`, `fear`, `affection` as signed integers per active NPC. Animates on `OnTrustChanged`.
- [ ] Trust gate verification: accumulate trust with Mira past 25 via natural dialogue. Confirm she reveals the Aldric information (observe in dialogue history — do not check engine internals directly). Repeat with 3 fresh sessions. Gate must clear in all 3.
- [ ] No `FHttpModule` usage outside `NpcEngineClient`. Enforce via code review before merging Phase 4.

---

### Phase 5 — Quest System + Faction Fork (Greybox)
**Goal:** Full chain A playable: investigate → identify Aldric → deliver or sell → quest log shows complete.  
**Independently demoable:** Quest log updates as steps complete; faction choice fires and changes a visible standing value.

- [ ] `UQuestSubsystem` (World Subsystem):
  - [ ] `ActivateQuest(FName QuestId)`: adds to active quest list; broadcasts `OnQuestActivated`
  - [ ] `CompleteStep(FName QuestId, FName StepId)`: marks step complete, checks if next step unlocks, broadcasts `OnStepCompleted`
  - [ ] Quest data loaded from `DemoWorld_v1.json` (same seed file — no duplicate data)
- [ ] `UQuestLogWidget`: active quest list. Each step has a title and a checkbox. No map markers. Quest becomes visible in log only when `ActivateQuest` is called.
- [ ] Quest confirm prompt: UI overlay ("Accept quest: [title]?") appears when NPC dialogue resolves to a quest offer. Accept calls `POST /v1/quest/offer` (to register the quest) then `POST /v1/quest/accept` (to mark player acceptance) — both with `{ quest_id, player_id }`. Decline dismisses. Use `POST /v1/quest/{quest_id}/choose` for the faction fork branch decision (`choice_id` = `"aldric"` or `"lira"`).
- [ ] `UNpcFactionSubsystem`: tracks `TMap<FName /* faction_id */, int32 /* standing */>`. Updated by `POST /v1/action` responses and dialogue `relation_deltas` where the NPC is faction-affiliated.
- [ ] Faction fork prompt: binary choice UI ("Deliver to Aldric" vs "Sell to Lira"). Choice calls `POST /v1/action` with `action_type: "sell_item"` (Lira path) or quest step completion (Aldric path). Log faction standing change to Output Log.
- [ ] `L_TavernBack` sub-level: visible only after Mira's gate 2 clears (`trust > 40`). Gate visibility to a bool set by `UNpcWorldSubsystem` listening to `OnTrustChanged`. When gate opens, a door actor or archway becomes passable.
- [ ] `USaveGame` implementation: persist `player_id`, active quest steps, faction standings. Load on startup. Save on quest step completion and faction choice.
- [ ] Verify chain A end-to-end: fresh save → investigate → identify Aldric → deliver (or sell) → quest log shows complete → `aldric_confession` step appears → faction standing logged.

---

### Phase 6 — Gossip Chain + Rumor Journal (Greybox)
**Goal:** Distorted rumor arrives at Old Henryk. Rumor Journal shows the full chain. Sorn's quest chain unlocks.  
**Independently demoable:** Tab shows a Sorn → Mira → Henryk chain entry after completing the golden path to beat 15.

- [ ] `UGossipCacheSubsystem`: stores gossip entries locally. Updated when:
  - The player talks to an NPC whose dialogue reveals war-related content (keyed by NPC ID + keyword pattern)
  - `learned_facts` in a dialogue response contains a war-related fact
  - After each tick, call `GET /v1/npc/old_henryk/state` to check if `knowledge_state` on the war event has updated (use this to trigger the journal entry for Henryk's hop)
- [ ] `URumorJournalWidget` (Tab key):
  - [ ] List of known gossip chains
  - [ ] Per-chain: source → intermediate → endpoint NPC portrait cards
  - [ ] Each hop shows: NPC name, authored distortion text (from seed), distortion level badge: `0 → "Firsthand"`, `1 → "Rumor"`, `2+ → "Distorted"`
  - [ ] Chain entry appears only after the player has spoken to the NPC at that hop
  - [ ] No art — readable text layout only in greybox
- [ ] `ANoticeBoard` actor:
  - [ ] `TArray<FText> RumorTiers` (authored — 3 tiers: pre-war / rumors spreading / distorted widely)
  - [ ] On `UNpcWorldSubsystem::OnTickAdvanced`: advance to next tier if `TickCount` passes authored thresholds
  - [ ] On examine (E): display current tier text in a popup panel
- [ ] Sorn quest chain unlock: `UDialogueComponent::OnTrustChanged` for Sorn → if `AccumulatedTrust > 50` → `UQuestSubsystem::ActivateQuest("patrol_duty")` → quest log updates
- [ ] **Gossip chain verification (mandatory before Phase 7):** Run the full golden path 5 times from a fresh seed (Tavern → Barracks → Tavern → Market, talking to Sorn and then Henryk). In all 5 runs, Henryk's dialogue response must contain the distorted war account. If any run fails: tune `gossipy`/`credulity` personality values in `DemoWorld_v1.json` and rerun. Do not advance until 5/5 pass.
- [ ] **Greybox acceptance gate:** The complete golden path (all 17 beats in §10) is playable start-to-finish. All trust gates, quest steps, gossip chain, journal, and faction fork are functional. If any beat is non-functional, it is a blocker for Phase 7.

---

### Phase 7 — MetaHuman + Dialogue Camera
**Goal:** Replace capsule NPCs with MetaHuman actors. Cinematic dialogue camera active.  
**Independently demoable:** Initiating dialogue with Mira shows her MetaHuman face with engine-driven expressions.  
**Prerequisite:** MetaHuman customization for Mira, Sorn, and Lira must be complete before starting this phase.

- [ ] Import Mira MetaHuman → `BP_NPC_Mira` (extends `ANpcActor`)
- [ ] Import Sorn MetaHuman → `BP_NPC_Sorn`
- [ ] Import Lira MetaHuman → `BP_NPC_Lira`
- [ ] Source and import Aldric humanoid actor from Fab → `BP_NPC_Aldric`
- [ ] Source and import Old Henryk humanoid actor from Fab → `BP_NPC_Henryk`
- [ ] Per-NPC `DialogueCamSocket` skeletal socket on each NPC actor: positioned to frame the face in close-up at the NPC's eye level. Required for all 5 NPCs.
- [ ] **Per-NPC portrait light** parented to `DialogueCamSocket` (or a rig following the dialogue cam): catchlights in the eyes, readable subsurface skin, a separating rim. Tune intensity/temperature per NPC mood. Required for all 5 NPCs — a face lit only by ambient scene light reads flat/dead in close-up (see §9 Portrait lighting).
- [ ] **Dialogue-cam depth of field:** shallow DoF focused on the face (focal distance on the head socket, aperture tuned for background fall-off). Cinematic + hides background greybox. Verify the face stays in focus through the 0.3 s blend-in.
- [ ] `UDialogueComponent` camera blend:
  - [ ] On `StartDialogue`: `APlayerController::SetViewTargetWithBlend(NpcDialogueCam, 0.3f, VTBlend_Cubic)`
  - [ ] On dialogue close: blend back to player `USpringArmComponent` camera (0.4 s)
- [ ] MetaHuman look-at: during thinking state, NPC's look-at target set to the player character's head socket. Cleared on response received.
- [ ] `FacialExpressionType` → MetaHuman morph target lookup table. Implement `UFacialExpressionMapper` (one class, one file):
  - [ ] Maps each expression type to a `(TargetName, WeightCurve)` pair
  - [ ] `ApplyExpression(USkeletalMeshComponent*, EFacialExpressionType, int32 Intensity)`: blends to target weight over 0.3 s
  - [ ] Unknown types log and apply `Neutral`
- [ ] Non-MetaHuman characters (Aldric, Henryk): apply expression via Animation Blueprint state machine with simplified emotion states.
- [ ] VRAM profile: load `L_Tavern` with Mira in scene. Check GPU memory usage. Load `L_GuardBarracks` with Sorn. Confirm neither scene exceeds 10 GB VRAM. If Mira scene exceeds 10 GB, investigate and resolve before Lira MetaHuman import.
- [ ] Verify: Mira and Lira are never in GPU memory simultaneously (confirm via Unreal memory stats or RenderDoc). If sub-level streaming causes them to co-load, add an explicit unload call on `L_TavernBack` when leaving the tavern.

---

### Phase 8 — Environment Art Pass
**Goal:** Replace box geometry with sourced environment assets.  
**Independently demoable:** The tavern, market, and barracks look and feel like a real medieval world.  
**Prerequisite:** Fab/Quixel asset packs acquired before starting.

- [ ] Build every scene to the **§7.1.1 Visual & lighting direction** table — hero light, contrast, color story, focal point, atmosphere — not just the object list below.
- [ ] Tavern interior (`L_Tavern`): hearth, bar, tables, candles, wooden beams. Source Quixel medieval interior kit. **Hearth is the hero key + cool window/door shafts for the warm/cool split** (§7.1.1). Add volumetric haze + dust motes in the shafts.
- [ ] Tavern back room (`L_TavernBack`): crates, barrels. **One motivated hard lantern key on Lira with deep falloff — NOT a global "dark post-process volume"** (that reads muddy). Chiaroscuro: the fence in shadow.
- [ ] Market square (`L_MarketSquare`): cobblestone, merchant stalls, notice board prop, awnings. Source Quixel outdoor medieval kit. **Low warm late-afternoon sun (~15–25°) for long raking shadows**; add life-proxy dressing (produce/baskets/cloth/sacks) so empty stalls don't read as a parking lot.
- [ ] Guard barracks courtyard (`L_GuardBarracks`): stone walls, gate arch, training props (non-interactive decoration). Share stone *materials* with market, but **different time/temperature** (colder/later) + banners/weapon-racks/gravel ground so the player feels they traveled.
- [ ] Notice board prop: `ANoticeBoard` actor placed in market and barracks. Physical examine trigger (E near prop → show current tier text).
- [ ] Lighting (per **DEC-030**): **Lumen GI + reflections** for the hearth-lit interiors (warm bounced GI is the tavern's whole look and tolerates flickering fire). Outdoors: Sky Atmosphere + **one directional sun aligned to the HDRI's sun direction** (avoid double-shadows) + SkyLight + Exponential Height Fog + Volumetric Fog + light shafts. Enable **DLSS/TSR upscaling** to fund the Lumen cost on the 5070 Ti. Bake only if Phase 7 VRAM profiling forces it.
- [ ] NavMesh volumes in each level (non-functional in demo v1, required for clean NPC placement without collision issues).
- [ ] Level streaming performance check: transition between `L_Tavern` and `L_MarketSquare` must complete without a hitch longer than 1 frame at 60 fps target. Add a brief transition fade if needed.

---

### Phase 9 — UI Polish + Audio
**Goal:** Dialogue panel art, journal art, relationship meter HUD, ambient audio, UI sounds.  
**Independently demoable:** The full game loop looks and sounds like a shipped product.

- [ ] Dialogue panel art: parchment or dark-tavern-wood theme. Text history area, input field with send icon, `memories_recalled` badge styled as a floating amber note.
- [ ] Rumor Journal art: chain entries as connected cards with hand-drawn connector lines. Distortion level badge: green (Firsthand), yellow (Rumor), red (Distorted).
- [ ] Relationship meter: small NPC portrait + trust bar per NPC encountered. HUD corner position. Trust bar animates on `OnTrustChanged` (spring animation, 0.5 s settle).
- [ ] Quest log art: parchment list. Active step highlighted. Completed steps with a checkmark.
- [ ] Arrival subtitle: elegant serif font, centered, 3-second fade. Semi-transparent letter-box bars optional.
- [ ] Ambient audio — import and assign to Audio Volume components:
  - [ ] Tavern: hearth crackle, low murmur, wood creak loop
  - [ ] Market: outdoor bustle, wind, cart sounds
  - [ ] Barracks: distant drills, metal clank, wind
- [ ] UI sounds — assign to widget events:
  - [ ] Quest accept: light confirmation chime
  - [ ] Journal open/close: parchment rustle
  - [ ] Trust increase: subtle positive ping
  - [ ] Faction choice confirm: weighted tone (neutral)
- [ ] All audio via Unreal MetaSounds or Sound Cues. No audio hardcoded inline.

---

### Phase 10 — Content Polish + Acceptance Validation
**Goal:** All authored content finalized, seed verified, acceptance criteria passed.  
**Independently demoable:** A naive player completes the full golden path in ≤ 25 minutes without guidance.

- [ ] Author all notice board texts (3 tiers × 3 locations = 9 entries). Town name: Thornfield in all texts.
- [ ] Author `memories_recalled` badge text for all memory node IDs in the seed (full lookup table)
- [ ] Author fallback canned lines for all 5 NPCs (used on 30 s LLM timeout)
- [ ] Final gossip chain verification: 5 fresh-seed runs. All 5 must show Henryk delivering the distorted war account. If any fail, tune `DemoWorld_v1.json` personality values and rerun.
- [ ] Final distortion review: play as a player who spoke with Sorn, then talk to Henryk. Is Henryk's version recognizably a corruption of Sorn's? If the playtest observer cannot identify the connection, exaggerate the authored distortion text and re-verify.
- [ ] Author `aldric_confession` dialogue context — **content is decided, seed these verbatim:**  
  - `aldric_merchant.belief["amulet_origin"]`: *"This amulet — I took it as trade debt in Riverwheel from a soldier passing through. He needed coin quickly; I didn't ask why. That was weeks ago. Now I have guardsmen coming to my stall asking what I know. I understand it now: that man deserted his post. He fled the northern garrison before the skirmish was reported, and this is what he left behind. I'm holding his evidence. That's what they want."*  
  - `aldric_merchant.secret["amulet_truth"]`: *"The amulet is evidence of a desertion from the northern garrison. The soldier who owned it sold it to Aldric to fund his flight from the northern pass before the skirmish the guards are suppressing."*
- [ ] `DemoWorld_v1.json` reconciled against live `GET /openapi.json` and `docs/ENGINE_CONTRACT.md`. Any property drift patched.
- [ ] Naive user playtest: one person who has not seen the demo plays without guidance. Observer notes every moment of confusion. Fix every "what do I do next?" moment before marking acceptance.
- [ ] Run acceptance criteria checklist (§14). All items must pass. No partial credit.

---

## 13. Risks & Open Questions

### Risks

| Risk | Severity | Mitigation |
|------|----------|------------|
| Gossip propagation fails on demo day | HIGH | 5-run verification in Phase 6 before any art pass. Do not ship without 5/5. Tune personality values if needed. |
| LLM latency (Ollama CPU: 5–30 s) ruins pacing | HIGH | 30 s timeout + authored fallback lines. Thinking animation frames the wait as character deliberation. Frame latency as a feature, not a bug. |
| MetaHuman VRAM exceeds RTX 5070 Ti budget | MEDIUM | Sub-level streaming enforced. Never load Mira + Lira simultaneously. Profile before art pass. Drop Lira to Marketplace character if VRAM > 10 GB with Mira scene loaded. |
| Seed data drifts from engine schema | MEDIUM | `DemoWorld_v1.json` is the single source of truth. After any NPC Engine schema change, re-run seeder + smoke test before any other work. |
| Information discovery too opaque | MEDIUM | Naive user playtest in Phase 10 specifically tests "where do I go next?" moments. Fix all of them. |
| Tavern sub-level streaming hitch | LOW | Test streaming boundary at 60 fps target. If hitch > 1 frame, add a brief crossfade. Pre-stream `L_TavernBack` on tavern entry if necessary (accept the VRAM cost, revisit if budget is tight). |
| NPC goes off-topic / breaks persona | LOW | Engine prompt template constrains personality. Off-topic input produces in-character deflection. Not a crash risk; acceptable for demo v1. |

### Open Questions

1. **Quest lifecycle endpoint shape:** ~~Verify quest accept / complete endpoint paths and request bodies against `GET http://localhost:8000/openapi.json` before Phase 5. The curated `openapi.json` does not include these.~~  
   **Resolved** — verified against `src/npc_engine/api/routes/quest/quest.py` and `api/schemas.py`. All endpoints mount under `POST /v1/quest/`. Full shapes:

   | Intent | Endpoint | Minimum body |
   |--------|----------|-------------|
   | Offer a quest to a player | `POST /v1/quest/offer` | `{ "quest_id": "…", "player_id": "…", "title": "…", "objectives": [{"objective_id": "…", "description": "…", "required_progress": 1}], "item_rewards": [], "currency_reward": null }` |
   | Player accepts the offer | `POST /v1/quest/accept` | `{ "quest_id": "…", "player_id": "…" }` |
   | Advance objective progress | `POST /v1/quest/objective` | `{ "quest_id": "…", "player_id": "…", "objective_id": "…", "progress_delta": 1 }` |
   | Check if quest is complete | `POST /v1/quest/evaluate` | `{ "quest_id": "…", "player_id": "…" }` |
   | Apply rewards after completion | `POST /v1/quest/reward` | `{ "quest_id": "…", "player_id": "…" }` |
   | Select a chain branch (faction fork) | `POST /v1/quest/{quest_id}/choose` | `{ "player_id": "…", "choice_id": "…" }` |

   **Implementation note:** The faction fork (Aldric vs Lira) uses `POST /v1/quest/{quest_id}/choose` with `choice_id` matching the authored branch key in the seed. The engine follows the `UNLOCKS` edge whose `on_choice_id` matches and auto-offers the next quest. Use this instead of `POST /v1/action` for quest chain branching.

2. **`/clock/advance` endpoint body:** ~~Confirm the request body shape (`{ "delta_ticks": 1 }` or different) against the live spec before Phase 2.~~  
   **Resolved** — verified against `src/npc_engine/api/routes/world/clock.py`. Minimum body: `{ "delta_ticks": 1 }`. Two optional extras exist — `game_time_seconds` (int, default 1) and `advance_time_field` (string or null, advances a structured time field on WorldState) — neither is required for Phase 2. The roadmap's assumed shape is correct.

3. **Save on engine restart:** ~~The NPC Engine persists NPC graph state server-side. If the engine is restarted between sessions, does NPC state persist across restart? Clarify with NPC Engine team. If state does not persist, the seeder must detect and re-seed on each engine restart.~~  
   **Resolved** — verified in `docker-compose.yml`. Neo4j uses a named Docker volume (`neo4j_data:/data`). All graph state persists across engine restarts, including `docker-compose down` / `docker-compose up` cycles. State is only wiped if the volume is explicitly deleted (`docker-compose down -v`). The seeder's existing idempotency check (`CheckNodeExists` → skip) is the correct and sufficient strategy for all normal restart scenarios.

4. **Aldric's confession content:** ~~What exactly does Aldric reveal about the amulet's connection to the northern war? This content must be authored in Phase 10. Decision: defer until Phase 9, author as a belief/secret node in the seed.~~  
   **Resolved** — authored content confirmed. See §7.3 (Aldric cast entry) for the updated belief and §7.6 for the quest step detail. Summary: the amulet belonged to a garrison soldier who deserted from the northern pass and settled a trade debt with Aldric in Riverwheel. Aldric received it unknowingly, but when soldiers started asking about him, he understood: he is holding physical evidence of a desertion the garrison is trying to suppress.

5. **Thornfield name:** ~~The town name is proposed as "Thornfield." Confirm and propagate to all authored text in `DemoWorld_v1.json` before Phase 3.~~  
   **Resolved** — confirmed Thornfield. Already propagated in §7.1 and the Phase 10 notice-board authoring task. Use "Thornfield" in all authored text; no further confirmation needed.

6. **Village arc (demo v2):** The demo ends at beat 17. The "tavern → village" arc's village half is deferred. Requires new seed locations, new cast, and a second gossip chain seeded from the war rumor. Plan scope for v2 after demo v1 acceptance.  
   **Status:** Accepted as deferred. No action needed before demo v1 acceptance.

---

## 14. Acceptance Criteria for Demo v1

A session qualifies as **demo-complete** when ALL of the following pass without developer intervention:

### Setup
- [ ] Engine health check returns 200. Seeder runs to completion with 0 errors.
- [ ] `NpcSmoke` Exec command returns a non-empty `npc_response` in Output Log.

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
- [ ] Gate 1 (Mira trust > 25): Mira reveals information about Aldric's situation. Gate clears in dialogue — no waypoint marker required.
- [ ] Player identifies Aldric through 2+ NPC conversations. No map marker. Observer can confirm the player discovered Aldric socially.

### Quest System
- [ ] Quest log shows `find_wine_merchant` as the first active step.
- [ ] Chain A completes: quest log shows `deliver_amulet` complete, `aldric_confession` step appears.
- [ ] Faction fork fires. Faction standing changes (logged or visible in debug HUD).
- [ ] Lira's back room is inaccessible below gate 2 and accessible above it.

### Gossip Chain + Journal
- [ ] After the golden path (Tavern → Barracks → Tavern → Market with appropriate conversations), Old Henryk's dialogue contains the distorted war account.
- [ ] A naive observer who heard the player's conversation with Sorn can identify Henryk's account as a distortion of it.
- [ ] Rumor Journal (Tab) shows the Sorn → Mira → Henryk chain with distortion level labels at each hop.
- [ ] Sorn trust gate unlocks `patrol_duty`. Quest appears in the quest log.

### Stability
- [ ] No crashes across the full golden path.
- [ ] LLM timeout produces a fallback line — no hang, no freeze, no error popup.
- [ ] `DegradationLevel != "full"` is logged silently and does not break the game.

### Playtest Gate
- [ ] A naive player (who has not seen the demo) reaches beat 15 (the gossip reveal) within 25 minutes without being guided.

---

*Roadmap version: 1.0 · 2026-06-23 · Adversarial design session*  
*Next review checkpoint: after Phase 6 greybox acceptance (gossip chain 5/5 verified)*
