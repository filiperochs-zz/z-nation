
#define MAX_CRAFT_ITENS (100)

enum playerCraftEnum {

	craft_item[4],
	craft_item_type[4],
	craft_item_slot[4],
}

new PlayerCraftItens[MAX_PLAYERS][playerCraftEnum];

new serverCraftCount = -1;
new serverRecipeCount = 0;

enum craftEnum {
		CRAFT_ITEM_RESULT_TYPE,
		CRAFT_ITEM_RESULT_MODEL,
		CRAFT_ITEM_RESULT_AMOUNT,
bool:   CRAFT_ITEM_RESULT_TABLE,
	
		// RECEITA 1
		CRAFT_ITEM_MODEL1,
bool:	CRAFT_ITEM_RESET1,
		CRAFT_ITEM_TYPE1,
	
		//RECEITA 2
		CRAFT_ITEM_MODEL2,
bool:	CRAFT_ITEM_RESET2,
		CRAFT_ITEM_TYPE2,
	
		// RECEITA 3
		CRAFT_ITEM_MODEL3,
bool:	CRAFT_ITEM_RESET3,
		CRAFT_ITEM_TYPE3,
	
	// RECEITA 4
		CRAFT_ITEM_MODEL4,
bool:	CRAFT_ITEM_RESET4,
		CRAFT_ITEM_TYPE4,
}

new CraftItens[MAX_CRAFT_ITENS][craftEnum];

stock AddServerItemCraft(itemname[], itemtype, itemmodel, quantia, bool:table = false)
{
	#pragma unused itemname

	serverCraftCount ++;

    CraftItens[serverCraftCount][CRAFT_ITEM_RESULT_TYPE]  	= itemtype;
    CraftItens[serverCraftCount][CRAFT_ITEM_RESULT_MODEL] 	= itemmodel;
    CraftItens[serverCraftCount][CRAFT_ITEM_RESULT_AMOUNT]  = quantia;
    CraftItens[serverCraftCount][CRAFT_ITEM_RESULT_TABLE]   = table;

	CraftItens[serverCraftCount][CRAFT_ITEM_TYPE1]   = -1;
 	CraftItens[serverCraftCount][CRAFT_ITEM_MODEL1]  = -1;
  	CraftItens[serverCraftCount][CRAFT_ITEM_RESET1]  = false;
  	
	CraftItens[serverCraftCount][CRAFT_ITEM_TYPE2]   = -1;
 	CraftItens[serverCraftCount][CRAFT_ITEM_MODEL2]  = -1;
  	CraftItens[serverCraftCount][CRAFT_ITEM_RESET2]  = false;
  	
	CraftItens[serverCraftCount][CRAFT_ITEM_TYPE3]   = -1;
 	CraftItens[serverCraftCount][CRAFT_ITEM_MODEL3]  = -1;
  	CraftItens[serverCraftCount][CRAFT_ITEM_RESET3]  = false;
  	
	CraftItens[serverCraftCount][CRAFT_ITEM_TYPE4]   = -1;
 	CraftItens[serverCraftCount][CRAFT_ITEM_MODEL4]  = -1;
  	CraftItens[serverCraftCount][CRAFT_ITEM_RESET4]  = false;

	serverRecipeCount = 0;
    
    return serverCraftCount;
}

stock ListPlayerCraft(playerid) {
	// reset global string
	stringGlobal[0] = EOS;
	
	new string[128];
	new countSkin;
	
	for(new index; index < serverCraftCount + 1; index++) {
	    // break if is a bandage
	    if (countSkin > 1) break;
	    // get model name
	    format(string, sizeof string, "%d Unid. de %s\t", CraftItens[index][CRAFT_ITEM_RESULT_AMOUNT], GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_RESULT_MODEL], CraftItens[index][CRAFT_ITEM_RESULT_TYPE]));
		strcat(stringGlobal, string);
		strcat(stringGlobal, CraftItens[index][CRAFT_ITEM_RESULT_TABLE] ? (GetPlayerLanguageKey(playerid, "NCRAFT1")) : (GetPlayerLanguageKey(playerid, "NCRAFT2")));
		strcat(stringGlobal, "\n");
		// check if is craft bandage
		if (CraftItens[index][CRAFT_ITEM_RESULT_TYPE] == ITEM_TYPE_BANDAGEMI) {
		    countSkin++;
		}
	}
	ShowPlayerDialog(playerid, DIALOG_CRAFT_LIST1, DIALOG_STYLE_TABLIST, " ", stringGlobal, "Visualizar", "Fechar");
}

