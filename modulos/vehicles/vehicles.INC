#include "../modulos/vehicles/core.inc"
#include "../modulos/vehicles/vspawns.inc"
//#include "../modulos/vehicles/utils.inc"

callback SaveServerVehicles() {
	for(new vehicleid = 1; vehicleid != sizeof (VehiclesPosInfo); vehicleid++) {
	    SaveVehicleInfo(vehicleid);
	}
}

callback SaveVehicleInfo(vehicleid) {

	if (!IsValidVehicle(vehicleid) || GetVehicleVirtualWorld(vehicleid) == 5001)
	    return 0;

	// variaveis
	new file[75], string[128];
	
	// arquivo
	format(file, sizeof (file), pastaVehicles, vehicleid);
	
	// Guardar infos
	new File: hand = fopen(file, io_write);
	
	if (hand) {
	
	    new Float:x, Float:y, Float:z, Float:a, Float:hea, panels, doors, lights, tires;
	    
	    GetVehiclePos(vehicleid, x, y, z);
	    GetVehicleZAngle(vehicleid, a);
	    GetVehicleHealth(vehicleid, hea);
	    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	    
	    format(string, sizeof (string), "%d,%f,%f,%f,%f,%f,%d,%f,%d,%d,%d,%d,%d,%d\r\n",
		GetVehicleModel(vehicleid), x, y, z, a, hea, VehicleInfo[vehicleid][vehFuel], VehicleInfo[vehicleid][vehBatery],
		VehicleInfo[vehicleid][vehColor1], VehicleInfo[vehicleid][vehColor2], VehicleInfo[vehicleid][vehUniqueId],
		VehicleInfo[vehicleid][vehTickRespawn], VehicleInfo[vehicleid][vehKeyId], VehicleInfo[vehicleid][vehLocked]);
	    fwrite(hand, string);
	    format(string, sizeof (string), "%d,%d,%d,%d\r\n", panels, doors, lights, tires);
	    fwrite(hand, string);
	    
	    new lootid = VehicleInfo[vehicleid][vehLoot];
	    
		for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {
			
		    format(string, sizeof (string), "%d,%s,%d,%d,%d\r\n",
			LootItensInfo[lootid][itens][item_valid], LootItensInfo[lootid][itens][item_nome],
			LootItensInfo[lootid][itens][item_type], LootItensInfo[lootid][itens][item_model],
			LootItensInfo[lootid][itens][item_quantia]);
		    fwrite(hand, string);
    	}
    	
    	fclose(hand);
	}
	return 1;
}

stock serverCreateVehicleKey()
{
    serverVehicleKeys ++;
    
	// variaveis
	new string_file[15];

	// Guardar infos
	new File: hand = fopen(pastaKeys, io_write);

	if (hand) {

		format(string_file, sizeof string_file, "%d", serverVehicleKeys);

		fwrite(hand, string_file);

		fclose(hand);
	}
    
    return serverVehicleKeys;
}

stock serverLoadVehicleKeys()
{
	// variaveis
	new string_file[15];

	// Guardar infos
	new File: hand = fopen(pastaKeys, io_read);

	if (hand) {

		fread(hand, string_file);

		serverVehicleKeys = strval(string_file);

		fclose(hand);
	}
	
	if (serverVehicleKeys < 1000)
	    serverVehicleKeys = 1000;
}

callback LoadVehicleInfo(vehicleid) {
	// variaveis
	new file[75], string_read[128], vehicle;

	// arquivo
	format(file, sizeof (file), pastaVehicles, vehicleid);

	// Guardar infos
	new File: hand = fopen(file, io_read);

	if (hand) {
	    if (flength(hand) < 25) {
	        fclose(hand);
	        hand = File:0;
	    }
	}

	if (hand) {

	    new string_info[14][35];

		// Criar o carro
	    fread(hand, string_read);
	    split(string_read, string_info, ',');

	    new modelid = strval(string_info[0]);
	    new maxitens = getMaxSlotsByModel(modelid);

	    vehicle = AddStaticVehicleEx(modelid, floatstr(string_info[1]), floatstr(string_info[2]), floatstr(string_info[3]), floatstr(string_info[4]), strval(string_info[8]), strval(string_info[9]), -1);

		//printf("vehicleid - FILE: %d", vehicle);

		// Setar a vida do carro
		
		new Float:health = floatstr(string_info[5]);
		
		if (health > 950)
		    health = 950.0;
		
		SetVehicleHealth(vehicle, health);

		SetCarEngineState(vehicle, 0);
		
		VehicleInfo[vehicle][vehFuel] = strval(string_info[6]);
		VehicleInfo[vehicle][vehBatery] = floatstr(string_info[7]);
		VehicleInfo[vehicle][vehUniqueId] = strval(string_info[10]);
		VehicleInfo[vehicle][vehTickRespawn] = strval(string_info[11]);
		VehicleInfo[vehicle][vehKeyId] = strval(string_info[12]);
		VehicleInfo[vehicle][vehLocked] = strval(string_info[13]);
		
		VehicleInfo[vehicle][vehDied] = 0;

		if (VehicleInfo[vehicle][vehUniqueId] == 0)
		{
		    VehicleInfo[vehicle][vehUniqueId] = vehicle;
		}

		// Damages
	    fread(hand, string_read);
	    split(string_read, string_info, ',');

		UpdateVehicleDamageStatus(vehicle, strval(string_info[0]), strval(string_info[1]), strval(string_info[2]), strval(string_info[3]));

		// Loot
		new lootid = createLoot(0.0000, 0.0000, 0.0000, 0, LOOT_TYPE_VEHICLE, false, true, false, 0.0000, maxitens);

		for(new itens; itens != maxitens; itens++) {

			fread(hand, string_read);
		    split(string_read, string_info, ',');

		    if (strval(string_info[0])) {
		        addItemToLoot(lootid, strval(string_info[2]), strval(string_info[3]), strval(string_info[4]), string_info[1]);
		    }
		}

		attachLootToVehicle(lootid, vehicle);
		VehicleInfo[vehicle][vehLoot] = lootid;

		fclose(hand);
	} 
}

public OnVehicleDeath(vehicleid, killerid) {

	if (GetVehicleVirtualWorld(vehicleid) != 0 || VehicleInfo[vehicleid][vehDied])
	    return 1;

	if (VehicleInfo[vehicleid][vehDestroyTimer] == 0)
    	VehicleInfo[vehicleid][vehDestroyTimer] = SetTimerEx("CreateNewVehicleRandomSpawn", 5000, false, "d", vehicleid);

    VehicleInfo[vehicleid][vehDied] = 1;

	return 1;
}

