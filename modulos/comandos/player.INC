CMD:assobiar(playerid) {

	if (PlayerData[playerid][dDead])
		return SendLanguageMessage(playerid, corError, "MSG_029");

	static
		Float:x,
		Float:y,
		Float:z;
		
	GetPlayerPos(playerid, x, y, z);

	// Tocar o audio de assobio 3D no local
	Play3DSound(36, x, y, z, 60.0, GetPlayerVirtualWorld(playerid));

	// Atrair os zombies pro local
	FazerBarulho(x, y, z, 60.0);
	
	applyRuido(x, y, z, ALTURA_ASSOBIO, MAX_ALTURA_ASSOBIO);

	// Aplicar anim de assobiar/grito
	ApplyAnimation(playerid, "RIOT", "RIOT_shout", 4.1, 0, 1, 1, 0, 0);

	return 1;
}

CMD:radio(playerid, params[]) return cmd_r(playerid, params);
CMD:r(playerid, params[]) {

	if (IsPlayerInBattleRoyale(playerid) || !PlayerData[playerid][dSpawned])
        return SendLanguageMessage(playerid, corError, "MSG_030");

	if (!IsPlayerHaveItem(playerid, ITEM_TYPE_RADIO))
	    return SendLanguageMessage(playerid, corError, "MSG_031");

	if (gettime() < PlayerData[playerid][dMuted])
	    return SendLanguageMessagef(playerid, corError, "MSG_MUTE", PlayerData[playerid][dMuted] - gettime());

	if (sscanf(params, "s[128]", params))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/radio <texto>");

	foreach(new i : Player) {
	    if (PlayerData[i][dRadio] == PlayerData[playerid][dRadio] && IsPlayerHaveItem(i, ITEM_TYPE_RADIO)) {
	        if (IsPlayerAdminDuty(playerid)) {
	            SendClientMessagef(i, 0xFFFFBBFF, "(( Rádio: [%.1f] Administrador: %s ))", PlayerData[playerid][dRadio], params);
	        } else {
	        	SendClientMessagef(i, 0xFFFFBBFF, "(( Rádio: [%.1f] %s: %s ))", PlayerData[playerid][dRadio], getNome(playerid), params);
			}
	    }
	}
	
	new string[144];
	format(string, sizeof string, "(( [Frequência %.1f]: %s ))", PlayerData[playerid][dRadio], params);
	SendBaseRadioMessage(playerid, string, 0xFFFFBBFF);
	
	Log::("radio", "%.1f\t\t|%s: %s", PlayerData[playerid][dRadio], getNome(playerid), params);
	
	static
		Float:x,
		Float:y,
		Float:z;
		
	GetPlayerPos(playerid, x, y, z);
	
	Play3DSound(47, x, y, z, 40.0, GetPlayerVirtualWorld(playerid));
	
	applyRuido(x, y, z, ALTURA_RADIO, MAX_ALTURA_RADIO);

	return 1;
}

CMD:estacao(playerid, params[]) {

	if (!IsPlayerHaveItem(playerid, ITEM_TYPE_RADIO))
	    return SendLanguageMessage(playerid, corError, "MSG_031");

	new Float:stationradio;
	if (sscanf(params, "f", stationradio))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/estacao <89.0 - 180.0>");

	if (stationradio < 89.0 || stationradio > 180.0) {
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/estacao <89.0 - 180.0>");
	}
	
	PlayerData[playerid][dRadio] = stationradio;
	
	SendLanguageMessagef(playerid, corInfo, "MSG_032", stationradio);

	return 1;
}

CMD:id(playerid, params[]) {

	new id;
	if (sscanf(params, "u", id))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/id <parte-do-nick>");

	if (!IsPlayerConnected(id))
		return SendLanguageMessage(playerid, corError, "MSG_010");
	
	SendClientMessagef(playerid, corInfo, "ID: %d | Nome: %s", id, getNome(id));

	return 1;
}

