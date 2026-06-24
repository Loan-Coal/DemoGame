# DemoGame — Working Rules

Auto-loaded via the root `CLAUDE.md` @-import. These rules are not suggestions. Violating one is a bug.

---

## Orientation

**What is this:** DemoGame is a UE5.8 third-person C++ RPG that connects to the NPC Engine backend
(separate repo, dockerized) for persistent NPC memory, relationships, emotion, and LLM dialogue over
REST + WebSocket. **Current phase:** Slice-1 (Tavern) scaffolding. See `ROADMAP.md`.

### Stack
| Component | Technology |
|-----------|-----------|
| Engine | Unreal Engine 5.8, Third Person, C++ |
| IDE | JetBrains Rider + RiderLink; MSVC toolchain from VS2026 |
| Characters | MetaHuman (1–2 hero per scene) |
| HTTP | `FHttpModule` | WebSocket | `FWebSocketsModule` | JSON | `JsonUtilities` |
| Tests | Unreal Automation framework (Spec + functional) |
| Backend contract | `docs/ENGINE_CONTRACT.md` + `docs/openapi.json` (source of truth) |

### Key commands (Windows / PowerShell)
- Build: Rider build, or `Build.bat DemoGameEditor Win64 Development -project="%CD%/DemoGame.uproject"`
- Smoke (in-editor): console exec `NpcEngine.Smoke` (health + one dialogue round-trip, logs reply)
- Seed (in-editor): console exec `NpcEngine.Seed` (replays `Seed/slice1_tavern.json`)
- Tests: `UnrealEditor-Cmd <uproject> -ExecCmds="Automation RunTests NpcEngine;Quit" -unattended -nopause -nosplash -nullrhi -testexit`
- Quality gate: `pwsh Scripts/check.ps1`

### Key file locations
| Path | What it is |
|------|-----------|
| `Source/DemoGame/` | Game module: actors, components, subsystems, UMG. **No network I/O, no JSON.** |
| `Source/NpcEngineClient/` | Integration module: HTTP, WS, contract models, seeding, config. **The ONLY module allowed network I/O.** |
| `docs/ENGINE_CONTRACT.md`, `docs/openapi.json` | Engine contract (source of truth) |
| `Seed/slice1_tavern.json` | Game-owned seed data |
| `Config/NpcEngine.ini` | base URL + API key (gitignored) |
| `Scripts/` | Quality-gate scripts |

### NPC map (IDs are STABLE — never rename)
| npc_id | Location | Slice |
|--------|----------|-------|
| `mira_innkeeper` | `loc_tavern` | 1 |
| `lira_fence` | `loc_tavern` | 1 |
| `aldric_merchant` | `loc_market_square` | 2 |
| `captain_sorn` | `loc_guard_barracks` | 2 |
| `old_henryk` | `loc_market_square` | 2 |
Player: `player_demo` (slice-1 default).

---

## Architecture

### Module / dependency model
Dependencies point one way: `Game` → `NpcEngineClient` → contract models. `NpcEngineClient` is a
self-contained runtime module with its own `.Build.cs`.

**Forbidden (each is a bug):**
- No `FHttpModule` / `FWebSocketsModule` / raw sockets outside `NpcEngineClient`.
- No JSON parsing (`FJsonObject`, `JsonUtilities`, `FJsonSerializer`) in the `Game` module. Gameplay
  receives typed USTRUCTs from the dialogue subsystem.
- No engine-contract USTRUCTs (the API-mirror types) defined outside `NpcEngineClient`.
- No hardcoded `npc_id`, URL, or endpoint-path string literals in gameplay. `npc_id` lives on the NPC
  actor as `FName NpcId`; endpoint paths are named constants in the client.
- No blocking the game thread on a network call. All engine calls are async via delegates.

To violate a module rule: stop, write a `DECISIONS.md` entry, wait for approval.

### Blueprint boundary (C++-first)
All logic in C++. Blueprint/editor only for: Animation Blueprints, UMG widget *layout* (over C++ base
widgets), materials, Niagara, the level, MetaHuman setup, thin BP data subclasses for tweakable
defaults. No gameplay logic, no HTTP, no JSON in Blueprint.

## Code style

### Files
- Target **≤400 lines `.cpp`, ≤200 lines `.h`**; hard ceiling **500 `.cpp`**. Prefer many small
  modules/files over megafiles — extract sub-objects/components rather than growing a file. Over the
  ceiling → split before merge, or justify with a top-of-file comment + a `DECISIONS.md` entry.
- One primary type (`UCLASS`/`USTRUCT`/`UENUM`) per matching `.h`/`.cpp` pair.

