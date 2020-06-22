
#define MAX_BASES         		(200) // Maximo de bases
#define MAX_BASE_OBJECTS  		(150) // Maximo de objetos na base
#define DEFALT_MAX_OBJECTS      (75) // Numero maximo de objetos na base por padrao
#define MAX_BASE_OBJECT_RANGE   (60.0) // Limite de distancia que pode adicionar objetos na base
#define MAX_BASE_AUTHORIZED     (10) // Maximo de pessoas que estao autorizados a editar a base
#define MAX_BASE_DISTANCE_OTHER (2.0 * MAX_BASE_OBJECT_RANGE) // Minimo de distancia que uma base deve ter da outra
#define MAX_BASE_DAYS_CHECK     (86400 * 7)

#define txd_model_madeira       (17049)
#define txd_model_rocha       	(8498)
#define txd_model_ferro       	(5775)

#define MAX_SLOTS_BAU_PEQUENO   (15)
#define MAX_SLOTS_BAU_MEDIO     (25)
#define MAX_SLOTS_BAU_GRANDE    (45)

new PlayerText:textPlayerCraftBase[3];

new PlayerText:playerCraftBase[15];

new Text:textBaseCraft[5];

new playerSelectedItemId[MAX_PLAYERS];

enum enumBases {
	baseArea,
	baseLastCheck,
	baseNumbObjects,
	baseDestroy,
	baseLastExplode,
	baseArmarioPass[10],
	Float:baseX,
	Float:baseY,
	Float:baseZ,
}
stock serverBaseInfo[MAX_BASES][enumBases];
stock serverBaseAuthorized[MAX_BASES][MAX_BASE_AUTHORIZED][24];
stock Iterator:baseIter<MAX_BASES>;

enum enumBaseObjects {
	baseObjectValid,
	baseObjectModel,
	baseObjectId,
	baseObjectLastEdit,
	baseObjectMadeiraUsed,
	baseObjectRochaUsed,
	baseObjectMetalUsed,
	baseObjectColAndreasId,
	Text3D:baseObject3dText,
	baseObjectTextureModel,
	baseObjectTxdName[15],
	baseObjectTextureName[15],
	baseObjectPassword[5],
	baseObjectOwner[MAX_PLAYER_NAME],
	baseObjectLastSpawn,
	Float:baseObjectH,
	Float:baseObjectX,
	Float:baseObjectY,
	Float:baseObjectZ,
	Float:baseObjectRX,
	Float:baseObjectRY,
	Float:baseObjectRZ,
}
stock serverBaseObjects[MAX_BASES][MAX_BASE_OBJECTS][enumBaseObjects];

enum enumBaseObjectsCraft {
	baseCraftName[27],
	baseCraftModel,
	baseCraftMadeira,
	baseCraftRocha,
	baseCraftFerro,
	Float:baseCraftHealth,
	baseCraftTxdModel,
	baseCraftTxdName[15],
	baseCraftTexture[15],
	Float:baseCraftX,
	Float:baseCraftY,
	Float:baseCraftZ,
	Float:baseCraftOffset,
}
stock const baseObjectsCraft[][enumBaseObjectsCraft] = {
//          Nome                        modelid     madeira   rocha    ferro       vida      txdmodel      txdname        texture          rx   ry   rz   selectdistance
    {"Armario de autorizacao", 	 	 	 11729,       0,       0,       75,        1500.0,    0,          "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
    // Madeira
	{"Piso de madeira", 		     	 19791,       345,     0,       0,         700.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	12.0},
	{"Teto de madeira grande", 	     	 19458,       275,     0,       0,         650.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 90.0, 0.0, 	5.0},
	{"Teto de madeira pequeno", 	     19360,       138,     0,       0,         450.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 90.0, 0.0, 	4.0},
	{"Parede de madeira grande", 	     19452,       230,     0,       0,         590.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	6.0},
    {"Parede de madeira media", 	     19366,       185,     0,       0,         590.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.5},
	{"Parede de madeira pequena", 	     19433,       120,     0,       0,         590.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	4.0},
	{"Moldura porta de madeira", 	 	 19390,       100,     0,       0,         590.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Moldura janela de madeira", 	 	 19406,       115,     0,       0,         590.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Porta de madeira", 	 			 1497,        90,      0,       0,         620.0,      17049,      "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	// Pedra
	{"Piso de pedra", 		     		 19791,       0,       315,     0,         800.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	12.0},
	{"Teto de pedra grande", 	     	 19458,       0,       280,     0,         780.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 90.0, 0.0, 	5.0},
	{"Teto de pedra pequeno", 	     	 19360,       0,       145,     0,         600.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 90.0, 0.0, 	4.0},
	{"Parede de pedra grande", 	     	 19452,       0,       280,     0,         820.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	6.0},
    {"Parede de pedra media", 	     	 19366,       0,       220,     0,         820.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	3.5},
	{"Parede de pedra pequena", 	     19433,       0,       165,     0,         820.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	4.0},
	{"Moldura porta de pedra", 	 	 	 19390,       0,       115,     0,         820.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	3.0},
	{"Moldura janela de pedra", 	 	 19406,       0,       125,     0,         820.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	3.0},
	{"Porta de pedra", 	 				 1497,        0,       85,      0,         890.0,      8498,       "excalibur", "ws_sandstone2",  0.0, 0.0, 0.0, 	3.0},
	// Ferro
	{"Piso de metal", 		     		 19791,       0,       0,       300,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	12.0},
	{"Teto de metal grande", 	     	 19458,       0,       0,       265,       900.0,      5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 90.0, 0.0, 	5.0},
	{"Teto de metal pequeno", 	     	 19360,       0,       0,       140,       920.0,      5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 90.0, 0.0, 	4.0},
	{"Parede de metal grande", 	     	 19452,       0,       0,       275,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	6.0},
    {"Parede de metal media", 	     	 19366,       0,       0,       215,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	3.5},
	{"Parede de metal pequena", 	     19433,       0,       0,       160,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	4.0},
	{"Moldura porta de metal", 	 	 	 19390,       0,       0,       120,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	3.0},
	{"Moldura janela de metal", 	 	 19406,       0,       0,       125,       1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",  0.0, 0.0, 0.0, 	3.0},
	{"Porta de metal", 	 				 1497,        0,       0,       95,        1000.0,     5775,       "sunset01_lawn",  "ws_corr_metal2",   0.0, 0.0, 0.0, 	3.0},
	// Outros
	{"Cama", 	 	 		 			 1812,        0,       0,       100,       20.0,       0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	
	{"Barreira", 	 	 		 		 -1050,       20,      20,      0,         20.0,       0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Barreira de ferro", 	 	 		 -1051,       0,       0,       35,        40.0,       0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Barreira grande", 	 	 		 -1052,       50,      75,      0,         90.0,       0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Torre de madeira", 	 	 		 -1053,       200,     0,       0,         150.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	5.5},
	{"Tenda grande", 	 	 		 	 -1054,       200,     150,     50,        500.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	4.5},
	{"Tenda grande", 	 	 		 	 -1067,       210,     180,     75,        500.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.5},
	{"Poco de pedra", 	 	 		 	 -1070,       75,      200,     15,        200.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	
	{"Cerca de madeira", 	 	 		 -1055,       100,     0,       0,         150.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Muro de pedra", 	 	 		 	 -1056,       0,       100,     0,         200.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Muro de metal", 	 	 		 	 -1057,       0,       0,       100,       300.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	{"Muro de madeira", 	 	 		 -1058,       180,     0,       0,         180.0,     0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.5},
	
	{"Mesa de crafting", 	 	 		 2206,        175,     0,       0,         75.0,       0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Portao de madeira", 	 	 		 3049,        375,     0,       0,         325.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Escada", 	 	 		 			 1472,        45,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Escada grande", 	 	 			 10244,       380,     0,       0,         450.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	4.0},
	{"Escada de metal", 	 	 		 8572,        0,       0,       115,       710.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.5},
	{"Rampa de madeira", 	 	 		 1473,        35,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Cerca de madeira", 	 	 		 19865,       30,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Cerca de madeira 2", 	 	 		 1408,        45,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Muro de madeira grande", 	 	 	 19641,       75,      0,       5,         325.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	3.0},
	{"Prateleira de madeira", 	 	 	 19922,       68,      0,       0,         250.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Receptor de frequencia", 	 	 	 3350,        0,       0,       295,       55.00,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Banco", 	 	 				 	 1368,        42,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Lareira", 	 	 				 11725,       35,      0,       63,        100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Teto solar", 	 	 				 1697,        0,       0,       118,       100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	4.0},
	{"Cadeira", 	 	 				 1810,        35,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0},
	{"Torre de controle", 	 	 		 3279,        0,       0,       440,       1000.0,     0,          "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	7.0},
	{"Ponte de madeira", 	 	 		 19588,       150,     0,       0,         500.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	7.0},
	{"Bau pequeno", 	 	 			 2969,        70,      0,       0,         100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	1.0},
	{"Bau medio", 	 	 			 	 3014,        100,     0,       0,         125.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	1.0},
	{"Bau grande", 	 	 			 	 3015,        145,     0,       0,         300.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	1.0},
	{"Anti Aircraft", 	 	 		 	 18848,       0,       0,       200,       100.0,      0,      	   "cuntwf",    "sw_barnwood5",   0.0, 0.0, 0.0, 	2.0}
};

#define MAX_PAGES_CRAFT_BASES ((sizeof(baseObjectsCraft) / 15))

stock createServerBase(Float:x, Float:y, Float:z, authorize[] = "---")
{
	new index = Iter_Free(baseIter);
	
	if (index != -1)
	{
	    // Add iterator
	    Iter_Add(baseIter, index);
	    
	    // Save the coords
		serverBaseInfo[index][baseX] = x;
		serverBaseInfo[index][baseY] = y;
		serverBaseInfo[index][baseZ] = z;
		
		serverBaseInfo[index][baseArea] = CreateDynamicSphere(x, y, z, MAX_BASE_OBJECT_RANGE);
		serverBaseInfo[index][baseLastCheck] = gettime() + MAX_BASE_DAYS_CHECK;
		serverBaseInfo[index][baseNumbObjects] = DEFALT_MAX_OBJECTS;
		serverBaseInfo[index][baseDestroy] = 0;
		serverBaseInfo[index][baseLastExplode] = 0;
		format(serverBaseInfo[index][baseArmarioPass], 75, "0000");
		
		format(serverBaseAuthorized[index][0], 24, authorize);
		for(new authorized = 1; authorized < MAX_BASE_AUTHORIZED; authorized++)
		{
		    format(serverBaseAuthorized[index][authorized], 24, "---");
		}
		
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
		    format(serverBaseObjects[index][index_object][baseObjectOwner], 24, "Ninguém");
		    serverBaseObjects[index][index_object][baseObjectLastSpawn] = 0;
		    serverBaseObjects[index][index_object][baseObjectValid] = 0;
		    serverBaseObjects[index][index_object][baseObjectModel] = 255;
		    serverBaseObjects[index][index_object][baseObjectH] = 1000.0;
		    serverBaseObjects[index][index_object][baseObjectX] = 0.0;
		    serverBaseObjects[index][index_object][baseObjectY] = 0.0;
		    serverBaseObjects[index][index_object][baseObjectZ] = 0.0;
		    serverBaseObjects[index][index_object][baseObjectRX] = 0.0;
		    serverBaseObjects[index][index_object][baseObjectRY] = 0.0;
		    serverBaseObjects[index][index_object][baseObjectRZ] = 0.0;
		}
		createBaseDatabase(index);
		
		Log::("base", "CREATE\t\t|%d created", index);
	}
	return index;
}

stock serverBaseDestroy(index, destroyloots = 1) {

	if (Iter_Contains(baseIter, index))
	{
		Iter_Remove(baseIter, index);
		
		DestroyDynamicArea(serverBaseInfo[index][baseArea]);
		
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
		    if (serverBaseObjects[index][index_object][baseObjectValid])
			{
			    if (destroyloots)
			    {
					foreach(new loot : iterLoots)
					{
					    if (LootInfo[loot][loot_baseid] == index && LootInfo[loot][loot_object][0] == serverBaseObjects[index][index_object][baseObjectId])
						{
						    destroyLoot(loot);
					        break;
					    }
					}
				}
			    serverBaseObjects[index][index_object][baseObjectValid] = 0;
			    DestroyDynamicObject(serverBaseObjects[index][index_object][baseObjectId]);
			    DestroyDynamic3DTextLabel(serverBaseObjects[index][index_object][baseObject3dText]);
			    
			    // ColAndreas
			    if (serverBaseObjects[index][index_object][baseObjectModel] > 0)
			    {
			    	CA_DestroyObject(serverBaseObjects[index][index_object][baseObjectColAndreasId]);
				}
			}
		}
		
		new query[75];
		format(query, sizeof query, "delete from `bases` where `id` = '%d';", index);
	    db_free_result(db_query(serverBasesDB, query));

        Log::("base", "DESTROY\t\t|%d destroyed", index);

	    return 1;
	}
	return 0;
}

stock serverBaseHaveArmario(index)
{
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 11729)
		{
			return 1;
		}
	}

	return 0;
}

stock IsPlayerInCraftTable(playerid) {

	new index = getPlayerBase(playerid);
	
	if (index != -1) {
	
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 2206)
			{
				if (IsPlayerInRangeOfPoint(playerid, 2.1, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
				{
				    return 1;
				}
			}
		}
	}
	return 0;
}

stock IsPlayerInBaseArmario(playerid, index)
{
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 11729)
		{
			if (IsPlayerInRangeOfPoint(playerid, 1.3, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
			{
			    return 1;
			}
		}
	}

	return 0;
}

stock getPlayerBaseBed(playerid, index)
{
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 1812)
		{
			if (IsPlayerInRangeOfPoint(playerid, 2.0, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
			{
			    return index_object;
			}
		}
	}

	return -1;
}

stock getPlayerBaseObject(playerid, index, &objecti)
{
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && (serverBaseObjects[index][index_object][baseObjectModel] == 1812 || serverBaseObjects[index][index_object][baseObjectModel] == 2206))
		{
			if (IsPlayerInRangeOfPoint(playerid, 2.0, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
			{
			    objecti = index_object;
			    return serverBaseObjects[index][index_object][baseObjectModel];
			}
		}
	}

	return -1;
}

stock GetBaseArmarioPos(index, &Float:x, &Float:y, &Float:z) {

	if (!Iter_Contains(baseIter, index))
	    return 0;

	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 11729)
		{
		    x = serverBaseObjects[index][index_object][baseObjectX];
		    y = serverBaseObjects[index][index_object][baseObjectY];
		    z = serverBaseObjects[index][index_object][baseObjectZ];
			return 1;
		}
	}
	
	x = serverBaseInfo[index][baseX];
	y = serverBaseInfo[index][baseY];
	z = serverBaseInfo[index][baseZ];
	
	return 1;
}

stock GetPlayerBaseDoor(playerid, index) {

	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && (serverBaseObjects[index][index_object][baseObjectModel] == 1497 || serverBaseObjects[index][index_object][baseObjectModel] == 3049))
		{
			if (IsPlayerInRangeOfPoint(playerid, serverBaseObjects[index][index_object][baseObjectModel] == 3049 ? (6.0) : (2.0), serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
			{
			    return index_object;
			}
		}
	}

	return -1;
}

stock ClearAllSpawnsByName(name[])
{
	foreach(new index : baseIter)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 1812)
			{
				if (!strcmp(serverBaseObjects[index][index_object][baseObjectOwner], name))
				{
				    format(serverBaseObjects[index][index_object][baseObjectOwner], 24, "Ninguém");
				    serverBaseSaveObject(index, index_object);
				}
			}
		}
	}
}

stock getPlayerBaseSpawn(playerid, &Float:x, &Float:y, &Float:z)
{
	foreach(new index : baseIter)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 1812)
			{
				if (!strcmp(serverBaseObjects[index][index_object][baseObjectOwner], getNome(playerid)))
				{
				    if (serverBaseObjects[index][index_object][baseObjectLastSpawn] > gettime())
				    {
				        SendClientMessagef(playerid, corError, "ERRO: {999999}Você poderá respawnar em sua cama novamente em %d segundos.", serverBaseObjects[index][index_object][baseObjectLastSpawn] - gettime());
				        return 0;
				    }
				
				    serverBaseObjects[index][index_object][baseObjectLastSpawn] = gettime() + (5 * 60);
				    x = serverBaseObjects[index][index_object][baseObjectX];
				    y = serverBaseObjects[index][index_object][baseObjectY];
				    z = serverBaseObjects[index][index_object][baseObjectZ] + 0.8;
				    return 1;
				}
			}
		}
	}
	SendClientMessage(playerid, corError, "ERRO: {999999}Você não possui uma cama em uma base.");
	return 0;
}

