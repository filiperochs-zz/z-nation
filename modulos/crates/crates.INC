
#define MAX_PAGES 500

// types
enum {
    BOX_TYPE_NORMAL,
}

enum {
	MENU_ACCESSORY_SHOP,
	MENU_ACCESSORY_PLAYER,
}

enum {
	E_TYPE_COMUM,
	E_TYPE_NO_COMUM,
	E_TYPE_RARE,
	E_TYPE_EPIC,
	E_TYPE_IMPOSSIBLE,
}

enum E_CRATES_SYSTEM
{
		E_CRATE_NAME[75],
		E_CRATE_MODEL,
		E_CRATE_RARITY,
		E_CRATE_BONE,
Float:	E_CRATE_RX,
Float:	E_CRATE_RY,
Float:  E_CRATE_RZ,
Float:  E_CRATE_ZOOM,
		E_CRATE_COST,
}
// player variables
new playerRowIndex[MAX_PLAYERS][9];
new playerPageFirstIndex[MAX_PLAYERS][MAX_PAGES];
new playerMenuAccessory[MAX_PLAYERS];

stock const s_CratesSystemInfo[][E_CRATES_SYSTEM] = {
//  name                        model     rarity    		   bone  rx       ry       rz       zoom     cost
	{"Caixa de acessorios", 	964, 	  E_TYPE_IMPOSSIBLE,   0,  	 -30.0,   0.0,     50.0,    1.2,     1250},
	// Acessorios
	{"Chapeu de bruxa", 		19528, 	  E_TYPE_EPIC,         2,  	 0.0,     270.0,   20.0,    0.9,     9600},
	{"Mascara de diabo", 		11704, 	  E_TYPE_EPIC,         2,  	 0.0,     0.0,     0.0,     0.9,     4100},
	{"Chapeu com cabelo", 		19136, 	  E_TYPE_EPIC,         2,  	 0.0,    -90.0,    0.0,     0.9,     3850},
	{"Abobora", 				19320, 	  E_TYPE_EPIC,         2,  	 0.0,    0.0,      0.0,     0.6,     6750},
	{"Oculos", 					19140, 	  E_TYPE_RARE,         2,  	 -10.0,   0.0,     50.0,    0.9,     5350},
	{"Oculos", 					19139, 	  E_TYPE_RARE,         2,  	 -10.0,   0.0,     50.0,    0.9,     5350},
	{"Oculos", 					19138, 	  E_TYPE_RARE,         2,  	 -10.0,   0.0,     50.0,    0.9,     5350},
	// Previa skins
	{"Skin", 					285, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     22500},
	{"Skin", 					286, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     21000},
	{"Skin", 					287, 	  E_TYPE_EPIC,   	   0,  	 0.0,     0.0,     20.0,    1.0,     23200},
	{"Skin", 					306, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     21200},
	{"Skin", 					307, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     21200},
	{"Skin", 					308, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     21200},
	{"Skin", 					309, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     21200},
	// Outros
	{"Touca natalina", 			19065, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     5350},
	{"Fone de ouvido", 			19424, 	  E_TYPE_RARE,         2,  	 90.0,    0.0,     0.0,     0.9,     4125},
	{"Fone de ouvido", 			19423, 	  E_TYPE_RARE,         2,  	 90.0,    0.0,     0.0,     0.9,     4125},
	{"Fone de ouvido", 			19422, 	  E_TYPE_RARE,         2,  	 90.0,    0.0,     0.0,     0.9,     4125},
	{"Fone de ouvido", 			19421, 	  E_TYPE_RARE,         2,  	 90.0,    0.0,     0.0,     0.9,     4125},
	{"Cartola preta", 			19352, 	  E_TYPE_NO_COMUM,     2,  	 0.0,     0.0,     20.0,    0.9,     4100},
	{"Cartola branca", 			19487, 	  E_TYPE_NO_COMUM,     2,  	 0.0,     0.0,     20.0,    0.9,     4000},
	{"Bone de policial", 		19161, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     4125},
	{"Bone de policial", 		19162, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     4125},
	{"Chapeu burger", 			19094, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2350},
	{"Bone de policial", 		18636, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     3900},
	{"Panela", 					11718, 	  E_TYPE_COMUM,        2,  	 -20.0,   0.0,     45.0,    0.9,     5000},
	{"Chapeu de boxeador", 		18952, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3000},
	// mascaras
	{"Mascara", 				19038, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     4500},
	{"Mascara", 				19036, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     4500},
	{"Mascara", 				19037, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     4500},
	{"Mascara do zorro", 		18974, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     3100},
	{"Mascara sexy", 			19557, 	  E_TYPE_COMUM,        2,  	 180.0,   90.0,    50.0,    0.9,     4000},
	// bandanas
	{"Bandana", 				18919, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18912, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18913, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18914, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18915, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18916, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18917, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18918, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	{"Bandana", 				18920, 	  E_TYPE_NO_COMUM,     2,  	 90.0,   -180.0,   0.0,     0.9,     4955},
	// oculos
	{"Oculos", 					19025, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19026, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19024, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19023, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19010, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19031, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19028, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19030, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19020, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19013, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19014, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19015, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19016, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19017, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19019, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19029, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19022, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	{"Oculos", 					19033, 	  E_TYPE_COMUM,        2,  	 -10.0,   0.0,     50.0,    0.9,     2950},
	// cabelos
	{"Cabelo", 					19274, 	  E_TYPE_NO_COMUM,     2,  	 -50.0,  0.0,      0.0,     0.9,     4850},
	{"Chapeu preto", 			18947, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3200},
	{"Chapeu laranja", 			18969, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     2350},
	{"Chapeu laranja", 			18944, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2350},
	{"Chapeu cinza", 			18945, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2350},
	{"Chapeu escuro", 			18962, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2000},
	{"Touca preta", 			19069, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     2100},
	{"Chapeu marrom", 			19098, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2100},
	{"Chapeu xadrez", 			18968, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     3000},
	{"Bone preto e branco", 	18933, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2500},
	{"Bone cinza", 				18929, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1900},
	{"Chapeu", 					18973, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     1500},
	{"Chapeu", 					18972, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     1500},
	{"Chapeu", 					18971, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     1500},
	{"Chapeu", 					18970, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     1500},
	{"Bone azul", 				18927, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2000},
	{"Bone laranja", 			18932, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1900},
	{"Chapeu vermelho", 		18950, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3000},
	{"Bone colorido", 			18928, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2550},
	{"Chapeu azul", 			18948, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1900},
	{"Chapeu", 					18946, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1500},
	{"Chapeu de taxista", 		19521, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3000},
	{"Chapeu de palha", 		19553, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     4500},
	{"Chapeu de bombeiro", 		19331, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3500},
	{"Chapeu de bombeiro", 		19330, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     3500},
	{"Bone de pizzaiolo", 		19558, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2900},
	{"Chapeu", 					19067, 	  E_TYPE_COMUM,        2,  	 0.0,     0.0,     20.0,    0.9,     1900},
	{"Chapeu de trabalhador", 	18638, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2450},
	{"Chapeu marrom", 			19095, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     2000},
	{"Chapeu vermelho", 		19097, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1500},
	{"Touca", 					18954, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1700},
	{"Touca", 					18953, 	  E_TYPE_COMUM,        2,  	 0.0,     270.0,   20.0,    0.9,     1700},
	// Skins
	{"Skin", 					22, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     7800},
	{"Skin", 					23, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Skin", 					33, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9500},
	{"Skin", 					40, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     8000},
	{"Skin", 					90, 	  E_TYPE_EPIC,         0,  	 0.0,     0.0,     20.0,    1.0,     8150},
	{"Skin", 					92, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     8150},
	{"Skin", 					43, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     7900},
	{"Skin", 					46, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     15500},
	{"Skin", 					53, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Skin", 					150, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     7800},
	{"Skin", 					195, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     14500},
	{"Skin", 					55, 	  E_TYPE_EPIC,         0,  	 0.0,     0.0,     20.0,    1.0,     13000},
	{"Skin", 					230, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     19000},
	{"Skin", 					58, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     10000},
	{"Skin", 					108, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     15000},
	{"Skin", 					62, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Skin", 					63, 	  E_TYPE_EPIC,         0,  	 0.0,     0.0,     20.0,    1.0,     11000},
	{"Skin", 					64, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     11000},
	{"Skin", 					70, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     14100},
	{"Skin", 					80, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     8400},
	{"Skin", 					81, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     8400},
	{"Skin", 					82, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     10000},
	{"Skin", 					83, 	  E_TYPE_EPIC,         0,  	 0.0,     0.0,     20.0,    1.0,     10000},
	{"Skin", 					84, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     10000},
	{"Skin", 					125, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     13000},
	{"Skin", 					141, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     13000},
	{"Skin", 					265, 	  E_TYPE_EPIC,         0,  	 0.0,     0.0,     20.0,    1.0,     16000},
	{"Skin", 					266, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     16000},
	{"Skin", 					267, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     16000},
	{"Skin", 					274, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Skin", 					275, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Skin", 					276, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     9000},
	{"Staff Skin", 				211, 	  E_TYPE_IMPOSSIBLE,   0,  	 0.0,     0.0,     20.0,    1.0,     50000}
};

stock GetAccessoryOffsets(modelid, &Float:rx, &Float:ry, &Float:rz, &Float:zoom)
{
	for(new index; index < sizeof s_CratesSystemInfo; index++) {
	
	    if (s_CratesSystemInfo[index][E_CRATE_MODEL] == modelid)
	    {
	        rx = s_CratesSystemInfo[index][E_CRATE_RX];
	        ry = s_CratesSystemInfo[index][E_CRATE_RY];
	        rz = s_CratesSystemInfo[index][E_CRATE_RZ];
	        zoom = s_CratesSystemInfo[index][E_CRATE_ZOOM];
	        
	        return 1;
	    }
	}
	return 0;
}

CMD:givecrate(playerid, params[]) {

	if (sscanf(params, "u", params[0])) return 1;
	GiveCrate(params[0]);
	return 1;
}

stock ShowPlayerBoxAlert(playerid, discription[],  modelid, time, Float:rx, Float:ry, Float:rz, Float:zoom) {
    TextDrawShowForPlayer(playerid, textCrates[2]);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerCrates[1][playerid], modelid);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerCrates[1][playerid], rx, ry, rz, zoom);
    PlayerTextDrawShow(playerid, textPlayerCrates[1][playerid]);
	new reward_name[144];
	format(reward_name, sizeof reward_name, "~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", discription);
	PlayerTextDrawSetString(playerid, textPlayerCrates[2][playerid], reward_name);
	PlayerTextDrawShow(playerid, textPlayerCrates[2][playerid]);
	SetTimerEx("g_PlayerHideCrateTextdrawsEx", time, false, "d", playerid);
	Audio_Play(playerid, 67);
}

stock GivePlayerRandomAccessory(playerid, boxtype = BOX_TYPE_NORMAL) {
	#pragma unused boxtype
	// check if have box
	if (PlayerData[playerid][dCrates] < 1)
		return 0;

	if (GetPVarInt(playerid, "p_LastCrate"))
	    return 0;

    new index;

	// get back
	go_back:

	index = random(sizeof s_CratesSystemInfo);
	
	printf("%s, %d", s_CratesSystemInfo[index][E_CRATE_NAME], s_CratesSystemInfo[index][E_CRATE_RARITY]);
	
	switch (s_CratesSystemInfo[index][E_CRATE_RARITY])
	{
	    case E_TYPE_NO_COMUM:
	    {
	        if (random(15) < 03) goto go_back;
	    }
	    case E_TYPE_RARE:
	    {
	        if (random(15) < 09) goto go_back;
	    }
	    case E_TYPE_EPIC:
	    {
	        if (random(15) < 14) goto go_back;
	    }
	    case E_TYPE_IMPOSSIBLE:
	    {
	        // if impossible item
	        goto go_back;
	    }
	}
	// audio
	Audio_Play(playerid, 70);
	// show textdraws
	TextDrawShowForPlayer(playerid, textCrates[2]);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerCrates[1][playerid], s_CratesSystemInfo[index][E_CRATE_MODEL]);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerCrates[1][playerid], s_CratesSystemInfo[index][E_CRATE_RX], s_CratesSystemInfo[index][E_CRATE_RY], s_CratesSystemInfo[index][E_CRATE_RZ], s_CratesSystemInfo[index][E_CRATE_ZOOM]);
	PlayerTextDrawSetString(playerid, textPlayerCrates[2][playerid], "AGUARDE...");
	PlayerTextDrawShow(playerid, textPlayerCrates[2][playerid]);
	// timer
	SetTimerEx("g_PlayerHideCrateTextdraws", 1150, false, "dd", playerid, index);
	
	GivePlayerAcessorie(playerid, s_CratesSystemInfo[index][E_CRATE_NAME], s_CratesSystemInfo[index][E_CRATE_MODEL], s_CratesSystemInfo[index][E_CRATE_BONE], s_CratesSystemInfo[index][E_CRATE_COST]);
	
	SetPVarInt(playerid, "p_LastCrate", 1);
	
	PlayerData[playerid][dCrates] --;
	
    new string[15];
    format(string, sizeof string, "x%d", PlayerData[playerid][dCrates]);
    PlayerTextDrawSetString(playerid, textPlayerCrates[0][playerid], string);
	
	return 1;
}

callback g_PlayerHideCrateTextdraws(playerid, index) {
	new reward_name[75];
	format(reward_name, sizeof reward_name, "~n~~n~~n~~n~~n~~n~~n~~n~~n~%s", s_CratesSystemInfo[index][E_CRATE_NAME]);
	PlayerTextDrawSetString(playerid, textPlayerCrates[2][playerid], reward_name);
	PlayerTextDrawShow(playerid, textPlayerCrates[1][playerid]);
	SetTimerEx("g_PlayerHideCrateTextdrawsEx", 3000, false, "d", playerid);
}

callback g_PlayerHideCrateTextdrawsEx(playerid) {
	DeletePVar(playerid, "p_LastCrate");
	// hide textdraws
	TextDrawHideForPlayer(playerid, textCrates[2]);
	PlayerTextDrawHide(playerid, textPlayerCrates[1][playerid]);
	PlayerTextDrawHide(playerid, textPlayerCrates[2][playerid]);
}

stock GivePlayerAcessorie(playerid, accessory[], modelid, boneid, cost = 250) {
	new query[275];
	format(query, sizeof query, "INSERT INTO accessories (owner,accessory,modelid,bone,cost) VALUES ('%s','%s','%d','%d','%d')", getNome(playerid), accessory, modelid, boneid, cost / 5);
	db_free_result(db_query(serverDB, query));
	
	printf("ADD ACCOUNT: %s\n\n", accessory);
}

CMD:giveacessoryex(playerid, params[])
{
	if (!IsPlayerAdmin(playerid))
	    return 1;
	    
	new acessory[75], modelid, boneid;
	    
	if (sscanf(params, "s[75]dd", acessory, modelid, boneid))
	    return SendClientMessage(playerid, -1, "/giveaccessory <nome> <modelid> <boneid>");
	    
    GivePlayerAcessorie(playerid, acessory, modelid, boneid);
	return 1;
}

stock ShowAccessoryTextdraws(playerid) {

	if (GetPVarInt(playerid, "p_ViewAccessories"))
	    return 0;

	DeletePVar(playerid, "p_LastDatabaseIndex");
	DeletePVar(playerid, "p_PageAccessory");
	SetPVarInt(playerid, "p_ViewAccessories", 1);
	// show textdraws
	TextDrawShowForPlayer(playerid, textAccessory[0]);
	TextDrawShowForPlayer(playerid, textAccessory[1]);
	PlayerTextDrawShow(playerid, textPlayerAccessory[9]);
	// set max pages
	new query[128];
   	format(query, sizeof query, "SELECT id FROM accessories WHERE owner = '%s'", getNome(playerid));
    new DBResult:result_index = db_query(serverDB, query);
    SetPVarInt(playerid, "p_MaxPagesItens", (db_num_rows(result_index) / 9));
 	// free result
    db_free_result(result_index);
	// list items
	ListPlayerAccessories(playerid);
	
	return 1;
}

stock HideAccessoryTextdraws(playerid) {
	if (!GetPVarInt(playerid, "p_ViewAccessories"))
	    return 0;
	DeletePVar(playerid, "p_LastDatabaseIndex");
	DeletePVar(playerid, "p_PageAccessory");
	DeletePVar(playerid, "p_ViewAccessories");
	// show textdraws
	TextDrawHideForPlayer(playerid, textAccessory[0]);
	TextDrawHideForPlayer(playerid, textAccessory[1]);
	for(new index; index < 10; index++)
		PlayerTextDrawHide(playerid, textPlayerAccessory[index]);
		
	return 1;
}

stock SetAttachedObjectByDatabase(playerid, databaseid) {
	new DBResult:result_index;
	new query[75];
	// query
	format(query, sizeof query, "SELECT modelid, bone FROM accessories WHERE id = '%d'", databaseid);
	result_index = db_query(serverDB, query);
	// result
	if (db_num_rows(result_index)) {
	    // variables
	    new modelid = db_get_field_assoc_int(result_index, "modelid");
	    // check if is skin
	    if (modelid < 312) {
	    
			new skinid = GetPlayerSkin(playerid);

			SetPlayerSkin(playerid, modelid);

			PlayerData[playerid][dSkin] = modelid;

			if (PlayerData[playerid][dColete] > 0.0)
			{
				SetPlayerAttachedObject(playerid, 4, 19142, 1, ColeteOffSets[modelid][0], ColeteOffSets[modelid][1], ColeteOffSets[modelid][2],
				ColeteOffSets[modelid][3], ColeteOffSets[modelid][4], ColeteOffSets[modelid][5], ColeteOffSets[modelid][6], ColeteOffSets[modelid][7], ColeteOffSets[modelid][8]);
			}

			format(query, sizeof query, "%s", GetSkinName(skinid));

			if (!PlayerData[playerid][dBlockSkin])
			{
				if (isInventoryFreeSpace(playerid, getItemModelSlots(skinid))) {
					givePlayerItem(playerid, ITEM_TYPE_SKIN, skinid, 1, query);
				} else {
					dropItem(playerid, ITEM_TYPE_SKIN, skinid, 1, query, false);
				}
			}

			PlayerData[playerid][dBlockSkin] = true;

			StartPlayerProgress(playerid, "Trocando de roupa...", 60,  5.0);

		    // hide inventory
		    hideInventory(playerid);
		    // free result
		    db_free_result(result_index);
	        return 1;
	    }
	    // set attached object
	    SetPlayerAttachedObject(playerid, 6, modelid, db_get_field_assoc_int(result_index, "bone"), 0.0, 0.0, 0.0 + 0.1);
	    // select object
	    EditAttachedObject(playerid, 6);
	    // hide inventory
	    hideInventory(playerid);
	    
	    // save
	    PlayerData[playerid][dAccessoryModel] 		= modelid;
	    PlayerData[playerid][dAccessoryId] 	  		= databaseid;
	    PlayerData[playerid][dAccessoryBone] 	  	= db_get_field_assoc_int(result_index, "bone");
	    PlayerData[playerid][dAccessoryOffset][0] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][1] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][2] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][3] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][4] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][5] 	= 0.0;
	    PlayerData[playerid][dAccessoryOffset][6] 	= 1.0;
	    PlayerData[playerid][dAccessoryOffset][7] 	= 1.0;
	    PlayerData[playerid][dAccessoryOffset][8] 	= 1.0;
		SavePlayerAcessory(playerid);
	}
	db_free_result(result_index);
	
	return 1;
}

