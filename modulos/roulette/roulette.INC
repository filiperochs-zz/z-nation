
stock showPlayerRoulette(playerid)
{
	if ((IsPlayerInInventory(playerid) || PlayerData[playerid][dDead]) && !IsPlayerInBattleRoyale(playerid))
	    return 0;

	if (GetPVarInt(playerid, "inRoulette"))
	    return 0;

	for(new text; text < sizeof (TextDrawEmotes); text++)
	{
	    TextDrawShowForPlayer(playerid, TextDrawEmotes[text]);
	}
	SelectTextDraw(playerid, 0xFFFFFFCC);
	SetPVarInt(playerid, "inRoulette", 1);
	
	return 1;
}

stock hidePlayerRoulette(playerid)
{
	if (!GetPVarInt(playerid, "inRoulette"))
	    return 0;
	    
	for(new text; text < sizeof (TextDrawEmotes); text++)
	{
	    TextDrawHideForPlayer(playerid, TextDrawEmotes[text]);
	}
	CancelSelectTextDraw(playerid);
	DeletePVar(playerid, "inRoulette");
	
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "inRoulette") && !IsPlayerInProgress(playerid))
	{
		if (clickedid == Text:INVALID_TEXT_DRAW)
		{
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// HANDSUP
		else if (clickedid == TextDrawEmotes[4])
		{
		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// DROP ALL
		else if (clickedid == TextDrawEmotes[2])
		{
		    DropAllPlayerThings(playerid);

		    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_2Idle", 4.1, 0, 1, 1, 0, 0);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// SENTAR
		else if (clickedid == TextDrawEmotes[3])
		{
		    ApplyAnimation(playerid,"SUNBATHE","ParkSit_M_IdleC",4.1,0,1,1,1,1);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// ASSOBIAR
		else if (clickedid == TextDrawEmotes[6])
		{
		    cmd_assobiar(playerid);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// FECHAR
		else if (clickedid == TextDrawEmotes[9])
		{
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// SALUTE
		else if (clickedid == TextDrawEmotes[5])
		{
		    ApplyAnimation(playerid,"GHANDS","gsign5LH", 4.1, 0, 1, 1, 0, 0);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// CHORAR
		else if (clickedid == TextDrawEmotes[7])
		{
		    ApplyAnimation(playerid,"GRAVEYARD","mrnF_loop", 4.1, 0, 1, 1, 0, 0);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// CRAFT
		else if (clickedid == TextDrawEmotes[1])
		{
		    ShowPlayerBaseCreationMenu(playerid);
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
		// DANÇAR
		else if (clickedid == TextDrawEmotes[8])
		{
		    new rand = random(5) + 4;
		    
		    switch (rand)
		    {
		        case 4: ApplyAnimation(playerid,"DANCING","DAN_Down_A",4.1,1,1,1,1,1);
		        case 5: ApplyAnimation(playerid,"DANCING","DAN_Left_A",4.1,1,1,1,1,1);
		        case 6: ApplyAnimation(playerid,"DANCING","DAN_Loop_A",4.1,1,1,1,1,1);
		        case 7: ApplyAnimation(playerid,"DANCING","DAN_Right_A",4.1,1,1,1,1,1);
		        case 8: ApplyAnimation(playerid,"DANCING","DAN_Up_A",4.1,1,1,1,1,1);
		        case 9: ApplyAnimation(playerid,"DANCING","dnce_M_a",4.1,1,1,1,1,1);
		    }
		    
		    // Fechar
		    hidePlayerRoulette(playerid);
		}
	}
 	#if defined roOnPlayerClickTextDraw
  		return roOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw roOnPlayerClickTextDraw
#if defined roOnPlayerClickTextDraw
	forward roOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

