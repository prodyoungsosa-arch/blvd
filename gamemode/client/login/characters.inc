new ActorLogin[MAX_PLAYERS];
new ActorLoginHombre[MAX_PLAYERS];
new ActorLoginMujer[MAX_PLAYERS];
new PersonajeSeleccionado[MAX_PLAYERS];
new bool:SlotDisponible[MAX_PLAYERS][4];
new Act_Personajes[MAX_PLAYERS], 
SeleccionoPJ1[MAX_PLAYERS], 
SeleccionoPJ2[MAX_PLAYERS], 
SeleccionoPJ3[MAX_PLAYERS], 
SeleccionoPJ4[MAX_PLAYERS], 
SeleccionoPJ5[MAX_PLAYERS];

IsValidRoleplayName(const name[])
{
	if( strlen( name ) < 6 )
		return 0;

    for( new i = 0; i < strlen( name ); i++ )
    {
		if( !( ( name[i] >= 'a' && name[i] <= 'z' ) || ( name[i] >= 'A' && name[i] <= 'Z' ) || name[i] == '_' ) )
                return 0;
	}

	new
		d = strfind( name, "_" );

    if( d == -1 )
		return 0;

    if( strfind( name, "_", false, d + 1 ) != -1 )
		return 0;

	new
		pname[10];
    strmid( pname, name, 0, d, sizeof pname );

	new
		surname[10];
    strmid( surname, name, d + 1, strlen( name ), sizeof surname);

    if( strlen( pname ) < 3 || strlen( surname ) < 3 )
		return 0;

	if( !( pname[0] >= 'A' && pname[0] <= 'Z' ) )
		return 0;

    if( !( surname[0] >= 'A' && surname[0]<='Z' ) )
		return 0;

    for( new i = 1; i < strlen( pname ); i++ )
    {
        if( !( pname[i] >= 'a' && pname[i] <= 'z' ) )
			return 0;
    }

    for( new i = 1; i < strlen( surname ); i++ )
    {
        if( !( surname[i] >= 'a' && surname[i] <= 'z' ) )
			return 0;
	}

    return 1;
}