stock RemovePlayerAttachedAccessory(playerid) {
	if (PlayerData[playerid][dAccessoryModel] != 0) {
	    // reset variables
	    PlayerData[playerid][dAccessoryModel] = 0;
	    PlayerData[playerid][dAccessoryId] 	  = 0;
	    // remove attach
	    RemovePlayerAttachedObject(playerid, 6);
	    // remove textdraw
	    PlayerTextDrawHide(playerid, textEquippedAccessory);
	    // save
	    SavePlayerAcessory(playerid);
	}
}

stock SetPlayerAttachedAccessory(playerid) {
	if (PlayerData[playerid][dAccessoryModel] != 0) {
	    SetPlayerAttachedObject(playerid, 6, PlayerData[playerid][dAccessoryModel], PlayerData[playerid][dAccessoryBone],
	    PlayerData[playerid][dAccessoryOffset][0], PlayerData[playerid][dAccessoryOffset][1], PlayerData[playerid][dAccessoryOffset][2],
	    PlayerData[playerid][dAccessoryOffset][3], PlayerData[playerid][dAccessoryOffset][4], PlayerData[playerid][dAccessoryOffset][5],
	    PlayerData[playerid][dAccessoryOffset][6], PlayerData[playerid][dAccessoryOffset][7], PlayerData[playerid][dAccessoryOffset][8]);
	}
}

