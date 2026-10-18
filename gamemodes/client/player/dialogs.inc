
Dialog:ShowPermisos(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: //casas
		{
			new count = 0, dialog_share[2056] = "{FFFFFF}", share_format[512], i = 0;
			Loop(id, totalcasas, 1) if (InfoCasa[id][cVenta] != 0 && InfoCasa[id][cTipo] != 0)
			{
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida1], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida2], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cCompartida3], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Casa %d (%s) | ", id, InfoCasa[id][cPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (i == 3)
				{
					i = 0;
					strcat(dialog_share, "\n");
				}
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te han dado permisos de ninguna casa.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Permisos de casas", dialog_share, "Cerrar", "");
		}
		case 1: //negocios
		{
			new count = 0, dialog_share[2056] = "{FFFFFF}", share_format[512], i = 0;
			Loop(id, totalnegocios, 1) if (InfoNegocio[id][nVenta] != 0 && InfoNegocio[id][nTipo] != 0)
			{
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida1], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida2], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida3], true) == 0)
				{
					i++;
					format(share_format, sizeof share_format, "Negocio %d (%s) | ", id, InfoNegocio[id][nPropietario]);
					strcat(dialog_share, share_format);
					count++;
				}
				if (i == 3)
				{
					i = 0;
					strcat(dialog_share, "\n");
				}
			}
			if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te han dado permisos de ningun negocio.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Permisos de negocios", dialog_share, "Cerrar", "");
		}
		case 2: //vehi�culos
		{
			new dialog[3084], gformat[370], iCount = 0;
			strcat(dialog, "Modelo (ID)\tLocalizacion (Estado)\n");
			Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0)
			{
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vCompartida1], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					//conteo
					new gformat2[64];
					format(gformat2, sizeof gformat2, "keyvehowo%d", iCount);
					SetPVarInt(playerid, gformat2, veh);
					iCount++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vCompartida2], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					//conteo
					new gformat2[64];
					format(gformat2, sizeof gformat2, "keyvehowo%d", iCount);
					SetPVarInt(playerid, gformat2, veh);
					iCount++;
				}
				if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoVehiculo[veh][vCompartida3], true) == 0)
				{
					if (InfoVehiculo[veh][vEmbargo] != 0) format(gformat, sizeof gformat, "{F2CB3F}%s\t{C0C0C0}Embargado\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					else
					{
						if (InfoVehiculo[veh][vSpawned] != 0)
						{
							new Float: carPos[3], zone[MAX_ZONE_NAME];
							GetVehiclePos(InfoVehiculo[veh][vIG_id], carPos[0], carPos[1], carPos[2]);
							GetCar3DZone(InfoVehiculo[veh][vIG_id], zone, sizeof zone);
							format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(%d)\t{9DF51D}%s\n", GetNameVehicle(InfoVehiculo[veh][vModelo]), InfoVehiculo[veh][vIG_id], zone);
						}
						else format(gformat, sizeof gformat, "{F2CB3F}%s {C0C0C0}(oculto)\n", GetNameVehicle(InfoVehiculo[veh][vModelo]));
					}
					strcat(dialog, gformat);
					//conteo
					new gformat2[64];
					format(gformat2, sizeof gformat2, "keyvehowo%d", iCount);
					SetPVarInt(playerid, gformat2, veh);
					iCount++;
				}
			}
			if (iCount == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te han dado permisos de ningun vehi�culo.");
			Dialog_Show(playerid, Menu_2Vehiculo, DIALOG_STYLE_TABLIST_HEADERS, "Permisos de vehiculos", dialog, "Continuar", "Volver");
		}
	}
	return 1;
}



