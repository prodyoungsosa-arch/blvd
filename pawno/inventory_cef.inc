/* ============================================================================
    inventory_cef.inc
    Inventario para open.mp / SA-MP usando el plugin omp-cef (Aurora CEF).

    Natives usados (todos de cef.inc):
        CEF_AddResource, CEF_RegisterEvent, CEF_EmitEvent, CEF_CreateBrowser,
        CEF_SetBrowserVisible, CEF_FocusBrowser, CEF_ToggleChatInput,
        CEF_IsChatInputOpen, CEF_SetKeyCapture, CEF_EnableKey

    Que tenes que llamar desde tu gamemode (ver gamemodes/inventory_demo.pwn):
        OnGameModeInit      -> Inventory_Init();
        OnPlayerConnect     -> Inventory_ResetPlayer(playerid);
        OnPlayerDisconnect  -> Inventory_ResetPlayer(playerid);
        OnCefInitialize     -> Inventory_OnCefInitialize(playerid, success);
        OnCefBrowserCreated -> Inventory_OnBrowserCreated(playerid, browserid, success);
        OnCefPressKey       -> Inventory_OnPressKey(playerid, key, down, repeat);

    Hooks opcionales que podes definir en tu gamemode (publics):
        OnInventoryItemUse(playerid, itemid, slot)           return 1 = lo manejaste vos
        OnInventoryEquipChange(playerid, itemid, slot, equipped)
        OnInventoryItemDropped(playerid, itemid, amount)     para crear el objeto en el mundo

    NOTA: usa texto SIN tildes en los strings de Pawn (SA-MP trabaja en
    Windows-1252 y el navegador espera UTF-8). Los textos con tildes van en
    scriptfiles/cef/inventory/js/items.js.
============================================================================ */

#if defined _inventory_cef_included
    #endinput
#endif
#define _inventory_cef_included

#include <a_samp>
#include <cef>


#define INV_BAG_SLOTS        30      // slots de la mochila (0-29). Los 0-4 son la barra rapida.
#define INV_EQUIP_SLOTS      6       // slots de equipamiento (30-35)
#define INV_TOTAL_SLOTS      36      // BAG + EQUIP  (tiene que coincidir con el JS)

#define INV_BROWSER_ID       2000    // id del browser del inventario (unico por jugador)
#define INV_RESOURCE         "inventory"
#define INV_URL              "http://cef/inventory/index.html"

#define INV_OPEN_KEY         0x49    // tecla 'I'  (VK_I)
#define INV_HOTBAR_KEY_1     0x31    // tecla '1'  (VK_1)  ... hasta '5'
#define INV_HOTBAR_SIZE      5

#define INV_DEFAULT_MAX_KG   30.0
#define INV_GIVE_RANGE       3.0     // distancia maxima para dar un objeto
#define INV_COOLDOWN_MS      250     // antirrebote de acciones (usar / tirar / dar)

/* Si en tu build de omp-cef los callbacks de eventos JS NO reciben `browserid`
   (es decir, son (playerid, ...) y no (playerid, browserid, ...)), borra el
   parametro `browserid` de los publics "OnInvJs..." de mas abajo. */

/* ----------------------------------------------------------------------------
    CATALOGO DE OBJETOS  (tiene que coincidir con js/items.js)
---------------------------------------------------------------------------- */

enum
{
    ITEM_NONE = 0,
    ITEM_WATER,        // 1
    ITEM_BREAD,        // 2
    ITEM_MEDKIT,       // 3
    ITEM_BANDAGE,      // 4
    ITEM_PHONE,        // 5
    ITEM_RADIO,        // 6
    ITEM_CARKEY,       // 7
    ITEM_PISTOL,       // 8
    ITEM_AMMO9,        // 9
    ITEM_VEST,         // 10
    ITEM_CAP,          // 11
    ITEM_PANTS,        // 12
    ITEM_SHOES,        // 13
    ITEM_BACKPACK,     // 14
    ITEM_TOOLBOX,      // 15
    ITEM_GOLDBAR,      // 16
    ITEM_COUNT
}

