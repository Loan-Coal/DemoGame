# Fab Free Claimer + biweekly reminder

Never miss Fab's rotating free drop. Fab releases **3 new assets free every 2 weeks**, and you must
**claim them during the 2-week window** to keep them forever ([CG Channel, 2024-11](https://www.cgchannel.com/2024/11/epic-games-to-share-new-free-assets-on-fab-every-two-weeks/);
[Fab Limited-Time Free](https://www.fab.com/limited-time-free)). Anything you claim while free is yours
permanently under the Fab Standard License (Epic-ecosystem, commercial use OK — no `swap_for_commercial` flag).

## Why a userscript, not a headless scraper

- fab.com returns **HTTP 403 to non-browser requests** (bot protection) — a standalone scheduled scraper
  is blocked outright.
- Claiming requires your **authenticated session** (CSRF cookie + `POST /i/listings/{id}/add-to-library`).
  A background script would have to **store your Fab credentials/cookies** and refresh them — brittle and
  a security liability.
- A **userscript runs inside your already-logged-in browser tab**, reusing your live session. No stored
  secrets, nothing to refresh.

So the design is: **scheduled reminder opens the page** + (optional) **userscript one-click claims**. Reminder-first.

## When the cycle resets

New free assets drop and the previous set expires at the **same moment: 9:59 AM ET** on rotation day.
Rotation is **every 2 weeks, usually Tuesday ~10 AM ET — but it drifts** (e.g. one 2025 cycle ended Monday
May 19, while Apr 22 and Jun 3 were Tuesdays). Don't hard-code a day; the
[Limited-Time Free page](https://www.fab.com/limited-time-free) always prints the live "Until \<date\> at 9:59 AM ET".

**Use a WEEKLY reminder, not biweekly.** Each asset is free for a full 14 days, so a 7-day check can never
miss a cycle (you see every drop with ≥7 days to spare). A 14-day timer can drift out of phase with Fab's
clock and skip one. The schedule command below is therefore weekly.

## Honest caveat (read once)

`fab-free-claimer.user.js` automates an action you may do by hand (clicking "Add to Library" on a $0 item).
It only ever claims items whose price is **0** — it does not bypass payment or touch paid content. Automating
account actions *may* still conflict with Fab/Epic Terms of Service; review them — using this is your call.
The conservative default is `AUTO_RUN = false` (you press the "Claim all free" button).

## Setup (one time, ~5 min)

1. **Install a userscript manager:** [Tampermonkey](https://www.tampermonkey.net/) (Chrome/Edge) or
   [Violentmonkey](https://violentmonkey.github.io/) (Firefox).
2. **Add the script:** open `fab-free-claimer.user.js`, copy its contents into a new userscript, save.
   (Or drag the `.user.js` file onto the Tampermonkey dashboard.)
3. **Log into fab.com** in that browser.
4. **Schedule the weekly reminder** (shows a popup + opens the free page). From the repo root in PowerShell
   (no admin needed for a per-user task):
   ```powershell
   schtasks /Create /TN "Fab Free Reminder" /SC WEEKLY /D MON /ST 09:00 `
     /TR "powershell -NoProfile -WindowStyle Hidden -File `"$PWD\project-harness\tools\fab-free\fab-free-reminder.ps1`""
   ```
   Weekly (every Monday 09:00) is miss-proof for the 2-week window — see "When the cycle resets" above.
   Adjust `/D` (day) and `/ST` (time) to taste. Add `-IncludeFreeFilter` to the task to also open the
   permanently-free catalog. Remove later with `schtasks /Delete /TN "Fab Free Reminder"`.

## Use

- **Automatic:** every 14 days the task opens the Limited-Time Free page; click the purple **"⬇ Claim all
  free"** button (bottom-right). Or set `AUTO_RUN = true` in the script's CONFIG to skip the click.
- **Manual any time:** visit <https://www.fab.com/limited-time-free> and click the button.
- **Verify:** open your [Fab Library](https://www.fab.com/library) — newly claimed packs appear there, then
  import into UE5.8 via **Windows → Fab → Library → Add to Project**.

## If Fab changes its API

The endpoints came from the [Subtixx gist](https://gist.github.com/Subtixx/47f6db9ceabf51c3f689db1594a50b37)
(fetched 2026-06-25) and may drift. To re-verify: open **DevTools → Network** on the free page, click a real
"Add to Library", and read the actual request. Update the `CONFIG` block / `findFreeOfferId` field names at the
top of `fab-free-claimer.user.js`. The script logs `[FabFree]` lines to the console so you can see exactly where
it stops.

## Files

| File | What |
|------|------|
| `fab-free-claimer.user.js` | Browser userscript — adds "Claim all free" to Fab free pages, claims via your session |
| `fab-free-reminder.ps1` | Opens the Fab free page in your browser; schedule it every 14 days |
| `README.md` | This file |
