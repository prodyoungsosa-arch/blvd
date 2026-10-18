Label_cajero(id, type)
{
	//info new
	new atm_label[470];
	format(atm_label, sizeof atm_label, "{EBEBEB}ATM {F5DEB3}%d\n{EBEBEB}Dinero: {00CC00}$%s\n{EBEBEB}Aquí puedes usar {F5DEB3}/cajero{EBEBEB} para tus operaciones", id, diner_coma(InfoCajero[id][atmDinero]));
	if (type == 1)
	{
		if (IsValidDynamicObject(InfoCajero[id][atmObject])) DestroyDynamicObject(InfoCajero[id][atmObject]);
		InfoCajero[id][atmObject] = 0;
		if (IsValidDynamic3DTextLabel(InfoCajero[id][atmLabel]))
		{
			DestroyDynamic3DTextLabel(InfoCajero[id][atmLabel]);
			InfoCajero[id][atmLabel] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoCajero[id][atmObject] = CreateDynamicObject(InfoCajero[id][atmModelo], InfoCajero[id][atmPotX], InfoCajero[id][atmPotY], InfoCajero[id][atmPotZ], InfoCajero[id][atmRotX], InfoCajero[id][atmRotY], InfoCajero[id][atmRotZ], .interiorid = InfoCajero[id][atmInterior], .worldid = InfoCajero[id][atmVirtualWorld]);
		InfoCajero[id][atmLabel] = CreateDynamic3DTextLabel(atm_label, -1, InfoCajero[id][atmPotX], InfoCajero[id][atmPotY], InfoCajero[id][atmPotZ] + 0.4, 8.0, .interiorid = InfoCajero[id][atmInterior], .worldid = InfoCajero[id][atmVirtualWorld]);
	}
	else UpdateDynamic3DTextLabelText(InfoCajero[id][atmLabel], -1, atm_label);
}