# DemoGame

Third-person RPG built on Unreal Engine 5.8 + C++, connected to the
[NPC Engine](../NPCSystem) — a FastAPI backend with Neo4j knowledge graph and
Ollama LLM giving NPCs persistent memory, relationships, and dialogue.

---

## Prerequisites

| Tool | Version | Notes |
|------|---------|-------|
| Unreal Engine | 5.8 | Via Epic Games Launcher |
| Visual Studio 2026 | Any edition | "Desktop development with C++" workload required (MSVC toolchain) |
| JetBrains Rider | Latest | Primary IDE; drives MSVC via RiderLink |
| RiderLink | Latest | Rider ↔ UE plugin (install from Rider: Settings → Plugins → search "RiderLink") |
| Git + Git LFS | Any recent | `git lfs install` must have run |

---

## GUI Setup Checklist (one-time)

All items below are confirmed installed on this machine. Steps are for reference / reproduction.

### 1. UE 5.8 project

- Epic Launcher → Library → **Unreal Engine 5.8** → Launch.
- If opening an existing project: Browse → select `DemoGame.uproject`. Click **More Options → Skip Conversion** if prompted about version.
- First open triggers a shader compile pass (~5–15 min). Leave it running.

### 2. Rider + RiderLink

- In Rider: **File → Open** → `DemoGame.uproject` (Rider auto-detects UE C++ projects).
- If RiderLink is not installed: **Settings → Plugins → Marketplace → search "RiderLink"** → Install → restart.
- Build from Rider: **Build → Build Solution** (uses MSVC under the hood via UBT).

### 3. Required plugins (already in DemoGame.uproject)

| Plugin | Source | Why |
|--------|--------|-----|
| MetaHuman | Epic marketplace (install via Launcher) | Hero NPC characters |
| HTTP | Engine built-in (Build.cs dep) | Async REST calls |
| WebSockets | Engine built-in (Build.cs dep) | WS streaming client (scaffolded) |
| Json / JsonUtilities | Engine built-in (Build.cs dep) | JSON serialisation |

MetaHuman plugin must be installed via the Epic Launcher before the first editor open:
> Epic Launcher → Library → Unreal Engine 5.8 → ⚙ → Manage Plugins → MetaHuman → Install.
> Then restart the editor. The plugin is already enabled in `DemoGame.uproject`.

### 4. MetaHuman workflow (slice-1, deferred to tomorrow)