// tipos de slot de equipamiento. El valor - 1 + INV_BAG_SLOTS = slot donde va.
enum
{
    EQ_NONE = 0,
    EQ_HEAD,           // slot 30
    EQ_BODY,           // slot 31
    EQ_LEGS,           // slot 32
    EQ_FEET,           // slot 33
    EQ_WEAPON,         // slot 34
    EQ_ACC             // slot 35
}

new const gItemName[ITEM_COUNT][] =
{
    "", "Botella de agua", "Pan", "Botiquin", "Vendas", "Celular", "Radio", "Llave de auto",
    "Pistola 9mm", "Municion 9mm", "Chaleco antibalas", "Gorra", "Pantalon cargo", "Zapatillas",
    "Mochila tactica", "Caja de herramientas", "Lingote de oro"
};

new const Float:gItemWeight[ITEM_COUNT] =
{
    0.0, 0.5, 0.3, 1.0, 0.1, 0.2, 0.4, 0.05,
    1.5, 0.02, 2.5, 0.2, 0.8, 0.7,
    1.2, 3.0, 1.0
};

new const gItemStack[ITEM_COUNT] =
{
    0, 10, 10, 5, 20, 1, 1, 1,
    1, 200, 1, 1, 1, 1,
    1, 1, 5
};

new const gItemEquip[ITEM_COUNT] =
{
    EQ_NONE, EQ_NONE, EQ_NONE, EQ_NONE, EQ_NONE, EQ_NONE, EQ_NONE, EQ_NONE,
    EQ_WEAPON, EQ_NONE, EQ_BODY, EQ_HEAD, EQ_LEGS, EQ_FEET,
    EQ_ACC, EQ_NONE, EQ_NONE
};

/* ----------------------------------------------------------------------------
    DATOS POR JUGADOR
---------------------------------------------------------------------------- */

enum E_INV_SLOT
{
    invItem,
    invAmount
}

new gInv[MAX_PLAYERS][INV_TOTAL_SLOTS][E_INV_SLOT];
new Float:gInvMaxWeight[MAX_PLAYERS];

new bool:gInvCefReady[MAX_PLAYERS];     // el cliente completo el handshake de CEF
new bool:gInvBrowserMade[MAX_PLAYERS];  // ya pedimos crear el browser
new bool:gInvPageReady[MAX_PLAYERS];    // la pagina cargo y emitio inv:ready
new bool:gInvOpen[MAX_PLAYERS];         // el inventario esta abierto
new gInvLastAction[MAX_PLAYERS];

forward OnInvJsReady(playerid, browserid);
forward OnInvJsClose(playerid, browserid);
forward OnInvJsUse(playerid, browserid, slot);
forward OnInvJsMove(playerid, browserid, from, to, amount);
forward OnInvJsDrop(playerid, browserid, slot, amount);
forward OnInvJsGive(playerid, browserid, slot, amount);

stock Inv_Min(a, b) return (a < b) ? a : b;

stock Inv_ValidSlot(slot) return (slot >= 0 && slot < INV_TOTAL_SLOTS);

stock Inv_Cooldown(playerid)
{
    new now = GetTickCount();
    if (now - gInvLastAction[playerid] < INV_COOLDOWN_MS) return 1;
    gInvLastAction[playerid] = now;
    return 0;
}

stock Inv_Heal(playerid, Float:amount)
{
    new Float:hp;
    GetPlayerHealth(playerid, hp);
    hp += amount;
    if (hp > 100.0) hp = 100.0;
    SetPlayerHealth(playerid, hp);
}

stock Inventory_CanPlace(slot, itemid)
{
    if (slot < INV_BAG_SLOTS) return 1;
    return (gItemEquip[itemid] == (slot - INV_BAG_SLOTS + 1));
}

stock Float:Inventory_GetWeight(playerid)
{
    new Float:total = 0.0;
    for (new s = 0; s < INV_TOTAL_SLOTS; s++)
    {
        new item = gInv[playerid][s][invItem];
        if (item) total += gItemWeight[item] * float(gInv[playerid][s][invAmount]);
    }
    return total;
}

