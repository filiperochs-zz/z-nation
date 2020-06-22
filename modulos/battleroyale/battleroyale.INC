
#define MIN_START_BATTLEROYALE   (3) // Mínimo de players para dar start no battle royale
#define MAX_BATTLEROYALE_WINNERS (1)
#define TIME_START_BATTLEROYALE  (120)

#include "../include/turngz.inc"

enum battleRoyaleEnum {

	battle_started,
	battle_announced,
	battle_kills,
	battle_time,
	battle_steptimer,
	battle_airdrop,
	battle_step,
	battle_timer,
	battle_gz,
	battle_safe_gz,
	battle_timerann,
	battle_timeann,
	battle_timer_itens,
	battle_item_index,
	battle_step_gas,
	battle_airplane,
	battle_attachcam,
	// GangZones
	Float:battle_toxic_size,
	Float:battle_toxic_gosize,
	Float:battle_toxic_x,
	Float:battle_toxic_y,
	Float:battle_toxic_gox,
	Float:battle_toxic_goy,
}

new BattleRoyale[battleRoyaleEnum];

stock const Float:LobbySpawns[][4] = {
	{2660.0110,3139.2212,05.9139,181.1412},
	{2660.4800,3083.2339,05.8405,000.0329},
	{2638.2373,3091.1772,10.6231,269.7921},
	{2660.1594,3174.8652,05.9139,179.5513}
};

stock const Float:BattleSpawns[][3] = {
{238.6711,-131.8297,1.5781},
{686.3788,-538.0560,16.1722},
{1290.6495,267.1218,19.5547},
{2325.1921,22.8257,26.4766},
{2212.8286,687.4065,14.9329},
{-2706.6680,-19.8085,4.1875}
};

new
	firstSpawnItens = 1;

stock Float:groupsSpawnBattleRoyale[MAX_GROUPS][3];

callback resetBattleRoyale() {

	BattleRoyale[battle_started]   = 0;
	BattleRoyale[battle_kills] 	   = 0;
	BattleRoyale[battle_time] 	   = 0;
	BattleRoyale[battle_step] 	   = 0;
	BattleRoyale[battle_announced] = 0;
	BattleRoyale[battle_step_gas]  = 0;
	
	StartBattleRoyaleSpawnItens();
	
	// Kill Timer
	KillTimer(BattleRoyale[battle_timer]);
	
	// Destruir round gang zone
	DestroyRoundGangZone(BattleRoyale[battle_gz]);
	DestroyRoundGangZone(BattleRoyale[battle_safe_gz]);
}

stock DestroyBattleRoyaleThings() {
	// destruir loot battle royale
	destroyBattleRoyaleItens();

	// Destruir veiculos battle royale
	destroyBattleRoyaleVehicles();
	
	// destroy airplane
	DestroyObject(BattleRoyale[battle_airplane]);
	DestroyObject(BattleRoyale[battle_attachcam]);
	BattleRoyale[battle_airplane] = -1;
	BattleRoyale[battle_attachcam]= -1;
}

CMD:announce558(playerid) {

    announceBattleRoyale();
	return 1;
}

callback announceBattleRoyale() {
	BattleRoyale[battle_announced] = 1;
	
//	BattleRoyale[battle_timeann] = gettime() + 30;
	BattleRoyale[battle_timeann] = gettime() + TIME_START_BATTLEROYALE;
	
	BattleRoyale[battle_timerann] = SetTimer("coolDownStartBattle", 1000, true);
	
	Log::("battleroyale", "BATTLE ROYALE\t|the battle has been announced");
}

stock StartBattleRoyaleSpawnItens() {
	KillTimer(BattleRoyale[battle_timer_itens]);
	BattleRoyale[battle_item_index]  = MAX_DROP_ITENS - 1;
	
	if (firstSpawnItens) {
	
		for(new idx, item = MAX_DROP_ITENS - 1; item > MAX_DROP_ITENS - sizeof BattleRoyale_Itens; item--, idx++) {
			new rdon = GetItemRandom(LOOT_TYPE_BATTLEROYALE);
		    createDroppedItem(BattleRoyale_Itens[idx][0], BattleRoyale_Itens[idx][1], BattleRoyale_Itens[idx][2],
			ItensArray[rdon][i_nome], ItensArray[rdon][i_type], ItensArray[rdon][i_model], random(ItensArray[rdon][i_maxrandom]) + 1, .raycast = false, .world = 5001, .randomize = false, .rdon = item);
  //          printf("spawned: %d/%d", idx, sizeof BattleRoyale_Itens);
		}
	
	    firstSpawnItens = 0;
	} else {
		BattleRoyale[battle_timer_itens] = SetTimer("b_SpawnItem", 100, true);
	}
	
	Log::("battleroyale", "BATTLE ROYALE\t|the battle royale itens start spawn");
}

