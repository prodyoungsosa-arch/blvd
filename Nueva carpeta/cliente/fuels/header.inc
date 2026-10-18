new totalgasolinas = 1;	

enum gsInfo
{
	gsID_sql,					// ID-DB
	Float: gsPotX,				// PotX
	Float: gsPotY,              // PotY
	Float: gsPotZ,              // PotZ
	gsInterior,                 // Interior
	gsVirtualWorld,             // VirtualWorld
	Text3D: gsLabel,			// 3d label
};
new InfoBidon[MAX_GASOLINERAS][gsInfo];

forward CargarBidones();
public CargarBidones()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoBidon[id][gsID_sql]);
		rebel_float(tabla, "PotX", InfoBidon[id][gsPotX]);
		rebel_float(tabla, "PotY", InfoBidon[id][gsPotY]);
		rebel_float(tabla, "PotZ", InfoBidon[id][gsPotZ]);
		rebel_int(tabla, "Interior", InfoBidon[id][gsInterior]);
		rebel_int(tabla, "VirtualWorld", InfoBidon[id][gsVirtualWorld]);
		if (InfoBidon[id][gsID_sql]) totalgasolinas++;
		//función
		if (InfoBidon[id][gsPotX] != 0.0)
		{
			cargaditos++;
			new query[190];
			format(query, sizeof query, "Punto de gasolina (%d), escribe {3E62F4}/llenar{EBEBEB} aquí.", id);
			InfoBidon[id][gsLabel] = CreateDynamic3DTextLabel(query, 0xEBEBEBFF, InfoBidon[id][gsPotX], InfoBidon[id][gsPotY], InfoBidon[id][gsPotZ], 12.0, .interiorid = InfoBidon[id][gsInterior], .worldid = InfoBidon[id][gsVirtualWorld]);
		}
	}
	//printf("|- %d puntos de bidones dinámicos (SQL: %d) cargados.", cargaditos, totalgasolinas-1);
	return 1;
}