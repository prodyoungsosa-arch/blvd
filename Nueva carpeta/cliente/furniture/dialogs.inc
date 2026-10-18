Dialog:BorrarAllMuebles(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_muebles(playerid);
	new id = -1, nameP[10];
	if (DentroCasa[playerid] != -1)
	{
		id = DentroCasa[playerid];
		alm(nameP, "casa");
	}
	if (DentroNegocio[playerid] != -1)
	{
		id = DentroNegocio[playerid];
		alm(nameP, "negocio");
	}
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error, si el mismo continua contacta con el programador.");
	new count_mubles = 0, gformat[128];
	if (DentroCasa[playerid] != -1)
	{
		Loop(x, totalmuebles+1, 1) if (InfoMueble[x][mVirtualWorld] == id + 400)
		{
			borrar_mueble(x);
			count_mubles++;
		}
	}
	if (DentroNegocio[playerid] != -1)
	{
		Loop(x, totalmuebles+1, 1) if (InfoMueble[x][mVirtualWorld] == id + 100)
		{
			borrar_mueble(x);
			count_mubles++;
		}
	}
	format(gformat, sizeof gformat, "Borraste los %d muebles de tu %s.", count_mubles, nameP);
	SendPlayerChatMessage(playerid, COLOR_GREEN, gformat);
	return 1;
}

Dialog:MenuMuebles(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = -1;
	if (DentroCasa[playerid] != -1) id = DentroCasa[playerid];
	if (DentroNegocio[playerid] != -1) id = DentroNegocio[playerid];
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error, si el mismo continua contacta con el programador.");
	switch (listitem)
	{
		case 0: ListaMuebles(playerid, 1);
		case 1:
		{
			Dialog_Show(playerid, MenuMebles2, DIALOG_STYLE_TABLIST_HEADERS, "{D6E1EB}Muebles", "Tipo de mueble\tPágina\n\
			Mesas, sillas, sillones\t#1\n\
			Juego de cuarto, camas\t#4\n\
			Baño\t#8\n\
			Cocina\t#10\n\
			Comida + Viveres\t#12\n\
			Electrónica\t#18\n\
			Accesorios varios\t#15\n\
			Accesorios varios-B\t#21\n\
			Puertas\t#27\n\
			Objetos de locales\t#28\n\
			Garaje, mecánica\t#32\n\
			Paredes, marcos\t#35", ">>", "Volver");
		}
		case 2:
		{
			new actual_muebles = CountMuebles(playerid);
			if (actual_muebles == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún mueble.");
			Dialog_Show(playerid, BorrarAllMuebles, DIALOG_STYLE_MSGBOX, "Borrar muebles", "{EBEBEB}¿Estás seguro de borrar todos los muebles?", "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:MenuMebles2(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_muebles(playerid);
	new pagina = -1;

	if (listitem == 0) pagina = 0;
	else if (listitem == 1) pagina = 3;
	else if (listitem == 2) pagina = 7;
	else if (listitem == 3) pagina = 9;
	else if (listitem == 4) pagina = 11;
	else if (listitem == 5) pagina = 17;
	else if (listitem == 6) pagina = 14;
	else if (listitem == 7) pagina = 20;
	else if (listitem == 8) pagina = 26;
	else if (listitem == 9) pagina = 27;
	else if (listitem == 10) pagina = 31;
	else if (listitem == 11) pagina = 34;

	if(pagina != -1) ShowModelSelectionMenu(playerid, ob_muebles, "Muebles", pagina);
	return 1;
}

Dialog:ShowMuebles(playerid, response, listitem, inputtext[])
{
	//opción volver
	if (!response)
	{
		if (pagina_mueble[playerid] != 1) ListaMuebles(playerid, pagina_mueble[playerid]-1);
		else pc_cmd_muebles(playerid);
		return 1;
	}
	//siguiente página
	if (listitem == MAX_PAGE_FURNITURE) return ListaMuebles(playerid, pagina_mueble[playerid]+1);
	//opción continuar
	new format_var[128];
	format(format_var, sizeof format_var, "mueble_actual%d", listitem);
	new id = GetPVarInt(playerid, format_var);
	if (!InfoMueble[id][mModelo]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No has seleccionado nada.");
	is_mueble_actual[playerid] = id;
	Dialogo_Editar_Mueble(playerid, id);
	return 1;
}

Dialogo_Editar_Mueble(playerid, id)
{
	new show_dialog[860];
	if (InfoMueble[id][mInterior] != -1) format(show_dialog, sizeof show_dialog, "{FFFFFF}Información\n{2EC231}Ocultar{FFFFFF}\nEditar posición\n{FF6347}Editar texturas{FFFFFF}\nEditar nombre\nGirar\nClonar\nBorrar");
	else format(show_dialog, sizeof show_dialog, "{FFFFFF}Información\n{F4C221}Mostrar{FFFFFF}\nEditar posición\n{FF6347}Editar texturas{FFFFFF}\nEditar nombre\nGirar\nClonar\nBorrar");
	Dialog_Show(playerid, EditarMueble, DIALOG_STYLE_LIST, "Menú del mueble", show_dialog, "Continuar", "Volver");
	return 1;
}

new id_mueble_textura[MAX_PLAYERS];

Dialog_Editar_Textura(playerid, id)
{
	id_mueble_textura[playerid] = -1;
	new show_dialog[1402], newformat[256], count = 0;
	strcat(show_dialog, "Modelo\tNombre TXD\tNombre textura\n");
	if (InfoMueble[id][mTxtModelo1] != 0) format(newformat, sizeof newformat, "%d\t%s\t%s\n", InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1]), count++;
	else format(newformat, sizeof newformat, "Disponible\n");
	strcat(show_dialog, newformat);
	if (InfoMueble[id][mTxtModelo2] != 0) format(newformat, sizeof newformat, "%d\t%s\t%s\n", InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2]), count++;
	else format(newformat, sizeof newformat, "Disponible\n");
	strcat(show_dialog, newformat);
	if (InfoMueble[id][mTxtModelo3] != 0) format(newformat, sizeof newformat, "%d\t%s\t%s\n", InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3]), count++;
	else format(newformat, sizeof newformat, "Disponible\n");
	strcat(show_dialog, newformat);
	if (InfoMueble[id][mTxtModelo4] != 0) format(newformat, sizeof newformat, "%d\t%s\t%s\n", InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4]), count++;
	else format(newformat, sizeof newformat, "Disponible\n");
	strcat(show_dialog, newformat);
	if (InfoMueble[id][mTxtModelo5] != 0) format(newformat, sizeof newformat, "%d\t%s\t%s\n", InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5]), count++;
	else format(newformat, sizeof newformat, "Disponible\n");
	strcat(show_dialog, newformat);
	if (count != 0)
	{
		strcat(show_dialog, "{D1C231}Remover todas las texturas");
		Dialog_Show(playerid, EditarTextura, DIALOG_STYLE_TABLIST_HEADERS, "Editar texturas del mueble", show_dialog, "Continuar", "Volver");
	}
	else Dialog_Show(playerid, EditarTextura, DIALOG_STYLE_TABLIST_HEADERS, "Editar texturas del mueble", show_dialog, "Continuar", "Volver");
	return 1;
}

