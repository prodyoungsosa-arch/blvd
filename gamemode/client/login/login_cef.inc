// login_cef.inc - login y registro con omp-cef (reemplaza los dialogos / textdraws de login.inc)
// Incluir DESPUES de login.inc y characters.inc (usa InfoCuenta, conectado, EnLogin, db_samp, etc.)
// UI: scriptfiles/cef/login/index.html  ->  http://cef/login/index.html

#if defined _login_cef_included
	#endinput
#endif
#define _login_cef_included

#include <cef>

#define LOGIN_BROWSER_ID	(100)
#define LOGIN_BROWSER_URL	"http://cef/login/index.html"

new bool:gCefLogin[MAX_PLAYERS];	// true mientras la pantalla de login esta abierta (los eventos solo se aceptan en ese estado)

new const gCefQuestions[][] =
{
	"Cual es el apellido de soltera de mi madre?",
	"Cual es el nombre de mi mascota?",
	"Como se llama mi primer amor?",
	"Cual es la fecha del cumpleaños de mi hermano(a)?",
	"En que colegio estudie en primaria?",
	"Cual es el nombre de mi mejor amigo?"
};

// ---------------------------------------------------------------- API
// Llamar una vez desde OnGameModeInit
stock CefLogin_Init()
{
	CEF_AddResource("login");	// scriptfiles/cef/login/ (igual que "inventory")
	CEF_RegisterEvent("login:submit", "OnCefLoginSubmit", Argument_String, Argument_String);
	CEF_RegisterEvent("register:submit", "OnCefRegisterSubmit", Argument_String, Argument_String, Argument_String, Argument_Integer, Argument_String);
}

// Devuelve 0 si el jugador no tiene el plugin (usa tu login anterior como respaldo)
stock CefLogin_Show(playerid)
{
	if (!gCefReady[playerid]) return 0;		// se pone en true en OnCefReady (main.pwn)
	if (gCefLogin[playerid]) return 1;
	gCefLogin[playerid] = true;
	CEF_CreateBrowser(playerid, LOGIN_BROWSER_ID, LOGIN_BROWSER_URL, true);
	return 1;
}

stock CefLogin_Hide(playerid)
{
	if (!gCefLogin[playerid]) return 0;
	gCefLogin[playerid] = false;
	CEF_DestroyBrowser(playerid, LOGIN_BROWSER_ID);
	return 1;
}

stock CefLogin_Error(playerid, const msg[])
{
	CEF_EmitEvent(playerid, LOGIN_BROWSER_ID, "ui:error", CEF_STR(msg));
	return 1;
}

// Login correcto: mismo codigo que el boton "Ingresar" (p_tdLogin[48]) en OnPlayerClickPlayerTextDraw
stock CefLogin_Success(playerid)
{
	EnLogin[playerid] = 3;

	new query[170], Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE ID = '%d'", InfoCuenta[playerid][jID]);
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0)
	{
		rebel_string(0, "Email", InfoCuenta[playerid][jEmail], 256);
		rebel_string(0, "IP", InfoCuenta[playerid][jIP], 18);
		rebel_int(0, "JotoOtaku", InfoCuenta[playerid][jAdmin]);
		rebel_int(0, "EncFac", InfoCuenta[playerid][jEncFac]);
		rebel_int(0, "VIP", InfoCuenta[playerid][jVIP]);
		rebel_int(0, "Expira", InfoCuenta[playerid][jExpira]);
		rebel_int(0, "CoinsVIP", InfoCuenta[playerid][jMonedas]);
		rebel_int(0, "Multicuenta", InfoCuenta[playerid][jMulticuenta]);
		rebel_int(0, "OtakuN_N", InfoCuenta[playerid][jBaneo]);
		rebel_int(0, "TimeBanUwU", InfoCuenta[playerid][jTiempoBaneo]);
		rebel_string(0, "FueBan", InfoCuenta[playerid][jCulpableBaneo], 24);
		rebel_string(0, "ReasonBanUwU", InfoCuenta[playerid][jRazonBaneo], 256);
		rebel_string(0, "MomentBan", InfoCuenta[playerid][jFechaBaneo], 256);
		rebel_string(0, "FechaRegistro", InfoCuenta[playerid][jFechaRegistro], 256);
		rebel_string(0, "UltimaConexion", InfoCuenta[playerid][jUltimaConexion], 256);
		rebel_int(0, "Ranuras", InfoCuenta[playerid][jRanuras]);
		rebel_int(0, "VerMP", InfoCuenta[playerid][jVerMP]);
		rebel_int(0, "TogMP", InfoCuenta[playerid][jTogMP]);
		rebel_int(0, "BloqueoMP", InfoCuenta[playerid][jBloqueoMP]);
		rebel_int(0, "TogPing", InfoCuenta[playerid][jTogPing]);
		rebel_int(0, "MaxMuebles", InfoCuenta[playerid][jMaxMuebles]);
		rebel_int(0, "MaxNegocios", InfoCuenta[playerid][jMaxNegocios]);
		rebel_int(0, "MaxCasas", InfoCuenta[playerid][jMaxCasas]);
		cache_unset_active();
		cache_delete(result);
	}
	SetLogin(playerid, 3);
	if (InfoCuenta[playerid][jBaneo] != 0) return MuestraBloqueoCuenta(playerid);
	VerPersonajes(playerid);
	return 1;
}

