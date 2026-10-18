new totalcontenedores = 1;

// contenedores dinámicos en sql - abril 2022
enum contInfo
{
	contID_sql,						// ID-DB
	contModelo,						// Modelo
	Float: contPotX,				// PotX
	Float: contPotY,              	// PotY
	Float: contPotZ,              	// PotZ
	Float: contRotX,              	// RotX
	Float: contRotY,              	// RotY
	Float: contRotZ,              	// RotZ
	contInterior,                 	// Interior
	contVirtualWorld,             	// VirtualWorld
	contObject,                   	// Objeto
	Text3D: contLabel,            	// 3d label
	cInv[10],
	cInvCant[10],
};
new InfoContenedor[MAX_CONTENEDORES][contInfo];

forward CargarContenedores();
public CargarContenedores()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoContenedor[id][contID_sql]);
		rebel_int(tabla, "Modelo", InfoContenedor[id][contModelo]);
		rebel_float(tabla, "PotX", InfoContenedor[id][contPotX]);
		rebel_float(tabla, "PotY", InfoContenedor[id][contPotY]);
		rebel_float(tabla, "PotZ", InfoContenedor[id][contPotZ]);
		rebel_float(tabla, "RotX", InfoContenedor[id][contRotX]);
		rebel_float(tabla, "RotY", InfoContenedor[id][contRotY]);
		rebel_float(tabla, "RotZ", InfoContenedor[id][contRotZ]);
		rebel_int(tabla, "Interior", InfoContenedor[id][contInterior]);
		rebel_int(tabla, "VirtualWorld", InfoContenedor[id][contVirtualWorld]);
		if (InfoContenedor[id][contID_sql]) totalcontenedores++;
		//función
		if (InfoContenedor[id][contPotX] != 0.0)
		{
			cargaditos++;
			Label_contenedor(id, 1);
		}
	}
	//printf("Contenedores: (Total: %d) (SQL: %d)", cargaditos, totalcontenedores-1);
	return 1;
}
