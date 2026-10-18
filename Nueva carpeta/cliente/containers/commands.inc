//Jugadores
cmd:tirar(playerid)
{
	new query[256];
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando en esta situación.");
	if (InfoPersonaje[playerid][pManoDerecha] != 0)
	{
		for(new i = 0; i < MAX_CONTENEDORES; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, InfoContenedor[i][contPotX], InfoContenedor[i][contPotY], InfoContenedor[i][contPotZ]))
			{
			    TirarObjContenedor(playerid, i, 1);
			    return 1;
			}
		}
		new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoDerCant = InfoPersonaje[playerid][pManoDerechaCant];
		format(query, sizeof query, "tira su %s.", InfoInventario[ManoDer][NombreObjeto]);
		rol_ame(playerid, query);
		if (InfoInventario[ManoDer][IDArma] > 0)
		{
			format(query, sizeof query, "%s tira %s.", GetNameFormat(playerid), InfoInventario[ManoDer][NombreObjeto]);
			Log("f_logs/Tirar_Recoger.log", query);
		}
		ResetPlayerWeapons(playerid);
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid, 7);
		new Float: X, Float: Y, Float: Z;
		GetPlayerPos(playerid, X, Y, Z);
		tirar_objeto(ManoDer, ManoDerCant, X, Y, Z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), 0);
		Streamer_Update(playerid);
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		SetPlayerInventario(playerid, 3);
		return 1;
	}
	if (InfoPersonaje[playerid][pManoIzquierda] != 0)
	{
		for(new i = 0; i < MAX_CONTENEDORES; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, InfoContenedor[i][contPotX], InfoContenedor[i][contPotY], InfoContenedor[i][contPotZ]))
			{
			    TirarObjContenedor(playerid, i, 2);
			    return 1;
			}
		}
		new ManoDer = InfoPersonaje[playerid][pManoIzquierda], ManoDerCant = InfoPersonaje[playerid][pManoIzquierdaCant];
		format(query, sizeof query, "tira su %s.", InfoInventario[ManoDer][NombreObjeto]);
		rol_ame(playerid, query);
		if (InfoInventario[ManoDer][IDArma] > 0)
		{
			format(query, sizeof query, "%s tira %s.", GetNameFormat(playerid), InfoInventario[ManoDer][NombreObjeto]);
			Log("f_logs/Tirar_Recoger.log", query);
		}
		ResetPlayerWeapons(playerid);
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid, 8);
		new Float: X, Float: Y, Float: Z;
		GetPlayerPos(playerid, X, Y, Z);
		tirar_objeto(ManoDer, ManoDerCant, X, Y, Z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), 0);
		Streamer_Update(playerid);
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		SetPlayerInventario(playerid, 3);
		return 1;
	}
	SendPlayerChatMessage(playerid, 0xccccccff, "No posees ningún objeto en tus manos.");
	return 1;
}


cmd:vercontenedor(playerid)
{
	new id = -1;
	for(new i = 0; i < MAX_CONTENEDORES; i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, InfoContenedor[i][contPotX], InfoContenedor[i][contPotY], InfoContenedor[i][contPotZ]))
		{
		    id = i;
		    break;
		}
	}
	if(id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca de ningún contenedor.");
	new contenedor[1024], string[128];
	for(new i = 0; i < 10; i++)
	{
		new Bol = InfoContenedor[id][cInv][i];
		if(Bol == 0) format(string, sizeof(string), "\n{b0b0b0}Vacío");
		else format(string, sizeof(string), "\n{FFFFFF}%s", slot_objeto(InfoContenedor[id][cInv][i], InfoContenedor[id][cInvCant][i]));
		strcat(contenedor, string);
	}
	SetPVarInt(playerid, "ViendoContID", id);
	Dialog_Show(playerid, D_CONTENEDOR, DIALOG_STYLE_LIST, "{D6E1EB}Contenedor", contenedor, "Sacar", "Cancelar");
	return 1;
}
cmd:contenedor(playerid) return pc_cmd_vercontenedor(playerid);

