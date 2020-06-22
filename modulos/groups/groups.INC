

#define MAX_GROUPS    		  	  		(300)
#define MAX_GROUP_MEMBERS     	  		(20)
#define MAX_GROUP_NAME_LEN    	  		(20)
#define MIN_GROUP_NAME_LEN    	  		(4)
#define MIN_LEVEL_CREATE_GROUP          (5)
#define IsValidServerGroup(%0)    		(Iter_Contains(iterGroups, %0))
#define GetServerGroupsPages()    		(Iter_Count(iterGroups) / 12)
#define GetPlayerServerGroupPage(%0)    (GetPVarInt(%0, "groupPage"))
#define IsPlayerViewServerGroups(%0)    (GetPVarInt(%0, "viewGroups"))
#define prevPageServerGroups(%0)        (SetPVarInt(%0, "groupPage", GetPVarInt(%0, "groupPage") - 1))
#define nextPageServerGroups(%0)        (SetPVarInt(%0, "groupPage", GetPVarInt(%0, "groupPage") + 1))
#define AUTOMATIC_DELETE_GROUP          (4 * 86400) // 4 dias

enum groupsEnum {

	groupName[MAX_GROUP_NAME_LEN],
	groupLeader[MAX_PLAYER_NAME],
	Text:textGroupMembers,
	groupLastActive,
}

enum {

    GROUP_DIALOG_CREATE,
    GROUP_DIALOG_DESTROY,
    GROUP_DIALOG_CLEAR,
    GROUP_DIALOG_INVITE,
	GROUP_DIALOG_LEAVE,
}

new GroupInfo[MAX_GROUPS][groupsEnum];
new GroupMembers[MAX_GROUPS][MAX_GROUP_MEMBERS][MAX_PLAYER_NAME];
new Iterator:iterGroups<MAX_GROUPS>;
new SelectGroups[MAX_PLAYERS][12];
new Text3D:playerGroupText[MAX_PLAYERS][4];
new InviteGroup[MAX_PLAYERS] = {-1, ...};

// Funções
stock createServerGroup(groupname[], leader[]) {

	new index = Iter_Free(iterGroups);
	
	if (index != -1) {
	
	    // Add iter
	    Iter_Add(iterGroups, index);
	
	    GroupInfo[index][groupLastActive] = gettime() + AUTOMATIC_DELETE_GROUP;
	
	    // Setar líder
	    format(GroupInfo[index][groupLeader], MAX_PLAYER_NAME, leader);
	
	    // Setar nome
	    format(GroupInfo[index][groupName], MAX_GROUP_NAME_LEN, groupname);
	    
	    // Resetar membros
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {
	        format(GroupMembers[index][members], MAX_PLAYER_NAME, "Ninguém");
	    }

		// salvar grupo
	    saveServerGroup(index);
	    
	    // update texts grupo
	    updateServerGroupTextLabels(index);
	
	    return index;
	}
	return -1;
}

stock destroyServerGroup(index) {

	if (IsValidServerGroup(index)) {
	
//	    format(GroupInfo[index][groupLeader], MAX_PLAYER_NAME, "Ninguém");
	
	    // Remover todos os players do grupo
	    foreach(new playerid : Player) {

			// Checar se pertence ao grupo
	        if (getPlayerServerGroup(playerid) == index) {
	        
				// Remover do grupo
	            removePlayerFromServerGroup(playerid, index, false);
	        }
	    }
	    
	    // Destruir grupo
	    new group_path[75];
			
	    // Local do arquivo
	    format(group_path, sizeof (group_path), pastaGroups, index);
	    
	    // Deletar o arquivo
	    fremove(group_path);
	    
	    // Remove iterator
	    Iter_Remove(iterGroups, index);
	    
	    return 1;
	}

	return 0;
}

stock saveServerGroup(index) {

	if (IsValidServerGroup(index)) {
	
	    new group_path[75];
	    new group_string[75];
	    new File:
			group_file;
	
	    // Local do arquivo
	    format(group_path, sizeof (group_path), pastaGroups, index);
	
	    // Abrir o arquivo
	    group_file = fopen(group_path, io_write);
	    
	    // Verificar se abriu corretamente
	    if (group_file) {
	    
	        // Salvar nome
	        format(group_string, sizeof (group_string), "%s|NULL\r\n", GroupInfo[index][groupName]);
	        fwrite(group_file, group_string);
	    
	        // Salvar líder
	        format(group_string, sizeof (group_string), "%s|NULL\r\n", GroupInfo[index][groupLeader]);
	        fwrite(group_file, group_string);
	        
	        format(group_string, sizeof (group_string), "%d|NULL\r\n", GroupInfo[index][groupLastActive]);
	        fwrite(group_file, group_string);
	        
	        // Salvar membros
		    for(new members; members < MAX_GROUP_MEMBERS; members++) {
	        	format(group_string, sizeof (group_string), "%s|NULL\r\n", GroupMembers[index][members]);
	        	fwrite(group_file, group_string);
		    }
		    
		    // Fechar o arquivo
		    fclose(group_file);
		    
		    // Debug
		    printf("[Grupos] %d salvo com sucesso!", index);
	    } else {
	    
	        // Debug
	        printf("[Grupos] %d não foi possível salvar!", index);
	    }
	
	    return 1;
	}
	return 0;
}