Dialog:ShowMonedas(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new query[1528];
	switch (listitem)
	{
	    case 0: pc_cmd_premium(playerid);
		case 1: //vip esmeralda
		{
			if (InfoCuenta[playerid][jVIP] != 0) return SendClientMessageEx(playerid, COLOR_GREY, "* Ya posees VIP %s activo, que expira: %s", GetNameVIP(InfoCuenta[playerid][jVIP]), Segundos_tiempo(InfoCuenta[playerid][jExpira]-gettime()));
			if (InfoCuenta[playerid][jMonedas] < m_vip_esmeralda) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_vip_esmeralda, InfoCuenta[playerid][jMonedas]);
			InfoCuenta[playerid][jVIP] = 1;
			new k = gettime();
			k += 2593600;
			InfoCuenta[playerid][jExpira] = k;
			InfoCuenta[playerid][jMonedas] -= m_vip_esmeralda;
			InfoCuenta[playerid][jMaxCasas] += 1;
			InfoCuenta[playerid][jMaxNegocios] += 1;
			InfoCuenta[playerid][jMaxMuebles] += 300;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET VIP = '%d', Expira = '%d', CoinsVIP = '%d', MaxCasas = 2, MaxNegocios = 2, MaxMuebles = '%d' WHERE ID = '%d'", InfoCuenta[playerid][jVIP], InfoCuenta[playerid][jExpira], InfoCuenta[playerid][jMonedas], InfoCuenta[playerid][jMaxMuebles], InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			InfoPersonaje[playerid][pHorasOn] += 4;
			guardar_int_mysql("personajes", "FugaoVicio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pHorasOn]);
			SetPlayerScore(playerid, InfoPersonaje[playerid][pHorasOn]);
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste VIP Level 1 por %d monedas, el mismo expira: %s", m_vip_esmeralda, Segundos_tiempo(InfoCuenta[playerid][jExpira]-gettime()));
			SendClientMessageEx(playerid, COLOR_YELLOW, "Las cuatro horas fueron cedidas en este personaje, ahora tienes %d horas de juego.", InfoPersonaje[playerid][pHorasOn]);
		}
		case 2: //vip diamante
		{
			if (InfoCuenta[playerid][jVIP] != 0) return SendClientMessageEx(playerid, COLOR_GREY, "* Ya posees VIP %s activo, que expira: %s", GetNameVIP(InfoCuenta[playerid][jVIP]), Segundos_tiempo(InfoCuenta[playerid][jExpira]-gettime()));
			if (InfoCuenta[playerid][jMonedas] < m_vip_diamante) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_vip_diamante, InfoCuenta[playerid][jMonedas]);
			InfoCuenta[playerid][jVIP] = 2;
			new k = gettime();
			k += 2593600;
			InfoCuenta[playerid][jExpira] = k;
			InfoCuenta[playerid][jMonedas] -= m_vip_diamante;
			InfoCuenta[playerid][jRanuras]++;
			InfoCuenta[playerid][jMaxCasas] += 2;
			InfoCuenta[playerid][jMaxNegocios] += 2;
			InfoCuenta[playerid][jMaxMuebles] += 500;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET VIP = '%d', Expira = '%d', Ranuras = '%d', CoinsVIP = '%d', MaxCasas = 3, MaxNegocios = 3, MaxMuebles = '%d' WHERE ID = '%d'", InfoCuenta[playerid][jVIP], InfoCuenta[playerid][jExpira], InfoCuenta[playerid][jRanuras], InfoCuenta[playerid][jMonedas], InfoCuenta[playerid][jMaxMuebles], InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			InfoPersonaje[playerid][pHorasOn] += 10;
			guardar_int_mysql("personajes", "FugaoVicio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pHorasOn]);
			SetPlayerScore(playerid, InfoPersonaje[playerid][pHorasOn]);
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste 'VIP Level 2' por %d monedas, el mismo expira: %s", m_vip_diamante, Segundos_tiempo(InfoCuenta[playerid][jExpira]-gettime()));
			SendClientMessageEx(playerid, COLOR_YELLOW, "Las diez horas fueron cedidas en este personaje, ahora tienes %d horas de juego.", InfoPersonaje[playerid][pHorasOn]);
			SendClientMessageEx(playerid, COLOR_YELLOW, "Se te aumento el maximo de personajes, ahora puedes tener hasta %d personajes.", InfoCuenta[playerid][jRanuras]);
		}
		case 3: //ranura extra de personaje
		{
	 		if (InfoCuenta[playerid][jMonedas] < m_slotpersonaje) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_slotpersonaje, InfoCuenta[playerid][jMonedas]);
			InfoCuenta[playerid][jRanuras]++;
			InfoCuenta[playerid][jMonedas] -= m_slotpersonaje;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET Ranuras = '%d', CoinsVIP = '%d' WHERE ID = '%d'", InfoCuenta[playerid][jRanuras], InfoCuenta[playerid][jMonedas], InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste 'Ranura de personaje' por %d monedas, ahora puedes tener hasta %d personajes.", m_slotpersonaje, InfoCuenta[playerid][jRanuras]);
		}
		case 4: //
		{
	 		if (InfoCuenta[playerid][jMonedas] < m_cambiodenumero) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_cambiodenumero, InfoCuenta[playerid][jMonedas]);
			Dialog_Show(playerid, ChangeNumber, DIALOG_STYLE_INPUT, "{EBEBEB}Cambio de {60bd7e}numero telefonico", "{FFFFFF}Introduce un {F5DEB3}numero{FFFFFF} (entre 100 a 999999).\nEjemplo: {00cc00}555 {FFFFFF}o {00cc00}606060\n", "Continuar", "Volver");
		}
		case 5: //
		{
			new carsamount = VehicleCount(playerid);
			if (carsamount >= 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no puede tener mas de 10 vehiculos.");
			new showConcesionario[4056] = "Modelo\tValor en monedas\n", gformat[256], iCount = 0;
			Loop(xd, sizeof infovehicle, 0) if (infovehicle[xd][elPrecio] >= 1 && infovehicle[xd][elPrecio] <= 100)
			{
				format(gformat, sizeof gformat, "{EBEBEB}%s\t{04B404}%d\n", infovehicle[xd][elNombre], infovehicle[xd][elPrecio]);
				strcat(showConcesionario, gformat);
				//conteo
				new gformat2[64];
				format(gformat2, sizeof gformat2, "vehConcesinx%d", iCount);
				SetPVarInt(playerid, gformat2, xd);
				iCount++;
			}
			Dialog_Show(playerid, BuyVehicle, DIALOG_STYLE_TABLIST_HEADERS, "{60bd7e}vehiculos exclusivos", showConcesionario, "Continuar", "Volver");
		}
		case 6: //ranuras de muebles
		{
	 		if (InfoCuenta[playerid][jMonedas] < m_mueblesextras) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_mueblesextras, InfoCuenta[playerid][jMonedas]);
			InfoCuenta[playerid][jMaxMuebles] += 100;
			InfoCuenta[playerid][jMonedas] -= m_mueblesextras;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET MaxMuebles = '%d', CoinsVIP = '%d' WHERE ID = '%d'", InfoCuenta[playerid][jMaxMuebles], InfoCuenta[playerid][jMonedas], InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste '100slots de muebles' por %d monedas, ahora puedes tener hasta %d muebles.", m_mueblesextras, InfoCuenta[playerid][jMaxMuebles]);
		}
		case 7: // 10k
		{
	 		if (InfoCuenta[playerid][jMonedas] < m_dinero10k) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d moneda para comprar esta opcion, tienes %d monedas.", m_dinero10k, InfoCuenta[playerid][jMonedas]);
   	    	GivePlayerCash(playerid, 10000, "compra 10k /precios");
			InfoCuenta[playerid][jMonedas] -= m_dinero10k;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET CoinsVIP = '%d' WHERE ID = '%d'", InfoCuenta[playerid][jMonedas], InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste '$10.000' por %d moneda.", m_dinero10k);
		}
	}
	return 1;
}

