#include "../modulos/inventario/core.inc"
#include "../modulos/inventario/searchitens.inc"

callback resetInventory(playerid) {

	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
	    InventarioInfo[playerid][inv][item_valid] 	= 0;
	    InventarioInfo[playerid][inv][item_type] 	= ITEM_TYPE_NONE;
	    InventarioInfo[playerid][inv][item_model] 	= 0;
	    InventarioInfo[playerid][inv][item_quantia] = 0;
	    InventarioInfo[playerid][inv][item_slots]   = 1;
	    format(InventarioInfo[playerid][inv][item_nome], 75, "Vazio");
	}
}

stock reorganizarItens(playerid)
{
	for(new t; t < MAX_ITENS_INVENTARIO; t++)
	{
	    if (!InventarioInfo[playerid][t][item_valid])
		{
	        resetItem(playerid, t, .organize=true);
	    }
	}
}

stock organizarItens(playerid, startitem) {

	for(new inv = startitem; inv < MAX_ITENS_INVENTARIO - 1; inv++) {
	    InventarioInfo[playerid][inv][item_valid] 	= InventarioInfo[playerid][inv + 1][item_valid];
	    InventarioInfo[playerid][inv][item_type] 	= InventarioInfo[playerid][inv + 1][item_type];
	    InventarioInfo[playerid][inv][item_model] 	= InventarioInfo[playerid][inv + 1][item_model];
	    InventarioInfo[playerid][inv][item_quantia] = InventarioInfo[playerid][inv + 1][item_quantia];
	    InventarioInfo[playerid][inv][item_slots]   = InventarioInfo[playerid][inv + 1][item_slots];
	    InventarioInfo[playerid][inv][item_health]  = InventarioInfo[playerid][inv + 1][item_health];
	    format(InventarioInfo[playerid][inv][item_nome], 45, InventarioInfo[playerid][inv + 1][item_nome]);
	    
	    resetItem(playerid, inv + 1);
	}
}

stock resetItem(playerid, itemid, bool:organize=false) {

	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO) {
	    return 0;
	}

	InventarioInfo[playerid][itemid][item_valid] 	= 0;
 	InventarioInfo[playerid][itemid][item_type] 	= ITEM_TYPE_NONE;
  	InventarioInfo[playerid][itemid][item_model] 	= 0;
   	InventarioInfo[playerid][itemid][item_quantia]  = 0;
   	InventarioInfo[playerid][itemid][item_slots]    = 1;
   	InventarioInfo[playerid][itemid][item_health]   = 100.0;
   	format(InventarioInfo[playerid][itemid][item_nome], 75, "Vazio");

	// Organizar os itens
	if (organize) organizarItens(playerid, itemid);

   	return 1;
}

callback isInventoryFuull(playerid) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (!InventarioInfo[playerid][inv][item_valid]) {

		    return 0;
		}
	}
	return 1;
}

stock isInventoryFreeSpace(playerid, quantidade = 1) {

	new maxslots = getPlayerMaxSlots(playerid);
	new countslots = 0;

	for(new inv; inv != maxslots; inv++) {

		if (InventarioInfo[playerid][inv][item_valid]) {
            countslots += InventarioInfo[playerid][inv][item_slots];
		}
	}
	
	return ((countslots + quantidade) <= maxslots ? (1) : (0));
}

callback countItensInventory(playerid) {

	new maxslots = getPlayerMaxSlots(playerid);
	new countslots = 0;

	for(new inv; inv != maxslots; inv++) {

		if (InventarioInfo[playerid][inv][item_valid]) {
            countslots += InventarioInfo[playerid][inv][item_slots];
		}
	}
	return countslots;
}

// Loots
stock createLoot(Float:x, Float:y, Float:z, timedestroy=120, type=LOOT_TYPE_NONE, bool:createobject=false, bool:create3dtext=false, bool:raycast=true, Float:rz=0.0, slots=45, world=0, attachobject=-1, idloot=-1) {

	new loot;

	if (idloot != -1) {
	    loot = idloot;
	} else {
	    loot = Iter_Free(iterLoots);
	}

	if (loot != -1) {

		Iter_Add(iterLoots, loot);

	    if (raycast && type != LOOT_TYPE_VEHICLE) {
			CA_RayCastLine(x, y, z, x, y, z-15.0, x, y, z);
			z += 0.1;
		}

		LootInfo[loot][loot_type] = type;
		LootInfo[loot][loot_slots] = slots;
		LootInfo[loot][loot_world] = world;
		LootInfo[loot][loot_baseid] = -1;
		LootInfo[loot][loot_area] = 0;

	    LootInfo[loot][loot_x] = x;
	    LootInfo[loot][loot_y] = y;
	    LootInfo[loot][loot_z] = z;
	    LootInfo[loot][loot_rz] = rz;

		for(new object; object != 12; object++) {
		    LootInfo[loot][loot_object][object] = -1;
		}
	    LootInfo[loot][loot_label]  = Text3D:-1;
	    LootInfo[loot][loot_timer]  = -1;
	    LootInfo[loot][loot_vehicle]= INVALID_VEHICLE_ID;

	    for(new itens; itens != MAX_ITENS_LOOT; itens++) {
	        LootItensInfo[loot][itens][item_valid] = 0;
			LootItensInfo[loot][itens][item_quantia] = 0;
			LootItensInfo[loot][itens][item_model]   = 0;
			LootItensInfo[loot][itens][item_slots]   = 1;
			LootItensInfo[loot][itens][item_health]  = 100.0;
            format(LootItensInfo[loot][itens][item_nome], 45, "Vazio");
	  	}

	   	if (type == LOOT_TYPE_AIRDROP) {
		   	LootInfo[loot][loot_timer] = SetTimerEx("destroyLoot", timedestroy * 60000, false, "i", loot);
	    }

	    if (createobject) {

	       	switch(type) {

		        case LOOT_TYPE_MOCHILA:
				{
				    LootInfo[loot][loot_area] = CreateDynamicSphere(x, y, z, 3.0);
		            LootInfo[loot][loot_object][0]  = CreateDynamicObject(2060, x, y, z, -90.0, 0.0, random(360), world);
		        }
		        case LOOT_TYPE_BOX:
				{
				    LootInfo[loot][loot_area] = CreateDynamicSphere(x, y, z, 3.0);
		            LootInfo[loot][loot_object][0]  = CreateDynamicObject(19921, x, y, z, 0.0, 0.0, random(360), world);
		        }
		        case LOOT_TYPE_AIRDROP:
				{
				    LootInfo[loot][loot_area] = CreateDynamicSphere(x, y, z, 3.0);
		            LootInfo[loot][loot_object][0]  = CreateDynamicObject(-1021, x, y, z + 1.0, 0.0, 0.0, 0.0, world, -1, -1, 500.0, 800.0);
                    LootInfo[loot][loot_object][1]  = CreateDynamicObject(18728, x + frandom(5.0) - frandom(5.0), y + frandom(5.0) - frandom(5.0), z - 2.8, 0.0, 0.0, 0.0, world);
				}
		        case LOOT_TYPE_TENDA:
				{
				    LootInfo[loot][loot_area] = CreateDynamicSphere(x, y, z, 1.4);
				    LootInfo[loot][loot_object][0]  = attachobject;
					//CreateTent(x, y, z - 0.5, rz, loot, world);
					
					if (idloot == -1) {
						saveTent(loot);
					}
				}
		        case LOOT_TYPE_BARRACA:
				{
				    LootInfo[loot][loot_area] = CreateDynamicSphere(x, y, z, 2.3);
					CreateTent(x, y, z - 0.5, rz, loot, world);

					if (idloot == -1) {
						saveTent(loot);
					}
				}
				/*
				case LOOT_TYPE_VEHICLE:
				{
//				    Streamer_SetFloatData(STREAMER_TYPE_AREA, LootInfo[loot][loot_area], E_STREAMER_SIZE, 4.0);
				}*/
		    }
  		}

	    if (create3dtext && type != LOOT_TYPE_VEHICLE) {
	       	LootInfo[loot][loot_label] = CreateDynamic3DTextLabel("Aperte a letra 'Y' para vasculhar", 0xFF9900AA, x, y, z, 5.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world);
	   	}
	}
	return loot;
}

// SaveVehicleInfo(vehicleid);
stock addItemToLoot(lootid, itemtype, modelid, quantidade, itemnome[], Float:health = 100.0, saveloot = 1) {

	if (Iter_Contains(iterLoots, lootid)) {

		for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
		
		    if (!LootItensInfo[lootid][itens][item_valid]) {

				// Tornar válido
				LootItensInfo[lootid][itens][item_valid] = 1;
				
				// Nome
				format(LootItensInfo[lootid][itens][item_nome], 45, itemnome);
				
				// Info
				LootItensInfo[lootid][itens][item_type]  	= itemtype;
				LootItensInfo[lootid][itens][item_model] 	= modelid;
				LootItensInfo[lootid][itens][item_quantia]  = quantidade;
				LootItensInfo[lootid][itens][item_health]   = health;
				LootItensInfo[lootid][itens][item_slots]    = getItemModelSlots(modelid);
				
				if (saveloot)
				{
					if (LootInfo[lootid][loot_vehicle] != INVALID_VEHICLE_ID) {
					    SaveVehicleInfo(LootInfo[lootid][loot_vehicle]);
					}

					if (LootInfo[lootid][loot_type] == LOOT_TYPE_TENDA || LootInfo[lootid][loot_type] == LOOT_TYPE_BARRACA) {
					    saveTent(lootid);
					}

				 	else if (LootInfo[lootid][loot_type] == LOOT_TYPE_VEHICLE) {
					    SaveVehicleInfo(LootInfo[lootid][loot_vehicle]);
					}
				}
				
				return 1;
			}
    	}
	}
	return 0;
}

stock attachLootToVehicle(lootid, vehicleid) {

	if (Iter_Contains(iterLoots, lootid) && LootInfo[lootid][loot_type] == LOOT_TYPE_VEHICLE) {
	
	    LootInfo[lootid][loot_vehicle] = vehicleid;

//	    Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, LootInfo[lootid][loot_label], E_STREAMER_ATTACHED_VEHICLE, vehicleid);
		return 1;
	}
	return 0;
}

stock resetAllLootItens(lootid)
{
	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
		LootItensInfo[lootid][itens][item_valid]   = 0;
		LootItensInfo[lootid][itens][item_quantia] = 0;
		LootItensInfo[lootid][itens][item_model]   = 0;
	}
}

stock resetLootSlot(lootid, slot) {

	if (Iter_Contains(iterLoots, lootid)) {
		LootItensInfo[lootid][slot][item_valid]   = 0;
		LootItensInfo[lootid][slot][item_quantia] = 0;
		LootItensInfo[lootid][slot][item_model]   = 0;
		
		if (LootInfo[lootid][loot_vehicle] != INVALID_VEHICLE_ID) {
		    SaveVehicleInfo(LootInfo[lootid][loot_vehicle]);
		}
		
		// Destruir o loot caso não tenha mais itens
		if (LootInfo[lootid][loot_type] != LOOT_TYPE_TENDA && LootInfo[lootid][loot_type] != LOOT_TYPE_BARRACA && LootInfo[lootid][loot_type] != LOOT_TYPE_VEHICLE && !countLootItens(lootid)) {
		    destroyLoot(lootid);
		}
		
		if (LootInfo[lootid][loot_type] == LOOT_TYPE_TENDA || LootInfo[lootid][loot_type] == LOOT_TYPE_BARRACA) {
		    saveTent(lootid);
		}
		
		else if (LootInfo[lootid][loot_type] == LOOT_TYPE_VEHICLE) {
		    SaveVehicleInfo(LootInfo[lootid][loot_vehicle]);
		}

		return 1;
	}
	return 0;
}

