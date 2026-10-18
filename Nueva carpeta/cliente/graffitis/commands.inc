//Jugadores
cmd:graffiti(playerid)
{
	new faccion = member_faccion(playerid, 9);
	if (faccion == 0 && InfoPersonaje[playerid][pAccesoGraffiti] != 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes permisos suficientes para usar esta función.");
	if (no_tiene_manos(playerid, 36) == 0) return 1;
	new dialog[2048];
	strcat(dialog, "{F80101}INFORMACIÓN:\n");
	strcat(dialog, "{EBEBEB}Se utiliza una plantilla especial BBcode para el formato de mensajes usando un sistema (c).\n\n");
	strcat(dialog, "{EBEBEB}	(n) Para una nueva línea.\n");
	strcat(dialog, "{EBEBEB}	Colores: {0000FF}(a): Azul, {FFFFFF}(b): Blanco, {FFFF00}(am): Amarillo, {00C200}(v): Verde\n");
	strcat(dialog, "{EBEBEB}	{EBEBEB}(ne): Negro, {FFBF00}(na): Naranja, {FF0000}(r): Rojo, {00FFFF}(ce): Celeste\n\n");
	strcat(dialog, "{EBEBEB}[USO] Esto hará que (v){00C200}palabra{EBEBEB}(b) sea verde y el resto blanco.\n\n");
	strcat(dialog, "{EBEBEB}- Trate de que su texto no sea tan largo. El máximo es de 60 caracteres.\n");
	Dialog_Show(playerid, GraffitiPersonalizado, DIALOG_STYLE_INPUT, "Escribe lo que quieras", dialog, "Continuar", "Salir");
	return 1;
}


//Administrativos

cmd:dargraffiti(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dargraffiti (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador no está conectado.");
	if (InfoPersonaje[playerid2][pAccesoGraffiti])
	{
		InfoPersonaje[playerid2][pAccesoGraffiti] = 0;
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) ha removido permisos de /graffiti a %s(%d)", InfoCuenta[playerid][jNombre], playerid, NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s ha removido permisos de graffiti a %s.", InfoCuenta[playerid][jNombre], NombreOriginal(playerid2));
		Log("f_logs/DarGraffiti.log", string);
	}
	else
	{
		InfoPersonaje[playerid2][pAccesoGraffiti] = 1;
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) ha otorgado permisos de /graffiti a %s(%d)", InfoCuenta[playerid][jNombre], playerid, NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s ha otorgado permisos de graffiti a %s.", InfoCuenta[playerid][jNombre], NombreOriginal(playerid2));
		Log("f_logs/DarGraffiti.log", string);
	}
	guardar_int_mysql("personajes", "AccesoGraffiti", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pAccesoGraffiti]);
	return 1;
}

cmd:creargraffiti(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (InfoPersonaje[playerid][pEditingMode] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás editando un objeto.");
	new objeto = -1;
	Loop(a, MAX_GRAFFITIS, 1) if (InfoGraffiti[a][gr_PosX] == 0.0)
	{
		objeto = a;
		break;
	}
	if (objeto == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Se alcanzó el límite de graffitis. (Max: 50)");
	GetPlayerPos(playerid, InfoGraffiti[objeto][gr_PosX], InfoGraffiti[objeto][gr_PosY], InfoGraffiti[objeto][gr_PosZ]);
	InfoGraffiti[objeto][gr_Interior] = GetPlayerInterior(playerid);
	InfoGraffiti[objeto][gr_VirtualWorld] = GetPlayerVirtualWorld(playerid);
	InfoGraffiti[objeto][gr_Objeto] = CreateDynamicObject(18665, InfoGraffiti[objeto][gr_PosX], InfoGraffiti[objeto][gr_PosY], InfoGraffiti[objeto][gr_PosZ], 0.0, 0.0, 0.0, InfoGraffiti[objeto][gr_VirtualWorld], InfoGraffiti[objeto][gr_Interior], -1, 6000.0);
	EditDynamicObject(playerid, InfoGraffiti[objeto][gr_Objeto]);
	edicion_sql_actual[playerid] = objeto;
	InfoPersonaje[playerid][pEditingMode] = 13;
	SendPlayerChatMessage(playerid, -1, "Mantén presionado {589DA0}~k~~PED_SPRINT~{FFFFFF} para cambiar la posición de la cámara y editar mejor el graffiti.");
	return 1;
}

cmd:vergraffitis(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new pro[500], pro2[3024], tgraffitis = 0;
	//indice
	strcat(pro2, "(id) Mensaje\tCreador\tFecha\n");
	Loop(id, MAX_GRAFFITIS, 1) if (InfoGraffiti[id][gr_PosX])
	{
	    if (InfoGraffiti[id][gr_Fecha] == 0) format(pro, sizeof pro, "{EBEBEB}(%d) Sin pintar uwu\n", id);
		else format(pro, sizeof pro, "{EBEBEB}(%d) %.20s\t{F5DEB3}%s\t{00CC00}%s\n", id, InfoGraffiti[id][gr_Mensaje], InfoGraffiti[id][gr_Creador], Segundos_tiempo(gettime() - InfoGraffiti[id][gr_Fecha]));
		strcat(pro2, pro);
		format(pro, sizeof pro, "e_graffiti%d", tgraffitis);
		SetPVarInt(playerid, pro, id);
		tgraffitis++;
	}
	if (tgraffitis != 0) Dialog_Show(playerid, AdminGraffiti, DIALOG_STYLE_TABLIST_HEADERS, "Graffitis", pro2, "Continuar", "Salir");
	else Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Graffitis", "{EBEBEB}No hay ningún graffiti creados.", "Cerrar", "");
	SetPVarInt(playerid, "z_graffs", 1);
	return 1;
}
alias:vergraffitis("graffitis");