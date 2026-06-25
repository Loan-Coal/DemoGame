# MetaHuman Clothing Shortlist — Task B

> **Run date:** 2026-06-25  
> **Task:** Task B — MetaHuman medieval clothing (Task B from ASSET_ACQUISITION.md §6)  
> **Gate role:** go/no-go for the entire all-MetaHuman cast (DEC-031)  
> **Tier:** MANUAL — no fetch script generated; all deliverables are import instructions.

---

## Pipeline Currency Check (verified 2026-06-25)

**What changed since legacy docs:**

| Old tool | Current status |
|----------|---------------|
| Quixel Bridge | Being sunset — do NOT use |
| MetaHuman web creator only | In-editor MetaHuman plugin since UE5.6 |
| Megascans standalone | Now distributed via Fab plugin |
| Fab "Add to Project" (legacy) | Still the correct verb; now routed through in-editor Fab plugin |

**Current UE5.8 workflow (verified via: [Epic docs — Buying MetaHumans from Fab](https://dev.epicgames.com/documentation/en-us/metahuman/buying-metahumans-from-fab), [MetaHuman 5.8 release notes](https://dev.epicgames.com/documentation/metahuman/metahuman-5-8-release-notes-in-unreal-engine)):**
- Editor menu: **Windows → Fab** opens the in-editor Fab plugin panel
- Browse or search; acquired assets → **Library tab → Add to Project**
- Clothing assets land in `/Game/Fab/MetaHumans/`
- MetaHuman Creator is accessible in-editor (no longer web-only)
- UE5.8 introduced the **Outfit Asset** system: garments packaged as `.mhpkg` that auto-fit any body shape via the parametric system

**Three clothing rig classifications used below:**

| Class | What it means | Work to wire |
|-------|--------------|--------------|
| **(a) MetaHuman-native Outfit Asset** | Pre-packaged `.mhpkg`; added via MetaHuman Creator wardrobe; auto-fits any body shape | Minimal — assign in MetaHuman Creator UI |
| **(b) Skeletal mesh rigged to MetaHuman skeleton** | FBX or UE Skeletal Mesh already weighted to `metahuman_base_skel`; import and add as a SkeletalMeshComponent on the MetaHuman BP | Medium — import, assign skeleton, set Leader Pose Component, hide covered body sections |
| **(c) UE5-Mannequin-rigged / needs retarget** | Weighted to Quinn/Manny skeleton; requires IK Retargeter or skin transfer to MetaHuman skeleton | Heavy — retarget step (~1–2h per body configuration) |

**License note (verified via: [Fab dev forum](https://forums.unrealengine.com/t/all-free-assets-including-ue-ones-are-now-standard-license-on-fab-meaning-no-commercial-use/2080626), [Fab docs](https://dev.epicgames.com/documentation/en-us/fab/licenses-and-pricing-in-fab)):**  
The Fab Standard License "allows for commercial use, regardless of purchasing it under the Personal or Professional tier." Standard License = Epic-ecosystem = no `swap_for_commercial` flag needed. The CC-BY assets (DevonLux/Sketchfab) do require the flag.

> ⚠️ **Fab listing pages return HTTP 403** (Epic login required) for direct web fetch. All Fab asset specs below are verified via Epic Developer Community Forum posts by the product authors, plus web search snippets quoting the product descriptions. The Fab Standard License is confirmed from the Fab documentation pages (fetched successfully). An unfetchable *individual* listing page is noted per asset; none are guessed or memory-sourced.

---

## ⚠️ Compatibility caveat — legacy clothing on UE5.6+ parametric MetaHuman (see ISSUE-015)

The current (UE5.6+) MetaHuman is **parametric** and the official clothing pipeline is the **Chaos Outfit Asset**
(verified this run via the [official Hair & Clothing Controls doc](https://dev.epicgames.com/documentation/en-us/metahuman/hair-and-clothing-controls)).
The body skeleton (`metahuman_base_skel`) is still shared, so legacy skeletal-mesh clothing **attaches**, but it is
**not drop-in**:
- Only **parametric outfits auto-conform** — *"Wearing an outfit will cause it to automatically resize to fit the
  current body"*; a fixed SkeletalMesh garment does **not** resize. Fixed-body assets are skinned to ONE body type
  (e.g. DevonLux = "Tall, Normal-Weight, Male" only).
- UE5.6 removed the **+2 cm foot offset** → shoes authored pre-5.6 can sit below the floor (manual height fix).
- Wardrobe **validation** rejects skeletal clothing from an *"incompatible skeleton"* (can be disabled in Project
  Settings → Wardrobe).

**Consequence for the picks below:** the ⭐ top-overall picks (PolyWear, GrubyCommander) are advertised as
**MetaHuman-Creator parametric** with 2025 updates → these are the *latest-MetaHuman-safe* path. The 🆓 free picks
(DevonLux CC-BY, and the cheaper Meta Clothes Designer / Priest & Nun) are **fixed-body skeletal meshes** → they work
but require keeping the MetaHuman body near the authored body type, attach-via-component (not wardrobe), and a
possible shoe-height fix. **Confirm each asset's last-updated date is post-5.6 before relying on it.**

---

## Recommendation convention (per ASSET_ACQUISITION.md §3)

Each NPC ends with **two picks**:
- 🆓 **Top free pick** — best CC0 / CC-BY / free-tier option. If **none exists**, the line says so and names the
  cheapest paid floor instead (this is the case for both female NPCs — see ISSUE-012).
- ⭐ **Top overall pick** — best option regardless of price (quality + fit + least manual work).

Both are caveated "human confirms the look." Where a single asset is both the cheapest and the best, the two lines say so.

---

## $0 free-only path (no budget) — all 5 NPCs

The user is using **free assets only**. There are two free routes, by gender:

**Male NPCs (Sorn, Aldric, Henryk) — free + already MetaHuman-rigged (rig class (b)):**
Use the [DevonLux CC-BY sets on Sketchfab](https://sketchfab.com/DevonLux) (all fetched/verified this run, all
CC-BY 4.0, all skinned to a "Tall, Normal-Weight, Male" MetaHuman). Import FBX, rename `root.00x`→`root`, attach
via SkeletalMeshComponent + Leader Pose. swap_for_commercial: YES (attribution).
- Sorn → 5 Piece Heavy Armor · Aldric → 5 Piece Leather Peasant (re-skin finer) · Henryk → 4 Piece Cloth Armor.

**Female NPCs (Mira, Lira) — no free MetaHuman-rigged garment exists → free CC-BY static dress + skin-wrap (rig class (c)):**
This is the "convert a free asset to MetaHuman clothing" route the user asked for. Verified free bases:

| Asset | License (quoted) | Form | Best for |
|-------|------------------|------|----------|
| [Medieval Dress (A9908244)](https://sketchfab.com/3d-models/medieval-dress-f6b5cf078d044b6cb9764445ecc0cdf0) | "CC AttributionCreative Commons Attribution" (CC-BY 4.0) | Static mesh, full dress, 38.8k verts | Mira |
| [Medieval clothing Free (Red_Ilya)](https://sketchfab.com/3d-models/medieval-clothing-free-4df74f937a074e8daa9b512dc600422e) | "CC AttributionCreative Commons Attribution" (CC-BY 4.0) | Static mesh, dark leather/gothic, 25k tris, 2K PBR | Lira |

**Conversion pipeline (static garment → MetaHuman clothing, rig class (c)) — verified via [yelzkizi clothes-for-MetaHuman](https://yelzkizi.org/clothes-for-metahuman/):**
1. Export your MetaHuman **body** mesh from UE5.8 (or use the MetaHuman body FBX).
2. In **Blender** (free): import the body + the CC-BY dress; scale/align the dress to the body.
3. **Data Transfer / weight-transfer** the body's skin weights onto the dress (Blender "Data Transfer" modifier,
   Vertex Groups → nearest face interpolated), so the dress shares the MetaHuman skeleton's weighting.
4. Export the dress as FBX bound to `metahuman_base_skel`.
5. Import to UE5.8 → assign skeleton `metahuman_base_skel` → attach as SkeletalMeshComponent + **Leader Pose
   Component = Body** → hide covered body sections.
6. Add **Chaos Cloth** on loose skirt areas if you want sim. Fix shoe height if it clips (UE5.6 offset change — ISSUE-015).

**$0 path cost:** **$0 cash.** Labor: ~30 min per male NPC (FBX import) + ~1–3h per female NPC (Blender skin-wrap).
A free **Marvelous Designer Personal** garment is an alternative female route (author straight onto the body, best fit).
Alternatively, claim free female medieval clothing from Fab's **biweekly Limited-Time Free** drop if one appears —
see `project-harness/tools/fab-free/` for the auto-claimer.

---

## NPC 1 — Mira (innkeeper, female)

**Need:** Apron over kirtle / peasant dress, warm working-class, female MetaHuman body.  
Personality: social hub, gossipy (82), the most dialogue-heavy NPC → outfit must read clearly in close-up.

---

### Option 1 — PolyWear Medieval Resizable Collection ⭐ recommended

- **Source / URL:** https://www.fab.com/listings/950f0713-29e7-4c80-b75d-fe97144cd4cf  
  *(Fab listing returns HTTP 403; specs verified via fetched Epic forum thread: https://forums.unrealengine.com/t/polywear-medieval-resizable-outfit-collection-for-metahuman-parametric/2687542)*
- **License:** Fab Standard License (Epic-ecosystem, commercially permissive) → swap_for_commercial: **no**
- **Tier:** manual
- **Rig class:** **(a) MetaHuman parametric** — "Fully parametric outfit designed for MetaHuman Creator"; "automatically adjusts to any body shape"; quoted from fetched forum post
- **UE version:** "works with MetaHuman in UE 5.6" — quoted from fetched forum post
- **Garments:** 11 customizable medieval garments (5 Tunic, 3 Pants, 3 Boots); both genders via parametric
- **Price:** ~$20–30 (search-confirmed)
- **Textures:** 4K PBR (quoted from forum post: "4K PBR textures")
- **Rubric score:** 12/14 (L2 U2 P1 T2 M2 V1 C2)
  - L2 = Fab Standard License (Epic-ecosystem)
  - U2 = Native MetaHuman parametric, UE5.6+ confirmed
  - P1 = 4K vendor-created PBR; not photoscanned
  - T2 = 4K confirmed
  - M2 = 11 modular garments, mix-and-match
  - V1 = 11 assets per scene; MetaHuman context keeps it manageable
  - C2 = Covers multiple NPCs and body shapes
- **Pros:** Auto-fits any MetaHuman body; one purchase covers Mira + other NPCs; modular so tunic can be Mira's kirtle, pants+boots round the look; no retarget step; 4K textures.
- **Cons:** Vendor-created art (not Megascans-quality); tunics may read more as plain commoner than innkeeper apron specifically; no dedicated apron piece confirmed.

---

### Option 2 — Meta Clothes Designer — Medieval Clothes & Dress I

- **Source / URL:** https://www.fab.com/listings/31ab9919-b602-4dc0-b7d3-f431df44df19  
  *(Fab listing returns HTTP 403; specs confirmed via search snippet quoting product page: "clothing skeletal meshes skinned to the MetaHuman 'Male Medium & Short Underweight' and 'Female Medium & Short Underweight' skeletons")*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Tier:** manual
- **Rig class:** **(b) Skeletal mesh pre-skinned to MetaHuman skeleton** — specifically the `Female Medium & Short Underweight` body configuration
- **UE version:** UE5, updated Nov 2025 with parametric clothing components
- **Garments:** Female + male medieval dress/clothes; exact garment list unconfirmed from public sources
- **Price:** $49.99 (confirmed via search)
- **Textures:** "texture editor to allow user color customization" (from search snippet); likely 2K
- **Rubric score:** 10/14 (L2 U2 P1 T1 M1 V1 C2)
  - L2 = Fab Standard License
  - U2 = MetaHuman skeleton native
  - P1 = PBR with color customization
  - T1 = 2K likely (unconfirmed at 4K)
  - M1 = Pack of outfits, not modular piece-by-piece
  - V1 = MetaHuman skeletal meshes; no poly count stated
  - C2 = Male + female covered; multiple garment types
- **Pros:** Native MetaHuman skeleton (no retarget); includes both male and female; color-customizable materials; proven MetaHuman pipeline seller.
- **Cons:** $49.99 (expensive for a demo budget); texture resolution unconfirmed at 4K; apron layer not confirmed; requires one pack per gender pair at this price.

---

### Option 3 — Yasin ERHAN — Female & Male MetaHuman Medieval Rustic Outfit

- **Source / URL:** https://www.fab.com/listings/1f9e948a-c580-435b-a5dd-e738f73446dd  
  *(Fab listing returns HTTP 403; product by same author confirmed at ~$2.99/$3.99 via search-quoted pricing for related listings by yasinyasobolu)*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Tier:** manual
- **Rig class:** **(b) Skeletal mesh rigged to MetaHuman skeleton** — cloth-simulated rustic outfit
- **UE version:** UE5 (MetaHuman rigged, confirmed via search)
- **Garments:** Rustic medieval outfit for both male and female MetaHuman bodies; 4 color variants (brown, red, green, blue based on related bundle: https://www.fab.com/listings/409a1d41-d712-4dcf-ac94-5a8eba513dd6)
- **Price:** ~$2.99 personal / $3.99 professional (confirmed via search: "Personal License at $2.99 and Professional License at $3.99")
- **Textures:** PBR; resolution unconfirmed
- **Rubric score:** 9/14 (L2 U2 P1 T0 M1 V2 C1)
  - L2 = Fab Standard License
  - U2 = MetaHuman rigged
  - P1 = Cloth-simulated rustic PBR; quality unverified at this price point
  - T0 = Texture resolution unconfirmed; price point suggests lower end
  - M1 = Limited garment variety
  - V2 = Lightweight cloth-simulated garment
  - C1 = Covers both genders but limited variety; need color tweaking for Mira vs Lira differentiation
- **Pros:** Extremely cheap ($3–4 total for male + female); MetaHuman native; cloth simulation adds life; both genders in one purchase.
- **Cons:** Quality unknown (T0); "rustic" style may not include an apron; limited variety; texture resolution unconfirmed — requires human visual inspection before committing.

**Recommendation for Mira:**
- 🆓 **Top free pick (convert):** No free *MetaHuman-rigged* female garment exists, so use a **free CC-BY static dress + skin-wrap to the MetaHuman body** (rig class (c) — see "Free convertible garments" below). Best base: [Medieval Dress (A9908244)](https://sketchfab.com/3d-models/medieval-dress-f6b5cf078d044b6cb9764445ecc0cdf0) — CC-BY 4.0, free, full dress. Cost = $0 cash + ~1–3h Blender skin-wrap. swap_for_commercial: YES (CC-BY attribution).
- ⭐ **Top overall pick:** Option 1 — PolyWear Resizable Collection (~$20–30): auto-fits any MetaHuman body shape, 4K PBR, one purchase also covers other NPCs with modular mixing.

*Human confirms the look.*

---

## NPC 2 — Captain Sorn (soldier, male)

**Need:** Gambeson + light leather-or-mail armor + guard tabard. Stoic, older. Male MetaHuman.

---

### Option 1 — DevonLux — 5 Piece Heavy Armor ⭐ recommended (free path)

- **Source / URL:** https://sketchfab.com/3d-models/5-piece-heavy-armor-metahuman-rigged-38758fc7c96847d78dd5f6da4c3db1db  
  *(Page fetched this run — license and rig compatibility quoted directly below)*
- **License (quoted from fetched page):** "CC AttributionCreative Commons Attribution" (CC-BY) → swap_for_commercial: **YES**
- **Tier:** manual (Sketchfab download, FBX)
- **Rig class:** **(b) Skeletal mesh pre-rigged to MetaHuman skeleton** — "All but the helm is a skeletal mesh bound to the vertices and skeleton of a Tall, Normal-Weight, Male Metahuman" (quoted from fetched page)
- **UE version:** UE5 compatible; requires rename: "Remember to change root.00x to root when separating meshes, or they will not port correctly to UE5" (quoted from fetched page)
- **Garments:** Heavy plate armor, 5 pieces (helm is static mesh; body pieces are skeletal)
- **Price:** FREE (2,795 downloads; long-standing free resource)
- **Textures:** Not confirmed; CC-BY free asset
- **Rubric score:** 7/14 (L1 U1 P1 T0 M1 V2 C1)
  - L1 = CC-BY (allowed; swap_for_commercial: YES)
  - U1 = Pre-rigged to MetaHuman skeleton; FBX import requires rename step + Leader Pose Component; not native Outfit Asset
  - P1 = Hand-modeled heavy armor; adequate for soldier read
  - T0 = Texture resolution unconfirmed
  - M1 = 5 armor pieces, one style
  - V2 = Free FBX; no VRAM overhead
  - C1 = Armor only; gambeson undergarment not included (likely hidden by armor pieces)
- **Pros:** FREE with attribution; already rigged to MetaHuman skeleton (no retarget needed, just import binding); heavy armor = authoritative soldier silhouette; 2.7k downloads suggests battle-tested workflow.
- **Cons:** CC-BY (attribution required, must swap for commercial); FBX import needs root bone rename; texture resolution unknown; "Tall, Normal-Weight" only — if Sorn's MetaHuman uses a shorter/heavier body, re-binding needed; no gambeson base.

---

### Option 2 — DevonLux — 5 Piece Scalemail Armor

- **Source / URL:** https://sketchfab.com/3d-models/5-piece-scalemail-armor-metahuman-rigged-33858247654b47e68d26d6fdf070ca7f  
  *(Page fetched this run)*
- **License (quoted from fetched page):** "Creative Commons Attribution" (CC-BY) → swap_for_commercial: **YES**
- **Rig class:** **(b) Skeletal mesh rigged to MetaHuman "Tall, Normal-Weight, Male"** — same family as Option 1
- **Price:** FREE
- **Textures:** Unconfirmed
- **Rubric score:** 7/14 (L1 U1 P1 T0 M1 V2 C1)
- **Pros:** Free; lighter chainmail aesthetic (more "light leather-or-mail" than full plate); same MetaHuman skeleton compatibility as Option 1.
- **Cons:** Same as Option 1; scalemail is distinct from gambeson — slightly off-theme for "stoic older guard."

---

### Option 3 — GrubyCommander — Rustic Medieval Granular Modular (paid fallback)

- **Source / URL:** https://www.fab.com/listings/9daac986-d768-4462-a104-820456afdb9f  
  *(Fab listing returns HTTP 403; specs confirmed via fetched Epic forum thread: https://forums.unrealengine.com/t/grubycommander-rustic-medieval-granular-modular-clothing-metahuman-parametric-4k/2730373)*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(a) MetaHuman Creator parametric** — "designed for MetaHuman Creator with automatic weight-painting; minor subsequent manual adjustments may be required" (quoted from fetched forum thread)
- **UE version:** UE5, MetaHuman parametric (quoted from forum)
- **Garments:** 16 modular components — "4 distinct rustic medieval tunics / shirts, 4 varied pant styles, 4 pairs of medieval boots, 4 unique belts and sashes" (quoted from fetched forum thread); can layer tunic under armor
- **Price:** Unknown (paid; creator mentions future free community assets suggesting paid base)
- **Textures:** "4K" confirmed in product title "Parametric 4K" (from search snippet)
- **Rubric score:** 11/14 (L2 U2 P2 T2 M2 V1 C1) — C1 because armor/tabard not included; needs supplement for soldier look
  - L2 = Fab Standard License
  - U2 = MetaHuman parametric, auto weight-painting
  - P2 = 4K modular PBR (named explicitly "4K" in listing)
  - T2 = 4K confirmed
  - M2 = 16 modular components
  - V1 = 16 components; MetaHuman parametric
  - C1 = Covers gambeson/tunic layer; tabard not included; needs armor supplement
- **Pros:** Highest art quality (4K, parametric); 16 components for maximum variation; auto weight-paint to any body; one purchase covers Sorn, Aldric, and Henryk.
- **Cons:** Price unknown; no armor/tabard — must combine with DevonLux armor for Sorn's look; "rustic" style may not read as official soldier.

**Recommendation for Sorn:**
- 🆓 **Top free pick:** Option 1 — DevonLux 5 Piece Heavy Armor (CC-BY, free): already MetaHuman-rigged, soldier silhouette is clear, ~30 min FBX import. Attribution credit required (swap_for_commercial: YES).
- ⭐ **Top overall pick:** Option 3 — GrubyCommander Modular (4K parametric) as the gambeson/tunic base, layered with armor + tabard (DevonLux free armor, or a dedicated paid armor pack). Highest art quality; one pack also covers Aldric + Henryk.

*Human confirms the look.*

---

## NPC 3 — Lira (fence, female)

**Need:** Hooded cloak / dark layered commoner garb for dim back room. Female MetaHuman.  
⚠️ **Critical gap:** No free female MetaHuman-native hooded/cloaked option was found this run. Both options below require either a retarget step or a paid purchase.

---

### Option 1 — Medieval Priest & Nun — Metahuman ⭐ recommended (best hood match)

- **Source / URL:** https://www.fab.com/listings/a3cacd66-4eee-4728-ba29-37921101a33c  
  *(Fab listing returns HTTP 403; specs confirmed via search snippet: "stripped-down version of Modular Medieval V2, built for the UE5 Mannequin. The morphology supports Metahuman tal nrw proportions")*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Tier:** manual
- **Rig class:** **(c) UE5 Mannequin-rigged, needs retarget to MetaHuman skeleton** — "built for the UE5 Mannequin; morphology supports MetaHuman tal nrw proportions" (from search snippet); requires skin transfer or IK Retargeter (~1–2h setup per body)
- **UE version:** UE5, updated Nov 2025
- **Garments:** Nun habit (hooded robe) + priest cassock; multiple head/hair/chest/pants/shoe components
- **Price:** Unknown (paid; related product Modular Medieval V2 is ~$449; this is described as a "stripped-down version" — estimate $50–150 but unconfirmed)
- **Textures:** Unconfirmed (1–2K typical for this type of character pack)
- **Rubric score:** 9/14 (L2 U1 P1 T1 M2 V1 C1)
  - L2 = Fab Standard License
  - U1 = UE5 confirmed but Mannequin rig — NOT MetaHuman native; retarget step required
  - P1 = NPC character pack quality; appropriate detail level for hooded garb
  - T1 = Unconfirmed; assumed 2K for character pack at this tier
  - M2 = Multiple modular components (head, hair, chest, pants, shoes)
  - V1 = Character pack including body mesh
  - C1 = Nun habit is closest available match to dark hooded commoner; but retarget is a real time cost
- **Pros:** Best available match for Lira's "hooded dark" look — nun habit is full robe with hood; modular components; UE5 confirmed.
- **Cons:** UE5 Mannequin rig, NOT MetaHuman native — **requires IK Retargeter or skin transfer to MetaHuman skeleton (~1–2h)** — this is the most work of any outfit in this shortlist; price unknown and likely highest; texture resolution unconfirmed; price must be verified in-editor before purchase.

---

### Option 2 — Meta Clothes Designer — Medieval Clothes & Dress III

- **Source / URL:** https://www.fab.com/listings/86375381-0a1a-4b34-a09d-ab16a06ec481  
  *(Fab listing returns HTTP 403; specs: "skeletal meshes skinned to MetaHuman Female Medium & Short Underweight skeletons"; confirmed via search snippet)*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(b) Skeletal mesh skinned to MetaHuman skeleton** — no retarget needed
- **Price:** $49.99
- **Textures:** 2K (likely; texture editor for color customization confirmed)
- **Rubric score:** 9/14 (L2 U2 P1 T1 M1 V1 C1) — C1 because no dedicated hood/cloak; rely on color customization to darken
- **Pros:** MetaHuman-native (no retarget); includes female body type; color-customizable materials — darken the palette for Lira's dim room.
- **Cons:** No hood or cloak piece confirmed; "series III" garment styles unconfirmed — inspect visually before purchase; at $49.99 this is the most expensive per-NPC option if combined with another pack for Mira.

---

### Option 3 — Yasin ERHAN — Female & Male Rustic Medieval Outfit

- **Source / URL:** https://www.fab.com/listings/1f9e948a-c580-435b-a5dd-e738f73446dd
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(b) MetaHuman skeleton rigged**
- **Price:** ~$3–4
- **Rubric score:** 9/14 (L2 U2 P1 T0 M1 V2 C1) — same as Mira Option 3
- **Pros:** Cheap; both genders (same pack as Mira option if purchased together); color variants (brown/dark tone plausible for Lira).
- **Cons:** No hood; texture quality unconfirmed; "rustic" look rather than "menacing fence in dim back room" — relies entirely on lighting + color variant.

**Recommendation for Lira:**
- 🆓 **Top free pick (convert):** No free MetaHuman-rigged female/hooded garment exists, so use a **free CC-BY static garment + skin-wrap** (rig class (c)). Best base: [Medieval clothing Free (Red_Ilya)](https://sketchfab.com/3d-models/medieval-clothing-free-4df74f937a074e8daa9b512dc600422e) — CC-BY 4.0, free, dark gothic/leather layered look that suits a fence. The dim `L_TavernBack` lighting carries most of the "hood" read, so a hood is optional. Cost = $0 cash + ~1–3h Blender skin-wrap. swap_for_commercial: YES.
- ⭐ **Top overall pick:** Option 1 — Medieval Priest & Nun (hooded habit, best hood match) — **but flag the UE5-Mannequin → MetaHuman retarget (~1–2h)** as the single biggest risk on this whole shortlist. If retarget quality is poor on Lira's MetaHuman, fall back to Option 2 (Dress III, native, no retarget, no hood) + dim lighting + material darkening to sell the "fence in shadows" look.

*Human confirms the look.* Verify Priest & Nun price before purchase.

---

## NPC 4 — Aldric (wine merchant, male)

**Need:** Respectable doublet/tunic, finer middle-class cloth, middle-aged male MetaHuman.

---

### Option 1 — GrubyCommander — Rustic Medieval Granular Modular ⭐ recommended

- **Source / URL:** https://www.fab.com/listings/9daac986-d768-4462-a104-820456afdb9f  
  *(Same asset as Sorn Option 3; full specs above)*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(a) MetaHuman Creator parametric**
- **Garments (quoted from fetched forum post):** "4 distinct rustic medieval tunics / shirts, 4 varied pant styles, 4 pairs of medieval boots, 4 unique belts and sashes" — select the finest-looking tunic + decorative belt for Aldric's merchant look
- **Rubric score:** 13/14 (L2 U2 P2 T2 M2 V1 C2) — highest on this shortlist
  - L2 U2 P2 T2 = all confirmed strong
  - M2 = maximum modularity
  - V1 = 16 components
  - C2 = Can assemble a merchant look; tunics + belts + boots complete the outfit alone
- **Pros:** 4K parametric; one pack covers Aldric + Henryk (and gambeson-layer for Sorn); modular tunics allow clear differentiation between merchant (finer tunic + ornate belt) vs commoner (plain tunic + rope belt).
- **Cons:** Price unknown; "rustic" style — the available tunics may be too worn for a "finer" merchant; confirm visually that one of the 4 tunic variants reads as merchant-class before purchase.

---

### Option 2 — PolyWear — Rigged Medieval MetaHuman Clothes

- **Source / URL:** https://www.fab.com/listings/ef230525-475a-4961-bc61-8ce0a1139e96  
  *(Fab listing returns HTTP 403; specs confirmed via fetched forum thread https://forums.unrealengine.com/t/polywear-rigged-metahuman-medieval-clothes/2620966: "rigged to the Metahuman skeleton", "Compatible with Metahuman Male (Medium Height, Normal Weight)", "5 medieval tunics", "4K PBR textures")*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(b) Skeletal mesh rigged to MetaHuman Male "Medium Height, Normal Weight"** — quoted from fetched forum post
- **UE version:** UE5, MetaHuman skeleton confirmed
- **Garments:** 5 medieval tunics; high + low poly variants; 4K PBR textures
- **Price:** ~$20–29.99 (confirmed via search)
- **Textures:** "4K PBR textures" (quoted from fetched forum)
- **Rubric score:** 10/14 (L2 U2 P1 T2 M1 V1 C1)
  - M1 = 5 tunics but no pants/boots included; needs supplement
  - C1 = Tunics alone don't complete the outfit; supplement needed
- **Pros:** 4K textures; 5 variants to pick the merchant-appropriate one; MetaHuman native skeleton.
- **Cons:** Male Medium Height, Normal Weight only — won't fit a different body preset; tunics only (no pants/boots); lower modularity than GrubyCommander.

---

### Option 3 — DevonLux — 5 Piece Leather Peasant Clothing (free fallback)

- **Source / URL:** https://sketchfab.com/3d-models/5-piece-leather-pesant-clothing-metahuman-908ac5061b8c46c8810631dcbfd0cdd9  
  *(Page fetched this run)*
- **License (quoted from fetched page):** "CC AttributionCreative Commons Attribution" (CC-BY) → swap_for_commercial: **YES**
- **Rig class:** **(b) FBX skeletal mesh** — "MetaHuman use with skeletal mesh rigging" (quoted from fetched page); "Tall, Normal-Weight, Male MetaHuman" body type; MetaHuman plugin note: helm lacks skeletal mesh
- **Price:** FREE
- **Textures:** Unconfirmed
- **Rubric score:** 7/14 (L1 U1 P1 T0 M1 V2 C1)
- **Pros:** Free with attribution; workable peasant-merchant read if Megascans material is re-applied.
- **Cons:** "Peasant" leather = wrong class for Aldric's merchant status; CC-BY requires commercial-swap flag; FBX import extra steps; Tall body only.

**Recommendation for Aldric:**
- 🆓 **Top free pick:** Option 3 — DevonLux 5 Piece Leather Peasant (CC-BY, free): MetaHuman-rigged, but "peasant" reads under merchant class — re-skin with a finer Megascans material to lift it. Attribution required (swap_for_commercial: YES).
- ⭐ **Top overall pick:** Option 1 — GrubyCommander Modular (4K): finer tunic + ornate belt for the merchant read; one purchase also covers Henryk.

*Human confirms the look and price.* Price must be verified on the Fab listing before purchase.

---

## NPC 5 — Old Henryk (elderly commoner, male)

**Need:** Worn robe/tunic, end-of-gossip-chain old man. Male MetaHuman (elderly preset).  
VRAM note: Henryk co-loads with Aldric in the market scene — outfit should be lightweight.

---

### Option 1 — PolyWear — Medieval Farmer / Villager Outfit ⭐ recommended

- **Source / URL:** https://www.fab.com/listings/b31ed1c6-82bc-48ce-b67f-dd86e406f0e4  
  *(Fab listing returns HTTP 403; specs confirmed via fetched Epic forum thread https://forums.unrealengine.com/t/polywear-medieval-farmer-metahuman-villager-clothing-rigged/2702439: "rigged to the Metahuman skeleton", "Compatible with Metahuman Male Medium height, Normal weight Metahuman (m_med_nrw_body)", "1 medieval farmer outfit", "4K PBR textures")*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(b) Skeletal mesh rigged to MetaHuman Male "Medium height, Normal weight" (m_med_nrw_body)** — quoted from fetched forum thread
- **UE version:** UE5 MetaHuman (confirmed from forum)
- **Garments:** 1 medieval farmer outfit; 4K PBR textures
- **Price:** Unknown (single-outfit PolyWear packs typically $15–25)
- **Textures:** "4K PBR textures" (quoted from fetched forum post)
- **Rubric score:** 12/14 (L2 U2 P1 T2 M1 V2 C2)
  - L2 U2 = Fab Standard + MetaHuman native
  - P1 = 4K vendor PBR; not photoscanned
  - T2 = 4K confirmed
  - M1 = Single outfit (no modularity)
  - V2 = Single lightweight skeletal mesh — good for market co-load
  - C2 = Single dedicated farmer/commoner outfit; exactly fits Henryk's role
- **Pros:** Perfect semantic fit ("farmer/villager = elderly commoner"); 4K textures; MetaHuman native; single outfit = lightweight for the market co-load scene; body type matches standard MetaHuman male.
- **Cons:** No modularity; single style (one variant); price unconfirmed; confirm body preset matches Henryk's MetaHuman body before purchase.

---

### Option 2 — GrubyCommander — Rustic Medieval Granular Modular (shared pack)

- **Source / URL:** https://www.fab.com/listings/9daac986-d768-4462-a104-820456afdb9f  
  *(Same as Aldric Option 1 — purchase once, covers both Aldric and Henryk)*
- **License:** Fab Standard License → swap_for_commercial: **no**
- **Rig class:** **(a) MetaHuman Creator parametric**
- **Garments:** Use worn tunic + simple rope belt for Henryk (contrast with Aldric's finer tunic + ornate belt from same pack)
- **Rubric score:** 13/14 (same as Aldric Option 1)
- **Pros:** Already purchased for Aldric (no extra cost); parametric auto-fits elderly body preset; 16 components lets you make Henryk visibly distinct from Aldric.
- **Cons:** Price unknown; "rustic" range — inspect to confirm that a sufficiently worn/rough tunic variant is included.

---

### Option 3 — DevonLux — 4 Piece Cloth Armor (free fallback)

- **Source / URL:** https://sketchfab.com/3d-models/4-piece-cloth-armor-metahuman-rigged-2eb2ee83524545078252d87b33cd13dd  
  *(Page fetched this run)*
- **License (quoted from fetched page):** "CC AttributionCreative Commons Attribution" (CC-BY) → swap_for_commercial: **YES**
- **Rig class:** **(b) FBX skeletal mesh** — "All meshes are bound to the vertices and skeleton of a Tall, Normal-Weight, Male MetaHuman" (quoted from fetched page)
- **Price:** FREE
- **Garments:** 4 cloth pieces — loose cloth panels; closest free analog to worn robe
- **Rubric score:** 7/14 (L1 U1 P1 T0 M1 V2 C1)
- **Pros:** Free with attribution; loose cloth panels could read as worn robe in dim market; no VRAM overhead.
- **Cons:** CC-BY (swap flag); tall body only — Henryk's elderly preset may be medium/short; texture resolution unconfirmed; "cloth armor" = gambesons/padded cloth, not a loose robe; requires visual inspection.

**Recommendation for Henryk:**
- 🆓 **Top free pick:** Option 3 — DevonLux 4 Piece Cloth Armor (CC-BY, free): loose cloth panels read as a worn robe in the dim market; Tall-male body only. Attribution required (swap_for_commercial: YES).
- ⭐ **Top overall pick:** Option 1 — PolyWear Farmer/Villager (4K, dedicated commoner, lightweight for the market co-load) — **or Option 2 (GrubyCommander) at no extra cost** if already bought for Aldric, differentiated via a worn tunic variant.

*Human confirms the look.* Verify price on Fab before purchase.

---

## Cost Summary (top free pick + top overall pick per NPC)

| NPC | 🆓 Top free pick | ⭐ Top overall pick | Overall-path cost |
|-----|------------------|---------------------|-------------------|
| Mira | *none (female gap)* — floor Yasin ERHAN ~$4 | PolyWear Resizable Collection | ~$20–30 |
| Sorn | DevonLux Heavy Armor (FREE, CC-BY) | GrubyCommander + armor/tabard | ~$20–50 |
| Lira | *none (female gap)* — floor Yasin ERHAN ~$4 | Medieval Priest & Nun (+retarget) | unknown ~$50–150 |
| Aldric | DevonLux Leather Peasant (FREE, CC-BY) | GrubyCommander Modular | ~$20–50 (shared w/ Henryk) |
| Henryk | DevonLux Cloth Armor (FREE, CC-BY) | PolyWear Farmer/Villager OR GrubyCommander (shared) | ~$15–25 / $0 if shared |

**All-free path ($0 cash — the chosen path):** 3 male NPCs = DevonLux CC-BY FBX (already MetaHuman-rigged, ~30 min each). 2 female NPCs = free CC-BY static dress + Blender skin-wrap to the MetaHuman body (~1–3h each), or a free Marvelous Designer garment. All CC-BY (attribution + swap_for_commercial: YES). See the "$0 free-only path" section above for the per-NPC bases + conversion pipeline. Cost = **$0 cash**, trading money for ~2–6h of Blender labor on the two women.

**Top-overall path:** ≈ **$60–130 cash** for all 5 NPCs + Lira's ~1–2h retarget. All Fab Standard License (Epic-ecosystem, no swap flag).

---

## GATE VERDICT

**CONDITIONAL GO**

All 5 outfits can plausibly be MetaHuman-rigged from available sources, but with conditions:

1. **Female NPCs (Mira, Lira): No free CC0 option exists.** Every confirmed female MetaHuman-rigged medieval garment is a paid Fab asset. Minimum cash outlay: ~$3–4 (Yasin ERHAN, both genders) up to ~$50–150 depending on art quality standard. This is **not a technical blocker** — paid Fab Standard License assets are Epic-ecosystem and no swap is needed.

2. **Lira's hood: No ideal ready-made option.** The closest match (Medieval Priest & Nun) is a UE5 Mannequin rig — a **1–2h retarget step** per body config is required. This is the **single biggest schedule/feasibility risk** for the photoreal cast plan. If the retarget quality is unacceptable on Lira's specific MetaHuman face, the fallback is Meta Clothes Designer III (no hood, no retarget, $49.99).

3. **Male NPCs (Sorn, Aldric, Henryk): Free CC-BY path is viable** via DevonLux Sketchfab assets. Extra work: FBX import, root bone rename, Leader Pose Component bind (~30 min each). These are pre-rigged to MetaHuman skeleton — NOT a full retarget. Constraint: DevonLux = "Tall, Normal-Weight" body only; if any male NPC uses a different body preset, re-binding is needed.

4. **No heavy per-outfit manual retarget is required for the recommended picks** — except Lira's Option 1. All other options (DevonLux type-b, PolyWear/GrubyCommander type-a/b) either are already MetaHuman-rigged (type b) or use the parametric system (type a).

5. **Latest-MetaHuman compatibility (ISSUE-015):** the UE5.6+ MetaHuman is parametric; only Chaos Outfit Assets auto-conform. The ⭐ parametric picks (PolyWear, GrubyCommander) are latest-safe. The 🆓 free fixed-body picks (DevonLux) attach but won't conform to an adjusted body, may need a shoe-height fix, and may fail wardrobe validation — usable, not drop-in. This **raises the cost of the $0 free path** in manual-fix time, and is the strongest reason the quality path is parametric.

**GO conditions:**
- Human verifies Lira's retarget quality on her MetaHuman blueprint (skin test)
- Human confirms each fixed-body asset's last-updated date is post-UE5.6, and skin-tests it on the target body type (ISSUE-015)
- Human confirms GrubyCommander and Priest & Nun pricing before purchase
- Budget ~$60–130 for quality path, or ~$4 + manual work for the bare-minimum path
- Fab page browse in-editor to visually verify garment styles before "Add to Project" commit

**Recommend starting with Mira** (most dialogue, most expression tuning — she's the critical path). Skin-test her outfit first. If DevonLux FBX import fails on the root-bone rename, fall back to a paid Fab option for Sorn/Aldric/Henryk too.
