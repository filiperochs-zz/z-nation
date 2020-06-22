
forward OnPlayerStartIntro(playerid);
forward OnPlayerEndIntro(playerid);

enum introEnum {

	introTitulo[45],
	introNomes[128],
	introTempo,
	
	// Camera pos
	Float:CamStartX,
	Float:CamStartY,
	Float:CamStartZ,
	Float:CamEndX,
	Float:CamEndY,
	Float:CamEndZ,
	
	// Camera look
	Float:LookStartX,
	Float:LookStartY,
	Float:LookStartZ,
	Float:LookEndX,
	Float:LookEndY,
	Float:LookEndZ,
}

new playerTimerIntroducao[MAX_PLAYERS];

new playerTimerCamIntro[MAX_PLAYERS];

#pragma unused playerTimerCamIntro

new playerIntroId[MAX_PLAYERS];

stock const IntroArray[][introEnum] = {

//     Titulo            Nomes         	  						Tempo
	{"CONTRIBUIDOR", 	"Nero_3D",     							9000,      -28.035308, 1004.411682, 50.825958, -24.387241, 1187.691650, 41.853858,        -27.891246, 1009.267517, 49.642669, -27.665849, 1191.244262, 40.577140},
	{"CONTRIBUIDOR", 	"Theus_Crazzy",     					9000,      -425.889892, 1261.159545, 60.782447, -695.213989, 1187.478271, 48.981796,      -429.011444, 1257.910278, 58.614856, -697.009338, 1183.354858, 46.796848},
	{"CONTRIBUIDOR", 	"Y_Less",     							9000,      -118.205055, -55.506320,  27.694372, 122.380050, 135.372222, 16.892074,        -115.093498, -52.028919, 25.898300, 127.285491, 135.089874, 15.966382},
	
	{"MAPPER", 			"C4DU",    								9000,      590.336364, 332.910278,  24.609607, 405.487213, 589.999938, 23.879989,   		588.117431, 337.388916, 24.475292, 405.885467, 594.981079, 23.707136},
	{"BETA TESTERS", 	"Nicky_Scarface~n~Gaby_Scarface~n~",	9000,      1274.585083, 547.414428,  49.691596, 1667.540893, 393.438262, 49.691596,   		1272.874877, 542.735046, 49.268600, 1665.723510, 388.801269, 49.249393},
	
	{"BETA TESTERS", 	"Fabio_Rpk~n~Relaxed",   				9000,      1662.383300, -232.823303, 78.328330, 1703.122802, -593.380187, 55.562496,   	1662.909423, -237.657241, 77.163780, 1703.471679, -598.365600, 55.717308},
	{"BETA TESTERS", 	"Alisson~n~sarah_scarface~n~The_Nikloxs~n~",9000,      989.599487, -275.772644, 110.125915, 985.931518, -598.353210, 130.033294,   	993.619445, -278.307403, 108.571907, 990.807861, -598.937072, 129.094879},
	{"BETA TESTERS", 	"Network_Scarface~n~LawRenCe~n~",			9000,      118.251327, -1761.897583, 22.891578, 328.429901, -2020.463500, 45.255950,   	119.751159, -1766.574096, 21.953168, 331.865936, -2023.343139, 43.042068},
	{"BETA TESTERS", 	"elPedro~n~tommy_scarface~n~C4DU~n~",  	9000,      -2614.690185, -2341.170410, 63.975166, -2285.359130, -2219.797119, 71.617584,   -2610.085693, -2339.903076, 62.494632, -2281.222412, -2216.989257, 71.676033},
	{"BETA TESTERS", 	"Escorpiao_Negro~n~Joao_LorD~n~", 		9000,      -1843.142578, -2337.550292, 101.736259, -1654.982421, -2247.691406, 46.938484,  -1838.334838, -2336.714111, 100.646835, -1651.168823, -2246.183593, 44.077991},
	
	{"PRODUZIDO POR", 	"dimmy_scarface",   					15600,      -1260.226440, -2363.994873, 67.948738, -1144.730834, -2663.515869, 85.251945,   -1264.199218, -2366.916748, 67.124183, -1144.499877, -2668.474853, 84.656364}
};

