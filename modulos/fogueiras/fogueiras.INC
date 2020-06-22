#define MAX_FOGUEIRAS 			(255)
#define MAX_ITENS_IN_FOGUEIRAS 	(25)
#define FOGUEIRA_UPDATE_RATE    (5000)

enum E_SERVER_FOGUEIRA
{
Float:
	S_FOGUEIRA_X,
Float:
	S_FOGUEIRA_Y,
Float:
	S_FOGUEIRA_Z,
	S_FOGUEIRA_OBJECT,
	S_FOGUEIRA_PANELA,
	S_FOGUEIRA_TIMER,
	S_FOGUEIRA_DESTROY,
}
new s_FogueiraInfo[MAX_FOGUEIRAS][E_SERVER_FOGUEIRA];
new Iterator:iterFogueiras<MAX_FOGUEIRAS>;

// Itens na fogueira
enum E_ITENS_FOGUEIRA
{
bool:
	S_ITEM_FOGUEIRA_VALID,
	S_ITEM_FOGUEIRA_ID,
}
new s_ItensFogueira[MAX_FOGUEIRAS][MAX_ITENS_IN_FOGUEIRAS][E_ITENS_FOGUEIRA];

stock CreateServerFogueira(Float:x, Float:y, Float:z, timedestroy = 10)
{
	new index = Iter_Free(iterFogueiras);
	
	if (index != -1)
	{
	    CA_RayCastLine(x, y, z + 5, x, y, z - 100.0, x, y, z);
	
	    z += 0.1;
	
	    Iter_Add(iterFogueiras, index);
	    
	    s_FogueiraInfo[index][S_FOGUEIRA_X] = x;
	    s_FogueiraInfo[index][S_FOGUEIRA_Y] = y;
	    s_FogueiraInfo[index][S_FOGUEIRA_Z] = z;
	    s_FogueiraInfo[index][S_FOGUEIRA_DESTROY] = gettime() + (timedestroy * 60);
	    
	    s_FogueiraInfo[index][S_FOGUEIRA_OBJECT] = CreateDynamicObject(19632, x, y, z, 0.0, 0.0, 0.0, .worldid = 0);
	    s_FogueiraInfo[index][S_FOGUEIRA_PANELA] = CreateDynamicObject(19585, x, y + 0.2, z + 0.4327, 0.0, 0.0, 0.0, .worldid = 0);
	    s_FogueiraInfo[index][S_FOGUEIRA_TIMER] = SetTimerEx("s_UpdateFogueira", FOGUEIRA_UPDATE_RATE, true, "d", index);
	    
		for(new slotid; slotid < MAX_ITENS_IN_FOGUEIRAS; slotid++)
		{
 			s_ItensFogueira[index][slotid][S_ITEM_FOGUEIRA_VALID] = false;
 			s_ItensFogueira[index][slotid][S_ITEM_FOGUEIRA_ID] = -1;
		}
	}
	return index;
}

stock GetPlayerFogueira(playerid)
{
	foreach(new index : iterFogueiras)
	{
	    if (IsPlayerInRangeOfPoint(playerid, 1.7, s_FogueiraInfo[index][S_FOGUEIRA_X], s_FogueiraInfo[index][S_FOGUEIRA_Y], s_FogueiraInfo[index][S_FOGUEIRA_Z]))
	    {
	        return index;
	    }
	}
	return -1;
}

stock DestroyServerFogueira(index)
{
	if (Iter_Contains(iterFogueiras, index))
	{
	    Iter_Remove(iterFogueiras, index);
	    
	    DestroyDynamicObject(s_FogueiraInfo[index][S_FOGUEIRA_OBJECT]);
	    DestroyDynamicObject(s_FogueiraInfo[index][S_FOGUEIRA_PANELA]);
	    KillTimer(s_FogueiraInfo[index][S_FOGUEIRA_TIMER]);
	    
	    return 1;
	}
	return 0;
}

