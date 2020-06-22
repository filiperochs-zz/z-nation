// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 

#define MAX_ARVORES   			(1000)
#define MAX_FRUTAS_POR_ARVORE 	(4)
#define RESPAWN_FRUTO_ARVORE    (2000 + random(2000))
#define AMADURECER_FRUTO_ARVORE (2100 + random(2500))


enum {
	ARVORE_TYPE_MACA,
	ARVORE_TYPE_MACAVERDE,
	ARVORE_TYPE_LARANJA,
	ARVORE_TYPE_BANANA,
	ARVORE_TYPE_TOMATE,
};

enum enumArvores {
       arvoreType,
       arvoreObject,
Float: arvoreX,
Float: arvoreY,
Float: arvoreZ,
Float: arvoreHealth,
};

enum enumArvoresFruto {
	   arvoreFrutaValid,
	   arvoreFrutaRespawn,
	   arvoreFrutaMadura,
	   arvoreFrutaObject,
};

// Vars
new ArvoreInfo[MAX_ARVORES][enumArvores];

// Frutas
new ArvoreFrutoInfo[MAX_ARVORES][MAX_FRUTAS_POR_ARVORE][enumArvoresFruto];

// Iterator
new Iterator:iterArvores<MAX_ARVORES>;

// Funções

stock CreateArvore(type, Float:x, Float:y, Float:z, save = true) {

	new index = Iter_Free(iterArvores);
	
	if (index != -1) {
	
	    Iter_Add(iterArvores, index);
	    
	    ArvoreInfo[index][arvoreType] = type;
	    ArvoreInfo[index][arvoreX]    = x;
	    ArvoreInfo[index][arvoreY]    = y;
	    ArvoreInfo[index][arvoreZ]    = z;
	    ArvoreInfo[index][arvoreHealth] = 100.0;
	    
	    ArvoreInfo[index][arvoreObject] = CreateDynamicObject(717, x, y, z - 2.1, 0.0, 0.0, 0.0, 0);
	    
	    // Resetar frutas
	    for(new frutas; frutas < MAX_FRUTAS_POR_ARVORE; frutas++) {
	        ArvoreFrutoInfo[index][frutas][arvoreFrutaValid]   = 0;
	        ArvoreFrutoInfo[index][frutas][arvoreFrutaRespawn] = RESPAWN_FRUTO_ARVORE;
	        ArvoreFrutoInfo[index][frutas][arvoreFrutaMadura]  = AMADURECER_FRUTO_ARVORE;
	        ArvoreFrutoInfo[index][frutas][arvoreFrutaObject]  = -1;
	    }
	    
	    // Salvar
	    if (save) {
			SalvarArvores();
	    	// Log
	    	Log::("arvores", "CREATE\t\t|%d created type %d", index, type);
		}
	}
	return index;
}

stock DestroyArvore(index) {

	if (Iter_Contains(iterArvores, index)) {
	
	    Iter_Remove(iterArvores, index);
	
	    // Destroys
	    DestroyDynamicObject(ArvoreInfo[index][arvoreObject]);
	    
 	    for(new frutas; frutas < MAX_FRUTAS_POR_ARVORE; frutas++) {
			if (ArvoreFrutoInfo[index][frutas][arvoreFrutaValid]) {
	        	DestroyDynamicObject(ArvoreFrutoInfo[index][frutas][arvoreFrutaObject]);
			}
	    }
	    
	    // Salvar
	    SalvarArvores();
	    
	    Log::("arvores", "DESTROY\t\t|%d destroyed", index);
	
	    return 1;
	}
	return 0;
}

stock SalvarArvores() {

	new File: fileArvores;
	new string[128];
	
	fileArvores = fopen(pastaArvores, io_write);
	
	if (fileArvores) {
	
	    foreach(new index : iterArvores) {
	    
	    	format(string, sizeof (string), "%f,%f,%f,%d\r\n", ArvoreInfo[index][arvoreX], ArvoreInfo[index][arvoreY], ArvoreInfo[index][arvoreZ], ArvoreInfo[index][arvoreType]);
	    	fwrite(fileArvores, string);
		}
	
	    fclose(fileArvores);
	}
}

stock CarregarArvores() {

	new File: fileArvores;
	new stringOutput[128];
	new string[4][25];

	fileArvores = fopen(pastaArvores, io_read);

	if (fileArvores) {

		while (fread(fileArvores, stringOutput)) {
		
		    split(stringOutput, string, ',');
		    
		    CreateArvore(strval(string[3]), floatstr(string[0]), floatstr(string[1]), floatstr(string[2]), .save = false);
		    
		    printf("[DEBUG] Arvore %d carregada em: %f %f %f : %d", floatstr(string[0]), floatstr(string[1]), floatstr(string[2]), strval(string[3]));
		}

	    fclose(fileArvores);
	}
}

