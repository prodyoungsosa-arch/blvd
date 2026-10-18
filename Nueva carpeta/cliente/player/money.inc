#define GetPlayerCash(%0) InfoPersonaje[%0][pDinero]
GivePlayerCash(playerid, money, reason[])
{
	new gformat[128], money_new = 0, gregistros[256];
	//diseño + log normal
	new f_string[32];
	format(f_string, sizeof f_string, "%d", money);
	if (!isnumeric(f_string))
	{
	    format(gregistros, sizeof gregistros, "[-] %s perdió %s$, razón: [%s]", NombreDeCuenta(playerid), diner_coma(money), reason);
		format(gformat, sizeof gformat, "~r~~h~ %s$", diner_coma(money));
		PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
	}
	else
	{
	    format(gregistros, sizeof gregistros, "[+] %s recibió %s$, razón: [%s]", NombreDeCuenta(playerid), diner_coma(money), reason);
		format(gformat, sizeof gformat, "~g~~h~ %s$", diner_coma(money));
		PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
	}
	Log("f_logs/MoneyUwU.txt", gregistros);
	//log si supera 50k
	if (money >= 50000)
	{
		new rse[190];
		format(rse, sizeof rse, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) recibió $%s [razón: %s]", NombreOriginal(playerid), playerid, diner_coma(money), reason);
		SendAdminMessage(0xFFFFFFFF, rse);
		format(rse, sizeof rse, "%s recibió $%s [razón: %s]", NombreOriginal(playerid), diner_coma(money), reason);
		Log("f_logs/ExagerarMoneyUwU.txt", rse);
	}
	if (GetTextDraw[playerid] == 0)
	{
		GetTextDraw[playerid] = 1;
		PlayerTextDrawSetStringEx(playerid, draw_money[playerid], gformat);
		PlayerTextDrawShow(playerid, draw_money[playerid]);
		SetTimerEx("HideDrawMoney", 4000, false, "d", playerid);
	}
	//ceder dinero
	money_new = InfoPersonaje[playerid][pDinero] + money;
	InfoPersonaje[playerid][pDinero] = money_new;
	GivePlayerMoney(playerid, money);
	guardar_int_mysql("personajes", "BolosUwU", InfoPersonaje[playerid][pID], money_new);
	return 1;
}

forward HideDrawMoney(playerid);
public HideDrawMoney(playerid)
{
	GetTextDraw[playerid] = 0;
	PlayerTextDrawHide(playerid, draw_money[playerid]);
}

CheckMoney(playerid, money)
{
	new b[190], xx;
	xx = money - (GetPlayerCash(playerid));
	if (GetPlayerCash(playerid) >= money)
	{
		return 1;
	}
	else
	{
		format(b, sizeof b, "No tienes dinero suficiente! Te faltan {F72222}$%s", diner_coma(xx));
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, b);
		return 0;
	}
}

stock diner_coma(e_number) /* By adri1 - SFR3 4.3 */
{
	new f_string[24], bool:negative;
	format(f_string, sizeof f_string, "%d", e_number);
	if(e_number < 0)
	{
		negative = true;
		strdel(f_string, 0, 1);
	}

	new numbers = strlen(f_string);
	while(numbers > 3)
	{
		numbers -= 3;
		strins(f_string, ",", numbers);
	}

	if(negative) strins(f_string, "-", 0);
	return f_string;
}