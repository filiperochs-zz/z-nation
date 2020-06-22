// FCNPC - Funções adicionais


/*
native FCNPC_CreateMovement(npcid);
native FCNPC_AddMovement(npcid, Float:x, Float:y, Float:z);
native FCNPC_PlayMovement(npcid, type=MOVE_TYPE_RUN);
*/

#include <a_samp>
#include <FCNPC>

#define MAX_MOVEMENTS_NODES  (500)
#define UPDATE_NPC_RATE      (150)

enum fcnpcEnum {

	// Velocidade do movimento
	movType,

	// Node atual
	movCur,
	
	// Total de nodes
	movNodes,

	// Posições
	Float: movX[MAX_MOVEMENTS_NODES],
	Float: movY[MAX_MOVEMENTS_NODES],
	Float: movZ[MAX_MOVEMENTS_NODES],
}
static movInfo[MAX_PLAYERS][fcnpcEnum];

stock FCNPC_CreateMovement(npcid) {

	if (!IsPlayerNPC(npcid) || FCNPC_IsDead(npcid)) return 0;

	movInfo[npcid][movCur]   = -1;
	movInfo[npcid][movNodes] = -1;
	
	for(new nodes; nodes != MAX_MOVEMENTS_NODES; nodes++) {
		movInfo[npcid][movX][nodes] = 0.0;
		movInfo[npcid][movY][nodes] = 0.0;
		movInfo[npcid][movZ][nodes] = 0.0;
	}

	return 1;
}

stock FCNPC_AddMovement(npcid, Float:x, Float:y, Float:z) {

    if (!IsPlayerNPC(npcid) || FCNPC_IsDead(npcid)) return 0;
    
    if (movInfo[npcid][movNodes] < MAX_MOVEMENTS_NODES - 1) {

	    movInfo[npcid][movNodes] ++;

		movInfo[npcid][movX][movInfo[npcid][movNodes]] = x;
		movInfo[npcid][movY][movInfo[npcid][movNodes]] = y;
		movInfo[npcid][movZ][movInfo[npcid][movNodes]] = z;
	}
    
    return 1;
}

stock FCNPC_PlayMovement(npcid, type=MOVE_TYPE_RUN) {

	if (!IsPlayerNPC(npcid) || FCNPC_IsDead(npcid)) return 0;
	
	movInfo[npcid][movCur]  = 0;
	movInfo[npcid][movType] = type;
	
	FCNPC_GoTo(npcid, movInfo[npcid][movX][0], movInfo[npcid][movY][0], movInfo[npcid][movZ][0], movInfo[npcid][movType], 4.1, 0);
	
	return 1;
}

public FCNPC_OnReachDestination(npcid) {

	movInfo[npcid][movCur] ++;

	if (movInfo[npcid][movCur] > movInfo[npcid][movNodes]) {

		#if defined FCNPC_OnMovementEnd
			FCNPC_OnMovementEnd(npcid);
		#endif
		
		return 1;
	}

	FCNPC_GoTo(npcid, movInfo[npcid][movX][movInfo[npcid][movCur]], movInfo[npcid][movY][movInfo[npcid][movCur]], movInfo[npcid][movZ][movInfo[npcid][movCur]], movInfo[npcid][movType], 4.1, 0);

	#if defined g_FCNPC_OnReachDestination
	    return g_FCNPC_OnReachDestination(npcid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_FCNPC_OnReachDestination
	#undef FCNPC_OnReachDestination
#else
	#define _ALS_FCNPC_OnReachDestination
#endif
#define FCNPC_OnReachDestination g_FCNPC_OnReachDestination
#if defined g_FCNPC_OnReachDestination
	forward g_FCNPC_OnReachDestination(npcid);
#endif

public OnGameModeInit() {

	#if defined g_FCNPC_OnReachDestination
	    return g_FCNPC_OnGameModeInit();
	#endif
	return 1;
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit g_FCNPC_OnGameModeInit
#if defined g_FCNPC_OnGameModeInit
	forward g_FCNPC_OnGameModeInit();
#endif

forward FCNPC_OnMovementEnd(npcid);
