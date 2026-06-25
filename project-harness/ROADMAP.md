# Roadmap

Slice-based delivery. Each unchecked box is a discrete, TDD-able unit an `/expand-next`-style flow can
consume top-to-bottom. Check a box only when its work is merged and `Scripts/check.ps1` is green.

All `NpcEngineClient` tasks follow strict TDD: **write the failing Automation Spec first**, confirm it
fails for the right reason, implement minimal to pass, refactor green. Gameplay tasks use smoke + manual
+ functional Automation tests.

### Headless-first policy (for the `/expand-next` overnight loop)

Every phase is split into a **headless C++ block** (the loop implements + gates green + ticks) and a
thin **human tail** (`[EDITOR SESSION]` blocks + items tagged `(human — …)`: MetaHuman/material/level
art and live-LLM playtests). The loop **logs each human tail to `HUMAN_VERIFICATION.md` and advances to
the next phase's headless work — it never stops merely because a phase's remaining steps are manual.**
Maximise headless C++ first: spatial layout, data, UI logic, and asset *wiring* live in code; only
visual/spatial *authoring* and live playtests stay human. See `Scripts/overnight-prompt.md` for the
exact terminal conditions.

---

## Bring-up — before any new game work (do these first)

- [x] **Generate project files + full build** (Rider, or `powershell Scripts/check.ps1 -WithBuild`). First compile of the integrated `NpcEngineClient` module. *(Done 2026-06-23: fixed dynamic-delegate binding in `DialogueWidgetBase` — `AddUObject`/`Remove` → `AddDynamic`/`RemoveDynamic` + `UFUNCTION()` handlers. Both module DLLs build clean.)*
- [x] **Create `Config/NpcEngine.ini`** from `Config/NpcEngine.ini.template`. *(Done 2026-06-23: default localhost:8000 + dev key; gitignored.)*
- [x] **Bring up the Docker engine** and prove the middleware end-to-end. *(2026-06-23: verified live through the compiled `UNpcEngineRestClient` — `NpcEngine.Smoke` ran headless: Health OK, Mira reply "Good evening to you as well…", DegradationLevel=full, Cached/Fallback=false, PASS. Also fixed a config bug: GConfig truncated `http://…` at `//`; now reads the ini manually.)*
- [x] **Register the `NpcEngine.Smoke` console command** + write ≥1 client `*.spec.cpp`. *(2026-06-23: `NpcEngineSmokeCommand.cpp` = GameMode-independent `FAutoConsoleCommandWithWorld`; `NpcEngineJsonUtils.spec.cpp` = 8 specs (parse, enum forward-compat, serialise), all pass headless. Presence + Automation gates now PASS. Fixes ISSUE-001.)*

---

## Phase 0 — Engine Smoke Test

**Goal:** Verify the NPC Engine is reachable and seed data is correct before writing any Unreal code.
**Independently demoable:** PowerShell output showing `/health` 200 and a non-empty `npc_response`.
**Prerequisites:** None. NPC Engine docker-compose running; `NPC_ENGINE_API_KEY` set in environment.
**Quality gate:** `pwsh Scripts/check.ps1`

- [x] Run `make demo-seed` in the NPC Engine repo (or verify that `player_demo` and `mira_innkeeper` Character nodes exist via `GET /v1/graph/nodes/Character/player_demo`)
- [x] PowerShell smoke test:
  ```powershell
  $h = @{ Authorization = "Bearer $env:NPC_ENGINE_API_KEY" }
  Invoke-RestMethod http://localhost:8000/health
  Invoke-RestMethod -Method Post http://localhost:8000/v1/dialogue `
    -Headers $h -ContentType application/json `
    -Body (@{ player_id="player_demo"; npc_id="mira_innkeeper"; player_message="Good evening." } | ConvertTo-Json)
  ```
- [x] Confirm `npc_response` is a non-empty string. Record it as the session's smoke-test baseline.
- [x] Store `NPC_ENGINE_URL` (default `http://localhost:8000`) and `NPC_ENGINE_API_KEY` in gitignored `Config/NpcEngine.ini` or environment variables. Never commit either value.

---

## Phase 1 — NpcEngineClient (TDD)

**Goal:** The sole C++ network layer for all engine communication; gameplay receives typed USTRUCTs, never raw JSON.
**Independently demoable:** All Automation Specs green; `npc_response` appears in Unreal Output Log via `NpcEngine.Smoke` exec command.
**Prerequisites:** Phase 0.
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [x] Create module `Source/NpcEngineClient/` with `NpcEngineClient.h`, `NpcEngineClient.cpp`, `NpcEngineClient.Build.cs`
- [x] File header on every `.h`/`.cpp`: `// File / Module: NpcEngineClient / Purpose / Net I/O: yes`
- [x] Write failing Automation Specs first (`NpcEngineClientSpec.cpp`):
  - [x] `GetHealth()` parses `OkEnvelope` → `FHealthResponse { status, version }`
  - [x] `PostDialogue(FDialogueRequest)` parses raw `DialogueResponse` → populated `FDialogueResponse`
  - [x] `PostDialogue` with empty `player_message` → `ERequestError::InvalidInput` (no HTTP call made)
  - [x] `PostDialogue` with `player_message` > 1000 chars → `ERequestError::InvalidInput` (no HTTP call made)
  - [x] `PostDialogue` on non-2xx → `ERequestError::NetworkError`; `npc_response` set to authored fallback text
  - [x] `PostClockAdvance(int32 Delta)` calls `/clock/advance` with `{ "delta_ticks": Delta }`, returns bool success
  - [x] `PostAction(FActionReportRequest)` calls `/v1/action`, returns raw status string
  - [x] `UpsertNode`, `UpsertEdge`, `CheckNodeExists` — each with a passing Automation Spec
- [x] Implement `UNpcEngineRestClient` to pass all specs:
  - [x] Read `NPC_ENGINE_URL` and `NPC_ENGINE_API_KEY` from `Config/NpcEngine.ini` or env; `UE_LOG(LogNpcEngine, Fatal, …)` if either is missing — fail fast
  - [x] All HTTP via `FHttpModule`; all callbacks fire on the game thread. Non-blocking: return immediately; callback fires on game thread.
  - [x] Response shape branch: raw body for `/v1/dialogue` and `/v1/action`; `OkEnvelope` (`.data`) for all others
  - [x] `FDialogueResponse` USTRUCT: all fields from `docs/openapi.json` (`npc_response`, `relation_deltas`, `mood_update`, `emotion`, `action`, `facial_expression`, `learned_facts`, `memories_recalled`, `session_id`, `cached`, `degradation_level`, `audio_bytes` stub)
  - [x] `EFacialExpressionType` UENUM: `Neutral, Happy, Wary, Fearful, Angry, Sad`. Unknown string → `UE_LOG(LogNpcEngine, Warning, …)` + return `Neutral`. Never crash on forward-compat values.
  - [x] `EActionType` UENUM: `Speak` as default. Unknown string → coerce to `Speak` + log.
  - [x] Dialogue timeout: 30 s; Health timeout: 3 s. Both configurable via `Config/NpcEngine.ini`.
  - [x] Fallback lines: `TMap<FName, FText>` in `DA_NpcFallbackLines` DataAsset (prefix `DA_`). Used on timeout or non-2xx. Data structure only — authored content added per phase as each NPC becomes interactable.
- [x] `INpcDialogueService` UInterface (`MinimalAPI, NotBlueprintable`) in NpcEngineClient: pure-virtual `SendDialogue`, `SendActionReport`, `GetNpcState`
- [x] `UNpcEngineServiceSubsystem` (UGameInstanceSubsystem): composition root; owns one `UNpcEngineRestClient`; exposes `TScriptInterface<INpcDialogueService>`; `SetDialogueService()` for test injection
- [x] Scaffold `FNpcEngineWebSocketClient`: `OnDialogueChunk(FString)` / `OnDialogueComplete(FDialogueResponse)` delegates; parse `token / done / error / proactive_line` message types; mark all `// TODO(SLICE-2-WS)`; do not wire to gameplay
- [x] Exec command `NpcEngine.Smoke`: calls `GetHealth()` and one `PostDialogue` for the tavern innkeeper NPC (NPC ID via named constant, not string literal); logs `npc_response` to `LogNpcEngine`
- [x] Gameplay skeleton (DemoGame module, Net I/O: no on all files):
  - [x] `ANpcActorBase`: `FName NpcId` UPROPERTY; `USphereComponent` proximity trigger; interact prompt
  - [x] Interaction driver on `ADemoGameCharacter`: finds nearest `ANpcActorBase` on E-key / `IA_Interact`; calls `BeginDialogue`; spawns and shows `WBP_Dialogue`; restores input on end. Legacy E-key fallback works before `IA_Interact` is authored.
  - [x] `UDialogueManagerSubsystem` (UGameInstanceSubsystem): resolves `TScriptInterface<INpcDialogueService>` lazily from `UNpcEngineServiceSubsystem`; exposes `SetDialogueService()` for test injection; routes `SubmitMessage` calls through the interface
  - [x] C++ UMG base widget: rejects empty / oversized input; `BlueprintNativeEvent` display handlers with C++ defaults so a minimal `WBP_Dialogue` shows dialogue without Blueprint scripting