CMD:global(playerid, params[]) return cmd_g(playerid, params);
CMD:g(playerid, params[]) {

	if (!serverGlobalChat)
	    return SendClientMessage(playerid, corError, "ERRO: {999999}O chat global está desativado!");

	if ((PlayerData[playerid][dLogged] && PlayerData[playerid][dSpawned]) || IsPlayerInBattleRoyale(playerid) || IsPlayerAdminDuty(playerid)) {

		if (gettime() < PlayerData[playerid][dMuted])
		    return SendLanguageMessagef(playerid, corError, "MSG_MUTE", PlayerData[playerid][dMuted] - gettime());

		if (sscanf(params, "s[128]", params))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/global <texto>");

		new string_text[144];
		format(string_text, sizeof (string_text), "%s{CCCCCC} %s(%d): %s", getPlayerTag(playerid), getNome(playerid), playerid, params);
/*
		format(params, 144, " %s", params);

		new string_text[144];
		format(string_text, sizeof (string_text), "%s{CCCCCC} %s(%d):%s", getPlayerTag(playerid), getNome(playerid), playerid, quote(0xCCCCCCFF, params));
*/
		foreach(new xplayer : Player) {

			if ((PlayerData[xplayer][dLogged] && PlayerData[xplayer][dSpawned]) || IsPlayerInBattleRoyale(xplayer) || IsPlayerAdminDuty(xplayer)) {
				SendClientMessage(xplayer, 0xFFFFFFFF, string_text);
			}
		}
		Log::("globalchat", "%s: %s", getNome(playerid), params);
	} else {
		SendLanguageMessage(playerid, corError, "MSG_029");
	}

	return 1;
}

CMD:v(playerid, params[]) {

	if (IsPlayerPremium(playerid)) {

		if (gettime() < PlayerData[playerid][dMuted])
		    return SendLanguageMessagef(playerid, corError, "MSG_MUTE", PlayerData[playerid][dMuted] - gettime());

		if (sscanf(params, "s[128]", params))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/v <texto>");

		new string_text[144];
		format(string_text, sizeof (string_text), "(( PREMIUM: %s(%d): %s ))", getNome(playerid), playerid, params);

		foreach(new xplayer : Player) {

			if (IsPlayerPremium(xplayer)) {
				SendClientMessage(xplayer, 0x00FFFFFF, string_text);
			}
		}
		Log::("premiumchat", "%s: %s", getNome(playerid), params);
	} else {
		SendLanguageMessage(playerid, corError, "NO_PERMISSION");
	}

	return 1;
}

CMD:gritar(playerid, params[]) return cmd_gr(playerid, params);
CMD:gr(playerid, params[]) {

	if ((PlayerData[playerid][dLogged] && PlayerData[playerid][dSpawned]) || IsPlayerInBattleRoyale(playerid) || IsPlayerAdminDuty(playerid)) {

		if (gettime() < PlayerData[playerid][dMuted])
	    	return SendLanguageMessagef(playerid, corError, "MSG_MUTE", PlayerData[playerid][dMuted] - gettime());

		if (sscanf(params, "s[128]", params))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}(/gr)ritar <texto>");

		new string_text[195];
		if (IsPlayerAdminDuty(playerid)) {
		    format(string_text, sizeof (string_text), "(( Administrador Grita: %s ))", params);
		} else {
			format(string_text, sizeof (string_text), "(( %s(%d) Grita: %s ))", getNome(playerid), playerid, params);
		}
		sendLocalMessage(playerid, string_text, 55.0, 0xFFFFFFFF);

		Log::("shout", "%s: %s", getNome(playerid), params);
	} else {
		SendLanguageMessage(playerid, corError, "MSG_029");
	}

	return 1;
}

CMD:ticket(playerid, params[])
	return cmd_suporte(playerid, params);
CMD:sos(playerid, params[])
	return cmd_suporte(playerid, params);
CMD:support(playerid, params[])
	return cmd_suporte(playerid, params);
