
forward OnPlayerChangeWeaponHold(playerid, newweapon, oldweapon);

new PlayerText:textWeaponsHold[4][MAX_PLAYERS];
new PlayerText:textWeaponsHoldAmmo[3][MAX_PLAYERS];

// Atual weapon
new playerWeaponHold[MAX_PLAYERS];

// Timer
new playerTimerHide[MAX_PLAYERS];

// Count weapons
new playerCountWeapons[MAX_PLAYERS];

public OnPlayerUpdate(playerid) {

	if (IsPlayerNPC(playerid))
	    return 1;

	new
	    weaponHold = GetPlayerWeapon(playerid);

	if (weaponHold != playerWeaponHold[playerid]) {

	    #if defined OnPlayerChangeWeaponHold
	        OnPlayerChangeWeaponHold(playerid, weaponHold, playerWeaponHold[playerid]);
		#endif

	    playerWeaponHold[playerid] = weaponHold;
	}

	#if defined holdOnPlayerUpdate
	    return holdOnPlayerUpdate(playerid);
	#else
	    return 1;
 	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate holdOnPlayerUpdate
#if defined holdOnPlayerUpdate
	forward holdOnPlayerUpdate(playerid);
#endif

public OnPlayerChangeWeaponHold(playerid, newweapon, oldweapon) {

    UpdatePlayerWeaponHold(playerid, newweapon);

	return 1;
}

stock UpdatePlayerWeaponHold(playerid, weaponHold) {

	new
		slotweapon,
		slotammo,
		slotstring[15];
		
    playerCountWeapons[playerid] = 0;

	for(new slotid; slotid < 12; slotid++) {

	    if (playerCountWeapons[playerid] > 2)
	        break;

	    GetPlayerWeaponData(playerid, slotid, slotweapon, slotammo);

	    if (slotweapon && slotweapon != 46) {

	        PlayerTextDrawSetPreviewModel(playerid, textWeaponsHold[playerCountWeapons[playerid]][playerid], getWeaponObjectModel(slotweapon));

	        format(slotstring, sizeof (slotstring), "%d", slotammo);
	        PlayerTextDrawSetString(playerid, textWeaponsHoldAmmo[playerCountWeapons[playerid]][playerid], slotstring);

	        if (slotweapon == weaponHold) {
	            PlayerTextDrawColor(playerid,textWeaponsHold[playerCountWeapons[playerid]][playerid], -156);
	        } else {
	            PlayerTextDrawColor(playerid,textWeaponsHold[playerCountWeapons[playerid]][playerid], -226);
	        }

	        playerCountWeapons[playerid] ++;
	    }
	}
	
	switch (playerCountWeapons[playerid]) {
	    case 1: PlayerTextDrawSetString(playerid, textWeaponsHold[3][playerid], "1");
	    case 2: PlayerTextDrawSetString(playerid, textWeaponsHold[3][playerid], "1                         2");
	    case 3: PlayerTextDrawSetString(playerid, textWeaponsHold[3][playerid], "1                         2                         3");
	}
	
	ShowPlayerWeaponsHold(playerid);
}

stock ShowPlayerWeaponsHold(playerid) {

	if (playerCountWeapons[playerid] < 1)
	    return 0;

	// Mostrar Textdarws

	for(new text; text < playerCountWeapons[playerid]; text++)
	    PlayerTextDrawShow(playerid, textWeaponsHold[text][playerid]);

    PlayerTextDrawShow(playerid, textWeaponsHold[3][playerid]);

	for(new text; text < playerCountWeapons[playerid]; text++)
	    PlayerTextDrawShow(playerid, textWeaponsHoldAmmo[text][playerid]);

	// Timer
	KillTimer(playerTimerHide[playerid]);

	playerTimerHide[playerid] = SetTimerEx("HidePlayerWeaponsHold", 3000, false, "d", playerid);
	
	return 1;
}

forward HidePlayerWeaponsHold(playerid);
public HidePlayerWeaponsHold(playerid) {

	// Esconder Textdarws

	for(new text; text < 4; text++)
	    PlayerTextDrawHide(playerid, textWeaponsHold[text][playerid]);

	for(new text; text < 3; text++)
	    PlayerTextDrawHide(playerid, textWeaponsHoldAmmo[text][playerid]);
}

stock CreatePlayerWeaponsHoldText(playerid) {

	textWeaponsHold[0][playerid] = CreatePlayerTextDraw(playerid,253.000000, 409.000000, "model_preview");
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHold[0][playerid], 100);
	PlayerTextDrawFont(playerid,textWeaponsHold[0][playerid], 5);
	PlayerTextDrawLetterSize(playerid,textWeaponsHold[0][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textWeaponsHold[0][playerid], -226);
	PlayerTextDrawSetOutline(playerid,textWeaponsHold[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHold[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHold[0][playerid], 1);
	PlayerTextDrawUseBox(playerid,textWeaponsHold[0][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textWeaponsHold[0][playerid], 0);
	PlayerTextDrawTextSize(playerid,textWeaponsHold[0][playerid], 43.000000, 35.000000);
	PlayerTextDrawSetPreviewModel(playerid, textWeaponsHold[0][playerid], 335);
	PlayerTextDrawSetPreviewRot(playerid, textWeaponsHold[0][playerid], -16.000000, 0.000000, -45.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHold[0][playerid], 1);

	textWeaponsHold[1][playerid] = CreatePlayerTextDraw(playerid,298.000000, 409.000000, "model_preview");
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHold[1][playerid], 100);
	PlayerTextDrawFont(playerid,textWeaponsHold[1][playerid], 5);
	PlayerTextDrawLetterSize(playerid,textWeaponsHold[1][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textWeaponsHold[1][playerid], -226);
	PlayerTextDrawSetOutline(playerid,textWeaponsHold[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHold[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHold[1][playerid], 1);
	PlayerTextDrawUseBox(playerid,textWeaponsHold[1][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textWeaponsHold[1][playerid], 0);
	PlayerTextDrawTextSize(playerid,textWeaponsHold[1][playerid], 43.000000, 35.000000);
	PlayerTextDrawSetPreviewModel(playerid, textWeaponsHold[1][playerid], 348);
	PlayerTextDrawSetPreviewRot(playerid, textWeaponsHold[1][playerid], -16.000000, 0.000000, -45.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHold[1][playerid], 1);

	textWeaponsHold[2][playerid] = CreatePlayerTextDraw(playerid,343.000000, 409.000000, "model_preview");
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHold[2][playerid], 100);
	PlayerTextDrawFont(playerid,textWeaponsHold[2][playerid], 5);
	PlayerTextDrawLetterSize(playerid,textWeaponsHold[2][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textWeaponsHold[2][playerid], -226);
	PlayerTextDrawSetOutline(playerid,textWeaponsHold[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHold[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHold[2][playerid], 1);
	PlayerTextDrawUseBox(playerid,textWeaponsHold[2][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textWeaponsHold[2][playerid], 0);
	PlayerTextDrawTextSize(playerid,textWeaponsHold[2][playerid], 43.000000, 35.000000);
	PlayerTextDrawSetPreviewModel(playerid, textWeaponsHold[2][playerid], 355);
	PlayerTextDrawSetPreviewRot(playerid, textWeaponsHold[2][playerid], -16.000000, 0.000000, -45.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHold[2][playerid], 1);

	textWeaponsHold[3][playerid] = CreatePlayerTextDraw(playerid,254.000000, 409.000000, "1                         2                         3");
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHold[3][playerid], 0);
	PlayerTextDrawFont(playerid,textWeaponsHold[3][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textWeaponsHold[3][playerid], 0.139999, 0.699998);
	PlayerTextDrawColor(playerid,textWeaponsHold[3][playerid], -186);
	PlayerTextDrawSetOutline(playerid,textWeaponsHold[3][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHold[3][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHold[3][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHold[3][playerid], 0);

	// Ammo
	textWeaponsHoldAmmo[0][playerid] = CreatePlayerTextDraw(playerid,295.000000, 436.000000, "000");
	PlayerTextDrawAlignment(playerid,textWeaponsHoldAmmo[0][playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHoldAmmo[0][playerid], 0);
	PlayerTextDrawFont(playerid,textWeaponsHoldAmmo[0][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textWeaponsHoldAmmo[0][playerid], 0.170000, 0.799997);
	PlayerTextDrawColor(playerid,textWeaponsHoldAmmo[0][playerid], -186);
	PlayerTextDrawSetOutline(playerid,textWeaponsHoldAmmo[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHoldAmmo[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHoldAmmo[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHoldAmmo[0][playerid], 0);

	textWeaponsHoldAmmo[1][playerid] = CreatePlayerTextDraw(playerid,340.000000, 436.000000, "000");
	PlayerTextDrawAlignment(playerid,textWeaponsHoldAmmo[1][playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHoldAmmo[1][playerid], 0);
	PlayerTextDrawFont(playerid,textWeaponsHoldAmmo[1][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textWeaponsHoldAmmo[1][playerid], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textWeaponsHoldAmmo[1][playerid], -186);
	PlayerTextDrawSetOutline(playerid,textWeaponsHoldAmmo[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHoldAmmo[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHoldAmmo[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHoldAmmo[1][playerid], 0);

	textWeaponsHoldAmmo[2][playerid] = CreatePlayerTextDraw(playerid,385.000000, 436.000000, "000");
	PlayerTextDrawAlignment(playerid,textWeaponsHoldAmmo[2][playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,textWeaponsHoldAmmo[2][playerid], 0);
	PlayerTextDrawFont(playerid,textWeaponsHoldAmmo[2][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textWeaponsHoldAmmo[2][playerid], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textWeaponsHoldAmmo[2][playerid], -186);
	PlayerTextDrawSetOutline(playerid,textWeaponsHoldAmmo[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textWeaponsHoldAmmo[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textWeaponsHoldAmmo[2][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textWeaponsHoldAmmo[2][playerid], 0);
}
