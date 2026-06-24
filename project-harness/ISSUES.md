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

<!--
IDs are monotonic and never reused — check this file AND archive/ISSUES_RESOLVED.md before numbering.
When fixed: mark `## [FIXED] ISSUE-NNN`, add `**Fixed:** YYYY-MM-DD, in <commit/task>`, then move the
entry to archive/ISSUES_RESOLVED.md.
-->
