# Decisions Log

Append-only. Each entry: context, decision, rationale. Never edit a past decision — supersede it with a
new entry that references the old one.

## DEC-001: Separate git repo from the engine
**Date:** 2026-06-23
**Decision:** DemoGame is its own git repository, distinct from the NPC Engine backend repo, and uses Git LFS for binary assets.
**Why:** The game and the engine ship and version independently; the engine is consumed only through its REST/WS contract. LFS keeps the game repo lean despite UE binary assets.

## DEC-002: C++-first, Blueprint only where visual/editor-forced
**Date:** 2026-06-23
**Decision:** All gameplay/integration logic lives in C++. Blueprint and editor work is limited to Animation Blueprints, UMG layout over C++ base widgets, materials, Niagara, the level, and MetaHuman setup.
**Why:** Keeps logic reviewable, testable, and diffable; avoids hidden behaviour and HTTP/JSON in Blueprint graphs.

## DEC-003: Game owns `player_id`
**Date:** 2026-06-23
**Decision:** The game owns the player identity (`player_<8hex>`, persisted per save). Slice-1 default is `player_demo`. A newly generated id self-seeds its Character node before its first dialogue request.
**Why:** The engine keys memory/relationships on `player_id`; the game is the authority on save identity, and self-seeding guarantees the node exists before first use.

## DEC-004: Game owns world seeding
**Date:** 2026-06-23
**Decision:** The game seeds the world via the engine's REST graph endpoints, replaying data from `Seed/slice1_tavern.json`.
**Why:** Seed content is game-owned design data, not engine data; replaying through the public graph API keeps the engine a black box behind its contract.

## DEC-005: Two engine response shapes
**Date:** 2026-06-23
**Decision:** The engine returns raw bodies for `/v1/dialogue` and `/v1/action`, and an `OkEnvelope` wrapper for every other endpoint. The JSON layer branches on which shape applies per endpoint.
**Why:** Matches the engine contract exactly; encoding the split in one place keeps parsing predictable and testable.

## DEC-006: `NpcEngineClient` is the sole network module
**Date:** 2026-06-23
**Decision:** Only `NpcEngineClient` performs network I/O (HTTP/WS) and JSON parsing. Gameplay never parses JSON and receives typed USTRUCTs from the dialogue subsystem.
**Why:** A single integration seam isolates the contract, makes the game module unit-testable without a network, and enforces a clean dependency direction.

## DEC-007: File size limits
**Date:** 2026-06-23
**Decision:** Target 400 lines `.cpp` / 200 lines `.h`; hard ceiling 500 `.cpp`. Prefer extracting submodules/components over growing megafiles.
**Why:** Small, focused files stay readable and reviewable; the ceiling forces a split-or-justify decision before bloat sets in.

## DEC-008: TDD split
**Date:** 2026-06-23
**Decision:** Strict TDD (Automation Specs first) for `NpcEngineClient`; smoke + manual + functional-eval tests for gameplay actors, components, and UMG.
**Why:** The client carries the contract risk and is unit-testable with a mock transport; gameplay/UMG is better verified by smoke and functional tests than by brittle unit tests.

## DEC-009: No line-coverage floor — presence gate instead
**Date:** 2026-06-23
**Decision:** No numeric line-coverage requirement (Unreal coverage tooling is impractical). Replaced by a presence gate: the client module ships with at least one Automation spec and a registered smoke command.
**Why:** Gets the value of a coverage gate (tests must exist and run) without fighting unreliable UE coverage instrumentation.

## DEC-010: TTS deferred — text-only Slice 1
**Date:** 2026-06-23
**Decision:** The contract carries TTS fields (`audio_bytes` / `audio_bytes_b64`). Slice 1 is text-only and exposes an `OnAudioReady` stub that does nothing yet.
**Why:** Keeps the contract complete and forward-compatible while deferring audio playback work until after the core dialogue loop is proven.

## DEC-013: DIP for dialogue via `INpcDialogueService` + a GameInstance composition root
**Date:** 2026-06-23
**Decision:** Gameplay depends on `INpcDialogueService` (`UINTERFACE(MinimalAPI, NotBlueprintable)` in NpcEngineClient, with non-`UFUNCTION` pure virtuals: SendDialogue/SendActionReport/GetNpcState), never the concrete client. A new `UNpcEngineServiceSubsystem` (`UGameInstanceSubsystem`) is the composition root: it owns the one `UNpcEngineRestClient` and hands it out as `TScriptInterface<INpcDialogueService>`. `DialogueManager` stores the interface, resolves it lazily from that subsystem on first use, and exposes `SetDialogueService()` for test injection. The shared completion delegates moved from `NpcEngineRestClient.h` into `NpcDialogueService.h` (declared once). The redundant PlayerController `NpcSmokeTest` exec was removed in favour of the `NpcEngine.Smoke` console command.
**Why:** Closes ISSUE-002 — DemoGame now has zero references to the concrete client (`rg UNpcEngineRestClient Source/DemoGame` = 0). Plain-virtual interface keeps the existing non-dynamic delegates and lambda callbacks unchanged (smallest blast radius). Lazy resolution avoids GameInstance-vs-World subsystem init-order issues, and the injection seam unlocks gameplay-side tests with a synchronous fake (no HTTP/engine) — see the `NpcEngine.Game.DialogueManager` spec.

