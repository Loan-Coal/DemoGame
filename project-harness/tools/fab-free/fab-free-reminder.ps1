# File: fab-free-reminder.ps1
# Purpose: Open the Fab "Limited-Time Free" page in the default browser so the companion userscript
#          (fab-free-claimer.user.js) auto-claims the rotating free drop. Schedule this every ~14 days.
# Net I/O: opens a URL in your browser only — no headless fetch (fab.com 403s non-browser requests),
#          no stored credentials. The claim happens in your logged-in browser session via the userscript.

[CmdletBinding()]
param(
    # The biweekly rotating free assets. The general free filter is also opened so permanently-free items get swept too.
    [string]$LimitedTimeUrl = 'https://www.fab.com/limited-time-free',
    [string]$FreeFilterUrl  = 'https://www.fab.com/search?ui_filter_price=1&is_free=1',
    [switch]$IncludeFreeFilter
)

# Optional desktop popup so it reads as a reminder even if a browser is already open.
try {
    Add-Type -AssemblyName System.Windows.Forms -ErrorAction Stop
    [void][System.Windows.Forms.MessageBox]::Show(
        "Fab's free assets rotate every 2 weeks (cutoff 9:59 AM ET, usually Tuesday but it drifts).`n`nOpening the Limited-Time Free page — claim anything new before its 'Until <date>' deadline.",
        'Fab free-asset check', 'OK', 'Information')
} catch { }

Write-Host "[fab-free-reminder] Opening Fab Limited-Time Free…" -ForegroundColor Magenta
Start-Process $LimitedTimeUrl

if ($IncludeFreeFilter) {
    Start-Sleep -Seconds 2
    Start-Process $FreeFilterUrl
}

# Schedule WEEKLY (not biweekly): each asset is free for 14 days, so a 7-day check can never miss a
# cycle, whereas a 14-day timer can drift out of phase with Fab's clock and skip one.
Write-Host "Tip: the Fab Free Claimer userscript adds a 'Claim all free' button on that page." -ForegroundColor DarkGray
Write-Host "Register a WEEKLY reminder (miss-proof for the 2-week window) with:" -ForegroundColor DarkGray
Write-Host '  schtasks /Create /TN "Fab Free Reminder" /SC WEEKLY /D MON /ST 09:00 ^' -ForegroundColor DarkGray
Write-Host '    /TR "powershell -NoProfile -WindowStyle Hidden -File \"%CD%\project-harness\tools\fab-free\fab-free-reminder.ps1\""' -ForegroundColor DarkGray