Dialog:BuyVehicle(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new veh = listitem, gformat[40];
	format(gformat, sizeof gformat, "vehConcesinx%d", veh);
	new id = GetPVarInt(playerid, gformat), color1 = random(250), color2 = random(250);
	TextDrawShowForPlayer(playerid, CocheVS[0]);
	//modelo nombre
	format(gformat, sizeof gformat, "%s", infovehicle[id][elNombre]);
	PlayerTextDrawSetStringEx(playerid, pCocheVS[playerid][0], gformat);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][0]);
	//angulo1
	PlayerTextDrawSetPreviewModel(playerid, pCocheVS[playerid][1], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, pCocheVS[playerid][1], color1, color2);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][1]);
	//angulo2
	PlayerTextDrawSetPreviewModel(playerid, pCocheVS[playerid][2], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, pCocheVS[playerid][2], color1, color2);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][2]);
	//angulo3
	PlayerTextDrawSetPreviewModel(playerid, pCocheVS[playerid][3], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, pCocheVS[playerid][3], color1, color2);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][3]);
	//angulo4
	PlayerTextDrawSetPreviewModel(playerid, pCocheVS[playerid][4], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, pCocheVS[playerid][4], color1, color2);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][4]);
	//precio
	format(gformat, sizeof gformat, "%d monedas", infovehicle[id][elPrecio]);
	PlayerTextDrawSetStringEx(playerid, pCocheVS[playerid][5], gformat);
	PlayerTextDrawShow(playerid, pCocheVS[playerid][5]);
	//espacios maletero
	if (infovehicle[id][elModelo] == 509 || infovehicle[id][elModelo] == 481 || infovehicle[id][elModelo] == 510) PlayerTextDrawSetStringEx(playerid, pCocheVS[playerid][6], "Maletero:_0_ranuras");
	else
	{
		format(gformat, sizeof gformat, "Maletero:_%d_ranuras", infovehicle[id][elMaxMaletero]);
		PlayerTextDrawSetStringEx(playerid, pCocheVS[playerid][6], "");
	}
	//regresar
	TextDrawShowForPlayer(playerid, CocheVS[1]);
	//comprar
	TextDrawShowForPlayer(playerid, CocheVS[2]);
	//seleccion
	SelectTextDraw(playerid, 0xd63417BB);
	BuyVIPvehicle[playerid] = id;
	return 1;
}

Dialog:ChangeNumber(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_precios(playerid);
	if (InfoCuenta[playerid][jMonedas] < m_cambiodenumero) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar esta opcion, tienes %d monedas.", m_cambiodenumero, InfoCuenta[playerid][jMonedas]);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo numeros porfavor, vuelve a intentarlo.");
	new numero = strval(inputtext);
	if (numero < 100 || numero > 999999) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Los digitos deben estar entre 100 a 999999.");
	if (VerificarNumero(numero))
	{
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "El {60bd7e}numero telefonico{EBEBEB} ya esta en uso, intenta con otro.");
		Dialog_Show(playerid, ChangeNumber, DIALOG_STYLE_INPUT, "{EBEBEB}Cambio de {60bd7e}numero telefonico", "{FFFFFF}Introduce un {F5DEB3}numero{FFFFFF} (entre 100 a 999999).\nEjemplo: {00cc00}555 {FFFFFF}o {00cc00}606060\n", "Continuar", "Volver");
		return 1;
	}
	InfoPersonaje[playerid][pTelefono] = numero;
	guardar_int_mysql("personajes", "Telefono", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTelefono]);
	InfoCuenta[playerid][jMonedas] -= m_cambiodenumero;
	guardar_int_mysql("cuentas", "CoinsVIP", InfoCuenta[playerid][jID], InfoCuenta[playerid][jMonedas]);
	SendClientMessageEx(playerid, 0x60bd7eFF, "Cambiaste tu numero telefonico al %d por %d monedas, te quedan %d monedas.", numero, m_cambiodenumero, InfoCuenta[playerid][jMonedas]);
	return 1;
}

Dialog:PreciosVIP(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 3:
		{
			new string1[1028];
			strcat(string1, "ID SAMP\tTipo\tModelo\tValor monedas\n");
			strcat(string1, "403\tCamion\tLinerunner\t7\n");
			strcat(string1, "408\tCamion basura\tTrashmaster\t9\n");
			strcat(string1, "409\tLimosina\tStretch\t12\n");
			strcat(string1, "411\tSport\tInfernus\t15\n");
			strcat(string1, "415\tSport\tCheetah\t12\n");
			strcat(string1, "424\tOff Road\tBF Injection\t2\n");
			strcat(string1, "428\tBlindado\tSecuricar\t9\n");
			strcat(string1, "Siguiente pagina");
			Dialog_Show(playerid, BuyVehVIP, DIALOG_STYLE_TABLIST_HEADERS, "VIP {F5DEB3}vehiculos", string1, "Continuar", "Volver");
		}
	}
	return 1;
}

new complandomodelovip[MAX_PLAYERS];
new complandopreciovip[MAX_PLAYERS];

