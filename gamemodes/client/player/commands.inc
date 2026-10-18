cmd:ext(playerid, params[])
{
	if (!CheckTimer(10, DopTimer[playerid]))
	{
		if (sscanf(params, "s[256]", params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ext (Mensaje)");
		new gformat[320];
		//puertas dinamicas
		Loop(id, totalpuertas, 1) if (InfoPuerta[id][pdExteriorX] != 0.0)
		{
			//entrada
			if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoPuerta[id][pdExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoPuerta[id][pdExteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Exterior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 7.0, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 50.0, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW]);
				return 1;
			}
			//salida
			else if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]) && InfoPersonaje[playerid][pVirtualWorld] == InfoPuerta[id][pdInteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Interior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 15.0, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 10.0, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW]);
				return 1;
			}
		}
		//casas dinamicas
		Loop(p, totalcasas, 1) if (InfoCasa[p][cTipo] != 0)
		{
			//entrada
			if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[p][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[p][cExteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Exterior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 7.0, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ], InfoCasa[p][cExteriorInt], InfoCasa[p][cExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 50.0, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ], InfoCasa[p][cInteriorInt], InfoCasa[p][cInteriorVW]);
				return 1;
			}
			//salida
			else if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[p][cInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[p][cInteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Interior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 15.0, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ], InfoCasa[p][cExteriorInt], InfoCasa[p][cExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 10.0, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ], InfoCasa[p][cInteriorInt], InfoCasa[p][cInteriorVW]);
				return 1;
			}
		}
		//negocios dinamicos
		Loop(id, totalnegocios, 1) if (InfoNegocio[id][nTipo] != 0)
		{
			//entrada
			if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoNegocio[id][nExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[id][nExteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Exterior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 7.0, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorInt], InfoNegocio[id][nExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 50.0, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ], InfoNegocio[id][nInteriorInt], InfoNegocio[id][nInteriorVW]);
				return 1;
			}
			//salida
			else if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoNegocio[id][nInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[id][nInteriorVW])
			{
				DopTimer[playerid] = gettime();
				format(gformat, sizeof gformat, "(Interior %d) %s", playerid, params);
				Uso_Dop(gformat, 0x009700FF, 15.0, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorInt], InfoNegocio[id][nExteriorVW]);
				Uso_Dop(gformat, 0x009700FF, 10.0, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ], InfoNegocio[id][nInteriorInt], InfoNegocio[id][nInteriorVW]);
				return 1;
			}
		}
		//error
		SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas en ninguna entrada/salida.");
    }
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(10, DopTimer[playerid]) ));
    }
	return 1;
}

cmd:lugar(playerid)
{
	if (GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes saber tu ubicación en interiores.");
	new Float: x, Float: y, Float: z, locatziona[32];
	GetPlayerPos(playerid, x, y, z);
	Get2DZone(locatziona, MAX_ZONE_NAME, x, y, z);
	SendClientMessageEx(playerid, 0xFFFFFFFF, "Estas ubicado en {4A4AFF}%s{FFFFFF}.", locatziona);
	return 1;
}
alias:lugar("varyna");

cmd:chaleco(playerid)
{
	if(pDroga[playerid][TiempoHeroina] > 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes quitarte el chaleco mientras estas bajo el efecto de una droga.");
	if (InfoPersonaje[playerid][pChaleco] != 0.0)
	{
		if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes quitarte el chaleco con ambas manos ocupadas."); return 1; }
		if (InfoPersonaje[playerid][pManoDerecha] == 0)
		{
			SendClientMessageEx(playerid, COLOR_YELLOW, "Te retiras el chaleco (%d) y lo dejas en tu mano derecha.", floatround(InfoPersonaje[playerid][pChaleco]));
			InfoPersonaje[playerid][pManoDerecha] = 66;
			InfoPersonaje[playerid][pManoDerechaCant] = floatround(InfoPersonaje[playerid][pChaleco]);
			PonerObjeto(playerid, 1, 66);
		}
		else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
		{
			SendClientMessageEx(playerid, COLOR_YELLOW, "Te retiras el chaleco (%d) y lo dejas en tu mano izquierda.", floatround(InfoPersonaje[playerid][pChaleco]));
			InfoPersonaje[playerid][pManoIzquierda] = 66;
			InfoPersonaje[playerid][pManoIzquierdaCant] = floatround(InfoPersonaje[playerid][pChaleco]);
			PonerObjeto(playerid, 2, 66);
		}
		InfoPersonaje[playerid][pChaleco] = 0.0;
		new query[512];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d', Chaleco = 0.0 WHERE ID = '%d'",
		InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	//
	if (InfoPersonaje[playerid][pManoDerecha] == 66 && InfoPersonaje[playerid][pManoDerechaCant] > 0)
	{
		dar_chaleco(playerid, InfoPersonaje[playerid][pManoDerechaCant]);
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid, 7);
		ActualizarManos(playerid, 1);
		return 1;
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 66 && InfoPersonaje[playerid][pManoIzquierdaCant] > 0)
	{
		dar_chaleco(playerid, InfoPersonaje[playerid][pManoIzquierdaCant]);
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid, 8);
		ActualizarManos(playerid, 1);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún blindaje puesto o en manos.");
	return 1;
}

cmd:permisos(playerid)
{
	Dialog_Show(playerid, ShowPermisos, DIALOG_STYLE_LIST, "Permisos otorgados", "Casas\nNegocios\nvehiculos", "Continuar", "Salir");
	return 1;
}

cmd:detalles(playerid)
{
	//casas
	Loop(id, sizeof InfoCasa, 0) if (IsPlayerInRangeOfPoint(playerid, 3.5, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[id][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[id][cExteriorVW])
	{
		new hide_acoount[1028], gformat[256], location[MAX_ZONE_NAME], exdireccion[215] = "";
		Get2DZone(location, MAX_ZONE_NAME, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]);
		if (InfoCasa[id][cExteriorVW] == 0 && InfoCasa[id][cExteriorInt] == 0) format(exdireccion, sizeof exdireccion, "%s", location);
		if (InfoCasa[id][cVenta] != 0) // comprada
		{
			format(gformat, sizeof gformat, "Puerta: %s\n", (InfoCasa[id][cSeguro]) ? ("Cerrada") : ("Abierta"));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Clase: %s\n", GetClaseCasa(InfoCasa[id][cTipo]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Dirección: %d %s\n", id, exdireccion);
			strcat(hide_acoount, gformat);
			//premium
			if (InfoCasa[id][cPremium] != 0)
			{
				strcat(hide_acoount, "Propiedad premium\n");
			}
			else
			{
				if (InfoCasa[id][cTiempoDisponible] < gettime())
				{
					strcat(hide_acoount, "Disponible en MINUTOS\n");
				}
				else
				{
					format(gformat, sizeof gformat, "Disponible en %s\n", Segundos_tiempo(InfoCasa[id][cTiempoDisponible]-gettime()));
					strcat(hide_acoount, gformat);
				}
			}
			//propietario
			if (GetPlayerAdmin(playerid, 1) == 1)
			{
				format(gformat, sizeof gformat, "Propietario: %s\n", InfoCasa[id][cPropietario]);
				strcat(hide_acoount, gformat);
			}
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Casa adquirida", hide_acoount, "Ok", "");
		}
		else // en venta
		{
			format(gformat, sizeof gformat, "Precio: $%s\n", diner_coma(InfoCasa[id][cPrecio]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Clase: %s\n", GetClaseCasa(InfoCasa[id][cTipo]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Dirección: %d %s\n", id, exdireccion);
			strcat(hide_acoount, gformat);
			strcat(hide_acoount, "\nPara comprar la vivienda usa '/comprarcasa'\n");
			strcat(hide_acoount, "y/o para revisar su interior usa '/vercasa'.\n");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Casa en venta", hide_acoount, "Ok", "");
		}
		return 1;
	}
	//negocios
	if (GetExtNegocio(playerid) != -1)
	{
		new hide_acoount[1028], gformat[256], id = GetExtNegocio(playerid), location[MAX_ZONE_NAME];
		Get2DZone(location, MAX_ZONE_NAME, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]);
		if (InfoNegocio[id][nVenta] != 0) // comprado
		{
			format(gformat, sizeof gformat, "Nombre: %s\n", InfoNegocio[id][nNombre]);
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Puerta: %s\n", (InfoNegocio[id][nSeguro]) ? ("Cerrada") : ("Abierta"));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Tipo: %s\n", GetTipoNegocio(InfoNegocio[id][nTipo]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Dirección: %d %s\n", id, location);
			strcat(hide_acoount, gformat);
			if (InfoNegocio[id][nTiempoDisponible] < gettime())
			{
				strcat(hide_acoount, "Disponible en MINUTOS\n");
			}
			else
			{
				format(gformat, sizeof gformat, "Disponible en %s\n", Segundos_tiempo(InfoNegocio[id][nTiempoDisponible]-gettime()));
				strcat(hide_acoount, gformat);
			}
			//propietario
			if (GetPlayerAdmin(playerid, 1) == 1)
			{
				format(gformat, sizeof gformat, "Propietario: %s\n", InfoNegocio[id][nPropietario]);
				strcat(hide_acoount, gformat);
			}
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Negocio adquirido", hide_acoount, "Ok", "");
		}
		else // en venta
		{
			format(gformat, sizeof gformat, "Precio: $%s\n", diner_coma(InfoNegocio[id][nPrecio]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Tipo: %s\n", GetTipoNegocio(InfoNegocio[id][nTipo]));
			strcat(hide_acoount, gformat);
			format(gformat, sizeof gformat, "Dirección: %d %s\n", id, location);
			strcat(hide_acoount, gformat);
			strcat(hide_acoount, "\nPuedes usar /comprarnegocio aqui­\n");
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Negocio en venta", hide_acoount, "Ok", "");
		}
		return 1;
	}
	//clear
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas cerca de ninguna propiedad.");
	return 1;
}

cmd:beber(playerid)
{
	if (no_tiene_manos(playerid, 65) == 0) return 1;
	if (InfoPersonaje[playerid][pManoDerecha] == 65) InfoPersonaje[playerid][pManoDerechaCant]--;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 65) InfoPersonaje[playerid][pManoIzquierdaCant]--;
	if (InfoPersonaje[playerid][pSexo] == 1) ApplyAnimation(playerid, "GANGS", "drnkbr_prtl", 4.0, 0, 0, 1, 0, 6000, 1);
	else ApplyAnimation(playerid, "BAR", "dnk_stndF_loop", 4.0, 0, 0, 1, 0, 4000, 1);
	ActualizarManos(playerid, 1);
	return 1;
}

cmd:dentorno(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas en estado herido o muerto.");
	if (GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo puedes utilizar esto en exteriores, no habri­a nadie en interiores.");
	if (YaAviso[playerid] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya has dado un aviso de tu situación actual.");
	new gformat[190], Float: KcyoX, Float: KcyoY, Float: KcyoZ, location[MAX_ZONE_NAME];
	GetPlayerPos(playerid, KcyoX, KcyoY, KcyoZ);
	Get2DZone(location, sizeof location, KcyoX, KcyoY, KcyoZ);
	format(gformat, sizeof gformat, "[CENTRAL] Se registró un nuevo herido en %s.", location);
	if (member_faccion(playerid, 1, 4) && OnDuty[playerid] == 1)
	{
		SendRadioMessage(1, COLOR_RADIO, gformat, 2);
		SendRadioMessage(4, COLOR_RADIO, gformat, 2);
		SendRadioMessage(6, COLOR_RADIO, gformat, 2);
	}
	else
	{
		SendRadioMessage(1, COLOR_RADIO, gformat, 4);
		SendRadioMessage(4, COLOR_RADIO, gformat, 4);
		SendRadioMessage(6, COLOR_RADIO, gformat, 4);
	}
	YaAviso[playerid] = 1;
	ProxDetector(30.0, playerid, "** Un transeúnte llamó a emergencias al ver la situación.", COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN);
	return 1;
}

cmd:fveh(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser el conductor de un vehiculo.");
	new idcar = GetPlayerVehicleID(playerid);
	new Float: cvida;
	GetVehicleHealth(idcar, cvida);
	if (cvida < 850.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos el vehiculo con 850.0 de vida. (Usa /dl para verificar)");
	new panels, doors, lights, tires, tires2;
	GetVehicleDamageStatus(idcar, panels, doors, lights, tires);
	RepairVehicle(idcar);
	SetVehicleHealth(idcar, cvida);
	GetVehicleDamageStatus(idcar, panels, doors, lights, tires2);
	if (tires != 0)
	{
		tires = encode_tires(1, 1, 1, 1);
		UpdateVehicleDamageStatus(idcar, panels, doors, lights, tires);
	}
	return 1;
}
alias:fveh("rcar");

cmd:premium(playerid)
{
	new showDialog[2056] = "Beneficio\tUsuario común\tVIP Level 1\tVIP Level 2\n";
	strcat(showDialog, "{EBEBEB}Pago adicional por payday\t0$\t400$\t900$\n");
	strcat(showDialog, "{EBEBEB}Li­mite de casas propias\t1\t2\t3\n");
	strcat(showDialog, "{EBEBEB}Li­mite de negocios propios\t1\t2\t3\n");
	strcat(showDialog, "{EBEBEB}Li­mite de vehi­culos propios\t3\t6\t10\n");
	strcat(showDialog, "{EBEBEB}Li­mite de muebles\t150\t+300\t+500\n");
	strcat(showDialog, "{EBEBEB}Li­mite de ranuras de trabajos\t2\t3\t3\n");
	strcat(showDialog, "{EBEBEB}Li­mite de habilidad en trabajos\t1\t2\t3\n");
	strcat(showDialog, "{EBEBEB}Li­mite de ranuras de toys en personajes\t4\t4\t7\n");
	strcat(showDialog, "{EBEBEB}Li­mite de vehiculos spawneados\t2\t5\t10\n");
	strcat(showDialog, "{EBEBEB}Acceso a toys en vehi­culos propios\tno\tno\tsi­\n");
	strcat(showDialog, "{EBEBEB}Acceso a nitro x2 en talleres\tno\tno\tsi­\n");
	strcat(showDialog, "{EBEBEB}Acceso a toys exclusivos\tno\tsi­\tsi­\n");
	strcat(showDialog, "{EBEBEB}Acceso a skins exclusivos\tno\tsi\tsi­\n");
	strcat(showDialog, "{EBEBEB}Acceso a cambiar colores en accesorios\tno\tno\tsi­\n");
	strcat(showDialog, "{EBEBEB}Acceso a /volver en casa\tno\tsi­\tsi­\n");
//	strcat(showDialog, "{EBEBEB}Descuento en arti­culos de negocios\t0%\t20%\t40%\n");
	strcat(showDialog, "{EBEBEB}Descuento en compra de vehi­culos\t0%%\t15%%\t30%%\n");
	strcat(showDialog, "{EBEBEB}Descuento de operaciones en los talleres\t0%%\t20%%\t40%%\n");
	strcat(showDialog, "{EBEBEB}Combustible gratis en gasolineras\tno\tno\tsi­\n");
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_TABLIST_HEADERS, "{EBEBEB}Información {60bd7e}Premium", showDialog, "Cerrar", "");
	return 1;
}

cmd:precios(playerid)
{
	new showDialog[2056] = "Beneficio\tMonedas\n", showFormat[256];
	format(showFormat, sizeof showFormat, "{EBEBEB}Ver información de VIP's\n"); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}VIP Level 1\t{00CC00}%d\n", m_vip_esmeralda); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}VIP Level 2\t{00CC00}%d\n", m_vip_diamante); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}Ranura de personaje\t{00CC00}%d\n", m_slotpersonaje); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}Cambio de número telefónico\t{00CC00}%d\n", m_cambiodenumero); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}Vehiculos exclusivos\t{00CC00}-\n"); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}+100 slots de muebles\t{00CC00}%d\n", m_mueblesextras); strcat(showDialog, showFormat);
	format(showFormat, sizeof showFormat, "{EBEBEB}$10.000\t{00CC00}%d\n", m_dinero10k); strcat(showDialog, showFormat);
	Dialog_Show(playerid, ShowMonedas, DIALOG_STYLE_TABLIST_HEADERS, "{EBEBEB}Uso de {60bd7e}Monedas", showDialog, "Continuar", "Salir");
	return 1;
}

