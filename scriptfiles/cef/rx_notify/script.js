/* =====================================================================
   rx-notify  ·  SA-MP + CEF
   Reemplazo de sh_notify con el notify de RX Scripts.

   Evento desde Pawn (CEF_EmitEvent):
     "rx:notify" -> (title, text, type, length, position, confetti)

   Tambien acepta los eventos viejos, por si algo sigue emitiendo SH:
     "sh:notify" -> (text, type, length, caption)
     "sh:local"  -> (text, type, length)
   ===================================================================== */

const CONFIG = {
    position:        "lc",
    defaultLength:   3000,
    maxVisible:      5,
    exitAnimMs:      300,
    sound:           true,
    soundVolume:     0.22,
    defaultTitles: {
        enabled: true,
        success: "Éxito",
        warn:    "Aviso",
        error:   "Error",
        info:    "Info"
    },
    colors: {
        background:    "#131415",
        textPrimary:   "#F7FAFC",
        textSecondary: "#A0AEC0",
        success:       "#10B981",
        warning:       "#F59E0B",
        error:         "#a52b2a",
        info:          "#3B82F6"
    }
};

const TYPE_ALIAS = {
    "": "info", "nil": "info", "default": "info", "inform": "info", "primary": "info",
    "info": "info", "police": "info",
    "success": "success", "open": "success",
    "error": "error", "closed": "error", "ambulance": "error",
    "warn": "warn", "warning": "warn"
};

const POSITIONS = { tl: 1, tc: 1, tr: 1, lc: 1, rc: 1, bl: 1, bc: 1, br: 1 };

const ICONS = {
    success: `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path fill-rule="evenodd" d="M2.25 12c0-5.385 4.365-9.75 9.75-9.75s9.75 4.365 9.75 9.75-4.365 9.75-9.75 9.75S2.25 17.385 2.25 12zm13.36-1.814a.75.75 0 10-1.22-.872l-3.236 4.53L9.53 12.22a.75.75 0 00-1.06 1.06l2.25 2.25a.75.75 0 001.14-.094l3.75-5.25z" clip-rule="evenodd"/></svg>`,
    error: `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path fill-rule="evenodd" d="M12 2.25c-5.385 0-9.75 4.365-9.75 9.75s4.365 9.75 9.75 9.75 9.75-4.365 9.75-9.75S17.385 2.25 12 2.25zm-1.72 6.97a.75.75 0 10-1.06 1.06L10.94 12l-1.72 1.72a.75.75 0 101.06 1.06L12 13.06l1.72 1.72a.75.75 0 101.06-1.06L13.06 12l1.72-1.72a.75.75 0 10-1.06-1.06L12 10.94l-1.72-1.72z" clip-rule="evenodd"/></svg>`,
    warn: `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path fill-rule="evenodd" d="M9.401 3.003c1.155-2 4.043-2 5.197 0l7.355 12.748c1.154 2-.29 4.5-2.599 4.5H4.645c-2.309 0-3.752-2.5-2.598-4.5L9.4 3.003zM12 8.25a.75.75 0 01.75.75v3.75a.75.75 0 01-1.5 0V9a.75.75 0 01.75-.75zm0 8.25a.75.75 0 100-1.5.75.75 0 000 1.5z" clip-rule="evenodd"/></svg>`,
    info: `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path fill-rule="evenodd" d="M2.25 12c0-5.385 4.365-9.75 9.75-9.75s9.75 4.365 9.75 9.75-4.365 9.75-9.75 9.75S2.25 17.385 2.25 12zm8.706-1.442c1.146-.573 2.437.463 2.126 1.706l-.709 2.836.042-.02a.75.75 0 01.67 1.34l-.04.022c-1.147.573-2.438-.463-2.127-1.706l.71-2.836-.042.02a.75.75 0 11-.671-1.34l.041-.022zM12 9a.75.75 0 100-1.5.75.75 0 000 1.5z" clip-rule="evenodd"/></svg>`
};

const timers = new Map();
let seq = 0;
let audioCtx = null;
let bits = [];
let confettiRaf = 0;

function normType(type) {
    const key = String(type == null ? "" : type).toLowerCase().trim();
    return TYPE_ALIAS[key] || "info";
}

function colorKey(type) {
    return type === "warn" ? "warning" : type;
}

function normPos(position) {
    const key = String(position == null ? "" : position).toLowerCase().trim();
    return POSITIONS[key] ? key : CONFIG.position;
}

function toMs(value) {
    const n = parseInt(value, 10);
    return (isNaN(n) || n <= 0) ? CONFIG.defaultLength : n;
}

function asBool(value) {
    return value === true || value === 1 || value === "1" || value === "true";
}

function sideOf(pos) {
    if (pos === "tc") return "top";
    if (pos === "bc") return "bottom";
    if (pos === "tl" || pos === "lc" || pos === "bl") return "left";
    return "right";
}