public OnVehicleSpawn(vehicleid)
{
    if (VehicleInfo[vehicleid][vehDied])
    {
        VehicleInfo[vehicleid][vehDied] = 0;
        
		new Float:health = 380 + random(100);

		if (health > 950)
		    health = 950.0;

		SetVehicleHealth(vehicleid, health);

		VehicleInfo[vehicleid][vehHealth] = health;

		SetCarEngineState(vehicleid, 0);

		VehicleInfo[vehicleid][vehFuel] = 10 + random(8);
		VehicleInfo[vehicleid][vehBatery] = 10.0 + frandom(10.0);

        new index = random(sizeof VehiclesSpawnsPoints);
        
        SetVehiclePos(vehicleid, VehiclesSpawnsPoints[index][spawnVehx],VehiclesSpawnsPoints[index][spawnVehy],VehiclesSpawnsPoints[index][spawnVehz]);
        SetVehicleZAngle(vehicleid, VehiclesSpawnsPoints[index][spawnVeha]);

		new col1 = random(128);
		new col2 = random(128);

	    VehicleInfo[vehicleid][vehColor1] = col1;
	    VehicleInfo[vehicleid][vehColor2] = col2;

		VehicleInfo[vehicleid][vehUniqueId] = vehicleid;
		VehicleInfo[vehicleid][vehTickRespawn] = 0;
		VehicleInfo[vehicleid][vehKeyId] = 0;
		VehicleInfo[vehicleid][vehLocked] = 0;

		// Setar itens no loot
	    SetLootItens(VehicleInfo[vehicleid][vehLoot], .lootType = getVehicleModelLootType(GetVehicleModel(vehicleid)), .maxitens = 1 + random(3));

		// Thanks to gamemode S&S
		new
			panels = encode_panels(random(4), random(4), random(4), random(4), random(4), random(4), random(4)),
			doors = encode_doors(random(5), random(5), random(5), random(5));

		UpdateVehicleDamageStatus(vehicleid,
			panels,
			doors,
			encode_lights(random(2), random(2), random(2), random(2)),
			encode_tires(random(2), random(2), random(2), random(2)) );

		SaveVehicleInfo(vehicleid);
	}

    return 1;
}

callback CreateNewVehicleRandomSpawn(vehicle) {

    VehicleInfo[vehicle][vehDestroyTimer] = 0;

	VehicleInfo[vehicle][vehUniqueId] = vehicle;
	VehicleInfo[vehicle][vehTickRespawn] = 0;
	VehicleInfo[vehicle][vehKeyId] = 0;
	VehicleInfo[vehicle][vehLocked] = 0;

	//printf("vehicleid - NO FILE: %d, type: %d", vehicle, modelid);

	new Float:health = 380 + random(100);

	if (health > 950)
	    health = 950.0;

	SetVehicleHealth(vehicle, health);

	VehicleInfo[vehicle][vehHealth] = health;

	SetCarEngineState(vehicle, 0);

	VehicleInfo[vehicle][vehFuel] = 10 + random(8);
	VehicleInfo[vehicle][vehBatery] = 10.0 + frandom(10.0);

	// Setar itens no loot
    
    resetAllLootItens(VehicleInfo[vehicle][vehLoot]);

	// Thanks to gamemode S&S
	new
		panels = encode_panels(random(4), random(4), random(4), random(4), random(4), random(4), random(4)),
		doors = encode_doors(random(5), random(5), random(5), random(5));

	UpdateVehicleDamageStatus(vehicle,
		panels,
		doors,
		encode_lights(random(2), random(2), random(2), random(2)),
		encode_tires(random(2), random(2), random(2), random(2)) );

	SaveVehicleInfo(vehicle);
	
	SetVehicleToRespawn(vehicle);
}

stock DestroyServerVehicle(vehindex)
{
	if (GetVehicleVirtualWorld(vehindex) != 0)
	    return 0;
	    
	new file[75];
	// arquivo
	format(file, sizeof (file), pastaVehicles, vehindex);

	// remover arquivo
	if (fexist(file))
	{
	    fremove(file);
	}

	// destruir veiculo
	if (IsValidVehicle(vehindex))
	{
	    DestroyVehicle(vehindex);

	    // destruir o loot
	    destroyLoot(VehicleInfo[vehindex][vehLoot]);
	}
	return 1;
}

stock remakeVehiclesServer(maxrandom = -1)
{
	new Iterator:spawnsVehiclesUsed<sizeof VehiclesSpawnsPoints>;
	
	for(new index; index < sizeof VehiclesSpawnsPoints; index++)
	    Iter_Add(spawnsVehiclesUsed, index);
	
	new file[75], vehicle;

	// destroy all vehicles
	for(new vehindex = 1; vehindex < MAX_VEHICLES; vehindex++)
	{
		// arquivo
		format(file, sizeof (file), pastaVehicles, vehindex);
		
		// remover arquivo
		if (fexist(file))
		{
		    fremove(file);
		}
		
		// destruir veiculo
		if (IsValidVehicle(vehindex))
		{
		    DestroyVehicle(vehindex);
		    
		    // destruir o loot
		    destroyLoot(VehicleInfo[vehindex][vehLoot]);
		}
	}
	
	new amountVehicles = 300 + random(50);
	
	if (maxrandom != -1)
	    amountVehicles = maxrandom;
	
	for(new vehicleid; vehicleid < amountVehicles; vehicleid++)
	{
	    new index = Iter_Random(spawnsVehiclesUsed);
	    
	    // remover
	    Iter_Remove(spawnsVehiclesUsed, index);
	    
	    new modelid = getVehicleModelByType(VehiclesSpawnsPoints[index][vehType]);
	    new maxitens = getMaxSlotsByModel(modelid);

		// color
		new col1 = random(128);
		new col2 = random(128);

	    vehicle = CreateVehicle(modelid,
	    VehiclesSpawnsPoints[index][spawnVehx],VehiclesSpawnsPoints[index][spawnVehy],VehiclesSpawnsPoints[index][spawnVehz],
		VehiclesSpawnsPoints[index][spawnVeha], col1, col2, -1);

        VehicleInfo[vehicle][vehColor1] = col1;
        VehicleInfo[vehicle][vehColor2] = col2;
		//printf("vehicleid - NO FILE: %d, type: %d", vehicle, modelid);

		new Float:health = 380 + random(100);

		if (health > 950)
		    health = 950.0;

		SetVehicleHealth(vehicle, health);

		SetCarEngineState(vehicle, 0);

		VehicleInfo[vehicle][vehFuel] = 10 + random(8);
		VehicleInfo[vehicle][vehBatery] = 10.0 + frandom(10.0);

		VehicleInfo[vehicle][vehUniqueId] = vehicle;
		VehicleInfo[vehicle][vehTickRespawn] = 0;
		VehicleInfo[vehicle][vehKeyId] = 0;
		VehicleInfo[vehicle][vehLocked] = 0;
		VehicleInfo[vehicle][vehDied] = 0;

		new lootid = createLoot(0.0000, 0.0000, 0.0000, 0, LOOT_TYPE_VEHICLE, false, true, false, 0.0000, maxitens);

		attachLootToVehicle(lootid, vehicle);
		VehicleInfo[vehicle][vehLoot] = lootid;

		// Setar itens no loot
        SetLootItens(lootid, .lootType = getVehicleModelLootType(modelid), .maxitens = 1 + random(3));

		// Thanks to gamemode S&S
		new
			panels = encode_panels(random(4), random(4), random(4), random(4), random(4), random(4), random(4)),
			doors = encode_doors(random(5), random(5), random(5), random(5));

		UpdateVehicleDamageStatus(vehicle,
			panels,
			doors,
			encode_lights(random(2), random(2), random(2), random(2)),
			encode_tires(random(2), random(2), random(2), random(2)) );

		SaveVehicleInfo(vehicle);
	}
}

