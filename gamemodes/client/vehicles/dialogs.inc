Dialog:PanelVehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: //Cinturon
		{
			if(!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas en un vehiculo.");
			new string[50 + MAX_PLAYER_NAME];
			if(IsPlayerInAnyVehicle(playerid) == 1 && Seatbelt[playerid] == 0){
				Seatbelt[playerid] = 1;
				if(IsABike(GetPlayerVehicleID(playerid))){format(string, sizeof string, "* {player:%d} agarra su casco, y se lo pone.", playerid);}
				else { format(string, sizeof string, "* {player:%d} pone las manos en su cinturon y se lo pone.", playerid); }
			}
			else if(IsPlayerInAnyVehicle(playerid) == 1 && Seatbelt[playerid] == 1){
				Seatbelt[playerid] = 0;
				if(IsABike(GetPlayerVehicleID(playerid))){format(string, sizeof string, "* {player:%d} pone las manos en su casco, y se lo quita.", playerid);}
				else { format(string, sizeof string, "* {player:%d} pone las manos en su cinturon y se lo quita.", playerid); }
			}
			ProxDetector(20.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
			RestorePlayerChat(playerid);
		}
		case 1: //Luces
		{
			if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
			new vehicleid = GetPlayerVehicleID(playerid);
			if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no tiene luces.");
			SetVehicleLights(vehicleid, playerid);
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		case 2: //Radio
		{
			if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new StationsDialog[1560];
				strcat(StationsDialog, "{fff400}Detener audio de musica\n");
				strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
				strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electronica{EBEBEB})\n");
				strcat(StationsDialog, "{FF0000}Agregar un url de internet .mp3");
				Dialog_Show(playerid, ConductorEstereo, DIALOG_STYLE_LIST, "Estereo", StationsDialog, "Continuar", "Salir");
			}	
		}
		case 3: //Ventanas
		{
			
		}
		case 4: //Intermitentes
		{

		}
		case 5: //Puertas
		{
			new Float: x, Float: y, Float: z;
			Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] != 0)
			{
				new vehicleid = InfoVehiculo[v][vIG_id];
				GetVehiclePos(vehicleid, x, y, z);
				if (IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z))
				{
					switch (InfoVehiculo[v][vTipo])
					{
						case 0: //usuarios
						{
							new access = 0;
							if (PermisosVehiculo(playerid, vehicleid) != -1) access = 1;
							if (access == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehiculo.");
							if (InfoVehiculo[v][vSeguro] == 0)
							{
								GameTextForPlayer(playerid,"~r~Vehiculo bloqueado!",5000,6);
								PlayerPlaySoundEx(1145, x, y, z);
								InfoVehiculo[v][vSeguro] = 1;
								LockPlayerVehicle(vehicleid);
							}
							else
							{
								GameTextForPlayer(playerid,"~g~Vehiculo desbloqueado!",5000,6);
								PlayerPlaySoundEx(1145, x, y, z);
								InfoVehiculo[v][vSeguro] = 0;
								UnLockPlayerVehicle(vehicleid);
							}
							guardar_int_mysql("vehiculos", "ConSeguro", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vSeguro]);
							return 1;
						}
						case 1..50: //facciones
						{
							if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehiculo de faccion.");
							if (InfoVehiculo[v][vSeguro] == 0)
							{
								GameTextForPlayer(playerid,"~r~Vehiculo bloqueado!",5000,6);
								PlayerPlaySoundEx(1145, x, y, z);
								InfoVehiculo[v][vSeguro] = 1;
								LockPlayerVehicle(vehicleid);
							}
							else
							{
								GameTextForPlayer(playerid,"~g~Vehiculo desbloqueado!",5000,6);
								PlayerPlaySoundEx(1145, x, y, z);
								InfoVehiculo[v][vSeguro] = 0;
								UnLockPlayerVehicle(vehicleid);
							}
							guardar_int_mysql("vehiculos", "ConSeguro", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vSeguro]);
							return 1;
						}
					}
				}
			}
			SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca de un vehiculo dinamico.");
		}
		case 6: //Capo
		{
			if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				if (EstaEnBicis(vehicleid) || IsAPlane(vehicleid) || IsABike(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no tiene capo.");
				SetVehicleHood(vehicleid, playerid);
			}
			else
			{
				new Float: x, Float: y, Float: z;
				Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
				{
					GetVehiclePos(InfoVehiculo[id][vIG_id], x, y, z);
					if (IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
					{
						if (GetVehicleVirtualWorld(InfoVehiculo[id][vIG_id]) == GetPlayerVirtualWorld(playerid) && GetVehicleInterior2(InfoVehiculo[id][vIG_id]) == GetPlayerInterior(playerid))
						{
							if (EstaEnBicis(InfoVehiculo[id][vIG_id]) || IsAPlane(InfoVehiculo[id][vIG_id]) || IsABike(InfoVehiculo[id][vIG_id])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no tiene capo.");
							SetVehicleHood(InfoVehiculo[id][vIG_id], playerid);
							return 1;
						}
					}
				}
			}
		}
		case 7: //Maletero
		{
			new vehicleid = -1;
			if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				vehicleid = GetPlayerVehicleID(playerid);
			}
			else if (!IsPlayerInAnyVehicle(playerid))
			{
				new Float: x, Float: y, Float: z;
				Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
				{
					GetVehiclePos(InfoVehiculo[id][vIG_id], x, y, z);
					if (IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
					{
						if (GetVehicleVirtualWorld(InfoVehiculo[id][vIG_id]) == GetPlayerVirtualWorld(playerid) && GetVehicleInterior2(InfoVehiculo[id][vIG_id]) == GetPlayerInterior(playerid))
						{
							vehicleid = InfoVehiculo[id][vIG_id];
							break;
						}
					}
				}
			}
			if (vehicleid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se ha detectado ningun vehiculo cerca.");
			Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
			{
				if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no tiene maletero.");
				new access = 0;
				if (InfoVehiculo[id][vNegocio] != 0)
				{
					if (llaves_negocio(playerid, vehicleid) != 0) access = 1;
				}
				else if (InfoVehiculo[id][vTrabajo] != 0)
				{
					if (llaves_trabajo(playerid, vehicleid) != 0) access = 1;
				}
				else
				{
					switch (InfoVehiculo[id][vTipo])
					{
						case 1..50: //facciones
						{
							if (llaves_faccion(playerid, vehicleid) != 0) access = 1;
						}
						case 200: //vip
						{
							if (llaves_vip(playerid, vehicleid) != 0) access = 1;
						}
						case 600: //rentable
						{
							if (llaves_renta(playerid, vehicleid) != 0) access = 1;
						}
						default: //usuarios
						{
							if (PermisosVehiculo(playerid, vehicleid) != -1) access = 1;
						}
					}
				}
				if (access == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehiculo o no hay permisos para abrirlo.");
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				if (InfoVehiculo[id][vMaleteroOn] != 0)
				{
					InfoVehiculo[id][vMaleteroOn] = 0;
					SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_OFF, objective);
					SendPlayerChatMessage(playerid, COLOR_LIGHTRED, "Maletero del vehiculo fue cerrado.");
				}
				else
				{
					InfoVehiculo[id][vMaleteroOn] = 1;
					SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, VEHICLE_PARAMS_ON, objective);
					SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Maletero del vehiculo fue abierto.");
				}
				return 1;
			}
			SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca del maletero de un vehiculo dinamico.");
		}
	}
	return 1;
}
Dialog:MaleteroMenu(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new i = listitem, slot = InfoVehiculo[PlayerMaleteroVeh[playerid]][vMaxMaletero];
	if(i == slot) return 1; //Selecciona la barra separadora
	if(i >= 0 && i <= slot) SacarMaletero(playerid, PlayerMaleteroVeh[playerid], i); //Selecciona un bolsillo
	if(i == 1+slot) GuardarMaletero(playerid, PlayerMaleteroVeh[playerid], 1); //Selecciona mano derecha
	if(i == 2+slot) GuardarMaletero(playerid, PlayerMaleteroVeh[playerid], 2); //Selecciona mano izquierda
    return 1;
}
Dialog:ConductorEstereo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar ninguna opcion si no eres el conductor.");
	switch (listitem)
	{
		case 0:
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			foreach(new playerid2: Player) if (IsPlayerConnectedEx(playerid2) && GetPlayerVehicleID(playerid2) == vehicleid)
			{
				if (TipoAudio[playerid2] == 3 && InfoPersonaje[playerid][pTogMusic] == 1)
				{
					TipoAudio[playerid2] = 0;
					StopAudioStreamForPlayer(playerid2);
				}
				alm(veh_music[vehicleid], "nadauwu");
			}
		}
		case 1: EstereoConductor(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1652147");
		case 2: EstereoConductor(playerid, "http://148.251.91.15:7004");
		case 3: EstereoConductor(playerid, "http://173.244.215.163:8380");
		case 4: EstereoConductor(playerid, "http://64.202.98.133:2010");
		case 5: EstereoConductor(playerid, "http://50.117.115.211:80");
		case 6: EstereoConductor(playerid, "http://108.61.30.179:4010");
		case 7: EstereoConductor(playerid, "http://50.7.64.226:80/frisky_mp3_hi");
		case 8: EstereoConductor(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1747543");
		case 9: EstereoConductor(playerid, "http://62.210.209.179:8030/stream");
		case 10: EstereoConductor(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1316323");
		case 11: EstereoConductor(playerid, "http://somafm.com/tags.pls");
		case 12: EstereoConductor(playerid, "http://listen.shoutcast.com:80/RadioHunter-TheHitzChannel");
		case 13: Dialog_Show(playerid, Conductor2Estereo, DIALOG_STYLE_INPUT, "URL internet", "{EBEBEB}Inserta un Stream ({3E62F4}www.offliberty.com{EBEBEB}) para reproducirlo", "Continuar", "Volver");
	}
	return 1;
}

Dialog:Conductor2Estereo(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		new StationsDialog[1560];
		strcat(StationsDialog, "{fff400}Detener audio de musica\n");
		strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electronica{EBEBEB})\n");
		strcat(StationsDialog, "{FF0000}Agregar un url de internet .mp3");
		Dialog_Show(playerid, ConductorEstereo, DIALOG_STYLE_LIST, "Estereo", StationsDialog, "Continuar", "Salir");
		return 1;
	}
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar ninguna opcion si no eres el conductor.");
	if (isnull(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has introducido ningun URL.");
	EstereoConductor(playerid, inputtext);
	return 1;
}

new id_vehshare_actual[MAX_PLAYERS];

Dialog:Menu_2Vehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40], show_dialog[512];
	format(gformat, sizeof gformat, "keyvehowo%d", ID);
	new veh = GetPVarInt(playerid, gformat);
	if (InfoVehiculo[veh][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[veh][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	id_vehshare_actual[playerid] = veh;
	if (InfoVehiculo[veh][vSpawned] != 0) format(show_dialog, sizeof show_dialog, "Ocultar {0073E6}%s{FFFFFF}\nLocalizar en radar\nVer informacion\nVer maletero", GetNameVehicle(InfoVehiculo[veh][vModelo]));
	else format(show_dialog, sizeof show_dialog, "Mostrar {0073E6}%s{FFFFFF}\nLocalizar en radar\nVer informacion\nVer maletero", GetNameVehicle(InfoVehiculo[veh][vModelo]));
	Dialog_Show(playerid, Menu2_2Vehiculo, DIALOG_STYLE_LIST, "Menu del vehiculo", show_dialog, "Continuar", "Salir");
	return 1;
}

Dialog:Show_2SpawnVeh(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = id_vehshare_actual[playerid];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (listitem)
	{
		case 0: MostrarVehiculo(id, 1), SendClientMessageEx(playerid, COLOR_GREEN, "Sacaste el vehiculo %s de %s en su ultima posicion.", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vPropietario]);
		case 1: MostrarVehiculo(id, 2), SendClientMessageEx(playerid, COLOR_GREEN, "Sacaste el vehiculo %s de %s en donde se aparco.", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vPropietario]);
	}
	return 1;
}

Dialog:Menu2_2Vehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_llaves(playerid);
	new id = id_vehshare_actual[playerid], string[235], dialog[1428];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (listitem)
	{
		case 0: //spawn-unspawn
		{
			if (InfoVehiculo[id][vSpawned] != 0) //ocultar
			{
				new Float: vx, Float: vy, Float: vz;
				GetVehiclePos(InfoVehiculo[id][vIG_id], vx, vy, vz);
				if (!IsPlayerInRangeOfPoint(playerid, 12, vx, vy, vz)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar en un rango de 12 metros de tu vehiculo para ocultarlo.");
				new dueno;
				sscanf(InfoVehiculo[id][vPropietario], "u", dueno);
				if (IsPlayerConnectedEx(dueno))
				{
					SendClientMessageEx(playerid, COLOR_GREY, "* No puedes ocultar este vehiculo si el propietario esta conectado. (ID %d)", dueno);
					return 1;
				}
				if (IsVehicleBusy(InfoVehiculo[id][vIG_id])) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes ocultar el vehiculo si posee ocupantes.");
				Quit_Vehicles(id);
				SendClientMessageEx(playerid, COLOR_YELLOW, "Has ocultado el vehiculo %s de %s.", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vPropietario]);
			}
			else
			{
				if (InfoVehiculo[id][vEndPosicionX] != 0) Dialog_Show(playerid, Show_2SpawnVeh, DIALOG_STYLE_LIST, "Lugar de mostrar", "Ultima posicion\nSitio de aparcado", "Continuar", "Inicio");
				else { MostrarVehiculo(id, 2), SendClientMessageEx(playerid, COLOR_GREEN, "Sacaste el vehiculo %s de %s en donde se aparco.", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vPropietario]); }
			}
		}
		case 1: //localizar
		{
			if (InfoVehiculo[id][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste esta oculto.");
			new vehicleid = InfoVehiculo[id][vIG_id], Float: carPos[3], zone[MAX_ZONE_NAME];
			GetVehiclePos(vehicleid, carPos[0], carPos[1], carPos[2]);
			GetCar3DZone(vehicleid, zone, sizeof zone);
			SendClientMessageEx(playerid, 0x0073E6FF, "El vehiculo %s fue marcado en el radar. (%s)", GetNameVehicle(InfoVehiculo[id][vModelo]), zone);
			SetPlayerCheckpoint(playerid, carPos[0], carPos[1], carPos[2], 10.0);
			PlayerPlaySound(playerid, 1138, 0, 0, 0);
			SetPVarInt(playerid, "TrackCar", 1);
		}
		case 2: //informacion
		{
			format(string, sizeof string, "{FFFFFF}Modelo: {F5DEB3}%s {FFFFFF}({0073E6}%d{FFFFFF})\n", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vModelo]); strcat(dialog, string);
			format(string, sizeof string, "{FFFFFF}Propietario: {F5DEB3}%s\n", InfoVehiculo[id][vPropietario]); strcat(dialog, string);
			if (InfoVehiculo[id][vSpawned] != 0) format(string, sizeof string, "{FFFFFF}Gasolina: {F5DEB3}%d\n", veh_gasolina[InfoVehiculo[id][vIG_id]]), strcat(dialog, string);
			else format(string, sizeof string, "{FFFFFF}Gasolina: {F5DEB3}%d\n", InfoVehiculo[id][vGasolina]), strcat(dialog, string);
			format(string, sizeof string, "{FFFFFF}Valor: {00B000}$%s\n", diner_coma(InfoVehiculo[id][vPrecio])); strcat(dialog, string);
			if (InfoVehiculo[id][vMulta] != 0) { format(string, sizeof string, "{FFFFFF}Multas: {D70000}$%s\n", diner_coma(InfoVehiculo[id][vMulta])); strcat(dialog, string); }
			format(string, sizeof string, "{FFFFFF}Slots maletero: {F5DEB3}%d\n", InfoVehiculo[id][vMaxMaletero]); strcat(dialog, string);
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Informacion del vehiculo", dialog, "Cerrar", "");
		}
		case 3: //maletero
		{
			new count = 0;
			Loop(x, 10, 0) if (InfoVehiculo[id][vMaletero][x] != 0)
			{
				count++;
				format(string, sizeof string, "#%d %s", x+1, slot_objeto(InfoVehiculo[id][vMaletero][x], InfoVehiculo[id][vMaleteroCant][x]));
				SendPlayerChatMessage(playerid, COLOR_WHITE, string);
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nada en el maletero.");
			SendPlayerChatMessage(playerid, -1, "Recuerda que los comandos de maletero son: {3E62F4}/gmaletero {FFFFFF}-{3E62F4} /smaletero");
		}
	}
	return 1;
}

Dialog:ShowCreateVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new gformat[250], modelid = actual_vehModel[playerid], color1 = actual_vehColor1[playerid], color2 = actual_vehColor2[playerid];
	switch (listitem)
	{
		case 0: //facciones
		{
			new gformat3[320], dialog[2048] = "#ID\tNombre\n", count = 0;
			Loop(id, totalfacciones, 1) if (InfoFaccion[id][fTipo] != 0)
			{
				format(gformat3, sizeof gformat3, "{EBEBEB}%d\t%s\n", id, InfoFaccion[id][fNombre]);
				strcat(dialog, gformat3);
				//conteo
				new gformat2[64];
				format(gformat2, sizeof gformat2, "VehIDcreate%d", count);
				SetPVarInt(playerid, gformat2, id);
				count++;
			}
			Dialog_Show(playerid, ShowCreateFacVehicle, DIALOG_STYLE_TABLIST_HEADERS, "Facciones", dialog, "Continuar", "Salir");
		}
		case 1: //vip
		{
			new Float: X, Float: Y, Float: Z, Float: Angle;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, Angle);
			crear_vehiculo(-1, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 10, 200, -1, -1);
			format(gformat, sizeof gformat, "Creaste un %s (%d) (Color1: %d) (Color2: %d) para los usuarios VIP, recuerda /estacionar.", GetNameVehicle(modelid), modelid, color1, color2);
			SendPlayerChatMessage(playerid, 0xA2DC35FF, gformat);
			format(gformat, sizeof gformat, "[VIP] %d creo un %s (%d) (Color1: %d) (Color2: %d)", NombreDeCuenta(playerid), GetNameVehicle(modelid), modelid, color1, color2);
			Log("f_logs/CrearVehiculo.log", gformat);
		}
		case 2: //renta
		{
			new Float: X, Float: Y, Float: Z, Float: Angle;
			GetPlayerPos(playerid, X, Y, Z);
			GetPlayerFacingAngle(playerid, Angle);
			crear_vehiculo(-1, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 6, 600, -1, -1);
			format(gformat, sizeof gformat, "Creaste un %s (%d) (Color1: %d) (Color2: %d) para rentar, recuerda /estacionar.", GetNameVehicle(modelid), modelid, color1, color2);
			SendPlayerChatMessage(playerid, 0xA2DC35FF, gformat);
			format(gformat, sizeof gformat, "[RENTA] %d creo un %s (%d) (Color1: %d) (Color2: %d)", NombreDeCuenta(playerid), GetNameVehicle(modelid), modelid, color1, color2);
			Log("f_logs/CrearVehiculo.log", gformat);
		}
		case 3: //negocio/empresa
		{
			Dialog_Show(playerid, ShowCreateNegVehicle, DIALOG_STYLE_INPUT, "Negocio:", "{EBEBEB}Introduce el {00CC00}ID{EBEBEB} del negocio:", "Continuar", "Salir");
		}
		case 4: //trabajo
		{
			Dialog_Show(playerid, ShowCreateJobVehicle, DIALOG_STYLE_INPUT, "Trabajo:", "{EBEBEB}Introduce el {00CC00}ID{EBEBEB} del trabajo:", "Continuar", "Salir");
		}
	}
	return 1;
}

