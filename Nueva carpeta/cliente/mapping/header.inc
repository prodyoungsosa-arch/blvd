new totalobjetosadmin = 1;

enum oInfo
{
	oID_sql,			// ID-DB
	oModelo,			// Modelo
	Float: oPotX,		// PotX
	Float: oPotY,		// PotY
	Float: oPotZ,		// PotZ
	Float: oRotX,		// RotX
	Float: oRotY,		// RotY
	Float: oRotZ,		// RotZ
	oInterior,			// Interior
	oVirtualWorld,		// VirtualWorld
	oObjeto,			// Objeto
};
new InfoObjeto[MAX_OBJETOS_ADMIN][oInfo];

forward CargarObjetosAdmin();
public CargarObjetosAdmin()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoObjeto[id][oID_sql]);
		rebel_int(tabla, "Modelo", InfoObjeto[id][oModelo]);
		rebel_float(tabla, "PotX", InfoObjeto[id][oPotX]);
		rebel_float(tabla, "PotY", InfoObjeto[id][oPotY]);
		rebel_float(tabla, "PotZ", InfoObjeto[id][oPotZ]);
		rebel_float(tabla, "RotX", InfoObjeto[id][oRotX]);
		rebel_float(tabla, "RotY", InfoObjeto[id][oRotY]);
		rebel_float(tabla, "RotZ", InfoObjeto[id][oRotZ]);
		rebel_int(tabla, "Interior", InfoObjeto[id][oInterior]);
		rebel_int(tabla, "VirtualWorld", InfoObjeto[id][oVirtualWorld]);
		if (InfoObjeto[id][oID_sql]) totalobjetosadmin++;
		//función
		if (InfoObjeto[id][oPotX] != 0.0)
		{
			cargaditos++;
			InfoObjeto[id][oObjeto] = CreateDynamicObject(InfoObjeto[id][oModelo], InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ], InfoObjeto[id][oRotX], InfoObjeto[id][oRotY], InfoObjeto[id][oRotZ], .interiorid = InfoObjeto[id][oInterior], .worldid = InfoObjeto[id][oVirtualWorld]);
		}
	}
	//printf("|- %d objetos dinámicos (SQL: %d) cargados.", cargaditos, totalobjetosadmin-1);
	return 1;
}