stock CefLogin_Start(playerid)
{
	if (CefLogin_Show(playerid)) return 1;
	SetTimerEx("CefLogin_Fallback", 8000, false, "d", playerid);
	return 0;
}

forward CefLogin_Fallback(playerid);
public CefLogin_Fallback(playerid)
{
	if (!IsPlayerConnected(playerid) || gCefLogin[playerid]) return 1;
	if (state_on[playerid] == 2 && usuario_registro[playerid] == 0) SetLogin(playerid, 1);
	return 1;
}

stock CefLogin_OnReady(playerid)
{
	printf("[LOGIN-CEF] ready p=%d state_on=%d usuario_registro=%d abierto=%d", playerid, state_on[playerid], usuario_registro[playerid], gCefLogin[playerid]);
	if (state_on[playerid] != 2 || usuario_registro[playerid] != 0 || gCefLogin[playerid]) return 0;
	SetLogin(playerid, 2);		// oculta los textdraws si el respaldo ya se habia mostrado
	return CefLogin_Show(playerid);
}

forward OnCefLoginSubmit(playerid, email[], pass[]);
public OnCefLoginSubmit(playerid, email[], pass[])
{
	if (!gCefLogin[playerid]) return 1;
	if (!email[0] || !pass[0]) return CefLogin_Error(playerid, "Completa todos los campos.");

	// igual que IniciarSesion: acepta email o nombre de personaje
	new newid = -1, query[256];
	mysql_format(db_samp, query, sizeof query, "SELECT CuentaID FROM personajes WHERE Nombre_Apellido = '%e' LIMIT 1", email);
	new Cache:pj = mysql_query(db_samp, query);
	if (cache_num_rows() > 0) rebel_int(0, "CuentaID", newid);
	cache_unset_active();
	cache_delete(pj);
	if (newid != -1) mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Email = '%e' OR ID = '%d' LIMIT 1", email, newid);
	else mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Email = '%e' LIMIT 1", email);

	new Cache:result = mysql_query(db_samp, query);
	if (!cache_num_rows())
	{
		cache_delete(result);
		return CefLogin_Error(playerid, "Correo o clave incorrectos.");	// mismo mensaje para no revelar si la cuenta existe
	}
	rebel_int(0, "ID", InfoCuenta[playerid][jID]);
	rebel_string(0, "Email", InfoCuenta[playerid][jEmail], MAX_PLAYER_NAME);
	rebel_string(0, "Nombre", InfoCuenta[playerid][jNombre], MAX_PLAYER_NAME);
	rebel_string(0, "Clave", InfoCuenta[playerid][jClave], 65);
	rebel_string(0, "Salt", InfoCuenta[playerid][jSalt], 11);
	cache_unset_active();
	cache_delete(result);

	// igual que IniciarSesion2: hash con salt y 3 intentos como maximo
	new hash[65];
	SHA256_PassHash(pass, InfoCuenta[playerid][jSalt], hash, 65);
	if (strcmp(hash, InfoCuenta[playerid][jClave]) != 0)
	{
		if (++intentos_load[playerid] >= 3)
		{
			CefLogin_Hide(playerid);
			Kick(playerid);
			return 1;
		}
		new msg[64];
		format(msg, sizeof msg, "Correo o clave incorrectos. Intentos restantes: %d", 3 - intentos_load[playerid]);
		return CefLogin_Error(playerid, msg);
	}

	foreach(new p: Player) if (p != playerid && conectado[p] == 1 && strcmp(InfoCuenta[playerid][jEmail], InfoCuenta[p][jEmail], true) == 0)
	{
		SendClientMessage(p, 0xFF6347AA, "Alguien intento entrar hace poco a tu cuenta.");
		CefLogin_Hide(playerid);
		Kick(playerid);
		return 1;
	}

	conectado[playerid] = 1;
	CefLogin_Hide(playerid);
	return CefLogin_Success(playerid);
}