stock countLootItens(lootid) {

	new count;
	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
	    if (LootItensInfo[lootid][itens][item_valid]){
 			count += LootItensInfo[lootid][itens][item_slots];
		}
	}
	return count;
}

stock countLootItensNumber(lootid) {

	new count;
	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
	    if (LootItensInfo[lootid][itens][item_valid]){
 			count ++;
		}
	}
	return count;
}

stock isLootFull(lootid) {

	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
	    if (!LootItensInfo[lootid][itens][item_valid]){
 			return 0;
		}
	}
	return 1;
}

stock isLootFreeSpace(lootid, quantidade = 1) {

	new maxslots = LootInfo[lootid][loot_slots];
	new countslots;

	for(new itens; itens != maxslots; itens++) {

		if (LootItensInfo[lootid][itens][item_valid]){
 			countslots += LootItensInfo[lootid][itens][item_slots];
		}
	}
	return ((countslots + quantidade) <= maxslots ? (1) : (0));
}

callback destroyLoot(lootid) {

	if (Iter_Contains(iterLoots, lootid)) {

        Iter_Remove(iterLoots, lootid);

		DestroyDynamic3DTextLabel(LootInfo[lootid][loot_label]);
		for(new object; object != 12; object++) {
			DestroyDynamicObject(LootInfo[lootid][loot_object][object]);
		}
		DestroyDynamicArea(LootInfo[lootid][loot_area]);

		if (LootInfo[lootid][loot_type] == LOOT_TYPE_AIRDROP)
		{
			KillTimer(LootInfo[lootid][loot_timer]);
		}
		LootInfo[lootid][loot_timer] = -1;

		for(new itens; itens != MAX_ITENS_LOOT; itens++) {
  			LootItensInfo[lootid][itens][item_valid] = 0;
    	}
    	
		if (LootInfo[lootid][loot_type] == LOOT_TYPE_TENDA || LootInfo[lootid][loot_type] == LOOT_TYPE_BARRACA) {
		    removeTentFile(lootid);
		}

		return 1;
	}
	return 0;
}

public OnPlayerEnterDynamicArea(playerid, areaid) {

	if (GetPlayerVirtualWorld(playerid) != 0)
	    return 1;

	new string[45];
	foreach(new loot : iterLoots) {
	
	    if (LootInfo[loot][loot_area] == areaid) {
	    
			switch(LootInfo[loot][loot_type]) {
			
			    case LOOT_TYPE_TENDA: {
			        PlayerData[playerid][dCurrentLoot] = loot;
			        // formatar a string
			        format(string, sizeof string, GetPlayerLanguageKey(playerid, "INFO_1"), countLootItens(loot), LootInfo[loot][loot_slots]);
			    }
			    case LOOT_TYPE_BARRACA: {
			        PlayerData[playerid][dCurrentLoot] = loot;
			        // formatar a string
			        format(string, sizeof string, "TENDA~n~~n~Slots: %d/%d~n~", countLootItens(loot), LootInfo[loot][loot_slots]);
			    }
			    case LOOT_TYPE_MOCHILA: {
			        // formatar a string
			        format(string, sizeof string, GetPlayerLanguageKey(playerid, "INFO_2"));
			    }
			    case LOOT_TYPE_BOX: {
			    
			        // formatar a string
			        format(string, sizeof string, "Loot");
			    }
			    default: {

			        // formatar a string
			        format(string, sizeof string, "Loot");
			    }
			}
		    PlayerTextDrawSetString(playerid, textPlayerLoot[playerid], string);
		    PlayerTextDrawShow(playerid, textPlayerLoot[playerid]);
		    
		    break;
	    }
	}

	#if defined inOnPlayerEnterDynamicArea
	    return inOnPlayerEnterDynamicArea(playerid, areaid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea inOnPlayerEnterDynamicArea
#if defined inOnPlayerEnterDynamicArea
	forward inOnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, areaid) {

	if (GetPlayerVirtualWorld(playerid) != 0)
	    return 1;

	new loot = PlayerData[playerid][dCurrentLoot];

	if (loot != -1 && LootInfo[loot][loot_area] == areaid) {
	    PlayerData[playerid][dCurrentLoot] = -1;
	}
	
	PlayerTextDrawHide(playerid, textPlayerLoot[playerid]);

	#if defined iOnPlayerLeaveDynamicArea
	    iOnPlayerLeaveDynamicArea(playerid, areaid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea iOnPlayerLeaveDynamicArea
#if defined iOnPlayerLeaveDynamicArea
	forward iOnPlayerLeaveDynamicArea(playerid, areaid);
#endif

stock getPlayerMaxSlots(playerid) {
	switch (PlayerData[playerid][dMochila]) {
	    case MOCHILA_TAMANHO_PEQUENO: return 15;
	    case MOCHILA_TAMANHO_MEDIO:   return 25;
	    case MOCHILA_TAMANHO_GRANDE:  return 35;
	    case MOCHILA_TAMANHO_GIGANTE: return 35;
	    default: 					  return 7;
	}
	return 0;
}

stock GetBagName(playerid) {
	new bagname[75];
	switch (PlayerData[playerid][dMochila]) {
	    case MOCHILA_TAMANHO_PEQUENO: bagname = "Mochila (Level 1)";
	    case MOCHILA_TAMANHO_MEDIO:   bagname = "Mochila (Level 2)";
	    case MOCHILA_TAMANHO_GRANDE:  bagname = "Mochila (Level 3)";
	    case MOCHILA_TAMANHO_GIGANTE: bagname = "Mala Grande";
	    default: 					  bagname = "Sem Mochila";
	}
	return bagname;
}

stock GetBackPackModel(playerid) {

	switch (PlayerData[playerid][dMochila]) {
	    case MOCHILA_TAMANHO_PEQUENO: return -1012;
	    case MOCHILA_TAMANHO_MEDIO:   return -1013;
	    case MOCHILA_TAMANHO_GRANDE:  return -1014;
	}
	return 0;
}

stock GetBackPackModelName(playerid) {
	new ret_name[12];
	switch (PlayerData[playerid][dMochila]) {
	    case MOCHILA_TAMANHO_PEQUENO: ret_name = "mdl-1004:b1";
	    case MOCHILA_TAMANHO_MEDIO:   ret_name = "mdl-1004:b2";
	    case MOCHILA_TAMANHO_GRANDE:  ret_name = "mdl-1004:b3";
	}
	return ret_name;
}

stock GetBackPack(type) {

	switch (type) {
	    case ITEM_TYPE_BACKPACK1: return MOCHILA_TAMANHO_PEQUENO;
	    case ITEM_TYPE_BACKPACK2: return MOCHILA_TAMANHO_MEDIO;
	    case ITEM_TYPE_BACKPACK3: return MOCHILA_TAMANHO_GRANDE;
	    case ITEM_TYPE_BACKPACK4: return MOCHILA_TAMANHO_GIGANTE;
	}
	return 0;
}

stock givePlayerMochila(playerid, type) {

	if (type > ITEM_TYPE_BACKPACK3)
	    type = ITEM_TYPE_BACKPACK3;

	switch(type) {
	
	    // Pequena
	    case ITEM_TYPE_BACKPACK1: {
	    
	        PlayerData[playerid][dMochila] = MOCHILA_TAMANHO_PEQUENO;
			// Grudar uma mochila
			SHOP_SetPlayerAttachedObject(playerid, 0, -1012);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[6], "mdl-1019:b1");
	    }
	    // Média
	    case ITEM_TYPE_BACKPACK2: {

            PlayerData[playerid][dMochila] = MOCHILA_TAMANHO_MEDIO;
			// Grudar uma mochila
			SHOP_SetPlayerAttachedObject(playerid, 0, -1013);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[6], "mdl-1019:b2");
	    }
	    // Grande
	    case ITEM_TYPE_BACKPACK3: {

            PlayerData[playerid][dMochila] = MOCHILA_TAMANHO_GRANDE;
			// Grudar uma mochila
			SHOP_SetPlayerAttachedObject(playerid, 0, -1014);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[6], "mdl-1019:b3");
	    }
	    default: {
            PlayerData[playerid][dMochila] = MOCHILA_TAMANHO_NENHUM;
			// Grudar uma mochila
			RemovePlayerAttachedObject(playerid, 0);
			// Textdraw
			PlayerTextDrawSetString(playerid, playerHudTextdraw[6], "INVALID");
	    }
	}
	
	return 1;
}

CMD:darmochilaex(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
	    return 1;

	new player, mochila;
	
	if (sscanf(params, "ud", player, mochila))return 1;
	
	givePlayerMochila(player, ITEM_TYPE_BACKPACK1 + (mochila - 1));
	return 1;
}

CMD:setskinex(playerid, params[]) {

	if (PlayerData[playerid][dAdmin] < 10)
	    return 1;

	new player, skinid;

	if (sscanf(params, "ud", player, skinid))return 1;

	SetPlayerSkin(player, skinid);
	
	PlayerData[player][dSkin] = skinid;
	return 1;
}

stock DropAllPlayerThings(playerid)
{
	static
		Float:x,
		Float:y,
		Float:z;

	// Pegar posição
	GetPlayerPos(playerid, x, y, z);
	
	GuardarArmor(playerid, .forcedrop = true);
	GuardarHelmet(playerid, .forcedrop = true);
	
	if (GetPlayerVirtualWorld(playerid) == 0) {
		if (PlayerData[playerid][dLanterna]) {
		    PlayerData[playerid][dLanterna] = false;
			RemovePlayerAttachedObject(playerid, 7);
			RemovePlayerAttachedObject(playerid, 8);
		    createDroppedItem(x, y, z, "Lanterna", ITEM_TYPE_LANTERNA, 18641, 1, true, GetPlayerVirtualWorld(playerid));
		}

		if (PlayerData[playerid][dGasMask]) {
		    PlayerData[playerid][dGasMask] = false;
			RemovePlayerAttachedObject(playerid, 9);
		    createDroppedItem(x, y, z, "Mascara de gas", ITEM_TYPE_GASMASK, -1020, 1, true, GetPlayerVirtualWorld(playerid));
		}
	}
	
	new weap, ammo;
	for(new slot; slot < 13; slot++)
	{
	    GetPlayerWeaponData(playerid, slot, weap, ammo);
	    if (weap)
	    {
	        createDroppedItem(x, y, z, NomeArma(weap), ITEM_TYPE_WEAPON, weap, ammo, true, GetPlayerVirtualWorld(playerid), .health = AC_WeaponInfo[playerid][slot][slot_health]);
	    }
	}
	
	ResetPlayerWeapons(playerid);

    dropMochila(playerid);
}