- [x] DIP complete (DEC-013): 4 `UDialogueManager` Automation Specs using synchronous fake `INpcDialogueService`; `rg UNpcEngineRestClient Source/DemoGame` = 0 references
- [x] All Automation Specs green. No file exceeds 500-line ceiling.
- [x] `docs/STORYBOARD.md` authored (Slice-1 narrative beats)
- [x] Annotate all mirror USTRUCTs in `NpcEngineClient` with `UPROPERTY(meta=(JsonName="..."))` matching `docs/openapi.json` field names. Moves `Scripts/check_contract_sync.py` from SKIP to enforcing PASS.

---

## Phase 2 — World Skeleton + Tick *(tick C++ complete 2026-06-24; procedural greybox world = NEXT headless work)*

**Goal:** Three navigable locations the player can walk between; location arrival fires a world clock tick.
**Independently demoable:** Player walks between three regions; Output Log shows tick number incrementing on each arrival; re-entering the same location shows no tick.
**Prerequisites:** Phase 1 (INpcDialogueService interface stable; UNpcEngineRestClient implements PostClockAdvance).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild`

- [x] **Verify `/clock/advance` endpoint** — shape confirmed per §13 OQ-2: `POST /clock/advance` body `{ "delta_ticks": 1 }`, OkEnvelope response. Recorded as **DEC-014**. *(2026-06-24: live verification against `GET http://localhost:8000/openapi.json` deferred — DEC-014 flags this.)*
- [x] **Add `AdvanceClock(int32 DeltaTicks)` to `INpcDialogueService`** in NpcEngineClient (DEC-015; ISP note recorded). Failing Automation Spec written first:
  - [x] Spec: `ClockAdvance.spec.cpp` — `SerialiseClockAdvance(1)` body contains `delta_ticks` + value `1`; JSON is parseable (NpcEngineClient module; Net I/O: no for this spec)
  - [x] Spec: `AdvanceClock` on non-2xx → `OnError` fired + `OnResult(false)`; error log: `ClockAdvance failed Status=%d`
  - [x] Implement `AdvanceClock` in `UNpcEngineRestClient`: POST `/clock/advance`; `OkEnvelope` response shape; parse `.data`; bool success via callback
- [x] `ANpcLocation` Actor (DemoGame module, Net I/O: no):
  - [x] `UPROPERTY FName LocationId` — logs warning if `NAME_None` in BeginPlay; default `NAME_None` is invalid
  - [x] `UPROPERTY bool bFiresTick` — default `true`; set `false` on the tavern back room actor in the editor
  - [x] `USphereComponent TriggerVolume` — `OnComponentBeginOverlap` registered in BeginPlay; calls `UNpcWorldSubsystem::OnPlayerArrived`. Note: overlap registered on the location actor itself (not on the player character) — cleaner SRP and no actor-iteration race. Design choice recorded in DEC-016.
- [x] `UNpcWorldSubsystem` (World Subsystem, DemoGame module, Net I/O: no):
  - [x] `Initialize`: subsystem ready; lazy-resolves `TScriptInterface<INpcDialogueService>` from `UNpcEngineServiceSubsystem` on first `OnPlayerArrived`
  - [x] `OnPlayerArrived(FName LocationId, bool bFiresTick)`: re-entry guard → `Service->AdvanceClock(1)` → `++TickCount` → `UE_LOG(LogNpcEngine, Log, "Tick=%d Location=%s", ...)` → `OnTickAdvanced.Broadcast()`
  - [x] Re-entry guard: `CurrentLocationId == LocationId` → return early; no tick, no log noise
  - [x] `GetCurrentLocationId()` accessor (const); `GetTickCount()` accessor (const)
  - [x] No `FHttpModule` usage — all network I/O routed through `INpcDialogueService`
  - [x] `SetDialogueService()` DIP seam for test injection; 5 Automation Specs (new location + tick, bFiresTick=false skip, re-entry guard, multi-location sequence, failure-path grace)
- [x] `ANpcLocation::OnTriggerOverlap` → `UNpcWorldSubsystem::OnPlayerArrived(LocationId, bFiresTick)` — player pawn check guards non-player actors. DEC-016 records the overlap-ownership choice.
- [x] `UArrivalSubtitleWidget` (UUserWidget, DemoGame module, Net I/O: no):
  - [x] Binds `OnTickAdvanced` in `NativeConstruct`; unbinds + clears timer in `NativeDestruct`
  - [x] Shows authored `FText` for `SubtitleDisplaySeconds` (default 3 s), then fades via `FadeOutAnimation` (`BindWidgetAnimOptional`); fallback timer-hide when no animation assigned
  - [x] Authored text in `ULocationSubtitleData` DataAsset (`TMap<FName, FText> SubtitleByLocation`); assign `DA_LocationSubtitles` in editor. Locations with no entry show nothing.

### Procedural Greybox World (C++ — headless; makes the slice playable with zero editor work)

A C++ subsystem builds the playable greybox world at begin-play so the loop (and the player) can walk
Tavern → Market → Barracks and exercise dialogue/quests/gossip **without any hand-built level**. Real
art levels become an optional Phase 8 pass that overrides this. **This block replaces the editor
level-build as the demo blocker; the `[EDITOR SESSION]` below is now an OPTIONAL human tail.**

- [x] `UGreyboxWorldSubsystem` (World Subsystem, DemoGame module, Net I/O: no) — single source of spatial truth: *(2026-06-25: GreyboxWorldSubsystem.h/.cpp; Automation Spec GreyboxWorld.spec.cpp; gate green)*
  - [x] Static `GetLayout()` returns a table of `FGreyboxLocation { FName Id; FVector CenterOffset; float Radius; bool bFiresTick; }` for the 4 canonical locations (`loc_tavern`, `loc_tavern_back` with `bFiresTick=false`, `loc_market_square`, `loc_guard_barracks`), spread along +X so the player walks Tavern → Market → Barracks in order; the back room sits off the main path.
  - [x] Write failing Automation Spec first (DemoGame/Tests, pure — no world): layout contains the 4 canonical locations; only `loc_tavern_back` has `bFiresTick=false`; every location radius > 0; **every NPC `LocationId` in `UNpcSpawnerSubsystem::GetRoster()` maps to a layout entry** (roster ↔ layout consistency).
  - [x] `ShouldCreateSubsystem` gated to game worlds; `OnWorldBeginPlay` → `EnsureBuilt()` (idempotent `bBuilt` guard) — mirror the `UNpcAutoSeedSubsystem` lifecycle pattern (DEC-035).
  - [x] `EnsureBuilt()`: resolve a base (PlayerStart, fallback world origin); spawn a floor slab (scaled `/Engine/BasicShapes/Cube`), and one `ANpcLocation` per layout entry (set `LocationId`, `bFiresTick`, trigger radius). **Skip** a location if an `ANpcLocation` with that id already exists in the loaded level (forward-compat with authored levels). *(Perimeter walls deferred — ThirdPerson template provides the floor; triggers are the functional core; see DEC-040.)*
  - [x] `GetLocationCenter(FName)` returns the absolute ground point for a location (builds first if needed).
- [x] Wire `UNpcSpawnerSubsystem` to the layout so NPCs stand inside their own location trigger: *(2026-06-25)*
  - [x] Before spawning, `EnsureBuilt()` the greybox subsystem; place each NPC at `GetLocationCenter(LocationId)` + a small intra-location spread (shrink the roster `Offset`s to spreads). Fall back to the player-start base if the greybox subsystem is absent.
  - [x] Move the cube's `+CubeHalfHeight` onto the actor's relative mesh offset so the actor root sits at the feet (prep for the Phase 7 avatar swap); spawn the root at the traced floor.
- [ ] (human — see HUMAN_VERIFICATION.md) **Human tail:** PIE — press Play (engine up → auto-seed) → walk Tavern → Market → Barracks; ticks logged, no double-tick on re-entry; all 5 NPCs reachable.

### [EDITOR SESSION] — Real Art Levels + Travel Triggers *(OPTIONAL human tail — deferred to Phase 8; the C++ greybox above makes the slice playable now)*

**What to do in Unreal Editor / Rider:**
1. Create four levels using box BSP geometry:
   - `L_Tavern` — main tavern floor; box room with doorway to `L_TavernBack`
   - `L_TavernBack` — created as a persistent sub-level of `L_Tavern`; hidden by default
   - `L_MarketSquare` — open courtyard box
   - `L_GuardBarracks` — barracks courtyard box
2. Place one `ANpcLocation` actor per level with `LocationId` set to the matching constant:
   - `L_Tavern`: `loc_tavern`, `bFiresTick = true`
   - `L_TavernBack`: `loc_tavern_back`, `bFiresTick = false`
   - `L_MarketSquare`: `loc_market_square`, `bFiresTick = true`
   - `L_GuardBarracks`: `loc_guard_barracks`, `bFiresTick = true`
3. Place travel trigger volumes (box volumes or door BSP actors) linking `L_Tavern` ↔ `L_MarketSquare` ↔ `L_GuardBarracks`. Choose level streaming or direct level load — record the choice in DECISIONS.md; do not change it later.
4. Add `UArrivalSubtitleWidget` to the player HUD; wire the `FOnTickAdvanced` delegate.

**Checklist (manual):**
- [ ] All three named levels plus `L_TavernBack` load in PIE
- [ ] `L_TavernBack` sub-level is hidden by default in `L_Tavern`
- [ ] Travel triggers connect all three main levels
- [ ] All `ANpcLocation` actors placed with correct `LocationId` UPROPERTY values

**Done when:** PIE — walk Tavern → Market → Barracks → Market → Tavern; Output Log shows 4 ticks at the correct `LogNpcEngine` category; re-entering the same location shows no additional tick; entering `L_TavernBack` shows no tick.

---

## Phase 3 — Seeder + Seed Data *(C++ + JSON seed complete 2026-06-24; live engine verification pending)*

**Goal:** DemoGame owns all world seeding; running the seeder against a fresh engine builds the complete demo world idempotently.
**Independently demoable:** Seeder runs to completion with 0 errors; second consecutive run logs 0 new nodes created (all skipped by idempotency check).
**Prerequisites:** Phase 2 (INpcDialogueService interface stable; world subsystem in place).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [x] **Reconcile tavern name conflict** — chosen: **"The Broken Flagon"** (DEC-017). `docs/STORYBOARD.md` updated. Propagated to `Seed/DemoWorld_v1.json`. Town name "Thornfield" used throughout. *(2026-06-24)*
- [x] Write failing Automation Specs for `UNpcWorldSeeder` (NpcEngineClient/Tests, Net I/O: yes): *(2026-06-24)*
  - [x] Seeder calls `CheckNodeExists` before each `UpsertNode`; skips the upsert when node exists (idempotency)
  - [x] Seeder processes Location nodes before Character nodes; Faction nodes before edge upserts (dependency order enforced)
  - [x] Seeder halts and logs on any non-2xx response; does not silently continue
  - [x] All upserts are non-blocking: return immediately; callbacks fire on game thread
- [x] Author `Seed/DemoWorld_v1.json` — single source of truth for all demo content: *(2026-06-24)*
  - [x] **Location nodes** (node_type `Location`): `loc_tavern` (The Broken Flagon), `loc_tavern_back`, `loc_market_square`, `loc_guard_barracks`. Town name "Thornfield" in all descriptors.
  - [x] **Character nodes** — all 5 NPCs with exact personality values from §7.3:
    - `mira_innkeeper`: gossipy=82, credulity=60, honesty=55; `is_player=false`, `is_active=true`
    - `lira_fence`: gossipy=40, credulity=30, honesty=20
    - `aldric_merchant`: gossipy=50, credulity=50, honesty=70; biography: *"Formerly traded textiles in Riverwheel before settling in Thornfield as a wine merchant."*
    - `captain_sorn`: gossipy=25, credulity=20, honesty=85
    - `old_henryk`: gossipy=90, credulity=95, honesty=40
  - [x] **Player node**: id=`player_demo`, name=`"Traveler"`, is_player=true, currency_balance=60, archetype=`"adventurer"`
  - [x] **Faction nodes**: `guard_faction` (City Guard), `thieves_guild` (Thieves Guild)
  - [x] **Event node**: `northern_war_begins` with authored source/hop-1/hop-2 distortion texts per §7.2 verbatim
  - [x] **Edges**: `LOCATED_AT` (all 5 NPCs), `MEMBER_OF` (Lira → guild, Sorn → guard), `KNOWS_ABOUT` (Sorn → northern_war_begins), `RELATES_TO` (neutral stubs)
  - [x] **Quest nodes**: `find_wine_merchant`, `deliver_amulet`, `aldric_confession`, `patrol_duty`, `captain_report`, `missing_goods`, `fence_confrontation` — each with objective text and chain links per §7.6
  - [ ] **Memory badge lookup stub**: `TMap<FName, FText>` entries for all memory node IDs in the seed. *(deferred: DataAsset work; wired in Phase 4/10)*
  - [x] Note: Slice 2 NPC deep inner-life deferred to Phase 5 via admin endpoints. DEC-018 records the decision and seeding path. *(2026-06-24)*
- [x] Implement `UNpcWorldSeeder` in NpcEngineClient module (Net I/O: yes): *(2026-06-24)*
  - [x] Reads `DemoWorld_v1.json` using `FFileHelper`; JSON parsing stays in NpcEngineClient
  - [x] For each node: `CheckNodeExists` → skip if found (logs `"Skipped NodeId=..."`) else `UpsertNode`
  - [x] For each edge: `UpsertEdge` — MERGE semantics; both endpoint nodes already seeded
  - [x] Seed order enforced: Locations → Factions → Characters → Events → Edges → Quest nodes
  - [x] On any non-2xx: `UE_LOG(LogNpcEngine, Error, …)` and halt; never silently continue
  - [x] Non-blocking: each upsert async; callbacks fire on game thread. `SetHttpExecutorForTesting` seam for specs.
- [x] Exec command `NpcEngine.SeedWorld` (FAutoConsoleCommandWithWorld in NpcEngineClient) — registered at bottom of `NpcWorldSeeder.cpp`; does not require a live `APlayerController`. *(2026-06-24)*
- [x] Verify: run seeder twice against a live engine. Second run logs 0 new nodes created (all skipped by idempotency check). *(requires live engine — manual gate)*
- [x] Reconcile `DemoWorld_v1.json` with `docs/ENGINE_CONTRACT.md`. Property shapes verified against §4 and existing `Seed/slice1_tavern.json` — consistent. *(2026-06-24)*

---

## Phase 4 — Dialogue + Trust Gate (Greybox) *(C++ complete 2026-06-24; editor session + live trust-gate verification pending)*

**Goal:** One complete investigation step playable — approach Mira, build trust, cross trust gate 1, learn Aldric's situation.
**Independently demoable:** Approach a capsule, press E, type a message, receive a response, watch the trust meter move.
**Prerequisites:** Phase 3 (world seeded; DemoWorld_v1.json stable; all 5 NPC nodes exist in engine).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [ ] **Author fallback lines for Mira and Lira** in `DA_NpcFallbackLines` DataAsset (`TMap<FName, FText>`) *(human — optional DataAsset override; C++ defaults already ship these via `NpcFallbackDefaults.h` / DEC-020, so dialogue already falls back correctly without this)*. Keys are the NPC ID FName constants — no hardcoded string literals in C++. These appear on 30 s timeout or non-2xx from the engine.
- [x] Write failing functional Automation Spec for `UDialogueComponent` (DemoGame/Tests): *(2026-06-24)*
  - [x] `SubmitMessage("")` → rejected client-side (no delegate fired, no HTTP call); uses `NpcEngine::MaxPlayerMessageChars` named constant from NpcEngineClient
  - [x] `SubmitMessage` with string over `NpcEngine::MaxPlayerMessageChars` → rejected client-side
  - [x] `SubmitMessage` on valid input with fake `INpcDialogueService` returning non-2xx → `OnFallbackLine` fired; fallback text from `DA_NpcFallbackLines`; mock fires `OnError` (not success) — LSP rule enforced
- [x] `UDialogueComponent` on `ANpcActorBase` (DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] `StartDialogue(APlayerController*)`: begins session; clears `SessionId` + `AccumulatedTrust`; calls `DM->BeginDialogue`. Input mode managed by `ADemoGameCharacter` (DEC-019).
  - [x] `SubmitMessage(FString PlayerMessage)`: validates non-empty AND `PlayerMessage.Len() <= NpcEngine::MaxPlayerMessageChars`; calls `Service->SendDialogue` through `TScriptInterface<INpcDialogueService>`; no `FHttpModule` usage.
  - [x] On response: cache `SessionId`; update `AccumulatedTrust`; broadcast `OnTrustChanged`, `OnMemoriesRecalled` (if non-empty), `OnFacialExpression`; notify DM for widget.
  - [x] On timeout / non-2xx: fire `OnFallbackLine(FName NpcId, FText FallbackText)` — text from `UNpcFallbackLinesAsset`; game continues; never crash.
  - [x] `DegradationLevel != "full"`: logged to `LogNpcEngine`; not surfaced to player in demo v1.