CMD:suporte(playerid, params[]) {

	if (sscanf(params, "s[128]", params))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/suporte <mensagem>");
		
	new string[144];
	format(string, sizeof string, "(Ticket) %s(%d): %s", getNome(playerid), playerid, params);
	sendMessageToAdmins(string, 0xFF5500FF);
	
	SendLanguageMessagef(playerid, 0xFF5500FF, "MSG_101", params);
	
	Log::("tickets", "%s: %s", getNome(playerid), params);
	
	return 1;
}

CMD:report(playerid, params[]) {

	if (sscanf(params, "us[128]", params[0], params[1]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/report <id/nick> <motivo>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	new string[144];
	format(string, sizeof string, "(REPORT) %s(%d) reportou %s(%d): %s", getNome(playerid), playerid, getNome(params[0]), params[0], params[1]);
	sendMessageToAdmins(string, 0xFF5555FF);

	SendLanguageMessage(playerid, 0xFF5500FF, "MSG_102");

	Log::("report", "REPORT \t|%s reported %s: %s", getNome(playerid), getNome(params[0]), params[1]);

	return 1;
}

CMD:help(playerid)
	return cmd_ajuda(playerid);
CMD:cmds(playerid)
	return cmd_ajuda(playerid);
CMD:comandos(playerid)
	return cmd_ajuda(playerid);
CMD:ajuda(playerid) {

	stringGlobal[0] = EOS;

	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP01"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP02"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP03"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP04"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP05"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP06"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP07"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP08"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP09"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP10"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP11"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP12"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP13"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP14"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP15"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{FF7777}/dpm        \t {AAAAAA}Bloqueia/desbloqueia mensagens privadas\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP16"));strcat(stringGlobal, "\n");
	
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP17"));strcat(stringGlobal, "\n\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP18"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP19"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "HELP20"));strcat(stringGlobal, "\n");
	if (PlayerData[playerid][dAdmin]) {
	strcat(stringGlobal, "{FF7777}/ah         \t {AAAAAA}Mostra os comandos de admin\n");
	}

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation comandos:", stringGlobal, "Ok", "");

	return 1;
}

CMD:credits(playerid) return cmd_creditos(playerid);
CMD:creditos(playerid) {

	stringGlobal[0] = EOS;

    strcat(stringGlobal, "{FFFFFF}CRÉDITOS DO SERVIDOR:\n");
	strcat(stringGlobal, "{FF7777}dimmy_scarface   \t{AAAAAA}Criador do Game Mode\n");
	strcat(stringGlobal, "{FF7777}Nero_3D          \t\t{AAAAAA}Ajuda em alguns sistemas\n");
	strcat(stringGlobal, "{FF7777}Southclaw        \t\t{AAAAAA}Coordenada de varios itens\n");
	strcat(stringGlobal, "{FF7777}Andre02          \t\t{AAAAAA}Tradução para o inglês\n");
	strcat(stringGlobal, "{FF7777}GlobitoPawn      \t{AAAAAA}Tradução para o espanhol\n");
	strcat(stringGlobal, "{FF7777}SA-MP Team       \t{AAAAAA}Criadores do sa-mp\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation créditos:", stringGlobal, "Ok", "");

	return 1;
}

CMD:ajudabase(playerid) {

	stringGlobal[0] = EOS;

	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE1"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE2"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE3"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE4"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE5"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE6"));strcat(stringGlobal, "\n");
    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "BASE7"));strcat(stringGlobal, "\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation bases:", stringGlobal, "Ok", "");

	return 1;
}

CMD:dicas(playerid) {

	stringGlobal[0] = EOS;

	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA1"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA2"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA3"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA4"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA5"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA6"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA7"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "DICA8"));strcat(stringGlobal, "\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation dicas:", stringGlobal, "Ok", "");

	return 1;
}

