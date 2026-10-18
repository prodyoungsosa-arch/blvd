CountNegocios(playerid)
{
	new count = 0;
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nVenta] != 0 && InfoNegocio[id][nTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nPropietario], true) == 0)
	{
		count++;
	}
	return count;
}

PermisosNegocio(playerid, id)
{
	if (InfoNegocio[id][nVenta] != 0 && InfoNegocio[id][nTipo] != 0)
	{
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nPropietario], true) == 0) { return 1; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida1], true) == 0) { return 1; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida2], true) == 0) { return 1; }
		if (strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nCompartida3], true) == 0) { return 1; }
	}
	return 0;
}

LlavesNegocio(playerid, id)
{
	if (InfoNegocio[id][nVenta] != 0 && InfoNegocio[id][nTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nPropietario], true) == 0)
	{
		return 1;
	}
	return 0;
}

ActualizarPrecioNegocio(id)
{
	new gformat2[512];
	format(gformat2, sizeof gformat2, "%d|%d|%d|%d|%d|%d|%d|%d|",
	InfoNegocio[id][nPrecioPintura], InfoNegocio[id][nPrecioPaintJob], InfoNegocio[id][nPrecioReparacion], InfoNegocio[id][nPrecioGasolina],
	InfoNegocio[id][nPrecioLlantas], InfoNegocio[id][nPrecioNitro], InfoNegocio[id][nPrecioHyd], InfoNegocio[id][nPrecioTuneo]);

	new query[620];
	mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET Mecanico = '%e' WHERE ID = '%d'", gformat2, InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, query);
	return 1;
}

