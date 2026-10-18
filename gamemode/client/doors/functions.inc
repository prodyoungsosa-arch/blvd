CreateDynamicDoor(id, mapicon)
{
	new label_door[235];
	DestroyDynamicPickup(InfoPuerta[id][pdExteriorPickup]);
	DestroyDynamicPickup(InfoPuerta[id][pdInteriorPickup]);
	if (IsValidDynamic3DTextLabel(InfoPuerta[id][pdExteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoPuerta[id][pdExteriorLabel]);
		InfoPuerta[id][pdExteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoPuerta[id][pdInteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoPuerta[id][pdInteriorLabel]);
		InfoPuerta[id][pdInteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	format(label_door, sizeof label_door, "[%d] {F5DEB3}%s\n{EBEBEB}Presiona {3E62F4}'H'{EBEBEB} para entrar", id, InfoPuerta[id][pdNombre]);
	InfoPuerta[id][pdExteriorLabel] = CreateDynamic3DTextLabel(label_door, 0xEBEBEBFF, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ]+0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoPuerta[id][pdExteriorVW], InfoPuerta[id][pdExteriorInt], -1);
	format(label_door, sizeof label_door, "[%d] {F5DEB3}%s\n{EBEBEB}Presiona {3E62F4}'H'{EBEBEB} para salir", id, InfoPuerta[id][pdNombre]);
	InfoPuerta[id][pdInteriorLabel] = CreateDynamic3DTextLabel(label_door, 0xEBEBEBFF, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ]+0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoPuerta[id][pdInteriorVW], InfoPuerta[id][pdInteriorInt], -1);
	InfoPuerta[id][pdExteriorPickup] = CreateDynamicPickup(GetModelDoor(id), 1, InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdExteriorVW], InfoPuerta[id][pdExteriorInt], -1);
	InfoPuerta[id][pdInteriorPickup] = CreateDynamicPickup(GetModelDoor(id), 1, InfoPuerta[id][pdInteriorX], InfoPuerta[id][pdInteriorY], InfoPuerta[id][pdInteriorZ], InfoPuerta[id][pdInteriorVW], InfoPuerta[id][pdInteriorInt], -1);
	if (mapicon != 0)
	{
		DestroyDynamicMapIcon(InfoPuerta[id][pdExteriorMapIcon]);
		if (InfoPuerta[id][pdMapIcon] != 0)
			InfoPuerta[id][pdExteriorMapIcon] = CreateDynamicMapIcon(InfoPuerta[id][pdExteriorX], InfoPuerta[id][pdExteriorY], InfoPuerta[id][pdExteriorZ], InfoPuerta[id][pdMapIcon], 0, 0, 0, -1, 300);
	}
}

noexitDoor(id)
{
	DestroyDynamicPickup(InfoPuerta[id][pdExteriorPickup]);
	DestroyDynamicPickup(InfoPuerta[id][pdInteriorPickup]);
	if (IsValidDynamic3DTextLabel(InfoPuerta[id][pdExteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoPuerta[id][pdExteriorLabel]);
		InfoPuerta[id][pdExteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoPuerta[id][pdInteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoPuerta[id][pdInteriorLabel]);
		InfoPuerta[id][pdInteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	DestroyDynamicMapIcon(InfoPuerta[id][pdExteriorMapIcon]);
	InfoPuerta[id][pdExteriorLabel] = CreateDynamic3DTextLabel("puelta", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
	InfoPuerta[id][pdInteriorLabel] = CreateDynamic3DTextLabel("puelta", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
	InfoPuerta[id][pdExteriorPickup] = CreateDynamicPickup(1239, 1, -2190.7974, 165.9186, 58.2604, id, id);
	InfoPuerta[id][pdInteriorPickup] = CreateDynamicPickup(1239, 1, -2190.7974, 165.9186, 58.2604, id, id);
	return 1;
}

GetModelDoor(id)
{
	new modelid = 1318;
	switch (InfoPuerta[id][pdModelo])
	{
		case 1: modelid = 1210;
		case 2: modelid = 1212;
		case 3: modelid = 1239;
		case 4: modelid = 1240;
		case 5: modelid = 1241;
		case 6: modelid = 1242;
		case 7: modelid = 1247;
		case 8: modelid = 1248;
		case 9: modelid = 1252;
		case 10: modelid = 1253;
		case 11: modelid = 1254;
		case 12: modelid = 1313;
		case 13: modelid = 1272;
		case 14: modelid = 1273;
		case 15: modelid = 1274;
		case 16: modelid = 1275;
		case 17: modelid = 1276;
		case 18: modelid = 1277;
		case 19: modelid = 1279;
		case 20: modelid = 1314;
		case 21: modelid = 1316;
		case 22: modelid = 1317;
		case 23: modelid = 1559;
		case 24: modelid = 1582;
		case 25: modelid = 2894;
	}
	return modelid;
}