callback b_SpawnItem() {

	new item = MAX_DROP_ITENS - BattleRoyale[battle_item_index];
	
	if (item >= sizeof BattleRoyale_Itens) {
	    // kill a timer
	    KillTimer(BattleRoyale[battle_timer_itens]);
	    
	    Log::("battleroyale", "BATTLE ROYALE\t|all itens of battle royale spawned");
	    return 1;
	}
	// check if is valid
	if (!Iter_Contains(iterDrops, BattleRoyale[battle_item_index])) {
	    // drop item
		new rdon = GetItemRandom(LOOT_TYPE_BATTLEROYALE);
	    createDroppedItem(BattleRoyale_Itens[item][0], BattleRoyale_Itens[item][1], BattleRoyale_Itens[item][2],
		ItensArray[rdon][i_nome], ItensArray[rdon][i_type], ItensArray[rdon][i_model], random(ItensArray[rdon][i_maxrandom]) + 1, .raycast = false, .world = 5001, .randomize = false, .rdon = BattleRoyale[battle_item_index]);
  //      printf("spawned: %d/%d", item , sizeof BattleRoyale_Itens);
	}
    BattleRoyale[battle_item_index] --;
    
    return 1;
}

callback coolDownStartBattle()
{
	new time = BattleRoyale[battle_timeann] - gettime();

	if (time > 0)
	{
	    new string[128];
	    format(string, sizeof (string), "A PARTIDA VAI COMECAR EM~n~%d", time);
	    showTextBattleAnnounce(string);
	}
	else
	{
	    if (countPlayersInLobby() < MIN_START_BATTLEROYALE)
		{
		    SendServerMessage("Nao ha jogadores suficientes para iniciar o Battle Royale");
		    BattleRoyale[battle_announced] = 0;
		    
		    Log::("battleroyale", "BATTLE ROYALE\t|the battle not initialized because not sufficient players");
		}
		else
		{
		    createBattleRoyaleAirplane();
		
			foreach(new playerid : Player) {
			
			    if (PlayerData[playerid][dLobby]) {
			        hideInfoTextdraws(playerid);
			        showPlayerLoading(playerid);

			        SetPVarInt(playerid, "inAirplane", 1);
			        // time to automatic drop
			        SetPVarInt(playerid, "setAirPlaneTime", gettime() + 45);
			        // toggle spectating
					TogglePlayerSpectating(playerid, true);
					// attach camera
					AttachCameraToObject(playerid, BattleRoyale[battle_attachcam]);
					// set a random spawn (if bugg)
					SetPVarFloat(playerid, "playerSetSpawnX", frandom(3000) - frandom(3000));
					SetPVarFloat(playerid, "playerSetSpawnY", frandom(3000) - frandom(3000));
					SetPVarFloat(playerid, "playerSetSpawnZ", 400.0);
					SetPlayerWeather(playerid, 3);
					if (Audio_IsClientConnected(playerid))
					{
					    SetPVarInt(playerid, "airplaneSound", Audio_PlayStreamed(playerid, "https://alphard.sscdn.co/palcomp3/d/d/b/9/serverbps-airplane-7e0f2fbd.mp3?"));
					}
					else
					{
					    PlayAudioStreamForPlayer(playerid, "https://alphard.sscdn.co/palcomp3/d/d/b/9/serverbps-airplane-7e0f2fbd.mp3?");
					}
			    }
			}
			showTextBattleAnnounce("AGUARDE A BATALHA COMECAR...");
			SetTimer("startBattleRoyale", 3000, false);
		}
		KillTimer(BattleRoyale[battle_timerann]);
	}
}

stock createBattleRoyaleAirplane() {

	DestroyObject(BattleRoyale[battle_attachcam]);
	DestroyObject(BattleRoyale[battle_airplane]);

	new Float:fx = 0.0 + (random(5) - random(5));
	new Float:fy = 0.0 + (random(5) - random(5));

	new Float:ang = GetPointAngleToPoint(fx, fy, 0.0, 0.0);

	fx = fx + (4300.0 * floatsin(-ang, degrees));
	fy = fy + (4300.0 * floatcos(-ang, degrees));

	ang = GetPointAngleToPoint(fx, fy, 0.0, 0.0);

	BattleRoyale[battle_airplane] = CreateObject(1681, fx, fy, 400.0, 0.0, 0.0, GetPointAngleToPoint(fx, fy, 0.0, 0.0), 500.0);
	BattleRoyale[battle_attachcam] = CreateObject(19300, fx, fy, 400.0, 0.0, 0.0, 0.0);

	AttachObjectToObject(BattleRoyale[battle_attachcam], BattleRoyale[battle_airplane], -3.0, -5.0, 9.0, 0.0, 0.0, 0.0);

	new Float:tx = 0.0 + (6000.0 * floatsin(-ang, degrees));
	new Float:ty = 0.0 + (6000.0 * floatcos(-ang, degrees));

	MoveObject(BattleRoyale[battle_airplane], tx, ty, 370.0, 70.0);
}