function progressOf(pos) {
    if (pos === "tr" || pos === "rc" || pos === "br") return "shrink-right";
    return "shrink-left";
}

function dismiss(el) {
    if (!el || el.dataset.leaving === "1") return;
    el.dataset.leaving = "1";
    const pending = timers.get(el.dataset.id);
    if (pending) {
        clearTimeout(pending);
        timers.delete(el.dataset.id);
    }
    el.classList.remove("animate-slide-left", "animate-slide-right", "animate-slide-top", "animate-slide-bottom");
    el.classList.add("animate-out-" + (el.dataset.side || "left"));
    setTimeout(() => el.remove(), CONFIG.exitAnimMs + 40);
}

function trim(container) {
    const alive = container.querySelectorAll(":scope > .rx-card:not([data-leaving='1'])");
    for (let i = 0; i < alive.length - CONFIG.maxVisible; i++) dismiss(alive[i]);
}

function playSound(type) {
    if (!CONFIG.sound) return;
    try {
        audioCtx = audioCtx || new AudioContext();
        if (audioCtx.state === "suspended") audioCtx.resume();
        const now = audioCtx.currentTime;
        const pair = type === "error" ? [392, 262]
            : type === "warn" ? [494, 370]
            : type === "success" ? [659, 880]
            : [698, 880];
        const osc = audioCtx.createOscillator();
        const gain = audioCtx.createGain();
        osc.type = "sine";
        osc.frequency.setValueAtTime(pair[0], now);
        osc.frequency.setValueAtTime(pair[1], now + 0.08);
        gain.gain.setValueAtTime(0.0001, now);
        gain.gain.exponentialRampToValueAtTime(CONFIG.soundVolume, now + 0.02);
        gain.gain.exponentialRampToValueAtTime(0.0001, now + 0.26);
        osc.connect(gain);
        gain.connect(audioCtx.destination);
        osc.start(now);
        osc.stop(now + 0.28);
    } catch (e) { /* CEF sin audio */ }
}

function confettiOrigin(pos) {
    const w = window.innerWidth;
    const h = window.innerHeight;
    let x = w * 0.5;
    let y = h * 0.5;
    if (pos === "tl" || pos === "lc" || pos === "bl") x = w * 0.14;
    else if (pos === "tr" || pos === "rc" || pos === "br") x = w * 0.86;
    if (pos === "tl" || pos === "tc" || pos === "tr") y = h * 0.12;
    else if (pos === "bl" || pos === "bc" || pos === "br") y = h * 0.88;
    return { x, y };
}

function tickConfetti() {
    const canvas = document.getElementById("rx-confetti");
    if (!canvas) { confettiRaf = 0; return; }
    const ctx = canvas.getContext("2d");
    const dpr = Math.min(window.devicePixelRatio || 1, 2);
    const w = window.innerWidth;
    const h = window.innerHeight;
    if (canvas.width !== Math.floor(w * dpr) || canvas.height !== Math.floor(h * dpr)) {
        canvas.width = Math.floor(w * dpr);
        canvas.height = Math.floor(h * dpr);
    }
    ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    ctx.clearRect(0, 0, w, h);
    const next = [];
    for (let i = 0; i < bits.length; i++) {
        const q = bits[i];
        q.life -= 1;
        if (q.life <= 0) continue;
        q.vy += q.g;
        q.x += q.vx;
        q.y += q.vy;
        q.rot += q.vr;
        ctx.save();
        ctx.translate(q.x, q.y);
        ctx.rotate(q.rot);
        ctx.globalAlpha = Math.max(q.life / 50, 0);
        ctx.fillStyle = q.color;
        ctx.fillRect(-q.w / 2, -q.h / 2, q.w, q.h);
        ctx.restore();
        next.push(q);
    }
    bits = next;
    if (bits.length) confettiRaf = requestAnimationFrame(tickConfetti);
    else {
        confettiRaf = 0;
        ctx.clearRect(0, 0, w, h);
    }
}

function burstConfetti(pos) {
    const origin = confettiOrigin(pos);
    const colors = ["#10B981", "#3B82F6", "#F59E0B", "#EF4444", "#8B5CF6"];
    for (let i = 0; i < 90; i++) {
        const angle = Math.random() * Math.PI * 2;
        const speed = 3.2 + Math.random() * 7;
        bits.push({
            x: origin.x,
            y: origin.y,
            vx: Math.cos(angle) * speed,
            vy: Math.sin(angle) * speed - 2.4,
            g: 0.14 + Math.random() * 0.08,
            w: 4 + Math.random() * 4,
            h: 6 + Math.random() * 5,
            rot: Math.random() * 6,
            vr: (Math.random() - 0.5) * 0.28,
            color: colors[i % colors.length],
            life: 64 + Math.random() * 28
        });
    }
    if (!confettiRaf) confettiRaf = requestAnimationFrame(tickConfetti);
}

