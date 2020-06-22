#include "../modulos/cervos/core.inc"

new
	countDeers;

stock createDeers() {

	// Timer
	SetTimer("updateDeers", DEER_UPDATE_TIME + 490, true);

	// Criar cervos
	for(new deer; deer != MAX_DEERS; deer++) {
	
	    new rdon = random(sizeof DeerSpawns);
	    
	    deerCreate(DeerSpawns[rdon][0]+frandom(100.0)-frandom(100.0), DeerSpawns[rdon][1]+frandom(100.0)-frandom(100.0));
	}
}

stock deerGetGroundZ(Float:x, Float:y, &Float:z) {
	CA_FindZ_For2DCoord(x, y, z);
}

stock deerCreate(Float:x, Float:y, Float:z=0.0) {

	deerGetGroundZ(x, y, z);
	deerInfo[countDeers][deerDead]      = false;
	deerInfo[countDeers][deerAssustado] = false;
    deerInfo[countDeers][deerRespawn]   = 0;
    deerInfo[countDeers][deerHealth]    = 30.0;
	        
	deerInfo[countDeers][deerObject] = CreateDynamicObject(19315, x, y, z, 0.0, 0.0, random(360));
	    
    countDeers++;

	return 0;
}

stock deerMove(deerid, Float:x, Float:y, Float:z) {

	if (!deerInfo[deerid][deerDead]) {
	
	    new Float:px, Float:py, Float:pz;
	    
	    getDeerPosition(deerid, px, py, pz);
	
	    deerGetGroundZ(x, y, z);
	
	    SetDynamicObjectRot(deerInfo[deerid][deerObject], 0.0, 0.0, (GetPointAngleToPoint(px, py, x, y) + 90.0));
	    
	   	MoveDynamicObject(deerInfo[deerid][deerObject], x, y, z + 0.37, deerInfo[deerid][deerAssustado] ? (DEER_SPEED_ASSUSTADO) : (DEER_SPEED_NORMAL));
	
	    return 1;
	}
	return 0;
}

stock isDeerViewingPlayer(deerid) {

	new Float:x, Float:y, Float:z;
	GetDynamicObjectPos(deerInfo[deerid][deerObject], x, y, z);
	
	foreach(new playerid : Player) {
	
	    if (IsPlayerInRangeOfPoint(playerid, 25.0, x, y, z)) {
	        return 1;
	    }
	}
	return 0;
}

stock getDeerPosition(deerid, &Float:x, &Float:y, &Float:z) {
    GetDynamicObjectPos(deerInfo[deerid][deerObject], x, y, z);
	return 1;
}

stock respawnDeer(deerid) {

    new rdon = random(sizeof DeerSpawns);
	new Float:x = DeerSpawns[rdon][0],
		Float:y = DeerSpawns[rdon][1],
		Float:z = DeerSpawns[rdon][2];

    deerGetGroundZ(x, y, z);
	deerInfo[deerid][deerDead]      = false;
	deerInfo[deerid][deerAssustado] = false;
    deerInfo[deerid][deerRespawn]   = 0;

	DestroyDynamic3DTextLabel(deerInfo[deerid][deerText]);

   	StopDynamicObject(deerInfo[deerid][deerObject]);
  	SetDynamicObjectPos(deerInfo[deerid][deerObject], x, y, z + 0.37);

	return 1;
}

stock matarDeer(deerid) {

	if (!deerInfo[deerid][deerDead]) {

        new Float:x, Float:y, Float:z;

        deerInfo[deerid][deerDead] 	  = true;
        deerInfo[deerid][deerRespawn] = gettime() + DEER_RESPAWN_TIME;
        
	    getDeerPosition(deerid, x, y, z);

	    deerGetGroundZ(x, y, z);
	    
	    MoveDynamicObject(deerInfo[deerid][deerObject], x, y + frandom(0.01), z + 0.2, 1.0, 90.0, 0.0);
	    deerInfo[deerid][deerText] = CreateDynamic3DTextLabel("{BB0000}Cervo Morto\n{BBBBBB}Use {FFFFFF}/cortarcarne {BBBBBB}para cortar a carne", 0xFFFFFFCC, x, y, z + 0.2, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0);

		return 1;
	}
	return 0;
}