stock createNewVehicleLoot(modelid, Float:x, Float:y, Float:z, Float:ang, color1, color2) {

	new maxitens = getMaxSlotsByModel(modelid);

	new vehicle = CreateVehicle(modelid, x, y, z, ang, color1, color2, -1);

	//printf("vehicleid - NO FILE: %d, type: %d", vehicle, modelid);

	new Float:health = 380 + random(100);

	if (health > 950)
	    health = 950.0;

	SetVehicleHealth(vehicle, health);

	SetCarEngineState(vehicle, 0);

	VehicleInfo[vehicle][vehFuel] = random(8);
	VehicleInfo[vehicle][vehBatery] = 10.0 + frandom(20.0);

	VehicleInfo[vehicle][vehUniqueId] = vehicle;
	VehicleInfo[vehicle][vehTickRespawn] = 0;
	VehicleInfo[vehicle][vehKeyId] = 0;
	VehicleInfo[vehicle][vehLocked] = 0;
	VehicleInfo[vehicle][vehDied] = 0;

	new lootid = createLoot(0.0000, 0.0000, 0.0000, 0, LOOT_TYPE_VEHICLE, false, true, false, 0.0000, maxitens);

	new random_quant;

    random_quant = random(10) + 5;
    if (random_quant)addItemToLoot(lootid, ITEM_TYPE_GASOLINA,   1650,  random_quant, "Gasolina");

	attachLootToVehicle(lootid, vehicle);
	VehicleInfo[vehicle][vehLoot] = lootid;

	// Thanks to gamemode S&S
	new
		panels = encode_panels(random(4), random(4), random(4), random(4), random(4), random(4), random(4)),
		doors = encode_doors(random(5), random(5), random(5), random(5));

	UpdateVehicleDamageStatus(vehicle,
		panels,
		doors,
		encode_lights(random(2), random(2), random(2), random(2)),
		encode_tires(random(2), random(2), random(2), random(2)) );

	SaveVehicleInfo(vehicle);
	printf("vehicleid - %d saved!", vehicle);
	
	return vehicle;
}

stock CountVehicleItemType(vehicleid, itemtype) {

	new lootid = VehicleInfo[vehicleid][vehLoot];
	new count  = 0;
	
	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {

		if (LootItensInfo[lootid][itens][item_valid] && LootItensInfo[lootid][itens][item_type] == itemtype) {
     		count += LootItensInfo[lootid][itens][item_quantia];
	    }
   	}
   	return count;
}

stock AddGasVehicle(vehicleid, quantia) {

    VehicleInfo[vehicleid][vehFuel] += quantia;

   	return 0;
}

stock RemoveGasVehicle(vehicleid) {

    VehicleInfo[vehicleid][vehFuel] --;
/*
	new lootid = VehicleInfo[vehicleid][vehLoot];

	for(new itens; itens != LootInfo[lootid][loot_slots]; itens++) {

		if (LootItensInfo[lootid][itens][item_valid] && LootItensInfo[lootid][itens][item_type] == ITEM_TYPE_GASOLINA) {

			if (LootItensInfo[lootid][itens][item_quantia]) {

				LootItensInfo[lootid][itens][item_quantia] --;
	 			
	 			if ( LootItensInfo[lootid][itens][item_quantia] < 1 ) {

					 resetLootSlot(lootid, itens);
	 			}
	 			return 1;
			}
	    }
   	}*/
   	return 0;
}

stock Float:GetVehicleHealthEx(vehicleid)
{
	new Float:health;
	GetVehicleHealth(vehicleid, health);
	if(health > 900.0)return health/10.0;
	else return (health/10.0)-(24);
}

stock GetVehicleSpeed_v(vehicleid)
{
	new Float:xPos[3];
	GetVehicleVelocity(vehicleid, xPos[0], xPos[1], xPos[2]);
	return floatround(floatsqroot(xPos[0] * xPos[0] + xPos[1] * xPos[1] + xPos[2] * xPos[2]) * 135.00);
}

stock Float:getLimitVelocityVehicle(Float:vehicleDamage) {

	new Float: speedLimit;
	
	if (vehicleDamage < 50) {
	
	    switch (floatround(vehicleDamage)) {
	    
	        case 01 .. 10: speedLimit = 15.0000;
	        case 11 .. 20: speedLimit = 30.0000;
	        case 21 .. 30: speedLimit = 35.0000;
	        case 31 .. 40: speedLimit = 50.0000;
	        case 41 .. 50: speedLimit = 65.0000;
	    }
	
	    return speedLimit;
	}
	return 99999.9;
}

