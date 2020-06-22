

#define HELMET1_REDUCE_PERCENT      30.0 // 30%
#define HELMET2_REDUCE_PERCENT      50.0 // 50%
#define HELMET3_REDUCE_PERCENT      70.0 // 70%

#define ARMOR1_REDUCE_PERCENT       30.0 // 30%
#define ARMOR2_REDUCE_PERCENT       50.0 // 50%
#define ARMOR3_REDUCE_PERCENT       70.0 // 70%

stock SetPlayerHelmet(playerid, level, Float:health)
{
	PlayerData[playerid][dHelmetType] = level;
	PlayerData[playerid][dHelmetHealth] = health;
	
	switch (level)
	{
	    case ITEM_TYPE_HELMETLVL1: {
			SHOP_SetPlayerAttachedObject(playerid, 5, -1006);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[8], "mdl-1019:h1");
		}
	    case ITEM_TYPE_HELMETLVL2: {
			SHOP_SetPlayerAttachedObject(playerid, 5, -1007);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[8], "mdl-1019:h2");
		}
	    case ITEM_TYPE_HELMETLVL3: {
			SHOP_SetPlayerAttachedObject(playerid, 5, -1008);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[8], "mdl-1019:h3");
		}
		default: PlayerTextDrawSetString(playerid, playerHudTextdraw[8], "INVALID");
	}
	PlayerTextDrawColor(playerid, playerHudTextdraw[8], ConvertHelmetDamageToColor(PlayerData[playerid][dHelmetType], PlayerData[playerid][dHelmetHealth]));
    if (IsPlayerViewingStatus(playerid))
    {
        PlayerTextDrawShow(playerid, playerHudTextdraw[8]);
    }
}

stock RemovePlayerHelmet(playerid)
{
	PlayerData[playerid][dHelmetType] = 0;
	PlayerData[playerid][dHelmetHealth] = 0.0;
	// Reset
	RemovePlayerAttachedObject(playerid, 5);
	// Textdraw
	PlayerTextDrawSetString(playerid, playerHudTextdraw[8], "INVALID");
}

stock Float:GetPlayerHelmetHealth(playerid)
{
	if (!PlayerData[playerid][dHelmetType])
	    return 0.0;
	    
	return PlayerData[playerid][dHelmetHealth];
}

stock ReductionHelmetDamage(playerid, &Float:amount)
{
	if (!PlayerData[playerid][dHelmetType])
	    return 0;

    PlayerData[playerid][dHelmetHealth] -= amount;

	switch (PlayerData[playerid][dHelmetType])
	{
	    case ITEM_TYPE_HELMETLVL1: amount = amount - ((HELMET1_REDUCE_PERCENT * amount) / 100.0);
	    case ITEM_TYPE_HELMETLVL2: amount = amount - ((HELMET2_REDUCE_PERCENT * amount) / 100.0);
	    case ITEM_TYPE_HELMETLVL3: amount = amount - ((HELMET3_REDUCE_PERCENT * amount) / 100.0);
	}
	
	if (PlayerData[playerid][dHelmetHealth] <= 0.0)
	{
	    RemovePlayerHelmet(playerid);
	} else {
	    PlayerTextDrawColor(playerid, playerHudTextdraw[8], ConvertHelmetDamageToColor(PlayerData[playerid][dHelmetType], PlayerData[playerid][dHelmetHealth]));
	    if (IsPlayerViewingStatus(playerid))
	    {
	        PlayerTextDrawShow(playerid, playerHudTextdraw[8]);
	    }
	}
	
	return 1;
}

stock ConvertHelmetDamageToColor(level, Float:health)
{
	new color;
	new Float:porcentagem;

	switch (level)
	{
	    case ITEM_TYPE_HELMETLVL1:
	    {
	        porcentagem = (health * 100.0) / MAX_HELMET1_HEALTH;
	    }
	    case ITEM_TYPE_HELMETLVL2:
	    {
	        porcentagem = (health * 100.0) / MAX_HELMET2_HEALTH;
	    }
	    case ITEM_TYPE_HELMETLVL3:
	    {
	        porcentagem = (health * 100.0) / MAX_HELMET3_HEALTH;
	    }
	}
	
	if (porcentagem > 90.0) 		color = -186;
	else if (porcentagem <= 20.0) 	color = 0xFF0000FF;
    else if (porcentagem <= 30.0) 	color = 0xFF5555AA;
	else                            color = 0xFFFFFFFF;
	
	return color;
}

