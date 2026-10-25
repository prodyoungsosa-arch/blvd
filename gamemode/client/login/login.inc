new conectado[MAX_PLAYERS];
new state_on[MAX_PLAYERS]; // 0: ningun logeo, 1: en spawn, 2: en login & 3: jugando.
new usuario_registro[MAX_PLAYERS]; // 2: jugando - 1: registrado - 0: no registrado
new EnLogin[MAX_PLAYERS];

numero_y_letras(const name[])
{
	if (!name[0])
		return 0;

	else for (new i = 0, len = strlen(name); i != len; i ++)
	{
		if ((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && (name[i] < '0' || name[i] > '9'))
			return 0;
	}
	return 1;
}


SetLogin(playerid, type)
{
	if(type == 1)
	{
		PlayerTextDrawSetStringEx(playerid, p_tdLogin[playerid][17], "Ingresar e-mail...");
		PlayerTextDrawSetStringEx(playerid, p_tdLogin[playerid][28], "Ingresar clave...");

		for(new i; i < 50; i++){
			PlayerTextDrawShow(playerid, p_tdLogin[playerid][i]);
		}
		SelectTextDraw(playerid,0x1f2329FF);	
	
		return 1;
	}
	else if(type == 2)
	{	
		for(new i; i < 50; i++){
			PlayerTextDrawHide(playerid, p_tdLogin[playerid][i]);
		}

		CancelSelectTextDraw(playerid);
		return 1;
	}
	else if(type == 3)
	{
		for(new i; i < 50; i++){
			PlayerTextDrawHide(playerid, p_tdLogin[playerid][i]);
		}
		StopAudioStreamForPlayer(playerid);
		return 1;
	}					
	return 1;
}

Dialog:IniciarSesion(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new newid = -1, query[256];
	

	if (VerificarPersonaje(inputtext))
	{
		rebel_int(0, "CuentaID", newid);
		cache_unset_active();
	}
	
	if (newid != -1) mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Email = '%e' OR ID = '%d' LIMIT 1", inputtext, newid);
	else mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE Email = '%e' LIMIT 1", inputtext);
	new Cache:result;
	result = mysql_query(db_samp, query);
	
	if (cache_num_rows() > 0)
	{
		rebel_int(0, "ID", InfoCuenta[playerid][jID]);
		rebel_string(0, "Email", InfoCuenta[playerid][jEmail], MAX_PLAYER_NAME);
		rebel_string(0, "Nombre", InfoCuenta[playerid][jNombre], MAX_PLAYER_NAME);
		foreach(new p: Player) if (conectado[p] == 1 && strcmp(InfoCuenta[playerid][jEmail], InfoCuenta[p][jEmail], true) == 0)
		{
			Kick(playerid);
			SendClientMessage(p, 0xFF6347AA, "Alguien intento entrar hace poco a tu cuenta.");
			return 1;
		}
		rebel_string(0, "Clave", InfoCuenta[playerid][jClave], 65);
		rebel_string(0, "Salt", InfoCuenta[playerid][jSalt], 11);
		cache_unset_active();
		conectado[playerid] = 1;

		EnLogin[playerid] = 2;
		new gformat[120];
		format(gformat, sizeof gformat, "%s", InfoCuenta[playerid][jEmail]);
    	PlayerTextDrawSetString(playerid, p_tdLogin[playerid][17], Fix_GT(gformat));
	} else {
		CrearNotificacion(playerid,"none", "Has colocado un email incorrecto.", 3);
	}
	cache_delete(result);
	return 1;
}

Dialog:IniciarSesion2(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new Salted_Key[65];
	SHA256_PassHash(inputtext, InfoCuenta[playerid][jSalt], Salted_Key, 65);
	if (strcmp(Salted_Key, InfoCuenta[playerid][jClave]) == 0) {
		new Str[512];
		for(new i = 0; i < strlen(inputtext); i++) {
			format(Str, sizeof(Str), "%s.", Str);
		}
		PlayerTextDrawSetString(playerid, p_tdLogin[playerid][28], Fix_GT(Str));
    	PlayerTextDrawShow(playerid, p_tdLogin[playerid][28]);
		EnLogin[playerid] = 3;
	} else {
		if(intentos_load[playerid] == 3) return Kick(playerid);
		intentos_load[playerid] += 1;
		CrearNotificacion(playerid,"none", "Has colocado una clave incorrecta.", 3);
	}
	return 1;
}

Dialog:Registrarse(playerid, response, listitem, inputtext[])
{
	if (!response) return SetLogin(playerid, 1);
	if (strlen(inputtext) < 5)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}nombre de usuario{EBEBEB} no puede ser inferior a 4 caracteres.");
		Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) > 20)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}nombre de usuario{EBEBEB} no puede sobrepasar los 20 caracteres.");
		Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	if (!numero_y_letras(inputtext))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}nombre de usuario{EBEBEB} solo puede contener letras y numeros.");
		Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	if (VerificarCuenta(inputtext))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}nombre de usuario{EBEBEB} ya esta en uso, prueba con otro.");
		Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	alm(InfoCuenta[playerid][jNombre], inputtext);
	Dialog_Show(playerid, Registrarse2, DIALOG_STYLE_INPUT, "{FFFFFF}Email", "{FFFFFF}Introduce tu {FE9A2E}correo electronico{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
	return 1;
}

