Timers()
{
	SetTimer("timer_segundo", 1000, true);
	SetTimer("timer_2segundo", 1000, true);
	SetTimer("timer_minuto", 60000, true);
    SetTimer("timer_mediosegundo", 500, true);
	SetTimer("timer_microbeat", 250, true);
	SetTimer("timer_spec", 3000, true);
	return 1;
}

forward timer_mediosegundo();
public timer_mediosegundo()
{
	Loop(playerid, MAX_PLAYERS, 0) if (usuario_registro[playerid] == 2)
	{
		if (GetPlayerState(playerid) == 1)
		{
			if (Taseado[playerid] != 0 && GetPlayerAnimationIndex(playerid) != 1209)
			{
				ApplyAnimation(playerid, "PED", "KO_skid_front", 4.1, 0, 1, 1, 1, 0, 1);
			}
			if (GetPVarInt(playerid, "EstaCrack") == 1 && GetPlayerAnimationIndex(playerid) != 1701)
			{
				ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0, 1);
			}
			if (ConBalasGoma[playerid] != 0 && GetPlayerAnimationIndex(playerid) != 1533)
			{
				ApplyAnimation(playerid, "SWEET", "LaFin_Sweet", 4.0, 0, 1, 1, 1, 0, 1);
			}
		}
		//otros
		if (papilla[playerid] != 0) SetPlayerColor(playerid, 0xb42d2d00);
		switch (tipo_refuerzos[playerid])
		{
		    case 1:
		    {
				if (refuerzos_pd[playerid] == 1)
				{
					Loop(i, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(i) && member_faccion(i, 1) && OnDuty[i] == 1)
					{
						SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
					}
				}
				if (refuerzos_sd[playerid] == 1)
				{
					Loop(i, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(i) && member_faccion(i, 4) && OnDuty[i] == 1)
					{
						SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
					}
				}
				if (refuerzos_fbi[playerid] == 1)
				{
					Loop(i, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(i) && member_faccion(i, 2) && OnDuty[i] == 1)
					{
						SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
					}
				}
			}
		    case 2:
		    {
				Loop(i, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(i) && member_faccion(i, 1, 2, 4) && OnDuty[i] == 1)
				{
					SetPlayerMarkerForPlayer(i, playerid, 0xFFF400FF);
				}
			}
		    case 3:
		    {
				Loop(i, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(i) && member_faccion(i, 1, 2, 4, 6) && OnDuty[i] == 1)
				{
					SetPlayerMarkerForPlayer(i, playerid, 0xFF0000FF);
				}
			}
		}
		//Vehículos
		ActualizarManos(playerid); //actualiza los objetos de manos del jugador
	} // } end
}