stock updateBaseBauPosition(index, index_object) {

	foreach(new loot : iterLoots)
	{
	    if (LootInfo[loot][loot_baseid] == index && LootInfo[loot][loot_object][0] == serverBaseObjects[index][index_object][baseObjectId])
		{
//		    printf("loot: %d, index_object: %d", loot, LootInfo[loot][loot_object][0]);
		
		    LootInfo[loot][loot_x] = serverBaseObjects[index][index_object][baseObjectX];
		    LootInfo[loot][loot_y] = serverBaseObjects[index][index_object][baseObjectY];
		    LootInfo[loot][loot_z] = serverBaseObjects[index][index_object][baseObjectZ];
	    
	        //AttachDynamicAreaToObject(LootInfo[loot][loot_area], serverBaseObjects[index][index_object][baseObjectId]);
	        Streamer_SetFloatData(STREAMER_TYPE_AREA, LootInfo[loot][loot_area], E_STREAMER_X, serverBaseObjects[index][index_object][baseObjectX]);
	        Streamer_SetFloatData(STREAMER_TYPE_AREA, LootInfo[loot][loot_area], E_STREAMER_Y, serverBaseObjects[index][index_object][baseObjectY]);
	        Streamer_SetFloatData(STREAMER_TYPE_AREA, LootInfo[loot][loot_area], E_STREAMER_Z, serverBaseObjects[index][index_object][baseObjectZ]);
	    
	        saveTent(loot);
	    
	        break;
	    }
	}
}

stock serverBaseAddObject(index, modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:health, txdmodel, txdname[], texturename[], password[] = "none") {

	if (GetPointDistanceToPoint(x, y, z, serverBaseInfo[index][baseX], serverBaseInfo[index][baseY], serverBaseInfo[index][baseZ]) > MAX_BASE_OBJECT_RANGE)
	    return -2;
	    
	if (modelid == 11729 && serverBaseHaveArmario(index)) {
	    return -3;
	}

	for(new index_object; index_object < serverBaseInfo[index][baseNumbObjects]; index_object++)
	{
		if (!serverBaseObjects[index][index_object][baseObjectValid])
		{
		    new string[15];
 		    format(serverBaseObjects[index][index_object][baseObjectOwner], 24, "Ninguém");
		    serverBaseObjects[index][index_object][baseObjectLastSpawn] = 0;
			serverBaseObjects[index][index_object][baseObjectValid] = 1;
	   		serverBaseObjects[index][index_object][baseObjectModel] = modelid;
		    serverBaseObjects[index][index_object][baseObjectH] = health;
		    serverBaseObjects[index][index_object][baseObjectX] = x;
		    serverBaseObjects[index][index_object][baseObjectY] = y;
		    serverBaseObjects[index][index_object][baseObjectZ] = z;
		    serverBaseObjects[index][index_object][baseObjectRX] = rx;
		    serverBaseObjects[index][index_object][baseObjectRY] = ry;
		    serverBaseObjects[index][index_object][baseObjectRZ] = rz;
		    serverBaseObjects[index][index_object][baseObjectLastEdit] = 0;
		    format(string, sizeof string, "%.0f%%", serverBaseObjects[index][index_object][baseObjectH]);
		    serverBaseObjects[index][index_object][baseObject3dText] = CreateDynamic3DTextLabel(string, 0xFFFFFF55, x, y, z, 1.6, .worldid = 0);
		    serverBaseObjects[index][index_object][baseObjectId] = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, 0, .streamdistance = 400.0, .drawdistance = 400.0);
		    serverBaseObjects[index][index_object][baseObjectTextureModel] = txdmodel;
		    format(serverBaseObjects[index][index_object][baseObjectTxdName], 15, txdname);
		    format(serverBaseObjects[index][index_object][baseObjectTextureName], 15, texturename);
		    format(serverBaseObjects[index][index_object][baseObjectPassword], 5, password);
		    
		    if (txdmodel != 0)
			{
				if (modelid == 1497)
				{
				    //SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, txdmodel, txdname, texturename);
				    SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
				}
				else
				{
		    		//SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, txdmodel, txdname, texturename);
		    		SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
				}
			}
			else
			{
   				for(new idx; idx < 15; idx++)
   				{
					SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], idx, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
				}
			}
			

		 	if (modelid == 2969)
			{
		 	    new loot = createLoot(x, y, z, 0, LOOT_TYPE_TENDA, .createobject=true, .create3dtext=false, .raycast=false, .slots=MAX_SLOTS_BAU_PEQUENO, .world=0, .attachobject = serverBaseObjects[index][index_object][baseObjectId]);
	       	    LootInfo[loot][loot_baseid] = index;
		    	LootInfo[loot][loot_baseobj] = index_object;
		    	saveTent(loot);
			}
		 	else if (modelid == 3014)
			{
		 	    new loot = createLoot(x, y, z, 0, LOOT_TYPE_TENDA, .createobject=true, .create3dtext=false, .raycast=false, .slots=MAX_SLOTS_BAU_MEDIO, .world=0, .attachobject = serverBaseObjects[index][index_object][baseObjectId]);
	       	    LootInfo[loot][loot_baseid] = index;
		    	LootInfo[loot][loot_baseobj] = index_object;
		    	saveTent(loot);
			}
		 	else if (modelid == 3015)
			{
		 	    new loot = createLoot(x, y, z, 0, LOOT_TYPE_TENDA, .createobject=true, .create3dtext=false, .raycast=false, .slots=MAX_SLOTS_BAU_GRANDE, .world=0, .attachobject = serverBaseObjects[index][index_object][baseObjectId]);
	       	    LootInfo[loot][loot_baseid] = index;
		    	LootInfo[loot][loot_baseobj] = index_object;
		    	saveTent(loot);
			}
			
		    //SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, txdmodel, txdname, texturename);
		    //SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 2, txdmodel, txdname, texturename);
		    serverBaseSaveObject(index, index_object);
		    
			// ColAndreas
			if (serverBaseObjects[index][index_object][baseObjectModel] > 0)
			{
				serverBaseObjects[index][index_object][baseObjectColAndreasId] = CA_CreateObject(modelid, x, y, z, rx, ry, rz, true);
			}
		    
		    Log::("base", "OBJECT ADD\t\t|base %d add object %d on %f %f %f", index, modelid, x, y, z);
		    
		    return serverBaseObjects[index][index_object][baseObjectId];
		}
	}
	return -1;
}

