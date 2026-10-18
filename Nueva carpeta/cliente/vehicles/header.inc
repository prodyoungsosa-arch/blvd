new totalvehiculos = 1;			//vehículos dinámicos
new CompraVehiculo[MAX_PLAYERS], BuyVIPvehicle[MAX_PLAYERS];
new IntentarPuente[MAX_PLAYERS]; // Uso del CMD /puente.
new arr_Engine[MAX_VEHICLES char];
new gLastCar[MAX_PLAYERS];
new EstereoCoche = 1150;
new PlayerMaleteroVeh[MAX_PLAYERS];
new interior_veh[MAX_VEHICLES];

enum documentalveh
{
	elModelo,
	elNombre[32],
	elPrecio,
	elMaxMaletero,
};

new infovehicle[][documentalveh] =
{
	{400, "Landstalker", 8900, 10},
	{401, "Bravura", 3200, 6},
	{402, "Buffalo", 77550, 8},
	{403, "Linerunner", 5, 10},
	{404, "Perennial", 2550, 6},
	{405, "Sentinel", 3700, 6},
	{406, "Dumper", 25, 10},
	{407, "Firetruck", 0, 0},
	{408, "Trashmaster", 10, 10},
	{409, "Stretch", 10, 10},
	{410, "Manana", 1800, 6},
	{411, "Infernus", 30, 10},
	{412, "Voodoo", 4130, 6},
	{413, "Pony", 5100, 10},
	{414, "Mule", 9430, 10},
	{415, "Cheetah", 265230, 8},
	{416, "Ambulance", 0, 0},
	{417, "Leviathan", 0, 10},
	{418, "Moonbeam", 2290, 10},
	{419, "Esperanto", 2100, 6},
	{420, "Taxi", 6400, 6},
	{421, "Washington", 8900, 8},
	{422, "Bobcat", 1500, 10},
	{423, "Mr. Whoopee", 4, 10},
	{424, "BF Injection", 146920, 6},
	{425, "Hunter", 0, 10},
	{426, "Premier", 8500, 6},
	{427, "Enforcer", 0, 10},
	{428, "Securicar", 0, 10},
	{429, "Banshee", 326450, 6},
	{430, "Predator", 0, 5},
	{431, "Bus", 7, 10},
	{432, "Rhino", 0, 4},
	{433, "Barracks", 0, 10},
	{434, "Hotknife", 10, 4},
	{435, "Article Trailer 1", 0, 10},
	{436, "Previon", 2200, 6},
	{437, "Coach", 6, 10},
	{438, "Cabbie", 4750, 6},
	{439, "Stallion", 2700, 6},
	{440, "Rumpo", 4100, 10},
	{441, "RC Bandit", 0, 2},
	{442, "Romero", 7000, 10},
	{443, "Packer", 15, 10},
	{444, "Monster", 35, 10},
	{445, "Admiral", 9300, 6},
	{446, "Squallo", 20, 6},
	{447, "Seasparrow", 0, 4},
	{448, "Pizzaboy", 1500, 2},
	{449, "Tram", 0, 6},
	{450, "Article Trailer 2", 0, 10},
	{451, "Turismo", 30, 8},
	{452, "Speeder", 0, 10},
	{453, "Reefer", 3, 10},
	{454, "Tropic", 4, 10},
	{455, "Flatbed", 0, 10},
	{456, "Yankee", 12890, 10},
	{457, "Caddy", 8, 3},
	{458, "Solair", 2100, 6},
	{459, "Topfun Van", 4750, 10},
	{460, "Skimmer", 15, 4},
	{461, "PCJ-600", 25578, 2},
	{462, "Faggio", 1200, 3},
	{463, "Freeway", 7900, 3},
	{464, "RC Baron", 0, 3},
	{465, "RC Raider", 0, 3},
	{466, "Glendale", 1400, 6},
	{467, "Oceanic", 3300, 6},
	{468, "Sanchez", 20200, 3},
	{469, "Sparrow", 0, 3},
	{470, "Patriot", 30, 10},
	{471, "Quad", 15000, 2},
	{472, "Coastguard", 0, 6},
	{473, "Dinghy", 5000, 4},
	{474, "Hermes", 3200, 5},
	{475, "Sabre", 1500, 5},
	{476, "Rustler", 12, 4},
	{477, "ZR-350", 196000, 5},
	{478, "Walton", 1350, 10},
	{479, "Regina", 3450, 5},
	{480, "Comet", 273400, 6},
	{481, "BMX", 570, 0},
	{482, "Burrito", 10790, 10},
	{483, "Camper", 7660, 10},
	{484, "Marquis", 15, 6},
	{485, "Baggage", 3, 2},
	{486, "Dozer", 4, 3},
	{487, "Maverick", 40, 10},
	{488, "SAN News Maverick", 35, 10},
	{489, "Rancher", 39050, 10},
	{490, "FBI Rancher", 0, 10},
	{491, "Virgo", 4000, 5},
	{492, "Greenwood", 7000, 5},
	{493, "Jetmax", 25, 4},
	{494, "Hotring Racer", 25, 5},
	{495, "Sandking", 20, 10},
	{496, "Blista Compact", 7000, 5},
	{497, "Police Maverick", 0, 10},
	{498, "Boxville", 8000, 10},
	{499, "Benson", 5500, 12},
	{500, "Mesa", 4200, 8},
	{501, "RC Goblin", 0, 1},
	{502, "Hotring Racer A", 25, 5},
	{503, "Hotring Racer B", 25, 5},
	{504, "Bloodring Banger", 20, 5},
	{505, "Rancher Lure", 0, 10},
	{506, "Super GT", 524900, 6},
	{507, "Elegant", 8400, 8},
	{508, "Journey", 7355, 10},
	{509, "Bike", 595, 0},
	{510, "Mountain Bike", 700, 0},
	{511, "Beagle", 0, 10},
	{512, "Cropduster", 5, 8},
	{513, "Stuntplane", 6, 8},
	{514, "Tanker", 15, 10},
	{515, "Roadtrain", 15, 10},
	{516, "Nebula", 4200, 5},
	{517, "Majestic", 5500, 5},
	{518, "Buccaneer", 4300, 5},
	{519, "Shamal", 25, 10},
	{520, "Hydra", 0, 10},
	{521, "FCR-900", 27900, 3},
	{522, "NRG-500", 20, 4},
	{523, "HPV1000", 0, 3},
	{524, "Cement Truck", 15, 5},
	{525, "Towtruck", 6, 7},
	{526, "Fortune", 1890, 5},
	{527, "Cadrona", 1800, 5},
	{528, "FBI Truck", 0, 9},
	{529, "Willard", 1670, 6},
	{530, "Forklift", 5, 1},
	{531, "Tractor", 0, 2},
	{532, "Combine Harvester", 0, 3},
	{533, "Feltzer", 4880, 5},
	{534, "Remington", 6350, 6},
	{535, "Slamvan", 7340, 7},
	{536, "Blade", 8450, 5},
	{537, "Freight (Train)", 0, 10},
	{538, "Brownstreak (Train)", 0, 10},
	{539, "Vortex", 0, 2},
	{540, "Vincent", 3800, 6},
	{541, "Bullet", 20, 8},
	{542, "Clover", 1810, 4},
	{543, "Sadler", 1789, 7},
	{544, "Firetruck LA", 0, 10},
	{545, "Hustler", 3980, 5},
	{546, "Intruder", 4420, 5},
	{547, "Primo", 2870, 5},
	{548, "Cargobob", 0, 10},
	{549, "Tampa", 1430, 4},
	{550, "Sunrise", 1260, 6},
	{551, "Merit", 3250, 5},
	{552, "Utility Van", 0, 10},
	{553, "Nevada", 0, 10},
	{554, "Yosemite", 5400, 10},
	{555, "Windsor", 17900, 6},
	{556, "Monster A", 30, 6},
	{557, "Monster B", 30, 6},
	{558, "Uranus", 138000, 5},
	{559, "Jester", 318000, 5},
	{560, "Sultan", 103590, 10},
	{561, "Stratum", 6000, 8},
	{562, "Elegy", 78690, 6},
	{563, "Raindance", 0, 10},
	{564, "RC Tiger", 0, 1},
	{565, "Flash", 55600, 5},
	{566, "Tahoma", 9700, 6},
	{567, "Savanna", 3700, 6},
	{568, "Bandito", 0, 2},
	{569, "Freight Flat Trailer", 0, 10},
	{570, "Streak Trailer", 0, 10},
	{571, "Kart", 10, 2},
	{572, "Mower", 5, 2},
	{573, "Dune", 5, 4},
	{574, "Sweeper", 0, 2},
	{575, "Brouge", 5700, 6},
	{576, "Tornado", 2990, 6},
	{577, "AT400", 0, 10},
	{578, "DFT-30", 10, 6},
	{579, "Huntley", 245000, 10},
	{580, "Stafford", 7900, 8},
	{581, "BF-400", 19500, 3},
	{582, "Newsvan", 0, 10},
	{583, "Tug", 0, 3},
	{584, "Petrol Trailer", 0, 0},
	{585, "Emperor", 640, 5},
	{586, "Wayfarer", 2860, 3},
	{587, "Euros", 64345, 5},
	{588, "Hotdog", 5, 10},
	{589, "Club", 17650, 6},
	{590, "Freight Box Trailer", 0, 10},
	{591, "Article Trailer 3", 0, 10},
	{592, "Andromada", 0, 10},
	{593, "Dodo", 7, 10},
	{594, "RC Cam", 0, 0},
	{595, "Launch", 0, 10},
	{596, "Car LSPD", 0, 10},
	{597, "Car SFPD", 0, 10},
	{598, "Car LVPD", 0, 10},
	{599, "Police Ranger", 0, 10},
	{600, "Picador", 345, 5},
	{601, "SWAT", 0, 10},
	{602, "Alpha", 214090, 5},
	{603, "Phoenix", 265098, 5},
	{604, "Glendale roto", 640, 3},
	{605, "Sadler roto", 750, 3},
	{606, "Baggage Trailer A", 0, 2},
	{607, "Baggage Trailer B", 0, 2},
	{608, "Tug Stairs Trailer", 0, 0},
	{609, "Boxville", 4, 10},
	{610, "Farm Trailer", 0, 0},
	{611, "Utility Trailer", 0, 0}
};