callback UpdateServerArvores() {

	foreach(new index : iterArvores) {
	
	    for(new frutas; frutas < MAX_FRUTAS_POR_ARVORE; frutas++) {
	    
	        if (ArvoreFrutoInfo[index][frutas][arvoreFrutaRespawn] > 0)
	        	ArvoreFrutoInfo[index][frutas][arvoreFrutaRespawn] --;
	        	
	        if (ArvoreFrutoInfo[index][frutas][arvoreFrutaMadura] > 0)
	        	ArvoreFrutoInfo[index][frutas][arvoreFrutaMadura] --;
	    
	        if (ArvoreFrutoInfo[index][frutas][arvoreFrutaValid]) {
	        
	            // Cair fruta madura
	            if (ArvoreFrutoInfo[index][frutas][arvoreFrutaMadura] < 1) {
					DerrubarArvoreFruto(index, frutas);
				}
					
	        } else {
	        
	            // Nascer nova fruta
	            if (ArvoreFrutoInfo[index][frutas][arvoreFrutaRespawn] < 1) {
					AddArvoreFruto(index, frutas);
				}
	        }
	    }
	}

	return 1;
}

stock AddArvoreFruto(index, toindex) {

	new
	    Float:spawnx = (ArvoreInfo[index][arvoreX]) + frandom(3.0) - frandom(3.0),
	    Float:spawny = (ArvoreInfo[index][arvoreY]) + frandom(3.0) - frandom(3.0),
	    Float:spawnz = (ArvoreInfo[index][arvoreZ] + 5.5) + frandom(2.5) - frandom(2.5);

    ArvoreFrutoInfo[index][toindex][arvoreFrutaValid]  = 1;
    ArvoreFrutoInfo[index][toindex][arvoreFrutaMadura] = AMADURECER_FRUTO_ARVORE;
    ArvoreFrutoInfo[index][toindex][arvoreFrutaObject] = CreateDynamicObject(GetArvoreFrutoModel(index), spawnx, spawny, spawnz, frandom(360), frandom(360), frandom(360), 0);
}

stock DerrubarArvoreFruto(index, frutoindex) {

	static
	    Float:x,
	    Float:y,
	    Float:z;
	    
	GetDynamicObjectPos(ArvoreFrutoInfo[index][frutoindex][arvoreFrutaObject], x, y, z);

    ArvoreFrutoInfo[index][frutoindex][arvoreFrutaValid]   = 0;
    ArvoreFrutoInfo[index][frutoindex][arvoreFrutaRespawn] = RESPAWN_FRUTO_ARVORE;
    
    CA_RayCastLine(x, y, z, x, y, z - 100.0, x, y, z);
    
    //z += 0.2;
    MoveDynamicObject(ArvoreFrutoInfo[index][frutoindex][arvoreFrutaObject], x, y, z, 8.0, frandom(360), frandom(360), frandom(360));
}

stock BalancarArvore(index) {

	if (Iter_Contains(iterArvores, index)) {

	    for(new frutas; frutas < MAX_FRUTAS_POR_ARVORE; frutas++) {

	        if (ArvoreFrutoInfo[index][frutas][arvoreFrutaValid]) {

				if (random(100) < 3) DerrubarArvoreFruto(index, frutas);
			}
	    }
	}
	return 0;
}

stock GetPlayerClossestArvore(playerid) {
	    
	foreach(new index : iterArvores) {
	
	    if (IsPlayerInRangeOfPoint(playerid, 2.0, ArvoreInfo[index][arvoreX], ArvoreInfo[index][arvoreY], ArvoreInfo[index][arvoreZ])) {
	        return index;
	    }
	}
	return -1;
}

stock GetArvoreFrutoModel(index) {

	if (Iter_Contains(iterArvores, index)) {

		switch (ArvoreInfo[index][arvoreType]) {
			case ARVORE_TYPE_MACA	  : return 19575;
			case ARVORE_TYPE_MACAVERDE: return 19576;
			case ARVORE_TYPE_LARANJA  : return 19574;
			case ARVORE_TYPE_BANANA   : return 19578;
			case ARVORE_TYPE_TOMATE   : return 19577;
		}
	}
	return 0;
}

