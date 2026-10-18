forward OnGasolinaCreate(id);
public OnGasolinaCreate(id)
{
	InfoBidon[id][gsID_sql] = cache_insert_id();
	cache_unset_active();
	totalgasolinas++;
    return 1;
}
