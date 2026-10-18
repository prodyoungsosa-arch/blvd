forward OnMembersAdmin(playerid);
public OnMembersAdmin(playerid)
{
	new members = 0, gformat[256], dialog[3072] = "Nombre\tRango\tEstado\tDuty\n";
	Loop(player, cache_num_rows(), 0)
	{
		new nombreapellido[32], rango, newid = -1, isname[32] = "Admin";
		rebel_string(player, "Nombre", nombreapellido, 32);
		rebel_int(player, "JotoOtaku", rango);
		//fix 22/04/2020
		foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoCuenta[juegador][jNombre], nombreapellido, true)) { newid = juegador; }
		//fix 22/04/2020
		//leer nombre rango
		if (!strcmp(nombreapellido, "sosaa", true)) { alm(isname, "Leadership"); }
		else if (!strcmp(nombreapellido, "sosaa", true)) { alm(isname, "Leadership"); }
		else if (!strcmp(nombreapellido, "Tulio", true)) { alm(isname, "Developer"); }
		else
		{
			switch (rango)
			{
				case 1: alm(isname, "Support");
				case 2: alm(isname, "Moderator");
				case 3: alm(isname, "Administrator");
				case 4: alm(isname, "Game Operator");
			}
		}
		//muestra
		if (IsPlayerConnectedEx(newid)) format(gformat, sizeof gformat, "%s\t%s (%d)\t{29B311}Conectado (ID %d)\t%s\n", nombreapellido, isname, rango, newid, (papilla[newid]) ? ("{55AD30}On-duty") : ("{F92B2B}Off-duty"));
		else format(gformat, sizeof gformat, "%s\t%s (%d)\t{E24D32}Desconectado\n", nombreapellido, isname, rango);
		strcat(dialog, gformat);
		format(gformat, sizeof gformat, "Miembro_List%d", members);
		SetPVarString(playerid, gformat, nombreapellido);
		members++;
	}
	if (members == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_LIST, "Administración", "{FFFFFF}No se encontraron miembros de la administración.", "Cerrar", "");
	if (GetPlayerAdmin(playerid, 4) != 0) Dialog_Show(playerid, MenuAdmins, DIALOG_STYLE_TABLIST_HEADERS, "Administración", dialog, "Continuar", "Salir");
	else Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, "Administración", dialog, "Cerrar", "");
	return 1;
}