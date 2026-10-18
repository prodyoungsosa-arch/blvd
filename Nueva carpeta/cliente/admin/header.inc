// sistema administrativo
new AdminDuty[MAX_PLAYERS];
new AdminChat[MAX_PLAYERS];
new papilla[MAX_PLAYERS];

enum pSpec
{
	Float:Coords[3],
	Float:sPx,
	Float:sPy,
	Float:sPz,
	sPint,
	sLocal,
	sCam,
};
new Unspec[MAX_PLAYERS][pSpec];

AdminOnlineCheck()
{
	new count;
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		if (GetPlayerAdmin(playerid, 1) != 0)
		{
			count++;
		}
	}
	return count;
}

SendAdminMessage(color, const gformat[])
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		if (GetPlayerAdmin(playerid, 1) == 1 && AdminChat[playerid] == 0)
		{
			SendSplitMessage(playerid, color, gformat);
		}
	}
	return 1;
}

CheckAdminCMD(playerid, rango)
{
	if (!IsPlayerConnectedEx(playerid)) return 1;
	new gformat[190];
	if (GetPlayerAdmin(playerid, rango) == 0)
	{
		new name[39] = "Admin";
		switch (rango)
		{
			case 1: alm(name, "Support");
			case 2: alm(name, "Moderator");
			case 3: alm(name, "Administrator");
			case 4: alm(name, "Game Operator");
			case 10: alm(name, "Leadership");
		}
		format(gformat, sizeof gformat, "* Para hacer esto debes ser mínimo rango %s.", name);
		SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
		return 1;
	}
	return 0;
}

CheckAdminDuty(playerid)
{
	if (!IsPlayerConnectedEx(playerid)) return 1;
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "Altyn", true)) { return 0; }
	if (papilla[playerid] == 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Para hacer esto debes estar admin duty. (/onstaff)"); return 1; }
	return 0;
}

GetPlayerAdmin(playerid, nivel)
{
	if (!IsPlayerConnectedEx(playerid)) return 0;
	if (nivel == 10)
	{
		if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "Altyn", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true)) { return 1; }
	}
	else
	{
		if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "Altyn", true)  || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true)) { return 1; }
		if (InfoCuenta[playerid][jAdmin] >= nivel) return 1;
	}
	return 0;
}

GetAdminName(playerid)
{
	new name[39] = "Admin";
	if (!strcmp(InfoCuenta[playerid][jNombre], "Altyn", true))
	{
		alm(name, "Leadership");
		return name;
	}
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		alm(name, "Leadership");
		return name;
	}
	if (!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true))
	{
		alm(name, "Developer");
		return name;
	}
	switch (InfoCuenta[playerid][jAdmin])
	{
		case 1: alm(name, "Support");
		case 2: alm(name, "Moderator");
		case 3: alm(name, "Administrator");
		case 4: alm(name, "Game Operator");
	}
	return name;
}

SoloPropietarios(playerid){
	if(!strcmp(InfoCuenta[playerid][jNombre], "VanNet", true) || !strcmp(InfoCuenta[playerid][jNombre], "Altyn", true) || !strcmp(InfoCuenta[playerid][jNombre], "VanNet", true)) return 1;
	return 0;
}
