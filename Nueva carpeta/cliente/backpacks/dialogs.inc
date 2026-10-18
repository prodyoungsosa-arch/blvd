Dialog:ShowMochila(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (InfoPersonaje[playerid][pManoDerecha] != 86) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ninguna mochila en tu mano derecha.");
	new id = InfoPersonaje[playerid][pManoDerechaCant];
	switch (listitem)
	{
		case 0..9: SacarMochila(playerid, listitem, id);
		case 10: return 1;
		case 11: GuardarMochila(playerid, id);
	}
	return 1;
}
