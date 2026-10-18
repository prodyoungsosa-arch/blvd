IsPlayerContrato(playerid, job)
{
	if (InfoPersonaje[playerid][pTrabajo1] == job) return 1;
	if (InfoPersonaje[playerid][pTrabajo2] == job) return 1;
	if (InfoPersonaje[playerid][pTrabajo3] == job) return 1;
	return 0;
}

GetNameContrato(job)
{
	new is_name[19];
	switch (job)
	{
		case 1: alm(is_name, "Disponible");
		case 2: alm(is_name, "Disponible");
		case 3: alm(is_name, "Disponible");
		case 4: alm(is_name, "Disponible");
		case 5: alm(is_name, "Disponible");
        case 6: alm(is_name, "Trailero");
        case 7: alm(is_name, "Disponible");
	}
	return is_name;
}