### Naming (Unreal)
- Types PascalCase with mandatory prefixes: `U` (UObject), `A` (Actor), `F` (struct), `E` (enum),
  `I` (interface), `T` (template). Bools `bPrefixed`. Functions/params PascalCase. Constants `constexpr`/UPPER.
- File name = primary type without prefix (`DialogueSubsystem.h`, not `UDialogueSubsystem.h`).
- Log category: `LogNpcEngine`. `npc_id` *values* stay snake_case (engine contract); the field is `FName NpcId`.

### Includes
IWYU: include what you use, forward-declare in headers, include in `.cpp`. Public headers in `Public/`,
private in `Private/`.

## Documentation
Every `.h`/`.cpp` starts with:
```
// File: <name>
// Module: <Game | NpcEngineClient>
// Purpose: one sentence.
// Net I/O: <yes|no>   (must be 'no' for every file outside NpcEngineClient)
```
Doxygen `/** */` on every public `UCLASS`, `USTRUCT`, `UENUM`, `UFUNCTION`, and any non-obvious
`UPROPERTY`. Private helpers <10 lines with self-evident names may skip. Test names are their own docs.

## Testing

### TDD split
- **`NpcEngineClient` module — STRICT TDD.** Write the failing Automation Spec first (JSON parse of
  both response shapes, ≤1000 + non-empty validation, fallback on timeout/non-2xx, UENUM forward-compat,
  contract USTRUCT round-trip), confirm it fails for the right reason, implement minimal, refactor green.
- **Gameplay actors / components / UMG — smoke + manual**, plus an Automation functional test (eval)
  where feasible (interaction component fires the subsystem; widget rejects empty/oversized input).
- Bug fixes: regression spec first.

### Layout
- `Source/NpcEngineClient/Private/Tests/*.spec.cpp` (`DEFINE_SPEC`) — use the mock transport, never a live engine.
- `Source/DemoGame/Private/Tests/` — functional tests.

### Mock parity (LSP)
The mock HTTP transport must match the real client's contract: same fallback on non-2xx, same parse
path. A mock that returns success where the real client would fall back is invalid.

## Project management files — canonical locations
`project-harness/ISSUES.md`, `DECISIONS.md`, `ROADMAP.md`, `PATTERNS.md` are the only copies. Never
create root-level duplicates.

## Issues log
`ISSUES.md` is the persistent issue log; every session reads and updates it.
- **Find a problem you're not fixing now** → add `## ISSUE-NNN` with Found/Severity(P1|P2|P3)/Where/
  Description/Why deferred/To fix. IDs monotonic, never reused (check `ISSUES.md` and the archive).
- **Fix an existing issue** → mark `## [FIXED] ISSUE-NNN`, add `**Fixed:** YYYY-MM-DD, in <commit/task>`,
  move the entry to `archive/ISSUES_RESOLVED.md`.
- Don't log the current task, or questions (those go to `DECISIONS.md`).

## Task discipline
- **Single-task focus:** working on X, you don't also do Y — log Y in `ISSUES.md` and continue, unless Y blocks X.
- **Bridge/temp files:** add `// TEMPORARY: delete by end of task <name>. Reason: <why>.` and log in `ISSUES.md`; delete on close.
- **Pre-merge checklist** (write the result into your final summary):
  - [ ] New Automation specs pass (client module)
  - [ ] Project compiles (Game + NpcEngineClient), no new warnings
  - [ ] `Scripts/check.ps1` green
  - [ ] No file over the ceiling
  - [ ] File header on every new file; Doxygen on new public API
  - [ ] No net I/O outside `NpcEngineClient`; no JSON in `Game`
  - [ ] USTRUCTs still match `docs/openapi.json` (contract-sync green)
  - [ ] No hardcoded `npc_id`/URL/endpoint literals in gameplay
  - [ ] Deferred work in `ISSUES.md`; non-obvious choices in `DECISIONS.md`; reused patterns in `PATTERNS.md`
  - [ ] Temp files deleted

## Asking before doing
Proceed without asking: bug fixes inside one module, adding tests/docs, adding ISSUES/DECISIONS/PATTERNS entries.
Stop and ask before: changing a public `UFUNCTION`/`UInterface` with callers outside its module; adding a
plugin or module dependency; changing a USTRUCT that mirrors the engine contract; touching `*.Build.cs`/
`*.Target.cs`/CI; deleting a non-temp file you didn't create; violating a module rule.

## Token efficiency
Don't paraphrase the codebase. Act, then summarize in one line. One precise sentence beats three vague ones.
Unsure about a small thing → choose and note in `DECISIONS.md`; stop only for blocking/irreversible matters.

---