stock SavePlayerAcessory(playerid) {
	new query[185];
	format(query, sizeof query, "UPDATE accounts SET accessory = '%d,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f,%.3f' WHERE nome = '%s'",
	PlayerData[playerid][dAccessoryModel], PlayerData[playerid][dAccessoryId], PlayerData[playerid][dAccessoryBone],
	PlayerData[playerid][dAccessoryOffset][0], PlayerData[playerid][dAccessoryOffset][1], PlayerData[playerid][dAccessoryOffset][2],
	PlayerData[playerid][dAccessoryOffset][3], PlayerData[playerid][dAccessoryOffset][4], PlayerData[playerid][dAccessoryOffset][5],
	PlayerData[playerid][dAccessoryOffset][6], PlayerData[playerid][dAccessoryOffset][7], PlayerData[playerid][dAccessoryOffset][8], getNome(playerid));
	db_free_result(db_query(serverDB, query));
}

stock LoadPlayerAccesory(playerid) {
	new query[95], DBResult:result_query, string[12][75];
	format(query, sizeof query, "SELECT accessory FROM accounts WHERE nome = '%s'", getNome(playerid));
	result_query = db_query(serverDB, query);
	
	if (db_num_rows(result_query)) {
	    // get field
	    db_get_field(result_query, 0, query, sizeof query);
	    // split the result
	    split(query, string, ',');
        PlayerData[playerid][dAccessoryModel]  		= strval(string[0]);
        PlayerData[playerid][dAccessoryId]     		= strval(string[1]);
        PlayerData[playerid][dAccessoryBone]     	= strval(string[2]);
        PlayerData[playerid][dAccessoryOffset][0]   = floatstr(string[3]);
        PlayerData[playerid][dAccessoryOffset][1]   = floatstr(string[4]);
        PlayerData[playerid][dAccessoryOffset][2]   = floatstr(string[5]);
        PlayerData[playerid][dAccessoryOffset][3]   = floatstr(string[6]);
        PlayerData[playerid][dAccessoryOffset][4]   = floatstr(string[7]);
        PlayerData[playerid][dAccessoryOffset][5]   = floatstr(string[8]);
        PlayerData[playerid][dAccessoryOffset][6]   = floatstr(string[9]);
        PlayerData[playerid][dAccessoryOffset][7]   = floatstr(string[10]);
        PlayerData[playerid][dAccessoryOffset][8]   = floatstr(string[11]);
	}
	db_free_result(result_query);
}

