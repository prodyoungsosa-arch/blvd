forward OnObjetoAdminCreate(id);
public OnObjetoAdminCreate(id)
{
	InfoObjeto[id][oID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