stock isObjectUpgrade(modelid) {

	for(new index; index < sizeof baseObjectsCraft; index++)
	{
	    if (modelid == baseObjectsCraft[index][baseCraftModel] && baseObjectsCraft[index][baseCraftTxdModel] != 0)
		{
	        return 1;
	    }
	}
	return 0;
}

stock upgradeGetInfo(modelid, materialtype, &madeira, &rocha, &ferro)
{
	for(new index; index < sizeof baseObjectsCraft; index++)
	{
	    if (modelid == baseObjectsCraft[index][baseCraftModel] && baseObjectsCraft[index][baseCraftTxdModel] == materialtype)
		{
	        madeira = baseObjectsCraft[index][baseCraftMadeira];
	        rocha = baseObjectsCraft[index][baseCraftRocha];
	        ferro = baseObjectsCraft[index][baseCraftFerro];
	    
	        return 1;
	    }
	}
	return 0;
}

stock CountBaseObjects(index) {
	new count;
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid])
		{
		    count++;
		}
	}
	return count;
}

stock SendBaseRadioMessage(playerid, message[], color) {

	if (GetPlayerVirtualWorld(playerid) != 0)
	    return 0;

	foreach(new index : baseIter)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == 3350)
			{
			    if (!IsPlayerInRangeOfPoint(playerid, 200.0, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
					continue;
					
				SendMessageInRange(message, color, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], .range=10.0, .world = 0);
				
				Play3DSound(47, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 10.0, GetPlayerVirtualWorld(playerid));

				applyRuido(serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], ALTURA_RADIO, MAX_ALTURA_RADIO);
				
				return 1;
			}
		}
	}
	return 0;
}

stock IsPlayerInPoco(playerid)
{
	if (GetPlayerVirtualWorld(playerid) != 0)
	    return 0;

    new index = getPlayerBase(playerid);

	if (index == -1)
	    return 0;
	    
	for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectModel] == -1070)
		{
		    if (IsPlayerInRangeOfPoint(playerid, 2.0, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]))
				return 1;
   		}
	}
	
	return 0;
}


stock CreateBaseExplosion(Float:x, Float:y, Float:z, Float:maxdamage = 65.0, Float:maxrange = 5.0, type = 1)
{
	new index = -1;

	foreach(new i : baseIter) {
	
	    if (IsPointInDynamicArea(serverBaseInfo[i][baseArea], x, y, z)) {
	        index = i;
			break;
	    }
	}

	CreateExplosionEx(x, y, z, type, maxrange, 0);

	if (index == -1) return 1;

	new string[48];
	new orderObjects[MAX_BASE_OBJECTS] = { -1, ... };
	new Float:rangeObjects[MAX_BASE_OBJECTS] = { 999.0, ... };
	new maxobjects = serverBaseInfo[index][baseNumbObjects];

	for(new index_object; index_object < maxobjects; index_object++)
	{
		if (serverBaseObjects[index][index_object][baseObjectValid])
		{
		    // get a distance to explosion
			new Float:rg = GetPointDistanceToPoint(x, y, z, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]);

			if (rg < maxrange)
			{
			    for(new obj; obj < maxobjects; obj++) {
			    
			        if (rg < rangeObjects[obj]) {
			        
			            for(new next = maxobjects - 1; next > obj; next--) {
			            	orderObjects[next] = orderObjects[next - 1];
			            	rangeObjects[next] = rangeObjects[next - 1];
			            }
			        
			            orderObjects[obj] = index_object;
			            rangeObjects[obj] = rg;
			            
			            break;
			        }
			    }
			}
		}
	}
	
	// damage
	for (new obj; obj < MAX_BASE_OBJECTS; obj++) {
	
	    new index_object = orderObjects[obj];
	    
	    if (index_object != -1) {
	    	new Float:damage = maxdamage - (50.0 * rangeObjects[obj]);

		    maxdamage = maxdamage / 1.2;

			if (damage > 0.0)
			{
		    	serverBaseObjects[index][index_object][baseObjectH] -= damage;
		    	serverBaseInfo[index][baseLastExplode] = gettime() + (5 * 60);
			}
			else
			    damage = 0.0;

			format(string, sizeof string, "%.0f%%", serverBaseObjects[index][index_object][baseObjectH]);
			UpdateDynamic3DTextLabelText(serverBaseObjects[index][index_object][baseObject3dText], 0xFFFFFF55, string);

            Log::("base", "OBJECT DAMAGE\t\t|base %d damaged object %d - %.1f hp", index, index_object, damage);

		    if (serverBaseObjects[index][index_object][baseObjectH] <= 0.0)
		    {
		        serverBaseRemoveObject(index, index_object);
		    }
		    else
		    {
		        serverBaseSaveObject(index, index_object);
		    }
	    }
	}
	return 1;
}

stock upgradeBaseObject(index, index_object, materialtype)
{
	for(new id; id < sizeof baseObjectsCraft; id++)
	{
	    if (serverBaseObjects[index][index_object][baseObjectModel] == baseObjectsCraft[id][baseCraftModel] && baseObjectsCraft[id][baseCraftTxdModel] == materialtype)
		{
		    serverBaseObjects[index][index_object][baseObjectTextureModel] = baseObjectsCraft[id][baseCraftTxdModel];
		    format(serverBaseObjects[index][index_object][baseObjectTxdName], 15, baseObjectsCraft[id][baseCraftTxdName]);
		    format(serverBaseObjects[index][index_object][baseObjectTextureName], 15, baseObjectsCraft[id][baseCraftTexture]);
		    serverBaseObjects[index][index_object][baseObjectH] = baseObjectsCraft[id][baseCraftHealth];
		    serverBaseObjects[index][index_object][baseObjectLastEdit] = gettime() + (5 * 60);

			new string[15];
		  	format(string, sizeof string, "%.0f%%", serverBaseObjects[index][index_object][baseObjectH]);
			UpdateDynamic3DTextLabelText(serverBaseObjects[index][index_object][baseObject3dText], 0xFFFFFF55, string);

			if (serverBaseObjects[index][index_object][baseObjectModel] == 1497)
			{
				SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, serverBaseObjects[index][index_object][baseObjectTextureModel],
				serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
		    }
			else
			{
				SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, serverBaseObjects[index][index_object][baseObjectTextureModel],
				serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
			}
			
			serverBaseSaveObject(index, index_object);

            Log::("base", "OBJECT UPGRADE\t\t|base %d upgrade object %d to %d material", index, index_object, materialtype);

	        return 1;
	    }
	}
	return 0;
}

stock serverBaseRemoveObject(index, index_object)
{
	if (serverBaseObjects[index][index_object][baseObjectValid])
	{
		foreach(new loot : iterLoots)
		{
		    if (LootInfo[loot][loot_baseid] == index && LootInfo[loot][loot_object][0] == serverBaseObjects[index][index_object][baseObjectId])
			{
			    for(new itens; itens != MAX_ITENS_LOOT; itens++)
				{
			        if (LootItensInfo[loot][itens][item_valid])
			        {
		                createDroppedItem(serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ],
						LootItensInfo[loot][itens][item_nome], LootItensInfo[loot][itens][item_type], LootItensInfo[loot][itens][item_model], LootItensInfo[loot][itens][item_quantia], .raycast=true, .world=0, .randomize = true, .health = LootItensInfo[loot][itens][item_health]);
		            }
			  	}
			
			    destroyLoot(loot);
		        break;
		    }
		}
	
 		serverBaseObjects[index][index_object][baseObjectValid] = 0;
	    serverBaseObjects[index][index_object][baseObjectModel] = 255;
	    serverBaseObjects[index][index_object][baseObjectH] = 1000.0;
	    serverBaseObjects[index][index_object][baseObjectX] = 0.0;
	    serverBaseObjects[index][index_object][baseObjectY] = 0.0;
	    serverBaseObjects[index][index_object][baseObjectZ] = 0.0;
	    serverBaseObjects[index][index_object][baseObjectRX] = 0.0;
	    serverBaseObjects[index][index_object][baseObjectRY] = 0.0;
	    serverBaseObjects[index][index_object][baseObjectRZ] = 0.0;
	    DestroyDynamicObject(serverBaseObjects[index][index_object][baseObjectId]);
	    DestroyDynamic3DTextLabel(serverBaseObjects[index][index_object][baseObject3dText]);
	    serverBaseSaveObject(index, index_object);

	    // ColAndreas
	    CA_DestroyObject(serverBaseObjects[index][index_object][baseObjectColAndreasId]);
	    
	    Log::("base", "OBJECT DESTROY\t\t|base %d destroyed object %d", index, index_object);
	}
	// destroy the base if not objects
	if (CountBaseObjects(index) < 1) {
	    // destroy the base
	    serverBaseDestroy(index, .destroyloots = 0);
	}
	return 0;
}

stock createBaseDatabase(index) {
	new query[208];
	format(query, sizeof query, "INSERT INTO `bases` (`id`,`lastcheck`,`nobjects`,`nucleo_x`,`nucleo_y`,`nucleo_z`) VALUES ('%d','%d','%d','%.2f','%.2f','%.2f');",
	index, serverBaseInfo[index][baseLastCheck], serverBaseInfo[index][baseNumbObjects], serverBaseInfo[index][baseX], serverBaseInfo[index][baseY], serverBaseInfo[index][baseZ]);
    db_free_result(db_query(serverBasesDB, query));
}
stock SetBaseLimitObjects(index, limit) {
	if (serverBaseInfo[index][baseNumbObjects] == limit)
	    return 0;
	    
    serverBaseInfo[index][baseNumbObjects] = limit;
	    
	new query[75];
	format(query, sizeof query, "UPDATE bases SET nobjects = '%d' WHERE id = '%d';", limit, index);
	db_free_result(db_query(serverBasesDB, query));
	    
    Log::("base", "OBJ LIMIT\t\t|base %d limit set %d", index, limit);
	    
	return 1;
}

stock SetBaseArmarioPass(index, password[]) {

    format(serverBaseInfo[index][baseArmarioPass], 144, password);

	new query[200];
	format(query, sizeof query, "UPDATE bases SET apass = '%s' WHERE id = '%d';", password, index);
	db_free_result(db_query(serverBasesDB, query));

    Log::("base", "ARMARIO PASS\t\t|base %d password %s", index, password);

	return 1;
}

stock SetBaseDestroy(index, value) {

	serverBaseInfo[index][baseDestroy] = value;

	new query[75];
	format(query, sizeof query, "UPDATE bases SET destroy = '%d' WHERE id = '%d';", value, index);
	db_free_result(db_query(serverBasesDB, query));

	return 1;
}

stock authorizeNickname(index, name[]) {

	for (new id = MAX_BASE_AUTHORIZED - 1; id > 0; id--)
	{
	    format(serverBaseAuthorized[index][id], 24, serverBaseAuthorized[index][id - 1]);
	}
	format(serverBaseAuthorized[index][0], 24, name);
	serverBaseSaveAuthorized(index);
	
	Log::("base", "AUTHORIZE\t\t|base %d authorized %s", index, name);
}

