
#define GetPlayerRankId(%0) 	 GetPVarInt(%0, "p_rankid")
#define SetPlayerRankId(%0,%1)   SetPVarInt(%0, "p_rankid", %1)
#define MAX_RANK_LISTED          (15)

enum e_RankEnum {
	e_rank_key[35],
	e_rank_name[35],
	e_rank_discription[128],
}

stock const g_rankServerInfo[][e_RankEnum] = {
	// Maior nivel
	{
		"level", 
		"Maior nivel", 
		"Lista dos jogadores com maior nivel"
	},
	// Maior XP
	{
		"points", 
		"Maior exp", 
		"Lista dos jogadores com maior exp"
	},
	// Mais kills
	{
		"totalkills",
		"Maiores matadores",
		"Lista dos jogadores com mais kills"
	},
	// Mais mortes
	{
		"deaths",
		"Mais mortes",
		"Lista dos jogadores que mais morreram"
	},
	// Maior kills zombies
	{
		"zkills",
		"Zombie kills",
		"Lista dos jogadores que mataram mais zombies"
	},
	// Mais disputaram Battle royale
	{
		"br_times",
		"Battle royale",
		"Os que mais disputaram o battle royale"
	},
	// Mais venceram Battle royale
	{
		"br_wins",
		"Battle royale vitorias",
		"Os que mais venceram o battle royale"
	},
	// Mais mataram no Battle royale
	{
		"br_kills",
		"Battle royale kills",
		"Os que mais mataram no battle royale"
	}
};

stock ShowPlayerRank(playerid)
{
	if (GetPVarInt(playerid, "viewrank"))
	    return 0;
	    
	for(new p_text; p_text < sizeof textServerRanks; p_text++)
	{
	    TextDrawShowForPlayer(playerid, textServerRanks[p_text]);
	    
	    if (p_text < 5)
	    {
	        PlayerTextDrawShow(playerid, textPlayerRanks[playerid][p_text]);
	    }
	}
	    
//	SelectTextDraw(playerid, 0xFFFFFFFF);
	    
    UpdateRankForPlayer(playerid);
	    
	SetPVarInt(playerid, "viewrank", 1);
	
	// show status
	stringGlobal[0] = EOS;
	
	PlayerTextDrawSetString(playerid, PlayerTextDrawStatus[0],
		"Level~n~~n~\
		Kills~n~~n~\
		Mortes~n~~n~\
		Dinheiro~n~~n~\
		Z Points~n~~n~\
		Zombie kills~n~~n~\
		Battle royales~n~~n~\
		Battle royale wins~n~~n~\
		Battle royale kills~n~~n~\
		Grupo");
	
	format(stringGlobal, 385,
		"%d~n~~n~\
		%d~n~~n~\
		%d~n~~n~\
		$%d~n~~n~\
		%d~n~~n~\
		%d~n~~n~\
		%d~n~~n~\
		%d~n~~n~\
		%d~n~~n~\
		%s~n~", PlayerData[playerid][dLevel], PlayerData[playerid][dTotalKills],
			 PlayerData[playerid][dDeaths], PlayerData[playerid][dMoney],
			 PlayerData[playerid][dCoins], PlayerData[playerid][dZombieKills],
			 PlayerData[playerid][dTimesBattleRoyale], PlayerData[playerid][dWinsBattleRoyale],
			 PlayerData[playerid][dKillsBattleRoyale], getPlayerServerGroupName(playerid));
	
	PlayerTextDrawSetString(playerid, PlayerTextDrawStatus[1], stringGlobal);
	PlayerTextDrawSetString(playerid, PlayerTextDrawStatus[2], getNome(playerid));
	
	for(new index; index < sizeof  PlayerTextDrawStatus; index++)
	    PlayerTextDrawShow(playerid,  PlayerTextDrawStatus[index]);
	    
    //TextDrawHideForPlayer(playerid, textChangeDSkin);
	
	return 1;
}

