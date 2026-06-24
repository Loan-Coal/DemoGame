<#
.SYNOPSIS
  DemoGame quality gate - the one command. Runs every gate in order, prints PASS/FAIL/SKIP per gate,
  and exits non-zero if any gate fails.

.DESCRIPTION
  Gates:
    1. Rules            check_rules.py            (HARD; runs even with no Source/)
    2. Contract sync    check_contract_sync.py    (HARD; SKIPs until mirror USTRUCTs are annotated)
    3. Build            Build.bat                 (opt-in: -WithBuild; otherwise SKIP)
    4. Automation tests UnrealEditor-Cmd          (opt-in: -WithBuild/-WithTests; otherwise SKIP)
    5. Presence         spec + smoke present       (arms once the client module grows tests)

  Build/test are OPT-IN: a frequently-run gate must not trigger a multi-minute UE cook by default.
  Pass -WithBuild to compile and run Automation tests. See project-harness/HARNESS_GATES.md.

.EXAMPLE
  pwsh Scripts/check.ps1
  pwsh Scripts/check.ps1 -WithBuild
#>
[CmdletBinding()]
param(
    [switch]$WithBuild,
    [switch]$WithTests
)

$ErrorActionPreference = "Stop"
$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$Root = Split-Path -Parent $ScriptDir
$Failures = 0

function Resolve-Python {
    foreach ($c in @("python", "python3", "py")) {
        $cmd = Get-Command $c -ErrorAction SilentlyContinue
        if ($cmd) { return $cmd.Source }
    }
    return $null
}

function Write-Gate {
    param([string]$Name, [string]$Status, [string]$Note = "")
    $tag = switch ($Status) {
        "PASS" { "PASS" }
        "FAIL" { "FAIL" }
        default { "SKIP" }
    }
    $line = "[{0}] {1}" -f $tag, $Name
    if ($Note) { $line += " - $Note" }
    Write-Host $line
}

$python = Resolve-Python
Write-Host "=== DemoGame quality gate ==="

# ---- Gate 1: Rules -------------------------------------------------------------------------------
if (-not $python) {
    Write-Gate "Rules" "FAIL" "python not found on PATH"
    $Failures++
}
else {
    $out = & $python (Join-Path $ScriptDir "check_rules.py") 2>&1
    $code = $LASTEXITCODE
    $out | ForEach-Object { Write-Host "    $_" }
    if ($code -eq 0) { Write-Gate "Rules" "PASS" }
    else { Write-Gate "Rules" "FAIL"; $Failures++ }
}

# ---- Gate 2: Contract sync -----------------------------------------------------------------------
if (-not $python) {
    Write-Gate "Contract sync" "SKIP" "python not found"
}
else {
    $out = & $python (Join-Path $ScriptDir "check_contract_sync.py") 2>&1
    $code = $LASTEXITCODE
    $out | ForEach-Object { Write-Host "    $_" }
    if ($code -eq 0) { Write-Gate "Contract sync" "PASS" }
    else { Write-Gate "Contract sync" "FAIL"; $Failures++ }
}

# ---- Locate the project --------------------------------------------------------------------------
$uproject = Get-ChildItem -Path $Root -Filter "*.uproject" -File -ErrorAction SilentlyContinue |
    Select-Object -First 1

# ---- Gate 3: Build -------------------------------------------------------------------------------
if (-not $uproject) {
    Write-Gate "Build" "SKIP" "no .uproject yet"
}
elseif (-not ($WithBuild)) {
    Write-Gate "Build" "SKIP" "opt-in - pass -WithBuild to compile"
}
else {
    $assoc = (Get-Content $uproject.FullName -Raw | ConvertFrom-Json).EngineAssociation
    $buildBat = $null
    foreach ($p in @(
        "C:\Program Files\Epic Games\UE_$assoc\Engine\Build\BatchFiles\Build.bat",
        "C:\Program Files\Epic Games\UE_5.8\Engine\Build\BatchFiles\Build.bat"
    )) {
        if (Test-Path $p) { $buildBat = $p; break }
    }
    if (-not $buildBat) {
        Write-Gate "Build" "SKIP" "Build.bat not found for engine '$assoc'"
    }
    else {
        & $buildBat DemoGameEditor Win64 Development -project="$($uproject.FullName)" -waitmutex
        if ($LASTEXITCODE -eq 0) { Write-Gate "Build" "PASS" }
        else { Write-Gate "Build" "FAIL" "Build.bat exit $LASTEXITCODE"; $Failures++ }
    }
}

# ---- Gate 4: Automation tests --------------------------------------------------------------------
if (-not $uproject) {
    Write-Gate "Automation tests" "SKIP" "no .uproject yet"
}
elseif (-not ($WithBuild -or $WithTests)) {
    Write-Gate "Automation tests" "SKIP" "opt-in - pass -WithBuild/-WithTests to run"
}
else {
    $assoc = (Get-Content $uproject.FullName -Raw | ConvertFrom-Json).EngineAssociation
    $editorCmd = $null
    foreach ($p in @(
        "C:\Program Files\Epic Games\UE_$assoc\Engine\Binaries\Win64\UnrealEditor-Cmd.exe",
        "C:\Program Files\Epic Games\UE_5.8\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
    )) {
        if (Test-Path $p) { $editorCmd = $p; break }
    }
    if (-not $editorCmd) {
        Write-Gate "Automation tests" "SKIP" "UnrealEditor-Cmd not found"
    }
    else {
        $log = Join-Path $Root "Saved\Logs\AutomationCheck.log"
        if (Test-Path $log) { Remove-Item $log -Force -ErrorAction SilentlyContinue }
        # No ";Quit" - let -testexit wait for the async queue to drain. Verdict comes from the log,
        # not the exit code (UnrealEditor-Cmd exit codes are unreliable: SDK-validate noise etc.).
        & $editorCmd $uproject.FullName `
            -ExecCmds="Automation RunTests NpcEngine" `
            -unattended -nopause -nosplash -nullrhi -testexit="Automation Test Queue Empty" -log -abslog="$log" | Out-Null
        $ran = $false; $failed = $false
        if (Test-Path $log) {
            $hits = Select-String -Path $log -Pattern 'Test Completed|Result=\{Fail|Result=\{Error|Automation Test Failed'
            $ran = [bool]($hits | Where-Object { $_.Line -match 'Test Completed' })
            $failed = [bool]($hits | Where-Object { $_.Line -match 'Result=\{Fail|Result=\{Error|Automation Test Failed' })
        }
        if ($ran -and -not $failed) { Write-Gate "Automation tests" "PASS" }
        elseif (-not $ran) { Write-Gate "Automation tests" "FAIL" "no tests ran - see $log"; $Failures++ }
        else { Write-Gate "Automation tests" "FAIL" "test failures - see $log"; $Failures++ }
    }
}

# ---- Gate 5: Presence (replaces coverage) --------------------------------------------------------
$clientDir = Join-Path $Root "Source\NpcEngineClient"
if (-not (Test-Path $clientDir)) {
    Write-Gate "Presence" "SKIP" "NpcEngineClient module not created yet"
}
else {
    $specs = Get-ChildItem -Path $clientDir -Recurse -Filter "*.spec.cpp" -File -ErrorAction SilentlyContinue
    $hasSpec = $null -ne $specs -and $specs.Count -gt 0
    $sourceDir = Join-Path $Root "Source"
    $sourceFiles = Get-ChildItem -Path $sourceDir -Recurse -Include *.cpp, *.h -File -ErrorAction SilentlyContinue
    # Match the registered exec command literal (quoted), not bare comment mentions.
    $smokeHits = $sourceFiles | Select-String -Pattern '"NpcEngine\.Smoke"' -ErrorAction SilentlyContinue
    $hasSmoke = $null -ne $smokeHits -and @($smokeHits).Count -gt 0

    if ($hasSpec -and $hasSmoke) {
        Write-Gate "Presence" "PASS" "client specs + NpcEngine.Smoke present"
    }
    elseif (-not $hasSpec -and -not $hasSmoke) {
        # Module scaffolded but no tests yet - gate arms when the first spec/smoke lands.
        Write-Gate "Presence" "SKIP" "module scaffolded; specs + smoke pending (Slice-1)"
    }
    else {
        $missing = @()
        if (-not $hasSpec) { $missing += "no *.spec.cpp under NpcEngineClient" }
        if (-not $hasSmoke) { $missing += "no NpcEngine.Smoke exec command" }
        Write-Gate "Presence" "FAIL" ($missing -join "; ")
        $Failures++
    }
}

# ---- Verdict -------------------------------------------------------------------------------------
Write-Host ""
if ($Failures -eq 0) {
    Write-Host "CHECK: PASS"
    exit 0
}
else {
    Write-Host "CHECK: FAIL ($Failures gate(s))"
    exit 1
}
