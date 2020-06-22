/*====================
khfesbgfhsegfsjbrgsjfbrjsgbrdgdrgrsgdr

======================*/

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
		frontleft;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

	decode_tires(tires, backright, frontright, backleft, frontleft);

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
			tires = encode_tires(backright, toggle, backleft, toggle);

		case BIKE_TIRE_REAR:
			tires = encode_tires(toggle, frontright, toggle, frontleft);
	}

	UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

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
		tires;

	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

	return tires & tire;
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

stock UpdateCarEngineState(vehicleid)
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
    SetVehicleParamsEx(vehicleid, VehicleInfo[vehicleid][vehFuel] ? (engine ? (0) : (1)) : (0), lights, alarm, doors, bonnet, boot, objective);

	return 1;
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

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if (ispassenger && !IsVehicleAnyDriver(vehicleid)) {
	
	    static
	        Float:x,
	        Float:y,
	        Float:z;

		GetPlayerPos(playerid, x, y, z);
		SetPlayerPos(playerid, x, y, z + 0.2);
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

stock IsPlayerAtVehicleTrunk(playerid, vehicleid)
{
	if(!(0 <= playerid < MAX_PLAYERS))
		return 0;

	if(!IsValidVehicle(vehicleid))
		return 0;

	new lootid = VehicleInfo[vehicleid][vehLoot];

	if(!IsPlayerInDynamicArea(playerid, LootInfo[lootid][loot_area]))
		return 0;

	new
		Float:vx,
		Float:vy,
		Float:vz,
		Float:px,
		Float:py,
		Float:pz,
		Float:vr,
		Float:angle;

	GetVehiclePos(vehicleid, vx, vy, vz);
	GetPlayerPos(playerid, px, py, pz);

	GetVehicleZAngle(vehicleid, vr);

	angle = absoluteangle(vr - GetAngleToPoint(vx, vy, px, py));

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

	new lootid = VehicleInfo[vehicleid][vehLoot];

	if(!IsPlayerInDynamicArea(playerid, LootInfo[lootid][loot_area]))
		return 0;

	new
		Float:vx,
		Float:vy,
		Float:vz,
		Float:px,
		Float:py,
		Float:pz,
		Float:vr,
		Float:angle;

	GetVehiclePos(vehicleid, vx, vy, vz);
	GetPlayerPos(playerid, px, py, pz);

	GetVehicleZAngle(vehicleid, vr);

	angle = absoluteangle(vr - GetAngleToPoint(vx, vy, px, py));

	if(-25.0 < angle < 25.0 || 335.0 < angle < 385.0)
	{
		return 1;
	}

	return 0;
}