callback UpdatePlayerVehicle(playerid, vehicleid) {
	// variable
	new string[128];
	// check if is a bike
	switch(GetVehicleModel(vehicleid)) {
	    case 510, 481:{
	        // set vehicle engine ON
		   	return SetCarEngineState(vehicleid, 1);
	    }
	}
	// get all vehicle info
	new countFuel    			= VehicleInfo[vehicleid][vehFuel];
	new Float: countBatery      = VehicleInfo[vehicleid][vehBatery];
	new Float: countSpeed 		= GetVehicleSpeed_v(vehicleid);
	new Float: vehicleDamage 	= GetVehicleHealthEx(vehicleid);
	new Float:countHealth;
	GetVehicleHealth(vehicleid, countHealth);
	// dont explode vehicle
	if (countHealth < 360.0)
		SetVehicleHealth(vehicleid, 360.0);
	// get vehicle speed
	new Float: getSpeedLimit = getLimitVelocityVehicle(vehicleDamage);
	// check if vehicle status
	if (countSpeed > getSpeedLimit || countFuel < 1 || countBatery <= 0.0)
	    SetCarEngineState(vehicleid, 0);
	// if vehicle have fuel
	if (countFuel) {
		// check if time to remove fuel and batery
	  	if (gettime() > VehicleInfo[vehicleid][vehLastFuel] && GetCarEngineState(vehicleid)) {
  			VehicleInfo[vehicleid][vehLastFuel] = gettime() + 35;
  			VehicleInfo[vehicleid][vehBatery] -= frandom(0.5);
		    RemoveGasVehicle(vehicleid);
		}
	}
	format(string, sizeof string, GetPlayerLanguageKey(playerid, "SPEEDO"), getVehicleName(vehicleid), countFuel, countBatery, GetVehicleHealthEx(vehicleid), countSpeed);
   	PlayerTextDrawSetString(playerid, textVelocimetro[playerid], string);
	return 1;
}


/*
callback UpdateVehicles() {

	new string[128];

	for(new vehicleid = 1, j = GetVehiclePoolSize(); vehicleid <= j; vehicleid++) {

		if (!IsValidVehicle(vehicleid))
		    continue;

		switch(GetVehicleModel(vehicleid))
		{
		    case 510, 481:
		    {
		    	SetCarEngineState(vehicleid, 1);
		    	continue;
		    }
		}

		new ocupped = IsVehicleOcuppied(vehicleid);

		if (!ocupped)
		    continue;

		//new countEngine  			= CountVehicleItemType(vehicleid, ITEM_TYPE_MOTOR);
		//new countFuel    			= CountVehicleItemType(vehicleid, ITEM_TYPE_GASOLINA);
		new countFuel    			= VehicleInfo[vehicleid][vehFuel];
		new Float: countBatery      = VehicleInfo[vehicleid][vehBatery];
		new Float: countSpeed 		= GetVehicleSpeed_v(vehicleid);
		new Float: vehicleDamage 	= GetVehicleHealthEx(vehicleid);
		new Float:countHealth;
		GetVehicleHealth(vehicleid, countHealth);
		
		if (countHealth < 360.0)
			SetVehicleHealth(vehicleid, 360.0);
			
		new Float: getSpeedLimit = getLimitVelocityVehicle(vehicleDamage);
		
		if (countSpeed > getSpeedLimit || countFuel < 1 || countBatery <= 0.0)
		    SetCarEngineState(vehicleid, 0);

		if (ocupped && countFuel) {
		    
		    if (gettime() > VehicleInfo[vehicleid][vehLastFuel] && GetCarEngineState(vehicleid)) {
		        VehicleInfo[vehicleid][vehLastFuel] = gettime() + 35;
		        VehicleInfo[vehicleid][vehBatery] -= frandom(0.5);
		        RemoveGasVehicle(vehicleid);
		    }
		}
		if (!ocupped)
		    continue;
		    
		foreach(new playerid : Player) {
		
		    if (GetPlayerVehicleID(playerid) == vehicleid) {
		        format(string, sizeof string, GetPlayerLanguageKey(playerid, "SPEEDO"), getVehicleName(vehicleid), countFuel, countBatery, GetVehicleHealthEx(vehicleid), countSpeed);
		        PlayerTextDrawSetString(playerid, textVelocimetro[playerid], string);
		    }
		}
	}
}*/

stock GetVehicleFuel(vehicleid)
	return VehicleInfo[vehicleid][vehFuel];

stock UnlockVehicle(vehicleid) {

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, 0, bonnet, boot, objective);
    VehicleInfo[vehicleid][vehLocked] = 0;
    
    SaveVehicleInfo(vehicleid);

	return 1;
}

stock LockVehicle(vehicleid) {

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, engine, lights, alarm, 1, bonnet, boot, objective);
    VehicleInfo[vehicleid][vehLocked] = 1;
    
    SaveVehicleInfo(vehicleid);

	return 1;
}

stock IsVehicleEngine(vehicleid) {

	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if (engine) {
        return 1;
	}

	return 0;
}

stock IsVehicleOcuppied(vehicleid) {

	foreach(new playerid : Player) {

		if (GetPlayerVehicleID(playerid) == vehicleid) {
  			return 1;
    	}
	}
	return 0;
}

stock IsVehicleAnyDriver(vehicleid) {

	foreach(new playerid : Player) {

		if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetPlayerVehicleID(playerid) == vehicleid) {
  			return 1;
    	}
	}
	return 0;
}

callback CreateServerVehicles() {

	for(new vehicleid = 1; vehicleid < sizeof (VehiclesSpawnsPoints); vehicleid++) {

		// Carregar as informações
		LoadVehicleInfo(vehicleid);
	}
}

callback ReconstroyVehicle(vehicleid) {

	// Destruir o veiculo
	DestroyVehicle(vehicleid);
	
	// Destruir o loot
	destroyLoot(VehicleInfo[vehicleid][vehLoot]);
	
	// Refazer o mesmo
    new modelid = getVehicleModelByType(VehiclesSpawnsPoints[vehicleid][vehType]);
    new maxitens = getMaxSlotsByModel(modelid);
	
	new vehicle = CreateVehicle(modelid,
	    VehiclesSpawnsPoints[vehicleid][spawnVehx],VehiclesSpawnsPoints[vehicleid][spawnVehy],VehiclesSpawnsPoints[vehicleid][spawnVehz],
		VehiclesSpawnsPoints[vehicleid][spawnVeha], -1, -1, -1);

	new lootid = createLoot(0.0000, 0.0000, 0.0000, 0, LOOT_TYPE_VEHICLE, false, true, false, 0.0000, maxitens);

	attachLootToVehicle(lootid, vehicle);
	VehicleInfo[vehicle][vehLoot] = lootid;
}

