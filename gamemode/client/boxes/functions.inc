crear_caja(playerid)
{
	Loop(id, MAX_CAJAS, 1) if (InfoCaja[id][cjActivo] == 0)
	{
	    InfoCaja[id][cjActivo] = 1;
		new query[128];
		mysql_format(db_samp, query, sizeof query, "INSERT INTO cajas (Activo) VALUES ('%d')", InfoCaja[id][cjActivo]);
		mysql_tquery(db_samp, query, "CreatePlayerCaja", "ii", playerid, id);
		id = MAX_CAJAS;
	}
	return 1;
}

VerCaja(playerid, id)
{
	ActualizarManos(playerid);
	new dialog[1024], string[128], string2[50];
	Loop(e, 10, 0)
	{
		new Bol = InfoCaja[id][cjObjeto][e];
		if (Bol == 0) format(string, sizeof string, "{CCCCCC}%d: vacío\n", e+1);
		else format(string, sizeof string, "{F5DEB3}%d{EBEBEB}: %s\n", e+1, slot_objeto(Bol, InfoCaja[id][cjObjetoCant][e]));
		strcat(dialog, string);
	}
	format(string, sizeof string, "{D1C231}—————\n");
	strcat(dialog, string);
	if (InfoPersonaje[playerid][pManoIzquierda] == 0) format(string, sizeof string, "{CCCCCC}Mano izquierda: vacío\n");
	else format(string, sizeof string, "{F5DEB3}Mano izquierda:{EBEBEB}: %s", slot_objeto(InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant]));
	strcat(dialog, string);
	format(string2, sizeof string2, "Caja {088A4B}%d", id);
	Dialog_Show(playerid, ShowCaja, DIALOG_STYLE_LIST, string2, dialog, "Continuar", "Salir");
	return 1;
}

Dialog:ShowCaja(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (InfoPersonaje[playerid][pManoDerecha] != 55) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ninguna caja en tu mano derecha.");
	new id = InfoPersonaje[playerid][pManoDerechaCant];
	switch (listitem)
	{
		case 0..9: SacarCaja(playerid, listitem, id);
		case 10: return 1;
		case 11: GuardarCaja(playerid, id);
	}
	return 1;
}

SacarCaja(playerid, x, id)
{
	new cajaobj = InfoCaja[id][cjObjeto][x], Cant = InfoCaja[id][cjObjetoCant][x], query[256];
	if (cajaobj == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El slot seleccionado se encuentra vacío.");
	if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano izquierda vacía.");
	InfoPersonaje[playerid][pManoIzquierda] = cajaobj;
	InfoPersonaje[playerid][pManoIzquierdaCant] = Cant;
	PonerObjeto(playerid, 2, cajaobj);
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	InfoCaja[id][cjObjeto][x] = 0;
	InfoCaja[id][cjObjetoCant][x] = 0;
	mysql_format(db_samp, query, sizeof query, "UPDATE cajas SET Obj%d = 0, ObjCant%d = 0 WHERE ID = '%d'", x+1, x+1, id);
	mysql_tquery(db_samp, query);
	SendClientMessageEx(playerid, 0x828BFDFF, "Sacaste %s de la caja.", InfoInventario[cajaobj][NombreObjeto]);
	return 1;
}

GuardarCaja(playerid, id)
{
	if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener algo en tu mano izquierda.");
	new Mano = InfoPersonaje[playerid][pManoIzquierda], Cant = InfoPersonaje[playerid][pManoIzquierdaCant], query[256];
	Loop(e, 10, 0) if (InfoCaja[id][cjObjeto][e] == 0)
	{
		InfoCaja[id][cjObjeto][e] = Mano;
		InfoCaja[id][cjObjetoCant][e] = Cant;
		mysql_format(db_samp, query, sizeof query, "UPDATE cajas SET Obj%d = '%d', ObjCant%d = '%d' WHERE ID = '%d'", e+1, Mano, e+1, Cant, id);
		mysql_tquery(db_samp, query);
		RemovePlayerAttachedObject(playerid, 8);
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		SendClientMessageEx(playerid, 0x828BFDFF, "Guardaste %s en la caja.", InfoInventario[Mano][NombreObjeto]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes guardar más nada en la caja.");
	return 1;
}