stock ListPlayerAccessories(playerid, bool:reverse = false) {
	new page_index = GetPVarInt(playerid, "p_PageAccessory");
	new last_index = GetPVarInt(playerid, "p_LastDatabaseIndex");
	new query[144];
	new DBResult:result_index;
	new rows_count, count_index;
	// query
	if (!reverse) {
		format(query, sizeof query, "SELECT id, modelid FROM accessories WHERE owner = '%s' and id > '%d' LIMIT 9", getNome(playerid), last_index);
//		print(query);
	}
	else {
	    format(query, sizeof query, "SELECT id, modelid FROM accessories WHERE owner = '%s' and id > '%d' LIMIT 9", getNome(playerid), playerPageFirstIndex[playerid][page_index]);
//	    print(query);
	}
    result_index = db_query(serverDB, query);
    
    rows_count = db_num_rows(result_index);
    
    // reset the select
	for(new index; index < 9; index++)
	    playerRowIndex[playerid][index] = -1;
    
    if (rows_count)
    {
        for (new id = 0; id < rows_count; id++)
        {
            if (id >= 9)
				break;
            // model
            new modelid = db_get_field_assoc_int(result_index, "modelid");
            // change textdraws
            PlayerTextDrawSetPreviewModel(playerid, textPlayerAccessory[id], modelid);
            // get offsets textdraw
            new Float:rx, Float:ry, Float:rz, Float:zoom;
            GetAccessoryOffsets(modelid, rx, ry, rz, zoom);
            // set textdraw preview rot
            PlayerTextDrawSetPreviewRot(playerid, textPlayerAccessory[id], rx, ry, rz, zoom);
            // show the textdraw
            PlayerTextDrawShow(playerid, textPlayerAccessory[id]);
            // save result id
            playerRowIndex[playerid][id] = db_get_field_assoc_int(result_index, "id");
            SetPVarInt(playerid, "p_LastDatabaseIndex", playerRowIndex[playerid][id]);
            // goto next row
            db_next_row(result_index);
            
            count_index ++;
        }
        
        playerPageFirstIndex[playerid][page_index] = playerRowIndex[playerid][0] - 1;
        
//        printf("first: %d      last: %d", playerPageFirstIndex[page_index], GetPVarInt(playerid, "p_LastDatabaseIndex"));
    } else {
        db_free_result(result_index);
        return 0;
    }
	// hide invalid variables
    for(new id = count_index; id < 9; id++) {
        PlayerTextDrawHide(playerid, textPlayerAccessory[id]);
    }
	// free result
    db_free_result(result_index);
	// update textdraw
    format(query, sizeof query, "%d-%d", page_index + 1, GetPVarInt(playerid, "p_MaxPagesItens") + 1);
    PlayerTextDrawSetString(playerid, textPlayerAccessory[9], query);
    
    return 1;
}