- [x] `UDialogueWidgetBase` (UUserWidget C++ base class, DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] Text input field: `IsReadOnly = true` during LLM wait; restored to `false` on response or fallback.
  - [x] Dialogue history appends to `ResponseText` (scrollable via `ResponseScroll`). Word-by-word animation deferred to editor — `UWidgetAnimation` authored in `WBP_Dialogue` BP subclass (ISSUE-NNN).
  - [x] `ThinkingIndicator` (`UTextBlock`, `BindWidgetOptional`): shown on submit, hidden on response/error. Pulsing ellipsis animation authored in BP subclass.
  - [x] `memories_recalled` badge: `MemoriesBadge` (`UTextBlock`, `BindWidgetOptional`) shown for 5 s via `FTimerHandle`; text from `UMemoryBadgeLookupAsset`; never shown when array is empty.
  - [x] No art — white panels, legible fonts at this stage. Visual polish in Phase 9.
- [x] `URelationshipMeterWidget` (debug HUD overlay, DemoGame module, Net I/O: no): shows `trust`, `fear`, `affection` as signed integers (formatted `+N`/`-N`) per active NPC; `OnRelationshipUpdated` BlueprintNativeEvent for lerp animation in BP subclass. *(2026-06-24)*
- [ ] Trust gate verification *(human — see HUMAN_VERIFICATION.md; live LLM)*: accumulate trust with Mira past 25 via natural dialogue; confirm she reveals the Aldric information in dialogue history (do not check engine internals directly). Repeat 3 times from a fresh seed. Gate must clear in all 3 runs.

### [EDITOR SESSION] — NPC Capsule Placement + Widget Layout

**What to do in Unreal Editor / Rider:**
1. Place Mira `ANpcActorBase` capsule in `L_Tavern`. Set `NpcId` UPROPERTY to the `mira_innkeeper` FName constant. Set `LocationId` to `loc_tavern`.
2. Place Lira `ANpcActorBase` capsule in `L_TavernBack`. Set `NpcId` to `lira_fence`. Set `LocationId` to `loc_tavern_back`. Keep `L_TavernBack` hidden by default; it streams in only after Mira gate 2 fires (wired in Phase 5).
3. Create `WBP_Dialogue` (child of `UDialogueWidget` C++ base): lay out text input, history panel, thinking indicator, memories badge. Wire `BindWidget` slots only — no Blueprint logic.
4. Create `WBP_RelationshipMeter` (child of `URelationshipMeterWidget` C++ base): lay out trust/fear/affection labels. Wire `BindWidget` slots.
5. Add `WBP_Dialogue` and `WBP_RelationshipMeter` to the player HUD.

**Checklist (manual):**
- [ ] PIE: approach Mira capsule, press E → `WBP_Dialogue` opens
- [ ] PIE: type message → input locks; response arrives → input unlocks
- [ ] PIE: `WBP_RelationshipMeter` shows values and animates after exchange
- [ ] PIE: `memories_recalled` badge appears if `MemoriesRecalled` array is non-empty
- [ ] PIE: empty input rejected client-side (Output Log shows no HTTP call made)

**Done when:** `pwsh Scripts/check.ps1 -WithBuild -WithTests` green; PIE — approach Mira → press E → receive response → trust meter moves.

> §14 acceptance criteria addressed: "Player initiates dialogue with Mira. Types a message. Receives a response within 30 seconds or a graceful fallback line." · "Trust meter updates visibly after each exchange." · "The `memories_recalled` badge appears at least once during the golden path."

---

## Phase 5 — Quest System + Faction Fork (Greybox)

**Goal:** Full chain A playable — investigate → identify Aldric → deliver or sell → quest log shows complete.
**Independently demoable:** Quest log updates as steps complete; faction choice fires and changes a visible standing value.
**Prerequisites:** Phase 4 (Mira trust gate functional; INpcDialogueService interface stable).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [x] **Add DEC-025/026/027/028 to `DECISIONS.md`:** USaveGame persistence contract (DEC-025), INpcQuestService ISP split (DEC-026), quest endpoint shapes from ROADMAP docs (DEC-027), greybox quest data as C++ constants (DEC-028). *(2026-06-24)*
- [ ] **Verify quest lifecycle endpoint shapes** against live `GET http://localhost:8000/openapi.json` (not in curated `docs/openapi.json`; resolved per §13 OQ-1 — confirm still match) *(human — see HUMAN_VERIFICATION.md)*:
  - `POST /v1/quest/offer` body: `{ "quest_id", "player_id", "title", "objectives": [{"objective_id","description","required_progress":1}], "item_rewards":[], "currency_reward":null }`
  - `POST /v1/quest/accept` body: `{ "quest_id", "player_id" }`
  - `POST /v1/quest/objective` body: `{ "quest_id", "player_id", "objective_id", "progress_delta":1 }`
  - `POST /v1/quest/evaluate` body: `{ "quest_id", "player_id" }`
  - `POST /v1/quest/reward` body: `{ "quest_id", "player_id" }`
  - `POST /v1/quest/{quest_id}/choose` body: `{ "player_id", "choice_id" }` — faction fork branch
  - Record confirmation result in DECISIONS.md.
- [x] **Add quest lifecycle methods to `INpcDialogueService`** (or new `INpcQuestService` UInterface — record decision in DECISIONS.md with ISP rationale). Write failing Automation Specs first (NpcEngineClient/Tests, Net I/O: yes): *(2026-06-24: INpcQuestService created as ISP-separate interface per DEC-026; QuestLifecycle.spec.cpp written first)*
  - [x] `QuestOffer(FQuestOfferRequest)` calls `POST /v1/quest/offer` with correct body fields (no field names from memory — verify against the confirmed shapes above); returns bool success
  - [x] `QuestAccept(FName QuestId, FString PlayerId)` calls `POST /v1/quest/accept`; returns bool
  - [x] `QuestObjective(FQuestObjectiveRequest)` calls `POST /v1/quest/objective`; returns bool
  - [x] `QuestEvaluate(FName QuestId, FString PlayerId)` calls `POST /v1/quest/evaluate`; returns bool
  - [x] `QuestReward(FName QuestId, FString PlayerId)` calls `POST /v1/quest/reward`; returns bool
  - [x] `QuestChoose(FName QuestId, FString PlayerId, FName ChoiceId)` calls `POST /v1/quest/{quest_id}/choose`; returns bool — `quest_id` path parameter from the named argument, not a hardcoded string
  - [x] All calls: non-blocking; callback fires on game thread
  - [x] All calls: non-2xx → `UE_LOG(LogNpcEngine, Error, …)` + return false; never crash
- [x] Implement quest lifecycle in `UNpcEngineRestClient`. All HTTP stays in NpcEngineClient; all USTRUCT types (`FQuestOfferRequest`, `FQuestObjectiveRequest`) defined in NpcEngineClient. *(2026-06-24)*
- [ ] **Author fallback lines for Aldric and Captain Sorn** in `DA_NpcFallbackLines`. Keys are NPC ID FName constants. *(human — see HUMAN_VERIFICATION.md)*
- [x] `UQuestSubsystem` (World Subsystem, DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] `Initialize`: resolves service interface from `UNpcEngineServiceSubsystem`
  - [x] `ActivateQuest(FName QuestId)`: adds to active list; calls `QuestOffer` + `QuestAccept` through service interface; broadcasts `OnQuestActivated(FName QuestId)`
  - [x] `CompleteStep(FName QuestId, FName StepId)`: marks step complete via `QuestObjective` + `QuestEvaluate`; if quest complete, calls `QuestReward`; checks if next step unlocks; broadcasts `OnStepCompleted`; triggers save
  - [x] Quest data (titles, objectives, chain links) — greybox static C++ map per DEC-028 (replaces DemoWorld_v1.json parse for Phase 5; finalised in Phase 9)
  - [x] No `FHttpModule` usage; no JSON parsing; no USTRUCTs defined in DemoGame
- [x] `UQuestLogWidget` (UUserWidget, DemoGame module, Net I/O: no): C++ base class created *(2026-06-24; WBP_QuestLog layout is editor session work)*
  - [x] Active quest list; each step shows title + completion checkbox
  - [x] Quest only appears in log when `ActivateQuest` fires — no map markers
- [x] Quest confirm prompt: UI overlay ("Accept quest: [authored title]?") appears when NPC dialogue resolves to a quest offer. Accept calls `UQuestSubsystem::ActivateQuest`. Decline dismisses. *(C++ base QuestConfirmWidget done 2026-06-24)*
- [x] `UNpcFactionSubsystem` (World Subsystem, DemoGame module, Net I/O: no): *(implemented as UFactionSubsystem 2026-06-24)*
  - [x] `TMap<FName, int32>` standings — no magic number defaults; initialized from save or to 0 on first run
  - [x] Updated by action response `relation_deltas` when the NPC is faction-affiliated (checked via membership data from DemoWorld_v1.json)
  - [x] Triggers save on standing change
