
CMD:a(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "s[128]", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/a <texto>");

	new level = PlayerData[playerid][dAdmin];

	new string[144];
	format(string, sizeof string, "* Admin (%s) %s: %s", getAdminCargoName(level), getNome(playerid), params[0]);
	sendMessageToAdmins(string, 0x00AAFFFF);
	
	print(string);
	
	Log::("admchat", "%s (%s): %s", getNome(playerid), getAdminCargoName(level), params[0]);

	return 1;
}

CMD:setcolor(playerid, params[])
{
	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");
		
	if (sscanf(params, "uh", params[0], params[1]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setcolor <nick-correto> <cor hexadecimal>");
		
	SetPlayerColor(params[0], params[1]);
	
	SendClientMessage(playerid, corCinza, "Cor mudada com sucesso.");
		
	return 1;
}

CMD:novasenha(playerid, params[])
{
	if (PlayerData[playerid][dAdmin] < 5)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	new account[24], password[144];
	if (sscanf(params, "s[24]s[144]", account, password))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/novasenha <nick-correto> <nova senha>");

	// Variaveis
	new fileAccount[185];
	new SHA256_password[85];

	// Encryptar a senha
	SHA256_PassHash(password, passwordSalt, SHA256_password, sizeof (SHA256_password));

	format(fileAccount, sizeof fileAccount, "UPDATE accounts SET password = '%s' WHERE nome = '%s';", SHA256_password, account);

	db_free_result(db_query(serverDB, fileAccount));

	SetPVarInt(playerid, "dShowNewPass", 0);
	SetPVarString(playerid, "dNewPass", password);

	ShowPlayerNewPasswordAdm(playerid);

	return 1;
}

CMD:getadmin(playerid)
{
	if (!IsPlayerAdmin(playerid))
	    return 1;
	    
	PlayerData[playerid][dAdmin] = 10;
	return 1;
}

CMD:avadm(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "s[128]", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/avadm <texto>");

	SendClientMessageToAllf(0x00AAFFFF, "| ADMIN AVISO | {FFFFFF}%s", params);
	
	// Mostrar aos admins
	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("adminaviso", "%s: %s", getNome(playerid), params);

	return 1;
}

CMD:limparchat(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "s[128]", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/avadm <texto>");

	for(new lines; lines < 50; lines++)
	    SendClientMessageToAll(-1, " ");

	SendClientMessageToAll(0x00AAFFFF, "| ADMIN AVISO | {FFFFFF}Chat limpo!");

	// Mostrar aos admins
	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	Log::("adminaviso", "%s: %s", getNome(playerid), params);

	return 1;
}


CMD:atrabalhoex(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (PlayerData[playerid][dAdminDuty]) {
	    PlayerData[playerid][dAdminDuty] = false;
	    SendClientMessage(playerid, corInfo, "* Você entrou em modo de jogador.");
	    // Log
     	Log::("adminduty", "%s: off duty", getNome(playerid));
	} else {
	    PlayerData[playerid][dAdminDuty] = true;
	    SendClientMessage(playerid, corInfo, "* Você entrou em modo de trabalho.");
	    // Log
	    Log::("adminduty", "%s: on duty", getNome(playerid));
	}

	// update 3d text labels
	UpdateAdminsPlayersTextLabels();

	return 1;
}

CMD:tv(playerid, params[]) return cmd_spec(playerid, params);
CMD:spec(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/spec <id/nick>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (!PlayerData[playerid][dSpectate]) {
		GetPlayerPos(playerid, PlayerData[playerid][dResyncPos][0], PlayerData[playerid][dResyncPos][1], PlayerData[playerid][dResyncPos][2]);
		GetPlayerFacingAngle(playerid, PlayerData[playerid][dResyncPos][3]);

		PlayerData[playerid][dResyncData][0] = GetPlayerInterior(playerid);
		PlayerData[playerid][dResyncData][1] = GetPlayerVirtualWorld(playerid);
	}
	
	for(new weapon; weapon < 13; weapon++)
	{
	    GetPlayerWeaponData(playerid, weapon, PlayerData[playerid][dWeapons][weapon], PlayerData[playerid][dAmmo][weapon], PlayerData[playerid][dHealth][weapon]);
	}
	
	PlayerData[playerid][dSpectate]   = true;
	PlayerData[playerid][dSpectateId] = params[0];

	TogglePlayerSpectating(playerid, true);
    PlayerData[playerid][dBaseProtect] = false;
    PlayerData[playerid][dPlayerBlocked] = false;

	if (IsPlayerInAnyVehicle(params[0])) {
	    PlayerSpectateVehicle(playerid, GetPlayerVehicleID(params[0]));
	} else {
	    PlayerSpectatePlayer(playerid, params[0]);
	}
	
	hideInfoTextdraws(playerid);
	
	PlayerTextDrawSetString(playerid, textAdminInfoSpec[playerid], "Aguardando...");
	PlayerTextDrawShow(playerid, textAdminInfoSpec[playerid]);

	if (IsPlayerAdmin(playerid) || PlayerData[playerid][dAdmin] >= 6)
	    return 1;

	// Mostrar aos admins
	new
		stringAdmin[75]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s entrou de espectador em %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	return 1;
}

CMD:desativarg(playerid) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (serverGlobalChat) {
	    serverGlobalChat = false;
	    SendLanguageMessageToAll(0xFF5555FF, "MSG_95");
	    // Log
     	Log::("globalcontrol", "%s: chat off", getNome(playerid));
	} else {
	    serverGlobalChat = true;
	    SendLanguageMessageToAll(0xFF5555FF, "MSG_96");
	    // Log
     	Log::("globalcontrol", "%s: chat on", getNome(playerid));
	}

    // Mostrar aos admins
	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	return 1;
}

CMD:specoff(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!PlayerData[playerid][dSpectate])
		return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo spectador.");

    PlayerTextDrawHide(playerid, textAdminInfoSpec[playerid]);

	TogglePlayerSpectating(playerid, false);

	if (IsPlayerAdmin(playerid) || PlayerData[playerid][dAdmin] >= 6)
	    return 1;

    // Mostrar aos admins
	new
		stringAdmin[55]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s saiu de spectador", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	return 1;
}

CMD:dpm(playerid)
{
	SetPVarInt(playerid, "p_pm", GetPVarInt(playerid, "p_pm") ? 0 : 1);
	
	SendClientMessagef(playerid, corInfo, "Mensagems privadas: %s", GetPVarInt(playerid, "p_pm") ? ("OFF") : ("ON"));

	return 1;
}

