
enum E_CRAFT_WEAPONS {

	w_name[75],
	w_type,
	w_model,
	w_quantidade,
	w_brokenweapon,
	w_pecas,
	w_polvora,
}

stock const craftWeapons[][E_CRAFT_WEAPONS] = {
//  Nome                        type                     model  quantia    brokenweapon       pecas       polvora
    {"9mm",   					ITEM_TYPE_WEAPON,    	 22,  	0,         1,                 15,         0},
    {"Silenciadora",   			ITEM_TYPE_WEAPON,    	 23,  	0,         1,                 21,         0},
	{"Desert Eagle",   			ITEM_TYPE_WEAPON,    	 24,  	0,         1,                 19,         0},
	{"Calibre 12",      		ITEM_TYPE_WEAPON,      	 25,  	0,         1,                 29,         0},
	{"MP5",  					ITEM_TYPE_WEAPON,  	 	 29,  	0,         1,                 31,         0},
	{"AK-47",  					ITEM_TYPE_WEAPON, 	 	 30,  	0,         1,                 40,         0},
	{"M4A1",  					ITEM_TYPE_WEAPON, 	     31,  	0,         1,                 45,         0},
	{"Espingarda",  			ITEM_TYPE_WEAPON, 	     33,  	0,         1,                 35,         0},
	{"Sniper", 					ITEM_TYPE_WEAPON, 	 	 34,  	0,         1,                 48,         0},
	{"Micro SMG",   			ITEM_TYPE_WEAPON,    	 28,  	0,         1,                 26,         0},
	{"Tec 9",   				ITEM_TYPE_WEAPON,    	 32,  	0,         1,                 22,         0},

	{".357mm rounds", 			ITEM_TYPE_AMMO_DEAGLE, 	 -1040,  10,        0,                 15,         45},
	{"15.6mm rounds", 			ITEM_TYPE_AMMO_SHOTGUN,  -1038,  15,        0,                 15,         30},
	{"9x19mm rounds", 			ITEM_TYPE_AMMO_MP5, 	 -1035,  10,        0,                 15,         56},
	{"7.62mm rounds", 			ITEM_TYPE_AMMO_AK47, 	 -1042,  10,        0,                 15,         85},
	{"5.56mm rounds", 			ITEM_TYPE_AMMO_M4, 		 -1041,  15,        0,                 15,         92},
	{"5.5mm rounds", 			ITEM_TYPE_AMMO_RIFLE, 	 -1037,  10,        0,                 15,         50},
 	{".50mm rounds", 			ITEM_TYPE_AMMO_SNIPER, 	 -1036,  10,        0,                 15,         99},
 	{".9mm rounds", 			ITEM_TYPE_AMMO_9MM, 	 -1034,  10,        0,                 15,         48}
};

// Textdraws
new Text:weaponsCraft[6];
new PlayerText:PlayerWeaponCraft[11];

// Page weapon craft
new playerPageWeapon[MAX_PLAYERS];

#define MaxPagesWeaponCraft() ((sizeof(craftWeapons)/4))

stock showPlayerWeaponsCraft(playerid)
{
	if (GetPVarInt(playerid, "p_viewcraft"))
		return 0;

	// reset selected
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[9], 999);
	PlayerTextDrawSetString(playerid, PlayerWeaponCraft[10], "_");

	new id = sizeof (PlayerWeaponCraft);
	
	while (id--)
	{
	    if (id > 7)
	    {
	    	PlayerTextDrawShow(playerid, PlayerWeaponCraft[id]);
		}
	    
	    if (id < 6)
	    {
			TextDrawShowForPlayer(playerid, weaponsCraft[id]);
	    }
	}
	
	SetPVarInt(playerid, "p_selectitem", -1);
	
	SetPVarInt(playerid, "p_viewcraft", 1);
	
	playerPageWeapon[playerid] = 0;
	
	// Update textdraws select
	UpdatePlayerWeaponCraft(playerid);
	
	SelectTextDraw(playerid, 0xBBBBBBFF);
	
	return 1;
}

stock hidePlayerWeaponsCraft(playerid)
{
	if (!GetPVarInt(playerid, "p_viewcraft"))
		return 0;

	new id = sizeof (PlayerWeaponCraft);

	while (id--)
	{
	   	PlayerTextDrawHide(playerid, PlayerWeaponCraft[id]);

	    if (id < 6)
	    {
			TextDrawHideForPlayer(playerid, weaponsCraft[id]);
	    }
	}

	DeletePVar(playerid, "p_viewcraft");
	DeletePVar(playerid, "p_selectitem");

	CancelSelectTextDraw(playerid);

	return 1;
}

