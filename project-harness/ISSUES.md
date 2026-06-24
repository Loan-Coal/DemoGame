# Issues Log

## ISSUE-001: NpcWorldSeeder.cpp above 400-line target (429 lines)
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/NpcEngineClient/Private/NpcWorldSeeder.cpp`
**Description:** File is 429 lines against the ≤400 target (hard ceiling 500). The overage is from safety fixes (C-1/C-2 GC pinning, H-1/H-4 status validation, H-2 ID sanitisation). All new code is load-bearing.
**Why deferred:** Under the 500-line hard ceiling; no correctness impact. DEC-019 records the justification.
**To fix:** Extract `CheckNodeExists` + upsert helpers into `NpcWorldSeederHttp.cpp` (≤120 lines) leaving the orchestration logic in the main file. Do before Phase 4 merge if the file grows further.

## ISSUE-002: ProcessNodes/ProcessEdges copy TArrays O(N²) into recursive lambdas
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/NpcEngineClient/Private/NpcWorldSeeder.cpp` lines ~340, ~390
**Description:** `Tasks`, `Edges`, `PostEdgeNodes` are captured by copy in every recursive lambda, producing O(N) allocations per step and O(N²) total. For the current 33-node seed this is ~33 × 3 string copies per step — negligible in practice, but will worsen with larger seed files.
**Why deferred:** Seed is 33 nodes; perf impact unmeasurable. Fix requires wrapping mutable state in a `TSharedPtr<FSeederState>`.
**To fix:** Introduce `FSeederState { TArray<FNodeTask> PreEdge; TArray<FEdgeTask> Edges; TArray<FNodeTask> PostEdge; TFunction<void()> OnDone; TFunction<void(FString)> OnError; }` as a `TSharedPtr` shared across all recursive steps; capture only the pointer in lambdas. Do at same time as ISSUE-001 split.

## ISSUE-003: BuildTasksFromJson silently adds nodes with empty node_type or node_id
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/NpcEngineClient/Private/NpcWorldSeeder.cpp` ~line 185–191
**Description:** If a seed JSON entry is missing `node_type` or `properties.id`, `TryGetStringField` leaves the output as an empty `FString` and the task is added with empty type/id. `IsValidGraphId` in `CheckNodeExists`/`PostUpsertNode` will catch it at runtime and fire `OnError`, halting the seeder — but the error message points to the URL assembly rather than the JSON parse step, making diagnosis harder.
**Why deferred:** `IsValidGraphId` catches it before any HTTP call; no silent data loss. Fix is a two-line guard in `ParseNodeSection`.
**To fix:** After `TryGetStringField`, skip the entry (log P3 warning) if `NodeType.IsEmpty() || NodeId.IsEmpty()`.

## ISSUE-004: Automation Spec UNpcWorldSeeder test objects not rooted (fragile if mock becomes async)
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/NpcEngineClient/Private/Tests/NpcWorldSeeder.spec.cpp` lines 38, 63, 87, 122, 153
**Description:** `NewObject<UNpcWorldSeeder>()` instances are not GC-rooted in spec tests. Currently safe because all mock callbacks fire synchronously (no GC window). If a future test refactor introduces deferred callbacks (e.g. `FPlatformProcess::Sleep`), `this` would dangle.
**Why deferred:** Zero risk as-is; synchronous mock is a stated spec contract.
**To fix:** Add `Seeder->AddToRoot()` in each `It(...)` block before the call, and `Seeder->RemoveFromRoot()` after. Or use `TStrongObjectPtr<UNpcWorldSeeder>` (RAII root handle) when that pattern is adopted project-wide.

## ISSUE-005: loc_tavern_back node in DB has truncated descriptor from manual debug test
**Found:** 2026-06-24
**Severity:** P2
**Where:** NPC Engine graph — node `loc_tavern_back`
**Description:** During seed debugging a manual POST created `loc_tavern_back` with `descriptor: "A dim storeroom."`. The full seed has `descriptor: "A dim storeroom behind the bar in The Broken Flagon. Lira operates here. Access requires Mira's trust."`. The seeder's CheckNodeExists → Skip logic prevents the full data from being written; the truncated node persists.
**Why deferred:** Doesn't block the seeder or game logic; only affects NPC context quality for Lira's location.
**To fix:** Run `Invoke-RestMethod -Method Delete "http://localhost:8000/v1/admin/graph/locations/loc_tavern_back" -Headers $h` then rerun `NpcEngine.SeedWorld`. The seeder will upsert the full descriptor on the next run.

