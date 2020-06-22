
//------------------------------------------------------------------------------


enum ConquistaEnum {
	ConquistaNome[45],
	ConquistaDesc[128],
}

//------------------------------------------------------------------------------


enum {
	Conquista_KillZombie,
	Conquista_NextLevel,
	Conquista_Level5,
	Conquista_Level10,
	Conquista_Level15,
	Conquista_Level50,
	Conquista_BattleRoyale,
	Conquista_Kill,
	Conquista_200Kill,
	Conquista_200Zombies,
	Conquista_BetaTester,
	Conquista_Admin,
	Conquista_Premium,
	Conquista_Mecanico,
	Conquista_Grupo,
	Conquista_Medico,
	Conquista_Construindo,
	Conquista_Pescador,
	Conquista_Cacador,
	Conquista_Coletando,
}

// -----------------------------------------------------------------------------

static const ConquistaInfo[][ConquistaEnum] = {
	{"Matar um zombie", 		"Desbloqueada ao matar um zombie pela primeira vez"},
	{"Progredindo", 			"Desbloqueada ao passar de nivel pela primeira vez"},
	{"Sobrevivente", 			"Desbloqueada ao alcancar o nivel 5"},
	{"Reconhecido", 			"Desbloqueada ao alcancar o nivel 10"},
	{"Experiente", 				"Desbloqueada ao alcancar o nivel 15"},
	{"Sobrevivente lendário", 	"Desbloqueada ao alcancar o nivel 50"},
	{"Ganhar o Battle Royale", 	"Desbloqueada ao vencer o modo battle royale"},
	{"Assassino", 				"Desbloqueada ao matar um jogador"},
	{"Sangue frio", 			"Desbloqueada ao matar 200 jogadores"},
	{"Predador", 				"Desbloqueada ao matar 200 zombies"},
	{"Ser um Beta-Tester", 		"Desbloqueada ao se tornar um beta tester"},
	{"Administrador", 			"Desbloqueada ao se tornar um administrador"},
	{"Jogador premium", 		"Desbloqueada ao se tornar premium"},
	{"Mecanico", 				"Desbloqueada ao arrumar completamente um veiculo"},
	{"Fazendo amigos", 			"Desbloqueada ao entrar em um grupo"},
	{"Medico", 					"Desbloqueada ao salvar alguem da morte"},
	{"Construindo", 			"Desbloqueada ao criar algo em uma base"},
	{"Pescador", 				"Desbloqueada ao pescar um peixe"},
	{"Cacador", 				"Desbloqueada ao matar um animal"},
	{"Coletando", 				"Desbloqueada ao coletar algum recurso"}
};

static PlayerConquistas[MAX_PLAYERS][sizeof (ConquistaInfo)];

//------------------------------------------------------------------------------

stock createTextsConquistas() {
	textConquista[0] = TextDrawCreate(400.000000, 119.000000, "i");
	TextDrawBackgroundColor(textConquista[0], 0);
	TextDrawFont(textConquista[0], 2);
	TextDrawLetterSize(textConquista[0], 27.640068, 12.200007);
	TextDrawColor(textConquista[0], 90);
	TextDrawSetOutline(textConquista[0], 0);
	TextDrawSetProportional(textConquista[0], 1);
	TextDrawSetShadow(textConquista[0], 1);
	TextDrawSetSelectable(textConquista[0], 0);

	textConquista[1] = TextDrawCreate(510.000000, 132.000000, ".");
	TextDrawBackgroundColor(textConquista[1], 0);
	TextDrawFont(textConquista[1], 1);
	TextDrawLetterSize(textConquista[1], 1.269999, 4.199999);
	TextDrawColor(textConquista[1], -156);
	TextDrawSetOutline(textConquista[1], 0);
	TextDrawSetProportional(textConquista[1], 1);
	TextDrawSetShadow(textConquista[1], 1);
	TextDrawSetSelectable(textConquista[1], 0);

	textConquista[2] = TextDrawCreate(513.000000, 153.000000, "z");
	TextDrawBackgroundColor(textConquista[2], 0);
	TextDrawFont(textConquista[2], 1);
	TextDrawLetterSize(textConquista[2], 0.469999, 1.299999);
	TextDrawColor(textConquista[2], 150);
	TextDrawSetOutline(textConquista[2], 0);
	TextDrawSetProportional(textConquista[2], 1);
	TextDrawSetShadow(textConquista[2], 1);
	TextDrawSetSelectable(textConquista[2], 0);

	textConquista[3] = TextDrawCreate(525.000000, 156.000000, "Conquista desbloqueada");
	TextDrawBackgroundColor(textConquista[3], 0);
	TextDrawFont(textConquista[3], 1);
	TextDrawLetterSize(textConquista[3], 0.270000, 1.000000);
	TextDrawColor(textConquista[3], -156);
	TextDrawSetOutline(textConquista[3], 0);
	TextDrawSetProportional(textConquista[3], 1);
	TextDrawSetShadow(textConquista[3], 1);
	TextDrawSetSelectable(textConquista[3], 0);
}

