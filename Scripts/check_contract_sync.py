#!/usr/bin/env python3
# File: check_contract_sync.py
# Purpose: Verify the NpcEngineClient mirror USTRUCTs carry every field of their openapi.json schema.
# Net I/O: no
#
# The two-repo rule: USTRUCTs in Source/NpcEngineClient mirror docs/openapi.json. This is a PRESENCE
# check (every contract field is represented), not a full type check.
#
# Matching convention: each mirrored UPROPERTY is annotated with its JSON name via
#     UPROPERTY(..., meta=(JsonName="npc_response"))
# If a mirror header exists but carries no JsonName annotations, the check cannot match fields and
# emits a NOTICE (not a failure) explaining the required convention.
#
# Output: `MISSING|<Schema>.<field>` per missing field. Exit 1 if any missing. SKIP (exit 0) when no
# mirror headers exist yet or annotations are absent.

import json
import os
import re
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(SCRIPT_DIR)
OPENAPI = os.path.join(ROOT, "docs", "openapi.json")
CLIENT_PUBLIC = os.path.join(ROOT, "Source", "NpcEngineClient", "Public")
CLIENT_DIR = os.path.join(ROOT, "Source", "NpcEngineClient")

# Contract schemas whose fields must be mirrored.
SCHEMAS = [
    "DialogueRequest",
    "DialogueResponse",
    "RelationDeltas",
    "ActionModel",
    "FacialExpressionModel",
]

JSONNAME_RE = re.compile(r'JsonName\s*=\s*"([^"]+)"')


def schema_fields(openapi, name):
    schemas = openapi.get("components", {}).get("schemas", {})
    node = schemas.get(name)
    if not node:
        return None
    return list(node.get("properties", {}).keys())


def collect_jsonnames():
    """Return the set of all JsonName values found across NpcEngineClient headers."""
    names = set()
    found_headers = False
    search_dir = CLIENT_PUBLIC if os.path.isdir(CLIENT_PUBLIC) else CLIENT_DIR
    if not os.path.isdir(search_dir):
        return names, False
    for dp, _, files in os.walk(search_dir):
        for f in files:
            if not f.endswith(".h"):
                continue
            found_headers = True
            with open(os.path.join(dp, f), encoding="utf-8", errors="replace") as fh:
                for m in JSONNAME_RE.finditer(fh.read()):
                    names.add(m.group(1))
    return names, found_headers


def main():
    if not os.path.isfile(OPENAPI):
        print("check_contract_sync: docs/openapi.json not found - SKIP")
        return 0

    if not os.path.isdir(CLIENT_DIR):
        print("check_contract_sync: no Source/NpcEngineClient yet - SKIP")
        return 0

    with open(OPENAPI, encoding="utf-8") as fh:
        openapi = json.load(fh)

    jsonnames, found_headers = collect_jsonnames()
    if not found_headers:
        print("check_contract_sync: no mirror USTRUCT headers yet - SKIP")
        return 0

    if not jsonnames:
        print("check_contract_sync: NOTICE - mirror headers found but NO JsonName annotations.")
        print("  Annotate each mirrored UPROPERTY: UPROPERTY(..., meta=(JsonName=\"<json_field>\"))")
        print("  to enable contract-sync field matching. SKIP (cannot verify).")
        return 0

    missing = []
    for schema in SCHEMAS:
        fields = schema_fields(openapi, schema)
        if fields is None:
            print(f"check_contract_sync: NOTICE - schema {schema} not in openapi.json, skipping")
            continue
        for field in fields:
            if field not in jsonnames:
                missing.append((schema, field))

    for schema, field in missing:
        print(f"MISSING|{schema}.{field}")

    if missing:
        print(f"check_contract_sync: {len(missing)} contract field(s) not mirrored")
        return 1
    print("check_contract_sync: PASS (all contract fields mirrored)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