stock GetVehicleLoot(vehicleid) return VehicleInfo[vehicleid][vehLoot];

callback destroyServerVehicle(vehicleid) {

	destroyLoot(VehicleInfo[vehicleid][vehLoot]);
	VehicleInfo[vehicleid][vehLoot] = -1;

	return DestroyVehicle(vehicleid);
}

stock IsACar(carid)
{
	new vehicleclass = GetVehicleModel(carid);
	switch(vehicleclass)
	{
		case 448:return 0;
		case 461:return 0;
		case 462:return 0;
		case 463:return 0;
		case 468:return 0;
		case 521:return 0;
		case 522:return 0;
		case 523:return 0;
		case 581:return 0;
		case 586:return 0;
		case 481:return 0;
		case 509:return 0;
		case 510:return 0;
		case 430:return 0;
		case 446:return 0;
		case 452:return 0;
		case 453:return 0;
		case 454:return 0;
		case 472:return 0;
		case 473:return 0;
		case 484:return 0;
		case 493:return 0;
		case 595:return 0;
		case 417:return 0;
		case 425:return 0;
		case 447:return 0;
		case 465:return 0;
		case 469:return 0;
		case 487:return 0;
		case 488:return 0;
		case 497:return 0;
		case 501:return 0;
		case 548:return 0;
		case 563:return 0;
		case 406:return 0;
		case 444:return 0;
		case 556:return 0;
		case 557:return 0;
		case 573:return 0;
		case 460:return 0;
		case 464:return 0;
		case 476:return 0;
		case 511:return 0;
		case 512:return 0;
		case 513:return 0;
		case 519:return 0;
		case 520:return 0;
		case 539:return 0;
		case 553:return 0;
		case 577:return 0;
		case 592:return 0;
		case 593:return 0;
		case 471:return 0;
	}
	return 1;
}

stock IsABoat(carid)
{
    new oo = GetVehicleModel(carid);
	switch(oo)
	{
		case 430:return 1;
		case 446:return 1;
		case 452:return 1;
		case 453:return 1;
		case 454:return 1;
		case 472:return 1;
		case 473:return 1;
		case 484:return 1;
		case 493:return 1;
		case 595:return 1;
	}
	return 0;
}

stock IsAPlane(carid)
{
	new oo = GetVehicleModel(carid);
	switch(oo)
	{
		case 460:return 1;
		case 464:return 1;
		case 476:return 1;
		case 511:return 1;
		case 512:return 1;
		case 513:return 1;
		case 519:return 1;
		case 520:return 1;
		case 539:return 1;
		case 553:return 1;
		case 577:return 1;
		case 592:return 1;
		case 593:return 1;
		case 417:return 1;
		case 425:return 1;
		case 447:return 1;
		case 465:return 1;
		case 469:return 1;
		case 487:return 1;
		case 488:return 1;
		case 497:return 1;
		case 501:return 1;
		case 548:return 1;
		case 563:return 1;
	}
	return 0;
}

stock IsABike(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
    switch(model)
    {
        case 509, 481, 510, 462, 448, 581, 522,
		     461, 521, 523, 463, 586, 468, 471: return 1;
    }
	return 0;
}

stock CountVehicleTires(vehicleid) {

    if (IsACar(vehicleid))   return 4;
	if (IsABike(vehicleid))  return 2;
	if (IsAPlane(vehicleid)) return 0;
	if (IsABoat(vehicleid))  return 0;
	return 6;
}

stock static VehicleNames[212][] =
{
    {"Landstalker"},
	{"Bravura"},
	{"Buffalo"},
	{"Linerunner"},
	{"Perrenial"},
	{"Sentinel"},
	{"Dumper"},
    {"Firetruck"},
	{"Trashmaster"},
	{"Stretch"},
	{"Manana"},
	{"Infernus"},
	{"Voodoo"},
	{"Pony"},
	{"Mule"},
    {"Cheetah"},
	{"Ambulance"},
	{"Leviathan"},
	{"Moonbeam"},
	{"Esperanto"},
	{"Taxi"},
	{"Washington"},
    {"Bobcat"},
	{"Mr Whoopee"},
	{"BF Injection"},
	{"Hunter"},
	{"Premier"},
	{"Enforcer"},
	{"Securicar"},
    {"Banshee"},
	{"Predator"},
	{"Bus"},
	{"Rhino"},
	{"Barracks"},
	{"Hotknife"},
	{"Trailer 1"},
	{"Previon"},
    {"Coach"},
	{"Cabbie"},
	{"Stallion"},
	{"Rumpo"},
	{"RC Bandit"},
	{"Romero"},
	{"Packer"},
	{"Monster"},
    {"Admiral"},
	{"Squalo"},
	{"Seasparrow"},
	{"Pizzaboy"},
	{"Tram"},
	{"Trailer 2"},
	{"Turismo"},
    {"Speeder"},
	{"Reefer"},
	{"Tropic"},
	{"Flatbed"},
	{"Yankee"},
	{"Caddy"},
	{"Solair"},
	{"Berkley"},
    {"Skimmer"},
	{"PCJ-600"},
	{"Faggio"},
	{"Freeway"},
	{"RC Baron"},
	{"RC Raider"},
	{"Glendale"},
	{"Oceanic"},
    {"Sanchez"},
	{"Sparrow"},
	{"Patriot"},
	{"Quad"},
	{"Coastguard"},
	{"Dinghy"},
	{"Hermes"},
	{"Sabre"},
    {"Rustler"},
	{"ZR-350"},
	{"Walton"},
	{"Regina"},
	{"Comet"},
	{"BMX"},
	{"Burrito"},
	{"Camper"},
	{"Marquis"},
    {"Baggage"},
	{"Dozer"},
	{"Maverick"},
	{"News Chopper"},
	{"Rancher"},
	{"FBI Rancher"},
	{"Virgo"},
	{"Greenwood"},
    {"Jetmax"},
	{"Hotring"},
	{"Sandking"},
	{"Blista"},
	{"Maverick"},
	{"Boxville"},
	{"Benson"},
    {"Mesa"},
	{"RC Goblin"},
	{"Hotring"},
	{"Hotring"},
	{"Bloodring"},
	{"Rancher"},
    {"Super GT"},
	{"Elegant"},
	{"Journey"},
	{"Bike"},
	{"Bike"},
	{"Beagle"},
	{"Cropdust"},
	{"Stunt"},
    {"Tanker"},
	{"Roadtrain"},
	{"Nebula"},
	{"Majestic"},
	{"Buccaneer"},
	{"Shamal"},
	{"Hydra"},
	{"FCR-900"},
    {"NRG-500"},
	{"HPV1000"},
	{"Truck"},
	{"Tow Truck"},
	{"Fortune"},
	{"Cadrona"},
	{"FBI Truck"},
    {"Willard"},
	{"Forklift"},
	{"Tractor"},
	{"Combine"},
	{"Feltzer"},
	{"Remington"},
	{"Slamvan"},
    {"Blade"},
	{"Freight"},
	{"Streak"},
	{"Vortex"},
	{"Vincent"},
	{"Bullet"},
	{"Clover"},
	{"Sadler"},
    {"Firetruck LA"},
	{"Hustler"},
	{"Intruder"},
	{"Primo"},
	{"Cargobob"},
	{"Tampa"},
	{"Sunrise"},
	{"Merit"},
    {"Utility"},
	{"Nevada"},
	{"Yosemite"},
	{"Windsor"},
	{"Monster A"},
	{"Monster B"},
	{"Uranus"},
	{"Jester"},
    {"Sultan"},
	{"Stratum"},
	{"Elegy"},
	{"Raindance"},
	{"RC Tiger"},
	{"Flash"},
	{"Tahoma"},
	{"Savanna"},
    {"Bandito"},
	{"Freight Flat"},
	{"Streak Carriage"},
	{"Kart"},
	{"Mower"},
	{"Duneride"},
	{"Sweeper"},
    {"Broadway"},
	{"Tornado"},
	{"AT-400"},
	{"DFT-30"},
	{"Huntley"},
	{"Stafford"},
	{"BF-400"},
	{"Newsvan"},
    {"Tug"},
	{"Trailer 3"},
	{"Emperor"},
	{"Wayfarer"},
	{"Euros"},
	{"Hotdog"},
	{"Club"},
	{"Freight"},
    {"Trailer 3"},
	{"Andromada"},
	{"Dodo"},
	{"RC Cam"},
	{"Launch"},
	{"Police Car"},
	{"Police Car"},
    {"Police Car"},
	{"Police Ranger"},
	{"Picador"},
	{"S.W.A.T. Van"},
	{"Alpha"},
	{"Phoenix"},
	{"Glendale"},
    {"Sadler"},
	{"Luggage"},
	{"Luggage"},
	{"Stair Trailer"},
	{"Boxville"},
	{"Farm Plow"},
    {"Utility Trailer"}
};