CMD:par(playerid, params[]) return cmd_pm(playerid, params);
CMD:pm(playerid, params[]) {

//	if (PlayerData[playerid][dAdmin] < 1)
//		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

//	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
//      return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "us[128]", params[0], params[1]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/pm <id/nick> <texto>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

    new string[128];

	if (PlayerData[playerid][dAdmin] > 0)
	{
	    SendClientMessagef(playerid, 0xFFFF00FF, "[PM] %s » %s: %s", getNome(playerid), getNome(params[0]), params[1]);

	    if (PlayerData[params[0]][dAdmin] > 0)
	    {
	        SendClientMessagef(params[0], 0xFFFF00FF, "[PM] » %s: %s", getNome(playerid), params[1]);
	    } else {
			SendClientMessagef(params[0], 0xFFFF00FF, "[PM] » administrador: %s", params[1]);
		}

		if (GetPVarInt(params[0], "lastContact") == INVALID_PLAYER_ID) {
			SetPVarInt(params[0], "lastContact", playerid);
			SendLanguageMessage(params[0], 0xFF5500FF, "MSG_97");

			format(string, sizeof string, "Admin %s atendeu o jogador %s", getNome(playerid), getNome(params[0]));
			sendMessageToAdmins(string, 0x00AA00FF);
		}
	} else {
	
		if (GetPVarInt(playerid, "p_pm"))
		    return SendClientMessage(playerid, corError, "ERROR: {888888}Você deve ativar suas mensagens privadas para enviar uma.");
	
		if (GetPVarInt(params[0], "p_pm"))
		    return SendClientMessage(playerid, corError, "ERROR: {888888}Este jogador bloqueou as mensagens privadas.");
		    
		SendClientMessagef(playerid, 0x00AA00FF, "(PM) Enviada para %s: %s", getNome(params[0]), params[1]);
		SendClientMessagef(params[0], 0x00AA00FF, "(PM) Recebida de %s: %s", getNome(playerid), params[1]);
	}
	
	format(string, sizeof string, "[PM] %s > %s: %s", getNome(playerid), getNome(params[0]), params[1]);
	foreach(new p : Player)
	{
	    if (p == playerid) continue;
		if (IsPlayerAdmin(p))
		{
		    SendClientMessage(p, 0x00FFFFFF, string);
		}
	}
	
    // Mostrar aos admins
    /*
	new
		stringAdmin[120]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s enviou uma mensagem privada para %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);*/
	
	Log::("pm", "%s > %s: %s", getNome(playerid), getNome(params[0]), params[1]);

	return 1;
}

CMD:re(playerid, params[]) {

	if (sscanf(params, "s[128]", params[1]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/re <texto>");

	new adminid = GetPVarInt(playerid, "lastContact");

	if (adminid == INVALID_PLAYER_ID)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerConnected(adminid))
		return SendLanguageMessage(playerid, corError, "MSG_010");

    SendClientMessagef(playerid, 0xFFFF00FF, "[PM] %s » administrador: %s", getNome(playerid), params[1]);
	SendClientMessagef(adminid, 0xFFFF00FF, "[PM] » %s: %s", getNome(playerid), params[1]);

	new string[128];
	format(string, sizeof string, "[RE] %s > %s: %s", getNome(playerid), getNome(adminid), params[1]);
	foreach(new p : Player)
	{
	    if (p == playerid) continue;
		if (IsPlayerAdmin(p))
		{
		    SendClientMessage(p, 0x00FFFFFF, string);
		}
	}

    Log::("pm", "%s > %s: %s", getNome(playerid), getNome(adminid), params[1]);

	return 1;
}

CMD:finalizarsup(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "u", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/finalizarsup <id/nick>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	new adminid = GetPVarInt(params[0], "lastContact");

	if (adminid != playerid)
		return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está atendendo este jogador.");

    SendClientMessagef(playerid, corInfo, "Você finalizou o atendimento com %s.", getNome(params[0]));
	SendLanguageMessage(params[0], corInfo, "MSG_98");
	
	SetPVarInt(params[0], "lastContact", INVALID_PLAYER_ID);

	new
		stringAdmin[120]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s finalizou o atendimento com %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0x00AA00FF);

    Log::("endsupport", "%s > %s", getNome(playerid), getNome(params[0]));

	return 1;
}

CMD:veh(playerid, params[]) return cmd_vehicle(playerid, params);
CMD:vehicle(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new vehicle, color1, color2;
	if (sscanf(params, "ddd", vehicle, color1, color2))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/vehicle <modelo> <cor1> <cor2>");

	if (vehicle < 400 || vehicle > 610)
	    return SendLanguageMessage(playerid, corError, "MSG_001");

	if ((color1 < -1 || color1 > 255) || (color2 < -1 || color2 > 255))
	    return SendLanguageMessage(playerid, corError, "MSG_002");

	static Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	createNewVehicleLoot(vehicle, x, y + 1.5, z, 0.0, color1, color2);
	
	new
		stringAdmin[75]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s criou um veiculo do modelo %d", getNome(playerid), vehicle);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("createvehicle", "%s\t\t|vehicle %d color %d %d", getNome(playerid), vehicle, color1, color2);
	
	return 1;
}

CMD:destruirveiculo(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 5)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new vehicle = GetPlayerClossestVehicle(playerid);

	if (vehicle != INVALID_VEHICLE_ID)
	{
        DestroyServerVehicle(vehicle);

		new
			stringAdmin[75]
			;
		format(stringAdmin, sizeof stringAdmin, "Admin %s destruiu o veiculo %d", getNome(playerid), vehicle);
		sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

		Log::("destroyvehicle", "%s\t\t|vehicle %d", getNome(playerid), vehicle);
	} else {
	    SendClientMessage(playerid, corError, "ERRO: {999999}Você não está próximo de nenhum veículo.");
	}

	return 1;
}


CMD:reconstruirveiculos(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/reconstruirveiculos <maximo de carros (100 - 900)>");

	if (params[0] < 100 || params[0] > 900)
	    return SendLanguageMessage(playerid, corError, "MSG_001");

	remakeVehiclesServer(.maxrandom = params[0]);
	
	SendClientMessage(playerid, corInfo, "Você deu remake em todos os veículos do servidor.");

	new
		stringAdmin[120]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s reconstruiu os veículos com %d unidades", getNome(playerid), params[0]);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	Log::("remakevehicles", "%s\t\t|amount: %d", getNome(playerid), params[0]);

	return 1;
}

CMD:vehiclehealth(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new vehicle, Float:health;
	if (sscanf(params, "f", health))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/vehiclehealth <vida>");

	vehicle = GetPlayerVehicleID(playerid);

	if (!IsValidVehicle(vehicle))
	    return SendLanguageMessage(playerid, corError, "MSG_003");

	SetVehicleHealth(vehicle, health);
	
	SendLanguageMessagef(playerid, corInfo, "MSG_004", health);

	new
		stringAdmin[120]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s setou %.1f de vida para o veiculo %d", getNome(playerid), health, vehicle);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("vehiclehealth", "%s\t\t|vehicle %d set to health %f", getNome(playerid), vehicle, health);

	return 1;
}