Dialog:ShowCreateNegVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo numeros porfavor, vuelve a intentarlo.");
	new negocio = strval(inputtext);
	if (negocio < 1 || negocio >= totalnegocios) return SendPlayerChatMessage(playerid, COLOR_GREY, "* ID de negocio invalida.");
	if (InfoNegocio[negocio][nTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Esa ID esta vaci­a.");

	new gformat[250], modelid = actual_vehModel[playerid], color1 = actual_vehColor1[playerid], color2 = actual_vehColor2[playerid];
	new Float: X, Float: Y, Float: Z, Float: Angle;
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, Angle);
	crear_vehiculo(-1, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 10, 0, negocio, -1);
	format(gformat, sizeof gformat, "Creaste un %s (%d) (Color1: %d) (Color2: %d) para el negocio %s, recuerda /estacionar.", GetNameVehicle(modelid), modelid, color1, color2, InfoNegocio[negocio][nNombre]);
	SendPlayerChatMessage(playerid, 0xA2DC35FF, gformat);
	format(gformat, sizeof gformat, "[NEGOCIO: %d] %d creo un %s (%d) (Color1: %d) (Color2: %d)", negocio, NombreDeCuenta(playerid), GetNameVehicle(modelid), modelid, color1, color2);
	Log("f_logs/CrearVehiculo.log", gformat);
	return 1;
}