callback updateDeers() {

	static Float:x, Float:y, Float:z;

	for(new deer; deer != MAX_DEERS; deer++) {

		if (!deerInfo[deer][deerDead]) {
				
			if (deerInfo[deer][deerAssustado] && gettime() > deerInfo[deer][deerTimeAssustado]) {
			    deerInfo[deer][deerAssustado] = false;
			}

			getDeerPosition(deer, x, y, z);

            if (IsDynamicObjectMoving(deerInfo[deer][deerObject]) && !deerInfo[deer][deerAssustado]) continue;
                
			deerMove(deer, x + frandom(10.0) - frandom(10.0), y + frandom(10.0) - frandom(10.0), z);
		} else {
			
			if (deerInfo[deer][deerRespawn] && (gettime() > deerInfo[deer][deerRespawn])) {
			    respawnDeer(deer);
			}
		}
	}
	return 1;
}

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z) {

	for(new deer; deer != MAX_DEERS; deer++) {
	
		if (!deerInfo[deer][deerDead] && objectid == deerInfo[deer][deerObject]) {
			
		    static Float:pos[3];
			
		 	// Pegar a posição do player
		   	getDeerPosition(deer, pos[0], pos[1], pos[2]);

			// Dar os pontos
		   	givePlayerPoints(playerid, floatround(getWeaponZDamage(weaponid) / 2.0), pos[0]+frandom(0.03)-frandom(0.03), pos[1]+frandom(0.03)-frandom(0.03), pos[2]+frandom(0.05)-frandom(0.05));
			
		    new Float:amount = getWeaponZDamage(weaponid) / 2.0;
			
		    deerInfo[deer][deerHealth] -= amount;
		    
            if (!deerInfo[deer][deerAssustado]) deerInfo[deer][deerAssustado] = true;

            deerInfo[deer][deerTimeAssustado] = gettime() + 16;
			
		    if (deerInfo[deer][deerHealth] <= 0.0) {
		    	matarDeer(deer);
			    	
			   	deerInfo[deer][deerHealth] = 30.0;
			    	
				// Dar os pontos
		     	givePlayerPoints(playerid, 55, pos[0]+frandom(0.03)-frandom(0.03), pos[1]+frandom(0.03)-frandom(0.03), pos[2]+0.05, 0xFFAA00CC);
			       	
		     	checkPlayerConquista(playerid, Conquista_Cacador);
			}
		}
	}

	#if defined dOnPlayerShootDynamicObject
	    dOnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject dOnPlayerShootDynamicObject
#if defined dOnPlayerShootDynamicObject
	forward dOnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif

CMD:cortarcarne(playerid) {

    if (GetPVarInt(playerid, "cortandoCarne")) return SendLanguageMessage(playerid, corError, "MSG_043");

    static Float:x, Float:y, Float:z;

	for(new deer; deer != MAX_DEERS; deer++) {

	    if (deerInfo[deer][deerDead]) {

			GetDynamicObjectPos(deerInfo[deer][deerObject], x, y, z);
			
			if (IsPlayerInRangeOfPoint(playerid, 1.5, x, y, z)) {
			
			    if (GetPlayerWeapon(playerid) != 4)
					return SendLanguageMessage(playerid, corError, "MSG_044");
			
			    SetPVarInt(playerid, "cortandoCarne", 1);
			
				SetTimerEx("cortarCarne", TEMPO_CORTAR_CARNE, false, "iii", playerid, deer);
			
			    StartPlayerProgress(playerid, "Aguarde...", 900,  20.0);
			
			    ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.0, 1, 0, 0, 0, 0);
			
			    SendLanguageMessage(playerid, corInfo, "MSG_045");
			
			    SetPlayerArmedWeapon(playerid, 4);
			
				new Float:pos[3];
				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				
				SetPlayerFacingAngle(playerid, GetPointAngleToPoint(pos[0], pos[1], x, y));
			
			    return 1;
			}
		}
	}
	
	SendLanguageMessage(playerid, corError, "MSG_046");
	
	return 1;
}

callback cortarCarne(playerid, deerid) {

    if (GetPVarInt(playerid, "cortandoCarne")) {
    
        static Float:x, Float:y, Float:z;
        GetDynamicObjectPos(deerInfo[deerid][deerObject], x, y, z);
    
		if (!IsPlayerInRangeOfPoint(playerid, 1.5, x, y, z)) return SendLanguageMessage(playerid, corError, "MSG_046");
		
        respawnDeer(deerid);
    
        GetPlayerPos(playerid, x, y, z);
    
        createDroppedItem(x + frandom(0.5)-frandom(0.5), y + frandom(0.5)-frandom(0.5), z - 0.5, "Carne crua", ITEM_TYPE_CARNECRUA, 2804, 1 + random(2), .health = 0.0);
        createDroppedItem(x + frandom(0.5)-frandom(0.5), y + frandom(0.5)-frandom(0.5), z - 0.5, "Couro", ITEM_TYPE_COURO, 1577, 1);
    
        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    
        ClearAnimations(playerid);
    
        DeletePVar(playerid, "cortandoCarne");
    }
	return 1;
}