CMD:temporestart(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/temporestart <minutos>");

	if (params[0] < 1)
	    return SendLanguageMessage(playerid, corError, "MSG_005");

    serverRestartTime = (params[0] * 60);
    
    SendLanguageMessagef(playerid, corInfo, "MSG_006", ConvertTime(params[0] * 60));

	new
		stringAdmin[95]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s setou o tempo de restart para %d minutos", getNome(playerid), params[0]);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("restarttime", "%s\t\t|restart server set to %s", getNome(playerid), ConvertTime(params[0] * 60));

	return 1;
}

CMD:irbase(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0]) || (params[0] < 0 || params[0] >= MAX_BASES))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/irbase <id válido>");

	new Float:x, Float:y, Float:z;
	
	if (!GetBaseArmarioPos(params[0], x, y, z))
	    return SendClientMessage(playerid, corError, "ERRO: {999999}Id de base inexistente.");

	SetPlayerPos(playerid, x, y, z, .freezetime = 3000);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	
	SendClientMessagef(playerid, corInfo, "Você foi até a base id: %d", params[0]);

	new
		stringAdmin[65]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s foi até a base %d", getNome(playerid), params[0]);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("gotobase", "%s\t\t|base id %d", getNome(playerid), params[0]);

	return 1;
}

CMD:destruirbase(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 6)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0]) || (params[0] < 0 || params[0] >= MAX_BASES))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/destruirbase <id válido>");

    if (serverBaseDestroy(params[0])) {

		SendClientMessagef(playerid, corInfo, "Você destruiu a base id: %d", params[0]);

		new
			stringAdmin[120]
			;
		format(stringAdmin, sizeof stringAdmin, "Admin %s destruiu a base %d", getNome(playerid), params[0]);
		sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    	Log::("destroybase", "%s\t\t|base id %d", getNome(playerid), params[0]);
	} else {
	    SendClientMessage(playerid, corError, "ERRO: {999999}Id de base inexistente.");
	}

	return 1;
}

CMD:npcupdate(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "dd", params[0], params[1]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/npcupdate <tickrate> <updaterate>");

    FCNPC_SetTickRate(params[0]);
    FCNPC_SetUpdateRate(params[1]);

	return 1;
}

CMD:clientupdate(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "d", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/clientupdate <tickrate>");

    clientTickUpdate = params[0];

	return 1;
}

CMD:gmx(playerid) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

    serverRestartTime = 1;

    SendLanguageMessageToAll(0xFF5500FF, "MSG_99");

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("gmx", "%s\t\t|restart server", getNome(playerid));

	return 1;
}


CMD:irpos(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	SubDel(params, ",");

	new Float:pos[3];
	if(sscanf(params, "fff", pos[0], pos[1], pos[2])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/irpos <x> <y> <z>");
	}
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SendLanguageMessagef(playerid, corInfo, "MSG_007", pos[0], pos[1], pos[2]);
	
	Log::("gotopos", "%s\t\t|x %f y %f z %f", getNome(playerid), pos[0], pos[1], pos[2]);
	
	return 1;
}

CMD:irposex(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new interior, Float:pos[3];
	if(sscanf(params, "dfff", interior, pos[0], pos[1], pos[2])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/irpos <interior> <x> <y> <z>");
	}
	SetPlayerInterior(playerid, interior);
	SetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	SendLanguageMessagef(playerid, corInfo, "MSG_007", pos[0], pos[1], pos[2]);

	Log::("gotopos", "%s\t\t|x %f y %f z %f", getNome(playerid), pos[0], pos[1], pos[2]);

	return 1;
}

CMD:mutar(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "uds[128]", params[0], params[1], params[2]) || (params[1] < 0 || params[1] > 999)) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/mutar <id/nick> <minutos (0 - 999)> <motivo>");
	}

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	PlayerData[params[0]][dMuted] = gettime() + (params[1] * 60);
	SendLanguageMessageToAllf(corCinza, "MSG_100", getNome(params[0]), params[1], params[2]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("mute", "%s\t\t|mute %d mins %s, reason: %s", getNome(playerid), params[1], getNome(params[0]), params[2]);

	return 1;
}

CMD:bloquear(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "uds[128]", params[0], params[1], params[2]) || (params[1] < 0 || params[1] > 999)) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/bloquear <id/nick> <minutos (0 - 999)> <motivo>");
	}

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	PlayerData[params[0]][dBlockedTime] = (params[1] * 60);
	SendLanguageMessageToAllf(corCinza, "MSGBLOCK", getNome(params[0]), params[1], params[2]);

    returnPlayerMenu(params[0]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("block", "%s\t\t|has blocked %s for %d mins, reason: %s", getNome(playerid), getNome(params[0]), params[1], params[2]);

	return 1;
}


CMD:setmadeira(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "ud", params[0], params[1])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setmadeira <id> <quantidade>");
	}
	
	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");
	
	AddQuantiaItem(params[0], ITEM_TYPE_MADEIRA, params[1]);
	
	SendClientMessagef(playerid, corInfo, "Você setou %d de madeiras para o jogador %s.", params[1], getNome(params[0]));
	SendClientMessagef(params[0], corInfo, "Um administrador setou %d de madeiras para você.", params[1]);

	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s setou %d madeiras para %s", getNome(playerid), params[1], getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("setwood", "%s\t\t|give %d wood to %s", getNome(playerid), params[1], getNome(params[0]));

	return 1;
}

CMD:setrocha(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "ud", params[0], params[1])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setrocha <id> <quantidade>");
	}

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

    AddQuantiaItem(params[0], ITEM_TYPE_ROCHA, params[1]);
	SendClientMessagef(playerid, corInfo, "Você setou %d de rochas para o jogador %s.", params[1], getNome(params[0]));
	SendClientMessagef(params[0], corInfo, "Um administrador setou %d de rochas para você.", params[1]);
	
	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s setou %d rochas para %s", getNome(playerid), params[1], getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("setstone", "%s\t\t|give %d stones to %s", getNome(playerid), params[1], getNome(params[0]));

	return 1;
}

CMD:setmetal(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "ud", params[0], params[1])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setmetal <id> <quantidade>");
	}

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	AddQuantiaItem(params[0], ITEM_TYPE_METAL, params[1]);
	SendClientMessagef(playerid, corInfo, "Você setou %d de metal para o jogador %s.", params[1], getNome(params[0]));
	SendClientMessagef(params[0], corInfo, "Um administrador setou %d de metal para você.", params[1]);
	
	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s setou %d metais para %s", getNome(playerid), params[1], getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("setmetal", "%s\t\t|give %d metal to %s", getNome(playerid), params[1], getNome(params[0]));

	return 1;
}

