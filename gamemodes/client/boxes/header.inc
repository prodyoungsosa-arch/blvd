new totalcajas = 1;

//info caja
enum j_info
{
	cjID,
	cjActivo,
	cjObjeto[10],
	cjObjetoCant[10],
};
new InfoCaja[MAX_CAJAS][j_info];

forward CargarCajas();
public CargarCajas()
{
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoCaja[id][cjID]);
		rebel_int(tabla, "Activo", InfoCaja[id][cjActivo]);
		rebel_int(tabla, "Obj1", InfoCaja[id][cjObjeto][0]);
		rebel_int(tabla, "ObjCant1", InfoCaja[id][cjObjetoCant][0]);
		rebel_int(tabla, "Obj2", InfoCaja[id][cjObjeto][1]);
		rebel_int(tabla, "ObjCant2", InfoCaja[id][cjObjetoCant][1]);
		rebel_int(tabla, "Obj3", InfoCaja[id][cjObjeto][2]);
		rebel_int(tabla, "ObjCant3", InfoCaja[id][cjObjetoCant][2]);
		rebel_int(tabla, "Obj4", InfoCaja[id][cjObjeto][3]);
		rebel_int(tabla, "ObjCant4", InfoCaja[id][cjObjetoCant][3]);
		rebel_int(tabla, "Obj5", InfoCaja[id][cjObjeto][4]);
		rebel_int(tabla, "ObjCant5", InfoCaja[id][cjObjetoCant][4]);
		rebel_int(tabla, "Obj6", InfoCaja[id][cjObjeto][5]);
		rebel_int(tabla, "ObjCant6", InfoCaja[id][cjObjetoCant][5]);
		rebel_int(tabla, "Obj7", InfoCaja[id][cjObjeto][6]);
		rebel_int(tabla, "ObjCant7", InfoCaja[id][cjObjetoCant][6]);
		rebel_int(tabla, "Obj8", InfoCaja[id][cjObjeto][7]);
		rebel_int(tabla, "ObjCant8", InfoCaja[id][cjObjetoCant][7]);
		rebel_int(tabla, "Obj9", InfoCaja[id][cjObjeto][8]);
		rebel_int(tabla, "ObjCant9", InfoCaja[id][cjObjetoCant][8]);
		rebel_int(tabla, "Obj10", InfoCaja[id][cjObjeto][9]);
		rebel_int(tabla, "ObjCant10", InfoCaja[id][cjObjetoCant][9]);
		if (InfoCaja[id][cjID]) totalcajas++;
		cargaditos++;
	}
	//printf("Cajas: (Total: %d) (SQL: %d)", cargaditos, totalcajas);
	return 1;
}