
stock GetXYInFrontOfPoint(&Float:x, &Float:y, Float:angle, Float:distance) {
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}

stock AngleInRangeOfAngle(Float:a1, Float:a2, Float:range = 10.0)
{
	a1 -= a2;
	if((a1 < range) && (a1 > -range)) return true;
	return false;
}

stock static IsAngleInRangeOfAngle(Float:a1, Float:a2, Float:range = 10.0)
{
	a1 -= a2;
	if((a1 < range) && (a1 > -range)) return true;
	return false;
}

stock IsPlayerFacingPoint(playerid, Float:x, Float:y, Float:range = 10.0)
{
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);

	new Float:facing;
	GetPlayerFacingAngle(playerid, facing);

	new Float:angle;

	if( pos[1] > y ) angle = (-acos((pos[0] - x) / floatsqroot((pos[0] - x)*(pos[0] - x) + (pos[1] - y)*(pos[1] - y))) - 90.0);
	else if( pos[1] < y && pos[0] < x ) angle = (acos((pos[0] - x) / floatsqroot((pos[0] - x)*(pos[0] - x) + (pos[1] - y)*(pos[1] - y))) - 450.0);
	else if( pos[1] < y ) angle = (acos((pos[0] - x) / floatsqroot((pos[0] - x)*(pos[0] - x) + (pos[1] - y)*(pos[1] - y))) - 90.0);

	return (IsAngleInRangeOfAngle(-angle, facing, range));
}

stock IsPlayerFacingPlayer(playerid, targetid, Float:range =  10.0)
{
	new Float:pos[3];
	GetPlayerPos(targetid, pos[0], pos[1], pos[2]);

	if (!IsPlayerInRangeOfPoint(playerid, 1.5, pos[0], pos[1], pos[2]))
	    return 0;

	return IsPlayerFacingPoint(playerid, pos[0], pos[1], range);
}

stock IsPlayerBehindPlayer(playerid, targetid, Float:range = 60.0)
{
	new Float:angle[2];
	GetPlayerFacingAngle(playerid, angle[0]);
	GetPlayerFacingAngle(targetid, angle[1]);

	return (IsAngleInRangeOfAngle(angle[0], angle[1], range) && IsPlayerFacingPlayer(playerid, targetid, range));
}

stock IsPlayerAdminDuty(playerid) {
	if (PlayerData[playerid][dAdmin] < 1)
	    return 0;
	return PlayerData[playerid][dAdminDuty];
}

stock ShowPlayerMapIcons(playerid)
{
	// Areas militares
	SetPlayerMapIcon(playerid, 0, -1351.9661,503.6382,18.2344, 18, 0xFFFFFFFF); // Militar
	SetPlayerMapIcon(playerid, 1, 584.0128,879.2130,91.3939, 18, 0xFFFFFFFF); // Militar
	SetPlayerMapIcon(playerid, 2, 207.1160,1944.3729,17.6406, 18, 0xFFFFFFFF); // Militar
	// Cidade radioativa
	SetPlayerMapIcon(playerid, 3, -2145.9011,-2381.3916,30.6250, 43, 0xFFFFFFFF); // Radiacao
	// Dealers
	SetPlayerMapIcon(playerid, 4, 263.4087,21.5002,3.4332, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 5, -1532.9003,2656.6895,56.2814, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 6, -2244.8455,2382.1687,5.0710, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 7, -2552.3354,55.0987,16.4219, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 8, -2190.7952,-2327.4702,30.6250, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 9, -283.1528,-2174.6311,28.6641, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 10, 1470.7056,-1847.6110,13.5469, 23, 0xFFFFFFFF); // Vendedor
	SetPlayerMapIcon(playerid, 11, 223.1966,1931.4866,17.6406, 23, 0xFFFFFFFF); // Vendedor
}

stock RemovePlayerMapIcons(playerid)
{
	for(new id; id < 12; id++)
	{
	    RemovePlayerMapIcon(playerid, id);
	}
}

// By zSuYaNw
stock quote(color, text[])
{
	new
 		string[155],
        id[10],
        pos = 0
    ;

    format(string, 155, text);

    while( (pos = strfind(string, "@", true, (pos + 1))) != -1 )
	{
        static
      			i
         ;

        i = (pos + 1);

        for( ; ; )
        {
			if(
                (string[i] > 64 && string[i] < 90) ||
                (string[i] > 96 && string[i] < 123) ||
                (string[i] == 32 || string[i] == '\0'))
            {
            	break;
   			}
			++i;
		}

		strmid(id, string, pos+1, i);

		if( (id[0] ^ '\0' && id[0] ^ '\1'  && id[0] ^ ' ') && IsPlayerConnected(strval(id)) && !IsPlayerNPC(strval(id)))
  		{

			strdel(string, pos, i);

			static
   				_n[45]
       		;

			GetPlayerName(strval(id), _n, 24);
			format(_n, 45, "{%06x}@%s{%06x}", GetPlayerColor(strval(id)) >>> 8, _n, color >>> 8);

			strins(string, _n, pos, sizeof(string));

		}
	}
 	return string;
}


stock Float:absoluteangle(Float:angle)
{
	while(angle < 0.0)angle += 360.0;
	while(angle > 360.0)angle -= 360.0;
	return angle;
}

stock Float:GetPointAngleToPoint(Float:x1, Float:y1, Float:x2, Float:y2) {
    return 180.0 - atan2(x1 - x2, y1 - y2);
}

stock IsNumeric(const string[])
{
    new length = strlen(string);
    if(!length) return false;
    for(new i = 0; i < length; i++)
	{
        if(string[i] > '9' || string[i] <'0') return false;
    }
    return true;
}

stock IsPlayerLoggedIn(playerid)
	return PlayerData[playerid][dLogged];

stock IsPlayerAutomaticWeather(playerid)
	return PlayerData[playerid][dWeather];

stock playerActualSpeed(playerid)
{
	new Float:xPos[3];
	if (IsPlayerInAnyVehicle(playerid))
	{
		GetVehicleVelocity(GetPlayerVehicleID(playerid), xPos[0], xPos[1], xPos[2]);
	} else {
	    GetPlayerVelocity(playerid, xPos[0], xPos[1], xPos[2]);
	}
	return floatround(floatsqroot(xPos[0] * xPos[0] + xPos[1] * xPos[1] + xPos[2] * xPos[2]) * 135.00);
}

