new totalcajeros = 1;

enum atmInfo
{
	atmID_sql,						// ID-DB
	atmModelo,						// Modelo
	atmDinero,						// Dinero
	Float: atmPotX,					// PotX
	Float: atmPotY,              	// PotY
	Float: atmPotZ,              	// PotZ
	Float: atmRotX,              	// RotX
	Float: atmRotY,              	// RotY
	Float: atmRotZ,              	// RotZ
	atmInterior,                 	// Interior
	atmVirtualWorld,             	// VirtualWorld
	atmObject,                   	// Objeto
	Text3D: atmLabel,            	// 3d label
};
new InfoCajero[MAX_CAJEROS][atmInfo];

forward CargarCajeros();
public CargarCajeros()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoCajero[id][atmID_sql]);
		rebel_int(tabla, "Modelo", InfoCajero[id][atmModelo]);
		rebel_int(tabla, "BolosUwU", InfoCajero[id][atmDinero]);
		rebel_float(tabla, "PotX", InfoCajero[id][atmPotX]);
		rebel_float(tabla, "PotY", InfoCajero[id][atmPotY]);
		rebel_float(tabla, "PotZ", InfoCajero[id][atmPotZ]);
		rebel_float(tabla, "RotX", InfoCajero[id][atmRotX]);
		rebel_float(tabla, "RotY", InfoCajero[id][atmRotY]);
		rebel_float(tabla, "RotZ", InfoCajero[id][atmRotZ]);
		rebel_int(tabla, "Interior", InfoCajero[id][atmInterior]);
		rebel_int(tabla, "VirtualWorld", InfoCajero[id][atmVirtualWorld]);
		if (InfoCajero[id][atmID_sql]) totalcajeros++;
		//función
		if (InfoCajero[id][atmPotX] != 0.0)
		{
			cargaditos++;
			Label_cajero(id, 1);
		}
	}
	//printf("|- %d cajeros automáticos (SQL: %d) cargados.", cargaditos, totalcajeros-1);
	return 1;
}