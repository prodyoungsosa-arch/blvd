//Jugadores
cmd:vercasa(playerid)
{
	if (!CheckTimer(60, VisitaTimer2[playerid]))
	{
		Loop(p, totalcasas, 1) if (InfoCasa[p][cTipo] != 0)
		{
			if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[p][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[p][cExteriorVW])
			{
				if (InfoCasa[p][cVenta] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes revisar una casa con propietario.");
				SetPosEx(playerid, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ], InfoCasa[p][cInteriorR], InfoCasa[p][cInteriorInt], InfoCasa[p][cInteriorVW], 0);
	  			SetCameraBehindPlayer(playerid);
	  			SendPlayerChatMessage(playerid, COLOR_PURPLE, "** Acceso a revisar la casa en venta por treinta (30) segundos **");
				VisitaTimer[playerid] = SetTimerEx("VisitandoCasa", 30000, false, "ii", playerid, p);
				VisitaTimer2[playerid] = gettime();
	        	return 1;
	       	}
		}
		SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en la entrada de ninguna casa.");
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(60, VisitaTimer2[playerid]) ));
	}
	return 1;
}

cmd:comprarcasa(playerid)
{
    new string[512], p = -1;
	Loop(x, sizeof InfoCasa, 0) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[x][cExteriorX], InfoCasa[x][cExteriorY], InfoCasa[x][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[x][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[x][cExteriorVW])
	{
		p = x;
		break;
	}
	if (p == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en la entrada de ninguna casa.");
	if (InfoCasa[p][cVenta] != 0) return SendPlayerChatMessage( playerid, COLOR_GREY, "* Esta casa ya tiene dueño.");
	if (GetPlayerCash(playerid) < InfoCasa[p][cPrecio])
	{
		format(string, sizeof string, "* Te hacen falta $%s para comprar esta casa.", diner_coma(InfoCasa[p][cPrecio]-GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_GREY, string);
		return 1;
	}
	if (CountCasas(playerid) >= InfoCuenta[playerid][jMaxCasas]) return SendClientMessageEx(playerid, COLOR_GREY, "* No puedes tener más de %d casas.", InfoCuenta[playerid][jMaxCasas]);
	InfoCasa[p][cVenta] = 1;
	new k = gettime();
	k += 1296000;
	InfoCasa[p][cTiempoDisponible] = k;
	alm(InfoCasa[p][cPropietario], InfoPersonaje[playerid][pNombre_Apellido]);
	GivePlayerCash(playerid, -InfoCasa[p][cPrecio], "comprar casa");
	Tax += (InfoCasa[p][cPrecio] * 40 ) / ( 100 );
	SetPlayerPosEx(playerid, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ]);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicitaciones por tu nueva compra!");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Escribe {3E62F4}/ayuda casa{FFFFFF} para ver los comandos disponibles!");
	mysql_format(db_samp, string, sizeof string, "UPDATE casas SET Venta = 1, Propietario = '%e', TiempoDisponible = '%d' WHERE ID = '%d'", InfoCasa[p][cPropietario], InfoCasa[p][cTiempoDisponible], InfoCasa[p][cID_sql]);
	mysql_tquery(db_samp, string);
	format(string, sizeof string, "%s compró la casa ID %d por $%s.", NombreDeCuenta(playerid), p, diner_coma(InfoCasa[p][cPrecio]));
	Log("f_logs/house.log", string);
	LabelPickup_casa(p);
	return 1;
}

cmd:timbre(playerid)
{
    new string[256], h = -1;
	Loop(x, sizeof InfoCasa, 0) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[x][cExteriorX], InfoCasa[x][cExteriorY], InfoCasa[x][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[x][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[x][cExteriorVW])
	{
		h = x;
		break;
	}
	if (h == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en la entrada de ninguna casa.");
	foreach(Player, i) if (InfoPersonaje[i][pInterior] == InfoCasa[h][cInteriorInt] && InfoPersonaje[i][pVirtualWorld] == InfoCasa[h][cInteriorVW])
	{
		format(string,sizeof string, "Timbre de %s suena.", InfoCasa[h][cPropietario]);
		SendPlayerChatMessage(i, COLOR_PURPLE, string);
		GameTextForPlayer(i, "~n~~n~~n~~n~~n~~n~~n~~n~~p~Timbre...", 4000, 3);
	}
	if (InfoCasa[h][cVenta] != 0) format(string, sizeof string, "presiona el timbre de la casa de %s.", InfoCasa[h][cPropietario]);
	else format(string, sizeof string, "presiona el timbre de la casa %d.", h);
	rol_auto(playerid, string);
	return 1;
}

cmd:vendercasa(playerid)
{
    new string[256], casa = -1;
	Loop(x, sizeof InfoCasa, 0) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[x][cExteriorX], InfoCasa[x][cExteriorY], InfoCasa[x][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[x][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[x][cExteriorVW])
	{
		casa = x;
		break;
	}
	if (casa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en la entrada de ninguna casa.");
	if (LlavesCasa(playerid, casa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres dueño de esta casa.");
	if (InfoCasa[casa][cPremium] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes vender una casa que compraste con monedas.");
	ClearPropiedad(casa);
	GivePlayerCash(playerid, InfoCasa[casa][cPrecio], "vender casa");
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	if (InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[casa][cInteriorVW]) SetPosEx(playerid,InfoCasa[casa][cExteriorX], InfoCasa[casa][cExteriorY], InfoCasa[casa][cExteriorZ], InfoCasa[casa][cExteriorR], InfoCasa[casa][cExteriorInt], InfoCasa[casa][cExteriorVW], 1);
	format(string, sizeof string, "~w~Vendiste tu casa por ~n~~g~$%s", diner_coma(InfoCasa[casa][cPrecio]));
	GameTextForPlayer(playerid, string, 4000, 3);
	format(string,sizeof string, "%s vendió su casa (ID %d) for $%s.", NombreDeCuenta(playerid), casa, diner_coma(InfoCasa[casa][cPrecio]));
	Log("f_logs/house.log", string);
	return 1;
}

cmd:cseguro(playerid)
{
	new casa = -1;
	Loop(x, totalcasas, 1)
	{
		if ((IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[x][cExteriorX], InfoCasa[x][cExteriorY], InfoCasa[x][cExteriorZ]) && InfoCasa[x][cExteriorInt] == InfoPersonaje[playerid][pInterior] && InfoCasa[x][cExteriorVW] == InfoPersonaje[playerid][pVirtualWorld]) ||
		(IsPlayerInRangeOfPoint(playerid, 5.0, InfoCasa[x][cInteriorX], InfoCasa[x][cInteriorY], InfoCasa[x][cInteriorZ]) && InfoCasa[x][cInteriorInt] == InfoPersonaje[playerid][pInterior] && InfoCasa[x][cInteriorVW] == InfoPersonaje[playerid][pVirtualWorld]) )
		{
			casa = x;
		}
	}
	if (casa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en la entrada o salida de alguna casa.");
	if (PermisosCasa(playerid, casa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (!InfoCasa[casa][cSeguro])
	{
		InfoCasa[casa][cSeguro] = 1;
		rol_ame(playerid, "saca sus llaves de casa y la cierra.");
	}
	else if (InfoCasa[casa][cSeguro])
	{
		InfoCasa[casa][cSeguro] = 0;
		rol_ame(playerid, "saca sus llaves de casa y la abre.");
	}
	guardar_int_mysql("casas", "Seguro", InfoCasa[casa][cID_sql], InfoCasa[casa][cSeguro]);
	return 1;
}
alias:cseguro("casaseguro");

cmd:casamenu(playerid)
{
	new casa = EnCasa(playerid);
	if (casa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, casa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	Dialog_Show(playerid, CasaOpciones, DIALOG_STYLE_LIST, "Menú de casa", "- Dinero\n- Armario\n- Permisos de casa", "Continuar", "Salir");
	return 1;
}
alias:casamenu("menucasa", "casa");

cmd:garmario(playerid)
{
	new id = EnCasa(playerid), gformat[370];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano derecha.");
	new objeto = InfoPersonaje[playerid][pManoDerecha], objetocant = InfoPersonaje[playerid][pManoDerechaCant];
	new rSlot = -1;
	Loop(xs, 10, 0) if (InfoCasa[id][cArmario][xs] == 0)
	{
		rSlot = xs;
		break;
	}
	if (rSlot == -1) return SendPlayerChatMessage(playerid, COLOR_RED, "No puedes guardar más cosas en tu armario, máximo 10 slots.");
	InfoCasa[id][cArmario][rSlot] = objeto;
	InfoCasa[id][cArmarioCant][rSlot] = objetocant;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE casas SET Armario%d = '%d', ArmarioCant%d = '%d' WHERE ID = '%d'", rSlot+1, objeto, rSlot+1, objetocant, InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, gformat);
	ResetPlayerWeapons(playerid);
	RemovePlayerAttachedObject(playerid, 7);
	InfoPersonaje[playerid][pManoDerecha] = 0;
	InfoPersonaje[playerid][pManoDerechaCant] = 0;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, gformat);
	if (objetocant == 0 || objetocant == 1) format(gformat, sizeof gformat, "Guardaste en el armario tu %s.", InfoInventario[objeto][NombreObjeto]);
	else
	{
		if (InfoInventario[objeto][IDArma] != 0)
		{
			format(gformat, sizeof gformat, "%s guarda %s en casa (SQL %d).", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto], InfoCasa[id][cID_sql]);
			Log("f_logs/Casa.log", gformat);
			format(gformat, sizeof gformat, "Guardaste en el armario tu %s con %d balas.", InfoInventario[objeto][NombreObjeto], objetocant);
		}
		else format(gformat, sizeof gformat, "Guardaste en el armario tu %s con %d de cantidad.", InfoInventario[objeto][NombreObjeto], objetocant);
	}
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
	format(gformat, sizeof gformat, "guarda en el armario su %s.", InfoInventario[objeto][NombreObjeto]);
	rol_ame(playerid, gformat);
	return 1;
}
alias:garmario("guardararmario");

cmd:sarmario(playerid, params[])
{
	new id = EnCasa(playerid), gformat[370];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes un objeto en tu mano derecha.");
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Tienes restricción de armas por dos horas.");
	new rSlot;
	if (sscanf(params, "i", rSlot))
	{
		new count = 0;
		Loop(xs, 10, 0) if (InfoCasa[id][cArmario][xs] != 0) count++;
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu armario.");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utiliza: /sarmario (Slot)");
		Loop(xs, 10, 0) if (InfoCasa[id][cArmario][xs] != 0)
		{
			format(gformat, sizeof gformat, "Tienes en {b42d2d}slot %d{EBEBEB}: %s", xs+1, slot_objeto(InfoCasa[id][cArmario][xs], InfoCasa[id][cArmarioCant][xs]));
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, gformat);
		}
		return 1;
	}
	if (rSlot < 1 || rSlot > 10) { SendPlayerChatMessage(playerid, COLOR_GREY, "El número de slot debe estar entre 1 y 10."); return 1; }
	rSlot--;
	if (InfoCasa[id][cArmario][rSlot] == 0) return SendPlayerChatMessage(playerid, COLOR_RED, "No tienes nada en ese slot.");
	new objeto = InfoCasa[id][cArmario][rSlot], objetocant = InfoCasa[id][cArmarioCant][rSlot];
	InfoCasa[id][cArmario][rSlot] = 0;
	InfoCasa[id][cArmarioCant][rSlot] = 0;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE casas SET Armario%d = 0, ArmarioCant%d = 0 WHERE ID = '%d'", rSlot+1, rSlot+1, InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, gformat);
	InfoPersonaje[playerid][pManoDerecha] = objeto;
	InfoPersonaje[playerid][pManoDerechaCant] = objetocant;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", objeto, objetocant, InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, gformat);
	if (objetocant == 1 || objetocant == 0) format(gformat, sizeof gformat, "Sacaste tu %s del armario.", InfoInventario[objeto][NombreObjeto]);
	else
	{
		if (InfoInventario[objeto][IDArma] != 0) format(gformat, sizeof gformat, "Sacaste tu %s con %d balas del armario.", InfoInventario[objeto][NombreObjeto], objetocant);
		else format(gformat, sizeof gformat, "Sacaste tu %s con %d de cantidad del armario.", InfoInventario[objeto][NombreObjeto], objetocant);
	}
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
	format(gformat, sizeof gformat, "saca su %s del armario.", InfoInventario[objeto][NombreObjeto]);
	rol_ame(playerid, gformat);
	ResetPlayerWeapons(playerid);
	if (InfoInventario[objeto][IDArma] > 0)
	{
		format(gformat, sizeof gformat, "%s saca %s de casa (SQL %d).", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto], InfoCasa[id][cID_sql]);
		Log("f_logs/Casa.log", gformat);
		GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], objetocant);
	}
	PonerObjeto(playerid, 1, objeto);
	return 1;
}
alias:sarmario("sacararmario");

//Administrativo
cmd:crearcasa(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new interior, precio, gformat[210];
	if (sscanf(params, "dd", interior, precio)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearcasa (InteriorID) (Precio)");
	if (IsValidInterior(interior) == 0) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Sólo hay interiores ID desde 1-14, 31-51. Si quieres saber las ID usa: /VerInterior");
	if (interior == 5) return SendPlayerChatMessage(playerid, -1, "No existe saludos jasjajsa.");
	Loop(cid, MAX_CASAS, 1) if (!InfoCasa[cid][cTipo])
	{
		GetPlayerPos(playerid, InfoCasa[cid][cExteriorX], InfoCasa[cid][cExteriorY], InfoCasa[cid][cExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoCasa[cid][cExteriorR]);
		InfoCasa[cid][cExteriorVW] = GetPlayerVirtualWorld(playerid);
		InfoCasa[cid][cExteriorInt] = GetPlayerInterior(playerid);
		InfoCasa[cid][cSeguro] = 1;
		InfoCasa[cid][cTiempoDisponible] = -1;
		InfoCasa[cid][cVenta] = 0;
		alm(InfoCasa[cid][cPropietario], "gobielno");
		InfoCasa[cid][cPrecio] = precio;
		new Float: x, Float: y, Float: z, Float: r, int, clase, vw = 400+cid;
		switch (interior)
		{

			case 1: x = 871.8456, y = -25.5141, z = 53.6920, r = 355.9342, int = 2, clase = 1, vw = 55367;
			case 2: x = 2335.5103, y = -1046.7898, z = 44.0400, r = 185.8437, int = 1, clase = 1, vw = 55499;
			case 3: x = 2233.7324, y = -1115.2200, z = 1050.8828, r = 4.4446, int = 5, clase = 1, vw = 400+cid;
			
			//media-baja
			case 4: x = 2468.8379, y = -1698.2688, z = 1013.5078, r = 90.6120, int = 2, clase = 2, vw = 400+cid;
			case 5: x = 217.2689, y = 1275.1978, z = 1059.0253, r = 1.2881, int = 4, clase = 2, vw = 400+cid;
			case 6: x = 295.1263, y = 1472.2615, z = 1080.2578, r = 358.1545, int = 15, clase = 2, vw = 400+cid;
			case 7: x = 226.7467, y = 1239.9583, z = 1082.1406, r = 87.4319, int = 2, clase = 2, vw = 400+cid;
			
			//media
			case 8: x = 2270.4004, y = -1210.5198, z = 1047.5625, r = 91.5055, int = 10, clase = 3, vw = 400+cid;
			case 9: x = 2196.8484, y = -1204.3329, z = 1049.0234, r = 94.3722, int = 6, clase = 3, vw = 400+cid;
			
			//media-alta
			case 10: x = 83.0492, y = 1322.2887, z = 1083.8662, r = 0.9745, int = 9, clase = 4, vw = 400+cid;
			case 11: x = 2317.7004, y = -1026.5896, z = 1050.2178, r = 7.2412, int = 9, clase = 4, vw = 400+cid;
			case 12: x = 2324.4644, y = -1149.5463, z = 1050.7101, r = 2.8840, int = 12, clase = 4, vw = 400+cid;
			
			//alta
			case 13: x = 140.2607, y = 1365.9283, z = 1083.8594, r = 3.7945, int = 5, clase = 5, vw = 400+cid;
			case 14: x = 1260.6597, y = -785.3624, z = 1091.9063, r = 272.6137, int = 5, clase = 5, vw = 400+cid;
			
			// news
			case 31: x = 223.4847, y = 1273.2301, z = 1082.2358, r = 0.0000, int = 31, clase = 2, vw = 400+cid; // baja
			case 32: x = 326.3992, y = 1455.8674, z = 1084.4762, r = 0.0000, int = 32, clase = 3, vw = 400+cid; // media
			case 33: x = 275.8466, y = 1237.4669, z = 1084.2766, r = 0.0000, int = 33, clase = 3, vw = 400+cid; // media
			case 34: x = 267.7001, y = 1186.7664, z = 1080.2880, r = 0.0000, int = 34, clase = 4, vw = 400+cid; // alta
			case 35: x = 24.2930, y = 1320.6143, z = 1084.4135, r = 0.0000, int = 35, clase = 4, vw = 400+cid; // alta
			case 36: x = 2308.3157, y = -1198.4255, z = 1049.0031, r = 0.0000, int = 36, clase = 2, vw = 400+cid; // baja
			case 37: x = 235.5607, y = 1127.8301, z = 1081.0802, r = 0.0000, int = 37, clase = 4, vw = 400+cid; // alta
			case 38: x = 268.5897, y = 1063.5112, z = 1084.1886, r = 0.0000, int = 38, clase = 4, vw = 400+cid; // alta
			case 39: x = 140.2896, y = 1396.3381, z = 1083.9066, r = 0.0000, int = 39, clase = 4, vw = 400+cid; // media-alta
			case 40: x = 250.9502, y = 994.3570, z = 1084.7968, r = 90.0000, int = 40, clase = 4, vw = 400+cid; // alta
			case 41: x = 2373.5054, y = -1183.8835, z = 1053.2743, r = 0.0000, int = 41, clase = 3, vw = 400+cid; // media-alta
			case 42: x = -79.8856, y = 1383.2831, z = 1079.0179, r = 0.0000, int = 42, clase = 2, vw = 400+cid; // baja
			case 43: x = -48.3364, y = 1458.5081, z = 1085.6765, r = 90.0000, int = 43, clase = 2, vw = 400+cid; // baja
			case 44: x = 310.9045, y = 327.6914, z = 1003.3773, r = 90.0000, int = 44, clase = 3, vw = 400+cid; // media
			case 45: x = 2298.0796, y = -1093.8049, z = 1048.9131, r = 90.0000, int = 45, clase = 2, vw = 400+cid; // baja
			case 46: x = 2254.8901, y = -1112.7531, z = 1049.1902, r = 0.0000, int = 46, clase = 1, vw = 400+cid; // habitación
			case 47: x = 2189.3179, y = -1073.4624, z = 1050.7418, r = 90.0000, int = 47, clase = 1, vw = 400+cid; // habitación
			case 48: x = 360.4886, y = 304.1310, z = 996.8765, r = -90.0000, int = 48, clase = 1, vw = 400+cid; // habitación
			case 49: x = 265.6623, y = 321.4920, z = 997.2649, r = -90.0000, int = 49, clase = 1, vw = 400+cid; // habitación
			case 50: x = 242.3355, y = 323.1314, z = 999.7263, r = -90.0000, int = 50, clase = 1, vw = 400+cid; // habitación
			case 51: x = 1376.5623, y = 2169.8779, z = -40.4082, r = 0.0000, int = 51, clase = 6, vw = 400+cid; // custom
		}
		InfoCasa[cid][cTipo] = clase;
		InfoCasa[cid][cInteriorX] = x;
		InfoCasa[cid][cInteriorY] = y;
		InfoCasa[cid][cInteriorZ] = z;
		InfoCasa[cid][cInteriorR] = r;
		InfoCasa[cid][cInteriorInt] = int;
		InfoCasa[cid][cInteriorVW] = vw;
		format(gformat, sizeof gformat, "Casa nueva ID: %d - Precio: $%s - Clase: %s.", cid, diner_coma(precio), GetClaseCasa(clase));
		SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
		LabelPickup_casa(cid);
		new que2ry[1000], query[1500];
		//opción idsql ya creada.
		if (InfoCasa[cid][cID_sql] != 0)
		{
			format(que2ry, sizeof que2ry, "UPDATE casas SET Propietario = '%s', Tipo = '%d', Seguro = '%d', Venta = '%d', Exterior_X = '%f', Exterior_Y = '%f', Exterior_Z = '%f', Exterior_R = '%f', Exterior_Int = '%d', Exterior_VW = '%d',",
			InfoCasa[cid][cPropietario],
			InfoCasa[cid][cTipo],
			InfoCasa[cid][cSeguro],
			InfoCasa[cid][cVenta],
			InfoCasa[cid][cExteriorX],
			InfoCasa[cid][cExteriorY],
			InfoCasa[cid][cExteriorZ],
			InfoCasa[cid][cExteriorR],
			InfoCasa[cid][cExteriorInt],
			InfoCasa[cid][cExteriorVW]);
			mysql_format(db_samp, query, sizeof query, "%s Interior_X = '%f', Interior_Y = '%f', Interior_Z = '%f', Interior_R = '%f', Interior_Int = '%d', Interior_VW = '%d', Precio = '%d', TiempoDisponible = '%d' WHERE ID = '%d'",
			que2ry,
			InfoCasa[cid][cInteriorX],
			InfoCasa[cid][cInteriorY],
			InfoCasa[cid][cInteriorZ],
			InfoCasa[cid][cInteriorR],
			InfoCasa[cid][cInteriorInt],
			InfoCasa[cid][cInteriorVW],
			InfoCasa[cid][cPrecio],
			InfoCasa[cid][cTiempoDisponible],
			InfoCasa[cid][cID_sql]);
			mysql_tquery(db_samp, query);
			cid = MAX_CASAS;
			return 1;
		}
		format(que2ry, sizeof que2ry, "INSERT INTO casas (Propietario, Tipo, Seguro, Venta, Exterior_X, Exterior_Y, Exterior_Z, Exterior_R, Exterior_Int, Exterior_VW, Interior_X, Interior_Y, Interior_Z, Interior_R, Interior_Int, Interior_VW, Precio, TiempoDisponible)");
		mysql_format(db_samp, query, sizeof query, "%s VALUES ('%e', '%d', '%d',  '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d')",
		que2ry,
		InfoCasa[cid][cPropietario],
		InfoCasa[cid][cTipo],
		InfoCasa[cid][cSeguro],
		InfoCasa[cid][cVenta],
		InfoCasa[cid][cExteriorX],
		InfoCasa[cid][cExteriorY],
		InfoCasa[cid][cExteriorZ],
		InfoCasa[cid][cExteriorR],
		InfoCasa[cid][cExteriorInt],
		InfoCasa[cid][cExteriorVW],
		InfoCasa[cid][cInteriorX],
		InfoCasa[cid][cInteriorY],
		InfoCasa[cid][cInteriorZ],
		InfoCasa[cid][cInteriorR],
		InfoCasa[cid][cInteriorInt],
		InfoCasa[cid][cInteriorVW],
		InfoCasa[cid][cPrecio],
		InfoCasa[cid][cTiempoDisponible]);
		mysql_tquery(db_samp, query, "OnCasaCreate", "i", cid);
		cid = MAX_CASAS;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_RED, "Se alcanzó el máximo de casas (500)");
	return 1;
}

cmd:borrarcasa(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, gformat[235], query[1028];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "USA: /borrarcasa [Casa ID]");
	if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
	if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
	//por si tenia dueño
	foreach(Player, p) if (IsPlayerConnectedEx(p) && LlavesCasa(p, id))
	{
		format(gformat, sizeof gformat, "Admin %s borró tu casa %d.", NombreOriginal(playerid), id);
		SendPlayerChatMessage(playerid, COLOR_ORANGE, gformat);
	}
	//muebles
	BorrarMueblesCasas(id);
	//destroy pickup+label
	noexitcasa(id);
	//clear sell
	InfoCasa[id][cSeguro] = 1;
	alm(InfoCasa[id][cPropietario], "gobielno");
	InfoCasa[id][cVenta] = 0; // Casa en venta.
	InfoCasa[id][cDinero] = 0;
	Loop(x, 10, 0)
	{
		InfoCasa[id][cArmario][x] = 0;
		InfoCasa[id][cArmarioCant][x] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Armario%d = 0 , ArmarioCant%d = 0 WHERE ID = '%d'", x+1, x+1, InfoCasa[id][cID_sql]);
		mysql_tquery(db_samp, query);
	}
	mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Propietario = '%e', Seguro = 1, Venta = 0, BolosUwU = 0 WHERE ID = '%d'", InfoCasa[id][cPropietario], InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, query);
	//coordenadas
	InfoCasa[id][cExteriorX] = 0.0;
	InfoCasa[id][cExteriorY] = 0.0;
	InfoCasa[id][cExteriorZ] = 0.0;
	InfoCasa[id][cExteriorR] = 0.0;
	InfoCasa[id][cExteriorInt] = 0;
	InfoCasa[id][cExteriorVW] = 0;
	InfoCasa[id][cInteriorX] = 0.0;
	InfoCasa[id][cInteriorY] = 0.0;
	InfoCasa[id][cInteriorZ] = 0.0;
	InfoCasa[id][cInteriorR] = 0.0;
	InfoCasa[id][cInteriorInt] = 0;
	InfoCasa[id][cInteriorVW] = 0;
	InfoCasa[id][cPremium] = 0;
	InfoCasa[id][cTiempoDisponible] = -1;
	alm(InfoCasa[id][cCompartida1], "none");
	alm(InfoCasa[id][cCompartida2], "none");
	alm(InfoCasa[id][cCompartida3], "none");
	//otros
	InfoCasa[id][cPrecio] = 0;
	InfoCasa[id][cTipo] = 0;
	mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Exterior_X = 0.0, Exterior_Y = 0.0, Exterior_Z = 0.0, Exterior_R = 0.0, Exterior_Int = 0, Exterior_VW = 0, Interior_X = 0.0, Interior_Y = 0.0, Interior_Z = 0.0, Interior_R = 0.0, Interior_Int = 0 WHERE ID = '%d'", InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, query);
	mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Premium = 0, Interior_VW = 0, Precio = 0, Tipo = 0, TiempoDisponible = -1, Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoCasa[id][cCompartida1], InfoCasa[id][cCompartida2], InfoCasa[id][cCompartida3], InfoCasa[id][cID_sql]);
	mysql_tquery(db_samp, query);
	//mensaje
	format(gformat, sizeof gformat, "Borraste la casa ID %d, SQL vacía: %d", id, InfoCasa[id][cID_sql]);
	SendPlayerChatMessage(playerid, -1, gformat);
	return 1;
}

cmd:irintcasa(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new house;
	if (sscanf(params, "d", house)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /irintcasa (CasaID)");
    if (house < 1 || house > totalcasas) return SendPlayerChatMessage(playerid, COLOR_GREY, "Casa no encontrada.");
	if (InfoCasa[house][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
	SetPosEx(playerid, InfoCasa[house][cInteriorX], InfoCasa[house][cInteriorY], InfoCasa[house][cInteriorZ], InfoCasa[house][cInteriorR], InfoCasa[house][cInteriorInt], InfoCasa[house][cInteriorVW], 1);
	GameTextForPlayer(playerid, "~w~Teletransportado", 5000, 1);
	return 1;
}

cmd:verinterior(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new interior;
	if (sscanf(params, "d", interior)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /verinterior (InteriorID)");
	if (IsValidInterior(interior) == 0) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Sólo hay interiores ID desde 1-14, 31-51. Si quieres saber las ID usa: /VerInterior");
	if (interior == 5) return SendPlayerChatMessage(playerid, -1, "No existe saludos jasjajsa.");
	SetInteriorCasa(playerid, -1, interior);
	return 1;
}

cmd:editarinterior(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new casa, interior, gformat[195];
	if (sscanf(params, "dd", casa, interior)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /editarinterior (CasaID) (InteriorID)");
    if (casa < 1 || casa > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
	if (InfoCasa[casa][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
	if (IsValidInterior(interior) == 0) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Sólo hay interiores ID desde 1-14, 31-51. Si quieres saber las ID usa: /VerInterior");
	if (interior == 5) return SendPlayerChatMessage(playerid, -1, "No existe saludos jasjajsa.");
	SetInteriorCasa(-1, casa, interior);
	LabelPickup_casa(casa);
	format(gformat, sizeof gformat, "Ahora la casa ID: %d, tiene le interior ID: %d - Clase: %s.", casa, interior, GetClaseCasa(InfoCasa[casa][cTipo]));
	SendPlayerChatMessage(playerid, 0x00cc00ff, gformat);
	return 1;
}

cmd:editarh(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new string[512], id, valor;
	if (sscanf(params, "s[32]", params))
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa (Opción) (CasaID) (Monto)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: exterior, interior, clase (1-4), precio");
		return 1;
	}
	if (!strcmp(params, "clase", true, 5))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa clase (CasaID) (Clase)");
		if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
		if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		if (valor < 1 || valor > 6) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Sólo hay 4 clases (1 baja, 2 media-baja, 3 media, 4 media-alta, 5 alta, 6 custom)");
		InfoCasa[id][cTipo] = valor;
		format(string, sizeof string, "Cambiaste la clase de la casa %d a clase: %s.", id, GetClaseCasa(InfoCasa[id][cTipo]));
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("casas", "Tipo", InfoCasa[id][cID_sql], InfoCasa[id][cTipo]);
	}
	else if (!strcmp(params, "interior", true, 8))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa interior (CasaID)");
		if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
		if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		GetPlayerPos(playerid, InfoCasa[id][cInteriorX], InfoCasa[id][cInteriorY], InfoCasa[id][cInteriorZ]);
		GetPlayerFacingAngle(playerid, InfoCasa[id][cInteriorR]);
		InfoCasa[id][cInteriorInt] = GetPlayerInterior(playerid);
		InfoCasa[id][cInteriorVW] = 400+id;
		format(string, sizeof string, "Cambiaste el interior de la casa %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		new query[1048];
		mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Interior_X = '%f', Interior_Y = '%f', Interior_Z = '%f', Interior_R = '%f', Interior_Int = '%d', Interior_VW = '%d' WHERE ID = '%d'", InfoCasa[id][cInteriorX], InfoCasa[id][cInteriorY], InfoCasa[id][cInteriorZ], InfoCasa[id][cInteriorR], InfoCasa[id][cInteriorInt], InfoCasa[id][cInteriorVW], InfoCasa[id][cID_sql]);
		mysql_tquery(db_samp, query);
		LabelPickup_casa(id);
	}
	else if (!strcmp(params, "exterior", true, 8))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa exterior (CasaID)");
		if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
		if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		GetPlayerPos(playerid, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoCasa[id][cExteriorR]);
		InfoCasa[id][cExteriorInt] = GetPlayerInterior(playerid);
		InfoCasa[id][cExteriorVW] = GetPlayerVirtualWorld(playerid);
		format(string, sizeof string, "Cambiaste el exterior de la casa %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		new query[1048];
		mysql_format(db_samp, query, sizeof query, "UPDATE casas SET Exterior_X = '%f', Exterior_Y = '%f', Exterior_Z = '%f', Exterior_R = '%f', Exterior_Int = '%d', Exterior_VW = '%d' WHERE ID = '%d'", InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ], InfoCasa[id][cExteriorR], InfoCasa[id][cExteriorInt], InfoCasa[id][cExteriorVW], InfoCasa[id][cID_sql]);
		mysql_tquery(db_samp, query);
		LabelPickup_casa(id);
	}
	else if (!strcmp(params, "precio", true, 6))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa precio (CasaID) (monto)");
		if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
		if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		InfoCasa[id][cPrecio] = valor;
		format(string, sizeof string, "Cambiaste el precio a $%s de la casa %d.", diner_coma(valor), id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("casas", "Precio", InfoCasa[id][cID_sql], InfoCasa[id][cPrecio]);
		LabelPickup_casa(id);
	}
	else if (!strcmp(params, "premium", true, 7))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarcasa premium (CasaID)");
		if (id < 1 || id > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
		if (InfoCasa[id][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		if (InfoCasa[id][cPremium] == 0)
		{
		    InfoCasa[id][cPremium] = 1;
			format(string, sizeof string, "Ahora la casa %d es premium.", id);
		}
		else
		{
		    InfoCasa[id][cPremium] = 0;
			new k = gettime();
			k += 1296000;
			InfoCasa[id][cTiempoDisponible] = k;
			format(string, sizeof string, "Ahora la casa %d no es más premium.", id);
			guardar_int_mysql("casas", "TiempoDisponible", InfoCasa[id][cID_sql], InfoCasa[id][cTiempoDisponible]);
		}
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("casas", "Premium", InfoCasa[id][cID_sql], InfoCasa[id][cPremium]);
		LabelPickup_casa(id);
	}
	return 1;
}
alias:editarh("editarc", "editarcasa");

cmd:avecasa(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], house;
	if (sscanf(params, "d", house)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /avecasa (CasaID)");
    if (house < 1 || house > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
	if (InfoCasa[house][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
	if (InfoCasa[house][cVenta] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa ya está en venta.");

	foreach(Player, p) if (IsPlayerConnectedEx(p) && LlavesCasa(p, house))
	{
		format(string, sizeof string, "Admin %s vendió tu casa %d.", NombreOriginal(playerid), house);
		SendPlayerChatMessage(p, COLOR_ORANGE, string);
	}
	//mensaje
	format(string, sizeof string, "Admin %s vendió la casa %d (propietario %s).", NombreDeCuenta(playerid), house, InfoCasa[house][cPropietario]);
	Log("f_logs/house.log", string);
	ClearPropiedad(house);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	format(string, sizeof string, "~w~Vendiste la casa %d.", house);
	GameTextForPlayer(playerid, string, 6000, 3);
	return 1;
}

cmd:ircasa(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new house;
	if (sscanf(params, "d", house)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /ircasa (CasaID)");
	if (house < 1 || house > totalcasas) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Casa no encontrada.");
	if (InfoCasa[house][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
	SetPosEx(playerid, InfoCasa[house][cExteriorX], InfoCasa[house][cExteriorY], InfoCasa[house][cExteriorZ], InfoCasa[house][cExteriorR], InfoCasa[house][cExteriorInt], InfoCasa[house][cExteriorVW], 1);
	GameTextForPlayer(playerid, "~w~Teletransportado", 5000, 1);
	return 1;
}