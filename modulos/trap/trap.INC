#define MAX_SERVER_TRAPS   (100)

enum zTrapEnum {

	Float:s_trapX,
	Float:s_trapY,
	Float:s_trapZ,
	
	s_trapObject,
	s_trapArea,
	s_trapTime,
}
static serverTrapInfo[MAX_SERVER_TRAPS][zTrapEnum];

static Iterator:iterTraps<MAX_SERVER_TRAPS>;

stock createPlayerTrap(playerid) {

	new id = Iter_Free(iterTraps);
	
	if (id == -1) return print("createPlayerMina: O limite de minas foi esgotado"), 0;
	
	Iter_Add(iterTraps, id);
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	
	CA_RayCastLine(x, y, z, x, y, z - 100.0, x, y, z);

	z += 0.2;
	
	serverTrapInfo[id][s_trapTime] = gettime() + 10;
	
	serverTrapInfo[id][s_trapX] = x;
	serverTrapInfo[id][s_trapY] = y;
	serverTrapInfo[id][s_trapZ] = z;
	
	serverTrapInfo[id][s_trapObject] = CreateDynamicObject(-1069, x, y, z, 0.0, 0.0, random(360), 0);
	serverTrapInfo[id][s_trapArea]   = CreateDynamicSphere(x, y, z, 1.7, 0);
	
	return 1;
}

stock destroyTrap(trapid) {

	if (Iter_Contains(iterTraps, trapid))
	{
		DestroyDynamicObject(serverTrapInfo[trapid][s_trapObject]);
		DestroyDynamicArea(serverTrapInfo[trapid][s_trapArea]);
		
		Iter_Remove(iterTraps, trapid);
	
	    return 1;
	}
	return 0;
}

stock saveServerTraps()
{
}

stock loadServerTraps()
{
}

public OnPlayerEnterDynamicArea(playerid, areaid) {

	foreach(new trapid : iterTraps) {
	
	    if (gettime() < serverTrapInfo[trapid][s_trapTime]) continue;
	
	    if (serverTrapInfo[trapid][s_trapArea] == areaid) {
	    
			PlayerData[playerid][dVida] -= (22.4321 + frandom(16.321));
	    
	        SendClientMessage(playerid, 0xFF5555FF, "* Você pisou em uma armadilha de urso!");
	    
		    if (PlayerData[playerid][dVida] < 1.0) {
		        serverKillClient(playerid, INVALID_PLAYER_ID, 255);
		    } else {
		        // apply animation
		        ApplyAnimation(playerid, "FINALE2", "FIN_Cop1_Loop", 5.1, 1, 0, 0, 1, 0);
		        
		        PlayerPlaySound(playerid, 36400, 0.0, 0.0, 0.0);
		        
		        // progress
		        StartPlayerProgress(playerid, "esarmando",
					.time = 200,
					.lose = 1.0,
					.startG = 0.0,
					.goTo = 100.0,
					.progressid = PROGRESS_ARMADILHA);
					
				// attach trap in foot
                SetPlayerAttachedObject(playerid, 6, -1068, 10, 0.043000,0.000000,0.006000,0.000000,-88.200019,0.000000,1.542000,1.000000,1.114000);
                
				// set blood loss

				// Perna quebrada
				PlayerData[playerid][dDoenca] = 1;
				PlayerData[playerid][dSangramento] += 0.2;
		    }

	        destroyTrap(trapid);
	    
	        break;
	    }
	}
	#if defined mOnPlayerEnterDynamicArea
	    mOnPlayerEnterDynamicArea(playerid, areaid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea mOnPlayerEnterDynamicArea
#if defined mOnPlayerEnterDynamicArea
	forward mOnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z) {

	foreach(new trapid : iterTraps) {

	    if (serverTrapInfo[trapid][s_trapObject] == objectid) {

	        destroyTrap(trapid);

	        break;
	    }
	}

	#if defined mOnPlayerShootDynamicObject
	    mOnPlayerShootDynamicObject(playerid, weaponid, objectid, x, y, z);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject mOnPlayerShootDynamicObject
#if defined mOnPlayerShootDynamicObject
	forward mOnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z);
#endif