Dialog:BuyVehVIP(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_precios(playerid);
	new valor = 0, modelo = 0;
	switch (listitem)
	{
		case 0: valor = 7, modelo = 403;
		case 1: valor = 9, modelo = 408;
		case 2: valor = 12, modelo = 409;
		case 3: valor = 15, modelo = 411;
		case 4: valor = 12, modelo = 415;
		case 5: valor = 2, modelo = 424;
		case 6: valor = 9, modelo = 428;
		case 7:
		{
			new string2[1028];
			strcat(string2, "ID SAMP\tTipo\tModelo\tValor monedas\n");
			strcat(string2, "431\tServicios\tBus\t4\n");
			strcat(string2, "434\tEspecial\tHotknife\t5\n");
			strcat(string2, "437\tServicios\tCoach\t4\n");
			strcat(string2, "442\tServicios\tRomero\t3\n");
			strcat(string2, "443\tIndustrial\tPacker\t8\n");
			strcat(string2, "444\tOff Road\tMonster Truck\t10\n");
			strcat(string2, "451\tSport\tTurismo\t14\n");
			strcat(string2, "470\tOff Road\tPatriot\t5\n");
			strcat(string2, "487\tHelicopteros\tMaverick\t20\n");
			strcat(string2, "495\tOff Road\tSandking\t5\n");
			strcat(string2, "506\tSport\tSuper GT\t8\n");
			strcat(string2, "522\tMoto\tNRG-500\t8\n");
			strcat(string2, "541\tSport\tBullet\t10\n");
			strcat(string2, "571\tMario\tKart\t3\n");
			strcat(string2, "579\tOff Road\tHuntley\t2\n");
			strcat(string2, "580\tSaloon\tStrafford\t3\n");
			strcat(string2, "587\tSport\tEuros\t3");
			Dialog_Show(playerid, Buy2VehVIP, DIALOG_STYLE_TABLIST_HEADERS, "VIP {F5DEB3}vehiculos", string2, ">", "");
			return 1;
		}
	}
	complandomodelovip[playerid] = modelo;
	complandopreciovip[playerid] = valor;
	new gformat[256];
	format(gformat, sizeof gformat, "{FFFFFF}¿Estas seguro que quieres comprar este {F5DEB3}%s{FFFFFF} Coins: {00CC00}%d\n", GetNameVehicle(modelo), valor);
	Dialog_Show(playerid, ComplandoVehVIP, DIALOG_STYLE_MSGBOX, "Compra vehiculo VIP", gformat, "Comprar", "Salir");
	return 1;
}

Dialog:Buy2VehVIP(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_precios(playerid);
	new valor = 0, modelo = 0;
	switch (listitem)
	{
		case 0: valor = 4, modelo = 431;
		case 1: valor = 5, modelo = 434;
		case 2: valor = 4, modelo = 437;
		case 3: valor = 3, modelo = 442;
		case 4: valor = 8, modelo = 443;
		case 5: valor = 10, modelo = 444;
		case 6: valor = 14, modelo = 451;
		case 7: valor = 5, modelo = 470;
		case 8: valor = 20, modelo = 487;
		case 9: valor = 5, modelo = 495;
		case 10: valor = 8, modelo = 506;
		case 11: valor = 8, modelo = 522;
		case 12: valor = 10, modelo = 541;
		case 13: valor = 3, modelo = 571;
		case 14: valor = 2, modelo = 579;
		case 15: valor = 3, modelo = 580;
		case 16: valor = 3, modelo = 587;
	}
	complandomodelovip[playerid] = modelo;
	complandopreciovip[playerid] = valor;
	new gformat[256];
	format(gformat, sizeof gformat, "{FFFFFF}¿Estas seguro que quieres comprar este {F5DEB3}%s{FFFFFF} Coins: {00CC00}%d\n", GetNameVehicle(modelo), valor);
	Dialog_Show(playerid, ComplandoVehVIP, DIALOG_STYLE_MSGBOX, "Compra vehiculo VIP", gformat, "Comprar", "Salir");
	return 1;
}

