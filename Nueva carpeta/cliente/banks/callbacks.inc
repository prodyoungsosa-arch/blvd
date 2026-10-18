forward OnCajeroCreate(id);
public OnCajeroCreate(id)
{
	InfoCajero[id][atmID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
