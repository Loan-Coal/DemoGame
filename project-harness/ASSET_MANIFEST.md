# Asset Manifest

> **Purpose:** The single ledger of every asset selected or acquired for DemoGame, with its license
> and whether it must be swapped before a commercial release.
> **Written by:** Claude sessions running category tasks in `ASSET_ACQUISITION.md`. Append rows; never delete.
> **Read by:** you (to track licenses) and the future commercial-swap pass (to find what must be replaced).

## License policy (recap)

This demo is **non-commercial**, so NC and CC-BY assets are allowed — **but every NC / CC-BY asset MUST be
tagged `swap_for_commercial: YES`**. CC0 and Epic-ecosystem (MetaHuman / Fab-free / Megascans / Mixamo) need no swap.

Rule: **anything not CC0 and not Epic-ecosystem → `swap_for_commercial: YES`.**

## Tier legend

- `scripted` — CC0 direct-download; a scoped fetch script was generated for the human to run (no bundles).
- `manual` — account/editor-gated (MetaHuman, Fab, Megascans, Mixamo); acquired by hand in browser/editor.
- `generated` — 2D UI art produced by the human via SDXL/Midjourney.

## Manifest

| asset | category | source | url | license | tier | swap_for_commercial | local_path | notes |
|-------|----------|--------|-----|---------|------|---------------------|------------|-------|
| PolyWear Medieval Resizable Collection (Mira) | character-clothing | Fab | https://www.fab.com/listings/950f0713-29e7-4c80-b75d-fe97144cd4cf | Fab Standard License (Epic-ecosystem) | manual | no | (in-editor) /Game/Fab/MetaHumans/ | Mira rec. pick; 11 garments, parametric auto-fit any body, 4K PBR, UE5.6+; also covers Aldric/Henryk tunics. Score 12/14. |
| DevonLux 5 Piece Heavy Armor (Sorn) | character-clothing | Sketchfab | https://sketchfab.com/3d-models/5-piece-heavy-armor-metahuman-rigged-38758fc7c96847d78dd5f6da4c3db1db | CC-BY 4.0 ("CC AttributionCreative Commons Attribution" — quoted from page) | manual | YES | AssetStaging/character-clothing/DevonLux/HeavyArmor/ | Sorn rec. pick; free, pre-rigged to MetaHuman tall-normal-male skeleton; FBX import requires root.00x→root rename; attribution required. Score 7/14. |
| Medieval Priest & Nun — Metahuman (Lira) | character-clothing | Fab | https://www.fab.com/listings/a3cacd66-4eee-4728-ba29-37921101a33c | Fab Standard License (Epic-ecosystem) | manual | no | (in-editor) /Game/Fab/MetaHumans/ | Lira rec. pick (Option 1); nun habit = hooded dark robe; UE5 Mannequin rig — REQUIRES IK Retarget to MetaHuman skeleton (~1–2h); verify price in-editor before purchase. Score 9/14. |
| GrubyCommander Rustic Medieval Granular Modular (Aldric + Henryk) | character-clothing | Fab | https://www.fab.com/listings/9daac986-d768-4462-a104-820456afdb9f | Fab Standard License (Epic-ecosystem) | manual | no | (in-editor) /Game/Fab/MetaHumans/ | Aldric + Henryk rec. pick; 16 modular components, 4K parametric MetaHuman Creator; one pack covers both NPCs; price unconfirmed — verify in-editor. Score 13/14. |
| PolyWear Medieval Farmer/Villager Outfit (Henryk fallback) | character-clothing | Fab | https://www.fab.com/listings/b31ed1c6-82bc-48ce-b67f-dd86e406f0e4 | Fab Standard License (Epic-ecosystem) | manual | no | (in-editor) /Game/Fab/MetaHumans/ | Henryk fallback if GrubyCommander not purchased; single farmer outfit, 4K PBR, MetaHuman male m_med_nrw_body skeleton. Score 12/14. |
| Meta Clothes Designer — Medieval Clothes & Dress I (Mira/Lira fallback) | character-clothing | Fab | https://www.fab.com/listings/31ab9919-b602-4dc0-b7d3-f431df44df19 | Fab Standard License (Epic-ecosystem) | manual | no | (in-editor) /Game/Fab/MetaHumans/ | Fallback for Mira/Lira if PolyWear visually rejected; $49.99; MetaHuman female + male skeleton native; includes both genders. Score 10/14. |
| DevonLux 5 Piece Leather Peasant (Aldric — top free pick) | character-clothing | Sketchfab | https://sketchfab.com/3d-models/5-piece-leather-pesant-clothing-metahuman-908ac5061b8c46c8810631dcbfd0cdd9 | CC-BY ("CC AttributionCreative Commons Attribution" — quoted from page) | manual | YES | AssetStaging/character-clothing/DevonLux/LeatherPeasant/ | Aldric top FREE pick; pre-rigged to MetaHuman tall-normal-male skeleton; FBX import + root.00x→root rename; "peasant" reads under merchant — re-skin to lift; attribution required. Score 7/14. |
| DevonLux 4 Piece Cloth Armor (Henryk — top free pick) | character-clothing | Sketchfab | https://sketchfab.com/3d-models/4-piece-cloth-armor-metahuman-rigged-2eb2ee83524545078252d87b33cd13dd | CC-BY ("CC AttributionCreative Commons Attribution" — quoted from page) | manual | YES | AssetStaging/character-clothing/DevonLux/ClothArmor/ | Henryk top FREE pick; loose cloth panels ~ worn robe; bound to tall-normal-male MetaHuman skeleton; FBX import + root rename; attribution required. Score 7/14. |

| Medieval Dress (A9908244) — Mira free-convert base | character-clothing | Sketchfab | https://sketchfab.com/3d-models/medieval-dress-f6b5cf078d044b6cb9764445ecc0cdf0 | CC-BY 4.0 ("CC AttributionCreative Commons Attribution" — quoted from page) | manual | YES | AssetStaging/character-clothing/convert/MiraDress/ | Mira $0 free pick; static mesh (NOT MetaHuman-rigged) → Blender skin-wrap to metahuman_base_skel (rig class c, ~1–3h); 38.8k verts; attribution required. |
| Medieval clothing Free (Red_Ilya) — Lira free-convert base | character-clothing | Sketchfab | https://sketchfab.com/3d-models/medieval-clothing-free-4df74f937a074e8daa9b512dc600422e | CC-BY 4.0 ("CC AttributionCreative Commons Attribution" — quoted from page) | manual | YES | AssetStaging/character-clothing/convert/LiraGarb/ | Lira $0 free pick; static mesh dark leather/gothic, 25k tris, 2K PBR → Blender skin-wrap (rig class c, ~1–3h); dim L_TavernBack carries the hood read; attribution required. |

<!-- Append new rows above this line. One row per asset. Do not delete prior rows. -->
