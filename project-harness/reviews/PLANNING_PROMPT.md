# DemoGame — Review-to-Roadmap Planning Pass

## Brief

You are the **planning agent** in a two-pass review process. The first pass (see `REVIEW_PROMPT.md`)
has already run and produced individual finding files (`REV-001.md` … `REV-NNN.md`) in this directory.

Your job is to:
1. Read all `REV-*.md` files in `project-harness/reviews/`
2. Read the current `project-harness/ROADMAP.md` (understand what phases exist and what is planned)
3. Read the current `project-harness/ISSUES.md` (understand what is already tracked)
4. Produce **Phase 13** entries in the ROADMAP for each finding that requires a new phase,
   and **ISSUES.md additions** for findings that are bugs/debt rather than feature work.

---

## Rules

- **Do not modify completed phases** (Phases 0–10, any checked `[x]` items). Append only.
- **Do not duplicate** findings already in `ISSUES.md` (ISSUE-001 through ISSUE-020).
- **Preserve ROADMAP structure**: headless C++ blocks + human tails, quality gate lines, phase
  prerequisites, independently demoable goal line — match the existing phase format exactly.
- Phase 12 (appearance hardening) is already in the ROADMAP as planned. Do not duplicate it.
- New ISSUES.md entries must follow the existing format: `## ISSUE-NNN` with monotonic ID, Found date,
  Severity, Where, Description, Why deferred, To fix.

---

## Grouping Strategy

Group review findings into roadmap work this way:

| Finding type | Where it goes |
|--------------|--------------|
| P1 architectural blocker that blocks Slice 2 | New Phase 13 (or Phase 12 sub-block) |
| P2 technical debt that creates rework before Slice 2 | ISSUES.md (P2 severity) or Phase 13 |
| P3 quality/maintainability debt | ISSUES.md (P3 severity) |
| Dead code sweep | Phase 12 Block B or a new Phase 12 sub-block |
| Scalability redesigns needed before full game | New Phase 14 (Post-Slice-2 architecture work) |
| Stub implementations needed for full game | New Phase 15 (Completeness pass) |
| Asset integration gaps | Phase 12 Block A or new sub-block |
| Contract coupling mitigations | Phase 13 or new phase |

Use your judgment — if multiple P1 findings are all about the same system (e.g. quest data-driven
redesign), group them into one phase with multiple tasks rather than separate phases.

**Sequence using the `horizon` and `effort` frontmatter fields, not just priority.** A `full-game` P1
that everything else depends on (e.g. the single-source-of-truth consolidation from Dimension 11) should
come *early* even though it doesn't bite today, because every NPC added before it doubles the migration
cost later. Cheap `effort: S` fixes that unblock or de-risk bigger work should be front-loaded. Call out
any ordering dependencies a finding declares in its `Related` section.

---

## Output

Write the following:

1. **Append to `project-harness/ROADMAP.md`**: New phases (Phase 13+) in the same format as existing
   phases. Each phase must have: Goal, Independently demoable, Prerequisites, Quality gate, and a
   headless C++ task list. Include human tails where editor work is involved.

2. **Append to `project-harness/ISSUES.md`**: New `## ISSUE-NNN` entries for findings that are bugs
   or debt rather than feature phases. Follow the format exactly, starting at ISSUE-021.

3. **Produce `project-harness/reviews/PLANNING_SUMMARY.md`**: A brief (max 2 pages) overview of:
   - How many findings were P1/P2/P3
   - Which phases were added and why
   - Which findings were deferred to ISSUES.md and why
   - The recommended sequence for tackling the new work (what to do first, and why)

---

## Context on the Project

**Goal of expansion**: The demo is Slice-1 (5 NPCs, 4 locations, single investigation arc). The next
milestone is a **real shipped game (~100+ NPCs, 30+ locations)**. Architectural work that blocks that
scale is P1.

**NPC Engine contract**: The backend API is **evolving** — new endpoints and field additions are
expected. Findings about contract coupling brittleness are real risks, not hypotheticals.

**Author's working style**: Solo developer using Claude Code for most implementation. Headless C++
phases should be implementable by Claude without editor access. Human tails are kept minimal.

**Current state**: Phase 12 is planned but not started. The `feat/slice1-tavern` branch is the active
branch. Main branch is `main`.