callback startBattleRoyale() {

	BattleRoyale[battle_started]   	  = 1;
	BattleRoyale[battle_time] 	   	  = gettime();
	BattleRoyale[battle_airdrop]      = gettime() + 99999;
	BattleRoyale[battle_steptimer] 	  = gettime() + (115);
	BattleRoyale[battle_step] 	   	  = 0;
	BattleRoyale[battle_step_gas]  	  = 0;
	BattleRoyale[battle_toxic_size]   = 4000.0;
	BattleRoyale[battle_toxic_gosize] = 4000.0;
	BattleRoyale[battle_toxic_gox]    = 0.0000;
	BattleRoyale[battle_toxic_goy]    = 0.0000;
	BattleRoyale[battle_toxic_x]      = 0.0000;
	BattleRoyale[battle_toxic_y]      = 0.0000;
	// Gang zones
	BattleRoyale[battle_gz]           = -1;
	BattleRoyale[battle_safe_gz]      = -1;
	
	printf("Battle Royale iniciado!");
	// Timer
	BattleRoyale[battle_timer]     	  = SetTimer("updateBattleRoyale", 1500, true);
	// Criar os carros no mapa
	createBattleRoyaleVehicles();
	// Setar players no mapa
	//setPlayersBattleRoyale();
	foreach(new playerid : Player)
	{
	    if (PlayerData[playerid][dLobby])
	    {
			PlayerData[playerid][dLobby] 		= false;
			PlayerData[playerid][dBattleRoyale] = true;
	        hidePlayerLoading(playerid);
    		TextDrawShowForPlayer(playerid, boxDroppedItem1);
 			TextDrawShowForPlayer(playerid, boxDroppedItem2);
 			PlayerTextDrawSetString(playerid, textCameraItem[playerid], GetPlayerLanguageKey(playerid, "EJECT"));
 			PlayerTextDrawShow(playerid, textCameraItem[playerid]);
	    }
	}
	// Mensagem
    showTextBattleAnnounce("A BATALHA COMECOU, BOA SORTE A TODOS!");
    
    Log::("battleroyale", "BATTLE ROYALE\t|the battle royale has been initialized with %d players", countPlayersBattleRoyale());
}

stock setPlayersToAirplane() {

	foreach(new playerid : Player) {

	    if (PlayerData[playerid][dLobby]) {
	        SetPVarInt(playerid, "inAirplane", 1);
	        // time to automatic drop
	        SetPVarInt(playerid, "setAirPlaneTime", gettime() + 45);
	        // toggle spectating
			TogglePlayerSpectating(playerid, true);
			// attach camera
			AttachCameraToObject(playerid, BattleRoyale[battle_attachcam]);
			// set a random spawn (if bugg)
			SetPVarFloat(playerid, "playerSetSpawnX", frandom(3000) - frandom(3000));
			SetPVarFloat(playerid, "playerSetSpawnY", frandom(3000) - frandom(3000));
			SetPVarFloat(playerid, "playerSetSpawnZ", 400.0);
	    }
	}
}

stock SendBattleRoyaleInfo(info[]) {
	// loop in the players
	foreach(new playerid : Player) {
	    // check if player is in battle royale
 		if (IsPlayerInBattleRoyale(playerid)) {
 		    // show info textdraw
	       	showTextInfoDeath(playerid, info, .interval = 8000, .color = 0xFFFF55FA);
		}
    }
}

