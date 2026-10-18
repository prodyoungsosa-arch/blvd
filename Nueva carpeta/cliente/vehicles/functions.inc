GetVehicleInterior2(vehicleid) return interior_veh[vehicleid];

stock SetVehicleInterior(vehicleid, interior = 0)
{
	LinkVehicleToInterior(vehicleid, interior);
	interior_veh[vehicleid] = interior;
}

stock VehicleToPoint(Float:radi, vehicleid, Float:x, Float:y, Float:z)
{
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetVehiclePos(vehicleid, oldposx, oldposy, oldposz);
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
	{
		return 1;
	}
	return 0;
}


LockPlayerVehicle(vehicle)
{
	LockStatus[vehicle] = 1;
	new vParamArr[7];
	GetVehicleParamsEx(vehicle, vParamArr[0], vParamArr[1], vParamArr[2], vParamArr[3], vParamArr[4], vParamArr[5], vParamArr[6]);
	return SetVehicleParamsEx(vehicle, vParamArr[0], vParamArr[1], vParamArr[2], VEHICLE_PARAMS_ON, vParamArr[4], vParamArr[5], vParamArr[6]);
}

UnLockPlayerVehicle(vehicle)
{
	LockStatus[vehicle] = 0;
	new vParamArr[7];
	GetVehicleParamsEx(vehicle, vParamArr[0], vParamArr[1], vParamArr[2], vParamArr[3], vParamArr[4], vParamArr[5], vParamArr[6]);
	return SetVehicleParamsEx(vehicle, vParamArr[0], vParamArr[1], vParamArr[2], VEHICLE_PARAMS_OFF, vParamArr[4], vParamArr[5], vParamArr[6]);
}

funcion SetVehicleEngine(vehicleid, playerid)
{
	check_motor[playerid] = 0;
	new engine, lights, alarm, doors, bonnet, boot, objective, string1[128];
    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
    if (engine == VEHICLE_PARAMS_ON)
	{
		format(string1, sizeof(string1), "* {player:%d} apaga el motor de su vehiculo.", playerid);
		ProxDetector(30.0, playerid, string1, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF,lights,alarm,doors,bonnet,boot,objective);
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Motor a sido apagado con éxito.");
		arr_Engine{vehicleid} = 0;
	}
    else if(engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET)
	{
		new Float: f_vHealth;
		GetVehicleHealth(vehicleid, f_vHealth);
		if(f_vHealth < 350.0) return ShowInfoForPlayer(playerid, "El motor de este vehiculo esta averiado.", 2000);
	    if(veh_gasolina[vehicleid] <= 0) return ShowInfoForPlayer(playerid, "El vehiculo no tiene gasolina.", 2000);
		SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_ON,lights,alarm,doors,bonnet,boot,objective);
		arr_Engine{vehicleid} = 1;
		format(string1, sizeof(string1), "* {player:%d} arranca el motor de su vehiculo.", playerid);
		ProxDetector(30.0, playerid, string1, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		ShowInfoForPlayer(playerid, "~g~~h~Encendiendo...", 2000);
	}
	return 1;
}

SetVehicleLights(vehicleid, playerid)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
    if(lights == VEHICLE_PARAMS_ON)
	{
		SetVehicleParamsEx(vehicleid,engine,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective);
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Luces del vehiculo fueron apagadas.");
	}
    else if(lights == VEHICLE_PARAMS_OFF || lights == VEHICLE_PARAMS_UNSET)
	{
		SetVehicleParamsEx(vehicleid,engine,VEHICLE_PARAMS_ON,alarm,doors,bonnet,boot,objective);
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Luces del vehículo encendidas con éxito. Puedes usar los intermitentes.");
	}
	return 1;
}

SetVehicleHood(vehicleid, playerid)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
    GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
    if(bonnet == VEHICLE_PARAMS_ON)
	{
		SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,VEHICLE_PARAMS_OFF,boot,objective);
		ShowInfoForPlayer(playerid, "El capo del vehiculo fue cerrado.", 2000);
	}
    else if(bonnet == VEHICLE_PARAMS_OFF || bonnet == VEHICLE_PARAMS_UNSET)
	{
		SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,VEHICLE_PARAMS_ON,boot,objective);
		ShowInfoForPlayer(playerid, "El capo del vehiculo fue abierto.", 2000);
	}
	return 1;
}


