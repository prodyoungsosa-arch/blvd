//Sistema de Log
#define MAX_CHAT_LINES 100
#define MAX_CHAT_LENGTH 128

SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
    static args, str[144];

    if ((args = numargs()) == 3)
    {
        SendClientMessage(playerid, color, text);
        SaveChatLine(playerid, text, color);
    }
    else
    {
        while (--args >= 3)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit PUSH.S 8
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4
        SendClientMessage(playerid, color, str);
        SaveChatLine(playerid, str, color);
        #emit RETN
    }
    return 1;
}

new tempChatBuffer[MAX_PLAYERS][MAX_CHAT_LINES][MAX_CHAT_LENGTH];
new tempChatBufferColor[MAX_PLAYERS][MAX_CHAT_LINES];
new tempChatIndex[MAX_PLAYERS];

stock SaveChatLine(playerid, const line[], color) //guarda el mensaje en el log
{
    format(tempChatBuffer[playerid][tempChatIndex[playerid]], MAX_CHAT_LENGTH, "%s", line);
    tempChatBufferColor[playerid][tempChatIndex[playerid]] = color;
    tempChatIndex[playerid] = (tempChatIndex[playerid] + 1) % MAX_CHAT_LINES;
}

stock SendPlayerChatMessage(playerid, color, const message[]) //Guarda el mensaje en el log y lo muestra
{
    SaveChatLine(playerid, message, color);
    SendClientMessage(playerid, color, message);
	return 1;
}

stock ClearPlayerChat(playerid) //Oculta el log de chat
{
    for (new i = 0; i < 100; i++) SendClientMessage(playerid, -1, " ");
}

stock ClearChat(playerid, lines = 20)
{
	Loop(x, lines, 0)
		SendPlayerChatMessage(playerid, 0xccccccff, "");
	return 1;
}


stock RestorePlayerChat(playerid) //Muestra el log de chat guardado
{
	ClearPlayerChat(playerid);
    new index = tempChatIndex[playerid];
    for (new i = 0; i < MAX_CHAT_LINES; i++)
    {
        index = (index + 1) % MAX_CHAT_LINES;
        if (strlen(tempChatBuffer[playerid][index]) > 0)
        {
            SendClientMessage(playerid, tempChatBufferColor[playerid][index], tempChatBuffer[playerid][index]);
        }
    }
}

funcion LimpiezaLineas(playerid, lines) {
	if (IsPlayerConnected(playerid)) {
		for(new i=0; i<lines; i++) {
			SendPlayerChatMessage(playerid, COLOR_WHITE, " ");
		}
	}
	return 1;
}

funcion CleanScreen() {
    for(new i=0; i<MAX_PLAYERS; i++) {
        LimpiezaLineas(i, 100);
    }
    return 1;
}


CMD:tetra(playerid, params[])
{
    ClearPlayerChat(playerid);
	Dialog_Show(playerid, PanelVehiculo, DIALOG_STYLE_LIST, " ",
	"1. Cinturon\n\
	2. Luces\n\
	3. Radio\n\
	4. Ventana\n\
	5. Intermitentes\n\
	6. Puertas\n\
	7. Capo\n\
	8. Maletero",
	"Continuar", "Cerrar");
    return 1;
}

CMD:cerrartetra(playerid, params[])
{
    RestorePlayerChat(playerid);
    return 1;
}
