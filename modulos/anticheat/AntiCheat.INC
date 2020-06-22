// Maximo de slots
#define MAX_SLOTS_WEAPONS   		(13)

// Tempo para atualizar o anti cheat
#define ANTICHEAT_UPDATE_TICK  		(1000)

// Distancia para detectar o teleport ou airbreak
#define ANTICHEAT_RANGE_AIRBREAK    (95.0)

// Atualizar streamer ao setar a posição
#define STREAMER_UPDATE_POS         (1)
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Anti Cheaters
enum {
	antiCheatTeleport,      // 100%
	antiCheatAimbot,        // 100%
	antiCheatSpeedHack,     // 100%
	antiCheatFakeKill,      // 100%
	antiCheatStateHack,     // 100%
	antiCheatCrasher,       // 100%
	antiCheatCamHack,       // 100%
	antiCheatCarTroll,      // 100%
	antiCheatCarRespawn,    // 100%
	antiCheatMoneyHack,     // 100%
	antiCheatModCars,       // 100%
	antiCheatWeapon,        // 100%
	antiCheatAmmo,          // 100%
	antiCheatVehRepair,     // 100%
	antiCheatJetpack,       // 100%
}

stock const antiCheatNames[][25] = {

	{ "Airbreak/Teleport" },
	{ "Aimbot" },
	{ "Speed hack" },
	{ "Fake kill" },
	{ "State hack" },
	{ "Crasher" },
	{ "Cam hack" },
	{ "Car troll" },
	{ "Car respawn" },
	{ "Money Hack" },
	{ "Mod Cars" },
	{ "Weapon Hack" },
	{ "Ammo Hack" },
	{ "Vehicle-repair" },
	{ "Jetpack" }
};

enum antiCheatEnum
{
	// Tempo de intervalo para checar anti cheat
	antiCheatTick,
	
	// Tempo para parar a verificação
	antiCheatStopTimer,
	
	// Vezes que morreu sem spawnar
	antiCheatKills,
	
	// Vezes que mudou de state
	antiCheatState,
	antiCheatStateTick,
	
	// Ultima posição do jogador
	Float: antiCheatPos[6],
	
	// Vezes que mudou de veiculo
	antiCheatVehicleCount,
	antiCheatVehicleTick,
	antiCheatVehicleLast,
	
	// Vezes que enviou pacote v death
	antiCheatVDeathCount,
	antiCheatVDeathTick,
	
	// Wait weapon hack
	antiCheatWeaponTick,
}
new antiCheatInfo[MAX_PLAYERS][antiCheatEnum];

enum weapSlotEnum {
	slot_weapon,
	slot_ammo,
	Float:slot_health,
}

new AC_WeaponInfo[MAX_PLAYERS][MAX_SLOTS_WEAPONS][weapSlotEnum];

// tick last detect
new playerLastDetect[MAX_PLAYERS];

// count detect
new playerCountDetect[MAX_PLAYERS];

// Timer anticheat
static playerTimerAntiCheat[MAX_PLAYERS];

// Hooks
stock acResetAntiCheatInfo(playerid) {

	new currentTick = GetTickCount();

    antiCheatInfo[playerid][antiCheatVehicleTick] = currentTick + 500;
    antiCheatInfo[playerid][antiCheatVehicleCount] = 0;
    antiCheatInfo[playerid][antiCheatStopTimer] = currentTick + 10000;
    antiCheatInfo[playerid][antiCheatTick] 		= currentTick;
    antiCheatInfo[playerid][antiCheatKills]     = 0;
    antiCheatInfo[playerid][antiCheatState]     = 0;
    antiCheatInfo[playerid][antiCheatStateTick] = currentTick;
    antiCheatInfo[playerid][antiCheatVDeathTick] = currentTick + 500;
    antiCheatInfo[playerid][antiCheatVDeathCount] = 0;
}

stock getPlayerVehicleSpeed(playerid) {

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return 0;

	new playerVehicle = GetPlayerVehicleID(playerid);
	
	if (playerVehicle == 0)
	    return 0;
	
    static Float:x, Float:y, Float:z;
    GetVehicleVelocity(playerVehicle, x, y, z);
   	return floatround(floatsqroot(x * x + y * y) * 180);
}

stock acSetPlayerPos(playerid, Float:x, Float:y, Float:z, freezetime = 0, showloading = 0) {

	antiCheatInfo[playerid][antiCheatPos][3] = x;
	antiCheatInfo[playerid][antiCheatPos][4] = y;
	antiCheatInfo[playerid][antiCheatPos][5] = z;

	// Dar stop no anti cheat
	antiCheatInfo[playerid][antiCheatStopTimer] = GetTickCount() + 3000;
	
	// Resetar state change
	antiCheatInfo[playerid][antiCheatState] = 0;

	// Atualizar posição streamer
	#if STREAMER_UPDATE_POS == 1
	    Streamer_UpdateEx(playerid, x, y, z, -1, -1, STREAMER_TYPE_OBJECT);
	#endif

	if (freezetime) {
	
	    // Toggle player
	    TogglePlayerControllable(playerid, false);
	    
	    // Unfreeze time
	    SetTimerEx("unfreezePlayer", freezetime, false, "dd", playerid, showloading);
	    
	    if (showloading)
	    {
	        showPlayerLoading(playerid);
	    }
	}

	// Setar a posição do player
	return SetPlayerPos(playerid, x, y, z);
}

callback unfreezePlayer(playerid, showloading) {

	if (showloading)
	    hidePlayerLoading(playerid);

	return TogglePlayerControllable(playerid, true);
}

#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif
#define SetPlayerPos acSetPlayerPos

stock acPutPlayerInVehicle(playerid, vehicleid, seatid) {

	static Float:x, Float:y, Float:z;

	// Pegar a posição do veiculo
	GetVehiclePos(vehicleid, x, y, z);

	antiCheatInfo[playerid][antiCheatPos][3] = x;
	antiCheatInfo[playerid][antiCheatPos][4] = y;
	antiCheatInfo[playerid][antiCheatPos][5] = z;

	// Dar stop no anti cheat
	antiCheatInfo[playerid][antiCheatStopTimer] = GetTickCount() + 3000;

	// Resetar state change
	antiCheatInfo[playerid][antiCheatState] = 0;
	
	// Last vehicle
	antiCheatInfo[playerid][antiCheatVehicleLast] = vehicleid;

	// Atualizar posição streamer
	#if STREAMER_UPDATE_POS == 1
	    Streamer_UpdateEx(playerid, x, y, z, -1, -1, STREAMER_TYPE_OBJECT);
	#endif

	// Setar a posição do player
	return PutPlayerInVehicle(playerid, vehicleid, seatid);
}
#if defined _ALS_PutPlayerInVehicle
	#undef PutPlayerInVehicle
#else
	#define _ALS_PutPlayerInVehicle
#endif
#define PutPlayerInVehicle acPutPlayerInVehicle

stock acSetVehiclePos(vehicleid, Float:x, Float:y, Float:z) {

	foreach(new playerid : Player) {
	    if (GetPlayerVehicleID(playerid) == vehicleid) {
			antiCheatInfo[playerid][antiCheatPos][3] = x;
			antiCheatInfo[playerid][antiCheatPos][4] = y;
			antiCheatInfo[playerid][antiCheatPos][5] = z;

			// Dar stop no anti cheat
			antiCheatInfo[playerid][antiCheatStopTimer] = GetTickCount() + 3000;

			// Resetar state change
			antiCheatInfo[playerid][antiCheatState] = 0;

			// Last vehicle
			antiCheatInfo[playerid][antiCheatVehicleLast] = vehicleid;

			// Atualizar posição streamer
			#if STREAMER_UPDATE_POS == 1
			    Streamer_UpdateEx(playerid, x, y, z, -1, -1, STREAMER_TYPE_OBJECT);
			#endif
		}
	}

	// Setar a posição do vehicle
	return SetVehiclePos(vehicleid, x, y, z);
}
#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif
#define SetVehiclePos acSetVehiclePos

