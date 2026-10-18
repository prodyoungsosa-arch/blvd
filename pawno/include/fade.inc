#if defined _SCF_included
    #endinput
#endif
#define _SCF_included


#include <a_samp>
#include <colour-manipulation>
//#include <YSI\y_hooks>

#define SetPlayerScreenColor SetPlayerScreenColour
#define GetPlayerScreenColor GetPlayerScreenColour
#define FadePlayerScreenColor FadePlayerScreenColour
#define StopPlayerScreenColorFade StopPlayerScreenColourFade
#define OnScreenColorFadeComplete OnScreenColourFadeComplete


enum screenColourFadeData {
    sSteps,
    sCurrentStep,

    sOriginalColour,
    sFinalColour,

    sTimer
}


static
    ScreenColour[MAX_PLAYERS],
    Text:ScreenColourTD,
    ScreenColourFadeData[MAX_PLAYERS][screenColourFadeData]
;


forward public OnScreenColourFadeComplete(playerid);


static stock _SetPlayerScreenColour(playerid, colour) {
    ScreenColour[playerid] = colour;

    TextDrawBoxColor(ScreenColourTD, ScreenColour[playerid]);
    TextDrawShowForPlayer(playerid, ScreenColourTD);
}


stock SetPlayerScreenColour(playerid, colour) {
    if (!IsPlayerConnected(playerid)) {
        return 0;
    }

    _SetPlayerScreenColour(playerid, colour);
    return 1;
}


stock GetPlayerScreenColour(playerid) {
    if (!IsPlayerConnected(playerid)) {
        return 0x00000000;
    }

    return ScreenColour[playerid];
}


static stock _KillScreenColourFadeTimer(playerid) {
    KillTimer(ScreenColourFadeData[playerid][sTimer]);

    ScreenColourFadeData[playerid][sTimer] = -1;
}


stock FadePlayerScreenColour(playerid, colour, time, steps) {
    if (!IsPlayerConnected(playerid) || steps < 1 || time < 0) {
        return 0;
    }

    if (ScreenColourFadeData[playerid][sTimer] != -1) {
        KillTimer(ScreenColourFadeData[playerid][sTimer]);
    }

    ScreenColourFadeData[playerid][sOriginalColour] = ScreenColour[playerid];
    ScreenColourFadeData[playerid][sFinalColour] = colour;

    ScreenColourFadeData[playerid][sSteps] = steps;
    ScreenColourFadeData[playerid][sCurrentStep] = 0;

    ScreenColourFadeData[playerid][sTimer] = SetTimerEx("ScreenColourFadeTimer", time / steps, true, "i", playerid);

    return 1;
}


stock StopPlayerScreenColourFade(playerid) {
    if (!IsPlayerConnected(playerid) || ScreenColourFadeData[playerid][sTimer] == -1) {
        return 0;
    }

    _KillScreenColourFadeTimer(playerid);
    return 1;
}


forward public ScreenColourFadeTimer(playerid);
public ScreenColourFadeTimer(playerid) {
    if (ScreenColourFadeData[playerid][sCurrentStep] == ScreenColourFadeData[playerid][sSteps]) {
        _KillScreenColourFadeTimer(playerid);

        CallLocalFunction("OnScreenColourFadeComplete", "i", playerid);
        return 1;
    }

    _SetPlayerScreenColour(playerid, InterpolateColours(ScreenColourFadeData[playerid][sOriginalColour], ScreenColourFadeData[playerid][sFinalColour], float(ScreenColourFadeData[playerid][sCurrentStep] + 1) / float(ScreenColourFadeData[playerid][sSteps])));

    ScreenColourFadeData[playerid][sCurrentStep]++;
    return 1;
}

stock Fade_OnGameModeInit() {
    ScreenColourTD = TextDrawCreate(0.0, 0.0, "_");
    TextDrawTextSize(ScreenColourTD, 640.0, 480.0);
    TextDrawLetterSize(ScreenColourTD, 0.0, 50.0);
    TextDrawUseBox(ScreenColourTD, true);

}

stock Fade_OnPlayerConnect(playerid) {
    ScreenColourFadeData[playerid][sTimer] = -1;

    _SetPlayerScreenColour(playerid, 0x00000000);

    return 1;
}




stock Fade_OnPlayerDisconnect(playerid) {
    if (ScreenColourFadeData[playerid][sTimer] != -1) {
        _KillScreenColourFadeTimer(playerid);
    }
}