forward timer_segundo();
public timer_segundo()
{
	//system hour 01/08/2020
	xSegundo++;
	if (xSegundo == 60)
	{
		xMinuto++;
		xSegundo = 0;
	}
	if (xMinuto == 60)
	{
		xHora++;
		xMinuto = 0;
		xSegundo = 0;
	}
	if (xHora == 24)
	{
		xHora = 0;
		xMinuto = 0;
		xSegundo = 0;
	}
	// textdraw hora.
    new gformat[256];
//		new year, month, day, hour, minute, second;
//		getdate(year, month, day);
//		gettime(hour, minute, second);
	foreach(Player, i)
	{
	    if (IsPlayerConnected(i) && usuario_registro[i] == 2)
	    {
	        //afk
			if (GetPlayerAdmin(i, 10) == 0) InfoPersonaje[i][pModoAfk]++;
			if(pDroga[i][EfectoLSD] == 0 && pDroga[i][EfectoHongo] == 0 && pDroga[i][EfectoMDMA] == 0 && pDroga[i][EfectoEspecialUWU] == 0){
				SetPlayerTime(i, xHora, xMinuto);
			}
	        //auto save cada 5seg by edinsonwalker
			countGameTime[i]++;
			if (countGameTime[i] == 5)
			{
				if (Spectate[i] == 999)
				{
					GetPlayerPos(i, InfoPersonaje[i][pPosicionX], InfoPersonaje[i][pPosicionY], InfoPersonaje[i][pPosicionZ]);
					GetPlayerFacingAngle(i, InfoPersonaje[i][pPosicionR]);
					InfoPersonaje[i][pInterior] = GetPlayerInterior(i);
					InfoPersonaje[i][pVirtualWorld] = GetPlayerVirtualWorld(i);
				}
				new query[1500];
				mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET PosicionX = '%f', PosicionY = '%f', PosicionZ = '%f', PosicionR = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
				InfoPersonaje[i][pPosicionX], InfoPersonaje[i][pPosicionY], InfoPersonaje[i][pPosicionZ], InfoPersonaje[i][pPosicionR], InfoPersonaje[i][pInterior], InfoPersonaje[i][pVirtualWorld], InfoPersonaje[i][pID]);
				mysql_tquery(db_samp, query);
				countGameTime[i] = 0;
			}

			if (TiempoTecla[i] != 0) {
        			TiempoTecla[i] --;
        			if (TiempoTecla[i] == 0) {
        		    	TiempoTecla[i] = 0;
    				}
			}

			if(Tied[i] > 0) TogglePlayerControllable(i, 0);
			if(GetPlayerSpecialAction(i) == SPECIAL_ACTION_USEJETPACK && JetPack[i] == 0 && GetPlayerAdmin(i, 0) == 0)
			{
				format(gformat, sizeof gformat, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) ha sido auto-expulsado del servidor. Razón: cheat jetpack", GetNameFormat(i), i);
				SendAdminMessage(0xFFFFFFFF, gformat);
				SendPlayerChatMessage(i, COLOR_GENERAL, "Fuiste expulsado por usar cheat jetpack.");
				SetTimerEx("TimerKICK", 1000, false, "d", i);
			}
			//teleport cheats
			new Float: x, Float: y, Float: z;
			GetPlayerPos(i, x, y, z);
			if (cheat_PlayerTeleport != 0)
			{
				new reason[170], bool: surfing;
				if (!InfoSync[i][SYNC_TYPE_POS][sTimeSync])
				{
					surfing = (GetPlayerSurfingVehicleID (i) != INVALID_VEHICLE_ID || GetPlayerSurfingObjectID (i) != INVALID_OBJECT_ID);
					if ((z < 900.0) == (CurrentPos[i][2] < 900.0))//Prevent kick when entering buildings.
					{
						if (GetPlayerState(i) != PLAYER_STATE_PASSENGER && !surfing && !IsPlayerInRangeOfPoint(i, 350.0, CurrentPos[i][0], CurrentPos[i][1], CurrentPos[i][2]))
						{
							if (!IsPlayerInRangeOfPoint(i, 5.0, pSetPos[i][0], pSetPos[i][1], pSetPos[i][2]))
							{
								GetPlayer2DZone(i, reason, sizeof reason);
								if (IsCheatPosition (i))
								{
									format(reason, sizeof reason, "Teleport cheats #1 (%s)", reason);
								}
								else
								{
									format(reason, sizeof reason, "Teleport cheats #2 (%s)", reason);
								}
							 	WarningTPlayer[i]++;
								//función
					 		    if (WarningTPlayer[i] >= 3)
					 		    {
					 			    CheatDetected(i, reason, 2);
					 		    }
					 		    else //posible
					 		    {
									CheatDetected(i, reason, 1);
					 		    }
							}
						}
					}
				}
			}
			//
			CurrentPos[i][0] = x;
			CurrentPos[i][1] = y;
			CurrentPos[i][2] = z;
		}
	}
}