CMD:setint(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if(sscanf(params, "d", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setint <id>");
	}
	SetPlayerInterior(playerid, params[0]);
	SendClientMessagef(playerid, corInfo, "Interior modificado para: %d", params[0]);
	return 1;
}

CMD:world(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if(sscanf(params, "d", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/world <id>");
	}
	SetPlayerVirtualWorld(playerid, params[0]);
	SendLanguageMessagef(playerid, corInfo, "MSG_008", params[0]);
	return 1;
}

CMD:jetpack(playerid) {

	if (PlayerData[playerid][dAdmin] < 5)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	SendLanguageMessage(playerid, corInfo, "MSG_009");
	
	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s pegou um jetpack", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	return SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USEJETPACK);
}

CMD:dararma(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "udd", params[0], params[1], params[2]) || (params[1] < 1 || params[1] > 46)) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/dararma <id> <arma (1 - 46)> <municao>");
	}

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	SendLanguageMessagef(playerid, corInfo, "MSG_011", NomeArma(params[1]), params[2], getNome(params[0]));
	SendLanguageMessagef(params[0], corInfo, "MSG_012", NomeArma(params[1]), params[2]);

	GivePlayerWeapon(params[0], params[1], params[2]);

	if (IsPlayerNPC(params[0])) {
	    FCNPC_SetWeapon(params[0], params[1]);
	    FCNPC_SetAmmo(params[0], params[2]);
	}
	
	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s deu a arma %s com %d munições para %s", getNome(playerid), NomeArma(params[1]), params[2], getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("giveweapon", "%s\t\t|give a weapon %d with %d ammo to %s", getNome(playerid), params[1], params[2], getNome(params[0]));
	return 1;
}

CMD:clima(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");
        
	if (sscanf(params, "dd", params[0], params[1])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/clima <hora> <tempo>");
	}
	ForceGlobalWorldTime(params[0]);
	ForceGlobalWeather(params[1]);
	
	serverCurrentWeather = params[1];
	
	SendLanguageMessageToAllf(corInfo, "MSG_013", params[0], params[1]);
	
	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("wather", "%s\t\t|changed to hour %d wather %d", getNome(playerid), params[0], params[1]);
	return 1;
}

CMD:trazer(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/trazer <id/nick>");
	}

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	new Float:pos[3], vehicleid;
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if (IsPlayerInAnyVehicle(params[0])) {
        vehicleid = GetPlayerVehicleID(params[0]);
        SetVehiclePos(vehicleid, pos[0], pos[1]+1, pos[2]);
        SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
        LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
	} else {
		SetPlayerPos(params[0], pos[0], pos[1]+1, pos[2]);
	}
	SetPlayerInterior(params[0], GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));

	SendLanguageMessagef(playerid, corInfo, "MSG_014", getNome(params[0]));
	SendLanguageMessage(params[0], corInfo, "MSG_015");

	if(IsPlayerNPC(params[0])) {
		FCNPC_SetPosition(params[0], pos[0], pos[1], pos[2]);
		FCNPC_SetInterior(params[0], GetPlayerInterior(playerid));
	}
	
	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s levou %s até sua posição", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	return 1;
}

CMD:irveh(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/irveh <id>");
	}
	
	if (!IsValidVehicle(params[0]))
	    return SendClientMessage(playerid, corCinza, "Veículo inválido!");

	new Float:pos[3], vehicleid;
	GetVehiclePos(params[0], pos[0], pos[1], pos[2]);

	if (IsPlayerInAnyVehicle(playerid)) {
        vehicleid = GetPlayerVehicleID(playerid);
        SetVehiclePos(vehicleid, pos[0], pos[1]+1, pos[2]);
	} else {
		SetPlayerPos(playerid, pos[0], pos[1]+1, pos[2]);
	}

	SendClientMessagef(playerid, corCinza, "Voce foi até o veículo id: %d", params[0]);

	return 1;
}

CMD:trazerveh(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 5)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/trazerveh <id>");
	}

	if (!IsValidVehicle(params[0]))
	    return SendClientMessage(playerid, corCinza, "Veículo inválido!");

	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

    SetVehiclePos(params[0], pos[0], pos[1]+1, pos[2]);
    
    SaveVehicleInfo(params[0]);

	SendClientMessagef(playerid, corCinza, "Voce puxou o veículo: %d", params[0]);

	return 1;
}

CMD:destrancarveiculo(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 5)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "d", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/destrancarveiculo <id>");
	}

	if (!IsValidVehicle(params[0]))
	    return SendClientMessage(playerid, corCinza, "Veículo inválido!");

	if (VehicleInfo[params[0]][vehLocked])
 	{
  		UnlockVehicle(params[0]);
    	SendServerMessageToPlayer(playerid, "O veiculo foi destrancado");
    } else
    {
    	LockVehicle(params[0]);
     	SendServerMessageToPlayer(playerid, "O veiculo foi trancado");
  	}
   	PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);

    SaveVehicleInfo(params[0]);

	return 1;
}

CMD:ir(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/ir <id/nick>");
	}

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	new Float:pos[3], vehicleid;
	GetPlayerPos(params[0], pos[0], pos[1], pos[2]);

	if(IsPlayerNPC(params[0])) {
		FCNPC_GetPosition(params[0], pos[0], pos[1], pos[2]);
	}

	if (IsPlayerInAnyVehicle(playerid)) {
        vehicleid = GetPlayerVehicleID(playerid);
        SetVehiclePos(vehicleid, pos[0], pos[1]+1, pos[2]);
        SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(params[0]));
        LinkVehicleToInterior(vehicleid, GetPlayerInterior(params[0]));
	} else {
		SetPlayerPos(playerid, pos[0], pos[1]+1, pos[2]);
	}
	SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));

	SendLanguageMessagef(playerid, corInfo, "MSG_016", getNome(params[0]));
	SendLanguageMessage(params[0], corInfo, "MSG_017");

	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s foi até a posição de %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	return 1;
}

CMD:ip(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0])) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/ip <id/nick>");
	}

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerAdmin(params[0]))
	    return SendClientMessage(playerid, corCinza, "Você não pode ver o ip de um cheater supremo.");

	SendClientMessagef(playerid, 0xFF5500FF, "Nick: %s | IP: %s", getNome(params[0]), getIp(params[0]));

	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s checou o ip de %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	return 1;
}


CMD:getposition(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	static
		Float:pos[3], npcid
		;

	if (sscanf(params, "u", npcid)) {
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/getposition <id>");
	}

	FCNPC_GetPosition(npcid, pos[0], pos[1], pos[2]);

	SetPlayerCheckpoint(playerid, pos[0], pos[1], pos[2], 1.0);

	return 1;
}