cmd:cambiarpersonaje(playerid)
{
	if(GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar esto mientras estas herido.");
 	if(GetPVarInt(playerid, "PlayerCuffed") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar esto en ese estado.");
	if(puede_detener(playerid) == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando esposado.");
	if(InfoPersonaje[playerid][pTiempoSancion] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estas en prisión.");

	if (!CheckTimer(180, PersonajeTiempo[playerid]))
	{
		Dialog_Show(playerid, ChangeCharacter, DIALOG_STYLE_MSGBOX, "{088A4B}Confirmación", "{FFFFFF}Â¿Estas seguro de cambiar personaje?\n{FFEF57}Nota: El mal uso de este comando es sancionable.\n", "Sí", "No");
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, PersonajeTiempo[playerid]) ));
	}
	return 1;
}
alias:cambiarpersonaje("changechar");

cmd:clearchat(playerid)
{
	ClearChat(playerid);
	return 1;
}
alias:clearchat("cpantalla", "limpiarpantalla");

cmd:reloj(playerid)
{
	if (xHora >= 12) SendClientMessageEx(playerid, COLOR_YELLOW, "Son las %02d:%02d PM con %02d segundos", (xHora == 12) ? (12) : (xHora - 12), xMinuto, xSegundo);
	else if (xHora < 12) SendClientMessageEx(playerid, COLOR_YELLOW, "Son las %02d:%02d AM con %02d segundos", (xHora == 0) ? (12) : (xHora), xMinuto, xSegundo);
	rol_ame(playerid, "observa la hora de su reloj.");
	return 1;
}

cmd:hora(playerid)
{
	new Ano, Mes, Dia, Hora, Minutos, Segundos, string[190];
	getdate(Ano, Mes, Dia);
	gettime(Hora, Minutos, Segundos);
	if (Hora >= 12) format(string, sizeof string, "~y~%02d/%02d/%d~n~~w~ %02d:%02d pm", Dia, Mes, Ano, (Hora == 12) ? (12) : (Hora - 12), Minutos);
	else if(Hora < 12) format(string, sizeof string, "~y~%02d/%02d/%d~n~~w~ %02d:%02d am", Dia, Mes, Ano, (Hora == 0) ? (12) : (Hora), Minutos);
	GameTextForPlayer(playerid, string, 5000, 1);
	ShowWeatherData(playerid);
	return 1;
}

cmd:comprarbotiquin(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, 1163.0784, -1323.8208, 1015.4130)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas dentro del hospital.");
	new precio = 227, string[190];
	if (GetPlayerCash(playerid) < precio)
	{
		format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Botiquin{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
		return 1;
	}
	if (DarObjeto(playerid, 53, 1) == 2) return 1;
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un botiquin. (/hpsave)");
	GivePlayerCash(playerid, -precio, "compra botiquin");
	return 1;
}

cmd:config(playerid)
{
	new dialog[2056], gformat[195];
	format(gformat, sizeof gformat, "{EBEBEB}Status telefono\t%s\n", (InfoPersonaje[playerid][pTogTelefono]) ? ("{54C822}Encendido") : ("{E81700}Apagado")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Movimiento de manos\t%s\n", (InfoPersonaje[playerid][pTogManos]) ? ("{54C822}Activado") : ("{E81700}Desactivado")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Visualización de anuncios\t%s\n", (InfoPersonaje[playerid][pTogAnuncios]) ? ("{E81700}No") : ("{54C822}Sí")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Visualización de velocímetro\t%s\n", (InfoPersonaje[playerid][pTogVelocimetro]) ? ("{54C822}Sí") : ("{E81700}No")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Mensajes administrativos\t%s\n", (InfoPersonaje[playerid][pTogOOC]) ? ("{54C822}Habilitados") : ("{E81700}Deshabilitados")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Mensajes de radio o whatsapp\t%s\n", (InfoPersonaje[playerid][pTogRadio]) ? ("{54C822}Habilitados") : ("{E81700}Deshabilitados")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Reproductor de música\t%s\n", (InfoPersonaje[playerid][pTogMusic]) ? ("{54C822}Activado") : ("{E81700}Desactivado")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Audio de radio portatil\t%s\n", (InfoPersonaje[playerid][pTogPortatil]) ? ("{54C822}Activado") : ("{E81700}Desactivado")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Mensajes de facción\t%s\n", (InfoPersonaje[playerid][pTogFaccion]) ? ("{54C822}Habilitados") : ("{E81700}Deshabilitados")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Estilo de manos\t{6E97C7}%d\n", InfoPersonaje[playerid][pEstiloManos]); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Visualización de fps/ping\t%s\n", (InfoCuenta[playerid][jTogPing]) ? ("{E81700}No") : ("{54C822}Sí")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Estilo de anuncios\t%s\n", (InfoCuenta[playerid][jEstiloAnuncio]) ? ("{6CAAF2}Chat") : ("{E4940E}Pantalla")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Estilo de bolsillos\t%s\n", (InfoCuenta[playerid][jEstiloBolsillos]) ? ("{6CAAF2}Dialogo") : ("{E4940E}Pantalla")); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Limpiar pantalla\n"); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EBEBEB}Cambiar personaje\n"); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{FF8C69}Configurar personaje");
	Dialog_Show(playerid, ShowPanel, DIALOG_STYLE_TABLIST, "Configuración de cuenta", dialog, "Cambiar", "Salir");
	return 1;
}

cmd:togooc(playerid)
{
	if (InfoPersonaje[playerid][pTogOOC] != 0)
	{
		InfoPersonaje[playerid][pTogOOC] = 0;
		ShowTDN(playerid, "Ahora ~r~~h~no veras~w~ los mensajes administrativos ooc.");
	}
	else
	{
		InfoPersonaje[playerid][pTogOOC] = 1;
		ShowTDN(playerid, "Ahora ~b~~h~puedes ver~w~ los mensajes administrativos ooc.");
	}
	guardar_int_mysql("personajes", "TogOOC", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogOOC]);
	return 1;
}

cmd:togphone(playerid)
{
	if (InfoPersonaje[playerid][pTogTelefono] != 0)
	{
		InfoPersonaje[playerid][pTogTelefono] = 0;
		ShowTDN(playerid, "Ahora tu telefono esta ~r~~h~apagado~w~, ahora no podras recibir llamadas o mensajes.");
	}
	else
	{
		InfoPersonaje[playerid][pTogTelefono] = 1;
		ShowTDN(playerid, "Ahora tu telefono esta ~b~~h~encendido~w~, ahora podras recibir llamadas o mensajes.");
	}
	guardar_int_mysql("personajes", "TogTelefono", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogTelefono]);
	return 1;
}
alias:togphone("togmovil", "togtelefono");

cmd:togmanos(playerid)
{
	if (InfoPersonaje[playerid][pTogManos] != 0)
	{
		InfoPersonaje[playerid][pTogManos] = 0;
		ShowTDN(playerid, "Ahora tienes ~r~~h~desactivado~w~ el movimiento de manos cuando escribes en el chat ic.");
	}
	else
	{
		InfoPersonaje[playerid][pTogManos] = 1;
		ShowTDN(playerid, "Ahora tienes ~b~~h~activado~w~ el movimiento de manos cuando escribes en el chat ic.");
	}
	guardar_int_mysql("personajes", "TogManos", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogManos]);
	return 1;
}

cmd:togmusic(playerid)
{
	if (InfoPersonaje[playerid][pTogMusic] != 0)
	{
		InfoPersonaje[playerid][pTogMusic] = 0;
		TipoAudio[playerid] = 0;
		StopAudioStreamForPlayer(playerid);
		ShowTDN(playerid, "Ahora ~r~~h~no escucharas~w~ los audios de música.");
	}
	else
	{
		InfoPersonaje[playerid][pTogMusic] = 1;
		ShowTDN(playerid, "Ahora ~b~~h~puedes escuchar~w~ los audios de música.");
	}
	guardar_int_mysql("personajes", "TogMusic", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogMusic]);
	return 1;
}
alias:togmusic("togmusica");

cmd:radio(playerid)
{
	if (InfoPersonaje[playerid][pTogRadio] != 0)
	{
		InfoPersonaje[playerid][pTogRadio] = 0;
		ShowTDN(playerid, "Ahora ~r~~h~no veras~w~ los mensajes de radio o whatsapp.");
	}
	else
	{
		InfoPersonaje[playerid][pTogRadio] = 1;
		ShowTDN(playerid, "Ahora ~b~~h~puedes ver~w~ los mensajes de radio o whatsapp.");
	}
	guardar_int_mysql("personajes", "TogRadio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogRadio]);
	return 1;
}
alias:radio("togradio", "togrd", "togwsp");

cmd:togpr(playerid)
{
	if (tiene_objeto(playerid, 50) == 0) return 1;
	new string[195];
	if (InfoPersonaje[playerid][pTogPortatil] != 0)
	{
		InfoPersonaje[playerid][pTogPortatil] = 0;
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, "Has ~r~~h~apagado~w~ tu radio portatil.");
	}
	else
	{
		InfoPersonaje[playerid][pTogPortatil] = 1;
		if (InfoPersonaje[playerid][pFrecuencia_radio] != 0) format(string, sizeof string, "Has ~b~~h~encendido~w~ tu radio portatil, frecuencia sincronizada %d khz.", InfoPersonaje[playerid][pFrecuencia_radio]);
		else format(string, sizeof string, "Has ~b~~h~encendido~w~ tu radio portatil.");
		ShowTDN(playerid, string);
	}
	guardar_int_mysql("personajes", "TogPortatil", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogPortatil]);
	return 1;
}
alias:togpr("togportatil");

cmd:togpm(playerid)
{
	if (!InfoCuenta[playerid][jTogMP])
	{
		InfoCuenta[playerid][jTogMP] = 1;
		ShowTDN(playerid, "Privados bloqueados.");
	}
	else
	{
		InfoCuenta[playerid][jTogMP] = 0;
		ShowTDN(playerid, "Privados habilitados.");
	}
	guardar_int_mysql("cuentas", "TogMP", InfoCuenta[playerid][jID], InfoCuenta[playerid][jTogMP]);
	return 1;
}
alias:togpm("togmp");

