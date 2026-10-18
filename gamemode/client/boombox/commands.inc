//Jugadores
cmd:equiposonido(playerid)
{
	if (InfoPersonaje[playerid][pSancionado] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar el equipo de sonido en prisión.");
 	if (InfoBoombox[playerid][BB_obj]) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Usa '/encender' para el menú del estéreo y '/rboombox' para recogerlo.");
	if (no_tiene_manos(playerid, 51) == 0) return 1;
	foreach(Player, i)
	{
		if (InfoBoombox[i][BB_obj])
		{
			if (IsPlayerInRangeOfPoint(playerid, 30.0, InfoBoombox[i][BB_x], InfoBoombox[i][BB_y], InfoBoombox[i][BB_z]))
			{
				SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes colocar tu boombox aquí, se encuentra uno cerca.");
				return 1;
			}
		}
	}
	if (InfoPersonaje[playerid][pManoDerecha] == 51)
	{
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid, 7);
	}
	else
	{
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid, 8);
	}
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 1, 1, 0, 0, 1);
	new Float:X, Float:Y, Float:Z, Float:A, string[128];
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, A);
	InfoBoombox[playerid][BB_obj] = CreateDynamicObject(2103, X, Y, Z-1, 0.0, 0.0, A, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));
	format(string, sizeof string, "Estéreo de %s", NombreOriginal(playerid));
	InfoBoombox[playerid][BB_label] = CreateDynamic3DTextLabel(string, COLOR_GREEN, X, Y, Z-0.45, 20.0, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));
	InfoBoombox[playerid][BB_area] = CreateDynamicSphere(X, Y, Z, 30.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	InfoBoombox[playerid][BB_x] = X;
	InfoBoombox[playerid][BB_y] = Y;
	InfoBoombox[playerid][BB_z] = Z;
	InfoBoombox[playerid][BB_int] = GetPlayerInterior(playerid);
	InfoBoombox[playerid][BB_vw] = GetPlayerVirtualWorld(playerid);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Estéreo plantado, usa '/encender' para abrir el menú de opciones.");
	Streamer_Update(playerid);
 	return 1;
}
alias:equiposonido("boombox", "esonido");

cmd:encender(playerid)

{
	if (!InfoBoombox[playerid][BB_obj]) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has colocado ningún boombox.");
	if (!IsPlayerInRangeOfPoint(playerid, 4.0, InfoBoombox[playerid][BB_x], InfoBoombox[playerid][BB_y], InfoBoombox[playerid][BB_z])) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca de tu boombox.");
	if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar agachado.");
	Dialog_Show(playerid, ShowBoombox, DIALOG_STYLE_LIST, "Boombox", "{F50000}Detener música{FFFFFF}\nRadios\nURL - Internet\n{00CC00}Recoger radio", "Continuar", "Salir");
	return 1;
}

cmd:requiposonido(playerid)
{
	if (!InfoBoombox[playerid][BB_obj]) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has colocado ningún boombox.");
	if (!IsPlayerInRangeOfPoint(playerid, 4.0, InfoBoombox[playerid][BB_x], InfoBoombox[playerid][BB_y], InfoBoombox[playerid][BB_z])) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca de tu boombox.");
	if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_DUCK) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes estar agachado.");
	if (DarObjeto(playerid, 51, 1) == 2) return 1;
	foreach(Player, i) if (IsPlayerInDynamicArea(i, InfoBoombox[playerid][BB_area]))
	{
		StopStream(i);
	}
	InfoBoombox[playerid][BB_area] = 0;
	if (IsValidDynamicObject(InfoBoombox[playerid][BB_obj])) DestroyDynamicObject(InfoBoombox[playerid][BB_obj]);
	InfoBoombox[playerid][BB_obj] = 0;
	if (IsValidDynamic3DTextLabel(InfoBoombox[playerid][BB_label]))
	{
		DestroyDynamic3DTextLabel(InfoBoombox[playerid][BB_label]);
		InfoBoombox[playerid][BB_label] = Text3D:INVALID_3DTEXT_ID;
	}
	InfoBoombox[playerid][BB_x] = 0.0;
	InfoBoombox[playerid][BB_y] = 0.0;
	InfoBoombox[playerid][BB_z] = 0.0;
	InfoBoombox[playerid][BB_int] = 0;
	InfoBoombox[playerid][BB_vw] = 0;
	DeletePVar(playerid, "BBStation");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Recogiste tu boombox.");
	return 1;
}
alias:requiposonido("requipo", "rboombox");