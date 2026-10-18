forward UsandoSpray(playerid);
public UsandoSpray(playerid)
{
	//check
	new sprayCounter = GetPVarInt(playerid, "LetraGraffiti"), id = GetPVarInt(playerid, "GraffitiID"), counter[60], graffitiText[128];
	GetPVarString(playerid, "TextoGraffiti", graffitiText, sizeof graffitiText);
	if (isnull(graffitiText)) return SendPlayerChatMessage(playerid, 0xEBEBEBFF, "No tienes nada asignado a rociar, usa /graffiti.");
	//spray
	if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoGraffiti[id][gr_PosX], InfoGraffiti[id][gr_PosY], InfoGraffiti[id][gr_PosZ]))
	{
		sprayCounter--;
		SetPVarInt(playerid, "LetraGraffiti", sprayCounter);
		format(counter, sizeof counter, "~p~Pintando~n~~w~&~g~%d]", sprayCounter);
		GameTextForPlayer(playerid, counter, 3000, 3);
		if (sprayCounter <= 0)
		{
			alm(InfoGraffiti[id][gr_Mensaje], graffitiText);
			strreplace(graffitiText, "(n)", "\n");
			strreplace(graffitiText, "(a)", "{0000FF}"); //azul
			strreplace(graffitiText, "(b)", "{FFFFFF}"); //blanco
			strreplace(graffitiText, "(am)", "{FFFF00}"); //amarillo
			strreplace(graffitiText, "(v)", "{00C200}"); //verde
			strreplace(graffitiText, "(ne)", "{000000}"); //negro
			strreplace(graffitiText, "(na)", "{FFBF00}"); //naranja
			strreplace(graffitiText, "(r)", "{FF0000}"); //rojo
			strreplace(graffitiText, "(ce)", "{00FFFF}"); //celeste
			SetDynamicObjectMaterialText(InfoGraffiti[id][gr_Objeto], 0, graffitiText, OBJECT_MATERIAL_SIZE_256x256, "Arial", 32, 1, 0xFFFFFFFF, 0, 1);
			GameTextForPlayer(playerid, "~g~Terminado", 3500, 3);
			alm(InfoGraffiti[id][gr_Creador], NombreDeCuenta(playerid));
			InfoGraffiti[id][gr_Fecha] = gettime();
			SetPVarInt(playerid, "LetraGraffiti", GetPVarInt(playerid, "SetraGraffiti"));
			DeletePVar(playerid, "GraffitiID");
			DeletePVar(playerid, "ModoSpray");
			KillTimer(playerGraffitiTimer[playerid]);
			new query[512];
			mysql_format(db_samp, query, sizeof query, "UPDATE graffitis SET Mensaje = '%e', Creador = '%e', Fecha = '%d' WHERE ID = '%d'", InfoGraffiti[id][gr_Mensaje], InfoGraffiti[id][gr_Creador], InfoGraffiti[id][gr_Fecha], InfoGraffiti[id][grID_sql]);
			mysql_tquery(db_samp, query);
		}
	}
	else
	{
		SetPVarInt(playerid, "LetraGraffiti", GetPVarInt(playerid, "SetraGraffiti"));
		DeletePVar(playerid, "GraffitiID");
		DeletePVar(playerid, "ModoSpray");
		KillTimer(playerGraffitiTimer[playerid]);
		GameTextForPlayer(playerid, "~n~~w~Pintura ~r~cancelada", 3000, 5);
	}
	return 1;
}

forward OnGraffitiCreate(id);
public OnGraffitiCreate(id)
{
	InfoGraffiti[id][grID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
