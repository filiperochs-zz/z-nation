// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Barulho do player
new
	Float:playerBarulho[MAX_PLAYERS];

// Ultimo barulho
new
	lastRuidoTick;

#pragma unused lastRuidoTick

// Fazer barulho

stock applyRuido(Float:x, Float:y, Float:z, Float:altura = 150.0, Float:maxaltura = 14.0) {

	// Loop nos players
	foreach(new playerid : Player) {
	
 		new Float:range = GetPlayerDistanceFromPoint(playerid, x, y, z);
 		
 		if (range < altura) {

			new Float:result = 14.0 - ( (range / altura) * 15.0 );
 		    
 		    if (playerBarulho[playerid] > result)
 		        return 1;
 		    
 		    playerBarulho[playerid] = result;
 		    
 		    if (playerBarulho[playerid] > maxaltura) {
 		        playerBarulho[playerid] = maxaltura;
			}
 		}
	}
	
	return 1;
}

stock updatePlayerRuido(playerid) {

	if (playerBarulho[playerid] > 1.0) {
	
	    // Remover barulho
	
	    playerBarulho[playerid] -= 1.2;
	    
	    if (playerBarulho[playerid] < 1.0)
	        playerBarulho[playerid] = 1.0;
	
	    // Textdarw
		new string[2][75] = { {"-"},{"-"} };
	
	    for(new Float:index = 1.0; index < playerBarulho[playerid] + (frandom(2.5) - frandom(2.5)); index += 1.0) {

			if (index < 0.0 || index > 14.0) break;

			strcat(string[0], "~n~-");
	    }
	    
	    for(new Float:index = 1.0; index < playerBarulho[playerid] + (frandom(2.5) - frandom(2.5)); index += 1.0) {

			if (index < 0.0 || index > 14.0) break;

			strcat(string[1], "~n~-");
	    }
	    PlayerTextDrawSetString(playerid, textPlayerBarulho[0], playerBarulho[playerid] == 1.0 ? ("-") : (string[0]));
	    PlayerTextDrawSetString(playerid, textPlayerBarulho[1], playerBarulho[playerid] == 1.0 ? ("-") : (string[1]));
	}
}

/*
CMD:barulho(playerid, params[]) {

	new Float:x, Float:y, Float:z, value = strval(params[0]);
	
	GetPlayerPos(playerid, x, y, z);
	
	applyRuido(x, y + float(value), z, 85);

	return 1;
}
*/





