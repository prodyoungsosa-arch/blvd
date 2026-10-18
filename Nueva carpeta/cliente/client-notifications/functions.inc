stock gn_FindGoodNotePosById(playerid, goodnoteid)
{
	for(new i = 0; i < MAX_GOOD_NOTES; i++)
	{
		if(GoodNoteData[playerid][i][GOOD_NOTE_ID] == goodnoteid) return i;
	}
	return -1;
}
stock gn_GetFreeNotePos(playerid)
{
	for(new i = 0; i < MAX_GOOD_NOTES; i++)
	{
		if(GoodNoteData[playerid][i][GOOD_NOTE_ID] == 0) {
			return i;
		}
	}
	return -1;
}

stock gn_GetLineOfString(const string[])
{
	new lines_count = 1;
	lines_count = strlen(string)/23;
	return lines_count;
}

stock gn_GetLines(const cadena[])
{
    new count = 0;
    new len = strlen(cadena);

    for (new i = 0; i < len; i++)
    {
        if (cadena[i] == '\n')
        {
            count++;
        }
    }
    return count;
}

stock SetGoodNoteSound(sound)
{
	GoodNoteSound = sound;
	return 1;
}

stock SetGoodNoteDirection(type)
{
	switch(type)
	{
		case GN_DIRECTION_UP, GN_DIRECTION_DOWN:
		{
			GoodNoteDirection = type;
			return 1;
		}
	}
	return 0;
}

stock SetGoodNotePos(Float:pos_x, Float:pos_y)
{
	GoodNotePosX = pos_x;
	GoodNotePosY = pos_y;
	return 1;
}