Dialog:ShowRespuesta(playerid, response, listitem, inputtext[])
{
	if (!response) return Kick(playerid);
	if (!strcmp(InfoCuenta[playerid][jRespuestaSeguridad], inputtext, true))
	{
		VerPersonajes(playerid);
	}
	else
	{
		IntentosRespuesta[playerid]--;
		if (IntentosRespuesta[playerid] == 0)
		{
			SendPlayerChatMessage(playerid, COLOR_GENERAL, "Has sido expulsado del servidor, no respondiste la pregunta de seguridad correctamente.");
			SetTimerEx("TimerKICK", 1000, false, "d", playerid);
			IntentosRespuesta[playerid] = 0;
			return 1;
		}
		SendPlayerChatMessage(playerid, COLOR_GENERAL, "Respuesta incorrecta, intenta de nuevo.");
		new dialog[1580], gformat[250];
		strcat(dialog, "{EBEBEB}Nuestro sistema ha detectado que la {FF2F2F}IP{EBEBEB} que estas usando es distinta a la de tu ultima sesion.\n");
		strcat(dialog, "{EBEBEB}Para continuar con la sesion de tu cuenta, necesitaremos que respondas la pregunta de seguridad.\n\n");
		format(gformat, sizeof gformat, "{EBEBEB}Pregunta de seguridad: {FFBF00}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		format(gformat, sizeof gformat, "{EBEBEB}Si te equivocas puedes intentarlo {DAA838}%d{EBEBEB} veces mas.\n", IntentosRespuesta[playerid]);
		strcat(dialog, gformat);
		Dialog_Show(playerid, ShowRespuesta, DIALOG_STYLE_INPUT, "{FFFFFF}Medida de seguridad", dialog, "Continuar", "Salir");
	}
	return 1;
}

Dialog:ShowPregunta(playerid, response, listitem, inputtext[])
{
	if (!response) return Kick(playerid);
	new dialog[1028];
	strcat(dialog, "1. ¿Cual es el apellido de soltera de mi madre?\n");
	strcat(dialog, "2. ¿Cual es el nombre de mi mascota?\n");
	strcat(dialog, "3. ¿Como se llama mi primer amor?\n");
	strcat(dialog, "4. ¿Cual es la fecha del cumpleaños de mi hermano(a)?\n");
	strcat(dialog, "5. ¿En que colegio estudie en primaria?\n");
	strcat(dialog, "6. ¿Cual es el nombre de mi mejor amigo?");
	Dialog_Show(playerid, Show2Pregunta, DIALOG_STYLE_LIST, "{FFFFFF}Lista de preguntas", dialog, "Continuar", "Salir");
	return 1;
}

Dialog:Show2Pregunta(playerid, response, listitem, inputtext[])
{
	if (!response) return Kick(playerid);
	switch (listitem)
	{
		case 0: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿Cual es el apellido de soltera de mi madre?");
		case 1: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿Cual es el nombre de mi mascota?");
		case 2: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿Como se llama mi primer amor?");
		case 3: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿Cual es la fecha del cumpleaï¿½os de mi hermano(a)?");
		case 4: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿En que colegio estudie en primaria?");
		case 5: alm(InfoCuenta[playerid][jPreguntaSeguridad], "¿ual es el nombre de mi mejor amigo?");
	}
	new dialog[1028], gformat[250];
	strcat(dialog, "{EBEBEB}Bien has escogido como pregunta de seguridad:\n");
	format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
	strcat(dialog, gformat);
	strcat(dialog, "{EBEBEB}Ahora introduce la {00CCFF}respuesta de seguridad{EBEBEB}, recuerda tener esto de memoria,\n\
	{EBEBEB}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
	Dialog_Show(playerid, Show3Pregunta, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Show3Pregunta(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		alm(InfoCuenta[playerid][jPreguntaSeguridad], "ninguna");
		new dialog[1028];
		strcat(dialog, "1. ¿Cual es el apellido de soltera de mi madre?\n");
		strcat(dialog, "2. ¿Cual es el nombre de mi mascota?\n");
		strcat(dialog, "3. ¿Como se llama mi primer amor?\n");
		strcat(dialog, "4. ¿Cual es la fecha del cumpleaños de mi hermano(a)?\n");
		strcat(dialog, "5. ¿En que colegio estudie en primaria?\n");
		strcat(dialog, "6. ¿Cual es el nombre de mi mejor amigo?");
		Dialog_Show(playerid, Show2Pregunta, DIALOG_STYLE_LIST, "{FFFFFF}Lista de preguntas", dialog, "Continuar", "Salir");
		return 1;
	}
	if (strlen(inputtext) < 5)
	{
		SendPlayerChatMessage(playerid, 0xccccccff, "No puedes tener una respuesta con menos de 4 caracteres.");
		new dialog[1028], gformat[250];
		strcat(dialog, "{EBEBEB}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{EBEBEB}Ahora introduce la {00CCFF}respuesta de seguridad{EBEBEB}, recuerda tener esto de memoria,\n\
		{EBEBEB}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Show3Pregunta, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	if (strlen(inputtext) > 33)
	{
		SendPlayerChatMessage(playerid, 0xccccccff, "No puedes tener una respuesta con mas de 32 caracteres.");
		new dialog[1028], gformat[250];
		strcat(dialog, "{EBEBEB}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{EBEBEB}Ahora introduce la {00CCFF}respuesta de seguridad{EBEBEB}, recuerda tener esto de memoria,\n\
		{EBEBEB}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Show3Pregunta, DIALOG_STYLE_INPUT, "{FFFFFF}Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	alm(InfoCuenta[playerid][jRespuestaSeguridad], inputtext);
	new dialog[1028], gformat[250];
	strcat(dialog, "{EBEBEB}Perfecto, para terminar verifica que este todo en orden.\n\n");
	format(gformat, sizeof gformat, "{FFBF00}Pregunta de seguridad: {EBEBEB}%s\n", InfoCuenta[playerid][jPreguntaSeguridad]);
	strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{00CCFF}Respuesta de seguridad: {EBEBEB}%s\n\n", InfoCuenta[playerid][jRespuestaSeguridad]);
	strcat(dialog, gformat);
	strcat(dialog, "{EBEBEB}Si todo esta bien presiona '{FF2F2F}Confirmar{EBEBEB}' para ingresar al servidor.\n");
	Dialog_Show(playerid, Show4Pregunta, DIALOG_STYLE_MSGBOX, "{FFFFFF}Confirmacion de seguridad", dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Show4Pregunta(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		alm(InfoCuenta[playerid][jRespuestaSeguridad], "ninguna");
		new dialog[1028], gformat[250];
		strcat(dialog, "{EBEBEB}Bien has escogido como pregunta de seguridad:\n");
		format(gformat, sizeof gformat, "{FF2F2F}%s\n\n", InfoCuenta[playerid][jPreguntaSeguridad]);
		strcat(dialog, gformat);
		strcat(dialog, "{EBEBEB}Ahora introduce la {00CCFF}respuesta de seguridad{EBEBEB}, recuerda tener esto de memoria,\n\
		{EBEBEB}dado que en un futuro la necesitaras para ingresar a tu cuenta.\n");
		Dialog_Show(playerid, Show3Pregunta, DIALOG_STYLE_INPUT, "Respuesta de seguridad", dialog, "Continuar", "Volver");
		return 1;
	}
	VerPersonajes(playerid);
	new offquery[512];
	mysql_format(db_samp, offquery, sizeof offquery, "UPDATE cuentas SET PreguntaSeguridad = '%e', RespuestaSeguridad = '%e' WHERE ID = '%d'", InfoCuenta[playerid][jPreguntaSeguridad], InfoCuenta[playerid][jRespuestaSeguridad], InfoCuenta[playerid][jID]);
	mysql_tquery(db_samp, offquery);
	return 1;
}

SetCameraIntroPJ(playerid)
{
	InterpolateCameraPos(playerid, 300.720367, -1629.248413, 74.230682, 300.720367, -1629.248413, 74.230682, 7000);
	InterpolateCameraLookAt(playerid, 303.759643, -1632.941406, 72.772994, 303.759643, -1632.941406, 72.772994, 7000);	
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, playerid + 10);
	return 1;
}

VerPersonajes(playerid)
{
	new query[310];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE CuentaID = '%d'", InfoCuenta[playerid][jID]);
	mysql_tquery(db_samp, query, "OnShowCharacters", "d", playerid);
	Act_Personajes[playerid] = 1;
	SetCameraIntroPJ(playerid);
	return 1;
}

forward OnShowCharacters(playerid);
public OnShowCharacters(playerid)
{
	if (cache_num_rows() > 0)
	{
		new gformat[320], pj1[32], pj2[32], pj3[32], pj4[32], count = 0;
		
		SlotDisponible[playerid][0] = false;
		SlotDisponible[playerid][1] = false;
		SlotDisponible[playerid][2] = false;
		SlotDisponible[playerid][3] = false;

		for(new i = 0; i < 50; i++) { PlayerTextDrawShow(playerid, p_tdSeleccionarPJ[playerid][i]); }
		
		Loop(id, cache_num_rows(), 0)
		{
			new pDI, pName[MAX_PLAYER_NAME];
			rebel_int(id, "ID", pDI);
			rebel_string(id, "Nombre_Apellido", pName, MAX_PLAYER_NAME);
		
			count++;										
			SelectTextDraw(playerid, 0xffc41cFF);

			if (count == 1)
			{
				format(pj1, sizeof pj1, "%s", pName);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][35], pj1);
				format(gformat, sizeof gformat, "id_rows%d", count);
				SetPVarInt(playerid, gformat, pDI);	
				SeleccionoPJ1[playerid] = pDI;	
				new SkinPlayer, fecha[32];
				rebel_int(id, "Skin", SkinPlayer);
				rebel_string(id, "UltimaConexion", fecha, 32);
				strdel(fecha, 0, 10);
				format(fecha, sizeof(fecha), "Ultimo acceso:%s", fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][36], fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][34], "1");
			}
			else if (count == 2)
			{
				format(pj2, sizeof pj2, "%s", pName);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][39], pj2);
				format(gformat, sizeof gformat, "id_rows%d", count);
				SetPVarInt(playerid, gformat, pDI);	
				SeleccionoPJ2[playerid] = pDI;
				new SkinPlayer, fecha[32];
				rebel_int(id, "Skin", SkinPlayer);
				rebel_string(id, "UltimaConexion", fecha, 32);
				strdel(fecha, 0, 10);
				format(fecha, sizeof(fecha), "Ultimo acceso:%s", fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][40], fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][38], "2");
			}
			else if (count == 3)
			{
				format(pj3, sizeof pj3, "%s", pName);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][43], pj3);
				format(gformat, sizeof gformat, "id_rows%d", count);
				SetPVarInt(playerid, gformat, pDI);	
				SeleccionoPJ3[playerid] = pDI;
				new SkinPlayer, fecha[32];
				rebel_int(id, "Skin", SkinPlayer);
				rebel_string(id, "UltimaConexion", fecha, 32);
				strdel(fecha, 0, 10);
				format(fecha, sizeof(fecha), "Ultimo acceso: %s", fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][44], fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][42], "3");
			}
			else if (count == 4)
			{
				format(pj4, sizeof pj4, "%s", pName);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][47], pj4);
				format(gformat, sizeof gformat, "id_rows%d", count);
				SetPVarInt(playerid, gformat, pDI);	
				SeleccionoPJ4[playerid] = pDI;
				new SkinPlayer, fecha[32];
				rebel_int(id, "Skin", SkinPlayer);
				rebel_string(id, "UltimaConexion", fecha, 32);
				strdel(fecha, 0, 10);
				format(fecha, sizeof(fecha), "Ultimo acceso: %s", fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][48], fecha);
				PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][46], "4");
			}
		}
		
		SetPVarInt(playerid, "max_pjs", count);
		
		if (count < 1)
		{
			SlotDisponible[playerid][0] = true;
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][35], "DISPONIBLE");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][36], "Slot disponible");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][34], "?");
		}
		if (count < 2)
		{
			SlotDisponible[playerid][1] = true;
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][39], "DISPONIBLE");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][40], "Slot disponible");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][38], "?");
		}
		if (count < 3)
		{
			SlotDisponible[playerid][2] = true;
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][43], "DISPONIBLE");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][44], "Slot disponible");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][42], "?");
		}
		if (count < 4)
		{
			SlotDisponible[playerid][3] = true;
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][47], "DISPONIBLE");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][48], "Slot disponible");
			PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][46], "?");
		}
	}
	else
	{
		SlotDisponible[playerid][0] = true;
		SlotDisponible[playerid][1] = true;
		SlotDisponible[playerid][2] = true;
		SlotDisponible[playerid][3] = true;
		
		SelectTextDraw(playerid, 0xffc41cFF);
		for(new i = 0; i < 50; i++) { PlayerTextDrawShow(playerid, p_tdSeleccionarPJ[playerid][i]); }

		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][35], "DISPONIBLE");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][36], "Slot disponible");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][34], "?");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][39], "DISPONIBLE");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][40], "Slot disponible");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][38], "?");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][43], "DISPONIBLE");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][44], "Slot disponible");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][42], "?");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][47], "DISPONIBLE");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][48], "Slot disponible");
		PlayerTextDrawSetString(playerid, p_tdSeleccionarPJ[playerid][46], "?");
		
		Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {DAA838}Creacion", "{FFFFFF}Estas a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {DAA838}Nombre_Apellido{FFFFFF} (Ejemplo: {ebebeb}Jose_Paredes{FFFFFF})\n", "Continuar", "Volver");
		SetPVarInt(playerid, "QhacerPj", 1);
		SetPVarInt(playerid, "max_pjs", 1);
	}
	return 1;
}

