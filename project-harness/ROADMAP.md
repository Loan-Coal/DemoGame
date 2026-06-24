# Roadmap

Slice-based delivery. Each unchecked box is a discrete, TDD-able unit an `/expand-next`-style flow can
consume top-to-bottom. Check a box only when its work is merged and `Scripts/check.ps1` is green.

## Bring-up — before any new game work (do these first)
- [x] **Generate project files + full build** (Rider, or `powershell Scripts/check.ps1 -WithBuild`). First compile of the integrated `NpcEngineClient` module. *(Done 2026-06-23: fixed dynamic-delegate binding in `DialogueWidgetBase` — `AddUObject`/`Remove` → `AddDynamic`/`RemoveDynamic` + `UFUNCTION()` handlers. Both module DLLs build clean.)*
- [x] **Create `Config/NpcEngine.ini`** from `Config/NpcEngine.ini.template`. *(Done 2026-06-23: default localhost:8000 + dev key; gitignored.)*
- [x] **Bring up the Docker engine** and prove the middleware end-to-end. *(2026-06-23: verified live through the compiled `UNpcEngineRestClient` — `NpcEngine.Smoke` ran headless: Health OK, Mira reply "Good evening to you as well…", DegradationLevel=full, Cached/Fallback=false, PASS. Also fixed a config bug: GConfig truncated `http://…` at `//`; now reads the ini manually.)*
- [x] **Register the `NpcEngine.Smoke` console command** + write ≥1 client `*.spec.cpp`. *(2026-06-23: `NpcEngineSmokeCommand.cpp` = GameMode-independent `FAutoConsoleCommandWithWorld`; `NpcEngineJsonUtils.spec.cpp` = 8 specs (parse, enum forward-compat, serialise), all pass headless. Presence + Automation gates now PASS. Fixes ISSUE-001.)*
- [ ] **Annotate mirror USTRUCTs** with `UPROPERTY(meta=(JsonName="..."))` so contract-sync moves from SKIP to enforcing PASS.

## Slice 1 — Tavern (scaffolding)
- [ ] Repo + Git LFS configured (.gitattributes for UE binary asset types)
- [ ] UE5.8 Third Person C++ project skeleton
- [ ] Plugins enabled: MetaHuman, WebSockets, HTTP, Json
- [ ] `NpcEngineClient` module: config loader (`Config/NpcEngine.ini` + env, fail-fast on missing)
- [ ] `NpcEngineClient` module: REST client (`FHttpModule`, async delegates, Bearer auth)
- [ ] `NpcEngineClient` module: contract USTRUCTs mirroring `docs/openapi.json` (with `JsonName` meta)
- [ ] `NpcEngineClient` module: both response shapes (raw vs `OkEnvelope`) handled in the JSON layer
- [ ] `NpcEngineClient` module: UENUMs for closed sets with forward-compat fallback
- [ ] `NpcEngineClient` module: seeding client (replays `Seed/slice1_tavern.json`)
- [ ] `NpcEngineClient` module: player-id provider (`player_<8hex>`, self-seed before first dialogue)
- [ ] `NpcEngineClient` module: WebSocket scaffold (class exists, not yet wired)
- [ ] `NpcEngineClient` module: fallback contract (timeout/non-2xx → canned line, game continues)
- [x] Gameplay skeleton: NPC base actor (`FName NpcId`)
- [x] Gameplay skeleton: interaction wired (player → nearest NPC → dialogue subsystem). *(2026-06-23: driver on `ADemoGameCharacter` — interact finds nearest `ANpcActorBase`, opens dialogue, spawns widget; E-key fallback before `IA_Interact` exists. See DEC-012.)*
- [x] Gameplay skeleton: dialogue subsystem (composition root in `Initialize`). *(Note: depends on concrete `UNpcEngineRestClient`, not yet the `INpcDialogueService` interface — see ISSUE-002.)*
- [x] Gameplay skeleton: C++ UMG base widget (rejects empty / oversized input; display events have C++ defaults so a minimal WBP works).
- [x] Smoke tests: curl health + dialogue round-trip; in-editor `NpcEngine.Smoke` exec command
- [x] Automation specs for the client module (`NpcEngineJsonUtils.spec.cpp` — parse/enum/serialise; mock-transport fallback specs still to come)
- [ ] `STORYBOARD.md` (Slice-1 narrative beats)

## Slice 2 — Village
- [ ] Market-square + guard-barracks NPCs: `aldric_merchant`, `captain_sorn`, `old_henryk`
- [ ] Location streaming (`loc_market_square`, `loc_guard_barracks`)
- [ ] Expand seed data for Slice-2 locations and NPCs

## Slice 3+ — Outward
- [ ] Open-world expansion
- [ ] WebSocket streaming wired end-to-end
- [ ] MetaHuman hero wiring (1–2 per scene)
- [ ] TTS playback (`OnAudioReady` → audio) — see DEC-010
