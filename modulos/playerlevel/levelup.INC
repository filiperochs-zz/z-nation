
#define multiplier  			     (4250)

/*
stock getPlayerNextLevel(playerid) {

	if (PlayerData[playerid][dLevel] < 2) return 4250;
	return ((PlayerData[playerid][dLevel] * multiplier) + (PlayerData[playerid][dLevel] * (multiplier / 2)));
}

stock getPlayerOlderLevel(playerid) {

	new level = PlayerData[playerid][dLevel] - 1;

	if (level < 2) return 0;
	return ((level * multiplier) + (level * (multiplier / 2)));
}*/

stock getPlayerNextLevel(playerid) {

	if (PlayerData[playerid][dLevel] < 2) return multiplier;
	return (PlayerData[playerid][dLevel] - 1) * (multiplier * ((PlayerData[playerid][dLevel] / 10) + 2));
	
}

stock getPlayerOlderLevel(playerid) {

	new level = PlayerData[playerid][dLevel] - 1;

	if (level < 2) return 0;
	return (level - 1) * (multiplier * ((level / 10) + 2));
}

stock checkPlayerLevelUp(playerid) {

	if (!PlayerData[playerid][dLogged]) return 0;

	if (PlayerData[playerid][dPoints] >= getPlayerNextLevel(playerid)) {
	
	    // Add um level
	    PlayerData[playerid][dLevel] ++;
	    
	    // Checar conquista - passou de nivel
		checkPlayerConquista(playerid, Conquista_NextLevel);
	    
	    // Checar conquistas - Niveis
		if (PlayerData[playerid][dLevel] >= 05) checkPlayerConquista(playerid, Conquista_Level5);
		if (PlayerData[playerid][dLevel] >= 10) checkPlayerConquista(playerid, Conquista_Level10);
		if (PlayerData[playerid][dLevel] >= 15) checkPlayerConquista(playerid, Conquista_Level15);
		if (PlayerData[playerid][dLevel] >= 50) checkPlayerConquista(playerid, Conquista_Level50);
	    
	    new string[144];
	    new money = PlayerData[playerid][dLevel] * 215;
		// Atualizar o nivel
		format(string, sizeof (string), "%d", PlayerData[playerid][dLevel]);
		PlayerTextDrawSetString(playerid, textPlayerLevel[playerid], string);
		// setar score
		SetPlayerScore(playerid, PlayerData[playerid][dLevel]);
		
		PlayerData[playerid][dMoney] += money;
	    
	    SendClientMessage(playerid, corBranco, "_______________________________________________________________");
	    SendLanguageMessage(playerid, corBranco, "LEVEL1");
	    SendLanguageMessagef(playerid, corBranco, "LEVEL2", PlayerData[playerid][dLevel], getMoneyFormat(money));
	    SendClientMessage(playerid, corBranco, "_______________________________________________________________");
	    
	    // Salvar conta
	    savePlayerAccount(playerid);
	    
	    return 1;
	}
	return 0;
}