CMD:changepassword(playerid, params[]) return cmd_trocarsenha(playerid, params);
CMD:trocarsenha(playerid, password[])
{
	if (sscanf(password, "s[144]", password))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/trocarsenha <nova senha>");
		
	// Variaveis
	new fileAccount[185];
	new SHA256_password[85];

	// Encryptar a senha
	SHA256_PassHash(password, passwordSalt, SHA256_password, sizeof (SHA256_password));
		
	format(fileAccount, sizeof fileAccount, "UPDATE accounts SET password = '%s' WHERE nome = '%s';", SHA256_password, getNome(playerid));

	db_free_result(db_query(serverDB, fileAccount));
		
	SetPVarInt(playerid, "dShowNewPass", 0);
	SetPVarString(playerid, "dNewPass", password);
	
	ShowPlayerNewPassword(playerid);
		
	return 1;
}

stock getNewPass(playerid)
{
	new string[144];
	GetPVarString(playerid, "dNewPass", string, sizeof string);
	return string;
}

stock ShowPlayerNewPassword(playerid)
{
	stringGlobal[0] = EOS;
	new string[158];
	strcat(stringGlobal, "{FFFFFF}Você trocou a senha de acesso da conta, cuidado para não perdê-la!\n\n");
	// new password
	if (GetPVarInt(playerid, "dShowNewPass")) {
	    format(string, sizeof string, "Nova senha: {FF5555}%s\n\n", getNewPass(playerid));
	} else {
		format(string, sizeof string, "Nova senha: {FF5555}***************\n\n");
	}
	strcat(stringGlobal, string);
	strcat(stringGlobal, "{FFFFFF}Tire uma foto {FF5555}F8 {FFFFFF}da nova senha, pois você não terá como recuperá-la\n");
	strcat(stringGlobal, "{FFFFFF}Fórum: {00AAFF}http://znation.brasilplaystart.com.br/forum\n");
	
	ShowPlayerDialog(playerid, DIALOG_NEWPASS, DIALOG_STYLE_MSGBOX, " ", stringGlobal, GetPVarInt(playerid, "dShowNewPass") ? ("Esconder") : ("Mostrar"), "Sair");
}

stock ShowPlayerNewPasswordAdm(playerid)
{
	stringGlobal[0] = EOS;
	new string[158];
	strcat(stringGlobal, "{FFFFFF}Você trocou a senha de acesso da conta, cuidado para não perdê-la!\n\n");
	// new password
    format(string, sizeof string, "Nova senha: {FF5555}%s\n\n", getNewPass(playerid));

	strcat(stringGlobal, string);
	strcat(stringGlobal, "{FFFFFF}Tire uma foto {FF5555}F8 {FFFFFF}da nova senha\n");
	strcat(stringGlobal, "{FFFFFF}Fórum: {00AAFF}http://znation.brasilplaystart.com.br/forum\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Sair", "");
}

CMD:premium(playerid) {

	stringGlobal[0] = EOS;

	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM1"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM2"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM3"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM4"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM5"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Ao adquirir 5 dias de premium ou mais, ganha uma skin legada do {FF0000}John Wick");strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM6"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM7"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM8"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "PREMIUM9"));strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Premium nasce com uma mochila média");strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Premium nasce com o item adrenalina");strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Premium nasce com 100 de vida");strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Premium nasce com 100 de fome");strcat(stringGlobal, "\n");
	strcat(stringGlobal, "{AAAAAA}Premium nasce com 100 de sede");strcat(stringGlobal, "\n");

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation: Conta premium:", stringGlobal, "Ok", "");

	return 1;
}

CMD:admins(playerid) {

	if (PlayerData[playerid][dAdmin] < 1)
	    return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	new countAdmins = countAdminsOnline();
	
	SendClientMessagef(playerid, corInfo, countAdmins ? ("No momento tem {FF5500}%d {FAF0CE}administradores ajudando.") : ("Não há administradores ajudando no momento."), countAdmins);
	
	if (PlayerData[playerid][dAdmin]) {
	
	    foreach(new index : Player)
		{
	        if (PlayerData[index][dAdmin] < 1 || IsPlayerAdmin(index))
	            continue;
	            
			SendClientMessagef(playerid, 0x999999FF, "%s: (%s) [%s]", getNome(index), getAdminCargoName(PlayerData[index][dAdmin]), PlayerData[index][dAdminDuty] ? ("AJUDANDO") : ("JOGANDO"));
	    }
	}
	
	return 1;
}

