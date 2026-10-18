#if defined _GoodNote_included
#endinput
#endif

#define _GoodNote_included

#if !defined MAX_GOOD_NOTES
#define MAX_GOOD_NOTES 5
#endif

#if !defined MAX_GOOD_TEXT_LENGTH
#define MAX_GOOD_TEXT_LENGTH 400
#endif

#define GN_DIRECTION_UP 2		/* /\ */
#define GN_DIRECTION_DOWN 1		/* \/ */


enum GOOD_NOTE_INFO
{
	GOOD_NOTE_ID,
	PlayerText:GOOD_NOTE_TD_TEXT,
	PlayerText:GOOD_NOTE_ICO,
	GOOD_NOTE_TEXT[MAX_GOOD_TEXT_LENGTH],
	GOOD_NOTE_TEXT_I[MAX_GOOD_TEXT_LENGTH],
	GOOD_NOTE_TIME_OUT,
	GOOD_NOTE_TIMER,
	GOOD_NOTE_NOTI,
	GOOD_NOTE_LINES,
	GOOD_NOTE_COL_BG,
	GOOD_NOTE_COL_TEXT,
	GOOD_NOTE_TYPE,
    //-- Dinamics
	PlayerText:GENERAL_TD[4],
    PlayerText:GENERAL_TD_TEXT[MAX_PLAYERS],
	//-- Informes
	PlayerText:Informe1,
	PlayerText:Informe2,
	//-- Informes
	PlayerText: Crimenes1,
	PlayerText: Crimenes2, 
	PlayerText: Crimenes3,
	PlayerText: Crimenes4,
	PlayerText: Crimenes5,
	PlayerText: Crimenes6
}

#define EPOCH_YEAR 1970

new
	GoodNoteData[MAX_PLAYERS][MAX_GOOD_NOTES][GOOD_NOTE_INFO],
	GoodNoteLastId = 0,
	Float:GoodNotePosX = 497.0,
	Float:GoodNotePosY = 111.0,
	GoodNoteDirection = GN_DIRECTION_DOWN,
	GoodNoteSound = 1149,
	Noti_Basurero[MAX_PLAYERS],
    TiempoNotificaciones[MAX_PLAYERS][1],

	//-- Informes
	InformePolicia1[MAX_PLAYERS][60], 
	InformePolicia2[MAX_PLAYERS][150],
	Noti_Informe[MAX_PLAYERS],
	SaltosInforme[MAX_PLAYERS],

	//-- Crimenes
	InformeCrimen1[MAX_PLAYERS][60],
	InformeCrimen2[MAX_PLAYERS][60],
	InformeCrimen3[MAX_PLAYERS][60],
	InformeCrimen4[MAX_PLAYERS][60],
	InformeCrimen5[MAX_PLAYERS][60],
	InformeCrimen6[MAX_PLAYERS][60],
	Noti_Crimen[MAX_PLAYERS]
;