Dialog:Registrarse2(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
	if (strlen(inputtext) < 10)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}correo electronico{EBEBEB} no puede ser inferior a 10 caracteres.");
		Dialog_Show(playerid, Registrarse2, DIALOG_STYLE_INPUT, "{FFFFFF}Email", "{FFFFFF}Introduce tu {FE9A2E}correo electronico{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	if (strfind(inputtext, "@", true) == -1)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}correo electronico{EBEBEB} debe contener el '@'.");
		Dialog_Show(playerid, Registrarse2, DIALOG_STYLE_INPUT, "{FFFFFF}Email", "{FFFFFF}Introduce tu {FE9A2E}correo electronico{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	if (VerificarEmail(inputtext))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {FE9A2E}correo electronico{EBEBEB} que ingresaste esta en uso.");
		Dialog_Show(playerid, Registrarse2, DIALOG_STYLE_INPUT, "{FFFFFF}Email", "{FFFFFF}Introduce tu {FE9A2E}correo electronico{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
		return 1;
	}
	alm(InfoCuenta[playerid][jEmail], inputtext);
	Dialog_Show(playerid, Registrarse3, DIALOG_STYLE_INPUT, "{FFFFFF}clave", "{FFFFFF}Ahora introduce una {FE9A2E}clave{FFFFFF} con la cual ingresaras en tu cuenta:\n", "Continuar", "Volver");
	return 1;
}

