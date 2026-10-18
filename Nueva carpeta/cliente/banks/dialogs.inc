Dialog:ShowBanco(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			new gformat[170];
			format(gformat, sizeof gformat, "Tienes $%s en tu cuenta bancaria.", diner_coma(InfoPersonaje[playerid][pBanco]));
			SendPlayerChatMessage(playerid, 0x0CA7B8FF, gformat);
		}
		case 1:
		{
			Dialog_Show(playerid, RetirarBancoEfectivo, DIALOG_STYLE_INPUT, "Retirar efectivo", "{EBEBEB}Por favor, ingrese el monto a retirar:\n", "Retirar", "Volver");
		}
		case 2:
		{
			Dialog_Show(playerid, DepositarBancoEfectivo, DIALOG_STYLE_INPUT, "Depositar efectivo", "{EBEBEB}Por favor, ingrese el monto a depositar:\n", "Depositar", "Volver");
		}
		case 3:
		{
			if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos dos horas, para poder transferir dinero.");
            ConTransferir[playerid] = 1;
			Dialog_Show(playerid, TransferirBancoDinero, DIALOG_STYLE_INPUT, "Transferencia (paso 1)", "{EBEBEB}Por favor, ingrese {F5DEB3}ID del jugador{EBEBEB} que deseas transferir dinero:", "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:RetirarBancoEfectivo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_banco(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new dinero = strval(inputtext), string[170];
	if (dinero < 1 || dinero > 1000000) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Máximo que puedes retirar más de $1,000,000.");
	if (dinero > InfoPersonaje[playerid][pBanco]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes esa cantidad en tu cuenta bancaria.");
	GivePlayerCash(playerid, dinero, "retiro de dinero banco");
	InfoPersonaje[playerid][pBanco] -= dinero;
	format(string, sizeof string, "* Sacaste en efectivo $%s. Ahora tienes en tu cuenta bancaria $%s.", diner_coma(dinero), diner_coma(InfoPersonaje[playerid][pBanco]));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	rol_ame(playerid, "hace una transacción bancaria.");
	format(string, sizeof string, "%s retiró $%s.", NombreDeCuenta(playerid), diner_coma(dinero));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	return 1;
}

Dialog:DepositarBancoEfectivo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_banco(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new dinero = strval(inputtext), string[170];
	if (dinero < 1 || dinero > 1000000) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Máximo que puedes depositar más de $1,000,000.");
	if (dinero > GetPlayerCash(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes esa cantidad en efectivo.");
	GivePlayerCash(playerid, -dinero, "deposito de dinero banco");
	InfoPersonaje[playerid][pBanco] += dinero;
	format(string, sizeof string, "* Depositaste en efectivo $%s. Ahora tienes en tu cuenta bancaria $%s.", diner_coma(dinero), diner_coma(InfoPersonaje[playerid][pBanco]));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	rol_ame(playerid, "hace una transacción bancaria.");
	format(string, sizeof string, "%s depositó $%s.", NombreDeCuenta(playerid), diner_coma(dinero));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	return 1;
}

Dialog:TransferirBancoDinero(playerid, response, listitem, inputtext[])
{
	if (ConTransferir[playerid] == 2)
	{
		if (!response)
	    {
   			if (IsPlayerContrato(playerid, 1) != 0) Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {F5DEB3}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles\n- {00CC00}Repartos disponibles", "Continuar", "Volver");
			else Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {F5DEB3}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
			return 1;
		}
	}
	else { if (!response) return pc_cmd_banco(playerid); }

	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new playerid2 = strval(inputtext);
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes transferirte dinero a ti mismo.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador no conectado.");
	SetPVarInt(playerid,"JugadorATransferir",playerid2);
	Dialog_Show(playerid, TransferirBanco2Dinero, DIALOG_STYLE_INPUT, "Transferencia (paso 2)", "{EBEBEB}Ahora ingresa el monto a transferir:", "Transferir", "Volver");
	return 1;
}

Dialog:TransferirBanco2Dinero(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new playerid2 = GetPVarInt(playerid, "JugadorATransferir"), dinero = strval(inputtext), string[180];
	if (dinero > InfoPersonaje[playerid][pBanco]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Cantidad incorrecta.");
	if (dinero < 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes transferir menos de 0.");
	InfoPersonaje[playerid][pBanco] -= dinero;
	InfoPersonaje[playerid2][pBanco] += dinero;
	format(string, sizeof string, "* Realizaste una transferencia de $%s a %s.", diner_coma(dinero), GetNameFormat(playerid2));
	SendPlayerChatMessage(playerid, 0xEAEA00FF, string);
	format(string, sizeof string, "* Recibiste una transferencia de $%s de %s.", diner_coma(dinero), GetNameFormat(playerid));
	SendPlayerChatMessage(playerid2, 0xFFFF04FF, string);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid2, 1052, 0.0, 0.0, 0.0);
	format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) hizo una transferencia de $%s a %s(%d).", NombreOriginal(playerid), playerid, diner_coma(dinero), NombreOriginal(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s transfirió $%s a %s.", NombreDeCuenta(playerid), diner_coma(dinero), NombreDeCuenta(playerid2));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pBanco]);
	DeletePVar(playerid, "JugadorATransferir");
	rol_ame(playerid, "hace una transacción bancaria.");
	return 1;
}

Dialog:ShowCajero(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			new gformat[170];
			format(gformat, sizeof gformat, "Tienes $%s en tu cuenta bancaria.", diner_coma(InfoPersonaje[playerid][pBanco]));
			SendPlayerChatMessage(playerid, 0x0CA7B8FF, gformat);
		}
		case 1:
		{
			if (InfoPersonaje[playerid][pTogCajero] != 0)
			{
				new gformat[190];
				format(gformat, sizeof gformat, "* Debes esperar %d minutos para volver a retirar efectivo, puedes ir al banco sino quieres esperar.", InfoPersonaje[playerid][pTogCajero]);
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
			    return 1;
			}
			Dialog_Show(playerid, RetirarEfectivo, DIALOG_STYLE_INPUT, "Retirar efectivo", "{EBEBEB}Por favor, ingrese el monto a retirar:\n\n{0CA7B8}El máximo a retirar es de $100,000 dólares por hora.", "Retirar", "Volver");
		}
		case 2:
		{
			Dialog_Show(playerid, DepositarEfectivo, DIALOG_STYLE_INPUT, "Depositar efectivo", "{EBEBEB}Por favor, ingrese el monto a depositar:\n", "Depositar", "Volver");
		}
		case 3:
		{
			if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos dos horas, para poder transferir dinero.");
			Dialog_Show(playerid, TransferirDinero, DIALOG_STYLE_INPUT, "Transferencia (paso 1)", "{EBEBEB}Por favor, ingrese {F5DEB3}ID del jugador{EBEBEB} que deseas transferir dinero:", "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:RetirarEfectivo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_cajero(playerid);
	new id = EnIDatm[playerid];
	if (InfoCajero[id][atmDinero] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay más efectivo en este cajero.");
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new dinero = strval(inputtext), string[170];
	if (dinero < 1 || dinero > 100000) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Máximo que puedes retirar por hora es $100,000.");
	if (dinero > InfoPersonaje[playerid][pBanco]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes esa cantidad en tu cuenta bancaria.");
	if (dinero > InfoCajero[id][atmDinero]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay esa cantidad de efectivo en este cajero automático.");
	GivePlayerCash(playerid, dinero, "retiro de dinero atm");
	InfoPersonaje[playerid][pBanco] -= dinero;
	InfoCajero[id][atmDinero] -= dinero;
	guardar_int_mysql("cajeros", "BolosUwU", InfoCajero[id][atmID_sql], InfoCajero[id][atmDinero]);
	format(string, sizeof string, "* Sacaste en efectivo $%s. Ahora tienes en tu cuenta bancaria $%s.", diner_coma(dinero), diner_coma(InfoPersonaje[playerid][pBanco]));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	rol_ame(playerid, "hace una transacción bancaria.");
	format(string, sizeof string, "%s retiró $%s.", NombreDeCuenta(playerid), diner_coma(dinero));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	Label_cajero(id, 0);
	if (dinero >= 50000)
	{
		InfoPersonaje[playerid][pTogCajero] = 60;
		guardar_int_mysql("personajes", "TogCajero", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogCajero]);
	}
	return 1;
}

Dialog:DepositarEfectivo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_cajero(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new id = EnIDatm[playerid];
	new dinero = strval(inputtext), string[170];
	if (dinero < 1 || dinero > 1000000) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Máximo que puedes depositar más de $1,000,000.");
	if (dinero > GetPlayerCash(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes esa cantidad en efectivo.");
	GivePlayerCash(playerid, -dinero, "deposito de dinero banco");
	InfoPersonaje[playerid][pBanco] += dinero;
	format(string, sizeof string, "* Depositaste en efectivo $%s. Ahora tienes en tu cuenta bancaria $%s.", diner_coma(dinero), diner_coma(InfoPersonaje[playerid][pBanco]));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	rol_ame(playerid, "hace una transacción bancaria.");
	format(string, sizeof string, "%s depositó $%s.", NombreDeCuenta(playerid), diner_coma(dinero));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	InfoCajero[id][atmDinero] += dinero;
	guardar_int_mysql("cajeros", "BolosUwU", InfoCajero[id][atmID_sql], InfoCajero[id][atmDinero]);
	Label_cajero(id, 0);
	return 1;
}

Dialog:TransferirDinero(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_cajero(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new playerid2 = strval(inputtext);
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes transferirte dinero a ti mismo.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador no conectado.");
	SetPVarInt(playerid,"JugadorATransferir",playerid2);
	Dialog_Show(playerid, Transferir2Dinero, DIALOG_STYLE_INPUT, "Transferencia (paso 2)", "{EBEBEB}Ahora ingresa el monto a transferir:", "Transferir", "Salir");
	return 1;
}

Dialog:Transferir2Dinero(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números porfavor, vuelve a intentarlo.");
	new playerid2 = GetPVarInt(playerid, "JugadorATransferir"), dinero = strval(inputtext), string[180];
	if (dinero > InfoPersonaje[playerid][pBanco]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Cantidad incorrecta.");
	if (dinero < 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes transferir menos de 0.");
	InfoPersonaje[playerid][pBanco] -= dinero;
	InfoPersonaje[playerid2][pBanco] += dinero;
	format(string, sizeof string, "* Realizaste una transferencia de $%s a %s.", diner_coma(dinero), GetNameFormat(playerid2));
	SendPlayerChatMessage(playerid, 0xEAEA00FF, string);
	format(string, sizeof string, "* Recibiste una transferencia de $%s de %s.", diner_coma(dinero), GetNameFormat(playerid));
	SendPlayerChatMessage(playerid2, 0xFFFF04FF, string);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid2, 1052, 0.0, 0.0, 0.0);
	format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) hizo una transferencia de $%s a %s(%d).", NombreOriginal(playerid), playerid, diner_coma(dinero), NombreOriginal(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s transfirió $%s a %s.", NombreDeCuenta(playerid), diner_coma(dinero), NombreDeCuenta(playerid2));
	Log("f_logs/banco.log", string);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pBanco]);
	guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pBanco]);
	DeletePVar(playerid, "JugadorATransferir");
	rol_ame(playerid, "hace una transacción bancaria.");
	return 1;
}
