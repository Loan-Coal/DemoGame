# Appendix: Blender Headless Clothing Workflow (Optional, Free-Only Path)

> **This appendix is optional.** Follow it only if you are using free CC-BY skeletal-mesh garments
> that need skin-weight transfer onto the MetaHuman skeleton. The estimated time budget is **~2 hours
> per garment** for an experienced Blender user. See the **OFF-RAMP** section at the bottom if the
> effort or quality does not meet bar.
>
> **Prerequisites:** Blender 4.x installed and on PATH, `blender` runnable from PowerShell.

---

## Pipeline Overview

Three clothing rig classes exist in this project:

| Class | What it means | Blender work needed |
|-------|--------------|---------------------|
| **(a) MetaHuman Outfit Asset** | `.mhpkg` parametric — auto-fits any MetaHuman body in UE5.8 | **None.** Import directly via Fab plugin. |
| **(b) Already MetaHuman-rigged FBX** | Pre-rigged to `metahuman_base_skel` (e.g. DevonLux CC-BY packs for male NPCs) | Minimal: root bone rename only. |
| **(c) Mannequin or other rig** | FBX rigged to UE4/UE5 Mannequin or Mixamo skeleton | Full skin-weight transfer + IK retarget in UE5. |

**This appendix covers Class (c) only.** Classes (a) and (b) are handled directly in UE5 — see §1 of the main playbook.

---

## ISSUE-015 Caveats (read before starting)

These are live issues logged 2026-06-25:

1. **No +2 cm foot offset:** UE5.6+ MetaHumans removed the `+2 cm` foot offset correction present in
   older fixed-body MetaHumans. If a Class (b)/(c) garment was authored against the legacy body,
   its hem/shoes may float above the ground plane. Fix: in Blender, translate the mesh down 2 cm
   on the Z axis before weight transfer; or re-export against the UE5.8 MetaHuman T-pose mesh.

2. **Parametric body non-conform:** UE5.8 parametric MetaHuman bodies auto-adjust mesh shape to
   body preset sliders. A Class (c) garment skin-wrapped to a specific body shape will clip when
   the body preset changes. Keep body presets fixed per NPC (Medium-Female for Mira/Lira,
   Medium-Male for Sorn, etc.) and do not alter them after clothing is fitted.

3. **Wardrobe validation errors:** UE5.8 has a wardrobe validation system for MetaHuman Outfit Assets
   that checks garment metadata. Non-Outfit-Asset (Class b/c) garments imported as skeletal meshes
   are outside this system — skip/ignore any wardrobe validation warnings for Class b/c imports.
   Locate the toggle in Project Settings → MetaHuman if validation errors block import.

4. **DevonLux root bone rename (Class b):** DevonLux FBX files name the root bone `root.001` or
   `root.00x`. UE5 expects `root`. In Blender: select the Armature → Edit Mode → rename root bone
   to `root`. Export FBX → re-import. Required once per FBX; saved in the re-exported file.

---

## Per-NPC Clothing Plan

| NPC | Free path (Class b/c) | Paid fallback |
|-----|-----------------------|---------------|
| **Mira** (Female, Medium) | Free CC-BY wool dress or apron + chemise from Sketchfab (search `"medieval dress CC0"`) — Class (c), needs full skin-wrap | PolyWear "Medieval Innkeeper" (~$20) |
| **Lira** (Female, Medium) | Free CC-BY hooded cloak + tunic from Sketchfab (search `"medieval rogue hood CC0"`) — Class (c), needs skin-wrap | PolyWear "Rogue Set" (~$20) |
| **Sorn** (Male, Medium) | DevonLux CC-BY Heavy Armor (Sketchfab) — Class (b), root rename only | GrubyCommander Military Armor (Fab) |
| **Aldric** (Male, Medium) | DevonLux CC-BY Merchant Outfit — Class (b), root rename only | PolyWear "Merchant Set" |
| **Henryk** (Male, Medium) | DevonLux CC-BY Peasant Cloth — Class (b), root rename only | PolyWear "Peasant Aged" |

> ⚠️ Verify each Sketchfab CC-BY asset exists and confirms CC license on the asset page before
> downloading. Asset names above are search guidance, not confirmed titles. The DevonLux packs are
> confirmed CC-BY 4.0 as of 2026-06-25.

---

