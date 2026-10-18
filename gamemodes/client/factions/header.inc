// Sistema facciones
new totalfacciones = 1;         //facciones dinámicas
new fac_rango[MAX_FACCIONES][15][32];
new TomandoTrabajo[MAX_PLAYERS];
new OnDuty[MAX_PLAYERS];
new ID_ACTUAL_FACUWU[MAX_PLAYERS];
new ID_ACTUAL_EquipoUWU[MAX_PLAYERS];

enum facInfo
{
	fID_sql,							// id sql
	fNombre[128],						// nombre
	fLogo[8],                           // logo
	fLider[MAX_PLAYER_NAME],			// líder
	fSubLider[MAX_PLAYER_NAME],         // sub líder
	fMensaje[256],						// mensaje
	fTipo,								// tipo
	fDinero,                            // dinero
	fSalario,							// salario
	fMaxRangos,                         // max de rangos
	Float: fSpawnX,						// spawn x
	Float: fSpawnY,						// spawn y
	Float: fSpawnZ,						// spawn z
	Float: fSpawnR,						// spawn r
	fSpawnInt,							// spawn int
	fSpawnVW,							// spawn vw
	Float: fArmarioX,					// armario x
	Float: fArmarioY,					// armario y
	Float: fArmarioZ,					// armario z
	fArmarioInt,						// armario int
	fArmarioVW,                         // armario vw
	fEquipo[20],						// objetos de equipo
	fRequiere[20],						// rango de equipo
	fSkin[20],							// skins de equipo
	fArmarioPickup,                     // armario pickup
	Text3D: fArmarioLabel,              // armario label
	fChat,
};
new InfoFaccion[MAX_FACCIONES][facInfo];