stock UpdatePlayerWeaponCraft(playerid)
{
	new pageid = playerPageWeapon[playerid];
	
	new string[75];
	
	for(new index; index < 4; index++)
	{
 		PlayerTextDrawHide(playerid, PlayerWeaponCraft[index]);
   		PlayerTextDrawHide(playerid, PlayerWeaponCraft[index + 4]);
	}
	
	for(new text, index = pageid * 4; index < sizeof (craftWeapons); index++, text++)
	{
	    format(string, sizeof string, "%s [%d]", craftWeapons[index][w_name], craftWeapons[index][w_quantidade]);
	    PlayerTextDrawSetString(playerid, PlayerWeaponCraft[text + 4], string);
	
	    PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[text], craftWeapons[index][w_type] == ITEM_TYPE_WEAPON ? (getWeaponObjectModel(craftWeapons[index][w_model])) : (craftWeapons[index][w_model]));
	
 		PlayerTextDrawShow(playerid, PlayerWeaponCraft[text]);
   		PlayerTextDrawShow(playerid, PlayerWeaponCraft[text + 4]);
   		
   		if (text >= 4)
   			break;
	}
	
	format(string, sizeof string, "%d-%d", pageid + 1, MaxPagesWeaponCraft() + 1);
	PlayerTextDrawSetString(playerid, PlayerWeaponCraft[8], string);
	
	return 1;
}

stock UpdatePlayerSelectedWeapon(playerid, index)
{
	// Item selected
	SetPVarInt(playerid, "p_selectitem", index);
	
	if (index > -1 && index < sizeof craftWeapons)
	{
		new
		    string[128];
		PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[9], craftWeapons[index][w_type] == ITEM_TYPE_WEAPON ? (getWeaponObjectModel(craftWeapons[index][w_model])) : (craftWeapons[index][w_model]));
		PlayerTextDrawShow(playerid, PlayerWeaponCraft[9]);
		
		format(string, sizeof string, "%s [%d]~n~~n~", craftWeapons[index][w_name], craftWeapons[index][w_quantidade]);
		
		if (craftWeapons[index][w_brokenweapon])
		    format(string, sizeof string, "%sx%d Arma quebrada~n~", string, craftWeapons[index][w_brokenweapon]);
		
		if (craftWeapons[index][w_pecas])
		    format(string, sizeof string, "%sx%d Pecas de armas~n~", string, craftWeapons[index][w_pecas]);
		
		if (craftWeapons[index][w_polvora])
		    format(string, sizeof string, "%sx%d Polvora~n~", string, craftWeapons[index][w_polvora]);
		
		PlayerTextDrawSetString(playerid, PlayerWeaponCraft[10], string);
	}
}

stock ConstroyWeaponCraft(playerid)
{
	new index = GetPVarInt(playerid, "p_selectitem");
	
	if (index == -1)
	    return 0;

	if (!IsPlayerHaveItemQuantiaEx(playerid, ITEM_TYPE_ARMAQUEBRADA, craftWeapons[index][w_brokenweapon]) ||
        !IsPlayerHaveItemQuantiaEx(playerid, ITEM_TYPE_PECAARMA, craftWeapons[index][w_pecas]) ||
        !IsPlayerHaveItemQuantiaEx(playerid, ITEM_TYPE_POLVORA, craftWeapons[index][w_polvora]))
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você não tem os recursos necessários para criar este item.");
        
	new slots = getItemModelSlots(craftWeapons[index][w_model]);
        
	if (!isInventoryFreeSpace(playerid, slots))
        return SendLanguageMessagef(playerid, corError, "MSG_073", slots);
        
    RemoveQuantiaItem(playerid, ITEM_TYPE_ARMAQUEBRADA, craftWeapons[index][w_brokenweapon]);
    RemoveQuantiaItem(playerid, ITEM_TYPE_PECAARMA, craftWeapons[index][w_pecas]);
    RemoveQuantiaItem(playerid, ITEM_TYPE_POLVORA, craftWeapons[index][w_polvora]);
        
    givePlayerItem(playerid, craftWeapons[index][w_type], craftWeapons[index][w_model], craftWeapons[index][w_quantidade], craftWeapons[index][w_name]);
        
	Audio_Play(playerid, 44);

	StartPlayerProgress(playerid, "Craftando...", 60,  3.0);
	
	givePlayerPoints(playerid, 350, .point_3d = 0);
	
	Log::("craft", "Weapon\t|%s criou %s com %d unid", getNome(playerid), craftWeapons[index][w_name], craftWeapons[index][w_quantidade]);
        
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "p_viewcraft"))
	{
	    if (IsPlayerInProgress(playerid))
	    {
	        SendClientMessage(playerid, corCinza, "Aguarde...");
	        SelectTextDraw(playerid, 0xBBBBBBFF);
	        return 0;
		}
	
	    // page preview
	    if (clickedid == weaponsCraft[2])
	    {
	        if (playerPageWeapon[playerid] > 0)
	        {
	            playerPageWeapon[playerid] --;
	            
	            UpdatePlayerWeaponCraft(playerid);
	        }
	    }
	    // page next
	    else if (clickedid == weaponsCraft[3])
	    {
	        if (playerPageWeapon[playerid] < MaxPagesWeaponCraft())
	        {
	            playerPageWeapon[playerid] ++;
	            
	            UpdatePlayerWeaponCraft(playerid);
	        }
	    }
	    
	    // construir
	    else if (clickedid == weaponsCraft[4])
	    {
	        ConstroyWeaponCraft(playerid);
	    }
	    
	    // exit
	    else if (clickedid == weaponsCraft[5] || clickedid == Text:INVALID_TEXT_DRAW)
	    {
	        hidePlayerWeaponsCraft(playerid);
	    }
	}
 	#if defined yOnPlayerClickTextDraw
  		return yOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw yOnPlayerClickTextDraw
