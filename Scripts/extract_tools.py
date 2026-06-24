#!/usr/bin/env python3
"""Post-run analyzer for the overnight loop.

Reads the stream-json session logs produced by overnight-expand.ps1
(project-harness/overnight-logs/*.stream.jsonl), extracts every tool the autonomous
runner invoked, dedupes them, and reports which are NOT already covered by the allow
list in .claude/settings.local.json. Use the report to build an accurate permission
allowlist for future non-skip runs.

Usage:  python Scripts/extract_tools.py
Net I/O: no.
"""
from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LOG_DIR = ROOT / "project-harness" / "overnight-logs"
SETTINGS = ROOT / ".claude" / "settings.local.json"


def iter_tool_uses(stream_path: Path):
    """Yield (tool_name, command_or_path) for every tool_use block in a stream log."""
    for line in stream_path.read_text(encoding="utf-8", errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            evt = json.loads(line)
        except json.JSONDecodeError:
            continue
        msg = evt.get("message", {})
        content = msg.get("content", []) if isinstance(msg, dict) else []
        if not isinstance(content, list):
            continue
        for block in content:
            if isinstance(block, dict) and block.get("type") == "tool_use":
                inp = block.get("input", {}) or {}
                detail = inp.get("command") or inp.get("file_path") or inp.get("path") or ""
                yield block.get("name", "?"), str(detail)[:100]


def load_allow() -> list[str]:
    if not SETTINGS.exists():
        return []
    try:
        data = json.loads(SETTINGS.read_text(encoding="utf-8"))
        return data.get("permissions", {}).get("allow", [])
    except Exception:
        return []


def main() -> int:
    if not LOG_DIR.exists():
        print(f"No log dir at {LOG_DIR} — run the overnight loop first.")
        return 0

    seen: dict[str, set[str]] = {}
    for stream in sorted(LOG_DIR.glob("*.stream.jsonl")):
        for tool, detail in iter_tool_uses(stream):
            seen.setdefault(tool, set()).add(detail)

    if not seen:
        print("No tool_use events found in the logs.")
        return 0

    allow = load_allow()
    print("=== Tools used by the overnight runner ===\n")
    for tool in sorted(seen):
        details = sorted(d for d in seen[tool] if d)
        covered = any(tool in rule or rule.startswith(tool) for rule in allow)
        flag = "" if covered else "   <-- NOT in allowlist"
        print(f"{tool}  ({len(seen[tool])} distinct){flag}")
        for d in details[:12]:
            print(f"    {d}")
        if len(details) > 12:
            print(f"    ... (+{len(details) - 12} more)")
        print()

    print("Build allowlist entries from the above, e.g.:")
    print('  "Bash(git status*)", "Bash(git diff*)", "Edit", "Write", "Grep", "Glob",')
    print('  "PowerShell(*check.ps1 -WithBuild -WithTests*)"')
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
