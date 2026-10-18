new totalmochilas = 1;

enum m_info
{
    mjID,
    mjActivo,
    mjObjeto[10],
    mjObjetoCant[10],
};
new InfoMochila[MAX_MOCHILAS][m_info];

forward CargarMochilas();
public CargarMochilas()
{
    new cargaditos = 0;
    Loop(tabla, cache_num_rows(), 0)
    {
        new id = tabla+1;
        rebel_int(tabla, "ID", InfoMochila[id][mjID]);
        rebel_int(tabla, "Activo", InfoMochila[id][mjActivo]);
        rebel_int(tabla, "Obj1", InfoMochila[id][mjObjeto][0]);
        rebel_int(tabla, "ObjCant1", InfoMochila[id][mjObjetoCant][0]);
        rebel_int(tabla, "Obj2", InfoMochila[id][mjObjeto][1]);
        rebel_int(tabla, "ObjCant2", InfoMochila[id][mjObjetoCant][1]);
        rebel_int(tabla, "Obj3", InfoMochila[id][mjObjeto][2]);
        rebel_int(tabla, "ObjCant3", InfoMochila[id][mjObjetoCant][2]);
        rebel_int(tabla, "Obj4", InfoMochila[id][mjObjeto][3]);
        rebel_int(tabla, "ObjCant4", InfoMochila[id][mjObjetoCant][3]);
        rebel_int(tabla, "Obj5", InfoMochila[id][mjObjeto][4]);
        rebel_int(tabla, "ObjCant5", InfoMochila[id][mjObjetoCant][4]);
        rebel_int(tabla, "Obj6", InfoMochila[id][mjObjeto][5]);
        rebel_int(tabla, "ObjCant6", InfoMochila[id][mjObjetoCant][5]);
        rebel_int(tabla, "Obj7", InfoMochila[id][mjObjeto][6]);
        rebel_int(tabla, "ObjCant7", InfoMochila[id][mjObjetoCant][6]);
        rebel_int(tabla, "Obj8", InfoMochila[id][mjObjeto][7]);
        rebel_int(tabla, "ObjCant8", InfoMochila[id][mjObjetoCant][7]);
        rebel_int(tabla, "Obj9", InfoMochila[id][mjObjeto][8]);
        rebel_int(tabla, "ObjCant9", InfoMochila[id][mjObjetoCant][8]);
        rebel_int(tabla, "Obj10", InfoMochila[id][mjObjeto][9]);
        rebel_int(tabla, "ObjCant10", InfoMochila[id][mjObjetoCant][9]);
        if (InfoMochila[id][mjID]) totalmochilas++;
        cargaditos++;
    }
    //printf("Mochilas: (Total %d) (SQL: %d)", cargaditos, totalmochilas);
    return 1;
}