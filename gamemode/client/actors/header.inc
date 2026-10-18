new totalactores = 1;
enum actorInfo
{
	aID_sql,						// id sql
	aNombre[MAX_PLAYER_NAME],       // nombre
	aSkin,                          // skin
	Float: aPosX,                   // pos x
	Float: aPosY,                   // pos y
	Float: aPosZ,                   // pos z
	Float: aPosR,                   // pos r
	aInterior,                      // interior
	aVirtualWorld,                  // virtualworld
	aAnimacion,                     // animación id
	aID_ig,                         // id ig
	Text3D: aLabel,                 // label
	aTipo,							// Tipo
}
new InfoActor[MAX_ACTORES][actorInfo];

forward CargarActores();
public CargarActores()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoActor[id][aID_sql]);
		rebel_string(tabla, "Nombre", InfoActor[id][aNombre], MAX_PLAYER_NAME);
		rebel_int(tabla, "Skin", InfoActor[id][aSkin]);
		rebel_float(tabla, "PosX", InfoActor[id][aPosX]);
		rebel_float(tabla, "PosY", InfoActor[id][aPosY]);
		rebel_float(tabla, "PosZ", InfoActor[id][aPosZ]);
		rebel_float(tabla, "PosR", InfoActor[id][aPosR]);
		rebel_int(tabla, "Interior", InfoActor[id][aInterior]);
		rebel_int(tabla, "VirtualWorld", InfoActor[id][aVirtualWorld]);
		rebel_int(tabla, "Animacion", InfoActor[id][aAnimacion]);
		rebel_int(tabla, "Tipo", InfoActor[id][aTipo]);
		if (InfoActor[id][aID_sql]) totalactores++;
		//funcion
		if (InfoActor[id][aPosX] != 0.0)
		{
			Dynamic_actor(id);
			cargaditos++;
		}
	}
	return 1;
}