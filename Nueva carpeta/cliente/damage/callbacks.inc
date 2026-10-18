forward estado_xdxdxd(playerid, type);
public estado_xdxdxd(playerid, type)
{
	SetPVarInt(playerid, "PlayerCuffed", 0);
	switch (type)
	{
	    case 1:
	    {
			new killerid = player_asesino[playerid];
			new reason = player_weapon[playerid];
			// /qfa
			if (IsPlayerConnected(killerid)) { alm(QFA[playerid], GetNameFormat(killerid)); }
			//aviso muerte staff
			new gformat[256], dead[20];
			switch(reason)
			{
				case 54:                    {dead="Suicidio";}
				case 49:                    {dead="Atropellado";}
				case 50:                    {dead="Heli-Kill";}
				case 53:                    {dead="Ahogado";}
				case 255: 					{dead="Quemado/Bug";}
				case 51:    				{dead="Explotado";}
				case 47:                    {dead="Fake Pistol";}
				default:                   {dead="Desconocida";}
			}
			if (reason >= 0 && reason <= 42)
			{
				format(gformat, sizeof gformat, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) mató a %s(%d). Weapon: %s", GetNameFormat(killerid), killerid, GetNameFormat(playerid), playerid, WeaponNames[reason]);
				SendAdminMessage(0xFFFFFFFF, gformat);
			}
			else if (reason >= 47 && reason <= 255) // Anteriormente 54.
			{
				if(pDroga[playerid][Sobredosis]) format(gformat, sizeof gformat, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) murió por posible bug/muerte sin rol. Razón: Sobredosis", GetNameFormat(playerid), playerid);
				else format(gformat, sizeof gformat, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) murió por posible bug/muerte sin rol. Razón: %s", GetNameFormat(playerid), playerid, dead);
				SendAdminMessage(0xFFFFFFFF, gformat);
			}
			//animacion
			if (gPlayerUsingLoopingAnim[playerid] == 1)
			{
		        gPlayerUsingLoopingAnim[playerid] = 0;
			}
			//anim
			anim_muerte(playerid);
			//label's
			InfoPersonaje[playerid][pMuerto] = 1;
			//mensaje
			SendClientMessageEx(playerid, 0xE99D00FF, "Si un médico no llega a salvarte. Puedes aceptar tu muerte con /volver.");
			SendClientMessageEx(playerid, 0xE99D00FF, "Fuiste herido %d veces, usa /heridas %d para ver sus lesiones.", VecesHerido[playerid], playerid);
			SendClientMessageEx(playerid, 0x6D88F8FF, "La gente a los alrededores daria aviso a emergencias. (Usa: /dentorno)");
			//Vida
			InfoPersonaje[playerid][pVida] = 80;
			dar_chaleco(playerid, 0);
			timer_herido[playerid] = 240;
			new query[190];
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Vida = '%f', Muerto = 1 WHERE ID = '%d'", InfoPersonaje[playerid][pVida], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
		}
		case 2:
		{
			InfoPersonaje[playerid][pMuerto] = 2;
			timer_herido[playerid] = 120;
			MensajeMuelto[playerid] = 1;
			anim_muerte(playerid);
			new query[190];
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Vida = '%f', Muerto = 1 WHERE ID = '%d'", InfoPersonaje[playerid][pVida], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
		}
	}
	return 1;
}