Dialog:EditarMueble(playerid, response, listitem, inputtext[])
{
	//opción volver
	if (!response)
	{
		ListaMuebles(playerid, pagina_mueble[playerid]);
		return 1;
	}
	new id = is_mueble_actual[playerid], gformat[256], query[512];
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	//opción continuar
	switch (listitem)
	{
		case 0:
		{
			if (InfoMueble[id][mInterior] != -1) format(gformat, sizeof gformat, "{FFFFFF}Nombre: %s\nModelo: %d\nDistancia: %0.2f metros\n{2EC231}Colocado", InfoMueble[id][mNombre], InfoMueble[id][mModelo], (GetPlayerDistanceFromPoint(playerid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ]) * 0.01));
			else format(gformat, sizeof gformat, "{FFFFFF}Nombre: %s\nModelo: %d\n{F4C221}Oculto", InfoMueble[id][mNombre], InfoMueble[id][mModelo]);
			Dialog_Show(playerid, DialogNone, DIALOG_STYLE_MSGBOX, "Información", gformat, "Cerrar", "");
			is_mueble_actual[playerid] = 0;
		}
		case 1: //ocultar/mostrar
		{
		    if (InfoMueble[id][mInterior] != -1)
		    {
				InfoMueble[id][mInterior] = -1;
				if (IsValidDynamicObject(InfoMueble[id][mObjeto])) DestroyDynamicObject(InfoMueble[id][mObjeto]);
				InfoMueble[id][mObjeto] = 0;
				is_mueble_actual[playerid] = 0;
				format(gformat, sizeof gformat, "Ocultaste {2EC231}%s{FFFFFF}.", InfoMueble[id][mNombre]);
				SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
		    }
		    else
		    {
		        new edit = 0;
				if (InfoMueble[id][mPotX] == 0.0 && InfoMueble[id][mPotY] == 0.0 && InfoMueble[id][mPotZ] == 0.0)
				{
					GetPlayerPos(playerid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ]);
	        		GetXYInFrontOfPlayer(playerid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], 3.0);
	        		edit = 1;
	        	}
				InfoMueble[id][mInterior] = GetPlayerInterior(playerid);
				InfoMueble[id][mObjeto] = CreateDynamicObject(InfoMueble[id][mModelo], InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ], InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mVirtualWorld], InfoMueble[id][mInterior]);

				if (InfoMueble[id][mTxtModelo1] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]); }
				if (InfoMueble[id][mTxtModelo2] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]); }
				if (InfoMueble[id][mTxtModelo3] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]); }
				if (InfoMueble[id][mTxtModelo4] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]); }
				if (InfoMueble[id][mTxtModelo5] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]); }

				if (edit != 0)
				{
					InfoPersonaje[playerid][pEditingMode] = 55;
					EditDynamicObject(playerid, InfoMueble[id][mObjeto]);
					edicion_sql_actual[playerid] = id;

					SendPlayerChatMessage(playerid, COLOR_GREY, "El objeto no tenía posición guardada, así que te tocará editarlo.");
				}
				else
				{
					format(gformat, sizeof gformat, "Sacaste {F4C221}%s{FFFFFF}.", InfoMueble[id][mNombre]);
					SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
					is_mueble_actual[playerid] = 0;
				}
			}
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET Interior = '%d' WHERE ID = '%d'", InfoMueble[id][mInterior], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			Streamer_Update(playerid);
		}
		case 2:
		{
			//si no tiene configurado la id.
			if (InfoMueble[id][mPotX] == 0.0 && InfoMueble[id][mPotY] == 0.0 && InfoMueble[id][mPotZ] == 0.0)
			{
				GetPlayerPos(playerid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ]);
        		GetXYInFrontOfPlayer(playerid, InfoMueble[id][mPotX], InfoMueble[id][mPotY], 3.0);
        	}
			if (InfoMueble[id][mInterior] == -1)
			{
				InfoMueble[id][mInterior] = GetPlayerInterior(playerid);
				InfoMueble[id][mObjeto] = CreateDynamicObject(InfoMueble[id][mModelo], InfoMueble[id][mPotX], InfoMueble[id][mPotY], InfoMueble[id][mPotZ], 0.0, 0.0, 0.0, InfoMueble[id][mVirtualWorld], InfoMueble[id][mInterior]);

				if (InfoMueble[id][mTxtModelo1] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]); }
				if (InfoMueble[id][mTxtModelo2] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]); }
				if (InfoMueble[id][mTxtModelo3] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]); }
				if (InfoMueble[id][mTxtModelo4] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]); }
				if (InfoMueble[id][mTxtModelo5] != 0) { SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]); }
			}
			InfoPersonaje[playerid][pEditingMode] = 55;
			EditDynamicObject(playerid, InfoMueble[id][mObjeto]);
			edicion_sql_actual[playerid] = id;
		}
		case 3:
		{
			if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
			Dialog_Editar_Textura(playerid, id);
		}
		case 4: Dialog_Show(playerid, ChangeMuebleName, DIALOG_STYLE_INPUT, "Nombre del mueble", "{EBEBEB}Escribe el nuevo nombre del mueble", "Continuar", "Volver");
		case 5:
		{
			if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
			Dialog_Show(playerid, GirarMueble, DIALOG_STYLE_LIST, "Girar mueble", "0 grados\n90 grados\n180 grados\n270 grados", "Continuar", "Volver");
		}
		case 6:
		{
			if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
			new nameP[10], limite = InfoCuenta[playerid][jMaxMuebles];
			if (DentroCasa[playerid] != -1)
			{
				alm(nameP, "casa");
			}
			if (DentroNegocio[playerid] != -1)
			{
				alm(nameP, "negocio");
			}
			if (limite == CountMuebles(playerid))
			{
				SendClientMessageEx(playerid, COLOR_GREY, "* No puedes tener más de %d muebles en tu %s.", limite, nameP);
				return 1;
			}
			//opción idsql ya creada.
			Loop(clon, totalmuebles+1, 1)
			{
				if (InfoMueble[clon][mID_sql] != 0 && InfoMueble[clon][mModelo] == 0)
				{
					InfoMueble[clon][mTipo] = InfoMueble[id][mTipo];
					InfoMueble[clon][mPropiedad] = InfoMueble[id][mPropiedad];
					InfoMueble[clon][mModelo] = InfoMueble[id][mModelo];
					alm(InfoMueble[clon][mNombre], InfoMueble[id][mNombre]);
					InfoMueble[clon][mPotX] = InfoMueble[id][mPotX];
					InfoMueble[clon][mPotY] = InfoMueble[id][mPotY];
					InfoMueble[clon][mPotZ] = InfoMueble[id][mPotZ];
					InfoMueble[clon][mRotX] = InfoMueble[id][mRotX];
					InfoMueble[clon][mRotY] = InfoMueble[id][mRotY];
					InfoMueble[clon][mRotZ] = InfoMueble[id][mRotZ];
					InfoMueble[clon][mInterior] = InfoMueble[id][mInterior];
					InfoMueble[clon][mVirtualWorld] = InfoMueble[id][mVirtualWorld];
					InfoMueble[clon][mPrecio] = InfoMueble[id][mPrecio];
					InfoMueble[clon][mPuerta] = InfoMueble[id][mPuerta];
					InfoMueble[clon][mTxtMaterial1] = InfoMueble[id][mTxtMaterial1];
					InfoMueble[clon][mTxtModelo1] = InfoMueble[id][mTxtModelo1];
					alm(InfoMueble[clon][mTxtNombre1], InfoMueble[id][mTxtNombre1]);
					alm(InfoMueble[clon][mTxtNombreTextura1], InfoMueble[id][mTxtNombreTextura1]);
					InfoMueble[clon][mTxtColor1] = InfoMueble[id][mTxtColor1];
					InfoMueble[clon][mTxtMaterial2] =  InfoMueble[id][mTxtMaterial2];
					InfoMueble[clon][mTxtModelo2] = InfoMueble[id][mTxtModelo2];
					alm(InfoMueble[clon][mTxtNombre2], InfoMueble[id][mTxtNombre2]);
					alm(InfoMueble[clon][mTxtNombreTextura2], InfoMueble[id][mTxtNombreTextura2]);
					InfoMueble[clon][mTxtColor2] = InfoMueble[id][mTxtColor2];
					InfoMueble[clon][mTxtMaterial3] = InfoMueble[id][mTxtMaterial3];
					InfoMueble[clon][mTxtModelo3] = InfoMueble[id][mTxtModelo3];
					alm(InfoMueble[clon][mTxtNombre3], InfoMueble[id][mTxtNombre3]);
					alm(InfoMueble[clon][mTxtNombreTextura3], InfoMueble[id][mTxtNombreTextura3]);
					InfoMueble[clon][mTxtColor3] = InfoMueble[id][mTxtColor3];
					InfoMueble[clon][mTxtMaterial4] = InfoMueble[id][mTxtMaterial4];
					InfoMueble[clon][mTxtModelo4] = InfoMueble[id][mTxtModelo4];
					alm(InfoMueble[clon][mTxtNombre4], InfoMueble[id][mTxtNombre4]);
					alm(InfoMueble[clon][mTxtNombreTextura4], InfoMueble[id][mTxtNombreTextura4]);
					InfoMueble[clon][mTxtColor4] = InfoMueble[id][mTxtColor4];
					InfoMueble[clon][mTxtMaterial5] = InfoMueble[id][mTxtMaterial5];
					InfoMueble[clon][mTxtModelo5] = InfoMueble[id][mTxtModelo5];
					alm(InfoMueble[clon][mTxtNombre5], InfoMueble[id][mTxtNombre5]);
					alm(InfoMueble[clon][mTxtNombreTextura5], InfoMueble[id][mTxtNombreTextura5]);
					InfoMueble[clon][mTxtColor5] = InfoMueble[id][mTxtColor5];

					new offquery[2048], onquery[5000];
					//primer
					format(offquery, sizeof offquery, "UPDATE muebles SET Tipo = '%d', Propiedad = '%d', Modelo = '%d', PotX = '%f', \
					PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d', Precio = '%d', Puerta = '%d',",
					InfoMueble[clon][mTipo], InfoMueble[clon][mPropiedad], InfoMueble[clon][mModelo], InfoMueble[clon][mPotX], InfoMueble[clon][mPotY], InfoMueble[clon][mPotZ],
					InfoMueble[clon][mRotX], InfoMueble[clon][mRotY], InfoMueble[clon][mRotZ], InfoMueble[clon][mInterior], InfoMueble[clon][mVirtualWorld], InfoMueble[clon][mPrecio], InfoMueble[clon][mPuerta]);

					//segundo
					format(offquery, sizeof offquery, "%s TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtColor1 = '%d', TxtMaterial2 = '%d', TxtModelo2 = '%d', \
					TxtColor2 = '%d', TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtColor3 = '%d', TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtColor4 = '%d',",
					offquery, InfoMueble[clon][mTxtMaterial1], InfoMueble[clon][mTxtModelo1], InfoMueble[clon][mTxtColor1], InfoMueble[clon][mTxtMaterial2], InfoMueble[clon][mTxtModelo2],
					InfoMueble[clon][mTxtColor2], InfoMueble[clon][mTxtMaterial3], InfoMueble[clon][mTxtModelo3], InfoMueble[clon][mTxtColor3], InfoMueble[clon][mTxtMaterial4], InfoMueble[clon][mTxtModelo4], InfoMueble[clon][mTxtColor4]);

					//tercero
					mysql_format(db_samp, onquery, sizeof onquery, "%s TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e', TxtNombre2 = '%e', TxtNombreTextura2 = '%e', \
					TxtNombre3 = '%e', TxtNombreTextura3 = '%e', TxtNombre4 = '%e', TxtNombreTextura4 = '%e', TxtNombre5 = '%e', TxtNombreTextura5 = '%e', TxtColor5 = '%d', Nombre = '%e' WHERE ID = '%d'",
					offquery, InfoMueble[clon][mTxtMaterial5], InfoMueble[clon][mTxtModelo5], InfoMueble[clon][mTxtNombre1], InfoMueble[clon][mTxtNombreTextura1], InfoMueble[clon][mTxtNombre2], InfoMueble[clon][mTxtNombreTextura2],
					InfoMueble[clon][mTxtNombre3], InfoMueble[clon][mTxtNombreTextura3], InfoMueble[clon][mTxtNombre4], InfoMueble[clon][mTxtNombreTextura4], InfoMueble[clon][mTxtNombre5], InfoMueble[clon][mTxtNombreTextura5], InfoMueble[clon][mTxtColor5], InfoMueble[clon][mNombre], InfoMueble[clon][mID_sql]);
					mysql_tquery(db_samp, onquery);

					InfoMueble[clon][mObjeto] = CreateDynamicObject(InfoMueble[clon][mModelo], InfoMueble[clon][mPotX], InfoMueble[clon][mPotY], InfoMueble[clon][mPotZ], InfoMueble[clon][mRotX], InfoMueble[clon][mRotY], InfoMueble[clon][mRotZ], InfoMueble[clon][mVirtualWorld], InfoMueble[clon][mInterior]);

					if (InfoMueble[clon][mTxtModelo1] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial1], InfoMueble[clon][mTxtModelo1], InfoMueble[clon][mTxtNombre1], InfoMueble[clon][mTxtNombreTextura1], InfoMueble[clon][mTxtColor1]); }
					if (InfoMueble[clon][mTxtModelo2] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial2], InfoMueble[clon][mTxtModelo2], InfoMueble[clon][mTxtNombre2], InfoMueble[clon][mTxtNombreTextura2], InfoMueble[clon][mTxtColor2]); }
					if (InfoMueble[clon][mTxtModelo3] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial3], InfoMueble[clon][mTxtModelo3], InfoMueble[clon][mTxtNombre3], InfoMueble[clon][mTxtNombreTextura3], InfoMueble[clon][mTxtColor3]); }
					if (InfoMueble[clon][mTxtModelo4] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial4], InfoMueble[clon][mTxtModelo4], InfoMueble[clon][mTxtNombre4], InfoMueble[clon][mTxtNombreTextura4], InfoMueble[clon][mTxtColor4]); }
					if (InfoMueble[clon][mTxtModelo5] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial5], InfoMueble[clon][mTxtModelo5], InfoMueble[clon][mTxtNombre5], InfoMueble[clon][mTxtNombreTextura5], InfoMueble[clon][mTxtColor5]); }

					InfoPersonaje[playerid][pEditingMode] = 55;
					EditDynamicObject(playerid, InfoMueble[clon][mObjeto]);
					edicion_sql_actual[playerid] = clon;
					SendPlayerChatMessage(playerid, COLOR_GREY, "Objeto duplicado, ya puedes editarlo.");
					return 1;
				}
			}
			new clon = totalmuebles+1;
		   	InfoMueble[clon][mTipo] = InfoMueble[id][mTipo];
			InfoMueble[clon][mPropiedad] = InfoMueble[id][mPropiedad];
			InfoMueble[clon][mModelo] = InfoMueble[id][mModelo];
			alm(InfoMueble[clon][mNombre], InfoMueble[id][mNombre]);
			InfoMueble[clon][mPotX] = InfoMueble[id][mPotX];
			InfoMueble[clon][mPotY] = InfoMueble[id][mPotY];
			InfoMueble[clon][mPotZ] = InfoMueble[id][mPotZ];
			InfoMueble[clon][mRotX] = InfoMueble[id][mRotX];
			InfoMueble[clon][mRotY] = InfoMueble[id][mRotY];
			InfoMueble[clon][mRotZ] = InfoMueble[id][mRotZ];
			InfoMueble[clon][mInterior] = InfoMueble[id][mInterior];
			InfoMueble[clon][mVirtualWorld] = InfoMueble[id][mVirtualWorld];
			InfoMueble[clon][mPrecio] = InfoMueble[id][mPrecio];
			InfoMueble[clon][mPuerta] = InfoMueble[id][mPuerta];
			InfoMueble[clon][mTxtMaterial1] = InfoMueble[id][mTxtMaterial1];
			InfoMueble[clon][mTxtModelo1] = InfoMueble[id][mTxtModelo1];
			alm(InfoMueble[clon][mTxtNombre1], InfoMueble[id][mTxtNombre1]);
			alm(InfoMueble[clon][mTxtNombreTextura1], InfoMueble[id][mTxtNombreTextura1]);
			InfoMueble[clon][mTxtColor1] = InfoMueble[id][mTxtColor1];
			InfoMueble[clon][mTxtMaterial2] =  InfoMueble[id][mTxtMaterial2];
			InfoMueble[clon][mTxtModelo2] = InfoMueble[id][mTxtModelo2];
			alm(InfoMueble[clon][mTxtNombre2], InfoMueble[id][mTxtNombre2]);
			alm(InfoMueble[clon][mTxtNombreTextura2], InfoMueble[id][mTxtNombreTextura2]);
			InfoMueble[clon][mTxtColor2] = InfoMueble[id][mTxtColor2];
			InfoMueble[clon][mTxtMaterial3] = InfoMueble[id][mTxtMaterial3];
			InfoMueble[clon][mTxtModelo3] = InfoMueble[id][mTxtModelo3];
			alm(InfoMueble[clon][mTxtNombre3], InfoMueble[id][mTxtNombre3]);
			alm(InfoMueble[clon][mTxtNombreTextura3], InfoMueble[id][mTxtNombreTextura3]);
			InfoMueble[clon][mTxtColor3] = InfoMueble[id][mTxtColor3];
			InfoMueble[clon][mTxtMaterial4] = InfoMueble[id][mTxtMaterial4];
			InfoMueble[clon][mTxtModelo4] = InfoMueble[id][mTxtModelo4];
			alm(InfoMueble[clon][mTxtNombre4], InfoMueble[id][mTxtNombre4]);
			alm(InfoMueble[clon][mTxtNombreTextura4], InfoMueble[id][mTxtNombreTextura4]);
			InfoMueble[clon][mTxtColor4] = InfoMueble[id][mTxtColor4];
			InfoMueble[clon][mTxtMaterial5] = InfoMueble[id][mTxtMaterial5];
			InfoMueble[clon][mTxtModelo5] = InfoMueble[id][mTxtModelo5];
			alm(InfoMueble[clon][mTxtNombre5], InfoMueble[id][mTxtNombre5]);
			alm(InfoMueble[clon][mTxtNombreTextura5], InfoMueble[id][mTxtNombreTextura5]);
			InfoMueble[clon][mTxtColor5] = InfoMueble[id][mTxtColor5];
			//opción id por crear
			mysql_format(db_samp, query, sizeof query, "INSERT INTO muebles (Tipo, Propiedad, Modelo) VALUES ('%d', '%d', '%d')", InfoMueble[clon][mTipo], InfoMueble[clon][mPropiedad], InfoMueble[clon][mModelo]);
			mysql_tquery(db_samp, query, "OnCreateMueble", "i", 1);

			InfoMueble[clon][mObjeto] = CreateDynamicObject(InfoMueble[clon][mModelo], InfoMueble[clon][mPotX], InfoMueble[clon][mPotY], InfoMueble[clon][mPotZ], InfoMueble[clon][mRotX], InfoMueble[clon][mRotY], InfoMueble[clon][mRotZ], InfoMueble[clon][mVirtualWorld], InfoMueble[clon][mInterior]);

			if (InfoMueble[clon][mTxtModelo1] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial1], InfoMueble[clon][mTxtModelo1], InfoMueble[clon][mTxtNombre1], InfoMueble[clon][mTxtNombreTextura1], InfoMueble[clon][mTxtColor1]); }
			if (InfoMueble[clon][mTxtModelo2] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial2], InfoMueble[clon][mTxtModelo2], InfoMueble[clon][mTxtNombre2], InfoMueble[clon][mTxtNombreTextura2], InfoMueble[clon][mTxtColor2]); }
			if (InfoMueble[clon][mTxtModelo3] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial3], InfoMueble[clon][mTxtModelo3], InfoMueble[clon][mTxtNombre3], InfoMueble[clon][mTxtNombreTextura3], InfoMueble[clon][mTxtColor3]); }
			if (InfoMueble[clon][mTxtModelo4] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial4], InfoMueble[clon][mTxtModelo4], InfoMueble[clon][mTxtNombre4], InfoMueble[clon][mTxtNombreTextura4], InfoMueble[clon][mTxtColor4]); }
			if (InfoMueble[clon][mTxtModelo5] != 0) { SetDynamicObjectMaterial(InfoMueble[clon][mObjeto], InfoMueble[clon][mTxtMaterial5], InfoMueble[clon][mTxtModelo5], InfoMueble[clon][mTxtNombre5], InfoMueble[clon][mTxtNombreTextura5], InfoMueble[clon][mTxtColor5]); }

			InfoPersonaje[playerid][pEditingMode] = 55;
			EditDynamicObject(playerid, InfoMueble[clon][mObjeto]);
			edicion_sql_actual[playerid] = clon;
			SendPlayerChatMessage(playerid, COLOR_GREY, "Objeto duplicado, ya puedes editarlo.");
		}
		case 7:
		{
			format(gformat, sizeof gformat, "Borraste {b42d2d}%s{FFFFFF}.", InfoMueble[id][mNombre]);
			SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
			borrar_mueble(id);
		}
	}
	return 1;
}