stock loadServerGroup(index) {

	// Reset iterator
	Iter_Remove(iterGroups, index);

	// Variaveis
  	new group_path[75];
    new group_string[2][75];
    new group_read[75];
    new File:
		group_file;

    // Local do arquivo
   	format(group_path, sizeof (group_path), pastaGroups, index);

	// Verificar se existe
	if (!fexist(group_path)) return 0;

    // Abrir o arquivo
    group_file = fopen(group_path, io_read);

    // Verificar se abriu corretamente
    if (group_file) {

		// Add iterator
		Iter_Add(iterGroups, index);

      	// Carregar o nome
      	fread(group_file, group_read);
      	split(group_read, group_string, '|');
      	format(GroupInfo[index][groupName], MAX_GROUP_NAME_LEN, group_string[0]);

	    // Carregar líder
      	fread(group_file, group_read);
      	split(group_read, group_string, '|');
      	format(GroupInfo[index][groupLeader], MAX_PLAYER_NAME, group_string[0]);
      	
      	fread(group_file, group_read);
      	split(group_read, group_string, '|');
      	GroupInfo[index][groupLastActive] = strval(group_string[0]);
      	
	    // Carregar membros
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {
	      	fread(group_file, group_read);
	      	split(group_read, group_string, '|');
	      	format(GroupMembers[index][members], MAX_PLAYER_NAME, group_string[0]);
	   	}

	    // Fechar o arquivo
	    fclose(group_file);

	    // Debug
	    printf("[Grupos] %d | %s | Líder: %s", index, GroupInfo[index][groupName], GroupInfo[index][groupLeader]);
	    
	    if (gettime() > GroupInfo[index][groupLastActive])
	    {
	        destroyServerGroup(index);
	        
	        Log::("destroygroup", "group %d destroyed for inactivity", index);
	    }
	    
	    return 1;
    }
    return 0;
}

stock loadServerGroups() {

	for(new index; index < MAX_GROUPS; index++) {
	    loadServerGroup(index);
	}
}

stock ActivityCheckGroup(playerid)
{
	new index = getPlayerServerGroup(playerid);
	
	if (index != -1)
	{
	    GroupInfo[index][groupLastActive] = gettime() + AUTOMATIC_DELETE_GROUP;
	    
	    saveServerGroup(index);
	}
}

stock getPlayerServerGroup(playerid) {

	foreach(new index : iterGroups) {
	
	    // Checar se for o líder
	    if (!strcmp(getNome(playerid), GroupInfo[index][groupLeader])) {
	        return index;
	    }

		// Checar se for um dos membros
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {

		    if (!strcmp(getNome(playerid), GroupMembers[index][members])) {
		        return index;
		    }
	   	}
	}

	return -1;
}

stock isNameServerGroupExist(namegroup[]) {

	foreach(new index : iterGroups) {

	    // Checar se for o mesmo nome
	    if (!strcmp(namegroup, GroupInfo[index][groupName])) {
	        return 1;
	    }
	}

	return 0;
}

stock kickGroup(namegroup[]) {

	foreach(new index : iterGroups) {
	    // Checar se for o mesmo nome
	    if (!strcmp(namegroup, GroupInfo[index][groupName])) {

			// Kick jogador caso for do grupo
			foreach(new playerid : Player) {
			    if (getPlayerServerGroup(playerid) == index) Kick(playerid);
			}

			return 1;
	    }
	}
	return 0;
}

stock IsPlayerLeaderGroup(playerid, index) {

	if (IsValidServerGroup(index)) {
	
	    // Checar se for o líder
	    if (!strcmp(getNome(playerid), GroupInfo[index][groupLeader])) {
	        return 1;
	    }
	}
	return 0;
}

