forward ProvocarIncendio(playerid, tipo, id);
public ProvocarIncendio(playerid, tipo, id)
{
	new location[MAX_ZONE_NAME], gformat[256];
	if (tipo == 1) //casa
	{
		Get2DZone(location, MAX_ZONE_NAME, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]);
		format(gformat, sizeof gformat, "[CENTRAL] Se registró un nuevo incendio en la casa #%d en %s.", id, location);
		SendRadioMessage(6, COLOR_RADIO, gformat, 1);
		CreateFireGeneral(id, 0, 0);
	}
	else if (tipo == 2) //negocio
	{
		Get2DZone(location, MAX_ZONE_NAME, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]);
		format(gformat, sizeof gformat, "[CENTRAL] Se registró un nuevo incendio en el negocio '%s' en %s.", InfoNegocio[id][nNombre], location);
		SendRadioMessage(6, COLOR_RADIO, gformat, 1);
		CreateFireGeneral(id, 1, 0);
	}
	return 1;
}

forward CargarIncendios();
public CargarIncendios()
{
	new cargaditos = 0;
	//clean
	Loop(e, MAX_INCENDIOS, 0)
	{
		InfoIncendio[e][pI_tipo] = -1;
		InfoIncendio[e][pI_propiedad] = -1;
	}
	//load
	Loop(tabla, cache_num_rows(), 0)
	{
		new id = tabla+1;
		rebel_int(tabla, "ID", InfoIncendio[id][pI_IDsql]);
		rebel_int(tabla, "Tipo", InfoIncendio[id][pI_tipo]);
		rebel_int(tabla, "Propiedad", InfoIncendio[id][pI_propiedad]);
		if (InfoIncendio[id][pI_IDsql]) totalincendios++;
		if (InfoIncendio[id][pI_propiedad] != -1)
		{
			cargaditos++;
	        CreateFireGeneral(InfoIncendio[id][pI_propiedad], InfoIncendio[id][pI_tipo], 1, id);
		}
	}
	//printf("|- %d incendios (SQL: %d) cargadas.", cargaditos, totalincendios-1);
	return 1;
}

forward FuegoSiguiente();
public FuegoSiguiente()
{
	Loop(id, MAX_INCENDIOS, 1) if (InfoIncendio[id][pI_propiedad] == -1)
	{
		return id;
	}
	return -1;
}

forward DestroyFire(id);
public DestroyFire(id)
{
	if (InfoIncendio[id][pI_propiedad] != -1)
	{
		if (InfoIncendio[id][pI_tipo] == 1)
		{
			new n_id = InfoIncendio[id][pI_propiedad];
			if (InfoNegocio[n_id][nVenta] == 0)
			{
				InfoNegocio[n_id][nSeguro] = 0;
				Labelupdate_negocio(n_id);
				TallerOpened(n_id, InfoNegocio[n_id][nSeguro]);
				guardar_int_mysql("negocios", "Seguro", InfoNegocio[n_id][nID_sql], InfoNegocio[n_id][nSeguro]);
			}
			InfoNegocio[n_id][EnLlamas] = 0;
		}
		InfoIncendio[id][pI_propiedad] = -1;
		InfoIncendio[id][pI_tipo] = -1;
		guardar_int_mysql("incendios", "Tipo", InfoIncendio[id][pI_IDsql], -1);
		guardar_int_mysql("incendios", "Propiedad", InfoIncendio[id][pI_IDsql], -1);
		Loop(e, 15, 0) if (IsValidDynamicObject(InfoIncendio[id][pI_objeto][e]))
		{
			DestroyDynamicObject(InfoIncendio[id][pI_objeto][e]);
			InfoIncendio[id][pI_objeto][e] = 0;
		}
		return true;
	}
	return false;
}

