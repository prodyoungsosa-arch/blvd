cmd:cpeaje(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (InfoPersonaje[playerid][pRango] < 5) return  SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser mínimo rango 5 para hacer esto.");
	new id = InfoPersonaje[playerid][pMiembro], info[512];
	if(cierre_p == 0)
	{
		format(info, sizeof(info), "** [%s] %s %s a cerrado todos los peajes.", InfoFaccion[id][fLogo], fac_rango[id][InfoPersonaje[playerid][pRango]-1], GetNameFormat(playerid));
		SendRadioMessage(1, 0xF07A7AFF, info, 1);
		SendRadioMessage(2, 0xF07A7AFF, info, 1);
		SendRadioMessage(3, 0xF07A7AFF, info, 1);
		SendRadioMessage(4, 0xF07A7AFF, info, 1);
		SendRadioMessage(5, 0xF07A7AFF, info, 1);
        cierre_p = 1;
        return 1;
	}
	if(cierre_p == 1)
	{
		format(info, sizeof(info), "** [%s] %s %s a abierto todos los peajes.", InfoFaccion[id][fLogo], fac_rango[id][InfoPersonaje[playerid][pRango]-1], GetNameFormat(playerid));
		SendRadioMessage(1, 0xF07A7AFF, info, 1);
		SendRadioMessage(2, 0xF07A7AFF, info, 1);
		SendRadioMessage(3, 0xF07A7AFF, info, 1);
		SendRadioMessage(4, 0xF07A7AFF, info, 1);
		SendRadioMessage(5, 0xF07A7AFF, info, 1);
        cierre_p = 0;
        return 1;
	}
	return 1;
}

cmd:peaje(playerid)
{
	estaen_peaje(playerid, 0, d_peaje);
	return 1;
}