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

## ISSUE-011: No interaction prompt before opening NPC dialogue
**Found:** 2026-06-25
**Severity:** P3
**Where:** `Source/DemoGame/DemoGameCharacter.cpp` (`OpenDialogue` / interact path), NPC actors
**Description:** Interacting with an NPC opens the dialogue widget directly with no on-screen prompt (e.g. "Press E to talk") and no confirmation popup when in range. The player has no affordance telling them an NPC is interactable or which key starts dialogue. Noted during the floating-cube / dialogue-UI fix; user confirmed it is acceptable for the current greybox stage.
**Why deferred:** Out of scope for the current task (grounding + dialogue-panel visibility). Dialogue is fully reachable without the prompt; this is discoverability polish, not a blocker.
**To fix:** Add a small world-space or screen-space prompt that appears when an NPC is within `InteractRadius` (reuse `FindNearestNpc`), showing the interact key. Hide it once dialogue opens.

## ISSUE-012: No free female MetaHuman-native medieval clothing option exists
**Found:** 2026-06-25
**Severity:** P2
**Where:** Asset acquisition Task B — Mira and Lira outfit slots
**Description:** All confirmed female MetaHuman-rigged medieval clothing on Fab is paid (~$3–50 per pack). No CC0 or free female medieval garment exists for MetaHuman. DevonLux's free CC-BY library on Sketchfab (5 Piece Leather Peasant, Heavy Armor, Scalemail, Cloth Armor) covers only "Tall, Normal-Weight, Male" MetaHumans. This means a minimum cash purchase is required for Mira and Lira regardless of the chosen quality tier.
**Why deferred:** Task B research only — purchasing is a human gate. Not a code issue.
**To fix:** Human selects and purchases one of the shortlisted options from `metahuman-clothing.md`. Budget minimum: Yasin ERHAN Female & Male Rustic (~$3–4); recommended quality path: PolyWear Resizable Collection (~$20–30, covers both Mira and multiple other NPCs).

## ISSUE-013: Lira's hooded cloak has no direct MetaHuman-native free/cheap equivalent
**Found:** 2026-06-25
**Severity:** P2
**Where:** Asset acquisition Task B — Lira outfit slot; `project-harness/asset-shortlists/metahuman-clothing.md`
**Description:** Lira's role requires a dark hooded commoner garb for the dim back room. No MetaHuman-native paid or free asset was found with a dedicated hood/cloak garment. The closest option (Medieval Priest & Nun on Fab) is a UE5 Mannequin rig that requires an IK Retarget step (~1–2h of manual editor work) to bind to the MetaHuman skeleton. The fallback (Meta Clothes Designer Dress III, ~$49.99) is MetaHuman-native but has no hood — the "hooded" effect relies entirely on the dim `L_TavernBack` lighting and material darkening.
**Why deferred:** Task B is research only; no assets purchased yet. The retarget-quality question can only be answered after a human performs the retarget and inspects the result in-editor.
**To fix:** (1) Human tests the Medieval Priest & Nun retarget (IK Retargeter, Quinn → MetaHuman, ~1–2h). (2) If retarget quality is unacceptable: fall back to Meta Clothes Designer Dress III + dark material + L_TavernBack chiaroscuro lighting — the silhouette alone (back-room, dim, behind the bar) carries the "fence" read. (3) Long-term: commission or create a dedicated hooded cloak for MetaHuman if the project scales.

## ISSUE-014: GrubyCommander and Medieval Priest & Nun prices unconfirmed (Fab 403)
**Found:** 2026-06-25
**Severity:** P3
**Where:** `project-harness/asset-shortlists/metahuman-clothing.md` — Aldric/Henryk and Lira picks
**Description:** Fab.com listing pages return HTTP 403 for unauthenticated fetches. The prices for GrubyCommander Rustic Medieval Granular Modular and Medieval Priest & Nun could not be verified this research run. The shortlist includes price estimates (GrubyCommander: ~$20–50; Priest & Nun: ~$50–150 based on being a "stripped-down" version of the $449 Modular Medieval V2) but these are unconfirmed. Actual prices must be verified in-editor before purchase.
**Why deferred:** Requires Epic login + in-editor Fab panel to verify. Research-only blocker; no code impact.
**To fix:** Human opens the Fab plugin (Windows → Fab), searches for each asset by name, and confirms price before purchasing. If either price exceeds budget, select the corresponding fallback from the shortlist.

