


#define MAX_AIR_DROPS   (100)

enum AirDropEnum {
	AirDropValid,
	AirDropId,
	AirDropParachute,
	AirPlane,
	AirWorld,
	AirType,
	Float: airX,
	Float: airY,
	Float: airZ,
	Float: airToX,
	Float: airToY,
}
static AirDropInfo[MAX_AIR_DROPS][AirDropEnum];

callback CreateServerAirDrop() {

	static Float:x, Float:y;
	x = 0.0 + frandom(2900.0) - frandom(2900.0);
	y = 0.0 + frandom(2900.0) - frandom(2900.0);

	SendClientMessageToAll(corCinza, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
	SendClientMessageToAllf(corAmarelo, "[AIRDROP] {FFFFFF}Um avião está sobrevoando a região de '{00AAFF}%s{FFFFFF}' e vai largar {AAFFFF}Itens {FFFFFF}em 3 minutos!", LocationName(x, y, 0.0));
	SendClientMessageToAll(corCinza, "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");

    SetTimerEx("CallAirDrop", 2 * 60000, false, "ffdd", x, y, 0, LOOT_TYPE_MILITAR);
//  CallAirDrop(x, y);

	printf("[AirDrop] Sera largado em: %f %f %s", x, y, LocationName(x, y, 0.0));
}

callback CallAirDrop(Float:x, Float:y, world, loottype) {

	for(new airdrop; airdrop < MAX_AIR_DROPS; airdrop++) {

		if (AirDropInfo[airdrop][AirDropValid])
		    continue;

		AirDropInfo[airdrop][AirDropValid] = 1;
		AirDropInfo[airdrop][AirWorld]     = world;
		AirDropInfo[airdrop][AirType]      = loottype;

		CreateAirDrop(airdrop, x, y, 1000.0);

		return 1;
	}
	
	return 0;
}

callback CreateAirDrop(airdrop, Float:x, Float:y, Float:z) {

	static Float: fx;
	static Float: fy;
	static Float: ang;

	CA_RayCastLine(x, y, 1000.0, x, y, -1000.0, x, y, z);

	AirDropInfo[airdrop][airX] = x;
	AirDropInfo[airdrop][airY] = y;
	AirDropInfo[airdrop][airZ] = z;

	fx = x + (random(3000) - random(3000));
	fy = y + (random(3000) - random(3000));

	ang = GetPointAngleToPoint(fx, fy, x, y);

	AirDropInfo[airdrop][AirPlane] = CreateDynamicObject(10757, fx, fy, z + (AirDropInfo[airdrop][AirWorld] != 5001 ? (300.0) : (250.0)), 0.0, 0.0, ang - 180.0, AirDropInfo[airdrop][AirWorld], -1, -1, 800.0, 800.0);

	AirDropInfo[airdrop][airToX] = fx + (15000.0 * floatsin(-ang, degrees));
	AirDropInfo[airdrop][airToY] = fy + (15000.0 * floatcos(-ang, degrees));

	if (AirDropInfo[airdrop][AirWorld] != 5001) {
		MoveDynamicObject(AirDropInfo[airdrop][AirPlane], x, y, z + 300.0, 20.0, 0.0, 0.0, ang - 180);
	} else {
	    MoveDynamicObject(AirDropInfo[airdrop][AirPlane], x, y, z + 250.0, 35.0, 0.0, 0.0, ang - 180);
	}
	
	foreach(new playerid : Player) {

		if (IsPlayerInRangeOfPoint(playerid, 1000.0, x, y, z) && GetPlayerVirtualWorld(playerid) == AirDropInfo[airdrop][AirWorld]) {
	        Audio_PlayStreamed(playerid, "https://japeto.sscdn.co/palcomp3/1/3/3/d/znation-airdrop-aab44e4b.mp3?");
		}
	}
}

callback ContinueAirDrop(airdrop, airplane, Float:x, Float:y, Float:z) {

	AirDropInfo[airdrop][AirDropId] = CreateDynamicObject(-1021, x, y, z + (AirDropInfo[airdrop][AirWorld] != 5001 ? (300.0) : (250.0)), 0.0, 0.0, 0.0, AirDropInfo[airdrop][AirWorld], -1, -1, 800.0, 800.0);

    AirDropInfo[airdrop][AirDropParachute] = CreateDynamicObject(-1022, x, y, z + (AirDropInfo[airdrop][AirWorld] != 5001 ? (300.0) : (250.0)), 0.0, 0.0, 0.0, AirDropInfo[airdrop][AirWorld], -1, -1, 800.0, 800.0);

	MoveDynamicObject(AirDropInfo[airdrop][AirDropId], x, y, z + 1.0, AirDropInfo[airdrop][AirWorld] != 5001 ? (1.8) : (2.5), 0.0, 0.0, random(360));
	MoveDynamicObject(AirDropInfo[airdrop][AirDropParachute], x, y, z + 1.0, AirDropInfo[airdrop][AirWorld] != 5001 ? (1.8) : (2.5), 0.0, 0.0, random(360));

    SetTimerEx("DestroyAirplane", 2 * 60000, false, "d", airplane);
    
    if (AirDropInfo[airdrop][AirWorld] != 5001) {
    	MoveDynamicObject(AirDropInfo[airdrop][AirPlane], AirDropInfo[airdrop][airToX], AirDropInfo[airdrop][airToY], z + 300.0, 20.0);
	} else {
	    MoveDynamicObject(AirDropInfo[airdrop][AirPlane], AirDropInfo[airdrop][airToX], AirDropInfo[airdrop][airToY], z + 250.0, 35.0);
	}
    
    new string[75];
    format(string, sizeof (string), "Um aviao sobrevoou a regiao de %s e largou um AirDrop", LocationName(x, y, 0.0));

	foreach(new playerid : Player) {

		if (GetPlayerVirtualWorld(playerid) == AirDropInfo[airdrop][AirWorld]) {
	        SendServerMessageToPlayer(playerid, string);
		}
	}
//  SendDayZMessage(string);
}

callback DestroyAirplane(airplane) return DestroyDynamicObject(airplane);

public OnDynamicObjectMoved(objectid)
{
	for(new airdrop; airdrop < MAX_AIR_DROPS; airdrop++)
	{
		if (!AirDropInfo[airdrop][AirDropValid])
		    continue;

		if (objectid == AirDropInfo[airdrop][AirPlane])
		{
		    ContinueAirDrop(airdrop, AirDropInfo[airdrop][AirPlane], AirDropInfo[airdrop][airX], AirDropInfo[airdrop][airY], AirDropInfo[airdrop][airZ]);
		}
		else if (objectid == AirDropInfo[airdrop][AirDropId])
		{
			// Destruir o avião
		    DestroyDynamicObject(AirDropInfo[airdrop][AirDropId]);
		    DestroyDynamicObject(AirDropInfo[airdrop][AirDropParachute]);

			// Criar o loot
			new lootid = createLoot(AirDropInfo[airdrop][airX], AirDropInfo[airdrop][airY], AirDropInfo[airdrop][airZ], 25, LOOT_TYPE_AIRDROP, true, true, false, 0.0, MAX_ITENS_LOOT, AirDropInfo[airdrop][AirWorld]);

			SetLootItens(lootid, AirDropInfo[airdrop][AirType], 10 + random(15));
	        
	        // Resetar o airdrop
	        AirDropInfo[airdrop][AirDropValid] = 0;
		}
	}
	#if defined airdropOnDynamicObjectMoved
	    airdropOnDynamicObjectMoved(objectid);
 	#endif
	return 1;
}
#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved airdropOnDynamicObjectMoved
#if defined airdropOnDynamicObjectMoved
   	forward airdropOnDynamicObjectMoved(objectid);
#endif

CMD:airdrop(playerid) {

	if (PlayerData[playerid][dAdmin] < 10)
	    return 1;

	static
		Float:x,
		Float:y,
		Float:z;
		
	GetPlayerPos(playerid, x, y, z);
	
    CallAirDrop(x, y, GetPlayerVirtualWorld(playerid), LOOT_TYPE_MILITAR);
    
	return 1;
}









