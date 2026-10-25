#include <colandreas>

static Fisherman_KeyGameCallback(playerid, bool:success)
{
    TogglePlayerControllable(playerid, true);

    if (success)
    {
        //Player_AddXP(playerid, 10);
        //Inventory_AddFixedItem(playerid, ITEM_FISH, 1, 0);

        new randomFish = random(sizeof(FishItems));
        new fishId = FishItems[randomFish];

        DarObjeto(playerid, fishId, 1);

        IsPlayerFishing[playerid] = false;
                
        ShowNotification(playerid, "Pesca", "¡Bien ahí! Conseguiste un pescado.", "success", 3000);
        ApplyAnimation(playerid, "OTB", "WTCHRACE_WIN", 4.1, false, false, false, false, 0, true);
    }
    else
    {
        ApplyAnimation(playerid, "OTB", "WTCHRACE_LOSE", 4.1, false, false, false, false, 0, true);
        ShowNotification(playerid, "Pesca", "¡Fallaste! el pez se te escapó...", "error", 3000);
    }

    RemovePlayerAttachedObject(playerid, 9);
    return 1;
}

FishingRod_OnUse(playerid, slot)
{
    #pragma unused slot

    if (CA_IsPlayerFacingWater(playerid) )
    {
        TogglePlayerControllable(playerid, false);
        SetPlayerAttachedObject(playerid, 9, 18632, 6, 0.0620, 0.0199, 0.0149, 9.1999, 171.9999, 103.0999, 0.8920, 0.9029, 1.0589, 0xFFFFFFFF, 0xFFFFFFFF);

        Player_StartKeyGame(playerid, __addressof(Fisherman_KeyGameCallback), 9.9, 2.5);
        IsPlayerFishing[playerid] = true;
        ApplyAnimation(playerid, "SWORD", "SWORD_IDLE", 4.1, true, false, false, false, 0, true);
    }
    else
    {
        ShowNotification(playerid, "Pesca", "Tienes que estar frente al agua para poder pescar.", "error", 3000);
    }
    return 1;
}

CMD:pescar(playerid)
{
    FishingRod_OnUse(playerid, 1);
    return 1;
}

stock bool:EsPescado(itemid)
{
    for(new i = 0; i < sizeof(FishItems); i++)
    {
        if(FishItems[i] == itemid)
            return true;
    }
    return false;
}