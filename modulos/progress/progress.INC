
enum {

	PROGRESS_NONE,
	PROGRESS_FIXVEH,
	PROGRESS_REFUEL,
	PROGRESS_REFUEL_VEH,
	PROGRESS_FISHING,
	PROGRESS_REVIVING,
	PROGRESS_BANDAGE,
	PROGRESS_BANDAGEI,
	PROGRESS_CUFF,
	PROGRESS_UNCUFF,
	PROGRESS_EXPLOSIVE,
	PROGRESS_ADRENALINA,
	PROGRESS_BARRACA,
	PROGRESS_DBARRACA,
	PROGRESS_KEY_VEH,
	PROGRESS_KEY_COPY,
	PROGRESS_ARMADILHA,
}

// Textdraws
new PlayerText:textPlayerProgress[3];

enum progressEnum {

	bool:
		progressIn,
		progressId,
	Float:
		progressPlayer,
	Float:
	    progressGo,
	Float:
	    progressLose,
		progressTimer,
		progressLastId,
}
static PlayerProgress[MAX_PLAYERS][progressEnum];

stock IsPlayerInProgress(playerid) return PlayerProgress[playerid][progressIn];
stock IsProgressValidId(playerid) {
	if (PlayerProgress[playerid][progressId] != PROGRESS_NONE) return 1;
	return 0;
}
stock StartPlayerProgress(playerid, title[] = "Aguarde...", time=40,  Float:lose=2.0, Float:startG = 0.0, Float:goTo = 100.0, progressid = PROGRESS_NONE) {

	#pragma unused title

	if (IsPlayerInProgress(playerid))
	    return 0;
	    
    #if defined OnPlayerStartProgress
        OnPlayerStartProgress(playerid, progressid);
	#endif

    PlayerProgress[playerid][progressIn]     = true;
    PlayerProgress[playerid][progressPlayer] = startG;
    PlayerProgress[playerid][progressGo] 	 = goTo;
    PlayerProgress[playerid][progressLose]   = lose;
    PlayerProgress[playerid][progressId]     = progressid;
    PlayerProgress[playerid][progressLastId] = 0;
    PlayerProgress[playerid][progressTimer]  = SetTimerEx("UpdatePlayerProgress", time, true, "d", playerid);
	    
	// Dar o titulo para o progresso
	PlayerTextDrawSetString(playerid, textPlayerProgress[1], "0%");
	
	if (progressid != PROGRESS_NONE) {
	    PlayerTextDrawSetString(playerid, textPlayerProgress[2], GetPlayerLanguageKey(playerid, "PROGRESS"));
	    PlayerTextDrawShow(playerid, textPlayerProgress[2]);
	}
	
	// Setar o progresso para 0
	PlayerTextDrawSetString(playerid, textPlayerProgress[0], "mdl-1043:0");
	
	// Mostrar as texts
	ShowPlayerProgress(playerid);
	return 1;
}

stock StopPlayerProgress(playerid) {

	HidePlayerProgress(playerid);

	if (!PlayerProgress[playerid][progressIn] || PlayerProgress[playerid][progressId] == PROGRESS_NONE)
	    return 0;

	PlayerProgress[playerid][progressIn] = false;

    KillTimer(PlayerProgress[playerid][progressTimer]);

    #if defined OnPlayerEndProgress
        OnPlayerStopProgress(playerid, PlayerProgress[playerid][progressId]);
	#endif
	
	return 1;
}

callback UpdatePlayerProgress(playerid) {

	if (PlayerProgress[playerid][progressPlayer] >= PlayerProgress[playerid][progressGo]) {
	
	    PlayerProgress[playerid][progressIn] = false;
	
	    HidePlayerProgress(playerid);
	    
	    KillTimer(PlayerProgress[playerid][progressTimer]);
	    
	    #if defined OnPlayerEndProgress
	        OnPlayerEndProgress(playerid, PlayerProgress[playerid][progressId]);
		#endif
	
	} else {
	
	    PlayerProgress[playerid][progressPlayer] += PlayerProgress[playerid][progressLose];
	    
	    #if defined OnPlayerUpdateProgress
	        OnPlayerUpdateProgress(playerid, PlayerProgress[playerid][progressId], PlayerProgress[playerid][progressPlayer], PlayerProgress[playerid][progressGo]);
		#endif
		new string[15];
		new Float:currentProgress = ((PlayerProgress[playerid][progressPlayer] / PlayerProgress[playerid][progressGo]) * 100.0);
		format(string, sizeof string, "%.0f%", currentProgress);
		PlayerTextDrawSetString(playerid, textPlayerProgress[1], string);
		
		// Update progress textdraw
		string[14] = floatround(currentProgress) / 10;
		if (string[14] != PlayerProgress[playerid][progressLastId])
		{
			format(string, sizeof string, "mdl-1043:%d", string[14]);
			PlayerTextDrawSetString(playerid, textPlayerProgress[0], string);
			
			PlayerProgress[playerid][progressLastId] = string[14];
		}
	}
	
	return 1;
}

