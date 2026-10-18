public OnDialogTDResponse(playerid, dialogid, response)
{
    if(dialogid == DIALOG_TEST)
    {
        if(response == 1)
        {
            SendClientMessage(playerid, -1, "{ffffff}Te follaste a {ff3277}VanNet {ffffff}por {ff3277}$200.");
            GivePlayerCash(playerid, -200, "Follar a vannet");
            return 1;
        }
        else
        {
            SendClientMessage(playerid, -1, "{ffffff}No te follaste a {ff3277}VanNet {ffffff}por {ff3277}$200.");
            return 1;
        }
    }
    return 0;
}