static stock bool:IsLeapYear(year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static const MONTH_DAYS[12]	= {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

stock Timestamp(year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, hourGMT = 0, minuteGMT = 0) {
    static const
		SECONDS_PER_MINUTE = 60,
		SECONDS_PER_HOUR = 3600,
		SECONDS_PER_DAY = 86400;

	new timestamp = 0;

	if (year == 0 || month == 0 || day == 0) {
	    getdate(year, month, day);
	    gettime(hour, minute, second);
	}

	for (new i = EPOCH_YEAR; i < year; i++)
	    day += (IsLeapYear(i) == true) ? 365 : 366;

	for (new i = 1; i < month; i++)
		day += MONTH_DAYS[i - 1];

	if (IsLeapYear(year) == true && month > 2)
	    day += 1;

    timestamp += ((day - 1) * SECONDS_PER_DAY);
    timestamp += ((hour + hourGMT) * SECONDS_PER_HOUR);
    timestamp += ((minute + minuteGMT) * SECONDS_PER_MINUTE);
    timestamp += second;

	return timestamp;
}

stock CrearNotificacion(playerid, const icon[], const text[], time = 0, color = -1, bg_color = 255, sound = 1, const size = sizeof(text),tipo = 0,noti = 90)
{
	if(noti < 10 && TiempoNotificaciones[playerid][noti] != 0) return 1;

	#pragma unused size
	static
	free_pos,
	lines_count,
	Float:size_bg,
	Float:pos_y;


	free_pos = gn_GetFreeNotePos(playerid);		
	if(free_pos == -1) return 0;

    // Icono
	new TextoNotificacion[200];
	format(TextoNotificacion, sizeof(TextoNotificacion), "%s", icon);
	format(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT_I], MAX_GOOD_TEXT_LENGTH, TextoNotificacion);
	
    // Texto culiao
    format(TextoNotificacion, sizeof(TextoNotificacion), "%s",text);
	format(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT], MAX_GOOD_TEXT_LENGTH, TextoNotificacion);
	
    lines_count = gn_GetLineOfString(TextoNotificacion);

	if(tipo == 1) lines_count = 3; //general
	if(tipo == 2) lines_count = 3; // Default SAPD
	if(tipo == 3) lines_count = 4; // Crimenes

	size_bg = 1.2 + (lines_count * 1.4);

	pos_y = GoodNotePosY;
	for(new i; i < free_pos; i++)
	{
		if(GoodNoteDirection == GN_DIRECTION_DOWN) {
			pos_y += 13.0 + (GoodNoteData[playerid][i][GOOD_NOTE_LINES] * 16.0) + 6.0;
		} else {
			pos_y -= 13.0 + (GoodNoteData[playerid][i][GOOD_NOTE_LINES] * 16.0) + 6.0;
		}
	}
	if(lines_count > 1 && GoodNoteDirection == GN_DIRECTION_UP) {
		pos_y -= (lines_count - 1) * 16.0;
	}
	GoodNoteData[playerid][free_pos][GOOD_NOTE_TYPE] = tipo;
	GoodNoteData[playerid][free_pos][GOOD_NOTE_LINES] = lines_count;
	GoodNoteData[playerid][free_pos][GOOD_NOTE_COL_BG] = bg_color;
	GoodNoteData[playerid][free_pos][GOOD_NOTE_COL_TEXT] = color;
	new PlayerText:temp_td;

	if(strfind(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT_I], "none", true) != -1)
	{
		format(TextoNotificacion, sizeof(TextoNotificacion), "%s",Desbug(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT]));	
	}
	else
	{
		format(TextoNotificacion, sizeof(TextoNotificacion), "____%s",Desbug(TextoNotificacion));
	}

	temp_td = CreatePlayerTextDraw(playerid, GoodNotePosX, pos_y+lines_count, TextoNotificacion);
	PlayerTextDrawLetterSize(playerid, temp_td, 0.271250, 1.383465);
	PlayerTextDrawTextSize(playerid, temp_td, 607.500000, size_bg);
	PlayerTextDrawAlignment(playerid, temp_td, 1);
	PlayerTextDrawColor(playerid, temp_td, color);
	PlayerTextDrawUseBox(playerid, temp_td, true);
	PlayerTextDrawSetShadow(playerid, temp_td, 0);
	PlayerTextDrawSetOutline(playerid, temp_td, 0);
	PlayerTextDrawBackgroundColor(playerid, temp_td, 100996095);
	PlayerTextDrawBoxColor(playerid, temp_td, 0x131416FF);
	PlayerTextDrawFont(playerid, temp_td, 1);
	PlayerTextDrawSetProportional(playerid, temp_td, 1);
	PlayerTextDrawShow(playerid, temp_td);
	GoodNoteLastId++;
	GoodNoteData[playerid][free_pos][GOOD_NOTE_TD_TEXT] = temp_td;

	if(strfind(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT_I], "none", true) != -1)
	{
		//
	}
	else
	{
		format(TextoNotificacion, sizeof(TextoNotificacion), "%s", Desbug(GoodNoteData[playerid][free_pos][GOOD_NOTE_TEXT_I]));
		temp_td = CreatePlayerTextDraw(playerid, GoodNotePosX, pos_y+1.3, TextoNotificacion);
		PlayerTextDrawLetterSize(playerid, temp_td, 0.000000, 0.000000);
		PlayerTextDrawTextSize(playerid, temp_td, 13.125000, 13.125000);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawFont(playerid, temp_td, 4);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][GOOD_NOTE_ICO] = temp_td;
	}

	if(GoodNoteData[playerid][free_pos][GOOD_NOTE_TYPE] == 1) //Basurero
	{
		Noti_Basurero[playerid] = free_pos;

		temp_td = CreatePlayerTextDraw(playerid, 499.000000, pos_y+1.5, "LD_BEAT:CHIT");
	    PlayerTextDrawFont(playerid, temp_td, 4);
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.600000, 2.000000);
	    PlayerTextDrawTextSize(playerid, temp_td, 13.000000, 13.000000);
	    PlayerTextDrawSetOutline(playerid, temp_td, 1);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, -1);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 255);
	    PlayerTextDrawBoxColor(playerid, temp_td, 50);
	    PlayerTextDrawUseBox(playerid, temp_td, 1);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
	    PlayerTextDrawSetSelectable(playerid, temp_td, 0);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][GENERAL_TD][2] = temp_td;
    
	    temp_td = CreatePlayerTextDraw(playerid, 505.000000, pos_y+2.5, "!");
	    PlayerTextDrawFont(playerid, temp_td, 1);
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.175416, 0.983465);
	    PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
	    PlayerTextDrawSetOutline(playerid, temp_td, 0);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, 1296911871);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 255);
	    PlayerTextDrawBoxColor(playerid, temp_td, 100996095);
	    PlayerTextDrawUseBox(playerid, temp_td, 0);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
	    PlayerTextDrawSetSelectable(playerid, temp_td, 0);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][GENERAL_TD][1] = temp_td;
		
		temp_td = CreatePlayerTextDraw(playerid, 514.000000,  pos_y+2.5,  "Alerta policial");
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.192083, 1.083465);
	    PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, -1);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawSetOutline(playerid, temp_td, 1);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
	    PlayerTextDrawFont(playerid, temp_td, 1);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
	    GoodNoteData[playerid][free_pos][GENERAL_TD][0] = temp_td;

	    temp_td = CreatePlayerTextDraw(playerid, 501.000000, pos_y+17.0, "_");
	    PlayerTextDrawFont(playerid, temp_td, 1);
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
	    PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
	    PlayerTextDrawSetOutline(playerid, temp_td, 0);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, 1296911871);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 255);
	    PlayerTextDrawBoxColor(playerid, temp_td, 0xf1f1f1ff);
	    PlayerTextDrawUseBox(playerid, temp_td, 0);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
	    GoodNoteData[playerid][free_pos][GENERAL_TD_TEXT] = temp_td;
		
	}	

	if(GoodNoteData[playerid][free_pos][GOOD_NOTE_TYPE] == 2) // Informe
	{
		Noti_Informe[playerid] = free_pos;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000,  pos_y+2.5,  InformePolicia1[playerid]);
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.192083, 1.083465);
	    PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, -1);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawSetOutline(playerid, temp_td, 0);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
	    PlayerTextDrawFont(playerid, temp_td, 1);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Informe1] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+17, InformePolicia2[playerid]);
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Informe2] = temp_td;
	}

	if(GoodNoteData[playerid][free_pos][GOOD_NOTE_TYPE] == 3) // Crimenes
	{
		Noti_Crimen[playerid] = free_pos;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000,  pos_y+5,  InformeCrimen1[playerid]); //-- [CENTRAL]
	    PlayerTextDrawLetterSize(playerid, temp_td, 0.192083, 1.083465);
	    PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
	    PlayerTextDrawAlignment(playerid, temp_td, 1);
	    PlayerTextDrawColor(playerid, temp_td, 0x7b88fbFF);
	    PlayerTextDrawSetShadow(playerid, temp_td, 0);
	    PlayerTextDrawSetOutline(playerid, temp_td, 0);
	    PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
	    PlayerTextDrawFont(playerid, temp_td, 1);
	    PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes1] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+20, InformeCrimen2[playerid]); //-- Articulo
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes2] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+38, InformeCrimen3[playerid]); //-- Aplicado a...
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes3] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+43+5, InformeCrimen4[playerid]); //-- Localizacion
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes4] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+48+10, InformeCrimen5[playerid]); //-- Gravedad
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes5] = temp_td;

		temp_td = CreatePlayerTextDraw(playerid, 498.875000, pos_y+53+15, InformeCrimen6[playerid]); //-- Reportado por
		PlayerTextDrawLetterSize(playerid, temp_td, 0.154583, 0.883465);
		PlayerTextDrawTextSize(playerid, temp_td, 607.500000, 1.383465);
		PlayerTextDrawAlignment(playerid, temp_td, 1);
		PlayerTextDrawColor(playerid, temp_td, -1);
		PlayerTextDrawSetShadow(playerid, temp_td, 0);
		PlayerTextDrawSetOutline(playerid, temp_td, 0);
		PlayerTextDrawBackgroundColor(playerid, temp_td, 51);
		PlayerTextDrawFont(playerid, temp_td, 1);
		PlayerTextDrawSetProportional(playerid, temp_td, 1);
		PlayerTextDrawShow(playerid, temp_td);
		GoodNoteData[playerid][free_pos][Crimenes6] = temp_td;
	}

	if(time == 0) {
		GoodNoteData[playerid][free_pos][GOOD_NOTE_TIME_OUT] = 0;
		GoodNoteData[playerid][free_pos][GOOD_NOTE_TIMER] = 0;
	} else {
		GoodNoteData[playerid][free_pos][GOOD_NOTE_TIME_OUT] = time + Timestamp();
		GoodNoteData[playerid][free_pos][GOOD_NOTE_NOTI] = noti;
		if(noti < 10 && noti != 90) TiempoNotificaciones[playerid][noti] = 6;
		GoodNoteData[playerid][free_pos][GOOD_NOTE_TIMER] = SetTimerEx("DestroyGoodNote", time * 1000, false, "dd", playerid, GoodNoteLastId);
	}
	if(sound) {
		PlayerPlaySound(playerid, GoodNoteSound, 0.0, 0.0, 0.0);
	}
	GoodNoteData[playerid][free_pos][GOOD_NOTE_ID] = GoodNoteLastId;

	return GoodNoteLastId;
}

