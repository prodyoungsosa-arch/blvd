noexitcasa(id)
{
	if (IsValidDynamic3DTextLabel(InfoCasa[id][cLabelExt]))
	{
		DestroyDynamic3DTextLabel(InfoCasa[id][cLabelExt]);
		InfoCasa[id][cLabelExt] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoCasa[id][cLabelInt]))
	{
		DestroyDynamic3DTextLabel(InfoCasa[id][cLabelInt]);
		InfoCasa[id][cLabelInt] = Text3D:INVALID_3DTEXT_ID;
	}
	InfoCasa[id][cLabelExt] = CreateDynamic3DTextLabel("casita", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
	InfoCasa[id][cLabelInt] = CreateDynamic3DTextLabel("casita", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
}

LabelPickup_casa(id)
{
	//delete error
	if (IsValidDynamic3DTextLabel(InfoCasa[id][cLabelExt]))
	{
		DestroyDynamic3DTextLabel(InfoCasa[id][cLabelExt]);
		InfoCasa[id][cLabelExt] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoCasa[id][cLabelInt]))
	{
		DestroyDynamic3DTextLabel(InfoCasa[id][cLabelInt]);
		InfoCasa[id][cLabelInt] = Text3D:INVALID_3DTEXT_ID;
	}
	//info new
	new location[MAX_ZONE_NAME], house_label[470], exdireccion[215] = "";
	Get2DZone(location, MAX_ZONE_NAME, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]);
	if (InfoCasa[id][cExteriorVW] == 0 && InfoCasa[id][cExteriorInt] == 0) format(exdireccion, sizeof exdireccion, "{F1C40F}%s", location);
	//3d label
	if (InfoCasa[id][cVenta] != 0) format(house_label, sizeof house_label, "{E67E22}Casa #%d %s\n{CCCCCC}Usa '/detalles' para más información", id, exdireccion);
	else format(house_label, sizeof house_label, "{00CC00}Casa #%d %s en venta\n{CCCCCC}Usa '/detalles' para más información", id, exdireccion);
	InfoCasa[id][cLabelExt] = CreateDynamic3DTextLabel(house_label, -1, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoCasa[id][cExteriorVW], InfoCasa[id][cExteriorInt], -1);
	format(house_label, sizeof house_label, "{E67E22}Salida #%d %s", id, exdireccion);
	InfoCasa[id][cLabelInt] = CreateDynamic3DTextLabel(house_label, -1, InfoCasa[id][cInteriorX], InfoCasa[id][cInteriorY], InfoCasa[id][cInteriorZ]+0.35, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoCasa[id][cInteriorVW], InfoCasa[id][cInteriorInt], -1);
}

GetClaseCasa(x)
{
	new eClase[24];
	switch (x)
	{
		case 1: alm(eClase, "baja");
		case 2: alm(eClase, "media-baja");
		case 3: alm(eClase, "media");
		case 4: alm(eClase, "media-alta");
		case 5: alm(eClase, "alta");
		case 6: alm(eClase, "custom");
	}
	return eClase;
}

