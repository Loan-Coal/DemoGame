#!/usr/bin/env python3
# File: check_rules.py
# Purpose: Static rule linter for the DemoGame harness. Regex/structure checks over Source/**/*.{h,cpp}.
# Net I/O: no
#
# Clean repo -> zero hits, so every rule is HARD from day 1. Pre-existing template/scaffold files are
# grandfathered for the header & file-size rules only (see Scripts/.rules_legacy.txt); all content rules
# (net I/O, JSON, URL/endpoint literals, npc_id literals, on-screen logging) apply to EVERY file.
#
# Output: one `RULE|<rule_name>|<relpath>:<line>` line per hit. Exit 1 if any hit, else 0.
# No Source/ dir yet -> exit 0 (no-op pass).
#
# Extending: append a tuple to CONTENT_RULES below. Each rule is independent of the others.
#
# Per-line suppression (content rules): put `// rules-allow: <rule_name>` (or bare `// rules-allow`)
# on the offending line. File-level: `// rules-allow-file: <rule_name>` in the first 10 lines.

import os
import re
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(SCRIPT_DIR)
SOURCE_DIR = os.path.join(ROOT, "Source")
BASELINE_FILE = os.path.join(SCRIPT_DIR, ".rules_legacy.txt")

CPP_LINE_LIMIT = 500
H_LINE_LIMIT = 200

# Known stable npc_id values (engine contract). Must not appear as raw literals in gameplay.
NPC_IDS = ["mira_innkeeper", "lira_fence", "aldric_merchant", "captain_sorn", "old_henryk"]

# Content rules: (name, compiled_regex, include_prefixes, exclude_prefixes)
# Matched against COMMENT-STRIPPED text (string literals preserved, comments blanked), so doc comments
# that legitimately reference the contract do not trip these.
CONTENT_RULES = [
    (
        "net_io_outside_client",
        re.compile(r"\bFHttpModule\b|\bFWebSocketsModule\b|\bIWebSocket\b|\bFHttpRequest\b"),
        ["Source/DemoGame/"],
        [],
    ),
    (
        "json_in_game",
        re.compile(r"\bFJsonObject\b|\bJsonUtilities\b|\bFJsonSerializer\b|\bTJsonReader\b"),
        ["Source/DemoGame/"],
        [],
    ),
    (
        "url_or_endpoint_literal",
        re.compile(r'"http://|/v1/'),
        ["Source/"],
        ["Source/NpcEngineClient/"],
    ),
    (
        "hardcoded_npc_id",
        re.compile("|".join(re.escape(n) for n in NPC_IDS)),
        ["Source/DemoGame/"],
        [],
    ),
    (
        "onscreen_or_stdio_logging",
        re.compile(r"AddOnScreenDebugMessage|\bprintf\b|std::cout"),
        ["Source/"],
        [],
    ),
]

HEADER_RE = re.compile(r"//\s*File:")
ALLOW_LINE_RE = re.compile(r"//\s*rules-allow(?::\s*(?P<name>[\w-]+))?")
ALLOW_FILE_RE = re.compile(r"//\s*rules-allow-file:\s*(?P<name>[\w-]+)")


def load_baseline():
    legacy = set()
    if os.path.isfile(BASELINE_FILE):
        with open(BASELINE_FILE, encoding="utf-8") as fh:
            for line in fh:
                line = line.strip()
                if line and not line.startswith("#"):
                    legacy.add(line.replace("\\", "/"))
    return legacy


