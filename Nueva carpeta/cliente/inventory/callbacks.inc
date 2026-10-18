forward tiene_objeto(playerid, objeto);
public tiene_objeto(playerid, objeto)
{
	Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] == objeto) return 1;
	Loop(x, 6, 0) if (InfoPersonaje[playerid][pCinturon][x] == objeto) return 1;
	if (InfoPersonaje[playerid][pManoDerecha] == objeto) return 1;
	if (InfoPersonaje[playerid][pManoIzquierda] == objeto) return 1;
	new no_tiene[256];
	format(no_tiene, sizeof no_tiene, "No tienes {b42d2d}%s{EFEFEF} en ninguna mano o en tu inventario.", InfoInventario[objeto][NombreObjeto]);
	SendPlayerChatMessage(playerid, 0xEFEFEFFF, no_tiene);
	return 0;
}

forward no_tiene_manos(playerid, objeto);
public no_tiene_manos(playerid, objeto)
{
	if (InfoPersonaje[playerid][pManoDerecha] == objeto) return 1;
	if (InfoPersonaje[playerid][pManoIzquierda] == objeto) return 1;
	new no_tiene[256];
	format(no_tiene, sizeof no_tiene, "No tienes {b42d2d}%s{EFEFEF} en ninguna mano.", InfoInventario[objeto][NombreObjeto]);
	SendPlayerChatMessage(playerid, 0xEFEFEFFF, no_tiene);
	return 0;
}

forward DarObjeto(playerid, objeto, cantidad);
public DarObjeto(playerid, objeto, cantidad)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		InfoPersonaje[playerid][pManoDerecha] = objeto;
		InfoPersonaje[playerid][pManoDerechaCant] = cantidad;
		PonerObjeto(playerid, 1, objeto);
		if (InfoInventario[objeto][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], cantidad); }
		ActualizarManos(playerid, 1);
		return 1;
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = objeto;
		InfoPersonaje[playerid][pManoIzquierdaCant] = cantidad;
		PonerObjeto(playerid, 2, objeto);
		ActualizarManos(playerid, 1);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Debes tener alguna mano vacía, tira o guarda lo que llevas en tus manos.");
	return 2;
}

forward PlayerWeapon(playerid, idarma);
public PlayerWeapon(playerid, idarma)
{
	new idobj = -1, gformat[128];
	Loop(x, sizeof InfoInventario, 0) if (InfoInventario[x][IDArma] == idarma)
	{
		idobj = x;
		break;
	}
	if (idobj == -1) { SendPlayerChatMessage(playerid, COLOR_GREY, "Error, ese id de arma no existe en la base de datos, contacta con el programador."); return 0; }
	if (InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		InfoPersonaje[playerid][pManoDerecha] = idobj;
		InfoPersonaje[playerid][pManoDerechaCant] = InfoInventario[idobj][DefaultCantidad];
		PonerObjeto(playerid, 1, idobj);
		GivePlayerWeapon(playerid, idarma, InfoInventario[idobj][DefaultCantidad]);
		ActualizarManos(playerid, 1);
		format(gformat, sizeof gformat, "Mano derecha: {F5DEB3}%s", InfoInventario[idobj][NombreObjeto]);
		SendPlayerChatMessage(playerid, 0xccccccff, gformat);
		return 1;
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = idobj;
		InfoPersonaje[playerid][pManoIzquierdaCant] = InfoInventario[idobj][DefaultCantidad];
		PonerObjeto(playerid, 2, idobj);
		ActualizarManos(playerid, 1);
		format(gformat, sizeof gformat, "Mano izquierda: {F5DEB3}%s{cccccc} usa /mano", InfoInventario[idobj][NombreObjeto]);
		SendPlayerChatMessage(playerid, 0xccccccff, gformat);
		return 1;
	}
	SendPlayerChatMessage(playerid, 0xebebebff, "Tienes ambas manos ocupadas!");
	return 0;
}

stock UpdateInv(playerid)
{
	if(InfoPersonaje[playerid][pManoDerecha] > 0)
	{
		if(GetPlayerWeapon(playerid) != InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma] && InfoPersonaje[playerid][pManoDerechaCant] > 0)
		{
			if(InfoPersonaje[playerid][pManoDerechaCant] > 0 && GetPlayerWeaponAmmo(playerid, InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma]) == 0)
			{
				ResetPlayerWeapons(playerid);
				GivePlayerWeapon(playerid, InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma], InfoPersonaje[playerid][pManoDerechaCant]);
			}
			SetPlayerArmedWeapon(playerid, InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma]);
		}
		else if(InfoPersonaje[playerid][pManoDerechaCant] == 0)
		{ //Si no le queda munición
			if(GetPlayerWeapon(playerid) != 0) SetPlayerArmedWeapon(playerid, 0);
		}
	}
	return 1;
}