stock clearAuthorize(index)
{
	for (new id = MAX_BASE_AUTHORIZED - 1; id > -1; id--)
	{
	    new playerid = getId(serverBaseAuthorized[index][id]);

		if (playerid != INVALID_PLAYER_ID && getPlayerBase(playerid) == index)
		{
	        PlayerTextDrawSetString(playerid, textAuthorize[playerid], "~r~~h~Construcao bloqueada");
	        // Esconder dialog
	        ShowPlayerDialog(playerid, -1, 0, " ", "invalid dialog", "ok", "");
	    }
	
	    format(serverBaseAuthorized[index][id], 24, "---");
	}
	serverBaseSaveAuthorized(index);
	
	Log::("base", "CLEAR AUTHORIZE\t\t|base %d clear authorize", index);
}

stock IsNicknameAuthorized(index, name[]) {

	if (!serverBaseHaveArmario(index))
	    return 1;
	    
	if (!strcmp(name, "dimmy_scarface"))
	    return 1;

	for (new id = MAX_BASE_AUTHORIZED - 1; id > -1; id--)
	{
	    if (!strcmp(serverBaseAuthorized[index][id], name)) return 1;
	}
	return 0;
}

stock countPlayerBases(playerid) {

	new count;
	
	foreach(new index : baseIter)
	{
	    if (IsNicknameAuthorized(index, getNome(playerid)) && serverBaseHaveArmario(index)) count++;
	}

	return count;
}

stock UpdateBaseDoorState(index, index_object) {

	if ((serverBaseObjects[index][index_object][baseObjectModel] != 1497 && serverBaseObjects[index][index_object][baseObjectModel] != 3049) || IsDynamicObjectMoving(serverBaseObjects[index][index_object][baseObjectId]))
	    return 0;

	static
	    Float:rx,
	    Float:ry,
		Float:rz;
		
	GetDynamicObjectRot(serverBaseObjects[index][index_object][baseObjectId], rx, ry, rz);

	if (serverBaseObjects[index][index_object][baseObjectRZ] == rz)
	{
	    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497) {
		    MoveDynamicObject(serverBaseObjects[index][index_object][baseObjectId],
			serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ] + 0.01, 0.02,
			serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ] + 85.0);
			Play3DSound(48, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 25.0);
		}
	    else if (serverBaseObjects[index][index_object][baseObjectModel] == 3049) {
		    MoveDynamicObject(serverBaseObjects[index][index_object][baseObjectId],
			serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ] + 0.01, 0.005,
			serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ] + 85.0);
			Play3DSound(68, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 25.0, .soundid = 12200);
		}
		// ColAndreas
		CA_SetObjectRot(serverBaseObjects[index][index_object][baseObjectColAndreasId], serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ] + 85.0);
	}
	else
	{
	    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497) {
		    MoveDynamicObject(serverBaseObjects[index][index_object][baseObjectId],
			serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 0.02,
			serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ]);
			Play3DSound(49, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 25.0);
		}
	    else if (serverBaseObjects[index][index_object][baseObjectModel] == 3049) {
		    MoveDynamicObject(serverBaseObjects[index][index_object][baseObjectId],
			serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 0.005,
			serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ]);
			Play3DSound(69, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ], 25.0, .soundid = 12200);
		}

		// ColAndreas
		CA_SetObjectRot(serverBaseObjects[index][index_object][baseObjectColAndreasId], serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ]);
	}

	return 1;
}

stock getPlayerBase(playerid)
{
	new index = GetPVarInt(playerid, "playerInBase");
	
	if (!Iter_Contains(baseIter, index))
	    return -1;

	return index;
}

stock getPlayerBaseEx(playerid)
{
	foreach(new index : baseIter)
	{
	    if (IsPlayerInRangeOfPoint(playerid, MAX_BASE_OBJECT_RANGE, serverBaseInfo[index][baseX], serverBaseInfo[index][baseY], serverBaseInfo[index][baseZ]))
		{
	        return index;
	    }
	}

	return -1;
}

stock getPlayerBaseProx(playerid) {

	foreach(new index : baseIter)
	{
	    if (IsPlayerInRangeOfPoint(playerid, (MAX_BASE_OBJECT_RANGE * 2.0) + 25.0, serverBaseInfo[index][baseX], serverBaseInfo[index][baseY], serverBaseInfo[index][baseZ]))
		{
	        return 1;
	    }
	}
	return 0;
}

stock IsPlayerInAnyBase(playerid)
{
	new index = getPlayerBase(playerid);
	if (index != -1) return 1;
	return 0;
}

stock serverBaseSaveAuthorized(index)
{
	new query[456];
	new string[MAX_BASE_AUTHORIZED * MAX_PLAYER_NAME + 55];

    strcat(string, serverBaseAuthorized[index][0]);

	for(new authorized = 1; authorized < MAX_BASE_AUTHORIZED; authorized++)
	{
	    strcat(string, ",");
	    strcat(string, serverBaseAuthorized[index][authorized]);
	}

	format(query, sizeof query, "update `bases` set `authorized` = '%s' where `id` = '%d';", string, index);
    db_free_result(db_query(serverBasesDB, query));
}

stock serverBaseSaveObject(index, index_object) {

	new query[256];
	format(query, sizeof query, "UPDATE `bases` SET `obj_%d` = '%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%s,%s,%s,%s' WHERE `id` = '%d';",
	index_object, serverBaseObjects[index][index_object][baseObjectValid], serverBaseObjects[index][index_object][baseObjectModel], serverBaseObjects[index][index_object][baseObjectH],
	serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ],
    serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], serverBaseObjects[index][index_object][baseObjectRZ],
	serverBaseObjects[index][index_object][baseObjectTextureModel], serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName],
	serverBaseObjects[index][index_object][baseObjectPassword], serverBaseObjects[index][index_object][baseObjectOwner], index);

//	printf(query);

	db_free_result(db_query(serverBasesDB, query));
}

stock CheckBaseActivity(index) {

    serverBaseInfo[index][baseLastCheck] = gettime() + MAX_BASE_DAYS_CHECK;

	new query[75];
	format(query, sizeof query, "UPDATE `bases` SET `lastcheck` = '%d' WHERE `id` = '%d';", serverBaseInfo[index][baseLastCheck], index);
    db_free_result(db_query(serverBasesDB, query));
}

stock loadBases()
{
	for(new index; index < MAX_BASES; index++)
	{
	    serverBaseLoad(index);
	}
}

stock serverBaseLoad(index) {
	Iter_Remove(baseIter, index);
	
	new DBResult:resultQuery;
	new query[128];
	
	// Query
	format(query, sizeof query, "select * from `bases` WHERE `id` = '%d'", index);
	resultQuery = db_query(serverBasesDB, query);
	
	// Checar se existe
	if (db_num_rows(resultQuery) > 0)
	{
		// Variaveis
	    new splitRead[MAX_BASE_AUTHORIZED * MAX_PLAYER_NAME + 55];
	    new splitStringRead[25][MAX_PLAYER_NAME];
	
		// Add a base na lista
	    Iter_Add(baseIter, index);
	    
	    // Carregar a posição
		serverBaseInfo[index][baseX] = db_get_field_assoc_float(resultQuery, "nucleo_x");
		serverBaseInfo[index][baseY] = db_get_field_assoc_float(resultQuery, "nucleo_y");
		serverBaseInfo[index][baseZ] = db_get_field_assoc_float(resultQuery, "nucleo_z");
		serverBaseInfo[index][baseLastCheck] = db_get_field_assoc_int(resultQuery, "lastcheck");
		serverBaseInfo[index][baseNumbObjects] = db_get_field_assoc_int(resultQuery, "nobjects");
		serverBaseInfo[index][baseDestroy] = db_get_field_assoc_int(resultQuery, "destroy");
		db_get_field_assoc(resultQuery, "apass", serverBaseInfo[index][baseArmarioPass], 10);
		if (strlen(serverBaseInfo[index][baseArmarioPass]) < 1)
		    format(serverBaseInfo[index][baseArmarioPass], 10, "0000");

        serverBaseInfo[index][baseArea] = CreateDynamicSphere(serverBaseInfo[index][baseX], serverBaseInfo[index][baseY], serverBaseInfo[index][baseZ], MAX_BASE_OBJECT_RANGE);

		// Carregar autorizados a mexer na base
		db_get_field_assoc(resultQuery, "authorized", splitRead, sizeof (splitRead));
		split(splitRead, splitStringRead, ',');

		for(new authorized; authorized < MAX_BASE_AUTHORIZED; authorized++)
		{
		    format(serverBaseAuthorized[index][authorized], 24, splitStringRead[authorized]);
		}

		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			// Carregar informações
			format(query, sizeof query, "obj_%d", index_object);
			db_get_field_assoc(resultQuery, query, splitRead, sizeof (splitRead));
			split(splitRead, splitStringRead, ',');

			// Setar as informações
			serverBaseObjects[index][index_object][baseObjectValid] = strval(splitStringRead[0]);
		    serverBaseObjects[index][index_object][baseObjectModel] = strval(splitStringRead[1]);
		    serverBaseObjects[index][index_object][baseObjectH] = floatstr(splitStringRead[2]);
		    serverBaseObjects[index][index_object][baseObjectX] = floatstr(splitStringRead[3]);
		    serverBaseObjects[index][index_object][baseObjectY] = floatstr(splitStringRead[4]);
		    serverBaseObjects[index][index_object][baseObjectZ] = floatstr(splitStringRead[5]);
		    serverBaseObjects[index][index_object][baseObjectRX] = floatstr(splitStringRead[6]);
		    serverBaseObjects[index][index_object][baseObjectRY] = floatstr(splitStringRead[7]);
		    serverBaseObjects[index][index_object][baseObjectRZ] = floatstr(splitStringRead[8]);
		    serverBaseObjects[index][index_object][baseObjectTextureModel] = strval(splitStringRead[9]);
		    format(serverBaseObjects[index][index_object][baseObjectTxdName], 15, splitStringRead[10]);
		    format(serverBaseObjects[index][index_object][baseObjectTextureName], 15, splitStringRead[11]);
		    format(serverBaseObjects[index][index_object][baseObjectPassword], 5, splitStringRead[12]);
		    format(serverBaseObjects[index][index_object][baseObjectOwner], MAX_PLAYER_NAME, splitStringRead[13]);
		    serverBaseObjects[index][index_object][baseObjectLastSpawn] = 0;
		    if (strlen(serverBaseObjects[index][index_object][baseObjectOwner]) < 1)
		        format(serverBaseObjects[index][index_object][baseObjectOwner], MAX_PLAYER_NAME, "Ninguém");
		    
		    if (serverBaseObjects[index][index_object][baseObjectValid])
			{
		        // Criar o objeto
		    	serverBaseObjects[index][index_object][baseObjectId] = CreateDynamicObject(serverBaseObjects[index][index_object][baseObjectModel],
				serverBaseObjects[index][index_object][baseObjectX],serverBaseObjects[index][index_object][baseObjectY],serverBaseObjects[index][index_object][baseObjectZ],
				serverBaseObjects[index][index_object][baseObjectRX],serverBaseObjects[index][index_object][baseObjectRY],serverBaseObjects[index][index_object][baseObjectRZ], 0, .streamdistance = 400.0, .drawdistance = 400.0);

				if (serverBaseObjects[index][index_object][baseObjectModel] == 11729 && serverBaseObjects[index][index_object][baseObjectH] > 1500.0)
				{
				    serverBaseObjects[index][index_object][baseObjectH] = 1500.0;
				}

				// Criar a 3d label
				new string[15];
			    format(string, sizeof string, "%.0f%%", serverBaseObjects[index][index_object][baseObjectH]);
			    serverBaseObjects[index][index_object][baseObject3dText] = CreateDynamic3DTextLabel(string, 0xFFFFFF55,
				serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ],
				1.6, .worldid = 0);

				// Setar a textura
				if (serverBaseObjects[index][index_object][baseObjectTextureModel] != 0)
				{
				    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497)
					{
						SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, serverBaseObjects[index][index_object][baseObjectTextureModel],
						serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
				    }
					else
					{
						SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, serverBaseObjects[index][index_object][baseObjectTextureModel],
						serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
					}
				}
				
				/*
			 	if (serverBaseObjects[index][index_object][baseObjectModel] == 2969) {
			 	    new loot = createLoot(serverBaseObjects[index][index_object][baseObjectX],serverBaseObjects[index][index_object][baseObjectY],serverBaseObjects[index][index_object][baseObjectZ], 0, LOOT_TYPE_TENDA, .createobject=true, .create3dtext=false, .raycast=false, .slots=25, .world=0, .attachobject = serverBaseObjects[index][index_object][baseObjectId]);
		       	    LootInfo[loot][loot_baseid] = index;
			    	LootInfo[loot][loot_baseobj] = index_object;
				}*/
				
				// ColAndreas
				if (serverBaseObjects[index][index_object][baseObjectModel] > 0)
				{
					serverBaseObjects[index][index_object][baseObjectColAndreasId] = CA_CreateObject(serverBaseObjects[index][index_object][baseObjectModel],
					serverBaseObjects[index][index_object][baseObjectX],serverBaseObjects[index][index_object][baseObjectY],serverBaseObjects[index][index_object][baseObjectZ],
					serverBaseObjects[index][index_object][baseObjectRX],serverBaseObjects[index][index_object][baseObjectRY],serverBaseObjects[index][index_object][baseObjectRZ], true);
				}
			}
		}
		Log::("base", "LOADED\t\t|base %d loaded", index);
	}
	db_free_result(resultQuery);
	
	if (Iter_Contains(baseIter, index))
	{
		if (gettime() > serverBaseInfo[index][baseLastCheck])
		{
			serverBaseDestroy(index, .destroyloots = 0);

			Log::("base", "DESTROY\t\t|%d destroyed for innactivity", index);
		    return 1;
		}

		// destroy base if not objects
		if (CountBaseObjects(index) < 1 || serverBaseInfo[index][baseDestroy]) {
		    // destroy the base
		    serverBaseDestroy(index, .destroyloots = 0);
		}
	}
	return 1;
}