stock dropMochila(playerid) {

	static
		Float:x,
		Float:y,
		Float:z;

	// Pegar posição
	GetPlayerPos(playerid, x, y, z);

	// Dropar item de mochila
	if (PlayerData[playerid][dMochila] > MOCHILA_TAMANHO_NENHUM) {
		dropItem(playerid, ITEM_TYPE_BACKPACK1 + (PlayerData[playerid][dMochila] - 1), GetBackPackModel(playerid), 1, GetBagName(playerid), false, false);
	}

	if (countItensInventory(playerid)) {
		// Dropar itens da mochila
		for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {
		
			if (InventarioInfo[playerid][inv][item_valid]) {
				createDroppedItem(x, y, z, InventarioInfo[playerid][inv][item_nome], InventarioInfo[playerid][inv][item_type], InventarioInfo[playerid][inv][item_model], InventarioInfo[playerid][inv][item_quantia], true, GetPlayerVirtualWorld(playerid), .health = InventarioInfo[playerid][inv][item_health]);
			}
		}
	}
	resetInventory(playerid);
	
	givePlayerMochila(playerid, MOCHILA_TAMANHO_NENHUM);
	
	if (PlayerData[playerid][dServerState] == SERVER_STATE_SURVIVAL && !PlayerData[playerid][dDead])
	{
		for(new text; text != sizeof (textHud); text++) {
		    TextDrawShowForPlayer(playerid, textHud[text]);
		}
		GangZoneShowForPlayer(playerid, HUD_GZ, 0x222222FF);
	}
	RemovePlayerMapIcons(playerid);
	
	return 0;
}
/*
stock dropMochila(playerid) {

	if (countItensInventory(playerid)) {
	
		new Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		
		dropItem(playerid, ITEM_TYPE_BACKPACK1 + (PlayerData[playerid][dMochila] - 1), GetBackPackModel(playerid), 1, GetBagName(playerid), false, false);
		
	    new lootid = createLoot(x, y, z, 10, LOOT_TYPE_MOCHILA, true, true, true, 0.0, MAX_ITENS_INVENTARIO, GetPlayerVirtualWorld(playerid));
	    
	    if (lootid == -1) return print("Loot: Não foi possível criar um loot."), 0;

		for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {

			if (InventarioInfo[playerid][inv][item_valid]) {
                addItemToLoot(lootid, InventarioInfo[playerid][inv][item_type], InventarioInfo[playerid][inv][item_model], InventarioInfo[playerid][inv][item_quantia], InventarioInfo[playerid][inv][item_nome]);
			}
		}
	    
	    return 1;
	}
	return 0;
}*/

stock givePlayerItem(playerid, itemtype, modelid, quantidade, itemnome[], Float:health = 100.0) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (!InventarioInfo[playerid][inv][item_valid]) {
		    InventarioInfo[playerid][inv][item_valid] 	= 1;
		    InventarioInfo[playerid][inv][item_type] 	= itemtype;
		    InventarioInfo[playerid][inv][item_model] 	= modelid;
		    InventarioInfo[playerid][inv][item_quantia] = quantidade;
		    InventarioInfo[playerid][inv][item_slots]   = getItemModelSlots(modelid);
		    InventarioInfo[playerid][inv][item_health]  = health;
		    format(InventarioInfo[playerid][inv][item_nome], 75, itemnome);

		    // is notebook?
		    if (modelid == 19893)
		    {
				for(new text; text != sizeof (textHud); text++) {
				    TextDrawHideForPlayer(playerid, textHud[text]);
				}
				GangZoneHideForPlayer(playerid, HUD_GZ);
				ShowPlayerMapIcons(playerid);
		    }

			if (IsPlayerInInventory(playerid)) {
   				// Atualizar os itens
	            updateInventoryText(playerid);
			}

		    return 1;
		}
	}
	return 0;
}

stock setItemToSlot(playerid, slotid, itemtype, modelid, quantidade, itemnome[], Float:health = 100.0) {

	InventarioInfo[playerid][slotid][item_valid] 	= 1;
 	InventarioInfo[playerid][slotid][item_type] 	= itemtype;
  	InventarioInfo[playerid][slotid][item_model] 	= modelid;
   	InventarioInfo[playerid][slotid][item_quantia]  = quantidade;
   	InventarioInfo[playerid][slotid][item_slots]    = getItemModelSlots(modelid);
   	InventarioInfo[playerid][slotid][item_health]   = health;
    format(InventarioInfo[playerid][slotid][item_nome], 75, itemnome);

	if (IsPlayerInInventory(playerid)) {
		// Atualizar os itens
  		updateInventoryText(playerid);
	}
	return 1;
}

callback saveInventory(playerid) {

	if (IsPlayerInBattleRoyale(playerid)) {
		return 0;
	}

	new fileName[128];

	format(fileName, sizeof (fileName), pastaInventario, getNome(playerid));

	new string_inv[128];

	new File: fileInventory;

	for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {

		format(string_inv, sizeof (string_inv), "%s|%d|%d|%d|%d|%d|%.1f\r\n", InventarioInfo[playerid][inv][item_nome],InventarioInfo[playerid][inv][item_valid],
		InventarioInfo[playerid][inv][item_type], InventarioInfo[playerid][inv][item_model], InventarioInfo[playerid][inv][item_quantia], InventarioInfo[playerid][inv][item_slots], InventarioInfo[playerid][inv][item_health]);

		if (inv == 0) {
  			fileInventory = fopen(fileName, io_write);
		} else {
  			fileInventory = fopen(fileName, io_append);
		}
		fwrite(fileInventory, string_inv);
		fclose(fileInventory);
	}
	return 1;
}

callback loadInventory(playerid) {

    if (IsPlayerInBattleRoyale(playerid)) {
		return 0;
	}

	new fileName[128];

	format(fileName, sizeof (fileName), pastaInventario, getNome(playerid));

	new string_read[128];
	new string_inv[7][76];

	new File: fileInventory = fopen(fileName, io_read);

	if (fileInventory) {

		for(new inv; inv != MAX_ITENS_INVENTARIO; inv++) {

			fread(fileInventory, string_read);
			split(string_read, string_inv, '|');

			format(InventarioInfo[playerid][inv][item_nome], 75, string_inv[0]);
		    InventarioInfo[playerid][inv][item_valid] 	= strval(string_inv[1]);
		    InventarioInfo[playerid][inv][item_type] 	= strval(string_inv[2]);
		    InventarioInfo[playerid][inv][item_model] 	= strval(string_inv[3]);
		    InventarioInfo[playerid][inv][item_quantia] = strval(string_inv[4]);
		    InventarioInfo[playerid][inv][item_slots]   = strval(string_inv[5]);
		    InventarioInfo[playerid][inv][item_health]  = floatstr(string_inv[6]);

/*
			if (InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_MADEIRA || InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_ROCHA || InventarioInfo[playerid][inv][item_type] == ITEM_TYPE_METAL)
			{
			    if (InventarioInfo[playerid][inv][item_quantia] > 3000)
			    {
			        InventarioInfo[playerid][inv][item_valid] = 0;
			        InventarioInfo[playerid][inv][item_quantia] = 0;
			    }
			}*/

		    if (strlen(InventarioInfo[playerid][inv][item_nome]) < 2) {
		        resetItem(playerid, inv);
		    }
		}

	    fclose(fileInventory);
	}
	return 1;
}

callback showInventory(playerid) {

	// Verificar se já está no inventpario ou morto
	if ((IsPlayerInInventory(playerid) || PlayerData[playerid][dDead]) && !IsPlayerInBattleRoyale(playerid) || PlayerData[playerid][dCuffed]) {
	    return 1;
	}

	if (IsPlayerInProgress(playerid))
		return 1;

	// Se não estiver em um carro, aplicar uma animação
	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != 2 && playerActualSpeed(playerid) < 6) {
		ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0);
	}

	// Resetar as variaveis antes de abrir
    ItemSelected[playerid] 	  = -1;
    DropSelected[playerid]    = -1;
    PageInventory[playerid]   = 0;
    lastPlayerClick[playerid] = 0;
    DeletePVar(playerid, "PageInventoryDrop");
    SetPVarInt(playerid, "InInventory", 1);

	// Tocar o audio de abrindo a mochila
	Audio_Play(playerid, 23);
	
	// Esconder a barra de vida a necessidades
 	hidePlayerStatus(playerid);
 	
 	// Hide velocimetro
 	PlayerTextDrawHide(playerid, textVelocimetro[playerid]);

	// Mostrar Textdraws
	for(new text; text < sizeof textInventory; text++) {
	    TextDrawShowForPlayer(playerid, textInventory[text]);
	}
	PlayerTextDrawShow(playerid, textPlayerItens[0][playerid]);
	PlayerTextDrawShow(playerid, textPlayerItens[1][playerid]);
    PlayerTextDrawShow(playerid, textPlayerPage[playerid]);
    PlayerTextDrawShow(playerid, textPlayerItemHealth[playerid]);

	PlayerTextDrawSetString(playerid, textPlayerDrop[0][playerid], "_");
	PlayerTextDrawSetString(playerid, textPlayerDrop[1][playerid], "_");

	PlayerTextDrawShow(playerid, textPlayerDrop[0][playerid]);
	PlayerTextDrawShow(playerid, textPlayerDrop[1][playerid]);
	PlayerTextDrawShow(playerid, textPlayerPageDrop[playerid]);
	PlayerTextDrawShow(playerid, textPlayerDropHealth[playerid]);

	for(new index; index < 8; index++) {
	    // Inventory itens
	    PlayerTextDrawShow(playerid, p_ItensInventory[index]);
	    // Droppes itens
	    PlayerTextDrawShow(playerid, p_DropInventory[index]);
	}

	// Selecionar as textdraws
	SelectTextDraw(playerid, 0xFFFFFFCC);

	// Update nas textdraws
	updateInventoryText(playerid);
	
	// Procurar itens no chão
	searchItens(playerid);
	
	// outros
	for(new text; text < 5; text++) {
	    if (text == 1 || text == 2 || text == 3)continue;
		PlayerTextDrawShow(playerid, textPlayerInventory [text]);
	}
	
	for(new text; text < sizeof playerItemsEquip; text++) {
		PlayerTextDrawShow(playerid, playerItemsEquip[text]);
	}
	PlayerTextDrawShow(playerid, playerHealthProtect);
	
	// Atualizar textdraw das armas
	updateWeaponSelect(playerid);
	
	UpdatePlayerItemsName(playerid);
	
	new string[75];
	
	foreach(new lootid : iterLoots)
	{
	    if (LootInfo[lootid][loot_type] == LOOT_TYPE_VEHICLE && IsPlayerInLoot(playerid, lootid, .checklock = 1))
		{
  			format(string, sizeof string, GetPlayerLanguageKey(playerid, "INFO_3"), countLootItens(lootid), LootInfo[lootid][loot_slots]);
		    PlayerTextDrawSetString(playerid, textPlayerLoot[playerid], string);
		    PlayerTextDrawShow(playerid, textPlayerLoot[playerid]);
  			// Abrir portamalas
     		VehicleBootState(LootInfo[lootid][loot_vehicle], 1);
     		SetPVarInt(playerid, "d_LastVehicle", LootInfo[lootid][loot_vehicle]);
		}
	}
	
	updateTextdrawsLang(playerid);

	return 1;
}

stock updateInventoryText(playerid) {

	if (!IsPlayerInInventory(playerid)) {
	    return 0;
	}

	static string_inv[2][425];
	new string_health[200];
    new string[55];

    string_inv[0][0] = EOS;
    string_inv[1][0] = EOS;

	for(new itemid = (PageInventory[playerid] * 8), index; itemid < (PageInventory[playerid] + 1) * 8; itemid++, index++) {
	    // Set model
	    format(string, sizeof string, "mdl-1005:%d", InventarioInfo[playerid][itemid][item_model]);
	    PlayerTextDrawSetString(playerid, p_ItensInventory[index], string);
	    // Set name
	    format(string, sizeof (string), InventarioInfo[playerid][itemid][item_valid] ? ("%s%s~n~~n~~n~") : ("~w~~h~_~n~~n~~n~"), ItemSelected[playerid] == itemid ? ("~b~~h~~h~") : ("~w~~h~"), InventarioInfo[playerid][itemid][item_nome]);
	    strcat(string_inv[0], string);
	    format(string, sizeof (string), InventarioInfo[playerid][itemid][item_valid] ? ("%s%d~n~~n~~n~") : ("~w~~h~_~n~~n~~n~"), ItemSelected[playerid] == itemid ? ("~b~~h~~h~") : ("~w~~h~"), InventarioInfo[playerid][itemid][item_quantia]);
	    strcat(string_inv[1], string);
	    format(string, sizeof (string), InventarioInfo[playerid][itemid][item_valid] ? ("%.0f%%~n~~n~~n~") : ("_~n~~n~~n~"), InventarioInfo[playerid][itemid][item_health]);
	    strcat(string_health, string);
	}

	PlayerTextDrawSetString(playerid, textPlayerItens[0][playerid], string_inv[0]);
	PlayerTextDrawSetString(playerid, textPlayerItens[1][playerid], string_inv[1]);
	PlayerTextDrawSetString(playerid, textPlayerItemHealth[playerid], string_health);

	// Página atual
	format(string, sizeof (string), "%d-%d", PageInventory[playerid] + 1, MAX_PAGES_INVENTORY + 1);
	PlayerTextDrawSetString(playerid, textPlayerPage[playerid], string);
	
	return 1;
}