stock ShowPlayerCraftList(playerid, index) {
	// check if is valid craft id
	if (index < 0 || index > serverCraftCount)
	    return 0;
	// reset global string
	stringGlobal[0] = EOS;
 	new string[128];
 	// get name of item
 	format(string, sizeof string, "{FFFFFF}%d Unid. de {AA0000}%s\n\n", CraftItens[index][CRAFT_ITEM_RESULT_AMOUNT], GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_RESULT_MODEL], CraftItens[index][CRAFT_ITEM_RESULT_TYPE]));
    strcat(stringGlobal, string);

	strcat(string, "{AA0000}RECEITA:\n\n");
	// get recipe list
 	if (CraftItens[index][CRAFT_ITEM_TYPE1] != -1) {
        format(string, sizeof string, "%s {BBBBBB}%s\n", CraftItens[index][CRAFT_ITEM_RESET1] ? ("{FF0000}+") : ("{00FF00}+"), GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_MODEL1], CraftItens[index][CRAFT_ITEM_TYPE1]));
        strcat(stringGlobal, string);
	}
 	if (CraftItens[index][CRAFT_ITEM_TYPE2] != -1) {
        format(string, sizeof string, "%s {BBBBBB}%s\n", CraftItens[index][CRAFT_ITEM_RESET2] ? ("{FF0000}+") : ("{00FF00}+"), GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_MODEL2], CraftItens[index][CRAFT_ITEM_TYPE2]));
        strcat(stringGlobal, string);
	}
 	if (CraftItens[index][CRAFT_ITEM_TYPE3] != -1) {
        format(string, sizeof string, "%s {BBBBBB}%s\n", CraftItens[index][CRAFT_ITEM_RESET3] ? ("{FF0000}+") : ("{00FF00}+"), GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_MODEL3], CraftItens[index][CRAFT_ITEM_TYPE3]));
        strcat(stringGlobal, string);
	}
 	if (CraftItens[index][CRAFT_ITEM_TYPE4] != -1) {
        format(string, sizeof string, "%s {BBBBBB}%s\n", CraftItens[index][CRAFT_ITEM_RESET4] ? ("{FF0000}+") : ("{00FF00}+"), GetItemModelTypeName(CraftItens[index][CRAFT_ITEM_MODEL4], CraftItens[index][CRAFT_ITEM_TYPE4]));
        strcat(stringGlobal, string);
	}
	// info aditional
    strcat(stringGlobal, "{444444}\n___________________________________________\n\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "NCRAFT3"));
	strcat(stringGlobal, "\n");
	strcat(stringGlobal, GetPlayerLanguageKey(playerid, "NCRAFT4"));
	strcat(stringGlobal, "\n\n");
 	
 	ShowPlayerDialog(playerid, DIALOG_CRAFT_LIST2, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Voltar", "");
 	return 1;
}

stock AddRecipe(itemname[], itemtype, itemmodel, bool:resetitem = true)
{
    #pragma unused itemname
    
    switch (serverRecipeCount)
    {
        case 0:
        {
            CraftItens[serverCraftCount][CRAFT_ITEM_TYPE1]   = itemtype;
            CraftItens[serverCraftCount][CRAFT_ITEM_MODEL1]  = itemmodel;
            CraftItens[serverCraftCount][CRAFT_ITEM_RESET1]  = resetitem;
        }
        case 1:
        {
            CraftItens[serverCraftCount][CRAFT_ITEM_TYPE2]   = itemtype;
            CraftItens[serverCraftCount][CRAFT_ITEM_MODEL2]  = itemmodel;
            CraftItens[serverCraftCount][CRAFT_ITEM_RESET2]  = resetitem;
        }
        case 2:
        {
            CraftItens[serverCraftCount][CRAFT_ITEM_TYPE3]   = itemtype;
            CraftItens[serverCraftCount][CRAFT_ITEM_MODEL3]  = itemmodel;
            CraftItens[serverCraftCount][CRAFT_ITEM_RESET3]  = resetitem;
        }
        case 3:
        {
            CraftItens[serverCraftCount][CRAFT_ITEM_TYPE4]   = itemtype;
            CraftItens[serverCraftCount][CRAFT_ITEM_MODEL4]  = itemmodel;
            CraftItens[serverCraftCount][CRAFT_ITEM_RESET4]  = resetitem;
        }
    }
    
    serverRecipeCount++;
}

// ITENS CRAFTAVEIS
stock InitItensCraftables()
{
	// Caixa de ferramentas
 	AddServerItemCraft("Caixa de ferramentas", ITEM_TYPE_TOOLBOX, 19921, 1);
    AddRecipe("Caixa vazia", 	ITEM_TYPE_CAIXAVAZIA, 19921, 	.resetitem = true);
    AddRecipe("Martelo", 		ITEM_TYPE_MARTELO, 	  18635, 	.resetitem = true);
    AddRecipe("Chave de fenda", ITEM_TYPE_CHAVEFENDA, 18644, 	.resetitem = true);
    AddRecipe("Chave de roda", 	ITEM_TYPE_CHAVERODA,  18633, 	.resetitem = true);
    
    // Fogueira
    AddServerItemCraft("Fogueira", ITEM_TYPE_FOGUEIRA, 	19793, 1);
    AddRecipe("Madeira", 		ITEM_TYPE_MADEIRA, 		19793, 	.resetitem = true);
    AddRecipe("Isqueiro", 		ITEM_TYPE_ISQUEIRO, 	-1059, 	.resetitem = false);
    AddRecipe("Panela", 		ITEM_TYPE_PANELA, 		19585, 	.resetitem = true);
    
    // Sinal de fumaça
    AddServerItemCraft("Sinal de fumaca", ITEM_TYPE_SINALFUMACA, 	343, 1, .table = true);
    AddRecipe("Caixa de polvora", 	ITEM_TYPE_CAIXA_POLVORA,2037, 	.resetitem = true);
    AddRecipe("Lata de gas", 		ITEM_TYPE_LATAGAS, 		1672, 	.resetitem = true);
    AddRecipe("Isqueiro", 			ITEM_TYPE_ISQUEIRO, 	-1059, 	.resetitem = false);
    AddRecipe("Garrafa vazia", 		ITEM_TYPE_GARRAFAV, 	1668, 	.resetitem = true);
    
    // Tranca de veiculo
    AddServerItemCraft("Tranca de veiculo", ITEM_TYPE_TRANCAV, 	2680, 1, .table = true);
    AddRecipe("Corrente", 	ITEM_TYPE_CORRENTE, 	2680, 	.resetitem = true);
    AddRecipe("Cadeado", 	ITEM_TYPE_CADEADO, 		19804, 	.resetitem = true);
    AddRecipe("Chave", 		ITEM_TYPE_KEY, 			11746, 	.resetitem = true);
    
    // Dinamite
    AddServerItemCraft("Dinamite", ITEM_TYPE_EXPLOSIVO, 	1654, 1, .table = true);
    AddRecipe("Caixa de polvora", 	ITEM_TYPE_CAIXA_POLVORA, 	   2037, 	.resetitem = true);
    AddRecipe("Chave de fenda", 	ITEM_TYPE_CHAVEFENDA,  18644, 	.resetitem = false);
    AddRecipe("Relogio", 			ITEM_TYPE_RELOGIO,     19039, 	.resetitem = true);
    AddRecipe("Celular", 			ITEM_TYPE_CELULAR,     2967, 	.resetitem = true);
    
    // C4
    AddServerItemCraft("Explosivo C4", ITEM_TYPE_EXPLOSIVOC4, 1252, 1, .table = true);
    AddRecipe("Caixa de polvora", 	ITEM_TYPE_CAIXA_POLVORA, 	   2037, 	.resetitem = true);
    AddRecipe("Chave de fenda", 	ITEM_TYPE_CHAVEFENDA,  18644, 	.resetitem = false);
    AddRecipe("Relogio", 			ITEM_TYPE_RELOGIO,     19039, 	.resetitem = true);
    AddRecipe("Teclado", 			ITEM_TYPE_TECLADO,     19305, 	.resetitem = true);
    
    // Explosivo remoto
    AddServerItemCraft("Explosivo remoto", ITEM_TYPE_EXPLOSIVORE, 	363, 1, .table = true);
    AddRecipe("Caixa de polvora", 	ITEM_TYPE_CAIXA_POLVORA, 	   2037, 	.resetitem = true);
    AddRecipe("Chave de fenda", 	ITEM_TYPE_CHAVEFENDA,  18644, 	.resetitem = false);
    AddRecipe("Celular", 			ITEM_TYPE_CELULAR,     2967, 	.resetitem = true);
    AddRecipe("Controle remoto", 	ITEM_TYPE_CONTROLE,    19920, 	.resetitem = true);
    
    AddServerItemCraft("Molotov",   ITEM_TYPE_WEAPON, 	    18, 1,  .table = false);
    AddRecipe("Garrafa vazia", 		ITEM_TYPE_GARRAFAV, 	1668, 	.resetitem = true);
    AddRecipe("Gasolina", 			ITEM_TYPE_GASOLINA, 	1650, 	.resetitem = true);
    AddRecipe("Caderno", 			ITEM_TYPE_CADERNO, 	    2894, 	.resetitem = true);
    AddRecipe("Isqueiro", 			ITEM_TYPE_ISQUEIRO, 	-1059, 	.resetitem = false);
    
    AddServerItemCraft("Tenda", 	ITEM_TYPE_BARRACA, 	    2891, 1,  .table = false);
    AddRecipe("Pe de cabra", 		ITEM_TYPE_PEDECABRA, 	18634, 	.resetitem = false);
    AddRecipe("Corda", 				ITEM_TYPE_CORDA, 		19087, 	.resetitem = true);
    AddRecipe("Couro", 				ITEM_TYPE_COURO, 	    1577, 	.resetitem = true);
    
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 3);
    AddRecipe("Faca", 			 ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Mochila pequena", ITEM_TYPE_BACKPACK1, -1012, .resetitem = true);
    
// SKINS - BANDAGENS
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN, 261, 	.resetitem = true);
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   56,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   16,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   233,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   60,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   192,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   93,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   144,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   188,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   141,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   216,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   167,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   165,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   166,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   190,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   191,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   125,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   124,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   306,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   308,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   293,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   281,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   285,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   309,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   280,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   287,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   307,	.resetitem = true);
    
    // -------------------------------------------------------------------------
    AddServerItemCraft("Bandagem improvisada", ITEM_TYPE_BANDAGEMI, 11748, 2);
    AddRecipe("Faca", 			ITEM_TYPE_WEAPON, 4, 	.resetitem = false);
    AddRecipe("Qualquer roupa", ITEM_TYPE_SKIN,   309,	.resetitem = true);
}

