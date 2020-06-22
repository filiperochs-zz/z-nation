
static PlayerText:playerRewardText[3];
static PlayerText:rewardTime;

stock ShowPlayerReward(playerid, textname[], discription[] = "_")
{
	// update textdraws
	PlayerTextDrawSetString(playerid, playerRewardText[2], textname);
	PlayerTextDrawSetString(playerid, rewardTime, discription);
	// show dialogs
	for(new index; index < sizeof playerRewardText; index++)
	{
	    PlayerTextDrawShow(playerid, playerRewardText[index]);
	}
	PlayerTextDrawShow(playerid, rewardTime);
	// save pvars
	SetPVarInt(playerid, "p_inreward", 1);
	// select color
	SelectTextDraw(playerid, 0xFFFFFFFF);
	
	return 1;
}

stock HidePlayerReward(playerid)
{
	// check if player is view dialog
	if (!GetPVarInt(playerid, "p_inreward"))
	    return 0;
	    
	// hide dialogs
	for(new index; index < sizeof playerRewardText; index++)
	{
	    PlayerTextDrawHide(playerid, playerRewardText[index]);
	}
	PlayerTextDrawHide(playerid, rewardTime);
	// save pvars
	DeletePVar(playerid, "p_inreward");
	
 	if (PlayerData[playerid][dServerState] != SERVER_STATE_MENU)
	    CancelSelectTextDraw(playerid);
	    
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (GetPVarInt(playerid, "p_inreward"))
	{
		if (playertextid == playerRewardText[1])
		{
		    if (!SHOP_CheckNewItems(playerid))
		    {
		    	HidePlayerReward(playerid);
			}
		}
		return 1;
	}
 	#if defined reOPCPTD
  		return reOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw reOPCPTD
#if defined reOPCPTD
	forward reOPCPTD(playerid, PlayerText:playertextid);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "p_inreward"))
	{
	    if (clickedid == Text:INVALID_TEXT_DRAW)
		{
		    if (!SHOP_CheckNewItems(playerid))
		    {
		    	HidePlayerReward(playerid);
		    	
	 	        if (PlayerData[playerid][dServerState] == SERVER_STATE_MENU)
		        {
		            SelectTextDraw(playerid, 0xFFFFFFFF);
		        }
			}
	    }
		return 1;
	}

 	#if defined reOnPlayerClickTextDraw
  		return reOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw reOnPlayerClickTextDraw
#if defined reOnPlayerClickTextDraw
	forward reOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

stock CreatePlayerRewardTexts(playerid)
{
	playerRewardText[0] = CreatePlayerTextDraw(playerid,226.000000, 126.000000, "mdl-1002:reward");
	PlayerTextDrawBackgroundColor(playerid,playerRewardText[0], 255);
	PlayerTextDrawFont(playerid,playerRewardText[0], 4);
	PlayerTextDrawLetterSize(playerid,playerRewardText[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerRewardText[0], -1);
	PlayerTextDrawSetOutline(playerid,playerRewardText[0], 0);
	PlayerTextDrawSetProportional(playerid,playerRewardText[0], 1);
	PlayerTextDrawSetShadow(playerid,playerRewardText[0], 1);
	PlayerTextDrawUseBox(playerid,playerRewardText[0], 1);
	PlayerTextDrawBoxColor(playerid,playerRewardText[0], 255);
	PlayerTextDrawTextSize(playerid,playerRewardText[0], 182.000000, 230.000000);
	PlayerTextDrawSetSelectable(playerid,playerRewardText[0], 0);

	rewardTime = CreatePlayerTextDraw(playerid,316.000000, 297.000000, "0_day(s)_00:00:00");
	PlayerTextDrawAlignment(playerid,rewardTime, 2);
	PlayerTextDrawBackgroundColor(playerid,rewardTime, 0);
	PlayerTextDrawFont(playerid,rewardTime, 1);
	PlayerTextDrawLetterSize(playerid,rewardTime, 0.190000, 1.000000);
	PlayerTextDrawColor(playerid,rewardTime, -1);
	PlayerTextDrawSetOutline(playerid,rewardTime, 0);
	PlayerTextDrawSetProportional(playerid,rewardTime, 1);
	PlayerTextDrawSetShadow(playerid,rewardTime, 1);
	PlayerTextDrawUseBox(playerid,rewardTime, 1);
	PlayerTextDrawBoxColor(playerid,rewardTime, 336860385);
	PlayerTextDrawTextSize(playerid,rewardTime, 390.000000, -82.000000);
	PlayerTextDrawSetSelectable(playerid,rewardTime, 0);

	playerRewardText[1] = CreatePlayerTextDraw(playerid,275.000000, 313.000000, "mdl-1002:buttonok");
	PlayerTextDrawBackgroundColor(playerid,playerRewardText[1], 255);
	PlayerTextDrawFont(playerid,playerRewardText[1], 4);
	PlayerTextDrawLetterSize(playerid,playerRewardText[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerRewardText[1], -76);
	PlayerTextDrawSetOutline(playerid,playerRewardText[1], 0);
	PlayerTextDrawSetProportional(playerid,playerRewardText[1], 1);
	PlayerTextDrawSetShadow(playerid,playerRewardText[1], 1);
	PlayerTextDrawUseBox(playerid,playerRewardText[1], 1);
	PlayerTextDrawBoxColor(playerid,playerRewardText[1], 255);
	PlayerTextDrawTextSize(playerid,playerRewardText[1], 82.000000, 26.000000);
	PlayerTextDrawSetSelectable(playerid,playerRewardText[1], 1);

	playerRewardText[2] = CreatePlayerTextDraw(playerid,267.000000, 170.000000, "mdl-1003:0000");
	PlayerTextDrawBackgroundColor(playerid,playerRewardText[2], 255);
	PlayerTextDrawFont(playerid,playerRewardText[2], 4);
	PlayerTextDrawLetterSize(playerid,playerRewardText[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerRewardText[2], -1);
	PlayerTextDrawSetOutline(playerid,playerRewardText[2], 0);
	PlayerTextDrawSetProportional(playerid,playerRewardText[2], 1);
	PlayerTextDrawSetShadow(playerid,playerRewardText[2], 1);
	PlayerTextDrawUseBox(playerid,playerRewardText[2], 1);
	PlayerTextDrawBoxColor(playerid,playerRewardText[2], 255);
	PlayerTextDrawTextSize(playerid,playerRewardText[2], 99.000000, 123.000000);
	PlayerTextDrawSetSelectable(playerid,playerRewardText[2], 0);
}
