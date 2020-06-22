
enum dSearchEnum {

	search_id,
	search_item_id,
	bool:
	search_viewtd,
}
new cameraSearchItens[MAX_PLAYERS][dSearchEnum];


stock searchCameraItens(playerid) {

	// check if band economy is active
	if (PlayerData[playerid][dEconomia] && !GetPVarInt(playerid, "inAirplane")) return 0;
	
	// get a player target dynamic object id
	new index = GetPlayerCameraTargetDynObject(playerid);

	// check if current target object is invalid
	if (index == INVALID_STREAMER_ID) {

		// check if old target object is valid
		if (cameraSearchItens[playerid][search_item_id] != -1) {
	        cameraSearchItens[playerid][search_item_id] = -1;
	    }

		// check if old itemid is valid
	    if (cameraSearchItens[playerid][search_id] != 0) {
	    	cameraSearchItens[playerid][search_id] = 0;
		    // update textdraw view
		    updateTextCameraItem(playerid);
		}
		return 0;
	}

	// check if current target object id the old
	if (cameraSearchItens[playerid][search_id] != index) {

		// get a dynamic object position
		static Float:x, Float:y, Float:z;
		GetDynamicObjectPos(index, x, y, z);

		// check if player in range of object
		if (!IsPlayerInRangeOfPoint(playerid, 2.49, x, y, z)) {

			// check if old target object is valid
			if (cameraSearchItens[playerid][search_item_id] != -1) {
		        cameraSearchItens[playerid][search_item_id] = -1;
		    }

			// check if old itemid is valid
		    if (cameraSearchItens[playerid][search_id] != 0) {
		        // save variable player behind item
		    	cameraSearchItens[playerid][search_id] = 0;
			}

			// update textdraw view
		    updateTextCameraItem(playerid);
			return 0;
		}

		// save variable value
        cameraSearchItens[playerid][search_item_id] = -1;

		// get int array save into dynamic object id
		new item = Streamer_GetIntData(STREAMER_TYPE_OBJECT, index, E_STREAMER_EXTRA_ID);

		if (item != 0)
		{
			if (IsPlayerInRangeOfPoint(playerid, 2.5, DropItensInfo[item][drop_x], DropItensInfo[item][drop_y], DropItensInfo[item][drop_z])) {
			    // save variable player behind item
				cameraSearchItens[playerid][search_item_id] = item;
			}
		}
		cameraSearchItens[playerid][search_id] = index;
		// Update na textdraw
		updateTextCameraItem(playerid);
	}
	return 1;
}

stock updateTextCameraItem(playerid)
{
	// Item guardado na variavel
	new drop = cameraSearchItens[playerid][search_item_id];
	
	// Verificar se é um item válido
	if (drop != -1)
	{
	    // show textdraws
	    showSearchTextdraws(playerid);
	    // Variável
	    new string[75];
	    // Update na textdraw
	    format(string, sizeof (string), "%s (%d)", DropItensInfo[drop][drop_nome], DropItensInfo[drop][drop_quantia]);
	    PlayerTextDrawSetString(playerid, textCameraItem[playerid], string);
	}
	else
	{
		// Esconder a textdraw
		hideSearchTextdraws(playerid);
	}
}

stock showSearchTextdraws(playerid) {
	// check if viewing textdraws
	if (cameraSearchItens[playerid][search_viewtd])
	    return 0;
	// show textdraws to player
   	TextDrawShowForPlayer(playerid, boxDroppedItem1);
 	TextDrawShowForPlayer(playerid, boxDroppedItem2);
 	PlayerTextDrawShow(playerid, textCameraItem[playerid]);
 	// set variable value
 	cameraSearchItens[playerid][search_viewtd] = true;
 	return 1;
}

stock hideSearchTextdraws(playerid) {
    // check if viewing textdraws
	if (!cameraSearchItens[playerid][search_viewtd])
	    return 0;
    // hide textdraws to player
   	TextDrawHideForPlayer(playerid, boxDroppedItem1);
 	TextDrawHideForPlayer(playerid, boxDroppedItem2);
 	PlayerTextDrawHide(playerid, textCameraItem[playerid]);
 	// set variable value
 	cameraSearchItens[playerid][search_viewtd] = false;
 	return 1;
}

stock givePlayerTargetItem(playerid)
{
	// check last pick up
	if (GetTickCount() < GetPVarInt(playerid, "p_LastPickup"))
	    return 0;
	// Item guardado na variavel
	new dropid = cameraSearchItens[playerid][search_item_id];

	// Verificar se é um item válido
	if (dropid != -1)
	{
		// checar se o item ainda está no chão
		if (!Iter_Contains(iterDrops, dropid)) return 0;

        new string[75];
		
		if (DropItensInfo[dropid][drop_type] == ITEM_TYPE_DINHEIRO)
		{
			// Dar o dinheiro
			PlayerData[playerid][dMoney] += DropItensInfo[dropid][drop_quantia];

			// Efeito de som de dinheiro
			Audio_Play(playerid, 40);

			// Mensagem
			format(string, sizeof (string), "+$%d %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
			SendServerMessageToPlayer(playerid, string);
			// set last pick up and anim
			ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
			// destruir item
			destroyDropItem(dropid);
			
			// Reset item
			cameraSearchItens[playerid][search_item_id] = -1;
		    return 1;
		}
		
		switch (DropItensInfo[dropid][drop_type]) {
		    // if a weapon dropped
		    case ITEM_TYPE_WEAPON: {
		        if (DropItensInfo[dropid][drop_quantia]) {
			        // get slot of weapon
					new currentWeapon = GetPlayerWeapon(playerid);

					if (fireWeapons(currentWeapon) && currentWeapon == DropItensInfo[dropid][drop_model]) {
					    new ammo = GetPlayerAmmo(playerid);
					    SetPlayerAmmo(playerid, currentWeapon, ammo + DropItensInfo[dropid][drop_quantia]);
						format(string, sizeof (string), "+%d municao de %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
						SendServerMessageToPlayer(playerid, string);
						DropItensInfo[dropid][drop_quantia] = 0;
						Audio_Play(playerid, 30);
						cameraSearchItens[playerid][search_item_id] = -1;
						cameraSearchItens[playerid][search_id] = 0;
						ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
					    return 1;
					}

					new typew = GetWeaponType(DropItensInfo[dropid][drop_model]);

					static weaponid, ammo;
					GetPlayerWeaponByType(playerid, typew, weaponid, ammo);

					if (weaponid) {
					    GivePlayerWeaponByType(playerid, typew);
					}

					GivePlayerWeapon(playerid, DropItensInfo[dropid][drop_model], DropItensInfo[dropid][drop_quantia], .health = DropItensInfo[dropid][drop_health]);

					if (currentWeapon != 0)
						SetPlayerArmedWeapon(playerid, currentWeapon);

					Audio_Play(playerid, 34);
					// set last pick up and anim
					ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
					// destruir item
					destroyDropItem(dropid);

					// Mensagem
					format(string, sizeof (string), "%dx %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
					SendServerMessageToPlayer(playerid, string);

					cameraSearchItens[playerid][search_item_id] = -1;
					return 1;
				}
		    }
			case ITEM_TYPE_BACKPACK1 .. ITEM_TYPE_BACKPACK4: {

				if (PlayerData[playerid][dMochila] < GetBackPack(DropItensInfo[dropid][drop_type])) {

					// Dropar mochila atual
					if (PlayerData[playerid][dMochila] > MOCHILA_TAMANHO_NENHUM)
						dropItem(playerid, ITEM_TYPE_BACKPACK1 + (PlayerData[playerid][dMochila] - 1), GetBackPackModel(playerid), 1, GetBagName(playerid), false, false);

					// Dar mochila
					givePlayerMochila(playerid, DropItensInfo[dropid][drop_type]);

                    UpdatePlayerItemsName(playerid);

					// Audio
					Audio_Play(playerid, 34);
					// set last pick up and anim
					ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
					// destruir item
					destroyDropItem(dropid);

					// Mensagem
					format(string, sizeof (string), "%dx %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
					SendServerMessageToPlayer(playerid, string);

					cameraSearchItens[playerid][search_item_id] = -1;
		            
		            return 1;
				}
			}
			case ITEM_TYPE_GASMASK: {
				if (!PlayerData[playerid][dGasMask]) {
					PlayerData[playerid][dGasMask] = true;
					SHOP_SetPlayerAttachedObject(playerid, 9, -1020);
		            
					// Audio
					Audio_Play(playerid, 34);
					// set last pick up and anim
					ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
					// destruir item
					destroyDropItem(dropid);

					// Mensagem
					format(string, sizeof (string), "%dx %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
					SendServerMessageToPlayer(playerid, string);

					cameraSearchItens[playerid][search_item_id] = -1;
		            
		            return 1;
				}
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
					// set last pick up and anim
					ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);
					// destruir item
					destroyDropItem(dropid);

					// Mensagem
					format(string, sizeof (string), "%dx %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
					SendServerMessageToPlayer(playerid, string);

					cameraSearchItens[playerid][search_item_id] = -1;
			    
			        return 1;
			    }
			}
		}

		if (!isInventoryFreeSpace(playerid, DropItensInfo[dropid][drop_slots]))
		{
		    SendLanguageMessagef(playerid, corError, "MSG_073", DropItensInfo[dropid][drop_slots]);
		    return 0;
		}

		// Dar o item
		givePlayerItem(playerid, DropItensInfo[dropid][drop_type], DropItensInfo[dropid][drop_model], DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome], .health = DropItensInfo[dropid][drop_health]);

		// Mensagem
		format(string, sizeof (string), "%dx %s", DropItensInfo[dropid][drop_quantia], DropItensInfo[dropid][drop_nome]);
		SendServerMessageToPlayer(playerid, string);

        ApplyAnimation(playerid,"BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,400);SetPVarInt(playerid, "p_LastPickup", GetTickCount() + 900);

		// destruir item
		destroyDropItem(dropid);
		
		// Audio
		Audio_Play(playerid, 34);
		
		// Reset item
		cameraSearchItens[playerid][search_item_id] = -1;
	}
	return 1;
}



