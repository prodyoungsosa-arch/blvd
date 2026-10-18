new totalcasas = 1;				//casas dinámicas
new DentroCasa[MAX_PLAYERS];
new VisitaTimer[MAX_PLAYERS];
new VisitaTimer2[MAX_PLAYERS];

enum casaInfo
{
	cID_sql,                            // id sql
	cPropietario[MAX_PLAYER_NAME],      // propietario
	cTipo,                              // tipo de clase
	cVenta,                             // 0 en venta, 1 comprado
	cSeguro,                            // 1 seguro, 0 sin seguro
	Float: cExteriorX,                  // pos x
	Float: cExteriorY,                  // pos y
	Float: cExteriorZ,                  // pos z
	Float: cExteriorR,                  // pos angulo
	cExteriorInt,                       // ext int
	cExteriorVW,                        // ext vw
	Float: cInteriorX,                  // int x
	Float: cInteriorY,                  // int y
	Float: cInteriorZ,                  // int z
	Float: cInteriorR,                  // int r
	cInteriorInt,                       // int int
	cInteriorVW,                        // int vw
	cDinero,                            // dinero
	cPrecio,                            // precio
	cArmario[10],                       // armario
	cArmarioCant[10],                   // armario cant
	cPremium,
	cTiempoDisponible,
	cCompartida1[MAX_PLAYER_NAME],
	cCompartida2[MAX_PLAYER_NAME],
	cCompartida3[MAX_PLAYER_NAME],
	//dynamic
	Text3D: cLabelExt,                  // label ext
	Text3D: cLabelInt,                  // label int
};
new InfoCasa[MAX_CASAS][casaInfo];

forward CargarCasas();
public CargarCasas()
{
	new cargaditos = 0;
	Loop(e, MAX_CASAS, 0)
	{
		alm(InfoCasa[e][cPropietario], "gobielno");
		alm(InfoCasa[e][cCompartida1], "none");
		alm(InfoCasa[e][cCompartida2], "none");
		alm(InfoCasa[e][cCompartida3], "none");
	}
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoCasa[id][cID_sql]);
		rebel_string(tabla, "Propietario", InfoCasa[id][cPropietario], MAX_PLAYER_NAME);
		rebel_int(tabla, "Tipo", InfoCasa[id][cTipo]);
		rebel_int(tabla, "Venta", InfoCasa[id][cVenta]);
		rebel_int(tabla, "Seguro", InfoCasa[id][cSeguro]);
		rebel_float(tabla, "Exterior_X", InfoCasa[id][cExteriorX]);
		rebel_float(tabla, "Exterior_Y", InfoCasa[id][cExteriorY]);
		rebel_float(tabla, "Exterior_Z", InfoCasa[id][cExteriorZ]);
		rebel_float(tabla, "Exterior_R", InfoCasa[id][cExteriorR]);
		rebel_int(tabla, "Exterior_Int", InfoCasa[id][cExteriorInt]);
		rebel_int(tabla, "Exterior_VW", InfoCasa[id][cExteriorVW]);
		rebel_float(tabla, "Interior_X", InfoCasa[id][cInteriorX]);
		rebel_float(tabla, "Interior_Y", InfoCasa[id][cInteriorY]);
		rebel_float(tabla, "Interior_Z", InfoCasa[id][cInteriorZ]);
		rebel_float(tabla, "Interior_R", InfoCasa[id][cInteriorR]);
		rebel_int(tabla, "Interior_Int", InfoCasa[id][cInteriorInt]);
		rebel_int(tabla, "Interior_VW", InfoCasa[id][cInteriorVW]);
		rebel_int(tabla, "BolosUwU", InfoCasa[id][cDinero]);
		rebel_int(tabla, "Precio", InfoCasa[id][cPrecio]);
		rebel_int(tabla, "Armario1", InfoCasa[id][cArmario][0]);
		rebel_int(tabla, "ArmarioCant1", InfoCasa[id][cArmarioCant][0]);
		rebel_int(tabla, "Armario2", InfoCasa[id][cArmario][1]);
		rebel_int(tabla, "ArmarioCant2", InfoCasa[id][cArmarioCant][1]);
		rebel_int(tabla, "Armario3", InfoCasa[id][cArmario][2]);
		rebel_int(tabla, "ArmarioCant3", InfoCasa[id][cArmarioCant][2]);
		rebel_int(tabla, "Armario4", InfoCasa[id][cArmario][3]);
		rebel_int(tabla, "ArmarioCant4", InfoCasa[id][cArmarioCant][3]);
		rebel_int(tabla, "Armario5", InfoCasa[id][cArmario][4]);
		rebel_int(tabla, "ArmarioCant5", InfoCasa[id][cArmarioCant][4]);
		rebel_int(tabla, "Armario6", InfoCasa[id][cArmario][5]);
		rebel_int(tabla, "ArmarioCant6", InfoCasa[id][cArmarioCant][5]);
		rebel_int(tabla, "Armario7", InfoCasa[id][cArmario][6]);
		rebel_int(tabla, "ArmarioCant7", InfoCasa[id][cArmarioCant][6]);
		rebel_int(tabla, "Armario8", InfoCasa[id][cArmario][7]);
		rebel_int(tabla, "ArmarioCant8", InfoCasa[id][cArmarioCant][7]);
		rebel_int(tabla, "Armario9", InfoCasa[id][cArmario][8]);
		rebel_int(tabla, "ArmarioCant9", InfoCasa[id][cArmarioCant][8]);
		rebel_int(tabla, "Armario10", InfoCasa[id][cArmario][9]);
		rebel_int(tabla, "ArmarioCant10", InfoCasa[id][cArmarioCant][9]);
		rebel_int(tabla, "Premium", InfoCasa[id][cPremium]);
		rebel_int(tabla, "TiempoDisponible", InfoCasa[id][cTiempoDisponible]);
		rebel_string(tabla, "Compartida1", InfoCasa[id][cCompartida1], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida2", InfoCasa[id][cCompartida2], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida3", InfoCasa[id][cCompartida3], MAX_PLAYER_NAME);
		if (InfoCasa[id][cID_sql]) totalcasas++;
		//función
		if (InfoCasa[id][cTipo] != 0)
		{
			LabelPickup_casa(id);
			cargaditos++;
		}
		else noexitcasa(id);
	}
	//printf("|- %d casas dinámicas (SQL: %d) cargadas.", cargaditos, totalcasas-1);
	return 1;
}