LabelPickup_negocio(id, labelpickup, mapicon, actor, lugarcompra)
{
	if (labelpickup != 0)
	{
		//delete error
		DestroyDynamicPickup(InfoNegocio[id][nExteriorPickup]);
		DestroyDynamicPickup(InfoNegocio[id][nInteriorPickup]);
		if (IsValidDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]))
		{
			DestroyDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]);
			InfoNegocio[id][nExteriorLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		if (IsValidDynamic3DTextLabel(InfoNegocio[id][nInteriorLabel]))
		{
			DestroyDynamic3DTextLabel(InfoNegocio[id][nInteriorLabel]);
			InfoNegocio[id][nInteriorLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		//info new
		new negocio_label[470], model = 1272;
		//3d label
		format(negocio_label, sizeof negocio_label, "{00CC00}%s #%d\n{CCCCCC}Usa '/detalles' para más información", GetTipoNegocio(InfoNegocio[id][nTipo]), id);
		InfoNegocio[id][nExteriorLabel] = CreateDynamic3DTextLabel(negocio_label, -1, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]+0.2, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoNegocio[id][nExteriorVW], InfoNegocio[id][nExteriorInt], -1);
		format(negocio_label, sizeof negocio_label, "{00CC00}Salida #%d\n{CCCCCC}%s", id, InfoNegocio[id][nNombre]);
		if (InfoNegocio[id][nInteriorX] != 0)
		{
			InfoNegocio[id][nInteriorLabel] = CreateDynamic3DTextLabel(negocio_label, -1, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoNegocio[id][nInteriorVW], InfoNegocio[id][nInteriorInt], -1);
			InfoNegocio[id][nInteriorPickup] = CreateDynamicPickup(model, 1, InfoNegocio[id][nInteriorX], InfoNegocio[id][nInteriorY], InfoNegocio[id][nInteriorZ], InfoNegocio[id][nInteriorVW], InfoNegocio[id][nInteriorInt]);
		}
		InfoNegocio[id][nExteriorPickup] = CreateDynamicPickup(model, 1, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nExteriorVW], InfoNegocio[id][nExteriorInt]);
	}
	if (mapicon != 0 && InfoNegocio[id][nMapIcon] != 0)
	{
		DestroyDynamicMapIcon(InfoNegocio[id][nExteriorMapIcon]);
		InfoNegocio[id][nExteriorMapIcon] = CreateDynamicMapIcon(InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ], InfoNegocio[id][nMapIcon], 0, 0, 0, -1, 300);
	}
	if (actor != 0 && InfoNegocio[id][nActorSkin] != 0)
	{
		DestroyDynamicActor(InfoNegocio[id][nInteriorActor]);
		if (InfoNegocio[id][nTipo] == 9) { InfoNegocio[id][nInteriorActor] = CreateDynamicActor(InfoNegocio[id][nActorSkin], InfoNegocio[id][nActorX], InfoNegocio[id][nActorY], InfoNegocio[id][nActorZ], InfoNegocio[id][nActorR], true, 100.0, 0, 0); }
		else { InfoNegocio[id][nInteriorActor] = CreateDynamicActor(InfoNegocio[id][nActorSkin], InfoNegocio[id][nActorX], InfoNegocio[id][nActorY], InfoNegocio[id][nActorZ], InfoNegocio[id][nActorR], true, 100.0, InfoNegocio[id][nInteriorVW], InfoNegocio[id][nInteriorInt]); }
	}
	if (lugarcompra != 0 && InfoNegocio[id][nLugarCompraX] != 0.0)
	{
		if (IsValidDynamic3DTextLabel(InfoNegocio[id][nLugarCompraLabel]))
		{
			DestroyDynamic3DTextLabel(InfoNegocio[id][nLugarCompraLabel]);
			InfoNegocio[id][nLugarCompraLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoNegocio[id][nLugarCompraLabel] = CreateDynamic3DTextLabel("Para abrir el {F5DEB3}menú de productos{FFFFFF}\nEscribe aquí '{3E62F4}/comprar{FFFFFF}'", -1, InfoNegocio[id][nLugarCompraX], InfoNegocio[id][nLugarCompraY], InfoNegocio[id][nLugarCompraZ], 10.0, .worldid = InfoNegocio[id][nInteriorVW], .interiorid = InfoNegocio[id][nInteriorInt]);
	}
}

Labelupdate_negocio(id)
{
	new negocio_label[470];
	format(negocio_label, sizeof negocio_label, "{00CC00}%s #%d\n{CCCCCC}Usa '/detalles' para mas informacion", GetTipoNegocio(InfoNegocio[id][nTipo]), id);
	UpdateDynamic3DTextLabelText(InfoNegocio[id][nExteriorLabel], -1, negocio_label);
	format(negocio_label, sizeof negocio_label, "{00CC00}Salida #%d\n{CCCCCC}%s", id, InfoNegocio[id][nNombre]);
	if (InfoNegocio[id][nInteriorX] != 0) UpdateDynamic3DTextLabelText(InfoNegocio[id][nInteriorLabel], -1, negocio_label);
}

noexitnegocio(id)
{
	DestroyDynamicActor(InfoNegocio[id][nInteriorActor]);
	DestroyDynamicMapIcon(InfoNegocio[id][nExteriorMapIcon]);
	DestroyDynamicPickup(InfoNegocio[id][nExteriorPickup]);
	DestroyDynamicPickup(InfoNegocio[id][nInteriorPickup]);
	if (IsValidDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]);
		InfoNegocio[id][nExteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]))
	{
		DestroyDynamic3DTextLabel(InfoNegocio[id][nExteriorLabel]);
		InfoNegocio[id][nExteriorLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	if (IsValidDynamic3DTextLabel(InfoNegocio[id][nLugarCompraLabel]))
	{
		DestroyDynamic3DTextLabel(InfoNegocio[id][nLugarCompraLabel]);
		InfoNegocio[id][nLugarCompraLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	InfoNegocio[id][nExteriorPickup] = CreateDynamicPickup(1273, 1, -2190.7974, 165.9186, 58.2604, id, id);
	InfoNegocio[id][nInteriorPickup] = CreateDynamicPickup(1273, 1, -2190.7974, 165.9186, 58.2604, id, id);
	InfoNegocio[id][nExteriorLabel] = CreateDynamic3DTextLabel("negocio", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
	InfoNegocio[id][nInteriorLabel] = CreateDynamic3DTextLabel("negocio", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
	InfoNegocio[id][nLugarCompraLabel] = CreateDynamic3DTextLabel("negocio", -1, -2190.7974, 165.9186, 58.2604, 1.0, .worldid = id, .interiorid = id);
}

GetTipoNegocio(tipo)
{
	new name_tipo[27];
	switch (tipo)
	{
		case 1: alm(name_tipo, "24-7");
		case 2: alm(name_tipo, "Ropa");
		case 3: alm(name_tipo, "Restaurante");
		case 4: alm(name_tipo, "Gasolinera");
		case 5: alm(name_tipo, "Armerí­a");
		case 6: alm(name_tipo, "Repartos");
		case 7: alm(name_tipo, "Sex shop");
		case 8: alm(name_tipo, "Club bar");
		case 9: alm(name_tipo, "Taller mecanico");
		case 10: alm(name_tipo, "Concesionario");
		case 21: alm(name_tipo, "Tienda de pesca");
		case 11: alm(name_tipo, "none");
		case 12: alm(name_tipo, "none");
		default: alm(name_tipo, "Privado");
	}
	return name_tipo;
}

CobroNegocio(id, valor) // ID del negocio (VW del usuario y cantidad a pagar). (Este stock no afecta al VW 0).
{
	if (id == -1) return 1;
	if (InfoNegocio[id][nVenta] == 0) return 1;
	InfoNegocio[id][nDinero] += valor;
	if (valor >= 500) InfoNegocio[id][nProductos]--;
	new query[210];
	mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET BolosUwU = '%d', Productos = '%d' WHERE ID = '%d'", InfoNegocio[id][nDinero], InfoNegocio[id][nProductos], InfoNegocio[id][nID_sql]);
	mysql_tquery(db_samp, query);
	return 1;
}

CheckNegocio()
{
	new countB = 0, gformat[320];
	//negocios
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nTipo] != 0 && InfoNegocio[id][nVenta] != 0)
	{
		if (InfoNegocio[id][nTiempoDisponible] < gettime())
		{
			countB++;
			//limpiar negocio
			if (VerificarPersonaje(InfoNegocio[id][nPropietario]))
			{
				new dinero;
				rebel_int(0, "BolosUwU", dinero);
				dinero+=InfoNegocio[id][nPrecio];
				mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET BolosUwU = '%d' WHERE Nombre_Apellido = '%e'", dinero, InfoNegocio[id][nPropietario]);
				mysql_tquery(db_samp, gformat);
			}
			alm(InfoNegocio[id][nPropietario], "gobielno");
			InfoNegocio[id][nSeguro] = 0;
			InfoNegocio[id][nVenta] = 0;
			InfoNegocio[id][nTiempoDisponible] = -1;
			LabelPickup_negocio(id, 1, 0, 0, 0);
			TallerOpened(id, InfoNegocio[id][nSeguro]);
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE negocios SET Propietario = '%e', Seguro = 0, Venta = 0, TiempoDisponible = -1 WHERE ID = '%d'", InfoNegocio[id][nPropietario], InfoNegocio[id][nID_sql]);
			mysql_tquery(db_samp, gformat);
			alm(InfoNegocio[id][nCompartida1], "none");
			alm(InfoNegocio[id][nCompartida2], "none");
			alm(InfoNegocio[id][nCompartida3], "none");
			mysql_format(db_samp, gformat, sizeof gformat, "UPDATE negocios SET Compartida1 = '%e', Compartida2 = '%e', Compartida3 = '%e' WHERE ID = '%d'", InfoNegocio[id][nCompartida1], InfoNegocio[id][nCompartida2], InfoNegocio[id][nCompartida3], InfoNegocio[id][nID_sql]);
			mysql_tquery(db_samp, gformat);
		}
	}
	//printf("|-  Se vendieron %d negocios inactivos.", countB);
	return 1;
}

Positions_Negocio(id, tipo)
{
	new myint, myskin, mytipo;
	new Float: myposX, Float: myposY, Float: myposZ, Float: myposR;
	new Float: compraX, Float: compraY, Float: compraZ;
	new Float: jactorX, Float: jactorY, Float: jactorZ, Float: jactorR;
	myskin = RandomSkinCivil();
	switch (tipo)
	{
		case 1: //24-7 pequeÃ±o
		{
            mytipo = 1;
			myposX = -27.3552, myposY = -58.2659, myposZ = 1003.5469, myposR = 2.3829, myint = 6;
			compraX = -23.3468, compraY = -55.4924, compraZ = 1003.5469;
			jactorX = -22.8758, jactorY = -57.5155, jactorZ = 1003.5469, jactorR = 9.1313;
		}
		case 2: //24-7 grande
		{
            mytipo = 1;
			myposX = -30.9624, myposY = -92.0089, myposZ = 1003.5469, myposR = 4.8661, myint = 18;
			compraX = -28.0597, compraY = -89.8704, compraZ = 1003.5469;
			jactorX = -27.7799, jactorY = -91.6342, jactorZ = 1003.5469, jactorR = 6.6012;
		}
		case 3: //binco
		{
            mytipo = 2;
			myposX = 207.6547, myposY = -111.2579, myposZ = 1005.1328, myposR = 356.0927, myint = 15;
			compraX = 207.5624, compraY = -100.7229, compraZ = 1005.2578;
			jactorX = 207.5043, jactorY = -98.7054, jactorZ = 1005.2578, jactorR = 182.9861;
		}
		case 4: //sub urban
		{
            mytipo = 2;
			myposX = 203.8141, myposY = -50.6344, myposZ = 1001.8047, myposR = 1.7561, myint = 1;
			compraX = 203.8293, compraY = -43.3790, compraZ = 1001.8047;
			jactorX = 203.8100, jactorY = -41.6695, jactorZ = 1001.8047, jactorR = 182.0694;
		}
		case 5: //ZIP
		{
            mytipo = 2;
			myposX = 161.3801, myposY = -97.1028, myposZ = 1001.8047, myposR = 2.9859, myint = 18;
			compraX = 161.3631, compraY = -83.5608, compraZ = 1001.8047;
			jactorX = 161.3364, jactorY = -81.0248, jactorZ = 1001.8047, jactorR = 182.9859;
		}
		case 6: //victim
		{
            mytipo = 2;
			myposX = 227.5202, myposY = -8.1432, myposZ = 1002.2109, myposR = 93.2500, myint = 5;
			compraX = 206.3774, compraY = -7.9412, compraZ = 1001.2109;
			jactorX = 204.8456, jactorY = -8.7871, jactorZ = 1001.2109, jactorR = 277.9267;
		}
		case 7: //pro laps
		{
            mytipo = 2;
			myposX = 207.0223, myposY = -140.3593, myposZ = 1003.5078, myposR = 4.5758, myint = 3;
			compraX = 207.1047, compraY = -129.2098, compraZ = 1003.5078;
			jactorX = 207.0363, jactorY = -127.7927, jactorZ = 1003.5078, jactorR = 180.8391;
		}
		case 8: //ds
		{
            mytipo = 2;
			myposX = 204.3592, myposY = -168.8523, myposZ = 1000.5234, myposR = 0.2125, myint = 14;
			compraX = 204.2387, compraY = -159.3654, compraZ = 1000.5234;
			jactorX = 204.2719, jactorY = -157.7728, jactorZ = 1000.5234, jactorR = 180.5491;
		}
		case 9: //cluckin bell
		{
            mytipo = 3;
			myskin = 167;
			myposX = 364.9182, myposY = -11.7833, myposZ = 1001.8516, myposR = 3.0558, myint = 9;
			compraX = 370.9220, compraY = -6.0173, compraZ = 1001.8589;
			jactorX = 370.8978, jactorY = -4.4378, jactorZ = 1001.8589, jactorR = 178.9823;
		}
		case 10: //pizzeria
		{
            mytipo = 3;
			myskin = 155;
			myposX = 372.4181, myposY = -133.5219, myposZ = 1001.4922, myposR = 358.9738, myint = 5;
			compraX = 376.6881, compraY = -118.8069, compraZ = 1001.4995;
			jactorX = 376.6858, jactorY = -117.2020, jactorZ = 1001.4922, jactorR = 182.3972;
		}
		case 11: //burger shot
		{
            mytipo = 3;
			myskin = 205;
			myposX = 362.9157, myposY = -75.2065, myposZ = 1001.5078, myposR = 317.3002, myint = 10;
			compraX = 376.5519, compraY = -67.4450, compraZ = 1001.5078;
			jactorX = 376.4981, jactorY = -65.8334, jactorZ = 1001.5078, jactorR = 182.7574;
		}
		case 12: //gasolinera
		{
            mytipo = 4;
			myposX = -27.3804, myposY = -31.7613, myposZ = 1003.5573, myposR = 3.0473, myint = 4;
			compraX = -30.6065, compraY = -28.9321, compraZ = 1003.5573;
			jactorX = -30.3688, jactorY = -30.8017, jactorZ = 1003.5573, jactorR = 354.1288;
		}
		case 13: //ammunation pequeÃ±o
		{
            mytipo = 5;
			myposX = 296.8890, myposY = -112.0669, myposZ = 1001.5156, myposR = 4.0106, myint = 6;
			compraX = 290.2662, compraY = -106.2288, compraZ = 1001.5156;
			jactorX = 290.2452, jactorY = -104.4911, jactorZ = 1001.5156, jactorR = 183.9872;
		}
		case 14: //ammunation mediano
		{
            mytipo = 5;
			myposX = 285.3417, myposY = -41.6345, myposZ = 1001.5156, myposR = 357.3369, myint = 1;
			compraX = 295.3187, compraY = -38.4259, compraZ = 1001.5156;
			jactorX = 295.4275, jactorY = -40.3169, jactorZ = 1001.5156, jactorR = 4.3987;
		}
		case 15: //ammunation grande
		{
            mytipo = 5;
			myposX = 315.8150, myposY = -143.6635, myposZ = 999.6016, myposR = 6.1806, myint = 7;
			compraX = 314.0374, compraY = -133.6105, compraZ = 999.6016;
			jactorX = 316.1269, jactorY = -133.4615, jactorZ = 999.6016, jactorR = 87.1663;
		}
		case 16: //sex shop
		{
            mytipo = 7;
			myskin = 178;
			myposX = -100.3137, myposY = -25.0355, myposZ = 1000.7188, myposR = 2.6871, myint = 3;
			compraX = -104.7556, compraY = -10.7418, compraZ = 1000.7188;
			jactorX = -104.7971, jactorY = -8.9126, jactorZ = 1000.7188, jactorR = 183.0237;
		}
		case 17: //bar
		{
            mytipo = 8;
			myposX = 501.8990, myposY = -67.5652, myposZ = 998.7578, myposR = 182.8555, myint = 11;
			compraX = 496.9826, compraY = -76.0265, compraZ = 998.7578;
			jactorX = 497.1426, jactorY = -77.5720, jactorZ = 998.7651, jactorR = 3.8187;
		}
		case 18: //alhambra
		{
            mytipo = 8;
			myposX = 493.4397, myposY = -24.9173, myposZ = 1000.6719, myposR = 359.2636, myint = 17;
			compraX = 499.9566, compraY = -18.8178, compraZ = 1000.6719;
			jactorX = 501.8318, jactorY = -18.7009, jactorZ = 1000.6719, jactorR = 90.5894;
		}
		case 19: //strip club
		{
            mytipo = 8;
			myposX = 1204.8147, myposY = -13.8345, myposZ = 1000.9219, myposR = 7.3870, myint = 2;
			compraX = 1215.7231, compraY = -13.3252, compraZ = 1000.9219;
			jactorX = 1215.9199, jactorY = -15.2619, jactorZ = 1000.9219, jactorR = 2.8553;
		}
		case 20: //concesionaria alta
		{
            mytipo = 10; 
            myposX =  1827.3885, myposY = 386.1728, myposZ = 2998.3926, myposR = 88.3790,  myint = 0;
            compraX = 1817.0568, compraY = 386.8588, compraZ = 2998.3926;
            jactorX = 1815.6685, jactorY = 386.4512, jactorZ = 2998.3926, jactorR = 289.9992;
		}
		case 21: // bait shop
		{
			mytipo = 21;
            myposX =  -229.1941, myposY = 1401.2935, myposZ = 27.7656, myposR = 284.5854, myint = 18;
			compraX = -224.8882, compraY = 1404.7489, compraZ = 27.7734;
			jactorX = 814.2169, jactorY = -973.8372, jactorZ = 1090.0890, jactorR = 261.5580;
		}
		
	}
	InfoNegocio[id][nTipo] = mytipo;
	InfoNegocio[id][nActorSkin] = myskin;
	InfoNegocio[id][nInteriorInt] = myint;
	InfoNegocio[id][nInteriorVW] = 100+id;
	InfoNegocio[id][nInteriorX] = myposX; InfoNegocio[id][nInteriorY] = myposY; InfoNegocio[id][nInteriorZ] = myposZ; InfoNegocio[id][nInteriorR] = myposR;
	InfoNegocio[id][nLugarCompraX] = compraX; InfoNegocio[id][nLugarCompraY] = compraY; InfoNegocio[id][nLugarCompraZ] = compraZ;
	InfoNegocio[id][nActorX] = jactorX; InfoNegocio[id][nActorY] = jactorY; InfoNegocio[id][nActorZ] = jactorZ; InfoNegocio[id][nActorR] = jactorR;
}

GetExtNegocio(playerid)
{
	new id = -1;
	Loop(x, totalnegocios, 1)
	{
		if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoNegocio[x][nExteriorX], InfoNegocio[x][nExteriorY], InfoNegocio[x][nExteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoNegocio[x][nExteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[x][nExteriorVW])
		{
			id = x;
		}
	}
	return id;
}

GetIntNegocio(playerid)
{
	new id = -1;
	Loop(x, totalnegocios, 1)
	{
		if (IsPlayerInRangeOfPoint(playerid, 1.5, InfoNegocio[x][nInteriorX], InfoNegocio[x][nInteriorY], InfoNegocio[x][nInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoNegocio[x][nInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[x][nInteriorVW])
		{
			id = x;
		}
		if (IsPlayerInRangeOfPoint(playerid, 10.0, -2144.1904, -247.4404, 544.8129) && InfoPersonaje[playerid][pInterior] == InfoNegocio[x][nInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[x][nInteriorVW])
		{
			id = x;
		}
		if (IsPlayerInRangeOfPoint(playerid, 10.0, 1512.2188,-1638.6256,1374.6003) && InfoPersonaje[playerid][pInterior] == InfoNegocio[x][nInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoNegocio[x][nInteriorVW])
		{
			id = x;
		}
	}
	return id;
}

EnNegocio(playerid)
{
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nInteriorVW] != 0)
	{
		if (InfoNegocio[id][nInteriorInt] == InfoPersonaje[playerid][pInterior] && InfoNegocio[id][nInteriorVW] == InfoPersonaje[playerid][pVirtualWorld])
		{
			return id;
		}
	}
	return -1;
}