stock atualizarDropSelect(playerid) {

	static string_inv[2][420];
	new string_health[200];
    new string[45];
    new count_items = 0;

    string_inv[0][0] = EOS;
    string_inv[1][0] = EOS;

	new atualpagina = GetPVarInt(playerid, "PageInventoryDrop");

	for(new itens = (atualpagina * 8), index; itens < (atualpagina + 1) * 8; itens++, index++) {

		if (InventarioDrop[playerid][itens][item_valid]) {
		    new dropid = InventarioDrop[playerid][itens][item_dropid];

			switch(InventarioDrop[playerid][itens][item_type]) {

				case DROP_TYPE_NONE: {
				    // Set model
				    format(string, sizeof string, "mdl-1005:%d", DropItensInfo[dropid][drop_model]);
				    PlayerTextDrawSetString(playerid, p_DropInventory[index], string);
				    // Set name
				    format(string, sizeof (string), "%s%s ~n~_~n~_~n~_", DropSelected[playerid] == itens ? ("~b~~h~~h~") : ("~w~~h~"), DropItensInfo[dropid][drop_nome]);
				    strcat(string_inv[0], string);
				    format(string, sizeof (string), "%s%d~n~_~n~_~n~_", DropSelected[playerid] == itens ? ("~b~~h~~h~") : ("~w~~h~"), DropItensInfo[dropid][drop_quantia]);
				    strcat(string_inv[1], string);
				    format(string, sizeof (string), "%.0f%%~n~_~n~_~n~_", DropItensInfo[dropid][drop_health]);
				    strcat(string_health, string);
				    
				    count_items++;
				}
				case DROP_TYPE_LOOT: {
				    new lootslot = InventarioDrop[playerid][itens][item_slot];
				    // Set model
				    format(string, sizeof string, "mdl-1005:%d", LootItensInfo[dropid][lootslot][item_model]);
				    PlayerTextDrawSetString(playerid, p_DropInventory[index], string);
				    // Set name
				    format(string, sizeof (string), "%s%s ~n~_~n~_~n~_", DropSelected[playerid] == itens ? ("~b~~h~~h~") : ("~w~~h~"), LootItensInfo[dropid][lootslot][item_nome]);
				    strcat(string_inv[0], string);
				    format(string, sizeof (string), "%s%d~n~_~n~_~n~_", DropSelected[playerid] == itens ? ("~b~~h~~h~") : ("~w~~h~"), LootItensInfo[dropid][lootslot][item_quantia]);
				    strcat(string_inv[1], string);
				    format(string, sizeof (string), "%.0f%%~n~_~n~_~n~_", LootItensInfo[dropid][lootslot][item_health]);
				    strcat(string_health, string);
				    
				    count_items++;
				}
			}
		}
	}
	
	for(new index = count_items; index < 8; index++)
	{
	    PlayerTextDrawSetString(playerid, p_DropInventory[index], "mdl-1005:invalid");
	}
	
	PlayerTextDrawSetString(playerid, textPlayerDrop[0][playerid], string_inv[0]);
	PlayerTextDrawSetString(playerid, textPlayerDrop[1][playerid], string_inv[1]);
	PlayerTextDrawSetString(playerid, textPlayerDropHealth[playerid], string_health);
	
	format(string, sizeof string, "%d-%d", atualpagina + 1, MAX_PAGES_DROP + 1);
	PlayerTextDrawSetString(playerid, textPlayerPageDrop[playerid], string);
}

stock hideInventory(playerid, cancelselect = 1, cancelanim = 1) {

	if (!IsPlayerInInventory(playerid)) {
	    return 0;
	}

	if (!IsPlayerInAnyVehicle(playerid) && GetPlayerSpecialAction(playerid) != 2 && cancelanim) {
	    ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 0, 1, 1, 0, 0);
		ClearAnimations(playerid);
	}

	if (!PlayerData[playerid][dDead] || IsPlayerInBattleRoyale(playerid)) {
	    showPlayerStatus(playerid);
	}

	DeletePVar(playerid, "InInventory");

	// Esconder craft
	hidePlayerCraftTabble(playerid);
	
	// Esconder condições
	hideTextDrawsCondicao(playerid);

	for(new text; text < sizeof textInventory; text++) {
	    TextDrawHideForPlayer(playerid, textInventory[text]);
	}
	PlayerTextDrawHide(playerid, textPlayerItens[0][playerid]);
	PlayerTextDrawHide(playerid, textPlayerItens[1][playerid]);
	PlayerTextDrawHide(playerid, textPlayerPage[playerid]);
	PlayerTextDrawHide(playerid, textPlayerItemHealth[playerid]);
	
	PlayerTextDrawHide(playerid, textPlayerDrop[0][playerid]);
	PlayerTextDrawHide(playerid, textPlayerDrop[1][playerid]);
	PlayerTextDrawHide(playerid, textPlayerPageDrop[playerid]);
	PlayerTextDrawHide(playerid, textPlayerDropHealth[playerid]);
	
	TextDrawHideForPlayer(playerid, textLanterna);
	TextDrawHideForPlayer(playerid, textGasMask);

	for(new text; text < 5; text++)
		PlayerTextDrawHide(playerid, textPlayerInventory [text]);

	if (IsPlayerInAnyVehicle(playerid)) {
	    PlayerTextDrawShow(playerid, textVelocimetro[playerid]);
	}
	
	for(new text; text < sizeof playerItemsEquip; text++) {
		PlayerTextDrawHide(playerid, playerItemsEquip[text]);
	}
	
	PlayerTextDrawHide(playerid, playerHealthProtect);
	
	for(new index; index < 8; index++) {
	    // Inventory itens
	    PlayerTextDrawHide(playerid, p_ItensInventory[index]);
	    // Droppes itens
	    PlayerTextDrawHide(playerid, p_DropInventory[index]);
	}
	
	hideTextItemDiscription(playerid);

	if (cancelselect)
		CancelSelectTextDraw(playerid);
	
	HidePlayerDialog(playerid);

	if (GetPVarInt(playerid, "d_LastVehicle") != 0) {
	    PlayerTextDrawHide(playerid, textPlayerLoot[playerid]);
	    DeletePVar(playerid, "d_LastVehicle");
	}

	foreach(new lootid : iterLoots)
	{
	    if (LootInfo[lootid][loot_type] == LOOT_TYPE_VEHICLE && IsPlayerInLoot(playerid, lootid))
		{
  			// Abrir portamalas
     		VehicleBootState(LootInfo[lootid][loot_vehicle], 0);
		}
	}

	return 1;
}

stock IsSpecialType(type) {

	switch(type) {
		case ITEM_TYPE_WEAPON, ITEM_TYPE_DINHEIRO, ITEM_TYPE_GASOLINA, ITEM_TYPE_AMMO_MP5, ITEM_TYPE_AMMO_M4, ITEM_TYPE_AMMO_DEAGLE, ITEM_TYPE_MADEIRA, ITEM_TYPE_METAL, ITEM_TYPE_ROCHA,
			 ITEM_TYPE_AMMO_SHOTGUN, ITEM_TYPE_AMMO_AK47, ITEM_TYPE_AMMO_SILENCER, ITEM_TYPE_AMMO_SNIPER, ITEM_TYPE_AMMO_RIFLE, ITEM_TYPE_AMMO_9MM, ITEM_TYPE_AMMO_TEC9: return 1;
	}
	return 0;
}

callback utilizarItem(playerid, itemid) {

	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO) {
		return 0;
	}

    HidePlayerDialog(playerid);

	if (InventarioInfo[playerid][itemid][item_type]) {

		if (OnPlayerUseItem(playerid, itemid, InventarioInfo[playerid][itemid][item_nome], InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], InventarioInfo[playerid][itemid][item_quantia])) {

			InventarioInfo[playerid][itemid][item_quantia] --;

			if (IsSpecialType(InventarioInfo[playerid][itemid][item_type]))
			{
				InventarioInfo[playerid][itemid][item_quantia] = 0;
			}

	    	if (InventarioInfo[playerid][itemid][item_quantia] <= 0) {

				resetItem(playerid, itemid, true);
				ItemSelected[playerid] = -1;
	    	}
		}
	} else {
	    SendLanguageMessage(playerid, corError, "MSG_070");
	}

    updateInventoryText(playerid);

	return 1;
}

callback dropAllItensType(playerid, itemtype) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
  			dropItem(playerid, itemtype, InventarioInfo[playerid][inv][item_model], InventarioInfo[playerid][inv][item_quantia], InventarioInfo[playerid][inv][item_nome]);
			resetItem(playerid, inv);
		}
	}

	updateInventoryText(playerid);
	return 1;
}

stock IsPlayerHaveItem(playerid, itemtype) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            return 1;
		}
	}
	return 0;
}

stock GetPlayerQuantiaItem(playerid, itemtype) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            return InventarioInfo[playerid][inv][item_quantia];
		}
	}
	return 0;
}

stock IsPlayerHaveItemQuantia(playerid, itemtype, quantia) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            if (InventarioInfo[playerid][inv][item_quantia] >= quantia) return 1;
		}
	}
	return 0;
}

stock IsPlayerHaveItemQuantiaEx(playerid, itemtype, quantia) {

	if (quantia < 1)
		return 1;

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
            if (InventarioInfo[playerid][inv][item_quantia] >= quantia) return 1;
		}
	}
	return 0;
}

stock RemoveQuantiaItem(playerid, itemtype, quantia) {

	if (quantia < 1)
	    return 0;

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {

			if (InventarioInfo[playerid][inv][item_quantia] > 0) {
				InventarioInfo[playerid][inv][item_quantia] -= quantia;

		    	if (InventarioInfo[playerid][inv][item_quantia] <= 0) {
					resetItem(playerid, inv, true);
		    	}

				if (IsPlayerInInventory(playerid)) {
					ItemSelected[playerid] = -1;
			    }

			    updateInventoryText(playerid);
			    return 1;
			}
		}
	}
	return 0;
}

stock RemoveQuantiaIndex(playerid, index, quantia) {

	if (quantia < 1)
	    return 0;

	if (InventarioInfo[playerid][index][item_valid]) {

		if (InventarioInfo[playerid][index][item_quantia] > 0) {
			InventarioInfo[playerid][index][item_quantia] -= quantia;

		   	if (InventarioInfo[playerid][index][item_quantia] <= 0) {
				resetItem(playerid, index, true);
		   	}

			if (IsPlayerInInventory(playerid)) {
				ItemSelected[playerid] = -1;
		    }

		    updateInventoryText(playerid);
		    return 1;
		}
	}
	return 0;
}

stock AddQuantiaItem(playerid, itemtype, quantia) {

	if (quantia < 1)
	    return 0;

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {

			InventarioInfo[playerid][inv][item_quantia] += quantia;

		    updateInventoryText(playerid);
		    return 1;
		}
	}
	return 0;
}

stock IsPlayerHaveItemModel(playerid, itemmodel) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_model] == itemmodel) {
            return 1;
		}
	}
	return 0;
}

callback ResetAllItensType(playerid, itemtype) {

	for(new inv; inv != getPlayerMaxSlots(playerid); inv++) {

		if (InventarioInfo[playerid][inv][item_valid] && InventarioInfo[playerid][inv][item_type] == itemtype) {
			resetItem(playerid, inv);
		}
	}

	updateInventoryText(playerid);

	return 0;
}

