new totalgraffitis = 1;

enum grInfo
{
	grID_sql,						// id db
	gr_Mensaje[256],                // mensaje
	gr_Creador[MAX_PLAYER_NAME],    // creador
	gr_Fecha,                       // fecha de creación
	Float: gr_PosX,					// potX
	Float: gr_PosY,					// potY
	Float: gr_PosZ,					// potZ
	Float: gr_RotX,					// rotX
	Float: gr_RotY,					// rotY
	Float: gr_RotZ,					// rotZ
	gr_Interior,					// interior
	gr_VirtualWorld,				// virtualWorld
	gr_Objeto,                      // objeto
};
new InfoGraffiti[MAX_GRAFFITIS][grInfo];

forward CargarGraffitis();
public CargarGraffitis()
{
	//clear
	Loop(x, MAX_GRAFFITIS, 0)
	{
		alm(InfoGraffiti[x][gr_Mensaje], "ninguno");
		alm(InfoGraffiti[x][gr_Creador], "ninguno");
		InfoGraffiti[x][gr_Fecha] = 0;
		InfoGraffiti[x][gr_PosX] = 0.0;
		InfoGraffiti[x][gr_PosY] = 0.0;
		InfoGraffiti[x][gr_PosZ] = 0.0;
		InfoGraffiti[x][gr_RotX] = 0.0;
		InfoGraffiti[x][gr_RotY] = 0.0;
		InfoGraffiti[x][gr_RotZ] = 0.0;
	}
	new cargaditos = 0, pintados = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoGraffiti[id][grID_sql]);
		rebel_string(tabla, "Mensaje", InfoGraffiti[id][gr_Mensaje], 256);
		rebel_string(tabla, "Creador", InfoGraffiti[id][gr_Creador], MAX_PLAYER_NAME);
		rebel_int(tabla, "Fecha", InfoGraffiti[id][gr_Fecha]);
		rebel_float(tabla, "PotX", InfoGraffiti[id][gr_PosX]);
		rebel_float(tabla, "PotY", InfoGraffiti[id][gr_PosY]);
		rebel_float(tabla, "PotZ", InfoGraffiti[id][gr_PosZ]);
		rebel_float(tabla, "RotX", InfoGraffiti[id][gr_RotX]);
		rebel_float(tabla, "RotY", InfoGraffiti[id][gr_RotY]);
		rebel_float(tabla, "RotZ", InfoGraffiti[id][gr_RotZ]);
		rebel_int(tabla, "Interior", InfoGraffiti[id][gr_Interior]);
		rebel_int(tabla, "VirtualWorld", InfoGraffiti[id][gr_VirtualWorld]);
		if (InfoGraffiti[id][grID_sql]) totalgraffitis++;
		//función
		if (InfoGraffiti[id][gr_PosX] != 0.0)
		{
			if (!strcmp(InfoGraffiti[id][gr_Creador], "ninguno", true))
			{
				InfoGraffiti[id][gr_Objeto] = CreateDynamicObject(18665, InfoGraffiti[id][gr_PosX], InfoGraffiti[id][gr_PosY], InfoGraffiti[id][gr_PosZ], InfoGraffiti[id][gr_RotX], InfoGraffiti[id][gr_RotY], InfoGraffiti[id][gr_RotZ], -1, 0, -1, 6000.0);
			}
			else
			{
				InfoGraffiti[id][gr_Objeto] = CreateDynamicObject(18665, InfoGraffiti[id][gr_PosX], InfoGraffiti[id][gr_PosY], InfoGraffiti[id][gr_PosZ], InfoGraffiti[id][gr_RotX], InfoGraffiti[id][gr_RotY], InfoGraffiti[id][gr_RotZ], -1, 0, -1, 6000.0);
				new graffitiText[128];
				alm(graffitiText, InfoGraffiti[id][gr_Mensaje]);
				strreplace(graffitiText, "(n)", "\n");
				strreplace(graffitiText, "(a)", "{0000FF}"); //azul
				strreplace(graffitiText, "(b)", "{FFFFFF}"); //blanco
				strreplace(graffitiText, "(am)", "{FFFF00}"); //amarillo
				strreplace(graffitiText, "(v)", "{00C200}"); //verde
				strreplace(graffitiText, "(ne)", "{000000}"); //negro
				strreplace(graffitiText, "(na)", "{FFBF00}"); //naranja
				strreplace(graffitiText, "(r)", "{FF0000}"); //rojo
				strreplace(graffitiText, "(ce)", "{00FFFF}"); //celeste
				SetDynamicObjectMaterialText(InfoGraffiti[id][gr_Objeto], 0, graffitiText, OBJECT_MATERIAL_SIZE_256x256, "Arial", 32, 1, 0xFFFFFFFF, 0, 1);
				pintados++;
			}
			cargaditos++;
		}
	}
	//printf("Graffitis: (Total: %d) (Pintados: %d) (SQL: %d)", cargaditos, pintados, totalgraffitis-1);
	return 1;
}
