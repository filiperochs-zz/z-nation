
#define tab_maxplayers   (20)

new Text:textTabList[6];

stock tab_CreateTextdraws() {

	textTabList[0] = TextDrawCreate(144.000000, 145.000000, "mdl-1019:test");
	TextDrawBackgroundColor(textTabList[0], 255);
	TextDrawFont(textTabList[0], 4);
	TextDrawLetterSize(textTabList[0], 0.500000, 1.000000);
	TextDrawColor(textTabList[0], -56);
	TextDrawSetOutline(textTabList[0], 0);
	TextDrawSetProportional(textTabList[0], 1);
	TextDrawSetShadow(textTabList[0], 1);
	TextDrawUseBox(textTabList[0], 1);
	TextDrawBoxColor(textTabList[0], 255);
	TextDrawTextSize(textTabList[0], 343.000000, 244.000000);
	TextDrawSetSelectable(textTabList[0], 1);

	textTabList[1] = TextDrawCreate(157.000000, 180.000000, "Ninguem");
	TextDrawBackgroundColor(textTabList[1], 0);
	TextDrawFont(textTabList[1], 1);
	TextDrawLetterSize(textTabList[1], 0.170000, 1.000000);
	TextDrawColor(textTabList[1], -106);
	TextDrawSetOutline(textTabList[1], 0);
	TextDrawSetProportional(textTabList[1], 1);
	TextDrawSetShadow(textTabList[1], 1);
	TextDrawSetSelectable(textTabList[1], 0);

	textTabList[2] = TextDrawCreate(249.000000, 181.000000, "00:00:00");
	TextDrawBackgroundColor(textTabList[2], 0);
	TextDrawFont(textTabList[2], 2);
	TextDrawLetterSize(textTabList[2], 0.160000, 1.000000);
	TextDrawColor(textTabList[2], -176);
	TextDrawSetOutline(textTabList[2], 0);
	TextDrawSetProportional(textTabList[2], 1);
	TextDrawSetShadow(textTabList[2], 1);
	TextDrawSetSelectable(textTabList[2], 0);

	textTabList[3] = TextDrawCreate(300.000000, 181.000000, "0");
	TextDrawBackgroundColor(textTabList[3], 0);
	TextDrawFont(textTabList[3], 2);
	TextDrawLetterSize(textTabList[3], 0.160000, 1.000000);
	TextDrawColor(textTabList[3], -176);
	TextDrawSetOutline(textTabList[3], 0);
	TextDrawSetProportional(textTabList[3], 1);
	TextDrawSetShadow(textTabList[3], 1);
	TextDrawSetSelectable(textTabList[3], 0);

	textTabList[4] = TextDrawCreate(342.000000, 181.000000, "0");
	TextDrawBackgroundColor(textTabList[4], 0);
	TextDrawFont(textTabList[4], 2);
	TextDrawLetterSize(textTabList[4], 0.160000, 1.000000);
	TextDrawColor(textTabList[4], -176);
	TextDrawSetOutline(textTabList[4], 0);
	TextDrawSetProportional(textTabList[4], 1);
	TextDrawSetShadow(textTabList[4], 1);
	TextDrawSetSelectable(textTabList[4], 0);

	textTabList[5] = TextDrawCreate(382.000000, 181.000000, "-");
	TextDrawBackgroundColor(textTabList[5], 0);
	TextDrawFont(textTabList[5], 1);
	TextDrawLetterSize(textTabList[5], 0.170000, 1.000000);
	TextDrawColor(textTabList[5], -106);
	TextDrawSetOutline(textTabList[5], 0);
	TextDrawSetProportional(textTabList[5], 1);
	TextDrawSetShadow(textTabList[5], 1);
	TextDrawSetSelectable(textTabList[5], 0);
}

stock showTabList(playerid) {
	for(new text; text < sizeof (textTabList); text++) {
	    TextDrawShowForPlayer(playerid, textTabList[text]);
	}
}

stock hideTabList(playerid) {
	for(new text; text < sizeof (textTabList); text++) {
	    TextDrawHideForPlayer(playerid, textTabList[text]);
	}
}