callback AddQuantiaToSlot(playerid, itemid, quantia) {

	if (InventarioInfo[playerid][itemid][item_valid]) {

		InventarioInfo[playerid][itemid][item_quantia] += quantia;

		if (InventarioInfo[playerid][itemid][item_quantia] < 0)
		    InventarioInfo[playerid][itemid][item_quantia] = 0;

	    updateInventoryText(playerid);
	    
	    return 1;
	}
	return 0;
}

stock IsItemUtilizavel(playerid, itemid) {
 	#pragma unused playerid, itemid
	return 1;
}

stock IsPlayerInLoot(playerid, loot, checklock = 0) {

	if (GetPlayerVirtualWorld(playerid) != LootInfo[loot][loot_world])
	    return 0;

	if (LootInfo[loot][loot_type] != LOOT_TYPE_VEHICLE) {

		new Float:range = 1.2;

		if (LootInfo[loot][loot_type] == LOOT_TYPE_AIRDROP)
            range = 1.9;

		else if (LootInfo[loot][loot_type] == LOOT_TYPE_BARRACA)
            range = 2.3;

		if (IsPlayerInRangeOfPoint(playerid, range, LootInfo[loot][loot_x], LootInfo[loot][loot_y], LootInfo[loot][loot_z])) {
		    return 1;
		}
		
	} else {
		if (IsPlayerAtVehicleTrunk(playerid, LootInfo[loot][loot_vehicle])) {
		
		    if (VehicleInfo[LootInfo[loot][loot_vehicle]][vehLocked])
			{
		        if (checklock)
		        {
			        PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
			        SendServerMessageToPlayer(playerid, "Este porta-malas esta trancado");
				}
		        return 0;
		    }
		
		    return 1;
		}
	}
	return 0;
}

stock searchItens(playerid) {

	static Float:playerPos[3];
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	
	foreach(new xplayer : Player) {
	
	    // Verificar se o player está morto
	    if ( PlayerData[xplayer][dDead] && !IsPlayerInBattleRoyale(playerid)) continue;
	    
	    // Verificar se o player está perto
	    if ( IsPlayerInRangeOfPoint(xplayer, 10.0, playerPos[0], playerPos[1], playerPos[2]) ) {
	        searchPlayerItens(xplayer);
	    }
	}
}

new inventory_items[400];

stock searchPlayerItens(playerid) {

	if (!IsPlayerInInventory(playerid)) return 0;

	// Resetar os itens
    for(new item; item < MAX_ITENS_DROP_VIEW; item++) InventarioDrop[playerid][item][item_valid] = 0;

	new itemid = 0;
	
	new bindex = getPlayerBase(playerid);

	// Procurar Loots
	if (PlayerData[playerid][dPlayerBlocked])
	{
	    ShowPlayerBaseProtectDialog(playerid);
	}
	else if (bindex != -1 && serverBaseHaveArmario(bindex) && !IsNicknameAuthorized(bindex, getNome(playerid)))
	{
	    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Você não está autorizado", "{FF0000}INFO: Você precisa estar autorizado no armário para mexer nos baús.", "Ok", "");
	}
	else
	{
		foreach(new loot : iterLoots) {

		    if (IsPlayerInLoot(playerid, loot)) {
		        // Procurar itens no loot
				for(new item; item < LootInfo[loot][loot_slots]; item++) {
				    // Caso o item for válido
				    if (LootItensInfo[loot][item][item_valid] && itemid < MAX_ITENS_DROP_VIEW) {
					    // Setar o item
		       			InventarioDrop[playerid][itemid][item_valid]  = 1;
		       			InventarioDrop[playerid][itemid][item_type]   = DROP_TYPE_LOOT;
		           		InventarioDrop[playerid][itemid][item_dropid] = loot;
		           		InventarioDrop[playerid][itemid][item_slot]   = item;
			           	itemid ++;
			           	if (itemid >= MAX_ITENS_DROP_VIEW) break;
				    }
				}
		    }
		    if (itemid >= MAX_ITENS_DROP_VIEW) break;
		}
	}

	if (itemid < MAX_ITENS_DROP_VIEW)
	{
		static
		    Float:x,
		    Float:y,
		    Float:z;

		GetPlayerPos(playerid, x, y, z);

	    new count = Streamer_GetNearbyItems(x, y, z, STREAMER_TYPE_OBJECT, inventory_items, .range = 3.0);
		
		if (count > sizeof (inventory_items))
		    count = sizeof (inventory_items) - 1;

		for(new index; index < count; index++) {

			new drop = Streamer_GetIntData(STREAMER_TYPE_OBJECT, inventory_items[index], E_STREAMER_EXTRA_ID);

		    if (drop) {

		    	if (GetPlayerVirtualWorld(playerid) != DropItensInfo[drop][drop_world])
		        	continue;

				if ( itemid < MAX_ITENS_DROP_VIEW )
				{
		            InventarioDrop[playerid][itemid][item_valid]  = 1;
		            InventarioDrop[playerid][itemid][item_type]   = DROP_TYPE_NONE;
		            InventarioDrop[playerid][itemid][item_dropid] = drop;
			        itemid ++;
			        
			        if (itemid >= MAX_ITENS_DROP_VIEW) break;
		        }
		    }
		}
	}
	atualizarDropSelect(playerid);

	return 1;
}

stock GivePlayerWeaponByType(playerid, type) {

	for(new slot; slot != 13; slot++) {

	    static slot__weaponid, slot__ammo;
	    GetPlayerWeaponData(playerid, slot, slot__weaponid, slot__ammo);

	    if (slot__weaponid && GetWeaponType(slot__weaponid) == type) {

            new slots = getItemModelSlots(slot__weaponid);

			// Verificar se o inventário está cheio
			if (isInventoryFreeSpace(playerid, slots)) {

				// Guardar a arma no inventário
		        givePlayerItem(playerid, ITEM_TYPE_WEAPON, slot__weaponid, slot__ammo, NomeArma(slot__weaponid), GetWeaponHealth(playerid, slot__weaponid));

				// Barra de progresso
//				StartPlayerProgress(playerid, "Guardando arma...", 60,  10.0);
			// Caso estiver cheio
			} else {

			    // Pegar a posição
				new Float:pos[3];
				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

				// Dropar a arma
	   			createDroppedItem(pos[0], pos[1], pos[2], NomeArma(slot__weaponid), ITEM_TYPE_WEAPON, slot__weaponid, slot__ammo, .world = GetPlayerVirtualWorld(playerid), .health = GetWeaponHealth(playerid, slot__weaponid));

//				StartPlayerProgress(playerid, "Dropando arma...", 60,  10.0);

				// Procurar itens no chao
				if (IsPlayerInInventory(playerid)) {
					searchItens(playerid);
				}
			}
			// Remover a arma das mãos
			RemovePlayerWeapon(playerid, slot__weaponid);

			// Atualizar as textdraws de armas
			if (IsPlayerInInventory(playerid)) {
				updateWeaponSelect(playerid);
			}
			break;
	    }
	}
}

stock updateWeaponSelect(playerid) {

    if (!IsPlayerInInventory(playerid)) return 0;
    
    new weaponid[3], ammo[3];
    new string[45];
    
    weaponid[0] = 0; ammo[0] = 0;
    GetPlayerWeaponByType(playerid, WEAPON_TYPE_PRIMARY, weaponid[0], ammo[0]);
    
    if (weaponid[0]) {
        format(string, sizeof string, "mdl-1015:%d", weaponid[0]);
        PlayerTextDrawSetString(playerid, textPlayerInventory [1], string);
    } else {
        PlayerTextDrawSetString(playerid, textPlayerInventory [1], "mdl-INVALID");
    }
    
    weaponid[1] = 0; ammo[1] = 0;
    GetPlayerWeaponByType(playerid, WEAPON_TYPE_SECONDARY, weaponid[1], ammo[1]);

    if (weaponid[1]) {
        format(string, sizeof string, "mdl-1015:%d", weaponid[1]);
        PlayerTextDrawSetString(playerid, textPlayerInventory [2], string);
    } else {
        PlayerTextDrawSetString(playerid, textPlayerInventory [2], "mdl-INVALID");
    }
    
    weaponid[2] = 0; ammo[2] = 0;
    GetPlayerWeaponByType(playerid, WEAPON_TYPE_TERTIARY, weaponid[2], ammo[2]);

    if (weaponid[2]) {
        format(string, sizeof string, "mdl-1015:%d", weaponid[2]);
        PlayerTextDrawSetString(playerid, textPlayerInventory [3], string);
    } else {
        PlayerTextDrawSetString(playerid, textPlayerInventory [3], "mdl-INVALID");
    }
    
    format(string, sizeof string, "%d~n~~n~%d~n~~n~%d", ammo[0], ammo[1], ammo[2]);
	PlayerTextDrawSetString(playerid, textPlayerInventory [4], string);
	
	if (!PlayerData[playerid][dCrafting] && !PlayerData[playerid][dCondicao]) {
		PlayerTextDrawShow(playerid, textPlayerInventory [1]);
		PlayerTextDrawShow(playerid, textPlayerInventory [2]);
		PlayerTextDrawShow(playerid, textPlayerInventory [3]);
	}

	return 1;
}

callback droparItem(playerid, itemid) {

	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO) {
		return 0;
	}

	if (InventarioInfo[playerid][itemid][item_type]) {

		if (dropItem(playerid, InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], InventarioInfo[playerid][itemid][item_quantia], InventarioInfo[playerid][itemid][item_nome], .healthh = InventarioInfo[playerid][itemid][item_health]) == -1) {
			return 1;
		}

		#if defined OnPlayerDropItem
        	OnPlayerDropItem(playerid, InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], InventarioInfo[playerid][itemid][item_quantia], InventarioInfo[playerid][itemid][item_nome]);
		#endif
		new modelid = InventarioInfo[playerid][itemid][item_model];

		InventarioInfo[playerid][itemid][item_quantia] = 0;
		resetItem(playerid, itemid, true);
		ItemSelected[playerid] = -1;
        updateInventoryText(playerid);
        
        if (modelid == 19893)
        {
			if (PlayerData[playerid][dServerState] == SERVER_STATE_SURVIVAL && !PlayerData[playerid][dDead])
			{
				for(new text; text != sizeof (textHud); text++) {
				    TextDrawShowForPlayer(playerid, textHud[text]);
				}
				GangZoneShowForPlayer(playerid, HUD_GZ, 0x222222FF);
				RemovePlayerMapIcons(playerid);
			}
		}
	}
	return 1;
}

stock GetWeaponAmmoType(model) {

	switch(model) {
	    case 29:
			return ITEM_TYPE_AMMO_MP5;
	    case 31:
			return ITEM_TYPE_AMMO_M4;
	    case 24:
			return ITEM_TYPE_AMMO_DEAGLE;
	    case 25:
			return ITEM_TYPE_AMMO_SHOTGUN;
	    case 30:
			return ITEM_TYPE_AMMO_AK47;
	    case 22,23,28:
			return ITEM_TYPE_AMMO_9MM;
	    case 34:
			return ITEM_TYPE_AMMO_SNIPER;
	    case 33:
			return ITEM_TYPE_AMMO_RIFLE;
	    case 32:
			return ITEM_TYPE_AMMO_TEC9;
	}
	return -1;
}

callback droparItemQuantia(playerid, itemid, quantia) {

	if (itemid < 0 || itemid >= MAX_ITENS_INVENTARIO) {
		return 0;
	}

	if (InventarioInfo[playerid][itemid][item_type]) {

		if (InventarioInfo[playerid][itemid][item_type] == ITEM_TYPE_WEAPON && GetWeaponAmmoType(InventarioInfo[playerid][itemid][item_model]) != -1) {

			new type = GetWeaponAmmoType(InventarioInfo[playerid][itemid][item_model]);

			if (dropItem(playerid, type, getItemModelByType(type), quantia, getItemTypeName(GetWeaponAmmoType(InventarioInfo[playerid][itemid][item_model])), .healthh = InventarioInfo[playerid][itemid][item_health]) == -1) {
				return 1;
			}
		} else {
			if (dropItem(playerid, InventarioInfo[playerid][itemid][item_type], InventarioInfo[playerid][itemid][item_model], quantia, InventarioInfo[playerid][itemid][item_nome], .healthh = InventarioInfo[playerid][itemid][item_health]) == -1) {
				return 1;
			}
		}

		InventarioInfo[playerid][itemid][item_quantia] -= quantia;
		
		if (InventarioInfo[playerid][itemid][item_quantia] <= 0 && InventarioInfo[playerid][itemid][item_type] != ITEM_TYPE_WEAPON) {
			resetItem(playerid, itemid, true);
		}
		
		ItemSelected[playerid] = -1;
        updateInventoryText(playerid);
	}
	return 1;
}


stock isSlotOccupied(playerid, slotid) {

	new weaponid, ammo;
	GetPlayerWeaponData(playerid, slotid, weaponid, ammo);

	if (weaponid) return 1;

	return 0;
}

stock giveWeaponAmmo(playerid, weaponid, amount) {

	new weapon, ammo, slotid;
	
	slotid = GetWeaponSlot(weaponid);
	
	GetPlayerWeaponData(playerid, slotid, weapon, ammo);

	SetPlayerAmmo(playerid, weaponid, ammo + amount);

	return 1;
}

stock dropSlotWeapon(playerid, slotid) {

	new weaponid, ammo;
	GetPlayerWeaponData(playerid, slotid, weaponid, ammo);
	
	if (weaponid) {
	
	    // Pegar a posição
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

		// Dropar a arma
  		createDroppedItem(pos[0], pos[1], pos[2], NomeArma(weaponid), ITEM_TYPE_WEAPON, weaponid, ammo, .health = GetWeaponHealth(playerid, weaponid));
	
	    // remover a arma
	    RemovePlayerWeapon(playerid, weaponid);
	    
	    return 1;
	}
	return 0;
}

stock guardarWeapon(playerid, slotid) {

	new weaponid, ammo;
	GetPlayerWeaponData(playerid, slotid, weaponid, ammo);

	// Verificar se a arma é válida
	if (weaponid) {

		new slots = getItemModelSlots(weaponid);

		// Verificar se o inventário está cheio
		if (isInventoryFreeSpace(playerid, slots)) {

			// Guardar a arma no inventário
	        givePlayerItem(playerid, ITEM_TYPE_WEAPON, weaponid, ammo, NomeArma(weaponid), GetWeaponHealth(playerid, weaponid));

		// Caso estiver cheio
		} else {
		
		    // Pegar a posição
			new Float:pos[3];
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

			// Dropar a arma
   			createDroppedItem(pos[0], pos[1], pos[2], NomeArma(weaponid), ITEM_TYPE_WEAPON, weaponid, ammo, .health = GetWeaponHealth(playerid, weaponid));

			// Procurar itens no chao
			searchItens(playerid);
		}
		// Remover a arma das mãos
		RemovePlayerWeapon(playerid, weaponid);
		
		// Atualizar as textdraws de armas
		updateWeaponSelect(playerid);
		
		return 1;
	}
	return 0;
}

stock GetPlayerTenda(playerid) {

	// Procurar Loots
	foreach(new loot : iterLoots) {

		switch(LootInfo[loot][loot_type]) {

			case LOOT_TYPE_BARRACA:{

				if (IsPlayerInLoot(playerid, loot)) {

					return loot;
				}
			}
		}
	}
	return -1;
}

stock GetPlayerLoot(playerid) {

	// Procurar Loots
	foreach(new loot : iterLoots) {

		switch(LootInfo[loot][loot_type]) {

			case LOOT_TYPE_TENDA, LOOT_TYPE_BARRACA, LOOT_TYPE_VEHICLE:{

				if (IsPlayerInLoot(playerid, loot)) {

					return loot;
				}
			}
		}
	}
	return -1;
}

stock GetPlayerClossestLoot(playerid) {

	// Procurar Loots
	foreach(new loot : iterLoots) {

		if (IsPlayerInLoot(playerid, loot)) {

			return loot;
		}
	}
	return -1;
}


stock dropItem(playerid, type, model, quantia, itemnome[], bool:useanim=true, bool:useloot=true, Float:healthh = 100.0) {

	if (quantia < 0 || type == ITEM_TYPE_NONE) {
	    return -1;
	}

	if (useloot && !PlayerData[playerid][dPlayerBlocked]) {
	
	    new curloot;
	    new slots;
	    new index = getPlayerBase(playerid);
	    
	    slots = getItemModelSlots(model);
	
	/*
		if (IsPlayerInAnyVehicle(playerid)) {

		    curloot = GetVehicleLoot(GetPlayerVehicleID(playerid));
		    
		} else {
		
		    curloot = GetPlayerLoot(playerid);
		}*/
		curloot = GetPlayerLoot(playerid);

		if (index != -1 && serverBaseHaveArmario(index) && !IsNicknameAuthorized(index, getNome(playerid)))
		{
		    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Você não está autorizado", "{FF0000}INFO: Você precisa estar autorizado no armário para mexer nos baús.", "Ok", "");
		}

		// Checar se está em uma tenda e se ela estiver espaço
		else if (curloot != -1) {

			if (!isLootFreeSpace(curloot, slots)) {
			
				SendLanguageMessagef(playerid, corError, (LootInfo[curloot][loot_type] == LOOT_TYPE_TENDA || LootInfo[curloot][loot_type] == LOOT_TYPE_BARRACA) ? ("MSG_071") : ("MSG_072"), slots);
			
			    return -1;
			}

			addItemToLoot(curloot, type, model, quantia, itemnome, .health = healthh);

			if (GetPVarInt(playerid, "d_LastVehicle") != 0) {
			    new string[75];
  				format(string, sizeof string, GetPlayerLanguageKey(playerid, "INFO_3"), countLootItens(curloot), LootInfo[curloot][loot_slots]);
		    	PlayerTextDrawSetString(playerid, textPlayerLoot[playerid], string);
			}

			StartPlayerProgress(playerid, "Aguarde...", 150,  25.0);
			
			// procurar itens
			searchItens(playerid);
			
			return 1;
		}
	}
	// Ou criar o item no chão

	if (PlayerData[playerid][dPlayerBlocked])
	{
	    ShowPlayerBaseProtectDialog(playerid);
	}

	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	if (!IsPlayerInInventory(playerid) && useanim) {
		ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,0);
	}
	
	new result = createDroppedItem(pos[0], pos[1], pos[2], itemnome, type, model, quantia, true, GetPlayerVirtualWorld(playerid), .health = healthh);
    
    if (result != -1)
    {
		if (type == ITEM_TYPE_CARNECRUA || type == ITEM_TYPE_PEIXE)
		{
			new index = GetPlayerFogueira(playerid);
			if (index != -1)
			{
			    AddItemToServerFogueira(result, index);
			}
		}
    }
    
	// procurar itens
	searchItens(playerid);
	
	return result;
}

