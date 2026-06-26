# DemoGame — Comprehensive Codebase Review

## Brief

You are performing a comprehensive code review of **DemoGame**, a UE5.8 third-person C++ RPG demo that
connects to the NPC Engine backend for persistent NPC memory, relationships, emotion, and LLM dialogue
over REST + WebSocket. The project is **demo-complete at Slice-1 scale (5 NPCs, 4 locations)**, and
this review assesses it for expansion to a **real shipped game (~100+ NPCs, 30+ locations)**.

You will write **one file per finding** into `project-harness/reviews/`, named `REV-001.md`,
`REV-002.md`, etc. (sequential, no gaps). Use the template in `project-harness/reviews/_template.md`.

---

## Ground Rules for Findings (read first — these govern everything below)

1. **Read-only.** Do not modify any source file. This pass documents; a later pass fixes.
2. **This repo only.** The NPC Engine backend is a separate repo — do not review it. Review the
   Unreal client (`Source/`, `Seed/`, `Config/`, `docs/`, `Scripts/`).
3. **Evidence or it didn't happen.** Every REV file must quote the actual code at a real `file:line`
   in its Evidence section. If you cannot cite the code, you have not verified the finding — do not
   write it. No finding from memory, assumption, or "this is probably…".
4. **The specifics below are hypotheses, not verdicts.** Where this prompt names a suspected problem
   (e.g. "`GetRoster()` is a static map", "trust may not be saved"), treat it as a *lead to verify*,
   not a confirmed bug. **Expect a meaningful fraction to be non-issues.** If you read the code and it
   is actually fine, do NOT write a file — silently move on. Reporting a non-issue as a finding is a
   failure, not thoroughness.
5. **One finding per root cause.** If the same underlying problem surfaces in three files or under
   three dimensions, write ONE REV file that names all instances — not three. Merge aggressively.
6. **Confidence bar.** Only write a file for something you would defend to a senior Unreal engineer.
   No style nitpicks. A swarm of tiny related nits → one "pattern" finding, or drop them.