callback updateBattleRoyale() {

	// variaveis
	new string[95];

	// Avançar o gás tóxico
	if (BattleRoyale[battle_toxic_size] > BattleRoyale[battle_toxic_gosize]) {

		// Diminuir o tamanho
		new Float:velocity;
		
		if (BattleRoyale[battle_toxic_size] > 2500.0) {
		    velocity = 32.0;
		}
		else if (BattleRoyale[battle_toxic_size] > 1000.0) {
		    velocity = 26.5;
		}
		else if (BattleRoyale[battle_toxic_size] > 450.0) {
		    velocity = 19.0;
		} else {
		    velocity = 15.5;
		}
		
		BattleRoyale[battle_toxic_size] -= velocity;
		
		if (BattleRoyale[battle_toxic_size] < BattleRoyale[battle_toxic_gosize]) {
		    BattleRoyale[battle_toxic_size] = BattleRoyale[battle_toxic_gosize];
		}

		if (BattleRoyale[battle_toxic_x] > BattleRoyale[battle_toxic_gox]) {
		    BattleRoyale[battle_toxic_x] -= velocity;

			if (BattleRoyale[battle_toxic_x] < BattleRoyale[battle_toxic_gox]) {
		        BattleRoyale[battle_toxic_x] = BattleRoyale[battle_toxic_gox];
		    }
		}
		if (BattleRoyale[battle_toxic_x] < BattleRoyale[battle_toxic_gox]) {
		    BattleRoyale[battle_toxic_x] += velocity;
		    
			if (BattleRoyale[battle_toxic_x] > BattleRoyale[battle_toxic_gox]) {
		        BattleRoyale[battle_toxic_x] = BattleRoyale[battle_toxic_gox];
		    }
		}
		if (BattleRoyale[battle_toxic_y] > BattleRoyale[battle_toxic_goy]) {
		    BattleRoyale[battle_toxic_y] -= velocity;
		    
			if (BattleRoyale[battle_toxic_y] < BattleRoyale[battle_toxic_goy]) {
		        BattleRoyale[battle_toxic_y] = BattleRoyale[battle_toxic_goy];
		    }
		}
		if (BattleRoyale[battle_toxic_y] < BattleRoyale[battle_toxic_goy]) {
		    BattleRoyale[battle_toxic_y] += velocity;
		    
			if (BattleRoyale[battle_toxic_y] > BattleRoyale[battle_toxic_goy]) {
		        BattleRoyale[battle_toxic_y] = BattleRoyale[battle_toxic_goy];
		    }
		}

		// Destruir a GZ
		if (BattleRoyale[battle_gz] != -1)
			DestroyRoundGangZone(BattleRoyale[battle_gz]);
		
		// Recriar a GZ
        BattleRoyale[battle_gz] = CreateRoundGangZone(BattleRoyale[battle_toxic_x], BattleRoyale[battle_toxic_y], BattleRoyale[battle_toxic_size]);

		// Mostrar o circulo para os players
		foreach(new playerid : Player) {
		    // check if player is in battle royale
		    if (IsPlayerInBattleRoyale(playerid)) {
		        ShowRoundGangZoneForPlayer(playerid, BattleRoyale[battle_gz], 0xFFFFFF85);
		    }
		}
	} else {
	    // Tempo para marcar uma nova area do mapa
	    if (BattleRoyale[battle_steptimer] - gettime() > 1000) {
 			BattleRoyale[battle_step]      = 0;
 			
 			if (BattleRoyale[battle_toxic_size] > 1000.0)
 			{
   				BattleRoyale[battle_steptimer] = gettime() + 1 * 60;
			}
			else
			{
			    BattleRoyale[battle_steptimer] = gettime() + 15;
			}
		}
	}
	
	// Checar se terminou o Battle Royale
	if (BattleRoyale[battle_step] == 10 && gettime() > BattleRoyale[battle_steptimer]) {
		// Kill Timer
		KillTimer(BattleRoyale[battle_timer]);
		// destroy things
 		DestroyBattleRoyaleThings();
		// Setar timer para terminar
		SetTimer("resetBattleRoyale", 5000, false);
		// Matar o vencedor
		new playerid = getWinnerBattleRoyale();
		// check if player is valid
		if (playerid != INVALID_PLAYER_ID) {
		    // Setar variaveis
			PlayerData[playerid][dBattleRoyale] = false;
 			PlayerData[playerid][dLobby] 		= false;
		    // setplayer to login menu
		    returnPlayerMenu(playerid);
		}

	    return 1;
	}
	
	// Dano nos players
	foreach(new playerid : Player) {
		// check if player in battle royale and not in lobby
	    if (PlayerData[playerid][dBattleRoyale])
		{
	        if (IsPlayerInToxicGas(playerid) && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
	        {
				// Retirar vida
				GivePlayerHealth(playerid, - (BattleRoyale[battle_step_gas] * 0.89927));
				// check if is dropped player
				if (PlayerData[playerid][dDropped]) {
				    GivePlayerHealth(playerid, - (BattleRoyale[battle_step_gas] * 1.19927));
				}
				// blood effect in the screen
				createPlayerBloodText(playerid);
				// Checar se a vida chegou ao fim
				if (PlayerData[playerid][dVida] <= 0.0) {
					// kill client
					if (PlayerData[playerid][dDropped]) {
						// send message
						SendLanguageMessage(playerid, corInfo, "MSG_DEAD_5");
						// mandar mensagem
						format(string, sizeof (string), "%s morreu para o gas toxico", getNome(playerid));
						SendBattleRoyaleMessage(string);
						serverKillClient(playerid, INVALID_PLAYER_ID, 255);
					} else {
					    // drop client in the ground
	                	dropClient(playerid);
					}
				} else {
				    SendServerMessageToPlayer(playerid, GetPlayerLanguageKey(playerid, "MSG_039"));
				}
			}
		    if (GetPVarInt(playerid, "inAirplane"))
		    {
      			new
				  	Float:x,
				  	Float:y,
				  	Float:z;

				GetPlayerPos(playerid, x, y, z);
				
				if ((x < -2500.0 || x > 2500.0 || y < -2500.0 || y > 2500.0) && gettime() > GetPVarInt(playerid, "setAirPlaneTime"))
				{
			     	GetObjectPos(BattleRoyale[battle_airplane], x, y, z);
			     	// set spawn pos
					SetPVarFloat(playerid, "playerSetSpawnX", x);
					SetPVarFloat(playerid, "playerSetSpawnY", y);
					SetPVarFloat(playerid, "playerSetSpawnZ", z - 5.0);
					// hide textdraws
		    		TextDrawHideForPlayer(playerid, boxDroppedItem1);
		 			TextDrawHideForPlayer(playerid, boxDroppedItem2);
		 			PlayerTextDrawHide(playerid, textCameraItem[playerid]);
					// show loading
					showPlayerLoading(playerid);
					// toggle spectating
					TogglePlayerSpectating(playerid, false);
			        // delete pvar
			      	DeletePVar(playerid, "inAirplane");
				}
		    }
		}
		// Update na textdraw
		format(string, sizeof (string), GetPlayerLanguageKey(playerid, "MSG_042"), countPlayersBattleRoyale(), LocationName(BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy]));
		TextDrawSetString(textBattleRoyale, string);
	}
	
	// check if battle is a winner
	checkBattleRoyaleWinner();
	
	// Atualizar AirDrop
	if (gettime() > BattleRoyale[battle_airdrop] && BattleRoyale[battle_toxic_size] > 850.0) {
		// Chamar o aidrop na area segura
		createBattleRoyaleAirdrop();
		// Setar o tempo
        BattleRoyale[battle_airdrop] = gettime() + 99999;
	}
	
	// Atualizar local onde vai fechar a fumaça
	
	if (gettime() > BattleRoyale[battle_steptimer]) {

	    switch (BattleRoyale[battle_step]) {
			// create a new safe area
	        case 0: {
				// reset area size
	            if (BattleRoyale[battle_toxic_gox] > 3500) {
	                BattleRoyale[battle_toxic_gox] = 2500.0;
	            }
	            if (BattleRoyale[battle_toxic_goy] > 3500) {
	                BattleRoyale[battle_toxic_goy] = 2500.0;
	            }
	            if (BattleRoyale[battle_toxic_gosize] > 3500.0) {
	                BattleRoyale[battle_toxic_gosize] = 3000.0;
	                BattleRoyale[battle_toxic_size]   = 3000.0;
	            }
				// set a new safe area position
				new Float:gox;
				new Float:goy;
				if (BattleRoyale[battle_toxic_gosize] == 3000.0) {
	            	gox = BattleRoyale[battle_toxic_gox] + frandom(BattleRoyale[battle_toxic_gosize]) - frandom(BattleRoyale[battle_toxic_gosize]);
	            	goy = BattleRoyale[battle_toxic_goy] + frandom(BattleRoyale[battle_toxic_gosize]) - frandom(BattleRoyale[battle_toxic_gosize]);
				} else {
	            	gox = BattleRoyale[battle_toxic_gox] + frandom(BattleRoyale[battle_toxic_gosize] / 2.0) - frandom(BattleRoyale[battle_toxic_gosize] / 2.0);
	            	goy = BattleRoyale[battle_toxic_goy] + frandom(BattleRoyale[battle_toxic_gosize] / 2.0) - frandom(BattleRoyale[battle_toxic_gosize] / 2.0);
				}

                BattleRoyale[battle_toxic_gox]    = gox;
				BattleRoyale[battle_toxic_goy]    = goy;
				// size of gang zone safe area
				new Float:gosize = BattleRoyale[battle_toxic_gosize] / 2.0;

				if (gosize < 80.0)
				    gosize = 0.0;

				if (BattleRoyale[battle_safe_gz] != -1)
                	DestroyRoundGangZone(BattleRoyale[battle_safe_gz]);
				// create a new rectangle safe area
                BattleRoyale[battle_safe_gz] = CreateRoundGangZone(BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy], gosize, .extrasize = 7.0);

				foreach(new playerid : Player) {
			 		if (IsPlayerInBattleRoyale(playerid)) {
				       	ShowRoundGangZoneForPlayer(playerid, BattleRoyale[battle_safe_gz], 0x0022FFFF);
				       	SetPlayerMapIcon(playerid, 99, BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy], 0.0, 0, 0x0022FFFF, .style = MAPICON_GLOBAL);
					}
			    }
				// set a timer to avance toxic area
				if (BattleRoyale[battle_toxic_size] < 500)
				{
		            BattleRoyale[battle_step]      = 4;
		            BattleRoyale[battle_steptimer] = gettime() + 15;
		            showTextBattleAnnounce( "A RESTRICAO DA AREA SEGURA FOI MARCADA NO MAPA!" );
				}
				else if (BattleRoyale[battle_toxic_size] < 800)
				{
		            BattleRoyale[battle_step]      = 3;
		            BattleRoyale[battle_steptimer] = gettime() + 15;
		            showTextBattleAnnounce( "A RESTRICAO DA AREA SEGURA FOI MARCADA NO MAPA!" );
				}
				else if (BattleRoyale[battle_toxic_size] < 1300)
				{
		            BattleRoyale[battle_step]      = 2;
		            BattleRoyale[battle_steptimer] = gettime() + 15;
		            showTextBattleAnnounce( "A RESTRICAO DA AREA SEGURA FOI MARCADA NO MAPA!" );
				}
				else
				{
		            BattleRoyale[battle_step]      = 1;
		            BattleRoyale[battle_steptimer] = gettime() + 15;
		            showTextBattleAnnounce( "A RESTRICAO DA AREA SEGURA FOI MARCADA NO MAPA!" );
				}
	            
	            Log::("battleroyale", "BATTLE ROYALE\t|the safe area has been marked");
	        }
	        case 1: {
	            BattleRoyale[battle_step]      = 2;
	            BattleRoyale[battle_steptimer] = gettime() + 15;
	            showTextBattleAnnounce( "O GAS TOXICO SERA LIBERADO EM 2:15 MINUTOS!" );
	        }
	        case 2: {
	            BattleRoyale[battle_step]      = 3;
	            BattleRoyale[battle_steptimer] = gettime() + 1 * 60;
	            showTextBattleAnnounce( "O GAS TOXICO SERA LIBERADO EM 2 MINUTOS!" );
	        }
	        case 3: {
	            BattleRoyale[battle_step]      = 4;
	            BattleRoyale[battle_steptimer] = gettime() + 30;
	            showTextBattleAnnounce( "O GAS TOXICO SERA LIBERADO EM 1 MINUTO!" );
	        }
	        case 4: {
	            BattleRoyale[battle_step]      = 5;
	            BattleRoyale[battle_steptimer] = gettime() + 30;
	            showTextBattleAnnounce( "O GAS TOXICO SERA LIBERADO EM 30 SEGUNDOS!" );
	        }
	        case 5: {
				// reset step timer
	            BattleRoyale[battle_step]      = 0;
	            BattleRoyale[battle_steptimer] = gettime() + 99999;

	            // Escolher um local random do mapa para fechar
				BattleRoyale[battle_toxic_gosize] = BattleRoyale[battle_toxic_size] / 2.0;

				if (BattleRoyale[battle_toxic_gosize] < 80.0) {
				    BattleRoyale[battle_toxic_gosize] = 0.0;
				}

				// Airdrop
				BattleRoyale[battle_airdrop] = gettime() + ((2 * 60) + random(60));
				BattleRoyale[battle_step_gas] ++;

				// Mandar mensagem com o local seguro
				format(string, sizeof (string), "A regiao mais segura fica em: %s", LocationName(BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy]));
				SendBattleRoyaleMessage( string );
                showTextBattleAnnounce( "O GAS TOXICO FOI LIBERADO E AGORA ESTA AVANCANDO!" );

	            // Audio de sirene pra todos que estao no battle royale
	            foreach(new playerid : Player)
				{
					if (PlayerData[playerid][dBattleRoyale])
					{
	                    Audio_Play(playerid, 39);
	                }
	            }
	            
	            Log::("battleroyale", "BATTLE ROYALE\t|the toxic gas has been released");
			}
	    }
	}
	return 1;
}

stock createBattleRoyaleVehicles() {

	for(new vehicleid = 1; vehicleid != sizeof (VehiclesPosInfo); vehicleid++) {

		// Criar apenas alguns
		new rdon_br = random(5);
		
		if (rdon_br > 3)
		    continue;

		// Criar o carro
		new vehicle = CreateVehicle(VehiclesPosInfo[vehicleid][vehModel],
	    VehiclesPosInfo[vehicleid][vehPosX],VehiclesPosInfo[vehicleid][vehPosY],VehiclesPosInfo[vehicleid][vehPosZ],
		VehiclesPosInfo[vehicleid][vehPosA], -1, -1, -1);

		// Setar o virtual world do carro
		SetVehicleVirtualWorld(vehicle, 5001);
		
		VehicleInfo[vehicle][vehFuel] = 999;
		VehicleInfo[vehicle][vehBatery] = 100.0;
		
		// Setar vida do carro
		SetVehicleHealth(vehicle, 950.0);
	}
	
	Log::("battleroyale", "BATTLE ROYALE\t|the battle royale vehicles has been spawned");
}

stock destroyBattleRoyaleVehicles() {
	// Destruir os carros do battle royale
	for(new vehicleid = 1; vehicleid != MAX_VEHICLES; vehicleid++) {
	    if (IsValidVehicle(vehicleid) && GetVehicleVirtualWorld(vehicleid) == 5001) {
	        // Destruir o veiculo
	        DestroyVehicle(vehicleid);
	    }
	}
}

