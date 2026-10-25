// Administrativos
cmd:verarmas(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new playerid2, dialog[1024], dialog2[256], count = 0;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /verarmas (PlayerID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	format(dialog2, sizeof dialog2, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) usó /verarmas %s(%d).", InfoCuenta[playerid][jNombre], playerid, NombreOriginal(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, dialog2);
	//indice
	Loop(x, 9, 0)
	{
		if (InfoPersonaje[playerid2][pBolsillo][x] != 0)
		{
			format(dialog2, sizeof dialog2, "{FFFFFF}%s\n", slot_objeto(InfoPersonaje[playerid2][pBolsillo][x], InfoPersonaje[playerid2][pBolsilloCant][x])), count++;
			strcat(dialog, dialog2);
		}
	}
	//barra espacio
	if (count != 0) strcat(dialog, "{b42d2d}--------------------\n");
	//mano derecha
	if (InfoPersonaje[playerid2][pManoDerecha] != 0)
	{
		format(dialog2, sizeof dialog2, "{FFFFFF}Mano derecha: %s\n", slot_objeto(InfoPersonaje[playerid2][pManoDerecha], InfoPersonaje[playerid2][pManoDerechaCant])), count++;
		strcat(dialog, dialog2);
	}
	//mano izquierda
	if (InfoPersonaje[playerid2][pManoIzquierda] != 0)
	{
		format(dialog2, sizeof dialog2, "{FFFFFF}Mano izquierda: %s\n", slot_objeto(InfoPersonaje[playerid2][pManoIzquierda], InfoPersonaje[playerid2][pManoIzquierdaCant])), count++;
		strcat(dialog, dialog2);
	}
	//espalda
	if (InfoPersonaje[playerid2][pEspalda] != 0)
	{
		format(dialog2, sizeof dialog2, "{F5DEB3}%s:{FFFFFF} %s\n", GetParteToy(playerid2, 7), slot_objeto(InfoPersonaje[playerid2][pEspalda], InfoPersonaje[playerid2][pEspaldaCant])), count++;
		strcat(dialog, dialog2);
	}
	//formato
	format(dialog2, sizeof dialog2, "{CCCCCC}Bolsillos de {F5DEB3}%s", GetNameFormat(playerid2));
	//show_dialog
	if (count == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, dialog2, "{CCCCCC}No tiene nada", "Cerrar", "");
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, dialog2, dialog, "Cerrar", "");
	return 1;
}

cmd:limpiarmanos(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new playerid2, string[256];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /limpiarmanos (PlayerID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador no se encuentra conectado.");

	QuitarManos(playerid2);
	format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) limpió las manos de %s(%d).", InfoCuenta[playerid][jNombre], playerid, NombreOriginal(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:limpiararmas(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new playerid2, string[256], count = 0, query[465];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /limpiararmas (PlayerID)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador no se encuentra conectado.");
	Loop(x, 9, 0) if (InfoInventario[InfoPersonaje[playerid2][pBolsillo][x]][IDArma] != 0)
	{
		InfoPersonaje[playerid2][pBolsillo][x] = 0;
		InfoPersonaje[playerid2][pBolsilloCant][x] = 0;
		count++;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = 0, Cantidad_bolsillo_%d = 0 WHERE ID = '%d'", x+1, x+1, InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
	}
	if (InfoInventario[InfoPersonaje[playerid2][pManoIzquierda]][IDArma] != 0)
	{
		InfoPersonaje[playerid2][pManoIzquierda] = 0;
		InfoPersonaje[playerid2][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid2, 8);
		count++;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
	}
	if (InfoInventario[InfoPersonaje[playerid2][pManoDerecha]][IDArma] != 0)
	{
		InfoPersonaje[playerid2][pManoDerecha] = 0;
		InfoPersonaje[playerid2][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid2, 7);
		ResetPlayerWeapons(playerid2);
		count++;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
	}
	if (InfoInventario[InfoPersonaje[playerid2][pEspalda]][IDArma] != 0)
	{
		InfoPersonaje[playerid2][pEspalda] = 0;
		InfoPersonaje[playerid2][pEspaldaCant] = 0;
		RemovePlayerAttachedObject(playerid2, 9);
		count++;
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = 0, Cantidad_espalda = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
	}
	if (count != 0)
	{
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) limpió %d armas a %s(%d).", InfoCuenta[playerid][jNombre], playerid, count, NombreOriginal(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		SendClientMessageEx(playerid2, COLOR_YELLOW, "%s(%d) limpió las armas de tu inventario.", InfoCuenta[playerid][jNombre], playerid);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no lleva armas encima.");
	return 1;
}

cmd:limpiarsuelo(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new count = 0, string[180];
	Loop(id, sizeof InfoSuelo, 0) if (InfoInventario[InfoSuelo[id][DropID]][IDArma] != 0)
	{
		count++;
		SueloTime(id);
	}
	if (count == 0) return SendPlayerChatMessage(playerid, 0xebebebff, "No hay ningún objeto tirado en todo el servidor.");
	format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s(%d) limpió %d armas del suelo.", InfoCuenta[playerid][jNombre], playerid, count);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:crearobjeto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new idobj, cantidad, string[180];
	if (sscanf(params, "ii", idobj, cantidad)) { SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /crearobjeto (ObjetoID) (Cantidad)"); return 1; }
	if (idobj <= 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "La ID del objeto no puede ser nula o negativa.");
	if (cantidad <= 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "La cantidad no puede ser nula o negativa.");
	if (idobj < 0 || idobj >= sizeof(InfoInventario)) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de objeto erroneo.");
	if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
	if (idobj == 86)
	{
		if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano derecha vacía.");
		crear_mochila(playerid);
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s ha creado (ID %d | %s) en mano derecha.", InfoCuenta[playerid][jNombre], idobj, InfoInventario[idobj][NombreObjeto]);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s ha creado %s(%d)", InfoCuenta[playerid][jNombre], InfoInventario[idobj][NombreObjeto], idobj);
		Log("f_logs/CrearObjeto.log", string);
	    return 1;
	}
	if (idobj == 55)
	{
		if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano derecha vacía.");
		crear_caja(playerid);
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s ha creado (ID %d | %s) en mano derecha.", InfoCuenta[playerid][jNombre], idobj, InfoInventario[idobj][NombreObjeto]);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s ha creado %s(%d)", InfoCuenta[playerid][jNombre], InfoInventario[idobj][NombreObjeto], idobj);
		Log("f_logs/CrearObjeto.log", string);
	    return 1;
	}
	if (InfoPersonaje[playerid][pManoDerecha] != 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = idobj;
		InfoPersonaje[playerid][pManoIzquierdaCant] = cantidad;
		PonerObjeto(playerid, 2, idobj);
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s ha creado (ID %d | %s | Cantidad %d) en mano izquierda.", InfoCuenta[playerid][jNombre], idobj, InfoInventario[idobj][NombreObjeto], cantidad);
	}
	else
	{
		InfoPersonaje[playerid][pManoDerecha] = idobj;
		InfoPersonaje[playerid][pManoDerechaCant] = cantidad;
		PonerObjeto(playerid, 1, idobj);
		if (InfoInventario[idobj][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[idobj][IDArma], cantidad); }
		format(string, sizeof string, "{FF2F2F}[AdmCmd]{FFFFFF} %s ha creado (ID %d | %s | Cantidad %d) en mano derecha.", InfoCuenta[playerid][jNombre], idobj, InfoInventario[idobj][NombreObjeto], cantidad);
	}
	ActualizarManos(playerid, 1);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s ha creado %s(%d) cantidad %d", InfoCuenta[playerid][jNombre], InfoInventario[idobj][NombreObjeto], idobj, cantidad);
	Log("f_logs/CrearObjeto.log", string);
	return 1;
}

cmd:listaobjetos(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	new DComandosAdmin[3500], as2[60], i = 0;
	for(new a = 1; a < sizeof(InfoInventario); a++)
	{
		i++;
		format(as2, sizeof(as2), "%d - %s | ", a, InfoInventario[a][NombreObjeto]);
		strcat(DComandosAdmin, as2);
		if(i == 6)
		{
			i = 0;
			strcat(DComandosAdmin, "\n");
		}
	}
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Lista del /crearobjeto", DComandosAdmin, "Continuar", "");
	return 1;
}
alias:listaobjetos("listaobjeto");

