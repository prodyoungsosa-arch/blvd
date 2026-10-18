new PlayerPermisos[MAX_PLAYERS];

cmd:verpermisos(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20];
    if (sscanf(params, "s[19]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /verpermisos #codigo");
    new targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    Dialog_Show(playerid, ShowAdminPermisos, DIALOG_STYLE_LIST, "Permisos otorgados", "Casas\nNegocios\nVehículos", "Continuar", "Salir");
    PlayerPermisos[playerid] = targetid;
    return 1;
}

/* Mercados Negros */
new
	BM_CAR_WASH_OPEN = true,
	BM_CAMPO_OPEN = false,
	BM_AMMUNATION_OPEN = false,
    doorAmmu
;

cmd:blackmarkets(playerid)
{
    if (CheckAdminCMD(playerid, 5)) return 1;
    BM_CAR_WASH_OPEN = true,
    BM_CAMPO_OPEN = true,
    BM_AMMUNATION_OPEN = true;
    if (BM_AMMUNATION_OPEN)
        MoveDynamicObject(doorAmmu, 252.6878, -154.9085, -36.8164, 0.5);

    else
        MoveDynamicObject(doorAmmu, 252.6878, -154.9085, -40.2164, 0.5);

    return SendPlayerChatMessage(playerid, COLOR_WHITE, "All black markets open");
}