CMD:explodir(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "ud", params[0], params[1]) || (params[1] < 0 || params[1] > 10))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/explodir <id> <tipo da explosao (0 - 10)>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerAdmin(params[0]))
	    return SendClientMessage(playerid, corCinza, "Você não pode explodir um cheater supremo.");

	new Float:pos[3];

	if (IsPlayerNPC(params[0])) {
		FCNPC_GetPosition(params[0], pos[0], pos[1], pos[2]);
	} else {
	    GetPlayerPos(params[0], pos[0], pos[1], pos[2]);
	}
	CreateExplosion(pos[0], pos[1], pos[2], params[1], 1.0);

	SendLanguageMessagef(playerid, corInfo, "MSG_018", getNome(params[0]));
	SendLanguageMessage(params[0], corInfo, "MSG_019");

	new
		stringAdmin[75]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s explodiu %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("explode", "%s\t\t|exploded %s", getNome(playerid), getNome(params[0]));

	return 1;
}

CMD:darvida(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 4)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new Float:health;

	if (sscanf(params, "uf", params[0], health) || (health < 0.0 || health > 100.0))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/darvida <id> <quantia (1.0 - 100.0)>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerNPC(params[0])) {
		FCNPC_SetHealth(params[0], health);
	} else {
	    SetHealthPlayer(params[0], health);
	}

	SendLanguageMessagef(playerid, corInfo, "MSG_020", health, getNome(params[0]));
	SendLanguageMessagef(params[0], corInfo, "MSG_021", health);

	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s deu %.1f de vida para %s", getNome(playerid), health, getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("sethealth", "%s\t\t|set %f health to %s", getNome(playerid), health, getNome(params[0]));

	return 1;
}

CMD:darcashoff(playerid, params[]) {

	if (!strcmp(getNome(playerid), "dimmy_scarface") || !strcmp(getNome(playerid), "Theus_Crazzy"))
	{
		new coins, name[MAX_PLAYER_NAME];

		if (sscanf(params, "s[24]d", name, coins))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/darcashoff <nick> <quantia (1 - 50000)>");

		if (coins < 1 || coins > 50000)
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/darcashoff <nick> <quantia (1 - 50000)>");

		new
			stringAdmin[90]
			;

		if (getId(name) == INVALID_PLAYER_ID)
		{
		    if (!isNickRegistered(name))
		        return SendClientMessage(playerid, corError, "ERRO: {999999}Nome não encontrado no banco de dados.");
		        
		    new query[128];
		    format(query, sizeof query, "UPDATE accounts SET `coins` = `coins` + %d WHERE nome = '%s';", coins, name);
		    db_free_result(db_query(serverDB, query));
		
			format(stringAdmin, sizeof stringAdmin, "Admin %s deu %d de cash para %s", getNome(playerid), coins, name);
			sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

		    Log::("givecash", "%s\t\t|give %d cash to %s", getNome(playerid), coins, name);
			return 1;
		} else {
		    SendClientMessage(playerid, corError, "ERRO: {999999}Este jogador está conectado, use /darcash.");
		}
	}

	return 1;
}

CMD:setcashoff(playerid, params[]) {

	if (!strcmp(getNome(playerid), "dimmy_scarface") || !strcmp(getNome(playerid), "Theus_Crazzy"))
	{
		new coins, name[MAX_PLAYER_NAME];

		if (sscanf(params, "s[24]d", name, coins))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setcashoff <nick> <quantia (1 - 50000)>");

		if (coins < 1 || coins > 50000)
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setcashoff <nick> <quantia (1 - 50000)>");

		new
			stringAdmin[90]
			;

		if (getId(name) == INVALID_PLAYER_ID)
		{
		    if (!isNickRegistered(name))
		        return SendClientMessage(playerid, corError, "ERRO: {999999}Nome não encontrado no banco de dados.");

		    new query[128];
		    format(query, sizeof query, "UPDATE accounts SET `coins` = %d WHERE nome = '%s';", coins, name);
		    db_free_result(db_query(serverDB, query));

			format(stringAdmin, sizeof stringAdmin, "Admin %s setou %d de cash para %s", getNome(playerid), coins, name);
			sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

		    Log::("givecash", "%s\t\t|set %d cash to %s", getNome(playerid), coins, name);
			return 1;
		} else {
		    SendClientMessage(playerid, corError, "ERRO: {999999}Este jogador está conectado, use /darcash.");
		}
	}

	return 1;
}

CMD:setadminoff(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] >= 6)
	{
		new level, name[MAX_PLAYER_NAME];

		if (sscanf(params, "s[24]d", name, level) || (level < 0 || level > 10))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setadminoff <nick> <0 - 10>");
			
		if (level > PlayerData[playerid][dAdmin])
		    return SendClientMessage(playerid, -1, "Você não pode setar um nível maior que o seu.");

		new
			stringAdmin[90]
			;

		if (getId(name) == INVALID_PLAYER_ID)
		{
		    if (!isNickRegistered(name))
		        return SendClientMessage(playerid, corError, "ERRO: {999999}Nome não encontrado no banco de dados.");

		    new query[128];
		    format(query, sizeof query, "UPDATE accounts SET `admin` = %d WHERE nome = '%s';", level, name);
		    db_free_result(db_query(serverDB, query));

			format(stringAdmin, sizeof stringAdmin, "Admin %s setou admin level %d para %s", getNome(playerid), level, name);
			sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

		    Log::("givecash", "%s\t\t|set %d cash to %s", getNome(playerid), level, name);
			return 1;
		} else {
		    SendClientMessage(playerid, corError, "ERRO: {999999}Este jogador está conectado, use /daradmin.");
		}
	}

	return 1;
}

CMD:infoadmins(playerid)
{
	if (PlayerData[playerid][dAdmin] >= 1)
	{
	    new DBResult:result = db_query(serverDB, "SELECT * FROM accounts WHERE admin > 0 LIMIT 30");
	    
	    new count_rows = db_num_rows(result);
	    
	    if (count_rows)
	    {
	        stringGlobal[0] = EOS;
	        new string[128];
	        
	        strcat(stringGlobal, "Nome do admin\tLevel de admin\n");
	        
	        for(new idx; idx < count_rows; idx++)
	        {
				format(string, sizeof string, "%s\t{00AA00}%d\n", sql_getstring(result, "nome"), sql_getint(result, "admin"));
				strcat(stringGlobal, string);
				db_next_row(result);
	        }
	        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Lista de {00AA00}Administradores", stringGlobal, "Informado", "");
	    } else {
	        SendClientMessage(playerid, corError, "ERRO: {999999}Nenhum admin encontrado na base de dados.");
	    }
	    db_free_result(result);
	}
	return 1;
}


