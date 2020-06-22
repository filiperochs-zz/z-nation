
stock showPlayerConfigs(playerid) {

	// checar se está logado
	if (!PlayerData[playerid][dLogged])
		return SendClientMessage(playerid, corError, "ERRO: {999999}Você precisa estar logado!");

	// Mostrar as configurações
	for(new text; text != sizeof (textConfig); text++) {
	    TextDrawShowForPlayer(playerid, textConfig[text]);
	}
	PlayerTextDrawShow(playerid, textPlayerConfig[playerid]);
	
	// Atualizar as configs
	updatePlayerConfigs(playerid);
	
	PlayerData[playerid][dConfig] = true;
	
	return 1;
}

stock hidePlayerConfigs(playerid) {

	// Mostrar as configurações
	for(new text; text != sizeof (textConfig); text++) {
	    TextDrawHideForPlayer(playerid, textConfig[text]);
	}
	PlayerTextDrawHide(playerid, textPlayerConfig[playerid]);
	
	PlayerData[playerid][dConfig] = false;
}

stock updatePlayerConfigs(playerid) {

	// Variável
	new string_config[128];
	
	// Formatar
	format(string_config, sizeof (string_config), "\
	: %s~n~~n~\
	: %s~n~~n~\
	: %s~n~~n~\
	: %s~n~~n~\
	: %s~n~~n~\
	: %s",
	PlayerData[playerid][dMusic] 	   ? ("On") : ("Off"),
	PlayerData[playerid][dPoints3D]    ? ("On") : ("Off"),
	PlayerData[playerid][dFirstPerson] ? ("On") : ("Off"),
	PlayerData[playerid][dEconomia]    ? ("On") : ("Off"),
	GetPlayerLanguage(playerid),
	PlayerData[playerid][dWeather]     ? ("On") : ("Off"));
	
	// Atualizar a textdraw
	PlayerTextDrawSetString(playerid, textPlayerConfig[playerid], string_config);
}

stock showPlayerStatus(playerid) {

	TextDrawShowForPlayer(playerid, textBaseHud);

	for(new text; text < sizeof playerHudTextdraw; text++) {
		PlayerTextDrawShow(playerid, playerHudTextdraw[text]);
	}
	SetPVarInt(playerid, "plstatus", 1);
}

stock hidePlayerStatus(playerid) {

	TextDrawHideForPlayer(playerid, textBaseHud);

	for(new text; text < sizeof playerHudTextdraw; text++) {
		PlayerTextDrawHide(playerid, playerHudTextdraw[text]);
	}
	DeletePVar(playerid, "plstatus");
}

// Craft
stock showPlayerCraftTabble(playerid) {

	if (PlayerData[playerid][dCrafting])
	    return 0;
	    
	// Esconder textdraws
	
	hideTextDrawsStatus(playerid);
	
	// Mostrar textdraws craft
	    
	showTextDrawsCraft(playerid);
	    
	// Reset craft
	resetPlayerCraft(playerid);
	    
    PlayerData[playerid][dCrafting] = true;

	return 1;
}

stock hidePlayerCraftTabble(playerid) {

	if (!PlayerData[playerid][dCrafting])
	    return 0;

	// Mostrar textdraws

	//showTextDrawsStatus(playerid);

	// Esconder textdraws craft

	hideTextDrawsCraft(playerid);

    PlayerData[playerid][dCrafting] = false;

	return 1;
}

stock showTextItemDiscription(playerid, discription[])
{
	PlayerTextDrawSetString(playerid, textInfoBox[2][playerid], discription);
	
	for (new text; text < 3; text++)
	{
	    PlayerTextDrawShow(playerid, textInfoBox[text][playerid]);
	}
}

stock hideTextItemDiscription(playerid)
{
	for (new text; text < 3; text++)
	{
	    PlayerTextDrawHide(playerid, textInfoBox[text][playerid]);
	}
}

