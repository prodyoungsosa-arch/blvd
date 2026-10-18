Dialog:InviteFaccion(playerid, response, listitem, inputtext[])
{
	new string[256], playerid2 = TomandoTrabajo[playerid], query[512];
	if (!IsPlayerConnectedEx(playerid2))
	{
		TomandoTrabajo[playerid] = -1;
		SendPlayerChatMessage(playerid, COLOR_GREY, "El lider se ha desconectado, perdiste la oferta.");
		return 1;
	}
	new id = InfoPersonaje[playerid2][pMiembro];
	if (!response) //rechazo
	{
		format(string, sizeof string, "Rechaste la invitación a %s.", InfoFaccion[id][fNombre]);
		SendPlayerChatMessage(playerid, 0xEFEFEFFF, string);
		format(string, sizeof string, "%s rechazó la invitación", GetNameFormat(playerid));
		SendPlayerChatMessage(playerid2, 0xEFEFEFFF, string);
		TomandoTrabajo[playerid] = -1;
		return 1;
	}
	//acepto
	InfoPersonaje[playerid][pMiembro] = id;
	InfoPersonaje[playerid][pRango] = 1;
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET MiembroFaccion = '%d', Rango = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pMiembro], InfoPersonaje[playerid][pRango], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);

	format(string, sizeof string, "Ahora formas parte de %s.", InfoFaccion[id][fNombre]);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "%s aceptó la invitación.", GetNameFormat(playerid));
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "Registros: %s ahora es %s por %s.", NombreDeCuenta(playerid), InfoFaccion[id][fNombre], NombreDeCuenta(playerid2));
	Log("f_logs/UnirseFaccion.log", string);

	TomandoTrabajo[playerid] = -1;
	return 1;
}