stock Inventory_GetAmount(playerid, itemid)
{
    new total = 0;
    for (new s = 0; s < INV_TOTAL_SLOTS; s++)
        if (gInv[playerid][s][invItem] == itemid) total += gInv[playerid][s][invAmount];
    return total;
}

stock Inventory_HasItem(playerid, itemid, amount = 1)
{
    return (Inventory_GetAmount(playerid, itemid) >= amount);
}

stock Inventory_FindFreeBagSlot(playerid)
{
    for (new s = 0; s < INV_BAG_SLOTS; s++)
        if (!gInv[playerid][s][invItem]) return s;
    return -1;
}

stock Inventory_SetMaxWeight(playerid, Float:kg)
{
    gInvMaxWeight[playerid] = kg;
    if (gInvOpen[playerid] && gInvPageReady[playerid])
        CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:info", CEF_FLOAT(kg), CEF_INT(GetPlayerMoney(playerid)), CEF_STR(""));
    return 1;
}


stock Inventory_SyncSlot(playerid, slot)
{
    if (!gInvOpen[playerid] || !gInvPageReady[playerid] || !Inv_ValidSlot(slot)) return 0;
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:slot",
        CEF_INT(slot), CEF_INT(gInv[playerid][slot][invItem]), CEF_INT(gInv[playerid][slot][invAmount]));
    return 1;
}

stock Inventory_SyncAll(playerid)
{
    if (!gInvPageReady[playerid]) return 0;

    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof name);

    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:clear");
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:info",
        CEF_FLOAT(gInvMaxWeight[playerid]), CEF_INT(GetPlayerMoney(playerid)), CEF_STR(name));

    for (new s = 0; s < INV_TOTAL_SLOTS; s++)
    {
        if (!gInv[playerid][s][invItem]) continue;
        CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:slot",
            CEF_INT(s), CEF_INT(gInv[playerid][s][invItem]), CEF_INT(gInv[playerid][s][invAmount]));
    }
    return 1;
}

// aviso: dentro de la UI como toast (type 0 info, 1 ok, 2 error). Si esta cerrada, va por chat.
stock Inventory_Notify(playerid, const text[], type = 0)
{
    if (gInvOpen[playerid] && gInvPageReady[playerid])
        CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:notify", CEF_STR(text), CEF_INT(type));
    else
        SendClientMessage(playerid, (type == 2) ? 0xFF4D5EFF : 0xFFB020FF, text);
    return 1;
}

stock Inv_FireEquip(playerid, slot, oldItem, newItem)
{
    if (slot < INV_BAG_SLOTS || oldItem == newItem) return;
    if (oldItem) CallLocalFunction("OnInventoryEquipChange", "dddd", playerid, oldItem, slot, 0);
    if (newItem) CallLocalFunction("OnInventoryEquipChange", "dddd", playerid, newItem, slot, 1);
}

stock Inventory_SetSlot(playerid, slot, itemid, amount)
{
    if (!Inv_ValidSlot(slot)) return 0;

    new old = gInv[playerid][slot][invItem];

    if (itemid <= 0 || itemid >= ITEM_COUNT || amount <= 0)
    {
        itemid = 0;
        amount = 0;
    }

    InfoPersonaje[playerid][pBolsillo][slot] = itemid;
    InfoPersonaje[playerid][pBolsilloCant][slot] = amount;

    Inventory_SyncSlot(playerid, slot);
    Inv_FireEquip(playerid, slot, old, itemid);
    return 1;
}

stock Inventory_RemoveFromSlot(playerid, slot, amount)
{
    if (!Inv_ValidSlot(slot) || amount <= 0) return 0;

    new item = InfoPersonaje[playerid][pBolsillo][slot];
    new have = InfoPersonaje[playerid][pBolsilloCant][slot];
    if (!item || have < amount) return 0;

    Inventory_SetSlot(playerid, slot, item, have - amount);
    return 1;
}