forward OnCefRegisterSubmit(playerid, user[], email[], pass[], question, answer[]);
public OnCefRegisterSubmit(playerid, user[], email[], pass[], question, answer[])
{
	if (!gCefLogin[playerid]) return 1;

	// el servidor valida SIEMPRE, la validacion del HTML es solo comodidad
	new len = strlen(user);
	if (len < 5 || len > 20 || !numero_y_letras(user)) return CefLogin_Error(playerid, "Usuario invalido (5-20 letras o numeros).");
	if (VerificarCuenta(user)) return CefLogin_Error(playerid, "El nombre de usuario ya esta en uso.");

	len = strlen(email);
	if (len < 10 || strfind(email, "@", true) == -1) return CefLogin_Error(playerid, "Correo electronico invalido.");
	if (VerificarEmail(email)) return CefLogin_Error(playerid, "El correo ingresado ya esta en uso.");

	len = strlen(pass);
	if (len < 5 || len > 18) return CefLogin_Error(playerid, "La clave debe tener entre 5 y 18 caracteres.");

	if (question < 0 || question >= sizeof gCefQuestions) return CefLogin_Error(playerid, "Pregunta de seguridad invalida.");
	len = strlen(answer);
	if (len < 5 || len > 33) return CefLogin_Error(playerid, "La respuesta debe tener entre 5 y 32 caracteres.");

	foreach(new p: Player) if (p != playerid && conectado[p] == 1 && strcmp(user, InfoCuenta[p][jNombre], true) == 0)
		return CefLogin_Error(playerid, "El nombre de usuario ya esta en uso.");

	// mismos datos que Registrarse .. Registrarse6
	conectado[playerid] = 1;
	alm(InfoCuenta[playerid][jNombre], user);
	alm(InfoCuenta[playerid][jEmail], email);
	alm(name_password[playerid], pass);
	Loop(e, 10, 0) { InfoCuenta[playerid][jSalt][e] = random(79) + 47; }
	InfoCuenta[playerid][jSalt][10] = 0;
	SHA256_PassHash(pass, InfoCuenta[playerid][jSalt], InfoCuenta[playerid][jClave], 65);
	alm(InfoCuenta[playerid][jPreguntaSeguridad], gCefQuestions[question]);
	alm(InfoCuenta[playerid][jRespuestaSeguridad], answer);

	CefLogin_Hide(playerid);
	ClearChat(playerid);
	InfoCuenta[playerid][jFechaRegistro] = FechaHoy();
	InfoCuenta[playerid][jUltimaConexion] = FechaHoy();
	new newip[18];
	GetPlayerIp(playerid, newip, sizeof newip);
	alm(InfoCuenta[playerid][jIP], newip);

	new query[2056];
	mysql_format(db_samp, query, sizeof query, "INSERT INTO cuentas (Nombre, Clave, Salt, Email, IP, PreguntaSeguridad, RespuestaSeguridad, FechaRegistro, UltimaConexion) \
	VALUES ('%e', '%e', '%e', '%e', '%e', '%e', '%e', '%e', '%e')",
	InfoCuenta[playerid][jNombre],
	InfoCuenta[playerid][jClave],
	InfoCuenta[playerid][jSalt],
	InfoCuenta[playerid][jEmail],
	InfoCuenta[playerid][jIP],
	InfoCuenta[playerid][jPreguntaSeguridad],
	InfoCuenta[playerid][jRespuestaSeguridad],
	InfoCuenta[playerid][jFechaRegistro],
	InfoCuenta[playerid][jUltimaConexion]);
	mysql_tquery(db_samp, query, "CreatePlayerAccount", "i", playerid);
	return 1;
}