stock UpdatePlayerSelectedItemId(playerid)
{
	if (playerSelectedItemId[playerid] == -1)
	{
	    TextDrawHideForPlayer(playerid, textBaseCraft[1]);
	
	    PlayerTextDrawHide(playerid, textPlayerCraftBase[0]);
	    PlayerTextDrawHide(playerid, textPlayerCraftBase[1]);
	
	    return 0;
	}

    new string[128];
	new item = playerSelectedItemId[playerid];

	format(string, sizeof string, "%.0f HP~n~~n~~n~~n~~n~~n~%d~n~~n~~n~%d~n~~n~~n~%d",
		baseObjectsCraft[item][baseCraftHealth],
		baseObjectsCraft[item][baseCraftMadeira],
		baseObjectsCraft[item][baseCraftRocha],
		baseObjectsCraft[item][baseCraftFerro]);

	PlayerTextDrawSetString(playerid, textPlayerCraftBase[0], string);
	
	PlayerTextDrawSetPreviewModel(playerid, textPlayerCraftBase[1], baseObjectsCraft[item][baseCraftModel]);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerCraftBase[1], baseObjectsCraft[item][baseCraftX], baseObjectsCraft[item][baseCraftY], -55.0, 1.0);

    TextDrawShowForPlayer(playerid, textBaseCraft[1]);

    PlayerTextDrawShow(playerid, textPlayerCraftBase[0]);
    PlayerTextDrawShow(playerid, textPlayerCraftBase[1]);

	return 1;
}

stock updatePlayerCraftBaseText(playerid) {

	new page = GetPVarInt(playerid, "pageCraftBase");
	new curitem = (page * 15);
	new lasitem = (curitem + 15);
	new string[128];
	
	new count;
	
	for(new item = curitem, textid; item < lasitem; item++, textid++)
	{
		if (item >= sizeof(baseObjectsCraft))
		    break;

	    format(string, sizeof string, "%s%s", playerSelectedItemId[playerid] == item ? ("~>~") : (""), baseObjectsCraft[item][baseCraftName]);
		PlayerTextDrawSetString(playerid, playerCraftBase[textid], string);
		
		count ++;
	}
	
	for(new textid = count; textid < 15; textid++)
	{
	    PlayerTextDrawSetString(playerid, playerCraftBase[textid], "_");
	}
	
	format(string, sizeof string, "%d-%d", page + 1, MAX_PAGES_CRAFT_BASES + 1);
	PlayerTextDrawSetString(playerid, textPlayerCraftBase[2], string);
	
	UpdatePlayerSelectedItemId(playerid);
}

stock SelectPlayerItem(playerid, itemid) {

 	new index = getPlayerBase(playerid);

	if (GetPlayerQuantiaItem(playerid, ITEM_TYPE_MADEIRA) < baseObjectsCraft[itemid][baseCraftMadeira] ||
		GetPlayerQuantiaItem(playerid, ITEM_TYPE_ROCHA) < baseObjectsCraft[itemid][baseCraftRocha] ||
		GetPlayerQuantiaItem(playerid, ITEM_TYPE_METAL) < baseObjectsCraft[itemid][baseCraftFerro]) {
		return SendLanguageMessage(playerid, corError, "MSG_80");
 	}
 	
 	static
 	    Float:x,
 	    Float:y,
 	    Float:z,
		Float:angle;

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

 	GetXYInFrontOfPoint(x, y, angle, baseObjectsCraft[itemid][baseCraftOffset]);

 	if (index == -1) {
 	
		if (getPlayerBaseProx(playerid))
		{
		    return SendLanguageMessage(playerid, corError, "MSG_81");
		}
 	
		if (countPlayerBases(playerid) > 1 && !IsPlayerPremium(playerid))
	        return SendLanguageMessage(playerid, corError, "MSG_82");

	    if (countPlayerBases(playerid) > 3)
	        return SendLanguageMessage(playerid, corError, "msg_83");
 	
 	    index = createServerBase(x, y, z);
 	
 	    if (index == -1)
 	        return SendLanguageMessage(playerid, corError, "MSG_84");
 	
	 	new objectid = serverBaseAddObject(index, baseObjectsCraft[itemid][baseCraftModel], x, y, z,
	 	baseObjectsCraft[itemid][baseCraftX], baseObjectsCraft[itemid][baseCraftY], angle, baseObjectsCraft[itemid][baseCraftHealth],
	 	baseObjectsCraft[itemid][baseCraftTxdModel], baseObjectsCraft[itemid][baseCraftTxdName], baseObjectsCraft[itemid][baseCraftTexture]);

	 	if (objectid < 0) {
	 	    if (baseObjectsCraft[itemid][baseCraftModel] == 11729) {
	 	        SendLanguageMessage(playerid, corError, "MSG_85");
	 	    } else {
	 	    	SendLanguageMessage(playerid, corError, "MSG_86");
			}
			return 1;
		}

	 	if (baseObjectsCraft[itemid][baseCraftModel] == 11729) {
	 	    clearAuthorize(index);
	 	    authorizeNickname(index, getNome(playerid));
	 	}

	 	hideCraftItensBase(playerid);

	 	SetPVarInt(playerid, "editbase", index);

        GetPlayerPos(playerid, x, y, z);
	 	SetPVarFloat(playerid, "p_EditBaseX", x);
	 	SetPVarFloat(playerid, "p_EditBaseY", y);
	 	SetPVarFloat(playerid, "p_EditBaseZ", z);

        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

	 	EditDynamicObject(playerid, objectid);
		
		RemoveQuantiaItem(playerid, ITEM_TYPE_MADEIRA, baseObjectsCraft[itemid][baseCraftMadeira]);
		RemoveQuantiaItem(playerid, ITEM_TYPE_ROCHA, baseObjectsCraft[itemid][baseCraftRocha]);
		RemoveQuantiaItem(playerid, ITEM_TYPE_METAL, baseObjectsCraft[itemid][baseCraftFerro]);
		
		checkPlayerConquista(playerid, Conquista_Construindo);
	} else {
 	
 	    if (gettime() < serverBaseInfo[index][baseLastExplode])
 	        return SendClientMessagef(playerid, corError, "ERROR: {888888}Você deve aguardar %d segundos para editar essa base, pois ela foi explodida recentemente.", serverBaseInfo[index][baseLastExplode] - gettime());
 	
	 	new objectid = serverBaseAddObject(index, baseObjectsCraft[itemid][baseCraftModel], x, y, z,
	 	baseObjectsCraft[itemid][baseCraftX], baseObjectsCraft[itemid][baseCraftY], angle, baseObjectsCraft[itemid][baseCraftHealth],
	 	baseObjectsCraft[itemid][baseCraftTxdModel], baseObjectsCraft[itemid][baseCraftTxdName], baseObjectsCraft[itemid][baseCraftTexture]);

	 	if (objectid < 0) {
	 	    if (baseObjectsCraft[itemid][baseCraftModel] == 11729) {
	 	        SendLanguageMessage(playerid, corError, "MSG_85");
	 	    } else {
	 	    	SendLanguageMessage(playerid, corError, "MSG_86");
			}
			return 1;
		}
	 	    
	 	if (baseObjectsCraft[itemid][baseCraftModel] == 11729)
		{
	 	    clearAuthorize(index);
	 	    authorizeNickname(index, getNome(playerid));
	 	}

	 	hideCraftItensBase(playerid);

	 	SetPVarInt(playerid, "editbase", index);
	 	
	 	// position
	 	GetPlayerPos(playerid, x, y, z);
	 	SetPVarFloat(playerid, "p_EditBaseX", x);
	 	SetPVarFloat(playerid, "p_EditBaseY", y);
	 	SetPVarFloat(playerid, "p_EditBaseZ", z);

		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

	 	EditDynamicObject(playerid, objectid);
	 	
		RemoveQuantiaItem(playerid, ITEM_TYPE_MADEIRA, baseObjectsCraft[itemid][baseCraftMadeira]);
		RemoveQuantiaItem(playerid, ITEM_TYPE_ROCHA, baseObjectsCraft[itemid][baseCraftRocha]);
		RemoveQuantiaItem(playerid, ITEM_TYPE_METAL, baseObjectsCraft[itemid][baseCraftFerro]);
		
		checkPlayerConquista(playerid, Conquista_Construindo);
	}
 	
 	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) {

	new index = GetPVarInt(playerid, "editbase");

	if (response == EDIT_RESPONSE_UPDATE)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectId] == objectid)
			{
				if (rx != serverBaseObjects[index][index_object][baseObjectRX] || ry != serverBaseObjects[index][index_object][baseObjectRY])
				{
				    SetDynamicObjectRot(objectid, serverBaseObjects[index][index_object][baseObjectRX], serverBaseObjects[index][index_object][baseObjectRY], rz);
				    EditDynamicObject(playerid, objectid);
				}
				
			 	new Float:lx = GetPVarFloat(playerid, "p_EditBaseX");
			 	new Float:ly = GetPVarFloat(playerid, "p_EditBaseY");
			 	new Float:lz = GetPVarFloat(playerid, "p_EditBaseZ");

				if (!IsPlayerInRangeOfPoint(playerid, 5.0, lx, ly, lz)) {
				    SetPlayerPos(playerid, lx, ly, lz, .freezetime = 3000);
				    CancelEdit(playerid);
				    SetDynamicObjectPos(objectid, serverBaseObjects[index][index_object][baseObjectX], serverBaseObjects[index][index_object][baseObjectY], serverBaseObjects[index][index_object][baseObjectZ]);
					EditDynamicObject(playerid, objectid);
				}
				
				break;
			}
		}
	
