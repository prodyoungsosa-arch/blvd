VerificarNumero(number)
{
	new query[256];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Telefono = '%d'", number);
	result = mysql_query(db_samp, query);
	new nmr = cache_num_rows();
	cache_delete(result);
	if (nmr > 0) return 1;
	return 0;
}

funcion CurarBotiquin(playerid, playerid2)
{
	TogglePlayerControllable(playerid, true);
	TogglePlayerControllable(playerid2, true);
    ClearAnimations(playerid);
    ClearAnimations(playerid2);
	new Float: health = InfoPersonaje[playerid2][pVida];
	if (health >= 50) dar_vida(playerid2, 100);
	else dar_vida(playerid2, health + 50.0);
	return 1;
}

SetPlayerPayDay(playerid)
{
	PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
	if (FakePayday[playerid] == 0) InfoPersonaje[playerid][pHorasOn]++;
	FakePayday[playerid] = 0;
	if (InfoPersonaje[playerid][pHorasOn] == 0) SetPlayerScore(playerid, 1);
	else SetPlayerScore(playerid, InfoPersonaje[playerid][pHorasOn]);
	SendPlayerChatMessage(playerid, 0x00AE57FF, "Hora de pago diario");
	//mensaje
	new saldo_viejo = InfoPersonaje[playerid][pBanco];
	new pago2 = 0;
	new intereses = 0;

	//SALARIO 
	new faccion = InfoPersonaje[playerid][pMiembro];
	if (faccion != 0)
	{
		pago2 = InfoFaccion[faccion][fSalario];
		if (InfoFaccion[faccion][fSalario] != 0)
		{
			SendClientMessageEx(playerid, 0xEBEBEBFF, "Salario: {00DC00}$%s", diner_coma(pago2));
		}
	}
	new pago_vip = 0;
	if (InfoCuenta[playerid][jVIP] == 1) pago_vip = 400;
	else if (InfoCuenta[playerid][jVIP] == 2) pago_vip = 900;
	// intereses
	intereses = saldo_viejo/1000;
	if (intereses > 1000) { intereses = 1000; }
	InfoPersonaje[playerid][pBanco] += intereses;
	// dinero estado
	new pago1 = 120;
	SendClientMessageEx(playerid, 0xEBEBEBFF, "Dinero del estado: {00DC00}$%s{EBEBEB} - Intereses (Ganancia): {00DC00}$%s", diner_coma(pago1), diner_coma(intereses));
	//vip
	if (pago_vip != 0)
	{
	    SendClientMessageEx(playerid, 0xFFBF00FF, "Dinero VIP: {EBEBEB}$%s", diner_coma(pago_vip));
		InfoPersonaje[playerid][pBanco] += pago_vip;
	}
	// balance
	InfoPersonaje[playerid][pBanco] += (pago1+pago2);
	SendClientMessageEx(playerid, 0xEBEBEBFF, "Balance anterior: {00DC00}$%s{EBEBEB} | Balance ahora: {00AC00}$%s", diner_coma(saldo_viejo), diner_coma(InfoPersonaje[playerid][pBanco]));
	//save
	new query[620];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET BanescoOwO = '%d', LimiteRobos = 0, FugaoVicio = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pBanco], InfoPersonaje[playerid][pHorasOn], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	//
	if (InfoPersonaje[playerid][pLimiteRobos] != 0)
	{
		SendPlayerChatMessage(playerid, 0x36C548FF, "Ya puedes volver a robar. (/robar247)");
		InfoPersonaje[playerid][pLimiteRobos] = 0;
	}
	return 1;
}

MensajeMPS(color, const gformat[])
{
	foreach (new playerid2: Player) if (IsPlayerConnectedEx(playerid2))
	{
		if (InfoCuenta[playerid2][jAdmin] >= 1 && InfoCuenta[playerid2][jVerMP] == 0)
		{
			SendSplitMessage(playerid2, color, gformat);
		}
	}
}

rol_ame(playerid, params[])
{
	if (InfoPersonaje[playerid][pMuerto] != 2)
	{
	    new string[256];
	    format(string, sizeof string, "> {player:%d} %s", playerid, params);
	    SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);
		ProxDetector(15.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	}
}