Dialog:ShowEncubierto(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_equipo(playerid);
	new skinid = strval(inputtext);
	if (IsValidSkin(skinid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes de escoger una id de skin entre 1 y 311.");
	GivePlayerJobSkin(playerid, skinid);
	return 1;
}

Dialog:ShowEquipo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, xwds[40];
	format(xwds, sizeof xwds, "RanuraEq%d", ID);
	new x = GetPVarInt(playerid, xwds);
	new faccion = InfoPersonaje[playerid][pMiembro], gformat[170];
	if (member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) //lspd, fbi, USMC, lscsd, gob
	{
		switch (x)
		{
			case 0: //duty
			{
				if (OnDuty[playerid] != 0)
				{
					OnDuty[playerid] = 0;
					rol_ame(playerid, "deja su placa en el casillero y deja su labor.");
				}
				else
				{
					OnDuty[playerid] = 1;
					rol_ame(playerid, "coge su placa del casillero y entra en su labor.");
				}
			}
			case 1..20: //equipo
			{
				new objeto = InfoFaccion[faccion][fEquipo][x-1];
				if (InfoPersonaje[playerid][pRango] < InfoFaccion[faccion][fRequiere][x-1])
				{
					new gece[190];
					format(gece, sizeof gece, "* Debes ser mínimo rango %d para tomar este item del equipo.", InfoFaccion[faccion][fRequiere][x-1]);
					SendPlayerChatMessage(playerid, COLOR_GREY, gece);
					return 1;
				}
				if (objeto == 900)
				{
					if (InfoPersonaje[playerid][pVida] >= 99.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes la vida full.");
					dar_vida(playerid, 100);
					rol_ame(playerid, "coge un botiquin hp del casillero.");
				}
				else if (objeto == 950)
				{
					if (InfoPersonaje[playerid][pChaleco] >= 99.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes el chaleco full.");
					dar_chaleco(playerid, 100);
					rol_ame(playerid, "coge un chaleco del casillero.");
				}
				else
				{
					if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
					if (InfoPersonaje[playerid][pManoDerecha] != 0)
					{
						InfoPersonaje[playerid][pManoIzquierda] = objeto;
						InfoPersonaje[playerid][pManoIzquierdaCant] = InfoInventario[objeto][MaxCantidad];
						PonerObjeto(playerid, 2, objeto);
						format(gformat, sizeof gformat, "coge %s del casillero en su mano izquierda.", GetObjEquipo(objeto));
					}
					else
					{
						InfoPersonaje[playerid][pManoDerecha] = objeto;
						InfoPersonaje[playerid][pManoDerechaCant] = InfoInventario[objeto][MaxCantidad];
						PonerObjeto(playerid, 1, objeto);
						if (InfoInventario[objeto][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], InfoInventario[objeto][MaxCantidad]); }
						format(gformat, sizeof gformat, "coge %s del casillero en su mano derecha.", GetObjEquipo(objeto));
					}
					rol_ame(playerid, gformat);
					ActualizarManos(playerid, 1);
					if (InfoInventario[objeto][IDArma] > 0)
					{
						format(gformat, sizeof gformat, "%s saca %s.", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto]);
						Log("f_logs/Equipop.log", gformat);
					}
				}
			}
			case 21: //skins
			{
				new SkinMuestra[20], count = 0;
				Loop(e, 20, 0) if (InfoFaccion[faccion][fSkin][e] != 0)
				{
					SkinMuestra[count] = InfoFaccion[faccion][fSkin][e];
					count++;
				}
				ShowModelSelectionMenuEx(playerid, SkinMuestra, count, InfoFaccion[faccion][fLogo], Equipo_Skin, -11.0, 0.0, -55.0, 1.0);
			}
			case 22: //skin normal
			{
				if (InfoPersonaje[playerid][pJobSkin] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes puesto ningún skin de facción o trabajo.");
				GivePlayerSkin(playerid, InfoPersonaje[playerid][pSkin]);
				rol_ame(playerid, "se viste con su ropa normal.");
			}
			case 23: //encubierto
			{
				Dialog_Show(playerid, ShowEncubierto, DIALOG_STYLE_INPUT, "Encubierto", "{FFFFFF}Introduce la skin de 1 entre 311:", "Continuar", "Volver");
			}
			case 24: //accesorios
			{
				new max_cToys = 4;
				if (InfoCuenta[playerid][jVIP] == 2) max_cToys = 7;
				Loop(id, max_cToys, 0) if (InfoPersonaje[playerid][ptModelo][id] == 0)
				{
					slotselection[playerid] = id;
					new ToyMuestra[180], count = 0;
					Loop(e, sizeof InfoToy, 0) if (InfoToy[e][accTipo] == 2)
					{
						ToyMuestra[count] = InfoToy[e][accModelo];
						count++;
					}
					ShowModelSelectionMenuEx(playerid, ToyMuestra, count, "Toys de policia", Compra_Toy);
					return 1;
				}
				new gformat2[128];
				format(gformat2, sizeof gformat2, "No puedes tener más de %d toys.", max_cToys);
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat2);
			}
			case 25: //borrar objetos
			{
				new count = 0, gformat2[128];
				if (InfoPersonaje[playerid][pManoDerecha] != 0)
				{
					format(gformat2, sizeof gformat2, "Borraste %s de tu mano derecha.", InfoInventario[InfoPersonaje[playerid][pManoDerecha]][NombreObjeto]);
				    count++;
					RemovePlayerAttachedObject(playerid, 7);
					InfoPersonaje[playerid][pManoDerecha] = 0;
					InfoPersonaje[playerid][pManoDerechaCant] = 0;
					ResetPlayerWeapons(playerid);
					SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat2);
				}
				if (InfoPersonaje[playerid][pManoIzquierda] != 0)
				{
				    format(gformat2, sizeof gformat2, "Borraste %s de tu mano izquierda.", InfoInventario[InfoPersonaje[playerid][pManoIzquierda]][NombreObjeto]);
					count++;
					RemovePlayerAttachedObject(playerid, 8);
					InfoPersonaje[playerid][pManoIzquierda] = 0;
					InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
					SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat2);
				}
				if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes nada que borrar de tus manos, están vacías.");
				new query[500];
				mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0, Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid][pID]);
				mysql_tquery(db_samp, query);
			}
			case 26: //recargar balas
			{
				Dialog_Show(playerid, BalasEquipo, DIALOG_STYLE_LIST, "Cargadores", "9mm\nDesert eagle\nUzi\nMp5\nTec-9\nAk47\nM4a1\nRifles\nEscopetas", "Coger", "Volver");
			}
		}
	}
	else //otros
	{
		switch (x)
		{
			case 0..19: //equipo
			{
				new objeto = InfoFaccion[faccion][fEquipo][x];
				if (InfoPersonaje[playerid][pRango] < InfoFaccion[faccion][fRequiere][x])
				{
					new gece[190];
					format(gece, sizeof gece, "* Debes ser mínimo rango %d para tomar este item del equipo.", InfoFaccion[faccion][fRequiere][x]);
					SendPlayerChatMessage(playerid, COLOR_GREY, gece);
					return 1;
				}
				if (objeto == 900)
				{
					if (InfoPersonaje[playerid][pVida] >= 99.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes la vida full.");
					dar_vida(playerid, 100);
					rol_ame(playerid, "coge un botiquin hp del armario.");
				}
				else if (objeto == 950)
				{
					if (InfoPersonaje[playerid][pChaleco] >= 99.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes el chaleco full.");
					dar_chaleco(playerid, 100);
					rol_ame(playerid, "coge un chaleco del armario.");
				}
				else
				{
					if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
					if (InfoPersonaje[playerid][pManoDerecha] != 0)
					{
						InfoPersonaje[playerid][pManoIzquierda] = objeto;
						InfoPersonaje[playerid][pManoIzquierdaCant] = InfoInventario[objeto][DefaultCantidad];
						PonerObjeto(playerid, 2, objeto);
						format(gformat, sizeof gformat, "coge %s del armario en su mano izquierda.", GetObjEquipo(objeto));
					}
					else
					{
						InfoPersonaje[playerid][pManoDerecha] = objeto;
						InfoPersonaje[playerid][pManoDerechaCant] = InfoInventario[objeto][DefaultCantidad];
						PonerObjeto(playerid, 1, objeto);
						if (InfoInventario[objeto][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], InfoInventario[objeto][DefaultCantidad]); }
						format(gformat, sizeof gformat, "coge %s del armario en su mano derecha.", GetObjEquipo(objeto));
					}
					rol_ame(playerid, gformat);
					ActualizarManos(playerid, 1);
					if (InfoInventario[objeto][IDArma] > 0)
					{
						format(gformat, sizeof gformat, "%s saca %s.", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto]);
						Log("f_logs/Equipop.log", gformat);
					}
				}
			}
			case 20: //skins
			{
				new SkinMuestra[20], count = 0;
				Loop(e, 20, 0) if (InfoFaccion[faccion][fSkin][e] != 0)
				{
					SkinMuestra[count] = InfoFaccion[faccion][fSkin][e];
					count++;
				}
				ShowModelSelectionMenuEx(playerid, SkinMuestra, count, InfoFaccion[faccion][fLogo], Equipo_Skin, -11.0, 0.0, -55.0, 1.0);

			}
			case 21: //skin normal
			{
				if (InfoPersonaje[playerid][pJobSkin] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes puesto ningún skin de facción o trabajo.");
				GivePlayerSkin(playerid, InfoPersonaje[playerid][pSkin]);
				rol_ame(playerid, "se viste con su ropa normal.");
			}
		}
	}
	return 1;
}