stock getVehicleName(vehicleid){
	new vehmodel = GetVehicleModel(vehicleid);
	new nameVeh[75];

	if (vehmodel < 400 || vehmodel > 611) {
		strcat(nameVeh, "Nenhum");
		return nameVeh;
	}
	strcat(nameVeh, VehicleNames[vehmodel - 400]);
	return nameVeh;
}

enum
{
	WHEELSFRONT_LEFT,	// 0
	WHEELSFRONT_RIGHT,	// 1
	WHEELSMID_LEFT,		// 2
	WHEELSMID_RIGHT,	// 3
	WHEELSREAR_LEFT,	// 4
	WHEELSREAR_RIGHT	// 5
}

stock GetVehicleWheelPos(vehicleid, wheel, &Float:x, &Float:y, &Float:z)
{
	new
		Float:rot,
		Float:x2,
		Float:y2,
		Float:z2,
		Float:div;

	GetVehicleZAngle(vehicleid, rot);
	GetVehiclePos(vehicleid, x2, y2, z2);

	rot = 360 - rot;

	switch(wheel)
	{
		case WHEELSFRONT_LEFT .. WHEELSFRONT_RIGHT: // Front Tyres
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_WHEELSFRONT, x, y, z);

		case WHEELSMID_LEFT .. WHEELSMID_RIGHT: // Middle Tyres
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_WHEELSMID, x, y, z);

		case WHEELSREAR_LEFT .. WHEELSREAR_RIGHT: // Rear Tyres
			GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_WHEELSREAR, x, y, z);

		default: return 0;
	}
	div = (wheel % 2) ? (x) : (-x);
	x = floatsin(rot, degrees) * y + floatcos(rot, degrees) * div + x2;
	y = floatcos(rot, degrees) * y - floatsin(rot, degrees) * div + y2;
	z += z2;
	return 1;
}

stock GetVehiclePosEx(vid, &Float:px, &Float:py, &Float:pz, Float:offsetx = 0.0, Float:offsety = 0.0, Float:offsetz = 0.0)
{
	new
		Float:rx, Float:ry, Float:rz,
		Float:ssx, Float:ssy, Float:ssz,
		Float:cy, Float:cx, Float:cz, Float:w;
	GetVehiclePos(vid, px, py, pz);
	GetVehicleRotationQuat(vid, w, rx, ry, rz);
	GetVehicleZAngle(vid, rz);
	ssx = floatsin(rx, degrees),
	ssy = floatsin(ry, degrees),
	ssz = floatsin(rz, degrees),
	cx = floatcos(rx, degrees),
	cy = floatcos(ry, degrees),
	cz = floatcos(rz, degrees);
	if (offsetx)
	{
		px = px + offsetx * (cy * cz - ssx * ssy * ssz);
		py = py + offsetx * (cz * ssx * ssy + cy * ssz);
		pz = pz - offsetx * (cx * ssy);
	}
	if (offsety)
	{
		px = px - offsety * (cx * ssz);
		py = py + offsety * (cx * cz);
		pz = pz + offsety * (ssx);
	}
	if (offsetz)
	{
		px = px + offsetz * (cz * ssy + cy * ssx * ssz);
		py = py - offsetz * (cy * cz * ssx + ssy * ssz);
		pz = pz + offsetz * (cx * cy);
	}
	return 1;
}

stock GetVehiclePetrolCapPos(vehicleid, &Float:px, &Float:py, &Float:pz) {

	new
	    Float: vX, Float: vY, Float: vZ;

	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_PETROLCAP, vX, vY, vZ);

	GetVehiclePosEx(vehicleid, px, py, pz, vX, vY, vZ);
}

stock IsPlayerInPetrolCap(playerid, vehicleid) {

	static
	    Float:x, Float:y, Float:z;
	    
    GetVehiclePetrolCapPos(vehicleid, x, y, z);
    
    if (IsPlayerInRangeOfPoint(playerid, 1.5, x, y, z))
        return 1;

	return 0;
}