stock showTextInfoDeath(playerid, discription[], interval = 5000, color = -116)
{
	PlayerTextDrawSetString(playerid, textInfoDeath[playerid], discription);
	PlayerTextDrawColor(playerid, textInfoDeath[playerid], color);
	PlayerTextDrawShow(playerid, textInfoDeath[playerid]);
	
	if (GetPVarInt(playerid, "playerInfoDeath") != 0)
	    KillTimer(GetPVarInt(playerid, "playerInfoDeath"));
	    
    SetPVarInt(playerid, "playerInfoDeath", SetTimerEx("hideTextInfoDeath", interval, false, "d", playerid));
}

callback hideTextInfoDeath(playerid)
{
	PlayerTextDrawHide(playerid, textInfoDeath[playerid]);

    DeletePVar(playerid, "playerInfoDeath");
}

stock showTextBattleAnnounce(discription[], interval = 9000, color = -44936, playerid = INVALID_PLAYER_ID)
{
	TextDrawSetString(textBattleAnnounce, discription);
	TextDrawColor(textBattleAnnounce, color);
	
	if (playerid == INVALID_PLAYER_ID) {
		foreach(new x : Player) {
		    if (IsPlayerInBattleRoyale(x)) {
		        TextDrawShowForPlayer(x, textBattleAnnounce);
		    } else {
		        TextDrawHideForPlayer(x, textBattleAnnounce);
		    }
		}
	} else {
	    TextDrawHideForAll(textBattleAnnounce);
	    TextDrawShowForPlayer(playerid, textBattleAnnounce);
	}

	if (GetSVarInt("g_AnnounceBattle") != 0)
	    KillTimer(GetSVarInt("g_AnnounceBattle"));

    SetSVarInt("g_AnnounceBattle", SetTimer("hideTextBattleAnnounce", interval, false));
}

callback hideTextBattleAnnounce()
{
	TextDrawHideForAll(textBattleAnnounce);

    DeleteSVar("g_AnnounceBattle");
}

stock showTextDrawsBlocked(playerid)
{
	for(new index; index < 2; index++)
		TextDrawShowForPlayer(playerid, textBlockedAccount[index]), PlayerTextDrawShow(playerid, playerTextBlocked[index]);
}

stock hideTextDrawsBlocked(playerid)
{
	for(new index; index < 2; index++)
		TextDrawHideForPlayer(playerid, textBlockedAccount[index]), PlayerTextDrawHide(playerid, playerTextBlocked[index]);
}

stock showTextDrawsStatus(playerid) {

    PlayerData[playerid][dCrafting] = false;
    PlayerData[playerid][dCondicao] = false;

	PlayerTextDrawShow(playerid, textPlayerInventory[0]);
	PlayerTextDrawShow(playerid, textPlayerInventory[4]);
	PlayerTextDrawShow(playerid, playerHealthProtect);
}

stock hideTextDrawsStatus(playerid) {
    PlayerTextDrawHide(playerid, textPlayerInventory[0]);
	PlayerTextDrawHide(playerid, textPlayerInventory[4]);
	PlayerTextDrawHide(playerid, playerHealthProtect);
}

stock showTextDrawsCraft(playerid) {
	for(new index; index < 12; index++)
		PlayerTextDrawShow(playerid, playerTextDrawsCraft[index]);
}

stock hideTextDrawsCraft(playerid) {
	for(new index; index < 12; index++)
		PlayerTextDrawHide(playerid, playerTextDrawsCraft[index]);
}

