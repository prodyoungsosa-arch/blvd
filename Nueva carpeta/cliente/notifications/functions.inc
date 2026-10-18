#if defined _notification_functions_
    #endinput
#endif
#define _notification_functions_

static GetFreeNotificationSlot(playerid)
{
    for (new i; i < MAX_NOTIFICATIONS; ++i)
	{
		if (!g_rgeNotificationData[playerid][i][e_bActive])
		    return i;
	}
    return MAX_NOTIFICATIONS + 1;
}

NotificationShowAll(playerid, index)
{
    PlayerTextDrawShow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0]);
    PlayerTextDrawShow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1]);
    PlayerTextDrawShow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2]);
    return 1;
}

static CreateNotificationTD(playerid, index, const text[], color)
{
    g_rgeNotificationData[playerid][index][e_tdTextdraw][0] = CreatePlayerTextDraw(playerid, 55.000000, 135.000000, !"_");
    PlayerTextDrawFont(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 1);
    PlayerTextDrawLetterSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 0.574999, 4.399980);
    PlayerTextDrawTextSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 298.500000, 75.000000);
    PlayerTextDrawSetOutline(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 1);
    PlayerTextDrawSetShadow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 0);
    PlayerTextDrawAlignment(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 2);
    PlayerTextDrawColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], -1);
    PlayerTextDrawBackgroundColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 255);
    PlayerTextDrawBoxColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], color);
    PlayerTextDrawUseBox(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 1);
    PlayerTextDrawSetProportional(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 1);
    PlayerTextDrawSetSelectable(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 0);

    g_rgeNotificationData[playerid][index][e_tdTextdraw][1] = CreatePlayerTextDraw(playerid, 100.000000, 135.000000, !"_");
    PlayerTextDrawFont(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 1);
    PlayerTextDrawLetterSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 0.975000, 4.399980);
    PlayerTextDrawTextSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 281.500000, 159.500000);
    PlayerTextDrawSetOutline(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 1);
    PlayerTextDrawSetShadow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 0);
    PlayerTextDrawAlignment(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 2);
    PlayerTextDrawColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], -1);
    PlayerTextDrawBackgroundColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 255);
    PlayerTextDrawBoxColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 454761471);
    PlayerTextDrawUseBox(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 1);
    PlayerTextDrawSetProportional(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 1);
    PlayerTextDrawSetSelectable(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 0);

    g_rgeNotificationData[playerid][index][e_tdTextdraw][2] = CreatePlayerTextDraw(playerid, 22.000000, 136.000000, text);
    PlayerTextDrawFont(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 1);
    PlayerTextDrawLetterSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 0.174999, 1.049999);
    PlayerTextDrawTextSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 0);
    PlayerTextDrawSetShadow(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 0);
    PlayerTextDrawAlignment(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 1);
    PlayerTextDrawColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], -134744065);
    PlayerTextDrawBackgroundColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 255);
    PlayerTextDrawBoxColor(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 50);
    PlayerTextDrawUseBox(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 0);
    PlayerTextDrawSetProportional(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 1);
    PlayerTextDrawSetSelectable(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 0);
    return 1;
}

Notification_Show(playerid, const text[], time, color = 0xFCCF3AFF)
{
    new index = GetFreeNotificationSlot(playerid);
    new dbg[64]; format(dbg, sizeof(dbg), "DEBUG 0 - index: %d", index);
    SendClientMessage(playerid, -1, dbg);
    if (index > MAX_NOTIFICATIONS)
        return 0;

    g_rgeNotificationData[playerid][index][e_bActive] = true;
    g_rgeNotificationData[playerid][index][e_iFrameCount] = 0;
    g_rgeNotificationData[playerid][index][e_fHeight] = 0.0;
    KillTimer(g_rgeNotificationData[playerid][index][e_iFrameTimer]);

    new fixed_text[512];
    strcat(fixed_text, text);
    Fix_GT(fixed_text);

    SplitTextDrawString(fixed_text, 155.0, 0.174999, 1, 0, true);
    CreateNotificationTD(playerid, index, fixed_text, color);

    new line_count = GetTextDrawLineCount(fixed_text);
    g_rgeNotificationData[playerid][index][e_fHeight] += float(line_count) + 0.3;
    
    PlayerTextDrawLetterSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 0.975000, g_rgeNotificationData[playerid][index][e_fHeight]);
    PlayerTextDrawLetterSize(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 0.975000, g_rgeNotificationData[playerid][index][e_fHeight]);

    new Float:pos_y = 135.000000;
    SendClientMessage(playerid, -1, "Debug 1");
    if (index)
    {
        new Float:pos_x;
        PlayerTextDrawGetPos(playerid, g_rgeNotificationData[playerid][index - 1][e_tdTextdraw][0], pos_x, pos_y);
        #pragma unused pos_x

        PlayerTextDrawGetString(playerid, g_rgeNotificationData[playerid][index - 1][e_tdTextdraw][2], fixed_text);
        line_count = GetTextDrawLineCount(fixed_text);
        pos_y += (line_count * 10.0) + 10.0;

        PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 55.000000, pos_y);
        PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 100.000000, pos_y);
        PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 22.000000, pos_y + 1.0);
    }
    SendClientMessage(playerid, -1, "Debug 2");
    g_rgeNotificationData[playerid][index][e_iFrameTimer] = SetTimerEx("NotificationMoveToRight", 15, true, "dddffd", playerid, index, time, pos_y, 300.0, 5);
    SendClientMessage(playerid, -1, "Debug 3");
    return 1;
}

ShowLoadScreen(playerid, time)
{
    for(new i = 0; i < 4; i++) { PlayerTextDrawShow(playerid, p_tdLoad[playerid][i]); }
    TogglePlayerControllable(playerid, false);
    r_rgiLoadTimer[playerid] = SetTimerEx("HideLoadScreen", time, false, "i", playerid);
    SetPVarInt(playerid, "LoadingObjects", 1);
    ClearChat(playerid);
    return 1;
}

Notification_DestroyAll(playerid)
{
    for (new i = 0; i < MAX_NOTIFICATIONS; i++)
    {
        if (g_rgeNotificationData[playerid][i][e_bActive])
        {
            DestroyPlayerNotification(playerid, i);
        }
    }
    return 1;
}