Dialog:ShowCreateJobVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo numeros porfavor, vuelve a intentarlo.");
	new trabajo = strval(inputtext);
	if (trabajo < 1 || trabajo > 7) return SendPlayerChatMessage(playerid, COLOR_GREY, "* ID de trabajo invalida.");

	new gformat[250], modelid = actual_vehModel[playerid], color1 = actual_vehColor1[playerid], color2 = actual_vehColor2[playerid];
	new Float: X, Float: Y, Float: Z, Float: Angle;
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, Angle);
	crear_vehiculo(-1, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 10, 0, -1, trabajo);
	format(gformat, sizeof gformat, "Creaste un %s (%d) (Color1: %d) (Color2: %d) para el trabajo %s, recuerda /estacionar.", GetNameVehicle(modelid), modelid, color1, color2, GetNameContrato(trabajo));
	SendPlayerChatMessage(playerid, 0xA2DC35FF, gformat);
	format(gformat, sizeof gformat, "[TRABAJO: %d] %d creo un %s (%d) (Color1: %d) (Color2: %d)", trabajo, NombreDeCuenta(playerid), GetNameVehicle(modelid), modelid, color1, color2);
	Log("f_logs/CrearVehiculo.log", gformat);
	return 1;
}
Dialog:ShowCreateFacVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat2[64];
	format(gformat2, sizeof gformat2, "VehIDcreate%d", ID);
	new faccion = GetPVarInt(playerid, gformat2);
	if (CountVehs(faccion) >= 80) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes crear mas de 80 vehiculos para esta faccion.");
	new gformat[250], modelid = actual_vehModel[playerid], color1 = actual_vehColor1[playerid], color2 = actual_vehColor2[playerid];
	new Float: X, Float: Y, Float: Z, Float: Angle;
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, Angle);
	crear_vehiculo(-1, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 10, faccion, -1, -1);
	format(gformat, sizeof gformat, "Creaste un %s (%d) (Color1: %d) (Color2: %d) para %s, recuerda /estacionar.", GetNameVehicle(modelid), modelid, color1, color2, InfoFaccion[faccion][fLogo]);
	SendPlayerChatMessage(playerid, 0xA2DC35FF, gformat);
	format(gformat, sizeof gformat, "[FACCIi“N: %s] %d creo un %s (%d) (Color1: %d) (Color2: %d)", InfoFaccion[faccion][fLogo], NombreDeCuenta(playerid), GetNameVehicle(modelid), modelid, color1, color2);
	Log("f_logs/CrearVehiculo.log", gformat);
	return 1;
}