SetInteriorCasa(playerid, id, interior)
{
	new Float: x, Float: y, Float: z, Float: r, int, clase;
	switch (interior)
	{
		//baja
		case 1: x = 266.5080, y = 304.9096, z = 999.1484, r = 271.8487, int = 2, clase = 1;
		case 2: x = 2218.4019, y = -1076.2317, z = 1050.4844, r = 94.0354, int = 1, clase = 1;
		case 3: x = 2233.7324, y = -1115.2200, z = 1050.8828, r = 4.4446, int = 5, clase = 1;
		//media-baja
		case 4: x = 2468.8379, y = -1698.2688, z = 1013.5078, r = 90.6120, int = 2, clase = 2;
		case 5: x = 217.2689, y = 1275.1978, z = 1059.0253, r = 1.2881, int = 4, clase = 2;
		case 6: x = 295.1263, y = 1472.2615, z = 1080.2578, r = 358.1545, int = 15, clase = 2;
		case 7: x = 226.7467, y = 1239.9583, z = 1082.1406, r = 87.4319, int = 2, clase = 2;
		//media
		case 8: x = 2270.4004, y = -1210.5198, z = 1047.5625, r = 91.5055, int = 10, clase = 3;
		case 9: x = 2196.8484, y = -1204.3329, z = 1049.0234, r = 94.3722, int = 6, clase = 3;
		//media-alta
		case 10: x = 83.0492, y = 1322.2887, z = 1083.8662, r = 0.9745, int = 9, clase = 4;
		case 11: x = 2317.7004, y = -1026.5896, z = 1050.2178, r = 7.2412, int = 9, clase = 4;
		case 12: x = 2324.4644, y = -1149.5463, z = 1050.7101, r = 2.8840, int = 12, clase = 4;
		//alta
		case 13: x = 140.2607, y = 1365.9283, z = 1083.8594, r = 3.7945, int = 5, clase = 5;
		case 14: x = 1260.6597, y = -785.3624, z = 1091.9063, r = 272.6137, int = 5, clase = 5;
		// news
		case 31: x = 223.4847, y = 1273.2301, z = 1082.2358, r = 0.0000, int = 31, clase = 2; // baja
		case 32: x = 326.3992, y = 1455.8674, z = 1084.4762, r = 0.0000, int = 32, clase = 3; // media
		case 33: x = 275.8466, y = 1237.4669, z = 1084.2766, r = 0.0000, int = 33, clase = 3; // media
		case 34: x = 267.7001, y = 1186.7664, z = 1080.2880, r = 0.0000, int = 34, clase = 4; // alta
		case 35: x = 24.2930, y = 1320.6143, z = 1084.4135, r = 0.0000, int = 35, clase = 4; // alta
		case 36: x = 2308.3157, y = -1198.4255, z = 1049.0031, r = 0.0000, int = 36, clase = 2; // baja
		case 37: x = 235.5607, y = 1127.8301, z = 1081.0802, r = 0.0000, int = 37, clase = 4; // alta
		case 38: x = 268.5897, y = 1063.5112, z = 1084.1886, r = 0.0000, int = 38, clase = 4; // alta
		case 39: x = 140.2896, y = 1396.3381, z = 1083.9066, r = 0.0000, int = 39, clase = 4; // media-alta
		case 40: x = 250.9502, y = 994.3570, z = 1084.7968, r = 90.0000, int = 40, clase = 4; // alta
		case 41: x = 2373.5054, y = -1183.8835, z = 1053.2743, r = 0.0000, int = 41, clase = 3; // media-alta
		case 42: x = -79.8856, y = 1383.2831, z = 1079.0179, r = 0.0000, int = 42, clase = 2; // baja
		case 43: x = -48.3364, y = 1458.5081, z = 1085.6765, r = 90.0000, int = 43, clase = 2; // baja
		case 44: x = 310.9045, y = 327.6914, z = 1003.3773, r = 90.0000, int = 44, clase = 3; // media
		case 45: x = 2298.0796, y = -1093.8049, z = 1048.9131, r = 90.0000, int = 45, clase = 2; // baja
		case 46: x = 2254.8901, y = -1112.7531, z = 1049.1902, r = 0.0000, int = 46, clase = 1; // habitación
		case 47: x = 2189.3179, y = -1073.4624, z = 1050.7418, r = 90.0000, int = 47, clase = 1; // habitación
		case 48: x = 360.4886, y = 304.1310, z = 996.8765, r = -90.0000, int = 48, clase = 1; // habitación
		case 49: x = 265.6623, y = 321.4920, z = 997.2649, r = -90.0000, int = 49, clase = 1; // habitación
		case 50: x = 242.3355, y = 323.1314, z = 999.7263, r = -90.0000, int = 50, clase = 1; // habitación
		case 51: x = 1376.5623, y = 2169.8779, z = -40.4082, r = 0.0000, int = 51, clase = 6; // custom
	}
	if (playerid == -1)
	{
		new string[370];
		InfoCasa[id][cInteriorX] = x;
		InfoCasa[id][cInteriorY] = y;
		InfoCasa[id][cInteriorZ] = z;
		InfoCasa[id][cInteriorR] = r;
		InfoCasa[id][cInteriorInt] = int;
		InfoCasa[id][cTipo] = clase;
		mysql_format(db_samp, string, sizeof string, "UPDATE casas SET Interior_X = '%f', Interior_Y = '%f', Interior_Z = '%f', Interior_R = '%f', Interior_Int = '%d', Tipo = '%d' WHERE ID = '%d'", InfoCasa[id][cInteriorX], InfoCasa[id][cInteriorY], InfoCasa[id][cInteriorZ], InfoCasa[id][cInteriorR], InfoCasa[id][cInteriorInt], InfoCasa[id][cTipo], InfoCasa[id][cID_sql]);
		mysql_tquery(db_samp, string);
	}
	else
	{
		new string[170];
		SetPlayerPosEx(playerid, x, y, z);
		SetPlayerInterior(playerid, int);
		SetPlayerVirtualWorld(playerid, playerid);
		format(string, sizeof string, "Estás en el interior %d, clase: %s.", interior, GetClaseCasa(clase));
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	}
	return 1;
}

CountCasas(playerid)
{
	new count = 0;
	Loop(id, totalcasas, 1) if (InfoCasa[id][cVenta] != 0 && InfoCasa[id][cTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cPropietario], true) == 0)
	{
		count++;
	}
	return count;
}