stock checkBattleRoyaleWinner() {
	// check is step
	if (BattleRoyale[battle_step] == 10)
	    return 0;
	// count players in battle
	if (countPlayersBattleRoyale() > MAX_BATTLEROYALE_WINNERS)
	    return 0;
	// get a player winner
	new pId = getWinnerBattleRoyale();
	
	if ( pId != INVALID_PLAYER_ID ) {
	    showTextBattleAnnounce(GetPlayerLanguageKey(pId, "BR_WIN"), .interval = 20000, .playerid = pId);
	    // Add vezes que ganhou
	    PlayerData[pId][dWinsBattleRoyale] ++;
	    
	    SetTimerEx("GiveCrate", 3000, false, "d", pId);
	    
	    SendClientMessageToAllf(0xAAAAAAFF, "[Battle Royale]: A batalha terminou tendo {FFFFFF}%s {AAAAAA}como vencedor!", getNome(pId));
	    
	    checkPlayerConquista(pId, Conquista_BattleRoyale);
	    
	    if (!SHOP_IsPlayerHaveSkinId(pId, 22008))
	    {
	        SHOP_GiveItem(pId, 22008, 0, 4, .gender = 0, .time = -1, .legacy = 1, .name = "Battleroyale skin");
	    }
	    
	    Log::("battleroyale", "BATTLE ROYALE\t|the battle royale ends with %s winner", getNome(pId));
	} else {
	    SendBattleRoyaleInfo("A BATALHA TERMINOU SEM NENHUM VENCEDOR!");
	    
	    SendClientMessageToAll(0xAAAAAAFF, "[Battle Royale]: A batalha terminou sem nenhum vencedor!");
	    
	    Log::("battleroyale", "BATTLE ROYALE\t|the battle royale ends with NO winner");
	}
	
	if (BattleRoyale[battle_gz] != -1)
	    DestroyRoundGangZone(BattleRoyale[battle_gz]);
	
	if (BattleRoyale[battle_safe_gz] != -1)
	    DestroyRoundGangZone(BattleRoyale[battle_safe_gz]);
	
	BattleRoyale[battle_gz] = -1;
	BattleRoyale[battle_safe_gz] = -1;
	
 	BattleRoyale[battle_step]      = 10;
	BattleRoyale[battle_steptimer] = gettime() + 10;
	
	return 1;
}


stock setPlayersBattleRoyale() {

	foreach(new playerid : Player) {
	
	    if (PlayerData[playerid][dLobby]) {
	        setPlayerBattleRoyale(playerid);
	    }
	}
}

