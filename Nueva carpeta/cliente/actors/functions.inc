Dynamic_actor(id)
{
	if (InfoActor[id][aPosX] == 0.0) return 1;
	//label
	if (IsValidDynamic3DTextLabel(InfoActor[id][aLabel]))
	{
		DestroyDynamic3DTextLabel(InfoActor[id][aLabel]);
		InfoActor[id][aLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	new labelactor[128];
	if(InfoActor[id][aTipo] == 1) 
	{
		format(labelactor, sizeof labelactor, "%s [%d]", InfoActor[id][aNombre], id);
	}
	else format(labelactor, sizeof labelactor, "{a52b2a}%s {FFFFFF}[%d]", InfoActor[id][aNombre], id);

	InfoActor[id][aLabel] = CreateDynamic3DTextLabel(labelactor, -1, InfoActor[id][aPosX], InfoActor[id][aPosY], InfoActor[id][aPosZ]+1, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoActor[id][aVirtualWorld], InfoActor[id][aInterior], -1);
	
	//actor
	DestroyDynamicActor(InfoActor[id][aID_ig]);
	InfoActor[id][aID_ig] = CreateDynamicActor(InfoActor[id][aSkin], InfoActor[id][aPosX], InfoActor[id][aPosY], InfoActor[id][aPosZ], InfoActor[id][aPosR], true, 100.0, InfoActor[id][aVirtualWorld], InfoActor[id][aInterior]);
    Animacion_actor(id);
	return 1;
}

Animacion_actor(id)
{
	switch (InfoActor[id][aAnimacion])
	{
		case 1: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "DEALER", "DEALER_IDLE_01", 4.0, 1, 0, 1, 0, 0); // Hablar.
		case 2: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "GRAVEYARD", "prst_loopa", 4.0, 1, 0, 1, 0, 0); // Seguridad.
		case 3: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "SMOKING","M_smk_in", 4.0, 1, 0, 1, 0, 0); // Fumar.
		case 4: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "MISC", "Idle_Chat_02", 4.0, 1, 0, 1, 0, 0); // Hablar 2.
		case 5: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "ped", "SEAT_down", 4.0, 0, 0, 0, 1, 0); // Sentado.
		case 6: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "RAPPING", "Laugh_01", 4.0, 1, 0, 1, 0, 0); // Rie.
		case 7: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "DEALER", "DEALER_DEAL", 4.0, 1, 0, 1, 0, 0); //  Sacando dinero.
		case 8: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "RAPPING","RAP_A_Loop", 4.0, 1, 0, 1, 0, 0); // Rapeando.
		case 9: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "GANGS","smkcig_prtl", 4.0, 1, 0, 1, 0, 0); // Observando.
		case 10: ApplyDynamicActorAnimation(InfoActor[id][aID_ig], "STRIP","strip_E",4.1,7,5,1,1,1); // Perrea, perrea :D
	}
}

stock GetNearestActorOfType(playerid, tipo, Float:maxDist)
{
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for(new i = 0; i < MAX_ACTORS; i++)
    {
        if(!IsActorStreamedIn(i, playerid)) continue;
        if(InfoActor[i][aTipo] != tipo) continue;

        new Float:ax, Float:ay, Float:az;
        GetActorPos(i, ax, ay, az);

        if(IsPlayerInRangeOfPoint(playerid, maxDist, ax, ay, az))
            return i;
    }
    return INVALID_ACTOR_ID;
}

funcion Actores()
{
	// camello
	new ActorCamello[4];
	ActorCamello[0] = CreateDynamicActor(29, 2526.8215, -1641.3239, 13.9997, 336.4544, true, 100.0, 0, 0);
	ActorCamello[1] = CreateDynamicActor(28, 2474.8921, -1324.3365, 27.5433, 290.1262, true, 100.0, 0, 0);
	ActorCamello[2] = CreateDynamicActor(29, 1935.6304, -1060.5109, 24.4119, 216.1305, true, 100.0, 0, 0);
	ActorCamello[3] = CreateDynamicActor(28, 833.7507, -1528.7776, 13.6607, 162.5782, true, 100.0, 0, 0);
	ApplyDynamicActorAnimation(ActorCamello[0], "COP_AMBIENT", "Coplook_watch", 4.1, 0, 1, 1, 1, 1);
	ApplyDynamicActorAnimation(ActorCamello[1], "COP_AMBIENT", "Coplook_watch", 4.1, 0, 1, 1, 1, 1);
	ApplyDynamicActorAnimation(ActorCamello[2], "COP_AMBIENT", "Coplook_watch", 4.1, 0, 1, 1, 1, 1);
	ApplyDynamicActorAnimation(ActorCamello[3], "COP_AMBIENT", "Coplook_watch", 4.1, 0, 1, 1, 1, 1);
	CreateDynamic3DTextLabel(""#ColorWhite"Para hablar o interactuar con el {eb4040}Camello"#ColorWhite"\n"#ColorWhite"Escribe '{3E62F4}/camello"#ColorWhite"' en este lugar.", 0xE6DE48FF, 2526.8215, -1641.3239, 13.9997, 5.0);
	CreateDynamic3DTextLabel(""#ColorWhite"Para hablar o interactuar con el {eb4040}Camello"#ColorWhite"\n"#ColorWhite"Escribe '{3E62F4}/camello"#ColorWhite"' en este lugar.", 0xE6DE48FF, 2474.8921, -1324.3365, 27.5433, 5.0);
	CreateDynamic3DTextLabel(""#ColorWhite"Para hablar o interactuar con el {eb4040}Camello"#ColorWhite"\n"#ColorWhite"Escribe '{3E62F4}/camello"#ColorWhite"' en este lugar.", 0xE6DE48FF, 1935.6304, -1060.5109, 24.4119, 5.0);
	CreateDynamic3DTextLabel(""#ColorWhite"Para hablar o interactuar con el {eb4040}Camello"#ColorWhite"\n"#ColorWhite"Escribe '{3E62F4}/camello"#ColorWhite"' en este lugar.", 0xE6DE48FF, 833.7507, -1528.7776, 13.6607, 5.0);

	return 1;
}

