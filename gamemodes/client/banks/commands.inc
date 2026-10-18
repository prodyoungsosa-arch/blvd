new EnIDatm[MAX_PLAYERS];

//Jugadores
cmd:banco(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 3.0, -983.8863, 1448.5732, 1340.6270)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el Banco Central de Los Santos.");
	Dialog_Show(playerid, ShowBanco, DIALOG_STYLE_LIST, "Banco", "Consultar saldo\nRetirar efectivo\nDepositar efectivo\nTransferir dinero", "Continuar", "Salir");
	return 1;
}

cmd:cajero(playerid)
{
	new id = -1;
	Loop(x, MAX_CAJEROS, 1) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCajero[x][atmPotX], InfoCajero[x][atmPotY], InfoCajero[x][atmPotZ]) && InfoPersonaje[playerid][pInterior] == InfoCajero[x][atmInterior] && InfoPersonaje[playerid][pVirtualWorld] == InfoCajero[x][atmVirtualWorld])
	{
		id = x;
		break;
	}
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca de ningún cajero.");
	Dialog_Show(playerid, ShowCajero, DIALOG_STYLE_LIST, "Cajero", "Consultar saldo\nRetirar efectivo\nDepositar efectivo\nTransferir dinero", "Continuar", "Salir");
	EnIDatm[playerid] = id;
	return 1;
}
alias:cajero("atm");

//Administrativos
cmd:crearcajero(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (InfoPersonaje[playerid][pEditingMode] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás editando un objeto.");
	new query[1028];
	Loop(id, MAX_CAJEROS, 1) if (!InfoCajero[id][atmModelo])
	{
		InfoCajero[id][atmModelo] = 19324;
		InfoCajero[id][atmDinero] = 5000000;
		GetPlayerPos(playerid, InfoCajero[id][atmPotX], InfoCajero[id][atmPotY], InfoCajero[id][atmPotZ]);
		InfoCajero[id][atmInterior] = GetPlayerInterior(playerid);
		InfoCajero[id][atmVirtualWorld] = GetPlayerVirtualWorld(playerid);
		Label_cajero(id, 1);
		SendPlayerChatMessage(playerid, 0x90C3D4FF, "Creaste el cajero indicado, ahora editalo.");
		EditDynamicObject(playerid, InfoCajero[id][atmObject]);
		InfoPersonaje[playerid][pEditingMode] = 74;
		edicion_sql_actual[playerid] = id;
		//opción idsql ya creada.
		if (InfoCajero[id][atmID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE cajeros SET Modelo = '%d', BolosUwU = '%d', PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoCajero[id][atmModelo],
			InfoCajero[id][atmDinero],
			InfoCajero[id][atmPotX],
			InfoCajero[id][atmPotY],
			InfoCajero[id][atmPotZ],
			InfoCajero[id][atmRotX],
			InfoCajero[id][atmRotY],
			InfoCajero[id][atmRotZ],
			InfoCajero[id][atmInterior],
			InfoCajero[id][atmVirtualWorld],
			InfoCajero[id][atmID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_CAJEROS;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO cajeros (Modelo, BolosUwU, PotX, PotY, PotZ, RotX, RotY, RotZ, Interior, VirtualWorld) VALUES ('%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
		InfoCajero[id][atmModelo],
		InfoCajero[id][atmDinero],
		InfoCajero[id][atmPotX],
		InfoCajero[id][atmPotY],
		InfoCajero[id][atmPotZ],
		InfoCajero[id][atmRotX],
		InfoCajero[id][atmRotY],
		InfoCajero[id][atmRotZ],
		InfoCajero[id][atmInterior],
		InfoCajero[id][atmVirtualWorld]);
		mysql_tquery(db_samp, query, "OnCajeroCreate", "i", id);
		id = MAX_CAJEROS;
	}
	return 1;
}
cmd:borrarcajero(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, string[256];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borrarcajero (CajeroID)");
	if (!InfoCajero[id][atmModelo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id cajero invalida.");
	InfoCajero[id][atmModelo] = 0;
	InfoCajero[id][atmDinero] = 0;
	InfoCajero[id][atmPotX] = 0.0;
	InfoCajero[id][atmPotY] = 0.0;
	InfoCajero[id][atmPotZ] = 0.0;
	InfoCajero[id][atmRotX] = 0.0;
	InfoCajero[id][atmRotY] = 0.0;
	InfoCajero[id][atmRotZ] = 0.0;
	InfoCajero[id][atmInterior] = 0;
	InfoCajero[id][atmVirtualWorld] = 0;
	if (IsValidDynamicObject(InfoCajero[id][atmObject])) DestroyDynamicObject(InfoCajero[id][atmObject]);
	InfoCajero[id][atmObject] = 0;
	if (IsValidDynamic3DTextLabel(InfoCajero[id][atmLabel]))
	{
		DestroyDynamic3DTextLabel(InfoCajero[id][atmLabel]);
		InfoCajero[id][atmLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	new query[2048];
	mysql_format(db_samp, query, sizeof query, "UPDATE cajeros SET Modelo = 0, BolosUwU = 0, PotX = 0.0, PotY = 0.0, PotZ = 0.0, RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'", InfoCajero[id][atmID_sql]);
	mysql_tquery(db_samp, query);
	format(string, sizeof string, "Borraste el cajero ID %d, SQL vacía: %d", id, InfoCajero[id][atmID_sql]);
	SendPlayerChatMessage(playerid, -1, string);
	return 1;
}

cmd:ircajero(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, string[128];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ircajero (CajeroID)");
	if (id < 1 || id >= MAX_CAJEROS) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de cajero erróneo.");
	if (!InfoCajero[id][atmModelo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id cajero invalida.");
	SetPosEx(playerid, InfoCajero[id][atmPotX], InfoCajero[id][atmPotY], InfoCajero[id][atmPotZ], 0.0, InfoCajero[id][atmInterior], InfoCajero[id][atmVirtualWorld], 1);
	format(string, sizeof string, "Teleport al cajero ID %d.", id);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	return 1;
}
