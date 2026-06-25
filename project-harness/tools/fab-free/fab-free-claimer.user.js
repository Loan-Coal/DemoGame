// ==UserScript==
// @name         Fab Free Claimer (DemoGame)
// @namespace    demogame.assets
// @version      1.0.0
// @description  One-click claim every free asset on the Fab "Limited-Time Free" / free-filter pages, using YOUR logged-in session. Pairs with the biweekly reminder task so you never miss the rotating free drop.
// @match        https://www.fab.com/limited-time-free*
// @match        https://www.fab.com/search*
// @run-at       document-idle
// @grant        none
// ==/UserScript==

/*
 * WHY A USERSCRIPT (not a headless scraper):
 *   fab.com returns HTTP 403 to non-browser requests (bot protection), and claiming requires an
 *   authenticated session (CSRF cookie + add-to-library POST). A standalone scheduled scraper would
 *   be blocked AND would force you to store Fab credentials. A userscript runs inside your already
 *   logged-in browser tab, so it reuses your live session — no stored secrets, nothing to refresh.
 *
 * HONEST CAVEAT (read once):
 *   This automates an action you are entitled to do by hand (clicking "Add to Library" on a $0 item).
 *   It only ever claims items whose price is 0. It does not bypass payment, scrape paid content, or
 *   touch your password. Automating account actions may still be against Fab/Epic Terms of Service —
 *   review them; using this is your call. Conservative default: AUTO_RUN = false (you press the button).
 *
 * ENDPOINTS (sourced from the Subtixx gist, fetched 2026-06-25 — VERIFY if Fab changed them):
 *   GET  /i/listings/{id}                         -> listing detail incl. offers/licenses
 *   GET  /i/users/me/listings-states?listing_ids= -> which listings you already own (max 24 per call)
 *   POST /i/listings/{id}/add-to-library          -> claim (body: offer_id=...), header X-CsrfToken
 *   To verify: open DevTools > Network on the free page, click a real "Add to Library", inspect the call.
 */

(function () {
  'use strict';

  // ---- CONFIG (override here if Fab's API shape shifts) -------------------------------------------
  const CONFIG = {
    AUTO_RUN: false,            // true = claim on page load with no click. Leave false to stay in control.
    REQUEST_DELAY_MS: 600,      // politeness gap between claims (gist used 500ms)
    CSRF_COOKIE: 'fab_csrftoken',
    CSRF_HEADER: 'X-CsrfToken',
    LISTING_HREF_RE: /\/listings\/([0-9a-f-]{36})/i, // listing UUID in card links
  };
  // ------------------------------------------------------------------------------------------------

  const log = (...a) => console.log('%c[FabFree]', 'color:#7c5cff;font-weight:bold', ...a);
  const sleep = (ms) => new Promise((r) => setTimeout(r, ms));

  function getCookie(name) {
    const m = document.cookie.match(new RegExp('(?:^|; )' + name + '=([^;]*)'));
    return m ? decodeURIComponent(m[1]) : null;
  }

  // Collect unique listing UUIDs from every card link on the current page.
  function collectListingIds() {
    const ids = new Set();
    document.querySelectorAll('a[href*="/listings/"]').forEach((a) => {
      const m = a.getAttribute('href').match(CONFIG.LISTING_HREF_RE);
      if (m) ids.add(m[1]);
    });
    return [...ids];
  }

  async function fetchJson(url, opts) {
    const res = await fetch(url, Object.assign({ credentials: 'include' }, opts));
    if (!res.ok) throw new Error(`${url} -> HTTP ${res.status}`);
    return res.json();
  }

  // Find the price-0 offer on a listing. Field names vary; we probe the likely ones and log misses.
  function findFreeOfferId(listing) {
    const offers = listing.offers || listing.licenseOfferings || listing.licenses || [];
    for (const o of offers) {
      const price = o.price ?? o.priceTier?.price ?? o.amount ?? null;
      const free = price === 0 || price === '0' || o.isFree === true || /free/i.test(o.name || '');
      if (free) return o.uid || o.id || o.offerId || o.offer_id || null;
    }
    return null;
  }

  async function ownedSet(ids) {
    // listings-states caps at 24 ids per request.
    const owned = new Set();
    for (let i = 0; i < ids.length; i += 24) {
      const chunk = ids.slice(i, i + 24);
      const qs = chunk.map((id) => `listing_ids=${id}`).join('&');
      try {
        const states = await fetchJson(`/i/users/me/listings-states?${qs}`);
        const arr = Array.isArray(states) ? states : states.results || [];
        arr.forEach((s) => {
          if (s.acquired || s.isAcquired || s.owned || s.inLibrary) owned.add(s.uid || s.listingId || s.listing_id);
        });
      } catch (e) {
        log('ownership check failed (will attempt claims anyway):', e.message);
      }
      await sleep(150);
    }
    return owned;
  }

  async function claim(id) {
    const csrf = getCookie(CONFIG.CSRF_COOKIE);
    if (!csrf) throw new Error(`no ${CONFIG.CSRF_COOKIE} cookie — are you logged in?`);
    const listing = await fetchJson(`/i/listings/${id}`);
    const offerId = findFreeOfferId(listing);
    const title = listing.title || listing.name || id;
    if (!offerId) { log(`skip "${title}" — no free offer found`); return false; }
    const res = await fetch(`/i/listings/${id}/add-to-library`, {
      method: 'POST',
      credentials: 'include',
      headers: {
        [CONFIG.CSRF_HEADER]: csrf,
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: `offer_id=${encodeURIComponent(offerId)}`,
    });
    if (res.ok) { log(`✅ claimed "${title}"`); return true; }
    log(`❌ "${title}" -> HTTP ${res.status}`);
    return false;
  }

  async function run() {
    const ids = collectListingIds();
    if (!ids.length) { log('no listing cards found on this page'); return; }
    log(`found ${ids.length} listings; checking ownership…`);
    const owned = await ownedSet(ids);
    const todo = ids.filter((id) => !owned.has(id));
    log(`${todo.length} not yet owned; claiming…`);
    let ok = 0;
    for (const id of todo) {
      try { if (await claim(id)) ok++; } catch (e) { log('claim error:', e.message); }
      await sleep(CONFIG.REQUEST_DELAY_MS);
    }
    log(`done — ${ok}/${todo.length} newly claimed. Refresh your Fab Library to confirm.`);
    alert(`Fab Free Claimer: ${ok} new free asset(s) claimed. Check your Library.`);
  }

  function addButton() {
    if (document.getElementById('fabfree-btn')) return;
    const btn = document.createElement('button');
    btn.id = 'fabfree-btn';
    btn.textContent = '⬇ Claim all free';
    Object.assign(btn.style, {
      position: 'fixed', bottom: '20px', right: '20px', zIndex: 99999,
      padding: '12px 18px', background: '#7c5cff', color: '#fff', border: 'none',
      borderRadius: '8px', fontWeight: '700', cursor: 'pointer', boxShadow: '0 4px 14px rgba(0,0,0,.3)',
    });
    btn.onclick = () => { btn.disabled = true; btn.textContent = 'Claiming…'; run().finally(() => { btn.disabled = false; btn.textContent = '⬇ Claim all free'; }); };
    document.body.appendChild(btn);
  }

  addButton();
  if (CONFIG.AUTO_RUN) setTimeout(run, 2500);
})();
