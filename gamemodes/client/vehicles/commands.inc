//Jugadores
cmd:panelv(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid)) return 1;
	Dialog_Show(playerid, PanelVehiculo, DIALOG_STYLE_LIST, " ",
	"1. Cinturón\n\
	2. Luces\n\
	3. Radio\n\
	4. Ventana\n\
	5. Intermitentes\n\
	6. Puertas\n\
	7. Capó\n\
	8. Maletero",
	"Continuar", "Cerrar");
	return 1;
}

cmd:vehid(playerid)
{
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estás en un vehiculo");
	new string[32];
	format(string, sizeof string, "* Vehiculo ID: %d.", GetPlayerVehicleID(playerid));
	SendPlayerChatMessage(playerid, COLOR_GREY, string);
	return 1;
}
cmd:drivebug(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No se encuentra en ningÃºn vehículo.");
	if(GetPlayerState(playerid) != PLAYER_STATE_PASSENGER) return SendPlayerChatMessage(playerid, COLOR_GREY, "No se encuentra como pasajero.");
	ApplyAnimation(playerid, "PED", "CAR_GETIN_RHS", 4.1, 0, 0, 0, 0, 1, 1);
	ApplyAnimation(playerid, "PED", "CAR_GETIN_RHS", 4.1, 0, 0, 0, 0, 1, 1);
	SetPlayerArmedWeapon(playerid, 0);
    SetTimerEx("desbugdrive", 500, false, "ii", playerid, GetPlayerWeapon(playerid));
    return 1;
}

