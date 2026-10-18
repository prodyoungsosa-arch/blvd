Dialog:ShowFireFD(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new i = sel_incendio[playerid][listitem];
	new id = InfoIncendio[i][pI_propiedad];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El incendio ya fue controlado.");
	SetPVarInt(playerid, "EnCheckPoint", 1);
	if (InfoIncendio[i][pI_tipo] == 0) SetPlayerCheckpoint(playerid, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ], 6.0);
	else SetPlayerCheckpoint(playerid, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], 6.0);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "El incendio fue marcado en el radar.");
	return 1;
}

Dialog:ShowFireAdmin(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (DestroyFire(sel_incendio[playerid][listitem]))
	{
	    new string[190];
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) eliminó un incendio desde /aincendios.", InfoCuenta[playerid][jNombre], playerid);
		SendAdminMessage(0xFFFFFFFF, string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREEN, "Ese incendio ya fue apagado con éxito.");
	return 1;
}