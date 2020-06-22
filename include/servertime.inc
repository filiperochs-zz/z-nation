
static
 	serverTimeHour;
	   
#define IsPlayerToggleHour(%0)  GetPVarInt(%0, "toggleHour")

stock ForceGlobalWeather(weatherid)
	SetWeather(weatherid);
	
stock ForceGlobalWorldTime(hour)
	SetWorldTime(hour);

stock server_SetWorldTime(hour) {

    serverTimeHour = hour;
    
    foreach(new playerid : Player) {
    
        if (!IsPlayerToggleHour(playerid) && IsPlayerAutomaticWeather(playerid)) {
            SetPlayerTime(playerid, serverTimeHour, 0);
        }
    }
    return 1;
}

stock server_SetWeather(weatherid) {

    foreach(new playerid : Player) {

		if (!IsPlayerLoggedIn(playerid))
		    continue;

        if (!IsPlayerToggleHour(playerid) && IsPlayerAutomaticWeather(playerid)) {
        
            if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
                continue;
        
            SetPlayerWeather(playerid, weatherid);
        }
    }
    return 1;
}

stock server_SetWeatherAndTime(hour, weatherid)
{
    serverTimeHour = hour;

    foreach(new playerid : Player) {
        SetPlayerTime(playerid, serverTimeHour, 0);
		if (!IsPlayerLoggedIn(playerid))
		    continue;

		if (!IsPlayerToggleHour(playerid)) {
			
            if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
                continue;

            SetPlayerWeather(playerid, weatherid);
        }
	}
}

stock TogglePlayerServerTime(playerid, toggle) {
	SetPVarInt(playerid, "toggleHour", toggle);
}

stock SetPlayerServerTime(playerid) {
    SetPlayerTime(playerid, serverTimeHour, 0);
}

#define SetWorldTime server_SetWorldTime
#define SetWeather 	 server_SetWeather
