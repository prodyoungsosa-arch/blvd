/* 	Gamemode Boulevard, desarrollada en sus inicios por VanNet y Saiint.
	Ahora utilizada en el servidor Boulevard y siendo desarrollada por Saiint.

	LISTA DE TAREAS:
	- Sistema realista de enfermedades
	- Centrificar los sistemas basicos en fortcarson
	- Robo de autos
	- Sistema de heridas
	- Mapeos
	- Limitar los vehiculos deportivos
*/


// Compilación
#pragma warning disable 239, 204, 203
#pragma dynamic 100000


// Librerías
#include <a_samp>
#include <foreach>
#include <sscanf2>
#include <Pawn.RakNet>
#include <Pawn.CMD>
#include <Pawn.Regex>
#include <strlib>
#include <a_mysql>
#include <streamer>
#include <fade>
#include <pawn-easing-functions>
#include <easyDialog>
#include <yom_buttons>
#include <td-notification>
#include <mSelection2>
#include <menuv>
#include <playerprogress>
#include <colandreas>
#include <cef>


#define NDEBUG 1
#if NDEBUG == 0
	#pragma option -d0
	#pragma option -O0
#else
	#pragma option -d3
	#include <crashdetect>
#endif

new bool:gCefReady[MAX_PLAYERS];
new gCefInvEstado[MAX_PLAYERS];

__beware__thieves__();
__beware__thieves__()
{
	#emit    stack    0x7FFFFFFF
	#emit    inc.s    cellmax

	static const ___[][] = { "hi", "i hate netanyahu" };

	#emit    retn
	#emit    load.s.pri    ___
	#emit    proc
	#emit    proc
	#emit    fill    cellmax
	#emit    proc
	#emit    stack    1
	#emit    stor.alt    ___
	#emit    strb.i    2
	#emit    switch    0
	#emit    retn
L1:
	#emit    jump    L1
	#emit    zero    cellmin
}

const __dada = __addressof(__beware__thieves__);
#pragma unused __dada

// Server information
#define SERVER_HOSTNAME "Boulevard Juego de rol | ES | dsc.gg/boulevard-rp"
#define SERVER_VERSION  "Alpha I"
#define SERVER_MODE 	"Roleplay en español"
#define SERVER_NAME     "Boulevard"
#define SERVER_WEBSITE 	"sa-mp.net"

// Misc
#include "server/misc/utils.inc"
#include "server/misc/constants.inc"
#include "server/misc/zones.inc"
#include "server/misc/macros.inc"
#include "server/misc/weather.inc"

// Android
#define IsPlayerAndroid(%0) GetPVarInt(%0, "NotAndroid") == 0

// Database
#define Conexion_MySQL 1 // ( 1 | Localhost) __ ( 2 | Server hosting )
#include "server/database/db.inc"

// Colors
#include "server/colors/pallete.inc"

// Textdraws
#include "server/textdraws/header.inc"
#include "server/textdraws/utils.inc"
#include "server/textdraws/global.inc"
#include "server/textdraws/player.inc"

new player_asesino[MAX_PLAYERS];
new player_weapon[MAX_PLAYERS];
new Vehicle_Color[MAX_PLAYERS];

// Droga sistema by Vestige
#define MAX_PLANTAS 120

new Float:lastcall911[3];

enum PlantaInfo
{
	sID,
	Tipo,
	Float:Posicion[3],
	IntP,
	VWP,
	Plantador,
	Cosechas,
	Text3D:Draw,
	Objeto,
	TiempoRestante
}
new Planta[MAX_PLANTAS][PlantaInfo];

enum pDrugInfo
{
	NivelSobredosis,
	AdiccionAnfetamina,
	AdiccionCocaina,
	AdiccionOpioides,

	EfectoMetanfetamina,
	EfectoCocaina,
	EfectoMarihuana,
	EfectoLSD,
	EfectoMDMA,
	EfectoHongo,
	EfectoEspecialUWU,

	TiempoMetanfetamina,
	TiempoCocaina,
	TiempoMarihuana,
	TiempoHeroina,
	TiempoKetamina,

	EnMenuLab,
	SelEntrega,

	Sobredosis,
	AdicCoca,
	AdicOpio,
	AdicMeta,
	ChalecoDroga,

	Float:OldUWU[3]
};
new pDroga[MAX_PLAYERS][pDrugInfo];

//variables
new InfoTimer[MAX_PLAYERS],
	InfoTextShowing[MAX_PLAYERS];

new xHora = 19, xMinuto = 30, xSegundo = 30;

new CountMinute = 0;
new TipoAudio[MAX_PLAYERS];
new veh_music[MAX_VEHICLES][256];

const
	m_cambiodenumero = 2,
	m_slotpersonaje = 3,
	m_vip_esmeralda = 6,
	m_vip_diamante = 10,
	m_mueblesextras = 2,
	m_dinero10k = 1
;

new wsp_u[MAX_PLAYERS];
new wsp_time[MAX_PLAYERS];

new TiempoTecla[MAX_PLAYERS];

new Text3D:ConceLabel[MAX_PLAYERS];

new fRespawnTiempo[MAX_PLAYERS];

new check_motor[MAX_PLAYERS];
new veh_asiento[MAX_PLAYERS];

new Active_Registro = 1;
new Active_Rol = 0;
new YaAviso[MAX_PLAYERS];

new pDrunkLevelLast[MAX_PLAYERS];
new pFPS[MAX_PLAYERS];

new RecargarTiempo[MAX_PLAYERS];

new es_hablando[MAX_PLAYERS];
new NPCrepara[MAX_PLAYERS];
new VehiculoGasolina[MAX_PLAYERS];

new SirenObject[MAX_VEHICLES][7]; //objeto
new bool:SirenOn[MAX_VEHICLES]; //bool sirena

//anticheat (16/02/2020) - 1: activado - 0: desactivado
new
	cheat_VehicleSpawning = 1,
	cheat_Vehicle1teleport = 1,
	cheat_Vehicle2teleport = 1,
	cheat_weapons = 1,
	cheat_balas = 1,
	cheat_PlayerTeleport = 1,
	cheat_TPgranjero = 1,
	cheat_IPS = 1
;

//cheat teleport 03/03/2020
new Float: CurrentPos[MAX_PLAYERS][3];
new Float: pSetPos[MAX_PLAYERS][3];
new WarningTPlayer[MAX_PLAYERS];

static const Float: CheatPositions [][3] =
{
	{-1935.77, 228.79, 34.16}, //Transfender near Wang Cars in Doherty
	{-2707.48, 218.65, 4.93}, //Wheel Archangels in Ocean Flats
	{2645.61, -2029.15, 14.28}, //LowRider Tuning Garage in Willowfield
	{1041.26, -1036.77, 32.48}, //Transfender in Temple
	{2387.55, 1035.70, 11.56}, //Transfender in come-a-lot
	{1836.93, -1856.28, 14.13}, //Eight Ball Autos near El Corona
	{2006.11, 2292.87, 11.57}, //Welding Wedding Bomb-workshop in Emerald Isle
	{-1787.25, 1202.00, 25.84}, //Michelles Pay 'n' Spray in Downtown
	{720.10, -470.93, 17.07}, //Pay 'n' Spray in Dillimore
	{-1420.21, 2599.45, 56.43}, //Pay 'n' Spray in El Quebrados
	{-100.16, 1100.79, 20.34}, //Pay 'n' Spray in Fort Carson
	{2078.44, -1831.44, 14.13}, //Pay 'n' Spray in Idlewood
	{-2426.89, 1036.61, 51.14}, //Pay 'n' Spray in Juniper Hollow
	{1957.96, 2161.96, 11.56}, //Pay 'n' Spray in Redsands East
	{488.29, -1724.85, 12.01}, //Pay 'n' Spray in Santa Maria Beach
	{1025.08, -1037.28, 32.28}, //Pay 'n' Spray in Temple
	{2393.70, 1472.80, 11.42}, //Pay 'n' Spray near Royal Casino
	{-1904.97, 268.51, 41.04}, //Pay 'n' Spray near Wang Cars in Doherty
	{403.58, 2486.33, 17.23}, //Player Garage: Verdant Meadows
	{1578.24, 1245.20, 11.57}, //Player Garage: Las Venturas Airport
	{-2105.79, 905.11, 77.07}, //Player Garage: Calton Heights
	{423.69, 2545.99, 17.07}, //Player Garage: Derdant Meadows
	{785.79, -513.12, 17.44}, //Player Garage: Dillimore
	{-2027.34, 141.02, 29.57}, //Player Garage: Doherty
	{1698.10, -2095.88, 14.29}, //Player Garage: El Corona
	{-361.10, 1185.23, 20.49}, //Player Garage: Fort Carson
	{-2463.27, -124.86, 26.41}, //Player Garage: Hashbury
	{2505.64, -1683.72, 14.25}, //Player Garage: Johnson House
	{1350.76, -615.56, 109.88}, //Player Garage: Mulholland
	{2231.64, 156.93, 27.63}, //Player Garage: Palomino Creek
	{-2695.51, 810.70, 50.57}, //Player Garage: Paradiso
	{1293.61, 2529.54, 11.42}, //Player Garage: Prickle Pine
	{1401.34, 1903.08, 11.99}, //Player Garage: Redland West
	{2436.50, 698.43, 11.60}, //Player Garage: Rockshore West
	{322.65, -1780.30, 5.55}, //Player Garage: Santa Maria Beach
	{917.46, 2012.14, 11.65}, //Player Garage: Whitewood Estates
	{1641.14, -1526.87, 14.30}, //Commerce Region Loading Bay
	{-1617.58, 688.69, -4.50}, //San Fierro Police Garage
	{837.05, -1101.93, 23.98}, //Los Santos Cemetery
	{2338.32, -1180.61, 1027.98}, //Interior: Burning Desire House
	{-975.5766, 1061.1312, 1345.6719}, //Interior: RC Zero's Battlefield
	{-750.80, 491.00, 1371.70}, //Interior: Liberty City
	{-1400.2138, 106.8926, 1032.2779}, //Interior: Unknown Stadium
	{-2015.6638, 147.2069, 29.3127}, //Interior: Secret San Fierro Chunk
	{2220.26, -1148.01, 1025.80}, //Interior: Jefferson Motel
	{-2660.6185, 1426.8320, 907.3626}, //Interior: Jizzy's Pleasure Dome
	{-1394.20, 987.62, 1023.96}, //Stadium: Bloodbowl
	{-1410.72, 1591.16, 1052.53}, //Stadium: Kickstart
	{-1417.8720, -276.4260, 1051.1910}, //Stadium: 8-Track Stadium
	{-25.8844, -185.8689, 1003.5499}, //24/7 Store: Big-L-Shaped
	{6.0911, -29.2718, 1003.5499}, //24/7 Store: Big-Oblong
	{-30.9469, -89.6095, 1003.5499}, //24/7 Store: Med-Square
	{-25.1329, -139.0669, 1003.5499}, //24/7 Store: Med-Square
	{-27.3123, -29.2775, 1003.5499}, //24/7 Store: Sml-Long
	{-26.6915, -55.7148, 1003.5499}, //24/7 Store: Sml-Square
	{-1827.1473, 7.2074, 1061.1435}, //Airport: Ticket Sales
	{-1855.5687, 41.2631, 1061.1435}, //Airport: Baggage Claim
	{2.3848, 33.1033, 1199.8499}, //Airplane: Shamal Cabin
	{315.8561, 1024.4964, 1949.7973}, //Airplane: Andromada Cargo hold
	{2536.08, -1632.98, 13.79}, // Grove Street
	{1992.93, 1047.31, 10.82}, //Four Dragons Casino
	{2033.00, -1416.02, 16.99}, // LS Hospital
	{-2653.11, 634.78, 14.45}, // SF Hospital
	{1580.22, 1768.93, 10.82}, //LV Hospital
	{-1550.73, 99.29, 17.33}, //SF Export
	//Positions given to me by SureShot :O
 	{-2057.8000, 229.9000, 35.6204}, // San Fierro
 	{-2366.0000, -1667.4000, 484.1011}, // Mount Chiliad
 	{2503.7000, -1705.8000, 13.5480}, // Grove Street
 	{1997.9000, 1056.3000, 10.8203}, // Las Venturas
 	{-2872.7000, 2712.6001, 275.2690}, // BaySide
 	{904.1000, 608.0000, -32.3281}, // Unterwasser
 	{-236.9000, 2663.8000, 73.6513} // The big Cock
};

forward IsCheatPosition (playerid);
public IsCheatPosition (playerid)//Teleporting to these locations is always cheating!
{
	for (new i = 0; i < sizeof (CheatPositions); ++i)
		if (IsPlayerInRangeOfPoint (playerid, 5.0, CheatPositions [i][0], CheatPositions [i][1], CheatPositions [i][2]))
			return true;
	return false;
}

//cheat weapons
new advWeapons[MAX_PLAYERS];

new autodemierda[MAX_PLAYERS];

new LastUpdate[MAX_PLAYERS];

#define MAX_SYNC_TYPES          (5)

#define SYNC_TYPE_POS           (0)
#define SYNC_TYPE_HEALTH        (1)
#define SYNC_TYPE_ARMOUR        (2)
#define SYNC_TYPE_WEAPONS       (3)
#define SYNC_TYPE_VEHICLE       (4)


#define CONCE_CAM_DIST          7.5
#define CONCE_CAM_HEIGHT        2.4
#define CONCE_CAM_ANGLE_OFFSET  40.0
#define CONCE_SWEEP_EXTRA       35.0
#define CONCE_SWEEP_MS          1500
#define CONCE_SWEEP_Z_EXTRA     1.8
#define CONCE_SWEEP_DIST_EXTRA  4.0
#define CONCE_LOOK_Z_OFFSET     0.85
#define CONCE_TIMER_MS          800

enum sxdInfo
{
	sTimeSync,
	sLastSyncUpdate,
};
new InfoSync[MAX_PLAYERS][MAX_SYNC_TYPES][sxdInfo];

stock SetSyncTime(playerid, synctype, base = 3)
{
	if (!IsPlayerConnectedEx(playerid) || synctype < 0 || synctype >= MAX_SYNC_TYPES)
	    return 0;

    InfoSync[playerid][synctype][sTimeSync] = base;
	InfoSync[playerid][synctype][sLastSyncUpdate] = GetTickCount ();
	return 1;
}

//vehicle teleport type 1
new CarTick[MAX_PLAYERS];

//vehicle teleport type 2
new LastVehicle[MAX_PLAYERS];
new Adv2Vehs[MAX_PLAYERS];


new InconTimer[MAX_PLAYERS];

SetPlayerPosEx(playerid, Float: x, Float: y, Float: z)
{
	if (IsPlayerConnectedEx(playerid))
	{
		if (SetPlayerPos(playerid, x, y, z))
		{
			CurrentPos[playerid][0] = x;
			CurrentPos[playerid][1] = y;
			CurrentPos[playerid][2] = z;
			pSetPos[playerid][0] = x;
			pSetPos[playerid][1] = y;
			pSetPos[playerid][2] = z;
   			SetSyncTime(playerid, SYNC_TYPE_POS);
   			WarningTPlayer[playerid] = 0;
			return 1;
		}
	}
	return 0;
}

/*
SetPlayerRaceCheckpointEx(playerid, type, Float: x, Float: y, Float: z, Float: nextx, Float: nexty, Float: nextz, Float: size)
{
	if (IsPlayerInRangeOfPoint (playerid, (size + 5.0), x, y, z))//Prevent that spawning a checkpoint near a player counts as checkpoint teleport.
		SetSyncTime (playerid, SYNC_TYPE_POS);
	return SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
}
*/

PutPlayerInVehicleEx(playerid, vehicleid, seatid)
{
	if (IsPlayerConnectedEx(playerid) && vehicleid != INVALID_VEHICLE_ID)
	{
		if (PutPlayerInVehicle(playerid, vehicleid, seatid))
		{
		    SetSyncTime(playerid, SYNC_TYPE_POS);
			LastVehicle[playerid] = vehicleid;
 			return 1;
		}
	}
	return 0;
}

//vehicle spawning
new AdvVehs[MAX_PLAYERS];

enum e_VEH_POS
{
	Float: vp_x,
	Float: vp_y,
	Float: vp_z,
	Float: vp_z_angle,
	Float: vp_distance,
}
new uwuVehPos[MAX_VEHICLES][e_VEH_POS];

stock MoverVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	if (SetVehiclePos(vehicleid, x, y, z))
	{
		uwuVehPos[vehicleid][vp_x] = x;
		uwuVehPos[vehicleid][vp_y] = y;
		uwuVehPos[vehicleid][vp_z] = z;
		foreach(Player, i) if (GetPlayerVehicleID(i) == vehicleid)
		{
			CurrentPos[i][0] = x;
			CurrentPos[i][1] = y;
			CurrentPos[i][2] = z;
			pSetPos[i][0] = x;
			pSetPos[i][1] = y;
			pSetPos[i][2] = z;
			SetSyncTime(i, SYNC_TYPE_POS);
   			WarningTPlayer[i] = 0;
		}
		return 1;
	}
	return 0;
}

new depositoembargo, open_embargo = 0;
new porton_usmc;
new puerta_sadoc[3];
new celda_sd, celda_open_sd, celda_pf[18], celda_open_pf[18];
new lspdPuerta, lspdBoton, celda_pd[3], celda_open_pd[3];
new SDobj1, SDobj2;
new SDboton1, SDboton2;

new FakePayday[MAX_PLAYERS];
new PortonTaller[5];
new VehicleWindows[MAX_VEHICLES];

new name_password[MAX_PLAYERS][128];
new Act_Inventario[MAX_PLAYERS];

new CulandoPrecio[MAX_PLAYERS];
new CulandoCliente[MAX_PLAYERS];
new CulandoNegocio[MAX_PLAYERS];

new ConTransferir[MAX_PLAYERS];
new NumeroMensaje[MAX_PLAYERS];
new playerGraffitiTimer[MAX_PLAYERS];

//animaciones
static const g_aPreloadLibs[][] =
{
	"AIRPORT",      "ATTRACTORS",   "BAR",          "BASEBALL",     "BD_FIRE",
	"BEACH",        "BENCHPRESS",   "BF_INJECTION", "BIKE_DBZ",     "BIKED",
	"BIKEH",        "BIKELEAP",     "BIKES",        "BIKEV",        "BLOWJOBZ",
	"BMX",          "BOMBER",       "BOX",          "BSKTBALL",     "BUDDY",
	"BUS",          "CAMERA",       "CAR",          "CAR_CHAT",     "CARRY",
	"CASINO",       "CHAINSAW",     "CHOPPA",       "CLOTHES",      "COACH",
	"COLT45",       "COP_AMBIENT",  "COP_DVBYZ",    "CRACK",        "CRIB",
	"DAM_JUMP",     "DANCING",      "DEALER",       "DILDO",        "DODGE",
	"DOZER",        "DRIVEBYS",     "FAT",          "FIGHT_B",      "FIGHT_C",
	"FIGHT_D",      "FIGHT_E",      "FINALE",       "FINALE2",      "FLAME",
	"FLOWERS",      "FOOD",         "FREEWEIGHTS",  "GANGS",        "GFUNK",
	"GHANDS",       "GHETTO_DB",    "GOGGLES",      "GRAFFITI",     "GRAVEYARD",
	"GRENADE",      "GYMNASIUM",    "HAIRCUTS",     "HEIST9",       "INT_HOUSE",
	"INT_OFFICE",   "INT_SHOP",     "JST_BUISNESS", "KART",         "KISSING",
	"KNIFE",        "LAPDAN1",      "LAPDAN2",      "LAPDAN3",      "LOWRIDER",
	"MD_CHASE",     "MD_END",       "MEDIC",        "MISC",         "MTB",
	"MUSCULAR",     "NEVADA",       "ON_LOOKERS",   "OTB",          "PARACHUTE",
	"PARK",         "PAULNMAC",     "PED",          "PLAYER_DVBYS", "PLAYIDLES",
	"POLICE",       "POOL",         "POOR",         "PYTHON",       "QUAD",
	"QUAD_DBZ",     "RAPPING",      "RIFLE",        "RIOT",         "ROB_BANK",
	"ROCKET",       "RUNNINGMAN",   "RUSTLER",      "RYDER",        "SCRATCHING",
	"SEX",          "SHAMAL",       "SHOP",         "SHOTGUN",      "SILENCED",
	"SKATE",        "SMOKING",      "SNIPER",       "SNM",          "SPRAYCAN",
	"STRIP",        "SUNBATHE",     "SWAT",         "SWEET",        "SWIM",
	"SWORD",        "TANK",         "TATTOOS",      "TEC",          "TRAIN",
	"TRUCK",        "UZI",          "VAN",          "VENDING",      "VORTEX",
	"WAYFARER",     "WEAPONS",      "WOP",          "WUZI"
};

new TimerWeaponCreate[MAX_PLAYERS];
new MensajeMuelto[MAX_PLAYERS];

new GetTextDraw[MAX_PLAYERS];

//puntos de embargos
new Float: point_embargo[][] =
{
	{1605.6499, -1838.4331, 13.4624, -90.1200},
	{1605.6586, -1831.6129, 13.4624, -90.1200},
	{1605.6606, -1826.2428, 13.4624, -90.1200},
	{1605.4218, -1820.1104, 13.4624, -90.1200},
	{1600.9728, -1814.9929, 13.4624, -90.1200},
	{1600.4681, -1809.2795, 13.4624, -90.1200},
	{1610.5453, -1801.6992, 13.4624, -153.1800},
	{1649.7317, -1807.5803, 13.4624, -175.8000},
	{1655.2010, -1807.9847, 13.4624, -175.8000},
	{1655.7618, -1817.2306, 13.4624, -260.5800},
	{1656.4235, -1822.8483, 13.4624, -260.5800},
	{1655.6775, -1828.7864, 13.4624, -269.3400},
	{1654.6257, -1834.6389, 13.4624, -269.3400},
	{1653.7234, -1839.9099, 13.4624, -272.1600},
	{1635.1046, -1844.4045, 13.4624, -370.5000},
	{1629.9003, -1844.0775, 13.4624, -356.7600}
};

new ConBalasGoma[MAX_PLAYERS];
new test_rol[MAX_PLAYERS];

new show_velocimetro[MAX_PLAYERS]; //velocimetro 26/05/2020


new tipo_anuncio[MAX_PLAYERS];
new DiferenciaAnuncio = -1;
new TimerReportarBug = -1;

new AnunceID = 0;
new AnunceString1[256];
new AnunceString2[256];
new AnunceString3[256];
new AnunceString4[256];
new PlayerViewAnunce[MAX_PLAYERS];

new ColorList[] = {
	    0x000000FF, 0xF5F5F5FF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF,
		0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF,
		0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF,
		0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF,
		0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF,
		0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF,
		0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF,
		0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF,
		0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF,
		0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF,
		0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF,
		0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF,
		0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF, 0x177517FF, 0x210606FF,
		0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF, 0xB7B7B7FF, 0x464C8DFF,
		0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF, 0x1E1D13FF, 0x1E1306FF,
		0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF, 0x992E1EFF, 0x2C1E08FF,
		0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF, 0x481A0EFF, 0x7A7399FF,
		0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF, 0x7B3E7EFF, 0x3C1737FF,
		0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF, 0x163012FF, 0x16301BFF,
		0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF, 0x2B3C99FF, 0x3A3A0BFF,
		0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF, 0x2C5089FF, 0x15426CFF,
		0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF, 0x995C52FF, 0x99581EFF,
		0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF, 0x96821DFF, 0x197F19FF,
		0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF, 0x8A653AFF, 0x732617FF,
		0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF, 0x561A28FF, 0x4E0E27FF,
		0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
	};

new Float: PosSpawnBug[MAX_PLAYERS][4], PosVwBug[MAX_PLAYERS], PosIntBug[MAX_PLAYERS];
new LockStatus[MAX_VEHICLES];

new EditandoObjetoJ[MAX_PLAYERS];

new Altavoz[MAX_PLAYERS];
new EnLlamada[MAX_PLAYERS];
new ToqueLlamada[MAX_PLAYERS];
new PersonaEnLlamada[MAX_PLAYERS];
new ToqueLlamadaTimer[MAX_PLAYERS];

//<=================================> nuevo centralita:
#define MAX_BUSCADOS		(50)
enum e_bus
{
	b_ID,
	b_string[256],
	b_creador[32],
	b_fecha[128]
};
new i_Buscados[MAX_BUSCADOS][e_bus];

enum r_info
{
	aID,
	aNombre[32],
	aTelefono,
	aHechos[256],
	aZona[128],
	aAtendido,
};
new
	info_c[50][r_info],
	r_id[MAX_PLAYERS],
	CentrTimer[50]
;

new bool:playerTextdraw[MAX_PLAYERS];

new edicion_sql_actual[MAX_PLAYERS];

new ContadorCuraciones[MAX_PLAYERS];

new Text3D:playerVehicleTextdraw[MAX_PLAYERS];

new IntentosRespuesta[MAX_PLAYERS];

new CountKick[MAX_PLAYERS];
new TimerCkick[MAX_PLAYERS];
new CountBan[MAX_PLAYERS];
new TimerCban[MAX_PLAYERS];
new CountWarn[MAX_PLAYERS];
new TimerCwarn[MAX_PLAYERS];

new PlayerDuda[MAX_PLAYERS];
new PlayerTextoDuda[MAX_PLAYERS][256];

new id_negocio[MAX_PLAYERS];
new slotselection[MAX_PLAYERS];

new GunVendedor[MAX_PLAYERS];
new GunCliente[MAX_PLAYERS];
new GunObjeto[MAX_PLAYERS];
new GunCantidad[MAX_PLAYERS];
new GunPrecio[MAX_PLAYERS];

new PayDaySecond = 120;

new Osql_vehicle[MAX_PLAYERS];
new Pla_vehicle[MAX_PLAYERS];
new Price_vehicle[MAX_PLAYERS];

new Taseado[MAX_PLAYERS]; //nuevo táser
new TaserRecarga[MAX_PLAYERS];
new CederTiempo[MAX_PLAYERS];
new	countGameTime[MAX_PLAYERS]; //variable update cada 5seg la posición del jugador

new timer_herido[MAX_PLAYERS];
new intentos_load[MAX_PLAYERS];
new gPlayerUsingLoopingAnim[MAX_PLAYERS];

new CommandSpamTimes[MAX_PLAYERS];
new CommandSpamUnmute[MAX_PLAYERS];

#define IDObj_Admin 505

//antichit
enum antichit
{
	bool:teleport,
	bool:Balas
}
new AntiG[antichit];

enum antichitplayers
{
	Float:vidac1,
	Float:vidac2,
	BalasW
}
new Anti[MAX_PLAYERS][antichitplayers];

//*******************************
new BigEar[MAX_PLAYERS];
//*******************Sistema de Reparacion de Auto con latas*******************
new autorepara[MAX_PLAYERS];

//variables del jugador en sql, hecho: 03/01/2020 by EdinsonWalker
new altavoz_phone[MAX_PLAYERS];
new tipo_refuerzos[MAX_PLAYERS];
new refuerzos_pd[MAX_PLAYERS];
new refuerzos_sd[MAX_PLAYERS];
new refuerzos_fbi[MAX_PLAYERS];
new nombre_contacto[MAX_PLAYERS][20][MAX_PLAYER_NAME];
new Tax = 0;

new See_FRC[MAX_PLAYERS];
new TicketOffer[MAX_PLAYERS];
new TicketMoney[MAX_PLAYERS];
new PrecioLicencia[MAX_PLAYERS];
new NombreLicencia[MAX_PLAYERS];
new OwnableCarOffer[MAX_PLAYERS];
new OwnableCarID[MAX_PLAYERS];
new OwnableCarPrice[MAX_PLAYERS];
new Condom[MAX_PLAYERS];
new Spectate[MAX_PLAYERS];
new GettingSpectated[MAX_PLAYERS];
new Spectating[MAX_PLAYERS];
new BlindFold[MAX_PLAYERS];
new PlayerNeedsHelp[MAX_PLAYERS];
new RegText[MAX_PLAYERS];
new RegConfig[MAX_PLAYERS];
new Facturing[MAX_PLAYERS];
new fPay[MAX_PLAYERS];
new fDest[MAX_PLAYERS];
new fFacturer[MAX_PLAYERS];

new Editing[MAX_PLAYERS];

new RequestingBackup[MAX_PLAYERS];
new FreezeLast[MAX_PLAYERS];
new RStep[MAX_PLAYERS];

new Refueling[MAX_PLAYERS];
new QFA[MAX_PLAYERS][24];
new Float:TeleportDest[MAX_PLAYERS][3];

/* Client */
 
// Logs
#include "client/log/header.inc"

// Player - Header
#include "client/player/account.inc"
#include "client/player/characters.inc"
#include "client/player/money.inc"
#include "client/player/toys.inc"
#include "client/player/skins.inc"
#include "client/player/misc.inc"

// Admin - Header
#include "client/admin/header.inc"

// Player - Keygame
#include "client/keygame/header.inc"
#include "client/keygame/callbacks.inc"
#include "client/keygame/functions.inc"

// Mapping
#include "client/mapping/header.inc"
#include "client/mapping/functions.inc"
#include "client/mapping/callbacks.inc"
#include "client/mapping/commands.inc"

// Fish
#include "client/fishing/header.inc"
#include "client/fishing/functions.inc"

// Inventory
#include "client/inventory/header.inc"
#include "client/inventory/callbacks.inc"
#include "client/inventory/functions.inc"
#include "client/inventory/commands.inc"

// Factions
#include "client/factions/header.inc"
#include "client/factions/functions.inc"
#include "client/factions/callbacks.inc"
#include "client/factions/commands.inc"
#include "client/factions/dialogs.inc"

// Desconocidos
#include "client/player/desconocidos.inc"

// Login
#include "client/login/textdraws.inc"
#include "client/login/login.inc"
#include "client/login/characters.inc"

// Banks
#include "client/banks/header.inc"
#include "client/banks/functions.inc"
#include "client/banks/callbacks.inc"
#include "client/banks/commands.inc"
#include "client/banks/dialogs.inc"

// Doors
#include "client/doors/header.inc"
#include "client/doors/functions.inc"
#include "client/doors/callbacks.inc"
#include "client/doors/commands.inc"

// Actors
#include "client/actors/header.inc"
#include "client/actors/functions.inc"
#include "client/actors/callbacks.inc"
#include "client/actors/commands.inc"

// House
#include "client/house/header.inc"
#include "client/house/functions.inc"
#include "client/house/callbacks.inc"
#include "client/house/commands.inc"
#include "client/house/dialogs.inc"

// Business
#include "client/business/header.inc"
#include "client/business/functions.inc"
#include "client/business/callbacks.inc"
#include "client/business/commands.inc"
#include "client/business/dialogs.inc"

// Vehicles
#include "client/vehicles/header.inc"
#include "client/vehicles/functions.inc"
#include "client/vehicles/callbacks.inc"
#include "client/vehicles/commands.inc"
#include "client/vehicles/dialogs.inc"

// Fuels
#include "client/fuels/header.inc"
#include "client/fuels/callbacks.inc"
#include "client/fuels/commands.inc"

// Furniture
#include "client/furniture/header.inc"
#include "client/furniture/functions.inc"
#include "client/furniture/callbacks.inc"
#include "client/furniture/commands.inc"
#include "client/furniture/dialogs.inc"

// Peaje
#include "client/peaje/header.inc"
#include "client/peaje/functions.inc"
#include "client/peaje/mapeo.inc"
#include "client/peaje/commands.inc"

// Fire
#include "client/fire/header.inc"
#include "client/fire/functions.inc"
#include "client/fire/callbacks.inc"
#include "client/fire/commands.inc"
#include "client/fire/dialogs.inc"

// Locations
#include "client/locations/header.inc"
#include "client/locations/callbacks.inc"
#include "client/locations/commands.inc"
#include "client/locations/dialogs.inc"

// Graffitis
#include "client/graffitis/header.inc"
#include "client/graffitis/callbacks.inc"
#include "client/graffitis/commands.inc"
#include "client/graffitis/dialogs.inc"

// Boxes
#include "client/boxes/header.inc"
#include "client/boxes/functions.inc"
#include "client/boxes/callbacks.inc"
#include "client/boxes/commands.inc"

// Backpacks
#include "client/backpacks/header.inc"
#include "client/backpacks/functions.inc"
#include "client/backpacks/callbacks.inc"
#include "client/backpacks/commands.inc"
#include "client/backpacks/dialogs.inc"

// Containers
#include "client/containers/header.inc"
#include "client/containers/functions.inc"
#include "client/containers/callbacks.inc"
#include "client/containers/commands.inc"
#include "client/containers/dialogs.inc"

// Objects
#include "client/objects/header.inc"
#include "client/objects/functions.inc"
#include "client/objects/callbacks.inc"
#include "client/objects/commands.inc"
#include "client/objects/dialogs.inc"

// Boombox
#include "client/boombox/header.inc"
#include "client/boombox/functions.inc"
#include "client/boombox/callbacks.inc"
#include "client/boombox/commands.inc"
#include "client/boombox/dialogs.inc"

// Damage
#include "client/damage/header.inc"
#include "client/damage/functions.inc"
#include "client/damage/callbacks.inc"
#include "client/damage/dialogs.inc"

// Player
#include "client/player/functions.inc"
#include "client/player/commands.inc"
#include "client/player/dialogs.inc"

// Admin 
#include "client/admin/functions.inc"
#include "client/admin/commands.inc"
#include "client/admin/dialogs.inc"

// Jobs
#include "client/jobs/header.inc"

// Notificaciones del cliente (servidor)
#include "client/client-notifications/headers.inc"
#include "client/client-notifications/functions.inc"

// Notificaciones del jugador
#include "client/notifications/headers.inc"
#include "client/notifications/callbacks.inc"
#include "client/notifications/functions.inc"


/*-------- Server --------*/

// Loader
#include "client/loader/header.inc"
#include "client/loader/infoserver.inc"

// Maps
#include "client/maps/loader.inc"



stock isnumeric(const str[]) {
    for (new i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

stock hexstr(const hex[]) {
    new value = 0;
    for (new i = 0; i < strlen(hex); i++) {
        value <<= 4;
        if (hex[i] >= '0' && hex[i] <= '9') value += hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F') value += hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f') value += hex[i] - 'a' + 10;
        else return 0; // carácter inválido
    }
    return value;
}

//actualizar skin normal
GivePlayerSkin(playerid, idskin)
{
	if (idskin == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes colocarle la skin de CJ.");
	InfoPersonaje[playerid][pJobSkin] = 0;
	InfoPersonaje[playerid][pSkin] = idskin;
	SetPlayerSkin(playerid, idskin);
	new query[170];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Skin = '%d', JobSkin = 0 WHERE ID = '%d'", idskin, InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

//actualizar skin de facción/trabajo
GivePlayerJobSkin(playerid, idskin)
{
	if (idskin == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes colocarle la skin de CJ.");
	InfoPersonaje[playerid][pJobSkin] = idskin;
	SetPlayerSkin(playerid, idskin);
	guardar_int_mysql("personajes", "JobSkin", InfoPersonaje[playerid][pID], idskin);
	return 1;
}

funcion SPEC_SetPlayerVirtualWorld(playerid, vw)
{
	SetPlayerVirtualWorld(playerid, vw);
	if (vw == 0)
	{
		DentroNegocio[playerid] = -1;
		DentroCasa[playerid] = -1;
	}
	return 1;
}
#define SetPlayerVirtualWorld SPEC_SetPlayerVirtualWorld

SetPosEx(playerid, Float: pot_x, Float: pot_y, Float: pot_z, Float: pot_r = 0.0, pot_int, pot_vw, guardable)
{
	//posiciones x,y,z,r
	if (pot_x != -1)
	{
		InfoPersonaje[playerid][pPosicionX] = pot_x;
		InfoPersonaje[playerid][pPosicionY] = pot_y;
		InfoPersonaje[playerid][pPosicionZ] = pot_z;
		InfoPersonaje[playerid][pPosicionR] = pot_r;
		SetPlayerPosEx(playerid, pot_x, pot_y, pot_z);
		SetPlayerFacingAngle(playerid, pot_r);
	}
	else { GetPlayerPos(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ]); GetPlayerFacingAngle(playerid, InfoPersonaje[playerid][pPosicionR]); }
	//interior
	if (pot_int != -1)
	{
		InfoPersonaje[playerid][pInterior] = pot_int;
		SetPlayerInterior(playerid, pot_int);
	}
	else InfoPersonaje[playerid][pInterior] = GetPlayerInterior(playerid);
	//virtualworld
	if (pot_vw != -1)
	{
		InfoPersonaje[playerid][pVirtualWorld] = pot_vw;
		SetPlayerVirtualWorld(playerid, pot_vw);
	}
	else InfoPersonaje[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
	if (guardable != 0)
	{
		//guardado mysql
		new query[1028];
		mysql_format(db_samp, query, sizeof query , "UPDATE personajes SET PosicionX = '%f', PosicionY = '%f', PosicionZ = '%f', PosicionR = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
		InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ], InfoPersonaje[playerid][pPosicionR], InfoPersonaje[playerid][pInterior], InfoPersonaje[playerid][pVirtualWorld], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
    }
	return 1;
}


/*GetNameFormat(playerid)
{
    new nameplayer[128];
    if (AdminDuty[playerid] == 1) { format(nameplayer, sizeof(nameplayer), "%s", InfoPersonaje[playerid][pNombre_Apellido]); }
    else { format(nameplayer, sizeof(nameplayer), "#%s", InfoPersonaje[playerid][pCodigo]); }
    for (new i = 0, j = strlen(nameplayer); i < j; i++)
    {
        if (nameplayer[i] == '_')
        {
            nameplayer[i] = ' ';
        }
    }
    return nameplayer;
}*/

NombreDeCuenta(playerid)
{
    new nameplayer[128];
    if (AdminDuty[playerid] == 1) { format(nameplayer, sizeof(nameplayer), "%s", InfoPersonaje[playerid][pNombre_Apellido]); }
    else { format(nameplayer, sizeof(nameplayer), "#%s", InfoPersonaje[playerid][pCodigo]); }
    return nameplayer;
}

NombreOriginal(playerid)
{
    new nameplayer[128];
    if (AdminDuty[playerid] == 1) { format(nameplayer, sizeof(nameplayer), "%s", InfoPersonaje[playerid][pNombre_Apellido]); }
    else { format(nameplayer, sizeof(nameplayer), "#%s", InfoPersonaje[playerid][pCodigo]); }
    return nameplayer;
}

Nombre2Original(playerid)
{
	new nameplayer[128];
    if (AdminDuty[playerid] == 1) { format(nameplayer, sizeof(nameplayer), "%s", InfoPersonaje[playerid][pNombre_Apellido]); }
    else { format(nameplayer, sizeof(nameplayer), "#%s", InfoPersonaje[playerid][pCodigo]); }	
	return nameplayer;
}

//sistema de objetos en vehículos (VIP)
#define Create_VehObject 690

new VehicleFurnObjs[] =
{
	1000,1001,1002,1003,1004,1005,1007,1018,1019,1021,1024,1029,1043,
    1044,1047,1048,1049,1050,1056,1090,2768, 11736,19147,19580,2690,
	19308,1550,19306,19307,18749,19054, 19314,2404,2405,2406,19317,19318,
	2232,1840,19471,19878,19893,19894,19873,19874,19624,19621,19620,19078,
	1025,1073,1074,1075,1076,1077,1078,1079,1080,1081,1082,1083,1084,1085,
	1096,1097,1098,
};

//system vehicleinfo by edinson
#define MAX_VEHICLE_NAME			27

enum vSync_Vehicle_Info
{
	NombreVehicle[MAX_VEHICLE_NAME],
	Seats,
	Windows,
	Float:Mass,
	DriveType,
	EngineType,
	MaxSpeed,
	bool:Nitro,
	Float: NeonOffsetX,
	Float: NeonOffsetY,
    Float: NeonOffsetZ
}

new vSync_VehicleInfo[212][vSync_Vehicle_Info] =
{
	{"Landstalker", 4, 4, 1700.0, '4', 'D', 159, true, -0.924996, 0.009998, -0.674996},
	{"Bravura", 2, 2, 1300.0, 'F', 'P', 148, true, -0.979999, 0.074997, -0.489998},
	{"Buffalo", 2, 2, 1500.0, 'R', 'P', 188, true, -1.034999, -0.029998, -0.579999},
	{"Linerunner", 2, 2, 3800.0, 'R', 'D', 111, true, -0.884998, 1.834998, -1.099997},
	{"Perennial", 4, 4, 1200.0, 'F', 'P', 134, true, -0.839999, -0.064998, -0.419999},
	{"Sentinel", 4, 4, 1600.0, 'R', 'P', 165, true, -0.914999, 0.000000, -0.534999},
	{"Dumper", 1, 1, 20000.0, 'R', 'D', 111, true, -1.129999, 0.354999, -1.219998},
	{"Firetruck", 2, 2, 6500.0, 'R', 'D', 150, true, -1.214998, 0.125000, -0.759998},
	{"Trashmaster", 2, 2, 5500.0, 'R', 'D', 101, true, -0.664999, 0.709999, -0.889998},
	{"Stretch", 4, 4, 2200.0, 'R', 'P', 159, true, -0.914999, -0.294999, -0.474999},
	{"Manana", 2, 2, 1000.0, 'F', 'P', 131, true, -0.879998, 0.000000, -0.389999},
	{"Infernus", 2, 2, 1400.0, '4', 'P', 223, true, -0.969999, 0.004999, -0.559997},
	{"Voodoo", 2, 2, 1800.0, 'R', 'P', 170, true, -0.994997, -0.154999, -0.569998},
	{"Pony", 4, 4, 2600.0, 'R', 'D', 111, true, -0.919999, -0.069999, -0.719999},
	{"Mule", 2, 2, 3500.0, 'R', 'D', 107, true, -0.759998, -0.469998, -0.524999},
	{"Cheetah", 2, 2, 1200.0, 'R', 'P', 194, true, -0.949998, -0.009998, -0.524999},
	{"Ambulance", 4, 4, 2600.0, '4', 'D', 155, true, -1.259999, -0.604999, -0.664999},
	{"Leviathan", 2, 2, 15000.0, '4', 'P', 143, false, -2.255002, 0.859999, -0.124999},
	{"Moonbeam", 4, 4, 2000.0, 'R', 'D', 116, true, -1.004999, 0.089997, -0.829999},
	{"Esperanto", 2, 2, 1800.0, 'R', 'P', 150, true, -0.934997, -0.009998, -0.584999},
	{"Taxi", 4, 4, 1450.0, 'F', 'P', 146, true, -0.954999, -0.009998, -0.444999},
	{"Washington", 2, 2, 1850.0, 'R', 'P', 155, true, -0.929997, -0.029998, -0.589999},
	{"Bobcat", 2, 2, 1700.0, '4', 'D', 141, true, -0.889998, 0.009998, -0.609999},
	{"Mr. Whoopee", 2, 2, 1700.0, 'R', 'D', 100, true, -0.999997, 0.164995, -0.714999},
	{"BF Injection", 2, 0, 1200.0, 'R', 'P', 137, true, -0.739997, 0.039999, -0.234999},
	{"Hunter", 1, 1, 10000.0, '4', 'P', 214, false, -0.639998, 2.475008, -0.789999},
	{"Premier", 4, 4, 1600.0, 'R', 'P', 175, true, -0.969999, 0.000000, -0.464998},
	{"Enforcer", 4, 4, 4000.0, 'R', 'D', 167, true, -1.124999, -0.714999, -0.734999},
	{"Securicar", 4, 2, 7000.0, 'R', 'D', 158, true, -1.124999, 0.054999, -0.759998},
	{"Banshee", 2, 2, 1400.0, 'R', 'P', 203, true, -0.844999, 0.004999, -0.474999},
	{"Predator", 1, 0, 2200.0, 'R', 'P', 184, false, 0.000000, 0.000000, 0.000000},
	{"Bus", 9, 2, 5500.0, 'R', 'D', 131, true, -1.304998, 2.300004, -0.714999},
	{"Rhino", 1, 0, 25000.0, '4', 'D', 95, true, 0.000000, 0.000000, 0.000000},
	{"Barracks", 2, 2, 10500.0, '4', 'D', 112, true, -0.579999, 0.994997, -0.874997},
	{"Hotknife", 2, 2, 1400.0, 'R', 'P', 169, true, 0.000000, 0.000000, 0.000000},
	{"Article Trailer", 1, 0, 3800.0, 'R', 'D', 0, true, 0.000000, 0.000000, 0.000000},
	{"Previon", 2, 2, 1400.0, 'F', 'P', 150, true, -0.859999, -0.024999, -0.489998},
	{"Coach", 9, 0, 9500.0, 'R', 'D', 159, true, -1.314998, 2.245002, -0.724999},
	{"Cabbie", 4, 4, 1750.0, 'R', 'P', 144, true, -0.969999, -0.034999, -0.674996},
	{"Stallion", 2, 2, 1600.0, 'R', 'P', 170, true, -0.884998, 0.034999, -0.644999},
	{"Rumpo", 4, 4, 2000.0, 'F', 'P', 137, true, -0.914999, -0.045000, -0.899999},
	{"RC Bandit", 1, 0, 100.0, '4', 'E', 76, true, 0.000000, 0.000000, 0.000000},
	{"Romero", 2, 2, 2500.0, 'R', 'P', 140, true, -1.004999, -0.074997, -0.604999},
	{"Packer", 2, 2, 8000.0, 'R', 'D', 127, true, -0.809997, 2.770015, -1.174998},
	{"Monster", 2, 2, 5000.0, '4', 'P', 111, true, -1.064998, 0.000000, 0.135000},
	{"Admiral", 4, 4, 1650.0, 'F', 'P', 165, true, -0.949998, 0.000000, -0.519999},
	{"Squallo", 1, 0, 2200.0, 'R', 'P', 240, false, 0.000000, 0.000000, 0.000000},
	{"Seasparrow", 2, 2, 3000.0, '4', 'P', 145, false, -1.004999, 0.259999, -0.769999},
	{"Pizzaboy", 1, 0, 350.0, 'R', 'P', 190, false, 0.000000, 0.000000, 0.000000},
	{"Tram", 2, 0, 1900.0, 'R', 'P', 185, false, 0.000000, 0.000000, 0.000000},
	{"Article Trailer 2", 1, 0, 3800.0, 'R', 'D', 0, true, 0.000000, 0.000000, 0.000000},
	{"Turismo", 2, 2, 1400.0, '4', 'P', 195, true, -0.984999, -0.194995, -0.519999},
	{"Speeder", 1, 0, 2200.0, 'R', 'P', 183, false, 0.000000, 0.000000, 0.000000},
	{"Reefer", 1, 0, 5000.0, 'R', 'P', 57, false, 0.000000, 0.000000, 0.000000},
	{"Tropic", 1, 0, 2200.0, 'R', 'P', 130, false, 0.000000, 0.000000, 0.000000},
	{"Flatbed", 2, 2, 8500.0, 'R', 'D', 159, true, -0.579999, 0.979999, -0.859999},
	{"Yankee", 2, 2, 4500.0, 'R', 'D', 107, true, -0.764998, -0.179995, -0.464998},
	{"Caddy", 2, 0, 1000.0, '4', 'E', 96, true, 0.000000, 0.000000, 0.000000},
	{"Solair", 4, 4, 2000.0, 'R', 'P', 159, true, -0.959999, -0.039999, -0.594999},
	{"Topfun Van (Berkley's RC)", 4, 4, 1900.0, 'R', 'D', 137, true, -0.919999, -0.069999, -0.719999},
	{"Skimmer", 2, 2, 5000.0, '4', 'P', 135, false, -1.399996, 0.554997, -1.819998},
	{"PCJ-600", 2, 0, 500.0, 'R', 'P', 207, false, 0.000000, 0.000000, 0.000000},
	{"Faggio", 2, 0, 350.0, 'R', 'P', 190, false, 0.000000, 0.000000, 0.000000},
	{"Freeway", 2, 0, 800.0, 'R', 'P', 210, false, 0.000000, 0.000000, 0.000000},
	{"RC Baron", 1, 0, 100.0, 'F', 'P', 45, true, 0.000000, 0.000000, 0.000000},
	{"RC Raider", 1, 0, 100.0, '4', 'P', 50, true, 0.000000, 0.000000, 0.000000},
	{"Glendale", 4, 4, 1600.0, 'R', 'P', 148, true, -0.989997, -0.064998, -0.489998},
	{"Oceanic", 4, 4, 1900.0, 'R', 'P', 142, true, -0.989997, -0.044998, -0.484999},
	{"Sanchez", 2, 0, 500.0, 'R', 'P', 186, false, 0.000000, 0.000000, 0.000000},
	{"Sparrow", 2, 2, 2500.0, '4', 'P', 145, false, 0.000000, 0.000000, 0.000000},
	{"Patriot", 4, 4, 2500.0, '4', 'P', 158, true, -1.119999, -0.149995, -0.359999},
	{"Quad", 2, 0, 400.0, '4', 'P', 111, true, 0.000000, 0.000000, 0.000000},
	{"Coastguard", 1, 0, 1200.0, 'R', 'P', 125, false, 0.000000, 0.000000, 0.000000},
	{"Dinghy", 1, 0, 800.0, 'R', 'P', 107, false, 0.000000, 0.000000, 0.000000},
	{"Hermes", 2, 2, 1950.0, 'F', 'P', 150, true, -0.994997, -0.064998, -0.544999},
	{"Sabre", 2, 2, 1700.0, 'R', 'P', 175, true, -0.904999, -0.054999, -0.549996},
	{"Rustler", 1, 1, 5000.0, '4', 'P', 220, false, 0.000000, 0.000000, 0.000000},
	{"ZR-350", 2, 2, 1400.0, 'R', 'P', 188, true, -0.979999, 0.019997, -0.514998},
	{"Walton", 2, 2, 1850.0, '4', 'D', 119, true, -0.804997, 0.064998, -0.519999},
	{"Regina", 4, 4, 1500.0, 'F', 'P', 141, true, -0.854999, 0.090000, -0.454997},
	{"Comet", 2, 2, 1400.0, '4', 'P', 186, true, -0.879998, 0.000000, -0.489998},
	{"BMX", 1, 0, 100.0, 'R', 'P', 97, false, 0.000000, 0.000000, 0.000000},
	{"Burrito", 2, 4, 1900.0, 'R', 'P', 158, true, -0.989997, 0.000000, -0.759998},
	{"Camper", 3, 3, 1900.0, 'R', 'P', 124, true, -0.834999, -0.149995, -0.744997},
	{"Marquis", 1, 0, 5000.0, 'R', 'P', 64, false, 0.000000, 0.000000, 0.000000},
	{"Baggage", 1, 0, 1000.0, 'R', 'E', 100, true, -0.629998, 0.164995, -0.374998},
	{"Dozer", 1, 0, 10000.0, '4', 'D', 65, true, 0.000000, 0.000000, 0.000000},
	{"Maverick", 4, 4, 5000.0, '4', 'P', 181, false, 0.000000, 0.000000, 0.000000},
	{"News Chopper", 2, 2, 3500.0, '4', 'P', 170, false, 0.000000, 0.000000, 0.000000},
	{"Rancher", 2, 2, 2500.0, '4', 'P', 141, true, -1.019999, 0.109999, -0.679997},
	{"FBI Rancher", 4, 4, 3500.0, '4', 'P', 158, true, -1.054998, 0.125000, -0.604999},
	{"Virgo", 2, 2, 1700.0, 'R', 'P', 150, true, -0.874997, -0.009998, -0.569998},
	{"Greenwood", 4, 4, 1600.0, 'R', 'P', 142, true, -0.909999, 0.000000, -0.459998},
	{"Jetmax", 1, 0, 3000.0, 'R', 'P', 183, false, 0.000000, 0.000000, 0.000000},
	{"Hotring Racer", 2, 2, 1600.0, 'R', 'P', 217, true, -0.909999, -0.199999, -0.639998},
	{"Sandking", 2, 2, 2000.0, '4', 'P', 178, true, -1.024999, 0.184999, -0.809997},
	{"Blista Compact", 2, 2, 1000.0, 'F', 'P', 164, true, -0.854999, 0.029998, -0.469998},
	{"Police Maverick", 4, 4, 4500.0, '4', 'P', 190, false, 0.000000, 0.000000, 0.000000},
	{"Boxville", 4, 2, 5500.0, 'R', 'D', 109, true, -1.149999, 0.269998, -0.654999},
	{"Benson", 2, 2, 3500.0, 'R', 'D', 124, true, -0.969999, -1.404996, -0.199999},
	{"Mesa", 2, 2, 1300.0, '4', 'D', 142, true, -0.969999, 0.189998, -0.574998},
	{"RC Goblin", 1, 0, 100.0, '4', 'P', 30, true, 0.000000, 0.000000, 0.000000},
	{"Hotring Racer A", 2, 2, 1600.0, 'R', 'P', 217, true, -0.909999, 0.029998, -0.639998},
	{"Hotring Racer B", 2, 2, 1600.0, 'R', 'P', 217, true, -0.909999, -0.184999, -0.639998},
	{"Bloodring Banger", 2, 2, 2100.0, 'R', 'P', 175, true, -0.989997, -0.059999, -0.494998},
	{"Rancher (Lure)", 2, 2, 2500.0, '4', 'P', 141, true, -1.019999, 0.109999, -0.679997},
	{"Super GT", 2, 2, 1400.0, 'R', 'P', 181, true, -0.904999, -0.249999, -0.509998},
	{"Elegant", 4, 4, 2200.0, 'R', 'P', 167, true, -1.084998, -0.024999, -0.589999},
	{"Journey", 2, 3, 3500.0, 'R', 'D', 109, true, -1.334998, -0.424997, -0.979999},
	{"Bike", 1, 0, 100.0, 'R', 'P', 105, false, 0.000000, 0.000000, 0.000000},
	{"Mountain Bike", 1, 0, 100.0, 'R', 'P', 130, false, 0.000000, 0.000000, 0.000000},
	{"Beagle", 2, 2, 10000.0, '4', 'P', 133, false, 0.000000, 0.000000, 0.000000},
	{"Cropduster", 1, 1, 5000.0, '4', 'P', 115, false, 0.000000, 0.000000, 0.000000},
	{"Stuntplane", 1, 1, 5000.0, '4', 'P', 151, false, 0.000000, 0.000000, 0.000000},
	{"Tanker", 2, 2, 3800.0, 'R', 'D', 122, true, -0.969999, 1.669998, -1.174998},
	{"Roadtrain", 2, 2, 5000.0, 'R', 'D', 144, true, -1.454998, 0.439999, -1.854997},
	{"Nebula", 4, 4, 1400.0, 'F', 'P', 159, true, -0.989997, 0.024999, -0.584999},
	{"Majestic", 2, 2, 1400.0, 'R', 'P', 159, true, -0.959999, 0.004999, -0.554997},
	{"Buccaneer", 2, 2, 1700.0, 'R', 'P', 166, true, -1.049998, 0.109999, -0.439999},
	{"Shamal", 1, 0, 15000.0, '4', 'P', 272, false, 0.000000, 0.000000, 0.000000},
	{"Hydra", 1, 1, 9000.0, '4', 'P', 272, false, 0.000000, 0.000000, 0.000000},
	{"FCR-900", 2, 0, 500.0, 'R', 'P', 209, false, 0.000000, 0.000000, 0.000000},
	{"NRG-500", 2, 0, 400.0, 'R', 'P', 209, false, 0.000000, 0.000000, 0.000000},
	{"HPV1000", 2, 0, 500.0, 'R', 'P', 197, false, 0.000000, 0.000000, 0.000000},
	{"Cement Truck", 2, 2, 5500.0, 'R', 'D', 131, true, -0.689997, 1.489997, -1.319998},
	{"Towtruck", 2, 2, 3500.0, 'R', 'D', 162, true, -1.054998, 0.499998, -0.329997},
	{"Fortune", 2, 2, 1700.0, 'R', 'P', 159, true, -0.899999, 0.000000, -0.564997},
	{"Cadrona", 2, 2, 1200.0, 'R', 'P', 150, true, -0.944998, 0.154999, -0.419999},
	{"FBI Truck", 2, 2, 4000.0, '4', 'D', 178, true, -0.924996, 0.059999, -0.529999},
	{"Willard", 4, 4, 1800.0, 'R', 'P', 150, true, -0.934997, -0.109999, -0.429998},
	{"Forklift", 1, 0, 1000.0, 'F', 'E', 61, true, 0.000000, 0.000000, 0.000000},
	{"Tractor", 1, 0, 2000.0, 'R', 'D', 71, true, -0.144997, 0.314999, -0.444999},
	{"Combine Harvester", 1, 1, 8500.0, '4', 'D', 111, true, 0.000000, 0.000000, 0.000000},
	{"Feltzer", 2, 2, 1600.0, 'R', 'P', 169, true, -0.924996, -0.034999, -0.479999},
	{"Remington", 2, 2, 1800.0, 'R', 'P', 170, true, -0.984999, 0.164995, -0.564997},
	{"Slamvan", 2, 2, 1950.0, 'R', 'P', 160, true, -1.069998, -0.034999, -0.569998},
	{"Blade", 2, 2, 1500.0, 'R', 'P', 175, true, -0.954999, -0.019997, -0.579999},
	{"Freight", 2, 0, 5500.0, 'R', 'D', 0, false, 0.000000, 0.000000, 0.000000},
	{"Brown Streak", 2, 0, 5500.0, 'R', 'D', 0, false, 0.000000, 0.000000, 0.000000},
	{"Vortex", 1, 0, 1900.0, 'R', 'P', 101, true, -1.004999, -0.049998, -0.019997},
	{"Vincent", 4, 4, 1800.0, 'F', 'P', 150, true, -1.024999, -0.090000, -0.639998},
	{"Bullet", 2, 2, 1200.0, 'R', 'P', 205, true, -0.904999, 0.000000, -0.414999},
	{"Clover", 2, 2, 1600.0, 'R', 'P', 166, true, -0.894999, 0.014999, -0.539999},
	{"Sadler", 2, 2, 1700.0, '4', 'D', 152, true, -0.904999, 0.009998, -0.409999},
	{"Firetruck (ladder variant)", 2, 2, 6500.0, 'R', 'D', 150, true, -1.089998, 0.000000, -0.709999},
	{"Hustler", 2, 2, 1700.0, 'R', 'P', 148, true, -0.939997, -0.029998, -0.564997},
	{"Intruder", 4, 4, 1800.0, 'R', 'P', 150, true, -1.039999, -0.100000, -0.474999},
	{"Primo", 4, 4, 1600.0, 'R', 'P', 144, true, -0.884998, 0.059999, -0.479999},
	{"Cargobob", 2, 2, 20000.0, '4', 'P', 158, false, -1.769997, 1.484997, -1.774996},
	{"Tampa", 2, 2, 1700.0, 'R', 'P', 155, true, -0.949998, 0.104997, -0.439999},
	{"Sunrise", 4, 4, 1600.0, 'F', 'P', 146, true, -1.089998, -0.059999, -0.554997},
	{"Merit", 4, 4, 1800.0, 'R', 'P', 159, true, -0.964999, 0.004999, -0.564997},
	{"Utility Van", 2, 2, 2600.0, 'R', 'D', 122, true, -1.034999, 0.749997, -0.254999},
	{"Nevada", 1, 0, 25000.0, '4', 'P', 193, false, 0.000000, 0.000000, 0.000000},
	{"Yosemite", 2, 2, 3000.0, 'R', 'P', 145, true, -1.109997, 0.009998, -0.534999},
	{"Windsor", 2, 2, 1500.0, 'R', 'P', 160, true, -0.754998, 0.000000, -0.464998},
	{"Monster A", 2, 2, 5000.0, '4', 'P', 111, true, -1.119999, 0.000000, 0.184999},
	{"Monster B", 2, 2, 5000.0, '4', 'P', 111, true, -1.129999, 0.044998, 0.074997},
	{"Uranus", 2, 2, 1400.0, 'R', 'P', 157, true, -0.894999, -0.089997, -0.374998},
	{"Jester", 2, 2, 1500.0, 'F', 'P', 179, true, -0.964999, 0.000000, -0.444999},
	{"Sultan", 4, 4, 1400.0, '4', 'P', 171, true, -1.004999, 0.054999, -0.414999},
	{"Stratum", 4, 4, 1800.0, 'R', 'P', 155, true, -0.919999, 0.129997, -0.574998},
	{"Elegy", 2, 2, 1500.0, 'R', 'P', 179, true, -0.909999, 0.119998, -0.404998},
	{"Raindance", 2, 2, 10000.0, '4', 'P', 160, false, 0.000000, 0.000000, 0.000000},
	{"RC Tiger", 1, 0, 100.0, '4', 'E', 89, true, 0.000000, 0.000000, 0.000000},
	{"Flash", 2, 2, 1400.0, 'F', 'P', 166, true, -0.824998, 0.000000, -0.414999},
	{"Tahoma", 4, 4, 1800.0, 'R', 'P', 161, true, -0.989997, -0.049998, -0.479999},
	{"Savanna", 4, 2, 1500.0, 'R', 'P', 175, true, -1.089998, 0.309998, -0.609999},
	{"Bandito", 1, 0, 1000.0, 'R', 'P', 148, true, -0.334998, 0.100000, -0.374998},
	{"Freight Flat Trailer", 1, 0, 5500.0, 'R', 'D', 0, false, 0.000000, 0.000000, 0.000000},
	{"Brown Streak Trailer", 1, 0, 5500.0, 'R', 'D', 0, false, 0.000000, 0.000000, 0.000000},
	{"Kart", 1, 0, 300.0, 'R', 'P', 94, true, 0.000000, 0.000000, 0.000000},
	{"Mower", 1, 0, 800.0, 'R', 'P', 61, true, 0.000000, 0.000000, 0.000000},
	{"Dune", 2, 2, 10000.0, '4', 'P', 111, true, 0.000000, 0.000000, 0.000000},
	{"Sweeper", 1, 2, 800.0, 'R', 'P', 61, true, 0.000000, 0.000000, 0.000000},
	{"Brouge", 2, 2, 1700.0, 'R', 'P', 159, true, -0.924996, 0.004999, -0.334998},
	{"Tornado", 2, 2, 1700.0, 'R', 'P', 159, true, -1.019999, -0.140000, -0.419999},
	{"AT-400", 2, 0, 60000.0, '4', 'P', 250, false, 0.000000, 0.000000, 0.000000},
	{"DFT-30", 2, 2, 5500.0, 'R', 'D', 131, true, -1.429998, -0.649999, -0.879998},
	{"Huntley", 4, 4, 2500.0, '4', 'P', 159, true, -1.014999, 0.000000, -0.484999},
	{"Stafford", 4, 4, 2200.0, 'R', 'P', 154, true, -1.089998, 0.014999, -0.474999},
	{"BF-400", 2, 0, 500.0, 'R', 'P', 200, false, 0.000000, 0.000000, 0.000000},
	{"Newsvan", 4, 3, 1900.0, 'R', 'D', 137, true, -0.984999, -0.194995, -0.709999},
	{"Tug", 1, 2, 800.0, 'R', 'P', 86, true, -0.674996, 0.259999, 0.129997},
	{"Petrol Trailer", 1, 0, 3800.0, 'R', 'D', 0, true, 0.000000, 0.000000, 0.000000},
	{"Emperor", 4, 4, 1800.0, 'R', 'P', 154, true, -1.019999, -0.009998, -0.354999},
	{"Wayfarer", 2, 0, 800.0, 'R', 'P', 211, false, 0.000000, 0.000000, 0.000000},
	{"Euros", 2, 2, 1400.0, '4', 'P', 166, true, -1.009999, -0.064998, -0.534999},
	{"Hotdog", 2, 2, 5500.0, 'R', 'D', 109, true, -1.374997, 0.000000, -0.664999},
	{"Club", 2, 2, 1400.0, 'F', 'P', 164, true, -0.909999, 0.000000, -0.359999},
	{"Freight Box Trailer", 1, 0, 5500.0, 'R', 'D', 0, false, 0.000000, 0.000000, 0.000000},
	{"Article Trailer 3", 1, 0, 3800.0, 'R', 'D', 0, true, 0.000000, 0.000000, 0.000000},
	{"Andromada", 2, 0, 40000.0, '4', 'P', 266, false, 0.000000, 0.000000, 0.000000},
	{"Dodo", 2, 2, 5000.0, '4', 'P', 135, false, 0.000000, 0.000000, 0.000000},
	{"RC Cam", 1, 0, 100.0, '4', 'E', 62, true, 0.000000, 0.000000, 0.000000},
	{"Launch", 1, 0, 2200.0, 'R', 'P', 118, false, 0.000000, 0.000000, 0.000000},
	{"Police Car (LSPD)", 4, 4, 1600.0, 'R', 'P', 177, true, -0.974999, 0.000000, -0.469998},
	{"Police Car (SFPD)", 4, 4, 1600.0, 'R', 'P', 177, true, -0.969999, 0.000000, -0.464998},
	{"Police Car (LVPD)", 4, 4, 1600.0, 'R', 'P', 177, true, -1.004999, -0.014999, -0.414999},
	{"Ranger", 2, 2, 2500.0, '4', 'D', 159, true, -1.019999, 0.115000, -0.684997},
	{"Picador", 2, 2, 1600.0, 'R', 'D', 152, true, -0.959999, 0.204998, -0.499998},
	{"S.W.A.T.", 2, 0, 5000.0, '4', 'D', 111, true, 0.000000, 0.000000, 0.000000},
	{"Alpha", 2, 2, 1500.0, 'R', 'P', 171, true, -1.024999, 0.000000, -0.549996},
	{"Phoenix", 2, 2, 1500.0, 'R', 'P', 173, true, -0.954999, 0.034999, -0.629998},
	{"Glendale (destroyed)", 4, 4, 1600.0, 'R', 'P', 148, true, -0.989997, -0.064998, -0.489998},
	{"Sadler (destroyed)", 2, 2, 1700.0, '4', 'D', 152, true, -0.904999, 0.009998, -0.409999},
	{"Baggage Trailer A", 1, 0, 1000.0, 'R', 'E', 0, true, 0.000000, 0.000000, 0.000000},
	{"Baggage Trailer B", 1, 0, 1000.0, 'R', 'E', 0, true, 0.000000, 0.000000, 0.000000},
	{"Tug Stairs Trailer", 1, 0, 1000.0, 'R', 'E', 0, true, 0.000000, 0.000000, 0.000000},
	{"Boxville (burglary)", 4, 2, 5500.0, 'R', 'D', 109, true, -1.149999, 0.269998, -0.654999},
	{"Farm Trailer", 1, 0, 400.0, 'R', 'E', 0, true, 0.000000, 0.000000, 0.000000},
	{"Utility Trailer", 1, 0, 1000.0, 'R', 'E', 0, true, 0.000000, 0.000000, 0.000000}
};
Valid_Vehicle_Nitro(modelid)
{
    new idx = modelid - 400;
	if (0 <= idx <= 211)
	{
        if (vSync_VehicleInfo[idx][Nitro] == false)
		{
	    	return 0;
		}
		return 1;
	}
	return 0;
}

Colocar_Objeto(id, vehicleid)
{
	Loop(x, 5, 0) if (InfoVehiculo[id][vObjModelo][x] != 0)
	{
		if (IsValidDynamicObject(InfoVehiculo[id][vTuneo][x])) DestroyDynamicObject(InfoVehiculo[id][vTuneo][x]);
		InfoVehiculo[id][vTuneo][x] = 0;
		InfoVehiculo[id][vTuneo][x] = CreateDynamicObject(InfoVehiculo[id][vObjModelo][x], 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, GetVehicleVirtualWorld(vehicleid), -1);
		AttachDynamicObjectToVehicle(InfoVehiculo[id][vTuneo][x], vehicleid, InfoVehiculo[id][vObjPosX][x], InfoVehiculo[id][vObjPosY][x], InfoVehiculo[id][vObjPosZ][x], InfoVehiculo[id][vObjRotX][x], InfoVehiculo[id][vObjRotY][x], InfoVehiculo[id][vObjRotZ][x]);
	}
}

//points:
static const Float: PrisonSpawns[][] =
{
	{1776.69446, -1552.67859, -16.99492},
	{1780.51526, -1553.43176, -16.99492},
	{1773.17920, -1552.82556, -16.99492},
	{1769.94604, -1552.24744, -16.99492},
	{1774.08887, -1566.37305, -16.99492},
	{1777.54370, -1566.35754, -16.99492},
	{1781.06042, -1566.39111, -16.99492},
	{1784.12488, -1569.50427, -13.48743},
	{1779.88831, -1571.19141, -13.48743},
	{1773.11743, -1571.12317, -13.48743},
	{1776.72620, -1570.80774, -13.48743},
	{1770.01611, -1571.29309, -13.48743},
	{1769.85059, -1548.55701, -13.48743},
	{1773.26196, -1549.37634, -13.48743},
	{1776.86987, -1549.58398, -13.48743},
	{1779.88196, -1549.17017, -13.48743},
	{1783.45874, -1549.51221, -13.48743}
};

dar_chaleco(playerid, Float: armour) // Fijar
{
	if (armour >= 99.0) InfoPersonaje[playerid][pChaleco] = 100.0;
	else InfoPersonaje[playerid][pChaleco] = armour;
	SetPlayerArmour(playerid, InfoPersonaje[playerid][pChaleco]);
	guardar_float_mysql("personajes", "Chaleco", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pChaleco]);
	return 1;
}

dar_vida(playerid, Float: hp) // Fijar
{
	if (hp >= 99.0) { InfoPersonaje[playerid][pVida] = 100.0; ResetPlayerHeridas(playerid); }
	else InfoPersonaje[playerid][pVida] = hp;
	SetPlayerHealth(playerid, InfoPersonaje[playerid][pVida]);
	guardar_float_mysql("personajes", "Vida", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pVida]);
	return 1;
}

quitar_vida(playerid, Float: sg1) // Quitar
{
	new Float: sg0 = InfoPersonaje[playerid][pVida];
	InfoPersonaje[playerid][pVida] = sg0+sg1;


	if(InfoPersonaje[playerid][pVida] <= 10.0) // si tiene menos de 10 de vida dejar inconsciente
	{
		if(InfoPersonaje[playerid][pEstado] == 0)
		{
			PonerInconsciente(playerid);
		}
	}

	if (InfoPersonaje[playerid][pEstado] == 2)
	{
		if(InfoPersonaje[playerid][pVida] <= 0.0)
		{
			if (GetPVarInt(playerid, "EstaCrack") == 0)
			{
				SetPlayerHealth(playerid, 25.0);
				SetPVarInt(playerid, "EstaCrack", 1);
				estado_xdxdxd(playerid, 1);
				Rematar(playerid);
			}
			else estado_xdxdxd(playerid, 2);
			return 1;
		}
	}
	SetPlayerHealth(playerid, sg0+sg1);
	guardar_float_mysql("personajes", "Vida", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pVida]);
	return 1;
}

stock Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2))
	{
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock split(const strsrc[], strdest[][], delimiter)
{
	new i, li;
	new aNum;
	new len;
	while(i <= strlen(strsrc)){
	    if(strsrc[i]==delimiter || i==strlen(strsrc)){
	        len = strmid(strdest[aNum], strsrc, li, i, 128);
	        strdest[aNum][len] = 0;
	        li = i+1;
	        aNum++;
		}
		i++;
	}
	return 1;
}

enum Spikes
{
	Float:sX,
	Float:sY,
	Float:sZ,
	sObjectID,
	sDeployedBy[MAX_PLAYER_NAME],
	sDeployedAt[MAX_ZONE_NAME]
}

new SpikeStrips[MAX_PINCHOS][Spikes];


public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	new id = verificar_id_vehiculo(vehicleid);
	if (id != -1)
	{
		InfoVehiculo[id][vPaintJob] = paintjobid;
		guardar_int_mysql("vehiculos", "PaintJob", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vPaintJob]);
	}
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	new id = verificar_id_vehiculo(vehicleid);
	if (id != -1)
	{
		new query[128];
		InfoVehiculo[id][vColor_1] = color1;
		InfoVehiculo[id][vColor_2] = color2;
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET Color_1 = '%d', Color_2 = '%d' WHERE ID = '%d'", InfoVehiculo[id][vColor_1], InfoVehiculo[id][vColor_2], InfoVehiculo[id][vID_sql]);
		mysql_tquery(db_samp, query);
	}
	return 1;
}

public OnEnterExitModShop(playerid, enterexit, interiorid)
{
	if (enterexit == 0)
	{
		if (EsteVehEs(playerid, GetPlayerVehicleID(playerid)) > -1)
		{
			ActualizarMods(EsteVehEs(playerid, GetPlayerVehicleID(playerid)));
		}
		SetPlayerInterior(playerid, 0);
	}
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if(!(1 <= GetPlayerInterior(playerid) <= 3))
	{
		new szMessage[260];
		format(szMessage, sizeof szMessage, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) tal vez esté usando hacks de modificaciones de autos (aplicando: %s %s en un %s).", GetNameFormat(playerid), playerid, partName(componentid), partType(GetVehicleComponentType(componentid)), GetVehicleName(vehicleid));
		SendAdminMessage(0xFFFFFFFF, szMessage);
	}
	return 1;
}

//vehicle spawning
public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if (cheat_VehicleSpawning != 0)
	{
		new Float: ac_x, Float: ac_y, Float: ac_z, Float: distance = GetVehicleDistanceFromPoint(vehicleid, new_x, new_y, new_z);
		GetVehiclePos(vehicleid, ac_x, ac_y, ac_z);
		if (distance > 16.0 && ac_z > -70 && distance > uwuVehPos[vehicleid][vp_distance] + ( distance / 2 ))
		{
			GetVehicleZAngle(vehicleid, uwuVehPos[vehicleid][vp_z_angle]);
			SetVehicleZAngle(vehicleid, uwuVehPos[vehicleid][vp_z_angle]);
			MoverVehiclePos(vehicleid, ac_x, ac_y, ac_z );
			if (InfoPersonaje[playerid][pHorasOn] == 0 || InfoPersonaje[playerid][pHorasOn] == 1) { CheatDetected(playerid, "Vehicle Spawning", 2); }
			return 1;
		}
		uwuVehPos[vehicleid][vp_distance] = distance;
	}
	return 1;
}

CheatDetected(playerid, reason[], type)
{
	if (GetPlayerAdmin(playerid, 1) != 0) return 1;
	new gformat[320];
	if (type == 1) //Advertencia
	{
		format(gformat, sizeof gformat, "{DC1005}[AC]{FFFFFF} Se detectó a %s[%d] (%s) de posible '%s'.", InfoPersonaje[playerid][pNombre_Apellido], playerid, InfoCuenta[playerid][jNombre], reason);
		SendAdminMessage(0xFFFFFFFF, gformat);
	}
	else if (type == 2) //Kick
	{
		new Ip[18];
		GetPlayerIp(playerid, Ip, 18);
		format(gformat, sizeof gformat, "{DC1005}[AC]{FFFFFF} %s[%d] (%s) fue expulsado por '%s' - IP: %s", InfoPersonaje[playerid][pNombre_Apellido], playerid, InfoCuenta[playerid][jNombre], reason, Ip);
		SendAdminMessage(0xFFFFFFFF, gformat);
		cheat_kick(playerid, reason);
	}
	return 2;
}

stock cheat_kick(playerid, reason[])
{
	printf("[AC] %s (%s) kickeado [%s]", InfoPersonaje[playerid][pNombre_Apellido], InfoCuenta[playerid][jNombre], reason);
	SendClientMessageEx(playerid, 0x989898FF, "Has sido expulsado por el anticheat, detectado: {F80101}%s", reason);
	new string[185];
	new File: antic_Log = fopen("Anticheat_log.txt", io_append);
	format(string, sizeof string, "%s (%s) expulsado - #%s\r\n", InfoPersonaje[playerid][pNombre_Apellido], InfoCuenta[playerid][jNombre], reason);
	fwrite(antic_Log, string);
	fclose(antic_Log);
	SetTimerEx("TimerKICK", 800, false, "i", playerid);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1)
	{
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
		SetPlayerPosEx(playerid, X, Y+1, Z);
		TogglePlayerControllable(playerid, false);
		ClearAnimations(playerid);
		ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0, 1);
		return 1;
	}
    Seatbelt[playerid] = 0;
    if (veh_gasolina[vehicleid] <= 0) { SetVehicleEngine(vehicleid, playerid); }
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	if (engine == VEHICLE_PARAMS_UNSET) switch(GetVehicleModel(vehicleid))
	{
		case 509, 481, 510: veh_gasolina[vehicleid] = 100, arr_Engine{vehicleid} = 1, SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_ON,lights,alarm,doors,bonnet,boot,objective), arr_Engine{vehicleid} = 1;
		default: SetVehicleParamsEx(vehicleid,VEHICLE_PARAMS_OFF,VEHICLE_PARAMS_OFF,alarm,doors,bonnet,boot,objective), arr_Engine{vehicleid} = 0;
	}
	if (!ispassenger)
	{
		if (cocheocupado(vehicleid))
		{
			new Float: slx,Float: sly,Float: slz;
			GetPlayerPos(playerid, slx, sly, slz);
			SetPlayerPosEx(playerid, slx, sly, slz);
			ClearAnimations(playerid);
			SendPlayerChatMessage(playerid, 0xFFC800FF, "No está permitido el car jacked, fuiste congelado 4 segundos.");
			TogglePlayerControllable(playerid, false);
			SetTimerEx("Descongelar", 4000, 0, "i", playerid);
			return 1;
		}
		new si_no = 0;
		Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
		{
		    if (InfoVehiculo[id][vNegocio] != 0)
		    {
				if (llaves_negocio(playerid, vehicleid)) si_no = 1;
		    }
		    else if (InfoVehiculo[id][vTrabajo] != 0)
		    {
				if (llaves_trabajo(playerid, vehicleid)) si_no = 1;
		    }
		    else
		    {
				switch (InfoVehiculo[id][vTipo])
				{
					case 1..50: //facciones
					{
						if (llaves_faccion(playerid, vehicleid)) si_no = 1;
					}
					case 200: //vip
					{
						if (llaves_vip(playerid, vehicleid)) si_no = 1;
					}
					case 600: //rentable
					{
						si_no = 1;
					}
					default: //usuarios
					{
						si_no = 1;
					}
				}
			}
		}
		//función
		if (si_no != 1)
		{
			if (playerTextdraw[playerid] == false)
			{
				playerVehicleTextdraw[playerid] = CreateDynamic3DTextLabel("No tienes las llaves de este vehiculo.", 0xFFFFFFFF, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, vehicleid, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerid);
				SetTimerEx("OnVehicleTextdraw", 4000, false, "i", playerid);
				playerTextdraw[playerid] = true;
			}
			new Float: slx,Float: sly,Float: slz;
			GetPlayerPos(playerid, slx, sly, slz);
			SetPlayerPosEx(playerid, slx, sly, slz);
			return ClearAnimations(playerid);
		}
	}
    else
    {
		if (!IsPlayerInRangeOfVehicle(playerid, vehicleid, 7.5) || LockStatus[vehicleid] != 0)// G-bugging fix
		{
			if (playerTextdraw[playerid] == false)
			{
				playerVehicleTextdraw[playerid] = CreateDynamic3DTextLabel("Este vehículo se encuentra bloqueado.", 0xFFFFFFFF, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, vehicleid, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerid);
				SetTimerEx("OnVehicleTextdraw", 4000, false, "i", playerid);

				playerTextdraw[playerid] = true;
			}
			new Float: slx,Float: sly,Float: slz;
			GetPlayerPos(playerid, slx, sly, slz);
			SetPlayerPosEx(playerid, slx, sly, slz);
			return ClearAnimations(playerid);
		}
	}
	return 1;
}

funcion Descongelar(playerid) return TogglePlayerControllable(playerid, true);

forward OnVehicleTextdraw(playerid);
public OnVehicleTextdraw(playerid)
{
	if (IsValidDynamic3DTextLabel(playerVehicleTextdraw[playerid]))
	{
		DestroyDynamic3DTextLabel(playerVehicleTextdraw[playerid]);
		playerVehicleTextdraw[playerid] = Text3D:INVALID_3DTEXT_ID;
	}
	playerTextdraw[playerid] = false;
	return 1;
}

funcion uwu_tp_job(playerid, job[])
{
	if (cheat_TPgranjero != 0)
	{
		new string[256];
		format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) [%s] fue expulsado, razón: posible tp %s", GetNameFormat(playerid), playerid, InfoCuenta[playerid][jNombre], job);
		SendAdminMessage(0xFFFFFFFF, string);
		SetTimerEx("TimerKICK", 2000, 0, "d", playerid);
	}
	return 1;
}

IsTallerIn(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 10.0, 1981.1217, -2061.6235, 13.4121)) return 1;
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1471.9691, -1495.3605, 13.6370)) return 2;
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 2354.3213, -1369.8083, 24.1138)) return 3;
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1830.2946, -1401.7294, 13.4792)) return 4;
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1004.9277, -1439.2111, 13.6102)) return 5;
	return 0;
}

Tienda_247(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid,5.0,-1833.8270,62.3936,1055.1891)) { return 1; } //intaero
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-22.3260,-138.6221,1003.5469)) { return 1; }
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-25.6448,-56.6718,1003.5469)) { return 1; }
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-29.3554,-28.8020,1003.5573)) { return 1; }
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-28.7605,-185.1333,1003.5469)) { return 1; } //LV 1er 24-7
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-10.3085,-178.2465,1003.5469)) { return 1; } // LV 1er 24-7 >
	else if (IsPlayerInRangeOfPoint(playerid,5.0,2.3437,-29.0118,1003.5494)) { return 1; } //LV 2do 24-7
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-28.0818,-89.9434,1003.5469)) { return 1; } //LV 3er 24-7
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-29.1318,-184.7204,1003.5469)) { return 1; } //LV 3er 24-7
	else if (IsPlayerInRangeOfPoint(playerid,5.0,-25.7885,-183.2835,1003.5469)) { return 1; } //LV 3er 24-7
	else if (IsPlayerInRangeOfPoint(playerid,3.0,664.8079,-568.7150,16.3433)) { return 1; }
	return 0;
}

PlayerPlaySoundEx(soundid, Float:x, Float:y, Float:z)
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid))
	{
		if (IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
			PlayerPlaySound(playerid, soundid, x, y, z);
	}
	return 1;
}

partType(type)
{
	new name[64];
	switch(type){
	    case 0: name = "Alerón";
        case 1: name = "Capó";
        case 2: name = "Techo";
        case 3: name = "Lados";
        case 4: name = "Lamps";
        case 5: name = "Nitro";
        case 6: name = "Escape";
        case 7: name = "Ruedas";
        case 8: name = "Stereo";
        case 9: name = "Hidráulica";
        case 10: name = "Parachoque D.";
        case 11: name = "Parachoque T.";
        case 12: name = "Ventilacion Izq.";
        case 13: name = "Ventilacion Der.";
        default: name = "Desconocida";
	}
	return name;
}

partName(part){

	new
		name[24];

	switch(part - 1000) {
		case 0:	name = "Pro";
		case 1: name = "Win";
		case 2: name = "Drag";
		case 3: name = "Alpha";
		case 4: name = "Champ Scoop";
		case 5: name = "Fury Scoop";
		case 6: name = "Roof Scoop";
		case 7: name = "Sideskirt";
		case 8: name = "2x";
		case 9: name = "5x";
		case 10: name = "10x";
		case 11: name = "Race Scoop";
		case 12: name = "Worx Scoop";
		case 13: name = "Round Fog";
		case 14: name = "Champ";
		case 15: name = "Race";
		case 16: name = "Worx";
		case 17: name = "Sideskirt";
		case 18: name = "Upswept";
		case 19: name = "Twin";
		case 20: name = "Large";
		case 21: name = "Medium";
		case 22: name = "Small";
		case 23: name = "Fury";
		case 24: name = "Square Fog";
		case 26: name = "Alien";
		case 27: name = "Alien";
		case 28: name = "Alien";
		case 29: name = "X-Flow";
		case 30: name = "X-Flow";
		case 31: name = "X-Flow";
		case 32: name = "Alien Roof Vent";
		case 33: name = "X-Flow Roof Vent";
		case 34: name = "Alien";
		case 35: name = "X-Flow Roof Vent";
		case 36: name = "Alien";
		case 37: name = "X-Flow";
		case 38: name = "Alien Roof Vent";
		case 39: name = "X-Flow";
		case 40: name = "Alien";
		case 41: name = "X-Flow";
		case 42: name = "Chrome";
		case 43: name = "Slamin";
		case 44: name = "Chrome";
		case 45: name = "X-Flow";
		case 46: name = "Alien";
		case 47: name = "Alien";
		case 48: name = "X-Flow";
		case 49: name = "Alien";
		case 50: name = "X-Flow";
		case 51: name = "Alien";
		case 52: name = "X-Flow";
		case 53: name = "X-Flow";
		case 54: name = "Alien";
		case 55: name = "Alien";
		case 56: name = "Alien";
		case 57: name = "X-Flow";
		case 58: name = "Alien";
		case 59: name = "X-Flow";
		case 60: name = "X-Flow";
		case 61: name = "X-Flow";
		case 62: name = "Alien";
		case 63: name = "X-Flow";
		case 64: name = "Alien";
		case 65: name = "Alien";
		case 66: name = "X-Flow";
		case 67: name = "Alien";
		case 68: name = "X-Flow";
		case 69: name = "Alien";
		case 70: name = "X-Flow";
		case 71: name = "Alien";
		case 72: name = "X-Flow";
		case 88: name = "Alien";
		case 89: name = "X-Flow";
		case 90: name = "Alien";
		case 91: name = "X-Flow";
		case 92: name = "Alien";
		case 93: name = "X-Flow";
		case 94: name = "Alien";
		case 95: name = "X-Flow";
		case 99: name = "Chrome";
		case 100: name = "Chrome Grill";
		case 101: name = "Chrome Flames";
		case 102: name = "Chrome Strip";
		case 103: name = "Convertible";
		case 104: name = "Chrome";
		case 105: name = "Slamin";
		case 106: name = "Chrome Arches";
		case 107: name = "Chrome Strip";
		case 108: name = "Chrome Strip";
		case 109: name = "Chrome";
		case 110: name = "Slamin";
		case 113: name = "Chrome";
		case 114: name = "Slamin";
		case 115: name = "Chrome";
		case 116: name = "Slamin";
		case 117: name = "Chrome";
		case 118: name = "Chrome Trim";
		case 119: name = "Wheelcovers";
		case 120: name = "Chrome Trim";
		case 121: name = "Wheelcovers";
		case 122: name = "Chrome Flames";
		case 123: name = "Bullbar Chrome Bars";
		case 124: name = "Chrome Arches";
		case 125: name = "Bullbar Chrome Lights";
		case 126: name = "Chrome";
		case 127: name = "Slamin";
		case 128: name = "Vinyl Hardtop";
		case 129: name = "Chrome";
		case 130: name = "Hardtop";
		case 131: name = "Softtop";
		case 132: name = "Slamin";
		case 133: name = "Chrome Strip";
		case 134: name = "Chrome Strip";
		case 135: name = "Slamin";
		case 136: name = "Chrome";
		case 137: name = "Chrome Strip";
		case 138: name = "Alien";
		case 139: name = "X-Flow";
		case 140: name = "X-Flow";
		case 141: name = "Alien";
		case 142: name = "Left Oval Vents";
		case 143: name = "Right Oval Vents";
		case 144: name = "Left Square Vents";
		case 145: name = "Right Square Vents";
		case 146: name = "X-Flow";
		case 147: name = "Alien";
		case 148: name = "X-Flow";
		case 149: name = "Alien";
		case 150: name = "Alien";
		case 151: name = "X-Flow";
		case 152: name = "X-Flow";
		case 153: name = "Alien";
		case 154: name = "Alien";
		case 155: name = "Alien";
		case 156: name = "X-Flow";
		case 157: name = "X-Flow";
		case 158: name = "X-Flow";
		case 159: name = "Alien";
		case 160: name = "Alien";
		case 161: name = "X-Flow";
		case 162: name = "Alien";
		case 163: name = "X-Flow";
		case 164: name = "Alien";
		case 165: name = "X-Flow";
		case 166: name = "Alien";
		case 167: name = "X-Flow";
		case 168: name = "Alien";
		case 169: name = "Alien";
		case 170: name = "X-Flow";
		case 171: name = "Alien";
		case 172: name = "X-Flow";
		case 173: name = "X-Flow";
		case 174: name = "Chrome";
		case 175: name = "Slamin";
		case 176: name = "Chrome";
		case 177: name = "Slamin";
		case 178: name = "Slamin";
		case 179: name = "Chrome";
		case 180: name = "Chrome";
		case 181: name = "Slamin";
		case 182: name = "Chrome";
		case 183: name = "Slamin";
		case 184: name = "Chrome";
		case 185: name = "Slamin";
		case 186: name = "Slamin";
		case 187: name = "Chrome";
		case 188: name = "Slamin";
		case 189: name = "Chrome";
		case 190: name = "Slamin";
		case 191: name = "Chrome";
		case 192: name = "Chrome";
		case 193: name = "Slamin";
	}
	return name;
}

//
public OnPlayerRequestClass(playerid, classid)
{
    if (IsPlayerNPC(playerid)) return 1;
	if (state_on[playerid] == 0)
	{
		SetPlayerColor(playerid, 0x00000000); // color logeo
		state_on[playerid] = 1;
		SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0) ;
		SpawnPlayer(playerid);
		ClearChat(playerid);
	}
    return 1;
}
new bool:Abierto[MAX_PLAYERS];
new bool:InventarioAbierto[MAX_PLAYERS];


//
public OnPlayerConnect(playerid)
{
    if (IsPlayerNPC(playerid)) return 1;
	conectado[playerid] = 0;
	EnLogin[playerid] = 0;
	InfoTextShowing[playerid] = 0;

	new playerIP[19];
	GetPlayerIp(playerid, playerIP, sizeof playerIP);
	
	Abierto[playerid] = false; 
	InventarioAbierto[playerid] = false;

	gCefReady[playerid] = false;
	gCefInvEstado[playerid] = 0;

	if (CheckBan(playerIP))
	{
		new query[160];
		new Cache:result;
		mysql_format(db_samp, query, sizeof query, "SELECT * FROM ips WHERE IP = '%e'", playerIP);
		result = mysql_query(db_samp, query);
		new admin[24], razon[256], fecha[256];
		rebel_string(0, "Admin", admin, 24);
		rebel_string(0, "Razon", razon, 256);
		rebel_string(0, "Fecha", fecha, 256);
	    SendClientMessageEx(playerid, COLOR_YELLOW, "Lo sentimos, pero tu IP se encuentra bloqueada en nuestra base de datos.");
		SendClientMessageEx(playerid, COLOR_YELLOW, "Razón del bloqueo: %s | Admin: %s | Fecha: %s", razon, admin, fecha);
		SendClientMessageEx(playerid, COLOR_YELLOW, "Si crees que esto es un error, apela en nuestro Discord: https://discord.gg/YsEN5q5h5t)");
		SetTimerEx("TimerKICK", 1000, false, "d", playerid);
		cache_delete(result);
		return 1;
 	}

	// contador de usuarios
	state_on[playerid] = 0;
    reset_InfoCuenta(playerid);         // cuentas
    reset_InfoPersonaje(playerid);      // personajes
	CheckPlayerIP(playerid);            // sistema de multicuenta por IP
	NotificationsConnect(playerid);

	if (cheat_IPS != 0)
	{
		KickIPMultiples(playerid);
	}

	PersonajeSeleccionado[playerid] = 0;
	resetPlayerVariables(playerid);     // limpieza de variables 1
	OnPlayerCleanVariables(playerid);	// limpieza de variables 2
	MueblesRemoveForPlayer(playerid);   // remueve muebles default
	OnPlayerTextDraw(playerid);         // PlayerTextDraw
	SyncPlayerTime(playerid);           // tiempo real
	ResetPlayerHeridas(playerid);       // limpieza de heridas

    new string[40];
    new randomName[17];
    GenerateRandomName(randomName);
    format(string, sizeof(string), "%s", randomName);
    SetPlayerName(playerid, string);

	SetPlayerColor(playerid, 0x00000000); // color logeo
	DesconocidoConnect(playerid);
	Maps_Remove(playerid);
	return 1;
}

stock GenerateRandomName(name[], size = 17) {
    new charset[] = "AbCdEFgHiJklMNoPqRsTuVwXyZ";
    for (new i = 0; i < size - 1; i++) { name[i] = charset[random(sizeof(charset) - 1)]; }
    name[size - 1] = '\0';
}

public OnPlayerDisconnect(playerid, reason)
{
	if (InfoPersonaje[playerid][pBaneo] != 0) return 1; // new 11/01/2020
	if (usuario_registro[playerid] != 2) return 1; // new 11/01/2020
	new gformat[256];

	//última conexión & posiciones
	GetPlayerPos(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ]);
	GetPlayerFacingAngle(playerid, InfoPersonaje[playerid][pPosicionR]);
	InfoPersonaje[playerid][pInterior] = GetPlayerInterior(playerid);
	InfoPersonaje[playerid][pVirtualWorld] = GetPlayerVirtualWorld(playerid);
	InfoPersonaje[playerid][pUltimaConexion] = FechaHoy();
	InfoCuenta[playerid][jUltimaConexion] = FechaHoy();

	KillTimer(VisitaTimer[playerid]); //cmd_visitar
	YaAviso[playerid] = 0;
    pDrunkLevelLast[playerid] = 0;

	DestroyDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]);
	InfoPersonaje[playerid][pNameTag] = Text3D:INVALID_3DTEXT_ID;

	//estéreo
	if (GetPVarType(playerid, "AreaVehPos"))
	{
		if (GetPVarType(playerid, "AreaVehMus"))
		{
			foreach(new playerid2: Player) if (IsPlayerInDynamicArea(playerid2, GetPVarInt(playerid, "AreaVehMus")))
			{
				PararMVeh(playerid2);
                SendPlayerChatMessage(playerid2, COLOR_YELLOW, "* El propietario del vehículo con música, desconectó del servidor.");
			}
		}
	}
	//boombox
	if (InfoBoombox[playerid][BB_obj])
	{
		if (IsValidDynamicObject(InfoBoombox[playerid][BB_obj])) DestroyDynamicObject(InfoBoombox[playerid][BB_obj]);
		InfoBoombox[playerid][BB_obj] = 0;
		if (IsValidDynamic3DTextLabel(InfoBoombox[playerid][BB_label]))
		{
			DestroyDynamic3DTextLabel(InfoBoombox[playerid][BB_label]);
			InfoBoombox[playerid][BB_label] = Text3D:INVALID_3DTEXT_ID;
		}
		tirar_objeto(51, 1, InfoBoombox[playerid][BB_x], InfoBoombox[playerid][BB_y], InfoBoombox[playerid][BB_z], InfoBoombox[playerid][BB_vw], InfoBoombox[playerid][BB_int], 1);
		if (InfoBoombox[playerid][BB_area])
		{
			foreach(Player, playerid2) if (IsPlayerInDynamicArea(playerid2, InfoBoombox[playerid][BB_area]) && TipoAudio[playerid2] == 1 && InfoPersonaje[playerid2][pTogMusic] == 1)
			{
				StopAudioStreamForPlayer(playerid2);
				SendPlayerChatMessage(playerid2, COLOR_YELLOW, "* El dueño del boombox ha salido del servidor.");
				Streamer_Update(playerid2);
				TipoAudio[playerid2] = 0;
			}
		}
	}

	//textdraw's
	PlayerTextDrawDestroy(playerid, draw_money[playerid]);
	Loop(x, 9, 0) { PlayerTextDrawDestroy(playerid, p_tdVelocimetro[playerid][x]); }
	Loop(x, 7, 0) { PlayerTextDrawDestroy(playerid, pCocheVS[playerid][x]); }
	Loop(x, 3, 0) { PlayerTextDrawDestroy(playerid, p_tdMuerte[playerid][x]); }


	//llamadas gc
	KillTimer(ToqueLlamadaTimer[playerid]); // comando llamar
	if (PersonaEnLlamada[playerid] != -1) KillTimer(ToqueLlamadaTimer[PersonaEnLlamada[playerid]]); // comando llamar
	if (PersonaEnLlamada[playerid] != -1)
	{
		if (EnLlamada[PersonaEnLlamada[playerid]] == 3)
		{
			SendPlayerChatMessage(PersonaEnLlamada[playerid], COLOR_LIGHTRED, "Coste de la llamada: 1$");
			GivePlayerCash(PersonaEnLlamada[playerid], -1, "costo de llamada");
		}
	}
	for(new i=0; i<MAX_PLAYERS; i++) { if(PersonaEnLlamada[i] == playerid){SendPlayerChatMessage(i, COLOR_LIGHTRED, "Se ha cortado la línea..."); EnLlamada[i] = 0; PersonaEnLlamada[i] = -1; break;} }

	//desconectar esposado
	if (GetPVarInt(playerid, "PlayerCuffed") == 1 && reason != 2)
	{
		new alertaxd[190];
		format(alertaxd, sizeof alertaxd, "*** %s [%d] desconectó del servidor con las esposas puestas.", InfoPersonaje[playerid][pNombre_Apellido], playerid);
		SendFaccionMessage(1, 0x1EB121FF, alertaxd);
		SendFaccionMessage(2, 0x1EB121FF, alertaxd);
	}

	//info desconexión
	static const reasonQuit[3][32] = {"Crash", "Quit (/Q)", "Kick/Ban"};
	format(gformat, sizeof gformat, "{player:%d} ha salido del servidor. (%s)", playerid, reasonQuit[reason]);
	ProxDetector(20.0, playerid, gformat, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);

	if (Spectate[playerid] != 999)
	{
		InfoPersonaje[playerid][pPosicionX] = GetPVarFloat(playerid, "SpecPosX");
		InfoPersonaje[playerid][pPosicionY] = GetPVarFloat(playerid, "SpecPosY");
		InfoPersonaje[playerid][pPosicionZ] = GetPVarFloat(playerid, "SpecPosZ");
        InfoPersonaje[playerid][pInterior] = GetPVarInt(playerid, "SpecInt");
		InfoPersonaje[playerid][pVirtualWorld] = GetPVarInt(playerid, "SpecVW");
	    GettingSpectated[Spectate[playerid]] = 999;
	    Spectate[playerid] = 999;
	}

	//reporte activo
	Loop(x, MAX_REPORTS, 0) if (Reports[x][ReportFrom] == playerid)
	{
		Reports[x][ReportFrom] = 999;
		Reports[x][BeingUsed] = 0;
		Reports[x][TimeToExpire] = 0;
	}

	//actualiza sql positions
	new query[2056];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET PosicionX = '%f', PosicionY = '%f', PosicionZ = '%f', PosicionR = '%f', Vida = '%f', Chaleco = '%f', Interior = '%d', VirtualWorld = '%d', \
	UltimaConexion = '%e', TiempoSancion = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE Nombre_Apellido = '%e'",
	InfoPersonaje[playerid][pPosicionX],
	InfoPersonaje[playerid][pPosicionY],
	InfoPersonaje[playerid][pPosicionZ],
	InfoPersonaje[playerid][pPosicionR],
	InfoPersonaje[playerid][pVida],
	InfoPersonaje[playerid][pChaleco],
	InfoPersonaje[playerid][pInterior],
	InfoPersonaje[playerid][pVirtualWorld],
	InfoPersonaje[playerid][pUltimaConexion],
	InfoPersonaje[playerid][pTiempoSancion],
	InfoPersonaje[playerid][pManoDerecha],
	InfoPersonaje[playerid][pManoDerechaCant],
	InfoPersonaje[playerid][pManoIzquierda],
	InfoPersonaje[playerid][pManoIzquierdaCant],
	InfoPersonaje[playerid][pNombre_Apellido]);
	mysql_tquery(db_samp, query);

	guardar_string_mysql("cuentas", "UltimaConexion", InfoCuenta[playerid][jID], InfoCuenta[playerid][jUltimaConexion]);

	SecuenciaVehiculos(playerid);

	DeletePVar(playerid, "CPJ_STEP_ONE");
	DeletePVar(playerid, "CPJ_STEP_TWO");
	DeletePVar(playerid, "CPJ_STEP_THREE");
	DeletePVar(playerid, "SEXO_PJ");
	DeletePVar(playerid, "EDAD_PJ");
	DeletePVar(playerid, "PESO_PJ");
 	return 1;
}

forward IntentarPuenteTimer(playerid);
public IntentarPuenteTimer(playerid)
{
	IntentarPuente[playerid] = 0;
	Notification_Show(playerid, "Puedes usar de nuevo el comando /puente.", 3000);
}

SetPlayerSpawn(playerid)
{
	SetPlayerTeam(playerid, 1);
	if (usuario_registro[playerid] == 0)
	{
		SetTimerEx("FreezePlayer", 1000, false, "i", playerid);
		state_on[playerid] = 2;
		//camera
		TogglePlayerSpectating(playerid, true);
		SetCameraIntro(playerid);
		return 1;
	}
	else
	{
		SetPlayerColor(playerid, 0xFFFFFF00);
		if (GetPVarInt(playerid, "SpecOff" ) == 1 )
		{
			SetPlayerPosEx(playerid, GetPVarFloat(playerid, "SpecPosX"), GetPVarFloat(playerid, "SpecPosY"), GetPVarFloat(playerid, "SpecPosZ"));
			SetPlayerInterior(playerid, GetPVarInt(playerid, "SpecInt"));
			SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "SpecVW"));
			SetPVarInt(playerid, "SpecOff", 0 );
			SetPVarInt(playerid, "SpecState", -1 );
			return 1;
		}
		switch (InfoPersonaje[playerid][pSancionado])
		{
		    case 1: // jail ooc
			{
			    InfoPersonaje[playerid][pTogTelefono] = 0;
				SetPlayerPosEx(playerid, 436.4944, 2547.5933, 16.3020);
			    SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, playerid+1);
				SetPlayerSkin(playerid, 50);
				SendClientMessageEx(playerid, COLOR_YELLOW, "Sigues con sanción administrativa por %s, motivo: %s.", InfoPersonaje[playerid][pRazonSancion], InfoPersonaje[playerid][pBySancion]);
				SendClientMessageEx(playerid, COLOR_YELLOW, "Tiempo restante de la sanción: %s.", Segundos_tiempo(InfoPersonaje[playerid][pTiempoSancion]));
				TogglePlayerControllable(playerid, false);
				return 1;
			}
		    case 2: // prisión federal
			{
			    InfoPersonaje[playerid][pTogTelefono] = 0;
				SendClientMessageEx(playerid, COLOR_YELLOW, "Sigues en prisión federal, tiempo restante: %s.", Segundos_tiempo(InfoPersonaje[playerid][pTiempoSancion]));
				return 1;
			}
		}
		if (GetPVarInt(playerid, "desbug_muerte") == 1)
		{
			SetPosEx(playerid, PosSpawnBug[playerid][0], PosSpawnBug[playerid][1], PosSpawnBug[playerid][2], PosSpawnBug[playerid][3], PosIntBug[playerid], PosVwBug[playerid], 1);
			dar_vida(playerid, 25); dar_chaleco(playerid, 0);
			SetPVarInt(playerid, "EstaCrack", 1);
			estado_xdxdxd(playerid, 2);
			SetCameraBehindPlayer(playerid);
			DeletePVar(playerid, "desbug_muerte");
			return 1;
		}
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if (IsValidDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]))
	{
		DestroyDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]);
		InfoPersonaje[playerid][pNameTag] = Text3D:INVALID_3DTEXT_ID;
	}
	SetPlayerColor(playerid, 0xFFFFFF00);
	GetPlayerPos(playerid, PosSpawnBug[playerid][0], PosSpawnBug[playerid][1], PosSpawnBug[playerid][2]);
	GetPlayerFacingAngle(playerid, PosSpawnBug[playerid][3]);
	PosVwBug[playerid] = GetPlayerVirtualWorld(playerid);
	PosIntBug[playerid] = GetPlayerInterior(playerid);
	SetPVarInt(playerid, "desbug_muerte", 1);
	return 1;
}

SetCameraIntro(playerid)
{
	InterpolateCameraPos(playerid, 1573.397094, -1375.661132, 264.182373, 1705.742675, -1484.626953, 300.826171, 15000);
	InterpolateCameraLookAt(playerid, 1570.846435, -1372.473022, 267.068664, 1701.697021, -1481.814697, 299.975189, 15000);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, playerid);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	PlayerWeather[playerid] = ServerWeather;
	if (IsPlayerNPC(playerid)) return 1;
	if (state_on[playerid] == 1)
	{
		SetPlayerColor(playerid, 0x00000000); // color logeo
		ClearChat(playerid);
		state_on[playerid] = 2;

		// cámara de inicio
		TogglePlayerSpectating(playerid, true);
		SetCameraIntro(playerid);
		SyncPlayerTime(playerid);
		SetLogin(playerid, 1);
		return 1;
	}
	if (usuario_registro[playerid] == 0)
	{
	    SendPlayerChatMessage(playerid, COLOR_GREY, "No has ingresado correctamente al servidor!");
        Kick(playerid);
        return 1;
 	}
	if (IsValidDynamicActor(ActorLogin[playerid])) DestroyDynamicActor(ActorLogin[playerid]);
	SetPlayerSpawn(playerid);
	OnDuty[playerid] = 0;
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
	SyncPlayerTime(playerid);

	if (InfoPersonaje[playerid][pJobSkin] != 0) SetPlayerSkin(playerid, InfoPersonaje[playerid][pJobSkin]);
	else SetPlayerSkin(playerid, InfoPersonaje[playerid][pSkin]);

	//toys
	Loop(listitem, 7, 0) if (InfoPersonaje[playerid][ptColocado][listitem] != 0)
	{
		SetPlayerAttachedObject(playerid, listitem, InfoPersonaje[playerid][ptModelo][listitem], InfoPersonaje[playerid][ptHueso][listitem], InfoPersonaje[playerid][ptPosX][listitem], InfoPersonaje[playerid][ptPosY][listitem], InfoPersonaje[playerid][ptPosZ][listitem],
		InfoPersonaje[playerid][ptRotX][listitem], InfoPersonaje[playerid][ptRotY][listitem], InfoPersonaje[playerid][ptRotZ][listitem], InfoPersonaje[playerid][ptScaleX][listitem], InfoPersonaje[playerid][ptScaleY][listitem], InfoPersonaje[playerid][ptScaleZ][listitem],
		SetColorToy(InfoPersonaje[playerid][ptColor][listitem]));
	}

	//armas
	new ManoDer = InfoPersonaje[playerid][pManoDerecha], ManoIzq = InfoPersonaje[playerid][pManoIzquierda], Espalda = InfoPersonaje[playerid][pEspalda];
	if (ManoDer > 0)
	{
		PonerObjeto(playerid, 1, ManoDer);
		if (InfoInventario[ManoDer][IDArma] > 0)
		{
			GivePlayerWeapon(playerid, InfoInventario[ManoDer][IDArma], InfoPersonaje[playerid][pManoDerechaCant]);
		}
	}
	if (ManoIzq > 0) { PonerObjeto(playerid, 2, ManoIzq); }
	if (Espalda > 0) { PonerObjeto(playerid, 3, Espalda); }
	return 1;
}

forward CargarCuenta(playerid);
public CargarCuenta(playerid)
{
	if (InfoPersonaje[playerid][pBaneo] != 0) return MuestraBloqueoPJ(playerid);
	ShowLoadScreen(playerid, 5000);
	TogglePlayerSpectating(playerid, false);
	StopAudioStreamForPlayer(playerid);

	CEF_CrearInventario(playerid);
	ClearChat(playerid);
	generar_codigo(playerid);
	SetPlayerName(playerid, InfoPersonaje[playerid][pCodigo]);
	new ex_ip[18];
	GetPlayerIp(playerid, ex_ip, sizeof ex_ip);
	ResetPlayerMoney(playerid);
	usuario_registro[playerid] = 2;
	alm(InfoCuenta[playerid][jIP], ex_ip);
	guardar_string_mysql("cuentas", "IP", InfoCuenta[playerid][jID], ex_ip);
	state_on[playerid] = 3;
	
	if (VehicleCount(playerid) != 0) Notification_Show(playerid, "Utiliza el comando '/llaves' para sacar tus vehículos ocultos.", 5000);
	
	
	if (InfoPersonaje[playerid][pMuerto] != 0) 
	{ 
		SetPVarInt(playerid, "EstaCrack", 1); 
		estado_xdxdxd(playerid, InfoPersonaje[playerid][pMuerto]); 
		InfoPersonaje[playerid][pEstado] = 2; 
	}

	if (InfoPersonaje[playerid][pEstado] == 0)
	{
		InfoPersonaje[playerid][pEstado] = 0;
	}
	
	
	if (InfoPersonaje[playerid][pPosicionX] == 0.0 && InfoPersonaje[playerid][pPosicionY] == 0.0 && InfoPersonaje[playerid][pPosicionZ] == 0.0)
	{
		InfoPersonaje[playerid][pPosicionX] = 2105.0334;
		InfoPersonaje[playerid][pPosicionY] = -1473.9088;
		InfoPersonaje[playerid][pPosicionZ] = 24.1237;
		KillEMSQueue(playerid);
		timer_herido[playerid] = 0;
		dar_vida(playerid, 100);
		ShowInfoForPlayer(playerid, "Has sido desbugeado.", 5000);
	}
	SetPlayerPosEx(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ]);
	SetPlayerFacingAngle(playerid, InfoPersonaje[playerid][pPosicionR]);
	SetPlayerInterior(playerid, InfoPersonaje[playerid][pInterior]);
	SetPlayerVirtualWorld(playerid, InfoPersonaje[playerid][pVirtualWorld]);
	Streamer_UpdateEx(playerid, InfoPersonaje[playerid][pPosicionX], InfoPersonaje[playerid][pPosicionY], InfoPersonaje[playerid][pPosicionZ]);
	SetCameraBehindPlayer(playerid);
	SetPlayerHealth(playerid, InfoPersonaje[playerid][pVida]);
	SetPlayerArmour(playerid, InfoPersonaje[playerid][pChaleco]);
	if (InfoPersonaje[playerid][pHorasOn] == 0) SetPlayerScore(playerid, 1);
	else SetPlayerScore(playerid, InfoPersonaje[playerid][pHorasOn]);
 	SetPlayerFightingStyle(playerid, InfoPersonaje[playerid][pEstiloPelea]);
	if (InfoPersonaje[playerid][pEstrellas] >= 2) SetPlayerWantedLevel(playerid, InfoPersonaje[playerid][pEstrellas]);
	SyncPlayerTime(playerid);
	SetPlayerColor(playerid, 0xFFFFFF00);
	PreloadAnimations(playerid);
	ReiniciarSecuencia(playerid);

	if(InfoPersonaje[playerid][pEstado] == 1)//inconsciente
	{
		PonerInconsciente(playerid);
	}


	revisar_viapiuwu(playerid); //revisa vip
	if (InfoPersonaje[playerid][pJobSkin] != 0) SetPlayerSkin(playerid, InfoPersonaje[playerid][pJobSkin]), SendPlayerChatMessage(playerid, COLOR_GENERAL, "Llevas puesto un skin de trabajo/faccion.");
	else SetPlayerSkin(playerid, InfoPersonaje[playerid][pSkin]);

	for(new i; i < 3; i++){
		PlayerTextDrawShow(playerid, logo_gtafive[playerid][i]);
	}

	Streamer_Update(playerid);
	SetPVarInt(playerid, "LoadingObjects", 1);
	SetTimerEx("HideLoadingInterior", 3000, false, "i", playerid);

	//casas
	Loop(id, totalcasas, 1) if (InfoCasa[id][cTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoCasa[id][cPropietario], true) == 0)
	{
		new k = gettime();
		k += 1296000;
		InfoCasa[id][cTiempoDisponible] = k;
		guardar_int_mysql("casas", "TiempoDisponible", InfoCasa[id][cID_sql], InfoCasa[id][cTiempoDisponible]);
	}

	//negocios
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nTipo] != 0 && strcmp(InfoPersonaje[playerid][pNombre_Apellido], InfoNegocio[id][nPropietario], true) == 0)
	{
		new k = gettime();
		k += 1296000;
		InfoNegocio[id][nTiempoDisponible] = k;
		guardar_int_mysql("negocios", "TiempoDisponible", InfoNegocio[id][nID_sql], InfoNegocio[id][nTiempoDisponible]);
	}
	return 1;
}

forward revisar_viapiuwu(playerid);
public revisar_viapiuwu(playerid)
{
	new year, month, day, query[280];
	getdate(year, month, day);
	if (InfoCuenta[playerid][jVIP] == 0)
	{
		InfoCuenta[playerid][jExpira] = -1;
		guardar_int_mysql("cuentas", "Expira", InfoCuenta[playerid][jID], -1);
	}
	else
	{
		if (InfoCuenta[playerid][jExpira] < gettime())
		{
			InfoCuenta[playerid][jExpira] = -1;
			InfoCuenta[playerid][jVIP] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET VIP = 0, Expira = -1 WHERE ID = '%d'", InfoCuenta[playerid][jID]);
			mysql_tquery(db_samp, query);
			SetPlayerColor(playerid, 0xFFFFFF00);
			return 1;
		}
	}
	return 1;
}

Log(const sz_fileName[], const sz_input[]) {

	new
		sz_logEntry[156],
		i_dateTime[2][3],
		File: fileGformat = fopen(sz_fileName, io_append);

	gettime(i_dateTime[0][0], i_dateTime[0][1], i_dateTime[0][2]);
	getdate(i_dateTime[1][0], i_dateTime[1][1], i_dateTime[1][2]);

	format(sz_logEntry, sizeof(sz_logEntry), "[%i/%i/%i - %i:%i:%i] %s\r\n", i_dateTime[1][0], i_dateTime[1][1], i_dateTime[1][2], i_dateTime[0][0], i_dateTime[0][1], i_dateTime[0][2], sz_input);
	fwrite(fileGformat, sz_logEntry);
	return fclose(fileGformat);
}

//
public OnPlayerEnterCheckpoint(playerid)
{
	if (!IsPlayerConnectedEx(playerid)) return 1;
	PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
	if(GetPVarInt(playerid, "EnCheckPoint") == 280){ // carga PD
		DeletePVar(playerid, "EnCheckPoint");
	}
	if (GetPVarInt(playerid,"TrackCar") != 0)
	{
	    DisablePlayerCheckpoint(playerid);
		DeletePVar(playerid, "TrackCar");
		return 1;
	}
	DisablePlayerCheckpoint(playerid);
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    if (IsPlayerNPC(playerid)) return 1;
	if (newstate <= 0 || newstate > 6)
	    for (new i = 0; i < MAX_SYNC_TYPES; ++i)
	        SetSyncTime (playerid, i);
	//vehicle teleport
	if (oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)
	{
		if (cheat_Vehicle1teleport != 0)
		{
			if (GetTickCount() - CarTick[playerid] < 300) CheatDetected(playerid, "Vehicle teleport (type 1)", 2);
			CarTick[playerid] = GetTickCount();
		}
	}
	//
	new string[256], engine, lights, alarm, doors, bonnet, boot, objective, vehicleid = GetPlayerVehicleID(playerid);
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	//spec
	if (GettingSpectated[playerid] != 999)
	{
	    new spectator = GettingSpectated[playerid];
	    if(!IsPlayerConnected(spectator))
	    {
	        GettingSpectated[playerid] = 999;
	        Spectate[spectator] = 999;
		}
		if (newstate == PLAYER_STATE_DRIVER && GetPlayerAdmin(playerid, 1) == 1 || newstate == PLAYER_STATE_PASSENGER && GetPlayerAdmin(playerid, 1) == 1)
		{
	        TogglePlayerSpectating(spectator, true);
			new carid = GetPlayerVehicleID( playerid );
			PlayerSpectateVehicle( spectator, carid );
			SetPVarInt(spectator, "SpecState", newstate);
	    }
	    else if(newstate == PLAYER_STATE_ONFOOT && GetPlayerAdmin(playerid, 1) == 1)
	    {
	        TogglePlayerSpectating(spectator, true);
		   	PlayerSpectatePlayer( spectator, playerid );
		   	SetPlayerInterior( spectator, GetPlayerInterior( playerid ) );
			SetPVarInt(spectator, "SpecState", newstate);
	    }
	}
	//pasajero
	if (newstate == PLAYER_STATE_PASSENGER)
	{
	    veh_asiento[playerid] = GetPlayerVehicleSeat(playerid);
		SetSyncTime(playerid, SYNC_TYPE_POS);
		gLastCar[playerid] = vehicleid;
		if (strcmp(veh_music[vehicleid], "nadauwu", true))
		{
			if (TipoAudio[playerid] == 0 && InfoPersonaje[playerid][pTogMusic] == 1)
			{
				PlayAudioStreamForPlayer(playerid, veh_music[vehicleid]);
				TipoAudio[playerid] = 3;
				SendPlayerChatMessage(playerid, COLOR_GREEN, "** Escuchas música del estéreo que está dentro del vehículo **");
			}
		}
	}
	//deja conductor
	if (oldstate == PLAYER_STATE_DRIVER)
	{
		hide_velocimetro(playerid);
		LastVehicle[playerid] = 0;
	}
	//conductor
	if (newstate == PLAYER_STATE_DRIVER)
	{
		veh_asiento[playerid] = GetPlayerVehicleSeat(playerid);
		LastVehicle[playerid] = vehicleid;
		if (vehicleid != 0) mostrar_velocimetro(playerid, vehicleid);
		SetVehicleParamsEx(vehicleid, arr_Engine{vehicleid}, lights, alarm, doors, bonnet, boot, objective);
		if (Vehiculo_Renta(vehicleid))
		{
			new id = verificar_id_vehiculo(vehicleid);
			if (InfoVehiculo[id][vRentaTiempo] != 0) //rentado
			{
				if (llaves_renta(playerid, vehicleid) != 0) format(string, sizeof string, "Tienes las llaves de {FFFFFF}%s{FF9B6A} rentado. (Tiempo restante %d minutos)", GetVehicleName(vehicleid), InfoVehiculo[id][vRentaTiempo]);
				else format(string, sizeof string, "Este {FFFFFF}%s{FF9B6A} está rentado por {FFFFFF}%s{FF9B6A}.", GetVehicleName(vehicleid), InfoVehiculo[id][vRentaDueno]);
				SendPlayerChatMessage(playerid, 0xFF9B6AFF, string);
			}
			else //por rentar
			{
				format(string, sizeof string, "Este %s esta disponible, su renta 15 minutos es de $150. (/rentarveh)", GetVehicleName(vehicleid));
				SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, string);
			}
		}
   		gLastCar[playerid] = vehicleid;
		if (strcmp(veh_music[vehicleid], "nadauwu", true))
		{
			if (TipoAudio[playerid] == 0 && InfoPersonaje[playerid][pTogMusic] == 1)
			{
				PlayAudioStreamForPlayer(playerid, veh_music[vehicleid]);
				TipoAudio[playerid] = 3;
				SendPlayerChatMessage(playerid, COLOR_GREEN, "** Escuchas música del estéreo que está dentro del vehículo **");
			}
		}
		//usuarios
		Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid && InfoVehiculo[id][vTipo] == 0 && InfoVehiculo[id][vNegocio] == 0 && InfoVehiculo[id][vTrabajo] == 0)
		{
			if (PermisosVehiculo(playerid, vehicleid) != -1)
			{
				//if (llaves_vehiculo(playerid, vehicleid) != -1) SendClientMessageEx(playerid, 0x79A5C9FF, "Eres el propietario de este vehículo %s.", GetVehicleName(vehicleid));
				//else SendClientMessageEx(playerid, 0x79A5C9FF, "Posees las llaves de este vehículo %s.", GetVehicleName(vehicleid));
				if (InfoVehiculo[id][vMulta] != 0)
				{
					SendClientMessageEx(playerid, 0xEB17009B, "Este vehículo tiene una multa de $%s, la misma se pega en DGT. (/gps)", diner_coma(InfoVehiculo[id][vMulta]));
				}
				return 1;
			}
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if ((engine == VEHICLE_PARAMS_OFF || engine == VEHICLE_PARAMS_UNSET)) SendPlayerChatMessage(playerid, COLOR_GREY, "El motor está apagado, puedes usar ganzúas para encenderlo. (/puente)");
			return 1;
		}
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	//si el jugador está herido/muerto
	if (InfoPersonaje[playerid][pMuerto] != 0)
	{
		if (veh_asiento[playerid] != -1)
		{
			ClearAnimations(playerid);
			PutPlayerInVehicle(playerid, vehicleid, veh_asiento[playerid]);
			anim_muerte(playerid);
			anim_muerte(playerid);
		    return 1;
		}
	}
	hide_velocimetro(playerid);
	if (TipoAudio[playerid] == 3)
	{
		StopAudioStreamForPlayer(playerid);
		TipoAudio[playerid] = 0;
	}
	if (Seatbelt[playerid] == 1)
	{
		if (IsABike(vehicleid)) rol_ame(playerid, "se quita el casco con sus manos.");
		else rol_ame(playerid, "se quita el cinturón con sus manos.");
		Seatbelt[playerid] = 0;
	}
	veh_asiento[playerid] = -1;
	return 1;
}

Show_cuenta(playerid, playerid2)
{
	if (!IsPlayerConnected(playerid) && !IsPlayerConnected(playerid2)) return 1;
	new hide_acoount[3500], gformat[320], gindice[128];
	//estadísticas
	//cuenta id
	format(gformat, sizeof gformat, "{6E72C7}Cuenta ID: {FFFFFF}%d (%s)\n", InfoCuenta[playerid2][jID], InfoCuenta[playerid2][jNombre]);
	strcat(hide_acoount, gformat);
	//id
	format(gformat, sizeof gformat, "{6E72C7}Personaje ID: {FFFFFF}%d (%s)\n", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pNombre_Apellido]);
	strcat(hide_acoount, gformat);
	//Dispositivo
	new mDispositivo[10];
	if(IsPlayerAndroid(playerid2)) alm(mDispositivo, "Android");
	else alm(mDispositivo, "PC");
	format(gformat, sizeof gformat, "{6E72C7}Dispositivo: {FFFFFF}%s\n", mDispositivo);
	strcat(hide_acoount, gformat);
	//edad
	format(gformat, sizeof gformat, "{6E72C7}Edad: {FFFFFF}%d\n", InfoPersonaje[playerid2][pEdad]);
	strcat(hide_acoount, gformat);
	//sexo
	new mSexo[10];
	if (InfoPersonaje[playerid2][pSexo] == 1) alm(mSexo, "Masculino");
	else alm(mSexo, "Femenino");
	format(gformat, sizeof gformat, "{6E72C7}Sexo: {FFFFFF}%s\n", mSexo);
	strcat(hide_acoount, gformat);
 	//horas conectado
	format(gformat, sizeof gformat, "{6E72C7}Horas jugando: {FFFFFF}%d\n", InfoPersonaje[playerid2][pHorasOn]);
	strcat(hide_acoount, gformat);
	//dinero
	if (GetPlayerCash(playerid2) >= 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}Dinero: {00C600}$%s\n", diner_coma(GetPlayerCash(playerid2)));
		strcat(hide_acoount, gformat);
	}
	else
	{
		format(gformat, sizeof gformat, "{6E72C7}Dinero: {FD1717}$%s\n", diner_coma(GetPlayerCash(playerid2)));
		strcat(hide_acoount, gformat);
	}
	//banco
	if (InfoPersonaje[playerid2][pBanco] >= 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}Cuenta bancaria: {00C600}$%s\n", diner_coma(InfoPersonaje[playerid2][pBanco]));
		strcat(hide_acoount, gformat);
	}
	else
	{
		format(gformat, sizeof gformat, "{6E72C7}Cuenta bancaria: {FD1717}$%s\n", diner_coma(InfoPersonaje[playerid2][pBanco]));
		strcat(hide_acoount, gformat);
	}
	//teléfono
	if (InfoPersonaje[playerid2][pTelefono] != 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}Número de teléfono: {FFFFFF}%d\n", InfoPersonaje[playerid2][pTelefono]);
		strcat(hide_acoount, gformat);
	}
	else strcat(hide_acoount, "{6E72C7}Número de teléfono: {FD1717}No tienes\n");
	//facción
	if (InfoPersonaje[playerid2][pMiembro] != 0)
	{
		new id = InfoPersonaje[playerid2][pMiembro];
		//facción logo
		format(gformat, sizeof gformat, "{6E72C7}Facción: {FE9A2E}%s\n", InfoFaccion[id][fLogo]);
		strcat(hide_acoount, gformat);
		//facción rango
		format(gformat, sizeof gformat, "{6E72C7}Rango: {FE9A2E}%s {FFFFFF}(%d)\n", fac_rango[id][InfoPersonaje[playerid2][pRango]-1], InfoPersonaje[playerid2][pRango]);
		strcat(hide_acoount, gformat);
	}
	else strcat(hide_acoount, "{6E72C7}Facción: {FD1717}No tienes\n");
	//Empleo 1
	if (InfoPersonaje[playerid2][pTrabajo1] != -1)
	{
		format(gformat, sizeof gformat, "{6E72C7}Empleo (1): {F2F81D}%s\n", GetNameContrato(InfoPersonaje[playerid2][pTrabajo1]));
		strcat(hide_acoount, gformat);
	}
	else strcat(hide_acoount, "{6E72C7}Empleo (1): {FD1717}No tienes\n");
	//Empleo 2
	if (InfoPersonaje[playerid2][pTrabajo2] != -1)
	{
		format(gformat, sizeof gformat, "{6E72C7}Empleo (2): {F2F81D}%s\n", GetNameContrato(InfoPersonaje[playerid2][pTrabajo2]));
		strcat(hide_acoount, gformat);
	}
	else strcat(hide_acoount, "{6E72C7}Empleo (2): {FD1717}No tienes\n");
	//Empleo 3
	if (InfoCuenta[playerid2][jVIP] != 0)
	{
		if (InfoPersonaje[playerid2][pTrabajo3] != -1)
		{
			format(gformat, sizeof gformat, "{6E72C7}Empleo (3): {F2F81D}%s\n", GetNameContrato(InfoPersonaje[playerid2][pTrabajo3]));
			strcat(hide_acoount, gformat);
		}
		else strcat(hide_acoount, "{6E72C7}Empleo (3): {FD1717}No tienes\n");
	}
	//vida
	format(gformat, sizeof gformat, "{6E72C7}Vida: {FFFFFF}%.1f\n", InfoPersonaje[playerid2][pVida]);
	strcat(hide_acoount, gformat);
	//chaleco
	format(gformat, sizeof gformat, "{6E72C7}Chaleco: {FFFFFF}%.1f\n", InfoPersonaje[playerid2][pChaleco]);
	strcat(hide_acoount, gformat);
	//interior
	format(gformat, sizeof gformat, "{6E72C7}Interior: {FFFFFF}%d\n", InfoPersonaje[playerid2][pInterior]);
	strcat(hide_acoount, gformat);
	//virtualworld
	format(gformat, sizeof gformat, "{6E72C7}Mundo: {FFFFFF}%d\n", InfoPersonaje[playerid2][pVirtualWorld]);
	strcat(hide_acoount, gformat);
	//skin
	format(gformat, sizeof gformat, "{6E72C7}Skin: {FFFFFF}%d\n", InfoPersonaje[playerid2][pSkin]);
	strcat(hide_acoount, gformat);
	//casas
	new count1 = 0;
	Loop(id, totalcasas, 1) if (LlavesCasa(playerid2, id))
	{
		count1++;
		format(gformat, sizeof gformat, "{6E72C7}Casa (%d): {FFFFFF}%d\n", count1, id);
		strcat(hide_acoount, gformat);
	}
	if (count1 == 0) strcat(hide_acoount, "{6E72C7}Casas: {FD1717}No tienes\n");
	//negocios
	new count2 = 0;
	Loop(id, totalnegocios, 1) if (LlavesNegocio(playerid2, id))
	{
		count2++;
		format(gformat, sizeof gformat, "{6E72C7}Negocio (%d): {FFFFFF}%d\n", count2, id);
		strcat(hide_acoount, gformat);
	}
	if (count2 == 0) strcat(hide_acoount, "{6E72C7}Negocios: {FD1717}No tienes\n");
	//arrestos ic
	format(gformat, sizeof gformat, "{6E72C7}Arrestos IC: {FFFFFF}%d\n", InfoPersonaje[playerid2][pArrestos]);
	strcat(hide_acoount, gformat);
	//arrestos ooc
	format(gformat, sizeof gformat, "{6E72C7}Arrestos OOC: {FFFFFF}%d\n", InfoPersonaje[playerid2][pJails]);
	strcat(hide_acoount, gformat);
	//tiempo sanción
	if (InfoPersonaje[playerid2][pSancionado] != 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}Tiempo sanción: {FFFFFF}%s\n", Segundos_tiempo(InfoPersonaje[playerid2][pTiempoSancion]));
		strcat(hide_acoount, gformat);
	}
	//documento
	format(gformat, sizeof gformat, "{6E72C7}Documento (DNI): {FFFFFF}%d\n", InfoPersonaje[playerid2][pDocumento]);
	strcat(hide_acoount, gformat);
	//fecha de registro
	format(gformat, sizeof gformat, "{6E72C7}Fecha registro: {FFFFFF}%s\n", InfoPersonaje[playerid2][pFechaRegistro]);
	strcat(hide_acoount, gformat);
	//vip
	if (InfoCuenta[playerid2][jVIP] != 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}VIP: {E1CD1A}%s {FFFFFF}(Expira en %s)\n", GetNameVIP(InfoCuenta[playerid2][jVIP]), Segundos_tiempo(InfoCuenta[playerid2][jExpira]-gettime()));
		strcat(hide_acoount, gformat);
	}
	//coins vip
	if (InfoCuenta[playerid2][jMonedas] != 0)
	{
		format(gformat, sizeof gformat, "{6E72C7}Coins VIP: {FFFFFF}%d\n", InfoCuenta[playerid2][jMonedas]);
		strcat(hide_acoount, gformat);
	}
	//indice
	if (playerid2 != playerid) format(gindice, sizeof gindice, "{6E72C7}Estadísticas de %s", InfoPersonaje[playerid2][pNombre_Apellido]);
	else alm(gindice, "{6E72C7}Estadísticas");
	//diálogo
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, gindice, hide_acoount, "Ok", "");
	return 1;
}

AntiDeAMX()
{
    new a[][] = {
        "Unarmed (Fist)",
        "Brass K"
    };
    #pragma unused a
}

stock buscar_modelo_obj(model, &dest)
{
	Loop(i, sizeof objetos_interior, 0)
	{
		if(model == objetos_interior[i][0]) dest = i;
	}
	return 0;
}

// strmatch
stock strmatch(const String1[], const String2[])
{
	if ((strcmp(String1, String2, true, strlen(String2)) == 0) && (strlen(String2) == strlen(String1)))
	{
		return true;
	}
	else
	{
		return false;
	}
}


public OnPlayerStreamIn(playerid, forplayerid)
{
	ShowPlayerNameTagForPlayer(playerid, forplayerid, false);
	return 1;
}

main()
{
	gettime(xHora, xMinuto, xSegundo); // 01/08/2020
	Timers();
}

public OnGameModeInit()
{
	AntiDeAMX();
	ConexionMySQL();
	CA_Init();

	CEF_AddResource("inventory"); 
    CEF_RegisterEvent("inventory:move", "OnInventoryMove", Argument_String);
    CEF_RegisterEvent("inventory:use", "OnInventoryUse", Argument_Integer);
    CEF_RegisterEvent("inventory:equip", "OnInventoryEquip", Argument_Integer);
    CEF_RegisterEvent("inventory:drop", "OnInventoryDrop", Argument_Integer);

	//configuración
	SendRconCommand("mapname Los Santos");
	SendRconCommand("language Español | Spanish");
	SendRconCommand("weburl "SERVER_WEBSITE"");
	SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("hostname "SERVER_HOSTNAME"");
	SendRconCommand("rcon_password Fugados741");
    AllowInteriorWeapons(true);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
    EnableStuntBonusForAll(false);
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();
    SetNameTagDrawDistance(20.0);
	ShowNameTags(false);

    //loader
 	LoadServerInfo();
	SanAndreas();
	AddMaps();
	Update_Weather();

	SetServerRuleFlags("weather", CON_VARFLAG_READONLY);

	mysql_log(ERROR | WARNING);
	return 1;
}


stock CEF_CrearInventario(playerid)
{
	if (!gCefReady[playerid]) return 0;
	if (gCefInvEstado[playerid] != 0) return 1;
	gCefInvEstado[playerid] = 1;
	CEF_CreateBrowser(playerid, CEF_INV_ID, CEF_INV_URL, false, true);
	return 1;
}

stock CEF_AbrirInventario(playerid, bool:abrir)
{
	if (gCefInvEstado[playerid] != 2) return 0;
	CEF_SetBrowserVisible(playerid, CEF_INV_ID, abrir);
	CEF_FocusBrowser(playerid, CEF_INV_ID, abrir);
	InventarioAbierto[playerid] = abrir;
	return 1;
}

public OnCefInitialize(playerid, bool:success, E_CEF_INIT_REASON:reason, const message[])
{
	printf("[CEF-DBG] OnCefInitialize p=%d success=%d reason=%d msg=%s", playerid, success, _:reason, message);
	if (!success)
	{
		printf("[CEF] init fallo: player=%d reason=%d msg=%s", playerid, _:reason, message);
		SendClientMessage(playerid, -1, "No tienes el plugin CEF instalado.");
	}
	
	return 1;
}

public OnCefReady(playerid)
{
	if (QuiereAbrirInv[playerid])
    {
        CrearNavegadorInventario(playerid);
        QuiereAbrirInv[playerid] = false;
    }
	
	printf("[CEF-DBG] OnCefReady p=%d logueado=%d", playerid, usuario_registro[playerid] == 2);
	gCefReady[playerid] = true;
	if (usuario_registro[playerid] == 2) CEF_CrearInventario(playerid); // si ya hizo login
	return 1;
}

public OnCefBrowserCreated(playerid, browserid, bool:success, E_CEF_CREATE_STATUS:code, const reason[])
{
	printf("[CEF] browser creado: player=%d id=%d ok=%d code=%d reason=%s", playerid, browserid, success, _:code, reason);
	if (browserid == CEF_INV_ID)
	{
		if (success)
		{
			gCefInvEstado[playerid] = 2;
			CEF_SetBrowserVisible(playerid, CEF_INV_ID, false); // arranca oculto
		}
		else gCefInvEstado[playerid] = 0;
	}
	return 1;
}

public OnGameModeExit()
{

    return 1;
}

forward PayDay2();
public PayDay2()
{
	new query[175];
	PayDaySecond = 120;
	//pago automático:
	Loop(id, totalnegocios, 1) if (InfoNegocio[id][nVenta] != 0)
	{
		new pagoG = neg_automatico[InfoNegocio[id][nTipo]];
		if (InfoNegocio[id][EnLlamas] == 1) // en llamas
		{
			if (pagoG != 0 && InfoNegocio[id][nProductos] >= 20)
			{
				InfoNegocio[id][nProductos] -= 20;
				InfoNegocio[id][nDinero] -= pagoG;
				mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET BolosUwU = '%d', Productos = '%d' WHERE ID = '%d'", InfoNegocio[id][nDinero], InfoNegocio[id][nProductos], InfoNegocio[id][nID_sql]);
				mysql_tquery(db_samp, query);
				foreach(Player, playerid) if (IsPlayerConnectedEx(playerid) && LlavesNegocio(playerid, id))
				{
					SendClientMessageEx(playerid, 0x19AD7AC2, "[#] El negocio %s que es de tu propiedad, ha perdido $%s y veinte productos por las llamas del incendio.", InfoNegocio[id][nNombre], diner_coma(pagoG));
				}
			}
		}
		else // normal
		{
			if (pagoG != 0 && InfoNegocio[id][nProductos] >= 20)
			{
				InfoNegocio[id][nProductos] -= 20;
				InfoNegocio[id][nDinero] += pagoG;
				mysql_format(db_samp, query, sizeof query, "UPDATE negocios SET BolosUwU = '%d', Productos = '%d' WHERE ID = '%d'", InfoNegocio[id][nDinero], InfoNegocio[id][nProductos], InfoNegocio[id][nID_sql]);
				mysql_tquery(db_samp, query);
				foreach(Player, playerid) if (IsPlayerConnectedEx(playerid) && LlavesNegocio(playerid, id))
				{
					SendClientMessageEx(playerid, 0x19AD7AC2, "[#] El negocio %s que es de tu propiedad, ha generado $%s en dos horas.", InfoNegocio[id][nNombre], diner_coma(pagoG));
				}
			}
		}
	}
	CheckNegocio();
	CheckHouse();
	CheckContenedores();
	return 1;
}

forward ClosedLSPDPuerta();
public ClosedLSPDPuerta()
{
	MoveDynamicObject(lspdPuerta, 1555.61816, -1670.56628, 2110.85913, 3.0);
	return 1;
}

public OnPlayerPressButton(playerid, buttonid)
{
	if (buttonid == lspdBoton)
    {
		if (!member_faccion(playerid, 1, 4)) return SendPlayerChatMessage(playerid,COLOR_GREY, "Acceso denegado; Sólo policias.");
		MoveDynamicObject(lspdPuerta, 1554.1582, -1670.5663, 2110.8591, 3.0);
		SetTimer("ClosedLSPDPuerta", 5000, false);
    }
	if (buttonid == SDboton1)
	{
		if (InfoPersonaje[playerid][pInterior] == 38) // pd
		{

		}
		else // sd
		{
			if (!member_faccion(playerid, 4)) return SendPlayerChatMessage(playerid,COLOR_GREY, "Acceso denegado; Sólo miembros de LSCSD.");
			MoveDynamicObject(SDobj1, 1616.2306, 1579.2373, 9.8099,4);
			SetTimer("CerrarSDOne", 2500, false);
		}
	}
	if (buttonid == SDboton2)
	{
		if (InfoPersonaje[playerid][pInterior] == 38) // pd
		{

		}
		else // sd
		{
			if (!member_faccion(playerid, 4)) return SendPlayerChatMessage(playerid,COLOR_GREY, "Acceso denegado; Sólo miembros de LSCSD.");
			MoveDynamicObject(SDobj2, 1616.2507, 1594.7173, 9.8099,4);
			SetTimer("CerrarSDTwo", 2500, false);
		}
	}
	return false;
}

// EMS
KillEMSQueue(playerid)
{
	SetPVarInt(playerid, "EstaCrack", 0);
    StopApplyAnimEx(playerid);
    TogglePlayerControllable(playerid, true);
	DeletePVar(playerid, "IsFrozen");
	dar_vida(playerid, 50);
	InfoPersonaje[playerid][pMuerto] = 0;
	YaAviso[playerid] = 0;
	timer_herido[playerid] = 0;
    player_weapon[playerid] = -1;
	player_asesino[playerid] = -1;
	pDroga[playerid][Sobredosis] = 0;
	guardar_int_mysql("personajes", "Sobredosis", InfoPersonaje[playerid][pID], 0);
	guardar_int_mysql("personajes", "Muerto", InfoPersonaje[playerid][pID], 0);
	Loop(x, 3, 0) { PlayerTextDrawHide(playerid, p_tdMuerte[playerid][x]); }
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		for(new i; i < MAX_COP_OBJECTS; i++)
		{

			if(!CopObjectData[i][ObjCreated]) continue;
			if(areaid == CopObjectData[i][ObjArea])
			{

				switch(CopObjectData[i][Type])
				{

					case OBJECT_TYPE_SPIKE:
					{

						new panelsx, doorsx, lightsx, tiresx;
						GetVehicleDamageStatus(GetPlayerVehicleID(playerid), panelsx, doorsx, lightsx, tiresx);
						UpdateVehicleDamageStatus(GetPlayerVehicleID(playerid), panelsx, doorsx, lightsx, encode_tires(1, 1, 1, 1));
						PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
					}
				}

				break;
			}
		}
	}
    foreach(Player, i) if (IsPlayerConnectedEx(i))
	{
		if (InfoBoombox[i][BB_area]) if (areaid == InfoBoombox[i][BB_area])
		{
			new station[256];
			GetPVarString(i, "BBStation", station, sizeof station);
			if (!isnull(station) && TipoAudio[playerid] == 0 && InfoPersonaje[playerid][pTogMusic] == 1)
			{
				SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "*** Escuchas música proveniente de un equipo de sonido ***");
				PlayStream(playerid, station, InfoBoombox[i][BB_x], InfoBoombox[i][BB_y], InfoBoombox[i][BB_z], 30.0, 1);
				TipoAudio[playerid] = 1;
			}
			return 1;
		}
		//estéreo
		if (GetPVarType(i, "AreaVehMus")) if (areaid == GetPVarInt(i, "AreaVehMus"))
		{
			new station[256];
			GetPVarString(i, "AreaVehAud", station, sizeof(station));
			if (!isnull(station) && TipoAudio[playerid] == 0 && InfoPersonaje[playerid][pTogMusic] == 1)
			{
				TipoAudio[playerid] = 4;
				if (!GetVehicleModel(GetPVarInt(i, "AreaVehID"))) SendClientMessageEx(playerid, COLOR_LIGHTGREEN, "*** Escuchas música proveniente de un vehículo ***");
				else SendClientMessageEx(playerid, COLOR_LIGHTGREEN, "*** Escuchas música proveniente del vehículo %s ***", GetVehicleName(GetPVarInt(i, "AreaVehID")));
				ReproducirMVeh(playerid, station, GetPVarFloat(i, "AreaVehPosX"), GetPVarFloat(i, "AreaVehPosY"), GetPVarFloat(i, "AreaVehPosZ"), 50.0, 1);
			}
			return 1;
		}
	}
	return 1;
}

stock PlayStream(playerid, const url[], Float: posX = 0.0, Float: posY = 0.0, Float: posZ = 0.0, Float: distance = 50.0, usepos = 0)
{
	if(GetPVarType(playerid, "MusBB")) StopAudioStreamForPlayer(playerid);
	else SetPVarInt(playerid, "MusBB", 1);
	if (TipoAudio[playerid] == 0 || TipoAudio[playerid] == 1) PlayAudioStreamForPlayer(playerid, url, posX, posY, posZ, distance, usepos);
}

forward StopStream(playerid);
public StopStream(playerid)
{
	DeletePVar(playerid, "MusBB");
	if (TipoAudio[playerid] == 1)
	{
		StopAudioStreamForPlayer(playerid);
		TipoAudio[playerid] = 0;
	}
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	foreach(Player, i)
	{
		if (InfoBoombox[i][BB_area]) if (areaid == InfoBoombox[i][BB_area])
		{
			StopStream(playerid);
			return 1;
		}
		if (GetPVarType(i, "AreaVehMus")) if (areaid == GetPVarInt(i, "AreaVehMus"))
		{
			PararMVeh(playerid);
			return 1;
		}
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid,Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,Float:fRotX, Float:fRotY, Float:fRotZ,Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{
	if (EditandoObjetoJ[playerid] == 2)
	{
		if (InfoPersonaje[playerid][pEspalda] == 0)
		{
			EditandoObjetoJ[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes ningún arma que editar.");
			return 1;
		}
		if (!response)
		{
			SetPlayerAttachedObject(playerid, 9, modelid, InfoPersonaje[playerid][ptHueso][7], InfoPersonaje[playerid][ptPosX][7], InfoPersonaje[playerid][ptPosY][7], InfoPersonaje[playerid][ptPosZ][7], InfoPersonaje[playerid][ptRotX][7], InfoPersonaje[playerid][ptRotY][7], InfoPersonaje[playerid][ptRotZ][7], 1.000000, 1.000000, 1.000000);
			SendPlayerChatMessage(playerid, 0xefefefff, "Cancelaste la edición del arma.");
			EditandoObjetoJ[playerid] = 0;
			return 1;
		}
		InfoPersonaje[playerid][ptPosX][7] = fOffsetX;
	    InfoPersonaje[playerid][ptPosY][7] = fOffsetY;
	    InfoPersonaje[playerid][ptPosZ][7] = fOffsetZ;
	    InfoPersonaje[playerid][ptRotX][7] = fRotX;
	    InfoPersonaje[playerid][ptRotY][7] = fRotY;
	    InfoPersonaje[playerid][ptRotZ][7] = fRotZ;
		InfoPersonaje[playerid][ptScaleX][7] = 1.000000;
		InfoPersonaje[playerid][ptScaleX][7] = 1.000000;
		InfoPersonaje[playerid][ptScaleX][7] = 1.000000;

		RemovePlayerAttachedObject(playerid, 9);

		SetPlayerAttachedObject(playerid, 9, modelid, InfoPersonaje[playerid][ptHueso][7], InfoPersonaje[playerid][ptPosX][7], InfoPersonaje[playerid][ptPosY][7], InfoPersonaje[playerid][ptPosZ][7], InfoPersonaje[playerid][ptRotX][7], InfoPersonaje[playerid][ptRotY][7], InfoPersonaje[playerid][ptRotZ][7], 1.000000, 1.000000, 1.000000);

		EditandoObjetoJ[playerid] = 0;
		ActualizarToy(playerid, 7);

		SendPlayerChatMessage(playerid, COLOR_GENERAL, "Posiciones guardadas, si deseas editar otra vez escribe /arma ajustar.");
		return 1;
	}
	new x = slotselection[playerid], gformat[264];
	InfoPersonaje[playerid][ptPosX][x] = fOffsetX;
    InfoPersonaje[playerid][ptPosY][x] = fOffsetY;
    InfoPersonaje[playerid][ptPosZ][x] = fOffsetZ;
    InfoPersonaje[playerid][ptRotX][x] = fRotX;
    InfoPersonaje[playerid][ptRotY][x] = fRotY;
    InfoPersonaje[playerid][ptRotZ][x] = fRotZ;

    InfoPersonaje[playerid][ptScaleX][x] = fScaleX;
    if (fScaleX < 0.1) InfoPersonaje[playerid][ptScaleX][x] = 0.1;
 	else if (fScaleX > 1.5) InfoPersonaje[playerid][ptScaleX][x] = 1.5;

    InfoPersonaje[playerid][ptScaleY][x] = fScaleY;
 	if (fScaleY < 0.1) InfoPersonaje[playerid][ptScaleY][x] = 0.1;
 	else if (fScaleY > 1.5) InfoPersonaje[playerid][ptScaleY][x] = 1.5;

 	InfoPersonaje[playerid][ptScaleZ][x] = fScaleZ;
 	if (fScaleZ < 0.1) InfoPersonaje[playerid][ptScaleZ][x] = 0.1;
 	else if (fScaleZ > 1.5) InfoPersonaje[playerid][ptScaleZ][x] = 1.5;

	SetPlayerAttachedObject(playerid, x, InfoPersonaje[playerid][ptModelo][x], InfoPersonaje[playerid][ptHueso][x], InfoPersonaje[playerid][ptPosX][x], InfoPersonaje[playerid][ptPosY][x], InfoPersonaje[playerid][ptPosZ][x],
	InfoPersonaje[playerid][ptRotX][x], InfoPersonaje[playerid][ptRotY][x], InfoPersonaje[playerid][ptRotZ][x], InfoPersonaje[playerid][ptScaleX][x], InfoPersonaje[playerid][ptScaleY][x], InfoPersonaje[playerid][ptScaleZ][x],
	SetColorToy(InfoPersonaje[playerid][ptColor][x]));
	InfoPersonaje[playerid][ptColocado][x] = 1;
	ActualizarToy(playerid, x);
	format(gformat, sizeof gformat, "Posiciones de tu {FE9A2E}%s{FFFFFF} actualizadas. Si quieres editar otro toy, usa: {3E62F4}/toys{FFFFFF}.", GetNameToy(playerid, x));
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
	slotselection[playerid] = -1;
	Editing[playerid] = 0;
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	return 1;
}

IsVehicleBusy(vehicleid) // The_Chaoz ¿?¿?¿
{
    for(new i; i<GetMaxPlayers(); i++)
    	if(IsPlayerConnected(i) && IsPlayerInVehicle(i, vehicleid))
    		return 1;
    return 0;
}

SendAllICMessage(color, const string[])
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid) && InfoPersonaje[playerid][pTogAnuncios] == 0)
	{
		SendSplitMessage(playerid, color, string);
	}
}

SendAllMessage(color, const string[])
{
	foreach(Player, playerid) if (IsPlayerConnectedEx(playerid) && InfoPersonaje[playerid][pTogOOC] == 1)
	{
		SendSplitMessage(playerid, color, string);
	}
}

GetMiembrosFaccion(id)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE MiembroFaccion = '%d'", id);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}

GetEmpleados1Job(id)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Trabajo1 = '%d'", id);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}

GetEmpleados2Job(id)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Trabajo2 = '%d'", id);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}

GetEmpleados3Job(id)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Trabajo3 = '%d'", id);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}

stock Float:GetPosInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)//by: whoever
{
	new Float:a;
	GetPlayerPos(playerid, x, y, a);
	switch(IsPlayerInAnyVehicle(playerid))
	{
	    case 0: GetPlayerFacingAngle(playerid, a);
	    case 1: GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
	return a;
}

SetPlayerAnuncio(playerid, type)
{
	if (InfoPersonaje[playerid][pTogAnuncios] == 1) return 1;
	if (InfoCuenta[playerid][jEstiloAnuncio] == 1) return 1;
	if (type == 1)
	{
		new numer = PlayerViewAnunce[playerid];
		if (numer != 0)
		{
			Loop(x, numer, 0) { TextDrawShowForPlayer(playerid, TD_Anuncio[x]); }
		}
	}
	else if (type == 2)
	{
		Loop(x, 5, 0) { TextDrawHideForPlayer(playerid, TD_Anuncio[x]); }
	}
	return 1;
}

Descuento_Compra(playerid, valor_dolar, type)
{
	new nuevo_valor_dolar = valor_dolar;
	if (type == 1) //compra de articulos de negocios
	{
		if (InfoCuenta[playerid][jVIP] == 1) nuevo_valor_dolar = (valor_dolar*80)/100;
		if (InfoCuenta[playerid][jVIP] == 2) nuevo_valor_dolar = (valor_dolar*60)/100;
	}
	else if (type == 2) //compra de vehículos
	{
		if (InfoCuenta[playerid][jVIP] == 1) nuevo_valor_dolar = (valor_dolar*85)/100;
		if (InfoCuenta[playerid][jVIP] == 2) nuevo_valor_dolar = (valor_dolar*70)/100;
	}
	return nuevo_valor_dolar;
}

VerificarDNI(documento)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Documento = '%d'", documento);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	if (nm > 0) return 1;
	return 0;
}

GetAntecedentes(documento)
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE Documento = '%d'", documento);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}


Uso_Dop(const string[], color, Float: radio, Float: x, Float: y, Float: z, int, vw)
{
	foreach(new playerid: Player) if (IsPlayerConnectedEx(playerid))
	{
		if (GetPlayerVirtualWorld(playerid) == vw && GetPlayerInterior(playerid) == int)
		{
			if (IsPlayerInRangeOfPoint(playerid, radio / 16, x, y, z)) SendSplitMessage(playerid, color, string);
			else if (IsPlayerInRangeOfPoint(playerid, radio / 8, x, y, z)) SendSplitMessage(playerid, color, string);
			else if (IsPlayerInRangeOfPoint(playerid, radio / 4, x, y, z)) SendSplitMessage(playerid, color, string);
			else if (IsPlayerInRangeOfPoint(playerid, radio / 2, x, y, z)) SendSplitMessage(playerid, color, string);
			else if (IsPlayerInRangeOfPoint(playerid, radio, x, y, z)) SendSplitMessage(playerid, color, string);
		}
	}
	return 1;
}

//desde aquí empiezan los comandos.
cmd:llamada(playerid){
	if (!member_faccion(playerid, 1, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo miembros de LSPD, LSCSD o LSFD.");
	if(lastcall911[0] != 0.0){
		SetPlayerCheckpoint(playerid, lastcall911[0], lastcall911[1], lastcall911[2], 2.0);
	}
	return 1;
}

cmd:llamados(playerid)
{
	new string[256], dialog[3000], cuerpos = 0, Str[128];
	if (!member_faccion(playerid, 1, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo miembros de LSPD, LSCSD o LSFD.");
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2) && YaAviso[playerid2] != 0)
	{
		new estado2[24], Float: xp, Float: yp, Float: zp, location[MAX_ZONE_NAME];
		if (InfoPersonaje[playerid2][pMuerto] == 1) estado2 = "{FF0000}Herida";
		else estado2 = "{E94434}Muerta";
		GetPlayerPos(playerid2, xp, yp, zp);
		Get2DZone(location, sizeof location, xp, yp, zp);
		format(string, sizeof string, "{EBEBEB}%s en %s (%s{EBEBEB})\n", GetNameFormat(playerid2), location, estado2);
		strcat(dialog, string);
		format(Str, sizeof Str, "enfermo_%d", cuerpos);
		SetPVarInt(playerid, Str, playerid2);
		cuerpos++;
  	}
	if (cuerpos == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay ningún jugador en estado herido o muerto.");
	Dialog_Show(playerid, ShowLlamados, DIALOG_STYLE_LIST, "{EBEBEB}Lista de {FE9A2E}llamados", dialog, ">>", "<<");
	return 1;
}

Dialog:ShowLlamados(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ID = listitem,StrPVar[40];
	format(StrPVar, sizeof StrPVar, "enfermo_%d",ID);
	new playerid2 = GetPVarInt(playerid, StrPVar), Float: xp, Float: yp, Float: zp;
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* La vicima se ha desconectado, se canceló el llamado.");
	GetPlayerPos(playerid2, xp, yp, zp);
	if (IsPlayerInAnyVehicle(playerid))
	{
		foreach(new p: Player) if (IsPlayerConnectedEx(p) && IsPlayerInVehicle(p, GetPlayerVehicleID(playerid)))
		{
			SetPlayerCheckpoint(p, xp, yp, zp, 2.0);
			SendClientMessageEx(p, 0x3BA4C2FF, "Llamado sobre la victima %s, marcada en el mapa (radar).", GetNameFormat(playerid2));
		}
		return 1;
	}
	SetPlayerCheckpoint(playerid, xp, yp, zp, 2.0);
	SendClientMessageEx(playerid, 0x3BA4C2FF, "Llamado sobre la victima %s, marcada en el mapa (radar).", GetNameFormat(playerid2));
	return 1;
}

funcion tiene_carga(playerid, idobj)
{
	new izq = InfoPersonaje[playerid][pManoIzquierda];
	if (izq == idobj)
	{
		return idobj;
	}
	Loop(e, 9, 0) if (InfoPersonaje[playerid][pBolsillo][e] == idobj)
	{
		return idobj;
	}
	return 0;
}

cmd:cargar(playerid) //poner cargador
{
	if (!CheckTimer(3, RecargarTiempo[playerid]))
	{
		if (InfoPersonaje[playerid][pManoDerechaCant] == InfoInventario[InfoPersonaje[playerid][pManoDerecha]][MaxCantidad]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El arma que tienes en mano tiene el máximo de balas.");
		new derecha = InfoPersonaje[playerid][pManoDerecha], derechaCant = InfoPersonaje[playerid][pManoDerechaCant], izquierda = InfoPersonaje[playerid][pManoIzquierda], izquierdaCant = InfoPersonaje[playerid][pManoIzquierdaCant];
		if (InfoInventario[derecha][IDArma] > 0 && InfoInventario[derecha][MaxCantidad] > 1) //tiene un arma en mano derecha
		{
			ActualizarManos(playerid);
			new cargador, ArmaID = InfoInventario[derecha][IDArma];
			switch (derecha)
			{
				case 19: cargador = 56;
				case 20: cargador = 56;
				case 21: cargador = 57;
				case 22: cargador = 64;
				case 23: cargador = 64;
				case 24: cargador = 64;
				case 25: cargador = 58;
				case 26: cargador = 59;
				case 27: cargador = 61;
				case 28: cargador = 62;
				case 29: cargador = 60;
				case 30: cargador = 63;
				case 31: cargador = 63;
			}
			new objeto = tiene_carga(playerid, cargador);
			if (objeto != cargador) { SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún cargador para esta arma."); return 1; }

			if (izquierda != cargador) //función bolsillos
			{
				new ranura = tiene_objeto(playerid, cargador);
				if (InfoPersonaje[playerid][pBolsilloCant][ranura] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar un cargador vacío.");
				if (InfoInventario[derecha][MaxCantidad] >= derechaCant+InfoPersonaje[playerid][pBolsilloCant][ranura]) SendClientMessageEx(playerid, COLOR_YELLOW, "Cargas tu %s con %d balas.", InfoInventario[derecha][NombreObjeto], InfoPersonaje[playerid][pBolsilloCant][ranura]);
				else SendClientMessageEx(playerid, COLOR_YELLOW, "Cargas tu %s con %d balas.", InfoInventario[derecha][NombreObjeto], InfoInventario[derecha][MaxCantidad]-InfoPersonaje[playerid][pManoDerechaCant]);

				ResetPlayerWeapons(playerid);
				GivePlayerWeapon(playerid, ArmaID, InfoPersonaje[playerid][pBolsilloCant][ranura]+derechaCant);
				InfoPersonaje[playerid][pManoDerechaCant] = InfoPersonaje[playerid][pBolsilloCant][ranura]+derechaCant;
				InfoPersonaje[playerid][pBolsillo][ranura] = 0;
				InfoPersonaje[playerid][pBolsilloCant][ranura] = 0;
				RecargarTiempo[playerid] = gettime();
				Anti[playerid][BalasW] = 0;
				ActualizarManos(playerid, 1);
				return 1;
			}
			else //función mano izquierda
			{
				if (izquierdaCant == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar un cargador vacío.");
				if (InfoInventario[derecha][MaxCantidad] >= derechaCant+izquierdaCant) SendClientMessageEx(playerid, COLOR_YELLOW, "Cargas tu %s con %d balas.", InfoInventario[derecha][NombreObjeto], izquierdaCant);
				else SendClientMessageEx(playerid, COLOR_YELLOW, "Cargas tu %s con %d balas.", InfoInventario[derecha][NombreObjeto], InfoInventario[derecha][MaxCantidad]-InfoPersonaje[playerid][pManoDerechaCant]);
				ResetPlayerWeapons(playerid);
				GivePlayerWeapon(playerid, ArmaID, izquierdaCant+derechaCant);
				InfoPersonaje[playerid][pManoDerechaCant] = izquierdaCant+derechaCant;
				InfoPersonaje[playerid][pManoIzquierda] = 0;
				InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
				RemovePlayerAttachedObject(playerid, 8);
				RecargarTiempo[playerid] = gettime();
				Anti[playerid][BalasW] = 0;
				ActualizarManos(playerid, 1);
				return 1;
			}

		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(3, RecargarTiempo[playerid]) ));
	}
	return 1;
}

cmd:qcables(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	new playerid2, gformat[256];
	if (sscanf(params, "u", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /qcables (playerid)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador especificado no válido.");
	if (!CercaDelMarica(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está cerca tuyo.");
	if (Taseado[playerid2] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador no tiene cables de táser encima.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes quitarte los cables, pide ayuda a otro miembro.");
	Taseado[playerid2] = 0;
	ClearAnimations(playerid2);
	TogglePlayerControllable(playerid2, true);
	format(gformat, sizeof gformat, "le quitó los cables de táser a %s.", GetNameFormat(playerid2));
	rol_auto(playerid, gformat);
	return 1;
}
alias:qcables("quitarcables");

cmd:ant(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de LSPD, FBI, LSCSD o SADOC.");
	if (InfoPersonaje[playerid][pRango] < 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Necesitas ser mayor de rango 3.");
	new documento, detalles[256], id = InfoPersonaje[playerid][pMiembro], gformat[320], query[256];
	if (sscanf(params, "ds[256]", documento, detalles)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ant (DocumentoID) (Detalles)");
	if (!VerificarDNI(documento)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se encontro ningún personaje con ese documento.");
	if (GetAntecedentes(documento) >= 15) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese personaje ya tiene un total de 15 antecedentes.");

	mysql_format(db_samp, query, sizeof query, "INSERT INTO antecedentes (Documento, Faccion, Responsable, Detalles, Fecha) VALUES ('%d', '%e', '%e', '%e', '%e')", documento, InfoFaccion[id][fLogo], InfoPersonaje[playerid][pNombre_Apellido], detalles, FechaHoy());
	mysql_tquery(db_samp, query);

	format(gformat, sizeof gformat, "[CENTRAL] %s registró un nuevo antecedente al documento %d.", GetNameFormat(playerid), documento);
	SendRadioMessage(id, COLOR_RADIO, gformat, 1);

	return 1;
}
alias:ant("kawai");

cmd:historial(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de LSPD, FBI, LSCSD o SADOC.");
	new documento;
	if (sscanf(params, "d", documento)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /historial (DocumentoID)");
	if (!VerificarDNI(documento)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se encontro ningún personaje con ese documento.");
	new nant = GetAntecedentes(documento);
	if (nant > 0)
	{
		new count = 0, gformat[256], dialog[4096] = "#\tDetalles\tFecha\n";

		new query[160];
		new Cache:result;
		mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE Documento = '%d'", documento);
		result = mysql_query(db_samp, query);

		Loop(e, cache_num_rows(), 0)
		{
			new registro, detalles[512], fecha[256];
			rebel_int(e, "ID", registro);
			rebel_string(e, "Detalles", detalles, 512);
			rebel_string(e, "Fecha", fecha, 256);
			new mensaje[35];
			strmid(mensaje, detalles, 0, 35);
			//dialog
			format(gformat, sizeof gformat, "{EBEBEB}Registro: %d\t%s\t{E24D32}%s\n", registro, mensaje, fecha);
			strcat(dialog, gformat);
			//conteo
			new gformat2[64];
			format(gformat2, sizeof gformat2, "ehcHis%d", count);
			SetPVarInt(playerid, gformat2, registro);
			count++;
		}
		cache_delete(result);
		format(gformat, sizeof gformat, "{EBEBEB}Documento {088A4B}%d", documento);
		Dialog_Show(playerid, ShowHistorial, DIALOG_STYLE_TABLIST_HEADERS, gformat, dialog, "Ver más", "Salir");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay registros de antecedentes con ese documento.");
	return 1;
}
alias:historial("his", "otaku");

Dialog:ShowHistorial(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ehw = listitem, gformat[40];
	format(gformat, sizeof gformat, "ehcHis%d", ehw);
	new id = GetPVarInt(playerid, gformat), query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE ID = '%d'", id);
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0)
	{
		new documento, faccion[10], responsable[24], detalles[512], fecha[256];
		rebel_int(0, "Documento", documento);
		rebel_string(0, "Faccion", faccion, 10);
		rebel_string(0, "Responsable", responsable, 24);
		rebel_string(0, "Detalles", detalles, 512);
		rebel_string(0, "Fecha", fecha, 256);
		new dialog[1028], gstring[256];
		format(gstring, sizeof gstring, "Registro: #%d\n", id); strcat(dialog, gstring);
		format(gstring, sizeof gstring, "Responsable: %s (%s)\n", responsable, faccion); strcat(dialog, gstring);
		format(gstring, sizeof gstring, "Antecedente: %s\n", detalles); strcat(dialog, gstring);
		format(gstring, sizeof gstring, "Fecha: %s\n", fecha); strcat(dialog, gstring);
		format(gstring, sizeof gstring, "{EBEBEB}Documento {088A4B}%d", documento);
		Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, gstring, dialog, "Cerrar", "");
		return 1;
	}
	cache_delete(result);
	SendPlayerChatMessage(playerid, COLOR_GREY, "* Problemas con la base de datos, si continúa contacta con el programador vía Discord.");
	return 1;
}

cmd:qant(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de LSPD, FBI, LSCSD o SADOC.");
	if (InfoPersonaje[playerid][pRango] < 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Necesitas ser mayor de rango 3.");
	new documento;
	if (sscanf(params, "d", documento)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /qant (DocumentoID)");
	if (!VerificarDNI(documento)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se encontro ningún personaje con ese documento.");
	new nant = GetAntecedentes(documento);
	if (nant > 0)
	{
		new count = 0, gformat[256], dialog[4096] = "#\tDetalles\tFecha\n";

		new query[160];
		new Cache:result;
		mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE Documento = '%d'", documento);
		result = mysql_query(db_samp, query);

		Loop(e, cache_num_rows(), 0)
		{
			new registro, detalles[512], fecha[256];
			rebel_int(e, "ID", registro);
			rebel_string(e, "Detalles", detalles, 512);
			rebel_string(e, "Fecha", fecha, 256);
			new mensaje[35];
			strmid(mensaje, detalles, 0, 35);
			//dialog
			format(gformat, sizeof gformat, "{EBEBEB}Registro: %d\t%s\t{E24D32}%s\n", registro, mensaje, fecha);
			strcat(dialog, gformat);
			//conteo
			new gformat2[64];
			format(gformat2, sizeof gformat2, "ehcHis%d", count);
			SetPVarInt(playerid, gformat2, registro);
			count++;
		}
		cache_delete(result);
		format(gformat, sizeof gformat, "{EBEBEB}Documento {088A4B}%d", documento);
		Dialog_Show(playerid, DeleteHistorial, DIALOG_STYLE_TABLIST_HEADERS, gformat, dialog, "Borrar", "Salir");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay registros de antecedentes con ese documento.");
	return 1;
}
alias:qant("hentai");

Dialog:DeleteHistorial(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new ehw = listitem, gformat[40];
	format(gformat, sizeof gformat, "ehcHis%d", ehw);
	new id = GetPVarInt(playerid, gformat), slas[10] = "none", query[350];
	mysql_format(db_samp, query, sizeof query, "UPDATE antecedentes SET Documento = 0, Faccion = '%e', Responsable = '%e', Detalles = '%e', Fecha = '%e' WHERE ID = '%d'", slas, slas, slas, slas, id);
	mysql_tquery(db_samp, query);
	SendClientMessageEx(playerid, COLOR_YELLOW, "Eliminaste los registros de antecedentes nº%d.", id);
	format(query, sizeof query, "%s borró los antecedentes nº%d.", InfoPersonaje[playerid][pNombre_Apellido], id);
	Log("f_logs/DeleteHistorial.txt", query);
	return 1;
}

cmd:mecanicos(playerid)
{
	if (NPCrepara[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes una operación de mecánico activa.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser el conductor de un vehículo.");
	if (VehiculoGasolina[playerid] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes llamar un mecánico en este momento.");
	new vehicleid = GetPlayerVehicleID(playerid), costo = 450;
	new Float: cvida;
	GetVehicleHealth(vehicleid, cvida);
	new Percent_damage = floatround(cvida);
	if (Percent_damage >= 520) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El health (/dl) del vehículo pasa los 520, lleva el vehículo a un taller.");
	if (GetPlayerCash(playerid) < costo) { SendClientMessageEx(playerid, COLOR_GREY, "* No tienes suficiente dinero ($%s).", diner_coma(costo)); return 1; }
	SetTimerEx("CheckMecanicos", 60000, false, "ddd", playerid, vehicleid, costo);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Llamaste un mecánico (npc), el mismo reparará un poco la vida del motor de tu vehículo. (60 segundos)");
    NPCrepara[playerid] = 1;
	return 1;
}

forward CheckMecanicos(playerid, vehicleid, costo);
public CheckMecanicos(playerid, vehicleid, costo)
{
	if (GetPlayerCash(playerid) < costo) { SendClientMessageEx(playerid, COLOR_GREY, "* No tienes suficiente dinero ($%s).", diner_coma(costo)); return 1; }
	SetVehicleHealth(vehicleid, 550.0);
	if (veh_gasolina[vehicleid] >= 99) veh_gasolina[vehicleid] = 100;
	else veh_gasolina[vehicleid] += 25;

	GivePlayerCash(playerid, -costo, "cobro mecanico npc");
	new string[190];
	format(string, sizeof string, "** Un mecánico llegó al lugar y revisó las fallas del vehículo de {player:%d}.", playerid);
	ProxDetector(30.0, playerid, string, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN, COLOR_LIGHTGREEN);
    NPCrepara[playerid] = 0;
    SendPlayerChatMessage(playerid, COLOR_YELLOW, "Revisaron las fallas del motor (550 hp) y echaron algo de gasolina en el tanque de tu vehículo.");
	return 1;
}

Dialog:ComplandoVehVIP(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new gformat[256], modelo = complandomodelovip[playerid], valor = complandopreciovip[playerid];
	if (InfoCuenta[playerid][jMonedas] < valor)
	{
		format(gformat, sizeof gformat, "El costo del modelo {FE9A2E}%d{FFFFFF} es {00CC00}%d coins VIP{FFFFFF}, los cuales no tienes!", modelo, valor);
		SendPlayerChatMessage(playerid, -1, gformat);
		return 1;
	}
	if (DetectarMaxVehiculos(playerid) == 1) return 1;
	InfoCuenta[playerid][jMonedas] -= valor;
	guardar_int_mysql("cuentas", "CoinsVIP", InfoCuenta[playerid][jID], InfoCuenta[playerid][jMonedas]);
	new Float: X, Float:Y, Float: Z, Float: Angle, color1 = random(240), color2 = random(240);
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, Angle);
	crear_vehiculo(playerid, modelo, X, Y, Z, Angle, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), color1, color2, 0, 5, 0, -1, -1);
	format(gformat, sizeof gformat, "Felicidades por tu nuevo vehículo, gastaste %d coins vip.", valor);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, gformat);
	return 1;
}

cmd:sirena(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo uso para LSPD, LSCSD, FBI y USMC.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debe ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid), id;
	if (sscanf(params, "d", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sirena (0:off - 1:roja y azul - 2: amarilla - 3: rojo y azul[normal] - 4: amarillo[normal])");
	if (id < 0 || id > 4) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sirena (0:off - 1:roja y azul - 2: amarilla - 3: rojo y azul[normal] - 4: amarillo[normal])");
	if (!id)
	{
		if (!SirenOn[vehicleid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no posee una sirena instalada.");
		Loop(e, 7, 0)
		{
			if (IsValidDynamicObject(SirenObject[vehicleid][e])) DestroyDynamicObject(SirenObject[vehicleid][e]);
			SirenObject[vehicleid][e] = 0;
		}
		rol_ame(playerid, "retiró la sirena de su vehículo.");
		SirenOn[vehicleid] = false;
		return 1;
	}
	if (SirenOn[vehicleid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo ya posee una sirena instalada.");
	new acceso = 0;
	switch (id)
	{
		case 1:
		{
			if (GetVehicleModel(vehicleid) == 596)
			{
				SirenObject[vehicleid][0] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -0.360, -0.330, 0.970, 0.000, 0.000, 0.000);
				SirenObject[vehicleid][1] = CreateDynamicObject(19292, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, 0.380, -0.310, 0.960, 0.000, 0.000, 0.000);
				SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, 0.700, 2.521, -0.150, 0.000, 0.000, 0.000);
				SirenObject[vehicleid][3] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, -0.650, 2.580, -0.120, 0.000, 0.000, 0.000);
				SirenObject[vehicleid][4] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, 0.810, -2.880, 0.020, 0.000, 0.000, 0.000);
				SirenObject[vehicleid][5] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, -0.840, -2.890, 0.070, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 599)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19292, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.420, -0.050, 1.160, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.400, -0.070, 1.180, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, 0.960, 2.641, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, -0.970, 2.661, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, -1.070, -2.731, 0.200, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, 1.120, -2.719, 0.200, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 597)
			{
				SirenObject[vehicleid][0] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -0.346, -0.209, 0.930, 0.000, 0.000, -43.200);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19292, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, 0.340, -0.240, 0.910, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, -0.719, -2.770, 0.150, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, 0.790, -2.821, 0.140, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, 0.650, 2.700, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, -0.659, 2.610, -0.049, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 598)
			{
				SirenObject[vehicleid][0] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.650, 2.611, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.630, 2.670, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, -0.720, -2.801, 0.150, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, 0.760, -2.859, 0.110, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, -0.400, -0.320, 0.980, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19292, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, 0.360, -0.350, 0.950, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 560)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19797, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.011, 0.579, 0.600, 0.000, 0.000, -179.699);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19797, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, 0.000, -0.950, 0.600, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 426)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19797, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, 0.460, 0.600, 0.000, 0.000, -179.499);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19797, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, 0.000, -1.729, 0.400, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 468)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -0.080, -0.920, 0.320, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19797, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.005, 0.549, 0.473, 0.000, -0.800, 179.700);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 521)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -0.050, -1.140, 0.470, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 528)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19290, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -0.360, 0.000, 1.329, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19292, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, 0.350, 0.000, 1.350, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 525)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19803, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, 0.130, 0.000, 0.000, 0.000, 0.000);
				acceso = 1;
			}
		}
		case 2:
		{
			if (GetVehicleModel(vehicleid) == 596)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, -0.300, 0.930, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.460, -0.320, 0.920, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, 0.440, -0.360, 0.930, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, 0.700, 2.521, -0.150, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, -0.650, 2.580, -0.120, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, 0.810, -2.880, 0.020, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][6] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][6], vehicleid, -0.840, -2.890, 0.070, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 599)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, -0.070, 1.070, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.560, -0.060, 1.070, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, 0.960, 2.641, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, -0.970, 2.661, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, -1.070, -2.731, 0.200, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, 1.120, -2.719, 0.200, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][6] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][6], vehicleid, 0.550, -0.060, 1.060, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 597)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, -0.230, 0.940, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.480, -0.199, 0.940, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, -0.719, -2.770, 0.150, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, 0.790, -2.821, 0.140, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, 0.650, 2.700, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, -0.659, 2.610, -0.049, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][6] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][6], vehicleid, 0.440, -0.230, 0.950, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 598)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19288, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.650, 2.611, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.630, 2.670, 0.000, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][2] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][2], vehicleid, -0.720, -2.801, 0.150, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][3] = CreateDynamicObject(19286, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][3], vehicleid, 0.760, -2.859, 0.110, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][4] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][4], vehicleid, 0.430, -0.380, 0.910, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][5] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][5], vehicleid, 0.000, -0.400, 0.890, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][6] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][6], vehicleid, -0.470, -0.390, 0.910, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 560)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19419, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, 0.000, 0.840, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 426)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19419, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, -0.240, 0.890, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 528)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19803, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.000, 0.410, -0.130, 0.000, 0.000, 0.000);
				acceso = 1;
			}
			else if (GetVehicleModel(vehicleid) == 525)
			{
			    SirenObject[vehicleid][0] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, 0.610, -0.380, 1.530, 0.000, 0.000, 0.000);
			    SirenObject[vehicleid][1] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			    AttachDynamicObjectToVehicle(SirenObject[vehicleid][1], vehicleid, -0.610, -0.379, 1.530, 0.000, 0.000, 0.000);
				acceso = 1;
			}
		}
		case 3:
		{
			new Float:fSize[3], Float:fSeat[3];
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, fSize[0], fSize[1], fSize[2]);
		    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_FRONTSEAT, fSeat[0], fSeat[1], fSeat[2]);
			SirenObject[vehicleid][0] = CreateDynamicObject(18646, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -fSeat[0], fSeat[1], fSize[2] / 2.0, 0.0, 0.0, 0.0);
			acceso = 1;
		}
		case 4:
		{
			new Float:fSize[3], Float:fSeat[3];
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, fSize[0], fSize[1], fSize[2]);
		    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_FRONTSEAT, fSeat[0], fSeat[1], fSeat[2]);
			SirenObject[vehicleid][0] = CreateDynamicObject(19294, 0.0, 0.0, 1000.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToVehicle(SirenObject[vehicleid][0], vehicleid, -fSeat[0], fSeat[1], fSize[2] / 2.0, 0.0, 0.0, 0.0);
			acceso = 1;
		}
	}
	if (acceso == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* En este vehículo no se puede instalar sirena de este tipo.");
	SirenOn[vehicleid] = true;
	rol_ame(playerid, "colocó una sirena en su vehículo.");
	return 1;
}
alias:sirena("sir");


cmd:gentrar(playerid)
{
	new id = -1;
	if (IsPlayerInRangeOfPoint(playerid, 15.0, 2780.1606, -1444.1877, 30.4491)) id = 1; // pd
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 624.4334,-604.5157,16.6686)) id = 2; // sd
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1505.3354, -1242.5944, 14.2322)) id = 3; // fbi
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1141.5438, -1335.2451, 13.7517)) id = 4; // fd
	else if (IsPlayerInRangeOfPoint(playerid, 10.0, 1789.9878, -1594.0779, 13.6542)) id = 5; // sadoc
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna entrada de estacionamiento.");
	switch (id)
	{
		case 1: { if (!member_faccion(playerid, 1)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de la policía."); }
		case 2: { if (!member_faccion(playerid, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de la sheriff."); }
		case 3: { if (!member_faccion(playerid, 2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro del fbi."); }
		case 4: { if (!member_faccion(playerid, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de los médicos/bomberos."); }
		case 5: { if (!member_faccion(playerid, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de la prisión federal."); }
	}
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		SetPosEx(playerid, -852.6990,-1728.1836,46.5421,272.5085, 5, id, 1);
		SetCameraBehindPlayer(playerid);
	}
	else
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			if (IsPlayerInVehicle(playerid, tmpcar))
			{
				SetPlayerVirtualWorld(playerid, id);
				SetPlayerInterior(playerid, 5);
				SetVehicleVirtualWorld(tmpcar, id);
				SetVehicleInterior(tmpcar, 5);
				SetVehiclePos(tmpcar, -847.7791,-1724.6656,46.2458);
				SetVehicleZAngle(tmpcar, 211.0195);
				SetCameraBehindPlayer(playerid);
				foreach(new p: Player) if (IsPlayerInVehicle(p,GetPlayerVehicleID(playerid)))
				{
					SetPlayerInterior(p, 5);
					SetPlayerVirtualWorld(p, id);
				}
			}
		}
	}
	return 1;
}

cmd:gsalir(playerid)
{
	new id = -1, Float: extX, Float: extY, Float: extZ, Float: extR, Float: vehX, Float: vehY, Float: vehZ, Float: vehR;
	if (IsPlayerInRangeOfPoint(playerid, 15.0, -847.7791,-1724.6656,46.2458) && GetPlayerVirtualWorld(playerid) == 1) id = 1; // pd
	else if (IsPlayerInRangeOfPoint(playerid, 15.0, -847.7791,-1724.6656,46.2458) && GetPlayerVirtualWorld(playerid) == 2) id = 2; // sd
	else if (IsPlayerInRangeOfPoint(playerid, 15.0, -847.7791,-1724.6656,46.2458) && GetPlayerVirtualWorld(playerid) == 3) id = 3; // fbi
	else if (IsPlayerInRangeOfPoint(playerid, 15.0, -847.7791,-1724.6656,46.2458) && GetPlayerVirtualWorld(playerid) == 4) id = 4; // fd
	else if (IsPlayerInRangeOfPoint(playerid, 15.0, -847.7791,-1724.6656,46.2458) && GetPlayerVirtualWorld(playerid) == 5) id = 5; // sadoc
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en ninguna salida de estacionamiento.");
	switch (id)
	{
		case 1:
		{
			vehX = 2780.1606, vehY = -1444.1877, vehZ = 30.4491, vehR = 180.0000;
			extX = 2776.1614, extY = -1439.1371, extZ = 30.4927, extR = 180.0000;
		}
		case 2:
		{
			vehX = 624.4334, vehY = -604.5157, vehZ = 16.6686, vehR = 301.1805;
			extX = 618.9147, extY = -601.7184, extZ = 17.2382, extR = 270.7610;
		}
		case 3:
		{
			vehX = 1505.3354, vehY = -1242.5944, vehZ = 14.2322, vehR = 21.9000;
			extX = 1502.4017, extY = -1248.0347, extZ = 14.6062, extR = 0.0000;
		}
		case 4:
		{
			vehX = 1140.2589, vehY = -1328.7355, vehZ = 13.4052, vehR = 1.5600;
			extX = 1144.2094, extY = -1333.8014, extZ = 13.7370, extR = 90.000;
		}
		case 5:
		{
			vehX = 1790.3801, vehY = -1595.7080, vehZ = 13.2206, vehR = 187.8169;
			extX = 1785.1676, extY = -1593.4481, extZ = 13.4798, extR = 223.0013;
		}
	}
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		SetPosEx(playerid, extX, extY, extZ, extR, 0, 0, 1);
		SetCameraBehindPlayer(playerid);
	}
	else
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new tmpcar = GetPlayerVehicleID(playerid);
			if (IsPlayerInVehicle(playerid, tmpcar))
			{
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				SetVehicleVirtualWorld(tmpcar, 0);
				SetVehicleInterior(tmpcar, 0);
				SetVehiclePos(tmpcar, vehX, vehY, vehZ);
				SetVehicleZAngle(tmpcar, vehR);
				SetCameraBehindPlayer(playerid);
				foreach(new p: Player) if (IsPlayerInVehicle(p,GetPlayerVehicleID(playerid)))
				{
					SetPlayerInterior(p, 0);
					SetPlayerVirtualWorld(p, 0);
				}
			}
		}
	}
	return 1;
}

cmd:anticheat(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new dialog[1028], gformat[170];
	strcat(dialog, "Cheat\tStatus\n");
	format(gformat, sizeof gformat, "{EFEFEF}Armas\t%s\n", OnCheat(cheat_weapons)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Balas\t%s\n", OnCheat(cheat_balas)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Vehicle spawning\t%s\n", OnCheat(cheat_VehicleSpawning)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Vehicle teleport (type 1)\t%s\n", OnCheat(cheat_Vehicle1teleport)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Vehicle teleport (type 2)\t%s\n", OnCheat(cheat_Vehicle2teleport)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Player teleport\t%s\n", OnCheat(cheat_PlayerTeleport)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Granjero teleport\t%s\n", OnCheat(cheat_TPgranjero)); strcat(dialog, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Multi-IP\t%s\n", OnCheat(cheat_IPS)); strcat(dialog, gformat);
	Dialog_Show(playerid, ShowAntiCheat, DIALOG_STYLE_TABLIST_HEADERS, "{F80101}uwu anticheat", dialog, "Continuar", "Salir");
	return 1;
}

OnCheat(x)
{
	new name[32];
	if (x == 1) alm(name, "{00BB00}activado");
	else alm(name, "{E01005}desactivado");
	return name;
}

Dialog:ShowAntiCheat(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			if (cheat_weapons != 0) cheat_weapons = 0;
			else cheat_weapons = 1;
			pc_cmd_anticheat(playerid);
		}
		case 1:
		{
			if (cheat_balas != 0) cheat_balas = 0;
			else cheat_balas = 1;
			pc_cmd_anticheat(playerid);
		}
		case 2:
		{
			if (cheat_VehicleSpawning != 0) cheat_VehicleSpawning = 0;
			else cheat_VehicleSpawning = 1;
			pc_cmd_anticheat(playerid);
		}
		case 3:
		{
			if (cheat_Vehicle1teleport != 0) cheat_Vehicle1teleport = 0;
			else cheat_Vehicle1teleport = 1;
			pc_cmd_anticheat(playerid);
		}
		case 4:
		{
			if (cheat_Vehicle2teleport != 0) cheat_Vehicle2teleport = 0;
			else cheat_Vehicle2teleport = 1;
			pc_cmd_anticheat(playerid);
		}
		case 5:
		{
			if (cheat_PlayerTeleport != 0) cheat_PlayerTeleport = 0;
			else cheat_PlayerTeleport = 1;
			pc_cmd_anticheat(playerid);
		}
		case 6:
		{
			if (cheat_TPgranjero != 0) cheat_TPgranjero = 0;
			else cheat_TPgranjero = 1;
			pc_cmd_anticheat(playerid);
		}
		case 7:
		{
			if (cheat_IPS != 0) cheat_IPS = 0;
			else cheat_IPS = 1;
			pc_cmd_anticheat(playerid);
		}
	}
	return 1;
}


cmd:taller(playerid)
{
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	if (InfoNegocio[id][nSeguro] == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este taller mecánico está cerrado.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar dentro de un vehículo como conductor.");
	new dialog_taller[2056], gformat[256];
	strcat(dialog_taller, "Servicio\tPrecio\n");
	new Float: cvida, idcoche = GetPlayerVehicleID(playerid);
	GetVehicleHealth(idcoche, cvida);
	//reparacion
	if (cvida >= 920) format(gformat, sizeof gformat, "{EFEFEF}Reparación\t{fff000}no necesita\n");
	else format(gformat, sizeof gformat, "{EFEFEF}Reparación\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioReparacion], 1)));
	strcat(dialog_taller, gformat);
	//pintura
	format(gformat, sizeof gformat, "{EFEFEF}Pintura\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioPintura], 1)));
	strcat(dialog_taller, gformat);
	//gasolina
	if (veh_gasolina[idcoche] >= 100) format(gformat, sizeof gformat, "{EFEFEF}Gasolina: 40 litros\t{fff000}no necesita\n");
	else format(gformat, sizeof gformat, "{EFEFEF}Gasolina: 100 litros\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioGasolina], 1)));
	strcat(dialog_taller, gformat);
	//tuneo
	format(gformat, sizeof gformat, "{EFEFEF}Tuneo chasis\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioTuneo], 1)));
	strcat(dialog_taller, gformat);
	//llantas
	format(gformat, sizeof gformat, "{EFEFEF}Juego de llantas\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioLlantas], 1)));
	strcat(dialog_taller, gformat);
	//nitro
	format(gformat, sizeof gformat, "{EFEFEF}Hidráulica\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioHyd], 1)));
	strcat(dialog_taller, gformat);
	//estéreo
	format(gformat, sizeof gformat, "{EFEFEF}Estéreo\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, EstereoCoche, 1)));
	strcat(dialog_taller, gformat);
	//nitro
	if (InfoCuenta[playerid][jVIP] == 2)
	{
		format(gformat, sizeof gformat, "{EFEFEF}Nitro x2 (VIP)\t{00CC00}$%s\n", diner_coma(Descuento_Compra(playerid, InfoNegocio[id][nPrecioNitro], 1)));
		strcat(dialog_taller, gformat);
	}
	//indice
	Dialog_Show(playerid, ShowTaller, DIALOG_STYLE_TABLIST_HEADERS, InfoNegocio[id][nNombre], dialog_taller, "Continuar", "Salir");
	return 1;
}

NoEstaEnTaller(playerid)
{
	new id = IsTallerIn(playerid);
	if (id == 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico."); return 1; }
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) { SendPlayerChatMessage(playerid, COLOR_GREY, "* Usted no es el conductor del vehículo."); return 1; }
	return 0;
}

tiene_componente(componente, vehicleid)
{
	new id = verificar_id_vehiculo(vehicleid);
	if (id == -1) return 0;
	Loop(x, MAX_MODIFICACIONES, 0)
	{
		if (InfoVehiculo[id][vModificacion][x] == componente)
			return 1;
	}
	return 0;
}

forward ShotRepararUwu(playerid);
public ShotRepararUwu(playerid)
{
	if (NoEstaEnTaller(playerid) == 1) return 1;
	new id = IsTallerIn(playerid), vehicleid = GetPlayerVehicleID(playerid), string[190];
	new reparacion = InfoNegocio[id][nPrecioReparacion];
	new Float: cvida;
	GetVehicleHealth(vehicleid, cvida);
	new Percent_damage = floatround(cvida);
	if (Percent_damage >= 920) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El health (/dl) del vehículo pasa los 920.");
	if (GetPlayerCash(playerid) < reparacion) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(reparacion)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
	RepairVehicle(vehicleid);
	if (GetVehicleModel(vehicleid) == 528 || GetVehicleModel(vehicleid) == 427) SetVehicleHealth(vehicleid, 5000.0);
	else SetVehicleHealth(vehicleid, 920.0);
	GivePlayerCash(playerid, -reparacion, "servicio reparación (npc)");
	rol_ame(playerid, "paga por la reparación de su vehículo.");
	if (InfoNegocio[id][nVenta] != 0)
	{
		InfoNegocio[id][nDinero] += reparacion;
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
	}
	return 1;
}

Dialog:ShowTaller(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (NoEstaEnTaller(playerid) == 1) return 1;
	new id = IsTallerIn(playerid), vehicleid = GetPlayerVehicleID(playerid), string[190];
	new
		reparacion = Descuento_Compra(playerid, InfoNegocio[id][nPrecioReparacion], 1),
		gasolina = Descuento_Compra(playerid, InfoNegocio[id][nPrecioGasolina], 1),
		pintura = Descuento_Compra(playerid, InfoNegocio[id][nPrecioPintura], 1)
	;
	switch (listitem)
	{
		case 0: //reparación
		{
			new Float: cvida;
			GetVehicleHealth(vehicleid, cvida);
			new Percent_damage = floatround(cvida);
			if (Percent_damage >= 920) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El health (/dl) del vehículo pasa los 920.");
			if (GetPlayerCash(playerid) < reparacion) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(reparacion)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
			SetTimerEx("ShotRepararUwu", 9000, false, "d", playerid);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Están reparando tu vehículo . . .");
		}
		case 1:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			if (GetPlayerCash(playerid) < pintura) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(pintura)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
			ShowVehColor(playerid, "", 1); //color
		}
		case 2:
		{
			if (GetPlayerCash(playerid) < gasolina) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(gasolina)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
			if (veh_gasolina[vehicleid] >= 99) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El tanque de gasolina del vehículo no aguanta más de 200 litros.");
			GivePlayerCash(playerid, -gasolina, "servicio gasolina (npc)");
			veh_gasolina[vehicleid] += 100;
			if (veh_gasolina[vehicleid] >= 100) veh_gasolina[vehicleid] = 200;
			Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
			{
				InfoVehiculo[v][vGasolina] = veh_gasolina[vehicleid];
				guardar_int_mysql("vehiculos", "Gasolina", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vGasolina]);
				break;
			}
			rol_ame(playerid, "paga por el combustible de su vehículo.");
			if (InfoNegocio[id][nVenta] != 0)
			{
				InfoNegocio[id][nDinero] += gasolina;
				guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
			}
		}
		case 3:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			if (!eEnvcvehs(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no se le puede tunear la carrocería.");
			new costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioTuneo], 1);
			if (GetPlayerCash(playerid) < costo)
			{
				format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
				SendPlayerChatMessage(playerid, COLOR_GREY, string);
				return 1;
			}
			Dialog_Show(playerid, Show_TuneoMecanico, DIALOG_STYLE_LIST, "Menú de Tuneo", "- Chasis X-Flow\n- Chasis Alien", "Continuar", "Volver");
		}
		case 4:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			if (EstaEnAvion(vehicleid) || EstaEnBote(vehicleid) || EnMotos_Bicis(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes colocar llantas en ese tipo de vehículo.");
			new costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioLlantas], 1);
			if (GetPlayerCash(playerid) < costo)
			{
				format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
				SendPlayerChatMessage(playerid, COLOR_GREY, string);
				return 1;
			}
			Dialog_Show(playerid, Show_LlantasMecanico, DIALOG_STYLE_LIST, "Menú de llantas",
			"- Offroad Wheels\n\
			- Shadow Wheels\n\
			- Mega Wheels\n\
			- Rimshine Wheels\n\
			- Wires Wheels\n\
			- Classic Wheels\n\
			- Twist Wheels\n\
			- Cutter Wheels\n\
			- Stitch Wheels\n\
			- Grove Wheels\n\
			- Import Wheels\n\
			- Dollar Wheels\n\
			- Trance Wheels\n\
			- Atomic Wheels\n\
			- Ahab Wheels\n\
			- Virtual Wheels\n\
			- Access Wheels", "Continuar", "Volver");
		}
		case 5:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			if (Valid_Vehicle_Nitro(GetVehicleModel(vehicleid)) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no admite componente hidráulica.");
			if (tiene_componente(1087, vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo ya tiene componente hidráulica.");
			new costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioHyd], 1);
			if (GetPlayerCash(playerid) < costo)
			{
				format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
				SendPlayerChatMessage(playerid, COLOR_GREY, string);
				return 1;
			}
			AddVehicleComponent(vehicleid, 1087);
			rol_ame(playerid, "paga la hidráulica de su vehículo.");
			GivePlayerCash(playerid, -costo, "servicio nitro");
			if (InfoNegocio[id][nVenta] != 0)
			{
				InfoNegocio[id][nDinero] += costo;
				guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
			}
		}
		case 6:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			new vid = -1;
			Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
			{
				vid = v;
				break;
			}
			if (vid == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no tiene registros vehicular, contacta a Kiselev");
			if (InfoVehiculo[vid][vStereo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo ya posee un estéreo.");
			new costo = Descuento_Compra(playerid, EstereoCoche, 1);
			if (GetPlayerCash(playerid) < costo)
			{
				format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
				SendPlayerChatMessage(playerid, COLOR_GREY, string);
				return 1;
			}
			rol_ame(playerid, "paga el estéreo de su vehículo.");
			GivePlayerCash(playerid, -costo, "servicio estéreo");
			if (InfoNegocio[id][nVenta] != 0)
			{
				InfoNegocio[id][nDinero] += costo;
				guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
			}
			InfoVehiculo[vid][vStereo] = 1;
			guardar_int_mysql("vehiculos", "Stereo", InfoVehiculo[vid][vID_sql], InfoVehiculo[vid][vStereo]);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Para encender tu estéreo, abarca tu vehículo y abre el maletero para usar /estereo.");
		}
		case 7:
		{
			if (vehiculos_legales(vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se puede modificar vehículos de facciones legales.");
			if (Valid_Vehicle_Nitro(GetVehicleModel(vehicleid)) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no admite componente nitro.");
			if (tiene_componente(1009, vehicleid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo ya tiene componente nitro.");
			new costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioNitro], 1);
			if (GetPlayerCash(playerid) < costo)
			{
				format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
				SendPlayerChatMessage(playerid, COLOR_GREY, string);
				return 1;
			}
			AddVehicleComponent(vehicleid, 1009);
			rol_ame(playerid, "paga el nitro x2 de su vehículo.");
			GivePlayerCash(playerid, -costo, "servicio nitro");
			if (InfoNegocio[id][nVenta] != 0)
			{
				InfoNegocio[id][nDinero] += costo;
				guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
			}
		}
	}
	return 1;
}

Dialog:Show_LlantasMecanico(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_taller(playerid);
	if (NoEstaEnTaller(playerid) == 1) return 1;
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	new costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioLlantas], 1), vehicleid = GetPlayerVehicleID(playerid), string[190];
	if (GetPlayerCash(playerid) < costo)
	{
		format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
		SendPlayerChatMessage(playerid, COLOR_GREY, string);
		return 1;
	}
	new name_llantas[32], rin = -1;
	switch (listitem)
	{
		case 0: rin = 1025, alm(name_llantas, "offroad");
		case 1: rin = 1073, alm(name_llantas, "shadow");
		case 2: rin = 1074, alm(name_llantas, "mega");
		case 3: rin = 1075, alm(name_llantas, "rimshine");
		case 4: rin = 1076, alm(name_llantas, "wires");
		case 5: rin = 1077, alm(name_llantas, "classic");
		case 6: rin = 1078, alm(name_llantas, "twist");
		case 7: rin = 1079, alm(name_llantas, "cutter");
		case 8: rin = 1080, alm(name_llantas, "stitch");
		case 9: rin = 1081, alm(name_llantas, "grove");
		case 10: rin = 1082, alm(name_llantas, "import");
		case 11: rin = 1083, alm(name_llantas, "dollar");
		case 12: rin = 1084, alm(name_llantas, "trance");
		case 13: rin = 1085, alm(name_llantas, "atomic");
		case 14: rin = 1096, alm(name_llantas, "ahab");
		case 15: rin = 1097, alm(name_llantas, "virtual");
		case 16: rin = 1098, alm(name_llantas, "access");
	}
	if (tiene_componente(rin, vehicleid) != 0)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese juego de llantas ya está instalado.");
		return 1;
	}
	AddVehicleComponent(vehicleid, rin);
	if (EsteVehEs(playerid, vehicleid) > -1) { ActualizarMods(EsteVehEs(playerid, vehicleid)); }
	format(string, sizeof string, "paga por el juego de llantas %s de su vehículo.", name_llantas);
	rol_ame(playerid, string);
	GivePlayerCash(playerid, -costo, "servicio llantas");
	if (InfoNegocio[id][nVenta] != 0)
	{
		InfoNegocio[id][nDinero] += costo;
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
	}
	return 1;
}

Dialog:Show_TuneoMecanico(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_taller(playerid);
	if (NoEstaEnTaller(playerid) == 1) return 1;
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	new vehicleid = GetPlayerVehicleID(playerid), string[195], costo = Descuento_Compra(playerid, InfoNegocio[id][nPrecioTuneo], 1);
	if (GetPlayerCash(playerid) < costo)
	{
		format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(costo));
		SendPlayerChatMessage(playerid, COLOR_GREY, string);
		return 1;
	}
	new name_tuneo[32];
	switch (listitem)
	{
		case 0: alm(name_tuneo, "chasis x-flow");
		case 1: alm(name_tuneo, "chasis alien");
	}
	AplicarTuneo(vehicleid, listitem);
	if (EsteVehEs(playerid, vehicleid) > -1) { ActualizarMods(EsteVehEs(playerid, vehicleid)); }
	format(string, sizeof string, "paga por el %s de su vehículo.", name_tuneo);
	rol_ame(playerid, string);
	GivePlayerCash(playerid, -costo, "servicio tuneo");
	if (InfoNegocio[id][nVenta] != 0)
	{
		InfoNegocio[id][nDinero] += costo;
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
	}
	return 1;
}

AplicarTuneo(idcar, type)
{
	if (type == 0)
	{
		switch (GetVehicleModel(idcar))
		{
			case 560:
			{
				AddVehicleComponent(idcar, 1030);
				AddVehicleComponent(idcar, 1033);
				AddVehicleComponent(idcar, 1140);
				AddVehicleComponent(idcar, 1170);
				AddVehicleComponent(idcar, 1029);
				AddVehicleComponent(idcar, 1139);
			}
			case 562:
			{
				AddVehicleComponent(idcar, 1039);
				AddVehicleComponent(idcar, 1035);
				AddVehicleComponent(idcar, 1148);
				AddVehicleComponent(idcar, 1172);
				AddVehicleComponent(idcar, 1037);
				AddVehicleComponent(idcar, 1146);
			}
			case 565:
			{
				AddVehicleComponent(idcar, 1048);
				AddVehicleComponent(idcar, 1053);
				AddVehicleComponent(idcar, 1050);
				AddVehicleComponent(idcar, 1151);
				AddVehicleComponent(idcar, 1152);
				AddVehicleComponent(idcar, 1045);
			}
			case 559:
			{
				AddVehicleComponent(idcar, 1070);
				AddVehicleComponent(idcar, 1068);
				AddVehicleComponent(idcar, 1158);
				AddVehicleComponent(idcar, 1161);
				AddVehicleComponent(idcar, 1173);
				AddVehicleComponent(idcar, 1066);
			}
			case 561:
			{
				AddVehicleComponent(idcar, 1057);
				AddVehicleComponent(idcar, 1061);
				AddVehicleComponent(idcar, 1060);
				AddVehicleComponent(idcar, 1156);
				AddVehicleComponent(idcar, 1157);
				AddVehicleComponent(idcar, 1059);
			}
			case 558:
			{
				AddVehicleComponent(idcar, 1093);
				AddVehicleComponent(idcar, 1091);
				AddVehicleComponent(idcar, 1163);
				AddVehicleComponent(idcar, 1167);
				AddVehicleComponent(idcar, 1165);
				AddVehicleComponent(idcar, 1089);
			}
		}
	}
	else if (type == 1)
	{
		switch (GetVehicleModel(idcar))
		{
			case 560:
			{
				AddVehicleComponent(idcar, 1026);
				AddVehicleComponent(idcar, 1032);
				AddVehicleComponent(idcar, 1138);
				AddVehicleComponent(idcar, 1141);
				AddVehicleComponent(idcar, 1169);
				AddVehicleComponent(idcar, 1028);
			}
			case 562:
			{
				AddVehicleComponent(idcar, 1036);
				AddVehicleComponent(idcar, 1038);
				AddVehicleComponent(idcar, 1149);
				AddVehicleComponent(idcar, 1171);
				AddVehicleComponent(idcar, 1034);
				AddVehicleComponent(idcar, 1147);
			}
			case 565:
			{
				AddVehicleComponent(idcar, 1047);
				AddVehicleComponent(idcar, 1054);
				AddVehicleComponent(idcar, 1049);
				AddVehicleComponent(idcar, 1150);
				AddVehicleComponent(idcar, 1153);
				AddVehicleComponent(idcar, 1046);
			}
			case 559:
			{
				AddVehicleComponent(idcar, 1069);
				AddVehicleComponent(idcar, 1067);
				AddVehicleComponent(idcar, 1162);
				AddVehicleComponent(idcar, 1159);
				AddVehicleComponent(idcar, 1160);
				AddVehicleComponent(idcar, 1065);
			}
			case 561:
			{
				AddVehicleComponent(idcar, 1056);
				AddVehicleComponent(idcar, 1055);
				AddVehicleComponent(idcar, 1058);
				AddVehicleComponent(idcar, 1154);
				AddVehicleComponent(idcar, 1153);
				AddVehicleComponent(idcar, 1064);
			}
			case 558:
			{
				AddVehicleComponent(idcar, 1094);
				AddVehicleComponent(idcar, 1088);
				AddVehicleComponent(idcar, 1164);
				AddVehicleComponent(idcar, 1168);
				AddVehicleComponent(idcar, 1166);
				AddVehicleComponent(idcar, 1092);
			}
		}
	}
	return 1;
}

ShowVehColor(playerid, msg[] = "", color)
{
	if (NoEstaEnTaller(playerid) == 1) return 1;
	new color_string[3256];
	if (strlen(msg)) format(color_string, sizeof(color_string), "{E74C3C}%s\n\n", msg);
	for(new i; i < sizeof(ColorList); i++) format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 10 == 0) ? ("\n") : (""));
	if (color == 1) Dialog_Show(playerid, Change1ColorVeh, DIALOG_STYLE_INPUT, "Escoge el color número 1", color_string, "Continuar", "Volver");
	else if (color == 2)  Dialog_Show(playerid, Change2ColorVeh, DIALOG_STYLE_INPUT, "Escoge el color número 2", color_string, "Continuar", "Volver");
	return 1;
}

new colorvehselec[MAX_PLAYERS];

Dialog:Change1ColorVeh(playerid, response, listitem, inputtext[])
{
	if (NoEstaEnTaller(playerid) == 1) return 1;
	if (!response) return pc_cmd_taller(playerid);
	new id = IsTallerIn(playerid);
	new pintura = Descuento_Compra(playerid, InfoNegocio[id][nPrecioPintura], 1), string[170];
	if (GetPlayerCash(playerid) < pintura) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(pintura)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
	if (!isnumeric(inputtext)) return ShowVehColor(playerid, "ID del color inválido.", 1);
	new color = strval(inputtext);
	if(!(0 <= color <= sizeof(ColorList)-1)) return ShowVehColor(playerid, "ID del color inválido.", 1);
	colorvehselec[playerid] = color;
	ShowVehColor(playerid, "", 2);
	return 1;
}

Dialog:Change2ColorVeh(playerid, response, listitem, inputtext[])
{
	if (NoEstaEnTaller(playerid) == 1) return 1;
	if (!response) return ShowVehColor(playerid, "", 1); //color
	new id = IsTallerIn(playerid);
	new pintura = Descuento_Compra(playerid, InfoNegocio[id][nPrecioPintura], 1), string[170];
	if (GetPlayerCash(playerid) < pintura) { format(string, sizeof string, "* No tienes suficiente dinero ($%s).", diner_coma(pintura)); SendPlayerChatMessage(playerid, COLOR_GREY, string); return 1; }
	if (!isnumeric(inputtext)) return ShowVehColor(playerid, "ID del color inválido.", 2);
	new color1 = colorvehselec[playerid], color2 = strval(inputtext);
	if(!(0 <= color2 <= sizeof(ColorList)-1)) return ShowVehColor(playerid, "ID del color inválido.", 2);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Están pintando tu vehículo (60 segundos) . . .");
	SetTimerEx("ShotPintarUwu", 60000, false, "dddddd", playerid, GetPlayerVehicleID(playerid), color1, color2, pintura, id);
	return 1;
}

forward ShotPintarUwu(playerid, vehicleid, color1, color2, pintura, id);
public ShotPintarUwu(playerid, vehicleid, color1, color2, pintura, id)
{
	if (NoEstaEnTaller(playerid) == 1) return 1;
	if (vehicleid == 0) return 1;
	if (!IsPlayerConnectedEx(playerid)) return 1;
	if (GetPlayerCash(playerid) < pintura) { SendClientMessageEx(playerid, COLOR_GREY, "* No tienes suficiente dinero ($%s).", diner_coma(pintura)); return 1; }
	ChangeVehicleColor(vehicleid, color1, color2);
	SendPlayerChatMessage(playerid, ColorList[color1], "** Cambiaste el color del vehículo **");
	GivePlayerCash(playerid, -pintura, "servicio pintura (npc)");
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		InfoVehiculo[v][vColor_1] = color1;
		InfoVehiculo[v][vColor_2] = color2;
		guardar_int_mysql("vehiculos", "Color_1", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vColor_1]);
		guardar_int_mysql("vehiculos", "Color_2", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vColor_2]);
		break;
	}
	rol_ame(playerid, "paga por la pintura de su vehículo.");
	if (InfoNegocio[id][nVenta] != 0)
	{
		InfoNegocio[id][nDinero] += pintura;
		guardar_int_mysql("negocios", "BolosUwU", InfoNegocio[id][nID_sql], InfoNegocio[id][nDinero]);
	}
	return 1;
}

cmd:estiloanuncio(playerid)
{
	if (InfoCuenta[playerid][jEstiloAnuncio] != 0)
	{
		InfoCuenta[playerid][jEstiloAnuncio] = 0;
		if (InfoPersonaje[playerid][pTogAnuncios] == 0)
		{
			new numer = PlayerViewAnunce[playerid];
			if (numer != 0)
			{
				Loop(x, numer, 0) { TextDrawShowForPlayer(playerid, TD_Anuncio[x]); }
			}
		}
		Notification_Show(playerid, "Ahora verás los siguientes anuncios en ~b~~h~pantalla~w~.", 5000);
	}
	else
	{
		InfoCuenta[playerid][jEstiloAnuncio] = 1;
	    Loop(x, 5, 0) { TextDrawHideForPlayer(playerid, TD_Anuncio[x]); }
		Notification_Show(playerid, "Ahora verás los siguientes anuncios en ~b~~h~chat~w~.", 5000);
	}
	guardar_int_mysql("cuentas", "EstiloAnuncio", InfoCuenta[playerid][jID], InfoCuenta[playerid][jEstiloAnuncio]);
	return 1;
}
alias:estiloanuncio("estiloanuncios");

cmd:togad(playerid)
{
	if (Act_Inventario[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes utilizar este comando mientras tengas el inventario activo.");
	if (InfoPersonaje[playerid][pTogAnuncios] != 0)
	{
		new numer = PlayerViewAnunce[playerid];
		if (numer != 0)
		{
			Loop(x, numer, 0) { TextDrawShowForPlayer(playerid, TD_Anuncio[x]); }
		}
		InfoPersonaje[playerid][pTogAnuncios] = 0;
		Notification_Show(playerid, "Ahora ~b~~h~puedes ver~w~ los anuncios de publicidad.", 5000);
	}
	else
	{
	    Loop(x, 5, 0) { TextDrawHideForPlayer(playerid, TD_Anuncio[x]); }
		InfoPersonaje[playerid][pTogAnuncios] = 1;
		Notification_Show(playerid, "Ahora ~r~~h~no verás~w~ los anuncios de publicidad.", 5000);
	}
	guardar_int_mysql("personajes", "TogAnuncios", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTogAnuncios]);
	return 1;
}
alias:togad("togads", "toganuncio", "toganuncios");

Dialog:MenuAplicaciones(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_telefono(playerid);
	switch (listitem)
	{
		case 0:
		{
		    if (InfoPersonaje[playerid][pTogMusic] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Posees los audios de música deshabilitados, usa /togmusic.");
			new StationsDialog[1560];
			strcat(StationsDialog, "{fff400}Detener audio de música\n");
			strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
			strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electrónica{EBEBEB})\n");
			strcat(StationsDialog, "{FF0000}Agregar un url de internet .mp3");
			Dialog_Show(playerid, PlayMusic, DIALOG_STYLE_LIST, "Radios", StationsDialog, "Continuar", "Volver");
		}
		case 1: pc_cmd_agenda(playerid);
		case 2: pc_cmd_transferir(playerid);
		case 3:
		{
			new showdialog[1028] = "Empleo\tContratados\n", gstring[210];
			format(gstring, sizeof gstring, "{FFFFFF}%s\t{54C822}%d\n", GetNameContrato(1), GetEmpleados1Job(1)+GetEmpleados2Job(1)+GetEmpleados3Job(1));
			strcat(showdialog, gstring);
			format(gstring, sizeof gstring, "{FFFFFF}%s\t{54C822}%d\n", GetNameContrato(2), GetEmpleados1Job(2)+GetEmpleados2Job(2)+GetEmpleados3Job(2));
			strcat(showdialog, gstring);
			format(gstring, sizeof gstring, "{FFFFFF}%s\t{54C822}%d\n", GetNameContrato(3), GetEmpleados1Job(3)+GetEmpleados2Job(3)+GetEmpleados3Job(3));
			strcat(showdialog, gstring);
			format(gstring, sizeof gstring, "{FFFFFF}%s\t{54C822}%d\n", GetNameContrato(4), GetEmpleados1Job(4)+GetEmpleados2Job(4)+GetEmpleados3Job(4));
			strcat(showdialog, gstring);
			format(gstring, sizeof gstring, "{FFFFFF}%s\t{54C822}%d\n", GetNameContrato(5), GetEmpleados1Job(5)+GetEmpleados2Job(5)+GetEmpleados3Job(5));
			strcat(showdialog, gstring);
			Dialog_Show(playerid, JobTelefono, DIALOG_STYLE_TABLIST_HEADERS, "Opción: {FE9A2E}Empleos disponibles", showdialog, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:PlayMusic(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		if (IsPlayerContrato(playerid, 1) != 0) Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {FE9A2E}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
		else Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {FE9A2E}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
		return 1;
	}
	switch (listitem)
	{
		case 0: { StopAudioStreamForPlayer(playerid); TipoAudio[playerid] = 0; }
		case 1: { PlayAudioStreamForPlayer(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1652147"); TipoAudio[playerid] = 2; }
		case 2: { PlayAudioStreamForPlayer(playerid, "http://148.251.91.15:7004"); TipoAudio[playerid] = 2; }
		case 3: { PlayAudioStreamForPlayer(playerid, "http://173.244.215.163:8380"); TipoAudio[playerid] = 2; }
		case 4: { PlayAudioStreamForPlayer(playerid, "http://64.202.98.133:2010"); TipoAudio[playerid] = 2; }
		case 5: { PlayAudioStreamForPlayer(playerid, "http://50.117.115.211:80"); TipoAudio[playerid] = 2; }
		case 6: { PlayAudioStreamForPlayer(playerid, "http://108.61.30.179:4010"); TipoAudio[playerid] = 2; }
		case 7: { PlayAudioStreamForPlayer(playerid, "http://50.7.64.226:80/frisky_mp3_hi"); TipoAudio[playerid] = 2; }
		case 8: { PlayAudioStreamForPlayer(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1747543"); TipoAudio[playerid] = 2; }
		case 9: { PlayAudioStreamForPlayer(playerid, "http://62.210.209.179:8030/stream"); TipoAudio[playerid] = 2; }
		case 10: { PlayAudioStreamForPlayer(playerid, "http://yp.shoutcast.com/sbin/tunein-station.pls?id=1316323"); TipoAudio[playerid] = 2; }
		case 11: { PlayAudioStreamForPlayer(playerid, "http://somafm.com/tags.pls"); TipoAudio[playerid] = 2; }
		case 12: { PlayAudioStreamForPlayer(playerid, "http://listen.shoutcast.com:80/RadioHunter-TheHitzChannel"); TipoAudio[playerid] = 2; }
		case 13: Dialog_Show(playerid, Play2Music, DIALOG_STYLE_INPUT, "URL internet", "{EBEBEB}Inserta un Stream ({FE9A2E}www.offliberty.com{EBEBEB}) para reproducirlo", "Continuar", "Volver");
	}
	return 1;
}

Dialog:Play2Music(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		new StationsDialog[1560];
		strcat(StationsDialog, "{fff400}Detener audio de música\n");
		strcat(StationsDialog, "{EBEBEB}Top Latino ({22FF00}Variado{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Dubbase.FM ({22FF00}Dubstep{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Soft Rock Cafe ({22FF00}Heavy Metal{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Aural Moon ({22FF00}Punk{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Idobi Radio ({22FF00}Electronic{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}www.Hot108.com ({22FF00}Hip Hop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Sensacion Peru ({22FF00}Pop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}DEEGAY RADIO ({22FF00}Dance Pop{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}PaganMetalRadio ({22FF00}Extreme Metal{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}PulsRadio TRANCE ({22FF00}Eletronic{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}The Trip ({22FF00}Music Usa{EBEBEB})\n");
		strcat(StationsDialog, "{EBEBEB}Radio Hunter ({22FF00}Electrónica{EBEBEB})\n");
		strcat(StationsDialog, "{FF0000}Agregar un url de internet .mp3");
		Dialog_Show(playerid, PlayMusic, DIALOG_STYLE_LIST, "Radios", StationsDialog, "Continuar", "Volver");
		return 1;
	}
	if (isnull(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No has introducido ningún URL.");
	PlayAudioStreamForPlayer(playerid, inputtext);
	TipoAudio[playerid] = 2;
	return 1;
}

Dialog:JobTelefono(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		if (IsPlayerContrato(playerid, 1) != 0) Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {FE9A2E}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
		else Dialog_Show(playerid, MenuAplicaciones, DIALOG_STYLE_LIST, "Opción: {FE9A2E}Aplicaciones", "- Play Music\n- Contactos\n- Transferencias express\n- Empleos disponibles", "Continuar", "Volver");
		return 1;
	}
	new gstring[294], id_job=listitem+1;
	if (InfoPersonaje[playerid][pSexo] != 2 && id_job == 4) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo sexo femenino puede tomar este trabajo.");
	//ceder trabajo
	if (InfoPersonaje[playerid][pTrabajo1] == -1)
	{
	    if (InfoPersonaje[playerid][pTrabajo2] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 2.");
		InfoPersonaje[playerid][pTrabajo1] = id_job;
		format(gstring, sizeof gstring, "Has conseguido el empleo(1) de {FE9A2E}%s{FFFFFF}. Utiliza ({3E62F4}/ayuda empleos{FFFFFF})",  GetNameContrato(id_job));
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, gstring);
		Notification_Show(playerid, "Si quieres saber la ubicación exacta de este trabajo, utiliza /base.", 5000);
		guardar_int_mysql("personajes", "Trabajo1", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTrabajo1]);
	}
	else
	{
		if (InfoCuenta[playerid][jVIP] != 0)
		{
			if (InfoPersonaje[playerid][pTrabajo2] == -1)
			{
			    if (InfoPersonaje[playerid][pTrabajo1] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 1.");
				if (InfoPersonaje[playerid][pTrabajo3] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 3.");
				InfoPersonaje[playerid][pTrabajo2] = id_job;
				format(gstring, sizeof gstring, "Has conseguido el empleo(2) de {FE9A2E}%s{FFFFFF}. Utiliza ({3E62F4}/ayuda empleos{FFFFFF})",  GetNameContrato(id_job));
				SendPlayerChatMessage(playerid, 0xFFFFFFFF, gstring);
				Notification_Show(playerid, "Si quieres saber la ubicación exacta de este trabajo, utiliza /base.", 5000);
				guardar_int_mysql("personajes", "Trabajo2", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTrabajo2]);
			}
			else
			{
				if (InfoPersonaje[playerid][pTrabajo3] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes tres ranuras de empleo en uso, utiliza /dejarempleo.");
			    if (InfoPersonaje[playerid][pTrabajo1] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 1.");
				if (InfoPersonaje[playerid][pTrabajo2] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 2.");
				InfoPersonaje[playerid][pTrabajo3] = id_job;
				format(gstring, sizeof gstring, "Has conseguido el empleo(3) de {FE9A2E}%s{FFFFFF}. Utiliza ({3E62F4}/ayuda empleos{FFFFFF})",  GetNameContrato(id_job));
				SendPlayerChatMessage(playerid, 0xFFFFFFFF, gstring);
				Notification_Show(playerid, "Si quieres saber la ubicación exacta de este trabajo, utiliza /base.", 5000);
				guardar_int_mysql("personajes", "Trabajo3", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTrabajo3]);
			}
		}
		else // sin vip
		{
			if (InfoPersonaje[playerid][pTrabajo2] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ambas ranuras de empleo en uso, utiliza /dejarempleo.");
		    if (InfoPersonaje[playerid][pTrabajo1] == id_job) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya tienes ese empleo, utiliza /dejarempleo 1.");
			InfoPersonaje[playerid][pTrabajo2] = id_job;
			format(gstring, sizeof gstring, "Has conseguido el empleo(2) de {FE9A2E}%s{FFFFFF}. Utiliza ({3E62F4}/ayuda empleos{FFFFFF})",  GetNameContrato(id_job));
			SendPlayerChatMessage(playerid, 0xFFFFFFFF, gstring);
			Notification_Show(playerid, "Si quieres saber la ubicación exacta de este trabajo, utiliza /base.", 5000);
			guardar_int_mysql("personajes", "Trabajo2", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTrabajo2]);
		}
	}
	return 1;
}

cmd:gtaller(playerid)
{
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, -807.5030, -1755.6345, 46.5406)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca del taller policial.");
	if (!member_faccion(playerid, 1, 2, 3, 4, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de LSPD, LSCSD, LSFD, FBI o USMC.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser el conductor un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (!Vehiculo_LSPD(vehicleid) && !Vehiculo_FBI(vehicleid) && !Vehiculo_LSCSD(vehicleid) && !Vehiculo_LSFD(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar dentro de un vehículo LSPD, LSCSD, LSFD o FBI.");
	Dialog_Show(playerid, TallerPolicial, DIALOG_STYLE_LIST, "{D6E1EB}Taller policial", "Motor + Carrocería\n200 litros de gasolina", "Seleccionar", "Salir");
	return 1;
}
alias:gtaller("tallerpd");

Dialog:TallerPolicial(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (!IsPlayerInRangeOfPoint(playerid, 5.0, -807.5030, -1755.6345, 46.5406)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca del taller policial.");
	if (!member_faccion(playerid, 1, 2, 3, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de LSPD, LSCSD, LSFD, FBI o USMC.");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser el conductor un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (!Vehiculo_LSPD(vehicleid) && !Vehiculo_FBI(vehicleid) && !Vehiculo_LSCSD(vehicleid) && !Vehiculo_LSFD(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar dentro de un vehículo LSPD, LSCSD, LSFD o FBI.");
	switch (listitem)
	{
		case 0: //reparación
		{
			new Float: cvida;
			GetVehicleHealth(vehicleid, cvida);
			if (cvida >= 990.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El health (/dl) del vehículo pasa los 990.");
			RepairVehicle(vehicleid);
			if (GetVehicleModel(vehicleid) == 528 || GetVehicleModel(vehicleid) == 427) SetVehicleHealth(vehicleid, 5000.0);
			else SetVehicleHealth(vehicleid, 1000.0);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Vehículo reparado.");
		}
		case 1:
		{
			if (veh_gasolina[vehicleid] >= 99) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El tanque de gasolina del vehículo no aguanta más de 200 litros.");
			veh_gasolina[vehicleid] = 100;
			Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
			{
				InfoVehiculo[v][vGasolina] = veh_gasolina[vehicleid];
				guardar_int_mysql("vehiculos", "Gasolina", InfoVehiculo[v][vID_sql], InfoVehiculo[v][vGasolina]);
				break;
			}
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Combustible full.");
		}
	}
	return 1;
}

cmd:adminfac(playerid)
{
	if (InfoCuenta[playerid][jEncFac] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes variables de encargado de facciones.");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "/facciones - /crearfaccion - /statusfacc - /facchat - /supervisar - /hacerlider - /hacersublider");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "/borrarfaccion - /darmiembro - /limpiarfaccion - /editarfnombre - /editarfequipo - /qfaccoff");
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "/editarfaccion - /editarflogo - /editarflider - /editarfsublider - /editarfskin");
	return 1;
}
alias:adminfac("adminfacciones");

cmd:borraranuncios(playerid)
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new count = 0, string[190];
	if (strcmp(AnunceString1, "none", true) == 0) { } else { count++; }
	if (strcmp(AnunceString2, "none", true) == 0) { } else { count++; }
	if (strcmp(AnunceString3, "none", true) == 0) { } else { count++; }
	if (strcmp(AnunceString4, "none", true) == 0) { } else { count++; }
	if (count != 0)
	{
		AnunceID = 0;
		alm(AnunceString1, "none");
		alm(AnunceString2, "none");
		alm(AnunceString3, "none");
		alm(AnunceString4, "none");
		Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
		{
			PlayerViewAnunce[playerid2] = 0;
			Loop(x, 5, 0) { TextDrawHideForPlayer(playerid2, TD_Anuncio[x]); }
		}
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) borró %d anuncios.", InfoCuenta[playerid][jNombre], playerid, count);
		SendAdminMessage(0xFFFFFFFF, string);
		DiferenciaAnuncio = gettime();
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay ningún anuncio publicado.");
	return 1;
}

cmd:ads(playerid)
{
	if (InfoPersonaje[playerid][pHorasOn] < 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes jugar al menos tres horas el servidor para enviar anuncios.");
	if (InfoPersonaje[playerid][pSancionado] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás en prisión.");
	new string[190], d_anuncie[1028];
	if (InfoPersonaje[playerid][pTimerAnuncios] != 0)
	{
		format(string, sizeof string, "Debes esperar %d minutos para enviar otro anuncio.", InfoPersonaje[playerid][pTimerAnuncios]);
		SendPlayerChatMessage(playerid, COLOR_GREY, string);
		return 1;
	}
	if (tiene_objeto(playerid, 50) == 0) return 1;
	if (GetPlayerCash(playerid) < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficiente dinero ($2).");
	if (!CheckTimer(60, DiferenciaAnuncio))
	{
		strcat(d_anuncie, "Tipo\tUso\n");
		strcat(d_anuncie, "{4cc61a}COMERCIO\t{EBEBEB}Compras/ventas/alquileres o similares.\n");
		strcat(d_anuncie, "{4cc61a}EVENTOS\t{EBEBEB}Para anunciar eventos.\n");
		strcat(d_anuncie, "{4cc61a}SORTEOS\t{EBEBEB}Para anunciar sorteos.\n");
		strcat(d_anuncie, "{4cc61a}EMPLEOS\t{EBEBEB}Para buscar o ofrecer empleo.\n");
		strcat(d_anuncie, "{4cc61a}SERVICIOS\t{EBEBEB}Para buscar o ofrecer servicios.");
		Dialog_Show(playerid, ShowAnuncio, DIALOG_STYLE_TABLIST_HEADERS, "Elige el tipo de anuncio a enviar", d_anuncie, "Continuar", "Salir");
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(60, DiferenciaAnuncio) ));
	}
	return 1;
}
alias:ads("anuncio", "anuncios");

Dialog:ShowAnuncio(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new tipo = listitem+1, string[512];
	new name_tipo[32];
	switch (tipo)
	{
		case 1: name_tipo = "Comercio";
		case 2: name_tipo = "Eventos";
		case 3: name_tipo = "Sorteos";
		case 4: name_tipo = "Empleos";
		case 5: name_tipo = "Servicios";
	}
	if (GetPlayerCash(playerid) < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficiente dinero ($2).");
	tipo_anuncio[playerid] = tipo;
	format(string, sizeof string, "{EBEBEB}Bien has elegido el tipo {eb4040}%s{EBEBEB}.\n\nA continuación escribe el enunciado a publicar:", name_tipo);
	Dialog_Show(playerid, Show2Anuncio, DIALOG_STYLE_INPUT, "Anuncio global", string, "Enviar", "Volver");
	return 1;
}

Dialog:Show2Anuncio(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_ads(playerid);
	if (!strlen(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No escribiste nada, intentalo de nuevo.");
	if (strlen(inputtext) > 65 || strlen(inputtext) < 10)
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes escribir un anuncio con menos de 10 carácteres ni mayor a 64 carácteres.");
		return 1;
	}
	if (!IsValidCaracterAnunce(inputtext))
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Su anuncio sólo puede contener letras, números y estos simbolos '[].,_()$'.");
		return 1;
	}
	if (GetPlayerCash(playerid) < 50) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes suficiente dinero ($50).");
	new tipo = tipo_anuncio[playerid], name_tipo[64], string[512], string2[512];
	switch (tipo)
	{
		case 1: name_tipo = "~g~~h~[Comercio LS]~w~~h~~h~";
		case 2: name_tipo = "~p~[Eventos LS]~w~~h~~h~";
		case 3: name_tipo = "~r~~h~[Sorteos LS]~w~~h~~h~";
		case 4: name_tipo = "~y~[Empleos LS]~w~~h~~h~";
		case 5: name_tipo = "~b~~h~~h~[Servicios LS]~w~~h~~h~";
	}
	format(string, sizeof string, "%s%s ~g~~h~~h~Móvil: %d", name_tipo, inputtext, InfoPersonaje[playerid][pTelefono]);
	switch (tipo)
	{
		case 1: name_tipo = "[Comercio LS]";
		case 2: name_tipo = "[Eventos LS]";
		case 3: name_tipo = "[Sorteos LS]";
		case 4: name_tipo = "[Empleos LS]";
		case 5: name_tipo = "[Servicios LS]";
	}
	format(string2, sizeof string2, "%s %s Móvil: %d", name_tipo, inputtext, InfoPersonaje[playerid][pTelefono]);
	RegistrarAnuncio(string, string2); // register anunce
	DiferenciaAnuncio = gettime();
	format(string, sizeof string, "Anuncio por %s (ID: %d)", GetNameFormat(playerid), playerid);
	SendAdminMessage(0xF7FE2EFF, string);
	GivePlayerCash(playerid, -50, "anuncio");
	InfoPersonaje[playerid][pTimerAnuncios] = 10;
	guardar_int_mysql("personajes", "TimerAnuncios", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pTimerAnuncios]);
	return 1;
}

RegistrarAnuncio(const string[], const string2[])
{
	TextDrawSetStringEx(TD_Anuncio[0], string);
	if (AnunceID == 0)
	{
		if (strcmp(AnunceString1, "none", true) == 0)
		{
			alm(AnunceString1, string);
		}
		else
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
			TextDrawSetStringEx(TD_Anuncio[4], AnunceString4);
			alm(AnunceString4, AnunceString3);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		AnunceID = 1;
	}
	else if (AnunceID == 1)
	{
		if (strcmp(AnunceString2, "none", true) == 0)
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		else
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
			TextDrawSetStringEx(TD_Anuncio[4], AnunceString4);
			alm(AnunceString4, AnunceString3);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		AnunceID = 2;
	}
	else if (AnunceID == 2)
	{
		if (strcmp(AnunceString3, "none", true) == 0)
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		else
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
			TextDrawSetStringEx(TD_Anuncio[4], AnunceString4);
			alm(AnunceString4, AnunceString3);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		AnunceID = 3;
	}
	else if (AnunceID == 3)
	{
		if (strcmp(AnunceString4, "none", true) == 0)
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
			alm(AnunceString4, AnunceString3);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		else
		{
			TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
			TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
			TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
			TextDrawSetStringEx(TD_Anuncio[4], AnunceString4);
			alm(AnunceString4, AnunceString3);
			alm(AnunceString3, AnunceString2);
			alm(AnunceString2, AnunceString1);
			alm(AnunceString1, string);
		}
		AnunceID = 4;
	}
	else if (AnunceID == 4)
	{
		TextDrawSetStringEx(TD_Anuncio[1], AnunceString1);
		TextDrawSetStringEx(TD_Anuncio[2], AnunceString2);
		TextDrawSetStringEx(TD_Anuncio[3], AnunceString3);
		TextDrawSetStringEx(TD_Anuncio[4], AnunceString4);
		alm(AnunceString4, AnunceString3);
		alm(AnunceString3, AnunceString2);
		alm(AnunceString2, AnunceString1);
		alm(AnunceString1, string);
		AnunceID = 0;
	}
	Loop(playerid, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid))
	{
		new numer = PlayerViewAnunce[playerid];
		if (numer != 5)
		{
			PlayerViewAnunce[playerid]++;
			if (InfoPersonaje[playerid][pTogAnuncios] == 0)
			{
				if(InfoCuenta[playerid][jEstiloAnuncio] == 1) SendSplitMessage(playerid, 0x0EB716FF, string2);
				else if (Act_Inventario[playerid] == 0) TextDrawShowForPlayer(playerid, TD_Anuncio[numer]);
				else SendSplitMessage(playerid, 0x0EB716FF, string2);
			}
		}
	}
    return 1;
}

stock IsValidCaracterAnunce(const password[])
{
    for(new i = 0; password[i] != EOS; ++i)
    {
        switch(password[i])
        {
            case '0'..'9', 'A'..'Z', 'a'..'z', '.', ',', '(', ')', '[', ']', ' ', '_', '$', 'ñ': continue;
            default: return 0;
        }
    }
    return 1;
}

new IDOpcionPrecio[MAX_PLAYERS];
cmd:cambiarprecios(playerid)
{
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	new dialog_taller[2056], gformat[256];
	strcat(dialog_taller, "Servicio\tCosto máximo\n");
	format(gformat, sizeof gformat, "{EFEFEF}Pintura\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioPintura]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}PaintJob\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioPaintJob]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Reparación\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioReparacion]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Gasolina\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioGasolina]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Llantas\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioLlantas]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Nitro\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioNitro]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Hidráulica\t{00CC00}$%s\n", diner_coma(InfoNegocio[id][nPrecioHyd]));
	strcat(dialog_taller, gformat);
	format(gformat, sizeof gformat, "{EFEFEF}Tunning carroceria\t{00CC00}$%s", diner_coma(InfoNegocio[id][nPrecioTuneo]));
	strcat(dialog_taller, gformat);
	Dialog_Show(playerid, ChangePrecioTaller, DIALOG_STYLE_TABLIST_HEADERS, "Precios del taller:", dialog_taller, "Continuar", "Salir");
    IDOpcionPrecio[playerid] = -1;
	return 1;
}

Dialog:ChangePrecioTaller(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	new nametip[32], tipo = listitem+1, valor = 0, dialog_precio[512], gtitulo[128];
	switch (tipo)
	{
		case 1: alm(nametip, "Pintura"), valor = InfoNegocio[id][nPrecioPintura];
		case 2: alm(nametip, "PaintJob"), valor = InfoNegocio[id][nPrecioPaintJob];
		case 3: alm(nametip, "Reparación"), valor = InfoNegocio[id][nPrecioReparacion];
		case 4: alm(nametip, "Gasolina"), valor = InfoNegocio[id][nPrecioGasolina];
		case 5: alm(nametip, "Llantas"), valor = InfoNegocio[id][nPrecioLlantas];
		case 6: alm(nametip, "Nitro"), valor = InfoNegocio[id][nPrecioNitro];
		case 7: alm(nametip, "Hidráulica"), valor = InfoNegocio[id][nPrecioHyd];
		case 8: alm(nametip, "Tunning carroceria"), valor = InfoNegocio[id][nPrecioTuneo];
	}
    IDOpcionPrecio[playerid] = tipo;
	format(dialog_precio, sizeof dialog_precio,
	"{EBEBEB}El precio actual del servicio {FE9A2E}%s{EBEBEB} es {00CC00}$%s{EBEBEB}\n\n\
	Introduce el nuevo monto $ máximo del servicio.\n", nametip, diner_coma(valor));
	format(gtitulo, sizeof gtitulo, "{EBEBEB}Nuevo precio de {FE9A2E}%s", nametip);
	Dialog_Show(playerid, Change2PrecioTaller, DIALOG_STYLE_INPUT, gtitulo, dialog_precio, "Continuar", "Volver");
	return 1;
}

Dialog:Change2PrecioTaller(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = IsTallerIn(playerid);
	if (id == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás en el interior de ningún taller mécanico.");
	if (LlavesNegocio(playerid, id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este negocio.");
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo números, vuelve a intentarlo");
	new nametip[32], tipo = IDOpcionPrecio[playerid], valor = strval(inputtext), gformat[320];
	new minimocost = MinimoPrecioTaller(tipo), maximocost = MinimoPrecioTaller(tipo)*3;
	if (valor < minimocost || valor > maximocost)
	{
	    format(gformat, sizeof gformat, "Sólo puedes colocar de mínimo $%s y máximo $%s.", diner_coma(minimocost), diner_coma(maximocost));
		SendPlayerChatMessage(playerid, COLOR_RED, gformat);
	    return 1;
	}
	switch (tipo)
	{
		case 1: alm(nametip, "Pintura"), InfoNegocio[id][nPrecioPintura] = valor;
		case 2: alm(nametip, "PaintJob"), InfoNegocio[id][nPrecioPaintJob] = valor;
		case 3: alm(nametip, "Reparación"), InfoNegocio[id][nPrecioReparacion] = valor;
		case 4: alm(nametip, "Gasolina"), InfoNegocio[id][nPrecioGasolina] = valor;
		case 5: alm(nametip, "Llantas"), InfoNegocio[id][nPrecioLlantas] = valor;
		case 6: alm(nametip, "Nitro"), InfoNegocio[id][nPrecioNitro] = valor;
		case 7: alm(nametip, "Hidráulica"), InfoNegocio[id][nPrecioHyd] = valor;
		case 8: alm(nametip, "Tunning carroceria"), InfoNegocio[id][nPrecioTuneo] = valor;
	}
	IDOpcionPrecio[playerid] = -1;
	format(gformat, sizeof gformat, "El nuevo costo del servicio {5EAEFF}%s{EBEBEB} es de {00CC00}$%s", nametip, diner_coma(valor));
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, gformat);
	ActualizarPrecioNegocio(id);
	return 1;
}

MinimoPrecioTaller(tipo)
{
	new valore = 0;
	switch (tipo)
	{
		case 1: valore = 500;
		case 2: valore = 700;
		case 3: valore = 1000;
		case 4: valore = 200;
		case 5: valore = 4000;
		case 6: valore = 8000;
		case 7: valore = 5000;
		case 8: valore = 12000;
	}
	return valore;
}

cmd:vobjeto(playerid, params[])
{
	if (InfoCuenta[playerid][jVIP] != 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Acceso sólo para usuarios VIP Level 2.");
	new vehicleid;
	if (sscanf(params, "s[32]", params))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vobjeto (Opción) (VehiculoID)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Opciones: agregar, editar, borrar");
		return 1;
	}
	if (!strcmp(params, "agregar", true, 7))
	{
		if (sscanf(params, "s[32]i", params, vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vobjeto agregar (VehiculoID)");
		if (vehicleid < 1 || vehicleid > MAX_VEHICLES) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido.");
		if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido, intenta con otra ID.");
	 	if (GetDistancePlayerVeh(playerid, vehicleid) >= 6.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar al menos 6 metros del vehículo seleccionado.");
 		new id = verificar_id_vehiculo(vehicleid);
		if (id == -1) return SendPlayerChatMessage(playerid, 0xebebebff, "* Este vehículo no es dinámico.");
		if (llaves_vehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres propietario de este vehículo.");
		if (CountObjVeh(id) >= 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes instalar más de tres objetos en tu vehículo siendo VIP Oro.");
		ShowModelSelectionMenuEx(playerid, VehicleFurnObjs, sizeof VehicleFurnObjs, "Elige un objeto", Create_VehObject, 16.0, 0.0, -55.0);
		SetPVarInt(playerid, "FurnVehicleID", id);
	}
	else if (!strcmp(params, "editar", true, 6))
	{
		new slotuwu;
		if (sscanf(params, "s[32]ii", params, vehicleid, slotuwu)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vobjeto editar (VehiculoID) (Slot)");
		if (vehicleid < 1 || vehicleid > MAX_VEHICLES) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido.");
		if (slotuwu < 1 || slotuwu > 5) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Prueba entre 1 - 5.");
		if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido, intenta con otra ID.");
	 	if (GetDistancePlayerVeh(playerid, vehicleid) >= 6.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar al menos 6 metros del vehículo seleccionado.");
		new id = verificar_id_vehiculo(vehicleid);
		if (id == -1) return SendPlayerChatMessage(playerid, 0xebebebff, "* Este vehículo no es dinámico.");
		if (llaves_vehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres propietario de este vehículo.");
		if (CountObjVeh(id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no tiene ningún objeto agregado.");
		new xd = slotuwu-1;
		if (InfoVehiculo[id][vObjModelo][xd] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes nada en ese slot.");
		if (IsValidDynamicObject(InfoVehiculo[id][vTuneo][xd])) DestroyDynamicObject(InfoVehiculo[id][vTuneo][xd]);
		InfoVehiculo[id][vTuneo][xd] = 0;
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
		new obj = CreatePlayerObject(playerid, InfoVehiculo[id][vObjModelo][xd], X+1.0, Y+1.0, Z, 0.0, 0.0, 0.0, 100.0);
		SetPVarInt(playerid, "FurnModelo", InfoVehiculo[id][vObjModelo][xd]);
		SetPVarInt(playerid, "FurnObject", obj);
		SetPVarInt(playerid, "EditorMode", 2);
		EditPlayerObject(playerid, obj);
		SetPVarInt(playerid, "FurnVehicleID", id);
		SetPVarInt(playerid, "FurnSlotObj", xd);
	}
	else if (!strcmp(params, "borrar", true, 6))
	{
		new slotuwu;
		if (sscanf(params, "s[32]ii", params, vehicleid, slotuwu)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /vobjeto borrar (VehiculoID) (Slot)");
		if (vehicleid < 1 || vehicleid > MAX_VEHICLES) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido.");
		if (slotuwu < 1 || slotuwu > 5) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Prueba entre 1 - 5.");
		if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido, intenta con otra ID.");
	 	if (GetDistancePlayerVeh(playerid, vehicleid) >= 6.0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes estar al menos 6 metros del vehículo seleccionado.");
		new id = verificar_id_vehiculo(vehicleid);
		if (id == -1) return SendPlayerChatMessage(playerid, 0xebebebff, "* Este vehículo no es dinámico.");
		if (llaves_vehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres propietario de este vehículo.");
		if (CountObjVeh(id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no tiene ningún objeto agregado.");
		new xd = slotuwu-1;
		if (InfoVehiculo[id][vObjModelo][xd] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes nada en ese slot.");
		if (IsValidDynamicObject(InfoVehiculo[id][vTuneo][xd])) DestroyDynamicObject(InfoVehiculo[id][vTuneo][xd]);
		InfoVehiculo[id][vTuneo][xd] = 0;
		InfoVehiculo[id][vObjModelo][xd] = 0;
		InfoVehiculo[id][vObjPosX][xd] = 0;
		InfoVehiculo[id][vObjPosY][xd] = 0;
		InfoVehiculo[id][vObjPosZ][xd] = 0;
		InfoVehiculo[id][vObjRotX][xd] = 0;
		InfoVehiculo[id][vObjRotY][xd] = 0;
		InfoVehiculo[id][vObjRotZ][xd] = 0;
		new query[1028];
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET ObjModelo_%d = '%d', ObjPosX_%d = '%f', ObjPosY_%d = '%f', ObjPosZ_%d = '%f', ObjRotX_%d = '%f', ObjRotY_%d = '%f', ObjRotZ_%d = '%f' WHERE ID = '%d'",
		xd+1, InfoVehiculo[id][vObjModelo][xd], xd+1, InfoVehiculo[id][vObjPosX][xd], xd+1, InfoVehiculo[id][vObjPosY][xd], xd+1, InfoVehiculo[id][vObjPosZ][xd], xd+1, InfoVehiculo[id][vObjRotX][xd], xd+1, InfoVehiculo[id][vObjRotY][xd], xd+1, InfoVehiculo[id][vObjRotZ][xd], InfoVehiculo[id][vID_sql]);
		mysql_tquery(db_samp, query);
	}
	return 1;
}

CountObjVeh(id)
{
	new count = 0;
	Loop(x, 5, 0) if (InfoVehiculo[id][vObjModelo][x] != 0)
	{
		count++;
	}
	return count;
}

new OBJ_Dinamita[MAX_PLAYERS];
cmd:dinamita(playerid)
{
	if (no_tiene_manos(playerid, 52) == 0) return 1;
	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes poner dinamita estando en un vehículo.");
	if (InfoPersonaje[playerid][pManoDerecha] == 52)
	{
		InfoPersonaje[playerid][pManoDerecha] = 0;
		InfoPersonaje[playerid][pManoDerechaCant] = 0;
		RemovePlayerAttachedObject(playerid, 7);
	}
	else
	{
		InfoPersonaje[playerid][pManoIzquierda] = 0;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
		RemovePlayerAttachedObject(playerid, 8);
	}
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	GetPosInFrontOfPlayer(playerid, x, y, 0.6);
	OBJ_Dinamita[playerid] = CreateDynamicObject(1654, x, y, z-0.8, 0, 0, 0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid) );
	SetTimerEx("DetonarDinamita", 12000, false, "dfff", playerid, x, y, z);
	rol_auto(playerid,"coloca dinamita en el suelo.");
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 1, 1, 0, 0, 1);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "La dinamita explotará en 12 segundos.");
	Streamer_Update(playerid);
	return 1;
}

forward DetonarDinamita(playerid, Float:x, Float:y, Float:z);
public DetonarDinamita(playerid, Float:x, Float:y, Float:z)
{
	CreateExplosionEx(x, y, z, 0, 10.0);
	if (IsValidDynamicObject(OBJ_Dinamita[playerid])) DestroyDynamicObject(OBJ_Dinamita[playerid]);
	OBJ_Dinamita[playerid] = 0;
	return 1;
}

CreateExplosionEx(Float: x, Float: y, Float: z, type, Float: rango)
{
	Loop(playerid, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid))
	{
		new Float: damage, Float: rango2 = GetPlayerDistanceFromPoint(playerid, x, y, z);
		switch (floatround(rango2))
		{
			case 1: damage = 100;
			case 2: damage = 95;
			case 3: damage = 80;
			case 4: damage = 70;
			case 5: damage = 65;
			case 6: damage = 50;
			case 7: damage = 45;
			case 8: damage = 30;
			case 9: damage = 20;
			case 10: damage = 10;
		}
		quitar_vida(playerid, -damage);
	}
	CreateExplosion(x, y, z, type, rango);
	return 1;
}

cmd:limpiarobjetov(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new vehicleid, sstring[186];
	if (sscanf(params, "i", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /limpiarobjetov (VehiculoID)");
	if (vehicleid < 1 || vehicleid > MAX_VEHICLES) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido.");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Vehículo inválido, intenta con otra ID.");
	new id = verificar_id_vehiculo(vehicleid), iCount = 0;
	if (id == -1) return SendPlayerChatMessage(playerid, 0xebebebff, "* Este vehículo no es dinámico.");
	if (CountObjVeh(id) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Este vehículo no tiene ningún objeto agregado.");
	Loop(xd, 5, 0) if (InfoVehiculo[id][vObjModelo][xd] != 0)
	{
	    iCount++;
		if (IsValidDynamicObject(InfoVehiculo[id][vTuneo][xd])) DestroyDynamicObject(InfoVehiculo[id][vTuneo][xd]);
		InfoVehiculo[id][vTuneo][xd] = 0;
		InfoVehiculo[id][vObjModelo][xd] = 0;
		InfoVehiculo[id][vObjPosX][xd] = 0;
		InfoVehiculo[id][vObjPosY][xd] = 0;
		InfoVehiculo[id][vObjPosZ][xd] = 0;
		InfoVehiculo[id][vObjRotX][xd] = 0;
		InfoVehiculo[id][vObjRotY][xd] = 0;
		InfoVehiculo[id][vObjRotZ][xd] = 0;
		new query[1028];
		mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET ObjModelo_%d = '%d', ObjPosX_%d = '%f', ObjPosY_%d = '%f', ObjPosZ_%d = '%f', ObjRotX_%d = '%f', ObjRotY_%d = '%f', ObjRotZ_%d = '%f' WHERE ID = '%d'",
		xd+1, InfoVehiculo[id][vObjModelo][xd], xd+1, InfoVehiculo[id][vObjPosX][xd], xd+1, InfoVehiculo[id][vObjPosY][xd], xd+1, InfoVehiculo[id][vObjPosZ][xd], xd+1, InfoVehiculo[id][vObjRotX][xd], xd+1, InfoVehiculo[id][vObjRotY][xd], xd+1, InfoVehiculo[id][vObjRotZ][xd], InfoVehiculo[id][vID_sql]);
		mysql_tquery(db_samp, query);
	}
	format(sstring, sizeof sstring, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) limpió %d objetos VIP del vehículo ID %d.", InfoCuenta[playerid][jNombre], playerid, iCount, vehicleid);
	SendAdminMessage(0xFFFFFFFF, sstring);
	return 1;
}

stock ShowCamello(playerid)
{
	new faccion = member_faccion(playerid, 9);
	if (faccion == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Solo pandilleros pueden comprarle al camello.");
	Dialog_Show(playerid, ShowCamello, DIALOG_STYLE_LIST, "Camello", "Cargadores\nDrogas", "Seleccionar", "Salir");
	return 1;
}

Dialog:ShowCamello(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	switch(listitem){
		case 0: {
			new dialg_products[2500];
			strcat(dialg_products, "Cargador\tValor\n");
			strcat(dialg_products, "{ffffff}9mm\t{00cc00}$25\n");
			strcat(dialg_products, "{ffffff}Desert eagle\t{00cc00}$27\n");
			strcat(dialg_products, "{ffffff}Uzi\t{00cc00}$25\n");
			strcat(dialg_products, "{ffffff}Mp5\t{00cc00}$30\n");
			strcat(dialg_products, "{ffffff}Tec-9\t{00cc00}$35\n");
			strcat(dialg_products, "{ffffff}Ak47\t{00cc00}$55\n");
			strcat(dialg_products, "{ffffff}M4\t{00cc00}$54\n");
			strcat(dialg_products, "{ffffff}Rifle\t{00cc00}$40\n");
			strcat(dialg_products, "{ffffff}Escopeta\t{00cc00}$55");
			Dialog_Show(playerid, BuyCargadores, DIALOG_STYLE_TABLIST_HEADERS, "Camello: {D1C231}Cargadores", dialg_products, "Comprar", "Salir");
			return 1;
		}
		case 1: {
			new DProductos[1234];
			strcat(DProductos, "Producto\tValor\n");
			strcat(DProductos, "Cocaína\t{00CC00}$1,650\n");
			strcat(DProductos, "Crack\t{00CC00}$1,426\n");
			strcat(DProductos, "Marihuana\t{00CC00}$2,500\n");
			strcat(DProductos, "Cigarrillo electrico\t{00CC00}$500\n");
			strcat(DProductos, "Semilla de coca\t{00CC00}$2,000\n");
			strcat(DProductos, "Semilla de marihuana\t{00CC00}$4,000\n");
			strcat(DProductos, "Micelio de alucinógeno\t{00CC00}$1,000\n");
			Dialog_Show(playerid, BuyDrogas, DIALOG_STYLE_TABLIST_HEADERS, "Camello: {D1C231}Drogas", DProductos, "Comprar", "Salir");
			return 1;
		}
	}
	return 1;
}

Dialog:BuyCargadores(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new precio, obj;
	switch (listitem)
	{
		case 0: precio = 25, obj = 56;
		case 1: precio = 27, obj = 57;
		case 2: precio = 25, obj = 58;
		case 3: precio = 30, obj = 59;
		case 4: precio = 35, obj = 60;
		case 5: precio = 55, obj = 61;
		case 6: precio = 54, obj = 62;
		case 7: precio = 40, obj = 63;
		case 8: precio = 55, obj = 64;
	}
	if (GetPlayerCash(playerid) < precio)
	{
		SendClientMessageEx(playerid, 0xEBEBEBFF, "Te hacen falta $%s para comprar '{b42d2d}Cargador{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
		return 1;
	}
	if (DarObjeto(playerid, obj, InfoInventario[obj][DefaultCantidad]) == 2) return 1;
	SendClientMessageEx(playerid, COLOR_LIGHTGREEN, "Compraste %s por $%d dólares.", InfoInventario[obj][NombreObjeto], precio);
	GivePlayerCash(playerid, -precio, "cargador");
	return 1;
}

Dialog:BuyDrogas(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new string[195];
	switch (listitem)
	{
		case 0:
		{
		    new precio = 1650;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}10 gramos de cocaína{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 46, 10) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste 10 gramos de cocaína por $1,650 dólares.");
			GivePlayerCash(playerid, -precio, "10gr de cocaina");
		}
		case 1:
		{
		    new precio = 1426;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}15 gramos de crack{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 44, 15) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste 15 gramos de crack por $1,426 dólares.");
			GivePlayerCash(playerid, -precio, "15gr de crack");
		}
		case 2:
		{
		    new precio = 2500;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}30 gramos de marihuana{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 43, 30) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste 30 gramos de marihuana por $2,500 dólares.");
			GivePlayerCash(playerid, -precio, "30gr de marihuana");
		}
		case 3: {
			new precio = 500;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar un 'cigarro electrico' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 79, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un cigarro electrico");
			GivePlayerCash(playerid, -precio, "compra de cigarro electrico");
		}
		case 4: {
			new precio = 2000;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar una 'semilla de coca' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 85, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una semilla de coca");
			GivePlayerCash(playerid, -precio, "semilla de coca");
		}
		case 5: {
			new precio = 4000;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar una 'semilla de marihuana' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 83, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una semilla de marihuana");
			GivePlayerCash(playerid, -precio, "semilla de marihuana");
		}
		case 6: {
			new precio = 1000;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar 'micelio de aluciógeno' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 83, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste micelio de aluciógeno");
			GivePlayerCash(playerid, -precio, "micelio");
		}
	}
	return 1;
}

EnCamellos(playerid)
{
	if (IsPlayerInRangeOfPoint(playerid, 5.0, 2526.8215, -1641.3239, 13.9997)) return 1;
	else if (IsPlayerInRangeOfPoint(playerid, 5.0, 2474.8921, -1324.3365, 27.5433)) return 1;
	else if (IsPlayerInRangeOfPoint(playerid, 5.0, 1935.6304, -1060.5109, 24.4119)) return 1;
	else if (IsPlayerInRangeOfPoint(playerid, 5.0, 833.7507, -1528.7776, 13.6607)) return 1;
	return 0;
}

cmd:arrastrar(playerid, params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos 10 horas jugando el servidor.");
	new playerid2, gformat[160];
	if (sscanf(params, "u", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /arrastrar (PlayerID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador desconectado.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te vas arrastrar a ti mismo.");
	if (!CercaDelWeon(3.5, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Estás lejos del jugador.");
	if (EstaParaArrastrar(playerid2) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador debe estar en estado de herido/muerto/rendido/esposado.");
	new Float:p_x, Float:p_y, Float:p_z, interior = GetPlayerInterior(playerid), vw = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, p_x, p_y, p_z);
	SetPosEx(playerid2, p_x, p_y+0.5, p_z, 0, interior, vw, 1);
	format(gformat, sizeof gformat, "* %s se aprovecha de tu estado y te arrastra hacía él.", GetNameFormat(playerid));
	SendPlayerChatMessage(playerid2, 0x1EB032FF, gformat);
	format(gformat, sizeof gformat, "* Aprovechas del estado de %s para arrastrarlo hacía ti.", GetNameFormat(playerid2));
	SendPlayerChatMessage(playerid, 0x1EB032FF, gformat);
	return 1;
}

EstaParaArrastrar(playerid)
{
	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_HANDSUP) return 1;
	if (GetPVarInt(playerid, "PlayerCuffed") == 1) return 1;
	if (GetPVarInt(playerid, "EstaCrack") != 0) return 1;
	return 0;
}

cmd:arma(playerid, params[])
{
	if (sscanf(params, "s[32]", params[0])) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /arma (Colgar - Ajustar - Hueso - Tomar)");
	if (strcmp(params[0], "colgar", true) == 0) pc_cmd_espalda(playerid);
	else if (strcmp(params[0], "ajustar", true) == 0) pc_cmd_pespalda(playerid);
	else if (strcmp(params[0], "hueso", true) == 0)
	{
		if (EditandoObjetoJ[playerid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya estás editando un arma.");
		new gformat[512];
		format(gformat, sizeof(gformat), "Columna vertebral\nCabeza\nBrazo izquierdo\nBrazo derecho\nMano izquierda\nMano derecha\nMuslo izquierdo\nMuslo derecho\n\
		Pie izquierdo\nPie derecho\nPantorrilla derecha\nPantorrilla izquierda\nAntebrazo izquierdo\nAntebrazo derecho\nClavícula izquierda\n\
		Clavícula derecha\nCuello\nMandíbula");
		Dialog_Show(playerid, EditHueso, DIALOG_STYLE_LIST, "Hueso", gformat, "Continuar", "Salir");
	}
	else if (strcmp(params[0], "tomar", true) == 0) pc_cmd_qespalda(playerid);
	else SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /arma (Colgar - Ajustar - Hueso - Tomar)");
	return 1;
}

Dialog:EditHueso(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	InfoPersonaje[playerid][ptHueso][7] = listitem + 1;
	SendPlayerChatMessage(playerid, COLOR_YELLOW, "Cambiaste el hueso de tu arma.");
	if (InfoPersonaje[playerid][pEspalda] != 0)
	{
		RemovePlayerAttachedObject(playerid, 9);
		PonerObjeto(playerid, 3, InfoPersonaje[playerid][pEspalda]);
	}
	return 1;
}

cmd:espalda(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido.");
	new manod = InfoPersonaje[playerid][pManoDerecha];
	if (EditandoObjetoJ[playerid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya estás editando un arma.");
	if (InfoPersonaje[playerid][pEspalda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees un arma colgada, debes usar (/arma tomar) para quitarla.");
	if (manod == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu mano derecha mano.");
	new weaponid = InfoInventario[manod][IDArma];
	new mochila = InfoPersonaje[playerid][pManoDerecha] == 86;
	if (!weaponid && !mochila) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás sosteniendo un arma.");
	if (!IsObjectWearable(manod)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto no puede ser editado.");
	SendClientMessageEx(playerid, 0x828BFDFF, "Cuelgas tu %s en tu personaje.", GetNameObjeto(manod));
	InfoPersonaje[playerid][pEspalda] = manod, InfoPersonaje[playerid][pEspaldaCant] = InfoPersonaje[playerid][pManoDerechaCant];
	InfoPersonaje[playerid][pManoDerecha] = 0, InfoPersonaje[playerid][pManoDerechaCant] = 0;
	PonerObjeto(playerid, 3, manod);
	ResetPlayerWeapons(playerid);
	RemovePlayerAttachedObject(playerid, 7);
	new query[512];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = '%d', Cantidad_espalda = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'",
	InfoPersonaje[playerid][pEspalda], InfoPersonaje[playerid][pEspaldaCant], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	SetPlayerInventario(playerid, 3);
	return 1;
}

cmd:pespalda(playerid)
{
	if (InfoPersonaje[playerid][pEspalda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada colgado en tu cuerpo.");
	new obj = InfoPersonaje[playerid][pEspalda];
	new weaponid = InfoInventario[obj][IDArma];
	if (!weaponid) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás sosteniendo un arma.");
	if (!IsObjectWearable(obj)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esta arma no puede ser editada.");
	if (EditandoObjetoJ[playerid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya estás editando un arma.");
	EditAttachedObject(playerid, 9);
	EditandoObjetoJ[playerid] = 2;
	SendPlayerChatMessage(playerid, -1, "Mantén presionado {3E62F4}~k~~PED_SPRINT~{FFFFFF} para cambiar la posición de la cámara.");
	return 1;
}

IsObjectWearable(objectid)
{
	switch (objectid)
	{
		case 2..15: return 1;
		case 19..40: return 1;
		case 54: return 1;
		case 86: return 1;
	}
	return 0;
}

cmd:qespalda(playerid)
{
	new Espalda = InfoPersonaje[playerid][pEspalda];
	if (Espalda == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes ningún arma colgada.");
	if (EditandoObjetoJ[playerid]) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes tomar el arma mientras editas.");
	if (InfoPersonaje[playerid][pManoDerecha] > 0 && InfoPersonaje[playerid][pManoIzquierda] > 0) { SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas."); return 1; }
	if (InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		SendClientMessageEx(playerid, 0x828BFDFF, "Descuelgas tu %s de tu personaje.", GetNameObjeto(Espalda));
		GivePlayerWeapon(playerid, InfoInventario[Espalda][IDArma], InfoPersonaje[playerid][pEspaldaCant]);
		InfoPersonaje[playerid][pManoDerecha] = Espalda;
		InfoPersonaje[playerid][pManoDerechaCant] = InfoPersonaje[playerid][pEspaldaCant];
		PonerObjeto(playerid, 1, Espalda);
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		SendClientMessageEx(playerid, 0x828BFDFF, "Descuelgas tu %s de tu personaje.", GetNameObjeto(Espalda));
		InfoPersonaje[playerid][pManoIzquierda] = Espalda;
		InfoPersonaje[playerid][pManoIzquierdaCant] = InfoPersonaje[playerid][pEspaldaCant];
		PonerObjeto(playerid, 2, Espalda);
	}
	InfoPersonaje[playerid][pEspalda] = 0, InfoPersonaje[playerid][pEspaldaCant] = 0;
	RemovePlayerAttachedObject(playerid, 9);
	new query[1000];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = '%d', Cantidad_espalda = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
	InfoPersonaje[playerid][pEspalda], InfoPersonaje[playerid][pEspaldaCant], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	SetPlayerInventario(playerid, 3);
	return 1;
}

cmd:altavoz(playerid)
{
	if (EnLlamada[playerid] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te encuentras en una llamada.");
	if (Altavoz[playerid] == 0)
	{
		Altavoz[playerid] = 1;
		SendPlayerChatMessage(playerid, 0xA7CE00FF, "Altavoz activado.");
	}
	else
	{
		Altavoz[playerid] = 0;
		SendPlayerChatMessage(playerid, 0xA7CE00FF, "Altavoz desactivado.");
	}
	return 1;
}

cmd:llamar(playerid, params[])
{
	if (InfoPersonaje[playerid][pTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes un número telefónico.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	if (InfoPersonaje[playerid][pTiempoSancion] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás en prisión.");
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás herido.");
	if (InfoPersonaje[playerid][pTogTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Tu teléfono se encuentra apagado, escribe /togphone para encenderlo.");
	if (EnLlamada[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya te encuentras en una llamada.");
	if (GetPlayerCash(playerid) < 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos 3$ dólares en bolsillos para llamar.");
	new numero;
	if (sscanf(params, "d", numero)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /llamar (Número)");
	if (numero == 0) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /llamar (Número)");
	if (numero == InfoPersonaje[playerid][pTelefono]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te puedes llamar a ti mismo.");
	rol_ame(playerid, "saca su móvil y marca unos números.");
	llamar_numero(playerid, numero);
	return 1;
}

posee_telefono(playerid)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 50) return 1;
	if (InfoPersonaje[playerid][pManoIzquierda] == 50) return 1;
	Loop(x, 9, 0)
		if (InfoPersonaje[playerid][pBolsillo][x] == 50) return 1;
	Loop(x, 6, 0)
		if (InfoPersonaje[playerid][pCinturon][x] == 50) return 1;
	return 0;
}

forward llamar_numero(playerid, numero);
public llamar_numero(playerid, numero)
{
	if (numero == InfoPersonaje[playerid][pTelefono]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te puedes llamar a ti mismo.");
	new string[256];
	if (numero == 911) //emergencias
	{
		if (OnDuty[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes llamar a la estación estando de servicio.");
		EnLlamada[playerid] = 911;
		SendPlayerChatMessage(playerid, 0x828BFDFF, "Una voz de operadora te saluda. Enseguida te pondrá con alguien.");
		SendPlayerChatMessage(playerid, 0xFFF000FF, "[Teléfono: 911]: De acuerdo, ¿cuál es su emergencia? Sea lo más explícito posible, por favor.");
		for (new x=1; x<sizeof(info_c); x++)
		{
			if (info_c[x][aID] == 0)
			{
				r_id[playerid] = x;
				return 0;
			}
		}
		return 1;
	}
	new tlfencontrado = 0;
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		if (InfoPersonaje[playerid2][pTelefono] == numero)
		{
			if (EnLlamada[playerid2] != 0 || PersonaEnLlamada[playerid2] != -1) { tlfencontrado = -1; break; }
			if (!posee_telefono(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El teléfono seleccionado se encuentra apagado. (1)");
			if (InfoPersonaje[playerid2][pTogTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El teléfono seleccionado se encuentra apagado. (2)");
			tlfencontrado = 1;
			rol_ame(playerid2, "le suena el móvil.");
			format(string, sizeof string, "* Llamada entrante del número %d, escribe /contestar para responder la llamada.", InfoPersonaje[playerid][pTelefono]);
			SendPlayerChatMessage(playerid2, COLOR_LIGHTGREEN, string);
			format(string, sizeof string, "*** Llamando al número %d ***", numero);
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
			ToqueLlamada[playerid2] = 0;
			PersonaEnLlamada[playerid] = playerid2;
			PersonaEnLlamada[playerid2] = playerid;
			EnLlamada[playerid] = 1;
			ToqueLlamadaTimer[playerid2] = SetTimerEx("OnLlamadaPhone", 15000, true, "i", playerid2);
			break;
		}
	}
	if (tlfencontrado == -1) SendPlayerChatMessage(playerid, COLOR_GREY, "* El número que ha marcado está en una llamada.");
	if (tlfencontrado == 0) SendPlayerChatMessage(playerid, COLOR_GREY, "* El número que ha marcado no existe o no está disponible.");
	return 1;
}

cmd:colgar(playerid)
{
	new string[245], oyente = PersonaEnLlamada[playerid];
	if (!IsPlayerConnectedEx(oyente))
	{
		EnLlamada[playerid] = 0;
		PersonaEnLlamada[playerid] = -1;
	    return 1;
	}
	if (EnLlamada[playerid] == 1) //está llamando a alguien
	{
		EnLlamada[playerid] = 0;
		SendPlayerChatMessage(playerid, COLOR_GREY, "*** Has colgado.");
		format(string, sizeof string, "Tienes una llamada perdida del %d.", InfoPersonaje[playerid][pTelefono]);
		SendPlayerChatMessage(oyente, 0x9C791200, string);
		KillTimer(ToqueLlamadaTimer[oyente]);
		ToqueLlamada[oyente] = 0;
		PersonaEnLlamada[oyente] = -1;
		PersonaEnLlamada[playerid] = -1;
		return 1;
	}
	if (EnLlamada[playerid] == 2 || EnLlamada[playerid] == 3) //llamando normal
	{
		SendPlayerChatMessage(playerid, COLOR_GREY, "*** Has colgado.");
		SendPlayerChatMessage(oyente, COLOR_GREY, "*** Han colgado.");
		if (EnLlamada[playerid] == 3)
		{
			SendPlayerChatMessage(playerid, COLOR_LIGHTRED, "Coste de la llamada: 1$");
			GivePlayerCash(playerid, -1, "costo de llamada");
		}
		if (EnLlamada[oyente] == 3)
		{
			SendPlayerChatMessage(oyente, COLOR_LIGHTRED, "Coste de la llamada: 1$");
			GivePlayerCash(oyente, -1, "costo de llamada");
		}
		EnLlamada[playerid] = 0;
		EnLlamada[oyente] = 0;
		PersonaEnLlamada[oyente] = -1;
		PersonaEnLlamada[playerid] = -1;
		return 1;
	}
	if (EnLlamada[playerid] == 911) //llamando a emergencias
	{
		EnLlamada[playerid] = 0;
		SendPlayerChatMessage(playerid, COLOR_GREY, "*** Has colgado.");
	}
	return 1;
}

forward OnLlamadaPhone(playerid);
public OnLlamadaPhone(playerid)
{
	new string[240];
	if (!telefono_enmanos(playerid))
	{
		EnLlamada[PersonaEnLlamada[playerid]] = 0;
		ToqueLlamada[playerid] = 0;
		SendPlayerChatMessage(PersonaEnLlamada[playerid], 0xEBEBEBFF, "No contestan.");
		PersonaEnLlamada[PersonaEnLlamada[playerid]] = -1;
		PersonaEnLlamada[playerid] = -1;
		KillTimer(ToqueLlamadaTimer[playerid]);
		return 1;
	}
	if (ToqueLlamada[playerid] > 4)
	{
		if (PersonaEnLlamada[playerid] != -1) EnLlamada[PersonaEnLlamada[playerid]] = 0;
		ToqueLlamada[playerid] = 0;
		format(string, sizeof string, "* Llamada perdida del %d.", InfoPersonaje[PersonaEnLlamada[playerid]][pTelefono]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		SendPlayerChatMessage(PersonaEnLlamada[playerid], 0xEBEBEBFF, "No contestan.");
		for(new i=0; i<MAX_PLAYERS; i++) { if(PersonaEnLlamada[i] == playerid){PersonaEnLlamada[i] = -1; break;} }
		PersonaEnLlamada[playerid] = -1;
		KillTimer(ToqueLlamadaTimer[playerid]);
		return 1;
	}
	/*PlayerAudio(playerid, 20600, 15.0);*/
	SendPlayerChatMessage(PersonaEnLlamada[playerid], 0xEBEBEBFF, "* Llamando...");
	ToqueLlamada[playerid] ++;
	return 1;
}

telefono_enmanos(playerid)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 50) return 1;
	if (InfoPersonaje[playerid][pManoIzquierda] == 50) return 1;
	return 0;
}

cmd:transferir(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás herido.");
	if (InfoPersonaje[playerid][pTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes un número telefónico.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos dos horas, para poder transferir dinero.");
	Dialog_Show(playerid, TransferirBancoDinero, DIALOG_STYLE_INPUT, "Transferencia (paso 1)", "{EBEBEB}Por favor, ingrese {FE9A2E}ID del jugador{EBEBEB} que deseas transferir dinero:", "Continuar", "Volver");
    ConTransferir[playerid] = 2;
	return 1;
}

cmd:sms(playerid, params[])
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás herido.");
	if (InfoPersonaje[playerid][pTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes un número telefónico.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	new string[256], phonenumb, text[256];
	if (sscanf(params, "ds[256]", phonenumb, text)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sms (Número) (Texto)");
	if (GetPlayerCash(playerid) < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos 2$ dólares en bolsillos para enviar mensajes.");
	foreach(new i: Player) if (IsPlayerConnectedEx(i))
	{
		if (InfoPersonaje[i][pTelefono] == phonenumb && phonenumb != 0)
		{
			new playerid2 = i;
			if (InfoPersonaje[playerid2][pTogTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Mensaje no enviado, teléfono apagado.");
			format(string, sizeof string, "SMS de %d: %s", InfoPersonaje[playerid][pTelefono], text);
			SendPlayerChatMessage(playerid2, 0xFFEA5FFF, string);
			format(string, sizeof string, "SMS a %d: %s", phonenumb, text);
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
			PlayerAudio(playerid, 1053, 10.0);
			PlayerAudio(playerid2, 20804, 10.0);
			GivePlayerCash(playerid, -1, "costo de sms");
			rol_ame(playerid, "envía un mensaje de texto.");
			return 1;
		}
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* El número que ha marcado no existe o no está disponible.");
	return 1;
}

cmd:contestar(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando mientras estás herido.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	if (EnLlamada[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ya te encuentras en una llamada.");
	if (PersonaEnLlamada[playerid] > -1)//llamada normal
	{
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "Contestas la llamada.");
		SendPlayerChatMessage(PersonaEnLlamada[playerid], COLOR_YELLOW, "Contestaron el teléfono, se te cobrara 1$ por esta llamada.");
		EnLlamada[playerid] = 2;
		EnLlamada[PersonaEnLlamada[playerid]] = 3;
		KillTimer(ToqueLlamadaTimer[playerid]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "* Parece no haber llamadas entrantes.");
	return 1;
}
alias:contestar("atender");

cmd:fumar(playerid, params[])
{
	new manoder = InfoPersonaje[playerid][pManoDerecha];
	/*
		41 Encendedor
		42 Paquete de cigarros
		43 Marihuana
		47 Canuto de marihuana
		48 Blunt de marihuana
		49 Cigarro
	*/
	new query[500];
	if ((manoder == 42 || manoder == 43) && InfoPersonaje[playerid][pManoDerechaCant] > 0)
	{
		if (InfoPersonaje[playerid][pManoIzquierda] != 41) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes tener un encendedor en tu mano izquierda.");
		if (InfoPersonaje[playerid][pManoIzquierdaCant] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "El encendedor que tienes ya no tiene gas.");
		new slot = -1;
		Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] == 0)
		{
			slot = x;
			break;
		}
		if (slot == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes donde guardar el objeto de la mano derecha.");
		switch (manoder)
		{
			case 42: //paquete cigarros
			{
				RemovePlayerAttachedObject(playerid, 7);
				InfoPersonaje[playerid][pManoDerechaCant]--;
				InfoPersonaje[playerid][pManoIzquierdaCant]--;
				InfoPersonaje[playerid][pBolsillo][slot] = 42;
				InfoPersonaje[playerid][pBolsilloCant][slot] = InfoPersonaje[playerid][pManoDerechaCant];
				InfoPersonaje[playerid][pManoDerecha] = 49;
				InfoPersonaje[playerid][pManoDerechaCant] = 5;
				PonerObjeto(playerid, 1, 49);
				SendPlayerChatMessage(playerid, 0xFFFF00AA, "Te lías un cigarro, para dar otra calada utliza /fumar.");
				pc_cmd_fumando(playerid, "5");
				mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
				slot+1, InfoPersonaje[playerid][pBolsillo][slot], slot+1, InfoPersonaje[playerid][pBolsilloCant][slot], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
				mysql_tquery(db_samp, query);
				return 1;
			}
			case 49:
			{
				InfoPersonaje[playerid][pManoDerechaCant]--;
				pc_cmd_fumando(playerid, "5");
				ActualizarManos(playerid, 1);
			}
		}
	}
	else return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada para encender o fumar en tu mano derecha.");
	return 1;
}

//
cmd:ct(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un cinturón táctico.");
	ver_cinturon(playerid);
	return 1;
}

ver_cinturon(playerid)
{
	// normal
	new dialog[1024], dialog2[256], count = 0;
	Loop(x, 6, 0)
	{
		if (InfoPersonaje[playerid][pCinturon][x] != 0) format(dialog2, sizeof dialog2, "{FFFFFF}%s\n", slot_inv(InfoPersonaje[playerid][pCinturon][x], InfoPersonaje[playerid][pCinturonCant][x])), count++;
		else alm(dialog2, "{CCCCCC}—\n");
		strcat(dialog, dialog2);
	}
	//barra espacio
	strcat(dialog, "{b42d2d}--------------------\n");
	//mano derecha
	if (InfoPersonaje[playerid][pManoDerecha] != 0) format(dialog2, sizeof dialog2, "{FFFFFF}Mano derecha: %s\n", slot_inv(InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant])), count++;
	else alm(dialog2, "{CCCCCC}Mano derecha vacía\n");
	strcat(dialog, dialog2);
	//mano izquierda
	if (InfoPersonaje[playerid][pManoIzquierda] != 0) format(dialog2, sizeof dialog2, "{FFFFFF}Mano izquierda: %s\n", slot_inv(InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant])), count++;
	else alm(dialog2, "{CCCCCC}Mano izquierda vacía\n");
	strcat(dialog, dialog2);
	//show_dialog
	if (count == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Cinturón táctico", "{CCCCCC}No tienes nada que sacar o guardar.", "Cerrar", "");
	Dialog_Show(playerid, OpcionCinturon, DIALOG_STYLE_LIST, "Cinturón táctico", dialog, "Continuar", "Salir");
	return 1;
}

Dialog:OpcionCinturon(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0..5: sacar_cinturon(playerid, listitem);
		case 6: return pc_cmd_ct(playerid);
		case 7: guardar_cinturon(playerid, 1);
		case 8: guardar_cinturon(playerid, 2);
	}
	return 1;
}

cmd:guardarct(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un cinturón táctico.");
	guardar_cinturon(playerid, 1);
	return 1;
}
alias:guardarct("gct");

cmd:sacarct(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un cinturón táctico.");
	new id;
	if (sscanf(params, "i", id))
	{
		new count = 0, dialog[256];
		Loop(x, 6, 0) if (InfoPersonaje[playerid][pCinturon][x] != 0) count++;
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu cinturón táctico.");
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /sacarct (slot)");
		Loop(x, 6, 0) if (InfoPersonaje[playerid][pCinturon][x] != 0)
		{
			format(dialog, sizeof(dialog), "Tienes en {b42d2d}slot %d{EBEBEB}: %s", x+1, slot_objeto(InfoPersonaje[playerid][pCinturon][x], InfoPersonaje[playerid][pCinturonCant][x]));
			SendPlayerChatMessage(playerid, 0xEBEBEBFF, dialog);
		}
		return 1;
	}
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /sacarct (Slot)");
	if (id < 1 || id > 6) { SendPlayerChatMessage(playerid, COLOR_GREY, "El número del espacio debe estar entre 1 y 6."); return 1; }
	sacar_cinturon(playerid, id - 1);
	return 1;
}
alias:sacarct("sct");

sacar_cinturon(playerid, id)
{
	new query[512];
	new Bol = InfoPersonaje[playerid][pCinturon][id], Cant = InfoPersonaje[playerid][pCinturonCant][id], string[128];
	if (Bol == 0) return 1;
	if (InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		if (InfoInventario[Bol][IDArma] > 0)
		{
			new arma = InfoInventario[Bol][IDArma], municion = Cant;
			if (municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
		}
		InfoPersonaje[playerid][pManoDerecha] = Bol;
		InfoPersonaje[playerid][pManoDerechaCant] = Cant;
		PonerObjeto(playerid, 1, Bol);
		InfoPersonaje[playerid][pCinturon][id] = 0;
		InfoPersonaje[playerid][pCinturonCant][id] = 0;
		format(string, sizeof string, "desenfunda su %s reglamentaria.", InfoInventario[Bol][NombreObjeto]);
		rol_ame(playerid, string);
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Cinturon_%d = '%d', Cantidad_cinturon_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'",
		id+1, InfoPersonaje[playerid][pCinturon][id], id+1, InfoPersonaje[playerid][pCinturonCant][id], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = Bol;
		InfoPersonaje[playerid][pManoIzquierdaCant] = Cant;
		PonerObjeto(playerid, 2, Bol);
		InfoPersonaje[playerid][pCinturon][id] = 0;
		InfoPersonaje[playerid][pCinturonCant][id] = 0;
		format(string, sizeof string, "desenfunda su %s reglamentaria.", InfoInventario[Bol][NombreObjeto]);
		rol_ame(playerid, string);
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Cinturon_%d = '%d', Cantidad_cinturon_%d = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
		id+1, InfoPersonaje[playerid][pCinturon][id], id+1, InfoPersonaje[playerid][pCinturonCant][id], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
	} else return SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
	return 1;
}

guardar_cinturon(playerid, mano)
{
	new query[512];
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido.");
	if(mano == 1)
	{
		if(InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano derecha.");
		new Mano = InfoPersonaje[playerid][pManoDerecha], Cant = InfoPersonaje[playerid][pManoDerechaCant], string[128], BolsilloLibre;
		if(InfoInventario[Mano][Guardable] == 2 || InfoInventario[Mano][Guardable] == 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande.");
		Loop(x, 6, 0) if(InfoPersonaje[playerid][pCinturon][x] == 0)
		{
			InfoPersonaje[playerid][pCinturon][x] = Mano;
			InfoPersonaje[playerid][pCinturonCant][x] = Cant;
			RemovePlayerAttachedObject(playerid, 7);
			ResetPlayerWeapons(playerid);
			InfoPersonaje[playerid][pManoDerecha] = 0;
			InfoPersonaje[playerid][pManoDerechaCant] = 0;
			format(string, sizeof string, "enfunda su %s reglamentaria.", InfoInventario[Mano][NombreObjeto]);
			rol_ame(playerid, string);
			BolsilloLibre = 1;
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Cinturon_%d = '%d', Cantidad_cinturon_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'",
			x+1, InfoPersonaje[playerid][pCinturon][x], x+1, InfoPersonaje[playerid][pCinturonCant][x], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
		if (BolsilloLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes más huecos en tu cinturón.");
	}
	else if (mano == 2)
	{
		if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano izquierda.");
		new Mano = InfoPersonaje[playerid][pManoIzquierda], Cant = InfoPersonaje[playerid][pManoIzquierdaCant], string[128], BolsilloLibre;
		if (InfoInventario[Mano][Guardable] == 2 || InfoInventario[Mano][Guardable] == 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande.");
		Loop(x, 6, 0) if(InfoPersonaje[playerid][pCinturon][x] == 0)
		{
			InfoPersonaje[playerid][pCinturon][x] = Mano;
			InfoPersonaje[playerid][pCinturonCant][x] = Cant;
			RemovePlayerAttachedObject(playerid, 8);
			InfoPersonaje[playerid][pManoIzquierda] = 0;
			InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
			format(string, sizeof string, "enfunda su %s reglamentaria.", InfoInventario[Mano][NombreObjeto]);
			rol_ame(playerid, string);
			BolsilloLibre = 1;
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Cinturon_%d = '%d', Cantidad_cinturon_%d = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
			x+1, InfoPersonaje[playerid][pCinturon][x], x+1, InfoPersonaje[playerid][pCinturonCant][x], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
		if (BolsilloLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes más huecos en tu cinturón.");
	}
	return 1;
}

cmd:dropa(playerid)
{
	if (InfoPersonaje[playerid][pJobSkin] == 0) return SendPlayerChatMessage(playerid, -1, "No tienes puesto ninguna ropa de trabajo.");
	GivePlayerSkin(playerid, InfoPersonaje[playerid][pJobSkin]);
	InfoPersonaje[playerid][pJobSkin] = 0;
	guardar_int_mysql("personajes", "JobSkin", InfoPersonaje[playerid][pID], 0);
	return 1;
}

cmd:rellenarauto(playerid)
{
	new idcar = GetPlayerVehicleID(playerid);
	if (autorepara[playerid] == 1)
	{
		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
		    rol_ame(playerid, "llena el tanque de su vehículo.");
			veh_gasolina[idcar] += 30;
			autorepara[playerid] = 0;
		}
	}
	return 1;
}

cmd:venderarma(playerid,params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas tener al menos 2 horas para usar este comando.");
	new playerid2, precio, string[180], objeto = InfoPersonaje[playerid][pManoDerecha], objetocantidad = InfoPersonaje[playerid][pManoDerechaCant];
	if (member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes vender armas siendo policia o FBI!");
	if (GunVendedor[playerid] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya has ofrecido algo, espera la respuesta del cliente.");
	if (objeto == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en tu mano derecha mano.");
    if (InfoInventario[objeto][IDArma] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un arma en tu mano derecha.");
	if (sscanf(params, "dd", playerid2, precio)) return SendPlayerChatMessage(playerid,COLOR_WHITE,"Utiliza: /venderarma (ID) (Precio)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid,COLOR_WHITE,"Ese jugador no está conectado.");
	if (!CercaDelMarica(5.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese jugador no está cerca tuyo.");
	if (GunCliente[playerid2] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya le han ofrecido algo a ese jugador.");
	if (precio < 1 || precio > 99999) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Sólo precio desde $1 hasta $99,999.");

	new name_ofrece[65];
	if (objetocantidad == 0 || objetocantidad == 1) format(name_ofrece, sizeof name_ofrece, "%s", InfoInventario[objeto][NombreObjeto]);
	else format(name_ofrece, sizeof name_ofrece, "%s con %d balas", InfoInventario[objeto][NombreObjeto], objetocantidad);
	format(string, sizeof string, "* %s quiere venderte su %s por $%s. Usa /aceptar arma para pagarlo.", GetNameFormat(playerid), name_ofrece, diner_coma(precio));
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "* Has ofrecido tu %s a %s por $%s. Espera su respuesta.", name_ofrece, GetNameFormat(playerid2), diner_coma(precio));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	if (objetocantidad >= 2) SendPlayerChatMessage(playerid, COLOR_YELLOW, "ADVERTENCIA:{FFFFFF} Si intentas guardar el arma, tirarla, cambiarla de mano o gastarle balas, se cancela la venta.");
	GunCliente[playerid2] = playerid;
	GunObjeto[playerid2] = objeto;
	GunCantidad[playerid2] = objetocantidad;
	GunPrecio[playerid2] = precio;
	GunVendedor[playerid] = playerid2;
	return 1;
}

cmd:aceptar(playerid, params[])
{
	new string[480];
	if (isnull(params))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /aceptar (Nombre)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombres: arma - saludo - licencia - multa - coche");
		return 1;
	}
	if (strcmp(params, "arma", true) == 0) //agregado 17/01/2019 by EdinsonWalker
	{
		new playerid2 = GunCliente[playerid], objeto = GunObjeto[playerid], objetocantidad = GunCantidad[playerid], precio = GunPrecio[playerid];
		if (!IsPlayerConnected(playerid2))
		{
			GunCliente[playerid] = -1;
			GunObjeto[playerid] = 0;
			GunCantidad[playerid] = 0;
			GunPrecio[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Vendedor desconectado.");
			return 1;
		}
		if (playerid2 == -1)
		{
			GunCliente[playerid] = -1;
			GunObjeto[playerid] = 0;
			GunCantidad[playerid] = 0;
			GunPrecio[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha ofrecido un arma!");
			return 1;
		}
		if (!CercaDelMarica(5.0, playerid2, playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estás cerca del que te va a vender el arma.");
		if (GetPlayerCash(playerid) < precio)
		{
			format(string, sizeof string, "Te faltan $%s, para comprar el arma a %s.", diner_coma(precio-GetPlayerCash(playerid)), GetNameFormat(playerid2));
			SendPlayerChatMessage(playerid, COLOR_GREY, string);
			return 1;
		}
		if (InfoPersonaje[playerid2][pManoDerecha] != objeto)
		{
			GunCliente[playerid] = -1;
			GunObjeto[playerid] = 0;
			GunCantidad[playerid] = 0;
			GunPrecio[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Error en la venta, el arma del vendedor que te intenta vender ya no lo lleva en su mano derecha.");
			SendPlayerChatMessage(playerid2, COLOR_WHITE, "Error en la venta, ya no llevas el arma a vender en tu mano derecha.");
			GunVendedor[playerid2] = -1;
			return 1;
		}
		if (InfoPersonaje[playerid2][pManoDerechaCant] != objetocantidad)
		{
			GunCliente[playerid] = -1;
			GunObjeto[playerid] = 0;
			GunCantidad[playerid] = 0;
			GunPrecio[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Error en la venta, la munición del arma cambió.");
			SendPlayerChatMessage(playerid2, COLOR_WHITE, "Error en la venta, gastaste las balas del arma a vender.");
			GunVendedor[playerid2] = -1;
			return 1;
		}
	//	if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes tener tu mano derecha vacía.");
		new name_ofrece[65];
		if (objetocantidad == 0 || objetocantidad == 1) format(name_ofrece, sizeof name_ofrece, "%s", InfoInventario[objeto][NombreObjeto]);
		else format(name_ofrece, sizeof name_ofrece, "%s con %d balas", InfoInventario[objeto][NombreObjeto], objetocantidad);
		InfoPersonaje[playerid2][pManoDerecha] = 0;
		InfoPersonaje[playerid2][pManoDerechaCant] = 0;
		ResetPlayerWeapons(playerid2);
		ActualizarManos(playerid2, 1);
		GivePlayerCash(playerid2, precio, "venta de armas");
		GivePlayerCash(playerid, -precio, "venta de armas");
		if (InfoInventario[objeto][IDArma] > 0) { GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], objetocantidad); }
		InfoPersonaje[playerid][pManoDerecha] = objeto;
		InfoPersonaje[playerid][pManoDerechaCant] = objetocantidad;
		PonerObjeto(playerid, 1, objeto);
		ActualizarManos(playerid, 1);
		format(string, sizeof string, "%s compró %s a %s por $%s.", NombreDeCuenta(playerid), name_ofrece, NombreDeCuenta(playerid2), diner_coma(precio));
		Log("f_logs/venderarma.log", string);
		format(string, sizeof string, "compra %s a %s.", name_ofrece, GetNameFormat(playerid2));
		rol_auto(playerid, string);
		format(string, sizeof string, "* Pagaste $%s por %s.", diner_coma(precio), name_ofrece);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		GunVendedor[playerid2] = -1;
		GunCliente[playerid] = -1;
		GunObjeto[playerid] = 0;
		GunCantidad[playerid] = 0;
		GunPrecio[playerid] = 0;
		return 1;
	}
	else if (strcmp(params, "saludo",true) == 0)
	{
		new Count;
		foreach(Player, i)
		{
			if (GetPVarInt(i, "shrequest") == playerid)
			{
				new Float: ppFloats[3];
				GetPlayerPos(i, ppFloats[0], ppFloats[1], ppFloats[2]);
				if (!IsPlayerInRangeOfPoint(playerid, 5, ppFloats[0], ppFloats[1], ppFloats[2]))
				{
					Count++;
					SendPlayerChatMessage(playerid, COLOR_WHITE, "Estás demasiado lejos. No puedes aceptar el saludo ahora.");
				}
				else
				{
					switch (GetPVarInt(i, "shstyle"))
					{
						case 1:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "hndshkaa", 4.0, 1, 1, 1, 0, 1000,1);
							ApplyAnimation( i, "GANGS", "hndshkaa", 4.0, 1, 1, 1, 0, 1000,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 2:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "hndshkba", 4.0, 1, 1, 1, 0, 1000,1);
							ApplyAnimation( i, "GANGS", "hndshkba", 4.0, 1, 1, 1, 0, 1000,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 3:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "hndshkca", 4.0, 1, 1, 1, 0, 1000,1);
							ApplyAnimation( i, "GANGS", "hndshkca", 4.0, 1, 1, 1, 0, 1000,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 4:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "hndshkcb", 4.0, 1, 1, 1, 0, 1000,1);
							ApplyAnimation( i, "GANGS", "hndshkca", 4.0, 1, 1, 1, 0, 1000,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 5:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "hndshkda", 4.0, 1, 1, 1, 0, 1000,1);
							ApplyAnimation( i, "GANGS", "hndshkca", 4.0, 1, 1, 1, 0, 1000,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 6:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS","hndshkfa_swt", 4.0, 1, 1, 1, 0, 2600,1);
							ApplyAnimation( i, "GANGS","hndshkfa_swt", 4.0, 1, 1, 1, 0, 2600,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 7:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "prtial_hndshk_01", 4.0, 1, 1, 1, 0, 1250,1);
							ApplyAnimation( i, "GANGS", "prtial_hndshk_01", 4.0, 1, 1, 1, 0, 1250,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
						case 8:
						{
							Count++;
							PlayerFacePlayer( playerid, i );
							ApplyAnimation( playerid, "GANGS", "prtial_hndshk_biz_01", 3.7, 1, 1, 1, 0, 2200,1);
							ApplyAnimation( i, "GANGS", "prtial_hndshk_biz_01", 3.5, 1, 1, 1, 0, 2200,1);
							SetPVarInt(i, "shrequest", INVALID_PLAYER_ID);
							format(string, sizeof string, "se saluda con %s.", GetNameFormat(playerid));
							rol_ame(i, string);
							DeletePVar(i, "shstyle");
						}
					}
				}
			}
		}
		if (Count == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha saludado.");
	}
	else if (strcmp(params,"multa",true) == 0)
	{
		if (TicketOffer[playerid] == 999) return SendPlayerChatMessage(playerid, COLOR_WHITE, "{FFFF00}[ERROR]:{FFFFFF} Nadie te multado.");
		rol_ame(playerid, "paga una multa.");
		format(string, sizeof string, " %s pagó una multa de %d$.", GetNameFormat(playerid), TicketMoney[playerid]);
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		SendPlayerChatMessage(TicketOffer[playerid], COLOR_LIGHTBLUE, string);
		GivePlayerCash(playerid, -TicketMoney[playerid], "aceptar multa");
		Tax += TicketMoney[playerid];
		TicketOffer[playerid] = 999;
		TicketMoney[playerid] = 0;
		Facturing[playerid] = 0;
	}
	else if (strcmp(params,"licencia",true) == 0)
	{
		if (NombreLicencia[playerid] == 999) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha ofrecido una licencia.");
		if (CheckMoney(playerid, PrecioLicencia[playerid]) == 0)
		{
   			NombreLicencia[playerid] = 999;
			PrecioLicencia[playerid] = 0;
			Facturing[playerid] = 0;
			SendPlayerChatMessage(NombreLicencia[playerid], 0xEBEBEBFF, "El sujeto no tiene suficiente dinero para pagar la licencia.");
			return 1;
		}
		rol_ame(playerid, "obtiene una licencia de armas.");
		GivePlayerCash(playerid, -PrecioLicencia[playerid], "aceptar licencia");
		Tax += PrecioLicencia[playerid];
		InfoPersonaje[playerid][pLicencia][3] = 1;
		guardar_int_mysql("personajes", "Licencia4", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pLicencia][3]);
		NombreLicencia[playerid] = 999;
		PrecioLicencia[playerid] = 0;
		Facturing[playerid] = 0;
	}
	else if (strcmp(params, "coche", true) == 0) //corregido 09/01/2019 by EdinsonWalker
	{
		new playerid2 = Pla_vehicle[playerid], veh = Osql_vehicle[playerid], precio = Price_vehicle[playerid];
		if (!IsPlayerConnectedEx(playerid2))
		{
			Osql_vehicle[playerid] = 0;
			Pla_vehicle[playerid] = 999;
			Price_vehicle[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Vendedor desconectado.");
			return 1;
		}
		if (playerid2 == 999)
		{
			Osql_vehicle[playerid] = 0;
			Pla_vehicle[playerid] = 999;
			Price_vehicle[playerid] = 0;
			SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha ofrecido un coche!");
			return 1;
		}
		if (!CercaDelMarica(8.0, playerid2, playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estás cerca del que te va a vender el vehículo.");
		if (GetPlayerCash(playerid) < precio)
		{
			format(string, sizeof string, "Te faltan $%s, para comprar el vehículo a %s.", diner_coma(precio-GetPlayerCash(playerid)), GetNameFormat(playerid2));
			SendPlayerChatMessage(playerid, COLOR_GREY, string);
			return 1;
		}
		new vehicleid = InfoVehiculo[veh][vIG_id];
		if (!IsPlayerInVehicle(playerid2, vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El vendedor debe estar dentro del vehículo que te va a vender.");
		if (DetectarMaxVehiculos(playerid) == 1)
		{
			Osql_vehicle[playerid] = 0;
			Pla_vehicle[playerid] = 999;
			Price_vehicle[playerid] = 0;
			return 1;
		}
		//
		new ip[32], ipex[32];
		GetPlayerIp(playerid, ip, sizeof(ip));
		GetPlayerIp(playerid2, ipex, sizeof(ipex));
		format(string, sizeof string, "%s (IP: %s) pagó $%s a %s por el %s (IP: %s)", NombreDeCuenta(playerid), ip, diner_coma(precio), NombreDeCuenta(playerid2), GetVehicleName(vehicleid), ipex);
		Log("f_logs/pay.log", string);
		format(string, sizeof string, "* Has pagado $%s a %s por su %s. (Usa /ayuda vehículo para más información)", diner_coma(precio), GetNameFormat(playerid2), GetVehicleName(vehicleid));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		format(string, sizeof string, "* Vendiste tu %s a %s por $%s.", GetVehicleName(vehicleid), GetNameFormat(playerid), diner_coma(precio));
		SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
		format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) le compró un %s por $%s a %s(%d).", GetNameFormat(playerid), playerid, GetVehicleName(vehicleid), diner_coma(precio), GetNameFormat(playerid2), playerid2);
		SendAdminMessage(0xFFFFFFFF, string);
		if (!strcmp(InfoCuenta[playerid][jIP], InfoCuenta[Pla_vehicle[playerid]][jIP], false) && InfoCuenta[playerid][jMulticuenta] == 0 && InfoCuenta[Pla_vehicle[playerid]][jMulticuenta] == 0)
		{
			// Si las IP son iguales y ambos son multicuentas NO AUTORIZADAS = 0.
			new ipc[32], stringlog[180]; GetPlayerIp(playerid, ipc, 32);
			format(stringlog, sizeof(stringlog), "[ATENCIÓN] Posibles multicuentas: %s(%d) ha vendido un vehículo a %s(%d). [IP: %s]", GetNameFormat(playerid2), playerid2, GetNameFormat(playerid), playerid, ipc);
			SendAdminMessage(COLOR_YELLOW, stringlog); Log("f_logs/multicuentas.log", stringlog);
		}
		GivePlayerCash(playerid2, precio, "venta de vehiculo");
		GivePlayerCash(playerid, -precio, "venta de vehiculo");
		RemovePlayerFromVehicle(playerid2);
		new Float:slx, Float:sly, Float:slz, query3[186];
		GetPlayerPos(playerid2, slx, sly, slz);
		SetPlayerPosEx(playerid2, slx, sly, slz+2);
		PutPlayerInVehicleEx(playerid, vehicleid, 0);
		//actualizar vehículo
		alm(InfoVehiculo[veh][vPropietario], InfoPersonaje[playerid][pNombre_Apellido]);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE vehiculos SET Propietario = '%e' WHERE ID = '%d'", InfoVehiculo[veh][vPropietario], InfoVehiculo[veh][vID_sql]);
		mysql_tquery(db_samp, query3);
		Osql_vehicle[playerid] = 0;
		Pla_vehicle[playerid] = 999;
		Price_vehicle[playerid] = 0;
		return 1;
	}
	return 1;
}

cmd:heridas(playerid, params[])
{
	new id;
	if (sscanf(params, "u", id)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /heridas (JugadorID)");
	if (!IsPlayerConnected(id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Usuario no conectado.");
	if (!CercaDelWeon(7.0, playerid, id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Estás lejos del jugador.");
	ShowPlayerHeridas(id, playerid);
	return 1;
}

//comandos toys renovado by EdinsonWalker (18/01/2020)
cmd:ayudatoy(playerid)
{
	SendPlayerChatMessage(playerid, COLOR_GENERAL, "Ayuda - Accesorios (Toys)");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Para comprar un toy en la tienda usa: {3E62F4}/ctoys");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Para abrir el menú de toys: {3E62F4}/toys");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Para colocarte todos tus toys usa: {3E62F4}/ptoys");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Para retirarte todos tus toys usa: {3E62F4}/qtoys");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Para colocar o retirar un determinado toy usa: {3E62F4}/toy (0-6 slot)");
	return 1;
}

cmd:toys(playerid)
{
	new dialog[4096] = "Objeto\tParte\tColocado\n", dialog2[512], count = 0;
	Loop(x, 7, 0)
	{
		if (InfoPersonaje[playerid][ptModelo][x] != 0) format(dialog2, sizeof dialog2, "{FFFFFF}%s\t{9A9A9A}%s\t%s\n", GetNameToy(playerid, x), GetParteToy(playerid, x), GetStatusToy(playerid, x)), count++;
		else alm(dialog2, "{CCCCCC}—\n");
		strcat(dialog, dialog2);
	}
	if (count == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Toys", "{EBEBEB}No tienes ningún {3E62F4}toy{EBEBEB} en tu cuenta.", "Cerrar", "");
	Dialog_Show(playerid, ShowToys, DIALOG_STYLE_TABLIST_HEADERS, "Toys", dialog, "Continuar", "Salir");
	return 1;
}

Dialog:ShowToys(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new id = listitem;
	if (InfoPersonaje[playerid][ptModelo][id] == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes ningún toy en ese slot.");
 	slotselection[playerid] = id;
	indice_toy(playerid, id);
	return 1;
}

indice_toy(playerid, id)
{
	new gtitulo[128], gformat[512], dialog[2056];
	format(gtitulo, sizeof gtitulo, "Toy: {FE9A2E}%s", GetNameToy(playerid, id));
	if (InfoCuenta[playerid][jVIP] == 2)
	{
		format(gformat, sizeof gformat, "{FFFFFF}Edición personalizada\nEditar parte: {b42d2d}%s{FFFFFF}\n%s\nEliminar toy\n", GetParteToy(playerid, id), (InfoPersonaje[playerid][ptColocado][id]) ? ("{ED3F3F}Retirar toy{FFFFFF}") : ("{64CA46}Colocar toy{FFFFFF}"));
		strcat(dialog, gformat);
		format(gformat, sizeof gformat, "{FFFFFF}Editar color: %s", GetColorToy(playerid, id));
		strcat(dialog, gformat);
	}
	else
	{
		format(gformat, sizeof gformat, "{FFFFFF}Edición personalizada\nEditar parte: {b42d2d}%s{FFFFFF}\n%s\nEliminar toy", GetParteToy(playerid, id), (InfoPersonaje[playerid][ptColocado][id]) ? ("{ED3F3F}Retirar toy{FFFFFF}") : ("{64CA46}Colocar toy{FFFFFF}"));
		strcat(dialog, gformat);
	}
	Dialog_Show(playerid, Show2Toys, DIALOG_STYLE_LIST, gtitulo, dialog, "Continuar", "Volver");
	return 1;
}

Dialog:Show2Toys(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_toys(playerid);
	new x = slotselection[playerid];
	if (x == -1) return 1;
	switch (listitem)
	{
		case 0: //edición personalizada
		{
			SetPlayerAttachedObject(playerid, x, InfoPersonaje[playerid][ptModelo][x], InfoPersonaje[playerid][ptHueso][x], InfoPersonaje[playerid][ptPosX][x], InfoPersonaje[playerid][ptPosY][x], InfoPersonaje[playerid][ptPosZ][x],
			InfoPersonaje[playerid][ptRotX][x], InfoPersonaje[playerid][ptRotY][x], InfoPersonaje[playerid][ptRotZ][x], InfoPersonaje[playerid][ptScaleX][x], InfoPersonaje[playerid][ptScaleY][x], InfoPersonaje[playerid][ptScaleZ][x],
			SetColorToy(InfoPersonaje[playerid][ptColor][x]));
			EditAttachedObject(playerid, x);
			Editing[playerid] = 1;
			SendPlayerChatMessage(playerid, 0xFFFFFFFF, "* Mantén presionado {3E62F4}~k~~PED_SPRINT~{FFFFFF} para cambiar la posición de la cámara.");
		}
		case 1: //editar parte
		{
			new gtitulo[128], gformat[512];
			format(gtitulo, sizeof gtitulo, "Parte actual: {FE9A2E}%s", GetParteToy(playerid, x));
			format(gformat, sizeof gformat, "Columna vertebral\nCabeza\nBrazo izquierdo\nBrazo derecho\nMano izquierda\nMano derecha\nMuslo izquierdo\nMuslo derecho\n\
			Pie izquierdo\nPie derecho\nPantorrilla derecha\nPantorrilla izquierda\nAntebrazo izquierdo\nAntebrazo derecho\nClavicula izquierda\nClavicula derecha\nCuello\nQuijada");
			Dialog_Show(playerid, EditarParteToy, DIALOG_STYLE_LIST, gtitulo, gformat, "Continuar", "Volver");
		}
		case 2: //colocar/remover
		{
			new string[243];
			if (InfoPersonaje[playerid][ptColocado][x])
			{
				RemovePlayerAttachedObject(playerid, x);
				InfoPersonaje[playerid][ptColocado][x] = 0;
				format(string, sizeof string, "Te has retirado %s. ({FFFFFF}Parte: %s{ED3F3F})", GetNameToy(playerid, x), GetParteToy(playerid, x));
				SendPlayerChatMessage(playerid, 0xED3F3FFF, string);
			}
			else
			{
				SetPlayerAttachedObject(playerid, x, InfoPersonaje[playerid][ptModelo][x], InfoPersonaje[playerid][ptHueso][x], InfoPersonaje[playerid][ptPosX][x], InfoPersonaje[playerid][ptPosY][x], InfoPersonaje[playerid][ptPosZ][x],
				InfoPersonaje[playerid][ptRotX][x], InfoPersonaje[playerid][ptRotY][x], InfoPersonaje[playerid][ptRotZ][x], InfoPersonaje[playerid][ptScaleX][x], InfoPersonaje[playerid][ptScaleY][x], InfoPersonaje[playerid][ptScaleZ][x],
				SetColorToy(InfoPersonaje[playerid][ptColor][x]));
				InfoPersonaje[playerid][ptColocado][x] = 1;
				format(string, sizeof string, "Te has colocado %s. ({FFFFFF}Parte: %s{64CA46})", GetNameToy(playerid, x), GetParteToy(playerid, x));
				SendPlayerChatMessage(playerid, 0x64CA46FF, string);
			}
			ActualizarToy(playerid, x);
		}
		case 3: //eliminar toy
		{
			new gtitulo[128];
			format(gtitulo, sizeof gtitulo, "Toy: {FE9A2E}%s", GetNameToy(playerid, x));
			Dialog_Show(playerid, EliminarToy, DIALOG_STYLE_MSGBOX, gtitulo, "{FFFFFF}¿Estás seguro de eliminar este toy?", "Continuar", "Volver");
		}
		case 4: //personalizar color 1
		{
			new gtitulo[128], str[1024];
			format(gtitulo, sizeof gtitulo, "Color actual: %s", GetColorToy(playerid, x));
			format(str, sizeof str, "Color predeterminado\n");
			Loop(e, sizeof InfoColorToy, 0)
			{
	 			format(str, sizeof str, "%s{%.6s}%s\n", str, InfoColorToy[e][ctColor][2], InfoColorToy[e][ctNombre]);
			}
			Dialog_Show(playerid, ChangeToyColor, DIALOG_STYLE_LIST, gtitulo, str, "Continuar", "Volver");
		}
	}
	return 1;
}

Dialog:EditarParteToy(playerid, response, listitem, inputtext[])
{
	new x = slotselection[playerid], string[232];
	if (x == -1) return 1;
	if (!response) return indice_toy(playerid, x);
	InfoPersonaje[playerid][ptHueso][x] = listitem+1;
	if (InfoPersonaje[playerid][ptColocado][x] != 0)
	{
	    RemovePlayerAttachedObject(playerid, x);
		SetPlayerAttachedObject(playerid, x, InfoPersonaje[playerid][ptModelo][x], InfoPersonaje[playerid][ptHueso][x], InfoPersonaje[playerid][ptPosX][x], InfoPersonaje[playerid][ptPosY][x], InfoPersonaje[playerid][ptPosZ][x],
		InfoPersonaje[playerid][ptRotX][x], InfoPersonaje[playerid][ptRotY][x], InfoPersonaje[playerid][ptRotZ][x], InfoPersonaje[playerid][ptScaleX][x], InfoPersonaje[playerid][ptScaleY][x], InfoPersonaje[playerid][ptScaleZ][x],
		SetColorToy(InfoPersonaje[playerid][ptColor][x]));
	}
	ActualizarToy(playerid, x);
	format(string, sizeof string, "Editaste la parte del toy %s. ({b42d2d}Parte: %s{FFFFFF})", GetNameToy(playerid, x), GetParteToy(playerid, x));
	SendPlayerChatMessage(playerid, 0x00AACCFF, string);
	pc_cmd_toys(playerid);
	return 1;
}

Dialog:EliminarToy(playerid, response, listitem, inputtext[])
{
	new x = slotselection[playerid], string[232];
	if (x == -1) return 1;
	if (!response) return indice_toy(playerid, x);
	format(string, sizeof string, "Eliminaste el toy %s. ({b42d2d}Parte: %s{FFFFFF})", GetNameToy(playerid, x), GetParteToy(playerid, x));
	SendPlayerChatMessage(playerid, 0x00AACCFF, string);
	if (IsPlayerAttachedObjectSlotUsed(playerid, x)) RemovePlayerAttachedObject(playerid, x);
	InfoPersonaje[playerid][ptModelo][x] = 0;
	InfoPersonaje[playerid][ptHueso][x] = 0;
	InfoPersonaje[playerid][ptPosX][x] = 0.0;
	InfoPersonaje[playerid][ptPosY][x] = 0.0;
	InfoPersonaje[playerid][ptPosZ][x] = 0.0;
	InfoPersonaje[playerid][ptPosX][x] = 0.0;
	InfoPersonaje[playerid][ptPosY][x] = 0.0;
	InfoPersonaje[playerid][ptPosZ][x] = 0.0;
	InfoPersonaje[playerid][ptScaleZ][x] = 0.0;
	InfoPersonaje[playerid][ptScaleY][x] = 0.0;
	InfoPersonaje[playerid][ptScaleX][x] = 0.0;
	InfoPersonaje[playerid][ptColocado][x] = 0;
	InfoPersonaje[playerid][ptColor][x] = -1;
	ActualizarToy(playerid, x);
	return 1;
}

Dialog:ChangeToyColor(playerid, response, listitem, inputtext[])
{
	new x = slotselection[playerid], string[195];
	if (x == -1) return 1;
	if (!response) return indice_toy(playerid, x);
	new color = listitem-1;
	InfoPersonaje[playerid][ptColor][x] = color;
	format(string, sizeof string, "Cambiaste el color de tu %s (%d) al %s", GetNameToy(playerid, x), x+1, GetColorToy(playerid, x));
	SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
	if (InfoPersonaje[playerid][ptColocado][x] != 0)
	{
		RemovePlayerAttachedObject(playerid, x);
		SetPlayerAttachedObject(playerid, x, InfoPersonaje[playerid][ptModelo][x], InfoPersonaje[playerid][ptHueso][x], InfoPersonaje[playerid][ptPosX][x], InfoPersonaje[playerid][ptPosY][x], InfoPersonaje[playerid][ptPosZ][x],
		InfoPersonaje[playerid][ptRotX][x], InfoPersonaje[playerid][ptRotY][x], InfoPersonaje[playerid][ptRotZ][x], InfoPersonaje[playerid][ptScaleX][x], InfoPersonaje[playerid][ptScaleY][x], InfoPersonaje[playerid][ptScaleZ][x],
		SetColorToy(InfoPersonaje[playerid][ptColor][x]));
	}
	ActualizarToy(playerid, x);
	return 1;
}

cmd:toy(playerid, params[])
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes usar este comando en este momento.");
	new toyslot, string[128];
	if (sscanf(params, "d", toyslot)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /toy [slot (0-6)]");
	if (toyslot < 0 || toyslot > 6) return SendPlayerChatMessage(playerid, COLOR_GRAD1, "{FFFF00}[ERROR]:{FFFFFF} Los Slots de los toys son del número 0 al 6.");
	if (InfoPersonaje[playerid][ptModelo][toyslot] == 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No tienes ningún toy en ese slot.");
	if (InfoPersonaje[playerid][ptColocado][toyslot])
	{
		format(string, sizeof string, "Te has retirado %s. ({FFFFFF}Parte: %s{ED3F3F})", GetNameToy(playerid, toyslot), GetParteToy(playerid, toyslot));
		SendPlayerChatMessage(playerid, 0xED3F3FFF, string);
		RemovePlayerAttachedObject(playerid, toyslot);
		InfoPersonaje[playerid][ptColocado][toyslot] = 0;
	}
	else
	{
		SetPlayerAttachedObject(playerid, toyslot, InfoPersonaje[playerid][ptModelo][toyslot], InfoPersonaje[playerid][ptHueso][toyslot], InfoPersonaje[playerid][ptPosX][toyslot], InfoPersonaje[playerid][ptPosY][toyslot], InfoPersonaje[playerid][ptPosZ][toyslot],
		InfoPersonaje[playerid][ptRotX][toyslot], InfoPersonaje[playerid][ptRotY][toyslot], InfoPersonaje[playerid][ptRotZ][toyslot], InfoPersonaje[playerid][ptScaleX][toyslot], InfoPersonaje[playerid][ptScaleY][toyslot], InfoPersonaje[playerid][ptScaleZ][toyslot],
		SetColorToy(InfoPersonaje[playerid][ptColor][toyslot]));
		InfoPersonaje[playerid][ptColocado][toyslot] = 1;
		format(string, sizeof string, "Te has colocado %s. ({FFFFFF}Parte: %s{64CA46})", GetNameToy(playerid, toyslot), GetParteToy(playerid, toyslot));
		SendPlayerChatMessage(playerid, 0x64CA46FF, string);
	}
	ActualizarToy(playerid, toyslot);
	return 1;
}

cmd:ptoys(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes usar este comando en este momento.");
	new count = 0, gformat[130];
	Loop(listitem, 7, 0) if (InfoPersonaje[playerid][ptModelo][listitem] != 0)
	{
		SetPlayerAttachedObject(playerid, listitem, InfoPersonaje[playerid][ptModelo][listitem], InfoPersonaje[playerid][ptHueso][listitem], InfoPersonaje[playerid][ptPosX][listitem], InfoPersonaje[playerid][ptPosY][listitem], InfoPersonaje[playerid][ptPosZ][listitem],
		InfoPersonaje[playerid][ptRotX][listitem], InfoPersonaje[playerid][ptRotY][listitem], InfoPersonaje[playerid][ptRotZ][listitem], InfoPersonaje[playerid][ptScaleX][listitem], InfoPersonaje[playerid][ptScaleY][listitem], InfoPersonaje[playerid][ptScaleZ][listitem],
		SetColorToy(InfoPersonaje[playerid][ptColor][listitem]));
		count++;
		InfoPersonaje[playerid][ptColocado][listitem] = 1;
		ActualizarToy(playerid, listitem);
	}
	if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes toys.");
	if (count == 1) format(gformat, sizeof gformat, "Te has colocado 1 toy.");
	else format(gformat, sizeof gformat, "Te has colocado %d toys.", count);
	SendPlayerChatMessage(playerid, COLOR_GREEN, gformat);
	return 1;
}

cmd:qtoys(playerid)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes usar este comando en este momento.");
	new count = 0, gformat[130];
	Loop(listitem, 7, 0) if (InfoPersonaje[playerid][ptModelo][listitem] != 0)
	{
		RemovePlayerAttachedObject(playerid, listitem);
		count++;
		InfoPersonaje[playerid][ptColocado][listitem] = 0;
		ActualizarToy(playerid, listitem);
	}
	if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes toys.");
	if (count == 1) format(gformat, sizeof gformat, "Te has removido 1 toy.", count);
	else format(gformat, sizeof gformat, "Te has removido %d toys.", count);
	SendPlayerChatMessage(playerid, COLOR_GREEN, gformat);
	return 1;
}

//nombre temporal admin

cmd:su(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (OnDuty[playerid] == 0) return  SendPlayerChatMessage(playerid, COLOR_WHITE, "No estas en servicio.");
	new playerid2;
	if (sscanf(params, "u", playerid2)) SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /su (PlayerID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador seleccionado está desconectado.");
	if (InfoPersonaje[playerid2][pEstrellas] == 6) return SendPlayerChatMessage(playerid, 0xb00000ff, "Ese jugador ya tiene el máximo de estrellas (6).");
	InfoPersonaje[playerid2][pEstrellas]++;
	guardar_int_mysql("personajes", "Estrellas", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pEstrellas]);
	SendClientMessageEx(playerid, COLOR_YELLOW, "Colocaste una estrella de busqueda a %s, ahora tiene %d.", GetNameFormat(playerid2), InfoPersonaje[playerid2][pEstrellas]);
	SetPlayerWantedLevel(playerid2, InfoPersonaje[playerid2][pEstrellas]);
	return 1;
}

cmd:sospechosos(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	new string[128], x;
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, "Sospechosos buscados:");
	foreach(Player, i)
	{
		if (InfoPersonaje[i][pEstrellas] >= 2)
		{
			format(string, sizeof string, "%s%s: %d", string,GetNameFormat(i),InfoPersonaje[i][pEstrellas]);
			x++;
			if (x > 3)
			{
				SendPlayerChatMessage(playerid, COLOR_WHITE, string);
				x = 0;
				format(string, sizeof string, " ");
			}
			else format(string, sizeof string, "%s, ", string);
		}
	}
	if (x <= 3 && x > 0)
	{
		string[strlen(string)-2] = '.';
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	}
	return 1;
}

cmd:bk(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la policía o sheriff.");
	if (tipo_refuerzos[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes un pedido de ayuda, usa /noref.");
	new string[256];
	format(string, sizeof string, "[CENTRAL] Todas las unidades, %s necesita ayuda (Información marcada).", GetNameFormat(playerid));
	if (member_faccion(playerid, 1)) //pd
	{
		refuerzos_pd[playerid] = 1;
		SendRadioMessage(1, 0xF07A7AFF, string, 3);
		Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1) && OnDuty[i] == 1)
		{
			SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
		}
	}
	else if (member_faccion(playerid, 2)) //fbi
	{
		refuerzos_fbi[playerid] = 1;
		SendRadioMessage(2, 0xF07A7AFF, string, 0);
		Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 2) && OnDuty[i] == 1)
		{
			SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
		}
	}
	else if (member_faccion(playerid, 4)) //pd
	{
		refuerzos_sd[playerid] = 1;
		SendRadioMessage(4, 0xF07A7AFF, string, 3);
		Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 4) && OnDuty[i] == 1)
		{
			SetPlayerMarkerForPlayer(i, playerid, 0x22FF00FF);
		}
	}
	tipo_refuerzos[playerid] = 1;
	SendPlayerChatMessage(playerid, COLOR_ORANGE, "/noref, para cancelar los refuerzos.");
	return 1;
}
alias:bk("ref", "ref1", "refuerzos");

cmd:bk2(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la policía o sheriff.");
	if (tipo_refuerzos[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes un pedido de ayuda, usa /noref.");
	new string[256];
	format(string, sizeof string, "[CENTRAL] Todas las unidades, %s (%s) necesita ayuda (Información marcada).", GetNameFormat(playerid), InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo]);
	SendRadioMessage(1, 0xF07A7AFF, string, 0);
	SendRadioMessage(2, 0xF07A7AFF, string, 0);
	SendRadioMessage(4, 0xF07A7AFF, string, 0);
	tipo_refuerzos[playerid] = 2;
	Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1, 2, 4) && OnDuty[i] == 1)
	{
		SetPlayerMarkerForPlayer(i, playerid, 0xFFF400FF);
	}
	SendPlayerChatMessage(playerid, COLOR_ORANGE, "/noref, para cancelar los refuerzos.");
	return 1;
}
alias:bk2("ref2", "refuerzos2");

cmd:bk3(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la policía, sheriff o lsfd.");
	if (tipo_refuerzos[playerid] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ya tienes un pedido de ayuda, usa /noref.");
	new string[256];
	format(string, sizeof string, "[CENTRAL] Todas las unidades, %s (%s) necesita ayuda (Información marcada).", GetNameFormat(playerid), InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo]);
	SendRadioMessage(1, 0xF07A7AFF, string, 0);
	SendRadioMessage(2, 0xF07A7AFF, string, 0);
	SendRadioMessage(4, 0xF07A7AFF, string, 0);
	SendRadioMessage(6, 0xF07A7AFF, string, 0);
	tipo_refuerzos[playerid] = 3;
	Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1, 2, 4, 6) && OnDuty[i] == 1)
	{
		SetPlayerMarkerForPlayer(i, playerid, 0xFF0000FF);
	}
	SendPlayerChatMessage(playerid, COLOR_ORANGE, "/noref, para cancelar los refuerzos.");
	return 1;
}
alias:bk3("ref3", "refuerzos3");

cmd:bkc(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la policía, sheriff o lsfd.");
	if (tipo_refuerzos[playerid] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás solicitando refuerzos.");
	new string[256];
	switch (tipo_refuerzos[playerid])
	{
		case 1: //pd o sd
		{
			refuerzos_pd[playerid] = 0;
			refuerzos_sd[playerid] = 0;
			refuerzos_fbi[playerid] = 0;
			tipo_refuerzos[playerid] = 0;
			format(string, sizeof string, "[CENTRAL] Todas las unidades que están de apoyo a %s, se ha cancelado el llamado.", GetNameFormat(playerid));
			if (member_faccion(playerid, 1)) //pd
			{
				SendRadioMessage(1, 0xF07A7AFF, string, 0);
				Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1) && OnDuty[i] == 1)
				{
					SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
				}
			}
			else if (member_faccion(playerid, 2)) //fbi
			{
				SendRadioMessage(2, 0xF07A7AFF, string, 0);
				Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 2) && OnDuty[i] == 1)
				{
					SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
				}
			}
			else if (member_faccion(playerid, 4)) //sd
			{
				SendRadioMessage(4, 0xF07A7AFF, string, 0);
				Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 4) && OnDuty[i] == 1)
				{
					SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
				}
			}
		}
		case 2: // conjunto pd y sd
		{
			tipo_refuerzos[playerid] = 0;
			format(string, sizeof string, "[CENTRAL] Todas las unidades que están de apoyo a %s (%s), se ha cancelado el llamado.", GetNameFormat(playerid), InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo]);
			SendRadioMessage(1, 0xF07A7AFF, string, 0);
			SendRadioMessage(2, 0xF07A7AFF, string, 0);
			SendRadioMessage(4, 0xF07A7AFF, string, 0);
			Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1, 4) && OnDuty[i] == 1)
			{
				SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
			}
		}
		case 3: // refuerzos de fd a sd y pd
		{
			tipo_refuerzos[playerid] = 0;
			format(string, sizeof string, "[CENTRAL] Todas las unidades que están de apoyo a %s (%s), se ha cancelado el llamado.", GetNameFormat(playerid), InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo]);
			SendRadioMessage(1, 0xF07A7AFF, string, 0);
			SendRadioMessage(2, 0xF07A7AFF, string, 0);
			SendRadioMessage(4, 0xF07A7AFF, string, 0);
			SendRadioMessage(6, 0xF07A7AFF, string, 0);
			Loop(i, MAX_PLAYERS, 0) if (member_faccion(i, 1, 2, 4, 6) && OnDuty[i] == 1)
			{
				SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
			}
		}
	}
	return 1;
}
alias:bkc("bpc", "noref", "norefuerzos");

cmd:darlicencia(playerid, params[])
{
	if (!Propietario_faccion(playerid, 1, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo líder de LSPD o LSCSD.");
	new playerid2, precio;
	if (sscanf(params, "dd", playerid2, precio)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darlicencia (JugadorID) (Precio)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa ID es inválida, jugador desconectado.");
	if (!CercaDelMarica(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Muy lejos de el jugador.");
	if (InfoPersonaje[playerid2][pLicencia][3] != 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Este jugador ya tiene una licencia de armas trámitada.");
	if (precio < 0 || precio > 50000) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El precio máximo para la licencia de armas es 50 mil dólares.");
	if (Facturing[playerid2] == 1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Este jugador ya tiene una petición pendiente.");
	if (InfoPersonaje[playerid2][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "[ERROR] Este usuario no tiene más de 2 horas de juego o dispone de restricción de armas.");
	new string[290];
	if (GetPlayerCash(playerid2) < precio)
	{
		format(string, sizeof string, "* Esa persona no dispone de {FFFF00}%s${FFFFFF} para pagar la licencia de armas.", diner_coma(precio));
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		return 1;
	}
	format(string, sizeof string, "* Oficial {3052DC}%s{EBEBEB} te ofrece una licencia de armas por {00CC00}$%s{EBEBEB}.", GetNameFormat(playerid), diner_coma(precio));
	SendPlayerChatMessage(playerid2, 0xEBEBEBFF, string);
	SendPlayerChatMessage(playerid2, 0xEBEBEBFF, "Utiliza {3E62F4}/aceptar licencia{EBEBEB} ó {3E62F4}/cancelar licencia{EBEBEB}.");
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Espera la respuesta del sujeto, espere un momento.");
	NombreLicencia[playerid2] = playerid;
	PrecioLicencia[playerid2] = precio;
	Facturing[playerid2] = 1; // ID ocupado en la tarea.
	return 1;
}

cmd:multar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (OnDuty[playerid] == 0) return  SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en servicio.");
	if (sscanf(params, "dis[64]", params[0], params[1], params[2])) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /multar (ID) (precio) (razón)");
	if (!IsPlayerConnected(params[0])) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	if (!CercaDelMarica(8.0,playerid,params[0])) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Muy lejos de el jugador.");
	if (Facturing[playerid] == 1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Este jugador ya tiene una petición pendiente.");
	if (params[1] < 0 || params[1] > 2000) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El máximo de multa son $2,000.");
	new string[170];
	if (GetPlayerCash(params[0]) < params[1])
	{
		format(string, sizeof string, "* El infractor no tiene {FFFF00}%s${FFFFFF} para pagar la multa.", diner_coma(params[1]));
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		return 1;
	}
	ClearChat(playerid);
	SendPlayerChatMessage(params[0], -1, "Estado de San Andreas");
	format(string, sizeof string, "Demandante: %s", GetNameFormat(playerid));
	SendPlayerChatMessage(params[0], -1, string);
	format(string, sizeof string, "Infracción: %s", params[2]);
	SendPlayerChatMessage(params[0], -1, string);
	format(string, sizeof string, "Multa: %s$", diner_coma(params[1]));
	SendPlayerChatMessage(params[0], -1, string);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "* Espera la respuesta del sujeto");
	SendPlayerChatMessage(params[0], COLOR_WHITE, "Te han multado. Utiliza /aceptar multa ó /cancelar multa, para pagar la multa.");
	TicketOffer[params[0]] = playerid;
	TicketMoney[params[0]] = params[1];
	Facturing[params[0]] = 1;
	return 1;
}

cmd:m(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No estás en un vehículo.");
	if (sscanf(params, "s[256]", params)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /m (texto)");
	new string[320];
	format(string, sizeof string, "(Megáfono) {player:%d}: %s", playerid, params[0]);
	ProxDetector(60.0, playerid, string, COLOR_MEGAPHONE, COLOR_MEGAPHONE, COLOR_MEGAPHONE, COLOR_MEGAPHONE, COLOR_MEGAPHONE);
	return 1;
}

cmd:quitar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (OnDuty[playerid] == 0) return  SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en servicio.");
	new item[32], string[190], playerid2;
	if (sscanf(params, "ds[32]",playerid2,item))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /quitar (JugadorID) (Item)");
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Items: lconduccion, lvuelo, larma, armas");
		return 1;
	}
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador no conectado.");
	if (!CercaDelMarica(5.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Jugador muy lejos.");
	if (strcmp(item, "lconduccion", true) == 0)
	{
	    if (InfoPersonaje[playerid2][pLicencia][0] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no tiene licencia de conducción.");
		InfoPersonaje[playerid2][pLicencia][0] = 0;
		guardar_int_mysql("personajes", "Licencia1", InfoPersonaje[playerid2][pID], 0);
		format(string, sizeof string, "le quita la licencia de conducción a %s.", GetNameFormat(playerid2));
		rol_auto(playerid, string);
	}
	else if (strcmp(item, "lvuelo", true) == 0)
	{
	    if (InfoPersonaje[playerid2][pLicencia][1] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no tiene licencia de vuelo.");
		InfoPersonaje[playerid2][pLicencia][1] = 0;
		guardar_int_mysql("personajes", "Licencia2", InfoPersonaje[playerid2][pID], 0);
		format(string, sizeof string, "le quita la licencia de vuelo a %s.", GetNameFormat(playerid2));
		rol_auto(playerid, string);
	}
	else if (strcmp(item, "larma", true) == 0)
	{
	    if (InfoPersonaje[playerid2][pLicencia][3] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no tiene licencia de armas.");
		InfoPersonaje[playerid2][pLicencia][3] = 0;
		guardar_int_mysql("personajes", "Licencia4", InfoPersonaje[playerid2][pID], 0);
		format(string, sizeof string, "le quita la licencia de armas a %s.", GetNameFormat(playerid2));
		rol_auto(playerid, string);
	}
	else if (strcmp(item, "armas", true) == 0)
	{
		new query[360];
		Loop(x, 9, 0) if (InfoInventario[InfoPersonaje[playerid2][pBolsillo][x]][IDArma] != 0)
		{
			InfoPersonaje[playerid2][pBolsillo][x] = 0;
			InfoPersonaje[playerid2][pBolsilloCant][x] = 0;
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = 0, Cantidad_bolsillo_%d = 0 WHERE ID = '%d'", x+1, x+1, InfoPersonaje[playerid2][pID]);
			mysql_tquery(db_samp, query);
		}
		if (InfoInventario[InfoPersonaje[playerid2][pManoIzquierda]][IDArma] != 0)
		{
			InfoPersonaje[playerid2][pManoIzquierda] = 0;
			InfoPersonaje[playerid2][pManoIzquierdaCant] = 0;
			RemovePlayerAttachedObject(playerid2, 8);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = 0, Cantidad_mano_izquierda = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
			mysql_tquery(db_samp, query);
		}
		if (InfoInventario[InfoPersonaje[playerid2][pManoDerecha]][IDArma] != 0)
		{
			InfoPersonaje[playerid2][pManoDerecha] = 0;
			InfoPersonaje[playerid2][pManoDerechaCant] = 0;
			RemovePlayerAttachedObject(playerid, 7);
			ResetPlayerWeapons(playerid2);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = 0, Cantidad_mano_derecha = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
			mysql_tquery(db_samp, query);
		}
		if (InfoInventario[InfoPersonaje[playerid2][pEspalda]][IDArma] != 0)
		{
			InfoPersonaje[playerid2][pEspalda] = 0;
			InfoPersonaje[playerid2][pEspaldaCant] = 0;
			RemovePlayerAttachedObject(playerid2, 9);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = 0, Cantidad_espalda = 0 WHERE ID = '%d'", InfoPersonaje[playerid2][pID]);
			mysql_tquery(db_samp, query);
		}
		format(string, sizeof string, "le quita las armas a %s.", GetNameFormat(playerid2));
		rol_auto(playerid, string);
	}
	else SendPlayerChatMessage(playerid, COLOR_GRAD2, "Item incorrecto.");
	return 1;
}

cmd:changepass(playerid)
{
	Dialog_Show(playerid, ConfirmarPass, DIALOG_STYLE_PASSWORD, "Cambio de contraseña", "{cccccc}Introduce tu contraseña actual:", "Continuar", "Salir");
	return 1;
}
alias:changepass("cambiarclave");

Dialog:ConfirmarPass(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new Salted_Key[65];
	SHA256_PassHash(inputtext, InfoCuenta[playerid][jSalt], Salted_Key, 65);
	if (strcmp(Salted_Key, InfoCuenta[playerid][jClave]) == 0)
	{
		Dialog_Show(playerid, NewPass, DIALOG_STYLE_PASSWORD, "Nueva contraseña", "{cccccc}Introduce la nueva contraseña:", "Cambiar", "Salir");
	}
	else
	{
		SendPlayerChatMessage(playerid, 0xccccccff, "Contraseña incorrecta, intenta de nuevo.");
		Dialog_Show(playerid, ConfirmarPass, DIALOG_STYLE_PASSWORD, "Cambio de contraseña", "{cccccc}Introduce tu contraseña actual:", "Continuar", "Salir");
	}
	return 1;
}

Dialog:NewPass(playerid, response, listitem, inputtext[])
{
	new string[256];
	if (!response) return 1;
	if (strlen(inputtext) < 5)
	{
		SendPlayerChatMessage(playerid, 0xccccccff, "No puedes tener una contraseña con menos de 4 carácteres.");
		Dialog_Show(playerid, NewPass, DIALOG_STYLE_PASSWORD, "Nueva contraseña", "{cccccc}Introduce la nueva contraseña:", "Cambiar", "Salir");
		return 1;
	}
	if (strlen(inputtext) > 23)
	{
		SendPlayerChatMessage(playerid, 0xccccccff, "No puedes tener una contraseña con más de 24 carácteres.");
		Dialog_Show(playerid, NewPass, DIALOG_STYLE_PASSWORD, "Nueva contraseña", "{cccccc}Introduce la nueva contraseña:", "Cambiar", "Salir");
		return 1;
	}
	//hash password + save
	Loop(e, 10, 0) { InfoCuenta[playerid][jSalt][e] = random(79) + 47; }
	InfoCuenta[playerid][jSalt][10] = 0;
	SHA256_PassHash(inputtext, InfoCuenta[playerid][jSalt], InfoCuenta[playerid][jClave], 65);
	mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET Clave = '%e', Salt = '%e' WHERE ID = '%d'", InfoCuenta[playerid][jClave], InfoCuenta[playerid][jSalt], InfoCuenta[playerid][jID]);
	mysql_tquery(db_samp, string);
	//log + message
	format(string, sizeof string, "%s ha cambiado su contraseña.", InfoCuenta[playerid][jNombre]);
	Log("f_logs/password.log", string);
	format(string, sizeof string, "Has cambiado tu contraseña a: '%s'", inputtext);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	return 1;
}

cmd:gob(playerid, params[])
{
	if (!Propietario_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes acceso a este comando.");
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Utiliza: /gob (texto)");
	new string[321];
	format(string, sizeof string, "{2641FE}[%s] %s: {FFFFFF}%s", InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo], GetNameFormat(playerid), params[0]);
	SendAllICMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:jail(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No tienes suficentes permisos para usar este comando.");
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], time, playerid2, reason[64], query3[1028], type;
	if (CommandSpamTimes[playerid] == 20)
	{
		format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) fue baneado automáticamente, razón: Flood Cmd´s", InfoCuenta[playerid][jNombre], playerid);
		SendAdminMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s fue baneado automáticamente, razón: Flood Cmd´s", InfoCuenta[playerid][jNombre]);
		Log("f_logs/hackeraction.log", string);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE cuentas SET JotoOtaku = 0, EncFac = 0, EncMap = 0, OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", "Server", "Abuso cmds", FechaHoy(), InfoCuenta[playerid][jID]);
		mysql_tquery(db_samp, query3);
		Kick(playerid);
		return 1;
	}
	//cmd
	if (sscanf(params, "ddds[64]", playerid2, type, time, reason)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Utiliza: /jail (playerid) (type [0 ic] [1 ooc]) (minutos) (razón)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID inválida.");
	if (type == 1) // ooc
	{
		if (strlen(reason) >= sizeof(reason)-1) return SendPlayerChatMessage(playerid, COLOR_GREY, "El motivo del jail no puede ocupar más de 64 carácteres.");
		if (InfoPersonaje[playerid2][pJails] >= 10)
		{
			format(string, sizeof string, "%s fue bloqueado, razón: +10 Jails", GetNameFormat(playerid2));
			Log("f_logs/ban.log", string);
			format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) fue bloqueado. Razón: +10 Jails", GetNameFormat(playerid2), playerid2);
			SendAdminMessage(0xFFFFFFFF, string);
			mysql_format(db_samp, query3, sizeof query3, "UPDATE personajes SET OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", "Server", "+15 jails", FechaHoy(), InfoPersonaje[playerid2][pID]);
			mysql_tquery(db_samp, query3);
			SetTimerEx("TimerKICK", 1500, false, "d", playerid2);
		    return 1;
		}
		alm(InfoPersonaje[playerid2][pBySancion], InfoCuenta[playerid][jNombre]);
		alm(InfoPersonaje[playerid2][pRazonSancion], reason);
		CommandSpamTimes[playerid]++;
		CommandSpamUnmute[playerid] = 60;
		InfoPersonaje[playerid2][pJails] += 1;
		InfoPersonaje[playerid2][pSancionado] = 1;
		InfoPersonaje[playerid2][pTogTelefono] = 0;
		InfoPersonaje[playerid2][pTiempoSancion] = time*60;
		SetPlayerPosEx(playerid2, 436.4944, 2547.5933, 16.3020 );
		SetPlayerInterior(playerid2, 0);
		SetPlayerVirtualWorld(playerid2, playerid2+1);
		TogglePlayerControllable(playerid2, false);
		new query[410];
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Sancionado = 1, TiempoSancion = '%d', BySancion = '%e', RazonSancion = '%e', Jails = '%d' WHERE ID = '%d'", InfoPersonaje[playerid2][pTiempoSancion], InfoPersonaje[playerid2][pBySancion], InfoPersonaje[playerid2][pRazonSancion], InfoPersonaje[playerid2][pJails], InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) sancionó a %s(%d). Razón: %s", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2, InfoPersonaje[playerid2][pRazonSancion]);
		SendAllMessage(0xFFFFFFFF, string);
		format(string, sizeof string, "%s encarceló a %s, razón: %s, tiempo: %d minuto(s)", InfoCuenta[playerid][jNombre], NombreDeCuenta(playerid2), InfoPersonaje[playerid2][pRazonSancion], time);
		Log("f_logs/SancionesOOC.log", string);
		StopAudioStreamForPlayer(playerid2);
		TipoAudio[playerid2] = 0;
		return 1;
	}
	QuitarBolsillos(playerid2);
	QuitarManos(playerid2);
	QuitarEspalda(playerid2);
	alm(InfoPersonaje[playerid2][pBySancion], InfoCuenta[playerid][jNombre]);
	alm(InfoPersonaje[playerid2][pRazonSancion], reason);
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
	format(string, sizeof string, "[CENTRAL] %s fue arrestado por %s, %d minutos. (STAFF)", GetNameFormat(playerid2), GetNameFormat(playerid), time);
	SendRadioMessage(1, COLOR_RADIO, string, 1);
	SendRadioMessage(2, COLOR_RADIO, string, 1);
	SendRadioMessage(4, COLOR_RADIO, string, 1);
	SendRadioMessage(7, COLOR_RADIO, string, 1);
	InfoPersonaje[playerid2][pTiempoSancion] = time*60;
	DeletePVar(playerid2, "IsFrozen");
	new rand = random(sizeof PrisonSpawns);
	SetPosEx(playerid2, PrisonSpawns[rand][0], PrisonSpawns[rand][1], PrisonSpawns[rand][2], 0.0000, 60, 60, 1);
	InfoPersonaje[playerid2][pSancionado] = 2;
	InfoPersonaje[playerid2][pTogTelefono] = 0;
	InfoPersonaje[playerid2][pArrestos] += 1;
	InfoPersonaje[playerid2][pEstrellas] = 0;
	SetPlayerWantedLevel(playerid2, 0);
	ClearAnimations(playerid2);
	RemovePlayerAttachedObject(playerid2, 0);
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
	DeletePVar(playerid2, "PlayerCuffed");
	new query[410];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Estrellas = 0, Sancionado = 2, TiempoSancion = '%d', Arrestos = '%d' WHERE ID = '%d'",InfoPersonaje[playerid2][pTiempoSancion], InfoPersonaje[playerid2][pArrestos], InfoPersonaje[playerid2][pID]);
	mysql_tquery(db_samp, query);
	SendClientMessageEx(playerid2, COLOR_LIGHTBLUE, "Fuiste encarcelado %d minutos por un STAFF. (Puedes verificar el tiempo restante en /cuenta)", time);
	format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) encarceló en prisión a %s(%d). Razón: %s", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2, InfoPersonaje[playerid2][pRazonSancion]);
	SendAllMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s encarceló a %s, razón: %s, tiempo: %d minuto(s)", InfoCuenta[playerid][jNombre], NombreDeCuenta(playerid2), InfoPersonaje[playerid2][pRazonSancion], time);
	Log("f_logs/SancionesIC.log", string);
	return 1;
}
alias:jail("sancionar", "san");

cmd:jailoffline(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No tienes suficentes permisos para usar este comando.");
	if (CheckAdminDuty(playerid)) return 1;
	new gformat[512], pide, name[MAX_PLAYER_NAME], minutes, reason[64];
	if (sscanf(params, "uds[64]", pide, minutes, reason)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /jailoffline (Nombre_Apellido) (Minutos) (Razón)");
	if (IsPlayerConnected(pide)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Ese jugador está conectado, usa /jail.");
	if (sscanf(params, "s[24]ds[64]", name, minutes, reason)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /jailoffline (Nombre_Apellido) (Minutos) (Razón)");
	if (VerificarPersonaje(name))
	{
		new total_jails;
		rebel_int(0, "Jails", total_jails);
		mysql_format(db_samp, gformat, sizeof gformat, "UPDATE personajes SET Jails = '%d', Sancionado = 1, TiempoSancion = '%d', PosicionX = '%f', PosicionY = '%f', PosicionZ = '%f', Interior = 0, VirtualWorld = '%d', BySancion = '%e', RazonSancion = '%e' WHERE Nombre_Apellido = '%e'", total_jails, minutes*60, 436.4944, 2547.5933, 16.3020, playerid+1, NombreDeCuenta(playerid), reason, name);
		mysql_tquery(db_samp, gformat);
		format(gformat, sizeof gformat, "%s fue jaileado por %s, razon: %s. [CMD OFFLINE]", name, InfoCuenta[playerid][jNombre], reason);
		Log("f_logs/admin.log", gformat);
		format(gformat, sizeof gformat, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) sancionó %d minutos a %s, razon: %s. (OFFLINE)", InfoCuenta[playerid][jNombre], playerid, minutes, name, reason);
		SendAdminMessage(0xFFFFFFFF, gformat);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa cuenta no existe.");
	return 1;
}
alias:jailoffline("jailcuenta", "sancionaroff", "sanoffline");

cmd:checkmoney(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No tienes suficentes permisos para usar este comando.");
	new monto;
	if (sscanf(params, "d", monto)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /checkmoney (Cantidad)");
	SendClientMessageEx(playerid, 0xCCCC00FF, "Jugadores con más de %s en bolsillos+banco", diner_coma(monto));
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		new cash = GetPlayerCash(playerid2)+InfoPersonaje[playerid2][pBanco];
		if (cash > monto)
		{
			SendClientMessageEx(playerid, 0xEBEBEBFF, "ID: %d (nick: %s) (pj: %s) (horas: %d) (bolsillos: $%s) (banco: $%s) (total: $%s)",
			playerid2, InfoCuenta[playerid2][jNombre], InfoPersonaje[playerid2][pNombre_Apellido], InfoPersonaje[playerid2][pHorasOn], diner_coma(GetPlayerCash(playerid2)), diner_coma(InfoPersonaje[playerid2][pBanco]), diner_coma(cash));
		}
	}
	return 1;
}
alias:checkmoney("money");

cmd:bloquearprivados(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new gformat[170], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /bloquearmp (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador seleccionado está desconectado.");
	if (InfoCuenta[playerid2][jBloqueoMP] == 0)
	{
		format(gformat, sizeof gformat, "{FF6347}Administración:{FFFFFF} %s(%d) bloqueó los permisos de /mp a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoPersonaje[playerid2][pNombre_Apellido], playerid2);
		SendClientMessageEx(playerid2, COLOR_GREY, "* %s te ha bloqueado los permisos de /mp.", InfoCuenta[playerid][jNombre]);
		InfoCuenta[playerid2][jBloqueoMP] = 1;
	}
	else
	{
		format(gformat, sizeof gformat, "{FF6347}Administración:{FFFFFF} %s(%d) desbloqueó los permisos de /mp a %s(%d).", InfoCuenta[playerid][jNombre], playerid, InfoPersonaje[playerid2][pNombre_Apellido], playerid2);
		SendClientMessageEx(playerid2, COLOR_GREY, "* %s te ha desbloqueado los permisos de /mp.", InfoCuenta[playerid][jNombre]);
		InfoCuenta[playerid2][jBloqueoMP] = 0;
	}
	SendAdminMessage(0xFFFFFFFF, gformat);
	guardar_int_mysql("cuentas", "BloqueoMP", InfoCuenta[playerid2][jID], InfoCuenta[playerid2][jBloqueoMP]);
	return 1;
}
alias:bloquearprivados("bloquearmp");

cmd:sp(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	SetPosEx(playerid, 1452.3049, -1066.5161, 213.4904, 0, 0, 0, 1); //1529.6,-1691.2,13.3
	return 1;
}

cmd:ls(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (GetPlayerState(playerid) == 2) MoverVehiclePos(GetPlayerVehicleID(playerid), 1529.6, -1705.5, 13.4); //1529.6,-1691.2,13.3
	else SetPosEx(playerid, 1529.6, -1705.5, 13.4, 0, 0, 0, 1); //1529.6,-1691.2,13.3
	return 1;
}

cmd:sf(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (GetPlayerState(playerid) == 2) MoverVehiclePos(GetPlayerVehicleID(playerid), -2016.4399,-79.7714,35.3203);
	else SetPosEx(playerid, -2016.4399,-79.7714,35.3203, 0, 0, 0, 1);
	return 1;
}

cmd:lv(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (GetPlayerState(playerid) == 2) MoverVehiclePos(GetPlayerVehicleID(playerid), 1694.6566,1453.4523,10.7632);
	else SetPosEx(playerid, 1694.6566,1453.4523,10.7632, 0, 0, 0, 1);
	return 1;
}

cmd:entrarauto(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new vehicleid;
	if (sscanf(params, "i", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /entrarauto (VehicleID)");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo no encontrado, intenta con otra ID.");

	PutPlayerInVehicleEx(playerid, vehicleid, 1);
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Teleportado.");
	return 1;
}
alias:entrarauto("entercar");

cmd:llenargas(playerid)
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new gformat[170];
	format(gformat, sizeof gformat, "{FF6347}Administración:{FFFFFF} %s(%d) llenó la gasolina de todos los vehículos.", InfoCuenta[playerid][jNombre], playerid);
	SendAllMessage(0xFFFFFFFF, gformat);
	Loop(veh, MAX_VEHICLES, 0) if (GetVehicleModel(veh))
	{
		veh_gasolina[veh] = 100;
	}
	return 1;
}

cmd:anunciostaff(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new text[64], type;
	if (sscanf(params, "is[64]", type, text)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /anunciostaff (Tipo) (Texto)");
	if (type == 2) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes elegir el numero 2.");
	for(new i = 0; i < MAX_PLAYERS; i++){ if (IsPlayerConnectedEx(i)){ GameTextForPlayer(i, text, 5000, type); } }
	new string[170];
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) usó el comando /anunciostaff.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

TallerOpened(id, status)
{
	if (id == 1)
	{
		if (status == 1) MoveDynamicObject(PortonTaller[0], 1973.32129, -2061.40601, 15.23994, 5.0);
		else MoveDynamicObject(PortonTaller[0], 1973.32129, -2061.40601, 9.40735, 5.0);
	}
	if (id == 2)
	{
		if (status == 1) MoveDynamicObject(PortonTaller[1], 1465.04749, -1495.59863, 15.42555, 5.0);
		else MoveDynamicObject(PortonTaller[1], 1465.04749, -1495.59863, 9.58047, 5.0);
	}
	if (id == 3)
	{
		if (status == 1) MoveDynamicObject(PortonTaller[2], 2360.93237, -1369.77771, 25.93274, 5.0);
		else MoveDynamicObject(PortonTaller[2], 2360.93237, -1369.77771, 20.05445, 5.0);
	}
	if (id == 4)
	{
		if (status == 1) MoveDynamicObject(PortonTaller[3], 1836.73279, -1401.49719, 15.29182, 5.0);
		else MoveDynamicObject(PortonTaller[3], 1836.73279, -1401.49719, 9.49952, 5.0);
	}
	if (id == 5)
	{
		if (status == 1) MoveDynamicObject(PortonTaller[4], 1005.10144, -1445.46802, 15.41000, 5.0);
		else MoveDynamicObject(PortonTaller[4], 1005.10144, -1445.46802, 9.64894, 5.0);
	}
}

cmd:ap(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return 1; //SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres miembro de LSPD, FBI, LSCSD o SADOC.");
	if (IsPlayerInRangeOfPoint(playerid, 2.0, 1756.493408, -1501.452514, -40.847515))
	{
		MoveDynamicObject(puerta_sadoc[0], 1755.1134, -1501.4525, -40.8475, 5.0);
		SetTimerEx("Closed_SADOC", 5000, false, "d", 0);
	}
	if (IsPlayerInRangeOfPoint(playerid, 2.0, 1745.393554, -1501.452514, -40.847515))
	{
		MoveDynamicObject(puerta_sadoc[1], 1743.9736, -1501.4525, -40.8475, 5.0);
		SetTimerEx("Closed_SADOC", 5000, false, "d", 1);
	}
	if (IsPlayerInRangeOfPoint(playerid, 2.0, 1699.225830, -1484.844482, -39.620868))
	{
		MoveDynamicObject(puerta_sadoc[2], 1697.5458, -1484.8445, -39.6209, 5.0);
		SetTimerEx("Closed_SADOC", 5000, false, "d", 2);
	}
	//celda sd
	if (IsPlayerInRangeOfPoint(playerid, 7.0, 1614.7880, 1609.2120, 11.5660))
	{
		if (celda_open_sd == 0)
		{
			MoveDynamicObject(celda_sd, 1614.7880, 1611.2920, 11.5660, 8.0);
			celda_open_sd = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_sd, 1614.7880, 1609.2120, 11.5660, 8.0);
			celda_open_sd = 0; //cerrada
		}
	}

	//celdas lspd
	if (IsPlayerInRangeOfPoint(playerid, 3.0, 1605.359,-1657.171,2108.643))
	{
		if (celda_open_pd[0] == 0)
		{
			MoveDynamicObject(celda_pd[0], 1603.6990, -1657.1710, 2108.6431, 8.0);
			celda_open_pd[0] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pd[0], 1605.359,-1657.171,2108.643, 8.0);
			celda_open_pd[0] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 3.0, 1599.194,-1657.166,2108.643))
	{
		if (celda_open_pd[1] == 0)
		{
			MoveDynamicObject(celda_pd[1], 1600.7940, -1657.1660, 2108.6431, 8.0);
			celda_open_pd[1] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pd[1], 1599.194,-1657.166,2108.643, 8.0);
			celda_open_pd[1] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 7.0, 1614.7880, 1609.2120, 11.5660)) //celda db
	{
		if (celda_open_pd[2] == 0)
		{
			MoveDynamicObject(celda_pd[2], 1614.7880, 1611.2920, 11.5660, 8.0);
			celda_open_pd[2] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pd[2], 1614.7880, 1609.2120, 11.5660, 8.0);
			celda_open_pd[2] = 0; //cerrada
		}
	}
	//celdas prisión federal
	if (IsPlayerInRangeOfPoint(playerid, 2.0, 1769.65454, -1568.21716, -13.35490))
	{
		if (celda_open_pf[0] == 0)
		{
			MoveDynamicObject(celda_pf[0], 1768.1545, -1568.2172, -13.3549, 5.0);
			celda_open_pf[0] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[0], 1769.65454, -1568.21716, -13.35490, 5.0);
			celda_open_pf[0] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1773.02490, -1568.21716, -13.35490))
	{
		if (celda_open_pf[1] == 0)
		{
			MoveDynamicObject(celda_pf[1], 1771.5249, -1568.2172, -13.3549, 5.0);
			celda_open_pf[1] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[1], 1773.02490, -1568.21716, -13.35490, 5.0);
			celda_open_pf[1] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1776.38538, -1568.21716, -13.35490))
	{
		if (celda_open_pf[2] == 0)
		{
			MoveDynamicObject(celda_pf[2], 1774.8854, -1568.2172, -13.3549, 5.0);
			celda_open_pf[2] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[2], 1776.38538, -1568.21716, -13.35490, 5.0);
			celda_open_pf[2] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1779.75537, -1568.21716, -13.35490))
	{
		if (celda_open_pf[3] == 0)
		{
			MoveDynamicObject(celda_pf[3], 1778.2554, -1568.2172, -13.3549, 5.0);
			celda_open_pf[3] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[3], 1779.75537, -1568.21716, -13.35490, 5.0);
			celda_open_pf[3] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1783.11670, -1568.21716, -13.35490))
	{
		if (celda_open_pf[4] == 0)
		{
			MoveDynamicObject(celda_pf[4], 1781.6167, -1568.2172, -13.3549, 5.0);
			celda_open_pf[4] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[4], 1783.11670, -1568.21716, -13.35490, 5.0);
			celda_open_pf[4] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1772.98267, -1564.68665, -16.84490))
	{
		if (celda_open_pf[5] == 0)
		{
			MoveDynamicObject(celda_pf[5], 1771.4827, -1564.6866, -16.8449, 5.0);
			celda_open_pf[5] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[5], 1772.98267, -1564.68665, -16.84490, 5.0);
			celda_open_pf[5] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1776.38367, -1564.68665, -16.84490))
	{
		if (celda_open_pf[6] == 0)
		{
			MoveDynamicObject(celda_pf[6], 1774.8837, -1564.6866, -16.8449, 5.0);
			celda_open_pf[6] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[6], 1776.38367, -1564.68665, -16.84490, 5.0);
			celda_open_pf[6] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1779.76453, -1564.68665, -16.84490))
	{
		if (celda_open_pf[7] == 0)
		{
			MoveDynamicObject(celda_pf[7], 1778.2645, -1564.6866, -16.8449, 5.0);
			celda_open_pf[7] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[7], 1779.76453, -1564.68665, -16.84490, 5.0);
			celda_open_pf[7] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1769.46436, -1550.66504, -13.35490))
	{
		if (celda_open_pf[8] == 0)
		{
			MoveDynamicObject(celda_pf[8], 1767.9844, -1550.6650, -13.3549, 5.0);
			celda_open_pf[8] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[8], 1769.46436, -1550.66504, -13.35490, 5.0);
			celda_open_pf[8] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1772.82153, -1550.66504, -13.35490))
	{
		if (celda_open_pf[9] == 0)
		{
			MoveDynamicObject(celda_pf[9], 1771.3415, -1550.6650, -13.3549, 5.0);
			celda_open_pf[9] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[9], 1772.82153, -1550.66504, -13.35490, 5.0);
			celda_open_pf[9] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1776.18555, -1550.66504, -13.35490))
	{
		if (celda_open_pf[10] == 0)
		{
			MoveDynamicObject(celda_pf[10], 1774.6855, -1550.6650, -13.3549, 5.0);
			celda_open_pf[10] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[10], 1776.18555, -1550.66504, -13.35490, 5.0);
			celda_open_pf[10] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1779.54785, -1550.66504, -13.35490))
	{
		if (celda_open_pf[11] == 0)
		{
			MoveDynamicObject(celda_pf[11], 1778.0879, -1550.6650, -13.3549, 5.0);
			celda_open_pf[11] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[11], 1779.54785, -1550.66504, -13.35490, 5.0);
			celda_open_pf[11] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1782.91858, -1550.66504, -13.35490))
	{
		if (celda_open_pf[12] == 0)
		{
			MoveDynamicObject(celda_pf[12], 1781.4376, -1550.6450, -13.3549, 5.0);
			celda_open_pf[12] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[12], 1782.91858, -1550.66504, -13.35490, 5.0);
			celda_open_pf[12] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1770.96204, -1554.17542, -16.84490))
	{
		if (celda_open_pf[13] == 0)
		{
			MoveDynamicObject(celda_pf[13], 1772.4420, -1554.1754, -16.8449, 5.0);
			celda_open_pf[13] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[13], 1770.96204, -1554.17542, -16.84490, 5.0);
			celda_open_pf[13] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1774.34351, -1554.17542, -16.84490))
	{
		if (celda_open_pf[14] == 0)
		{
			MoveDynamicObject(celda_pf[14], 1775.8035, -1554.1754, -16.8449, 5.0);
			celda_open_pf[14] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[14], 1774.34351, -1554.17542, -16.84490, 5.0);
			celda_open_pf[14] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1777.69348, -1554.17542, -16.84490))
	{
		if (celda_open_pf[15] == 0)
		{
			MoveDynamicObject(celda_pf[15], 1779.1735, -1554.1754, -16.8449, 5.0);
			celda_open_pf[15] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[15], 1777.69348, -1554.17542, -16.84490, 5.0);
			celda_open_pf[15] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1781.06506, -1554.17542, -16.84490))
	{
		if (celda_open_pf[16] == 0)
		{
			MoveDynamicObject(celda_pf[16], 1782.5451, -1554.1754, -16.8449, 5.0);
			celda_open_pf[16] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[16], 1781.06506, -1554.17542, -16.84490, 5.0);
			celda_open_pf[16] = 0; //cerrada
		}
	}
	else if (IsPlayerInRangeOfPoint(playerid, 2.0, 1784.44409, -1554.17542, -16.84490))
	{
		if (celda_open_pf[17] == 0)
		{
			MoveDynamicObject(celda_pf[17], 1785.9241, -1554.1754, -16.8449, 5.0);
			celda_open_pf[17] = 1; //abierta
		}
		else
		{
			MoveDynamicObject(celda_pf[17], 1784.44409, -1554.17542, -16.84490, 5.0);
			celda_open_pf[17] = 0; //cerrada
		}
	}
	return 1;
}
alias:ap("celda");

forward Closed_SADOC(type);
public Closed_SADOC(type)
{
	switch (type)
	{
		case 0: MoveDynamicObject(puerta_sadoc[0], 1756.493408, -1501.452514, -40.847515, 5.0);
		case 1: MoveDynamicObject(puerta_sadoc[1], 1745.3736, -1501.4525, -40.8475, 5.0);
		case 2: MoveDynamicObject(puerta_sadoc[2], 1699.225830, -1484.844482, -39.620868, 5.0);
	}
	return 1;
}

forward Closed_USMC();
public Closed_USMC()
{
	MoveDynamicObject(porton_usmc, 134.5650, 1941.5498, 21.6258, 5.0);
	return 1;
}

forward ClosedDeposito();
public ClosedDeposito()
{
	open_embargo = 0;
	MoveDynamicObject(depositoembargo, 1620.6500244,-1861.5996094,15.3000002,2.5);
	return 1;
}

new slot_agenda[MAX_PLAYERS];

cmd:agenda(playerid)
{
	if (InfoPersonaje[playerid][pTelefono] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes un número telefónico.");
	if (no_tiene_manos(playerid, 50) == 0) return 1;
	new dialog[2048], gformat[512];
	Loop(x, 20, 0)
	{
		if (InfoPersonaje[playerid][pNumeroContacto][x] != 0) format(gformat, sizeof gformat, "{cccccc}%d\t{008000}%s{cccccc} (%d)\n", x+1, nombre_contacto[playerid][x], InfoPersonaje[playerid][pNumeroContacto][x]);
		else format(gformat, sizeof gformat, "{cccccc}%d\t{ffffff}vacío\n", x+1);
		strcat(dialog, gformat);
	}
	Dialog_Show(playerid, ShowAgenda, DIALOG_STYLE_LIST, "Agenda", dialog, "Continuar", "Volver");
	return 1;
}

Dialog:ShowAgenda(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_telefono(playerid);
	new x = listitem;
	slot_agenda[playerid] = x;
	if (InfoPersonaje[playerid][pNumeroContacto][x] == 0)
	{
		Dialog_Show(playerid, AgregarContacto, DIALOG_STYLE_INPUT, "Número telefónico", "{cccccc}Escribe el número de teléfono del contacto a agregar:", "Continuar", "Volver");
		return 1;
	}
	Dialog_Show(playerid, OpcionContacto, DIALOG_STYLE_LIST, "Opciones", "Llamar contacto\nEnviar mensaje\nEliminar contacto\nEnviar ubicación actual", "Continuar", "Volver");
	return 1;
}

Dialog:OpcionContacto(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_agenda(playerid);
	new id = slot_agenda[playerid];
	new query[256];
	if (InfoPersonaje[playerid][pNumeroContacto][id] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún contacto en ese slot.");
	switch (listitem)
	{
		case 0: //llamar
		{
			new gformatenvie[128];
			format(gformatenvie, sizeof gformatenvie, "%d", InfoPersonaje[playerid][pNumeroContacto][id]);
			pc_cmd_llamar(playerid, gformatenvie);
		}
		case 1: //enviar mensaje
		{
			Dialog_Show(playerid, ShowSMS, DIALOG_STYLE_INPUT, "Enviar mensaje", "{ffffff}Introduce el texto que vas a enviar:", "Enviar", "Volver");
		}
		case 2: //eliminar contacto
		{
			alm(nombre_contacto[playerid][id], "none");
			InfoPersonaje[playerid][pNumeroContacto][id] = 0;
			slot_agenda[playerid] = -1;
			pc_cmd_agenda(playerid);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET NombreContacto%d = '%e', NumeroContacto%d = 0 WHERE ID = '%d'", id+1, nombre_contacto[playerid][id], id+1, InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			SendPlayerChatMessage(playerid, 0xaaaa00ff, "Contacto eliminado de tu agenda telefónica.");
		}
		case 3: //enviar ubicación
		{
			if (GetPlayerInterior(playerid) != 0 && GetPlayerVirtualWorld(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes compartir tu ubicación dentro de un interior.");
			if (!CheckTimer(300, wsp_time[playerid]))
			{
				foreach(new playerid2: Player) if (IsPlayerConnectedEx(playerid2) && InfoPersonaje[playerid2][pTelefono] == InfoPersonaje[playerid][pNumeroContacto][id])
				{
					if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No sabemos si tienes problemas mentales, pero no puedes enviarte a ti mismo la ubicación.");
					if (wsp_u[playerid2] != -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese número de teléfono está en otra operación.");
					wsp_u[playerid2] = playerid;
					slot_agenda[playerid] = -1;
					format(query, sizeof query, "El número %d, quiere enviarte su ubicación actual:\n", InfoPersonaje[playerid][pTelefono]);
					Dialog_Show(playerid2, Compaltilwsp, DIALOG_STYLE_MSGBOX, "Notificación WhatsApp", query, "Aceptar", "Cancelar");
					SendClientMessageEx(playerid, COLOR_YELLOW, "Enviaste tu ubicación al contacto %s (%d).", nombre_contacto[playerid][id], InfoPersonaje[playerid][pNumeroContacto][id]);
					return 1;
				}
				slot_agenda[playerid] = -1;
				SendPlayerChatMessage(playerid, COLOR_GREY, "* El contacto seleccionado no se encuentra disponible o no existe.");
			}
			else
			{
				SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar esta función en %d segundos.", CheckTimer(180, wsp_time[playerid]));
			}
		}
	}
	return 1;
}

Dialog:Compaltilwsp(playerid, response, listitem, inputtext[])
{
	new contacto = wsp_u[playerid];
	if (!IsPlayerConnectedEx(contacto))
	{
		wsp_u[playerid] = -1;
		SendPlayerChatMessage(playerid, COLOR_GREY, "* El contacto que te envió su ubicación desconectó.");
		return 1;
	}
	if (!response)
	{
		wsp_u[playerid] = -1;
		SendPlayerChatMessage(contacto, COLOR_GREY, "* El contacto canceló la ubicación.");
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Cancelaste la ubicación.");
		return 1;
	}
	if (GetPlayerInterior(contacto) != 0 && GetPlayerVirtualWorld(contacto) != 0)
	{
		wsp_u[playerid] = -1;
		SendPlayerChatMessage(contacto, COLOR_GREY, "* Entraste a un interior, la ubicación se canceló.");
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Se canceló la ubicación, el contacto entró a un interior.");
		return 1;
	}
	new Float:xp, Float:yp, Float:zp;
	GetPlayerPos(contacto, xp, yp, zp);
	SetPlayerCheckpoint(playerid, xp, yp, zp, 4.0);
	PlayerPlaySound(playerid, 1138, 0, 0, 0);
	SetPVarInt(playerid, "TrackCar", 1);
	SendPlayerChatMessage(playerid, COLOR_GREEN, "El punto fue marcado en el radar.");
	SendPlayerChatMessage(contacto, COLOR_GREEN, "Se envió la información de tu última ubicación a tu contacto.");
	wsp_time[contacto] = gettime();
	wsp_u[playerid] = -1;
	return 1;
}

Dialog:ShowSMS(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_agenda(playerid);
	new id = slot_agenda[playerid], gformatenvie[320];
	format(gformatenvie, sizeof gformatenvie, "%d %s", InfoPersonaje[playerid][pNumeroContacto][id], inputtext);
	pc_cmd_sms(playerid, gformatenvie);
	return 1;
}

Dialog:AgregarContacto(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_agenda(playerid);
	new amount = strval(inputtext);
	new id = slot_agenda[playerid];
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Sólo números porfavor, vuelve a intentarlo.");
	if (amount > 99999999 || amount < 1000) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "El número no puede ser mayor a 999999 o menor a 1000.");

	InfoPersonaje[playerid][pNumeroContacto][id] = amount;
	Dialog_Show(playerid, Agregar2Contacto, DIALOG_STYLE_INPUT, "Nombre del contacto", "{cccccc}Escribe el nombre del contacto", "Continuar", "Volver");
	return 1;
}

Dialog:Agregar2Contacto(playerid, response, listitem, inputtext[])
{
	if (!response) return Dialog_Show(playerid, AgregarContacto, DIALOG_STYLE_INPUT, "Número telefónico", "{cccccc}Escribe el número de teléfono del contacto a agregar:", "Continuar", "Volver");
	if (!strlen(inputtext)) return Dialog_Show(playerid, Agregar2Contacto, DIALOG_STYLE_INPUT, "Nombre del contacto", "{cccccc}Escribe el nombre del contacto", "Continuar", "Volver");
	if (strlen(inputtext) > 20 || strlen(inputtext) < 0)
	{
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "Sólo puedes escribir menos de 20 carácteres.");
		Dialog_Show(playerid, Agregar2Contacto, DIALOG_STYLE_INPUT, "Nombre del contacto", "{cccccc}Escribe el nombre del contacto", "Continuar", "Volver");
		return 1;
	}
	new id = slot_agenda[playerid];
	alm(nombre_contacto[playerid][id], inputtext);
	slot_agenda[playerid] = -1;
	pc_cmd_agenda(playerid);
	new query[500];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET NombreContacto%d = '%e', NumeroContacto%d = '%d' WHERE ID = '%d'", id+1, nombre_contacto[playerid][id], id+1, InfoPersonaje[playerid][pNumeroContacto][id], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	SendPlayerChatMessage(playerid, 0x00cc00ff, "Nuevo contacto agregado a tu agenda telefónica.");
	return 1;
}

cmd:estado(playerid, params[])
{
	if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos dos horas.");
	if (InfoPersonaje[playerid][pMuerto] == 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando en estado muerto.");
	new result[32], string[256];
	if (sscanf(params, "s[32]", result)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /estado (Texto)");
	if (isnull(result) || strlen(result) > 31) return SendPlayerChatMessage(playerid, COLOR_GREY, "* El estado sólo puede contener 32 caracteres.");
	if (!isnull(InfoPersonaje[playerid][pEstadoYo])) //quitar
	{
		format(string, sizeof string, "** {E81700}Retiraste{EBEBEB} tu estado: {00A5AA}%s", InfoPersonaje[playerid][pEstadoYo]);
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
		if (IsValidDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]))
		{
			DestroyDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]);
			InfoPersonaje[playerid][pNameTag] = Text3D:INVALID_3DTEXT_ID;
		}
		alm(InfoPersonaje[playerid][pEstadoYo], "");
	}
	else //poner
	{
		format(string, sizeof string, "** {54C822}Colocaste{EBEBEB} un nuevo estado: {00A5AA}%s", result);
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, "El estado queda permanente (sin importar re-login), si deseas retirarlo usa '/estado' nuevamente.");
		alm(InfoPersonaje[playerid][pEstadoYo], result);
		if (IsValidDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]))
		{
			DestroyDynamic3DTextLabel(InfoPersonaje[playerid][pNameTag]);
			InfoPersonaje[playerid][pNameTag] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoPersonaje[playerid][pNameTag] = CreateDynamic3DTextLabel(result, 0x00A5AAFF, 0, 0, 0.5, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 100.0);
	}
	guardar_string_mysql("personajes", "EstadoYo", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pEstadoYo]);
	return 1;
}
alias:estado("yo");

cmd:ao(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /ao (general chat)");
	new string[256];
	format(string, sizeof string, "{0095C6}[GENERAL] %s{FFFFFF} %s: %s", GetAdminName(playerid), InfoCuenta[playerid][jNombre], params);
	SendAllMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:comprar(playerid)
{
	new id = EnNegocio(playerid);
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el interior de ningún negocio.");
	if (InfoNegocio[id][nVenta] != 0)
	{
		if (InfoNegocio[id][nProductos] < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este negocio no tiene productos.");
	}
	if (!IsPlayerInRangeOfPoint(playerid, 4.0, InfoNegocio[id][nLugarCompraX], InfoNegocio[id][nLugarCompraY], InfoNegocio[id][nLugarCompraZ])) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el lugar de compra.");
	id_negocio[playerid] = id;
	new dialg_products[1028];
	switch (InfoNegocio[id][nTipo])
	{
		case 1: // 24-7
		{
			strcat(dialg_products, "Producto\tValor\tUnidades\n");
			strcat(dialg_products, "{EBEBEB}Teléfono S10 color oro\t{04B404}$420\t{3E62F4}1\n");
			strcat(dialg_products, "{EBEBEB}Paquete de cigarros\t{04B404}$40\t{3E62F4}20\n");
			strcat(dialg_products, "{EBEBEB}Encendedor\t{04B404}$20\t{3E62F4}2\n");
			strcat(dialg_products, "{EBEBEB}Cámara fotográfica\t{04B404}$200\t{3E62F4}50\n");
			strcat(dialg_products, "{EBEBEB}Boombox\t{04B404}$1,500\t{3E62F4}1\n");
			strcat(dialg_products, "{EBEBEB}Caja\t{04B404}$500\t{3E62F4}1\n");
			strcat(dialg_products, "{EBEBEB}Mochila\t{04B404}$800\t{3E62F4}1\n");
			strcat(dialg_products, "{EBEBEB}Spray (sólo pandillas)\t{04B404}$50\t{3E62F4}99999\n");
			strcat(dialg_products, "{EBEBEB}Sixpack de cervezas\t{04B404}$50\t{3E62F4}6\n");
			strcat(dialg_products, "{EBEBEB}Diazepam (VIP)\t{04B404}$200\t{3E62F4}6\n");
			strcat(dialg_products, "{EBEBEB}Metadona (VIP)\t{04B404}$200\t{3E62F4}6");
			Dialog_Show(playerid, Show24siete, DIALOG_STYLE_TABLIST_HEADERS, "24/7", dialg_products, "Comprar", "Salir");
		}
		case 2: // ropa
		{
			if (InfoPersonaje[playerid][pSexo] == 1)
			{
				strcat(dialg_products, "Ropa de civil\n");
				strcat(dialg_products, "Ropa de pandillero\n");
				strcat(dialg_products, "Ropa de mafioso\n");
				strcat(dialg_products, "Ropa sexy\n");
				strcat(dialg_products, "Toys");
			}
			else
			{
				strcat(dialg_products, "Ropa de civil\n");
				strcat(dialg_products, "Ropa de pandillera\n");
				strcat(dialg_products, "Ropa de mafiosa\n");
				strcat(dialg_products, "Ropa sexy\n");
				strcat(dialg_products, "Toys");
			}
			Dialog_Show(playerid, ShowRopa, DIALOG_STYLE_LIST, "Tienda de ropa", dialg_products, "Continuar", "Salir");
		}
		case 3,8: // restaurantes y bar
		{
			strcat(dialg_products, "Producto\tValor\n");
			strcat(dialg_products, "{EBEBEB}Emparedado\t{04B404}$40\n");
			strcat(dialg_products, "{EBEBEB}Coca-Cola\t{04B404}$20\n");
			strcat(dialg_products, "{EBEBEB}Cerveza\t{04B404}$10\n");
			Dialog_Show(playerid, ShowRestaurante, DIALOG_STYLE_TABLIST_HEADERS, "Menú de produtos", dialg_products, "Comprar", "Salir");
		}
		case 4: // gasolinera
		{
			strcat(dialg_products, "Producto\tValor\n");
			strcat(dialg_products, "{EBEBEB}Lata de gasolina\t{04B404}$50\n");
			strcat(dialg_products, "{EBEBEB}Bolsa de patatas\t{04B404}$20\n");
			strcat(dialg_products, "{EBEBEB}Refresco\t{04B404}$10\n");
			strcat(dialg_products, "{EBEBEB}Paquete de cigarros\t{04B404}$40\n");
			strcat(dialg_products, "{EBEBEB}Encendedor\t{04B404}$20");
			Dialog_Show(playerid, ShowGasolinera, DIALOG_STYLE_TABLIST_HEADERS, "Gasolinera", dialg_products, "Comprar", "Salir");
		}
		case 5: // ammunation
		{
			if (InfoPersonaje[playerid][pLicencia][3] == 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Vendedor dice: Es imposible venderte armas, no tienes licencia para portarlas.");
			if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes tener al menos dos horas de juego para comprar armas.");
			strcat(dialg_products, "Producto\tValor\n");
			strcat(dialg_products, "{EBEBEB}Puño americano\t{04B404}$50\n");
			strcat(dialg_products, "{EBEBEB}Bate\t{04B404}$100\n");
			strcat(dialg_products, "{EBEBEB}Pistola 9mm\t{04B404}$1,650\n");
			strcat(dialg_products, "{EBEBEB}Escopeta\t{04B404}$5,700\n");
			strcat(dialg_products, "{EBEBEB}Rifle de caza\t{04B404}$7,450\n");
			strcat(dialg_products, "{EBEBEB}Comprar balas");
			Dialog_Show(playerid, ShowAmmunation, DIALOG_STYLE_TABLIST_HEADERS, "Ammunation", dialg_products, "Comprar", "Salir");
		}
		case 7: // sex shop
		{
			strcat(dialg_products, "Producto\tValor\n");
			strcat(dialg_products, "{EBEBEB}Dildo\t{04B404}$30\n");
			strcat(dialg_products, "{EBEBEB}Consolador\t{04B404}$20");
			Dialog_Show(playerid, ShowSexShop, DIALOG_STYLE_TABLIST_HEADERS, "Tienda erótica", dialg_products, "Comprar", "Salir");
		}
		case 10: // concesionario
		{
			if (DetectarMaxVehiculos(playerid) == 1) return 1;
			new showConcesionario[4056] = "Modelo\tValor\n", gformat[256], iCount = 0;
			Loop(xd, sizeof infovehicle, 0) if (infovehicle[xd][elPrecio] >= 100)
			{
				format(gformat, sizeof gformat, "{EBEBEB}%s\t{04B404}$%s\n", infovehicle[xd][elNombre], diner_coma(infovehicle[xd][elPrecio]));
				strcat(showConcesionario, gformat);
				//conteo
				new gformat2[64];
				format(gformat2, sizeof gformat2, "vehConcesinx%d", iCount);
				SetPVarInt(playerid, gformat2, xd);
				iCount++;
			}
			Dialog_Show(playerid, ComprarVehiculo, DIALOG_STYLE_TABLIST_HEADERS, "Concesionaria", showConcesionario, "Continuar", "Salir");
		}
		case 21: // sex shop
		{
			strcat(dialg_products, "Producto\tValor\n");
			strcat(dialg_products, "{EBEBEB}Caña de pescar\t{04B404}$150\n");
			strcat(dialg_products, "{EBEBEB}Gusanos\t{04B404}$10\n");
			strcat(dialg_products, "{EBEBEB}Vender pescados\t{04B404}+$50");
			Dialog_Show(playerid, ShowBaitShop, DIALOG_STYLE_TABLIST_HEADERS, "Tienda de pesca", dialg_products, "Comprar", "Salir");
		}
		default: SendPlayerChatMessage(playerid, -1, "No tiene sistema de compras este tipo de negocio.");
	}
	return 1;
}
alias:comprar("tomarhp");


Dialog:ComprarVehiculo(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new veh = listitem, gformat[40];
	format(gformat, sizeof gformat, "vehConcesinx%d", veh);
	new id = GetPVarInt(playerid, gformat), color1 = random(250), color2 = random(250);

	Vehicle_Color[playerid] = 1; //color blanco default

	SetPlayerVirtualWorld(playerid, 1);
	
	//modelo nombre
	format(gformat, sizeof gformat, "%s", infovehicle[id][elNombre]);
	PlayerTextDrawSetStringEx(playerid, p_tdConce[playerid][13], gformat);
	
	//angulo1
	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][12], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][12], 1, 1);

	// colores
	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][40], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][40], 0, 0);

	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][41], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][41], 3, 3);

	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][42], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][42], 6, 6);

	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][43], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][43], 10, 10);

	PlayerTextDrawSetPreviewModel(playerid, p_tdConce[playerid][44], infovehicle[id][elModelo]);
	PlayerTextDrawSetPreviewVehCol(playerid, p_tdConce[playerid][44], 151, 151);

	// UpdateConceBars(playerid);
	Loop(i, 48, 0) { PlayerTextDrawShow(playerid, p_tdConce[playerid][i]); }
	
	if(IsValidVehicle(autodemierda[playerid]))
	{ 
		DestroyVehicle(autodemierda[playerid]);
	}
	
	if(InfoNegocio[id_negocio[playerid]][nTipo] == 10) autodemierda[playerid] = CreateVehicle(infovehicle[id][elModelo], 1830.7097,406.2690,2999.3513,179.4810, 1, 1, -1);
	else SendClientMessage(playerid, -1, "Algo fallo... Comunicate con Sleek.");

	SetVehicleVirtualWorld(autodemierda[playerid], 1);
	SetPlayerVirtualWorld(playerid, 1);

	if(InfoNegocio[id_negocio[playerid]][nTipo] == 10) {
		InterpolateCameraPos(playerid,1830.835205,398.156311,2999.473388,1830.835205,398.156311,2999.432373,1000,CAMERA_MOVE);
		InterpolateCameraLookAt(playerid,1831.264648,403.176391,2998.943115,1830.515502,405.536193,2998.853027,1000,CAMERA_MOVE);
	}
	
	SelectTextDraw(playerid, 0xDADADABB);
	CompraVehiculo[playerid] = id;
	return 1;
}

Dialog:Show24siete(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new string[195];
	switch (listitem)
	{
		case 0:
		{
		    new precio = 420;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Teléfono S10 color oro{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 50, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste teléfono S10 color oro.");
			GivePlayerCash(playerid, -precio, "compra de telefono");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 1:
		{
		    new precio = 40;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Paquete de cigarros{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 42, 20) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un paquete de 20 cigarros. (/fumar)");
			GivePlayerCash(playerid, -precio, "compra de 20 cigarros");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 2:
		{
		    new precio = 20;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Encendedor{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 41, 20) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un encendedor.");
			GivePlayerCash(playerid, -precio, "compra de encendedor");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 3:
		{
		    new precio = 200;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Cámara fotográfica{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (PlayerWeapon(playerid, 43) == 0) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una cámara fotográfica.");
			GivePlayerCash(playerid, -precio, "compra de cámara fotográfica");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 4:
		{
		    new precio = 1500;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Boombox{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 51, 1) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un boombox. (/equiposonido)");
			GivePlayerCash(playerid, -precio, "compra de boombox");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 5:
		{
			if (InfoPersonaje[playerid][pHorasOn] < 10) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Necesitas jugar al menos diez horas, para poder comprar esto.");
			new precio = 500;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Caja{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano derecha vacía.");
			crear_caja(playerid);
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una caja para guardar objetos. (/caja)");
			GivePlayerCash(playerid, -precio, "compra de caja");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 6:
		{
			new precio = 800;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Mochila{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (InfoPersonaje[playerid][pManoDerecha] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener la mano derecha vacía.");
			crear_mochila(playerid);
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una mochila para guardar objetos. (/mochila)");
			GivePlayerCash(playerid, -precio, "compra de mochila");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 7:
		{
			new faccion = member_faccion(playerid, 9);
			if (faccion == 0 && InfoPersonaje[playerid][pAccesoGraffiti] != 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes permisos suficientes para usar esta función.");
		    new precio = 50;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Spray{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 36, 99999) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un spray. (/graffiti)");
			GivePlayerCash(playerid, -precio, "compra de graffiti");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 8:
		{
		    new precio = 50;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Sixpack de cervezas{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 67, 6) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste un sixpack de cervezas. (/caja - /beber)");
			GivePlayerCash(playerid, -precio, "compra de sixpack de cervezas");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 9:
		{
		    new precio = 200;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Diazepam{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 70, 6) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste Diazepam (/usar)");
			GivePlayerCash(playerid, -precio, "compra de Diazepam");
			CobroNegocio(id_negocio[playerid], precio);
		}
		case 10:
		{
		    new precio = 200;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Metadona{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 69, 6) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste Metadona (/usar)");
			GivePlayerCash(playerid, -precio, "compra de Metadona");
			CobroNegocio(id_negocio[playerid], precio);
		}
	}
	return 1;
}

Dialog:ShowRopa(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (listitem == 4)
	{
		new max_cToys = 4;
		if (InfoCuenta[playerid][jVIP] == 2) max_cToys = 7;
		Loop(id, max_cToys, 0) if (InfoPersonaje[playerid][ptModelo][id] == 0)
		{
			slotselection[playerid] = id;
			new ToyMuestra[180], count = 0;
			Loop(x, sizeof InfoToy, 0) if (InfoToy[x][accTipo] == 1)
			{
				ToyMuestra[count] = InfoToy[x][accModelo];
				count++;
			}
			ShowModelSelectionMenuEx(playerid, ToyMuestra, count, "Toys", Compra_Toy);
			return 1;
		}
		new gformat[128];
		format(gformat, sizeof gformat, "No puedes tener más de %d toys.", max_cToys);
		SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
		return 1;
	}
	new SkinMuestra[150], name_tip[42], count = 0, id_tip = listitem+1;
	switch (id_tip)
	{
		case 1: alm(name_tip, "Ropa de civil");
		case 2:
		{
			if (InfoPersonaje[playerid][pSexo] == 1) alm(name_tip, "Ropa de pandillero");
			else alm(name_tip, "Ropa de pandillera");
		}
		case 3:
		{
			if (InfoPersonaje[playerid][pSexo] == 1) alm(name_tip, "Ropa de mafioso");
			else alm(name_tip, "Ropa de mafiosa");
		}
		case 4: alm(name_tip, "Ropa sexy");
	}
	Loop(x, sizeof InfoSkin, 0) if (InfoSkin[x][sSexo] == InfoPersonaje[playerid][pSexo] && InfoSkin[x][sTipo] == id_tip)
	{
		SkinMuestra[count] = x;
		count++;
	}
	ShowModelSelectionMenuEx(playerid, SkinMuestra, count, name_tip, Compra_Skin, -11.0, 0.0, -55.0, 1.0);
	return 1;
}

Dialog:ShowRestaurante(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new Float:Health = InfoPersonaje[playerid][pVida], string[190];
	switch (listitem)
	{
		case 0:
		{
		    new precio = 40;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Plato huevos{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (Health < 101) dar_vida(playerid, Health+20);
			rol_ame(playerid, "come un plato de huevos con chorizo.");
			GivePlayerCash(playerid, -precio, "compra de plato huevos");
			CobroNegocio(id_negocio[playerid], precio);
			ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 1, 1, 0, 0, 1);
		}
		case 1:
		{
		    new precio = 20;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Coca cola{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (Health < 101) dar_vida(playerid, Health+1);
			rol_ame(playerid, "bebe una coca cola.");
			GivePlayerCash(playerid, -precio, "compra de cocacola");
			CobroNegocio(id_negocio[playerid],precio);
			if (InfoPersonaje[playerid][pSexo] == 1) ApplyAnimation(playerid, "GANGS", "drnkbr_prtl", 4.0, 0, 0, 1, 0, 6000, 1);
			else ApplyAnimation(playerid, "BAR", "dnk_stndF_loop", 4.0, 0, 0, 1, 0, 4000, 1);
		}
		case 2: // cerveza
		{
		    new precio = 10;
			if (GetPlayerCash(playerid) < precio)
			{
				format(string, sizeof string, "Te hacen falta $%s para comprar '{b42d2d}Cerveza{EBEBEB}' por $%s.", diner_coma(precio-GetPlayerCash(playerid)), diner_coma(precio));
				SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
				return 1;
			}
			if (DarObjeto(playerid, 65, 5) == 2) return 1;
			SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, "Compraste una botella de cerveza. (/beber)");
			GivePlayerCash(playerid, -precio, "compra de cerveza");
			CobroNegocio(id_negocio[playerid], precio);
		}
	}
	return 1;
}

Dialog:ShowGasolinera(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			if (CheckMoney(playerid, 50) == 0) return 1;
			autorepara[playerid] = 1;
			SendPlayerChatMessage(playerid, 0xA2DC35FF, "[Gas]:{FFFFFF} Compraste una lata de gasolina. Comandos: /rellenarauto");
			GivePlayerCash(playerid, -50, "compra de lata de gasolina");
			CobroNegocio(id_negocio[playerid], 50);
		}
		case 1:
		{
			if (CheckMoney(playerid, 2) == 0) return 1;
			new Float:Health = InfoPersonaje[playerid][pVida];
			if (Health < 101)	{	dar_vida(playerid, Health+20); 	}
			rol_ame(playerid, "come una bolsa de patatas.");
			ApplyAnimation(playerid, "GRAFFITI", "graffiti_Chkout", 4.0, 0, 0, 0, 0, 0, 1);
			GivePlayerCash(playerid, -20, "compra de bolsa de patatas");
			CobroNegocio(id_negocio[playerid], 20);
		}
		case 2:
		{
			if (CheckMoney(playerid, 10) == 0) return 1;
			new Float:Health = InfoPersonaje[playerid][pVida];
			if (Health < 101)	{	dar_vida(playerid, Health+2); 	}
			rol_ame(playerid, "bebe un refresco.");
			GivePlayerCash(playerid, -10, "compra de refresco");
			CobroNegocio(id_negocio[playerid], 10);
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DRINK_SPRUNK);
		}
		case 3:
		{
			if (CheckMoney(playerid, 40) == 0) return 1;
			if (DarObjeto(playerid, 42, 8) == 2) return 1;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendPlayerChatMessage(playerid, 0xA2DC35FF, "[Gas]:{FFFFFF} Compraste una caja de cigarros (8 unidades). Comandos: /fumar");
			GivePlayerCash(playerid, -40, "compra de 8 cigarros");
			CobroNegocio(id_negocio[playerid], 40);
		}
		case 4:
		{
			if (CheckMoney(playerid, 20) == 0) return 1;
			if (DarObjeto(playerid, 41, 8) == 2) return 1;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			SendPlayerChatMessage(playerid, 0xA2DC35FF, "[Gas]:{FFFFFF} Compraste un encendedor (8 usos).");
			GivePlayerCash(playerid, -20, "compra de encendedor 8u");
			CobroNegocio(id_negocio[playerid], 20);
		}
	}
	return 1;
}

Dialog:ShowAmmunation(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0: //puño americano
		{
			if (CheckMoney(playerid, 50) == 0) return 1;
			if (PlayerWeapon(playerid, 1) == 0) return 1;
			GivePlayerCash(playerid, -50, "compra de puño americano");
			CobroNegocio(id_negocio[playerid], 50);
		}
		case 1: //bate
		{
			if (CheckMoney(playerid, 100) == 0) return 1;
			if (PlayerWeapon(playerid, 5) == 0) return 1;
			GivePlayerCash(playerid, -100, "compra de bate");
			CobroNegocio(id_negocio[playerid], 100);
		}
		case 2: //9mm
		{
			if (CheckMoney(playerid, 1650) == 0) return 1;
			if (PlayerWeapon(playerid, 22) == 0) return 1;
			GivePlayerCash(playerid, -1650, "compra de 9mm");
			CobroNegocio(id_negocio[playerid], 1650);
		}
		case 3: //escopeta
		{
			if (CheckMoney(playerid, 5700) == 0) return 1;
			if (PlayerWeapon(playerid, 25) == 0) return 1;
			GivePlayerCash(playerid, -5700, "compra de escopeta");
			CobroNegocio(id_negocio[playerid], 5700);
		}
		case 4: //rifle de caza
		{
			if (CheckMoney(playerid, 7450) == 0) return 1;
			if (PlayerWeapon(playerid, 33) == 0) return 1;
			GivePlayerCash(playerid, -7450, "compra de rifle de caza");
			CobroNegocio(id_negocio[playerid], 7450);
		}
		case 5: //comprar balas
		{
			new mano = InfoPersonaje[playerid][pManoDerecha], cantidad = InfoPersonaje[playerid][pManoDerechaCant];
			new weaponid = InfoInventario[mano][IDArma], gformat[470];
			if (!weaponid) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás sosteniendo un arma en tu mano derecha.");
			if (cantidad == InfoInventario[mano][MaxCantidad])
			{
				format(gformat, sizeof gformat, "El máximo de balas de tu %s es de %d.", InfoInventario[mano][NombreObjeto], InfoInventario[mano][MaxCantidad]);
				SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
				return 1;
			}
			format(gformat, sizeof gformat, "{FFFFFF}El costo de cada bala es de {00CC00}1${FFFFFF}.\n\nPuedes comprar {3E62F4}%d balas{FFFFFF} más para tu {FE9A2E}%s{FFFFFF}.\n", InfoInventario[mano][MaxCantidad]-cantidad, InfoInventario[mano][NombreObjeto]);
			Dialog_Show(playerid, BuyBalas, DIALOG_STYLE_INPUT, "Compra de balas", gformat, "Comprar", "Volver");
		}
	}
	return 1;
}

Dialog:BuyBalas(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_comprar(playerid);
	if (!isnumeric(inputtext)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo números para las balas, vuelve a intentarlo.");
	new balasCant = strval(inputtext);
	new mano = InfoPersonaje[playerid][pManoDerecha], cantidad = InfoPersonaje[playerid][pManoDerechaCant];
	new weaponid = InfoInventario[mano][IDArma], gformat[470];
	if (cantidad+balasCant >= InfoInventario[mano][MaxCantidad]+1)
	{
		format(gformat, sizeof gformat, "No puedes comprar %d balas, si tu %s tiene %d balas, el máximo es %d.", balasCant, InfoInventario[mano][NombreObjeto], cantidad, InfoInventario[mano][MaxCantidad]);
		SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
		return 1;
	}
	new costo = balasCant*15;
	if (CheckMoney(playerid, costo) == 0) return 1;
	//quita dinero
	GivePlayerCash(playerid, -costo, "compra de balas");
	CobroNegocio(id_negocio[playerid], costo);
	//actualiza balas
	InfoPersonaje[playerid][pManoDerechaCant] += balasCant;
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, weaponid, InfoPersonaje[playerid][pManoDerechaCant]);
	//guarda variables
	ActualizarManos(playerid, 1);
	//mensaje de compra uwu
	format(gformat, sizeof gformat, "Compraste {3E62F4}%d balas{FFFFFF} a tu {FE9A2E}%s{FFFFFF} por {00CC00}$%s{FFFFFF}, ahora tienes {3E62F4}%d balas{FFFFFF}.", balasCant, InfoInventario[mano][NombreObjeto], diner_coma(costo), InfoPersonaje[playerid][pManoDerechaCant]);
	SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
	return 1;
}

Dialog:ShowSexShop(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			if (CheckMoney(playerid, 30) == 0) return 1;
			if (PlayerWeapon(playerid, 10) == 0) return 1;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			rol_ame(playerid, "compra un dildo morado.");
			GivePlayerCash(playerid, -30, "compra de dildo morado");
			CobroNegocio(id_negocio[playerid], 30);
		}
		case 1:
		{
			if (CheckMoney(playerid, 20) == 0) return 1;
			if (PlayerWeapon(playerid, 12) == 0) return 1;
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			rol_ame(playerid, "compra un consolador.");
			GivePlayerCash(playerid, -20, "compra de consolador");
			CobroNegocio(id_negocio[playerid], 20);
		}
	}
	return 1;
}

Dialog:ShowBaitShop(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	switch (listitem)
	{
		case 0:
		{
			DarObjeto(playerid, 92, 1);
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			rol_ame(playerid, "compra una caña de pescar.");
			GivePlayerCash(playerid, -150, "compra de aña de pescar");
			CobroNegocio(id_negocio[playerid], 150);
		}
		case 1:
		{
			PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
			rol_ame(playerid, "compra gusanos.");
			GivePlayerCash(playerid, -10, "compra de gusanos");
			CobroNegocio(id_negocio[playerid], 10);
		}
		case 2:
		{
			if(EsPescado(InfoPersonaje[playerid][pManoDerecha]))
			{
				InfoPersonaje[playerid][pManoDerecha] = 0;
				InfoPersonaje[playerid][pManoDerechaCant] = 0;
				ActualizarManos(playerid);

				GivePlayerCash(playerid, 50, "venta de peces");
				CobroNegocio(id_negocio[playerid], 5);
			}
			else
			{
				ShowInfoForPlayer(playerid, "No tienes ningun pescado en la mano derecha.", 3000);
			}
		}
	}
	return 1;
}

hide_comprarvehiculo(playerid)
{
	Loop(x, 3, 0)
		TextDrawHideForPlayer(playerid, CocheVS[x]);
	Loop(x, 7, 0)
		PlayerTextDrawHide(playerid, pCocheVS[playerid][x]);
}

HideConceTextdraw(playerid)
{
	Loop(x, 48, 0)
	{
		PlayerTextDrawHide(playerid, p_tdConce[playerid][x]);
	}
	CancelSelectTextDraw(playerid);
	SetCameraBehindPlayer(playerid);
}

cmd:carsign(playerid, params[])
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser el conductor de un vehículo.");
	new	faccion = InfoPersonaje[playerid][pMiembro];
	new result[32], vehicleid = GetPlayerVehicleID(playerid), string[256];
	new id = verificar_id_vehiculo(vehicleid);
	if (vehiculos_legales(vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo se puede usar CallSign en vehículos legales.");
	if (llaves_faccion(playerid, vehicleid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes las llaves de este vehículo de facción.");
	if (sscanf(params, "s[32]", result)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /carsign (Texto)");
	if (isnull(result) || strlen(result) > 31) return SendPlayerChatMessage(playerid, COLOR_GREY, "El callsign sólo puede contener 32 caracteres.");
	if (!isnull(InfoVehiculo[id][vCallSign])) //quitar
	{
		if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
		{
			DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
			InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
		}
		alm(InfoVehiculo[id][vCallSign], "");
	}
	else //poner
	{
		alm(InfoVehiculo[id][vCallSign], result);
		if (IsValidDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]))
		{
			DestroyDynamic3DTextLabel(InfoVehiculo[id][vOnCallSign]);
			InfoVehiculo[id][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
		}
		InfoVehiculo[id][vOnCallSign] = CreateDynamic3DTextLabel(result, 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, vehicleid);
		format(string, sizeof string, "[%s] %s(%s) fijó el carsign [%d]: %s", InfoFaccion[faccion][fLogo], GetNameFormat(playerid), InfoCuenta[playerid][jNombre], vehicleid, result);
		Log("f_logs/Carsign.txt", string);
	}
	guardar_string_mysql("vehiculos", "CallSign", InfoVehiculo[id][vID_sql], InfoVehiculo[id][vCallSign]);
	return 1;
}

cmd:cancelar(playerid, params[])
{
	new string[128], choice[32];
	if(sscanf(params, "s[32]", choice))
	{
		SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /cancelar (Nombre)");
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Nombres: arma - multa - coche - licencia");
		return 1;
	}
	else if(strcmp(choice,"arma",true) == 0)
	{
	    if (GunCliente[playerid] == -1) return SendPlayerChatMessage(playerid, -1, "Nadie te ha ofrecido un arma.");
		if (IsPlayerConnected(GunCliente[playerid]))
		{
			GunVendedor[GunCliente[playerid]] = -1;
			SendPlayerChatMessage(GunCliente[playerid], -1, "Cancelaron la compra.");
		}
		GunCliente[playerid] = -1;
		GunObjeto[playerid] = 0;
		GunCantidad[playerid] = 0;
		GunPrecio[playerid] = 0;
		SendPlayerChatMessage(playerid, -1, "Cancelaste la compra.");
	}
	else if(strcmp(choice,"coche",true) == 0) { Pla_vehicle[playerid] = 999; Price_vehicle[playerid] = 0; Osql_vehicle[playerid] = 0; }
	else if(strcmp(choice,"multa",true) == 0)
	{
	    if(TicketOffer[playerid] == 999) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te multado.");
	    format(string, sizeof string, "{player:%d} se niega a pagar una multa", playerid);
	    ProxDetector(30.0,playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	    format(string, sizeof string, "* {player:%d} canceló el pago de una multa de %d$.", playerid, TicketMoney[playerid]);
	    SendPlayerChatMessage(TicketOffer[playerid], -1, string);
	    TicketOffer[playerid] = 999;
	    TicketMoney[playerid] = 0;
	    Facturing[playerid] = 0;
	}
	else if(strcmp(choice,"licencia",true) == 0)
	{
	    if(NombreLicencia[playerid] == 999) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha ofrecido una licencia de armas.");
	    format(string, sizeof string, "{player:%d} se niega a pagar la licencia de armas.", playerid);
	    ProxDetector(30.0,playerid, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE);
	    format(string, sizeof string, "* {player:%d} canceló el pago de la licencia por %d dólares.", playerid, PrecioLicencia[playerid]);
	    SendPlayerChatMessage(NombreLicencia[playerid], -1, string);  // Mensaje al policia.
	    NombreLicencia[playerid] = 999;
	    PrecioLicencia[playerid] = 0;
	    Facturing[playerid] = 0;
	}
	else { return 1; }
	format(string, sizeof string, "* Cancelaste: %s.", choice);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	return 1;
}

cmd:verllaves(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	new playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /verllaves (jugador)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, -1, "Jugador desconectado.");
	SendPlayerChatMessage(playerid, COLOR_GREEN, "_______________________________________");
	SendClientMessageEx(playerid, COLOR_GRAD2, "*** Vehículos de %s  ***", GetNameFormat(playerid2));
	Loop(veh, totalvehiculos, 1) if (InfoVehiculo[veh][vTipo] == 0 && strcmp(InfoPersonaje[playerid2][pNombre_Apellido], InfoVehiculo[veh][vPropietario], true) == 0)
	{
		if (InfoVehiculo[veh][vEmbargo] != 0)  SendClientMessageEx(playerid, COLOR_WHITE, "Vehículo (%s) actualmente embargado con una multa $%s.", VehicleName[InfoVehiculo[veh][vModelo] - 400], diner_coma(InfoVehiculo[veh][vMulta]));
		else SendClientMessageEx(playerid, COLOR_WHITE, "Vehículo (%s)", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
	}
	SendPlayerChatMessage(playerid, COLOR_GREEN, "_______________________________________");
	return 1;
}

cmd:embargar(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (!IsPlayerInRangeOfPoint(playerid, 5.0,1636.041259,-1811.950317,13.524469)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás cerca del punto de incautación, no puedes confiscar!");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (!IsTrailerAttachedToVehicle(vehicleid)) return SendPlayerChatMessage(playerid, -1, "No estás en una grua.");
	new vehicleid2 = GetVehicleTrailer(vehicleid), veh = 0, gformat[256];
	if (!GetVehicleModel(vehicleid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El vehículo en el remolque se ha desenganchado y por lo tanto no puede ser confiscado.");
	//usuarios
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid2)
	{
		veh = v;
		break;
	}
	if (veh == 0)
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "No se pudo encontrar ningún tipo de registro en el vehículo y se ha soltado.");
		DetachTrailerFromVehicle(vehicleid);
		return 1;
	}
	if (InfoVehiculo[veh][vMulta] <= 100) return SendPlayerChatMessage(playerid, COLOR_GREY, "Para embargar un vehiculo es necesario que este mismo tenga mínimo $100 de multa.");
	format(gformat, sizeof gformat,"* Has confiscado el vehiculo de %s - Modelo %s.", InfoVehiculo[veh][vPropietario], VehicleName[InfoVehiculo[veh][vModelo] - 400]);
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, gformat);
	foreach(Player, playerid2) if (llaves_vehiculo(playerid2, vehicleid2) != -1)
	{
		format(gformat, sizeof gformat, "Su %s ha sido confiscado. Es posible que lo pueda sacar pagando la multa en LSPD.", VehicleName[InfoVehiculo[veh][vModelo] - 400]);
		SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, gformat);
	}
	format(gformat, sizeof gformat, "[CENTRAL] %s ha confiscado el vehiculo de %s - Modelo %s (No pagó $%s de multa).", GetNameFormat(playerid), InfoVehiculo[veh][vPropietario], VehicleName[InfoVehiculo[veh][vModelo] - 400], diner_coma(InfoVehiculo[veh][vMulta]));
	SendRadioMessage(InfoPersonaje[playerid][pMiembro], COLOR_RADIO, gformat, 1);
	InfoVehiculo[veh][vEmbargo] = 1;
	DetachTrailerFromVehicle(vehicleid);
	DestroyVehicle(vehicleid2);
	InfoVehiculo[veh][vMaleteroOn] = 0;
	Loop(x, 5, 0) if (InfoVehiculo[veh][vObjModelo][x] != 0) { if (IsValidDynamicObject(InfoVehiculo[veh][vTuneo][x])) DestroyDynamicObject(InfoVehiculo[veh][vTuneo][x]); }
	if (!isnull(InfoVehiculo[veh][vCallSign]))
	{
		if (IsValidDynamic3DTextLabel(InfoVehiculo[veh][vOnCallSign]))
		{
			DestroyDynamic3DTextLabel(InfoVehiculo[veh][vOnCallSign]);
			InfoVehiculo[veh][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
		}
	}
	InfoVehiculo[veh][vIG_id] = 0;
	InfoVehiculo[veh][vSpawned] = 0;
	InfoVehiculo[veh][vTimeSave] = 0;
	return 1;
}

cmd:enganchar(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (!IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "{FFFF00}[ERROR]:{FFFFFF} Tienes que estar en un vehículo.");
	new carid = GetPlayerVehicleID(playerid);
	if (!IsATowTruck(carid)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "{FFFF00}[ERROR]:{FFFFFF} No puedes remolcar en este tipo de vehículo.");
	new closestcar = GetClosestCar(playerid, carid);
	if (GetDistancePlayerVeh(playerid,closestcar) <= 8 && !IsTrailerAttachedToVehicle(carid))
	{
		foreach(Player, i) if (llaves_vehiculo(i, carid) != -1)
		{
			if (CercaDelMarica(30.0, playerid, i))
				SendPlayerChatMessage(i, COLOR_LIGHTBLUE, "Alguien está tratando de remolcar tu vehículo!");
		}
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Este vehiculo no tiene ningún registro, está disponible para embargar");
		AttachTrailerToVehicle(closestcar,carid);
	}
	return 1;
}

cmd:desenganchar(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	new vehicleid = GetPlayerVehicleID(playerid);
	if (!IsTrailerAttachedToVehicle(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_WHITE,"Aún no has enganchado nada.");
	SendPlayerChatMessage(playerid, COLOR_WHITE,"Has desenganchado el vehículo que traías.");
	DetachTrailerFromVehicle(vehicleid);
	return 1;
}

cmd:dejarmulta(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (InfoPersonaje[playerid][pRango] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo rangos 2 y superiores pueden dejar multas!");
	new vehicleid, precio, gformat[190];
	if (sscanf(params, "dd", vehicleid, precio)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dejarmulta (VehicleID /dl) (Precio)");
	if (precio < 10 || precio > 1000) return SendPlayerChatMessage(playerid, COLOR_GREY, "Mínimo 10$ - Máximo 1,000$ de multa.");
	if (!GetVehicleModel(vehicleid)) return SendPlayerChatMessage(playerid, -1, "El vehículo seleccionado no se encuentra spawneado.");
	new veh = -1;
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		veh = v;
		break;
	}
	if (veh == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese vehículo no tiene ningún registro o no tiene propietario, llevalo al depósito.");
	if (InfoVehiculo[veh][vMulta]+precio >= 1000) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Este vehiculo ya excedio el máximo de multas, se debe embargar.");
	InfoVehiculo[veh][vMulta] += precio;
	format(gformat, sizeof gformat, "Dejaste una multa de $%s en el vehículo de %s, modelo %s.", diner_coma(precio), InfoVehiculo[veh][vPropietario], GetVehicleName(vehicleid));
	SendPlayerChatMessage(playerid, COLOR_WHITE, gformat);
    guardar_int_mysql("vehiculos", "Multa", InfoVehiculo[veh][vID_sql], InfoVehiculo[veh][vMulta]);
	return 1;
}

cmd:remolcar(playerid, params[])
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    new Float:vX,Float:vY,Float:vZ,Found=0,vid=0,idcar = GetPlayerVehicleID(playerid);
		if(GetVehicleModel(idcar) == 525)
		{
			new Float:pX,Float:pY,Float:pR;
			GetPlayerPos(playerid,pX,pY,pR);

			while((vid<GetVehiclePoolSize())&&(!Found))
			{
				vid++;
				GetVehiclePos(vid,vX,vY,vZ);
				if ((floatabs(pX-vX)<7.0)&&(floatabs(pY-vY)<7.0)&&(floatabs(pR-vZ)<7.0)&&(vid!=GetPlayerVehicleID(playerid)))
				{
					Found=1;
					if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
					{
		   				DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
					}
			   		else
			   		{
		   				AttachTrailerToVehicle(vid,GetPlayerVehicleID(playerid));
					}
				}
			}
			if(!Found)
			{
				SendPlayerChatMessage(playerid,COLOR_WHITE,"No hay ningún vehículo cerca.");
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes remolcar con este vehículo.");
	}
	return 1;
}

new SQLIDVEH[MAX_PLAYERS];

cmd:qmod(playerid)
{
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Debes ser el conductor de un vehículo.");
	new vehicleid = GetPlayerVehicleID(playerid);
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[v][vEmbargo] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehículo se encuentra embargado.");
		new string[222], modList[512], count = 0;
		if (llaves_vehiculo(playerid, vehicleid) == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No eres el propietario de este vehículo.");
		Loop(f, MAX_MODIFICACIONES, 0) if (GetVehicleComponentInSlot(vehicleid, f) != 0)
		{
			if (f != 9 && f != 7 && f != 8)
			{
				format(modList, sizeof modList, "%s\n%s - %s", modList, partType(f), partName(GetVehicleComponentInSlot(vehicleid, f)));
			}
			else format(modList, sizeof(modList), "%s\n%s", modList, partType(f));
			format(string, sizeof string, "partList%d", count);
			SetPVarInt(playerid, string, GetVehicleComponentInSlot(vehicleid, f));
			count++;
		}
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Este vehiculo no tiene ninguna modificación.");
		format(modList, sizeof modList, "%s\nTodo", modList);
		format(string, sizeof string, "partList%d", count);
		SetPVarInt(playerid, string, 999);
		count++;
		SetPVarInt(playerid, "modCount", count);
		Dialog_Show(playerid, QuitMods, DIALOG_STYLE_LIST, "Partes", modList, "Continuar", "Salir");
		SQLIDVEH[playerid] = v;
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_WHITE, "Debes estar dentro de un vehículo propio o con llaves.");
 	return 1;
}
alias:qmod("quitarmodificaciones");

Dialog:QuitMods(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new veh = SQLIDVEH[playerid], count = GetPVarInt(playerid, "modCount"), string[64];
	Loop(i, count, 0) if (listitem == i)
	{
		format(string, sizeof string, "partList%i", i);
		new partID = GetPVarInt(playerid, string), vehicleid = InfoVehiculo[veh][vIG_id];
		if (partID == 999)
		{
			Loop(f, MAX_MODIFICACIONES, 0)
			{
				RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, f));
				InfoVehiculo[veh][vModificacion][f] = 0;
				format(string, sizeof string, "Modificacion%d", f+1);
				guardar_int_mysql("vehiculos", string, InfoVehiculo[veh][vID_sql], 0);
			}
			SendPlayerChatMessage(playerid, 0xA2DC35FF, "[INFO]:{FFFFFF} Todas las modificaciones se han eliminado de tu vehículo.");
			return 1;
		}
		RemoveVehicleComponent(vehicleid, partID);
		InfoVehiculo[veh][vModificacion][GetVehicleComponentType(partID)] = 0;
		format(string, sizeof string, "Modificacion%d", GetVehicleComponentType(partID)+1);
		guardar_int_mysql("vehiculos", string, InfoVehiculo[veh][vID_sql], 0);
		SendPlayerChatMessage(playerid, 0xA2DC35FF, "[INFO]:{FFFFFF} La modificación que has seleccionado ha sido eliminado.");
	}
	return 1;
}

cmd:afks(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], count = 0;
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2) && InfoPersonaje[playerid2][pModoAfk] > 120)
	{
		format(string, sizeof string, "[%d] %s (%s) lleva afk {00cc00}%s", playerid2, InfoCuenta[playerid2][jNombre], InfoPersonaje[playerid2][pNombre_Apellido], Segundos_tiempo(InfoPersonaje[playerid2][pModoAfk]));
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, string);
	    count++;
	}
	if (count != 0) format(string, sizeof string, "Hay %d jugadores en estado pausa (afk).", count);
	else format(string, sizeof string, "No hay ningún jugador en estado pausa (afk)");
	SendPlayerChatMessage(playerid, 0x00CC00FF, string);
	return 1;
}
alias:afks("verafks");

cmd:mandarls(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /mandarls (ID/Jugador)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Usuario desconectado.");
	if (GetPlayerAdmin(playerid2, 10) != 0) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes hacer esto con propietarios o programadores.");

	SendPlayerChatMessage(playerid2, COLOR_WHITE, "Fuiste llevado a Los Santos por un miembro de la administración.");
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha mandado %s(%d) a Los Santos.", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	SetPosEx(playerid2, 1529.6, -1705.5, 13.4, 0.0, 0, 0, 1);
	return 1;
}
alias:mandarls("llevarls");

cmd:mps(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new string[180];
	if (!InfoCuenta[playerid][jVerMP])
	{
		InfoCuenta[playerid][jVerMP] = 1;
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) dejó de ver los /mp.", InfoCuenta[playerid][jNombre], playerid);
	}
	else
	{
		InfoCuenta[playerid][jVerMP] = 0;
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ahora ve los /mp.", InfoCuenta[playerid][jNombre], playerid);
	}
	SendAdminMessage(0xFFFFFFFF, string);
	guardar_int_mysql("cuentas", "VerMP", InfoCuenta[playerid][jID], InfoCuenta[playerid][jVerMP]);
	return 1;
}
alias:mps("vermps", "verprivados");

cmd:musica(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /musica (URL.mp3)");
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2) && TipoAudio[playerid] == 0 && InfoPersonaje[playerid2][pTogMusic] == 1)
	{
		PlayAudioStreamForPlayer(playerid2, params);
	}
	return 1;
}

cmd:revisarmaletero(playerid, params[])
{
	new vehicleid;
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /revisarmaletero (VehiculoID) [el de /dl]");
	if (vehicleid < 1 || vehicleid > 1999) return SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no es de ningún usuario o no existe. (2)");
	if (!CercaDelVehiculo(playerid, vehicleid, 9.0)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca del vehículo especificado.");
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo seleccionado no tiene modelo.");
		if (InfoVehiculo[id][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo seleccionado se encuentra oculto.");
		SendClientMessageEx(playerid, COLOR_GREEN, "Propietario: %s | Modelo: %s (%d)", InfoVehiculo[id][vPropietario], GetNameVehicle(InfoVehiculo[id][vModelo]), InfoVehiculo[id][vModelo]);
		new gformat[190];
		format(gformat, sizeof gformat, "revisa el maletero del vehículo %s.", GetNameVehicle(InfoVehiculo[id][vModelo]));
		pc_cmd_me(playerid, gformat);
		new count = 0;
		Loop(x, 10, 0) if (InfoVehiculo[id][vMaletero][x] != 0)
		{
			count++;
			SendClientMessageEx(playerid, COLOR_YELLOW, "#%d %s", x+1, slot_objeto(InfoVehiculo[id][vMaletero][x], InfoVehiculo[id][vMaleteroCant][x]));
		}
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nada en el maletero.");
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no existe o no tiene registro.");
	return 1;
}

cmd:limpiarmaletero(playerid, params[])
{
	new vehicleid;
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (InfoPersonaje[playerid][pRango] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser mínimo rango 2.");
	if (sscanf(params, "d", vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /revisarmaletero (VehiculoID) [el de /dl]");
	if (vehicleid < 1 || vehicleid > 1999) return SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no es de ningún usuario o no existe. (2)");
	if (!CercaDelVehiculo(playerid, vehicleid, 9.0)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca del vehículo especificado.");
	Loop(id, totalvehiculos, 1) if (InfoVehiculo[id][vIG_id] == vehicleid)
	{
		if (InfoVehiculo[id][vModelo] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo seleccionado no tiene modelo.");
		if (InfoVehiculo[id][vSpawned] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Vehículo seleccionado se encuentra oculto.");
		new count = 0;
		Loop(x, 10, 0) if (InfoVehiculo[id][vMaletero][x] != 0)
		{
			count++;
			new dex_query[170];
			InfoVehiculo[id][vMaletero][x] = 0;
			InfoVehiculo[id][vMaleteroCant][x] = 0;
			mysql_format(db_samp, dex_query, sizeof dex_query, "UPDATE vehiculos SET Maletero%d = 0, MaleteroCant%d = 0 WHERE ID = '%d'", x+1, x+1, InfoVehiculo[id][vID_sql]);
			mysql_tquery(db_samp, dex_query);
		}
		if (count == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nada que incautar del vehículo.");
		new gformat[190];
		format(gformat, sizeof gformat, "incauta los objetos del vehículo %s.", GetNameVehicle(InfoVehiculo[id][vModelo]));
		pc_cmd_me(playerid, gformat);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "El vehículo seleccionado no existe o no tiene registro.");
	return 1;
}

cmd:reanimar(playerid, params[])
{
	new string[170], playerid2;
	if (!member_faccion(playerid, 1, 2, 3, 4, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo para LSPD, FBI, USMC, LSCSD y LSFD.");
	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes reanimar a alguien desde un vehículo.");
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes hacer esto, tu también estás herido.");
    if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /reanimar (PlayerID)");
    if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "No te puedes reanimar a tí mismo, abusadol de mielda :v");
	if (!CercaDelMarica(3.5, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador no está cerca tuyo.");
	if (InfoPersonaje[playerid2][pMuerto] == 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está muerto.");
	if (InfoPersonaje[playerid2][pEstado] == 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está muerto.");
	if (GetPVarInt(playerid2, "EstaCrack") == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está en estado herido.");

	if(pDroga[playerid2][Sobredosis]){
		if(InfoPersonaje[playerid][pManoDerecha] == 72)InfoPersonaje[playerid][pManoDerechaCant]--;
		else if(InfoPersonaje[playerid][pManoIzquierda] == 72) 	InfoPersonaje[playerid][pManoIzquierda]--;
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "Para reanimar a este jugador necesitas Naloxona ¡tiene una sobredosis!");
	}
	pDroga[playerid2][Sobredosis] = 0;

	timer_herido[playerid2] = 0;
	KillEMSQueue(playerid2);
	ResetPlayerHeridas(playerid2);
	if (IsValidDynamic3DTextLabel(InfoPersonaje[playerid2][pNameTag]))
	{
		DestroyDynamic3DTextLabel(InfoPersonaje[playerid2][pNameTag]);
		InfoPersonaje[playerid2][pNameTag] = Text3D:INVALID_3DTEXT_ID;
	}
	TogglePlayerControllable(playerid, 0);
	TogglePlayerControllable(playerid2, 0);
	SetTimerEx("Descongelar", 8000, false, "i", playerid);
	SetTimerEx("Descongelar", 8000, false, "i", playerid2);
	ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 1, 1, 0, 0, 1);
	ApplyAnimation(playerid2, "CRACK", "crckidle2", 4.1, 1, 1, 1, 0, 0, 1);
	SetCameraBehindPlayer(playerid2);
	dar_vida(playerid2, 70);
	InfoPersonaje[playerid2][pMuerto] = 0;
	InfoPersonaje[playerid2][pEstado] = 0;
	YaAviso[playerid2] = 0;
	format(string, sizeof string, "* %s reanima a %s mediante primeros auxilios.", GetNameFormat(playerid), GetNameFormat(playerid2));
	ProxDetector(20.0, playerid, string, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF, 0x1EB032FF);
	guardar_int_mysql("personajes", "Muerto", InfoPersonaje[playerid2][pID], 0);
	guardar_int_mysql("personajes", "Estado", InfoPersonaje[playerid2][pID], 0);
	guardar_int_mysql("personajes", "Sobredosis", InfoPersonaje[playerid2][pID], 0);
	return 1;
}

cmd:spec(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new tmp[32];
	if(sscanf(params, "s[32]", tmp)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /spec (playerid/off)");
	if(strcmp("off", tmp, true, strlen(tmp)) == 0)
	{
		if(Spectating[playerid] > 0)
		{
			GettingSpectated[Spectate[playerid]] = 999;
			Spectating[playerid] = 0;
			Spectate[playerid] = 999;
			SetPVarInt(playerid, "SpecState", -1);
			SetPVarInt(playerid, "SpecOff", 1 );
			TogglePlayerSpectating( playerid, false );
			SetCameraBehindPlayer(playerid);
			return 1;
		}
	}
	new playerid2 = ReturnUser(tmp);
	if(IsPlayerConnected(playerid2))
	{
		if(playerid2 != INVALID_PLAYER_ID)
		{
			if(Spectating[playerid] == 0)
			{
				new Float: pPositions[ 3 ];
				GetPlayerPos(playerid, pPositions[ 0 ], pPositions[ 1 ], pPositions[ 2 ]);
				SetPVarFloat(playerid, "SpecPosX", pPositions[ 0 ]);
				SetPVarFloat(playerid, "SpecPosY", pPositions[ 1 ]);
				SetPVarFloat(playerid, "SpecPosZ", pPositions[ 2 ]);
				SetPVarInt(playerid, "SpecInt", GetPlayerInterior(playerid));
				SetPVarInt(playerid, "SpecVW", GetPlayerVirtualWorld(playerid));

				if(IsPlayerInAnyVehicle(playerid2))
				{
					TogglePlayerSpectating(playerid, true);
					new carid = GetPlayerVehicleID( playerid2 );
					PlayerSpectateVehicle( playerid, carid );
					SetPlayerInterior( playerid, GetPlayerInterior( playerid2 ) );
					SetPlayerVirtualWorld( playerid, GetPlayerVirtualWorld( playerid2 ) );
					SetPVarInt(playerid, "SpecState", GetPlayerState(playerid2));
				}
				else
				{
					TogglePlayerSpectating(playerid, true);
					PlayerSpectatePlayer( playerid, playerid2 );
					SetPlayerInterior( playerid, GetPlayerInterior( playerid2 ) );
					SetPlayerVirtualWorld( playerid, GetPlayerVirtualWorld( playerid2 ) );
					SetPVarInt(playerid, "SpecState", GetPlayerState(playerid2));
				}
				GettingSpectated[playerid2] = playerid;
				Spectate[playerid] = playerid2;
				Spectating[playerid] = 1;
			}
			else
			{
				if(IsPlayerInAnyVehicle(playerid2))
				{
					TogglePlayerSpectating(playerid, true);
					new carid = GetPlayerVehicleID( playerid2 );
					PlayerSpectateVehicle( playerid, carid );
					SetPlayerInterior( playerid, GetPlayerInterior( playerid2 ) );
					SetPlayerVirtualWorld( playerid, GetPlayerVirtualWorld( playerid2 ) );
					SetPVarInt(playerid, "SpecState", GetPlayerState(playerid2));
				}
				else
				{
					TogglePlayerSpectating(playerid, true);
					PlayerSpectatePlayer( playerid, playerid2 );
					SetPlayerInterior( playerid, GetPlayerInterior( playerid2 ) );
					SetPlayerVirtualWorld( playerid, GetPlayerVirtualWorld( playerid2 ) );
					SetPVarInt(playerid, "SpecState", GetPlayerState(playerid2));
				}
				GettingSpectated[Spectate[playerid]] = 999;
				GettingSpectated[playerid2] = playerid;
				Spectate[playerid] = playerid2;
				Spectating[playerid] = 1;
			}
		}
	}
	else SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese jugador está desconectado.");
	return 1;
}

cmd:liberar(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[256], playerid2, query[410];
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /liberar (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador no conectado.");
	if (InfoPersonaje[playerid2][pTiempoSancion] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está sancionado o en prisión.");
	format(string, sizeof string, "[ADMIN]: %s fue liberado de prisión por %s.", NombreDeCuenta(playerid2), InfoCuenta[playerid][jNombre]);
	Log("f_logs/admin.log", string);
	format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) sacó de prisión a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	if (InfoPersonaje[playerid2][pSancionado] == 1) InfoPersonaje[playerid2][pJails]--;
	InfoPersonaje[playerid2][pSancionado] = 0;
	InfoPersonaje[playerid2][pEstrellas] = 0;
	SetPlayerWantedLevel(playerid2, 0);
	InfoPersonaje[playerid2][pTiempoSancion] = 0;
	SetPosEx(playerid2, 1529.6, -1705.5, 13.4, 0.0, 0, 0, 1);
	alm(InfoPersonaje[playerid2][pBySancion], "none");
	alm(InfoPersonaje[playerid2][pRazonSancion], "none");
	TogglePlayerControllable(playerid2, true);
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Sancionado = 0, Estrellas = 0, TiempoSancion = 0, Jails = '%d', BySancion = '%e', RazonSancion = '%e' WHERE ID = '%d'", InfoPersonaje[playerid2][pJails], InfoPersonaje[playerid2][pBySancion], InfoPersonaje[playerid2][pRazonSancion], InfoPersonaje[playerid2][pID]);
	mysql_tquery(db_samp, query);
	return 1;
}

cmd:roleplay(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (Active_Rol != 0) { Active_Rol = 0, SendPlayerChatMessage(playerid, COLOR_YELLOW, "Test de rol desactivado."); }
	else { Active_Rol = 1, SendPlayerChatMessage(playerid, COLOR_GREEN, "Test de rol activado."); }
	return 1;
}

cmd:register(playerid)
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (Active_Registro != 0) { Active_Registro = 0, SendPlayerChatMessage(playerid, COLOR_YELLOW, "Registro desactivado."); }
	else { Active_Registro = 1, SendPlayerChatMessage(playerid, COLOR_GREEN, "Registro activado."); }
	return 1;
}

cmd:dardinero(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new playerid2, dinero, string[170];
	if (sscanf(params, "dd", playerid2, dinero)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /dardinero (PlayerID) ($)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador desconectado.");
	GivePlayerCash(playerid2, dinero, "dardinero (admin)");
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) ha dado $%s dólares a %s(%d).", InfoCuenta[playerid][jNombre], playerid, diner_coma(dinero), GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	format(string, sizeof string, "%s ha dado $%s dólares a %s.", InfoCuenta[playerid][jNombre], diner_coma(dinero), NombreDeCuenta(playerid2));
	Log("f_logs/dardinero.log", string);
	return 1;
}

cmd:venderlaser(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], playerid2, slot, color[32], invoice[64];
	if (sscanf(params, "ddss[64]", playerid2, slot, color, invoice)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /venderlaser (playerid) (slot(0-9)) (red/green/orange/yellow/pink/blue) (precio)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	if (slot < 0 || slot > 6) return SendPlayerChatMessage(playerid, COLOR_GRAD1, "{FFFF00}[ERROR]:{FFFFFF} Los Slots de los toys son del número 0 al 6.");
	if (strcmp(color,"red",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 18643;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	else if(strcmp(color,"green",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 19083;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	else if(strcmp(color,"orange",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 19082;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	else if(strcmp(color,"yellow",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 19084;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	else if(strcmp(color,"pink",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 19081;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	else if(strcmp(color,"blue",true) == 0)
	{
		InfoPersonaje[playerid2][ptModelo][slot] = 19080;
		InfoPersonaje[playerid2][ptHueso][slot] = 6;
		InfoPersonaje[playerid2][ptPosX][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosY][slot] = 0.0;
		InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
		InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	}
	ActualizarToy(playerid2, slot);
	format(string, sizeof string, "Recibiste un laser de color %s en el slot %d, usa /toys para verlo.", color, slot);
	SendPlayerChatMessage(playerid2, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "Le diste a %s laser de color %s en el slot %d", GetNameFormat(playerid2), color, slot);
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "[SHOPLASER] %s dió %s un laser toy - Pagó fue de %s", GetNameFormat(playerid), GetNameFormat(playerid2), invoice);
	Log("f_logs/shoplog.log", string);
	return 1;
}

cmd:congelar(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /congelar (playerid)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Usuario desconectado.");
	if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin]) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes congelar a un administrador de mayor nivel.");
	SetPVarInt(playerid2, "IsFrozen", 1);
	TogglePlayerControllable(playerid2, 0);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) congeló a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:descongelar(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /descongelar (playerid)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Usuario desconectado.");
	DeletePVar(playerid2, "IsFrozen");
	TogglePlayerControllable(playerid2, 1);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) descongeló a %s(%d).", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:cambiarhora(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[160], time1, time2, time3;
	if(sscanf(params, "ddd", time1, time2, time3)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /cambiarhora (hora) (minuto) (segundo)");
	xHora = time1; xMinuto = time2; xSegundo = time3;
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnected(playerid2)) { SyncPlayerTime(playerid); }
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) cambió la hora a %d/%d/%d.", InfoCuenta[playerid][jNombre], playerid, time1, time2, time3);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}

cmd:setweather(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new weather, string[170];
	if (sscanf(params, "d", weather)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /setweather (clima id)");
	if (weather < 0||weather > 45) { SendPlayerChatMessage(playerid, COLOR_GREY, "Climas: 0 a 45."); return 1; }
	SetWeatherEx(weather);
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) cambió el clima al ID %d", InfoCuenta[playerid][jNombre], playerid, weather);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}
alias:setweather("cambiarclima");

cmd:gotoco(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new Float: pos[3], int, vw;
	if(sscanf(params, "fffdd", pos[0], pos[1], pos[2], int, vw)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /gotoco (coordenada x) (coordenada y) (coordenada z) (interior) (virtualworld)");
	SendPlayerChatMessage(playerid, COLOR_GRAD2, "Fuiste a las coordenadas.");
	SetPosEx(playerid, pos[0], pos[1], pos[2], 0.0000, int, vw, 1);
	return 1;
}
alias:gotoco("ircor", "ircordenada", "ircoordenada");

cmd:getpos(playerid, params[])
{
	if (CheckAdminCMD(playerid, 3)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[170], Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	format(string,sizeof string, "X: %f | Y: %f | Z: %f | Int: %d | VW: %d", X,Y,Z, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	SendPlayerChatMessage(playerid, 0xFE9A2EAA, string);
	return 1;
}

cmd:curar(playerid, params[])
{
	if (!member_faccion(playerid, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de LSFD.");
	if (InfoPersonaje[playerid][pTriageTime] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes esperar 2 minutos para hacer esto de nuevo.");
	new gformat[190], playerid2;
	if (sscanf(params, "u", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /curar (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador desconectado.");
	if (!CercaDelMarica(5.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador muy lejos de ti.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te puedes curar tu mismo.");
	if (IsPlayerInAnyVehicle(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador está dentro de un vehículo.");
	if (InfoPersonaje[playerid2][pMuerto] == 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está en estado muerto.");
	if (GetPVarInt(playerid2, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está en estado herido, usa /reanimar.");

	format(gformat, sizeof gformat, "da servicio médico a %s", GetNameFormat(playerid2));
	pc_cmd_me(playerid, gformat);
	InfoPersonaje[playerid][pTriageTime] = 120;
	dar_vida(playerid2, 100);
	return 1;
}

cmd:spinchos(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo miembros de LSPD o FBI.");
	if (IsPlayerInAnyVehicle(playerid) || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes estar dentro de un vehículo o interior para usar esto.");
	if (InfoPersonaje[playerid][pRango] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser mínimo rango 2.");
	new id = -1, zone[MAX_ZONE_NAME];
	Loop(i, MAX_PINCHOS, 0) if (SpikeStrips[i][sX] != 0)
	{
		if (IsPlayerInRangeOfPoint(playerid, 4.0, SpikeStrips[i][sX], SpikeStrips[i][sY], SpikeStrips[i][sZ]))
		{
			id = i;
			break;
		}
	}
	if (id == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca de ningún pincho, usa /verpinchos.");
	if (IsValidDynamicObject(SpikeStrips[id][sObjectID])) { DestroyDynamicObject(SpikeStrips[id][sObjectID]); }
	SpikeStrips[id][sX] = 0; SpikeStrips[id][sY] = 0; SpikeStrips[id][sZ] = 0;
	SpikeStrips[id][sObjectID] = INVALID_OBJECT_ID;
	GetPlayer3DZone(playerid, zone, sizeof zone);
	SendClientMessageEx(playerid, COLOR_RADIO, "Pincho %d borrado (%s).", id, zone);
	return 1;
}
alias:spinchos("qspikes", "cspincho");

cmd:ppinchos(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Sólo miembros de LSPD o FBI.");
	if (IsPlayerInAnyVehicle(playerid) || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes estar dentro de un vehículo o interior para usar esto.");
	if (InfoPersonaje[playerid][pRango] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes ser mínimo rango 2.");
	new id = -1;
	Loop(i, MAX_PINCHOS, 0) if (SpikeStrips[i][sX] == 0)
	{
		id = i;
		break;
	}
	if (id == -1) return SendClientMessageEx(playerid, COLOR_GREY, "* No se pueden crear más de %d pinchos.", MAX_PINCHOS);
	new Float:p[4];
	GetPlayerPos(playerid, p[0], p[1], p[2]);
	GetPlayerFacingAngle(playerid, p[3]);
	SpikeStrips[id][sObjectID] = CreateDynamicObject(2899, p[0], p[1]-1.0, p[2] - 0.8, 0, 0, p[3]+90.0);
	SpikeStrips[id][sX] = p[0];
	SpikeStrips[id][sY] = p[1]-1.0;
	SpikeStrips[id][sZ] = p[2];
	GetPlayer3DZone(playerid, SpikeStrips[id][sDeployedAt], MAX_ZONE_NAME);
	alm(SpikeStrips[id][sDeployedBy], NombreDeCuenta(playerid));
	SendClientMessageEx(playerid, COLOR_YELLOW, "Puedes remover el pincho (%d - %s) usando /spinchos.", id, SpikeStrips[id][sDeployedAt]);
	return 1;
}
alias:ppinchos("pspikes", "ppincho");

cmd:spikes(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Tienes que estar en el piso para usar este comando.");
	if (InfoPersonaje[playerid][pRango] < 3) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Necesitas ser mayor de rango 3.");
	SendPlayerChatMessage(playerid, COLOR_GREEN, "Spikes actuales:");
	new string[180], count = 0;
	Loop(i, MAX_PINCHOS, 0) if (SpikeStrips[i][sX] != 0)
	{
		format(string, sizeof string, "Pincho %d | Localización: %s | Creador: %s", i, SpikeStrips[i][sDeployedAt], SpikeStrips[i][sDeployedBy]);
		SendPlayerChatMessage(playerid, COLOR_GRAD2, string);
		count++;
	}
	if (count == 0) SendPlayerChatMessage(playerid, -1, "No hay ningún pincho creado.");
	return 1;
}
alias:spikes("verpinchos");

cmd:nuevos(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	SendPlayerChatMessage(playerid, COLOR_GREEN, "Lista de todos los usuarios con menos de 5 horas de juego.");
	new szNoobs[120];
	foreach(Player, i) if (IsPlayerConnectedEx(i) && InfoPersonaje[i][pHorasOn] < 5)
	{
		format(szNoobs, sizeof szNoobs, "* %s (%d) | Horas conectado: %d", GetNameFormat(i), i, InfoPersonaje[i][pHorasOn]);
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, szNoobs);
	}
	return 1;
}

cmd:ram(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (GetPVarInt(playerid, "EstaCrack") != 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes hacer esto ahora.");
	Loop(id, totalcasas, 1) if (IsPlayerInRangeOfPoint(playerid, 3, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]) && InfoCasa[id][cExteriorInt] == InfoPersonaje[playerid][pInterior] && InfoCasa[id][cExteriorVW] == InfoPersonaje[playerid][pVirtualWorld])
	{
		rol_auto(playerid, "rompe la puerta y entra por ella.");
		SetPlayerInterior(playerid, InfoCasa[id][cInteriorInt]);
		SetPlayerVirtualWorld(playerid, InfoCasa[id][cInteriorVW]);
		SetPlayerPosEx(playerid, InfoCasa[id][cInteriorX], InfoCasa[id][cInteriorY], InfoCasa[id][cInteriorZ]);
		GameTextForPlayer(playerid, "~r~Rompiste la puerta", 5000, 1);
		KillTimer(VisitaTimer[playerid]);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en la entrada de ninguna casa.");
	return 1;
}

cmd:esposar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes hacer esto ahora.");
	new string[170], playerid2;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /esposar (JugadorID)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Jugador especificado inválido.");
	if (!CercaDelMarica(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está cerca tuyo.");
	if (playerid2 == playerid) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes hacer esto contigo mismo.");
	if (GetPVarInt(playerid2, "PlayerCuffed") == 1)
	{
		format(string, sizeof string, "le quita las esposas a %s.", GetNameFormat(playerid2));
		rol_auto(playerid, string);
		ClearAnimations(playerid2);
		RemovePlayerAttachedObject(playerid2, 0);
		SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
		DeletePVar(playerid2, "PlayerCuffed");
		return 1;
	}
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_CUFFED); //animacion
	SetPlayerAttachedObject(playerid2, 0, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
	format(string, sizeof string, "le pone las esposas a %s.", GetNameFormat(playerid2));
	rol_auto(playerid, string);
	SetPVarInt(playerid2, "PlayerCuffed", 1);
	return 1;
}

puede_detener(playerid)
{
	if (GetPVarInt(playerid, "PlayerCuffed") == 1) return 1;
	if (Tied[playerid] != 0) return 1;
	return 0;
}

cmd:detener(playerid, params[])
{
	if (gLastCar[playerid] == 0) return SendPlayerChatMessage(playerid, -1, "No te has subido a ningún vehículo.");
	new string[170], playerid2, seat;
	if (sscanf(params, "dd", playerid2, seat)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /detener (PlayerID) (Asiento 1-3)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Jugador desconectado.");
	if (playerid2 == playerid) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes hacer esto contigo.");
	if (!CercaDelMarica(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No estás cerca del jugador seleccionado.");
	if (puede_detener(playerid2) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador no está esposado o amarrado con /atar.");
	if (IsPlayerInAnyVehicle(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Esa persona está en un vehiculo.");
	if (seat < 1 || seat > 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "Asientos: 1 al 3.");
	new carid = gLastCar[playerid];
	if (IsSeatAvailable(carid, seat))
	{
		new Float:pos[6];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerPos(playerid2, pos[3], pos[4], pos[5]);
		GetVehiclePos(carid, pos[0], pos[1], pos[2]);
		if (floatcmp(floatabs(floatsub(pos[0], pos[3])), 10.0) != -1 &&
		floatcmp(floatabs(floatsub(pos[1], pos[4])), 10.0) != -1 &&
		floatcmp(floatabs(floatsub(pos[2], pos[5])), 10.0) != -1) return false;
		RemovePlayerAttachedObject(playerid2, playerid);
		SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
		format(string, sizeof string, "sube a %s al vehiculo.", GetNameFormat(playerid), GetNameFormat(playerid2));
		rol_auto(playerid, string);
		GameTextForPlayer(playerid2, "~r~Detenido", 2500, 3);
		ClearAnimations(playerid2);
		TogglePlayerControllable(playerid2, false);
		PutPlayerInVehicleEx(playerid2, carid, seat);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese asiento no está disponible.");
	return 1;
}

cmd:sfondos(playerid, params[])
{
	if (!Propietario_faccion(playerid, 5)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres líder del Gobierno.");
	new string[180], amount, reason[64];
	if (sscanf(params, "ds[64]", amount, reason))
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /sfondos (monto) (razón)");
		format(string, sizeof string, "* BALANCE: $%s.", diner_coma(Tax));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		return 1;
	}
	if (amount < 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El monto es inválido.");
	if (Tax < amount) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No hay fondos suficientes.");
	Tax -= amount;
	GivePlayerCash(playerid, amount, "sfondos");
	format(string, sizeof string, "Retiraste $%s de los fondos del gobierno.", diner_coma(amount));
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	format(string, sizeof string, "{FF2F2F}[AdmWarning]{FFFFFF} Presidente %s(%d) retiro $%s de los fondos del gobierno, razón: %s.", GetNameFormat(playerid), playerid, diner_coma(amount), reason);
	SendAdminMessage(0xFFFFFFFF, string);
	Log("f_logs/especial.log", string);
	return 1;
}
alias:sfondos("sacarfondos");

cmd:dfondos(playerid, params[])
{
	if (!Propietario_faccion(playerid, 5)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres líder del Gobierno.");
	new string[180], amount;
	if (sscanf(params, "d", amount))
	{
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /dejarfondos (monto)");
		format(string, sizeof string, "* BALANCE: $%s.", diner_coma(Tax));
		SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
		return 1;
	}
	if (amount < 0) return SendPlayerChatMessage(playerid, COLOR_WHITE, "El monto es inválido.");
	if (GetPlayerCash(playerid) < amount) return SendPlayerChatMessage(playerid, COLOR_WHITE, "No dispones de ese dinero.");
	Tax += amount;
	GivePlayerCash(playerid, -amount, "dfondos");
	format(string, sizeof string, "Depositaste $%s en los fondos del Gobierno.", diner_coma(amount));
	SendPlayerChatMessage(playerid, COLOR_WHITE, string);
	return 1;
}
alias:dfondos("dejarfondos");

cmd:arrestar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (!IsPlayerInRangeOfPoint(playerid, 7.0, -807.5030, -1755.6345, 46.5406)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el punto de entrega.");
	new string[180], playerid2, time;
	if (sscanf(params, "dd", playerid2, time)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /arrestar (JugadorID) (Minutos)");
	if (time < 10 || time > 300) { SendPlayerChatMessage(playerid, COLOR_GREY, "Tiempo: 10 a 300 minutos."); return 1; }
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está conectado.");
	if (playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes arrestarte a ti mismo.");
	if (!CercaDelMarica(5.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador no está cerca tuyo.");
	if (InfoPersonaje[playerid2][pEstrellas] < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "El sospechoso debe tener un nivel de búsqueda de al menos una estrella.");
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
	format(string, sizeof string, "[CENTRAL] %s fue arrestado por %s, %d minutos. (%s)", GetNameFormat(playerid2), GetNameFormat(playerid), time, InfoFaccion[InfoPersonaje[playerid][pMiembro]][fLogo]);
	SendRadioMessage(1, COLOR_RADIO, string, 1);
	SendRadioMessage(2, COLOR_RADIO, string, 1);
	SendRadioMessage(4, COLOR_RADIO, string, 1);
	SendRadioMessage(7, COLOR_RADIO, string, 1);
	InfoPersonaje[playerid2][pTiempoSancion] = time * 60;
	DeletePVar(playerid2, "IsFrozen");
	new rand = random(sizeof PrisonSpawns);
	SetPosEx(playerid2, PrisonSpawns[rand][0], PrisonSpawns[rand][1], PrisonSpawns[rand][2], 0.0000, 60, 60, 1);
	InfoPersonaje[playerid2][pSancionado] = 2;
	InfoPersonaje[playerid2][pTogTelefono] = 0;
	InfoPersonaje[playerid2][pArrestos] += 1;
	InfoPersonaje[playerid2][pEstrellas] = 0;
	SetPlayerWantedLevel(playerid2, 0);
	ClearAnimations(playerid2);
	RemovePlayerAttachedObject(playerid2, 0);
	SetPlayerSpecialAction(playerid2, SPECIAL_ACTION_NONE);
	DeletePVar(playerid2, "PlayerCuffed");
	QuitarBolsillos(playerid2);
	QuitarManos(playerid2);
	QuitarEspalda(playerid2);
	new query[410];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Estrellas = 0, Sancionado = 2, TiempoSancion = '%d', Arrestos = '%d' WHERE ID = '%d'",InfoPersonaje[playerid2][pTiempoSancion], InfoPersonaje[playerid2][pArrestos], InfoPersonaje[playerid2][pID]);
	mysql_tquery(db_samp, query);
	SendClientMessageEx(playerid2, COLOR_LIGHTBLUE, "Fuiste encarcelado %d minutos. (Puedes verificar el tiempo restante en /cuenta)", time);
	return 1;
}

cmd:saludar(playerid, params[])
{
	new string[128], playerid2, style;
	if(sscanf(params, "dd", playerid2, style)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /saludar (playerid) (estilo (1-8))");

	if(IsPlayerConnected(playerid2))
	{
		if(playerid2 == playerid)
		{
			SendPlayerChatMessage(playerid, COLOR_WHITE, "No puedes hacer eso tu mismo.");
			return 1;
		}
		if(style >= 1 && style < 9)
		{
			new Float: ppFloats[3];
			GetPlayerPos(playerid2, ppFloats[0], ppFloats[1], ppFloats[2]);
			if(!IsPlayerInRangeOfPoint(playerid, 5, ppFloats[0], ppFloats[1], ppFloats[2]))
			{
				SendPlayerChatMessage(playerid, COLOR_WHITE, "Estás demasiado lejos de la persona.");
				return 1;
			}
			SetPVarInt(playerid, "shrequest", playerid2);
			SetPVarInt(playerid, "shstyle", style);

			format(string, sizeof string, "Saludaste a %s, espera que el responda.", GetNameFormat(playerid2));
			SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);

			format(string, sizeof string, "%s te ha saludado, porfavor usa '/aceptar saludo' para darle la mano.", GetNameFormat(playerid));
			SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
		}
		else return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /saludar (playerid) (estilo (1-8))");
	}
	else SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador desconectado.");
	return 1;
}

cmd:limpiar(playerid, params[])
{
	new string[128], playerid2;
	if (!member_faccion(playerid, 1, 2, 4, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /limpiar (playerid)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	format(string, sizeof string, "* Limpiaste el nivel de búsqueda %s.", GetNameFormat(playerid2));
	SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "* Agente %s a limpiado tu nivel de búsqueda.", GetNameFormat(playerid));
	SendPlayerChatMessage(playerid2, COLOR_LIGHTBLUE, string);
	format(string, sizeof string, "[CENTRAL] %s a limpiado el nivel de búsqueda de %s.", GetNameFormat(playerid), GetNameFormat(playerid2));
	SendRadioMessage(InfoPersonaje[playerid][pMiembro], COLOR_RADIO, string, 1);
	InfoPersonaje[playerid2][pEstrellas] = 0;
	guardar_int_mysql("personajes", "Estrellas", InfoPersonaje[playerid2][pID], InfoPersonaje[playerid2][pEstrellas]);
	SetPlayerWantedLevel(playerid2, 0);
	return 1;
}

cmd:darvest(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[128], playerid2, slot, invoice[64];
	if (sscanf(params, "dds[64]", playerid2, slot, invoice)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /darvest (playerid) (slot(0-6)) (invoice #)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	if (slot < 0 || slot > 6) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Slot 0 al 6.");

	InfoPersonaje[playerid2][ptModelo][slot] = 19142;
	InfoPersonaje[playerid2][ptHueso][slot] = 1;
	InfoPersonaje[playerid2][ptPosX][slot] = 0.07998;
	InfoPersonaje[playerid2][ptPosY][slot] = 0.03999;
	InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	ActualizarToy(playerid2, slot);
	format(string, sizeof string, "Police Vest en el slot %d, usa /toys para editar la posición.", slot);
	SendPlayerChatMessage(playerid2, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "Diste a %s un police vest en el slot %d", GetNameFormat(playerid2), slot);
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "[SHOPVEST] %s has given %s a police vest toy - Invoice %s", NombreDeCuenta(playerid), NombreDeCuenta(playerid2), invoice);
	Log("f_logs/shoplog.log", string);
	return 1;
}

cmd:darvest2(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new string[128], playerid2, slot, invoice[64];
	if (sscanf(params, "dds[64]", playerid2, slot, invoice)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /darvest (playerid) (slot(0-6)) (invoice #)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
	if (slot < 0 || slot > 6) return SendPlayerChatMessage(playerid, 0xFF6347AA, "Slot 0 al 6.");

	InfoPersonaje[playerid2][ptModelo][slot] = 19515;
	InfoPersonaje[playerid2][ptHueso][slot] = 1;
	InfoPersonaje[playerid2][ptPosX][slot] = 0.07998;
	InfoPersonaje[playerid2][ptPosY][slot] = 0.03999;
	InfoPersonaje[playerid2][ptPosZ][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotX][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotY][slot] = 0.0;
	InfoPersonaje[playerid2][ptRotZ][slot] = 0.0;
	ActualizarToy(playerid2, slot);
	format(string, sizeof string, "Police Vest en el slot %d, usa /toys para editar la posición.", slot);
	SendPlayerChatMessage(playerid2, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "Diste a %s un police vest en el slot %d", GetNameFormat(playerid2), slot);
	SendPlayerChatMessage(playerid, COLOR_LIGHTGREEN, string);
	format(string, sizeof string, "[SHOPVEST] %s has given %s a police vest toy - Invoice %s", NombreDeCuenta(playerid), NombreDeCuenta(playerid2), invoice);
	Log("f_logs/shoplog.log", string);
	return 1;
}

cmd:servicio(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 5, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
	if (OnDuty[playerid] == 0)
	{
		OnDuty[playerid] = 1;
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Ahora estas en servicio.");
	}
	else
	{
		OnDuty[playerid] = 0;
		SendPlayerChatMessage(playerid, COLOR_WHITE, "Ahora ya no estas en servicio.");
	}
	return 1;
}
alias:servicio("duty", "enservicio");

cmd:placa(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4, 5, 6, 7)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley.");
	new id = InfoPersonaje[playerid][pMiembro];
	new string[180], playerid2, rango = InfoPersonaje[playerid][pRango]-1;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /placa (playerid)");
	if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Jugador no conectado.");
	if (!CercaDelMarica(5.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Muy lejos de el jugador.");
	SendPlayerChatMessage(playerid2, COLOR_GRAD2, "----------------------------------------------------------------------------------------------------");
	format(string, sizeof string, "%s miembro de {3E62F4}%s", GetNameFormat(playerid), InfoFaccion[id][fLogo]);
	SendPlayerChatMessage(playerid2, COLOR_WHITE, string);
	format(string, sizeof string, "Asignación actual: {3E62F4}%s", fac_rango[id][rango]);
	SendPlayerChatMessage(playerid2, COLOR_WHITE, string);
	if (member_faccion(playerid, 1, 2, 3, 4)) SendPlayerChatMessage(playerid2, COLOR_RED, "Tiene autoridad para arrestar.");
	SendPlayerChatMessage(playerid2, COLOR_GRAD2, "----------------------------------------------------------------------------------------------------");
	format(string, sizeof string, "muesta su placa a %s.", GetNameFormat(playerid2));
	rol_ame(playerid, string);
	return 1;
}

cmd:revisar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4))
	{
		if (InfoPersonaje[playerid][pHorasOn] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes jugar al menos dos horas el servidor para revisar a otros.");
	}
	new playerid2, dialog[1024], dialog2[256], count = 0;
	if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Utiliza: /revisar (playerid)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador especificado no válido.");
	if (!CercaDelMarica(8.0, playerid, playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Ese jugador no está cerca tuyo.");
	if (!member_faccion(playerid, 1, 2, 3, 4))
	{
		if (EstaParaArrastrar(playerid2) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Ese jugador debe estar en estado de herido/muerto/rendido/esposado.");
	}
	if (playerid2 == playerid) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No te puedes revisar a ti mismo.");
	//indice
	Loop(x, 9, 0)
	{
		if (InfoPersonaje[playerid2][pBolsillo][x] != 0)
		{
			format(dialog2, sizeof dialog2, "{FFFFFF}%s\n", slot_objeto(InfoPersonaje[playerid2][pBolsillo][x], InfoPersonaje[playerid2][pBolsilloCant][x])), count++;
			strcat(dialog, dialog2);
		}
	}
	//barra espacio
	if (count != 0) strcat(dialog, "{b42d2d}--------------------\n");
	//mano derecha
	if (InfoPersonaje[playerid2][pManoDerecha] != 0)
	{
		format(dialog2, sizeof dialog2, "{FFFFFF}Mano derecha: %s\n", slot_objeto(InfoPersonaje[playerid2][pManoDerecha], InfoPersonaje[playerid2][pManoDerechaCant])), count++;
		strcat(dialog, dialog2);
	}
	//mano izquierda
	if (InfoPersonaje[playerid2][pManoIzquierda] != 0)
	{
		format(dialog2, sizeof dialog2, "{FFFFFF}Mano izquierda: %s\n", slot_objeto(InfoPersonaje[playerid2][pManoIzquierda], InfoPersonaje[playerid2][pManoIzquierdaCant])), count++;
		strcat(dialog, dialog2);
	}
	//espalda
	if (InfoPersonaje[playerid2][pEspalda] != 0)
	{
		format(dialog2, sizeof dialog2, "{FE9A2E}%s:{FFFFFF} %s\n", GetParteToy(playerid2, 7), slot_objeto(InfoPersonaje[playerid2][pEspalda], InfoPersonaje[playerid2][pEspaldaCant])), count++;
		strcat(dialog, dialog2);
	}
	//dinero
	if (GetPlayerCash(playerid2) != 0)
	{
		format(dialog2, sizeof dialog2, "Dinero en bolsillos {00CC00}$%s\n", diner_coma(GetPlayerCash(playerid2))), count++;
		strcat(dialog, dialog2);
	}
	//show_dialog
	format(dialog2, sizeof dialog2, "revisa a %s.", GetNameFormat(playerid2));
	rol_ame(playerid, dialog2);
	format(dialog2, sizeof dialog2, "{CCCCCC}Inventario de {FE9A2E}%s", GetNameFormat(playerid2));
	if (count == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, dialog2, "{CCCCCC}No tiene nada", "Cerrar", "");
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, dialog2, dialog, "Cerrar", "");
	return 1;
}

cmd:qfa(playerid, params[])
{
	new playerid2, string[73];
	if (!sscanf(params, "u", playerid2))
	{
		if (CheckAdminCMD(playerid, 1)) return 1;
		if (CheckAdminDuty(playerid)) return 1;
		if (!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid,COLOR_YELLOW,"El jugador no esta conectado.");
		format(string,sizeof string, "%s fue asesinado por %s.", GetNameFormat(playerid2), QFA[playerid2]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	}
	else
	{
		if (player_asesino[playerid] == -1) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Nadie te ha asesinado, posible error.");
		format(string,sizeof string, "Fuiste asesinado por %s.", QFA[playerid]);
		SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		if (GetPlayerAdmin(playerid, 1) != 0) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /qfa (PlayerID)");
	}
	return 1;
}

GetNameVIP(nivel)
{
	new name_vip[19];
	switch (nivel)
	{
		case 0: alm(name_vip, "Ninguno");
		case 1: alm(name_vip, "Level 1");
		case 2: alm(name_vip, "Level 2");
		default: alm(name_vip, "desconocido");
	}
	return name_vip;
}

cmd:cambiarclaveusuario(playerid)
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	Dialog_Show(playerid, CambiarClave, DIALOG_STYLE_INPUT, "Cambiar contraseña", "{EBEBEB}Ingresa el '{FE9A2E}Nombre de usuario{EBEBEB}' de la cuenta que deseas cambiarle la contraseña:", "Continuar", "Salir");
	return 1;
}

new IsChangeName[MAX_PLAYERS][32];
Dialog:CambiarClave(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	if (VerificarCuenta(inputtext) == 0) return SendPlayerChatMessage(playerid, -1, "Esa cuenta no existe.");
	alm(IsChangeName[playerid], inputtext);
	new gformat[256];
	format(gformat, sizeof gformat, "{FFFFFF}Ahora introduce la contraseña que tendrá %s.", inputtext);
	Dialog_Show(playerid, Cambiar2Clave, DIALOG_STYLE_INPUT, "Cambiar contraseña", gformat, "Continuar", "Salir");
	return 1;
}

Dialog:Cambiar2Clave(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
	new gformat[256];
	if (strlen(inputtext) < 4)
	{
		SendPlayerChatMessage(playerid, -1, "Contraseña muy corta, debe contener más de 4 caracteres y menos de 25");
		format(gformat, sizeof gformat, "Ahora introduce la contraseña que tendrá la cuenta %s.", IsChangeName[playerid]);
		Dialog_Show(playerid, Cambiar2Clave, DIALOG_STYLE_INPUT, "Cambiar contraseña", gformat, "Continuar", "Cancelar");
		return 1;
	}
	if (strlen(inputtext) > 25)
	{
		SendPlayerChatMessage(playerid, -1, "Contraseña muy larga, debe contener más de 4 caracteres y menos de 25");
		format(gformat, sizeof gformat, "Ahora introduce la contraseña que tendrá la cuenta %s.", IsChangeName[playerid]);
		Dialog_Show(playerid, Cambiar2Clave, DIALOG_STYLE_INPUT, "Cambiar contraseña", gformat, "Continuar", "Cancelar");
		return 1;
	}
	new exSalt[11];
	new exClave[65];
	for (new i = 0; i < 10; i++)
	{
		exSalt[i] = random(79) + 47;
	}
	exSalt[10] = 0;
	SHA256_PassHash(inputtext, exSalt, exClave, 65);
	new query[512];
	mysql_format(db_samp, query, sizeof query, "UPDATE cuentas SET Clave = '%e', Salt = '%e' WHERE Nombre = '%e'", exClave, exSalt, IsChangeName[playerid]);
	mysql_tquery(db_samp, query);
	format(query, sizeof query, "Le has cambiado la contraseña a %s, (clave: %s)", IsChangeName[playerid], inputtext);
	SendPlayerChatMessage(playerid, 0x008800FF, query);
	format(query, sizeof query, "ADMIN: %s cambió la contraseña de %s.", NombreDeCuenta(playerid), IsChangeName[playerid]);
	Log("f_logs/password.log", query);
	alm(IsChangeName[playerid], "none");
	return 1;
}

cmd:dudas(playerid)
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new string[320];
	SendPlayerChatMessage(playerid, COLOR_GREEN, "DUDAS:");
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		if (PlayerDuda[playerid2] != 0)
		{
			format(string, sizeof string, "{00A2FF}%s (ID: %d):{FFFFFF} %s", GetNameFormat(playerid2), playerid2, PlayerTextoDuda[playerid2]);
			if (strlen(string) > 0) SendSplitMessage(playerid, 0xFFFFFFFF, string);
		}
	}
	return 1;
}

cmd:aduda(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new string[320], playerid2, respuesta[256];
	if (sscanf(params, "ds[200]", playerid2, respuesta)) return SendPlayerChatMessage(playerid, -1, "Utiliza: /aduda (PlayerID) (Respuesta)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, 0xFF0000FF, "Jugador no conectado.");
	if (PlayerDuda[playerid2] == 0) return SendPlayerChatMessage(playerid, 0xFF0000FF, "Este jugador no tiene una duda.");

	format(string, sizeof string, "{2F99B5}%s{EBEBEB} te responde: %s.", GetNameFormat(playerid), respuesta);
	SendSplitMessage(playerid2, 0xEBEBEBFF, string);

	format(string, sizeof string, "Respondes a %s (%d): %s", GetNameFormat(playerid2), playerid2, respuesta);
	SendSplitMessage(playerid, 0x96964BFF, string);

	PlayerDuda[playerid2] = 0;
	alm(PlayerTextoDuda[playerid2], "nada");

	format(string, sizeof string, "{9EC73D}%s{FFFFFF} ha aceptado la duda de %s(%d).", InfoCuenta[playerid][jNombre], GetNameFormat(playerid2), playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	return 1;
}
alias:aduda("ad");

cmd:rduda(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	new id, string[185];
	if (sscanf(params, "u", id)) return SendPlayerChatMessage(playerid, -1, "Utiliza: /rduda (PlayerID)");
	if (!IsPlayerConnectedEx(id)) return SendPlayerChatMessage(playerid, 0xFF0000FF, "Jugador no conectado.");
	if (PlayerDuda[id] == 0) return SendPlayerChatMessage(playerid, 0xFF0000FF, "Este jugador no tiene una duda.");

	format(string, sizeof string, "{2F99B5}%s{FFFFFF} ha {FF0000}rechazado{FFFFFF} su duda.",GetNameFormat(playerid));
	SendPlayerChatMessage(id, -1, string);
	format(string, sizeof string, "Le recomendamos que use el comando /soporte, posiblemente la respuesta de su pregunta esté ahí.");
	SendPlayerChatMessage(id, -1, string);

	format(string, sizeof string, "{2F99B5}%s{FFFFFF} ha rechazado la duda de %s(%d).", InfoCuenta[playerid][jNombre], GetNameFormat(id), id);
	SendAdminMessage(0xFFFFFFFF, string);
	PlayerDuda[id] = 0;
	alm(PlayerTextoDuda[id], "nada");
	return 1;
}
alias:rduda("rd");

cmd:showsound(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	new sound;
    if (sscanf(params, "d", sound)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /showsound (ID)");
    PlayerPlaySound(playerid, sound, 0,0,0);
    return 1;
}

cmd:banearpj(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new string[250], playerid2, reason[64], query3[1028];
	if (!CheckTimer(60, TimerCban[playerid]))
	{
		if (sscanf(params, "ds[64]", playerid2, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /banearpj (PlayerID) (Razón)");
		if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa ID es inválida.");
		format(string, sizeof string, "ADMIN: %s bloqueó el personaje %s, razón: %s", InfoCuenta[playerid][jNombre], InfoCuenta[playerid2][jNombre], reason);
		Log("f_logs/ban.log", string);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) bloqueó el personaje %s(%d). Razón: %s", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2, reason);
		SendAllMessage(0xFFFFFFFF, string);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE personajes SET OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", InfoCuenta[playerid][jNombre], reason, FechaHoy(), InfoPersonaje[playerid2][pID]);
		mysql_tquery(db_samp, query3);
		SetTimerEx("TimerKICK",500, false, "d", playerid2);
		//seguridad 24/02/2020
		CountBan[playerid]++;
		if (CountBan[playerid] == 5)
		{
			TimerCban[playerid] = gettime();
			CountBan[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, TimerCban[playerid]) ));
	}
	return 1;
}
alias:banearpj("bloquearpj", "banpj");

cmd:banip(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	if (!CheckTimer(60, TimerCban[playerid]))
	{
		new string[320], playerid2, reason[64], query3[1028];
		if (sscanf(params, "ds[64]", playerid2, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /banip (PlayerID) (Razón)");
		if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa ID es inválida.");
		if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes kickear a ningún Propietario.");
		if(GetPlayerAdmin(playerid, 10) == 0)
		{
			if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
			{
				format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
				SendAdminMessage(0xFFFFFFFF, string);
				return 1;
			}
		}
		if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) baneó con IP a %s(%d) (Cuenta: %s). Razón: %s", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2, InfoCuenta[playerid2][jNombre], reason);
		SendAdminMessage(0xFFFFFFFF, string);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE cuentas SET JotoOtaku = 0, EncFac = 0, EncMap = 0, OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", InfoCuenta[playerid][jNombre], reason, FechaHoy(), InfoCuenta[playerid2][jID]);
		mysql_tquery(db_samp, query3);
		//register ban ip
		new playerip[18];
		GetPlayerIp(playerid2, playerip, sizeof playerip);
		AddBan(playerip, InfoCuenta[playerid][jNombre], reason);
		SetTimerEx("TimerKICK", 500, false, "d", playerid2);
		//seguridad 24/02/2020
		CountBan[playerid]++;
		if (CountBan[playerid] == 5)
		{
			TimerCban[playerid] = gettime();
			CountBan[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, TimerCban[playerid]) ));
	}
	return 1;
}
alias:banip("banearip");

cmd:obanearcuenta(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new string[1028], playername[MAX_PLAYER_NAME], reason[64];
	if (sscanf(params, "s[24]s[64]", playername, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /obanearcuenta (Nombre de  usuario) (Razón)");
	if (VerificarCuenta(playername))
	{
		new banex;
		rebel_int(0, "OtakuN_N", banex);
		if (banex != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta ya está bloqueada.");
		mysql_format(db_samp, string, sizeof string, "UPDATE cuentas SET OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE Nombre = '%e'", InfoCuenta[playerid][jNombre], reason, FechaHoy(), playername);
		mysql_tquery(db_samp, string);
		format(string, sizeof string, "%s bloqueó la cuenta %s, razón: %s", NombreDeCuenta(playerid), playername, reason);
		Log("f_logs/offban.log", string);
		format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) bloqueó la cuenta %s, razón: %s (OFFLINE)", InfoCuenta[playerid][jNombre], playerid, playername, reason);
		SendAdminMessage(0xFFFFFFFF, string);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta no existe.");
	return 1;
}
alias:obanearcuenta("obloquearcuenta");

cmd:banearcuenta(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new string[250], playerid2, reason[64], query3[1028];
	if (!CheckTimer(60, TimerCban[playerid]))
	{
		if (sscanf(params, "ds[64]", playerid2, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /banearcuenta (PlayerID) (Razón)");
		if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa ID es inválida.");
		if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes bloquear a ningún Propietario.");
		if(GetPlayerAdmin(playerid, 10) == 0)
		{
			if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
			{
				format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
				SendAdminMessage(0xFFFFFFFF, string);
				return 1;
			}
		}
		if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

		format(string, sizeof string, "ADMIN: %s bloqueó la cuenta %s, razón: %s", InfoCuenta[playerid][jNombre], InfoCuenta[playerid2][jNombre], reason);
		Log("f_logs/ban.log", string);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) bloqueó la cuenta (%s) de %s(%d). Razón: %s", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], GetNameFormat(playerid2), playerid2, reason);
		SendAdminMessage(0xFFFFFFFF, string);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE cuentas SET OtakuN_N = 2, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", InfoCuenta[playerid][jNombre], reason, FechaHoy(), InfoCuenta[playerid2][jID]);
		mysql_tquery(db_samp, query3);
		SetTimerEx("TimerKICK",500, false, "d", playerid2);
		//seguridad 24/02/2020
		CountBan[playerid]++;
		if (CountBan[playerid] == 5)
		{
			TimerCban[playerid] = gettime();
			CountBan[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(180, TimerCban[playerid]) ));
	}
	return 1;
}
alias:banearcuenta("bloquearcuenta", "bancuenta");

cmd:tbanpj(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new playerid2, razon[190], minutos, query3[1028], string[512];
	if (sscanf(params, "iis[128]", playerid2, minutos, razon)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /tbanpj (JugadorID) (Minutos) (Razón)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes bloquear a ningún Propietario.");
	if(GetPlayerAdmin(playerid, 10) == 0)
	{
		if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
		{
			format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
			SendAdminMessage(0xFFFFFFFF, string);
			return 1;
		}
	}
	if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

	if (minutos < 1 || minutos > 2880) { SendPlayerChatMessage(playerid, COLOR_GREY, "El tiempo mínimo es de 1 minuto y el máximo 2880 (48 hs)"); return 1; }
	format(string, sizeof string, "ADMIN: %s fue expulsado %d minutos por %s, razón: %s", GetNameFormat(playerid2), minutos, GetNameFormat(playerid), razon);
	Log("f_logs/ban.log", string);
	format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) fue expulsado %d minutos por %s(%d). Razón: %s", GetNameFormat(playerid2), playerid2, minutos, InfoCuenta[playerid][jNombre], playerid, razon);
	SendAllMessage(0xFFFFFFFF, string);
	new k = gettime(), elpru[30];
	alm(elpru, "0");
	minutos *= 60;
	k += minutos;
	format(elpru, sizeof(elpru), "%d", k);
	mysql_format(db_samp, query3, sizeof query3, "UPDATE personajes SET OtakuN_N = 1, TimeBanUwU = '%e', MomentBan = '%e', ReasonBanUwU = '%e', FueBan = '%e' WHERE ID = '%d'", elpru, FechaHoy(), razon, InfoCuenta[playerid][jNombre], InfoPersonaje[playerid2][pID]);
	mysql_tquery(db_samp, query3);
	SetTimerEx("TimerKICK", 1500, false, "d", playerid2);
	return 1;
}

cmd:tbancuenta(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new playerid2, razon[190], minutos, query3[1028], string[512];
	if (sscanf(params, "iis[128]", playerid2, minutos, razon)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /tbancuenta (JugadorID) (Minutos) (Razón)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "El jugador seleccionado no se encuentra conectado.");
	if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes bloquear a ningún Propietario.");
	if(GetPlayerAdmin(playerid, 10) == 0)
	{
		if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
		{
			format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
			SendAdminMessage(0xFFFFFFFF, string);
			return 1;
		}
	}
	if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

	if (minutos < 1 || minutos > 2880) { SendPlayerChatMessage(playerid, COLOR_GREY, "El tiempo mínimo es de 1 minuto y el máximo 2880 (48 hs)"); return 1; }

	format(string, sizeof string, "ADMIN: %s (cuenta: %s) fue expulsado %d minutos por %s, razón: %s", GetNameFormat(playerid2), InfoCuenta[playerid2][jNombre], minutos, GetNameFormat(playerid), razon);
	Log("f_logs/ban.log", string);
	format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) (cuenta: %s) fue expulsado %d minutos por %s(%d). Razón: %s", GetNameFormat(playerid2), playerid2, InfoCuenta[playerid2][jNombre], minutos, InfoCuenta[playerid][jNombre], playerid, razon);
	SendAdminMessage(0xFFFFFFFF, string);
	new k = gettime(), elpru[30];
	alm(elpru, "0");
	minutos *= 60;
	k += minutos;
	format(elpru, sizeof(elpru), "%d", k);
	mysql_format(db_samp, query3, sizeof query3, "UPDATE cuentas SET OtakuN_N = 1, TimeBanUwU = '%e', MomentBan = '%e', ReasonBanUwU = '%e', FueBan = '%e' WHERE ID = '%d'", elpru, FechaHoy(), razon, InfoCuenta[playerid][jNombre], InfoCuenta[playerid2][jID]);
	mysql_tquery(db_samp, query3);
	SetTimerEx("TimerKICK", 1500, false, "d", playerid2);
	return 1;
}

cmd:otbanpj(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new playerid2, tiempo, razon[128], nombrexdd[50], string[512];
	if (sscanf(params, "s[24]ds[128]", nombrexdd, tiempo, razon)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /otbanpj (Nombre_Apellido) (Minutos) (Razón)");
	if (sscanf(params, "uds[128]", playerid2, tiempo, razon)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Hubo un problema, utiliza de nuevo el comando.");
	if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes bloquear a ningún Propietario.");
	if (IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está conectado, utiliza /otbanpj.");
	if (tiempo < 1 || tiempo > 2880) { SendPlayerChatMessage(playerid, COLOR_GREY, "El tiempo mínimo es de 1 minuto y el máximo 2880 (48 hs)"); return 1; }
	if (VerificarPersonaje(nombrexdd))
	{
	    new banex, query3[1028];
		rebel_int(0, "OtakuN_N", banex);
		if (banex != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese personaje ya está bloqueado.");
		format(string, sizeof string, "ADMIN: %s fue expulsado %d minutos por %s, razón: %s (OFFLINE)", nombrexdd, tiempo, GetNameFormat(playerid), razon);
		Log("f_logs/ban.log", string);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s fue expulsado %d minutos por %s(%d). Razón: %s (OFFLINE)", nombrexdd, tiempo, InfoCuenta[playerid][jNombre], playerid, razon);
		SendAllMessage(0xFFFFFFFF, string);
		new k = gettime(), elpru[30];
		tiempo *= 60;
		k += tiempo;
		format(elpru, sizeof(elpru), "%d", k);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE personajes SET OtakuN_N = 1, TimeBanUwU = '%e', MomentBan = '%e', ReasonBanUwU = '%e', FueBan = '%e' WHERE Nombre_Apellido = '%e'", elpru, FechaHoy(), razon, InfoCuenta[playerid][jNombre], nombrexdd);
		mysql_tquery(db_samp, query3);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Ese personaje no existe.");
	return 1;
}

cmd:otbancuenta(playerid, params[])
{
	if (CheckAdminCMD(playerid, 2)) return 1;
	new playerid2, tiempo, razon[128], nombrexdd[50], string[512];
	if (sscanf(params, "s[24]ds[128]", nombrexdd, tiempo, razon)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /otbancuenta (Nombre de usuario) (Minutos) (Razón)");
	if (sscanf(params, "uds[128]", playerid2, tiempo, razon)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Hubo un problema, utiliza de nuevo el comando.");
	if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes bloquear a ningún Propietario.");
	if (IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Ese jugador está conectado, utiliza /otbanpj.");
	if (tiempo < 1 || tiempo > 2880) { SendPlayerChatMessage(playerid, COLOR_GREY, "El tiempo mínimo es de 1 minuto y el máximo 2880 (48 hs)"); return 1; }
	if (VerificarCuenta(nombrexdd))
	{
	    new ex_ban, query3[1028];
		rebel_int(0, "OtakuN_N", ex_ban);
		if (ex_ban != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta ya está bloqueada.");
		format(string, sizeof string, "ADMIN: La cuenta %s fue expulsada %d minutos por %s, razón: %s (OFFLINE)", nombrexdd, tiempo, GetNameFormat(playerid), razon);
		Log("f_logs/ban.log", string);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} La cuenta %s fue expulsada %d minutos por %s(%d). Razón: %s (OFFLINE)", nombrexdd, tiempo, InfoCuenta[playerid][jNombre], playerid, razon);
		SendAdminMessage(0xFFFFFFFF, string);
		new k = gettime(), elpru[30];
		tiempo *= 60;
		k += tiempo;
		format(elpru, sizeof(elpru), "%d", k);
		mysql_format(db_samp, query3, sizeof query3, "UPDATE cuentas SET OtakuN_N = 1, TimeBanUwU = '%e', MomentBan = '%e', ReasonBanUwU = '%e', FueBan = '%e' WHERE Nombre = '%e'", elpru, FechaHoy(), razon, InfoCuenta[playerid][jNombre], nombrexdd);
		mysql_tquery(db_samp, query3);
		return 1;
	}
	SendPlayerChatMessage(playerid, COLOR_GREY, "Esa cuenta no existe.");
	return 1;
}

cmd:kick(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (!CheckTimer(60, TimerCkick[playerid]))
	{
		new string[190], playerid2, reason[64];
		if(sscanf(params, "ds[64]", playerid2, reason)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /kick (PlayerID) (Razón)");
		if(!IsPlayerConnected(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
		if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes kickear a ningún Propietario.");
		if(GetPlayerAdmin(playerid, 10) == 0)
		{
			if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
			{
				format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
				SendAdminMessage(0xFFFFFFFF, string);
				return 1;
			}
		}
		if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

		format(string, sizeof string, "%s fue expulsado por %s. Razón: %s", NombreDeCuenta(playerid2), NombreDeCuenta(playerid), reason);
		Log("f_logs/kick.log", string);
		format(string, sizeof string, "{FF6347}Administración:{FFFFFF} %s(%d) expulsó del servidor a %s(%d). Razón: %s", InfoCuenta[playerid][jNombre], playerid, GetNameFormat(playerid2), playerid2, reason);
		SendAllMessage(0xFFFFFFFF, string);
		SetTimerEx("TimerKICK",500,false,"d",playerid2);
		//seguridad 24/02/2020
		CountKick[playerid]++;
		if (CountKick[playerid] == 5)
		{
			TimerCkick[playerid] = gettime();
			CountKick[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(60, TimerCkick[playerid]) ));
	}
	return 1;
}

cmd:kickname(playerid, params[])
{
	if (CheckAdminCMD(playerid, 1)) return 1;
	if (CheckAdminDuty(playerid)) return 1;
	if (!CheckTimer(60, TimerCkick[playerid]))
	{
		new string[180], playerid2;
		if (sscanf(params, "d", playerid2)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /kickname (PlayerID)");
		if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Esa ID es inválida.");
		if(SoloPropietarios(playerid2)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No puedes kickear a ningún Propietario.");
		if(GetPlayerAdmin(playerid, 10) == 0)
		{
			if (InfoCuenta[playerid2][jAdmin] > InfoCuenta[playerid][jAdmin])
			{
				format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) intentó kickear a %s(%d) superior a él.", InfoCuenta[playerid][jNombre], playerid, InfoCuenta[playerid2][jNombre], playerid2);
				SendAdminMessage(0xFFFFFFFF, string);
				return 1;
			}
		}
		if(playerid == playerid2) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "No te puedes kickear a ti mismo.");

		format(string, sizeof string, "%s fue expulsado por %s. Razón: Nombre inapropiado", NombreDeCuenta(playerid2), NombreDeCuenta(playerid));
		Log("f_logs/kick.log", string);
		SendPlayerChatMessage(playerid2, COLOR_GREEN,"Has sido expulsado por el servidor ya que tu cuenta no cumple las normas de la comunidad.");
		SendPlayerChatMessage(playerid2, COLOR_WHITE,"No se permite nombre de famosos, nicks trolls, inadecuados, que no son Role Play o que falten el respeto.");
		SendPlayerChatMessage(playerid2, COLOR_WHITE,"Recuerda poner las iniciales en mayúscula usado un nombre real, formato Nombre_Apellido.");
		format(string, sizeof string, "{FF2F2F}[AdmWarnig]{FFFFFF} %s(%d) fue expulsado del servidor por %s(%d). Razón: Nombre inapropiado", GetNameFormat(playerid2), playerid2, InfoCuenta[playerid][jNombre], playerid);
		SendAdminMessage(0xFFFFFFFF, string);
		SetTimerEx("TimerKICK",500,false,"d",playerid2);
		//seguridad 24/02/2020
		CountKick[playerid]++;
		if (CountKick[playerid] == 5)
		{
			TimerCkick[playerid] = gettime();
			CountKick[playerid] = 0;
		}
	}
	else
	{
		SendClientMessageEx(playerid, COLOR_GREY, "Puedes volver a usar este comando en %s.", Segundos_tiempo( CheckTimer(60, TimerCkick[playerid]) ));
	}
	return 1;
}

cmd:forzarpayday(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new string[180], count = 0;
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) adelantó el PayDay.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		FakePayday[playerid2] = 1;
		SetPlayerPayDay(playerid2);
		count++;
	}
	format(string, sizeof string, "El payday fue cedido a %d jugadores conectados.", count);
	SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
	return 1;
}

cmd:forzarpayday2(playerid, params[])
{
	if (CheckAdminCMD(playerid, 4)) return 1;
	new string[180];
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) adelantó el PayDay de negocios.", InfoCuenta[playerid][jNombre], playerid);
	SendAdminMessage(0xFFFFFFFF, string);
	PayDay2();
	return 1;
}

cmd:darmonedas(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new playerid2, monedas, string[256];
	if (sscanf(params, "dd", playerid2, monedas)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /darmonedas (PlayerID) (Cantidad)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador no conectado.");
	InfoCuenta[playerid2][jMonedas] += monedas;
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) dió %d monedas a %s(%d).", InfoCuenta[playerid][jNombre], playerid, monedas, InfoCuenta[playerid2][jNombre], playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	guardar_int_mysql("cuentas", "CoinsVIP", InfoCuenta[playerid2][jID], InfoCuenta[playerid2][jMonedas]);
	return 1;
}

cmd:quitarmonedas(playerid, params[])
{
	if (CheckAdminCMD(playerid, 10)) return 1;
	new playerid2, monedas, string[256];
	if (sscanf(params, "dd", playerid2, monedas)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /quitarmonedas (PlayerID) (Cantidad)");
	if (!IsPlayerConnectedEx(playerid2)) return SendPlayerChatMessage(playerid, COLOR_WHITE, "Jugador no conectado.");
	InfoCuenta[playerid2][jMonedas] -= monedas;
	format(string, sizeof string, "{FF2F2F}[ADMIN]{FFFFFF} %s(%d) quitó %d monedas a %s(%d).", InfoCuenta[playerid][jNombre], playerid, monedas, InfoCuenta[playerid2][jNombre], playerid2);
	SendAdminMessage(0xFFFFFFFF, string);
	guardar_int_mysql("cuentas", "CoinsVIP", InfoCuenta[playerid2][jID], InfoCuenta[playerid2][jMonedas]);
	return 1;
}

cmd:revisarcasa(playerid)
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (InfoPersonaje[playerid][pRango] < 3) return SendPlayerChatMessage(playerid, COLOR_GREY, "[AVISO] Sólo agentes con rango 2 o mayor podrán usar este comando.");
	new h = -1;
	Loop(casa, totalcasas, 1) if (IsPlayerInRangeOfPoint(playerid, 30.0, InfoCasa[casa][cInteriorX], InfoCasa[casa][cInteriorY], InfoCasa[casa][cInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[casa][cInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[casa][cInteriorVW])
	{
		h = casa;
		break;
	}
	if (h == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el interior de ninguna casa.");
	rol_auto(playerid, "comienza a revisar cada espacio de la casa y obtiene información.");
	new string[265], count = 0;
	format(string, sizeof string, "[Información conocida] Casa comprada por %s, valorada en %s dólares.", InfoCasa[h][cPropietario], diner_coma(InfoCasa[h][cPrecio]));
	SendPlayerChatMessage(playerid, COLOR_GREEN, string);
	SendPlayerChatMessage(playerid, COLOR_RED, "Usted ha revisado la casa, esto es lo que ha encontrado:");
	Loop(s, 10, 0) if (InfoCasa[h][cArmario][s] != 0)
	{
		format(string, sizeof string, "Slot %d: %s", s+1, slot_objeto(InfoCasa[h][cArmario][s], InfoCasa[h][cArmarioCant][s]));
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		count++;
	}
	if (count == 0) SendPlayerChatMessage(playerid, COLOR_WHITE, "No hay nada en la casa.");
	return 1;
}

cmd:incautar(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "Sólo miembros de la ley policial.");
	if (InfoPersonaje[playerid][pRango] < 4) return SendPlayerChatMessage(playerid, COLOR_GREY, "[AVISO] Sólo agentes con rango 4 o mayor podrán usar este comando.");
	new item[12], string[230];
	if (sscanf(params, "s[12]", item)) return SendPlayerChatMessage(playerid, COLOR_GRAD2, "Utiliza: /incautar [Opción: armario]. (Realizar cerca de la salida)");
	new h = -1;
	Loop(casa, totalcasas, 1) if (IsPlayerInRangeOfPoint(playerid, 30.0, InfoCasa[casa][cInteriorX], InfoCasa[casa][cInteriorY], InfoCasa[casa][cInteriorZ]) && InfoPersonaje[playerid][pInterior] == InfoCasa[casa][cInteriorInt] && InfoPersonaje[playerid][pVirtualWorld] == InfoCasa[casa][cInteriorVW])
	{
		h = casa;
		break;
	}
	if (h == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en el interior de ninguna casa.");
	if (strcmp(item, "armario", true) == 0)
	{
		format(string, sizeof string, "[CENTRAL] %s ha incautado el armario de %s.",GetNameFormat(playerid), InfoCasa[h][cPropietario]);
		SendRadioMessage(InfoPersonaje[playerid][pMiembro], COLOR_RADIO, string, 1);
		Loop(s, 10, 0)
		{
			InfoCasa[h][cArmario][s] = 0;
			InfoCasa[h][cArmarioCant][s] = 0;
			format(string, sizeof string, "Armario%d", s+1); guardar_int_mysql("casas", string, InfoCasa[h][cID_sql], 0);
			format(string, sizeof string, "ArmarioCant%d", s+1); guardar_int_mysql("casas", string, InfoCasa[h][cID_sql], 0);
		}
	}
	else
	{
		SendPlayerChatMessage(playerid, COLOR_GREY,"[ERROR] Opciones disponibles en uso: armario.");
	}
	return 1;
}

//Velocimetro system
new uwu_color_veh[MAX_VEHICLES];

new const Float:MaxVehicleSpeeds[212] = {
    160.0, 180.0, 160.0, 145.0, 140.0, 155.0, 110.0, 160.0, 110.0, 165.0, // 400 - 409
    160.0, 220.0, 180.0, 110.0, 110.0, 200.0, 140.0, 110.0, 160.0, 160.0, // 410 - 419
    160.0, 160.0, 140.0, 140.0, 140.0, 160.0, 160.0, 160.0, 160.0, 200.0, // 420 - 429
    140.0, 160.0, 110.0, 160.0, 160.0, 160.0, 160.0, 160.0, 140.0, 160.0, // 430 - 439
    160.0, 160.0, 140.0, 160.0, 140.0, 200.0, 160.0, 140.0, 110.0, 160.0, // 440 - 449
    160.0, 210.0, 160.0, 140.0, 160.0, 200.0, 160.0, 160.0, 160.0, 140.0, // 450 - 459
    110.0, 140.0, 160.0, 140.0, 110.0, 140.0, 160.0, 160.0, 160.0, 110.0, // 460 - 469
    160.0, 140.0, 140.0, 140.0, 160.0, 160.0, 160.0, 220.0, 160.0, 160.0, // 470 - 479
    160.0, 110.0, 160.0, 160.0, 140.0, 160.0, 110.0, 110.0, 110.0, 110.0, // 480 - 489
    140.0, 160.0, 160.0, 160.0, 160.0, 160.0, 160.0, 160.0, 160.0, 160.0, // 490 - 499
    160.0, 160.0, 200.0, 160.0, 200.0, 200.0, 200.0, 160.0, 140.0, 140.0, // 500 - 509
    160.0, 160.0, 160.0, 140.0, 160.0, 160.0, 200.0, 160.0, 140.0, 160.0, // 510 - 519
    140.0, 160.0, 200.0, 160.0, 140.0, 160.0, 160.0, 160.0, 160.0, 160.0, // 520 - 529
    140.0, 110.0, 110.0, 160.0, 160.0, 160.0, 200.0, 160.0, 160.0, 160.0, // 530 - 539
    160.0, 200.0, 160.0, 160.0, 140.0, 160.0, 200.0, 160.0, 160.0, 140.0, // 540 - 549
    160.0, 160.0, 160.0, 140.0, 160.0, 160.0, 160.0, 140.0, 200.0, 200.0, // 550 - 559
    200.0, 160.0, 200.0, 110.0, 140.0, 160.0, 160.0, 140.0, 110.0, 110.0, // 560 - 569
    160.0, 140.0, 160.0, 160.0, 140.0, 160.0, 160.0, 160.0, 160.0, 160.0, // 570 - 579
    140.0, 200.0, 160.0, 140.0, 140.0, 160.0, 160.0, 200.0, 160.0, 160.0, // 580 - 589
    160.0, 160.0, 160.0, 110.0, 110.0, 160.0, 200.0, 160.0, 160.0, 160.0, // 590 - 599
    160.0, 160.0, 200.0, 200.0, 160.0, 160.0, 140.0, 140.0, 140.0, 140.0, // 600 - 609
    140.0, 140.0                                                          // 610 - 611
};

stock Float:GetVehicleTopSpeed(modelid)
{
    if(modelid < 400 || modelid > 611) return 160.0;
    return MaxVehicleSpeeds[modelid - 400];
}

forward Float: GetVehicleSpeed(vehicleid);
public Float: GetVehicleSpeed(vehicleid)
{
	new Float:x,Float:y,Float:z;
	GetVehicleVelocity(vehicleid,x,y,z);
	return floatmul(VectorSize(x,y,z),170.0);
}

stock UpdateBars(playerid)
{
    if(!IsPlayerInAnyVehicle(playerid)) return 1;

    new vehicleid = GetPlayerVehicleID(playerid);
    new modelid = GetVehicleModel(vehicleid);

    new Float:velocidad_actual = GetVehicleSpeed(vehicleid);
    new Float:velocidad_maxima = GetVehicleTopSpeed(modelid);

    if(velocidad_actual > velocidad_maxima) velocidad_actual = velocidad_maxima;
    new Float:porcentaje_vel = velocidad_actual / velocidad_maxima;
    new Float:tamano_y_vel = porcentaje_vel * -40.0; 

    new gasolina_actual = veh_gasolina[vehicleid]; 

    if(gasolina_actual > 100) gasolina_actual = 100;
    if(gasolina_actual < 0) gasolina_actual = 0;

    new Float:porcentaje_gas = float(gasolina_actual) / 100.0;
    new Float:tamano_y_gas = porcentaje_gas * -40.0;

    if(!EstaEnBicis(vehicleid))
    {
        PlayerTextDrawTextSize(playerid, p_tdVelocimetro[playerid][2], 20.000, tamano_y_vel);
        PlayerTextDrawTextSize(playerid, p_tdVelocimetro[playerid][3], 20.000, tamano_y_gas);

        PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][2]);
        PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][3]);
    }
    else
    {
        PlayerTextDrawTextSize(playerid, p_tdVelocimetro[playerid][2], 20.000, tamano_y_vel);
        PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][2]);
        
        PlayerTextDrawHide(playerid, p_tdVelocimetro[playerid][3]);
    }

    return 1;
}

hide_velocimetro(playerid)
{
	show_velocimetro[playerid] = 0;
	Loop(x, 9, 0) { PlayerTextDrawHide(playerid, p_tdVelocimetro[playerid][x]); }
	return 1;
}

mostrar_velocimetro(playerid, vehicleid)
{
	if (InfoPersonaje[playerid][pTogVelocimetro] == 0) return 1;
	if (vehicleid == 0) return 1;
	
	//actived
	show_velocimetro[playerid] = 1;
	
	//new's
	new colorsito = 1, id = verificar_id_vehiculo(vehicleid), gvel[100];
	if (id != -1) colorsito = InfoVehiculo[id][vColor_1];
	uwu_color_veh[vehicleid] = colorsito;
	if (EstaEnBicis(vehicleid))
	{
	    //box principal
	    PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][0]);
		PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][2]);
		PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][4]);
		PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][5]);

		format(gvel, sizeof gvel, "%03d", floatround(GetVehicleSpeed(vehicleid)));
		PlayerTextDrawSetStringEx(playerid, p_tdVelocimetro[playerid][4], gvel);
		UpdateBars(playerid);
	}
	if (!EstaEnBicis(vehicleid))
	{
		format(gvel, sizeof gvel, "%03d", floatround(GetVehicleSpeed(vehicleid)));
		PlayerTextDrawSetStringEx(playerid, p_tdVelocimetro[playerid][4], gvel);

		UpdateBars(playerid);
		
		Loop(x, 9, 0) { PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][x]); }

	}
	return 1;
}

update_velocimetro(playerid, vehicleid)
{
	if (vehicleid != 0)
	{
		//new's
		new gvel[100];
		if (EstaEnBicis(vehicleid))
		{
			// Velocidad
			format(gvel, sizeof gvel, "%03d", floatround(GetVehicleSpeed(vehicleid)));
			PlayerTextDrawSetStringEx(playerid, p_tdVelocimetro[playerid][4], gvel);
			PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][4]);

			UpdateBars(playerid);

		}
		if (!EstaEnBicis(vehicleid))
		{
			//-- km/h
			format(gvel, sizeof gvel, "%03d", floatround(GetVehicleSpeed(vehicleid)));
			PlayerTextDrawSetStringEx(playerid, p_tdVelocimetro[playerid][4], gvel);
			PlayerTextDrawShow(playerid, p_tdVelocimetro[playerid][4]);

			UpdateBars(playerid);
		}
	}
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	// CONCE REMAKE
	if(playertextid == p_tdConce[playerid][40]) //color negro 3 6 10 151
	{
		ChangeVehicleColor(autodemierda[playerid], 0, 0);
		Vehicle_Color[playerid] = 0;
	}

	if(playertextid == p_tdConce[playerid][41]) //color negro
	{
		ChangeVehicleColor(autodemierda[playerid], 3, 3);
		Vehicle_Color[playerid] = 3;
	}

	if(playertextid == p_tdConce[playerid][42]) //color negro
	{
		ChangeVehicleColor(autodemierda[playerid], 6, 6);
		Vehicle_Color[playerid] = 6;
	}

	if(playertextid == p_tdConce[playerid][43]) //color negro
	{
		ChangeVehicleColor(autodemierda[playerid], 10, 10);
		Vehicle_Color[playerid] = 10;
	}

	if(playertextid == p_tdConce[playerid][44]) //color negro
	{
		ChangeVehicleColor(autodemierda[playerid], 151, 151);
		Vehicle_Color[playerid] = 151;
	}


	if (playertextid == p_tdConce[playerid][45]) //comprar
	{
		if (CompraVehiculo[playerid] == -1)
		{
			CancelSelectTextDraw(playerid);
			CompraVehiculo[playerid] = -1;
			return ShowInfoForPlayer(playerid, "~r~No has ingresado ningún modelo.", 5000);
		}
		new id = CompraVehiculo[playerid];
		new modelo = infovehicle[id][elModelo], precio = Descuento_Compra(playerid, infovehicle[id][elPrecio], 2);
		if (GetPlayerCash(playerid) < precio)
		{
			CancelSelectTextDraw(playerid);
			CompraVehiculo[playerid] = -1;
			return ShowInfoForPlayer(playerid, "~w~No cuentas con el ~r~dinero suficiente~w~...", 5000);
		}
		GivePlayerCash(playerid, -precio, "comprar vehiculo");
		CobroNegocio(id_negocio[playerid], (precio*10)/100);
		new Float:PX, Float:PY, Float:PZ, Float:Angulo;
		if (vehiculo_avion(modelo))
		{
			PX = 1948.0747;
			PY = -2492.8047;
			PZ = 24.6460;
			Angulo = 90.0000;
		}
		else if (vehiculo_bote(modelo))
		{
			PX = 2933.2100; PY = -1070.8807; PZ = 10.0364; Angulo = 180.0000;
		}
		else
		{
			PX = InfoNegocio[id_negocio[playerid]][nVehicleX];
			PY = InfoNegocio[id_negocio[playerid]][nVehicleY];
			PZ = InfoNegocio[id_negocio[playerid]][nVehicleZ];
			Angulo = InfoNegocio[id_negocio[playerid]][nVehicleR];
		}
		new colorxdd = Vehicle_Color[playerid];
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		crear_vehiculo(playerid, modelo, PX, PY, PZ, Angulo, 0, 0, colorxdd, colorxdd, precio, infovehicle[id][elMaxMaletero], 0, -1, -1);
		CancelSelectTextDraw(playerid);
		CompraVehiculo[playerid] = -1;
		
		HideConceTextdraw(playerid);
		SetCameraBehindPlayer(playerid);
		DestroyVehicle(autodemierda[playerid]);

		new str[256];
		if (InfoCuenta[playerid][jVIP] != 0) { format(str, sizeof(str), "~w~Adquiriste un ~y~%s ~w~por ~g~$%s ~w~y recibiste un descuento de ~g~$%s ~w~por tu ~y~membersia premium."); }
		else format(str, sizeof(str), "~w~Adquiriste un ~y~%s ~w~por ~g~%s.", GetNameVehicle(modelo), diner_coma(precio));

		ShowInfoForPlayer(playerid, str, 5000);
	}

	// CREACION DE PJ
	if (playertextid == p_tdSeleccionarPJ[playerid][29]) // box slot 1
	{
		if (SlotDisponible[playerid][0]) return 1;
		PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
		LimpiarTD(playerid);
		SeleccionarPersonaje(playerid, SeleccionoPJ1[playerid]);
	}
	if (playertextid == p_tdSeleccionarPJ[playerid][30]) // box slot 2
	{
		if (SlotDisponible[playerid][1]) return 1;
		PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
		LimpiarTD(playerid);
		SeleccionarPersonaje(playerid, SeleccionoPJ2[playerid]);
	}
	if (playertextid == p_tdSeleccionarPJ[playerid][31]) // box slot 3
	{
		if (SlotDisponible[playerid][2]) return 1;
		PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
		LimpiarTD(playerid);
		SeleccionarPersonaje(playerid, SeleccionoPJ3[playerid]);
	}
	if (playertextid == p_tdSeleccionarPJ[playerid][32]) // box slot 4
	{
		if (SlotDisponible[playerid][3]) return 1;
		PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
		LimpiarTD(playerid);
		SeleccionarPersonaje(playerid, SeleccionoPJ4[playerid]);
	}
	if (playertextid == p_tdSeleccionarPJ[playerid][49]) // crear personaje
	{
		if(GetPVarInt(playerid, "max_pjs") >= 4)
			return SendClientMessage(playerid, 0xFF4444AA, "Has alcanzado el limite maximo de personajes (4).");
		Dialog_Show(playerid, CrearPersonaje, DIALOG_STYLE_INPUT, "{FFFFFF}Personajes - {FE9A2E}Creación", "{FFFFFF}Estás a punto de crear un personaje, introduce el nombre del mismo.\nEs importante usar el formato {a7292c}Nombre_Apellido{FFFFFF}.\n\n((EJEMPLO - {a7292c}Rick_Grimes{FFFFFF}))\n", "Continuar", "Volver");
		SetPVarInt(playerid, "QhacerPj", 1);
		SetPVarInt(playerid, "max_pjs", 1);
	}

	if(playertextid == p_tdCrearPJ[playerid][29])
	{
		new sexo = GetPVarInt(playerid, "SEXO_PJ");

		if(sexo == 0 || sexo == 2) // pasa a hombre
		{
			SetPVarInt(playerid, "CPJ_STEP_ONE", 1);

			InfoPersonaje[playerid][pSexo] = 1;
			InfoPersonaje[playerid][pSkin] = 7;
			SetPVarInt(playerid, "SEXO_PJ", 1);

			PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][29], "H");

			if(IsValidDynamicActor(ActorLoginMujer[playerid])) 
				DestroyDynamicActor(ActorLoginMujer[playerid]);

			if(IsValidDynamicActor(ActorLoginHombre[playerid])) 
				DestroyDynamicActor(ActorLoginHombre[playerid]);

			ActorLoginHombre[playerid] = CreateDynamicActor(7, 254.7127, 4.6209, 1501.0079, 22.7942, .worldid = playerid + 10);
			ApplyDynamicActorAnimation(ActorLoginHombre[playerid], "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);
		}
		else if(sexo == 1) // pasa a mujer
		{
			SetPVarInt(playerid, "CPJ_STEP_ONE", 1);

			InfoPersonaje[playerid][pSexo] = 2;
			InfoPersonaje[playerid][pSkin] = 96;
			SetPVarInt(playerid, "SEXO_PJ", 2);

			PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][29], "M");

			if(IsValidDynamicActor(ActorLoginHombre[playerid])) 
				DestroyDynamicActor(ActorLoginHombre[playerid]);

			if(IsValidDynamicActor(ActorLoginMujer[playerid])) 
				DestroyDynamicActor(ActorLoginMujer[playerid]);

			ActorLoginMujer[playerid] = CreateDynamicActor(96, 254.7127, 4.6209, 1501.0079, 22.7942, .worldid = playerid + 10);
			ApplyDynamicActorAnimation(ActorLoginMujer[playerid], "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0);
		}
	}

	if(playertextid == p_tdCrearPJ[playerid][33])
	{
		new str[512];
		format(str, sizeof(str), "\
            {DADADA}Hola, {b7a354}%s{DADADA}. Selecciona la edad que tendra tu personaje.\n\n\
            \t{DADADA}Minimo {b7a354}18{DADADA} años y maximo {b7a354}85{dadada} años.\n\n\
        ", InfoCuenta[playerid][jNombre]);
        Dialog_Show(playerid, CrearPJ_Edad, DIALOG_STYLE_INPUT, "{b7a354}Boulevard{DADADA} - Personalizar personaje", str, "Continuar", "Atrás");
	}

	if(playertextid == p_tdCrearPJ[playerid][34])
	{
		new str[1024];
		format(str, sizeof(str), "\
            {DADADA}Hola, {b7a354}%s{DADADA}. Selecciona el peso que tendra tu personaje.\n\n\
            \t{DADADA}Minimo {b7a354}45{DADADA} kilos y maximo {b7a354}120 {dadada}kilos.\n\n\
        ", InfoCuenta[playerid][jNombre]);
        Dialog_Show(playerid, CrearPJ_Peso, DIALOG_STYLE_INPUT, "{b7a354}Boulevard{DADADA} - Personalizar personaje", str, "Continuar", "Atrás");
	}

	if(playertextid == p_tdCrearPJ[playerid][41])
	{
		if(InfoPersonaje[playerid][pSexo] == 0)
   			return Notification_Show(playerid, "Falta seleccionar sexo.", 5000);

		if(InfoPersonaje[playerid][pEdad] == 0)
			return Notification_Show(playerid, "Falta ingresar edad.", 5000);

		if(InfoPersonaje[playerid][pPeso] == 0)
			return Notification_Show(playerid, "Falta ingresar peso.", 5000);

		for(new i; i < 42; i++)
		{
			PlayerTextDrawHide(playerid, p_tdCrearPJ[playerid][i]);
		}
		CancelSelectTextDraw(playerid);
		TogglePlayerControllable(playerid, true);
		EmpezarPersonaje(playerid);
	}

	//-- Email
	if (playertextid == p_tdLogin[playerid][17]) {
       Dialog_Show(playerid, IniciarSesion, DIALOG_STYLE_INPUT, " ", "\n{FFFFFF}Ingresa tu correo electronico para acceder.\n", "Continuar", "Atrás");
	}
	//-- Password...
    if (playertextid == p_tdLogin[playerid][28]) {
       if (EnLogin[playerid] == 2) {
            Dialog_Show(playerid, IniciarSesion2, DIALOG_STYLE_PASSWORD, " ", "\n{FFFFFF}Ingresa tu contraseña para acceder.", "Ingresar", "Atrás");
	   	}
		else return CrearNotificacion(playerid,"none", "Aun no colocas el Email.", 3); //ShowInfoForPlayer(playerid, "Aun no colocas el Email.", 3000);
	}

	//-- Boton ingresar
    if (playertextid == p_tdLogin[playerid][48]) 
	{
       	if (EnLogin[playerid] == 3) 
	   	{
			new query[170], Cache:result;
			mysql_format(db_samp, query, sizeof query, "SELECT * FROM cuentas WHERE ID = '%d'", InfoCuenta[playerid][jID]);
			result = mysql_query(db_samp, query);
			if (cache_num_rows() > 0) 
			{
				rebel_string(0, "Email", InfoCuenta[playerid][jEmail], 256);
				rebel_string(0, "IP", InfoCuenta[playerid][jIP], 18);
				rebel_int(0, "JotoOtaku", InfoCuenta[playerid][jAdmin]);
				rebel_int(0, "EncFac", InfoCuenta[playerid][jEncFac]);
				rebel_int(0, "VIP", InfoCuenta[playerid][jVIP]);
				rebel_int(0, "Expira", InfoCuenta[playerid][jExpira]);
				rebel_int(0, "CoinsVIP", InfoCuenta[playerid][jMonedas]);
				rebel_int(0, "Multicuenta", InfoCuenta[playerid][jMulticuenta]);
				rebel_int(0, "OtakuN_N", InfoCuenta[playerid][jBaneo]);
				rebel_int(0, "TimeBanUwU", InfoCuenta[playerid][jTiempoBaneo]);
				rebel_string(0, "FueBan", InfoCuenta[playerid][jCulpableBaneo], 24);
				rebel_string(0, "ReasonBanUwU", InfoCuenta[playerid][jRazonBaneo], 256);
				rebel_string(0, "MomentBan", InfoCuenta[playerid][jFechaBaneo], 256);
				rebel_string(0, "FechaRegistro", InfoCuenta[playerid][jFechaRegistro], 256);
				rebel_string(0, "UltimaConexion", InfoCuenta[playerid][jUltimaConexion], 256);
				rebel_int(0, "Ranuras", InfoCuenta[playerid][jRanuras]);
				rebel_int(0, "VerMP", InfoCuenta[playerid][jVerMP]);
				rebel_int(0, "TogMP", InfoCuenta[playerid][jTogMP]);
				rebel_int(0, "BloqueoMP", InfoCuenta[playerid][jBloqueoMP]);
				rebel_int(0, "TogPing", InfoCuenta[playerid][jTogPing]);
				rebel_int(0, "MaxMuebles", InfoCuenta[playerid][jMaxMuebles]);
				rebel_int(0, "MaxNegocios", InfoCuenta[playerid][jMaxNegocios]);
				rebel_int(0, "MaxCasas", InfoCuenta[playerid][jMaxCasas]);
				cache_unset_active();

				cache_delete(result);
			}
			SetLogin(playerid, 3);
			if (InfoCuenta[playerid][jBaneo] != 0) return MuestraBloqueoCuenta(playerid);
			VerPersonajes(playerid);
		}
	}

	//-- Registrarse
    if (playertextid == p_tdLogin[playerid][37]) 
	{
		PlayerTextDrawSetStringEx(playerid, p_tdLogin[playerid][17], "_");
		PlayerTextDrawSetStringEx(playerid, p_tdLogin[playerid][28], "_");

		SetLogin(playerid, 2);
		
       	if (Active_Registro == 0) {
	        SendClientMessage(playerid, COLOR_GREY, "Registro deshabilitado, hasta la próxima.");
	    	SetTimerEx("TimerKICK", 1500, false, "i", playerid);
	        return 1;
       	}
		Dialog_Show(playerid, Registrarse, DIALOG_STYLE_INPUT, "{FFFFFF}Registrarse", "{FFFFFF}Introduce tu {FE9A2E}nombre de usuario{FFFFFF}, el cual te identificará en la base de datos:\n", "Continuar", "Volver");

	}

	new target = GetPVarInt(playerid, "USER_INTERACT");
    if(playertextid == p_tdInteractuar[playerid][10])
    { 
        new str[512];
        format(str, sizeof(str), "{1378DE}%s {ffffff}Te ha enviado una solicitud de amistad.", GetUnknown(playerid));
        Dialog_Show(target, DialogUnknown, DIALOG_STYLE_MSGBOX, "Solicitud de amistad", str, "Aceptar", "Rechazar");
		
        Unknown[target] = playerid;
        CancelSelectTextDraw(playerid);
        Loop(j, 25, 0) { PlayerTextDrawHide(playerid, p_tdInteractuar[playerid][j]); }
		SetPVarInt(playerid, "IN_UNK", 0);
        return SendClientMessage(playerid, COLOR_WHITE, "{1378DE}[AMIGOS] {ffffff}Le enviaste una solicitud de amistad, espera su respuesta.");
    }

    if(playertextid == p_tdInteractuar[playerid][12])
    {
        new gformat[128];
        format(gformat, sizeof gformat, "{ffffff}Introduce la cantidad de {62A64C}dinero {ffffff}que le daras a {a3a3a3}%s", 
        InfoPersonaje[target][pCodigo]);
        Dialog_Show(playerid, CederDineroxd, DIALOG_STYLE_INPUT, "Ceder dinero", gformat, "Continuar", "Cancelar");
        Unknown[target] = playerid;
        CancelSelectTextDraw(playerid);
        Loop(j, 25, 0) { PlayerTextDrawHide(playerid, p_tdInteractuar[playerid][j]); }
		SetPVarInt(playerid, "IN_UNK", 0);
    }

	if(playertextid == p_tdInteractuar[playerid][14])
	{
		if(target != INVALID_PLAYER_ID && target != playerid)
		{
			new Float:pos[3];
			GetPlayerPos(target, pos[0], pos[1], pos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
			{
				Dialog_Show(playerid, DialogSaludos, DIALOG_STYLE_LIST, "Selecciona un saludo", "Saludo 1\nSaludo 2\nSaludo 3\nSaludo 4\nSaludo 5\nSaludo 6\nSaludo 7\nSaludo 8", "Seleccionar", "Cancelar");

				CancelSelectTextDraw(playerid);
				Loop(j, 25, 0) { PlayerTextDrawHide(playerid, p_tdInteractuar[playerid][j]); }
				SetPVarInt(playerid, "IN_UNK", 0);
			}
			else
			{
				ShowInfoForPlayer(playerid, "~r~~h~Estás demasiado lejos de la persona.", 5000);
			}
		}
		else
		{
			ShowInfoForPlayer(playerid, "~r~~h~Jugador inválido.", 5000);
		}
	}
    
	if(playertextid == p_tdInteractuar[playerid][18])
	{
		Loop(x, 25, 0) { PlayerTextDrawHide(playerid, p_tdInteractuar[playerid][x]); }
		CancelSelectTextDraw(playerid);
		SetPVarInt(playerid, "IN_UNK", 0);
		return 1;
	}

	//inventario
	if (Act_Inventario[playerid] != 0)
	{
		//bolsillos
		if (playertextid == INV_obj[playerid][0]) //slot 1
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 0);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][2]) //slot 2
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 1);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][4]) //slot 3
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 2);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][6]) //slot 4
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 3);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][8]) //slot 5
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 4);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][10]) //slot 6
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 5);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][12]) //slot 7
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 6);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][14]) //slot 8
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 7);
			CancelSelectTextDraw(playerid);
		}
		if (playertextid == INV_obj[playerid][16]) //slot 9
		{
			SetPlayerInventario(playerid, 2);
			sacar_inventario(playerid, 8);
			CancelSelectTextDraw(playerid);
		}
		//mano derecha
		if (playertextid == INV_obj[playerid][22])
		{
			SetPlayerInventario(playerid, 2);
			guardar_inventario(playerid, 1);
			CancelSelectTextDraw(playerid);
		}
		//mano izquierda
		if (playertextid == INV_obj[playerid][18])
		{
			SetPlayerInventario(playerid, 2);
			guardar_inventario(playerid, 2);
			CancelSelectTextDraw(playerid);
		}
		//espalda
		if (playertextid == INV_obj[playerid][20])
		{
			SetPlayerInventario(playerid, 2);
			pc_cmd_qespalda(playerid);
			CancelSelectTextDraw(playerid);
		}
	}
    return 0;
}

Dialog:CederDineroxd(playerid, response, listitem, inputtext[])
{
    if(!response)
    {
        Loop(i, 25, 0) { PlayerTextDrawShow(playerid, p_tdInteractuar[playerid][i]);}
        SelectTextDraw(playerid, 0x121429FF);
        return 1;
    }
    if(!IsNumeric(inputtext)) 
    {
        SendClientMessage(playerid, -1, "Solo puedes poner numeros.");
        return 1;
    }
    new cantidad = strval(inputtext);   
    if(InfoPersonaje[playerid][pDinero] < cantidad) 
    {
        SendClientMessage(playerid, -1, "No tienes esa cantidad de dinero");
        return 1;
    }
    GivePlayerCash(playerid, -cantidad, "Cedio dinero");
    new targetId = GetPVarInt(playerid, "USER_INTERACT");
	GivePlayerCash(targetId, cantidad, "le cedieron dinero");
    return 1;
}

Dialog:DialogSaludos(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new target = GetPVarInt(playerid, "USER_INTERACT");
        new style = listitem + 1;
        
        if(IsPlayerConnected(target) && target != playerid)
        {
            new Float:pos[3];
            GetPlayerPos(target, pos[0], pos[1], pos[2]);
            
            if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
            {
                SetPVarInt(playerid, "shrequest", target);
                SetPVarInt(playerid, "shstyle", style);
                
                new string[128];
                format(string, sizeof string, "Saludaste a %s, espera que el responda.", GetNameFormat(target));
                Notification_Show(playerid, string, 5000);
                
                format(string, sizeof string, "%s te ha saludado, porfavor usa '/aceptar saludo' para darle la mano.", GetNameFormat(playerid));
                Notification_Show(target, string, 5000);
            }
            else
            {
                ShowInfoForPlayer(playerid, "~r~~h~Estás demasiado lejos de la persona.", 5000);
            }
        }
        else
        {
            ShowInfoForPlayer(playerid, "~r~~h~Jugador desconectado.", 5000);
        }
    }
    return 1;
}

Dialog:CrearPJ_Edad(playerid, response, listitem, inputtext[])
{
	if(!response){ Notification_Show(playerid, "Recuerda que debes personalizar tu personaje antes de iniciar a jugar.", 3000); return 1; }
    if(!IsNumeric(inputtext)) { Notification_Show(playerid, "No puedes poner letras, solo numeros.", 3000); return 1; }
    if(strval(inputtext) < 18) { Notification_Show(playerid, "Debes tener mas de 18 años.", 3000); return 1; }
    if(strval(inputtext) > 85) { Notification_Show(playerid, "Debes tener menos de 85 años.", 3000); return 1; }
    InfoPersonaje[playerid][pEdad] = strval(inputtext);

    new age[12];
    format(age, sizeof(age), "%s", inputtext);
    PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][33], age);
    SetPVarInt(playerid, "CPJ_STEP_TWO", 1);
	return 1;
}

Dialog:CrearPJ_Peso(playerid, response, listitem, inputtext[])
{
	if(!response){ Notification_Show(playerid, "Recuerda que debes personalizar tu personaje antes de iniciar a jugar.", 3000); return 1; }
    if(!IsNumeric(inputtext)) { Notification_Show(playerid, "No puedes poner letras, solo numeros.", 3000); return 1; }
    if(strval(inputtext) < 45) { Notification_Show(playerid, "Debes pesar mas de 45 kilos.", 3000); return 1; }
    if(strval(inputtext) > 120) { Notification_Show(playerid, "Debes pesar menos de 120 kilos.", 3000); return 1; }
    InfoPersonaje[playerid][pPeso] = strval(inputtext);

    new peso[12];
    format(peso, sizeof(peso), "%s", inputtext);
    PlayerTextDrawSetString(playerid, p_tdCrearPJ[playerid][34], peso);
    SetPVarInt(playerid, "CPJ_STEP_THREE", 1);
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (Act_Inventario[playerid] != 0)
	{
		//esc
		if (Text:INVALID_TEXT_DRAW == clickedid)
		{
			SetPlayerInventario(playerid, 2);
			CancelSelectTextDraw(playerid);
			return 1;
		}
		//exit
		if (clickedid == INV_exit)
		{
			SetPlayerInventario(playerid, 2);
			CancelSelectTextDraw(playerid);
		}
	}	
	
	if (BuyVIPvehicle[playerid] != -1)
	{
		//esc
		if (Text:INVALID_TEXT_DRAW == clickedid)
		{
			HideConceTextdraw(playerid);
			CancelSelectTextDraw(playerid);
			BuyVIPvehicle[playerid] = -1;
			DestroyVehicle(autodemierda[playerid]);
			return 1;
		}
		//comprar
		else if (clickedid == CocheVS[2])
		{
			hide_comprarvehiculo(playerid);
			if (BuyVIPvehicle[playerid] == -1)
			{
				CancelSelectTextDraw(playerid);
				BuyVIPvehicle[playerid] = -1;
				return SendPlayerChatMessage(playerid, -1, "No has ingresado ningún modelo.");
			}
			new id = BuyVIPvehicle[playerid];
			new modelo = infovehicle[id][elModelo], precio = infovehicle[id][elPrecio];
			if (InfoCuenta[playerid][jMonedas] < precio) return SendClientMessageEx(playerid, COLOR_GREY, "* Necesitas %d monedas para comprar este vehículo, tienes %d monedas.", precio, InfoCuenta[playerid][jMonedas]);
			InfoCuenta[playerid][jMonedas] -= precio;
			guardar_int_mysql("cuentas", "CoinsVIP", InfoCuenta[playerid][jID], InfoCuenta[playerid][jMonedas]);
			new Float:PX, Float:PY, Float:PZ, Float:Angulo;
			if (vehiculo_avion(modelo)) { PX = 1948.0747; PY = -2492.8047; PZ = 24.6460; Angulo = 90.0000; }
			else if (vehiculo_bote(modelo)) { PX = 2933.2100; PY = -1070.8807; PZ = 10.0364; Angulo = 180.0000; }
			else { PX = 767.4407; PY = -1377.7820; PZ = 14.1683; Angulo = -90.0000; }
			new color1 = random(250), color2 = random(250);
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			crear_vehiculo(playerid, modelo, PX, PY, PZ, Angulo, 0, 0, color1, color2, precio, infovehicle[id][elMaxMaletero], 0, -1, -1);
			CancelSelectTextDraw(playerid);
			BuyVIPvehicle[playerid] = -1;
			SendClientMessageEx(playerid, 0x60bd7eFF, "Compraste '%s' por %d monedas, te quedan %d monedas.", GetNameVehicle(modelo), precio, InfoCuenta[playerid][jMonedas]);
		}
	}
	//concesionario
	if (CompraVehiculo[playerid] != -1)
	{
		//esc
		if (Text:INVALID_TEXT_DRAW == clickedid)
		{
			HideConceTextdraw(playerid);
			CancelSelectTextDraw(playerid);
			CompraVehiculo[playerid] = -1;
			DestroyVehicle(autodemierda[playerid]);
			return 1;
		}
		//regresar
		if (clickedid == CocheVS[1])
		{
			HideConceTextdraw(playerid);
			CancelSelectTextDraw(playerid);
			CompraVehiculo[playerid] = -1;
			pc_cmd_comprar(playerid);
		}
		//comprar
	}
	return 0;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
    if (usuario_registro[playerid] != 2)
	{
		SendPlayerChatMessage(playerid, COLOR_GRAD2, "* No puedes introducir comandos si no estás ingresado en el servidor.");
		return 0;
	}
	if (GetPVarInt(playerid, "LoadingObjects") == 1)
	{
	    SendPlayerChatMessage(playerid, COLOR_GRAD2, "* No puedes introducir comandos mientras los objetos cargan.");
	    return 0;
	}
    if (GetPlayerAdmin(playerid, 0) == 0)
	{
		if (strfind(cmd, ":", true) != -1)
		{
			new i_numcount, i_period, i_pos;
			while (cmd[i_pos])
			{
				if('0' <= cmd[i_pos] <= '9') i_numcount++;
				else if(cmd[i_pos] == '.') i_period++;
				i_pos++;
			}
			if (i_numcount >= 8 && i_period >= 3)
			{
				new string[260];
				format(string,sizeof string, "[ATENCIÓN] %s(%d) puede estar haciendo SPAM: '%s'", GetNameFormat(playerid), playerid, cmd);
				SendAdminMessage(COLOR_YELLOW, string);
				return 0;
			}
		}
	}
    return 1;
}


stock ShowInfoForPlayer(playerid, text[], time = 3000)
{
    KillTimer(InfoTimer[playerid]);
    PlayerTextDrawSetStringEx(playerid, InfoText[playerid], text);
	PlayerTextDrawShow(playerid, InfoText[playerid]);
	PlayerText_MoveToY(playerid, InfoText[playerid], 435.000000, 1000, EASE_OUT_BACK);
    InfoTextShowing[playerid] = 1;
    FixTextDrawString(text);
	InfoTimer[playerid] = SetTimerEx("OcultarMierda", time, false, "i", playerid);
	return 1;
}

funcion OcultarMierda(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	PlayerText_MoveToY(playerid, InfoText[playerid], 450.000000, 1000, EASE_IN_BACK);
	PlayerTextDrawHide(playerid, InfoText[playerid]);
	InfoTextShowing[playerid] = 0;
	KillTimer(InfoTimer[playerid]);
    return 1;
}

FixTextDrawString(message[], bool:space = false) {
	for(new len = strlen(message), pos; pos < len; pos ++)
	{
		switch(message[pos])
		{
			case 'à': message[pos] = 151;
			case 'á': message[pos] = 152;
			case 'â': message[pos] = 153;
			case 'ä': message[pos] = 154;
			case 'À': message[pos] = 128;
			case 'Á': message[pos] = 129;
			case 'Â': message[pos] = 130;
			case 'Ä': message[pos] = 131;
			case 'è': message[pos] = 157;
			case 'é': message[pos] = 158;
			case 'ê': message[pos] = 159;
			case 'ë': message[pos] = 160;
			case 'È': message[pos] = 134;
			case 'É': message[pos] = 135;
			case 'Ê': message[pos] = 136;
			case 'Ë': message[pos] = 137;
			case 'ì': message[pos] = 161;
			case 'í': message[pos] = 162;
			case 'î': message[pos] = 163;
			case 'ï': message[pos] = 164;
			case 'Ì': message[pos] = 138;
			case 'Í': message[pos] = 139;
			case 'Î': message[pos] = 140;
			case 'Ï': message[pos] = 141;
			case 'ò': message[pos] = 165;
			case 'ó': message[pos] = 166;
			case 'ô': message[pos] = 167;
			case 'ö': message[pos] = 168;
			case 'Ò': message[pos] = 142;
			case 'Ó': message[pos] = 143;
			case 'Ô': message[pos] = 144;
			case 'Ö': message[pos] = 145;
			case 'ù': message[pos] = 169;
			case 'ú': message[pos] = 170;
			case 'û': message[pos] = 171;
			case 'ü': message[pos] = 172;
			case 'Ù': message[pos] = 146;
			case 'Ú': message[pos] = 147;
			case 'Û': message[pos] = 148;
			case 'Ü': message[pos] = 149;
			case 'ñ': message[pos] = 174;
			case 'Ñ': message[pos] = 173;
			case '¡': message[pos] = 64;
			case '¿': message[pos] = 175;
			case '`': message[pos] = 177;
			case '&': message[pos] = 38;
			case ' ': {
				if(space) {
					message[pos] = '_';
				}
			}
			default:  message[pos] = message[pos];
		}
	}
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (result == -1)
	{
		new str[256];
		format(str, sizeof(str), "~w~El comando '~r~%s~w~' que introduciste es ~r~incorrecto~w~, utiliza ~y~/ayuda.", cmd);
		ShowInfoForPlayer(playerid, str, 5000);
		return 0;
	}
	else
	{
		printf("[CMD] [%s] [%s]: /%s %s", GetNameFormat(playerid), InfoCuenta[playerid][jNombre], cmd, params);
	}
	return 1;
}

//------------------------------------------------------------------------------------------------------
encode_tires(tire1, tire2, tire3, tire4)
{
	return tire1 | (tire2 << 1) | (tire3 << 2) | (tire4 << 3);
}

public OnPlayerText(playerid, text[])
{
	if (usuario_registro[playerid] != 2) return 0;
	if (InfoPersonaje[playerid][pMuerto] == 2) { SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes usar este comando en estado muerto."); return 0; }
	new string[320];
	//sistema de centralita
	if (EnLlamada[playerid] == 911) //inicio
	{
		format(string, sizeof string, "{player:%d} por teléfono: %s", playerid, text);
		ProxDetector(8.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		SendPlayerChatMessage(playerid, 0xFFF000FF, "[Teléfono: 911]: Su llamada de emergencia está siendo procesada.");
		Altavoz[playerid] = 0;
		EnLlamada[playerid] = 0; //Sistema teléfono
		ToqueLlamada[playerid] = 0;
		PersonaEnLlamada[playerid] = -1;
		new info[355], zona[128];
		GetPlayer3DZone(playerid, zona, MAX_ZONE_NAME);

		//mensaje a lspd, lscsd y lsfd
		format(info, sizeof info, "|___________Llamada de emergencia___________|");
		SendRadioMessage(1, 0xF2D21EFF, info, 0);
		SendRadioMessage(4, 0xF2D21EFF, info, 0);
		SendRadioMessage(6, 0xF2D21EFF, info, 0);	
		format(info, sizeof info, "{DE8601}* Nombre del ciudadano:{F2D21E} %s", GetNameFormat(playerid));
		SendRadioMessage(1, 0xF2D21EFF, info, 0);
		SendRadioMessage(4, 0xF2D21EFF, info, 0);
		SendRadioMessage(6, 0xF2D21EFF, info, 0);
		format(info, sizeof info, "{DE8601}* Teléfono:{F2D21E} %d", InfoPersonaje[playerid][pTelefono]);
		SendRadioMessage(1, 0xF2D21EFF, info, 0);
		SendRadioMessage(4, 0xF2D21EFF, info, 0);
		SendRadioMessage(6, 0xF2D21EFF, info, 0);
		format(info, sizeof info, "{DE8601}* Situación:{F2D21E} %s", text);
		SendRadioMessage(1, 0xF2D21EFF, info, 0);
		SendRadioMessage(4, 0xF2D21EFF, info, 0);
		SendRadioMessage(6, 0xF2D21EFF, info, 0);
		format(info, sizeof info, "{DE8601}* Rastreo de llamada:{F2D21E} %s.", zona);
		SendRadioMessage(1, 0xF2D21EFF, info, 1);
		SendRadioMessage(4, 0xF2D21EFF, info, 1);
		SendRadioMessage(6, 0xF2D21EFF, info, 1);
		GetPlayerPos(playerid, lastcall911[0], lastcall911[1], lastcall911[2]);

		//centralita
		new x = r_id[playerid];
		if (r_id[playerid] != -1)
		{
			info_c[x][aID] = x;
			info_c[x][aTelefono] = InfoPersonaje[playerid][pTelefono];
			alm(info_c[x][aNombre], GetNameFormat(playerid));
			alm(info_c[x][aHechos], text);
			alm(info_c[x][aZona], zona);
		}
		r_id[playerid] = -1;
		return 0;
	}
	//teléfono
	if(PersonaEnLlamada[playerid] != -1)
	{
		if(EnLlamada[playerid] == 2 || EnLlamada[playerid] == 3)
		{
			if(Altavoz[PersonaEnLlamada[playerid]] == 0)
			{
				format(string, sizeof string, "(Teléfono %d): %s", InfoPersonaje[playerid][pTelefono], text);
				SendPlayerChatMessage(PersonaEnLlamada[playerid], COLOR_YELLOW, string);
			}
			else
			{
				format(string, sizeof string, "[T. Altavoz %d] %s", InfoPersonaje[playerid][pTelefono], text);
				ProxDetector(5.5, PersonaEnLlamada[playerid], string, 0xFFF000FF, 0xFFF000FF, 0xFFF000FF, 0xFFF000FF, 0xFFF000FF);
			}
			format(string, sizeof string, "{player:%d} por teléfono: %s", playerid, text);
			ProxDetector(15.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
			return 0;
		}
		//chat normal
		format(string, sizeof string, "{player:%d} dice: %s", playerid, text);
		ProxDetector(20.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		AnimHablar(playerid, text);
		return 0;
	}
	//chat normal
	format(string, sizeof string, "{player:%d} dice: %s", playerid, text);
	ProxDetector(20.0, playerid, string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	AnimHablar(playerid, text);
	return 0;
}

AnimHablar(playerid, const text[])
{
	if (IsPlayerInAnyVehicle(playerid)) return 1;
	if (InfoPersonaje[playerid][pTogManos] == 0) return 1;
	if (gPlayerUsingLoopingAnim[playerid] != 0) return 1;

	//
	new anim = GetPlayerAnimationIndex(playerid);
	if ((anim != 1538 || anim != 1539 || anim != 1540 || anim != 1541 || anim != 1542))
	{
		es_hablando[playerid] = 1;
		switch (InfoPersonaje[playerid][pEstiloManos])
		{
			case 1: //normal
			{
				ApplyAnimation(playerid, "PED", "IDLE_chat", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 2: //pandillero
			{
				ApplyAnimation(playerid, "MISC", "IDLE_CHAT_02", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 200, false, "d", playerid);
			}
			case 3: //pandillero2
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 4: //pandillero3
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkB", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 5: //pandillero4
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkE", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 6: //pandillero5
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkF", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 7: //pandillero6
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkG", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
			case 8: //pandillero7
			{
				ApplyAnimation(playerid, "GANGS", "prtial_gngtlkH", 4.1, 1, 0, 0, 1, 1, 1);
				SetTimerEx("FinHablar", strlen(text) * 150, false, "d", playerid);
			}
		}
	}
	return 1;
}

funcion FinHablar(playerid)
{
	es_hablando[playerid] = 0;
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

stock IsNumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

stock GetSueloId( id )
{
	for( new i; i < sizeof InfoSuelo; i++ )
	{
		if ( InfoSuelo[i][DropID] == id )
		return i;
	}
	return 0;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (!IsPlayerConnectedEx(playerid)) return 1;
	if (IsPlayerNPC(playerid)) return 1;
	//Heridas en las piernas
	if(PRESSED(KEY_SPRINT) || PRESSED(KEY_JUMP))
	{
	    if (!IsPlayerInAnyVehicle(playerid))
		{
		    Loop(e, MAX_HERIDAS, 0)
		    {
				if(InfoHerida[playerid][e][dmgBodypart] == 4 || InfoHerida[playerid][e][dmgBodypart] == 7 || InfoHerida[playerid][e][dmgBodypart] == 8)
				{
				    if(InfoPersonaje[playerid][pMuerto] == 0)
				    {
				    	ClearAnimations(playerid);
						ApplyAnimation(playerid, "ped", "FALL_collapse", 4.1, 0, 1, 1, 0, 0, 1);
					}
				}
			}
		}
	}

	if(PRESSED(KEY_YES))
    {
        new nearActor = GetNearestActorOfType(playerid, 2, 2.0);
        if(nearActor != INVALID_ACTOR_ID)
        {
            ShowCamello(playerid);
        }
    }

	//lsfd
	if (member_faccion(playerid, 6))
	{
		if (PRESSED(KEY_FIRE) && InfoPersonaje[playerid][pManoDerecha] == 37 && InfoPersonaje[playerid][pManoDerechaCant] > 1)
		{
			new FireID = CercaIncendio(playerid);
			if (FireID != -1)
			{
				if (InfoIncendio[FireID][pI_intensidad] > 0)
				{
					if (InfoIncendio[FireID][pI_intensidad]-2 < 0) InfoIncendio[FireID][pI_intensidad] = 0;
					else InfoIncendio[FireID][pI_intensidad]--;
					if (InfoIncendio[FireID][pI_intensidad] != 0)
					{
						new text[128];
						format(text, sizeof text, "~n~~n~~n~~n~~n~~n~~n~ ~y~Intensidad de incendio:~n~~w~%d restante", InfoIncendio[FireID][pI_intensidad]);
						GameTextForPlayer(playerid, text, 2000, 3);
					}
					else
					{
						DestroyFire(FireID);
						GivePlayerCash(playerid, 550, "apagar incendio");
						SendPlayerChatMessage(playerid, COLOR_LIGHTBLUE, "Recibiste $550 por apagar el incendio.");
					}
				}
			}
		}
	}
	if((newkeys & KEY_CTRL_BACK) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && (newkeys & KEY_CROUCH))) //Al pulsar H
	{
		pc_cmd_peaje(playerid);
    }
	// H
	if (newkeys == KEY_CTRL_BACK)
	{
		//cmds
		pc_cmd_entrar(playerid);
		pc_cmd_salir(playerid);
		pc_cmd_ap(playerid);
		//
	}
	// N
	if (newkeys == KEY_LOOK_BEHIND)
	{
		if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			pc_cmd_motor(playerid);
		}
	}
	// Alt
	if (newkeys == KEY_ACTION)
	{
		if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(!IsPlayerInAnyVehicle(playerid)) return 1;
			Dialog_Show(playerid, PanelVehiculo, DIALOG_STYLE_LIST, " ",
			"1. Cinturón\n\
			2. Luces\n\
			3. Radio\n\
			4. Ventana\n\
			5. Intermitentes\n\
			6. Puertas\n\
			7. Capó\n\
			8. Maletero",
			"Continuar", "Cerrar");
		}
	}	
	// Alt + Y
   	if(newkeys & KEY_WALK && newkeys & KEY_YES || newkeys & KEY_FIRE && newkeys & KEY_YES)
 	{
		pc_cmd_seguro(playerid);
	}

	//-- Panel desconocido
	if(newkeys & KEY_CTRL_BACK) {
        if(GetPVarInt(playerid, "PressUnknownKey") == 0) {
            SetPVarInt(playerid, "PressUnknownKey", 1);
        }
    }
    if(oldkeys & KEY_CTRL_BACK) {
        if(GetPVarInt(playerid, "PressUnknownKey") == 1) {
            SetPVarInt(playerid, "PressUnknownKey", 0);
        }
    }

	// Y
	if (newkeys == KEY_NO)
	{
		if (InfoPersonaje[playerid][pManoDerecha] == 40 && InfoPersonaje[playerid][pManoDerechaCant] == 0)
		{
			if(TaserRecarga[playerid] != 0){SendPlayerChatMessage(playerid, COLOR_GREY, "Espera 5 segundos antes de recargar."); return 1;}
			rol_ame(playerid, "recarga su pistola táser con 400V.");
			GivePlayerWeapon(playerid, 23, 2);
			InfoPersonaje[playerid][pManoDerechaCant] = 2;
			ApplyAnimation(playerid,"SILENCED","Silence_reload",4.1,0,1,1,0,0,1);
			ActualizarManos(playerid, 1);
		}
		else { pc_cmd_bol(playerid); }
	}
	
	//recoger objetos
	if (newkeys == KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) {
    	for (new id = 0; id < sizeof(InfoSuelo); id++) 	{
        	if (!IsPlayerInAnyVehicle( playerid ) && IsPlayerInRangeOfPoint(playerid, 1.5, InfoSuelo[id][DropPosX], InfoSuelo[id][DropPosY], InfoSuelo[id][DropPosZ]))
       		{
       	    	if (TiempoTecla[playerid] > 0) return 1;
       			TiempoTecla[playerid] = 1;
   	        	new i = GetSueloId(InfoSuelo[id][DropID]);
		   		recoger_objeto(playerid, i);
               	TiempoTecla[playerid] = 2;
       		}
        }

	}

	// graffitear
	if (PRESSED(KEY_FIRE) && GetPlayerWeapon(playerid) == WEAPON_SPRAYCAN && GetPVarInt(playerid, "ModoSpray") == 0)
	{
		new faccion = member_faccion(playerid, 9);
		if (faccion != 0 || InfoPersonaje[playerid][pAccesoGraffiti] == 1)
		{
			new bool: nearGraffiti;
			Loop(id, MAX_GRAFFITIS, 0) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoGraffiti[id][gr_PosX], InfoGraffiti[id][gr_PosY], InfoGraffiti[id][gr_PosZ]))
			{
				nearGraffiti = true;
				SetPVarInt(playerid, "ModoSpray", 1);
				SetPVarInt(playerid, "GraffitiID", id);
			}
			if (nearGraffiti)
				playerGraffitiTimer[playerid] = SetTimerEx("UsandoSpray", 1000, true, "i", playerid);
		}
	}
	if (RELEASED(KEY_FIRE) && GetPlayerWeapon(playerid) == WEAPON_SPRAYCAN && GetPVarInt(playerid, "ModoSpray") == 1)
	{
		KillTimer(playerGraffitiTimer[playerid]);
		DeletePVar(playerid, "ModoSpray");
		DeletePVar(playerid, "GraffitiID");
		GameTextForPlayer(playerid, "~n~~w~Pintura ~r~cancelada", 3000, 5);
	}
	//
	if(IsKeyJustDown(KEY_SPRINT,newkeys,oldkeys) && gPlayerUsingLoopingAnim[playerid] == 1)
	{
	    StopApplyAnimEx(playerid);
		if (GetPVarInt(playerid, "PlayerCuffed") == 2) SetPVarInt(playerid, "PlayerCuffed", 0);
    }
	return 1;
}

funcion FreezePlayer(playerid)
{
	TogglePlayerControllable(playerid, 0);
}

funcion UnfreezePlayer(playerid)
{
	TogglePlayerControllable(playerid, 1);
}

ApplyAnimEx(playerid, vehicle, const animlib[],const animname[], Float:Speed, looping, lockx, locky, lockz, lp)
{
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estás herido.");
 	if (GetPVarInt(playerid, "PlayerCuffed") != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones en ese estado.");
	if (vehicle == 0) { if (IsPlayerInAnyVehicle(playerid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones mientras estés dentro de un vehículo."); }
	if (GetPVarInt(playerid, "IsFrozen") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar animaciones porque estás congelado.");
	gPlayerUsingLoopingAnim[playerid] = 1;
	ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, 1);
	return 1;
}

StopApplyAnimEx(playerid)
{
	es_hablando[playerid] = 0;
	gPlayerUsingLoopingAnim[playerid] = 0;
 	ApplyAnimation(playerid, "CARRY", "crry_prtial", 2.0, 0, 0, 0, 0, 0, 1);
}

//Buttons
funcion CerrarSDOne()
{
	MoveDynamicObject(SDobj1, 1617.65063, 1579.23730, 9.80994,4);
	return 1;
}
funcion CerrarSDTwo()
{
	MoveDynamicObject(SDobj2, 1617.67065, 1594.71729, 9.8099,4);
	return 1;
}

stock PlayerFacePlayer(playerid, targetplayerid) { // Yeah, this'll fix the handshake headaches we had last time around (shaking air).
	new
		Float: Angle;

	GetPlayerFacingAngle(playerid, Angle);
	SetPlayerFacingAngle(targetplayerid, Angle+180);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	if (VehicleWindows[vehicleid])
	{
		VehicleWindows[vehicleid] = 0;
		SetVehicleParamsCarWindows(vehicleid, 1, 1, 1, 1);
	}
	if (SirenOn[vehicleid] == true)
	{
		Loop(e, 7, 0)
		{
			if (IsValidDynamicObject(SirenObject[vehicleid][e])) DestroyDynamicObject(SirenObject[vehicleid][e]);
			SirenObject[vehicleid][e] = 0;
		}
		SirenOn[vehicleid] = false;
	}
	//uwu
	alm(veh_music[vehicleid], "nadauwu");
	arr_Engine{vehicleid} = 0;
	veh_gasolina[vehicleid] = 100;
	// vehiculos de usuarios uwu
	Loop(v, totalvehiculos, 1) if (InfoVehiculo[v][vIG_id] == vehicleid)
	{
		InfoVehiculo[v][vMaleteroOn] = 0;
		DestroyVehicle(vehicleid);
		InfoVehiculo[v][vIG_id] = CreateVehicle(InfoVehiculo[v][vModelo], InfoVehiculo[v][vPosicionX], InfoVehiculo[v][vPosicionY], InfoVehiculo[v][vPosicionZ], InfoVehiculo[v][vPosicionR], InfoVehiculo[v][vColor_1], InfoVehiculo[v][vColor_2], -1, InfoVehiculo[v][vSirena]);
        InfoVehiculo[v][vSpawned] = 1;
        SetVehicleMatricula(InfoVehiculo[v][vIG_id]);
		new v_vehicleid = InfoVehiculo[v][vIG_id];
		if (InfoVehiculo[v][vSeguro] != 0) LockPlayerVehicle(v_vehicleid);
		if (InfoVehiculo[v][vPaintJob] != -1) ChangeVehiclePaintjob(v_vehicleid, InfoVehiculo[v][vPaintJob]);
		SetVehicleInterior(v_vehicleid, InfoVehiculo[v][vInterior]);
		SetVehicleExVirtualWorld(v_vehicleid, InfoVehiculo[v][vVirtualWorld]);
		if (InfoVehiculo[v][vModelo] == 528 || InfoVehiculo[v][vModelo] == 427) SetVehicleHealth(v_vehicleid, 5000.0);
		else SetVehicleHealth(v_vehicleid, InfoVehiculo[v][vVida]);
		UpdateVehicleDamageStatus(v_vehicleid, InfoVehiculo[v][vDanioSuperficie], InfoVehiculo[v][vDanioPuertas], InfoVehiculo[v][vDanioLuces], InfoVehiculo[v][vDanioRuedas]);
		Loop(m, MAX_MODIFICACIONES, 0) { AddVehicleComponent(v_vehicleid, InfoVehiculo[v][vModificacion][m]); }
		if (!isnull(InfoVehiculo[v][vCallSign]))
		{
			if (IsValidDynamic3DTextLabel(InfoVehiculo[v][vOnCallSign]))
			{
				DestroyDynamic3DTextLabel(InfoVehiculo[v][vOnCallSign]);
				InfoVehiculo[v][vOnCallSign] = Text3D:INVALID_3DTEXT_ID;
			}
			InfoVehiculo[v][vOnCallSign] = CreateDynamic3DTextLabel(InfoVehiculo[v][vCallSign], 0xEBEBEBFF, -1.0, -2.8, 0.0, 12.0, INVALID_PLAYER_ID, v_vehicleid);
		}
		foreach(new playerid: Player) if (IsPlayerConnectedEx(playerid))
		{
			if (llaves_vehiculo(playerid, v_vehicleid) != -1)
			{
				SendClientMessageEx(playerid, 0xF8AA14AF, "El vehículo (%s) fue enviado a la última posición donde lo estacionaste.", GetVehicleName(v_vehicleid));
			}
		}
		return 1;
	}
	return 1;
}

stock SendReportToQue(reportfrom, report[])
{
    new bool:breakingloop = false, newid = -1;
    for(new i=0;i<MAX_REPORTS;i++)
    {
        if(!breakingloop)
        {
            if(Reports[i][HasBeenUsed] == 0)
            {
                    breakingloop = true;
                    newid = i;
            }
        }
    }
    if(newid != -1)
    {
        alm(Reports[newid][Report], report);
        Reports[newid][ReportFrom] = reportfrom;
        Reports[newid][TimeToExpire] = 5;
        Reports[newid][HasBeenUsed] = 1;
        Reports[newid][BeingUsed] = 1;
        Reports[newid][ReportExpireTimer] = SetTimerEx("ReportTimer", 30000, 0, "d", newid);
        new string[250];
        format(string, sizeof string, "Reporte de %s(%d) {RID: %d]: %s", GetNameFormat(reportfrom), reportfrom, newid, (report));
        SendAdminMessage(0xFFFF91FF, string);
    }
    else
    {
        ClearReports();
		SendReportToQue(reportfrom, report);
	}
	return 1;
}

funcion ClearReports()
{
	for(new i=0;i<MAX_REPORTS;i++)
	{
		alm(Reports[i][Report], "None");
		Reports[i][CheckingReport] = 999;
        Reports[i][ReportFrom] = 999;
        Reports[i][TimeToExpire] = 5;
        Reports[i][HasBeenUsed] = 0;
        Reports[i][BeingUsed] = 0;
	}
	return 1;
}

funcion ReportTimer(reportid)
{
	if(Reports[reportid][BeingUsed] == 1)
	{
	    if(Reports[reportid][TimeToExpire] > 0)
	    {
	        Reports[reportid][TimeToExpire]--;
	        if(Reports[reportid][TimeToExpire] == 0)
	        {
	            SendPlayerChatMessage(Reports[reportid][ReportFrom], COLOR_WHITE, "Tu reporte ha expirado. Recomendamos buscar ayuda en nuestro discord: {3E62F4}https://discord.gg/YsEN5q5h5t");
	            Reports[reportid][BeingUsed] = 0;
	            Reports[reportid][ReportFrom] = 999;
	            return 1;
	        }
  			Reports[reportid][ReportExpireTimer] = SetTimerEx("ReportTimer", 30000, 0, "d", reportid);
		}
	}
	return 1;
}

funcion ReplyTimer(reportid)
{
	alm(Reports[reportid][Report], "None");
	Reports[reportid][CheckingReport] = 999;
	Reports[reportid][ReportFrom] = 999;
	Reports[reportid][TimeToExpire] = 5;
	Reports[reportid][HasBeenUsed] = 0;
	Reports[reportid][BeingUsed] = 0;
}

funcion RadioBroadCast(playerid, color, string[])
{
	new MiscString[128], Float: aaaPositions[3];
	foreach(Player, i)
	{
		if(InfoPersonaje[i][pFrecuencia_radio] == InfoPersonaje[playerid][pFrecuencia_radio] && InfoPersonaje[i][pTogPortatil] != 0 || See_FRC[i] == 1) // Frecuencia de todos, igual al del player, tener todos radio y tenerla todos encendida.
		{                                                                                   // Segunda opción: Tener /verwalkie activado y poder ver todos el canal.
		    if(See_FRC[playerid] == 0) // Espiar canal /wt - /wa - /pr.
		    {
				GetPlayerPos(i, aaaPositions[0], aaaPositions[1], aaaPositions[2]);
				format(MiscString, sizeof(MiscString), "** Radio (%d khz) ** %s: %s", InfoPersonaje[playerid][pFrecuencia_radio], GetNameFormat(playerid), string);
				SendPlayerChatMessage(i, 0x6DFB6DFF, MiscString);
			}
			else
			{
				format(MiscString, sizeof(MiscString), "[ADM] WALKIE OOC: (( Administrador dice %s: %s))", GetNameFormat(playerid), string);
				SendPlayerChatMessage(i, 0x6DFB6DFF, MiscString);
			}
		}
	}
}
funcion RadioBroadCastOOC(playerid, color, string[])
{
	new MiscString[128], Float: aaaPositions[3];
	foreach(Player, i)
	{
		if(InfoPersonaje[i][pFrecuencia_radio] == InfoPersonaje[playerid][pFrecuencia_radio] && InfoPersonaje[i][pTogPortatil] != 0 || See_FRC[i] == 1) // Frecuencia de todos, igual al del player, tener todos radio y tenerla todos encendida.
		{                                                                                   // Segunda opción: Tener /verwalkie activado y poder ver todos el canal.
		    if(See_FRC[playerid] == 0) // Espiar canal /wt - /wa - /pr.
		    {
				GetPlayerPos(i, aaaPositions[0], aaaPositions[1], aaaPositions[2]);
				format(MiscString, sizeof(MiscString), "*[OOC] WALKIE (%d khz) ** (( %s: %s ))", InfoPersonaje[playerid][pFrecuencia_radio], GetNameFormat(playerid), string);
				SendPlayerChatMessage(i, 0x6DFB6DFF, MiscString);
			}
			else
			{
				format(MiscString, sizeof(MiscString), "[ADM] WALKIE OOC: (( Administrador dice %s: %s))", GetNameFormat(playerid), string);
				SendPlayerChatMessage(i, 0x6DFB6DFF, MiscString);
			}
		}
	}
}

IsKeyJustDown(key, newkeys, oldkeys)
{
	if((newkeys & key) && !(oldkeys & key)) return 1;
	return 0;
}

IsValidIP(const ip[])
{
    new a;
	for (new i = 0; i < strlen(ip); i++)
	{
		if (ip[i] == '.')
		{
		    a++;
		}
	}
	if (a != 3)
	{
	    return 1;
	}
	return 0;
}

CheckBan(ip[])
{
	new query[160];
	new Cache:result;
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM ips WHERE IP = '%e'", ip);
	result = mysql_query(db_samp, query);
	new nm = cache_num_rows();
	cache_delete(result);
	return nm;
}

AddBan(ip[], admin[], razon[])
{
	if (CheckBan(ip) == 0)
	{
		new query[1028];
		mysql_format(db_samp, query, sizeof query, "INSERT INTO ips (IP, Admin, Fecha, Razon) VALUES ('%e', '%e', '%e', '%e')", ip, admin, FechaHoy(), razon);
		mysql_tquery(db_samp, query);
	 	foreach(Player, playerid)
		{
		    new playerIP[18];
			GetPlayerIp(playerid, playerIP, sizeof playerIP);
			if (strcmp(playerIP, ip) == 0)
			{
	            SendClientMessageEx(playerid, COLOR_YELLOW, "Fuiste expulsado del servidor, dado que tu IP se encuentra bloqueada por %s.", razon);
				SetTimerEx("TimerKICK", 500, false, "d", playerid);
			}
		}
		return 1;
	}
	return 0;
}

PreloadAnimations(playerid)
{
	for (new i = 0; i < sizeof(g_aPreloadLibs); i ++)
	{
		ApplyAnimation(playerid, g_aPreloadLibs[i], "null", 0.0, 0, 0, 0, 0, 0);
	}
	return 1;
}


public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	SetSyncTime(playerid, SYNC_TYPE_POS);
	if (newinteriorid != 0)
	{
		Streamer_Update(playerid);
		TogglePlayerControllable(playerid, false);
		ShowLoadScreen(playerid, 4000);
	}
	return 1;
}

public OnPlayerUpdate(playerid)
{
	if (IsPlayerConnectedEx(playerid))
	{
		// fps.
		new drunknew;
		drunknew = GetPlayerDrunkLevel(playerid);
		if (drunknew < 100)
		{ // go back up, keep cycling.
			SetPlayerDrunkLevel(playerid, 2000);
		}
		else
		{
			if (pDrunkLevelLast[playerid] != drunknew)
			{
				new wfps = pDrunkLevelLast[playerid] - drunknew;
				if ((wfps > 0) && (wfps < 200))
				pFPS[playerid] = wfps;
				pDrunkLevelLast[playerid] = drunknew;
			}
		}
		//
		LastUpdate[playerid] = GetTickCount ();

	    UnknownUpdate(playerid);

		if (InfoPersonaje[playerid][pModoAfk] > 300)
		{
			new string[128];
			format(string, sizeof string, "Has estado en pausa por %s.", Segundos_tiempo(InfoPersonaje[playerid][pModoAfk]));
			SendPlayerChatMessage(playerid, COLOR_YELLOW, string);
		}
		InfoPersonaje[playerid][pModoAfk] = 0;

		//actualiza vida & chaleco como pequeño anticheat
		SetPlayerArmour(playerid, InfoPersonaje[playerid][pChaleco]);
		if (GetPVarInt(playerid, "EstaCrack") == 0) SetPlayerHealth(playerid, InfoPersonaje[playerid][pVida]);
		else SetPlayerHealth(playerid, 15.0);

		// Inventory
		UpdateInv(playerid);

		//otros
		if (GetPVarInt(playerid, "IsFrozen") == 1) TogglePlayerControllable(playerid, 0);

		//sync
		for (new i = 0; i < MAX_SYNC_TYPES; ++i)
		{
		    if (InfoSync[playerid][i][sTimeSync])
		    {
		        if (LastUpdate[playerid] - InfoSync[playerid][i][sLastSyncUpdate] > 1000)
		        {
		            InfoSync[playerid][i][sTimeSync]--;
		            InfoSync[playerid][i][sLastSyncUpdate] = LastUpdate[playerid];
		        }
		    }
		}
		
		//vehicle teleport (type 2)
		if (cheat_Vehicle2teleport != 0)
		{
			new ivar = GetPlayerState(playerid);
			new vehicleid = GetPlayerVehicleID(playerid);
			if (ivar == PLAYER_STATE_DRIVER)
			{
				if (LastVehicle[playerid] != 0 && vehicleid != 0)
				{
					if (LastVehicle[playerid] != vehicleid)
					{
						if (!InfoSync[playerid][SYNC_TYPE_POS][sTimeSync])
						{
				 			Adv2Vehs[playerid]++;
			 		   		if (Adv2Vehs[playerid] >= 2)
		 		   			{
								CheatDetected(playerid, "Vehicle teleport (type 2)", 2);
								//JB::Ban (playerid, "Vehicle teleport");
								return 1;
							}
							else
							{
							    new string[240];
								format(string, sizeof string, "Vehicle teleport con %s (type 2)", GetVehicleName(vehicleid));
								CheatDetected(playerid, string, 1);
							}
						}
					}
				}
				LastVehicle[playerid] = vehicleid;
			}
		}
	} // } end
	return 1;
}

funcion SyncPlayerTime(playerid)
{
//	new hour, minute, second;
//	gettime(hour, minute, second);
	if(pDroga[playerid][EfectoLSD] == 0 && pDroga[playerid][EfectoHongo] == 0 && pDroga[playerid][EfectoMDMA] == 0 && pDroga[playerid][EfectoEspecialUWU] == 0){
		SetPlayerTime(playerid, xHora, xMinuto);
	}
	return 1;
}

Random(min, max)
{
    new a = random(max - min) + min;
    return a;
}

ReturnUser(const text[])
{
	new strPos, returnID = 0, bool: isnum = true;
	while (text[strPos])
	{
		if (isnum)
		{
			if ('0' <= text[strPos] <= '9') returnID = (returnID * 10) + (text[strPos] - '0');
			else isnum = false;
		}
		strPos++;
	}
	if (isnum)
	{
		if (IsPlayerConnected(returnID)) return returnID;
	}
	else
	{
		new sz_playerName[MAX_PLAYER_NAME];
		foreach(Player, i)
		{
			GetPlayerName(i, sz_playerName, MAX_PLAYER_NAME);
			if (!strcmp(sz_playerName, text, true, strPos)) return i;
		}
	}
	return INVALID_PLAYER_ID;
}

IsValidSkin(skinid)
{
	switch (skinid)
	{
		case 1..73: return 1;
		case 74: return 0;
		case 75..311: return 1;
	}
	return 0;
}

stock GetClosestCar(playerid, exception = INVALID_VEHICLE_ID) {
    new
		Float:Distance,
		target = -1;
    for(new v; v < GetVehiclePoolSize(); v++) if(GetVehicleModel(v)) {
        if(v != exception && (target < 0 || Distance > GetDistancePlayerVeh(playerid, v))) {
            target = v;
            Distance = GetDistancePlayerVeh(playerid, v);
        }
    }
    return target;
}

stock IsPlayerInRangeOfVehicle(playerid, vehicleid, Float: radius) {
	new
		Float:Floats[3];
	GetVehiclePos(vehicleid, Floats[0], Floats[1], Floats[2]);
	return IsPlayerInRangeOfPoint(playerid, radius, Floats[0], Floats[1], Floats[2]);
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
    return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (GetPlayerAdmin(playerid, 3) != 0)
	{
	 	new message[480];
		format(message, 256, "Fuiste teletransportado a la posición que marcaste: %f %f %f", fX, fY, fZ);
		SetPlayerInterior(playerid, 0);
		SendPlayerChatMessage(playerid, 0xEBEBEBFF, message);
	    SetPlayerPosFindZ(playerid, fX, fY, fZ);
		if(IsPlayerInAnyVehicle(playerid))
		{
			SetVehiclePos(GetPlayerVehicleID(playerid), fX, fY, fZ);
			PutPlayerInVehicle(playerid, GetPlayerVehicleID(playerid), GetPlayerVehicleSeat(playerid));
		}
	}
    return 1;
}

forward TimerKICK(playerid);
public TimerKICK(playerid)
{
	Kick(playerid);
	return 1;
}

stock RandomEx(min, max)
{
    new randval = random(max - min) + min;
    return randval;
}

stock IsWeaponWithAmmo(weaponid)
{
	switch(weaponid)
	{
		case 16..18, 22..39, 41..42: return 1;
		default: return 0;
	}
	return 0;

}

stock GetPlayerWeaponAmmo(playerid,weaponid)
{
	new wd[2][13];
	for(new i; i<13; i++) GetPlayerWeaponData(playerid,i,wd[0][i],wd[1][i]);
	for(new i; i<13; i++)
	{

		if(weaponid == wd[0][i]) return wd[1][i];
	}
	return 0;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	//xx
	if (hittype==BULLET_HIT_TYPE_PLAYER)
	{
		if (!(-100.0<=fX<=100.0)||!(-1000.0<=fY<=100.0)||!(-100.0<=fZ<=100.0))
		{
			//kickorbanthecrasher
			return 0b0;
		}
	}
	//
	if (IsPlayerConnectedEx(playerid))
	{
		new idobj = InfoPersonaje[playerid][pManoDerecha];/* balas = GetPlayerAmmo(playerid);*/
		if (IsWeaponWithAmmo(weaponid))
		{
			if (cheat_weapons != 0 && InfoInventario[idobj][IDArma] != weaponid && InfoPersonaje[playerid][pHorasOn] <= 5) // "armas invisibles"
			{
			    CheatDetected(playerid, "Arma no sincronizada", 2);
				return 1;
			}
			if (InfoPersonaje[playerid][pManoDerechaCant])
			{
				InfoPersonaje[playerid][pManoDerechaCant]--;
				if (GetPlayerWeaponAmmo(playerid, InfoInventario[idobj][IDArma]) != 0 && GetPlayerWeaponAmmo(playerid, InfoInventario[idobj][IDArma]) < InfoPersonaje[playerid][pManoDerechaCant])
				{
					InfoPersonaje[playerid][pManoDerechaCant] = GetPlayerWeaponAmmo(playerid, InfoInventario[idobj][IDArma]);
				}
				if (InfoPersonaje[playerid][pManoDerechaCant] == 0) // remueve arma si no tienes balas, si continua disparando abajo está el check para dar kick <-
				{
					ResetPlayerWeapons(playerid);
				}
			}
			else
			{
				Anti[playerid][BalasW]++;
				ResetPlayerWeapons(playerid);
			   	if(cheat_balas != 0 && Anti[playerid][BalasW] == 3 && AntiG[Balas]) // 3 advertencias de tolerancia ^^
			    {
					if (CheatDetected(playerid, "Cheat de balas (type 1)", 2) == 1)
						QuitarManos(playerid);
					return 1;
				}
			}
		}
		if (InfoPersonaje[playerid][pManoDerecha] == 40 && weaponid == 23)
		{
			TaserRecarga[playerid] = 1;
			SetTimerEx("RecargarTaser", 5000, false, "i", playerid);
		}
	}
    return 1;
}

forward RecargarTaser(playerid);
public RecargarTaser(playerid)
{
	TaserRecarga[playerid] = 0;
	return 1;
}

forward _FGomas(playerid);
public _FGomas(playerid)
{
	ClearAnimations(playerid);
	TogglePlayerControllable(playerid, 1);
	ConBalasGoma[playerid] = 0;
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	return 1;
}

stock Float:GetRealDistance(playerid, playerid2, unit)
{
	new Float:Pos[3], Float:Pos2[3], Float:converter;
    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
    GetPlayerPos(playerid2, Pos2[0], Pos2[1], Pos2[2]);

	Pos[0] -= Pos2[0];
	Pos[1] -= Pos2[1];
	Pos[2] -= Pos2[2];

	switch(unit)
	{
        case 0: converter = 1.0; // Metros
        case 1: converter = 1.0/1000.0; // Kilómetros
        case 2: converter = (1.0/1000.0)/1.6; // Millas
        case 3: converter = 100.0; // Centímetros
        case 4: converter = 39.3701; // Pulgadas
    }
    return floatsqroot((Pos[0]*Pos[0]) + (Pos[1]*Pos[1]) + (Pos[2]*Pos[2]))*converter;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	switch (weaponid)
	{
		case 49,50,53,54: //caidas y varios
		{
			if (AdminDuty[playerid] == 1) return 1;
			player_weapon[playerid] = weaponid;
			player_asesino[playerid] = issuerid;
			quitar_vida(playerid, -amount);
			return 1;
		}
	}
	if (playerid != INVALID_PLAYER_ID)
	{
		if (!IsPlayerConnected(playerid)) { return 1; }
		if (GetPlayerTeam(issuerid) == GetPlayerTeam(playerid))
		{
			if (AdminDuty[playerid] == 1) return 1;
			if (GetPlayerState(playerid) == PLAYER_STATE_WASTED) return 1;
			if (InfoPersonaje[playerid][pMuerto] == 2) return 1;
			
			//una vez muerto
			if(InfoPersonaje[playerid][pEstado] == 2)
			{
				return 0;
			}

			//anticheat
			if (InfoInventario[InfoPersonaje[issuerid][pManoDerecha]][IDArma] != weaponid && weaponid != 0)
			{
				if (cheat_weapons != 0)
				{
				 	advWeapons[issuerid]++;
		 		    if (advWeapons[issuerid] >= 2)
		 		    {
		 			    CheatDetected(issuerid, "Cheat de armas", 2);
		 		        return 1;
		 		    }
		 		    else //posible
		 		    {
						CheatDetected(issuerid, "Cheat de armas", 1);
		 		    }
				}
			    return 1;
			}
			if (weaponid != 0) advWeapons[playerid] = 0;
			//news
			new
				Float:armour = InfoPersonaje[playerid][pChaleco], Float:damage;
			//daños
			if(amount == 2.64 && (weaponid > 21 && weaponid < 34))
			{
				damage = 3.5;
			}
			else
			{
				switch (weaponid)
				{
					case 0: damage = amount; //puños
					case 1: damage = amount; //nudillera
					case 2,3,5..7: //palo de golf, porra, bate, pala, palo de billar
					{
						damage = amount;
					}
					case 4: damage = 15.0; //navaja
					case 8,9: damage = 35.0; //katana y motosierra
					case 10..15: damage = amount; //dildos, flor, palanca
					case 22,23: //colt, silenciadora
					{
						if (InfoPersonaje[issuerid][pManoDerecha] == 40) //táser
						{
							if (!CercaDelWeon(8.0, issuerid, playerid)) return SendPlayerChatMessage(issuerid, COLOR_GREY, "* No lograste tasear al jugador, está muy lejos.");
							if (IsPlayerInAnyVehicle(playerid) && EnMotos_Bicis(GetPlayerVehicleID(playerid))) { RemovePlayerFromVehicle(playerid); }
							new string[128];
							TogglePlayerControllable(playerid, 0);
							Taseado[playerid] = 1;
							PlayerAudio(playerid, 6003, 8.0);
							format(string, sizeof string, "%s te ha paralizado con cables de táser.", GetNameFormat(issuerid));
							SendPlayerChatMessage(playerid, COLOR_GREEN, string);
							format(string, sizeof string, "Has paralizado con cables de táser a %s. (Usa /qcables %d)", GetNameFormat(playerid), issuerid);
							SendPlayerChatMessage(issuerid, COLOR_GREEN, string);
							return 1;
						}
						switch (bodypart)
						{
							case 9, 3: damage = 16.0;
							case 8, 7, 4: damage = 11.25;
							case 6, 5: damage = 13.0;
						}
					}
					case 24: //eagle
					{
						switch (bodypart)
						{
							case 9, 3: damage = 38.0;
							case 8, 7, 4: damage = 25.55;
							case 6, 5: damage = 28.0;
						}
					}
					case 25, 26, 27: //escopetas
					{
						if (InfoPersonaje[issuerid][pManoDerecha] == 54)
						{
							new string[128];
							if (ConBalasGoma[playerid] == 1) return 1;
							if (IsPlayerInAnyVehicle(playerid))
							{
								if (EnMotos_Bicis(GetPlayerVehicleID(playerid)))
								{
									TogglePlayerControllable(playerid, 0);
									RemovePlayerFromVehicle(playerid);
									ConBalasGoma[playerid] = 1;
									format(string, sizeof string, "%s te ha paralizado con balas de goma, 15 segundos para pasar efecto.", GetNameFormat(issuerid));
									SendPlayerChatMessage(playerid, 0x00CF00FF, string);
									format(string, sizeof string, "Has paralizado con balas de goma a %s.", GetNameFormat(playerid));
									SendPlayerChatMessage(issuerid, 0x00CF00FF, string);
									TogglePlayerControllable(playerid, 0);
									SetTimerEx("_FGomas", 15000, false, "i", playerid);
								}
								else { return 1; }
							}
							else
							{
								TogglePlayerControllable(playerid, 0);
								ConBalasGoma[playerid] = 1;
								format(string, sizeof string, "%s te ha paralizado con balas de goma, 15 segundos para pasar efecto.", GetNameFormat(issuerid));
								SendPlayerChatMessage(playerid, 0x00CF00FF, string);
								format(string, sizeof string, "Has paralizado con balas de goma a %s.", GetNameFormat(playerid));
								SendPlayerChatMessage(issuerid, 0x00CF00FF, string);
								TogglePlayerControllable(playerid, 0);
								SetTimerEx("_FGomas", 15000, false, "i", playerid);
							}
						}
						else
						{
							switch (bodypart)
							{
								case 9, 3: damage = 45.0;
								case 8, 7, 4: damage = 35.0;
								case 6, 5: damage = 38.0;
							}
						}
					}
					case 28, 32: //mac-10 y tec-9
					{
						switch (bodypart)
						{
							case 9, 3: damage = 18.0;
							case 8, 7, 4: damage = 11.55;
							case 6, 5: damage = 12.90;
						}
					}
					case 29: //mp5
					{
						switch (bodypart)
						{
							case 9, 3: damage = 24.0;
							case 8, 7, 4: damage = 15.0;
							case 6, 5: damage = 19.90;
						}
					}
					case 30: //ak47
					{
						switch (bodypart)
						{
							case 9, 3: damage = 34.50;
							case 8, 7, 4: damage = 24.0;
							case 6, 5: damage = 28.90;
						}
					}
					case 31: //m4
					{
						switch (bodypart)
						{
							case 9, 3: damage = 30.0;
							case 8, 7, 4: damage = 22.0;
							case 6, 5: damage = 25.9;
						}
					}

					case 33: //rifle caza
					{
						switch (bodypart)
						{
							case 9, 3: damage = 49.0;
							case 8, 7, 4: damage = 25.90;
							case 6, 5: damage = 29.90;
						}
					}
					case 34: //francotirador
					{
						switch (bodypart)
						{
							case 9, 3: damage = 49.0;
							case 8, 7, 4: damage = 35.0;
							case 6, 5: damage = 39.0;
						}
					}
					case 41: if (member_faccion(issuerid, 1, 2, 3, 4)) damage = 0.33; //spray
					default: damage = amount;
				}
			}

			new si_hs = 0;
			if (bodypart == 9 && (weaponid >= 22 && weaponid <= 34))
			{
				new Float:distance = GetRealDistance(playerid, issuerid, 0);
				if (distance <= 12.0)
				{
				    si_hs = 1;
				}
				switch (weaponid)
				{
					case 22,23: damage = 90.0;
					case 24: damage = 90.0;
					case 25: damage = 90.0;
					case 26: damage = 90.0;
					case 27: damage = 90.0;
					case 28: damage = 90.0;
					case 29: damage = 90.0;
					case 30: damage = 90.0;
					case 31: damage = 90.0;
					case 32: damage = 90.0;
				}
			}

			if(weaponid >=  22){
				if(pDroga[playerid][TiempoCocaina] > 0) damage-= pDroga[playerid][EfectoCocaina]*3.0;
			} // - daño con la cocaina

			//vida y chaleco
			VecesHerido[playerid]++;
			if ((weaponid > 21 && weaponid < 35) && (bodypart == 3 || bodypart == 4) && armour)
			{
				if (armour > damage)
				{
					InfoPersonaje[playerid][pChaleco] = armour-damage;
				}
				else
				{
					InfoPersonaje[playerid][pChaleco] = 0.0;
					armour = damage-armour;
					quitar_vida(playerid, -armour);
				}
				guardar_float_mysql("personajes", "Chaleco", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pChaleco]);
			}
			else
			{
			    if (bodypart == 9)
			    {
					if (si_hs == 1) quitar_vida(playerid, -damage);
					else
					{
						if (armour > damage)
						{
							InfoPersonaje[playerid][pChaleco] = armour-damage;
						}
						else
						{
							InfoPersonaje[playerid][pChaleco] = 0.0;
							armour = damage-armour;
							quitar_vida(playerid, -armour);
						}
						guardar_float_mysql("personajes", "Chaleco", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pChaleco]);
					}
			    }
			    else
			    {
					quitar_vida(playerid, -damage);
				}
			}
		    //heridas
			player_weapon[playerid] = weaponid;
			player_asesino[playerid] = issuerid;
		    Loop(e, MAX_HERIDAS, 0) if (InfoHerida[playerid][e][dmgDamage] == 0)
			{
				InfoHerida[playerid][e][dmgWeapon] = weaponid;
				InfoHerida[playerid][e][dmgBodypart] = bodypart;
				InfoHerida[playerid][e][dmgSeconds] = gettime();
			    InfoHerida[playerid][e][dmgDamage] = floatround(damage);
				e = MAX_HERIDAS;
			}
	
			
		}
	}
	return 1;
}

PonerInconsciente(playerid)
{
    InfoPersonaje[playerid][pEstado] = 2;

    SetPlayerHealth(playerid, 10.0);

    TogglePlayerControllable(playerid, false);
    ClearAnimations(playerid, 1);

    ApplyAnimation(playerid, "PED", "FLOOR_hit", 4.1, 0, 0, 0, 1, 0, 1);

    PlayerTextDrawSetString(playerid, p_tdMuerte[playerid][1], "Estas inconsciente.");

    PlayerTextDrawShow(playerid, p_tdMuerte[playerid][0]);
    PlayerTextDrawShow(playerid, p_tdMuerte[playerid][1]);
	SetTimerEx("Despertar", 20000, false, "i", playerid);
    return 1;
}

forward Despertar(playerid);
public Despertar(playerid)
{
	PlayerTextDrawHide(playerid, p_tdMuerte[playerid][0]);
    PlayerTextDrawHide(playerid, p_tdMuerte[playerid][1]);
    PlayerTextDrawHide(playerid, p_tdMuerte[playerid][2]);
	TogglePlayerControllable(playerid, true);
	ClearAnimations(playerid, 1);
	InfoPersonaje[playerid][pEstado] = 0;
	guardar_int_mysql("personajes", "Estado", InfoPersonaje[playerid][pID], InfoPersonaje[playerid][pEstado]);
	return 1;
}

Rematar(playerid)
{
    InfoPersonaje[playerid][pEstado] = 2;

    ClearAnimations(playerid, 1);
    ApplyAnimation(playerid, "PED", "KO_shot_front", 4.1, 0, 0, 0, 1, 0, 1);

    SetPlayerHealth(playerid, 0.0);
    TogglePlayerControllable(playerid, false);

    PlayerTextDrawSetString(playerid, p_tdMuerte[playerid][1], "Has muerto.");
    PlayerTextDrawSetString(playerid, p_tdMuerte[playerid][2], "Espera 2 minutos para usar /reaparecer");
    return 1;
}

public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if (!response) return 1;
	if (extraid == Create_VehObject)
	{
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
		new obj = CreatePlayerObject(playerid, modelid, X+1.0, Y+1.0, Z, 0.0, 0.0, 0.0, 100.0);
		SetPVarInt(playerid, "FurnModelo", modelid);
		SetPVarInt(playerid, "FurnObject", obj);
		SetPVarInt(playerid, "EditorMode", 1);
		EditPlayerObject(playerid, obj);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, "* Mantén presionado {3E62F4}~k~~PED_SPRINT~{FFFFFF} para cambiar la posición de la cámara.");
	}
	//
	else if (extraid == Actor_Skin)
	{
		new id = actore_skin[playerid], string[240];
		InfoNegocio[id][nActorSkin] = modelid;
		guardar_int_mysql("negocios", "ActorSkin", InfoNegocio[id][nID_sql], InfoNegocio[id][nActorSkin]);
		if (InfoNegocio[id][nActorX] != 0.0)
		{
			LabelPickup_negocio(id, 0, 0, 1, 0);
		}
		format(string, sizeof string, "Cambiaste el skin del actor (%d) del negocio %d.", modelid, id);
		SendPlayerChatMessage(playerid, COLOR_WHITE, string);
		return 1;
	}
	else if (extraid == VIP_Skin)
	{
		GivePlayerSkin(playerid, modelid);
		return 1;
	}
	else if (extraid == Equipo_Skin)
	{
		GivePlayerJobSkin(playerid, modelid);
		if (member_faccion(playerid, 1, 2, 3, 4, 5)) rol_ame(playerid, "se viste con ropa del casillero.");
		else rol_ame(playerid, "se viste con ropa del armario.");
		return 1;
	}
	else if (extraid == IDObj_Admin)
	{
		new id = edicion_sql_actual[playerid];
		if (id == -1) return SendPlayerChatMessage(playerid, -1, "ERROR, avisale al desarrollador.");
		Creando_Objeto_Admin(playerid, id, modelid);
		return 1;
	}
	else if (extraid == Clinica_Skin)
	{
		GivePlayerJobSkin(playerid, modelid);
		rol_ame(playerid, "se viste con ropa del casillero.");
		return 1;
	}
	else if (extraid == Compra_Skin)
	{
		if (CheckMoney(playerid, 100) == 0) return 1;
		GivePlayerSkin(playerid, modelid);
		if (GetPlayerVirtualWorld(playerid) != 0)
		{
			GivePlayerCash(playerid, -100, "compra de skin");
			CobroNegocio(id_negocio[playerid], 100);
		}
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, "Compraste ropa nueva, costo: {00CC00}$100{FFFFFF}.");
		return 1;
	}
	else if (extraid == Compra_Toy)
	{
		new idtoy = -1;
		Loop(uwu, sizeof InfoToy, 0) if (InfoToy[uwu][accModelo] == modelid)
		{
			idtoy = uwu;
			break;
		}
		if (idtoy == -1) return 1;
		new precio = InfoToy[idtoy][accPrecio], gformat[340];
		if (GetPlayerCash(playerid) < precio)
		{
			format(gformat, sizeof gformat, "Te hacen falta $%s para comprar %s por $%s.", diner_coma(precio-GetPlayerCash(playerid)), InfoToy[idtoy][accNombre], diner_coma(precio));
			SendPlayerChatMessage(playerid, COLOR_GREY, gformat);
			return 1;
		}
		new x = slotselection[playerid];
		InfoPersonaje[playerid][ptModelo][x] = modelid;
		if ((modelid >= 19006 && modelid <= 19035) || (modelid >= 19138 && modelid <= 19140))
		{
			InfoPersonaje[playerid][ptHueso][x] = 2;
			InfoPersonaje[playerid][ptPosX][x] = 0.9;
			InfoPersonaje[playerid][ptPosY][x] = 0.0;
			InfoPersonaje[playerid][ptPosZ][x] = 0.35;
			InfoPersonaje[playerid][ptRotX][x] = 90.0;
			InfoPersonaje[playerid][ptRotY][x] = 90.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if (modelid >= 18891 && modelid <= 18910)
		{
			InfoPersonaje[playerid][ptHueso][x] = 2;
			InfoPersonaje[playerid][ptPosX][x] = 0.15;
			InfoPersonaje[playerid][ptPosY][x] = 0.0;
			InfoPersonaje[playerid][ptPosZ][x] = 0.0;
			InfoPersonaje[playerid][ptRotX][x] = 90.0;
			InfoPersonaje[playerid][ptRotY][x] = 180.0;
			InfoPersonaje[playerid][ptRotZ][x] = 90.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if (modelid >= 18926 && modelid <= 18935)
		{
			InfoPersonaje[playerid][ptHueso][x] = 2;
			InfoPersonaje[playerid][ptPosX][x] = 0.1;
			InfoPersonaje[playerid][ptPosY][x] = 0.0;
			InfoPersonaje[playerid][ptPosZ][x] = 0.0;
			InfoPersonaje[playerid][ptRotX][x] = 0.0;
			InfoPersonaje[playerid][ptRotY][x] = 0.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if (modelid >= 18911 && modelid <= 18920)
		{
			InfoPersonaje[playerid][ptHueso][x] = 2;
			InfoPersonaje[playerid][ptPosX][x] = 0.1;
			InfoPersonaje[playerid][ptPosY][x] = 0.035;
			InfoPersonaje[playerid][ptPosZ][x] = 0.0;
			InfoPersonaje[playerid][ptRotX][x] = 90.0;
			InfoPersonaje[playerid][ptRotY][x] = 180.0;
			InfoPersonaje[playerid][ptRotZ][x] = 90.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if (modelid == 19078 || modelid == 19078)
		{
			InfoPersonaje[playerid][ptHueso][x] = 16;
			InfoPersonaje[playerid][ptPosX][x] = 0;
			InfoPersonaje[playerid][ptPosY][x] = 0;
			InfoPersonaje[playerid][ptPosZ][x] = 0;
			InfoPersonaje[playerid][ptRotX][x] = 180.0;
			InfoPersonaje[playerid][ptRotY][x] = 180.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if ((modelid >= 18641 && modelid <= 18644) || (modelid >= 19080 && modelid <= 19084) || modelid == 18890)
		{
			InfoPersonaje[playerid][ptHueso][x] = 6;
			InfoPersonaje[playerid][ptPosX][x] = 0.0;
			InfoPersonaje[playerid][ptPosY][x] = 0.0;
			InfoPersonaje[playerid][ptPosZ][x] = 0.0;
			InfoPersonaje[playerid][ptRotX][x] = 0.0;
			InfoPersonaje[playerid][ptRotY][x] = 0.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else if (modelid == 19317)
		{
			InfoPersonaje[playerid][ptHueso][x] = 1;
			InfoPersonaje[playerid][ptPosX][x] = 0.079;
			InfoPersonaje[playerid][ptPosY][x] = -0.10;
			InfoPersonaje[playerid][ptPosZ][x] = 0.09;
			InfoPersonaje[playerid][ptRotX][x] = 0.0;
			InfoPersonaje[playerid][ptRotY][x] = 30.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		else
		{
			InfoPersonaje[playerid][ptHueso][x] = 2;
			InfoPersonaje[playerid][ptPosX][x] = 0.0;
			InfoPersonaje[playerid][ptPosY][x] = 0.0;
			InfoPersonaje[playerid][ptPosZ][x] = 0.0;
			InfoPersonaje[playerid][ptRotX][x] = 0.0;
			InfoPersonaje[playerid][ptRotY][x] = 0.0;
			InfoPersonaje[playerid][ptRotZ][x] = 0.0;
			InfoPersonaje[playerid][ptScaleX][x] = 1;
			InfoPersonaje[playerid][ptScaleY][x] = 1;
			InfoPersonaje[playerid][ptScaleZ][x] = 1;
		}
		ActualizarToy(playerid, x);
		GivePlayerCash(playerid, -precio, "compra de toy");
		format(gformat, sizeof gformat, "* Compraste el toy {FE9A2E}%s{FFFFFF} por {00CC00}$%s{FFFFFF}. Para editarlo: {3E62F4}/toys{FFFFFF}.", InfoToy[idtoy][accNombre], diner_coma(precio));
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, gformat);
		return 1;
	}
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
    if(listid == RoadblockList)
	{
	    if(!response) return 1;
		new id = GetFreeObjectID();
	    if(id == -1) return SendPlayerChatMessage(playerid, 0xFFFFFFFF, "Se alcanzó el límite de objetos.");
	    CopObjectData[id][ObjCreated] = true;
	    GetPlayerName(playerid, CopObjectData[id][Owner], MAX_PLAYER_NAME);
	    CopObjectData[id][Type] = OBJECT_TYPE_ROADBLOCK;
	    CopObjectData[id][ObjModel] = modelid;
	    CopObjectData[id][ObjInterior] = GetPlayerInterior(playerid);
	    CopObjectData[id][ObjVirtualWorld] = GetPlayerVirtualWorld(playerid);

	    new Float: x, Float: y, Float: z, Float: a;
	    GetPlayerPos(playerid, x, y, z);
	    GetPlayerFacingAngle(playerid, a);
	    x += (2.0 * floatsin(-a, degrees));
		y += (2.0 * floatcos(-a, degrees));
		CopObjectData[id][ObjXb] = x;
		CopObjectData[id][ObjYb] = y;
		CopObjectData[id][ObjZb] = z;
		CopObjectData[id][ObjRX] = 0.0;
		CopObjectData[id][ObjRY] = 0.0;
		CopObjectData[id][ObjRZ] = a;
		CopObjectData[id][ObjID] = CreateDynamicObject(modelid, x, y, z, 0.0, 0.0, a, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		CopObjectData[id][ObjArea] = -1;

        new string[123];
		format(string, sizeof(string), "ID: %d", id); //1.35
		CopObjectData[id][ObjLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, x, y, z + 0.0, 10.0, _, _, _, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, "Utiliza /ebar para editar la señal, y /qbar para eliminarla.");
	}
	if(listid == SignList)
	{
	    if(!response) return 1;
		new id = GetFreeObjectID();
	    if(id == -1) return SendPlayerChatMessage(playerid, 0xFFFFFFFF, "Se alcanzó el límite de objetos.");
	    CopObjectData[id][ObjCreated] = true;
	    GetPlayerName(playerid, CopObjectData[id][Owner], MAX_PLAYER_NAME);
	    CopObjectData[id][Type] = OBJECT_TYPE_SIGN;
	    CopObjectData[id][ObjModel] = modelid;
	    CopObjectData[id][ObjInterior] = GetPlayerInterior(playerid);
	    CopObjectData[id][ObjVirtualWorld] = GetPlayerVirtualWorld(playerid);

	    new Float: x, Float: y, Float: z, Float: a;
	    GetPlayerPos(playerid, x, y, z);
	    GetPlayerFacingAngle(playerid, a);
	    x += (2.0 * floatsin(-a, degrees));
		y += (2.0 * floatcos(-a, degrees));
		CopObjectData[id][ObjXb] = x;
		CopObjectData[id][ObjYb] = y;
		CopObjectData[id][ObjZb] = z - 1.25;
		CopObjectData[id][ObjRX] = 0.0;
		CopObjectData[id][ObjRY] = 0.0;
		CopObjectData[id][ObjRZ] = a;
		CopObjectData[id][ObjID] = CreateDynamicObject(modelid, x, y, z - 1.25, 0.0, 0.0, a, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		CopObjectData[id][ObjArea] = -1;

        new string[123];
		format(string, sizeof(string), "ID: %d", id);
		CopObjectData[id][ObjLabel] = CreateDynamic3DTextLabel(string, COLOR_WHITE, x, y, z + 0.0, 10.0, _, _, _, CopObjectData[id][ObjVirtualWorld], CopObjectData[id][ObjInterior]);
		SendPlayerChatMessage(playerid, 0xFFFFFFFF, "Utiliza /ebar para editar la señal, y /qbar para eliminarla.");
		return 1;
	}
	if (listid == ob_muebles)
	{
		if (!response) return pc_cmd_muebles(playerid);
		new OBJ_INDEX, gformat[256];
		buscar_modelo_obj(modelid, OBJ_INDEX);
		MuebleActual[playerid] = modelid;
		format(gformat, sizeof gformat, "{EBEBEB}Modelo {2CE59E}%d{EBEBEB} ({2CE59E}%s{EBEBEB})\nPara agregar este objeto a tu lista de muebles, clic '{3E62F4}continuar{EBEBEB}'", modelid, objetos_interior[OBJ_INDEX][2]);
		Dialog_Show(playerid, Comprar2Muebles, DIALOG_STYLE_MSGBOX, "Nuevo mueble", gformat, "Continuar", "Volver");
		return 1;
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new query[1028], gformat[256];
	if (response == EDIT_RESPONSE_UPDATE) return 1;
	if(EditingCopObjectID[playerid] != -1)
	{
	    new id = EditingCopObjectID[playerid];

	    switch(response)
	    {
			case EDIT_RESPONSE_FINAL:
			{
			    CopObjectData[id][ObjXb] = x;
				CopObjectData[id][ObjYb] = y;
				CopObjectData[id][ObjZb] = z;
				CopObjectData[id][ObjRX] = rx;
				CopObjectData[id][ObjRY] = ry;
				CopObjectData[id][ObjRZ] = rz;
			    SetDynamicObjectPos(objectid, x, y, z);
	            SetDynamicObjectRot(objectid, rx, ry, rz);

	            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, CopObjectData[id][ObjLabel], E_STREAMER_X, x);
	            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, CopObjectData[id][ObjLabel], E_STREAMER_Y, y);
	            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, CopObjectData[id][ObjLabel], E_STREAMER_Z, z + zOffsets[ CopObjectData[id][Type] ]);

	            if(IsValidDynamicArea(CopObjectData[id][ObjArea]))
	            {
	                Streamer_SetFloatData(STREAMER_TYPE_AREA, CopObjectData[id][ObjArea], E_STREAMER_X, x);
		            Streamer_SetFloatData(STREAMER_TYPE_AREA, CopObjectData[id][ObjArea], E_STREAMER_Y, y);
		            Streamer_SetFloatData(STREAMER_TYPE_AREA, CopObjectData[id][ObjArea], E_STREAMER_Z, z + zOffsets[ CopObjectData[id][Type] ]);
	            }

			    EditingCopObjectID[playerid] = -1;
			}

	        case EDIT_RESPONSE_CANCEL:
	        {
	            SetDynamicObjectPos(objectid, CopObjectData[id][ObjXb], CopObjectData[id][ObjYb], CopObjectData[id][ObjZb]);
	            SetDynamicObjectRot(objectid, CopObjectData[id][ObjRX], CopObjectData[id][ObjRY], CopObjectData[id][ObjRZ]);
	            EditingCopObjectID[playerid] = -1;
	        }
	    }
	}
	if (InfoPersonaje[playerid][pEditingMode] == 5)
	{
		if (response == EDIT_RESPONSE_CANCEL)
		{
			if (InfoPersonaje[playerid][pEditingMode] != 0) InfoPersonaje[playerid][pEditingMode] = 0;
		}
	}
	if (InfoPersonaje[playerid][pEditingMode] == 55)
	{
        EditMueble(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
	}
	if (InfoPersonaje[playerid][pEditingMode] == 13) // comando creargraffiti
	{
		new id = edicion_sql_actual[playerid];
		if (id == -1) return SendPlayerChatMessage(playerid, -1, "Error edición.");
		if (objectid == InfoGraffiti[id][gr_Objeto])
		{
			if (response == EDIT_RESPONSE_FINAL)
			{
				InfoGraffiti[id][gr_PosX] = x;
				InfoGraffiti[id][gr_PosY] = y;
				InfoGraffiti[id][gr_PosZ] = z;
				InfoGraffiti[id][gr_RotX] = rx;
				InfoGraffiti[id][gr_RotY] = ry;
				InfoGraffiti[id][gr_RotZ] = rz;
				SetDynamicObjectPos(InfoGraffiti[id][gr_Objeto], x, y, z);
				SetDynamicObjectRot(InfoGraffiti[id][gr_Objeto], rx, ry, rz);
				format(gformat, sizeof gformat, "Posición de graffiti actualizada correctamente.", id);
				SendPlayerChatMessage(playerid, -1, gformat);
				InfoPersonaje[playerid][pEditingMode] = 0;
				edicion_sql_actual[playerid] = -1;
				//opción idsql ya creada.
				if (InfoGraffiti[id][grID_sql] != 0)
				{
					mysql_format(db_samp, query, sizeof query, "UPDATE graffitis SET PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
					InfoGraffiti[id][gr_PosX],
					InfoGraffiti[id][gr_PosY],
					InfoGraffiti[id][gr_PosZ],
					InfoGraffiti[id][gr_RotX],
					InfoGraffiti[id][gr_RotY],
					InfoGraffiti[id][gr_RotZ],
					InfoGraffiti[id][gr_Interior],
					InfoGraffiti[id][gr_VirtualWorld],
					InfoGraffiti[id][grID_sql]);
					mysql_tquery(db_samp, query);
					return 1;
				}
				mysql_format(db_samp, query, sizeof query, "INSERT INTO graffitis (PotX, PotY, PotZ, RotX, RotY, RotZ, Interior, VirtualWorld) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d')",
				InfoGraffiti[id][gr_PosX],
				InfoGraffiti[id][gr_PosY],
				InfoGraffiti[id][gr_PosZ],
				InfoGraffiti[id][gr_RotX],
				InfoGraffiti[id][gr_RotY],
				InfoGraffiti[id][gr_RotZ],
				InfoGraffiti[id][gr_Interior],
				InfoGraffiti[id][gr_VirtualWorld]);
				mysql_tquery(db_samp, query, "OnGraffitiCreate", "i", id);
			}
			else if (response == EDIT_RESPONSE_CANCEL)
			{
				InfoGraffiti[id][gr_PosX] = 0.0;
				InfoGraffiti[id][gr_PosY] = 0.0;
				InfoGraffiti[id][gr_PosZ] = 0.0;
				InfoGraffiti[id][gr_RotX] = 0.0;
				InfoGraffiti[id][gr_RotY] = 0.0;
				InfoGraffiti[id][gr_RotZ] = 0.0;
				InfoGraffiti[id][gr_Interior] = 0;
				InfoGraffiti[id][gr_VirtualWorld] = 0;
				InfoGraffiti[id][gr_Fecha] = 0;
				if (IsValidDynamicObject(InfoGraffiti[id][gr_Objeto])) DestroyDynamicObject(InfoGraffiti[id][gr_Objeto]);
				InfoGraffiti[id][gr_Objeto] = 0;
				SendPlayerChatMessage(playerid, -1, "Cancelaste la edición de graffiti.");
				InfoPersonaje[playerid][pEditingMode] = 0;
				edicion_sql_actual[playerid] = -1;
			}
		}
	}
	if (InfoPersonaje[playerid][pEditingMode] == 74) // comando crearcajero
	{
		if (response == EDIT_RESPONSE_CANCEL)
		{
			if (InfoPersonaje[playerid][pEditingMode] != 0)
			{
				InfoPersonaje[playerid][pEditingMode] = 0;
				edicion_sql_actual[playerid] = -1;
				return 1;
			}
		}
		else if (response == EDIT_RESPONSE_FINAL)
		{
			new id = edicion_sql_actual[playerid];
			if (InfoCajero[id][atmModelo] == 0) return 1;
			InfoPersonaje[playerid][pEditingMode] = 0;
			InfoCajero[id][atmPotX] = x;
			InfoCajero[id][atmPotY] = y;
			InfoCajero[id][atmPotZ] = z;
			InfoCajero[id][atmRotX] = rx;
			InfoCajero[id][atmRotY] = ry;
			InfoCajero[id][atmRotZ] = rz;
			SetDynamicObjectPos(InfoCajero[id][atmObject], x, y, z);
			SetDynamicObjectRot(InfoCajero[id][atmObject], rx, ry, rz);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Posición finalizada del cajero automático.");
			Label_cajero(id, 1);
			mysql_format(db_samp, query, sizeof query, "UPDATE cajeros SET Modelo = '%d', PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoCajero[id][atmModelo],
			InfoCajero[id][atmPotX],
			InfoCajero[id][atmPotY],
			InfoCajero[id][atmPotZ],
			InfoCajero[id][atmRotX],
			InfoCajero[id][atmRotY],
			InfoCajero[id][atmRotZ],
			InfoCajero[id][atmInterior],
			InfoCajero[id][atmVirtualWorld],
			InfoCajero[id][atmID_sql]);
			mysql_tquery(db_samp, query);
			edicion_sql_actual[playerid] = -1;
			return 1;
		}
	}
	if (InfoPersonaje[playerid][pEditingMode] == 75) // comando crearcontenedor
	{
		if (response == EDIT_RESPONSE_CANCEL)
		{
			if (InfoPersonaje[playerid][pEditingMode] != 0)
			{
				InfoPersonaje[playerid][pEditingMode] = 0;
				edicion_sql_actual[playerid] = -1;
				return 1;
			}
		}
		else if (response == EDIT_RESPONSE_FINAL)
		{
			new id = edicion_sql_actual[playerid];
			if (InfoContenedor[id][contModelo] == 0) return 1;
			InfoPersonaje[playerid][pEditingMode] = 0;
			InfoContenedor[id][contPotX] = x;
			InfoContenedor[id][contPotY] = y;
			InfoContenedor[id][contPotZ] = z;
			InfoContenedor[id][contRotX] = rx;
			InfoContenedor[id][contRotY] = ry;
			InfoContenedor[id][contRotZ] = rz;
			SetDynamicObjectPos(InfoContenedor[id][contObject], x, y, z);
			SetDynamicObjectRot(InfoContenedor[id][contObject], rx, ry, rz);
			SendPlayerChatMessage(playerid, COLOR_YELLOW, "Posición finalizada del contenedor dinámico.");
			Label_contenedor(id, 1);
			mysql_format(db_samp, query, sizeof query, "UPDATE contenedores SET Modelo = '%d', PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d' WHERE ID = '%d'",
			InfoContenedor[id][contModelo],
			InfoContenedor[id][contPotX],
			InfoContenedor[id][contPotY],
			InfoContenedor[id][contPotZ],
			InfoContenedor[id][contRotX],
			InfoContenedor[id][contRotY],
			InfoContenedor[id][contRotZ],
			InfoContenedor[id][contInterior],
			InfoContenedor[id][contVirtualWorld],
			InfoContenedor[id][contID_sql]);
			mysql_tquery(db_samp, query);
			edicion_sql_actual[playerid] = -1;
			return 1;
		}
	}
	if (InfoPersonaje[playerid][pEditingMode] == 4) // comando mapear
	{
		new id = edicion_sql_actual[playerid];
		if (id == -1) return SendPlayerChatMessage(playerid, -1, "Error edición.");
		if (objectid == InfoObjeto[id][oObjeto])
		{
			if (response == EDIT_RESPONSE_FINAL)
			{
				InfoObjeto[id][oPotX] = x;
				InfoObjeto[id][oPotY] = y;
				InfoObjeto[id][oPotZ] = z;
				InfoObjeto[id][oRotX] = rx;
				InfoObjeto[id][oRotY] = ry;
				InfoObjeto[id][oRotZ] = rz;
				SetDynamicObjectPos(InfoObjeto[id][oObjeto], x, y, z);
				SetDynamicObjectRot(InfoObjeto[id][oObjeto], rx, ry, rz);
				InfoPersonaje[playerid][pEditingMode] = 0;
				SendPlayerChatMessage(playerid, -1, "Edición terminada.");
				edicion_sql_actual[playerid] = -1;
				mysql_format(db_samp, query, sizeof query, "UPDATE objetos_admin SET PotX = '%f', PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f' WHERE ID = '%d'",
				InfoObjeto[id][oPotX],
				InfoObjeto[id][oPotY],
				InfoObjeto[id][oPotZ],
				InfoObjeto[id][oRotX],
				InfoObjeto[id][oRotY],
				InfoObjeto[id][oRotZ],
				InfoObjeto[id][oID_sql]);
				mysql_tquery(db_samp, query);
				return 1;
			}
			else if (response == EDIT_RESPONSE_CANCEL)
			{
				SetDynamicObjectPos(InfoObjeto[id][oObjeto], InfoObjeto[id][oPotX], InfoObjeto[id][oPotY], InfoObjeto[id][oPotZ]);
				SetDynamicObjectRot(InfoObjeto[id][oObjeto], InfoObjeto[id][oRotX], InfoObjeto[id][oRotY], InfoObjeto[id][oRotZ]);
				InfoPersonaje[playerid][pEditingMode] = 0;
				edicion_sql_actual[playerid] = -1;
				SendPlayerChatMessage(playerid, -1, "Cancelaste la edición del objeto dinámico admin.");
				return 1;
			}
		}
	}
	return 1;
}

forward Float:GetDistanceFromPointToPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);
public Float:GetDistanceFromPointToPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

public OnPlayerEditObject(playerid, playerobject, objectid, response, Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ) // Nueva POS.
{
	if (response != EDIT_RESPONSE_FINAL && response != EDIT_RESPONSE_CANCEL) return true;
	if (GetPVarInt(playerid, "FurnObject") != 0) DestroyPlayerObject(playerid, GetPVarInt(playerid, "FurnObject"));
	switch (GetPVarInt(playerid, "EditorMode"))
	{
		case 1: //Vehicle furn
		{
			if (GetPVarInt(playerid, "FurnObject") != 0) DestroyPlayerObject(playerid, GetPVarInt(playerid, "FurnObject"));
			if (!response)
			{
				DeletePVar(playerid, "FurnVehicleID");
				return 1;
			}
			new id = GetPVarInt(playerid, "FurnVehicleID");
			new vehicleid = InfoVehiculo[id][vIG_id];
			new modelo = GetPVarInt(playerid, "FurnModelo");
			DeletePVar(playerid, "FurnVehicleID");
			if (vehicleid == 0) { return 1; } //Just incase.
			new Float:pos[3];
			GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
			new Float:distance = GetDistanceFromPointToPoint(fX, fY, fZ, pos[0], pos[1], pos[2]);
			if (distance > 10.0)
			{
				SendPlayerChatMessage(playerid, COLOR_LIGHTRED, "El objeto está demasiado lejos del vehículo y no se pudo poner!");
				return 1;
			}
			Loop(i, 5, 0) if (InfoVehiculo[id][vObjModelo][i] == 0)
			{
				InfoVehiculo[id][vTuneo][i] = CreateDynamicObject(modelo, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
				new Float:offset[3];
				GetOffsetFromVehicle(fX, fY, fZ, vehicleid, offset[0], offset[1], offset[2]);
				new Float:rotz;
				GetVehicleZAngle(vehicleid, rotz);
				InfoVehiculo[id][vObjPosX][i] = offset[0];
				InfoVehiculo[id][vObjPosY][i] = offset[1];
				InfoVehiculo[id][vObjPosZ][i] = offset[2];
				InfoVehiculo[id][vObjRotZ][i] = fRotZ-rotz;
				AttachDynamicObjectToVehicle(InfoVehiculo[id][vTuneo][i], vehicleid, offset[0], offset[1], offset[2], fRotX, fRotY, fRotZ-rotz);
				Streamer_Update(playerid);
				InfoVehiculo[id][vObjModelo][i] = modelo;
				InfoVehiculo[id][vObjRotX][i] = fRotX;
				InfoVehiculo[id][vObjRotY][i] = fRotY;
				new query[1028];
				mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET ObjModelo_%d = '%d', ObjPosX_%d = '%f', ObjPosY_%d = '%f', ObjPosZ_%d = '%f', ObjRotX_%d = '%f', ObjRotY_%d = '%f', ObjRotZ_%d = '%f' WHERE ID = '%d'",
				i+1, InfoVehiculo[id][vObjModelo][i], i+1, InfoVehiculo[id][vObjPosX][i], i+1, InfoVehiculo[id][vObjPosY][i], i+1, InfoVehiculo[id][vObjPosZ][i], i+1, InfoVehiculo[id][vObjRotX][i], i+1, InfoVehiculo[id][vObjRotY][i], i+1, InfoVehiculo[id][vObjRotZ][i], InfoVehiculo[id][vID_sql]);
				mysql_tquery(db_samp, query);
				break;
			}
			SendPlayerChatMessage(playerid, COLOR_GENERAL, "Agregaste un nuevo objeto a tu vehículo, posiciones guardadas.");
		}
		case 2: //Vehicle furn
		{
			if (GetPVarInt(playerid, "FurnObject") != 0) DestroyPlayerObject(playerid, GetPVarInt(playerid, "FurnObject"));
			new id = GetPVarInt(playerid, "FurnVehicleID");
			new vehicleid = InfoVehiculo[id][vIG_id];
			if (!response)
			{
				DeletePVar(playerid, "FurnVehicleID");
				Colocar_Objeto(id, vehicleid);
				Streamer_Update(playerid);
				return 1;
			}
			new modelo = GetPVarInt(playerid, "FurnModelo");
			new i = GetPVarInt(playerid, "FurnSlotObj");
			DeletePVar(playerid, "FurnVehicleID");
			new Float:pos[3];
			GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
			new Float:distance = GetDistanceFromPointToPoint(fX, fY, fZ, pos[0], pos[1], pos[2]);
			if (distance > 10.0)
			{
				SendPlayerChatMessage(playerid, COLOR_LIGHTRED, "El objeto está demasiado lejos del vehículo y no se pudo editar");
				Colocar_Objeto(id, vehicleid);
				Streamer_Update(playerid);
				return 1;
			}
			InfoVehiculo[id][vTuneo][i] = CreateDynamicObject(modelo, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			new Float:offset[3], Float:rotz, query[1028];
			GetOffsetFromVehicle(fX, fY, fZ, vehicleid, offset[0], offset[1], offset[2]);
			GetVehicleZAngle(vehicleid, rotz);
			InfoVehiculo[id][vObjPosX][i] = offset[0];
			InfoVehiculo[id][vObjPosY][i] = offset[1];
			InfoVehiculo[id][vObjPosZ][i] = offset[2];
			InfoVehiculo[id][vObjRotZ][i] = fRotZ-rotz;
			AttachDynamicObjectToVehicle(InfoVehiculo[id][vTuneo][i], vehicleid, offset[0], offset[1], offset[2], fRotX, fRotY, fRotZ-rotz);
			Streamer_Update(playerid);
			InfoVehiculo[id][vObjModelo][i] = modelo;
			InfoVehiculo[id][vObjRotX][i] = fRotX;
			InfoVehiculo[id][vObjRotY][i] = fRotY;
			mysql_format(db_samp, query, sizeof query, "UPDATE vehiculos SET ObjModelo_%d = '%d', ObjPosX_%d = '%f', ObjPosY_%d = '%f', ObjPosZ_%d = '%f', ObjRotX_%d = '%f', ObjRotY_%d = '%f', ObjRotZ_%d = '%f' WHERE ID = '%d'",
			i+1, InfoVehiculo[id][vObjModelo][i], i+1, InfoVehiculo[id][vObjPosX][i], i+1, InfoVehiculo[id][vObjPosY][i], i+1, InfoVehiculo[id][vObjPosZ][i], i+1, InfoVehiculo[id][vObjRotX][i], i+1, InfoVehiculo[id][vObjRotY][i], i+1, InfoVehiculo[id][vObjRotZ][i], InfoVehiculo[id][vID_sql]);
			mysql_tquery(db_samp, query);
			SendPlayerChatMessage(playerid, COLOR_GENERAL, "Nuevas posiciones del objeto de tu vehículo guardadas.");
		}
	}
	DeletePVar(playerid,"EditorMode");
	return 1;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	return 1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
    new Float:a;
    GetPlayerPos(playerid, x, y, a);
    GetPlayerFacingAngle(playerid, a);
    if (GetPlayerVehicleID(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
    x += (distance * floatsin(-a, degrees));
    y += (distance * floatcos(-a, degrees));
}

KickIPMultiples(playerid) // detector simple
{
	new IP[2][16], ips = 0, string[256];
	GetPlayerIp(playerid, IP[0], 16);
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnected(playerid2))
	{
		GetPlayerIp(playerid2, IP[1], 16);
		if (!strcmp(IP[0], IP[1]))
		{
			ips++;
		}
	}
	if (ips >= 3)
	{
		Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnected(playerid2))
		{
			GetPlayerIp(playerid2, IP[1], 16);
			if (!strcmp(IP[0], IP[1]))
			{
				SendPlayerChatMessage(playerid2, COLOR_YELLOW, "No pueden conectar más de 3 jugadores por IP.");
				SetTimerEx("TimerKICK", 800, false, "i", playerid2);
			}
		}
		format(string, sizeof string, "[ATENCIÓN] Se expulsó %d players de la IP %d. Razón: Más de 3 conexiones", ips, IP);
		SendAdminMessage(COLOR_YELLOW, string);
	}
	return 1;
}

CheckPlayerIP(playerid) // Multicuentas.
{
	new IP[2][16], ips = 0, string[256];
	GetPlayerIp(playerid, IP[0], 16);
	Loop(playerid2, MAX_PLAYERS, 0) if (IsPlayerConnectedEx(playerid2))
	{
		GetPlayerIp(playerid2, IP[1], 16);
		if (!strcmp(IP[0], IP[1])) ips++;
	}
	if (ips >= 2)
	{
		format(string, sizeof string, "[ATENCIÓN] %s(%d) ingreso al servidor con la misma IP de otro usuario conectado (posible multicuenta).", GetNameFormat(playerid), playerid);
		SendAdminMessage(COLOR_YELLOW, string);
	}
	return 1;
}

//by edinsonwalker:
stock alm(string[], const string2[])
{
	strmid(string, string2, 0, strlen(string2), strlen(string2) + 1);
	return 1;
}

stock Mins_time(minutos)
{
    new tiempito[150];
    new horitas,dias;
    if(minutos > 59)
    {
        horitas = minutos / 60;
        minutos = minutos - (horitas * 60);
    }
    if(horitas > 23)
    {
        dias = horitas / 24;
        horitas = horitas - (dias * 24);
    }
    if(dias > 0)
    {
        format(tiempito,sizeof(tiempito),"%d dias, %d horas",dias, horitas);
    }
    else if(horitas > 0)
    {
        format(tiempito,sizeof(tiempito),"%d horas, %d minutos",horitas,minutos);
    }
    else
    {
        format(tiempito,sizeof(tiempito),"%d minutos",minutos);
    }
    return tiempito;
}

GetMonth(Month)
{
    new MonthStr[15];
    switch(Month)
    {
        case 1:  MonthStr = "Enero";
        case 2:  MonthStr = "Febrero";
        case 3:  MonthStr = "Marzo";
        case 4:  MonthStr = "Abril";
        case 5:  MonthStr = "Mayo";
        case 6:  MonthStr = "Junio";
        case 7:  MonthStr = "Julio";
        case 8:  MonthStr = "Agosto";
        case 9:  MonthStr = "Septiembre";
        case 10: MonthStr = "Octubre";
        case 11: MonthStr = "Noviembre";
        case 12: MonthStr = "Diciembre";
    }
    return MonthStr;
}

stock GetWeekDay(day=0, month=0, year=0)
{
    if (!day)
    getdate(year, month, day);
    new weekday_str[12],j,e;
    if (month <= 2)
    {
        month += 12;
        --year;
    }
    j = year % 100;
    e = year / 100;
    switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
    {
        case 0: weekday_str = "Sabado";
        case 1: weekday_str = "Domingo";
        case 2: weekday_str = "Lunes";
        case 3: weekday_str = "Martes";
        case 4: weekday_str = "Miercoles";
        case 5: weekday_str = "Jueves";
        case 6: weekday_str = "Viernes";
    }
    return weekday_str;
}

FechaHoy()
{
	new Ano, Mes, Dia, Hora, Minutos, Segundos, gformat[256];
	getdate(Ano, Mes, Dia);
	gettime(Hora, Minutos, Segundos);
	format(gformat, sizeof gformat, "%02d:%02d:%02d - %02d/%02d/%02d", Hora, Minutos, Segundos, Dia, Mes, Ano);
	return gformat;
}

Fecha2Hoy()
{
	new Ano, Mes, Dia, Hora, Minutos, Segundos, gformat[256];
	getdate(Ano, Mes, Dia);
	gettime(Hora, Minutos, Segundos);
	if (Hora >= 12) format(gformat, sizeof gformat, "%02d:%02d:%02d PM - %s %02d del %02d", (Hora == 12) ? (12) : (Hora - 12), Minutos, Segundos, GetMonth(Mes), Dia, Ano);
	else if (Hora < 12) format(gformat, sizeof gformat, "%02d:%02d:%02d AM - %s %02d del %02d", (Hora == 0) ? (12) : (Hora), Minutos, Segundos, GetMonth(Mes), Dia, Ano);
	return gformat;
}

IntentoChitearBalas(playerid)
{
	if(cheat_balas != 0 && GetPlayerAmmo(playerid) > InfoPersonaje[playerid][pManoDerechaCant] && AntiG[Balas])
	{
		if (CheatDetected(playerid, "Cheat de balas (type 2)", 2) == 1)
			QuitarManos(playerid);
		return 1;
	}
	return 0;
}

funcion CheckTimer(time, ref)
{
	new seconds = (time - (gettime() - ref));
	if(ref == 0) return -1;
	else if(seconds <= 0) return 0;
	else return seconds;
}

funcion CercaDelWeon(Float:radi, playerid, playerid2) {
	new Float: fp_playerPos[3];
	GetPlayerPos(playerid2, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, radi, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(playerid2)) { return 1; }
	return 0;
}

stock PlayerAudio(playerid, soundid, Float: radio = 10.0)// Realistic sound playback
{
    new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y, z);
	foreach(new i: Player)
	{
		if(IsPlayerInRangeOfPoint(i, radio, x, y, z)) PlayerPlaySound(i, soundid, x, y, z);
	}
	return 1;
}

funcion RemovePlayerWeapon(playerid, weaponid) //quitar un arma de un jugador
{
	if(!IsPlayerConnected(playerid) || weaponid < 0 || weaponid > 50) return;
	new saveweapon[13], saveammo[13];
	for(new slot = 0; slot < 13; slot++)
	GetPlayerWeaponData(playerid, slot, saveweapon[slot], saveammo[slot]);
	ResetPlayerWeapons(playerid);
	for(new slot; slot < 13; slot++)
	{
		if(saveweapon[slot] == weaponid || saveammo[slot] == 0) continue;
		GivePlayerWeapon(playerid, saveweapon[slot], saveammo[slot]);
	}
	GivePlayerWeapon(playerid, 0, 1);
}

stock GetZoneName(Float:x, Float:y, zone[], len)
{
	for(new i = 0; i != sizeof(gSAZones); i++)
	{
		
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
		{
			
			return format(zone, len, gSAZones[i][SAZONE_NAME], 0);
		}
	}
	return 0;
}

stock Get2DZone(zone[], len, Float: x, Float: y, Float: z)
{
	#pragma unused z
	for (new i = 0; i != sizeof(gSAZones); i++)
	{
		if (x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
		{
			return format(zone, len, gSAZones[i][SAZONE_NAME]);
		}
	}
	return format(zone, len, "San Andreas");
}

// 12/02/2020
funcion IsPlayerConnectedEx(const playerid)
{
	if (IsPlayerConnected(playerid) && usuario_registro[playerid] == 2) return 1;
	return 0;
}

// 13/02/2020
SendSplitMessage(playerid, color, const text[])
{
	#define LENGHT (125)

	if(strlen(text) > LENGHT)
	{
		new firstString[LENGHT], secondString[LENGHT];

		strmid(firstString, text, 0, LENGHT);
		strmid(secondString, text, LENGHT - 1, LENGHT * 2);

		format(firstString, LENGHT, "%s...", firstString);
		format(secondString, LENGHT, "...%s", secondString);

		SendPlayerChatMessage(playerid, color, firstString);
		SendPlayerChatMessage(playerid, color, secondString);
	}
	else SendPlayerChatMessage(playerid, color, text);

	#undef LENGHT

	return 1;
}

// 15/02/2020
ProxExDetector(Float: f_Radius, playerid, const string[], col1, col2, col3, col4, col5)
{
	new Float: f_playerPos[3];
	GetPlayerPos(playerid, f_playerPos[0], f_playerPos[1], f_playerPos[2]);
	foreach(Player, i)
	{
		if (i == playerid)break;
		if (GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			if (IsPlayerInRangeOfPoint(i, f_Radius / 16, f_playerPos[0], f_playerPos[1], f_playerPos[2]))
			{
				if (InfoPersonaje[i][pHorasOn] != -1) SendSplitMessage(i, col1, string);
			}
			else if (IsPlayerInRangeOfPoint(i, f_Radius / 8, f_playerPos[0], f_playerPos[1], f_playerPos[2]))
			{
				if (InfoPersonaje[i][pHorasOn] != -1) SendSplitMessage(i, col2, string);
			}
			else if (IsPlayerInRangeOfPoint(i, f_Radius / 4, f_playerPos[0], f_playerPos[1], f_playerPos[2]))
			{
				if (InfoPersonaje[i][pHorasOn] != -1) SendSplitMessage(i, col3, string);
			}
			else if (IsPlayerInRangeOfPoint(i, f_Radius / 2, f_playerPos[0], f_playerPos[1], f_playerPos[2]))
			{
				if (InfoPersonaje[i][pHorasOn] != -1) SendSplitMessage(i, col4, string);
			}
			else if (IsPlayerInRangeOfPoint(i, f_Radius, f_playerPos[0], f_playerPos[1], f_playerPos[2]))
			{
				if (InfoPersonaje[i][pHorasOn] != -1) SendSplitMessage(i, col5, string);
			}
		}
	}
	return 1;
}

stock ReplaceString(const str[], Regex:regex, const fmt[], dest[], size = sizeof dest)
{
    Regex_Replace(str, regex, fmt, dest, MATCH_DEFAULT, size);
}

ProxDetector(Float: f_Radius, playerid, string[], col1, col2, col3, col4, col5) 
{
    new Float: f_playerPos[3];
    GetPlayerPos(playerid, f_playerPos[0], f_playerPos[1], f_playerPos[2]);
    
    new Regex:regex = Regex_New("\\{player:(\\d+)\\}");

    new RegexMatch:match, pos;
    if(Regex_Search(string, regex, match, pos))
    {
        new id_str[16], length, id;
        Match_GetGroup(match, 1, id_str, length);
        id = strval(id_str);
        
        Match_Free(match); 
    
        foreach(new i : Player) 
        {      
            if (!BigEar[i]) {
                if (GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) {
                    
                    new playerName[128];
                    GetRealName(i, id, playerName, sizeof(playerName));
                    
                    new custom_string[512];
                    ReplaceString(string, regex, playerName, custom_string);
                    
                    if (IsPlayerInRangeOfPoint(i, f_Radius / 16, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col1, custom_string);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 8, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col2, custom_string);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 4, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col3, custom_string);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 2, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col4, custom_string);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col5, custom_string);
                    }
                }
            } 
            else
            { 
                new playerName[128];
                GetRealName(i, id, playerName, sizeof(playerName));
                
                new custom_string[512];
                ReplaceString(string, regex, playerName, custom_string);
                
                SendClientMessage(i, col1, custom_string); 
            }
        }
    }
    else 
    {
        new str_to_send[512];
        format(str_to_send, sizeof(str_to_send), "%s", string); 
        
        foreach(new i : Player) 
        {      
            if (!BigEar[i]) {
                if (GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) {
                    
                    if (IsPlayerInRangeOfPoint(i, f_Radius / 16, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col1, str_to_send);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 8, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col2, str_to_send);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 4, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col3, str_to_send);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius / 2, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col4, str_to_send);
                    } else if (IsPlayerInRangeOfPoint(i, f_Radius, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
                        SendSplitMessage(i, col5, str_to_send);
                    }
                }
            } 
            else
            { 
                SendClientMessage(i, col1, str_to_send); 
            }
        }
    }
    
    Regex_Delete(regex);
    return 1;
}

CercaDelMarica(Float:radi, playerid, targetid)
{
	new Float: fp_playerPos[3];
	GetPlayerPos(targetid, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]);
	if (IsPlayerInRangeOfPoint(playerid, radi, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
	{
		return 1;
	}
	return 0;
}

Segundos_tiempo(segundos)
{
	new gformat[256], minutos, horitas, dias;
	if (segundos > 59)
	{
		minutos = segundos / 60;
		segundos = segundos - (minutos * 60);
	}
	if (minutos > 59)
	{
		horitas = minutos / 60;
		minutos = minutos - (horitas * 60);
	}
	if (horitas > 23)
	{
		dias = horitas / 24;
		horitas = horitas - (dias * 24);
	}
	if (dias > 0)
    {
//		format(gformat, sizeof gformat, "%d días, %d hrs, %d mins, %d segs", dias, horitas, minutos, segundos);
		format(gformat, sizeof gformat, "%d días, %d hrs", dias, horitas);
	}
	else if (horitas > 0)
	{
		format(gformat, sizeof gformat, "%d hrs, %d mins", horitas, minutos);
	}
	else if (minutos > 0)
	{
		format(gformat, sizeof gformat, "%d mins, %d segs", minutos, segundos);
	}
	else
	{
		format(gformat, sizeof gformat, "%d segs", segundos);
	}
	return gformat;
}

stock GetPlayerFirstName(playerid)
{
    new
        namestring[2][MAX_PLAYER_NAME],
        name[MAX_PLAYER_NAME];

    GetPlayerName(playerid,name,MAX_PLAYER_NAME);
    split(name, namestring, '_');
    return namestring[0];
}

stock GetPlayerLastName(playerid)
{
    new
        namestring[2][MAX_PLAYER_NAME],
        name[MAX_PLAYER_NAME];

    GetPlayerName(playerid,name,MAX_PLAYER_NAME);
    split(name, namestring, '_');
    return namestring[1];
}

#if !defined IsValidVehicle
    native IsValidVehicle(vehicleid);
#endif

#define MAX_TRY 30

cmd:quitaradiccion(playerid, params[]){
	if (CheckAdminCMD(playerid, 3)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/quitarefectos ID");
	if(!IsPlayerConnectedEx(id)) return 1;

	pDroga[id][AdiccionAnfetamina] = 0;
	pDroga[id][AdiccionCocaina] = 0;
	pDroga[id][AdiccionOpioides] = 0;
	actualizarDrogas(id);
	SendClientMessageEx(playerid, COLOR_GREY, "Le quitaste los efectos de droga a %s.", GetNameFormat(id));
	return 1;
}

cmd:quitarefectos(playerid, params[]){
	if (CheckAdminCMD(playerid, 3)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/quitarefectos ID");
	if(!IsPlayerConnectedEx(id)) return 1;

	QuitarEfectosDroga(id);
	actualizarDrogas(id);
	SendClientMessageEx(playerid, COLOR_GREY, "Le quitaste los efectos de droga a %s.", GetNameFormat(id));
	return 1;
}

cmd:adelantarefectos(playerid, params[]){
	if (CheckAdminCMD(playerid, 3)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/adelantarefectos ID");
	if(!IsPlayerConnectedEx(id)) return 1;

	pDroga[id][TiempoMetanfetamina] = 1;
	pDroga[id][TiempoKetamina] = 1;
	pDroga[id][TiempoCocaina] = 1;
	pDroga[id][TiempoMarihuana] = 1;
	FadePlayerScreenColour(playerid, 0x71d08100, 5000, 50);
	actualizarDrogas(id);
	return 1;
}

QuitarEfectosDroga(id){
	SetPlayerWeatherEx(id, ServerWeather);
	pDroga[id][TiempoMetanfetamina] = 0;
	pDroga[id][TiempoKetamina] = 0;
	pDroga[id][TiempoCocaina] = 0;
	pDroga[id][TiempoHeroina] = 0;
	pDroga[id][TiempoMarihuana] = 0;
	pDroga[id][EfectoMarihuana] = 0;
	pDroga[id][EfectoLSD] = 0;
	pDroga[id][EfectoHongo] = 0;
	pDroga[id][EfectoEspecialUWU] = 0;
	pDroga[id][EfectoCocaina] = 0;
	pDroga[id][EfectoMDMA] = 0;
	FadePlayerScreenColour(id, 0x71d08100, 5000, 50);
	actualizarDrogas(id);
}

cmd:crearblunt(playerid){
	if(InfoPersonaje[playerid][pManoDerecha] == 43 && InfoPersonaje[playerid][pManoIzquierda] == 0){
		SendPlayerChatMessage(playerid, COLOR_GREY, "Creaste un blunt de marihuana.");
		rol_ame(playerid, "arma un blunt de marihuana");
		InfoPersonaje[playerid][pManoIzquierda] = 48;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 5;
	}else if (InfoPersonaje[playerid][pManoIzquierda] == 43&& InfoPersonaje[playerid][pManoDerecha] == 0){
		SendPlayerChatMessage(playerid, COLOR_GREY, "Creaste un blunt de marihuana.");
		rol_ame(playerid, "arma un blunt de marihuana");
		InfoPersonaje[playerid][pManoDerecha] = 48;
		InfoPersonaje[playerid][pManoDerechaCant] = 5;
	}
	return 1;
}

cmd:creargallo(playerid){
	if(InfoPersonaje[playerid][pManoDerecha] == 43 && InfoPersonaje[playerid][pManoIzquierda] == 0){
		SendPlayerChatMessage(playerid, COLOR_GREY, "Creaste un gallo de marihuana.");
		rol_ame(playerid, "arma un gallo de marihuana");
		InfoPersonaje[playerid][pManoIzquierda] = 47;
		InfoPersonaje[playerid][pManoIzquierdaCant] = 5;
	}else if (InfoPersonaje[playerid][pManoIzquierda] == 43&& InfoPersonaje[playerid][pManoDerecha] == 0){
		SendPlayerChatMessage(playerid, COLOR_GREY, "Creaste un gallo de marihuana.");
		rol_ame(playerid, "arma un gallo de marihuana");
		InfoPersonaje[playerid][pManoDerecha] = 47;
		InfoPersonaje[playerid][pManoDerechaCant] = 5;
	}
	return 1;
}

cmd:usar(playerid, params[]){
	if(isnull(params)) {
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (metadona-diazepam-blunt-canuto-electrico-cocaina)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (ketamina-heroinas-oxicodona-planta-hongo)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (mdma-lsd-anfetamina-metanfetamina-crack)");
	}

	if (strcmp(params, "metadona", true) == 0 || strcmp(params, "diazepam", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 69 || InfoPersonaje[playerid][pManoDerecha] == 70){
			InfoPersonaje[playerid][pManoDerechaCant]--;
			ActualizarManos(playerid, 1);
			new Float: health = InfoPersonaje[playerid][pVida];
			if (health >= 85) dar_vida(playerid, 100);
			else dar_vida(playerid, health + 15.0);
			rol_ame(playerid, "consume unas pastillas");
			actualizarDrogas(playerid);
		}
		else SendPlayerChatMessage(playerid, COLOR_GREY, "* Tienes que tener las pastillas en tu mano derecha.");
	}
	else if(strcmp(params, "blunt", true) == 0 || strcmp(params, "canuto", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 47 || InfoPersonaje[playerid][pManoDerecha] == 48){
			InfoPersonaje[playerid][pManoDerechaCant]--;
			ActualizarManos(playerid, 1);

			pDroga[playerid][EfectoMarihuana] = 1; // Tipo 1 (blunt-canuto)
			if(pDroga[playerid][TiempoMarihuana] < 25) pDroga[playerid][TiempoMarihuana] += 2; // max 26 min
			rol_ame(playerid, "Le da una calada a su marihuana");
			pc_cmd_fumando(playerid, "5");
			actualizarDrogas(playerid);
		}
		else SendPlayerChatMessage(playerid, COLOR_GREY, "* Tienes que tener la marihuana en tu mano derecha.");
	}
	else if(strcmp(params, "electrico", true) == 0 || strcmp(params, "cigarroelectrico", true) == 0){
		new manoder = InfoPersonaje[playerid][pManoDerecha];
		new manoizq = InfoPersonaje[playerid][pManoIzquierda];

		if(manoder == 79 && (manoizq == 80 || manoizq == 81 || manoizq == 82)){
			InfoPersonaje[playerid][pManoIzquierdaCant]--;
			rol_ame(playerid, "Le da una calada a su cigarro eléctrico");
			pDroga[playerid][EfectoMarihuana] = 2; // Tipo 1 (electrico)
			actualizarDrogas(playerid);
			if(pDroga[playerid][TiempoMarihuana] < 25) pDroga[playerid][TiempoMarihuana] += 4; // max 26 min
		}else if(manoizq == 79 && (manoder == 80 || manoder == 81 || manoder == 82)){
			pDroga[playerid][EfectoMarihuana] = 2; // Tipo 1 (electrico)
			if(pDroga[playerid][TiempoMarihuana] < 25) pDroga[playerid][TiempoMarihuana] += 4; // max 26 min
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "Le da una calada a su cigarro eléctrico");
			actualizarDrogas(playerid);
		}else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes cigarro electrico y un cartucho en tus manos.");
	}
	else if(strcmp(params, "cocaina", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 46)
		{
			if(pDroga[playerid][EfectoCocaina] < 2) pDroga[playerid][EfectoCocaina]++; // max 2 acumulaciones
			if(pDroga[playerid][TiempoCocaina] > 10)  pDroga[playerid][TiempoCocaina] = 25;  // max 25 minutos
			else pDroga[playerid][TiempoCocaina] += 15;
			if(pDroga[playerid][AdiccionCocaina] < 60) pDroga[playerid][AdiccionCocaina] += 3;
			pDroga[playerid][NivelSobredosis] += 2;
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "Esnifa una raya de cocaína");
			actualizarDrogas(playerid);
			if(pDroga[playerid][AdicCoca]){
				pDroga[playerid][AdicCoca] = 0;
				FadePlayerScreenColour(playerid, 0xe1401800, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes cocaína en tu mano derecha.");
	}
	else if(strcmp(params, "ketamina", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 77)
		{
			pDroga[playerid][TiempoKetamina] = 15;// siempre 15min
			if(pDroga[playerid][AdiccionOpioides] < 60) pDroga[playerid][AdiccionOpioides] += 1;

			pDroga[playerid][NivelSobredosis] += 2;
			new Float: health = InfoPersonaje[playerid][pVida];
			if (health >= 80) dar_vida(playerid, 100);
			else dar_vida(playerid, health + 20.0);
			rol_ame(playerid, "se inyecta ketamina");
			actualizarDrogas(playerid);
			InfoPersonaje[playerid][pManoDerechaCant]--;
			if(pDroga[playerid][AdicOpio]){
				pDroga[playerid][AdicOpio] = 0;
				FadePlayerScreenColour(playerid, 0xe1184a00, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ketamina en tu mano derecha.");
	}
	else if(strcmp(params, "heroina", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 76)
		{
			pDroga[playerid][TiempoHeroina] = 15;// siempre 15min
			if(pDroga[playerid][AdiccionOpioides] < 60) pDroga[playerid][AdiccionOpioides] += 3;
			pDroga[playerid][NivelSobredosis] += 3;

			new Float: health = InfoPersonaje[playerid][pChaleco];
			if (health >= 80) dar_chaleco(playerid, 100);
			else dar_chaleco(playerid, health + 20.0);
			rol_ame(playerid, "se inyecta heroina");
			InfoPersonaje[playerid][pManoDerechaCant]--;
			actualizarDrogas(playerid);
			if(pDroga[playerid][AdicOpio]){
				pDroga[playerid][AdicOpio] = 0;
				FadePlayerScreenColour(playerid, 0xe1184a00, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes heroina en tu mano derecha.");
	}
	else if(strcmp(params, "oxicodona", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 71)
		{
			if(pDroga[playerid][AdiccionOpioides] < 60) pDroga[playerid][AdiccionOpioides] += 2;
			pDroga[playerid][NivelSobredosis] += 1;
			new Float: health = InfoPersonaje[playerid][pChaleco];
			if (health >= 95) dar_chaleco(playerid, 100);
			else dar_chaleco(playerid, health + 5.0);
			health = InfoPersonaje[playerid][pVida];
			if (health >= 95) dar_vida(playerid, 100);
			else dar_vida(playerid, health + 5.0);
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "se inyecta oxicodona");
			actualizarDrogas(playerid);
			if(pDroga[playerid][AdicOpio]){
				pDroga[playerid][AdicOpio] = 0;
				FadePlayerScreenColour(playerid, 0xe1184a00, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes oxicodona en tu mano derecha.");
	}
	else if(strcmp(params, "planta", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 71)
		{
			new Float: health = InfoPersonaje[playerid][pVida];
			if (health >= 80) dar_vida(playerid, 100);
			else dar_vida(playerid, health + 20.0);
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "se come una planta");
			actualizarDrogas(playerid);
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes una planta en tu mano derecha.");
	}
	else if(strcmp(params, "hongo", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 78)
		{
			pDroga[playerid][EfectoHongo] = 20; // 20min
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "se come unos hongos");
			actualizarDrogas(playerid);
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes hongos en tu mano derecha.");
	}
	else if(strcmp(params, "mdma", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 73)
		{
			pDroga[playerid][EfectoMDMA] = 20; // 20min
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "se come mdma");
			actualizarDrogas(playerid);
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes mdma en tu mano derecha.");
	}
	else if(strcmp(params, "lsd", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 74)
		{
			pDroga[playerid][EfectoLSD] = 20; // 20min
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "se traga un trip de lsd");
			actualizarDrogas(playerid);
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes lsd en tu mano derecha.");
	}
	else if(strcmp(params, "anfetamina", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 68)
		{
			new Float: health = InfoPersonaje[playerid][pChaleco];
			if (health >= 80) dar_chaleco(playerid, 100);
			else dar_chaleco(playerid, health + 20.0);
			InfoPersonaje[playerid][pManoDerechaCant]--;
			if(pDroga[playerid][AdiccionAnfetamina] < 60) pDroga[playerid][AdiccionAnfetamina] += 3;
			pDroga[playerid][NivelSobredosis] += 2;
			actualizarDrogas(playerid);
			rol_ame(playerid, "Esnifa anfetamina");
			if(pDroga[playerid][AdicMeta]){
				pDroga[playerid][AdicMeta] = 0;
				FadePlayerScreenColour(playerid, 0xad18e100, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes anfetamina en tu mano derecha.");
	}
	else if(strcmp(params, "metanfetamina", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 45)
		{
			pDroga[playerid][TiempoMetanfetamina] = 10; // 10 min
			pDroga[playerid][EfectoMetanfetamina] = 1;
			InfoPersonaje[playerid][pManoDerechaCant]--;
			if(pDroga[playerid][AdiccionAnfetamina] < 60) pDroga[playerid][AdiccionAnfetamina] += 2;
			pDroga[playerid][NivelSobredosis] += 2;
			rol_ame(playerid, "Esnifa metanfetamina");
			actualizarDrogas(playerid);
			if(pDroga[playerid][AdicMeta]){
				pDroga[playerid][AdicMeta] = 0;
				FadePlayerScreenColour(playerid, 0xad18e100, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes metanfetamina en tu mano derecha.");
	}
	else if(strcmp(params, "crack", true) == 0){
		if(InfoPersonaje[playerid][pManoDerecha] == 44)
		{
			if(pDroga[playerid][AdiccionCocaina] < 60) pDroga[playerid][AdiccionCocaina] += 1;
			pDroga[playerid][NivelSobredosis] += 1;
			new Float: health = InfoPersonaje[playerid][pChaleco];
			if (health >= 98) dar_chaleco(playerid, 100);
			else dar_chaleco(playerid, health + 2.0);
			health = InfoPersonaje[playerid][pVida];
			if (health >= 90) dar_vida(playerid, 100);
			else dar_vida(playerid, health + 10.0);
			InfoPersonaje[playerid][pManoDerechaCant]--;
			rol_ame(playerid, "Esnifa crack");
			actualizarDrogas(playerid);
			if(pDroga[playerid][AdicCoca]){
				pDroga[playerid][AdicCoca] = 0;
				FadePlayerScreenColour(playerid, 0xe1401800, 2200, 25);
			}
		}
		else return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes crack en tu mano derecha.");
	}
	else {
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (metadona-diazepam-blunt-canuto-electrico-cocaina)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (ketamina-heroinas-oxicodona-planta-hongo)");
		SendPlayerChatMessage(playerid, COLOR_GREY, "Utilizar /usar (mdma-lsd-anfetamina-metanfetamina-crack)");
	}
	return 1;
}

actualizarDrogas(playerid){
	new query[2500];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET NivelSobredosis = '%d', AdiccionAnfetamina = '%d', AdiccionCocaina = '%d', AdiccionOpioides = '%d', EfectoMetanfetamina = '%d', EfectoCocaina = '%d', EfectoMarihuana = '%d', EfectoLSD = '%d', EfectoMDMA = '%d', EfectoHongo = '%d', EfectoEspecialUWU = '%d', TiempoMetanfetamina = '%d', TiempoCocaina = '%d', TiempoMarihuana = '%d', TiempoHeroina = '%d', TiempoKetamina = '%d' WHERE ID = '%d'",
	pDroga[playerid][NivelSobredosis],
	pDroga[playerid][AdiccionAnfetamina],
	pDroga[playerid][AdiccionCocaina],
	pDroga[playerid][AdiccionOpioides],
	pDroga[playerid][EfectoMetanfetamina],
	pDroga[playerid][EfectoCocaina],
	pDroga[playerid][EfectoMarihuana],
	pDroga[playerid][EfectoLSD],
	pDroga[playerid][EfectoMDMA],
	pDroga[playerid][EfectoHongo],
	pDroga[playerid][EfectoEspecialUWU],
	pDroga[playerid][TiempoMetanfetamina],
	pDroga[playerid][TiempoCocaina],
	pDroga[playerid][TiempoMarihuana],
	pDroga[playerid][TiempoHeroina],
	pDroga[playerid][TiempoKetamina],
	InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
}


cmd:unirdroga(playerid, params[])
{
	if (DrogaDerecha(playerid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún tipo de droga en tu mano derecha.");
	if (DrogaIzquierda(playerid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún tipo de droga en tu mano izquierda.");
	if (InfoPersonaje[playerid][pManoDerecha] != InfoPersonaje[playerid][pManoIzquierda]) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Las drogas que llevas en las manos no son iguales.");
	if (InfoPersonaje[playerid][pManoDerechaCant]+InfoPersonaje[playerid][pManoIzquierdaCant] >= 100) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No puedes unir más de 100 gramos.");
	InfoPersonaje[playerid][pManoDerechaCant] += InfoPersonaje[playerid][pManoIzquierdaCant];
	InfoPersonaje[playerid][pManoIzquierda] = 0;
	InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
	rol_ame(playerid, "junta los gramos de su droga.");
	ActualizarManos(playerid, 1);
	return 1;
}

cmd:dividirdroga(playerid, params[])
{
	if (DrogaDerecha(playerid) == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No tienes ningún tipo de droga en tu mano derecha.");
	if (InfoPersonaje[playerid][pManoIzquierda] != 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener tu mano izquierda vacía.");
	if (InfoPersonaje[playerid][pManoDerechaCant] < 2) return SendPlayerChatMessage(playerid, COLOR_GREY, "* Debes tener al menos dos gramos para dividir.");
	new droga = InfoPersonaje[playerid][pManoDerecha], mont_derecha = InfoPersonaje[playerid][pManoDerechaCant], fuerte = mont_derecha-1, cantidad;
	if (sscanf(params, "d", cantidad)) return SendClientMessageEx(playerid, COLOR_GREEN, "Utiliza: /dividirdroga (Cantidad) [disponible: %d gramos a dividir]", fuerte);
	if (cantidad < 1 || cantidad > fuerte) return SendClientMessageEx(playerid, COLOR_GREY, "* No puedes dividir más de %d gramos.", fuerte);
	InfoPersonaje[playerid][pManoIzquierda] = droga;
	InfoPersonaje[playerid][pManoIzquierdaCant] = cantidad;
	InfoPersonaje[playerid][pManoDerechaCant] -= cantidad;
	PonerObjeto(playerid, 2, droga);
	rol_ame(playerid, "divide los gramos de su droga.");
	ActualizarManos(playerid, 1);
	return 1;
}

DrogaDerecha(playerid)
{
	if (InfoPersonaje[playerid][pManoDerecha] == 43) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 44) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 45) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 46) return 1;

	else if (InfoPersonaje[playerid][pManoDerecha] == 68) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 69) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 70) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 71) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 73) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 74) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 75) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 76) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 77) return 1;
	else if (InfoPersonaje[playerid][pManoDerecha] == 78) return 1;
	return 0;
}

DrogaIzquierda(playerid)
{
	if (InfoPersonaje[playerid][pManoIzquierda] == 43) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 44) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 45) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 46) return 1;

	else if (InfoPersonaje[playerid][pManoIzquierda] == 68) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 69) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 70) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 71) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 73) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 74) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 75) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 76) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 77) return 1;
	else if (InfoPersonaje[playerid][pManoIzquierda] == 78) return 1;
	return 0;
}

plantaLibre(){
	for(new i; i < MAX_PLANTAS; i++) if(Planta[i][Tipo] == 0) return i;
	return -1;
}

cmd:infoplanta(playerid, params[]){
	if (CheckAdminCMD(playerid, 1)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/borrarplanta ID");
	if(id < 0 || id >= MAX_PLANTAS-1) return 1;
	if(Planta[id][Tipo] == 0) return 1;
	new query[200], dueno[MAX_PLAYER_NAME];

	mysql_format(db_samp, query, sizeof query, "SELECT Nombre_Apellido FROM personajes WHERE ID = %d", Planta[id][Plantador]);
	new Cache:result;
	result = mysql_query(db_samp, query);
	cache_get_value_name(0, "Nombre_Apellido", dueno);
	cache_delete(result);

	SendClientMessageEx(playerid, COLOR_GREY, "ID: %d - Dueño: %s - Cosechas restantes: %d - Minutos restantes: %d", id, dueno, Planta[id][Cosechas], Planta[id][TiempoRestante]);
	return 1;
}
cmd:matarplanta(playerid, params[]){
	for(new i; i < MAX_PLANTAS; i++){
		if(Planta[i][Tipo] != 0){
			if(GetPlayerDistanceFromPoint(playerid, Planta[i][Posicion][0], Planta[i][Posicion][1], Planta[i][Posicion][2]) > 1.5) continue;
			MatarPlanta(i);
			SendPlayerChatMessage(playerid, COLOR_GREY, "Mataste a la planta, demscanse em pas");
		}
	}
	return 1;
}

cmd:borrarplanta(playerid, params[]){
	if (CheckAdminCMD(playerid, 2)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/borrarplanta ID");
	if(id < 0 || id >= MAX_PLANTAS-1) return 1;
	if(Planta[id][Tipo] == 0) return 1;
	MatarPlanta(id);
	SendPlayerChatMessage(playerid, COLOR_GREY, "Planta eliminada del planeta, -3 de oxigeno.");
	return 1;
}

cmd:cosecharplanta(playerid){
	new pvw = GetPlayerVirtualWorld(playerid);
	for(new i; i < MAX_PLANTAS; i++){
		if(Planta[i][Tipo] != 0){
			new cant, obj;
			if(pvw != Planta[i][VWP]) continue;
			if(GetPlayerDistanceFromPoint(playerid, Planta[i][Posicion][0], Planta[i][Posicion][1], Planta[i][Posicion][2]) > 1.5) continue;
			if(Planta[i][TiempoRestante] > 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "Esta planta aún no está lista");
			if(Planta[i][Tipo] == 1){
				cant = 25;
				obj = 43;
			}
			else if(Planta[i][Tipo] == 2){
				cant = 3;
				obj = 78;
			}
			else if(Planta[i][Tipo] == 3){
				cant = 2;
				obj = 75;
			}
			if (InfoPersonaje[playerid][pManoDerecha] == 0)
			{
				InfoPersonaje[playerid][pManoDerecha] = obj;
				InfoPersonaje[playerid][pManoDerechaCant] = cant;
				ActualizarManos(playerid, 1);
				updatePlanta(i);
			}
			else if (InfoPersonaje[playerid][pManoIzquierda] == 0){
				InfoPersonaje[playerid][pManoIzquierda] = obj;
				InfoPersonaje[playerid][pManoIzquierdaCant] = cant;
				updatePlanta(i);
				ActualizarManos(playerid, 1);
			}
			else return SendPlayerChatMessage(playerid, COLOR_GREY, "Tus manos están ocupadas.");
			Planta[i][Cosechas] -= 1;
			if(Planta[i][Cosechas] == 0){
				MatarPlanta(i);
			}
			SendPlayerChatMessage(playerid, COLOR_GREY, "Cosechaste una parte de la planta.");
			return 1;
		}
	}
	return 1;
}

cmd:crecerplanta(playerid, params[]){
	if (CheckAdminCMD(playerid, 4)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/crecerplanta ID");
	if(id < 0 || id >= MAX_PLANTAS-1) return 1;
	if(Planta[id][Tipo] == 0) return 1;
	Planta[id][TiempoRestante] = 2;
	SendPlayerChatMessage(playerid, COLOR_GREY, "La planta crecerá en 2 minutos");
	return 1;
}

cmd:irplanta(playerid, params[]){
	if (CheckAdminCMD(playerid, 1)) return 1;
	new id;
	if (sscanf(params, "i", id)) return SendPlayerChatMessage(playerid, COLOR_GREY, "/irplanta ID");
	if(id < 0 || id >= MAX_PLANTAS-1) return 1;
	if(Planta[id][Tipo] == 0) return 1;
	SetPlayerPos(playerid, Planta[id][Posicion][0], Planta[id][Posicion][1], Planta[id][Posicion][2]);
	SetPlayerVirtualWorld(playerid, Planta[id][VWP]);
	SetPlayerInterior(playerid, Planta[id][IntP]);
	return 1;
}

cmd:idplanta(playerid){
	if (CheckAdminCMD(playerid, 1)) return 1;
	new sl[20];

	for(new i; i < MAX_PLANTAS; i++){
		if(Planta[i][Tipo] != 0){
			if(GetPlayerDistanceFromPoint(playerid, Planta[i][Posicion][0], Planta[i][Posicion][1], Planta[i][Posicion][2]) < 15.0){
				if(Planta[i][Tipo] == 1) alm(sl, "Marihuana");
				else if(Planta[i][Tipo] == 2) alm(sl, "Hongo");
				else if(Planta[i][Tipo] == 3) alm(sl, "Coca");
				SendClientMessageEx(playerid, COLOR_GREY, "[%s] id: %d", sl, i);
			}
		}
	}
	return 1;
}

ActualizarObjetoPlanta(id){
	if(!IsValidDynamicObject(Planta[id][Objeto]))
	{
		if(Planta[id][Tipo] == 1) Planta[id][Objeto] = CreateDynamicObject(19473, Planta[id][Posicion][0], Planta[id][Posicion][1], Planta[id][Posicion][2], 0.0, 0.0, 0.0, Planta[id][VWP], Planta[id][IntP]);
		else if (Planta[id][Tipo] == 2) Planta[id][Objeto] = CreateDynamicObject(2194, Planta[id][Posicion][0], Planta[id][Posicion][1], Planta[id][Posicion][2], 0.0, 0.0, 0.0, Planta[id][VWP], Planta[id][IntP]);
		else if (Planta[id][Tipo] == 3) Planta[id][Objeto] = CreateDynamicObject(2249, Planta[id][Posicion][0], Planta[id][Posicion][1], Planta[id][Posicion][2], 0.0, 0.0, 0.0, Planta[id][VWP], Planta[id][IntP]);
	}
	new pl[20], texto[200];
	if(Planta[id][Tipo] == 1) alm(pl, "Marihuana");
	else if(Planta[id][Tipo] == 2) alm(pl, "Hongo");
	else if(Planta[id][Tipo] == 3) alm(pl, "Coca");

	if(Planta[id][TiempoRestante] > 0) format(texto, sizeof texto, "{4bea96}[%s] {ffffff} crecerá en {ccea4b} %0.2f {ffffff}horas",pl, float(Planta[id][TiempoRestante])/60.0);
	else format(texto, sizeof texto, "{4bea96}[%s] {ffffff} morirá en {ea8a4b} %0.2f {ffffff}horas",pl, 48.0-floatabs(float(Planta[id][TiempoRestante])/60.0));
	if(!IsValidDynamic3DTextLabel(Planta[id][Draw])) Planta[id][Draw] = CreateDynamic3DTextLabel(texto, 0xFFFFFFFF, Planta[id][Posicion][0], Planta[id][Posicion][1], Planta[id][Posicion][2], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Planta[id][VWP], Planta[id][IntP]);
	else UpdateDynamic3DTextLabelText(Planta[id][Draw], 0xFFFFFFFF, texto);
}

MatarPlanta(id){
	if(IsValidDynamicObject(Planta[id][Objeto])) DestroyDynamicObject(Planta[id][Objeto]);
	if(IsValidDynamic3DTextLabel(Planta[id][Draw])) DestroyDynamic3DTextLabel(Planta[id][Draw]);
	Planta[id][Draw] = Text3D:INVALID_3DTEXT_ID;
	Planta[id][Objeto] = INVALID_OBJECT_ID;
	Planta[id][Tipo] = 0;
	Planta[id][Posicion][2] = -10.0;
	Planta[id][Cosechas] = 0;
	Planta[id][TiempoRestante] = 0;
	Planta[id][Plantador] = -1;
	updatePlanta(id);
}

CrearPlanta(playerid, tipo){
	if(!IsPlayerConnectedEx(playerid)) return 1;

	new ID = plantaLibre();

	if(ID == -1) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No hay plantas disponibles :( contacta con un GO.");

	GetPlayerPos(playerid, Planta[ID][Posicion][0],Planta[ID][Posicion][1],Planta[ID][Posicion][2]);
	Planta[ID][Posicion][2] -= 0.72;

	Planta[ID][IntP] = GetPlayerInterior(playerid);
	Planta[ID][VWP] = GetPlayerVirtualWorld(playerid);
	Planta[ID][Plantador] = InfoPersonaje[playerid][pID];

	// grass house 3261
	if(tipo == 1){ // maria 19473
		Planta[ID][Posicion][2] -= 0.54;
		Planta[ID][Tipo] = 1;
		Planta[ID][Cosechas] = 4;
		Planta[ID][TiempoRestante] = 48*60;
	}else if(tipo == 2){ // hongo 2194
		Planta[ID][Tipo] = 2;
		Planta[ID][Cosechas] = 5;
		Planta[ID][Posicion][2] -= 0.15;
		Planta[ID][TiempoRestante] = 36*60;
	}else if(tipo == 3){  // coca 2249
		Planta[ID][Cosechas] = 4;
		Planta[ID][Tipo] = 3;
		Planta[ID][Posicion][2] -= 0.08;
		Planta[ID][TiempoRestante] = 64*60;
	}
	if(Planta[ID][IntP] == 0 && Planta[ID][VWP] == 0) // mitad tiempo
	{
		Planta[ID][TiempoRestante] /= 2;
	}

	SendClientMessageEx(playerid, COLOR_GREY, "La planta estará lista en %d horas.", Planta[ID][TiempoRestante]/60);

	if(Planta[ID][sID] == -1){ // no existe
		new query[2000];
		mysql_format(db_samp, query, sizeof query, "INSERT INTO plantas (Tipo) VALUES (%d)", Planta[ID][Tipo]);
		mysql_tquery(db_samp, query, "OnPlantCreate", "i", ID);
		updatePlanta(ID);
	}else{ // existe
		ActualizarPlanta(ID);
	}

	ActualizarObjetoPlanta(ID);
	return 1;
}


forward OnPlantCreate(id);
public OnPlantCreate(id)
{
	Planta[id][sID] = cache_insert_id();
	cache_unset_active();
    return 1;
}

updatePlanta(id){
	SetTimerEx("ActualizarPlanta", 300, false, "i", id);
}

forward ActualizarPlanta(id);
public ActualizarPlanta(id){
	new query[3500];
	mysql_format(db_samp, query, sizeof query, "UPDATE plantas SET Tipo = '%d', X = '%f', Y = '%f', Z = '%f', I = '%d', VW = '%d', Cosechas = '%d', TiempoRestante = '%d', Plantador = '%d' WHERE ID = '%d'",
	Planta[id][Tipo],
	Planta[id][Posicion][0],
	Planta[id][Posicion][1],
	Planta[id][Posicion][2],
	Planta[id][IntP],
	Planta[id][VWP],
	Planta[id][Cosechas],
	Planta[id][TiempoRestante],
	Planta[id][Plantador],
	Planta[id][sID]);
	mysql_tquery(db_samp, query);
}

cmd:plantar(playerid, params[]){
	new manoder = InfoPersonaje[playerid][pManoDerecha];
	new manoizq = InfoPersonaje[playerid][pManoIzquierda];
	if(isnull(params)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* /plantar (marihuana-micelio-coca)");

	if (strcmp(params, "marihuana", true) == 0){
		if(manoder == 83){
			InfoPersonaje[playerid][pManoDerechaCant]--;
			CrearPlanta(playerid, 1);
			return 1;
		}else if(manoizq == 83){
			InfoPersonaje[playerid][pManoIzquierdaCant]--;
			CrearPlanta(playerid, 1);
			return 1;
		}
		return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes semillas de marihuana en tus manos");
	}else if(strcmp(params, "micelio", true) == 0){
		if(manoder == 84){
			InfoPersonaje[playerid][pManoDerechaCant]--;
			CrearPlanta(playerid, 2);
			return 1;
		}else if(manoizq == 84){
			InfoPersonaje[playerid][pManoIzquierdaCant]--;
			CrearPlanta(playerid, 2);
			return 1;
		}
		return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes micelio en tus manos");
	}else if(strcmp(params, "coca", true) == 0){
		if(manoder == 85){
			InfoPersonaje[playerid][pManoDerechaCant]--;
			CrearPlanta(playerid, 3);
			return 1;
		}else if(manoizq == 85){
			InfoPersonaje[playerid][pManoIzquierdaCant]--;
			CrearPlanta(playerid, 3);
			return 1;
		}
		return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes semillas de coca en tus manos");
	} else SendPlayerChatMessage(playerid, COLOR_GREY, "* /plantar (marihuana-micelio-coca)");
	return 1;
}

SQLConectado(id){
	foreach (new playerid2: Player)
    {
		if (IsPlayerConnectedEx(playerid2)){
			if(InfoPersonaje[playerid2][pID] == id) return playerid2;
		}
	}
	return -1;
}

new DrugCounter;

forward startUwu(playerid);
public startUwu(playerid){
	GetPlayerPos(playerid, pDroga[playerid][OldUWU][0], pDroga[playerid][OldUWU][1], pDroga[playerid][OldUWU][2]);
	SetPlayerPos(playerid, pDroga[playerid][OldUWU][0], pDroga[playerid][OldUWU][1], pDroga[playerid][OldUWU][2]+40000);
	SetPlayerWeatherEx(playerid, 246);
	SetPlayerTime(playerid, 22, 0);
	FadePlayerScreenColour(playerid, 0x00000000, 2500, 25);
}

// ODP sistema
cmd:centralita(playerid)
{
	if (!member_faccion(playerid, 1, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No formas parte de la ley.");
	if (member_faccion(playerid, 1, 4))
	{
		new Str[256], Str_[5000], i_ = 0;
		for (new x=1; x<sizeof(info_c); x++)
		{
		    if (info_c[x][aID] != 0)
			{
				format(Str, sizeof(Str), "{00a2ff}%d: {DDCC72}%s, Teléfono:{00a2ff} %d\n", x, info_c[x][aNombre], info_c[x][aTelefono]);
				strcat(Str_, Str);
				format(Str, sizeof( Str ), "Centra_Puto%d", i_);
				SetPVarInt(playerid, Str, x);
				i_++;
			}
		}
		if (i_ == 0) Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_LIST, "Llamadas recibidas.", "No hay ninguna llamada pendiente.", "Ok", "");
		Dialog_Show(playerid, D_Centralita, DIALOG_STYLE_LIST, "Llamadas recibidas.", Str_, ">>", "<<");
	}
	else if (member_faccion(playerid, 6))
	{
	    new Str[256], Str_[5000], i_ = 0;
		for (new x=1; x<sizeof(info_c); x++)
		{
		    if (info_c[x][aID] != 0)
			{
				format(Str, sizeof(Str), "{00a2ff}%d: {DDCC72}%s, Teléfono:{00a2ff} %d\n", x, info_c[x][aNombre], info_c[x][aTelefono]);
				strcat(Str_, Str);
				format(Str, sizeof( Str ), "Centra_Puto%d", i_);
				SetPVarInt(playerid, Str, x);
				i_++;
			}
		}
		if (i_ == 0) Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_LIST, "Llamadas recibidas.", "No hay ninguna llamada pendiente.", "Ok", "");
		Dialog_Show(playerid, D_Centralita, DIALOG_STYLE_LIST, "Llamadas recibidas.", Str_, ">>", "<<");
	}
	return 1;
}
alias:centralita("atenderpd");
Dialog:D_Centralita(playerid, response, listitem, inputtext[])
{
	if(!response) return pc_cmd_informes(playerid);
	new ID = listitem,StrPVar[40];
	format(StrPVar, sizeof StrPVar, "Centra_Puto%d", ID);
	new i = GetPVarInt(playerid,StrPVar);
    new _dialog1[3000],
		_dialog2[300],
		_dialog3[128],
		a_atendido[50];

	if(info_c[i][aAtendido] == 0) a_atendido = "{C20000}No atendido";
	else if(info_c[i][aAtendido] == 1) a_atendido = "{009100}Atendido";

	format(_dialog2, sizeof(_dialog2), "{00a2ff}* Nombre del ciudadano:{DDCC72} %s\n", info_c[i][aNombre]); strcat(_dialog1, _dialog2);
	format(_dialog2, sizeof(_dialog2), "{00a2ff}* Teléfono:{DDCC72} %d\n", info_c[i][aTelefono]); strcat(_dialog1, _dialog2);
	new stringx[128], mensaje[256];
	alm(mensaje, info_c[i][aHechos]);
    if(strlen(mensaje) > 65)
	{
		new string2[128];
		format(string2,256,"{DDCC72}... %s\n",mensaje[70]);
		strdel(mensaje,65,strlen(mensaje));
		format(stringx, sizeof(stringx), "{00a2ff}* Situación:{DDCC72} %s\n", mensaje);
        strcat(_dialog1, stringx);
        strcat(_dialog1, string2);
	}
	else if(strlen(mensaje) <= 65)
	{
		format(stringx, sizeof(stringx), "{00a2ff}* Situación:{DDCC72} %s\n", mensaje);
        strcat(_dialog1, stringx);
	}
	format(_dialog2, sizeof(_dialog2), "{00a2ff}* Último rastreo de la llamada:{DDCC72} %s\n", info_c[i][aZona]); strcat(_dialog1, _dialog2);
	format(_dialog3, sizeof(_dialog3), "{00a2ff}Centralita:{DDCC72} %d | %s", i, a_atendido);
	if(info_c[i][aAtendido] == 0) Dialog_Show(playerid,D_Centralita2, DIALOG_STYLE_MSGBOX, _dialog3, _dialog1, "ATENDER", "SALIR");
	else Dialog_Show(playerid,D_Centralita2, DIALOG_STYLE_MSGBOX, _dialog3, _dialog1, "BORRAR", "SALIR");
	SetPVarInt(playerid, "en_centralita", 0);
	SetPVarInt(playerid, "centra_id", i);
	return 1;
}

Dialog:D_Centralita2(playerid, response, listitem, inputtext[])
{
    if(response)
    {
		new x = GetPVarInt(playerid, "centra_id");
		if(info_c[x][aAtendido] == 0)
		{
	        if (GetPVarInt(playerid, "en_centralita") == 0)
			{
				Dialog_Show(playerid, D_Centralita2, DIALOG_STYLE_INPUT, "Registros", "{00a2ff}Ingresar Callsign:", "Código 2", "Código 3");
				SetPVarInt(playerid, "en_centralita", 1);
				return 1;
			}
			else
			{
				if (x != 0)
				{
					new info[128];
					switch (InfoPersonaje[playerid][pMiembro])
					{
						case 1:
						{
							format(info, sizeof(info), "** [CH: DISPATCH, S: 1] %s: %s, atiende al llamado de emergencia en %s, código dos.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(1, COLOR_RADIO, info, 1);
						}
						case 4:
						{
							format(info, sizeof(info), "** [CH: DISPATCH, S: 4] %s: %s, atiende al llamado de emergencia en %s, código dos.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(4, COLOR_RADIO, info, 1);
						}
						case 6:
						{
							format(info, sizeof(info), "** [CH: 911, S: 3] %s: %s, atiende al llamado de emergencia en %s, código dos.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(6, COLOR_RADIO, info, 1);
						}
					}
					info_c[x][aAtendido] = 1;
					CentrTimer[x] = SetTimerEx("delete_centra", 60000*20, false, "i", x);
					DeletePVar(playerid, "centra_id");
					DeletePVar(playerid, "en_centralita");
				}
				return 1;
			}
		}
		else
		{
		    ShowInfoForPlayer(playerid, "Borraste la llamada seleccionada.", 5000);
		    info_c[x][aID] = 0;
			info_c[x][aAtendido] = 0;
			KillTimer(CentrTimer[x]);
			DeletePVar(playerid, "centra_id");
			DeletePVar(playerid, "en_centralita");
		}
	}
	else
	{
		new x = GetPVarInt(playerid, "centra_id");
	    if(info_c[x][aAtendido] == 0)
		{
		    if (GetPVarInt(playerid, "en_centralita") == 0)
			{
				ShowInfoForPlayer(playerid, "Saliste del registro de centralita.", 5000);
				DeletePVar(playerid, "centra_id");
				DeletePVar(playerid, "en_centralita");
			}
			else
			{
				if (x != 0)
				{
					new info[128];
					switch (InfoPersonaje[playerid][pMiembro])
					{
						case 1:
						{
							format(info, sizeof(info), "** [CH: DISPATCH, S: 1] %s: %s, atiende al llamado de emergencia en %s, código tres.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(1, COLOR_RADIO, info, 1);
						}
						case 4:
						{
							format(info, sizeof(info), "** [CH: DISPATCH, S: 4] %s: %s, atiende al llamado de emergencia en %s, código tres.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(4, COLOR_RADIO, info, 1);
						}
						case 6:
						{
							format(info, sizeof(info), "** [CH: 911, S: 3] %s: %s, atiende al llamado de emergencia en %s, código tres.", GetNameFormat(playerid), inputtext, info_c[x][aZona]);
							SendRadioMessage(6, COLOR_RADIO, info, 1);
						}
					}
					info_c[x][aAtendido] = 1;
					CentrTimer[x] = SetTimerEx("delete_centra", 60000*20, false, "i", x);
				    DeletePVar(playerid, "centra_id");
					DeletePVar(playerid, "en_centralita");
				}
				return 1;
			}
		}
		else
		{
			ShowInfoForPlayer(playerid, "Saliste del registro de centralita.", 5000);
			DeletePVar(playerid, "centra_id");
			DeletePVar(playerid, "en_centralita");
		}
	}
	return 1;
}

cmd:informes(playerid)
{
	if (!member_faccion(playerid, 1, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la PD o SD.");

	if (member_faccion(playerid, 1, 4))Dialog_Show(playerid, D_informes, DIALOG_STYLE_LIST, "Informes", "— Llamadas (911)\n— Heridos", ">>", "<<");
	else if (member_faccion(playerid, 6))Dialog_Show(playerid, D_informes, DIALOG_STYLE_LIST, "Informes", "— Llamadas (911)\n— Heridos", ">>", "<<");
	return 1;
}

Dialog:D_informes(playerid, response, listitem, inputtext[])
{
    if (!response) return 1;

    switch (listitem)
    {
        case 0: pc_cmd_centralita(playerid);
        case 1: pc_cmd_heridos(playerid);
    }
	return 1;
}

cmd:buscados(playerid, params[])
{
	if (!member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de la PD o SD.");

	new option[128];
	if (sscanf(params, "s[128]", option)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /buscados (agregar - ver - borrar)");

	if (!strcmp(option, "agregar", true, 7))
	{
		if (InfoPersonaje[playerid][pRango] < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser superior a rango 1.");
		if (sscanf(params, "s[128]s[200]", option, params)) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /buscados agregar <texto>");

		for (new x=0; x<sizeof(i_Buscados); x++)
		{
			if (i_Buscados[x][b_ID] == 0)
			{
				i_Buscados[x][b_ID] = x+1;

				format(i_Buscados[x][b_string], 200, params);
				new year, month, day, hour, minute, second;
				getdate(year, month, day); gettime(hour, minute, second);
				format(i_Buscados[x][b_fecha], 128, "Fecha: %d/%d/%d - Hora: %02d:%02d:%02d", day, month, year, hour, minute, second);

				alm(i_Buscados[x][b_creador], GetNameFormat(playerid));
				new string[128], id = InfoPersonaje[playerid][pMiembro];
				format(string, sizeof(string), "[JUSTICIA] %s agregó un nuevo informe. /buscados.", InfoFaccion[id][fNombre]);
				SendRadioMessage(1, 0x5FB2FFFF, string, 1);
				SendRadioMessage(2, 0x5FB2FFFF, string, 1);
				SendRadioMessage(3, 0x5FB2FFFF, string, 1);
				SendRadioMessage(4, 0x5FB2FFFF, string, 1);
				return 1;
			}
		}
		SendPlayerChatMessage(playerid, COLOR_GREY, "Informes llegó a su limite, contacte con VanNet.");
	}
	else if (!strcmp(option, "ver", true, 8))
	{
		new Str[256], Str_[5000], i_ = 0;
		for (new x=0; x<sizeof(i_Buscados); x++)
		{
			if (i_Buscados[x][b_ID] != 0)
			{
				new mensaje[35];
				strmid(mensaje, i_Buscados[x][b_string], 0, 35);
				format(Str, sizeof(Str), "[ID: %d] {CB2700}%s"#ColorWhite" | {90C3D4}Por:"#ColorWhite" %s\n", x, mensaje, i_Buscados[x][b_creador]);
				strcat(Str_, Str);
				format(Str, sizeof(Str), "buscado_xd%d", i_);
				SetPVarInt(playerid, Str, x);
				i_++;
			}
		}
		if (i_ == 0) Dialog_Show(playerid, D_HISTORIALT, DIALOG_STYLE_LIST, "Buscados.", "No hay nada escrito, use /buscados agregar [texto].", "Cerrar", "");
		Dialog_Show(playerid, D_Buscados, DIALOG_STYLE_LIST, "Buscados.", Str_, "Seleccionar", "Cancelar");
	}
	else if (!strcmp(option, "borrar", true, 5))
	{
		if (InfoPersonaje[playerid][pRango] < 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "Debes ser superior a rango 1.");
		if (sscanf(params, "s[128]i", option, params[1])) return SendPlayerChatMessage(playerid, COLOR_GREEN, "Utiliza: /buscados <borrar> <id>");
		if (params[1] < 0 || params[1] >= MAX_BUSCADOS) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID de busqueda errónea.");
		if (!i_Buscados[params[1]][b_ID]) return SendPlayerChatMessage(playerid, COLOR_GREY, "ID Inválida.");
		i_Buscados[params[1]][b_ID] = 0;
		alm(i_Buscados[params[1]][b_string], "nada");
		alm(i_Buscados[params[1]][b_creador], "nadie");
		alm(i_Buscados[params[1]][b_fecha], "sinfecha");
		ShowInfoForPlayer(playerid, "Borraste un informe de busqueda.", 5000);
		return 1;
	}
	else SendPlayerChatMessage(playerid, COLOR_GREY, "Opcion inválida.");
	return 1;
}

Dialog:D_Buscados(playerid, response, listitem, inputtext[])
{
	if(!response) { ShowInfoForPlayer(playerid, "Cerraste los informes de busquedas.", 5000); return 1; }
	new ID = listitem,StrPVar[40];
	format( StrPVar, sizeof( StrPVar ), "buscado_xd%d", ID);
	new i = GetPVarInt(playerid,StrPVar);
	new
	_dialog1[3000],
	_dialog2[256];

	#define LENGHTx (60)

	if(strlen(i_Buscados[i][b_string]) > LENGHTx)
	{
		new firstString[LENGHTx], secondString[LENGHTx];
		strmid(firstString, i_Buscados[i][b_string], 0, LENGHTx);
		strmid(secondString, i_Buscados[i][b_string], LENGHTx - 1, LENGHTx * 2);
		format(firstString, LENGHTx, "%s...", firstString);
		format(secondString, LENGHTx, "\n...%s", secondString);
		strcat(_dialog1, firstString);
		strcat(_dialog1, secondString);
	}
	else strcat(_dialog1, i_Buscados[i][b_string]);
	format(_dialog2, sizeof(_dialog2), "\n\n"#ColorWhite"%s\nEscrito por {CB2700}%s", i_Buscados[i][b_fecha], i_Buscados[i][b_creador]); strcat(_dialog1, _dialog2);
	Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Buscados.", _dialog1, "CERRAR", "");
	return 1;
}

cmd:heridos(playerid)
{
	if (!member_faccion(playerid, 1, 4, 6)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No eres miembro de LAPD, LSCSD o LAMD.");
	new string[128], totalstr[3000], count = 0;
	foreach(Player, i)
	{
		if (YaAviso[i] == 1)
		{
			new Float:PosX, Float:PosY, Float:PosZ;
			GetPlayerPos(playerid, PosX, PosY, PosZ);

			new location[MAX_ZONE_NAME];
			Get2DZone(location, sizeof location, PosX, PosY, PosZ);

			format(string, sizeof string, "Persona herida\tUbicación: %s\n", location);
			strcat(totalstr, string);

			format(string, sizeof string, "Heridos%d", count);
			SetPVarInt(playerid, string, i);
			count++;
		}
	}
	if(count == 0) return Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Heridos", "No hay heridos.", "Aceptar", "");
	Dialog_Show(playerid, HeridosPD, DIALOG_STYLE_LIST, "Heridos", totalstr, "Localizar", "Cancelar");
	return 1;
}

Dialog:HeridosPD(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new string[128];

	format(string, sizeof string, "Heridos%d", listitem);
	new id = GetPVarInt(playerid, string);

	new Float:x, Float:y, Float:z;
	GetPlayerPos(id, x, y, z);

	SetPVarInt(playerid, "BuscandoHeridop", 1);
	SetPlayerCheckpoint(playerid, x, y, z, 5.0);
	ShowInfoForPlayer(playerid, "Se ha trazado la posición del herido.", 5000);
	return 1;
}

cmd:computador(playerid)
{
	if (!member_faccion(playerid, 1, 2, 3, 4)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No perteneces a un cuerpo policial.");
	if (IsPlayerInAnyVehicle(playerid))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (!Vehiculo_LSPD(vehicleid) && !Vehiculo_LSCSD(vehicleid) && !Vehiculo_FBI(vehicleid) && !Vehiculo_USMC(vehicleid)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en un vehículo de tu facción.");
		OrdenadorPD(playerid);
	}
	else
	{
		if(!IsPlayerInRangeOfPoint(playerid,4.0,16.3881,-1856.1171,2501.0859) && !IsPlayerInRangeOfPoint(playerid, 4.0, 338.6380,857.9088,1004.4059)) return SendPlayerChatMessage(playerid, COLOR_GREY, "No estás en las oficinas de tu central.");
		OrdenadorPD(playerid);
	}
	return 1;
}

funcion OrdenadorPD(playerid)
{
	new _dialog1[3000], _dialog2[300];
	strcat(_dialog1, "1. Identificar una persona (Documento)\n\
	2. Informes y registros de búsqueda\n\
	3. Identificar un vehículo\n\
	4. Atender buzón de llamadas (911)\n\
	5. Comprobar lista de sospechosos\n\
	6. Localización de vivienda\n\
	7. Comprobar historial delictivo", sizeof(_dialog1));
	format(_dialog2, sizeof(_dialog2), "Ordenador policial - Sesión iniciada: %s", GetNameFormat(playerid));
	Dialog_Show(playerid, D_Computador1, DIALOG_STYLE_LIST, _dialog2, _dialog1, "Continuar", "Salir");
	return 1;
}
Dialog:D_Computador0(playerid, response, listitem, inputtext[])
{
	if(!response) return OrdenadorPD(playerid);
	OrdenadorPD(playerid);
	return 1;
}
Dialog:D_Computador1(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowInfoForPlayer(playerid, "Saliste del ordenador policial.", 5000);
	PlayerPlaySound(playerid, 40405, 0, 0, 0);
	switch(listitem)
	{
		case 0: Dialog_Show(playerid, D_Computador2, DIALOG_STYLE_INPUT, "Búsqueda de información", "Introduzca el documento de la persona:", "Buscar", "Cancelar");
		case 1: pc_cmd_buscados(playerid, "ver");
		case 2: Dialog_Show(playerid, D_Computador3, DIALOG_STYLE_INPUT, "Información de vehículo", "Introduzca el número de matrícula del vehículo (ID):", "Buscar", "Cancelar");
		case 3: pc_cmd_centralita(playerid);
		case 4:
		{
			new _dialog1[3000], _dialog2[300], so_s = 0;
			strcat(_dialog1, ""#ColorWhite"Listado:\n\n");
			foreach(new _i: Player) if (InfoPersonaje[_i][pEstrellas] != 0)
			{
				format(_dialog2, sizeof(_dialog2), ""#ColorWhite"Nombre completo: %s | Nivel de búsqueda: %d\n", GetNameFormat(_i), InfoPersonaje[_i][pEstrellas]);
				strcat(_dialog1, _dialog2);
				++so_s;
			}
			if (so_s != 0) Dialog_Show(playerid, D_Computador0, DIALOG_STYLE_MSGBOX, "Sospechosos", _dialog1, "Cerrar", "");
			else Dialog_Show(playerid, D_Computador0, DIALOG_STYLE_MSGBOX, "Sospechosos", "No se encuentran sospechosos en este momento", "Cerrar", "");
		}
		case 5: Dialog_Show(playerid, D_Computador4, DIALOG_STYLE_INPUT, "Localización de vivienda", "Introduzca el número de llave de la propiedad:", "Buscar", "Cancelar");
		case 6: Dialog_Show(playerid, D_Computador5, DIALOG_STYLE_INPUT, "Historial delictivo", "Introduzca el documento de la persona:", "Buscar", "Cancelar");
	}
	return 1;
}
Dialog:D_Computador2(playerid, response, listitem, inputtext[])
{
	if(!response) {
		OrdenadorPD(playerid);
	} else {
		if(!isnumeric(inputtext)) return Dialog_Show(playerid, D_Computador2, DIALOG_STYLE_INPUT, "Búsqueda de información", "Introduzca el documento de la persona:\n\n{ff0000} Documento inválido (coloco palabras)", "Buscar", "Cancelar");
		new x212 = strval(inputtext);
		if (x212 == 0) return Dialog_Show(playerid, D_Computador2, DIALOG_STYLE_INPUT, "Búsqueda de información", "Introduzca el documento de la persona:\n\n{ff0000} Documento inválido (coloco número 0)", "Buscar", "Cancelar");
		foreach(Player, idjugador) if (InfoPersonaje[idjugador][pDocumento] == x212) {
			new car[5], fly[5], boat[5], gun[5];
			new _dialog1[3000], _dialog2[300], _dialog3[400];
			if (InfoPersonaje[idjugador][pLicencia][3]) gun = "Si";
			else gun = "No";
			if (InfoPersonaje[idjugador][pLicencia][0]) car = "Si";
			else car = "No";
			if (InfoPersonaje[idjugador][pLicencia][1]) fly = "Si";
			else fly = "No";
			if (InfoPersonaje[idjugador][pLicencia][2]) boat = "Si";
			else boat = "No";

			strcat(_dialog1, ""#ColorWhite"Resultados de búsqueda:\n\n");

			format(_dialog2, sizeof(_dialog2),
			""#ColorWhite"Nombre completo: %s\nEdad: %d\nTeléfono: %d\nDocumento: %d\n\n", GetNameFormat(idjugador), InfoPersonaje[idjugador][pEdad], InfoPersonaje[idjugador][pTelefono], InfoPersonaje[idjugador][pDocumento]);
			strcat(_dialog1, _dialog2);

            new count1 = 0, count2 = 0;
			Loop(id, totalcasas, 1) if (LlavesCasa(idjugador, id))
			{
			    count1++;
				Get2DZone(_dialog2, MAX_ZONE_NAME, InfoCasa[id][cExteriorX], InfoCasa[id][cExteriorY], InfoCasa[id][cExteriorZ]);
				format(_dialog2, sizeof _dialog2, "Casa %d: %s - %d\n", count1, _dialog2, id);
				strcat(_dialog1, _dialog2);
			}
			if (count1 == 0) strcat(_dialog1, "Casas: No posee\n");
			Loop(id, totalnegocios, 1) if (LlavesNegocio(idjugador, id))
			{
				count2++;
				Get2DZone(_dialog2, MAX_ZONE_NAME, InfoNegocio[id][nExteriorX], InfoNegocio[id][nExteriorY], InfoNegocio[id][nExteriorZ]);

				format(_dialog2, sizeof _dialog2, "Negocio %d: %s - %d\n", count2, _dialog2, id);
				strcat(_dialog1, _dialog2);
			}
			if (count2 == 0) strcat(_dialog1, "Negocios: No posee\n\n");

			format(_dialog2, sizeof(_dialog2),
			""#ColorWhite"Licencia de conducir: %s\nLicencia de vuelo: %s\nLicencia de bote: %s\nLicencia de armas: %s\n\n", car, fly, boat, gun);
			strcat(_dialog1, _dialog2);


			format(_dialog3, sizeof(_dialog3), "Información de %s", GetNameFormat(idjugador));
        	Dialog_Show(playerid, D_Computador0, DIALOG_STYLE_MSGBOX, _dialog3, _dialog1, "Cerrar", "");
			return 1;
		}
		Dialog_Show(playerid, D_Computador2, DIALOG_STYLE_INPUT, "Búsqueda de información", "Introduzca el documento de la persona:\n\n{ff0000} Documento inválido (user desconectado)", "Buscar", "Cancelar");
	}
	return 1;
}

Dialog:D_Computador3(playerid, response, listitem, inputtext[])
{
	if (!response) {
		OrdenadorPD(playerid);
	} else {
		if (!isnumeric(inputtext)) return Dialog_Show(playerid, D_Computador3, DIALOG_STYLE_INPUT, "Información de vehículo", "Introduzca el número de matrícula del vehículo:\n\n{ff0000} Matrícula inválida (coloco palabras)", "Buscar", "Cancelar");
		new vehicleid = strval(inputtext);
		foreach(Player, i)
		{
		if (vehicleid != INVALID_VEHICLE_ID) {
			Loop(veh, MAX_VEHICULOS, 0) {
				if(InfoVehiculo[veh][vIG_id] == vehicleid) {
				    new _dialog1[3000], _dialog2[300], _dialog3[300];

					format(_dialog2, sizeof(_dialog2),
					""#ColorWhite"Información:\n\nModelo: %s\nPropetario: %s\nMulta: %d\n\n",
					VehicleName[InfoVehiculo[veh][vModelo] - 400],
					InfoVehiculo[veh][vPropietario],
					InfoVehiculo[veh][vMulta]);
					strcat(_dialog1, _dialog2);
					format(_dialog3, sizeof(_dialog3), "Matrícula LS-%d", vehicleid);
					Dialog_Show(playerid, D_Computador0, DIALOG_STYLE_MSGBOX, _dialog3, _dialog1, "Cerrar", "");
					return 1;
				}
			}
			Dialog_Show(playerid, D_Computador3, DIALOG_STYLE_INPUT, "Información de vehículo", "Introduzca el número de matrícula del vehículo:\n\n{ff0000} Matrícula inválida (vehículo sin dueño)", "Buscar", "Cancelar");
		}
	}
	}
	return 1;
}
Dialog:D_Computador4(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		OrdenadorPD(playerid);
	}
	else
	{
		if (!isnumeric(inputtext)) return Dialog_Show(playerid, D_Computador3, DIALOG_STYLE_INPUT, "Localización de vivienda", "Introduzca el número de llave de la propiedad:\n\n{ff0000} ID de llave inválida (coloco palabras)", "Buscar", "Cancelar");
		new casa = strval(inputtext);
		if (casa != -1)
		{
			for(new cid = 0; cid < MAX_CASAS; cid++)
			{
				if(cid == casa)
				{
				    if (InfoCasa[cid][cExteriorVW] == 0)
				    {
						new zona[MAX_ZONE_NAME], string[128];
						Get2DZone(zona, MAX_ZONE_NAME, InfoCasa[cid][cExteriorX], InfoCasa[cid][cExteriorY], InfoCasa[cid][cExteriorZ]);
						format(string, sizeof(string), "Casa N-%d, localizada en ~y~%s~w~.", casa, zona);
						ShowInfoForPlayer(playerid, string, 5000);
						SetPVarInt(playerid, "EnCheckPoint", 5);
						SetPlayerCheckpoint(playerid, InfoCasa[cid][cExteriorX], InfoCasa[cid][cExteriorY], InfoCasa[cid][cExteriorZ], 1.5);
						TogglePlayerAllDynamicCPs(playerid, false);
						return 1;
					}
					else
					{
					    Dialog_Show(playerid, D_Computador4, DIALOG_STYLE_INPUT, "Localización de vivienda", "Introduzca el número de llave de la propiedad:\n\n{ff0000} ID de llave inválida (casa en otra dimensión)", "Buscar", "Cancelar");
					    return 1;
					}
				}
			}
			Dialog_Show(playerid, D_Computador4, DIALOG_STYLE_INPUT, "Localización de vivienda", "Introduzca el número de llave de la propiedad:\n\n{ff0000} ID de llave inválida (casa no existente)", "Buscar", "Cancelar");
		}
	}
	return 1;
}

Dialog:D_Computador5(playerid, response, listitem, inputtext[])
{
	if(!response) {
		OrdenadorPD(playerid);
	} else {
		if(!isnumeric(inputtext)) return Dialog_Show(playerid, D_Computador5, DIALOG_STYLE_INPUT, "Historial delictivo", "Introduzca el documento de la persona:\n\n{ff0000} Documento inválido (coloco palabras)", "Buscar", "Cancelar");
        new documento = strval(inputtext);
		if (!VerificarDNI(documento)) return SendPlayerChatMessage(playerid, COLOR_GREY, "* No se encontro ningún personaje con ese documento.");
		new nant = GetAntecedentes(documento);
		if (nant > 0)
		{
			new count = 0, gformat[256], dialog[4096] = "#\tDetalles\tFecha\n";

			new query[160];
			new Cache:result;
			mysql_format(db_samp, query, sizeof query, "SELECT * FROM antecedentes WHERE Documento = '%d'", documento);
			result = mysql_query(db_samp, query);

			Loop(e, cache_num_rows(), 0)
			{
				new registro, detalles[512], fecha[256];
				rebel_int(e, "ID", registro);
				rebel_string(e, "Detalles", detalles, 512);
				rebel_string(e, "Fecha", fecha, 256);
				new mensaje[35];
				strmid(mensaje, detalles, 0, 35);
				
				//dialog
				format(gformat, sizeof gformat, "{EBEBEB}Registro: %d\t%s\t{E24D32}%s\n", registro, mensaje, fecha);
				strcat(dialog, gformat);
				
				//conteo
				new gformat2[64];
				format(gformat2, sizeof gformat2, "ehcHis%d", count);
				SetPVarInt(playerid, gformat2, registro);
				count++;
			}
			cache_delete(result);
			format(gformat, sizeof gformat, "{EBEBEB}Documento {088A4B}%d", documento);
			Dialog_Show(playerid, ShowHistorial, DIALOG_STYLE_TABLIST_HEADERS, gformat, dialog, "Ver más", "Salir");
			return 1;
		}
		SendPlayerChatMessage(playerid, COLOR_GREY, "* Sin registros de antecedentes con ese DNI.");
	}
	return 1;
}


CMD:informetest(playerid, params[])
{
	CrearInforme("[CENTRAL] Informe de sospechoso.", params);
	return 1;
}

CMD:crimentest(playerid)
{
	CrearCrimen("Crimen aplicado.", "Articulo 8.6, Homicido a funcionario publico", playerid, 1);
	return 1;
}

// Misc
#include "client/misc/timers.inc"

CMD:cef(playerid)
{
	SendClientMessageEx(playerid, -1, "[CEF] plugin=%d ready=%d estado=%d", CEF_PlayerHasPlugin(playerid), gCefReady[playerid], gCefInvEstado[playerid]);

	if (gCefInvEstado[playerid] == 0 && CEF_PlayerHasPlugin(playerid))
	{
		gCefReady[playerid] = true; // el handshake ya terminó, forzamos la creación
		CEF_CrearInventario(playerid);
		return 1;
	}
	if (gCefInvEstado[playerid] != 2) return SendClientMessage(playerid, -1, "CEF todavia no esta listo.");

	new bool:abrir = !InventarioAbierto[playerid];
	CEF_AbrirInventario(playerid, abrir);
	return 1;
}