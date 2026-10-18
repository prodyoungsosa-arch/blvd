new VecesHerido[MAX_PLAYERS];

enum dmgInfo
{
	dmgDamage,
	dmgWeapon,
	dmgBodypart,
	dmgSeconds
}
new InfoHerida[MAX_PLAYERS][MAX_HERIDAS][dmgInfo];

new WeaponNames[47][] = // Armas en mano.
{
	"Puños","brass knuckles","golf club","nitestick","knife","baseball bat","shovel","palo de billar","katana","chainsaw","purple dildo","small white vibrator","large white vibrator","silver vibrator",
	"bouquet of flowers","cane","grenade","tear gas grenade","molotov cocktail","jetpack"," "," ","Colt .45","silenced Colt .45","Desert Eagle","12-gauge shotgun","sawn-off shotgun","SPAS-12",
	"Micro Uzi","MP5","AK-47","M4A1","TEC-9","rifle","sniper rifle","rocket launcher","heatseeker","flamethrower","minigun","satchel charge","detonator","spray can","fire extinguisher",
	"camera","nightvision goggles", "thermal goggles","parachute"
};

ResetPlayerHeridas(playerid)
{
	VecesHerido[playerid] = 0;
	Loop(e, MAX_HERIDAS, 0) if (InfoHerida[playerid][e][dmgDamage] != 0)
	{
		InfoHerida[playerid][e][dmgDamage] = 0;
		InfoHerida[playerid][e][dmgWeapon] = 0;
		InfoHerida[playerid][e][dmgBodypart] = 0;
		InfoHerida[playerid][e][dmgSeconds] = 0;
	}
	return 1;
}

GetNameHeridas(bodypart)
{
	new bodyname[24];
	switch (bodypart)
	{
		case 3: alm(bodyname, "Torso");
		case 4: alm(bodyname, "Entrepierna");
		case 5: alm(bodyname, "Brazo izquierdo");
		case 6: alm(bodyname, "Brazo derecho");
		case 7: alm(bodyname, "Pierna izquierda");
		case 8: alm(bodyname, "Pierna derecha");
		case 9: alm(bodyname, "Cabeza");
	}
	return bodyname;
}

GetNameArma(weaponid)
{
	new weapon[32];
    switch (weaponid)
    {
		case 0: weapon = "Puños";
		case 1: weapon = "Nudillera";
		case 2: weapon = "Palo de golf";
		case 3: weapon = "Porra";
		case 4: weapon = "Cuchillo";
		case 5: weapon = "Bate";
		case 6: weapon = "Pala";
		case 7: weapon = "Palo de billar";
		case 8: weapon = "Katana";
		case 9: weapon = "Motosierra";
		case 10: weapon = "Consolador rosa";
		case 11: weapon = "Consolador pequeño";
		case 12: weapon = "Consolador largo";
		case 13: weapon = "Consolador plateado";
		case 14: weapon = "Flores";
		case 15: weapon = "Bastón";
		case 16: weapon = "Granada";
		case 17: weapon = "Granada de gas";
		case 22: weapon = "9mm";
		case 23: weapon = "9mm con silenciador";
		case 24: weapon = "Desert eagle";
		case 25: weapon = "Escopeta";
		case 26: weapon = "Recortada";
		case 27: weapon = "Escopeta de combate";
		case 28: weapon = "Uzi";
		case 29: weapon = "MP5";
		case 30: weapon = "Ak47";
		case 31: weapon = "M4";
		case 32: weapon = "Tec9";
		case 33: weapon = "Rifle de caza";
		case 34: weapon = "Rifle de francotirador";
		case 35: weapon = "Cohete";
		case 36: weapon = "RPG Cohete";
		case 37: weapon = "Lanzallamas";
		case 38: weapon = "Minigun";
		case 41: weapon = "Spray";
		case 42: weapon = "Extintor";
		default: GetWeaponName(weaponid, weapon, sizeof weapon);
    }
	return weapon;
}
