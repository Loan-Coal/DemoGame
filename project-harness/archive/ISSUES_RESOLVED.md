# Resolved Issues (archive)

Append-only. Fixed issues are moved here from `ISSUES.md` (keep the original ISSUE-NNN id and add a
`**Fixed:** YYYY-MM-DD, in <commit/task>` line). Never reuse a retired id.

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