## Coding principles  (rules marked **(strict)** are bugs when violated)

### SOLID
- **SRP (strict):** one responsibility per class — model, transport, subsystem/orchestrator, actor,
  component, widget, or test. Never mix.
- **OCP (strict):** new NPCs/locations added via data (DataAsset / Seed JSON), not code edits. A new
  transport (e.g. wiring real WS) is a new class, not edits to the REST client.
- **DIP (strict):** gameplay depends on a `UInterface` (e.g. `INpcDialogueService`), never the concrete
  `UNpcEngineClient`. Composition root = `UGameInstanceSubsystem::Initialize`.
- **ISP (strict):** small interfaces. Don't force a streaming method on a REST-only consumer.
- **LSP (strict):** mock transport matches the real transport's contract.

### Structure
- **Function length (strict):** ≤40 lines. **Nesting (strict):** ≤3 levels — extract named helpers.
- **No magic numbers/strings (strict):** timeouts, caps, endpoint paths, `npc_id`s, enum string values
  are named constants. No raw URL fragments.

### Types & models
- **USTRUCT for boundary data (strict):** all data crossing a module boundary is a `USTRUCT` with
  `UPROPERTY`. No raw `TMap<FString,FString>` or FString-JSON blobs crossing a boundary.
- **UENUM for fixed sets (strict):** the engine's closed sets (action type, expression type) are
  `UENUM`. **Forward-compat:** an unknown string → log + safe default (`speak`/`neutral`), never crash, never drop.

### Error handling (no C++ exceptions — they're disabled)
- Use result structs / `bool`+out-params / `TOptional` and success+error delegates.
- **Fail fast at boundaries (strict):** validate every engine JSON response and all player input on
  receipt — external data is untrusted.
- **Never silently drop a failed request (strict):** every failure → `OnError` or a fallback line, logged.
- **Fallback contract (strict):** timeout/unreachable/non-2xx → canned fallback line, game continues.
  The engine's own `degradation_level != "full"` is surfaced, not hidden. Document the fallback in the
  function comment.

### DI / lifecycle
- No global mutable singletons for stateful objects. Use subsystems (GameInstance/World) with
  `Initialize`/`Deinitialize`. Config may be a read-only accessor.

### Async / threading
- **Async (strict):** all engine I/O via `FHttpModule`; never block the game thread.
- **Game-thread safety (strict):** `UObject`/`AActor` touched only on the game thread. `FHttpModule`
  completion delegates fire on the game thread (safe); if you ever offload work, marshal results back
  with `AsyncTask(ENamedThreads::GameThread, ...)`.

### Observability
- **Structured logging (strict):** `LogNpcEngine` category; `UE_LOG` with key=value context
  (`NpcId`, `PlayerId`, `DurationMs`, `Status`). Never use on-screen debug messages as real logging.
- **Redaction (strict):** never log the API key; never log the full player message in shipping (dev-only verbose).

### Security
- **Input cap (strict):** `player_message` validated `≤ MAX_PLAYER_MESSAGE_CHARS` (1000) and non-empty
  before send.
- **Secrets (strict):** base URL + API key from gitignored `Config/NpcEngine.ini` or env
  (`NPC_ENGINE_URL`/`NPC_ENGINE_API_KEY`); fail fast if missing; never commit; never log.
- **Auth (strict):** client attaches `Authorization: Bearer` on every call except `GET /health`.

### Packaged-build correctness (Unreal-only, strict)
Rules hold in cooked builds, not just the editor. No editor-only API in runtime modules. Config/save
paths use `FPaths` (e.g. `ProjectSavedDir`), never absolute dev paths.

### Content / asset discipline (Unreal-only)
- Asset prefixes: `BP_`, `WBP_`, `M_`, `MI_`, `T_`, `SK_`, `SM_`, `A_`, `DA_`.
- Prefer `TSoftObjectPtr` for heavy assets; avoid hard refs that bloat the cooked memory graph.
- LFS covers binary asset types; never commit `DerivedDataCache/`, `Intermediate/`, `Binaries/`, `Saved/`.

### Performance budget (standing rules)
12GB VRAM ceiling: Ollama in CPU mode during dev (frees VRAM); 1–2 hero MetaHumans per scene, LODs/
cheaper meshes for background NPCs; every engine call async (never block the game thread).

### Contract sync (the two-repo rule, strict)
The USTRUCTs in `NpcEngineClient` mirror `docs/openapi.json`. Changing a contract type updates
`docs/ENGINE_CONTRACT.md` + `docs/openapi.json` + the USTRUCT in the **same change**, with a
`DECISIONS.md` entry. `Scripts/check_contract_sync.py` enforces field presence.