stock HidePlayerRank(playerid)
{
	if (!GetPVarInt(playerid, "viewrank"))
	    return 0;

	for(new p_text; p_text < sizeof textServerRanks; p_text++)
	{
	    TextDrawHideForPlayer(playerid, textServerRanks[p_text]);

	    if (p_text < 5)
	    {
	        PlayerTextDrawHide(playerid, textPlayerRanks[playerid][p_text]);
	    }
	}

	for(new index; index < sizeof  PlayerTextDrawStatus; index++)
	    PlayerTextDrawHide(playerid,  PlayerTextDrawStatus[index]);

	DeletePVar(playerid, "viewrank");
	
	//TextDrawShowForPlayer(playerid, textChangeDSkin);
	
//	showLoginMenu(playerid, .select = true);
	return 1;
}

stock UpdateRankForPlayer(playerid)
{
	new s_position[MAX_RANK_LISTED * 7];
	new s_names[MAX_RANK_LISTED * 27];
	new s_number[MAX_RANK_LISTED * 11];
	new s_string[35];
	new s_query[100];
	new rankid = GetPlayerRankId(playerid);
	// Data Base
	new DBResult:returnResult, numrows;

	format(s_query, sizeof s_query, "SELECT * FROM `accounts` ORDER BY `%s` DESC LIMIT %d", g_rankServerInfo[rankid][e_rank_key], MAX_RANK_LISTED);

	returnResult = db_query(serverDB, s_query);

	numrows = db_num_rows(returnResult);
	
	if (numrows > 0)
	{
	    for(new p_rank; p_rank < numrows; p_rank++)
	    {
	        // Posição
			format(s_string, sizeof (s_string), "#%d~n~", p_rank + 1);
	        strcat(s_position, s_string);
	    
	        // Nome
	        db_get_field_assoc(returnResult, "nome", s_string, sizeof (s_string));
	        strcat(s_names, s_string);
	        strcat(s_names, "~n~");
	        
	        // Rank
			format(s_string, sizeof (s_string), "%d~n~", db_get_field_assoc_int(returnResult, g_rankServerInfo[rankid][e_rank_key]));
	        strcat(s_number, s_string);
	        
	        db_next_row(returnResult);
	    }
	}
	
	PlayerTextDrawSetString(playerid, textPlayerRanks[playerid][1], s_position);
	PlayerTextDrawSetString(playerid, textPlayerRanks[playerid][2], s_names);
	PlayerTextDrawSetString(playerid, textPlayerRanks[playerid][3], s_number);
	PlayerTextDrawSetString(playerid, textPlayerRanks[playerid][0], g_rankServerInfo[rankid][e_rank_name]);
	PlayerTextDrawSetString(playerid, textPlayerRanks[playerid][4], g_rankServerInfo[rankid][e_rank_discription]);

	db_free_result(returnResult);
}


public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "viewrank"))
	{
	    if (clickedid == Text:INVALID_TEXT_DRAW)
	    {
	        SelectTextDraw(playerid, 0xFFFFFF10);
	    }
	    else if (clickedid == textServerRanks[3])
	    {
	        SetPlayerRankId(playerid, GetPlayerRankId(playerid) - 1);
	        
	        if (GetPlayerRankId(playerid) < 0)
	        {
	            SetPlayerRankId(playerid, sizeof (g_rankServerInfo) - 1);
	        }
	        UpdateRankForPlayer(playerid);
         	// Efeito de som
          	Audio_Play(playerid, 25);
	    }
	    else if (clickedid == textServerRanks[4])
	    {
	        SetPlayerRankId(playerid, GetPlayerRankId(playerid) + 1);

	        if (GetPlayerRankId(playerid) > sizeof (g_rankServerInfo) - 1)
	        {
	            SetPlayerRankId(playerid, 0);
	        }
	        UpdateRankForPlayer(playerid);
         	// Efeito de som
          	Audio_Play(playerid, 25);
	    }
	    else if (clickedid == textServerRanks[5] || clickedid == Text:INVALID_TEXT_DRAW)
	    {
	        HidePlayerRank(playerid);
	    }
	    return 1;
	}
 	#if defined rOnPlayerClickTextDraw
  		return rOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw rOnPlayerClickTextDraw
#if defined rOnPlayerClickTextDraw
	forward rOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif




