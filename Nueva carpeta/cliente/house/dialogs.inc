new ShareCasa[MAX_PLAYERS];
Dialog:CasaOpciones(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new idcasa = EnCasa(playerid), gformat[370];
	if (idcasa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, idcasa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	switch (listitem)
	{
		case 0:
		{
		    format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoCasa[idcasa][cDinero]));
			Dialog_Show(playerid, DineroCasa, DIALOG_STYLE_LIST, gformat, "Retirar dinero\nDepositar dinero", "Continuar", "Volver");
		}
		case 1:
		{
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, "Para guardar objetos/armas en el armario, usa: {3E62F4}/guardararmario{EBEBEB} o {3E62F4}/garmario");
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, "Para sacar objetos/armas del armario, usa: {3E62F4}/sacararmario (slot){EBEBEB} o {3E62F4}/garmario (slot)");
		}
		case 2: CasaShareShow(playerid);
	}
	return 1;
}

Dialog:DineroCasa(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_casamenu(playerid);
	new idcasa = EnCasa(playerid), gformat[370];
	if (idcasa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, idcasa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	switch (listitem)
	{
		case 0:
		{
			format(gformat, sizeof gformat, "{EBEBEB}Ingresa el monto que quieres retirar del baúl de tu casa.\n\nTienes {00CC00}$%s{EBEBEB} dólares.\n", diner_coma(InfoCasa[idcasa][cDinero]));
			Dialog_Show(playerid, DineroRCasa, DIALOG_STYLE_INPUT, "Sacar dinero", gformat, "Continuar", "Volver");
		}
		case 1:
		{
			format(gformat, sizeof gformat, "{EBEBEB}Ingresa el monto que quieres depositar en el baúl de tu casa.\n\nTienes {00CC00}$%s{EBEBEB} dólares.\n", diner_coma(InfoCasa[idcasa][cDinero]));
			Dialog_Show(playerid, DineroDCasa, DIALOG_STYLE_INPUT, "Guardar dinero", gformat, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:DineroRCasa(playerid, response, listitem, inputtext[])
{
	new idcasa = EnCasa(playerid), gformat[370];
	if (idcasa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, idcasa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (!response)
	{
		format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoCasa[idcasa][cDinero]));
		Dialog_Show(playerid, DineroCasa, DIALOG_STYLE_LIST, gformat, "Retirar dinero\nDepositar dinero", "Continuar", "Volver");
		return 1;
	}
	new amount = strval(inputtext);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	if (amount < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes retirar menos de un dolar.");
	if (InfoCasa[idcasa][cDinero] >= amount)
	{
		InfoCasa[idcasa][cDinero] -= amount;
		GivePlayerCash(playerid, amount, "retiro baul casa");
		format(gformat, sizeof gformat, "Retiraste $%s de tu casa dejaste en el baúl $%s, ahora tienes en bolsillos $%s.", diner_coma(amount), diner_coma(InfoCasa[idcasa][cDinero]), diner_coma(GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
		guardar_int_mysql("casas", "BolosUwU", InfoCasa[idcasa][cID_sql], InfoCasa[idcasa][cDinero]);
		return 1;
	}
	format(gformat, sizeof gformat, "* No puedes retirar $%s, si sólo tienes en el bául $%s.", diner_coma(amount), diner_coma(InfoCasa[idcasa][cDinero]));
	SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
	return 1;
}

Dialog:DineroDCasa(playerid, response, listitem, inputtext[])
{
	new idcasa = EnCasa(playerid), gformat[370];
	if (idcasa == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, idcasa) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (!response)
	{
		format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoCasa[idcasa][cDinero]));
		Dialog_Show(playerid, DineroCasa, DIALOG_STYLE_LIST, gformat, "Retirar dinero\nDepositar dinero", "Continuar", "Volver");
		return 1;
	}
	new amount = strval(inputtext);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	if (amount < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes depositar menos de un dolar.");
	if (GetPlayerCash(playerid) >= amount)
	{
		InfoCasa[idcasa][cDinero] += amount;
		GivePlayerCash(playerid, -amount, "deposito baul casa");
		format(gformat, sizeof gformat, "Depositaste $%s en tu casa (total: $%s), ahora tienes en bolsillos $%s.", diner_coma(amount), diner_coma(InfoCasa[idcasa][cDinero]), diner_coma(GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
		guardar_int_mysql("casas", "BolosUwU", InfoCasa[idcasa][cID_sql], InfoCasa[idcasa][cDinero]);
		return 1;
	}
	format(gformat, sizeof gformat, "* No puedes depositar $%s, si sólo tienes en bolsillos $%s.", diner_coma(amount), diner_coma(GetPlayerCash(playerid)));
	SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
	return 1;
}

Dialog:CompartirCasa(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_casamenu(playerid);
	new n = EnCasa(playerid), gformat[370];
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	switch (listitem)
	{
	    case 0: //slot1
	    {
			if (strcmp(InfoCasa[n][cCompartida1], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Casa, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 1", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su casa.", "Continuar", "Volver");
				ShareCasa[playerid] = 1;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu casa a %s?\n", InfoCasa[n][cCompartida1]);
				Dialog_Show(playerid, Compartir3Casa, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 1", gformat, "Sí", "Volver");
				ShareCasa[playerid] = 1;
			}
		}
	    case 1: //slot2
	    {
			if (strcmp(InfoCasa[n][cCompartida2], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Casa, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 2", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su casa.", "Continuar", "Volver");
				ShareCasa[playerid] = 2;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu casa a %s?\n", InfoCasa[n][cCompartida2]);
				Dialog_Show(playerid, Compartir3Casa, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 2", gformat, "Sí", "Volver");
				ShareCasa[playerid] = 2;
			}
		}
	    case 2: //slot3
	    {
			if (strcmp(InfoCasa[n][cCompartida3], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Casa, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 3", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su casa.", "Continuar", "Volver");
				ShareCasa[playerid] = 3;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu casa a %s?\n", InfoCasa[n][cCompartida1]);
				Dialog_Show(playerid, Compartir3Casa, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 3", gformat, "Sí", "Volver");
				ShareCasa[playerid] = 3;
			}
		}
	}
	return 1;
}

Dialog:Compartir2Casa(playerid, response, listitem, inputtext[])
{
	if (!response) return CasaShareShow(playerid);
	new n = EnCasa(playerid);
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo puedes ingresar números, intenta de nuevo.");
	new playerid2 = strval(inputtext);
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes compartir permisos de la casa a ti mismo.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El jugador seleccionado no se encuentra conectado.");
	if (strmatch(InfoCasa[n][cCompartida1], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu casa, revisa slot 1."); return 1; }
	if (strmatch(InfoCasa[n][cCompartida2], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu casa, revisa slot 2."); return 1; }
	if (strmatch(InfoCasa[n][cCompartida3], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu casa, revisa slot 3."); return 1; }
	switch (ShareCasa[playerid])
	{
	    case 1: { alm(InfoCasa[n][cCompartida1], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("casas", "Compartida1", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida1]); }
	    case 2: { alm(InfoCasa[n][cCompartida2], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("casas", "Compartida2", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida2]); }
	    case 3: { alm(InfoCasa[n][cCompartida3], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("casas", "Compartida3", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida3]); }
	}
	SendClientMessageEx(playerid2, 0x59F37BFF, "* %s te ha dado permisos de su casa %d.", NombreOriginal(playerid), n);
	SendClientMessageEx(playerid, 0x59F37BFF, "* Cediste permisos de tu casa %d con %s (slot %d).", n, NombreOriginal(playerid2), ShareCasa[playerid]);
	return 1;
}

Dialog:Compartir3Casa(playerid, response, listitem, inputtext[])
{
	if (!response) return CasaShareShow(playerid);
	new n = EnCasa(playerid);
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna casa.");
	if (LlavesCasa(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de esta casa.");
	switch (ShareCasa[playerid])
	{
	    case 1:
		{
			if (strmatch(InfoCasa[n][cCompartida1], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 1."); return 1; }
			new playerid2;
			sscanf(InfoCasa[n][cCompartida1], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su casa %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu casa %d a %s. (slot 1)", n, InfoCasa[n][cCompartida1]);
			alm(InfoCasa[n][cCompartida1], "none");
			guardar_string_mysql("casas", "Compartida1", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida1]);
		}
	    case 2:
		{
			if (strmatch(InfoCasa[n][cCompartida2], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 2."); return 1; }
			new playerid2;
			sscanf(InfoCasa[n][cCompartida2], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su casa %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu casa %d a %s. (slot 2)", n, InfoCasa[n][cCompartida2]);
			alm(InfoCasa[n][cCompartida2], "none");
			guardar_string_mysql("casas", "Compartida2", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida2]);
		}
	    case 3:
		{
			if (strmatch(InfoCasa[n][cCompartida3], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 3."); return 1; }
			new playerid2;
			sscanf(InfoCasa[n][cCompartida3], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su casa %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu casa %d a %s. (slot 3)", n, InfoCasa[n][cCompartida3]);
			alm(InfoCasa[n][cCompartida3], "none");
			guardar_string_mysql("casas", "Compartida3", InfoCasa[n][cID_sql], InfoCasa[n][cCompartida3]);
		}
	}
	return 1;
}