// Stocks

stock resetPlayerCraft(playerid) {

	for(new index; index < 4; index++) {
		PlayerCraftItens[playerid][craft_item][index] 	   = -1;
		PlayerCraftItens[playerid][craft_item_type][index] = -1;
		PlayerCraftItens[playerid][craft_item_slot][index] = -1;
	}
	
	PlayerData[playerid][dCraftId] = -1;
	
	// Atualizar textdraws
	updatePlayerCraftTextDraws(playerid);
}

stock addPlayerCraftItem(playerid, slotid, itemid) {

	for(new index; index < 4; index++) {
	    if (PlayerCraftItens[playerid][craft_item_slot][index] == itemid) return 0;
	}

	PlayerCraftItens[playerid][craft_item][slotid] 	    = InventarioInfo[playerid][itemid][item_model];
	PlayerCraftItens[playerid][craft_item_type][slotid] = InventarioInfo[playerid][itemid][item_type];
	PlayerCraftItens[playerid][craft_item_slot][slotid] = itemid;
	
	// Atualizar textdraws
	updatePlayerCraftTextDraws(playerid);
	
	return 1;
}

stock craftPlayerItem(playerid) {

    new result_type, result_model, result_quantia, index = PlayerData[playerid][dCraftId];
    
    if (index == -1)
        return 0;
    
	result_type    = CraftItens[index][CRAFT_ITEM_RESULT_TYPE];
 	result_model   = CraftItens[index][CRAFT_ITEM_RESULT_MODEL];
  	result_quantia = CraftItens[index][CRAFT_ITEM_RESULT_AMOUNT];
  	new slots = getItemModelSlots(result_model);
  	
  	if (CraftItens[index][CRAFT_ITEM_RESULT_TABLE] && !IsPlayerInCraftTable(playerid)) {
  	    SendLanguageMessage(playerid, corError, "MSG_103");
  	    return -1;
	}
  	
  	if (!isInventoryFreeSpace(playerid, slots)) {
  	    SendLanguageMessagef(playerid, corError, "MSG_104", slots);
  	    return -1;
  	}
  	
  	new itens[8];
  	new itens_type[4];
  	new bool:reset[4];
  	
  	itens_type[0] = CraftItens[index][CRAFT_ITEM_TYPE1];
  	itens_type[1] = CraftItens[index][CRAFT_ITEM_TYPE2];
  	itens_type[2] = CraftItens[index][CRAFT_ITEM_TYPE3];
  	itens_type[3] = CraftItens[index][CRAFT_ITEM_TYPE4];
  	
  	itens[0] = CraftItens[index][CRAFT_ITEM_MODEL1];
  	itens[1] = CraftItens[index][CRAFT_ITEM_MODEL2];
  	itens[2] = CraftItens[index][CRAFT_ITEM_MODEL3];
  	itens[3] = CraftItens[index][CRAFT_ITEM_MODEL4];
  	
  	reset[0] = CraftItens[index][CRAFT_ITEM_RESET1];
  	reset[1] = CraftItens[index][CRAFT_ITEM_RESET2];
  	reset[2] = CraftItens[index][CRAFT_ITEM_RESET3];
  	reset[3] = CraftItens[index][CRAFT_ITEM_RESET4];
  	
  	for(new i; i < 4; i++) {
  	
  	    for(new p; p < 4; p++) {

			if (PlayerCraftItens[playerid][craft_item][i] == itens[p] && PlayerCraftItens[playerid][craft_item_type][i] == itens_type[p] && reset[p]) {

				resetItem(playerid, PlayerCraftItens[playerid][craft_item_slot][i], false);

				break;
	    	}
  	    }
  	}
  	
  	reorganizarItens(playerid);
  	
  	givePlayerItem(playerid, result_type, result_model, result_quantia, GetItemModelTypeName(result_model, result_type));
  	
	resetPlayerCraft(playerid);
	
	Audio_Play(playerid, 44);
	
	StartPlayerProgress(playerid, "Craftando...", 60,  3.0);
	
	givePlayerPoints(playerid, 250, .point_3d = 0);
	
	Log::("craft", "Item\t|%s criou %s com %d unid", getNome(playerid), GetItemModelTypeName(result_model, result_type), result_quantia);
	
  	return 1;
}