## Class (b) — DevonLux Root Bone Rename

This is the only Blender step needed for Sorn, Aldric, and Henryk.

```powershell
# Run from the project root — PowerShell
blender --background --python Scripts/rename_root_bone.py -- `
    --input "C:\Assets\DevonLux\heavy_armor.fbx" `
    --output "Content/SkeletalMeshes/SK_Sorn_HeavyArmor.fbx"
```

Create `Scripts/rename_root_bone.py`:

```python
"""Rename the MetaHuman-convention root bone in a DevonLux FBX."""
import bpy, sys, argparse

argv = sys.argv[sys.argv.index("--") + 1:]
p = argparse.ArgumentParser()
p.add_argument("--input")
p.add_argument("--output")
args = p.parse_args(argv)

bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=args.input)

arm = next(o for o in bpy.data.objects if o.type == 'ARMATURE')
bpy.context.view_layer.objects.active = arm
bpy.ops.object.mode_set(mode='EDIT')

for bone in arm.data.edit_bones:
    if bone.name.startswith("root.") or bone.name == "root.001":
        bone.name = "root"
        break

bpy.ops.object.mode_set(mode='OBJECT')
bpy.ops.export_scene.fbx(
    filepath=args.output,
    use_selection=False,
    add_leaf_bones=False,
    bake_anim=False,
)
print(f"Exported to {args.output}")
```

**After export:** Import the FBX into UE5 → Skeletal Mesh import → pick `metahuman_base_skel` as
the target skeleton → confirm bone names match (check Skeleton Tree: `root` → `pelvis` → …).

---

## Class (c) — Full Skin-Weight Transfer

For Mira and Lira's dresses from Sketchfab CC-BY sources.

### Step 1 — Prepare Source Files

1. Download the CC-BY dress FBX from Sketchfab.
2. Download the **MetaHuman T-pose reference mesh** from your MetaHuman export
   (`Content/MetaHumans/Mira/SKM_Mira_Body.uasset` → export to FBX via right-click → Asset Actions
   → Export). This is your source body for skin weight reference.

### Step 2 — Headless Align and Weight Transfer

```powershell
blender --background --python Scripts/fit_garment.py -- `
    --body   "C:\Assets\MetaHuman\Mira_Body_TPose.fbx" `
    --garment "C:\Assets\Free\CC0_WoolDress.fbx" `
    --output  "Content/SkeletalMeshes/SK_Mira_WoolDress.fbx"
```

Create `Scripts/fit_garment.py`:

```python
"""
Skin-weight transfer: align a garment to the MetaHuman T-pose body and
bake weights from the body mesh using Blender's Data Transfer modifier.
"""
import bpy, sys, argparse

argv = sys.argv[sys.argv.index("--") + 1:]
p = argparse.ArgumentParser()
p.add_argument("--body")
p.add_argument("--garment")
p.add_argument("--output")
args = p.parse_args(argv)

bpy.ops.wm.read_factory_settings(use_empty=True)

# Import body (has the MetaHuman armature + skin weights)
bpy.ops.import_scene.fbx(filepath=args.body)
body_arm = next(o for o in bpy.data.objects if o.type == 'ARMATURE')
body_mesh = next(o for o in bpy.data.objects if o.type == 'MESH')

# Import garment (may have its own armature; we replace it)
bpy.ops.import_scene.fbx(filepath=args.garment)
garment_mesh = next(
    o for o in bpy.data.objects
    if o.type == 'MESH' and o != body_mesh
)

# Remove garment's own armature (we'll use the MetaHuman one)
for obj in bpy.data.objects:
    if obj.type == 'ARMATURE' and obj != body_arm:
        bpy.data.objects.remove(obj, do_unlink=True)

# Parent garment to MetaHuman armature (without weights first)
garment_mesh.parent = body_arm
garment_mesh.parent_type = 'OBJECT'

# Data Transfer modifier: transfer skin weights from body to garment
mod = garment_mesh.modifiers.new(name="DataTransfer", type='DATA_TRANSFER')
mod.object = body_mesh
mod.use_vert_data = True
mod.data_types_verts = {'VGROUP_WEIGHTS'}
mod.vert_mapping = 'NEAREST'   # use POLYINTERP_NEAREST for better quality on loose meshes

# Apply modifier
bpy.context.view_layer.objects.active = garment_mesh
bpy.ops.object.modifier_apply(modifier="DataTransfer")

