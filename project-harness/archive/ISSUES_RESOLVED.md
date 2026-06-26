# Resolved Issues (archive)

Append-only. Fixed issues are moved here from `ISSUES.md` (keep the original ISSUE-NNN id and add a
`**Fixed:** YYYY-MM-DD, in <commit/task>` line). Never reuse a retired id.

## [FIXED] ISSUE-009: Phase 6 C++ complete but uncommitted — Live Coding gate blocker
**Found:** 2026-06-24
**Fixed:** 2026-06-25, in commit `8a2f9bb` (chore: baseline before overnight run — included Phase 6 code as "prior-session code"). Build gate confirmed PASS on 2026-06-25 with editor closed.
**Severity:** P1
**Where:** Phase 6 C++ files (DialogueComponent, DialogueWidgetBase, etc.)
**Description:** Phase 6 code existed in the working tree but was not committed because Live Coding kept the editor open; the `abort if editor open` gate was added to Scripts to prevent false-green gates. ISSUE-009 was marked stale in session 2026-06-25 after confirming all Phase 6 files were present in `8a2f9bb`.

## [FIXED] ISSUE-010: Five Automation tests fail under headless run (root-caused, not environmental)
**Found:** 2026-06-25
**Fixed:** 2026-06-25, in task "Fix BP_ThirdPersonCharacter compile + 5 test failures"
**Severity:** P2
**Where:** `NpcEngine.Client.WorldSeeder.Halt on error`; `NpcEngine.Game.DialogueManager.SubmitPlayerMessage` (OnNpcSpoke / OnDialogueError / session_id, 3 tests); `NpcEngine.Game.NpcWorldSubsystem.OnPlayerArrived` (AdvanceClock graceful-failure).
**Description:** Five tests failed under `Automation RunTests NpcEngine` (`-nullrhi -testexit`). The initial guess (latent/environmental) was wrong; two distinct root causes were found.
**Root cause + fix (two mechanisms):**
1. **Error-log auto-fail (2 tests).** `WorldSeeder.Halt on error` and `NpcWorldSubsystem.AdvanceClock failure` exercise error paths that emit `UE_LOG(..., Error, ...)` ([NpcWorldSeeder.cpp:377](../../Source/NpcEngineClient/Private/NpcWorldSeeder.cpp), [NpcWorldSubsystem.cpp:144](../../Source/DemoGame/World/NpcWorldSubsystem.cpp)). UE's automation framework auto-fails any test that logs an Error unless it declares `AddExpectedError`. Assertions actually passed; the logged Error failed them. (Contrast: `DialogueComponent` fallback tests hit the same path but log at *Warning* → passed.) **Fix:** added `AddExpectedError(..., Contains, 0)` to both `It`s. Production code untouched.
2. **Stale tests after Phase 4 refactor (3 tests).** `DialogueManager::SubmitPlayerMessage` was changed to delegate to the NPC's `UDialogueComponent` when present; `ATestNpcActor` inherits one, so the manager-injected fake was bypassed (component had no service/world → fallback, not canned response). **Fix:** `MakeNpc()` now calls `DialogueComponent->DestroyComponent()` so the manager exercises its direct-service path with the injected fake; original assertions hold. The component-delegation path needs a world for the component→manager broadcast and is covered by `DialogueComponent.spec` + PIE. A world-based integration test for that path is optional future work.
**Verification:** full build clean; `Automation RunTests NpcEngine` → 53 tests completed, 0 Fail/Error. Related: [[ISSUE-008]] (`FakeNpcDialogueService` double-callback) remains open but does not affect these now-green tests.

## [FIXED] ISSUE-002: DialogueManager depended on the concrete client, not an interface (DIP)
**Found:** 2026-06-23
**Fixed:** 2026-06-23, in task "ISSUE-002: DIP via INpcDialogueService"
**Severity:** P3
**Where:** `Source/DemoGame/Dialogue/DialogueManager.{h,cpp}`
**Description:** Gameplay held/constructed the concrete `UNpcEngineRestClient`, violating the strict DIP rule.
**Fix:** Introduced `INpcDialogueService` (`UINTERFACE(NotBlueprintable)`, NpcEngineClient module); `UNpcEngineRestClient` implements it. New `UNpcEngineServiceSubsystem` (GameInstance composition root) owns the concrete client and exposes it as `TScriptInterface<INpcDialogueService>`. `DialogueManager` now stores the interface, resolves it lazily from the GI subsystem, and has a `SetDialogueService()` test seam. The redundant PC `NpcSmokeTest` was deleted (use `NpcEngine.Smoke`). Result: `rg UNpcEngineRestClient Source/DemoGame` = 0 hits. Verified: build clean + 4 new `NpcEngine.Game.DialogueManager` specs (success/error/no-op/session) pass headless against a synchronous `UFakeNpcDialogueService`. See DEC-013.

