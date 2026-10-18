// Jugadores
cmd:togfaccion(playerid)
{
	if (InfoPersonaje[playerid][pTogFaccion] != 0)
	{
		InfoPersonaje[playerid][pTogFaccion] = 0;
		ShowTDN(playerid, "Ahora ~r~~h~no verás~w~ los mensajes de facción.");
	}
	else
	{
		InfoPersonaje[playerid][pTogFaccion] = 1;
		ShowTDN(playerid, "Ahora ~b~~h~puedes ver~w~ los mensajes de facción.");
	}
	guardar_int_mysql("personajes", "TogFaccion", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogFaccion]);
	return 1;
}
alias:togfaccion("togfac");
cmd:facciones(playerid)
{
	new gformat[320], dialog[3048] = "Facción\tMiembros (ON)\tLíder\tSub Líder\n";
	Loop(id, totalfacciones, 1) if (InfoFaccion[id][fTipo] != 0)
	{
		format(gformat, sizeof gformat, "{EBEBEB}(%d %s%s{EBEBEB}) %s\t%d ({00CC00}%d{EBEBEB})\t{589DA0}%s\t%s\n", id, GetColorLogo(InfoFaccion[id][fTipo]), InfoFaccion[id][fLogo], InfoFaccion[id][fNombre], GetMiembrosFaccion(id), OnFaction(id), InfoFaccion[id][fLider], InfoFaccion[id][fSubLider]);
		strcat(dialog, gformat);
	}
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, "Facciones", dialog, "Cerrar", "");
	return 1;
}
alias:facciones("organizaciones", "bandas", "facc");

