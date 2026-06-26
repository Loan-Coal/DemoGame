---
id: REV-NNN
priority: P1|P2|P3
horizon: now | slice-2 | full-game   # when this actually bites
confidence: high | medium            # only write the file if high, or medium with strong evidence
effort: S | M | L                    # rough fix size: S<2h, M<1day, L=multi-day
category: ssot|architecture|scalability|simplicity|contract|async-safety|assets|tests|dead-code|production|expansion|performance|stub
title: Short descriptive title (max 80 chars)
---

## Description
What the issue is. One clear paragraph.

## Evidence (required)
Quote the actual code that proves this finding, with `file:line`. A finding with no code
citation does not get written. If you cannot point at the code, you have not verified it.

```cpp
// Source/Module/File.cpp:NN
<paste the real lines that demonstrate the problem>
```

## Why It Matters
Impact at current scale vs impact at 100+ NPC / 30+ location full-game scale.

## Recommended Fix
Concrete, actionable. Name the specific change to make. If there are multiple options, name them and give a recommendation.

## Related
- ROADMAP Phase / DECISIONS entry / ISSUES.md item if relevant
- Any other REV-NNN that must be addressed first (ordering dependency)