Dialog:ShowMultas(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat2[40], gformat[256];
	format(gformat2, sizeof gformat2, "multevehuwu%d", ID);
	new veh = GetPVarInt(playerid, gformat2);
	if (InfoVehiculo[veh][vModelo] == 0) return SendPlayerChatMessage(playerid, 0xEBEBEBFF, "vehiculo invalido (model 0). Si el error continua contacta con el programador.");

	if (InfoPersonaje[playerid][pEstrellas] != 0)
	{
		format(gformat, sizeof gformat, "[CENTRAL] %s intento pagar sus multas, esta en busqueda y captura. Estrellas: %d", GetNameFormat(playerid), InfoPersonaje[playerid][pEstrellas]);
		SendRadioMessage(1, COLOR_RADIO, gformat, 1);
		SendRadioMessage(2, COLOR_RADIO, gformat, 1);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "La polici­a viene en camino, hemos alertado a ellos dado que estas en ByC.");
		return 1;
	}
	if (InfoVehiculo[veh][vEmbargo])
	{
		new iCost = (InfoVehiculo[veh][vMulta]*2);
		new xspawn = random(sizeof point_embargo);
		if (GetPlayerCash(playerid) < iCost)
		{
			format(gformat, sizeof gformat, "Te faltan $%s para pagar la liberacion de tu vehiculo.", diner_coma(iCost-GetPlayerCash(playerid)));
			SendPlayerChatMessage(playerid, COLOR_GRAD2, gformat);
			return 1;
		}
		format(gformat, sizeof gformat, "Liberaste tu %s por $%s.", VehicleName[InfoVehiculo[veh][vModelo] - 400], diner_coma(iCost));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
		SendPlayerChatMessage(playerid, 0xA2DC35FF, "[INFO]:{FFFFFF} Tu auto se encuentra en el deposito municipal, contacta con un policia para que lo saque.");
		GivePlayerCash(playerid, -iCost, "pago embargo");
		Tax += iCost;
		InfoVehiculo[veh][vEmbargo] = 0; // Deposito.
		InfoVehiculo[veh][vMulta] = 0;
		InfoVehiculo[veh][vPosicionX] = point_embargo[xspawn][0];
		InfoVehiculo[veh][vPosicionY] = point_embargo[xspawn][1];
		InfoVehiculo[veh][vPosicionZ] = point_embargo[xspawn][2];
		InfoVehiculo[veh][vPosicionR] = point_embargo[xspawn][3];
		InfoVehiculo[veh][vInterior] = 0;
		InfoVehiculo[veh][vVirtualWorld] = 0;
		InfoVehiculo[veh][vEndPosicionX] = point_embargo[xspawn][0];
		InfoVehiculo[veh][vEndPosicionY] = point_embargo[xspawn][1];
		InfoVehiculo[veh][vEndPosicionZ] = point_embargo[xspawn][2];
		InfoVehiculo[veh][vEndPosicionR] = point_embargo[xspawn][3];
		InfoVehiculo[veh][vEndInterior] = 0;
		InfoVehiculo[veh][vEndVirtualWorld] = 0;
		new Coche = CreateVehicle(InfoVehiculo[veh][vModelo], InfoVehiculo[veh][vPosicionX], InfoVehiculo[veh][vPosicionY], InfoVehiculo[veh][vPosicionZ], InfoVehiculo[veh][vPosicionR], InfoVehiculo[veh][vColor_1], InfoVehiculo[veh][vColor_2], -1, InfoVehiculo[veh][vSirena]);
        InfoVehiculo[veh][vIG_id] = Coche;
        InfoVehiculo[veh][vSpawned] = 1;
		InfoVehiculo[veh][vTimeSave] = 0;
		SetVehicleInterior(Coche, InfoVehiculo[veh][vInterior]);
		SetVehicleExVirtualWorld(Coche, InfoVehiculo[veh][vVirtualWorld]);
		SetVehicleMatricula(Coche);
		if (InfoVehiculo[veh][vModelo] == 528 || InfoVehiculo[veh][vModelo] == 427) SetVehicleHealth(Coche, 5000.0);
		else SetVehicleHealth(Coche, InfoVehiculo[veh][vVida]);
		UpdateVehicleDamageStatus(Coche, InfoVehiculo[veh][vDanioSuperficie], InfoVehiculo[veh][vDanioPuertas], InfoVehiculo[veh][vDanioLuces], InfoVehiculo[veh][vDanioRuedas]);
		veh_gasolina[Coche] = InfoVehiculo[veh][vGasolina];
		if (InfoVehiculo[veh][vSeguro] != 0) LockPlayerVehicle(Coche);
		Load_Mods(veh);
		if (!isnull(InfoVehiculo[veh][vCallSign]))
		{
			if (IsValidDynamic3DTextLabel(InfoVehiculo[veh][vOnCallSign]))
			{
				DestroyDynamic3DTextLabel(InfoVehiculo[veh][vOnCallSign]);
				InfoVehiculo[veh][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
			}
			InfoVehiculo[veh][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[veh][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, Coche);
		}
		new query[512];
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET Posicion_X = '%f', Posicion_Y = '%f', Posicion_Z = '%f', Posicion_R = '%f', Interior = 0, VirtualWorld = 0, Multa = 0, Embargo = 0 WHERE ID = '%d'", InfoVehiculo[veh][vPosicionX], InfoVehiculo[veh][vPosicionY], InfoVehiculo[veh][vPosicionZ], InfoVehiculo[veh][vPosicionR], InfoVehiculo[veh][vID_sql]);
		mysql_tquery(db_samp, query);
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET End_Posicion_X = '%f', End_Posicion_Y = '%f', End_Posicion_Z = '%f', End_Posicion_R = '%f', End_Interior = 0, End_VirtualWorld = 0 WHERE ID = '%d'", InfoVehiculo[veh][vEndPosicionX], InfoVehiculo[veh][vEndPosicionY], InfoVehiculo[veh][vEndPosicionZ], InfoVehiculo[veh][vEndPosicionR], InfoVehiculo[veh][vID_sql]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	if (InfoVehiculo[veh][vMulta])
	{
		new iCost = InfoVehiculo[veh][vMulta];
		if (GetPlayerCash(playerid) < iCost)
		{
			format(gformat, sizeof gformat, "Te faltan $%s para pagar la multa de tu vehiculo.", diner_coma(iCost-GetPlayerCash(playerid)));
			SendPlayerChatMessage(playerid, COLOR_GRAD2, gformat);
			return 1;
		}
		GivePlayerCash(playerid, -iCost, "pago multa");
		Tax += iCost;
		format(gformat, sizeof gformat, "Pagaste la multa de $%s de tu %s.", diner_coma(iCost), VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		SendPlayerChatMessage(playerid, COLOR_GRAD2, gformat);
		InfoVehiculo[veh][vMulta] = 0;
		guardar_int_mysql("vehiculos", "Multa", InfoVehiculo[veh][vID_sql], 0);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GRAD2, "Ese vehiculo no necesita ser liberado o tiene multas a pagar.");
	return 1;
}

Dialog:MenuVehiculos(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40], show_dialog[512];
	format(gformat, sizeof gformat, "keyvehowo%d", ID);
	new veh = GetPVarInt(playerid, gformat);
	if (InfoVehiculo[veh][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[veh][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	id_veh_actual[playerid] = veh;
	if (InfoVehiculo[veh][vSpawned] != 0) format(show_dialog, sizeof show_dialog, "Ocultar {0073E6}%s{FFFFFF}\nLocalizar en radar\nVer informacion\nVer maletero\nDesmantelar vehiculo\nPermisos de vehiculo", GetNameVehicle(InfoVehiculo[veh][vModelo]));
	else format(show_dialog, sizeof show_dialog, "Mostrar {0073E6}%s{FFFFFF}\nLocalizar en radar\nVer informacion\nVer maletero\nDesmantelar vehiculo\nPermisos de vehiculo", GetNameVehicle(InfoVehiculo[veh][vModelo]));
	Dialog_Show(playerid, Menu2Vehiculos, DIALOG_STYLE_LIST, "Menu del vehiculo", show_dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Menu2Vehiculos(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_llaves(playerid);
	new id = id_veh_actual[playerid], string[235], dialog[1428];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (listitem)
	{
		case 0: //spawn-unspawn
		{
			if (InfoVehiculo[id][vSpawned] != 0) //ocultar
			{
				new Float: vx, Float: vy, Float: vz;
				GetVehiclePos(InfoVehiculo[id][vIG_id], vx, vy, vz);
				if (!IsPlayerInRangeOfPoint(playerid, 12, vx, vy, vz)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar en un rango de 12 metros de tu vehiculo para ocultarlo.");
				if (IsVehicleBusy(InfoVehiculo[id][vIG_id])) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes ocultar el vehiculo si posee ocupantes.");
				Quit_Vehicles(id);
				SendClientMessageEx(playerid, COLOR_YELLOW, "Has ocultado tu %s.", GetNameVehicle(InfoVehiculo[id][vModelo]));
			}
			else
			{
				if (SpawnVehiculos(playerid) == 1) return 1;
				if (InfoVehiculo[id][vEndPosicionX] != 0) Dialog_Show(playerid, ShowSpawnVeh, DIALOG_STYLE_LIST, "Lugar de mostrar", "ultima posicion\nSitio de aparcado", "Continuar", "Inicio");
				else { MostrarVehiculo(id, 2), SendClientMessageEx(playerid, COLOR_GREEN, "Has sacado tu %s en donde lo aparcaste.", GetNameVehicle(InfoVehiculo[id][vModelo])); }
			}
		}
		case 1: //localizar
		{
			if (InfoVehiculo[id][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste esta oculto.");
			new vehicleid = InfoVehiculo[id][vIG_id], Float: carPos[3], zone[MAX_ZONE_NAME];
			GetVehiclePos(vehicleid, carPos[0], carPos[1], carPos[2]);
			GetCar3DZone(vehicleid, zone, sizeof zone);
			SendClientMessageEx(playerid, 0x0073E6FF, "Tu %s fue marcado en el radar. (%s)", GetNameVehicle(InfoVehiculo[id][vModelo]), zone);
			SetPlayerCheckpoint(playerid, carPos[0], carPos[1], carPos[2], 10.0);
			PlayerPlaySound(playerid, 1138, 0, 0, 0);
			SetPVarInt(playerid, "TrackCar", 1);
		}
		case 2: //informacion
		{
			format(string, sizeof string, "{FFFFFF}Modelo: {F5DEB3}%s {FFFFFF}({0073E6}%d{FFFFFF})\n", GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vModelo]); strcat(dialog, string);
			format(string, sizeof string, "{FFFFFF}Propietario: {F5DEB3}%s\n", InfoVehiculo[id][vPropietario]); strcat(dialog, string);
			if (InfoVehiculo[id][vSpawned] != 0) format(string, sizeof string, "{FFFFFF}Gasolina: {F5DEB3}%d\n", veh_gasolina[InfoVehiculo[id][vIG_id]]), strcat(dialog, string);
			else format(string, sizeof string, "{FFFFFF}Gasolina: {F5DEB3}%d\n", InfoVehiculo[id][vGasolina]), strcat(dialog, string);
			format(string, sizeof string, "{FFFFFF}Valor: {00B000}$%s\n", diner_coma(InfoVehiculo[id][vPrecio])); strcat(dialog, string);
			if (InfoVehiculo[id][vMulta] != 0) { format(string, sizeof string, "{FFFFFF}Multas: {D70000}$%s\n", diner_coma(InfoVehiculo[id][vMulta])); strcat(dialog, string); }
			format(string, sizeof string, "{FFFFFF}Slots maletero: {F5DEB3}%d\n", InfoVehiculo[id][vMaxMaletero]); strcat(dialog, string);
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Informacion del vehiculo", dialog, "Cerrar", "");
		}
		case 3: //maletero
		{
			new count = 0;
			Loop(x, 10, 0) if (InfoVehiculo[id][vMaletero][x] != 0)
			{
				count++;
				format(string, sizeof string, "#%d %s", x+1, slot_objeto(InfoVehiculo[id][vMaletero][x], InfoVehiculo[id][vMaleteroCant][x]));
				SendPlayerChatMessage(playerid, COLOR_WHITE, string);
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nada en el maletero.");
			SendPlayerChatMessage(playerid, -1, "Recuerda que los comandos de maletero son: {3E62F4}/gmaletero {FFFFFF}-{3E62F4} /smaletero");
		}
		case 4: //eliminar
		{
			if (InfoVehiculo[id][vPremium] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes eliminar vehiculos que compraste con monedas.");
			format(dialog, sizeof dialog, "{EBEBEB}El uso de esta opcion {9c2828}eliminara completamente{EBEBEB} tu {b42d2d}%s{EBEBEB} y no habra reembolso.\n\
			Si estas seguro de que quieres eliminar el vehiculo, por favor presiona {9c2828}continuar{EBEBEB}.\n", GetNameVehicle(InfoVehiculo[id][vModelo]));
			Dialog_Show(playerid, EliminarVehiculo, DIALOG_STYLE_MSGBOX, "Desmantelar vehiculo", dialog, "Continuar", "Inicio");
		}
		case 5: VehiculoShareShow(playerid);
	}
	return 1;
}

Dialog:ShowSpawnVeh(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_llaves(playerid);
	new id = id_veh_actual[playerid];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (listitem)
	{
		case 0: MostrarVehiculo(id, 1), SendClientMessageEx(playerid, COLOR_GREEN, "Has sacado tu %s en su ultima posicion.", GetNameVehicle(InfoVehiculo[id][vModelo]));
		case 1: MostrarVehiculo(id, 2), SendClientMessageEx(playerid, COLOR_GREEN, "Has sacado tu %s en donde lo aparcaste.", GetNameVehicle(InfoVehiculo[id][vModelo]));
	}
	return 1;
}

Dialog:EliminarVehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_llaves(playerid);
	new id = id_veh_actual[playerid];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	borrar_vehiculo(id);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Su vehiculo fue desmantelado con exito.");
	return 1;
}

VehiculoShareShow(playerid)
{
	new gformat[370], dialog_show[1028], id = id_veh_actual[playerid];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	//slot1
	if (strcmp(InfoVehiculo[id][vCompartida1], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 1\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 1:{59F37B} %s\n", InfoVehiculo[id][vCompartida1]);
		strcat(dialog_show, gformat);
	}
	//slot2
	if (strcmp(InfoVehiculo[id][vCompartida2], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 2\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 2:{59F37B} %s\n", InfoVehiculo[id][vCompartida2]);
		strcat(dialog_show, gformat);
	}
	//slot3
	if (strcmp(InfoVehiculo[id][vCompartida3], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 3\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 3:{59F37B} %s\n", InfoVehiculo[id][vCompartida3]);
		strcat(dialog_show, gformat);
	}
	//dialog preview
	Dialog_Show(playerid, CompartirVehiculo, DIALOG_STYLE_LIST, "Permisos de tu vehiculo", dialog_show, "Continuar", "Inicio");
	return 1;
}

new ShareVehiculo[MAX_PLAYERS];

Dialog:CompartirVehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_llaves(playerid);
	new gformat[370], n = id_veh_actual[playerid];
	if (InfoVehiculo[n][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[n][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (listitem)
	{
	    case 0: //slot1
	    {
			if (strcmp(InfoVehiculo[n][vCompartida1], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Vehiculo, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 1", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su vehiculo.", "Continuar", "Volver");
				ShareVehiculo[playerid] = 1;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}Â¿Deseas quitarle los permisos de tu %s a %s?\n", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida1]);
				Dialog_Show(playerid, Compartir3Vehiculo, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 1", gformat, "Si­", "Volver");
				ShareVehiculo[playerid] = 1;
			}
		}
	    case 1: //slot2
	    {
			if (strcmp(InfoVehiculo[n][vCompartida2], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Vehiculo, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 2", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su vehiculo.", "Continuar", "Volver");
				ShareVehiculo[playerid] = 2;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}Â¿Deseas quitarle los permisos de tu %s a %s?\n", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida2]);
				Dialog_Show(playerid, Compartir3Vehiculo, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 2", gformat, "Si­", "Volver");
				ShareVehiculo[playerid] = 2;
			}
		}
	    case 2: //slot3
	    {
			if (strcmp(InfoVehiculo[n][vCompartida3], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Vehiculo, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 3", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su vehiculo.", "Continuar", "Volver");
				ShareVehiculo[playerid] = 3;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}Â¿Deseas quitarle los permisos de tu %s a %s?\n", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida1]);
				Dialog_Show(playerid, Compartir3Vehiculo, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 3", gformat, "Si­", "Volver");
				ShareVehiculo[playerid] = 3;
			}
		}
	}
	return 1;
}

Dialog:Compartir2Vehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return VehiculoShareShow(playerid);
	new n = id_veh_actual[playerid];
	if (InfoVehiculo[n][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[n][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo puedes ingresar numeros, intenta de nuevo.");
	new playerid2 = strval(inputtext);
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes compartir permisos del vehiculo a ti mismo.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El jugador seleccionado no se encuentra conectado.");
	if (strmatch(InfoVehiculo[n][vCompartida1], InfoPersonaje[playerid2][pNombre_Apellido])) { SendClientMessageEx(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu %s, revisa slot 1.", GetNameVehicle(InfoVehiculo[n][vModelo])); return 1; }
	if (strmatch(InfoVehiculo[n][vCompartida2], InfoPersonaje[playerid2][pNombre_Apellido])) { SendClientMessageEx(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu %s, revisa slot 2.", GetNameVehicle(InfoVehiculo[n][vModelo])); return 1; }
	if (strmatch(InfoVehiculo[n][vCompartida3], InfoPersonaje[playerid2][pNombre_Apellido])) { SendClientMessageEx(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu %s, revisa slot 3.", GetNameVehicle(InfoVehiculo[n][vModelo])); return 1; }
	switch (ShareVehiculo[playerid])
	{
	    case 1: { alm(InfoVehiculo[n][vCompartida1], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("vehiculos", "Compartida1", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida1]); }
	    case 2: { alm(InfoVehiculo[n][vCompartida2], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("vehiculos", "Compartida2", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida2]); }
	    case 3: { alm(InfoVehiculo[n][vCompartida3], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("vehiculos", "Compartida3", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida3]); }
	}
	SendClientMessageEx(playerid2, 0x59F37BFF, "* %s te ha dado permisos de su %s.", NombreOriginal(playerid), GetNameVehicle(InfoVehiculo[n][vModelo]));
	SendClientMessageEx(playerid, 0x59F37BFF, "* Cediste permisos de tu %s con %s (slot %d).", GetNameVehicle(InfoVehiculo[n][vModelo]), NombreOriginal(playerid2), ShareVehiculo[playerid]);
	return 1;
}

Dialog:Compartir3Vehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return VehiculoShareShow(playerid);
	new n = id_veh_actual[playerid];
	if (InfoVehiculo[n][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste no posee un modelo.");
 	if (InfoVehiculo[n][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El vehiculo que seleccionaste se encuentra embargado.");
	switch (ShareVehiculo[playerid])
	{
	    case 1:
		{
			if (strmatch(InfoVehiculo[n][vCompartida1], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 1."); return 1; }
			new playerid2;
			sscanf(InfoVehiculo[n][vCompartida1], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removio los permisos de su .", NombreOriginal(playerid), GetNameVehicle(InfoVehiculo[n][vModelo]));
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu %s a %s. (slot 1)", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida1]);
			alm(InfoVehiculo[n][vCompartida1], "none");
			guardar_string_mysql("vehiculos", "Compartida1", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida1]);
		}
	    case 2:
		{
			if (strmatch(InfoVehiculo[n][vCompartida2], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 2."); return 1; }
			new playerid2;
			sscanf(InfoVehiculo[n][vCompartida2], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removio los permisos de su %s.", NombreOriginal(playerid), GetNameVehicle(InfoVehiculo[n][vModelo]));
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu %s a %s. (slot 2)", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida2]);
			alm(InfoVehiculo[n][vCompartida2], "none");
			guardar_string_mysql("vehiculos", "Compartida2", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida2]);
		}
	    case 3:
		{
			if (strmatch(InfoVehiculo[n][vCompartida3], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 3."); return 1; }
			new playerid2;
			sscanf(InfoVehiculo[n][vCompartida3], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removio los permisos de su %s.", NombreOriginal(playerid), GetNameVehicle(InfoVehiculo[n][vModelo]));
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu %s a %s. (slot 3)", GetNameVehicle(InfoVehiculo[n][vModelo]), InfoVehiculo[n][vCompartida3]);
			alm(InfoVehiculo[n][vCompartida3], "none");
			guardar_string_mysql("vehiculos", "Compartida3", InfoVehiculo[n][vID_sql], InfoVehiculo[n][vCompartida3]);
		}
	}
	return 1;
}

Dialog:GotoVehU(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40];
	format(gformat, sizeof gformat, "cehvehkey%d", ID);
	new veh = GetPVarInt(playerid, gformat);
	if (InfoVehiculo[veh][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Seleccionaste un slot vaci­o.");
	if (InfoVehiculo[veh][vEmbargo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "No se puede tpear a un vehiculo confiscado.");
	if (InfoVehiculo[veh][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese vehiculo esta oculto, no puedes ir a el.");
	new Float: carPos[3], vehicleid = InfoVehiculo[veh][vIG_id];
	GetVehiclePos(vehicleid, carPos[0], carPos[1], carPos[2]);
	SetPosEx(playerid, carPos[0], carPos[1], carPos[2], 0.0000, 0, GetVehicleVirtualWorld(vehicleid), 1);
	return 1;
}

Dialog:RespawnCategoria(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (listitem == 0)
	{
		new gformat[320], dialog[3048], iCount = 0;
		Loop(id, totalfacciones, 1) if (InfoFaccion[id][fTipo] != 0)
		{
			format(gformat, sizeof gformat, "{EBEBEB}%s ({589DA0}%d{EBEBEB})\n", InfoFaccion[id][fNombre], id);
			strcat(dialog, gformat);
			//conteo
			new gformat2[64];
			format(gformat2, sizeof gformat2, "countfacr%d", iCount);
			SetPVarInt(playerid, gformat2, id);
			iCount++;
		}
		Dialog_Show(playerid, RespawnFacciones, DIALOG_STYLE_LIST, "Facciones", dialog, "Continuar", "Volver");
		return 1;
	}
	new string[190], bool:unwanted[MAX_VEHICLES], count = 0, namecato[19];
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerInAnyVehicle(playerid2))
	{
		unwanted[GetPlayerVehicleID(playerid2)] = true;
	}
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
	{
		new vehicleid = InfoVehiculo[id][vIG_id];
		//vip
		if (!unwanted[vehicleid] && InfoVehiculo[id][vTipo] == 200 && listitem == 1)
		{
			SetVehicleToRespawn(vehicleid);
			SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
			arr_Engine{vehicleid} = 0;
			count++;
		}
		//negocios
		if (InfoVehiculo[id][vNegocio] != 0 && !unwanted[vehicleid] && listitem == 2)
		{
			SetVehicleToRespawn(vehicleid);
			SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
			arr_Engine{vehicleid} = 0;
			count++;
		}
		//trabajos
		if (InfoVehiculo[id][vTrabajo] != 0 && !unwanted[vehicleid] && listitem == 3)
		{
			SetVehicleToRespawn(vehicleid);
			SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
			arr_Engine{vehicleid} = 0;
			count++;
		}
		//rentables
		if (!unwanted[vehicleid] && InfoVehiculo[id][vTipo] == 600 && listitem == 4)
		{
			SetVehicleToRespawn(vehicleid);
			SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
			arr_Engine{vehicleid} = 0;
			count++;
		}
		//usuarios
		if (!unwanted[vehicleid] && InfoVehiculo[id][vTipo] == 0 && listitem == 5 && InfoVehiculo[id][vNegocio] == 0 && InfoVehiculo[id][vTrabajo] == 0)
		{
			SetVehicleToRespawn(vehicleid);
			SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
			arr_Engine{vehicleid} = 0;
			count++;
		}
	}
	switch (listitem)
	{
		case 1: alm(namecato, "vips");
		case 2: alm(namecato, "negocios");
		case 3: alm(namecato, "trabajos");
		case 4: alm(namecato, "rentables");
		case 5: alm(namecato, "usuarios");
	}
	format(string, sizeof string, "Se respawnearon %d vehiculos de la categoria '%s'.", count, namecato);
	SendPlayerChatMessage(playerid, 0x00AACCFF, string);
	return 1;
}

Dialog:RespawnFacciones(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40];
	format(gformat, sizeof gformat, "countfacr%d", ID);
	new faccion = GetPVarInt(playerid, gformat);
	new bool:unwanted[MAX_VEHICLES], string[170], count = 0;
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerInAnyVehicle(playerid2))
	{
		unwanted[GetPlayerVehicleID(playerid2)] = true;
	}
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
	{
		new vehicleid = InfoVehiculo[id][vIG_id];
		if (InfoVehiculo[id][vTipo] == faccion)
		{
			if (!unwanted[vehicleid])
			{
				SetVehicleToRespawn(vehicleid);
				SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
				arr_Engine{vehicleid} = 0;
				count++;
			}
		}
	}
	format(string, sizeof string, "Se respawnearon %d vehiculos de la faccion %d '%s'.", count, faccion, InfoFaccion[faccion][fNombre]);
	SendPlayerChatMessage(playerid, 0x00AACCFF, string);
	return 1;
}

Dialog:SellVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40];
	format(gformat, sizeof gformat, "sellvehkey%d", ID);
	new veh = GetPVarInt(playerid, gformat);
	if (InfoVehiculo[veh][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Seleccionaste un slot vaci­o.");
	if (InfoVehiculo[veh][vPremium] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes vender vehiculos que compraste con monedas.");
	if (InfoVehiculo[veh][vEmbargo]) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No se puede vender un vehiculo confiscado.");
	if (InfoVehiculo[veh][vPrecio] < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes vender vehiculos VIP o cedidos por la administracion.");
	new string[245], valor = InfoVehiculo[veh][vPrecio]/2;

	borrar_vehiculo(veh);
	format(string, sizeof string, "Gracias por la venta, el gobierno te ha pagado la mitad del vehiculo por el vehiculo. ($%s)", diner_coma(valor));
	SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	GivePlayerCash(playerid, valor, "sellvehicle");
	return 1;
}
Dialog:MenuFacVehiculos(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new xd = listitem, gformat[40], gtitulo[170];
	format(gformat, sizeof gformat, "RanuraVeh%d", xd);
	new id = GetPVarInt(playerid, gformat);
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Seleccionaste un slot vaci­o.");
	id_veh_actual[playerid] = id;
	format(gtitulo, sizeof gtitulo, "Opciones para {F5DEB3}%s", VehicleName[InfoVehiculo[id][vModelo] - 400]);
	Dialog_Show(playerid, Menu2FacVehiculos, DIALOG_STYLE_LIST, gtitulo, "{0073E6}-{FFFFFF} Localizar\n{0073E6}-{FFFFFF} Maletero", "Continuar", "Volver");
	return 1;
}

Dialog:Menu2FacVehiculos(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_fllaves(playerid);
	new id = id_veh_actual[playerid], string[235];
	if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Seleccionaste un slot vaci­o.");
	switch (listitem)
	{
		case 0: //localizar
		{
			new Float: carPos[3], zone[MAX_ZONE_NAME];
			GetVehiclePos(InfoVehiculo[id][vIG_id], carPos[0], carPos[1], carPos[2]);
			GetCar3DZone(InfoVehiculo[id][vIG_id], zone, sizeof(zone));
			format(string, sizeof string, "El vehiculo {F5DEB3}%s{FFFFFF} fue localizado en {00D500}%s{FFFFFF}. (Ve al checkpoint)", GetVehicleName(InfoVehiculo[id][vIG_id]), zone);
			SendPlayerChatMessage(playerid, COLOR_WHITE, string);
			SetPlayerCheckpoint(playerid, carPos[0], carPos[1], carPos[2], 15.0);
			PlayerPlaySound(playerid, 1138, 0, 0, 0);
			SetPVarInt(playerid, "TrackCar", 1);
		}
		case 1: //maletero
		{
			new count = 0;
			Loop(x, 10, 0) if (InfoVehiculo[id][vMaletero][x] != 0)
			{
				count++;
				format(string, sizeof string, "#%d %s", x+1, slot_objeto(InfoVehiculo[id][vMaletero][x], InfoVehiculo[id][vMaleteroCant][x]));
				SendPlayerChatMessage(playerid, COLOR_WHITE, string);
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nada en el maletero.");
			SendPlayerChatMessage(playerid, -1, "Recuerda que los comandos de maletero son: {3E62F4}/gmaletero {FFFFFF}-{3E62F4} /smaletero");
		}
	}
	return 1;
}
Dialog:ShowEstereo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!GetPVarType(playerid, "AreaVehPos")) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No has encendido ningun estereo de vehiculo.");
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, GetPVarFloat(playerid, "AreaVehPosX"), GetPVarFloat(playerid, "AreaVehPosY"), GetPVarFloat(playerid, "AreaVehPosZ"))) return	SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas cerca de tu vehiculo con estereo encendido.");
	switch (listitem)
	{
		case 0:
		{
			if (GetPVarType(playerid, "AreaVehMus"))
			{
				foreach(new i: Player) if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "AreaVehMus")))
				{
					PararMVeh(i);
				}
				DeletePVar(playerid, "AreaVehMus");
			}
			SendPlayerChatMessage(playerid, COLOR_RED, "Has detenido el audio de tu estereo.");
		}
		case 1:
		{
			new StationsDialog[1560];
			strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electronica{EBEBEB})");
			Dialog_Show(playerid, EmisorasEstereo, DIALOG_STYLE_LIST, "Radios", StationsDialog, "Continuar", "Volver");
		}
		case 2: Dialog_Show(playerid, UrlEstereo, DIALOG_STYLE_INPUT, "URL internet", "{EBEBEB}Inserta un Stream ({3E62F4}www.offliberty.com{EBEBEB}) para reproducirlo", "Continuar", "Volver");
		case 3:
		{
			DeletePVar(playerid, "AreaVehPos");
			DeletePVar(playerid, "AreaVehAud");
			DeletePVar(playerid, "AreaVehPosLabel");
			DeletePVar(playerid, "AreaVehPosX");
			DeletePVar(playerid, "AreaVehPosY");
			DeletePVar(playerid, "AreaVehPosZ");
			DeletePVar(playerid, "AreaVehPosInt");
			DeletePVar(playerid, "AreaVehPosVW");
			DeletePVar(playerid, "AreaVehID");
			if (GetPVarType(playerid, "AreaVehMus"))
			{
				foreach(new i: Player) if (IsPlayerInDynamicArea(i, GetPVarInt(playerid, "AreaVehMus")))
				{
					PararMVeh(i);
				}
				DeletePVar(playerid, "AreaVehMus");
			}
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Has apagado el estereo de tu vehiculo.");
		}
	}
	return 1;
}

Dialog:EmisorasEstereo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_menuestereo(playerid);
	switch (listitem)
	{
		case 0: ReproducirEstereo(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1652147");
		case 1: ReproducirEstereo(playerid, "http://148.251.91.15:7004");
		case 2: ReproducirEstereo(playerid, "http://173.244.215.163:8380");
		case 3: ReproducirEstereo(playerid, "http://64.202.98.133:2010");
		case 4: ReproducirEstereo(playerid, "http://50.117.115.211:80");
		case 5: ReproducirEstereo(playerid, "http://108.61.30.179:4010");
		case 6: ReproducirEstereo(playerid, "http://50.7.64.226:80/frisky_mp3_hi");
		case 7: ReproducirEstereo(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1747543");
		case 8: ReproducirEstereo(playerid, "http://62.210.209.179:8030/stream");
		case 9: ReproducirEstereo(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1316323");
		case 10: ReproducirEstereo(playerid, "http://somafm.com/tags.pls");
		case 11: ReproducirEstereo(playerid, "http://listen.shoutcast.com:80/RadioHunter-TheHitzChannel");
	}
	return 1;
}

Dialog:UrlEstereo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_menuestereo(playerid);
	if (isnull(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has introducido ningun URL.");
	ReproducirEstereo(playerid, inputtext);
	return 1;
}