// 		SetDynamicObjectPos(objectid, x, y, z);
//		SetDynamicObjectRot(objectid, rx, ry, rz);
	}
	else if (response == EDIT_RESPONSE_FINAL)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectId] == objectid)
			{
			    serverBaseObjects[index][index_object][baseObjectX] = x;
			    serverBaseObjects[index][index_object][baseObjectY] = y;
			    serverBaseObjects[index][index_object][baseObjectZ] = z;
			    serverBaseObjects[index][index_object][baseObjectRX] = rx;
			    serverBaseObjects[index][index_object][baseObjectRY] = ry;
			    serverBaseObjects[index][index_object][baseObjectRZ] = rz;
			    
			    SetDynamicObjectPos(objectid, x, y, z);
			    SetDynamicObjectRot(objectid, rx, ry, rz);
			    
			    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, serverBaseObjects[index][index_object][baseObject3dText], E_STREAMER_X, x);
			    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, serverBaseObjects[index][index_object][baseObject3dText], E_STREAMER_Y, y);
			    Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, serverBaseObjects[index][index_object][baseObject3dText], E_STREAMER_Z, z);
			    
			    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497 || serverBaseObjects[index][index_object][baseObjectModel] == 3049)
				{
			        SetPVarInt(playerid, "upgradeObject", index_object);
			        ShowPlayerDialog(playerid, 557, DIALOG_STYLE_PASSWORD, " ", "{FFFFFF}Digite a senha para abrir esta porta/portão:\n\n{FFAA00}OBS: {999999}A senha deve conter 4 {FF0000}numeros{999999}.", "Definir", "");
			    }
			    
				if (serverBaseObjects[index][index_object][baseObjectTextureModel] != 0)
				{
				    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497)
					{
						SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, serverBaseObjects[index][index_object][baseObjectTextureModel],
						serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
				    }
					else
					{
						SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, serverBaseObjects[index][index_object][baseObjectTextureModel],
						serverBaseObjects[index][index_object][baseObjectTxdName], serverBaseObjects[index][index_object][baseObjectTextureName]);
					}
				}
				else
				{
				    for(new idx; idx < 15; idx++)
						SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], idx, -1, "none", "none", 0);
				}
				
				Audio_Play(playerid, 52);
				StartPlayerProgress(playerid, "Aguarde...", 80,  5.0);
			    
			    if (serverBaseObjects[index][index_object][baseObjectModel] > 0)
			    {
			    	CA_SetObjectPos(serverBaseObjects[index][index_object][baseObjectColAndreasId], x, y, z);
			    	CA_SetObjectRot(serverBaseObjects[index][index_object][baseObjectColAndreasId], rx, ry, rz);
				}
			    
			    updateBaseBauPosition(index, index_object);
			    
			    serverBaseSaveObject(index, index_object);
			    
			    Log::("base", "EDIT OBJECT\t\t|base %d edited object %d to %f %f %f", index, index_object, x, y, z);
			    return 1;
			}
		}
	}
	else if (response == EDIT_RESPONSE_CANCEL)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectId] == objectid)
			{
			    EditDynamicObject(playerid, objectid);
			    return 1;
			}
		}
	}
	return 1;
}

stock const upgradeLimits[][] = {
	// numb        zp
	{	85,        900	},
	{	95,        1100	},
	{	100,       1500	},
	{	110,       1900	},
	{	120,       2300	},
	{	130,       3100	},
	{	140,       3900	},
	{	150,       5000	}
};

stock showDialogLimitObjects(playerid) {
	new string[85];
	stringGlobal[0] = EOS;
	
	new index = getPlayerBase(playerid);
	
	strcat(stringGlobal, "Limite de objetos\tZP\n");
	
	for(new id; id < sizeof upgradeLimits; id++) {
	    format(string, sizeof string, "%sLimite de %d objetos\t%s%d ZP\n",
		serverBaseInfo[index][baseNumbObjects] >= upgradeLimits[id][0] ? ("{999999}") : (""), upgradeLimits[id][0],
		serverBaseInfo[index][baseNumbObjects] >= upgradeLimits[id][0] ? ("{999999}") : ("{BB0000}"), upgradeLimits[id][1]);
		// add a string
		strcat(stringGlobal, string);
	}
	ShowPlayerDialog(playerid, DIALOG_OBJECTSLIMIT, DIALOG_STYLE_TABLIST_HEADERS, "Aumentando o limite de objetos", stringGlobal, "Selecionar", "Voltar");
}

stock ShowBaseArmarioMenu(playerid, index)
{
	if (PlayerData[playerid][dPlayerBlocked]) {
	    ShowPlayerBaseProtectDialog(playerid);
	    return 0;
	}

	new string[356];
	new strindex[75];

	new pass[10];
	format(pass, sizeof pass, serverBaseInfo[index][baseArmarioPass]);

    if (gettime() > serverBaseInfo[index][baseLastCheck])
    {
	   	format(string, sizeof string,
		   	"Autorizar-me\n\
			Lista de autorizados\n\
			Limpar todos autorizados\n\
			Check base: {FF0000}INATIVO\n\
			Limite de objetos: %d atualmente\n\
			Destruição automática: %s\n\
			Senha do armário: %s",
			serverBaseInfo[index][baseNumbObjects],
			serverBaseInfo[index][baseDestroy] ? ("{FF0000}ATIVADA") : ("Desativada"),
			strlen(serverBaseInfo[index][baseArmarioPass]) > 0 ? (pass) : ("Sem senha"));
	}
	else
	{
	    format(string, sizeof string,
			"Autorizar-me\n\
			Lista de autorizados\n\
			Limpar todos autorizados\n\
			Check base: %s restantes\n\
			Limite de objetos: %d atualmente\n\
			Destruição automática: %s\n\
			Senha do armário: %s",
			ConvertBanDate(serverBaseInfo[index][baseLastCheck] - gettime()),
			serverBaseInfo[index][baseNumbObjects],
			serverBaseInfo[index][baseDestroy] ? ("{FF0000}ATIVADA") : ("Desativada"),
			strlen(serverBaseInfo[index][baseArmarioPass]) > 0 ? (pass) : ("Sem senha"));
	}
    SetPVarInt(playerid, "editbase", index);
    
    format(strindex, sizeof strindex, "Base ID: [%d] | Objetos: [%d/%d]", index, CountBaseObjects(index), serverBaseInfo[index][baseNumbObjects]);
    ShowPlayerDialog(playerid, 559, DIALOG_STYLE_LIST, strindex, string, "Selecionar", "Cancelar");
    
    return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PlayerData[playerid][dDropped])
	    return 1;

	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if (newkeys & KEY_SECONDARY_ATTACK)
		{
		    new index = getPlayerBase(playerid);
		    
		    if (index != -1)
			{
				if (IsPlayerInBaseArmario(playerid, index))
				{
				    if (IsNicknameAuthorized(index, getNome(playerid)))
				    {
				    	ShowBaseArmarioMenu(playerid, index);
					}
					else
					{
					    ShowPlayerDialog(playerid, 878, DIALOG_STYLE_PASSWORD, " ", "{FFFFFF}Insira a senha do armário abaixo:\n\n{999999}OBS: A senha contém 4 números (Padrão: 0000)", "Confirmar", "Cancelar");
					}
					return 1;
				}

				new index_object = GetPlayerBaseDoor(playerid, index);

				if (index_object != -1)
				{
					if (IsNicknameAuthorized(index, getNome(playerid)))
					{
					    UpdateBaseDoorState(index, index_object);
					}
					else
					{
					    SetPVarInt(playerid, "upgradeObject", index_object);
					    ShowPlayerDialog(playerid, 558, DIALOG_STYLE_PASSWORD, " ", "{FFFFFF}Insira a senha da porta/portão abaixo:\n\n{999999}OBS: A senha contém 4 números.", "Confirmar", "Cancelar");
					}
					return 1;
				}
				
				new modelid = getPlayerBaseObject(playerid, index, index_object);

				if (modelid == 1812)
				{
				    stringGlobal[0] = EOS;
				    
				    new string[75];
				    
				    new time = serverBaseObjects[index][index_object][baseObjectLastSpawn] - gettime();
				    
				    strcat(stringGlobal, "Definir spawn\n");
				    strcat(stringGlobal, "Limpar dono\n");
				    if (time > 0)
				    {
				    	format(string, sizeof string, "{FF5555}Spawn bloqueado por: %s", ConvertTimeEx(time));
				    	strcat(stringGlobal, string);
					}
				
				    SetPVarInt(playerid, "upgradeObject", index_object);
				    format(string, sizeof string, "Spawn de: {00FFFF}%s", serverBaseObjects[index][index_object][baseObjectOwner]);
				    ShowPlayerDialog(playerid, 921, DIALOG_STYLE_LIST, string, stringGlobal, "Selecionar", "Cancelar");
				}
				else if (modelid == 2206)
				{
					showPlayerWeaponsCraft(playerid);
				}
		    }
		}
	}
 	#if defined qOnPlayerKeyStateChange
  		return qOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange qOnPlayerKeyStateChange
#if defined qOnPlayerKeyStateChange
	forward qOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

stock ShowPlayerBaseCreationMenu(playerid)
{
	new index = getPlayerBase(playerid);

    if (index != -1)
	{
 		if (!IsNicknameAuthorized(index, getNome(playerid)))
	 		return SendClientMessage(playerid, corError, "ERRO: {999999}Você não tem autorização para construir neste local.");
 	}
	if (PlayerData[playerid][dPlayerBlocked]) {
	    ShowPlayerBaseProtectDialog(playerid);
	    return 0;
	}
    ShowPlayerDialog(playerid, 555, DIALOG_STYLE_LIST, " ", "Adicionar objeto\nEditar objeto\nRemover objeto\nUpgrade objeto\n", "Selecionar", "Cancelar");
    SetPVarInt(playerid, "editingBase", index);
   	SetPVarInt(playerid, "lastShowDialog", gettime() + 2);
   	
   	return 1;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z) {

    new index = GetPVarInt(playerid, "editingBase");

	if (index != -1)
	{
		for(new index_object; index_object < MAX_BASE_OBJECTS; index_object++)
		{
			if (serverBaseObjects[index][index_object][baseObjectValid] && serverBaseObjects[index][index_object][baseObjectId] == objectid)
			{
				switch (GetPVarInt(playerid, "editingBaseType"))
				{
				    case 1:
					{
						if (serverBaseObjects[index][index_object][baseObjectTextureModel] != 0)
						{
						    if (serverBaseObjects[index][index_object][baseObjectModel] == 1497)
							{
								SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 1, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
						    }
							else
							{
								SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], 0, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
							}
						}
						else
						{
			   				for(new idx; idx < 15; idx++)
								SetDynamicObjectMaterial(serverBaseObjects[index][index_object][baseObjectId], idx, 8839, "vgsecarshow", "lightgreen2_32", 0xBBFFFFFF);
						}
				    
					 	GetPlayerPos(playerid, x, y, z);
					 	SetPVarFloat(playerid, "p_EditBaseX", x);
					 	SetPVarFloat(playerid, "p_EditBaseY", y);
					 	SetPVarFloat(playerid, "p_EditBaseZ", z);
				    
						SetPVarInt(playerid, "editbase", index);
						EditDynamicObject(playerid, objectid);
					}
				    case 2: {
				    
				        SetPVarInt(playerid, "p_BaseRemoveIndex", index);
				        SetPVarInt(playerid, "p_BaseRemoveObjectIndex", index_object);
				    
				        CancelEdit(playerid);
				        
						ShowPlayerDialogTextdraw(playerid, 999, GetPlayerLanguageKey(playerid, "MSG_87"));
				    
						//serverBaseRemoveObject(index, index_object);
					}
				    case 3:
					{
					    CancelEdit(playerid);
					    
					    if (!isObjectUpgrade(serverBaseObjects[index][index_object][baseObjectModel]))
					        return SendLanguageMessage(playerid, corError, "MSG_88");
					    
					    if (serverBaseObjects[index][index_object][baseObjectLastEdit] > gettime()) {
					        return SendLanguageMessagef(playerid, corError, "MSG_89", serverBaseObjects[index][index_object][baseObjectLastEdit] - gettime());
					    }
					    
					    new
					        madeira,
					        rocha,
							ferro,
							string[128];
					    
					    stringGlobal[0] = EOS;
					    
						strcat(stringGlobal, "Material\tMadeira\tRocha\tMetal\n");
					    
					    upgradeGetInfo(serverBaseObjects[index][index_object][baseObjectModel], txd_model_madeira, madeira, rocha, ferro);
					    format(string, sizeof string, "Material: Madeira\t%d\t%d\t%d\n", madeira, rocha, ferro);
					    strcat(stringGlobal, string);
					    upgradeGetInfo(serverBaseObjects[index][index_object][baseObjectModel], txd_model_rocha, madeira, rocha, ferro);
					    format(string, sizeof string, "Material: Rocha\t%d\t%d\t%d\n", madeira,  rocha, ferro);
					    strcat(stringGlobal, string);
					    upgradeGetInfo(serverBaseObjects[index][index_object][baseObjectModel], txd_model_ferro, madeira, rocha, ferro);
					    format(string, sizeof string, "Material: Metal\t%d\t%d\t%d\n", madeira, rocha, ferro);
					    strcat(stringGlobal, string);
					    
						ShowPlayerDialog(playerid, 556, DIALOG_STYLE_TABLIST_HEADERS, " ", stringGlobal, "Upgrade", "Cancelar");
						SetPVarInt(playerid, "upgradeObject", index_object);
						return 1;
					}
				}

				return 1;
			}
		}
	}

	return 1;
}

