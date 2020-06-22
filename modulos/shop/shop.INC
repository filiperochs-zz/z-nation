// Test
//
#define SHOP_Database       ("ZNation/Shop/shop.db")
#define MAX_SHOP_ITENS      (100)
#define DIVIDER_RENT        (8)
#define c_days(%0)    		((%0) * 86400)
#define c_hours(%0)    		((%0) * 3600)

static
	SERVER_DOWNLOAD[] = "https://pantherhosting.tk/downloads/models";

enum {
	CRATE_TYPE_NONE,
	CRATE_TYPE_DAILY,
	CRATE_TYPE_SILVER,
	CRATE_TYPE_GOLD,
	CRATE_TYPE_DIAMOND,
	CRATE_TYPE_LEGENDARY,
	CRATE_TYPE_ULTIMATE,
}

enum {
	SKIN_GENDER_MALE,  		// Men
	SKIN_GENDER_FEMALE,		// Woman
}

enum {
	SKIN_RARITY_COMUM,    	// Rarity comum
	SKIN_RARITY_RARE,     	// Rarity raro
	SKIN_RARITY_LEGENDARY,	// Rarity lendária
	SKIN_RARITY_ULTIMATE, 	// Rarity ultimate
	SKIN_RARITY_LEGACY,     // Rarity legacy
}

enum {
 	ORDER_BY_RANDOM,   		// Order by random
	ORDER_BY_LCOST,   		// Order by lowest price
	ORDER_BY_BCOST,   		// Order by biggest price
	ORDER_BY_RARITY, 		// Order by rarity
	ORDER_BY_DATE,   		// Order by date
	ORDER_BY_MALE,          // order by male skins
	ORDER_BY_FEMALE,        // order by female skins
	ORDER_BY_CRATES,        // order by crates
}

enum {
	SKIN_SELECT_SHOP,     	// Viewing shop skins
	SKIN_SELECT_INVENTORY,	// Viewing inventory skins
}

enum p_enum_shop {
	ps_ai,
	ps_modelid,
	ps_cost,
	ps_rarity,
	ps_gender,
	ps_legacy,
	ps_time,
}

// Store result query in array
new ps_array[MAX_PLAYERS][MAX_SHOP_ITENS][p_enum_shop];

// Store num rows from query
new ps_num_rows[MAX_PLAYERS];

// current page
new ps_current_page[MAX_PLAYERS];

// Server shop database
new DB:shop_database;

// Player textdraws
new PlayerText:playerShopText[16];

// Server textdraws
new Text:serverShopTexts[14];

