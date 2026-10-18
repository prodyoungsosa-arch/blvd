//Jugadores
cmd:caja(playerid, params[])
{
	if (InfoPersonaje[playerid][pManoDerecha] == 55) // caja normal
	{
		new id = InfoPersonaje[playerid][pManoDerechaCant];
		if (sscanf(params, "s[32]", params))
		{
			SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /caja (Opción)");
			SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: ver, sacar, guardar");
			return 1;
		}
		if (!strcmp(params, "ver", true, 3))
		{
			VerCaja(playerid, id);
		}
		else if (!strcmp(params, "sacar", true, 5))
		{
			if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Posees la mano izquierda ocupada.");
			new item;
			if (sscanf(params, "s[32]i", params, item))
			{
				new count = 0;
				Loop(x, 10, 0) if (InfoCaja[id][cjObjeto][x] != 0) count++;
				if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en la caja.");
				SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /caja sacar (slot)");
				Loop(x, 9, 0) if (InfoCaja[id][cjObjeto][x] != 0)
				{
					SendClientMessageEx(playerid, 0xEBEBEBFF, "Tienes en {F5DEB3}slot %d{EBEBEB}: %s", x+1, slot_objeto(InfoCaja[id][cjObjeto][x], InfoCaja[id][cjObjetoCant][x]));
				}
				return 1;
			}
			if (item < 1 || item > 10) { SendPlayerChatMessage(playerid, COLOR_GREY, "El número de slot debe estar entre 1 y 10."); return 1; }
			SacarCaja(playerid, item - 1, id);
		}
		else if (!strcmp(params, "guardar", true, 7))
		{
			if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes nada en la mano izquierda.");
			GuardarCaja(playerid, id);
		}
		return 1;
	}
	if (InfoPersonaje[playerid][pManoDerecha] == 67) // sixpack de cerveza
	{
		if (sscanf(params, "s[32]", params))
		{
			SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /caja (Opción)");
			SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: sacar");
			return 1;
		}
		if (!strcmp(params, "sacar", true, 5))
		{
			if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Posees la mano izquierda ocupada.");
			new objeto = 65;
			InfoPersonaje[playerid][pManoDerechaCant]--;
			InfoPersonaje[playerid][pManoIzquierda] = objeto;
			PonerObjeto(playerid, 2, objeto);
			InfoPersonaje[playerid][pManoIzquierdaCant] = InfoInventario[objeto][DefaultCantidad];
			ActualizarManos(playerid, 1);
			SendPlayerChatMessage(playerid, 0x828BFDFF, "Sacas una botella de cerveza del sixpack. (/beber)");
		}
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ninguna caja en tu mano derecha.");
	return 1;
}
