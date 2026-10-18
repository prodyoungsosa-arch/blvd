NoFacEdit(id)
{
	switch (id)
	{
		case 1..5: return 1;
	}
	return 0;
}

IsPlayerFaction(playerid, faccion)
{
	if (!IsPlayerConnectedEx(playerid)) return 0;
	new lider = InfoPersonaje[playerid][pLider], miembro = InfoPersonaje[playerid][pMiembro];
	if (lider == faccion || miembro == faccion) return 1;
	return 0;
}

faccion_armario(id, estilo)
{
	new faccion_label[350];
	format(faccion_label, sizeof faccion_label, "Equipo {226BBD}%s", InfoFaccion[id][fLogo]);
	if (estilo == 0)
	{
		DestroyDynamicPickup(InfoFaccion[id][fArmarioPickup]);
		if (IsValidDynamic3DTextLabel(InfoFaccion[id][fArmarioLabel]))
		{
			DestroyDynamic3DTextLabel(InfoFaccion[id][fArmarioLabel]);
			InfoFaccion[id][fArmarioLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoFaccion[id][fArmarioLabel] = CreateDynamic3DTextLabel(faccion_label, 0xEBEBEBFF, InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ]+0.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, InfoFaccion[id][fArmarioVW], InfoFaccion[id][fArmarioInt], -1);
		InfoFaccion[id][fArmarioPickup] = CreateDynamicPickup(1239, 1, InfoFaccion[id][fArmarioX], InfoFaccion[id][fArmarioY], InfoFaccion[id][fArmarioZ], InfoFaccion[id][fArmarioVW], InfoFaccion[id][fArmarioInt]);
	}
	else
	{
		UpdateDynamic3DTextLabelText(InfoFaccion[id][fArmarioLabel], 0xEBEBEBFF, faccion_label);
	}
}

SendRadioMessage(faccion, color, const gformat[], tipo)
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		if (InfoPersonaje[playerid][pMiembro] == faccion && InfoPersonaje[playerid][pTogRadio] == 1)
		{
			SendSplitMessage(playerid, color, gformat);
			//ninguno
			if (tipo == 0) { }
			//centralita
			if (tipo == 1) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961466983478595614/Central.mp3"); }
			//oficial caido
			if (tipo == 2) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961468042238365796/Oficial_caido.mp3"); }
			//solicita refuerzos
			if (tipo == 3) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961467558068903986/Solicita_refuerzos.mp3"); }
			//persona herida
			if (tipo == 4) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961468907259047997/Persona_herida.mp3"); }
			//robo normal
			if (tipo == 5) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961469862797000704/Robo_normal.mp3"); }
			//robo vehiculo
			if (tipo == 6) { PlayAudioStreamForPlayer(playerid, "https://cdn.discordapp.com/attachments/900954544635256833/961469658135932938/Robo_a_carro.mp3"); }
		}
	}
}

SendFaccionMessage(faccion, color, const gformat[])
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid) && InfoPersonaje[playerid][pTogFaccion] == 1)
	{
		if (InfoPersonaje[playerid][pMiembro] == faccion || InfoPersonaje[playerid][pLider] == faccion)
		{
			SendSplitMessage(playerid, color, gformat);
		}
	}
}

GetObjEquipo(obj)
{
	new name_ex[64];
	if (obj == 900) alm(name_ex, "Botiquin HP");
	else if (obj == 950) alm(name_ex, "Chaleco");
	else
	{
		alm(name_ex, InfoInventario[obj][NombreObjeto]);
	}
	return name_ex;
}

ValidObjEquipo(obj)
{
	if (obj == 0) return 1;
	if (obj == 900) return 1;
	if (obj == 950) return 1;
	if (obj >= 1 && obj <= sizeof InfoInventario) return 1;
	return 0;
}

GetColorLogo(tipo)
{
	new color[12];
	switch (tipo)
	{
		case 1: alm(color, "{000080}");
		case 2: alm(color, "{0080C0}");
		case 3: alm(color, "{4F9D00}");
		case 4: alm(color, "{CCCC00}");
		case 5: alm(color, "{808080}");
		case 6: alm(color, "{FF4242}");
		case 7: alm(color, "{808040}");
		case 8: alm(color, "{8080C0}");
		case 9: alm(color, "{FF8000}");
		case 10: alm(color, "{804040}");
		default: alm(color, "{000000}");
	}
	return color;
}

stock member_faccion(playerid, faccion, extra = -1, extra2 = -1, extra3 = -1, extra4 = -1, extra5 = -1, extra6 = -1)
{
	if (!IsPlayerConnectedEx(playerid)) return 0;
	new lider = InfoPersonaje[playerid][pLider], miembro = InfoPersonaje[playerid][pMiembro];
	if (InfoFaccion[lider][fTipo] == faccion || InfoFaccion[miembro][fTipo] == faccion) return 1;
	if (InfoFaccion[lider][fTipo] == extra || InfoFaccion[miembro][fTipo] == extra) return 1;
	if (InfoFaccion[lider][fTipo] == extra2 || InfoFaccion[miembro][fTipo] == extra2) return 1;
	if (InfoFaccion[lider][fTipo] == extra3 || InfoFaccion[miembro][fTipo] == extra3) return 1;
	if (InfoFaccion[lider][fTipo] == extra4 || InfoFaccion[miembro][fTipo] == extra4) return 1;
	if (InfoFaccion[lider][fTipo] == extra5 || InfoFaccion[miembro][fTipo] == extra5) return 1;
	if (InfoFaccion[lider][fTipo] == extra6 || InfoFaccion[miembro][fTipo] == extra6) return 1;
	return 0;
}

stock Propietario_faccion(playerid, faccion, extra = -1, extra2 = -1, extra3 = -1, extra4 = -1, extra5 = -1, extra6 = -1)
{
	if (!IsPlayerConnectedEx(playerid)) return 0;
	new id = InfoPersonaje[playerid][pMiembro];
	if (InfoFaccion[id][fTipo] == faccion)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra2)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra3)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra4)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra5)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	if (InfoFaccion[id][fTipo] == extra6)
	{
		if (InfoPersonaje[playerid][pLider] == id) return 1; //afirmativo, tiene acceso
		if (InfoPersonaje[playerid][pRango] == InfoFaccion[id][fMaxRangos]) return 1; //afirmativo, tiene acceso
	}
	return 0;
}

stock TieneArmamento(id)
{
	new count = 0;
	Loop(x, 20, 0) if (InfoFaccion[id][fEquipo][x] != 0) { count++; }
	return count;
}

stock TieneSkin(id)
{
	new count = 0;
	Loop(x, 20, 0) if (InfoFaccion[id][fSkin][x] != 0) { count++; }
	return count;
}

OnFaction(faction)
{
	new count;
	foreach(new playerid: Player) if (IsPlayerConnectedEx(playerid) && IsPlayerFaction(playerid, faction))
	{
		count++;
	}
	return count;
}
