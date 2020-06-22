
new PlayerText:TextPlayerDialog[5];

stock ShowPlayerDialogTextdraw(playerid, dialogid, inputtext[], buttons[] = "SIM                NAO") {
	// update textdraws
	PlayerTextDrawSetString(playerid, TextPlayerDialog[1], inputtext);
	PlayerTextDrawSetString(playerid, TextPlayerDialog[4], buttons);
	// show dialogs
	for(new index; index < sizeof TextPlayerDialog; index++) {
	    PlayerTextDrawShow(playerid, TextPlayerDialog[index]);
	}
	// save pvars
	SetPVarInt(playerid, "p_InDialogText", 1);
	SetPVarInt(playerid, "p_DialogTextId", dialogid);
	// select color
	SelectTextDraw(playerid, 0xBBBBBB80);
	
	return 1;
}

stock HidePlayerDialogTextdraw(playerid) {
	// check if player is view dialog
	if (!GetPVarInt(playerid, "p_InDialogText"))
	    return 0;
	// hide dialogs
	for(new index; index < sizeof TextPlayerDialog; index++) {
	    PlayerTextDrawHide(playerid, TextPlayerDialog[index]);
	}
	// save pvars
	DeletePVar(playerid, "p_InDialogText");
	//DeletePVar(playerid, "p_DialogTextId");
	
	if (GetPVarInt(playerid, "p_vshop"))
	    SelectTextDraw(playerid, 0xFFFFFFFF);
	    
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (GetPVarInt(playerid, "p_InDialogText")) {
		// check if response is 1
		if (playertextid == TextPlayerDialog[2]) {
		    HidePlayerDialogTextdraw(playerid);
		    #if defined OnTextDialogResponse
		        OnTextDialogResponse(playerid, GetPVarInt(playerid, "p_DialogTextId"), 1);
			#endif
		}
		// check if response id 0
		if (playertextid == TextPlayerDialog[3]) {
		    HidePlayerDialogTextdraw(playerid);
		    #if defined OnTextDialogResponse
		        OnTextDialogResponse(playerid, GetPVarInt(playerid, "p_DialogTextId"), 0);
			#endif
		}
		return 1;
	}
 	#if defined dOPCPTD
  		return dOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw dOPCPTD
#if defined dOPCPTD
	forward dOPCPTD(playerid, PlayerText:playertextid);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "p_InDialogText")) {
	    if (clickedid == Text:INVALID_TEXT_DRAW) {
	        HidePlayerDialogTextdraw(playerid);
		    #if defined OnTextDialogResponse
		        OnTextDialogResponse(playerid, GetPVarInt(playerid, "p_DialogTextId"), 0);
			#endif
	    }
		return 1;
	}

 	#if defined diOnPlayerClickTextDraw
  		return diOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw diOnPlayerClickTextDraw
#if defined diOnPlayerClickTextDraw
	forward diOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