stock GetNearestVehicle(playerid)
{
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    new closestVehicle = INVALID_VEHICLE_ID;
    new Float:minDist = 9999.0;

    for (new i = 1; i <= MAX_VEHICLES; i++)
    {
        if (!IsVehicleStreamedIn(i, playerid)) continue;

        new Float:vx, Float:vy, Float:vz;
        GetVehiclePos(i, vx, vy, vz);

        new Float:dist = floatsqroot((vx - px) * (vx - px) + (vy - py) * (vy - py) + (vz - pz) * (vz - pz));
        if (dist < minDist && dist <= 10.0)
        {
            minDist = dist;
            closestVehicle = i;
        }
    }
    return closestVehicle;
}
funcion SacarMaletero(playerid, vehicleid, id)
{
	ActualizarManos(playerid);
	new Bonnet = InfoVehiculo[vehicleid][vMaletero][id], Cant = InfoVehiculo[vehicleid][vMaleteroCant][id], string[128];
	if(Bonnet == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ésta ranura se encuentra vacía.");
	if(Bonnet == 131)
	{
		if(InfoPersonaje[playerid][pManoDerecha] == 0 && InfoPersonaje[playerid][pManoIzquierda] == 0)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		} else return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes poseer ambas manos vacías.");
	}
	new weaponid = InfoInventario[InfoVehiculo[vehicleid][vMaletero][id]][IDArma];
	if (InfoPersonaje[playerid][pHorasOn] < 2)
	{
		if (weaponid >= 22 && weaponid <= 34)
		{
 			SendPlayerChatMessage(playerid, COLOR_GREY, "Tienes restricción de armas por seis horas.");
 			return 1;
    	}
	}
	if(InfoPersonaje[playerid][pManoDerecha] == 0)
	{

		if(InfoInventario[Bonnet][IDArma] > 0)
		{
			new arma = InfoInventario[Bonnet][IDArma], municion = Cant;
			if(municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
		}
		InfoPersonaje[playerid][pManoDerecha] = Bonnet;
		InfoPersonaje[playerid][pManoDerechaCant] = Cant;
		mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", Bonnet, Cant, InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, string);
		PonerObjeto(playerid, 1, Bonnet);
		InfoVehiculo[vehicleid][vMaletero][id] = 0;
		InfoVehiculo[vehicleid][vMaleteroCant][id] = 0;
		mysql_format(db_samp, string, sizeof string, "UPDATE vehiculos SET Maletero%d = 0, MaleteroCant%d = 0 WHERE ID = '%d'", id+1, id+1, InfoVehiculo[vehicleid][vID_sql]);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "%s saca %s del %s (SQL %d).", GetNameFormat(playerid), InfoInventario[Bonnet][NombreObjeto], GetNameVehicle(InfoVehiculo[vehicleid][vModelo]), InfoVehiculo[vehicleid][vID_sql]);
		Log("f_logs/Maletero.log", string);
		PlayerMaleteroVeh[playerid] = 0;
		return 1;
	}
	else if(InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = Bonnet;
		InfoPersonaje[playerid][pManoIzquierdaCant] = Cant;
		mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'", Bonnet, Cant, InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, string);
		PonerObjeto(playerid, 2, Bonnet);
		InfoVehiculo[vehicleid][vMaletero][id] = 0;
		InfoVehiculo[vehicleid][vMaleteroCant][id] = 0;
		mysql_format(db_samp, string, sizeof string, "UPDATE vehiculos SET Maletero%d = 0, MaleteroCant%d = 0 WHERE ID = '%d'", id+1, id+1, InfoVehiculo[vehicleid][vID_sql]);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "%s saca %s del %s (SQL %d).", GetNameFormat(playerid), InfoInventario[Bonnet][NombreObjeto], GetNameVehicle(InfoVehiculo[vehicleid][vModelo]), InfoVehiculo[vehicleid][vID_sql]);
		Log("f_logs/Maletero.log", string);
		PlayerMaleteroVeh[playerid] = 0;
	} else return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
	return 1;
}
funcion GuardarMaletero(playerid, vehicleid, mano)
{
	ActualizarManos(playerid);
	if(mano == 1)
	{
		if(InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu mano derecha.");
		new Mano = InfoPersonaje[playerid][pManoDerecha], Cant = InfoPersonaje[playerid][pManoDerechaCant], string[128], BonnetLibre;
		if(InfoInventario[Mano][IDArma] > 0) //- Si es arma
		{
			if(IntentoChitearBalas(playerid)) return 1;
			Cant = InfoPersonaje[playerid][pManoDerechaCant];
			RemovePlayerWeapon(playerid, InfoInventario[Mano][IDArma]);
		}
		for(new x = 0; x < InfoVehiculo[vehicleid][vMaxMaletero]; x++)
		{
			if(InfoVehiculo[vehicleid][vMaletero][x] == 0)
			{
				if(InfoPersonaje[playerid][pManoDerecha] == 131) SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				InfoVehiculo[vehicleid][vMaletero][x] = Mano;
				InfoVehiculo[vehicleid][vMaleteroCant][x] = Cant;
				mysql_format(db_samp, string, sizeof string, "UPDATE vehiculos SET Maletero%d = '%d', MaleteroCant%d = '%d' WHERE ID = '%d'", x+1, Mano, x+1, Cant, InfoVehiculo[vehicleid][vID_sql]);
				mysql_tquery(db_samp, string);
				RemovePlayerAttachedObject(playerid, 7);
				InfoPersonaje[playerid][pManoDerecha] = 0;
				InfoPersonaje[playerid][pManoDerechaCant] = 0;
				mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
				mysql_tquery(db_samp, string);
				format(string, sizeof string, "%s guarda %s en el %s (SQL %d).", GetNameFormat(playerid), InfoInventario[Mano][NombreObjeto], GetNameVehicle(InfoVehiculo[vehicleid][vModelo]), InfoVehiculo[vehicleid][vID_sql]);
				Log("f_logs/Maletero.log", string);
				BonnetLibre = 1;
				PlayerMaleteroVeh[playerid] = 0;
				return 1;
			}
		}
		if(BonnetLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Todas las ranuras del maletero están ocupadas.");
	}
	else if(mano == 2)
	{
		if(InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu mano izquierda.");
		new Mano = InfoPersonaje[playerid][pManoIzquierda], Cant = InfoPersonaje[playerid][pManoIzquierdaCant], string[128], BonnetLibre;
		for(new x = 0; x < InfoVehiculo[vehicleid][vMaxMaletero]; x++)
		{
			if(InfoVehiculo[vehicleid][vMaletero][x] == 0)
			{
				if(InfoPersonaje[playerid][pManoIzquierda] == 131) SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				InfoVehiculo[vehicleid][vMaletero][x] = Mano;
				InfoVehiculo[vehicleid][vMaleteroCant][x] = Cant;
				mysql_format(db_samp, string, sizeof string, "UPDATE vehiculos SET Maletero%d = '%d', MaleteroCant%d = '%d' WHERE ID = '%d'", x+1, Mano, x+1, Cant, InfoVehiculo[vehicleid][vID_sql]);
				mysql_tquery(db_samp, string);
				RemovePlayerAttachedObject(playerid, 8);
				InfoPersonaje[playerid][pManoIzquierda] = 0;
				InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
				mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
				mysql_tquery(db_samp, string);
				format(string, sizeof string, "%s guarda %s en el %s (SQL %d).", GetNameFormat(playerid), InfoInventario[Mano][NombreObjeto], GetNameVehicle(InfoVehiculo[vehicleid][vModelo]), InfoVehiculo[vehicleid][vID_sql]);
				Log("f_logs/Maletero.log", string);
				BonnetLibre = 1;
				PlayerMaleteroVeh[playerid] = 0;
				return 1;
			}
		}
		if(BonnetLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Todas las ranuras del maletero están ocupadas.");
	}
	return 1;
}

funcion VerMaletero(playerid, vehicleid)
{
	ActualizarManos(playerid);
	new dialog[1024], string[128];
	for(new i = 0; i < InfoVehiculo[vehicleid][vMaxMaletero]; i++)
	{
		new Bonnet = InfoVehiculo[vehicleid][vMaletero][i];
		if(Bonnet == 0) format(string, sizeof(string), "\n{b0b0b0}Vacío");
		else format(string, sizeof(string), "\n{EBEBEB}%s", slot_objeto(Bonnet, InfoVehiculo[vehicleid][vMaleteroCant][i]));
		strcat(dialog, string);
	}
	format(string, sizeof(string), "\n{eb4040}--------------------");
	strcat(dialog, string);
	if(InfoPersonaje[playerid][pManoDerecha] == 0) format(string, sizeof(string), "\n{b0b0b0}M. Derecha: vacía");
	else format(string, sizeof(string), "\n{EBEBEB}Mano derecha: %s", slot_objeto(InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant]));
	strcat(dialog, string);
	if(InfoPersonaje[playerid][pManoIzquierda] == 0) format(string, sizeof(string), "\n{b0b0b0}M. Izquierda: vacía");
	else format(string, sizeof(string), "\n{EBEBEB}Mano izquierda: %s", slot_objeto(InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant]));
	strcat(dialog, string);
	Dialog_Show(playerid, MaleteroMenu, DIALOG_STYLE_LIST, "Maletero", dialog, "Seleccionar", "Cancelar");
	return 1;
}
funcion desbugdrive(playerid, arma)
	SetPlayerArmedWeapon(playerid, arma);
	
vehiculo_avion(modelo)
{
	new Avioneta[] = {592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469};
	for(new i = 0; i < sizeof(Avioneta); i++) { if(modelo == Avioneta[i]) return 1; }
	return 0;
}

vehiculo_bote(modelo)
{
	new Boats[] = {472, 473, 493, 484, 430, 454, 453, 452, 446};
	for(new i = 0; i < sizeof(Boats); i++) { if(modelo == Boats[i]) return 1; }
	return 0;
}

SetVehicleExVirtualWorld(vehicleid, vw)
{
	SetVehicleVirtualWorld(vehicleid, vw);
	Loop(id, totalvehiculos, 0) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		Colocar_Objeto(id, vehicleid);
	}
}

funcion SetVehicleMatricula(carid) {
	if(!GetVehicleModel(carid)) return 1;
	new matricula[24];
	format(matricula, sizeof(matricula), "LS-%d", carid);
	SetVehicleNumberPlate(carid, matricula);
	return 1;
}

CountVehs(type)
{
	new count = 0;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == type)
	{
		count++;
	}
	return count;
}

