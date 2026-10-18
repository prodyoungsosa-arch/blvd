forward OnFactionCreate(id);
public OnFactionCreate(id)
{
	totalfacciones++;
	InfoFaccion[id][fID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}

forward OnActiveMembers(playerid, id);
public OnActiveMembers(playerid, id)
{
	new members = 0;
	Loop(player, cache_num_rows(), 0)
	{
		new nombreapellido[32], newid = -1;
		rebel_string(player, "Nombre_Apellido", nombreapellido, 32);
		//fix 22/04/2020
		foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoPersonaje[juegador][pNombre_Apellido], nombreapellido, true)) { newid = juegador; }
 		//fix 22/04/2020
		if (IsPlayerConnectedEx(newid))
		{
			InfoPersonaje[newid][pLider] = 0;
			InfoPersonaje[newid][pMiembro] = 0;
			InfoPersonaje[newid][pRango] = 0;
			SendPlayerChatMessage(newid, COLOR_LIGHTRED, "Acaban de borrar la facción en la que estabas.");
		}
		new query[256];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET LiderFaccion = 0, MiembroFaccion = 0, Rango = 0 WHERE Nombre_Apellido = '%e'", nombreapellido);
		mysql_tquery(db_samp, query);
		members++;
	}
	alm(InfoFaccion[id][fNombre], "none");
	alm(InfoFaccion[id][fLogo], "none");
	alm(InfoFaccion[id][fLider], "disponible");
	alm(InfoFaccion[id][fSubLider], "disponible");
	alm(InfoFaccion[id][fMensaje], "none");
	InfoFaccion[id][fTipo] = 0;
	InfoFaccion[id][fDinero] = 0;
	InfoFaccion[id][fSalario] = 0;
	InfoFaccion[id][fMaxRangos] = 6;
	InfoFaccion[id][fSpawnX] = 0.0;
	InfoFaccion[id][fSpawnY] = 0.0;
	InfoFaccion[id][fSpawnZ] = 0.0;
	InfoFaccion[id][fSpawnR] = 0.0;
	InfoFaccion[id][fSpawnInt] = 0;
	InfoFaccion[id][fSpawnVW] = 0;
	InfoFaccion[id][fArmarioX] = 0.0;
	InfoFaccion[id][fArmarioY] = 0.0;
	InfoFaccion[id][fArmarioZ] = 0.0;
	InfoFaccion[id][fArmarioInt] = 0;
	InfoFaccion[id][fArmarioVW] = 0;
	DestroyDynamicPickup(InfoFaccion[id][fArmarioPickup]);
	if (IsValidDynamic3DTextLabel(InfoFaccion[id][fArmarioLabel]))
	{
		DestroyDynamic3DTextLabel(InfoFaccion[id][fArmarioLabel]);
		InfoFaccion[id][fArmarioLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	Loop(x, 20, 0)
	{
		InfoFaccion[id][fEquipo][x] = 0;
		InfoFaccion[id][fRequiere][x] = 0;
		InfoFaccion[id][fSkin][x] = 0;
		new que3ry[256];
		mysql_format(db_samp, que3ry, sizeof que3ry, "UPDATE facciones SET Equipo%d = 0, Requiere%d = 0, Skin%d = 0 WHERE ID = '%d'", x+1, x+1, x+1, InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, que3ry);
	}
	Loop(x, 15, 0)
	{
		new gformat[15], que3ry[256];
		format(gformat, sizeof(gformat), "Rank%d", x+1);
		alm(fac_rango[id][x], gformat);
		mysql_format(db_samp, que3ry, sizeof que3ry, "UPDATE facciones SET Rango%d = '%e' WHERE ID = '%d'", x+1, fac_rango[id][x], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, que3ry);
	}
	new query[2048], string[256];
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e', Logo = '%e', Lider = '%e', SubLider = '%e', Mensaje = '%e', Tipo = 0, BolosUwU = 0, Salario = 0, \
	SpawnX = 0.0, SpawnY = 0.0, SpawnZ = 0.0, SpawnR = 0.0, SpawnInt = 0, SpawnVW = 0, ArmarioX = 0.0, ArmarioY = 0.0, ArmarioZ = 0.0, ArmarioInt = 0, ArmarioVW = 0, MaxRangos = 6 WHERE ID = '%d'",
	InfoFaccion[id][fNombre], InfoFaccion[id][fLogo], InfoFaccion[id][fLider], InfoFaccion[id][fSubLider], InfoFaccion[id][fMensaje], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(string, sizeof string, "Borraste la facción ID %d con %d miembros, SQL vacía: %d", id, members, InfoFaccion[id][fID_sql]);
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, string);
	return 1;
}