Dialog:Registrarse3(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, Registrarse2, DIALOG_STYLE_INPUT, "{FFFFFF}Email", "{FFFFFF}Introduce tu {FE9A2E}correo electronico{FFFFFF}, el cual te identificara en la base de datos:\n", "Continuar", "Volver");
	if (strlen(inputtext) < 5)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "La {FE9A2E}clave{FFFFFF} no puede ser inferior a 4 caracteres.");
		Dialog_Show(playerid, Registrarse3, DIALOG_STYLE_INPUT, "{FFFFFF}clave", "{FFFFFF}Ahora introduce una {FE9A2E}clave{FFFFFF} con la cual ingresaras en tu cuenta:\n", "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) > 18)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "La {FE9A2E}clave{FFFFFF} no puede sobrepasar los 18 caracteres.");
		Dialog_Show(playerid, Registrarse3, DIALOG_STYLE_INPUT, "{FFFFFF}Clave", "{FFFFFF}Ahora introduce una {FE9A2E}clave{FFFFFF} con la cual ingresaras en tu cuenta:\n", "Continuar", "Volver");
		return 1;
	}
	foreach(new p: Player) if (conectado[p] == 1 && strcmp(inputtext, InfoCuenta[p][jNombre], true) == 0)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "Ya han registrado o ingresado con el nombre de usuario que usaste, fuiste expulsado.");
		SetTimerEx("TimerKICK", 1000, false, "d", playerid);
		SendPlayerChatMessage(p, COLOR_YELLOW, "Alguien intento entrar hace poco a tu cuenta.");
		return 1;
	}
	conectado[playerid] = 1;
	alm(name_password[playerid], inputtext);
	
	//hash password
	Loop(e, 10, 0) { InfoCuenta[playerid][jSalt][e] = random(79) + 47; }
	InfoCuenta[playerid][jSalt][10] = 0;
	SHA256_PassHash(inputtext, InfoCuenta[playerid][jSalt], InfoCuenta[playerid][jClave], 65);
	
	//dialogo
	new dialog[1028];
	strcat(dialog, "1. Cual es el apellido de soltera de mi madre?\n");
	strcat(dialog, "2. Cual es el nombre de mi mascota?\n");
	strcat(dialog, "3. Como se llama mi primer amor?\n");
	strcat(dialog, "4. Cual es la fecha del cumplea�os de mi hermano(a)?\n");
	strcat(dialog, "5. En que colegio estudie en primaria?\n");
	strcat(dialog, "6. Cual es el nombre de mi mejor amigo?");
	Dialog_Show(playerid, Registrarse4, DIALOG_STYLE_LIST, "{FFFFFF}Ganton Stories A2F", dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Registrarse4(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, Registrarse3, DIALOG_STYLE_INPUT, "{FFFFFF}clave", "{FFFFFF}Ahora introduce una {FE9A2E}clave{FFFFFF} con la cual ingresaras en tu cuenta:\n", "Continuar", "Volver");
	switch (listitem)
	{
		case 0: alm(InfoCuenta[playerid][jPreguntaSeguridad], "Cual es el apellido de soltera de mi madre?");
		case 1: alm(InfoCuenta[playerid][jPreguntaSeguridad], "Cual es el nombre de mi mascota?");
		case 2: alm(InfoCuenta[playerid][jPreguntaSeguridad], "Como se llama mi primer amor?");
		case 3: alm(InfoCuenta[playerid][jPreguntaSeguridad], "Cual es la fecha del cumplea�os de mi hermano(a)?");
		case 4: alm(InfoCuenta[playerid][jPreguntaSeguridad], "En que colegio estudie en primaria?");
		case 5: alm(InfoCuenta[playerid][jPreguntaSeguridad], "Cual es el nombre de mi mejor amigo?");
	}
	new dialog[1028], gformat[250];
	strcat(dialog, "{FFFFFF}Bien has escogido como pregunta de seguridad:\n");
	format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
	strcat(dialog, gformat);
	strcat(dialog, "{FFFFFF}Ahora introduce la {00CCFF}respuesta de seguridad{FFFFFF}, recuerda tener esto de memoria,\n\
	{FFFFFF}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
	Dialog_Show(playerid, Registrarse5, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Registrarse5(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		alm(InfoCuenta[playerid][jPreguntaSeguridad], "ninguna");
		new dialog[1028];
		strcat(dialog, "1. Cual es el apellido de soltera de mi madre?\n");
		strcat(dialog, "2. Cual es el nombre de mi mascota?\n");
		strcat(dialog, "3. Como se llama mi primer amor?\n");
		strcat(dialog, "4. Cual es la fecha del cumplea�os de mi hermano(a)?\n");
		strcat(dialog, "5. En que colegio estudie en primaria?\n");
		strcat(dialog, "6. Cual es el nombre de mi mejor amigo?");
		Dialog_Show(playerid, Registrarse4, DIALOG_STYLE_LIST, "{FFFFFF}Pregunta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) < 5)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "No puedes tener una respuesta con menos de 4 caracteres.");
		new dialog[1028], gformat[250];
		strcat(dialog, "{FFFFFF}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{FFFFFF}Ahora introduce la {00CCFF}respuesta de seguridad{FFFFFF}, recuerda tener esto de memoria,\n\
		{FFFFFF}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Registrarse5, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) > 33)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "No puedes tener una respuesta con mas de 32 caracteres.");
		new dialog[1028], gformat[250];
		strcat(dialog, "{FFFFFF}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{FFFFFF}Ahora introduce la {00CCFF}respuesta de seguridad{FFFFFF}, recuerda tener esto de memoria,\n\
		{FFFFFF}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Registrarse5, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	alm(InfoCuenta[playerid][jRespuestaSeguridad], inputtext);
	new dialog[2056], gformat[320];
	strcat(dialog, "{FFFFFF}Comprueba que los datos sean los correctos, cuando confirmes pasaras a realizar una prueba de rol.\n\n");
	format(gformat, sizeof gformat, "{FE9A2E}Nombre de usuario: {FFFFFF}%s\n", InfoCuenta[playerid][jNombre]); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{00CC00}Correo electronico: {FFFFFF}%s\n", InfoCuenta[playerid][jEmail]); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{FFBF00}Pregunta de seguridad: {FFFFFF}%s\n", InfoCuenta[playerid][jPreguntaSeguridad]); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{00CCFF}Respuesta de seguridad: {FFFFFF}%s\n", InfoCuenta[playerid][jRespuestaSeguridad]); strcat(dialog, gformat);
	Dialog_Show(playerid, Registrarse6, DIALOG_STYLE_MSGBOX, "{FFFFFF}Confirmacion", dialog, "Confirmar", "Volver");
	return 1;
}

Dialog:Registrarse6(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		alm(InfoCuenta[playerid][jRespuestaSeguridad], "ninguna");
		new dialog[1028], gformat[250];
		strcat(dialog, "{FFFFFF}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{FFFFFF}Ahora introduce la {00CCFF}respuesta de seguridad{FFFFFF}, recuerda tener esto de memoria,\n\
		{FFFFFF}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Registrarse5, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	//if (Active_Rol != 0) PreguntaTestRol(playerid, 1, 0);
	else
	{
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
	}
	return 1;
}