cmd:sorteo(playerid, params[])
{
	if (CheckAdminCMD(playerid, 5)) return 1;
	new maxjugadores;
	if (sscanf(params, "d", maxjugadores)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sorteo (MaxPlayers)");
	new pay = Random(0, maxjugadores);
	if (IsPlayerConnectedEx(pay))
	{
		Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
		{
		    SendClientMessageEx(playerid2, 0xFF0080FF, "Número ganador %s (%d), felicidades!", InfoPersonaje[pay][pNombre_Apellido], pay);
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "El ganador era ID %d, no figura conectado.", pay);
	}
	return 1;
}

cmd:quitarvida(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20], hpset, string[180];
    if (sscanf(params, "s[19]d", codigo, hpset)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darvida #codigo (HP)");
    new targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    if (hpset < 0 || hpset > 100) return SendPlayerChatMessage(playerid, COLOR_GREY, "El mínimo de vida es 0 y el máximo 100.");
    quitar_vida(targetid, -hpset);
    format(string, sizeof string, "{FF2F2F}Administración:{FFFFFF} %s(%d) Le quito salud a %s(%d), %dHP.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid, hpset);
    SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

cmd:revivir(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new string[170], codigo[20];
    if (sscanf(params, "s[19]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /revivir #codigo");
    new targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    if (GetPVarInt(targetid, "EstaCrack") == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Usuario no herido.");
    SendPlayerChatMessage(targetid, COLOR_WHITE, "Un miembro de la administración te revivió.");
    format(string, sizeof string, "{FF2F2F}Administración:{FFFFFF} %s(%d) ha revivido a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
    SendAdminMessage(0xFFFFFFFF, string);
    KillEMSQueue(targetid);
    ClearAnimations(targetid);
    ResetPlayerHeridas(targetid);
    dar_vida(targetid, 100);
    timer_herido[targetid] = 0;
    InfoPersonaje[targetid][pMuerto] = 0;
    YaAviso[targetid] = 0;
    pDroga[targetid][Sobredosis] = 0;
    guardar_int_mysql("personajes", "Muerto", InfoPersonaje[targetid][pID], 0);
    guardar_int_mysql("personajes", "Sobredosis", InfoPersonaje[targetid][pID], 0);
    return 1;
}

cmd:darvida(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20], hpset, string[180];
    if (sscanf(params, "s[19]d", codigo, hpset)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darvida #codigo (HP)");
    new targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    if (hpset < 0 || hpset > 100) return SendPlayerChatMessage(playerid, COLOR_GREY, "El mínimo de vida es 0 y el máximo 100.");
    dar_vida(targetid, hpset);
    format(string, sizeof string, "{FF2F2F}Administración:{FFFFFF} %s(%d) estableció la salud de %s(%d) a %dHP.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid, hpset);
    SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

cmd:verip(playerid, params[])
{
    if (CheckAdminCMD(playerid, 3)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20], ip[18];
    if (sscanf(params, "s[19]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /verip #codigo");
    new targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    if (CheckAdminCMD(playerid, InfoCuenta[targetid][jAdmin])) return 1;
    if (InfoCuenta[playerid][jAdmin] < InfoCuenta[targetid][jAdmin]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes ver la IP de un staff superior.");
    GetPlayerIp(targetid, ip, sizeof ip);
    SendClientMessageEx(playerid, COLOR_PURPLE, "%s [ID: %d] (Cuenta: %s [%d]) - IP: %s.", InfoPersonaje[targetid][pNombre_Apellido], targetid, InfoCuenta[targetid][jNombre], InfoCuenta[targetid][jID], ip);
    return 1;
}

cmd:ip(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ip (ip)");
	if (IsValidIP(params)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa IP no es válida, intenta de nuevo.");
	new string[170], IP[32];
	foreach(Player, i)
	{
		GetPlayerIp(i, IP, sizeof IP);
		if (strfind(IP, params, true) != -1)
		{
			format(string, sizeof string, "%s(%s) [ID: %d] (Cuenta: %s [%d]) - IP: %s.", InfoPersonaje[i][pNombre_Apellido], InfoPersonaje[i][pCodigo], i, InfoCuenta[i][jNombre], InfoCuenta[i][jID], IP);
			SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		}
	}
	return 1;
}

cmd:bloquearip(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (!CheckTimer(60, TimerCban[playerid]))
	{
		new ip[18], reason[64], string[190];
		if (sscanf(params, "s[18]s[64]", ip, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bloquearip (IP) (Razón)");
		if (IsValidIP(ip)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa IP no es válida, intenta de nuevo.");
		if (CheckBan(ip) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Esa IP ya se encuentra bloqueda.");
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) bloqueó la IP %s. Razón: %s", InfoCuenta[playerid][jNombre], playerid, ip, reason);
		SendAdminMessage(0xFFFFFFFF, string);
		//register ban ip
		AddBan(ip, InfoCuenta[playerid][jNombre], reason);
		//seguridad 24/02/2020
		CountBan[playerid]++;
		if (CountBan[playerid] == 5)
		{
			TimerCban[playerid] = gettime();
			CountBan[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, TimerCban[playerid]) ));
	}
	return 1;
}

IsValidChangeName(const name[])
{
	if (!name[0] || strfind(name, "_") == -1)
	    return 0;

	else for (new i = 0, len = strlen(name); i != len; i ++) {
	    if ((i == 0) && (name[i] < 'A' || name[i] > 'Z'))
	        return 0;

		else if ((i != 0 && i < len  && name[i] == '_') && (name[i + 1] < 'A' || name[i + 1] > 'Z'))
		    return 0;

		else if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != '.')
		    return 0;
	}
	return 1;
}

cmd:changename(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new nombre_viejo[MAX_PLAYER_NAME], nombre_nuevo[MAX_PLAYER_NAME], edad, gformat[256];
	if (sscanf(params, "s[24]s[24]d", nombre_viejo, nombre_nuevo, edad)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /changename [Nombre_Apellido (viejo)] [Nombre_Apellido (nuevo)] [edad]");
	if (!IsValidChangeName(nombre_viejo)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El Nombre_Apellido viejo, no sigue el formato correcto.");
	if (!IsValidChangeName(nombre_nuevo)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El Nombre_Apellido nuevo, no sigue el formato correcto.");
	if (VerificarPersonaje(nombre_viejo))
	{
	    new personajeID = -1, dni;
		rebel_int(0, "ID", personajeID);
		rebel_int(0, "Documento", dni);
		cache_unset_active();
		if (VerificarPersonaje(nombre_nuevo) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "El Nombre_Apellido nuevo, está existente.");
		Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2) && strcmp(InfoPersonaje[playerid2][pNombre_Apellido], nombre_viejo, true) == 0)
		{
			format(gformat, sizeof gformat, "El personaje que quieres cambiarle el nombre, está conectado (ID %d).", playerid2);
			SendPlayerChatMessage(playerid, COLOR_GREEN, gformat);
			return 1;
		}
		new vcount = 0, hcount = 0, ncount = 0;
		//renover cuenta
		guardar_string_mysql("personajes", "Nombre_Apellido", personajeID, nombre_nuevo);
		guardar_int_mysql("personajes", "Edad", personajeID, edad);
		//limpiar antecedentes
		guardar_int_mysql("personajes", "Arrestos", personajeID, 0);
		new nant = GetAntecedentes(dni);
		if (nant > 0)
		{
			new Cache:result;
			new query[250];
			mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE Documento = '%d'", dni);
			result = mysql_query(db_samp, query);
			Loop(e, cache_num_rows(), 0)
			{
				new registro;
				rebel_int(e, "ID", registro);
				new slas[10] = "none", query2[350];
				mysql_format(db_samp, query2, sizeof query2, "UPDATE antecedentes SET Documento = 0, Faccion = '%e', Responsable = '%e', Detalles = '%e', Fecha = '%e' WHERE ID = '%d'", slas, slas, slas, slas, e);
				mysql_tquery(db_samp, query2);
			}
			cache_delete(result);
		}
		//vehs
	 	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vModelo] != 0 && strcmp(nombre_viejo, InfoVehiculo[id][vPropietario], true) == 0)
		{
			vcount++;
			alm(InfoVehiculo[id][vPropietario], nombre_nuevo);
			guardar_string_mysql("vehiculos", "Propietario", InfoVehiculo[id][vID_sql], nombre_nuevo);
 		}
		//casas
	 	Loop(id, totalcasas, 1) if (InfoCasa[id][cTipo] != 0 && strcmp(nombre_viejo, InfoCasa[id][cPropietario], true) == 0)
		{
			hcount++;
			alm(InfoCasa[id][cPropietario], nombre_nuevo);
			guardar_string_mysql("casas", "Propietario", InfoCasa[id][cID_sql], nombre_nuevo);
			LabelPickup_casa(id);
 		}
		//negocios
	 	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nTipo] != 0 && strcmp(nombre_viejo, InfoNegocio[id][nPropietario], true) == 0)
		{
			ncount++;
			alm(InfoNegocio[id][nPropietario], nombre_nuevo);
			guardar_string_mysql("negocios", "Propietario", InfoNegocio[id][nID_sql], nombre_nuevo);
			Labelupdate_negocio(id);
 		}
		//fin
		SendClientMessageEx(playerid, COLOR_YELLOW, "Realizaste con éxito el cambio de nombre SQL %d (%s) antiguo: %s.", personajeID, nombre_nuevo, nombre_viejo);
		SendClientMessageEx(playerid, COLOR_YELLOW, "Se actualizaron las propiedades (casas %d) (vehs %d) (negocios %d)", hcount, vcount, ncount);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "El Nombre_Apellido viejo, no existe.");
	return 1;
}

cmd:togadmin(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (!AdminChat[playerid])
	{
		AdminChat[playerid] = 1;
		ShowTDN(playerid, "Canal de administración desactivado.");
	}
	else
	{
		AdminChat[playerid] = 0;
		ShowTDN(playerid, "Canal de administración activado.");
	}
	return 1;
}
alias:togadmin("togac");

cmd:listaadmins(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	mysql_tquery(db_samp, "SELECT * FROM cuentas WHERE JotoOtaku != 0", "OnMembersAdmin", "d", playerid);
	return 1;
}
alias:listaadmins("listaadmin", "administracion");

cmd:adminduty(playerid)
{
	new string[256];
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (InfoPersonaje[playerid][pSancionado] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes colocarte duty mientras estás en prisión.");
	if (papilla[playerid] == 0)
	{
		papilla[playerid] = 1;
		AdminDuty[playerid] = 1;
		InfoPersonaje[playerid][pTogTelefono] = 0;
		format(string, sizeof string, "%s {eb4040}%s(%d){FFFFFF} ahora está On-Duty.", GetAdminName(playerid), InfoCuenta[playerid][jNombre], playerid);
	}
	else
	{
		InfoPersonaje[playerid][pTogTelefono] = 1;
		papilla[playerid]= 0;
		AdminDuty[playerid] = 0;
		format(string, sizeof string, "%s {eb4040}%s(%d){FFFFFF} ahora está Off-Duty.", GetAdminName(playerid), InfoCuenta[playerid][jNombre], playerid);
	}
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}
alias:adminduty("aduty", "staffon", "onstaff");

/*cmd:jetpack(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20], gformat[160];
    if (sscanf(params, "s[19]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /jetpack #codigo");

    new targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_USEJETPACK);
    JetPack[targetid] = 1;
    format(gformat, sizeof gformat, "Le has dado un jetpack a %s.", GetNameFormat(targetid));
    SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
    return 1;
}*/
cmd:jetpack(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[20], gformat[160], targetid;
    if (sscanf(params, "s[19]", codigo)) 
    { targetid = playerid; }
    else
    {
        targetid = GetPlayerByCodigo(codigo);
        if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    }
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_USEJETPACK);
    JetPack[targetid] = 1;
    if (targetid == playerid) { SendPlayerChatMessage(playerid, COLOR_WHITE, "Te has dado un jetpack."); }
    else 
    {
        format(gformat, sizeof gformat, "Le has dado un jetpack a %s.", GetNameFormat(targetid));
        SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
    }
    return 1;
}

cmd:desbanip(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /desbanip (IP)");
	if (IsValidIP(params)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa IP no es válida, intenta de nuevo.");
    if (CheckBan(params))
    {
		new query2[160];
		new Cache:result;
		mysql_format(db_samp, query2, sizeof query2, "SELECT * FROM ips WHERE IP = '%e'", params);
		result = mysql_query(db_samp, query2);

		new id, admin[24], razon[256], none[6] = "none";
		rebel_int(0, "ID", id);
		rebel_string(0, "Admin", admin, 24);
		rebel_string(0, "Razon", razon, 256);
		new query[350];
		mysql_format(db_samp, query, sizeof query, "UPDATE ips SET IP = '%e', Admin = '%e', Fecha = '%e', Razon = '%e' WHERE ID = '%d'", none, none, none, none, id);
		mysql_tquery(db_samp, query);
		new string[256];
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) desbloqueo la IP %s (admin bloq: %s)", InfoCuenta[playerid][jNombre], playerid, params, admin);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s desbloqueo la IP %s que bloqueó %s por %s.", InfoCuenta[playerid][jNombre], params, admin, razon);
		Log("f_logs/desbanip.log", string);
		cache_delete(result);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa IP no se encuentra bloqueada.");
	return 1;
}
alias:desbanip("desbanearip", "desbloquearip");

cmd:desbanpj(playerid, params[])
{
    if (CheckAdminCMD(playerid, 2)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /desbanpj (Nombre_Apellido o #Codigo)");
    new query[512];
    new codigo_limpio[17];
    new real_name[MAX_PLAYER_NAME]; 
    new string[512], banex = 0;
    new param_for_code_search[128]; 
    new bool:tiene_hash = (params[0] == '#');
    strmid(param_for_code_search, params, 0, sizeof(param_for_code_search)); 
    if (tiene_hash)
    {
        strmid(codigo_limpio, params, 1, sizeof(codigo_limpio) - 1);
        strmid(param_for_code_search, codigo_limpio, 0, sizeof(param_for_code_search));
    }
    mysql_format(db_samp, query, sizeof query, "SELECT Nombre_Apellido FROM personajes WHERE Nombre_Apellido = '%e' OR Codigo = '%e' LIMIT 1",  params, param_for_code_search);
    new Cache:result = mysql_query(db_samp, query);
    if (cache_num_rows() == 0) 
    {
        cache_delete(result);
        return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese personaje o código no existe en la base de datos.");
    }
    cache_get_value(0, "Nombre_Apellido", real_name, sizeof(real_name));
    cache_delete(result); 
    mysql_format(db_samp, query, sizeof query,  "SELECT OtakuN_N FROM personajes WHERE Nombre_Apellido = '%e' LIMIT 1", real_name);
    new Cache:result_ban = mysql_query(db_samp, query);
    if (cache_num_rows() > 0)
    {
        cache_get_value_int(0, "OtakuN_N", banex);
    }
    cache_delete(result_ban);
    if (banex == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese personaje no está bloqueado.");
    mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET OtakuN_N = 0 WHERE Nombre_Apellido = '%e'", real_name);
    mysql_tquery(db_samp, string);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) desbloqueó el personaje %s.", InfoCuenta[playerid][jNombre], playerid, real_name);
    SendAdminMessage(0xFFFFFFFF, string);
    format(string, sizeof string, "%s desbaneo el personaje %s.", InfoCuenta[playerid][jNombre], real_name);
    Log("f_logs/desban.log", string);
    return 1;
}

alias:desbanpj("desbloquearpj", "desbanearpj");

cmd:desbancuenta(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /desbancuenta (Nombre de usuario)");
	if (VerificarCuenta(params))
	{
		new string[512], banex;
		rebel_int(0, "OtakuN_N", banex);
		if (banex == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa cuenta no está baneada.");
		mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET OtakuN_N = 0 WHERE Nombre = '%e'", params);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) desbaneó la cuenta %s.", InfoCuenta[playerid][jNombre], playerid, params);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s desbaneo la cuenta %s.", InfoCuenta[playerid][jNombre], params);
		Log("f_logs/desban.log", string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta no existe.");
	return 1;
}
alias:desbancuenta("desbloquearcuenta", "desbanearcuenta");

cmd:obanearpj(playerid, params[])
{
    if (CheckAdminCMD(playerid, 2)) return 1;
    new playername_input[25], reason[64]; 
    new query[512];
    new real_name[MAX_PLAYER_NAME]; 
    new string[1028], banex = 0;
    if (sscanf(params, "s[24]s[64]", playername_input, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /obanearpj (Nombre_Apellido o #Codigo) (Razón)");
    new codigo_limpio[sizeof(playername_input)]; 
    new param_for_code_search[sizeof(playername_input)]; 
    new bool:tiene_hash = (playername_input[0] == '#');
    strmid(param_for_code_search, playername_input, 0, sizeof(param_for_code_search)); 
    if (tiene_hash)
    {
        strmid(codigo_limpio, playername_input, 1, sizeof(codigo_limpio) - 1);
        strmid(param_for_code_search, codigo_limpio, 0, sizeof(param_for_code_search));
    }
    mysql_format(db_samp, query, sizeof query, "SELECT Nombre_Apellido FROM personajes WHERE Nombre_Apellido = '%e' OR Codigo = '%e' LIMIT 1", playername_input, param_for_code_search);
    new Cache:result_find = mysql_query(db_samp, query);
    if (cache_num_rows() == 0) 
    {
        cache_delete(result_find);
        return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese personaje o código no existe.");
    }
    cache_get_value(0, "Nombre_Apellido", real_name, sizeof(real_name));
    cache_delete(result_find); 
    mysql_format(db_samp, query, sizeof query, "SELECT OtakuN_N FROM personajes WHERE Nombre_Apellido = '%e' LIMIT 1", real_name);
    new Cache:result_ban = mysql_query(db_samp, query);
    if (cache_num_rows() > 0)
    {
        cache_get_value_int(0, "OtakuN_N", banex);
    }
    cache_delete(result_ban);
    if (banex != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese personaje ya está bloqueado.");
    mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE Nombre_Apellido = '%e'", GetNameFormat(playerid), reason, FechaHoy(), real_name);
    mysql_tquery(db_samp, string);
    format(string, sizeof string, "%s bloqueó el personaje %s, razón: %s", InfoCuenta[playerid][jNombre], real_name, reason);
    Log("f_logs/offban.log", string);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) bloqueó el personaje %s, razón: %s (OFFLINE)", InfoCuenta[playerid][jNombre], playerid, real_name, reason);
    SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

alias:obanearpj("obloquearpj");

cmd:limpiarreportes(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	new string[128];
	ClearReports();
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha limpiado todos los reportes activos.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:reportes(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[320];
	SendPlayerChatMessage(playerid, COLOR_GREEN, "REPORTES:");
	Loop(id, MAX_REPORTS, 0) if (Reports[id][BeingUsed] == 1)
	{
		new playerid2 = Reports[id][ReportFrom];
		format(string, sizeof string, "[{FF9B6A}%s(ID: %d) | RID: %d{FFFFFF}] %s", GetNameFormat(playerid2), playerid2, id, Reports[id][Report]);
		SendSplitMessage(playerid, 0xFFFFFFFF, string);
	}
	return 1;
}

cmd:ar(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[180], reportid;
	if (sscanf(params, "d", reportid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ar (Reporte ID)");
	if (reportid < 0 || reportid > 50) { SendPlayerChatMessage(playerid, COLOR_GREY, "ID del reporte no debe ser menor de 0 ni mayor de 50."); return 1; }
	if (Reports[reportid][BeingUsed] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese RID ya fue atendido.");
	if (!IsPlayerConnectedEx(Reports[reportid][ReportFrom]))
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "El que reportó se ha desconectado.");
		Reports[reportid][ReportFrom] = 999;
		Reports[reportid][BeingUsed] = 0;
		return 1;
	}
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) aceptó el reporte de %s (ID: %i, RID: %i).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(Reports[reportid][ReportFrom]),Reports[reportid][ReportFrom],reportid);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s ha aceptado tu reporte, Puedes usar {A2DC35}/reply{FFFFFF} para explicar tu reporte. [T: 60 Seg.]", InfoCuenta[playerid][jNombre]);
	SendPlayerChatMessage(Reports[reportid][ReportFrom], COLOR_WHITE, string);
	Reports[reportid][ReplyTimerr] = SetTimerEx("ReplyTimer", 60000, 0, "d", reportid);
	Reports[reportid][CheckingReport] = playerid;
	Reports[reportid][BeingUsed] = 0;
	Reports[reportid][TimeToExpire] = 0;
	alm(Reports[reportid][Report], "None");
	return 1;
}

cmd:rr(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[180], reportid;
	if (sscanf(params, "d", reportid)) return SendPlayerChatMessage(playerid, COLOR_WHITE,"USE: /rr [Report ID]");
	if (reportid < 0 || reportid > 499) { SendPlayerChatMessage(playerid, COLOR_WHITE, "ID del reporte no debe ser menor de 0 ni mayor de 499!"); return 1; }
	if (Reports[reportid][BeingUsed] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese RID ya fue atendido!");
	if (!IsPlayerConnectedEx(Reports[reportid][ReportFrom]))
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "El que reportó se ha desconectado !");
		Reports[reportid][ReportFrom] = 999;
		Reports[reportid][BeingUsed] = 0;
		return 1;
	}
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) rechazó el reporte de %s.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(Reports[reportid][ReportFrom]));
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s marcó tu reporte como invalido. Usa y lee muy bien {FF0000}/retips{FFFFFF} antes de reportar.", InfoCuenta[playerid][jNombre]);
	SendPlayerChatMessage(Reports[reportid][ReportFrom], COLOR_WHITE, string);
	Reports[reportid][ReportFrom] = 999;
	Reports[reportid][BeingUsed] = 0;
	Reports[reportid][TimeToExpire] = 0;
	alm(Reports[reportid][Report], "None");
	return 1;
}

cmd:verwalkie(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (See_FRC[playerid] == 1)
	{
		See_FRC[playerid] = 0;
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Notificación del uso de la radio portátil entre usuarios desactivada.");
	}
	else
	{
		See_FRC[playerid] = 1;
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Notificación del uso de la radio portátil entre usuarios activada.");
	}
	return 1;
}

cmd:darchaleco(playerid, params[])
{
    if (CheckAdminCMD(playerid, 2)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], hpset, string[180];
    if (sscanf(params, "s[24]d", codigo, hpset)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darchaleco (#Codigo) (Chaleco)");
    new targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    if (hpset < 0 || hpset > 100) return SendPlayerChatMessage(playerid, COLOR_GREY, "El mínimo de chaleco es 0 y el máximo 100.");
    dar_chaleco(targetid, hpset);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) estableció el chaleco de %s(%d) a %d.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid, hpset);
    SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

cmd:darstat(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    new codigo[25];
    new stat_num, stat_value;
    new targetid = -1;
    new string[170];
    if (sscanf(params, "s[24]dd", codigo, stat_num, stat_value))
    {
        SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darstat (#Código) (Número) (Valor)");
        SendPlayerChatMessage(playerid, COLOR_GRAD1, "1 Banco$ | 2 Sexo | 3 Número teléfono | 4 Estilo de pelea");
        SendPlayerChatMessage(playerid, COLOR_GRAD1, "5 Edad | 6 Horas jugando | 7 Jails ooc");
        return 1;
    }
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    switch (stat_num)
    {
        case 1:
        {
            InfoPersonaje[targetid][pBanco] = stat_value;
            format(string, sizeof string, "Cuenta bancaria: $%d", stat_value);
            guardar_int_mysql("personajes", "BanescoOwO", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pBanco]);
        }
        case 2:
        {
            InfoPersonaje[targetid][pSexo] = stat_value;
            format(string, sizeof string, "Sexo: %d", stat_value);
            guardar_int_mysql("personajes", "Sexo", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pSexo]);
        }
        case 3:
        {
            InfoPersonaje[targetid][pTelefono] = stat_value;
            format(string, sizeof string, "Teléfono: #%d", stat_value);
            guardar_int_mysql("personajes", "Telefono", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pTelefono]);
        }
        case 4:
        {
            InfoPersonaje[targetid][pEstiloPelea] = stat_value;
            format(string, sizeof string, "Tipo Lucha: %d", stat_value);
            guardar_int_mysql("personajes", "EstiloPelea", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pEstiloPelea]);
        }
        case 5:
        {
            InfoPersonaje[targetid][pEdad] = stat_value;
            format(string, sizeof string, "Edad: %d", stat_value);
            guardar_int_mysql("personajes", "Edad", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pEdad]);
        }
        case 6:
        {
            InfoPersonaje[targetid][pHorasOn] = stat_value;
            format(string, sizeof string, "Horas jugando: %d", stat_value);
            guardar_int_mysql("personajes", "FugaoVicio", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pHorasOn]);
            SetPlayerScore(targetid, InfoPersonaje[targetid][pHorasOn]);
        }
        case 7:
        {
            InfoPersonaje[targetid][pJails] = stat_value;
            format(string, sizeof string, "Jails: %d", stat_value);
            guardar_int_mysql("personajes", "Jails", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pJails]);
        }
        default: return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código de estadística inválido!");
    }
    
    SendPlayerChatMessage(playerid, COLOR_GRAD2, string);
    SendPlayerChatMessage(playerid, COLOR_WHITE, "Estadística actualizada para el personaje.");
    
    return 1;
}

cmd:verstat(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25];
    new targetid = -1;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vercuenta (#Código)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador desconectado.");
    Show_cuenta(playerid, targetid);
    return 1;
}

alias:verstat("vercuenta", "check", "verstats");

cmd:cambiarint(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25];
    new interior_id;
    new targetid = -1;
    new string[195];
    if (sscanf(params, "s[24]d", codigo, interior_id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /cambiarint (#Código) (Interior)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    SetPlayerInterior(targetid, interior_id);
    format(string, sizeof string, "Cambiaste el interior (%d) de %s.", interior_id, GetNameFormat(targetid));
    SendPlayerChatMessage(playerid, COLOR_GRAD1, string);
    format(string, sizeof string, "%s te cambio el interior (%d).", GetNameFormat(playerid), interior_id);
    SendPlayerChatMessage(targetid, COLOR_GRAD1, string);
    return 1;
}
alias:cambiarint("editarint", "changeint");

cmd:cambiarvw(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], virtual_world_id, targetid = -1, string[195];
    if (sscanf(params, "s[24]d", codigo, virtual_world_id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /cambiarvw (#Código) (VirtualWorld)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    SetPlayerVirtualWorld(targetid, virtual_world_id);
    format(string, sizeof string, "Cambiaste el virtualworld (%d) de %s.", virtual_world_id, GetNameFormat(targetid));
    SendPlayerChatMessage(playerid, COLOR_GRAD1, string);
    format(string, sizeof string, "%s te cambio el virtualworld (%d).", GetNameFormat(playerid), virtual_world_id);
    SendPlayerChatMessage(targetid, COLOR_GRAD1, string);
    return 1;
}

alias:cambiarvw("editarvw", "changevw");

cmd:autovw(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170];
	if (sscanf(params, "dd", params[0],params[1])) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /autovw (VehicleID) (VirtualWorld)");
	if (!GetVehicleModel(params[0])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo inválido, intenta con otra ID.");
	SetVehicleExVirtualWorld(params[0], params[1]);
	format(string, sizeof string, "VirtualWorld del vehículo %d, ahora es %d.", params[0], params[1]);
	SendPlayerChatMessage(playerid, COLOR_GRAD1, string);
	return 1;
}
alias:autovw("vehvw");

cmd:autoint(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170];
	if (sscanf(params, "dd", params[0],params[1])) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /autoint (VehicleID) (Interior)");
	if (!GetVehicleModel(params[0])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo inválido, intenta con otra ID.");
	SetVehicleInterior(params[0], params[1]);
	format(string, sizeof string, "Interior del vehículo %d, ahora es %d.", params[0], params[1]);
	SendPlayerChatMessage(playerid, COLOR_GRAD1, string);
	return 1;
}
alias:autoint("vehint");

cmd:a(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /a (Texto)");
	new string[256];
	format(string, sizeof(string), "{00AE57}** %s %s:{ffffff} %s", GetAdminName(playerid), InfoCuenta[playerid][jNombre], params);
	SendAdminMessage(0xEBEBEBFF, string);
	return 1;
}

cmd:ir(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], gformat[160], targetid = -1;
    new Float:p_x, Float:p_y, Float:p_z;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ir (#Código)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    GetPlayerPos(targetid, p_x, p_y, p_z);
    new interior = GetPlayerInterior(targetid);
    new vw = GetPlayerVirtualWorld(targetid);
    SetPosEx(playerid, p_x, p_y, p_z, 0, interior, vw, 1);
    format(gformat, sizeof gformat, "Fuiste hasta la posición de %s.", GetNameFormat(targetid));
    SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
    return 1;
}
alias:ir("gotoplayer", "irjugador", "irplayer");

cmd:limpiarchat(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	CleanScreen();
	new string[170];
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) limpió el chat completo.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:leetodo(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (!BigEar[playerid])
	{
		BigEar[playerid] = 1;
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Chat global activado.");
	}
	else
	{
		BigEar[playerid] = 0;
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Chat global desactivado.");
	}
	return 1;
}

cmd:traer(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], gformat[160], targetid = -1;
    new Float:p_x, Float:p_y, Float:p_z;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /traer (#Código)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    if (GetPlayerAdmin(targetid, 10) != 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes hacer esto con propietarios o programadores.");
    GetPlayerPos(playerid, p_x, p_y, p_z);
    new interior = GetPlayerInterior(playerid);
    new vw = GetPlayerVirtualWorld(playerid);
    SetPosEx(targetid, p_x, p_y, p_z, 0, interior, vw, 1);
    format(gformat, sizeof gformat, "Llevaste hasta tu posición a %s.", GetNameFormat(targetid));
    SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
    return 1;
}

cmd:slap(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], altura, targetid = -1, string[128];
    new Float:slx, Float:sly, Float:slz;
    if (sscanf(params, "s[24]d", codigo, altura)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /slap (#Código) (Altura)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    GetPlayerPos(targetid, slx, sly, slz);
    SetPlayerPosEx(targetid, slx, sly, slz + altura);
    PlayerPlaySound(targetid, 1130, slx, sly, slz + altura);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) golpeó a %s(%d). Altura: %d", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid, altura);
    SendAdminMessage(0xFFFFFFFF, string);
    format(string, sizeof string, "%s(%d) te golpeó a una altura: %d", InfoCuenta[playerid][jNombre], playerid, altura);
    SendPlayerChatMessage(targetid, COLOR_YELLOW, string);
    return 1;
}

cmd:vehslap(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new alt, vehiculo, Float:slx, Float:sly, Float:slz, string[128];
	if (sscanf(params, "dd", vehiculo, alt)) SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vehslap (vehicleID) (Altitud)");
	if (!GetVehicleModel(vehiculo)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El vehículo introducido no existe, verifica en /dl.");
	GetVehiclePos(vehiculo, slx, sly, slz);
	MoverVehiclePos(vehiculo, slx, sly, slz+alt);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) golpeó el vehiculo id %d.", InfoCuenta[playerid][jNombre], playerid, vehiculo);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:irpunto(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (GetPlayerState(playerid) == 2) MoverVehiclePos(GetPlayerVehicleID(playerid), TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2]);
	else SetPosEx(playerid, TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2], 0.0000, 0, 0, 1);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Teleportado.");
	return 1;
}

cmd:punto(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	GetPlayerPos(playerid, TeleportDest[playerid][0],TeleportDest[playerid][1],TeleportDest[playerid][2]);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Posición guardada.");
	return 1;
}


cmd:traerauto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new Float:plocx, Float:plocy, Float:plocz, vehicleid;
	if (sscanf(params, "i", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /traerauto (Auto ID)");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El vehículo introducido no existe, verifica en /dl.");
	GetPlayerPos(playerid, plocx, plocy, plocz);
	SetVehicleInterior(vehicleid, GetPlayerInterior(playerid));
	SetVehicleExVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	MoverVehiclePos(vehicleid, plocx, plocy+4, plocz);
	return 1;
}
alias:traerauto("traercar", "getcar");

cmd:irauto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new Float:cwx2, Float:cwy2, Float:cwz2, vehicleid;
	if (sscanf(params, "i", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /irauto (Auto ID)");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El vehículo introducido no existe, verifica en /dl.");
	GetVehiclePos(vehicleid, cwx2, cwy2, cwz2);
	SetPosEx(playerid, cwx2, cwy2, cwz2, 0.0, 0, 0, 1);
	return 1;
}
alias:irauto("ircar", "gotocar");

cmd:repararveh(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estás en un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	RepairVehicle(vehicleid);
	if (GetVehicleModel(vehicleid) == 528 || GetVehicleModel(vehicleid) == 427) SetVehicleHealth(vehicleid, 5000.0);
	else SetVehicleHealth(vehicleid, 1000.0);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Vehículo reparado.");
	return 1;
}
alias:repararveh("fixveh");

cmd:fixvid(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], vehicleid;
    if (sscanf(params, "i", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fixvid (VehiculoID)");
	if (vehicleid < 0 || vehicleid > MAX_VEHICULOS) return SendPlayerChatMessage(playerid, COLOR_GREEN, "ID de vehículo incorrecto.");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El vehículo introducido no existe, verifica en /dl.");
	SetVehicleHealth(vehicleid, 1000.0);
	RepairVehicle(vehicleid);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) reparó el vehículo %d (%s).", InfoCuenta[playerid][jNombre], playerid, vehicleid, GetVehicleName(vehicleid));
	SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

cmd:ah(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new dialog[4096];
	strcat(dialog, "{FF2F2F}Comandos administrativos:\n");
	if (GetPlayerAdmin(playerid, 1) != 0)
	{
	    strcat(dialog, "{b42d2d}Support\n");
		strcat(dialog, "{FFFFFF}/a - /ir - /ircar - /kick - /kickname - /darvida - /encarcelados\n");
		strcat(dialog, "{FFFFFF}/enrenta - /vergraffitis - /dudas - /aduda - /rduda - /ls - /sf - /lv - /llevarls\n");
		strcat(dialog, "{FFFFFF}/afks - /quitarefectos - /revivir - /spec - /nuevos - /qfa - /togvip\n");
		strcat(dialog, "{FFFFFF}/traer - /reportes - /ar - /rr - /irfaccion - /irnegocio - /ircajero - /irpuerta\n");
		strcat(dialog, "{FFFFFF}/acallsign - /vercuenta - /cambiarint - /cambiarvw - /autoint - /autovw - /traercar\n");
		strcat(dialog, "{FFFFFF}/verpermisos - /darskin - /sp - /verprivados - /rtcar - /slap - /vehslap - /darrol\n");
		strcat(dialog, "{FFFFFF}/infoplanta /irplanta /idplanta\n\n");
	}
	if (GetPlayerAdmin(playerid, 2) != 0)
	{
	    strcat(dialog, "{b42d2d}Moderator\n");
		strcat(dialog, "{FFFFFF}/borraranuncios - /adminbaneo - /rcategoria - /respawncars - /limpiarmanos - /fixvid - /ao\n");
		strcat(dialog, "{FFFFFF}/ocultarveh - /jetpack - /congelar - /descongelar - /irpuertainterior - /liberar - /verarmas\n");
		strcat(dialog, "{FFFFFF}/listavehs - /bloquearmp - /checkmoney- /sancionar - /sancionaroff\n");
		strcat(dialog, "{FFFFFF}/limpiararmas - /desbanearpj - /desbanearcuenta - /desbanip - /darchaleco - /checkllaves \n");
		strcat(dialog, "{FFFFFF}/borrarplanta\n\n");
	}
	if (GetPlayerAdmin(playerid, 3) != 0)
	{
	    strcat(dialog, "{b42d2d}Administrator\n");
		strcat(dialog, "{FFFFFF}/quitardni - /limpiarchat - /limpiarsuelo - /ircoordenada - /repararveh - /irintcasa\n");
		strcat(dialog, "{FFFFFF}/getpos - /vertoys - /entercar - /punto - /irpunto\n");
		strcat(dialog, "{FFFFFF}/listaobjetos - /horaregalo - /limpiarreportes - /reparartodo - /llenargas - /verinterior\n");
		strcat(dialog, "{FFFFFF}/dargraffiti - /aincendios - /crearincendio - /aseguro - /amotor - /limpiarobjetov\n");
		strcat(dialog, "{FFFFFF}/quitarefectos /quitaradiccion /adelantarefectos\n\n");
	}
	if (GetPlayerAdmin(playerid, 4) != 0)
	{
	    strcat(dialog, "{b42d2d}Game Opertator\n");
		strcat(dialog, "{FFFFFF}/crearobjeto - /regaloatodos - /forzarpayday - /multicuenta - /verwalkie - /nombreactor\n");
		strcat(dialog, "{FFFFFF}/bloqbug - /desbloqbug - /crearactor - /borraractor - /skinactor - /animactor - /anunciostaff\n");
		strcat(dialog, "{FFFFFF}/crearpuerta - /editarpuerta - /borrarpuerta - /anticheat - /crearregalo - /musica - /showsound\n");
		strcat(dialog, "{FFFFFF}/daref - /daradmin - /darstat - /forzarpayday2 - /avenegocio - /negocioname - /leetodo\n");
		strcat(dialog, "{FFFFFF}/creargraffiti - /avecasa - /editarinterior - /darvest - /darvest2 - /venderlaser\n");
		strcat(dialog, "{FFFFFF}/quitarfaccionoff - /cambiarhora - /setweather - /editarpuertanombre - /editargps\n");
		strcat(dialog, "{FFFFFF}/verip - /ip - /roleplay - /register - /nombreadmin - /crearcajero - /borrarcajero\n");
		strcat(dialog, "{FFFFFF}/crecerplanta\n\n");
	}
	if (GetPlayerAdmin(playerid, 10) != 0)
	{
	    strcat(dialog, "{b42d2d}Leadership\n");
		strcat(dialog, "{FFFFFF}/dardinero - /crearnegocio - /editarnegocio - /borrarnegocio - /crearcasa - /editarh\n");
		strcat(dialog, "{FFFFFF}/cambiarclaveusuario - /borrarcasa - /editarvehiculo\n\n");
	}
	if (InfoCuenta[playerid][jEncFac] != 0)
	{
		strcat(dialog, "{FFFF00}Encargado de facciones\n");
		strcat(dialog, "{FFFFFF}/facciones - /crearfaccion - /editarfnombre - /editarflogo - /editarflider - /editarfsublider\n");
		strcat(dialog, "{FFFFFF}/statusfacciones - /irfaccion - /editarfaccion - /editarfskin - /editarfequipo - /limpiarfaccion\n");
		strcat(dialog, "{FFFFFF}/supervisar - /facchat - /hacerlider - /hacersublider - /hacermiembro - /borrarfaccion\n\n");
	}
	if (InfoCuenta[playerid][jEncMap] != 0)
	{
		strcat(dialog, "{FFFF00}Mapper: {FFFFFF}/adminmap\n");
	}
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos administrativos", dialog, "Cerrar", "");
	return 1;
}
alias:ah("adminayuda", "ahelp");

cmd:darskin(playerid, params[])
{
    if (CheckAdminCMD(playerid, 1)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], skin, targetid = -1, string[128];
    if (sscanf(params, "s[24]d", codigo, skin)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /darskin (#Código) (SkinID)");
    targetid = GetPlayerByCodigo(codigo); 
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Código no válido o jugador desconectado.");
    if (IsValidSkin(skin) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes de escoger una id de skin entre 1 y 311.");
    GivePlayerSkin(targetid, skin);
    format(string, sizeof string, "%s te cambió el skin, ID SKIN: %d.", GetNameFormat(playerid), skin);
    SendPlayerChatMessage(targetid, COLOR_WHITE, string);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) cambió el skin(%d) de %s(%d).", InfoCuenta[playerid][jNombre], playerid, skin, GetNameFormat(targetid), targetid);
    SendAdminMessage(0xFFFFFFFF, string);
    return 1;
}

cmd:adminbaneo(playerid)
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "/banearpj - /obanearpj - /banearcuenta - /obanearcuenta - /banearip");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "/desbanearcuenta - /desbanearpj - /tbanpj - /tbancuenta - /otbanpj - /otbancuenta");
	return 1;
}

cmd:multicuenta(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], string[128], targetid = -1;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "USE: /multicuenta [#Código]");
    targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Código no válido o jugador desconectado.");
    if (InfoCuenta[targetid][jMulticuenta] == 0)
    {
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) autorizó la multicuenta a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s autorizó la multicuenta a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/multicuenta.log", string);
        InfoCuenta[targetid][jMulticuenta] = 1;
    }
    else
    {
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) rechazó la multicuenta a %s(%d). Sólo puede tener una cuenta.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s rechazó la multicuenta a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/multicuenta.log", string);
        InfoCuenta[targetid][jMulticuenta] = 0;
    }
    guardar_int_mysql("cuentas", "Multicuenta", InfoCuenta[targetid][jID], InfoCuenta[targetid][jMulticuenta]);
    return 1;
}
cmd:desbloqbug(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], string[190], targetid = -1;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /desbloqbug (#Código)");
    targetid = GetPlayerByCodigo(codigo);
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Código no válido o jugador desconectado.");
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) desbloqueó del /reportarbug a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
    SendAdminMessage(0xFFFFFFFF, string);
    format(string, sizeof string, "%s desbloqueó a %s del /reportarbug.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
    Log("f_logs/reportbugA.log", string);
    InfoPersonaje[targetid][pBlockBug] = 0;
    guardar_int_mysql("personajes", "BlockBug", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pBlockBug]);
    return 1;
}

cmd:nog(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    if (CheckAdminDuty(playerid)) return 1;
    new codigo[25], string[128], targetid = -1;
    if (sscanf(params, "s[24]", codigo)) return SendPlayerChatMessage(playerid, COLOR_GREY, "USA: /nog [#Código]");
    targetid = GetPlayerByCodigo(codigo);  
    if (targetid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Código no válido o jugador no conectado.");
    if (InfoPersonaje[targetid][pTogGraffiti] == 0)
    {
        InfoPersonaje[targetid][pTogGraffiti] = 1;
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) le a bloqueado el uso del CMD /graffiti a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s le a bloqueado el uso del CMD /graffiti a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/admin.log", string);
        SendPlayerChatMessage(targetid, COLOR_GREY, "[Aviso]: Fuiste bloqueado del comando /graffiti.");
    }
    else
    {
        InfoPersonaje[targetid][pTogGraffiti] = 0;
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha desbloqueado el uso del CMD /graffiti a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s ha desbloqueado el uso del CMD /graffiti a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/admin.log", string);
        SendPlayerChatMessage(targetid, COLOR_GREY, "[Aviso]: Fuiste desbloqueado del comando /graffiti.");
    }
    guardar_int_mysql("personajes", "BlockG", InfoPersonaje[targetid][pID], InfoPersonaje[targetid][pTogGraffiti]);
    return 1;
}
alias:nog("bloqueargraffiti");

/*cmd:daradmin(playerid, params[])
{
	if (InfoCuenta[playerid][jEncStaff] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de E.S");
	new playerid2, level, string[340];
	if(sscanf(params, "ud", playerid2, level)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /daradmin (PlayerID) (Nivel) [Niveles: 1 Soporte, 2 Mod, 3 Admin, 4 GO]");
	if(!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	if(level < 0 || level > 4) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Sólo existen 4 rangos administrativos.");
	if(level == 0){
		SetPlayerColor(playerid2, 0xFFFFFF00);
		papilla[playerid2] = 0;
		InfoCuenta[playerid2][jEncFac] = 0;
		InfoCuenta[playerid2][jAdmin] = 0;
		mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET JotoOtaku = 0, EncFac = 0, EncMap = 0 WHERE ID = '%d'", InfoCuenta[playerid2][jID]);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "%s(%d) te ha expulsado de la administración.", InfoCuenta[playerid][jNombre], playerid);
		SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) expulsó de la administración a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s expulsó a %s de la administración.", InfoCuenta[playerid][jNombre], NombreDeCuenta(playerid2));
		Log("f_logs/admins.log", string);
		return 1;
	}
	InfoCuenta[playerid2][jAdmin] = level;
	guardar_int_mysql("cuentas", "JotoOtaku", InfoCuenta[playerid2][jID], InfoCuenta[playerid2][jAdmin]);
	format(string, sizeof string, "%s(%d) lo ha asignado %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetAdminName(playerid2), level);
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado %s(%d) a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetAdminName(playerid2), level, InfoCuenta[playerid2][jNombre], playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s asignó %s a %s.", InfoCuenta[playerid][jNombre], GetAdminName(playerid2), InfoCuenta[playerid2][jNombre]);
	Log("f_logs/admins.log", string);
	return 1;
}*/

cmd:daradmin(playerid, params[])
{
    if (InfoCuenta[playerid][jEncStaff] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de E.S"); 
    new account_name[25], level, targetid = -1, account_db_id = -1, string[340], query[256];
    new target_name[MAX_PLAYER_NAME], admin_rank_name[30];   
    if(sscanf(params, "s[24]d", account_name, level)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /daradmin (Nombre_Cuenta) (Nivel) [Niveles: 1 Soporte, 2 Mod, 3 Admin, 4 GO]"); 
    if(level < 0 || level > 4) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Sólo existen 4 rangos administrativos.");
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && strcmp(InfoCuenta[i][jNombre], account_name, true, sizeof(account_name)) == 0)
        {
            targetid = i;
            account_db_id = InfoCuenta[i][jID];
            format(target_name, sizeof target_name, "%s", InfoCuenta[i][jNombre]);
            break;
        }
    }
    if (targetid == -1)
    {
        mysql_format(db_samp, query, sizeof query, "SELECT ID FROM cuentas WHERE Nombre = '%e' LIMIT 1", account_name);
        new Cache:result = mysql_query(db_samp, query);

        if (cache_num_rows() == 0) 
        {
            cache_delete(result);
            return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombre de cuenta no encontrado en la base de datos.");
        }       
        cache_get_value_int(0, "ID", account_db_id);
        format(target_name, sizeof target_name, "%s", account_name);
        cache_delete(result);
    }    
    if (account_db_id == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Error interno al obtener la ID de la cuenta.");
    if (targetid != -1) {
        format(admin_rank_name, sizeof admin_rank_name, "%s", GetAdminName(targetid)); 
    } else {
        switch (level)
        {
            case 1: format(admin_rank_name, sizeof admin_rank_name, "Support");
            case 2: format(admin_rank_name, sizeof admin_rank_name, "Moderator");
            case 3: format(admin_rank_name, sizeof admin_rank_name, "Administrator");
            case 4: format(admin_rank_name, sizeof admin_rank_name, "Game Operator");
            default: format(admin_rank_name, sizeof admin_rank_name, "Nivel %d", level);
        }
    }
    if (level == 0)
    {
        if (targetid != -1)
        {
            SetPlayerColor(targetid, 0xFFFFFF00);
            papilla[targetid] = 0;
            InfoCuenta[targetid][jEncFac] = 0;
            InfoCuenta[targetid][jAdmin] = 0;
            format(string, sizeof string, "%s(%d) te ha expulsado de la administración.", InfoCuenta[playerid][jNombre], playerid);
            SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);
        }       
        mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET JotoOtaku = 0, EncFac = 0, EncMap = 0 WHERE ID = '%d'", account_db_id);
        mysql_tquery(db_samp, query);       
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) expulsó de la administración a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s expulsó a %s de la administración.", InfoCuenta[playerid][jNombre], target_name);
        Log("f_logs/admins.log", string);
        return 1;
    }   
    if (targetid != -1)
    {
        InfoCuenta[targetid][jAdmin] = level;
        format(string, sizeof string, "%s(%d) lo ha asignado %s.", InfoCuenta[playerid][jNombre], playerid, GetAdminName(targetid)); 
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);
    }
    guardar_int_mysql("cuentas", "JotoOtaku", account_db_id, level);
    format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado %s a la cuenta %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, admin_rank_name, target_name, account_db_id);
    SendAdminMessage(0xFFFFFFFF, string);  
    format(string, sizeof string, "%s asignó %s a %s.", InfoCuenta[playerid][jNombre], admin_rank_name, target_name);
    Log("f_logs/admins.log", string);
    return 1;
}

cmd:darmap(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    new account_name[25], targetid = -1, account_db_id = -1, string[178], query[128];
    new target_name[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]", account_name)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darmap (Nombre_Cuenta)");
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && strcmp(InfoCuenta[i][jNombre], account_name, true, sizeof(account_name)) == 0)
        {
            targetid = i;
            account_db_id = InfoCuenta[i][jID];
            format(target_name, sizeof target_name, "%s", InfoCuenta[i][jNombre]);
            break;
        }
    }
    if (targetid == -1)
    {
        mysql_format(db_samp, query, sizeof query, "SELECT ID, EncMap FROM cuentas WHERE Nombre = '%e' LIMIT 1", account_name);
        new Cache:result = mysql_query(db_samp, query);

        if (cache_num_rows() == 0) 
        {
            cache_delete(result);
            return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombre de cuenta no encontrado en la base de datos.");
        }
        
        cache_get_value_int(0, "ID", account_db_id);
        new current_encmap;
        cache_get_value_int(0, "EncMap", current_encmap);
        format(target_name, sizeof target_name, "%s", account_name);
        cache_delete(result);
        new new_encmap = (current_encmap == 0) ? 1 : 0;
        mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET EncMap = '%d' WHERE ID = '%d'", new_encmap, account_db_id);
        mysql_tquery(db_samp, query);
        
        if (new_encmap == 1)
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado mapper a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha asignado mapper a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        else
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el mapper a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha retirado el mapper a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        Log("f_logs/security.log", string);
        return 1;
    }    
    if (InfoCuenta[targetid][jEncMap] == 0)
    {
        InfoCuenta[targetid][jEncMap] = 1;
        format(string, sizeof string, "%s(%d) lo ha asignado mapper.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);       
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado mapper a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[targetid][jNombre], targetid);
        SendAdminMessage(0xFFFFFFFF, string);       
        format(string, sizeof string, "%s ha asignado mapper a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    else
    {
        InfoCuenta[targetid][jEncMap] = 0;
        format(string, sizeof string, "%s(%d) le ha retirado el mapper.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);        
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el mapper a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[targetid][jNombre], targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        format(string, sizeof string, "%s ha retirado el mapper a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    guardar_int_mysql("cuentas", "EncMap", InfoCuenta[targetid][jID], InfoCuenta[targetid][jEncMap]);
    return 1;
}

cmd:dares(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    new account_name[25], targetid = -1, account_db_id = -1, string[178], query[128];
    new target_name[MAX_PLAYER_NAME];
    if (sscanf(params, "s[24]", account_name)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dares (Nombre_Cuenta)");
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && strcmp(InfoCuenta[i][jNombre], account_name, true, sizeof(account_name)) == 0)
        {
            targetid = i;
            account_db_id = InfoCuenta[i][jID];
            format(target_name, sizeof target_name, "%s", InfoCuenta[i][jNombre]);
            break;
        }
    }
    if (targetid == -1)
    {
        mysql_format(db_samp, query, sizeof query, "SELECT ID, EncStaff FROM cuentas WHERE Nombre = '%e' LIMIT 1", account_name);
        new Cache:result = mysql_query(db_samp, query);

        if (cache_num_rows() == 0) 
        {
            cache_delete(result);
            return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombre de cuenta no encontrado en la base de datos.");
        }
        cache_get_value_int(0, "ID", account_db_id);
        new current_encstaff;
        cache_get_value_int(0, "EncStaff", current_encstaff);
        format(target_name, sizeof target_name, "%s", account_name);
        cache_delete(result);
        new new_encstaff = (current_encstaff == 0) ? 1 : 0;
        mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET EncStaff = '%d' WHERE ID = '%d'", new_encstaff, account_db_id);
        mysql_tquery(db_samp, query);
        
        if (new_encstaff == 1)
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado encargado de staff a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha asignado encargado de staff a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        else
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el encargado de staff a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha retirado el encargado de staff a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        Log("f_logs/security.log", string);
        return 1;
    }
    if (InfoCuenta[targetid][jEncStaff] == 0)
    {
        InfoCuenta[targetid][jEncStaff] = 1;
        format(string, sizeof string, "%s(%d) lo ha asignado encargado de staff.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);       
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado encargado de staff a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);       
        format(string, sizeof string, "%s ha asignado encargado de staff a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    else
    {
        InfoCuenta[targetid][jEncStaff] = 0;
        format(string, sizeof string, "%s(%d) le ha retirado el encargado de staff.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);        
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el encargado de staff a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);       
        format(string, sizeof string, "%s ha retirado el encargado de staff a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    guardar_int_mysql("cuentas", "EncStaff", InfoCuenta[targetid][jID], InfoCuenta[targetid][jEncStaff]);
    return 1;
}

cmd:daref(playerid, params[])
{
    if (CheckAdminCMD(playerid, 4)) return 1;
    
    new account_name[25], targetid = -1, account_db_id = -1, string[178], query[128];
    new target_name[MAX_PLAYER_NAME];

    if (sscanf(params, "s[24]", account_name)) 
        return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /daref (Nombre_Cuenta)");
        
    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (IsPlayerConnected(i) && strcmp(InfoCuenta[i][jNombre], account_name, true, sizeof(account_name)) == 0)
        {
            targetid = i;
            account_db_id = InfoCuenta[i][jID];
            format(target_name, sizeof target_name, "%s", InfoCuenta[i][jNombre]);
            break;
        }
    }

    if (targetid == -1)
    {
        mysql_format(db_samp, query, sizeof query, "SELECT ID, EncFac FROM cuentas WHERE Nombre = '%e' LIMIT 1", account_name);
        new Cache:result = mysql_query(db_samp, query);

        if (cache_num_rows() == 0) 
        {
            cache_delete(result);
            return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombre de cuenta no encontrado en la base de datos.");
        }
        
        cache_get_value_int(0, "ID", account_db_id);
        new current_encfac;
        cache_get_value_int(0, "EncFac", current_encfac);
        format(target_name, sizeof target_name, "%s", account_name);
        cache_delete(result);
        
        new new_encfac = (current_encfac == 0) ? 1 : 0;
        
        mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET EncFac = '%d' WHERE ID = '%d'", new_encfac, account_db_id);
        mysql_tquery(db_samp, query);
        
        if (new_encfac == 1)
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado encargado de facciones a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha asignado encargado de facciones a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        else
        {
            format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el encargado de facciones a %s (ID Cuenta: %d).", InfoCuenta[playerid][jNombre], playerid, target_name, account_db_id);
            SendAdminMessage(0xFFFFFFFF, string);
            format(string, sizeof string, "%s ha retirado el encargado de facciones a %s.", InfoCuenta[playerid][jNombre], target_name);
        }
        Log("f_logs/security.log", string);
        return 1;
    }
    
    if (InfoCuenta[targetid][jEncFac] == 0)
    {
        InfoCuenta[targetid][jEncFac] = 1;
        format(string, sizeof string, "%s(%d) lo ha asignado encargado de facciones.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);
        
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha asignado encargado de facciones a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        
        format(string, sizeof string, "%s ha asignado encargado de facciones a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    else
    {
        InfoCuenta[targetid][jEncFac] = 0;
        format(string, sizeof string, "%s(%d) le ha retirado el encargado de facciones.", InfoCuenta[playerid][jNombre], playerid);
        SendPlayerChatMessage(targetid, COLOR_LIGHTBLUE, string);
        
        format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha retirado el encargado de facciones a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(targetid), targetid);
        SendAdminMessage(0xFFFFFFFF, string);
        
        format(string, sizeof string, "%s ha retirado el encargado de facciones a %s.", InfoCuenta[playerid][jNombre], NombreDeCuenta(targetid));
        Log("f_logs/security.log", string);
    }
    
    guardar_int_mysql("cuentas", "EncFac", InfoCuenta[targetid][jID], InfoCuenta[targetid][jEncFac]);
    return 1;
}
alias:daref("darencfac");

cmd:encarcelados(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No tienes suficentes permisos para usar este comando.");
	if (CheckAdminDuty(playerid)) return 1;
	SendPlayerChatMessage(playerid, COLOR_GRAD1, "Encarcelados de prisión y jail ooc:");
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2) && InfoPersonaje[playerid2][pSancionado] != 0)
	{
		if (InfoPersonaje[playerid2][pSancionado] == 1) { SendClientMessageEx(playerid, COLOR_YELLOW, "%s (ID: %d) en jail ooc (by %s), tiempo restante: %s.", InfoPersonaje[playerid2][pNombre_Apellido], playerid2, InfoPersonaje[playerid2][pBySancion], Segundos_tiempo(InfoPersonaje[playerid2][pTiempoSancion])); }
		else { SendClientMessageEx(playerid, COLOR_GREEN, "%s (ID: %d) en prisión, tiempo restante: %s.", InfoPersonaje[playerid2][pNombre_Apellido], playerid2, Segundos_tiempo(InfoPersonaje[playerid2][pTiempoSancion])); }
	}
	return 1;
}
alias:encarcelados("enjail");