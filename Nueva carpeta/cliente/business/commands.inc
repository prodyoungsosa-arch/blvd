//Jugadores
cmd:comprarnegocio(playerid)
{
	if (InfoPersonaje[playerid][pComprarNegocio] != 0) return SendClientMessageEx(playerid, COLOR_GREY, "* No puedes comprar un negocio hasta dentro de %d minutos.", InfoPersonaje[playerid][pComprarNegocio]);
	new id = GetExtNegocio(playerid), string[512];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el exterior de ningún negocio.");
	if (InfoNegocio[id][nVenta] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes comprar un negocio con dueño.");
	if (GetPlayerCash(playerid) < InfoNegocio[id][nPrecio])
	{
		format(string, sizeof string, "No tienes dinero suficiente! Te faltan {00cc00}$%s", diner_coma(InfoNegocio[id][nPrecio]-GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_GRAD2, string);
		return 1;
	}
	if (CountNegocios(playerid) >= InfoCuenta[playerid][jMaxNegocios]) return SendClientMessageEx(playerid, COLOR_GREY, "* No puedes tener más de %d negocios.", InfoCuenta[playerid][jMaxNegocios]);
	GivePlayerCash(playerid, -InfoNegocio[id][nPrecio], "compra de negocio");
	Tax += InfoNegocio[id][nPrecio];
	alm(InfoNegocio[id][nPropietario], NombreDeCuenta(playerid));
	InfoNegocio[id][nVenta] = 1;
	new k = gettime();
	k += 1296000;
	InfoNegocio[id][nTiempoDisponible] = k;
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicitaciones por tu nueva compra!");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Escribe {3E62F4}/ayuda negocio{FFFFFF} para ver los comandos disponibles!");
	mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET Propietario = '%e', Venta = 1, TiempoDisponible = '%d' WHERE ID = '%d'", InfoNegocio[id][nPropietario], InfoNegocio[id][nTiempoDisponible], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, string);
	if (InfoNegocio[id][nTipo] == 9) SendPlayerChatMessage(playerid, 0x5EAEFFFF, "Puedes cambiar el precio de los servicios desde /cambiarprecios.");
	LabelPickup_negocio(id, 1, 0, 0, 0);
	return 1;
}

cmd:vendernegocio(playerid)
{
	new id = GetExtNegocio(playerid), string[250];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el exterior de ningún negocio.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este negocio no te pertenece.");
	new money = InfoNegocio[id][nPrecio]+InfoNegocio[id][nDinero];
	format(string, sizeof string, "Vendiste tu negocio. Recuperaste {00CC00}$%s{FFFFFF} del negocio más {00CC00}$%s{FFFFFF} de ganancias.", diner_coma(InfoNegocio[id][nPrecio]), diner_coma(InfoNegocio[id][nDinero]));
	SendPlayerChatMessage(playerid, -1, string);
 	GivePlayerCash(playerid, money, "venta de negocio");
	InfoNegocio[id][nDinero] = 0;
	InfoNegocio[id][nVenta] = 0;
	InfoNegocio[id][nTiempoDisponible] = -1;
	alm(InfoNegocio[id][nPropietario], "gobielno");
	mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET Propietario = '%e', BolosUwU = 0, TiempoDisponible = 0 WHERE ID = '%d'", InfoNegocio[id][nPropietario], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, string);
	LabelPickup_negocio(id, 1, 0, 0, 0);
	alm(InfoNegocio[id][nCompartida1], "none");
	alm(InfoNegocio[id][nCompartida2], "none");
	alm(InfoNegocio[id][nCompartida3], "none");
	mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoNegocio[id][nCompartida1], InfoNegocio[id][nCompartida2], InfoNegocio[id][nCompartida3], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, string);
	InfoPersonaje[playerid][pComprarNegocio] = 600;
	guardar_int_mysql("personajes", "ComprarNegocio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pComprarNegocio]);
	return 1;
}

cmd:nseguro(playerid)
{
	new id = 0;
	if (GetExtNegocio(playerid) != -1) id = GetExtNegocio(playerid);
	if (GetIntNegocio(playerid) != -1) id = GetIntNegocio(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en la entrada/salida de ningún negocio.");
	if (PermisosNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	if (InfoNegocio[id][nSeguro] != 0)
	{
		if (InfoNegocio[id][EnLlamas] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes abrir el negocio si está en llamas.");
		rol_ame(playerid, "saca su llave de negocio y lo abre.");
		InfoNegocio[id][nSeguro] = 0;
	}
	else
	{
		rol_ame(playerid, "saca su llave de negocio y lo cierra.");
		InfoNegocio[id][nSeguro] = 1;
	}
	Labelupdate_negocio(id);
	guardar_int_mysql("negocios", "Seguro", InfoNegocio[id][nID_sql], InfoNegocio[id][nSeguro]);
	TallerOpened(id, InfoNegocio[id][nSeguro]);
	return 1;
}
alias:nseguro("negocioseguro");

cmd:negociomenu(playerid)
{
	new id = EnNegocio(playerid), gformat[520];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	switch (InfoNegocio[id][nTipo])
	{
		case 9: format(gformat, sizeof gformat, "{0080C0}%s\n{EBEBEB}Dinero en caja: {00CC00}$%s\n{EBEBEB}Taller: %s\n{EBEBEB}Productos: {8E4BE9}%d\n{EBEBEB}Permisos de negocio", InfoNegocio[id][nNombre], diner_coma(InfoNegocio[id][nDinero]), (InfoNegocio[id][nSeguro]) ? ("{F92B2B}Cerrada") : ("{55AD30}Abierta"), InfoNegocio[id][nProductos]);
		default: format(gformat, sizeof gformat, "{0080C0}%s\n{EBEBEB}Dinero en caja: {00CC00}$%s\n{EBEBEB}Puerta: %s\n{EBEBEB}Productos: {8E4BE9}%d\n{EBEBEB}Permisos de negocio", InfoNegocio[id][nNombre], diner_coma(InfoNegocio[id][nDinero]), (InfoNegocio[id][nSeguro]) ? ("{F92B2B}Cerrada") : ("{55AD30}Abierta"), InfoNegocio[id][nProductos]);
	}
	Dialog_Show(playerid, NegocioOpciones, DIALOG_STYLE_LIST, "Menú de negocio", gformat, "Continuar", "Salir");
	return 1;
}
alias:negociomenu("negocio", "menunegocio");

//Administrativos
cmd:irnegocio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id, gformat[170];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /irnegocio (NegocioID)");
	if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
	if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	SetPosEx(playerid, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorR], InfoNegocio[id][nExteriorInt], InfoNegocio[id][nExteriorVW], 1);
	format(gformat, sizeof gformat, "Te has movido al negocio {3E62F4}%s{FFFFFF} ID %d.", InfoNegocio[id][nNombre], id);
	SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
	return 1;
}

cmd:avenegocio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, gformat[512];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /avenegocio (NegocioID)");
	if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
	if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	if (InfoNegocio[id][nVenta] == 0) return SendPlayerChatMessage(playerid, -1, "Ese negocio ya está en venta.");
	foreach(Player, p) if (IsPlayerConnectedEx(p) && LlavesNegocio(p, id))
	{
		format(gformat, sizeof gformat, "Admin %s vendió tu negocio id: %d", NombreOriginal(playerid), id);
		SendPlayerChatMessage(p, COLOR_ORANGE, gformat);
	}
	format(gformat, sizeof gformat, "%s vendió el negocio %d (propietario %s).", InfoCuenta[playerid][jNombre], id, InfoNegocio[id][nPropietario]);
	Log("f_logs/negocios.log", gformat);
	alm(InfoNegocio[id][nPropietario], "gobielno");
	InfoNegocio[id][nSeguro] = 0;
	InfoNegocio[id][nTiempoDisponible] = -1;
	InfoNegocio[id][nVenta] = 0;
	LabelPickup_negocio(id, 1, 0, 0, 0);
	TallerOpened(id, InfoNegocio[id][nSeguro]);
	format(gformat, sizeof gformat, "Vendiste el negocio %d (%s), las ganancias se conservan.", id, InfoNegocio[id][nNombre]);
	SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE negocios SET Propietario = '%e', Seguro = 0, Venta = 0, TiempoDisponible = -1 WHERE ID = '%d'", InfoNegocio[id][nPropietario], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, gformat);
	alm(InfoNegocio[id][nCompartida1], "none");
	alm(InfoNegocio[id][nCompartida2], "none");
	alm(InfoNegocio[id][nCompartida3], "none");
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE negocios SET Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoNegocio[id][nCompartida1], InfoNegocio[id][nCompartida2], InfoNegocio[id][nCompartida3], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, gformat);
	return 1;
}