stock sendServerGroupMessage(index, color, message[]) {

	foreach(new playerid : Player) {
	
	    if (getPlayerServerGroup(playerid) == index) {
	        SendClientMessage(playerid, color, message);
	    }
	}
}

CMD:c(playerid, params[]) {

	if (gettime() < PlayerData[playerid][dMuted])
	    return SendLanguageMessagef(playerid, corError, "MSG_MUTE", PlayerData[playerid][dMuted] - gettime());

	if (sscanf(params, "s[128]", params))
        return SendClientMessage(playerid, corCinza, "Uso correto: {FF5500}/c <texto>");
        
	new index = getPlayerServerGroup(playerid);
	
	if (index != -1) {
	    new string[144];
	    format(string, sizeof string, "@%s (%s): %s", getPlayerServerGroupName(playerid), getNome(playerid), params);
	    sendServerGroupMessage(index, 0xAAAAFFFF, string);
	    Log::("groupchat", string);
	} else {
	    SendLanguageMessage(playerid, corError, "MSG_047");
	}
	return 1;
}

stock countServerGroupMembers(index) {

	if (IsValidServerGroup(index)) {

		// variavel
		new group_count;

	    // Checar se for o líder
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {

			// Checar se não tem ninguém na vaga
		    if (!strcmp("Ninguém", GroupMembers[index][members])) {
		        continue;
		    }
		    
		    // add contagem
		    group_count++;
	   	}
	   	return group_count;
	}
	return 0;
}

stock listPlayerServerGroupMembers(playerid, index) {

	// Variavel
	new group_string[75];

	// Limpar a string
    stringGlobal[0] = EOS;
    
    // Mostrar o nome
    format(group_string, sizeof (group_string), GetPlayerLanguageKey(playerid, "GP_1"), GroupInfo[index][groupName]);
    strcat(stringGlobal, group_string);
    
    // Mostrar o lider
    format(group_string, sizeof (group_string), GetPlayerLanguageKey(playerid, "GP_2"), GroupInfo[index][groupLeader]);
    strcat(stringGlobal, group_string);
    
    // Mostrar os membros
    for(new members; members < MAX_GROUP_MEMBERS; members++) {

		// Checar se não tem ninguém na vaga
	    if (!strcmp("Ninguém", GroupMembers[index][members])) {
	        continue;
	    }
    	format(group_string, sizeof (group_string), "%s~n~", GroupMembers[index][members]);
    	strcat(stringGlobal, group_string);
  	}
  	
  	// Update na TextDraw
	PlayerTextDrawSetString(playerid, textPlayerGroups[0][playerid], stringGlobal);
}

stock listPlayerServerGroups(playerid) {

	if (!IsPlayerViewServerGroups(playerid)) return 0;

	// variaveis
	new group_string[75];
	new group_total_count;
	new group_count;
	
	// Resetar os grupos na variavel do jogador
	for(new index; index < 12; index++)
	    SelectGroups[playerid][index] = -1;
	
	// Guardar os grupos válidos em uma variavel
	new groups[MAX_GROUPS] = {-1, ...};
	foreach(new index : iterGroups) {

		groups[group_total_count] = index;
        group_total_count++;
	}

	// Limpar string
    stringGlobal[0] = EOS;

	if (group_total_count > 0) {

		for(new index = (GetPlayerServerGroupPage(playerid) * 12); index < group_total_count; index++) {

		    if (group_count > 11)
				break;

		    // paginas
		    new index_real = groups[index];

		    // guardar na variavel
		    SelectGroups[playerid][group_count] = index_real;

		    // formatar string
		    format(group_string, sizeof (group_string), "%s~n~~n~", GroupInfo[index_real][groupName]);
		    strcat(stringGlobal, group_string);

			// Add contagem
		    group_count++;
		}
	}

	// Update na textdraw
	PlayerTextDrawSetString(playerid, textPlayerGroups[1][playerid], stringGlobal);

	// Update na textdraw paginas
	format(group_string, sizeof (group_string), "%d-%d", GetPlayerServerGroupPage(playerid) + 1, GetServerGroupsPages() + 1);
	PlayerTextDrawSetString(playerid, textPlayerGroups[2][playerid], group_string);
	
	return 1;
}

