# Kick-off prompt — Task B (MetaHuman medieval clothing)

> Paste the block below to run Task B end to end. Encodes the dual-pick policy (DEC-033):
> every outfit ends with a 🆓 top free pick AND a ⭐ top overall pick.

---

You are running ONE asset-acquisition category task for DemoGame, end to end: Task B —
MetaHuman medieval clothing. This is the go/no-go gate for the entire photoreal cast.
Runtime is not a constraint — be exhaustive. Do NOT start any other category.

## Read first (only these — do not read the whole file)
- project-harness/ASSET_ACQUISITION.md: §1 (locked context), §2 (rubric + 0/14 scoring scale),
  §3 (deliverables + Definition of Done — note the top-free + top-overall dual-pick rule), §4 (tiers,
  pipeline-currency rule, resolution ceilings), §5 (manifest format), §6 Task B, §8 (pre-flight).
- project-harness/DECISIONS.md: DEC-031 (all 5 NPCs are MetaHuman), DEC-030 (Lumen),
  DEC-032 (clothing strategy), DEC-033 (dual-pick policy).
- docs/game_design_roadmap.md §7.3 (cast personalities) for outfit tone per NPC.

## Locked context (do not re-litigate)
- Photoreal medieval, UE5.8. ALL 5 NPCs are MetaHuman (DEC-031): Mira (innkeeper), Captain Sorn
  (soldier), Lira (fence, hooded/dim), Aldric (wine merchant), Old Henryk (elderly preset).
- License policy: CC0 / Epic-ecosystem preferred; NC and CC-BY allowed but every such asset is
  tagged swap_for_commercial: YES.
- Task B is MANUAL tier: you produce research + a shortlist + import instructions. You do NOT
  download anything and you do NOT write a fetch script (manual tier has no scripted fetch).

## Hard rules (a run that breaks any of these is rejected)
1. Pipeline currency FIRST: before writing import steps, fetch and confirm the CURRENT UE5.8 flow
   for MetaHuman + Fab + clothing (Megascans now lives in Fab; Quixel Bridge is being sunset;
   MetaHuman is an in-editor plugin in UE5.6+). Write steps against what you verify today, not
   against any tool name you remember.
2. EVERY cited URL must be fetched and read THIS run; quote the exact license string and the
   rig/skeleton-compatibility claim from the page. No memory-sourced URLs, licenses, or specs.
   An unfetchable candidate is dropped, not guessed. (Note: fab.com listing pages return HTTP 403
   to unauthenticated fetches — verify Fab asset specs via the seller's Epic Dev Community forum
   thread + search snippets, and verify the Fab Standard License via the Fab/Epic docs pages.)
3. Do NOT assume "Fab humanoid = MetaHuman-rigged." Most Fab garments are UE-Mannequin-rigged and
   need retarget / skin-wrap / Mesh-to-MetaHuman. For each option state exactly which it is:
   (a) MetaHuman-native clothing, (b) skeletal mesh needing retarget, or (c) static garment needing
   cloth-binding — and the work that implies.
4. Score every candidate on the §2 0/14 scale; report the per-axis vector + total. License is a
   gate: unverifiable license caps total at 0. A recommended pick may not have a 0 on License,
   UE5 compatibility, or Photoreal match.
5. ≥ 2 options per outfit (target 2–4). Five outfits total (one per NPC, per Task B).
6. **Dual pick per outfit (DEC-033):** end EVERY outfit with BOTH a 🆓 top free/CC0 pick AND a
   ⭐ top overall pick. If no free/CC0 option exists for that outfit, the free line must say so
   explicitly and name the cheapest paid floor — never silently omit it. If one asset is both the
   cheapest and the best, say the two coincide.

## Search method
Use the project's web search + page-fetch tools (the repo mandates the mgrep skill; WebSearch +
WebFetch are the working fallback). Use WebFetch to open and quote each candidate asset page (Fab
listings 403 → use the seller's Epic forum thread + Sketchfab/ArtStation mirrors). Search Fab
(Free + NC filters), MetaHuman-native clothing sources, free CC-BY MetaHuman-rigged garments
(e.g. Sketchfab), and alternative routes (Marvelous Designer garments + how they bind to the
MetaHuman body, CC0 garment scans). Cast a wide net per outfit, especially for the free pick.

## Deliverables (produce ALL; match §3)
1. project-harness/asset-shortlists/metahuman-clothing.md — per outfit (Mira/Sorn/Lira/Aldric/Henryk):
   2–4 options, each with fetched source URL, quoted license, quoted UE5.x/rig-compat statement,
   the (a)/(b)/(c) rig classification, pros, cons, 0/14 score vector + total, then a 🆓 top free pick
   AND a ⭐ top overall pick (caveated "human confirms the look").
2. HUMAN_VERIFICATION.md — append "## Asset import — MetaHuman clothing" with verbatim, click-exact,
   verified-current import + skin-test steps (recommend testing on Mira first). Cover both the free
   path (e.g. CC-BY FBX import) and the overall path (Fab plugin / parametric Outfit Asset / retarget).
3. project-harness/ASSET_MANIFEST.md — append one manifest row per recommended outfit option,
   covering BOTH the top free pick and the top overall pick per NPC (§5 format); tag NC/CC-BY rows
   swap_for_commercial: YES; delete the placeholder example row if it is still the only row.
4. Log any blocker, gap, or contradiction you hit in project-harness/ISSUES.md; record any
   non-obvious choice in DECISIONS.md.

## End the run with the GATE VERDICT (this is the point of Task B)
State GO / NO-GO / CONDITIONAL: can all 5 outfits plausibly be MetaHuman-rigged from free/NC sources?
If it only works with heavy per-outfit manual retarget, say so loudly as a schedule/feasibility risk
to the photoreal-cast plan, and recommend the cheapest viable path (e.g. MetaHuman-native first,
retarget second, Marvelous third). Be explicit about what is scripted (nothing, this run) vs only
instructed.

Then give me a tight summary: the verdict, the 🆓 top free pick AND the ⭐ top overall pick per NPC,
and the single biggest risk you found. Do not pad.