//Administrativos
cmd:crearcontenedor(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (InfoPersonaje[playerid][pEditingMode] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás editando un objeto.");
	new query[1028];
	Loop(id, MAX_CONTENEDORES, 1) if (!InfoContenedor[id][contModelo])
	{
		InfoContenedor[id][contModelo] = 3035;
		GetPlayerPos(playerid, InfoContenedor[id][contPotX], InfoContenedor[id][contPotY], InfoContenedor[id][contPotZ]);
		InfoContenedor[id][contInterior] = GetPlayerInterior(playerid);
		InfoContenedor[id][contVirtualWorld] = GetPlayerVirtualWorld(playerid);
		Label_contenedor(id, 1);
		SendPlayerChatMessage(playerid, 0x90C3D4FF, "Creaste el contenedor indicado, ahora editalo.");
		EditDynamicObject(playerid, InfoContenedor[id][contObject]);
		InfoPersonaje[playerid][pEditingMode] = 75;
		edicion_sql_actual[playerid] = id;
		//opción idsql ya creada.
		if (InfoContenedor[id][contID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE contenedores SET Modelo = '%d', PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoContenedor[id][contModelo],
			InfoContenedor[id][contPotX],
			InfoContenedor[id][contPotY],
			InfoContenedor[id][contPotZ],
			InfoContenedor[id][contRotX],
			InfoContenedor[id][contRotY],
			InfoContenedor[id][contRotZ],
			InfoContenedor[id][contInterior],
			InfoContenedor[id][contVirtualWorld],
			InfoContenedor[id][contID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_CONTENEDORES;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO contenedores (Modelo, PotX, PotY, PotZ, RotX, RotY, RotZ, Interior, VirtualWorld) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
		InfoContenedor[id][contModelo],
		InfoContenedor[id][contPotX],
		InfoContenedor[id][contPotY],
		InfoContenedor[id][contPotZ],
		InfoContenedor[id][contRotX],
		InfoContenedor[id][contRotY],
		InfoContenedor[id][contRotZ],
		InfoContenedor[id][contInterior],
		InfoContenedor[id][contVirtualWorld]);
		mysql_tquery(db_samp, query, "OnContenedorCreate", "i", id);
		id = MAX_CONTENEDORES;
	}
	return 1;
}

cmd:borrarcontenedor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, string[256];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borrarcontenedor (contenedorID)");
	if (!InfoContenedor[id][contModelo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id contenedor invalida.");
	InfoContenedor[id][contModelo] = 0;
	InfoContenedor[id][contPotX] = 0.0;
	InfoContenedor[id][contPotY] = 0.0;
	InfoContenedor[id][contPotZ] = 0.0;
	InfoContenedor[id][contRotX] = 0.0;
	InfoContenedor[id][contRotY] = 0.0;
	InfoContenedor[id][contRotZ] = 0.0;
	InfoContenedor[id][contInterior] = 0;
	InfoContenedor[id][contVirtualWorld] = 0;
	if (IsValidDynamicObject(InfoContenedor[id][contObject])) DestroyDynamicObject(InfoContenedor[id][contObject]);
	InfoContenedor[id][contObject] = 0;
	if (IsValidDynamic3DTextLabel(InfoContenedor[id][contLabel]))
	{
		DestroyDynamic3DTextLabel(InfoContenedor[id][contLabel]);
		InfoContenedor[id][contLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	new query[2048];
	mysql_format(db_samp, query, sizeof query, "UPDATE contenedores SET Modelo = 0, PotX = 0.0, PotY = 0.0, PotZ = 0.0, RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'", InfoContenedor[id][contID_sql]);
	mysql_tquery(db_samp, query);
	format(string, sizeof string, "Borraste el contenedor ID %d, SQL vacía: %d", id, InfoContenedor[id][contID_sql]);
	SendPlayerChatMessage(playerid, -1, string);
	return 1;
}

cmd:ircontenedor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, string[128];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ircontenedor (contenedorID)");
	if (id < 1 || id >= MAX_CONTENEDORES) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de contenedor erróneo.");
	if (!InfoContenedor[id][contModelo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id contenedor invalida.");
	SetPosEx(playerid, InfoContenedor[id][contPotX], InfoContenedor[id][contPotY], InfoContenedor[id][contPotZ], 0.0, InfoContenedor[id][contInterior], InfoContenedor[id][contVirtualWorld], 1);
	format(string, sizeof string, "Teleport al contenedor ID %d.", id);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	return 1;
}