stock countPlayersInLobby() {

	new count;
	foreach(new playerid : Player) {

		if (PlayerData[playerid][dLobby]) {
	        count++;
	    }
	}
	return count;
}

stock getWinnerBattleRoyale() {

	foreach(new playerid : Player) {

		if (PlayerData[playerid][dBattleRoyale]) {
	        return playerid;
	    }
	}
	return INVALID_PLAYER_ID;
}

stock countPlayersBattleRoyale() {

	new count;
	foreach(new playerid : Player) {

		if (PlayerData[playerid][dBattleRoyale]) {
	        count++;
	    }
	}
	return count;
}

stock IsPlayerInToxicGas(playerid) {

	if (!IsPlayerInArea(playerid, BattleRoyale[battle_toxic_x], BattleRoyale[battle_toxic_y], BattleRoyale[battle_toxic_size]))
	    return 1;

	return 0;
}

stock IsPlayerInArea(playerid, Float:px, Float:py, Float:size)
{
	new Float:MinX = px - size;
	new Float:MinY = py - size;
	new Float:MaxX = px + size;
	new Float:MaxY = py + size;

    new Float: X, Float: Y, Float: Z;
    GetPlayerPos(playerid, X, Y, Z);

	if (X < MaxX && X > MinX && Y < MaxY && Y > MinY)
	    return 1;
	    
	return 0;
}

stock destroyBattleRoyaleItens() {

	for(new drop = MAX_DROP_ITENS - sizeof BattleRoyale_Itens; drop > -1; drop--) {
	    if (Iter_Contains(iterDrops, drop) && DropItensInfo[drop][drop_world] == 5001) {
	     	destroyDropItem(drop);
	     	printf("BR: %d jas been destroyed", drop);
	    }
	}
	
	for(new loot; loot < MAX_LOOTS; loot++) {
	
	    if (LootInfo[loot][loot_world] == 5001) {
	        destroyLoot(loot);
	        printf("BR: loot %d has been destroyed", loot);
	    }
	}
	Log::("battleroyale", "BATTLE ROYALE\t|the battle royale itens has been destroyed");
}

stock createBattleRoyaleAirdrop() {
	// string
	new string[75];
	// Mandar mensagem para os participantes
	format(string, sizeof (string), "O AirDrop sera largado em: %s", LocationName(BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy]));
    SendBattleRoyaleMessage( string );
	SendBattleRoyaleMessage( "Um aviao ira largar itens militares na area segura do mapa" );
	// Chamar o aidrop
    CallAirDrop(BattleRoyale[battle_toxic_gox], BattleRoyale[battle_toxic_goy], 5001, LOOT_TYPE_BATTLEROYALE);
}

stock initPlayerLobby(playerid) {
	// Setar variaveis
	PlayerData[playerid][dBattleRoyale] = false;
 	PlayerData[playerid][dLobby] 		= true;
 	// Setar vida
 	PlayerData[playerid][dVida] = 100.0;
	// Setar uma posição random no lobby
	SetSpawnInfo(playerid, 1, 141, 2481.4751 + frandom(5.0) - frandom(5.0),4262.4268 + frandom(5.0) - frandom(5.0),13.3923 + 0.2, random(360), 0, 0, 0, 0, 0, 0);
	// Esconder o menu de login
    hideLoginMenu(playerid, true);
	// Fade In
	fadeIn(playerid, 1500);
	// Efeito de som
	Audio_Play(playerid, 22);
	// resetar inventario
	resetInventory(playerid);
	// Reset armor/helmet
	RemovePlayerHelmet(playerid);
	RemovePlayerArmor(playerid);
	// Timer para colocar no lobby
	SetTimerEx("setPlayerLobby", 2500, false, "d", playerid);
	
	PlayerData[playerid][dLanterna]     = false;
	PlayerData[playerid][dSangramento]  = 0.0;
	PlayerData[playerid][dRadiacao]  	= 0.0;
	PlayerData[playerid][dVirus]  		= 0.0;
	
	SetPVarFloat(playerid, "playerSetSpawnX", frandom(3000) - frandom(3000));
	SetPVarFloat(playerid, "playerSetSpawnY", frandom(3000) - frandom(3000));
	SetPVarFloat(playerid, "playerSetSpawnZ", 400.0);
	
	PlayerData[playerid][dServerState] = SERVER_STATE_LOBBY;
	
	Log::("battleroyale", "BATTLE ROYALE\t|player %s has entered in the lobby", getNome(playerid));
}