cmd:eject(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No estás en ningÃºn vehículo.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No eres conductor.");
	new string[180], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /eject (PlayerID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador desconectado.");
	if (playerid2 == playerid) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "{FFFF00}[ERROR]:{FFFFFF} No te puedes echar ati mismo.");
	if (GetPlayerVehicleID(playerid) != GetPlayerVehicleID(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El jugador no está en tu vehículo.");
	format(string, sizeof string, "hace caer a %s de su vehículo.", GetNameFormat(playerid2));
	rol_auto(playerid, string);
	RemovePlayerFromVehicle(playerid2);
	return 1;
}
alias:eject("expulsarveh", "expulsarcoche");

cmd:velocimetro(playerid)
{
	if (Act_Inventario[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes utilizar este comando mientras tengas el inventario activo.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser el conductor de un vehículo.");
	if (InfoPersonaje[playerid][pTogVelocimetro] == 0)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		ShowTDN(playerid, "Ahora ~b~~h~puedes ver~w~ el velocimetro.");
		InfoPersonaje[playerid][pTogVelocimetro] = 1;
		mostrar_velocimetro(playerid, vehicleid);
	}
	else
	{
		ShowTDN(playerid, "Ahora ~r~~h~no verás~w~ el velocimetro.");
		InfoPersonaje[playerid][pTogVelocimetro] = 0;
		hide_velocimetro(playerid);
	}
	guardar_int_mysql("personajes", "Velocimetro", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogVelocimetro]);
	return 1;
}
alias:velocimetro("togvelocimetro");

cmd:ventana(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No estás en ningÃºn vehículo.");
	new vehicle = GetPlayerVehicleID(playerid), ven_1, ven_2, ven_3, ven_4, ab_cr[20], name_ven[32], string[220];
	if (!IsWindowedVehicle(vehicle)) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Este vehículo no tiene ventanas.");
	GetVehicleParamsCarWindows(vehicle, ven_1, ven_2, ven_3, ven_4);
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new slotid;
		if (sscanf(params, "d", slotid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ventana (1: Tu ventana - 2: Todas las ventanas)");
		if (slotid < 1 || slotid > 2) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ventana (1: Tu ventana - 2: Todas las ventanas)");

		switch (slotid)
		{
		    case 1:
		    {
			    if(ven_1 != 0) SetVehicleParamsCarWindows(vehicle, 0, ven_2, ven_3, ven_4), ab_cr = "baja";
				else SetVehicleParamsCarWindows(vehicle, 1, ven_2, ven_3, ven_4), ab_cr = "sube";
				name_ven = "del conductor";
				format(string, sizeof string, "%s la ventana %s del %s.", ab_cr, name_ven, GetVehicleName(vehicle));
				rol_ame(playerid, string);
		    }
		    case 2:
		    {
				if (VehicleWindows[vehicle] == 0)
				{
					SetVehicleParamsCarWindows(vehicle, 0, 0, 0, 0);
					format(string, sizeof string, "baja las ventanas del %s.", GetVehicleName(vehicle));
					rol_ame(playerid, string);
				}
				else
				{
					SetVehicleParamsCarWindows(vehicle, 1, 1, 1, 1);
					format(string, sizeof string, "sube las ventanas del %s.", GetVehicleName(vehicle));
					rol_ame(playerid, string);
				}
			}
			default: return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ventana (1: Tu ventana - 2: Todas las ventanas)");
		}

	}
	else
	{
		new asiento = GetPlayerVehicleSeat(playerid);
		switch (asiento)
		{
			case 0: //conductor
			{
			    if (ven_1 != 0) SetVehicleParamsCarWindows(vehicle, 0, ven_2, ven_3, ven_4), ab_cr = "baja";
				else SetVehicleParamsCarWindows(vehicle, 1, ven_2, ven_3, ven_4), ab_cr = "sube";
				name_ven = "del conductor";
			}
			case 1: //pasajero
			{
			    if (ven_2 != 0) SetVehicleParamsCarWindows(vehicle, ven_1, 0, ven_3, ven_4), ab_cr = "baja";
				else SetVehicleParamsCarWindows(vehicle, ven_1, 1, ven_3, ven_4), ab_cr = "sube";
				name_ven = "de pasajero";
			}
			case 2: //trasera izquierda
			{
			    if (ven_3 != 0) SetVehicleParamsCarWindows(vehicle, ven_1, ven_2, 0, ven_4), ab_cr = "baja";
				else SetVehicleParamsCarWindows(vehicle, ven_1, ven_2, 1, ven_4), ab_cr = "sube";
				name_ven = "trasera izquierda";
			}
			case 3: //trasera derecha
			{
			    if (ven_4 != 0) SetVehicleParamsCarWindows(vehicle, ven_1, ven_2, ven_3, 0), ab_cr = "baja";
				else SetVehicleParamsCarWindows(vehicle, ven_1, ven_2, ven_3, 1), ab_cr = "sube";
				name_ven = "trasera derecha";
			}
		}

		format(string, sizeof string, "%s la ventana %s del %s.", ab_cr, name_ven, GetVehicleName(vehicle));
		rol_ame(playerid, string);
	}
	VehicleWindows[vehicle] = IsWindowOpened(vehicle);
	return 1;
}
alias:ventana("ven", "ventanilla");

cmd:motor(playerid) // 19-02-2020
{
	if (check_motor[playerid] != 0) return 1;
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	if (NPCrepara[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando ahora.");
	if (VehiculoGasolina[playerid] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes encender el motor en este momento.");
	new engine, lights, alarm, doors, bonnet, boot, objective, vehicleid = GetPlayerVehicleID(playerid), string[180];
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	if (EstaEnBicis(vehicleid))
	{
		if ((engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET)) { SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective); }
		SendPlayerChatMessage(playerid, COLOR_WHITE, "¿Pero por que intentas prender el motor de una bici? xDXD");
		return 1;
	}
	if (engine == VEHICLE_PARAMS_ON)
	{
		format(string, sizeof string, "apaga el motor de su vehículo.");
		rol_auto(playerid, string);
		SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
		arr_Engine{vehicleid} = 0;
		check_motor[playerid] = 0;
	}
	else if ((engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET))
	{
		if (GetPVarType(playerid, "AreaVehPos")) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes encender el vehículo, si tiene el estÃ©reo encendido.");
		//dinámicos
		Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
		{
		    if (InfoVehiculo[id][vNegocio] != 0)
		    {
				if (llaves_negocio(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo de negocio.");
				ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
				check_motor[playerid] = 1;
				SetTimerEx("SetVehicleEngine", 1000, 0, "dd",  vehicleid, playerid);
		    }
		    else if (InfoVehiculo[id][vTrabajo] != 0)
		    {
				if (llaves_trabajo(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo de trabajo.");
				ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
				check_motor[playerid] = 1;
				SetTimerEx("SetVehicleEngine", 1000, 0, "dd",  vehicleid, playerid);
		    }
		    else
			{
				switch (InfoVehiculo[id][vTipo])
				{
					case 1..50: //facciones
					{
						if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo de facción.");
						ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
						check_motor[playerid] = 1;
						SetTimerEx("SetVehicleEngine", 1000, 0, "dd",  vehicleid, playerid);
					}
					case 200: //vip
					{
						if (llaves_vip(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo VIP.");
						ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
						check_motor[playerid] = 1;
						SetTimerEx("SetVehicleEngine", 1000, 0, "dd",  vehicleid, playerid);
					}
					case 600: //rentable
					{
						if (llaves_renta(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo rentable.");
						ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
						check_motor[playerid] = 1;
						SetTimerEx("SetVehicleEngine", 1000, 0, "dd",  vehicleid, playerid);
					}
					default: //usuarios
					{
						if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo se encuentra embargado.");
						if (PermisosVehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo.");
						ShowInfoForPlayer(playerid, "Encendiendo...", 5000);
						check_motor[playerid] = 1;
						SetTimerEx("SetVehicleEngine", 1500, 0, "dd",  vehicleid, playerid);
					}
				}
			}
		}
	}
	return 1;
}

cmd:luces(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no tiene luces.");
	SetVehicleLights(vehicleid, playerid);
	PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
	return 1;
}

cmd:capo(playerid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (EstaEnBicis(vehicleid) || IsAPlane(vehicleid) || IsABike(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no tiene capo.");
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
					if (EstaEnBicis(InfoVehiculo[id][vIG_id]) || IsAPlane(InfoVehiculo[id][vIG_id]) || IsABike(InfoVehiculo[id][vIG_id])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no tiene capo.");
					SetVehicleHood(InfoVehiculo[id][vIG_id], playerid);
					return 1;
				}
			}
		}
	}
	return 1;
}

cmd:maletero(playerid)
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
	if (vehicleid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se ha detectado ningÃºn vehículo cerca.");
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no tiene maletero.");
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
		if (access == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo o no hay permisos para abrirlo.");
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
	SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca del maletero de un vehículo dinámico.");
	return 1;
}

cmd:vestado(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	new engine, lights, alarm, doors, bonnet, boot, objective, enginestatus[15], lightstatus[15], string[128];
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no necesita gasolina.");
	if (engine != VEHICLE_PARAMS_ON) format(enginestatus, sizeof(enginestatus), "Apagado");
	else format(enginestatus, sizeof(enginestatus), "Prendido");
	if (lights != VEHICLE_PARAMS_ON) format(lightstatus, sizeof(lightstatus), "Apagadas");
	else format(lightstatus, sizeof(lightstatus), "Prendidas");
	format(string, sizeof string, "Motor: %s | Luces: %s | Gasolina: %d",enginestatus,lightstatus,veh_gasolina[vehicleid]);
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	return 1;
}

cmd:v(playerid, params[])
{
	if (isnull(params))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /v (opción)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Opciones: estado, luces, maletero, capo");
		return 1;
	}
	if (strcmp(params, "luces", true) == 0) pc_cmd_luces(playerid);
	else if (strcmp(params, "capo", true) == 0) pc_cmd_capo(playerid);
	else if (strcmp(params, "maletero", true) == 0) pc_cmd_maletero(playerid);
	else if (strcmp(params, "estado", true) == 0) pc_cmd_vestado(playerid);
	return 1;
}

cmd:estereo(playerid)
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new StationsDialog[1560];
		strcat(StationsDialog, "{fff400}Detener audio de mÃºsica\n");
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
		strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electrónica{EBEBEB})\n");
		strcat(StationsDialog, "{FF0000}Agregar un url de internet .mp3");
		Dialog_Show(playerid, ConductorEstereo, DIALOG_STYLE_LIST, "EstÃ©reo", StationsDialog, "Continuar", "Salir");
		return 1;
	}
	if (GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes encender el estÃ©reo en interiores.");
	new id = -1, vehicleid, Float: x, Float: y, Float: z;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] != 0)
	{
		vehicleid = InfoVehiculo[v][vIG_id];
		GetVehiclePos(vehicleid, x, y, z);
		if (IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
		{
			id = v;
			break;
		}
	}
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca de ningÃºn vehículo con registro.");
	if (PermisosVehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de ese vehículo.");
	if (InfoVehiculo[id][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese vehículo se encuentra embargado.");
	if (InfoVehiculo[id][vStereo] != 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese vehículo no tiene estÃ©reo, compra uno en un taller mecánico.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if (boot == VEHICLE_PARAMS_OFF || boot == VEHICLE_PARAMS_UNSET) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese vehículo tiene el maletero cerrado.");
	if (engine == VEHICLE_PARAMS_ON) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese vehículo tiene el motor encendido.");
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		if (IsPlayerInRangeOfPoint(playerid, 60.0, GetPVarFloat(playerid2, "AreaVehPosX"), GetPVarFloat(playerid2, "AreaVehPosY"), GetPVarFloat(playerid2, "AreaVehPosZ")))
		{
			SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya se encuentra un vehículo con estÃ©reo en el rango de 60 metros.");
			return 1;
		}
	}
	SetPVarInt(playerid, "AreaVehPos", 1);
	SetPVarFloat(playerid, "AreaVehPosX", x);
	SetPVarFloat(playerid, "AreaVehPosY", y);
	SetPVarFloat(playerid, "AreaVehPosZ", z);
	SetPVarInt(playerid, "AreaVehMus", CreateDynamicSphere(GetPVarFloat(playerid, "AreaVehPosX"), GetPVarFloat(playerid, "AreaVehPosY"), GetPVarFloat(playerid, "AreaVehPosZ"), 45.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
	SetPVarInt(playerid, "AreaVehPosInt", GetPlayerInterior(playerid));
	SetPVarInt(playerid, "AreaVehPosVW", GetPlayerVirtualWorld(playerid));
	SetPVarInt(playerid, "AreaVehID", vehicleid);
	SendClientMessageEx(playerid, COLOR_GREEN, "Encendiste el estÃ©reo de tu %s, usa /menuestereo para ver las opciones.", GetVehicleName(vehicleid));
	return 1;
}

cmd:menuestereo(playerid)
{
	if (!GetPVarType(playerid, "AreaVehPos")) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No has encendido ningÃºn estÃ©reo de vehículo.");
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, GetPVarFloat(playerid, "AreaVehPosX"), GetPVarFloat(playerid, "AreaVehPosY"), GetPVarFloat(playerid, "AreaVehPosZ"))) return	SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca de tu vehículo con estÃ©reo encendido.");
	Dialog_Show(playerid, ShowEstereo, DIALOG_STYLE_LIST, "EstÃ©reo", "{F50000}Detener mÃºsica{FFFFFF}\nRadios\nURL - Internet\n{00CC00}Apagar estÃ©reo", "Continuar", "Salir");
	return 1;
}

cmd:desrentarveh(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (Vehiculo_Renta(vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás dentro de un vehículo rentable.");
	new id = verificar_id_vehiculo(vehicleid);
	if (InfoVehiculo[id][vRentaTiempo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no está rentado.");
	if (strcmp(NombreDeCuenta(playerid), InfoVehiculo[id][vRentaDueno], true) == 0)
	{
		foreach(new p: Player) if (IsPlayerInVehicle(p, vehicleid))
		{
			if (p != playerid) SendPlayerChatMessage(p, COLOR_YELLOW, "El vehículo en el que estabas fue respawneado, el dueÃ±o lo desrentó.");
		}
		InfoVehiculo[id][vRentaTiempo] = 0;
		alm(InfoVehiculo[id][vRentaDueno], "none");
		SetVehicleToRespawn(vehicleid);
		GivePlayerCash(playerid, 70, "desrentarveh");
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "Has dejado de rentar un vehículo, se te devolvió 70$.");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no está rentado por ti.");
	return 1;
}
alias:desrentarveh("quitaralquiler");

cmd:rentarveh(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (Vehiculo_Renta(vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás dentro de un vehículo rentable.");
	new id = verificar_id_vehiculo(vehicleid), string[170];
	if (InfoVehiculo[id][vRentaTiempo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo ya está rentado.");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vRentaTiempo] != 0)
	{
		if (strcmp(NombreDeCuenta(playerid), InfoVehiculo[v][vRentaDueno], true) == 0)
		{
			format(string, sizeof string, "Ya posees un vehículo con renta, ID %d.", InfoVehiculo[v][vIG_id]);
			SendPlayerChatMessage(playerid, 0xFF6347AA, string);
			return 1;
		}
	}
	if (GetPlayerCash(playerid) < 150) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes 150$ dólares.");
	GivePlayerCash(playerid, -150, "rentarveh");
	alm(InfoVehiculo[id][vRentaDueno], NombreDeCuenta(playerid));
	InfoVehiculo[id][vRentaTiempo] = 15;
	SendPlayerChatMessage(playerid, 0x90C3D4FF, "Rentaste este vehículo por 10 minutos en $150 dólares. (Puedes usar /desrentarveh)");
	return 1;
}

cmd:estacionar(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[v][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo se encuentra embargado.");
		new access = 0, string[160];
		if (InfoVehiculo[v][vNegocio] != 0)
		{
			if (CheckAdminCMD(playerid, 4)) return 1;
			access = 5;
		}
		if (InfoVehiculo[v][vTrabajo] != 0)
		{
			if (CheckAdminCMD(playerid, 4)) return 1;
			access = 7;
		}
		else
		{
			switch (InfoVehiculo[v][vTipo])
			{
				case 1..50: //facciones
				{
					if (llaves_lider(playerid, vehicleid) != 0) access = 3;
				}
			    case 200:
			    {
					if (CheckAdminCMD(playerid, 4)) return 1;
					access = 4;
				}
			    case 600:
			    {
					if (CheckAdminCMD(playerid, 4)) return 1;
					access = 6;
				}
				default: //usuarios
				{
				    if (PermisosVehiculo(playerid, vehicleid) != -1)
				    {
						if (llaves_vehiculo(playerid, vehicleid) != -1) access = 1;
						else access = 2;
					}
				}
			}
		}
		if (access == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo.");
		//mensaje de estacionar
		switch (access)
		{
			case 1: format(string, sizeof string, "estaciona su %s.", GetVehicleName(vehicleid));
			case 2: format(string, sizeof string, "estaciona el vehículo %s de %s.", GetVehicleName(vehicleid), InfoVehiculo[v][vPropietario]);
			case 3: format(string, sizeof string, "estaciona el vehículo %s de facción.", GetVehicleName(vehicleid));
			case 4: format(string, sizeof string, "estaciona el vehículo %s VIP.", GetVehicleName(vehicleid));
			case 5: format(string, sizeof string, "estaciona el vehículo %s de negocio.", GetVehicleName(vehicleid));
			case 6: format(string, sizeof string, "estaciona el vehículo %s de renta.", GetVehicleName(vehicleid));
			case 7: format(string, sizeof string, "estaciona el vehículo %s de trabajo.", GetVehicleName(vehicleid));
		}
		rol_auto(playerid, string);
		//apaga motor
		if (!EstaEnBicis(vehicleid))
		{
			check_motor[playerid] = 0;
			arr_Engine {vehicleid} = 0;
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
		}
		//save
		GetVehicleHealth(vehicleid, InfoVehiculo[v][vVida]);
		GetVehicleDamageStatus(vehicleid, InfoVehiculo[v][vDanioSuperficie], InfoVehiculo[v][vDanioPuertas], InfoVehiculo[v][vDanioLuces], InfoVehiculo[v][vDanioRuedas]);
		GetVehiclePos(vehicleid, InfoVehiculo[v][vPosicionX], InfoVehiculo[v][vPosicionY], InfoVehiculo[v][vPosicionZ]);
		GetVehicleZAngle(vehicleid, InfoVehiculo[v][vPosicionR]);
		InfoVehiculo[v][vVirtualWorld] = GetPlayerVirtualWorld(playerid);
		InfoVehiculo[v][vInterior] = GetPlayerInterior(playerid);
		GetVehiclePos(vehicleid, InfoVehiculo[v][vEndPosicionX], InfoVehiculo[v][vEndPosicionY], InfoVehiculo[v][vEndPosicionZ]);
		GetVehicleZAngle(vehicleid, InfoVehiculo[v][vEndPosicionR]);
		InfoVehiculo[v][vEndVirtualWorld] = GetPlayerVirtualWorld(playerid);
		InfoVehiculo[v][vEndInterior] = GetPlayerInterior(playerid);
		InfoVehiculo[v][vGasolina] = veh_gasolina[vehicleid];
		new query[2056];
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET Posicion_X = '%f', Posicion_Y = '%f', Posicion_Z = '%f', Posicion_R = '%f', Interior = '%d', VirtualWorld = '%d', Vida = '%f', DanioSuperficie = '%d', DanioPuertas = '%d', \
		DanioLuces = '%d', DanioRuedas = '%d', Gasolina = '%d', End_Posicion_X = '%f', End_Posicion_Y = '%f', End_Posicion_Z = '%f', End_Posicion_R = '%f', End_Interior = '%d', End_VirtualWorld = '%d' WHERE ID = '%d'",
		InfoVehiculo[v][vPosicionX],
		InfoVehiculo[v][vPosicionY],
		InfoVehiculo[v][vPosicionZ],
		InfoVehiculo[v][vPosicionR],
		InfoVehiculo[v][vInterior],
		InfoVehiculo[v][vVirtualWorld],
		InfoVehiculo[v][vVida],
		InfoVehiculo[v][vDanioSuperficie],
		InfoVehiculo[v][vDanioPuertas],
		InfoVehiculo[v][vDanioLuces],
		InfoVehiculo[v][vDanioRuedas],
		InfoVehiculo[v][vGasolina],
		InfoVehiculo[v][vEndPosicionX],
		InfoVehiculo[v][vEndPosicionY],
		InfoVehiculo[v][vEndPosicionZ],
		InfoVehiculo[v][vEndPosicionR],
		InfoVehiculo[v][vEndInterior],
		InfoVehiculo[v][vEndVirtualWorld],
		InfoVehiculo[v][vID_sql]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Debes estar dentro de un vehículo propio o con llaves.");
	return 1;
}

cmd:pagarm(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 3.0, 240.4770,112.7777,1003.2188) || IsPlayerInRangeOfPoint(playerid, 3.0, 358.236083,182.073394,1008.382812)) // Map de LSPD y DGT respectivamente.
	{
		if (InfoPersonaje[playerid][pLicencia][0] == 0) return SendPlayerChatMessage(playerid, 0xA2DC35FF, "[MULTA]:{FFFFFF} Una licencia de conducir válida es necesaria para liberar su vehículo del depósito municipal.");
		new dialog[2048], gformat[256], iCount = 0, iMultas = 0;
		Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vPropietario], true) == 0)
		{
			if (InfoVehiculo[veh][vPrecio] < 1)
			{
				InfoVehiculo[veh][vPrecio] = 10000;
				//guardar_int_mysql("vehiculos", "Precio", InfoVehiculo[veh][vID_sql], InfoVehiculo[veh][vPrecio]);
			}
			//vehículo embargado
			if (InfoVehiculo[veh][vEmbargo] != 0)
			{
				format(gformat, sizeof gformat, "%s (Multa - $%s) (Embargado - $%s Liberación)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400], diner_coma(InfoVehiculo[veh][vMulta]), diner_coma(InfoVehiculo[veh][vMulta]*2)), iMultas++;
			}
			else //vehículo status normal o con multa
			{
				if (InfoVehiculo[veh][vMulta] != 0) format(gformat, sizeof gformat, "%s (Multa - $%s)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400], diner_coma(InfoVehiculo[veh][vMulta])), iMultas++;
				else format(gformat, sizeof gformat, "%s\n", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
			}
			strcat(dialog, gformat);
			//conteo
			new gformat2[64];
			format(gformat2, sizeof gformat2, "multevehuwu%d", iCount);
			SetPVarInt(playerid, gformat2, veh);
			iCount++;
		}
		if (iMultas == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes multas para pagar o vehículos para ser liberados.");
		if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes vehículos a tu nombre.");
		Dialog_Show(playerid, ShowMultas, DIALOG_STYLE_LIST, "Vehiculos", dialog, "Liberar", "Salir");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Las multas pueden ser pagadas en la DGT, Dirección General de Tráfico.");
	return 1;
}
alias:pagarm("pagarmulta");

cmd:seguro(playerid)
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
					if (access == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo.");
					if (InfoVehiculo[v][vSeguro] == 0)
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~r~trabado", 3000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 1;
						LockPlayerVehicle(vehicleid);
					}
					else
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~g~destrabado",5000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 0;
						UnLockPlayerVehicle(vehicleid);
					}
					guardar_int_mysql("vehiculos", "ConSeguro", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vSeguro]);
					return 1;
				}
				case 1..50: //facciones
				{
					if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo de facción.");
					if (InfoVehiculo[v][vSeguro] == 0)
					{
						ShowInfoForPlayer(playerid,"~r~Vehiculo trabado.", 3000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 1;
						LockPlayerVehicle(vehicleid);
					}
					else
					{
						ShowInfoForPlayer(playerid,"~g~Vehiculo destrabado.", 3000);
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
    SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca de un vehículo dinámico.");
    return 1;
}
alias:seguro("lock");

new id_veh_actual[MAX_PLAYERS];

cmd:llaves(playerid)
{
	new dialog[3084], gformat[370], iCount = 0;
	strcat(dialog, "Modelo (ID)\tLocalización (Estado)\n");
	Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vPropietario], true) == 0)
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
		//conteo
		new gformat2[64];
		format(gformat2, sizeof gformat2, "keyvehowo%d", iCount);
		SetPVarInt(playerid, gformat2, veh);
		iCount++;
	}
	if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes ningÃºn vehículo a tu nombre.");
	Dialog_Show(playerid, MenuVehiculos, DIALOG_STYLE_TABLIST_HEADERS, "Tus vehículos", dialog, "Continuar", "Salir");
	return 1;
}
alias:llaves("localizar", "vehiculos", "coches", "veh");

cmd:vendermicoche(playerid, params[])
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar dentro de tu vehículo como conductor.");
	new string[256], playerid2, price;
	new Float: health, vehicleid = GetPlayerVehicleID(playerid);
	Loop(d, totalvehiculos, 1) if (InfoVehiculo[d][vIG_id] == vehicleid)
	{
		if (llaves_vehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres el propietario de este vehículo.");
		if (InfoVehiculo[d][vPremium] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes vender vehículos que compraste con monedas.");
		GetVehicleHealth(vehicleid, health);
		if (sscanf(params, "dd", playerid2, price)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /vendermicoche (id) (precio)");
		if (price < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Precio debe ser mayor a 0.");
		if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes venderte el vehículo a ti mismo.");
		if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
		if (!CercaDelWeon(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás lejos del jugador.");
		if (InfoPersonaje[playerid2][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador debe jugar el servidor al menos 2 horas.");
		if (health < 500) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El vehiculo está muy daÃ±ado como para ser vendido.");
		if (CountObjVeh(d) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes vender un vehículo con objetos VIP.");
		if (tiene_componente(1008, vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo tiene componente nitro x5, usa /qmod para poder continuar.");
		if (tiene_componente(1009, vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo tiene componente nitro x2, usa /qmod para poder continuar.");
		if (tiene_componente(1010, vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo tiene componente nitro x10, usa /qmod para poder continuar.");

		Pla_vehicle[playerid2] = playerid;
		Osql_vehicle[playerid2] = d;
		Price_vehicle[playerid2] = price;

		format(string, sizeof string, "* Ofreciste a %s para comprar este %s por $%d.", GetNameFormat(playerid2), GetVehicleName(vehicleid), price);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		format(string, sizeof string, "* %s te ha ofrecidor su %s por $%d, (usa /aceptar coche).", GetNameFormat(playerid), GetVehicleName(vehicleid), price);
		SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
		return 1;
	}
    SendPlayerChatMessage(playerid, COLOR_GREY, " Tu necesitas estar dentro de un vehiculo que te pertenece.");
    return 1;
}
cmd:oldcar(playerid)
{
	if (gLastCar[playerid] == 0) return SendPlayerChatMessage(playerid, -1, "No te has subido a ningÃºn vehículo.");
	new string[170];
	format(string, sizeof string, "Tu Ãºltimo vehiculo manejado fue el ID %d.", gLastCar[playerid]);
	SendPlayerChatMessage(playerid, COLOR_GREY, string);
	return 1;
}
cmd:vendercoche(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 5, 358.3934,186.1840,1008.3828)) return SendPlayerChatMessage(playerid, COLOR_GREY, "[ERROR]:{FFFFFF} Tienes que estar en el mostrador de la DGT, Dirección General de Tráfico para hacer esto.");
	new dialog[2048], gformat[256], iCount = 0;
	Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vPropietario], true) == 0)
	{
		if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "%s (Embargado)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		else
		{
			if (InfoVehiculo[veh][vSpawned] != 0) format(gformat, sizeof gformat, "%s (%d)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400], InfoVehiculo[veh][vIG_id]);
			else format(gformat, sizeof gformat, "%s (oculto)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		}
		strcat(dialog, gformat);
		//conteo
		new gformat2[64];
		format(gformat2, sizeof gformat2, "sellvehkey%d", iCount);
		SetPVarInt(playerid, gformat2, veh);
		iCount++;
	}
	if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes ningÃºn vehículo a tu nombre.");
	Dialog_Show(playerid, SellVehicle, DIALOG_STYLE_LIST, "Vender - vehículo", dialog, "Continuar", "Salir");
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, "Si vendes el vehículo te pagarán la cuarta parte del precio de lo que te habia costado o menos.");
	return 1;
}

/*cmd:gunlocker(playerid)
{
	if (GetPlayerCash(playerid) < 2500) { SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes 2,500$ para mejorar el máximo de slots de tu maletero."); return 1; }
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Debes ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[v][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo se encuentra embargado.");
		if (PermisosVehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes las llaves de este vehículo.");
		if (InfoVehiculo[v][vMaxMaletero] == 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "Llegaste al máximo de 10 slots en el maletero de este vehículo.");
		new string[256];
		GameTextForPlayer(playerid,"~g~Gunlocker mejorado!",5000,6);
		PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		InfoVehiculo[v][vMaxMaletero]++;
		GivePlayerCash(playerid, -2500, "gunlocker");
		format(string, sizeof string, "Ahora tu %s dispone de {FFFF00}%d slots{FFFFFF} en el maletero. (Mejoras: {FFFF00}/smaletero /gmaletero{FFFFFF})", InfoVehiculo[v][vMaxMaletero]);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, string);
		guardar_int_mysql("vehiculos", "MaxMaletero", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vMaxMaletero]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Debes estar dentro de un vehículo propio.");
	return 1;
}*/

//nuevo sistema de maletero
cmd:vermaletero(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estÃƒÂ¡s herido o muerto.");
	new Float: x, Float: y, Float: z;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
	{
		new vehicleid = InfoVehiculo[id][vIG_id];
		GetVehiclePos(vehicleid, x, y, z);
		if (IsPlayerInRangeOfPoint(playerid, 4.0, x, y, z))
		{
			if (InfoVehiculo[id][vMaleteroOn] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "El maletero de este vehículo está cerrado, utiliza (/v maletero) para abrirlo.");
			if (vehiculos_legales(vehicleid))
			{
				if (llaves_faccion(playerid, vehicleid) == 0) SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo de facción.");
			}
			if (InfoVehiculo[id][vMaxMaletero] >= 10)
			{
				InfoVehiculo[id][vMaxMaletero] = 10;
				guardar_int_mysql("vehiculos", "MaxMaletero", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vMaxMaletero]);
			}
			if (EstaEnBicis(vehicleid)) SendPlayerChatMessage(playerid, COLOR_GREY,"Este vehículo no tiene maletero.");
            VerMaletero(playerid, id);
			PlayerMaleteroVeh[playerid] = id;
			return 1;
		}
	}
    SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca del maletero de un vehículo dinámico.");
	return 1;
}


/*cmd:gmaletero(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido o muerto.");
 	if (InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano derecha.");
	new gformat[270], Float: x, Float: y, Float: z;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
	{
		new vehicleid = InfoVehiculo[id][vIG_id], objeto = InfoPersonaje[playerid][pManoDerecha], objetocant = InfoPersonaje[playerid][pManoDerechaCant];
		GetVehiclePos(vehicleid, x, y, z);
		if (IsPlayerInRangeOfPoint(playerid, 4.0, x, y, z))
		{
			if (InfoVehiculo[id][vMaleteroOn] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "El maletero de este vehículo está cerrado, utilzia (/v maletero) para abrirlo.");
			if (vehiculos_legales(vehicleid))
			{
				if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo de facción.");
			}
			if (InfoVehiculo[id][vMaxMaletero] >= 10)
			{
				InfoVehiculo[id][vMaxMaletero] = 10;
				guardar_int_mysql("vehiculos", "MaxMaletero", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vMaxMaletero]);
			}
			if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY,"Este vehículo no tiene maletero.");
			new rSlot = -1;
			Loop(xs, InfoVehiculo[id][vMaxMaletero], 0) if (InfoVehiculo[id][vMaletero][xs] == 0)
			{
			    rSlot = xs;
			    break;
			}
			if (rSlot == -1)
			{
				if (InfoVehiculo[id][vMaxMaletero] == 10) format(gformat, sizeof gformat, "No puedes guardar más cosas en tu maletero, máximo %d slots.", InfoVehiculo[id][vMaxMaletero]);
				else format(gformat, sizeof gformat, "No puedes guardar más cosas en tu maletero, máximo %d slots. (Usa /gunlocker)", InfoVehiculo[id][vMaxMaletero]);
				SendPlayerChatMessage(playerid, COLOR_RED, gformat);
				return 1;
			}
			InfoVehiculo[id][vMaletero][rSlot] = objeto;
			InfoVehiculo[id][vMaleteroCant][rSlot] = objetocant;
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE vehiculos SET Maletero%d = '%d', MaleteroCant%d = '%d' WHERE ID = '%d'", rSlot+1, objeto, rSlot+1, objetocant, InfoVehiculo[id][vID_sql]);
			mysql_tquery(db_samp, gformat);
			ResetPlayerWeapons(playerid);
			RemovePlayerAttachedObject(playerid, 7);
			InfoPersonaje[playerid][pManoDerecha] = 0;
			InfoPersonaje[playerid][pManoDerechaCant] = 0;
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, gformat);
			if (objetocant == 0 || objetocant == 1) format(gformat, sizeof gformat, "Guardaste en el maletero tu %s.", InfoInventario[objeto][NombreObjeto]);
			else
			{
				if (InfoInventario[objeto][IDArma] != 0)
				{
					format(gformat, sizeof gformat, "%s guarda %s en el %s (SQL %d).", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto], GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vID_sql]);
					Log("f_logs/Maletero.log", gformat);
					format(gformat, sizeof gformat, "Guardaste en el maletero tu %s con %d balas.", InfoInventario[objeto][NombreObjeto], objetocant);
				}
				else format(gformat, sizeof gformat, "Guardaste en el maletero tu %s con %d de cantidad.", InfoInventario[objeto][NombreObjeto], objetocant);
			}
			SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
			return 1;
		}
	}
    SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca del maletero de un vehículo dinámico.");
	return 1;
}
alias:gmaletero("guardarmaletero");

cmd:smaletero(playerid, params[])
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido o muerto.");
	if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes un objeto en tu mano derecha.");
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tienes restricción de armas por dos horas.");
	new gformat[270], Float: x, Float: y, Float: z;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] != 0)
	{
		new vehicleid = InfoVehiculo[id][vIG_id];
		GetVehiclePos(vehicleid, x, y, z);
		if (IsPlayerInRangeOfPoint(playerid, 4.0, x, y, z))
		{
			if (!Vehiculo_LSPD(vehicleid) && !Vehiculo_LSCSD(vehicleid) && !Vehiculo_FBI(vehicleid) && !Vehiculo_USMC(vehicleid))
			{
				if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes hacer esto mientras estar en el interior del vehículo!");
				if (InfoVehiculo[id][vMaleteroOn] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "El maletero de este vehículo está cerrado, utilzia (/v maletero) para abrirlo.");
			}
			if (vehiculos_legales(vehicleid))
			{
				if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo de facción.");
			}
			if (InfoVehiculo[id][vMaxMaletero] >= 10)
			{
				InfoVehiculo[id][vMaxMaletero] = 10;
				guardar_int_mysql("vehiculos", "MaxMaletero", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vMaxMaletero]);
			}
			if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo no tiene maletero.");
			new rSlot, maxmaletero = InfoVehiculo[id][vMaxMaletero];
			if (sscanf(params, "i", rSlot))
			{
			    new count = 0;
				Loop(xs, maxmaletero, 0) if (InfoVehiculo[id][vMaletero][xs] != 0) count++;
				if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu maletero.");
				SendPlayerChatMessage(playerid, COLOR_GREY, "Utiliza: /smaletero (Slot)");
				Loop(xs, maxmaletero, 0) if (InfoVehiculo[id][vMaletero][xs] != 0)
				{
					format(gformat, sizeof gformat, "Tienes en {b42d2d}slot %d{EBEBEB}: %s", xs+1, slot_objeto(InfoVehiculo[id][vMaletero][xs], InfoVehiculo[id][vMaleteroCant][xs]));
					SendPlayerChatMessage(playerid, 0xEBEBEBFF, gformat);
				}
				return 1;
			}
			if (rSlot < 1 || rSlot > maxmaletero)
			{
				format(gformat, sizeof gformat, "El nÃºmero de slot debe estar entre 1 y %d.", maxmaletero);
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
				return 1;
			}
			rSlot--;
			if (InfoVehiculo[id][vMaletero][rSlot] == 0) return SendPlayerChatMessage(playerid, COLOR_RED, "No tienes nada en ese slot.");
			new objeto = InfoVehiculo[id][vMaletero][rSlot], objetocant = InfoVehiculo[id][vMaleteroCant][rSlot];
			InfoVehiculo[id][vMaletero][rSlot] = 0;
			InfoVehiculo[id][vMaleteroCant][rSlot] = 0;
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE vehiculos SET Maletero%d = 0, MaleteroCant%d = 0 WHERE ID = '%d'", rSlot+1, rSlot+1, InfoVehiculo[id][vID_sql]);
			mysql_tquery(db_samp, gformat);
			InfoPersonaje[playerid][pManoDerecha] = objeto;
			InfoPersonaje[playerid][pManoDerechaCant] = objetocant;
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", objeto, objetocant, InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, gformat);
			if (objetocant == 1 || objetocant == 0) format(gformat, sizeof gformat, "Sacaste tu %s del maletero.", InfoInventario[objeto][NombreObjeto]);
			else
			{
				if (InfoInventario[objeto][IDArma] != 0) format(gformat, sizeof gformat, "Sacaste tu %s con %d balas del maletero.", InfoInventario[objeto][NombreObjeto], objetocant);
				else format(gformat, sizeof gformat, "Sacaste tu %s con %d de cantidad del maletero.", InfoInventario[objeto][NombreObjeto], objetocant);
			}
			SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
			ResetPlayerWeapons(playerid);
			if (InfoInventario[objeto][IDArma] > 0)
			{
				GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], objetocant);
				format(gformat, sizeof gformat, "%s saca %s del %s (SQL %d).", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto], GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vID_sql]);
				Log("f_logs/Maletero.log", gformat);
			}
			PonerObjeto(playerid, 1, objeto);
			return 1;
		}
	}
    SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca del maletero de un vehículo dinámico.");
	return 1;
}
alias:smaletero("sacarmaletero");*/

cmd:fllaves(playerid)
{
	new faccion = InfoPersonaje[playerid][pMiembro];
	if (faccion == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembros de facción.");
	new dialog[3684], gformat[370], vcount = 0;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == faccion)
	{
		format(gformat, sizeof gformat, "[%d] %s (%d)\n", vcount+1, VehicleName[InfoVehiculo[id][vModelo] - 400], InfoVehiculo[id][vIG_id]);
		strcat(dialog, gformat);
		//conteo
		new gformat2[64];
		format(gformat2, sizeof gformat2, "RanuraVeh%d", vcount);
		SetPVarInt(playerid, gformat2, id);
		vcount++;
	}
	if (vcount == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes ningÃºn vehículo en tu facción.");
	Dialog_Show(playerid, MenuFacVehiculos, DIALOG_STYLE_LIST, InfoFaccion[faccion][fNombre], dialog, "Continuar", "Salir");
	return 1;
}

cmd:frespawn(playerid, params[])
{
	if (!Propietario_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes acceso a este comando.");
	if (!CheckTimer(120, fRespawnTiempo[playerid]))
	{
		new id = InfoPersonaje[playerid][pMiembro];
		if (!InfoFaccion[id][fTipo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tu facción no tiene un tipo asignado.");
		new bool:unwanted[MAX_VEHICLES], string[170], count = 0;
		Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerInAnyVehicle(playerid2))
		{
			unwanted[GetPlayerVehicleID(playerid2)] = true;
		}
		Loop(e, totalvehiculos, 1) if (InfoVehiculo[e][vIG_id] != 0)
		{
			new vehicleid = InfoVehiculo[e][vIG_id];
			if (InfoVehiculo[e][vTipo] == id && !unwanted[vehicleid])
			{
				SetVehicleToRespawn(vehicleid);
				SetVehicleParamsEx(vehicleid,0,0,0,0,0,0,0);
				arr_Engine{vehicleid} = 0;
				count++;
			}
		}
		format(string, sizeof string, "Se respawnearon %d vehículos de %s.", count, InfoFaccion[id][fLogo]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		fRespawnTiempo[playerid] = gettime();
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(120, fRespawnTiempo[playerid]) ));
	}
	return 1;
}

//Administrativos
cmd:reparartodo(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], count = 0;
	Loop(car, GetVehiclePoolSize(), 0) if (GetVehicleModel(car))
	{
		RepairVehicle(car);
		if (GetVehicleModel(car) == 528 || GetVehicleModel(car) == 427) SetVehicleHealth(car, 5000.0);
		else SetVehicleHealth(car, 1000.0);
		count++;
	}
	format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %d vehículos fueron reparados por %s(%d).", count, InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}
cmd:rcategoria(playerid)
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	Dialog_Show(playerid, RespawnCategoria, DIALOG_STYLE_LIST, "Elige cuales respawnear", "Facciones\nVIPs\nNegocios\nTrabajos\nRentables\nUsuarios", "Continuar", "Salir");
	return 1;
}

cmd:respawncars(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], radius;
	if (sscanf(params, "d", radius)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /respawncars (Radio)");
	if (radius < 1 || radius > 50) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El radio debe ser de 1 a 50.");
	RespawnNearbyVehicles(playerid, radius);
	format(string, sizeof string, "Usted ha respawneado los vehículos dentro del radio de %d.", radius);
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	return 1;
}

cmd:respawnauto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], carid;
	if (sscanf(params, "d", carid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /respawnauto (carid)");
	SetVehicleToRespawn(carid);
	format(string, sizeof string, "vehículo ID %d - Respawneado.", carid);
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	return 1;
}
alias:respawnauto("rtcar", "respawncar");

cmd:checkllaves(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /checkllaves (Jugador)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "ID no válida.");
	new dialog[2048], gformat[256], iCount = 0;
	Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0 && strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoVehiculo[veh][vPropietario], true) == 0)
	{
		if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "%s (Embargado)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		else
		{
			if (InfoVehiculo[veh][vSpawned] != 0) format(gformat, sizeof gformat, "%s (%d)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400], InfoVehiculo[veh][vIG_id]);
			else format(gformat, sizeof gformat, "%s (oculto)\n", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		}
		strcat(dialog, gformat);
		//conteo
		new gformat2[64];
		format(gformat2, sizeof gformat2, "cehvehkey%d", iCount);
		SetPVarInt(playerid, gformat2, veh);
		iCount++;
	}
	if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese jugador no tiene ningÃºn vehículo a su nombre.");
	format(gformat, sizeof gformat, "vehículos de {F5DEB3}%s", NombreDeCuenta(playerid2));
	Dialog_Show(playerid, GotoVehU, DIALOG_STYLE_LIST, gformat, dialog, "Ir", "Salir");
	return 1;
}
alias:checkllaves("vercoches");

cmd:aseguro(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
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
					if (InfoVehiculo[v][vSeguro] == 0)
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~r~trabado",5000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 1;
						LockPlayerVehicle(vehicleid);
					}
					else
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~g~destrabado",5000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 0;
						UnLockPlayerVehicle(vehicleid);
					}
					guardar_int_mysql("vehiculos", "ConSeguro", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vSeguro]);
					return 1;
				}
				case 1..50: //facciones
				{
					if (InfoVehiculo[v][vSeguro] == 0)
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~r~bloqueado.",5000);
						PlayerPlaySoundEx(1145, x, y, z);
						InfoVehiculo[v][vSeguro] = 1;
						LockPlayerVehicle(vehicleid);
					}
					else
					{
						ShowInfoForPlayer(playerid,"~w~Vehiculo ~g~desbloqueado.",5000);
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
    SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar cerca de un vehículo dinámico.");
    return 1;
}

cmd:enrenta(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new string[185];
	SendPlayerChatMessage(playerid, 0x90C3D4FF, "vehículos rentados:");
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vRentaTiempo] != 0)
	{
		format(string, sizeof string, "[ID: %d] %s - tiempo: {90C3D4}%d minutos", InfoVehiculo[id][vIG_id], InfoVehiculo[id][vRentaDueno], InfoVehiculo[id][vRentaTiempo]);
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
	}
	return 1;
}

cmd:listavehs(playerid)
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new max_vehs = 0, max_vehs2 = 0;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == 0 && InfoVehiculo[id][vNegocio] == 0 && InfoVehiculo[id][vTrabajo] == 0)
	{
		if (InfoVehiculo[id][vTimeSave] != 0) { SendClientMessageEx(playerid, -1, "%d (%s) se oculta en %d minutos.", InfoVehiculo[id][vIG_id], GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vTimeSave]); max_vehs++; }
		if (InfoVehiculo[id][vSpawned] == 1) { max_vehs2++; }
	}
	SendClientMessageEx(playerid, -1, "vehículos por ocultar: {FF0000}%d{FFFFFF} | vehículos spawneados: {FF0000}%d", max_vehs, max_vehs2);
	return 1;
}

cmd:ocultarveh(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new vehicleid;
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ocultarveh (VehiculoID) [/dl]");
	if (vehicleid < 100 || vehicleid > 1999) return SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no es de ningÃºn usuario o no existe. (2)");
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] == 0 && InfoVehiculo[id][vNegocio] == 0 && InfoVehiculo[id][vTrabajo] == 0)
	{
		if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "vehículo seleccionado no tiene modelo.");
		if (InfoVehiculo[id][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "vehículo seleccionado se encuentra oculto.");
		if (IsVehicleBusy(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "vehículo seleccionado posee ocupantes.");
		SendClientMessageEx(playerid, COLOR_YELLOW, "Ocultaste el vehículo ID %d (SQL %d) (%s de %s)", vehicleid, InfoVehiculo[id][vID_sql], GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vPropietario]);
		Quit_Vehicles(id);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no es de ningÃºn usuario o no existe.");
	return 1;
}

cmd:veh_premium(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new vehicleid, string[160];
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /veh_premium (VehiculoID) [para saber ID exacta acercate al vehículo con /dl]");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[v][vPremium] == 0)
		{
			format(string, sizeof string, "Colocaste modo premium el %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
			InfoVehiculo[v][vPremium] = 1;
		}
		else
		{
			format(string, sizeof string, "Sacaste modo premium el %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
			InfoVehiculo[v][vPremium] = 0;
		}
		guardar_int_mysql("vehiculos", "Premium", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vPremium]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese vehículo no está spawneado o no existe.");
	return 1;
}

cmd:veh_sirena(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new vehicleid, string[160], Float: vehx, Float: vehy, Float: vehz, Float: vehr;
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /veh_sirena (VehiculoID) [para saber ID exacta acercate al vehículo con /dl]");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (AnibleVeh(v) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo puedes agregar sirena en vehículos LSPD/FBI/USMC/LSCSD.");
		if (InfoVehiculo[v][vSirena] == 0)
		{
			format(string, sizeof string, "Colocaste sonido de sirena en el %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
			InfoVehiculo[v][vSirena] = 1;
		}
		else
		{
			format(string, sizeof string, "Retiraste sonido de sirena del %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
			InfoVehiculo[v][vSirena] = 0;
		}
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		guardar_int_mysql("vehiculos", "Sirena", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vSirena]);
		GetVehicleHealth(vehicleid, InfoVehiculo[v][vVida]);
		GetVehicleDamageStatus(vehicleid, InfoVehiculo[v][vDanioSuperficie], InfoVehiculo[v][vDanioPuertas], InfoVehiculo[v][vDanioLuces], InfoVehiculo[v][vDanioRuedas]);
		GetVehiclePos(vehicleid, vehx, vehy, vehz);
		GetVehicleZAngle(vehicleid, vehr);
		DestroyVehicle(vehicleid);
		InfoVehiculo[v][vIG_id] = CreateVehicle(InfoVehiculo[v][vModelo], vehx, vehy, vehz, vehr, InfoVehiculo[v][vColor_1], InfoVehiculo[v][vColor_2], -1, InfoVehiculo[v][vSirena]);
		new v_vehicleid = InfoVehiculo[v][vIG_id];
		if (InfoVehiculo[v][vSeguro] != 0) LockPlayerVehicle(v_vehicleid);
		if (InfoVehiculo[v][vPaintJob] != -1) ChangeVehiclePaintjob(v_vehicleid, InfoVehiculo[v][vPaintJob]);
		SetVehicleInterior(v_vehicleid, InfoVehiculo[v][vInterior]);
		SetVehicleExVirtualWorld(v_vehicleid, InfoVehiculo[v][vVirtualWorld]);
		SetVehicleMatricula(InfoVehiculo[v][vIG_id]);
		if (InfoVehiculo[v][vModelo] == 528 || InfoVehiculo[v][vModelo] == 427) SetVehicleHealth(v_vehicleid, 5000.0);
		else SetVehicleHealth(v_vehicleid, InfoVehiculo[v][vVida]);
		UpdateVehicleDamageStatus(v_vehicleid, InfoVehiculo[v][vDanioSuperficie], InfoVehiculo[v][vDanioPuertas], InfoVehiculo[v][vDanioLuces], InfoVehiculo[v][vDanioRuedas]);
		Loop(m, MAX_MODIFICACIONES, 0) { AddVehicleComponent(v_vehicleid, InfoVehiculo[v][vModificacion][m]); }
		if (!isnull(InfoVehiculo[v][vCallSign]))
		{
			if (IsValidDynamic3DTextLabel(InfoVehiculo[v][vOnCallSign]))
			{
				DestroyDynamic3DTextLabel(InfoVehiculo[v][vOnCallSign]);
				InfoVehiculo[v][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
			}
			InfoVehiculo[v][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[v][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, v_vehicleid);
		}
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese vehículo no está spawneado o no existe.");
	return 1;
}

cmd:acallsign(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No tienes suficentes permisos para usar este comando.");
	if (CheckAdminDuty(playerid)) return 1;
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar dentro de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid), string[256];
	new id = verificar_id_vehiculo(vehicleid);
	if (!isnull(InfoVehiculo[id][vCallSign])) //quitar
	{
		if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
		{
			DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
			InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
		}
		alm(InfoVehiculo[id][vCallSign], "");
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) removió el callsign [%d].", InfoCuenta[playerid][jNombre], playerid, vehicleid);
		SendAdminMessage(0xFFFFFFFF, string);
		guardar_string_mysql("vehiculos", "CallSign", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vCallSign]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no posee ningÃºn callsign activo.");
	return 1;
}

cmd:amotor(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar dentro de un vehículo como conductor.");
	new engine,lights, alarm, doors, bonnet, boot, objective, vehicleid = GetPlayerVehicleID(playerid);
	if (GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 510) return SendPlayerChatMessage(playerid,COLOR_WHITE,"{FFFF00}[ERROR]:{FFFFFF} No puedes usar este comando si estás en este tipo de vehiculos.");
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	if (engine == VEHICLE_PARAMS_ON)
	{
		SendPlayerChatMessage(playerid, COLOR_RED, "[ADM] El motor del vehículo ha sido apagado correctamente.");
		SetVehicleEngine(vehicleid, playerid);
	}
	else if ((engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET))
	{
		SendPlayerChatMessage(playerid, COLOR_RED, "[ADM] El motor del vehículo ha sido encendido correctamente.");
		SetVehicleEngine(vehicleid, playerid);
	}
	return 1;
}

cmd:darauto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
 	new string[170], playerid2, modelid, color1, color2;
	if (sscanf(params, "dddd", playerid2, modelid, color1, color2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darauto (PlayerID) (ModeloID) (Color1) (Color2)");
	if (color1 < 0 || color1 > 250) { SendPlayerChatMessage(playerid, COLOR_GREY, "El color 1 no puede super el ID 250."); return 1; }
	if (color2 < 0 || color2 > 250) { SendPlayerChatMessage(playerid, COLOR_GREY, "El color 2 no puede super el ID 250."); return 1; }
	if (modelid < 400 || modelid > 611) { SendPlayerChatMessage(playerid, COLOR_GREY, "Modelo inválido, intenta entre 400 y 611."); return 1; }
 	new carsamount = VehicleCount(playerid);
	if (carsamount >= 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no puede tener más de 10 vehículos.");
	new Float: X, Float: Y, Float: Z, Float: Angle;
    GetPlayerPos(playerid2,X,Y,Z);
    GetPlayerFacingAngle(playerid2,Angle);
  	crear_vehiculo(playerid2, modelid, X, Y, Z, Angle, GetPlayerInterior(playerid2), GetPlayerVirtualWorld(playerid2), color1, color2, 0, 5, 0, -1, -1);
	format(string, sizeof string, "%s creó [M-%d C1-%d C2-%d] a %s", NombreDeCuenta(playerid), modelid, color1, color2, NombreDeCuenta(playerid2));
	SendPlayerChatMessage(playerid, 0xA2DC35FF, string);
	Log("f_logs/shoplog.log", string);
	return 1;
}
alias:darauto("shopveh", "crearauto");

cmd:editarvehiculo(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new vehicleid, color1, color2, string[160];
	if (sscanf(params, "ddd", vehicleid, color1, color2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarvehiculo (VehiculoID) (Color1) (Color2)");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		format(string, sizeof string, "Cambiaste el color del %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
		SendPlayerChatMessage(playerid, ColorList[color1], string);
		ChangeVehicleColor(vehicleid, color1, color2);
		InfoVehiculo[v][vColor_1] = color1;
		InfoVehiculo[v][vColor_2] = color2;
		guardar_int_mysql("vehiculos", "Color_1", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vColor_1]);
		guardar_int_mysql("vehiculos", "Color_2", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vColor_2]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese vehículo no está spawneado o no existe.");
	return 1;
}

new actual_vehModel[MAX_PLAYERS];
new actual_vehColor1[MAX_PLAYERS];
new actual_vehColor2[MAX_PLAYERS];

cmd:borrarvehiculo(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new vehicleid, string[160];
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borrarvehiculo (VehiculoID) [para saber ID exacta acercate al vehículo con /dl]");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[v][vTipo] == 0 && InfoVehiculo[v][vNegocio] == 0 && InfoVehiculo[v][vTrabajo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes borrar vehículos de usuarios.");
		format(string, sizeof string, "Borraste %s de %s.", GetNameVehicle(InfoVehiculo[v][vModelo]), InfoVehiculo[v][vPropietario]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		borrar_vehiculo(v);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese vehículo no está spawneado o no existe.");
	return 1;
}

cmd:crearvehiculo(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new modelid, color1, color2;
	if (sscanf(params, "ddd", modelid, color1, color2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearvehiculo (ModeloID) (Color1) (Color2)");
	if (color1 < 0 || color1 > 250) { SendPlayerChatMessage(playerid, COLOR_GREY, "El color 1 no puede super el ID 250."); return 1; }
	if (color2 < 0 || color2 > 250) { SendPlayerChatMessage(playerid, COLOR_GREY, "El color 2 no puede super el ID 250."); return 1; }
	if (modelid < 400 || modelid > 611) { SendPlayerChatMessage(playerid, COLOR_GREY, "Modelo inválido, intenta entre 400 y 611."); return 1; }
	Dialog_Show(playerid, ShowCreateVehicle, DIALOG_STYLE_LIST, "Elige donde crear el vehículo", "Facción\nVIP\nRenta\nNegocio\nTrabajo", "Continuar", "Salir");
	actual_vehModel[playerid] = modelid;
	actual_vehColor1[playerid] = color1;
	actual_vehColor2[playerid] = color2;
	return 1;
}