stock createDroppedItem(Float:x, Float:y, Float:z, itemnome[], type, model, quantia, bool:raycast=true, world=0, bool:randomize = true, Float:health = 100.0, rdon = -1) {

	if (quantia < 0 || type == ITEM_TYPE_NONE) {
	    return 0;
	}

	if (randomize) {
		x += frandom(1.0) - frandom(1.0);
		y -= frandom(1.0) + frandom(1.0);
	}

	if (raycast)
	{
		CA_RayCastLine(x, y, z + 0.5, x, y, z - 100.0, x, y, z);
		z += 1.0000;
	}
	/*else
	{
		z += 0.9458;
	}*/
	new drop;
	if (rdon == -1) {
		drop = Iter_Free(iterDrops);
	} else {
	    drop = rdon;
	}

	if (drop != -1) {

		Iter_Add(iterDrops, drop);

	    DropItensInfo[drop][drop_x] 		= x;
	    DropItensInfo[drop][drop_y] 		= y;
	    DropItensInfo[drop][drop_z] 		= z;

	    DropItensInfo[drop][drop_type]  	= type;
	    DropItensInfo[drop][drop_model] 	= model;
	    DropItensInfo[drop][drop_quantia] 	= quantia;
	    DropItensInfo[drop][drop_slots]     = getItemModelSlots(model);
	    DropItensInfo[drop][drop_world]     = world;
	    DropItensInfo[drop][drop_health]    = health;

	    format(DropItensInfo[drop][drop_nome], 75, type == ITEM_TYPE_SKIN ? (GetSkinName(model)) : (itemnome));

		static
			Float:item_drop_rx,
			Float:item_drop_ry,
			Float:item_drop_rz,
			Float:item_drop_z
			;
		
        GetItemModelDropInfo(model, item_drop_rx, item_drop_ry, item_drop_rz, item_drop_z);

        DropItensInfo[drop][drop_z] += item_drop_z;

	    if (type == ITEM_TYPE_WEAPON) {
			DropItensInfo[drop][drop_object] = CreateDynamicObject(ObjectsArmas[model],DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_SKIN) {
			DropItensInfo[drop][drop_object] = CreateDynamicObject(2846, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		} else {
		    DropItensInfo[drop][drop_object] = CreateDynamicObject(model, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		}
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, DropItensInfo[drop][drop_object], E_STREAMER_EXTRA_ID, drop);
//		Streamer_ToggleItemCallbacks(STREAMER_TYPE_OBJECT, DropItensInfo[drop][drop_object], 1);
	}
	return drop;
}

stock changeDroppedItemInfo(drop, itemnome[], type, model, quantia, Float:health = 100.0)
{
	if (Iter_Contains(iterDrops, drop))
	{
	    new Float:x = DropItensInfo[drop][drop_x];
	    new Float:y = DropItensInfo[drop][drop_y];
	    new Float:z = DropItensInfo[drop][drop_z];
	    
		CA_RayCastLine(x, y, z + 0.5, x, y, z - 100.0, x, y, z);
		z += 1.0000;

	    DropItensInfo[drop][drop_type]  	= type;
	    DropItensInfo[drop][drop_model] 	= model;
	    DropItensInfo[drop][drop_quantia] 	= quantia;
	    DropItensInfo[drop][drop_slots]     = getItemModelSlots(model);
	    DropItensInfo[drop][drop_health]    = health;

	    format(DropItensInfo[drop][drop_nome], 75, type == ITEM_TYPE_SKIN ? (GetSkinName(model)) : (itemnome));

/*
		static
			Float:item_drop_rx,
			Float:item_drop_ry,
			Float:item_drop_rz,
			Float:item_drop_z
			;

        GetItemModelDropInfo(model, item_drop_rx, item_drop_ry, item_drop_rz, item_drop_z);

        DropItensInfo[drop][drop_z] += item_drop_z;

		DestroyDynamicObject(DropItensInfo[drop][drop_object]);

	    if (type == ITEM_TYPE_WEAPON) {
			DropItensInfo[drop][drop_object] = CreateDynamicObject(ObjectsArmas[model],DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_SKIN) {
			DropItensInfo[drop][drop_object] = CreateDynamicObject(2846, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		} else {
		    DropItensInfo[drop][drop_object] = CreateDynamicObject(model, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], item_drop_rx, item_drop_ry, item_drop_rz, world, -1, -1, 80.0);
		}*/
	    return 1;
	}
	return 0;
}
/*
stock createDroppedItem(Float:x, Float:y, Float:z, itemnome[], type, model, quantia, bool:raycast=true, world=0) {

	if (quantia < 0 || type == ITEM_TYPE_NONE) {
	    return 0;
	}
	
	if (raycast) {
		CA_RayCastLine(x, y, z + 0.5, x, y, z - 100.0, x, y, z);
		z += 0.1;
	}

	new drop = Iter_Free(iterDrops);

	if (drop != -1) {

		Iter_Add(iterDrops, drop);

	    DropItensInfo[drop][drop_x] 		= x + frandom(1.2) - frandom(1.2);
	    DropItensInfo[drop][drop_y] 		= y - frandom(1.2) + frandom(1.2);
	    DropItensInfo[drop][drop_z] 		= z;

	    DropItensInfo[drop][drop_type]  	= type;
	    DropItensInfo[drop][drop_model] 	= model;
	    DropItensInfo[drop][drop_quantia] 	= quantia;
	    DropItensInfo[drop][drop_world]     = world;

	    format(DropItensInfo[drop][drop_nome], 75, type == ITEM_TYPE_SKIN ? (GetSkinName(model)) : (itemnome));

	    if (type == ITEM_TYPE_WEAPON) {

			DropItensInfo[drop][drop_object] = CreateDynamicObject(ObjectsArmas[model],DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 93.7, 120.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_REMEDIO) {

			DropItensInfo[drop][drop_z] += 0.09;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type >= ITEM_TYPE_AMMO_MP5 && type <= ITEM_TYPE_AMMO_RIFLE) {

			DropItensInfo[drop][drop_z] += 0.13;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_PIZZA || type == ITEM_TYPE_COCA) {

			DropItensInfo[drop][drop_z] += 0.075;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_HAMBURGER) {

			DropItensInfo[drop][drop_z] += 0.075;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], -24.0, -84.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_BANDAGE) {

			DropItensInfo[drop][drop_z] += 0.075;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_PNEU) {

			DropItensInfo[drop][drop_z] += 0.100;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, 0.0, world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_MOTOR) {

			// DropItensInfo[drop][drop_z] += 0.100;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_SKIN) {

			DropItensInfo[drop][drop_object] = CreateDynamicObject(2846, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	    else if (type == ITEM_TYPE_GASOLINA) {

			DropItensInfo[drop][drop_z] += 0.100;
            DropItensInfo[drop][drop_object] = CreateDynamicObject(model, DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		} else {

			DropItensInfo[drop][drop_object] = CreateDynamicObject(model,DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], 0.0, 0.0, random(360), world, -1, -1, 80.0);
		}
	}
	return drop;
}*/

stock destroyDropItem(itemid) {

	if (Iter_Contains(iterDrops, itemid)) {

        Streamer_ToggleItemCallbacks(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], 0);

		DestroyDynamicObject(DropItensInfo[itemid][drop_object]);
		
		Iter_Remove(iterDrops, itemid);
		
		return 1;
  	}
	return 0;
}

callback OnPlayerPickUpItem(playerid, itemtype, modelid, quantia, itemname[]) {

	return 1;
}

callback OnPlayerDropItem(playerid, itemtype, modelid, quantia, itemname[]) {

	return 1;
}

/*
CMD:dropskin(playerid, params[]) {

	new string[128];
	
	new skinid = strval(params);
	
	format(string, sizeof string, "Roupa %d", skinid);

	if (isInventoryFreeSpace(playerid, getItemModelSlots(skinid))) {
		givePlayerItem(playerid, ITEM_TYPE_SKIN, skinid, 1, string);
	} else {
		dropItem(playerid, ITEM_TYPE_SKIN, skinid, 1, string, false);
	}
	
	return 1;
}*/

CMD:inventariosex(playerid) {

    if (GetPlayerWeapon(playerid) == 46)
        return 1;

	return (IsPlayerInInventory(playerid) ? (hideInventory(playerid)) : (showInventory(playerid)));
}

stock giveDropObject(playerid) {

	new text = DropSelected[playerid];
 	new dropid = InventarioDrop[playerid][text][item_dropid];

	// checar se o item é valido
	if (!InventarioDrop[playerid][text][item_valid]) return 1;

	switch(InventarioDrop[playerid][text][item_type]) {

		// Caso for um item jogado no chão
		case DROP_TYPE_NONE: {
			// checar se o item ainda está no chão
			if (!Iter_Contains(iterDrops, dropid)) return 1;
			
			switch (DropItensInfo[dropid][drop_type])
			{
				case ITEM_TYPE_DINHEIRO: {
					// Dar o dinheiro
					PlayerData[playerid][dMoney] += DropItensInfo[dropid][drop_quantia];
					// Efeito de som de dinheiro
					Audio_Play(playerid, 40);
					// destruir item
					destroyDropItem(InventarioDrop[playerid][text][item_dropid]);
					// Atualizar os itens
					DropSelected[playerid] = -1;
				 	searchItens(playerid);
				    return 1;
				}
				case ITEM_TYPE_COCA,ITEM_TYPE_BEBIDA,ITEM_TYPE_AMMO_MP5,ITEM_TYPE_AMMO_M4,ITEM_TYPE_AMMO_DEAGLE,ITEM_TYPE_AMMO_SHOTGUN,ITEM_TYPE_AMMO_AK47,
					 ITEM_TYPE_AMMO_SILENCER,ITEM_TYPE_AMMO_SNIPER,ITEM_TYPE_AMMO_RIFLE,ITEM_TYPE_AMMO_9MM,ITEM_TYPE_CARNECRUA,ITEM_TYPE_CARNEASSADA,ITEM_TYPE_BUSSOLA,ITEM_TYPE_CIGARRO,ITEM_TYPE_PEIXE,
			         ITEM_TYPE_SINALFUMACA,ITEM_TYPE_MADEIRA,ITEM_TYPE_RELOGIO,ITEM_TYPE_EXPLOSIVO,ITEM_TYPE_ADRENALINA,ITEM_TYPE_METAL,ITEM_TYPE_ROCHA,ITEM_TYPE_COURO,ITEM_TYPE_AMMO_TEC9,
					 ITEM_TYPE_BANDAGEMI,ITEM_TYPE_PEIXEASSADO,ITEM_TYPE_EXPLOSIVOC4,ITEM_TYPE_EXPLOSIVORE,ITEM_TYPE_POLVORA,ITEM_TYPE_PECAARMA,ITEM_TYPE_ARMAQUEBRADA:
				{
				    if (IsPlayerHaveItem(playerid, DropItensInfo[dropid][drop_type]))
				    {
				        AddQuantiaItem(playerid, DropItensInfo[dropid][drop_type], DropItensInfo[dropid][drop_quantia]);
						// Audio
						Audio_Play(playerid, 34);
						// destruir item
						destroyDropItem(InventarioDrop[playerid][text][item_dropid]);
						// Atualizar os itens
						DropSelected[playerid] = -1;
					 	searchItens(playerid);
				        return 1;
				    }
				}
			}

			if ( !isInventoryFreeSpace(playerid, DropItensInfo[dropid][drop_slots]))
	    		return SendLanguageMessagef(playerid, corError, "MSG_073", DropItensInfo[dropid][drop_slots]);

			// Dar o item
			givePlayerItem(playerid, DropItensInfo[dropid][drop_type], DropItensInfo[dropid][drop_model], DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome], DropItensInfo[dropid][drop_health]);

			// Audio
			Audio_Play(playerid, 34);

			// destruir item
			destroyDropItem(InventarioDrop[playerid][text][item_dropid]);
		}
		// Caso for um item de algum Loot
		case DROP_TYPE_LOOT: {
		
		    new lootslot = InventarioDrop[playerid][text][item_slot];
		    
		    // checar se o item ainda existe
		    if (!LootItensInfo[dropid][lootslot][item_valid]) return 1;
			
			switch (LootItensInfo[dropid][lootslot][item_type])
			{
				case ITEM_TYPE_DINHEIRO: {
					// Dar o dinheiro
					PlayerData[playerid][dMoney] += LootItensInfo[dropid][lootslot][item_quantia];
					// Efeito de som de dinheiro
					Audio_Play(playerid, 40);
					// resetar o slot do loot
					resetLootSlot(dropid, lootslot);
					// Atualizar os itens
					DropSelected[playerid] = -1;
				 	searchItens(playerid);
				    return 1;
				}
				case ITEM_TYPE_COCA,ITEM_TYPE_BEBIDA,ITEM_TYPE_AMMO_MP5,ITEM_TYPE_AMMO_M4,ITEM_TYPE_AMMO_DEAGLE,ITEM_TYPE_AMMO_SHOTGUN,ITEM_TYPE_AMMO_AK47,
					 ITEM_TYPE_AMMO_SILENCER,ITEM_TYPE_AMMO_SNIPER,ITEM_TYPE_AMMO_RIFLE,ITEM_TYPE_AMMO_9MM,ITEM_TYPE_CARNECRUA,ITEM_TYPE_CARNEASSADA,ITEM_TYPE_BUSSOLA,ITEM_TYPE_CIGARRO,ITEM_TYPE_PEIXE,
			         ITEM_TYPE_SINALFUMACA,ITEM_TYPE_MADEIRA,ITEM_TYPE_RELOGIO,ITEM_TYPE_EXPLOSIVO,ITEM_TYPE_ADRENALINA,ITEM_TYPE_METAL,ITEM_TYPE_ROCHA,ITEM_TYPE_COURO,ITEM_TYPE_AMMO_TEC9,
					 ITEM_TYPE_BANDAGEMI,ITEM_TYPE_PEIXEASSADO,ITEM_TYPE_EXPLOSIVOC4,ITEM_TYPE_EXPLOSIVORE,ITEM_TYPE_POLVORA,ITEM_TYPE_PECAARMA,ITEM_TYPE_ARMAQUEBRADA:
				{
				    if (IsPlayerHaveItem(playerid, LootItensInfo[dropid][lootslot][item_type]))
				    {
				        AddQuantiaItem(playerid, LootItensInfo[dropid][lootslot][item_type], LootItensInfo[dropid][lootslot][item_quantia]);
						// Audio
						Audio_Play(playerid, 34);
						// destruir item
						resetLootSlot(dropid, lootslot);
						
				        new baseindex = getPlayerBase(playerid);

				        if (baseindex != -1)
				        {
				            Log::("baseitem", "%s tirou o item %s da base %d", getNome(playerid), LootItensInfo[dropid][lootslot][item_nome], baseindex);
				        }
						
						// Atualizar os itens
						DropSelected[playerid] = -1;
					 	searchItens(playerid);
				        return 1;
				    }
				}
			}
		    
			if ( !isInventoryFreeSpace(playerid, LootItensInfo[dropid][lootslot][item_slots]))
	    		return SendLanguageMessagef(playerid, corError, "MSG_073", LootItensInfo[dropid][lootslot][item_slots]);
		    
			// Dar o item
			givePlayerItem(playerid, LootItensInfo[dropid][lootslot][item_type], LootItensInfo[dropid][lootslot][item_model], LootItensInfo[dropid][lootslot][item_quantia], LootItensInfo[dropid][lootslot][item_nome], LootItensInfo[dropid][lootslot][item_health]);

			// Audio
			Audio_Play(playerid, 34);

			// resetar o slot do loot
			resetLootSlot(dropid, lootslot);
			
	        new baseindex = getPlayerBase(playerid);

	        if (baseindex != -1)
	        {
	            Log::("baseitem", "%s tirou o item %s da base %d", getNome(playerid), LootItensInfo[dropid][lootslot][item_nome], baseindex);
	        }
		}
	}
	// Atualizar seleção
 	DropSelected[playerid] = -1;

	// Atualizar os itens
 	searchItens(playerid);
 	
 	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (IsPlayerInInventory(playerid)) {
	
	    // Se apertar ESC
	    if (clickedid == Text:INVALID_TEXT_DRAW) {
	    
			if (IsPlayerInProgress(playerid) && IsProgressValidId(playerid))
	    		return StopPlayerProgress(playerid), SelectTextDraw(playerid, 0xFFFFFFCC);
	    
	        if (IsPlayerInProgress(playerid)) {
				return SelectTextDraw(playerid, 0xFFFFFFCC);
			}
	    
	        hideInventory(playerid);
	    }
	    
   		if (IsPlayerInProgress(playerid)) {
			return 0;
		}
	    
	    // Dropar o item
	    if (clickedid == textInventory[8]) {

            if (ItemSelected[playerid] > -1) {

				if (PlayerData[playerid][dCrafting])
				    return SendLanguageMessage(playerid, corError, "MSG_074");

				// Largar o item
				droparItem(playerid, ItemSelected[playerid]);
                
                // Atualizar seleção
                ItemSelected[playerid] = -1;
                
	            // Atualizar os itens
	            updateInventoryText(playerid);
	            
	            SetPVarInt(playerid, "p_ItemSelected", -1);
	            HidePlayerDialog(playerid);
            }
			return 1;
	    }
	    
	    else if (clickedid == textInventory[9]) {

            if (ItemSelected[playerid] > -1) {

				if (PlayerData[playerid][dCrafting])
				    return SendLanguageMessage(playerid, corError, "MSG_074");

				new index = ItemSelected[playerid];
				
				new string[128];
				format(string, sizeof string, "{FFFFFF}%d unid. de %s", InventarioInfo[playerid][index][item_quantia], InventarioInfo[playerid][index][item_nome]);
				ShowPlayerDialog(playerid, DIALOG_DROP_ITEM, DIALOG_STYLE_INPUT, string, "{AAAAAA}Digite a {FFFFFF}quantidade {AAAAAA}que deseja dropar.", "Drop", "Cancelar");
				
				// save pvar
				SetPVarInt(playerid, "p_ItemSelected", index);
            }
			return 1;
	    }

		// Book
		else if (clickedid == textInventory[12]) {
		    bookShowForPlayer(playerid, bookCountPagesDiscover(playerid)) ;
		    return 1;
		}
		// Status
		else if (clickedid == textInventory[1]) {
		    HidePlayerDialog(playerid);
		    hidePlayerCraftTabble(playerid);
		    hideTextDrawsCondicao(playerid);
		    showTextDrawsStatus(playerid);
		    updateTextdrawsLang(playerid);
		    return 1;
		}
		// Craft
		else if (clickedid == textInventory[3]) {
		    HidePlayerDialog(playerid);
		    hideTextDrawsCondicao(playerid);
		    showPlayerCraftTabble(playerid);
		    updateTextdrawsLang(playerid);
		    return 1;
		}
		// Condição
		else if (clickedid == textInventory[2]) {
		    HidePlayerDialog(playerid);
		    showTextDrawsCondicao(playerid);
		    return 1;
		}

		// Se clicar em "fechar"
		else if (clickedid == textInventory[11]) {
		
		    // Esconder o inventário
		   	hideInventory(playerid);

		    return 1;
		}
		// Se clicar em "?"
		else if (clickedid == textInventory[10])
		{
			if (ItemSelected[playerid] > -1 || DropSelected[playerid] > -1)
			{
			    showTextItemDiscription(playerid, getItemModelDiscription(GetPVarInt(playerid, "click_model"), GetPVarInt(playerid, "click_type")));
			}
		    return 1;
		}
	    
// Página atual - itens
	    
		// Se voltar uma pagina
		else if (clickedid == textInventory[6]) {

			if (PageInventory[playerid] > 0) {

				// Passar uma página
				PageInventory[playerid] --;

	            // Atualizar os itens
	            updateInventoryText(playerid);
	            
	            // Efeito de som
	            Audio_Play(playerid, 25);
	            
	            HidePlayerDialog(playerid);
			}
		    return 1;
		}
	    
		// Se passar a pagina
		else if (clickedid == textInventory[7]) {

			if (PageInventory[playerid] < MAX_PAGES_INVENTORY) {

				// Passar uma página
				PageInventory[playerid] ++;
			    
	            // Atualizar os itens
	            updateInventoryText(playerid);

	            // Efeito de som
	            Audio_Play(playerid, 25);
			}
		    return 1;
		}
	    
// Página atual - Drops
	    
	    // Se voltar uma pagina
		else if (clickedid == textInventory[4]) {

			if (GetPVarInt(playerid, "PageInventoryDrop") > 0) {

				// Passar uma página
				SetPVarInt(playerid, "PageInventoryDrop", GetPVarInt(playerid, "PageInventoryDrop") - 1);

	            // Atualizar os itens
	            atualizarDropSelect(playerid);

	            // Efeito de som
	            Audio_Play(playerid, 25);
	            
	            HidePlayerDialog(playerid);
			}
		    return 1;
		}

		// Se passar a pagina
		else if (clickedid == textInventory[5]) {

			if (GetPVarInt(playerid, "PageInventoryDrop") < MAX_PAGES_DROP) {

				// Passar uma página
				SetPVarInt(playerid, "PageInventoryDrop", GetPVarInt(playerid, "PageInventoryDrop") + 1);

	            // Atualizar os itens
	            atualizarDropSelect(playerid);

	            // Efeito de som
	            Audio_Play(playerid, 25);
			}
		    return 1;
		}
	}
 	#if defined iOnPlayerClickTextDraw
  		return iOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw iOnPlayerClickTextDraw
#if defined iOnPlayerClickTextDraw
	forward iOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (IsPlayerInInventory(playerid)) {

   		if (IsPlayerInProgress(playerid)) {
			return 0;
		}

		if ( playertextid == textPlayerInventory[1] ) {
		    if (PlayerData[playerid][dCrafting] || PlayerData[playerid][dCondicao])
		        return 1;
		    GivePlayerWeaponByType(playerid, WEAPON_TYPE_PRIMARY);
		}

		else if ( playertextid == textPlayerInventory[2] ) {
  			if (PlayerData[playerid][dCrafting] || PlayerData[playerid][dCondicao])
     			return 1;
            GivePlayerWeaponByType(playerid, WEAPON_TYPE_SECONDARY);
		}

		else if ( playertextid == textPlayerInventory[3] ) {
		    if (PlayerData[playerid][dCrafting] || PlayerData[playerid][dCondicao])
		        return 1;
            GivePlayerWeaponByType(playerid, WEAPON_TYPE_TERTIARY);
		}
		
		else if ( playertextid == textInfoBox[1][playerid] ) {
            hideTextItemDiscription(playerid);
		}
		
		// Retirar colete
		else if (playertextid == playerItemsEquip[1])
		{
			if ((PlayerData[playerid][dLogged] && PlayerData[playerid][dSpawned]) || IsPlayerInBattleRoyale(playerid)) {
			
			    if (PlayerData[playerid][dCrafting] || PlayerData[playerid][dCondicao])
			        return 1;
			
	            GuardarArmor(playerid);
			}
			return 1;
		}
		// Retirar capacete
		else if (playertextid == playerItemsEquip[0])
		{
			if ((PlayerData[playerid][dLogged] && PlayerData[playerid][dSpawned]) || IsPlayerInBattleRoyale(playerid)) {
			
			    if (PlayerData[playerid][dCrafting] || PlayerData[playerid][dCondicao])
			        return 1;
			        
	            GuardarHelmet(playerid);
			}
			return 1;
		}
		
	    // Loop nas textdraws - itens
	    for(new textid; textid < 8; textid++) {

	        // Se for uma Textdraw de itens
	        if (playertextid == p_ItensInventory[textid]) {

	            new itemid = textid + (PageInventory[playerid] * 8);

	            // Checar se o item é valido
	            if (!InventarioInfo[playerid][itemid][item_valid]) return 1;

	            // Barulho de botão
	            Audio_Play(playerid, 28);

	            // Selecionar o item
	            if (ItemSelected[playerid] != itemid) {
	            	ItemSelected[playerid] = itemid;

	            	SetPVarInt(playerid, "click_model", InventarioInfo[playerid][itemid][item_model]);
	            	SetPVarInt(playerid, "click_type", InventarioInfo[playerid][itemid][item_type]);
				} else {

				    // Verificar se deu 2 clicks rápidos
				    if (GetTickCount() < lastPlayerClick[playerid] && !PlayerData[playerid][dCrafting]) {

						// Caso sim, utilizar o item
						utilizarItem(playerid, itemid);

						// Resetar o tempo do click
				        lastPlayerClick[playerid] = 0;

						SetPVarInt(playerid, "p_ItemSelected", -1);

				        return 1;
				    }
				}

				// Guardar o tempo do click
				lastPlayerClick[playerid] = GetTickCount() + CLICK_DELAY;

	            // Atualizar os itens
	            updateInventoryText(playerid);

	            return 1;
	        }
	    }
	    
	    
	    // Loop nas textdraws - drops
	    for(new textid; textid < 8; textid++) {

	        // Se for uma Textdraw de itens
	        if (playertextid == p_DropInventory[textid]) {

                new itemid = textid + (GetPVarInt(playerid, "PageInventoryDrop") * 8);

				// checar se é valido
				if (!InventarioDrop[playerid][itemid][item_valid]) return 1;

	            // Selecionar o item
	            if (DropSelected[playerid] != itemid) {
	            	DropSelected[playerid] = itemid;

                    new dropid = InventarioDrop[playerid][itemid][item_dropid];

                    switch(InventarioDrop[playerid][textid][item_type])
                    {
						// Caso for um item jogado no chão
						case DROP_TYPE_NONE: {
	            			SetPVarInt(playerid, "click_model", DropItensInfo[dropid][drop_model]);
	            			SetPVarInt(playerid, "click_type", DropItensInfo[dropid][drop_type]);
						}
						// Caso for um item de algum Loot
						case DROP_TYPE_LOOT: {
						    new lootslot = InventarioDrop[playerid][itemid][item_slot];
	            			SetPVarInt(playerid, "click_model", LootItensInfo[dropid][lootslot][item_model]);
	            			SetPVarInt(playerid, "click_type", LootItensInfo[dropid][lootslot][item_type]);
						}
                    }
				} else {

				    // Verificar se deu 2 clicks rápidos
				    if (GetTickCount() < lastPlayerClick[playerid]) {

						// Dar o item
						giveDropObject(playerid);

			            // Barulho de dar item
			            //Audio_Play(playerid, 34);

						// Resetar o tempo do click
				        lastPlayerClick[playerid] = 0;

				        return 1;
				    }
				}

	            // Barulho de botão
	            Audio_Play(playerid, 28);

				// Guardar o tempo do click
				lastPlayerClick[playerid] = GetTickCount() + CLICK_DELAY;

				atualizarDropSelect(playerid);

	            return 1;
	        }
	    }
		
		if (PlayerData[playerid][dCrafting]) {
		
			// Craftar
			if (playertextid == playerTextDrawsCraft[9]) {

				new result = craftPlayerItem(playerid);

				if (result == 0) {
				    SendLanguageMessage(playerid, corError, "MSG_075");
				}
				return 1;
			}

			// Receitas
			else if (playertextid == playerTextDrawsCraft[10]) {
			    ListPlayerCraft(playerid);
			    return 1;
			}

			// Resetar
			else if (playertextid == playerTextDrawsCraft[11]) {
			    resetPlayerCraft(playerid);
			    return 1;
			}
		
		    new itemid = ItemSelected[playerid];
		    
		    if (itemid != -1) {
		    
			    for(new text; text < 4; text++) {

					if (playertextid == playerTextDrawsCraft[text + 1]) {
					
					    addPlayerCraftItem(playerid, text, itemid);
					
					    break;
					}
			    }
		    
		        ItemSelected[playerid] = -1;
		    }
		    
	        // Atualizar os itens
	        updateInventoryText(playerid);
		}
	}
 	#if defined zOPCPTD
  		return zOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw zOPCPTD
#if defined zOPCPTD
	forward zOPCPTD(playerid, PlayerText:playertextid);
#endif


