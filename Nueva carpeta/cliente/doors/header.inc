new totalpuertas = 1;

enum puertaInfo
{
	pdID_sql,                   // id sql
	pdNombre[128],              // nombre
	Float: pdExteriorX,         // exterior x
	Float: pdExteriorY,         // exterior y
	Float: pdExteriorZ,         // exterior z
	Float: pdExteriorR,         // exterior r
	pdExteriorInt,              // exterior int
	pdExteriorVW,               // exterior vw
	Float: pdInteriorX,         // interior x
	Float: pdInteriorY,         // interior y
	Float: pdInteriorZ,         // interior z
	Float: pdInteriorR,         // interior r
	pdInteriorInt,              // interior int
	pdInteriorVW,               // interior vw
	pdModelo,                   // modelo pickup
	pdMapIcon,					// modelo mapicon
	pdFaccion,                  // facción
	pdAdmin,                    // admin
	pdVIP,                      // vip
	pdEstrellas,                // estrellas
	pdStatusVehiculo,           // status vehículo
	//dynamic
	pdExteriorPickup,           // exterior pickup
	Text3D: pdExteriorLabel,    // exterior label
	pdExteriorMapIcon,          // exterior mapicon
	pdInteriorPickup,           // interior pickup
	Text3D: pdInteriorLabel,    // interior label
};
new InfoPuerta[MAX_PUERTAS][puertaInfo];

forward CargarPuertas();
public CargarPuertas()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoPuerta[id][pdID_sql]);
		rebel_string(tabla, "Nombre", InfoPuerta[id][pdNombre], 128);
		rebel_float(tabla, "ExteriorX", InfoPuerta[id][pdExteriorX]);
		rebel_float(tabla, "ExteriorY", InfoPuerta[id][pdExteriorY]);
		rebel_float(tabla, "ExteriorZ", InfoPuerta[id][pdExteriorZ]);
		rebel_float(tabla, "ExteriorR", InfoPuerta[id][pdExteriorR]);
		rebel_int(tabla, "ExteriorInt", InfoPuerta[id][pdExteriorInt]);
		rebel_int(tabla, "ExteriorVW", InfoPuerta[id][pdExteriorVW]);
		rebel_float(tabla, "InteriorX", InfoPuerta[id][pdInteriorX]);
		rebel_float(tabla, "InteriorY", InfoPuerta[id][pdInteriorY]);
		rebel_float(tabla, "InteriorZ", InfoPuerta[id][pdInteriorZ]);
		rebel_float(tabla, "InteriorR", InfoPuerta[id][pdInteriorR]);
		rebel_int(tabla, "InteriorInt", InfoPuerta[id][pdInteriorInt]);
		rebel_int(tabla, "InteriorVW", InfoPuerta[id][pdInteriorVW]);
		rebel_int(tabla, "Modelo", InfoPuerta[id][pdModelo]);
		rebel_int(tabla, "MapIcon", InfoPuerta[id][pdMapIcon]);
		rebel_int(tabla, "Faccion", InfoPuerta[id][pdFaccion]);
		rebel_int(tabla, "Admin", InfoPuerta[id][pdAdmin]);
		rebel_int(tabla, "VIP", InfoPuerta[id][pdVIP]);
		rebel_int(tabla, "Estrellas", InfoPuerta[id][pdEstrellas]);
		rebel_int(tabla, "StatusVehiculo", InfoPuerta[id][pdStatusVehiculo]);
		if (InfoPuerta[id][pdID_sql]) totalpuertas++;
		//función
		if (InfoPuerta[id][pdExteriorX] != 0.0)
		{
			cargaditos++;
			CreateDynamicDoor(id, 1);
		} else noexitDoor(id);
	}
	//printf("|- %d puertas dinámicas (SQL: %d) cargadas.", cargaditos, totalpuertas-1);
	return 1;
}