CMD:darcash(playerid, params[]) {

	//if (PlayerData[playerid][dAdmin] < 10)
		//return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!strcmp(getNome(playerid), "dimmy_scarface") || !strcmp(getNome(playerid), "Theus_Crazzy"))
	{
		//if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
	        //return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

		new coins;

		if (sscanf(params, "ud", params[0], coins) || (coins < 1 || coins > 50000))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/darcash <id> <quantia (1 - 50000)>");

		if (!IsPlayerConnected(params[0]))
			return SendLanguageMessage(playerid, corError, "MSG_010");

		GivePlayerCoins(params[0], coins);

		SendLanguageMessagef(playerid, corInfo, "MSG_076", coins, getNome(params[0]));
		SendLanguageMessagef(params[0], corInfo, "MSG_077", coins);

		new
			stringAdmin[90]
			;
		format(stringAdmin, sizeof stringAdmin, "Admin %s deu %d de cash para %s", getNome(playerid), coins, getNome(params[0]));
		sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	    Log::("givecash", "%s\t\t|give %d cash to %s", getNome(playerid), coins, getNome(params[0]));
	}

	return 1;
}

CMD:fjdshfsbg(playerid, params[]) {

	//if (PlayerData[playerid][dAdmin] < 10)
		//return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

		//if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
	        //return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new coins;

	if (sscanf(params, "ud", params[0], coins) || (coins < 1 || coins > 50000))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/darcash <id> <quantia (1 - 50000)>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	GivePlayerCoins(params[0], coins);

	SendLanguageMessagef(playerid, corInfo, "MSG_076", coins, getNome(params[0]));
	SendLanguageMessagef(params[0], corInfo, "MSG_077", coins);

  	Log::("givecash", "%s\t\t|give %d cash to %s", getNome(playerid), coins, getNome(params[0]));

	return 1;
}


CMD:setarcash(playerid, params[]) {

//	if (PlayerData[playerid][dAdmin] < 10)
	//	return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

//	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
     //   return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (!strcmp(getNome(playerid), "dimmy_scarface") || !strcmp(getNome(playerid), "Theus_Crazzy"))
	{
		new coins;

		if (sscanf(params, "ud", params[0], coins) || (coins < 0 || coins > 50000))
			return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/setarcash <id> <quantia (0 - 50000)>");

		if (!IsPlayerConnected(params[0]))
			return SendLanguageMessage(playerid, corError, "MSG_010");

		PlayerData[params[0]][dCoins] = coins;

		SendLanguageMessagef(playerid, corInfo, "MSG_078", coins, getNome(params[0]));
		SendLanguageMessagef(params[0], corInfo, "MSG_079", coins);

		new
			stringAdmin[90]
			;
		format(stringAdmin, sizeof stringAdmin, "Admin %s setou %d de cash para %s", getNome(playerid), coins, getNome(params[0]));
		sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	    Log::("setcash", "%s\t\t|set %d cash to %s", getNome(playerid), coins, getNome(params[0]));
	}

	return 1;
}

CMD:daradmin(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 6 && !IsPlayerAdmin(playerid))
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	new level;

	if (sscanf(params, "ud", params[0], level) || (level < 0 || level > 10))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/daradmin <id> <level (0 - 10)>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (level > PlayerData[playerid][dAdmin] && !IsPlayerAdmin(playerid))
		return SendClientMessage(playerid, corError, "ERRO: {999999}Você não pode setar um nível maior que o seu!");

	PlayerData[params[0]][dAdmin] = level;

	SendLanguageMessagef(playerid, corInfo, "MSG_022", getAdminCargoName(level), getNome(params[0]));
	SendLanguageMessagef(params[0], corInfo, "MSG_023", getNome(playerid), getAdminCargoName(level));

	if (level)
	    checkPlayerConquista(params[0], Conquista_Admin);

	if (IsPlayerAdmin(playerid))
	    return 1;

	new
		stringAdmin[90]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s deu admin level %s para %s", getNome(playerid), getAdminCargoName(level), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("setadmin", "%s\t\t|became %s admin level %d", getNome(playerid), getNome(params[0]), level);

	return 1;
}


CMD:setbetatester(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10 && !IsPlayerAdmin(playerid))
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new level;

	if (sscanf(params, "ud", params[0], level) || (level < 0 || level > 1))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/daradmin <id> <level (0 - 1)>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	PlayerData[params[0]][dBetaTester] = bool:level;

    SendClientMessagef(playerid, corInfo, "Você tornou %s um Beta-Tester nível: %d", getNome(params[0]), level);
	SendClientMessagef(params[0], corInfo, "Um administrador tornou você Beta-Tester nível: %d", level);

	if (level)
	    checkPlayerConquista(params[0], Conquista_BetaTester);

    Log::("setbetatester", "%s\t\t|tornou %s beta tester level %d", getNome(playerid), getNome(params[0]), level);

	return 1;
}

CMD:testetext(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "hs[128]", params[0], params[1]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/testetext <color> <texto>");

	SendLanguageMessage(playerid, params[0], params[1]);

	return 1;
}

CMD:select(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "h", params[0]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/select <color>");

	SelectTextDraw(playerid, params[0]);

	return 1;
}

CMD:ban(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "us[128]", params[0], params[1]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/ban <id/nick> <motivo>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (!PlayerData[params[0]][dLogged])
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerAdmin(params[0]))
	    return SendClientMessage(playerid, corCinza, "Você não pode banir um cheater supremo.");

	SendLanguageMessageToAllf(corCinza, "MSG_BAN", getNome(params[0]), params[1]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    banAccount(getNome(params[0]), getIp(params[0]), getNome(playerid), params[1], gettime() + (30 * 86400));

	Kick(params[0]);

    Log::("ban", "%s\t\t|ban %s reason %s", getNome(playerid), getNome(params[0]), params[1]);

	return 1;
}

CMD:banoff(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new nick[24], motivo[128];

	if (sscanf(params, "s[128]s[128]", nick, motivo))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/banoff <nick> <motivo>");

	if (isAccoundBanned(nick))
		return SendLanguageMessage(playerid, corError, "ALREADY_BAN");

	if (getId(nick) != INVALID_PLAYER_ID)
		return SendLanguageMessage(playerid, corError, "CONNECTED");

	SendLanguageMessageToAllf(corCinza, "MSG_BAN_OFF", nick, motivo);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    banAccount(nick, "0.0.0.0", getNome(playerid), motivo, gettime() + (30 * 86400));

    Log::("banoff", "%s\t\t|ban account %s reason %s", getNome(playerid), nick, motivo);

	return 1;
}