forward CercaIncendio(playerid);
public CercaIncendio(playerid)
{
	Loop(id, totalincendios, 1) if (InfoIncendio[id][pI_propiedad] != -1)
	{
		new Float: PosFire[3];
		if (InfoIncendio[id][pI_tipo] == 0)
		{
			PosFire[0] = InfoCasa[InfoIncendio[id][pI_propiedad]][cExteriorX];
			PosFire[1] = InfoCasa[InfoIncendio[id][pI_propiedad]][cExteriorY];
			PosFire[2] = InfoCasa[InfoIncendio[id][pI_propiedad]][cExteriorZ];
		}
		else
		{
			PosFire[0] = InfoNegocio[InfoIncendio[id][pI_propiedad]][nExteriorX];
			PosFire[1] = InfoNegocio[InfoIncendio[id][pI_propiedad]][nExteriorY];
			PosFire[2] = InfoNegocio[InfoIncendio[id][pI_propiedad]][nExteriorZ];
		}
		if (IsPlayerInRangeOfPoint(playerid, 10.0, PosFire[0], PosFire[1], PosFire[2])) return id;
	}
	return -1;
}

forward EstaEnFuego(playerid);
public EstaEnFuego(playerid)
{
	Loop(id, totalincendios, 1) if (InfoIncendio[id][pI_propiedad] != -1)
	{
		if (InfoIncendio[id][pI_tipo] == 0)
		{
			new house = InfoIncendio[id][pI_propiedad];
			if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoCasa[house][cExteriorX], InfoCasa[house][cExteriorY], InfoCasa[house][cExteriorZ]))
			{
				quitar_vida(playerid, -1.5);
			}
		}
		else
		{
			new business = InfoIncendio[id][pI_propiedad];
			if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoNegocio[business][nExteriorX], InfoNegocio[business][nExteriorY], InfoNegocio[business][nExteriorZ]))
			{
				quitar_vida(playerid, -1.5);
			}
		}
	}
}

forward GenerarIncendio();
public GenerarIncendio()
{
	if (OnFaction(6) < 2) return 1;
	new a = random(4), location[MAX_ZONE_NAME], gformat[256];
	if (a == 0 || a == 1)
	{
		new casaid = random(totalcasas)-1;
		if (casaid == -1 || casaid == 0) casaid = 1;
		if (InfoCasa[casaid][cTipo] != 0)
		{
			if (InfoCasa[casaid][cExteriorInt] == 0 && InfoCasa[casaid][cExteriorVW] == 0)
			{
				Get2DZone(location, MAX_ZONE_NAME, InfoCasa[casaid][cExteriorX], InfoCasa[casaid][cExteriorY], InfoCasa[casaid][cExteriorZ]);
				format(gformat, sizeof gformat, "[CENTRAL] Se generó un nuevo incendio en la casa #%d en %s.", casaid, location);
				SendRadioMessage(6, COLOR_RADIO, gformat, 1);
				CreateFireGeneral(casaid, 0, 0);
				return 1;
			}
		}
	}
	if (a == 2 || a == 3)
	{
		new negocioid = random(totalnegocios)-1;
		if (negocioid == -1 || negocioid == 0) negocioid = 1;
		if (InfoNegocio[negocioid][nTipo] != 0)
		{
			Get2DZone(location, MAX_ZONE_NAME, InfoNegocio[negocioid][nExteriorX], InfoNegocio[negocioid][nExteriorY], InfoNegocio[negocioid][nExteriorZ]);
			format(gformat, sizeof gformat, "[CENTRAL] Se generó un nuevo incendio en el negocio '%s' en %s.", InfoNegocio[negocioid][nNombre], location);
			SendRadioMessage(6, COLOR_RADIO, gformat, 1);
			CreateFireGeneral(negocioid, 1, 0);
			return 1;
		}
	}
	return 0;
}

forward OnIncendioCreate(id);
public OnIncendioCreate(id)
{
	InfoIncendio[id][pI_IDsql] = cache_insert_id();
	cache_unset_active();
	totalincendios++;
    return 1;
}