stock CreatePlayerTextsProgress(playerid) {
    PlayerProgress[playerid][progressIn] = false;

	textPlayerProgress[0] = CreatePlayerTextDraw(playerid,305.000000, 229.000000, "mdl-1043:30");
	PlayerTextDrawBackgroundColor(playerid,textPlayerProgress[0], 255);
	PlayerTextDrawFont(playerid,textPlayerProgress[0], 4);
	PlayerTextDrawLetterSize(playerid,textPlayerProgress[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textPlayerProgress[0], -56);
	PlayerTextDrawSetOutline(playerid,textPlayerProgress[0], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerProgress[0], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerProgress[0], 1);
	PlayerTextDrawUseBox(playerid,textPlayerProgress[0], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerProgress[0], 255);
	PlayerTextDrawTextSize(playerid,textPlayerProgress[0], 25.000000, 30.000000);
	PlayerTextDrawSetSelectable(playerid,textPlayerProgress[0], 0);

	textPlayerProgress[1] = CreatePlayerTextDraw(playerid,317.000000, 239.000000, "50%");
	PlayerTextDrawAlignment(playerid,textPlayerProgress[1], 2);
	PlayerTextDrawBackgroundColor(playerid,textPlayerProgress[1], 0);
	PlayerTextDrawFont(playerid,textPlayerProgress[1], 2);
	PlayerTextDrawLetterSize(playerid,textPlayerProgress[1], 0.169999, 1.100000);
	PlayerTextDrawColor(playerid,textPlayerProgress[1], -1);
	PlayerTextDrawSetOutline(playerid,textPlayerProgress[1], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerProgress[1], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerProgress[1], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerProgress[1], 0);

	textPlayerProgress[2] = CreatePlayerTextDraw(playerid,319.000000, 267.000000, "PRESS ESC TO CANCEL");
	PlayerTextDrawAlignment(playerid,textPlayerProgress[2], 2);
	PlayerTextDrawBackgroundColor(playerid,textPlayerProgress[2], 0);
	PlayerTextDrawFont(playerid,textPlayerProgress[2], 1);
	PlayerTextDrawLetterSize(playerid,textPlayerProgress[2], 0.139999, 0.799998);
	PlayerTextDrawColor(playerid,textPlayerProgress[2], -76);
	PlayerTextDrawSetOutline(playerid,textPlayerProgress[2], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerProgress[2], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerProgress[2], 1);
	PlayerTextDrawUseBox(playerid,textPlayerProgress[2], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerProgress[2], 150);
	PlayerTextDrawTextSize(playerid,textPlayerProgress[2], 0.000000, 63.000000);
	PlayerTextDrawSetSelectable(playerid,textPlayerProgress[2], 0);
}

stock ShowPlayerProgress(playerid) {

	for(new text; text != 2; text++) {
	    PlayerTextDrawShow(playerid, textPlayerProgress[text]);
	}
}

stock HidePlayerProgress(playerid) {

	for(new text; text != 3; text++) {
	    PlayerTextDrawHide(playerid, textPlayerProgress[text]);
	}
}

CMD:progressex(playerid, params[]) {

	new title[25], time, Float:lose;
	
	if (sscanf(params, "s[25]df", title, time, lose)) return 1;

    StartPlayerProgress(playerid, title, time, lose);

	return 1;
}

forward OnPlayerStartProgress(playerid, progressid);
forward OnPlayerEndProgress(playerid, progressid);
forward OnPlayerStopProgress(playerid, progressid);
forward OnPlayerUpdateProgress(playerid, progressid, Float:current, Float:total);
