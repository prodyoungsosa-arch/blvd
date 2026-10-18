//Jugadores
cmd:gps(playerid)
{
	Dialog_Show(playerid, ShowGPS, DIALOG_STYLE_LIST, "{EBEBEB}GPS - {088A4B}Menú", "Tus Vehículos\nLugares de la ciudad", "Continuar", "Salir");
	return 1;
}
alias:gps("vermapa");

//Administrativos
cmd:editargps(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], slot, nombre[128];
	if (sscanf(params, "ds[128]", slot, nombre)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editargps (Slot) (Nombre)");
	if (slot < 1 || slot > MAX_UBICACIONES) return SendPlayerChatMessage(playerid, COLOR_WHITE, "GPS no encontrado.");
	format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) movió la ubicación %d del GPS (%s).", InfoCuenta[playerid][jNombre], playerid, slot, nombre);
	SendAdminMessage(0xFFFFFFFF, string);
	new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
	InfoGPS[slot][uPosicion][0] = x;
	InfoGPS[slot][uPosicion][1] = y;
	InfoGPS[slot][uPosicion][2] = z;
	alm(InfoGPS[slot][uNombre], nombre);
	//opción idsql ya creada.
	new query[1028];
	if (InfoGPS[slot][gpsID_sql] != 0)
	{
		mysql_format(db_samp, query, sizeof query, "UPDATE ubicaciones SET Ubicacion = '%e', PotX = '%f', PotY = '%f', PotZ = '%f' WHERE ID = '%d'",
		InfoGPS[slot][uNombre],
		InfoGPS[slot][uPosicion][0],
		InfoGPS[slot][uPosicion][1],
		InfoGPS[slot][uPosicion][2],
		InfoGPS[slot][gpsID_sql]);
		mysql_tquery(db_samp, query);
		slot = MAX_UBICACIONES;
		return 1;
	}
	mysql_format(db_samp, query, sizeof query, "INSERT INTO ubicaciones (Ubicacion, PotX, PotY, PotZ) VALUES ('%e', '%f', '%f', '%f')",
	InfoGPS[slot][uNombre],
	InfoGPS[slot][uPosicion][0],
	InfoGPS[slot][uPosicion][1],
	InfoGPS[slot][uPosicion][2]);
	mysql_tquery(db_samp, query, "OnUbicacionCreate", "i", slot);
	slot = MAX_UBICACIONES;
	return 1;
}
