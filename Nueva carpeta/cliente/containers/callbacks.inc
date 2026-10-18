forward OnContenedorCreate(id);
public OnContenedorCreate(id)
{
	InfoContenedor[id][contID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
