// keys.inc - Client key bindings for SA-MP (keybinds.asi)
// Include AFTER <Pawn.RakNet>.

#if defined _keys_included
	#endinput
#endif
#define _keys_included

#if !defined RPC_ServerCommand
	#define RPC_ServerCommand	(50)
#endif

#if !defined VK_1
	#define VK_0 (0x30)
	#define VK_1 (0x31)
	#define VK_2 (0x32)
	#define VK_3 (0x33)
	#define VK_4 (0x34)
	#define VK_5 (0x35)
	#define VK_6 (0x36)
	#define VK_7 (0x37)
	#define VK_8 (0x38)
	#define VK_9 (0x39)
	#define VK_A (0x41)
	#define VK_B (0x42)
	#define VK_C (0x43)
	#define VK_D (0x44)
	#define VK_E (0x45)
	#define VK_F (0x46)
	#define VK_G (0x47)
	#define VK_H (0x48)
	#define VK_I (0x49)
	#define VK_J (0x4A)
	#define VK_K (0x4B)
	#define VK_L (0x4C)
	#define VK_M (0x4D)
	#define VK_N (0x4E)
	#define VK_O (0x4F)
	#define VK_P (0x50)
	#define VK_Q (0x51)
	#define VK_R (0x52)
	#define VK_S (0x53)
	#define VK_T (0x54)
	#define VK_U (0x55)
	#define VK_V (0x56)
	#define VK_W (0x57)
	#define VK_X (0x58)
	#define VK_Y (0x59)
	#define VK_Z (0x5A)
	#define VK_SPACE   (0x20)
	#define VK_LEFT    (0x25)
	#define VK_UP      (0x26)
	#define VK_RIGHT   (0x27)
	#define VK_DOWN    (0x28)
	#define VK_NUMPAD0 (0x60)
	#define VK_NUMPAD1 (0x61)
	#define VK_NUMPAD2 (0x62)
	#define VK_NUMPAD3 (0x63)
	#define VK_NUMPAD4 (0x64)
	#define VK_NUMPAD5 (0x65)
	#define VK_NUMPAD6 (0x66)
	#define VK_NUMPAD7 (0x67)
	#define VK_NUMPAD8 (0x68)
	#define VK_NUMPAD9 (0x69)
	#define VK_F1  (0x70)
	#define VK_F2  (0x71)
	#define VK_F3  (0x72)
	#define VK_F4  (0x73)
	#define VK_F5  (0x74)
	#define VK_F9  (0x78)
	#define VK_F10 (0x79)
	#define VK_F11 (0x7A)
	#define VK_F12 (0x7B)
#endif

new bool:gKeysReady[MAX_PLAYERS];

stock Keys_Enable(playerid, const keys[] = "", bool:release = true)
{
	if (!IsPlayerConnected(playerid)) return 0;
	new s[144];
	gKeysReady[playerid] = false;
	format(s, sizeof s, "#KEY|on|%s|%d", keys, release ? 1 : 0);
	return SendClientMessage(playerid, 0x00000000, s);
}

stock Keys_Disable(playerid)
{
	gKeysReady[playerid] = false;
	if (!IsPlayerConnected(playerid)) return 0;
	return SendClientMessage(playerid, 0x00000000, "#KEY|off");
}

stock Keys_IsReady(playerid)
{
	return _:gKeysReady[playerid];
}

stock Keys_Handle(playerid, const args[])
{
	new vk = strval(args);
	new key_state = 1;
	new sp = strfind(args, " ");
	
	if (sp != -1) key_state = strval(args[sp + 1]);
	if (vk < 0 || vk > 255) return 1;

	if (vk == 0)
	{
		if (!gKeysReady[playerid])
		{
			gKeysReady[playerid] = true;
			if (funcidx("OnPlayerKeysReady") != -1) CallLocalFunction("OnPlayerKeysReady", "i", playerid);
		}
		return 1;
	}
	if (!gKeysReady[playerid]) return 1;

	if (key_state) { if (funcidx("OnPlayerPressKey") != -1)   CallLocalFunction("OnPlayerPressKey",   "ii", playerid, vk); }
	else           { if (funcidx("OnPlayerReleaseKey") != -1) CallLocalFunction("OnPlayerReleaseKey", "ii", playerid, vk); }
	return 1;
}

public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
    if (rpcid == RPC_ServerCommand)
    {
        new len;
        BS_ReadValue(bs, PR_UINT32, len);
        if (len > 3 && len < 24)
        {
            new cmd[24];
            BS_ReadValue(bs, PR_STRING, cmd, len);
            cmd[len] = 0;
            if (!strcmp(cmd, "/_k ", false, 4))
            {
                Keys_Handle(playerid, cmd[4]);
                return 0;
            }
        }
        BS_ResetReadPointer(bs);
    }
    #if defined KEYS_OnIncomingRPC
        return KEYS_OnIncomingRPC(playerid, rpcid, bs);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnIncomingRPC
	#undef OnIncomingRPC
#else
	#define _ALS_OnIncomingRPC
#endif
#define OnIncomingRPC KEYS_OnIncomingRPC
#if defined KEYS_OnIncomingRPC
	forward KEYS_OnIncomingRPC(playerid, rpcid, BitStream:bs);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	gKeysReady[playerid] = false;
	#if defined KEYS_OnPlayerDisconnect
		return KEYS_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect KEYS_OnPlayerDisconnect
#if defined KEYS_OnPlayerDisconnect
	forward KEYS_OnPlayerDisconnect(playerid, reason);
#endif