#define Compra_Toy 760

enum ToyEnum
{
	accModelo,
	accPrecio,
	accNombre[66],
	accTipo,
};

new InfoToy[][ToyEnum] =
{
	{11745, 4, "Bolso", 1},
	{19610, 4, "Microfono", 1},
	{19559, 4, "Mochila", 1},
	{19878, 2, "Skate", 3},
	{19591, 1, "Abanico", 3},
	{18952, 5, "Casco de boxeo", 1},
	{19555, 4, "Guante izquierdo", 1},
	{19556, 4, "Guante derecho", 1},
	{19631, 2, "Martillo", 1},
	{19626, 2, "Pala", 1},
	{19623, 20, "Cámara de fotos", 1},
	{19893, 60, "Computador portatil", 3},
	{19942, 4, "Radio portatil", 1},
	{19904, 15, "Chaleco naranja", 1},
	{2706, 7, "Camisa roja", 3},
	{19086, 25, "Dildo grande", 3},
	{19528, 19, "Gorro bruja", 3},
	{19141, 10, "Casco SWAT", 2},
	{19142, 10, "Chaleco SWAT", 2},
	{19777, 2, "Parche FBI", 2},
	{18636, 10, "Gorra de policía", 2},
	{19099, 10, "Sombrero de policía", 2},
	{18637, 20, "Escudo de policía", 2},
	{19200, 6, "Casco de policía", 2},
	{19138, 4, "Lentes de policía", 2},
	{18633, 2, "Llave inglesa", 1},
	{18634, 3, "Palanca", 1},
	{18635, 1, "Martillo", 1},
	{18638, 3, "Casco de minero", 1},
	{19093, 3, "Casco dude", 1},
	{18639, 3, "Sombrero negro", 1},
	{18640, 1, "Peluca 1", 1},
	{18975, 1, "Peluca 2", 1},
	{19136, 1, "Peluca 3", 1},
	{19274, 1, "Peluca 4", 1},
	{19516, 1, "Peluca 5", 1},
	{19517, 1, "Peluca 6", 1},
	{19518, 1, "Peluca 7", 1},
	{19519, 1, "Peluca 8", 1},
	{18641, 4, "Linterna", 1},
	{18644, 2, "Destornillador", 1},
	{18874, 20, "Teléfono", 1},
	{18890, 4, "Rastrillo", 1},
	{18891, 3, "Bandana 1", 1},
	{18892, 3, "Bandana 2", 1},
	{18893, 3, "Bandana 3", 1},
	{18894, 3, "Bandana 4", 1},
	{18895, 3, "Bandana 5", 1},
	{18896, 3, "Bandana 6", 1},
	{18897, 3, "Bandana 7", 1},
	{18898, 3, "Bandana 8", 1},
	{18899, 3, "Bandana 9", 1},
	{18900, 3, "Bandana 10", 1},
	{18901, 3, "Bandana 11", 1},
	{18902, 3, "Bandana 12", 1},
	{18903, 3, "Bandana 13", 1},
	{18904, 3, "Bandana 14", 1},
	{18905, 3, "Bandana 15", 1},
	{18906, 3, "Bandana 16", 1},
	{18907, 3, "Bandana 17", 1},
	{18908, 3, "Bandana 18", 1},
	{18909, 3, "Bandana 19", 1},
	{18910, 3, "Bandana 20", 1},
	{18911, 3, "Bandana 22", 1},
	{18912, 3, "Bandana 23", 1},
	{18913, 3, "Bandana 24", 1},
	{18914, 3, "Bandana 25", 1},
	{18915, 3, "Bandana 26", 1},
	{18916, 3, "Bandana 27", 1},
	{18917, 3, "Bandana 28", 1},
	{18918, 3, "Bandana 29", 1},
	{18919, 3, "Bandana 30", 1},
	{18920, 3, "Bandana 31", 1},
	{18921, 5, "Boina negra"},
	{18922, 5, "Boina roja"},
	{18923, 7, "Boina azul"},
	{18924, 8, "Boina guerra"},
	{18925, 8, "Boina francia"},
	{18941, 4, "Gorra negra", 1},
	{18961, 5, "Gorra camionero", 1},
	{19469, 2, "Cinta blanca", 1},
	{19330, 7, "Casco de bombero", 1},
	{19331, 7, "Casco de bombero 2", 1},
	{18974, 22, "Máscara de zorro", 3},
	{18645, 15, "Casco roja", 3},
	{18976, 14, "Casco azul", 3},
	{18978, 14, "Casco blanco", 1},
	{19006, 2, "Gafas roja", 1},
	{19007, 2, "Gafas amarilla", 1},
	{19008, 2, "Gafas verde", 1},
	{19009, 2, "Gafas azul", 1},
	{19010, 2, "Gafas porpura", 1},
	{19011, 2, "Gafas manipulador", 1},
	{19012, 2, "Gafas negra", 1},
	{19013, 2, "Gafas ojo", 1},
	{19014, 2, "Gafas carrera", 1},
	{19015, 2, "Gafas blanca", 1},
	{19016, 2, "Gafas vision", 1},
	{19017, 3, "Lentes amarillo", 1},
	{19018, 3, "Lentes naranja", 1},
	{19019, 3, "Lentes rosa", 1},
	{19020, 3, "Lentes celeste", 1},
	{19021, 3, "Lentes verde", 1},
	{19022, 4, "Gafas R negro", 1},
	{19023, 4, "Gafas R azul", 1},
	{19024, 4, "Gafas R porpura", 1},
	{19025, 4, "Gafas R rosa", 1},
	{19026, 4, "Gafas R rojo", 1},
	{19027, 4, "Gafas R naranja", 1},
	{19028, 4, "Gafas R amarillo", 1},
	{19029, 4, "Gafas R verde", 1},
	{19030, 3, "Lentes N marron", 1},
	{19031, 3, "Lentes N amarillo", 1},
	{19032, 3, "Lentes N rojo", 1},
	{19033, 3, "Lentes N negro", 1},
	{19034, 3, "Lentes N carrera", 1},
	{19035, 3, "Lentes N azul", 1},
	{19036, 12, "Máscara de terror", 1},
	{19039, 40, "Reloj oro", 1},
	{19040, 25, "Reloj plata", 1},
	{19041, 12, "Reloj cobre", 1},
	{19042, 45, "Reloj oro 2", 1},
	{19043, 29, "Reloj plata 2", 1},
	{19044, 9, "Reloj morado", 1},
	{19045, 9, "Reloj rosa", 1},
	{19046, 9, "Reloj verde", 1},
	{19047, 9, "Reloj azul", 1},
	{19048, 9, "Reloj azul negro", 1},
	{19049, 60, "Reloj floriado", 1},
	{19050, 9, "Reloj azul celeste", 1},
	{19051, 9, "Reloj naranja negro", 1},
	{19052, 9, "Reloj rosa naranja", 1},
	{19053, 9, "Reloj militar", 1},
	{19064, 12, "Gorro de santa normal", 1},
	{19065, 20, "Gorro de santa MXMas", 3},
	{19066, 30, "Gorro de santa HXMas", 3},
	{19078, 5, "Loro", 3},
	{19085, 2, "Parche de ojo", 1},
	{19163, 40, "Máscara de CJ", 3},
	{19317, 10, "Guitarra roja", 1},
	{19318, 25, "Guitarra X", 1},
	{19319, 50, "XFireGuitarra", 3},
	{1210, 5, "Maleta", 1},
	{19346, 1, "HotDog", 1},
	{19472, 50, "Máscara de gas", 3},
	{19421, 3, "Audifonos blanco", 1},
	{19422, 3, "Audifonos negro", 1},
	{19423, 3, "Audifonos rosa", 1},
	{19424, 3, "Audifonos azul", 1},
	{11704, 40, "Máscara demonio", 3}, //agregados x edinsonwalker (18/01/2020)
	{1242, 44, "Chaleco de seguridad", 3},
	{371, 44, "Paracaidas", 3},
	{19801, 21, "Pasamontañas", 2},
	{19773, 2, "Pistolera", 2},
	{19347, 2, "Estrella", 2},
	{19515, 19, "Chaleco tactico gris", 2},
	{19514, 15, "Casco gris", 2},
	{368, 10, "Visión nocturna", 2},
	{19781, 12, "Sargento I", 2},
	{19782, 12, "Sargento II", 2},
	{19783, 12, "Oficial II", 2},
	{19784, 12, "Oficial III", 2},
	{19785, 12, "Oficial III+", 2},
	{19778, 12, "Detective I", 2},
	{19779, 12, "Detective II", 2},
	{19780, 12, "Detective III", 2},
	{370, 11118, "Jetpack", 3},
	{19558, 4, "Gorra pizzero", 1},
	{19488, 5, "Sombrero blanco", 1}
};
//actualizar toy
ActualizarToy(playerid, toy)
{
	new query[1029], infotoy[512];
	format(infotoy, sizeof infotoy, "%d|%d|%f|%f|%f|%f|%f|%f|%f|%f|%f|%d|",
	InfoPersonaje[playerid][ptModelo][toy], InfoPersonaje[playerid][ptHueso][toy],
	InfoPersonaje[playerid][ptPosX][toy], InfoPersonaje[playerid][ptPosY][toy], InfoPersonaje[playerid][ptPosZ][toy],
	InfoPersonaje[playerid][ptRotX][toy], InfoPersonaje[playerid][ptRotY][toy], InfoPersonaje[playerid][ptRotZ][toy],
	InfoPersonaje[playerid][ptScaleX][toy], InfoPersonaje[playerid][ptScaleY][toy], InfoPersonaje[playerid][ptScaleZ][toy],
	InfoPersonaje[playerid][ptColocado][toy]);

	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Toy%d = '%e', ColorToy%d = '%d' WHERE ID = '%d'", toy+1, infotoy, toy+1, InfoPersonaje[playerid][ptColor][toy], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

GetNameToy(playerid, id)
{
	new	name_this[64];
	alm(name_this, "desconocido");
	Loop(x, sizeof InfoToy, 0) if (InfoToy[x][accModelo] == InfoPersonaje[playerid][ptModelo][id])
	{
		alm(name_this, InfoToy[x][accNombre]);
		return name_this;
	}
	return name_this;
}

GetStatusToy(playerid, id)
{
	new	name_this[64];
	if (InfoPersonaje[playerid][ptColocado][id] != 0) alm(name_this, "{64CA46}Sí");
	else alm(name_this, "{ED3F3F}No");
	return name_this;
}

GetParteToy(playerid, id)
{
	new	name_this[24];
	alm(name_this, "Desconocida");
	switch (InfoPersonaje[playerid][ptHueso][id])
	{
		case 1: alm(name_this, "Columna");
		case 2: alm(name_this, "Cabeza");
		case 3: alm(name_this, "Brazo izquierdo");
		case 4: alm(name_this, "Brazo derecho");
		case 5: alm(name_this, "Mano izquierda");
		case 6: alm(name_this, "Mano derecha");
		case 7: alm(name_this, "Muslo izquierdo");
		case 8: alm(name_this, "Muslo derecho");
		case 9: alm(name_this, "Pie izquierdo");
		case 10: alm(name_this, "Pie derecho");
		case 11: alm(name_this, "Pantorrilla derecha");
		case 12: alm(name_this, "LefPantorrillat izquierda");
		case 13: alm(name_this, "Antevrazo izquierdo");
		case 14: alm(name_this, "Antevrazo derecho");
		case 15: alm(name_this, "Clavicula izquierda");
		case 16: alm(name_this, "Clavicula derecha");
		case 17: alm(name_this, "Cuello");
		case 18: alm(name_this, "Quijada");
	}
	return name_this;
}

// colores toys
#define RGBAToARGB(%1)		(%1 >>> 8 | %1 << 24)

enum ctInfo
{
	ctColor[32],
	ctNombre[32]
};

new InfoColorToy[][ctInfo] =
{
	// ROSA
    {"0xFFC0CBFF", "Rosado"},
    {"0xFFB6C1FF", "Rosado claro"},
    {"0xFF69B4FF", "Rosado caliente"},
    {"0xFF1493FF", "Rosado profundo"},
    {"0xC71585FF", "Violeta medio"},
    {"0xDB7093FF", "Violeta roso"},
    {"0x8B008BFF", "Magenta oscuro"},
    {"0x9932CCFF", "Orquidea oscuro"},
    {"0x7FFF00FF", "Chatreuse 1"},

	// NARANJA
    {"0xFFA07AFF", "Salmon claro"},
    {"0xFF7F50FF", "Coral"},
    {"0xFF6347FF", "Tomate"},
    {"0xFF4500FF", "Anaranjado"},
    {"0xFF8C00FF", "Naranja oscura"},
    {"0xFFA500FF", "Naranja"},

	// AMARILLO
    {"0xFFD700FF", "Oro"},
    {"0xFFFF00FF", "Amarillo"},
    {"0xFFFFE0FF", "Amarilo claro"},
    {"0xFFFACDFF", "Limon gasa"},
    {"0xFAFAD2FF", "Amarillo oro claro"},
    {"0xFFEFD5FF", "Papaya latigo"},
    {"0xFFE4B5FF", "Moccasin"},
    {"0xFFDAB9FF", "Hojaldre de melcoton"},
    {"0xEEE8AAFF", "Amarillo caía"},
    {"0xF0E68CFF", "Khaki"},
    {"0xBDB76BFF", "Khaki oscuro"},

	// ROJO
	{"0xCD5C5CFF", "Rojo indio"},
	{"0xF08080FF", "Coral claro"},
	{"0xFA8072FF", "Salmón"},
	{"0xE9967AFF", "Salmón oscuro"},
	{"0xFFA07AFF", "Salmón claro"},
	{"0xDC143CFF", "Carmesí"},
	{"0xFF0000FF", "Rojo"},
	{"0xB22222FF", "Ladrillo fuego"},
	{"0x8B0000FF", "Rojo oscuro"},
	{"0x000000FF", "Negro"}
};

GetColorToy(playerid, id)
{
	new exName[128] = "{EBEBEB}Ninguno";
	//verifica si es -1
	if (InfoPersonaje[playerid][ptColor][id] == -1) return exName;
	//resto:
	format(exName, sizeof exName, "{%.6s}%s\n", InfoColorToy[InfoPersonaje[playerid][ptColor][id]][ctColor][2], InfoColorToy[InfoPersonaje[playerid][ptColor][id]][ctNombre]);
	return exName;
}

SetColorToy(coler)
{
	new color = 0, gformat[32];
	if (coler == -1) return color;
	format(gformat, sizeof gformat, "%x", RGBAToARGB(hexstr(InfoColorToy[coler][ctColor])));
	color = hexstr(gformat);
	return color;
}

//commands
cmd:ctoys(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 5.0, 802.5069,-1419.6813,1016.4688))
	{
		if (InfoCuenta[playerid][jVIP] != 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Acceso sólo para usuarios VIP Level 2.");
		Loop(id, 7, 0) if (InfoPersonaje[playerid][ptModelo][id] == 0)
		{
			slotselection[playerid] = id;
			new ToyMuestra[180], count = 0;
			Loop(x, sizeof InfoToy, 0) if (InfoToy[x][accTipo] == 3)
			{
				ToyMuestra[count] = InfoToy[x][accModelo];
				count++;
			}
			ShowModelSelectionMenuEx(playerid, ToyMuestra, count, "Toys V.I.P", Compra_Toy);
			return 1;
		}
		SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes tener más de 7 toys.");
		return 1;
	}
	return 1;
}
alias:ctoys("comprartoys");

cmd:vertoys(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new iTargetID;
	if (sscanf(params, "d", iTargetID)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vertoys (playerid)");
	if (!IsPlayerConnectedEx(iTargetID)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador Invalido.");
	new szMessages[170], count = 0;
	Loop(iToyIter, 7, 0)
	{
		Loop(LoopRapist, sizeof InfoToy, 0) if (InfoToy[LoopRapist][accModelo] == InfoPersonaje[iTargetID][ptModelo][iToyIter])
		{
			format(szMessages, sizeof szMessages, "%s (slot %i, parte: %s)", InfoToy[LoopRapist][accNombre], iToyIter, GetParteToy(iTargetID, iToyIter));
			SendPlayerChatMessage(playerid, COLOR_WHITE, szMessages);
			count++;
		}
	}
	if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no tiene toys.");
	return 1;
}