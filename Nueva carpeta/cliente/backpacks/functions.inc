crear_mochila(playerid)
{
    Loop(id, MAX_MOCHILAS, 1) if (InfoMochila[id][mjActivo] == 0)
    {
        InfoMochila[id][mjActivo] = 1;
        new query[128];
        mysql_format(db_samp, query, sizeof query, "INSERT INTO mochilas (Activo) VALUES ('%d')", InfoMochila[id][mjActivo]);
        mysql_tquery(db_samp, query, "CreatePlayerMochila", "ii", playerid, id);
        id = MAX_MOCHILAS;
    }
    return 1;
}

VerMochila(playerid, id)
{
	ActualizarManos(playerid);
	new dialog[1024], string[128], string2[50];
	Loop(e, 10, 0)
	{
		new Bol = InfoMochila[id][mjObjeto][e];
		if (Bol == 0) format(string, sizeof string, "{CCCCCC}%d: vac�o\n", e+1);
		else format(string, sizeof string, "{4f9162}%d{EBEBEB}: %s\n", e+1, slot_objeto(Bol, InfoMochila[id][mjObjetoCant][e]));
		strcat(dialog, string);
	}
	format(string, sizeof string, "{D1C231}�����\n");
	strcat(dialog, string);
	if (InfoPersonaje[playerid][pManoIzquierda] == 0) format(string, sizeof string, "{CCCCCC}Mano izquierda: vac�o\n");
	else format(string, sizeof string, "{4f9162}Mano izquierda:{EBEBEB}: %s", slot_objeto(InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant]));
	strcat(dialog, string);
	format(string2, sizeof string2, "Mochila {088A4B}%d", id);
	Dialog_Show(playerid, ShowMochila, DIALOG_STYLE_LIST, string2, dialog, "Continuar", "Salir");
	return 1;
}

SacarMochila(playerid, x, id)
{
	new mochilaobj = InfoMochila[id][mjObjeto][x], Cant = InfoMochila[id][mjObjetoCant][x], query[256];
	if (mochilaobj == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El slot seleccionado se encuentra vac�o.");
	if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano izquierda vacia.");
	InfoPersonaje[playerid][pManoIzquierda] = mochilaobj;
	InfoPersonaje[playerid][pManoIzquierdaCant] = Cant;
	PonerObjeto(playerid, 2, mochilaobj);
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	InfoMochila[id][mjObjeto][x] = 0;
	InfoMochila[id][mjObjetoCant][x] = 0;
	mysql_format(db_samp, query, sizeof query, "UPDATE mochilas SET Obj%d = 0, ObjCant%d = 0 WHERE ID = '%d'", x+1, x+1, id);
	mysql_tquery(db_samp, query);
	SendClientMessageEx(playerid, 0x828BFDFF, "Sacaste %s de la mochila.", InfoInventario[mochilaobj][NombreObjeto]);
	return 1;
}

GuardarMochila(playerid, id)
{
	if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener algo en tu mano izquierda.");
	new Mano = InfoPersonaje[playerid][pManoIzquierda], Cant = InfoPersonaje[playerid][pManoIzquierdaCant], query[256];
	Loop(e, 10, 0) if (InfoMochila[id][mjObjeto][e] == 0)
	{
		InfoMochila[id][mjObjeto][e] = Mano;
		InfoMochila[id][mjObjetoCant][e] = Cant;
		mysql_format(db_samp, query, sizeof query, "UPDATE mochilas SET Obj%d = '%d', ObjCant%d = '%d' WHERE ID = '%d'", e+1, Mano, e+1, Cant, id);
		mysql_tquery(db_samp, query);
		RemovePlayerAttachedObject(playerid, 8);
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		SendClientMessageEx(playerid, 0x828BFDFF, "Guardaste %s en la mochila.", InfoInventario[Mano][NombreObjeto]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes guardar m�s nada en la mochila.");
	return 1;
}
