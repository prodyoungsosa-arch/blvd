cmd:adminmap(playerid)
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Comandos del sistema de objetos dinámicos (MAP)");
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, "/mapear (Para crear objeto) - /a_objetos (Ver objetos en rango especifico) - /irobjeto (Ir objeto especifico)");
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, "/objetosadmin (Para ver diálogo de objetos creados) - /editar_objeto (Editar objeto especifico)");
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, "/aborrarobjeto (Borrar objeto especifico) - /borrarobjetoadmin (Borrar objeto más cercano)");
	return 1;
}

cmd:a_objetos(playerid, params[])
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new string[128], radius;
	if (sscanf(params, "d", radius)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /a_objetos (Radio)");
	if (radius < 1 || radius > 100) { SendPlayerChatMessage(playerid, COLOR_GREY, "El radio debe ser de 1 a 100."); return 1; }
	Loop(id, MAX_OBJETOS_ADMIN, 1) if (IsPlayerInRangeOfPoint(playerid, radius, InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ]) && InfoPersonaje[playerid][pInterior] == InfoObjeto[id][oInterior] && InfoPersonaje[playerid][pVirtualWorld] == InfoObjeto[id][oVirtualWorld])
	{
		format(string, sizeof string, "ID: %d - Modelo: %d", id, InfoObjeto[id][oModelo]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	}
	return 1;
}

cmd:irobjeto(playerid, params[])
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /irobjeto (ObjetoID)");
	if (id < 1 || id >= MAX_OBJETOS_ADMIN) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de objeto admin inválido.");
	if (!InfoObjeto[id][oPotX]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID Invalida.");

	SetPosEx(playerid, InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ], 0.0, InfoObjeto[id][oInterior], InfoObjeto[id][oVirtualWorld], 1);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, "Teleportado.");
	return 1;
}

cmd:aborrarobjeto(playerid, params[])
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /aborrarobjeto (ObjetoID)");
	if (id < 1 || id >= MAX_OBJETOS_ADMIN) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de objeto admin inválido.");
	if (!InfoObjeto[id][oPotX]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID Invalida.");

	if (IsValidDynamicObject(InfoObjeto[id][oObjeto])) DestroyDynamicObject(InfoObjeto[id][oObjeto]);
	InfoObjeto[id][oObjeto] = 0;

	new string[256];
	format(string, sizeof string , "Borraste el objeto ID %d (Modelo: %d), SQL vacía: %d", id, InfoObjeto[id][oModelo], InfoObjeto[id][oID_sql]);

	InfoObjeto[id][oModelo] = 0;
	InfoObjeto[id][oPotX] = 0.0;
	InfoObjeto[id][oPotY] = 0.0;
	InfoObjeto[id][oPotZ] = 0.0;
	InfoObjeto[id][oRotX] = 0.0;
	InfoObjeto[id][oRotY] = 0.0;
	InfoObjeto[id][oRotZ] = 0.0;
	InfoObjeto[id][oInterior] = 0;
	InfoObjeto[id][oVirtualWorld] = 0;

	new query[1028];
	mysql_format(db_samp, query, sizeof query, "UPDATE objetos_admin SET Modelo = 0, PotX = 0.0, PotY = 0.0, PotZ = 0.0, RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'", InfoObjeto[id][oID_sql]);
	mysql_tquery(db_samp, query);

	SendPlayerChatMessage(playerid, -1, string);
	return 1;
}

