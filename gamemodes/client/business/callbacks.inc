forward CargarNegocios();
public CargarNegocios()
{
	Loop(e, MAX_NEGOCIOS, 0)
	{
		alm(InfoNegocio[e][nPropietario], "Gobierno");
		alm(InfoNegocio[e][nCompartida1], "none");
		alm(InfoNegocio[e][nCompartida2], "none");
		alm(InfoNegocio[e][nCompartida3], "none");
	}
	//cargado de negocios
	new cargaditos = 0;
	Loop(tabla, cache_num_rows(), 0)
	{
	    new id = tabla+1;
		rebel_int(tabla, "ID", InfoNegocio[id][nID_sql]);
		rebel_string(tabla, "Nombre", InfoNegocio[id][nNombre], 32);
		rebel_string(tabla, "Propietario", InfoNegocio[id][nPropietario], MAX_PLAYER_NAME);
		rebel_int(tabla, "Venta", InfoNegocio[id][nVenta]);
		rebel_int(tabla, "Tipo", InfoNegocio[id][nTipo]);
		rebel_int(tabla, "Precio", InfoNegocio[id][nPrecio]);
		rebel_float(tabla, "ExteriorX", InfoNegocio[id][nExteriorX]);
		rebel_float(tabla, "ExteriorY", InfoNegocio[id][nExteriorY]);
		rebel_float(tabla, "ExteriorZ", InfoNegocio[id][nExteriorZ]);
		rebel_float(tabla, "ExteriorR", InfoNegocio[id][nExteriorR]);
		rebel_int(tabla, "ExteriorInt", InfoNegocio[id][nExteriorInt]);
		rebel_int(tabla, "ExteriorVW", InfoNegocio[id][nExteriorVW]);
		rebel_float(tabla, "InteriorX", InfoNegocio[id][nInteriorX]);
		rebel_float(tabla, "InteriorY", InfoNegocio[id][nInteriorY]);
		rebel_float(tabla, "InteriorZ", InfoNegocio[id][nInteriorZ]);
		rebel_float(tabla, "InteriorR", InfoNegocio[id][nInteriorR]);
		rebel_int(tabla, "InteriorInt", InfoNegocio[id][nInteriorInt]);
		rebel_int(tabla, "InteriorVW", InfoNegocio[id][nInteriorVW]);
		rebel_float(tabla, "LugarCompraX", InfoNegocio[id][nLugarCompraX]);
		rebel_float(tabla, "LugarCompraY", InfoNegocio[id][nLugarCompraY]);
		rebel_float(tabla, "LugarCompraZ", InfoNegocio[id][nLugarCompraZ]);
		rebel_int(tabla, "Seguro", InfoNegocio[id][nSeguro]);
		rebel_int(tabla, "BolosUwU", InfoNegocio[id][nDinero]);
		rebel_int(tabla, "Productos", InfoNegocio[id][nProductos]);
		rebel_int(tabla, "MapIcon", InfoNegocio[id][nMapIcon]);
		rebel_float(tabla, "ActorX", InfoNegocio[id][nActorX]);
		rebel_float(tabla, "ActorY", InfoNegocio[id][nActorY]);
		rebel_float(tabla, "ActorZ", InfoNegocio[id][nActorZ]);
		rebel_float(tabla, "ActorR", InfoNegocio[id][nActorR]);
		rebel_int(tabla, "ActorSkin", InfoNegocio[id][nActorSkin]);
		rebel_float(tabla, "VehicleX", InfoNegocio[id][nVehicleX]);
		rebel_float(tabla, "VehicleY", InfoNegocio[id][nVehicleY]);
		rebel_float(tabla, "VehicleZ", InfoNegocio[id][nVehicleZ]);
		rebel_float(tabla, "VehicleR", InfoNegocio[id][nVehicleR]);
		new gformat[512];
		rebel_string(tabla, "Mecanico", gformat, 512);
		sscanf(gformat, "p<|>dddddddd", InfoNegocio[id][nPrecioPintura], InfoNegocio[id][nPrecioPaintJob], InfoNegocio[id][nPrecioReparacion], InfoNegocio[id][nPrecioGasolina],
		InfoNegocio[id][nPrecioLlantas], InfoNegocio[id][nPrecioNitro], InfoNegocio[id][nPrecioHyd], InfoNegocio[id][nPrecioTuneo]);
		rebel_int(tabla, "TiempoDisponible", InfoNegocio[id][nTiempoDisponible]);
		rebel_string(tabla, "Compartida1", InfoNegocio[id][nCompartida1], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida2", InfoNegocio[id][nCompartida2], MAX_PLAYER_NAME);
		rebel_string(tabla, "Compartida3", InfoNegocio[id][nCompartida3], MAX_PLAYER_NAME);
		if (InfoNegocio[id][nID_sql]) totalnegocios++;
		

		if (InfoNegocio[id][nTipo] != 0)
		{
			LabelPickup_negocio(id, 1, 1, 1, 1);
			TallerOpened(id, InfoNegocio[id][nSeguro]);
			cargaditos++;
		}
		else noexitnegocio(id);
	}

	//costo de productos y ganancia
	neg_automatico[1] = Random(1200, 2500);
	neg_automatico[2] = Random(1700, 2400);
	neg_automatico[3] = Random(900, 1800);
	neg_automatico[4] = Random(1000, 1990);
	neg_automatico[5] = Random(2200, 3600);
	neg_automatico[6] = 0;
	neg_automatico[7] = Random(750, 1670);
	neg_automatico[8] = Random(2400, 3800);
	neg_automatico[9] = 0;
	neg_automatico[10] = 0;
	return 1;
}

forward OnNegocioCreate(id);
public OnNegocioCreate(id)
{
	InfoNegocio[id][nID_sql] = cache_insert_id();
	cache_unset_active();
	totalnegocios++;
    return 1;
}