// Funcs
stock playerPlayIntro(playerid) {

	if (PlayerData[playerid][dIntroducao])
	    return 0;
	    
	StopAudioStreamForPlayer(playerid);
	    
	// Parar batida de coração
	if (PlayerData[playerid][dHeartAudio] != -1) {
		Audio_Stop(playerid, PlayerData[playerid][dHeartAudio]);
		PlayerData[playerid][dHeartAudio] = -1;
	}
	    
    playerIntroId[playerid] = -1;
	    
    fadeIn(playerid, 1000);
    
    playerTimerIntroducao[playerid] = SetTimerEx("updatePlayerIntro", 4000, false, "d", playerid);

	TogglePlayerServerTime(playerid, 1);
	
	SetPlayerTime(playerid, 0, 0);
	
	SetPVarInt(playerid, "playerInIntro", 1);
	
	PlayerData[playerid][dServerState] = SERVER_STATE_INTRO;

	return 1;
}

stock IsPlayerInIntro(playerid) return GetPVarInt(playerid, "playerInIntro");

callback updatePlayerIntro(playerid) {

	// Toggle spectating
	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING) {
		TogglePlayerSpectating(playerid, true);
	}
	
	if (playerIntroId[playerid] == -1) {
	
	    if (Audio_IsClientConnected(playerid))
	    {
		    Audio_Stop(playerid, PlayerData[playerid][dHandleAudio]);

		    PlayerData[playerid][dHandleAudio] = Audio_PlayStreamed(playerid, "http://192.99.120.57/znation-intro.mp3");
		}
		else
		{
			PlayAudioStreamForPlayer(playerid, "http://192.99.120.57/znation-intro.mp3");
		}
	}
	
	// Interior
	SetPlayerInterior(playerid, 0);
	
	// Limpar chat
	clearPlayerChat(playerid);
	
	// Setar world
	SetPlayerVirtualWorld(playerid, playerid + MAX_PLAYERS);
    
	// Pular intro
    playerIntroId[playerid] ++;
    
    if (playerIntroId[playerid] >= sizeof (IntroArray)) {
    
        #if defined OnPlayerEndIntro
            OnPlayerEndIntro(playerid);
		#endif
    
        return 1;
    }
    
    // Criar textdraws
    CreateTextDrawsIntro(playerid);
    
    new
        string[128];
    
    fadeIn(playerid, 300);
    
    format(string, sizeof string, IntroArray[playerIntroId[playerid]][introTitulo]);
    
    PlayerTextDrawSetString(playerid, textIntroducao[0][playerid], string);
    
    format(string, sizeof string, IntroArray[playerIntroId[playerid]][introNomes]);

    PlayerTextDrawSetString(playerid, textIntroducao[1][playerid], string);
    
    playerTimerIntroducao[playerid] = SetTimerEx("updatePlayerIntro", IntroArray[playerIntroId[playerid]][introTempo], false, "d", playerid);
    
    SetPVarInt(playerid, "timerIntro1", SetTimerEx("fadeOutIntro", 1500, false, "d", playerid));
    
    SetPVarInt(playerid, "timerIntro2", SetTimerEx("setCameraIntroducao", 900, false, "d", playerid));
    
    SetPVarInt(playerid, "timerIntro3", SetTimerEx("showPlayerIntro", 3000, false, "d", playerid));
    
    return 1;
}

callback fadeOutIntro(playerid) {
    SetPVarInt(playerid, "timerIntro1", -1);
	return fadeOut(playerid, 400);
}

callback showPlayerIntro(playerid) {

	for(new text; text < 2; text++) {
	    PlayerTextDrawShow(playerid, textIntroducao[text][playerid]);
	}
	SetTimerEx("hidePlayerIntro", 6000, false, "d", playerid);
	
	SetPVarInt(playerid, "timerIntro3", -1);
}