stock listPlayerOwnGroup(playerid) {

	// variaveis
	new group_string[75];
	new index;

	// Listar membros
	index = getPlayerServerGroup(playerid);
	
	if (index != -1) {
	
	    if (!IsPlayerLeaderGroup(playerid, index)) return 0;
	
	    stringGlobal[0] = EOS;
	
	    // Headers
	    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_3"));
	    strcat(stringGlobal, "\t");
	    strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_4"));
	    strcat(stringGlobal, "\n");
	
	    // Loop nos membros
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {

			// Checar se não tem ninguém na vaga
		    if (!strcmp("Ninguém", GroupMembers[index][members])) {
				format(group_string, sizeof (group_string), "{777777}%d.\t{777777}%s\n", members + 1, GroupMembers[index][members]);
				strcat(stringGlobal, group_string);
		    } else {
				format(group_string, sizeof (group_string), "%d.\t%s\n", members + 1, GroupMembers[index][members]);
				strcat(stringGlobal, group_string);
		    }
	   	}

	   	ShowPlayerDialog(playerid, DIALOG_GROUP_CLEAR, DIALOG_STYLE_TABLIST_HEADERS, " ", stringGlobal, GetPlayerLanguageKey(playerid, "GP_5"), GetPlayerLanguageKey(playerid, "MENU_CANCEL"));
	
	    return 1;
	}
	return 0;
}


stock putPlayerInServerGroup(playerid, index) {

	if (IsValidServerGroup(index)) {

	    // Checar se for o líder
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {

			// Checar se não tem ninguém na vaga
		    if (!strcmp("Ninguém", GroupMembers[index][members])) {

				// add membro na vaga
				format(GroupMembers[index][members], MAX_PLAYER_NAME, getNome(playerid));

				// Atualizar 3d textlabels e textdraw
                updateServerGroupTextLabels(index);

				// Salvar grupo
				saveServerGroup(index);
				
				return 1;
		    }
	   	}
	}
	return 0;
}

stock removePlayerFromServerGroup(playerid, index, bool:savegroup=true) {

	if (IsValidServerGroup(index)) {

		// Checar se for lider
		if (!strcmp(getNome(playerid), GroupInfo[index][groupLeader])) {
		
			// Destruir texts
            destroyGroupTexts(playerid);
		
		    // Limpar vaga
		    format(GroupInfo[index][groupLeader], MAX_PLAYER_NAME, "Ninguém");

			// Esconder textdraw
			PlayerTextDrawHide(playerid, textGroupMembersList[playerid]);

			// Salvar grupo
			if (savegroup) {
				saveServerGroup(index);
			}
		    return 1;
		}

	    // Checar se for membro
	    for(new members; members < MAX_GROUP_MEMBERS; members++) {

			// Checar se não tem ninguém na vaga
		    if (!strcmp(getNome(playerid), GroupMembers[index][members])) {

				// Destruir texts
                destroyGroupTexts(playerid);

				// Remover membro na vaga
				format(GroupMembers[index][members], MAX_PLAYER_NAME, "Ninguém");

				// Esconder textdraw
				PlayerTextDrawHide(playerid, textGroupMembersList[playerid]);

				// Salvar grupo
				if (savegroup) {
					saveServerGroup(index);
				}

				return 1;
		    }
	   	}
	}
	return 0;
}

stock showPlayerServerGroups(playerid) {

	if (IsPlayerAdminDuty(playerid))
	    return 0;

	// Mostrar textdraws
	for(new text; text < sizeof textGroups; text++)
		TextDrawShowForPlayer(playerid, textGroups[text]);
		
	for(new text; text != 3; text++)
	    PlayerTextDrawShow(playerid, textPlayerGroups[text][playerid]);
	    
	// Checar pagina
	if (GetPlayerServerGroupPage(playerid) > GetServerGroupsPages()) {
	    SetPVarInt(playerid, "groupPage", GetServerGroupsPages());
	}
	    
	// Setar pvar
	SetPVarInt(playerid, "viewGroups", 1);
	    
	// Update nos grupos
	listPlayerServerGroups(playerid);
	    
	new index = getPlayerServerGroup(playerid);
	
	if (index != -1) {
	    listPlayerServerGroupMembers(playerid, index);
	} else {
	    PlayerTextDrawSetString(playerid, textPlayerGroups[0][playerid], "_");
	}
	    
	// Selecionar textdraws
	SelectTextDraw(playerid, 0x333333FF);
	
	return 1;
}

stock hidePlayerServerGroups(playerid) {

	// Esconder textdraws
	for(new text; text < sizeof textGroups; text++)
		TextDrawHideForPlayer(playerid, textGroups[text]);

	for(new text; text != 3; text++)
	    PlayerTextDrawHide(playerid, textPlayerGroups[text][playerid]);

	// Parar de selecionar textdraws
	CancelSelectTextDraw(playerid);

	// Setar pvar
	DeletePVar(playerid, "viewGroups");
}

