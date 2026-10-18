stock BorrarMueblesCasas(id) //comando /borrarcasa
{
	Loop(x, totalmuebles+1, 1) if (InfoMueble[x][mVirtualWorld] == id + 400)
	{
		borrar_mueble(x);
	}
}

stock BorrarMueblesNegocio(id) //comando /borrarcasa
{
	Loop(x, totalmuebles+1, 1) if (InfoMueble[x][mVirtualWorld] == id + 100)
	{
		borrar_mueble(x);
	}
}

funcion EditMueble(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) //OnPlayerEditDynamicObject
{
	new id = edicion_sql_actual[playerid], query[1028];
	if (id == -1) return SendPlayerChatMessage(playerid, -1, "Error edicion.");
	if (objectid == InfoMueble[id][mObjeto])
	{
		if (response == EDIT_RESPONSE_FINAL)
		{
			InfoMueble[id][mPotX] = x;
			InfoMueble[id][mPotY] = y;
			InfoMueble[id][mPotZ] = z;
			InfoMueble[id][mRotX] = rx;
			InfoMueble[id][mRotY] = ry;
			InfoMueble[id][mRotZ] = rz;
			SetDynamicObjectPos(objectid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ]);
			SetDynamicObjectRot(objectid, InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ], InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mInterior], InfoMueble[id][mVirtualWorld], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			InfoPersonaje[playerid][pEditingMode] = 0;
			edicion_sql_actual[playerid] = -1;
			is_mueble_actual[playerid] = 0;
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
			SetDynamicObjectPos(objectid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ]);
			SetDynamicObjectRot(objectid, InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ], InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mInterior], InfoMueble[id][mVirtualWorld], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			InfoPersonaje[playerid][pEditingMode] = 0;
			edicion_sql_actual[playerid] = -1;
			is_mueble_actual[playerid] = 0;
		}
	}
	return 1;
}

OpenableDoor(modelid)
{
    static const openableDoors[] =
    {
        1495, 1498, 1535, 1557, 1536, 3089, 997,
        1492, 1494, 1493, 1499, 1504, 1507, 1567,
        1555, 2963, 19302, 19303, 1569, 1537, 2875,
        2876, 2877, 2878, 19859, 19860, 1561, 19875
    };

    for(new x; x < sizeof(openableDoors); x++) if(modelid == openableDoors[x]) return x;

    return -1;
}

check_id_prop_mueble(playerid)
{
	new id = -1;
	if (DentroCasa[playerid] != -1)
	{
		id = DentroCasa[playerid];
	}
	if (DentroNegocio[playerid] != -1)
	{
		id = DentroNegocio[playerid];
	}
	return id;
}

CountMuebles(playerid)
{
	new VW = GetPlayerVirtualWorld(playerid), count = 0;
	Loop(id, totalmuebles+1, 1) if (InfoMueble[id][mVirtualWorld] == VW)
	{
        count++;
	}
	return count;
}

