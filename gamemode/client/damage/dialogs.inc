ShowPlayerHeridas(playerid, playerid2)
{
	new str[400], longstr[3072], title[128], count = 0;
	Loop(e, MAX_HERIDAS, 0) { if (InfoHerida[playerid][e][dmgDamage] >= 1) count++; }
	if (count == 0) return SendPlayerChatMessage(playerid2, COLOR_GREY, "* Ese jugador no tiene ninguna herida.");
	Loop(e, MAX_HERIDAS, 0)
	{
		if (InfoHerida[playerid][e][dmgDamage] >= 1)
		{
			format(str, sizeof str, "{FFFFFF}%d dmg con {088A4B}%s{FFFFFF} ({E99D00}%s{FFFFFF}) hace %s\n", InfoHerida[playerid][e][dmgDamage], GetNameArma(InfoHerida[playerid][e][dmgWeapon]), GetNameHeridas(InfoHerida[playerid][e][dmgBodypart]), Segundos_tiempo(gettime()-InfoHerida[playerid][e][dmgSeconds]));
			strcat(longstr, str);
		}
		else if(InfoHerida[playerid][e][dmgDamage] != 0 && e >= MAX_HERIDAS)
		{
			format(str, sizeof str, "{FFFFFF}Parece que sufre muchos daños ...");
			strcat(longstr, str);
		}
	}
	format(title, sizeof title, "Lesiones de {088A4B}%s", GetNameFormat(playerid));
	Dialog_Show(playerid2, ShowInvalido, DIALOG_STYLE_LIST, title, longstr, "Cerrar", "");
	return 1;
}