Dialog:ChangeCharacter(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	//ultima conexion & posiciones
	GetPlayerPos(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ]);
	GetPlayerFacingAngle(playerid, InfoPersonaje[playerid][pPosicionR]);
	InfoPersonaje[playerid][pInterior] = GetPlayerInterior(playerid);
	InfoPersonaje[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
	InfoPersonaje[playerid][pUltimaConexion] = FechaHoy();
	InfoCuenta[playerid][jUltimaConexion] = FechaHoy();
	//desconectar vehiculos player.
	SecuenciaVehiculos(playerid);
	//save mysql
	new query[2056];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET PosicionX = '%f', PosicionY = '%f', PosicionZ = '%f', PosicionR = '%f', Vida = '%f', Chaleco = '%f', Interior = '%d', VirtualWorld = '%d', \
	UltimaConexion = '%e', TiempoSancion = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE Nombre_Apellido = '%e'",
	InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ], InfoPersonaje[playerid][pPosicionR], InfoPersonaje[playerid][pVida], InfoPersonaje[playerid][pChaleco],
	InfoPersonaje[playerid][pInterior], InfoPersonaje[playerid][pVirtualWorld], InfoPersonaje[playerid][pUltimaConexion], InfoPersonaje[playerid][pTiempoSancion], InfoPersonaje[playerid][pManoDerecha],
	InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pNombre_Apellido]);
	mysql_tquery(db_samp, query);
	guardar_string_mysql("cuentas", "UltimaConexion", InfoCuenta[playerid][jID], InfoCuenta[playerid][jUltimaConexion]);
	//reset
	InfoPersonaje[playerid][pDinero] = 0;
	ResetPlayerMoney(playerid);

	new rse[190];
	format(rse, sizeof rse, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) acaba de usar /cambiarpersonaje.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, rse);

	format(rse, sizeof rse, "%s (%d) acaba de usar /cambiarpersonaje.", NombreOriginal(playerid), playerid);
	ProxDetector(20.0, playerid, rse, 0x1EB121FF, 0x1EB121FF, 0x1EB121FF, 0x1EB121FF, 0x1EB121FF);

	SetPVarInt(playerid, "EstaCrack", 0);
    StopApplyAnimEx(playerid);
    TogglePlayerControllable(playerid, true);
	DeletePVar(playerid, "IsFrozen");
	InfoPersonaje[playerid][pMuerto] = 0;
	YaAviso[playerid] = 0;
	timer_herido[playerid] = 0;
    player_weapon[playerid] = -1;
	player_asesino[playerid] = -1;

	SetPlayerColor(playerid, 0x00000000); // color logeo
 	new string[360];
	format(string, sizeof(string), "Conectando_%d", playerid);
	SetPlayerName(playerid, string);

	ClearChat(playerid);
	state_on[playerid] = 2;
	SetPlayerName(playerid, InfoCuenta[playerid][jNombre]);
	SetPlayerScore(playerid, 0);
	reset_InfoPersonaje(playerid);      // personajes
	ResetPlayerHeridas(playerid);       // limpieza de heridas
	usuario_registro[playerid] = 0;
	// camara de inicio
	TogglePlayerSpectating(playerid, true);
	SetCameraIntro(playerid);
	SyncPlayerTime(playerid);
	VerPersonajes(playerid);
	if (InfoCuenta[playerid][jVIP] != 2) PersonajeTiempo[playerid] = gettime();
	return 1;
}

Dialog:ShowPanel(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: pc_cmd_togphone(playerid), pc_cmd_config(playerid);
		case 1: pc_cmd_togmanos(playerid), pc_cmd_config(playerid);
		case 2: pc_cmd_togad(playerid), pc_cmd_config(playerid);
		case 3: pc_cmd_velocimetro(playerid), pc_cmd_config(playerid);
		case 4: pc_cmd_togooc(playerid), pc_cmd_config(playerid);
		case 5: pc_cmd_radio(playerid), pc_cmd_config(playerid);
		case 6: pc_cmd_togmusic(playerid), pc_cmd_config(playerid);
		case 7: pc_cmd_togpr(playerid), pc_cmd_config(playerid);
		case 8: pc_cmd_togfaccion(playerid), pc_cmd_config(playerid);
		case 9:
		{
			Dialog_Show(playerid, EstiloManitas, DIALOG_STYLE_INPUT, "Estilo: {F5DEB3}Manos", "{EBEBEB}Introduce el numero de estilo ({6E97C7}1-8{EBEBEB})\n", "Continuar", "Volver");
		}
		case 10: pc_cmd_estiloanuncio(playerid), pc_cmd_config(playerid);
		case 11: pc_cmd_estilobolsillos(playerid), pc_cmd_config(playerid);
		case 12: ClearChat(playerid);
		case 13: pc_cmd_cambiarpersonaje(playerid);
		case 14:
		{
			new sexoduro[1028] = "Opcion\tCosto\n", contuhermana[210], chaseuwu[128];
			format(chaseuwu, sizeof chaseuwu, "Configuracion del personaje > %s", InfoPersonaje[playerid][pNombre_Apellido]);
			format(contuhermana, sizeof contuhermana, "{FFFFFF}Cambiar nombre del personaje\t3 EBCoins\n");
			strcat(sexoduro, contuhermana);
			format(contuhermana, sizeof contuhermana, "{FFFFFF}Cambiar edad del personaje\t1 EBCoins\n");
			strcat(sexoduro, contuhermana);
			format(contuhermana, sizeof contuhermana, "{FFFFFF}Cambiar sexo del personaje\t2 EBCoins\n");
			strcat(sexoduro, contuhermana);
			Dialog_Show(playerid, ConfigPJ, DIALOG_STYLE_TABLIST_HEADERS, chaseuwu, sexoduro, "Seleccionar", "Cerrar");
		}
	}
	return 1;
}

Dialog:ConfigPJ(playerid, response, listitem, inputtext[])
{
	if(!response) return SendClientMessageEx(playerid, COLOR_GREY, "* Cerraste la configuracion de tu personaje.");
	switch(listitem)
	{
		case 0: SendClientMessageEx(playerid, 0xffffffff, "cambiar nombre");
		case 1: SendClientMessageEx(playerid, 0xffffffff, "cambiar edad");
		case 2: SendClientMessageEx(playerid, 0xffffffff, "cambiar sexo");
	}
	return 1;
}

Dialog:EstiloManitas(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_config(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo numeros, vuelve a intentarlo");
	new estilo = strval(inputtext);
	if (estilo < 1 || estilo > 8)
	{
	    SendPlayerChatMessage(playerid, COLOR_GREY, "* Solo existen 8 estilos, intenta de nuevo.");
		Dialog_Show(playerid, EstiloManitas, DIALOG_STYLE_INPUT, "Estilo: {F5DEB3}Manos", "{EBEBEB}Introduce el numero de estilo ({6E97C7}a1-8{EBEBEB})\n", "Continuar", "Volver");
	    return 1;
	}
	InfoPersonaje[playerid][pEstiloManos] = estilo;
	SendClientMessageEx(playerid, 0xEBEBEBFF, "Estableciste el {6E97C7}estilo %d{EBEBEB} de manos.", estilo);
	guardar_int_mysql("personajes", "EstiloManos", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pEstiloManos]);
	return 1;
}