rol_auto(playerid, params[])
{
	if (InfoPersonaje[playerid][pMuerto] != 2)
	{
		new string[256];
		format(string, sizeof string, "* %s %s", GetNameFormat(playerid), params);
		ProxDetector(15.0, playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	}
}

ReturnName(playerid)
{
    new name[MAX_PLAYER_NAME];
    if (playerid == -1) name = "EOS";
    else GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    return name;
}

OnPlayerCleanVariables(playerid)
{	

	// Conce
	Vehicle_Color[playerid] = -1;

	//Ordenado 6/11/2025
	Act_Personajes[playerid] = 0; //Personajes
	SeleccionoPJ1[playerid] = -1;
	SeleccionoPJ2[playerid] = -1;
	SeleccionoPJ3[playerid] = -1;
	SeleccionoPJ4[playerid] = -1;
	SeleccionoPJ5[playerid] = -1;


	PlayerWeather[playerid] = INVALID; //clima nuevo
	TheUseDegrees[playerid] = 0;
	//
	DopTimer[playerid] = -1;
	VisitaTimer[playerid] = 0;
	VisitaTimer2[playerid] = -1;
	TipoAudio[playerid] = 0;
    wsp_u[playerid] = -1;
	wsp_time[playerid] = -1;
    PersonajeTiempo[playerid] = -1;
    fRespawnTiempo[playerid] = -1;
    check_motor[playerid] = 0;
	veh_asiento[playerid] = -1;
	gPlayerUsingLoopingAnim[playerid] = 0;

	DeletePVar(playerid, "LoadingObjects");
	VecesHerido[playerid] = 0;
	YaAviso[playerid] = 0;

	SetPVarInt(playerid, "act_point", 0);

    pDrunkLevelLast[playerid]   = 0;

    RecargarTiempo[playerid] = -1;
	DentroCasa[playerid] = -1;
	DentroNegocio[playerid] = -1;

	pagina_mueble[playerid] = 0;
	is_mueble_actual[playerid] = 0;

	es_hablando[playerid] = 0;

    NPCrepara[playerid] = 0;
	VehiculoGasolina[playerid] = 0;

	FakePayday[playerid] = 0;
	CarTick[playerid] = 0;
	LastVehicle[playerid] = 0;
	advWeapons[playerid] = 0;
	AdvVehs[playerid] = 0;
	Adv2Vehs[playerid] = 0;
	for (new i = 0; i < MAX_SYNC_TYPES; ++i) { SetSyncTime (playerid, i); }
 	WarningTPlayer[playerid] = 0;

	InfoPersonaje[playerid][pModoAfk] = 0;

	Act_Inventario[playerid] = 0;

	CulandoPrecio[playerid] = 0;
	CulandoCliente[playerid] = -1;
	CulandoNegocio[playerid] = -1;

	DeletePVar(playerid, "ModoSpray");
	SetPVarString(playerid, "TextoGraffiti", "");
	SetPVarInt(playerid, "LetraGraffiti", 5);

	TimerWeaponCreate[playerid] = -1;

	MensajeMuelto[playerid] = 0;
	GetTextDraw[playerid] = 0;
	ConBalasGoma[playerid] = 0;
	test_rol[playerid] = 5;

    show_velocimetro[playerid] = 0;
	PlayerViewAnunce[playerid] = 0;
	SetPVarString(playerid, "anunce1", "");
	SetPVarString(playerid, "anunce2", "");
	SetPVarString(playerid, "anunce3", "");
	SetPVarString(playerid, "anunce4", "");
	SetPVarString(playerid, "anunce5", "");

	DeletePVar(playerid, "desbug_muerte");
	PosSpawnBug[playerid][0] = 2105.0334;
	PosSpawnBug[playerid][1] = -1473.9088;
	PosSpawnBug[playerid][2] = 24.1237;
	PosSpawnBug[playerid][3] = 0.0000;
	PosVwBug[playerid] = 0;
	PosIntBug[playerid] = 0;

	SetPVarInt(playerid, "PlayerCuffed", 0);
	EditandoObjetoJ[playerid] = 0;

	Altavoz[playerid] = 0;
	EnLlamada[playerid] = 0; //Sistema teléfono
	ToqueLlamada[playerid] = 0;
	PersonaEnLlamada[playerid] = -1;

	edicion_sql_actual[playerid] = -1;
	InfoPersonaje[playerid][pEditingMode] = 0;

	ContadorCuraciones[playerid] = 0;

	playerTextdraw[playerid] = false;

	CountKick[playerid] = 0;
	TimerCkick[playerid] = -1;
	CountBan[playerid] = 0;
	TimerCban[playerid] = -1;
	CountWarn[playerid] = 0;
	TimerCwarn[playerid] = -1;

    papilla[playerid] = 0;
	AdminChat[playerid] = 0;
	PlayerDuda[playerid] = 0;
	alm(PlayerTextoDuda[playerid], "nada");
	TomandoTrabajo[playerid] = -1;
	Taseado[playerid] = 0;
	Anti[playerid][BalasW] = 0;
    CederTiempo[playerid] = -1;
	countGameTime[playerid] = 0;
	player_weapon[playerid] = -1;
	player_asesino[playerid] = -1;
    DeletePVar(playerid, "EstaCrack");
	intentos_load[playerid] = 0;
    autorepara[playerid] = 0;
	// Administración.
	See_FRC[playerid] = 0; // Frecuencia de la radio.
}

resetPlayerVariables(playerid)
{

	pDroga[playerid][TiempoMetanfetamina] = 0;
	pDroga[playerid][TiempoKetamina] = 0;
	pDroga[playerid][TiempoCocaina] = 0;
	pDroga[playerid][TiempoHeroina] = 0;
	pDroga[playerid][TiempoMarihuana] = 0;
	pDroga[playerid][EfectoMarihuana] = 0;
	pDroga[playerid][EfectoLSD] = 0;
	pDroga[playerid][EfectoHongo] = 0;
	pDroga[playerid][EfectoEspecialUWU] = 0;
	pDroga[playerid][EfectoCocaina] = 0;
	pDroga[playerid][EfectoMDMA] = 0;

	pDroga[playerid][NivelSobredosis] = 0;
	pDroga[playerid][AdiccionAnfetamina] = 0;
	pDroga[playerid][AdiccionCocaina] = 0;
	pDroga[playerid][EfectoCocaina] = 0;
	pDroga[playerid][AdiccionOpioides] = 0;

	pDroga[playerid][AdicCoca] = 0;
	pDroga[playerid][AdicOpio] = 0;
	pDroga[playerid][AdicMeta] = 0;

	pDroga[playerid][EnMenuLab] = 0;
	pDroga[playerid][Sobredosis] = 0;

    tipo_refuerzos[playerid] = 0;
	BuyVIPvehicle[playerid] = -1;
	CompraVehiculo[playerid] = -1;
    slotselection[playerid] = -1;

	GunVendedor[playerid] = -1;
	GunCliente[playerid] = -1;
	GunObjeto[playerid] = 0;
	GunCantidad[playerid] = 0;
	GunPrecio[playerid] = 0;

	usuario_registro[playerid] = 0;
	altavoz_phone[playerid] = 0;
	refuerzos_pd[playerid] = 0;
	refuerzos_sd[playerid] = 0;
	refuerzos_fbi[playerid] = 0;

	Osql_vehicle[playerid] = 0;
	Pla_vehicle[playerid] = 999;
	Price_vehicle[playerid] = 0;

	SetPVarInt(playerid, "shrequest", INVALID_PLAYER_ID);

	NombreLicencia[playerid] = 999;
	PrecioLicencia[playerid] = 0;

	BigEar[playerid] = 0;
	gLastCar[playerid] = 0;
	TicketOffer[playerid] = 999; 				TicketMoney[playerid] = 0;

	OwnableCarOffer[playerid] = 999; 			OwnableCarID[playerid] = 999; 		OwnableCarPrice[playerid] = 0; 		BlindFold[playerid] = 0;
	AdminDuty[playerid] = 0; 					PlayerNeedsHelp[playerid] = 0;

	PuedeD[playerid] = 0;
	Facturing[playerid] = 0; 					fPay[playerid] = 0; 				fDest[playerid] = 0; 				fFacturer[playerid] = 0;
	Refueling[playerid] = -1;		 			RequestingBackup[playerid] = 0;
	RegText[playerid] = 0;						RegConfig[playerid] = 0;

	FreezeLast[playerid] = 0;
	Condom[playerid] = 0;
	RStep[playerid] = 0;

	OnDuty[playerid] = 0;
	JetPack[playerid] = 0;
	JustDuda[playerid] = -1;
	JustReported[playerid] = -1;
	Spectating[playerid] = 0;                   GettingSpectated[playerid] = 999;   Spectate[playerid] = 999;           Unspec[playerid][sLocal] = 255;
	Editing[playerid] = 0;

	Blinded[playerid] = 0; 						Tied[playerid] = 0;
	CommandSpamTimes[playerid] = 0;				CommandSpamUnmute[playerid] = 0;
	alm(QFA[playerid], "Nadie");
	return true;
}