# Add Armature modifier so UE5 reads the rig correctly
arm_mod = garment_mesh.modifiers.new(name="Armature", type='ARMATURE')
arm_mod.object = body_arm

# Export — include both armature and garment; exclude body mesh
body_mesh.select_set(False)
garment_mesh.select_set(True)
body_arm.select_set(True)
bpy.context.view_layer.objects.active = garment_mesh

bpy.ops.export_scene.fbx(
    filepath=args.output,
    use_selection=True,
    add_leaf_bones=False,
    bake_anim=False,
    mesh_smooth_type='FACE',
)
print(f"Exported to {args.output}")
```

> ⚠️ `NEAREST` vertex mapping works for form-fitting garments. For loose robes or flowing fabrics
> with larger gaps from the body surface, change `mod.vert_mapping` to `'POLYINTERP_NEAREST'` and
> run a manual visual check in Blender's viewport before exporting (`--background` disables the
> viewport; remove that flag for visual review).

### Step 3 — Visual Inspection (cannot be headless)

The weight transfer must be spot-checked in Blender's GUI or UE5 PIE. Open Blender without
`--background` for the inspection pass:

```powershell
blender "Content/SkeletalMeshes/SK_Mira_WoolDress.blend"
```

Check with a pose test:
1. Select the Armature → Pose Mode.
2. Rotate the `thigh_l` and `spine_01` bones.
3. Confirm the dress deforms without hard creases or stiff patches at the hips/waist.
4. If bad: Weight Paint mode → manually brush problem vertices → re-export.

### Step 4 — Import to UE5 (Leader Pose setup)

1. Content Browser → `Content/SkeletalMeshes/` → Import → pick the output FBX.
2. FBX Import Options:
   - **Import as**: Skeletal Mesh
   - **Skeleton**: `metahuman_base_skel`
   - Uncheck **Import Animations**
3. After import, open the garment Skeletal Mesh asset → **Asset Details** →
   **Skeletal Mesh → LOD Settings → Leader Pose Component Skin** = `SKM_Mira_Body`
   (use Leader Pose to inherit the body's bone transforms — no independent skin needed).
4. In `BP_NPC_Mira`: add the garment Skeletal Mesh as a second component, set Leader Pose Mode.

### Step 5 — Hide Covered Body Sections

MetaHuman bodies are full-skin meshes. Without hiding covered sections, you see body geometry
clipping through the garment.

In UE5 editor → open `SKM_Mira_Body` → **Asset Details → Sections**: identify and uncheck
visibility for sections covered by the garment (typically `Torso`, `Legs`, `Feet`).

Or do it per-instance in `BP_NPC_Mira` Blueprint:
```
Event BeginPlay →
    Set Material (SkeletalMeshComponent=Body, ElementIndex=TorsoSection, Material=M_Invisible)
```

Use `M_Invisible` (a material with Opacity = 0 and Two Sided = false) to hide covered sections
without breaking morph target calculation.

---

## Validation Checklist (per garment)

Before marking a garment done:

- [ ] Root bone named `root` (DevonLux: script ran)
- [ ] No +2 cm foot offset mismatch (dress hem sits at correct ground level)
- [ ] Skin weights inspected — no stiff patches at hips, shoulders, wrists
- [ ] Body sections hidden under the garment (no clipping visible in PIE)
- [ ] `stat gpu` rechecked with garment applied — still < 10 GB

---

## OFF-RAMP

**If any garment exceeds ~2 hours of Blender work or fails the deformation quality bar:**

1. Purchase **PolyWear** (~$20/set) from Fab: search `"PolyWear MetaHuman"` in the Fab plugin.
   These are Class (a) MetaHuman Outfit Assets — `.mhpkg` parametric, auto-fit, no Blender.
2. Import via: Windows → Fab → Add to Project → open MetaHuman Creator → apply outfit to the
   character. (Or use the Outfit Asset import workflow in UE5 → MetaHuman Outfit Asset editor.)
3. Record the purchase and asset name in `project-harness/ASSET_MANIFEST.md`.
4. No Blender work needed for the paid path.

The paid path for all 5 NPCs costs approximately $60–$100 and saves 6–10 hours of Blender work.
This is the recommended choice if the demo deadline is under 2 weeks.