Dialog:EditarTextura(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialogo_Editar_Mueble(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	switch (listitem)
	{
		case 0: //slot 1
		{
			Dialog_Show(playerid, Editar2Textura, DIALOG_STYLE_LIST, "SLOT 1", "Agregar color\nAgregar textura\nRemover texturas", "Continuar", "Volver");
			id_mueble_textura[playerid] = 0;
		}
		case 1: //slot 2
		{
			Dialog_Show(playerid, Editar2Textura, DIALOG_STYLE_LIST, "SLOT 2", "Agregar color\nAgregar textura\nRemover texturas", "Continuar", "Volver");
			id_mueble_textura[playerid] = 1;
		}
		case 2: //slot 3
		{
			Dialog_Show(playerid, Editar2Textura, DIALOG_STYLE_LIST, "SLOT 3", "Agregar color\nAgregar textura\nRemover texturas", "Continuar", "Volver");
			id_mueble_textura[playerid] = 2;
		}
		case 3: //slot 4
		{
			Dialog_Show(playerid, Editar2Textura, DIALOG_STYLE_LIST, "SLOT 4", "Agregar color\nAgregar textura\nRemover texturas", "Continuar", "Volver");
			id_mueble_textura[playerid] = 3;
		}
		case 4: //slot 5
		{
			Dialog_Show(playerid, Editar2Textura, DIALOG_STYLE_LIST, "SLOT 5", "Agregar color\nAgregar textura\nRemover texturas", "Continuar", "Volver");
			id_mueble_textura[playerid] = 4;
		}
		case 5: //remover todas las texturas del mueble
		{
			Dialog_Show(playerid, BorrarAllTextura, DIALOG_STYLE_MSGBOX, "Borrar texturas", "{EBEBEB}¿Estás seguro de borrar la texturas de este mueble?", "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:BorrarAllTextura(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], query[1000];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	new count = 0;
	if (InfoMueble[id][mTxtModelo1] != 0)
	{
	    count++;
		InfoMueble[id][mTxtMaterial1] = -1;
		InfoMueble[id][mTxtModelo1] = 0;
		alm(InfoMueble[id][mTxtNombre1], "none");
		alm(InfoMueble[id][mTxtNombreTextura1], "none");
		InfoMueble[id][mTxtColor1] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e', TxtColor1 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
		SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]);
	}
	if (InfoMueble[id][mTxtModelo2] != 0)
	{
	    count++;
		InfoMueble[id][mTxtMaterial2] = -1;
		InfoMueble[id][mTxtModelo2] = 0;
		alm(InfoMueble[id][mTxtNombre2], "none");
		alm(InfoMueble[id][mTxtNombreTextura2], "none");
		InfoMueble[id][mTxtColor2] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial2 = '%d', TxtModelo2 = '%d', TxtNombre2 = '%e', TxtNombreTextura2 = '%e', TxtColor2 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
		SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]);
	}
	if (InfoMueble[id][mTxtModelo3] != 0)
	{
	    count++;
		InfoMueble[id][mTxtMaterial3] = -1;
		InfoMueble[id][mTxtModelo3] = 0;
		alm(InfoMueble[id][mTxtNombre3], "none");
		alm(InfoMueble[id][mTxtNombreTextura3], "none");
		InfoMueble[id][mTxtColor3] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtNombre3 = '%e', TxtNombreTextura3 = '%e', TxtColor3 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
		SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]);
	}
	if (InfoMueble[id][mTxtModelo4] != 0)
	{
	    count++;
		InfoMueble[id][mTxtMaterial4] = -1;
		InfoMueble[id][mTxtModelo4] = 0;
		alm(InfoMueble[id][mTxtNombre4], "none");
		alm(InfoMueble[id][mTxtNombreTextura4], "none");
		InfoMueble[id][mTxtColor4] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtNombre4 = '%e', TxtNombreTextura4 = '%e', TxtColor4 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
		SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]);
	}
	if (InfoMueble[id][mTxtModelo5] != 0)
	{
	    count++;
		InfoMueble[id][mTxtMaterial5] = -1;
		InfoMueble[id][mTxtModelo5] = 0;
		alm(InfoMueble[id][mTxtNombre5], "none");
		alm(InfoMueble[id][mTxtNombreTextura5], "none");
		InfoMueble[id][mTxtColor5] = 0;
		mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre5 = '%e', TxtNombreTextura5 = '%e', TxtColor5 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mID_sql]);
		mysql_tquery(db_samp, query);
		SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]);
	}
	if (count != 0)
	{
		format(query, sizeof query, "Removiste {b42d2d}%d{FFFFFF} texturas del mueble seleccionado.", count);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, query);
	}
	else SendPlayerChatMessage(playerid, COLOR_GREY, "* El mueble seleccionado no tiene ninguna textura.");
	id_mueble_textura[playerid] = -1;
	is_mueble_actual[playerid] = 0;
	return 1;
}