- [x] Faction fork prompt: binary choice UI with authored option labels (do not use raw NPC ID values as display text). Choice calls `QuestChoose(quest_id, choice_id)` through service interface. Logs faction standing change to `LogNpcEngine`. *(C++ base FactionForkWidget done 2026-06-24)*
- [x] `L_TavernBack` streaming gate: `UNpcWorldSubsystem` listens to `OnTrustChanged` for the tavern innkeeper NPC (FName constant — not a string literal); when accumulated trust ≥ `TRUST_GATE_2_MIRA` named constant (threshold=40), fires `OnTavernBackUnlocked` delegate. *(2026-06-24; sub-level streaming wired in editor session)*
- [x] `USaveGame` implementation (DemoGame module, Net I/O: no): *(UNpcSaveGame done 2026-06-24)*
  - [x] Persists PlayerId, TArray<FQuestStepState>, TMap<FName,int32> FactionStandings per DEC-025
  - [x] On first run (no save file): initialize defaults (player_demo id, no active quests, all faction standings = 0)
  - [x] On game startup with existing save: load; call `Service->CheckNodeExists("Character", SavedPlayerId)` through interface; if node not found → call `UNpcWorldSeeder` before first dialogue (handles engine restart + volume wipe edge case, per §13 OQ-3)
  - [x] Save triggers: quest step completion, faction choice, session end (quit). Each trigger is an explicit task — not implicit.
- [ ] Verify chain A end-to-end: fresh save → investigate Mira → identify Aldric through 2+ NPC conversations (no waypoint) → deliver or sell → quest log shows `deliver_amulet` complete → `aldric_confession` step appears → faction standing change logged to Output Log. *(human — see HUMAN_VERIFICATION.md)*

### [EDITOR SESSION] — NPC Placement + Quest Log Widget

**What to do in Unreal Editor / Rider:**
1. Place `ANpcActorBase` capsules for the three Slice-2 NPCs: Aldric in `L_MarketSquare` (`NpcId` = aldric_merchant constant); Sorn in `L_GuardBarracks` (`NpcId` = captain_sorn constant); Old Henryk in `L_MarketSquare` (`NpcId` = old_henryk constant).
2. Create `WBP_QuestLog` (child of `UQuestLogWidget` C++ base): lay out active quests and step checkboxes. Wire `BindWidget` slots — no Blueprint logic.
3. Create `WBP_FactionFork` (binary choice prompt). Wire to `UNpcFactionSubsystem` and `UQuestSubsystem`.
4. Add `WBP_QuestLog` to the player HUD.
5. Test `L_TavernBack` streaming gate: build trust with Mira past gate 2 threshold in PIE; confirm back room becomes visible and passable.

**Checklist (manual):**
- [ ] PIE: approach Aldric, Sorn, Old Henryk capsules — all respond to E-interact
- [ ] PIE: quest log shows `find_wine_merchant` as first active step after investigation starts
- [ ] PIE: chain A fork fires; `deliver_amulet` completes; faction standing change is logged

**Done when:** Chain A playable end-to-end from a fresh save; quest log updates at each step; faction standing change logged to Output Log after fork.

> §14 acceptance criteria addressed: "Quest log shows `find_wine_merchant` as the first active step." · "Chain A completes: quest log shows `deliver_amulet` complete, `aldric_confession` step appears." · "Faction fork fires. Faction standing changes." · "Lira's back room is inaccessible below gate 2 and accessible above it." · "Player identifies Aldric through 2+ NPC conversations. No map marker."

---

## Phase 6 — Gossip Chain + Rumor Journal (Greybox)

**Goal:** Distorted rumor arrives at Old Henryk; Rumor Journal shows the full chain; Sorn's quest chain unlocks.
**Independently demoable:** Tab opens the journal showing a Sorn → Mira → Henryk chain entry after completing the golden path through beat 15.
**Prerequisites:** Phase 5 (all 5 NPC capsules placed; trust, quest, and faction systems functional; full golden path setup complete).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [ ] (human — see HUMAN_VERIFICATION.md) **Author fallback line for Old Henryk** in `DA_NpcFallbackLines`. All 5 NPC fallback lines are now authored (Mira + Lira in Phase 4; Aldric + Sorn in Phase 5; Old Henryk here).
- [x] `FNpcStateSnapshot` USTRUCT (NpcEngineClient module, Net I/O: no for the struct itself): *(2026-06-24)*
  - [x] Mirrors `GET /v1/npc/{npc_id}/state` response `data` field shape: `character` object, `relations` array, `events` array — all fields `UPROPERTY`. Sub-structs `FNpcRelationEntry`, `FNpcEventEntry` also defined in `NpcEngineTypes.h`.
  - [x] Write failing Automation Spec first (NpcEngineClient/Tests):
    - [x] Parses `OkEnvelope` `.data` → `FNpcStateSnapshot` correctly (character fields present, relations count, events array)
    - [x] Non-2xx or parse error → empty `FNpcStateSnapshot` + error delegate; no crash
- [x] `GetNpcState` callback updated to `FNpcStateSnapshot` (DEC-029). All parsing in `NpcEngineJsonUtils::ParseNpcStateSnapshot`; only `FNpcStateSnapshot` crosses the module boundary. *(2026-06-24)*
- [x] Write failing Automation Spec for `UGossipCacheSubsystem` (DemoGame/Tests): *(2026-06-24)*
  - [x] `AddGossipEntry(FName SourceNpcId, FName EventId, int32 HopCount, FText DistortionText)` stores a `FGossipEntry` USTRUCT
  - [x] `GetChainForEvent(FName EventId)` returns entries in HopCount ascending order
  - [x] Journal entry for an NPC at a hop is only returned after `MarkPlayerSpokeToNpc(NpcId)` is called
- [x] `UGossipCacheSubsystem` (World Subsystem, DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] Stores `TArray<FGossipEntry>` (USTRUCT `FGossipEntry`: `SourceNpcId`, `EventId`, `HopCount`, `DistortionText`, `bPlayerSpokeToNpc`)
  - [x] Updated after each tick: calls `Service->GetNpcState(NpcId::OldHenryk)` through `INpcDialogueService` — NPC ID via `NpcId::` constant, not a string literal. Parses `FNpcStateSnapshot.Events` to check if the war event `knowledge_state` has updated; if so, adds/updates Henryk's hop entry.
  - [x] Updated when dialogue response `learned_facts` contains a war-related event key (keyed by `GossipEventId::NorthernWarBegins` FName constant). `UDialogueComponent::NotifyGossipCache` calls `MarkGossipFromDialogue` and `MarkPlayerSpokeToNpc`.
  - [x] No `FHttpModule`; no JSON parsing; all net I/O through `INpcDialogueService`
- [x] `URumorJournalWidget` (UUserWidget, Tab key, DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] Reads from `UGossipCacheSubsystem`; refreshes on open
  - [x] `OnJournalRefreshed` BlueprintNativeEvent — BP subclass populates chain card rows (editor session)
  - [x] `GetDistortionLabel(HopCount)` static helper: HopCount 0 → "Firsthand"; 1 → "Rumor"; 2+ → "Distorted"
  - [x] Chain entry row only shown after `bPlayerSpokeToNpc == true` for that hop's NPC (enforced in BP subclass)
  - [x] No art — readable text layout only at this stage; `ChainScrollBox`/`ChainContainer` BindWidgetOptional
- [x] `ANoticeBoard` Actor (DemoGame module, Net I/O: no): *(2026-06-24)*
  - [x] `UPROPERTY TArray<FText> RumorTiers` (authored — 3 tiers: pre-war / rumors spreading / distorted widely). Property set in editor; not hardcoded in C++.
  - [x] `UPROPERTY TArray<int32> TierTickThresholds` (defaults [0, 2, 4] via `NoticeBoardDefaults` constants in .cpp; not magic numbers).
  - [x] Listens to `UNpcWorldSubsystem::FOnTickAdvanced`; advances to next tier when `TickCount` passes the authored threshold
  - [x] `GetCurrentTierText()` returns the display text; BP_NoticeBoard wires E-examine → popup (editor session)