## ISSUE-015: Legacy fixed-body MetaHuman clothing is not "drop-in" on UE5.6+ parametric MetaHumans
**Found:** 2026-06-25
**Severity:** P2
**Where:** Asset acquisition Task B — all fixed skeletal-mesh clothing picks (DevonLux free CC-BY, Meta Clothes Designer I/II/III, Medieval Priest & Nun); `project-harness/asset-shortlists/metahuman-clothing.md`
**Description:** The UE5.6+ MetaHuman is parametric (adjustable body shape) and the official pipeline moved to **Chaos Outfit Assets** that auto-conform. Verified this run from current sources:
- Official Hair & Clothing Controls doc (https://dev.epicgames.com/documentation/en-us/metahuman/hair-and-clothing-controls): only parametric outfits auto-resize — *"Wearing an outfit will cause it to automatically resize to fit the current body... if further changes to the body shape are made,"* whereas a SkeletalMesh garment **does not** auto-adjust. The wardrobe system also rejects skeletal clothing *"created using an incompatible skeleton"* (validation; can be disabled in Project Settings → Wardrobe → Enable Wardrobe Item Validation).
- UE5.6 removed the legacy **+2 cm MetaHuman foot offset** → footwear authored pre-5.6 sits below the ground plane (search-confirmed via Epic forum / yelzkizi pipeline notes).
- UE5.7 in-editor Creator's new `SKM_MHC_*` body meshes show **retargeting deformation regressions** even when sharing `metahuman_base_skel` (search-confirmed).
The body skeleton (`metahuman_base_skel`, an extended UE5-Mannequin skeleton) is still shared, so legacy clothing *attaches*, but it (a) will NOT conform if the MetaHuman body shape is adjusted, (b) is skinned to ONE fixed body type (e.g. DevonLux = "Tall, Normal-Weight, Male" only), (c) may need a vertical offset fix for shoes, and (d) may fail wardrobe validation. So "outdated clothing unusable" is partly true: not broken bones, but no longer drop-in.
**Why deferred:** Task B is research-only; impact is verified per-asset only by a human skin test in-editor.
**To fix:** Prefer **parametric / Chaos Outfit Asset** items (PolyWear, GrubyCommander — advertised "MetaHuman Creator parametric", recent 2025 updates) as the latest-MetaHuman-safe path. For fixed skeletal-mesh items (incl. all free DevonLux): keep the MetaHuman body at (or near) the asset's authored body type, attach via SkeletalMeshComponent + Leader Pose (not as a validated wardrobe item, or disable validation), and correct the foot height if shoes clip the floor. Confirm each asset's last-updated date is post-5.6 before relying on it. This is the strongest reason the recommended *quality* path is parametric, and a real caveat on the free path.

## [FIXED] ISSUE-016: NpcAppearance.spec.cpp missing `#if WITH_DEV_AUTOMATION_TESTS` guard
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 1e86dd0 (Phase 12 B1)
**Severity:** P3
**Where:** `Source/DemoGame/Private/Tests/NpcAppearance.spec.cpp`
**Description:** This is the only `*.spec.cpp` in the project without the `#if WITH_DEV_AUTOMATION_TESTS` / `#endif` wrapper (all 11 others have it). The `DEFINE_SPEC` body therefore compiles into Test/Shipping/cooked configurations instead of editor/dev only. Caught reviewing the Phase 7 appearance seam; gate is green because dev builds compile it fine.
**Why deferred:** No correctness impact in the Development editor build the gate runs; affects only cooked-build hygiene. One-line wrap.
**Fix:** Wrapped NpcAppearance.spec.cpp (and the also-unguarded FacialExpressionMapper.spec.cpp) with the guard. Added `missing_spec_automation_guard` rule to `Scripts/check_rules.py` so the gate catches any future omission.

## [FIXED] ISSUE-017: ANpcGreyboxActor::TrySpawnAvatar synchronously loads the avatar class on the game thread
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 9b39022 (Phase 12 A4)
**Severity:** P2
**Where:** `Source/DemoGame/NPC/NpcGreyboxActor.cpp` (`TrySpawnAvatar`, `AvatarClass.LoadSynchronous()`)
**Description:** The avatar swap path calls `LoadSynchronous()` inside `BeginPlay`. Harmless today (registry is empty → cubes only), but this is exactly the code that fires once a MetaHuman BP path is added to `NpcAppearance`. Synchronously loading a multi-MB MetaHuman skeletal mesh on the game thread will cause a visible begin-play hitch, against the "never block the game thread" rule.
**Fix:** Replaced `LoadSynchronous()` with `UAssetManager::GetStreamableManager().RequestAsyncLoad()` + completion lambda guarded by `TWeakObjectPtr`. `EndPlay` releases the `FStreamableHandle`. Cube stays visible until load completes.

## [FIXED] ISSUE-018: FNpcSpawnRecord and FGreyboxLocation USTRUCT fields lack UPROPERTY
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 5c945b6 (Phase 12 A3)
**Severity:** P3
**Where:** `Source/DemoGame/World/NpcSpawnerSubsystem.h` (`FNpcSpawnRecord`), `Source/DemoGame/World/GreyboxWorldSubsystem.h` (`FGreyboxLocation`)
**Description:** Both structs declare `USTRUCT()` + `GENERATED_BODY()` but none of their fields carry `UPROPERTY`. The `TSoftClassPtr<AActor> AvatarClass` in `FNpcSpawnRecord` is therefore not GC-tracked, and neither struct is reflection/serialise-safe.
**Fix:** Added `UPROPERTY()` to all 5 fields of `FNpcSpawnRecord` and all 4 fields of `FGreyboxLocation`.

## [FIXED] ISSUE-019: Memory badge fallback can render a raw node ID to the player
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 4de45b6 (Phase 12 B2)
**Severity:** P3
**Where:** `Source/DemoGame/Dialogue/DialogueWidgetBase.cpp` (`OnMemoriesRecalled` handler)
**Description:** The badge lookup chain terminated with `FText::FromString(Memories[0])` (raw ID). `MemoryBadgeDefaults.h` states raw IDs must never be shown to the player.
**Fix:** Terminal fallback replaced with `UE_LOG(Verbose)` + early return (badge stays `Collapsed`). Also corrected the `MemoryBadgeLookup` UPROPERTY doc comment in `DialogueWidgetBase.h`.

## [FIXED] ISSUE-020: slice1_tavern.json tavern name "The Rusty Flagon" conflicts with locked "The Broken Flagon"
**Found:** 2026-06-25
**Fixed:** 2026-06-26, in commit 7be4736 (Phase 12 B3 / DEC-043)
**Severity:** P3
**Where:** `Seed/slice1_tavern.json`
**Description:** DEC-017 locked the tavern name to "The Broken Flagon". The legacy `slice1_tavern.json` said "The Rusty Flagon".
**Fix:** Retired `slice1_tavern.json` entirely (along with `UNpcEngineSeedClient`). `NpcEngine.SeedWorld` using `DemoWorld_v1.json` is the sole seed path.

<!--
IDs are monotonic and never reused — check this file AND archive/ISSUES_RESOLVED.md before numbering.
When fixed: mark `## [FIXED] ISSUE-NNN`, add `**Fixed:** YYYY-MM-DD, in <commit/task>`, then move the
entry to archive/ISSUES_RESOLVED.md.
-->
