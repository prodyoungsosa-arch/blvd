/* =========================================================
   INVENTARIO - logica de la interfaz (omp-cef / Aurora CEF)

   PAWN  -> JS  (cef.on)                    JS -> PAWN (cef.emit)
   -------------------------------------    ----------------------------------
   inv:open                                 inv:ready
   inv:close                                inv:close
   inv:clear                                inv:use   (slot)
   inv:slot  (slot, itemid, amount)         inv:move  (from, to, amount)
   inv:info  (maxWeight, money, name)       inv:drop  (slot, amount)
   inv:notify(text, type)                   inv:give  (slot, amount)

   Slots 0-29  = mochila (los 0-4 son tambien la barra rapida)
   Slots 30-35 = equipamiento
   ========================================================= */
(function () {
    'use strict';

    var BAG = 30;
    var TOTAL = 36;
    var HOTBAR = 5;

    var EQUIP = [
        { slot: 30, type: 'head',   label: 'CABEZA',  ph: '🧢' },
        { slot: 31, type: 'body',   label: 'TORSO',   ph: '🦺' },
        { slot: 32, type: 'legs',   label: 'PIERNAS', ph: '👖' },
        { slot: 33, type: 'feet',   label: 'CALZADO', ph: '👟' },
        { slot: 34, type: 'weapon', label: 'ARMA',    ph: '🔫' },
        { slot: 35, type: 'acc',    label: 'MOCHILA', ph: '🎒' }
    ];

    var ITEMS = window.INV_ITEMS || {};
    var RARITY = window.INV_RARITY || {};

    var st = {
        slots: [],
        maxWeight: 30,
        money: 0,
        sel: -1,
        visible: false,
        search: ''
    };
    for (var n = 0; n < TOTAL; n++) st.slots.push(null);

    /* ---------- helpers ---------- */

    function $(sel, root) { return (root || document).querySelector(sel); }
    function $$(sel, root) { return Array.prototype.slice.call((root || document).querySelectorAll(sel)); }

    function def(id) {
        return ITEMS[id] || {
            name: 'Objeto #' + id, icon: '❔', cat: 'Varios', rarity: 'common',
            weight: 0, stack: 1, equip: null, desc: 'Objeto desconocido.'
        };
    }

    function fmtKg(v) { return (Math.round(v * 100) / 100).toFixed(v >= 10 ? 1 : 2).replace(/\.?0+$/, '') + ' kg'; }
    function fmtMoney(v) { return String(Math.floor(v)).replace(/\B(?=(\d{3})+(?!\d))/g, '.'); }

    function isImage(icon) { return /\.(png|jpe?g|webp|gif|svg)$/i.test(icon || ''); }

    function fillIcon(el, icon) {
        el.textContent = '';
        if (isImage(icon)) {
            var img = document.createElement('img');
            img.src = 'img/' + icon;
            img.alt = '';
            img.draggable = false;
            el.appendChild(img);
        } else {
            el.textContent = icon || '❔';
        }
    }

    function rarityClass(item) { return 'r-' + def(item).rarity; }

    /* ---------- puente con el servidor ---------- */

    var hasCef = !!(window.cef && typeof window.cef.on === 'function' && typeof window.cef.emit === 'function');
    var demo = !hasCef || /[?&]demo/.test(location.search);
    var listeners = {};

    function onServer(name, cb) {
        listeners[name] = cb;
        if (hasCef) window.cef.on(name, cb);
    }

    function emit(name) {
        var args = Array.prototype.slice.call(arguments, 1);
        if (hasCef) window.cef.emit.apply(window.cef, [name].concat(args));
        else mockServer(name, args);
    }

    /* ---------- logica de mover (idéntica a la del Pawn) ---------- */

    function canPlace(slot, itemId) {
        if (slot < BAG) return true;
        return def(itemId).equip === EQUIP[slot - BAG].type;
    }

    function moveLogic(from, to, amount) {
        if (from === to || from < 0 || to < 0 || from >= TOTAL || to >= TOTAL) return false;
        var src = st.slots[from];
        if (!src) return false;
        if (!amount || amount <= 0 || amount > src.amount) amount = src.amount;
        if (!canPlace(to, src.item)) return false;

        var dst = st.slots[to];
        var stack = def(src.item).stack;

        if (!dst) {
            if (amount > stack) amount = stack;
            st.slots[to] = { item: src.item, amount: amount };
            src.amount -= amount;
            if (src.amount <= 0) st.slots[from] = null;
            return true;
        }

        if (dst.item === src.item && stack > 1) {
            var space = stack - dst.amount;
            if (space <= 0) return false;
            if (amount > space) amount = space;
            dst.amount += amount;
            src.amount -= amount;
            if (src.amount <= 0) st.slots[from] = null;
            return true;
        }

        if (amount !== src.amount) return false;
        if (!canPlace(from, dst.item)) return false;
        st.slots[from] = dst;
        st.slots[to] = src;
        return true;
    }

    /* ---------- construccion del DOM ---------- */

    function makeSlot(i, opts) {
        opts = opts || {};
        var el = document.createElement('div');
        el.className = 'slot';
        el.setAttribute('data-slot', i);
        if (opts.type) el.setAttribute('data-type', opts.type);

        var key = document.createElement('span');
        key.className = 'key';
        if (i < HOTBAR && !opts.equip) key.textContent = String(i + 1);
        el.appendChild(key);

        var ico = document.createElement('span');
        ico.className = 'ico';
        el.appendChild(ico);

        var qty = document.createElement('span');
        qty.className = 'qty';
        el.appendChild(qty);

        if (opts.equip) {
            var ph = document.createElement('span');
            ph.className = 'ph';
            ph.innerHTML = '<b>' + opts.equip.ph + '</b><em>' + opts.equip.label + '</em>';
            el.appendChild(ph);
        }
        return el;
    }

    function build() {
        var grid = $('#grid');
        for (var i = 0; i < BAG; i++) grid.appendChild(makeSlot(i));

        var stage = $('#equip');
        EQUIP.forEach(function (e) { stage.appendChild(makeSlot(e.slot, { type: e.type, equip: e })); });

        var hb = $('#hotbar');
        for (var h = 0; h < HOTBAR; h++) hb.appendChild(makeSlot(h));
    }

    /* ---------- render ---------- */

    function renderSlot(i) {
        var data = st.slots[i];
        var q = st.search;

        $$('.slot[data-slot="' + i + '"]').forEach(function (el) {
            el.className = el.className.replace(/\b(has|sel|dim|r-\w+)\b/g, '').replace(/\s+/g, ' ').trim();

            var ico = $('.ico', el);
            var qty = $('.qty', el);

            if (data) {
                var d = def(data.item);
                el.classList.add('has', rarityClass(data.item));
                fillIcon(ico, d.icon);
                qty.textContent = data.amount > 1 ? 'x' + data.amount : '';
                if (q && d.name.toLowerCase().indexOf(q) === -1) el.classList.add('dim');
            } else {
                ico.textContent = '';
                qty.textContent = '';
            }

            if (st.sel === i) el.classList.add('sel');
        });
    }

    function renderAll() {
        for (var i = 0; i < TOTAL; i++) renderSlot(i);
        renderWeight();
        renderDetail();
    }

    function totalWeight() {
        var w = 0;
        st.slots.forEach(function (s) { if (s) w += def(s.item).weight * s.amount; });
        return w;
    }

    function renderWeight() {
        var w = totalWeight();
        var pct = st.maxWeight > 0 ? Math.min(100, (w / st.maxWeight) * 100) : 0;
        $('#wCur').textContent = (Math.round(w * 10) / 10).toFixed(1);
        $('#wMax').textContent = (Math.round(st.maxWeight * 10) / 10).toFixed(1);
        var f = $('#wFill');
        f.style.width = pct + '%';
        f.className = pct >= 95 ? 'full' : (pct >= 75 ? 'warn' : '');
    }

    function renderMoney() { $('#money').textContent = fmtMoney(st.money); }

    function getQty() {
        var s = st.slots[st.sel];
        var v = parseInt($('#qty').value, 10);
        if (isNaN(v) || v < 1) v = 1;
        if (s && v > s.amount) v = s.amount;
        return v;
    }

    function setQty(v) {
        var s = st.slots[st.sel];
        var max = s ? s.amount : 1;
        v = Math.max(1, Math.min(max, v | 0));
        $('#qty').value = v;
    }

    function useLabel(slot) {
        var s = st.slots[slot];
        if (!s) return 'USAR';
        if (def(s.item).equip) return slot >= BAG ? 'QUITAR' : 'EQUIPAR';
        return 'USAR';
    }

    function renderDetail() {
        var s = st.slots[st.sel];
        var empty = $('#detailEmpty');
        var body = $('#detailBody');

        if (!s) { empty.hidden = false; body.hidden = true; return; }

        var d = def(s.item);
        empty.hidden = true;
        body.hidden = false;
        body.className = 'detail-body ' + rarityClass(s.item);

        fillIcon($('#dIcon'), d.icon);
        $('#dName').textContent = d.name;
        $('#dRarity').textContent = RARITY[d.rarity] || d.rarity;
        $('#dCat').textContent = d.cat;
        $('#dDesc').textContent = d.desc;
        $('#dUnit').textContent = fmtKg(d.weight);
        $('#dAmount').textContent = String(s.amount);
        $('#dTotal').textContent = fmtKg(d.weight * s.amount);

        $('#qtyBox').style.display = s.amount > 1 ? '' : 'none';
        setQty(getQty());

        $('#btnUse').textContent = useLabel(st.sel);
    }

    function select(i) {
        var old = st.sel;
        st.sel = i;
        if (old >= 0) renderSlot(old);
        if (i >= 0) renderSlot(i);
        $('#qty').value = 1;
        renderDetail();
    }

    /* ---------- acciones ---------- */

    function firstFreeBagSlot() {
        for (var i = 0; i < BAG; i++) if (!st.slots[i]) return i;
        return -1;
    }

    function equipSlotFor(itemId) {
        var t = def(itemId).equip;
        for (var i = 0; i < EQUIP.length; i++) if (EQUIP[i].type === t) return EQUIP[i].slot;
        return -1;
    }

    function shake(i) {
        $$('.slot[data-slot="' + i + '"]').forEach(function (el) {
            el.classList.remove('shake');
            void el.offsetWidth;
            el.classList.add('shake');
        });
    }

    function doMove(from, to, amount) {
        if (from === to) return;
        var before = st.sel;
        if (!moveLogic(from, to, amount)) {
            shake(to);
            toast('No puedes mover eso ahi', 2);
            return;
        }
        renderSlot(from);
        renderSlot(to);
        if (before === from && !st.slots[from]) st.sel = to;
        else if (before === from && st.slots[from]) st.sel = from;
        renderSlot(st.sel);
        renderWeight();
        renderDetail();
        emit('inv:move', from | 0, to | 0, amount | 0);
    }

    function actUse(slot) {
        var s = st.slots[slot];
        if (!s) return;
        var d = def(s.item);

        if (d.equip) {
            if (slot >= BAG) {
                var free = firstFreeBagSlot();
                if (free < 0) { toast('Mochila llena', 2); return; }
                doMove(slot, free, 1);
            } else {
                doMove(slot, equipSlotFor(s.item), 1);
            }
            return;
        }
        emit('inv:use', slot | 0);
    }

    function actDrop(slot, amount) {
        var s = st.slots[slot];
        if (!s) return;
        amount = Math.max(1, Math.min(s.amount, amount | 0));
        emit('inv:drop', slot | 0, amount);
    }

    function actGive(slot, amount) {
        var s = st.slots[slot];
        if (!s) return;
        amount = Math.max(1, Math.min(s.amount, amount | 0));
        emit('inv:give', slot | 0, amount);
    }

    /* ---------- tooltip ---------- */

    var tip = null;

    function showTip(slot, x, y) {
        var s = st.slots[slot];
        if (!s || drag && drag.active) { hideTip(); return; }

        var d = def(s.item);
        tip.className = 'tooltip show ' + rarityClass(s.item);
        tip.innerHTML = '';

        var name = document.createElement('div'); name.className = 't-name'; name.textContent = d.name;
        var sub = document.createElement('div'); sub.className = 't-sub';
        sub.textContent = (RARITY[d.rarity] || d.rarity) + '  ·  ' + d.cat.toUpperCase();
        var desc = document.createElement('div'); desc.className = 't-desc'; desc.textContent = d.desc;
        var meta = document.createElement('div'); meta.className = 't-meta';
        meta.innerHTML = '<span></span><span></span>';
        meta.children[0].textContent = 'Peso: ' + fmtKg(d.weight * s.amount);
        meta.children[1].textContent = s.amount > 1 ? 'Cantidad: ' + s.amount : '';

        tip.appendChild(name); tip.appendChild(sub); tip.appendChild(desc); tip.appendChild(meta);
        moveTip(x, y);
    }

    function moveTip(x, y) {
        var pad = 18;
        var w = tip.offsetWidth, h = tip.offsetHeight;
        var left = x + pad, top = y + pad;
        if (left + w > window.innerWidth - 8) left = x - w - pad;
        if (top + h > window.innerHeight - 8) top = y - h - pad;
        tip.style.left = Math.max(8, left) + 'px';
        tip.style.top = Math.max(8, top) + 'px';
    }

    function hideTip() { if (tip) tip.className = 'tooltip'; }

    /* ---------- menu contextual ---------- */

    var ctx = null;

    function openCtx(slot, x, y) {
        var s = st.slots[slot];
        if (!s) return;
        select(slot);
        hideTip();

        ctx.innerHTML = '';
        function add(label, fn, cls) {
            var b = document.createElement('button');
            b.type = 'button';
            b.textContent = label;
            if (cls) b.className = cls;
            b.addEventListener('click', function () { closeCtx(); fn(); });
            ctx.appendChild(b);
        }

        var d = def(s.item);
        add(d.equip ? useLabel(slot).charAt(0) + useLabel(slot).slice(1).toLowerCase() : 'Usar', function () { actUse(slot); });
        add('Dar al jugador mas cercano', function () { actGive(slot, getQty()); });
        ctx.appendChild(document.createElement('hr'));
        add('Tirar' + (s.amount > 1 ? ' (' + getQty() + ')' : ''), function () { actDrop(slot, getQty()); }, 'dng');
        if (s.amount > 1) add('Tirar todo', function () { actDrop(slot, s.amount); }, 'dng');

        ctx.classList.add('show');
        var w = ctx.offsetWidth, h = ctx.offsetHeight;
        ctx.style.left = Math.min(x, window.innerWidth - w - 8) + 'px';
        ctx.style.top = Math.min(y, window.innerHeight - h - 8) + 'px';
    }

    function closeCtx() { ctx.classList.remove('show'); }

    /* ---------- toasts ---------- */

    function toast(text, type) {
        var box = $('#toasts');
        var t = document.createElement('div');
        t.className = 'toast' + (type === 1 ? ' ok' : type === 2 ? ' err' : '');
        t.textContent = text;
        box.appendChild(t);
        while (box.children.length > 4) box.removeChild(box.firstChild);
        setTimeout(function () { t.classList.add('out'); }, 2600);
        setTimeout(function () { if (t.parentNode) t.parentNode.removeChild(t); }, 2900);
    }

    /* ---------- arrastrar y soltar (con el mouse, no HTML5 DnD) ----------
       El drag nativo de HTML5 no es fiable con CEF off-screen, por eso
       se implementa a mano con mousedown / mousemove / mouseup.            */

    var drag = null;
    var ghost = null;

    function startDrag(e) {
        var s = st.slots[drag.from];
        if (!s) { drag = null; return; }
        drag.active = true;
        hideTip();
        closeCtx();

        ghost.className = 'ghost show';
        ghost.innerHTML = '';
        var ico = document.createElement('span');
        fillIcon(ico, def(s.item).icon);
        ghost.appendChild(ico);
        if (s.amount > 1) {
            var q = document.createElement('span');
            q.className = 'qty';
            q.textContent = 'x' + s.amount;
            ghost.appendChild(q);
        }
        $$('.slot[data-slot="' + drag.from + '"]').forEach(function (el) { el.classList.add('dragging'); });
        select(drag.from);
    }

    function clearDropMarks() {
        $$('.drop-ok, .drop-bad').forEach(function (el) { el.classList.remove('drop-ok', 'drop-bad'); });
    }

    function onMouseDown(e) {
        if (e.button !== 0) return;
        closeCtx();
        var el = e.target.closest ? e.target.closest('.slot') : null;
        if (!el) return;
        var i = parseInt(el.getAttribute('data-slot'), 10);
        drag = { from: i, sx: e.clientX, sy: e.clientY, active: false };
    }

    function onMouseMove(e) {
        if (tip && tip.classList.contains('show')) moveTip(e.clientX, e.clientY);

        if (drag) {
            if (!drag.active && Math.abs(e.clientX - drag.sx) + Math.abs(e.clientY - drag.sy) > 8 && st.slots[drag.from]) {
                startDrag(e);
            }
            if (drag && drag.active) {
                ghost.style.left = e.clientX + 'px';
                ghost.style.top = e.clientY + 'px';

                clearDropMarks();
                var over = document.elementFromPoint(e.clientX, e.clientY);
                var target = over && over.closest ? over.closest('.slot') : null;
                if (target) {
                    var to = parseInt(target.getAttribute('data-slot'), 10);
                    var src = st.slots[drag.from];
                    if (to !== drag.from && src) {
                        $$('.slot[data-slot="' + to + '"]').forEach(function (n) {
                            n.classList.add(canPlace(to, src.item) ? 'drop-ok' : 'drop-bad');
                        });
                    }
                }
                return;
            }
        }

        // tooltip al pasar por un slot
        var hov = e.target.closest ? e.target.closest('.slot') : null;
        if (hov) {
            var hi = parseInt(hov.getAttribute('data-slot'), 10);
            if (st.slots[hi]) showTip(hi, e.clientX, e.clientY); else hideTip();
        } else {
            hideTip();
        }
    }

    function onMouseUp(e) {
        if (!drag) return;
        var d = drag;
        drag = null;

        if (!d.active) {
            select(d.from);
            return;
        }

        ghost.className = 'ghost';
        clearDropMarks();
        $$('.slot.dragging').forEach(function (el) { el.classList.remove('dragging'); });

        var over = document.elementFromPoint(e.clientX, e.clientY);
        var target = over && over.closest ? over.closest('.slot') : null;
        if (!target) return;

        var to = parseInt(target.getAttribute('data-slot'), 10);
        var amount = 0;
        if (e.shiftKey) {
            var src = st.slots[d.from];
            amount = src ? Math.min(src.amount, getQtyFor(src)) : 0;
        }
        doMove(d.from, to, amount);
    }

    function getQtyFor(src) {
        var v = parseInt($('#qty').value, 10);
        if (isNaN(v) || v < 1) v = 1;
        return Math.min(v, src.amount);
    }

    /* ---------- abrir / cerrar ---------- */

    function show() {
        st.visible = true;
        $('#app').classList.remove('hidden');
    }

    function hide() {
        st.visible = false;
        closeCtx();
        hideTip();
        if (drag && drag.active) {
            ghost.className = 'ghost';
            clearDropMarks();
            $$('.slot.dragging').forEach(function (el) { el.classList.remove('dragging'); });
        }
        drag = null;
        $('#app').classList.add('hidden');
    }

    function requestClose() {
        if (!st.visible) return;
        hide();
        // esperamos a que termine la animacion antes de que Pawn oculte el browser
        setTimeout(function () { emit('inv:close'); }, 210);
    }

    /* ---------- eventos que llegan desde Pawn ---------- */

    function bindServer() {
        onServer('inv:open', function () { show(); renderAll(); });
        onServer('inv:close', function () { hide(); });

        onServer('inv:clear', function () {
            for (var i = 0; i < TOTAL; i++) st.slots[i] = null;
            renderAll();
        });

        onServer('inv:slot', function (slot, item, amount) {
            slot = slot | 0; item = item | 0; amount = amount | 0;
            if (slot < 0 || slot >= TOTAL) return;
            st.slots[slot] = (item > 0 && amount > 0) ? { item: item, amount: amount } : null;
            renderSlot(slot);
            renderWeight();
            if (st.sel === slot) renderDetail();
        });

        onServer('inv:info', function (maxWeight, money, name) {
            st.maxWeight = +maxWeight || 0;
            st.money = +money || 0;
            if (name) $('#ownerName').textContent = String(name).replace(/_/g, ' ');
            renderWeight();
            renderMoney();
        });

        onServer('inv:notify', function (text, type) { toast(String(text), type | 0); });
    }

    /* ---------- servidor simulado (solo para probar en un navegador) ---------- */

    function mockServer(name, a) {
        if (name === 'inv:use') {
            var s = st.slots[a[0]];
            if (!s) return;
            toast('Usaste ' + def(s.item).name, 1);
            s.amount--;
            if (s.amount <= 0) st.slots[a[0]] = null;
            renderSlot(a[0]); renderWeight(); renderDetail();
        } else if (name === 'inv:drop' || name === 'inv:give') {
            var t = st.slots[a[0]];
            if (!t) return;
            var q = Math.min(a[1], t.amount);
            toast((name === 'inv:drop' ? 'Tiraste ' : 'Diste ') + q + 'x ' + def(t.item).name, 1);
            t.amount -= q;
            if (t.amount <= 0) st.slots[a[0]] = null;
            renderSlot(a[0]); renderWeight(); renderDetail();
        } else if (name === 'inv:close') {
            if (/[?&]demo/.test(location.search) || !hasCef) setTimeout(function () { show(); }, 900);
        }
    }

    function loadDemo() {
        document.body.classList.add('demo');
        st.maxWeight = 30;
        st.money = 125430;
        $('#ownerName').textContent = 'Brian Lopez';
        var seed = [
            [0, 1, 4], [1, 2, 3], [2, 3, 2], [3, 4, 12], [4, 5, 1],
            [5, 8, 1], [6, 9, 90], [7, 6, 1], [8, 7, 1], [9, 15, 1],
            [12, 16, 3], [13, 4, 20], [30, 11, 1], [31, 10, 1], [33, 13, 1]
        ];
        seed.forEach(function (x) { st.slots[x[0]] = { item: x[1], amount: x[2] }; });
        renderAll();
        renderMoney();
        show();
        toast('Modo demo: abierto fuera del juego', 0);
    }

    /* ---------- teclado ---------- */

    function onKeyDown(e) {
        if (!st.visible) return;
        var typing = e.target && e.target.tagName === 'INPUT';

        if (e.key === 'Escape') {
            if (typing && e.target.id === 'search' && e.target.value) { e.target.value = ''; st.search = ''; renderAll(); return; }
            e.preventDefault();
            if (ctx.classList.contains('show')) closeCtx(); else requestClose();
            return;
        }
        if (typing) return;

        if (e.key === 'i' || e.key === 'I') { e.preventDefault(); requestClose(); return; }

        if (e.key >= '1' && e.key <= '5') {
            e.preventDefault();
            var idx = parseInt(e.key, 10) - 1;
            if (st.slots[idx]) actUse(idx);
        }
    }

    /* ---------- init ---------- */

    function init() {
        tip = $('#tooltip');
        ctx = $('#ctx');
        ghost = $('#ghost');

        build();
        bindServer();
        renderAll();
        renderMoney();

        document.addEventListener('mousedown', onMouseDown);
        document.addEventListener('mousemove', onMouseMove);
        document.addEventListener('mouseup', onMouseUp);
        document.addEventListener('keydown', onKeyDown);
        document.addEventListener('contextmenu', function (e) {
            e.preventDefault();
            var el = e.target.closest ? e.target.closest('.slot') : null;
            if (!el) { closeCtx(); return; }
            openCtx(parseInt(el.getAttribute('data-slot'), 10), e.clientX, e.clientY);
        });
        document.addEventListener('dblclick', function (e) {
            var el = e.target.closest ? e.target.closest('.slot') : null;
            if (!el) return;
            actUse(parseInt(el.getAttribute('data-slot'), 10));
        });
        document.addEventListener('mouseleave', hideTip);

        $('#btnClose').addEventListener('click', requestClose);
        $('#btnUse').addEventListener('click', function () { actUse(st.sel); });
        $('#btnGive').addEventListener('click', function () { actGive(st.sel, getQty()); });
        $('#btnDrop').addEventListener('click', function () { actDrop(st.sel, getQty()); });

        $('#qMinus').addEventListener('click', function () { setQty(getQty() - 1); });
        $('#qPlus').addEventListener('click', function () { setQty(getQty() + 1); });
        $('#qMax').addEventListener('click', function () { var s = st.slots[st.sel]; if (s) setQty(s.amount); });
        $('#qty').addEventListener('change', function () { setQty(getQty()); });

        $('#search').addEventListener('input', function (e) {
            st.search = e.target.value.trim().toLowerCase();
            for (var i = 0; i < TOTAL; i++) renderSlot(i);
        });

        // clic fuera de los paneles = cerrar menu contextual
        document.addEventListener('click', function (e) {
            if (!e.target.closest || !e.target.closest('#ctx')) closeCtx();
        });

        if (demo) loadDemo();

        // avisamos a Pawn de que la pagina ya cargo
        if (hasCef) emit('inv:ready');
    }

    if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', init);
    else init();

    // util para depurar desde DevTools (CEF_EnableDevTools)
    window.__inv = { state: st, show: show, hide: hide, toast: toast };
})();