funcion SeleccionarPersonaje(playerid, personaje)
{
	new query[170];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE ID = '%d'", personaje);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0)
	{
		rebel_int(0, "ID", InfoPersonaje[playerid][pID]);
		rebel_string(0, "Nombre_Apellido", InfoPersonaje[playerid][pNombre_Apellido], MAX_PLAYER_NAME);
		rebel_string(0, "Codigo", InfoPersonaje[playerid][pCodigo], 24);
		rebel_int(0, "CuentaID", InfoPersonaje[playerid][pCuentaID]);
		rebel_float(0, "PosicionX", InfoPersonaje[playerid][pPosicionX]);
		rebel_float(0, "PosicionY", InfoPersonaje[playerid][pPosicionY]);
		rebel_float(0, "PosicionZ", InfoPersonaje[playerid][pPosicionZ]);
		rebel_float(0, "PosicionR", InfoPersonaje[playerid][pPosicionR]);
		rebel_int(0, "Interior", InfoPersonaje[playerid][pInterior]);
		rebel_int(0, "VirtualWorld", InfoPersonaje[playerid][pVirtualWorld]);
		rebel_float(0, "Vida", InfoPersonaje[playerid][pVida]);
		rebel_float(0, "Chaleco", InfoPersonaje[playerid][pChaleco]);
		rebel_int(0, "Skin", InfoPersonaje[playerid][pSkin]);
		rebel_int(0, "FugaoVicio", InfoPersonaje[playerid][pHorasOn]);
		rebel_int(0, "Sexo", InfoPersonaje[playerid][pSexo]);
		rebel_int(0, "Edad", InfoPersonaje[playerid][pEdad]);
		rebel_int(0, "Ciudad", InfoPersonaje[playerid][pCiudad]);
		rebel_int(0, "EstiloPelea", InfoPersonaje[playerid][pEstiloPelea]);
		rebel_int(0, "BolosUwU", InfoPersonaje[playerid][pDinero]);
		rebel_int(0, "BanescoOwO", InfoPersonaje[playerid][pBanco]);
		rebel_int(0, "LiderFaccion", InfoPersonaje[playerid][pLider]);
		rebel_int(0, "MiembroFaccion", InfoPersonaje[playerid][pMiembro]);
		rebel_int(0, "Rango", InfoPersonaje[playerid][pRango]);
		rebel_int(0, "Bolsillo_1", InfoPersonaje[playerid][pBolsillo][0]);
		rebel_int(0, "Cantidad_bolsillo_1", InfoPersonaje[playerid][pBolsilloCant][0]);
		rebel_int(0, "Bolsillo_2", InfoPersonaje[playerid][pBolsillo][1]);
		rebel_int(0, "Cantidad_bolsillo_2", InfoPersonaje[playerid][pBolsilloCant][1]);
		rebel_int(0, "Bolsillo_3", InfoPersonaje[playerid][pBolsillo][2]);
		rebel_int(0, "Cantidad_bolsillo_3", InfoPersonaje[playerid][pBolsilloCant][2]);
		rebel_int(0, "Bolsillo_4", InfoPersonaje[playerid][pBolsillo][3]);
		rebel_int(0, "Cantidad_bolsillo_4", InfoPersonaje[playerid][pBolsilloCant][3]);
		rebel_int(0, "Bolsillo_5", InfoPersonaje[playerid][pBolsillo][4]);
		rebel_int(0, "Cantidad_bolsillo_5", InfoPersonaje[playerid][pBolsilloCant][4]);
		rebel_int(0, "Bolsillo_6", InfoPersonaje[playerid][pBolsillo][5]);
		rebel_int(0, "Cantidad_bolsillo_6", InfoPersonaje[playerid][pBolsilloCant][5]);
		rebel_int(0, "Bolsillo_7", InfoPersonaje[playerid][pBolsillo][6]);
		rebel_int(0, "Cantidad_bolsillo_7", InfoPersonaje[playerid][pBolsilloCant][6]);
		rebel_int(0, "Bolsillo_8", InfoPersonaje[playerid][pBolsillo][7]);
		rebel_int(0, "Cantidad_bolsillo_8", InfoPersonaje[playerid][pBolsilloCant][7]);
		rebel_int(0, "Bolsillo_9", InfoPersonaje[playerid][pBolsillo][8]);
		rebel_int(0, "Cantidad_bolsillo_9", InfoPersonaje[playerid][pBolsilloCant][8]);
		rebel_int(0, "Mano_derecha", InfoPersonaje[playerid][pManoDerecha]);
		rebel_int(0, "Cantidad_mano_derecha", InfoPersonaje[playerid][pManoDerechaCant]);
		rebel_int(0, "Mano_izquierda", InfoPersonaje[playerid][pManoIzquierda]);
		rebel_int(0, "Cantidad_mano_izquierda", InfoPersonaje[playerid][pManoIzquierdaCant]);
		rebel_int(0, "Espalda", InfoPersonaje[playerid][pEspalda]);
		rebel_int(0, "Cantidad_espalda", InfoPersonaje[playerid][pEspaldaCant]);
		rebel_int(0, "Muerto", InfoPersonaje[playerid][pMuerto]);
		rebel_int(0, "Jails", InfoPersonaje[playerid][pJails]);
		rebel_int(0, "Arrestos", InfoPersonaje[playerid][pArrestos]);
		rebel_int(0, "Sancionado", InfoPersonaje[playerid][pSancionado]);
		rebel_int(0, "TiempoSancion", InfoPersonaje[playerid][pTiempoSancion]);
		rebel_string(0, "BySancion", InfoPersonaje[playerid][pBySancion], MAX_PLAYER_NAME);
		rebel_string(0, "RazonSancion", InfoPersonaje[playerid][pRazonSancion], 128);
		rebel_int(0, "Telefono", InfoPersonaje[playerid][pTelefono]);
		rebel_int(0, "Velocimetro", InfoPersonaje[playerid][pTogVelocimetro]);
		rebel_int(0, "Licencia1", InfoPersonaje[playerid][pLicencia][0]);
		rebel_int(0, "Licencia2", InfoPersonaje[playerid][pLicencia][1]);
		rebel_int(0, "Licencia3", InfoPersonaje[playerid][pLicencia][2]);
		rebel_int(0, "Licencia4", InfoPersonaje[playerid][pLicencia][3]);
		rebel_int(0, "Licencia5", InfoPersonaje[playerid][pLicencia][4]);
		rebel_int(0, "OtakuN_N", InfoPersonaje[playerid][pBaneo]);
		rebel_int(0, "TimeBanUwU", InfoPersonaje[playerid][pTiempoBaneo]);
		rebel_string(0, "FueBan", InfoPersonaje[playerid][pCulpableBaneo], 24);
		rebel_string(0, "ReasonBanUwU", InfoPersonaje[playerid][pRazonBaneo], 256);
		rebel_string(0, "MomentBan", InfoPersonaje[playerid][pFechaBaneo], 256);
		rebel_int(0, "BlockBug", InfoPersonaje[playerid][pBlockBug]);
		rebel_int(0, "BlockG", InfoPersonaje[playerid][pTogGraffiti]);
		rebel_int(0, "Documento", InfoPersonaje[playerid][pDocumento]);
		rebel_int(0, "Habilidad1", InfoPersonaje[playerid][pHabilidad][0]);
		rebel_int(0, "Habilidad2", InfoPersonaje[playerid][pHabilidad][1]);
		rebel_int(0, "Habilidad3", InfoPersonaje[playerid][pHabilidad][2]);
		rebel_int(0, "Habilidad4", InfoPersonaje[playerid][pHabilidad][3]);
		rebel_int(0, "Habilidad5", InfoPersonaje[playerid][pHabilidad][4]);
		rebel_int(0, "Habilidad6", InfoPersonaje[playerid][pHabilidad][5]);
		rebel_int(0, "Payday", InfoPersonaje[playerid][pPayday]);
		rebel_int(0, "Estrellas", InfoPersonaje[playerid][pEstrellas]);
		rebel_int(0, "LimiteRobos", InfoPersonaje[playerid][pLimiteRobos]);
		rebel_int(0, "Frecuencia_radio", InfoPersonaje[playerid][pFrecuencia_radio]);
		rebel_int(0, "TipoSpawn", InfoPersonaje[playerid][pSpawnTipo]);
		rebel_string(0, "EstadoYo", InfoPersonaje[playerid][pEstadoYo], 128);
		rebel_string(0, "NombreContacto1", nombre_contacto[playerid][0], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto1", InfoPersonaje[playerid][pNumeroContacto][0]);
		rebel_string(0, "NombreContacto2", nombre_contacto[playerid][1], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto2", InfoPersonaje[playerid][pNumeroContacto][1]);
		rebel_string(0, "NombreContacto3", nombre_contacto[playerid][2], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto3", InfoPersonaje[playerid][pNumeroContacto][2]);
		rebel_string(0, "NombreContacto4", nombre_contacto[playerid][3], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto4", InfoPersonaje[playerid][pNumeroContacto][3]);
		rebel_string(0, "NombreContacto5", nombre_contacto[playerid][4], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto5", InfoPersonaje[playerid][pNumeroContacto][4]);
		rebel_string(0, "NombreContacto6", nombre_contacto[playerid][5], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto6", InfoPersonaje[playerid][pNumeroContacto][5]);
		rebel_string(0, "NombreContacto7", nombre_contacto[playerid][6], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto7", InfoPersonaje[playerid][pNumeroContacto][6]);
		rebel_string(0, "NombreContacto8", nombre_contacto[playerid][7], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto8", InfoPersonaje[playerid][pNumeroContacto][7]);
		rebel_string(0, "NombreContacto9", nombre_contacto[playerid][8], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto9", InfoPersonaje[playerid][pNumeroContacto][8]);
		rebel_string(0, "NombreContacto10", nombre_contacto[playerid][9], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto10", InfoPersonaje[playerid][pNumeroContacto][9]);
		rebel_string(0, "NombreContacto11", nombre_contacto[playerid][10], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto11", InfoPersonaje[playerid][pNumeroContacto][10]);
		rebel_string(0, "NombreContacto12", nombre_contacto[playerid][11], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto12", InfoPersonaje[playerid][pNumeroContacto][11]);
		rebel_string(0, "NombreContacto13", nombre_contacto[playerid][12], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto13", InfoPersonaje[playerid][pNumeroContacto][12]);
		rebel_string(0, "NombreContacto14", nombre_contacto[playerid][13], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto14", InfoPersonaje[playerid][pNumeroContacto][13]);
		rebel_string(0, "NombreContacto15", nombre_contacto[playerid][14], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto15", InfoPersonaje[playerid][pNumeroContacto][14]);
		rebel_string(0, "NombreContacto16", nombre_contacto[playerid][15], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto16", InfoPersonaje[playerid][pNumeroContacto][15]);
		rebel_string(0, "NombreContacto17", nombre_contacto[playerid][16], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto17", InfoPersonaje[playerid][pNumeroContacto][16]);
		rebel_string(0, "NombreContacto18", nombre_contacto[playerid][17], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto18", InfoPersonaje[playerid][pNumeroContacto][17]);
		rebel_string(0, "NombreContacto19", nombre_contacto[playerid][18], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto19", InfoPersonaje[playerid][pNumeroContacto][18]);
		rebel_string(0, "NombreContacto20", nombre_contacto[playerid][19], MAX_PLAYER_NAME);
		rebel_int(0, "NumeroContacto20", InfoPersonaje[playerid][pNumeroContacto][19]);
		rebel_int(0, "JobSkin", InfoPersonaje[playerid][pJobSkin]);
		rebel_int(0, "RestriccionRobo", InfoPersonaje[playerid][pRestriccionRobo]);
		rebel_string(0, "FechaRegistro", InfoPersonaje[playerid][pFechaRegistro], 256);
		rebel_string(0, "UltimaConexion", InfoPersonaje[playerid][pUltimaConexion], 256);

		//accesorios
		new gformat[512];
		rebel_string(0, "Toy1", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][0], InfoPersonaje[playerid][ptHueso][0], InfoPersonaje[playerid][ptPosX][0], InfoPersonaje[playerid][ptPosY][0], InfoPersonaje[playerid][ptPosZ][0], InfoPersonaje[playerid][ptRotX][0],
		InfoPersonaje[playerid][ptRotY][0], InfoPersonaje[playerid][ptRotZ][0], InfoPersonaje[playerid][ptScaleX][0], InfoPersonaje[playerid][ptScaleY][0], InfoPersonaje[playerid][ptScaleZ][0], InfoPersonaje[playerid][ptColocado][0]);
		rebel_string(0, "Toy2", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][1], InfoPersonaje[playerid][ptHueso][1], InfoPersonaje[playerid][ptPosX][1], InfoPersonaje[playerid][ptPosY][1], InfoPersonaje[playerid][ptPosZ][1], InfoPersonaje[playerid][ptRotX][1],
		InfoPersonaje[playerid][ptRotY][1], InfoPersonaje[playerid][ptRotZ][1], InfoPersonaje[playerid][ptScaleX][1], InfoPersonaje[playerid][ptScaleY][1], InfoPersonaje[playerid][ptScaleZ][1], InfoPersonaje[playerid][ptColocado][1]);
		rebel_string(0, "Toy3", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][2], InfoPersonaje[playerid][ptHueso][2], InfoPersonaje[playerid][ptPosX][2], InfoPersonaje[playerid][ptPosY][2], InfoPersonaje[playerid][ptPosZ][2], InfoPersonaje[playerid][ptRotX][2],
		InfoPersonaje[playerid][ptRotY][2], InfoPersonaje[playerid][ptRotZ][2], InfoPersonaje[playerid][ptScaleX][2], InfoPersonaje[playerid][ptScaleY][2], InfoPersonaje[playerid][ptScaleZ][2], InfoPersonaje[playerid][ptColocado][2]);
		rebel_string(0, "Toy4", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][3], InfoPersonaje[playerid][ptHueso][3], InfoPersonaje[playerid][ptPosX][3], InfoPersonaje[playerid][ptPosY][3], InfoPersonaje[playerid][ptPosZ][3], InfoPersonaje[playerid][ptRotX][3],
		InfoPersonaje[playerid][ptRotY][3], InfoPersonaje[playerid][ptRotZ][3], InfoPersonaje[playerid][ptScaleX][3], InfoPersonaje[playerid][ptScaleY][3], InfoPersonaje[playerid][ptScaleZ][3], InfoPersonaje[playerid][ptColocado][3]);
		rebel_string(0, "Toy5", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][4], InfoPersonaje[playerid][ptHueso][4], InfoPersonaje[playerid][ptPosX][4], InfoPersonaje[playerid][ptPosY][4], InfoPersonaje[playerid][ptPosZ][4], InfoPersonaje[playerid][ptRotX][4],
		InfoPersonaje[playerid][ptRotY][4], InfoPersonaje[playerid][ptRotZ][4], InfoPersonaje[playerid][ptScaleX][4], InfoPersonaje[playerid][ptScaleY][4], InfoPersonaje[playerid][ptScaleZ][4], InfoPersonaje[playerid][ptColocado][4]);
		rebel_string(0, "Toy6", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][5], InfoPersonaje[playerid][ptHueso][5], InfoPersonaje[playerid][ptPosX][5], InfoPersonaje[playerid][ptPosY][5], InfoPersonaje[playerid][ptPosZ][5], InfoPersonaje[playerid][ptRotX][5],
		InfoPersonaje[playerid][ptRotY][5], InfoPersonaje[playerid][ptRotZ][5], InfoPersonaje[playerid][ptScaleX][5], InfoPersonaje[playerid][ptScaleY][5], InfoPersonaje[playerid][ptScaleZ][5], InfoPersonaje[playerid][ptColocado][5]);
		rebel_string(0, "Toy7", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][6], InfoPersonaje[playerid][ptHueso][6], InfoPersonaje[playerid][ptPosX][6], InfoPersonaje[playerid][ptPosY][6], InfoPersonaje[playerid][ptPosZ][6], InfoPersonaje[playerid][ptRotX][6],
		InfoPersonaje[playerid][ptRotY][6], InfoPersonaje[playerid][ptRotZ][6], InfoPersonaje[playerid][ptScaleX][6], InfoPersonaje[playerid][ptScaleY][6], InfoPersonaje[playerid][ptScaleZ][6], InfoPersonaje[playerid][ptColocado][6]);
		rebel_string(0, "Toy8", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][7], InfoPersonaje[playerid][ptHueso][7], InfoPersonaje[playerid][ptPosX][7], InfoPersonaje[playerid][ptPosY][7], InfoPersonaje[playerid][ptPosZ][7], InfoPersonaje[playerid][ptRotX][7],
		InfoPersonaje[playerid][ptRotY][7], InfoPersonaje[playerid][ptRotZ][7], InfoPersonaje[playerid][ptScaleX][7], InfoPersonaje[playerid][ptScaleY][7], InfoPersonaje[playerid][ptScaleZ][7], InfoPersonaje[playerid][ptColocado][7]);
		rebel_string(0, "Toy9", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][8], InfoPersonaje[playerid][ptHueso][8], InfoPersonaje[playerid][ptPosX][8], InfoPersonaje[playerid][ptPosY][8], InfoPersonaje[playerid][ptPosZ][8], InfoPersonaje[playerid][ptRotX][8],
		InfoPersonaje[playerid][ptRotY][8], InfoPersonaje[playerid][ptRotZ][8], InfoPersonaje[playerid][ptScaleX][8], InfoPersonaje[playerid][ptScaleY][8], InfoPersonaje[playerid][ptScaleZ][8], InfoPersonaje[playerid][ptColocado][8]);
		rebel_string(0, "Toy10", gformat, 512);
		sscanf(gformat, "p<|>ddfffffffffd",
		InfoPersonaje[playerid][ptModelo][9], InfoPersonaje[playerid][ptHueso][9], InfoPersonaje[playerid][ptPosX][9], InfoPersonaje[playerid][ptPosY][9], InfoPersonaje[playerid][ptPosZ][9], InfoPersonaje[playerid][ptRotX][9],
		InfoPersonaje[playerid][ptRotY][9], InfoPersonaje[playerid][ptRotZ][9], InfoPersonaje[playerid][ptScaleX][9], InfoPersonaje[playerid][ptScaleY][9], InfoPersonaje[playerid][ptScaleZ][9], InfoPersonaje[playerid][ptColocado][9]);
		rebel_int(0, "Cinturon_1", InfoPersonaje[playerid][pCinturon][0]);
		rebel_int(0, "Cantidad_cinturon_1", InfoPersonaje[playerid][pCinturonCant][0]);
		rebel_int(0, "Cinturon_2", InfoPersonaje[playerid][pCinturon][1]);
		rebel_int(0, "Cantidad_cinturon_2", InfoPersonaje[playerid][pCinturonCant][1]);
		rebel_int(0, "Cinturon_3", InfoPersonaje[playerid][pCinturon][2]);
		rebel_int(0, "Cantidad_cinturon_3", InfoPersonaje[playerid][pCinturonCant][2]);
		rebel_int(0, "Cinturon_4", InfoPersonaje[playerid][pCinturon][3]);
		rebel_int(0, "Cantidad_cinturon_4", InfoPersonaje[playerid][pCinturonCant][3]);
		rebel_int(0, "Cinturon_5", InfoPersonaje[playerid][pCinturon][4]);
		rebel_int(0, "Cantidad_cinturon_5", InfoPersonaje[playerid][pCinturonCant][4]);
		rebel_int(0, "Cinturon_6", InfoPersonaje[playerid][pCinturon][5]);
		rebel_int(0, "Cantidad_cinturon_6", InfoPersonaje[playerid][pCinturonCant][5]);
		rebel_int(0, "ColorToy1", InfoPersonaje[playerid][ptColor][0]);
		rebel_int(0, "ColorToy2", InfoPersonaje[playerid][ptColor][1]);
		rebel_int(0, "ColorToy3", InfoPersonaje[playerid][ptColor][2]);
		rebel_int(0, "ColorToy4", InfoPersonaje[playerid][ptColor][3]);
		rebel_int(0, "ColorToy5", InfoPersonaje[playerid][ptColor][4]);
		rebel_int(0, "ColorToy6", InfoPersonaje[playerid][ptColor][5]);
		rebel_int(0, "ColorToy7", InfoPersonaje[playerid][ptColor][6]);
		rebel_int(0, "ColorToy8", InfoPersonaje[playerid][ptColor][7]);
		rebel_int(0, "ColorToy9", InfoPersonaje[playerid][ptColor][8]);
		rebel_int(0, "ColorToy10", InfoPersonaje[playerid][ptColor][9]);
		rebel_int(0, "Trabajo1", InfoPersonaje[playerid][pTrabajo1]);
		rebel_int(0, "Trabajo2", InfoPersonaje[playerid][pTrabajo2]);
		rebel_int(0, "Trabajo3", InfoPersonaje[playerid][pTrabajo3]);
		rebel_int(0, "TogManos", InfoPersonaje[playerid][pTogManos]);
		rebel_int(0, "TogCajero", InfoPersonaje[playerid][pTogCajero]);
		rebel_int(0, "TogAnuncios", InfoPersonaje[playerid][pTogAnuncios]);
		rebel_int(0, "TogTelefono", InfoPersonaje[playerid][pTogTelefono]);
		rebel_int(0, "TimerAnuncios", InfoPersonaje[playerid][pTimerAnuncios]);
		rebel_int(0, "TogOOC", InfoPersonaje[playerid][pTogOOC]);
		rebel_int(0, "TogMusic", InfoPersonaje[playerid][pTogMusic]);
		rebel_int(0, "TogRadio", InfoPersonaje[playerid][pTogRadio]);
		rebel_int(0, "TogPortatil", InfoPersonaje[playerid][pTogPortatil]);
		rebel_int(0, "TogFaccion", InfoPersonaje[playerid][pTogFaccion]);
		rebel_int(0, "EstiloManos", InfoPersonaje[playerid][pEstiloManos]);
		rebel_int(0, "TiempoMolotov", InfoPersonaje[playerid][pTiempoMolotov]);
		rebel_int(0, "AccesoGraffiti", InfoPersonaje[playerid][pAccesoGraffiti]);
		rebel_int(0, "ComprarNegocio", InfoPersonaje[playerid][pComprarNegocio]);


		// Cargado de variables de drogas.
		rebel_int(0, "NivelSobredosis", pDroga[playerid][NivelSobredosis]);
		rebel_int(0, "AdiccionAnfetamina",  pDroga[playerid][AdiccionAnfetamina]);
		rebel_int(0, "AdiccionCocaina",  pDroga[playerid][AdiccionCocaina]);
		rebel_int(0, "AdiccionOpioides",  pDroga[playerid][AdiccionOpioides]);
		rebel_int(0, "EfectoMetanfetamina",  pDroga[playerid][EfectoMetanfetamina]);
		rebel_int(0, "EfectoCocaina", pDroga[playerid][EfectoCocaina]);
		rebel_int(0, "EfectoMarihuana",  pDroga[playerid][EfectoMarihuana]);
		rebel_int(0, "EfectoLSD", pDroga[playerid][EfectoLSD]);
		rebel_int(0, "EfectoMDMA", pDroga[playerid][EfectoMDMA]);
		rebel_int(0, "EfectoHongo", pDroga[playerid][EfectoHongo]);
		rebel_int(0, "EfectoEspecialUWU", pDroga[playerid][EfectoEspecialUWU]);
		rebel_int(0, "TiempoMetanfetamina", pDroga[playerid][TiempoMetanfetamina]);
		rebel_int(0, "TiempoCocaina", pDroga[playerid][TiempoCocaina]);
		rebel_int(0, "TiempoMarihuana", pDroga[playerid][TiempoMarihuana]);
		rebel_int(0, "TiempoHeroina", pDroga[playerid][TiempoHeroina]);
		rebel_int(0, "TiempoKetamina", pDroga[playerid][TiempoKetamina]);
		rebel_int(0, "Sobredosis", pDroga[playerid][Sobredosis]);
		rebel_int(0, "Estado", InfoPersonaje[playerid][pEstado]);

		cache_unset_active();
	}
	cache_delete(result);

	usuario_registro[playerid] = 1;
	SeleccionoPJ1[playerid] = -1;
	SeleccionoPJ2[playerid] = -1;
	SeleccionoPJ3[playerid] = -1;
	SeleccionoPJ4[playerid] = -1;
	SeleccionoPJ5[playerid] = -1;
	SetLogin(playerid, 3);
	LimpiarTD(playerid);	
	CargarCuenta(playerid);
	return 1;
}

Dialog:CrearPersonaje(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		if (GetPVarInt(playerid, "max_pjs") == 1) VerPersonajes(playerid);
		else VerPersonajes(playerid);
		return 1;
	}
	if (isnull(inputtext) || strlen(inputtext) > 23)
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {DAA838}Nombre_Apellido{EBEBEB} no puede ser superior a 24 caracteres.");
		Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {DAA838}Creacion", "{FFFFFF}Estas a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {DAA838}Nombre_Apellido{FFFFFF} (Ejemplo: {00CC00}Camila_Rodriguez{FFFFFF})\n", "Continuar", "Volver");
		return 1;
	}
	if (!IsValidRoleplayName(inputtext))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {DAA838}Nombre_Apellido{EBEBEB} no es RolePlay, sigue bien el formato de ejemplo.");
		Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {DAA838}Creacion", "{FFFFFF}Estas a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {DAA838}Nombre_Apellido{FFFFFF} (Ejemplo: {00CC00}Camila_Rodriguez{FFFFFF})\n", "Continuar", "Volver");
		return 1;
	}
	if (VerificarPersonaje(inputtext))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {DAA838}Nombre_Apellido{EBEBEB} ya esta en uso, intenta con otro.");
		Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {9f8d46}Creacion", "{FFFFFF}Estas a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {DAA838}Nombre_Apellido{FFFFFF} (Ejemplo: {00CC00}Camila_Rodriguez{FFFFFF})\n", "Continuar", "Volver");
		return 1;
	}
	if (!strcmp(InfoCuenta[playerid][jNombre], inputtext, true))
	{
		format(InfoPersonaje[playerid][pNombre_Apellido], 24, "%s", inputtext);
		InitCreateCharacter(playerid);
	}
	else
	{
		if (VerificarCuenta(inputtext))
		{
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {DAA838}Nombre_Apellido{EBEBEB} ya esta en uso como una cuenta 'nombre de usuario', intenta con otro.");
			Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {DAA838}Creacion", "{FFFFFF}Estas a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {DAA838}Nombre_Apellido{FFFFFF} (Ejemplo: {00CC00}Camila_Rodriguez{FFFFFF})\n", "Continuar", "Volver");
			return 1;
		}

		format(InfoPersonaje[playerid][pNombre_Apellido], 24, "%s", inputtext);
		InitCreateCharacter(playerid);
	}
	return 1;
}

stock InitCreateCharacter(playerid)
{
	LimpiarTD(playerid);
	ShowNotification(playerid, "Registro", "Personaliza tu personaje utilizando el panel de la derecha.", "info", 5000, "bc");
	PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][29], "SD");
	PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][33], "SD");
	PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][34], "SD");

	for(new i; i < 42; i++){
		PlayerTextDrawShow(playerid, p_tdCrearPJ[playerid][i]);
	}
	SelectTextDraw(playerid, 0x181B2030);

	InterpolateCameraPos(playerid, 256.767822,-0.733140,1502.460083,252.197830,8.486864,1502.490966,2000,CAMERA_MOVE);
    InterpolateCameraLookAt(playerid, 261.267883,2.306858,1500.999877,254.447738,4.246859,1500.999877,2000,CAMERA_MOVE);
    
    SetPlayerVirtualWorld(playerid, playerid + 10);
	TogglePlayerControllable(playerid, false);
}