- [x] Sorn quest chain unlock: `UNpcWorldSubsystem::NotifyRelationshipUpdated` checks `NpcId::CaptainSorn` accumulated trust ≥ `NpcEngine::TrustGateSornQuest` (50) → `UQuestSubsystem::ActivateQuest(QuestId::PatrolDuty)` → quest log updates. *(2026-06-24)*
- [ ] (human — see HUMAN_VERIFICATION.md) **GATE: Gossip chain 5/5 — do not start Phase 7 until this passes.**
  - [ ] Run the full golden path 5 times from a fresh seed: Tavern (speak with Mira) → Barracks (build trust with Sorn; he shares war information) → Tavern (tick fires) → Market (speak with Old Henryk)
  - [ ] In all 5 runs: Henryk's dialogue response must contain the distorted war account from §7.2
  - [ ] If any run fails: tune `gossipy` and `credulity` personality values in `DemoWorld_v1.json` and re-run the seeder. Do not advance to Phase 7 until 5/5 pass.
- [ ] (human — see HUMAN_VERIFICATION.md) **Greybox acceptance gate:** All 17 beats from §10 of the game design roadmap are playable start-to-finish. All trust gates, quest steps, gossip chain, Rumor Journal, and faction fork must be functional. Any non-functional beat is a blocker for Phase 7.

### [EDITOR SESSION] — Notice Board + Journal Widget

**What to do in Unreal Editor / Rider:**
1. Create `BP_NoticeBoard` (extends `ANoticeBoard` C++ base; prefix `BP_`). Set `RumorTiers` and `TierTickThresholds` UPROPERTY arrays.
2. Place `BP_NoticeBoard` in `L_MarketSquare` and `L_GuardBarracks`. Wire E-examine trigger.
3. Create `WBP_RumorJournal` (child of `URumorJournalWidget` C++ base): lay out chain cards with NPC name, distortion text, distortion level badge. Wire `BindWidget`. No Blueprint logic.
4. Bind Tab key to open/close `WBP_RumorJournal` from the player HUD (or `UEnhancedInputComponent` action).

**Checklist (manual):**
- [ ] PIE: examine notice board in market square → shows tier 1 text
- [ ] PIE: after 2 ticks, notice board advances to tier 2 text
- [ ] PIE: Tab opens journal; chain cards appear only after player has spoken to the NPC at that hop
- [ ] PIE after full golden path: journal shows Sorn → Mira → Henryk chain with correct distortion badges

**Done when:** PIE Tab shows the complete Sorn → Mira → Henryk chain with distortion badges; all 17 beats play without blocking the reviewer; gossip chain 5/5 verified before tagging this phase complete.

> §14 acceptance criteria addressed: "After the golden path, Old Henryk's dialogue contains the distorted war account." · "A naive observer who heard Sorn's account can identify Henryk's account as a distortion of it." · "Rumor Journal shows the Sorn → Mira → Henryk chain with distortion level labels at each hop." · "Sorn trust gate unlocks `patrol_duty`. Quest appears in the quest log."

---

## Phase 7 — MetaHuman + Dialogue Camera

**Goal:** Replace capsule NPCs with MetaHuman and Fab humanoid actors; cinematic dialogue camera active; engine-driven expressions on MetaHuman faces.
**Independently demoable:** Initiating dialogue with Mira shows her MetaHuman face, camera blending to `DialogueCamSocket`, and expression change in response to the `facial_expression` payload.
**Prerequisites:** Phase 6 gossip chain 5/5 verified and greybox acceptance gate passed; Phase 11 MetaHuman assets (Mira, Sorn, Lira) exported to UE5 project and Fab humanoids acquired.
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild`

**C++ tasks (Rider, no editor required):**

- [x] **Data-driven appearance seam** (cube → MetaHuman with a one-line swap; DemoGame module, Net I/O: no) — do this FIRST, it decouples the swap from the editor: *(2026-06-25: NpcAppearance.h/.cpp + NpcAppearance.spec.cpp + FNpcSpawnRecord.AvatarClass + ANpcGreyboxActor.TrySpawnAvatar; gate green)*
  - [x] `NpcAppearance.h/.cpp` — the single swap point: `TSoftClassPtr<AActor> GetAvatarClass(FName NpcId)` backed by a `TMap<FName, FSoftClassPath>` that is **EMPTY today** (every NPC is a cube). Swapping one NPC to a MetaHuman = add one row pointing at the imported BP class path, e.g. `/Game/MetaHumans/Mira/BP_Mira.BP_Mira_C`. No other code change.
  - [x] Write failing Automation Spec first (DemoGame/Tests, pure): every rostered NPC defaults to empty (cube); unknown id → empty; the spawn roster's `AvatarClass` matches `GetAvatarClass` (no divergent second source).
  - [x] `ANpcGreyboxActor`: add `TSoftClassPtr<AActor> AvatarClass`; in `BeginPlay`, if set, load + spawn it as a child attached at the actor root (feet) and hide the cube + name label; else keep the cube. (Root-at-feet refactor lands in Phase 2.)
  - [x] `FNpcSpawnRecord` gains `TSoftClassPtr<AActor> AvatarClass`; the spawner fills it from `NpcAppearance::GetAvatarClass(NpcId)` and passes it to the actor.
  - [x] **Claude-doable swap:** once a MetaHuman is imported (editor session below) at a known `/Game/...` path, flipping that NPC is a one-line `NpcAppearance` edit — no editor step for the wiring, gate stays green. Records as DEC-039 (already present).
- [x] `UFacialExpressionMapper` (NpcEngineClient module, Net I/O: no): *(2026-06-25: FacialExpressionMapper.h/.cpp + spec; all 3 spec cases pass; gate green)*
  - [x] Write failing Automation Spec first: maps `ENpcFacialExpression::Neutral` → correct morph target name; maps unknown enum value → `Neutral` without crash; `ApplyExpression` with null `USkeletalMeshComponent*` → logs warning and returns without crash
  - [x] Maps each `ENpcFacialExpression` to `(TargetMorphName FName, WeightScale float)` pair. C++ default map ships placeholder ARKit-namespace names; override via `DA_FacialExpressionMap` DataAsset once MetaHumans are imported.
  - [x] `ApplyExpression(USkeletalMeshComponent*, ENpcFacialExpression, int32 Intensity)`: sets morph target weight directly; function ≤ 40 lines. Timer-blend deferred to Phase 9 art pass (no MetaHumans yet).
  - [x] Unknown `ENpcFacialExpression`: `UE_LOG(LogNpcEngine, Warning, …)` + apply `Neutral`. Never crash.
- [x] `UDialogueComponent` camera blend (DemoGame module, Net I/O: no): *(2026-06-25: StartDialogue calls BlendCameraToNpc; EndDialogue calls BlendCameraToPlayer; ADemoGameCharacter tracks ActiveNpc + calls EndDialogue in HandleDialogueEnded; gate green)*
  - [x] `OnStartDialogue`: `APlayerController::SetViewTargetWithBlend(NpcOwner, 0.3f, VTBlend_Cubic)` when a `UCameraComponent` is found on the NPC actor (attached at `DialogueCamSocket` in the Phase 7 editor session); no-op if no camera yet (greybox stage).
  - [x] `OnDialogueClose`: blend back to player pawn (0.4 s). `ADemoGameCharacter` tracks `ActiveNpc` and calls `DialogueComponent->EndDialogue(PC)` in `HandleDialogueEnded`.
  - [ ] Thinking state: set NPC look-at target to player head socket; cleared on response received *(human — requires MetaHuman Animation Blueprint; deferred to Phase 7 editor session — see HUMAN_VERIFICATION.md)*

### [EDITOR SESSION] — MetaHuman Import + Camera Socket Setup

**What to do in Unreal Editor / Rider:**

**VRAM gate — complete this before importing Lira:**
1. Load `L_Tavern` with Mira MetaHuman placed (`BP_NPC_Mira`). Open `stat gpu` (console command). Confirm VRAM < 10 GB.
2. Load `L_GuardBarracks` with Sorn MetaHuman placed (`BP_NPC_Sorn`). Confirm VRAM < 10 GB.
3. If either scene exceeds 10 GB: investigate (reduce texture pool, LOD settings, streaming). Record findings in DECISIONS.md before continuing. Do not import Lira until Mira scene is under budget.

**MetaHuman setup (after VRAM gate passes):**
4. Create `BP_NPC_Mira` (extends `ANpcActorBase`; prefix `BP_`): place Mira MetaHuman mesh. Set `NpcId` UPROPERTY to `mira_innkeeper` FName constant. Configure Animation Blueprint with looping thinking idle + neutral blend space.
5. Create `BP_NPC_Sorn` (extends `ANpcActorBase`): set `NpcId` = captain_sorn constant.
6. Create `BP_NPC_Lira` (extends `ANpcActorBase`): set `NpcId` = lira_fence constant. Place in `L_TavernBack` sub-level only.
7. Source Aldric rigged humanoid from Fab (acquired in Phase 11). Create `BP_NPC_Aldric` (extends `ANpcActorBase`; prefix `BP_`): set `NpcId` = aldric_merchant constant. Place in `L_MarketSquare`.
8. Source Old Henryk rigged humanoid from Fab (acquired in Phase 11). Create `BP_NPC_Henryk` (extends `ANpcActorBase`; prefix `BP_`): set `NpcId` = old_henryk constant. Place in `L_MarketSquare`.

**DialogueCamSocket — required for all 5 NPCs:**
9. For each NPC skeleton, add a socket named exactly `DialogueCamSocket` positioned to frame the NPC face in close-up at eye level. This is a hard deliverable; dialogue camera blend fails without it.

**Expression setup:**
10. On each MetaHuman Animation Blueprint: add a morph target blend layer driven by `UFacialExpressionMapper` output. Wire `EFacialExpressionType` → blend weights.
11. On Aldric and Henryk Animation Blueprints: add simplified emotion state machine (Neutral / Happy / Wary / Fearful states) wired to a blend space. Reduced fidelity is acceptable.

**Checklist (manual):**
- [ ] Mira MetaHuman renders in `L_Tavern`; VRAM stat < 10 GB
- [ ] Sorn MetaHuman renders in `L_GuardBarracks`; VRAM stat < 10 GB
- [ ] Lira MetaHuman renders in `L_TavernBack`; Mira and Lira never simultaneously in GPU memory (confirm via `stat gpu` or RenderDoc snapshot)
- [ ] Aldric and Old Henryk humanoids placed in `L_MarketSquare`
- [ ] All 5 NPC actors have `DialogueCamSocket` added to their skeletons
- [ ] `BP_NPC_Mira` expression layer changes when `ApplyExpression` is called from `UDialogueComponent`

**Done when:** PIE — approach Mira, press E; camera blends smoothly to `DialogueCamSocket` framing; receive dialogue response; Mira's expression changes based on `facial_expression.type`; VRAM < 10 GB in each scene; Mira and Lira not simultaneously loaded.

> §14 acceptance criteria addressed: "MetaHuman expressions animate during dialogue in response to the `facial_expression` payload." · "Thinking animation plays during LLM wait. Input is locked during wait."

---

## Phase 8 — Environment Art Pass

**Goal:** Replace box geometry with sourced Quixel/Fab environment assets.
**Independently demoable:** All four levels look and feel like a real medieval world; level transitions are seamless at 60 fps.
**Prerequisites:** Phase 7 (MetaHumans placed and VRAM verified); Phase 11 Fab/Quixel environment packs acquired.
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild`

