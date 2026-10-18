//Jugadores

cmd:mochila(playerid, params[])
{
	if (InfoPersonaje[playerid][pManoDerecha] == 86) // mochila normal
	{
		new id = InfoPersonaje[playerid][pManoDerechaCant];
		if (sscanf(params, "s[32]", params))
		{
			SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mochila (Opcion)");
			SendPlayerChatMessage(playerid, COLOR_GREY, "Opciones: ver, sacar, guardar");
			return 1;
		}
		if (!strcmp(params, "ver", true, 3))
		{
			VerMochila(playerid, id);
		}
		else if (!strcmp(params, "sacar", true, 5))
		{
			if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Posees la mano izquierda ocupada.");
			new item;
			if (sscanf(params, "s[32]i", params, item))
			{
				new count = 0;
				Loop(x, 10, 0) if (InfoMochila[id][mjObjeto][x] != 0) count++;
				if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en la mochila.");
				SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mochila sacar (slot)");
				Loop(x, 9, 0) if (InfoMochila[id][mjObjeto][x] != 0)
				{
					SendClientMessageEx(playerid, 0xEBEBEBFF, "Tienes en {4f9162}slot %d{EBEBEB}: %s", x+1, slot_objeto(InfoMochila[id][mjObjeto][x], InfoMochila[id][mjObjetoCant][x]));
				}
				return 1;
			}
			if (item < 1 || item > 10) { SendPlayerChatMessage(playerid, COLOR_GREY, "El numero de slot debe estar entre 1 y 10."); return 1; }
			SacarMochila(playerid, item - 1, id);
		}
		else if (!strcmp(params, "guardar", true, 7))
		{
			if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes nada en la mano izquierda.");
			GuardarMochila(playerid, id);
		}
	}
	return 1;
}