
#define MAX_TEXT_LINES (5)

enum textLinesEnum {
	linesText[128],
	linesTime,
Float:
	linesBoxSize,
}
new TextLines[MAX_PLAYERS][MAX_TEXT_LINES][textLinesEnum];

stock SendServerMessageToPlayer(playerid, text[]) {

	new len = strlen(text);

	if (!len)
	    return 0;

	// Rolar o chat
	for(new textline = MAX_TEXT_LINES - 1; textline > 0; textline--) {

	    format(TextLines[playerid][textline][linesText], 128, TextLines[playerid][textline - 1][linesText]);

	    TextLines[playerid][textline][linesTime] = TextLines[playerid][textline - 1][linesTime];
	    TextLines[playerid][textline][linesBoxSize] = TextLines[playerid][textline - 1][linesBoxSize];

		if (gettime() < TextLines[playerid][textline][linesTime]) {
		    PlayerTextDrawSetString(playerid, textChat[textline], TextLines[playerid][textline][linesText]);
		    PlayerTextDrawTextSize(playerid, textChat[textline], 0.000000, TextLines[playerid][textline][linesBoxSize]);
			PlayerTextDrawShow(playerid, textChat[textline]);
		} else {
		    PlayerTextDrawHide(playerid, textChat[textline]);
		}
	}

	for(new index = len; index > -1; index--)
	{
	    if (text[index] == ' ')
		{
	        text[index] = '_';
		}
	}

	// Formatar
	format(TextLines[playerid][0][linesText], 128, text);
	TextLines[playerid][0][linesBoxSize] = len * 3.3;

	// Setar a msg na textdraw
	PlayerTextDrawSetString(playerid, textChat[0], text);
	PlayerTextDrawTextSize(playerid, textChat[0], 0.000000, TextLines[playerid][0][linesBoxSize]);
	PlayerTextDrawShow(playerid, textChat[0]);

	// Setar a cor
	TextLines[playerid][0][linesTime] = gettime() + 5;
	
	return 1;
}

stock SendServerMessage(text[]) {

	// Rolar o chat
	foreach(new playerid : Player) {
	    SendServerMessageToPlayer(playerid, text);
	}
}

stock SendDayZMessage(text[]) {

	// Rolar o chat
	foreach(new playerid : Player) {

	    if (PlayerData[playerid][dServerState] != SERVER_STATE_SURVIVAL)
	        continue;

	    SendServerMessageToPlayer(playerid, text);
	}
}

stock SendBattleRoyaleMessage(text[]) {

	// Rolar o chat
	foreach(new playerid : Player) {
	
	    if (!IsPlayerInBattleRoyale(playerid))
	        continue;
	
	    SendServerMessageToPlayer(playerid, text);
	}
}

callback updatePlayersChat()
{
	foreach(new playerid : Player)
	{
		for(new textline; textline < MAX_TEXT_LINES; textline++) {

			if ( strlen (TextLines[playerid][textline][linesText]) < 2 )
				continue;

			if (gettime() > TextLines[playerid][textline][linesTime]) {
			    PlayerTextDrawHide(playerid, textChat[textline]);
			    format(TextLines[playerid][textline][linesText], 3, "_");
			}
		}
	}
}

stock ShowPlayerTextChat(playerid) {

	for(new textline; textline != MAX_TEXT_LINES; textline++) {
	    PlayerTextDrawShow(playerid, textChat[textline]);
	}
}

stock HidePlayerTextChat(playerid) {

	for(new textline; textline != MAX_TEXT_LINES; textline++) {
	    PlayerTextDrawHide(playerid, textChat[textline]);
	}
}


CMD:sendmessageex(playerid, params[]) {

    SendServerMessageToPlayer(playerid, params);
	return 1;
}