stock setZombieAngleToPlayer(npcid, playerid) {

	static
	    Float:zx, Float:zy, Float:zz,
	    Float:px, Float:py, Float:pz,
		Float:ang,
		Float:angz
		;

	FCNPC_GetPosition(npcid, zx, zy, zz);
	
	GetPlayerPos(playerid, px, py, pz);
	
	angz = FCNPC_GetAngle(npcid);
	
	zx -= (5.0 * floatsin(-angz, degrees));
	zy -= (5.0 * floatcos(-angz, degrees));
	
	ang = GetPointAngleToPoint(zx, zy, px, py);
	
	zx += (10.0 * floatsin(-ang, degrees));
	zy += (10.0 * floatcos(-ang, degrees));
	
	FCNPC_SetAngleToPos(npcid, zx, zy);
}

stock ResyncPlayer(playerid) {

	GetPlayerPos(playerid, PlayerData[playerid][dResyncPos][0], PlayerData[playerid][dResyncPos][1], PlayerData[playerid][dResyncPos][2]);
	GetPlayerFacingAngle(playerid, PlayerData[playerid][dResyncPos][3]);
	
	for(new weapon; weapon < 13; weapon++)
	{
	    GetPlayerWeaponData(playerid, weapon, PlayerData[playerid][dWeapons][weapon], PlayerData[playerid][dAmmo][weapon], PlayerData[playerid][dHealth][weapon]);
	}
	
	PlayerData[playerid][dResyncData][0] = GetPlayerInterior(playerid);
	PlayerData[playerid][dResyncData][1] = GetPlayerVirtualWorld(playerid);
	
	PlayerData[playerid][dResync] = true;
	
	SpawnPlayer(playerid);
}

stock GetPlayerCameraDynamicObject(playerid)
	return Streamer_GetItemStreamerID(playerid, STREAMER_TYPE_OBJECT, GetPlayerCameraTargetObject(playerid));

stock GetDynamicObjectModel(objectid)
	return Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_MODEL_ID);

stock ConvertPos(Float:x, Float:y, Float:z, &Float:rx, &Float:ry, &Float:rz) {

	// Pos x
	x += 3000.0;

	// Pos y
	y = y - ( 2 * y ) + 3000.0;

	rx = x;
	ry = y;
	rz = z;
}

stock LocationName(Float:px, Float:py, Float:pz = 0.0) {

	static Float:x;
	static Float:y;
	static Float:z;

	ConvertPos(px, py, pz, x, y, z);

	new location_letter = -1;
	new location_number = 0;
	new location_string[15];

	for(new Float:location_pos; location_pos < x; location_pos += 539.0000) {
	    location_letter++;
	}
	for(new Float:location_pos; location_pos < y; location_pos += 500.0000) {
	    location_number++;
	}

	format(location_string, sizeof location_string, "%c%d", 'A' + location_letter, location_number);
	return location_string;
}

stock returnPlayerPos(playerid) {

	static Float:px;
	static Float:py;
	static Float:pz;
	new string_return[15];

	GetPlayerPos(playerid, px, py, pz);
	format(string_return, sizeof (string_return), LocationName(px, py, pz));
	return string_return;
}

stock GetPlayerPosEx(playerid, &Float:x, &Float:y, &Float:z) {

	static Float:px;
	static Float:py;
	static Float:pz;

	GetPlayerPos(playerid, px, py, pz);

	ConvertPos(px, py, pz, x, y, z);
}


stock GetXYInFrontOfPlayer(playerid, &Float:x, &Float:y, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, x, y, a);
	GetPlayerFacingAngle(playerid, a);
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

callback destroyAirDropDynamicObj(objectid) {
	DestroyDynamicObject(objectid);
}

stock SetPlayerFaceToPoint(playerid, Float: X, Float: Y)
{
    static
        Float: pX,
        Float: pY,
        Float: oZ
    ;

    GetPlayerPos(playerid, pX, pY, oZ);

    oZ = ( floatadd(atan2(floatsub(Y, pY), floatsub(X, pX)), 270.0) );

    SetPlayerFacingAngle(playerid, oZ);
}

stock ConvertTime(number)
{
    new
		hours,
		mins,
		string[45];
		
    hours 	= floatround( number / 3600);
    mins 	= floatround( (number / 60) - (hours * 60) ) ;
    
    // Formatar a string
    format(string, 100, "%02d:%02d", hours, mins);
    
    // retornar a string
    return string;
}

stock ConvertTimeEx(number)
{
    new hours = 0, mins = 0, secs = 0, string[75];
    hours = floatround(number / 3600);
    mins = floatround((number / 60) - (hours * 60));
    secs = floatround(number - ((hours * 3600) + (mins * 60)));

	if(hours > 0)
    {
        format(string, 75, "%02d:%02d:%02d", hours, mins, secs);
    }
    else
    {
        format(string, 75, "%02d:%02d", mins, secs);
    }
    return string;
}

stock ConvertTimeSkin(number)
{
	new hours = 0, mins = 0, secs = 0, string[45];
	hours = floatround(number / 3600);
	mins = floatround((number / 60) - (hours * 60));
	secs = floatround(number - ((hours * 3600) + (mins * 60)));
	new days = 0;

	if(hours >= 24)
	{
		days = floatround((hours/24), floatround_floor);
		hours = hours % 24;
	}

	if(days > 0)
	{
		format(string, 45, "%d_day(s)_%02d:%02d:%02d", days, hours, mins, secs);
	}
	else if(hours > 0)
	{
		format(string, 45, "%02d:%02d:%02d", hours, mins, secs);
	}
	else
	{
		format(string, 45, "%02d:%02d", mins, secs);
	}
    return string;
}

