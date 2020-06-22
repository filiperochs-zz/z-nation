
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
	{"Bandagem",        		ITEM_TYPE_BANDAGE, 	     11747, 1,      800},
	{"Mochila Pequena",        	ITEM_TYPE_BACKPACK1, 	 -1012, 1,      950},
    {"Mochila Media",        	ITEM_TYPE_BACKPACK2, 	 -1013, 1,      1200},
	{"Mochila Grande",        	ITEM_TYPE_BACKPACK3, 	 -1014, 1,      1850},
    {"Pneu",   					ITEM_TYPE_PNEU,    	 	 1077,  1,      4200},
	{"Bussola",   				ITEM_TYPE_BUSSOLA,    	 18875, 1,      925},
    {"Garrafa vazia",     		ITEM_TYPE_GARRAFAV, 	 1668,  1,      300},
    {"Lata de gas", 		    ITEM_TYPE_LATAGAS, 	     1672,  1,      550},
    {"Teclado", 		        ITEM_TYPE_TECLADO, 	     19305, 1,      695},
    {"Saco de carvao", 		    ITEM_TYPE_CARVAO, 	     19573, 1,      800},
    {"Binoculos",   			ITEM_TYPE_WEAPON,    	 43,  	1,      900},
	{"Remedio pequeno", 		ITEM_TYPE_REMEDIOP, 	 11736, 1,      745},
	{"Mascara de gas", 		    ITEM_TYPE_GASMASK, 	     -1020, 1,      1125},
	{"Mapa",            		ITEM_TYPE_MAP,           3017,  1,      740},
	{"Caixa vazia",  			ITEM_TYPE_CAIXAVAZIA, 	 19921, 1,      250},
    {"Panela",				    ITEM_TYPE_PANELA, 	     19585, 1,      125},
    {"Carteira de cigarro",     ITEM_TYPE_CIGARRO, 	     19897, 7,      150},
    {"Peixe",     				ITEM_TYPE_PEIXE, 	     19630, 1,      300},
    {"Isqueiro",     			ITEM_TYPE_ISQUEIRO, 	 -1059, 1,      580},
    {"Cadeado",     			ITEM_TYPE_CADEADO, 	 	 19804, 1,      365},
    {"Marreta",     			ITEM_TYPE_WEAPON, 	 	 5, 	1,      700},
    {"Facao",   				ITEM_TYPE_WEAPON,    	 8, 	1,      700},
    {"Martelo",     			ITEM_TYPE_MARTELO, 	 	 18635, 1,      500},
    {"Chave de fenda",     		ITEM_TYPE_CHAVEFENDA, 	 18644, 1,      500},
    {"Chave de roda",     		ITEM_TYPE_CHAVERODA, 	 18633, 1,      500},
    {"Pe de cabra",     		ITEM_TYPE_PEDECABRA, 	 18634, 1,      500},
    {"Painkiller", 		    	ITEM_TYPE_PAINKILLER, 	 -1025, 1,      960},
    {"Radio", 		    	    ITEM_TYPE_RADIO, 	     2966,  1,      1000},
    {"Relogio", 		    	ITEM_TYPE_RELOGIO, 	     19039, 1,      450},
    {"Corrente", 		    	ITEM_TYPE_CORRENTE,    	 2680,  1,      150},
    {"Extintor",   				ITEM_TYPE_WEAPON,    	 42,  	500,    1200},
    {"Caderno",   				ITEM_TYPE_CADERNO,    	 2894,  1,      100},
    {"Garfo",   				ITEM_TYPE_GARFO,    	 11715, 1,      95},
    {"Faca de cozinha",   		ITEM_TYPE_FACACOZINHA,   11716, 1,      95},
    {"Espatula",   				ITEM_TYPE_ESPATULA,   	 19586, 1,      95},
    {"Chave",   				ITEM_TYPE_KEY,   		 11746, 1,      500},
    {"Lanterna", 		    	ITEM_TYPE_LANTERNA, 	 18641, 1,      850},
    {"Cartao", 		    		ITEM_TYPE_CARTAO, 	 	 19792, 1,      700},
    {"Fita de video", 		   	ITEM_TYPE_FITA, 	 	 19814, 1,      400},
    {"Tigela", 		   			ITEM_TYPE_TIGELA, 	 	 19993, 1,      300},
    {"Disco de vinil", 		   	ITEM_TYPE_DISCO, 	 	 1960,  1,      150},
    {"Celular",   				ITEM_TYPE_CELULAR,    	 2967,  1,      350},
    {"Vara de pescar",   		ITEM_TYPE_VARA,    	 	 18632, 1,      745},
    {"Ancinho",   				ITEM_TYPE_ANCINHO,    	 18890, 1,      255},
    {"Cano",   					ITEM_TYPE_CANO,    	 	 19348, 1,      180},
    {"Balde",   				ITEM_TYPE_BALDE,    	 19468, 1,      100},
    {"Bateria",   				ITEM_TYPE_BATERIA,    	 3016,  1,      1500},
    {"Giroscopio",   			ITEM_TYPE_GIROSCOPIO,    1945,  1,      600},
    {"Maleta",   				ITEM_TYPE_MALETA,    	 1210,  1,      525},
    {"Chave de boca",   		ITEM_TYPE_CHAVEBOCA,     19627, 1,      500},
    {"Lata de oleo",   			ITEM_TYPE_LATAOLEO,      19621, 1,      300},
    {"Vassoura",   				ITEM_TYPE_VASSOURA,    	 19622, 1,      400},
    {"Controle remoto",   		ITEM_TYPE_CONTROLE,    	 19920, 1,      955},
    {"Capacete (Level 1)",   	ITEM_TYPE_HELMETLVL1,    -1006, 1,      1000}
};