forward EmpezarPersonaje(playerid);
public EmpezarPersonaje(playerid)
{
	ShowLoadScreen(playerid, 5000);
	if(IsValidDynamicActor(ActorLoginHombre[playerid])) 
		DestroyDynamicActor(ActorLoginHombre[playerid]);

	if(IsValidDynamicActor(ActorLoginMujer[playerid])) 
		DestroyDynamicActor(ActorLoginMujer[playerid]);

	TogglePlayerSpectating(playerid, false);
	StopAudioStreamForPlayer(playerid);

	InfoPersonaje[playerid][pPosicionX] = 161.149;
	InfoPersonaje[playerid][pPosicionY] = 1222.93;
	InfoPersonaje[playerid][pPosicionZ] = 22.3884;
	InfoPersonaje[playerid][pPosicionR] = 99.5988;
	InfoPersonaje[playerid][pInterior] = 0;
	InfoPersonaje[playerid][pVirtualWorld] = 0;
	SetCameraBehindPlayer(playerid);

	new skin = InfoPersonaje[playerid][pSkin];
	SetPlayerSkin(playerid, skin);

	//-- Desconocido
	generar_codigo(playerid);
	SetPlayerName(playerid, InfoPersonaje[playerid][pCodigo]);

	InfoPersonaje[playerid][pVida] = 100;
	SetPlayerHealth(playerid, 100);
	usuario_registro[playerid] = 2;

	ClearChat(playerid);

	SetPlayerScore(playerid, 1);

	for(new i; i < 3; i++){
		PlayerTextDrawShow(playerid, logo_gtafive[playerid][i]);
	}

	for(new i; i < 42; i++){
		PlayerTextDrawHide(playerid, p_tdCrearPJ[playerid][i]);
	}

	InfoPersonaje[playerid][pHorasOn] = 0;
	state_on[playerid] = 3; // logeado
	new DineroInicial = 10000; // Stats de Inicio.
	InfoPersonaje[playerid][pDinero] = DineroInicial;
	GivePlayerMoney(playerid, DineroInicial);
	SetPosEx(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ], InfoPersonaje[playerid][pPosicionR], InfoPersonaje[playerid][pInterior], InfoPersonaje[playerid][pVirtualWorld], 0);
	TogglePlayerControllable(playerid, true);
	SetCameraBehindPlayer(playerid);
	SetPlayerColor(playerid, 0xFFFFFF00);
	InfoPersonaje[playerid][pFechaRegistro] = FechaHoy();
	InfoPersonaje[playerid][pUltimaConexion] = FechaHoy();
	InfoPersonaje[playerid][pCuentaID] = InfoCuenta[playerid][jID];

	new query[2056];
	mysql_format(db_samp, query, sizeof query, "INSERT INTO personajes (Nombre_Apellido, Codigo, CuentaID, PosicionX, PosicionY, PosicionZ, PosicionR, Interior, VirtualWorld, Skin, Sexo, Edad, Ciudad, BolosUwU, FechaRegistro, UltimaConexion) \
	VALUES ('%e', '%e', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%e', '%e')",
	InfoPersonaje[playerid][pNombre_Apellido],
	InfoPersonaje[playerid][pCodigo],
	InfoPersonaje[playerid][pCuentaID],
	InfoPersonaje[playerid][pPosicionX],
	InfoPersonaje[playerid][pPosicionY],
	InfoPersonaje[playerid][pPosicionZ],
	InfoPersonaje[playerid][pPosicionR],
	InfoPersonaje[playerid][pInterior],
	InfoPersonaje[playerid][pVirtualWorld],
	InfoPersonaje[playerid][pSkin],
	InfoPersonaje[playerid][pSexo],
	InfoPersonaje[playerid][pEdad],
	InfoPersonaje[playerid][pCiudad],
	DineroInicial,
	InfoPersonaje[playerid][pFechaRegistro],
	InfoPersonaje[playerid][pUltimaConexion]);
	mysql_tquery(db_samp, query, "CreatePlayerCharacter", "i", playerid);
	LimpiarTD(playerid);

	ShowNotification(playerid, "¡Bienvenido!", "Gracias por registrarte en Boulevard.es.", "success", 5000, "tc");
	ShowNotification(playerid, "Boulevard.es", "¡Hola! Te registraste con éxito en Boulevard.es.", "info", 5000);
	ShowNotification(playerid, "Boulevard.es", "Puedes utilizar /gps para ubicar lugares de la ciudad, si tienes dudas usa /ayuda o /duda.", "info", 5000);
	ShowNotification(playerid, "Boulevard.es", "Para conseguir un trabajo averigua uno con /empleos.", "info", 5000);
	return 1;
}


funcion LimpiarTD(playerid)
{	
	for(new i = 0; i < 50; i++) { PlayerTextDrawHide(playerid, p_tdSeleccionarPJ[playerid][i]); }
	Act_Personajes[playerid] = 0;
	CancelSelectTextDraw(playerid);
	return 1;
}