stock getPlayerServerGroupName(playerid) {

	new index = getPlayerServerGroup(playerid);
	new sgroupName[MAX_GROUP_NAME_LEN] = "-";
	
	if (index != -1) {
	
	    sgroupName[0] = EOS;
	    
	    format(sgroupName, sizeof sgroupName, GroupInfo[index][groupName]);
	}
	return sgroupName;
}

stock updateServerGroupTextLabels(index, ignoreid=INVALID_PLAYER_ID) {

	if (IsValidServerGroup(index)) {
	
		// Players que virão o text label
		new playersViewText[MAX_GROUP_MEMBERS + 3] = {-1, ...};
		
		// Variaveis
		new group_count;
		new group_string[35];
		
		// Limpar strng
		stringGlobal[0] = EOS;
		
		foreach(new playerid : Player) {
		
		    if (getPlayerServerGroup(playerid) == index && playerid != ignoreid) {
		    
		        playersViewText[group_count] = playerid;
		        group_count++;
		        
		        // formatar membros na textdraw
		        format(group_string, sizeof (group_string), "~t~ %s~n~", getNome(playerid));
		        strcat(stringGlobal, group_string);
		    }
		}
		
		// format na flexa
		new str[5];
		format(str, sizeof (str), "%c/", 92);
		
		//foreach(new playerid : Player) {
		for(new pindex; pindex < group_count; pindex++) {

		    new playerid = playersViewText[pindex];

			for(new text3d; text3d < 4; text3d++)
			    DestroyDynamic3DTextLabel(playerGroupText[playerid][text3d]);

		   	playerGroupText[playerid][0] = CreateDynamic3DTextLabelEx(str, 0xCCFF00EE, 0.0, 0.0, 0.070, 300.0,
											.attachedplayer = playerid,
											.testlos = 0,
											.streamdistance = 150.0,
											.players = playersViewText,
											.maxplayers = group_count);
			
		    playerGroupText[playerid][1] = CreateDynamic3DTextLabelEx(str, 0xCCFF00EE, 0.0, 0.0, 0.080, 300.0,
											.attachedplayer = playerid,
											.testlos = 0,
											.streamdistance = 150.0,
											.players = playersViewText,
											.maxplayers = group_count);
											
		    playerGroupText[playerid][2] = CreateDynamic3DTextLabelEx(str, 0xCCFF00EE, 0.0, 0.0, 0.090, 300.0,
											.attachedplayer = playerid,
											.testlos = 0,
											.streamdistance = 150.0,
											.players = playersViewText,
											.maxplayers = group_count);

		    playerGroupText[playerid][3] = CreateDynamic3DTextLabelEx(getNome(playerid), 0xCCFF00F5, 0.0, 0.0, 0.23, 6.0,
											.attachedplayer = playerid,
											.testlos = 0,
											.streamdistance = 150.0,
											.players = playersViewText,
											.maxplayers = group_count);
		}
		
		for(new pindex; pindex < group_count; pindex++) {

		    new playerid = playersViewText[pindex];
			Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
			
			// Update na textdraw
			PlayerTextDrawSetString(playerid, textGroupMembersList[playerid], stringGlobal);
			PlayerTextDrawShow(playerid, textGroupMembersList[playerid]);
		}
		
		return 1;
	}
	return 0;
}

stock destroyGroupTexts(playerid) {

	new index = getPlayerServerGroup(playerid);
	
	if (index != -1) {
    	updateServerGroupTextLabels(index, playerid);
	}
	
	PlayerTextDrawHide(playerid, textGroupMembersList[playerid]);

	for(new text3d; text3d < 4; text3d++)
	    DestroyDynamic3DTextLabel(playerGroupText[playerid][text3d]);
}