cmd:borrarobjetoadmin(playerid)
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	Loop(id, MAX_OBJETOS_ADMIN, 1) if (InfoObjeto[id][oPotX] != 0.0)
	{
		if (IsPlayerInRangeOfPoint(playerid, 3.0, InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ]) && InfoPersonaje[playerid][pInterior] == InfoObjeto[id][oInterior] && InfoPersonaje[playerid][pVirtualWorld] == InfoObjeto[id][oVirtualWorld])
		{
			if (IsValidDynamicObject(InfoObjeto[id][oObjeto])) DestroyDynamicObject(InfoObjeto[id][oObjeto]);
			InfoObjeto[id][oObjeto] = 0;

			new string[256];
			format(string, sizeof string , "Borraste el objeto ID %d (Modelo: %d), SQL vacía: %d", id, InfoObjeto[id][oModelo], InfoObjeto[id][oID_sql]);

			InfoObjeto[id][oModelo] = 0;
			InfoObjeto[id][oPotX] = 0.0;
			InfoObjeto[id][oPotY] = 0.0;
			InfoObjeto[id][oPotZ] = 0.0;
			InfoObjeto[id][oRotX] = 0.0;
			InfoObjeto[id][oRotY] = 0.0;
			InfoObjeto[id][oRotZ] = 0.0;
			InfoObjeto[id][oInterior] = 0;
			InfoObjeto[id][oVirtualWorld] = 0;

			new query[2048];
			mysql_format(db_samp, query, sizeof query, "UPDATE objetos_admin SET Modelo = 0, PotX = 0.0, PotY = 0.0, PotZ = 0.0, RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'", InfoObjeto[id][oID_sql]);
			mysql_tquery(db_samp, query);

			SendPlayerChatMessage(playerid, -1, string);
			return 1;
		}
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca de ningún objeto dinámico admin.");
	return 1;
}

cmd:objetosadmin(playerid)
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new as2[256], DComandosAdmin[3500], tobjects, i = 0;
	Loop(id, MAX_OBJETOS_ADMIN, 1) if (InfoObjeto[id][oPotX] != 0.0)
	{
		i++;
		format(as2, sizeof(as2), "ID: %d | OBJETO: %d | ", id, InfoObjeto[id][oModelo]);
		strcat(DComandosAdmin, as2);
		if (i == 6)
		{
			i = 0;
			strcat(DComandosAdmin, "\n");
		}
		tobjects++;
	}
	if(tobjects > 0) Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Objetos admin", DComandosAdmin, "Cerrar", "");
	else Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Objetos admin", "{FFFFFF}No hay ningún objeto dinámico creado.", "Cerrar", "");
	return 1;
}

cmd:editar_objeto(playerid, params[])
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new id;
	if (InfoPersonaje[playerid][pEditingMode] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás editando un objeto.");
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editar_objeto (ObjetoID)");
	if (id < 1 || id >= MAX_OBJETOS_ADMIN) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de objeto admin inválido.");
	if (!InfoObjeto[id][oPotX]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID Invalida.");

	if (IsPlayerInRangeOfPoint(playerid, 3.0, InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ]) && InfoPersonaje[playerid][pInterior] == InfoObjeto[id][oInterior] && InfoPersonaje[playerid][pVirtualWorld] == InfoObjeto[id][oVirtualWorld])
	{
		edicion_sql_actual[playerid] = id;
		InfoPersonaje[playerid][pEditingMode] = 4;
		EditDynamicObject(playerid, InfoObjeto[id][oObjeto]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca del objeto.");
	return 1;
}

cmd:mapear(playerid, params[])
{
	if (InfoCuenta[playerid][jEncMap] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de mapper.");
	new id = -1;
	Loop(x, MAX_OBJETOS_ADMIN, 1) if (InfoObjeto[x][oModelo] == 0)
	{
		id = x;
		break;
	}
	if (id == -1) return SendClientMessageEx(playerid, COLOR_GREY, "Se alcanzó el límite de objetos admin (%d).", MAX_OBJETOS_ADMIN);
	if (isnull(params))
	{
		new OA[20];
		OA[0] = 2636; OA[1] = 2121; OA[2] = 1811; OA[3] = 2748; OA[4] = 2763; OA[5] = 2644; OA[6] = 2188; OA[7] = 11691; OA[8] = 2111; OA[9] = 1824; OA[10] = 1896;
		OA[11] = 1516; OA[12] = 15037; OA[13] = 2636; OA[14] = 3039; OA[15] = 3862; OA[16] = 3040; OA[17] = 3860; OA[18] = 8572; OA[19] = 19470;
		ShowModelSelectionMenuEx(playerid, OA, 20, "Objetos	", IDObj_Admin);
		edicion_sql_actual[playerid] = id;
	}
	else
	{
		new modelid;
		if (sscanf(params, "d", modelid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearobjetoadmin (Modelo de SAMP)");
		if (modelid < 700 || modelid > 19999) return SendPlayerChatMessage(playerid, COLOR_GREY, "Modelo inválido, intenta con otro.");

		Creando_Objeto_Admin(playerid, id, modelid);
	}
	return 1;
}
alias:mapear("crearobjetoadmin");