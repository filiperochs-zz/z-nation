// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 

stock CreateTent(Float:x, Float:y, Float:z, Float:rz, lootid, world=0) {

	new Side1, Side2, Entrada1, Entrada2, Entrada3, Entrada4;
	new Corda2, Corda3, Corda4, Corda5, Corda6, Corda7;

	//carpa

	Side1 = CreateDynamicObject(19325,
		x + (1.110 * floatsin(-rz + 90.0, degrees)),
		y + (1.110 * floatcos(-rz + 90.0, degrees)),
		z + 0.8,
		0.00000, -32.00000, rz, world);

	Side2 = CreateDynamicObject(19325,
	 	x + (1.110 * floatsin(-rz + 270.0, degrees)),
 		y + (1.110 * floatcos(-rz + 270.0, degrees)),
		z + 0.8,
		0.00000, 34.00000, rz, world);


// Lado 1
	Entrada1 = CreateDynamicObject(2068,
		x + (2.800 * floatsin(-rz + 16.0, degrees)),
		y + (2.800 * floatcos(-rz + 16.0, degrees)),
		z - 3.0,
		138.00000, 105.00000, rz - 99.0, world);

	Entrada2 = CreateDynamicObject(2068,
		x - (2.800 * floatsin(-rz + 16.0, degrees)),
		y - (2.800 * floatcos(-rz + 16.0, degrees)),
		z - 3.0,
		138.00000, 105.00000, rz + 78.00, world);


// Lado 2
	Entrada3 = CreateDynamicObject(2068,
		x + (3.999 * floatsin(-rz - 10.0, degrees)),
		y + (3.999 * floatcos(-rz - 10.0, degrees)),
		z - 3.0,
		138.00000, 105.00000, rz + 78.0, world);

	Entrada4 = CreateDynamicObject(2068,
		x - (3.999 * floatsin(-rz - 10.0, degrees)),
		y - (3.999 * floatcos(-rz - 10.0, degrees)),
		z - 3.0,
		138.00000, 105.00000, rz - 99.00, world);

// Cordas

    Corda2 = CreateDynamicObject(19089,
		x + (3.300 * floatsin(-rz, degrees)),
		y + (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, -42.00000, rz + 90.00000, world);

	Corda3 = CreateDynamicObject(19089,
		x - (3.300 * floatsin(-rz, degrees)),
		y - (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, 42.00000, rz + 90.00000, world);

	Corda4 = CreateDynamicObject(19089,
		x + (3.300 * floatsin(-rz, degrees)),
		y + (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, -53.00000, rz + 0.00000, world);

	Corda5 = CreateDynamicObject(19089,
		x - (3.300 * floatsin(-rz, degrees)),
		y - (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, -53.00000, rz + 0.00000, world);

	Corda6 = CreateDynamicObject(19089,
		x + (3.300 * floatsin(-rz, degrees)),
		y + (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, -53.00000, rz - 180.00000, world);

	Corda7 = CreateDynamicObject(19089,
		x - (3.300 * floatsin(-rz, degrees)),
		y - (3.300 * floatcos(-rz, degrees)),
		z + 2.5,
		0.00000, -53.00000, rz - 180.00000, world);


	SetDynamicObjectMaterial(Side1, 0, 3066, "ammotrx", "ammotrn92tarp128", -1);
	SetDynamicObjectMaterial(Side2, 0, 3066, "ammotrx", "ammotrn92tarp128", -1);
	
    LootInfo[lootid][loot_object][0] = Side1;
    LootInfo[lootid][loot_object][1] = Side2;
    LootInfo[lootid][loot_object][2] = Entrada1;
    LootInfo[lootid][loot_object][3] = Entrada2;
    LootInfo[lootid][loot_object][4] = Entrada3;
    LootInfo[lootid][loot_object][5] = Entrada4;
    LootInfo[lootid][loot_object][6] = Corda2;
    LootInfo[lootid][loot_object][7] = Corda3;
    LootInfo[lootid][loot_object][8] = Corda4;
    LootInfo[lootid][loot_object][9] = Corda5;
    LootInfo[lootid][loot_object][10] = Corda6;
    LootInfo[lootid][loot_object][11] = Corda7;
}

stock saveTents() {

	foreach(new loot : iterLoots) {
		saveTent(loot);
	}
	return 0;
}

stock saveTent(loot) {

	new filename[95],
		File:file,
	    string_save[95];

    format(filename, sizeof (filename), pastaTendas, loot);
    
    file = fopen(filename, io_write);

	if (file)
	{
	    if (LootInfo[loot][loot_type] == LOOT_TYPE_TENDA) {

			new countitens = countLootItensNumber(loot);

	     	format(string_save, sizeof (string_save), "%.3f|%.3f|%.3f|%.3f|%d\r\n", LootInfo[loot][loot_x], LootInfo[loot][loot_y], LootInfo[loot][loot_z], LootInfo[loot][loot_rz], countitens);
			fwrite(file, string_save);

	      	for(new itens; itens != MAX_ITENS_INVENTARIO; itens++) {

                if (!LootItensInfo[loot][itens][item_valid]) continue;

		        format(string_save, sizeof (string_save), "%s|%d|%d|%d|%d|%.1f\r\n", LootItensInfo[loot][itens][item_nome], LootItensInfo[loot][itens][item_type], LootItensInfo[loot][itens][item_model], LootItensInfo[loot][itens][item_quantia], LootItensInfo[loot][itens][item_slots], LootItensInfo[loot][itens][item_health]);
				fwrite(file, string_save);
			}
			printf("[Save Tenda] Tenda: %d: %f %f %f   Itens: %d", loot, LootInfo[loot][loot_x], LootInfo[loot][loot_y], LootInfo[loot][loot_z], countitens);
		}
		fclose(file);
		
		return 1;
	}
	return 0;
}


stock removeTentFile(loot) {

	new filename[95];

    format(filename, sizeof (filename), pastaTendas, loot);

	if (fexist(filename)) {
		fremove(filename);
	}

	return 0;
}


stock loadTents() {

	new File:file,
	    string_read[128],
		string_file[MAX_ITENS_LOOT][45],
		filename[95];

	for(new loot; loot < MAX_LOOTS; loot++) {

		format(filename, sizeof (filename), pastaTendas, loot);

		if (!fexist(filename))
		    continue;
		
		file = fopen(filename, io_read);

		if (file)
		{
            fread(file, string_read);

			split(string_read, string_file, '|');

	        new lootid = createLoot(floatstr(string_file[0]), floatstr(string_file[1]), floatstr(string_file[2]), 10, LOOT_TYPE_TENDA, true, true, false, floatstr(string_file[3]), idloot = loot);
	        new totalitens = strval(string_file[4]);

	        printf("[Load Tenda] Tenda: %d: %f %f %f %f   Itens: %d", loot, floatstr(string_file[0]), floatstr(string_file[1]), floatstr(string_file[2]), floatstr(string_file[3]), totalitens);

			for(new itens; itens != totalitens; itens++) {

	            fread(file, string_read);

				split(string_read, string_file, '|');

				addItemToLoot(lootid, strval(string_file[1]), strval(string_file[2]), strval(string_file[3]), string_file[0], .health = floatstr(string_file[5]), .saveloot = 0);

	            printf("    Item: %s %d %d %d", string_file[0], strval(string_file[1]), strval(string_file[2]), strval(string_file[3]));
			}
			fclose(file);
			
			//fremove(filename);
			
			//saveTent(lootid);
		}
	}
	return 0;
}

stock createPlayerTent(playerid) {

	static Float:x, Float:y, Float:z, Float:rz;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, rz);
	
	createLoot(x, y, z, 0, LOOT_TYPE_TENDA, true, true, false, rz);
}