stock CreatePlayerTextdrawsDialog(playerid) {
	TextPlayerDialog[0] = CreatePlayerTextDraw(playerid,235.000000, 200.000000, "usebox");
	PlayerTextDrawBackgroundColor(playerid,TextPlayerDialog[0], 0);
	PlayerTextDrawFont(playerid,TextPlayerDialog[0], 1);
	PlayerTextDrawLetterSize(playerid,TextPlayerDialog[0], 0.500000, 7.999999);
	PlayerTextDrawColor(playerid,TextPlayerDialog[0], 0);
	PlayerTextDrawSetOutline(playerid,TextPlayerDialog[0], 0);
	PlayerTextDrawSetProportional(playerid,TextPlayerDialog[0], 1);
	PlayerTextDrawSetShadow(playerid,TextPlayerDialog[0], 1);
	PlayerTextDrawUseBox(playerid,TextPlayerDialog[0], 1);
	PlayerTextDrawBoxColor(playerid,TextPlayerDialog[0], 185273343);
	PlayerTextDrawTextSize(playerid,TextPlayerDialog[0], 397.000000, 20.000000);
	PlayerTextDrawSetSelectable(playerid,TextPlayerDialog[0], 0);

	TextPlayerDialog[1] = CreatePlayerTextDraw(playerid,316.000000, 210.000000, "dialog descricao");
	PlayerTextDrawAlignment(playerid,TextPlayerDialog[1], 2);
	PlayerTextDrawBackgroundColor(playerid,TextPlayerDialog[1], 0);
	PlayerTextDrawFont(playerid,TextPlayerDialog[1], 1);
	PlayerTextDrawLetterSize(playerid,TextPlayerDialog[1], 0.179999, 1.000000);
	PlayerTextDrawColor(playerid,TextPlayerDialog[1], -76);
	PlayerTextDrawSetOutline(playerid,TextPlayerDialog[1], 0);
	PlayerTextDrawSetProportional(playerid,TextPlayerDialog[1], 1);
	PlayerTextDrawSetShadow(playerid,TextPlayerDialog[1], 1);
	PlayerTextDrawUseBox(playerid,TextPlayerDialog[1], 1);
	PlayerTextDrawBoxColor(playerid,TextPlayerDialog[1], 0);
	PlayerTextDrawTextSize(playerid,TextPlayerDialog[1], 496.000000, 144.000000);
	PlayerTextDrawSetSelectable(playerid,TextPlayerDialog[1], 0);

	TextPlayerDialog[2] = CreatePlayerTextDraw(playerid,243.000000, 246.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,TextPlayerDialog[2], 255);
	PlayerTextDrawFont(playerid,TextPlayerDialog[2], 4);
	PlayerTextDrawLetterSize(playerid,TextPlayerDialog[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,TextPlayerDialog[2], 6579455);
	PlayerTextDrawSetOutline(playerid,TextPlayerDialog[2], 0);
	PlayerTextDrawSetProportional(playerid,TextPlayerDialog[2], 1);
	PlayerTextDrawSetShadow(playerid,TextPlayerDialog[2], 1);
	PlayerTextDrawUseBox(playerid,TextPlayerDialog[2], 1);
	PlayerTextDrawBoxColor(playerid,TextPlayerDialog[2], 255);
	PlayerTextDrawTextSize(playerid,TextPlayerDialog[2], 70.000000, 20.000000);
	PlayerTextDrawSetSelectable(playerid,TextPlayerDialog[2], 1);

	TextPlayerDialog[3] = CreatePlayerTextDraw(playerid,318.000000, 246.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,TextPlayerDialog[3], 255);
	PlayerTextDrawFont(playerid,TextPlayerDialog[3], 4);
	PlayerTextDrawLetterSize(playerid,TextPlayerDialog[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,TextPlayerDialog[3], 336860415);
	PlayerTextDrawSetOutline(playerid,TextPlayerDialog[3], 0);
	PlayerTextDrawSetProportional(playerid,TextPlayerDialog[3], 1);
	PlayerTextDrawSetShadow(playerid,TextPlayerDialog[3], 1);
	PlayerTextDrawUseBox(playerid,TextPlayerDialog[3], 1);
	PlayerTextDrawBoxColor(playerid,TextPlayerDialog[3], 255);
	PlayerTextDrawTextSize(playerid,TextPlayerDialog[3], 70.000000, 20.000000);
	PlayerTextDrawSetSelectable(playerid,TextPlayerDialog[3], 1);

	TextPlayerDialog[4] = CreatePlayerTextDraw(playerid,270.000000, 251.000000, "SIM                NAO");
	PlayerTextDrawBackgroundColor(playerid,TextPlayerDialog[4], 0);
	PlayerTextDrawFont(playerid,TextPlayerDialog[4], 1);
	PlayerTextDrawLetterSize(playerid,TextPlayerDialog[4], 0.239999, 0.999998);
	PlayerTextDrawColor(playerid,TextPlayerDialog[4], -106);
	PlayerTextDrawSetOutline(playerid,TextPlayerDialog[4], 0);
	PlayerTextDrawSetProportional(playerid,TextPlayerDialog[4], 1);
	PlayerTextDrawSetShadow(playerid,TextPlayerDialog[4], 1);
	PlayerTextDrawSetSelectable(playerid,TextPlayerDialog[4], 0);
}

forward OnTextDialogResponse(playerid, dialogid, response);