forward timer_2segundo();
public timer_2segundo()
{
	foreach(Player, i)
	{
	    if (IsPlayerConnected(i) && usuario_registro[i] == 2)
		{
		    new query[320];
			if (GetPlayerPing(i) > MAX_PING)
			{
				format(query, sizeof query, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) ha sido auto-expulsado del servidor. Razón: ping (%d)", GetNameFormat(i), i, GetPlayerPing(i));
				SendAdminMessage(0xFFFFFFFF, query);
				SendPlayerChatMessage(i, COLOR_GENERAL, "Fuiste expulsado por exceso de ping.");
				SetTimerEx("TimerKICK", 1000, false, "d", i);
		    }
 			if(CommandSpamUnmute[i] != 0)
	 		{
				CommandSpamUnmute[i]--;
   				if (CommandSpamUnmute[i] == 0) CommandSpamTimes[i] = 0;
			}
			if(InfoPersonaje[i][pServiceTime] != 0) { InfoPersonaje[i][pServiceTime]--; }
			if(GetPlayerCash(i) != GetPlayerMoney(i))
			{
				ResetPlayerMoney(i);
				GivePlayerMoney(i, InfoPersonaje[i][pDinero]);
			}
			if (timer_herido[i] != 0)
			{
				timer_herido[i]--;
				if (timer_herido[i] == 0) SendPlayerChatMessage(i, 0x59C52CFF, "Ya puedes usar /volver.");
			}
			if (InfoPersonaje[i][pTriageTime] != 0)
			{
				InfoPersonaje[i][pTriageTime]--;
    		}
		    if(InfoPersonaje[i][pSancionado] > 0)
			{
				if(InfoPersonaje[i][pTiempoSancion] > 0)
				{
					new text[128];
		        	if (InfoPersonaje[i][pSancionado] == 1)
					{
						InfoPersonaje[i][pTiempoSancion]--;
		            	format(text, sizeof(text), "~n~~n~~n~~n~~n~~n~~n~ ~r~Sancion OOC!~n~~w~%s restantes", Segundos_tiempo(InfoPersonaje[i][pTiempoSancion]));
					}
					else
					{
					    if (InfoPersonaje[i][pModoAfk] < 3)
						{
							InfoPersonaje[i][pTiempoSancion]--;
						}

					}
					GameTextForPlayer(i, text, 2000, 3);
					guardar_int_mysql("personajes", "TiempoSancion", InfoPersonaje[i][pID], InfoPersonaje[i][pTiempoSancion]);
				}
    			if (InfoPersonaje[i][pTiempoSancion] <= 0)
				{
				    InfoPersonaje[i][pTiempoSancion] = 0;
				    switch (InfoPersonaje[i][pSancionado])
				    {
				        case 1: SetPosEx(i, 1722.2679, -1715.8794, 13.6703, 0.0000, 0, 0, 1);
				        case 2: SetPosEx(i, 1825.0082, -1538.3765, 13.6957, -90.0000, 0, 0, 1);
					}
					InfoPersonaje[i][pEstrellas] = 0;
					SetPlayerWantedLevel(i, InfoPersonaje[i][pEstrellas]);
					InfoPersonaje[i][pSancionado] = 0;
					InfoPersonaje[i][pTogTelefono] = 1;
					SendPlayerChatMessage(i, COLOR_GREEN, "Cumpliste el tiempo de condena, ahora eres libre.");
					GivePlayerSkin(i, InfoPersonaje[i][pSkin]);
					alm(InfoPersonaje[i][pBySancion], "none");
					alm(InfoPersonaje[i][pRazonSancion], "none");
					mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Estrellas = 0, Sancionado = 0, TiempoSancion = 0, BySancion = '%e', RazonSancion = '%e' WHERE ID = '%d'", InfoPersonaje[i][pBySancion], InfoPersonaje[i][pRazonSancion], InfoPersonaje[i][pID]);
					mysql_tquery(db_samp, query);
					TogglePlayerControllable(i, true);
				}
			}
   			if (JustReported[i] > 0) 	{ 	JustReported[i]--; 	}
			if (JustDuda[i] > 0)		{ 	JustDuda[i]--; 		}
		    if (InfoCuenta[i][jRegalo] != 0)
			{
				InfoCuenta[i][jRegalo]--;
				guardar_int_mysql("cuentas", "Regalo", InfoCuenta[i][jID], InfoCuenta[i][jRegalo]);
			}
		}
	}
}