Dialog:BalasEquipo(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_equipo(playerid);
	new obj;
	switch (listitem)
	{
		case 0: obj = 56;
		case 1: obj = 57;
		case 2: obj = 58;
		case 3: obj = 59;
		case 4: obj = 60;
		case 5: obj = 61;
		case 6: obj = 62;
		case 7: obj = 63;
		case 8: obj = 64;
	}
	if (DarObjeto(playerid, obj, InfoInventario[obj][DefaultCantidad]) == 2) return 1;
	new gformat[190];
	format(gformat, sizeof gformat, "%s saca %s.", GetNameFormat(playerid), InfoInventario[obj][NombreObjeto]);
	Log("f_logs/Equipop.log", gformat);
	return 1;
}

Dialog:ChangeFequipo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new gformat[450], id = ID_ACTUAL_FACUWU[playerid];
	format(gformat, sizeof gformat, "Estás editando el slot %d (objeto actual: %s)\n\nEscribe el id del nuevo objeto (id 900 es vida - id 950 es chaleco - el resto en /listaobjetos): ", listitem+1, GetObjEquipo(InfoFaccion[id][fEquipo][listitem]));
	Dialog_Show(playerid, Change2Fequipo, DIALOG_STYLE_INPUT, "Ajustes de /equipo", gformat, "Continuar", "Salir");
	ID_ACTUAL_EquipoUWU[playerid] = listitem;
	return 1;
}

Dialog:Change2Fequipo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo números porfavor, vuelve a intentarlo.");
	new obj = strval(inputtext);
	if (ValidObjEquipo(obj) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Objeto inválido, revisa /listaobjetos.");
	new slot = ID_ACTUAL_EquipoUWU[playerid], id = ID_ACTUAL_FACUWU[playerid], gformat[240];
	Loop(x, 20, 0) if (obj != 0 && InfoFaccion[id][fEquipo][x] == obj)
	{
		format(gformat, sizeof gformat, "%s ya lo tienes en el slot %d", GetObjEquipo(obj), x+1);
		SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
		return 1;
	}
	InfoFaccion[id][fEquipo][slot] = obj;
	mysql_format(db_samp, gformat, sizeof gformat, "UPDATE facciones SET Equipo%d = '%d' WHERE ID = '%d'", slot+1, InfoFaccion[id][fEquipo][slot], InfoFaccion[id][fID_sql]);
	mysql_tquery(db_samp, gformat);
	format(gformat, sizeof gformat, "Facción: %s | Agregaste %s en el slot %d.", InfoFaccion[id][fLogo], GetObjEquipo(obj), slot+1);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
	return 1;
}

