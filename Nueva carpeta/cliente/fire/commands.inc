//Jugadores
cmd:incendios(playerid)
{
	if (!member_faccion(playerid, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de LSFD.");
	new IncendiosDialog[1028], TempConvert[128], ConteoFire = -1;
	Loop(id, totalincendios, 1) if (InfoIncendio[id][pI_propiedad] != -1)
	{
		if (ConteoFire != -1)
		{
			if (InfoIncendio[id][pI_tipo] == 0) format(TempConvert, sizeof TempConvert, "\r\nCasa #%d", InfoIncendio[id][pI_propiedad]);
			else format(TempConvert, sizeof TempConvert, "\r\nNegocio (%s)", InfoNegocio[InfoIncendio[id][pI_propiedad]][nNombre]);
		}
		else
		{
			if (InfoIncendio[id][pI_tipo] == 0) format(TempConvert, sizeof TempConvert, "Casa #%d", InfoIncendio[id][pI_propiedad]);
			else format(TempConvert, sizeof TempConvert, "Negocio (%s)", InfoNegocio[InfoIncendio[id][pI_propiedad]][nNombre]);
		}
		strcat(IncendiosDialog, TempConvert, sizeof IncendiosDialog);
		ConteoFire++;
		sel_incendio[playerid][ConteoFire] = id;
	}
	if (ConteoFire == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay ningún incendio existente.");
	Dialog_Show(playerid, ShowFireFD, DIALOG_STYLE_LIST, "Incendios activos", IncendiosDialog, "Localizar", "Cancelar");
	return 1;
}

cmd:molotov(playerid)
{
	if (InfoPersonaje[playerid][pHorasOn] < 15) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes jugar al menos 15 horas el servidor.");
	if (no_tiene_manos(playerid, 18) == 0) return 1;
	if (GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes crear incendios en interiores.");
	if (FuegoSiguiente() == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se pueden crear más incendios, se llegó al limite de 20.");
	if (InfoPersonaje[playerid][pTiempoMolotov] != 0)
	{
	    SendClientMessageEx(playerid, COLOR_GREY, "No puedes provocar incendios hasta dentro de %d minutos.", InfoPersonaje[playerid][pTiempoMolotov]);
	    return 1;
	}
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nTipo] != 0 && IsPlayerInRangeOfPoint(playerid, 7.0, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]))
	{
		SendClientMessageEx(playerid, 0x19AD7AC2, "Acabas de provocar un incendio en el negocio %s, alejate de la entrada!", InfoNegocio[id][nNombre]);
		SetTimerEx("ProvocarIncendio", 6000, false, "iii", playerid, 2, id);
		if (InfoPersonaje[playerid][pManoDerecha] == 18) InfoPersonaje[playerid][pManoDerechaCant]--;
		else InfoPersonaje[playerid][pManoIzquierdaCant]--;
		ActualizarManos(playerid);
		InfoPersonaje[playerid][pTiempoMolotov] = 120;
		guardar_int_mysql("personajes", "TiempoMolotov", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTiempoMolotov]);
		return 1;
	}
	Loop(id, totalcasas, 1) if (InfoCasa[id][cTipo] != 0 && IsPlayerInRangeOfPoint(playerid, 7.0, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]))
	{
		SendClientMessageEx(playerid, 0x19AD7AC2, "Acabas de provocar un incendio en la casa #%d, alejate de la entrada!", id);
		SetTimerEx("ProvocarIncendio", 6000, false, "iii", playerid, 1, id);
		if (InfoPersonaje[playerid][pManoDerecha] == 18) InfoPersonaje[playerid][pManoDerechaCant]--;
		else InfoPersonaje[playerid][pManoIzquierdaCant]--;
		ActualizarManos(playerid);
		InfoPersonaje[playerid][pTiempoMolotov] = 120;
		guardar_int_mysql("personajes", "TiempoMolotov", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTiempoMolotov]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en la entrada de ninguna casa o negocio.");
	return 1;
}

//Administrativos
cmd:crearincendio(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new tipo, id_propiedad, nextFire = FuegoSiguiente(), gformat[256];
	if (nextFire == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se pueden crear más incendios, se llegó al limite de 20.");
	if (sscanf(params, "dd", tipo, id_propiedad)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearincendio [tipo propiedad (0casa 1negocio)] [id propiedad]");
	if (tipo < 0 || tipo > 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo existen dos tipos (0 casa) (1 negocio)");
	if (tipo == 0)
	{
		if (id_propiedad < 1 || id_propiedad > totalcasas) return SendPlayerChatMessage(playerid, COLOR_GREY, "Casa no encontrada.");
		if (InfoCasa[id_propiedad][cTipo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa casa no existe.");
		format(gformat, sizeof gformat, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) creó un incendio en la casa %d.", InfoCuenta[playerid][jNombre], playerid, id_propiedad);
		SendAdminMessage(0xFFFFFFFF, gformat);
		CreateFireGeneral(id_propiedad, tipo, 0);
	}
	else if (tipo == 1)
	{
		if (id_propiedad < 1 || id_propiedad >= totalnegocios) return SendPlayerChatMessage(playerid, -1, "ID de negocio inválida.");
		if (InfoNegocio[id_propiedad][nTipo] == 0) return SendPlayerChatMessage(playerid, -1, "Esa ID está vacía.");
		format(gformat, sizeof gformat, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) creó un incendio en el negocio %d.", InfoCuenta[playerid][jNombre], playerid, id_propiedad);
		SendAdminMessage(0xFFFFFFFF, gformat);
		CreateFireGeneral(id_propiedad, tipo, 0);
	}
	return 1;
}

cmd:aincendios(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new IncendiosDialog[1028], TempConvert[128], ConteoFire = -1;
	Loop(id, totalincendios, 1) if (InfoIncendio[id][pI_propiedad] != -1)
	{
		if (ConteoFire != -1)
		{
			if (InfoIncendio[id][pI_tipo] == 0) format(TempConvert, sizeof TempConvert, "\r\nCasa #%d", InfoIncendio[id][pI_propiedad]);
			else format(TempConvert, sizeof TempConvert, "\r\nNegocio (%s)", InfoNegocio[InfoIncendio[id][pI_propiedad]][nNombre]);
		}
		else
		{
			if (InfoIncendio[id][pI_tipo] == 0) format(TempConvert, sizeof TempConvert, "Casa #%d", InfoIncendio[id][pI_propiedad]);
			else format(TempConvert, sizeof TempConvert, "Negocio (%s)", InfoNegocio[InfoIncendio[id][pI_propiedad]][nNombre]);
		}
		strcat(IncendiosDialog, TempConvert, sizeof IncendiosDialog);
		ConteoFire++;
		sel_incendio[playerid][ConteoFire] = id;
	}
	if (ConteoFire == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay ningún incendio existente.");
	Dialog_Show(playerid, ShowFireAdmin, DIALOG_STYLE_LIST, "Incendios activos", IncendiosDialog, "Apagar", "Cancelar");
	return 1;
}