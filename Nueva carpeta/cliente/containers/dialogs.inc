Dialog:D_CONTENEDOR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new contenedorid = GetPVarInt(playerid, "ViendoContID"), id = listitem, string[128];
	ActualizarManos(playerid);
	new Bol = InfoContenedor[contenedorid][cInv][id], Cant = InfoContenedor[contenedorid][cInvCant][id];
	if(Bol == 0) return 1;
	if(InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		if(InfoInventario[Bol][IDArma] > 0)
		{
			new arma = InfoInventario[Bol][IDArma], municion = Cant;
			if(municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
		}
		InfoPersonaje[playerid][pManoDerecha] = Bol;
		InfoPersonaje[playerid][pManoDerechaCant] = Cant;
		PonerObjeto(playerid, 1, Bol);
		InfoContenedor[contenedorid][cInv][id] = 0;
		InfoContenedor[contenedorid][cInvCant][id] = 0;
		format(string, sizeof(string), "Sacaste %s del contenedor de basura.", InfoInventario[Bol][NombreObjeto]);
		SendPlayerChatMessage(playerid, 0x828BFDFF, string);
		format(string, sizeof(string), "recoge %s del contenedor de basura.", InfoInventario[Bol][NombreObjeto]);
		rol_ame(playerid, string);
		return 1;
	}
	else if(InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = Bol;
		InfoPersonaje[playerid][pManoIzquierdaCant] = Cant;
		PonerObjeto(playerid, 2, Bol);
		InfoContenedor[contenedorid][cInv][id] = 0;
		InfoContenedor[contenedorid][cInvCant][id] = 0;
		format(string, sizeof(string), "Sacas %s del contenedor de basura.", InfoInventario[Bol][NombreObjeto]);
		SendPlayerChatMessage(playerid, 0x828BFDFF, string);
		format(string, sizeof(string), "recoge %s del contenedor de basura.", InfoInventario[Bol][NombreObjeto]);
		rol_ame(playerid, string);
	} else return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
	return 1;
}