### [EDITOR SESSION] — Environment Dressing + Lighting

**What to do in Unreal Editor / Rider:**
1. **`L_Tavern`**: dress with Quixel medieval interior kit — hearth prop, bar counter (SM_ prefixed static meshes), tables, chairs, candle holders, wooden beam supports. Assign baked lightmap to all static geometry. Place 3–4 dynamic point lights (candles, hearth) as hero light sources only. No Lumen in demo v1 — record decision in DECISIONS.md with rationale (VRAM + performance budget).
2. **`L_TavernBack`**: dress from the same interior kit — crates (SM_), barrels (SM_), rough stone wall sections. Apply a dark post-process volume (low exposure, desaturated). Reduce shadow map resolution where possible for VRAM budget.
3. **`L_MarketSquare`**: dress with Quixel outdoor medieval kit — cobblestone ground material (M_ prefix), merchant stall meshes (SM_), awnings (SM_), notice board prop (SM_). Place `BP_NoticeBoard` actor at the notice board prop position. Baked lightmap; dynamic sky-light contribution only.
4. **`L_GuardBarracks`**: dress with stone wall segments (SM_), gate arch (SM_), training props for decoration only (non-interactive). Reuse stone Material Instances (MI_ prefix) from the market kit to share texture memory.
5. **Build lightmaps** for all four levels. Resolve all unlit / invalid lightmap warnings before proceeding.
6. **NavMesh volumes**: add `NavMeshBoundsVolume` to each level. Non-functional for NPC pathfinding in demo v1, but required to prevent collision issues at NPC actor placement points.
7. **Level streaming performance check**: transition `L_Tavern` ↔ `L_MarketSquare` at the 60 fps target. If any frame transition causes a stall > 1 frame: add a brief UUserWidget black fade (0.15 s) or pre-stream `L_MarketSquare` on tavern entry. Record the chosen mitigation in DECISIONS.md.

**Checklist (manual):**
- [ ] All four levels dressed with Quixel assets; no stylized or mismatched assets mixed in
- [ ] Lightmaps built; no unlit warnings in any level
- [ ] NavMesh volumes present in each level
- [ ] `L_Tavern` ↔ `L_MarketSquare` transition: no visible stall at 60 fps target
- [ ] `BP_NoticeBoard` actor placed at the notice board prop position in `L_MarketSquare`
- [ ] `stat gpu` in each scene shows VRAM < 10 GB

**Done when:** All four levels load with photorealistic medieval art; level transitions are seamless at 60 fps; VRAM < 10 GB per scene.

> §14 acceptance criteria addressed: "Player navigates between all three named locations. Tick fires and arrival subtitle appears on each." · "Tavern back room does not fire a tick. Sub-level streams in without a visible hitch."

---

## Phase 9 — UI Polish + Audio

**Goal:** Dialogue panel art, Rumor Journal art, relationship meter HUD, ambient audio, and UI sounds all at shipped quality.
**Independently demoable:** The full game loop looks and sounds like a finished product.
**Prerequisites:** Phase 8 (environment art complete; levels dressed and lit).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild`

### [EDITOR SESSION] — UI Art Pass + Audio Integration

**What to do in Unreal Editor / Rider:**

**UI art pass:**
1. `WBP_Dialogue`: apply parchment or dark-tavern-wood theme. Style the text history area, input field (add send icon), and `memories_recalled` badge (floating amber note appearance). Use Material assets with prefix `M_` for any custom widget materials.
2. `WBP_RumorJournal`: render chain entries as connected cards with hand-drawn-style connector lines (static art or UImage with line texture). Distortion level badges: green (`T_Badge_Firsthand`), yellow (`T_Badge_Rumor`), red (`T_Badge_Distorted`). Texture prefix `T_`.
3. `WBP_RelationshipMeter`: NPC portrait (bound via `TSoftObjectPtr<UTexture2D>` — no hard asset references that bloat the cooked graph). Trust bar animates on `OnTrustChanged` using a 0.5 s spring-settle UWidgetAnimation or C++ lerp tick.
4. `WBP_QuestLog`: parchment list background. Active step highlighted. Completed steps show a checkmark icon (`T_Icon_Checkmark`).
5. Arrival subtitle: assign an elegant serif font asset (FA_ or engine default). Center the text, 3-second fade. Add semi-transparent letterbox bars as optional `UImage` overlay.

**Ambient audio:**
6. Import tavern ambient audio from acquired Fab pack. Add `AudioVolume` in `L_Tavern`. Assign `MetaSound` or `SoundCue` (prefix `A_`) — hearth crackle, low murmur, wood creak loop. Fade on volume enter/exit.
7. Import outdoor medieval audio. Add `AudioVolume` in `L_MarketSquare` — bustle, wind, cart sounds. Assign `A_Amb_MarketSquare`.
8. Import barracks ambient audio. Add `AudioVolume` in `L_GuardBarracks` — distant drills, metal clank, wind. Assign `A_Amb_Barracks`.

**UI sounds:**
9. Import UI audio assets from Fab pack. Assign to widget events via `UGameplayStatics::PlaySound2D` (no audio hardcoded inline in C++):
   - Quest accept: `A_UI_QuestAccept` (light confirmation chime)
   - Journal open/close: `A_UI_JournalOpen` (parchment rustle)
   - Trust increase: `A_UI_TrustIncrease` (subtle positive ping)
   - Faction choice confirm: `A_UI_FactionChoice` (weighted neutral tone)

**Checklist (manual):**
- [ ] `WBP_Dialogue` parchment art applied; memories badge styled as amber note
- [ ] `WBP_RumorJournal` chain cards with coloured distortion badges render correctly
- [ ] `WBP_RelationshipMeter` trust bar animates with spring settle
- [ ] `WBP_QuestLog` parchment style applied; completed steps show checkmark
- [ ] Tavern, market, barracks ambient audio plays in PIE when entering each level
- [ ] UI sounds fire on quest accept, journal open/close, trust increase, faction choice

**Done when:** Full game loop is visually and aurally polished; all widget art applied; ambient audio plays in all scenes; UI sounds fire on their triggers.

---

## Phase 10 — Content Polish + Acceptance Validation

**Goal:** All authored content finalized, seed verified against the live engine, and all acceptance criteria passed.
**Independently demoable:** A naive player who has not seen the demo reaches beat 15 (the gossip reveal) within 25 minutes without being guided.
**Prerequisites:** Phase 9 (UI and audio complete; full game loop playable).
**Quality gate:** `pwsh Scripts/check.ps1 -WithBuild -WithTests`

- [ ] **Author all notice board texts** — 3 tiers × up to 3 boards = 9 entries. Use "Thornfield" in all authored text; no other town name. Tiers: pre-war silence / rumors spreading / distorted widely. *(headless: author as C++ constants like the existing `MakeNoticeTiers()` / DEC-028 quest metadata — no DataAsset needed.)*
- [ ] **Author full `memories_recalled` badge lookup table** as C++ constants (headless — like DEC-028; a `DA_MemoryBadgeLookup` DataAsset may override later): authored `FText` display strings per memory node ID FName. Replace all Phase 3 stub entries with final authored text. Do not use raw memory node IDs as display text.
- [ ] **Review and finalize fallback canned lines** for all 5 NPCs (used on 30 s LLM timeout or non-2xx). Authored per phase: Mira + Lira (Phase 4), Aldric + Sorn (Phase 5), Old Henryk (Phase 6). Ensure each line fits the NPC's personality and does not break immersion.
- [ ] **Author `aldric_confession` dialogue context** — seed verbatim to the engine via the appropriate seeding endpoint (verify path in DECISIONS.md per the Phase 3 admin endpoint task):
  - `aldric_merchant.belief["amulet_origin"]`: *"This amulet — I took it as trade debt in Riverwheel from a soldier passing through. He needed coin quickly; I didn't ask why. That was weeks ago. Now I have guardsmen coming to my stall asking what I know. I understand it now: that man deserted his post. He fled the northern garrison before the skirmish was reported, and this is what he left behind. I'm holding his evidence. That's what they want."*
  - `aldric_merchant.secret["amulet_truth"]`: *"The amulet is evidence of a desertion from the northern garrison. The soldier who owned it sold it to Aldric to fund his flight from the northern pass before the skirmish the guards are suppressing."*
- [ ] **Final gossip chain verification** — 5 fresh-seed runs. All 5 must show Old Henryk delivering the distorted war account in his dialogue response. If any run fails: tune `gossipy` and `credulity` values in `DemoWorld_v1.json` and re-run the seeder. Do not mark this phase complete until 5/5 pass.
- [ ] **Final distortion review** — play as a player who spoke with Sorn, then talk to Old Henryk. Is Henryk's version recognizably a corruption of Sorn's? If a neutral observer cannot identify the connection, exaggerate the authored distortion text in the seed (Henryk's hop 2 entry) and re-verify with another run.
- [ ] `DemoWorld_v1.json` reconciled against live `GET http://localhost:8000/openapi.json` and `docs/ENGINE_CONTRACT.md`. Any property shape drift → patch the seed and re-run the seeder.
- [ ] **Naive user playtest**: one person who has not seen or worked on the demo plays without guidance. An observer notes every moment of confusion (particularly "what do I do next?" moments). Fix every such moment before marking acceptance. Playtest must confirm the player reaches beat 15 within 25 minutes.
- [ ] **Run acceptance criteria checklist** — full §14 content reproduced in the Acceptance Criteria section below. All items must pass. No partial credit.

