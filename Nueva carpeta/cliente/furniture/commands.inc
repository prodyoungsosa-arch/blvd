cmd:muebles(playerid)
{
	if (InfoPersonaje[playerid][pVirtualWorld] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te encuentras dentro de ningún interior.");
	Loop(c, totalcasas, 1) if (InfoPersonaje[playerid][pVirtualWorld] == c + 400)
	{
		if (PermisosCasa(playerid, c) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficientes permisos en esta casa.");
		Dialog_Show(playerid, MenuMuebles, DIALOG_STYLE_LIST, "Menú de muebles", "Lista de tus muebles\nConseguir más muebles\n{F4C233}Borrar todos los muebles", "Continuar", "Salir");
		DentroCasa[playerid] = c;
		return 1;
	}
	Loop(n, totalnegocios, 1) if (InfoPersonaje[playerid][pVirtualWorld] == n + 100)
	{
		if (PermisosNegocio(playerid, n) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficientes permisos en este negocio.");
		Dialog_Show(playerid, MenuMuebles, DIALOG_STYLE_LIST, "Menú de muebles", "Lista de tus muebles\nConseguir más muebles\n{F4C233}Borrar todos los muebles", "Continuar", "Salir");
		DentroNegocio[playerid] = n;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No te encuentras dentro de ninguna casa o negocio.");
	return 1;
}
cmd:puerta(playerid)
{
	//Casas
	Loop(x, totalcasas, 1) if (InfoPersonaje[playerid][pVirtualWorld] == x + 400)
	{
		new objetoid, Float: mueblex, Float: muebley, Float: mueblez, Float: mueblerx, Float: mueblery, Float: mueblerz;
		Loop(id, totalmuebles+1, 1) if (InfoMueble[id][mInterior] != -1 && InfoMueble[id][mVirtualWorld] == x + 400)
		{
			objetoid = InfoMueble[id][mObjeto];
			if (IsValidDynamicObject(objetoid) <= 0)continue;
			GetDynamicObjectPos(objetoid, mueblex, muebley, mueblez);
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, mueblex, muebley, mueblez) || OpenableDoor(InfoMueble[id][mModelo]) == -1) continue;
			if (PermisosCasa(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficientes permisos en esta casa.");
			GetDynamicObjectRot(objetoid, mueblerx, mueblery, mueblerz);
			InfoMueble[id][mPuerta] = (InfoMueble[id][mPuerta]) ? 0 : 1;
			mueblerz = (InfoMueble[id][mPuerta]) ? mueblerz - 90 : mueblerz + 90;
			InfoMueble[id][mRotX] = mueblerx;
			InfoMueble[id][mRotY] = mueblery;
			InfoMueble[id][mRotZ] = mueblerz;
			SetDynamicObjectRot(objetoid, InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
			new que2ry[512];
			mysql_format(db_samp, que2ry, sizeof que2ry, "UPDATE muebles SET RotX = '%f', RotY = '%f', RotZ = '%f' WHERE ID = '%d'", InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, que2ry);
			return 1;
		}
	}
	Loop(x, totalnegocios, 1) if (InfoPersonaje[playerid][pVirtualWorld] == x + 100)
	{
		new objetoid, Float: mueblex, Float: muebley, Float: mueblez, Float: mueblerx, Float: mueblery, Float: mueblerz;
		Loop(id, totalmuebles+1, 1) if (InfoMueble[id][mInterior] != -1 && InfoMueble[id][mVirtualWorld] == x + 100)
		{
			objetoid = InfoMueble[id][mObjeto];
			if (IsValidDynamicObject(objetoid) <= 0)continue;
			GetDynamicObjectPos(objetoid, mueblex, muebley, mueblez);
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, mueblex, muebley, mueblez) || OpenableDoor(InfoMueble[id][mModelo]) == -1) continue;
			if (PermisosNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficientes permisos en este negocio.");
			GetDynamicObjectRot(objetoid, mueblerx, mueblery, mueblerz);
			InfoMueble[id][mPuerta] = (InfoMueble[id][mPuerta]) ? 0 : 1;
			mueblerz = (InfoMueble[id][mPuerta]) ? mueblerz - 90 : mueblerz + 90;
			InfoMueble[id][mRotX] = mueblerx;
			InfoMueble[id][mRotY] = mueblery;
			InfoMueble[id][mRotZ] = mueblerz;
			SetDynamicObjectRot(objetoid, InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ]);
			new que2ry[512];
			mysql_format(db_samp, que2ry, sizeof que2ry, "UPDATE muebles SET RotX = '%f', RotY = '%f', RotZ = '%f' WHERE ID = '%d'", InfoMueble[id][mRotX], InfoMueble[id][mRotY], InfoMueble[id][mRotZ], InfoMueble[id][mID_sql]);
			mysql_tquery(db_samp, que2ry);
			return 1;
		}
	}
	return 1;
}
alias:puerta("door");