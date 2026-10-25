#if defined _INC_rx_notify
    #endinput
#endif
#define _INC_rx_notify

// RX Notify para SA-MP + PawnCEF.
// Reemplaza sh_notify: saca #include <sh_notify> y deja este.
// Carpeta CEF: rx_notify/index.html  (http://cef/rx_notify/index.html)

#if !defined _INC_cef
    #error "rx_notify: hace #include <cef> antes de #include <rx_notify>"
#endif

#if !defined RXN_RESOURCE
    #define RXN_RESOURCE        "rx_notify"
#endif

#if !defined RXN_URL
    #define RXN_URL             "http://cef/rx_notify/index.html"
#endif

#if !defined RXN_BROWSER_ID
    #define RXN_BROWSER_ID      9200
#endif

#if !defined RXN_LAYER
    #define RXN_LAYER           100
#endif

#if !defined RXN_READY_DELAY
    #define RXN_READY_DELAY     900
#endif

#if !defined RXN_QUEUE_SIZE
    #define RXN_QUEUE_SIZE      4
#endif

#if !defined RXN_POSITION
    #define RXN_POSITION        "lc"
#endif

#define RXN_TITLE_SIZE          48
#define RXN_TEXT_SIZE           128
#define RXN_TYPE_SIZE           16
#define RXN_POS_SIZE            8

static gRXN_State[MAX_PLAYERS];
static gRXN_Count[MAX_PLAYERS];
static gRXN_Length[MAX_PLAYERS][RXN_QUEUE_SIZE];
static gRXN_Confetti[MAX_PLAYERS][RXN_QUEUE_SIZE];
static gRXN_Title[MAX_PLAYERS][RXN_QUEUE_SIZE][RXN_TITLE_SIZE];
static gRXN_Text[MAX_PLAYERS][RXN_QUEUE_SIZE][RXN_TEXT_SIZE];
static gRXN_Type[MAX_PLAYERS][RXN_QUEUE_SIZE][RXN_TYPE_SIZE];
static gRXN_Pos[MAX_PLAYERS][RXN_QUEUE_SIZE][RXN_POS_SIZE];

stock bool:RxNotify_IsReady(playerid)
{
    return (0 <= playerid < MAX_PLAYERS) && IsPlayerConnected(playerid) && gRXN_State[playerid] == 2;
}

static stock RXN_Color(const type[])
{
    if (!strcmp(type, "success") || !strcmp(type, "open")) return 0x10B981FF;
    if (!strcmp(type, "error") || !strcmp(type, "closed") || !strcmp(type, "ambulance")) return 0xEF4444FF;
    if (!strcmp(type, "warn") || !strcmp(type, "warning")) return 0xF59E0BFF;
    return 0x3B82F6FF;
}

static stock RXN_Fallback(playerid, const title[], const text[], const type[])
{
    new color = RXN_Color(type);
    if (title[0]) SendClientMessage(playerid, color, title);
    if (text[0]) SendClientMessage(playerid, color, text);
    if (!title[0] && !text[0]) SendClientMessage(playerid, color, "Notificacion");
}

static stock RXN_Emit(playerid, const title[], const text[], const type[], length, confetti, const position[])
{
    CEF_EmitEvent(playerid, RXN_BROWSER_ID, "rx:notify",
        CEF_STR(title), CEF_STR(text), CEF_STR(type),
        CEF_INT(length), CEF_STR(position), CEF_INT(confetti));
}

static stock RXN_Dispatch(playerid, const title[], const text[], const type[], length, confetti, const position[])
{
    if (playerid < 0 || playerid >= MAX_PLAYERS || !IsPlayerConnected(playerid)) return 0;

    if (!CEF_PlayerHasPlugin(playerid))
    {
        RXN_Fallback(playerid, title, text, type);
        return 0;
    }

    if (gRXN_State[playerid] == 2)
    {
        RXN_Emit(playerid, title, text, type, length, confetti, position);
        return 1;
    }

    new n = gRXN_Count[playerid];
    if (n < RXN_QUEUE_SIZE)
    {
        gRXN_Length[playerid][n] = length;
        gRXN_Confetti[playerid][n] = confetti;
        gRXN_Title[playerid][n][0] = EOS;
        gRXN_Text[playerid][n][0] = EOS;
        gRXN_Type[playerid][n][0] = EOS;
        gRXN_Pos[playerid][n][0] = EOS;
        strcat(gRXN_Title[playerid][n], title, RXN_TITLE_SIZE);
        strcat(gRXN_Text[playerid][n], text, RXN_TEXT_SIZE);
        strcat(gRXN_Type[playerid][n], type, RXN_TYPE_SIZE);
        strcat(gRXN_Pos[playerid][n], position, RXN_POS_SIZE);
        gRXN_Count[playerid] = n + 1;
    }

    if (gRXN_State[playerid] == 0)
    {
        gRXN_State[playerid] = 1;
        CEF_CreateBrowser(playerid, RXN_BROWSER_ID, RXN_URL, false, false);
        CEF_SetBrowserLayer(playerid, RXN_BROWSER_ID, RXN_LAYER);
        SetTimerEx("RXN_Ready", RXN_READY_DELAY, false, "i", playerid);
        #if defined RXN_DEBUG
            printf("[rx_notify] browser creado para %d -> %s", playerid, RXN_URL);
        #endif
    }
    return 1;
}