forward CargarFacciones();
public CargarFacciones()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoFaccion[id][fID_sql]);
		rebel_string(tabla, "Nombre", InfoFaccion[id][fNombre], 128);
		rebel_string(tabla, "Logo", InfoFaccion[id][fLogo], 8);
		rebel_string(tabla, "Lider", InfoFaccion[id][fLider], MAX_PLAYER_NAME);
		rebel_string(tabla, "SubLider", InfoFaccion[id][fSubLider], MAX_PLAYER_NAME);
		rebel_string(tabla, "Mensaje", InfoFaccion[id][fMensaje], 256);
		rebel_int(tabla, "Tipo", InfoFaccion[id][fTipo]);
		rebel_int(tabla, "BolosUwU", InfoFaccion[id][fDinero]);
		rebel_int(tabla, "Salario", InfoFaccion[id][fSalario]);
		rebel_int(tabla, "MaxRangos", InfoFaccion[id][fMaxRangos]);
		rebel_string(tabla, "Rango1", fac_rango[id][0], 32);
		rebel_string(tabla, "Rango2", fac_rango[id][1], 32);
		rebel_string(tabla, "Rango3", fac_rango[id][2], 32);
		rebel_string(tabla, "Rango4", fac_rango[id][3], 32);
		rebel_string(tabla, "Rango5", fac_rango[id][4], 32);
		rebel_string(tabla, "Rango6", fac_rango[id][5], 32);
		rebel_string(tabla, "Rango7", fac_rango[id][6], 32);
		rebel_string(tabla, "Rango8", fac_rango[id][7], 32);
		rebel_string(tabla, "Rango9", fac_rango[id][8], 32);
		rebel_string(tabla, "Rango10", fac_rango[id][9], 32);
		rebel_string(tabla, "Rango11", fac_rango[id][10], 32);
		rebel_string(tabla, "Rango12", fac_rango[id][11], 32);
		rebel_string(tabla, "Rango13", fac_rango[id][12], 32);
		rebel_string(tabla, "Rango14", fac_rango[id][13], 32);
		rebel_string(tabla, "Rango15", fac_rango[id][14], 32);
		rebel_float(tabla, "SpawnX", InfoFaccion[id][fSpawnX]);
		rebel_float(tabla, "SpawnY", InfoFaccion[id][fSpawnY]);
		rebel_float(tabla, "SpawnZ", InfoFaccion[id][fSpawnZ]);
		rebel_float(tabla, "SpawnR", InfoFaccion[id][fSpawnR]);
		rebel_int(tabla, "SpawnInt", InfoFaccion[id][fSpawnInt]);
		rebel_int(tabla, "SpawnVW", InfoFaccion[id][fSpawnVW]);
		rebel_float(tabla, "ArmarioX", InfoFaccion[id][fArmarioX]);
		rebel_float(tabla, "ArmarioY", InfoFaccion[id][fArmarioY]);
		rebel_float(tabla, "ArmarioZ", InfoFaccion[id][fArmarioZ]);
		rebel_int(tabla, "ArmarioInt", InfoFaccion[id][fArmarioInt]);
		rebel_int(tabla, "ArmarioVW", InfoFaccion[id][fArmarioVW]);
		rebel_int(tabla, "Equipo1", InfoFaccion[id][fEquipo][0]);
		rebel_int(tabla, "Equipo2", InfoFaccion[id][fEquipo][1]);
		rebel_int(tabla, "Equipo3", InfoFaccion[id][fEquipo][2]);
		rebel_int(tabla, "Equipo4", InfoFaccion[id][fEquipo][3]);
		rebel_int(tabla, "Equipo5", InfoFaccion[id][fEquipo][4]);
		rebel_int(tabla, "Equipo6", InfoFaccion[id][fEquipo][5]);
		rebel_int(tabla, "Equipo7", InfoFaccion[id][fEquipo][6]);
		rebel_int(tabla, "Equipo8", InfoFaccion[id][fEquipo][7]);
		rebel_int(tabla, "Equipo9", InfoFaccion[id][fEquipo][8]);
		rebel_int(tabla, "Equipo10", InfoFaccion[id][fEquipo][9]);
		rebel_int(tabla, "Equipo11", InfoFaccion[id][fEquipo][10]);
		rebel_int(tabla, "Equipo12", InfoFaccion[id][fEquipo][11]);
		rebel_int(tabla, "Equipo13", InfoFaccion[id][fEquipo][12]);
		rebel_int(tabla, "Equipo14", InfoFaccion[id][fEquipo][13]);
		rebel_int(tabla, "Equipo15", InfoFaccion[id][fEquipo][14]);
		rebel_int(tabla, "Equipo16", InfoFaccion[id][fEquipo][15]);
		rebel_int(tabla, "Equipo17", InfoFaccion[id][fEquipo][16]);
		rebel_int(tabla, "Equipo18", InfoFaccion[id][fEquipo][17]);
		rebel_int(tabla, "Equipo19", InfoFaccion[id][fEquipo][18]);
		rebel_int(tabla, "Equipo20", InfoFaccion[id][fEquipo][19]);
		rebel_int(tabla, "Requiere1", InfoFaccion[id][fRequiere][0]);
		rebel_int(tabla, "Requiere2", InfoFaccion[id][fRequiere][1]);
		rebel_int(tabla, "Requiere3", InfoFaccion[id][fRequiere][2]);
		rebel_int(tabla, "Requiere4", InfoFaccion[id][fRequiere][3]);
		rebel_int(tabla, "Requiere5", InfoFaccion[id][fRequiere][4]);
		rebel_int(tabla, "Requiere6", InfoFaccion[id][fRequiere][5]);
		rebel_int(tabla, "Requiere7", InfoFaccion[id][fRequiere][6]);
		rebel_int(tabla, "Requiere8", InfoFaccion[id][fRequiere][7]);
		rebel_int(tabla, "Requiere9", InfoFaccion[id][fRequiere][8]);
		rebel_int(tabla, "Requiere10", InfoFaccion[id][fRequiere][9]);
		rebel_int(tabla, "Requiere11", InfoFaccion[id][fRequiere][10]);
		rebel_int(tabla, "Requiere12", InfoFaccion[id][fRequiere][11]);
		rebel_int(tabla, "Requiere13", InfoFaccion[id][fRequiere][12]);
		rebel_int(tabla, "Requiere14", InfoFaccion[id][fRequiere][13]);
		rebel_int(tabla, "Requiere15", InfoFaccion[id][fRequiere][14]);
		rebel_int(tabla, "Requiere16", InfoFaccion[id][fRequiere][15]);
		rebel_int(tabla, "Requiere17", InfoFaccion[id][fRequiere][16]);
		rebel_int(tabla, "Requiere18", InfoFaccion[id][fRequiere][17]);
		rebel_int(tabla, "Requiere19", InfoFaccion[id][fRequiere][18]);
		rebel_int(tabla, "Requiere20", InfoFaccion[id][fRequiere][19]);
		rebel_int(tabla, "Skin1", InfoFaccion[id][fSkin][0]);
		rebel_int(tabla, "Skin2", InfoFaccion[id][fSkin][1]);
		rebel_int(tabla, "Skin3", InfoFaccion[id][fSkin][2]);
		rebel_int(tabla, "Skin4", InfoFaccion[id][fSkin][3]);
		rebel_int(tabla, "Skin5", InfoFaccion[id][fSkin][4]);
		rebel_int(tabla, "Skin6", InfoFaccion[id][fSkin][5]);
		rebel_int(tabla, "Skin7", InfoFaccion[id][fSkin][6]);
		rebel_int(tabla, "Skin8", InfoFaccion[id][fSkin][7]);
		rebel_int(tabla, "Skin9", InfoFaccion[id][fSkin][8]);
		rebel_int(tabla, "Skin10", InfoFaccion[id][fSkin][9]);
		rebel_int(tabla, "Skin11", InfoFaccion[id][fSkin][10]);
		rebel_int(tabla, "Skin12", InfoFaccion[id][fSkin][11]);
		rebel_int(tabla, "Skin13", InfoFaccion[id][fSkin][12]);
		rebel_int(tabla, "Skin14", InfoFaccion[id][fSkin][13]);
		rebel_int(tabla, "Skin15", InfoFaccion[id][fSkin][14]);
		rebel_int(tabla, "Skin16", InfoFaccion[id][fSkin][15]);
		rebel_int(tabla, "Skin17", InfoFaccion[id][fSkin][16]);
		rebel_int(tabla, "Skin18", InfoFaccion[id][fSkin][17]);
		rebel_int(tabla, "Skin19", InfoFaccion[id][fSkin][18]);
		rebel_int(tabla, "Skin20", InfoFaccion[id][fSkin][19]);
		if (InfoFaccion[id][fTipo]) cargaditos++;
		if (InfoFaccion[id][fID_sql]) totalfacciones++;
		if (InfoFaccion[id][fArmarioX] != 0.0) faccion_armario(id, 0);
		InfoFaccion[id][fChat] = 0;
	}
	//printf("|- %d facciones dinámicas (SQL: %d) cargadas.", cargaditos, totalfacciones-1);
	return 1;
}