stock ShowPlayerMenuAccessory(playerid, type = MENU_ACCESSORY_SHOP) {
	if (GetPVarInt(playerid, "p_ViewAccessoriesMenu"))
	    return 0;

	DeletePVar(playerid, "p_LastDatabaseIndex");
	DeletePVar(playerid, "p_PageAccessory");
	SetPVarInt(playerid, "p_ViewAccessoriesMenu", 1);
	
	playerMenuAccessory[playerid] = type;
	
	SelectTextDraw(playerid, 0xFFFFFFBB);
	
	// update
	switch(type)
	{
	    case MENU_ACCESSORY_SHOP:
		{
	        SetPVarInt(playerid, "p_MaxPagesItens", sizeof(s_CratesSystemInfo) / 8);
	    }
	    case MENU_ACCESSORY_PLAYER:
		{
			new query[80];
		   	format(query, sizeof query, "SELECT id FROM accessories WHERE owner = '%s'", getNome(playerid));
		    new DBResult:result_index = db_query(serverDB, query);
		    SetPVarInt(playerid, "p_MaxPagesItens", (db_num_rows(result_index) / 8));
		 	// free result
		    db_free_result(result_index);
	    }
	}
	
	// show textdraws
	for(new index; index < sizeof textMenuAccessory; index++) {
	    TextDrawShowForPlayer(playerid, textMenuAccessory[index]);
	}
	
	// update textdraws
	UpdatePlayerMenuAccessory(playerid);
	
	return 1;
}

stock HidePlayerMenuAccessory(playerid) {
	if (!GetPVarInt(playerid, "p_ViewAccessoriesMenu"))
	    return 0;

	DeletePVar(playerid, "p_LastDatabaseIndex");
	DeletePVar(playerid, "p_PageAccessory");
	DeletePVar(playerid, "p_ViewAccessoriesMenu");

	// show textdraws
	for(new index; index < sizeof textMenuAccessory; index++) {
	    TextDrawHideForPlayer(playerid, textMenuAccessory[index]);
	}
	
	for(new index; index < sizeof textPlayerMenuAccessory; index++) {
	    PlayerTextDrawHide(playerid, textPlayerMenuAccessory[index]);
	}

	return 1;
}


