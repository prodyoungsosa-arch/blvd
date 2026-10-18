Dialog:ShowGPS(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: //vehículos
		{
		    pc_cmd_llaves(playerid);
		}
		case 1:
		{
			new stringo[2048], totalstring[2048], iCount = 0;
			strcat(totalstring, "Ubicación\t\tDistancia\n");
			Loop(id, sizeof InfoGPS, 0) if (InfoGPS[id][uPosicion][0] != 0.0)
			{
			    new Float:Distancia = GetPlayerDistanceFromPoint(playerid,InfoGPS[id][uPosicion][0], InfoGPS[id][uPosicion][1], InfoGPS[id][uPosicion][2]);
				format(stringo, sizeof stringo, "%s\t\t%0.2f M\n", InfoGPS[id][uNombre],Distancia);
				strcat(totalstring, stringo);
				//conteo
				new gformat2[64];
				format(gformat2, sizeof gformat2, "ubicgps%d", iCount);
				SetPVarInt(playerid, gformat2, id);
				iCount++;
			}
			Dialog_Show(playerid, ShowUbicaciones, DIALOG_STYLE_TABLIST_HEADERS, "{EBEBEB}GPS - {088A4B}Ubicaciones", totalstring, "Localizar", "Atrás");

		}
	}
	return 1;
}

Dialog:ShowUbicaciones(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_gps(playerid);
	new xdxd = listitem, gformat[40], gstring[250];
	format(gformat, sizeof gformat, "ubicgps%d", xdxd);
	new id = GetPVarInt(playerid, gformat);
	SetPlayerCheckpoint(playerid, InfoGPS[id][uPosicion][0], InfoGPS[id][uPosicion][1], InfoGPS[id][uPosicion][2], 2.0);
	PlayerPlaySound(playerid, 1138, 0, 0, 0);
	format(gstring, sizeof gstring, "Se marcó en el mapa la ubicación del {088A4B}%s", InfoGPS[id][uNombre]);
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, gstring);
	return 1;
}
