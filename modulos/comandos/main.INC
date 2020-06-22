//#include "../modulos/comandos/anims.inc"
#include "../modulos/comandos/admins.inc"
#include "../modulos/comandos/player.inc"

public OnPlayerCommandReceived(playerid, cmdtext[]) {

	if (IsPlayerInIntro(playerid))
	    return 0;

	if (PlayerData[playerid][dLastCommand] > gettime())
	{
	    SendLanguageMessage(playerid, corCinza, "STOP_FLOOD");
	    return 0;
	}

	if (!PlayerData[playerid][dLogged]) {

		SendLanguageMessage(playerid, corError, "MSG_NO_LOGGED");
		
		return 0;
	}
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success) {

	if (!success) {
	    SendLanguageMessagef(playerid, corError, "MSG_INVALID_COMMAND", cmdtext);
	} else {
	    PlayerData[playerid][dLastCommand] = gettime() + 1;
	}
	return 1;
}