Dialog:Editar2Textura(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	switch (listitem)
	{
		case 0:
		{
			new edit_color[] = "{FF0000}Rojo\n{00FF00}Verde\n{FFFF00}Amarillo\n{0080FF}Azul\n{FF8000}Naranja\n{000000}Negro\n{FFFFFF}Ninguno";
			Dialog_Show(playerid, EditarMuebleColor, DIALOG_STYLE_LIST, "Editar color", edit_color, "Continuar", "Volver");
		}
		case 1:
		{
			new show_dialog[1028];
			strcat(show_dialog, "Madera 1 (19375) (all_walls) (mp_furn_floor)\n");
			strcat(show_dialog, "Madera 2 (2030) (cj_tables) (cj_lightwood)\n");
			strcat(show_dialog, "Puerta 1 (1557) (dave_door_2b) (miragedoor1_256)\n");
			strcat(show_dialog, "Puerta 2 (1536) (ext_doors2) (CJ_WOODDOOR4)\n");
			strcat(show_dialog, "Piedra 1 (6134) (venice_law) (stonewall_la)\n");
			strcat(show_dialog, "Piedra 2 (4600) (theatrelan2) (gm_labuld2_b)\n");
			strcat(show_dialog, "Ladrillo 1 (11450) (des_nwtown) (des_brick1)\n");
			strcat(show_dialog, "Ladrillo 2 (8675) (wddngchpl02) (shingles6)\n");
			strcat(show_dialog, "Metálico 1 (1735) (cj_tv_stand) (cj_steel)\n");
			strcat(show_dialog, "Metálico 2 (10932) (station_sfse) (ws_stationfloor)\n");
			strcat(show_dialog, "Cuadriculado (16150) (ufo_bar) (dinerfloor01_128)\n");
			strcat(show_dialog, "Agua (3947) (rczero_track) (waterclear256)\n");
			strcat(show_dialog, "{F5DEB3}Colocar textura personalizada");
			Dialog_Show(playerid, AgregarTextura, DIALOG_STYLE_LIST, "Editar texturas", show_dialog, "Continuar", "Volver");
		}
		case 2:
		{
			new gformat[256];
			format(gformat, sizeof gformat, "{EBEBEB}¿Estás seguro de borrar la texturas slot {b42d2d}%d{EBEBEB}?", idtxt+1);
			Dialog_Show(playerid, BorrarXTextura, DIALOG_STYLE_MSGBOX, "Borrar texturas", gformat, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:BorrarXTextura(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid], query[1000];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	switch (idtxt)
	{
		case 0:
		{
			InfoMueble[id][mTxtMaterial1] = -1;
			InfoMueble[id][mTxtModelo1] = 0;
			alm(InfoMueble[id][mTxtNombre1], "none");
			alm(InfoMueble[id][mTxtNombreTextura1], "none");
			InfoMueble[id][mTxtColor1] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e', TxtColor1 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Removiste las textura del slot {b42d2d}%d", idtxt+1);
			SendPlayerChatMessage(playerid, COLOR_WHITE, query);
		}
		case 1:
		{
			InfoMueble[id][mTxtMaterial2] = -1;
			InfoMueble[id][mTxtModelo2] = 0;
			alm(InfoMueble[id][mTxtNombre2], "none");
			alm(InfoMueble[id][mTxtNombreTextura2], "none");
			InfoMueble[id][mTxtColor2] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial2 = '%d', TxtModelo2 = '%d', TxtNombre2 = '%e', TxtNombreTextura2 = '%e', TxtColor2 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Removiste las textura del slot {b42d2d}%d", idtxt+1);
			SendPlayerChatMessage(playerid, COLOR_WHITE, query);
		}
		case 2:
		{
			InfoMueble[id][mTxtMaterial3] = -1;
			InfoMueble[id][mTxtModelo3] = 0;
			alm(InfoMueble[id][mTxtNombre3], "none");
			alm(InfoMueble[id][mTxtNombreTextura3], "none");
			InfoMueble[id][mTxtColor3] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtNombre3 = '%e', TxtNombreTextura3 = '%e', TxtColor3 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Removiste las textura del slot {b42d2d}%d", idtxt+1);
			SendPlayerChatMessage(playerid, COLOR_WHITE, query);
		}
		case 3:
		{
			InfoMueble[id][mTxtMaterial4] = -1;
			InfoMueble[id][mTxtModelo4] = 0;
			alm(InfoMueble[id][mTxtNombre4], "none");
			alm(InfoMueble[id][mTxtNombreTextura4], "none");
			InfoMueble[id][mTxtColor4] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtNombre4 = '%e', TxtNombreTextura4 = '%e', TxtColor4 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Removiste las textura del slot {b42d2d}%d", idtxt+1);
			SendPlayerChatMessage(playerid, COLOR_WHITE, query);
		}
		case 4:
		{
			InfoMueble[id][mTxtMaterial5] = -1;
			InfoMueble[id][mTxtModelo5] = 0;
			alm(InfoMueble[id][mTxtNombre5], "none");
			alm(InfoMueble[id][mTxtNombreTextura5], "none");
			InfoMueble[id][mTxtColor5] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre5 = '%e', TxtNombreTextura5 = '%e', TxtColor5 = 0 WHERE ID = '%d'", InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Removiste las textura del slot {b42d2d}%d", idtxt+1);
			SendPlayerChatMessage(playerid, COLOR_WHITE, query);
		}
	}
	return 1;
}

new model_textura_actual[MAX_PLAYERS];
new txd_name_actual[MAX_PLAYERS][128];

Dialog:AgregarTextura(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	new model_texture = 0, name_txd[128], nombre_texture[128], query[1000];
	switch (listitem)
	{
		case 0: { model_texture = 19375; name_txd = "all_walls"; nombre_texture = "mp_furn_floor"; }
		case 1: { model_texture = 2030; name_txd = "cj_tables"; nombre_texture = "cj_lightwood"; }
		case 2: { model_texture = 1557; name_txd = "dave_door_2b"; nombre_texture = "miragedoor1_256"; }
		case 3: { model_texture = 1536; name_txd = "ext_doors2"; nombre_texture = "CJ_WOODDOOR4"; }
		case 4: { model_texture = 6134; name_txd = "venice_law"; nombre_texture = "stonewall_la"; }
		case 5: { model_texture = 4600; name_txd = "theatrelan2"; nombre_texture = "gm_labuld2_b"; }
		case 6: { model_texture = 11450; name_txd = "des_nwtown"; nombre_texture = "des_brick1"; }
		case 7: { model_texture = 8675; name_txd = "wddngchpl02"; nombre_texture = "shingles6"; }
		case 8: { model_texture = 1735; name_txd = "cj_tv_stand"; nombre_texture = "cj_steel"; }
		case 9: { model_texture = 10932; name_txd = "station_sfse"; nombre_texture = "ws_stationfloor"; }
		case 10: { model_texture = 16150; name_txd = "ufo_bar"; nombre_texture = "dinerfloor01_128"; }
		case 11: { model_texture = 3947; name_txd = "rczero_track"; nombre_texture = "waterclear256"; }
		case 12: // personalizado
		{
			Dialog_Show(playerid, PzTxdModelo, DIALOG_STYLE_INPUT, "Paso 1: Model ID", "{EBEBEB}Primero debes colocar el ModelID (Ej: 8565)", "Continuar", "Salir");
			return 1;
		}
	}
	switch (idtxt)
	{
		case 0:
		{
			InfoMueble[id][mTxtMaterial1] = 0;
			InfoMueble[id][mTxtModelo1] = model_texture;
			alm(InfoMueble[id][mTxtNombre1], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura1], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 1:
		{
			InfoMueble[id][mTxtMaterial2] = 1;
			InfoMueble[id][mTxtModelo2] = model_texture;
			alm(InfoMueble[id][mTxtNombre2], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura2], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial2 = '%d', TxtModelo2 = '%d', TxtNombre2 = '%e', TxtNombreTextura2 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 2:
		{
			InfoMueble[id][mTxtMaterial3] = 2;
			InfoMueble[id][mTxtModelo3] = model_texture;
			alm(InfoMueble[id][mTxtNombre3], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura3], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtNombre3 = '%e', TxtNombreTextura3 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 3:
		{
			InfoMueble[id][mTxtMaterial4] = 3;
			InfoMueble[id][mTxtModelo4] = model_texture;
			alm(InfoMueble[id][mTxtNombre4], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura4], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtNombre4 = '%e', TxtNombreTextura4 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 4:
		{
			InfoMueble[id][mTxtMaterial5] = 4;
			InfoMueble[id][mTxtModelo5] = model_texture;
			alm(InfoMueble[id][mTxtNombre5], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura5], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre5 = '%e', TxtNombreTextura5 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
	}
	return 1;
}

Dialog:PzTxdModelo(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	if (!isnumeric(inputtext))
	{
		Dialog_Show(playerid, PzTxdModelo, DIALOG_STYLE_INPUT, "Paso 1: Model ID", "{EBEBEB}Primero debes colocar el ModelID (Ej: 8565)", "Continuar", "Salir");
		return SendPlayerChatMessage(playerid, COLOR_GREY, "* El modelo debe ser únicamente en números.");
	}
	if (strval(inputtext) < 700 || strval(inputtext) > 19000)
	{
		Dialog_Show(playerid, PzTxdModelo, DIALOG_STYLE_INPUT, "Paso 1: Model ID", "{EBEBEB}Primero debes colocar el ModelID (Ej: 8565)", "Continuar", "Salir");
		return SendPlayerChatMessage(playerid, COLOR_GREY, "* El modelo ingresado es inválido.");
	}
	model_textura_actual[playerid] = strval(inputtext);
	Dialog_Show(playerid, PzTxdName, DIALOG_STYLE_INPUT, "Paso 2: TXD Name", "{EBEBEB}Segundo debes colocar es TXDName (Ej: vgsebuild01)", "Continuar", "Volver");
	return 1;
}

Dialog:PzTxdName(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Show(playerid, PzTxdModelo, DIALOG_STYLE_INPUT, "Paso 1: Model ID", "{EBEBEB}Primero debes colocar el ModelID (Ej: 8565)", "Continuar", "Salir");
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");

	alm(txd_name_actual[playerid], inputtext);
	Dialog_Show(playerid, PzTxdNameTxt, DIALOG_STYLE_INPUT, "Paso 3: Texture Name", "{EBEBEB}Tercero que debes colocar es TextureName (Ej: ws_stonewall)", "Continuar", "Salir");
	return 1;
}

Dialog:PzTxdNameTxt(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Show(playerid, PzTxdName, DIALOG_STYLE_INPUT, "Paso 2: TXD Name", "{EBEBEB}Segundo debes colocar es TXDName (Ej: vgsebuild01)", "Continuar", "Volver");
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");

 	new model_texture = model_textura_actual[playerid], name_txd[128], nombre_texture[128], query[1000];
	alm(name_txd, txd_name_actual[playerid]);
	alm(nombre_texture, inputtext);
	switch (idtxt)
	{
		case 0:
		{
			InfoMueble[id][mTxtMaterial1] = 0;
			InfoMueble[id][mTxtModelo1] = model_texture;
			alm(InfoMueble[id][mTxtNombre1], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura1], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 1:
		{
			InfoMueble[id][mTxtMaterial2] = 1;
			InfoMueble[id][mTxtModelo2] = model_texture;
			alm(InfoMueble[id][mTxtNombre2], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura2], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial2 = '%d', TxtModelo2 = '%d', TxtNombre2 = '%e', TxtNombreTextura2 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 2:
		{
			InfoMueble[id][mTxtMaterial3] = 2;
			InfoMueble[id][mTxtModelo3] = model_texture;
			alm(InfoMueble[id][mTxtNombre3], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura3], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtNombre3 = '%e', TxtNombreTextura3 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 3:
		{
			InfoMueble[id][mTxtMaterial4] = 3;
			InfoMueble[id][mTxtModelo4] = model_texture;
			alm(InfoMueble[id][mTxtNombre4], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura4], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtNombre4 = '%e', TxtNombreTextura4 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
		case 4:
		{
			InfoMueble[id][mTxtMaterial5] = 4;
			InfoMueble[id][mTxtModelo5] = model_texture;
			alm(InfoMueble[id][mTxtNombre5], name_txd);
			alm(InfoMueble[id][mTxtNombreTextura5], nombre_texture);
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre5 = '%e', TxtNombreTextura5 = '%e' WHERE ID = '%d'", InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "[Slot textura: %d] [ID Modelo: %d] [Nombre TXD: %s] [Nombre textura: %s]", idtxt+1, model_texture, name_txd, nombre_texture);
			SendPlayerChatMessage(playerid, COLOR_GREY, query);
		}
	}
	return 1;
}

Dialog:EditarMuebleColor(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], idtxt = id_mueble_textura[playerid];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (idtxt == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la selección de slot para texturizar.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialog_Editar_Textura(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	new colortexture = 0, name_color_m[32], query[256];
	switch (listitem)
	{
		case 0: colortexture = 0xFFFF0000, name_color_m = "Rojo";
		case 1: colortexture = 0xFF00FF00, name_color_m = "Verde";
		case 2: colortexture = 0xFFFFFF00, name_color_m = "Amarillo";
		case 3: colortexture = 0xFF0080FF, name_color_m = "Azul";
		case 4: colortexture = 0xFFFF8000, name_color_m = "Naranja";
		case 5: colortexture = 0xFF000000, name_color_m = "Negro";
		case 6: colortexture = 0, name_color_m = "Ninguno";
	}
	switch (idtxt)
	{
		case 0:
		{
			if (InfoMueble[id][mTxtModelo1] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes agregar una textura antes de elegir un color, slot 1.");
			InfoMueble[id][mTxtColor1] = colortexture;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtColor1 = '%d' WHERE ID = '%d'", InfoMueble[id][mTxtColor1], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial1], InfoMueble[id][mTxtModelo1], InfoMueble[id][mTxtNombre1], InfoMueble[id][mTxtNombreTextura1], InfoMueble[id][mTxtColor1]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Color %s de la textura %d.", name_color_m, idtxt+1);
			SendPlayerChatMessage(playerid, colortexture, query);
		}
		case 1:
		{
			if (InfoMueble[id][mTxtModelo2] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes agregar una textura antes de elegir un color, slot 2.");
			InfoMueble[id][mTxtColor2] = colortexture;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtColor2 = '%d' WHERE ID = '%d'", InfoMueble[id][mTxtColor2], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial2], InfoMueble[id][mTxtModelo2], InfoMueble[id][mTxtNombre2], InfoMueble[id][mTxtNombreTextura2], InfoMueble[id][mTxtColor2]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Color %s de la textura %d.", name_color_m, idtxt+1);
			SendPlayerChatMessage(playerid, colortexture, query);
		}
		case 2:
		{
			if (InfoMueble[id][mTxtModelo3] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes agregar una textura antes de elegir un color, slot 3.");
			InfoMueble[id][mTxtColor3] = colortexture;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtColor3 = '%d' WHERE ID = '%d'", InfoMueble[id][mTxtColor3], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial3], InfoMueble[id][mTxtModelo3], InfoMueble[id][mTxtNombre3], InfoMueble[id][mTxtNombreTextura3], InfoMueble[id][mTxtColor3]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Color %s de la textura %d.", name_color_m, idtxt+1);
			SendPlayerChatMessage(playerid, colortexture, query);
		}
		case 3:
		{
			if (InfoMueble[id][mTxtModelo4] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes agregar una textura antes de elegir un color, slot 4.");
			InfoMueble[id][mTxtColor4] = colortexture;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtColor4 = '%d' WHERE ID = '%d'", InfoMueble[id][mTxtColor4], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial4], InfoMueble[id][mTxtModelo4], InfoMueble[id][mTxtNombre4], InfoMueble[id][mTxtNombreTextura4], InfoMueble[id][mTxtColor4]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Color %s de la textura %d.", name_color_m, idtxt+1);
			SendPlayerChatMessage(playerid, colortexture, query);
		}
		case 4:
		{
			if (InfoMueble[id][mTxtModelo5] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes agregar una textura antes de elegir un color, slot 5.");
			InfoMueble[id][mTxtColor5] = colortexture;
			mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET TxtColor5 = '%d' WHERE ID = '%d'", InfoMueble[id][mTxtColor5], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, query);
			SetDynamicObjectMaterial(InfoMueble[id][mObjeto], InfoMueble[id][mTxtMaterial5], InfoMueble[id][mTxtModelo5], InfoMueble[id][mTxtNombre5], InfoMueble[id][mTxtNombreTextura5], InfoMueble[id][mTxtColor5]);
			id_mueble_textura[playerid] = -1;
			is_mueble_actual[playerid] = 0;
			format(query, sizeof query, "Color %s de la textura %d.", name_color_m, idtxt+1);
			SendPlayerChatMessage(playerid, colortexture, query);
		}
	}
	return 1;
}

Dialog:GirarMueble(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], query[512];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialogo_Editar_Mueble(playerid, id);
	if (InfoMueble[id][mInterior] == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese mueble está oculto o no lo has agregado.");
	new Float: grados = 0.0;
	switch (listitem)
	{
		case 0:
		{
		    if (InfoMueble[id][mRotZ] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El mueble ya está en 0 grados.");
			grados = 0.0;
		}
		case 1:
		{
		    if (InfoMueble[id][mRotZ] == 90.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El mueble ya está en 90 grados.");
			grados = 90.0;
		}
		case 2:
		{
		    if (InfoMueble[id][mRotZ] == 180.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El mueble ya está en 180 grados.");
			grados = 180.0;
		}
		case 3:
		{
		    if (InfoMueble[id][mRotZ] == 270.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El mueble ya está en 270 grados.");
			grados = 270.0;
		}
	}
	format(query, sizeof query, "Giraste %s %0.f grados.", InfoMueble[id][mNombre], grados);
	SendPlayerChatMessage(playerid, COLOR_GREY, query);
	GetDynamicObjectRot(InfoMueble[id][mObjeto], InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
	InfoMueble[id][mRotZ] = grados;
	SetDynamicObjectRot(InfoMueble[id][mObjeto], InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
	mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET RotX = '%f', RotY = '%f', RotZ = '%f' WHERE ID = '%d'", InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mID_sql]);
	mysql_tquery(db_samp, query);
	return 1;
}

Dialog:ChangeMuebleName(playerid, response, listitem, inputtext[])
{
	new id = is_mueble_actual[playerid], query[512];
	if (check_id_prop_mueble(playerid) == -1) return pc_cmd_muebles(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (InfoMueble[id][mVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Has seleccionado un slot sin mueble.");
	if (!response) return Dialogo_Editar_Mueble(playerid, id);
	if (strlen(inputtext) > 32 || strlen(inputtext) < 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes poner más de 32 carácteres para renombrar."); return 1; }
	alm(InfoMueble[id][mNombre], inputtext);
	format(query, sizeof query, "Nuevo nombre del mueble: {D1C231}%s", InfoMueble[id][mNombre]);
	SendPlayerChatMessage(playerid, -1, query);
	mysql_format(db_samp, query, sizeof query, "UPDATE muebles SET Nombre = '%e' WHERE ID = '%d'", InfoMueble[id][mNombre], InfoMueble[id][mID_sql]);
	mysql_tquery(db_samp, query);
	is_mueble_actual[playerid] = 0;
	return 1;
}

Dialog:Comprar2Muebles(playerid, response, listitem, inputtext[])
{
	new tipo = 0, id_propiedad = -1;
	new modelid = MuebleActual[playerid], OBJ_INDEX;
	if (DentroCasa[playerid] != -1) { tipo = 1; id_propiedad = DentroCasa[playerid]; }
	if (DentroNegocio[playerid] != -1) { tipo = 2; id_propiedad = DentroNegocio[playerid]; }
	//inicio
	if (!response)
	{
		MuebleActual[playerid] = 0;
		pc_cmd_muebles(playerid);
		return 1;
	}
	if (modelid == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ocurrió un error con la compra de muebles (2) contacta con el programador.");
	buscar_modelo_obj(modelid, OBJ_INDEX);
	Adquirir_mueble(playerid, tipo, modelid, objetos_interior[OBJ_INDEX][1], id_propiedad);
	return 1;
}