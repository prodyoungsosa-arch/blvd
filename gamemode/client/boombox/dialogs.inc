
Dialog:ShowBoombox(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			if (InfoBoombox[playerid][BB_area])
			{
				foreach(Player, i)
				{
					if(IsPlayerInDynamicArea(i, InfoBoombox[playerid][BB_area]))
						StopStream(i);
				}
				DeletePVar(playerid, "BBStation");
			}
			SendPlayerChatMessage(playerid, COLOR_RED, "Apagaste tu equipo sonido.");
		}
		case 1:
		{
			new StationsDialog[1560];
			strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electrónica{EBEBEB})");
			Dialog_Show(playerid, EmisorasBoombox, DIALOG_STYLE_LIST, "Radios", StationsDialog, "Continuar", "Volver");
		}
		case 2: Dialog_Show(playerid, UrlBoombox, DIALOG_STYLE_INPUT, "URL internet", "{EBEBEB}Inserta un Stream ({b42d2d}www.offliberty.com{EBEBEB}) para reproducirlo", "Continuar", "Volver");
		case 3:
		{
			if (!IsPlayerInRangeOfPoint(playerid, 4.0, InfoBoombox[playerid][BB_x], InfoBoombox[playerid][BB_y], InfoBoombox[playerid][BB_z])) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca de tu boombox.");
			if (DarObjeto(playerid, 51, 1) == 2) return 1;
			foreach(Player, i) if (IsPlayerInDynamicArea(i, InfoBoombox[playerid][BB_area]))
			{
				StopStream(i);
			}
			InfoBoombox[playerid][BB_area] = 0;
			if (IsValidDynamicObject(InfoBoombox[playerid][BB_obj])) DestroyDynamicObject(InfoBoombox[playerid][BB_obj]);
			if (IsValidDynamic3DTextLabel(InfoBoombox[playerid][BB_label]))
			{
				DestroyDynamic3DTextLabel(InfoBoombox[playerid][BB_label]);
				InfoBoombox[playerid][BB_label] = Text3D:INVALID_3DTEXT_ID;
			}
			InfoBoombox[playerid][BB_obj] = 0;
			InfoBoombox[playerid][BB_x] = 0.0;
			InfoBoombox[playerid][BB_y] = 0.0;
			InfoBoombox[playerid][BB_z] = 0.0;
			InfoBoombox[playerid][BB_int] = 0;
			InfoBoombox[playerid][BB_vw] = 0;
			DeletePVar(playerid, "BBStation");
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Recogiste tu boombox.");
		}
	}
	return 1;
}

Dialog:EmisorasBoombox(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_encender(playerid);
	switch (listitem)
	{
		case 0: ReproducirBoombox(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1652147");
		case 1: ReproducirBoombox(playerid, "http://148.251.91.15:7004");
		case 2: ReproducirBoombox(playerid, "http://173.244.215.163:8380");
		case 3: ReproducirBoombox(playerid, "http://64.202.98.133:2010");
		case 4: ReproducirBoombox(playerid, "http://50.117.115.211:80");
		case 5: ReproducirBoombox(playerid, "http://108.61.30.179:4010");
		case 6: ReproducirBoombox(playerid, "http://50.7.64.226:80/frisky_mp3_hi");
		case 7: ReproducirBoombox(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1747543");
		case 8: ReproducirBoombox(playerid, "http://62.210.209.179:8030/stream");
		case 9: ReproducirBoombox(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1316323");
		case 10: ReproducirBoombox(playerid, "http://somafm.com/tags.pls");
		case 11: ReproducirBoombox(playerid, "http://listen.shoutcast.com:80/RadioHunter-TheHitzChannel");
	}
	return 1;
}

Dialog:UrlBoombox(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_encender(playerid);
	if (isnull(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has introducido ningún URL.");
	ReproducirBoombox(playerid, inputtext);
	return 1;
}