Dialog:MenuTelefono(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: pc_cmd_telefono(playerid);
		case 1: Dialog_Show(playerid, MarcarNumero, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Marcar un numero", "{FFFFFF}Introduce el numero:", "Llamar", "Volver");
		case 2: Dialog_Show(playerid, SMSSend, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Enviar mensaje", "{FFFFFF}Introduce el numero:", "Continuar", "Volver");
		case 3:
		{
			if (IsPlayerContrato(playerid, 1) != 0) Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opcion: {F5DEB3}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles\n- {00CC00}Repartos disponibles", "Continuar", "Volver");
			else Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opcion: {F5DEB3}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
		}
		case 4: //status
		{
			pc_cmd_togphone(playerid);
			pc_cmd_telefono(playerid);
		}
	}
	return 1;
}

Dialog:MarcarNumero(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_telefono(playerid);
	new string[128];
	if (isnull(inputtext) || !isnumeric(inputtext)) return Dialog_Show(playerid, MarcarNumero, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Marcar un numero", "{FFFFFF}Introduce el numero:", "Llamar", "Volver");
	format(string, sizeof string, "%d", strval(inputtext));
	pc_cmd_llamar(playerid, string);
	return 1;
}

Dialog:SMSSend(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_telefono(playerid);
	if (GetPlayerCash(playerid) < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos 2$ dolares en bolsillos para enviar mensajes.");
	if (isnull(inputtext) || !isnumeric(inputtext)) return Dialog_Show(playerid, SMSSend, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Enviar mensaje", "{FFFFFF}Introduce el numero:", "Continuar", "Volver");
	new string[128];
	format(string, sizeof string, "%d", strval(inputtext));
	NumeroMensaje[playerid] = strval(inputtext);
	Dialog_Show(playerid, SMS2Send, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Enviar mensaje", "{FFFFFF}Introduce el texto que vas a enviar:", "Enviar", "Volver");
	return 1;
}

Dialog:SMS2Send(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, SMSSend, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Enviar mensaje", "{FFFFFF}Introduce el numero:", "Continuar", "Volver");
	if (isnull(inputtext)) return Dialog_Show(playerid, SMS2Send, DIALOG_STYLE_INPUT, "Opcion: {F5DEB3}Enviar mensaje", "{FFFFFF}Introduce el texto que vas a enviar:", "Enviar", "Volver");
	if (GetPlayerCash(playerid) < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos 2$ dolares en bolsillos para enviar mensajes.");
	new phonenumb = NumeroMensaje[playerid], text[256];
	new string[240];
	alm(text, inputtext);
	foreach(new i: Player) if (IsPlayerConnectedEx(i))
	{
		if (InfoPersonaje[i][pTelefono] == phonenumb && phonenumb != 0)
		{
			new playerid2 = i;
			if (InfoPersonaje[playerid2][pTogTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Mensaje no enviado, teléfono apagado.");
			format(string, sizeof string, "SMS de %d: %s", InfoPersonaje[playerid][pTelefono], text);
			SendPlayerChatMessage(playerid2, 0xFFEA5FFF, string);
			format(string, sizeof string, "SMS a %d: %s", phonenumb, text);
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
			PlayerAudio(playerid, 1053, 10.0);
			PlayerAudio(playerid2, 20804, 10.0);
			GivePlayerCash(playerid, -1, "costo de sms");
			rol_ame(playerid, "envi�a un mensaje de texto.");
			return 1;
		}
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* El numero que ha marcado no existe o no esta disponible.");
	return 1;
}

Dialog:FSTYLE_DIALOG(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			if (CheckMoney(playerid, 80) == 0) return 1;
			GivePlayerCash(playerid, -80, "estilo de pelea (1)");
			InfoPersonaje[playerid][pEstiloPelea] = 7;
			SetPlayerFightingStyle (playerid, FIGHT_STYLE_KNEEHEAD);
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicidades! Has aprendido Knee Head.");
			ApplyAnimation(playerid,"benchpress", "gym_bp_celebrate",4.0,1,1,1,1,500, 1);
		}
		case 1:
		{
			if (CheckMoney(playerid, 140) == 0) return 1;
			GivePlayerCash(playerid, -140, "estilo de pelea (2)");
			InfoPersonaje[playerid][pEstiloPelea] = 6;
			SetPlayerFightingStyle (playerid, FIGHT_STYLE_KUNGFU);
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicidades! Has aprendido Kung Fu.");
			ApplyAnimation(playerid,"benchpress", "gym_bp_celebrate",4.0,1,1,1,1,500, 1);
		}
		case 2:
		{
			if (CheckMoney(playerid, 110) == 0) return 1;
			GivePlayerCash(playerid, -110, "estilo de pelea (3)");
			InfoPersonaje[playerid][pEstiloPelea] = 5;
			SetPlayerFightingStyle (playerid, FIGHT_STYLE_BOXING);
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicidades! Has aprendido a Boxear.");
			ApplyAnimation(playerid,"benchpress", "gym_bp_celebrate",4.0,1,1,1,1,500, 1);
		}
		case 3:
		{
			if (CheckMoney(playerid, 90) == 0) return 1;
			GivePlayerCash(playerid, -90, "estilo de pelea (4)");
			InfoPersonaje[playerid][pEstiloPelea] = 15;
			SetPlayerFightingStyle (playerid, FIGHT_STYLE_GRABKICK);
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Felicidades! Has aprendido pelea callejera.");
			ApplyAnimation(playerid,"benchpress", "gym_bp_celebrate",4.0,1,1,1,1,500, 1);
		}
	}
	guardar_int_mysql("personajes", "EstiloPelea", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pEstiloPelea]);
	return 1;
}

Dialog:ShowHelp(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			new dialog_help[2056];
			strcat(dialog_help, "{FFFFFF}/cuenta - /cambiarclave - /removergps - /dni - /licencias - /empleos\n");
			strcat(dialog_help, "{FFFFFF}/mecanicos - /pagar - /payday - /id - /ventana - /telefono - /clearchat\n");
			strcat(dialog_help, "{FFFFFF}/panel - /eject - /moneda - /ceder - /inventario - /gps - /coches - /soporte\n");
			strcat(dialog_help, "{FFFFFF}/comprar - /desbug - - /hora - /reloj - /stopanim - /unirdroga - /dividirdroga\n");
			strcat(dialog_help, "{FFFFFF}/cambiarpersonaje - /top - /negro - /gris - /beber - /dentorno - /fveh - /mecanicos\n");
			strcat(dialog_help, "{088A4B}OOC:{FFFFFF} /b - /f - /mp - /togmp{FFFFFF} | {088A4B}IC:{FFFFFF} /g - /s - /c - /me - /do\n");
			strcat(dialog_help, "{088A4B}Teléfono:{FFFFFF} /telefono - /llamar - /contestar - /colgar - /sms - /altavoz - /transferir\n");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}Frecuentes", dialog_help, "Cerrar", "");
		}
		case 1:
		{
		    new id = InfoPersonaje[playerid][pMiembro];
			new dialog_help[1024], dialog_name[128];
		    if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estas en una faccion.");
		    switch (InfoFaccion[id][fTipo])
		    {
		        case 1: //lspd
		        {
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /equipo - /apgarage - /placa - /carsign - /ram - /revisarcasa - /incautar - /ap - /cp\n");
					strcat(dialog_help, "{FFFFFF}/duty - /radio - /arrestar - /detener - /esposar - /spikes - /pspikes - /qspikes - /limpiar - /dejarmulta\n");
					strcat(dialog_help, "{FFFFFF}/quitar - /multar - /su - /sospechosos - /ct - /sacarct - /guardarct - /ref - /noref - /darlicencia\n");
					strcat(dialog_help, "{FFFFFF}/celda - /enganchar - /desenganchar - /embargar - /verllaves - /revisarmaletero - /limpiarmaletero\n");
					strcat(dialog_help, "{FFFFFF}/llamados - /qcables - /ant - /his - /qant - /sirena - /identidad - /reanimar - /bar - /qbar - /ebar\n");
					strcat(dialog_help, "{FFFFFF}/computador - /buscados - /heridos - /informes - /centralita \n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /frespawn - /fequipo - /fchat - /listamiembros - /gob - /asignarf\n");
				}
				case 2: //fbi
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /duty - /radio - /carsign - /arrestar - /detener - /esposar - /limpiar - /verllaves\n");
					strcat(dialog_help, "{FFFFFF}/celda - /qcables - /ant - /his - /qant - /sirena - /equipo - /quitar - /sospechosos - /ct - /sacarct - /guardarct\n");
					strcat(dialog_help, "{FFFFFF}/identidad - /dejarmulta - /enganchar - /desenganchar - /embargar - /revisarcasa - /incautar - /limpiarmaletero\n");
					strcat(dialog_help, "{FFFFFF}/revisarmaletero - /reanimar - /placa - /ram - /multar - /spikes - /pspikes - /qspikes - /bar - /qbar - /ebar\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /frespawn - /fequipo - /fchat -/listamiembros - /gob\n");
				}
				case 3: //usmc
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /duty - /placa - /radio - /qcables\n");
					strcat(dialog_help, "{FFFFFF}/esposar - /equipo - /ct - /sacarct - /guardarct - /sirena - /enganchar\n");
					strcat(dialog_help, "{FFFFFF}/reanimar - /carsign - /bar - /qbar - /ebar - /desenganchar\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /frespawn - /fequipo - /fchat - /listamiembros - /gob\n");
				}
				case 4: //lscsd
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /equipo - /placa - /carsign - /ram - /revisarcasa - /incautar - /limpiar\n");
					strcat(dialog_help, "{FFFFFF}/identidad - /duty - /radio - /arrestar - /detener - /esposar - /spikes - /pspikes - /qspikes\n");
					strcat(dialog_help, "{FFFFFF}/quitar - /multar - /su - /sospechosos - /ct - /sacarct - /guardarct - /ref - /noref - /darlicencia\n");
					strcat(dialog_help, "{FFFFFF}/celda - /llamados - /ant - /his - /qant - /sirena - /enganchar - /desenganchar - /embargar - /verllaves\n");
					strcat(dialog_help, "{FFFFFF}/qcables - /reanimar - /bar - /qbar - /ebar - /revisarmaletero - /limpiarmaletero - /dejarmulta\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /frespawn - /fequipo - /fchat - /listamiembros - /gob\n");
				}
				case 5: //gob
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /placa - /radio - /equipo\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /listamiembros - /fnombre - /frango - /frespawn - /fequipo - /fchat - /gob - /sacarfondos - /dejarfondos\n");
				}
				case 6: //lsfd
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /placa - /radio - /equipo - /curar - /reanimar - /llamados\n");
					strcat(dialog_help, "{FFFFFF}/incendios - /bar - /qbar - /ebar - /m - /carsign - /sirena\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /listamiembros - /fnombre - /frango - /frespawn - /fequipo - /fchat - /gob\n");
				}
				case 7: //sadoc
				{
					strcat(dialog_help, "{FFFFFF}/f - /r - /d - /dooc - /placa - /radio - /equipo - /ap - /gentrar - /gsalir - /arrestar\n");
					strcat(dialog_help, "{FFFFFF}/duty - /esposar - /ct - /sacarct - /guardarct - /carsign - /reanimar - /his - /limpiar\n");
					strcat(dialog_help, "{FFFFFF}/celda - /qcables - /quitar - /su - /ant - /qant - /sirena\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /listamiembros - /fnombre - /frango - /frespawn - /fequipo - /fchat - /gob\n");
				}
				case 8: //legal
				{
					strcat(dialog_help, "{FFFFFF}/f - /wsp - /togwsp - /equipo\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /fchat - /listamiembros\n");
				}
				case 9: //pandilla
				{
					strcat(dialog_help, "{FFFFFF}/f - /wsp - /togwsp - /robar247 - /graffiti\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /fchat - /listamiembros\n");
				}
				case 10: //mafia
				{
					strcat(dialog_help, "{FFFFFF}/f - /wsp - /togwsp - /robar247\n");
					if (InfoPersonaje[playerid][pLider] != 0) strcat(dialog_help, "{F5DEB3}Lider:{FFFFFF} /invitar - /fnombre - /frango - /fchat - /listamiembros\n");
				}
			}
			format(dialog_name, sizeof(dialog_name), "Comandos de %s%s", GetColorLogo(InfoFaccion[id][fTipo]), InfoFaccion[id][fLogo]);
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, dialog_name, dialog_help, "Cerrar", "");
		}
		case 2: Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}Casa", "{FFFFFF}/comprarcasa - /timbre - /vendercasa - /menucasa\n/guardararmario - /sacararmario - /casaseguro - /muebles", "Cerrar", "");
		case 3: Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}vehiculo", "{FFFFFF}/llaves - /estacionar - /v (nombre) - /seguro - /velocimetro\n/qmod - /gunlocker - /vendermicoche - /smaletero - /gmaletero\n/permisos - /estereo - /menuestereo - /carsign", "Cerrar", "");
		case 4:
		{
			if (InfoCuenta[playerid][jVIP] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Acceso solo para usuarios VIP.");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}VIP", "{FFFFFF}/togvip - /spawncasa", "Cerrar", "");
		}
		case 5: Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}Inventario", "{FFFFFF}/bolsillos - /mano - /guardar - /sacar - /tirar - /cargar\n/recoger - /ceder - /arma (Colgar - Ajustar - Hueso - Tomar)", "Cerrar", "");
		case 6: Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Comandos: {F5DEB3}Negocio", "{FFFFFF}/comprarnegocio - /vendernegocio - /negociomenu - /negocioseguro - /muebles", "Cerrar", "");
		case 7: pc_cmd_animaciones(playerid);
		case 8:
		{
		    new count = 0;
			if (IsPlayerContrato(playerid, 6) != 0)
			{
			    count++;
				SendClientMessageEx(playerid, 0x15BDA8FF, "%s: {EBEBEB}/trailero - /trailerocheckpoint - /trailercarga - /manifesto - /revisartrailer - /trailerolab", GetNameContrato(6));
			}
			if (count == 0) SendPlayerChatMessage(playerid, COLOR_GREY, "Esta opcion es para ver los comandos del empleo en el que andas, usa /empleos para trabajar en alguno.");
		}
	}
	return 1;
}

