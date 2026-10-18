Label_contenedor(id, type)
{
	//info new
	new cont_label[470];
	format(cont_label, sizeof cont_label, "{EBEBEB}Contenedor de Basura {F5DEB3}%d\n{EBEBEB}Aquí puedes usar {F5DEB3}/contenedor{EBEBEB} para revisar el contenedor.", id);
	if (type == 1)
	{
		if (IsValidDynamicObject(InfoContenedor[id][contObject])) DestroyDynamicObject(InfoContenedor[id][contObject]);
		InfoContenedor[id][contObject] = 0;
		if (IsValidDynamic3DTextLabel(InfoContenedor[id][contLabel]))
		{
			DestroyDynamic3DTextLabel(InfoContenedor[id][contLabel]);
			InfoContenedor[id][contLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoContenedor[id][contObject] = CreateDynamicObject(InfoContenedor[id][contModelo], InfoContenedor[id][contPotX], InfoContenedor[id][contPotY], InfoContenedor[id][contPotZ], InfoContenedor[id][contRotX], InfoContenedor[id][contRotY], InfoContenedor[id][contRotZ], .interiorid = InfoContenedor[id][contInterior], .worldid = InfoContenedor[id][contVirtualWorld]);
		InfoContenedor[id][contLabel] = CreateDynamic3DTextLabel(cont_label, -1, InfoContenedor[id][contPotX], InfoContenedor[id][contPotY], InfoContenedor[id][contPotZ] + 0.4, 8.0, .interiorid = InfoContenedor[id][contInterior], .worldid = InfoContenedor[id][contVirtualWorld]);

	}
	else UpdateDynamic3DTextLabelText(InfoContenedor[id][contLabel], -1, cont_label);
}

CheckContenedores()
{
	new countC = 0;
	Loop(id, totalcontenedores, 1) if (InfoContenedor[id][contPotX] != 0.0)
	{
	    Loop(slot, 10, 0) if (InfoContenedor[id][cInv][slot] != 0)
	    {
	        countC++;
	        //limpiar contenedores
		    InfoContenedor[id][cInv][slot] = 0;
			InfoContenedor[id][cInvCant][slot] = 0;
		}
	}
	printf("Contenedores: Se limpiaron %d contenedores.", countC);
	return 1;
}

stock TirarObjContenedor(playerid, contenedorid, mano)
{
	new string[128];
	ActualizarManos(playerid);
	if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando en esta situación.");
	new id = -1;
	for(new i = 0; i < MAX_CONTENEDORES; i++)
	{
		if(InfoContenedor[contenedorid][cInv][i] == 0) { id = i; break; }
	}
	if(id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay espacio en éste contenedor, busque otro u tire el objeto al piso.");

	switch(mano)
	{
	    case 1:
	    {
			new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoDerCant = InfoPersonaje[playerid][pManoDerechaCant];

			format(string, sizeof(string), "Tiraste tu %s dentro del contenedor.", InfoInventario[ManoDer][NombreObjeto]);
			SendPlayerChatMessage(playerid, 0x828BFDFF, string);
			format(string, sizeof(string), "tira su %s dentro del contenedor.", InfoInventario[ManoDer][NombreObjeto]);
			rol_ame(playerid, string);
			ResetPlayerWeapons(playerid);
			InfoPersonaje[playerid][pManoDerecha] = 0;
			InfoPersonaje[playerid][pManoDerechaCant] = 0;
			RemovePlayerAttachedObject(playerid, 7);
			InfoContenedor[contenedorid][cInv][id] = ManoDer;
			InfoContenedor[contenedorid][cInvCant][id] = ManoDerCant;
			return 1;
		}
		case 2:
		{
			new ManoDer = InfoPersonaje[playerid][pManoIzquierda], ManoDerCant = InfoPersonaje[playerid][pManoIzquierdaCant];

			format(string, sizeof(string), "Tiraste tu %s dentro del contenedor.", InfoInventario[ManoDer][NombreObjeto]);
			SendPlayerChatMessage(playerid, 0x828BFDFF, string);
			format(string, sizeof(string), "tira su %s dentro del contenedor.", InfoInventario[ManoDer][NombreObjeto]);
			rol_ame(playerid, string);
			ResetPlayerWeapons(playerid);
			InfoPersonaje[playerid][pManoIzquierda] = 0;
			InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
			RemovePlayerAttachedObject(playerid, 8);
			InfoContenedor[contenedorid][cInv][id] = ManoDer;
			InfoContenedor[contenedorid][cInvCant][id] = ManoDerCant;
			return 1;
		}
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "No posees ningún objeto en tus manos.");
	return 1;
}