stock AddItemToServerFogueira(itemid, toindex)
{
	if (Iter_Contains(iterFogueiras, toindex))
	{
		for(new slotid; slotid < MAX_ITENS_IN_FOGUEIRAS; slotid++)
		{
		    if (s_ItensFogueira[toindex][slotid][S_ITEM_FOGUEIRA_VALID] || s_ItensFogueira[toindex][slotid][S_ITEM_FOGUEIRA_ID] == itemid)
		        continue;
		        
            s_ItensFogueira[toindex][slotid][S_ITEM_FOGUEIRA_VALID] = true;
            s_ItensFogueira[toindex][slotid][S_ITEM_FOGUEIRA_ID] 	= itemid;
            
            new Float:x = s_FogueiraInfo[toindex][S_FOGUEIRA_X];
            new Float:y = s_FogueiraInfo[toindex][S_FOGUEIRA_Y];
            new Float:z = s_FogueiraInfo[toindex][S_FOGUEIRA_Z];
            
            DropItensInfo[itemid][drop_x] = x;
            DropItensInfo[itemid][drop_y] = y;
            DropItensInfo[itemid][drop_z] = z + 0.4;
            
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_X, x);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_Y, y);
            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_Z, z + 0.4);
            if (DropItensInfo[itemid][drop_type] == ITEM_TYPE_CARNECRUA) {
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_X, 0.0);
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_Y, 0.0);
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_Z, 0.0);
			} else {
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_X, 90.0);
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_Y, 0.0);
	            Streamer_SetFloatData(STREAMER_TYPE_OBJECT, DropItensInfo[itemid][drop_object], E_STREAMER_R_Z, 0.0);
			}
            
			return 1;
		}
	
	    return 0;
	}
	return 0;
}

stock RemoveItemToServerFogueira(itemid, fromindex)
{
	if (Iter_Contains(iterFogueiras, fromindex))
	{
		for(new slotid; slotid < MAX_ITENS_IN_FOGUEIRAS; slotid++)
		{
		    if (!s_ItensFogueira[fromindex][slotid][S_ITEM_FOGUEIRA_VALID])
		        continue;

			if (s_ItensFogueira[fromindex][slotid][S_ITEM_FOGUEIRA_ID] == itemid)
			{
            	s_ItensFogueira[fromindex][slotid][S_ITEM_FOGUEIRA_VALID] = false;
            	s_ItensFogueira[fromindex][slotid][S_ITEM_FOGUEIRA_ID] = -1;
            	
            	return 1;
			}
		}
	    return 0;
	}
	return 0;
}

callback s_UpdateFogueira(index)
{
	for(new slotid; slotid < MAX_ITENS_IN_FOGUEIRAS; slotid++)
	{
 		if (!s_ItensFogueira[index][slotid][S_ITEM_FOGUEIRA_VALID])
   			continue;

		new itemid = s_ItensFogueira[index][slotid][S_ITEM_FOGUEIRA_ID];

		if (Iter_Contains(iterDrops, itemid))
		{
		    if (GetPointDistanceToPoint(DropItensInfo[itemid][drop_x],DropItensInfo[itemid][drop_y],DropItensInfo[itemid][drop_z],s_FogueiraInfo[index][S_FOGUEIRA_X],s_FogueiraInfo[index][S_FOGUEIRA_Y],s_FogueiraInfo[index][S_FOGUEIRA_Z]) > 7.0)
			{
			    RemoveItemToServerFogueira(itemid, index);
				continue;
			}
		
		    switch (DropItensInfo[itemid][drop_type])
		    {
		        case ITEM_TYPE_CARNECRUA:
		        {
		            DropItensInfo[itemid][drop_health] += 1.0 + frandom(1.0);
		            
		            if (DropItensInfo[itemid][drop_health] >= 100.0)
		            {
		                changeDroppedItemInfo(itemid, "Carne assada", ITEM_TYPE_CARNEASSADA, 2804, DropItensInfo[itemid][drop_quantia], .health = 100.0);
		                RemoveItemToServerFogueira(itemid, index);
					}
		        }
		        case ITEM_TYPE_PEIXE:
		        {
		            DropItensInfo[itemid][drop_health] += 1.0 + frandom(1.0);

		            if (DropItensInfo[itemid][drop_health] >= 100.0)
		            {
		                changeDroppedItemInfo(itemid, "Peixe assado", ITEM_TYPE_PEIXEASSADO, 19630, DropItensInfo[itemid][drop_quantia], .health = 100.0);
		                RemoveItemToServerFogueira(itemid, index);
					}
		        }
    		}
		}
		else
		{
  			RemoveItemToServerFogueira(itemid, index);
	    }
	}
	if (gettime() > s_FogueiraInfo[index][S_FOGUEIRA_DESTROY])
	{
	    DestroyServerFogueira(index);
	}

	return 1;
}

