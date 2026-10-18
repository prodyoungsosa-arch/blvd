forward OnActorCreate(id);
public OnActorCreate(id)
{
	InfoActor[id][aID_sql] = cache_insert_id();
	cache_unset_active();
	totalactores++;
    return 1;
}