def strip_comments(text):
    """Blank // and /* */ comments (replaced with spaces, newlines preserved); keep string/char
    literals intact so URL and npc_id literals are still detectable."""
    out = []
    i, n = 0, len(text)
    state = "normal"  # normal | line | block | string | char
    while i < n:
        c = text[i]
        nxt = text[i + 1] if i + 1 < n else ""
        if state == "normal":
            if c == "/" and nxt == "/":
                state = "line"
                out.append("  ")
                i += 2
                continue
            if c == "/" and nxt == "*":
                state = "block"
                out.append("  ")
                i += 2
                continue
            if c == '"':
                state = "string"
                out.append(c)
            elif c == "'":
                state = "char"
                out.append(c)
            else:
                out.append(c)
            i += 1
        elif state == "line":
            if c == "\n":
                state = "normal"
                out.append("\n")
            else:
                out.append(" ")
            i += 1
        elif state == "block":
            if c == "*" and nxt == "/":
                state = "normal"
                out.append("  ")
                i += 2
                continue
            out.append("\n" if c == "\n" else " ")
            i += 1
        elif state == "string":
            out.append(c)
            if c == "\\":
                if nxt:
                    out.append(nxt)
                    i += 2
                    continue
            elif c == '"':
                state = "normal"
            i += 1
        elif state == "char":
            out.append(c)
            if c == "\\":
                if nxt:
                    out.append(nxt)
                    i += 2
                    continue
            elif c == "'":
                state = "normal"
            i += 1
    return "".join(out)


def under(relpath, prefixes):
    return any(relpath.startswith(p) for p in prefixes)


def file_allows(raw_lines):
    allowed = set()
    for line in raw_lines[:10]:
        m = ALLOW_FILE_RE.search(line)
        if m:
            allowed.add(m.group("name"))
    return allowed


def line_allows(raw_line, rule_name):
    for m in ALLOW_LINE_RE.finditer(raw_line):
        nm = m.group("name")
        if nm is None or nm == rule_name:
            return True
    return False


def check_file(path, relpath, legacy):
    hits = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        raw = fh.read()
    raw_lines = raw.splitlines()
    file_allowed = file_allows(raw_lines)
    is_legacy = relpath in legacy

    # Content rules (every file).
    code = strip_comments(raw)
    code_lines = code.splitlines()
    for name, rx, inc, exc in CONTENT_RULES:
        if name in file_allowed:
            continue
        if not under(relpath, inc) or under(relpath, exc):
            continue
        for idx, cline in enumerate(code_lines):
            if rx.search(cline):
                raw_line = raw_lines[idx] if idx < len(raw_lines) else ""
                if line_allows(raw_line, name):
                    continue
                hits.append((name, relpath, idx + 1))

    # Header rule (skipped for grandfathered files).
    if not is_legacy and "missing_file_header" not in file_allowed:
        head = raw_lines[:5]
        if not any(HEADER_RE.search(l) for l in head):
            hits.append(("missing_file_header", relpath, 1))

    # Size rule (skipped for grandfathered files).
    if not is_legacy and "file_too_long" not in file_allowed:
        count = len(raw_lines)
        limit = CPP_LINE_LIMIT if relpath.endswith(".cpp") else H_LINE_LIMIT
        if count > limit:
            hits.append(("file_too_long", relpath, count))

    # Spec guard rule: every Tests/*.spec.cpp must be wrapped in #if WITH_DEV_AUTOMATION_TESTS.
    if (
        "missing_spec_automation_guard" not in file_allowed
        and relpath.endswith(".spec.cpp")
        and "/Tests/" in relpath
    ):
        if not any("#if WITH_DEV_AUTOMATION_TESTS" in l for l in raw_lines):
            hits.append(("missing_spec_automation_guard", relpath, 1))

    return hits


def main():
    if not os.path.isdir(SOURCE_DIR):
        print("check_rules: no Source/ directory yet - PASS (no-op)")
        return 0

    legacy = load_baseline()
    all_hits = []
    for dp, _, files in os.walk(SOURCE_DIR):
        for f in files:
            if not f.endswith((".cpp", ".h")):
                continue
            path = os.path.join(dp, f)
            relpath = os.path.relpath(path, ROOT).replace("\\", "/")
            all_hits.extend(check_file(path, relpath, legacy))

    all_hits.sort(key=lambda h: (h[1], h[2], h[0]))
    for name, relpath, line in all_hits:
        print(f"RULE|{name}|{relpath}:{line}")

    if all_hits:
        print(f"check_rules: {len(all_hits)} violation(s)")
        return 1
    print("check_rules: PASS (0 violations)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