enum
{
	CAR_TIRE_FRONT_LEFT,
	CAR_TIRE_REAR_LEFT,
	CAR_TIRE_FRONT_RIGHT,
	CAR_TIRE_REAR_RIGHT,
	BIKE_TIRE_FRONT,
	BIKE_TIRE_REAR
}

stock SetCarTireState(vehicleid, tire, toggle)
{
	if(!IsValidVehicle(vehicleid))
		return 0;

	new
		panels,
		doors,
		lights,
		tires,

		backright,
		frontright,
		backleft,
		frontleft,
		backtire,
		fronttire;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

	decode_tires(tires, backright, frontright, backleft, frontleft);
	decode_tires_bike(tires, backtire, fronttire);

	switch(tire)
	{
		case CAR_TIRE_FRONT_LEFT:
			tires = encode_tires(backright, frontright, backleft, toggle);

		case CAR_TIRE_REAR_LEFT:
			tires = encode_tires(backright, frontright, toggle, frontleft);

		case CAR_TIRE_FRONT_RIGHT:
			tires = encode_tires(backright, toggle, backleft, frontleft);

		case CAR_TIRE_REAR_RIGHT:
			tires = encode_tires(toggle, frontright, backleft, frontleft);

		case BIKE_TIRE_FRONT:
		{
			tires = encode_tires_bike(backtire, toggle);
		}
		case BIKE_TIRE_REAR:
		{
			tires = encode_tires_bike(toggle, fronttire);
		}
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

	return 1;
}

CMD:state(playerid) {

    new vehicleid = GetPlayerClossestVehicle(playerid);

	SendClientMessagef(playerid, -1, "%d", GetCarTireState(vehicleid, GetPlayerVehicleWeel(playerid, vehicleid)));

	return 1;
}

stock GetCarTireState(vehicleid, tire)
{
	if(!IsValidVehicle(vehicleid))
		return 0;

	new
		panels,
		doors,
		lights,
		tires,
		backtire,
		fronttire;

	new backright, frontright, backleft, frontleft;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

    decode_tires(tires, backright, frontright, backleft, frontleft);
    decode_tires_bike(tires, backtire, fronttire);

	switch(tire)
	{
		case CAR_TIRE_FRONT_LEFT: return frontleft;
		case CAR_TIRE_REAR_LEFT:  return backleft;
		case CAR_TIRE_FRONT_RIGHT:return frontright;
		case CAR_TIRE_REAR_RIGHT: return backright;
		case BIKE_TIRE_FRONT:     return fronttire;
		case BIKE_TIRE_REAR:      return backtire;
	}

	return tires & tire;
}

CMD:tire(playerid) {

    new vehicleid = GetPlayerClossestVehicle(playerid);

	SendClientMessagef(playerid, -1, "%d", GetPlayerVehicleWeel(playerid, vehicleid));

	return 1;
}

stock GetPlayerVehicleWeel(playerid, vehicleid)
{
	static
	    Float:x,
	    Float:y,
	    Float:z;

	// Frente esquerda
    GetVehicleWheelPos(vehicleid, WHEELSFRONT_LEFT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return CAR_TIRE_FRONT_LEFT;

	// Frente direita
    GetVehicleWheelPos(vehicleid, WHEELSREAR_LEFT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return CAR_TIRE_REAR_LEFT;

    // Meio esquerda
    GetVehicleWheelPos(vehicleid, WHEELSFRONT_RIGHT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return CAR_TIRE_FRONT_RIGHT;

    // Meio direita
    GetVehicleWheelPos(vehicleid, WHEELSREAR_RIGHT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return CAR_TIRE_REAR_RIGHT;

    // Trás esquerda
    GetVehicleWheelPos(vehicleid, WHEELSFRONT_LEFT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return BIKE_TIRE_FRONT;

    // Trás direita
    GetVehicleWheelPos(vehicleid, WHEELSREAR_LEFT, x, y, z);
    if (IsPlayerInRangeOfPoint(playerid, 1.2, x, y, z)) return BIKE_TIRE_REAR;

	return -1;
}


stock GetCarEngineState(vehicleid)
{
	if(!IsValidVehicle(vehicleid))
		return 0;

	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	return engine;
}

stock UpdateCarEngineState(playerid, vehicleid)
{
	if(!IsValidVehicle(vehicleid))
		return 0;

	switch(GetVehicleModel(vehicleid))
	{
	    case 510, 481:
	    {
		   	SetCarEngineState(vehicleid, 1);
		   	return 1;
	    }
	}

	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    
    if (!engine) {
		new Float: countSpeed 		= GetVehicleSpeed_v(vehicleid);
		new Float: vehicleDamage 	= GetVehicleHealthEx(vehicleid);

		new Float: getSpeedLimit = getLimitVelocityVehicle(vehicleDamage);

		if (countSpeed > getSpeedLimit)
		    return 0;
		    
		if (VehicleInfo[vehicleid][vehBatery] <= 0.0)
		    return SendLanguageMessage(playerid, corCinza, "MSG_109");
		    
		if (VehicleInfo[vehicleid][vehFuel] < 1)
		    return SendLanguageMessage(playerid, corCinza, "MSG_110");
	}
    
    SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vehFuel] ? (engine ? (0) : (1)) : (0), lights, alarm, doors, bonnet, boot, objective);

	return 1;
}

stock IsPlayerAtVehicleTrunk(playerid, vehicleid)
{
	if(!(0 <= playerid < MAX_PLAYERS))
		return 0;

	if(!IsValidVehicle(vehicleid))
		return 0;

	new
		Float:vx,
		Float:vy,
		Float:vz,
		Float:px,
		Float:py,
		Float:pz,
		Float:vr,
		Float:six,
		Float:siy,
		Float:siz,
		Float:angle;

	GetVehiclePos(vehicleid, vx, vy, vz);
	GetPlayerPos(playerid, px, py, pz);

	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, six, siy, siz);

	// temp workaround for interaction zone of the marquis boat
	if(GetVehicleModel(vehicleid) == 484)
		siy = 0.0;

	if (!IsPlayerInRangeOfPoint(playerid, (siy / 2.0) + 0.8, vx, vy, vz))
	    return 0;

	GetVehicleZAngle(vehicleid, vr);

	angle = absoluteangle(vr - GetPointAngleToPoint(vx, vy, px, py));

	if(155.0 < angle < 205.0)
	{
		return 1;
	}

	return 0;
}

stock IsPlayerAtVehicleBonnet(playerid, vehicleid)
{
	if(!(0 <= playerid < MAX_PLAYERS))
		return 0;

	if(!IsValidVehicle(vehicleid))
		return 0;

	new
		Float:vx,
		Float:vy,
		Float:vz,
		Float:px,
		Float:py,
		Float:pz,
		Float:vr,
		Float:six,
		Float:siy,
		Float:siz,
		Float:angle;

	GetVehiclePos(vehicleid, vx, vy, vz);
	GetPlayerPos(playerid, px, py, pz);

	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, six, siy, siz);

	// temp workaround for interaction zone of the marquis boat
	if(GetVehicleModel(vehicleid) == 484)
		siy = 0.0;

	if (!IsPlayerInRangeOfPoint(playerid, siy + 2.8, vx, vy, vz))
	    return 0;

	GetVehicleZAngle(vehicleid, vr);

	angle = absoluteangle(vr - GetPointAngleToPoint(vx, vy, px, py));

	if(-25.0 < angle < 25.0 || 335.0 < angle < 385.0)
	{
		return 1;
	}

	return 0;
}

stock GetPlayerClossestVehicle(playerid) {

	new vehicleid = INVALID_VEHICLE_ID;

	new
	    Float:x,
	    Float:y,
	 	Float:z,
		Float:dist = 999999.0;

	for(new vehicle; vehicle < MAX_VEHICLES; vehicle++) {

		if (IsValidVehicle(vehicle)) {

		    GetVehiclePos(vehicle, x, y, z);

		    new Float:pdist = GetPlayerDistanceFromPoint(playerid, x, y, z);

		    if (pdist < dist && pdist < 4.0000) {

		        vehicleid = vehicle;
		        dist = pdist;
		    }
		}
	}

	return vehicleid;
}

stock SetCarEngineState(vehicleid, statee)
{
	if (statee) {
	
		if (VehicleInfo[vehicleid][vehFuel] < 1)
	    	return 0;
	
		new Float: countSpeed 		= GetVehicleSpeed_v(vehicleid);
		new Float: vehicleDamage 	= GetVehicleHealthEx(vehicleid);
		
		new Float: getSpeedLimit = getLimitVelocityVehicle(vehicleDamage);

		if (countSpeed > getSpeedLimit)
		    return 0;
	}

	new
		engine,
		lights,
		alarm,
		doors,
		bonnet,
		boot,
		objective;

    GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
    SetVehicleParamsEx(vehicleid, statee, lights, alarm, doors, bonnet, boot, objective);

	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if ((ispassenger && !IsVehicleAnyDriver(vehicleid)) || PlayerData[playerid][dPlayerBlocked] || PlayerData[playerid][dDropped]) {

	    static
	        Float:x,
	        Float:y,
	        Float:z;

		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z + 0.0002);
		
		if (PlayerData[playerid][dPlayerBlocked])
		{
		    ShowPlayerBaseProtectDialog(playerid);
		}
	}
    return 1;
}

/*==============================================================================

	Standard "encode_" functions with "decode_" counterparts

==============================================================================*/


stock decode_panels(input, &flp, &frp, &rlp, &rrp, &windshield, &front_bumper, &rear_bumper)
{
	flp = input & 0xF;
	frp = (input >> 4) & 0xF;
	rlp = (input >> 8) & 0xF;
	rrp = (input >> 12) & 0xF;
	windshield = (input >> 16) & 0xF;
	front_bumper = (input >> 20) & 0xF;
	rear_bumper = (input >> 24) & 0xF;
}
stock encode_panels(flp, frp, rlp, rrp, windshield, front_bumper, rear_bumper)
{
	return flp | (frp << 4) | (rlp << 8) | (rrp << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}

stock decode_doors(input, &bonnet, &boot, &driver_door, &passenger_door)
{
	bonnet = input & 0xFF;
	boot = (input >> 8) & 0xFF;
	driver_door = (input >> 16) & 0xFF;
	passenger_door = (input >> 24) & 0xFF;
}
stock encode_doors(bonnet, boot, driver_door, passenger_door)
{
	return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}

stock decode_lights(input, &light1, &light2, &light3, &light4)
{
	light1 = input & 0x1;
	light2 = (input >> 1) & 0x1;
	light3 = (input >> 2) & 0x1;
	light4 = (input >> 3) & 0x1;
}
stock encode_lights(light1, light2, light3, light4)
{
	return light1 | (light2 << 1) | (light3 << 2) | (light4 << 3);
}

stock decode_tires(input, &backright, &frontright, &backleft, &frontleft)
{
	backright = input & 0x1;
	frontright = (input >> 1) & 0x1;
	backleft = (input >> 2) & 0x1;
	frontleft = (input >> 3) & 0x1;
}
stock encode_tires(backright, frontright, backleft, frontleft)
{
	return backright | (frontright << 1) | (backleft << 2) | (frontleft << 3);
}

encode_tires_bike(rear, front) {

	return rear | (front << 1);
}

stock decode_tires_bike(input, &backtire, &fronttire)
{
	backtire = input & 0x1;
	fronttire = (input >> 1) & 0x1;
}

stock VehicleBonnetState(v, t=-1)
{
	new e, l, a, d, bn, bt, o;

	GetVehicleParamsEx(v, e, l, a, d, bn, bt, o);

	if(t != -1)
		SetVehicleParamsEx(v, e, l, a, d, t, bt, o);

	return bn;
}

stock VehicleBootState(v, t=-1)
{
	new e, l, a, d, bn, bt, o;

	GetVehicleParamsEx(v, e, l, a, d, bn, bt, o);

	if(t != -1)
		SetVehicleParamsEx(v, e, l, a, d, bn, t, o);

	return bt;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	if (IsPlayerNPC(playerid))
	    return 1;
	    
	static
	    Float:old_x,
	    Float:old_y,
	    Float:old_z;
	    
	GetVehiclePos(vehicleid, old_x, old_y, old_z);

	if(old_x * old_y * old_z == 0.0)
		return 0;

    // Check if it moved far
    if(GetVehicleDistanceFromPoint(vehicleid, new_x, new_y, new_z) > 15)
    {
        // Reject the update
        SetVehiclePos(vehicleid, old_x, old_y, old_z);
        return 0;
    }

    return 1;
}