1. Open [MetaHuman Creator](https://metahuman.unrealengine.com/) → create Mira + Lira.
2. Export from Creator → download via UE Quixel Bridge plugin.
3. In-editor: drag the MetaHuman Blueprint into the tavern level.
4. Set the Blueprint's `NpcId` to `mira_innkeeper` / `lira_fence` in the Details panel.
5. Wire the Animation Blueprint (AnimBP) — do NOT hand-code it in C++.

---

## API key and base URL

The game reads connection settings in this priority order:

1. **Environment variables** (recommended for CI / shared machines):
   ```
   NPC_ENGINE_URL=http://localhost:8000
   NPC_ENGINE_API_KEY=local_dev_secret_change_this_2026
   ```

2. **Gitignored ini file** (recommended for local dev):
   ```
   cp Config\NpcEngine.ini.template Config\NpcEngine.ini
   # Edit Config\NpcEngine.ini and fill in ApiKey=
   ```
   `Config/NpcEngine.ini` is in `.gitignore` — never commit it.

The game logs a **Fatal** error at startup if neither source provides the URL or key.

---

## Starting the NPC Engine

```powershell
# From the NPCSystem repo directory:
docker-compose up --build
```

The engine starts on `http://localhost:8000`. Verify with:
```powershell
Invoke-RestMethod http://localhost:8000/health
```
Expected: `{ data: { status: "ok", version: "..." } }`

---

## Seeding the world

The game owns its seed data (`Seed/slice1_tavern.json`) and replays it over REST.

### Option A — In-editor console command (preferred for slice-1)

Run the Unreal editor. In PIE or standalone, open the console (`~`) and type:
```
NpcSmokeTest
```
This first verifies `/health`, then seeds via the engine's built-in `make demo-seed`, then
sends one dialogue message to Mira and logs the response.

Actually for seeding specifically, the engine's `make demo-seed` is the quickest route:
```powershell
# From the NPCSystem repo directory:
make demo-seed
```

### Option B — Engine's own seed command
```powershell
# From the NPCSystem repo directory:
make demo-seed
```

---

## Smoke test

### Terminal (no Unreal required)

```powershell
# Step 1: health
Invoke-RestMethod http://localhost:8000/health

# Step 2: dialogue
$h = @{ Authorization = "Bearer $env:NPC_ENGINE_API_KEY" }
Invoke-RestMethod `
  -Method Post `
  -Uri http://localhost:8000/v1/dialogue `
  -Headers $h `
  -ContentType application/json `
  -Body (@{ player_id="player_demo"; npc_id="mira_innkeeper"; player_message="Good evening, Mira." } | ConvertTo-Json)
```

Expected: HTTP 200 with a non-empty `npc_response`.

### In-editor (C++ via Exec command)

1. Start PIE (Play In Editor).
2. Open the console (`~`).
3. Type: `NpcSmokeTest`
4. Check the **Output Log** for:
   ```
   NpcSmokeTest | Health: OK
   NpcSmokeTest | Mira says: "..."
   === NpcSmokeTest PASS ===
   ```

---

## Ollama — GPU vs CPU during development

**Binding constraint:** RTX 5070 Ti has ~12 GB VRAM.
- `qwen2.5:14b` on GPU uses ~9–10 GB VRAM.
- MetaHuman + Lumen + Nanite in UE editor uses 4–8 GB VRAM.
- Running both simultaneously exceeds 12 GB → crashes / severe stutter.

### Recommended dev workflow: GPU + smaller model

Run `qwen2.5:7b` (or `qwen2.5:3b`) on GPU during Unreal development for fast iteration.
Swap back to `qwen2.5:14b` for final demo captures / recordings.

```powershell
# In the NPCSystem docker-compose or .env:
# OLLAMA_MODEL=qwen2.5:7b   ← dev
# OLLAMA_MODEL=qwen2.5:14b  ← final captures

# Pull the smaller model first:
ollama pull qwen2.5:7b
```

### Alternative: CPU mode

If VRAM conflicts still occur, force Ollama to CPU (uses ~50 GB RAM instead):
```bash
# In docker-compose.yml or Ollama env:
OLLAMA_NUM_GPU=0
```
Trade-off: dialogue latency increases (~5–30 s on CPU). Acceptable because every call is async.

---

## Performance checklist

- [ ] Max 2 hero MetaHumans per scene (Mira + Lira in tavern; background NPCs use cheaper rigs).
- [ ] Ollama model matches VRAM headroom (7b for dev, 14b for captures).
- [ ] All NPC Engine calls async — never block game thread.
- [ ] Dialogue timeout: 30 s (CPU Ollama is slow). Health timeout: 3 s.
- [ ] Lumen + Nanite enabled (GPU rendering); disable in editor when iterating on C++ only.
- [ ] Close Rider Hot-Reload during shader / LLM sessions to free RAM.

---

## Project structure

```
Source/
  NpcEngineClient/        ← standalone C++ module: all NPC Engine HTTP/WS logic
    Public/
      NpcEngineTypes.h    ← USTRUCTs matching the engine contract
      NpcEngineConfig.h   ← URL + key loader (env var / gitignored ini)
      NpcEngineRestClient.h  ← async REST client
      NpcEngineWsClient.h    ← WS streaming client (built, not wired in slice-1)
      NpcEngineSeedClient.h  ← replays Seed/slice1_tavern.json
      PlayerIdProvider.h     ← player_id generation/persistence
      NpcEngineJsonUtils.h   ← JSON helpers (both response shapes)
  DemoGame/
    NPC/
      NpcActorBase.h/.cpp          ← NPC actor base (carries stable NpcId)
      NpcInteractionComponent.h/.cpp  ← interact trigger
    Dialogue/
      DialogueManager.h/.cpp       ← world subsystem owning conversations
      DialogueWidgetBase.h/.cpp    ← C++ UMG widget base (layout in editor)
Seed/
  slice1_tavern.json       ← game-owned seed data (locations, NPCs, edges)
docs/
  ENGINE_CONTRACT.md       ← authoritative integration contract
  openapi.json             ← curated OpenAPI subset
  STORYBOARD.md            ← slice roadmap + beat breakdown
Config/
  NpcEngine.ini.template   ← copy → NpcEngine.ini, fill in key (gitignored)
```

---

## What's next (tomorrow)

1. UMG layout: open `DialogueWidgetBase` in the UMG editor, add EditableText + TextBlock, bind the BindWidgetOptional slots.
2. MetaHuman: import Mira + Lira, place in tavern level, assign `NpcId`.
3. Tavern level: place trigger volumes, wire player enter → open widget.
4. Interact input: bind Enhanced Input "Interact" action → call `UNpcInteractionComponent::TryInteract`.
5. Fill in `BeginDialogue` / `EndDialogue` from the player controller / interaction component.
6. Animation Blueprint: hook `FacialExpression` data to blend tree (slice-2+).