stock updatePlayerCraftTextDraws(playerid) {

	new string[256];
	new textname[25];

	for(new index; index < 4; index++) {

		new itemid = PlayerCraftItens[playerid][craft_item_slot][index];
		
		if (itemid != -1) {
		    format(textname, sizeof textname, "mdl-1005:%d", InventarioInfo[playerid][itemid][item_model]);
		    PlayerTextDrawSetString(playerid, playerTextDrawsCraft[index + 1], textname);
		    
		    format(string, sizeof string, "%s%s~n~~n~~n~", string, InventarioInfo[playerid][itemid][item_nome]);
		} else {
			PlayerTextDrawSetString(playerid, playerTextDrawsCraft[index + 1], "mdl-1005:-999");
			
			format(string, sizeof string, "%s_~n~~n~~n~", string);
		}
	}
	
	// Mostrar resultado
	new resulttype, resultmodel, resultquantia;
	
	PlayerData[playerid][dCraftId] = StartCraftItens(playerid, resulttype, resultmodel, resultquantia);
	
	if (resulttype != ITEM_TYPE_NONE) {
	
	    new modelview = resultmodel;

		format(textname, sizeof textname, "mdl-1005:%d", modelview);
		PlayerTextDrawSetString(playerid, playerTextDrawsCraft[5], textname);
		
		format(string, sizeof string, "%s~n~%s (%d Unid.)~n~~n~~n~", string, GetItemModelTypeName(resultmodel, resulttype), resultquantia);
	} else {
		PlayerTextDrawSetString(playerid, playerTextDrawsCraft[5], "mdl-1005:-999");
		
		format(string, sizeof string, "%s~n~_~n~~n~~n~", string);
	}
	
	PlayerTextDrawSetString(playerid, playerTextDrawsCraft[8], string);
}