stock ConvertArmorDamageToColor(level, Float:health)
{
	new color;
	new Float:porcentagem;

	switch (level)
	{
	    case ITEM_TYPE_ARMORLVL1:
	    {
	        porcentagem = (health * 100.0) / MAX_ARMOR1_HEALTH;
	    }
	    case ITEM_TYPE_ARMORLVL2:
	    {
	        porcentagem = (health * 100.0) / MAX_ARMOR2_HEALTH;
	    }
	    case ITEM_TYPE_ARMORLVL3:
	    {
	        porcentagem = (health * 100.0) / MAX_ARMOR3_HEALTH;
	    }
	}

	if (porcentagem > 90.0) 		color = -186;
	else if (porcentagem <= 20.0) 	color = 0xFF0000FF;
    else if (porcentagem <= 30.0) 	color = 0xFF5555AA;
	else                            color = 0xFFFFFFFF;

	return color;
}

stock GetPlayerHelmetObject(playerid)
{
	switch (PlayerData[playerid][dHelmetType])
	{
	    case ITEM_TYPE_HELMETLVL1: return -1006;
	    case ITEM_TYPE_HELMETLVL2: return -1007;
	    case ITEM_TYPE_HELMETLVL3: return -1008;
	}
	return 0;
}

stock GetPlayerHelmetTextName(playerid)
{
	new string[15];
	switch (PlayerData[playerid][dHelmetType])
	{
	    case ITEM_TYPE_HELMETLVL1: string = "mdl-1004:h1";
	    case ITEM_TYPE_HELMETLVL2: string = "mdl-1004:h2";
	    case ITEM_TYPE_HELMETLVL3: string = "mdl-1004:h3";
	}
	return string;
}

stock GetPlayerHelmetType(playerid)
{
	return PlayerData[playerid][dHelmetType];
}

stock SetPlayerArmor(playerid, level, Float:health)
{
	PlayerData[playerid][dArmorType] = level;
	PlayerData[playerid][dArmorHealth] = health;

	switch (level)
	{
	    case ITEM_TYPE_ARMORLVL1: {
			SHOP_SetPlayerAttachedObject(playerid, 4, -1009);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[7], "mdl-1019:a1");
		}
	    case ITEM_TYPE_ARMORLVL2: {
			SHOP_SetPlayerAttachedObject(playerid, 4, -1010);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[7], "mdl-1019:a2");
		}
	    case ITEM_TYPE_ARMORLVL3: {
			SHOP_SetPlayerAttachedObject(playerid, 4, -1011);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[7], "mdl-1019:a3");
		}
		default: PlayerTextDrawSetString(playerid, playerHudTextdraw[7], "INVALID");
	}
	PlayerTextDrawColor(playerid, playerHudTextdraw[7], ConvertArmorDamageToColor(PlayerData[playerid][dArmorType], PlayerData[playerid][dArmorHealth]));
    if (IsPlayerViewingStatus(playerid))
    {
     	PlayerTextDrawShow(playerid, playerHudTextdraw[7]);
    }
}

stock RemovePlayerArmor(playerid)
{
	PlayerData[playerid][dArmorType] = 0;
	PlayerData[playerid][dArmorHealth] = 0.0;
	// Reset
	RemovePlayerAttachedObject(playerid, 4);
	// Textdraw
	PlayerTextDrawSetString(playerid, playerHudTextdraw[7], "INVALID");
}

stock Float:GetPlayerArmorHealth(playerid)
{
	if (!PlayerData[playerid][dArmorType])
	    return 0.0;

	return PlayerData[playerid][dArmorHealth];
}

stock ReductionArmorDamage(playerid, &Float:amount)
{
	if (!PlayerData[playerid][dArmorType])
	    return 0;
	    
    PlayerData[playerid][dArmorHealth] -= amount;
	    
	switch (PlayerData[playerid][dArmorType])
	{
	    case ITEM_TYPE_ARMORLVL1: amount = amount - ((ARMOR1_REDUCE_PERCENT * amount) / 100.0);
	    case ITEM_TYPE_ARMORLVL2: amount = amount - ((ARMOR2_REDUCE_PERCENT * amount) / 100.0);
	    case ITEM_TYPE_ARMORLVL3: amount = amount - ((ARMOR3_REDUCE_PERCENT * amount) / 100.0);
	}
	
	if (PlayerData[playerid][dArmorHealth] <= 0.0)
	{
	    RemovePlayerArmor(playerid);
	} else {
	    PlayerTextDrawColor(playerid, playerHudTextdraw[7], ConvertArmorDamageToColor(PlayerData[playerid][dArmorType], PlayerData[playerid][dArmorHealth]));
	    if (IsPlayerViewingStatus(playerid))
	    {
	        PlayerTextDrawShow(playerid, playerHudTextdraw[7]);
	    }
	}
	
	return 1;
}

stock GetPlayerArmorObject(playerid)
{
	switch (PlayerData[playerid][dArmorType])
	{
	    case ITEM_TYPE_ARMORLVL1: return -1016;
	    case ITEM_TYPE_ARMORLVL2: return -1017;
	    case ITEM_TYPE_ARMORLVL3: return -1018;
	}
	return 0;
}

stock GetPlayerArmorTextName(playerid)
{
	new string[15];
	switch (PlayerData[playerid][dArmorType])
	{
	    case ITEM_TYPE_ARMORLVL1: string = "mdl-1004:a1";
	    case ITEM_TYPE_ARMORLVL2: string = "mdl-1004:a2";
	    case ITEM_TYPE_ARMORLVL3: string = "mdl-1004:a3";
	}
	return string;
}

stock GetPlayerArmorType(playerid)
{
	return PlayerData[playerid][dArmorType];
}

stock UpdatePlayerItemsName(playerid)
{
	PlayerTextDrawSetString(playerid, playerItemsEquip[0], GetPlayerHelmetTextName(playerid));
	PlayerTextDrawSetString(playerid, playerItemsEquip[1], GetPlayerArmorTextName(playerid));
	PlayerTextDrawSetString(playerid, playerItemsEquip[2], GetBackPackModelName(playerid));
	
	new string[45];
	
	if (PlayerData[playerid][dHelmetType] > 0)
	{
	    format(string, sizeof string, "%.0f~n~~n~~n~~n~", PlayerData[playerid][dHelmetHealth]);
	} else {
	    format(string, sizeof string, "_~n~~n~~n~~n~");
	}
	
	if (PlayerData[playerid][dArmorType] > 0)
	{
	    format(string, sizeof string, "%s%.0f~n~", string, PlayerData[playerid][dArmorHealth]);
	} else {
	    format(string, sizeof string, "%s_~n~", string);
	}

	PlayerTextDrawSetString(playerid, playerHealthProtect, string);
	
	// Gas mask / Lanterna
	if (IsPlayerInInventory(playerid))
	{
		if (PlayerData[playerid][dLanterna]) {
			TextDrawShowForPlayer(playerid, textLanterna);
		}
		else {
		    TextDrawHideForPlayer(playerid, textLanterna);
		}

		if (PlayerData[playerid][dGasMask]) {
			TextDrawShowForPlayer(playerid, textGasMask);
		}
		else {
		    TextDrawHideForPlayer(playerid, textGasMask);
		}
	}
}

stock GuardarHelmet(playerid, bool:forcedrop = false)
{
	if (!PlayerData[playerid][dHelmetType])
	    return 0;
	    
	if (!isInventoryFreeSpace(playerid, getItemTypeSlots(PlayerData[playerid][dHelmetType])) || forcedrop)
	{
	    static
	        Float:x, Float:y, Float:z;
	        
		GetPlayerPos(playerid, x, y, z);
	        
	    createDroppedItem(
				x,
				y,
				z,
				getItemTypeName(PlayerData[playerid][dHelmetType]),
				PlayerData[playerid][dHelmetType],
				GetPlayerHelmetObject(playerid),
				1,
				true,
				GetPlayerVirtualWorld(playerid),
				true,
				GetPlayerHelmetHealth(playerid)
		);
	} else {
	    givePlayerItem(
				playerid,
				PlayerData[playerid][dHelmetType],
				GetPlayerHelmetObject(playerid),
				1,
				getItemTypeName(PlayerData[playerid][dHelmetType]),
				GetPlayerHelmetHealth(playerid)
		);
	}
	
	RemovePlayerHelmet(playerid);
	
	UpdatePlayerItemsName(playerid);
	
	// procurar itens
	searchItens(playerid);
	    
	return 1;
}

stock GuardarArmor(playerid, bool:forcedrop = false)
{
	if (!PlayerData[playerid][dArmorType])
	    return 0;

	if (!isInventoryFreeSpace(playerid, getItemTypeSlots(PlayerData[playerid][dArmorType])) || forcedrop)
	{
	    static
	        Float:x, Float:y, Float:z;

		GetPlayerPos(playerid, x, y, z);

	    createDroppedItem(
				x,
				y,
				z,
				getItemTypeName(PlayerData[playerid][dArmorType]),
				PlayerData[playerid][dArmorType],
				GetPlayerArmorObject(playerid),
				1,
				true,
				GetPlayerVirtualWorld(playerid),
				true,
				GetPlayerArmorHealth(playerid)
		);
	} else {
	    givePlayerItem(
				playerid,
				PlayerData[playerid][dArmorType],
				GetPlayerArmorObject(playerid),
				1,
				getItemTypeName(PlayerData[playerid][dArmorType]),
				GetPlayerArmorHealth(playerid)
		);
	}
	
	RemovePlayerArmor(playerid);
	
	UpdatePlayerItemsName(playerid);

	// procurar itens
	searchItens(playerid);

	return 1;
}

