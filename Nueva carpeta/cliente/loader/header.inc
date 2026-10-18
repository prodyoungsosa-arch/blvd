SanAndreas()
{
	for(new i; i < MAX_PLANTAS; i++) Planta[i][sID] = -1;
	
	CreateTextDraws();
    Actores();
	CargarPeajes();

	//talleres
	CreateDynamicMapIcon(1981.1217, -2061.6235, 13.4121, 63, 0, 0, 0, -1, 500.0);
	CreateDynamicMapIcon(1471.9691, -1495.3605, 13.6370, 63, 0, 0, 0, -1, 500.0);
	CreateDynamicMapIcon(2354.3213, -1369.8083, 24.1138, 63, 0, 0, 0, -1, 500.0);
	CreateDynamicMapIcon(1830.2946, -1401.7294, 13.4792, 63, 0, 0, 0, -1, 500.0);
	CreateDynamicMapIcon(1004.9277, -1439.2111, 13.6102, 63, 0, 0, 0, -1, 500.0);
	CreateDynamic3DTextLabel("Utiliza {3E62F4}/taller{EBEBEB} para acceder al menú", 0xEBEBEBFF, 1981.1217, -2061.6235, 13.4121, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
	CreateDynamic3DTextLabel("Utiliza {3E62F4}/taller{EBEBEB} para acceder al menú", 0xEBEBEBFF, 1471.9691, -1495.3605, 13.6370, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
	CreateDynamic3DTextLabel("Utiliza {3E62F4}/taller{EBEBEB} para acceder al menú", 0xEBEBEBFF, 2354.3213, -1369.8083, 24.1138, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
	CreateDynamic3DTextLabel("Utiliza {3E62F4}/taller{EBEBEB} para acceder al menú", 0xEBEBEBFF, 1830.2946, -1401.7294, 13.4792, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
	CreateDynamic3DTextLabel("Utiliza {3E62F4}/taller{EBEBEB} para acceder al menú", 0xEBEBEBFF, 1004.9277, -1439.2111, 13.6102, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);

	// 3d label's
	CreateDynamic3DTextLabel("Para reparaciones o arrestos\nEscribe {3E62F4}/gtaller{EBEBEB} y {3E62F4}/arrestar{EBEBEB} aquí", 0xEBEBEBFF, -807.5030, -1755.6345, 46.5406, 8.0, .worldid = -1, .interiorid = 5); // gtaller
	CreateDynamicPickup(1366, 1, -807.5030, -1755.6345, 46.5406); // gtaller

	CreateDynamic3DTextLabel("Adquiere un botiquin por {3E62F4}$227{EBEBEB}\nEscribe {3E62F4}/comprarbotiquin{EBEBEB} aquí", 0xEBEBEBFF, 1163.0784, -1323.8208, 1015.4130, 8.0, .worldid = -1, .interiorid = 61); // comprarbotiquin
	CreateDynamicPickup(11738, 1, 1163.0784, -1323.8208, 1015.4130); // comprarbotiquin

	//mercado negro
	CreateDynamic3DTextLabel("Mercado negro\nUtiliza: {3E62F4}/mccomprar{EBEBEB}",			0xEBEBEBFF, 1296.2917,-989.3190,32.6953,8.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1,0,0);

	//Comandos
	CreateDynamic3DTextLabel("Depósito\nUtiliza {3E62F4}/embargar{EBEBEB}", 							                                                 COLOR_WHITE, 1636.041259,-1811.950317,13.524469+0.6, 10.0);
	CreateDynamic3DTextLabel("Multas\nUtiliza {3E62F4}/pagarm{EBEBEB}", 					                  								 COLOR_WHITE, 240.4770,112.7777,1003.2188+0.6, 8.0); // Pagar Multas MAP LSPD.
	CreateDynamic3DTextLabel("Multas\nUtiliza {3E62F4}/pagarm{EBEBEB}", 					                  								 COLOR_WHITE, 358.2679,182.0734,1008.3828, 8.0); // Pagar Multas DGT.
	CreateDynamic3DTextLabel("Deseas vender tú coche\nUtiliza {3E62F4}/vendercoche{EBEBEB}.",                                                COLOR_WHITE, 358.2679,186.2302,1008.3828, 8.0); // /vendercoche.

	CreateDynamic3DTextLabel("Para aprender algún estilo de pelea\nUtiliza {3E62F4}/estilopelea{EBEBEB}",                                        COLOR_WHITE, 767.6719,13.6320,1000.7010,8.0); //GYM LS
	CreateDynamic3DTextLabel("Para aprender algún estilo de pelea\nUtiliza {3E62F4}/estilopelea{EBEBEB}",                                        COLOR_WHITE, 769.00,-47.39,1000.59,8.0); // GYM SF
	CreateDynamic3DTextLabel("Para adquirir licencias\nUtiliza {3E62F4}/comprarlicencia{EBEBEB}", 			                     			 COLOR_WHITE, 1561.7712,-1673.9811,2110.5364, 7.5); // /comprarlicencias UNI

	//otros
	CreateDynamic3DTextLabel("Banco Central de Los Santos\nUtiliza {3E62F4}/banco{EBEBEB}",	0xEBEBEBFF, -983.8863, 1448.5732, 1340.6270, 8.0);
	CreateDynamicPickup(1239, 1, -983.8863, 1448.5732, 1340.6270);

	//LSPD
	depositoembargo = CreateDynamicObject(980, 1620.6500244,-1861.5996094,15.3000002,0.0000000,0.0000000,179.9945068); //object(airportgate) (3)

	//comandos
	CreateDynamicPickup(1239, 1, 240.4770, 112.7777, 1003.2188); // Pagar Multas LS
	CreateDynamicPickup(1240, 1, 1636.041259, -1811.950317, 13.524469); // Embargar
	CreateDynamicPickup(1252, 1, 1628.361938, -1808.970458, 13.521308); // / Gasolinera única - Depósito.
	CreateDynamicPickup(1252, 1, 1880.558105, -2304.451660, 14.119070); // / Gasolinera única - Aeropuerto.
	CreateDynamicPickup(1239, 1, 767.6719, 13.6320, 1000.7010); // GYM LS	
	return 1;
}