cmd:editarnegocio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new string[860], id, valor;
	if (sscanf(params, "s[32]", params))
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio (Opción) (NegocioID) (Monto)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: exterior, interior, ganancias, precio, productos");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: comprar, mapicon, skinactor, posactor, posvehiculo");
		return 1;
	}
	if (!strcmp(params, "exterior", true, 8))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio exterior (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		GetPlayerPos(playerid, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoNegocio[id][nExteriorR]);
		InfoNegocio[id][nExteriorInt] = GetPlayerInterior(playerid);
		InfoNegocio[id][nExteriorVW] = GetPlayerVirtualWorld(playerid);
		mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET ExteriorX = '%f', ExteriorY = '%f', ExteriorZ = '%f', ExteriorR = '%f', ExteriorInt = '%d', ExteriorVW = '%d' WHERE ID = '%d'", InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorR], InfoNegocio[id][nExteriorInt], InfoNegocio[id][nExteriorVW], InfoNegocio[id][nID_sql]);
		mysql_tquery(db_samp, string);
		LabelPickup_negocio(id, 1, 1, 0, 0);
		format(string, sizeof string, "Cambiaste el exterior del negocio %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	else if (!strcmp(params, "interior", true, 8))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio interior (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		GetPlayerPos(playerid, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ]);
		GetPlayerFacingAngle(playerid, InfoNegocio[id][nInteriorR]);
		InfoNegocio[id][nInteriorInt] = GetPlayerInterior(playerid);
		InfoNegocio[id][nInteriorVW] = 100+id;
		mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET InteriorX = '%f', InteriorY = '%f', InteriorZ = '%f', InteriorR = '%f', InteriorInt = '%d', InteriorVW = '%d' WHERE ID = '%d'", InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ], InfoNegocio[id][nInteriorR], InfoNegocio[id][nInteriorInt], InfoNegocio[id][nInteriorVW], InfoNegocio[id][nID_sql]);
		mysql_tquery(db_samp, string);
		LabelPickup_negocio(id, 1, 0, 0, 0);
		format(string, sizeof string, "Cambiaste el interior del negocio %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	else if (!strcmp(params, "skinactor", true, 9))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio skinactor (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		actore_skin[playerid] = id;
		new SkinMuestra[200], count = 0;
		Loop(x, sizeof InfoSkin, 0) if (InfoSkin[x][sTipo] == 1)
		{
			SkinMuestra[count] = x;
			count++;
		}
		ShowModelSelectionMenuEx(playerid, SkinMuestra, count, "Skin para el actor", Actor_Skin, -11.0, 0.0, -55.0, 1.0);
	}
	else if (!strcmp(params, "posactor", true, 8))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio posactor (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		if (InfoNegocio[id][nActorSkin] == 0) return SendPlayerChatMessage(playerid, -1, "Aún no colocas un skin al actor.");
		GetPlayerPos(playerid, InfoNegocio[id][nActorX], InfoNegocio[id][nActorY], InfoNegocio[id][nActorZ]);
		GetPlayerFacingAngle(playerid, InfoNegocio[id][nActorR]);
		mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET ActorX = '%f', ActorY = '%f', ActorZ = '%f', ActorR = '%f' WHERE ID = '%d'", InfoNegocio[id][nActorX], InfoNegocio[id][nActorY], InfoNegocio[id][nActorZ], InfoNegocio[id][nActorR], InfoNegocio[id][nID_sql]);
		mysql_tquery(db_samp, string);
		LabelPickup_negocio(id, 0, 0, 1, 0);
		format(string, sizeof string, "Cambiaste el lugar del actor del negocio %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	else if (!strcmp(params, "comprar", true, 7))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio comprar (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		GetPlayerPos(playerid, InfoNegocio[id][nLugarCompraX], InfoNegocio[id][nLugarCompraY], InfoNegocio[id][nLugarCompraZ]);
		mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET LugarCompraX = '%f', LugarCompraY = '%f', LugarCompraZ = '%f' WHERE ID = '%d'", InfoNegocio[id][nLugarCompraX], InfoNegocio[id][nLugarCompraY], InfoNegocio[id][nLugarCompraZ], InfoNegocio[id][nID_sql]);
		mysql_tquery(db_samp, string);
		LabelPickup_negocio(id, 0, 0, 0, 1);
		format(string, sizeof string, "Cambiaste el lugar de /comprar del negocio %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	else if (!strcmp(params, "precio", true, 6))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio precio (NegocioID) ($)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoNegocio[id][nPrecio] = valor;
		format(string, sizeof string, "Cambiaste el precio ($%s) del negocio %d.", diner_coma(valor), id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("negocios", "Precio", InfoNegocio[id][nID_sql], InfoNegocio[id][nPrecio]);
		Labelupdate_negocio(id);
	}
	else if (!strcmp(params, "ganancias", true, 9))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio ganancias (NegocioID) ($)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoNegocio[id][nDinero] = valor;
		format(string, sizeof string, "Cambiaste las ganacias ($%s) del negocio %d.", diner_coma(valor), id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
	}
	else if (!strcmp(params, "productos", true, 9))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio productos (NegocioID) (Cantidad)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoNegocio[id][nProductos] = valor;
		format(string, sizeof string, "Cambiaste los productos (%d) del negocio %d.", valor, id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("negocios", "Productos", InfoNegocio[id][nID_sql], InfoNegocio[id][nProductos]);
	}
	else if (!strcmp(params, "mapicon", true, 7))
	{
		if (sscanf(params, "s[32]ii", params, id, valor)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio mapicon (NegocioID) (ModelID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		InfoNegocio[id][nMapIcon] = valor;
		format(string, sizeof string, "Cambiaste el mapicon (%d) del negocio %d.", valor, id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		guardar_int_mysql("negocios", "MapIcon", InfoNegocio[id][nID_sql], InfoNegocio[id][nMapIcon]);
		LabelPickup_negocio(id, 0, 1, 0, 0);
	}
	else if (!strcmp(params, "posvehiculo", true, 11))
	{
		if (sscanf(params, "s[32]i", params, id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnegocio posvehiculo (NegocioID)");
		if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		if (InfoNegocio[id][nTipo] != 10) return SendPlayerChatMessage(playerid, -1, "Ese negocio no es tipo concesionario.");
		if (InfoPersonaje[playerid][pInterior] != 0 && InfoPersonaje[playerid][pVirtualWorld] != 0) return SendPlayerChatMessage(playerid, -1, "No puedes editar el spawn del vehiculo comprado en interiores.");
		GetPlayerPos(playerid, InfoNegocio[id][nVehicleX], InfoNegocio[id][nVehicleY], InfoNegocio[id][nVehicleZ]);
		GetPlayerFacingAngle(playerid, InfoNegocio[id][nVehicleR]);
		mysql_format(db_samp, string, sizeof string, "UPDATE negocios SET VehicleX = '%f', VehicleY = '%f', VehicleZ = '%f', VehicleR = '%f' WHERE ID = '%d'", InfoNegocio[id][nVehicleX], InfoNegocio[id][nVehicleY], InfoNegocio[id][nVehicleZ], InfoNegocio[id][nVehicleR], InfoNegocio[id][nID_sql]);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "Cambiaste el spawn de compra de vehiculo del negocio %d.", id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	return 1;
}
alias:editarnegocio("editarn");

cmd:crearnegocio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new precio, tipo, gformat[260];
	if (sscanf(params, "dd", tipo, precio))
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utiliza: /crearnegocio (Tipo) (Precio)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Tipos: 1 (24-7 peque�o) 2 (24-7 grande) 3 (binco) 4 (Sub urban) 5 (ZIP) 6 (Victim) 7 (Pro Laps) 8 (Ds) 9 (Cluckin bell)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Tipos: 10 (Pizzería) 11 (Burger shot) 12 (Gasolinera) 13 (Ammunation pequeño) 14 (Ammunation mediano) 15 (Ammunation grande)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Tipos: 16 (Sex shop) 17 (Bar) 18 (Alhambra) 19 (Strip club) 20 (Concesionaria) 21 (BAITSHOP)");
		return 1;
	}
	if (tipo < 1 || tipo > 21) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Los tipos están entre 1 - 20.");
	Loop(id, MAX_NEGOCIOS, 1) if (InfoNegocio[id][nTipo] == 0)
	{
		GetPlayerPos(playerid, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]);
		GetPlayerFacingAngle(playerid, InfoNegocio[id][nExteriorR]);
		InfoNegocio[id][nVenta] = 0;
		InfoNegocio[id][nPrecio] = precio;
		InfoNegocio[id][nExteriorVW] = GetPlayerVirtualWorld(playerid);
		InfoNegocio[id][nExteriorInt] = GetPlayerInterior(playerid);
		Positions_Negocio(id, tipo);
		alm(InfoNegocio[id][nNombre], GetTipoNegocio(InfoNegocio[id][nTipo]));
		LabelPickup_negocio(id, 1, 0, 1, 1);
		InfoNegocio[id][nProductos] = 800;
		InfoNegocio[id][nTiempoDisponible] = -1;
		format(gformat, sizeof gformat, "Negocio nuevo ID: %d - Precio: $%s - Tipo: %s.", id, diner_coma(precio), GetTipoNegocio(InfoNegocio[id][nTipo]));
		SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
		switch (InfoNegocio[id][nTipo])
		{
			case 10: SendPlayerChatMessage(playerid, 0xFFFF00FF, "Recuerda usar /editarn posvehiculo (NegocioID), para editar el lugar de entrega de compra.");
		}
		new que2ry[2000], query[3500];
		//opción idsql ya creada.
		if (InfoNegocio[id][nID_sql] != 0)
		{
			format(que2ry, sizeof que2ry, "UPDATE negocios SET Nombre = '%s', Tipo = '%d', Venta = '%d', Precio = '%d', ExteriorX = '%f', ExteriorY = '%f', ExteriorZ = '%f', ExteriorR = '%f', ExteriorInt = '%d', ExteriorVW = '%d', InteriorX = '%f', InteriorY = '%f', InteriorZ = '%f', InteriorR = '%f', InteriorInt = '%d', InteriorVW = '%d',",
			InfoNegocio[id][nNombre],
			InfoNegocio[id][nTipo],
			InfoNegocio[id][nVenta],
			InfoNegocio[id][nPrecio],
			InfoNegocio[id][nExteriorX],
			InfoNegocio[id][nExteriorY],
			InfoNegocio[id][nExteriorZ],
			InfoNegocio[id][nExteriorR],
			InfoNegocio[id][nExteriorInt],
			InfoNegocio[id][nExteriorVW],
			InfoNegocio[id][nInteriorX],
			InfoNegocio[id][nInteriorY],
			InfoNegocio[id][nInteriorZ],
			InfoNegocio[id][nInteriorR],
			InfoNegocio[id][nInteriorInt],
			InfoNegocio[id][nInteriorVW]);
			mysql_format(db_samp, query, sizeof query, "%s LugarCompraX = '%f', LugarCompraY = '%f', LugarCompraZ = '%f', Productos = '%d', ActorX = '%f', ActorY = '%f', ActorZ = '%f', ActorR = '%f', ActorSkin = '%d', TiempoDisponible = -1 WHERE ID = '%d'",
			que2ry,
			InfoNegocio[id][nLugarCompraX],
			InfoNegocio[id][nLugarCompraY],
			InfoNegocio[id][nLugarCompraZ],
			InfoNegocio[id][nProductos],
			InfoNegocio[id][nActorX],
			InfoNegocio[id][nActorY],
			InfoNegocio[id][nActorZ],
			InfoNegocio[id][nActorR],
			InfoNegocio[id][nActorSkin],
			InfoNegocio[id][nID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_NEGOCIOS;
			return 1;
		}
		format(que2ry, sizeof que2ry, "INSERT INTO negocios (Nombre, Tipo, Venta, Precio, ExteriorX, ExteriorY, ExteriorZ, ExteriorR, ExteriorInt, ExteriorVW, InteriorX, InteriorY, InteriorZ, InteriorR, InteriorInt, InteriorVW, LugarCompraX, LugarCompraY, LugarCompraZ,");
		mysql_format(db_samp, query, sizeof query, "%s Productos, ActorX, ActorY, ActorZ, ActorR, ActorSkin, TiempoDisponible) VALUES ('%e', '%d', '%d',  '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%f', '%f', '%f', '%d', '%f', '%f', '%f', '%f', '%d', -1)",
		que2ry,
		InfoNegocio[id][nNombre],
		InfoNegocio[id][nTipo],
		InfoNegocio[id][nVenta],
		InfoNegocio[id][nPrecio],
		InfoNegocio[id][nExteriorX],
		InfoNegocio[id][nExteriorY],
		InfoNegocio[id][nExteriorZ],
		InfoNegocio[id][nExteriorR],
		InfoNegocio[id][nExteriorInt],
		InfoNegocio[id][nExteriorVW],
		InfoNegocio[id][nInteriorX],
		InfoNegocio[id][nInteriorY],
		InfoNegocio[id][nInteriorZ],
		InfoNegocio[id][nInteriorR],
		InfoNegocio[id][nInteriorInt],
		InfoNegocio[id][nInteriorVW],
		InfoNegocio[id][nLugarCompraX],
		InfoNegocio[id][nLugarCompraY],
		InfoNegocio[id][nLugarCompraZ],
		InfoNegocio[id][nProductos],
		InfoNegocio[id][nActorX],
		InfoNegocio[id][nActorY],
		InfoNegocio[id][nActorZ],
		InfoNegocio[id][nActorR],
		InfoNegocio[id][nActorSkin]);
		mysql_tquery(db_samp, query, "OnNegocioCreate", "i", id);
		id = MAX_NEGOCIOS;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_RED, "Se alcanzó el máximo de negocios (100)");
	return 1;
}

cmd:borrarnegocio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new id, gformat[235], query[1408];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Utiliza: /borrarnegocio (NegocioID)");
	if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida. (6 en adelante)");
	if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	//si tenía dueño
	foreach(Player, p) if (IsPlayerConnectedEx(p) && LlavesNegocio(p, id))
	{
		format(gformat, sizeof gformat, "Admin %s vendió tu negocio (1) %d.", NombreOriginal(playerid), id);
		SendPlayerChatMessage(playerid, COLOR_ORANGE, gformat);
	}
	BorrarMueblesNegocio(id);
	//destroy pickup+label
	noexitnegocio(id);
	//reset variables
	alm(InfoNegocio[id][nNombre], "none");
	alm(InfoNegocio[id][nPropietario], "gobielno");
	InfoNegocio[id][nVenta] = 0;
	InfoNegocio[id][nTipo] = 0;
	InfoNegocio[id][nPrecio] = 0;
	InfoNegocio[id][nExteriorX] = 0.0;
	InfoNegocio[id][nExteriorY] = 0.0;
	InfoNegocio[id][nExteriorZ] = 0.0;
	InfoNegocio[id][nExteriorR] = 0.0;
	InfoNegocio[id][nExteriorInt] = 0;
	InfoNegocio[id][nExteriorVW] = 0;
	InfoNegocio[id][nInteriorX] = 0.0;
	InfoNegocio[id][nInteriorY] = 0.0;
	InfoNegocio[id][nInteriorZ] = 0.0;
	InfoNegocio[id][nInteriorR] = 0.0;
	InfoNegocio[id][nInteriorInt] = 0;
	InfoNegocio[id][nInteriorVW] = 0;
	InfoNegocio[id][nLugarCompraX] = 0.0;
	InfoNegocio[id][nLugarCompraY] = 0.0;
	InfoNegocio[id][nLugarCompraZ] = 0.0;
	InfoNegocio[id][nSeguro] = 0;
	InfoNegocio[id][nDinero] = 0;
	InfoNegocio[id][nProductos] = 0;
	InfoNegocio[id][nMapIcon] = 0;
	InfoNegocio[id][nActorX] = 0.0;
	InfoNegocio[id][nActorY] = 0.0;
	InfoNegocio[id][nActorZ] = 0.0;
	InfoNegocio[id][nActorR] = 0.0;
	InfoNegocio[id][nActorSkin] = 0;
	InfoNegocio[id][nVehicleX] = 0.0;
	InfoNegocio[id][nVehicleY] = 0.0;
	InfoNegocio[id][nVehicleZ] = 0.0;
	InfoNegocio[id][nVehicleR] = 0.0;
	InfoNegocio[id][nPrecioPintura] = 0;
	InfoNegocio[id][nPrecioPaintJob] = 0;
	InfoNegocio[id][nPrecioReparacion] = 0;
	InfoNegocio[id][nPrecioGasolina] = 0;
	InfoNegocio[id][nPrecioLlantas] = 0;
	InfoNegocio[id][nPrecioNitro] = 0;
	InfoNegocio[id][nPrecioHyd] = 0;
	InfoNegocio[id][nPrecioTuneo] = 0;
	InfoNegocio[id][nTiempoDisponible] = -1;
	ActualizarPrecioNegocio(id);
	alm(InfoNegocio[id][nCompartida1], "none");
	alm(InfoNegocio[id][nCompartida2], "none");
	alm(InfoNegocio[id][nCompartida3], "none");
	mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoNegocio[id][nCompartida1], InfoNegocio[id][nCompartida2], InfoNegocio[id][nCompartida3], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, query);
	//query
	mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET Nombre = '%e', Propietario = '%e', Venta = 0, Tipo = 0, Precio = 0, ExteriorX = 0.0, ExteriorY = 0.0, ExteriorZ = 0.0,  ExteriorR = 0.0, \
	ExteriorInt = 0.0, ExteriorVW = 0.0 WHERE ID = '%d'", InfoNegocio[id][nNombre], InfoNegocio[id][nPropietario], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, query);
	mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET InteriorX = 0.0, InteriorY = 0.0, InteriorZ = 0.0, InteriorR = 0.0, InteriorInt = 0, InteriorVW = 0, LugarCompraX = 0.0, \
	LugarCompraY = 0.0, LugarCompraZ = 0.0, Seguro = 0, BolosUwU = 0, TiempoDisponible = -1, Productos = 0, MapIcon = 0, ActorX = 0.0, ActorY = 0.0, ActorZ = 0.0, ActorR = 0.0, ActorSkin = 0 WHERE ID = '%d'", InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, query);
	//mensaje
	format(gformat, sizeof gformat, "Borraste el negocio ID %d, SQL vacía: %d", id, InfoNegocio[id][nID_sql]);
	SendPlayerChatMessage(playerid, -1, gformat);
	return 1;
}

cmd:negocioname(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new query[256], id, doorname[32];
	if (sscanf(params, "ds[32]", id, doorname)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /editarnombrenegocio (NegocioID) (Nombre)");
	if (id < 1 || id >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
	if (InfoNegocio[id][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
	if (strlen(doorname) > 31 || strlen(doorname) < 0) { SendPlayerChatMessage(playerid, -1, "Sólo puedes escribir menos de 30 carácteres."); return 1; }
	alm(InfoNegocio[id][nNombre], doorname);
	format(query, sizeof query, "Cambiaste el nombre (%s) del negocio %d.", doorname, id);
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
	Labelupdate_negocio(id);
	guardar_string_mysql("negocios", "Nombre", InfoNegocio[id][nID_sql], InfoNegocio[id][nNombre]);
	return 1;
}
alias:negocioname("editarnnombre", "editarnegocionombre", "editarnombrenegocio");