callback UpdateAntiCheatForPlayer(playerid)
{
		if (!PlayerData[playerid][dLogged])
		    return 0;

		new
		curTick = GetTickCount();

	    new
	        pstate = GetPlayerState(playerid);

	    // Anti Cheat - Airbreak ou Teleporte
	    if (!IsPlayerInRangeOfPoint(playerid, ANTICHEAT_RANGE_AIRBREAK, antiCheatInfo[playerid][antiCheatPos][0], antiCheatInfo[playerid][antiCheatPos][1], antiCheatInfo[playerid][antiCheatPos][2]))
		{
			if (!IsPlayerInRangeOfPoint(playerid, 25.0, antiCheatInfo[playerid][antiCheatPos][3], antiCheatInfo[playerid][antiCheatPos][4], antiCheatInfo[playerid][antiCheatPos][5]) && GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
			{
			    new
			        posurf = GetPlayerSurfingObjectID(playerid),
			        pvsurf = GetPlayerSurfingVehicleID(playerid);

			    if ((pstate == PLAYER_STATE_DRIVER || pstate == PLAYER_STATE_ONFOOT) && posurf == INVALID_OBJECT_ID && pvsurf == INVALID_VEHICLE_ID)
			    {
					#if defined detectServerAntiCheat
					    detectServerAntiCheat(playerid, antiCheatTeleport, #);
					#endif
				}
			}
	    }
	    GetPlayerPos(playerid, antiCheatInfo[playerid][antiCheatPos][0], antiCheatInfo[playerid][antiCheatPos][1], antiCheatInfo[playerid][antiCheatPos][2]);
	    
	    if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK)
	    {
			#if defined detectServerAntiCheat
			    detectServerAntiCheat(playerid, antiCheatJetpack, #);
			#endif
	    }

	    // Anti Cheat - Money Hack
	    if (GetPlayerMoney(playerid) > 0)
	    {
			#if defined detectServerAntiCheat
			    detectServerAntiCheat(playerid, antiCheatMoneyHack, #);
			#endif
	    }

		// Anti vehicle health
		if (pstate == PLAYER_STATE_DRIVER)
		{
		    new
		        Float:vhealth;

			new p_veh = GetPlayerVehicleID(playerid);

			GetVehicleHealth(p_veh, vhealth);

			if (vhealth < VehicleInfo[p_veh][vehHealth]) {
			    VehicleInfo[p_veh][vehHealth] = vhealth;
			}

			if (vhealth >= 980.0)
			{
				#if defined detectServerAntiCheat
				    detectServerAntiCheat(playerid, antiCheatVehRepair, #);
				#endif
			    DirectKick(playerid);

			    SetVehicleHealth(p_veh, VehicleInfo[p_veh][vehHealth]);

			    return 0;
			}
			if ( vhealth > VehicleInfo[p_veh][vehHealth] ) {
			    SetVehicleHealth(p_veh, VehicleInfo[p_veh][vehHealth]);
			}
			
		    // Anti Cheat - Speed Hack
		    if (getPlayerVehicleSpeed(playerid) > 265)
			{
				#if defined detectServerAntiCheat
				    detectServerAntiCheat(playerid, antiCheatSpeedHack, #);
				#endif
		    }
		}

	    // Anti Weapon Hack
	    if (curTick > antiCheatInfo[playerid][antiCheatWeaponTick])
	    {
		    new
			 	p_weapon, p_ammo;
		    for(new weaponslot; weaponslot < MAX_SLOTS_WEAPONS; weaponslot++)
		    {
		        GetPlayerWeaponData(playerid, weaponslot, p_weapon, p_ammo);

		        if (p_weapon > 0 && p_weapon < 46 && p_ammo > 0 && p_weapon != AC_WeaponInfo[playerid][weaponslot][slot_weapon])
		        {
					#if defined detectServerAntiCheat
					    detectServerAntiCheat(playerid, antiCheatWeapon, #);
					#endif
					SetPlayerAmmo(playerid, p_weapon, 0);
					//GivePlayerWeapon(playerid, AC_WeaponInfo[playerid][weaponslot][slot_weapon], AC_WeaponInfo[playerid][weaponslot][slot_ammo]);
					printf("ANTI WEAPON HACK: %s detected", getNome(playerid));
					break;
		        }
		        if (p_weapon > 0 && p_weapon < 46 && p_ammo > AC_WeaponInfo[playerid][weaponslot][slot_ammo])
		        {
		        /*
					#if defined detectServerAntiCheat
					    detectServerAntiCheat(playerid, antiCheatAmmo, #);
					#endif
					*/
					SetPlayerAmmo(playerid, p_weapon, AC_WeaponInfo[playerid][weaponslot][slot_ammo]);
//					printf("ANTI AMMO HACK: %s detected", getNome(playerid));
					break;
		        }
		        if (p_ammo < -1000)
		        {
					#if defined detectServerAntiCheat
					    detectServerAntiCheat(playerid, antiCheatWeapon, #);
					#endif
				    SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado pelo anti-cheat (Weapon-hack)");
				    Kick(playerid);

				    break;
		        }
//		        AC_WeaponInfo[playerid][weaponslot][slot_ammo] = p_ammo;
		    }
		}
		
		return 1;
}

// Update anti cheat
public OnPlayerUpdate(playerid)
{
	static curTick, p_vehid;
	curTick = GetTickCount();
	
	// Anti flood cars
	p_vehid = GetPlayerVehicleID(playerid);
	    
	if (p_vehid != antiCheatInfo[playerid][antiCheatVehicleLast])
	{
	    if (curTick < antiCheatInfo[playerid][antiCheatVehicleTick] && p_vehid != 0)
	    {
	        antiCheatInfo[playerid][antiCheatVehicleCount] ++;
	        
	        if (antiCheatInfo[playerid][antiCheatVehicleCount] > 3)
	        {
				#if defined detectServerAntiCheat
				    detectServerAntiCheat(playerid, antiCheatCarTroll, #);
				#endif
	            DirectKick(playerid);
	            return 1;
	        }
	    } else {
	        antiCheatInfo[playerid][antiCheatVehicleTick] = curTick + 500;
	        antiCheatInfo[playerid][antiCheatVehicleCount] = 0;
	    }
	
	    antiCheatInfo[playerid][antiCheatVehicleLast] = p_vehid;
	}

	static
		weaponid
		;

	weaponid = GetPlayerWeapon(playerid);

	if ( weaponid == 44 || weaponid == 45 ) {

		static Keys, ud, lr;
	    GetPlayerKeys(playerid, Keys, ud, lr);

	    if ( Keys & KEY_FIRE ) {
	        return 0;
	    }
	}

	// ALS Hook
	#if defined antiCheatOnPlayerUpdate
	    return antiCheatOnPlayerUpdate(playerid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate antiCheatOnPlayerUpdate
#if defined antiCheatOnPlayerUpdate
	forward antiCheatOnPlayerUpdate(playerid);
#endif


public OnPlayerRequestClass(playerid, classid) {

	acResetAntiCheatInfo(playerid);
    
	#if defined antiOnPlayerRequestClass
        return antiOnPlayerRequestClass(playerid, classid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerRequestClass
	#undef OnPlayerRequestClass
#else
	#define _ALS_OnPlayerRequestClass
#endif
#define OnPlayerRequestClass antiOnPlayerRequestClass
#if defined antiOnPlayerRequestClass
	forward antiOnPlayerRequestClass(playerid, classid);
#endif

public OnVehicleDeath(vehicleid, killerid) {

	if (GetTickCount() < antiCheatInfo[killerid][antiCheatVDeathTick])
 	{
  		antiCheatInfo[killerid][antiCheatVDeathCount] ++;

		if (antiCheatInfo[killerid][antiCheatVDeathCount] > 3)
  		{
			#if defined detectServerAntiCheat
			    detectServerAntiCheat(killerid, antiCheatCarRespawn, #);
			#endif
    		DirectKick(killerid);
        }
    } else {
    	antiCheatInfo[killerid][antiCheatVDeathTick] = GetTickCount() + 500;
	    antiCheatInfo[killerid][antiCheatVDeathCount] = 0;
    }

	#if defined antiOnVehicleDeath
        return antiOnVehicleDeath(vehicleid, killerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnVehicleDeath
	#undef OnVehicleDeath
#else
	#define _ALS_OnVehicleDeath
#endif
#define OnVehicleDeath antiOnVehicleDeath
#if defined antiOnVehicleDeath
	forward antiOnVehicleDeath(vehicleid, killerid);
#endif

public OnPlayerConnect(playerid) {

	if (IsPlayerNPC(playerid))
	    return 1;

	if (playerTimerAntiCheat[playerid] == 0)
    	playerTimerAntiCheat[playerid] = SetTimerEx("UpdateAntiCheatForPlayer", ANTICHEAT_UPDATE_TICK, true, "d", playerid);

	acResetAntiCheatInfo(playerid);
	
	#if defined antiCheatOnPlayerConnect
        antiCheatOnPlayerConnect(playerid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect antiCheatOnPlayerConnect
#if defined antiCheatOnPlayerConnect
	forward antiCheatOnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason) {

	if (IsPlayerNPC(playerid))
	    return 1;

	if (playerTimerAntiCheat[playerid] > 0)
    	KillTimer(playerTimerAntiCheat[playerid]);

    playerTimerAntiCheat[playerid] = 0;

	#if defined antiCheatOnPlayerDisconnect
        antiCheatOnPlayerDisconnect(playerid, reason);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect antiCheatOnPlayerDisconnect
#if defined antiCheatOnPlayerDisconnect
	forward antiCheatOnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerSpawn(playerid) {

	acResetAntiCheatInfo(playerid);
	
	playerCountDetect[playerid] = 0;
	playerLastDetect[playerid] = 0;

	#if defined antiCheatOnPlayerConnect
        return antiCheatOnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn antiCheatOnPlayerSpawn
#if defined antiCheatOnPlayerSpawn
	forward antiCheatOnPlayerSpawn(playerid);
#endif

public OnPlayerDeath(playerid, killerid, reason) {

	antiCheatInfo[playerid][antiCheatKills] ++;
	
	if (antiCheatInfo[playerid][antiCheatKills] > 2) {
		#if defined detectServerAntiCheat
		    detectServerAntiCheat(playerid, antiCheatFakeKill, #);
		#endif
	}

	#if defined antiCheatOnPlayerDeath
        return antiCheatOnPlayerDeath(playerid, killerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath antiCheatOnPlayerDeath
#if defined antiCheatOnPlayerDeath
	forward antiCheatOnPlayerDeath(playerid, killerid, reason);
#endif

public OnPlayerStateChange(playerid, newstate, oldstate) {

	antiCheatInfo[playerid][antiCheatState] ++;

	if (antiCheatInfo[playerid][antiCheatStateTick] < GetTickCount()) {

		antiCheatInfo[playerid][antiCheatStateTick] = GetTickCount() + 1000;
	    antiCheatInfo[playerid][antiCheatState] 	= 0;
	}

	if (antiCheatInfo[playerid][antiCheatState] > 3) {

		#if defined detectServerAntiCheat
		    detectServerAntiCheat(playerid, antiCheatStateHack, #);
		#endif
	}

	#if defined antiCheatOnPlayerStateChange
        return antiCheatOnPlayerStateChange(playerid, newstate, oldstate);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
	#undef OnPlayerStateChange
#else
	#define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange antiCheatOnPlayerStateChange
#if defined antiCheatOnPlayerStateChange
	forward antiCheatOnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	// Anti Crasher
	if( hittype != BULLET_HIT_TYPE_NONE ) {
	    if(!( -1000.0 <= fX <= 1000.0 ) || !( -1000.0 <= fY <= 1000.0 ) || !( -1000.0 <= fZ <= 1000.0)) {
			return 0;
		}
	}
	
    if((weaponid < 22 || weaponid > 38)) {
		return 0;
	}

	static
	    Float:x,
	    Float:y,
	    Float:z;
	GetPlayerPos(playerid, x, y, z);

    applyRuido(x, y, z, ALTURA_TIRO, MAX_ALTURA_TIRO);

	// Anti Cam hack
	static Float:frX, Float:frY, Float:frZ,
	       Float:toX, Float:toY, Float:toZ;
	       
    // Pegar a posição da camera
    GetPlayerCameraPos(playerid, frX, frY, frZ);

	if (weaponid == 34 && GetPlayerDistanceFromPoint(playerid, frX, frY, frZ) > 10.0) {
		#if defined detectServerAntiCheat
		    detectServerAntiCheat(playerid, antiCheatCamHack, #);
		#endif
	}

	if (hittype == BULLET_HIT_TYPE_PLAYER && !IsPlayerInAnyVehicle(playerid) && !IsPlayerInAnyVehicle(hitid)) {

		// Variáveis
	    new
		achitSurfingObject   = GetPlayerSurfingObjectID(hitid),
		achitSurfingVehicle  = GetPlayerSurfingVehicleID(hitid),
		Float:achitDistance
		;

	    // Anti Pro-Aimbot

		// Pegar a posição do ultimo tiro
	    GetPlayerLastShotVectors(playerid, frX, frY, frZ, toX, toY, toZ);
	    
        achitDistance = GetPlayerDistanceFromPoint(hitid, toX, toY, toZ);

		if ((achitSurfingObject == INVALID_OBJECT_ID && achitSurfingVehicle == INVALID_VEHICLE_ID) && achitDistance > 6.0 && achitDistance < 200.0 && IsPlayerInRangeOfPoint(playerid, 6.0, toX, toY, toZ)) {

			#if defined detectServerAntiCheat
			    detectServerAntiCheat(playerid, antiCheatAimbot, #);
			#endif
		}
	}
    if (weaponid > 21 && weaponid < 38)
    {
        new slotid = GetWeaponSlot(weaponid);
        
	    AC_WeaponInfo[playerid][slotid][slot_ammo] --;
	    
	    if (AC_WeaponInfo[playerid][slotid][slot_ammo] < 0) AC_WeaponInfo[playerid][slotid][slot_ammo] = 0;
	}

	#if defined antiCheatOnPlayerStateChange
        return antiCheatOnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerWeaponShot
	#undef OnPlayerWeaponShot
#else
	#define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot antiCheatOnPlayerWeaponShot
#if defined antiCheatOnPlayerWeaponShot
	forward antiCheatOnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif

public OnVehicleMod(playerid,vehicleid,componentid)
{
    if(GetPlayerInterior(playerid) == 0)
    {
		#if defined detectServerAntiCheat
		    detectServerAntiCheat(playerid, antiCheatModCars, #);
		#endif
	    SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado pelo anti-cheat (Car Mod)");
	    Kick(playerid);
        return 0; 
    }
    return 0; // server not using mods
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
    if(GetPlayerInterior(playerid) == 0)
    {
		#if defined detectServerAntiCheat
		    detectServerAntiCheat(playerid, antiCheatModCars, #);
		#endif
	    SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado pelo anti-cheat (Car Mod)");
	    Kick(playerid);
        return 0;
    }
    return 0; // server not using mods
}

stock GetPlayerWeaponDataReal(playerid, slotid, &weaponid, &ammo) {

	GetPlayerWeaponData(playerid, slotid, weaponid, ammo);

	return 1;
}

// Hooks weapon hack
stock AC_GivePlayerWeapon(playerid, weaponid, ammo, Float:health = 100.0) {

	if (weaponid < 0 || weaponid > 46) return 0;

	new slot = GetWeaponSlot(weaponid);
    AC_WeaponInfo[playerid][slot][slot_weapon] = weaponid;
    AC_WeaponInfo[playerid][slot][slot_ammo]  += ammo;
    AC_WeaponInfo[playerid][slot][slot_health] = health;

    if (weaponid == 43) {
        ammo = 999;
    }

    updateWeaponSelect(playerid);

    antiCheatInfo[playerid][antiCheatWeaponTick] = GetTickCount() + 3000;

    return GivePlayerWeapon(playerid, weaponid, ammo);
}

stock AC_GetPlayerAmmo(playerid) {

	new weaponid = GetPlayerWeapon(playerid);

	if (weaponid == 43)
	{
	    return 1;
	}
	new amount = GetPlayerAmmo(playerid);
	new slot = GetWeaponSlot(weaponid);
	
	if (weaponid > 0 && weaponid < 46 && amount > AC_WeaponInfo[playerid][slot][slot_ammo])
	{
	    amount = AC_WeaponInfo[playerid][slot][slot_ammo];
	}
	
	return amount;
}

callback Float:GetWeaponHealth(playerid, weaponid) {

	if (weaponid < 0 || weaponid > 46) return 0.0;

	new slot = GetWeaponSlot(weaponid);
    return AC_WeaponInfo[playerid][slot][slot_health];
}

callback SetWeaponHealth(playerid, weaponid, Float:health) {

	if (weaponid < 0 || weaponid > 46) return 0;

	new slot = GetWeaponSlot(weaponid);
    AC_WeaponInfo[playerid][slot][slot_health] = health;

    if (AC_WeaponInfo[playerid][slot][slot_health] < 1.0)
    {
        RemovePlayerWeapon(playerid, weaponid);
        new str[75];
        format(str, sizeof str, "Sua arma %s quebrou por estar muito desgastada...", NomeArma(weaponid));
        SendServerMessageToPlayer(playerid, str);
    }

    return 1;
}

callback AC_ResetPlayerWeapons(playerid) {

	for (new slot; slot < MAX_SLOTS_WEAPONS; slot++) {
    	AC_WeaponInfo[playerid][slot][slot_weapon] = 0;
    	AC_WeaponInfo[playerid][slot][slot_ammo]   = 0;
    	AC_WeaponInfo[playerid][slot][slot_health] = 0.0;
	}

	RemovePlayerAttachedObject(playerid, 1);
	RemovePlayerAttachedObject(playerid, 2);
	RemovePlayerAttachedObject(playerid, 3);

	updateWeaponSelect(playerid);
	
	antiCheatInfo[playerid][antiCheatWeaponTick] = GetTickCount() + 5000;

	return ResetPlayerWeapons(playerid);
}

callback IsPlayerHaveWeapon(playerid, weaponid) {

	for (new slot; slot < MAX_SLOTS_WEAPONS; slot++) {
	    // checar se tem a arma
	    if (AC_WeaponInfo[playerid][slot][slot_weapon] == weaponid) return 1;
	}

	return 0;
}

callback AC_SetPlayerAmmo(playerid, weaponid, ammo) {

	if (weaponid < 0 || weaponid > 46) return 0;

	new slot = GetWeaponSlot(weaponid);
    AC_WeaponInfo[playerid][slot][slot_ammo] = ammo;

    updateWeaponSelect(playerid);
    
    antiCheatInfo[playerid][antiCheatWeaponTick] = GetTickCount() + 3000;

	return SetPlayerAmmo(playerid, weaponid, ammo);
}

stock AC_GetPlayerWeaponData(playerid, slotid, &weaponid, &ammo, &Float:health = 100.0) {

    if (slotid < 0 || slotid >= MAX_SLOTS_WEAPONS || !AC_WeaponInfo[playerid][slotid][slot_weapon])  {

        weaponid = 0;
		ammo = 0;

		return 0;
	}

	GetPlayerWeaponData(playerid, slotid, weaponid, ammo);
    //ammo	 = AC_WeaponInfo[playerid][slotid][slot_ammo];


	weaponid = AC_WeaponInfo[playerid][slotid][slot_weapon];
	health = AC_WeaponInfo[playerid][slotid][slot_health];

	if (weaponid == 46) {
	    weaponid = 0;
	}

	if (ammo > AC_WeaponInfo[playerid][slotid][slot_ammo])
	    ammo = AC_WeaponInfo[playerid][slotid][slot_ammo];

	if (weaponid == 43) {
	    ammo = 1;
	}

	return 1;
}

stock AC_SetVehicleHealth(vehicleid, Float:health)
{
    VehicleInfo[vehicleid][vehHealth] = health;
    return SetVehicleHealth(vehicleid, health);
}


// Callback de anti cheat
forward detectServerAntiCheat(playerid, anticheatid, description[]);
public detectServerAntiCheat(playerid, anticheatid, description[]) {

	if (!PlayerData[playerid][dLogged] || GetTickCount() < antiCheatInfo[playerid][antiCheatStopTimer])
	    return 0;

	new string_ac[144];

	format(string_ac, sizeof (string_ac), "- AC -: %s(%d) foi detectado pelo anticheat (%s) - use /slap para checar se não está de RT.", getNome(playerid), playerid, antiCheatNames[anticheatid]);
	sendMessageToAdmins(string_ac, 0xFF5500FF);
	
	Log::("anticheat", "%s\t|Cheat: %s", getNome(playerid), antiCheatNames[anticheatid]);
	
	if (gettime() > playerLastDetect[playerid])
	{
	    playerLastDetect[playerid] = gettime() + 60;
	    playerCountDetect[playerid] = 0;
	}
	
    playerCountDetect[playerid] ++;
    
    if (playerCountDetect[playerid] == 3)
    {
	    playerLastDetect[playerid] = gettime() + 60;
	    playerCountDetect[playerid] = 0;
        
		format(string_ac, sizeof (string_ac), "- AC -: %s(%d) foi kickado automaticamente.", getNome(playerid), playerid);
		sendMessageToAdmins(string_ac, 0xFF5500FF);

		Log::("anticheat", "%s\t|automatic kick", getNome(playerid));
        
	    SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado automaticamente pelo anti-cheat.");
	    Kick(playerid);
		return 1;
    }
	
	// check if is money hack
	if (anticheatid == antiCheatMoneyHack)
	{
	    SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado pelo anti-cheat (Money-hack)");
	    Kick(playerid);
	}
	
	else if(anticheatid == antiCheatJetpack)
	{
	    if (PlayerData[playerid][dAdmin] < 5)
	    {
	    	SendClientMessage(playerid, 0xAAAAAAFF, "Você foi kickado pelo anti-cheat (Jetpack)");
	    	Kick(playerid);
		}
	}
	
	print(string_ac);

	return 1;
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon 		AC_GivePlayerWeapon

#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons 		AC_ResetPlayerWeapons

#if defined _ALS_SetPlayerAmmo
	#undef SetPlayerAmmo
#else
	#define _ALS_SetPlayerAmmo
#endif
#define SetPlayerAmmo           AC_SetPlayerAmmo

#if defined _ALS_GetPlayerWeaponData
	#undef GetPlayerWeaponData
#else
	#define _ALS_GetPlayerWeaponData
#endif
#define GetPlayerWeaponData     AC_GetPlayerWeaponData

#if defined _ALS_GetPlayerAmmo
	#undef GetPlayerAmmo
#else
	#define _ALS_GetPlayerAmmo
#endif
#define GetPlayerAmmo     		AC_GetPlayerAmmo

#if defined _ALS_SetVehicleHealth
	#undef SetVehicleHealth
#else
	#define _ALS_SetVehicleHealth
#endif
#define SetVehicleHealth    	AC_SetVehicleHealth