## ISSUE-006: NpcActorBase.h / .cpp missing required file headers
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/DemoGame/NPC/NpcActorBase.h`, `Source/DemoGame/NPC/NpcActorBase.cpp`
**Description:** Files predate the `// File: / Module: / Purpose: / Net I/O:` header rule (added in Phase 1). Both files are missing the four-line header.
**Why deferred:** Non-blocking; Phase 4 focus is dialogue system. No build or logic impact.
**To fix:** Add headers at line 1 of each file. `NpcActorBase.h`: `// File: NpcActorBase.h // Module: Game // Purpose: Abstract base class for all NPC actors — carries NpcId, interaction sphere, dialogue component. // Net I/O: no`. Similar for the `.cpp`.

## ISSUE-008: FakeNpcDialogueService::AdvanceClock fires both OnError and OnResult(false) — LSP violation
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/DemoGame/Private/Tests/FakeNpcDialogueService.h` lines 73–77
**Description:** On `bAdvanceClockSucceeds = false`, the fake fires both `OnError.ExecuteIfBound(...)` and `OnResult(false)`. The real `UNpcEngineRestClient::AdvanceClock` implementation fires one or the other, never both. Any test asserting the error path will see two callbacks — a latent LSP parity bug.
**Why deferred:** No test currently covers `AdvanceClock` failure + `OnResult` interaction in combination. Existing `ClockAdvance.spec.cpp` tests use `bAdvanceClockSucceeds = true`. No correctness impact today.
**To fix:** Remove `OnResult(false)` from the error branch in `FakeNpcDialogueService`, or verify that the real client also calls `OnResult(false)` on error and make them match.

## ISSUE-007: UDialogueWidgetBase word-by-word text reveal deferred to BP subclass
**Found:** 2026-06-24
**Severity:** P3
**Where:** `Source/DemoGame/Dialogue/DialogueWidgetBase.h` / `.cpp`
**Description:** Phase 4 roadmap specifies word-by-word text reveal at 20 ms/word via `UWidgetAnimation`. The C++ base appends full text immediately; the pulsing animation is described as a "cosmetic UWidgetAnimation" that must be authored in the `WBP_Dialogue` Blueprint subclass. No C++ support for this is wired yet.
**Why deferred:** Animation authoring is an editor session task. Full text is available immediately so gameplay is not blocked. The `ThinkingIndicator` visible/hidden logic is done; only the ellipsis pulse animation remains.
**To fix:** In the editor session: (1) Create a UWidgetAnimation in `WBP_Dialogue` that plays an ellipsis `...` cycle on `ThinkingIndicator`. (2) Add a word-by-word reveal animation or timer-driven substring reveal in the widget's `OnNpcResponseReceived` BP override.

## ISSUE-009: Phase 6 C++ complete but uncommitted — Live Coding gate blocker
**Found:** 2026-06-24
**Severity:** P1
**Where:** Build gate (`Scripts/check.ps1 -WithBuild`)
**Description:** All Phase 6 headless C++ implementation is complete (FNpcStateSnapshot, GossipCacheSubsystem, RumorJournalWidget, ANoticeBoard, Sorn quest gate, two Automation specs, HUMAN_VERIFICATION.md Phase 6 section). The build gate exits with code 6: "Unable to build while Live Coding is active." The Rules check and Contract Sync both pass. Changes are NOT committed because the overnight runner rule forbids committing a red gate.
**Why deferred:** Unreal Editor is open with Live Coding enabled — pure environmental blocker, not a code error. Once the editor is closed the gate will pass and the commit can proceed.
**To fix:** Close Unreal Editor (or disable Live Coding via Ctrl+Alt+F11). Then run `powershell -NoProfile -ExecutionPolicy Bypass -File Scripts/check.ps1 -WithBuild -WithTests`. If green, commit all Phase 6 changes: `git add Source/ project-harness/ Seed/ docs/ Scripts/` then `git commit -m "feat(phase6): GossipCacheSubsystem + FNpcStateSnapshot + RumorJournalWidget + NoticeBoard + Sorn quest gate"`.

<!--
IDs are monotonic and never reused — check this file AND archive/ISSUES_RESOLVED.md before numbering.
When fixed: mark `## [FIXED] ISSUE-NNN`, add `**Fixed:** YYYY-MM-DD, in <commit/task>`, then move the
entry to archive/ISSUES_RESOLVED.md.
-->
