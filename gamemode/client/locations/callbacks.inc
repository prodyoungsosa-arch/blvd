forward OnUbicacionCreate(id);
public OnUbicacionCreate(id)
{
	InfoGPS[id][gpsID_sql] = cache_insert_id();
	cache_unset_active();
    return 1;
}
