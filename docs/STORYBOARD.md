# DemoGame — Story / Slice Roadmap

## Slice roadmap

| Slice | Location | NPCs | Goal |
|-------|----------|------|------|
| **1 — Tavern** | The Broken Flagon (`loc_tavern`) | `mira_innkeeper`, `lira_fence` | Prove the pipe: free-text dialogue, NPC memory, relationship deltas, emotion |
| **2 — Village** | Market square + guard barracks | `aldric_merchant`, `captain_sorn`, `old_henryk` | Gossip chain, 2-hop distortion, faction knowledge |
| **3+ — Outward** | TBD (forests, dungeons, court) | TBD | Full world, quests, multi-NPC planning |

---

## Slice 1 — TAVERN (filled)

### Location: The Broken Flagon
- Worn wooden interior; firelight; low murmur of other patrons (background NPCs, NOT full MetaHumans).
- Two hero MetaHuman NPCs maximum: **Mira** (behind bar) + **Lira** (corner booth).
- Player enters via tavern door transition trigger.

### Seed NPCs

| NpcId | Name | Position | Personality | Slice-1 role |
|-------|------|----------|-------------|--------------|
| `mira_innkeeper` | Mira | Behind the bar | Warm but guarded; 70% honest; gossipy. Never says more than she needs to. | Smoke-test target; main dialogue hub |
| `lira_fence` | Lira | Corner booth, hood up | Light, deflective. Turns every question into a joke. 30% honest. | Optional second conversation |

### Demo conversation beats

The following beats are designed to showcase individual engine features in a single session.

#### Beat 1 — First contact (engine feature: fresh-session memory)
- Player walks up to Mira, presses Interact.
- Player types: *"Good evening, Mira."*
- Mira greets the player and sizes them up. The engine has no prior memory → neutral greeting.
- **Shows:** dialogue works end-to-end; session_id returned for continuity.

#### Beat 2 — Fishing for gossip (engine feature: gossip propagation)
- Player types: *"Heard anything interesting lately?"*
- Mira deflects ("Quiet night… so far.") or mentions a rumour depending on graph state.
- **Shows:** knowledge graph context injected into LLM prompt.

#### Beat 3 — Trust-building action (engine feature: relationship delta)
- Player types: *"I'll have the good ale and I'll pay double."*
- Mira's `affection` delta ticks up; `trust` may follow.
- **Shows:** relation_deltas returned and logged (visual feedback in slice-2+).

#### Beat 4 — Emotional probe (engine feature: emotion / mood)
- Player types: *"Something's worrying you. What is it?"*
- Mira's `emotion` field shifts (e.g. "anxious"). facial_expression.type hints at animation.
- **Shows:** emotion tracking + facial_expression data (wired to AnimBP in slice-2+).

#### Beat 5 — Return session (engine feature: persistent memory)
- End dialogue (player walks away), then return and interact again.
- Player types: *"It's me again, Mira."*
- Mira references the previous meeting (engine's memory nodes recall the prior session).
- **Shows:** session_id continuity + NPC memory across sessions.

#### Optional — Lira (engine feature: faction / honesty gap)
- Player approaches Lira's booth.
- Player types: *"Are you… for hire?"*
- Lira deflects with humour. Her low honesty score (30%) means responses are more evasive.
- **Shows:** per-NPC personality parameters shaping LLM output.

### Engine features demonstrated in Slice 1

| Feature | Engine field/mechanism | Beat |
|---------|----------------------|------|
| LLM dialogue | `npc_response` | All |
| Session continuity | `session_id` round-trip | 1, 5 |
| Persistent memory | `memories_recalled`, memory nodes | 5 |
| Relationship change | `relation_deltas` (trust/fear/affection) | 3 |
| Emotion / mood | `emotion`, `mood_update` | 4 |
| Facial expression hint | `facial_expression.type + intensity` | 4 |
| Knowledge / gossip | graph context in LLM prompt | 2 |
| Degradation resilience | `degradation_level`, client fallback | Always-on |

### Out of scope for Slice 1 (deferred)
- Audio (TTS) — hook is built, not wired.
- WebSocket streaming — client is built, not wired.
- Relationship UI overlay — wire in slice-2.
- Faction/gossip chain across multiple NPCs — slice-2.
- Quest triggers — slice-3+.
