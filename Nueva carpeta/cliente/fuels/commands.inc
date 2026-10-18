//Jugadores
cmd:combustible(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debe ser el conductor de un vehículo.");
	if (VehiculoGasolina[playerid] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya estás llenando el tanque de gasolina.");
	new gas = -1;
	Loop(id, totalgasolinas, 1) if (IsPlayerInRangeOfPoint(playerid, 8.0, InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ]) && GetPlayerVirtualWorld(playerid) == InfoBidon[id][gsVirtualWorld] && GetPlayerInterior(playerid) == InfoBidon[id][gsInterior])
	{
		gas = id;
	}
	if (gas == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún punto de bidón de gasolina.");
	new vehicleid = GetPlayerVehicleID(playerid), engine, lights, alarm, doors, bonnet, boot, objective;
	if (EstaEnBicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "AAaaaaa no, tu tienes serios problemaxD¿");
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if (engine == VEHICLE_PARAMS_ON) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener el motor apagado para tomar gasolina.");
	if (InfoCuenta[playerid][jVIP] == 0)
	{
		if (GetPlayerCash(playerid) < 115) {	SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficiente dinero ($115)."); return 1; }
	}
	if (veh_gasolina[vehicleid] >= 199) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El tanque de gasolina del vehículo no aguanta más de 200 litros.");
	GameTextForPlayer(playerid, "~w~Echando ~p~gasolina...", 10000, 3);
	VehiculoGasolina[playerid] = 1;
	SetTimerEx("llenando_gasolina", 6000, false, "dd", playerid, vehicleid);
	return 1;
}
alias:combustible("llenar", "fuel", "bidon");

//Administrativos

cmd:creargasolina(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new query[512];
	Loop(id, MAX_GASOLINERAS, 1) if (!InfoBidon[id][gsPotX])
	{
		GetPlayerPos(playerid, InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ]);
		InfoBidon[id][gsInterior] = GetPlayerInterior(playerid);
		InfoBidon[id][gsVirtualWorld] = GetPlayerVirtualWorld(playerid);
		format(query, sizeof query, "Creaste el bidón ID %d.", id);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, query);
		format(query, sizeof query, "Punto de gasolina (%d), escribe {3E62F4}/llenar{EBEBEB} aquí.", id);
		InfoBidon[id][gsLabel] = CreateDynamic3DTextLabel(query, 0xEBEBEBFF, InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ], 8.0, .interiorid = InfoBidon[id][gsInterior], .worldid = InfoBidon[id][gsVirtualWorld]);
		//opción idsql ya creada.
		if (InfoBidon[id][gsID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE bidones SET PotX = '%f', PotY = '%f', PotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ], InfoBidon[id][gsInterior], InfoBidon[id][gsVirtualWorld], InfoBidon[id][gsID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_GASOLINERAS;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO bidones (PotX, PotY, PotZ, Interior, VirtualWorld) VALUES ('%f', '%f', '%f', '%d', '%d')",
		InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ], InfoBidon[id][gsInterior], InfoBidon[id][gsVirtualWorld]);
		mysql_tquery(db_samp, query, "OnGasolinaCreate", "i", id);
		id = MAX_GASOLINERAS;
	}
	return 1;
}


cmd:borrargasolinera(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, gformat[128], query[512];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borrargasolinera (BidonID)");
	if (!InfoBidon[id][gsPotX]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Id gasolinera invalida.");
	InfoBidon[id][gsPotX] = 0.0;
	InfoBidon[id][gsPotY] = 0.0;
	InfoBidon[id][gsPotZ] = 0.0;
	InfoBidon[id][gsInterior] = 0;
	InfoBidon[id][gsVirtualWorld] = 0;
	if (IsValidDynamic3DTextLabel(InfoBidon[id][gsLabel]))
	{
		DestroyDynamic3DTextLabel(InfoBidon[id][gsLabel]);
		InfoBidon[id][gsLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	mysql_format(db_samp, query, sizeof query, "UPDATE bidones SET PotX = 0.0, PotY = 0.0, PotZ = 0.0, Interior = 0, VirtualWorld = 0 WHERE ID = '%d'", InfoBidon[id][gsID_sql]);
	mysql_tquery(db_samp, query);
	format(gformat, sizeof gformat, "Borraste el bidón ID %d, SQL vacía: %d", id, InfoBidon[id][gsID_sql]);
	SendPlayerChatMessage(playerid, -1, gformat);
	return 1;
}