// vehículos dinámicos, renovación en sql 09/01/2019 by EdinsonWalker
new veh_gasolina[MAX_VEHICLES] = 200;

enum PVinfo
{
	vID_sql,                            // id en base de datos
	vIG_id,                             // id dentro del servidor (/dl)
	vNombre[128],                       // nombre
	vPropietario[MAX_PLAYER_NAME],      // propietario
	vTipo,								// tipo (0: usuarios, 1..50: facciones, 200: vip, 300: admin, 600: renta)
	vNegocio,
	vTrabajo,
	vModelo,                            // modelo
	Float: vPosicionX,                  // X
	Float: vPosicionY,                  // Y
	Float: vPosicionZ,                  // Z
	Float: vPosicionR,                  // Angle
	vInterior,                          // Interior
	vVirtualWorld,                      // VirtualWorld
	Float: vEndPosicionX,                  // X
	Float: vEndPosicionY,                  // Y
	Float: vEndPosicionZ,                  // Z
	Float: vEndPosicionR,                  // Angle
	vEndInterior,                          // Interior
	vEndVirtualWorld,                      // VirtualWorld
	Float: vVida,                       // Vida
	vDanioSuperficie,                   // Daño superficie
	vDanioPuertas,                      // Daño puertas
	vDanioLuces,                        // Daño luces
	vDanioRuedas,                       // Daño ruedas
	vGasolina,							// Gasolina
	vColor_1,                           // Color 1
	vColor_2,                           // Color 2
	vPaintJob,                          // Paint job
	vSeguro,							// Con seguro puesto
	vPrecio,                            // Precio
	vEmbargo,                           // Embargo
	vMulta,                             // Multa
	vMaletero[10],                      // Maletero
	vMaleteroCant[10],                  // Maletero cantidad
	vMaxMaletero,                       // Máximo maletero
	vModificacion[MAX_MODIFICACIONES],	// Tunning
	vCallSign[40],                      // Callsign
	vObjModelo[5],
	Float: vObjPosX[5],
	Float: vObjPosY[5],
	Float: vObjPosZ[5],
	Float: vObjRotX[5],
	Float: vObjRotY[5],
	Float: vObjRotZ[5],
	vSirena,                            // Sirena
	vPremium,
	vCompartida1[MAX_PLAYER_NAME],
	vCompartida2[MAX_PLAYER_NAME],
	vCompartida3[MAX_PLAYER_NAME],
	vStereo,
	//no save:
	vSpawned,                           // Spawned
	vTimeSave,                          // Tiempo en que se guardará.
	vMaleteroOn,                        // 0 cerrado, 1 abierto
	vRentaDueno[MAX_PLAYER_NAME],       // Renta dueño
	vRentaTiempo,                       // Renta tiempo
	Text3D: vOnCallSign,                // Label callsign
	vTuneo[5],
};
new InfoVehiculo[MAX_VEHICULOS][PVinfo];