static const Float: EntersDealer[][] = {
	{263.4087,21.5002,3.4332},
	{-1532.9003,2656.6895,56.2814},
	{-2244.8455,2382.1687,5.0710},
	{-2552.3354,55.0987,16.4219},
	{-2190.7952,-2327.4702,30.6250},
	{-283.1528,-2174.6311,28.6641},
	{1470.7056,-1847.6110,13.5469},
	{223.1966,1931.4866,17.6406}
};

static CP_ShopEnters[sizeof (EntersDealer)];
static CP_ShopExit;
static CP_DealerShop;

// Stocks/Callbacks

#define IsPlayerInShop(%0) 	  (GetPVarInt(%0, "shopCoin"))
#define GetPlayerPageShop(%0) (GetPVarInt(%0, "pageShopCoin"))
#define GetShopMaxPages       ((sizeof (Shop_Array) / 6) + 1)

stock CreateDealerEnterExits() {

	// Enters
	for (new e; e < sizeof (EntersDealer); e++)
	{
	    CP_ShopEnters[e] = CreateDynamicCP(EntersDealer[e][0], EntersDealer[e][1], EntersDealer[e][2], 1.0, 0);
	    CreateDynamicActor(25000, 289.8398, 24.6469, 1001.5002, 2.6814, .invulnerable = 1, .health = 100.0, .worldid = e);
	}
	
	// Exit
	CP_ShopExit = CreateDynamicCP(279.9380, 20.0980, 1001.4483 - 1.0, 1.5);
	CP_DealerShop = CreateDynamicCP(289.5316,26.5957,1001.4440 - 1.0, 1.5);
	
	//CreateDynamicActor(230, 289.8398, 24.6469, 1001.5002, 2.6814, .invulnerable = 1, .health = 100.0, .worldid = -1);
}

public OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP checkpointid)
{
	if (gettime() < GetPVarInt(playerid, "lastEnterDealer"))
		return 1;
		
	for (new e; e < sizeof (EntersDealer); e++)
	{
	    if (CP_ShopEnters[e] == checkpointid)
	    {
	        SetPlayerPos(playerid, 281.9540,20.7875,1001.4551, .freezetime = 3000, .showloading = 1);
	        SetPlayerFacingAngle(playerid, 339.1092);
	        SetPlayerInterior(playerid, 10);
	        SetPlayerVirtualWorld(playerid, e);
	        return 1;
	    }
	}
	
	if (checkpointid == CP_ShopExit)
	{
	    new e = GetPlayerVirtualWorld(playerid);

	    if (e < 0 || e > sizeof (EntersDealer))
			e = 0;

	    SetPlayerPos(playerid, EntersDealer[e][0], EntersDealer[e][1], EntersDealer[e][2], .freezetime = 2000);
     	SetPlayerVirtualWorld(playerid, 0);
     	SetPlayerInterior(playerid, 0);

     	// save last enter time
     	SetPVarInt(playerid, "lastEnterDealer", gettime() + 5);
	}
	
	else if (checkpointid == CP_DealerShop)
	{
	    showPlayerShop(playerid);
	}
	
	return 1;
}

public OnPlayerLeaveDynamicCP(playerid, STREAMER_TAG_CP checkpointid)
{
	return 1;
}

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
	format(string, sizeof string, "{00AAFF}| Preço: {FFFFFF}$%s", getMoneyFormat(Shop_Array[itemid][shopCost] * 2));
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
		lastItem = sizeof (Shop_Array) ;
	}

	for(new item = currentItem, current; item < lastItem; item++, current++) {
	
	    // Nome do item
	    format(string_shop, sizeof (string_shop), "%s x%d~n~~n~~g~~h~~h~$%s", Shop_Array[item][shopName],Shop_Array[item][shopQuant],getMoneyFormat(Shop_Array[item][shopCost] * 2));
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
	        hidePlayerShop(playerid);
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