ListaMuebles(playerid, pagina)
{
	new actual_muebles = CountMuebles(playerid);
	if (actual_muebles == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún mueble.");

	pagina_mueble[playerid] = pagina;
	is_mueble_actual[playerid] = 0;
	//check id mueble
	new countx = 0, VW = GetPlayerVirtualWorld(playerid);
	Loop(id, totalmuebles+1, 1) if (InfoMueble[id][mVirtualWorld] == VW)
	{
		new format_var[128];
		format(format_var, sizeof format_var, "judsjmueble%d", countx);
		SetPVarInt(playerid, format_var, id);
		countx++;
	}
	//show dialogo
	new gformat[256], show_dialog[3072], show_muestra, inicio_id;
	switch (pagina)
	{
		case 1: show_muestra = 50, inicio_id = 0;
		case 2: show_muestra = MAX_PAGE_FURNITURE*2, inicio_id = MAX_PAGE_FURNITURE;
		case 3: show_muestra = MAX_PAGE_FURNITURE*3, inicio_id = MAX_PAGE_FURNITURE*2;
		case 4: show_muestra = MAX_PAGE_FURNITURE*4, inicio_id = MAX_PAGE_FURNITURE*3;
		case 5: show_muestra = MAX_PAGE_FURNITURE*5, inicio_id = MAX_PAGE_FURNITURE*4;
		case 6: show_muestra = MAX_PAGE_FURNITURE*6, inicio_id = MAX_PAGE_FURNITURE*5;
		case 7: show_muestra = MAX_PAGE_FURNITURE*7, inicio_id = MAX_PAGE_FURNITURE*6;
		case 8: show_muestra = MAX_PAGE_FURNITURE*8, inicio_id = MAX_PAGE_FURNITURE*7;
		case 9: show_muestra = MAX_PAGE_FURNITURE*9, inicio_id = MAX_PAGE_FURNITURE*8;
		case 10: show_muestra = MAX_PAGE_FURNITURE*10, inicio_id = MAX_PAGE_FURNITURE*9;
	}
	new count = 0;
	Loop(x, show_muestra, inicio_id)
	{
		new format_var[128];
		format(format_var, sizeof format_var, "judsjmueble%d", x);
		new id = GetPVarInt(playerid, format_var), excolor[10];
		if (InfoMueble[id][mInterior] == -1) excolor = "{F4C221}";
		else excolor = "{2EC231}";
		if (InfoMueble[id][mVirtualWorld] == VW)
		{
			format(gformat, sizeof gformat, "(%d) %s%s\n", x+1, excolor, InfoMueble[id][mNombre]);
			strcat(show_dialog, gformat);
			format(format_var, sizeof format_var, "mueble_actual%d", count);
			SetPVarInt(playerid, format_var, id);
			count++;
		}
		format(format_var, sizeof format_var, "judsjmueble%d", x);
		SetPVarInt(playerid, format_var, 0);
	}
	//siguiente página
	if (actual_muebles >= MAX_PAGE_FURNITURE*pagina)
	{
		format(gformat, sizeof gformat, "{F5DEB3}>> Ir siguiente página %d\n", pagina+1);
		strcat(show_dialog, gformat);
	}
	format(gformat, sizeof gformat, "Lista de tus muebles: {F5DEB3}%d", actual_muebles);
	Dialog_Show(playerid, ShowMuebles, DIALOG_STYLE_LIST, gformat, show_dialog, "Continuar", "Volver");
	return 1;
}

borrar_mueble(id)
{
	if (IsValidDynamicObject(InfoMueble[id][mObjeto])) DestroyDynamicObject(InfoMueble[id][mObjeto]);
	InfoMueble[id][mObjeto] = 0;
	InfoMueble[id][mTipo] = 0;
	InfoMueble[id][mPropiedad] = -1;
	InfoMueble[id][mModelo] = 0;
	alm(InfoMueble[id][mNombre], "none");
	InfoMueble[id][mPotX] = 0.0;
	InfoMueble[id][mPotY] = 0.0;
	InfoMueble[id][mPotZ] = 0.0;
	InfoMueble[id][mRotX] = 0.0;
	InfoMueble[id][mRotY] = 0.0;
	InfoMueble[id][mRotZ] = 0.0;
	InfoMueble[id][mInterior] = -1;
	InfoMueble[id][mVirtualWorld] = 0;
	InfoMueble[id][mPrecio] = 0;
	InfoMueble[id][mPuerta] = 0;
	new query[1028];
	mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET Tipo = 0, Propiedad = -1, Modelo = 0, PotX = 0.0, PotY = 0.0, PotZ = 0.0, \
	RotX = 0.0, RotY = 0.0, RotZ = 0.0, Interior = -1, VirtualWorld = 0, Precio = 0, Puerta = 0 WHERE ID = '%d'", InfoMueble[id][mID_sql]);
	mysql_tquery(db_samp, query);
	if (InfoMueble[id][mTxtModelo1] != 0)
	{
		InfoMueble[id][mTxtMaterial1] = -1;
		InfoMueble[id][mTxtModelo1] = 0;
		alm(InfoMueble[id][mTxtNombre1], "none");
		alm(InfoMueble[id][mTxtNombreTextura1], "none");
		InfoMueble[id][mTxtColor1] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e', TxtColor1 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
	}
	if (InfoMueble[id][mTxtModelo2] != 0)
	{
		InfoMueble[id][mTxtMaterial2] = -1;
		InfoMueble[id][mTxtModelo2] = 0;
		alm(InfoMueble[id][mTxtNombre2], "none");
		alm(InfoMueble[id][mTxtNombreTextura2], "none");
		InfoMueble[id][mTxtColor2] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial2 = '%d', TxtModelo2 = '%d', TxtNombre2 = '%e', TxtNombreTextura2 = '%e', TxtColor2 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
	}
	if (InfoMueble[id][mTxtModelo3] != 0)
	{
		InfoMueble[id][mTxtMaterial3] = -1;
		InfoMueble[id][mTxtModelo3] = 0;
		alm(InfoMueble[id][mTxtNombre3], "none");
		alm(InfoMueble[id][mTxtNombreTextura3], "none");
		InfoMueble[id][mTxtColor3] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtNombre3 = '%e', TxtNombreTextura3 = '%e', TxtColor3 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
	}
	if (InfoMueble[id][mTxtModelo4] != 0)
	{
		InfoMueble[id][mTxtMaterial4] = -1;
		InfoMueble[id][mTxtModelo4] = 0;
		alm(InfoMueble[id][mTxtNombre4], "none");
		alm(InfoMueble[id][mTxtNombreTextura4], "none");
		InfoMueble[id][mTxtColor4] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtNombre4 = '%e', TxtNombreTextura4 = '%e', TxtColor4 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
	}
	if (InfoMueble[id][mTxtModelo5] != 0)
	{
		InfoMueble[id][mTxtMaterial5] = -1;
		InfoMueble[id][mTxtModelo5] = 0;
		alm(InfoMueble[id][mTxtNombre5], "none");
		alm(InfoMueble[id][mTxtNombreTextura5], "none");
		InfoMueble[id][mTxtColor5] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre5 = '%e', TxtNombreTextura5 = '%e', TxtColor5 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
	}
	return 1;
}

Adquirir_mueble(playerid, tipo, modelid, precio, propiedad)
{
	if (propiedad == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrio un error con la compra de muebles (1) contacta con el programador.");
	new gformat[256], OBJ_INDEX, nameP[10], limite = InfoCuenta[playerid][jMaxMuebles], VW = GetPlayerVirtualWorld(playerid);
	buscar_modelo_obj(modelid, OBJ_INDEX);
	if (tipo == 1) alm(nameP, "casa");
	else if (tipo == 2) alm(nameP, "negocio");
	if (limite == CountMuebles(playerid))
	{
		SendClientMessageEx(playerid, COLOR_GREY, "* No puedes tener más de %d muebles en tu %s.", limite, nameP);
		return 1;
	}
	format(gformat, sizeof gformat, "Nuevo mueble {D1C231}%s{FFFFFF} para tu {D1C231}%s{FFFFFF}.", objetos_interior[OBJ_INDEX][2], nameP);
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
	MuebleActual[playerid] = 0;
	//opcion idsql ya creada.
	new query[1028];
	Loop(id, totalmuebles+1, 1)
	{
		if (InfoMueble[id][mID_sql] != 0 && InfoMueble[id][mModelo] == 0)
		{
			InfoMueble[id][mTipo] = tipo;
			InfoMueble[id][mPropiedad] = propiedad;
			InfoMueble[id][mModelo] = modelid;
			InfoMueble[id][mInterior] = -1;
			InfoMueble[id][mVirtualWorld] = VW;
			InfoMueble[id][mPrecio] = precio;
			alm(InfoMueble[id][mNombre], objetos_interior[OBJ_INDEX][2]);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET Tipo = '%d', Propiedad = '%d', Modelo = '%d', Nombre = '%e', VirtualWorld = '%d', Precio = '%d' WHERE ID = '%d'", tipo, propiedad, modelid, InfoMueble[id][mNombre], VW, precio, InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			return 1;
		}
	}
	//opcion id por crear
	mysql_format(db_samp, query, sizeof query, "INSERT INTO muebles (Tipo, Propiedad, Modelo, Nombre, VirtualWorld, Precio) VALUES ('%d', '%d', '%d', '%e', '%d', '%d')", tipo, propiedad, modelid, objetos_interior[OBJ_INDEX][2], VW, precio);
	mysql_tquery(db_samp, query, "OnCreateMueble", "i", 0);
	new newid = totalmuebles+1;
	InfoMueble[newid][mInterior] = -1;
	InfoMueble[newid][mTipo] = tipo;
	InfoMueble[newid][mPropiedad] = propiedad;
	InfoMueble[newid][mModelo] = modelid;
	InfoMueble[newid][mVirtualWorld] = VW;
	InfoMueble[newid][mPrecio] = precio;
	alm(InfoMueble[newid][mNombre], objetos_interior[OBJ_INDEX][2]);
	return 1;
}