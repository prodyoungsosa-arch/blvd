VerificarCuenta(account[])
{
	new query[512];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Nombre = '%e'", account);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0) return 1;
	cache_delete(result);
	return 0;
}

VerificarEmail(account[])
{
	new query[512];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Email = '%e' LIMIT 1", account);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0) return 1;
	cache_delete(result);
	return 0;
}

enum cuentaInfo
{
	jID,                                // ID en base de datos
	jNombre[MAX_PLAYER_NAME],           // Nombre
	jClave[65],							// Contraseña
	jSalt[11],              			// Salt contraseña
	jEmail[256],                        // Email
	jIP[18],                			// Dirección IP
	jAdmin,                 			// Nivel admin
	jEncFac,                			// Encargado de facciones
	jEncMap,                            // Encargado de mapeos
	jEncStaff,                          // Encargado de staff
	jPreguntaSeguridad[256],			// Pregunta seguridad
	jRespuestaSeguridad[256],			// Respuesta seguridad
	jVIP,                           	// VIP nivel
	jExpira,							// VIP duración
	jMonedas,                   		// VIP monedas
	jMulticuenta,                   	// Multicuenta access
	jBaneo,
	jTiempoBaneo,
	jCulpableBaneo[MAX_PLAYER_NAME],
	jRazonBaneo[256],
	jFechaBaneo[256],
	jRegalo,							// Tiempo de regalo
	jFechaRegistro[256],                // Fecha de registro
	jUltimaConexion[256],               // Última conexión
	jRanuras,                           // slots de personajes
	jBloqueoMP,                         // Bloqueo MP
	jTogMP,                             // tog mp
	jVerMP,                             // ver mp
	jMaxCasas,							// casas
	jMaxNegocios, 						// negocios
	jMaxMuebles,                        // muebles
	jTogPing,                           // tog ping
	jEstiloAnuncio,                     // estilo anuncios
	jEstiloBolsillos,                   // estilo bolsillos
};
new InfoCuenta[MAX_PLAYERS][cuentaInfo];

forward CreatePlayerAccount(playerid);
public CreatePlayerAccount(playerid)
{
	InfoCuenta[playerid][jID] = cache_insert_id();
	cache_unset_active();
	VerPersonajes(playerid);
	return 1;
}

reset_InfoCuenta(playerid)
{
	InfoCuenta[playerid][jID] = -1;
	alm(InfoCuenta[playerid][jNombre], NombreOriginal(playerid));
	InfoCuenta[playerid][jClave][0] = EOS;
	InfoCuenta[playerid][jSalt][0] = EOS;
	alm(InfoCuenta[playerid][jEmail], "-");
	alm(InfoCuenta[playerid][jIP], "127.0.0.1");
	InfoCuenta[playerid][jAdmin] = 0;
	alm(InfoCuenta[playerid][jPreguntaSeguridad], "ninguna");
	alm(InfoCuenta[playerid][jRespuestaSeguridad], "ninguna");
	InfoCuenta[playerid][jEncFac] = 0;
	InfoCuenta[playerid][jEncMap] = 0;
	InfoCuenta[playerid][jEncStaff] = 0;
	InfoCuenta[playerid][jVIP] = 0;
	InfoCuenta[playerid][jExpira] = -1;
	InfoCuenta[playerid][jMonedas] = 0;
	InfoCuenta[playerid][jMulticuenta] = 0;
	InfoCuenta[playerid][jRegalo] = 0;
	alm(InfoCuenta[playerid][jFechaRegistro], "none");
	alm(InfoCuenta[playerid][jUltimaConexion], "none");
	InfoCuenta[playerid][jRanuras] = 3;
	InfoCuenta[playerid][jBaneo] = 0;
	InfoCuenta[playerid][jTiempoBaneo] = 0;
	alm(InfoCuenta[playerid][jCulpableBaneo], "-");
	alm(InfoCuenta[playerid][jRazonBaneo], "-");
	alm(InfoCuenta[playerid][jFechaBaneo], "-");
	InfoCuenta[playerid][jBloqueoMP] = 0;
	InfoCuenta[playerid][jTogMP] = 0;
	InfoCuenta[playerid][jVerMP] = 0;
	InfoCuenta[playerid][jMaxCasas] = 2;
	InfoCuenta[playerid][jMaxNegocios] = 2;
	InfoCuenta[playerid][jMaxMuebles] = 150;
	InfoCuenta[playerid][jTogPing] = 0;
	InfoCuenta[playerid][jEstiloAnuncio] = 0;
	InfoCuenta[playerid][jEstiloBolsillos] = 0;
}

MuestraBloqueoCuenta(playerid)
{
	new string[1028];
	switch (InfoCuenta[playerid][jBaneo])
	{
		case 1: //temporal
		{
			if (InfoCuenta[playerid][jTiempoBaneo] < gettime())
			{
				SendPlayerChatMessage(playerid, COLOR_GREY, "El bloqueo de tu personaje ha terminado, ya puedes ingresar.");
				InfoCuenta[playerid][jTiempoBaneo] = 0;
				InfoCuenta[playerid][jBaneo] = 0;
				new list[32];
				alm(list, "ninguno");
				mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET OtakuN_N = 0, TimeBanUwU = 0, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", list, list, list, InfoCuenta[playerid][jID]);
				mysql_tquery(db_samp, string);
				VerPersonajes(playerid);
			}
			else
			{
				format(string, sizeof string, "{FFFFFF}Cuenta: {F5DEB3}%s\n\n{FFFFFF}Encargado: {FFBF00}%s\n{FFFFFF}Razón: {b42d2d}%s\n{FFFFFF}Fecha: {F5DEB3}%s\n{FFFFFF}Tiempo: {F5DEB3}%s\n",
				InfoCuenta[playerid][jNombre], InfoCuenta[playerid][jCulpableBaneo], InfoCuenta[playerid][jRazonBaneo], InfoCuenta[playerid][jFechaBaneo], Segundos_tiempo(InfoCuenta[playerid][jTiempoBaneo] - gettime()));
				Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Información del bloqueo temporal", string, "", "");
				SetTimerEx("TimerKICK", 1500, false, "d", playerid);
			}
		}
		case 2: //permanente
		{
			format(string, sizeof string, "{FFFFFF}Cuenta: {F5DEB3}%s\n\n{FFFFFF}Encargado: {FFBF00}%s\n{FFFFFF}Razón: {b42d2d}%s\n{FFFFFF}Fecha: {F5DEB3}%s\n",
			InfoCuenta[playerid][jNombre], InfoCuenta[playerid][jCulpableBaneo], InfoCuenta[playerid][jRazonBaneo], InfoCuenta[playerid][jFechaBaneo]);
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Información del bloqueo", string, "", "");
			SetTimerEx("TimerKICK", 1500, false, "d", playerid);
		}
		default: //limpio
		{
			Kick(playerid);
		}
	}
	return 1;
}