stock ConvertTimeName(number)
{
    new hours = 0, mins = 0, secs = 0, string[75];
    hours = floatround(number / 3600);
    mins = floatround((number / 60) - (hours * 60));
    secs = floatround(number - ((hours * 3600) + (mins * 60)));

	if(hours > 0)
    {
        format(string, 75, "%02d horas, %02d minutos e %02d segundos", hours, mins, secs);
    }
 	else if(mins > 0)
    {
        format(string, 75, "%d minutos e %d segundos", mins, secs);
    }
    else
    {
        format(string, 75, "%d segundos", secs);
    }
    return string;
}

stock ConvertBanDate(number)
{
	new hours = 0, mins = 0, secs = 0, string[75];
	hours = floatround(number / 3600);
	mins = floatround((number / 60) - (hours * 60));
	secs = floatround(number - ((hours * 3600) + (mins * 60)));
	new days = 0;

	if(hours >= 24)
	{
		days = floatround((hours/24), floatround_floor);
		hours = hours % 24;
	}

	if(days > 0)
	{
		format(string, 75, "%d dia(s), %dh %dm e %ds", days, hours, mins, secs);
	}
	else if(hours > 0)
	{
		format(string, 75, "%dh %dm e %ds", hours, mins, secs);
	}
	else
	{
		format(string, 75, "%dm e %ds", mins, secs);
	}
	return string;
}

stock ConvertHour(number)
{
	new string[24];

	format(string, 25, "%dh", floatround(number / 3600));

	return string;
}

stock Play3DSound(audio_id, Float:x, Float:y, Float:z, Float:distance=25.0, world=0, soundid = 0) {

	foreach(new playerid : Player) {

		// Checar se está conectado ao audio plugin
		if(GetPlayerVirtualWorld(playerid) == world) {

			// Checar se está dentro da distancia
			if(IsPlayerInRangeOfPoint(playerid, distance + 5.0, x, y, z)) {

				if (Audio_IsClientConnected(playerid))
				{

					// Iniciar a tocar parada
					new handle = Audio_Play(playerid, audio_id, true);

					// Setar a posição 3d
					Audio_Set3DPosition(playerid, handle, x, y, z, 25.0);

					// Iniciar o audio
					Audio_Resume(playerid, handle);
				}
				else
				{
				    if (soundid > 0)
				    {
				        PlayerPlaySound(playerid, soundid, x, y, z);
				    }
				}
			}
		}
	}
}

stock GetNearest_Player(playerid, Float:distance)
{
	static Float:xX, Float:yY, Float:zZ, retElement, Float:odist;
	
	retElement = -1;

	foreach(new i : Player)
    {
    	if((i == playerid)) continue;
    	
        GetPlayerPos(i, xX, yY, zZ);
        
        odist = GetPlayerDistanceFromPoint(playerid, xX, yY, zZ);
        
        if (retElement == -1)
        {
            retElement = i;
            distance = odist;
        }
        else if (odist < distance)
        {
            retElement = i;
            distance = odist;
        }
    }
    return retElement;
}

stock GetClosestPlayerAdmin(playerid, Float:maxdist = 999999.0) {

	new player = INVALID_PLAYER_ID;
	new Float:dist = maxdist;

	for(new x; x < MAX_PLAYERS; x++) {

		if (!IsPlayerConnected(x))
		    continue;

		if (x == playerid)
			continue;

		if (GetPlayerState(x) == PLAYER_STATE_SPECTATING)
		    continue;

	    static Float:pos[4];
	    GetPlayerPos(x, pos[0], pos[1], pos[2]);
	    if ( (pos[3] = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]) ) < dist)
		{
	        player = x;
	        dist = pos[3];
	    }
	}

	return player;
}

stock GetClosestPlayer(playerid, Float:maxdist = 999999.0) {

	new player = INVALID_PLAYER_ID;
	new Float:dist = maxdist;

	foreach(new x : Player) {

		if (x == playerid)
			continue;
			
		if (GetPlayerState(x) == PLAYER_STATE_SPECTATING)
		    continue;

	    static Float:pos[4];
	    GetPlayerPos(x, pos[0], pos[1], pos[2]);
	    if ( (pos[3] = GetPlayerDistanceFromPoint(playerid, pos[0], pos[1], pos[2]) ) < dist)
		{
	        player = x;
	        dist = pos[3];
	    }
	}

	return player;
}

