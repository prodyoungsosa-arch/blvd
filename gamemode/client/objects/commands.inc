//Jugadores
cmd:bar(playerid, params[])
{
 	if (!member_faccion(playerid, 1, 2, 3, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
 	if(IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando en un vehículo.");
 	Dialog_Show(playerid,COPOBJECTS_DIALOG, DIALOG_STYLE_LIST, "Elige una categoría", "Barricadas\nSignos\nLíneas policiales\nPinchos", ">>", "Cancelar");
	return 1;
}
cmd:ebar(playerid, params[])
{
 	if (!member_faccion(playerid, 1, 2, 3, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
 	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tienes que estar en el piso para usar este comando.");
	if(EditingCopObjectID[playerid] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya estás editando un objeto.");
	if(isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Uso: /ebar <Id>");
	new id = strval(params[0]);
	if(!(0 <= id <= MAX_COP_OBJECTS - 1)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id de objeto inválida.");
	if(!CopObjectData[id][ObjCreated]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese objeto no existe.");
	if(!IsPlayerInRangeOfPoint(playerid, 16.0, CopObjectData[id][ObjXb], CopObjectData[id][ObjYb], CopObjectData[id][ObjZb])) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca del objeto que quieres editar.");
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
	if(!IsPlayerAdmin(playerid) && strcmp(CopObjectData[id][Owner], name)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto no es tuyo, no puedes editarlo.");
    EditingCopObjectID[playerid] = id;
	EditDynamicObject(playerid, CopObjectData[id][ObjID]);
	return 1;
}

cmd:qbar(playerid, params[])
{
  	if (!member_faccion(playerid, 1, 2, 3, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
  	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tienes que estar en el piso para usar este comando.");
	if(isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Uso: /qbar [Id]");
	new id = strval(params[0]);
	if(!(0 <= id <= MAX_COP_OBJECTS - 1)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id de objeto inválida.");
	if(!CopObjectData[id][ObjCreated]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese objeto no existe.");
	if(EditingCopObjectID[playerid] == id) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes quitar un objeto que estás editando.");
	new name[MAX_PLAYER_NAME];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
	if(CheckAdminDuty(playerid) && strcmp(CopObjectData[id][Owner], name)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto no es tuyo, no puedes quitarlo.");
	CopObjectData[id][ObjCreated] = false;
	DestroyDynamicObject(CopObjectData[id][ObjID]);
	DestroyDynamic3DTextLabel(CopObjectData[id][ObjLabel]);
	if(IsValidDynamicArea(CopObjectData[id][ObjArea])) DestroyDynamicArea(CopObjectData[id][ObjArea]);
	CopObjectData[id][ObjID] = -1;
	CopObjectData[id][ObjLabel] = Text3D: -1;
	CopObjectData[id][ObjArea] = -1;
	ShowInfoForPlayer(playerid, "El objeto fue removido correctamente.", 5000);
	return 1;
}

//Administrativos
cmd:irbar(playerid, params[])
{
 	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if(isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Uso: /irbar <Id>");
	new id = strval(params[0]);
	if(!(0 <= id <= MAX_COP_OBJECTS - 1)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id de objeto inválida.");
	if(!CopObjectData[id][ObjCreated]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese objeto no existe.");
	SetPlayerPos(playerid, CopObjectData[id][ObjXb], CopObjectData[id][ObjYb], CopObjectData[id][ObjZb] + 1.75);
	SetPlayerInterior(playerid, CopObjectData[id][ObjInterior]);
	SetPlayerVirtualWorld(playerid, CopObjectData[id][ObjVirtualWorld]);
	ShowInfoForPlayer(playerid, "Teleportado.", 5000);
	return 1;
}