CMD:tempbanoff(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new nick[128], dias, motivo[128];

	if (sscanf(params, "ds[128]s[128]", dias, nick, motivo))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/tempbanoff <dias> <nick> <motivo>");

	if (isAccoundBanned(nick))
		return SendLanguageMessage(playerid, corError, "ALREADY_BAN");

	if (getId(nick) != INVALID_PLAYER_ID)
		return SendLanguageMessage(playerid, corError, "CONNECTED");

	SendLanguageMessageToAllf(corCinza, "MSG_TEMP_BAN", nick, dias, motivo);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    banAccount(nick, "0.0.0.0", getNome(playerid), motivo, gettime() + (dias * 86400));

    Log::("tempbanoff", "%s\t\t|ban account %s for %d days, reason %s", getNome(playerid), nick, dias, motivo);

	return 1;
}


CMD:tempban(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "uds[128]", params[0], params[1], params[2]) || (params[1] < 1 || params[1] > 120))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/tempban <id/nick> <dias (1 - 120)> <motivo>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (!PlayerData[params[0]][dLogged])
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerAdmin(params[0]))
	    return SendClientMessage(playerid, corCinza, "Você não pode banir um cheater supremo.");

	SendLanguageMessageToAllf(corCinza, "MSG_TEMP_BAN", getNome(params[0]), params[1], params[2]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    banAccount(getNome(params[0]), getIp(params[0]), getNome(playerid), params[2], gettime() + (params[1] * 86400));

	Kick(params[0]);

    Log::("tempban", "%s\t\t|ban %s of %d days reason %s", getNome(playerid), getNome(params[0]), params[1], params[2]);

	return 1;
}