stock Inventory_AddItem(playerid, itemid, amount = 1)
{
    if (itemid <= 0 || itemid >= ITEM_COUNT || amount <= 0) return 0;

    new Float:w = gItemWeight[itemid];
    if (w > 0.0)
    {
        new Float:freeKg = gInvMaxWeight[playerid] - Inventory_GetWeight(playerid);
        if (freeKg <= 0.0) return 0;
        new canTake = floatround((freeKg + 0.0001) / w, floatround_floor);
        amount = Inv_Min(amount, canTake);
        if (amount <= 0) return 0;
    }

    new stack = gItemStack[itemid];
    new remaining = amount;

    // 1) completar stacks existentes
    if (stack > 1)
    {
        for (new s = 0; s < INV_BAG_SLOTS && remaining > 0; s++)
        {
            if (InfoPersonaje[playerid][pBolsillo][s] != itemid) continue;
            new space = stack - InfoPersonaje[playerid][pBolsilloCant][s];
            if (space <= 0) continue;

            new add = Inv_Min(space, remaining);
            Inventory_SetSlot(playerid, s, itemid, InfoPersonaje[playerid][pBolsilloCant][s] + add);
            remaining -= add;
        }
    }

    // 2) usar slots vacios
    for (new s = 0; s < INV_BAG_SLOTS && remaining > 0; s++)
    {
        if (InfoPersonaje[playerid][pBolsillo][s]) continue;

        new add = Inv_Min(stack, remaining);
        Inventory_SetSlot(playerid, s, itemid, add);
        remaining -= add;
    }

    return amount - remaining;
}

stock Inventory_RemoveItem(playerid, itemid, amount = 1)
{
    if (amount <= 0 || Inventory_GetAmount(playerid, itemid) < amount) return 0;

    new remaining = amount;
    for (new s = 0; s < INV_TOTAL_SLOTS && remaining > 0; s++)
    {
        if (InfoPersonaje[playerid][pBolsillo][s] != itemid) continue;

        new take = Inv_Min(InfoPersonaje[playerid][pBolsilloCant][s], remaining);
        Inventory_RemoveFromSlot(playerid, s, take);
        remaining -= take;
    }
    return 1;
}

stock Inventory_Clear(playerid)
{
    for (new s = 0; s < INV_TOTAL_SLOTS; s++) Inventory_SetSlot(playerid, s, 0, 0);
    return 1;
}

stock Inventory_Move(playerid, from, to, amount = 0)
{
    if (!Inv_ValidSlot(from) || !Inv_ValidSlot(to) || from == to) return 0;

    new src = InfoPersonaje[playerid][pBolsillo][from];
    new srcAmt = InfoPersonaje[playerid][pBolsilloCant][from];
    if (!src) return 0;

    if (amount <= 0 || amount > srcAmt) amount = srcAmt;
    if (!Inventory_CanPlace(to, src)) return 0;

    new dst = InfoPersonaje[playerid][pBolsillo][to];
    new dstAmt = InfoPersonaje[playerid][pBolsilloCant][to];
    new stack = gItemStack[src];

    if (!dst)
    {
        // destino vacio
        amount = Inv_Min(amount, stack);
        Inventory_SetSlot(playerid, from, src, srcAmt - amount);
        Inventory_SetSlot(playerid, to, src, amount);
        return 1;
    }

    if (dst == src && stack > 1)
    {
        // apilar
        new space = stack - dstAmt;
        if (space <= 0) return 0;

        amount = Inv_Min(amount, space);
        Inventory_SetSlot(playerid, from, src, srcAmt - amount);
        Inventory_SetSlot(playerid, to, src, dstAmt + amount);
        return 1;
    }

    // intercambio: solo con el stack completo y si ambos objetos caben en el slot opuesto
    if (amount != srcAmt) return 0;
    if (!Inventory_CanPlace(from, dst)) return 0;

    Inventory_SetSlot(playerid, from, dst, dstAmt);
    Inventory_SetSlot(playerid, to, src, srcAmt);
    return 1;
}