stock UpdatePlayerMenuAccessory(playerid, bool:reverse = false)
{
	new page_index = GetPVarInt(playerid, "p_PageAccessory");
	new last_index = GetPVarInt(playerid, "p_LastDatabaseIndex");
	new query[144];
	new DBResult:result_index;
	new rows_count, count_index;
	
	switch (playerMenuAccessory[playerid])
	{
	    case MENU_ACCESSORY_PLAYER:
	    {
			// query
			if (!reverse) {
				format(query, sizeof query, "SELECT id, modelid, cost FROM accessories WHERE owner = '%s' and id > '%d' LIMIT 8", getNome(playerid), last_index);
			}
			else {
			    format(query, sizeof query, "SELECT id, modelid, cost FROM accessories WHERE owner = '%s' and id > '%d' LIMIT 8", getNome(playerid), playerPageFirstIndex[playerid][page_index]);
			}
		    result_index = db_query(serverDB, query);

		    rows_count = db_num_rows(result_index);

		    // reset the select
			for(new index; index < 9; index++)
			    playerRowIndex[playerid][index] = -1;

		    if (rows_count)
		    {
		        for (new id = 0; id < rows_count; id++)
		        {
		            if (id >= 8)
						break;
		            // model
		            new modelid = db_get_field_assoc_int(result_index, "modelid");
		            // change textdraws
		            PlayerTextDrawSetPreviewModel(playerid, textPlayerMenuAccessory[id], modelid);
		            // get offsets textdraw
		            new Float:rx, Float:ry, Float:rz, Float:zoom;
		            GetAccessoryOffsets(modelid, rx, ry, rz, zoom);
		            // set textdraw preview rot
		            PlayerTextDrawSetPreviewRot(playerid, textPlayerMenuAccessory[id], rx, ry, rz, zoom);
		            // show the textdraw
		            PlayerTextDrawShow(playerid, textPlayerMenuAccessory[id]);
		            // save result id
		            playerRowIndex[playerid][id] = db_get_field_assoc_int(result_index, "id");
		            SetPVarInt(playerid, "p_LastDatabaseIndex", playerRowIndex[playerid][id]);
		            // show textdraws
		            format(query, sizeof query, "~g~~h~$%d", db_get_field_assoc_int(result_index, "cost"));
		            PlayerTextDrawSetString(playerid, textPlayerMenuAccessory[id + 8], query);
		            PlayerTextDrawShow(playerid, textPlayerMenuAccessory[id + 8]);
		            // goto next row
		            db_next_row(result_index);

		            count_index ++;
		        }

		        playerPageFirstIndex[playerid][page_index] = playerRowIndex[playerid][0] - 1;

		//        printf("first: %d      last: %d", playerPageFirstIndex[page_index], GetPVarInt(playerid, "p_LastDatabaseIndex"));
		    }
			// hide invalid variables
		    for(new id = count_index; id < 8; id++) {
		        PlayerTextDrawHide(playerid, textPlayerMenuAccessory[id]);
		        PlayerTextDrawHide(playerid, textPlayerMenuAccessory[id + 8]);
		    }
			// free result
		    db_free_result(result_index);
		}
		case MENU_ACCESSORY_SHOP:
		{
		    // reset the select
			for(new index; index < 9; index++)
			    playerRowIndex[playerid][index] = -1;
		
			for (new id = page_index * 8; id < sizeof s_CratesSystemInfo; id++)
		    {
		        if (count_index >= 8)
					break;
		        // model
		        new modelid = s_CratesSystemInfo[id][E_CRATE_MODEL];
		        // change textdraws
		        PlayerTextDrawSetPreviewModel(playerid, textPlayerMenuAccessory[count_index], modelid);
		        // get offsets textdraw
		        new Float:rx, Float:ry, Float:rz, Float:zoom;
		        GetAccessoryOffsets(modelid, rx, ry, rz, zoom);
		        // set textdraw preview rot
		        PlayerTextDrawSetPreviewRot(playerid, textPlayerMenuAccessory[count_index], rx, ry, rz, zoom);
		        // show the textdraw
		        PlayerTextDrawShow(playerid, textPlayerMenuAccessory[count_index]);
		        // save result id
		        playerRowIndex[playerid][count_index] = id;
		        // show textdraws
		        format(query, sizeof query, "%d ZP", s_CratesSystemInfo[id][E_CRATE_COST]);
		        PlayerTextDrawSetString(playerid, textPlayerMenuAccessory[count_index + 8], query);
		        PlayerTextDrawShow(playerid, textPlayerMenuAccessory[count_index + 8]);
		        // goto next row
		        db_next_row(result_index);

		        count_index ++;
			}
			
		    for(new id = count_index; id < 8; id++) {
		        PlayerTextDrawHide(playerid, textPlayerMenuAccessory[id]);
		        PlayerTextDrawHide(playerid, textPlayerMenuAccessory[id + 8]);
		    }
		}
	}
	// update textdraw
    format(query, sizeof query, "%d-%d", page_index + 1, GetPVarInt(playerid, "p_MaxPagesItens") + 1);
    PlayerTextDrawSetString(playerid, textPlayerMenuAccessory[16], query);
    PlayerTextDrawShow(playerid, textPlayerMenuAccessory[16]);
    
    return 1;
}

stock ChangePlayerMenuAccessoryType(playerid, type)
{
	if (playerMenuAccessory[playerid] == type)
	    return 0;
	    
    playerMenuAccessory[playerid] = type;
	    
	DeletePVar(playerid, "p_LastDatabaseIndex");
	DeletePVar(playerid, "p_PageAccessory");

	// update
	switch(type)
	{
	    case MENU_ACCESSORY_SHOP:
		{
	        SetPVarInt(playerid, "p_MaxPagesItens", sizeof(s_CratesSystemInfo) / 8);
	    }
	    case MENU_ACCESSORY_PLAYER:
		{
			new query[80];
		   	format(query, sizeof query, "SELECT id FROM accessories WHERE owner = '%s'", getNome(playerid));
		    new DBResult:result_index = db_query(serverDB, query);
		    SetPVarInt(playerid, "p_MaxPagesItens", (db_num_rows(result_index) / 8));
		 	// free result
		    db_free_result(result_index);
	    }
	}
	
	UpdatePlayerMenuAccessory(playerid);
	    
	return 1;
}

callback CheckPlayerDailyCrate(playerid) {

	if (gettime() < PlayerData[playerid][dDailyCrate])
	    return 0;
	    
	PlayerData[playerid][dDailyCrate] = gettime() + 86400;
	PlayerData[playerid][dCrates] ++;
	    
    ShowPlayerBoxAlert(playerid, "Caixa de acessorios~n~~b~~h~- PRESENTE DIARIO -",  964, 3000, -30.0, 0.0, 50.0, 1.2);
	    
 	new string[15];
    format(string, sizeof string, "x%d", PlayerData[playerid][dCrates]);
    PlayerTextDrawSetString(playerid, textPlayerCrates[0][playerid], string);
	    
    savePlayerAccount(playerid);
	    
	return 1;
}