new OneSeatVehicles[38] =
{
    425, 430, 432, 441, 446, 448, 452, 453,
	454, 464, 465, 472, 473, 476, 481, 484,
	485, 486, 493, 501, 509, 510, 519, 520,
	530, 531, 532, 539, 553, 564, 568, 571,
	572, 574, 583, 592, 594, 595
};

new VehicleName[212][] = {
	"Landstalker","Bravura","Buffalo","Linerunner","Perennial","Sentinel","Dumper","Firetruck","Trashmaster","Stretch",
	"Manana","Infernus","Voodoo","Pony","Mule","Cheetah","Ambulance","Leviathan","Moonbeam","Esperanto","Taxi",
	"Washington","Bobcat","Mr Whoopee","BF Injection","Hunter","Premier","Enforcer","Securicar","Banshee","Predator",
	"Bus","Rhino","Barracks","Hotknife","Trailer","Previon","Coach","Cabbie","Stallion","Rumpo","RC Bandit", "Romero",
	"Packer","Monster","Admiral","Squalo","Seasparrow","Pizzaboy","Tram","Trailer","Turismo","Speeder","Reefer","Tropic","Flatbed",
	"Yankee","Caddy","Solair","Berkleys RC Van","Skimmer","PCJ-600","Faggio","Freeway","RC Baron","RC Raider",
	"Glendale","Oceanic","Sanchez","Sparrow","Patriot","Quad","Coastguard","Dinghy","Hermes","Sabre","Rustler",
	"ZR-350","Walton","Regina","Comet","BMX","Burrito","Camper","Marquis","Baggage","Dozer","Maverick","News Chopper",
	"Rancher","FBI Rancher","Virgo","Greenwood","Jetmax","Hotring Racer","Sandking","Blista Compact","Police Maverick",
	"Boxville","Benson","Mesa","RC Goblin","Hotring Racer A","Hotring Racer B","Bloodring Banger","Rancher","Super GT",
	"Elegant","Journey","Bike","Mountain Bike","Beagle","Cropduster","Stuntplane","Tanker","Road Train","Nebula","Majestic",
	"Buccaneer","Shamal","Hydra","FCR-900","NRG-500","HPV-1000","Cement Truck","Tow Truck","Fortune","Cadrona","FBI Truck",
	"Willard","Forklift","Tractor","Combine","Feltzer","Remington","Slamvan","Blade","Freight","Streak","Vortex","Vincent",
	"Bullet","Clover","Sadler","Firetruck","Hustler","Intruder","Primo","Cargobob","Tampa","Sunrise","Merit","Utility",
	"Nevada","Yosemite","Windsor","Monster A","Monster B","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RC Tiger",
	"Flash","Tahoma","Savanna","Bandito","Freight","Trailer","Kart","Mower","Duneride","Sweeper","Brouge",
	"Tornado","AT-400","DFT-30","Huntley","Stafford","BF-400","Newsvan","Tug","Trailer","Emperor","Wayfarer",
	"Euros","HotDog","Club","Trailer","Trailer","Andromada","Dodo","RCCam","Launch","Police Car (LSPD)","Police Car (SFPD)",
	"Police Car (LVPD)","Police Ranger","Picador","S.W.A.T. Van","Alpha","Phoenix","Glendale","Sadler","Luggage Trailer A",
	"Luggage Trailer B","Stair Trailer","Boxville","Farm Plow","Utility Trailer"
};