#if defined _NOTIFICATION_HEADER_
    #endinput
#endif
#define _NOTIFICATION_HEADER_

const MAX_NOTIFICATIONS = 16;
const NOTIFICATION_TEXT_BEAT_DIFF = 4;

enum eNotificationData 
{
    bool:e_bActive,
    e_iFrameCount,
    e_iFrameTimer,
    PlayerText:e_tdTextdraw[3],
    Float:e_fHeight
};
new g_rgeNotificationData[MAX_PLAYERS][MAX_NOTIFICATIONS][eNotificationData];

new r_rgiLoadTimer[MAX_PLAYERS];

forward Notification_Show(playerid, const text[], time, color = 0xFCCF3AFF);
forward HideLoadScreen(playerid);