// Jugadores

cmd:estilobolsillos(playerid)
{
	if (InfoCuenta[playerid][jEstiloBolsillos] != 0)
	{
		InfoCuenta[playerid][jEstiloBolsillos] = 0;
		ShowTDN(playerid, "Ahora veras el sistema de bolsillos en ~b~~h~pantalla~w~.");
	}
	else
	{
		InfoCuenta[playerid][jEstiloBolsillos] = 1;
		ShowTDN(playerid, "Ahora verás el sistema de bolsillos en ~b~~h~diálogo~w~.");
	}
	guardar_int_mysql("cuentas", "EstiloBolsillos", InfoCuenta[playerid][jID], InfoCuenta[playerid][jEstiloBolsillos]);
	return 1;
}
alias:estilobolsillos("estilobolsillo");

cmd:bol(playerid)
{
    if (InventarioAbierto[playerid]) SetPlayerInventario(playerid, 2); // Si est� abierto, CERRAR
    else SetPlayerInventario(playerid, 1); // Si est� cerrado, ABRIR
    return 1;
}
alias:bol("inv", "inventario", "bolsillos");

Dialog:OpcionInventario(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[40];
	format(gformat, sizeof gformat, "RanuraInv%d", ID);
	new x = GetPVarInt(playerid, gformat);
	switch (x)
	{
		case 0..8: sacar_inventario(playerid, x);
		case 9: return pc_cmd_bol(playerid);
		case 10: guardar_inventario(playerid, 1);
		case 11: guardar_inventario(playerid, 2);
		case 12: pc_cmd_qespalda(playerid);
	}
	return 1;
}

cmd:cmano(playerid)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 0 && InfoPersonaje[playerid][pManoIzquierda] == 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en ninguna mano."); return 1; }
	new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoDerCant = InfoPersonaje[playerid][pManoDerechaCant];
	new ManoIzq = InfoPersonaje[playerid][pManoIzquierda], ManoIzqCant = InfoPersonaje[playerid][pManoIzquierdaCant];
	if (ManoDer == 0)
	{
		RemovePlayerAttachedObject(playerid, 8);
		PonerObjeto(playerid, 1, ManoIzq);
		SendPlayerChatMessage(playerid, 0x00AA00FF, "Cambiaste de lugar los objetos de tus manos.");
		if(InfoInventario[ManoIzq][IDArma] > 0) {
			GivePlayerWeapon(playerid, InfoInventario[ManoIzq][IDArma], ManoIzqCant);
		}
	}
	else if (ManoIzq == 0)
	{
		PonerObjeto(playerid, 2, ManoDer);
		ResetPlayerWeapons(playerid);
		RemovePlayerAttachedObject(playerid, 7);
		SendPlayerChatMessage(playerid, 0x00AA00FF, "Cambiaste de lugar los objetos de tus manos.");
	}
	else
	{
		ResetPlayerWeapons(playerid);
		PonerObjeto(playerid, 1, ManoIzq);
		PonerObjeto(playerid, 2, ManoDer);
		SendPlayerChatMessage(playerid, 0x00AA00FF, "Cambiaste de lugar los objetos de tus manos.");
		if(InfoInventario[ManoIzq][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[ManoIzq][IDArma], ManoIzqCant); }
	}
	InfoPersonaje[playerid][pManoDerechaCant] = ManoIzqCant, InfoPersonaje[playerid][pManoDerecha] = ManoIzq;
	InfoPersonaje[playerid][pManoIzquierdaCant] = ManoDerCant, InfoPersonaje[playerid][pManoIzquierda] = ManoDer;
	new query[500];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
	InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	SetPlayerInventario(playerid, 3);
	return 1;
}
alias:cmano("mano");

cmd:guardar(playerid)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 0) guardar_inventario(playerid, 2);
	else guardar_inventario(playerid, 1);
	SetPlayerInventario(playerid, 3);
	return 1;
}

