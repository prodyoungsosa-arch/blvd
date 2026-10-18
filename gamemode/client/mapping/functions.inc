Creando_Objeto_Admin(playerid, id, modelid)
{
	new query[1028];
	GetPlayerPos(playerid, InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ]);
	InfoObjeto[id][oModelo] = modelid;
	InfoObjeto[id][oInterior] = GetPlayerInterior(playerid);
	InfoObjeto[id][oVirtualWorld] = GetPlayerVirtualWorld(playerid);
	InfoObjeto[id][oObjeto] = CreateDynamicObject(InfoObjeto[id][oModelo], InfoObjeto[id][oPotX]-2.0, InfoObjeto[id][oPotY]-1.0, InfoObjeto[id][oPotZ], InfoObjeto[id][oRotX], InfoObjeto[id][oRotY], InfoObjeto[id][oRotZ], .interiorid = InfoObjeto[id][oInterior], .worldid = InfoObjeto[id][oVirtualWorld]);
	edicion_sql_actual[playerid] = id;
	InfoPersonaje[playerid][pEditingMode] = 4;
	EditDynamicObject(playerid, InfoObjeto[id][oObjeto]);
	//opción idsql ya creada.
	if (InfoObjeto[id][oID_sql] != 0)
	{
		mysql_format(db_samp, query, sizeof query, "UPDATE objetos_admin SET Modelo = '%d', PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
		InfoObjeto[id][oModelo],
		InfoObjeto[id][oPotX],
		InfoObjeto[id][oPotY],
		InfoObjeto[id][oPotZ],
		InfoObjeto[id][oRotX],
		InfoObjeto[id][oRotY],
		InfoObjeto[id][oRotZ],
		InfoObjeto[id][oInterior],
		InfoObjeto[id][oVirtualWorld],
		InfoObjeto[id][oID_sql]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	mysql_format(db_samp, query, sizeof query, "INSERT INTO objetos_admin (Modelo, PotX, PotY, PotZ, RotX, RotY, RotZ, Interior, VirtualWorld) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
	InfoObjeto[id][oModelo],
	InfoObjeto[id][oPotX],
	InfoObjeto[id][oPotY],
	InfoObjeto[id][oPotZ],
	InfoObjeto[id][oRotX],
	InfoObjeto[id][oRotY],
	InfoObjeto[id][oRotZ],
	InfoObjeto[id][oInterior],
	InfoObjeto[id][oVirtualWorld]);
	mysql_tquery(db_samp, query, "OnObjetoAdminCreate", "i", id);
	return 1;
}