stock CreateModelsArtWork()
{
	// Delete all
//	db_query(shop_database, "delete from skins");

	// login screen
	AddSimpleModel(-1, 19379, -1000, "d_object.dff", "background/background.txd");
	AddSimpleModel(-1, 19379, -1001, "d_object.dff", "login_screen/login_screen.txd");
	// shop skins
	AddSimpleModel(-1, 19379, -1002, "d_object.dff", "shop_design/shop_design.txd");
	AddSimpleModel(-1, 19379, -1003, "d_object.dff", "shop_design/shop_skins.txd");
	// Inventory
	AddSimpleModel(-1, 19379, -1004, "d_object.dff", "inventory/inventory.txd");
	AddSimpleModel(-1, 19379, -1005, "d_object.dff", "inventory/items.txd");
	// Items
	AddSimpleModel(-1, 19379, -1006, "pubg/helmet1.dff", "pubg/helmet1.txd");
	AddSimpleModel(-1, 19379, -1007, "pubg/helmet2.dff", "pubg/helmet2.txd");
	AddSimpleModel(-1, 19379, -1008, "pubg/helmet3.dff", "pubg/helmet3.txd");
	AddSimpleModel(-1, 19379, -1009, "pubg/colete1.dff", "pubg/colete1.txd");
	AddSimpleModel(-1, 19379, -1010, "pubg/colete2.dff", "pubg/colete2.txd");
	AddSimpleModel(-1, 19379, -1011, "pubg/colete3.dff", "pubg/colete3.txd");
	AddSimpleModel(-1, 19379, -1012, "pubg/backpack1.dff", "pubg/backpack1.txd");
	AddSimpleModel(-1, 19379, -1013, "pubg/backpack2.dff", "pubg/backpack2.txd");
	AddSimpleModel(-1, 19379, -1014, "pubg/backpack3.dff", "pubg/backpack3.txd");
	AddSimpleModel(-1, 19379, -1014, "pubg/pan.dff", "pubg/pan.txd");
	// weapons
	AddSimpleModel(-1, 19379, -1015, "d_object.dff", "inventory/weapons.txd");
	// Coletes drop
	AddSimpleModel(-1, 19379, -1016, "pubg/colete1_drop.dff", "pubg/colete1.txd");
	AddSimpleModel(-1, 19379, -1017, "pubg/colete2_drop.dff", "pubg/colete2.txd");
	AddSimpleModel(-1, 19379, -1018, "pubg/colete3_drop.dff", "pubg/colete3.txd");
	// Hud
	AddSimpleModel(-1, 19379, -1019, "d_object.dff", "hud/hud.txd");
	// Gas mask
	AddSimpleModel(-1, 19379, -1020, "pubg/gasmask.dff", "pubg/gasmask.txd");
	// Airdrop
	AddSimpleModel(-1, 19379, -1021, "pubg/airdrop.dff", "pubg/airdrop.txd");
	AddSimpleModel(-1, 19379, -1022, "pubg/paraquedas.dff", "pubg/paraquedas.txd");
	// Facão
	AddSimpleModel(-1, 19379, -1023, "pubg/facao.dff", "pubg/facao.txd");
	// Spawns selection
	AddSimpleModel(-1, 19379, -1024, "d_object.dff", "login_screen/login_spawns.txd");
	// Painkiller
	AddSimpleModel(-1, 19379, -1025, "pubg/painkiller.dff", "pubg/painkiller.txd");
	// Red bull
	AddSimpleModel(-1, 19379, -1026, "pubg/redbull.dff", "pubg/redbull.txd");
	// Tenda
	AddSimpleModel(-1, 19379, -1027, "pubg/tent.dff", "pubg/tent.txd");
	// Emotes
	AddSimpleModel(-1, 19379, -1028, "d_object.dff", "emotes/emotes.txd");
	// Book
	AddSimpleModel(-1, 19379, -1029, "d_object.dff", "book/book1.txd");
	AddSimpleModel(-1, 19379, -1030, "d_object.dff", "book/book2.txd");
	AddSimpleModel(-1, 19379, -1031, "d_object.dff", "book/book3.txd");
	AddSimpleModel(-1, 19379, -1032, "d_object.dff", "book/book4.txd");
	AddSimpleModel(-1, 19379, -1033, "pubg/book.dff", "pubg/book.txd");
	// Ammo boxes
	AddSimpleModel(-1, 19379, -1034, "pubg/9mm/ammo.dff", "pubg/9mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1035, "pubg/9x19mm/ammo.dff", "pubg/9x19mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1036, "pubg/50mm/ammo.dff", "pubg/50mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1037, "pubg/55mm/ammo.dff", "pubg/55mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1038, "pubg/156mm/ammo.dff", "pubg/156mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1040, "pubg/357mm/ammo.dff", "pubg/357mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1041, "pubg/556mm/ammo.dff", "pubg/556mm/ammo.txd");
	AddSimpleModel(-1, 19379, -1042, "pubg/762mm/ammo.dff", "pubg/762mm/ammo.txd");
	// progres
	AddSimpleModel(-1, 19379, -1043, "d_object.dff", "hud/progress.txd");
	// Broken vehicles
	AddSimpleModel(-1, 19379, -1044, "brokenvehicles/1.dff", "brokenvehicles/1.txd");
	AddSimpleModel(-1, 19379, -1045, "brokenvehicles/2.dff", "brokenvehicles/2.txd");
	AddSimpleModel(-1, 19379, -1046, "brokenvehicles/3.dff", "brokenvehicles/3.txd");
	AddSimpleModel(-1, 19379, -1047, "brokenvehicles/4.dff", "brokenvehicles/4.txd");
	AddSimpleModel(-1, 19379, -1048, "brokenvehicles/5.dff", "brokenvehicles/5.txd");
	AddSimpleModel(-1, 19379, -1049, "brokenvehicles/6.dff", "brokenvehicles/6.txd");
	// Base builds
	AddSimpleModel(-1, 19379, -1050, "basebuilds/barreira.dff", "basebuilds/barreira.txd");
	AddSimpleModel(-1, 19379, -1051, "basebuilds/barreiraferro.dff", "basebuilds/barreiraferro.txd");
	AddSimpleModel(-1, 19379, -1052, "basebuilds/barreiragrande.dff", "basebuilds/barreiragrande.txd");
	AddSimpleModel(-1, 19379, -1053, "basebuilds/torre.dff", "basebuilds/torre.txd");
	AddSimpleModel(-1, 19379, -1054, "basebuilds/tendagrande.dff", "basebuilds/tendagrande.txd");
	AddSimpleModel(-1, 19379, -1055, "basebuilds/cercamadeira.dff", "basebuilds/cercamadeira.txd");
	AddSimpleModel(-1, 19379, -1056, "basebuilds/murocon.dff", "basebuilds/murocon.txd");
	AddSimpleModel(-1, 19379, -1057, "basebuilds/murofer.dff", "basebuilds/murofer.txd");
	AddSimpleModel(-1, 19379, -1058, "basebuilds/muromad.dff", "basebuilds/muromad.txd");
	// Isqueiro
	AddSimpleModel(-1, 19379, -1059, "pubg/isqueiro.dff", "pubg/isqueiro.txd");
	// Food & drinks
	AddSimpleModel(-1, 19379, -1060, "food_drink/Can_beans.dff", "food_drink/Can_beans.txd");
	AddSimpleModel(-1, 19379, -1061, "food_drink/Can_Frank.dff", "food_drink/Can_Frank.txd");
	AddSimpleModel(-1, 19379, -1062, "food_drink/Can_Pasta.dff", "food_drink/Can_Pasta.txd");
	AddSimpleModel(-1, 19379, -1063, "food_drink/Can_sardines.dff", "food_drink/Can_sardines.txd");
	AddSimpleModel(-1, 19379, -1064, "food_drink/Soda_montadew.dff", "food_drink/Soda_montadew.txd");
	AddSimpleModel(-1, 19379, -1065, "food_drink/Soda_pepsi.dff", "food_drink/Soda_pepsi.txd");
	AddSimpleModel(-1, 19379, -1066, "food_drink/can_empty.dff", "food_drink/can_empty.txd");
	// Base builds
	AddSimpleModel(-1, 19379, -1067, "basebuilds/tentbig.dff", "basebuilds/tentbig.txd");
	// Trap
	AddSimpleModel(-1, 19379, -1068, "pubg/trapclose.dff", "pubg/trapclose.txd");
	AddSimpleModel(-1, 19379, -1069, "pubg/trapopen.dff", "pubg/trapopen.txd");
	// base builds
	AddSimpleModel(-1, 19379, -1070, "basebuilds/poco.dff", "basebuilds/poco.txd");
	// Grass
	AddSimpleModel(-1, 874, -1071, "pubg/grass.dff", "pubg/grass.txd");
	
	// New backpacks
	/*AddSimpleModel(-1, 19379, -2000, "backpacks/medium.dff", "backpacks/medium.txd");
	AddSimpleModel(-1, 19379, -2001, "backpacks/small.dff", "backpacks/small.txd");
	AddSimpleModel(-1, 19379, -2002, "backpacks/gamespot.dff", "backpacks/gamespot.txd");
	AddSimpleModel(-1, 19379, -2003, "backpacks/teddy.dff", "backpacks/teddy.txd");*/
	
	// Seller
	AddCharModel(136, 25000, "skins/zombies/seller.dff", "skins/zombies/seller.txd");
	
	// Zombies
	AddCharModel(136, 25001, "skins/zombies/1.dff", "skins/zombies/1.txd");
	AddCharModel(136, 25002, "skins/zombies/2.dff", "skins/zombies/2.txd");
	AddCharModel(136, 25003, "skins/zombies/3.dff", "skins/zombies/3.txd");
	AddCharModel(136, 25004, "skins/zombies/4.dff", "skins/zombies/4.txd");
	AddCharModel(136, 25005, "skins/zombies/5.dff", "skins/zombies/5.txd");
	AddCharModel(136, 25006, "skins/zombies/6.dff", "skins/zombies/6.txd");
	AddCharModel(136, 25007, "skins/zombies/7.dff", "skins/zombies/7.txd");
	AddCharModel(136, 25008, "skins/zombies/8.dff", "skins/zombies/8.txd");
	AddCharModel(136, 25009, "skins/zombies/9.dff", "skins/zombies/9.txd");
	AddCharModel(136, 25010, "skins/zombies/10.dff", "skins/zombies/10.txd");
	AddCharModel(136, 25011, "skins/zombies/11.dff", "skins/zombies/11.txd");
	AddCharModel(136, 25012, "skins/zombies/12.dff", "skins/zombies/12.txd");
	AddCharModel(136, 25013, "skins/zombies/13.dff", "skins/zombies/13.txd");
	AddCharModel(136, 25014, "skins/zombies/14.dff", "skins/zombies/14.txd");
	AddCharModel(136, 25015, "skins/zombies/15.dff", "skins/zombies/15.txd");
	AddCharModel(136, 25016, "skins/zombies/16.dff", "skins/zombies/16.txd");
	AddCharModel(129, 25017, "skins/zombies/17.dff", "skins/zombies/17.txd");
	AddCharModel(136, 25018, "skins/zombies/18.dff", "skins/zombies/18.txd");
	AddCharModel(136, 25019, "skins/zombies/19.dff", "skins/zombies/19.txd");
	AddCharModel(129, 25020, "skins/zombies/20.dff", "skins/zombies/20.txd");
	// Zombie gordo
	AddCharModel(5, 25021, "skins/zombies/fat.dff", "skins/zombies/fat.txd");
	// Zombies flamer
	AddCharModel(136, 25023, "skins/zombies/flamer.dff", "skins/zombies/flamer.txd");
	// Zombie lobos
	AddCharModel(136, 25024, "skins/zombies/wolf.dff", "skins/zombies/wolf.txd");
	// skins comuns
    AddCharModel(141, 21001, "skins/female/4_padrao/21001.dff", "skins/female/4_padrao/21001.txd");
    AddCharModel(240, 21002, "skins/male/4_padrao/21002.dff", "skins/male/4_padrao/21002.txd");
    AddCharModel(141, 21003, "skins/female/4_padrao/21003.dff", "skins/female/4_padrao/21003.txd");
    AddCharModel(240, 21004, "skins/male/4_padrao/21004.dff", "skins/male/4_padrao/21004.txd");
    // Negan
    AddCharModel(240, 22001, "skins/dimmy/1.dff", "skins/dimmy/1.txd");
    // Anjo
    AddCharModel(141, 22002, "skins/anjo/1.dff", "skins/anjo/1.txd");
    // Sarah
    AddCharModel(141, 22003, "skins/sarah/1.dff", "skins/sarah/1.txd");
    // Tommy
    AddCharModel(240, 22004, "skins/tommy/1.dff", "skins/tommy/1.txd");
    // Nicky
    AddCharModel(240, 22005, "skins/nicky/1.dff", "skins/nicky/1.txd");
    // Admins
    AddCharModel(211, 22006, "skins/admin/admin.dff", "skins/admin/admin.txd");
    // Premium
    AddCharModel(285, 22007, "skins/premium/johnwick.dff", "skins/premium/johnwick.txd");
    // Battle royale
    AddCharModel(285, 22008, "skins/premium/br.dff", "skins/premium/br.txd");
    // Youtuber
    AddCharModel(285, 22009, "skins/premium/yt.dff", "skins/premium/yt.txd");
    // Crates
    //SHOP_AddNewItem(0, CRATE_TYPE_DAILY, "invalid", "invalid", SKIN_RARITY_COMUM);
    SHOP_AddNewItem(0, CRATE_TYPE_SILVER, "invalid", "invalid", SKIN_RARITY_COMUM, .gender = 10, 														.cost = 1000);
    SHOP_AddNewItem(0, CRATE_TYPE_GOLD, "invalid", "invalid", SKIN_RARITY_RARE, .gender = 10, 															.cost = 1500);
    SHOP_AddNewItem(0, CRATE_TYPE_DIAMOND, "invalid", "invalid", SKIN_RARITY_LEGENDARY, .gender = 10, 													.cost = 2100);
    SHOP_AddNewItem(0, CRATE_TYPE_LEGENDARY, "invalid", "invalid", SKIN_RARITY_LEGENDARY, .gender = 10, 												.cost = 3000);
    SHOP_AddNewItem(0, CRATE_TYPE_ULTIMATE, "invalid", "invalid", SKIN_RARITY_ULTIMATE, .gender = 10, 													.cost = 3600);
    
    // New items (backpacks)
    /*SHOP_AddNewItem(0, -2000, "invalid", "invalid", SKIN_RARITY_RARE, .gender = 11, 																	.cost = 1000);
    SHOP_AddNewItem(0, -2001, "invalid", "invalid", SKIN_RARITY_RARE, .gender = 11, 																	.cost = 1000);
    SHOP_AddNewItem(0, -2002, "invalid", "invalid", SKIN_RARITY_RARE, .gender = 11, 																	.cost = 1000);
    SHOP_AddNewItem(0, -2003, "invalid", "invalid", SKIN_RARITY_RARE, .gender = 11, 																	.cost = 1000);*/
// -----------------------------------------------------------------------------
//                                   FEMALE
//------------------------------------------------------------------------------
	SHOP_AddNewItem(141, 20020, "skins/female/0_comum/20020.dff", "skins/female/0_comum/20020.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 3800);//
	SHOP_AddNewItem(141, 20021, "skins/female/0_comum/20021.dff", "skins/female/0_comum/20021.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 4800);//
	SHOP_AddNewItem(141, 20022, "skins/female/0_comum/20022.dff", "skins/female/0_comum/20022.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 3700);//
	SHOP_AddNewItem(141, 20023, "skins/female/0_comum/20023.dff", "skins/female/0_comum/20023.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 3700);//
	SHOP_AddNewItem(141, 20024, "skins/female/0_comum/20024.dff", "skins/female/0_comum/20024.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 4100);//
	SHOP_AddNewItem(141, 20025, "skins/female/0_comum/20025.dff", "skins/female/0_comum/20025.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 4100);//
	SHOP_AddNewItem(141, 20026, "skins/female/0_comum/20026.dff", "skins/female/0_comum/20026.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 5250);//
	SHOP_AddNewItem(141, 20027, "skins/female/0_comum/20027.dff", "skins/female/0_comum/20027.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 7300);//

	SHOP_AddNewItem(141, 20028, "skins/female/1_rare/20028.dff", "skins/female/1_rare/20028.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 4550);//
	SHOP_AddNewItem(141, 20029, "skins/female/1_rare/20029.dff", "skins/female/1_rare/20029.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 6900);//
	SHOP_AddNewItem(141, 20030, "skins/female/1_rare/20030.dff", "skins/female/1_rare/20030.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 8000);//
	SHOP_AddNewItem(141, 20031, "skins/female/1_rare/20031.dff", "skins/female/1_rare/20031.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 6500);//

	SHOP_AddNewItem(141, 20032, "skins/female/2_legendary/20032.dff", "skins/female/2_legendary/20032.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 5000);//
	SHOP_AddNewItem(141, 20033, "skins/female/2_legendary/20033.dff", "skins/female/2_legendary/20033.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 12000);

	SHOP_AddNewItem(141, 20034, "skins/female/3_ultimate/20034.dff", "skins/female/3_ultimate/20034.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 30000);
	SHOP_AddNewItem(141, 20035, "skins/female/3_ultimate/20035.dff", "skins/female/3_ultimate/20035.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 24500);
	SHOP_AddNewItem(141, 20036, "skins/female/3_ultimate/20036.dff", "skins/female/3_ultimate/20036.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 19000);
	SHOP_AddNewItem(141, 20037, "skins/female/3_ultimate/20037.dff", "skins/female/3_ultimate/20037.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 20000);

// -----------------------------------------------------------------------------
//                                   MALE
//------------------------------------------------------------------------------
	SHOP_AddNewItem(240, 20038, "skins/male/0_comum/20038.dff", "skins/male/0_comum/20038.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 3800);
	SHOP_AddNewItem(240, 20039, "skins/male/0_comum/20039.dff", "skins/male/0_comum/20039.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 5600);
	SHOP_AddNewItem(240, 20040, "skins/male/0_comum/20040.dff", "skins/male/0_comum/20040.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 5000);
    SHOP_AddNewItem(240, 20041, "skins/male/0_comum/20041.dff", "skins/male/0_comum/20041.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 7000);

    SHOP_AddNewItem(240, 20042, "skins/male/1_rare/20042.dff", "skins/male/1_rare/20042.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 9500);
    SHOP_AddNewItem(240, 20043, "skins/male/1_rare/20043.dff", "skins/male/1_rare/20043.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 9000);
    SHOP_AddNewItem(240, 20044, "skins/male/1_rare/20044.dff", "skins/male/1_rare/20044.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 7800);
    SHOP_AddNewItem(240, 20045, "skins/male/1_rare/20045.dff", "skins/male/1_rare/20045.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 4900);
    SHOP_AddNewItem(240, 20046, "skins/male/1_rare/20046.dff", "skins/male/1_rare/20046.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 5000);

    SHOP_AddNewItem(240, 20047, "skins/male/2_legendary/20047.dff", "skins/male/2_legendary/20047.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 15000);
    SHOP_AddNewItem(240, 20048, "skins/male/2_legendary/20048.dff", "skins/male/2_legendary/20048.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 13500);
    SHOP_AddNewItem(240, 20049, "skins/male/2_legendary/20049.dff", "skins/male/2_legendary/20049.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 23000);

    SHOP_AddNewItem(240, 20050, "skins/male/3_ultimate/20050.dff", "skins/male/3_ultimate/20050.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_MALE, 			.cost = 25000);
    SHOP_AddNewItem(240, 20051, "skins/male/3_ultimate/20051.dff", "skins/male/3_ultimate/20051.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_MALE, 			.cost = 45000);
    SHOP_AddNewItem(240, 20052, "skins/male/3_ultimate/20052.dff", "skins/male/3_ultimate/20052.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_MALE, 			.cost = 21500);
    SHOP_AddNewItem(240, 20053, "skins/male/3_ultimate/20053.dff", "skins/male/3_ultimate/20053.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_MALE, 			.cost = 15000);
    
    // Futures add
    SHOP_AddNewItem(141, 20054, "skins/female/3_ultimate/20054.dff", "skins/female/3_ultimate/20054.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 19000);
    SHOP_AddNewItem(240, 20055, "skins/male/1_rare/20055.dff", "skins/male/1_rare/20055.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 15000);
    SHOP_AddNewItem(141, 20056, "skins/female/2_legendary/20056.dff", "skins/female/2_legendary/20056.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 22000);
    SHOP_AddNewItem(141, 20057, "skins/female/2_legendary/20057.dff", "skins/female/2_legendary/20057.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 14000);
    SHOP_AddNewItem(240, 20058, "skins/male/2_legendary/20058.dff", "skins/male/2_legendary/20058.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 11000);
    SHOP_AddNewItem(240, 20059, "skins/male/2_legendary/20059.dff", "skins/male/2_legendary/20059.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 25000);
    SHOP_AddNewItem(141, 20060, "skins/female/3_ultimate/20060.dff", "skins/female/3_ultimate/20060.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 12100);
    SHOP_AddNewItem(141, 20061, "skins/female/0_comum/20061.dff", "skins/female/0_comum/20061.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 5000);
    SHOP_AddNewItem(141, 20062, "skins/female/0_comum/20062.dff", "skins/female/0_comum/20062.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 9000);
    SHOP_AddNewItem(141, 20063, "skins/female/0_comum/20063.dff", "skins/female/0_comum/20063.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 8800);
    SHOP_AddNewItem(141, 20064, "skins/female/0_comum/20064.dff", "skins/female/0_comum/20064.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 3700);
    SHOP_AddNewItem(141, 20065, "skins/female/0_comum/20065.dff", "skins/female/0_comum/20065.txd", SKIN_RARITY_COMUM, SKIN_GENDER_FEMALE, 				.cost = 4100);
    SHOP_AddNewItem(141, 20066, "skins/female/1_rare/20066.dff", "skins/female/1_rare/20066.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 12700);
    SHOP_AddNewItem(141, 20067, "skins/female/1_rare/20067.dff", "skins/female/1_rare/20067.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 10600);
    SHOP_AddNewItem(141, 20068, "skins/female/1_rare/20068.dff", "skins/female/1_rare/20068.txd", SKIN_RARITY_RARE, SKIN_GENDER_FEMALE, 				.cost = 7000);
	SHOP_AddNewItem(141, 20069, "skins/female/2_legendary/20069.dff", "skins/female/2_legendary/20069.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 5000);
    SHOP_AddNewItem(141, 20070, "skins/female/2_legendary/20070.dff", "skins/female/2_legendary/20070.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 28000);
    SHOP_AddNewItem(141, 20071, "skins/female/2_legendary/20071.dff", "skins/female/2_legendary/20071.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 20000);
    SHOP_AddNewItem(141, 20072, "skins/female/2_legendary/20072.dff", "skins/female/2_legendary/20072.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_FEMALE, 	.cost = 20000);
	SHOP_AddNewItem(141, 20073, "skins/female/3_ultimate/20073.dff", "skins/female/3_ultimate/20073.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_FEMALE, 	.cost = 14000);

	SHOP_AddNewItem(240, 20074, "skins/male/0_comum/20074.dff", "skins/male/0_comum/20074.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 4000);
    SHOP_AddNewItem(240, 20075, "skins/male/0_comum/20075.dff", "skins/male/0_comum/20075.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 4500);
    SHOP_AddNewItem(240, 20076, "skins/male/0_comum/20076.dff", "skins/male/0_comum/20076.txd", SKIN_RARITY_COMUM, SKIN_GENDER_MALE, 					.cost = 7000);
	SHOP_AddNewItem(240, 20077, "skins/male/1_rare/20077.dff", "skins/male/1_rare/20077.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 9000);
    SHOP_AddNewItem(240, 20078, "skins/male/1_rare/20078.dff", "skins/male/1_rare/20078.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 10000);
    SHOP_AddNewItem(240, 20079, "skins/male/1_rare/20079.dff", "skins/male/1_rare/20079.txd", SKIN_RARITY_RARE, SKIN_GENDER_MALE, 						.cost = 7000);
	SHOP_AddNewItem(240, 20080, "skins/male/2_legendary/20080.dff", "skins/male/2_legendary/20080.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 13000);
    SHOP_AddNewItem(240, 20081, "skins/male/2_legendary/20081.dff", "skins/male/2_legendary/20081.txd", SKIN_RARITY_LEGENDARY, SKIN_GENDER_MALE, 		.cost = 12900);
	SHOP_AddNewItem(240, 20082, "skins/male/3_ultimate/20082.dff", "skins/male/3_ultimate/20082.txd", SKIN_RARITY_ULTIMATE, SKIN_GENDER_MALE, 			.cost = 20000);
}

stock SHOP_OpenDatabase()
{
	shop_database = db_open(SHOP_Database);
	
	db_query(shop_database, "PRAGMA synchronous = OFF");
}

stock SHOP_AddNewItem(baseid, modelid, dff[], txd[], rarity = SKIN_RARITY_COMUM, gender = SKIN_GENDER_FEMALE, cost = 5000, name[] = "Skin")
{
//    cost += 800;

	new
	    DBResult:result_sql,
		sql_string[256];

	format(sql_string, sizeof (sql_string), "select * from skins where id = '%d' LIMIT 1", modelid);
    result_sql = db_query(shop_database, sql_string);

	if (db_num_rows(result_sql))
	{
	    format(sql_string, sizeof (sql_string), "UPDATE skins SET price='%d', rarity='%d', gender='%d', name='%s' where id='%d'", cost, rarity, gender, name, modelid);
		db_query(shop_database, sql_string);
	} else {
	    format(sql_string, sizeof (sql_string), "INSERT INTO skins (id, price, rarity, gender, name, date) values ('%d','%d','%d','%d','%s',current_timestamp)", modelid, cost, rarity, gender, name);
		db_query(shop_database, sql_string);
	}
	db_free_result(result_sql);

	// Add char model
	if (modelid > 20000)
		AddCharModel(baseid, modelid, dff, txd);
}

stock SHOP_SetPlayerMode(playerid, modeid = SKIN_SELECT_SHOP)
{
	SetPVarInt(playerid, "SHOP_mode", modeid);

	SHOP_SetPlayerOrder(playerid);
}

stock SHOP_SetPlayerOrder(playerid, orderby = ORDER_BY_LCOST)
{
	SetPVarInt(playerid, "SHOP_order", orderby);

    ps_current_page[playerid] = 0;

	SHOP_UpdateOrder(playerid);
	SHOP_UpdateTexts(playerid);
}

stock SHOP_ShowForPlayer(playerid)
{
	if (GetPVarInt(playerid, "p_vshop"))
	    return 0;
	    
    hideLoginMenu(playerid, false);
    
    SHOP_HideBoxDiscription(playerid);
    
    // Camera
	InterpolateCameraPos(playerid, 2535.772949, -1674.579956, 1016.038635, 2535.758056, -1675.458129, 1016.110229, 750);
	InterpolateCameraLookAt(playerid, 2530.988769, -1675.701416, 1015.115051, 2531.520996, -1672.939453, 1015.271423, 750);
    
    SetPVarInt(playerid, "vmenuLogin", 1);
    
    switch(GetPVarInt(playerid, "SHOP_mode"))
    {
		case SKIN_SELECT_SHOP:
		{
		    TextDrawColor(serverShopTexts[2], 0xFFFFFFFF);
		    TextDrawColor(serverShopTexts[3], -156);
		}
		case SKIN_SELECT_INVENTORY:
		{
		    TextDrawColor(serverShopTexts[2], -156);
		    TextDrawColor(serverShopTexts[3], 0xFFFFFFFF);
		}
	}
    
	for(new text; text < 10; text++)
	{
	    TextDrawShowForPlayer(playerid, serverShopTexts[text]);
	}

	SetPVarInt(playerid, "p_selecteditem", -1);
	SetPVarInt(playerid, "p_daysitem", 1);

	PlayerTextDrawShow(playerid, playerShopText[9]);

	SHOP_SetPlayerOrder(playerid);
	
	SHOP_UpdateTexts(playerid);

	SetPVarInt(playerid, "p_vshop", 1);

	return 1;
}

stock SHOP_HideForPlayer(playerid)
{
   	if (!GetPVarInt(playerid, "p_vshop"))
	    return 0;

    SHOP_HideBoxDiscription(playerid);

	for(new text; text < sizeof serverShopTexts; text++)
	{
	    TextDrawHideForPlayer(playerid, serverShopTexts[text]);
	}
	
	for(new text; text < 16; text++)
	{
		PlayerTextDrawHide(playerid, playerShopText[text]);
	}
	
	InterpolateCameraPos(playerid, 2535.758056, -1675.458129, 1016.110229, 2535.772949, -1674.579956, 1016.038635, 750);
	InterpolateCameraLookAt(playerid, 2531.520996, -1672.939453, 1015.271423, 2530.988769, -1675.701416, 1015.115051, 750);
	
	showLoginMenu(playerid, true);
	
	DeletePVar(playerid, "p_vshop");
	
	DestroyActor(PlayerData[playerid][dActorId]);

	if (PlayerData[playerid][dSkin] != -1)
	{
	    PlayerData[playerid][dActorId] = CreateActor(PlayerData[playerid][dSkin], 2533.1841,-1674.5376,1015.4986,269.0892);
	    SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
	} else {
	    PlayerData[playerid][dActorId] = CreateActor(PlayerData[playerid][dTempSkin], 2533.1841,-1674.5376,1015.4986,269.0892);
	    SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
	}
	return 1;
}

stock SHOP_UpdateOrder(playerid)
{
	new query[185];

    switch(GetPVarInt(playerid, "SHOP_mode"))
    {
		case SKIN_SELECT_SHOP:
		{
			switch(GetPVarInt(playerid, "SHOP_order"))
			{
			    case ORDER_BY_RANDOM: query = "SELECT * FROM skins ORDER BY random() LIMIT 100";
				case ORDER_BY_LCOST	: query = "SELECT * FROM skins ORDER BY price ASC LIMIT 100";
				case ORDER_BY_BCOST	: query = "SELECT * FROM skins ORDER BY price DESC LIMIT 100";
				case ORDER_BY_RARITY: query = "SELECT * FROM skins ORDER BY rarity DESC LIMIT 100";
				case ORDER_BY_DATE	: query = "SELECT * FROM skins ORDER BY date DESC LIMIT 100";
				case ORDER_BY_MALE	: query = "SELECT * FROM skins WHERE gender = 0 LIMIT 100";
				case ORDER_BY_FEMALE: query = "SELECT * FROM skins WHERE gender = 1 LIMIT 100";
				case ORDER_BY_CRATES: query = "SELECT * FROM skins WHERE gender = 10 ORDER BY price ASC LIMIT 100";
			}
		}
		case SKIN_SELECT_INVENTORY:
		{
			switch(GetPVarInt(playerid, "SHOP_order"))
			{
			    case ORDER_BY_RANDOM: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' ORDER BY random() LIMIT 100", getNome(playerid));
				case ORDER_BY_LCOST	: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' ORDER BY price ASC LIMIT 100", getNome(playerid));
				case ORDER_BY_BCOST	: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' ORDER BY price DESC LIMIT 100", getNome(playerid));
				case ORDER_BY_RARITY: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' ORDER BY rarity DESC LIMIT 100", getNome(playerid));
				case ORDER_BY_DATE	: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' ORDER BY date DESC LIMIT 100", getNome(playerid));
				case ORDER_BY_MALE	: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' and gender = 0 LIMIT 100", getNome(playerid));
				case ORDER_BY_FEMALE: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' and gender = 1 LIMIT 100", getNome(playerid));
				case ORDER_BY_CRATES: format(query, sizeof query, "SELECT * FROM player_skins WHERE owner = '%s' and gender = 10 ORDER BY price ASC LIMIT 100", getNome(playerid));
			}
		}
	}
	
	SHOP_HideBoxDiscription(playerid);

    SHOP_StoreQuery(playerid, query);
}

stock SHOP_UpdateTexts(playerid)
{
    new page = ps_current_page[playerid];
    new count_rows = ps_num_rows[playerid];
    new count_index;
    new string[128];

	for(new index = page * 9; index < count_rows; index++)
	{
	    if (count_index >= 9)
	        break;

		format(string, sizeof string, "mdl-1003:%d", ps_array[playerid][index][ps_modelid]);
		PlayerTextDrawSetString(playerid, playerShopText[count_index], string);
		PlayerTextDrawShow(playerid, playerShopText[count_index]);

        count_index ++;
	}

	for(new index = count_index; index < 9; index++)
	{
	    PlayerTextDrawHide(playerid, playerShopText[index]);
	}

	format(string, sizeof string, "%d-%d", page + 1, (count_rows / 9) + 1);
	PlayerTextDrawSetString(playerid, playerShopText[9], string);
	
	for(new text = 10; text < 16; text++)
	{
		PlayerTextDrawHide(playerid, playerShopText[text]);
	}
	TextDrawHideForPlayer(playerid, serverShopTexts[9]);
	TextDrawHideForPlayer(playerid, serverShopTexts[10]);
	TextDrawHideForPlayer(playerid, serverShopTexts[11]);
	TextDrawHideForPlayer(playerid, serverShopTexts[12]);
	TextDrawHideForPlayer(playerid, serverShopTexts[13]);
}

stock SHOP_StoreQuery(playerid, query[])
{
	new DBResult:result_sql;

    result_sql = db_query(shop_database, query);

    ps_num_rows[playerid] = db_num_rows(result_sql);

    // fix possible bug
    if (ps_num_rows[playerid] > MAX_SHOP_ITENS)
        ps_num_rows[playerid] = MAX_SHOP_ITENS;

    // Store results in array
    for(new row; row < ps_num_rows[playerid]; row++)
    {
        ps_array[playerid][row][ps_modelid] = db_get_field_assoc_int(result_sql, "id");
        ps_array[playerid][row][ps_cost] = db_get_field_assoc_int(result_sql, "price");
        ps_array[playerid][row][ps_rarity] = db_get_field_assoc_int(result_sql, "rarity");
        ps_array[playerid][row][ps_gender] = db_get_field_assoc_int(result_sql, "gender");
        if (GetPVarInt(playerid, "SHOP_mode") == SKIN_SELECT_INVENTORY){
            ps_array[playerid][row][ps_ai] = db_get_field_assoc_int(result_sql, "AI");
        	ps_array[playerid][row][ps_time] = db_get_field_assoc_int(result_sql, "time");
        	ps_array[playerid][row][ps_legacy] = db_get_field_assoc_int(result_sql, "legacy");
		}
        // next row
        db_next_row(result_sql);
    }

    db_free_result(result_sql);
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (GetPVarInt(playerid, "p_vshop"))
	{
		if (clickedid == serverShopTexts[7])
		{
		    ps_current_page[playerid] --;

		    if (ps_current_page[playerid] < 0)
		        return ps_current_page[playerid] = 0, true;

            SHOP_HideBoxDiscription(playerid);

	        SHOP_UpdateTexts(playerid);
		}
		else if (clickedid == serverShopTexts[8])
		{
		    ps_current_page[playerid] ++;

		    if (ps_current_page[playerid] > (ps_num_rows[playerid] / 9))
		        return ps_current_page[playerid] = (ps_num_rows[playerid] / 9), true;

            SHOP_HideBoxDiscription(playerid);

	        SHOP_UpdateTexts(playerid);
		}
		else if (clickedid == serverShopTexts[1])
		{
		    SHOP_HideForPlayer(playerid);
		}
		else if (clickedid == serverShopTexts[5])
		{
		    SHOP_SetPlayerOrder(playerid, .orderby = ORDER_BY_MALE);
		}
		else if (clickedid == serverShopTexts[6])
		{
		    SHOP_SetPlayerOrder(playerid, .orderby = ORDER_BY_FEMALE);
		}
		else if (clickedid == serverShopTexts[4])
		{
		    SHOP_SetPlayerOrder(playerid, .orderby = ORDER_BY_CRATES);
		}
		else if (clickedid == serverShopTexts[2])
		{
		    TextDrawColor(serverShopTexts[2], 0xFFFFFFFF);
		    TextDrawColor(serverShopTexts[3], -156);
		    
		    TextDrawShowForPlayer(playerid, serverShopTexts[2]);
		    TextDrawShowForPlayer(playerid, serverShopTexts[3]);
		    
		    SHOP_SetPlayerMode(playerid, .modeid = SKIN_SELECT_SHOP);
		}
		else if (clickedid == serverShopTexts[3])
		{
		    TextDrawColor(serverShopTexts[2], -156);
		    TextDrawColor(serverShopTexts[3], 0xFFFFFFFF);

		    TextDrawShowForPlayer(playerid, serverShopTexts[2]);
		    TextDrawShowForPlayer(playerid, serverShopTexts[3]);
		    SHOP_SetPlayerMode(playerid, .modeid = SKIN_SELECT_INVENTORY);
		}
		else if (clickedid == serverShopTexts[9])
		{
		    new days = GetPVarInt(playerid, "p_daysitem");

		    if (days < 2) return 0;

		    new index = GetPVarInt(playerid, "p_selecteditem");

		    days--;

		    new string[25];

		    SetPVarInt(playerid, "p_daysitem", days);

			format(string, sizeof string, "~r~ZP ~w~~h~%s", getMoneyFormat(days * (ps_array[playerid][index][ps_cost]/DIVIDER_RENT)));
			PlayerTextDrawSetString(playerid, playerShopText[13], string);
			format(string, sizeof string, "%d DAYS", days);
			PlayerTextDrawSetString(playerid, playerShopText[14], string);
		}
		else if (clickedid == serverShopTexts[10])
		{
		    new days = GetPVarInt(playerid, "p_daysitem");

		    if (days > 14) return 0;

		    new index = GetPVarInt(playerid, "p_selecteditem");

		    days++;

	        new string[25];

		    SetPVarInt(playerid, "p_daysitem", days);

			format(string, sizeof string, "~r~ZP ~w~~h~%s", getMoneyFormat(days * (ps_array[playerid][index][ps_cost]/DIVIDER_RENT)));
			PlayerTextDrawSetString(playerid, playerShopText[13], string);
			format(string, sizeof string, "%d DAYS", days);
			PlayerTextDrawSetString(playerid, playerShopText[14], string);
		}
		else if (clickedid == serverShopTexts[12])
		{
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
				if (GetPVarInt(playerid, "SHOP_mode") == SKIN_SELECT_INVENTORY)
				{
					ShowPlayerDialogTextdraw(playerid, 565, "Voce deseja realmente excluir este item?");
				}
			}
		    return 1;
		}
		else if (clickedid == serverBoxDiscription[1])
		{
		    SHOP_HideBoxDiscription(playerid);
		}
		else if (clickedid == serverShopTexts[13])
		{
		    ShowPlayerPrizeDialog(playerid);
		}
	}
 	#if defined pOPCTD
  		return pOPCTD(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw pOPCTD
#if defined pOPCTD
	forward pOPCTD(playerid, Text:clickedid);
#endif

stock SHOP_CreateActor(playerid)
{
	DestroyActor(PlayerData[playerid][dActorId]);

	if (PlayerData[playerid][dSkin] != -1)
	{
	    PlayerData[playerid][dActorId] = CreateActor(PlayerData[playerid][dSkin], 2533.1841,-1674.5376,1015.4986,269.0892);
	    SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
	} else {
	    PlayerData[playerid][dActorId] = CreateActor(PlayerData[playerid][dTempSkin], 2533.1841,-1674.5376,1015.4986,269.0892);
	    SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
	}
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (GetPVarInt(playerid, "p_vshop"))
	{
		// Buy / use
		if (playertextid == playerShopText[10])
		{
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
				if (GetPVarInt(playerid, "SHOP_mode") == SKIN_SELECT_INVENTORY)
				{
				    if (ps_array[playerid][index][ps_modelid] < 20000)
				    {
				        SHOP_OnPlayerUseCrate(playerid, ps_array[playerid][index][ps_modelid]);
				    } else {
					    PlayerData[playerid][dSkin] = ps_array[playerid][index][ps_modelid];

						SHOP_CreateActor(playerid);

						savePlayerAccount(playerid);
					}
				} else {
					new string[128];
					format(string, sizeof string, "Voce deseja comprar este item por ~r~ZP ~w~~h~%s?", getMoneyFormat(ps_array[playerid][index][ps_cost]));
					ShowPlayerDialogTextdraw(playerid, 558, string);
				}
			}
		    return 1;
		}
		// Temp buy / sell
		else if (playertextid == playerShopText[12])
		{
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
	  		    if (ps_array[playerid][index][ps_modelid] < 20000)
	  		        return 1;
	  		
	  		    new string[128];
				if (GetPVarInt(playerid, "SHOP_mode") == SKIN_SELECT_INVENTORY)
				{
					format(string, sizeof string, "Voce deseja vender essa skin por ~g~$ ~w~~h~%s?", getMoneyFormat(ps_array[playerid][index][ps_cost]));
					ShowPlayerDialogTextdraw(playerid, 560, string);
				} else {
				    new days = GetPVarInt(playerid, "p_daysitem");
				
					format(string, sizeof string, "Deseja alugar essa skin (%d dias) por ~r~ZP ~w~~h~%s?", days, getMoneyFormat(days * (ps_array[playerid][index][ps_cost]/DIVIDER_RENT)));
					ShowPlayerDialogTextdraw(playerid, 559, string);
				}
			}
		    return 1;
		}
		for(new text; text < 9; text++)
		{
		    if (playertextid == playerShopText[text])
		    {
		        new index = text + (ps_current_page[playerid] * 9);

				if (index < 0 || index > MAX_SHOP_ITENS)
				    return 0;

				if (ps_array[playerid][index][ps_modelid] < 20000)
				{
				    SHOP_OnPlayerSelectCrate(playerid, ps_array[playerid][index][ps_modelid]);
				} else {
				    SHOP_HideBoxDiscription(playerid);
				}

		        SHOP_OnPlayerSelectItem(playerid, index,
					ps_array[playerid][index][ps_modelid],
					ps_array[playerid][index][ps_cost],
					ps_array[playerid][index][ps_rarity],
					ps_array[playerid][index][ps_gender],
					ps_array[playerid][index][ps_time],
					ps_array[playerid][index][ps_legacy]);

				return 1;
			}
		}
	}
 	#if defined eOPCPTD
  		return eOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw eOPCPTD
#if defined eOPCPTD
	forward eOPCPTD(playerid, PlayerText:playertextid);
#endif

stock SHOP_OnPlayerUseCrate(playerid, type)
{
	new index = GetPVarInt(playerid, "p_selecteditem");
	if (index > -1)
	{
	    SHOP_DeleteSkin(playerid, ps_array[playerid][index][ps_ai]);

        SHOP_OpenCrate(playerid, type);

	    SHOP_SetPlayerOrder(playerid, GetPVarInt(playerid, "SHOP_order"));
	}
}

stock SHOP_OnPlayerSelectCrate(playerid, type)
{
	stringGlobal[0] = EOS;
	
	switch (type)
	{
		case CRATE_TYPE_DAILY:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "DAILY LOGIN CRATE");
		    
		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 5-15 hours~n~");
		    strcat(stringGlobal, "~t~ Receive $1,500 money~n~");
		    strcat(stringGlobal, "~t~ Receive 500 experience~n~");
		}
		case CRATE_TYPE_SILVER:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "SILVER CRATE");

		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 24-35 hours~n~");
		    strcat(stringGlobal, "~t~ Receive $2,500 money~n~");
		    strcat(stringGlobal, "~t~ Receive 600 experience~n~");
		}
		case CRATE_TYPE_GOLD:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "GOLD CRATE");

		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 3-5 days~n~");
		    strcat(stringGlobal, "~t~ 5% chance to receive a permanent skin~n~");
		    strcat(stringGlobal, "~t~ Receive $5,000 money~n~");
		    strcat(stringGlobal, "~t~ Receive 800 experience~n~");
		}
		case CRATE_TYPE_DIAMOND:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "DIAMOND CRATE");

		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 5-10 days~n~");
		    strcat(stringGlobal, "~t~ 8% chance to receive a permanent skin~n~");
		    strcat(stringGlobal, "~t~ Receive $8,000 money~n~");
		    strcat(stringGlobal, "~t~ Receive 1000 experience~n~");
		}
		case CRATE_TYPE_LEGENDARY:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "LEGENDARY CRATE");

		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 10-15 days~n~");
		    strcat(stringGlobal, "~t~ 10% chance to receive a permanent skin~n~");
		    strcat(stringGlobal, "~t~ Receive $11,000 money~n~");
		    strcat(stringGlobal, "~t~ Receive 1500 experience~n~");
		}
		case CRATE_TYPE_ULTIMATE:
		{
		    // name of crate
		    PlayerTextDrawSetString(playerid, boxDiscription[0], "ULTIMATE CRATE");

		    // itens in crate
		    strcat(stringGlobal, "~t~ Receive a random skin for 15-30 days~n~");
		    strcat(stringGlobal, "~t~ 15% chance to receive a permanent skin~n~");
		    strcat(stringGlobal, "~t~ Receive $16,000 money~n~");
		    strcat(stringGlobal, "~t~ Receive 2000 experience~n~");
		}
	}
	PlayerTextDrawSetString(playerid, boxDiscription[1], stringGlobal);
	
	SHOP_ShowBoxDiscription(playerid);
}

stock SHOP_OnPlayerSelectItem(playerid, index, modelid, cost, rarity, gender, time, legacy)
{
	#pragma unused gender, rarity
	
	//if (modelid < 20000)
	    //return 0;

	SetPVarInt(playerid, "p_selecteditem", index);
	SetPVarInt(playerid, "p_daysitem", 1);
	
	new days = GetPVarInt(playerid, "p_daysitem");
	
	new string[128];
	
    switch(GetPVarInt(playerid, "SHOP_mode"))
    {
		case SKIN_SELECT_SHOP:
		{
			format(string, sizeof string, "~r~ZP ~w~~h~%s", getMoneyFormat(cost));
			PlayerTextDrawSetString(playerid, playerShopText[11], string);
			
			format(string, sizeof string, "~r~ZP ~w~~h~%s", getMoneyFormat(days * (cost/DIVIDER_RENT)));
			PlayerTextDrawSetString(playerid, playerShopText[13], string);
			
			PlayerTextDrawSetString(playerid, playerShopText[10], "mdl-1002:button1");
			PlayerTextDrawSetString(playerid, playerShopText[12], "mdl-1002:button2");
			
			for(new text = 10; text < 15; text++)
			{
				PlayerTextDrawShow(playerid, playerShopText[text]);
			}
			
			if (modelid > 10)
			{
				TextDrawShowForPlayer(playerid, serverShopTexts[9]);
				TextDrawShowForPlayer(playerid, serverShopTexts[10]);

				format(string, sizeof string, "%d DAYS", days);
				PlayerTextDrawSetString(playerid, playerShopText[14], string);
			
				DestroyActor(PlayerData[playerid][dActorId]);

	    		PlayerData[playerid][dActorId] = CreateActor(modelid, 2533.1841,-1674.5376,1015.4986,269.0892);
	    		SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
			} else {
				TextDrawHideForPlayer(playerid, serverShopTexts[9]);
				TextDrawHideForPlayer(playerid, serverShopTexts[10]);
				PlayerTextDrawHide(playerid, playerShopText[12]);
				PlayerTextDrawHide(playerid, playerShopText[13]);
				PlayerTextDrawHide(playerid, playerShopText[14]);
			}
		}
		case SKIN_SELECT_INVENTORY:
		{
		    PlayerTextDrawHide(playerid, playerShopText[11]);
			format(string, sizeof string, "~g~$ ~w~~h~%s", getMoneyFormat(cost));
			PlayerTextDrawSetString(playerid, playerShopText[13], string);

			PlayerTextDrawSetString(playerid, playerShopText[10], "mdl-1002:button3");
			PlayerTextDrawSetString(playerid, playerShopText[12], "mdl-1002:button4");

			PlayerTextDrawShow(playerid, playerShopText[10]);
			TextDrawShowForPlayer(playerid, serverShopTexts[12]);
			if (!legacy && time == -1 && modelid > 10)
			{
				PlayerTextDrawShow(playerid, playerShopText[12]);
				PlayerTextDrawShow(playerid, playerShopText[13]);
				TextDrawShowForPlayer(playerid, serverShopTexts[13]);
			} else {
				PlayerTextDrawHide(playerid, playerShopText[12]);
				PlayerTextDrawHide(playerid, playerShopText[13]);
				TextDrawHideForPlayer(playerid, serverShopTexts[13]);
			}
			
			if (time > -1 && modelid > 10)
			{
				format(string, sizeof string, "%s", gettime() > time ? ("Expired") : (ConvertTimeSkin(time - gettime())));
				PlayerTextDrawSetString(playerid, playerShopText[15], string);
				PlayerTextDrawShow(playerid, playerShopText[15]);
			    TextDrawShowForPlayer(playerid, serverShopTexts[11]);
			} else {
				PlayerTextDrawHide(playerid, playerShopText[15]);
			    TextDrawHideForPlayer(playerid, serverShopTexts[11]);
			}
			
			if (modelid > 10)
			{
				DestroyActor(PlayerData[playerid][dActorId]);

		    	PlayerData[playerid][dActorId] = CreateActor(modelid, 2533.1841,-1674.5376,1015.4986,269.0892);
		    	SetActorVirtualWorld(PlayerData[playerid][dActorId], playerid + MAX_PLAYERS);
			}
		}
	}
	return 1;
}

stock SHOP_GiveItem(playerid, modelid, cost, rarity, gender, time = -1, legacy = 0, name[] = "Skin name", notification = 1)
{
	#pragma unused name
	new
		sql_string[356];

	format(sql_string, sizeof (sql_string),
	"INSERT INTO player_skins (owner, id, price, rarity, gender, time, legacy, date, notification) VALUES ('%s','%d','%d','%d','%d','%d','%d',current_timestamp,'%d')",
	getNome(playerid), modelid, cost, rarity, gender, time, legacy, notification);
	
	db_free_result(db_query(shop_database, sql_string));
	
	new textname[20];
   	format(textname, sizeof textname, "mdl-1003:%d", modelid);
   	ShowPlayerReward(playerid, textname, time == -1 ? ("PERMANENT") : (ConvertTimeSkin(time - gettime())));
}

stock SHOP_GiveDailyCrate(playerid)
{
	if (gettime() > PlayerData[playerid][dDailyCrate])
	{
	    // give daily crate
	    SHOP_GiveItem(playerid, .modelid = CRATE_TYPE_DAILY, .cost = 0, .rarity = SKIN_RARITY_COMUM, .gender = 10);
	
	    // wait 1 day to give another
	    PlayerData[playerid][dDailyCrate] = gettime() + 86400;
	} else {
	    SHOP_CheckNewItems(playerid);
	}
}

stock SHOP_EncomendarItem(nickname[], modelid, cost = 0, rarity = 1, gender = 0, time = -1, legacy = 0, name[] = "Skin name", notification = 0)
{
	#pragma unused name
	new
		sql_string[356];

	format(sql_string, sizeof (sql_string),
	"INSERT INTO player_skins (owner, id, price, rarity, gender, time, legacy, date, notification) VALUES ('%s','%d','%d','%d','%d','%d','%d',current_timestamp,'%d')",
	nickname, modelid, cost, rarity, gender, time, legacy, notification);

	db_free_result(db_query(shop_database, sql_string));
	
	new playerid = getId(nickname);
	
	if (playerid != INVALID_PLAYER_ID)
	{
	    if (PlayerData[playerid][dLogged])
	    {
	        SHOP_CheckNewItems(playerid);
	    }
	}
}

CMD:darskin(playerid, params[])
{
	if (PlayerData[playerid][dAdmin] < 6)
		return SendClientMessage(playerid, corError, "ERROR: {888888}Você não tem permissão para usar este comando.");
		
	new nick[24], model, gend;
	
	if (sscanf(params, "s[24]dd", nick, model, gend))
	    return SendClientMessage(playerid, -1, "/darskin <nick-correto> <modelid> <sexo (0 - homem | 1 - mulher)>");
	
	SHOP_EncomendarItem(nick, model, .cost = 0, .gender = gend, .time = -1, .legacy = 1);
	
	SendClientMessagef(playerid, corCinza, "Skin de modelo %d enviada com sucesso para o nick: %s", model, nick);
	
	return 1;
}

stock SHOP_CheckNewItems(playerid)
{
	new sql_string[128];
	new DBResult:sql_result;
	
	format(sql_string, sizeof (sql_string), "SELECT * FROM player_skins WHERE notification = 0 and owner = '%s' LIMIT 1", getNome(playerid));
	sql_result = db_query(shop_database, sql_string);
	
	if (db_num_rows(sql_result))
	{
		new textname[20];
		new time = db_get_field_assoc_int(sql_result, "time");
	   	format(textname, sizeof textname, "mdl-1003:%d", db_get_field_assoc_int(sql_result, "id"));
	   	ShowPlayerReward(playerid, textname, time == -1 ? ("PERMANENT") : (ConvertTimeSkin(time - gettime())));
	   	
	   	format(sql_string, sizeof sql_string, "UPDATE player_skins SET notification = 1 WHERE AI = '%d'", db_get_field_assoc_int(sql_result, "AI"));
	   	db_query(shop_database, sql_string);
	   	
	   	db_free_result(sql_result);
	   	return 1;
	}
	db_free_result(sql_result);
	
	return 0;
}

stock SHOP_DeleteSkin(playerid, AI)
{
	#pragma unused playerid
	new
		sql_string[75];

	format(sql_string, sizeof (sql_string), "DELETE FROM player_skins WHERE AI = '%d'", AI);

	db_free_result(db_query(shop_database, sql_string));
}

stock SHOP_PrizeItem(AI, nickname[])
{
	new
		sql_string[128];

	format(sql_string, sizeof (sql_string), "UPDATE player_skins SET `owner` = '%s', notification = 0 WHERE AI = '%d'", nickname, AI);

	db_free_result(db_query(shop_database, sql_string));
	
	new playerid = getId(nickname);

	if (playerid != INVALID_PLAYER_ID)
	{
	    if (PlayerData[playerid][dLogged])
	    {
	        SHOP_CheckNewItems(playerid);
	    }
	}
}

stock SHOP_DeleteExpiredItems()
{
	new
		sql_string[75];

	format(sql_string, sizeof (sql_string), "DELETE FROM player_skins WHERE time < '%d' and time != '-1'", gettime());
	db_free_result(db_query(shop_database, sql_string));
}

stock ShowPlayerPrizeDialog(playerid)
{
	ShowPlayerDialog(playerid, 821, DIALOG_STYLE_INPUT, " ",
	"{FFFFFF}* Digite o nome/id para quem deseja enviar este item como presente\n\n\
	{00AAFF}O jogador que receberá a skin será informado imediatamente e deve estar online.\n\
	Certifique-se de que o id/nick digitado está correto, pois não terá reembolso da skin selecionada.", "Enviar", "Cancelar");
}

stock SHOP_IsPlayerHaveSkinId(playerid, modelid)
{
	new
		sql_string[135],
		DBResult:sql_result;

	format(sql_string, sizeof (sql_string), "SELECT id FROM player_skins WHERE id = '%d' AND owner = '%s' LIMIT 1", modelid, getNome(playerid));

	sql_result = db_query(shop_database, sql_string);
	
	if (db_num_rows(sql_result))
	{
	    db_free_result(sql_result);
	    return 1;
	}
	db_free_result(sql_result);
	return 0;
}

stock SHOP_FixSkin(playerid)
{
	if (!SHOP_IsPlayerHaveSkinId(playerid, PlayerData[playerid][dSkin]))
	{
	    PlayerData[playerid][dSkin] = -1;
	    PlayerData[playerid][dTempSkin] = 21001 + random(4);
	    
	    return 0;
	}
	
	return 1;
}


/*
public OnPlayerRequestDownload(playerid, type, crc)
{
	if (gettime() > GetPVarInt(playerid, "p_reqtime"))
	{
	    //TogglePlayerSpectating(playerid, true);
	    
	    if (GetPVarInt(playerid, "p_reqtime") == 0) {
	    
			PlayAudioStreamForPlayer(playerid, "https://sites.google.com/site/znationdayzsamp/sounds/Untitled.mp3?");
			
			clearPlayerChat(playerid);
			
			SetPlayerTime(playerid, 0, 0);
			
			SetPlayerWeather(playerid, 7);
		}
	    
	    if (GetPVarInt(playerid, "p_requests") == 0)
	    {
			InterpolateCameraPos(playerid, 237.112899, -283.291381, 4.823380, 236.748443, 134.913452, 7.954418, 400000);
			InterpolateCameraLookAt(playerid, 237.108535, -278.291534, 4.860813, 236.744079, 139.913314, 7.991851, 400000);
			SetPlayerPos(playerid, 237.112899, -283.291381, 4.823380 - 10.0);
			
			SetPVarInt(playerid, "p_requests", 1);
		}
	    else if (GetPVarInt(playerid, "p_requests") == 1)
	    {
			InterpolateCameraPos(playerid, -856.914855, -2166.850830, 121.383178, -2354.097167, -2532.358886, 64.581443, 400000);
			InterpolateCameraLookAt(playerid, -861.892333, -2166.851318, 120.908988, -2358.679687, -2534.358154, 64.642021, 400000);
			SetPlayerPos(playerid, -856.914855, -2166.850830, 121.383178 - 10.0);
			
			SetPVarInt(playerid, "p_requests", 0);
		}
		SetPlayerVirtualWorld(playerid, playerid + MAX_PLAYERS);
		
		SetPVarInt(playerid, "p_reqtime", gettime() + 400);
	}

	printf("DEBUG:: playerid: %d downloading file...", playerid);

	return 1;
}*/


public OnPlayerRequestDownload(playerid, type, crc)
{
	if(!IsPlayerConnected(playerid))
		return 0;

	if (gettime() > GetPVarInt(playerid, "p_reqtime"))
	{
	    //TogglePlayerSpectating(playerid, true);

	    if (GetPVarInt(playerid, "p_reqtime") == 0) {

			PlayAudioStreamForPlayer(playerid, "https://sites.google.com/site/znationdayzsamp/sounds/Untitled.mp3?");

			clearPlayerChat(playerid);

			SetPlayerTime(playerid, 0, 0);

			SetPlayerWeather(playerid, 7);
		}

	    if (GetPVarInt(playerid, "p_requests") == 0)
	    {
			InterpolateCameraPos(playerid, 947.956970, 368.131591, 21.613374, 484.547882, 266.257995, 27.959131, 400000);
			InterpolateCameraLookAt(playerid, 943.106750, 366.930114, 21.791955, 479.570678, 265.780944, 27.963258, 400000);
			SetPlayerPos(playerid, 237.112899, -283.291381, 4.823380 - 10.0);

			SetPVarInt(playerid, "p_requests", 1);
		}
	    else if (GetPVarInt(playerid, "p_requests") == 1)
	    {
			InterpolateCameraPos(playerid, -856.914855, -2166.850830, 121.383178, -2354.097167, -2532.358886, 64.581443, 400000);
			InterpolateCameraLookAt(playerid, -861.892333, -2166.851318, 120.908988, -2358.679687, -2534.358154, 64.642021, 400000);
			SetPlayerPos(playerid, -856.914855, -2166.850830, 121.383178 - 10.0);

			SetPVarInt(playerid, "p_requests", 0);
		}
		SetPlayerVirtualWorld(playerid, playerid + MAX_PLAYERS);

		SetPVarInt(playerid, "p_reqtime", gettime() + 400);
	}

	new filename[64], filefound, url_final[356];

	if(type == DOWNLOAD_REQUEST_TEXTURE_FILE)
		filefound = FindTextureFileNameFromCRC(crc, filename, sizeof(filename));
	else if(type == DOWNLOAD_REQUEST_MODEL_FILE)
		filefound = FindModelFileNameFromCRC(crc, filename, sizeof(filename));

	if(filefound)
	{
		format(url_final, sizeof(url_final), "%s/%s", SERVER_DOWNLOAD, filename);
		RedirectDownload(playerid, url_final);

		printf("Redirect: %s - %s/%s", url_final, SERVER_DOWNLOAD, filename);
	}
	return 0;
}


new
	Float:ttx,
	Float:tty,
	Float:ttz,
	Float:trx,
	Float:try,
	Float:trz;


stock SHOP_NewAttachment(skinid, objectid, boneid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:sizex, Float:sizey, Float:sizez)
{
	new
	    DBResult:result_sql,
		sql_string[356];

	format(sql_string, sizeof (sql_string), "SELECT * FROM attachments WHERE skinid = '%d' and objectid = '%d'", skinid, objectid);
    result_sql = db_query(shop_database, sql_string);

	if (db_num_rows(result_sql))
	{
	    format(sql_string, sizeof (sql_string),
		"UPDATE attachments SET boneid='%d',x='%f', y='%f', z='%f', rx='%f', ry='%f', rz='%f', sx='%f', sy='%f', sz='%f' WHERE skinid = '%d' and objectid = '%d'",
		boneid,x,y,z,rx,ry,rz,sizex,sizey,sizez,skinid,objectid);
		db_query(shop_database, sql_string);
	} else {
	    format(sql_string, sizeof (sql_string),
		"INSERT INTO attachments (skinid,objectid,boneid,x,y,z,rx,ry,rz,sx,sy,sz) VALUES ('%d','%d','%d','%f','%f','%f','%f','%f','%f','%f','%f','%f')",
		skinid,	objectid,boneid,x,y,z,rx,ry,rz,sizex,sizey,sizez);
		db_query(shop_database, sql_string);
	}
	db_free_result(result_sql);
}

CMD:attachar(playerid, params[])
{
	if (IsPlayerAdmin(playerid))
	{
	    new slotid, objectid, boneid;
	    
	    if (sscanf(params, "ddd", objectid, slotid, boneid))
	        return SendClientMessage(playerid, -1, "/attachar <modelid> <slotid> <boneid>");
	        
	    SetPlayerAttachedObject(playerid, slotid, objectid, boneid, ttx, tty, ttz, trx, try, trz);
	    
	    EditAttachedObject(playerid, slotid);
	}
	return 1;
}

CMD:editattach(playerid, params[])
{
	if (IsPlayerAdmin(playerid))
	{
	    new slotid;

	    if (sscanf(params, "d", slotid))
	        return SendClientMessage(playerid, -1, "/editattach <slotid>");

	    EditAttachedObject(playerid, slotid);
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if (IsPlayerAdmin(playerid))
	{
		ttx = fOffsetX;
		tty = fOffsetY;
		ttz = fOffsetZ;
		trx = fRotX;
		try = fRotY;
		trz = fRotZ;
		
		SHOP_NewAttachment(GetPlayerCustomSkin(playerid), modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
	}
    return 1;
}

stock SHOP_SetPlayerAttachedObject(playerid, slotid, modelid)
{
	new
	    DBResult:result_sql,
		sql_string[85];

	format(sql_string, sizeof (sql_string), "SELECT * FROM attachments WHERE skinid = '%d' and objectid = '%d'", PlayerData[playerid][dSkin] == -1 ? (PlayerData[playerid][dTempSkin]) : (PlayerData[playerid][dSkin]), modelid);
    result_sql = db_query(shop_database, sql_string);

    if (db_num_rows(result_sql))
    {
        SetPlayerAttachedObject(playerid,
			slotid,
			modelid,
            db_get_field_assoc_int(result_sql, "boneid"),
            db_get_field_assoc_float(result_sql, "x"),
            db_get_field_assoc_float(result_sql, "y"),
            db_get_field_assoc_float(result_sql, "z"),
            db_get_field_assoc_float(result_sql, "rx"),
            db_get_field_assoc_float(result_sql, "ry"),
            db_get_field_assoc_float(result_sql, "rz"),
            db_get_field_assoc_float(result_sql, "sx"),
            db_get_field_assoc_float(result_sql, "sy"),
            db_get_field_assoc_float(result_sql, "sz"));
    } else {

		SetPlayerAttachedObject(playerid, slotid, modelid, 0);
	}
	db_free_result(result_sql);
}


stock SHOP_OpenCrate(playerid, type)
{
	new rand_money;
	new rand_time;
	new rand_luck;
	new rand_xp;
	new rand_string[128];
	new DBResult:rand_result;
	
	switch (type)
	{
		case CRATE_TYPE_DAILY:
		{
		    rand_money = 1500;
		    
		    rand_time = c_hours(1 + random(5));
		    
		    rand_luck = random(10);
		    
		    rand_xp = 500;
		    
		    // Querys
		    if (rand_luck > 8)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '0' OR rarity = '1') and id > 10 order by random() LIMIT 1");
		    } else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '0' and id > 10 order by random() LIMIT 1");
		    }
		}
		case CRATE_TYPE_SILVER:
		{
		    rand_money = 2500;

		    rand_time = c_hours(24 + random(12));

		    rand_luck = random(20);
		    
		    rand_xp = 600;

		    // Querys
		    if (rand_luck > 17)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' OR rarity = '2') and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 12)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '1' and id > 10 order by random() LIMIT 1");
		    } else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '0' and id > 10 order by random() LIMIT 1");
		    }
		}
		case CRATE_TYPE_GOLD:
		{
		    rand_money = 5000;

		    rand_time = c_days(3 + random(3));

		    rand_luck = random(30);
		    
		    rand_xp = 800;

		    // Querys
		    if (rand_luck > 28)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '3' and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 23)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' or rarity = '2' or rarity = '3') and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 15)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' or rarity = '2') and id > 10 order by random() LIMIT 1");
		    }else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '0' or rarity = '1') and id > 10 order by random() LIMIT 1");
		    }
		    
		    // Permanent skin
		    rand_luck = random(20);
		    
		    if (rand_luck == 17 || rand_luck == 10)
		    {
		        rand_time = -1;
		    }
		}
		case CRATE_TYPE_DIAMOND:
		{
		    rand_money = 8000;
		    
		    rand_time = c_days(5 + random(5));

		    rand_luck = random(30);
		    
		    rand_xp = 1000;

		    // Querys
		    if (rand_luck > 20)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '3' and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 17)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' or rarity = '2' or rarity = '3') and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 12)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE *rarity = '1' or rarity = '2') and id > 10 order by random() LIMIT 1");
		    }else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '1' and id > 10 order by random() LIMIT 1");
		    }
		    
		    // Permanent skin
		    rand_luck = random(15);

		    if (rand_luck == 10 || rand_luck == 5)
		    {
		        rand_time = -1;
		    }
		}
		case CRATE_TYPE_LEGENDARY:
		{
		    rand_money = 11000;
		    
		    rand_time = c_days(10 + random(5));

		    rand_luck = random(40);
		    
		    rand_xp = 1500;

		    // Querys
		    if (rand_luck > 29)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '3' and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 20)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' or rarity = '2' or rarity = '3') and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 10)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '1' or rarity = '2') and id > 10 order by random() LIMIT 1");
		    }else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '1' and id > 10 order by random() LIMIT 1");
		    }
		    
		    // Permanent skin
		    rand_luck = random(10);

		    if (rand_luck == 7 || rand_luck == 3)
		    {
		        rand_time = -1;
		    }
		}
		case CRATE_TYPE_ULTIMATE:
		{
		    rand_money = 16000;

		    rand_time = c_days(15 + random(15));

		    rand_luck = random(40);
		    
		    rand_xp = 2000;

		    // Querys
		    if (rand_luck > 25)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '3' and id > 10 order by random() LIMIT 1");
		    }
		    else if (rand_luck > 15)
		    {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE (rarity = '2' or rarity = '3') and id > 10 order by random() LIMIT 1");
		    }
			else {
		        format(rand_string, sizeof (rand_string), "SELECT * FROM skins WHERE rarity = '2' and id > 10 order by random() LIMIT 1");
		    }
		    
		    // Permanent skin
		    rand_luck = random(7);

		    if (rand_luck == 6 || rand_luck == 3)
		    {
		        rand_time = -1;
		    }
		}
	}
	
	rand_result = db_query(shop_database, rand_string);

	if (db_num_rows(rand_result))
	{
	    PlayerData[playerid][dMoney] += rand_money;
	    
	    givePlayerPoints(playerid, rand_xp);
	
	    SHOP_GiveItem(playerid,
						.modelid = db_get_field_assoc_int(rand_result, "id"),
						.cost = db_get_field_assoc_int(rand_result, "price"),
						.rarity = db_get_field_assoc_int(rand_result, "rarity"),
						.gender = db_get_field_assoc_int(rand_result, "gender"),
						.time = gettime() + rand_time,
						.legacy = 0);
	}

	db_free_result(rand_result);
	
	Log::("opencrate", "player %s opened crate type: %d", getNome(playerid), type);
}

stock SHOP_ShowBoxDiscription(playerid)
{
	for(new text; text < 2; text++)
	{
	    TextDrawShowForPlayer(playerid, serverBoxDiscription[text]);
	    PlayerTextDrawShow(playerid, boxDiscription[text]);
	}
}

stock SHOP_HideBoxDiscription(playerid)
{
	for(new text; text < 2; text++)
	{
	    TextDrawHideForPlayer(playerid, serverBoxDiscription[text]);
	    PlayerTextDrawHide(playerid, boxDiscription[text]);
	}
}

public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	if (!PlayerData[playerid][dDownloading])
		return 0;

    PlayerData[playerid][dDownloading] = false;
	if (PlayerData[playerid][dLogged])
	    return 1;

	showPlayerLoading(playerid);
	printf("%s[ID: %d] finish downloading", getNome(playerid), playerid);
	return 1;
}

public OnTextDialogResponse(playerid, dialogid, response)
{
	if (dialogid == 558)
	{
	    if(response)
	    {
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
	  		    if (PlayerData[playerid][dCoins] < ps_array[playerid][index][ps_cost])
	  		        return ShowPlayerDialogTextdraw(playerid, 0, "~r~Voce nao tem Z Points suficiente.", .buttons = " OK");
	  		
	  		    SHOP_GiveItem(playerid,
		  			ps_array[playerid][index][ps_modelid],
			  		ps_array[playerid][index][ps_cost],
			  		ps_array[playerid][index][ps_rarity],
			  		ps_array[playerid][index][ps_gender]);

                //PlayerData[playerid][dCoins] -= ps_array[playerid][index][ps_cost];
                GivePlayerCoins(playerid, -ps_array[playerid][index][ps_cost]);
                
                Log::("buyitem", "player %s\tmodelid:%d\tcost:%d\tTemp:0", getNome(playerid), ps_array[playerid][index][ps_modelid], ps_array[playerid][index][ps_cost]);
			}
	    }
	}
	else if (dialogid == 559)
	{
	    if(response)
	    {
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
	  		    new days = GetPVarInt(playerid, "p_daysitem");
	  		    new cost = (days * (ps_array[playerid][index][ps_cost]/DIVIDER_RENT));
	  		    if (PlayerData[playerid][dCoins] < cost)
	  		        return ShowPlayerDialogTextdraw(playerid, 0, "~r~Voce nao tem Z Points suficiente.", .buttons = " OK");

	  		    SHOP_GiveItem(playerid,
					ps_array[playerid][index][ps_modelid],
					ps_array[playerid][index][ps_cost],
					ps_array[playerid][index][ps_rarity],
					ps_array[playerid][index][ps_gender],
					.time = gettime() + (days * 86400));

				//PlayerData[playerid][dCoins] -= cost;
				GivePlayerCoins(playerid, -ps_array[playerid][index][ps_cost]);
				
				Log::("buyitem", "player %s\tmodelid:%d\tcost:%d\tTemp:%d days", getNome(playerid), ps_array[playerid][index][ps_modelid], ps_array[playerid][index][ps_cost], days * 86400);
			}
	    }
	}
	else if (dialogid == 560)
	{
	    if(response)
	    {
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
	  		    PlayerData[playerid][dMoney] += ps_array[playerid][index][ps_cost];
	  		    
	  		    SHOP_DeleteSkin(playerid, ps_array[playerid][index][ps_ai]);
	  		    
	  		    SHOP_SetPlayerOrder(playerid, GetPVarInt(playerid, "SHOP_order"));
	  		    
	  		    // Fix skin
	  		    SHOP_FixSkin(playerid);
	  		    
	  		    Log::("sellitem", "player %s\tmodelid:%d\tcost:%d", getNome(playerid), ps_array[playerid][index][ps_modelid], ps_array[playerid][index][ps_cost]);
			}
	    }
	}
	else if (dialogid == 565)
	{
	    if(response)
	    {
		    new index = GetPVarInt(playerid, "p_selecteditem");
			if (index > -1)
	  		{
	  		    SHOP_DeleteSkin(playerid, ps_array[playerid][index][ps_ai]);

	  		    SHOP_SetPlayerOrder(playerid, GetPVarInt(playerid, "SHOP_order"));

	  		    // Fix skin
	  		    SHOP_FixSkin(playerid);
	  		    
	  		    Log::("discarditem", "player %s\tmodelid:%d", getNome(playerid), ps_array[playerid][index][ps_modelid]);
			}
	    }
	}
 	#if defined OnTextDialogResponseS
  		return OnTextDialogResponseS(playerid, dialogid, response);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnTextDialogResponse
	#undef OnTextDialogResponse
#else
	#define _ALS_OnTextDialogResponse
#endif
#define OnTextDialogResponse OnTextDialogResponseS
#if defined OnTextDialogResponseS
	forward OnTextDialogResponseS(playerid, dialogid, response);
#endif

stock SHOP_CreatePlayerTextDraws(playerid)
{
	// PLAYER
	playerShopText[0] = CreatePlayerTextDraw(playerid, 368.000000, 135.000000, "mdl-1002:normal");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[0], 255);
	PlayerTextDrawFont(playerid, playerShopText[0], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[0], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[0], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[0], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[0], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[0], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[0], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[0], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[0], 1);

	playerShopText[1] = CreatePlayerTextDraw(playerid, 445.000000, 135.000000, "mdl-1002:normal");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[1], 255);
	PlayerTextDrawFont(playerid, playerShopText[1], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[1], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[1], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[1], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[1], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[1], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[1], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[1], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[1], 1);

	playerShopText[2] = CreatePlayerTextDraw(playerid, 522.000000, 135.000000, "mdl-1002:normal");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[2], 255);
	PlayerTextDrawFont(playerid, playerShopText[2], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[2], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[2], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[2], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[2], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[2], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[2], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[2], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[2], 1);

	playerShopText[3] = CreatePlayerTextDraw(playerid, 368.000000, 227.000000, "mdl-1002:rare");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[3], 255);
	PlayerTextDrawFont(playerid, playerShopText[3], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[3], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[3], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[3], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[3], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[3], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[3], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[3], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[3], 1);

	playerShopText[4] = CreatePlayerTextDraw(playerid, 445.000000, 227.000000, "mdl-1002:legendary");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[4], 255);
	PlayerTextDrawFont(playerid, playerShopText[4], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[4], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[4], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[4], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[4], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[4], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[4], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[4], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[4], 1);

	playerShopText[5] = CreatePlayerTextDraw(playerid, 522.000000, 227.000000, "mdl-1002:legendary");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[5], 255);
	PlayerTextDrawFont(playerid, playerShopText[5], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[5], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[5], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[5], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[5], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[5], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[5], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[5], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[5], 1);

	playerShopText[6] = CreatePlayerTextDraw(playerid, 368.000000, 319.000000, "mdl-1002:skinn");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[6], 255);
	PlayerTextDrawFont(playerid, playerShopText[6], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[6], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[6], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[6], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[6], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[6], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[6], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[6], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[6], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[6], 1);

	playerShopText[7] = CreatePlayerTextDraw(playerid, 445.000000, 319.000000, "mdl-1002:skinn");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[7], 255);
	PlayerTextDrawFont(playerid, playerShopText[7], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[7], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[7], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[7], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[7], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[7], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[7], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[7], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[7], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[7], 1);

	playerShopText[8] = CreatePlayerTextDraw(playerid, 522.000000, 319.000000, "mdl-1002:skinn");
	PlayerTextDrawBackgroundColor(playerid, playerShopText[8], 255);
	PlayerTextDrawFont(playerid, playerShopText[8], 4);
	PlayerTextDrawLetterSize(playerid, playerShopText[8], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[8], -1);
	PlayerTextDrawSetOutline(playerid, playerShopText[8], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[8], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[8], 1);
	PlayerTextDrawUseBox(playerid, playerShopText[8], 1);
	PlayerTextDrawBoxColor(playerid, playerShopText[8], 255);
	PlayerTextDrawTextSize(playerid, playerShopText[8], 76.000000, 91.000000);
	PlayerTextDrawSetSelectable(playerid, playerShopText[8], 1);

	playerShopText[9] = CreatePlayerTextDraw(playerid, 392.000000, 412.000000, "1-1");
	PlayerTextDrawAlignment(playerid, playerShopText[9], 2);
	PlayerTextDrawBackgroundColor(playerid, playerShopText[9], 0);
	PlayerTextDrawFont(playerid, playerShopText[9], 1);
	PlayerTextDrawLetterSize(playerid, playerShopText[9], 0.200000, 1.000000);
	PlayerTextDrawColor(playerid, playerShopText[9], -156);
	PlayerTextDrawSetOutline(playerid, playerShopText[9], 0);
	PlayerTextDrawSetProportional(playerid, playerShopText[9], 1);
	PlayerTextDrawSetShadow(playerid, playerShopText[9], 1);
	PlayerTextDrawSetSelectable(playerid, playerShopText[9], 0);
	
	playerShopText[10] = CreatePlayerTextDraw(playerid,364.000000, 424.000000, "mdl-2021:button1");
	PlayerTextDrawBackgroundColor(playerid,playerShopText[10], 255);
	PlayerTextDrawFont(playerid,playerShopText[10], 4);
	PlayerTextDrawLetterSize(playerid,playerShopText[10], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerShopText[10], -106);
	PlayerTextDrawSetOutline(playerid,playerShopText[10], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[10], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[10], 1);
	PlayerTextDrawUseBox(playerid,playerShopText[10], 1);
	PlayerTextDrawBoxColor(playerid,playerShopText[10], 255);
	PlayerTextDrawTextSize(playerid,playerShopText[10], 74.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerShopText[10], 1);

	playerShopText[11] = CreatePlayerTextDraw(playerid,433.000000, 431.000000, "~r~ZP ~w~~h~0.000");
	PlayerTextDrawAlignment(playerid,playerShopText[11], 3);
	PlayerTextDrawBackgroundColor(playerid,playerShopText[11], 0);
	PlayerTextDrawFont(playerid,playerShopText[11], 1);
	PlayerTextDrawLetterSize(playerid,playerShopText[11], 0.189998, 0.999998);
	PlayerTextDrawColor(playerid,playerShopText[11], -1);
	PlayerTextDrawSetOutline(playerid,playerShopText[11], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[11], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[11], 1);
	PlayerTextDrawSetSelectable(playerid,playerShopText[11], 0);

	playerShopText[12] = CreatePlayerTextDraw(playerid,438.000000, 424.000000, "mdl-2021:button2");
	PlayerTextDrawBackgroundColor(playerid,playerShopText[12], 255);
	PlayerTextDrawFont(playerid,playerShopText[12], 4);
	PlayerTextDrawLetterSize(playerid,playerShopText[12], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerShopText[12], -106);
	PlayerTextDrawSetOutline(playerid,playerShopText[12], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[12], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[12], 1);
	PlayerTextDrawUseBox(playerid,playerShopText[12], 1);
	PlayerTextDrawBoxColor(playerid,playerShopText[12], 255);
	PlayerTextDrawTextSize(playerid,playerShopText[12], 74.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerShopText[12], 1);

	playerShopText[13] = CreatePlayerTextDraw(playerid,507.000000, 431.000000, "~g~$ ~w~~h~0.000");
	PlayerTextDrawAlignment(playerid,playerShopText[13], 3);
	PlayerTextDrawBackgroundColor(playerid,playerShopText[13], 0);
	PlayerTextDrawFont(playerid,playerShopText[13], 1);
	PlayerTextDrawLetterSize(playerid,playerShopText[13], 0.189998, 0.999998);
	PlayerTextDrawColor(playerid,playerShopText[13], -1);
	PlayerTextDrawSetOutline(playerid,playerShopText[13], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[13], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[13], 1);
	PlayerTextDrawSetSelectable(playerid,playerShopText[13], 0);

	playerShopText[14] = CreatePlayerTextDraw(playerid,538.000000, 431.000000, "15 DAYS");
	PlayerTextDrawAlignment(playerid,playerShopText[14], 2);
	PlayerTextDrawBackgroundColor(playerid,playerShopText[14], 0);
	PlayerTextDrawFont(playerid,playerShopText[14], 1);
	PlayerTextDrawLetterSize(playerid,playerShopText[14], 0.179998, 1.000000);
	PlayerTextDrawColor(playerid,playerShopText[14], -156);
	PlayerTextDrawSetOutline(playerid,playerShopText[14], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[14], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[14], 1);
	PlayerTextDrawSetSelectable(playerid,playerShopText[14], 0);

	playerShopText[15] = CreatePlayerTextDraw(playerid,611.000000, 431.000000, "00:00:00");
	PlayerTextDrawAlignment(playerid,playerShopText[15], 3);
	PlayerTextDrawBackgroundColor(playerid,playerShopText[15], 0);
	PlayerTextDrawFont(playerid,playerShopText[15], 1);
	PlayerTextDrawLetterSize(playerid,playerShopText[15], 0.169998, 1.000000);
	PlayerTextDrawColor(playerid,playerShopText[15], -1);
	PlayerTextDrawSetOutline(playerid,playerShopText[15], 0);
	PlayerTextDrawSetProportional(playerid,playerShopText[15], 1);
	PlayerTextDrawSetShadow(playerid,playerShopText[15], 1);
	PlayerTextDrawSetSelectable(playerid,playerShopText[15], 0);
}

stock SHOP_CreateTextDraws()
{
	// SERVER
	serverShopTexts[0] = TextDrawCreate(366.000000, 108.000000, "mdl-1002:background");
	TextDrawBackgroundColor(serverShopTexts[0], 255);
	TextDrawFont(serverShopTexts[0], 4);
	TextDrawLetterSize(serverShopTexts[0], 0.500000, 0.299997);
	TextDrawColor(serverShopTexts[0], 1684301025);
	TextDrawSetOutline(serverShopTexts[0], 0);
	TextDrawSetProportional(serverShopTexts[0], 1);
	TextDrawSetShadow(serverShopTexts[0], 1);
	TextDrawUseBox(serverShopTexts[0], 1);
	TextDrawBoxColor(serverShopTexts[0], 255);
	TextDrawTextSize(serverShopTexts[0], 258.000000, 316.000000);
	TextDrawSetSelectable(serverShopTexts[0], 0);

	serverShopTexts[1] = TextDrawCreate(603.000000, 110.000000, "mdl-1002:fechar");
	TextDrawBackgroundColor(serverShopTexts[1], 255);
	TextDrawFont(serverShopTexts[1], 4);
	TextDrawLetterSize(serverShopTexts[1], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[1], -76);
	TextDrawSetOutline(serverShopTexts[1], 0);
	TextDrawSetProportional(serverShopTexts[1], 1);
	TextDrawSetShadow(serverShopTexts[1], 1);
	TextDrawUseBox(serverShopTexts[1], 1);
	TextDrawBoxColor(serverShopTexts[1], 255);
	TextDrawTextSize(serverShopTexts[1], 14.000000, 17.000000);
	TextDrawSetSelectable(serverShopTexts[1], 1);

	serverShopTexts[2] = TextDrawCreate(600.000000, 178.000000, "mdl-1002:shop");
	TextDrawBackgroundColor(serverShopTexts[2], 255);
	TextDrawFont(serverShopTexts[2], 4);
	TextDrawLetterSize(serverShopTexts[2], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[2], -156);
	TextDrawSetOutline(serverShopTexts[2], 0);
	TextDrawSetProportional(serverShopTexts[2], 1);
	TextDrawSetShadow(serverShopTexts[2], 1);
	TextDrawUseBox(serverShopTexts[2], 1);
	TextDrawBoxColor(serverShopTexts[2], 255);
	TextDrawTextSize(serverShopTexts[2], 20.000000, 20.000000);
	TextDrawSetSelectable(serverShopTexts[2], 1);

	serverShopTexts[3] = TextDrawCreate(601.000000, 216.000000, "mdl-1002:inventory");
	TextDrawBackgroundColor(serverShopTexts[3], 255);
	TextDrawFont(serverShopTexts[3], 4);
	TextDrawLetterSize(serverShopTexts[3], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[3], -156);
	TextDrawSetOutline(serverShopTexts[3], 0);
	TextDrawSetProportional(serverShopTexts[3], 1);
	TextDrawSetShadow(serverShopTexts[3], 1);
	TextDrawUseBox(serverShopTexts[3], 1);
	TextDrawBoxColor(serverShopTexts[3], 255);
	TextDrawTextSize(serverShopTexts[3], 20.000000, 20.000000);
	TextDrawSetSelectable(serverShopTexts[3], 1);

	serverShopTexts[4] = TextDrawCreate(601.000000, 256.000000, "mdl-1002:order");
	TextDrawBackgroundColor(serverShopTexts[4], 255);
	TextDrawFont(serverShopTexts[4], 4);
	TextDrawLetterSize(serverShopTexts[4], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[4], -156);
	TextDrawSetOutline(serverShopTexts[4], 0);
	TextDrawSetProportional(serverShopTexts[4], 1);
	TextDrawSetShadow(serverShopTexts[4], 1);
	TextDrawUseBox(serverShopTexts[4], 1);
	TextDrawBoxColor(serverShopTexts[4], 255);
	TextDrawTextSize(serverShopTexts[4], 20.000000, 20.000000);
	TextDrawSetSelectable(serverShopTexts[4], 1);

	serverShopTexts[5] = TextDrawCreate(599.000000, 291.000000, "mdl-1002:male");
	TextDrawBackgroundColor(serverShopTexts[5], 255);
	TextDrawFont(serverShopTexts[5], 4);
	TextDrawLetterSize(serverShopTexts[5], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[5], -156);
	TextDrawSetOutline(serverShopTexts[5], 0);
	TextDrawSetProportional(serverShopTexts[5], 1);
	TextDrawSetShadow(serverShopTexts[5], 1);
	TextDrawUseBox(serverShopTexts[5], 1);
	TextDrawBoxColor(serverShopTexts[5], 255);
	TextDrawTextSize(serverShopTexts[5], 23.000000, 24.000000);
	TextDrawSetSelectable(serverShopTexts[5], 1);

	serverShopTexts[6] = TextDrawCreate(599.000000, 328.000000, "mdl-1002:female");
	TextDrawBackgroundColor(serverShopTexts[6], 255);
	TextDrawFont(serverShopTexts[6], 4);
	TextDrawLetterSize(serverShopTexts[6], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[6], -156);
	TextDrawSetOutline(serverShopTexts[6], 0);
	TextDrawSetProportional(serverShopTexts[6], 1);
	TextDrawSetShadow(serverShopTexts[6], 1);
	TextDrawUseBox(serverShopTexts[6], 1);
	TextDrawBoxColor(serverShopTexts[6], 255);
	TextDrawTextSize(serverShopTexts[6], 23.000000, 24.000000);
	TextDrawSetSelectable(serverShopTexts[6], 1);

	serverShopTexts[7] = TextDrawCreate(370.000000, 412.000000, "ld_beat:left");
	TextDrawBackgroundColor(serverShopTexts[7], 255);
	TextDrawFont(serverShopTexts[7], 4);
	TextDrawLetterSize(serverShopTexts[7], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[7], -156);
	TextDrawSetOutline(serverShopTexts[7], 0);
	TextDrawSetProportional(serverShopTexts[7], 1);
	TextDrawSetShadow(serverShopTexts[7], 1);
	TextDrawUseBox(serverShopTexts[7], 1);
	TextDrawBoxColor(serverShopTexts[7], 255);
	TextDrawTextSize(serverShopTexts[7], 9.000000, 10.000000);
	TextDrawSetSelectable(serverShopTexts[7], 1);

	serverShopTexts[8] = TextDrawCreate(408.000000, 412.000000, "ld_beat:right");
	TextDrawBackgroundColor(serverShopTexts[8], 255);
	TextDrawFont(serverShopTexts[8], 4);
	TextDrawLetterSize(serverShopTexts[8], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[8], -156);
	TextDrawSetOutline(serverShopTexts[8], 0);
	TextDrawSetProportional(serverShopTexts[8], 1);
	TextDrawSetShadow(serverShopTexts[8], 1);
	TextDrawUseBox(serverShopTexts[8], 1);
	TextDrawBoxColor(serverShopTexts[8], 255);
	TextDrawTextSize(serverShopTexts[8], 9.000000, 10.000000);
	TextDrawSetSelectable(serverShopTexts[8], 1);
	
	serverShopTexts[9] = TextDrawCreate(514.000000, 431.000000, "ld_beat:left");
	TextDrawBackgroundColor(serverShopTexts[9], 255);
	TextDrawFont(serverShopTexts[9], 4);
	TextDrawLetterSize(serverShopTexts[9], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[9], -156);
	TextDrawSetOutline(serverShopTexts[9], 0);
	TextDrawSetProportional(serverShopTexts[9], 1);
	TextDrawSetShadow(serverShopTexts[9], 1);
	TextDrawUseBox(serverShopTexts[9], 1);
	TextDrawBoxColor(serverShopTexts[9], 255);
	TextDrawTextSize(serverShopTexts[9], 9.000000, 10.000000);
	TextDrawSetSelectable(serverShopTexts[9], 1);

	serverShopTexts[10] = TextDrawCreate(554.000000, 431.000000, "ld_beat:right");
	TextDrawBackgroundColor(serverShopTexts[10], 255);
	TextDrawFont(serverShopTexts[10], 4);
	TextDrawLetterSize(serverShopTexts[10], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[10], -156);
	TextDrawSetOutline(serverShopTexts[10], 0);
	TextDrawSetProportional(serverShopTexts[10], 1);
	TextDrawSetShadow(serverShopTexts[10], 1);
	TextDrawUseBox(serverShopTexts[10], 1);
	TextDrawBoxColor(serverShopTexts[10], 255);
	TextDrawTextSize(serverShopTexts[10], 9.000000, 10.000000);
	TextDrawSetSelectable(serverShopTexts[10], 1);

	serverShopTexts[11] = TextDrawCreate(613.000000, 429.000000, "mdl-1002:clock");
	TextDrawBackgroundColor(serverShopTexts[11], 255);
	TextDrawFont(serverShopTexts[11], 4);
	TextDrawLetterSize(serverShopTexts[11], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[11], -13487436);
	TextDrawSetOutline(serverShopTexts[11], 0);
	TextDrawSetProportional(serverShopTexts[11], 1);
	TextDrawSetShadow(serverShopTexts[11], 1);
	TextDrawUseBox(serverShopTexts[11], 1);
	TextDrawBoxColor(serverShopTexts[11], 255);
	TextDrawTextSize(serverShopTexts[11], 10.000000, 12.000000);
	TextDrawSetSelectable(serverShopTexts[11], 1);
	
	serverShopTexts[12] = TextDrawCreate(603.000000, 399.000000, "mdl-1004:drop");
	TextDrawBackgroundColor(serverShopTexts[12], 255);
	TextDrawFont(serverShopTexts[12], 4);
	TextDrawLetterSize(serverShopTexts[12], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[12], -106);
	TextDrawSetOutline(serverShopTexts[12], 0);
	TextDrawSetProportional(serverShopTexts[12], 1);
	TextDrawSetShadow(serverShopTexts[12], 1);
	TextDrawUseBox(serverShopTexts[12], 1);
	TextDrawBoxColor(serverShopTexts[12], 255);
	TextDrawTextSize(serverShopTexts[12], 17.000000, 19.000000);
	TextDrawSetSelectable(serverShopTexts[12], 1);
	
	serverShopTexts[13] = TextDrawCreate(339.000000, 395.000000, "mdl-1028:prize");
	TextDrawBackgroundColor(serverShopTexts[13], 255);
	TextDrawFont(serverShopTexts[13], 4);
	TextDrawLetterSize(serverShopTexts[13], 0.500000, 1.000000);
	TextDrawColor(serverShopTexts[13], -156);
	TextDrawSetOutline(serverShopTexts[13], 0);
	TextDrawSetProportional(serverShopTexts[13], 1);
	TextDrawSetShadow(serverShopTexts[13], 1);
	TextDrawUseBox(serverShopTexts[13], 1);
	TextDrawBoxColor(serverShopTexts[13], 255);
	TextDrawTextSize(serverShopTexts[13], 25.000000, 33.000000);
	TextDrawSetSelectable(serverShopTexts[13], 1);
}
