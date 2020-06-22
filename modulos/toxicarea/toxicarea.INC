#define MAX_TOXIC_AREAS (50)

// Quantidade de areas toxicas
new toxicareas = 0;

enum toxicEnum {
	Float:areatoxica_x,
	Float:areatoxica_y,
	Float:areatoxica_z,
	Float:areatoxica_s,
}
new toxicAreaInfo[MAX_TOXIC_AREAS][toxicEnum];

// Textdraws
new Text:textToxicArea[2];

stock CreateServerAreasToxicas() {

	AddServerToxicArea(2478.6580,-2224.1394,13.3828, 30.0);
	AddServerToxicArea(2670.8496,-2084.0037,13.5469, 40.0);
	AddServerToxicArea(2757.2434,-2089.7249,12.2545, 30.0);
	AddServerToxicArea(2448.1023,-1970.6045,13.5469, 15.0);
	AddServerToxicArea(2130.5500,-1998.6483,20.2707, 40.0);
	AddServerToxicArea(2237.9990,-2280.3335,13.5545, 40.0);
	AddServerToxicArea(-378.3448,-1852.3171,0.5249, 50.0);
	AddServerToxicArea(-593.2579,-1890.2622,5.9029, 70.0);
	AddServerToxicArea(-819.6978,-1970.4662,11.5690, 70.0);
	AddServerToxicArea(-1408.6851,498.8289,11.1953, 8.0);
	AddServerToxicArea(-1349.2169,507.1247,11.1953, 8.0);
	AddServerToxicArea(-1291.4204,502.3744,11.1953, 8.0);
	AddServerToxicArea(-1332.3987,495.3295,11.1953, 8.0);
	AddServerToxicArea(-1372.1169,495.9716,8.6427, 8.0);
	AddServerToxicArea(-1411.8019,500.3175,3.0391, 20.0);
	AddServerToxicArea(-1582.9351,719.6428,-5.2422, 30.0);
	AddServerToxicArea(-1419.5891,1489.7692,11.8084, 70.0);
	AddServerToxicArea(188.6085,1413.9816,10.5859, 100.0);
	AddServerToxicArea(250.0547,1862.7078,8.7578, 10.0);
	AddServerToxicArea(285.3167,1816.0964,1.0078, 30.0);
	AddServerToxicArea(268.6601,1883.5176,-30.0938, 15.0);
	AddServerToxicArea(2584.8047,2828.2761,10.8203, 30.0);
	AddServerToxicArea(-2141.6868,-2375.9653,37.8516, 165.0);
}

stock CreateTextdrawToxic() {
	textToxicArea[0] = TextDrawCreate(266.000000, 369.000000, "ld_none:warp");
	TextDrawBackgroundColor(textToxicArea[0], 0);
	TextDrawFont(textToxicArea[0], 4);
	TextDrawLetterSize(textToxicArea[0], 0.500000, 1.799999);
	TextDrawColor(textToxicArea[0], 16711700);
	TextDrawSetOutline(textToxicArea[0], 0);
	TextDrawSetProportional(textToxicArea[0], 1);
	TextDrawSetShadow(textToxicArea[0], 1);
	TextDrawUseBox(textToxicArea[0], 1);
	TextDrawBoxColor(textToxicArea[0], 255);
	TextDrawTextSize(textToxicArea[0], 102.000000, 20.000000);
	TextDrawSetSelectable(textToxicArea[0], 0);

	textToxicArea[1] = TextDrawCreate(318.000000, 373.000000, "Area toxica!");
	TextDrawAlignment(textToxicArea[1], 2);
	TextDrawBackgroundColor(textToxicArea[1], 16711685);
	TextDrawFont(textToxicArea[1], 2);
	TextDrawLetterSize(textToxicArea[1], 0.200000, 1.200000);
	TextDrawColor(textToxicArea[1], 16711730);
	TextDrawSetOutline(textToxicArea[1], 1);
	TextDrawSetProportional(textToxicArea[1], 1);
	TextDrawSetSelectable(textToxicArea[1], 0);
}

stock ShowTextDrawsToxic(playerid) {

	if (GetPVarInt(playerid, "inToxicArea"))
	    return 0;

	for(new text; text < sizeof textToxicArea; text++) {
	    TextDrawShowForPlayer(playerid, textToxicArea[text]);
	}
	
	SetPVarInt(playerid, "inToxicArea", 1);
	
	return 1;
}

stock HideTextDrawsToxic(playerid) {

	if (!GetPVarInt(playerid, "inToxicArea"))
	    return 0;

	for(new text; text < sizeof textToxicArea; text++) {
	    TextDrawHideForPlayer(playerid, textToxicArea[text]);
	}

	DeletePVar(playerid, "inToxicArea");
	
	return 1;
}

// funcs
stock AddServerToxicArea(Float:x, Float:y, Float:z, Float:toxicsize) {

	if (toxicareas >= MAX_TOXIC_AREAS)
	    return 0;
    
    toxicAreaInfo[toxicareas][areatoxica_x] = x;
    toxicAreaInfo[toxicareas][areatoxica_y] = y;
    toxicAreaInfo[toxicareas][areatoxica_z] = z;
    toxicAreaInfo[toxicareas][areatoxica_s] = toxicsize;

	toxicareas++;
	
	return 1;
}

stock IsPlayerInToxicArea(playerid) {

	if (GetPlayerVirtualWorld(playerid) != 0)
	    return 0;

	for(new areatoxic; areatoxic < toxicareas; areatoxic++) {

		if (IsPlayerInRangeOfPoint(playerid, toxicAreaInfo[areatoxic][areatoxica_s], toxicAreaInfo[areatoxic][areatoxica_x], toxicAreaInfo[areatoxic][areatoxica_y], toxicAreaInfo[areatoxic][areatoxica_z])) {
		    return 1;
		}
	}
	return 0;
}