stock Inventory_UseSlot(playerid, slot)
{
    if (!Inv_ValidSlot(slot)) return 0;

    new item = InfoPersonaje[playerid][pBolsillo][slot];
    if (!item) return 0;

    if (gItemEquip[item])
    {
        if (slot >= INV_BAG_SLOTS)
        {
            new free = Inventory_FindFreeBagSlot(playerid);
            if (free == -1)
            {
                ShowNotificacion(playerid, "Error", "Tu mochila esta llena.", "error");
                return 0;
            }
            return Inventory_Move(playerid, slot, free, 1);
        }
        return Inventory_Move(playerid, slot, INV_BAG_SLOTS + gItemEquip[item] - 1, 1);
    }

    // el gamemode puede manejarlo primero
    if (CallLocalFunction("OnInventoryItemUse", "ddd", playerid, item, slot)) return 1;

    switch (item)
    {
        case ITEM_WATER:
        {
            Inventory_RemoveFromSlot(playerid, slot, 1);
            Inventory_Notify(playerid, "Tomaste una botella de agua.", 1);
        }
        case ITEM_BREAD:
        {
            Inventory_RemoveFromSlot(playerid, slot, 1);
            Inv_Heal(playerid, 15.0);
            ShowNotificacion(playerid, "Información", "Comiste pan. +15 de salud.", "success");
        }
        case ITEM_BANDAGE:
        {
            Inventory_RemoveFromSlot(playerid, slot, 1);
            Inv_Heal(playerid, 25.0);
            ShowNotificacion(playerid, "Información", "Te pusiste una venda. +25 de salud.", "success");
        }
        case ITEM_MEDKIT:
        {
            Inventory_RemoveFromSlot(playerid, slot, 1);
            Inv_Heal(playerid, 60.0);
            ShowNotificacion(playerid, "Información", "Usaste un botiquin. +60 de salud.", "success");
        }
        default:
        {
            ShowNotificacion(playerid, "Error", "Este objeto no se puede usar asi.", "error");
            return 0;
        }
    }
    return 1;
}

stock Inventory_DropFromSlot(playerid, slot, amount)
{
    if (!Inv_ValidSlot(slot)) return 0;

    new item = InfoPersonaje[playerid][pBolsillo][slot];
    new have = InfoPersonaje[playerid][pBolsilloCant][slot];
    if (!item || amount <= 0) return 0;

    amount = Inv_Min(amount, have);
    Inventory_RemoveFromSlot(playerid, slot, amount);

    // aca tu gamemode puede crear el objeto en el suelo (pickup / objeto / DB)
    CallLocalFunction("OnInventoryItemDropped", "ddd", playerid, item, amount);

    new msg[96];
    format(msg, sizeof msg, "Tiraste %dx %s.", amount, gItemName[item]);
    Inventory_Notify(playerid, msg, 1);
    return 1;
}

stock Inventory_GiveToNearest(playerid, slot, amount)
{
    if (!Inv_ValidSlot(slot)) return 0;

    new item = InfoPersonaje[playerid][pBolsillo][slot];
    new have = InfoPersonaje[playerid][pBolsilloCant][slot];
    if (!item || amount <= 0) return 0;
    amount = Inv_Min(amount, have);

    // jugador mas cercano en rango, mismo mundo e interior
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    new target = INVALID_PLAYER_ID;
    new Float:best = INV_GIVE_RANGE;
    new world = GetPlayerVirtualWorld(playerid);
    new interior = GetPlayerInterior(playerid);

    for (new i = 0, m = GetMaxPlayers(); i < m; i++)
    {
        if (i == playerid || !IsPlayerConnected(i)) continue;
        if (GetPlayerVirtualWorld(i) != world || GetPlayerInterior(i) != interior) continue;

        new Float:d = GetPlayerDistanceFromPoint(i, x, y, z);
        if (d <= best)
        {
            best = d;
            target = i;
        }
    }

    if (target == INVALID_PLAYER_ID)
    {
        ShowNotificacion(playerid, "Error", "No hay nadie cerca para darle el objeto.", "error");
        return 0;
    }

    new added = Inventory_AddItem(target, item, amount);
    if (added <= 0)
    {
        ShowNotificacion(playerid, "Error", "Esa persona no tiene espacio o carga suficiente.", "error");
        return 0;
    }

    Inventory_RemoveFromSlot(playerid, slot, added);

    new msg[128], name[MAX_PLAYER_NAME];

    GetPlayerName(target, name, sizeof name);
    format(msg, sizeof msg, "Le diste %dx %s a %s.", added, gItemName[item], name);
    ShowNotificacion(playerid, "Información", msg, "info");

    GetPlayerName(playerid, name, sizeof name);
    format(msg, sizeof msg, "%s te dio %dx %s.", name, added, gItemName[item]);
    ShowNotificacion(target, "Información", msg, "info");
    return 1;
}