Dialog:REBUG(playerid, response, listitem, inputtext[])
{
	if (!response) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No dudes en reportar un bug si lo encuentras.");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Gracias por reportar el bug, intentaremos arreglarlo lo mas pronto posible.");
	new string[190];
	format(string, sizeof string, "{FF2F2F}[BugReport]{FFFFFF} %s(%d) reporto: %s", NombreOriginal(playerid), playerid, inputtext);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s reporto: %s", InfoCuenta[playerid][jNombre], inputtext);
	Log("f_logs/reportbug.log", string);
	return 1;
}

Dialog:ShowBuyLicencias(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			if (InfoPersonaje[playerid][pLicencia][0] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes la licencia de conduccion.");
			if (GetPlayerCash(playerid) < 900) return SendPlayerChatMessage(playerid, COLOR_RED, "No puedes pagar esta licencia de conducir.");
			GivePlayerCash(playerid,-900, "licencia de conduccion");
			InfoPersonaje[playerid][pLicencia][0] = 1;
			guardar_int_mysql("personajes", "Licencia1", InfoPersonaje[playerid][pID], 1);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Has adquirido con éxito una licencia de conduccion.");
		}
		case 1:
		{
			if (InfoPersonaje[playerid][pLicencia][2] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes la licencia de navegacion.");
			if (GetPlayerCash(playerid) < 2000) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes pagar esta licencia de navegacion.");
			GivePlayerCash(playerid,-2000, "licencia de navegacion");
			InfoPersonaje[playerid][pLicencia][2] = 1;
			guardar_int_mysql("personajes", "Licencia3", InfoPersonaje[playerid][pID], 1);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Has adquirido con éxito una licencia de navegacion.");
		}
		case 2:
		{
			if (InfoPersonaje[playerid][pLicencia][1] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes la licencia de piloto.");
			if (GetPlayerCash(playerid) < 3500) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes pagar esta licencia de piloto.");
			GivePlayerCash(playerid,-3500, "licencia de aviacion");
			InfoPersonaje[playerid][pLicencia][1] = 1;
			guardar_int_mysql("personajes", "Licencia2", InfoPersonaje[playerid][pID], 1);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Has adquirido con éxito una licencia de piloto; ahora sera capaz de manejar aeronaves.");
		}
	}
	return 1;
}