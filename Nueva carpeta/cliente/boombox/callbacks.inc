forward ReproducirBoombox(playerid, music[]);
public ReproducirBoombox(playerid, music[])
{
	if(InfoBoombox[playerid][BB_obj])
	{
		foreach(Player, i) if (IsPlayerConnectedEx(i) && InfoPersonaje[i][pTogMusic] == 1)
		{
			if(IsPlayerInDynamicArea(i, InfoBoombox[playerid][BB_area]))
			{
			    if (TipoAudio[playerid] == 0 || TipoAudio[playerid] == 1)
			    {
					PlayStream(i, music, InfoBoombox[playerid][BB_x], InfoBoombox[playerid][BB_y], InfoBoombox[playerid][BB_z], 30.0, 1);
					TipoAudio[i] = 1;
				}
			}
		}
		SetPVarString(playerid, "BBStation", music);
	}
	return 1;
}