stock z_GetClosestPlayer(npcid, &Float:distance = 0.0) {

	new player = INVALID_PLAYER_ID;
	new Float:dist = 99999.00;
	new Float:x, Float:y, Float:z, Float:pos;
	FCNPC_GetPosition(npcid, x, y, z);

	foreach(new playerid : Player) {

		if (GetPlayerVirtualWorld(playerid) != 0 || GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		    continue;
		    
		if (IsPlayerInAnyVehicle(playerid))
		    continue;

	    if ( (pos = GetPlayerDistanceFromPoint(playerid, x, y, z) ) < dist)
		{
	        player = playerid;
	        dist = pos;
	    }
	}
	distance = dist;

	return player;
}

stock RemovePlayerWeapon(playerid, weaponid)
{
	new plyWeapons[13] = 0;
	new plyAmmo[13] = 0;
	for(new sslot = 0; sslot != 13; sslot++)
	{
		new wep, ammo;
		GetPlayerWeaponData(playerid, sslot, wep, ammo);
		if(wep != weaponid) {
			GetPlayerWeaponData(playerid, sslot, plyWeapons[sslot], plyAmmo[sslot]);
		}
	}
	
	ResetPlayerWeapons(playerid);
	
	for(new sslot = 0; sslot != 13; sslot++) {
		if(plyWeapons[sslot] > 0) {
			GivePlayerWeapon(playerid, plyWeapons[sslot], plyAmmo[sslot]);
		}
	}
	return 1;
}

/*
stock getNome(playerid) {

	new playerNome[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerNome, sizeof (playerNome));
	return playerNome;
}*/

stock getId(name[]) {

	foreach(new playerid : Player) {
	
	    if (!strcmp(getNome(playerid), name)) {
	        return playerid;
	    }
	}
	return INVALID_PLAYER_ID;
}

stock getIp(playerid) {

	static playerIp[32];
	GetPlayerIp(playerid, playerIp, sizeof (playerIp));
	return playerIp;
}

stock getWorldTime() {

	static server_time;
	static server_hour;
	static server_minute;
	static server_second;

	gettime(server_hour, server_minute, server_second);

    server_hour ++;

	if (server_hour > 23)
	    server_hour = 0;

	switch (server_hour) {

	    case 00..05: server_time = 00;
	    case 06..08: server_time = 06;
	    case 09..11: server_time = 11;
	    case 12..15: server_time = 12;
	    case 16..17: server_time = 17;
	    case 18..19: server_time = 23;
	    case 20: 	 server_time = 23;
	    case 21: 	 server_time = 00;
	    case 22..23: server_time = 01;
	}
	return server_time;
}

stock sendLocalMessage(playerid, message[], Float:range=30.0, color=0xFFFFFFFF) {

	static Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	foreach(new xplayer : Player) {
	
	    if (IsPlayerInRangeOfPoint(xplayer, range, x, y, z) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(xplayer)) {
			SendClientMessage(xplayer, color, message);
		}
	}
}

stock SendMessageInRange(message[], color, Float:x, Float:y, Float:z, Float:range=30.0, world = 0) {

	foreach(new xplayer : Player) {

	    if (IsPlayerInRangeOfPoint(xplayer, range, x, y, z) && world == GetPlayerVirtualWorld(xplayer)) {
			SendClientMessage(xplayer, color, message);
		}
	}
}

stock CreateRayExplosion(Float:X, Float:Y, Float:Z, numrays, Float:maxdist, Float:vZ, Float:polygon[][3])
{
	new collisions = 0;

	for(new i = 0; i < numrays; i ++)
	{
	    new Float:a = (360.0 / numrays) * i, Float:cPos[3];

	    if(CA_RayCastLine(X, Y, Z, X + (maxdist * floatsin(-a, degrees)), Y + (maxdist * floatcos(-a, degrees)), Z + (maxdist * vZ), cPos[0], cPos[1], cPos[2]))
	    {
	        polygon[i] = cPos;
	        collisions ++;
	    }
	    else
	    {
	        polygon[i][0] = -30000.0;
	        polygon[i][1] = -30000.0;
	        polygon[i][2] = -30000.0;
	    }
	}

	return collisions;
}

new const weapon_slot[] = {
	0,
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	10, // 10
	10,
	10,
	10,
	10,
	10,
	8,
	8,
	8,
	0,
	0, // 20
	0,
	2,
	2,
	2,
	3,
	3,
	3,
	4,
	4,
	5, // 30
	5,
	4,
	6,
	6,
	7,
	7,
	7,
	7,
	8,
	12, // 40
	9,
	9,
	9,
	11,
	11,
	11
};

stock GetWeaponSlot(weaponid)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;
	    
	return weapon_slot[weaponid];
}

/*
stock GetWeaponSlot(weaponid)
{
	new slot;
	switch(weaponid)
	{
		case 0,1: slot = 0;
		case 2 .. 9: slot = 1;
		case 10 .. 15: slot = 10;
		case 16 .. 18, 39: slot = 8;
		case 22 .. 24: slot =2;
		case 25 .. 27: slot = 3;
		case 28, 29, 32: slot = 4;
		case 30, 31: slot = 5;
		case 33, 34: slot = 6;
		case 35 .. 38: slot = 7;
		case 40: slot = 12;
		case 41 .. 43: slot = 9;
		case 44 .. 46: slot = 11;
		default: slot = 0;
	}
	return slot;
}*/

static const stock s_WeaponsPoints[] = {
	6, // 0 - Fist
	12, // 1 - Brass knuckles
	15, // 2 - Golf club
	12, // 3 - Nitestick
	22, // 4 - Knife
	19, // 5 - Bat
	12, // 6 - Shovel
	11, // 7 - Pool cue
	19, // 8 - Katana
	2, // 9 - Chainsaw
	1, // 10 - Dildo
	1, // 11 - Taser
	1, // 12 - Vibrator
	1, // 13 - Vibrator 2
	1, // 14 - Flowers
	9, // 15 - Cane
	82, // 16 - Grenade
	9, // 17 - Teargas
	1, // 18 - Molotov
	10, // 19 - Vehicle M4 (custom)
	20, // 20 - Vehicle minigun (custom)
	1, // 21
	25, // 22 - Colt 45
	21, // 23 - Silenced
	39, // 24 - Deagle
	29, // 25 - Shotgun
	19, // 26 - Sawed-off
	38, // 27 - Spas
	23, // 28 - UZI
	20, // 29 - MP5
	29, // 30 - AK47
	29, // 31 - M4
	17, // 32 - Tec9
	49, // 33 - Cuntgun
	63, // 34 - Sniper
	82, // 35 - Rocket launcher
	82, // 36 - Heatseeker
	1, // 37 - Flamethrower
	0, // 38 - Minigun
	82, // 39 - Satchel
	6, // 40 - Detonator
	6, // 41 - Spraycan
	0, // 42 - Fire extinguisher
	6, // 43 - Camera
	6, // 44 - Night vision
	6, // 45 - Infrared
	6, // 46 - Parachute
	6, // 47 - Fake pistol
	2, // 48 - Pistol whip (custom)
	10, // 49 - Vehicle
	330, // 50 - Helicopter blades
	82, // 51 - Explosion
	1, // 52 - Car park (custom)
	1, // 53 - Drowning
	165  // 54 - Splat
};

stock getWeaponPoints(weaponid) {

	if (weaponid < 0 || weaponid >= sizeof (s_WeaponsPoints)) {
	    return 0;
	}

	return s_WeaponsPoints[weaponid];
}

stock Float:getWeaponZDamage(weaponid) {

	if (weaponid < 0 || weaponid >= sizeof (s_WeaponsPoints)) {
	    return 0.0;
	}

	return float(s_WeaponsPoints[weaponid]);
}

stock fireWeapons(weaponid) {

	switch(weaponid) {
	    case 22..34, 38: return 1;
	}
	return 0;
}