stock StartCraftItens(playerid, &result_type, &result_model, &result_quantia) {

	// player itens
	new model_1 = PlayerCraftItens[playerid][craft_item][0];
	new type_1  = PlayerCraftItens[playerid][craft_item_type][0];
	
	new model_2 = PlayerCraftItens[playerid][craft_item][1];
	new type_2  = PlayerCraftItens[playerid][craft_item_type][1];
	
	new model_3 = PlayerCraftItens[playerid][craft_item][2];
	new type_3  = PlayerCraftItens[playerid][craft_item_type][2];
	
	new model_4 = PlayerCraftItens[playerid][craft_item][3];
	new type_4  = PlayerCraftItens[playerid][craft_item_type][3];

    // tentar combinar
    
    new somaCraft[2];
    
	for(new index; index < serverCraftCount; index++) {
	
	    somaCraft[0] =
						model_1 + type_1 + model_2 + type_2 + model_3 + type_3 + model_4 + type_4;
						
	    somaCraft[1] =
						CraftItens[index][CRAFT_ITEM_MODEL1] + CraftItens[index][CRAFT_ITEM_TYPE1] +
						CraftItens[index][CRAFT_ITEM_MODEL2] + CraftItens[index][CRAFT_ITEM_TYPE2] +
						CraftItens[index][CRAFT_ITEM_MODEL3] + CraftItens[index][CRAFT_ITEM_TYPE3] +
						CraftItens[index][CRAFT_ITEM_MODEL4] + CraftItens[index][CRAFT_ITEM_TYPE4];
	
//	    printf("soma: %d - %d", somaCraft[0], somaCraft[1]);
	
		if (somaCraft[0] == somaCraft[1] && somaCraft[1] > 0) {
		    result_type    = CraftItens[index][CRAFT_ITEM_RESULT_TYPE];
		    result_model   = CraftItens[index][CRAFT_ITEM_RESULT_MODEL];
		    result_quantia = CraftItens[index][CRAFT_ITEM_RESULT_AMOUNT];
	    	return index;
		}
	}
	
	// Reset result
   	result_type    = ITEM_TYPE_NONE;
    result_model   = 0;
    result_quantia = 0;
    
    return -1;
}