#if defined yOnPlayerClickTextDraw
	forward yOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (GetPVarInt(playerid, "p_viewcraft"))
	{
	    if (IsPlayerInProgress(playerid))
	    {
	        SendClientMessage(playerid, corCinza, "Aguarde...");
	        SelectTextDraw(playerid, 0xBBBBBBFF);
	        return 0;
		}
	
	    new indexx = 4;

	    while(indexx--)
	    {
	        if (playertextid == PlayerWeaponCraft[indexx])
	        {
	        	UpdatePlayerSelectedWeapon(playerid, (playerPageWeapon[playerid] * 4) + indexx);

	        	return 1;
			}
	    }
	}
 	#if defined yOPCPTD
  		return yOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw yOPCPTD
#if defined yOPCPTD
	forward yOPCPTD(playerid, PlayerText:playertextid);
#endif

stock createServerWeaponsCraft() {
	weaponsCraft[0] = TextDrawCreate(101.000000, 126.000000, "usebox");
	TextDrawBackgroundColor(weaponsCraft[0], 0);
	TextDrawFont(weaponsCraft[0], 1);
	TextDrawLetterSize(weaponsCraft[0], 0.500000, 28.000000);
	TextDrawColor(weaponsCraft[0], 0);
	TextDrawSetOutline(weaponsCraft[0], 0);
	TextDrawSetProportional(weaponsCraft[0], 1);
	TextDrawSetShadow(weaponsCraft[0], 1);
	TextDrawUseBox(weaponsCraft[0], 1);
	TextDrawBoxColor(weaponsCraft[0], 84215220);
	TextDrawTextSize(weaponsCraft[0], 488.000000, 0.000000);
	TextDrawSetSelectable(weaponsCraft[0], 0);

	weaponsCraft[1] = TextDrawCreate(270.000000, 20.000000, "i");
	TextDrawBackgroundColor(weaponsCraft[1], 0);
	TextDrawFont(weaponsCraft[1], 2);
	TextDrawLetterSize(weaponsCraft[1], 0.159999, 46.099998);
	TextDrawColor(weaponsCraft[1], -156);
	TextDrawSetOutline(weaponsCraft[1], 0);
	TextDrawSetProportional(weaponsCraft[1], 1);
	TextDrawSetShadow(weaponsCraft[1], 1);
	TextDrawSetSelectable(weaponsCraft[1], 0);

	weaponsCraft[2] = TextDrawCreate(209.000000, 327.000000, "ld_beat:left");
	TextDrawAlignment(weaponsCraft[2], 3);
	TextDrawBackgroundColor(weaponsCraft[2], 0);
	TextDrawFont(weaponsCraft[2], 4);
	TextDrawLetterSize(weaponsCraft[2], 0.159998, 0.799998);
	TextDrawColor(weaponsCraft[2], -206);
	TextDrawSetOutline(weaponsCraft[2], 0);
	TextDrawSetProportional(weaponsCraft[2], 1);
	TextDrawSetShadow(weaponsCraft[2], 1);
	TextDrawUseBox(weaponsCraft[2], 1);
	TextDrawBoxColor(weaponsCraft[2], 255);
	TextDrawTextSize(weaponsCraft[2], 11.000000, 12.000000);
	TextDrawSetSelectable(weaponsCraft[2], 1);

	weaponsCraft[3] = TextDrawCreate(249.000000, 327.000000, "ld_beat:right");
	TextDrawAlignment(weaponsCraft[3], 3);
	TextDrawBackgroundColor(weaponsCraft[3], 0);
	TextDrawFont(weaponsCraft[3], 4);
	TextDrawLetterSize(weaponsCraft[3], 0.159998, 0.799998);
	TextDrawColor(weaponsCraft[3], -206);
	TextDrawSetOutline(weaponsCraft[3], 0);
	TextDrawSetProportional(weaponsCraft[3], 1);
	TextDrawSetShadow(weaponsCraft[3], 1);
	TextDrawUseBox(weaponsCraft[3], 1);
	TextDrawBoxColor(weaponsCraft[3], 255);
	TextDrawTextSize(weaponsCraft[3], 11.000000, 12.000000);
	TextDrawSetSelectable(weaponsCraft[3], 1);

	weaponsCraft[4] = TextDrawCreate(360.000000, 317.000000, "Construir");
	TextDrawBackgroundColor(weaponsCraft[4], 0);
	TextDrawFont(weaponsCraft[4], 2);
	TextDrawLetterSize(weaponsCraft[4], 0.150000, 0.899999);
	TextDrawColor(weaponsCraft[4], -176);
	TextDrawSetOutline(weaponsCraft[4], 0);
	TextDrawSetProportional(weaponsCraft[4], 1);
	TextDrawSetShadow(weaponsCraft[4], 1);
	TextDrawUseBox(weaponsCraft[4], 1);
	TextDrawBoxColor(weaponsCraft[4], 336860415);
	TextDrawTextSize(weaponsCraft[4], 394.000000, 20.000000);
	TextDrawSetSelectable(weaponsCraft[4], 1);

	weaponsCraft[5] = TextDrawCreate(451.000000, 137.000000, "fechar");
	TextDrawBackgroundColor(weaponsCraft[5], 0);
	TextDrawFont(weaponsCraft[5], 2);
	TextDrawLetterSize(weaponsCraft[5], 0.159999, 0.899999);
	TextDrawColor(weaponsCraft[5], -176);
	TextDrawSetOutline(weaponsCraft[5], 0);
	TextDrawSetProportional(weaponsCraft[5], 1);
	TextDrawSetShadow(weaponsCraft[5], 1);
	TextDrawUseBox(weaponsCraft[5], 1);
	TextDrawBoxColor(weaponsCraft[5], 336860415);
	TextDrawTextSize(weaponsCraft[5], 477.000000, 20.000000);
	TextDrawSetSelectable(weaponsCraft[5], 1);
}

