new HUD_GZ;

// server restart
new serverRestartTime = SERVER_RESTART_TIME;

// Database
new DB:serverDB;

// Bases database
new DB:serverBasesDB;

// Whitelist
new serverWhitelistActive = 0;

// Sobreviventes on
new serverCountSurvivors;

// weathers
new serverCurrentWeather = 1,
	serverWeatherLastUpdate;
	
// global chat
new bool:serverGlobalChat = true;

new bool:serverSecurity = false;

// server client update tick
new
	clientTickUpdate = 170;
	
// Keys created
new serverVehicleKeys = 1000;

// server auto msg
new serverAutoMsg = SERVER_AUTO_MSG_TIME;

// vehicles
enum vehEnumInfo {

	// Loot id
	vehLoot,

	// Retirar gasolina do carro
	vehLastFuel,

	// Gasolina
	vehFuel,
	
	// died
	vehDied,

	// ultimo a usar
	vehTickUsed,
	
	// unique id
	vehUniqueId,
	
	// chave
	vehKeyId,
	
	// trancado
	vehLocked,
	
	// tick respawn
	vehTickRespawn,
	
	// destroy timer
	vehDestroyTimer,

	// batery
	Float:vehBatery,
	
	// vida
	Float:vehHealth,

	// cor
	vehColor1,
	vehColor2,
}

new VehicleInfo[MAX_VEHICLES][vehEnumInfo];

enum idleEnum {

	idleLib[15],
	idleAnim[15],
}

stock const animPlayIdles[2][2][idleEnum] = {

	{"PLAYIDLES", "stretch"},
	{"PLAYIDLES", "time"}
};