forward OnLimpiezaFacction(playerid, id);
public OnLimpiezaFacction(playerid, id)
{
	new members = 0;
	new query[512];
	Loop(player, cache_num_rows(), 0)
	{
		new nombreapellido[32], newid = -1;
		rebel_string(player, "Nombre_Apellido", nombreapellido, 32);
		//fix 22/04/2020
		foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoPersonaje[juegador][pNombre_Apellido], nombreapellido, true)) { newid = juegador; }
 		//fix 22/04/2020
		if (IsPlayerConnectedEx(newid))
		{
			InfoPersonaje[newid][pLider] = 0;
			InfoPersonaje[newid][pMiembro] = 0;
			InfoPersonaje[newid][pRango] = 0;
			RemovePlayerAttachedObject(newid, 8);
			InfoPersonaje[newid][pManoDerecha] = 0; InfoPersonaje[newid][pManoDerechaCant] = 0; RemovePlayerAttachedObject(newid, 7); ResetPlayerWeapons(newid);
			InfoPersonaje[newid][pEspalda] = 0; InfoPersonaje[newid][pEspaldaCant] = 0; RemovePlayerAttachedObject(newid, 9);
			SendPlayerChatMessage(newid, COLOR_LIGHTRED, "Acaban de limpiar la facción en la que estabas.");
		}
		Loop(x, 9, 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = 0, Cantidad_bolsillo_%d = 0 WHERE Nombre_Apellido = '%e'", x+1, x+1, nombreapellido);
			mysql_tquery(db_samp, query);
		}
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = 0, Cantidad_espalda = 0, Mano_derecha = 0, Cantidad_mano_derecha = 0,\
		Mano_izquierda = 50, Cantidad_mano_izquierda = 1, LiderFaccion = 0, MiembroFaccion = 0, Rango = 0, Skin = 299 WHERE Nombre_Apellido = '%e'", nombreapellido);
		mysql_tquery(db_samp, query);
		members++;
	}
	alm(InfoFaccion[id][fLider], "disponible");
	alm(InfoFaccion[id][fSubLider], "disponible");
	alm(InfoFaccion[id][fMensaje], "none");
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Lider = '%e', SubLider = '%e', Mensaje = '%e' WHERE ID = '%d'", InfoFaccion[id][fLider], InfoFaccion[id][fSubLider], InfoFaccion[id][fMensaje], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Limpiaste %s con %d miembros.", InfoFaccion[id][fNombre], members);
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, query);
	return 1;
}

forward OnMembersFaction(playerid, id);
public OnMembersFaction(playerid, id)
{
	new members = 0, gformat[512], dialog[4096] = "Nombre\tRango\tEstado\n";
	Loop(player, cache_num_rows(), 0)
	{
		new nombreapellido[32], rango, newid = -1;
		rebel_string(player, "Nombre_Apellido", nombreapellido, 32);
		rebel_int(player, "Rango", rango);
		//fix 22/04/2020
		foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoPersonaje[juegador][pNombre_Apellido], nombreapellido, true)) { newid = juegador; }
 		//fix 22/04/2020
		if (IsPlayerConnectedEx(newid)) format(gformat, sizeof gformat, "%s\t%s (%d)\t{29B311}Conectado\n", nombreapellido, fac_rango[id][rango-1], rango);
		else format(gformat, sizeof gformat, "%s\t%s (%d)\t{E24D32}Desconectado\n", nombreapellido, fac_rango[id][rango-1], rango);
		strcat(dialog, gformat);
		format(gformat, sizeof gformat, "Miembro_List%d", members);
		SetPVarString(playerid, gformat, nombreapellido);
		members++;
	}
	if (members == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_LIST, InfoFaccion[id][fNombre], "{FFFFFF}No se encontraron miembros.", "Cerrar", "");
	new acceso = 0;
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso != 0) Dialog_Show(playerid, MenuMiembros, DIALOG_STYLE_TABLIST_HEADERS, InfoFaccion[id][fNombre], dialog, "Continuar", "Salir");
	else Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, InfoFaccion[id][fNombre], dialog, "Cerrar", "");
	return 1;
}