callback setPlayerLobby(playerid) {
    PlayerData[playerid][dVida] = 100.0;
	// Setar o world para 5000
	SetPlayerVirtualWorld(playerid, 5001);
	// Setar Interior
	SetPlayerInterior(playerid, 0);
	// Skin
	if (PlayerData[playerid][dSkin] != -1)
		SetPlayerSkin(playerid, PlayerData[playerid][dSkin]);
	else
	    SetPlayerSkin(playerid, PlayerData[playerid][dTempSkin]);
	// spawnar player
	TogglePlayerSpectating(playerid, false);
	// fade out
	fadeOut(playerid, 4000);
	// Parar a música
	Audio_Stop(playerid, PlayerData[playerid][dHandleAudio]);
	// Mostrar a textdraw
	TextDrawShowForPlayer(playerid, textBattleRoyale);
	// reset weapons
	ResetPlayerWeapons(playerid);
	// Reset armor/helmet
	RemovePlayerHelmet(playerid);
	RemovePlayerArmor(playerid);
//	hideLoading(playerid);
	// Update na textdraw
	SendLanguageMessage(playerid, 0x00AAFFFF, "MSG_92");
	if (!BattleRoyale[battle_started]) {
	
	    new string[75];
	
		format(string, sizeof (string), "Jogadores preparados: %d/%d", countPlayersInLobby(), MIN_START_BATTLEROYALE);
		TextDrawSetString(textBattleRoyale, string);
	 	// Mensagem pra quem estiver no lobby
		format(string, sizeof (string), "%s entrou: %d jogadores preparados", getNome(playerid), countPlayersInLobby());
		SendBattleRoyaleMessage(string);
	} else {
	    SendLanguageMessage(playerid, 0x00AAFFFF, "MSG_93");
	}
}

stock SpawnPlayerToBattleRoyale(playerid) {
	// Setar o virtualworld
	SetPlayerVirtualWorld(playerid, 5001);
	// Setar o interior
	SetPlayerInterior(playerid, 0);
	// reset weapons
	ResetPlayerWeapons(playerid);
	// resetar inventario
	resetInventory(playerid);
	// Setar a skin do player
	if (PlayerData[playerid][dSkin] != -1)
		SetPlayerSkin(playerid, PlayerData[playerid][dSkin]);
	else
	    SetPlayerSkin(playerid, PlayerData[playerid][dTempSkin]);
	// Dar mochila
	givePlayerMochila(playerid, ITEM_TYPE_BACKPACK1);
	// Setar a vida
	SetPlayerHealth(playerid, 100.0);
	// Variaveis
	PlayerData[playerid][dLobby] 		= false;
	PlayerData[playerid][dBattleRoyale] = true;
	PlayerData[playerid][dVida]         = 100.0;
	PlayerData[playerid][dLanterna]     = false;
	// Add vezes que participou
	PlayerData[playerid][dTimesBattleRoyale] ++;
	PlayerData[playerid][dServerState] = SERVER_STATE_BATTLE;

 	showInfoTextdraws(playerid);
  	hidePlayerLoading(playerid);
	// Reset armor/helmet
	RemovePlayerHelmet(playerid);
	RemovePlayerArmor(playerid);
	// Máscara de gás
	if (PlayerData[playerid][dGasMask])
	{
	    SetPlayerAttachedObject(playerid, 9, 19472,2,0.000999,0.127000,-0.000999,-110.000030,100.699935,-156.299911,0.836999,0.877000,1.100000);
	} else {
	    RemovePlayerAttachedObject(playerid, 9);
	}

	// Caso a primeira pessos estiver ativada
	if (PlayerData[playerid][dFirstPerson])
	{
		// Ativar o fps
		ActivePlayerFPS(playerid);
	}

  	Audio_Stop(playerid, GetPVarInt(playerid, "airplaneSound"));
  	StopAudioStreamForPlayer(playerid);
  	if (Audio_IsClientConnected(playerid))
  	{
  	    Audio_Play(playerid, 1);
  	}
  	
	new Float:x = GetPVarFloat(playerid, "playerSetSpawnX");
	new Float:y = GetPVarFloat(playerid, "playerSetSpawnY");
	new Float:z = GetPVarFloat(playerid, "playerSetSpawnZ");

   	// Dar um paraquedas
	GivePlayerWeapon(playerid, 46, 1);

	SetPlayerPos(playerid,
			x,
			y,
			z);
  	
  	DeletePVar(playerid, "playerSetSpawnX");
  	DeletePVar(playerid, "playerSetSpawnY");
  	DeletePVar(playerid, "playerSetSpawnZ");
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if (IsPlayerInBattleRoyale(playerid) && newkeys & 16)
	{
	    if (GetPVarInt(playerid, "inAirplane"))
	    {
	        new Float:x, Float:y, Float:z;
	        
			GetPlayerPos(playerid, x, y, z);
			
			if (x < -2800.0 || x > 2800.0 || y < -2800.0 || y > 2800.0)
			    return SendLanguageMessage(playerid, corCinza, "MSG_94");
	        
	        GetObjectPos(BattleRoyale[battle_airplane], x, y, z);
	        // set spawn pos
			SetPVarFloat(playerid, "playerSetSpawnX", x);
			SetPVarFloat(playerid, "playerSetSpawnY", y);
			SetPVarFloat(playerid, "playerSetSpawnZ", z - 5.0);
			// hide textdraws
    		TextDrawHideForPlayer(playerid, boxDroppedItem1);
 			TextDrawHideForPlayer(playerid, boxDroppedItem2);
 			PlayerTextDrawHide(playerid, textCameraItem[playerid]);
			// show loading
			showPlayerLoading(playerid);
			// toggle spectating
			TogglePlayerSpectating(playerid, false);
	        // delete pvar
	        DeletePVar(playerid, "inAirplane");
	    }
	}
	#if defined brOnPlayerKeyStateChange
	    brOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
 	#endif
	return 1;
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange brOnPlayerKeyStateChange
#if defined brOnPlayerKeyStateChange
   	forward brOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

callback descongelarLobby(playerid) return TogglePlayerControllable(playerid, true);