7. **Separate "bug now" from "scales badly later."** Use the `horizon` field: `now` (broken/at-risk in
   the current demo), `slice-2` (bites when you add the next chapter), `full-game` (bites at 100+ NPC
   scale). A thing that works fine today but won't scale is a real finding — but it is not P1 unless it
   *blocks* expansion. Distinguish **blocks** (cannot proceed without fixing) from **friction** (you
   can proceed, it's just tedious/risky).
8. **Aim for ~15–35 findings that matter.** Quality over count. A tight, evidenced list the author will
   act on beats an exhaustive list they'll ignore.

---

## Project Architecture (read this before touching any source file)

Two modules. The dependency boundary is strict and must be preserved:

```
Source/DemoGame/          — Game module. Actors, components, subsystems, UMG.
                            NO network I/O. NO JSON parsing. NO contract USTRUCTs.
Source/NpcEngineClient/   — Integration module. HTTP, WS, JSON, contract models, seeding.
                            The ONLY module allowed network I/O.
```

Key rules (violations are bugs, not style issues):
- No `FHttpModule`/raw sockets outside `NpcEngineClient`.
- No `FJsonObject`/`JsonUtilities`/`FJsonSerializer` in `DemoGame`.
- No engine-contract USTRUCTs (API-mirror types) defined outside `NpcEngineClient`.
- No hardcoded `npc_id`, URL, or endpoint-path string literals in gameplay.
- All engine calls async via delegates — never block the game thread.
- Gameplay depends on `UInterface` (`INpcDialogueService`, `INpcQuestService`), never the concrete
  `UNpcEngineRestClient`.
- Mock transport matches real transport contract (LSP — same fallback on non-2xx, same parse path).
- `USTRUCT` with `UPROPERTY` on every field that crosses a module boundary.

---

## What Was Built (phases complete as of this review)

| Phase | What it is |
|-------|-----------|
| 0 | Smoke test — health check + dialogue round-trip verified |
| 1 | `UNpcEngineRestClient`, `INpcDialogueService`, `UNpcEngineServiceSubsystem`, WS stub, UMG base |
| 2 | `ANpcLocation` (tick trigger), `UNpcWorldSubsystem` (re-entry guard, clock advance), `UGreyboxWorldSubsystem` (procedural greybox), `UArrivalSubtitleWidget` |
| 3 | `UNpcWorldSeeder` (idempotent, halt-on-error), `Seed/DemoWorld_v1.json` (5 NPCs, 4 locations, quests, factions, events), `UNpcAutoSeedSubsystem` (auto-seeds on Play) |
| 4 | `UDialogueComponent`, `UDialogueWidgetBase`, `URelationshipMeterWidget`, `MemoryBadgeDefaults`, `NpcFallbackDefaults` |
| 5 | `INpcQuestService`, `UQuestSubsystem` (C++ static quest map per DEC-028), `UFactionSubsystem`, `UNpcSaveGame`, trust gate for `L_TavernBack` unlock |
| 6 | `UGossipCacheSubsystem`, `URumorJournalWidget`, `ANoticeBoard`, Sorn quest chain unlock |
| 7C++ | `NpcAppearance` seam, `UFacialExpressionMapper`, camera blend in `UDialogueComponent` |
| 10 | Notice board texts, memory badge authored text, fallback canned lines finalized |
| 12 (planned) | Phase 12 Block A (async avatar load, `DA_NpcAppearance`, hybrid resolver) + Block B (dead code sweep) — NOT YET IMPLEMENTED |

NPC map (IDs are stable):
- `mira_innkeeper` → `loc_tavern`
- `lira_fence` → `loc_tavern_back`
- `aldric_merchant` → `loc_market_square`
- `captain_sorn` → `loc_guard_barracks`
- `old_henryk` → `loc_market_square`
Player: `player_demo`

---

## Files to Read (in this order — front-load the most architecturally important)

**Start here (architecture foundation):**
1. `project-harness/CLAUDE.md` — project rules (your rubric)
2. `Source/NpcEngineClient/Public/NpcDialogueService.h` — the primary interface boundary
3. `Source/NpcEngineClient/Public/NpcQuestService.h` — secondary interface
4. `Source/NpcEngineClient/Public/NpcEngineTypes.h` — all contract USTRUCTs
5. `Source/NpcEngineClient/Public/NpcEngineRestClient.h` and its `.cpp`
6. `Source/NpcEngineClient/Public/NpcWorldSeeder.h` + `Private/NpcWorldSeeder.cpp`

**Game module core:**
7. `Source/DemoGame/World/NpcWorldSubsystem.h` + `.cpp`
8. `Source/DemoGame/World/QuestSubsystem.h` + `.cpp`
9. `Source/DemoGame/World/FactionSubsystem.h` + `.cpp`
10. `Source/DemoGame/World/GossipCacheSubsystem.h` + `.cpp`
11. `Source/DemoGame/World/NpcSpawnerSubsystem.h` + `.cpp`
12. `Source/DemoGame/World/GreyboxWorldSubsystem.h` + `.cpp`
13. `Source/DemoGame/NPC/NpcActorBase.h` + `.cpp`
14. `Source/DemoGame/NPC/NpcGreyboxActor.h` + `.cpp`
15. `Source/DemoGame/NPC/NpcAppearance.h` + `.cpp`
16. `Source/DemoGame/Dialogue/DialogueComponent.h` + `.cpp`
17. `Source/DemoGame/Dialogue/DialogueWidgetBase.h` + `.cpp`
18. `Source/DemoGame/World/NpcSaveGame.h` + `.cpp`
19. `Source/DemoGame/DemoGameCharacter.h` + `.cpp`

**Tests (LSP + coverage gaps):**
20. `Source/DemoGame/Private/Tests/FakeNpcDialogueService.h`
21. `Source/DemoGame/Private/Tests/FakeNpcQuestService.h`
22. `Source/NpcEngineClient/Public/NpcAutoSeedSubsystem.h` + `Private/NpcAutoSeedSubsystem.cpp`
23. All `*.spec.cpp` files in `Source/NpcEngineClient/Private/Tests/`
24. All `*.spec.cpp` files in `Source/DemoGame/Private/Tests/`

**Dead code check:**
25. `Source/DemoGame/Variant_SideScrolling/`, `Variant_Combat/`, `Variant_Platforming/` — scan briefly
26. `Source/NpcEngineClient/Public/NpcEngineSeedClient.h` + `Private/NpcEngineSeedClient.cpp`
27. `Source/NpcEngineClient/Public/NpcEngineWsClient.h`

**Remaining files** — scan for rule violations (hardcoded strings, net I/O in wrong module, missing
UPROPERTY, magic numbers, function length > 40 lines, nesting > 3 levels):
28. Everything else under `Source/DemoGame/` and `Source/NpcEngineClient/`

---

## Review Dimensions

Work through ALL dimensions. Do not skip one because it has no findings — confirm it clean if so
(though do not create a review file for a clean pass; only write files for actual findings).

---

### Dimension 1 — Module Boundary + Architecture Rules

Check every `.cpp` and `.h` in `Source/DemoGame/` for:
- Any `#include` that pulls in `FHttpModule`, `FWebSocketsModule`, `FHttpRequest*`, or `IHttpRequest`
- Any `FJsonObject`, `FJsonValue`, `JsonUtilities`, or `FJsonSerializer` usage
- Any engine-contract USTRUCT defined in `DemoGame` (types that mirror the openapi.json response shapes)
- Any hardcoded `npc_id` string literals (e.g. `"mira_innkeeper"` as a string in gameplay code vs as an `FName` from a named constant)
- Any hardcoded URL fragments or endpoint path strings
- Any direct instantiation of `UNpcEngineRestClient` (instead of going through the interface)

Check `Source/NpcEngineClient/` for:
- Any gameplay logic (actor state, trust accumulation, quest progression) that has leaked into the client module
- Any hardcoded game-world constants (NPC IDs, location IDs) that should live in DemoGame

**CLAUDE.md rule reference:** "Forbidden" section in Architecture.

---

### Dimension 2 — SOLID Compliance

**SRP** — Does each class have exactly one responsibility?
- `UNpcWorldSubsystem`: does it do more than clock/location tracking? Check if trust gate logic (for `L_TavernBack`) is embedded here. If `OnTrustChanged` listening + `OnTavernBackUnlocked` firing live here alongside the clock, flag the dual responsibility.
- `UDialogueComponent`: does it handle dialogue session management AND trust accumulation AND memory badge notification AND gossip cache notification? List all responsibilities.
- `ADemoGameCharacter`: input handling + NPC detection + dialogue spawning + camera ownership — is this too broad for a character class?
- `UNpcWorldSeeder`: parses JSON, orchestrates HTTP calls, tracks seeding state, manages async chain. Count the responsibilities.

**OCP** — New content must be addable via data, not code edits:
- Adding a new NPC: does it require a code change? Check `UNpcSpawnerSubsystem::GetRoster()`.
- Adding a new location: does it require a code change? Check `UGreyboxWorldSubsystem::GetLayout()`.
- Adding a new quest: does it require a code change? Check `UQuestSubsystem`'s quest data structure.
- Adding a new faction: does it require a code change? Check `UFactionSubsystem`.
- Adding a new gossip event (beyond `northern_war_begins`): does it require a code change? Check `UGossipCacheSubsystem`.
- Adding a new trust gate: does it require a code change? Check `UNpcWorldSubsystem` and `UDialogueComponent`.

Flag every "yes" as a scalability blocker for a full game.

**DIP** — All gameplay dependencies on interfaces, not concretes:
- Search `Source/DemoGame/` for any direct reference to `UNpcEngineRestClient` (should be zero).
- Check `UQuestSubsystem` initialization — does it resolve `INpcQuestService` or does it touch the REST client?
- Check `UFactionSubsystem` — how does it get NPC membership data? Is it depending on a concrete data file or a runtime interface?

**ISP** — Interface sizes:
- `INpcDialogueService`: list all methods. Is `AdvanceClock` a natural fit here or an ISP violation? (DEC-015 noted this concern.)
- Does adding a new gameplay system require adding a method to an existing interface (forcing a recompile of all implementors), or can it use a new interface?

**LSP** — Mock parity (critical):
- Read `FakeNpcDialogueService` and compare every method against `UNpcEngineRestClient`. For each method: does the fake fire the same callbacks in the same order with the same conditions as the real client?
- Read `FakeNpcQuestService` and apply the same check.
- Specifically check the `AdvanceClock` error path (ISSUE-008: fake fires both `OnError` + `OnResult(false)`).
- Check if any fake method silently succeeds where the real client would call `OnError`.

---

### Dimension 3 — Scalability: 100+ NPCs / 30+ Locations

This is the most important dimension for expansion readiness. Think at scale throughout.

**NPC roster scaling:**
- `UNpcSpawnerSubsystem::GetRoster()` — is this a static C++ structure? At 100 NPCs, this becomes unmaintainable. What would need to change?
- Spawner memory: at 100 NPCs all spawned in the same world, what is the per-NPC actor overhead? Are there any patterns that suggest N² complexity per NPC?

**Location scaling:**
- `UGreyboxWorldSubsystem::GetLayout()` — static C++ table. At 30+ locations, same issue as the roster.
- `ANpcLocation` overlap detection — does `OnPlayerArrived` do any per-location iteration?

**Seeder scaling:**
- `UNpcWorldSeeder`: the recursive async chain (ISSUE-002) — at 100+ nodes with O(N²) lambda captures, what is the memory overhead? Estimate the number of copies at 100 nodes.
- `UNpcAutoSeedSubsystem`: seeds every Play with a `CheckNodeExists` per node. At 100+ nodes, this is 100+ HTTP calls on startup before gameplay starts. Is there a batching strategy or skip condition?
- `BuildTasksFromJson` parsing: is there any performance concern with large seed files?

**Dialogue + trust scaling:**
- `UDialogueComponent` accumulates trust per-component. With 100 NPCs, 100 trust counters are in memory. Is there any issue with this?
- Trust gate thresholds (`TRUST_GATE_2_MIRA`, `NpcEngine::TrustGateSornQuest`): these are named constants in C++. For 100 NPCs with different trust gates, where do these live? Is there a general trust gate data structure, or are they all individual named constants?
- The gossip cache watches for `GossipEventId::NorthernWarBegins`. For a full game with 50+ events, how does the gossip system generalize? Is there a pluggable event-watch pattern?

**Quest system scaling:**
- `UQuestSubsystem` stores quest data in a C++ static map (DEC-028). At 100+ quests, this becomes a maintenance problem. Evaluate how much rework is needed to make this data-driven (DataAsset / JSON).
- Quest chain links: are they hardcoded in the C++ map or data-driven?
- `QuestConfirmWidget`: what text does the player see when a quest is offered? Is it from the C++ map or dynamic from NPC dialogue context?

**Faction scaling:**
- `UFactionSubsystem`: how many factions can it handle? Is `TMap<FName, int32>` sufficient or is there a limit?
- NPC membership data: how does the faction subsystem know which NPC belongs to which faction at runtime? Is this coming from the seed JSON (seeder only) or from a runtime-accessible structure?

**Memory badge + gossip cache:**
- `MemoryBadgeDefaults.h` covers 20 node IDs. At 100+ NPCs with their own memory nodes, this static map becomes unmanageable. What is the data-driven upgrade path?
- `UGossipCacheSubsystem` pulls `FNpcStateSnapshot` via `GetNpcState` after each tick. At 30+ locations and frequent ticks, how many state polls happen per session?

**Save game:** (verify all of this by reading `NpcSaveGame.h/.cpp` — do not assume)
- Determine exactly what `UNpcSaveGame` persists and what it omits. Does trust accumulation per NPC survive a save→quit→load cycle? Session IDs? Relationship history? If trust resets on reload, is that an intentional demo simplification or a full-game gap?
- Save schema migration: is there a version field? When a field is added to `UNpcSaveGame` in a future patch, what happens to an existing save — graceful default, or corruption/crash?

---

### Dimension 4 — Contract Coupling (Evolving API)

The NPC Engine API will change as the backend develops. Flag everywhere the Unreal client is brittle to contract changes.

**USTRUCT mapping:**
- Read every USTRUCT in `NpcEngineTypes.h`. For each field: is the `meta=(JsonName="...")` annotation present and matching the `docs/openapi.json` name? (`Scripts/check_contract_sync.py` enforces field presence but does it verify JsonName annotations?)
- Are there any fields in `docs/openapi.json` that do NOT have a corresponding USTRUCT field (i.e., currently ignored)? If those fields become important in a future API version, where would parsing break?
- `FDialogueResponse::audio_bytes`: this is a stub. When the backend adds real audio, what changes in `NpcEngineJsonUtils`?

**UENUM forward-compat:**
- `EFacialExpressionType`: unknown string → `Neutral` + log. Verify this path in the JSON parser. Is there any case where an unknown value could crash instead of logging?
- `EActionType`: same check.
- Are there any other enums from the API that do NOT have the unknown-string-safe path?

**WebSocket contract:**
- `FNpcEngineWebSocketClient` handles `token / done / error / proactive_line` message types. If the backend adds a new WS message type, does the handler silently ignore it or crash? Check the dispatch logic.
- The WS client is a stub (`// TODO(SLICE-2-WS)`). When it is implemented, which `UDialogueComponent` methods will need to change to handle streaming vs batch responses?

**Seeder contract:**
- `DemoWorld_v1.json` must match the backend node/edge API shapes. The seeder has `IsValidGraphId` validation but if the backend adds a required field to `UpsertNode`, the seeder will silently omit it (no USTRUCT validation of the seed JSON). Flag if the seed JSON is verified against the schema.

**Quest API shapes:**
- Phase 5 notes that quest endpoint shapes need live verification against `GET /openapi.json` (marked as a human gate). Verify whether `FQuestOfferRequest`, `FQuestObjectiveRequest`, etc. have any field mismatches with the expected shapes listed in the ROADMAP.

---

### Dimension 5 — Test Coverage + Mock Parity

**Spec coverage gaps:**
- List all public methods in `INpcDialogueService` and verify each has at least one Automation Spec covering its happy path and at least one covering its error/non-2xx path.
- List all public methods in `INpcQuestService` and apply the same check.
- `UNpcWorldSubsystem::OnPlayerArrived` — how many edge cases are covered? (new location, re-entry, `bFiresTick=false`, service unavailable)
- `UGossipCacheSubsystem`: are the specs covering the `GetChainForEvent` ordering guarantee? The `MarkPlayerSpokeToNpc` gate?
- `UQuestSubsystem`: is there a spec for the case where `QuestEvaluate` returns false (quest not yet complete)?
- `UNpcAutoSeedSubsystem`: does the spec cover the "seeds at most once per session" guard if `OnWorldBeginPlay` fires multiple times (e.g. level restart)?

**`#if WITH_DEV_AUTOMATION_TESTS` guard:**
- Check every `*.spec.cpp` file. Exactly one is known to be missing the guard (ISSUE-016: `NpcAppearance.spec.cpp`). Verify there are no others.

**GC root safety:**
- Check all `NewObject<>()` calls in spec `It()` blocks. Known issue in `NpcWorldSeeder.spec.cpp` (ISSUE-004). Are there other spec files with the same pattern?

**Timeout coverage:**
- The 30s dialogue timeout is in `Config/NpcEngine.ini`. Is there a spec that fires a timeout and verifies the fallback line is delivered? Or is timeout coverage limited to the non-2xx path (which is not the same thing)?

---

### Dimension 6 — Dead Code + Hygiene

**UE template leftovers:**
- `Source/DemoGame/Variant_SideScrolling/`, `Variant_Combat/`, `Variant_Platforming/` — these are from the UE template. List all files. Are any of these files referenced from anywhere in the NPC demo code, or are they all orphaned?
- If orphaned: this is dead code that confuses future maintainers and inflates compilation time.

**Planned-but-not-done deletions:**
- `Source/NpcEngineClient/Public/NpcEngineSeedClient.h` — DEC-043 plans deletion. Still present?
- `Source/NpcEngineClient/Private/NpcEngineSeedClient.cpp` — same.
- `Seed/slice1_tavern.json` — stale (ISSUE-020). Still present?
- `Source/NpcEngineClient/Public/NpcEngineWsClient.h` — WebSocket stub. What is its current state? Does it have an implementation, or is it a header-only declaration?

**Orphaned console commands:**
- `NpcEngine.Seed` (the old `NpcEngineSeedClient` command) — is it still registered anywhere?

**File headers:**
- ISSUE-006 identified `NpcActorBase.h/.cpp` as missing file headers. Are there other files missing the required `// File: / Module: / Purpose: / Net I/O:` header?
- Scan all `.h` and `.cpp` under `Source/` and list every file missing the header.

**Doxygen coverage:**
- Spot-check 5 public `UCLASS` headers for `/** */` Doxygen on every `UFUNCTION` and `UPROPERTY`. List any public API without documentation.

---

### Dimension 7 — Asset Integration Friction

**Appearance pipeline (Phase 12 is planned but NOT done):**
- `ANpcGreyboxActor::TrySpawnAvatar` — ISSUE-017 flags `LoadSynchronous()`. Confirm this is still present. This will cause a game-thread hitch for every MetaHuman on map load.
- Phase 12 Block A specifies converting to `UAssetManager::GetStreamableManager().RequestAsyncLoad(...)`. Evaluate the complexity of this change and whether the weak-self-ptr cancel-on-`EndPlay` requirement is already scaffolded.
- `DA_NpcAppearance` DataAsset — Phase 12 plans this but it does not exist yet. What does the appearance resolution path look like WITHOUT it? Is there any fallback, or is `NpcAppearance.cpp` the only path?
- `FNpcSpawnRecord.AvatarClass` is a `TSoftClassPtr<AActor>` — ISSUE-018 flags that it lacks `UPROPERTY`. If this isn't annotated, the GC cannot track it. How serious is this in the spawn path?
- `FGreyboxLocation` fields lack `UPROPERTY` (ISSUE-018). If these structs are ever serialized or reflected, this breaks. Flag if they are already being serialized anywhere.

**Facial expression system:**
- `UFacialExpressionMapper` maps `ENpcFacialExpression` → `(MorphTargetName, WeightScale)`. The roadmap says the default C++ map ships placeholder ARKit-namespace names — confirm this in the code. If a mapped morph name does not match an actual MetaHuman blend shape at runtime, `ApplyExpression` will silently do nothing (no crash, no expression, no log). Is there any validation or warning when a morph target name fails to resolve on the skeletal mesh? That silent-no-op is the realistic failure mode when art lands.
- `DA_FacialExpressionMap` is referenced as the override DataAsset. Has the UPROPERTY to assign it been wired to the correct owner (`UFacialExpressionMapper` or a component)? How does the mapper know which DataAsset to load?
- The camera blend uses `"DialogueCamSocket"` — is this a hardcoded string literal in C++ code? CLAUDE.md forbids hardcoded string literals in gameplay.

**Animation Blueprint coupling:**
- DEC-041 defers the `bThinking` AnimBP variable name to be confirmed in-editor. Is there any C++ code that already writes to a hardcoded AnimBP variable name? If so, it will silently fail until the exact name is confirmed.
- How does `UFacialExpressionMapper::ApplyExpression` interact with the Animation Blueprint? Is it calling `SetMorphTarget` on the skeletal mesh directly (bypassing AnimBP blend) or driving a parameter the AnimBP reads?

**Level streaming / world partition:**
- The current architecture uses procedural greybox actors. Phase 8 introduces real levels. Is there a clear boundary in `UGreyboxWorldSubsystem::EnsureBuilt` that prevents it from conflicting with real levels (the "skip if already placed" guard)?
- For a full game with 30+ locations, UE5's World Partition system would replace level streaming. Is there anything in the current architecture that assumes the old level streaming model and would need to change for World Partition?

---

### Dimension 8 — Performance Concerns

**Game thread blocking:**
- Beyond ISSUE-017 (sync avatar load), scan all `BeginPlay`, `Tick`, and overlap handlers in `DemoGame` for any synchronous operations that could block the game thread (file I/O, heavy computation, sleep-loops).
- `UNpcAutoSeedSubsystem::OnWorldBeginPlay` fires a health check + up to 33+ `CheckNodeExists` calls. Are all of these truly non-blocking?

**Tick usage:**
- Does any subsystem or component use UE's `Tick()` function? Tick is called every frame — any per-frame work that could be event-driven instead is a performance concern at 100+ NPC scale.

**HTTP call density:**
- At 30+ locations with `bFiresTick=true`, how many `AdvanceClock` calls happen per session? Is there any debounce or batching?
- `UGossipCacheSubsystem` calls `GetNpcState` after each tick. At 30 locations × multiple player visits = many state polls. Is there a cooldown?

**Memory footprint:**
- The `TArray<FGossipEntry>` in `UGossipCacheSubsystem` — does it ever get pruned? For a long session across many events and NPCs, could this grow unbounded?
- `UDialogueWidgetBase` appends to `ResponseText` — is there a history length cap? In a long session, the dialogue history could grow unbounded.

---

### Dimension 9 — Expansion Readiness Per System

For each system, answer: "What must change to support a full game?" Rate each as: **Ready** / **Minor work** / **Redesign needed**.

**Dialogue system:**
- Concurrent dialogue (can the player open dialogue with two NPCs at once, or trigger background NPC→NPC dialogue)?
- `SessionId` caching in `UDialogueComponent` — what happens if the player exits and re-enters dialogue with the same NPC mid-session?

**Quest system:**
- Is the C++ static quest map (DEC-028) the only quest data source? Is there any runtime mechanism to load quest definitions from a DataAsset or JSON without recompiling?
- The quest chain link structure (which quest unlocks which next quest) — is this hardcoded or data-driven?

**Gossip system:**
- How would you add a second gossip event (e.g., `city_fire_begins`)? Trace what code changes would be needed.
- Is `UGossipCacheSubsystem` tightly coupled to the `northern_war_begins` event ID, or is it generic?

**Save game:**
- Trust accumulation per NPC is NOT saved. After restarting the game, all trust resets. Is this the intended design, or a known gap?
- `UNpcSaveGame` schema versioning: is there a version field? What happens when the schema changes in a future patch?

**NPC appearance:**
- The `NpcAppearance::GetAvatarClass` C++ default map is currently empty (all cubes). Phase 12 proposes `DA_NpcAppearance`. Until Phase 12 is done, what happens when a MetaHuman is imported? Can it be wired without Phase 12?

**Location / world:**
- Level streaming vs world partition: for 30+ locations, UE5.1+ World Partition is the recommended approach. What in the current architecture assumes explicit level boundaries vs. open world?
- `UNpcWorldSubsystem::CurrentLocationId` — is this state preserved across level transitions or does it reset when a new level loads?

**Faction system:**
- NPC-faction membership: at runtime, how does `UFactionSubsystem` know which NPCs belong to which faction? Is this data loaded from the seed JSON at startup, hard-coded, or resolved dynamically from the NPC Engine graph?
- Adding a third faction at runtime: what code changes are needed?

**Audio:**
- `FDialogueResponse::audio_bytes` is a stub (`TArray<uint8>` placeholder). When the backend adds audio streaming, what must change in `NpcEngineRestClient` and `UDialogueWidgetBase`?
- `UGameplayStatics::PlaySound2D` (Phase 9) is called from widget events. For a full game with spatial NPCs, positional audio (`PlaySoundAtLocation`) would be expected. Is the audio system designed for that upgrade?

---

### Dimension 10 — Stubs + Unimplemented Features

Identify every stubbed or partially-implemented feature and classify by criticality to a full game.

Specifically look for:
- `// TODO` comments — list every one with file and line
- `// TODO(SLICE-2-WS)` — WebSocket stub markers
- `audio_bytes` — the audio field stub
- `UDialogueWidgetBase` word-by-word reveal (ISSUE-007) — what is the current state?
- `ISSUE-011` interaction prompt — is it still missing?
- NPC look-at target during thinking state (DEC-041 deferred)
- `FNpcEngineWebSocketClient` — how complete is the WS client? List what is missing for it to be a real streaming client.
- Any `UFUNCTION` with an empty body or a single `return` that is marked as a placeholder.
- Any `BlueprintNativeEvent` with only a `_Implementation` that does nothing.

---

### Dimension 11 — Single Source of Truth / Data Duplication ⭐ (highest-leverage for expansion)

This is likely the most important maintainability finding for a 100-NPC game. **Map every place that
world/NPC/quest/location data is defined**, then measure the duplication.

Known/suspected data sources (verify each, find others):
- `Seed/DemoWorld_v1.json` — the seed graph (NPCs, locations, factions, events, quests, edges)
- `UNpcSpawnerSubsystem::GetRoster()` — spawn placement + appearance
- `UGreyboxWorldSubsystem::GetLayout()` — location geometry
- `MemoryBadgeDefaults.h` — per-memory-node display text
- `NpcFallbackDefaults.h` — per-NPC fallback lines
- the quest C++ static map (DEC-028)
- `NpcAppearance` — per-NPC avatar class
- faction membership (wherever the faction subsystem reads it)
- NPC ID / location ID named constants (wherever they live)
- notice board / gossip event text

**Deliverable for this dimension:** For "add one new NPC to the game," list every file a developer must
touch and keep mutually consistent. Do the same for "add one new location" and "add one new quest." If
that count is >2–3 files per entity, that is the expansion wall. The roadmap already ships a "roster ↔
layout consistency" spec — that spec existing is itself evidence the data is duplicated and must be
hand-synced. Propose the consolidation: one canonical per-entity definition (e.g. a single NPC DataAsset
or data table) that the spawner, greybox, appearance, fallback, and seeder all *read from*, instead of
N parallel hand-maintained maps. This is almost certainly a P1 `full-game` finding — but verify the real
file count before asserting it.

---

### Dimension 12 — Simplicity / Over-Engineering (YAGNI) ⭐ (author explicitly values simple code)

The author wants the codebase **simple and ready to expand**, not abstract for its own sake. Flag
*accidental complexity* — indirection that doesn't pay for itself. Be even-handed: also confirm where an
abstraction IS earning its keep (note it as a strength in the index).

- **Single-implementation interfaces / seams.** Every `SetXForTesting` / injection seam: is it used by
  anything other than a test? `INpcDialogueService` and `INpcQuestService` have one real implementor
  each — is the interface earning its DIP cost, or could the test use a subclass/spy more cheaply? (Be
  careful: DIP here is a stated project rule and genuinely helps swap REST→WS later — judge whether the
  *current* shape is the simplest that preserves that, not whether to delete it.)
- **The 3-layer override chains.** DataAsset → C++ default → raw fallback appears for fallback lines,
  memory badges, and (planned) appearance. Is the middle or outer layer actually exercised, or is one
  layer dead weight across all three? Could they share one generic "override map" helper instead of
  three near-identical hand-rolled chains?
- **Subsystem proliferation.** World, Quest, Faction, Gossip, Greybox, Spawner, Service, AutoSeed are
  all subsystems. Are any so thin or so coupled that merging two would reduce surface area without
  losing SRP? (Don't reflexively recommend merges — only where the split adds ceremony, not clarity.)
- **Premature generality vs missing generality.** Note the irony where it appears: data that *should* be
  generic (NPCs, quests) is hardcoded, while plumbing that could be simple is heavily abstracted.
- Recommend simplifications that **reduce line count while keeping testability**. A good finding here
  makes the codebase smaller.

---

### Dimension 13 — Async UObject Lifetime + Delegate Safety (the bug class tests can't catch)

Every Automation Spec uses a **synchronous** mock, so this entire failure class is invisible to the test
suite and only manifests in live play. Trace it manually with care — it is the most likely source of
real crashes.

For every async HTTP path (`UNpcEngineRestClient` and every caller — `UDialogueComponent`,
`UQuestSubsystem`, `UFactionSubsystem`, `UGossipCacheSubsystem`, `UNpcWorldSeeder`,
`UNpcAutoSeedSubsystem`, widgets):
- If the requesting `UObject` is **destroyed while a request is in flight**, does the completion delegate
  safely no-op, or does it dereference a dead `this` / dangling pointer?
- Do completion lambdas capture raw `this` / raw pointers, or `TWeakObjectPtr` / weak handles guarded
  before use?
- **World teardown mid-request** (PIE stop, level transition, travel): is there any callback that
  assumes the World / PlayerController / pawn still exists?
- Does closing a dialogue (or interacting with a second NPC) while the first request is pending leave a
  stale callback that mutates the wrong NPC's state?
- The streamable async-load path planned in Phase 12 (ISSUE-017) has the identical hazard for the actor
  being loaded into — note whether the planned design already accounts for cancel-on-`EndPlay`.

Each confirmed unsafe path is at least P2, likely P1 if it touches the common dialogue flow.

---

### Dimension 14 — Production-Shipping Readiness

Things that are fine for a demo but block an actual shipped game:

- **Localization.** Is *all* player-facing text `FText` (localizable), never `FString`? Scan UMG widgets
  and any text headed to the screen. Any hardcoded English `FString` reaching the UI, or authored
  content stored as `FString`, blocks localization and is a real shipping gap. (`FText` is used in
  places — confirm it's used *everywhere* player-facing.)
- **Config / environments.** There is one `Config/NpcEngine.ini`. How does dev vs staging vs prod
  backend selection work for a real release? Is the API-key handling shippable, or dev-only? Is anything
  that should be runtime-config baked in as a compile-time constant?
- **Module → Plugin.** `NpcEngineClient` is a self-contained integration module, and the NPC Engine is a
  separate product. For a real game (and reuse across projects), should it be a UE **Plugin** rather than
  a game module? Identify what currently couples it to *this* game (hardcoded NPC IDs, game-specific
  constants, DemoGame includes) that would have to move out first. This is an expansion-enabler worth
  flagging even if the answer is "later."
- **Onboarding / runbook.** Is there a doc that tells a developer (including the author returning in 6
  months) how to add an NPC / location / quest / gossip event end-to-end? Assess whether `PATTERNS.md`
  covers this. Missing runbooks are real expansion friction for a solo dev. (Tie to Dimension 11 — the
  runbook length is a proxy for the duplication count.)
- **Cooked-build correctness.** Any editor-only API in a runtime module, absolute dev paths, or logic
  that works in PIE but would fail in a packaged build (beyond what CLAUDE.md's packaged-build section
  already enforces — look for actual violations).

---

> **Dimensions overlap by design** (scalability ↔ expansion ↔ performance ↔ SSoT all touch the same
> systems). That is so nothing slips through — it is NOT license to write the same finding four times.
> When one root cause satisfies multiple dimensions, write ONE REV file and list the dimensions it
> covers. Per Ground Rule 5, merge.

---

## Do NOT Re-Log (already in ISSUES.md)

Do not create REV files for these known issues — they're tracked. You may reference them in a related finding:
- ISSUE-001: `NpcWorldSeeder.cpp` above 400-line target
- ISSUE-002: O(N²) lambda captures in seeder
- ISSUE-003: `BuildTasksFromJson` silent empty-id
- ISSUE-004: Spec objects not GC-rooted
- ISSUE-005: `loc_tavern_back` truncated descriptor in DB
- ISSUE-006: `NpcActorBase.h/.cpp` missing file headers
- ISSUE-007: Word-by-word text reveal deferred to BP
- ISSUE-008: `FakeNpcDialogueService::AdvanceClock` LSP violation
- ISSUE-011: No interaction prompt before dialogue
- ISSUE-012: No free female MetaHuman clothing
- ISSUE-013: Lira hood gap
- ISSUE-014: Fab 403 price unconfirmed
- ISSUE-015: Legacy MetaHuman clothing not drop-in on UE5.6+
- ISSUE-016: `NpcAppearance.spec.cpp` missing `#if WITH_DEV_AUTOMATION_TESTS`
- ISSUE-017: `TrySpawnAvatar` synchronous load on game thread
- ISSUE-018: `FNpcSpawnRecord`/`FGreyboxLocation` fields lack `UPROPERTY`
- ISSUE-019: Memory badge raw ID fallback renders to player
- ISSUE-020: `slice1_tavern.json` stale tavern name

---

## Priority Criteria

| Priority | Meaning |
|----------|---------|
| **P1** | *Blocks* expansion (cannot add content/scale without fixing) OR causes silent data loss / live-play crashes now. Fix before adding content. |
| **P2** | Forces significant rework at scale, makes the codebase brittle to the evolving API contract, or is a user-visible gap. Fix before Slice 2 work starts. |
| **P3** | Quality/maintainability/simplicity debt that compounds but doesn't block expansion. Fix during a cleanup pass. |

Priority answers *how bad*; `horizon` answers *when it bites* (`now`/`slice-2`/`full-game`). They are
independent: a `full-game` finding can still be P1 if it hard-blocks the 100-NPC target. A `now` finding
can be P3 if it's cosmetic. Set both honestly — the planning pass sequences on the combination.

---

## How to Run This (execution guidance)

- Work **dimension by dimension**, and **write each REV file as you confirm it** — do not hold all
  findings in memory until the end (you'll run out of context and drop the early ones).
- Read the actual code before writing any finding (Ground Rule 3). The "Files to Read" list is a
  suggested order, not exhaustive and not authoritative on line numbers — adapt.
- If running as a multi-agent workflow: fan out one reader per dimension over the relevant files, each
  emitting structured candidate findings; then a single pass dedups (Ground Rule 5), assigns sequential
  IDs, and writes the files. If running solo, just go top to bottom.

## Output

- One file per finding: `project-harness/reviews/REV-001.md`, `REV-002.md`, etc.
- Use `project-harness/reviews/_template.md` exactly — including the `horizon`/`confidence`/`effort`
  frontmatter and the required Evidence section.
- Sequential IDs, no gaps. One clear finding per file. Merged root causes count as one file.
- If a dimension is genuinely clean, do NOT create a file for it. A clean dimension is a good outcome,
  not a gap to fill.
- At the end, produce `project-harness/reviews/REVIEW_INDEX.md` containing:
  1. **Overall verdict** — 3–5 sentences: how expansion-ready is this codebase for a 100+ NPC game,
     and what are the top 3 things to fix first (by REV ID)?
  2. **Strengths** — a short list of what is genuinely well-built and should NOT be disturbed during
     fixes (so the author doesn't refactor away something that's working). Cite the code.
  3. **Findings table** — one row per REV: ID, priority, horizon, effort, category, title.
  4. **Counts** — totals by priority and by horizon.
