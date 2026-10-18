//Jugadores

//Administrativos
cmd:ddedit(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, valor, query[315];
	if (sscanf(params, "s[32]", params))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta (Opción) (PuertaID)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: exterior, interior, vip, faccion, admin, vehicle, estrellas, pickup, mapicon, borrar");
		return 1;
	}
	if (!strcmp(params, "exterior", true, 8))
	{
		if (sscanf(params, "s[32]d", params, id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta exterior (PuertaID)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		GetPlayerPos(playerid, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoPuerta[id][pdExteriorR]);
		InfoPuerta[id][pdExteriorInt] = GetPlayerInterior(playerid);
		InfoPuerta[id][pdExteriorVW] = GetPlayerVirtualWorld(playerid);
		mysql_format(db_samp, query, sizeof query, "UPDATE puertas SET ExteriorX = '%f', ExteriorY = '%f', ExteriorZ = '%f', ExteriorR = '%f', ExteriorInt = '%d', ExteriorVW = '%d' WHERE ID = '%d'", InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorR], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW], InfoPuerta[id][pdID_sql]);
		mysql_tquery(db_samp, query);
		CreateDynamicDoor(id, 1);
		format(query, sizeof query, "Cambiaste el exterior de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el exterior de la puerta id %d.", NombreDeCuenta(playerid), id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "interior", true, 8))
	{
		if (sscanf(params, "s[32]d", params, id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta interior (PuertaID)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		GetPlayerPos(playerid, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]);
		GetPlayerFacingAngle(playerid, InfoPuerta[id][pdInteriorR]);
		InfoPuerta[id][pdInteriorInt] = GetPlayerInterior(playerid);
		InfoPuerta[id][pdInteriorVW] = GetPlayerVirtualWorld(playerid);
		mysql_format(db_samp, query, sizeof query, "UPDATE puertas SET InteriorX = '%f', InteriorY = '%f', InteriorZ = '%f', InteriorR = '%f', InteriorInt = '%d', InteriorVW = '%d' WHERE ID = '%d'", InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorR], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW], InfoPuerta[id][pdID_sql]);
		mysql_tquery(db_samp, query);
		CreateDynamicDoor(id, 0);
		format(query, sizeof query, "Cambiaste el interior de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el interior de la puerta id %d.", NombreDeCuenta(playerid), id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "vip", true, 3))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta vip (PuertaID) (Nivel)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdVIP] = valor;
		guardar_int_mysql("puertas", "VIP", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdVIP]);
		format(query, sizeof query, "Cambiaste el VIP (%s) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", GetNameVIP(valor), InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el vip (%s) de la puerta id %d.", NombreDeCuenta(playerid), GetNameVIP(valor), id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "faccion", true, 7))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta faccion (PuertaID) (FacciónID)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdFaccion] = valor;
		guardar_int_mysql("puertas", "Faccion", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdFaccion]);
		format(query, sizeof query, "Cambiaste la facción (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado la facción (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "admin", true, 5))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta admin (PuertaID) (Rango)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		if (valor < 0 || valor > 6) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Sólo existen 6 rangos administrativos.");
		InfoPuerta[id][pdAdmin] = valor;
		guardar_int_mysql("puertas", "Admin", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdAdmin]);
		format(query, sizeof query, "Cambiaste el admin (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el admin (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "estrellas", true, 9))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta estrellas (PuertaID) (Nivel de busqueda)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdEstrellas] = valor;
		guardar_int_mysql("puertas", "Estrellas", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdEstrellas]);
		format(query, sizeof query, "Cambiaste el nivel de busqueda (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el nivel de busqueda (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "vehicle", true, 7))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta vehicle (PuertaID) (1 activado - 0 desactivado)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdStatusVehiculo] = valor;
		guardar_int_mysql("puertas", "StatusVehiculo", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdStatusVehiculo]);
		format(query, sizeof query, "Cambiaste el status vehículo (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el status vehículo (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
	}
	else if (!strcmp(params, "pickup", true, 6))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta pickup (PuertaID) (Monto)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdModelo] = valor;
		guardar_int_mysql("puertas", "Modelo", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdModelo]);
		format(query, sizeof query, "Cambiaste el modelo pickup (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el modelo pickup (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
		CreateDynamicDoor(id, 0);
	}
	else if (!strcmp(params, "mapicon", true, 7))
	{
		if (sscanf(params, "s[32]dd", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarpuerta mapicon (PuertaID) (ModelID)");
		if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
		if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoPuerta[id][pdMapIcon] = valor;
		guardar_int_mysql("puertas", "MapIcon", InfoPuerta[id][pdID_sql], InfoPuerta[id][pdMapIcon]);
		format(query, sizeof query, "Cambiaste el mapicon (%d) de la puerta {F5DEB3}%s{FFFFFF} (ID: {3E62F4}%d{FFFFFF}).", valor, InfoPuerta[id][pdNombre], id);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
		format(query, sizeof query, "%s ha editado el mapicon (%d) de la puerta id %d.", NombreDeCuenta(playerid), valor, id);
		Log("f_logs/ddedit.log", query);
		CreateDynamicDoor(id, 1);
	}
	else if (!strcmp(params, "borrar", true, 6))
	{
		SendPlayerChatMessage(playerid, -1, "Utiliza: /borrarpuerta (PuertaID)");
	}
	return 1;
}
alias:ddedit("editarpuerta");

cmd:ddborrar(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, string[128], query[2056];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, -1, "/borrarpuerta [puerta id]");
	if (id < 1 || id >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
	if (InfoPuerta[id][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	alm(InfoPuerta[id][pdNombre], "none");
	InfoPuerta[id][pdExteriorX] = 0.0;
	InfoPuerta[id][pdExteriorY] = 0.0;
	InfoPuerta[id][pdExteriorZ] = 0.0;
	InfoPuerta[id][pdExteriorR] = 0.0;
	InfoPuerta[id][pdExteriorInt] = 0;
	InfoPuerta[id][pdExteriorVW] = 0;
	InfoPuerta[id][pdInteriorX] = 0.0;
	InfoPuerta[id][pdInteriorY] = 0.0;
	InfoPuerta[id][pdInteriorZ] = 0.0;
	InfoPuerta[id][pdInteriorR] = 0.0;
	InfoPuerta[id][pdInteriorInt] = 0;
	InfoPuerta[id][pdInteriorVW] = 0;
	InfoPuerta[id][pdModelo] = 0;
	InfoPuerta[id][pdMapIcon] = 0;
	InfoPuerta[id][pdFaccion] = 0;
	InfoPuerta[id][pdAdmin] = 0;
	InfoPuerta[id][pdVIP] = 0;
	InfoPuerta[id][pdEstrellas] = 0;
	InfoPuerta[id][pdStatusVehiculo] = 0;
	mysql_format(db_samp, query, sizeof query, "UPDATE puertas SET Nombre = '%e', ExteriorX = 0.0, ExteriorY = 0.0, ExteriorZ = 0.0, ExteriorR = 0.0, ExteriorInt = 0, ExteriorVW = 0, InteriorX = 0.0,\
	InteriorY = 0.0, InteriorZ = 0.0, InteriorR = 0.0, InteriorInt = 0, InteriorVW = 0, Modelo = 0, MapIcon = 0, Faccion = 0, Admin = 0, VIP = 0, Estrellas = 0, StatusVehiculo = 0 WHERE ID = '%d'", InfoPuerta[id][pdNombre], InfoPuerta[id][pdID_sql]);
	mysql_tquery(db_samp, query);
	format(string, sizeof string, "Borraste la puerta ID %d, SQL vacía: %d", id, InfoPuerta[id][pdID_sql]);
	SendPlayerChatMessage(playerid, -1, string);
	noexitDoor(id);
	return 1;
}
alias:ddborrar("borrarpuerta");

cmd:goindoor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new doornum;
	if (sscanf(params, "d", doornum)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /irpuertainterior (PuertaID)");
	if (doornum < 1 || doornum >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
	if (InfoPuerta[doornum][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	SetPosEx(playerid, InfoPuerta[doornum][pdInteriorX], InfoPuerta[doornum][pdInteriorY], InfoPuerta[doornum][pdInteriorZ], InfoPuerta[doornum][pdInteriorR], InfoPuerta[doornum][pdInteriorInt], InfoPuerta[doornum][pdInteriorVW], 1);
	return 1;
}
alias:goindoor("irpuertainterior");

cmd:gotodoor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new doornum;
	if (sscanf(params, "d", doornum)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /irpuerta (PuertaID)");
	if (doornum < 1 || doornum >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
	if (InfoPuerta[doornum][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	SetPosEx(playerid, InfoPuerta[doornum][pdExteriorX], InfoPuerta[doornum][pdExteriorY], InfoPuerta[doornum][pdExteriorZ], InfoPuerta[doornum][pdExteriorR], InfoPuerta[doornum][pdExteriorInt], InfoPuerta[doornum][pdExteriorVW], 1);
	return 1;
}
alias:gotodoor("irpuerta");

cmd:ddname(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new query[256], doorid, doorname[128];
	if (sscanf(params, "ds[128]", doorid, doorname)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarpuertanombre (PuertaID) (Nombre)");
	if (doorid < 1 || doorid >= totalpuertas) return SendPlayerChatMessage(playerid, -1, "ID de puerta inválida.");
	if (InfoPuerta[doorid][pdExteriorX] == 0.0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	alm(InfoPuerta[doorid][pdNombre], doorname);
	format(query, sizeof query, "Cambiaste el nombre (%s) de la puerta {F5DEB3}%d{FFFFFF}.", doorname, doorid);
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
	CreateDynamicDoor(doorid, 0);
	guardar_string_mysql("puertas", "Nombre", InfoPuerta[doorid][pdID_sql], InfoPuerta[doorid][pdNombre]);
	format(query, sizeof query, "%s ha editado el nombre (%s) de la puerta id %d.", NombreDeCuenta(playerid), doorname, doorid);
	Log("f_logs/ddedit.log", query);
	return 1;
}
alias:ddname("editarpnombre", "editarpuertanombre", "editarnombrepuerta");

cmd:shopdoor(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new string[256], query[1028];
	Loop(id, MAX_PUERTAS, 1) if (InfoPuerta[id][pdExteriorX] == 0.0)
	{
		alm(InfoPuerta[id][pdNombre], "Usa /editarpuertanombre (PuertaID) (Nombre)");
		GetPlayerPos(playerid, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoPuerta[id][pdExteriorR]);
		InfoPuerta[id][pdExteriorVW] = GetPlayerVirtualWorld(playerid);
		InfoPuerta[id][pdExteriorInt] = GetPlayerInterior(playerid);
		GetPlayerPos(playerid, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]);
		InfoPuerta[id][pdInteriorY] += 2.0;
		GetPlayerFacingAngle(playerid, InfoPuerta[id][pdInteriorR]);
		InfoPuerta[id][pdInteriorVW] = GetPlayerVirtualWorld(playerid);
		InfoPuerta[id][pdInteriorInt] = GetPlayerInterior(playerid);
		CreateDynamicDoor(id, 1);

		format(string, sizeof string, "%s ha creado la puerta id %d.", NombreDeCuenta(playerid), id);
		Log("f_logs/ddedit.log", string);
		format(string, sizeof string, "Creaste la puerta ID %d, configura la misma con /editarpuerta y /editarpuertanombre.", id);
		SendPlayerChatMessage(playerid, COLOR_GENERAL, string);

		//opción idsql ya creada.
		if (InfoPuerta[id][pdID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE puertas SET Nombre = '%e', ExteriorX = '%f', ExteriorY = '%f', ExteriorZ = '%f', ExteriorR = '%f', ExteriorInt = '%d', ExteriorVW = '%d', InteriorX = '%f', InteriorY = '%f', InteriorZ = '%f', InteriorR = '%f', InteriorInt = '%d', InteriorVW = '%d' WHERE ID = '%d'",
			InfoPuerta[id][pdNombre],
			InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorR], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW],
			InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorR], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW],
			InfoPuerta[id][pdID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_PUERTAS;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO puertas (Nombre, ExteriorX, ExteriorY, ExteriorZ, ExteriorR, ExteriorInt, ExteriorVW, InteriorX, InteriorY, InteriorZ, InteriorR, InteriorInt, InteriorVW) VALUES ('%e', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d')",
		InfoPuerta[id][pdNombre],
		InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorR], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW],
		InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorR], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW]);
		mysql_tquery(db_samp, query, "OnPuertaCreate", "d", id);
		id = MAX_PUERTAS;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_RED, "Se alcanzó el máximo de puertas dinámicas (100)");
	return 1;
}
alias:shopdoor("crearpuerta");