function showNotify(title, text, type, length, position, confetti, opts) {
    const kind = normType(type);
    const pos = normPos(position);
    const ms = toMs(length);
    let heading = title == null ? "" : String(title);
    let body = text == null ? "" : String(text);

    if (!heading && CONFIG.defaultTitles.enabled) {
        heading = CONFIG.defaultTitles[kind] || "Info";
    }
    if (!heading && !body) return;

    const container = document.getElementById("rx-" + pos);
    if (!container) return;

    const accent = CONFIG.colors[colorKey(kind)] || CONFIG.colors.info;
    const side = sideOf(pos);
    const id = String(++seq);

    const card = document.createElement("div");
    card.className = "rx-card animate-slide-" + side + (body ? "" : " is-solo");
    card.dataset.id = id;
    card.dataset.side = side;
    card.style.setProperty("--accent-color", accent);
    card.style.setProperty("--text-primary", CONFIG.colors.textPrimary);
    card.style.setProperty("--text-secondary", CONFIG.colors.textSecondary);
    card.style.backgroundColor = CONFIG.colors.background;
    card.style.borderLeftColor = accent;
    card.setAttribute("role", "alert");

    const content = document.createElement("div");
    content.className = "rx-content";

    const icon = document.createElement("div");
    icon.className = "rx-icon";
    icon.innerHTML = ICONS[kind] || ICONS.info;
    content.appendChild(icon);

    const wrap = document.createElement("div");
    wrap.className = "rx-text";
    if (heading) {
        const h = document.createElement("h3");
        h.className = "rx-title";
        h.textContent = heading;
        wrap.appendChild(h);
    }
    if (body) {
        const p = document.createElement("p");
        p.className = "rx-desc" + (heading ? "" : " is-large");
        p.textContent = body;
        wrap.appendChild(p);
    }
    content.appendChild(wrap);
    card.appendChild(content);

    const track = document.createElement("div");
    track.className = "rx-progress";
    const bar = document.createElement("div");
    bar.className = "rx-progress-bar progress-" + progressOf(pos);
    bar.style.animationDuration = ms + "ms";
    bar.style.backgroundColor = accent;
    track.appendChild(bar);
    card.appendChild(track);

    container.appendChild(card);
    trim(container);

    timers.set(id, setTimeout(() => dismiss(card), ms));

    if (!opts || opts.sound !== false) playSound(kind);
    if (asBool(confetti)) burstConfetti(pos);
}

function clearAll() {
    document.querySelectorAll(".rx-card").forEach((el) => el.remove());
    timers.forEach((t) => clearTimeout(t));
    timers.clear();
}

if (new URLSearchParams(location.search).get("studio") === "1") {
    document.documentElement.classList.add("studio");
    const wide = window.innerWidth >= 860;
    const boot = wide
        ? [
            ["Banco", "Recibiste $2.500", "success", 12000, "lc", 0],
            ["", "No tenés dinero suficiente", "error", 12000, "lc", 0],
            ["Aviso", "Zona peligrosa cerca", "warn", 12000, "tr", 0]
        ]
        : [
            ["Banco", "Recibiste $2.500", "success", 12000, "lc", 0],
            ["", "No tenés dinero suficiente", "error", 12000, "lc", 0]
        ];
    boot.forEach((row, i) => {
        setTimeout(() => showNotify(row[0], row[1], row[2], row[3], row[4], row[5], { sound: false }), 40 + i * 160);
    });
}

window.rxNotify = {
    notify: showNotify,
    clear: clearAll,
    config: CONFIG
};

if (typeof cef !== "undefined") {
    cef.on("rx:notify", (title, text, type, length, position, confetti) => {
        showNotify(title, text, type, length, position, confetti);
    });
    cef.on("sh:notify", (text, type, length, caption) => {
        if (caption) showNotify(text, caption, type, length, "", 0);
        else showNotify("", text, type, length, "", 0);
    });
    cef.on("sh:local", (text, type, length) => {
        showNotify(text, "", type, length, "tc", 0);
    });
} else if (location.hash === "#demo") {
    document.body.style.background = "#12131a";
    const demo = [
        ["Éxito", "Acción completada", "success", 5000, "lc", 0],
        ["", "No tenés dinero suficiente", "error", 5200, "lc", 0],
        ["Aviso", "Zona peligrosa cerca", "warn", 5400, "lc", 0],
        ["Servidor", "Nuevo anuncio en el foro", "info", 5600, "lc", 0]
    ];
    demo.forEach((row, i) => setTimeout(() => showNotify(...row), 350 + i * 650));
    setTimeout(() => showNotify("Burgershot abrió sus puertas", "", "open", 6000, "tc", 1), 3000);
}