stock Inventory_Present(playerid)
{
    if (!gInvPageReady[playerid]) return 0;
    Inventory_SyncAll(playerid);
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:open");
    return 1;
}

stock Inventory_Open(playerid)
{
    if (!IsPlayerConnected(playerid) || gInvOpen[playerid]) return 0;

    if (!gInvCefReady[playerid])
    {
        SendClientMessage(playerid, 0xFF4D5EFF, "CEF todavia no esta listo. Espera unos segundos.");
        return 0;
    }

    gInvOpen[playerid] = true;
    CEF_ToggleChatInput(playerid, false);

    if (!gInvBrowserMade[playerid])
    {
        gInvBrowserMade[playerid] = true;
        gInvPageReady[playerid] = false;
        CEF_CreateBrowser(playerid, INV_BROWSER_ID, INV_URL, true, true);
    }
    else
    {
        CEF_SetBrowserVisible(playerid, INV_BROWSER_ID, true);
        CEF_FocusBrowser(playerid, INV_BROWSER_ID, true);
        Inventory_Present(playerid);
    }
    return 1;
}

stock Inventory_Close(playerid, bool:notifyJs = true)
{
    if (!gInvOpen[playerid]) return 0;

    gInvOpen[playerid] = false;

    if (notifyJs && gInvPageReady[playerid])
        CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:close");

    CEF_FocusBrowser(playerid, INV_BROWSER_ID, false);
    CEF_SetBrowserVisible(playerid, INV_BROWSER_ID, false);
    CEF_ToggleChatInput(playerid, true);
    return 1;
}

stock Inventory_Toggle(playerid)
{
    return gInvOpen[playerid] ? Inventory_Close(playerid) : Inventory_Open(playerid);
}

/* ----------------------------------------------------------------------------
    EVENTOS JS -> PAWN
    Todo lo que llega del navegador es INPUT DEL CLIENTE: se valida siempre.
---------------------------------------------------------------------------- */

public OnInvJsReady(playerid, browserid)
{
    if (browserid != INV_BROWSER_ID) return 1;

    gInvPageReady[playerid] = true;
    if (gInvOpen[playerid]) Inventory_Present(playerid);
    return 1;
}

public OnInvJsClose(playerid, browserid)
{
    Inventory_Close(playerid, false);
    return 1;
}