CMD:kick(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "us[128]", params[0], params[1]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/kick <id/nick> <motivo>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	if (IsPlayerAdmin(params[0]))
	    return SendClientMessage(playerid, corCinza, "Você não pode kickar um cheater supremo.");

	SendLanguageMessageToAllf(corCinza, "MSG_KICK", getNome(params[0]), params[1]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Kick conta

	Kick(params[0]);
	
	Log::("kick", "%s\t\t|kicked %s reason %s", getNome(playerid), getNome(params[0]), params[1]);

	return 1;
}

CMD:kickgrupo(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new groupname[75], motivo[128];

	if (sscanf(params, "s[75]s[128]", groupname, motivo))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/kickgrupo <nome-do-grupo> <motivo>");

	if (!isNameServerGroupExist(groupname))
	    return SendLanguageMessage(playerid, corError, "GP_24");

	SendLanguageMessageToAllf(corCinza, "MSG_KICKG", groupname, motivo);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Kick grupo

	kickGroup(groupname);
	
	Log::("kickgroup", "%s\t\t|kick group %s reason %s", getNome(playerid), groupname, motivo);

	return 1;
}

CMD:desban(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/desban <nick>");

	if (!isAccoundBanned(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_026");

	SendLanguageMessageToAllf(corCinza, "MSG_DESBAN", params[0]);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    unbanAccount(params[0]);
    
    Log::("unban", "%s\t\t|unban %s", getNome(playerid), params[0]);

	return 1;
}

CMD:desbanip(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 3)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 5)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "s[128]", params[0]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/desbanip <ip>");

	if (!isIpBanned(params[0]))
		return SendLanguageMessage(playerid, corError, "IP_BAN");

	new message[128];
	format(message, sizeof message, "MSG_DESBAN_IP", params[0]);
	sendMessageToAdmins(message, corCinza);

	new
		stringAdmin[45]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin: %s", getNome(playerid));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

	// Banid conta
    unbanIp(params[0]);
    
    Log::("unbanip", "%s\t\t|unban %s", getNome(playerid), params[0]);

	return 1;
}

CMD:slap(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/slap <id/nick>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	static
	    Float:x,
		Float:y,
		Float:z;
		
	GetPlayerPos(params[0], x, y, z);
	SetPlayerPos(params[0], x, y, z + 5.0);
	
	SendLanguageMessagef(playerid, corInfo, "MSG_027", getNome(params[0]));
	SendLanguageMessage(playerid, corInfo, "MSG_028");
	
	new
		stringAdmin[95]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s deu um tapa em %s", getNome(playerid), getNome(params[0]));
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
	
	Log::("slap", "%s\t\t|slapped %s", getNome(playerid), getNome(params[0]));

	return 1;
}

CMD:listararmas(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	if (sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/listararmas <id/nick>");

	if (!IsPlayerConnected(params[0]))
		return SendLanguageMessage(playerid, corError, "MSG_010");

	new
		stringAdmin[95]
		;

    stringGlobal[0] = EOS;

	for(new slot; slot < 13; slot++)
	{
		new weapon, ammo;
		GetPlayerWeaponDataReal(params[0], slot, weapon, ammo);
		format(stringAdmin, sizeof stringAdmin, "| %s: %d Balas\n", NomeArma(weapon), ammo);
		strcat(stringGlobal, stringAdmin);
	}
	
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Ok", "");

	Log::("listweapons", "%s\t\t|listed %s", getNome(playerid), getNome(params[0]));

	return 1;
}

CMD:addwhitelist(playerid, params[])
{
	if (PlayerData[playerid][dAdmin] < 1)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");
		
	if (sscanf(params, "s[24]", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/addwhitelist <nickname>");
	    
	if (!isNickRegistered(params[0]))
	    return SendClientMessage(playerid, corError, "ERROR: {888888}Nick não encontrado no banco de dados.");
	    
	if (IsNicknameInWhitelist(params[0]))
		return SendClientMessage(playerid, corError, "ERRO: {999999}Este nickname já se encontra na whitelist do servidor.");
		
    AddNicknameToWhitelist(params[0], getNome(playerid));
    
  	new
		stringAdmin[95]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s adicionou %s a whitelist", getNome(playerid), params[0]);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);
    
    SendClientMessagef(playerid, corInfo, "Você adicionou o nickname %s na whitelist do servidor.", params[0]);
    
    Log::("whitelist", "%s|\tadicionou %s", getNome(playerid), params[0]);
	return 1;
}

CMD:removewhitelist(playerid, params[])
{
	if (PlayerData[playerid][dAdmin] < 2)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (sscanf(params, "s[24]", params[0]))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/removewhitelist <nickname>");

	if (!isNickRegistered(params[0]))
	    return SendClientMessage(playerid, corError, "ERROR: {888888}Nick não encontrado no banco de dados.");

	if (!IsNicknameInWhitelist(params[0]))
		return SendClientMessage(playerid, corError, "ERRO: {999999}Este nickname não se encontra na whitelist do servidor.");

    RemoveNicknameFromWhitelist(params[0]);

  	new
		stringAdmin[95]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s removeu %s da whitelist", getNome(playerid), params[0]);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    SendClientMessagef(playerid, corInfo, "Você removeu o nickname %s da whitelist do servidor.", params[0]);
    
    Log::("whitelist", "%s|\tremoveu %s", getNome(playerid), params[0]);
	return 1;
}

CMD:spawnitem(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 7)
		return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	if (!IsPlayerAdminDuty(playerid) && PlayerData[playerid][dAdmin] < 10)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não está em modo de ajuda.");

	new name[128], quantidade;

	if (sscanf(params, "ds[128]", quantidade, name))
	    return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/spawnitem <unidades> <nome-do-item>");

	static
	    modelid,
	    type,
	    itemname[128],
	    // Pos
	    Float:x,
		Float:y,
		Float:z,
		Float:a;

    if (!GetItemInfoByName(name, modelid, type, itemname))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Nenhum item encontrado com este nome!");

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	GetXYInFrontOfPoint(x, y, a, 1.0);

	createDroppedItem(x, y, z, itemname, type, modelid, quantidade, true, GetPlayerVirtualWorld(playerid));

	SendClientMessagef(playerid, corInfo, "Você criou um(a) %s com %d unidade(s).", itemname, quantidade);

  	new
		stringAdmin[95]
		;
	format(stringAdmin, sizeof stringAdmin, "Admin %s criou o item %s com %d unidades", getNome(playerid), itemname, quantidade);
	sendMessageToAdmins(stringAdmin, 0xAAAAAAFF);

    Log::("spawnitem", "%s\t\t|created item %s with %d unid", getNome(playerid), itemname, quantidade);

	return 1;
}

stock countAdminsOnline() {

	new count;

	foreach(new playerid : Player) {

	    if (PlayerData[playerid][dAdmin])
	        count++;
	}
	return count;
}

CMD:ah(playerid) {

	if (!PlayerData[playerid][dAdmin])
	    return SendLanguageMessage(playerid, corError, "NO_PERMISSION");

	stringGlobal[0] = EOS;

	if (PlayerData[playerid][dAdmin] >= 1) {
		strcat(stringGlobal, "{FF7777}/a             \t{AAAAAA}Fala no chat admin\n");
		strcat(stringGlobal, "{FF7777}/pm            \t{AAAAAA}Manda mensagem para um jogador\n");
		strcat(stringGlobal, "{FF7777}/clima         \t{AAAAAA}Altera o clima do servidor\n");
		strcat(stringGlobal, "{FF7777}/world         \t{AAAAAA}Muda o virtual world\n");
		strcat(stringGlobal, "{FF7777}/slap          \t{AAAAAA}Da um tapa em um jogador\n");
		strcat(stringGlobal, "{FF7777}/finalizarsup  \t{AAAAAA}Finaliza um suporte a jogadores\n");
		strcat(stringGlobal, "{FF7777}/mutar         \t{AAAAAA}Muta um jogador\n");
		strcat(stringGlobal, "{FF7777}/limparchat    \t{AAAAAA}Limpa o chat de todos\n");
		strcat(stringGlobal, "{FF7777}/bloquear      \t{AAAAAA}Bloqueia um player de jogar\n");
		strcat(stringGlobal, "{FF7777}/addwhitelist  \t{AAAAAA}Adiciona um nick a whitelist\n");
	}
	if (PlayerData[playerid][dAdmin] >= 2) {
		strcat(stringGlobal, "{FF7777}/irpos         \t{AAAAAA}Vai até uma posição\n");
		strcat(stringGlobal, "{FF7777}/kick          \t{AAAAAA}Expulsa um jogador do servidor\n");
		strcat(stringGlobal, "{FF7777}/kickgrupo     \t{AAAAAA}Kicka os jogadores do grupo\n");
		strcat(stringGlobal, "{FF7777}/ir            \t{AAAAAA}Vai até um jogador\n");
		strcat(stringGlobal, "{FF7777}/trazer        \t{AAAAAA}Tras um jogador até sua posição\n");
		strcat(stringGlobal, "{FF7777}/avadm         \t{AAAAAA}Manda um aviso para todos online\n");
		strcat(stringGlobal, "{FF7777}/spec          \t{AAAAAA}Começa a spectar um jogador\n");
		strcat(stringGlobal, "{FF7777}/specoff       \t{AAAAAA}Cancela o modo spectador\n");
	}
	if (PlayerData[playerid][dAdmin] >= 3) {
		strcat(stringGlobal, "{FF7777}/ban           \t{AAAAAA}Bane um jogador do servidor\n");
		strcat(stringGlobal, "{FF7777}/banoff        \t{AAAAAA}Bane um jogador offline\n");
		strcat(stringGlobal, "{FF7777}/tempban       \t{AAAAAA}Bane temporariamente um jogador\n");
		strcat(stringGlobal, "{FF7777}/tempbanoff    \t{AAAAAA}Bane um jogador offline\n");
		strcat(stringGlobal, "{FF7777}/desban        \t{AAAAAA}Desbane um jogador\n");
		strcat(stringGlobal, "{FF7777}/desbanip      \t{AAAAAA}Desbane um IP\n");
		strcat(stringGlobal, "{FF7777}/ip            \t{AAAAAA}Mostra o IP de um jogador\n");
	}
	if (PlayerData[playerid][dAdmin] >= 4) {
		strcat(stringGlobal, "{FF7777}/vehiclehealth \t{AAAAAA}Seta a vida de um veiculo\n");
		strcat(stringGlobal, "{FF7777}/darvida       \t{AAAAAA}Seta a vida de um jogador\n");
		strcat(stringGlobal, "{FF7777}/temporestart  \t{AAAAAA}Seta o tempo de restart do server\n");
		strcat(stringGlobal, "{FF7777}/gmx           \t{AAAAAA}Reinicia o servidor\n");
		strcat(stringGlobal, "{FF7777}/explodir      \t{AAAAAA}Explode um jogador\n");
		strcat(stringGlobal, "{FF7777}/desativarg    \t{AAAAAA}Muta um jogador\n");
	}
	if (PlayerData[playerid][dAdmin] >= 5) {
		strcat(stringGlobal, "{FF7777}/novasenha     \t{AAAAAA}Troca a senha de uma conta\n");
	}
	if (PlayerData[playerid][dAdmin] >= 6) {
		strcat(stringGlobal, "{FF7777}/daradmin      \t{AAAAAA}Dá admin para um jogador\n");
	}
	if (PlayerData[playerid][dAdmin] >= 10) {
		strcat(stringGlobal, "{FF7777}/vehicle       \t{AAAAAA}Cria um veículo\n");
		strcat(stringGlobal, "{FF7777}/dararma       \t{AAAAAA}Dá uma arma para um jogador\n");
	    strcat(stringGlobal, "{FF7777}/darcash       \t{AAAAAA}Dá cash para um jogador\n");
	    strcat(stringGlobal, "{FF7777}/setarcash     \t{AAAAAA}Seta o cash de um jogador\n");
    }

	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Z Nation comandos:", stringGlobal, "Ok", "");

	return 1;
}