forward DestroyGoodNote(playerid, goodnoteid);
public DestroyGoodNote(playerid, goodnoteid)
{
	static pos;
	pos = gn_FindGoodNotePosById(playerid, goodnoteid);
	if(pos == -1) return 1;

	if(GoodNoteData[playerid][pos][GOOD_NOTE_TIMER] != 0) {
		KillTimer(GoodNoteData[playerid][pos][GOOD_NOTE_TIMER]);
	}

	PlayerTextDrawHide(playerid, GoodNoteData[playerid][pos][GOOD_NOTE_TD_TEXT]);
	PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GOOD_NOTE_TD_TEXT]);

	GoodNoteData[playerid][pos][GOOD_NOTE_ID] = 0;

	if(strfind(GoodNoteData[playerid][pos][GOOD_NOTE_TEXT_I], "none", true) != -1)
	{
		//
	}
	else
	{
		PlayerTextDrawHide(playerid, GoodNoteData[playerid][pos][GOOD_NOTE_ICO]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GOOD_NOTE_ICO]);
	}

	if(GoodNoteData[playerid][pos][GOOD_NOTE_TYPE] == 1)
	{
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GENERAL_TD][0]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GENERAL_TD][1]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GENERAL_TD][2]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GENERAL_TD][3]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][GENERAL_TD_TEXT]);
	}

	if(GoodNoteData[playerid][pos][GOOD_NOTE_TYPE] == 2) //-- Informes
	{	
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Informe1]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Informe2]);
	}

	if(GoodNoteData[playerid][pos][GOOD_NOTE_TYPE] == 3) //-- Crimenes
	{	
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes1]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes2]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes3]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes4]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes5]);
		PlayerTextDrawDestroy(playerid, GoodNoteData[playerid][pos][Crimenes6]);
	}
 		
 	if(GoodNoteData[playerid][pos][GOOD_NOTE_NOTI] < 10){ TiempoNotificaciones[playerid][GoodNoteData[playerid][pos][GOOD_NOTE_NOTI]] = 0; }
	GoodNoteData[playerid][pos][GOOD_NOTE_NOTI] = 90;
	if(pos + 1 >= MAX_GOOD_NOTES) return 1;
	for(new j = pos + 1, time; j < MAX_GOOD_NOTES; j++)
	{
		if(GoodNoteData[playerid][j][GOOD_NOTE_ID] == 0) continue;
		if(GoodNoteData[playerid][j][GOOD_NOTE_TIME_OUT] == 0) {
			CrearNotificacion(
			playerid,GoodNoteData[playerid][j][GOOD_NOTE_TEXT_I], GoodNoteData[playerid][j][GOOD_NOTE_TEXT], 0,
			GoodNoteData[playerid][j][GOOD_NOTE_COL_TEXT], GoodNoteData[playerid][j][GOOD_NOTE_COL_BG], 0
			,300,GoodNoteData[playerid][j][GOOD_NOTE_TYPE],GoodNoteData[playerid][j][GOOD_NOTE_NOTI]);
		} else {
			time = GoodNoteData[playerid][j][GOOD_NOTE_TIME_OUT] - Timestamp();
			if(time > 0) {
				CrearNotificacion(
				playerid,GoodNoteData[playerid][j][GOOD_NOTE_TEXT_I], GoodNoteData[playerid][j][GOOD_NOTE_TEXT], time,
				GoodNoteData[playerid][j][GOOD_NOTE_COL_TEXT], GoodNoteData[playerid][j][GOOD_NOTE_COL_BG], 0
				,300,GoodNoteData[playerid][j][GOOD_NOTE_TYPE],GoodNoteData[playerid][j][GOOD_NOTE_NOTI]);
			}
		}
		DestroyGoodNote(playerid, GoodNoteData[playerid][j][GOOD_NOTE_ID]);
		return 1;
	}
	return 1;
}

