new CobroActual[MAX_PLAYERS];

Dialog:NegocioOpciones(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = EnNegocio(playerid), gformat[360];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	switch (listitem)
	{
		case 0:
		{
			format(gformat, sizeof gformat, "{EBEBEB}Nombre actual: {0080C0}%s", InfoNegocio[id][nNombre]);
			Dialog_Show(playerid, NegocioNombre, DIALOG_STYLE_INPUT, gformat, "{EBEBEB}Escribe el nuevo nombre de tu negocio:", "Continuar", "Volver");
		}
		case 1:
		{
			format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoNegocio[id][nDinero]));
			Dialog_Show(playerid, DineroNegocio, DIALOG_STYLE_LIST, gformat, "- Retirar dinero\n- Depositar dinero", "Continuar", "Volver");
		}
		case 2:
		{
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
			TallerOpened(id, InfoNegocio[id][nSeguro]);
			guardar_int_mysql("negocios", "Seguro", InfoNegocio[id][nID_sql], InfoNegocio[id][nSeguro]);
		}
		case 3:
		{
			new pagoG = neg_automatico[InfoNegocio[id][nTipo]];
			if (pagoG == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Tu negocio/empresa no necesita productos.");
			CobroActual[playerid] = (pagoG/2)*10;
			format(gformat, sizeof gformat, "{EBEBEB}¿Deseas pagar {F72222}$%s{EBEBEB} por 200 productos?\nPodrías generar {00CC00}$%s{EBEBEB} cada dos horas por 20 productos.", diner_coma(CobroActual[playerid]), diner_coma(pagoG));
			Dialog_Show(playerid, NegocioProductos, DIALOG_STYLE_MSGBOX, "Productos", gformat, "Ordenar", "Volver");
		}
		case 4: NegocioShareShow(playerid);
	}
	return 1;
}

Dialog:NegocioProductos(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_negociomenu(playerid);
	new id = EnNegocio(playerid), query[260];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	new costo = CobroActual[playerid];
	if (GetPlayerCash(playerid) >= costo)
	{
		if (InfoNegocio[id][nProductos] >= 4000) return SendPlayerChatMessage(playerid, 0xEFEFEFFF, "No puedes tener más de 4,000 productos.");
		InfoNegocio[id][nProductos] += 200;
		GivePlayerCash(playerid, -costo, "compra de productos");
		guardar_int_mysql("negocios", "Productos", InfoNegocio[id][nID_sql], InfoNegocio[id][nProductos]);
		format(query, sizeof query, "Pagaste 200 productos por $%s. Ahora tienes %d productos.", diner_coma(costo), InfoNegocio[id][nProductos]);
		SendPlayerChatMessage(playerid, 0xFFEA5FFF, query);
	}
	else
	{
		format(query, sizeof query, "No tienes $%s para pagar los productos.", diner_coma(costo));
		SendPlayerChatMessage(playerid, 0xEFEFEFFF, query);
	}
	return 1;
}

Dialog:NegocioNombre(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_negociomenu(playerid);
	new id = EnNegocio(playerid), gformat[260];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (!strlen(inputtext))
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "Escribe algo.");
		format(gformat, sizeof gformat, "{EBEBEB}Nombre actual: {0080C0}%s", InfoNegocio[id][nNombre]);
		Dialog_Show(playerid, NegocioNombre, DIALOG_STYLE_INPUT, gformat, "{EBEBEB}Escribe el nuevo nombre de tu negocio:", "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) > 30 || strlen(inputtext) < 0)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes poner el nombre con más de 30 carácteres.");
		format(gformat, sizeof gformat, "{EBEBEB}Nombre actual: {0080C0}%s", InfoNegocio[id][nNombre]);
		Dialog_Show(playerid, NegocioNombre, DIALOG_STYLE_INPUT, gformat, "{EBEBEB}Escribe el nuevo nombre de tu negocio:", "Continuar", "Volver");
		return 1;
	}
	alm(InfoNegocio[id][nNombre], inputtext);
	Labelupdate_negocio(id);
	guardar_string_mysql("negocios", "Nombre", InfoNegocio[id][nID_sql], InfoNegocio[id][nNombre]);
	format(gformat, sizeof gformat, "Nombre de negocio cambiado a {0080C0}%s", InfoNegocio[id][nNombre]);
	SendPlayerChatMessage(playerid, -1, gformat);
	return 1;
}