public OnInvJsUse(playerid, browserid, slot)
{
#if defined INV_DEBUG
    printf("[inv] use  player=%d browser=%d slot=%d", playerid, browserid, slot);
#endif
    if (!gInvOpen[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_UseSlot(playerid, slot);
    return 1;
}

public OnInvJsMove(playerid, browserid, from, to, amount)
{
#if defined INV_DEBUG
    printf("[inv] move player=%d browser=%d %d -> %d (x%d)", playerid, browserid, from, to, amount);
#endif
    if (!gInvOpen[playerid] || !Inv_ValidSlot(from) || !Inv_ValidSlot(to)) return 1;

    if (!Inventory_Move(playerid, from, to, amount))
    {
        // la UI ya movio el objeto de forma optimista: la devolvemos al estado real
        Inventory_SyncSlot(playerid, from);
        Inventory_SyncSlot(playerid, to);
    }
    return 1;
}

public OnInvJsDrop(playerid, browserid, slot, amount)
{
    if (!gInvOpen[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_DropFromSlot(playerid, slot, amount);
    return 1;
}

public OnInvJsGive(playerid, browserid, slot, amount)
{
    if (!gInvOpen[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_GiveToNearest(playerid, slot, amount);
    return 1;
}

/* ----------------------------------------------------------------------------
    INICIALIZACION Y CALLBACKS DE CEF
---------------------------------------------------------------------------- */

stock Inventory_Init()
{
    // scriptfiles/cef/inventory/
    CEF_AddResource(INV_RESOURCE);

    CEF_RegisterEvent("inv:ready", "OnInvJsReady");
    CEF_RegisterEvent("inv:close", "OnInvJsClose");
    CEF_RegisterEvent("inv:use",   "OnInvJsUse",  Argument_Integer);
    CEF_RegisterEvent("inv:move",  "OnInvJsMove", Argument_Integer, Argument_Integer, Argument_Integer);
    CEF_RegisterEvent("inv:drop",  "OnInvJsDrop", Argument_Integer, Argument_Integer);
    CEF_RegisterEvent("inv:give",  "OnInvJsGive", Argument_Integer, Argument_Integer);
    return 1;
}

stock Inventory_ResetPlayer(playerid)
{
    for (new s = 0; s < INV_TOTAL_SLOTS; s++)
    {
        gInv[playerid][s][invItem] = 0;
        gInv[playerid][s][invAmount] = 0;
    }

    gInvMaxWeight[playerid] = INV_DEFAULT_MAX_KG;
    gInvCefReady[playerid] = false;
    gInvBrowserMade[playerid] = false;
    gInvPageReady[playerid] = false;
    gInvOpen[playerid] = false;
    gInvLastAction[playerid] = 0;
    return 1;
}

stock Inventory_OnCefInitialize(playerid, bool:success)
{
    gInvCefReady[playerid] = success;
    if (!success) return 0;

    // captura de teclas para abrir con 'I' y usar la barra rapida con 1-5
    CEF_SetKeyCapture(playerid, true);
    CEF_EnableKey(playerid, INV_OPEN_KEY, true);
    for (new k = 0; k < INV_HOTBAR_SIZE; k++) CEF_EnableKey(playerid, INV_HOTBAR_KEY_1 + k, true);
    return 1;
}

stock Inventory_OnBrowserCreated(playerid, browserid, bool:success)
{
    if (browserid != INV_BROWSER_ID || success) return 1;

    // fallo la creacion: dejamos todo limpio para poder reintentar
    gInvBrowserMade[playerid] = false;
    gInvPageReady[playerid] = false;
    if (gInvOpen[playerid])
    {
        gInvOpen[playerid] = false;
        CEF_ToggleChatInput(playerid, true);
    }
    SendClientMessage(playerid, 0xFF4D5EFF, "No se pudo abrir el inventario (error de CEF).");
    return 1;
}

stock Inventory_OnPressKey(playerid, key, bool:down, bool:repeat)
{
    if (!down || repeat || CEF_IsChatInputOpen(playerid)) return 0;

    // 'I' solo abre; cerrar lo hace la propia UI (ESC / I / boton) cuando tiene el foco
    if (key == INV_OPEN_KEY)
    {
        if (!gInvOpen[playerid]) Inventory_Open(playerid);
        return 1;
    }

    // barra rapida con el inventario cerrado
    if (key >= INV_HOTBAR_KEY_1 && key < INV_HOTBAR_KEY_1 + INV_HOTBAR_SIZE && !gInvOpen[playerid])
    {
        if (!Inv_Cooldown(playerid)) Inventory_UseSlot(playerid, key - INV_HOTBAR_KEY_1);
        return 1;
    }
    return 0;
}

