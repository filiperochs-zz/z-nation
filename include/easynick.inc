
new playerNick[MAX_PLAYERS][MAX_PLAYER_NAME];

#define getNome(%0) playerNick[%0]

// Usando a public OnPlayerConnect para guardar o nick
public OnPlayerConnect(playerid) {

	// Pegar o nome do jogador e guardar em uma variável
	GetPlayerName(playerid, playerNick[playerid], MAX_PLAYER_NAME);
	
	// ALS Hook
	#if defined nickOnPlayerConnect
	    nickOnPlayerConnect(playerid);
	#endif
	return 1;
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect nickOnPlayerConnect
#if defined nickOnPlayerConnect
	forward nickOnPlayerConnect(playerid);
#endif

// Stocks e defines

stock nickGetPlayerName(playerid, name[], len = sizeof (name)) {

	// Pegar o nick do jogador que está guardado
	format(name, len, playerNick[playerid]);
}

stock nickSetPlayerName(playerid, const name[]) {
	// Variavel para guardar o retorno
	static returnSetName;
	// Verificar se a troca de nick foi realizada
	if ((returnSetName = SetPlayerName(playerid, name)) == 1) {
	    // Guardar o novo nick na variavel
	    format(playerNick[playerid], MAX_PLAYER_NAME, name);
	}
	// Retornar o valor
	return returnSetName;
}

// Defines
#if defined _ALS_SetPlayerName
	#undef  SetPlayerName
#else
	#define _ALS_SetPlayerName
#endif
#define SetPlayerName nickSetPlayerName
#define GetPlayerName nickGetPlayerName
