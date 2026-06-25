# Asset Shortlists

> One file per category task (from `ASSET_ACQUISITION.md` §6): `metahuman-cast.md`, `metahuman-clothing.md`,
> `animations.md`, `env-geometry.md`, `surfaces-props.md`, `lighting-hdri.md`, `audio.md`, `ui-art.md`.
>
> A Claude session writes its research here as **2–4 options per asset, with reasoning** scored against the
> §2 rubric. **You approve a pick from each shortlist before any download is run** (the hard gate).

## Why this folder exists

Claude cannot judge how an asset *looks rendered* — that's a human gate. So a session's job is to narrow the
field to a few defensible candidates and explain the trade-offs; you make the final visual call.

## Shortlist entry template

Copy this per asset into the category file:

```markdown
## <asset name / slot> — e.g. "Tavern oak floor material"

**Need:** <what scene/role this fills>

### Option 1 — <name> ⭐ recommended
- **Source / URL:** <link>
- **License:** <CC0 / CC-BY / NC / Epic-ecosystem>  → swap_for_commercial: <yes/no>
- **Tier:** <scripted / manual / generated>
- **Rubric score:** license ✓ · UE5 ✓ · photoreal ✓ · texel 2K · modular n/a · VRAM ok · complete ✓
- **Pros:** ...
- **Cons:** ...

### Option 2 — <name>
- (same fields)

### Option 3 — <name>
- (same fields)

**Recommendation:** Option 1, pending your visual confirmation in-editor.
```

## Status

_No shortlists yet. Each is created when its category task in `ASSET_ACQUISITION.md` §6 is first run._