stock Float:convertDamage(Float:damage, bodypart) {

	new Float:newdamage;

	switch(bodypart) {

	    // Barriga
	    case 3: {newdamage = damage + 0.0;}

	    // Peito
	    case 4: {newdamage = damage * 1.40;}

	    // Braços
	    case 5: {newdamage = damage / 1.10;}
	    case 6: {newdamage = damage / 1.10;}

	    // Pernas
	    case 7: {newdamage = damage / 1.85;}
	    case 8: {newdamage = damage / 1.85;}

	    // Cabeça
	    case 9: {newdamage = damage * 1.90;}
	}

	return newdamage;
}

stock CreateExplosionEx(Float:x, Float:y, Float:z, type, Float:radius, world = 0)
{
	foreach(new playerid : Player)
	{
	    if (GetPlayerVirtualWorld(playerid) == world)
	    {
	    	CreateExplosionForPlayer(playerid, x, y, z, type, radius);
		}
	}
}

/*
callback GetClosestPlayer(p1)
{
    new x,Float:dis,Float:dis2,player;
    player = -1;
    dis = 99999.99;
    foreach(new x : Player) {

		if(x != p1) {

			dis2 = GetDistanceBetweenPlayers(x,p1);

			if(dis2 < dis && dis2 != -1.00) {
         		dis = dis2;
           		player = x;
            }
        }
    }
    return player;
}*/

Float:GetPointDistanceToPoint(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2)
{
	new Float:x, Float:y, Float:z;
 	x = x1-x2;
  	y = y1-y2;
  	z = z1-z2;
  	return floatsqroot(x*x+y*y+z*z);
}

stock IsPlayerInRangeOfXY(playerid, Float:x1, Float:y1, Float:range)
{
	static
		Float:x,
		Float:y,
		Float:z
	;
	GetPlayerPos(playerid, x, y, z);

	x = x1 - x;
  	y = y1 - y;

  	if (floatsqroot( x * x + y * y ) >= range) return 1;
		
  	return 0;
}

stock Float:GetDistanceBetweenPlayers(p1,p2)
{
    static
        Float:x,
        Float:y,
        Float:z;
        
	GetPlayerPos(p1, x, y, z);
        
    return GetPlayerDistanceFromPoint(p2, x, y, z);
}