## [FIXED] ISSUE-001: Smoke `Exec` can't route under the default ThirdPerson GameMode
**Found:** 2026-06-23
**Fixed:** 2026-06-23, in task "bring-up step 4 — NpcEngine.Smoke console command + first client spec"
**Severity:** P3
**Where:** `Source/DemoGame/DemoGamePlayerController.cpp` (`NpcSmokeTest`, `UFUNCTION(Exec)`); active GameMode `BP_ThirdPersonGameMode`
**Description:** The PlayerController `Exec` smoke didn't route because `BP_ThirdPersonGameMode` doesn't use `ADemoGamePlayerController`.
**Fix:** Added `Source/NpcEngineClient/Private/NpcEngineSmokeCommand.cpp` registering `NpcEngine.Smoke` as a GameMode-independent `FAutoConsoleCommandWithWorld` that drives `UNpcEngineRestClient` directly. Verified live headless: health OK + Mira reply, `DegradationLevel=full`, `=== NpcEngine.Smoke PASS ===`. The old PC `Exec NpcSmokeTest` remains as a convenience but is now redundant.

## [FIXED] ISSUE-016: NpcAppearance.spec.cpp missing `#if WITH_DEV_AUTOMATION_TESTS` guard
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 1e86dd0 (Phase 12 B1)
**Severity:** P3
**Where:** `Source/DemoGame/Private/Tests/NpcAppearance.spec.cpp`
**Description:** Only spec file without the `#if WITH_DEV_AUTOMATION_TESTS` guard; compiled into cooked/shipping builds.
**Fix:** Wrapped NpcAppearance.spec.cpp and FacialExpressionMapper.spec.cpp with the guard. Added `missing_spec_automation_guard` rule to `Scripts/check_rules.py`.

## [FIXED] ISSUE-017: ANpcGreyboxActor::TrySpawnAvatar synchronously loads the avatar class on the game thread
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 9b39022 (Phase 12 A4)
**Severity:** P2
**Where:** `Source/DemoGame/NPC/NpcGreyboxActor.cpp`
**Description:** `LoadSynchronous()` in `BeginPlay` would hitch the game thread when a MetaHuman BP is wired.
**Fix:** Replaced with `UAssetManager::GetStreamableManager().RequestAsyncLoad()` + completion lambda guarded by `TWeakObjectPtr`. `EndPlay` releases the `FStreamableHandle`.

## [FIXED] ISSUE-018: FNpcSpawnRecord and FGreyboxLocation USTRUCT fields lack UPROPERTY
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 5c945b6 (Phase 12 A3)
**Severity:** P3
**Where:** `NpcSpawnerSubsystem.h` (`FNpcSpawnRecord`), `GreyboxWorldSubsystem.h` (`FGreyboxLocation`)
**Description:** USTRUCT fields without `UPROPERTY` — not GC-tracked, not reflection-safe.
**Fix:** Added `UPROPERTY()` to all 5 fields of `FNpcSpawnRecord` and all 4 fields of `FGreyboxLocation`.

## [FIXED] ISSUE-019: Memory badge fallback can render a raw node ID to the player
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 4de45b6 (Phase 12 B2)
**Severity:** P3
**Where:** `Source/DemoGame/Dialogue/DialogueWidgetBase.cpp`
**Description:** `FText::FromString(Memories[0])` terminal fallback exposed raw snake_case memory keys to the player.
**Fix:** Terminal fallback replaced with `UE_LOG(Verbose)` + early return (badge stays `Collapsed`). Also corrected `MemoryBadgeLookup` UPROPERTY doc comment.

## [FIXED] ISSUE-020: slice1_tavern.json tavern name conflicts with locked lore name
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 7be4736 (Phase 12 B3 / DEC-043)
**Severity:** P3
**Where:** `Seed/slice1_tavern.json`
**Description:** Legacy seed file used "The Rusty Flagon"; DEC-017 locked the name to "The Broken Flagon".
**Fix:** Retired `slice1_tavern.json` and `UNpcEngineSeedClient` entirely. `NpcEngine.SeedWorld` is the sole seed path.
