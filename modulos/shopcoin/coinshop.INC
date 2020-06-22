
enum shopEnum {

	shopName[25],
	shopType,
	shopModel,
	shopQuant,
	shopCost,
}

stock const Shop_Array[][shopEnum] = {
/*
N: Nome
T: Tipo
M: Modelo
Q: Quantidade
P: Preço
         N                              T                  M    Q        P                               */
	{"Bandagem",        		ITEM_TYPE_BANDAGE, 	     11747, 1, 		800},
	{"Remedio",  				ITEM_TYPE_REMEDIO, 	     11738, 1, 		800},
	{"Remedio pequeno", 		ITEM_TYPE_REMEDIOP, 	 11736, 1, 		800},
	{"Mochila Pequena",        	ITEM_TYPE_BACKPACK1, 	 363,   1, 		800},
	{"Mochila Media",        	ITEM_TYPE_BACKPACK2, 	 371,   1, 		800},
	{"Mochila Grande",        	ITEM_TYPE_BACKPACK3, 	 19559, 1, 		800},
	{"Bussola",   				ITEM_TYPE_BUSSOLA,    	 18875, 1, 		800},
	{"Motor",        			ITEM_TYPE_MOTOR, 	     19917, 1, 		800},
	{"Pneu",  					ITEM_TYPE_PNEU, 	     1077,  1, 		800},
	{"Toolbox",  				ITEM_TYPE_TOOLBOX, 	     19921, 1, 		800},
	{"Mapa",            		ITEM_TYPE_MAP,           3017,  1, 		800},
	{"Tenda",        			ITEM_TYPE_TENDA, 	     1279,  1, 		800},
    {"Faca",   					ITEM_TYPE_WEAPON,    	 4,   	1, 		800},
    {"9mm",   					ITEM_TYPE_WEAPON,    	 22,  	15, 	800},
    {"Silenciadora",   			ITEM_TYPE_WEAPON,    	 23,  	15, 	800},
	{"Desert Eagle",   			ITEM_TYPE_WEAPON,    	 24,  	15, 	800},
	{"Calibre 12",      		ITEM_TYPE_WEAPON,      	 25,  	10, 	800},
	{"MP5",  					ITEM_TYPE_WEAPON,  	 	 29,  	50, 	800},
	{"AK-47",  					ITEM_TYPE_WEAPON, 	 	 30,  	50, 	800},
	{"M4A1",  					ITEM_TYPE_WEAPON, 	     31,  	25, 	800},
	{"Espingarda",  			ITEM_TYPE_WEAPON, 	     33,  	10, 	800},
	{"Sniper", 					ITEM_TYPE_WEAPON, 	 	 34,  	5, 		800},
	{"Visao Termica", 			ITEM_TYPE_WEAPON, 	 	 45,  	1, 		800},
	{"Mina terrestre",  		ITEM_TYPE_MINA, 	     19602, 1, 		800},
	
	{"Silenciadora Ammo", 		ITEM_TYPE_AMMO_SILENCER, 2041,  100, 	800},
	{"Desert Eagle Ammo", 		ITEM_TYPE_AMMO_DEAGLE, 	 2041,  100, 	800},
	{"Calibre 12 Ammo", 		ITEM_TYPE_AMMO_SHOTGUN,  2041,  100, 	800},
	{"MP5 Ammo", 				ITEM_TYPE_AMMO_MP5, 	 2041,  100, 	800},
	{"AK-47 Ammo", 				ITEM_TYPE_AMMO_AK47, 	 2041,  100, 	800},
	{"M4A1 Ammo", 				ITEM_TYPE_AMMO_M4, 		 2041,  100, 	800},
	{"Espingarda Ammo", 		ITEM_TYPE_AMMO_RIFLE, 	 2041,  100, 	800},
 	{"Sniper Ammo", 			ITEM_TYPE_AMMO_SNIPER, 	 2041,  100, 	800},
 	{"9mm Ammo", 				ITEM_TYPE_AMMO_9MM, 	 2041,  100, 	800}
};


// Stocks/Callbacks

#define IsPlayerInShop(%0) 	  (GetPVarInt(%0, "shopCoin"))
#define GetPlayerPageShop(%0) (GetPVarInt(%0, "pageShopCoin"))
#define GetShopMaxPages       ((sizeof (Shop_Array) / 6) + 1)

stock showPlayerShop(playerid) {

	if (IsPlayerInShop(playerid)) return 0;
	
	// Fix bug
	if (GetPlayerPageShop(playerid) == 0) {
	    SetPVarInt(playerid, "pageShopCoin", 1);
	}
	
	// Mostrar as TextDraws
	for(new text; text != sizeof (textShopCoins); text++) {
	    TextDrawShowForPlayer(playerid, textShopCoins[text]);
	}
	
  	PlayerTextDrawShow(playerid, textPlayerShopCoins[playerid]);
	
	// Update na pagina
	updatePlayerPageShop(playerid);
	
	// Setar a PVar
	SetPVarInt(playerid, "shopCoin", 1);
	
	// Selecionar as textdraws
	SelectTextDraw(playerid, 0x444444AA);
	
	return 1;
}

stock OnPlayerSelectShopItem(playerid, itemid) {

	new string[128];

	stringGlobal[0] = EOS;
	
	strcat(stringGlobal, "{FFFFFF}| ------------------------------------------------------------------------- |\n\n");
	strcat(stringGlobal, "| Informações do item:");
	strcat(stringGlobal, "\n\n");
	format(string, sizeof string, "{00AAFF}| Nome do item: {FFFFFF}%s", Shop_Array[itemid][shopName]);
	strcat(stringGlobal, string);
	strcat(stringGlobal, "\n");
	format(string, sizeof string, "{00AAFF}| Unidades: {FFFFFF}%d", Shop_Array[itemid][shopQuant]);
	strcat(stringGlobal, string);
	strcat(stringGlobal, "\n");
	format(string, sizeof string, "{00AAFF}| Preço: {FFFFFF}%d Cash", Shop_Array[itemid][shopCost]);
	strcat(stringGlobal, string);
	strcat(stringGlobal, "\n\n");
	strcat(stringGlobal, "{FFFFFF}| ------------------------------------------------------------------------- |");
	
	ShowPlayerDialog(playerid, DIALOG_BUY_ITEM, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Comprar", "Cancelar");
	
	SetPVarInt(playerid, "buyItem", itemid);
}

stock updatePlayerPageShop(playerid) {

	new currentItem = (GetPlayerPageShop(playerid) - 1) * 6;
	new lastItem    = (currentItem + 6);
	new string_shop [75];
	
	if (lastItem >= sizeof (Shop_Array)) {

		for(new current; current < 6; current++) {

			PlayerTextDrawHide(playerid, textPlayerShopModel[current][playerid]);
			PlayerTextDrawHide(playerid, textPlayerShopName[current][playerid]);
			TextDrawHideForPlayer(playerid, textShopCoins[current + 3]);
		}
		lastItem = sizeof (Shop_Array) - 1;
	}

	for(new item = currentItem, current; item < lastItem; item++, current++) {
	
	    // Nome do item
	    format(string_shop, sizeof (string_shop), "%s x%d~n~~n~~b~~h~%d cash", Shop_Array[item][shopName],Shop_Array[item][shopQuant],Shop_Array[item][shopCost]);
		PlayerTextDrawSetString(playerid, textPlayerShopName[current][playerid], string_shop);
		PlayerTextDrawShow(playerid, textPlayerShopName[current][playerid]);
		
		// Modelo do item
		if (Shop_Array[item][shopType] == ITEM_TYPE_WEAPON) {
		    PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[current][playerid], ObjectsArmas[Shop_Array[item][shopModel]]);
		} else {
			PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[current][playerid], Shop_Array[item][shopModel]);
		}
		PlayerTextDrawShow(playerid, textPlayerShopModel[current][playerid]);
		TextDrawShowForPlayer(playerid, textShopCoins[current + 3]);
	}
	
	// Atualizar a quantidade de coins/pagina

	format(string_shop, sizeof (string_shop), "%d-%d", GetPlayerPageShop(playerid), GetShopMaxPages);
	PlayerTextDrawSetString(playerid, textPlayerShopCoins[playerid], string_shop);
}

stock hidePlayerShop(playerid) {

	// Esconder as TextDraws
	for(new text; text != sizeof (textShopCoins); text++) {
	    TextDrawHideForPlayer(playerid, textShopCoins[text]);
	}

    PlayerTextDrawHide(playerid, textPlayerShopCoins[playerid]);

	for(new text; text < 6; text++) {
		PlayerTextDrawHide(playerid, textPlayerShopModel[text][playerid]);
		PlayerTextDrawHide(playerid, textPlayerShopName[text][playerid]);
	}

	// Cancelar a seleção de TextDraws
	CancelSelectTextDraw(playerid);

	// Deletar a PVar
	DeletePVar(playerid, "shopCoin");
}


public OnPlayerClickTextDraw(playerid, Text:clickedid)
{

	if (IsPlayerInShop(playerid)) {

        if (clickedid == Text:INVALID_TEXT_DRAW) {
            hidePlayerShop(playerid);
        }

	    else if (clickedid == textShopCoins[9]) {

	        if ( GetPlayerPageShop(playerid) <= 1 ) return 0;
	        
	        // Diminuir uma página
	        SetPVarInt(playerid, "pageShopCoin", GetPlayerPageShop(playerid) - 1);
	        
	        // Atualizar a página
	        updatePlayerPageShop(playerid);
	        
	        // Efeito de som
	        Audio_Play(playerid, 25);
	    }

 	    else if (clickedid == textShopCoins[10]) {

	        if ( GetPlayerPageShop(playerid) >= GetShopMaxPages ) return 0;

	        // Diminuir uma página
	        SetPVarInt(playerid, "pageShopCoin", GetPlayerPageShop(playerid) + 1);

	        // Atualizar a página
	        updatePlayerPageShop(playerid);
	        
	        // Efeito de som
	        Audio_Play(playerid, 25);
	    }
	    
	    else if (clickedid == textShopCoins[12]) {
	        hidePlayerShopCoin(playerid);
	    }
	    
		for(new text; text < 6; text++) {

		    if (clickedid == textShopCoins[text + 3]) {

		        OnPlayerSelectShopItem(playerid, text + ((GetPlayerPageShop(playerid) - 1) * 6));
		        break;
		    }
		}
	}

 	#if defined sOnPlayerClickTextDraw
  		return sOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw sOnPlayerClickTextDraw
#if defined sOnPlayerClickTextDraw
	forward sOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

/*
CMD:shop(playerid) {

    showPlayerShopCoin(playerid);
	return 1;
}*/