forward timer_microbeat();
public timer_microbeat()
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		if (InfoCuenta[playerid][jTogPing] == 0)
		{
			new gformat[190];
			format(gformat, sizeof gformat, "~w~~h~~h~Fps: %d", pFPS[playerid]);
			PlayerTextDrawSetStringEx(playerid, TDping[playerid], gformat);
		}
		// en vehiculo
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new Float: HPveh, vehicleid = GetPlayerVehicleID(playerid), arrDamage[4], arrVehParams[7];
			if (GetVehicleModel(vehicleid))
			{
				Loop(s, 10, 0) if (SpikeStrips[s][sX] != 0)
				{
					if (VehicleToPoint(2.0, vehicleid, SpikeStrips[s][sX], SpikeStrips[s][sY], SpikeStrips[s][sZ]))
					{
						GetVehicleDamageStatus(vehicleid, arrDamage[0], arrDamage[1], arrDamage[2], arrDamage[3]);
						arrDamage[3] = encode_tires(1, 1, 1, 1);
						UpdateVehicleDamageStatus(vehicleid, arrDamage[0], arrDamage[1], arrDamage[2], arrDamage[3]);
					}
				}
				GetVehicleHealth(vehicleid, HPveh);
				if (HPveh < 300.0 && !IsABike(vehicleid))
				{
					SetVehicleHealth(vehicleid, 299.0);
					SetVehicleParamsEx(vehicleid, arrVehParams[0], arrVehParams[1], arrVehParams[2], arrVehParams[3], arrVehParams[4], arrVehParams[5], arrVehParams[6]);
					if (arrVehParams[0] == VEHICLE_PARAMS_ON) SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, arrVehParams[1], arrVehParams[2], arrVehParams[3], arrVehParams[4], arrVehParams[5], arrVehParams[6]);
					arr_Engine{vehicleid} = 0;
				}
				//info velocimetro
				if (show_velocimetro[playerid]) update_velocimetro(playerid, vehicleid);
			}
		}
		else // a pie
		{
			//EstaEnFuego(playerid); esta wea deja super mal optimizado xd
		}
	}
}

forward timer_spec();
public timer_spec()
{
	foreach(Player, i) if (GetPlayerAdmin(i, 1) != 0)
	{
		if (Spectating[i] >= 1)
		{
			if (Spectate[i] < 553)
			{
				new targetid = Spectate[i];
				if (!IsPlayerConnected(targetid))
				{
    				SendPlayerChatMessage( i, COLOR_WHITE, "El jugador que estabas specteando salio del servidor." );
			    	GettingSpectated[Spectate[i]] = 999;
			    	Spectating[i] = 0;
					Spectate[i] = 999;
					SetPVarInt(i, "SpecState", -1);
					SetPVarInt(i, "SpecOff", 1 );
					TogglePlayerSpectating( i, false );
					SetCameraBehindPlayer(i);
				}
			}
			if (Spectate[i] == 554)
			{
				TogglePlayerControllable(i, 1);
				SetPlayerInterior(i,Unspec[i][sPint]);
				InfoPersonaje[i][pInterior] = Unspec[i][sPint];
				SetPlayerPosEx(i, Unspec[i][Coords][0], Unspec[i][Coords][1], Unspec[i][Coords][2]);
				Spectate[i] = 999;
			}
			if (Spectate[i] == 556)
			{
				Spectate[i] = 999;
			}
			if (Spectate[i] == 557)
			{
				Spectate[i] = 554;
			}
		}
	}
}