Dialog:MenuMiembros(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem, gformat[128], nombre_miembro[32];
	format(gformat, sizeof gformat, "Miembro_List%d", ID);
	GetPVarString(playerid, gformat, nombre_miembro, sizeof nombre_miembro);
	SetPVarString(playerid, "Miembro_Actual", nombre_miembro);
	format(gformat, sizeof gformat, "Miembro: {F5DEB3}%s", nombre_miembro);
	Dialog_Show(playerid, OpcionMiembros, DIALOG_STYLE_LIST, gformat, "Dar rango\nÚltima conexión\n{B00000}Expulsar de la facción", "Continuar", "Volver");
	return 1;
}

Dialog:OpcionMiembros(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_listamiembros(playerid);
	new nombre_miembro[32], newid = -1, string[256], ultimaconexion[256], faccion = InfoPersonaje[playerid][pMiembro], query[512];
	GetPVarString(playerid, "Miembro_Actual", nombre_miembro, sizeof nombre_miembro);
	//fix 22/04/2020
	foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoPersonaje[juegador][pNombre_Apellido], nombre_miembro, true)) { newid = juegador; }
	//fix 22/04/2020
	new eslider;
	if (VerificarPersonaje(nombre_miembro))
	{
		rebel_int(0, "LiderFaccion", eslider);
		rebel_string(0, "UltimaConexion", ultimaconexion, 256);
	}
	else return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta no existe.");
	switch (listitem)
	{
		case 0: //darrango
		{
			new maxrangos = InfoFaccion[faccion][fMaxRangos];
			new dialog[1024], gformat[128];
			Loop(rango, maxrangos, 0)
			{
				format(gformat, sizeof gformat, "(%d) %s\n", rango+1, fac_rango[faccion][rango]);
				strcat(dialog, gformat);
			}
			format(gformat, sizeof gformat, "Miembro: {F5DEB3}%s", nombre_miembro);
			Dialog_Show(playerid, DarRango, DIALOG_STYLE_LIST, gformat, dialog, "Continuar", "Salir");
		}
		case 1: //última conexión
		{
			if (IsPlayerConnectedEx(newid))
			{
				format(string, sizeof string, "%s está conectado ID: %d", nombre_miembro, newid);
				SendPlayerChatMessage(playerid, COLOR_GREEN, string);
				return 1;
			}
			format(string, sizeof string, "%s: %s", nombre_miembro, ultimaconexion);
			SendPlayerChatMessage(playerid, COLOR_PURPLE, string);
		}
		case 2: //expulsar de la facción
		{
			if (eslider != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes expulsar lideres de la facción, habla con un admin.");
			if (IsPlayerConnectedEx(newid))
			{
			    if (playerid == newid) return SendPlayerChatMessage(playerid, COLOR_GREY, "No te puedes expulsar de la facción.");
				InfoPersonaje[newid][pLider] = 0;
				InfoPersonaje[newid][pMiembro] = 0;
				InfoPersonaje[newid][pRango] = 0;
				if (faccion == 1 || faccion == 2 || faccion == 3) GivePlayerSkin(newid, 155);
				if (OnDuty[newid] != 0) OnDuty[newid] = 0;
			}
			format(string, sizeof string, "Líder %s expulsó de la facción a %s.", NombreOriginal(playerid), nombre_miembro);
			SendFaccionMessage(InfoPersonaje[playerid][pMiembro], 0x33CCFFFF, string);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET LiderFaccion = 0, MiembroFaccion = 0, Rango = 0 WHERE Nombre_Apellido = '%e'", nombre_miembro);
			mysql_tquery(db_samp, query);
		}
	}
	return 1;
}

Dialog:DarRango(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new nombre_miembro[32], newid = -1, string[256], rango = listitem;
	new faccion = InfoPersonaje[playerid][pMiembro], query[512];
	GetPVarString(playerid, "Miembro_Actual", nombre_miembro, sizeof nombre_miembro);
	//fix 22/04/2020
	foreach(Player, juegador) if (IsPlayerConnectedEx(juegador) && !strcmp(InfoPersonaje[juegador][pNombre_Apellido], nombre_miembro, true)) { newid = juegador; }
	//fix 22/04/2020
	if (IsPlayerConnectedEx(newid)) InfoPersonaje[newid][pRango] = rango+1;
	format(string, sizeof string, "Líder %s asignó rango %s(%d) al miembro %s.", NombreOriginal(playerid), fac_rango[faccion][rango], rango+1, nombre_miembro);
	SendFaccionMessage(faccion, 0x33CCFFFF, string);
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Rango = '%d' WHERE Nombre_Apellido = '%e'", rango+1, nombre_miembro);
	mysql_tquery(db_samp, query);
	return 1;
}