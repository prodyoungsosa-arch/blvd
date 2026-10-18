new
    StationOfYear[32] = "Estación del año",
    DegreesEx = 10,
    Humidity = 30,
	TheUseDegrees[MAX_PLAYERS]
;
new
    ServerWeather = -1,
	PlayerWeather[MAX_PLAYERS]
;

enum WeatherData
{
    wID
};

new RandomWeatherID[][wID] =
{
    {0}, {1}, {2}, {3},
    {4}, {5}, {6}, {7},
    {8}, {9}, {10}, {11},
    {14}
};

stock ShowWeatherData(playerid, bool:new_user = false)
{
    static
        string[128],
        date[6];

    getdate(date[2], date[1], date[0]),
    gettime(date[3], date[4], date[5]);

    if (date[1] == 12 || (date[1] > 0 && date[1] < 3)) StationOfYear = "Invierno"; // Invierno en USA
    else if (date[1] > 2 && date[1] < 6) StationOfYear = "Primavera"; // Primavera en USA
    else if (date[1] > 5 && date[1] < 9) StationOfYear = "Verano"; // Verano en USA
    else if (date[1] > 8 && date[1] < 12) StationOfYear = "Otoño"; // Otoño en USA

    if (TheUseDegrees[playerid] == 0)
    {
        TheUseDegrees[playerid] = 1;

        format(string, sizeof(string), Desbug("%s,~n~%d%c de humedad,~n~%d grados celsius."), StationOfYear, Humidity, '%', DegreesEx);
    }
    else if (TheUseDegrees[playerid] == 1)
    {
        TheUseDegrees[playerid] = 0;

        format(string, sizeof(string), Desbug("%s,~n~%d%c de humedad,~n~%d grados celsius."), StationOfYear, Humidity, '%', DegreesEx + 1);
    }

    if (!new_user)
    {
	    	CrearNotificacion(playerid, "none", string, 3);
	}
	else
	{
		CrearNotificacion(playerid, "none", string, 3);
	}
    return true;
}

funcion ReconfigureWeather()
{
    SetWeatherEx(7);
    return true;
}

stock SetWeatherEx(weatherid)
{
    SetWeather(weatherid),
    ServerWeather = weatherid;

    foreach (new i : Player)
    {
    	if (IsPlayerConnected(i))
        {
            PlayerWeather[i] = weatherid;
        }
    }

    return true;
}

stock SetPlayerWeatherEx(playerid, weatherid)
{
    SetPlayerWeather(playerid, weatherid);
    PlayerWeather[playerid] = weatherid;

    return true;
}

funcion Update_Weather()
{
    new
        rand = random(sizeof(RandomWeatherID)),
        hour,
        minute,
        date[3]
    ;

    SetWeatherEx(RandomWeatherID[rand][wID]);

    switch (RandomWeatherID[rand][wID])
    {
        case 8: // Lluvia
            SetTimer("ReconfigureWeather", 900000, true);

        case 9: // Neblina
            SetTimer("ReconfigureWeather", 900000, true);
    }

    gettime(hour, minute),
    getdate(date[0], date[1], date[2]);

    if (date[1] == 12 || (date[1] > 0 && date[1] < 3)) // Invierno en USA
    {
        if (7 < hour < 17) DegreesEx = 18, Humidity = 9; // Mañana y tarde
        else DegreesEx = 5, Humidity = 25; // Por la noche
    }
    else if (date[1] > 2 && date[1] < 6) // Primavera en USA
    {
        if (7 < hour < 17) DegreesEx = 26, Humidity = 20; // Mañana y tarde
        else DegreesEx = 15, Humidity = 38; // Por la noche
    }
    else if (date[1] > 5 && date[1] < 9) // Verano en USA
    {
        if (7 < hour < 17) DegreesEx = 35, Humidity = 36; // Mañana y tarde
        else DegreesEx = 25, Humidity = 60; // Por la noche
    }
    else if (date[1] > 8 && date[1] < 12) // Otoño en USA
    {
        if (7 < hour < 17) DegreesEx = 23, Humidity = 21; // Mañana y tarde
        else DegreesEx = 11, Humidity = 30; // Por la noche
    }
    return true;
}