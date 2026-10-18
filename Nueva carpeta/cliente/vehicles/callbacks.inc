forward CargarVehiculos();
public CargarVehiculos()
{
	Loop(xd, MAX_VEHICULOS, 0)
	{
		alm(InfoVehiculo[xd][vPropietario], "none");
		InfoVehiculo[xd][vMaleteroOn] = 0;
		InfoVehiculo[xd][vRentaTiempo] = 0;
		alm(InfoVehiculo[xd][vRentaDueno], "none");
		alm(InfoVehiculo[xd][vCallSign], "");
		alm(InfoVehiculo[xd][vCompartida1], "none");
		alm(InfoVehiculo[xd][vCompartida2], "none");
		alm(InfoVehiculo[xd][vCompartida3], "none");
	}
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoVehiculo[id][vID_sql]);
		rebel_string(tabla, "Nombre", InfoVehiculo[id][vNombre], 128);
		rebel_string(tabla, "Propietario", InfoVehiculo[id][vPropietario], MAX_PLAYER_NAME);
		rebel_int(tabla, "Tipo", InfoVehiculo[id][vTipo]);
		rebel_int(tabla, "Negocio", InfoVehiculo[id][vNegocio]);
		rebel_int(tabla, "Trabajo", InfoVehiculo[id][vTrabajo]);
		rebel_int(tabla, "Modelo", InfoVehiculo[id][vModelo]);
		rebel_float(tabla, "Posicion_X", InfoVehiculo[id][vPosicionX]);
		rebel_float(tabla, "Posicion_Y", InfoVehiculo[id][vPosicionY]);
		rebel_float(tabla, "Posicion_Z", InfoVehiculo[id][vPosicionZ]);
		rebel_float(tabla, "Posicion_R", InfoVehiculo[id][vPosicionR]);
		rebel_int(tabla, "Interior", InfoVehiculo[id][vInterior]);
		rebel_int(tabla, "VirtualWorld", InfoVehiculo[id][vVirtualWorld]);
		rebel_float(tabla, "End_Posicion_X", InfoVehiculo[id][vEndPosicionX]);
		rebel_float(tabla, "End_Posicion_Y", InfoVehiculo[id][vEndPosicionY]);
		rebel_float(tabla, "End_Posicion_Z", InfoVehiculo[id][vEndPosicionZ]);
		rebel_float(tabla, "End_Posicion_R", InfoVehiculo[id][vEndPosicionR]);
		rebel_int(tabla, "End_Interior", InfoVehiculo[id][vEndInterior]);
		rebel_int(tabla, "End_VirtualWorld", InfoVehiculo[id][vEndVirtualWorld]);
		rebel_float(tabla, "Vida", InfoVehiculo[id][vVida]);
		rebel_int(tabla, "DanioSuperficie", InfoVehiculo[id][vDanioSuperficie]);
		rebel_int(tabla, "DanioPuertas", InfoVehiculo[id][vDanioPuertas]);
		rebel_int(tabla, "DanioLuces", InfoVehiculo[id][vDanioLuces]);
		rebel_int(tabla, "DanioRuedas", InfoVehiculo[id][vDanioRuedas]);
		rebel_int(tabla, "Gasolina", InfoVehiculo[id][vGasolina]);
		rebel_int(tabla, "Color_1", InfoVehiculo[id][vColor_1]);
		rebel_int(tabla, "Color_2", InfoVehiculo[id][vColor_2]);
		rebel_int(tabla, "PaintJob", InfoVehiculo[id][vPaintJob]);
		rebel_int(tabla, "ConSeguro", InfoVehiculo[id][vSeguro]);
		rebel_int(tabla, "Precio", InfoVehiculo[id][vPrecio]);
		rebel_int(tabla, "Embargo", InfoVehiculo[id][vEmbargo]);
		rebel_int(tabla, "Multa", InfoVehiculo[id][vMulta]);
		rebel_int(tabla, "Maletero1", InfoVehiculo[id][vMaletero][0]);
		rebel_int(tabla, "MaleteroCant1", InfoVehiculo[id][vMaleteroCant][0]);
		rebel_int(tabla, "Maletero2", InfoVehiculo[id][vMaletero][1]);
		rebel_int(tabla, "MaleteroCant2", InfoVehiculo[id][vMaleteroCant][1]);
		rebel_int(tabla, "Maletero3", InfoVehiculo[id][vMaletero][2]);
		rebel_int(tabla, "MaleteroCant3", InfoVehiculo[id][vMaleteroCant][2]);
		rebel_int(tabla, "Maletero4", InfoVehiculo[id][vMaletero][3]);
		rebel_int(tabla, "MaleteroCant4", InfoVehiculo[id][vMaleteroCant][3]);
		rebel_int(tabla, "Maletero5", InfoVehiculo[id][vMaletero][4]);
		rebel_int(tabla, "MaleteroCant5", InfoVehiculo[id][vMaleteroCant][4]);
		rebel_int(tabla, "Maletero6", InfoVehiculo[id][vMaletero][5]);
		rebel_int(tabla, "MaleteroCant6", InfoVehiculo[id][vMaleteroCant][5]);
		rebel_int(tabla, "Maletero7", InfoVehiculo[id][vMaletero][6]);
		rebel_int(tabla, "MaleteroCant7", InfoVehiculo[id][vMaleteroCant][6]);
		rebel_int(tabla, "Maletero8", InfoVehiculo[id][vMaletero][7]);
		rebel_int(tabla, "MaleteroCant8", InfoVehiculo[id][vMaleteroCant][7]);
		rebel_int(tabla, "Maletero9", InfoVehiculo[id][vMaletero][8]);
		rebel_int(tabla, "MaleteroCant9", InfoVehiculo[id][vMaleteroCant][8]);
		rebel_int(tabla, "Maletero10", InfoVehiculo[id][vMaletero][9]);
		rebel_int(tabla, "MaleteroCant10", InfoVehiculo[id][vMaleteroCant][9]);
		rebel_int(tabla, "MaxMaletero", InfoVehiculo[id][vMaxMaletero]);
		rebel_int(tabla, "Modificacion1", InfoVehiculo[id][vModificacion][0]);
		rebel_int(tabla, "Modificacion2", InfoVehiculo[id][vModificacion][1]);
		rebel_int(tabla, "Modificacion3", InfoVehiculo[id][vModificacion][2]);
		rebel_int(tabla, "Modificacion4", InfoVehiculo[id][vModificacion][3]);
		rebel_int(tabla, "Modificacion5", InfoVehiculo[id][vModificacion][4]);
		rebel_int(tabla, "Modificacion6", InfoVehiculo[id][vModificacion][5]);
		rebel_int(tabla, "Modificacion7", InfoVehiculo[id][vModificacion][6]);
		rebel_int(tabla, "Modificacion8", InfoVehiculo[id][vModificacion][7]);
		rebel_int(tabla, "Modificacion9", InfoVehiculo[id][vModificacion][8]);
		rebel_int(tabla, "Modificacion10", InfoVehiculo[id][vModificacion][9]);
		rebel_int(tabla, "Modificacion11", InfoVehiculo[id][vModificacion][10]);
		rebel_int(tabla, "Modificacion12", InfoVehiculo[id][vModificacion][11]);
		rebel_int(tabla, "Modificacion13", InfoVehiculo[id][vModificacion][12]);
		rebel_int(tabla, "Modificacion14", InfoVehiculo[id][vModificacion][13]);
		rebel_int(tabla, "Modificacion15", InfoVehiculo[id][vModificacion][14]);
		rebel_string(tabla, "CallSign", InfoVehiculo[id][vCallSign], 40);
		rebel_int(tabla, "ObjModelo_1", InfoVehiculo[id][vObjModelo][0]);
		rebel_float(tabla, "ObjPosX_1", InfoVehiculo[id][vObjPosX][0]);
		rebel_float(tabla, "ObjPosY_1", InfoVehiculo[id][vObjPosY][0]);
		rebel_float(tabla, "ObjPosZ_1", InfoVehiculo[id][vObjPosZ][0]);
		rebel_float(tabla, "ObjRotX_1", InfoVehiculo[id][vObjRotX][0]);
		rebel_float(tabla, "ObjRotY_1", InfoVehiculo[id][vObjRotY][0]);
		rebel_float(tabla, "ObjRotZ_1", InfoVehiculo[id][vObjRotZ][0]);
		rebel_int(tabla, "ObjModelo_2", InfoVehiculo[id][vObjModelo][1]);
		rebel_float(tabla, "ObjPosX_2", InfoVehiculo[id][vObjPosX][1]);
		rebel_float(tabla, "ObjPosY_2", InfoVehiculo[id][vObjPosY][1]);
		rebel_float(tabla, "ObjPosZ_2", InfoVehiculo[id][vObjPosZ][1]);
		rebel_float(tabla, "ObjRotX_2", InfoVehiculo[id][vObjRotX][1]);
		rebel_float(tabla, "ObjRotY_2", InfoVehiculo[id][vObjRotY][1]);
		rebel_float(tabla, "ObjRotZ_2", InfoVehiculo[id][vObjRotZ][1]);
		rebel_int(tabla, "ObjModelo_3", InfoVehiculo[id][vObjModelo][2]);
		rebel_float(tabla, "ObjPosX_3", InfoVehiculo[id][vObjPosX][2]);
		rebel_float(tabla, "ObjPosY_3", InfoVehiculo[id][vObjPosY][2]);
		rebel_float(tabla, "ObjPosZ_3", InfoVehiculo[id][vObjPosZ][2]);
		rebel_float(tabla, "ObjRotX_3", InfoVehiculo[id][vObjRotX][2]);
		rebel_float(tabla, "ObjRotY_3", InfoVehiculo[id][vObjRotY][2]);
		rebel_float(tabla, "ObjRotZ_3", InfoVehiculo[id][vObjRotZ][2]);
		rebel_int(tabla, "ObjModelo_4", InfoVehiculo[id][vObjModelo][3]);
		rebel_float(tabla, "ObjPosX_4", InfoVehiculo[id][vObjPosX][3]);
		rebel_float(tabla, "ObjPosY_4", InfoVehiculo[id][vObjPosY][3]);
		rebel_float(tabla, "ObjPosZ_4", InfoVehiculo[id][vObjPosZ][3]);
		rebel_float(tabla, "ObjRotX_4", InfoVehiculo[id][vObjRotX][3]);
		rebel_float(tabla, "ObjRotY_4", InfoVehiculo[id][vObjRotY][3]);
		rebel_float(tabla, "ObjRotZ_4", InfoVehiculo[id][vObjRotZ][3]);
		rebel_int(tabla, "ObjModelo_5", InfoVehiculo[id][vObjModelo][4]);
		rebel_float(tabla, "ObjPosX_5", InfoVehiculo[id][vObjPosX][4]);
		rebel_float(tabla, "ObjPosY_5", InfoVehiculo[id][vObjPosY][4]);
		rebel_float(tabla, "ObjPosZ_5", InfoVehiculo[id][vObjPosZ][4]);
		rebel_float(tabla, "ObjRotX_5", InfoVehiculo[id][vObjRotX][4]);
		rebel_float(tabla, "ObjRotY_5", InfoVehiculo[id][vObjRotY][4]);
		rebel_float(tabla, "ObjRotZ_5", InfoVehiculo[id][vObjRotZ][4]);
		rebel_int(tabla, "Sirena", InfoVehiculo[id][vSirena]);
		rebel_int(tabla, "Premium", InfoVehiculo[id][vPremium]);
		rebel_string(tabla, "Compartida1", InfoVehiculo[id][vCompartida1], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida2", InfoVehiculo[id][vCompartida2], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida3", InfoVehiculo[id][vCompartida3], MAX_PLAYER_NAME);
		rebel_int(tabla, "Stereo", InfoVehiculo[id][vStereo]);
		if (InfoVehiculo[id][vID_sql]) totalvehiculos++;
		if (InfoVehiculo[id][vModelo] != 0) cargaditos++;
		if (InfoVehiculo[id][vTipo] != 0 || InfoVehiculo[id][vNegocio] != 0 || InfoVehiculo[id][vTrabajo] != 0)
		{
			new Coche;
			Coche = CreateVehicle(InfoVehiculo[id][vModelo], InfoVehiculo[id][vPosicionX], InfoVehiculo[id][vPosicionY], InfoVehiculo[id][vPosicionZ], InfoVehiculo[id][vPosicionR], InfoVehiculo[id][vColor_1], InfoVehiculo[id][vColor_2], -1, InfoVehiculo[id][vSirena]);
			InfoVehiculo[id][vIG_id] = Coche;
			InfoVehiculo[id][vSpawned] = 1;
			InfoVehiculo[id][vTimeSave] = 0;
			veh_gasolina[Coche] = InfoVehiculo[id][vGasolina];
			if (InfoVehiculo[id][vModelo] == 528 || InfoVehiculo[id][vModelo] == 427) SetVehicleHealth(Coche, 5000.0);
			else SetVehicleHealth(Coche, InfoVehiculo[id][vVida]);
			SetVehicleInterior(Coche, InfoVehiculo[id][vInterior]);
			SetVehicleExVirtualWorld(Coche, InfoVehiculo[id][vVirtualWorld]);
			SetVehicleMatricula(Coche);
			UpdateVehicleDamageStatus(Coche, InfoVehiculo[id][vDanioSuperficie], InfoVehiculo[id][vDanioPuertas], InfoVehiculo[id][vDanioLuces], InfoVehiculo[id][vDanioRuedas]);
			if (InfoVehiculo[id][vSeguro] != 0) LockPlayerVehicle(Coche);
			Load_Mods(id);
			if (!isnull(InfoVehiculo[id][vCallSign]))
			{
				if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
				{
					DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
					InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
				}
				InfoVehiculo[id][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[id][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, Coche);
			}
		}
	}
	//printf("|- %d vehículos dinámicos (SQL: %d) cargados.", cargaditos, totalvehiculos-1);
	return 1;
}


