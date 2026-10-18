forward OnCasaCreate(cid);
public OnCasaCreate(cid)
{
	InfoCasa[cid][cID_sql] = cache_insert_id();
	cache_unset_active();
	totalcasas++;
    return 1;
}