stock ShowNoti(playerid, const icon[], const texto[]) {
   
    new TextoCadena[600];
    format(TextoCadena, sizeof(TextoCadena), Desbug("%s"), texto);
    CrearNotificacion(playerid, icon, TextoCadena, 10, 0xFFFFFFDD,0x000000FF);
    
    return 1;
}

stock CrearInforme(const razon[], const desc[])
{
    foreach(new i : Player)
    {
        new fac_user = InfoPersonaje[i][pMiembro];

        if(!fac_user || InfoFaccion[fac_user][fTipo] != 1 || OnDuty[i] == 0) continue;

        format(InformePolicia1[i], 60,"~b~%s", Desbug(razon));
        format(InformePolicia2[i], 150, "~w~%s", Desbug(desc));
        CrearNotificacion(i,"none", "~n~~n~~n~", 8, -1, 255, 1, 255, 2, 90);
    }
    return 1;
}

stock CrearCrimen(const title[], const reason[], playerid, gravedad)
{
	new GPS_EX[28],gravedadplayer[32];
	new Float:X_pos,Float:Y_pos,Float:Z_pos;

	switch(gravedad)
	{
		case 1: gravedadplayer = "~w~leve";
		case 2: gravedadplayer = "~w~moderado";
		case 3: gravedadplayer = "~w~grave";
	}

	new str[64];
	GetPlayerPos(playerid, X_pos, Y_pos, Z_pos);
	GetZoneName(X_pos, Y_pos, GPS_EX, 60);
	format(str, sizeof(str), "%s", Desbug(GPS_EX));

    foreach(new i : Player)
    {
        new fac_user = InfoPersonaje[i][pMiembro];

        if(!fac_user || InfoFaccion[fac_user][fTipo] != 1 || OnDuty[i] == 0) continue;

        format(InformeCrimen1[i], 60,"~b~[CENTRAL] ~w~%s", Desbug(title));
        format(InformeCrimen2[i], 60, "~r~%s", Desbug(reason));
		format(InformeCrimen3[i], 60, "~w~Aplicado a: ~r~Un sospechoso.");
		format(InformeCrimen4[i], 60, "~w~Localizacion: ~g~%s", Desbug(str));
		format(InformeCrimen5[i], 60, "~w~Gravedad: %s", Desbug(gravedadplayer));
		format(InformeCrimen6[i], 60, "~w~Reportado por: ~b~CENTRAL");
        CrearNotificacion(i,"none", "~n~~n~~n~~n~~n~~n~", 8, -1, 255, 1, 255, 3, 90);
    }
}

