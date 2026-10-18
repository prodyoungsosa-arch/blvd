Dialog:ShowAdminPermisos(playerid, response, listitem, inputtext[])
{
	new playerid2 = PlayerPermisos[playerid];
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (!response) return 1;
	switch (listitem)
	{
		case 0: //casas
		{
			new count = 0, dialog_share[2056] = "{FFFFFF}", share_format[512], i = 0;
			Loop(id, totalcasas, 1) if (InfoCasa[id][cVenta] != 0 && InfoCasa[id][cTipo] != 0)
			{
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoCasa[id][cCompartida1], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoCasa[id][cCompartida2], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoCasa[id][cCompartida3], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (i == 3)
				{
					i = 0;
					strcat(dialog_share, "\n");
				}
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No le han dado permisos de ninguna casa.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Permisos de casas", dialog_share, "Cerrar", "");
		}
		case 1: //negocios
		{
			new count = 0, dialog_share[2056] = "{FFFFFF}", share_format[512], i = 0;
			Loop(id, totalnegocios, 1) if (InfoNegocio[id][nVenta] != 0 && InfoNegocio[id][nTipo] != 0)
			{
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoNegocio[id][nCompartida1], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoNegocio[id][nCompartida2], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoNegocio[id][nCompartida3], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (i == 3)
				{
					i = 0;
					strcat(dialog_share, "\n");
				}
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No le han dado permisos de ningún negocio.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Permisos de negocios", dialog_share, "Cerrar", "");
		}
		case 2: //vehículos
		{
			new dialog[3084], gformat[370], iCount = 0;
			strcat(dialog, "Modelo (ID)\tLocalización (Estado)\n");
			Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0)
			{
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoVehiculo[veh][vCompartida1], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					iCount++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoVehiculo[veh][vCompartida2], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					iCount++;
				}
				if (strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoVehiculo[veh][vCompartida3], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					iCount++;
				}
			}
			if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No le han dado permisos de ningún vehículo.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, "Permisos de vehículos", dialog, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:MenuAdmins(playerid, response, listitem, inputtext[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (InfoCuenta[playerid][jEncStaff] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de E.S");
	if (!response) return 1;
	new ID = listitem, gformat[128], nombre_miembro[32];
	format(gformat, sizeof gformat, "Miembro_List%d", ID);
	GetPVarString(playerid, gformat, nombre_miembro, sizeof nombre_miembro);
	SetPVarString(playerid, "Miembro_Actual", nombre_miembro);
	format(gformat, sizeof gformat, "Miembro: {FE9A2E}%s", nombre_miembro);
	Dialog_Show(playerid, OpcionAdmins, DIALOG_STYLE_LIST, gformat, "Dar rango\nÚltima conexión\n{B00000}Expulsar de la administración", "Continuar", "Volver");
	return 1;
}

Dialog:OpcionAdmins(playerid, response, listitem, inputtext[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (!response) return pc_cmd_listaadmins(playerid);
	new nombre_miembro[32], newid = -1, string[320], ultimaconexion[256];
	GetPVarString(playerid, "Miembro_Actual", nombre_miembro, sizeof nombre_miembro);
	//fix 22/04/2020
	foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoCuenta[juegador][jNombre], nombre_miembro, true)) { newid = juegador; }
 	//fix 22/04/2020
	if (VerificarCuenta(nombre_miembro))
	{
		rebel_string(0, "UltimaConexion", ultimaconexion, 256);
	}
	else return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta no existe.");
	switch (listitem)
	{
		case 0: //dar rango admin
		{
			new dialog[254], titulo[64];
			strcat(dialog, "Support\n");
			strcat(dialog, "Moderator\n");
			strcat(dialog, "Administrator\n");
			strcat(dialog, "Game Operator\n");
			format(titulo, sizeof titulo, "Admin: {FE9A2E}%s", nombre_miembro);
			Dialog_Show(playerid, DarAdminRango, DIALOG_STYLE_LIST, titulo, dialog, "Continuar", "Salir");
		}
		case 1: //última conexión
		{
			if (IsPlayerConnectedEx(newid))
			{
				format(string, sizeof string, "%s está conectado ID: %d", nombre_miembro, newid);
				SendPlayerChatMessage(playerid, COLOR_GREEN, string);
				return 1;
			}
			format(string, sizeof string, "%s: %s", nombre_miembro, ultimaconexion);
			SendPlayerChatMessage(playerid, COLOR_PURPLE, string);
		}
		case 2: //expulsar de la facción
		{
			//leer nombre rango
			if (!strcmp(nombre_miembro, "Altyn", true))
			{
				SendPlayerChatMessage(playerid, COLOR_RED, "No intentes expulsar a Altyn, podrías ser exiliado.");
				return 1;
			}
			else if (!strcmp(nombre_miembro, "VanNet", true))
			{
				SendPlayerChatMessage(playerid, COLOR_RED, "No intentes expulsar a VanNet, podrías ser exiliado.");
				return 1;
			}
			if (IsPlayerConnectedEx(newid))
			{
				if (playerid == newid) return SendPlayerChatMessage(playerid, COLOR_GREY, "No te puedes expulsar de la administración.");
				InfoCuenta[newid][jAdmin] = 0;
				InfoCuenta[newid][jEncFac] = 0;
				InfoCuenta[newid][jEncMap] = 0;
				papilla[newid] = 0;
				SetPlayerColor(newid, 0xFFFFFF00);
				GivePlayerSkin(newid, 155);
			}
			format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) expulsó de la administración a %s.", InfoCuenta[playerid][jNombre], playerid, nombre_miembro);
			SendAdminMessage(0xFFFFFFFF, string);
			mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET JotoOtaku = 0, EncFac = 0, EncMap = 0 WHERE Nombre = '%e'", nombre_miembro);
			mysql_tquery(db_samp, string);
		}
	}
	return 1;
}

Dialog:DarAdminRango(playerid, response, listitem, inputtext[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (!response) return 1;
	new nombre_miembro[32], newid = -1, string[256], rango = listitem+1;
	GetPVarString(playerid, "Miembro_Actual", nombre_miembro, sizeof nombre_miembro);
	//fix 22/04/2020
	foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoCuenta[juegador][jNombre], nombre_miembro, true)) { newid = juegador; }
	//fix 22/04/2020
	if (IsPlayerConnectedEx(newid)) InfoCuenta[newid][jAdmin] = rango;
	new isname[32];
	switch (rango)
	{
		case 1: alm(isname, "Support");
		case 2: alm(isname, "Moderator");
		case 3: alm(isname, "Administrator");
		case 4: alm(isname, "Game Operator");
	}
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado %s(%d) a %s.", InfoCuenta[playerid][jNombre], playerid, isname, rango, nombre_miembro);
	SendAdminMessage(0xFFFFFFFF, string);

	mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET JotoOtaku = '%d' WHERE Nombre = '%e'", rango, nombre_miembro);
	mysql_tquery(db_samp, string);
	return 1;
}