stock GetArvoreItemType(index) {

	if (Iter_Contains(iterArvores, index)) {

		switch (ArvoreInfo[index][arvoreType]) {
			case ARVORE_TYPE_MACA	  : return ITEM_TYPE_MACA;
			case ARVORE_TYPE_MACAVERDE: return ITEM_TYPE_MACAVERDE;
			case ARVORE_TYPE_LARANJA  : return ITEM_TYPE_LARANJA;
			case ARVORE_TYPE_BANANA   : return ITEM_TYPE_BANANA;
			case ARVORE_TYPE_TOMATE   : return ITEM_TYPE_TOMATE;
		}
	}
	return 0;
}

public OnDynamicObjectMoved(objectid) {

	foreach(new index : iterArvores) {
	
 	    for(new frutas; frutas < MAX_FRUTAS_POR_ARVORE; frutas++) {

			if (ArvoreFrutoInfo[index][frutas][arvoreFrutaObject] == objectid) {

				static
				    Float:x,
					Float:y,
					Float:z;
				    
				GetDynamicObjectPos(objectid, x, y, z);
				
				z += 0.8;
				    
				DestroyDynamicObject(objectid);
				
				ArvoreFrutoInfo[index][frutas][arvoreFrutaObject] = -1;
				
				createDroppedItem(x, y, z, getItemModelName(GetArvoreFrutoModel(index)), GetArvoreItemType(index), GetArvoreFrutoModel(index), 1, true, 0, false);
	        	
	        	break;
			}
	    }
	}
	#if defined treeOnDynamicObjectMoved
	    treeOnDynamicObjectMoved(objectid);
 	#endif
	return 1;
}
#if defined _ALS_OnDynamicObjectMoved
	#undef OnDynamicObjectMoved
#else
	#define _ALS_OnDynamicObjectMoved
#endif
#define OnDynamicObjectMoved treeOnDynamicObjectMoved
#if defined treeOnDynamicObjectMoved
   	forward treeOnDynamicObjectMoved(objectid);
#endif

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {

	if (PlayerData[playerid][dDropped])
	    return 1;

	if (!IsPlayerInAnyVehicle(playerid)) {
	
	    if ((newkeys & KEY_FIRE) && gettime() > GetPVarInt(playerid, "balancouArvore")) {

			new index = GetPlayerClossestArvore(playerid);

		    if (index != -1) {

				SetPlayerFaceToPoint(playerid, ArvoreInfo[index][arvoreX], ArvoreInfo[index][arvoreY]);

				BalancarArvore(index);
				
    			new weaponid = GetPlayerWeapon(playerid);

		        if (weaponid == 8) {

					StartPlayerProgress(playerid, "Cortando...", 80,  20.0);
		            ApplyAnimation(playerid, "BASEBALL","Bat_1", 4.1, 0, 1, 1, 0, 0);
		            SetWeaponHealth(playerid, weaponid, GetWeaponHealth(playerid, weaponid) - 0.05);

                    SetTimerEx("delayedSound", 300, false, "dd", playerid, 50);

					ArvoreInfo[index][arvoreHealth] -= (20.0 + frandom(15.0));
					
					givePlayerPoints(playerid, 150, .point_3d = 0);

					if (ArvoreInfo[index][arvoreHealth] < 0.0) {
		                DestroyArvore(index);
		                
		                new string[75];
		                new quantiaSpawn = 10 + random(25);

		      			if (!AddQuantiaItem(playerid, ITEM_TYPE_MADEIRA, quantiaSpawn))
		      			{
		      			    if (!isInventoryFreeSpace(playerid))
		      			    {
								static
								    Float:x,
								    Float:y,
								    Float:z;

								GetPlayerPos(playerid, x, y, z);
		      			    	createDroppedItem(x, y, z, "Madeira", ITEM_TYPE_MADEIRA, 19793, quantiaSpawn);
							} else {
							    givePlayerItem(playerid, ITEM_TYPE_MADEIRA, 19793, quantiaSpawn, "Madeira");
							}
		      			}

						format(string, sizeof string, "+%d madeiras", quantiaSpawn);
						SendServerMessageToPlayer(playerid, string);
						
						checkPlayerConquista(playerid, Conquista_Coletando);
		            }
		        }
				
				SetPVarInt(playerid, "balancouArvore", gettime() + 1);
		    }
		}
	}

	#if defined treeOnPlayerKeyStateChange
	    treeOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
 	#endif
	return 1;
}
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange treeOnPlayerKeyStateChange
#if defined treeOnPlayerKeyStateChange
   	forward treeOnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif

CMD:criararvoreex2(playerid, params[]) {

	static
	    Float:x,
	    Float:y,
	    Float:z;
	    
	GetPlayerPos(playerid, x, y, z);
	
	CreateArvore(strval(params), x, y, z);
	
	return 1;
}









