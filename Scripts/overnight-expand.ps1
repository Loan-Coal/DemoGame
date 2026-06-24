<#
.SYNOPSIS
  Overnight autonomous roadmap runner. Repeatedly invokes Claude Code headless to advance
  ROADMAP.md ONE phase at a time, each in a FRESH session (clean context, no ballooning).

.DESCRIPTION
  Each iteration:
    1. Records git HEAD.
    2. Runs `claude -p` (fresh session) with Scripts/overnight-prompt.md as the instruction set.
       The session does one phase's headless work, runs the full gate, commits per step, and
       logs any Unreal-Editor-only work to project-harness/HUMAN_VERIFICATION.md.
    3. Compares git HEAD. New commit -> progress -> continue. No commit -> stop.
  Session output (stream-json) is saved per iteration to project-harness/overnight-logs/ for
  the morning tool-usage analysis (Scripts/extract_tools.py).

  Runs with --dangerously-skip-permissions so nothing blocks unattended. Stays on the CURRENT
  branch, commits per phase, never pushes. Stop early by creating a file named STOP-OVERNIGHT
  in the project root.

.PARAMETER MaxIterations
  Hard cap on phases attempted (default 12). Backstop against runaway loops.

.PARAMETER Model
  Model for the headless sessions (default "sonnet"). Use "opus" for max quality at higher cost.

.PARAMETER MaxTurns
  Per-session turn cap (default 300). Backstop against a single session running away.

.EXAMPLE
  powershell -NoProfile -ExecutionPolicy Bypass -File Scripts\overnight-expand.ps1
  powershell -NoProfile -ExecutionPolicy Bypass -File Scripts\overnight-expand.ps1 -Model opus -MaxIterations 8
#>
[CmdletBinding()]
param(
    [int]$MaxIterations = 12,
    [string]$Model = "sonnet",
    [int]$MaxTurns = 300
)

$ErrorActionPreference = "Continue"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$Root = Split-Path -Parent $ScriptDir
$PromptFile = Join-Path $ScriptDir "overnight-prompt.md"
$LogDir = Join-Path $Root "project-harness\overnight-logs"
$StopFile = Join-Path $Root "STOP-OVERNIGHT"
$RunLog = Join-Path $LogDir "run.log"

New-Item -ItemType Directory -Force -Path $LogDir | Out-Null

function Log([string]$msg) {
    $stamp = (Get-Date).ToString("yyyy-MM-dd HH:mm:ss")
    $line = "[$stamp] $msg"
    Write-Host $line
    Add-Content -Path $RunLog -Value $line -Encoding utf8
}

# ---- Preflight -----------------------------------------------------------------------------------
if (-not (Get-Command claude -ErrorAction SilentlyContinue)) {
    Log "FATAL: 'claude' CLI not found on PATH. Install Claude Code or add it to PATH."
    exit 1
}
if (-not (Test-Path $PromptFile)) {
    Log "FATAL: prompt file missing: $PromptFile"
    exit 1
}
Push-Location $Root
$branch = (git rev-parse --abbrev-ref HEAD).Trim()
$dirty = (git status --porcelain) | Where-Object { $_ -notmatch '^\?\? Content/' -and $_ -notmatch '^\?\? STOP-OVERNIGHT' -and $_ -notmatch 'overnight-logs/' }
if ($dirty) {
    Log "WARNING: working tree has uncommitted non-Content changes. The first phase commit may absorb them."
    $dirty | ForEach-Object { Log "    $_" }
}

$prompt = Get-Content -Raw $PromptFile
Log "=== Overnight runner start | branch=$branch | model=$Model | maxIter=$MaxIterations ==="

# ---- Loop ----------------------------------------------------------------------------------------
$completed = 0
for ($i = 1; $i -le $MaxIterations; $i++) {

    if (Test-Path $StopFile) {
        Log "STOP-OVERNIGHT file present -> stopping before iteration ${i}."
        break
    }

    $before = (git rev-parse HEAD).Trim()
    $stream = Join-Path $LogDir ("iter{0:D2}.stream.jsonl" -f $i)
    Log "--- Iteration ${i}/$MaxIterations | HEAD before = $($before.Substring(0,8)) ---"

    # Fresh headless session. stdin carries the prompt; stream-json captured for tool analysis.
    # --dangerously-skip-permissions: required for unattended; tool usage is logged for review.
    $prompt | & claude -p `
        --output-format stream-json --verbose `
        --dangerously-skip-permissions `
        --model $Model `
        --max-turns $MaxTurns *> $stream

    $after = (git rev-parse HEAD).Trim()
    $status = (Select-String -Path $stream -Pattern 'OVERNIGHT-RUNNER:.*' -ErrorAction SilentlyContinue |
               Select-Object -Last 1).Line
    if (-not $status) { $status = "(no status line emitted)" }

    if ($after -ne $before) {
        $n = (git rev-list --count "$before..$after")
        $completed++
        Log "Iteration ${i}: PROGRESS - $n new commit(s). HEAD=$($after.Substring(0,8)). $status"
    }
    else {
        Log "Iteration ${i}: NO NEW COMMIT. $status"
        if ($status -match 'NO HEADLESS WORK REMAINING') {
            Log "Runner reports no headless work remaining -> stopping."
        }
        else {
            Log "No commit produced (blocked or stalled) -> stopping to avoid spinning."
        }
        break
    }
}

Pop-Location
Log "=== Overnight runner done | phases advanced this run: $completed ==="
Log "Next: review project-harness/HUMAN_VERIFICATION.md, then run: python Scripts/extract_tools.py"