cmd:sacar(playerid, params[])
{
	new id;
	if (sscanf(params, "i", id))
	{
	    new count = 0;
		Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] != 0) count++;
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tus bolsillos.");
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sacar (slot)");
		Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] != 0)
		{
			SendClientMessageEx(playerid, 0xEBEBEBFF, "Tienes en {b42d2d}slot %d{EBEBEB}: %s", x+1, slot_objeto(InfoPersonaje[playerid][pBolsillo][x], InfoPersonaje[playerid][pBolsilloCant][x]));
		}
		return 1;
	}
	if (id < 1 || id > 9) { SendPlayerChatMessage(playerid, COLOR_GREY, "El número de slot debe estar entre 1 y 9."); return 1; }
	sacar_inventario(playerid, id - 1);
	SetPlayerInventario(playerid, 3);
	return 1;
}

cmd:recoger(playerid, params[])
{
	if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes recoger nada si tienes ambas manos ocupadas."); return 1; }
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) { SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando en esta situación."); return 1; }
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido.");
	if (isnull(params)) recoger_objeto(playerid, -1);
	else
	{
		new id;
		if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /recogerobjeto (ObjetoID)");
		if (id < 0 || id >= MAX_OBJETOS_S) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Objeto incorrecto, selecciona entre 0-300.");
    	recoger_objeto(playerid, id);
	}
	SetPlayerInventario(playerid, 3);
    return 1;
}
alias:recoger("recogerobjeto");

cmd:ceder(playerid, params[])
{
	if (InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu mano derecha.");
	new playerid2, string[256];
	if (!CheckTimer(5, CederTiempo[playerid]))
	{
		if (sscanf(params, "u", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /ceder (PlayerID)");
		if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
		if (!CercaDelWeon(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Estás lejos del jugador.");
		new weaponid = InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma];
		if (InfoPersonaje[playerid2][pHorasOn] < 2)
		{
			if (weaponid >= 22 && weaponid <= 34)
			{
				SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador necesita tener al menos 2 horas de juego para recibir este tipo de arma.");
				return 1;
			}
		}
		if (InfoPersonaje[playerid2][pManoIzquierda] > 0 && InfoPersonaje[playerid2][pManoDerecha] > 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "Este jugador tiene ambas manos ocupadas."); return 1; }
		new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoDerCant = InfoPersonaje[playerid][pManoDerechaCant];
		if (InfoPersonaje[playerid2][pManoDerecha] == 0)
		{
			if (InfoInventario[ManoDer][IDArma] > 0) { GivePlayerWeapon(playerid2, InfoInventario[ManoDer][IDArma], ManoDerCant); }
			InfoPersonaje[playerid2][pManoDerecha] = ManoDer, InfoPersonaje[playerid2][pManoDerechaCant] = ManoDerCant, PonerObjeto(playerid2, 1, ManoDer);
		}
		else if (InfoPersonaje[playerid2][pManoIzquierda] == 0)
		{
			InfoPersonaje[playerid2][pManoIzquierda] = ManoDer, InfoPersonaje[playerid2][pManoIzquierdaCant] = ManoDerCant, PonerObjeto(playerid2, 2, ManoDer);
		}
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		ResetPlayerWeapons(playerid);
		CederTiempo[playerid] = gettime();
		format(string, sizeof string, "%s te entrega su %s.", GetNameFormat(playerid), InfoInventario[ManoDer][NombreObjeto]);
		SendPlayerChatMessage(playerid2, 0xf0ff00FF, string);
		format(string, sizeof string, "Entregas tu %s a %s.", InfoInventario[ManoDer][NombreObjeto], GetNameFormat(playerid2));
		SendPlayerChatMessage(playerid, 0xf0ff00FF, string);
		ActualizarManos(playerid, 1);
		ActualizarManos(playerid2, 1);
		SetPlayerInventario(playerid, 3);
		SetPlayerInventario(playerid2, 3);
		if (InfoInventario[ManoDer][IDArma] > 0)
		{
			format(string, sizeof string, "%s cedió %s a %s.", GetNameFormat(playerid), InfoInventario[ManoDer][NombreObjeto], GetNameFormat(playerid2));
			Log("f_logs/Ceder.log", string);
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(5, CederTiempo[playerid]) ));
	}
	return 1;
}
alias:ceder("dar", "dararma", "darobjeto");