callback GiveCrate(playerid) {

	PlayerData[playerid][dCrates] ++;

    ShowPlayerBoxAlert(playerid, "Caixa de acessorios",  964, 3000, -30.0, 0.0, 50.0, 1.2);

 	new string[15];
    format(string, sizeof string, "x%d", PlayerData[playerid][dCrates]);
    PlayerTextDrawSetString(playerid, textPlayerCrates[0][playerid], string);

    savePlayerAccount(playerid);

	return 1;
}

callback OnPlayerSelectAccessoryShop(playerid, index) {

	new price = s_CratesSystemInfo[index][E_CRATE_COST];

	if (PlayerData[playerid][dCoins] < price)
	    return SendClientMessagef(playerid, corError, "ERRO: {999999}Você não tem {FF5555}%d ZP {999999}para comprar este item.", price);

	format(stringGlobal, 128, "Voce realmente deseja comprar este item por %d ZP? Nao havera reembolso apos a compra.", price);
	ShowPlayerDialogTextdraw(playerid, 8746, stringGlobal);

    SetPVarInt(playerid, "p_SelectedAccessoryMenu", index);
    SetPVarInt(playerid, "p_PriceAccessoryMenu", price);

	return 1;
}

callback OnPlayerSelectAccessoryPlayer(playerid, index) {

	new query[80], price;
  	format(query, sizeof query, "SELECT cost FROM accessories WHERE id = '%d'", index);
    new DBResult:result_index = db_query(serverDB, query);
    if (db_num_rows(result_index)) {
        price = db_get_field_assoc_int(result_index, "cost");
    }
    db_free_result(result_index);

	format(stringGlobal, 128, "Voce realmente deseja vender este item por $%d? Nao havera reembolso apos a venda.", price);
	ShowPlayerDialogTextdraw(playerid, 8745, stringGlobal);

    SetPVarInt(playerid, "p_SelectedAccessoryMenu", index);
    SetPVarInt(playerid, "p_PriceAccessoryMenu", price);
	return 1;
}

