enum enum_pData {

	// Status de login
	bool: dLogged,
	
	// Mechendo nas configs
	bool: dConfig,
	
	// Morreu ou não
	bool: dDead,
	
	// Musica ambiente
	bool: dMusic,
	
	// Pontuação em 3d
	bool: dPoints3D,
	
	// primeira pessoa
	bool: dFirstPerson,
	
	// Economia de banda
	bool: dEconomia,
	
	// Spawnado
	bool: dSpawned,
	
	// mascara de gas
	bool: dGasMask,
	
	// ingame
	bool: dReturningMenu,
	
	// Tutorial
	bool: dIntroducao,
	
	// Craftando
	bool: dCrafting,
	
	// Vendo condicoes
	bool: dCondicao,
	
	// Lanterna
	bool: dLanterna,
	
	// automatic weather
	bool: dWeather,
	
	// inconsciente
	bool: dDropped,
	
	// Beta tester
	bool: dBetaTester,

	// admin duty
	bool: dAdminDuty,
	
	//cuffed
	bool: dCuffed,
	
	// block skin
	bool: dBlockSkin,
	
	// Base protect
	bool: dBaseProtect,
	
	// downloading
	bool: dDownloading,
	
	//
	bool: dPlayerBlocked,
	
	// Resync
	bool: dResync,
	Float:dResyncPos[4],
	dResyncData[2],
	
	// Spec admin
	bool: dSpectate,
	dSpectateId,
	
	// server state
	dServerState,
	
	// Player bloqueado
	dBlockedTime,
	
	// Craft ID
	dCraftId,
	
	// Last update
	dPlayerUpdate,
	
	// Nível
	dLevel,
	
	// assist
	dAssistId,
	
	// Actor
	dActorId,
	
	// zombies follow
	dCountZombies,
	
	// timer update
	dUpdateTimer,
	
	// muted
	dMuted,
	
	// update fome sede
	dLastUpdateFome,
	
	// Last command
	dLastCommand,
	
	// Last chat
	dLastChat,
	
	// Dinheiro
	dMoney,
	
	// Base protect position
	Float:dLastBaseX,
	Float:dLastBaseY,
	Float:dLastBaseZ,
	
	// tempo de jogo
	dPlayTime,
	
	// premium
	dPremium,
	
	// xp boost
	dBoostXp,
	dBoostExpire,
	
	// daily crate
	dDailyCrate,
	
	// Quem matou
	dKillerId,
	
	// Arma que matou
	dKillerIdReason,
	
	// Iniciou novo jogo
	dNewGame,
	
	// Crates
	dCrates,
	
	// give point
	dGivePoint,
	
	// Doença
	dDoenca,
	
	// Vida
	Float:dVida,
	
	// Vida medkit
	Float:dVidaRestore,
	
	// current loot
	dCurrentLoot,
	
	// Fome
	Float:dFome,
	
	// Sede
	Float:dSede,
	
	// Coins
	dCoins,
	
	// Sangramento,
	Float:dSangramento,
	
	// Virus Zombie
	Float:dVirus,
	
	// Radiacao
	Float:dRadiacao,
	
	// Estação de radio
	Float:dRadio,
	
	// Tempo vivo
	dTempoVivo,
	
	// Mochila
	dMochila,
	
	// Ultima pos
	Float:dPos[4],
	
	// Interior,
	dInterior,
	
	// World
	dVirtual,
	
	// arma atual
	dCurrentWeapon,
	
	// Armas
	dWeapons[13],
	
	// Balas
	dAmmo[13],
	
	// health weapons
	Float:dHealth[13],
	
	// Admin
	dAdmin,
	
	// Zombies mortos
	dZombieKills,
	
	// Players mortos
	dKills,
	
	// Total de player mortos
	dTotalKills,
	
	// Morreu
	dDeaths,

	// Infecção
	dInfeccao,
	
	// Skin
	dSkin,
	dTempSkin,
	
	// Pontos
	dPoints,

	// Audio plugin
	dHandleAudio,
	
	// Coração batendo
	dHeartAudio,
	
	// save
	dLastSave,
	
	// last background
	dLastBackground,

	// 3d text
	Text3D:dPlayerText3D,

	// Idioma
	dLanguage[25],
	
	// Armor
	dArmorType,
	Float:dArmorHealth,
	
	// Helmet
	dHelmetType,
	Float:dHelmetHealth,
	
	// Acessorio
	dAccessoryModel,
	dAccessoryId,
	dAccessoryBone,
	Float:dAccessoryOffset[9],
	
// ||||||||||||||||||||||| Battle Royale |||||||||||||||||||||||||

	// Modo Battle Royale
	bool: dBattleRoyale,

	// Lobby Battle Royale
	bool: dLobby,

	// Vezes que ganhou
	dWinsBattleRoyale,

	// Matou Battle royale
	dKillsBattleRoyale,
	
	// Mortes Battle Royale
	dDeathsBattleRoyale,

	// Vezes q participou
	dTimesBattleRoyale,
}
new PlayerData[MAX_PLAYERS][enum_pData];
