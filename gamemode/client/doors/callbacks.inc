forward OnPuertaCreate(id);
public OnPuertaCreate(id)
{
	InfoPuerta[id][pdID_sql] = cache_insert_id();
	cache_unset_active();
	totalpuertas++;
    return 1;
}