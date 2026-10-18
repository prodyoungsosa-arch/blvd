forward CreatePlayerMochila(playerid, id);
public CreatePlayerMochila(playerid, id)
{
    InfoMochila[id][mjID] = cache_insert_id();
    cache_unset_active();
    InfoPersonaje[playerid][pManoDerecha] = 86;
    InfoPersonaje[playerid][pManoDerechaCant] = InfoMochila[id][mjID];
    PonerObjeto(playerid, 1, 86);
    new query[256];
    mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 55, Cantidad_mano_derecha = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
    mysql_tquery(db_samp, query);
    totalmochilas++;
    return 1;
}
