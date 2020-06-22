
#include "../modulos/adminspec/freecam.inc"

#define MaxServerAdmins 25

stock UpdateAdminsPlayersTextLabels() {
	// variables
	new adminsLoggedCount;
	new adminsIndexCount[MaxServerAdmins] = { -1, ... };
	new stringTextLabel[MAX_PLAYER_NAME + 6];
	// loop in the players
	foreach(new playerid : Player) {
	    // check if player is admin
	    if (IsPlayerAdminDuty(playerid)) {
	        // add in the array
	        adminsIndexCount[adminsLoggedCount] = playerid;
	        adminsLoggedCount ++;
	    }
	}
	// Show text labels to admins
	foreach(new playerid : Player) {
	    // check if player logged
		if (PlayerData[playerid][dLogged]) {
		    // destroy a 3d label text
		    if (PlayerData[playerid][dPlayerText3D] != Text3D:0)
				DestroyDynamic3DTextLabel(PlayerData[playerid][dPlayerText3D]);
			// create a new 3d text label
			format(stringTextLabel, sizeof stringTextLabel, "%s(%d)", getNome(playerid), playerid);
			PlayerData[playerid][dPlayerText3D] =
                CreateDynamic3DTextLabelEx(stringTextLabel, 0x00E6CBFA, 0.0, 0.0, 0.23, 295.0, .attachedplayer = playerid, .streamdistance = 295.0, .players = adminsIndexCount, .maxplayers = adminsLoggedCount);
		}
	}
	// update streamer to admins
	for (new index; index < adminsLoggedCount; index++) {
	    Streamer_Update(adminsIndexCount[index], STREAMER_TYPE_3D_TEXT_LABEL);
	}
	// end
}