forward timer_minuto();
public timer_minuto()
{
    /* Hora */
    new
        hour,
        minute,
        second;

    gettime(hour, minute, second);
	SetWorldTime(hour);

   	if (minute == 1) Update_Weather();

	DrugCounter+=1;
	if(DrugCounter == 20) DrugCounter = 0;

	CountMinute++;
	if (CountMinute == 60)
	{
		GenerarIncendio();
		CountMinute = 0;
	}


	//resta de gasolina
	Loop(v, MAX_VEHICLES, 0) if (GetVehicleModel(v))
	{
		new modelid = GetVehicleModel(v);
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
		switch (modelid)
		{
			case 520, 476, 593, 553, 513, 512, 577, 592, 511, 539, 464, 519: veh_gasolina[v] = 200;
			case 509, 481, 510: veh_gasolina[v] = 200, arr_Engine{v} = 1, SetVehicleParamsEx(v, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
		}
		if (engine == VEHICLE_PARAMS_ON)
		{
			if (veh_gasolina[v] != 0)
			{
				veh_gasolina[v]--;
				if (veh_gasolina[v] == 0) SetVehicleParamsEx(v, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
			}
			if (arr_Engine{v} == 0) SetVehicleParamsEx(v, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
		}
	}
	//
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vSpawned] != 0)
	{
		if (InfoVehiculo[id][vTimeSave] != 0)
		{
			if (InfoVehiculo[id][vTimeSave] > 0) InfoVehiculo[id][vTimeSave]--;
			if (InfoVehiculo[id][vTimeSave] == 0)
				OcultarVehiculo(id);
		}
		//sistema renta
		if (InfoVehiculo[id][vRentaTiempo] != 0)
		{
		    new vehicleid = InfoVehiculo[id][vIG_id];
			if (InfoVehiculo[id][vRentaTiempo] > 0) InfoVehiculo[id][vRentaTiempo]--;
			if (InfoVehiculo[id][vRentaTiempo] == 3)
			{
				foreach(new p: Player) if (IsPlayerInVehicle(p, vehicleid))
				{
					SendPlayerChatMessage(p, COLOR_YELLOW, "Le quedan sólo tres minutos de renta a este vehículo.");
				}
			}
			if (InfoVehiculo[id][vRentaTiempo] == 0)
			{
				foreach(new p: Player) if (IsPlayerInVehicle(p, vehicleid))
				{
					SendPlayerChatMessage(p, COLOR_YELLOW, "El vehículo en el que estabas fue respawneado, su tiempo de renta termino.");
				}
				InfoVehiculo[id][vRentaTiempo] = 0;
				alm(InfoVehiculo[id][vRentaDueno], "none");
				SetVehicleToRespawn(vehicleid);
			}
		}
	}
 	if (PayDaySecond >= 1) { PayDaySecond--; }
	else { PayDaySecond = 120; }
	if (PayDaySecond == 0) PayDay2();

	// lab y plantas
	for(new i; i < MAX_PLANTAS; i++){
		if(Planta[i][Tipo] == 0) continue;
		Planta[i][TiempoRestante]--;

		if(Planta[i][TiempoRestante] == 0) {
			new dueno = SQLConectado(Planta[i][Plantador]);
			if(dueno != -1) SendPlayerChatMessage(dueno, COLOR_GREY, "Una de tus plantas ya está lista, tienes 48 horas para cosecharla.");
		}

		if(Planta[i][TiempoRestante] == -2880){ // se murió la pendeja
			MatarPlanta(i);
		}
		else ActualizarObjetoPlanta(i);
		updatePlanta(i);
	}

	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		// sistema drogas

		if(DrugCounter == 0){
			new prob = random(3); // 1/3 de probabilidad de efecto adverso
			if(pDroga[playerid][AdiccionCocaina] > 40){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 6500);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xe1401820, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes una gran necesidad de consumir cocaina");
			}else if(pDroga[playerid][AdiccionCocaina] > 20){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 4000);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xe1401814, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes necesidad de consumir cocaina");
			}

			if(pDroga[playerid][AdiccionOpioides] > 40){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 6500);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xe1184a20, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes una gran necesidad de consumir un opioide");
			}else if(pDroga[playerid][AdiccionOpioides] > 20){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 4000);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xe1184a14, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes necesidad de consumir un opioide");
			}

			if(pDroga[playerid][AdiccionAnfetamina] > 40){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 6500);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xad18e120, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes una gran necesidad de consumir anfetaminas");
			}else if(pDroga[playerid][AdiccionAnfetamina] > 20){
				if(prob == 1) SetPlayerDrunkLevel(playerid, 6500);
				if(prob == 2) FadePlayerScreenColour(playerid, 0xad18e120, 2200, 25);
				SendPlayerChatMessage(playerid, COLOR_RED, "Sientes una gran necesidad de consumir anfetaminas");
			}

			if(pDroga[playerid][AdiccionAnfetamina] > 0) pDroga[playerid][AdiccionAnfetamina]--;
			if(pDroga[playerid][AdiccionCocaina] > 0) pDroga[playerid][AdiccionCocaina]--;
			if(pDroga[playerid][AdiccionOpioides] > 0) pDroga[playerid][AdiccionOpioides]--;
		}

		if(DrugCounter % 5 == 0){ // cada 5 minutos reducir 1 nivel de sobredosis
			if(pDroga[playerid][NivelSobredosis] > 0 && !pDroga[playerid][Sobredosis]) pDroga[playerid][NivelSobredosis]--;
		}

		if(pDroga[playerid][NivelSobredosis] >= 12) // HE IS FUCKING DEAD.
		{
			pDroga[playerid][Sobredosis] = 1;
			quitar_vida(playerid, -100);
			pDroga[playerid][NivelSobredosis] = 0;
			guardar_int_mysql("personajes", "Sobredosis", InfoPersonaje[playerid][pID], 1);
			SendPlayerChatMessage(playerid, 0xd84444ff, "Estás sufriendo una sobredosis, caíste herido.");
		}

		if(pDroga[playerid][EfectoHongo] > 0){
			pDroga[playerid][EfectoHongo]--;
			SetPlayerWeatherEx(playerid, 246);
			SetPlayerTime(playerid, 22, 0);

			if(pDroga[playerid][EfectoHongo] > 0 && pDroga[playerid][EfectoMDMA] > 0 && pDroga[playerid][EfectoLSD] > 0){
				pDroga[playerid][EfectoEspecialUWU] = 5;
				pDroga[playerid][EfectoHongo] = 0;
				pDroga[playerid][EfectoMDMA] = 0;
				pDroga[playerid][EfectoLSD] = 0;
			}

			if(pDroga[playerid][EfectoHongo] == 0) SetPlayerWeatherEx(playerid, ServerWeather);
		}
		if(pDroga[playerid][EfectoMDMA] > 0){
			pDroga[playerid][EfectoMDMA]--;
			SetPlayerWeatherEx(playerid, 91);
			SetPlayerTime(playerid, 23, 0);
			if(pDroga[playerid][EfectoMDMA] == 0) SetPlayerWeatherEx(playerid, ServerWeather);
		}

		if(pDroga[playerid][EfectoLSD] > 0){
			if(pDroga[playerid][EfectoLSD] == 20) SetPlayerDrunkLevel(playerid, 7500);
			pDroga[playerid][EfectoLSD]--;
			SetPlayerWeatherEx(playerid, 145);
			SetPlayerTime(playerid, 21, 0);
			if(pDroga[playerid][EfectoLSD] == 0) SetPlayerWeather(playerid, ServerWeather);
		}

		if(pDroga[playerid][EfectoEspecialUWU] > 0){
			if(pDroga[playerid][EfectoEspecialUWU] == 5){
				FadePlayerScreenColour(playerid, 0x000000FF, 2200, 25);
				SetTimerEx("startUwu", 3000, false, "i", playerid);
				ClearChat(playerid);
			}
			if(pDroga[playerid][EfectoEspecialUWU] == 4){
				SetPlayerPos(playerid, pDroga[playerid][OldUWU][0],pDroga[playerid][OldUWU][1],pDroga[playerid][OldUWU][2]);
				ShowInfoForPlayer(playerid, "Te sientes confundido", 5000);
				pc_cmd_herido(playerid, "5");
				SetPlayerWeatherEx(playerid, 91);
				SetPlayerTime(playerid, 23, 0);
			}
			else if(pDroga[playerid][EfectoEspecialUWU] == 3){
				SetPlayerWeatherEx(playerid, 145);
				SetPlayerTime(playerid, 21, 0);
			}
			else if(pDroga[playerid][EfectoEspecialUWU] == 2){
				SetPlayerDrunkLevel(playerid, 5500);
			}
			else if(pDroga[playerid][EfectoEspecialUWU] == 1){
				pc_cmd_vomitar(playerid);
				rol_ame(playerid, "vomita fuertemente");
				SetPlayerWeatherEx(playerid, ServerWeather);
			}
			pDroga[playerid][EfectoEspecialUWU]--;
		}

		if(pDroga[playerid][TiempoMarihuana] > 0){
			pDroga[playerid][TiempoMarihuana]--;

			new Float: health = InfoPersonaje[playerid][pVida];

			if(pDroga[playerid][EfectoMarihuana] == 1){
				if (health >= 99) dar_vida(playerid, 100);
				else dar_vida(playerid, health + 2.0);
			}
			else if(pDroga[playerid][EfectoMarihuana] == 2){
				if (health >= 98) dar_vida(playerid, 100);
				else dar_vida(playerid, health + 4.0);
			}

			if(pDroga[playerid][TiempoMarihuana] > 10) FadePlayerScreenColour(playerid, 0x71d08116, 2500, 25);
			else if (pDroga[playerid][TiempoMarihuana] == 9) FadePlayerScreenColour(playerid, 0x71d08100, 5000, 50);

			actualizarDrogas(playerid);
		}

		if(pDroga[playerid][TiempoCocaina] > 0){ // agregar onplayertakedamage effect xd
			pDroga[playerid][TiempoCocaina]--;
			if(pDroga[playerid][TiempoCocaina] > 15) FadePlayerScreenColour(playerid, 0xf0f7f710, 2500, 25);
			else if (pDroga[playerid][TiempoCocaina] == 10) FadePlayerScreenColour(playerid, 0xf0f7f700, 5500, 55);
			actualizarDrogas(playerid);
		}

		if(pDroga[playerid][TiempoKetamina] > 0){
			pDroga[playerid][TiempoKetamina]--;
			if(pDroga[playerid][TiempoKetamina] > 6) FadePlayerScreenColour(playerid, 0x18181810, 2500, 25);
			else if (pDroga[playerid][TiempoKetamina] == 10) FadePlayerScreenColour(playerid, 0x18181800, 15500, 155);
			if(pDroga[playerid][TiempoKetamina] == 0){
				// adiós ketamina!
				new Float: health = InfoPersonaje[playerid][pVida];
				if (health-20.0 <= 15) {
					SendPlayerChatMessage(playerid, 0xd84444ff, "Has caido desplomado tras el efecto de la ketamina.");
					pDroga[playerid][Sobredosis] = 1;
					SendClientMessageEx(playerid, COLOR_GREY, "Tas en xd %d", pDroga[playerid][Sobredosis]);
				}
				quitar_vida(playerid, -20.0);
			}
		}

		if(pDroga[playerid][TiempoHeroina] > 0){
			pDroga[playerid][TiempoHeroina]--;
			if(pDroga[playerid][TiempoHeroina] > 6) FadePlayerScreenColour(playerid, 0x47208512, 2500, 25);
			else if (pDroga[playerid][TiempoHeroina] == 10) FadePlayerScreenColour(playerid, 0x47208500, 15500, 155);
			if(pDroga[playerid][TiempoHeroina] == 0){
				// adiós heroina!
				new Float: health = InfoPersonaje[playerid][pChaleco];
				if(health-20.0 < 0.0) dar_chaleco(playerid, 0);
				else dar_chaleco(playerid, health-20.0);
			}
		}

		// muerte

		if(InfoPersonaje[playerid][pEstado] == 2)
		{
			new str[64], tiempo = timer_herido[playerid];
			if (tiempo == 0)
			{
				format(str, sizeof(str), "Ahora puedes utilizar /reaparecer.");
			}
			else
			{
				format(str, sizeof(str), "Puedes utilizar /reaparecer en %s.", Mins_time(tiempo));
			}
			PlayerTextDrawSetString(playerid, p_tdMuerte[playerid][2], str);
		}
		//comprarnegocio
	    if (InfoPersonaje[playerid][pComprarNegocio] != 0)
	    {
			if (InfoPersonaje[playerid][pComprarNegocio] > 0) InfoPersonaje[playerid][pComprarNegocio]--;
	        if (InfoPersonaje[playerid][pComprarNegocio] == 0)
	        {
	            SendPlayerChatMessage(playerid, COLOR_PURPLE, "*** Ya puedes usar '/comprarnegocio' nuevamente.");
	        }
			guardar_int_mysql("personajes", "ComprarNegocio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pComprarNegocio]);
	    }
		//payday
		if (InfoPersonaje[playerid][pModoAfk] < 3)
		{
			InfoPersonaje[playerid][pPayday] ++;
			if (InfoPersonaje[playerid][pPayday] >= 60)
			{
				InfoPersonaje[playerid][pPayday] = 0;
				SetPlayerPayDay(playerid);
			}
			guardar_int_mysql("personajes", "Payday", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pPayday]);
			//molotov
			if (InfoPersonaje[playerid][pTiempoMolotov] != 0)
			{
				InfoPersonaje[playerid][pTiempoMolotov]--;
				guardar_int_mysql("personajes", "TiempoMolotov", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTiempoMolotov]);
			}
		}
		if (InfoPersonaje[playerid][pTimerAnuncios] != 0)
		{
			InfoPersonaje[playerid][pTimerAnuncios]--;
			guardar_int_mysql("personajes", "TimerAnuncios", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTimerAnuncios]);
		}
		if (InfoPersonaje[playerid][pTogCajero] != 0)
		{
			InfoPersonaje[playerid][pTogCajero]--;
			guardar_int_mysql("personajes", "TogCajero", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogCajero]);
		}
		if (InfoPersonaje[playerid][pRestriccionRobo] != 0)
		{
			InfoPersonaje[playerid][pRestriccionRobo]--;
			guardar_int_mysql("personajes", "RestriccionRobo", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pRestriccionRobo]);
		}
	}
}