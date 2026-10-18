enum eUnknownTdInf {
    bool:uEnabled,
    uTimer,
    uCount
};

new Text3D:Unknowns[MAX_PLAYERS][MAX_PLAYERS];
new PlayerText:UnknownTD[MAX_PLAYERS][6];
new Unknown[MAX_PLAYERS];
new UnknownTdInf[MAX_PLAYERS][eUnknownTdInf];
new PlayerText: p_tdInteractuar[MAX_PLAYERS][25];

stock GetPlayerByCodigo(const codigo[])
{
    new limpio[17];
    if (codigo[0] == '#')
    {
        for (new i = 1, j = 0; i < 17 && j < sizeof(limpio) - 1; i++, j++)
        {
            limpio[j] = codigo[i];
        }
        limpio[sizeof(limpio) - 1] = '\0';
    }
    else
    {
        strmid(limpio, codigo, 0, sizeof(limpio) - 1);
    }

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnectedEx(i)) continue;
        if (strcmp(InfoPersonaje[i][pCodigo], limpio, true) == 0)
            return i;
    }

    return -1;
}

GetUnknown(playerid) {
    new str[128];
    format(str, sizeof(str), "%s", InfoPersonaje[playerid][pCodigo]);
    return str;
}

IsUnknownCode(playerid) {
    new str[128];
    GetPlayerName(playerid, str, sizeof(str));
    if(!strcmp(str, InfoPersonaje[playerid][pCodigo])) return true;
    else return false;
}

VerificarCodigo(codigo[])
{
	new query[256];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Codigo = '%e'", codigo);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0) return 1;
	cache_delete(result);
	return 0;
}

CodigoDuplicado(playerid)
{
	new query[256];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Codigo = '%e'", InfoPersonaje[playerid][pCodigo]);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 1) 
	{
		alm(InfoPersonaje[playerid][pCodigo], ""); 
		generar_codigo(playerid);
		cache_delete(result);
		return 1;
	}
	cache_delete(result);
	return 0;
}

funcion generar_codigo(playerid)
{
	if (!isnull(InfoPersonaje[playerid][pCodigo]))
	{ 
		CodigoDuplicado(playerid);
	}
	else //poner
	{
	    new codigo[5];
	    new letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	    for (new i = 0; i < 4; i++)
	    {
	        codigo[i] = letras[random(sizeof(letras) - 1)];
	    }
	    codigo[4] = '\0';
	    if (VerificarCodigo(codigo) != 0) return generar_codigo(playerid);
	    alm(InfoPersonaje[playerid][pCodigo], codigo);
	    guardar_string_mysql("personajes", "Codigo", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pCodigo]);
	}      
    return 1;
}

CodigoPersonaje(playerid)
{
	new nameplayer[128];
    format(nameplayer, sizeof(nameplayer), "#%s", InfoPersonaje[playerid][pCodigo]);
	return nameplayer;
}

AreTheyKnown(const code_one[], const code_two[]) {
    new query[128];
    mysql_format(db_samp, query, sizeof(query), "SELECT * FROM `unknowns` WHERE `code_one` = '%s' AND `code_two` = '%s'", code_one, code_two);
    mysql_query(db_samp, query);
    if(cache_num_rows() > 0) return true;
    return false;
}

stock DesconocidoConnect(playerid)
{
    UnknownTdInf[playerid][uEnabled] = false;
    KillTimer(UnknownTdInf[playerid][uTimer]);
    UnknownTdInf[playerid][uTimer] = -1;
    UnknownTdInf[playerid][uCount] = 0;
    SetPVarInt(playerid, "PressUnknownKey", 0);
    Unknown[playerid] = -1;
    for(new i = 0; i < MAX_PLAYERS; i++) {
        DestroyDynamic3DTextLabel(Unknowns[playerid][i]);
        Unknowns[playerid][i] = Text3D:INVALID_3DTEXT_ID;
    }
    
    UnknownTD[playerid][0] = CreatePlayerTextDraw(playerid, 451.500000, 186.500000, "Preview_Model");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][0], 5);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][0], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][0], 200.500000, 28.000000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][0], 51255039);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][0], 0);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][0], 255);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, UnknownTD[playerid][0], 19827);
    PlayerTextDrawSetPreviewRot(playerid, UnknownTD[playerid][0], 0.000000, 0.000000, 0.000000, 0.640000);
    PlayerTextDrawSetPreviewVehCol(playerid, UnknownTD[playerid][0], 1, 1);

    UnknownTD[playerid][1] = CreatePlayerTextDraw(playerid, 500.000000, 192.000000, "Usa      para interactuar con");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][1], 0.216667, 0.950000);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][1], 607.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][1], -1061109710);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][1], 0);

    UnknownTD[playerid][2] = CreatePlayerTextDraw(playerid, 500.000000, 202.000000, "#FDSM");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][2], 0.220833, 0.900000);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][2], 605.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][2], -1061109710);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][2], 0);

    UnknownTD[playerid][3] = CreatePlayerTextDraw(playerid, 514.000000, 188.000000, "0");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][3], 2);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][3], 0.695833, 1.700000);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][3], 605.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][3], -1061109710);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][3], 0);

    UnknownTD[playerid][4] = CreatePlayerTextDraw(playerid, 522.000000, 196.000000, "_");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][4], 0.600000, 0.250002);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][4], 298.500000, 7.500000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][4], -1);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][4], 0);

    UnknownTD[playerid][5] = CreatePlayerTextDraw(playerid, 519.000000, 192.000000, "H");
    PlayerTextDrawFont(playerid, UnknownTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, UnknownTD[playerid][5], 0.216667, 0.950000);
    PlayerTextDrawTextSize(playerid, UnknownTD[playerid][5], 607.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, UnknownTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, UnknownTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, UnknownTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, UnknownTD[playerid][5], 51255039);
    PlayerTextDrawBackgroundColor(playerid, UnknownTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, UnknownTD[playerid][5], -1061109710);
    PlayerTextDrawUseBox(playerid, UnknownTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, UnknownTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, UnknownTD[playerid][5], 0);

    p_tdInteractuar[playerid][0] = CreatePlayerTextDraw(playerid, 237.000, 188.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][0], 188.000, 104.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][0], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][0], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][0], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][0], 1);

    p_tdInteractuar[playerid][1] = CreatePlayerTextDraw(playerid, 277.000, 186.000, "Interactuando con #BWYX");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][1], 0.219, 1.098);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][1], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][1], 1);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][1], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][1], 1);

    p_tdInteractuar[playerid][2] = CreatePlayerTextDraw(playerid, 242.000, 182.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][2], 178.000, 117.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][2], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][2], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][2], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][2], 1);

    p_tdInteractuar[playerid][3] = CreatePlayerTextDraw(playerid, 235.000, 179.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][3], 15.000, 20.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][3], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][3], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][3], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][3], 1);

    p_tdInteractuar[playerid][4] = CreatePlayerTextDraw(playerid, 413.000, 179.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][4], 14.500, 18.500);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][4], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][4], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][4], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][4], 1);

    p_tdInteractuar[playerid][5] = CreatePlayerTextDraw(playerid, 235.000, 282.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][5], 15.000, 20.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][5], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][5], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][5], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][5], 1);

    p_tdInteractuar[playerid][6] = CreatePlayerTextDraw(playerid, 410.000, 282.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][6], 17.500, 20.500);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][6], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][6], 84020991);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][6], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][6], 1);

    p_tdInteractuar[playerid][7] = CreatePlayerTextDraw(playerid, 240.000, 183.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][7], 16.000, 17.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][7], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][7], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][7], 1);

    p_tdInteractuar[playerid][8] = CreatePlayerTextDraw(playerid, 245.500, 184.500, "?");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][8], 0.310, 1.399);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][8], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][8], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][8], 1);

    p_tdInteractuar[playerid][9] = CreatePlayerTextDraw(playerid, 272.000, 207.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][9], 114.000, 18.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][9], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][9], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][9], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][9], 1);

    p_tdInteractuar[playerid][10] = CreatePlayerTextDraw(playerid, 285.000, 211.000, "enviar solicitud de amistad");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][10], 0.200, 0.999);
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][10], 388.000, 13.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][10], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][10], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, p_tdInteractuar[playerid][10], 1);

    p_tdInteractuar[playerid][11] = CreatePlayerTextDraw(playerid, 272.000, 228.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][11], 114.000, 18.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][11], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][11], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][11], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][11], 1);

    p_tdInteractuar[playerid][12] = CreatePlayerTextDraw(playerid, 307.000, 232.000, "ceder dinero");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][12], 0.200, 0.999);
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][12], 388.000, 11.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][12], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][12], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, p_tdInteractuar[playerid][12], 1);

    p_tdInteractuar[playerid][13] = CreatePlayerTextDraw(playerid, 272.000, 249.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][13], 114.000, 18.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][13], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][13], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][13], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][13], 1);

    p_tdInteractuar[playerid][14] = CreatePlayerTextDraw(playerid, 317.000, 253.000, "saludar");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][14], 0.200, 0.999);
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][14], 385.000, 11.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][14], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][14], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, p_tdInteractuar[playerid][14], 1);

    p_tdInteractuar[playerid][15] = CreatePlayerTextDraw(playerid, 265.000, 274.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][15], 130.000, 20.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][15], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][15], 675259647);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][15], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][15], 1);

    p_tdInteractuar[playerid][16] = CreatePlayerTextDraw(playerid, 252.000, 269.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][16], 27.000, 30.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][16], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][16], 675259647);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][16], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][16], 1);

    p_tdInteractuar[playerid][17] = CreatePlayerTextDraw(playerid, 383.000, 269.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][17], 27.000, 30.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][17], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][17], 675259647);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][17], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][17], 1);

    p_tdInteractuar[playerid][18] = CreatePlayerTextDraw(playerid, 320.000, 279.000, "cerrar");
    PlayerTextDrawLetterSize(playerid, p_tdInteractuar[playerid][18], 0.200, 0.999);
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][18], 402.000, 13.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][18], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][18], 150);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, p_tdInteractuar[playerid][18], 1);

    p_tdInteractuar[playerid][19] = CreatePlayerTextDraw(playerid, 258.000, 202.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][19], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][19], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][19], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][19], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][19], 1);

    p_tdInteractuar[playerid][20] = CreatePlayerTextDraw(playerid, 373.000, 202.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][20], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][20], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][20], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][20], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][20], 1);

    p_tdInteractuar[playerid][21] = CreatePlayerTextDraw(playerid, 258.000, 223.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][21], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][21], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][21], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][21], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][21], 1);

    p_tdInteractuar[playerid][22] = CreatePlayerTextDraw(playerid, 373.000, 223.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][22], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][22], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][22], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][22], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][22], 1);

    p_tdInteractuar[playerid][23] = CreatePlayerTextDraw(playerid, 258.000, 244.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][23], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][23], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][23], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][23], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][23], 1);

    p_tdInteractuar[playerid][24] = CreatePlayerTextDraw(playerid, 373.000, 244.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, p_tdInteractuar[playerid][24], 27.000, 28.000);
    PlayerTextDrawAlignment(playerid, p_tdInteractuar[playerid][24], 1);
    PlayerTextDrawColor(playerid, p_tdInteractuar[playerid][24], 303311359);
    PlayerTextDrawSetShadow(playerid, p_tdInteractuar[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, p_tdInteractuar[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, p_tdInteractuar[playerid][24], 255);
    PlayerTextDrawFont(playerid, p_tdInteractuar[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, p_tdInteractuar[playerid][24], 1);
    return true;
}

forward UnknownTdHide(playerid);
public UnknownTdHide(playerid) {
    if((UnknownTdInf[playerid][uCount] - 1) <= 0) {
        UnknownTdInf[playerid][uCount] = 0;
        KillTimer(UnknownTdInf[playerid][uTimer]);
        UnknownTdInf[playerid][uTimer] = -1;
    }
    else UnknownTdInf[playerid][uCount]--;
    
    if(UnknownTdInf[playerid][uCount] == 0) {
        if(UnknownTdInf[playerid][uEnabled] == true) {
            PlayerTextDrawHide(playerid, UnknownTD[playerid][0]);
            PlayerTextDrawHide(playerid, UnknownTD[playerid][1]);
            PlayerTextDrawHide(playerid, UnknownTD[playerid][2]);
            PlayerTextDrawHide(playerid, UnknownTD[playerid][3]);
            PlayerTextDrawHide(playerid, UnknownTD[playerid][4]);
            PlayerTextDrawHide(playerid, UnknownTD[playerid][5]);
            UnknownTdInf[playerid][uEnabled] = false;
        }
    }
    return true;
}



Dialog:DialogUnknown(playerid, response, listitem, inputtext[]) {
    if(!response) {
        SendClientMessage(Unknown[playerid], COLOR_WHITE, "{CB3126}[AMIGOS] {ffffff}Han {CB3126}rechazado {ffffff}tu solicitud.");
        Unknown[playerid] = -1;
        SetPVarInt(playerid, "IN_UNK", 0);
    }
    if(Unknown[playerid] != -1) {
        new query[256];
        mysql_format(db_samp, query, sizeof(query), "INSERT INTO `unknowns` (code_one, code_two) VALUES ('%s', '%s'), ('%s', '%s')", InfoPersonaje[playerid][pCodigo], InfoPersonaje[Unknown[playerid]][pCodigo], InfoPersonaje[Unknown[playerid]][pCodigo], InfoPersonaje[playerid][pCodigo]);
        mysql_query(db_samp, query, false);
        SetPVarInt(playerid, "IN_UNK", 0);
        SendClientMessage(Unknown[playerid], COLOR_WHITE, "{1378DE}[AMIGOS] {ffffff}Han {1378DE}aceptado {ffffff}tu solicitud.");
        Unknown[playerid] = -1;
    }
    return true;
}


stock GetRealName(observerid, targetid, buffer[], len)
{
    if (observerid == targetid)
    {
        format(buffer, len, "%s", InfoPersonaje[targetid][pNombre_Apellido]);
    }

    else if (AreTheyKnown(InfoPersonaje[observerid][pCodigo], InfoPersonaje[targetid][pCodigo]))
    {
        format(buffer, len, "%s", InfoPersonaje[targetid][pNombre_Apellido]);
    }

    else if (papilla[observerid] == 1 || papilla[targetid] == 1)
    {
        format(buffer, len, "%s", InfoPersonaje[targetid][pNombre_Apellido]);
    }

    else
    {
        format(buffer, len, "%s", GetUnknown(targetid));
    }
}

stock GetNameFormat(playerid)
{
    new str[128];

    foreach(new i : Player) 
    {
        if(i == playerid) continue;

        if(AreTheyKnown(InfoPersonaje[i][pCodigo], InfoPersonaje[playerid][pCodigo]) || papilla[i] == 1) 
        {
            if(papilla[playerid] == 1)
            {
                format(str, sizeof(str), "{FFFFFF}STAFF");
            }
            else 
            {
                format(str, sizeof(str), "{FFFFFF}%s", InfoPersonaje[playerid][pNombre_Apellido]);
            }
        } 
        else 
        {
           if(papilla[playerid] == 1)
            {
                format(str, sizeof(str), "{FFFFFF}STAFF");
            }
            else 
            {
                format(str, sizeof(str), "{FFFFFF}%s", GetUnknown(playerid));
            }
        }
        
    }
    
    return str; 
}

UnknownUpdate(playerid)
{
    if(IsPlayerConnectedEx(playerid)) {
        if(!isnull(InfoPersonaje[playerid][pCodigo]) && strlen(InfoPersonaje[playerid][pCodigo]) > 0 && !IsUnknownCode(playerid)) {
            new str[2][32];
            split(InfoPersonaje[playerid][pCodigo], str, '#');
            SetPlayerName(playerid, str[1]);
        }
        
        foreach(new i : Player) {
            if(i == playerid) continue;

            new Float:pos[3];
            GetPlayerPos(i, pos[0], pos[1], pos[2]);
            if(IsPlayerInRangeOfPoint(playerid, 8.0, pos[0], pos[1], pos[2])) {
                new str[128];
                if(AreTheyKnown(InfoPersonaje[playerid][pCodigo], InfoPersonaje[i][pCodigo]) || papilla[playerid] == 1) {
                    if(papilla[i] == 1) {
                        format(str, sizeof(str), "{FFFFFF}STAFF");
                    }
                    else if(OnDuty[playerid] == 1) {
                        format(str, sizeof(str), "{FFFFFF}%s", GetNameFormat(i));
                    }
                    else {
                        format(str, sizeof(str), "{FFFFFF}%s", GetNameFormat(i));
                    }
                } else {
                    if(papilla[i] == 1) {
                        format(str, sizeof(str), "{EBEBEB}STAFF");
                    }
                    else if(OnDuty[playerid] == 1) {
                        format(str, sizeof(str), "%s", GetNameFormat(i));
                    }
                    else {
                        format(str, sizeof(str), "{ebebeb}#%s", GetUnknown(i));
                    }
                }

                if(IsValidDynamic3DTextLabel(Unknowns[playerid][i])) {
                    UpdateDynamic3DTextLabelText(Unknowns[playerid][i], -1, str);
                } else {
                    Unknowns[playerid][i] = CreateDynamic3DTextLabel(str, -1, 0.0, 0.0, 0.2, 10.0, .attachedplayer = i, .playerid = playerid);
                }

                if(IsPlayerInRangeOfPoint(playerid, 1.5, pos[0], pos[1], pos[2])) {
                    PlayerTextDrawSetString(playerid, UnknownTD[playerid][2], InfoPersonaje[i][pCodigo]);

                    UnknownTdInf[playerid][uCount] = 2;
                    if(UnknownTdInf[playerid][uEnabled] == false) {
                        UnknownTdInf[playerid][uEnabled] = true;
                        
                        if(UnknownTdInf[playerid][uTimer] != -1) {
                            KillTimer(UnknownTdInf[playerid][uTimer]);
                        }
                        UnknownTdInf[playerid][uTimer] = SetTimerEx("UnknownTdHide", 1000, true, "d", playerid);
                    }
                    
                    if(GetPVarInt(playerid, "PressUnknownKey") == 1) {
                        SetPVarInt(playerid, "USER_INTERACT", i);
                        new targetcode = GetPVarInt(playerid, "USER_INTERACT");

                        new str2[64];
                        format(str2, sizeof(str2), "~w~Interactuando con ~y~%s", GetNameFormat(targetcode));
                        PlayerTextDrawSetString(playerid, p_tdInteractuar[playerid][1], str2);

                        for(new x = 0; x < 25; x++) { PlayerTextDrawShow(playerid, p_tdInteractuar[playerid][x]); }
                        SelectTextDraw(playerid, 0x121429FF);
                        SetPVarInt(playerid, "IN_UNK", 1);
                        return true;
                    }
                }
            } else {
                if(IsValidDynamic3DTextLabel(Unknowns[playerid][i])) {
                    DestroyDynamic3DTextLabel(Unknowns[playerid][i]);
                    Unknowns[playerid][i] = Text3D:INVALID_3DTEXT_ID;
                }
            }
        }
    }
    return 1;
}