forward vehiculos_legales(vehicleid);
public vehiculos_legales(vehicleid) //vehicleid legales
{
	if (Vehiculo_LSPD(vehicleid) || Vehiculo_FBI(vehicleid) || Vehiculo_USMC(vehicleid) || Vehiculo_LSCSD(vehicleid) || Vehiculo_GOB(vehicleid) ||
	Vehiculo_LSFD(vehicleid) || Vehiculo_SADOC(vehicleid))
	{
		return 1;
	}
	return 0;
}

public OnVehicleDeath(vehicleid)
{
	alm(veh_music[vehicleid], "nadauwu");
	LockStatus[vehicleid] = 0;
	new VehV = verificar_id_vehiculo(vehicleid);
	if (VehV != -1)
	{
		Loop(x, 5, 0) if (InfoVehiculo[VehV][vObjModelo][x] != 0)
		{
			if (IsValidDynamicObject(InfoVehiculo[VehV][vTuneo][x])) DestroyDynamicObject(InfoVehiculo[VehV][vTuneo][x]);
			InfoVehiculo[VehV][vTuneo][x] = 0;
		}
	}
    arr_Engine{vehicleid} = 0;
  	return 1;
}

forward llenando_gasolina(playerid, vehicleid);
public llenando_gasolina(playerid, vehicleid)
{
	if (!GetVehicleModel(vehicleid)) return 1;
	if (InfoCuenta[playerid][jVIP] == 0)
	{
		if (GetPlayerCash(playerid) < 115) { ShowInfoForPlayer(playerid, "No tienes 115 dolares."); return 1; }
		GivePlayerCash(playerid, -115, "servicio gasolina (bidon)");
	}
	veh_gasolina[vehicleid] = 100;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		InfoVehiculo[v][vGasolina] = veh_gasolina[vehicleid];
		guardar_int_mysql("vehiculos", "Gasolina", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vGasolina]);
		break;
	}
	rol_ame(playerid, "rellena el tanque de gasolina.");
	VehiculoGasolina[playerid] = 0;
	return 1;
}
forward CreateVehicleUser(id);
public CreateVehicleUser(id)
{
	totalvehiculos++;
	InfoVehiculo[id][vID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
forward ReproducirEstereo(playerid, music[]);
public ReproducirEstereo(playerid, music[])
{
	if(GetPVarType(playerid, "AreaVehPos"))
	{
		foreach(new i: Player)
		{
			if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "AreaVehMus")))
			{
				ReproducirMVeh(i, music, GetPVarFloat(playerid, "AreaVehPosX"), GetPVarFloat(playerid, "AreaVehPosY"), GetPVarFloat(playerid, "AreaVehPosZ"), 45.0, 1);
			}
		}
		SetPVarString(playerid, "AreaVehAud", music);
	}
	return 1;
}