callback hidePlayerIntro(playerid) {

	for(new text; text < 2; text++) {
	    PlayerTextDrawHide(playerid, textIntroducao[text][playerid]);
	}
}

callback setCameraIntroducao(playerid) {

	static
	    index;
	    
	index = playerIntroId[playerid];

	InterpolateCameraPos(playerid, IntroArray[index][CamStartX], IntroArray[index][CamStartY], IntroArray[index][CamStartZ],
                                   IntroArray[index][CamEndX], IntroArray[index][CamEndY], IntroArray[index][CamEndZ], 20000);
                                   
 	InterpolateCameraLookAt(playerid, IntroArray[index][LookStartX], IntroArray[index][LookStartY], IntroArray[index][LookStartZ],
                                   IntroArray[index][LookEndX], IntroArray[index][LookEndY], IntroArray[index][LookEndZ], 20000);
                                   
    SetPVarInt(playerid, "timerIntro2", -1);
}

stock CreateTextDrawsIntro(playerid) {

	PlayerTextDrawDestroy(playerid, textIntroducao[0][playerid]);
	PlayerTextDrawDestroy(playerid, textIntroducao[1][playerid]);

	new Float:randonFloatX = 80.00 + frandom(320.0);
	new Float:randonFloatY = 190.0 + frandom(100.0);

	//textIntroducao[0][playerid] = CreatePlayerTextDraw(playerid, 436.000000, 237.000000, "CONTRIBUIDOR");
	textIntroducao[0][playerid] = CreatePlayerTextDraw(playerid, randonFloatX, randonFloatY, "CONTRIBUIDOR");
	PlayerTextDrawAlignment(playerid,textIntroducao[0][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textIntroducao[0][playerid], 0);
	PlayerTextDrawFont(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid,textIntroducao[0][playerid], 0.200000, 0.799998);
	PlayerTextDrawColor(playerid,textIntroducao[0][playerid], -216);
	PlayerTextDrawSetOutline(playerid,textIntroducao[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textIntroducao[0][playerid], 0);

	//textIntroducao[1][playerid] = CreatePlayerTextDraw(playerid,437.000000, 246.000000, "Ninguem");
	textIntroducao[1][playerid] = CreatePlayerTextDraw(playerid, randonFloatX, randonFloatY + 10.0, "Ninguem");
	PlayerTextDrawAlignment(playerid,textIntroducao[1][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textIntroducao[1][playerid], 0);
	PlayerTextDrawFont(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid,textIntroducao[1][playerid], 0.290000, 1.399998);
	PlayerTextDrawColor(playerid,textIntroducao[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textIntroducao[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textIntroducao[1][playerid], 0);
}

public OnPlayerEndIntro(playerid) {

	TextDrawShowForPlayer(playerid, textIntroEnd[0]);
	TextDrawShowForPlayer(playerid, textIntroEnd[1]);
	
	PlayerData[playerid][dIntroducao] = true;

	SetPVarInt(playerid, "timerIntro4", SetTimerEx("endIntroducao", 8000, false, "d", playerid));
}

callback endIntroducao(playerid) {

	// Fade in
	fadeIn(playerid, 4000);

	// Setar um timer para spawnar
	SetPVarInt(playerid, "timerSpawnPlayer", SetTimerEx("spawnarPlayer", 6000, false, "dd", playerid, PlayerData[playerid][dNewGame] ? (1) : (0)));
	
	SetPVarInt(playerid, "timerIntro4", -1);
}

CMD:intro(playerid) {

	if (!PlayerData[playerid][dIntroducao]) {
	    return SendLanguageMessage(playerid, corBranco, "MSG_068");
	}

    PlayerData[playerid][dIntroducao] = false;
    SendLanguageMessage(playerid, corInfo, "MSG_069");
	return 1;
}