forward RXN_Ready(playerid);
public RXN_Ready(playerid)
{
    if (!IsPlayerConnected(playerid)) return 1;

    gRXN_State[playerid] = 2;
    new total = gRXN_Count[playerid];
    gRXN_Count[playerid] = 0;

    for (new i = 0; i < total; i++)
    {
        RXN_Emit(playerid,
            gRXN_Title[playerid][i],
            gRXN_Text[playerid][i],
            gRXN_Type[playerid][i],
            gRXN_Length[playerid][i],
            gRXN_Confetti[playerid][i],
            gRXN_Pos[playerid][i]);
    }

    #if defined RXN_DEBUG
        printf("[rx_notify] listo para %d, enviadas %d en cola", playerid, total);
    #endif
    return 1;
}

// RxNotify(playerid, titulo, texto, tipo, ms, confetti, posicion)
// tipo: "success" | "error" | "warn" | "info"
//       (tambien acepta success/error/warning/primary/open/closed/police/ambulance)
// posicion: "tl" "tc" "tr" "lc" "rc" "bl" "bc" "br"  (vacio = RXN_POSITION)
// confetti: 1 prende el confetti
stock RxNotify(playerid, const title[], const text[], const type[] = "info", length = 3000, confetti = 0, const position[] = "")
{
    new pos[RXN_POS_SIZE];
    pos[0] = EOS;
    if (position[0]) strcat(pos, position, sizeof pos);
    else strcat(pos, RXN_POSITION, sizeof pos);
    return RXN_Dispatch(playerid, title, text, type, length, confetti, pos);
}

stock RxNotifyAll(const title[], const text[], const type[] = "info", length = 3000, confetti = 0, const position[] = "")
{
    for (new i = 0; i < MAX_PLAYERS; i++)
        if (IsPlayerConnected(i)) RxNotify(i, title, text, type, length, confetti, position);
    return 1;
}

// Compatibilidad con sh_notify.
// Notify: el texto grande queda como titulo si hay caption; si no, el CEF pone el titulo por tipo.
// LocalNotify: tarjeta arriba al centro (ya no es el cartel gigante).
stock Notify(playerid, const text[], const type[] = "info", length = 5000, const caption[] = "")
{
    if (caption[0]) return RxNotify(playerid, text, caption, type, length, 0, "");
    return RxNotify(playerid, "", text, type, length, 0, "");
}

stock LocalNotify(playerid, const text[], const type[] = "open", length = 6000)
{
    return RxNotify(playerid, text, "", type, length, 0, "tc");
}

stock NotifyAll(const text[], const type[] = "info", length = 5000, const caption[] = "")
{
    for (new i = 0; i < MAX_PLAYERS; i++)
        if (IsPlayerConnected(i)) Notify(i, text, type, length, caption);
    return 1;
}

stock LocalNotifyAll(const text[], const type[] = "open", length = 6000)
{
    for (new i = 0; i < MAX_PLAYERS; i++)
        if (IsPlayerConnected(i)) LocalNotify(i, text, type, length);
    return 1;
}

static stock RXN_ResetPlayer(playerid)
{
    gRXN_State[playerid] = 0;
    gRXN_Count[playerid] = 0;
}

public OnGameModeInit()
{
    #if !defined RXN_NO_AUTO_RESOURCE
        CEF_AddResource(RXN_RESOURCE);
    #endif
    #if defined RXN_DEBUG
        printf("[rx_notify] recurso registrado: %s", RXN_RESOURCE);
    #endif
    #if defined RXN_OnGameModeInit
        return RXN_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit RXN_OnGameModeInit
#if defined RXN_OnGameModeInit
    forward RXN_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
    RXN_ResetPlayer(playerid);
    #if defined RXN_OnPlayerConnect
        return RXN_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect RXN_OnPlayerConnect
#if defined RXN_OnPlayerConnect
    forward RXN_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    RXN_ResetPlayer(playerid);
    #if defined RXN_OnPlayerDisconnect
        return RXN_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect RXN_OnPlayerDisconnect
#if defined RXN_OnPlayerDisconnect
    forward RXN_OnPlayerDisconnect(playerid, reason);
#endif
