

stock fishingInPlace(playerid)
{
    hideInventory(playerid);

	new objectid = GetPVarInt(playerid, "objectVara");
	
	if (objectid != 0)
	    DestroyDynamicObject(objectid);
	    
	SetPVarInt(playerid, "objectVara", CreateDynamicObject(18632, -0.01954, -0.22892, 0.10910,   5.00000, 113.00000, -278.00000));
	AttachDynamicObjectToPlayer(GetPVarInt(playerid, "objectVara"), playerid, 0.0500, 0.4000, 0.0590,   5.00000, 153.00000, 260.00000);
	
	ApplyAnimation(playerid,"SWORD","sword_IDLE", 4.1, 0, 1, 1, 0, 20000);
	
	StartPlayerProgress(playerid, "Pescando...", 80,  1.0, .progressid = PROGRESS_FISHING);
	
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
}