stock tab_Update() {

	// Variaveis
	new tablist_players[tab_maxplayers] = {-1, ...};
	new tablist_timlive[tab_maxplayers] = {00, ...};
	static tablist_string[620];
	new tablist_format[75];
	
	serverCountSurvivors = 0;
	
	// Loop nos players
	foreach(new playerid : Player) {
	
	    // Checar se o player está logado
	    if (PlayerData[playerid][dServerState] != SERVER_STATE_SURVIVAL) continue;

        serverCountSurvivors ++;

		// Loop na lista de players
		for (new slotid; slotid < tab_maxplayers; slotid++) {
		
		    // Checar se o tempo de vida dele é maior
		    if (PlayerData[playerid][dTempoVivo] > tablist_timlive[slotid]) {
		    
		        // Passar a fila
		        for (new slotnext = tab_maxplayers - 1; slotnext > slotid; slotnext--) {
					tablist_players[slotnext] = tablist_players[slotnext - 1];
					tablist_timlive[slotnext] = tablist_timlive[slotnext - 1];
				}
				
				// Guardar o id e o tempo vivo
				tablist_players[slotid] = playerid;
				tablist_timlive[slotid] = PlayerData[playerid][dTempoVivo];
				
				break;
			}
		}
	}
	
	// Update nas Textdraws
	
	tablist_string[0] = EOS;
	
	for (new slotid; slotid < tab_maxplayers; slotid++) {
	
	    new playerid = tablist_players[slotid];
	    
	    if ( playerid != -1 ) {
	    
	        format(tablist_format, sizeof (tablist_format), "%s~n~", getNome(playerid));
	        strcat(tablist_string, tablist_format);
	    }
	}
	TextDrawSetString(textTabList[1], tablist_string);
	
	tablist_string[0] = EOS;

	for (new slotid; slotid < tab_maxplayers; slotid++) {

	    new playerid = tablist_players[slotid];

	    if ( playerid != -1 ) {

	        format(tablist_format, sizeof (tablist_format), "%s~n~", ConvertTime(PlayerData[playerid][dTempoVivo]));
	        strcat(tablist_string, tablist_format);
	    }
	}
	TextDrawSetString(textTabList[2], tablist_string);
	
	tablist_string[0] = EOS;

	for (new slotid; slotid < tab_maxplayers; slotid++) {

	    new playerid = tablist_players[slotid];

	    if ( playerid != -1 ) {

	        format(tablist_format, sizeof (tablist_format), "%d~n~", PlayerData[playerid][dKills]);
	        strcat(tablist_string, tablist_format);
	    }
	}
	TextDrawSetString(textTabList[3], tablist_string);
	
	tablist_string[0] = EOS;

	for (new slotid; slotid < tab_maxplayers; slotid++) {

	    new playerid = tablist_players[slotid];

	    if ( playerid != -1 ) {

	        format(tablist_format, sizeof (tablist_format), "%d~n~", PlayerData[playerid][dZombieKills]);
	        strcat(tablist_string, tablist_format);
	    }
	}
	TextDrawSetString(textTabList[4], tablist_string);
	
	tablist_string[0] = EOS;

	for (new slotid; slotid < tab_maxplayers; slotid++) {

	    new playerid = tablist_players[slotid];

	    if ( playerid != -1 ) {

	        format(tablist_format, sizeof (tablist_format), "%s~n~", getPlayerServerGroupName(playerid));
	        strcat(tablist_string, tablist_format);
	    }
	}
	TextDrawSetString(textTabList[5], tablist_string);
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if (PlayerData[playerid][dLogged]) {
	
		if ( PRESSED(1) && !IsPlayerInBattleRoyale(playerid) ) {
		    showTabList(playerid);
		}

		else if ( RELEASED(1) ) {
	        hideTabList(playerid);
		}
	}

	#if defined tabOnPlayerKeyStateChange
	    return tabOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange tabOnPlayerKeyStateChange
#if defined tabOnPlayerKeyStateChange
	forward tabOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif









