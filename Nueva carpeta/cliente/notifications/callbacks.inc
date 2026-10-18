static Float:lerp(Float:start_value, Float:end_value, Float:pct)
{
    return (start_value + (end_value - start_value) * pct);
}

#if defined _notification_callbacks_
    #endinput
#endif
#define _notification_callbacks_

public OnPlayerDisconnect(playerid, reason)
{
    for (new i = 0; i < MAX_NOTIFICATIONS; i++)
    {
        if (g_rgeNotificationData[playerid][i][e_bActive])
        {
            DestroyPlayerNotification(playerid, i);
        }
    }


    #if defined NOTI_OnPlayerDisconnect
        return NOTI_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect NOTI_OnPlayerDisconnect
#if defined NOTI_OnPlayerDisconnect
    forward NOTI_OnPlayerDisconnect(playerid, reason);
#endif

forward DestroyPlayerNotification(playerid, index);
public DestroyPlayerNotification(playerid, index)
{
    g_rgeNotificationData[playerid][index][e_bActive] = false;
    PlayerTextDrawDestroy(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0]);
    PlayerTextDrawDestroy(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1]);
    PlayerTextDrawDestroy(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2]);
    KillTimer(g_rgeNotificationData[playerid][index][e_iFrameTimer]);
    return 1;
}

forward NotificationMoveToLeft(playerid, index, Float:pos_y, Float:max, count);
public NotificationMoveToLeft(playerid, index, Float:pos_y, Float:max, count)
{
	g_rgeNotificationData[playerid][index][e_iFrameCount] -= count;

    new Float:pct = floatdiv(g_rgeNotificationData[playerid][index][e_iFrameCount], max);
    new Float:pos_x = lerp(0.0, -100.0, easeInBack(pct)); // Salida

    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], 55.000000 - pos_x, pos_y);
    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 100.000000 - pos_x, pos_y);
    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], 22.000000 - pos_x, pos_y + 1.0);

    NotificationShowAll(playerid, index);
    
	if (pct <= -1.0)
	{
		g_rgeNotificationData[playerid][index][e_iFrameCount] = 0;
		DestroyPlayerNotification(playerid, index);
	}

	return 1;
}

forward NotificationWaitToLeft(playerid, index, Float:pos_y, Float:max, count);
public NotificationWaitToLeft(playerid, index, Float:pos_y, Float:max, count)
{
    KillTimer(g_rgeNotificationData[playerid][index][e_iFrameTimer]);
    g_rgeNotificationData[playerid][index][e_iFrameTimer] = SetTimerEx("NotificationMoveToLeft", 15, true, "ddffd", playerid, index, pos_y, 300.0, count);
	return 1;
}

forward NotificationMoveToRight(playerid, index, time, Float:pos_y, Float:max, count);
public NotificationMoveToRight(playerid, index, time, Float:pos_y, Float:max, count)
{
	g_rgeNotificationData[playerid][index][e_iFrameCount] += count;

    new Float:pct = floatdiv(g_rgeNotificationData[playerid][index][e_iFrameCount], max);
    new Float:pos_x = lerp(0.0, 100.0, easeOutElastic(pct)); // Entrada

    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][0], -45.000000 + pos_x, pos_y);
    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][1], 0.000000 + pos_x, pos_y);
    PlayerTextDrawSetPos(playerid, g_rgeNotificationData[playerid][index][e_tdTextdraw][2], -78.000000 + pos_x, pos_y + 1.0);
    
    SendClientMessage(playerid, -1, "Debug 4");
    
    NotificationShowAll(playerid, index);
    
    SendClientMessage(playerid, -1, "Debug 5");
    
	if (pct >= 1.0)
	{
		g_rgeNotificationData[playerid][index][e_iFrameCount] = 0;
		KillTimer(g_rgeNotificationData[playerid][index][e_iFrameTimer]);
        g_rgeNotificationData[playerid][index][e_iFrameTimer] = SetTimerEx("NotificationWaitToLeft", time, false, "ddffd", playerid, index, pos_y, 300.0, count);
        SendClientMessage(playerid, -1, "Debug 7");
	}
    SendClientMessage(playerid, -1, "Debug 6");
	return 1;
}

public HideLoadScreen(playerid)
{
    TogglePlayerControllable(playerid, true);
    for(new i = 0; i < 4; i++) { PlayerTextDrawHide(playerid, p_tdLoad[playerid][i]); }
    RestorePlayerChat(playerid);
    DeletePVar(playerid, "LoadingObjects");
    return 1;
}