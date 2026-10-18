Dialog:GraffitiPersonalizado(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (strlen(inputtext) > 60 || strlen(inputtext) < 4)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "Su graffiti personalizadono puede tener menos de 4 o más de 60 carácteres.");
		return pc_cmd_graffiti(playerid);
	}
	SetPVarInt(playerid, "LetraGraffiti", 10);
	SetPVarInt(playerid, "SetraGraffiti", 10);
	SetPVarString(playerid, "TextoGraffiti", inputtext);
	new text[256];
	format(text, sizeof text, "Graffiti actual: {EBEBEB}%s", inputtext);
	SendPlayerChatMessage(playerid, 0x00AACCFF, text);
	SendPlayerChatMessage(playerid, 0xA9D159FF, "Ahora puedes pintar cualquier punto de graffiti, sólo rocia la pared con tu spray!");
	return 1;
}

Dialog:AdminGraffiti(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (GetPVarInt(playerid, "z_graffs") == 1)
	{
		new ID = listitem, StrPVar[40];
		format(StrPVar, sizeof StrPVar, "e_graffiti%d", ID);
		new i = GetPVarInt(playerid, StrPVar);
		if (InfoCuenta[playerid][jAdmin] < 1) return Dialog_Show(playerid, AdminGraffiti, DIALOG_STYLE_LIST, "Graffitis", "Ir", "Continuar", "Volver");
		else Dialog_Show(playerid, AdminGraffiti, DIALOG_STYLE_LIST, "Graffitis", "Ir\nEditar coordenadas\nLimpiar\nBorrar coordenadas", "Continuar", "Volver");
		SetPVarInt(playerid, "z_graffs", 2);
		SetPVarInt(playerid, "grafs", i);
		return 1;
	}
	else if (GetPVarInt(playerid, "z_graffs") == 2)
	{
		if (!response) return pc_cmd_vergraffitis(playerid);
		new i = GetPVarInt(playerid, "grafs");
		new gformat[512];
		switch (listitem)
		{
			case 0: // ir
				SetPosEx(playerid, InfoGraffiti[i][gr_PosX], InfoGraffiti[i][gr_PosY], InfoGraffiti[i][gr_PosZ], 0.0, InfoGraffiti[i][gr_Interior], InfoGraffiti[i][gr_VirtualWorld], 1);
			case 1: // editar
			{
				edicion_sql_actual[playerid] = i;
				EditDynamicObject(playerid, InfoGraffiti[i][gr_Objeto]);
				InfoPersonaje[playerid][pEditingMode] = 13;
			}
			case 2: // limpiar
			{
				alm(InfoGraffiti[i][gr_Mensaje], "ninguno");
				alm(InfoGraffiti[i][gr_Creador], "ninguno");
				InfoGraffiti[i][gr_Fecha] = 0;
				if (IsValidDynamicObject(InfoGraffiti[i][gr_Objeto])) DestroyDynamicObject(InfoGraffiti[i][gr_Objeto]);
				InfoGraffiti[i][gr_Objeto] = 0;
				InfoGraffiti[i][gr_Objeto] = CreateDynamicObject(18665, InfoGraffiti[i][gr_PosX], InfoGraffiti[i][gr_PosY], InfoGraffiti[i][gr_PosZ], InfoGraffiti[i][gr_RotX], InfoGraffiti[i][gr_RotY], InfoGraffiti[i][gr_RotZ], -1, 0, -1, 6000.0);
				mysql_format(db_samp, gformat, sizeof gformat, "UPDATE graffitis SET Mensaje = '%e', Creador = '%e', Fecha = '%d' WHERE ID = '%d'", InfoGraffiti[i][gr_Mensaje], InfoGraffiti[i][gr_Creador], InfoGraffiti[i][gr_Fecha], InfoGraffiti[i][grID_sql]);
				mysql_tquery(db_samp, gformat);
				format(gformat, sizeof gformat, "Limpiaste el graffiti ID %d", i);
				SendPlayerChatMessage(playerid, -1, gformat);
				Streamer_Update(playerid);
			}
			case 3: // borrar
			{
				alm(InfoGraffiti[i][gr_Mensaje], "ninguno");
				alm(InfoGraffiti[i][gr_Creador], "ninguno");
				InfoGraffiti[i][gr_Fecha] = 0;
				InfoGraffiti[i][gr_PosX] = 0.0;
				InfoGraffiti[i][gr_PosY] = 0.0;
				InfoGraffiti[i][gr_PosZ] = 0.0;
				InfoGraffiti[i][gr_RotX] = 0.0;
				InfoGraffiti[i][gr_RotY] = 0.0;
				InfoGraffiti[i][gr_RotZ] = 0.0;
			    InfoGraffiti[i][gr_Interior] = 0;
			    InfoGraffiti[i][gr_VirtualWorld] = 0;
				InfoGraffiti[i][gr_Fecha] = 0;
				if (IsValidDynamicObject(InfoGraffiti[i][gr_Objeto])) DestroyDynamicObject(InfoGraffiti[i][gr_Objeto]);
				InfoGraffiti[i][gr_Objeto] = 0;
				new query[1024];
				mysql_format(db_samp, query, sizeof query, "UPDATE graffitis SET Mensaje = '%e', Creador = '%e', Fecha = '%d', PotX = 0.0, PotY = 0.0, PotZ = 0.0, RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'",
				InfoGraffiti[i][gr_Mensaje], InfoGraffiti[i][gr_Creador], InfoGraffiti[i][gr_Fecha], InfoGraffiti[i][grID_sql]);
				mysql_tquery(db_samp, query);
				format(gformat, sizeof gformat, "Borraste el graffiti ID %d, SQL vacía: %d", i, InfoGraffiti[i][grID_sql]);
				SendPlayerChatMessage(playerid, -1, gformat);
				Streamer_Update(playerid);
			}
		}
	}
	return 1;
}
