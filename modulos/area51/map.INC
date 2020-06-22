// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 

#define MAP_RESCALE         (2000.0)
#define RADAR_MAP_ZOFFSET	(-0.600)

new
		bool:showPlayerInradar	 [MAX_PLAYERS],
		playerRadarObject		 [MAX_PLAYERS],
		Text3D:playerRadar3DText [MAX_PLAYERS];

static  Float:MAP_OFF_X    =	 0.0,
       	Float:MAP_OFF_Y    =   	 0.0,
       	Float:MAP_OFF_Z    =   	 0.0;

enum RADAROBJECTOFFSETS {
		RadarMapObject,
		Float:RadarOffX,
		Float:RadarOffY,
		Float:RadarOffZ,
}
static MapPieces[8][RADAROBJECTOFFSETS];

stock IniciarPlayersMap() {

    SetTimer("updateArea51PlayersMap", 4500, true);

	new index;
	MapPieces[index++][RadarMapObject] = CreateDynamicObject(19168,-0.750,0.750,0.000,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	MapPieces[index++][RadarMapObject] = CreateDynamicObject(19169,0.750,0.750,0.000,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	MapPieces[index++][RadarMapObject] = CreateDynamicObject(19170,-0.750,-0.750,0.000,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	MapPieces[index++][RadarMapObject] = CreateDynamicObject(19171,0.750,-0.750,0.000,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	MapPieces[index][RadarMapObject] = CreateDynamicObject(19362,1.495,-0.014,-1.750,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(MapPieces[index++][RadarMapObject], 0, 6056, "venice_law", "law_blue4", -10079488);
	MapPieces[index][RadarMapObject] = CreateDynamicObject(19362,-1.534,-0.014,-1.750,0.000,0.000,0.000,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(MapPieces[index++][RadarMapObject], 0, 6056, "venice_law", "law_blue4", -10079488);
	MapPieces[index][RadarMapObject] = CreateDynamicObject(19362,-0.019,1.500,-1.749,0.000,0.000,89.999,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(MapPieces[index++][RadarMapObject], 0, 6056, "venice_law", "law_blue4", -10079488);
	MapPieces[index][RadarMapObject] = CreateDynamicObject(19362,-0.019,-1.529,-1.749,0.000,0.000,89.999,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(MapPieces[index++][RadarMapObject], 0, 6056, "venice_law", "law_blue4", -10079488);

	for(new i = 0; i < 8; i++) {
		GetDynamicObjectPos(MapPieces[i][RadarMapObject], MapPieces[i][RadarOffX], MapPieces[i][RadarOffY], MapPieces[i][RadarOffZ]);
	}
	
	SetRadarMap(220.8120,1822.9980,6.4141);
}

stock SetRadarMap(Float:x, Float:y, Float:z)
{
    MAP_OFF_X = x;
    MAP_OFF_Y = y;
    MAP_OFF_Z = z;

	for(new i = 0; i < 8; i++) {
		SetDynamicObjectPos(MapPieces[i][RadarMapObject], MapPieces[i][RadarOffX]+x, MapPieces[i][RadarOffY]+y, MapPieces[i][RadarOffZ]+z);
	}
	return 1;
}

stock createMapObjects(playerid) {

    if (showPlayerInradar[playerid]) return 0;

	playerRadarObject[playerid] = CreateDynamicObject(338,0.0,0.0,-1000.0,-4.799,0.000,0.000,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(playerRadarObject[playerid], 0, 10765, "airportgnd_sfse", "white", -6750208);
	playerRadar3DText[playerid] = CreateDynamic3DTextLabel(getNome(playerid), 0xFF0000FF, 0.0, 0.0, 0.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 10.0);

	showPlayerInradar[playerid] = true;

	return 1;
}

stock destroyMapObjects(playerid) {

    if (!showPlayerInradar[playerid]) return 0;

	DestroyDynamicObject(playerRadarObject[playerid]);
	DestroyDynamic3DTextLabel(playerRadar3DText[playerid]);

	playerRadarObject[playerid] = -1;
	playerRadar3DText[playerid] = Text3D:-1;
	
	showPlayerInradar[playerid] = false;
	
	return 1;
}

callback updateArea51PlayersMap()
{
	static string_map[35];
	foreach(new playerid : Player)
	{
	    if (!showPlayerInradar[playerid]) continue;
	
	    static
				Float:x,
				Float:y,
				Float:z
				;

	    GetPlayerPos(playerid, x, y, z);

	    if( ( x < 3000.0 && x > -3000.0 ) && ( y < 3000.0 && y > -3000.0 ) && ( z < 3000.0 && z > -3000.0 ) ) {

			x = ( x / MAP_RESCALE ) + MAP_OFF_X ;
			y = ( y / MAP_RESCALE ) + MAP_OFF_Y ;

		    format(string_map, sizeof (string_map), "{%06x}%s", GetPlayerColor(playerid) >>> 8, getNome(playerid));
		    UpdateDynamic3DTextLabelText(playerRadar3DText[playerid], 0xFFFFFFFF, string_map);

			SetDynamicObjectPos(playerRadarObject[playerid], x, y, RADAR_MAP_ZOFFSET + MAP_OFF_Z);

            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, playerRadar3DText[playerid], E_STREAMER_X, x);
            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, playerRadar3DText[playerid], E_STREAMER_Y, y);
            Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, playerRadar3DText[playerid], E_STREAMER_Z, RADAR_MAP_ZOFFSET + MAP_OFF_Z + 1.3);
		}
	}
	return 1;
}








