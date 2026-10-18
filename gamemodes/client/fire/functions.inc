stock CreateFireGeneral(houseid, tipo, create, a = -1)
{
	new intensidad = random(40)+10;
	if (create != 0)
	{
		if (tipo == 0)
		{
			InfoIncendio[a][pI_tipo] = 0;
			InfoIncendio[a][pI_intensidad] = intensidad;
			InfoIncendio[a][pI_propiedad] = houseid;
			InfoIncendio[a][pI_objeto][14] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][13] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][12] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][11] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][10] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][9] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][8] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][7] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][6] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][5] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][4] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][3] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][2] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][1] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][0] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
		}
		else if (tipo == 1)
		{
			InfoIncendio[a][pI_tipo] = 1;
			InfoIncendio[a][pI_intensidad] = intensidad;
			InfoIncendio[a][pI_propiedad] = houseid;
			InfoIncendio[a][pI_objeto][14] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][13] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][12] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][11] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][10] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][9] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][8] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][7] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][6] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][5] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][4] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][3] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][2] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][1] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoIncendio[a][pI_objeto][0] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			InfoNegocio[houseid][EnLlamas] = 1;
			InfoNegocio[houseid][nSeguro] = 1;
			guardar_int_mysql("negocios", "Seguro", InfoNegocio[houseid][nID_sql], InfoNegocio[houseid][nSeguro]);
			Labelupdate_negocio(houseid);
			TallerOpened(houseid, InfoNegocio[houseid][nSeguro]);
		}
	}
	else
	{
		Loop(id, MAX_INCENDIOS, 1) if (InfoIncendio[id][pI_propiedad] == -1)
		{
			if (tipo == 0)
			{
				InfoIncendio[id][pI_tipo] = 0;
				InfoIncendio[id][pI_intensidad] = intensidad;
				InfoIncendio[id][pI_propiedad] = houseid;
				InfoIncendio[id][pI_objeto][14] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][13] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][12] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][11] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][10] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][9] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][8] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][7] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][6] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][5] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][4] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][3] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX], InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][2] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY], InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][1] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] + 2, InfoCasa[houseid][cExteriorY] + 2, InfoCasa[houseid][cExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][0] = CreateDynamicObject(18691, InfoCasa[houseid][cExteriorX] - 2, InfoCasa[houseid][cExteriorY] - 2, InfoCasa[houseid][cExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
			}
			else if (tipo == 1)
			{
				InfoIncendio[id][pI_tipo] = 1;
				InfoIncendio[id][pI_intensidad] = intensidad;
				InfoIncendio[id][pI_propiedad] = houseid;
				InfoIncendio[id][pI_objeto][14] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][13] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][12] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][11] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][10] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][9] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][8] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][7] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][6] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][5] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][4] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ], 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][3] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX], InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][2] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY], InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][1] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] + 2, InfoNegocio[houseid][nExteriorY] + 2, InfoNegocio[houseid][nExteriorZ] + 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoIncendio[id][pI_objeto][0] = CreateDynamicObject(18691, InfoNegocio[houseid][nExteriorX] - 2, InfoNegocio[houseid][nExteriorY] - 2, InfoNegocio[houseid][nExteriorZ] - 2, 0.0, 0.0, 0.0, 0, 0, -1, 550.0, 550.0);
				InfoNegocio[houseid][EnLlamas] = 1;
				InfoNegocio[houseid][nSeguro] = 1;
				guardar_int_mysql("negocios", "Seguro", InfoNegocio[houseid][nID_sql], InfoNegocio[houseid][nSeguro]);
				Labelupdate_negocio(houseid);
				TallerOpened(houseid, InfoNegocio[houseid][nSeguro]);
			}
			//opción idsql ya creada.
			new query[195];
			if (InfoIncendio[id][pI_IDsql] != 0)
			{
				mysql_format(db_samp, query, sizeof query, "UPDATE incendios SET Tipo = '%d', Propiedad = '%d' WHERE ID = '%d'", InfoIncendio[id][pI_tipo], InfoIncendio[id][pI_propiedad], InfoIncendio[id][pI_IDsql]);
				mysql_tquery(db_samp, query);
				id = MAX_INCENDIOS;
				return 1;
			}
			mysql_format(db_samp, query, sizeof query, "INSERT INTO incendios (Tipo, Propiedad) VALUES ('%d', '%d')", InfoIncendio[id][pI_tipo], InfoIncendio[id][pI_propiedad]);
			mysql_tquery(db_samp, query, "OnIncendioCreate", "i", id);
			id = MAX_INCENDIOS;
		}
	}
	return 0;
}