stock showTextDrawsCondicao(playerid) {

	if (PlayerData[playerid][dCondicao])
	    return 0;

    PlayerData[playerid][dCondicao] = true;
    
    hideTextDrawsStatus(playerid);
    
    if (PlayerData[playerid][dCrafting])
    	hideTextDrawsCraft(playerid);
    	
	PlayerTextDrawShow(playerid, playerTextDrawsCraft[0]);
	PlayerTextDrawShow(playerid, textInventoryCondicao);
    	
	new string_players[75];
    	
	stringGlobal[0] = EOS;
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_7"), PlayerData[playerid][dVida]);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_8"), PlayerData[playerid][dFome]);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_9"), PlayerData[playerid][dSede]);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_10"), PlayerData[playerid][dRadiacao] * 100.0);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_11"), PlayerData[playerid][dDoenca] ? (GetPlayerLanguageKey(playerid, "INFO_4")) : (GetPlayerLanguageKey(playerid, "INFO_5")));
    strcat(stringGlobal, string_players);
	strcat(stringGlobal, "~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_12"), PlayerData[playerid][dSangramento] * 100.0);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");
	format(string_players, sizeof string_players, GetPlayerLanguageKey(playerid, "INFO_13"), PlayerData[playerid][dVirus] * 100.0);
	strcat(stringGlobal, string_players);
	strcat(stringGlobal, "%%~n~~n~");

	PlayerTextDrawSetString(playerid, textInventoryCondicao, stringGlobal);
    	
    PlayerData[playerid][dCrafting] = false;
    
    return 1;
}

stock hideTextDrawsCondicao(playerid) {

	if (!PlayerData[playerid][dCondicao])
	    return 0;

    PlayerData[playerid][dCondicao] = false;

    PlayerTextDrawHide(playerid, playerTextDrawsCraft[0]);
    PlayerTextDrawHide(playerid, textInventoryCondicao);
    
	return 1;
}

stock showLoginMenu(playerid, bool: select=true) {
	RemovePlayerMapIcon(playerid, 99);
    PlayerData[playerid][dAdminDuty] = false;

	for(new text; text < sizeof textLoginScreen; text++)
	{
	    TextDrawShowForPlayer(playerid, textLoginScreen[text]);
	}
	
	// Mostrar o botao
	PlayerTextDrawShow(playerid, texPlayerLoginScreen);
	
	// update o botão
	updateButtonMenu(playerid);

    SetPVarInt(playerid, "vmenuLogin", 1);
    
    ResetPlayerWeapons(playerid);
    SetPlayerCuffed(playerid, false);

	// Se select for "true"
	if (select) {
		// Ativar a seleção de TextDraws
		SelectTextDraw(playerid, 0xFFFFFFFF);
	}
	
	// Esconder o menu de configs
	if (PlayerData[playerid][dConfig]) {
	    hidePlayerConfigs(playerid);
	}
	
	// Esconder a textdraw Battle Royale
	TextDrawHideForPlayer(playerid, textBattleRoyale);
	
	if (PlayerData[playerid][dLogged])
	{
	    TextDrawShowForPlayer(playerid, textChangeDSkin);
	}
}

stock hideLoginMenu(playerid, bool:cancelselect=true) {

	// Escolher o menu de login
	for(new text; text < sizeof textLoginScreen; text++)
	{
	    TextDrawHideForPlayer(playerid, textLoginScreen[text]);
	}

	// Esconder o botao
    PlayerTextDrawHide(playerid, texPlayerLoginScreen);

    DeletePVar(playerid, "vmenuLogin");

	// Cancelar a seleção de TextDraws
	if (cancelselect) {
		CancelSelectTextDraw(playerid);
	}
	
    TextDrawHideForPlayer(playerid, textAdminMode1);
    TextDrawHideForPlayer(playerid, textChangeDSkin);
	
	// Esconder o menu de configs
	if (PlayerData[playerid][dConfig]) {
	    hidePlayerConfigs(playerid);
	}
	
	KillTimer(GetPVarInt(playerid, "pHideLoading"));
}

callback showPlayerLoading(playerid) {

	// Mostrar a tela de carregamento
    TextDrawShowForPlayer(playerid, textLoading);
}

stock hidePlayerLoading(playerid) {

	// Esconder a tela de carregamento
    TextDrawHideForPlayer(playerid, textLoading);
}