CMD:menu(playerid) {

	if (!PlayerData[playerid][dLogged]) {
		return SendLanguageMessage(playerid, corError, "MSG_NO_LOGGED");
	}

	if ((PlayerData[playerid][dDead] || !PlayerData[playerid][dSpawned]) && !IsPlayerAdminDuty(playerid) && !IsPlayerInBattleRoyale(playerid))
		return SendLanguageMessage(playerid, corError, "MSG_029");

	// dar kill no timer de tempo de espera
	KillTimer(GetPVarInt(playerid, "returnMenuTimer"));
		
	if (IsPlayerAdminDuty(playerid) || PlayerData[playerid][dLobby])
		SetPVarInt(playerid, "returnMenuTime", 1);
	else
	    SetPVarInt(playerid, "returnMenuTime", 31);
	
	// Mostrar o dialog
	returnMenu(playerid);
	
	return 1;
}

callback returnMenu(playerid) {

	if ((!PlayerData[playerid][dLogged] || !IsPlayerConnected(playerid) || PlayerData[playerid][dDead] || !PlayerData[playerid][dSpawned]) && !IsPlayerAdminDuty(playerid) && !IsPlayerInBattleRoyale(playerid))
	    return 0;

	SetPVarInt(playerid, "returnMenuTime", GetPVarInt(playerid, "returnMenuTime") - 1);

	new string[6];
	format(string, sizeof (string), "%d", GetPVarInt(playerid, "returnMenuTime"));

	if (!strcmp(GetPlayerLanguage(playerid), "Portugues")) {
		ShowPlayerDialog(playerid, DIALOG_RETURN_MENU, DIALOG_STYLE_MSGBOX, " ",
		"{999999}Você está prestes a retornar ao menu principal, fique ciente das regras:{FF5555}\n\n\
		× Não retornar ao menu caso esteja em combate\n\
		× Não retornar ao menu para despistar zombies\n\n\
		{999999}Aguarde o tempo para retornar ao menu...", GetPVarInt(playerid, "returnMenuTime") > 0 ? (string) : ("Retornar"), "Cancelar");
	}
	else if (!strcmp(GetPlayerLanguage(playerid), "English")) {
		ShowPlayerDialog(playerid, DIALOG_RETURN_MENU, DIALOG_STYLE_MSGBOX, " ",
		"{999999}You are about to return to the main menu, be aware of the rules:{FF5555}\n\n\
		× Do not return to the menu if you are in combat\n\
		× Do not return to menu to mislead zombies\n\n\
		{999999}Wait for the time to return to the menu...", GetPVarInt(playerid, "returnMenuTime") > 0 ? (string) : ("Return"), "Cancel");
	}
	else if (!strcmp(GetPlayerLanguage(playerid), "Espanhol")) {
		ShowPlayerDialog(playerid, DIALOG_RETURN_MENU, DIALOG_STYLE_MSGBOX, " ",
		"{999999}Vas a volver al menú principal, estar al tanto de las reglas:{FF5555}\n\n\
		× No volver al menú si está en combate\n\
		× No volver al menú para burlar los zombis\n\n\
		{999999}Esperar a que el tiempo para volver al menú...", GetPVarInt(playerid, "returnMenuTime") > 0 ? (string) : ("Regreso"), "Cancelar");
	}
	if (GetPVarInt(playerid, "returnMenuTime") > 0) {
	    SetPVarInt(playerid, "returnMenuTimer", SetTimerEx("returnMenu", 1000, false, "d", playerid));
	} else {
	    SetPVarInt(playerid, "returnMenuTimer", -1);
	}

	return 1;
}