cmd:telefono(playerid)
{
	if (InfoPersonaje[playerid][pTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes un número telefónico.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	if (InfoPersonaje[playerid][pTiempoSancion] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estas en prisión.");
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estas herido.");
	new gformat[249], gdialog[480];
	format(gformat, sizeof gformat, "{7777FF}%s\n", Fecha2Hoy()); strcat(gdialog, gformat);
	strcat(gdialog, "{FFFFFF}Marcar un número\n");
	strcat(gdialog, "Enviar un mensaje\n");
	strcat(gdialog, "Aplicaciones\n");
	if (InfoPersonaje[playerid][pTogTelefono] != 0) strcat(gdialog, "{E81700}Apagar {FFFFFF}telefono\n");
	else strcat(gdialog, "{54C822}Encender {FFFFFF}telefono\n");
	format(gformat, sizeof gformat, "Número telefónico: {F5DEB3}%d", InfoPersonaje[playerid][pTelefono]);
	Dialog_Show(playerid, MenuTelefono, DIALOG_STYLE_LIST, gformat, gdialog, "Continuar", "Salir");
	return 1;
}
alias:telefono("celular", "movil");

cmd:botiquin(playerid, params[])
{
	if (no_tiene_manos(playerid, 53) == 0) return 1;
	new playerid2, string[190];
	if (sscanf(params, "u", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /botiquin (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (!CercaDelMarica(3.5, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador no esta cerca tuyo.");
	if (GetPVarInt(playerid2, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador esta en estado herido.");
	if (InfoPersonaje[playerid2][pVida] >= 80) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no necesita botiquin ahora mismo.");
	if (InfoPersonaje[playerid][pManoDerecha] == 53) InfoPersonaje[playerid][pManoDerechaCant]--;
	else InfoPersonaje[playerid][pManoIzquierdaCant]--;
	ActualizarManos(playerid, 1);
	if (playerid != playerid2)
	{
		TogglePlayerControllable(playerid, false);
		TogglePlayerControllable(playerid2, false);
		ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 1, 1, 0, 0, 1);
		ApplyAnimation(playerid2, "CRACK", "crckidle2", 4.1, 1, 1, 1, 0, 0, 1);
		SetCameraBehindPlayer(playerid2);
		format(string, sizeof string, "* %s le da primeros auxilios a %s con su botiquin.", GetNameFormat(playerid), GetNameFormat(playerid2));
		ProxDetector(20.0, playerid, string, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF);
	 	SetTimerEx("CurarBotiquin", 8000, false, "ii", playerid, playerid2);
 	}
 	else
 	{
		new Float: health = InfoPersonaje[playerid][pVida];
		if (health >= 50) dar_vida(playerid, 100);
		else dar_vida(playerid, health + 50.0);
		format(string, sizeof string, "* %s se aplica primeros auxilios con su botiquin.", GetNameFormat(playerid));
		ProxDetector(20.0, playerid, string, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF);
 	}
	return 1;
}
alias:botiquin("hpsave");

cmd:reaparecer(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas en estado herido o muerto.");
	new gformat[186];
	if (timer_herido[playerid] != 0)
	{
		format(gformat, sizeof gformat, "Puedes reaparecer en el hospital en %d segundos.", timer_herido[playerid]);
		SendPlayerChatMessage(playerid, 0x6DDC76FF, gformat);
		return 1;
	}
	GoToHospital(playerid);
	return 1;
}


cmd:payday(playerid)
{
	new string[190];
	format(string, sizeof string, "Faltan {eb4040}%d{FFFFFF} minutos para el próximo {3E62F4}PayDay{FFFFFF}.", 60-InfoPersonaje[playerid][pPayday]);
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}


cmd:desbug(playerid)
{
	switch (InfoPersonaje[playerid][pSancionado])
	{
		case 0:
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			InfoPersonaje[playerid][pInterior] = 0;
			InfoPersonaje[playerid][pVirtualWorld] = 0;
		}
		case 1: // Jail OOC.
		{
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, playerid+1);
			InfoPersonaje[playerid][pInterior] = 0;
			InfoPersonaje[playerid][pVirtualWorld] = playerid+1;
		}
		case 2: // Jail IC
		{
			SetPlayerVirtualWorld(playerid, 60);
			InfoPersonaje[playerid][pVirtualWorld] = 60;
		}
	}
	SendPlayerChatMessage(playerid, -1, "Administración: Esperamos que su problema haya sido solucionado o reloguea.");
	return 1;
}

cmd:w(playerid, params[])
{
	new
		gformat[320],
		mensaje[256],
		playerid2;

	if (InfoCuenta[playerid][jBloqueoMP] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Un Moderator o administrador te bloqueo los permisos de /mp.");
	if (sscanf(params, "ds[256]", playerid2, mensaje)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /w (JugadorID) (Texto) {EBEBEB}El mal uso es sancionable.");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador seleccionado esta desconectado.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes enviarte mensajes a ti mismo.");
	if (InfoCuenta[playerid][jAdmin] == 0)
	{
		if (InfoCuenta[playerid2][jTogMP] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador tiene los mensajes privados bloqueados.");
		//staff
		if (InfoCuenta[playerid2][jAdmin] == 0)
		{
			if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos dos horas, para poder enviar privados.");
			format(gformat, sizeof gformat, "[MP] %s(%d) a %s(%d): %s", NombreOriginal(playerid), playerid, NombreOriginal(playerid2), playerid2, mensaje);
			MensajeMPS(0x3CE755FF, gformat);
		}
		format(gformat, sizeof gformat, "Mensaje de %s (%d): %s", NombreOriginal(playerid), playerid, mensaje);
		SendSplitMessage(playerid2, 0x9F9F00FF, gformat);
		format(gformat, sizeof gformat, "Susurras a %s (%d): %s", NombreOriginal(playerid2), playerid2, mensaje);
		SendSplitMessage(playerid, 0x96964BFF, gformat);
	}
	else
	{
		format(gformat, sizeof gformat, "Mensaje de %s (%d): %s", NombreOriginal(playerid), playerid, mensaje);
		SendSplitMessage(playerid2, 0x9F9F00FF, gformat);
		format(gformat, sizeof gformat, "Susurras a %s (%d): %s", NombreOriginal(playerid2), playerid2, mensaje);
		SendSplitMessage(playerid, 0x96964BFF, gformat);
	}
	return 1;
}
alias:w("mp");

cmd:estilopelea(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 10, 767.6719, 13.6320, 1000.7010)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas en el GYM.");
	Dialog_Show(playerid, FSTYLE_DIALOG, DIALOG_STYLE_LIST, "Que le gustaria aprender?", "Knee Head ($80)\nKung Fu ($140)\nBoxeo ($110)\nCallejero ($90)", "Aprender", "Salir");
	return 1;
}
alias:estilopelea("entrenar");

cmd:ayuda(playerid)
{
	Dialog_Show(playerid, ShowHelp, DIALOG_STYLE_LIST, "Menú de ayuda",
	"Comandos frecuentes\n\
	Facción\n\
	Casas\n\
	Vehículos\n\
	VIP\n\
	Inventario\n\
	Negocio\n\
	Animaciones\n\
	Empleos",
	"Continuar", "Salir");
	return 1;
}
alias:ayuda("help");

cmd:removegps(playerid) return DisablePlayerCheckpoint(playerid);

cmd:entrar(playerid)
{
	if (InfoPersonaje[playerid][pSancionado] == 1) return 1;
	if (GetPVarInt(playerid, "EstaCrack") != 0) return 1;
	new gformat[240];
	//puertas dinamicas
	Loop(id, totalpuertas, 1) if (InfoPuerta[id][pdExteriorX] != 0.0)
	{
		new Float: radius = 1.5;
		if (InfoPuerta[id][pdStatusVehiculo] != 0) radius = 6.0; //new 23/01/2020
		if (IsPlayerInRangeOfPoint(playerid, radius, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoPuerta[id][pdExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoPuerta[id][pdExteriorVW])
		{
		    //nivel vip
			if (InfoCuenta[playerid][jVIP] < InfoPuerta[id][pdVIP])
			{
				format(gformat, sizeof gformat, "Acceso denegado, debes ser mi­nimo VIP %s.", GetNameVIP(InfoPuerta[id][pdVIP]));
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
				return 1;
			}

			//fac
 			if (InfoPuerta[id][pdFaccion] != 0)
			{
			    if (InfoPersonaje[playerid][pMiembro] != InfoPuerta[id][pdFaccion])
			    {
					format(gformat, sizeof gformat, "Acceso denegado, debes ser miembro de %s.", InfoFaccion[InfoPuerta[id][pdFaccion]][fLogo]);
					SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
					return 1;
				}
			}
			//nivel admin
			if (GetPlayerAdmin(playerid, InfoPuerta[id][pdAdmin]) == 0)
			{
				format(gformat, sizeof gformat, "Acceso denegado, debes ser minimo rango %d admin.", InfoPuerta[id][pdAdmin]);
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
				return 1;
			}
			//busqueda captura
			if (InfoPuerta[id][pdEstrellas] != 0 && InfoPersonaje[playerid][pEstrellas] != 0)
			{
				SendPlayerChatMessage(playerid, COLOR_GREY, "Esta puerta esta restringida a personas con nivel de búsqueda.");
				return 1;
			}
			//vehicle
			if (InfoPuerta[id][pdStatusVehiculo] != 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
			    new vehicleid = GetPlayerVehicleID(playerid);
				// Posición.
	         	MoverVehiclePos(vehicleid, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]);
	         	SetVehicleZAngle(vehicleid, InfoPuerta[id][pdInteriorR]);
	          	// vehiculo.
	         	SetVehicleInterior(vehicleid, InfoPuerta[id][pdInteriorInt]);
	          	SetVehicleExVirtualWorld(vehicleid, InfoPuerta[id][pdInteriorVW]);
	          	// Player.
	        	SetPlayerVirtualWorld(playerid, InfoPuerta[id][pdInteriorVW]);
	        	SetPlayerInterior(playerid, InfoPuerta[id][pdInteriorInt]);
	        	// new by EdinsonWalker (16-01-2020)
				foreach(new p: Player) if (IsPlayerInVehicle(p, vehicleid))
				{
					SetPlayerInterior(p, InfoPuerta[id][pdInteriorInt]);
					SetPlayerVirtualWorld(p, InfoPuerta[id][pdInteriorVW]);
				}
			}
			else
			{
				SetPosEx(playerid, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorR], InfoPuerta[id][pdInteriorInt], InfoPuerta[id][pdInteriorVW], 1);
				SetCameraBehindPlayer(playerid);
			}
			return 1;
		}
	}
	//casas dinamicas
	Loop(p, totalcasas, 1) if (InfoCasa[p][cTipo] != 0)
	{
		if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[p][cExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[p][cExteriorVW])
		{
			if (InfoCasa[p][cSeguro] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Puerta cerrada.");
			SetPosEx(playerid, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ], InfoCasa[p][cInteriorR], InfoCasa[p][cInteriorInt], InfoCasa[p][cInteriorVW], 1);
  			SetCameraBehindPlayer(playerid);
        	return 1;
       	}
	}
	//negocios dinamicos
	if (GetExtNegocio(playerid) != -1)
	{
		new id = GetExtNegocio(playerid);
		if (InfoNegocio[id][nSeguro] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este negocio esta cerrado.");
		if (InfoNegocio[id][nTipo] == 9) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El taller ya esta abierto.");
		SetPosEx(playerid, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ], InfoNegocio[id][nInteriorR], InfoNegocio[id][nInteriorInt], InfoNegocio[id][nInteriorVW], 1);
		SetCameraBehindPlayer(playerid);
	}

	if (IsPlayerInRangeOfPoint(playerid,3,853.3862,-1387.1884,13.7470)) //  GARAGE VIP
	{
		if (InfoCuenta[playerid][jVIP] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Acceso sólo para usuarios VIP.");
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			MoverVehiclePos(GetPlayerVehicleID(playerid),  855.6053,-1412.6117,4202.1577);
			SetVehicleZAngle(GetPlayerVehicleID(playerid),  0);
		}
		else
		{
			SetPosEx(playerid, 855.6053,-1412.6117,4202.1577, 0, 0, 0, 1);
			SetCameraBehindPlayer(playerid);
		}
		return 1;
	}
	return 1;
}
alias:entrar("enter");

cmd:salir(playerid)
{
	if (InfoPersonaje[playerid][pSancionado] == 1) return 1;
	if (GetPVarInt(playerid, "EstaCrack") != 0) return 1;
	//puertas dinamicas
	Loop(id, totalpuertas, 1) if (InfoPuerta[id][pdInteriorX] != 0.0)
	{
		new Float: radius = 1.5;
		if (InfoPuerta[id][pdStatusVehiculo] != 0) radius = 6.0; //new 23/01/2020
		if (IsPlayerInRangeOfPoint(playerid, radius, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]) && InfoPersonaje[playerid][pVirtualWorld] == InfoPuerta[id][pdInteriorVW])
		{
			if (InfoPuerta[id][pdStatusVehiculo] != 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
			{
				// Posicion.
				MoverVehiclePos(GetPlayerVehicleID(playerid), InfoPuerta[id][pdExteriorX],InfoPuerta[id][pdExteriorY],InfoPuerta[id][pdExteriorZ]);
				SetVehicleZAngle(GetPlayerVehicleID(playerid), InfoPuerta[id][pdExteriorR]);
				// vehiculo.
				SetVehicleInterior(GetPlayerVehicleID(playerid), InfoPuerta[id][pdExteriorInt]);
				SetVehicleExVirtualWorld(GetPlayerVehicleID(playerid), InfoPuerta[id][pdExteriorVW]);
				// Player.
				SetPlayerVirtualWorld(playerid, InfoPuerta[id][pdExteriorVW]);
				SetPlayerInterior(playerid,InfoPuerta[id][pdExteriorInt]);
				// new by EdinsonWalker (16-01-2020)
				foreach(new p: Player) if (IsPlayerInVehicle(p,GetPlayerVehicleID(playerid)))
				{
					SetPlayerInterior(p, InfoPuerta[id][pdExteriorInt]);
					SetPlayerVirtualWorld(p, InfoPuerta[id][pdExteriorVW]);
				}
			}
			else
			{
				SetPosEx(playerid, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorR], InfoPuerta[id][pdExteriorInt], InfoPuerta[id][pdExteriorVW], 1);
				SetCameraBehindPlayer(playerid);
				//Cargado
				ShowLoadScreen(playerid, 3000);
			}
			return 1;
		}
	}
	//casas dinamicas
	Loop(p, totalcasas, 1) if (InfoCasa[p][cTipo] != 0)
	{
		if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoCasa[p][cInteriorX], InfoCasa[p][cInteriorY], InfoCasa[p][cInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[p][cInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[p][cInteriorVW])
		{
			SetPosEx(playerid, InfoCasa[p][cExteriorX], InfoCasa[p][cExteriorY], InfoCasa[p][cExteriorZ], InfoCasa[p][cExteriorR], InfoCasa[p][cExteriorInt], InfoCasa[p][cExteriorVW], 1);
			SetCameraBehindPlayer(playerid);
			DentroCasa[playerid] = -1;
			KillTimer(VisitaTimer[playerid]);
			ShowLoadScreen(playerid, 3000);
			return 1;
		}
	}
	//negocios dinamicos
	if (GetIntNegocio(playerid) != -1)
	{
		new id = GetIntNegocio(playerid);
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPosEx(playerid, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorR], InfoNegocio[id][nExteriorInt], InfoNegocio[id][nExteriorVW], 1);
			SetCameraBehindPlayer(playerid);
			DentroNegocio[playerid] = -1;
			//Cargado
			ShowLoadScreen(playerid, 3000);
		}
		return 1;
	}

	if (IsPlayerInRangeOfPoint(playerid,8,855.6053,-1412.6117,4202.1577)) //  GARAGE VIP
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			MoverVehiclePos(GetPlayerVehicleID(playerid),  853.3862,-1387.1884,13.7470);
			SetVehicleZAngle(GetPlayerVehicleID(playerid),  182.4513);
		}
		else
		{
			SetPosEx(playerid, 853.3862,-1387.1884,13.7470, 182.4513, 0, 0, 1);
			SetCameraBehindPlayer(playerid);
		}
		return 1;
	}
	return 1;
}
alias:salir("exit", "sair");

cmd:frecuencia(playerid, params[])
{
	if (tiene_objeto(playerid, 50) == 0) return 1;
	new string[128], frequency;
	if (sscanf(params, "d", frequency))
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /frecuencia [frecuencia]");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "* Ajusta la frecuencia de tu radio - 0 Si no quieres oir nada.");
		return 1;
	}
	if (frequency > 9999999 || frequency < -9999999) { SendPlayerChatMessage(playerid, COLOR_GREY, "Frecuencia no debe ser menor a -9999999 y mayor 9999999."); return 1; }

	InfoPersonaje[playerid][pFrecuencia_radio] = frequency;
    guardar_int_mysql("personajes", "Frecuencia_radio", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pFrecuencia_radio]);
	format(string, sizeof string, "Ajustaste la frecuencia de tu radio portable a %d khz.",frequency);
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	return 1;
}

cmd:pr(playerid, params[])
{
	if (tiene_objeto(playerid, 50) == 0) return 1;
	if (InfoPersonaje[playerid][pFrecuencia_radio] >= 1 || InfoPersonaje[playerid][pFrecuencia_radio] <= -1)
	{
		if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /pr (Texto)");
		if (GetPVarInt(playerid, "EstaCrack") != 0) return SendClientMessage (playerid, COLOR_GREY, "No puedes usar esto ahora.");
		RadioBroadCast(playerid, COLOR_GREY, params);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "* Primero ajusta la frecuencia. /frecuencia'");
	return 1;
}

cmd:prooc(playerid, params[])
{
	if (InfoPersonaje[playerid][pFrecuencia_radio] >= 1 || InfoPersonaje[playerid][pFrecuencia_radio] <= -1)
	{
		if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /prooc");
		if (GetPVarInt(playerid, "EstaCrack") != 0) return SendClientMessage (playerid, COLOR_GREY, "No puedes usar esto ahora.");
		RadioBroadCastOOC(playerid, COLOR_GREY, params);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "* Primero ajusta la frecuencia. /frecuencia'");
	return 1;
}

cmd:pagar(playerid, params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos 2 horas el servidor.");
	new string[256];
	if (sscanf(params, "dd", params[0], params[1])) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /pagar (JugadorID) (Cantidad $)");
	if (!IsPlayerConnected(params[0])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (playerid == params[0]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Buenooo.. tiras el dinero arriba y te cae encimaXd??");
	if (params[1] > GetPlayerCash(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No posees esa cantidad.");
	if (params[1] < 1 || params[1] > 15000) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo puedes pasar entre 1 y 15,000 dólares.");
	if (!CercaDelMarica(3.0, playerid, params[0])) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador muy lejos.");
	GivePlayerCash(playerid, -params[1], "pagar");
	GivePlayerCash(params[0], params[1], "pagar");
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	if (InfoCuenta[playerid][jMulticuenta] == 0 && InfoCuenta[params[0]][jMulticuenta] == 0)
	{
		if (!strcmp(InfoCuenta[playerid][jIP], InfoCuenta[params[0]][jIP], false))
		{
			new ipc[32], stringlog[180]; GetPlayerIp(playerid, ipc, 32);
			format(stringlog, sizeof(stringlog), "[ATENCION] Posibles multicuentas: %s(%d) ha pagado [$%d] a %s(%d). [IP: %s]", NombreOriginal(playerid), playerid, params[1],NombreOriginal(params[0]), params[0], ipc);
			SendAdminMessage(COLOR_ORANGE, stringlog); Log("f_logs/multicuentas.log", stringlog);
		}
	}
	PlayerPlaySound(playerid, 1052, X, Y, Z);
	PlayerPlaySound(params[0], 1052, X, Y, Z);
	format(string, sizeof string, "saca $%s dólares y se los da %s.", diner_coma(params[1]), GetNameFormat(params[0]));
	rol_auto(playerid, string);
	format(string, sizeof string, "* %s pagó %d$ a %s", NombreDeCuenta(playerid), params[1], NombreDeCuenta(params[0]));
	Log("f_logs/pagos.log", string);
	return 1;
}

cmd:cuenta(playerid)
{
	Show_cuenta(playerid, playerid);
	return 1;
}
alias:cuenta("stats", "est", "estadisticas");


cmd:robar247(playerid, params[])
{
	//if (!member_faccion(playerid, 9, 10)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No formas parte de una pandilla o mafia.");
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estas herido.");
	if (InfoPersonaje[playerid][pSancionado] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar esto aqui­.");
	new string[256];
	if (InfoPersonaje[playerid][pLimiteRobos] != 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ya robaste, espera al próximo PayDay.");
	if (!Tienda_247(playerid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No estas en ningún 24/7.");
	new robmoney = Random(500, 3500);
	GivePlayerCash(playerid, robmoney, "robo 24-7");
	ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0, 4000, 1); // Rob
	InfoPersonaje[playerid][pLimiteRobos] = 1;
	guardar_int_mysql("personajes", "LimiteRobos", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pLimiteRobos]);
	rol_auto(playerid, "amenaza con un arma al vendedor.");
	
	//
	format(string, sizeof string, "[CENTRAL] Robo reciente en el 24-7, sospechoso %s.", GetNameFormat(playerid));
	SendRadioMessage(1, COLOR_RADIO, string, 5);
	SendRadioMessage(4, COLOR_RADIO, string, 5);
	
	//
	format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) acaba de robar un 24-7.", NombreOriginal(playerid), playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}


cmd:licencias(playerid, params[])
{
	if (InfoPersonaje[playerid][pSancionado] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estas en prisión.");
	new car[32], fly[32], boat[32], gun[32], playerid2, string[320];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /licencias (JugadorID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (!CercaDelMarica(4.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estas demasiado lejos del jugador.");
	if (InfoPersonaje[playerid][pLicencia][0] != 0) car = "{2CC705}Si­{EBEBEB}";
	else car = "{FC2710}No{EBEBEB}";
	if (InfoPersonaje[playerid][pLicencia][1] != 0) boat = "{2CC705}Si­{EBEBEB}";
	else boat = "{FC2710}No{EBEBEB}";
	if (InfoPersonaje[playerid][pLicencia][2] != 0) fly = "{2CC705}Si­{EBEBEB}";
	else fly = "{FC2710}No{EBEBEB}";
	if (InfoPersonaje[playerid][pLicencia][3] != 0) gun = "{2CC705}Si­{EBEBEB}";
	else gun = "{FC2710}No{EBEBEB}";
	format(string, sizeof string, "LICENCIAS LEGALES | %s (%d)", GetNameFormat(playerid), InfoPersonaje[playerid][pDocumento]);
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "Conducir: %s - Vuelo: %s - Armas: %s - Navegación: %s", car, fly, gun, boat);
	SendPlayerChatMessage(playerid2, 0xEBEBEBFF, string);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid2, 1052, 0.0, 0.0, 0.0);
	format(string, sizeof string, "muestra sus licencias a %s.", GetNameFormat(playerid2));
	if (playerid != playerid2) rol_ame(playerid, string);
	return 1;
}
alias:licencias("licencia", "mostrarlicencias");

cmd:dni(playerid, params[])
{
	if (InfoPersonaje[playerid][pSancionado] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estas en prisión.");
	new gformat[170], playerid2, sex[18], otext[36];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dni (JugadorID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (!CercaDelMarica(4.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador muy lejos.");
	if (InfoPersonaje[playerid][pSexo] == 1) sex = "Masculino";
	else sex = "Femenino";
	if (InfoPersonaje[playerid][pCiudad] == 2) otext = "San Fierro";
	else if (InfoPersonaje[playerid][pCiudad] == 1) otext = "Los Santos";
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, "PAPELES LEGALES | DOCUMENTO DE NACIONALIDAD");
	format(gformat, sizeof gformat, "Nombre completo: %s - Sexo: %s - Edad: %d", GetNameFormat(playerid), sex, InfoPersonaje[playerid][pEdad]);
	SendPlayerChatMessage(playerid2, 0xEBEBEBFF, gformat);
	format(gformat, sizeof gformat, "Nacionalidad: %s - Documento: %d", otext, InfoPersonaje[playerid][pDocumento]);
	SendPlayerChatMessage(playerid2, 0xEBEBEBFF, gformat);
	PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
	PlayerPlaySound(playerid2, 1052, 0.0, 0.0, 0.0);
	format(gformat, sizeof gformat, "le muestra su documento a %s.", GetNameFormat(playerid2));
	if (playerid != playerid2) rol_ame(playerid, gformat);
	return 1;
}
alias:dni("mostrardni", "documento");

cmd:reportarbug(playerid)
{
	if (InfoPersonaje[playerid][pBlockBug] != 0) return SendPlayerChatMessage(playerid, COLOR_RED, "[ATENCION]:{FFFFFF} No puedes reportar bugs, estas bloqueado del comando.");
	if (!CheckTimer(180, TimerReportarBug))
	{
		TimerReportarBug = gettime();
		Dialog_Show(playerid, REBUG, DIALOG_STYLE_INPUT, "Reportar Bug", "{EBEBEB}Escribe exactamente el bug que has encontrado, se quedara guardado en la base de datos\ncuando el equipo de desarrolladores lo revise, trataran de solucionar el bug lo mas rapido posible.\n\nGracias por reportar.", "Reportar", "Salir");
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, TimerReportarBug) ));
	}
	return 1;
}


cmd:re(playerid, params[])
{
	if (AdminOnlineCheck() == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No hay {FF0000}administradores online{FFFFFF} en este momento, intenta mas tarde.");
	if (JustReported[playerid] > 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "{A2DC35}[INFO]:{FFFFFF} Espera 60 segundos para otro reporte.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /re (REPORTE)");

	SendReportToQue(playerid, params);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Tu reporte fue enviado al equipo de {eb4040}administración{FFFFFF} en breve te ayudaran.");
	JustReported[playerid] = 60;
	return 1;
}

cmd:creporte(playerid)
{
	Loop(i, MAX_REPORTS, 0) if (Reports[i][ReportFrom] == playerid)
	{
		Reports[i][ReportFrom] = 999;
		Reports[i][BeingUsed] = 0;
		Reports[i][TimeToExpire] = 0;
		return SendPlayerChatMessage(playerid, COLOR_WHITE, "Cancelaste el reporte satisfactoriamente." );
	}
	SendPlayerChatMessage(playerid, COLOR_GRAD2, "Actualmente no tienes reportes pendientes.");
	return 1;
}

cmd:removergps(playerid)
{
	DisablePlayerCheckpoint(playerid);
	return 1;
}

cmd:apgarage(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 15.0, 1622.9014, -1852.7107, 13.5014))
	{
		if (!member_faccion(playerid, 1, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de LSPD o LSCSD.");
		if (open_embargo == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El portón del depósito ya esta abierto.");
        MoveDynamicObject(depositoembargo, 1612.0996,-1861.5996,15.3000, 2.5);
		SetTimer("ClosedDeposito", 7000, false);
		open_embargo = 1;
		rol_auto(playerid, "abre el portón del depósito de embargos.");
	}
	//USMC
	if (IsPlayerInRangeOfPoint(playerid, 20.0, 134.5650, 1941.5498, 21.6258))
	{
		if (!member_faccion(playerid, 3)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de USMC.");
		MoveDynamicObject(porton_usmc, 148.5000, 1941.5498, 21.6258, 5.0);
		SetTimer("Closed_USMC", 7000, false);
	}
	return 1;
}
alias:apgarage("deposito", "porton");

cmd:atar(playerid, params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas haber jugado al menos 10 horas.");
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estas herido.");
	if (Rope[playerid] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes una cuerda.");
	new playerid2, string[129];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /atar (ID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador desconectado.");
	if (!CercaDelMarica(4.0,playerid,playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador muy lejos.");
	if (Tied[playerid2] == 0)
	{
		Tied[playerid2] = 1;
		format(string, sizeof string, "* %s agarra una cuerda y ata a %s", GetNameFormat(playerid), GetNameFormat(playerid2));
		ProxDetector(20.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		TogglePlayerControllable(playerid2, false);
	}
	else
	{
		Tied[playerid2] = 0;
		format(string, sizeof string, "* %s agarra una cuerda y desata a %s", GetNameFormat(playerid), GetNameFormat(playerid2));
		ProxDetector(20.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		TogglePlayerControllable(playerid2, true);
	}
	return 1;
}

cmd:vendar(playerid, params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas haber jugado al menos 10 horas.");
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estas herido.");
	if (Rope[playerid] == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes venda.");
	new playerid2, string[129];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /vendar (ID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador desconectado.");
	if (!CercaDelMarica(4.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador muy lejos.");
	if (Blinded[playerid2] == 0)
	{
		Blinded[playerid2] = 1;
		format(string, sizeof string, "* %s venda los ojos de %s", GetNameFormat(playerid), GetNameFormat(playerid2));
		ProxDetector(20.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		SetPlayerCameraPos(playerid2,0.0,0.0,1000);
		SetPlayerCameraLookAt(playerid2,0.0,0.0,5000);
	}
	else
	{
		Blinded[playerid2] = 0;
		format(string, sizeof string, "* %s desvenda los ojos de %s", GetNameFormat(playerid), GetNameFormat(playerid2));
		ProxDetector(20.0,playerid,string,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
		SetCameraBehindPlayer(playerid2);
	}
	return 1;
}

/*cmd:me(playerid, params[])
{
	if (isnull(params) || strlen(params) > 256) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /me (acción)");
	new string[256];
	format(string, sizeof string, "%s %s", GetNameFormat(playerid), params);
	ProxDetector(20.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	return 1;
}

cmd:do(playerid, params[])
{
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /do (entorno o aclaración)");
	new string[256];
	format(string, sizeof string, "[%s] %s", GetNameFormat(playerid), params);
	ProxDetector(30.0, playerid, string, COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN,COLOR_LIGHTGREEN);
	return 1;
}
cmd:s(playerid, params[])
{
	new string[256];
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /s (texto a susurrar)");
	format(string, sizeof string, "%s susurra: %s", GetNameFormat(playerid), params);
	ProxDetector(3.0, playerid, string,COLOR_FADE1,COLOR_FADE2,COLOR_FADE3,COLOR_FADE4,COLOR_FADE5);
	return 1;
}

cmd:g(playerid, params[])
{
	new string[256];
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /g (texto a gritar)");
	format(string, sizeof string, "%s grita: Â¡%s!", GetNameFormat(playerid), params);
	ProxDetector(30.0, playerid, string,COLOR_WHITE,COLOR_WHITE,COLOR_WHITE,COLOR_FADE1,COLOR_FADE2);
	return 1;
}*/
cmd:me(playerid, params[])
{
    if (isnull(params) || strlen(params) > 256) {
        return SendClientMessage(playerid, COLOR_GREEN, "Utiliza: /me (acción)");
    }
    new string[512];
    format(string, sizeof(string), "{player:%d} %s", playerid, params);
    ProxDetector(20.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
    return 1;
}

cmd:do(playerid, params[])
{
    if (isnull(params)) {
        return SendClientMessage(playerid, COLOR_GREEN, "Utiliza: /do (entorno o aclaración)");
    }
    new string[512];
    format(string, sizeof(string), "[{player:%d}] %s", playerid, params);
    ProxDetector(30.0, playerid, string, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN);
    return 1;
}

cmd:s(playerid, params[])
{
    new string[512]; // Buffer ampliado para el placeholder y el texto
    if (isnull(params)) {
        return SendClientMessage(playerid, COLOR_GREEN, "Utiliza: /s (texto a susurrar)");
    }
    format(string, sizeof(string), "{player:%d} susurra: %s", playerid, params);
    ProxDetector(3.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
    return 1;
}

cmd:g(playerid, params[])
{
    new string[512];
    if (isnull(params)) {
        return SendClientMessage(playerid, COLOR_GREEN, "Utiliza: /g (texto a gritar)");
    }
    format(string, sizeof(string), "{player:%d} grita: %s!", playerid, params);
    ProxDetector(30.0, playerid, string, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_FADE1, COLOR_FADE2);
    return 1;
}

cmd:ame(playerid, params[])
{
	if (isnull(params) || strlen(params) > 256) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ame (acción corta)");
	rol_ame(playerid, params);
	return 1;
}

cmd:b(playerid, params[])
{
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /b (ooc chat)");
	new string[320];
	if (AdminDuty[playerid] != 0) format(string, sizeof string, "{FF2F2F}[STAFF]{C8C8C8} %s: (( %s ))", InfoCuenta[playerid][jNombre], params);
	else format(string, sizeof string, "[OOC] %s: (( %s ))", NombreOriginal(playerid), params);
	ProxDetector(25.0, playerid, string, 0xC8C8C8FF, 0xC8C8C8FF, 0xC8C8C8FF, 0xC8C8C8FF, 0xC8C8C8FF);
	return 1;
}

cmd:eliminarcheckpoint(playerid)
{
    DeletePVar(playerid, "TrackCar");
    DisablePlayerCheckpoint(playerid);
    SendPlayerChatMessage(playerid, 0xA2DC35FF, "Todos los checkpoints fueron eliminados.");
	return 1;
}
alias:eliminarcheckpoint("eliminarcp", "borrarcp");

cmd:comprarlicencia(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, 1561.7712,-1673.9811,2110.5364)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas en la comisaria de los santos.");
	if (InfoPersonaje[playerid][pEstrellas] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Tienes órden de arresto, te prohibieron la adquisición de licencias.");
	Dialog_Show(playerid, ShowBuyLicencias, DIALOG_STYLE_LIST, "Licencias", "Conducir ($900)\nNavegación ($2,000)\nVuelo ($3,500)", "Comprar", "Salir");
	return 1;
}


cmd:reply(playerid, params[])
{
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /reply (texto)");
	new string[128], reportid = -1;
	Loop(i, MAX_REPORTS, 0)
	{
		if (Reports[i][ReportFrom] == playerid && Reports[i][CheckingReport] != 999)
		{
			reportid = i;
		}
	}
	if (reportid == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas en un reporte ahora mismo.");
	if (!IsPlayerConnectedEx(Reports[reportid][CheckingReport])) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es invalida.");
	format(string, sizeof string, "{FF0000}[RID]{FFFFFF} %s(ID: %d): %s", NombreOriginal(playerid), playerid, params);
	SendPlayerChatMessage(Reports[reportid][CheckingReport], COLOR_YELLOW, string);
	format(string, sizeof string, "{F5DEB3}Respuesta enviada{FFFFFF} a %s: %s", InfoCuenta[Reports[reportid][CheckingReport]][jNombre], params);
	SendPlayerChatMessage(playerid,  COLOR_YELLOW, string);
	return 1;
}

cmd:id(playerid, params[])
{
	new id, string[232], colorping[19];
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /id (Nombre o ID)");
	if (isnumeric(params))
	{
		sscanf(params, "d", id);
		if (!IsPlayerConnected(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
		if (InfoPersonaje[id][pHorasOn] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador esta logeando.");
		switch (GetPlayerPing(id))
		{
			case 0..150: alm(colorping, "{46e800}");
			case 151..200: alm(colorping, "{E0F600}");
			case 201..250: alm(colorping, "{FED32C}");
			case 251..300: alm(colorping, "{f7e300}");
			default: alm(colorping, "{f74000}");
		}
		if (InfoCuenta[playerid][jAdmin] != 0) format(string, sizeof string, "[ID: %d] {F5DEB3}%s{C4C4FF} (Horas: %d) (Ping: %s%d{C4C4FF}) (Cuenta: {FFBF00}%s{C4C4FF})", id, Nombre2Original(id),  InfoPersonaje[id][pHorasOn], colorping, GetPlayerPing(id), InfoCuenta[id][jNombre]);
		else format(string, sizeof string, "[ID: %d] {F5DEB3}%s{C4C4FF} (Horas: %d) (Ping: %s%d{C4C4FF})", id, Nombre2Original(id),  InfoPersonaje[id][pHorasOn], colorping, GetPlayerPing(id));
		SendPlayerChatMessage(playerid, 0xC4C4FFFF, string);
	}
	else
	{
		if (strlen(params) < 3 || strlen(params) > MAX_PLAYER_NAME) return SendPlayerChatMessage(playerid, COLOR_GREY, "El nombre del jugador debe estar entre 3 a 24 caracteres.");
		new count;
		foreach (new playerid2: Player) if (strfind(ReturnName(playerid2), params, true) != -1)
		{
			if (InfoPersonaje[playerid2][pHorasOn] != -1)
			{
				switch (GetPlayerPing(playerid2))
				{
					case 0..150: alm(colorping, "{46e800}");
					case 151..200: alm(colorping, "{E0F600}");
					case 201..250: alm(colorping, "{FED32C}");
					case 251..300: alm(colorping, "{f7e300}");
					default: alm(colorping, "{f74000}");
				}
				if (InfoCuenta[playerid][jAdmin] != 0) format(string, sizeof string, "[ID: %d] {F5DEB3}%s{C4C4FF} (Horas: %d) (Ping: %s%d{C4C4FF}) (Cuenta: {FFBF00}%s{C4C4FF})", playerid2, Nombre2Original(playerid2),  InfoPersonaje[playerid2][pHorasOn], colorping, GetPlayerPing(playerid2), InfoCuenta[playerid2][jNombre]);
				else format(string, sizeof string, "[ID: %d] {F5DEB3}%s{C4C4FF} (Horas: %d) (Ping: %s%d{C4C4FF})", playerid2, Nombre2Original(playerid2),  InfoPersonaje[playerid2][pHorasOn], colorping, GetPlayerPing(playerid2));
				SendPlayerChatMessage(playerid, 0xC4C4FFFF, string);
				count++;
			}
		}
		if (!count) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay ningún jugador con ese nombre conectado.");
	}
	return 1;
}

cmd:duda(playerid, params[])
{
	new Texto[128];
	if (JustDuda[playerid] > 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Espera 60 segundos para mandar otra duda.");
	if (AdminOnlineCheck() == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No hay {FF0000}administradores online{FFFFFF} en este momento, intenta mas tarde.");
	if (sscanf(params, "s[128]", Texto)) return SendPlayerChatMessage(playerid, -1, "Utiliza: {3E62F4}/duda{FFFFFF} (texto)");
	new string[322];
	format(string, sizeof string, "{2F99B5}%s(%d){FFFFFF} pregunta: {FF0000}%s", NombreOriginal(playerid), playerid, Texto);
    SendAdminMessage(0xFF0000FF, string);
	format(string, sizeof string, "Tu duda se ha mandado satifactoriamente a %d administrador(es)", AdminOnlineCheck());
	SendPlayerChatMessage(playerid,COLOR_WHITE,string);
	JustDuda[playerid] = 60;
	PlayerDuda[playerid] = 1;
	alm(PlayerTextoDuda[playerid], Texto);
	return 1;
}

cmd:cinturon(playerid, params[]){
    if(!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas en un vehiculo.");
	new string[50 + MAX_PLAYER_NAME];
    if(IsPlayerInAnyVehicle(playerid) == 1 && Seatbelt[playerid] == 0){
        Seatbelt[playerid] = 1;
        if(IsABike(GetPlayerVehicleID(playerid))){format(string, sizeof string, "* %s agarra su casco, y se lo pone.", GetNameFormat(playerid));}
        else { format(string, sizeof string, "* %s pone las manos en su cinturón y se lo pone.", GetNameFormat(playerid)); }
    }
    else if(IsPlayerInAnyVehicle(playerid) == 1 && Seatbelt[playerid] == 1){
        Seatbelt[playerid] = 0;
        if(IsABike(GetPlayerVehicleID(playerid))){format(string, sizeof string, "* %s pone las manos en su casco, y se lo quita.", GetNameFormat(playerid));}
        else { format(string, sizeof string, "* %s pone las manos en su cinturón y se lo quita.", GetNameFormat(playerid)); }
    }
    ProxDetector(20.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
    return 1;
}

cmd:vercinturon(playerid, params[]){
	new playerid2;
	if(sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /vercinturon (Jugador)");
    if(GetPlayerState(playerid2) == PLAYER_STATE_ONFOOT) return SendPlayerChatMessage(playerid,COLOR_GREY,"Ese jugador no esta en un vehiculo!");
    if (CercaDelMarica(9.0, playerid, playerid2)){
		new string[128];
        new stext[4];
        if(Seatbelt[playerid2] == 0) { stext = "sin"; }
        else { stext = "con"; }
        if(IsABike(GetPlayerVehicleID(playerid))){
            format(string, sizeof string, "%s esta %s casco." , GetNameFormat(playerid2) , stext);
            SendPlayerChatMessage(playerid,COLOR_WHITE,string);

            format(string, sizeof string, "* %s mira a %s, mirando si tiene puesto su casco.", GetNameFormat(playerid),GetNameFormat(playerid2));
            ProxDetector(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
        }
        else{
            format(string, sizeof string, "%s esta %s cinturón." , GetNameFormat(playerid2) , stext);
            SendPlayerChatMessage(playerid,COLOR_WHITE,string);

            format(string, sizeof string, "* %s observa a traves de la ventana de %s, mirando si usa el cinturón.", GetNameFormat(playerid),GetNameFormat(playerid2));
            ProxDetector(30.0, playerid, string, COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE,COLOR_PURPLE);
        }
    }
    else { SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas cerca de ese jugador!"); }
    return 1;
}

cmd:animaciones(playerid)
{
	SendPlayerChatMessage(playerid, 0xC2A2DAAA,"_________________________________________________________________________________");
	SendPlayerChatMessage(playerid, COLOR_GREEN, "Animaciones:");
	SendPlayerChatMessage(playerid, COLOR_WHITE,	"/poli /rendirse /asiento /bailar /rap /cruzar /ped /jiggy /fuck /pandillero /dj");
	SendPlayerChatMessage(playerid, COLOR_GREY,		"/fumando /sexo /orinar /chora /relax /fascista /lavar /llorar /mirarse /rifle");
	SendPlayerChatMessage(playerid, COLOR_WHITE,	"/tocar /saludo /cielo /enganche /cpr /bebiendo /palmada /borracho /besar /carga");
	SendPlayerChatMessage(playerid, COLOR_GREY,  	"/basket /lowrider /bartender /protestar /auxilio /gym /animauto /ganar /perder");
	SendPlayerChatMessage(playerid, COLOR_WHITE,	"/reir /robman /cubrirse /vomitar /comiendo /taichi /dormir /casino /rearma /dubstep");
	SendPlayerChatMessage(playerid, COLOR_GREY,  	"/negar /masticar /esquivar /zapatear /convulsionar /hablartel /mirarlados /herido");
	SendPlayerChatMessage(playerid, COLOR_WHITE, 	"/consola /dealer /azotar /cansado /sacoboxeo /acomodar /deacuerdo /empujar /pintar");
	SendPlayerChatMessage(playerid, COLOR_GREY, 	"/peluquero /animtienda /mirarcielo /asombrado /gritar /pajearse /aburrido /bate");
	SendPlayerChatMessage(playerid, COLOR_WHITE, 	"/bailarsexi /abanicarse /caminando /arobar /camara /hablando /sentadilla /apuntar");
	SendPlayerChatMessage(playerid, COLOR_GREY, 	"/apoyarse /billar /correr /mecanico /strip /brazos /oficina");
	return SendPlayerChatMessage(playerid, 0xC2A2DAAA,"_________________________________________________________________________________");
}
alias:animaciones("acciones");


cmd:oficina(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /oficina (1-10)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"INT_OFFICE", "FF_Dam_Fwd", 4.0, 0, 0, 0, 1, 0);
		case 2: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_2Idle_180", 4.0, 0, 0, 0, 1, 0);
		case 3: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Bored_Loop", 4.0, 0, 0, 0, 1, 0);
		case 4: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Crash", 4.0, 0, 0, 0, 1, 0);
		case 5: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Drink", 4.0, 0, 0, 0, 1, 0);
		case 6: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Idle_Loop", 4.0, 0, 0, 0, 1, 0);
		case 7: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_In", 4.0, 0, 0, 0, 1, 0);
		case 8: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Read", 4.0, 0, 0, 0, 1, 0);
		case 9: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Type_Loop", 4.0, 0, 0, 0, 1, 0);
		case 10: ApplyAnimEx(playerid, 0,"INT_OFFICE", "OFF_Sit_Watch", 4.0, 0, 0, 0, 1, 0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /oficina (1-10)");
	}
	return 1;
}

cmd:brazos(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /brazos (1-6)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"CASINO", "cards_in",4.1,0,1,1,1,1);
		case 2: ApplyAnimEx(playerid, 0,"COP_AMBIENT", "Coplook_shake",4.1,0,1,1,1,1);
		case 3: ApplyAnimEx(playerid, 0,"COP_AMBIENT", "Coplook_think",4.1,0,1,1,1,1);
		case 4: ApplyAnimEx(playerid, 0,"COP_AMBIENT", "Coplook_watch",4.1,0,1,1,1,1);
		case 5: ApplyAnimEx(playerid, 0,"DEALER", "DEALER_IDLE",4.1,0,1,1,1,1);
		case 6: ApplyAnimEx(playerid, 0,"GRAVEYARD", "prst_loopa",4.1,0,1,1,1,1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /brazos (1-6)");
	}
	return 1;
}

cmd:strip(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /strip (1-7)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 0,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1);
		case 3: ApplyAnimEx(playerid, 0,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1);
		case 4: ApplyAnimEx(playerid, 0,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1);
		case 5: ApplyAnimEx(playerid, 0,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1);
		case 6: ApplyAnimEx(playerid, 0,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1);
		case 7: ApplyAnimEx(playerid, 0,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /strip (1-7)");
	}
	return 1;
}

cmd:mecanico(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mecanico (1-2)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"CAR", "Fixn_Car_Loop", 4.1, 1, 0, 0, 1, 1);
		case 2: ApplyAnimEx(playerid, 0,"CAR", "Fixn_Car_Out", 4.1, 0, 0, 0, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mecanico (1-2)");
	}
	return 1;
}

cmd:correr(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /correr (1-6)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"PED", "run_civi", 4.1, 1, 1, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 0,"PED", "run_gang1", 4.1, 1, 1, 1, 1, 1);
		case 3: ApplyAnimEx(playerid, 0,"PED", "run_old", 4.1, 1, 1, 1, 1, 1);
		case 4: ApplyAnimEx(playerid, 0,"PED", "run_fat", 4.1, 1, 1, 1, 1, 1);
		case 5: ApplyAnimEx(playerid, 0,"PED", "woman_run", 4.1, 1, 1, 1, 1, 1);
		case 6: ApplyAnimEx(playerid, 0,"PED", "WOMAN_runsexy", 4.1, 1, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /correr (1-6)");
	}
	return 1;
}

cmd:billar(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /billar (1-3)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0, "POOL", "POOL_Idle_Stance", 4.1, 0, 1, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 0, "POOL", "POOL_Med_Start", 4.1, 0, 1, 1, 1, 1);
		case 3: ApplyAnimEx(playerid, 0, "POOL", "POOL_Med_Shot", 4.1, 0, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /billar (1-3)");
	}
	return 1;
}

cmd:apoyarse(playerid, params[])
{
	new animacion;
	if  (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /apoyarse (1-2)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"GANGS", "leanIDLE", 4.0, 1, 0, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 0,"MISC", "Plyrlean_loop", 4.0, 1, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /apoyarse (1-2)");
	}
	return 1;
}

cmd:stopanim(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar esto mientras estas herido.");
 	if (GetPVarInt(playerid, "PlayerCuffed") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar esto en ese estado.");
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	ClearAnimations(playerid);
	StopApplyAnimEx(playerid);
	return 1;
}

cmd:poli(playerid, params[])
{
	if (GetPVarInt(playerid, "EstaCrack") != 0 || IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes realizar esta animación dentro de un vehiculo o estado herido.");
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /poli (1-4)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"POLICE","CopTraf_Come",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"POLICE","CopTraf_Stop",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"POLICE","CopTraf_Away",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"POLICE","CopTraf_Left",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /poli (1-4)");
	}
	return 1;
}

cmd:rendirse(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estas herido.");
 	if (GetPVarInt(playerid, "PlayerCuffed") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones en ese estado.");
	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estes dentro de un vehiculo.");
	if (GetPVarInt(playerid, "IsFrozen") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones porque estas congelado.");
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
	return 1;
}

cmd:asiento(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /asiento (1-18)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"Attractors","Stepsit_in",4.0,0,0,0,1,0);// Not looping
		case 2: ApplyAnimEx(playerid, 0,"CRIB","PED_Console_Loop",4.0,1,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"INT_HOUSE","LOU_In",4.0,0,0,0,1,0); // Not looping
		case 4: ApplyAnimEx(playerid, 0,"MISC","SEAT_LR",4.0,1,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"MISC","Seat_talk_01",4.0,1,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"MISC","Seat_talk_02",4.0,1,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0,"ped","SEAT_down",4.0,0,0,0,1,0); // Not looping
		case 8: ApplyAnimEx(playerid, 0,"BEACH","bather",4.0,1,0,0,0,0);
		case 9: ApplyAnimEx(playerid, 0,"BEACH","Lay_Bac_Loop",4.0,1,0,0,0,0);
		case 10: ApplyAnimEx(playerid, 0,"BEACH","ParkSit_W_loop",4.0,1,0,0,0,0);
		case 11: ApplyAnimEx(playerid, 0,"BEACH","SitnWait_loop_W",4.0,1,0,0,0,0);
		case 12: ApplyAnimEx(playerid, 0,"BEACH","SitnWait_loop_W",4.0,1,0,0,0,0);
		case 13: ApplyAnimEx(playerid, 0,"BEACH", "ParkSit_M_loop", 4.0,1,0,0,0,0);
		case 14: ApplyAnimEx(playerid, 0,"SUNBATHE","batherdown",4.0,0,0,0,1,0);
		case 15: ApplyAnimEx(playerid, 0,"SUNBATHE","batherup",4.0,1,1,1,0,0);
		case 16: ApplyAnimEx(playerid, 0,"SUNBATHE","ParkSit_W_idleA",4.0,0,0,0,1,0);
		case 17: ApplyAnimEx(playerid, 0,"SUNBATHE","ParkSit_W_idleB",4.0,0,0,0,1,0);
		case 18: ApplyAnimEx(playerid, 0,"SUNBATHE","ParkSit_W_idleC",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /asiento (1-18)");
	}
	return 1;
}
alias:asiento("sentarse");

cmd:bailar(playerid, params[])
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estas herido.");
 	if (GetPVarInt(playerid, "PlayerCuffed") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones en ese estado.");
	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estes dentro de un vehiculo.");
	if (GetPVarInt(playerid, "IsFrozen") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones porque estas congelado.");
	new dancestyle;
	if (sscanf(params, "d", dancestyle)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /bailar (1-4)");
	switch (dancestyle)
	{
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		case 3: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		case 4: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /bailar (1-4)");
	}
	return 1;
}

cmd:rap(playerid, params[])
{
	new rapstyle;
	if (sscanf(params, "d", rapstyle)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /rap (1-3)");
	switch (rapstyle)
	{
		case 1: ApplyAnimEx(playerid, 0,"RAPPING","RAP_A_Loop",4.0,1,1,1,1,0);
		case 2: ApplyAnimEx(playerid, 0,"RAPPING","RAP_B_Loop",4.0,1,1,1,1,0);
		case 3: ApplyAnimEx(playerid, 0,"RAPPING","RAP_C_Loop",4.0,1,1,1,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /rap (1-3)");
	}
	return 1;
}

cmd:cruzar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /cruzar (1-5)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
		case 2: ApplyAnimEx(playerid, 0, "DEALER", "DEALER_IDLE", 4.0, 0, 1, 1, 1, -1);
		case 3: ApplyAnimEx(playerid, 0, "DEALER", "DEALER_IDLE_01", 4.0, 0, 1, 1, 1, -1);
		case 4: ApplyAnimEx(playerid, 0,"GRAVEYARD","mrnM_loop",4.0,1,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"GRAVEYARD","prst_loopa",4.0,1,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /cruzar (1-5)");
	}
	return 1;
}

cmd:ped(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /ped (1-26)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"PED","JOG_femaleA",4.0,1,1,1,1,1);
		case 2: ApplyAnimEx(playerid, 0,"PED","JOG_maleA",4.0,1,1,1,1,1);
		case 3: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkfatold",4.0,1,1,1,1,1);
		case 4: ApplyAnimEx(playerid, 0,"PED","run_fat",4.0,1,1,1,1,1);
		case 5: ApplyAnimEx(playerid, 0,"PED","run_fatold",4.0,1,1,1,1,1);
		case 6: ApplyAnimEx(playerid, 0,"PED","run_old",4.0,1,1,1,1,1);
		case 7: ApplyAnimEx(playerid, 0,"PED","Run_Wuzi",4.0,1,1,1,1,1);
		case 8: ApplyAnimEx(playerid, 0,"PED","swat_run",4.0,1,1,1,1,1);
		case 9: ApplyAnimEx(playerid, 0,"PED","WALK_fat",4.0,1,1,1,1,1);
		case 10: ApplyAnimEx(playerid, 0,"PED","WALK_fatold",4.0,1,1,1,1,1);
		case 11: ApplyAnimEx(playerid, 0,"PED","WALK_gang1",4.0,1,1,1,1,1);
		case 12: ApplyAnimEx(playerid, 0,"PED","WALK_gang2",4.0,1,1,1,1,1);
		case 13: ApplyAnimEx(playerid, 0,"PED","WALK_old",4.0,1,1,1,1,1);
		case 14: ApplyAnimEx(playerid, 0,"PED","WALK_shuffle",4.0,1,1,1,1,1);
		case 15: ApplyAnimEx(playerid, 0,"PED","woman_run",4.0,1,1,1,1,1);
		case 16: ApplyAnimEx(playerid, 0,"PED","WOMAN_runbusy",4.0,1,1,1,1,1);
		case 17: ApplyAnimEx(playerid, 0,"PED","WOMAN_runfatold",4.0,1,1,1,1,1);
		case 18: ApplyAnimEx(playerid, 0,"PED","woman_runpanic",4.0,1,1,1,1,1);
		case 19: ApplyAnimEx(playerid, 0,"PED","WOMAN_runsexy",4.0,1,1,1,1,1);
		case 20: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkbusy",4.0,1,1,1,1,1);
		case 21: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkfatold",4.0,1,1,1,1,1);
		case 22: ApplyAnimEx(playerid, 0,"PED","WOMAN_walknorm",4.0,1,1,1,1,1);
		case 23: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkold",4.0,1,1,1,1,1);
		case 24: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkpro",4.0,1,1,1,1,1);
		case 25: ApplyAnimEx(playerid, 0,"PED","WOMAN_walksexy",4.0,1,1,1,1,1);
		case 26: ApplyAnimEx(playerid, 0,"PED","WOMAN_walkshop",4.0,1,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /ped (1-26)");
	}
	return 1;
}

cmd:jiggy(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /jiggy (1-15)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0, "DANCING", "bd_clap",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0, "DANCING", "bd_clap1",4.0,1,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0, "DANCING", "dance_loop",4.0,1,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0, "DANCING", "DAN_Down_A",4.0,1,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0, "DANCING", "DAN_Left_A",4.0,1,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0, "DANCING", "DAN_Loop_A",4.0,1,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0, "DANCING", "DAN_Right_A",4.0,1,0,0,0,0);
		case 8: ApplyAnimEx(playerid, 0, "DANCING", "DAN_Up_A",4.0,1,0,0,0,0);
		case 9: ApplyAnimEx(playerid, 0, "DANCING", "dnce_M_a",4.0,1,0,0,0,0);
		case 10: ApplyAnimEx(playerid, 0, "DANCING", "dnce_M_b",4.0,1,0,0,0,0);
		case 11: ApplyAnimEx(playerid, 0, "DANCING", "dnce_M_c",4.0,1,0,0,0,0);
		case 12: ApplyAnimEx(playerid, 0, "DANCING", "dnce_M_d",4.0,1,0,0,0,0);
		case 13: ApplyAnimEx(playerid, 0, "DANCING", "dnce_M_e",4.0,1,0,0,0,0);
		case 14: ApplyAnimEx(playerid, 0, "HEIST9", "swt_wllshoot_in_L", 4.0, 0, 1, 1, 1, -1);
		case 15: ApplyAnimEx(playerid, 0, "HEIST9", "swt_wllshoot_in_R", 4.0, 0, 1, 1, 1, -1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /jiggy (1-15)");
	}
	return 1;
}
alias:jiggy("danzar");

cmd:queteden(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fuck (1-4)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","fucku",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"RIOT","RIOT_FUKU",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"MISC","Hiker_Pose",4.1,0,1,1,1,1);
		case 4: ApplyAnimEx(playerid, 0,"MISC","Hiker_Pose_L",4.1,0,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /fuck (1-4)");
	}
	return 1;
}
alias:queteden("fuck");

cmd:pandillero(playerid, params[])
{
	if (IsPlayerInAnyVehicle(playerid))
	{
		new animacion;
		if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: (1-9)");
		switch (animacion)
		{
			case 1: ApplyAnimEx(playerid, 1, "GHANDS", 		"gsign2", 			4.0, 0, 0, 1, 0, 0);
			case 2: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign2LH",			4.0, 0, 0, 1, 0, 0);
			case 3: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign3",			4.0, 0, 0, 1, 0, 0);
			case 4: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign3LH",			4.0, 0, 0, 1, 0, 0);
			case 5: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign4",			4.0, 0, 0, 1, 0, 0);
			case 6: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign4LH",			4.0, 0, 0, 1, 0, 0);
			case 7: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign5",			4.0, 0, 0, 1, 0, 0);
			case 8: ApplyAnimEx(playerid, 1, "GHANDS",		"gsign5LH",			4.0, 0, 0, 1, 0, 0);
			case 9: ApplyAnimEx(playerid, 1, "LOWRIDER",		"prtial_gngtlkG",	4.0, 0, 0, 1, 0, 0);
			default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: (1-9)");
		}
	}
	else
	{
		new animacion;
		if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: (1-16)");
		switch (animacion)
		{
			case 1: ApplyAnimEx(playerid, 0, "RAPPING",		"RAP_A_Loop", 		4.0, 1, 0, 1, 0, 0); //nosepuede en coche
			case 2: ApplyAnimEx(playerid, 0, "RAPPING",		"RAP_C_Loop", 		4.0, 1, 0, 1, 0, 0); //nosepuede en coche
			case 3: ApplyAnimEx(playerid, 0, "GHANDS", 		"gsign2", 			4.0, 1, 1, 1, 1, 1);
			case 4: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign2LH",			4.0, 1, 1, 1, 1, 1);
			case 5: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign3",			4.0, 1, 1, 1, 1, 1);
			case 6: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign3LH",			4.0, 1, 1, 1, 1, 1);
			case 7: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign4",			4.0, 1, 1, 1, 1, 1);
			case 8: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign4LH",			4.0, 1, 1, 1, 1, 1);
			case 9: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign5",			4.0, 1, 1, 1, 1, 1);
			case 10: ApplyAnimEx(playerid, 0, "GHANDS",		"gsign5LH",			4.0, 1, 1, 1, 1, 1);
			case 11: ApplyAnimEx(playerid, 0, "benchpress",	"gym_bp_celebrate", 4.0, 0, 0, 1, 0, 0);//nosepuede en coche
			case 12: ApplyAnimEx(playerid, 0, "LOWRIDER",		"prtial_gngtlkG",	4.0, 0, 0, 1, 0, 0);
			case 13: ApplyAnimEx(playerid, 0, "RIOT",			"RIOT_ANGRY",		4.0, 0, 0, 1, 0, 0);//nosepuede en coche
			case 14: ApplyAnimEx(playerid, 0, "RIOT",			"RIOT_challenge",	4.0, 0, 0, 1, 0, 0);//nosepuede en coche
			case 15: ApplyAnimEx(playerid, 0, "RAPPING",		"RAP_B_Loop",		4.0, 1, 0, 1, 0, 0);//nosepuede en coche
			case 16: ApplyAnimEx(playerid, 0, "SCRATCHING",	"scdrulp",			4.0, 1, 0, 1, 0, 0);//nosepuede en coche
			default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: (1-16)");
		}
	}
	return 1;
}
alias:pandillero("gesto");

cmd:fumando(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fumando (1-7)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 	0, "SMOKING",	"M_smklean_loop",	4.0, 1, 0, 1, 0, 0);
		case 2: ApplyAnimEx(playerid, 	0, "SMOKING",	"M_smkstnd_loop",	4.0, 1, 0, 1, 0, 0);
		case 3: ApplyAnimEx(playerid, 	0, "SMOKING",	"M_smk_out",		4.0, 0, 1, 1, 0, 0);
		case 4: ApplyAnimEx(playerid, 	0, "SMOKING",	"M_smk_in",			4.0, 0, 1, 1, 0, 0);
		case 5: ApplyAnimEx(playerid, 	0, "GANGS", 	"smkcig_prtl",		4.0, 0, 1, 1, 0, 0);
		case 6: ApplyAnimEx(playerid, 	0, "SMOKING",	"M_smk_drag",		4.0, 0, 1, 1, 0, 0);
		case 7: ApplyAnimEx(playerid,	0, "SMOKING",	"F_smklean_loop",	4.0, 1, 0, 1, 0, 0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /fumando (1-7)");
	}
	return 1;
}

cmd:sexo(playerid, params[])
{
	new sexstyle;
	if (sscanf(params, "d", sexstyle)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sexo (1-8)");
	switch (sexstyle)
	{
		case 1: ApplyAnimEx(playerid, 0,"SNM","SPANKING_IDLEW",4.1,0,1,1,1,0);
		case 2: ApplyAnimEx(playerid, 0,"SNM","SPANKING_IDLEP",4.1,0,1,1,1,0);
		case 3: ApplyAnimEx(playerid, 0,"SNM","SPANKINGW",4.1,0,1,1,1,0);
		case 4: ApplyAnimEx(playerid, 0,"SNM","SPANKINGP",4.1,0,1,1,1,0);
		case 5: ApplyAnimEx(playerid, 0,"SNM","SPANKEDW",4.1,0,1,1,1,0);
		case 6: ApplyAnimEx(playerid, 0,"SNM","SPANKEDP",4.1,0,1,1,1,0);
		case 7: ApplyAnimEx(playerid, 0,"SNM","SPANKING_ENDW",4.1,0,1,1,1,0);
		case 8: ApplyAnimEx(playerid, 0,"SNM","SPANKING_ENDP",4.1,0,1,1,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /sexo (1-8)");
	}
	return 1;
}

cmd:orinar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /orinar (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"PAULNMAC","Piss_loop",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"PAULNMAC","Piss_out",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /orinar (1-2)");
	}
	return 1;
}

cmd:chora(playerid) { ApplyAnimEx(playerid, 0,"COP_AMBIENT", "Coplook_watch",4.0,0,0,0,0,0); return 1; }
cmd:relax(playerid) { ApplyAnimEx(playerid, 0, "CRACK", "crckidle1",4.0,0,1,1,1,-1); return 1; }
cmd:fascista(playerid) { ApplyAnimEx(playerid, 0, "ON_LOOKERS", "Pointup_loop",4.0,1,0,0,1,0); return 1; }
cmd:lavar(playerid) { ApplyAnimEx(playerid, 0, "INT_HOUSE", "wash_up",4.0,1,0,0,0,0); return 1; }
cmd:llorar(playerid) { ApplyAnimEx(playerid, 0, "GRAVEYARD","mrnF_loop",4.0,1,0,0,0,0); return 1; }

cmd:mirarse(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /mirarse (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"CLOTHES","CLO_Pose_Shoes",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"CLOTHES","CLO_Pose_Torso",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"CLOTHES","CLO_Pose_Watch",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /mirarse (1-3)");
	}
	return 1;
}

cmd:tocar(playerid) { ApplyAnimEx(playerid, 0, "CASINO", "Slot_Plyr",4.0,0,1,1,1,-1); return 1; }

cmd:saludo(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /saludo (1-12)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","endchat_03",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"KISSING","gfwave2",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"ped","endchat_01",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"WUZI","Wuzi_Greet_Wuzi",4.0,0,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"GANGS","hndshkaa",4.0,0,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"GANGS","hndshkba",4.0,0,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0,"GANGS","hndshkca",4.0,0,0,0,0,0);
		case 8: ApplyAnimEx(playerid, 0,"GANGS","hndshkcb",4.0,0,0,0,0,0);
		case 9: ApplyAnimEx(playerid, 0,"GANGS","hndshkda",4.0,0,0,0,0,0);
		case 10: ApplyAnimEx(playerid, 0,"GANGS","hndshkea",4.0,0,0,0,0,0);
		case 11: ApplyAnimEx(playerid, 0,"GANGS","hndshkfa",4.0,0,0,0,0,0);
		case 12: ApplyAnimEx(playerid, 0,"GANGS","hndshkfa_swt",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /saludo (1-12)");
	}
	return 1;
}

cmd:cielo(playerid) { ApplyAnimEx(playerid, 0,"WUZI","Wuzi_stand_loop", 4.0, 1, 0, 0, 0, 0); return 1; }
cmd:enganche(playerid) { ApplyAnimEx(playerid, 0,"MISC","Hiker_Pose", 4.0, 1, 0, 0, 0, 0); return 1; }
cmd:cpr(playerid) { ApplyAnimEx(playerid, 0,"MEDIC","CPR",4.0,0,0,0,0,0); return 1; }

cmd:bebiendo(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bebiendo (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"VENDING","VEND_Drink2_P",4.0,0,1,1,1,0);
		case 2: ApplyAnimEx(playerid, 0,"VENDING","VEND_Drink_P",4.0,0,1,1,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /bebiendo (1-2)");
	}
	return 1;
}

cmd:palmada(playerid) { ApplyAnimEx(playerid, 0,"SWEET", "sweet_ass_slap",4.0,0,0,0,0,0); return 1; }
cmd:borracho(playerid) { ApplyAnimEx(playerid, 0,"PED","WALK_DRUNK",4.1,1,1,1,1,1); return 1; }

cmd:besar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /besar (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BD_FIRE","Grlfrd_Kiss_03",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"BD_FIRE","Playa_Kiss_03",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"KISSING","Playa_Kiss_01",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /besar (1-3)");
	}
	return 1;
}

cmd:carga(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /carga (1-7)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BOX","catch_box",4.0,0,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"CARRY","crry_prtial",4.0,0,0,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"CARRY","liftup",4.0,0,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"CARRY","liftup05",4.0,0,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"CARRY","liftup105",4.0,0,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"CARRY","putdwn",4.0,0,0,0,1,0);
		case 7: ApplyAnimEx(playerid, 0,"CARRY","putdwn05",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /carga (1-7)");
	}
	return 1;
}

cmd:basket(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /basket (1-7)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_idle",4.0,0,0,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_def_stepL",4.0,0,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_def_stepR",4.0,0,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_def_jump_shot",4.0,0,0,0,1,0);
		case 7: ApplyAnimEx(playerid, 0,"BSKTBALL","BBALL_def_loop",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /basket (1-7)");
	}
	return 1;
}

cmd:lowrider(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /lowrider (1-6)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"LOWRIDER","lrgirl_l1_loop",4.0,0,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"LOWRIDER","lrgirl_l2_bnce",4.0,1,0,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"LOWRIDER","lrgirl_l2_loop",4.0,1,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"LOWRIDER","lrgirl_l4_bnce",4.0,1,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"LOWRIDER","Sit_relaxed",4.0,0,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"LOWRIDER","Tap_hand",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /lowrider (1-6)");
	}
	return 1;
}

cmd:bartender(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bartender (1-9)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BAR","BARMAN_idle",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"BAR","Barserve_bottle",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"BAR","Barserve_give",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"BAR","Barserve_glass",4.0,0,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"BAR","Barserve_in",4.0,0,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"BAR","Barserve_loop",4.0,1,0,0,1,0);
		case 7: ApplyAnimEx(playerid, 0,"BAR","Barserve_order",4.0,0,0,0,0,0);
		case 8: ApplyAnimEx(playerid, 0,"BAR","dnk_stndF_loop",4.0,0,0,0,1,0);
		case 9: ApplyAnimEx(playerid, 0,"BAR","dnk_stndM_loop",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /bartender (1-9)");
	}
	return 1;
}

cmd:protestar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /protestar (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BASEBALL","Bat_M",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"BASEBALL","BAT_PART",4.0,1,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /protestar [1-2]");
	}
	return 1;
}

cmd:auxilio(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /auxilio (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"BD_FIRE","BD_Panic_01",4.0,0,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"BD_FIRE","BD_Panic_03",4.0,1,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /auxilio (1-2)");
	}
	return 1;
}

cmd:gym(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /gym (1-10)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_celebrate",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_down",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_getoff",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_geton",4.0,0,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_up_A",4.0,1,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_up_B",4.0,1,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0,"benchpress","gym_bp_up_smooth",4.0,1,0,0,0,0);
		case 8: ApplyAnimEx(playerid, 0,"Freeweights","gym_barbell",4.0,1,0,0,0,0);
		case 9: ApplyAnimEx(playerid, 0,"Freeweights","gym_free_A",4.0,1,0,0,0,0);
		case 10: ApplyAnimEx(playerid, 0,"Freeweights","gym_free_B",4.0,1,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /gym (1-10)");
	}
	return 1;
}

cmd:animauto(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estas dentro de un vehiculo para usar esta animación.");
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /animauto (1-19)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 1,"KISSING", 		"GF_CarArgue_01", 	4.0, 0, 0, 1, 0, 0);
		case 2: ApplyAnimEx(playerid, 1,"KISSING", 		"GF_CarArgue_02", 	4.0, 0, 0, 1, 0, 0);
		case 3: ApplyAnimEx(playerid, 1,"KISSING", 		"GF_CarSpot", 		4.0, 0, 0, 1, 0, 0);
		case 4: ApplyAnimEx(playerid, 1,"LOWRIDER", 	"lrgirl_hair",		4.0, 0, 0, 1, 1, 0);
		case 5: ApplyAnimEx(playerid, 1,"LOWRIDER", 	"lrgirl_idleloop",	4.0, 1, 0, 1, 0, 0);
		case 6: ApplyAnimEx(playerid, 1,"LOWRIDER", 	"Sit_relaxed",		4.0, 0, 0, 1, 1, 0);
		case 7: ApplyAnimEx(playerid, 1,"LOWRIDER", 	"Tap_hand",			4.0, 0, 0, 0, 1, 0);
		case 8: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"carfone_in", 		4.0, 0, 0, 0, 1, 0);
		case 9: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"carfone_loopA", 	4.0, 0, 0, 0, 1, 0);
		case 10: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"carfone_loopB", 	4.0, 0, 0, 0, 1, 0);
		case 11: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"CAR_Sc1_BL", 		4.0, 0, 0, 0, 1, 0);
		case 12: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"CAR_Sc3_FL", 		4.0, 0, 0, 0, 1, 0);
		case 13: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"car_talkm_in", 	4.0, 0, 0, 0, 1, 0);
		case 14: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"car_talkm_loop", 	4.0, 0, 0, 0, 1, 0);
		case 15: ApplyAnimEx(playerid, 1,"CAR_CHAT", 	"car_talkm_out", 	4.0, 0, 0, 0, 1, 0);
		case 16: ApplyAnimEx(playerid, 1,"ped", 		"CAR_sit_weak", 	4.0, 0, 0, 0, 1, 0);
		case 17: ApplyAnimEx(playerid, 1,"ped", 		"CAR_LB_pro", 		4.0, 0, 0, 0, 1, 0);
		case 18: ApplyAnimEx(playerid, 1,"ped", 		"CAR_sit", 			4.0, 0, 0, 0, 1, 0);
		case 19: ApplyAnimEx(playerid, 1,"ped", 		"CAR_dead_RHS", 	4.0, 0, 0, 0, 1, 0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /animauto (1-19)");
	}
	return 1;
}
alias:animauto("animcoche");

cmd:ganar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ganar (1-5)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"CASINO","manwinb",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"CASINO","manwind",4.0,1,0,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"CASINO","Roulette_win",4.0,0,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"CASINO","Slot_win_out",4.0,1,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"OTB","wtchrace_win",4.1,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /ganar (1-5)");
	}
	return 1;
}

cmd:perder(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /perder (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"CASINO","Slot_lose_out",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"CASINO","cards_lose",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /perder (1-2)");
	}
	return 1;
}

cmd:arobar(playerid) { ApplyAnimEx(playerid, 0,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1, 0); return 1; }
cmd:reir(playerid) { ApplyAnimEx(playerid, 0,"RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0); return 1; }
cmd:robman(playerid) { ApplyAnimEx(playerid, 0, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0); return 1; }

cmd:cubrirse(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /cubrirse (1-2)");
	switch (anim)
	{
		case 1:ApplyAnimEx(playerid, 0,"ped","cower",4.0,0,0,0,0,0);
		case 2:ApplyAnimEx(playerid, 0,"ped","DUCK_cower",4.0,1,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_WHITE,"COLOR_GREEN: /cubrirse (1-2)");
	}
	return 1;
}

cmd:vomitar(playerid) { ApplyAnimEx(playerid, 0,  "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); return 1; }

cmd:comiendo(playerid, params[])
{
	new gesto;
	if (sscanf(params, "d", gesto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /comiendo (1-9)");
	switch (gesto)
	{
		case 1: ApplyAnimEx(playerid, 0,"FOOD","EAT_Burger",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"FOOD","EAT_Chicken",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"FOOD","EAT_Pizza",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"FOOD","FF_Sit_Eat1",4.0,1,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"FOOD","FF_Sit_Eat2",4.0,1,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"FOOD","FF_Sit_Eat3",4.0,1,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0,"FOOD","SHP_Thank",4.0,0,0,0,0,0);
		case 8: ApplyAnimEx(playerid, 0,"FOOD","SHP_Tray_Lift_Loop",4.0,1,0,0,0,0);
		case 9: ApplyAnimEx(playerid, 0,"FOOD","SHP_Tray_Pose",4.0,1,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /comiendo (1-9)");
	}
	return 1;
}

cmd:taichi(playerid) { ApplyAnimEx(playerid, 0,"PARK","Tai_Chi_Loop", 4.0, 1, 0, 0, 0, 0); return 1; }

cmd:dormir(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dormir (1-6)");
	switch (anim)
	{
		case 1: ApplyAnimation(playerid, "INT_HOUSE", "BED_In_L",4.1,0,0,0,1,1);
		case 2: ApplyAnimation(playerid, "INT_HOUSE", "BED_In_R",4.1,0,0,0,1,1);
		case 3: ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_L",4.1,1,0,0,1,1);
		case 4: ApplyAnimation(playerid, "INT_HOUSE", "BED_Loop_R",4.1,1,0,0,1,1);
		case 5: ApplyAnimation(playerid, "INT_HOUSE", "BED_Out_L",4.1,0,1,1,0,0);
		case 6: ApplyAnimation(playerid, "INT_HOUSE", "BED_Out_R",4.1,0,1,1,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /dormir (1-6)");
	}
	return 1;
}

cmd:casino(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /casino (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"CASINO","dealone",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"CASINO","Roulette_bet",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"CASINO","Slot_bet_02",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /casino (1-3)");
	}
	return 1;
}

cmd:rearma(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /rearma (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"COLT45","colt45_reload",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"COLT45","sawnoff_reload",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /rearma (1-2)");
	}
	return 1;
}

cmd:dubstep(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dubstep (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","DAM_LegL_frmFT",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"ped","DAM_LegR_frmRT",4.0,1,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /dubstep [1-2]");
	}
	return 1;
}

cmd:negar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /negar (1-6)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","endchat_02",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"KISSING","GF_StreetArgue_02",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"GANGS","Invite_No",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"ped","handscower",4.0,0,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"MISC","plyr_shkhead",4.0,0,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"FOOD","EAT_Vomit_SK",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /negar [1-6]");
	}
	return 1;
}

cmd:masticar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /masticar (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","factalk",4.0,1,1,1,1,1);
		case 2: ApplyAnimEx(playerid, 0,"ped","facgum",4.0,1,1,1,1,1);
		case 3: ApplyAnimEx(playerid, 0,"ped","gum_eat",4.0,1,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /masticar (1-3)");
	}
	return 1;
}

cmd:esquivar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /esquivar (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","EV_dive",4.0,0,1,1,1,1);
		case 2: ApplyAnimEx(playerid, 0,"DODGE","Crush_Jump",4.0,0,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /esquivar (1-2)");
	}
	return 1;
}

cmd:zapatear(playerid) { ApplyAnimEx(playerid, 0,"ped","FightA_G",4.0,0,0,0,0,0); return 1; }
cmd:convulsionar(playerid) { ApplyAnimEx(playerid, 0,"ped","FLOOR_hit",4.0,1,0,0,1,0); return 1; }
cmd:hablartel(playerid) { ApplyAnimEx(playerid, 0,"ped", "phone_talk", 4.0, 0, 0, 0, 1, 0); return 1; }

cmd:mirarlados(playerid, params[])
{
	new gesto;
	if (sscanf(params, "d", gesto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mirarlados (1-2)");
	switch (gesto)
	{
		case 1: ApplyAnimEx(playerid, 0,"ped","roadcross_female",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"ped","roadcross_gang",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mirarlados (1-2)");
	}
	return 1;
}

cmd:herido(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /herido (1-10)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0, "SWAT", "gnstwall_injurd", 4.0, 0, 0, 0, 1, 0);
		case 2: ApplyAnimEx(playerid, 0, "CRACK", "crckdeth1", 4.0, 0, 0, 0, 1, 0);
		case 3: ApplyAnimEx(playerid, 0, "CRACK", "crckdeth2", 4.0, 0, 0, 0, 1, 0);
		case 4: ApplyAnimEx(playerid, 0, "CRACK", "crckdeth3", 4.0, 0, 0, 0, 1, 0);
		case 5: ApplyAnimEx(playerid, 0, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0);
		case 6: ApplyAnimEx(playerid, 0, "CRACK", "crckidle1", 4.0, 0, 0, 0, 1, 0);
		case 7: ApplyAnimEx(playerid, 0, "CRACK", "crckidle2", 4.0, 0, 0, 0, 1, 0);
		case 8: ApplyAnimEx(playerid, 0, "CRACK", "crckidle3", 4.0, 0, 0, 0, 1, 0);
		case 9: ApplyAnimEx(playerid, 0, "CRACK", "crckidle4", 4.0, 0, 0, 0, 1, 0);
		case 10: ApplyAnimEx(playerid, 0, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /herido (1-10)");
	}
	return 1;
}

cmd:consola(playerid, params[])
{
	new gesto;
	if (sscanf(params, "d", gesto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /consola (1-3)");
	switch (gesto)
	{
		case 1: ApplyAnimEx(playerid, 0,"CRIB","PED_Console_Loop",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"CRIB","PED_Console_Loose",4.0,1,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"CRIB","PED_Console_Win",4.0,1,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /consola (1-3)");
	}
	return 1;
}

cmd:dealer(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dealer (1-7)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"DEALER","DEALER_DEAL",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"DEALER","DEALER_IDLE",4.0,1,1,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"DEALER","DEALER_IDLE_01",4.0,1,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"DEALER","DEALER_IDLE_02",4.0,1,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"DEALER","DEALER_IDLE_03",4.0,1,0,0,0,0);
		case 6: ApplyAnimEx(playerid, 0,"DEALER","DRUGS_BUY",4.0,1,0,0,0,0);
		case 7: ApplyAnimEx(playerid, 0,"DEALER","shop_pay",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /dealer (1-7)");
	}
	return 1;
}

cmd:azotar(playerid) { ApplyAnimEx(playerid, 0, "DILDO", "DILDO_G",2.0,0,0,0,0,0); return 1; }
cmd:cansado(playerid) { ApplyAnimEx(playerid, 0, "FAT", "IDLE_tired",4.0,1,1,0,0,0); return 1; }
cmd:sacoboxeo(playerid) { ApplyAnimEx(playerid, 0,"GYMNASIUM","GYMshadowbox",4.0,1,1,0,0,0); return 1; }
cmd:acomodar(playerid) { ApplyAnimEx(playerid, 0,"ROB_BANK", "CAT_Safe_Rob",4.0,1,0,0,0,0); return 1; }
cmd:deacuerdo(playerid) { ApplyAnimEx(playerid, 0,"GANGS", "Invite_Yes",4.0,0,0,0,0,0); return 1; }

cmd:empujar(playerid, params[])
{
	new gesto;
	if (sscanf(params, "d", gesto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /empujar (1-3)");
	switch (gesto)
	{
		case 1: ApplyAnimEx(playerid, 0,"GANGS","shake_cara",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"GANGS","shake_carK",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"GANGS","shake_carSH",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /empujar (1-3)");
	}
	return 1;
}

cmd:pintar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /pintar (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"GRAFFITI","graffiti_Chkout",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"GRAFFITI","spraycan_fire",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"SPRAYCAN","spraycan_full",4.0,0,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /pintar (1-3)");
	}
	return 1;
}

cmd:peluquero(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /peluquero (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"HAIRCUTS","BRB_Cut",4.0,1,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"HAIRCUTS","BRB_Sit_Loop",4.0,1,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /peluquero (1-2)");
	}
	return 1;
}

cmd:bate(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bate (1-2)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 0,"CRACK", "Bbalbat_Idle_01", 4.1, 0, 1, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 0,"CRACK", "Bbalbat_Idle_02", 4.1, 0, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bate (1-2)");
	}
	return 1;
}

cmd:animtienda(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /animtienda (1-8)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_cashier",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_in",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_lookA",4.0,1,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_lookB",4.0,1,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_loop",4.0,1,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_out",4.0,1,0,0,1,0);
		case 7: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_pay",4.0,1,0,0,1,0);
		case 8: ApplyAnimEx(playerid, 0,"INT_SHOP","shop_shelf",4.0,1,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /animtienda (1-8)");
	}
	return 1;
}

cmd:mirarcielo(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mirarcielo (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ON_LOOKERS","lkup_loop",4.0,0,1,1,1,1);
		case 2: ApplyAnimEx(playerid, 0,"ON_LOOKERS","lkup_point",4.0,0,1,1,1,1);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /mirarcielo (1-2)");
	}
	return 1;
}

cmd:asombrado(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /asombrado (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"ON_LOOKERS","panic_cower",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"ON_LOOKERS","panic_hide",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"ON_LOOKERS","panic_loop",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /mirarcielo (1-3)");
	}
	return 1;
}

cmd:gritar(playerid, params[])
{
	new gesto;
	if (sscanf(params, "d", gesto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /gritar (1-3)");
	switch (gesto)
	{
		case 1: ApplyAnimEx(playerid, 0,"ON_LOOKERS","shout_01",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"ON_LOOKERS","shout_02",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"ON_LOOKERS","shout_loop",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /gritar (1-3)");
	}
	return 1;
}

cmd:pajearse(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /pajearse (1-2)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"PAULNMAC","wank_loop",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"PAULNMAC","wank_out",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /pajearse (1-2)");
	}
	return 1;
}

cmd:aburrido(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /aburrido (1-5)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"PLAYIDLES","shift",4.0,0,0,0,0,0);
		case 2: ApplyAnimEx(playerid, 0,"PLAYIDLES","shldr",4.0,0,0,0,0,0);
		case 3: ApplyAnimEx(playerid, 0,"PLAYIDLES","stretch",4.0,0,0,0,0,0);
		case 4: ApplyAnimEx(playerid, 0,"PLAYIDLES","strleg",4.0,0,0,0,0,0);
		case 5: ApplyAnimEx(playerid, 0,"PLAYIDLES","time",4.0,0,0,0,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /aburrido (1-5)");
	}
	return 1;
}

cmd:bailarsexi(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bailarsexi (1-3)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"STRIP","strip_G",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"STRIP","STR_A2B",4.0,1,0,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"STRIP","STR_Loop_A",4.0,1,0,1,0,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /bailarsexi (1-3)");
	}
	return 1;
}

cmd:abanicarse(playerid) { ApplyAnimEx(playerid, 0,"WUZI", "wuzi_follow",4.0,1,0,0,1,0); return 1; }

cmd:dj(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dj (1-12)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0,"SCRATCHING","scdldlp",4.0,1,0,0,1,0);
		case 2: ApplyAnimEx(playerid, 0,"SCRATCHING","scdlulp",4.0,1,1,0,1,0);
		case 3: ApplyAnimEx(playerid, 0,"SCRATCHING","scdrdlp",4.0,1,0,0,1,0);
		case 4: ApplyAnimEx(playerid, 0,"SCRATCHING","scdrulp",4.0,1,0,0,1,0);
		case 5: ApplyAnimEx(playerid, 0,"SCRATCHING","sclng_l",4.0,1,0,0,1,0);
		case 6: ApplyAnimEx(playerid, 0,"SCRATCHING","sclng_r",4.0,1,0,0,1,0);
		case 7: ApplyAnimEx(playerid, 0,"SCRATCHING","scmid_l",4.0,1,0,0,1,0);
		case 8: ApplyAnimEx(playerid, 0,"SCRATCHING","scmid_r",4.0,1,0,0,1,0);
		case 9: ApplyAnimEx(playerid, 0,"SCRATCHING","scshrtl",4.0,1,0,0,1,0);
		case 10: ApplyAnimEx(playerid, 0,"SCRATCHING","scshrtr",4.0,1,0,0,1,0);
		case 11: ApplyAnimEx(playerid, 0,"SCRATCHING","sc_ltor",4.0,0,0,0,1,0);
		case 12: ApplyAnimEx(playerid, 0,"SCRATCHING","sc_rtol",4.0,0,0,0,1,0);
		default: SendPlayerChatMessage(playerid,COLOR_GREEN,"Utiliza: /dj (1-12)");
	}
	return 1;
}

cmd:caminando(playerid, params[])
{
	new animacion;
	if (sscanf(params, "d", animacion)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /caminando (1-12)");
	switch (animacion)
	{
		case 1: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_civi", 		4.1, 1, 1, 1, 1, 1);
		case 2: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_gang1", 		4.1, 1, 1, 1, 1, 1);
		case 3: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_gang2", 		4.1, 1, 1, 1, 1, 1);
		case 4: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_old", 		4.1, 1, 1, 1, 1, 1);
		case 5: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_fatold",		4.1, 1, 1, 1, 1, 1);
		case 6: ApplyAnimEx(playerid, 	0, "PED", 	"WALK_fat",			4.1, 1, 1, 1, 1, 1);
		case 7: ApplyAnimEx(playerid, 	0, "PED", 	"WOMAN_walknorm",	4.1, 1, 1, 1, 1, 1);
		case 8: ApplyAnimEx(playerid, 	0, "PED", 	"WOMAN_walkbusy",	4.1, 1, 1, 1, 1, 1);
		case 9: ApplyAnimEx(playerid, 	0, "PED", 	"WOMAN_walkpro",	4.1, 1, 1, 1, 1, 1);
		case 10: ApplyAnimEx(playerid, 0, "PED", 	"WOMAN_walksexy",	4.1, 1, 1, 1, 1, 1);
		case 11: ApplyAnimEx(playerid, 0, "PED", 	"WALK_drunk",		4.1, 1, 1, 1, 1, 1);
		case 12: ApplyAnimEx(playerid, 0, "PED", 	"Walk_Wuzi",		4.1, 1, 1, 1, 1, 1);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /caminando (1-12)");
	}
	return 1;
}

cmd:camara(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /camara (0-13)");
	if (anim < 0 || anim > 13) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /camara (0-13)");
	switch (anim)
	{
		case 0: ApplyAnimEx(playerid, 0, "CAMERA", "camcrch_cmon", 4.0, 0, 0, 0, 1, 0);
		case 1: ApplyAnimEx(playerid, 0, "CAMERA", "camcrch_idleloop", 4.0, 0, 0, 0, 1, 0);
		case 2: ApplyAnimEx(playerid, 0, "CAMERA", "camcrch_stay", 4.0, 0, 0, 0, 1, 0);
		case 3: ApplyAnimEx(playerid, 0, "CAMERA", "camcrch_to_camstnd", 4.0, 0, 0, 0, 1, 0);
		case 4: ApplyAnimEx(playerid, 0, "CAMERA", "camstnd_cmon", 4.0, 0, 0, 0, 1, 0);
		case 5: ApplyAnimEx(playerid, 0, "CAMERA", "camstnd_idleloop", 4.0, 0, 0, 0, 1, 0);
		case 6: ApplyAnimEx(playerid, 0, "CAMERA", "camstnd_lkabt", 4.0, 0, 0, 0, 1, 0);
		case 7: ApplyAnimEx(playerid, 0, "CAMERA", "camstnd_to_camcrch", 4.0, 0, 0, 0, 1, 0);
		case 8: ApplyAnimEx(playerid, 0, "CAMERA", "piccrch_in", 4.0, 0, 0, 0, 1, 0);
		case 9: ApplyAnimEx(playerid, 0, "CAMERA", "piccrch_out", 4.0, 0, 0, 0, 1, 0);
		case 10: ApplyAnimEx(playerid, 0, "CAMERA", "piccrch_take", 4.0, 0, 0, 0, 1, 0);
		case 11: ApplyAnimEx(playerid, 0, "CAMERA", "picstnd_in", 4.0, 0, 0, 0, 1, 0);
		case 12: ApplyAnimEx(playerid, 0, "CAMERA", "picstnd_out", 4.0, 0, 0, 0, 1, 0);
		case 13: ApplyAnimEx(playerid, 0, "CAMERA", "picstnd_take", 4.0, 0, 0, 0, 1, 0);
	}
	return 1;
}

cmd:hablando(playerid)
{
	switch (InfoPersonaje[playerid][pEstiloManos])
	{
		case 1: ApplyAnimEx(playerid, 0, "PED", 	"IDLE_chat", 		4.1, 1, 0, 0, 1, 1);
		case 2: ApplyAnimEx(playerid, 0, "MISC", 	"IDLE_CHAT_02", 	4.1, 1, 0, 0, 1, 1);
		case 3: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkA", 	4.1, 1, 0, 0, 1, 1);
		case 4: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkB", 	4.1, 1, 0, 0, 1, 1);
		case 5: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkE", 	4.1, 1, 0, 0, 1, 1);
		case 6: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkF", 	4.1, 1, 0, 0, 1, 1);
		case 7: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkG", 	4.1, 1, 0, 0, 1, 1);
		case 8: ApplyAnimEx(playerid, 0, "GANGS", 	"prtial_gngtlkH", 	4.1, 1, 0, 0, 1, 1);
	}
	return 1;
}

cmd:sentadilla(playerid) { ApplyAnimEx(playerid,0, "SUNBATHE", "Lay_Bac_in", 4.0, 0, 0, 0, 1, 0); return 1; }

cmd:apuntar(playerid, params[])
{
	new anim;
	if (sscanf(params, "d", anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /apuntar (1-7)");
	switch (anim)
	{
		case 1: ApplyAnimEx(playerid, 0, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 1, 0);
		case 2: ApplyAnimEx(playerid, 0, "SHOP", "SHP_Gun_Aim", 4.0, 0, 0, 0, 1, 0);
		case 3: ApplyAnimEx(playerid, 0, "PYTHON", "python_crouchreload", 4.0, 0, 0, 0, 1, 0);
		case 4: ApplyAnimEx(playerid, 0, "PYTHON", "python_reload", 4.0, 0, 0, 0, 1, 0);
		case 5: ApplyAnimEx(playerid, 0, "SHOP", "SHP_Gun_Grab", 4.0, 0, 0, 0, 1, 0);
		case 6: ApplyAnimEx(playerid, 0, "SHOP", "SHP_Gun_Threat", 4.0, 0, 0, 0, 1, 0);
		case 7: ApplyAnimEx(playerid, 0, "ped", "gang_gunstand", 4.0, 0, 0, 0, 1, 0);
		default: SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /apuntar (1-7)");
	}
	return 1;
}

cmd:rifle(playerid) { ApplyAnimEx(playerid, 0, "BUDDY", "buddy_reload", 4.1, 0, 1, 1, 1, 1); return 1; }