verificar_id_vehiculo(vehicleid)
{
	new id = -1;
	Loop(x, totalvehiculos, 1) if (InfoVehiculo[x][vIG_id] == vehicleid)
	{
		id = x;
		break;
	}
	return id;
}

PermisosVehiculo(playerid, vehicleid)
{
	if (!IsPlayerConnected(playerid)) return -1;
	if (!GetVehicleModel(vehicleid)) return -1;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid && InfoVehiculo[v][vTipo] == 0)
	{
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[v][vPropietario], true) == 0) { return v; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[v][vCompartida1], true) == 0) { return v; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[v][vCompartida2], true) == 0) { return v; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[v][vCompartida3], true) == 0) { return v; }
	}
	return -1;
}

llaves_vehiculo(playerid, vehicleid)
{
	if (!IsPlayerConnected(playerid)) return -1;
	if (!GetVehicleModel(vehicleid)) return -1;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid && InfoVehiculo[v][vTipo] == 0)
	{
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[v][vPropietario], true) == 0)
		{
			return v;
		}
	}
	return -1;
}

Vehiculo_LSPD(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 1) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_FBI(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 2) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_USMC(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 3) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_LSCSD(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 4) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_GOB(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 5) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_LSFD(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 6) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_SADOC(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 6) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

Vehiculo_Renta(vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vTipo] == 600) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

llaves_lider(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] != 0)
	{
		if (InfoPersonaje[playerid][pLider] == InfoVehiculo[id][vTipo]) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pMiembro] == InfoVehiculo[id][vTipo])
			if (InfoPersonaje[playerid][pRango] == InfoFaccion[InfoPersonaje[playerid][pMiembro]][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

llaves_faccion(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] != 0)
	{
		if (InfoPersonaje[playerid][pMiembro] == InfoVehiculo[id][vTipo]) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

llaves_negocio(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vNegocio] != 0)
	{
		if (PermisosNegocio(playerid, InfoVehiculo[id][vNegocio]) != 0) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

llaves_trabajo(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTrabajo] != 0)
	{
		if (IsPlayerContrato(playerid, InfoVehiculo[id][vTrabajo])) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

llaves_renta(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] == 600)
	{
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[id][vRentaDueno], true) == 0)
		{
			return 1;
		}
		if (GetPlayerAdmin(playerid, 4) != 0) return 1;
	}
	return 0;
}

llaves_vip(playerid, vehicleid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] != 0)
	{
		if (InfoCuenta[playerid][jVIP] != 0) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

AnibleVeh(id)
{
	if (InfoVehiculo[id][vTipo] == 1) return 1;
	if (InfoVehiculo[id][vTipo] == 2) return 1;
	if (InfoVehiculo[id][vTipo] == 3) return 1;
	if (InfoVehiculo[id][vTipo] == 4) return 1;
	return 0;
}

EstereoConductor(playerid, const music[])
{
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		foreach(new playerid2: Player) if (IsPlayerConnectedEx(playerid2) && GetPlayerVehicleID(playerid2) == vehicleid && InfoPersonaje[playerid][pTogMusic] == 1)
		{
			if (TipoAudio[playerid2] == 0 || TipoAudio[playerid2] == 3)
			{
				TipoAudio[playerid2] = 3;
				PlayAudioStreamForPlayer(playerid2, music);
			}
		}
		alm(veh_music[vehicleid], music);
	}
	return 1;
}

RespawnNearbyVehicles(playerid, Float:radi)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    for(new i=1; i<GetVehiclePoolSize(); i++)
    {
        if(GetVehicleModel(i))
        {
            new Float:posx, Float:posy, Float:posz;
            new Float:tempposx, Float:tempposy, Float:tempposz;
            GetVehiclePos(i, posx, posy, posz);
            tempposx = (posx - x);
            tempposy = (posy - y);
            tempposz = (posz - z);
            if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi)))
            {
				SetVehicleToRespawn(i);
            }
        }
    }
}

stock IsSeatAvailable(vehicleid, seat)
{
	new carmodel = GetVehicleModel(vehicleid);
	for (new i = 0; i < sizeof( OneSeatVehicles ); i++ )
	{
	    if( carmodel == OneSeatVehicles[i] ) return 0;
	}
	foreach(Player, i)
	{
	    if(GetPlayerVehicleID(i) == vehicleid && GetPlayerVehicleSeat(i) == seat) return 0;
	}
	return 1;
}

VehicleSpawnCount(playerid)
{
	new cars = 0;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[id][vPropietario], true) == 0 && InfoVehiculo[id][vSpawned] != 0)
	{ cars++; }
	return cars;
}

SpawnVehiculos(playerid)
{
	new carsamount = VehicleSpawnCount(playerid);
	if (InfoCuenta[playerid][jVIP] == 0 && carsamount >= 2)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios normales sólo pueden tener 2 vehículos spawneados.");
		return 1;
	}
	if (InfoCuenta[playerid][jVIP] == 1 && carsamount >= 5)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios VIP Level 1 sólo pueden tener 5 vehículos spawneados.");
		return 1;
	}
	if (InfoCuenta[playerid][jVIP] == 2 && carsamount >= 10)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios VIP Level 2 sólo pueden tener 10 vehículos spawneados.");
		return 1;
	}
	return 2;
}

crear_vehiculo(playerid, modelid, Float: x, Float: y, Float: z, Float: angle, vehint, vehvw, color1, color2, price, maxeMaletero, type, negocio, trabajo)
{
	Loop(vid, MAX_VEHICULOS, 1) if (!InfoVehiculo[vid][vModelo])
	{
	    if (negocio != -1)
	    {
			new golfm[129];
			format(golfm, sizeof golfm, "Negocio_%d", negocio);
			alm(InfoVehiculo[vid][vPropietario], golfm);
			InfoVehiculo[vid][vNegocio] = negocio;
	    }
	    else if (trabajo != -1)
	    {
			new golfm[129];
			format(golfm, sizeof golfm, "Trabajo_%d", trabajo);
			alm(InfoVehiculo[vid][vPropietario], golfm);
			InfoVehiculo[vid][vTrabajo] = trabajo;
	    }
	    else
	    {
			InfoVehiculo[vid][vNegocio] = 0;
			InfoVehiculo[vid][vTrabajo] = 0;
			if (playerid != -1)
			{
				alm(InfoVehiculo[vid][vPropietario], InfoPersonaje[playerid][pNombre_Apellido]);
			}
			else
			{
				switch (type)
				{
					case 1..50:
					{
						if (InfoFaccion[type][fTipo] != 0)
						{
							alm(InfoVehiculo[vid][vPropietario], InfoFaccion[type][fLogo]);
						}
					}
					case 200: alm(InfoVehiculo[vid][vPropietario], "VIP");
					case 300: alm(InfoVehiculo[vid][vPropietario], "STAFF");
					case 600: alm(InfoVehiculo[vid][vPropietario], "RENTA");
					default: alm(InfoVehiculo[vid][vPropietario], "SERVER");
				}
			}
		}
		alm(InfoVehiculo[vid][vNombre], GetNameVehicle(modelid));
		InfoVehiculo[vid][vTipo] = type;
		InfoVehiculo[vid][vModelo] = modelid;
		InfoVehiculo[vid][vPosicionX] = x;
		InfoVehiculo[vid][vPosicionY] = y;
		InfoVehiculo[vid][vPosicionZ] = z;
		InfoVehiculo[vid][vPosicionR] = angle;
		InfoVehiculo[vid][vInterior] = vehint;
		InfoVehiculo[vid][vVirtualWorld] = vehvw;
		InfoVehiculo[vid][vVida] = 1000.0;
		InfoVehiculo[vid][vDanioSuperficie] = 0;
		InfoVehiculo[vid][vDanioPuertas] = 0;
		InfoVehiculo[vid][vDanioLuces] = 0;
		InfoVehiculo[vid][vDanioRuedas] = 0;
		InfoVehiculo[vid][vGasolina] = 200;
		InfoVehiculo[vid][vColor_1] = color1;
		InfoVehiculo[vid][vColor_2] = color2;
		InfoVehiculo[vid][vPaintJob] = -1;
		InfoVehiculo[vid][vSeguro] = 0;
		InfoVehiculo[vid][vPrecio] = price;
		InfoVehiculo[vid][vEmbargo] = 0;
		InfoVehiculo[vid][vMulta] = 0;
		if (price >= 1 && price <= 100)
		{
			InfoVehiculo[vid][vPremium] = 1;
		}
		InfoVehiculo[vid][vMaxMaletero] = maxeMaletero;
		Loop(m, MAX_MODIFICACIONES, 0) { InfoVehiculo[vid][vModificacion][m] = 0; }
		Loop(m, 10, 0) { InfoVehiculo[vid][vMaletero][m] = 0; InfoVehiculo[vid][vMaleteroCant][m] = 0; }
		// create vehicle
		new vehicleid = CreateVehicle(modelid, x, y, z, angle, color1, color2, -1);
		InfoVehiculo[vid][vIG_id] = vehicleid;
		InfoVehiculo[vid][vSpawned] = 1;
		InfoVehiculo[vid][vTimeSave] = 0;
		SetVehicleMatricula(vehicleid);
		veh_gasolina[vehicleid] = InfoVehiculo[vid][vGasolina];
		SetVehicleVirtualWorld(vehicleid, InfoVehiculo[vid][vVirtualWorld]);
		SetVehicleInterior(vehicleid, InfoVehiculo[vid][vInterior]);
		if (playerid != -1)
		{
			SetPlayerPosEx(playerid, x, y, z);
			PutPlayerInVehicleEx(playerid, vehicleid, 0);
		}
		new query[2050];
		//opción idsql ya creada.
		if (InfoVehiculo[vid][vID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET Nombre = '%e', Propietario = '%e', Tipo = '%d', Negocio = '%d', Trabajo = '%d', Modelo = '%d', Posicion_X = '%f', Posicion_Y = '%f', Posicion_Z = '%f', Posicion_R = '%f', Interior = '%d', VirtualWorld = '%d', Vida = '%f', \
			Gasolina = '%d', Color_1 = '%d', Color_2 = '%d', Precio = '%d', MaxMaletero = '%d', Premium = '%d' WHERE ID = '%d'",
			InfoVehiculo[vid][vNombre],
			InfoVehiculo[vid][vPropietario],
			InfoVehiculo[vid][vTipo],
			InfoVehiculo[vid][vNegocio],
			InfoVehiculo[vid][vTrabajo],
			InfoVehiculo[vid][vModelo],
			InfoVehiculo[vid][vPosicionX],
			InfoVehiculo[vid][vPosicionY],
			InfoVehiculo[vid][vPosicionZ],
			InfoVehiculo[vid][vPosicionR],
			InfoVehiculo[vid][vInterior],
			InfoVehiculo[vid][vVirtualWorld],
			InfoVehiculo[vid][vVida],
			InfoVehiculo[vid][vGasolina],
			InfoVehiculo[vid][vColor_1],
			InfoVehiculo[vid][vColor_2],
			InfoVehiculo[vid][vPrecio],
			InfoVehiculo[vid][vMaxMaletero],
			InfoVehiculo[vid][vPremium],
			InfoVehiculo[vid][vID_sql]);
			mysql_tquery(db_samp, query);
			vid = MAX_VEHICULOS;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO vehiculos (Nombre, Propietario, Tipo, Negocio, Trabajo, Modelo, Posicion_X, Posicion_Y, Posicion_Z, Posicion_R, Interior, VirtualWorld, Vida, Gasolina, Color_1, \
		Color_2, Precio, MaxMaletero, Premium) VALUES ('%e', '%e', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%d', '%d', '%d', '%d', '%d', '%d')",
		InfoVehiculo[vid][vNombre],
		InfoVehiculo[vid][vPropietario],
		InfoVehiculo[vid][vTipo],
		InfoVehiculo[vid][vNegocio],
		InfoVehiculo[vid][vTrabajo],
		InfoVehiculo[vid][vModelo],
		InfoVehiculo[vid][vPosicionX],
		InfoVehiculo[vid][vPosicionY],
		InfoVehiculo[vid][vPosicionZ],
		InfoVehiculo[vid][vPosicionR],
		InfoVehiculo[vid][vInterior],
		InfoVehiculo[vid][vVirtualWorld],
		InfoVehiculo[vid][vVida],
		InfoVehiculo[vid][vGasolina],
		InfoVehiculo[vid][vColor_1],
		InfoVehiculo[vid][vColor_2],
		InfoVehiculo[vid][vPrecio],
		InfoVehiculo[vid][vMaxMaletero],
		InfoVehiculo[vid][vPremium]);
		mysql_tquery(db_samp, query, "CreateVehicleUser", "i", vid);
		vid = MAX_VEHICULOS;
	}
	return 1;
}

MostrarVehiculo(id, type)
{
	if (InfoVehiculo[id][vModelo] != 0)
	{
		if (type == 1) // última ubicación
		{
			new Coche;
			Coche = CreateVehicle(InfoVehiculo[id][vModelo], InfoVehiculo[id][vEndPosicionX], InfoVehiculo[id][vEndPosicionY], InfoVehiculo[id][vEndPosicionZ], InfoVehiculo[id][vEndPosicionR], InfoVehiculo[id][vColor_1], InfoVehiculo[id][vColor_2], -1, InfoVehiculo[id][vSirena]);
			SetVehicleInterior(Coche, InfoVehiculo[id][vEndInterior]);
			SetVehicleExVirtualWorld(Coche, InfoVehiculo[id][vVirtualWorld]);
			InfoVehiculo[id][vIG_id] = Coche;
			alm(veh_music[Coche], "nadauwu");
			InfoVehiculo[id][vSpawned] = 1;
			InfoVehiculo[id][vTimeSave] = 0;
			SetVehicleMatricula(Coche);
			veh_gasolina[Coche] = InfoVehiculo[id][vGasolina];
			if (InfoVehiculo[id][vModelo] == 528 || InfoVehiculo[id][vModelo] == 427) SetVehicleHealth(Coche, 5000.0);
			else SetVehicleHealth(Coche, InfoVehiculo[id][vVida]);
			UpdateVehicleDamageStatus(Coche, InfoVehiculo[id][vDanioSuperficie], InfoVehiculo[id][vDanioPuertas], InfoVehiculo[id][vDanioLuces], InfoVehiculo[id][vDanioRuedas]);
			if (InfoVehiculo[id][vSeguro] != 0) LockPlayerVehicle(Coche);
			Load_Mods(id);
			if (!isnull(InfoVehiculo[id][vCallSign]))
			{
				if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
				{
					DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
					InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
				}
				InfoVehiculo[id][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[id][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, Coche);
			}
		}
		else if (type == 2) // donde estaciono
		{
			new Coche;
			Coche = CreateVehicle(InfoVehiculo[id][vModelo], InfoVehiculo[id][vPosicionX], InfoVehiculo[id][vPosicionY], InfoVehiculo[id][vPosicionZ], InfoVehiculo[id][vPosicionR], InfoVehiculo[id][vColor_1], InfoVehiculo[id][vColor_2], -1, InfoVehiculo[id][vSirena]);
			SetVehicleInterior(Coche, InfoVehiculo[id][vInterior]);
			SetVehicleExVirtualWorld(Coche, InfoVehiculo[id][vVirtualWorld]);
			alm(veh_music[Coche], "nadauwu");
			InfoVehiculo[id][vIG_id] = Coche;
			InfoVehiculo[id][vSpawned] = 1;
			InfoVehiculo[id][vTimeSave] = 0;
			SetVehicleMatricula(Coche);
			veh_gasolina[Coche] = InfoVehiculo[id][vGasolina];
			if (InfoVehiculo[id][vModelo] == 528 || InfoVehiculo[id][vModelo] == 427) SetVehicleHealth(Coche, 5000.0);
			else SetVehicleHealth(Coche, InfoVehiculo[id][vVida]);
			UpdateVehicleDamageStatus(Coche, InfoVehiculo[id][vDanioSuperficie], InfoVehiculo[id][vDanioPuertas], InfoVehiculo[id][vDanioLuces], InfoVehiculo[id][vDanioRuedas]);
			if (InfoVehiculo[id][vSeguro] != 0) LockPlayerVehicle(Coche);
			Load_Mods(id);
			if (!isnull(InfoVehiculo[id][vCallSign]))
			{
				if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
				{
					DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
					InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
				}
				InfoVehiculo[id][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[id][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, Coche);
			}
		}
	}
}

Load_Mods(veh)
{
	new vehicleid = InfoVehiculo[veh][vIG_id];
	if (InfoVehiculo[veh][vPaintJob] != -1) ChangeVehiclePaintjob(vehicleid, InfoVehiculo[veh][vPaintJob]);
	ChangeVehicleColor(vehicleid, InfoVehiculo[veh][vColor_1], InfoVehiculo[veh][vColor_2]);
	Loop(m, MAX_MODIFICACIONES, 0) { AddVehicleComponent(vehicleid, InfoVehiculo[veh][vModificacion][m]); }
}

OcultarVehiculo(id)
{
	if (id != 0)
	{
		if (!IsVehicleBusy(InfoVehiculo[id][vIG_id])) Quit_Vehicles(id);
		else InfoVehiculo[id][vTimeSave] = 5;
	}
}

SecuenciaVehiculos(playerid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[id][vPropietario], true) == 0)
	{
		if (InfoVehiculo[id][vModelo] != 0 && InfoVehiculo[id][vEmbargo] == 0 && InfoVehiculo[id][vSpawned] != 0)
		{
			InfoVehiculo[id][vTimeSave] = 20;
		}
	}
}

ReiniciarSecuencia(playerid)
{
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[id][vPropietario], true) == 0)
	{
		if (InfoVehiculo[id][vModelo] != 0 && InfoVehiculo[id][vEmbargo] == 0 && InfoVehiculo[id][vSpawned] != 0)
		{
			InfoVehiculo[id][vTimeSave] = 0;
		}
	}
}

Quit_Vehicles(id)
{
	if (InfoVehiculo[id][vModelo] == 0) return 1;
	if (InfoVehiculo[id][vSpawned] == 0) return 1;
	new vehicleid = InfoVehiculo[id][vIG_id], oldfuel, query[412];
	if (LockStatus[vehicleid] != 0) LockStatus[vehicleid] = 0;
	alm(veh_music[vehicleid], "nadauwu");
	oldfuel = veh_gasolina[vehicleid];
	InfoVehiculo[id][vGasolina] = oldfuel;
	GetVehicleHealth(vehicleid, InfoVehiculo[id][vVida]);
	GetVehicleDamageStatus(vehicleid, InfoVehiculo[id][vDanioSuperficie], InfoVehiculo[id][vDanioPuertas], InfoVehiculo[id][vDanioLuces], InfoVehiculo[id][vDanioRuedas]);
	GetVehiclePos(vehicleid, InfoVehiculo[id][vEndPosicionX], InfoVehiculo[id][vEndPosicionY], InfoVehiculo[id][vEndPosicionZ]);
	GetVehicleZAngle(vehicleid, InfoVehiculo[id][vEndPosicionR]);
	InfoVehiculo[id][vEndInterior] = GetVehicleInterior2(vehicleid);
	InfoVehiculo[id][vEndVirtualWorld] = GetVehicleVirtualWorld(vehicleid);
	ActualizarMods(id);
	DestroyVehicle(vehicleid);
	//update
	mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET End_Posicion_X = '%f', End_Posicion_Y = '%f', End_Posicion_Z = '%f', End_Posicion_R = '%f', End_Interior = '%d', End_VirtualWorld = '%d', Vida = '%f', \
	DanioSuperficie = '%d', DanioPuertas = '%d', DanioLuces = '%d', DanioRuedas = '%d', Gasolina = '%d' WHERE ID = '%d'",
	InfoVehiculo[id][vEndPosicionX],
	InfoVehiculo[id][vEndPosicionY],
	InfoVehiculo[id][vEndPosicionZ],
	InfoVehiculo[id][vEndPosicionR],
	InfoVehiculo[id][vEndInterior],
	InfoVehiculo[id][vEndVirtualWorld],
	InfoVehiculo[id][vVida],
	InfoVehiculo[id][vDanioSuperficie],
	InfoVehiculo[id][vDanioPuertas],
	InfoVehiculo[id][vDanioLuces],
	InfoVehiculo[id][vDanioRuedas],
	InfoVehiculo[id][vGasolina],
	InfoVehiculo[id][vID_sql]);
	mysql_tquery(db_samp, query);
	//objetos vip
	Loop(x, 5, 0) if (InfoVehiculo[id][vObjModelo][x] != 0)
	{
		if (IsValidDynamicObject(InfoVehiculo[id][vTuneo][x])) DestroyDynamicObject(InfoVehiculo[id][vTuneo][x]);
		InfoVehiculo[id][vTuneo][x] = 0;
	}
	//carsign
	if (!isnull(InfoVehiculo[id][vCallSign]))
	{
		if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
		{
			DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
			InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
		}
	}
	//clear variables
	InfoVehiculo[id][vIG_id] = 0;
	InfoVehiculo[id][vSpawned] = 0;
	InfoVehiculo[id][vMaleteroOn] = 0;
	InfoVehiculo[id][vTimeSave] = 0;
	return 1;
}

ActualizarMods(veh)
{
	if (InfoVehiculo[veh][vEmbargo] == 0)
	{
		new carid = InfoVehiculo[veh][vIG_id], dex_query[64];
		new exhaust, frontbumper, rearbumper, roof, spoilers, sideskirt1, sideskirt2, wheels, hydraulics, nitro, hood, lamps, stereo, ventright, ventleft;
		exhaust = GetVehicleComponentInSlot(carid, CARMODTYPE_EXHAUST);
		frontbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_FRONT_BUMPER);
		rearbumper = GetVehicleComponentInSlot(carid, CARMODTYPE_REAR_BUMPER);
		roof = GetVehicleComponentInSlot(carid, CARMODTYPE_ROOF);
		spoilers = GetVehicleComponentInSlot(carid, CARMODTYPE_SPOILER);
		sideskirt1 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		sideskirt2 = GetVehicleComponentInSlot(carid, CARMODTYPE_SIDESKIRT);
		wheels = GetVehicleComponentInSlot(carid, CARMODTYPE_WHEELS);
		hydraulics = GetVehicleComponentInSlot(carid, CARMODTYPE_HYDRAULICS);
		nitro = GetVehicleComponentInSlot(carid, CARMODTYPE_NITRO);
		hood = GetVehicleComponentInSlot(carid, CARMODTYPE_HOOD);
		lamps = GetVehicleComponentInSlot(carid, CARMODTYPE_LAMPS);
		stereo = GetVehicleComponentInSlot(carid, CARMODTYPE_STEREO);
		ventright = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_RIGHT);
		ventleft = GetVehicleComponentInSlot(carid, CARMODTYPE_VENT_LEFT);
		if (spoilers >= 1000)    InfoVehiculo[veh][vModificacion][0] = spoilers;
		if (hood >= 1000)        InfoVehiculo[veh][vModificacion][1] = hood;
		if (roof >= 1000)        InfoVehiculo[veh][vModificacion][2] = roof;
		if (sideskirt1 >= 1000)  InfoVehiculo[veh][vModificacion][3] = sideskirt1;
		if (lamps >= 1000)       InfoVehiculo[veh][vModificacion][4] = lamps;
		if (nitro >= 1000)       InfoVehiculo[veh][vModificacion][5] = nitro;
		if (exhaust >= 1000)     InfoVehiculo[veh][vModificacion][6] = exhaust;
		if (wheels >= 1000)      InfoVehiculo[veh][vModificacion][7] = wheels;
		if (stereo >= 1000)      InfoVehiculo[veh][vModificacion][8] = stereo;
		if (hydraulics >= 1000)  InfoVehiculo[veh][vModificacion][9] = hydraulics;
		if (frontbumper >= 1000) InfoVehiculo[veh][vModificacion][10] = frontbumper;
		if (rearbumper >= 1000)  InfoVehiculo[veh][vModificacion][11] = rearbumper;
		if (ventright >= 1000)   InfoVehiculo[veh][vModificacion][12] = ventright;
		if (ventleft >= 1000)    InfoVehiculo[veh][vModificacion][13] = ventleft;
		if (sideskirt2 >= 1000)  InfoVehiculo[veh][vModificacion][14] = sideskirt2;
		Loop(x, MAX_MODIFICACIONES, 0)
		{
			format(dex_query, sizeof dex_query, "Modificacion%d", x+1);
			guardar_int_mysql("vehiculos", dex_query, InfoVehiculo[veh][vID_sql], InfoVehiculo[veh][vModificacion][x]);
		}
	}
}

VehicleCount(playerid)
{
	new cars = 0;
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vTipo] == 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[id][vPropietario], true) == 0)
	{ cars++; }
	return cars;
}

stock EsteVehEs(playerid, vehicleid)
{
	if (!IsPlayerConnected(playerid)) return -1;
	if (!GetVehicleModel(vehicleid)) return -1;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		return v;
	}
	return -1;
}

stock GetDistancePlayerVeh(playerid, veh)
{
	new Float:Floats[7];
	GetPlayerPos(playerid, Floats[0], Floats[1], Floats[2]);
	GetVehiclePos(veh, Floats[3], Floats[4], Floats[5]);
	Floats[6] = floatsqroot((Floats[3]-Floats[0])*(Floats[3]-Floats[0])+(Floats[4]-Floats[1])*(Floats[4]-Floats[1])+(Floats[5]-Floats[2])*(Floats[5]-Floats[2]));
	return floatround(Floats[6]);
}