Dialog:DineroNegocio(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_negociomenu(playerid);
	new id = EnNegocio(playerid), gformat[260];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	switch (listitem)
	{
		case 0:
		{
			format(gformat, sizeof gformat, "{EBEBEB}Ingresa el monto que quieres retirar de la caja.\n\nTienes {00CC00}$%s{EBEBEB} dólares.\n", diner_coma(InfoNegocio[id][nDinero]));
			Dialog_Show(playerid, DineroRNegocio, DIALOG_STYLE_INPUT, "Sacar dinero", gformat, "Continuar", "Volver");
		}
		case 1:
		{
			format(gformat, sizeof gformat, "{EBEBEB}Ingresa el monto que quieres depositar en la caja.\n\nTienes {00CC00}$%s{EBEBEB} dólares.\n", diner_coma(InfoNegocio[id][nDinero]));
			Dialog_Show(playerid, DineroDNegocio, DIALOG_STYLE_INPUT, "Guardar dinero", gformat, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:DineroRNegocio(playerid, response, listitem, inputtext[])
{
	new id = EnNegocio(playerid), gformat[260];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (!response)
	{
		format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoNegocio[id][nDinero]));
		Dialog_Show(playerid, DineroNegocio, DIALOG_STYLE_LIST, gformat, "- Retirar dinero\n- Depositar dinero", "Continuar", "Volver");
		return 1;
	}
	new amount = strval(inputtext);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	if (amount < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes retirar menos de un dolar.");
	if (InfoNegocio[id][nDinero] >= amount)
	{
		InfoNegocio[id][nDinero] -= amount;
		GivePlayerCash(playerid, amount, "retiro de caja negocio");
		format(gformat, sizeof gformat, "Retiraste $%s dejaste en la caja $%s, ahora tienes en bolsillos $%s.", diner_coma(amount), diner_coma(InfoNegocio[id][nDinero]), diner_coma(GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
		return 1;
	}
	format(gformat, sizeof gformat, "* No puedes retirar $%s, si sólo tienes en el bául $%s.", diner_coma(amount), diner_coma(InfoNegocio[id][nDinero]));
	SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
	return 1;
}

Dialog:DineroDNegocio(playerid, response, listitem, inputtext[])
{
	new id = EnNegocio(playerid), gformat[260];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (!response)
	{
		format(gformat, sizeof gformat, "Dinero: {00CC00}$%s", diner_coma(InfoNegocio[id][nDinero]));
		Dialog_Show(playerid, DineroNegocio, DIALOG_STYLE_LIST, gformat, "- Retirar dinero\n- Depositar dinero", "Continuar", "Volver");
		return 1;
	}
	new amount = strval(inputtext);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	if (amount < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes depositar menos de un dolar.");
	if (GetPlayerCash(playerid) >= amount)
	{
		InfoNegocio[id][nDinero] += amount;
		GivePlayerCash(playerid, -amount, "deposito de caja negocio");
		format(gformat, sizeof gformat, "Depositaste $%s en la caja (total: $%s), ahora tienes en bolsillos $%s.", diner_coma(amount), diner_coma(InfoNegocio[id][nDinero]), diner_coma(GetPlayerCash(playerid)));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
		return 1;
	}
	format(gformat, sizeof gformat, "* No puedes depositar $%s, si sólo tienes en bolsillos $%s.", diner_coma(amount), diner_coma(GetPlayerCash(playerid)));
	SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
	return 1;
}

NegocioShareShow(playerid)
{
	new id = EnNegocio(playerid), gformat[370], dialog_show[1028];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	//slot1
	if (strcmp(InfoNegocio[id][nCompartida1], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 1\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 1:{59F37B} %s\n", InfoNegocio[id][nCompartida1]);
		strcat(dialog_show, gformat);
	}
	//slot2
	if (strcmp(InfoNegocio[id][nCompartida2], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 2\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 2:{59F37B} %s\n", InfoNegocio[id][nCompartida2]);
		strcat(dialog_show, gformat);
	}
	//slot3
	if (strcmp(InfoNegocio[id][nCompartida3], "none", true) == 0) { strcat(dialog_show, "{EBEBEB}Disponible slot 3\n"); }
	else
	{
		format(gformat, sizeof gformat, "{EBEBEB}Slot 3:{59F37B} %s\n", InfoNegocio[id][nCompartida3]);
		strcat(dialog_show, gformat);
	}
	//dialog preview
	Dialog_Show(playerid, CompartirNegocio, DIALOG_STYLE_LIST, "Permisos de tu negocio", dialog_show, "Continuar", "Volver");
	return 1;
}

new ShareNegocio[MAX_PLAYERS];

Dialog:CompartirNegocio(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_negociomenu(playerid);
	new n = EnNegocio(playerid), gformat[370];
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (LlavesNegocio(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	switch (listitem)
	{
	    case 0: //slot1
	    {
			if (strcmp(InfoNegocio[n][nCompartida1], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Negocio, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 1", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su negocio.", "Continuar", "Volver");
				ShareNegocio[playerid] = 1;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu negocio a %s?\n", InfoNegocio[n][nCompartida1]);
				Dialog_Show(playerid, Compartir3Negocio, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 1", gformat, "Sí", "Volver");
				ShareNegocio[playerid] = 1;
			}
		}
	    case 1: //slot2
	    {
			if (strcmp(InfoNegocio[n][nCompartida2], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Negocio, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 2", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su negocio.", "Continuar", "Volver");
				ShareNegocio[playerid] = 2;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu negocio a %s?\n", InfoNegocio[n][nCompartida2]);
				Dialog_Show(playerid, Compartir3Negocio, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 2", gformat, "Sí", "Volver");
				ShareNegocio[playerid] = 2;
			}
		}
	    case 2: //slot3
	    {
			if (strcmp(InfoNegocio[n][nCompartida3], "none", true) == 0)
			{
				Dialog_Show(playerid, Compartir2Negocio, DIALOG_STYLE_INPUT, "Permisos {59F37B}slot 3", "{ebebeb}Por favor ingrese la ID del jugador que desea compartir permisos de su negocio.", "Continuar", "Volver");
				ShareNegocio[playerid] = 3;
			}
			else
			{
				format(gformat, sizeof gformat, "{ebebeb}¿Deseas quitarle los permisos de tu negocio a %s?\n", InfoNegocio[n][nCompartida1]);
				Dialog_Show(playerid, Compartir3Negocio, DIALOG_STYLE_MSGBOX, "Permisos {59F37B}slot 3", gformat, "Sí", "Volver");
				ShareNegocio[playerid] = 3;
			}
		}
	}
	return 1;
}

Dialog:Compartir2Negocio(playerid, response, listitem, inputtext[])
{
	if (!response) return NegocioShareShow(playerid);
	new n = EnNegocio(playerid);
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (LlavesNegocio(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo puedes ingresar números, intenta de nuevo.");
	new playerid2 = strval(inputtext);
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes compartir permisos del negocio a ti mismo.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El jugador seleccionado no se encuentra conectado.");
	if (strmatch(InfoNegocio[n][nCompartida1], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu negocio, revisa slot 1."); return 1; }
	if (strmatch(InfoNegocio[n][nCompartida2], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu negocio, revisa slot 2."); return 1; }
	if (strmatch(InfoNegocio[n][nCompartida3], InfoPersonaje[playerid2][pNombre_Apellido])) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador ya tiene permisos en tu negocio, revisa slot 3."); return 1; }
	switch (ShareNegocio[playerid])
	{
	    case 1: { alm(InfoNegocio[n][nCompartida1], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("negocios", "Compartida1", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida1]); }
	    case 2: { alm(InfoNegocio[n][nCompartida2], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("negocios", "Compartida2", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida2]); }
	    case 3: { alm(InfoNegocio[n][nCompartida3], InfoPersonaje[playerid2][pNombre_Apellido]); guardar_string_mysql("negocios", "Compartida3", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida3]); }
	}
	SendClientMessageEx(playerid2, 0x59F37BFF, "* %s te ha dado permisos de su negocio %d.", NombreOriginal(playerid), n);
	SendClientMessageEx(playerid, 0x59F37BFF, "* Cediste permisos de tu negocio %d con %s (slot %d).", n, NombreOriginal(playerid2), ShareNegocio[playerid]);
	return 1;
}

Dialog:Compartir3Negocio(playerid, response, listitem, inputtext[])
{
	if (!response) return NegocioShareShow(playerid);
	new n = EnNegocio(playerid);
	if (n == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ningún negocio.");
	if (LlavesNegocio(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	switch (ShareNegocio[playerid])
	{
	    case 1:
		{
			if (strmatch(InfoNegocio[n][nCompartida1], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 1."); return 1; }
			new playerid2;
			sscanf(InfoNegocio[n][nCompartida1], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su negocio %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu negocio %d a %s. (slot 1)", n, InfoNegocio[n][nCompartida1]);
			alm(InfoNegocio[n][nCompartida1], "none");
			guardar_string_mysql("negocios", "Compartida1", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida1]);
		}
	    case 2:
		{
			if (strmatch(InfoNegocio[n][nCompartida2], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 2."); return 1; }
			new playerid2;
			sscanf(InfoNegocio[n][nCompartida2], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su negocio %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu negocio %d a %s. (slot 2)", n, InfoNegocio[n][nCompartida2]);
			alm(InfoNegocio[n][nCompartida2], "none");
			guardar_string_mysql("negocios", "Compartida2", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida2]);
		}
	    case 3:
		{
			if (strmatch(InfoNegocio[n][nCompartida3], "none")) { SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes disponible el slot 3."); return 1; }
			new playerid2;
			sscanf(InfoNegocio[n][nCompartida3], "u", playerid2);
			if (IsPlayerConnectedEx(playerid2))
			{
				SendClientMessageEx(playerid2, 0x79A5C9FF, "* %s te removió los permisos de su negocio %d.", NombreOriginal(playerid), n);
			}
			SendClientMessageEx(playerid, 0x79A5C9FF, "* Removiste los permisos de tu negocio %d a %s. (slot 3)", n, InfoNegocio[n][nCompartida3]);
			alm(InfoNegocio[n][nCompartida3], "none");
			guardar_string_mysql("negocios", "Compartida3", InfoNegocio[n][nID_sql], InfoNegocio[n][nCompartida3]);
		}
	}
	return 1;
}