cmd:listamiembros(playerid)
{
	new faccion = InfoPersonaje[playerid][pMiembro];
	if (faccion == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembros de facción.");
	new query[256];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE MiembroFaccion = '%d'", faccion);
	mysql_tquery(db_samp, query, "OnMembersFaction", "dd", playerid, faccion);
	return 1;
}
alias:listamiembros("integrantes", "miembros");

cmd:fnombre(playerid, params[])
{
	new acceso = 0, id = InfoPersonaje[playerid][pMiembro];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de facción.");
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres lider de facción o rango máximo.");
	new fnombre[128], query[256];
	if (sscanf(params, "s[128]", fnombre)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fnombre (Nombre)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tu facción no tiene un tipo asignado.");
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		alm(InfoFaccion[id][fNombre], fnombre);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e' WHERE ID = '%d'", InfoFaccion[id][fNombre], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Nuevo nombre: %s", fnombre);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	}
	else
	{
		if (NoFacEdit(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes editar facciones oficiales del servidor.");
		alm(InfoFaccion[id][fNombre], fnombre);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e' WHERE ID = '%d'", InfoFaccion[id][fNombre], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Nuevo nombre: %s", fnombre);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	}
	return 1;
}

cmd:fequipo(playerid, params[])
{
	new acceso = 0, id = InfoPersonaje[playerid][pMiembro];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de facción.");
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres lider de facción o rango máximo.");
	new query[256], item, rango;
	if (sscanf(params, "dd", item, rango)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fequipo (ID Item) (Rango)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tu facción no tiene un tipo asignado.");
	if (item > 20 || item < 1)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "El máximo de items del equipo es 20.");
		return 1;
	}
	if (rango > InfoFaccion[id][fMaxRangos] || rango < 1)
	{
		format(query, sizeof query, "El máximo de rangos de %s es %d.", InfoFaccion[id][fLogo], InfoFaccion[id][fMaxRangos]);
		SendPlayerChatMessage(playerid, COLOR_GREY, query);
		return 1;
	}
	if (InfoFaccion[id][fEquipo][item-1] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese slot del equipo está vacío.");
	InfoFaccion[id][fRequiere][item-1] = rango;
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Requiere%d = '%d' WHERE ID = '%d'", item, rango, InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Item %s de uso mínimo rango %d (%s)", GetObjEquipo(InfoFaccion[id][fEquipo][item-1]), rango, fac_rango[id][rango-1]);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	return 1;
}

cmd:frango(playerid, params[])
{
	new acceso = 0, id = InfoPersonaje[playerid][pMiembro];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de facción.");
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres lider de facción o rango máximo.");
	new fnamerango[32], query[256], rango;
	if (sscanf(params, "ds[32]", rango, fnamerango)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /frango (Rango) (Nombre)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tu facción no tiene un tipo asignado.");
	if (rango > InfoFaccion[id][fMaxRangos] || rango < 1)
	{
		format(query, sizeof query, "El máximo de rangos de %s es %d.", InfoFaccion[id][fLogo], InfoFaccion[id][fMaxRangos]);
		SendPlayerChatMessage(playerid, COLOR_GREY, query);
		return 1;
	}
	alm(fac_rango[id][rango-1], fnamerango);
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Rango%d = '%e' WHERE ID = '%d'", rango, fnamerango, InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Rango %d: %s", rango, fnamerango);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	return 1;
}

cmd:fchat(playerid)
{
	new acceso = 0, id = InfoPersonaje[playerid][pMiembro];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de facción.");
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres lider de facción o rango máximo.");
	if (InfoFaccion[id][fChat] != 0)
	{
		InfoFaccion[id][fChat] = 0;
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "Desbloqueaste el canal /f de tu facción.");
	}
	else
	{
		InfoFaccion[id][fChat] = 1;
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "Bloqueaste el canal /f de tu facción.");
	}
	return 1;
}

cmd:invitar(playerid, params[])
{
	new acceso = 0, id = InfoPersonaje[playerid][pMiembro], playerid2, dialog[550];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de facción.");
	if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) { acceso = 1; }
	else { if (InfoPersonaje[playerid][pLider] == id) acceso = 1; }
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres lider de facción o rango máximo.");
	if (GetMiembrosFaccion(id) >= 70) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes tener más de 70 miembros.");
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /invitar (PlayerID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if (TomandoTrabajo[playerid2] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este jugador está en otra tarea, espera.");
	if (InfoPersonaje[playerid2][pLider]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador es lider de una facción.");
	if (InfoPersonaje[playerid2][pMiembro]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador ya es miembro de una facción.");

	TomandoTrabajo[playerid2] = playerid;
	format(dialog, sizeof dialog, "{FFFFFF}%s te ha ofrecido unirte a {3E62F4}%s\n\
	{FFFFFF}Si quieres ser parte presiona 'si', de lo contrario presiona 'no'.\n", GetNameFormat(playerid), InfoFaccion[id][fNombre]);
	Dialog_Show(playerid2, InviteFaccion, DIALOG_STYLE_MSGBOX, "Unirse facción", dialog, "Si", "No");
	format(dialog, sizeof(dialog), "Has ofrecido a %s, formar parte de tu facción.", GetNameFormat(playerid2));
	SendPlayerChatMessage(playerid, COLOR_GREEN, dialog);
	return 1;
}
alias:invitar("contratar", "darfaccion", "darbanda");

cmd:f(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], string[512];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en ninguna facción.");
	if (InfoPersonaje[playerid][pTogFaccion] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes enviar mensajes si togeaste el canal, escribe /togfaccion.");
	if (InfoFaccion[id][fChat] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes enviar mensajes dado que un rango alto, bloqueó el /f.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /f (Texto)");
	switch (id)
	{
	    case 1,2,3,4,5,6,7: format(string, sizeof string, "{7BDDA5}[%s] %s %s:{FFFFFF} %s", InfoFaccion[id][fLogo], fac_rango[id][InfoPersonaje[playerid][pRango]-1], NombreOriginal(playerid), params);
	    default: format(string, sizeof string, "{7BDDA5}[%s] %s %s:{FFFFFF} %s", InfoFaccion[id][fLogo], fac_rango[id][InfoPersonaje[playerid][pRango]-1], NombreOriginal(playerid), params);
	}
	SendFaccionMessage(id, 0xFFFFFFFF, string);
	return 1;
}
alias:f("fac");

cmd:r(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], string[314];
	if (!member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo facciones oficiales del servidor tienen radio.");
	if (InfoPersonaje[playerid][pTogRadio] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees la radio de facción apagada, escribe /togradio.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /r (Texto)");
	//default
	if (member_faccion(playerid, 1, 4, 6)) format(string, sizeof string, "** [CH: DISPATCH, S: 1] %s: %s", GetNameFormat(playerid), params);
	else format(string, sizeof string, "** [CH: 0-, S: 1] %s: %s", GetNameFormat(playerid), params);
	SendRadioMessage(id, COLOR_RADIO, string, 0);
	format(string, sizeof string, "%s por radio: %s", GetNameFormat(playerid), params);
	ProxExDetector(3.5, playerid, string, 0x95939300, 0x95939300, 0x95939300, 0x95939300, 0x95939300);
	return 1;
}

cmd:wsp(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], string[314];
	if (!member_faccion(playerid, 9, 10, 11)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo facciones no-oficiales del servidor tienen wsp.");
	if (InfoPersonaje[playerid][pTogRadio] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees el whastapp deshabilitado, escribe /togwsp.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /wsp (Texto)");
	format(string, sizeof string, "(WS de %s) %s", GetPlayerFirstName(playerid), params);
	SendRadioMessage(id, 0x00D356FF, string, 0);
	return 1;
}
alias:wsp("ws");

cmd:d2(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], rango = InfoPersonaje[playerid][pRango], string[314];
	if (!member_faccion(playerid, 1, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo para miembros de LSPD y LSCSD.");
	if (InfoPersonaje[playerid][pTogRadio] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees la radio de facción apagada, escribe /togradio.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /d2 (Texto)");
	format(string, sizeof string, "** [%s] %s %s: %s **", InfoFaccion[id][fLogo], fac_rango[id][rango-1], GetNameFormat(playerid), params);
	SendRadioMessage(1, 0x00AEAEFF, string, 0);
	SendRadioMessage(4, 0x00AEAEFF, string, 0);
	format(string, sizeof string, "%s por radio: %s", GetNameFormat(playerid), params);
	ProxExDetector(3.5, playerid, string, 0x95939300, 0x95939300, 0x95939300, 0x95939300, 0x95939300);
	return 1;
}

cmd:d(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], rango = InfoPersonaje[playerid][pRango], string[314];
	if (!member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo facciones oficiales del servidor tienen acceso.");
	if (InfoPersonaje[playerid][pTogRadio] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees la radio de facción apagada, escribe /togradio.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /d (Texto)");
	format(string, sizeof string, "** [%s] %s %s: %s **", InfoFaccion[id][fLogo], fac_rango[id][rango-1], GetNameFormat(playerid), params);
	SendRadioMessage(1, 0xF07A7AFF, string, 0);
	SendRadioMessage(2, 0xF07A7AFF, string, 0);
	SendRadioMessage(3, 0xF07A7AFF, string, 0);
	SendRadioMessage(4, 0xF07A7AFF, string, 0);
	SendRadioMessage(5, 0xF07A7AFF, string, 0);
	SendRadioMessage(6, 0xF07A7AFF, string, 0);
	SendRadioMessage(7, 0xF07A7AFF, string, 0);
	format(string, sizeof string, "%s por radio: %s", GetNameFormat(playerid), params);
	ProxExDetector(3.5, playerid, string, 0x95939300, 0x95939300, 0x95939300, 0x95939300, 0x95939300);
	return 1;
}

cmd:dooc(playerid, params[])
{
	new id = InfoPersonaje[playerid][pMiembro], rango = InfoPersonaje[playerid][pRango], string[314];
	if (!member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo facciones oficiales del servidor tienen acceso.");
	if (InfoPersonaje[playerid][pTogRadio] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees la radio de facción apagada, escribe /togradio.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /d (Texto)");
	format(string, sizeof string, "(( [OOC: %s] %s %s: %s ))", InfoFaccion[id][fLogo], fac_rango[id][rango-1], GetNameFormat(playerid), params);
	SendRadioMessage(1, 0xAC58FAFF, string, 0);
	SendRadioMessage(2, 0xAC58FAFF, string, 0);
	SendRadioMessage(3, 0xAC58FAFF, string, 0);
	SendRadioMessage(4, 0xAC58FAFF, string, 0);
	SendRadioMessage(5, 0xAC58FAFF, string, 0);
	SendRadioMessage(6, 0xAC58FAFF, string, 0);
	SendRadioMessage(7, 0xAC58FAFF, string, 0);
	return 1;
}

cmd:equipo(playerid)
{
	new id = InfoPersonaje[playerid][pMiembro];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en ninguna facción.");
	if (InfoFaccion[id][fArmarioX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Su facción no tiene ajustado el lugar de /equipo.");
	//default
	if (IsPlayerInRangeOfPoint(playerid, 4.0, InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ]) && InfoPersonaje[playerid][pInterior] == InfoFaccion[id][fArmarioInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoFaccion[id][fArmarioVW])
	{
		new dialog[1870], titul[170], dialog2[256], count = 0, gformat[40];
		if (member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) //lspd, fbi, USMC, lscsd, gob, lsfd, sadoc
		{
			//duty
			if (OnDuty[playerid] != 0)
			{
				strcat(dialog, "{EFEFEF}Colocarse {FD1717}fuera de servicio\n");
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 0);
				count++;
			}
			else
			{
				strcat(dialog, "{EFEFEF}Colocarse {00C600}en servicio\n");
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 0);
				count++;
			}
			//equipo
			Loop(x, 20, 0) if (InfoFaccion[id][fEquipo][x] != 0)
			{
				format(dialog2, sizeof dialog2, "{EFEFEF}%s\n", GetObjEquipo(InfoFaccion[id][fEquipo][x]));
				strcat(dialog, dialog2);
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, x+1);
				count++;
			}
			//skins
			if (TieneSkin(id) != 0)
			{
				strcat(dialog, "{B7B7FF}Uniformes\n");
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 21);
				count++;
				if (GetPlayerSkin(playerid) != InfoPersonaje[playerid][pSkin])
				{
					strcat(dialog, "{B7B7FF}Vestir ropa normal\n");
					//conteo
					format(gformat, sizeof gformat, "RanuraEq%d", count);
					SetPVarInt(playerid, gformat, 22);
					count++;
				}
			}
			if (member_faccion(playerid, 1, 2, 3, 4, 7))
			{
				//Encubierto
				strcat(dialog, "{B7B7FF}Encubierto\n");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 23);
				count++;
				//Accessorios
				strcat(dialog, "{B7B7FF}Accessorios\n");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 24);
				count++;
				//Borrar objetos
				strcat(dialog, "{B7B7FF}Borrar objetos de manos\n");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 25);
				count++;
				//Cargadores
				strcat(dialog, "{B7B7FF}Cargadores");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 26);
				count++;
			}
			if (member_faccion(playerid, 6))
			{
				//Accessorios
				strcat(dialog, "{B7B7FF}Accessorios\n");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 24);
				count++;
				//Borrar objetos
				strcat(dialog, "{B7B7FF}Borrar objetos de manos\n");
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 25);
				count++;
			}
		}
		else //otros
		{
			//equipo
			Loop(x, 20, 0) if (InfoFaccion[id][fEquipo][x] != 0)
			{
				format(dialog2, sizeof dialog2, "{EFEFEF}%s\n", GetObjEquipo(InfoFaccion[id][fEquipo][x]));
				strcat(dialog, dialog2);
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, x);
				count++;
			}
			//skins
			if (TieneSkin(id) != 0)
			{
				strcat(dialog, "{EFEFEF}Skins\n");
				//conteo
				format(gformat, sizeof gformat, "RanuraEq%d", count);
				SetPVarInt(playerid, gformat, 20);
				count++;
				if (GetPlayerSkin(playerid) != InfoPersonaje[playerid][pSkin])
				{
					strcat(dialog, "{EFEFEF}Vestir skin normal");
					//conteo
					format(gformat, sizeof gformat, "RanuraEq%d", count);
					SetPVarInt(playerid, gformat, 21);
					count++;
				}
			}
		}
		format(titul, sizeof titul, "Equipo de {F5DEB3}%s", InfoFaccion[id][fLogo]);
		Dialog_Show(playerid, ShowEquipo, DIALOG_STYLE_LIST, titul, dialog, "Continuar", "Salir");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el lugar de /equipo.");
	return 1;
}

// Administrativos
cmd:qfaccoff(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No autorizado");
	new string[256];
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /qfaccoff (Nombre_Apellido)");
	if (VerificarPersonaje(params))
	{
		mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET LiderFaccion = 0, MiembroFaccion = 0, Rango = 0 WHERE Nombre_Apellido = '%e'", params);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) sacó variables de facción %s. (OFFLINE)", InfoCuenta[playerid][jNombre], playerid, params);
		SendAdminMessage(0xFFFFFFFF, string);
		Log("f_logs/admin.log", string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GRAD1, "Ese personaje no existe");
	return 1;
}
alias:qfaccoff("quitarfaccionoff");

cmd:statusfacc(playerid)
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new gformat[320], dialog[2048] = "Facción\tDinero\tSalario\n";
	Loop(id, totalfacciones, 1) if (InfoFaccion[id][fTipo] != 0)
	{
		format(gformat, sizeof gformat, "%s%s\t{00CC00}$%s\t{00CC00}$%s\n", GetColorLogo(InfoFaccion[id][fTipo]), InfoFaccion[id][fLogo], diner_coma(InfoFaccion[id][fDinero]), diner_coma(InfoFaccion[id][fSalario]));
		strcat(dialog, gformat);
	}
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, "Status de facciones", dialog, "Cerrar", "");
	return 1;
}
alias:statusfacc("statusfacciones");

cmd:facchat(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /facchat (Mensaje para miembros en las facciones)");
	new string[320];
	format(string, sizeof string, "{00A2FF}[E.F] %s:{FFFFFF} %s", NombreOriginal(playerid), params);
	foreach(Player, i) if (IsPlayerConnectedEx(i))
	{
		if (InfoPersonaje[i][pMiembro] != 0)
			SendSplitMessage(i, 0xFFFFFFFF, string);
	}
	return 1;
}

cmd:supervisar(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new faccion, string[345];
	if (sscanf(params, "d", faccion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /supervisar (FacciónID)");
	if (faccion < 0 || faccion > MAX_FACCIONES) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción incorrecta.");
	if (faccion == 0)
	{
		InfoPersonaje[playerid][pLider] = 0;
		InfoPersonaje[playerid][pMiembro] = 0;
		InfoPersonaje[playerid][pRango] = 0;
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, "Has dejado de supervisar facciones.");
		return 1;
	}
	if (!InfoFaccion[faccion][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	InfoPersonaje[playerid][pLider] = faccion;
	InfoPersonaje[playerid][pMiembro] = faccion;
	InfoPersonaje[playerid][pRango] = InfoFaccion[faccion][fMaxRangos];
	format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) está supervisando %s.", InfoCuenta[playerid][jNombre], playerid, InfoFaccion[faccion][fNombre]);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:hacerlider(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new playerid2, faccion, string[512], query[512];
	if (sscanf(params, "dd", playerid2, faccion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /hacerlider [id jugador] [facción]");
	if (faccion < 1 || faccion > MAX_FACCIONES) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción incorrecta.");
	if (!InfoFaccion[faccion][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if (strcmp(InfoFaccion[faccion][fLider], "disponible", true) == 0)
	{
		if (InfoPersonaje[playerid2][pMiembro] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador ya está en una facción.");
		alm(InfoFaccion[faccion][fLider], NombreDeCuenta(playerid2));
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Lider = '%e' WHERE ID = '%d'", InfoFaccion[faccion][fLider], InfoFaccion[faccion][fID_sql]);
		mysql_tquery(db_samp, query);
		InfoPersonaje[playerid2][pLider] = faccion;
		InfoPersonaje[playerid2][pMiembro] = faccion;
		InfoPersonaje[playerid2][pRango] = InfoFaccion[faccion][fMaxRangos];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET LiderFaccion = '%d', MiembroFaccion = '%d', Rango = '%d' WHERE ID = '%d'", faccion, faccion, InfoPersonaje[playerid2][pRango], InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
		format(string, sizeof string, "* %s te asignó el líder de %s.", NombreOriginal(playerid), InfoFaccion[faccion][fNombre]);
		SendPlayerChatMessage(playerid2, 0x6ADFFFFF, string);
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) asignó lider de %s a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoFaccion[faccion][fNombre], NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa facción ya posee lider, prueba /hacersublider.");
	return 1;
}

cmd:hacersublider(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new playerid2, faccion, string[512], query[512];
	if (sscanf(params, "dd", playerid2, faccion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /hacersublider [id jugador] [facción]");
	if (faccion < 1 || faccion > MAX_FACCIONES) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción incorrecta.");
	if (!InfoFaccion[faccion][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if (strcmp(InfoFaccion[faccion][fSubLider], "disponible", true) == 0)
	{
		if (InfoPersonaje[playerid2][pMiembro] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador ya está en una facción.");
		alm(InfoFaccion[faccion][fSubLider], NombreDeCuenta(playerid2));
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET SubLider = '%e' WHERE ID = '%d'", InfoFaccion[faccion][fSubLider], InfoFaccion[faccion][fID_sql]);
		mysql_tquery(db_samp, query);
		InfoPersonaje[playerid2][pLider] = faccion;
		InfoPersonaje[playerid2][pMiembro] = faccion;
		InfoPersonaje[playerid2][pRango] = InfoFaccion[faccion][fMaxRangos];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET LiderFaccion = '%d', MiembroFaccion = '%d', Rango = '%d' WHERE ID = '%d'", faccion, faccion, InfoPersonaje[playerid2][pRango], InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
		format(string, sizeof string, "* %s te asignó el sublíder de %s.", NombreOriginal(playerid), InfoFaccion[faccion][fNombre]);
		SendPlayerChatMessage(playerid2, 0x6ADFFFFF, string);
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) asignó sublider de %s a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoFaccion[faccion][fNombre], NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa facción ya posee sublider, intenta con /darmiembro o limpiando la facción.");
	return 1;
}

cmd:darmiembro(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new playerid2, id, rango, gformat[256];
	if (sscanf(params, "ddd", playerid2, id, rango)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darmiembro (JugadorID) (FacciónID) (Rango)");
	if (id < 0 || id > MAX_FACCIONES) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción incorrecta.");
	if (InfoPersonaje[playerid2][pLider] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando en lideres, debes limpiar la facción.");
	if (id == 0)
	{
		if (InfoPersonaje[playerid2][pMiembro] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está en ninguna facción.");
		OnDuty[playerid2] = 0;
		InfoPersonaje[playerid2][pLider] = 0;
		InfoPersonaje[playerid2][pMiembro] = 0;
		InfoPersonaje[playerid2][pRango] = 0;
		mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Rango = '%d', LiderFaccion = 0, MiembroFaccion = '%d' WHERE ID = '%d'", InfoPersonaje[playerid2][pRango], InfoPersonaje[playerid2][pMiembro], InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, gformat);
		format(gformat, sizeof gformat, "%s te sacó de la facción en la que estabas.", NombreOriginal(playerid));
		SendPlayerChatMessage(playerid2, 0x6ADFFFFF, gformat);
		format(gformat, sizeof gformat, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) saco a %s(%d) de la facción en la que estaba.", InfoCuenta[playerid][jNombre], playerid, NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, gformat);
		return 1;
	}
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if (rango < 1 || rango > InfoFaccion[id][fMaxRangos])
	{
		format(gformat, sizeof gformat, "El máximo de rangos de %s es de %d.", InfoFaccion[id][fLogo], InfoFaccion[id][fMaxRangos]);
		SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
		return 1;
	}
	OnDuty[playerid2] = 0;
	InfoPersonaje[playerid2][pLider] = 0;
	InfoPersonaje[playerid2][pMiembro] = id;
	InfoPersonaje[playerid2][pRango] = rango;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Rango = '%d', LiderFaccion = 0, MiembroFaccion = '%d' WHERE ID = '%d'", InfoPersonaje[playerid2][pRango], InfoPersonaje[playerid2][pMiembro], InfoPersonaje[playerid2][pID]);
	mysql_tquery(db_samp, gformat);
	format(gformat, sizeof gformat, "%s te asignó miembro de %s con rango %d.", NombreOriginal(playerid), InfoFaccion[id][fLogo], rango);
	SendPlayerChatMessage(playerid2, 0x6ADFFFFF, gformat);
	format(gformat, sizeof gformat, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) asignó miembro de %s (rango %d) a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoFaccion[id][fLogo], rango, NombreOriginal(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, gformat);
	return 1;
}
alias:darmiembro("hacermiembro");

cmd:crearfaccion(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new tipo, string[256], query[1028];
	if (sscanf(params, "d", tipo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearfaccion (Tipo)");
	SendPlayerChatMessage(playerid, 0xFF6347AA, "Tipos: 1 Legal 2 Pandilla 3 Mafia 4 Otro");
	if (tipo < 1 || tipo > 11) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Tipos: 1 Legal 2 Pandilla 3 Mafia 4 Otro");  														//	if (tipo < 1 || tipo > 5) return SendPlayerChatMessage(playerid, 0xFF6347AA, "1lspd, 2fbi, 3USMC, 4medicos, 5gobierno");
	tipo += 7;
	Loop(id, MAX_FACCIONES, 1) if (!InfoFaccion[id][fTipo])
	{
		alm(InfoFaccion[id][fNombre], "/editarfnombre");
		alm(InfoFaccion[id][fLogo], "none");
		alm(InfoFaccion[id][fLider], "disponible");
		alm(InfoFaccion[id][fSubLider], "disponible");
		alm(InfoFaccion[id][fMensaje], "none");
		InfoFaccion[id][fTipo] = tipo;
		InfoFaccion[id][fMaxRangos] = 6;
		Loop(x, 15, 0)
		{
			new gformat[15];
			format(gformat, sizeof gformat, "Rank%d", x+1);
			alm(fac_rango[id][x], gformat);
		}
		format(string, sizeof string, "%s ha creado la facción ID %d.", InfoCuenta[playerid][jNombre], id);
		Log("f_logs/Facciones.log", string);
		format(string, sizeof string, "Creaste la facción ID %d, configurala con /editarfnombre, /editarflogo y /editarfaccion", id);
		SendPlayerChatMessage(playerid, 0x90C3D4FF, string);

		//opción idsql ya creada.
		if (InfoFaccion[id][fID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e', Logo = '%e', Lider = '%e', SubLider = '%e', Mensaje = '%e', Tipo = '%d', MaxRangos = '%d' WHERE ID = '%d'",
			InfoFaccion[id][fNombre],
			InfoFaccion[id][fLogo],
			InfoFaccion[id][fLider],
			InfoFaccion[id][fSubLider],
			InfoFaccion[id][fMensaje],
			InfoFaccion[id][fTipo],
			InfoFaccion[id][fMaxRangos],
			InfoFaccion[id][fID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_FACCIONES;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO facciones (Nombre, Logo, Lider, SubLider, Mensaje, Tipo, MaxRangos) VALUES ('%e', '%e', '%e', '%e', '%e', '%d', '%d')",
		InfoFaccion[id][fNombre],
		InfoFaccion[id][fLogo],
		InfoFaccion[id][fLider],
		InfoFaccion[id][fSubLider],
		InfoFaccion[id][fMensaje],
		InfoFaccion[id][fTipo],
		InfoFaccion[id][fMaxRangos]);
		mysql_tquery(db_samp, query, "OnFactionCreate", "i", id);
		id = MAX_FACCIONES;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_RED, "Se alcanzó el máximo de facciones (50)");
	return 1;
}
alias:crearfaccion("crearfac");

cmd:borrarfaccion(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, query[256];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borrarfaccion [slot]");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE MiembroFaccion = '%d'", id);
		mysql_tquery(db_samp, query, "OnActiveMembers", "dd", playerid, id);
	}
	else
	{
		if (NoFacEdit(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes borrar facciones oficiales del servidor.");
		mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE MiembroFaccion = '%d'", id);
		mysql_tquery(db_samp, query, "OnActiveMembers", "dd", playerid, id);
	}
	return 1;
}
alias:borrarfaccion("borrarfac");

cmd:limpiarfaccion(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, query[256];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /limpiarfaccion (FacciónID)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE MiembroFaccion = '%d'", id);
	mysql_tquery(db_samp, query, "OnLimpiezaFacction", "dd", playerid, id);
	return 1;
}
alias:limpiarfaccion("limpiarf");

cmd:editarfnombre(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, fnombre[128], query[256];
	if (sscanf(params, "ds[128]", id, fnombre)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarfnombre (FacciónID) (Nombre)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		alm(InfoFaccion[id][fNombre], fnombre);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e' WHERE ID = '%d'", InfoFaccion[id][fNombre], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Facción %d | %s", id, fnombre);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	}
	else
	{
		if (NoFacEdit(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes editar facciones oficiales del servidor.");
		alm(InfoFaccion[id][fNombre], fnombre);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Nombre = '%e' WHERE ID = '%d'", InfoFaccion[id][fNombre], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Facción %d | %s", id, fnombre);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	}
	return 1;
}

cmd:editarflogo(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, flogo[11], query[256];
	if (sscanf(params, "ds[11]", id, flogo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarflogo (FacciónID) (LogoTipo)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		alm(InfoFaccion[id][fLogo], flogo);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Logo = '%e' WHERE ID = '%d'", InfoFaccion[id][fLogo], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Facción %d | %s", id, flogo);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
		if (InfoFaccion[id][fArmarioX] != 0.0) faccion_armario(id, 1);
	}
	else
	{
		if (NoFacEdit(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes editar facciones oficiales del servidor.");
		alm(InfoFaccion[id][fLogo], flogo);
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Logo = '%e' WHERE ID = '%d'", InfoFaccion[id][fLogo], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Facción %d | %s", id, flogo);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
		if (InfoFaccion[id][fArmarioX] != 0.0) faccion_armario(id, 1);
	}
	return 1;
}

cmd:editarflider(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, flider[25], query[256];
	if (sscanf(params, "ds[25]", id, flider)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarflider (FacciónID) (Lider)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	alm(InfoFaccion[id][fLider], flider);
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Lider = '%e' WHERE ID = '%d'", InfoFaccion[id][fLider], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Facción %d | Lider: %s", id, flider);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	return 1;
}

cmd:editarfsublider(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, flider[25], query[256];
	if (sscanf(params, "ds[25]", id, flider)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarfsublider (FacciónID) (SubLider)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	alm(InfoFaccion[id][fSubLider], flider);
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET SubLider = '%e' WHERE ID = '%d'", InfoFaccion[id][fSubLider], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Facción %d | Sub Lider: %s", id, flider);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	return 1;
}

cmd:editarfaccion(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, string[512], input;
	if (sscanf(params, "s[32]", params))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf (Nombre) (FacciónID) (Opción)");
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Opciones: dinero - tipo - salario - maxrangos - spawn - posequipo");
		return 1;
	}
	if (!strcmp(params, "dinero", true, 6))
	{
		if (sscanf(params, "s[32]ii", params, id, input)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf dinero (FacciónID) ($)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		InfoFaccion[id][fDinero] += input;
		guardar_int_mysql("facciones", "BolosUwU", InfoFaccion[id][fID_sql], InfoFaccion[id][fDinero]);
		format(string, sizeof string, "Ahora los fondos de la facción %s (%d) son $%d dólares.", InfoFaccion[id][fLogo], id, input);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	}
	else if (!strcmp(params, "tipo", true, 4))
	{
		if (sscanf(params, "s[32]ii", params, id, input)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf tipo (FacciónID) (Tipo) | Tipos (1: Legal | 2: Pandilla | 3: Mafia | 4: Otro)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		if (NoFacEdit(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes editar facciones oficiales del servidor.");
		if (input < 1 || input > 4) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Tipos (1: Legal | 2: Pandilla | 3: Mafia | 4: Otro)");
		input += 7;
		InfoFaccion[id][fTipo] = input;
		guardar_int_mysql("facciones", "Tipo", InfoFaccion[id][fID_sql], InfoFaccion[id][fTipo]);
		format(string, sizeof string, "Ahora el tipo de la facción %s (%d) es %d.", InfoFaccion[id][fLogo], id, input-5);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	}
	else if (!strcmp(params, "salario", true, 7))
	{
		if (sscanf(params, "s[32]ii", params, id, input)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf salario (FacciónID) ($)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		InfoFaccion[id][fSalario] = input;
		guardar_int_mysql("facciones", "Salario", InfoFaccion[id][fID_sql], InfoFaccion[id][fSalario]);
		format(string, sizeof string, "Ahora el salario de la facción %s (%d) es de $%d dólares.", InfoFaccion[id][fLogo], id, input);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	}
	else if (!strcmp(params, "maxrangos", true, 9))
	{
		if (sscanf(params, "s[32]ii", params, id, input)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf maxrangos (FacciónID) (Max)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		InfoFaccion[id][fMaxRangos] = input;
		guardar_int_mysql("facciones", "MaxRangos", InfoFaccion[id][fID_sql], InfoFaccion[id][fMaxRangos]);
		format(string, sizeof string, "Ahora el máximo de rangos de la facción %s (%d) es de %d rangos.", InfoFaccion[id][fLogo], id, input);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	}
	else if (!strcmp(params, "spawn", true, 5))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf spawn (FacciónID)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		GetPlayerPos(playerid, InfoFaccion[id][fSpawnX], InfoFaccion[id][fSpawnY], InfoFaccion[id][fSpawnZ]);
		GetPlayerFacingAngle(playerid, InfoFaccion[id][fSpawnR]);
		InfoFaccion[id][fSpawnInt] = GetPlayerInterior(playerid);
		InfoFaccion[id][fSpawnVW] = GetPlayerVirtualWorld(playerid);
		format(string, sizeof string, "Cambiaste el spawn de la facción %s (%d).", InfoFaccion[id][fLogo], id);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		mysql_format(db_samp, string, sizeof string, "UPDATE facciones SET SpawnX = '%f', SpawnY = '%f', SpawnZ = '%f', SpawnR = '%f', SpawnInt = '%d', SpawnVW = '%d' WHERE ID = '%d'", InfoFaccion[id][fSpawnX], InfoFaccion[id][fSpawnY], InfoFaccion[id][fSpawnZ], InfoFaccion[id][fSpawnR], InfoFaccion[id][fSpawnInt], InfoFaccion[id][fSpawnVW], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, string);
	}
	else if (!strcmp(params, "posequipo", true, 9))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarf posequipo (FacciónID)");
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
		GetPlayerPos(playerid, InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ]);
		InfoFaccion[id][fArmarioInt] = GetPlayerInterior(playerid);
		InfoFaccion[id][fArmarioVW] = GetPlayerVirtualWorld(playerid);
		format(string, sizeof string, "Cambiaste el lugar del /equipo de la facción %s (%d).", InfoFaccion[id][fLogo], id);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		mysql_format(db_samp, string, sizeof string, "UPDATE facciones SET ArmarioX = '%f', ArmarioY = '%f', ArmarioZ = '%f', ArmarioInt = '%d', ArmarioVW = '%d' WHERE ID = '%d'", InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ], InfoFaccion[id][fArmarioInt], InfoFaccion[id][fArmarioVW], InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, string);
		faccion_armario(id, 0);
	}
	return 1;
}
alias:editarfaccion("editarf");

cmd:editarfskin(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, pslot, pskin, query[256];
	if (sscanf(params, "ddd", id, pslot, pskin)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarfskin (FacciónID) (Slot [1-20]) (SkinModel)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (pslot < 1 || pslot > 20) return SendPlayerChatMessage(playerid, COLOR_GREY, "Slot inválido, prueba entre 1 al 20.");
	if (pskin == -1)
	{
		InfoFaccion[id][fSkin][pslot-1] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Skin%d = 0 WHERE ID = '%d'", pslot, InfoFaccion[id][fID_sql]);
		mysql_tquery(db_samp, query);
		format(query, sizeof query, "Facción %s | Skin%d: removido", InfoFaccion[id][fLogo], pslot);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
		return 1;
	}
	if (IsValidSkin(pskin) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Skin inválido, prueba entre 1 al 311.");
	Loop(x, 20, 0) if (InfoFaccion[id][fSkin][x] == pskin)
	{
		format(query, sizeof query, "Ya está el skin %d en el slot %d.", pskin, x+1);
		SendPlayerChatMessage(playerid, COLOR_GREY, query);
		return 1;
	}
	InfoFaccion[id][fSkin][pslot-1] = pskin;
	mysql_format(db_samp, query, sizeof query, "UPDATE facciones SET Skin%d = '%d' WHERE ID = '%d'", pslot, InfoFaccion[id][fSkin][pslot-1], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Facción %s | Skin%d: %d {FFFFFF}(Si quieres quitar el skin de este slot %d, usa en skin -1)", InfoFaccion[id][fLogo], pslot, pskin, pslot);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, query);
	return 1;
}

cmd:editarfequipo(playerid, params[])
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	new id, dialog[1024], gformat[256];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarfequipo (FacciónID)");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	Loop(x, 20, 0)
	{
		if (InfoFaccion[id][fEquipo][x] != 0) format(gformat, sizeof gformat, "{FFFFFF}%d | {b42d2d}%s\n", x+1, GetObjEquipo(InfoFaccion[id][fEquipo][x]));
		else format(gformat, sizeof gformat, "{CCCCCC}%d | Vacío\n", x+1);
		strcat(dialog, gformat);
	}
	format(gformat, sizeof gformat, "Equipo de %s", InfoFaccion[id][fLogo]);
	Dialog_Show(playerid, ChangeFequipo, DIALOG_STYLE_LIST, gformat, dialog, "Cambiar", "Salir");
	ID_ACTUAL_FACUWU[playerid] = id;
	return 1;
}

cmd:irfaccion(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, gformat[180];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /irfaccion (FacciónID) [esto te llevará al /equipo de la facción]");
	if (id < 1 || id > MAX_NEGOCIOS) return SendPlayerChatMessage(playerid, COLOR_GREY, "facción no encontrada.");
	if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de facción invalida.");
	if (InfoFaccion[id][fArmarioX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa facción no tiene ajustado el lugar de /equipo.");
	SetPosEx(playerid, InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ], 0.0000, InfoFaccion[id][fArmarioInt], InfoFaccion[id][fArmarioVW], 1);
	format(gformat, sizeof gformat, "Acabas de ir al lugar de /equipo de %s.", InfoFaccion[id][fLogo]);
	SendPlayerChatMessage(playerid, COLOR_GREEN, gformat);
	return 1;
}
alias:irfaccion("irf");