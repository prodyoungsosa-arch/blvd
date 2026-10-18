anim_muerte(playerid)
{
	// animación cuando muere.
	if (IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (EnMotos_Bicis(vehicleid))
		{
			RemovePlayerFromVehicle(playerid);
			new Float:X, Float:Y, Float:Z;
			GetPlayerPos(playerid, X, Y, Z);
			SetPlayerPos(playerid, X, Y+1, Z);
			ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0, 1);
		}
		else
		{
			if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				check_motor[playerid] = 0;
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				if (engine == VEHICLE_PARAMS_ON)
				{
					SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
					arr_Engine {vehicleid} = 0;
				}
			}
			ApplyAnimation(playerid, "ped", "CAR_dead_RHS", 4.0, 0, 0, 0, 1, 0, 1);
		}
	}
	else ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0, 1);
	return 1;
}

GoToHospital(playerid)
{
	MensajeMuelto[playerid] = 0;
	KillEMSQueue(playerid);
	dar_vida(playerid, 100);
	ResetPlayerHeridas(playerid);
	TipoAudio[playerid] = 0;
	StopAudioStreamForPlayer(playerid);
	new Float: hosX, Float: hosY, Float: hosZ, Float: hosR, hosInt, hosVW;
	if (InfoPersonaje[playerid][pMiembro] != 0)
	{
		new id = InfoPersonaje[playerid][pMiembro];
		if (InfoFaccion[id][fSpawnX] != 0.0)
		{
			hosX = InfoFaccion[id][fSpawnX];
			hosY = InfoFaccion[id][fSpawnY];
			hosZ = InfoFaccion[id][fSpawnZ];
			hosR = InfoFaccion[id][fSpawnR];
			hosInt = InfoFaccion[id][fSpawnInt];
			hosVW = InfoFaccion[id][fSpawnVW];
    		SendPlayerChatMessage(playerid, COLOR_WHITE, "Los gastos del seguro médico son de {B00000}$50{FFFFFF}, que tengas buen día.");
	    	GivePlayerCash(playerid, -50, "seguro médico facción");
		}
		else
		{ 
			hosX = -212.6715;
			hosY = 1014.5307;
			hosZ = 19.5854;
			hosR = 338.7838;
			hosInt = 0;
			hosVW = 0;

			ShowInfoForPlayer(playerid, "Has sido trasladado al hospital.", 3000);
    		SendPlayerChatMessage(playerid, COLOR_WHITE, "Los gastos del seguro médico son de {B00000}$100{FFFFFF}, que tengas buen día.");
    		GivePlayerCash(playerid, -100, "seguro médico civil");
		}
	}
	else
	{
		hosX = 1114.10;
		hosY = -1319.2;
		hosZ = 13.76;
		hosR = 270;
		hosInt = 0;
		hosVW = 0;
    	SendPlayerChatMessage(playerid, COLOR_WHITE, "Los gastos del seguro médico son de {B00000}$100{FFFFFF}, que tengas buen día.");
    	GivePlayerCash(playerid, -100, "seguro médico civil");
	}
	SetPosEx(playerid, hosX, hosY, hosZ, hosR, hosInt, hosVW, 1);
	SetCameraBehindPlayer(playerid);
	InfoPersonaje[playerid][pEstado] = 0;
	guardar_int_mysql("personajes", "Estado", InfoPersonaje[playerid][pID], 0);
	guardar_int_mysql("personajes", "Muerto", InfoPersonaje[playerid][pID], 0);

	return 1;
}