stock createPlayerTextsConquistas(playerid) {
	textPlayerConquista[0][playerid] = CreatePlayerTextDraw(playerid, 525.000000, 185.000000, "Descricao da conquista");
	PlayerTextDrawBackgroundColor(playerid, textPlayerConquista[0][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerConquista[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerConquista[0][playerid], 0.219999, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerConquista[0][playerid], -226);
	PlayerTextDrawSetOutline(playerid, textPlayerConquista[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerConquista[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerConquista[0][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerConquista[0][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerConquista[0][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerConquista[0][playerid], 631.000000, 0.000000);

	textPlayerConquista[1][playerid] = CreatePlayerTextDraw(playerid, 525.000000, 177.000000, "Nome da conquista");
	PlayerTextDrawBackgroundColor(playerid, textPlayerConquista[1][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerConquista[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerConquista[1][playerid], 0.239999, 0.799998);
	PlayerTextDrawColor(playerid, textPlayerConquista[1][playerid], 16777215);
	PlayerTextDrawSetOutline(playerid, textPlayerConquista[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerConquista[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerConquista[1][playerid], 1);
}

//------------------------------------------------------------------------------

stock checkPlayerConquista(playerid, conquistaid) {

	if (conquistaid < 0 || !IsPlayerConnected(playerid)) {
	    return 0;
	}
	
	if (PlayerConquistas[playerid][conquistaid]) {
	    return 0;
	}
	
	// Setar a conquista
	PlayerConquistas[playerid][conquistaid] = 1;
	
	// Efeito sonoro
	PlayerPlaySound(playerid, 40405, 0.0, 0.0, 0.0);// Ou 14407
	
	// Update nas textdraws
	PlayerTextDrawSetString(playerid, textPlayerConquista[1][playerid], ConquistaInfo[conquistaid][ConquistaNome]);
	PlayerTextDrawSetString(playerid, textPlayerConquista[0][playerid], ConquistaInfo[conquistaid][ConquistaDesc]);
	
	// Mostrar as textdraws
	showTextsConquistas(playerid);
	
	// Salvar as conquistas
	SaveConquistas(playerid);
	
	return 1;
}

//------------------------------------------------------------------------------

static stock showTextsConquistas(playerid, hidetime=5000) {

	for(new text; text < sizeof (textConquista); text++)
	    TextDrawShowForPlayer(playerid, textConquista[text]);
	    
	for(new text; text < 2; text++)
	    PlayerTextDrawShow(playerid, textPlayerConquista[text][playerid]);
	    
	SetTimerEx("hideTextsConquistas", hidetime, false, "d", playerid);
}

callback hideTextsConquistas(playerid) {

	for(new text; text < sizeof (textConquista); text++)
	    TextDrawHideForPlayer(playerid, textConquista[text]);

	for(new text; text < 2; text++)
	    PlayerTextDrawHide(playerid, textPlayerConquista[text][playerid]);
}

//------------------------------------------------------------------------------

static stock SaveConquistas(playerid) {

	new stringSave[128];
	new string[15];
	new fileAccount[188];
	
 	format(string, sizeof string, "%d", PlayerConquistas[playerid][0]);
  	strcat(stringSave, string);
	
	for(new conquista = 1; conquista != sizeof (ConquistaInfo); conquista++) {

	    format(string, sizeof string, "|%d", PlayerConquistas[playerid][conquista]);
	    strcat(stringSave, string);
	}
	
	// Salvando
	format(fileAccount, sizeof fileAccount, "UPDATE accounts SET conquistas = '%s' WHERE nome = '%s';", stringSave, getNome(playerid));
	db_query(serverDB, fileAccount);
}

//------------------------------------------------------------------------------

stock LoadConquistas(playerid) {

	new string[256],
		strCoords[sizeof (ConquistaInfo)][12];

	new fileAccount[128];
	new DBResult:returnResult;

	format(fileAccount, sizeof fileAccount, "SELECT * FROM `accounts` WHERE `nome` = '%s' LIMIT 1", getNome(playerid));

	returnResult = db_query(serverDB, fileAccount);

	if (db_num_rows(returnResult)) {
		format(string, sizeof string, sql_getstring(returnResult, "conquistas"));
	}

    split(string, strCoords, '|');

	for(new conquista; conquista != sizeof (ConquistaInfo); conquista++) {
	    PlayerConquistas[playerid][conquista] = strval(strCoords[conquista]);
	}
	
	db_free_result(returnResult);
}

//------------------------------------------------------------------------------

stock MostrarConquistas(playerid, forplayerid) {

}

CMD:achievements(playerid) return cmd_conquistas(playerid);
CMD:conquistas(playerid) {

	new string[144];
	
	stringGlobal[0] = EOS;
	
	for(new conq; conq < sizeof (ConquistaInfo); conq++) {
	
	    format(string, sizeof (string), "%s%s (%s)\n", PlayerConquistas[playerid][conq] ? ("") : ("{777777}"), ConquistaInfo[conq][ConquistaNome], ConquistaInfo[conq][ConquistaDesc]);
		strcat(stringGlobal, string);
	}
	
	ShowPlayerDialog(playerid, DIALOG_INVALID, DIALOG_STYLE_LIST, "Suas conquistas", stringGlobal, "Fechar", "");
	
	return 1;
}

//------------------------------------------------------------------------------

stock GetPlayerPastaContas(playerid) {

	new NickName[MAX_PLAYER_NAME];
	new returnPasta[75];
	
	GetPlayerName(playerid, NickName, MAX_PLAYER_NAME);
	format(returnPasta, sizeof returnPasta, pastaPlayers, NickName);
	
	return returnPasta;
}

//------------------------------------------------------------------------------

stock ResetConquistas(playerid) {

	for(new conquista; conquista != sizeof (ConquistaInfo); conquista++) {
	    PlayerConquistas[playerid][conquista] = 0;
	}
}

//------------------------------------------------------------------------------

stock showConquistas(playerid) {

}

//------------------------------------------------------------------------------

stock hideConquistas(playerid) {

}

//------------------------------------------------------------------------------