PermisosCasa(playerid, id)
{
	if (InfoCasa[id][cVenta] != 0 && InfoCasa[id][cTipo] != 0)
	{
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cPropietario], true) == 0)
		{
			return 1;
		}
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida1], true) == 0)
		{
			return 1;
		}
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida2], true) == 0)
		{
			return 1;
		}
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida3], true) == 0)
		{
			return 1;
		}
	}
	return 0;
}

LlavesCasa(playerid, id)
{
	if (InfoCasa[id][cVenta] != 0 && InfoCasa[id][cTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cPropietario], true) == 0)
	{
		return 1;
	}
	return 0;
}

CheckHouse()
{
	new countH = 0, gformat[320];
	//casas
	Loop(id, totalcasas, 1) if (InfoCasa[id][cTipo] != 0 && InfoCasa[id][cVenta] != 0 && InfoCasa[id][cPremium] == 0)
	{
		if (InfoCasa[id][cTiempoDisponible] < gettime())
		{
			countH++;
			//limpiar casa
			if (VerificarPersonaje(InfoCasa[id][cPropietario]))
			{
				new dinero;
				rebel_int(0, "BolosUwU", dinero);
				dinero+=InfoCasa[id][cPrecio];
				mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET BolosUwU = '%d' WHERE Nombre_Apellido = '%e'", dinero, InfoCasa[id][cPropietario]);
				mysql_tquery(db_samp, gformat);
			}
			ClearPropiedad(id);
		}
	}
	//printf("|- Se vendieron %d casas inactivas.", countH);
	return 1;
}

funcion VisitandoCasa(playerid, i)
{
	SetPosEx(playerid, InfoCasa[i][cExteriorX], InfoCasa[i][cExteriorY], InfoCasa[i][cExteriorZ], InfoCasa[i][cExteriorR], InfoCasa[i][cExteriorInt], InfoCasa[i][cExteriorVW], 1);
	SetCameraBehindPlayer(playerid);
	KillTimer(VisitaTimer[playerid]);
	return 1;
}

CasaShareShow(playerid)
{
	new id = EnCasa(playerid), gformat[370], dialog_show[1028];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	//slot1
	if (strcmp(InfoCasa[id][cCompartida1], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 1\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 1:{59F37B} %s\n", InfoCasa[id][cCompartida1]);
		strcat(dialog_show, gformat);
	}
	//slot2
	if (strcmp(InfoCasa[id][cCompartida2], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 2\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 2:{59F37B} %s\n", InfoCasa[id][cCompartida2]);
		strcat(dialog_show, gformat);
	}
	//slot3
	if (strcmp(InfoCasa[id][cCompartida3], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 3\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 3:{59F37B} %s\n", InfoCasa[id][cCompartida3]);
		strcat(dialog_show, gformat);
	}
	//dialog preview
	Dialog_Show(playerid, CompartirCasa, DIALOG_STYLE_LIST, "Permisos de tu casa", dialog_show, "Continuar", "Volver");
	return 1;
}

IsValidInterior(interior)
{
	switch (interior)
	{
		case 1..14: return 1;
		case 31..51: return 1;
	}
	return 0;
}

ClearPropiedad(id) //renovado by EdinsonWalker (16-01-2020)
{
	new query[370];
	InfoCasa[id][cSeguro] = 1;
	alm(InfoCasa[id][cPropietario], "gobielno");
	InfoCasa[id][cVenta] = 0; // Casa en venta.
	InfoCasa[id][cDinero] = 0;
	InfoCasa[id][cTiempoDisponible] = -1;
	alm(InfoCasa[id][cCompartida1], "none");
	alm(InfoCasa[id][cCompartida2], "none");
	alm(InfoCasa[id][cCompartida3], "none");
	Loop(x, 10, 0)
	{
		InfoCasa[id][cArmario][x] = 0;
		InfoCasa[id][cArmarioCant][x] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Armario%d = 0 , ArmarioCant%d = 0 WHERE ID = '%d'", x+1, x+1, InfoCasa[id][cID_sql]);
		mysql_tquery(db_samp, query);
	}
	mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Propietario = '%e', Seguro = 1, Venta = 0, BolosUwU = 0, TiempoDisponible = -1 WHERE ID = '%d'", InfoCasa[id][cPropietario], InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, query);
	mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoCasa[id][cCompartida1], InfoCasa[id][cCompartida2], InfoCasa[id][cCompartida3], InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, query);
    LabelPickup_casa(id);
}

EnCasa(playerid) //new by EdinsonWalker, 16/01/2020
{
	Loop(id, totalcasas, 1) if (InfoCasa[id][cInteriorVW] != 0)
	{
		if (InfoCasa[id][cInteriorInt] == InfoPersonaje[playerid][pInterior] && InfoCasa[id][cInteriorVW] == InfoPersonaje[playerid][pVirtualWorld])
		{
			return id;
		}
	}
	return -1;
}