public OnTextDialogResponse(playerid, dialogid, response)
{
	// dialogid
	switch (dialogid) {
	
		case 8745: {
			// select textdraw
			SelectTextDraw(playerid, 0xFFFFFFBB);
		    if (response) {
		        new index = GetPVarInt(playerid, "p_SelectedAccessoryMenu");
		        new query[75];
				// give money
				PlayerData[playerid][dMoney] += GetPVarInt(playerid, "p_PriceAccessoryMenu");
				format(query, sizeof query, "Voce recebeu ~g~~h~$%d", GetPVarInt(playerid, "p_PriceAccessoryMenu"));
				ShowPlayerBoxAlert(playerid, query, 1212, 2000, -20.0, 0.0, 50, 0.7);
				// delete item
				format(query, sizeof query, "DELETE FROM accessories WHERE id = '%d'", index);
				db_free_result(db_query(serverDB, query));
				// delete pvars
				DeletePVar(playerid, "p_LastDatabaseIndex");
				DeletePVar(playerid, "p_PageAccessory");
				DeletePVar(playerid, "p_PriceAccessoryMenu");
				DeletePVar(playerid, "p_SelectedAccessoryMenu");
				// set new max page
			   	format(query, sizeof query, "SELECT id FROM accessories WHERE owner = '%s'", getNome(playerid));
			    new DBResult:result_index = db_query(serverDB, query);
			    SetPVarInt(playerid, "p_MaxPagesItens", (db_num_rows(result_index) / 8));
			 	// free result
			    db_free_result(result_index);
				// update list
				UpdatePlayerMenuAccessory(playerid);

				// remove accessory if is current using
				if (PlayerData[playerid][dAccessoryId] == index) {
				    PlayerData[playerid][dAccessoryId] = 0;
				    PlayerData[playerid][dAccessoryModel] = 0;
				    SavePlayerAcessory(playerid);
				}
		    }
		}
		case 8746: {
			// select textdraw
			SelectTextDraw(playerid, 0xFFFFFFBB);
		    if (response) {
		        new index = GetPVarInt(playerid, "p_SelectedAccessoryMenu");
				// give money
				if (PlayerData[playerid][dCoins] < GetPVarInt(playerid, "p_PriceAccessoryMenu"))
				    return SendClientMessagef(playerid, corError, "ERRO: {999999}Você não tem {FF5555}%d ZP {999999}para comprar este item.", GetPVarInt(playerid, "p_PriceAccessoryMenu"));
				// delete item
				GivePlayerCoins(playerid, - GetPVarInt(playerid, "p_PriceAccessoryMenu"));
				// check if a box
				if (s_CratesSystemInfo[index][E_CRATE_MODEL] == 964) {
				    // give a crate
				    GiveCrate(playerid);
					// delete pvars
					DeletePVar(playerid, "p_LastDatabaseIndex");
					DeletePVar(playerid, "p_PageAccessory");
					DeletePVar(playerid, "p_PriceAccessoryMenu");
					DeletePVar(playerid, "p_SelectedAccessoryMenu");
					// update list
					UpdatePlayerMenuAccessory(playerid);
				    return 1;
				}
				// give accessory
				GivePlayerAcessorie(playerid, s_CratesSystemInfo[index][E_CRATE_NAME], s_CratesSystemInfo[index][E_CRATE_MODEL], s_CratesSystemInfo[index][E_CRATE_BONE], s_CratesSystemInfo[index][E_CRATE_COST]);
				// alert box
				new Float:rx, Float:ry, Float:rz, Float:zoom;
			    GetAccessoryOffsets(s_CratesSystemInfo[index][E_CRATE_MODEL], rx, ry, rz, zoom);
				ShowPlayerBoxAlert(playerid, s_CratesSystemInfo[index][E_CRATE_NAME],  s_CratesSystemInfo[index][E_CRATE_MODEL], 2000, rx, ry, rz, zoom);
				// delete pvars
				DeletePVar(playerid, "p_LastDatabaseIndex");
				DeletePVar(playerid, "p_PageAccessory");
				DeletePVar(playerid, "p_PriceAccessoryMenu");
				DeletePVar(playerid, "p_SelectedAccessoryMenu");
				// update list
				UpdatePlayerMenuAccessory(playerid);
		    }
		}
	}
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (IsPlayerInInventory(playerid))
	{
		new page_index = GetPVarInt(playerid, "p_PageAccessory");
		
		if (GetTickCount() > GetPVarInt(playerid, "p_LastPage"))
		{
			// inventory accessories
			if (clickedid == textAccessory[0])
			{
			    if (page_index > 0)
				{
				    SetPVarInt(playerid, "p_PageAccessory", page_index - 1);
					ListPlayerAccessories(playerid, .reverse = true);
					SetPVarInt(playerid, "p_LastPage", GetTickCount() + 400);
			    }
			}
			else if (clickedid == textAccessory[1])
			{
			    if (page_index < GetPVarInt(playerid, "p_MaxPagesItens"))
				{
				    SetPVarInt(playerid, "p_PageAccessory", page_index + 1);
					ListPlayerAccessories(playerid, .reverse = false);
					SetPVarInt(playerid, "p_LastPage", GetTickCount() + 400);
			    }
			}
		}
	}
	
	if (GetPVarInt(playerid, "p_ViewAccessoriesMenu")) {
	
		if (clickedid == Text:INVALID_TEXT_DRAW)
		    return SelectTextDraw(playerid, 0xFFFFFFBB);
	
	    new page_index = GetPVarInt(playerid, "p_PageAccessory");
		if (clickedid == textMenuAccessory[1]) {
		    ChangePlayerMenuAccessoryType(playerid, MENU_ACCESSORY_SHOP);
		}
		else if (clickedid == textMenuAccessory[2]) {
		    ChangePlayerMenuAccessoryType(playerid, MENU_ACCESSORY_PLAYER);
		}
		else if (clickedid == textMenuAccessory[3]) {
		    HidePlayerMenuAccessory(playerid);
		    SelectTextDraw(playerid, 0xFFFFFF10);
		}
		// menu accessories
		if (GetTickCount() > GetPVarInt(playerid, "p_LastPage"))
		{
			if (clickedid == textMenuAccessory[4])
			{
			    if (page_index > 0)
				{
				    SetPVarInt(playerid, "p_PageAccessory", page_index - 1);
					UpdatePlayerMenuAccessory(playerid, .reverse = true);
					
					SetPVarInt(playerid, "p_LastPage", GetTickCount() + 400);
			    }
			}
			else if (clickedid == textMenuAccessory[5])
			{
			    if (page_index < GetPVarInt(playerid, "p_MaxPagesItens"))
				{
				    SetPVarInt(playerid, "p_PageAccessory", page_index + 1);
					UpdatePlayerMenuAccessory(playerid, .reverse = false);
					
					SetPVarInt(playerid, "p_LastPage", GetTickCount() + 400);
			    }
			}
		}
		return 1;
	}
	
 	#if defined cOnPlayerClickTextDraw
  		return cOnPlayerClickTextDraw(playerid, clickedid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw cOnPlayerClickTextDraw
#if defined cOnPlayerClickTextDraw
	forward cOnPlayerClickTextDraw(playerid, Text:clickedid);
#endif

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if (IsPlayerInInventory(playerid)) {
	
	    for(new index; index < 9; index++) {
	        // check if clicked
	        if (playertextid == textPlayerAccessory[index]) {
	            SetAttachedObjectByDatabase(playerid, playerRowIndex[playerid][index]);
	            return 1;
	        }
	    }
	}
	if (GetPVarInt(playerid, "p_ViewAccessoriesMenu")) {
	
	    for(new index; index < 8; index++) {
	    
	        if (playertextid == textPlayerMenuAccessory[index]) {
	        
	            if (playerRowIndex[playerid][index] == -1)
	                break;
	        
	            switch(playerMenuAccessory[playerid])
	            {
				    case MENU_ACCESSORY_SHOP:
					{
					    OnPlayerSelectAccessoryShop(playerid, playerRowIndex[playerid][index]);
				    }
				    case MENU_ACCESSORY_PLAYER:
					{
					    OnPlayerSelectAccessoryPlayer(playerid, playerRowIndex[playerid][index]);
				    }
	            }
	        
	            break;
	        }
	    }
	
	    return 1;
	}
 	#if defined cOPCPTD
  		return cOPCPTD(playerid, playertextid);
	#else
 		return 1;
	#endif
}
#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw cOPCPTD
#if defined cOPCPTD
	forward cOPCPTD(playerid, PlayerText:playertextid);
#endif


public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if (index != 6)
	    return 1;
    if(response)
    {
        SetPlayerAttachedObject(playerid, 6, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        
	    PlayerData[playerid][dAccessoryModel] 		= modelid;
	    PlayerData[playerid][dAccessoryBone] 	  	= boneid;
	    PlayerData[playerid][dAccessoryOffset][0] 	= fOffsetX;
	    PlayerData[playerid][dAccessoryOffset][1] 	= fOffsetY;
	    PlayerData[playerid][dAccessoryOffset][2] 	= fOffsetZ;
	    PlayerData[playerid][dAccessoryOffset][3] 	= fRotX;
	    PlayerData[playerid][dAccessoryOffset][4] 	= fRotY;
	    PlayerData[playerid][dAccessoryOffset][5] 	= fRotZ;
	    PlayerData[playerid][dAccessoryOffset][6] 	= fScaleX;
	    PlayerData[playerid][dAccessoryOffset][7] 	= fScaleY;
	    PlayerData[playerid][dAccessoryOffset][8] 	= fScaleZ;
	    // save
	    SavePlayerAcessory(playerid);
    }
    else
    {
		EditAttachedObject(playerid, 6);
    }
    return 1;
}

/*
CREATE TABLE `acessories` ( `id` INTEGER PRIMARY KEY AUTOINCREMENT, `owner` TEXT DEFAULT 'NinguÃ©m', `name` TEXT DEFAULT 'Nenhum', `model` INTEGER DEFAULT 999, `cost` INTEGER DEFAULT 0, `date` INTEGER DEFAULT '00/00/00 00:00:00', `expire` INTEGER DEFAULT -1 )
*/












