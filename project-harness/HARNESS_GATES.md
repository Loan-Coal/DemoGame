# Harness Gates

## The one command

```
pwsh Scripts/check.ps1            # fast gates (rules, contract, presence); build/test SKIP
pwsh Scripts/check.ps1 -WithBuild # also compile + run Automation tests (slow, needs UE installed)
```

Exit code 0 ⇒ `CHECK: PASS`. Any failing gate ⇒ non-zero and `CHECK: FAIL (<n> gate(s))`.

## Gate table

| # | Gate | Script / tool | HARD? | Skips when |
|---|------|---------------|-------|------------|
| 1 | Rules | `Scripts/check_rules.py` | yes | never runs as a no-op pass if `Source/` is absent |
| 2 | Contract sync | `Scripts/check_contract_sync.py` | yes | no mirror USTRUCT headers yet, or no `JsonName` annotations |
| 3 | Build | `Build.bat DemoGameEditor Win64 Development` | opt-in | no `.uproject`, `-WithBuild` not passed, or engine not found |
| 4 | Automation tests | `UnrealEditor-Cmd … Automation RunTests NpcEngine` | opt-in | no `.uproject`, opt-in flag not passed, or editor not found |
| 5 | Presence | spec + smoke detection | arms with growth | module absent, or scaffolded with neither spec nor smoke yet |

## Stance: clean repo, HARD from day 1 — no ratchet

There is no legacy *contract* debt to ratchet down from: the content rules (net I/O outside the client,
JSON in the game module, URL/endpoint literals, `npc_id` literals, on-screen logging) are clean today
and apply to **every** file, new or old. No baseline, no "allowed failures" budget.

The single exception is **file-shape** debt from the UE5.8 Third Person template and the initial
scaffold (107 pre-existing `.h`/`.cpp` files with no `// File:` header, some over the size ceiling).
Those files are grandfathered **for the header and file-size rules only**, via the explicit baseline
list `Scripts/.rules_legacy.txt`. Every **new** file is HARD from line one — do not add files to that
baseline.

## Graceful skip before the project is fully built

The gate is runnable at every stage, including before the UE project compiles:

- **Build / Automation tests** are opt-in. A gate that runs on every change must not trigger a
  multi-minute UE cook; pass `-WithBuild` (or `-WithTests`) when you actually want them. Without UE
  installed they SKIP with a notice rather than failing.
- **Contract sync** SKIPs (with a NOTICE) until the mirror USTRUCTs carry `meta=(JsonName="…")`
  annotations, since it cannot match fields without them.
- **Presence** SKIPs while `NpcEngineClient` is freshly scaffolded with neither a `*.spec.cpp` nor a
  registered `NpcEngine.Smoke` command. It **arms** as soon as one of the two appears: from then on it
  requires **both**, so you cannot ship the client module half-tested.

## Per-rule suppression (escape hatch)

Content rules support an in-code, documented suppression so a sanctioned exception need not weaken the
global rule:

- Per line: `// rules-allow: <rule_name>` (or bare `// rules-allow`) on the offending line.
- Per file: `// rules-allow-file: <rule_name>` within the first 10 lines.

Example (the smoke dev fixture legitimately names a known NPC):
```
Req.NpcId = TEXT("mira_innkeeper");   // rules-allow: hardcoded_npc_id (NpcEngine.Smoke dev fixture)
```

Use suppression only for genuine, documented exceptions — never to mute a real violation.

## Adding a new rule

1. Open `Scripts/check_rules.py`.
2. Append a tuple to `CONTENT_RULES`:
   `("<rule_name>", re.compile(r"<regex>"), ["<include/prefix/>"], ["<exclude/prefix/>"])`.
   - Matching runs over comment-stripped text (string literals preserved), so doc comments referencing
     the contract do not trip content rules.
   - `include`/`exclude` are path-prefix lists relative to repo root (e.g. `Source/DemoGame/`).
3. A clean repo must produce zero hits — fix the code or add a justified suppression, never relax the
   rule. Re-run `pwsh Scripts/check.ps1` to confirm.

Structural rules (header presence, file size) live in `check_file()`; the grandfather baseline that
exempts pre-existing files for those two rules is `Scripts/.rules_legacy.txt`.
