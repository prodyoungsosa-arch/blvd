Dialog:COPOBJECTS_DIALOG(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
	if(listitem == 0) ShowModelSelectionMenu(playerid, RoadblockList, "Barricadas");
	if(listitem == 1) ShowModelSelectionMenu(playerid, SignList, "Signos");
	if(listitem == 2)
	{
		new id = GetFreeObjectID();
  		if(id == -1) return ShowInfoForPlayer(playerid, "Se alcanzó el límite de objetos.", 5000);
    	CopObjectData[id][ObjCreated] = true;
	    GetPlayerName(playerid, CopObjectData[id][Owner], MAX_PLAYER_NAME);
	    CopObjectData[id][Type] = OBJECT_TYPE_POLICELINE;
	    CopObjectData[id][ObjModel] = 19834;
	    CopObjectData[id][ObjInterior] = GetPlayerInterior(playerid);
	    CopObjectData[id][ObjVirtualWorld] = GetPlayerVirtualWorld(playerid);

		new Float: x, Float: y, Float: z, Float: a;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, a);
  		x += (2.0 * floatsin(-a, degrees));
		y += (2.0 * floatcos(-a, degrees));
		CopObjectData[id][ObjXb] = x;
		CopObjectData[id][ObjYb] = y;
		CopObjectData[id][ObjZb] = z;
		CopObjectData[id][ObjRX] = 0.0;
		CopObjectData[id][ObjRY] = 0.0;
		CopObjectData[id][ObjRZ] = a;
		CopObjectData[id][ObjID] = CreateDynamicObject(19834, x, y, z, 0.0, 0.0, a, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		CopObjectData[id][ObjArea] = -1;

		new stringXZ[96];
		format(stringXZ, sizeof(stringXZ), "ID: %d", id);
		CopObjectData[id][ObjLabel] = CreateDynamic3DTextLabel(stringXZ, COLOR_WHITE, x, y, z + 0.0, 5.0, _, _, _, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza /ebar para editar la línea, y /qbar para eliminarla.");
	}
	if(listitem == 3)
	{
		new id = GetFreeObjectID();
		if(id == -1) return ShowInfoForPlayer(playerid, "Se alcanzó el límite de objetos.", 5000);
  		CopObjectData[id][ObjCreated] = true;
        GetPlayerName(playerid, CopObjectData[id][Owner], MAX_PLAYER_NAME);
        CopObjectData[id][Type] = OBJECT_TYPE_SPIKE;
		CopObjectData[id][ObjModel] = 2899;
        CopObjectData[id][ObjInterior] = GetPlayerInterior(playerid);
        CopObjectData[id][ObjVirtualWorld] = GetPlayerVirtualWorld(playerid);

		new Float: x, Float: y, Float: z, Float: a;
  		GetPlayerPos(playerid, x, y, z);
    	GetPlayerFacingAngle(playerid, a);
	    x += (2.0 * floatsin(-a, degrees));
		y += (2.0 * floatcos(-a, degrees));

		CopObjectData[id][ObjXb] = x;
		CopObjectData[id][ObjYb] = y;
		CopObjectData[id][ObjZb] = z - 0.85;
		CopObjectData[id][ObjRX] = 0.0;
		CopObjectData[id][ObjRY] = 0.0;
		CopObjectData[id][ObjRZ] = a + 90.0;
		CopObjectData[id][ObjID] = CreateDynamicObject(2899, x, y, z - 0.85, 0.0, 0.0, a + 90.0, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		CopObjectData[id][ObjArea] = CreateDynamicSphere(x, y, z - 0.85, 2.5, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);

	    new stringXZ[96];
		format(stringXZ, sizeof(stringXZ), "ID: %d", id);
		CopObjectData[id][ObjLabel] = CreateDynamic3DTextLabel(stringXZ, COLOR_WHITE, x, y, z - 0.0, 3.0, _, _, _, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza /ebar para editar la línea, y /qbar para eliminarla.");
	}
	return 1;
}