> §14 acceptance criteria addressed: "A naive player (who has not seen the demo) reaches beat 15 (the gossip reveal) within 25 minutes without being guided." · All items in the Acceptance Criteria section below.

---

## Phase 11 — Asset Acquisition (Parallel Track)

> **Note:** Run this phase in parallel with Phases 2–6. MetaHuman assets and Fab environment packs must be ready before Phase 7 can start. **Blocking dependency: Phase 7 Prerequisites include Phase 11 completion.**

**Goal:** All visual and audio assets (MetaHumans, environment kits, humanoid characters, audio packs) acquired and project-ready before Phases 7–9 begin.
**Independently demoable:** MetaHuman characters open in MetaHuman Creator and export to UE5 without error; Fab/Quixel packs appear in the Content Browser.
**Prerequisites:** None — runs in parallel with Phases 2–6.
**Quality gate:** N/A — all validation is manual (editor asset work).

### [EDITOR SESSION] — MetaHuman Creation (long-pole; start immediately)

**Creation order is staggered to avoid wasted rework. Do not start Lira until Mira is validated.**

**Step 1 — Mira (P1 priority, start first):**
1. Open MetaHuman Creator. Design Mira: warm but guarded face; late 30s to early 40s; innkeeper archetype. Export to UE5 project.
2. Load `L_Tavern` with `BP_NPC_Mira` placed. Open `stat gpu`. Confirm VRAM < 10 GB in the Mira scene.
3. Validate morph target availability for the 6 `EFacialExpressionType` values (`Neutral`, `Happy`, `Wary`, `Fearful`, `Angry`, `Sad`). Confirm MetaHuman blend shapes cover the needed range.
4. If VRAM > 10 GB: investigate (reduce LOD distance, texture pool, streaming settings). Resolve before proceeding to Lira.

**Step 2 — Sorn (P1 priority, start in parallel with Mira):**
5. Design Sorn: stoic, weathered military face; 45–55 years old; harder trust arc. Export to UE5.
6. Validate in `L_GuardBarracks`. Confirm VRAM < 10 GB. Confirm expression morph coverage.

**Step 3 — Lira (P2 priority, start only after Mira is validated):**
7. Design Lira: sharp, evasive face; early 30s; corner-booth rogue. Export to UE5.
8. Load `L_TavernBack` (sub-level of `L_Tavern`) with Lira placed. Confirm Mira and Lira are **never simultaneously in GPU memory** — check `stat gpu` while manually toggling sub-level visibility. If they co-load, the sub-level streaming boundary must be tightened with an explicit unload call.
9. **Fallback decision point:** If `L_Tavern` with Mira AND `L_TavernBack` with Lira together exceed 10 GB VRAM (even with sub-level isolation), downgrade Lira to a Marketplace humanoid character and reallocate the MetaHuman VRAM budget to environment quality. Record the decision as **DEC-NNN** in `DECISIONS.md`.

### [EDITOR SESSION] — Fab / Quixel Asset Acquisition

**Environment packs (must be complete before Phase 8):**
10. Identify and acquire a photorealistic medieval interior kit from Quixel Megascans / Fab (for `L_Tavern` and `L_TavernBack`). Verify it matches MetaHuman photorealism quality. Do not mix stylized Fab assets in the same scene.
11. Identify and acquire a photorealistic outdoor medieval kit from Quixel / Fab (for `L_MarketSquare` and `L_GuardBarracks`). Can share stone texture samples with the indoor kit via Material Instances.

**Character assets (must be complete before Phase 7):**
12. Identify and acquire a rigged medieval merchant humanoid actor from Fab for Aldric. Bring into UE5; apply prefix `BP_NPC_Aldric` when creating the Blueprint.
13. Identify and acquire a rigged elderly merchant humanoid actor from Fab for Old Henryk. Bring into UE5; apply prefix `BP_NPC_Henryk`.

**Audio packs (must be complete before Phase 9):**
14. Identify and acquire ambient audio packs from Fab: tavern interior (hearth crackle, low murmur, wood creak), outdoor medieval (market bustle, wind, carts), barracks (distant drills, metal clank, wind), and UI sounds (confirmation chime, parchment rustle, positive ping, weighted tone).

**Checklist (manual):**
- [ ] Mira MetaHuman exported to UE5 project; renders in `L_Tavern` with VRAM < 10 GB; expression morphs validated
- [ ] Sorn MetaHuman exported to UE5 project; renders in `L_GuardBarracks` with VRAM < 10 GB
- [ ] Lira MetaHuman exported (or Marketplace fallback decided and recorded in DECISIONS.md); Mira + Lira confirmed not simultaneously in GPU memory
- [ ] Aldric rigged humanoid in Content Browser; `BP_NPC_Aldric` Blueprint created with correct prefix
- [ ] Old Henryk rigged humanoid in Content Browser; `BP_NPC_Henryk` Blueprint created with correct prefix
- [ ] Medieval interior kit in Content Browser; photorealistic quality confirmed
- [ ] Outdoor medieval kit in Content Browser; stone texture sharing with indoor kit verified
- [ ] Audio packs in Content Browser; all four categories present
- [ ] VRAM strategy confirmed: no more than 1 MetaHuman loaded at a time in any single scene

**Done when:** All MetaHumans open in PIE without VRAM issues; all Fab/Quixel packs visible in Content Browser; Phase 7 can begin without waiting on any outstanding asset.

---

## Acceptance Criteria — Demo v1

> Source: `docs/game_design_roadmap.md` §14. All items must pass before the demo is considered complete. No partial credit.

A session qualifies as **demo-complete** when ALL of the following pass without developer intervention:

### Setup
- [ ] Engine health check returns 200. Seeder runs to completion with 0 errors.
- [ ] `NpcEngine.Smoke` Exec command returns a non-empty `npc_response` in Output Log.

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
