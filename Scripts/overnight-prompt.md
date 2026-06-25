You are running UNATTENDED in a headless overnight loop. A driver script invokes you with
this prompt in a FRESH session, you complete ONE unit of work, you STOP, and the script
invokes a new fresh session for the next unit. State is carried entirely in files (ROADMAP
checkboxes, git history, HUMAN_VERIFICATION.md) — never assume memory of a previous session.

## Your job this invocation: advance the roadmap by ONE phase, headlessly.

Follow the `/expand-next` discipline (read project-harness/CLAUDE.md — every rule is binding;
strict TDD for NpcEngineClient: failing Automation Spec first, confirm it fails for the right
reason, minimal implementation, refactor green). But with these OVERRIDES for unattended mode:

### 1. Pick the target phase
Read `project-harness/ROADMAP.md`. Every phase is split into a **headless C++ block** and a thin
**human tail** (`[EDITOR SESSION]` blocks + steps tagged `(human — …)`: MetaHuman/material/level art
and live-LLM playtests). Find the FIRST phase that still has at least one unchecked `[ ]` step that is
implementable HEADLESSLY (C++, tests, JSON/data files, docs). Skip the human-tail steps (see §3). If a
phase's only remaining steps are its human tail, record them per §3 and move to the next phase — a
manual tail NEVER blocks the loop.

### 2. Do the headless work — full TDD, full gate
- Implement every headless `[ ]` step in that phase, in order, one commit per step.
- After EACH step, run the FULL gate with the build INCLUDED — this exact command:
  `powershell -NoProfile -ExecutionPolicy Bypass -File Scripts/check.ps1 -WithBuild -WithTests`
  It must print `CHECK: PASS` with the **Build** gate showing PASS (not SKIP) before you commit.
- MANDATORY — the `-WithBuild` flag is NON-NEGOTIABLE. Running `check.ps1` without `-WithBuild`
  SKIPs compilation and falsely reports PASS. NEVER commit a phase whose build you have not seen
  pass. "Rules + contract checks are clean" is NOT a green gate — the C++ must compile.
- If the Build gate prints SKIP (e.g. `Build.bat not found`, or exit code 6 "Unable to build
  while Live Coding is active" / editor open), you CANNOT verify the build. Treat the phase as
  BLOCKED: `git restore` all uncommitted changes, log the blocker in `project-harness/ISSUES.md`
  with the next free ISSUE id, make NO code commit, and emit the BLOCKED status line. Do NOT
  commit code you could not compile.
- If the gate fails on a real error: fix it. If unfixable after genuine effort, BLOCKED as above.
- Tick the `[x]` box in ROADMAP for each completed step, in the same commit (only after green).

### 3. Human-tail steps (editor + live verification) — LOG, do not halt
Any step in a phase's human tail — requiring the Unreal Editor (placing actors, authoring
DataAssets/MetaHumans, laying out UMG widgets, building art levels, materials, "[EDITOR SESSION]"
blocks) OR a live-LLM / PIE playtest ("manual"/"PIE"/"human — …" verification) — CANNOT be done
headlessly. Log it and keep going; do NOT treat it as "work remaining" that blocks advancing. For each:
- Append a section to `project-harness/HUMAN_VERIFICATION.md` (follow the FORMAT comment at
  the bottom of that file). Copy the editor instructions VERBATIM from the ROADMAP
  "[EDITOR SESSION]" block — exact actor names, NpcIds, widget bind names, property values.
- Leave the ROADMAP step unchecked but annotate it: change `- [ ]` to `- [ ] (human — see HUMAN_VERIFICATION.md)`.
- Do NOT halt. Continue with the remaining headless steps in the phase.

### 4. Dependencies & decisions
- If a headless step depends on a 🔶 unapproved entry in `project-harness/DECISIONS.md`, you
  MAY make the reasonable engineering choice and record it as a new approved DEC- entry
  (unattended autonomy — do not block waiting for human approval on small/reversible matters).
  EXCEPTION: if the step requires a module-rule violation, a new plugin/module dependency, a
  graph-schema change, a contract-USTRUCT change, or touching *.Build.cs/*.Target.cs/CI —
  do NOT do it. Record it in HUMAN_VERIFICATION.md as a human decision and skip that step.
- Verifying live-engine behavior (Docker on localhost:8000) is NOT available headless — treat
  as an editor/human step (§3).

### 5. Commit rules (STRICT)
- Commit per step on the CURRENT branch. Do NOT create branches. Do NOT push. Do NOT amend.
- `git add` ONLY: `Source/`, `Seed/`, `docs/`, `project-harness/`, `Scripts/`. NEVER
  `git add Content/` or `git add -A` (Content/ holds the human's binary editor assets).
- Conventional commit messages: `feat(phaseN): ...` / `test(phaseN): ...` / `docs(phaseN): ...`.

### 6. When to STOP this invocation
STOP (end your turn) as soon as ONE of these is true:
- You completed all headless steps of ONE phase (committed, gate green). Stop — the script
  starts a fresh session for the next phase. Do NOT continue into the next phase in this session.
- No phase has any headless `[ ]` step remaining (everything left is editor/human work). In
  this case make NO commit and end with the EXACT line: `OVERNIGHT-RUNNER: NO HEADLESS WORK REMAINING`
- The gate is red and you could not fix it (after logging the ISSUE and reverting).

### 7. Final line of your response (REQUIRED, machine-read by the driver)
End every response with ONE status line:
- `OVERNIGHT-RUNNER: PHASE <name> ADVANCED (<N> commits)` — you committed work
- `OVERNIGHT-RUNNER: NO HEADLESS WORK REMAINING` — nothing left to do headlessly
- `OVERNIGHT-RUNNER: BLOCKED <one-line reason>` — gate red / blocker logged, no commit

Begin: read ROADMAP.md, CLAUDE.md, DECISIONS.md, ISSUES.md, then act.