EstaEnBicis(carid)
{
	if(GetVehicleModel(carid) == 509 || GetVehicleModel(carid) == 481 || GetVehicleModel(carid) == 510) { return 1; }
	return 0;
}


eEnvcvehs(carid)
{
	new cvehs[] = { 560, 562, 565, 559, 561, 558, 567 };
	for(new i = 0; i < sizeof cvehs; i++) { if (GetVehicleModel(carid) == cvehs[i]) return 1; }
	return 0;
}

EnMotos_Bicis(carid)
{
	new Bike[] = { 509, 481, 510, 462, 448, 581, 522, 461, 521, 523, 463, 586, 468, 471 };
	for(new i = 0; i < sizeof(Bike); i++) { if(GetVehicleModel(carid) == Bike[i]) return 1; }
	return 0;
}

EstaEnAvion(carid)
{
	new Avioneta[] = {592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469};
	for(new i = 0; i < sizeof(Avioneta); i++) { if(GetVehicleModel(carid) == Avioneta[i]) return 1; }
	return 0;
}

EstaEnBote(carid)
{
	new Boats[] = {472, 473, 493, 484, 430, 454, 453, 452, 446};
	for(new i = 0; i < sizeof(Boats); i++) { if(GetVehicleModel(carid) == Boats[i]) return 1; }
	return 0;
}

borrar_vehiculo(vid)
{
	if (InfoVehiculo[vid][vSpawned] != 0)
	{
		DestroyVehicle(InfoVehiculo[vid][vIG_id]);
		Loop(x, 5, 0) if (InfoVehiculo[vid][vObjModelo][x] != 0)
		{
			if (IsValidDynamicObject(InfoVehiculo[vid][vTuneo][x])) DestroyDynamicObject(InfoVehiculo[vid][vTuneo][x]);
			InfoVehiculo[vid][vTuneo][x] = 0;
		}
		if (!isnull(InfoVehiculo[vid][vCallSign]))
		{
			if (IsValidDynamic3DTextLabel(InfoVehiculo[vid][vOnCallSign]))
			{
				DestroyDynamic3DTextLabel(InfoVehiculo[vid][vOnCallSign]);
				InfoVehiculo[vid][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
			}
		}
	}
	InfoVehiculo[vid][vMaleteroOn] = 0;
	InfoVehiculo[vid][vIG_id] = 0;
	InfoVehiculo[vid][vSpawned] = 0;
	InfoVehiculo[vid][vTimeSave] = 0;
	alm(InfoVehiculo[vid][vNombre], "none");
	alm(InfoVehiculo[vid][vPropietario], "none");
	InfoVehiculo[vid][vTipo] = 0;
	InfoVehiculo[vid][vNegocio] = 0;
	InfoVehiculo[vid][vTrabajo] = 0;
	InfoVehiculo[vid][vModelo] = 0;
	InfoVehiculo[vid][vPosicionX] = 0.0;
	InfoVehiculo[vid][vPosicionY] = 0.0;
	InfoVehiculo[vid][vPosicionZ] = 0.0;
	InfoVehiculo[vid][vPosicionR] = 0.0;
	InfoVehiculo[vid][vVirtualWorld] = 0;
	InfoVehiculo[vid][vInterior] = 0;
	InfoVehiculo[vid][vEndPosicionX] = 0.0;
	InfoVehiculo[vid][vEndPosicionY] = 0.0;
	InfoVehiculo[vid][vEndPosicionZ] = 0.0;
	InfoVehiculo[vid][vEndPosicionR] = 0.0;
	InfoVehiculo[vid][vEndVirtualWorld] = 0;
	InfoVehiculo[vid][vEndInterior] = 0;
	InfoVehiculo[vid][vVida] = 0.0;
	InfoVehiculo[vid][vDanioSuperficie] = 0;
	InfoVehiculo[vid][vDanioPuertas] = 0;
	InfoVehiculo[vid][vDanioLuces] = 0;
	InfoVehiculo[vid][vDanioRuedas] = 0;
	InfoVehiculo[vid][vGasolina] = 200;
	InfoVehiculo[vid][vColor_1] = 1;
	InfoVehiculo[vid][vColor_2] = 1;
	InfoVehiculo[vid][vPaintJob] = -1;
	InfoVehiculo[vid][vSeguro] = 0;
	InfoVehiculo[vid][vPrecio] = 0;
	InfoVehiculo[vid][vEmbargo] = 0;
	InfoVehiculo[vid][vMulta] = 0;
	InfoVehiculo[vid][vPremium] = 0;
	Loop(xd, 5, 0)
	{
		InfoVehiculo[vid][vObjModelo][xd] = 0;
		InfoVehiculo[vid][vObjPosX][xd] = 0;
		InfoVehiculo[vid][vObjPosY][xd] = 0;
		InfoVehiculo[vid][vObjPosZ][xd] = 0;
		InfoVehiculo[vid][vObjRotX][xd] = 0;
		InfoVehiculo[vid][vObjRotY][xd] = 0;
		InfoVehiculo[vid][vObjRotZ][xd] = 0;
		new query43[1028];
		mysql_format(db_samp, query43, sizeof query43, "UPDATE vehiculos SET ObjModelo_%d = '%d', ObjPosX_%d = '%f', ObjPosY_%d = '%f', ObjPosZ_%d = '%f', ObjRotX_%d = '%f', ObjRotY_%d = '%f', ObjRotZ_%d = '%f' WHERE ID = '%d'",
		xd+1, InfoVehiculo[vid][vObjModelo][xd], xd+1, InfoVehiculo[vid][vObjPosX][xd], xd+1, InfoVehiculo[vid][vObjPosY][xd], xd+1, InfoVehiculo[vid][vObjPosZ][xd], xd+1, InfoVehiculo[vid][vObjRotX][xd], xd+1, InfoVehiculo[vid][vObjRotY][xd], xd+1, InfoVehiculo[vid][vObjRotZ][xd], InfoVehiculo[vid][vID_sql]);
		mysql_tquery(db_samp, query43);
	}
	new dex_query[170];
	Loop(x, 10, 0)
	{
		InfoVehiculo[vid][vMaletero][x] = 0;
		InfoVehiculo[vid][vMaleteroCant][x] = 0;
		mysql_format(db_samp, dex_query, sizeof dex_query, "UPDATE vehiculos SET Maletero%d = 0, MaleteroCant%d = 0 WHERE ID = '%d'", x+1, x+1, InfoVehiculo[vid][vID_sql]);
		mysql_tquery(db_samp, dex_query);
	}
	InfoVehiculo[vid][vMaxMaletero] = 5;
	Loop(x, MAX_MODIFICACIONES, 0)
	{
		InfoVehiculo[vid][vModificacion][x] = 0;
		mysql_format(db_samp, dex_query, sizeof dex_query, "UPDATE vehiculos SET Modificacion%d = 0 WHERE ID = '%d'", x+1, InfoVehiculo[vid][vID_sql]);
		mysql_tquery(db_samp, dex_query);
	}
	InfoVehiculo[vid][vSirena] = 0;
	InfoVehiculo[vid][vStereo] = 0;
	new que2ry[3000], query[4000];
	format(que2ry, sizeof que2ry, "UPDATE vehiculos SET Nombre = '%s', Propietario = '%s', Tipo = 0, Modelo = 0, Negocio = 0, Posicion_X = 0.0, Posicion_Y = 0.0, Posicion_Z = 0.0, Posicion_R = 0.0,", InfoVehiculo[vid][vNombre], InfoVehiculo[vid][vPropietario]);
	format(que2ry, sizeof que2ry, "%s Interior = 0, VirtualWorld = 0, Vida = 1000.0, DanioSuperficie = 0, DanioPuertas = 0, DanioLuces = 0, DanioRuedas = 0, Gasolina = 200, Color_1 = 1, Sirena = 0,", que2ry);
	format(que2ry, sizeof que2ry, "%s End_Posicion_X = 0.0, End_Posicion_Y = 0.0, End_Posicion_Z = 0.0, End_Posicion_R = 0.0, End_Interior = 0, End_VirtualWorld = 0,", que2ry);
	mysql_format(db_samp, query, sizeof query, "%s Premium = 0, Stereo = 0, Trabajo = 0, Color_2 = 1, PaintJob = -1, ConSeguro = 0, Precio = 0, Embargo = 0, Multa = 0, MaxMaletero = 5, CallSign = '' WHERE ID = '%d'", que2ry, InfoVehiculo[vid][vID_sql]);
	mysql_tquery(db_samp, query);
	return 1;
}

stock GetCar3DZone(vehicleid, zone[], len)
{
    new Float: x, Float: y, Float: z;
    GetVehiclePos(vehicleid, x, y, z);
    for(new i = 0; i != sizeof(gSAZones); i++)
	{
        if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4] && z >= gSAZones[i][SAZONE_AREA][2] && z <= gSAZones[i][SAZONE_AREA][5]) {
            return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
        }
    }
    return 0;
}

