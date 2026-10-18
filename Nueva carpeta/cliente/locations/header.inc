new totalubicaciones = 1;			//ubicaciones

enum Ubicaciones
{
    gpsID_sql,
	uNombre[128],
	Float: uPosicion[3],
}
new InfoGPS[MAX_UBICACIONES][Ubicaciones];

forward CargarUbicaciones();
public CargarUbicaciones()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoGPS[id][gpsID_sql]);
		rebel_string(tabla, "Ubicacion", InfoGPS[id][uNombre], 128);
		rebel_float(tabla, "PotX", InfoGPS[id][uPosicion][0]);
		rebel_float(tabla, "PotY", InfoGPS[id][uPosicion][1]);
		rebel_float(tabla, "PotZ", InfoGPS[id][uPosicion][2]);
		if (InfoGPS[id][gpsID_sql]) totalubicaciones++;
		//función
		if (InfoGPS[id][uPosicion][0] != 0.0)
		{
			cargaditos++;
		}
	}
	//printf("|- %d ubicaciones dinámicas (SQL: %d) cargados.", cargaditos, totalubicaciones-1);
	return 1;
}