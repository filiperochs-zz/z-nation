
enum {
	E_SPAWN_SF,
	E_SPAWN_LV,
	E_SPAWN_COUNTRY,
	E_SPAWN_LS,
	E_SPAWN_BASE,
}

stock initPlayerSpawn(playerid) {

    hideLoginMenu(playerid, false);

    removePlayerWeapons(playerid);

	// Resetar o inventário
	resetInventory(playerid);

	// resetar infos
 	PlayerData[playerid][dKills] = 0;
 	PlayerData[playerid][dSangramento] = 0.0;
 	PlayerData[playerid][dVirus] = 0.0;
 	PlayerData[playerid][dRadiacao] = 0.0;

 	// Mascara de gás
 	PlayerData[playerid][dGasMask] = false;

	// Lanterna
	PlayerData[playerid][dLanterna] = false;

	SetPlayerHealth(playerid, 100.0);
	
	// Reset armor/helmet
	RemovePlayerHelmet(playerid);
	RemovePlayerArmor(playerid);
	
	PlayerData[playerid][dCuffed] = false;
	PlayerData[playerid][dVida] = 60.0;
	PlayerData[playerid][dFome] = 50.0;
	PlayerData[playerid][dSede] = 50.0;

	if (IsPlayerPremium(playerid))
	{
	    PlayerData[playerid][dMochila] = 2;
		PlayerData[playerid][dVida] = 100.0;
		PlayerData[playerid][dFome] = 100.0;
		PlayerData[playerid][dSede] = 100.0;
		givePlayerItem(playerid, ITEM_TYPE_ADRENALINA,-1026,  1, "Adrenalina");
	} else {
	    PlayerData[playerid][dMochila] = 1;
		PlayerData[playerid][dVida] = 60.0;
		PlayerData[playerid][dFome] = 50.0;
		PlayerData[playerid][dSede] = 50.0;
	}

	givePlayerItem(playerid, ITEM_TYPE_COCA, 	 1668,  1, "Garrafa dagua");
	givePlayerItem(playerid, ITEM_TYPE_BANDAGE,  11747, 1, "Bandagem");
	givePlayerItem(playerid, ITEM_TYPE_RADIO,    2966,  1, "Radio");
	givePlayerItem(playerid, ITEM_TYPE_WEAPON,   8,  	1, "Facao", 		.health = 10.0);
	givePlayerItem(playerid, ITEM_TYPE_WEAPON,   5,  	1, "Marreta",  		.health = 10.0);

	// Resetar tempo vivo
	PlayerData[playerid][dTempoVivo] = 0;

	// Doença
	PlayerData[playerid][dDoenca] = 0;

	// Spawnar o player
	for(new text; text < sizeof spawnSleepBag; text++)
	{
	    TextDrawShowForPlayer(playerid, spawnSleepBag[text]);
	}
	SelectTextDraw(playerid, 0x666666FF);
	
	SetPVarInt(playerid, "selectSkin", 1);
	
	return 1;
}

stock definePlayerSpawn(playerid, spawntype)
{
	new
	    Float:x = random(3000) - random(3000),
	    Float:y = random(3000) - random(3000),
	    Float:z = 1000.0;

	switch (spawntype)
	{
		case E_SPAWN_SF:
		{
		    x = -2151.6157 + frandom(400.0) - frandom(400.0);
		    y = 210.5628   + frandom(400.0) - frandom(400.0);
		    z = 500.0;
		}
		case E_SPAWN_LV:
		{
		    x = 1994.8849  + frandom(400.0) - frandom(400.0) ;
		    y = 1274.6910  + frandom(400.0) - frandom(400.0) ;
		    z = 500.0;
		}
		case E_SPAWN_COUNTRY:
		{
		    x = -1574.1030  + frandom(400.0) - frandom(400.0) ;
		    y = -2171.3499  + frandom(400.0) - frandom(400.0) ;
		    z = 500.0;
		}
		case E_SPAWN_LS:
		{
		    x = 1152.5310  + frandom(400.0) - frandom(400.0) ;
		    y = -1403.0725 + frandom(400.0) - frandom(400.0) ;
		    z = 500.0;
		}
		case E_SPAWN_BASE:
		{
		    new index = getPlayerBaseSpawn(playerid, x, y, z);
		    
		    if (!index)
		    {
		        return 0;
		    }
		    SetPVarInt(playerid, "spawnBase", 1);
  		}
	}
	
	// Setar status para vivo
	PlayerData[playerid][dDead] = false;
	
	SetPVarInt(playerid, "loadingPlayer", 1);
	
	DeletePVar(playerid, "selectSkin");

	CancelSelectTextDraw(playerid);
	
	for(new text; text < sizeof spawnSleepBag; text++)
	{
	    TextDrawHideForPlayer(playerid, spawnSleepBag[text]);
	}
	
	setPlayerSpawnInfo(playerid, 0, 0, PlayerData[playerid][dVida], x, y, z, random(360));
	
	processSpawn(playerid, true);
	
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "selectSkin")) {

		if (clickedid == Text:INVALID_TEXT_DRAW)
		{
		    SelectTextDraw(playerid, 0x666666FF);
		}
		else if (clickedid == spawnSleepBag[1])
		{
		    definePlayerSpawn(playerid, E_SPAWN_BASE);
		}
		else if (clickedid == spawnSleepBag[3])
		{
		    definePlayerSpawn(playerid, E_SPAWN_SF);
		}
		else if (clickedid == spawnSleepBag[4])
		{
		    definePlayerSpawn(playerid, E_SPAWN_LV);
		}
		else if (clickedid == spawnSleepBag[5])
		{
		    definePlayerSpawn(playerid, E_SPAWN_COUNTRY);
		}
		else if (clickedid == spawnSleepBag[6])
		{
		    definePlayerSpawn(playerid, E_SPAWN_LS);
		}
	}
 	#if defined ssOnPlayerClickTextDraw
  		return ssOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw ssOnPlayerClickTextDraw
#if defined ssOnPlayerClickTextDraw
	forward ssOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