stock CreatePlayerWeaponCraft(playerid) {
	PlayerWeaponCraft[0] = CreatePlayerTextDraw(playerid, 110.000000, 150.000000, "model");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[0], 336860415);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[0], 5);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[0], -1);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[0], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[0], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[0], 1);
	PlayerTextDrawUseBox(playerid, PlayerWeaponCraft[0], 1);
	PlayerTextDrawBoxColor(playerid, PlayerWeaponCraft[0], 0);
	PlayerTextDrawTextSize(playerid, PlayerWeaponCraft[0], 71.000000, 77.000000);
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[0], 999);
	PlayerTextDrawSetPreviewRot(playerid, PlayerWeaponCraft[0], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[0], 1);

	PlayerWeaponCraft[1] = CreatePlayerTextDraw(playerid, 190.000000, 150.000000, "model");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[1], 336860415);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[1], 5);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[1], -1);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[1], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[1], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[1], 1);
	PlayerTextDrawUseBox(playerid, PlayerWeaponCraft[1], 1);
	PlayerTextDrawBoxColor(playerid, PlayerWeaponCraft[1], 0);
	PlayerTextDrawTextSize(playerid, PlayerWeaponCraft[1], 71.000000, 77.000000);
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[1], 999);
	PlayerTextDrawSetPreviewRot(playerid, PlayerWeaponCraft[1], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[1], 1);

	PlayerWeaponCraft[2] = CreatePlayerTextDraw(playerid, 110.000000, 238.000000, "model");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[2], 336860415);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[2], 5);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[2], -1);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[2], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[2], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[2], 1);
	PlayerTextDrawUseBox(playerid, PlayerWeaponCraft[2], 1);
	PlayerTextDrawBoxColor(playerid, PlayerWeaponCraft[2], 0);
	PlayerTextDrawTextSize(playerid, PlayerWeaponCraft[2], 71.000000, 77.000000);
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[2], 999);
	PlayerTextDrawSetPreviewRot(playerid, PlayerWeaponCraft[2], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[2], 1);

	PlayerWeaponCraft[3] = CreatePlayerTextDraw(playerid, 190.000000, 238.000000, "model");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[3], 336860415);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[3], 5);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[3], -1);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[3], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[3], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[3], 1);
	PlayerTextDrawUseBox(playerid, PlayerWeaponCraft[3], 1);
	PlayerTextDrawBoxColor(playerid, PlayerWeaponCraft[3], 0);
	PlayerTextDrawTextSize(playerid, PlayerWeaponCraft[3], 71.000000, 77.000000);
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[3], 999);
	PlayerTextDrawSetPreviewRot(playerid, PlayerWeaponCraft[3], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[3], 1);

	PlayerWeaponCraft[4] = CreatePlayerTextDraw(playerid, 179.000000, 217.000000, "---");
	PlayerTextDrawAlignment(playerid, PlayerWeaponCraft[4], 3);
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[4], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[4], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[4], 0.159998, 0.799998);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[4], -106);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[4], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[4], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[4], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[4], 0);

	PlayerWeaponCraft[5] = CreatePlayerTextDraw(playerid, 259.000000, 217.000000, "---");
	PlayerTextDrawAlignment(playerid, PlayerWeaponCraft[5], 3);
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[5], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[5], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[5], 0.159998, 0.799998);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[5], -106);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[5], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[5], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[5], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[5], 0);

	PlayerWeaponCraft[6] = CreatePlayerTextDraw(playerid, 179.000000, 305.000000, "---");
	PlayerTextDrawAlignment(playerid, PlayerWeaponCraft[6], 3);
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[6], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[6], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[6], 0.159998, 0.799998);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[6], -106);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[6], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[6], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[6], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[6], 0);

	PlayerWeaponCraft[7] = CreatePlayerTextDraw(playerid, 259.000000, 305.000000, "---");
	PlayerTextDrawAlignment(playerid, PlayerWeaponCraft[7], 3);
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[7], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[7], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[7], 0.159998, 0.799998);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[7], -106);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[7], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[7], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[7], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[7], 0);

	PlayerWeaponCraft[8] = CreatePlayerTextDraw(playerid, 234.000000, 328.000000, "1-5");
	PlayerTextDrawAlignment(playerid, PlayerWeaponCraft[8], 2);
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[8], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[8], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[8], 0.230000, 0.899999);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[8], -156);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[8], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[8], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[8], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[8], 0);

	PlayerWeaponCraft[9] = CreatePlayerTextDraw(playerid, 281.000000, 150.000000, "model_selected");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[9], 252645375);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[9], 5);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[9], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[9], -1);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[9], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[9], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[9], 1);
	PlayerTextDrawUseBox(playerid, PlayerWeaponCraft[9], 1);
	PlayerTextDrawBoxColor(playerid, PlayerWeaponCraft[9], 0);
	PlayerTextDrawTextSize(playerid, PlayerWeaponCraft[9], 101.000000, 117.000000);
	PlayerTextDrawSetPreviewModel(playerid, PlayerWeaponCraft[9], 999);
	PlayerTextDrawSetPreviewRot(playerid, PlayerWeaponCraft[9], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[9], 0);

	PlayerWeaponCraft[10] = CreatePlayerTextDraw(playerid, 283.000000, 257.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, PlayerWeaponCraft[10], 0);
	PlayerTextDrawFont(playerid, PlayerWeaponCraft[10], 1);
	PlayerTextDrawLetterSize(playerid, PlayerWeaponCraft[10], 0.170000, 0.899999);
	PlayerTextDrawColor(playerid, PlayerWeaponCraft[10], -106);
	PlayerTextDrawSetOutline(playerid, PlayerWeaponCraft[10], 0);
	PlayerTextDrawSetProportional(playerid, PlayerWeaponCraft[10], 1);
	PlayerTextDrawSetShadow(playerid, PlayerWeaponCraft[10], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerWeaponCraft[10], 0);
}