stock QuitarBolsillos(playerid)
{
	Loop(e, 9, 0)
	{
		InfoPersonaje[playerid][pBolsillo][e] = 0;
		InfoPersonaje[playerid][pBolsilloCant][e] = 0;
	}
	new que2ry[1000], query[2000];
	format(que2ry, sizeof que2ry, "UPDATE personajes SET Bolsillo_1 = 0, Cantidad_bolsillo_1 = 0, Bolsillo_2 = 0, Cantidad_bolsillo_2 = 0, Bolsillo_3 = 0, Cantidad_bolsillo_3 = 0, Bolsillo_4 = 0, Cantidad_bolsillo_4 = 0, Bolsillo_5 = 0, Cantidad_bolsillo_5 = 0,");
	mysql_format(db_samp, query, sizeof query, "%s Bolsillo_6 = 0, Cantidad_bolsillo_6 = 0, Bolsillo_7 = 0, Cantidad_bolsillo_7 = 0, Bolsillo_8 = 0, Cantidad_bolsillo_8 = 0, Bolsillo_9 = 0, Cantidad_bolsillo_9 = 0 = 0 WHERE ID = '%d'", que2ry, InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

stock QuitarManos(playerid)
{
	InfoPersonaje[playerid][pManoIzquierda] = 0;
	InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
	InfoPersonaje[playerid][pManoDerecha] = 0;
	InfoPersonaje[playerid][pManoDerechaCant] = 0;
	RemovePlayerAttachedObject(playerid, 7);
	RemovePlayerAttachedObject(playerid, 8);
	ResetPlayerWeapons(playerid);
	new query[500];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0, Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

stock QuitarEspalda(playerid)
{
	InfoPersonaje[playerid][pEspalda] = 0, InfoPersonaje[playerid][pEspaldaCant] = 0;
	RemovePlayerAttachedObject(playerid, 9);
	new query[256];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = 0, Cantidad_espalda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

stock ActualizarManos(playerid, saved = 0)
{
	new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoDerCant = InfoPersonaje[playerid][pManoDerechaCant];
	if (ManoDer == 0) RemovePlayerAttachedObject(playerid, 7);
	if (InfoInventario[ManoDer][Arrojadizo] == 1 && ManoDerCant <= 0)
	{
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid, 7);
	}
	if (ManoDer > 0 && ManoDer < sizeof(InfoInventario))
	{
		if (ManoDerCant > InfoInventario[ManoDer][MaxCantidad])
		{
			if (InfoInventario[ManoDer][IDArma] > 0) { ResetPlayerWeapons(playerid), GivePlayerWeapon(playerid, InfoInventario[ManoDer][IDArma], InfoInventario[ManoDer][MaxCantidad]); }
			InfoPersonaje[playerid][pManoDerechaCant] = InfoInventario[ManoDer][MaxCantidad];
		}
		if (ManoDer < 16 && ManoDerCant <= 0) { GivePlayerWeapon(playerid, InfoInventario[ManoDer][IDArma], 1); }
	}
	new ManoIzq = InfoPersonaje[playerid][pManoIzquierda], ManoIzqCant = InfoPersonaje[playerid][pManoIzquierdaCant];
	if (ManoIzq == 0) RemovePlayerAttachedObject(playerid, 8);
	if (ManoIzq > 0 && ManoIzq < sizeof(InfoInventario))
	{
		if (ManoIzqCant > InfoInventario[ManoIzq][MaxCantidad]) { InfoPersonaje[playerid][pManoIzquierdaCant] = InfoInventario[ManoIzq][MaxCantidad]; }
		if (ManoIzq < 16 && ManoIzqCant <= 0) { InfoPersonaje[playerid][pManoIzquierdaCant] = 1; }
	}
	if (InfoInventario[ManoIzq][Arrojadizo] == 1 && ManoIzqCant <= 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid, 8);
	}
	if (saved != 0)
	{
		new query[512];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
		InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
	}
	return 1;
}