stock showPlayerDialogGroup(playerid, group_dialog_type = GROUP_DIALOG_CREATE) {

	stringGlobal[0] = EOS;
	
	switch(group_dialog_type) {
	
	    case GROUP_DIALOG_CREATE: {

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_6"));
			strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_7"));
			strcat(stringGlobal, "\n");
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_8"));
			strcat(stringGlobal, "\n");
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_9"));
			strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_10"));
			ShowPlayerDialog(playerid, DIALOG_GROUP_CREATE, DIALOG_STYLE_INPUT, " ", stringGlobal, GetPlayerLanguageKey(playerid, "MENU_CREATE"), GetPlayerLanguageKey(playerid, "MENU_CANCEL"));
		}
	    case GROUP_DIALOG_DESTROY: {
	    
	        new string[144];
	        
	        new index = getPlayerServerGroup(playerid);
	        
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_10"));
			strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_11"));
			strcat(stringGlobal, "\n");
			format(string, sizeof string, GetPlayerLanguageKey(playerid, "GP_12"), GroupInfo[index][groupName]);
            strcat(stringGlobal, string);
            strcat(stringGlobal, "\n");
			format(string, sizeof string, GetPlayerLanguageKey(playerid, "GP_13"), countServerGroupMembers(index));
            strcat(stringGlobal, string);
            strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_14"));
			ShowPlayerDialog(playerid, DIALOG_GROUP_DESTROY, DIALOG_STYLE_MSGBOX, " ", stringGlobal, GetPlayerLanguageKey(playerid, "MENU_DESTROY"), GetPlayerLanguageKey(playerid, "MENU_CANCEL"));
	    }
	    case GROUP_DIALOG_CLEAR: {
	        listPlayerOwnGroup(playerid);
	    }
	    case GROUP_DIALOG_INVITE: {
	    
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_15"));
			strcat(stringGlobal, "\n");
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_16"));
			ShowPlayerDialog(playerid, DIALOG_GROUP_INVITE, DIALOG_STYLE_INPUT, " ", stringGlobal, GetPlayerLanguageKey(playerid, "MENU_INVITE"), GetPlayerLanguageKey(playerid, "MENU_CANCEL"));
	    }
		case GROUP_DIALOG_LEAVE: {
		
	        new string[75];

	        new index = getPlayerServerGroup(playerid);

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_17"));
			strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_11"));
			strcat(stringGlobal, "\n");
			format(string, sizeof string, GetPlayerLanguageKey(playerid, "GP_12"), GroupInfo[index][groupName]);
            strcat(stringGlobal, string);
            strcat(stringGlobal, "\n");
			format(string, sizeof string, GetPlayerLanguageKey(playerid, "GP_13"), countServerGroupMembers(index));
            strcat(stringGlobal, string);
            strcat(stringGlobal, "\n\n");

			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_18"));
			strcat(stringGlobal, "\n\n");
			strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_19"));
			ShowPlayerDialog(playerid, DIALOG_GROUP_LEAVE, DIALOG_STYLE_MSGBOX, " ", stringGlobal, GetPlayerLanguageKey(playerid, "MENU_YES"), GetPlayerLanguageKey(playerid, "MENU_NO"));
		}
	}
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	// Se apertar ESC
    if (clickedid == Text:INVALID_TEXT_DRAW) {

		if (IsPlayerViewServerGroups(playerid)) {
		    hidePlayerServerGroups(playerid);
		}
	}
	
	// Se clicar em prev page
	if (clickedid == textGroups[21]) {
	
	    if (GetPlayerServerGroupPage(playerid) > 0) {

			// Voltar uma pagina
			prevPageServerGroups(playerid);
			
			// Atualizar grupos
			listPlayerServerGroups(playerid);
			
	        // Efeito de som
	        Audio_Play(playerid, 25);
	    }
	}

	// Se clicar em next page
	else if (clickedid == textGroups[22]) {
	
	    if (GetPlayerServerGroupPage(playerid) < GetServerGroupsPages()) {
	    
	        // Pular uma pagina
	        nextPageServerGroups(playerid);
	        
			// Atualizar grupos
			listPlayerServerGroups(playerid);

	        // Efeito de som
	        Audio_Play(playerid, 25);
	    }
	}
	
	// Se clicar Criar Grupo
	else if (clickedid == textGroups[15]) {
		showPlayerDialogGroup(playerid, GROUP_DIALOG_CREATE);
	}
	
	// Se clicar Meu Grupo
	else if (clickedid == textGroups[16]) {

		new index = getPlayerServerGroup(playerid);

		if (index != -1) {
		    listPlayerServerGroupMembers(playerid, index);
		} else {
		    SendLanguageMessage(playerid, corError, "MSG_047");
		}
	}
	
	// Se clicar Convidar membro
	else if (clickedid == textGroups[17]) {

		new index = getPlayerServerGroup(playerid);

		if (index != -1) {
		    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
		} else {
		    SendLanguageMessage(playerid, corError, "MSG_047");
		}
	}
	
	// Se clicar Limpar membro
	else if (clickedid == textGroups[18]) {

		new index = getPlayerServerGroup(playerid);

		if (index != -1) {
		    showPlayerDialogGroup(playerid, GROUP_DIALOG_CLEAR);
		} else {
		    SendLanguageMessage(playerid, corError, "MSG_047");
		}
	}
	
	// Se clicar Destruir grupo
	else if (clickedid == textGroups[19]) {

		new index = getPlayerServerGroup(playerid);

		if (index != -1 && IsPlayerLeaderGroup(playerid, index)) {
		    showPlayerDialogGroup(playerid, GROUP_DIALOG_DESTROY);
		} else {
		    SendLanguageMessage(playerid, corError, "MSG_048");
		}
	}
	
	// Se clicar Sair do grupo
	else if (clickedid == textGroups[20]) {

		new index = getPlayerServerGroup(playerid);

		if (index != -1) {
		   	showPlayerDialogGroup(playerid, GROUP_DIALOG_LEAVE);
		} else {
		    SendLanguageMessage(playerid, corError, "MSG_047");
		}
	}
	
	// Se clicar em fechar
	else if (clickedid == textGroups[24]) {
	    hidePlayerServerGroups(playerid);
	}
	
	// Loop nas textdraws
	for(new text = 1, index; index < 12; index++, text++) {
	
	    if (clickedid == textGroups[text]) {
	    
	        // Guardar o id do grupo q foi clicado
			new index_real = SelectGroups[playerid][index];
			
			// Checar se o grupo existe
			if (index_real != -1) {
			
			    // Update nas textdraws
			    listPlayerServerGroupMembers(playerid, index_real);
			}
	    
	        break;
	    }
	}
	

 	#if defined gOnPlayerClickTextDraw
  		return gOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw gOnPlayerClickTextDraw
#if defined gOnPlayerClickTextDraw
	forward gOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

CMD:grupos(playerid) {

    showPlayerServerGroups(playerid);
    updateTextdrawsLang(playerid, .showbutton = false);

	return 1;
}

CMD:hgruposex(playerid) {

    hidePlayerServerGroups(playerid);

	return 1;
}

CMD:cgrupoex(playerid, params[]) {

    createServerGroup(params, getNome(playerid));

	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid) {
	
	    case DIALOG_GROUP_CREATE: {
	    
			if (response) {
			
			    new len = strlen(inputtext);
			    
			    if (len < MIN_GROUP_NAME_LEN || len > MAX_GROUP_NAME_LEN) {
					return SendLanguageMessagef(playerid, corError, "MSG_049", MIN_GROUP_NAME_LEN, MAX_GROUP_NAME_LEN);
			    }
			    
			    if (isNameServerGroupExist(inputtext)) {
			        return SendLanguageMessagef(playerid, corError, "MSG_050", inputtext);
			    }
			    
			    if (getPlayerServerGroup(playerid) != -1) {
			        return SendLanguageMessage(playerid, corError, "MSG_051");
			    }
			    
			    if (PlayerData[playerid][dLevel] < MIN_LEVEL_CREATE_GROUP) {
			        return SendLanguageMessagef(playerid, corError, "MSG_052", MIN_LEVEL_CREATE_GROUP);
			    }
			    
			    new group = createServerGroup(inputtext, getNome(playerid));
			    
			    if (group != -1) {
			    
					// Update nos grupos
					listPlayerServerGroups(playerid);

					// Listar informações
			  		listPlayerServerGroupMembers(playerid, group);
			    
			        SendLanguageMessagef(playerid, corInfo, "MSG_053", inputtext);
			        
			        checkPlayerConquista(playerid, Conquista_Grupo);
			    } else {
			        SendLanguageMessage(playerid, corError, "MSG_054");
			    }
			}
	    }
	    case DIALOG_GROUP_INVITE: {
	    
	        if (response) {
	        
				new index;
				
				if (sscanf(inputtext, "u", index)) {
				    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
				    return 1;
				}
				
				if (!IsPlayerConnected(index)) {
				    SendLanguageMessage(playerid, corError, "MSG_010");
				    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
					return 1;
				}
				
				if (!PlayerData[index][dLogged]) {
				    SendLanguageMessage(playerid, corError, "MSG_010");
                    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
					return 1;
				}
				
				if (getPlayerServerGroup(index) == getPlayerServerGroup(playerid)) {
				    SendLanguageMessage(playerid, corError, "MSG_055");
                    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
					return 1;
				}
				
				if (getPlayerServerGroup(index) != -1) {
				    SendLanguageMessage(playerid, corError, "MSG_056");
                    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
                    return 1;
				}
				
				new gindex = getPlayerServerGroup(playerid);
				
				if (!IsPlayerLeaderGroup(playerid, gindex) || gindex == -1) {
				    SendLanguageMessage(playerid, corError, "MSG_048");
				    showPlayerDialogGroup(playerid, GROUP_DIALOG_INVITE);
				    return 1;
				}
				
				InviteGroup[index] = gindex;
				
				SendLanguageMessagef(playerid, corInfo, "MSG_057", getNome(index));
                SendLanguageMessagef(index, corInfo, "MSG_058", getNome(playerid), GroupInfo[gindex][groupName]);

				new string[75];
				
				stringGlobal[0] = EOS;
				
				strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_20"));
				strcat(stringGlobal, "\n\n");
				
				strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_21"));
				strcat(stringGlobal, "\n");
				format(string, sizeof (string), GetPlayerLanguageKey(playerid, "GP_12"), GroupInfo[gindex][groupName]);
				strcat(stringGlobal, string);
				strcat(stringGlobal, "\n");
				format(string, sizeof (string), GetPlayerLanguageKey(playerid, "GP_22"), getNome(playerid));
				strcat(stringGlobal, string);
				strcat(stringGlobal, "\n\n");
				
				strcat(stringGlobal, GetPlayerLanguageKey(playerid, "GP_23"));

				ShowPlayerDialog(index, DIALOG_GROUP_ACCEPT, DIALOG_STYLE_MSGBOX, " ", stringGlobal, GetPlayerLanguageKey(playerid, "MENU_YES"), GetPlayerLanguageKey(playerid, "MENU_NO"));
			}
	    }
	    case DIALOG_GROUP_ACCEPT: {
	    
	        if (response) {
	        
	            new index = InviteGroup[playerid];
	            
         		if (index != -1) {
	            
	                new success = putPlayerInServerGroup(playerid, index);
	                
	                if (success) {
	                    SendLanguageMessagef(playerid, corInfo, "MSG_059", GroupInfo[index][groupName]);

						new string[144];
						format(string, sizeof string, "Novo membro: O jogador %s entrou para o grupo!", getNome(playerid));
						sendServerGroupMessage(index, corInfo, string);
						
						checkPlayerConquista(playerid, Conquista_Grupo);
					} else {
	                    SendLanguageMessage(playerid, corError, "MSG_060");
	                }
	            } else {
	                SendLanguageMessage(playerid, corError, "MSG_061");
	            }
	        } else {
	            SendLanguageMessage(playerid, corError, "MSG_062");
	        }
	        InviteGroup[playerid] = -1;
	    }
	    case DIALOG_GROUP_CLEAR: {
	    
	        if (response) {
	        
	            new index = getPlayerServerGroup(playerid);
	            
	            if (!IsPlayerLeaderGroup(playerid, index) || index == -1) {
	                return SendLanguageMessage(playerid, corError, "MSG_048");
	            }
	            
	            // Mensagem para o lider
	            SendLanguageMessagef(playerid, corInfo, "MSG_063", listitem + 1, GroupMembers[index][listitem]);
	            
	            new playergroup = getId(GroupMembers[index][listitem]);
	            
	            if (IsPlayerConnected(playergroup)) {
	            
	                // Mandar mensagem para o player
	                SendLanguageMessagef(playergroup, corInfo, "MSG_064", GroupInfo[index][groupName]);

					// Remover o mesmo do grupo
                    removePlayerFromServerGroup(playergroup, index);
				} else {
	            
	                // Limpar a vaga
	                format(GroupMembers[index][listitem], MAX_PLAYER_NAME, "Ninguém");
	                
	                // Salvar o grupo
	                saveServerGroup(index);
	            }
	            
	            // Mostrar o dialog novamente
	            showPlayerDialogGroup(playerid, GROUP_DIALOG_CLEAR);
	        }
	    }
	    case DIALOG_GROUP_DESTROY: {
	    
	        if (response) {
	        
	            new index = getPlayerServerGroup(playerid);
	            
	            // Mandar mensagem
	            SendLanguageMessagef(playerid, corInfo, "MSG_065", GroupInfo[index][groupName]);

				// Destruir grupo
                destroyServerGroup(index);
                
                // Listar grupos
                listPlayerServerGroups(playerid);
			}
	    }
	    case DIALOG_GROUP_LEAVE: {

	        if (response) {

	            new index = getPlayerServerGroup(playerid);

			    if (IsPlayerLeaderGroup(playerid, index)) {
			    	return SendLanguageMessage(playerid, corError, "MSG_066");
				}

	            // Mandar mensagem
	            SendLanguageMessagef(playerid, corInfo, "MSG_067", GroupInfo[index][groupName]);

				// Sair do grupo
                removePlayerFromServerGroup(playerid, index);
			}
	    }
	}

	#if defined gOnDialogResponse
	    gOnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#endif
	return 1;
}
#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse gOnDialogResponse
#if defined gOnDialogResponse
	forward gOnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif







