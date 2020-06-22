
callback OnPlayerUseItem(playerid, itemid, itemname[], itemtype, modelid, quantia) {

//	new string[45];

	switch(itemtype) {

	    case ITEM_TYPE_WEAPON: {

			new typew = GetWeaponType(modelid);

			new weaponid, ammo;
			GetPlayerWeaponByType(playerid, typew, weaponid, ammo);

			if (weaponid) {
			    GivePlayerWeaponByType(playerid, typew);
			}

			GivePlayerWeapon(playerid, modelid, quantia, .health = InventarioInfo[playerid][itemid][item_health]);

			Audio_Play(playerid, 30);

			StartPlayerProgress(playerid, "Equipando...", 60,  5.0);
	    }
	    
	    case ITEM_TYPE_HELMETLVL1 .. ITEM_TYPE_HELMETLVL3:
	    {
	        GuardarHelmet(playerid);
	        
	        SetPlayerHelmet(playerid, InventarioInfo[playerid][itemid][item_type], .health = InventarioInfo[playerid][itemid][item_health]);
	        
	        UpdatePlayerItemsName(playerid);
	    }
	    
	    case ITEM_TYPE_ARMORLVL1 .. ITEM_TYPE_ARMORLVL3:
	    {
	        GuardarArmor(playerid);

	        SetPlayerArmor(playerid, InventarioInfo[playerid][itemid][item_type], .health = InventarioInfo[playerid][itemid][item_health]);
	        
	        UpdatePlayerItemsName(playerid);
	    }
	    
	    case ITEM_TYPE_RELOGIO: {
	        new hour, minu, sec;
	        gettime(hour, minu, sec);
	        SendClientMessagef(playerid, corCinza, "Horario atual: %02d:%02d:%02d", hour, minu, sec);
	        return 0;
	    }

		case ITEM_TYPE_DINHEIRO: {

            GivePlayerMoney(playerid, quantia);

            StartPlayerProgress(playerid, "Guardando grana...", 60,  10.0);
		}
		case ITEM_TYPE_REMEDIO: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			StartPlayerProgress(playerid, "Usando medkit...", 80, IsPlayerPremium(playerid) ? 5.0 : 3.0);
		}
		case ITEM_TYPE_ADRENALINA: {
		
			SetPVarInt(playerid, "p_ItemId", itemid);
		
		    StartPlayerProgress(playerid, "Aplicando adrenalina", 95, 1.0, .progressid = PROGRESS_ADRENALINA);
		    
		    ApplyAnimation(playerid,"BAR","dnk_stndM_loop",4.1, 0, 1, 1, 0, 0);
		    
		    return 0;
		}
		case ITEM_TYPE_REMEDIOP: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

            StartPlayerProgress(playerid, "Usando medkit...", 60,  IsPlayerPremium(playerid) ? 5.0 : 4.0);
		}
		case ITEM_TYPE_MOSTARDA, ITEM_TYPE_KETCHUP: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
		}
		case ITEM_TYPE_SODA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dSede] =
				((PlayerData[playerid][dSede] + getItemModelSede(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dSede] + getItemModelSede(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

			Audio_Play(playerid, 32);

			StartPlayerProgress(playerid, "Bebendo...", 60,  5.0);
			
			ApplyAnimation(playerid,"BAR","dnk_stndM_loop",4.1, 0, 1, 1, 0, 0);
			
			// Empty soda
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			
			CreateDynamicObject(-1066, x + frandom(0.5) - frandom(0.5), y + frandom(0.5) - frandom(0.5), z - 0.85, 0.0, 0.0, random(360), .worldid = GetPlayerVirtualWorld(playerid));
		}
		case ITEM_TYPE_COCA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dSede] =
				((PlayerData[playerid][dSede] + getItemModelSede(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dSede] + getItemModelSede(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

			Audio_Play(playerid, 32);

			StartPlayerProgress(playerid, "Bebendo...", 60,  5.0);
			
			ApplyAnimation(playerid,"BAR","dnk_stndM_loop", 4.1, 0, 1, 1, 0, 0);
		}
		case ITEM_TYPE_COCAR: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dRadiacao] += (0.051 + frandom(0.152));

			if (PlayerData[playerid][dRadiacao] > 1.0)
   				PlayerData[playerid][dRadiacao] = 1.0;

			PlayerData[playerid][dSede] =
				((PlayerData[playerid][dSede] + getItemModelSede(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dSede] + getItemModelSede(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;
            
            ApplyAnimation(playerid,"BAR","dnk_stndM_loop", 4.1, 0, 1, 1, 0, 0);

			Audio_Play(playerid, 32);

			StartPlayerProgress(playerid, "Bebendo...", 60,  5.0);
		}
		case ITEM_TYPE_BEBIDA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dSede] =
				((PlayerData[playerid][dSede] + getItemModelSede(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dSede] + getItemModelSede(modelid)));

			SetPlayerDrunkLevel(playerid, GetPlayerDrunkLevel(playerid) + 2000);

            PlayerData[playerid][dLastUpdateFome] = 0;

			Audio_Play(playerid, 32);

			StartPlayerProgress(playerid, "Bebendo...", 60,  5.0);
			
			ApplyAnimation(playerid,"BAR","dnk_stndM_loop",4.1, 0, 1, 1, 0, 0);
		}
		case ITEM_TYPE_PIZZA: {

			if (!IsPlayerHaveItem(playerid, ITEM_TYPE_FACACOZINHA))
			{
			    SendClientMessage(playerid, corError, "ERROR: {888888}Você precisa do item 'Faca de cozinha' para conseguir abrir este enlatado.");
			    return 0;
			}

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

//			Audio_Play(playerid, 31);

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1, 0, 1, 1, 0, 0);
			
			PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
			
			// Empty
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);

			CreateDynamicObject(-1066, x + frandom(0.5) - frandom(0.5), y + frandom(0.5) - frandom(0.5), z - 0.89, 0.0, 0.0, random(360), .worldid = GetPlayerVirtualWorld(playerid));
		}
		case ITEM_TYPE_CARNEASSADA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

//			Audio_Play(playerid, 31);

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);
			
			ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1, 0, 1, 1, 0, 0);
		}
		case ITEM_TYPE_PEIXEASSADO: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

//			Audio_Play(playerid, 31);

			PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1, 0, 1, 1, 0, 0);
		}
		case ITEM_TYPE_HAMBURGER: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

//			Audio_Play(playerid, 31);

			PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1, 0, 1, 1, 0, 0);
		}
		case ITEM_TYPE_FATIAPIZZA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

//			Audio_Play(playerid, 31);

            PlayerPlaySound(playerid, 32200, 0.0, 0.0, 0.0);

			StartPlayerProgress(playerid, "Comendo...", 60,  2.0);
			
			ApplyAnimation(playerid,"FOOD","EAT_Burger",4.1, 0, 1, 1, 0, 0);
		}

		case ITEM_TYPE_BANDAGE: {

/*
            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			if (PlayerData[playerid][dDoenca] != 0) {
            	PlayerData[playerid][dDoenca] = 0;
			}
			
			PlayerData[playerid][dSangramento] -= (0.5 + frandom(0.5));
			
			if (PlayerData[playerid][dSangramento] < 0.0)
			    PlayerData[playerid][dSangramento] = 0.0;
*/
			SetPVarInt(playerid, "p_AudioId", Audio_Play(playerid, 33));
			
			SetPVarInt(playerid, "p_ItemId", itemid);

			StartPlayerProgress(playerid, "Usando bandagem...", 80,  IsPlayerPremium(playerid) ? 2.0 : 1.0, .progressid = PROGRESS_BANDAGE);
			
			return 0;
		}
		
		case ITEM_TYPE_BANDAGEMI: {

/*
            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			if (PlayerData[playerid][dDoenca] != 0) {
            	PlayerData[playerid][dDoenca] = 0;
			}

			PlayerData[playerid][dSangramento] -= (0.1 + frandom(0.2));

			if (PlayerData[playerid][dSangramento] < 0.0)
			    PlayerData[playerid][dSangramento] = 0.0;
*/

			SetPVarInt(playerid, "p_AudioId", Audio_Play(playerid, 33));

			SetPVarInt(playerid, "p_ItemId", itemid);

			StartPlayerProgress(playerid, "Usando bandagem...", 60,  IsPlayerPremium(playerid) ? 2.0 : 1.0, .progressid = PROGRESS_BANDAGEI);
			
			return 0;
		}
		
		case ITEM_TYPE_PAINKILLER: {

			if (PlayerData[playerid][dVirus] == 0.0 && PlayerData[playerid][dRadiacao] == 0.0) {
			    SendLanguageMessage(playerid, corError, "MSG_114");
			    return 0;
			}

            PlayerData[playerid][dVirus] -= (0.8 + frandom(0.8));

			if (PlayerData[playerid][dVirus] < 0.0)
			    PlayerData[playerid][dVirus] = 0.0;

            PlayerData[playerid][dRadiacao] -= (0.8 + frandom(0.8));

			if (PlayerData[playerid][dRadiacao] < 0.0)
			    PlayerData[playerid][dRadiacao] = 0.0;

			Audio_Play(playerid, 45);

			StartPlayerProgress(playerid, "Usando painkiller...", 60,  4.0);
			
			ApplyAnimation(playerid,"BAR","dnk_stndM_loop", 4.1, 0, 1, 1, 0, 0);
		}

		// Tenda
		case ITEM_TYPE_BARRACA: {

			if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || PlayerData[playerid][dDead] || GetPlayerInterior(playerid)) {
			    return SendClientMessage(playerid, corError, "ERRO: {999999}Você não construir uma tenda agora!"), 0;
			}
			
			new baseindex = getPlayerBase(playerid);

			if (baseindex != -1)
			{
			    if (!IsNicknameAuthorized(baseindex, getNome(playerid)))
			    {
			        SendClientMessage(playerid, corError, "ERROR: {888888}Você não pode colocar uma tenda em uma base que não é sua.");
			        
			        return 0;
			    }
			}

			SetPVarInt(playerid, "p_ItemId", itemid);

			StartPlayerProgress(playerid, "Construindo tenda...", 100,  IsPlayerPremium(playerid) ? 2.0 : 1.0, .progressid = PROGRESS_BARRACA);
			
			return 0;
		}

		case ITEM_TYPE_PEDECABRA:
		{
			if (PlayerData[playerid][dPlayerBlocked])
			{
			    ShowPlayerBaseProtectDialog(playerid);
			    return 0;
			}
		
		    new index = GetPlayerTenda(playerid);
		    
		    if (index != -1) {
				SetPVarInt(playerid, "p_ItemId", itemid);

				StartPlayerProgress(playerid, "Desmontando tenda...", 100,  IsPlayerPremium(playerid) ? 2.0 : 1.0, .progressid = PROGRESS_DBARRACA);
		    } else {
		        SendClientMessage(playerid, corError, "ERRO: {999999}Você não está próximo de uma tenda!");
		    }
		    
		    return 0;
		}

		// Munições

		case ITEM_TYPE_AMMO_MP5: {

			if (!IsPlayerHaveWeapon(playerid, 29)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

			giveWeaponAmmo(playerid, 29, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}

			StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_M4: {

			if (!IsPlayerHaveWeapon(playerid, 31)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

            giveWeaponAmmo(playerid, 31, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


            StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_DEAGLE: {

			if (!IsPlayerHaveWeapon(playerid, 24)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

            giveWeaponAmmo(playerid, 24, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


            StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_SHOTGUN: {

			if (!IsPlayerHaveWeapon(playerid, 25)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 25, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_AK47: {

			if (!IsPlayerHaveWeapon(playerid, 30)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 30, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_SILENCER: {

			if (!IsPlayerHaveWeapon(playerid, 23)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 23, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_SNIPER: {

			if (!IsPlayerHaveWeapon(playerid, 34)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 34, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_RIFLE: {

			if (!IsPlayerHaveWeapon(playerid, 33)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 33, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_TEC9: {

			if (!IsPlayerHaveWeapon(playerid, 32)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

		    giveWeaponAmmo(playerid, 32, quantia);

			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		case ITEM_TYPE_AMMO_9MM: {

			if (!IsPlayerHaveWeapon(playerid, 22) && !IsPlayerHaveWeapon(playerid, 23) && !IsPlayerHaveWeapon(playerid, 28) && !IsPlayerHaveWeapon(playerid, 32)) {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}

			if (IsPlayerHaveWeapon(playerid, 22)) {
			    giveWeaponAmmo(playerid, 22, quantia);
			}
			else if (IsPlayerHaveWeapon(playerid, 23)) {
			    giveWeaponAmmo(playerid, 23, quantia);
			}
			else if (IsPlayerHaveWeapon(playerid, 28)) {
			    giveWeaponAmmo(playerid, 28, quantia);
			}
			else if (IsPlayerHaveWeapon(playerid, 32)) {
			    giveWeaponAmmo(playerid, 32, quantia);
			} else {
			    return SendLanguageMessage(playerid, corError, "MSG_115"), 0;
			}


			if (Audio_IsClientConnected(playerid))
			{
				Audio_Play(playerid, 29);
			}
			else
			{
				PlayerPlaySound(playerid, 36401, 0.0, 0.0, 0.0);
			}


		    StartPlayerProgress(playerid, "Adicionando municao...", 60,  4.0);
		}
		/*
		case ITEM_TYPE_SKIN: {

			if (IsPlayerInAnyVehicle(playerid)) {
			    return SendLanguageMessage(playerid, corError, "MSG_116"), 0;
			}

			new skinid = GetPlayerSkin(playerid);

			SetPlayerSkin(playerid, modelid);

			PlayerData[playerid][dSkin] = modelid;

			if (PlayerData[playerid][dColete] > 0.0)
			{
				SetPlayerAttachedObject(playerid, 4, 19142, 1, ColeteOffSets[modelid][0], ColeteOffSets[modelid][1], ColeteOffSets[modelid][2],
				ColeteOffSets[modelid][3], ColeteOffSets[modelid][4], ColeteOffSets[modelid][5], ColeteOffSets[modelid][6], ColeteOffSets[modelid][7], ColeteOffSets[modelid][8]);
			}

			format(string, sizeof string, "%s", GetSkinName(skinid));

			if (!PlayerData[playerid][dBlockSkin])
			{
				if (isInventoryFreeSpace(playerid, getItemModelSlots(skinid))) {
					givePlayerItem(playerid, ITEM_TYPE_SKIN, skinid, 1, string);
				} else {
					dropItem(playerid, ITEM_TYPE_SKIN, skinid, 1, string, false);
				}
			}
			
			PlayerData[playerid][dBlockSkin] = false;

			StartPlayerProgress(playerid, "Trocando de roupa...", 60,  5.0);
		}*/

		case ITEM_TYPE_TRAP: {

			if (IsPlayerInAnyVehicle(playerid)) {
			    return SendClientMessage(playerid, corError, "ERRO: {999999}Você precisa estar fora do veículo para colocar uma armadilha!"), 0;
			}

			switch (createPlayerTrap(playerid)) {

			    case 0: SendClientMessage(playerid, corError, "ERRO: {999999}O limite de armadilhas no servidor foi esgotado!");

				default: {

				    SendClientMessage(playerid, corServer, "• Você colocou uma armadilha neste local, você tem 10 segundos para se afastar antes que ative!");
				}
			}

			StartPlayerProgress(playerid, "Plantando uma armadilha...", 60,  10.0);
		}

		case ITEM_TYPE_MAP: {

            SendLanguageMessage(playerid, corError, "MSG_117");
			return 0;
		}
		case ITEM_TYPE_BUSSOLA: {

            SendLanguageMessage(playerid, corError, "MSG_118");
			return 0;
		}
		case ITEM_TYPE_MOTOR: {

			SendClientMessage(playerid, corError, "ERRO: {999999}Para usar este item você deve usar o botão de 'descartar' próximo de algum veículo!");
		    return 0;
		}
		case ITEM_TYPE_GASOLINA: {

			// Encher galão
			new refuel = getPlayerFuel(playerid);
			
			if (refuel != -1) {
			
			    if (quantia >= 25) {
				    SendLanguageMessage(playerid, corError, "MSG_119");
				    return 0;
			    }
			    
			    new litros = getFuelLitros(refuel);
			    
			    if (litros < 1) {
				    SendLanguageMessage(playerid, corError, "MSG_120");
				    return 0;
			    }
			
			    StartPlayerProgress(playerid, "Enchendo galao...", 1000, 1.0, float(quantia), 25.0, PROGRESS_REFUEL);
			
			    SetPVarInt(playerid, "varRefuel", itemid);
			
			    return 0;
			}
			
			new vehicleid = GetPlayerClossestVehicle(playerid);

			if (vehicleid == INVALID_VEHICLE_ID) {
			    SendLanguageMessage(playerid, corError, "MSG_121");
			    return 0;
			}
			
			if (quantia < 1) {
			    SendLanguageMessage(playerid, corError, "MSG_122");
			    return 0;
			}
			
			if (!IsPlayerInPetrolCap(playerid, vehicleid)) {
			    SendLanguageMessage(playerid, corError, "MSG_123");
			    return 0;
			}
			
			new vehfuel = GetVehicleFuel(vehicleid);
			
			if (vehfuel >= MAX_VEHICLE_FUEL) {
			    SendLanguageMessage(playerid, corError, "MSG_124");
			    return 0;
			}

		  	StartPlayerProgress(playerid, "Enchendo tanque...", 250, 1.0, float(vehfuel), float(MAX_VEHICLE_FUEL), PROGRESS_REFUEL_VEH);

			SetPVarInt(playerid, "varRefuel", itemid);

		//	AddGasVehicle(vehicleid, quantia);
			
			SetPVarInt(playerid, "audioRefuel", Audio_Play(playerid, 43, false, true));

			/*StartPlayerProgress(playerid, "Adicionando gasolina...", 60,  1.2);
			
			static Float:x, Float:y, Float:z;
			
			GetPlayerPos(playerid, x, y, z);
			
			createDroppedItem(x, y, z, "Galao de gasolina", ITEM_TYPE_GASOLINA, 1650, 0, true);*/

		    return 0;
		}
		
		case ITEM_TYPE_PNEU:
		{
			new vehicleid = GetPlayerClossestVehicle(playerid);

			if (vehicleid == INVALID_VEHICLE_ID)
			{
			    SendLanguageMessage(playerid, corError, "MSG_161");
			    return 0;
			}
			
			new weelclossest = GetPlayerVehicleWeel(playerid, vehicleid);

			if (weelclossest == -1)
			{
			    SendLanguageMessage(playerid, corError, "MSG_125");
			    return 0;
			}
			
			if (GetCarTireState(vehicleid, weelclossest) != 1)
			{
			    SendLanguageMessage(playerid, corError, "MSG_126");
			    return 0;
			}

		  	StartPlayerProgress(playerid, "Trocando pneu...", 80,  5.0);

            SetCarTireState(vehicleid, weelclossest, 0);
            
            SaveVehicleInfo(vehicleid);
            
            PlayerPlaySound(playerid, 32000, 0.0, 0.0, 0.0);

		    return 1;
		}
		
		case ITEM_TYPE_TRANCAV: {

			new vehicleid = GetPlayerClossestVehicle(playerid);

			if (vehicleid == INVALID_VEHICLE_ID) {
			    SendLanguageMessage(playerid, corError, "MSG_161");
			    return 0;
			}

			if (VehicleInfo[vehicleid][vehKeyId] != 0)
			{
			    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
			    
			    SendClientMessage(playerid, corInfo, "Este veículo já possui uma chave, tentando fazer uma copia...");
			    
			  	StartPlayerProgress(playerid, "Recriando chave...", 250, 1.0, .progressid = PROGRESS_KEY_COPY);

				SetPVarInt(playerid, "p_ItemId", itemid);
			    return 0;
			}

		  	StartPlayerProgress(playerid, "Criando chave...", 250, 3.0, .progressid = PROGRESS_KEY_VEH);

			SetPVarInt(playerid, "p_ItemId", itemid);

            //VehicleInfo[vehicleid][vehKeyId] = serverCreateVehicleKey();

			//new string[75];
			//format(string, sizeof string, "Chave do %s #%d", getVehicleName(vehicleid), VehicleInfo[vehicleid][vehKeyId]);

			//setItemToSlot(playerid, itemid, ITEM_TYPE_CHAVEV, 11746, 1, string);

            //SaveVehicleInfo(vehicleid);

		    return 0;
		}
		
		case ITEM_TYPE_CHAVEV:
		{
			new vehicleid = GetPlayerClossestVehicle(playerid);

			if (vehicleid == INVALID_VEHICLE_ID) {
			    SendLanguageMessage(playerid, corError, "MSG_161");
			    return 0;
			}

			new string_key[75];
			format(string_key, sizeof string_key, "Chave do %s #%d", getVehicleName(vehicleid), VehicleInfo[vehicleid][vehKeyId]);

			if (!strcmp(string_key, itemname))
			{
			    if (VehicleInfo[vehicleid][vehLocked])
			    {
			        UnlockVehicle(vehicleid);
			        SendServerMessageToPlayer(playerid, "O veiculo foi destrancado");
			    } else
			    {
			        LockVehicle(vehicleid);
			        SendServerMessageToPlayer(playerid, "O veiculo foi trancado");
			    }
			    PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			} else {
			    SendClientMessage(playerid, corError, "ERROR: {888888}Esta chave não pertence a este veículo.");
			    PlayerPlaySound(playerid, 24600, 0.0, 0.0, 0.0);
			    return 0;
			}

		    return 0;
		}

		
		case ITEM_TYPE_TOOLBOX: {

			new vehicleid = GetPlayerClossestVehicle(playerid);
			new Float:vehhHealth;

			if (vehicleid == INVALID_VEHICLE_ID) {
			    SendLanguageMessage(playerid, corError, "MSG_121");
			    return 0;
			}

			if (!IsPlayerAtVehicleBonnet(playerid, vehicleid)) {
			    SendLanguageMessage(playerid, corError, "MSG_127");
			    return 0;
			}
			
			GetVehicleHealth(vehicleid, vehhHealth);
			
			if (vehhHealth >= 950.0) {
			    SendLanguageMessage(playerid, corError, "MSG_128");
			    return 0;
			}

            VehicleBonnetState(vehicleid, 1);

			SetPVarInt(playerid, "fixVeh", vehicleid);
			SetPVarInt(playerid, "itemFix", itemid);

            StartPlayerProgress(playerid, "Reparando o veiculo...", 250, IsPlayerPremium(playerid) ? 4.0 : 2.0, vehhHealth, 950.0, PROGRESS_FIXVEH);
            
            SetPVarInt(playerid, "audioFix", Audio_Play(playerid, 46, false, true));

		    return 0;
		}
		
		case ITEM_TYPE_BATERIA: {

			new vehicleid = GetPlayerClossestVehicle(playerid);

			if (vehicleid == INVALID_VEHICLE_ID) {
			    SendLanguageMessage(playerid, corError, "MSG_121");
			    return 0;
			}

			if (!IsPlayerAtVehicleBonnet(playerid, vehicleid)) {
			    SendLanguageMessage(playerid, corError, "MSG_127");
			    return 0;
			}

			if (VehicleInfo[vehicleid][vehBatery] >= 35.0) {
			    SendLanguageMessage(playerid, corError, "MSG_129");
			    return 0;
			}
			
			VehicleInfo[vehicleid][vehBatery] = 100.0;
			
			SaveVehicleInfo(vehicleid);

            StartPlayerProgress(playerid, "Trocando bateria...", 250, 5.0);
		}
		
		case ITEM_TYPE_SINALFUMACA: {

			if (IsPlayerInAnyVehicle(playerid)) {
			    return 0;
			}

			static
			    Float:x,
			    Float:y,
			    Float:z,
			    Float:a,
				object;
			    
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, a);
			
			GetXYInFrontOfPoint(x, y, a, 1.0);
			
			CA_RayCastLine(x, y, z, x, y, z - 100.0, x, y, z);

            SetTimerEx("CallAirDrop", 1 * 60000, false, "ffdd", x, y, GetPlayerVirtualWorld(playerid), LOOT_TYPE_MILITAR);
            
            object = CreateDynamicObject(18728, x, y, z - 2.8, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid));
            
            SetTimerEx("destroyAirDropDynamicObj", 4 * 60000, false, "d", object);

			StartPlayerProgress(playerid, "Chamando airdrop...", 80,  15.0);

		    return 1;
		}
		
		case ITEM_TYPE_MACA, ITEM_TYPE_MACAVERDE, ITEM_TYPE_TOMATE, ITEM_TYPE_BANANA, ITEM_TYPE_LARANJA: {

            PlayerData[playerid][dVidaRestore] += getItemModelVida(modelid);

            if (PlayerData[playerid][dVidaRestore] > 100.0) {
                PlayerData[playerid][dVidaRestore] = 100.0;
            }

			PlayerData[playerid][dFome] =
				((PlayerData[playerid][dFome] + getItemModelFome(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dFome] + getItemModelFome(modelid)));

			PlayerData[playerid][dSede] =
				((PlayerData[playerid][dSede] + getItemModelSede(modelid)) >= 100.0 ? (100.0) : (PlayerData[playerid][dSede] + getItemModelSede(modelid)));

            PlayerData[playerid][dLastUpdateFome] = 0;

			Audio_Play(playerid, 31);

			StartPlayerProgress(playerid, "Comendo fruta...", 60,  2.0);
		}
		
		case ITEM_TYPE_BACKPACK1 .. ITEM_TYPE_BACKPACK4: {

			if (PlayerData[playerid][dMochila] >= GetBackPack(itemtype)) {
			    SendLanguageMessage(playerid, corError, "MSG_130");
			    return 0;
			}

			// Dropar mochila atual
			if (PlayerData[playerid][dMochila] > MOCHILA_TAMANHO_NENHUM)
				dropItem(playerid, ITEM_TYPE_BACKPACK1 + (PlayerData[playerid][dMochila] - 1), GetBackPackModel(playerid), 1, GetBagName(playerid), false, false);

			// Dar mochila
			givePlayerMochila(playerid, itemtype);

           	// procurar itens
//			searchItens(playerid);

			// Audio
			Audio_Play(playerid, 34);

            StartPlayerProgress(playerid, "Colocando mochila...", 60,  20.0);
            
            UpdatePlayerItemsName(playerid);
		}
		
		case ITEM_TYPE_GASMASK: {

			if (PlayerData[playerid][dGasMask]) {
			    return SendLanguageMessage(playerid, corError, "MSG_131"), 0;
			}

			PlayerData[playerid][dGasMask] = true;
			SHOP_SetPlayerAttachedObject(playerid, 9, -1020);
            StartPlayerProgress(playerid, "Colocando a mascara...", 60,  10.0);
            
            UpdatePlayerItemsName(playerid);
		}
		
		case ITEM_TYPE_FOGUEIRA: {

			if (IsPlayerInAnyVehicle(playerid)) {
			    return 0;
			}

			new
			    Float:x,
			    Float:y,
			    Float:z,
			    Float:ang;
			    
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, ang);

            GetXYInFrontOfPoint(x, y, ang, 0.6);

			new index = CreateServerFogueira(x, y, z, .timedestroy = 10);
			
			if (index == -1)
			{
			    SendClientMessage(playerid, corError, "ERRO: {999999}Muitas fogueiras já foram criadas no servidor!");
			    return 0;
			}
			
            StartPlayerProgress(playerid, "Acendendo fogueira...", 60,  5.0);
		}
		case ITEM_TYPE_VARA: {
			if (!CA_IsPlayerFacingWater(playerid)) {
			    SendLanguageMessage(playerid, corError, "MSG_132");
			    return 0;
			}
			SetPVarInt(playerid, "itemFish", itemid);
			fishingInPlace(playerid);
			
			return 0;
		}
		case ITEM_TYPE_LANTERNA: {
			if (PlayerData[playerid][dLanterna]) {
			    SendLanguageMessage(playerid, corError, "MSG_133");
			    return 0;
			}
			PlayerData[playerid][dLanterna] = true;
			SetPlayerAttachedObject(playerid, 7, 18641,1,0.269000 + 0.02,0.029999 + 0.06,-0.102999,87.100013,0.000000,0.000000,0.888999,0.751000,0.787999);
			SetPlayerAttachedObject(playerid, 8, 3872,1,0.025999,1.334000,-0.094999,-98.300056,86.800018,8.999998,0.184999,0.015999,0.045999);
			StartPlayerProgress(playerid, "Colocando lanterna...", 60,  10.0);
			
			UpdatePlayerItemsName(playerid);
		}
		case ITEM_TYPE_CIGARRO: {
			if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_SMOKE_CIGGY) {
			    SendLanguageMessage(playerid, corError, "MSG_134");
			    return 0;
			}
		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
		    SendLanguageMessage(playerid, corCinza, "MSG_135");
		}
		case ITEM_TYPE_VINHO: {
			if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DRINK_WINE) {
			    SendLanguageMessage(playerid, corError, "MSG_136");
			    return 0;
			}
		    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
		    SendLanguageMessage(playerid, corCinza, "MSG_137");
		}
		case ITEM_TYPE_GARRAFAV: {
			if (!CA_IsPlayerFacingWater(playerid) && !IsPlayerInPoco(playerid)) {
			    SendLanguageMessage(playerid, corError, "MSG_138");
			    return 0;
			}
			if (IsPlayerInToxicArea(playerid)) {
			    setItemToSlot(playerid, itemid, ITEM_TYPE_COCAR, modelid, 1, "Garrafa dagua");
			} else {
		    	setItemToSlot(playerid, itemid, ITEM_TYPE_COCA, modelid, 1, "Garrafa dagua");
			}
		    StartPlayerProgress(playerid, "Enchendo garrafa...", 60,  10.0);
		    return 0;
		}
		case ITEM_TYPE_SEMENTE1: {
		    // get position
		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);
		    GetXYInFrontOfPoint(x, y, a, 1.5);
		    // plantar semente
		    CreateArvore(0, x, y, z);
		    StartPlayerProgress(playerid, "Plantando arvore...", 60,  10.0);
		}
		case ITEM_TYPE_SEMENTE2: {
		    // get position
		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);
		    GetXYInFrontOfPoint(x, y, a, 1.5);
		    // plantar semente
		    CreateArvore(1, x, y, z);
		    StartPlayerProgress(playerid, "Plantando arvore...", 60,  10.0);
		}
		case ITEM_TYPE_SEMENTE3: {
		    // get position
		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);
		    GetXYInFrontOfPoint(x, y, a, 1.5);
		    // plantar semente
		    CreateArvore(2, x, y, z);
		    StartPlayerProgress(playerid, "Plantando arvore...", 60,  10.0);
		}
		case ITEM_TYPE_SEMENTE4: {
		    // get position
		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);
		    GetXYInFrontOfPoint(x, y, a, 1.5);
		    // plantar semente
		    CreateArvore(3, x, y, z);
		    StartPlayerProgress(playerid, "Plantando arvore...", 60,  10.0);
		}
		case ITEM_TYPE_SEMENTE5: {
		    // get position
		    new Float:x, Float:y, Float:z, Float:a;
		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, a);
		    GetXYInFrontOfPoint(x, y, a, 1.5);
		    // plantar semente
		    CreateArvore(4, x, y, z);
		    StartPlayerProgress(playerid, "Plantando arvore...", 60,  10.0);
		}
		case ITEM_TYPE_ALGEMA: {
		
		    new index = GetClosestPlayer(playerid, 1.5);
		    
		    if (index != INVALID_PLAYER_ID) {
		    
		        if (!IsPlayerBehindPlayer(playerid, index))
		            return SendLanguageMessage(playerid, corError, "MSG_139"), 0;
		    
		        if (PlayerData[index][dCuffed])
		            return SendLanguageMessage(playerid, corError, "MSG_140"), 0;
		    
		        SetPVarInt(playerid, "p_cuff", index);
		        
		        SetPVarInt(playerid, "p_ItemId", itemid);
		        
		        StartPlayerProgress(playerid, "Algemando...", 100,  2.0, .progressid = PROGRESS_CUFF);
		        
		        return 0;
		    } else {
		        SendLanguageMessage(playerid, corError, "MSG_141");
		    }
		    return 0;
		}
		case ITEM_TYPE_KEY: {

		    new index = GetClosestPlayer(playerid, 1.5);

		    if (index != INVALID_PLAYER_ID) {

		        if (!IsPlayerBehindPlayer(playerid, index))
		            return SendLanguageMessage(playerid, corError, "MSG_142"), 0;

		        if (!PlayerData[index][dCuffed])
		            return SendLanguageMessage(playerid, corError, "MSG_143"), 0;

		        SetPVarInt(playerid, "p_cuff", index);

		        StartPlayerProgress(playerid, "Desalgemando...", 80,  5.0, .progressid = PROGRESS_UNCUFF);

		        return 0;
		    } else {
		        SendLanguageMessage(playerid, corError, "MSG_141");
		    }
		    
		    return 0;
		}
		case ITEM_TYPE_EXPLOSIVO: {
			if (IsPlayerInAnyVehicle(playerid)) {
			    return 0;
			}
			if (PlayerData[playerid][dPlayerBlocked])
			{
			    ShowPlayerBaseProtectDialog(playerid);
			    return 0;
			}

            SetPVarInt(playerid, "p_ItemId", itemid);
            SetPVarInt(playerid, "p_ItemType", itemtype);
            
            ShowPlayerDialog(playerid, DIALOG_EXPLOSIVE_COUNT, DIALOG_STYLE_INPUT, " ", GetPlayerLanguageKey(playerid, "MSG_144"), "Definir", "Cancelar");
            
            return 0;
		}
		case ITEM_TYPE_EXPLOSIVOC4: {
			if (IsPlayerInAnyVehicle(playerid)) {
			    return 0;
			}

			if (PlayerData[playerid][dPlayerBlocked])
			{
			    ShowPlayerBaseProtectDialog(playerid);
			    return 0;
			}

            SetPVarInt(playerid, "p_ItemId", itemid);
            SetPVarInt(playerid, "p_ItemType", itemtype);

            ShowPlayerDialog(playerid, DIALOG_EXPLOSIVE_COUNT, DIALOG_STYLE_INPUT, " ", GetPlayerLanguageKey(playerid, "MSG_144"), "Definir", "Cancelar");

            return 0;
		}
		case ITEM_TYPE_EXPLOSIVORE: {
			if (IsPlayerInAnyVehicle(playerid)) {
			    return 0;
			}
			
			if (PlayerData[playerid][dPlayerBlocked])
			{
			    ShowPlayerBaseProtectDialog(playerid);
			    return 0;
			}

            SetPVarInt(playerid, "p_ItemId", itemid);
            SetPVarInt(playerid, "p_ItemType", itemtype);
            SetPVarInt(playerid, "p_ExplosiveCount", -1);

            StartPlayerProgress(playerid, "Armando explosivo...", 120, 1.0, .progressid = PROGRESS_EXPLOSIVE);
            return 0;
		}
		case ITEM_TYPE_CONTROLE: {
		
		    if (!detoneRemoteExplosive(playerid))
		    	SendLanguageMessage(playerid, corError, "MSG_145");
			else
		        ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", GetPlayerLanguageKey(playerid, "MSG_146"), "Ok", "");
		
		    return 0;
		}
		default: {
		    SendLanguageMessage(playerid, corError, "MSG_147");
		    return 0;
		}
	}

	return 1;
}
