stock Desbug(const string[])
{
	new
	szFixed[1024],
	iPos,
	iLen; 

	for (iLen = strlen(string); iPos < iLen; iPos ++)
	switch (string[iPos])
		{
		case 'à':   szFixed[iPos] = 151;
		case 'á':   szFixed[iPos] = 152;
		case 'â':   szFixed[iPos] = 153;
		case 'ä':   szFixed[iPos] = 154;
		case 'À':   szFixed[iPos] = 128;
		case 'Á':   szFixed[iPos] = 129;
		case 'Â':   szFixed[iPos] = 130;
		case 'Ä':   szFixed[iPos] = 131;
		case 'è':   szFixed[iPos] = 157;
		case 'é':   szFixed[iPos] = 158;
		case 'ê':   szFixed[iPos] = 159;
		case 'ë':   szFixed[iPos] = 160;
		case 'È':   szFixed[iPos] = 134;
		case 'É':   szFixed[iPos] = 135;
		case 'Ê':   szFixed[iPos] = 136;
		case 'Ë':   szFixed[iPos] = 137;
		case 'ì':   szFixed[iPos] = 161;
		case 'í':   szFixed[iPos] = 162;
		case 'î':   szFixed[iPos] = 163;
		case 'ï':   szFixed[iPos] = 164;
		case 'Ì':   szFixed[iPos] = 138;
		case 'Í':   szFixed[iPos] = 139;
		case 'Î':   szFixed[iPos] = 140;
		case 'Ï':   szFixed[iPos] = 141;
		case 'ò':   szFixed[iPos] = 165;
		case 'ó':   szFixed[iPos] = 166;
		case 'ô':   szFixed[iPos] = 167;
		case 'ö':   szFixed[iPos] = 168;
		case 'Ò':   szFixed[iPos] = 142;
		case 'Ó':   szFixed[iPos] = 143;
		case 'Ô':   szFixed[iPos] = 144;
		case 'Ö':   szFixed[iPos] = 145;
		case 'ù':   szFixed[iPos] = 169;
		case 'ú':   szFixed[iPos] = 170;
		case 'û':   szFixed[iPos] = 171;
		case 'ü':   szFixed[iPos] = 172;
		case 'Ù':   szFixed[iPos] = 146;
		case 'Ú':   szFixed[iPos] = 147;
		case 'Û':   szFixed[iPos] = 148;
		case 'Ü':   szFixed[iPos] = 149;
		case 'ñ':   szFixed[iPos] = 174;
		case 'Ñ':   szFixed[iPos] = 173;
		case '¡':   szFixed[iPos] = 64;
		case '¿':   szFixed[iPos] = 175;
		case '`':   szFixed[iPos] = 177;
		case '&':   szFixed[iPos] = 38;
		default:    szFixed[iPos] = string[iPos];
	}
	return szFixed;
}

stock PUSH(playerid, const text_[])
{
	new mensaje[250];
	format(mensaje, sizeof(mensaje),"%s", Desbug(text_));
	if(IsPlayerConnected(playerid) && !IsPlayerNPC(playerid)) CrearNotificacion(playerid,"none", text, 5,0xFFFFFFDD,0x000000FF);
	return 1;
}

stock SendFormatNotification(playerid, const text[], {Float, _}:...) {
	static
	    args,
	    str[192];

	if ((args = numargs()) <= 2) {
	    ShowTDN(playerid, text);
	} else {
		while (--args >= 2) {
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 192
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit ADD
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4


        CrearNotificacion(playerid,"none", str, 10, 0xFFFFFFDD, 0x000000FF);

		#emit RETN
	}
	return 1;
}

stock NotificationsConnect(playerid)
{
	Noti_Informe[playerid] = -1;
	GoodNoteLastId = 0;
	Noti_Basurero[playerid] = -1;
	SaltosInforme[playerid] = 0;
}