callback showPlayerMap(playerid) {

	// Mostrar o mapa
	for(new text; text != sizeof (textMap); text++) {
	    TextDrawShowForPlayer(playerid, textMap[text]);
	}
}

callback hidePlayerMap(playerid) {

	// esconder o mapa
	for(new text; text != sizeof (textMap); text++) {
	    TextDrawHideForPlayer(playerid, textMap[text]);
	}
}

stock showInfoTextdraws(playerid) {

	// Mostrar as informações na tela
	TextDrawShowForPlayer(playerid, textBoxInfo1);
	TextDrawShowForPlayer(playerid, textBoxInfo2);
	TextDrawShowForPlayer(playerid, textBoxInfo3);
	PlayerTextDrawShow(playerid, playerTextBoxInfo[playerid]);
	
	// Verificar se não está no battle royale
	if (!IsPlayerInBattleRoyale(playerid)) {

		if (IsPlayerHaveNotebook(playerid)) {
		    // Mostrar a localização do player
			// Hud mapa
			for(new text; text != sizeof (textHud); text++) {
			    TextDrawHideForPlayer(playerid, textHud[text]);
			}
			GangZoneHideForPlayer(playerid, HUD_GZ);
			ShowPlayerMapIcons(playerid);
		} else {
		    // Se não tiver, esconder a localização
			for(new text; text != sizeof (textHud); text++) {
			    TextDrawShowForPlayer(playerid, textHud[text]);
			}
			GangZoneShowForPlayer(playerid, HUD_GZ, 0x222222FF);
			RemovePlayerMapIcons(playerid);
		}
	}
	
	// Barulho
	TextDrawShowForPlayer(playerid, textBarulho);
	
	PlayerTextDrawShow(playerid, textPlayerBarulho[0]);
	PlayerTextDrawShow(playerid, textPlayerBarulho[1]);
	
	// Pontuação
/*	TextDrawShowForPlayer(playerid, textPoints[0]);
	TextDrawShowForPlayer(playerid, textPoints[1]);
	PlayerTextDrawShow(playerid, playerTextPoints[playerid]);
	PlayerTextDrawShow(playerid, textPlayerLevel[playerid]);*/
	
	// Mostrar as necessidades e vida
	showPlayerStatus(playerid);
}

stock hideInfoTextdraws(playerid) {

	// Mostrar as informações na tela
	TextDrawHideForPlayer(playerid, textBoxInfo1);
	TextDrawHideForPlayer(playerid, textBoxInfo2);
	TextDrawHideForPlayer(playerid, textBoxInfo3);
	PlayerTextDrawHide(playerid, playerTextBoxInfo[playerid]);

	// Hud mapa
	for(new text; text != sizeof (textHud); text++) {
	    TextDrawHideForPlayer(playerid, textHud[text]);
	}

	// Barulho
    TextDrawHideForPlayer(playerid, textBarulho);

	PlayerTextDrawHide(playerid, textPlayerBarulho[0]);
	PlayerTextDrawHide(playerid, textPlayerBarulho[1]);

	// Pontuação
/*	TextDrawHideForPlayer(playerid, textPoints[0]);
	TextDrawHideForPlayer(playerid, textPoints[1]);
	PlayerTextDrawHide(playerid, playerTextPoints[playerid]);
	PlayerTextDrawHide(playerid, textPlayerLevel[playerid]);*/
	
	// Esconder as necessidades e vida
	hidePlayerStatus(playerid);
}

forward OnPlayerChangeLanguage(playerid, language[]);
public OnPlayerChangeLanguage(playerid, language[]) {

    updateTextdrawsLang(playerid);
	return 1;
}

stock updateTextdrawsLang(playerid, bool:showbutton = true) {

	if (!IsPlayerInInventory(playerid) && showbutton) {
		updateButtonMenu(playerid);
	}
}








