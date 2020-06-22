// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
#define MAX_EXPLOSIVES (150)

enum E_EXPLOSIVES {
bool: 	e_valid,
Float:  e_x,
Float:  e_y,
Float:  e_z,
		e_object,
		e_type,
		e_timer,
		e_count,
		e_world,
}

new serverExplosivo[MAX_EXPLOSIVES][E_EXPLOSIVES];

stock CreateExplosive(Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, type = ITEM_TYPE_EXPLOSIVO, explodetime = 15, world = 0) {

	for(new index; index < MAX_EXPLOSIVES; index++)
	{
	    if (!serverExplosivo[index][e_valid])
	    {
	        serverExplosivo[index][e_valid] = true;
	        
	        serverExplosivo[index][e_x] = x;
	        serverExplosivo[index][e_y] = y;
	        serverExplosivo[index][e_z] = z;
	        serverExplosivo[index][e_type] = type;
	        serverExplosivo[index][e_world] = world;
	        serverExplosivo[index][e_count] = explodetime;
	        
	        if (explodetime != -1) {
	            serverExplosivo[index][e_timer] = SetTimerEx("countDownExplosive", 1000, true, "d", index);
	        } else {
	            serverExplosivo[index][e_timer] = -1;
	        }
	        
	        switch(type)
	        {
	            case ITEM_TYPE_EXPLOSIVO:   serverExplosivo[index][e_object] = CreateDynamicObject(1654, x, y, z, rx, ry, rz, .worldid = world);
	            case ITEM_TYPE_EXPLOSIVOC4: serverExplosivo[index][e_object] = CreateDynamicObject(1252, x, y, z, rx, ry, rz, .worldid = world);
	            case ITEM_TYPE_EXPLOSIVORE: serverExplosivo[index][e_object] = CreateDynamicObject(363, x, y, z, rx, ry, rz, .worldid = world);
	        }
	        
	        return 1;
	    }
	}

	return 0;
}

callback countDownExplosive(index) {
	// check if is valid explosive
	if (serverExplosivo[index][e_valid]) {
        // count down
        serverExplosivo[index][e_count] --;
        // audio effect clock count down
        // check if time is ended
        if (serverExplosivo[index][e_count] < 1) {
            // kill timer of explosive
            KillTimer(serverExplosivo[index][e_timer]);
            // detone explosive
            detoneExplosive(index);
            return 1;
        }
        Play3DSound(serverExplosivo[index][e_count] < 6 ? 72 : 71, serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z], .distance = 20.0);
        return 1;
    }
    return 0;
}

stock detoneRemoteExplosive(playerid) {

	for(new index; index < MAX_EXPLOSIVES; index++)
	{
	    if (serverExplosivo[index][e_valid] && serverExplosivo[index][e_type] == ITEM_TYPE_EXPLOSIVORE)
	    {
	        if (!IsPlayerInRangeOfPoint(playerid, 20.0, serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z]))
	            continue;
	    
	        Play3DSound(71, serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z], .distance = 20.0);
	    
			Audio_Play(playerid, 71);
	    
	        detoneExplosive(index);
	        
	        return 1;
	    }
	}
	return 0;
}

stock detoneExplosive(index) {
	if (serverExplosivo[index][e_valid]) {
	    serverExplosivo[index][e_valid] = false;
	    // destroy object
	    DestroyDynamicObject(serverExplosivo[index][e_object]);
	    // create explosion
	    switch (serverExplosivo[index][e_type])
	    {
   			case ITEM_TYPE_EXPLOSIVO:
			   	CreateBaseExplosion(serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z], .maxdamage = 217.0, .maxrange = 8.0, .type = 0);
            case ITEM_TYPE_EXPLOSIVOC4:
				CreateBaseExplosion(serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z], .maxdamage = 311.0, .maxrange = 10.0, .type = 0);
			case ITEM_TYPE_EXPLOSIVORE:
				CreateBaseExplosion(serverExplosivo[index][e_x], serverExplosivo[index][e_y], serverExplosivo[index][e_z], .maxdamage = 188.0, .maxrange = 7.0, .type = 0);
		}
	    // Kill timer
	    KillTimer(serverExplosivo[index][e_timer]);
	}
	return 1;
}



