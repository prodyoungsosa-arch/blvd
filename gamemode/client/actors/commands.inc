//Administrativo
cmd:iractor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new id;
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Uso: /iractor (ActorID)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado. ID erronéo.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no creado, créalo antes.");
	SetPosEx(playerid, InfoActor[id][aPosX], InfoActor[id][aPosY], InfoActor[id][aPosZ], InfoActor[id][aPosR], InfoActor[id][aInterior], InfoActor[id][aVirtualWorld], 1);
	GameTextForPlayer(playerid, "~w~Teletransportado", 5000, 1);
	return 1;
}

cmd:crearactor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new skin, nombre[24], gformat[210];
	if (sscanf(params, "ds[24]", skin, nombre)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Uso: /crearactor (SkinID) (Nombre)");
	if (IsValidSkin(skin) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes de escoger una id de skin entre 1 y 311.");
	if (strlen(nombre) > 24 || strlen(nombre) < 0) { SendPlayerChatMessage(playerid, -1, "Solo puedes escribir menos de 24 caracteres."); return 1; }
	Loop(id, MAX_ACTORES, 1) if (InfoActor[id][aPosX] == 0)
	{
		GetPlayerPos(playerid, InfoActor[id][aPosX], InfoActor[id][aPosY], InfoActor[id][aPosZ]);
		GetPlayerFacingAngle(playerid, InfoActor[id][aPosR]);
		InfoActor[id][aVirtualWorld] = GetPlayerVirtualWorld(playerid);
		InfoActor[id][aInterior] = GetPlayerInterior(playerid);
		InfoActor[id][aSkin] = skin;
		alm(InfoActor[id][aNombre], nombre);
		format(gformat, sizeof gformat, "Actor %d - Nombre: %s - Skin: %d.", id, nombre, skin);
		SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
		Dynamic_actor(id);
		new query[1500];
		//opcion idsql ya creada.
		if (InfoActor[id][aID_sql] != 0)
		{
			mysql_format(db_samp, query, sizeof query, "UPDATE actores SET Nombre = '%e', Skin = '%d', PosX = '%f', PosY = '%f', PosZ = '%f', PosR = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoActor[id][aNombre],
			InfoActor[id][aSkin],
			InfoActor[id][aPosX],
			InfoActor[id][aPosY],
			InfoActor[id][aPosZ],
			InfoActor[id][aPosR],
			InfoActor[id][aInterior],
			InfoActor[id][aVirtualWorld],
			InfoActor[id][aID_sql]);
			mysql_tquery(db_samp, query);
			id = MAX_ACTORES;
			return 1;
		}
		mysql_format(db_samp, query, sizeof query, "INSERT INTO actores (Nombre, Skin, PosX, PosY, PosZ, PosR, Interior, VirtualWorld) VALUES ('%e', '%d', '%f',  '%f', '%f', '%f', '%d', '%d')",
		InfoActor[id][aNombre],
		InfoActor[id][aSkin],
		InfoActor[id][aPosX],
		InfoActor[id][aPosY],
		InfoActor[id][aPosZ],
		InfoActor[id][aPosR],
		InfoActor[id][aInterior],
		InfoActor[id][aVirtualWorld]);
		mysql_tquery(db_samp, query, "OnActorCreate", "i", id);
		id = MAX_ACTORES;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_RED, "Se alcanzo el maximo de actores (100)");
	return 1;
}


cmd:borraractor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, gformat[235], query[1028];
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /borraractor (ActorID)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese actor no existe.");

	if (IsValidDynamic3DTextLabel(InfoActor[id][aLabel]))
	{
		DestroyDynamic3DTextLabel(InfoActor[id][aLabel]);
		InfoActor[id][aLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	DestroyDynamicActor(InfoActor[id][aID_ig]);

	alm(InfoActor[id][aNombre], "ninguno");
	InfoActor[id][aSkin] = -1;
	InfoActor[id][aPosX] = 0.0;
	InfoActor[id][aPosY] = 0.0;
	InfoActor[id][aPosZ] = 0.0;
	InfoActor[id][aPosR] = 0.0;
	InfoActor[id][aInterior] = 0;
	InfoActor[id][aVirtualWorld] = 0;
	InfoActor[id][aAnimacion] = 0;

	mysql_format(db_samp, query, sizeof query, "UPDATE actores SET Nombre = '%e', Skin = 0, PosX = 0.0, PosY = 0.0, PosZ = 0.0, PosR = 0.0, Interior = 0, VirtualWorld = 0, Animacion = 0 WHERE ID = '%d'", InfoActor[id][aNombre], InfoActor[id][aID_sql]);
	mysql_tquery(db_samp, query);
	//mensaje
	format(gformat, sizeof gformat, "Borraste el acctor ID %d, SQL vacía: %d", id, InfoActor[id][aID_sql]);
	SendPlayerChatMessage(playerid, -1, gformat);
	return 1;
}

cmd:skinactor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, skin, gformat[235];
	if (sscanf(params, "dd", id, skin)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /skinactor (ActorID) (SkinID)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese actor no existe.");
	if (IsValidSkin(skin) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes de escoger una id de skin entre 1 y 311.");
	InfoActor[id][aSkin] = skin;
	Dynamic_actor(id);
	guardar_int_mysql("actores", "Skin", InfoActor[id][aID_sql], InfoActor[id][aSkin]);
	format(gformat, sizeof gformat, "Actor %d - Skin: %d.", id, skin);
	SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
	Streamer_Update(playerid);
	return 1;
}

cmd:tipoactor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, tipo, gformat[235];
	if (sscanf(params, "dd", id, tipo)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /tipoactor (ActorID) (Tipos | 1 - NPC, 2 Traficante)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese actor no existe.");
	if(tipo < 1 || tipo > 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes escoger uno de los tipos");
	InfoActor[id][aTipo] = tipo;
	Dynamic_actor(id);
	guardar_int_mysql("actores", "Tipo", InfoActor[id][aID_sql], InfoActor[id][aTipo]);
	format(gformat, sizeof gformat, "Actor %d - tipo: %d.", id, tipo);
	SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
	Streamer_Update(playerid);
	return 1;
}

cmd:animactor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, anim, gformat[235];
	if (sscanf(params, "dd", id, anim)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /animactor (ActorID) (AnimacionID)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese actor no existe.");
	if (anim < 0 || anim > 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "Anim erronéa: 0 - 10 Animacion | ID 0 deja el Actor en estado Off.");
	InfoActor[id][aAnimacion] = anim;
	if (anim == 0) ClearDynamicActorAnimations(InfoActor[id][aID_ig]);
	else Animacion_actor(id);
	guardar_int_mysql("actores", "Animacion", InfoActor[id][aID_sql], InfoActor[id][aAnimacion]);
	format(gformat, sizeof gformat, "Actor %d - Animacion: %d.", id, anim);
	SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
	Streamer_Update(playerid);
	return 1;
}

cmd:nombreactor(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id, doorname[24], gformat[235];
	if (sscanf(params, "ds[24]", id, doorname)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /nombreactor (ActorID) (Nombre)");
	if (id < 1 || id > totalactores) return SendPlayerChatMessage(playerid, COLOR_GREY, "Actor no encontrado.");
	if (InfoActor[id][aPosX] == 0.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese actor no existe.");
	if (strlen(doorname) > 23 || strlen(doorname) < 0) { SendPlayerChatMessage(playerid, -1, "Solo puedes escribir menos de 24 caracteres."); return 1; }
	alm(InfoActor[id][aNombre], doorname);
	Dynamic_actor(id);
	format(gformat, sizeof gformat, "Actor %d - Nombre: %s.", id, doorname);
	SendPlayerChatMessage(playerid, 0x90C3D4FF, gformat);
	guardar_string_mysql("actores", "Nombre", InfoActor[id][aID_sql], InfoActor[id][aNombre]);
	Streamer_Update(playerid);
	return 1;
}