public OnTextDialogResponse(playerid, dialogid, response)
{
	if (dialogid == 999) {

	    if (response) {
	        serverBaseRemoveObject(GetPVarInt(playerid, "p_BaseRemoveIndex"), GetPVarInt(playerid, "p_BaseRemoveObjectIndex"));
	    }

		DeletePVar(playerid, #p_BaseRemoveIndex);
		DeletePVar(playerid, #p_BaseRemoveObjectIndex);

		CancelSelectTextDraw(playerid);
	}
 	#if defined OnTextDialogResponseEx
  		return OnTextDialogResponseEx(playerid, dialogid, response);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnTextDialogResponse
	#undef OnTextDialogResponse
#else
	#define _ALS_OnTextDialogResponse
#endif
#define OnTextDialogResponse OnTextDialogResponseEx
#if defined OnTextDialogResponseEx
	forward OnTextDialogResponseEx(playerid, dialogid, response);
#endif

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
   	if (PlayerData[playerid][dDropped] || IsPlayerAdminDuty(playerid))
	    return 1;
	    
	if (GetPVarInt(playerid, "varItensBase"))
	{
	    if (clickedid == Text:INVALID_TEXT_DRAW || clickedid == textBaseCraft[4])
		{
			hideCraftItensBase(playerid);
	    }
	    // <<
	    else if (clickedid == textBaseCraft[2])
		{
	        if (GetPVarInt(playerid, "pageCraftBase") > 0)
			{
			    playerSelectedItemId[playerid] = -1;
				SetPVarInt(playerid, "pageCraftBase", GetPVarInt(playerid, "pageCraftBase") - 1);
				updatePlayerCraftBaseText(playerid);
	        }
	    }
	    // >>
	    else if (clickedid == textBaseCraft[3])
		{
	        if (GetPVarInt(playerid, "pageCraftBase") < MAX_PAGES_CRAFT_BASES)
			{
			    playerSelectedItemId[playerid] = -1;
				SetPVarInt(playerid, "pageCraftBase", GetPVarInt(playerid, "pageCraftBase") + 1);
				updatePlayerCraftBaseText(playerid);
	        }
	    }
	    else if (clickedid == textBaseCraft[1])
	    {
	        if (playerSelectedItemId[playerid] > -1 && playerSelectedItemId[playerid] < sizeof baseObjectsCraft)
	        {
	            SelectPlayerItem(playerid, playerSelectedItemId[playerid]);
	        }
	    }
	}
 	#if defined qOnPlayerClickTextDraw
  		return qOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw qOnPlayerClickTextDraw
#if defined qOnPlayerClickTextDraw
	forward qOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (IsPlayerAdminDuty(playerid))
	    return 1;
	    
	if (GetPVarInt(playerid, "varItensBase"))
	{
		for(new text; text < 15; text++) {

			if (playertextid == playerCraftBase[text])
			{
                new curitem = text + (GetPVarInt(playerid, "pageCraftBase") * 15);

				if (curitem < sizeof baseObjectsCraft)
				{
					playerSelectedItemId[playerid] = curitem;

					//UpdatePlayerSelectedItemId(playerid);
					updatePlayerCraftBaseText(playerid);
				}

				break;
		    }
		}
	}
 	#if defined qOPCPTD
  		return qOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw qOPCPTD
#if defined qOPCPTD
	forward qOPCPTD(playerid, PlayerText:playertextid);
#endif

public OnPlayerEnterDynamicArea(playerid, areaid) {

	if (GetPlayerVirtualWorld(playerid) == 0)
	{
		foreach(new index : baseIter)
		{
		    if (areaid == serverBaseInfo[index][baseArea])
			{
		        SetPVarInt(playerid, "playerInBase", index);

		        if (IsNicknameAuthorized(index, getNome(playerid)))
				{
		            PlayerTextDrawSetString(playerid, textAuthorize[playerid], GetPlayerLanguageKey(playerid, "MSG_90"));
		            PlayerData[playerid][dBaseProtect] = false;
		            PlayerData[playerid][dPlayerBlocked] = false;
		        }
				else
				{
					PlayerTextDrawSetString(playerid, textAuthorize[playerid], GetPlayerLanguageKey(playerid, "MSG_91"));

					if (!IsPlayerAdminDuty(playerid))
					{
						new
						    Float:x,
						    Float:y,
						    Float:z;
						GetPlayerPos(playerid, x, y, z);

					    PlayerData[playerid][dLastBaseX] = x;
					    PlayerData[playerid][dLastBaseY] = y;
					    PlayerData[playerid][dLastBaseZ] = z;

						PlayerData[playerid][dBaseProtect] = true;
					}
					
					Log::("baseenter", "ENTER\t\t|%s entered in base %d area", getNome(playerid), index);
		        }
		        PlayerTextDrawShow(playerid, textAuthorize[playerid]);

		        if (PlayerData[playerid][dAdmin] && IsPlayerAdminDuty(playerid)) {
		        	SendClientMessagef(playerid, 0xAAAAAAFF, "Você entrou na área da base id: %d", index);
				}

		        //Log::("base", "ENTER\t\t|%s entered in base %d area", getNome(playerid), index);
		        break;
		    }
		}
	}

	#if defined qOnPlayerEnterDynamicArea
	    return qOnPlayerEnterDynamicArea(playerid, areaid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea qOnPlayerEnterDynamicArea
#if defined qOnPlayerEnterDynamicArea
	forward qOnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	foreach(new index : baseIter)
	{
	    if (areaid == serverBaseInfo[index][baseArea])
		{
	        SetPVarInt(playerid, "playerInBase", -1);
	        PlayerTextDrawHide(playerid, textAuthorize[playerid]);
	        
	        PlayerData[playerid][dBaseProtect] = false;
	        PlayerData[playerid][dPlayerBlocked] = false;
	        break;
	    }
	}

	#if defined qOnPlayerLeaveDynamicArea
	    return qOnPlayerLeaveDynamicArea(playerid, areaid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerLeaveDynamicArea
	#undef OnPlayerLeaveDynamicArea
#else
	#define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea qOnPlayerLeaveDynamicArea
#if defined qOnPlayerLeaveDynamicArea
	forward qOnPlayerLeaveDynamicArea(playerid, areaid);
#endif

public OnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z)
{
	if (GetDynamicObjectModel(objectid) == 1650)
	{
	    // get a id of global object id
	    new drop = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID);
	    // check if is a valid
		if (drop != 0)
		{
		    // check if item has sufficient amount
	     	if (DropItensInfo[drop][drop_quantia])
	 		{
	 		    // destroy dropped item
				destroyDropItem(drop);
				// create explosion
                CreateBaseExplosion(DropItensInfo[drop][drop_x], DropItensInfo[drop][drop_y], DropItensInfo[drop][drop_z], .maxdamage = float(DropItensInfo[drop][drop_quantia]) / 2.3, .maxrange = 5.0, .type = 0);
		    }
		}
	}
	#if defined qOnPlayerShootDynamicObject
	    qOnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, x, y, z);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerShootDynamicObject
	#undef OnPlayerShootDynamicObject
#else
	#define _ALS_OnPlayerShootDynamicObject
#endif
#define OnPlayerShootDynamicObject qOnPlayerShootDynamicObject
#if defined qOnPlayerShootDynamicObject
    forward qOnPlayerShootDynamicObject(playerid, weaponid, STREAMER_TAG_OBJECT objectid, Float:x, Float:y, Float:z);
#endif

stock showCraftItensBase(playerid) {

    playerSelectedItemId[playerid] = -1;

	for(new text; text < sizeof textBaseCraft; text++)
	    TextDrawShowForPlayer(playerid, textBaseCraft[text]);

	for(new text; text < sizeof playerCraftBase; text++)
	{
	    if (text < sizeof textPlayerCraftBase)
	    {
	        PlayerTextDrawShow(playerid, textPlayerCraftBase[text]);
	    }
	    PlayerTextDrawShow(playerid, playerCraftBase[text]);
	}

    updatePlayerCraftBaseText(playerid);

	SelectTextDraw(playerid, 0xFFFFFFFF);

	SetPVarInt(playerid, "varItensBase", 1);
}

stock hideCraftItensBase(playerid) {

	if (!GetPVarInt(playerid, "varItensBase"))
	    return 0;

	for(new text; text < sizeof textBaseCraft; text++)
	    TextDrawHideForPlayer(playerid, textBaseCraft[text]);

	for(new text; text < sizeof playerCraftBase; text++)
	{
	    if (text < sizeof textPlayerCraftBase)
	    {
	        PlayerTextDrawHide(playerid, textPlayerCraftBase[text]);
	    }
	    PlayerTextDrawHide(playerid, playerCraftBase[text]);
	}

	CancelSelectTextDraw(playerid);

	DeletePVar(playerid, "varItensBase");
	return 1;
}

stock BASE_CreateServerTextDraws()
{
	textBaseCraft[0] = TextDrawCreate(154.000000, 150.000000, "mdl-1043:basecraft");
	TextDrawBackgroundColor(textBaseCraft[0], 255);
	TextDrawFont(textBaseCraft[0], 4);
	TextDrawLetterSize(textBaseCraft[0], 0.500000, 1.000000);
	TextDrawColor(textBaseCraft[0], -56);
	TextDrawSetOutline(textBaseCraft[0], 0);
	TextDrawSetProportional(textBaseCraft[0], 1);
	TextDrawSetShadow(textBaseCraft[0], 1);
	TextDrawUseBox(textBaseCraft[0], 1);
	TextDrawBoxColor(textBaseCraft[0], 255);
	TextDrawTextSize(textBaseCraft[0], 340.000000, 259.200012);
	TextDrawSetSelectable(textBaseCraft[0], 0);

	textBaseCraft[1] = TextDrawCreate(360.000000, 339.000000, "    craft");
	TextDrawBackgroundColor(textBaseCraft[1], -256);
	TextDrawFont(textBaseCraft[1], 2);
	TextDrawLetterSize(textBaseCraft[1], 0.190000, 1.120000);
	TextDrawColor(textBaseCraft[1], -156);
	TextDrawSetOutline(textBaseCraft[1], 0);
	TextDrawSetProportional(textBaseCraft[1], 1);
	TextDrawSetShadow(textBaseCraft[1], 1);
	TextDrawUseBox(textBaseCraft[1], 1);
	TextDrawBoxColor(textBaseCraft[1], 336860415);
	TextDrawTextSize(textBaseCraft[1], 406.600097, 15.000000);
	TextDrawSetSelectable(textBaseCraft[1], 1);

	textBaseCraft[2] = TextDrawCreate(232.000000, 393.000000, "ld_beat:left");
	TextDrawBackgroundColor(textBaseCraft[2], 255);
	TextDrawFont(textBaseCraft[2], 4);
	TextDrawLetterSize(textBaseCraft[2], 0.500000, 1.000000);
	TextDrawColor(textBaseCraft[2], -206);
	TextDrawSetOutline(textBaseCraft[2], 0);
	TextDrawSetProportional(textBaseCraft[2], 1);
	TextDrawSetShadow(textBaseCraft[2], 1);
	TextDrawUseBox(textBaseCraft[2], 1);
	TextDrawBoxColor(textBaseCraft[2], 255);
	TextDrawTextSize(textBaseCraft[2], 8.000000, 9.200012);
	TextDrawSetSelectable(textBaseCraft[2], 1);

	textBaseCraft[3] = TextDrawCreate(261.000000, 393.000000, "ld_beat:right");
	TextDrawBackgroundColor(textBaseCraft[3], 255);
	TextDrawFont(textBaseCraft[3], 4);
	TextDrawLetterSize(textBaseCraft[3], 0.500000, 1.000000);
	TextDrawColor(textBaseCraft[3], -206);
	TextDrawSetOutline(textBaseCraft[3], 0);
	TextDrawSetProportional(textBaseCraft[3], 1);
	TextDrawSetShadow(textBaseCraft[3], 1);
	TextDrawUseBox(textBaseCraft[3], 1);
	TextDrawBoxColor(textBaseCraft[3], 255);
	TextDrawTextSize(textBaseCraft[3], 8.000000, 9.200012);
	TextDrawSetSelectable(textBaseCraft[3], 1);

	textBaseCraft[4] = TextDrawCreate(460.000000, 153.000000, "fechar");
	TextDrawBackgroundColor(textBaseCraft[4], -256);
	TextDrawFont(textBaseCraft[4], 2);
	TextDrawLetterSize(textBaseCraft[4], 0.139999, 0.719999);
	TextDrawColor(textBaseCraft[4], -156);
	TextDrawSetOutline(textBaseCraft[4], 0);
	TextDrawSetProportional(textBaseCraft[4], 1);
	TextDrawSetShadow(textBaseCraft[4], 1);
	TextDrawUseBox(textBaseCraft[4], 1);
	TextDrawBoxColor(textBaseCraft[4], 0);
	TextDrawTextSize(textBaseCraft[4], 482.600097, 10.000000);
	TextDrawSetSelectable(textBaseCraft[4], 1);
}

stock BASE_CreateTextDraws(playerid)
{
	textPlayerCraftBase[0] = CreatePlayerTextDraw(playerid, 308.000000, 299.000000, "1000 HP~n~~n~~n~~n~~n~~n~10~n~~n~~n~0~n~~n~~n~0");
	PlayerTextDrawBackgroundColor(playerid, textPlayerCraftBase[0], -256);
	PlayerTextDrawFont(playerid, textPlayerCraftBase[0], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerCraftBase[0], 0.180000, 0.719999);
	PlayerTextDrawColor(playerid, textPlayerCraftBase[0], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerCraftBase[0], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerCraftBase[0], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerCraftBase[0], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerCraftBase[0], 0);

	textPlayerCraftBase[1] = CreatePlayerTextDraw(playerid, 321.000000, 170.000000, "modelview");
	PlayerTextDrawBackgroundColor(playerid, textPlayerCraftBase[1], 0);
	PlayerTextDrawFont(playerid, textPlayerCraftBase[1], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerCraftBase[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerCraftBase[1], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerCraftBase[1], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerCraftBase[1], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerCraftBase[1], 1);
	PlayerTextDrawUseBox(playerid, textPlayerCraftBase[1], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerCraftBase[1], 0);
	PlayerTextDrawTextSize(playerid, textPlayerCraftBase[1], 123.000000, 126.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerCraftBase[1], 8572);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerCraftBase[1], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerCraftBase[1], 0);

	textPlayerCraftBase[2] = CreatePlayerTextDraw(playerid, 251.000000, 392.000000, "1-4");
	PlayerTextDrawAlignment(playerid, textPlayerCraftBase[2], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerCraftBase[2], -256);
	PlayerTextDrawFont(playerid, textPlayerCraftBase[2], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerCraftBase[2], 0.190000, 1.120000);
	PlayerTextDrawColor(playerid, textPlayerCraftBase[2], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerCraftBase[2], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerCraftBase[2], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerCraftBase[2], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerCraftBase[2], 0);

	// list
	playerCraftBase[0] = CreatePlayerTextDraw(playerid, 165.000000, 170.000000, "Porta de madeira grande");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[0], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[0], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[0], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[0], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[0], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[0], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[0], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[0], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[0], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[0], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[0], 1);

	playerCraftBase[1] = CreatePlayerTextDraw(playerid, 165.000000, 184.000000, "Porta de madeira grande");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[1], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[1], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[1], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[1], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[1], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[1], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[1], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[1], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[1], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[1], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[1], 1);

	playerCraftBase[2] = CreatePlayerTextDraw(playerid, 165.000000, 198.000000, "Porta de madeira grande");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[2], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[2], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[2], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[2], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[2], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[2], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[2], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[2], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[2], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[2], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[2], 1);

	playerCraftBase[3] = CreatePlayerTextDraw(playerid, 165.000000, 212.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[3], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[3], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[3], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[3], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[3], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[3], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[3], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[3], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[3], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[3], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[3], 1);

	playerCraftBase[4] = CreatePlayerTextDraw(playerid, 165.000000, 226.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[4], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[4], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[4], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[4], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[4], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[4], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[4], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[4], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[4], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[4], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[4], 1);

	playerCraftBase[5] = CreatePlayerTextDraw(playerid, 165.000000, 240.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[5], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[5], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[5], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[5], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[5], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[5], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[5], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[5], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[5], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[5], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[5], 1);

	playerCraftBase[6] = CreatePlayerTextDraw(playerid, 165.000000, 254.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[6], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[6], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[6], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[6], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[6], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[6], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[6], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[6], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[6], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[6], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[6], 1);

	playerCraftBase[7] = CreatePlayerTextDraw(playerid, 165.000000, 268.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[7], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[7], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[7], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[7], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[7], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[7], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[7], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[7], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[7], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[7], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[7], 1);

	playerCraftBase[8] = CreatePlayerTextDraw(playerid, 165.000000, 282.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[8], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[8], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[8], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[8], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[8], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[8], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[8], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[8], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[8], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[8], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[8], 1);

	playerCraftBase[9] = CreatePlayerTextDraw(playerid, 165.000000, 296.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[9], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[9], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[9], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[9], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[9], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[9], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[9], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[9], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[9], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[9], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[9], 1);

	playerCraftBase[10] = CreatePlayerTextDraw(playerid, 165.000000, 310.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[10], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[10], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[10], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[10], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[10], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[10], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[10], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[10], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[10], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[10], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[10], 1);

	playerCraftBase[11] = CreatePlayerTextDraw(playerid, 165.000000, 324.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[11], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[11], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[11], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[11], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[11], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[11], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[11], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[11], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[11], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[11], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[11], 1);

	playerCraftBase[12] = CreatePlayerTextDraw(playerid, 165.000000, 338.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[12], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[12], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[12], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[12], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[12], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[12], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[12], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[12], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[12], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[12], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[12], 1);

	playerCraftBase[13] = CreatePlayerTextDraw(playerid, 165.000000, 352.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[13], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[13], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[13], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[13], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[13], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[13], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[13], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[13], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[13], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[13], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[13], 1);

	playerCraftBase[14] = CreatePlayerTextDraw(playerid, 165.000000, 366.000000, "Moldura janela de madeira");
	PlayerTextDrawBackgroundColor(playerid, playerCraftBase[14], -256);
	PlayerTextDrawFont(playerid, playerCraftBase[14], 1);
	PlayerTextDrawLetterSize(playerid, playerCraftBase[14], 0.170000, 0.919999);
	PlayerTextDrawColor(playerid, playerCraftBase[14], -176);
	PlayerTextDrawSetOutline(playerid, playerCraftBase[14], 0);
	PlayerTextDrawSetProportional(playerid, playerCraftBase[14], 1);
	PlayerTextDrawSetShadow(playerid, playerCraftBase[14], 1);
	PlayerTextDrawUseBox(playerid, playerCraftBase[14], 1);
	PlayerTextDrawBoxColor(playerid, playerCraftBase[14], 0);
	PlayerTextDrawTextSize(playerid, playerCraftBase[14], 265.600097, 10.000000);
	PlayerTextDrawSetSelectable(playerid, playerCraftBase[14], 1);
}