stock GetOffsetFromVehicle(Float:posX, Float:posY, Float:posZ, vehicleid, &Float:X, &Float:Y, &Float:Z) {
	new Float:pos[3];
	GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
	new Float:rotZ;
	GetVehicleZAngle(vehicleid, rotZ);
	new Float:off[2];
	off[0] = posX - pos[0];
	off[1] = posY - pos[1];
	X = off[0]*floatcos(rotZ, degrees)+off[1]*floatsin(rotZ, degrees);
	Y = -off[0]*floatsin(rotZ, degrees)+off[1]*floatcos(rotZ, degrees);
	Z = posZ - pos[2];
	return 1;
}

stock ReproducirMVeh(playerid, const url[], Float: posX = 0.0, Float: posY = 0.0, Float: posZ = 0.0, Float: distance = 50.0, usepos = 0)
{
	if (GetPVarType(playerid, "MusVeh")) StopAudioStreamForPlayer(playerid);
	else SetPVarInt(playerid, "MusVeh", 1);
	if (InfoPersonaje[playerid][pTogMusic] == 1)
	{
		 if (TipoAudio[playerid] == 0||TipoAudio[playerid] == 4)
		 {
		 	PlayAudioStreamForPlayer(playerid, url, posX, posY, posZ, distance, usepos);
			TipoAudio[playerid] = 4;
		}
	}
}

funcion PararMVeh(playerid)
{
	DeletePVar(playerid, "MusVeh");
	if (TipoAudio[playerid] == 4)
	{
		StopAudioStreamForPlayer(playerid);
		TipoAudio[playerid] = 0;
 	}
}

funcion cocheocupado(vehicleid)
{
	for(new i; i < GetMaxPlayers(); i++)
	if(IsPlayerConnectedEx(i) && IsPlayerInVehicle(i, vehicleid) && GetPlayerState(i) == PLAYER_STATE_DRIVER) return 1;
	return 0;
}

funcion CercaDelVehiculo(playerid, vehicleid, Float: radius)
{
	new Float: Floats[3];
	GetVehiclePos(vehicleid, Floats[0], Floats[1], Floats[2]);
	return IsPlayerInRangeOfPoint(playerid, radius, Floats[0], Floats[1], Floats[2]);
}

DetectarMaxVehiculos(playerid)
{
	new carsamount = VehicleCount(playerid);
	if (InfoCuenta[playerid][jVIP] == 0 && carsamount >= 3)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios normales sólo pueden tener 3 vehículos.");
		return 1;
	}
	if (InfoCuenta[playerid][jVIP] == 1 && carsamount >= 6)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios VIP Level 1 sólo pueden tener 6 vehículos.");
		return 1;
	}
	if (InfoCuenta[playerid][jVIP] == 2 && carsamount >= 10)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuarios VIP Level 2 sólo pueden tener 10 vehículos.");
		return 1;
	}
	return 2;
}

IsWindowedVehicle(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
    if (400 <= model <= 611)
    {
        static const g_WindowInfo[] =
		{
		    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
		    1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1,
		    1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		    1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		    1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0,
		    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		    1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1,
			1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
		};
		return g_WindowInfo[model - 400];
	}
	return 0;
}

IsWindowOpened(vehicleid)
{
	new ven_1, ven_2, ven_3, ven_4;
	GetVehicleParamsCarWindows(vehicleid, ven_1, ven_2, ven_3, ven_4);
	if (ven_1 == 0) return 1;
	else if (ven_2 == 0) return 1;
	else if (ven_3 == 0) return 1;
	else if (ven_4 == 0) return 1;
	return 0;
}

IsATowTruck(carid)
{
	if(GetVehicleModel(carid) == 485 || GetVehicleModel(carid) == 525 || GetVehicleModel(carid) == 583 || GetVehicleModel(carid) == 574)
	{
		return 1;
	}
	return 0;
}

IsABike(carid)
{
	if(GetVehicleModel(carid) == 509 || GetVehicleModel(carid) ==  481 || GetVehicleModel(carid) == 510)
	{
		return 1;
	}
	return 0;
}

IsAPlane(carid)
{
	switch(GetVehicleModel(carid)) {
		case 592, 577, 511, 512, 593, 520, 553, 476, 519, 460, 513, 548, 425, 417, 487, 488, 497, 563, 447, 469: return 1;
	}
	return 0;
}