callback Float:z_GetDistanceBetweenPlayers(zombie, playerid)
{
    static Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
    if(!IsPlayerConnected(playerid)) {
        return -1.00;
    }
    FCNPC_GetPosition(zombie, x1, y1, z1);
    GetPlayerPos(playerid, x2, y2, z2);
    return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

callback Float:GetHealthPlayer(playerid) {

	new Float:health;
	GetPlayerHealth(playerid, health);
	return health;
}

static stock DoencasNames[][75] = {

	{"Nenhuma"},
	{"Perna quebrada"},
	{"Hemorragia interna"}
};

stock getDoencaName(id) {

	return DoencasNames[id];
}

stock IsMaleSkin(skinid)
{
	switch (skinid)
 	{
        case 0,1,4,5,6,7,8,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,36,
		37,42,43,44,45,46,49,32,33,34,35,2,47,48,50,51,52,57,59,58,60,67,70,71,78,
		79,84,86,94,96,97,98,99,62,68,72,73,80,81,82,83,95,100,101,102,103,104,
		105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,
		123,124,125,126,127,128,132,133,134,135,136,137,142,143,144,146,147,149,153,
        154,155,156,158,159,160,161,162,163,164,165,166,167,168,170,171,172,173,
		174,175,176,177,178,179,181,182,183,184,185,186,187,188,200,265,180,189,
		202,203,204,206,208,258,209,210,212,213,217,220,221,222,223,227,228,229,
		230,234,235,236,240,241,242,247,248,249,250,252,254,261,262,264,266,267,
		268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,
		286,287,288,289,290,291,292,294,299,259,260,293,295,296,297,61,255,253: {
			return 1;
		}
  	}
	return 0;
}
static stock const g_WeaponName[57][21] = {
	{"Punho"          	}, {"Soqueira"		}, {"Golf club"           },
	{"Nightstick"       }, {"Faca"          }, {"Marreta"             },
	{"Pa"               }, {"Taco"          }, {"Facao"               },
	{"Motosserra"       }, {"Purple dildo"  }, {"Taser"               },
	{"Vibrator"         }, {"Vibrator"      }, {"Flowers"             },
	{"Cano"             }, {"Granada"       }, {"Granada de fumaca"   },
	{"Coquetel Molotov" }, {"Vehicle gun"   }, {"Vehicle gun"         },
	{"N/A"              }, {"9mm"       	}, {"Silenciadora"     	  },
	{"Desert Eagle"     }, {"Calibre 12"    }, {"Sawn shotgun"    	  },
	{"Combat shotgun"   }, {"Mac-10"        }, {"MP5"                 },
	{"AK-47"            }, {"M4A1"          }, {"Tec-9"               },
	{"Espingarda"       }, {"Sniper"        }, {"Rocket launcher"     },
	{"Heat seeking RPG" }, {"Fogo"  		}, {"Minigun"             },
	{"Satchel"          }, {"Detonator"     }, {"Lata de Spray"       },
	{"Fire extinguisher"}, {"Binoculos"     }, {"Visao Noturna"		  },
	{"Visao Termica"    }, {"Parachute"     }, {"Fake pistol"         },
	{"Pistol whip"      }, {"Vehicle"       }, {"Helicopter blades"   },
	{"Explosion"        }, {"Car parking"   }, {"Drowning"            },
	{"Collision"        }, {"Splat"         }, {"Unknown"             }
};

stock NomeArma(weaponid)
{
	new weapname[35];
	if (weaponid < 0 || weaponid >= sizeof (g_WeaponName)) {
	    strcat(weapname, "Nenhuma");
	    return weapname;
	}
	strcat(weapname, g_WeaponName[weaponid]);
    return weapname;
}

static const s_AnimationLibraries[][] = {
        !"AIRPORT",    !"ATTRACTORS",   !"BAR",                 !"BASEBALL",
        !"BD_FIRE",    !"BEACH",            !"BENCHPRESS",  !"BF_INJECTION",
        !"BIKED",          !"BIKEH",        !"BIKELEAP",        !"BIKES",
        !"BIKEV",          !"BIKE_DBZ",     !"BMX",             !"BOMBER",
        !"BOX",            !"BSKTBALL",     !"BUDDY",           !"BUS",
        !"CAMERA",         !"CAR",          !"CARRY",           !"CAR_CHAT",
        !"CASINO",         !"CHAINSAW",     !"CHOPPA",          !"CLOTHES",
        !"COACH",          !"COLT45",       !"COP_AMBIENT", !"COP_DVBYZ",
        !"CRACK",          !"CRIB",         !"DAM_JUMP",         !"DANCING",
        !"DEALER",         !"DILDO",        !"DODGE",            !"DOZER",
        !"DRIVEBYS",   !"FAT",          !"FIGHT_B",      !"FIGHT_C",
        !"FIGHT_D",    !"FIGHT_E",      !"FINALE",               !"FINALE2",
        !"FLAME",      !"FLOWERS",      !"FOOD",                 !"FREEWEIGHTS",
        !"GANGS",      !"GHANDS",       !"GHETTO_DB",    !"GOGGLES",
        !"GRAFFITI",   !"GRAVEYARD",    !"GRENADE",      !"GYMNASIUM",
        !"HAIRCUTS",   !"HEIST9",       !"INT_HOUSE",    !"INT_OFFICE",
        !"INT_SHOP",   !"JST_BUISNESS", !"KART",                 !"KISSING",
        !"KNIFE",      !"LAPDAN1",              !"LAPDAN2",      !"LAPDAN3",
        !"LOWRIDER",   !"MD_CHASE",     !"MD_END",               !"MEDIC",
        !"MISC",       !"MTB",                  !"MUSCULAR",     !"NEVADA",
        !"ON_LOOKERS", !"OTB",                  !"PARACHUTE",    !"PARK",
        !"PAULNMAC",   !"PED",                  !"PLAYER_DVBYS", !"PLAYIDLES",
        !"POLICE",     !"POOL",                 !"POOR",                 !"PYTHON",
        !"QUAD",       !"QUAD_DBZ",     !"RAPPING",      !"RIFLE",
        !"RIOT",       !"ROB_BANK",     !"ROCKET",               !"RUSTLER",
        !"RYDER",      !"SCRATCHING",   !"SHAMAL",               !"SHOP",
        !"SHOTGUN",    !"SILENCED",     !"SKATE",                !"SMOKING",
        !"SNIPER",     !"SPRAYCAN",     !"STRIP",                !"SUNBATHE",
        !"SWAT",       !"SWEET",                !"SWIM",                 !"SWORD",
        !"TANK",       !"TATTOOS",              !"TEC",                  !"TRAIN",
        !"TRUCK",      !"UZI",                  !"VAN",                  !"VENDING",
        !"VORTEX",     !"WAYFARER",     !"WEAPONS",      !"WUZI",
        !"WOP",        !"GFUNK",                !"RUNNINGMAN"
};

stock PreloadActorAnimations(playerid) {
	for(new i = 0; i < sizeof(s_AnimationLibraries); i ++) {
		ApplyAnimation(playerid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
  	}
}

stock GetPlayerExplosivePos(playerid, &Float:x, &Float:y, &Float:z, &Float:rx, &Float:ry, &Float:rz) {
	// get a player position
	new Float:px, Float:py, Float:pz, Float:pa;

	GetPlayerPos(playerid, px, py, pz);
	GetPlayerFacingAngle(playerid, pa);

	// detect wall in front of player
	if (CA_RayCastLineNormal(px, py, pz, px + (1.5 * floatsin(-pa, degrees)), py + (1.5 * floatcos(-pa, degrees)), pz, x, y, z, rx, ry, rz)) {

		rx = 0.0;
		ry = 0.0;
		rz = pa;

	    return 1;
	}

	GetXYInFrontOfPoint(px, py, pa, 1.5);
	CA_RayCastLine(px, py, pz, px, py, pz - 200.0, x, y, z);

	rx = -90;
	ry = 0.0;
	rz = 0.0;

	z += 0.2;

	return 1;
}

enum skinEnum {

	skinId,
	skinName[35],
}

static stock SkinNames[][skinEnum] = {

	{261, "Roupa de homem comum"},
	{285, "Uniforme S.W.A.T."},
	{287, "Uniforme Exercito"},
	{209, "Roupa Oriental"},
	{248, "Roupa Motoqueiro"},
	{233, "Roupa de mulher comum"},
	{158, "Roupa de Fazendeiro"},
	{157, "Roupa de Fazendeira"},
	{283, "Roupa de Xerife"},
	{306, "Uniforme Policial feminina"},
	{309, "Uniforme Policial feminina"}
};

stock GetSkinName(skinid) {

	new skinname[35] = "Roupa comum";
	
	for(new skin; skin != sizeof SkinNames; skin++) {
	
	    if (skinid == SkinNames[skin][skinId]) {
	        format(skinname, sizeof skinname, SkinNames[skin][skinName]);
	    }
	}
	
	return skinname;
}

enum cargosEnum {

	levelAdm,
	cargoAdm[24],
}

static stock admCargosNames[][cargosEnum] = {

	{1, "Ajudante"},
	{2, "Supervisor"},
	{3, "Moderador"},
	{4, "Sub-Gerente"},
	{5, "Gerente"},
	{6, "Vice-diretor(a)"},
	{7, "Diretor"},
	{10, "Owner"}
};

stock getAdminCargoName(level) {

	new cargoname[35] = "Nenhum";

	for(new cargo; cargo != sizeof admCargosNames; cargo++) {

	    if (level == admCargosNames[cargo][levelAdm]) {
	        format(cargoname, sizeof cargoname, admCargosNames[cargo][cargoAdm]);
	    }
	}

	return cargoname;
}

stock getPlayerTag(playerid) {
	new tagname[75];
	

	if (PlayerData[playerid][dAdmin] == 10) {
	    strcat(tagname, "{00AA00}@Owner");
	}
	/*
	else if (PlayerData[playerid][dAdmin]) {
	    strcat(tagname, "{00DDFF}@Admin");
	}*/
	else if (PlayerData[playerid][dBetaTester]) {
	    strcat(tagname, "{00EEFF}@Beta-Tester");
	}
	else if (IsPlayerPremium(playerid)) {
	    strcat(tagname, "{FFEE00}@Premium");
	} else {
	    strcat(tagname, "{BBBBBB}@Sobrevivente");
	}
	return tagname;
}

stock GetDirectionName(playerid) {

	static Float:angle;

	GetPlayerFacingAngle(playerid, angle);

	if ( IsPlayerInAnyVehicle(playerid) ) {

	    GetVehicleZAngle(GetPlayerVehicleID(playerid), angle);
	}

	angle = 360.0 - angle;

	new directionName[4];

	if		(angle > 350.0 || angle < 10.0)		{ directionName = "N";   }
	else if (angle >= 10.0 && angle < 30.0)		{ directionName = "NNE"; }
	else if (angle >= 30.0 && angle < 60.0)		{ directionName = "NE";  }
	else if (angle >= 60.0 && angle < 80.0)		{ directionName = "ENE"; }
	else if (angle >= 80.0 && angle < 100.0)	{ directionName = "E";   }
	else if (angle >= 100.0 && angle < 120.0)	{ directionName = "ESE"; }
	else if (angle >= 120.0 && angle < 150.0)	{ directionName = "SE";  }
	else if (angle >= 150.0 && angle < 170.0)	{ directionName = "SSE"; }
	else if (angle >= 170.0 && angle < 190.0)	{ directionName = "S";   }
	else if (angle >= 190.0 && angle < 220.0)	{ directionName = "SSW"; }
	else if (angle >= 220.0 && angle < 240.0)	{ directionName = "SW";  }
	else if (angle >= 240.0 && angle < 260.0)	{ directionName = "WSW"; }
	else if (angle >= 260.0 && angle < 280.0)	{ directionName = "W";   }
	else if (angle >= 280.0 && angle < 300.0)	{ directionName = "WNW"; }
	else if (angle >= 300.0 && angle < 330.0)	{ directionName = "NW";  }
	else if (angle >= 330.0 && angle < 350.0)	{ directionName = "NNW"; }

	return directionName;
}

stock const GetWeaponAttachSlotId[47] = {
	1,//0
	1,//1
	1,//2
	1,//3
	1,//4
	1,//5
	1,//6
	1,//7
	1,//8
	1,//9
	1,//10
	1,//11
	1,//12
	1,//13
	1,//14
	1,//15
	1,//16
	1,//17
	1,//18
	1,//19
	1,//20
	1,//21
	2,//22
	2,//23
	2,//24
	3,//25
	2,//26
	3,//27
	2,//28
	3,//29
	3,//30
	3,//31
	2,//32
	3,//33
	3,//34
	3,//35
	3,//36
	3,//37
	3,//38
	1,//39
	1,//40
	1,//41
	1,//42
	1,//43
	1,//44
	1,//45
	1 //46
};

/*
stock GetWeaponAttachSlotId(weaponid) {

	switch(weaponid) {

	    case 0  .. 21, 41, 42, 43, 44, 45:
			return 1;
	    case 22 .. 24:
			return 2;
	    case 25 .. 38:
			return 3;
	}

	return 1;
}*/

stock GetWeaponType(weaponid) {

	switch(weaponid) {
	
	    case 0  .. 21, 41, 42, 43, 44, 45:
			return WEAPON_TYPE_PRIMARY;
	    case 22 .. 24:
			return WEAPON_TYPE_SECONDARY;
	    case 25 .. 38:
			return WEAPON_TYPE_TERTIARY;
	}

	return 1;
}

stock GetPlayerWeaponByType(playerid, type, &weaponid, &ammo) {

	for(new slot; slot != 13; slot++) {
	
	    new slot__weaponid, slot__ammo;
	    GetPlayerWeaponData(playerid, slot, slot__weaponid, slot__ammo);
	    
	    if (slot__weaponid && GetWeaponType(slot__weaponid) == type) {
	    
	        weaponid = slot__weaponid;
	        ammo = slot__ammo;
	        break;
	    }
	}
	return 1;
}

stock getMoneyFormat(amount){//by OTACON

	new
 		value[35]
 	;

    format(value, sizeof (value), "%d", amount);

    switch(strlen(value)){
        case 4:{//Mil
			strins(value,".", 1);
		}
        case 5:{//Dez Mil
			strins(value,".", 2);
		}
        case 6:{//Cem Mil
			strins(value,".", 3);
		}
        case 7:{//Um Milhão
			strins(value,".", 1);
			strins(value,".", 5);
		}
        case 8:{//Dez Milhoes
			strins(value,".", 2);
			strins(value,".", 6);
		}
        case 9:{//Cem Milhoes
			strins(value,".", 3);
			strins(value,".", 7);
		}
        case 10:{//Cem Milhoes
			strins(value,".", 1);
			strins(value,".", 5);
			strins(value,".", 9);
		}
    }

    if (amount < 0) {
    	format(value, sizeof (value), "%d", amount);
    }

    return value;
}

stock getPlayerOnfootSpeed(playerid) {

	static
		Float:velx,
		Float:vely,
		Float:velz;
	
	GetPlayerVelocity(playerid, velx, vely, velz);
	
	return floatround(floatsqroot(velx*velx+vely*vely+velz*velz) * 135.00);
}

static serverWeaponModels[47] = {
	331,331,333,334,335,/*Marreta*/19631,337,338,/*facão*/-1023,341,321,/*Taser*/18642,323,324,325,326,342,343,344,
	999,999,999,346,347,348,349,350,351,352,353,355,356,372,357,358,359,360,361,362,
	363,364,365,366,367,368,368,371
};

stock getWeaponObjectModel(weaponid) {

	if (weaponid < 0 || weaponid > 46) {
		return 0;
	}

	return serverWeaponModels[weaponid];
}

stock HidePlayerDialog(playerid)
	return ShowPlayerDialog(playerid, -1, 0, " ", "invalid", "invalid", "");

stock sendMessageToAdmins(message[], color) {

	foreach(new playerid : Player) {

	    if (PlayerData[playerid][dAdmin] || IsPlayerAdmin(playerid)) SendClientMessage(playerid, color, message);
	}
}

stock const AutomaticWeathers[] = {
	0,
	1,
	2,
	3,
	4,
	5,
	8,
	10,
	14,
	15
};

stock const Female_HitSound[5] = {
	53,
	54,
	55,
	56,
	57
};

stock const Male_HitSound[5] = {
	58,
	59,
	60,
	61,
	62
};

stock ApplyPlayerSoundHit(playerid)
{
	if (gettime() < GetPVarInt(playerid, "p_hitsound"))
	    return 0;

	new
	    p_skinid = GetPlayerSkin(playerid);

	if (IsMaleSkin(p_skinid))
	{
	    Audio_Play(playerid, Male_HitSound[random(sizeof Male_HitSound)]);
	}
	else
	{
	    Audio_Play(playerid, Female_HitSound[random(sizeof Female_HitSound)]);
	}
	
	SetPVarInt(playerid, "p_hitsound", gettime() + 1);
	return 1;
}

stock SubDel(string[],sub_string[])//by Sreyas
{
    new i,
        j,
        beg = -1,
        bool:flag;
    while( string[ i ] != '\0' )
    {
        j = 0;
        flag = true;

        if( sub_string[ 0 ] == string[ i ] )
        {
            beg = i;
            while( sub_string[ j ] != '\0' && string[ i ] != '\0' )
            {
                if( sub_string[ j ] != string[ i ] )
                    flag = false;
                i++;
                j++;
            }
            if(flag)
            {
                for( j = i,i = beg ; string[ i ] != '\0'; i++ , j++ )
                    string[ i ] = string[ j ];
                i= -1 ;
            }
        }
        i++;
    }
}

stock createPlayerBloodText(playerid)
{
	if (gettime() < GetPVarInt(playerid, "lastTextBlood"))
	    return 0;
	    
	SetPVarInt(playerid, "lastTextBlood", gettime() + 1);

	new PlayerText:textPlayerBlood1;
	new PlayerText:textPlayerBlood2;
	new Float:textPlayerBloodPosX = 20 + random(450);
	new Float:textPlayerBloodPosY = 65 + random(210);

	textPlayerBlood1 = CreatePlayerTextDraw(playerid, textPlayerBloodPosX, textPlayerBloodPosY, "particle:bloodpool_64");
	PlayerTextDrawBackgroundColor(playerid,textPlayerBlood1, 255);
	PlayerTextDrawFont(playerid,textPlayerBlood1, 4);
	PlayerTextDrawLetterSize(playerid,textPlayerBlood1, 0.400000, 1.000000);
	PlayerTextDrawColor(playerid,textPlayerBlood1, -16777066);
	PlayerTextDrawSetOutline(playerid,textPlayerBlood1, 0);
	PlayerTextDrawSetProportional(playerid,textPlayerBlood1, 1);
	PlayerTextDrawSetShadow(playerid,textPlayerBlood1, 1);
	PlayerTextDrawUseBox(playerid,textPlayerBlood1, 1);
	PlayerTextDrawBoxColor(playerid,textPlayerBlood1, 255);
	PlayerTextDrawTextSize(playerid,textPlayerBlood1, 71.000000, 100.000000);

	textPlayerBlood2 = CreatePlayerTextDraw(playerid, (textPlayerBloodPosX + 55) - random(150), textPlayerBloodPosY + 160, "particle:bloodpool_64");
	PlayerTextDrawBackgroundColor(playerid,textPlayerBlood2, 255);
	PlayerTextDrawFont(playerid,textPlayerBlood2, 4);
	PlayerTextDrawLetterSize(playerid,textPlayerBlood2, 0.400000, 0.000000);
	PlayerTextDrawColor(playerid,textPlayerBlood2, -16777066);
	PlayerTextDrawSetOutline(playerid,textPlayerBlood2, 0);
	PlayerTextDrawSetProportional(playerid,textPlayerBlood2, 1);
	PlayerTextDrawSetShadow(playerid,textPlayerBlood2, 1);
	PlayerTextDrawUseBox(playerid,textPlayerBlood2, 1);
	PlayerTextDrawBoxColor(playerid,textPlayerBlood2, 255);
	PlayerTextDrawTextSize(playerid,textPlayerBlood2, 51.000000, -60.000000);

	PlayerTextDrawShow(playerid, textPlayerBlood1);
	PlayerTextDrawShow(playerid, textPlayerBlood2);

	SetTimerEx("destroyBloodText", 1500, false, "ddd", playerid, _:textPlayerBlood1, _:textPlayerBlood2);
	
	return 1;
}

forward destroyBloodText(playerid, text1, text2);
public destroyBloodText(playerid, text1, text2)
{
	PlayerTextDrawDestroy(playerid, PlayerText:text1);
	PlayerTextDrawDestroy(playerid, PlayerText:text2);
}

static const serverAutomaticMessages[][7] = {
	{ "SMSG0" },
	{ "SMSG1" },
	{ "SMSG2" },
	{ "SMSG3" },
	{ "SMSG4" },
	{ "SMSG5" },
	{ "SMSG6" },
	{ "SMSG7" },
	{ "SMSG8" },
	{ "SMSG9" }
};

stock sendServerAutomaticMessage()
{
	new rdon = random(sizeof serverAutomaticMessages);
	SendLanguageMessageToAll(0x0099FFFF, serverAutomaticMessages[rdon]);
}


stock ShowPlayerBaseProtectDialog(playerid)
{
    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF5555}Esta base está protegida contra você:",
		"{FF5555}MOTIVOS POSSÍVEIS:{AAAAAA}\n\
		- Você logou próximo a uma base que não possui permissão\n\
		- Nosso anticheat detectou que você usa programas ilegais\n\
		- Você está com perda de pacotes (RT)\n\n\
		{FF5555}O QUE FOI BLOQUEADO:{AAAAAA}\n\
	    - Você não pode usar o armário\n\
		- Você não pode usar os baús e explosivos\n\
		- Você não pode editar a base\n\n\
		{FF5555}COMO RESOLVER:{AAAAAA}\n\
		• Saia da área da base e volte\n\
		• Chame um admin caso persistir",
		"Ok", "");
}