## DEC-012: Interaction + dialogue presentation driver lives on `ADemoGameCharacter`
**Date:** 2026-06-23
**Decision:** The player-side wiring (find nearest NPC on interact, BeginDialogue, create/show/hide the dialogue widget, restore input on end) lives on `ADemoGameCharacter` — the C++ base of the active pawn `BP_ThirdPersonCharacter`. Interact is bound via an assignable `InteractAction` (Enhanced Input) with a legacy `E`-key fallback so it works before `IA_Interact` is authored. The widget's display events (`OnNpcResponseReceived`, etc.) became `BlueprintNativeEvent` with C++ defaults that update `BindWidgetOptional` text slots, so a minimal `WBP_Dialogue` shows dialogue with no Blueprint scripting.
**Why:** Reaches the existing playable pawn without changing the GameMode or default map, keeps the composition in C++ (harness C++-first), and lets the engine loop be exercised in-game immediately while leaving UMG layout/MetaHuman/level placement as the designer's editor pass.

## DEC-011: UENUM for the engine's closed sets, with forward-compat
**Date:** 2026-06-23
**Decision:** The engine's closed sets (action type, expression type) are mirrored as `UENUM`s. An unknown incoming string logs a warning and falls back to a safe default (`speak` / `neutral`) — never crashes, never drops the message.
**Why:** Type safety for known values plus graceful handling when the engine adds a value the client doesn't know yet.

## DEC-014: /clock/advance endpoint shape
**Date:** 2026-06-24
**Decision:** `POST /clock/advance` body is `{ "delta_ticks": <int> }`. The OkEnvelope wrapper applies (shape B). Optional fields `game_time_seconds` and `advance_time_field` are NOT sent — the engine accepts the minimal body. Response `.data` is checked for presence; a non-2xx or missing `.data` → `false` returned + error logged. This shape was resolved per §13 OQ-2 in the game design roadmap. Live verification against `GET http://localhost:8000/openapi.json` should be performed before merging to confirm the endpoint still exists and the body schema has not changed.
**Why:** The endpoint is not in the curated `docs/openapi.json` (game-side subset). Recording the confirmed shape here so all implementers use the same body and do not rely on memory.

## DEC-016: ANpcLocation owns its own overlap — not the player character
**Date:** 2026-06-24
**Decision:** `ANpcLocation::BeginPlay()` registers `OnComponentBeginOverlap` on its own `TriggerVolume`. The handler checks that the overlapping actor is a player-controlled pawn, then calls `UNpcWorldSubsystem::OnPlayerArrived`. The player character (`ADemoGameCharacter`) is not modified.
**Why:** The ROADMAP described "player character registers with each ANpcLocation trigger volume" as the intended outcome. Implementing it on the location actor is equivalent in result, avoids an actor-iteration race condition (character constructed before locations exist), follows SRP (location actor owns its own trigger), and avoids modifying an actor that doesn't need to change.

## DEC-017: Canonical tavern name — "The Broken Flagon"
**Date:** 2026-06-24
**Decision:** The tavern at `loc_tavern` is named **"The Broken Flagon"** in all authored content and seed data. The name "The Rusty Flagon" used in `docs/STORYBOARD.md` was a stale draft label; `docs/game_design_roadmap.md` §7.1 (the canonical v1.0 GDD) uses "The Broken Flagon" and is the source of truth. `docs/STORYBOARD.md` updated to match.
**Why:** A single canonical name prevents authored text divergence across seed files, notice boards, NPC dialogue context, and fallback lines. The GDD is the authoritative design doc; the storyboard was an earlier draft.

## DEC-018: Aldric inner-life seeding via admin endpoints — deferred to Phase 5
**Date:** 2026-06-24
**Decision:** The `aldric_confession` belief (`aldric_merchant.belief["amulet_origin"]`) and secret (`aldric_merchant.secret["amulet_truth"]`) are **NOT** seeded in Phase 3. They will be seeded in Phase 5 via `POST /v1/admin/memories/{character_id}` (or equivalent belief/secret endpoint) when the quest chain that requires them is implemented. Phase 3 seeds Aldric's Character node with biography only.
**Why:** The admin endpoints (`/v1/admin/...`) are out of scope for Phase 3 seeding per ENGINE_CONTRACT.md §4. The belief/secret data only becomes load-bearing in Phase 5 (`aldric_confession` quest step). Seeding it early creates a dependency on admin API shape verification that belongs to Phase 5. The Phase 5 seeding path will be recorded in a dedicated DEC entry at that time.

## DEC-015: AdvanceClock added to INpcDialogueService (ISP note)
**Date:** 2026-06-24
**Decision:** `AdvanceClock(int32 DeltaTicks, TFunction<void(bool)> OnResult, FOnNpcEngineError OnError)` is added as a pure virtual to `INpcDialogueService`. The `UNpcWorldSubsystem` (DemoGame) calls it through the interface. The method signature follows the same async+callback pattern as the other interface methods. ISP note: the interface now carries one world-clock method alongside the dialogue methods. If a future consumer needs only clock ticks (e.g. a dedicated time subsystem with no dialogue), split off an `INpcWorldService` interface at that point. Do not split preemptively — one extra method does not violate ISP in practice.
**Why:** `UNpcWorldSubsystem` must advance the clock on player arrival without depending on the concrete `UNpcEngineRestClient`. Adding it to the existing interface is the minimal change. Splitting for hypothetical future consumers would be premature abstraction.
