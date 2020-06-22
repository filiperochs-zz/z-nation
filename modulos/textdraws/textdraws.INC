#include "../modulos/textdraws/core.inc"
#include "../modulos/textdraws/utils.inc"

const Float:reposition = 22.0;
const Float:menuposition = 15.0;
const Float:rank_repos = 38.0;

stock createServerTextDraws() {

	// Server Restart
	textServerRestart = TextDrawCreate(2.000000, 439.000000, "servidor reiniciando em: 00:00:00");
	TextDrawBackgroundColor(textServerRestart, 0);
	TextDrawFont(textServerRestart, 2);
	TextDrawLetterSize(textServerRestart, 0.159999, 0.899999);
	TextDrawColor(textServerRestart, -216);
	TextDrawSetOutline(textServerRestart, 0);
	TextDrawSetProportional(textServerRestart, 1);
	TextDrawSetShadow(textServerRestart, 1);
	TextDrawSetSelectable(textServerRestart, 0);

	// battle announce
	textBattleAnnounce = TextDrawCreate(319.000000, 247.000000, "A PARTIDA VAI COMECAR EM~n~25");
	TextDrawAlignment(textBattleAnnounce, 2);
	TextDrawBackgroundColor(textBattleAnnounce, 50);
	TextDrawFont(textBattleAnnounce, 1);
	TextDrawLetterSize(textBattleAnnounce, 0.220000, 1.099999);
	TextDrawColor(textBattleAnnounce, -44936);
	TextDrawSetOutline(textBattleAnnounce, 0);
	TextDrawSetProportional(textBattleAnnounce, 1);
	TextDrawSetShadow(textBattleAnnounce, 1);

	// Informações do player
	textBoxInfo1 = TextDrawCreate(494.000000, 20.000000, "usebox");
	TextDrawBackgroundColor(textBoxInfo1, 0);
	TextDrawFont(textBoxInfo1, 1);
	TextDrawLetterSize(textBoxInfo1, 0.500000, 11.800003);
	TextDrawColor(textBoxInfo1, 0);
	TextDrawSetOutline(textBoxInfo1, 0);
	TextDrawSetProportional(textBoxInfo1, 1);
	TextDrawSetShadow(textBoxInfo1, 1);
	TextDrawUseBox(textBoxInfo1, 1);
	TextDrawBoxColor(textBoxInfo1, 336860415);
	TextDrawTextSize(textBoxInfo1, 616.000000, 0.000000);
	TextDrawSetSelectable(textBoxInfo1, 0);

	textBoxInfo2 = TextDrawCreate(510.000000, 18.000000, "Z-Nation");
	TextDrawBackgroundColor(textBoxInfo2, 0);
	TextDrawFont(textBoxInfo2, 0);
	TextDrawLetterSize(textBoxInfo2, 0.750000, 1.900001);
	TextDrawColor(textBoxInfo2, -206);
	TextDrawSetOutline(textBoxInfo2, 0);
	TextDrawSetProportional(textBoxInfo2, 1);
	TextDrawSetShadow(textBoxInfo2, 1);
	TextDrawSetSelectable(textBoxInfo2, 0);

	textBoxInfo3 = TextDrawCreate(498.000000, 43.000000,"Itens~n~Zombies mortos~n~Players mortos~n~Tempo vivo~n~Coins~n~Dinheiro~n~~n~Arma~n~Municao~n~Dano");
	TextDrawBackgroundColor(textBoxInfo3, 0);
	TextDrawFont(textBoxInfo3, 1);
	TextDrawLetterSize(textBoxInfo3, 0.220000, 0.799999);
	TextDrawColor(textBoxInfo3, -106);
	TextDrawSetOutline(textBoxInfo3, 0);
	TextDrawSetProportional(textBoxInfo3, 1);
	TextDrawSetShadow(textBoxInfo3, 1);
	TextDrawSetSelectable(textBoxInfo3, 0);

	// Blocked account
	textBlockedAccount[0] = TextDrawCreate(296.000000, 110.000000, "mdl-1019:block");
	TextDrawBackgroundColor(textBlockedAccount[0], 255);
	TextDrawFont(textBlockedAccount[0], 4);
	TextDrawLetterSize(textBlockedAccount[0], 0.500000, 1.000000);
	TextDrawColor(textBlockedAccount[0], -80);
	TextDrawSetOutline(textBlockedAccount[0], 0);
	TextDrawSetProportional(textBlockedAccount[0], 1);
	TextDrawSetShadow(textBlockedAccount[0], 1);
	TextDrawUseBox(textBlockedAccount[0], 1);
	TextDrawBoxColor(textBlockedAccount[0], 255);
	TextDrawTextSize(textBlockedAccount[0], 194.000000, 251.000000);
	TextDrawSetSelectable(textBlockedAccount[0], 0);

	textBlockedAccount[1] = TextDrawCreate(394.000000, 285.000000, "Se voce acha que sua conta foi bloqueada injustamente, favor comparecer ao forum do servidor e postar suas contra provas.");
	TextDrawAlignment(textBlockedAccount[1], 2);
	TextDrawBackgroundColor(textBlockedAccount[1], 0);
	TextDrawFont(textBlockedAccount[1], 1);
	TextDrawLetterSize(textBlockedAccount[1], 0.180000, 0.799998);
	TextDrawColor(textBlockedAccount[1], -206);
	TextDrawSetOutline(textBlockedAccount[1], 0);
	TextDrawSetProportional(textBlockedAccount[1], 1);
	TextDrawSetShadow(textBlockedAccount[1], 1);
	TextDrawUseBox(textBlockedAccount[1], 1);
	TextDrawBoxColor(textBlockedAccount[1], 0);
	TextDrawTextSize(textBlockedAccount[1], -2.000000, 103.000000);
	TextDrawSetSelectable(textBlockedAccount[1], 0);

// CONQUISTAS
    createTextsConquistas();

// Barulho
	textBarulho = TextDrawCreate(602.000000, 293.000000, "L  R");
	TextDrawBackgroundColor(textBarulho, 0);
	TextDrawFont(textBarulho, 2);
	TextDrawLetterSize(textBarulho, 0.270000, 1.200000);
	TextDrawColor(textBarulho, -1);
	TextDrawSetOutline(textBarulho, 0);
	TextDrawSetProportional(textBarulho, 1);
	TextDrawSetShadow(textBarulho, 1);
	TextDrawSetSelectable(textBarulho, 0);

// Intro end
	textIntroEnd[0] = TextDrawCreate(318.000000, 180.000000, "Z Nation");
	TextDrawAlignment(textIntroEnd[0], 2);
	TextDrawBackgroundColor(textIntroEnd[0], 0);
	TextDrawFont(textIntroEnd[0], 2);
	TextDrawLetterSize(textIntroEnd[0], 0.699998, 2.700000);
	TextDrawColor(textIntroEnd[0], -1778384641);
	TextDrawSetOutline(textIntroEnd[0], 1);
	TextDrawSetProportional(textIntroEnd[0], 1);
	TextDrawSetSelectable(textIntroEnd[0], 0);

	textIntroEnd[1] = TextDrawCreate(318.000000, 202.000000, "DayZ - Battle Royale");
	TextDrawAlignment(textIntroEnd[1], 2);
	TextDrawBackgroundColor(textIntroEnd[1], 0);
	TextDrawFont(textIntroEnd[1], 2);
	TextDrawLetterSize(textIntroEnd[1], 0.170000, 0.999998);
	TextDrawColor(textIntroEnd[1], -1);
	TextDrawSetOutline(textIntroEnd[1], 0);
	TextDrawSetProportional(textIntroEnd[1], 1);
	TextDrawSetShadow(textIntroEnd[1], 1);
	TextDrawSetSelectable(textIntroEnd[1], 0);

// HUD
	textHud[0] = TextDrawCreate(30.000000, 334.000000, "ld_pool:ball");
	TextDrawBackgroundColor(textHud[0], 0);
	TextDrawFont(textHud[0], 4);
	TextDrawLetterSize(textHud[0], 1.000000, 0.000000);
	TextDrawColor(textHud[0], 168430335);
	TextDrawSetOutline(textHud[0], 0);
	TextDrawSetProportional(textHud[0], 1);
	TextDrawSetShadow(textHud[0], 1);
	TextDrawUseBox(textHud[0], 1);
	TextDrawBoxColor(textHud[0], 255);
	TextDrawTextSize(textHud[0], 114.000000, 97.000000);
	TextDrawSetSelectable(textHud[0], 0);

	textHud[1] = TextDrawCreate(86.000000, 351.000000, "Z");
	TextDrawAlignment(textHud[1], 2);
	TextDrawBackgroundColor(textHud[1], 0);
	TextDrawFont(textHud[1], 0);
	TextDrawLetterSize(textHud[1], 1.420000, 4.000002);
	TextDrawColor(textHud[1], 16777015);
	TextDrawSetOutline(textHud[1], 0);
	TextDrawSetProportional(textHud[1], 1);
	TextDrawSetShadow(textHud[1], 3);
	TextDrawSetSelectable(textHud[1], 0);

	textHud[2] = TextDrawCreate(86.000000, 383.000000, "nation");
	TextDrawAlignment(textHud[2], 2);
	TextDrawBackgroundColor(textHud[2], 0);
	TextDrawFont(textHud[2], 0);
	TextDrawLetterSize(textHud[2], 1.149999, 2.400002);
	TextDrawColor(textHud[2], -236);
	TextDrawSetOutline(textHud[2], 0);
	TextDrawSetProportional(textHud[2], 1);
	TextDrawSetShadow(textHud[2], 3);
	TextDrawSetSelectable(textHud[2], 0);

	// sleep bag
	spawnSleepBag[0] = TextDrawCreate(-20.000000, -20.000000, "usebox");
	TextDrawBackgroundColor(spawnSleepBag[0], 0);
	TextDrawFont(spawnSleepBag[0], 1);
	TextDrawLetterSize(spawnSleepBag[0], 0.500000, 53.000000);
	TextDrawColor(spawnSleepBag[0], 0);
	TextDrawSetOutline(spawnSleepBag[0], 0);
	TextDrawSetProportional(spawnSleepBag[0], 1);
	TextDrawSetShadow(spawnSleepBag[0], 1);
	TextDrawUseBox(spawnSleepBag[0], 1);
	TextDrawBoxColor(spawnSleepBag[0], 225);
	TextDrawTextSize(spawnSleepBag[0], 680.000000, 50.000000);
	TextDrawSetSelectable(spawnSleepBag[0], 0);

	spawnSleepBag[1] = TextDrawCreate(279.000000, 371.000000, "ld_dual:white");
	TextDrawBackgroundColor(spawnSleepBag[1], 255);
	TextDrawFont(spawnSleepBag[1], 4);
	TextDrawLetterSize(spawnSleepBag[1], 0.500000, 1.000000);
	TextDrawColor(spawnSleepBag[1], 336860415);
	TextDrawSetOutline(spawnSleepBag[1], 0);
	TextDrawSetProportional(spawnSleepBag[1], 1);
	TextDrawSetShadow(spawnSleepBag[1], 1);
	TextDrawUseBox(spawnSleepBag[1], 1);
	TextDrawBoxColor(spawnSleepBag[1], 255);
	TextDrawTextSize(spawnSleepBag[1], 80.000000, 18.000000);
	TextDrawSetSelectable(spawnSleepBag[1], 1);

	spawnSleepBag[2] = TextDrawCreate(318.000000, 375.000000, "Respawn na base");
	TextDrawAlignment(spawnSleepBag[2], 2);
	TextDrawBackgroundColor(spawnSleepBag[2], 0);
	TextDrawFont(spawnSleepBag[2], 1);
	TextDrawLetterSize(spawnSleepBag[2], 0.189999, 1.000000);
	TextDrawColor(spawnSleepBag[2], -106);
	TextDrawSetOutline(spawnSleepBag[2], 0);
	TextDrawSetProportional(spawnSleepBag[2], 1);
	TextDrawSetShadow(spawnSleepBag[2], 1);
	TextDrawSetSelectable(spawnSleepBag[2], 0);

	spawnSleepBag[3] = TextDrawCreate(19.000000, 139.000000, "mdl-1024:sanfierro");
	TextDrawBackgroundColor(spawnSleepBag[3], 255);
	TextDrawFont(spawnSleepBag[3], 4);
	TextDrawLetterSize(spawnSleepBag[3], 0.500000, 1.000000);
	TextDrawColor(spawnSleepBag[3], -1);
	TextDrawSetOutline(spawnSleepBag[3], 0);
	TextDrawSetProportional(spawnSleepBag[3], 1);
	TextDrawSetShadow(spawnSleepBag[3], 1);
	TextDrawUseBox(spawnSleepBag[3], 1);
	TextDrawBoxColor(spawnSleepBag[3], -1);
	TextDrawTextSize(spawnSleepBag[3], 150.000000, 210.000000);
	TextDrawSetSelectable(spawnSleepBag[3], 1);

	spawnSleepBag[4] = TextDrawCreate(170.000000, 139.000000, "mdl-1024:lasventuras");
	TextDrawBackgroundColor(spawnSleepBag[4], 255);
	TextDrawFont(spawnSleepBag[4], 4);
	TextDrawLetterSize(spawnSleepBag[4], 0.500000, 1.000000);
	TextDrawColor(spawnSleepBag[4], -1);
	TextDrawSetOutline(spawnSleepBag[4], 0);
	TextDrawSetProportional(spawnSleepBag[4], 1);
	TextDrawSetShadow(spawnSleepBag[4], 1);
	TextDrawUseBox(spawnSleepBag[4], 1);
	TextDrawBoxColor(spawnSleepBag[4], 255);
	TextDrawTextSize(spawnSleepBag[4], 150.000000, 210.000000);
	TextDrawSetSelectable(spawnSleepBag[4], 1);

	spawnSleepBag[5] = TextDrawCreate(321.000000, 139.000000, "mdl-1024:floresta");
	TextDrawBackgroundColor(spawnSleepBag[5], 255);
	TextDrawFont(spawnSleepBag[5], 4);
	TextDrawLetterSize(spawnSleepBag[5], 0.500000, 1.000000);
	TextDrawColor(spawnSleepBag[5], -1);
	TextDrawSetOutline(spawnSleepBag[5], 0);
	TextDrawSetProportional(spawnSleepBag[5], 1);
	TextDrawSetShadow(spawnSleepBag[5], 1);
	TextDrawUseBox(spawnSleepBag[5], 1);
	TextDrawBoxColor(spawnSleepBag[5], 255);
	TextDrawTextSize(spawnSleepBag[5], 150.000000, 210.000000);
	TextDrawSetSelectable(spawnSleepBag[5], 1);

	spawnSleepBag[6] = TextDrawCreate(472.000000, 139.000000, "mdl-1024:lossantos");
	TextDrawBackgroundColor(spawnSleepBag[6], 255);
	TextDrawFont(spawnSleepBag[6], 4);
	TextDrawLetterSize(spawnSleepBag[6], 0.500000, 1.000000);
	TextDrawColor(spawnSleepBag[6], -1);
	TextDrawSetOutline(spawnSleepBag[6], 0);
	TextDrawSetProportional(spawnSleepBag[6], 1);
	TextDrawSetShadow(spawnSleepBag[6], 1);
	TextDrawUseBox(spawnSleepBag[6], 1);
	TextDrawBoxColor(spawnSleepBag[6], 255);
	TextDrawTextSize(spawnSleepBag[6], 150.000000, 210.000000);
	TextDrawSetSelectable(spawnSleepBag[6], 1);

	// Tela de login
	textLoginScreen[0] = TextDrawCreate(-10.000000, -10.000000, "mdl-1001:background");
	TextDrawBackgroundColor(textLoginScreen[0], 255);
	TextDrawFont(textLoginScreen[0], 4);
	TextDrawLetterSize(textLoginScreen[0], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[0], -16);
	TextDrawSetOutline(textLoginScreen[0], 0);
	TextDrawSetProportional(textLoginScreen[0], 1);
	TextDrawSetShadow(textLoginScreen[0], 1);
	TextDrawUseBox(textLoginScreen[0], 1);
	TextDrawBoxColor(textLoginScreen[0], 255);
	TextDrawTextSize(textLoginScreen[0], 273.000000, 505.000000);
	TextDrawSetSelectable(textLoginScreen[0], 0);

	textLoginScreen[1] = TextDrawCreate(18.000000, 297.000000, "mdl-1001:battleroyale");
	TextDrawBackgroundColor(textLoginScreen[1], 255);
	TextDrawFont(textLoginScreen[1], 4);
	TextDrawLetterSize(textLoginScreen[1], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[1], -116);
	TextDrawSetOutline(textLoginScreen[1], 0);
	TextDrawSetProportional(textLoginScreen[1], 1);
	TextDrawSetShadow(textLoginScreen[1], 1);
	TextDrawUseBox(textLoginScreen[1], 1);
	TextDrawBoxColor(textLoginScreen[1], 255);
	TextDrawTextSize(textLoginScreen[1], 45.000000, 55.000000);
	TextDrawSetSelectable(textLoginScreen[1], 1);

	textLoginScreen[2] = TextDrawCreate(65.000000, 297.000000, "mdl-1001:skins");
	TextDrawBackgroundColor(textLoginScreen[2], 255);
	TextDrawFont(textLoginScreen[2], 4);
	TextDrawLetterSize(textLoginScreen[2], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[2], -116);
	TextDrawSetOutline(textLoginScreen[2], 0);
	TextDrawSetProportional(textLoginScreen[2], 1);
	TextDrawSetShadow(textLoginScreen[2], 1);
	TextDrawUseBox(textLoginScreen[2], 1);
	TextDrawBoxColor(textLoginScreen[2], 255);
	TextDrawTextSize(textLoginScreen[2], 45.000000, 55.000000);
	TextDrawSetSelectable(textLoginScreen[2], 1);

	textLoginScreen[3] = TextDrawCreate(112.000000, 183.000000, "mdl-1001:config");
	TextDrawBackgroundColor(textLoginScreen[3], 255);
	TextDrawFont(textLoginScreen[3], 4);
	TextDrawLetterSize(textLoginScreen[3], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[3], -116);
	TextDrawSetOutline(textLoginScreen[3], 0);
	TextDrawSetProportional(textLoginScreen[3], 1);
	TextDrawSetShadow(textLoginScreen[3], 1);
	TextDrawUseBox(textLoginScreen[3], 1);
	TextDrawBoxColor(textLoginScreen[3], 255);
	TextDrawTextSize(textLoginScreen[3], 45.000000, 55.000000);
	TextDrawSetSelectable(textLoginScreen[3], 1);

	textLoginScreen[4] = TextDrawCreate(112.000000, 240.000000, "mdl-1001:rankings");
	TextDrawBackgroundColor(textLoginScreen[4], 255);
	TextDrawFont(textLoginScreen[4], 4);
	TextDrawLetterSize(textLoginScreen[4], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[4], -116);
	TextDrawSetOutline(textLoginScreen[4], 0);
	TextDrawSetProportional(textLoginScreen[4], 1);
	TextDrawSetShadow(textLoginScreen[4], 1);
	TextDrawUseBox(textLoginScreen[4], 1);
	TextDrawBoxColor(textLoginScreen[4], 255);
	TextDrawTextSize(textLoginScreen[4], 45.000000, 55.000000);
	TextDrawSetSelectable(textLoginScreen[4], 1);

	textLoginScreen[5] = TextDrawCreate(14.000000, 51.000000, "mdl-1001:logo");
	TextDrawBackgroundColor(textLoginScreen[5], 255);
	TextDrawFont(textLoginScreen[5], 4);
	TextDrawLetterSize(textLoginScreen[5], 0.500000, 1.000000);
	TextDrawColor(textLoginScreen[5], -1);
	TextDrawSetOutline(textLoginScreen[5], 0);
	TextDrawSetProportional(textLoginScreen[5], 1);
	TextDrawSetShadow(textLoginScreen[5], 1);
	TextDrawUseBox(textLoginScreen[5], 1);
	TextDrawBoxColor(textLoginScreen[5], 255);
	TextDrawTextSize(textLoginScreen[5], 152.000000, 122.000000);
	TextDrawSetSelectable(textLoginScreen[5], 0);
	
	textChangeDSkin = TextDrawCreate(418.000000, 414.000000, "mdl-1043:changeicon");
	TextDrawBackgroundColor(textChangeDSkin, 255);
	TextDrawFont(textChangeDSkin, 4);
	TextDrawLetterSize(textChangeDSkin, 0.500000, 1.000000);
	TextDrawColor(textChangeDSkin, -106);
	TextDrawSetOutline(textChangeDSkin, 0);
	TextDrawSetProportional(textChangeDSkin, 1);
	TextDrawSetShadow(textChangeDSkin, 1);
	TextDrawUseBox(textChangeDSkin, 1);
	TextDrawBoxColor(textChangeDSkin, 255);
	TextDrawTextSize(textChangeDSkin, 23.000000, 27.000000);
	TextDrawSetSelectable(textChangeDSkin, 1);

	// admimn mode
	textAdminMode1 = TextDrawCreate(112.000000, 297.000000, "mdl-1001:admin");
	TextDrawBackgroundColor(textAdminMode1, 255);
	TextDrawFont(textAdminMode1, 4);
	TextDrawLetterSize(textAdminMode1, 0.500000, 1.000000);
	TextDrawColor(textAdminMode1, -116);
	TextDrawSetOutline(textAdminMode1, 0);
	TextDrawSetProportional(textAdminMode1, 1);
	TextDrawSetShadow(textAdminMode1, 1);
	TextDrawUseBox(textAdminMode1, 1);
	TextDrawBoxColor(textAdminMode1, 255);
	TextDrawTextSize(textAdminMode1, 45.000000, 55.000000);
	TextDrawSetSelectable(textAdminMode1, 1);

	// Tela de carregando
	
	textLoading = TextDrawCreate(-5.000000, -5.000000, "mdl-1000:background");
	TextDrawBackgroundColor(textLoading, 255);
	TextDrawFont(textLoading, 4);
	TextDrawLetterSize(textLoading, 0.500000, 1.000000);
	TextDrawColor(textLoading, -1);
	TextDrawSetOutline(textLoading, 0);
	TextDrawSetProportional(textLoading, 1);
	TextDrawSetShadow(textLoading, 1);
	TextDrawUseBox(textLoading, 1);
	TextDrawBoxColor(textLoading, 255);
	TextDrawTextSize(textLoading, 654.000000, 458.000000);
	TextDrawSetSelectable(textLoading, 0);
	
	// Pontuação do player
	textPoints[0] = TextDrawCreate(282.000000, 4.000000, "usebox");
	TextDrawBackgroundColor(textPoints[0], 0);
	TextDrawFont(textPoints[0], 1);
	TextDrawLetterSize(textPoints[0], 0.469998, 0.699997);
	TextDrawColor(textPoints[0], 0);
	TextDrawSetOutline(textPoints[0], 0);
	TextDrawSetProportional(textPoints[0], 1);
	TextDrawSetShadow(textPoints[0], 1);
	TextDrawUseBox(textPoints[0], 1);
	TextDrawBoxColor(textPoints[0], 842150655);
	TextDrawTextSize(textPoints[0], 360.000000, 0.000000);
	TextDrawSetSelectable(textPoints[0], 0);

	textPoints[1] = TextDrawCreate(368.000000, 4.000000, "usebox");
	TextDrawBackgroundColor(textPoints[1], 0);
	TextDrawFont(textPoints[1], 1);
	TextDrawLetterSize(textPoints[1], 0.469998, 0.699996);
	TextDrawColor(textPoints[1], 0);
	TextDrawSetOutline(textPoints[1], 0);
	TextDrawSetProportional(textPoints[1], 1);
	TextDrawSetShadow(textPoints[1], 1);
	TextDrawUseBox(textPoints[1], 1);
	TextDrawBoxColor(textPoints[1], -186);
	TextDrawTextSize(textPoints[1], 386.000000, 0.000000);
	TextDrawSetSelectable(textPoints[1], 0);
	
	// Configurações
	
	textConfig[0] = TextDrawCreate(315.000000, 233.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[0], 255);
	TextDrawFont(textConfig[0], 4);
	TextDrawLetterSize(textConfig[0], 0.500000, 1.000000);
	TextDrawColor(textConfig[0], -1768515946);
	TextDrawSetOutline(textConfig[0], 0);
	TextDrawSetProportional(textConfig[0], 1);
	TextDrawSetShadow(textConfig[0], 1);
	TextDrawUseBox(textConfig[0], 1);
	TextDrawBoxColor(textConfig[0], 255);
	TextDrawTextSize(textConfig[0], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[0], 1);

	textConfig[1] = TextDrawCreate(315.000000, 249.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[1], 255);
	TextDrawFont(textConfig[1], 4);
	TextDrawLetterSize(textConfig[1], 0.500000, 1.000000);
	TextDrawColor(textConfig[1], -1768515946);
	TextDrawSetOutline(textConfig[1], 0);
	TextDrawSetProportional(textConfig[1], 1);
	TextDrawSetShadow(textConfig[1], 1);
	TextDrawUseBox(textConfig[1], 1);
	TextDrawBoxColor(textConfig[1], 255);
	TextDrawTextSize(textConfig[1], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[1], 1);

	textConfig[2] = TextDrawCreate(315.000000, 265.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[2], 255);
	TextDrawFont(textConfig[2], 4);
	TextDrawLetterSize(textConfig[2], 0.500000, 1.000000);
	TextDrawColor(textConfig[2], -1768515946);
	TextDrawSetOutline(textConfig[2], 0);
	TextDrawSetProportional(textConfig[2], 1);
	TextDrawSetShadow(textConfig[2], 1);
	TextDrawUseBox(textConfig[2], 1);
	TextDrawBoxColor(textConfig[2], 255);
	TextDrawTextSize(textConfig[2], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[2], 1);

	textConfig[4] = TextDrawCreate(315.000000, 281.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[4], 255);
	TextDrawFont(textConfig[4], 4);
	TextDrawLetterSize(textConfig[4], 0.500000, 1.000000);
	TextDrawColor(textConfig[4], -1768515946);
	TextDrawSetOutline(textConfig[4], 0);
	TextDrawSetProportional(textConfig[4], 1);
	TextDrawSetShadow(textConfig[4], 1);
	TextDrawUseBox(textConfig[4], 1);
	TextDrawBoxColor(textConfig[4], 255);
	TextDrawTextSize(textConfig[4], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[4], 1);

	textConfig[5] = TextDrawCreate(315.000000, 297.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[5], 255);
	TextDrawFont(textConfig[5], 4);
	TextDrawLetterSize(textConfig[5], 0.500000, 1.000000);
	TextDrawColor(textConfig[5], -1768515946);
	TextDrawSetOutline(textConfig[5], 0);
	TextDrawSetProportional(textConfig[5], 1);
	TextDrawSetShadow(textConfig[5], 1);
	TextDrawUseBox(textConfig[5], 1);
	TextDrawBoxColor(textConfig[5], 255);
	TextDrawTextSize(textConfig[5], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[5], 1);

	textConfig[6] = TextDrawCreate(315.000000, 313.000000 - reposition, "mdl-1001:options");
	TextDrawBackgroundColor(textConfig[6], 255);
	TextDrawFont(textConfig[6], 4);
	TextDrawLetterSize(textConfig[6], 0.500000, 1.000000);
	TextDrawColor(textConfig[6], -1768515946);
	TextDrawSetOutline(textConfig[6], 0);
	TextDrawSetProportional(textConfig[6], 1);
	TextDrawSetShadow(textConfig[6], 1);
	TextDrawUseBox(textConfig[6], 1);
	TextDrawBoxColor(textConfig[6], 255);
	TextDrawTextSize(textConfig[6], 154.000000, 14.000000);
	TextDrawSetSelectable(textConfig[6], 1);

	textConfig[3] = TextDrawCreate(320.000000, 235.000000 - reposition, "Musica ambiente~n~~n~Pontuacao em 3D~n~~n~Camera em 1| pessoa~n~~n~Economia de banda~n~~n~Idioma~n~~n~Clima automatico");
	TextDrawBackgroundColor(textConfig[3], 0);
	TextDrawFont(textConfig[3], 1);
	TextDrawLetterSize(textConfig[3], 0.240000, 0.899999);
	TextDrawColor(textConfig[3], -156);
	TextDrawSetOutline(textConfig[3], 0);
	TextDrawSetProportional(textConfig[3], 1);
	TextDrawSetShadow(textConfig[3], 1);
	TextDrawSetSelectable(textConfig[3], 0);
	
	// Roleta de opções
	TextDrawEmotes[0] = TextDrawCreate(212.000000, 176.000000, "mdl-1028:actions");
	TextDrawBackgroundColor(TextDrawEmotes[0], 255);
	TextDrawFont(TextDrawEmotes[0], 4);
	TextDrawLetterSize(TextDrawEmotes[0], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[0], -206);
	TextDrawSetOutline(TextDrawEmotes[0], 0);
	TextDrawSetProportional(TextDrawEmotes[0], 1);
	TextDrawSetShadow(TextDrawEmotes[0], 1);
	TextDrawUseBox(TextDrawEmotes[0], 1);
	TextDrawBoxColor(TextDrawEmotes[0], 255);
	TextDrawTextSize(TextDrawEmotes[0], 215.000000, 238.000000);
	TextDrawSetSelectable(TextDrawEmotes[0], 0);

	TextDrawEmotes[1] = TextDrawCreate(279.000000, 197.000000, "mdl-1028:craft");
	TextDrawBackgroundColor(TextDrawEmotes[1], 255);
	TextDrawFont(TextDrawEmotes[1], 4);
	TextDrawLetterSize(TextDrawEmotes[1], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[1], -106);
	TextDrawSetOutline(TextDrawEmotes[1], 0);
	TextDrawSetProportional(TextDrawEmotes[1], 1);
	TextDrawSetShadow(TextDrawEmotes[1], 1);
	TextDrawUseBox(TextDrawEmotes[1], 1);
	TextDrawBoxColor(TextDrawEmotes[1], 255);
	TextDrawTextSize(TextDrawEmotes[1], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[1], 1);

	TextDrawEmotes[2] = TextDrawCreate(279.000000, 369.000000, "mdl-1028:dropall");
	TextDrawBackgroundColor(TextDrawEmotes[2], 255);
	TextDrawFont(TextDrawEmotes[2], 4);
	TextDrawLetterSize(TextDrawEmotes[2], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[2], -106);
	TextDrawSetOutline(TextDrawEmotes[2], 0);
	TextDrawSetProportional(TextDrawEmotes[2], 1);
	TextDrawSetShadow(TextDrawEmotes[2], 1);
	TextDrawUseBox(TextDrawEmotes[2], 1);
	TextDrawBoxColor(TextDrawEmotes[2], 255);
	TextDrawTextSize(TextDrawEmotes[2], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[2], 1);

	TextDrawEmotes[3] = TextDrawCreate(222.000000, 284.000000, "mdl-1028:sentar");
	TextDrawBackgroundColor(TextDrawEmotes[3], 255);
	TextDrawFont(TextDrawEmotes[3], 4);
	TextDrawLetterSize(TextDrawEmotes[3], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[3], -106);
	TextDrawSetOutline(TextDrawEmotes[3], 0);
	TextDrawSetProportional(TextDrawEmotes[3], 1);
	TextDrawSetShadow(TextDrawEmotes[3], 1);
	TextDrawUseBox(TextDrawEmotes[3], 1);
	TextDrawBoxColor(TextDrawEmotes[3], 255);
	TextDrawTextSize(TextDrawEmotes[3], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[3], 1);

	TextDrawEmotes[4] = TextDrawCreate(341.000000, 284.000000, "mdl-1028:handsup");
	TextDrawBackgroundColor(TextDrawEmotes[4], 255);
	TextDrawFont(TextDrawEmotes[4], 4);
	TextDrawLetterSize(TextDrawEmotes[4], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[4], -106);
	TextDrawSetOutline(TextDrawEmotes[4], 0);
	TextDrawSetProportional(TextDrawEmotes[4], 1);
	TextDrawSetShadow(TextDrawEmotes[4], 1);
	TextDrawUseBox(TextDrawEmotes[4], 1);
	TextDrawBoxColor(TextDrawEmotes[4], 255);
	TextDrawTextSize(TextDrawEmotes[4], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[4], 1);

	TextDrawEmotes[5] = TextDrawCreate(238.000000, 236.000000, "mdl-1028:salute");
	TextDrawBackgroundColor(TextDrawEmotes[5], 255);
	TextDrawFont(TextDrawEmotes[5], 4);
	TextDrawLetterSize(TextDrawEmotes[5], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[5], -106);
	TextDrawSetOutline(TextDrawEmotes[5], 0);
	TextDrawSetProportional(TextDrawEmotes[5], 1);
	TextDrawSetShadow(TextDrawEmotes[5], 1);
	TextDrawUseBox(TextDrawEmotes[5], 1);
	TextDrawBoxColor(TextDrawEmotes[5], 255);
	TextDrawTextSize(TextDrawEmotes[5], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[5], 1);

	TextDrawEmotes[6] = TextDrawCreate(325.000000, 236.000000, "mdl-1028:assobiar");
	TextDrawBackgroundColor(TextDrawEmotes[6], 255);
	TextDrawFont(TextDrawEmotes[6], 4);
	TextDrawLetterSize(TextDrawEmotes[6], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[6], -106);
	TextDrawSetOutline(TextDrawEmotes[6], 0);
	TextDrawSetProportional(TextDrawEmotes[6], 1);
	TextDrawSetShadow(TextDrawEmotes[6], 1);
	TextDrawUseBox(TextDrawEmotes[6], 1);
	TextDrawBoxColor(TextDrawEmotes[6], 255);
	TextDrawTextSize(TextDrawEmotes[6], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[6], 1);

	TextDrawEmotes[7] = TextDrawCreate(238.000000, 333.000000, "mdl-1028:chorar");
	TextDrawBackgroundColor(TextDrawEmotes[7], 255);
	TextDrawFont(TextDrawEmotes[7], 4);
	TextDrawLetterSize(TextDrawEmotes[7], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[7], -106);
	TextDrawSetOutline(TextDrawEmotes[7], 0);
	TextDrawSetProportional(TextDrawEmotes[7], 1);
	TextDrawSetShadow(TextDrawEmotes[7], 1);
	TextDrawUseBox(TextDrawEmotes[7], 1);
	TextDrawBoxColor(TextDrawEmotes[7], 255);
	TextDrawTextSize(TextDrawEmotes[7], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[7], 1);

	TextDrawEmotes[8] = TextDrawCreate(325.000000, 333.000000, "mdl-1028:dancar");
	TextDrawBackgroundColor(TextDrawEmotes[8], 255);
	TextDrawFont(TextDrawEmotes[8], 4);
	TextDrawLetterSize(TextDrawEmotes[8], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[8], -106);
	TextDrawSetOutline(TextDrawEmotes[8], 0);
	TextDrawSetProportional(TextDrawEmotes[8], 1);
	TextDrawSetShadow(TextDrawEmotes[8], 1);
	TextDrawUseBox(TextDrawEmotes[8], 1);
	TextDrawBoxColor(TextDrawEmotes[8], 255);
	TextDrawTextSize(TextDrawEmotes[8], 74.000000, 22.000000);
	TextDrawSetSelectable(TextDrawEmotes[8], 1);

	TextDrawEmotes[9] = TextDrawCreate(306.000000, 280.000000, "mdl-1028:fechar");
	TextDrawBackgroundColor(TextDrawEmotes[9], 255);
	TextDrawFont(TextDrawEmotes[9], 4);
	TextDrawLetterSize(TextDrawEmotes[9], 0.500000, 1.000000);
	TextDrawColor(TextDrawEmotes[9], -1761607756);
	TextDrawSetOutline(TextDrawEmotes[9], 0);
	TextDrawSetProportional(TextDrawEmotes[9], 1);
	TextDrawSetShadow(TextDrawEmotes[9], 1);
	TextDrawUseBox(TextDrawEmotes[9], 1);
	TextDrawBoxColor(TextDrawEmotes[9], 255);
	TextDrawTextSize(TextDrawEmotes[9], 25.000000, 29.000000);
	TextDrawSetSelectable(TextDrawEmotes[9], 1);
	
	// Necessidades e vida
	textBaseHud = TextDrawCreate(481.000000, 376.000000, "mdl-1019:hud");
	TextDrawBackgroundColor(textBaseHud, 255);
	TextDrawFont(textBaseHud, 4);
	TextDrawLetterSize(textBaseHud, 0.500000, 1.000000);
	TextDrawColor(textBaseHud, -106);
	TextDrawSetOutline(textBaseHud, 0);
	TextDrawSetProportional(textBaseHud, 1);
	TextDrawSetShadow(textBaseHud, 1);
	TextDrawUseBox(textBaseHud, 1);
	TextDrawBoxColor(textBaseHud, 255);
	TextDrawTextSize(textBaseHud, 140.000000, 65.000000);
	TextDrawSetSelectable(textBaseHud, 0);
	
// Mapa
	textMap[0] = TextDrawCreate(150.000000, 136.000000, "usebox");
	TextDrawBackgroundColor(textMap[0], 0);
	TextDrawFont(textMap[0], 1);
	TextDrawLetterSize(textMap[0], 0.500000, 34.699989);
	TextDrawColor(textMap[0], 0);
	TextDrawSetOutline(textMap[0], 0);
	TextDrawSetProportional(textMap[0], 1);
	TextDrawSetShadow(textMap[0], 1);
	TextDrawUseBox(textMap[0], 1);
	TextDrawBoxColor(textMap[0], 120);
	TextDrawTextSize(textMap[0], 470.000000, 20.000000);
	TextDrawSetSelectable(textMap[0], 0);

	textMap[1] = TextDrawCreate(161.000000, 145.000000, "samaps:gtasamapbit1");
	TextDrawBackgroundColor(textMap[1], 255);
	TextDrawFont(textMap[1], 4);
	TextDrawLetterSize(textMap[1], 0.500000, 1.000000);
	TextDrawColor(textMap[1], -1);
	TextDrawSetOutline(textMap[1], 0);
	TextDrawSetProportional(textMap[1], 1);
	TextDrawSetShadow(textMap[1], 1);
	TextDrawUseBox(textMap[1], 1);
	TextDrawBoxColor(textMap[1], 255);
	TextDrawTextSize(textMap[1], 149.000000, 149.000000);
	TextDrawSetSelectable(textMap[1], 0);

	textMap[2] = TextDrawCreate(310.000000, 145.000000, "samaps:gtasamapbit2");
	TextDrawBackgroundColor(textMap[2], 255);
	TextDrawFont(textMap[2], 4);
	TextDrawLetterSize(textMap[2], 0.500000, 1.000000);
	TextDrawColor(textMap[2], -1);
	TextDrawSetOutline(textMap[2], 0);
	TextDrawSetProportional(textMap[2], 1);
	TextDrawSetShadow(textMap[2], 1);
	TextDrawUseBox(textMap[2], 1);
	TextDrawBoxColor(textMap[2], 255);
	TextDrawTextSize(textMap[2], 149.000000, 149.000000);
	TextDrawSetSelectable(textMap[2], 0);

	textMap[3] = TextDrawCreate(161.000000, 294.000000, "samaps:gtasamapbit3");
	TextDrawBackgroundColor(textMap[3], 255);
	TextDrawFont(textMap[3], 4);
	TextDrawLetterSize(textMap[3], 0.500000, 1.000000);
	TextDrawColor(textMap[3], -1);
	TextDrawSetOutline(textMap[3], 0);
	TextDrawSetProportional(textMap[3], 1);
	TextDrawSetShadow(textMap[3], 1);
	TextDrawUseBox(textMap[3], 1);
	TextDrawBoxColor(textMap[3], 255);
	TextDrawTextSize(textMap[3], 149.000000, 149.000000);
	TextDrawSetSelectable(textMap[3], 0);

	textMap[4] = TextDrawCreate(310.000000, 294.000000, "samaps:gtasamapbit4");
	TextDrawBackgroundColor(textMap[4], 255);
	TextDrawFont(textMap[4], 4);
	TextDrawLetterSize(textMap[4], 0.500000, 1.000000);
	TextDrawColor(textMap[4], -1);
	TextDrawSetOutline(textMap[4], 0);
	TextDrawSetProportional(textMap[4], 1);
	TextDrawSetShadow(textMap[4], 1);
	TextDrawUseBox(textMap[4], 1);
	TextDrawBoxColor(textMap[4], 255);
	TextDrawTextSize(textMap[4], 149.000000, 149.000000);
	TextDrawSetSelectable(textMap[4], 0);

	textMap[5] = TextDrawCreate(161.000000, 138.000000, "A        B        C        D        E        F        G        H        I        J        K        L");
	TextDrawBackgroundColor(textMap[5], 0);
	TextDrawFont(textMap[5], 2);
	TextDrawLetterSize(textMap[5], 0.219999, 0.699998);
	TextDrawColor(textMap[5], -106);
	TextDrawSetOutline(textMap[5], 0);
	TextDrawSetProportional(textMap[5], 1);
	TextDrawSetShadow(textMap[5], 1);
	TextDrawSetSelectable(textMap[5], 0);

	textMap[6] = TextDrawCreate(161.000000, 442.000000, "A        B        C        D        E        F        G        H        I        J        K        L");
	TextDrawBackgroundColor(textMap[6], 0);
	TextDrawFont(textMap[6], 2);
	TextDrawLetterSize(textMap[6], 0.219999, 0.699998);
	TextDrawColor(textMap[6], -106);
	TextDrawSetOutline(textMap[6], 0);
	TextDrawSetProportional(textMap[6], 1);
	TextDrawSetShadow(textMap[6], 1);
	TextDrawSetSelectable(textMap[6], 0);

	textMap[7] = TextDrawCreate(158.000000, 143.000000, "1~n~~n~~n~2~n~~n~~n~3~n~~n~~n~4~n~~n~~n~5~n~~n~~n~6~n~~n~~n~7~n~~n~~n~8~n~~n~~n~9~n~~n~~n~10~n~~n~~n~11~n~~n~~n~12~n~~n~~n~13~n~");
	TextDrawAlignment(textMap[7], 3);
	TextDrawBackgroundColor(textMap[7], 0);
	TextDrawFont(textMap[7], 2);
	TextDrawLetterSize(textMap[7], 0.200000, 0.899999);
	TextDrawColor(textMap[7], -106);
	TextDrawSetOutline(textMap[7], 0);
	TextDrawSetProportional(textMap[7], 1);
	TextDrawSetShadow(textMap[7], 1);
	TextDrawSetSelectable(textMap[7], 0);

	textMap[8] = TextDrawCreate(460.000000, 143.000000, "1~n~~n~~n~2~n~~n~~n~3~n~~n~~n~4~n~~n~~n~5~n~~n~~n~6~n~~n~~n~7~n~~n~~n~8~n~~n~~n~9~n~~n~~n~10~n~~n~~n~11~n~~n~~n~12~n~~n~~n~13~n~");
	TextDrawBackgroundColor(textMap[8], 0);
	TextDrawFont(textMap[8], 2);
	TextDrawLetterSize(textMap[8], 0.200000, 0.899999);
	TextDrawColor(textMap[8], -106);
	TextDrawSetOutline(textMap[8], 0);
	TextDrawSetProportional(textMap[8], 1);
	TextDrawSetShadow(textMap[8], 1);
	TextDrawSetSelectable(textMap[8], 0);
	
	textMap[9] = TextDrawCreate(307.000000, 146.000000, "N~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~S");
	TextDrawBackgroundColor(textMap[9], 0);
	TextDrawFont(textMap[9], 1);
	TextDrawLetterSize(textMap[9], 0.399999, 1.299998);
	TextDrawColor(textMap[9], 16777080);
	TextDrawSetOutline(textMap[9], 0);
	TextDrawSetProportional(textMap[9], 1);
	TextDrawSetShadow(textMap[9], 1);
	TextDrawSetSelectable(textMap[9], 0);

	textMap[10] = TextDrawCreate(164.000000, 287.000000, "W                                                E");
	TextDrawBackgroundColor(textMap[10], 0);
	TextDrawFont(textMap[10], 1);
	TextDrawLetterSize(textMap[10], 0.379999, 1.299998);
	TextDrawColor(textMap[10], 16777080);
	TextDrawSetOutline(textMap[10], 0);
	TextDrawSetProportional(textMap[10], 1);
	TextDrawSetShadow(textMap[10], 1);
	TextDrawSetSelectable(textMap[10], 0);
	
	// SHOP COINS
	textShopCoins[0] = TextDrawCreate(316.000000, 134.000000, "ld_drv:ribbw");
	TextDrawBackgroundColor(textShopCoins[0], 255);
	TextDrawFont(textShopCoins[0], 4);
	TextDrawLetterSize(textShopCoins[0], 0.500000, 1.399999);
	TextDrawColor(textShopCoins[0], 1684301055);
	TextDrawSetOutline(textShopCoins[0], 0);
	TextDrawSetProportional(textShopCoins[0], 1);
	TextDrawSetShadow(textShopCoins[0], 1);
	TextDrawUseBox(textShopCoins[0], 1);
	TextDrawBoxColor(textShopCoins[0], 255);
	TextDrawTextSize(textShopCoins[0], 239.000000, 267.000000);
	TextDrawSetSelectable(textShopCoins[0], 0);

	textShopCoins[1] = TextDrawCreate(263.000000, 159.000000, "Vendedor");
	TextDrawBackgroundColor(textShopCoins[1], 0);
	TextDrawFont(textShopCoins[1], 0);
	TextDrawLetterSize(textShopCoins[1], 1.059999, 2.499998);
	TextDrawColor(textShopCoins[1], -206);
	TextDrawSetOutline(textShopCoins[1], 0);
	TextDrawSetProportional(textShopCoins[1], 1);
	TextDrawSetShadow(textShopCoins[1], 1);
	TextDrawSetSelectable(textShopCoins[1], 0);

	textShopCoins[2] = TextDrawCreate(324.000000, 134.000000, "ld_drv:ribbw");
	TextDrawBackgroundColor(textShopCoins[2], 255);
	TextDrawFont(textShopCoins[2], 4);
	TextDrawLetterSize(textShopCoins[2], 0.500000, 1.399999);
	TextDrawColor(textShopCoins[2], 1684301055);
	TextDrawSetOutline(textShopCoins[2], 0);
	TextDrawSetProportional(textShopCoins[2], 1);
	TextDrawSetShadow(textShopCoins[2], 1);
	TextDrawUseBox(textShopCoins[2], 1);
	TextDrawBoxColor(textShopCoins[2], 255);
	TextDrawTextSize(textShopCoins[2], -242.000000, 267.000000);
	TextDrawSetSelectable(textShopCoins[2], 0);

	textShopCoins[3] = TextDrawCreate(181.000000, 263.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[3], 255);
	TextDrawFont(textShopCoins[3], 4);
	TextDrawLetterSize(textShopCoins[3], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[3], 2021161215);
	TextDrawSetOutline(textShopCoins[3], 0);
	TextDrawSetProportional(textShopCoins[3], 1);
	TextDrawSetShadow(textShopCoins[3], 1);
	TextDrawUseBox(textShopCoins[3], 1);
	TextDrawBoxColor(textShopCoins[3], 255);
	TextDrawTextSize(textShopCoins[3], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[3], 1);

	textShopCoins[4] = TextDrawCreate(291.000000, 263.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[4], 255);
	TextDrawFont(textShopCoins[4], 4);
	TextDrawLetterSize(textShopCoins[4], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[4], 2021161215);
	TextDrawSetOutline(textShopCoins[4], 0);
	TextDrawSetProportional(textShopCoins[4], 1);
	TextDrawSetShadow(textShopCoins[4], 1);
	TextDrawUseBox(textShopCoins[4], 1);
	TextDrawBoxColor(textShopCoins[4], 255);
	TextDrawTextSize(textShopCoins[4], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[4], 1);

	textShopCoins[5] = TextDrawCreate(402.000000, 263.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[5], 255);
	TextDrawFont(textShopCoins[5], 4);
	TextDrawLetterSize(textShopCoins[5], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[5], 2021161215);
	TextDrawSetOutline(textShopCoins[5], 0);
	TextDrawSetProportional(textShopCoins[5], 1);
	TextDrawSetShadow(textShopCoins[5], 1);
	TextDrawUseBox(textShopCoins[5], 1);
	TextDrawBoxColor(textShopCoins[5], 255);
	TextDrawTextSize(textShopCoins[5], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[5], 1);

	textShopCoins[6] = TextDrawCreate(182.000000, 357.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[6], 255);
	TextDrawFont(textShopCoins[6], 4);
	TextDrawLetterSize(textShopCoins[6], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[6], 2021161215);
	TextDrawSetOutline(textShopCoins[6], 0);
	TextDrawSetProportional(textShopCoins[6], 1);
	TextDrawSetShadow(textShopCoins[6], 1);
	TextDrawUseBox(textShopCoins[6], 1);
	TextDrawBoxColor(textShopCoins[6], 255);
	TextDrawTextSize(textShopCoins[6], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[6], 1);

	textShopCoins[7] = TextDrawCreate(291.000000, 357.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[7], 255);
	TextDrawFont(textShopCoins[7], 4);
	TextDrawLetterSize(textShopCoins[7], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[7], 2021161215);
	TextDrawSetOutline(textShopCoins[7], 0);
	TextDrawSetProportional(textShopCoins[7], 1);
	TextDrawSetShadow(textShopCoins[7], 1);
	TextDrawUseBox(textShopCoins[7], 1);
	TextDrawBoxColor(textShopCoins[7], 255);
	TextDrawTextSize(textShopCoins[7], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[7], 1);

	textShopCoins[8] = TextDrawCreate(402.000000, 357.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[8], 255);
	TextDrawFont(textShopCoins[8], 4);
	TextDrawLetterSize(textShopCoins[8], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[8], 2021161215);
	TextDrawSetOutline(textShopCoins[8], 0);
	TextDrawSetProportional(textShopCoins[8], 1);
	TextDrawSetShadow(textShopCoins[8], 1);
	TextDrawUseBox(textShopCoins[8], 1);
	TextDrawBoxColor(textShopCoins[8], 255);
	TextDrawTextSize(textShopCoins[8], 52.000000, 13.000000);
	TextDrawSetSelectable(textShopCoins[8], 1);

	textShopCoins[9] = TextDrawCreate(136.000000, 259.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[9], 255);
	TextDrawFont(textShopCoins[9], 4);
	TextDrawLetterSize(textShopCoins[9], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[9], 1684301055);
	TextDrawSetOutline(textShopCoins[9], 0);
	TextDrawSetProportional(textShopCoins[9], 1);
	TextDrawSetShadow(textShopCoins[9], 1);
	TextDrawUseBox(textShopCoins[9], 1);
	TextDrawBoxColor(textShopCoins[9], 255);
	TextDrawTextSize(textShopCoins[9], 23.000000, 31.000000);
	TextDrawSetSelectable(textShopCoins[9], 1);

	textShopCoins[10] = TextDrawCreate(478.000000, 259.000000, "ld_dual:white");
	TextDrawBackgroundColor(textShopCoins[10], 255);
	TextDrawFont(textShopCoins[10], 4);
	TextDrawLetterSize(textShopCoins[10], 0.500000, 1.000000);
	TextDrawColor(textShopCoins[10], 1684301055);
	TextDrawSetOutline(textShopCoins[10], 0);
	TextDrawSetProportional(textShopCoins[10], 1);
	TextDrawSetShadow(textShopCoins[10], 1);
	TextDrawUseBox(textShopCoins[10], 1);
	TextDrawBoxColor(textShopCoins[10], 255);
	TextDrawTextSize(textShopCoins[10], 23.000000, 31.000000);
	TextDrawSetSelectable(textShopCoins[10], 1);

	textShopCoins[11] = TextDrawCreate(139.000000, 267.000000, "~<~                                                                                            ~>~");
	TextDrawBackgroundColor(textShopCoins[11], 0);
	TextDrawFont(textShopCoins[11], 2);
	TextDrawLetterSize(textShopCoins[11], 0.300000, 1.399999);
	TextDrawColor(textShopCoins[11], 1684300900);
	TextDrawSetOutline(textShopCoins[11], 0);
	TextDrawSetProportional(textShopCoins[11], 1);
	TextDrawSetShadow(textShopCoins[11], 1);
	TextDrawSetSelectable(textShopCoins[11], 0);

	textShopCoins[12] = TextDrawCreate(471.000000, 163.000000, "X");
	TextDrawBackgroundColor(textShopCoins[12], 0);
	TextDrawFont(textShopCoins[12], 1);
	TextDrawLetterSize(textShopCoins[12], 0.490000, 1.199998);
	TextDrawColor(textShopCoins[12], -56);
	TextDrawSetOutline(textShopCoins[12], 0);
	TextDrawSetProportional(textShopCoins[12], 1);
	TextDrawSetShadow(textShopCoins[12], 1);
	TextDrawUseBox(textShopCoins[12], 1);
	TextDrawBoxColor(textShopCoins[12], 50);
	TextDrawTextSize(textShopCoins[12], 484.000000, 15.000000);
	TextDrawSetSelectable(textShopCoins[12], 1);

	// Ranks
	textServerRanks[0] = TextDrawCreate(-10.000000, -10.000000, "usebox");
	TextDrawBackgroundColor(textServerRanks[0], 0);
	TextDrawFont(textServerRanks[0], 1);
	TextDrawLetterSize(textServerRanks[0], 0.500000, 53.400001);
	TextDrawColor(textServerRanks[0], 0);
	TextDrawSetOutline(textServerRanks[0], 0);
	TextDrawSetProportional(textServerRanks[0], 1);
	TextDrawSetShadow(textServerRanks[0], 1);
	TextDrawUseBox(textServerRanks[0], 1);
	TextDrawBoxColor(textServerRanks[0], 200);
	TextDrawTextSize(textServerRanks[0], 675.000000, 0.000000);
	TextDrawSetSelectable(textServerRanks[0], 0);

	textServerRanks[1] = TextDrawCreate(218.000000 + rank_repos, 191.000000, "usebox");
	TextDrawBackgroundColor(textServerRanks[1], 0);
	TextDrawFont(textServerRanks[1], 1);
	TextDrawLetterSize(textServerRanks[1], 0.500000, -0.099997);
	TextDrawColor(textServerRanks[1], 0);
	TextDrawSetOutline(textServerRanks[1], 0);
	TextDrawSetProportional(textServerRanks[1], 1);
	TextDrawSetShadow(textServerRanks[1], 1);
	TextDrawUseBox(textServerRanks[1], 1);
	TextDrawBoxColor(textServerRanks[1], -236);
	TextDrawTextSize(textServerRanks[1], 448.000000 + rank_repos, 0.000000);
	TextDrawSetSelectable(textServerRanks[1], 0);

	textServerRanks[2] = TextDrawCreate(360.000000 + rank_repos, 195.000000, "usebox");
	TextDrawBackgroundColor(textServerRanks[2], 0);
	TextDrawFont(textServerRanks[2], 1);
	TextDrawLetterSize(textServerRanks[2], 0.500000, 18.300003);
	TextDrawColor(textServerRanks[2], 0);
	TextDrawSetOutline(textServerRanks[2], 0);
	TextDrawSetProportional(textServerRanks[2], 1);
	TextDrawSetShadow(textServerRanks[2], 1);
	TextDrawUseBox(textServerRanks[2], 1);
	TextDrawBoxColor(textServerRanks[2], -236);
	TextDrawTextSize(textServerRanks[2], 359.000000 + rank_repos, 0.000000);
	TextDrawSetSelectable(textServerRanks[2], 0);

	textServerRanks[3] = TextDrawCreate(324.000000 + rank_repos, 168.000000, "ld_beat:left");
	TextDrawBackgroundColor(textServerRanks[3], 255);
	TextDrawFont(textServerRanks[3], 4);
	TextDrawLetterSize(textServerRanks[3], 0.500000, 1.000000);
	TextDrawColor(textServerRanks[3], -156);
	TextDrawSetOutline(textServerRanks[3], 0);
	TextDrawSetProportional(textServerRanks[3], 1);
	TextDrawSetShadow(textServerRanks[3], 1);
	TextDrawUseBox(textServerRanks[3], 1);
	TextDrawBoxColor(textServerRanks[3], 255);
	TextDrawTextSize(textServerRanks[3], 9.000000, 10.000000);
	TextDrawSetSelectable(textServerRanks[3], 1);

	textServerRanks[4] = TextDrawCreate(437.000000 + rank_repos, 168.000000, "ld_beat:right");
	TextDrawBackgroundColor(textServerRanks[4], 255);
	TextDrawFont(textServerRanks[4], 4);
	TextDrawLetterSize(textServerRanks[4], 0.500000, 1.000000);
	TextDrawColor(textServerRanks[4], -156);
	TextDrawSetOutline(textServerRanks[4], 0);
	TextDrawSetProportional(textServerRanks[4], 1);
	TextDrawSetShadow(textServerRanks[4], 1);
	TextDrawUseBox(textServerRanks[4], 1);
	TextDrawBoxColor(textServerRanks[4], 255);
	TextDrawTextSize(textServerRanks[4], 9.000000, 10.000000);
	TextDrawSetSelectable(textServerRanks[4], 1);

	textServerRanks[5] = TextDrawCreate(466.000000 + rank_repos, 163.000000, "x");
	TextDrawBackgroundColor(textServerRanks[5], 0);
	TextDrawFont(textServerRanks[5], 2);
	TextDrawLetterSize(textServerRanks[5], 0.259999, 1.000000);
	TextDrawColor(textServerRanks[5], -156);
	TextDrawSetOutline(textServerRanks[5], 0);
	TextDrawSetProportional(textServerRanks[5], 1);
	TextDrawSetShadow(textServerRanks[5], 1);
	TextDrawUseBox(textServerRanks[5], 1);
	TextDrawBoxColor(textServerRanks[5], 842150655);
	TextDrawTextSize(textServerRanks[5], 473.000000 + rank_repos, 15.000000);
	TextDrawSetSelectable(textServerRanks[5], 1);

	textServerRanks[6] = TextDrawCreate(209.000000 + rank_repos, 196.000000, "-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~-----~n~");
	TextDrawBackgroundColor(textServerRanks[6], 0);
	TextDrawFont(textServerRanks[6], 1);
	TextDrawLetterSize(textServerRanks[6], 3.509999, 0.899999);
	TextDrawColor(textServerRanks[6], -251);
	TextDrawSetOutline(textServerRanks[6], 0);
	TextDrawSetProportional(textServerRanks[6], 1);
	TextDrawSetShadow(textServerRanks[6], 1);
	TextDrawSetSelectable(textServerRanks[6], 0);
	
	// Battle Royale
	textBattleRoyale = TextDrawCreate(555.000000, 5.000000, "Jogadores preparados: 0");
	TextDrawAlignment(textBattleRoyale, 2);
	TextDrawBackgroundColor(textBattleRoyale, 0);
	TextDrawFont(textBattleRoyale, 1);
	TextDrawLetterSize(textBattleRoyale, 0.219999, 0.899997);
	TextDrawColor(textBattleRoyale, -106);
	TextDrawSetOutline(textBattleRoyale, 1);
	TextDrawSetProportional(textBattleRoyale, 1);
	TextDrawUseBox(textBattleRoyale, 1);
	TextDrawBoxColor(textBattleRoyale, 336860415);
	TextDrawTextSize(textBattleRoyale, 616.000000, 122.000000);
	TextDrawSetSelectable(textBattleRoyale, 0);
	
	// Grupos
	textGroups[0] = TextDrawCreate(124.000000, 133.000000, "usebox");
	TextDrawBackgroundColor(textGroups[0], 0);
	TextDrawFont(textGroups[0], 1);
	TextDrawLetterSize(textGroups[0], 0.500000, 22.499998);
	TextDrawColor(textGroups[0], 0);
	TextDrawSetOutline(textGroups[0], 0);
	TextDrawSetProportional(textGroups[0], 1);
	TextDrawSetShadow(textGroups[0], 1);
	TextDrawUseBox(textGroups[0], 1);
	TextDrawBoxColor(textGroups[0], 336860360);
	TextDrawTextSize(textGroups[0], 511.000000, 0.000000);
	TextDrawSetSelectable(textGroups[0], 0);

	textGroups[1] = TextDrawCreate(141.000000, 148.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[1], 255);
	TextDrawFont(textGroups[1], 4);
	TextDrawLetterSize(textGroups[1], 0.500000, 1.000000);
	TextDrawColor(textGroups[1], 673720575);
	TextDrawSetOutline(textGroups[1], 0);
	TextDrawSetProportional(textGroups[1], 1);
	TextDrawSetShadow(textGroups[1], 1);
	TextDrawUseBox(textGroups[1], 1);
	TextDrawBoxColor(textGroups[1], 168430335);
	TextDrawTextSize(textGroups[1], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[1], 1);

	textGroups[2] = TextDrawCreate(141.000000, 162.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[2], 255);
	TextDrawFont(textGroups[2], 4);
	TextDrawLetterSize(textGroups[2], 0.500000, 1.000000);
	TextDrawColor(textGroups[2], 673720575);
	TextDrawSetOutline(textGroups[2], 0);
	TextDrawSetProportional(textGroups[2], 1);
	TextDrawSetShadow(textGroups[2], 1);
	TextDrawUseBox(textGroups[2], 1);
	TextDrawBoxColor(textGroups[2], 168430335);
	TextDrawTextSize(textGroups[2], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[2], 1);

	textGroups[3] = TextDrawCreate(141.000000, 176.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[3], 255);
	TextDrawFont(textGroups[3], 4);
	TextDrawLetterSize(textGroups[3], 0.500000, 1.000000);
	TextDrawColor(textGroups[3], 673720575);
	TextDrawSetOutline(textGroups[3], 0);
	TextDrawSetProportional(textGroups[3], 1);
	TextDrawSetShadow(textGroups[3], 1);
	TextDrawUseBox(textGroups[3], 1);
	TextDrawBoxColor(textGroups[3], 168430335);
	TextDrawTextSize(textGroups[3], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[3], 1);

	textGroups[4] = TextDrawCreate(141.000000, 190.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[4], 255);
	TextDrawFont(textGroups[4], 4);
	TextDrawLetterSize(textGroups[4], 0.500000, 1.000000);
	TextDrawColor(textGroups[4], 673720575);
	TextDrawSetOutline(textGroups[4], 0);
	TextDrawSetProportional(textGroups[4], 1);
	TextDrawSetShadow(textGroups[4], 1);
	TextDrawUseBox(textGroups[4], 1);
	TextDrawBoxColor(textGroups[4], 168430335);
	TextDrawTextSize(textGroups[4], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[4], 1);

	textGroups[5] = TextDrawCreate(141.000000, 204.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[5], 255);
	TextDrawFont(textGroups[5], 4);
	TextDrawLetterSize(textGroups[5], 0.500000, 1.000000);
	TextDrawColor(textGroups[5], 673720575);
	TextDrawSetOutline(textGroups[5], 0);
	TextDrawSetProportional(textGroups[5], 1);
	TextDrawSetShadow(textGroups[5], 1);
	TextDrawUseBox(textGroups[5], 1);
	TextDrawBoxColor(textGroups[5], 168430335);
	TextDrawTextSize(textGroups[5], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[5], 1);

	textGroups[6] = TextDrawCreate(141.000000, 218.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[6], 255);
	TextDrawFont(textGroups[6], 4);
	TextDrawLetterSize(textGroups[6], 0.500000, 1.000000);
	TextDrawColor(textGroups[6], 673720575);
	TextDrawSetOutline(textGroups[6], 0);
	TextDrawSetProportional(textGroups[6], 1);
	TextDrawSetShadow(textGroups[6], 1);
	TextDrawUseBox(textGroups[6], 1);
	TextDrawBoxColor(textGroups[6], 168430335);
	TextDrawTextSize(textGroups[6], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[6], 1);

	textGroups[7] = TextDrawCreate(141.000000, 232.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[7], 255);
	TextDrawFont(textGroups[7], 4);
	TextDrawLetterSize(textGroups[7], 0.500000, 1.000000);
	TextDrawColor(textGroups[7], 673720575);
	TextDrawSetOutline(textGroups[7], 0);
	TextDrawSetProportional(textGroups[7], 1);
	TextDrawSetShadow(textGroups[7], 1);
	TextDrawUseBox(textGroups[7], 1);
	TextDrawBoxColor(textGroups[7], 168430335);
	TextDrawTextSize(textGroups[7], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[7], 1);

	textGroups[8] = TextDrawCreate(141.000000, 246.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[8], 255);
	TextDrawFont(textGroups[8], 4);
	TextDrawLetterSize(textGroups[8], 0.500000, 1.000000);
	TextDrawColor(textGroups[8], 673720575);
	TextDrawSetOutline(textGroups[8], 0);
	TextDrawSetProportional(textGroups[8], 1);
	TextDrawSetShadow(textGroups[8], 1);
	TextDrawUseBox(textGroups[8], 1);
	TextDrawBoxColor(textGroups[8], 168430335);
	TextDrawTextSize(textGroups[8], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[8], 1);

	textGroups[9] = TextDrawCreate(141.000000, 260.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[9], 255);
	TextDrawFont(textGroups[9], 4);
	TextDrawLetterSize(textGroups[9], 0.500000, 1.000000);
	TextDrawColor(textGroups[9], 673720575);
	TextDrawSetOutline(textGroups[9], 0);
	TextDrawSetProportional(textGroups[9], 1);
	TextDrawSetShadow(textGroups[9], 1);
	TextDrawUseBox(textGroups[9], 1);
	TextDrawBoxColor(textGroups[9], 168430335);
	TextDrawTextSize(textGroups[9], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[9], 1);

	textGroups[10] = TextDrawCreate(141.000000, 274.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[10], 255);
	TextDrawFont(textGroups[10], 4);
	TextDrawLetterSize(textGroups[10], 0.500000, 1.000000);
	TextDrawColor(textGroups[10], 673720575);
	TextDrawSetOutline(textGroups[10], 0);
	TextDrawSetProportional(textGroups[10], 1);
	TextDrawSetShadow(textGroups[10], 1);
	TextDrawUseBox(textGroups[10], 1);
	TextDrawBoxColor(textGroups[10], 168430335);
	TextDrawTextSize(textGroups[10], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[10], 1);

	textGroups[11] = TextDrawCreate(141.000000, 288.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[11], 255);
	TextDrawFont(textGroups[11], 4);
	TextDrawLetterSize(textGroups[11], 0.500000, 1.000000);
	TextDrawColor(textGroups[11], 673720575);
	TextDrawSetOutline(textGroups[11], 0);
	TextDrawSetProportional(textGroups[11], 1);
	TextDrawSetShadow(textGroups[11], 1);
	TextDrawUseBox(textGroups[11], 1);
	TextDrawBoxColor(textGroups[11], 168430335);
	TextDrawTextSize(textGroups[11], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[11], 1);

	textGroups[12] = TextDrawCreate(141.000000, 302.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[12], 255);
	TextDrawFont(textGroups[12], 4);
	TextDrawLetterSize(textGroups[12], 0.500000, 1.000000);
	TextDrawColor(textGroups[12], 673720575);
	TextDrawSetOutline(textGroups[12], 0);
	TextDrawSetProportional(textGroups[12], 1);
	TextDrawSetShadow(textGroups[12], 1);
	TextDrawUseBox(textGroups[12], 1);
	TextDrawBoxColor(textGroups[12], 168430335);
	TextDrawTextSize(textGroups[12], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[12], 1);

	textGroups[13] = TextDrawCreate(140.000000, 139.000000, "~d~ Lista de grupos          ~d~ Membros do grupo");
	TextDrawBackgroundColor(textGroups[13], 0);
	TextDrawFont(textGroups[13], 1);
	TextDrawLetterSize(textGroups[13], 0.250000, 0.799998);
	TextDrawColor(textGroups[13], -176);
	TextDrawSetOutline(textGroups[13], 0);
	TextDrawSetProportional(textGroups[13], 1);
	TextDrawSetShadow(textGroups[13], 1);
	TextDrawSetSelectable(textGroups[13], 0);

	textGroups[14] = TextDrawCreate(256.000000, 151.000000, "usebox");
	TextDrawBackgroundColor(textGroups[14], 0);
	TextDrawFont(textGroups[14], 1);
	TextDrawLetterSize(textGroups[14], 0.500000, 19.099996);
	TextDrawColor(textGroups[14], 0);
	TextDrawSetOutline(textGroups[14], 0);
	TextDrawSetProportional(textGroups[14], 1);
	TextDrawSetShadow(textGroups[14], 1);
	TextDrawUseBox(textGroups[14], 1);
	TextDrawBoxColor(textGroups[14], 673720575);
	TextDrawTextSize(textGroups[14], 374.000000, 0.000000);
	TextDrawSetSelectable(textGroups[14], 0);

	textGroups[15] = TextDrawCreate(387.000000, 148.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[15], 255);
	TextDrawFont(textGroups[15], 4);
	TextDrawLetterSize(textGroups[15], 0.500000, 1.000000);
	TextDrawColor(textGroups[15], 673720575);
	TextDrawSetOutline(textGroups[15], 0);
	TextDrawSetProportional(textGroups[15], 1);
	TextDrawSetShadow(textGroups[15], 1);
	TextDrawUseBox(textGroups[15], 1);
	TextDrawBoxColor(textGroups[15], 168430335);
	TextDrawTextSize(textGroups[15], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[15], 1);

	textGroups[16] = TextDrawCreate(387.000000, 162.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[16], 255);
	TextDrawFont(textGroups[16], 4);
	TextDrawLetterSize(textGroups[16], 0.500000, 1.000000);
	TextDrawColor(textGroups[16], 673720575);
	TextDrawSetOutline(textGroups[16], 0);
	TextDrawSetProportional(textGroups[16], 1);
	TextDrawSetShadow(textGroups[16], 1);
	TextDrawUseBox(textGroups[16], 1);
	TextDrawBoxColor(textGroups[16], 168430335);
	TextDrawTextSize(textGroups[16], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[16], 1);

	textGroups[17] = TextDrawCreate(387.000000, 176.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[17], 255);
	TextDrawFont(textGroups[17], 4);
	TextDrawLetterSize(textGroups[17], 0.500000, 1.000000);
	TextDrawColor(textGroups[17], 673720575);
	TextDrawSetOutline(textGroups[17], 0);
	TextDrawSetProportional(textGroups[17], 1);
	TextDrawSetShadow(textGroups[17], 1);
	TextDrawUseBox(textGroups[17], 1);
	TextDrawBoxColor(textGroups[17], 168430335);
	TextDrawTextSize(textGroups[17], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[17], 1);

	textGroups[18] = TextDrawCreate(387.000000, 190.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[18], 255);
	TextDrawFont(textGroups[18], 4);
	TextDrawLetterSize(textGroups[18], 0.500000, 1.000000);
	TextDrawColor(textGroups[18], 673720575);
	TextDrawSetOutline(textGroups[18], 0);
	TextDrawSetProportional(textGroups[18], 1);
	TextDrawSetShadow(textGroups[18], 1);
	TextDrawUseBox(textGroups[18], 1);
	TextDrawBoxColor(textGroups[18], 168430335);
	TextDrawTextSize(textGroups[18], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[18], 1);

	textGroups[19] = TextDrawCreate(387.000000, 204.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[19], 255);
	TextDrawFont(textGroups[19], 4);
	TextDrawLetterSize(textGroups[19], 0.500000, 1.000000);
	TextDrawColor(textGroups[19], 673720575);
	TextDrawSetOutline(textGroups[19], 0);
	TextDrawSetProportional(textGroups[19], 1);
	TextDrawSetShadow(textGroups[19], 1);
	TextDrawUseBox(textGroups[19], 1);
	TextDrawBoxColor(textGroups[19], 168430335);
	TextDrawTextSize(textGroups[19], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[19], 1);

	textGroups[20] = TextDrawCreate(387.000000, 218.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[20], 255);
	TextDrawFont(textGroups[20], 4);
	TextDrawLetterSize(textGroups[20], 0.500000, 1.000000);
	TextDrawColor(textGroups[20], 673720575);
	TextDrawSetOutline(textGroups[20], 0);
	TextDrawSetProportional(textGroups[20], 1);
	TextDrawSetShadow(textGroups[20], 1);
	TextDrawUseBox(textGroups[20], 1);
	TextDrawBoxColor(textGroups[20], 168430335);
	TextDrawTextSize(textGroups[20], 108.000000, 13.000000);
	TextDrawSetSelectable(textGroups[20], 1);

	textGroups[21] = TextDrawCreate(195.000000, 318.000000, "ld_beat:left");
	TextDrawBackgroundColor(textGroups[21], 255);
	TextDrawFont(textGroups[21], 4);
	TextDrawLetterSize(textGroups[21], 0.500000, 1.000000);
	TextDrawColor(textGroups[21], -206);
	TextDrawSetOutline(textGroups[21], 0);
	TextDrawSetProportional(textGroups[21], 1);
	TextDrawSetShadow(textGroups[21], 1);
	TextDrawUseBox(textGroups[21], 1);
	TextDrawBoxColor(textGroups[21], 255);
	TextDrawTextSize(textGroups[21], 15.000000, 10.000000);
	TextDrawSetSelectable(textGroups[21], 1);

	textGroups[22] = TextDrawCreate(235.000000, 318.000000, "ld_beat:right");
	TextDrawBackgroundColor(textGroups[22], 255);
	TextDrawFont(textGroups[22], 4);
	TextDrawLetterSize(textGroups[22], 0.500000, 1.000000);
	TextDrawColor(textGroups[22], -206);
	TextDrawSetOutline(textGroups[22], 0);
	TextDrawSetProportional(textGroups[22], 1);
	TextDrawSetShadow(textGroups[22], 1);
	TextDrawUseBox(textGroups[22], 1);
	TextDrawBoxColor(textGroups[22], 255);
	TextDrawTextSize(textGroups[22], 15.000000, 10.000000);
	TextDrawSetSelectable(textGroups[22], 1);

	textGroups[23] = TextDrawCreate(379.000000, 151.000000, "~>~  Criar grupo~n~~n~~>~  Meu grupo~n~~n~~>~  Convidar membro~n~~n~~>~  Limpar membro~n~~n~~>~  Destruir grupo~n~~n~~>~  Sair do grupo");
	TextDrawBackgroundColor(textGroups[23], 0);
	TextDrawFont(textGroups[23], 2);
	TextDrawLetterSize(textGroups[23], 0.219999, 0.779999);
	TextDrawColor(textGroups[23], -106);
	TextDrawSetOutline(textGroups[23], 0);
	TextDrawSetProportional(textGroups[23], 1);
	TextDrawSetShadow(textGroups[23], 1);
	TextDrawSetSelectable(textGroups[23], 0);

	textGroups[24] = TextDrawCreate(463.000000, 134.000000, "ld_dual:white");
	TextDrawBackgroundColor(textGroups[24], 255);
	TextDrawFont(textGroups[24], 4);
	TextDrawLetterSize(textGroups[24], 0.500000, 1.000000);
	TextDrawColor(textGroups[24], 673720575);
	TextDrawSetOutline(textGroups[24], 0);
	TextDrawSetProportional(textGroups[24], 1);
	TextDrawSetShadow(textGroups[24], 1);
	TextDrawUseBox(textGroups[24], 1);
	TextDrawBoxColor(textGroups[24], 168430335);
	TextDrawTextSize(textGroups[24], 41.000000, 10.000000);
	TextDrawSetSelectable(textGroups[24], 1);

	textGroups[25] = TextDrawCreate(466.000000, 135.000000, "fechar");
	TextDrawBackgroundColor(textGroups[25], 0);
	TextDrawFont(textGroups[25], 2);
	TextDrawLetterSize(textGroups[25], 0.209997, 0.879998);
	TextDrawColor(textGroups[25], -156);
	TextDrawSetOutline(textGroups[25], 0);
	TextDrawSetProportional(textGroups[25], 1);
	TextDrawSetShadow(textGroups[25], 1);
	TextDrawSetSelectable(textGroups[25], 0);
	
	// Crate discription
	serverBoxDiscription[0] = TextDrawCreate(192.000000, 180.000000, "usebox");
	TextDrawBackgroundColor(serverBoxDiscription[0], 0);
	TextDrawFont(serverBoxDiscription[0], 1);
	TextDrawLetterSize(serverBoxDiscription[0], 1.000000, 12.199996);
	TextDrawColor(serverBoxDiscription[0], 0);
	TextDrawSetOutline(serverBoxDiscription[0], 0);
	TextDrawSetProportional(serverBoxDiscription[0], 1);
	TextDrawSetShadow(serverBoxDiscription[0], 1);
	TextDrawUseBox(serverBoxDiscription[0], 1);
	TextDrawBoxColor(serverBoxDiscription[0], 200);
	TextDrawTextSize(serverBoxDiscription[0], 360.000000, 0.000000);
	TextDrawSetSelectable(serverBoxDiscription[0], 0);

	serverBoxDiscription[1] = TextDrawCreate(206.000000, 264.000000, "    OK");
	TextDrawBackgroundColor(serverBoxDiscription[1], 0);
	TextDrawFont(serverBoxDiscription[1], 1);
	TextDrawLetterSize(serverBoxDiscription[1], 0.270000, 1.300000);
	TextDrawColor(serverBoxDiscription[1], -136);
	TextDrawSetOutline(serverBoxDiscription[1], 0);
	TextDrawSetProportional(serverBoxDiscription[1], 1);
	TextDrawSetShadow(serverBoxDiscription[1], 1);
	TextDrawUseBox(serverBoxDiscription[1], 1);
	TextDrawBoxColor(serverBoxDiscription[1], 421075455);
	TextDrawTextSize(serverBoxDiscription[1], 250.000000, 10.000000);
	TextDrawSetSelectable(serverBoxDiscription[1], 1);
}

stock createPlayerTextDraws(playerid) {

	// Verificar se não é um npc
	if (IsPlayerNPC(playerid)) return 1;

	// Menu principal

	// Info admin spec
	textAdminInfoSpec[playerid] = CreatePlayerTextDraw(playerid,541.000000, 190.000000, "__");
	PlayerTextDrawBackgroundColor(playerid,textAdminInfoSpec[playerid], 0);
	PlayerTextDrawFont(playerid,textAdminInfoSpec[playerid], 1);
	PlayerTextDrawLetterSize(playerid,textAdminInfoSpec[playerid], 0.180000, 0.799999);
	PlayerTextDrawColor(playerid,textAdminInfoSpec[playerid], -156);
	PlayerTextDrawSetOutline(playerid,textAdminInfoSpec[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textAdminInfoSpec[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textAdminInfoSpec[playerid], 1);
	PlayerTextDrawUseBox(playerid,textAdminInfoSpec[playerid], 1);
	PlayerTextDrawBoxColor(playerid,textAdminInfoSpec[playerid], 50);
	PlayerTextDrawTextSize(playerid,textAdminInfoSpec[playerid], 644.000000, 110.000000);

	// Informações do audio plugin
	textAudioPlugin[playerid] = CreatePlayerTextDraw(playerid,312.000000, 263.000000, "Aguardando audio plugin~n~15");
	PlayerTextDrawAlignment(playerid,textAudioPlugin[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textAudioPlugin[playerid], 0);
	PlayerTextDrawFont(playerid,textAudioPlugin[playerid], 2);
	PlayerTextDrawLetterSize(playerid,textAudioPlugin[playerid], 0.230000, 1.100000);
	PlayerTextDrawColor(playerid,textAudioPlugin[playerid], -156);
	PlayerTextDrawSetOutline(playerid,textAudioPlugin[playerid], 1);
	PlayerTextDrawSetProportional(playerid,textAudioPlugin[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textAudioPlugin[playerid], 0);

	// Info death
	textInfoDeath[playerid] = CreatePlayerTextDraw(playerid,319.000000, 325.000000, "Voce esta inconsciente");
	PlayerTextDrawAlignment(playerid,textInfoDeath[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textInfoDeath[playerid], 50);
	PlayerTextDrawFont(playerid,textInfoDeath[playerid], 1);
	PlayerTextDrawLetterSize(playerid,textInfoDeath[playerid], 0.190000, 1.000000);
	PlayerTextDrawColor(playerid,textInfoDeath[playerid], -136);
	PlayerTextDrawSetOutline(playerid,textInfoDeath[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textInfoDeath[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textInfoDeath[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textInfoDeath[playerid], 0);

	// Bússola
	textBussola[playerid] = CreatePlayerTextDraw(playerid,619.000000, 134.000000, "N");
	PlayerTextDrawAlignment(playerid,textBussola[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,textBussola[playerid], 0);
	PlayerTextDrawFont(playerid,textBussola[playerid], 2);
	PlayerTextDrawLetterSize(playerid,textBussola[playerid], 0.440000, 1.800000);
	PlayerTextDrawColor(playerid,textBussola[playerid], -156);
	PlayerTextDrawSetOutline(playerid,textBussola[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textBussola[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textBussola[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textBussola[playerid], 0);

	// Criar a Textdraw de informações
	playerTextBoxInfo[playerid] = CreatePlayerTextDraw(playerid,608.000000, 43.000000, "00%~n~~w~~h~Nenhuma~n~0/100~n~~n~---~n~0~n~0%~n~_");
	PlayerTextDrawAlignment(playerid,playerTextBoxInfo[playerid], 3);
	PlayerTextDrawBackgroundColor(playerid,playerTextBoxInfo[playerid], 0);
	PlayerTextDrawFont(playerid,playerTextBoxInfo[playerid], 1);
	PlayerTextDrawLetterSize(playerid,playerTextBoxInfo[playerid], 0.210000, 0.799999);
	PlayerTextDrawColor(playerid,playerTextBoxInfo[playerid], 16777150);
	PlayerTextDrawSetOutline(playerid,playerTextBoxInfo[playerid], 0);
	PlayerTextDrawSetProportional(playerid,playerTextBoxInfo[playerid], 1);
	PlayerTextDrawSetShadow(playerid,playerTextBoxInfo[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,playerTextBoxInfo[playerid], 0);
	
	// Barulho
	textPlayerBarulho[0] = CreatePlayerTextDraw(playerid, 600.000000, 292.000000, "-");
	PlayerTextDrawBackgroundColor(playerid, textPlayerBarulho[0], 0);
	PlayerTextDrawFont(playerid, textPlayerBarulho[0], 3);
	PlayerTextDrawLetterSize(playerid, textPlayerBarulho[0], 0.670000, -0.499998);
	PlayerTextDrawColor(playerid, textPlayerBarulho[0], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerBarulho[0], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerBarulho[0], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerBarulho[0], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerBarulho[0], 0);

	textPlayerBarulho[1] = CreatePlayerTextDraw(playerid, 613.000000, 292.000000, "-");
	PlayerTextDrawBackgroundColor(playerid, textPlayerBarulho[1], 0);
	PlayerTextDrawFont(playerid, textPlayerBarulho[1], 3);
	PlayerTextDrawLetterSize(playerid, textPlayerBarulho[1], 0.670000, -0.499998);
	PlayerTextDrawColor(playerid, textPlayerBarulho[1], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerBarulho[1], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerBarulho[1], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerBarulho[1], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerBarulho[1], 0);
	
	// Pontuação do player
	playerTextPoints[playerid] = CreatePlayerTextDraw(playerid, 321.000000, 3.000000, "000000/000000");
	PlayerTextDrawAlignment(playerid, playerTextPoints[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, playerTextPoints[playerid], 0);
	PlayerTextDrawFont(playerid, playerTextPoints[playerid], 1);
	PlayerTextDrawLetterSize(playerid, playerTextPoints[playerid], 0.229999, 0.799998);
	PlayerTextDrawColor(playerid, playerTextPoints[playerid], 16777215);
	PlayerTextDrawSetOutline(playerid, playerTextPoints[playerid], 1);
	PlayerTextDrawSetProportional(playerid, playerTextPoints[playerid], 1);
	
	// Level do player
	textPlayerLevel[playerid] = CreatePlayerTextDraw(playerid, 377.000000, 2.000000, "0");
	PlayerTextDrawAlignment(playerid, textPlayerLevel[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerLevel[playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerLevel[playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerLevel[playerid], 0.319998, 0.999998);
	PlayerTextDrawColor(playerid, textPlayerLevel[playerid], 16777060);
	PlayerTextDrawSetOutline(playerid, textPlayerLevel[playerid], 1);
	PlayerTextDrawSetProportional(playerid, textPlayerLevel[playerid], 1);
	
	// ZP
	textPlayerZp = CreatePlayerTextDraw(playerid,277.000000, 3.000000, "0 ~r~~h~~h~ZP");
	PlayerTextDrawAlignment(playerid,textPlayerZp, 3);
	PlayerTextDrawBackgroundColor(playerid,textPlayerZp, 0);
	PlayerTextDrawFont(playerid,textPlayerZp, 2);
	PlayerTextDrawLetterSize(playerid,textPlayerZp, 0.149998, 0.799996);
	PlayerTextDrawColor(playerid,textPlayerZp, -156);
	PlayerTextDrawSetOutline(playerid,textPlayerZp, 1);
	PlayerTextDrawSetProportional(playerid,textPlayerZp, 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerZp, 0);
	
	// Introducao
	/*textIntroducao[0][playerid] = CreatePlayerTextDraw(playerid,436.000000, 237.000000, "CONTRIBUIDOR");
	PlayerTextDrawAlignment(playerid,textIntroducao[0][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textIntroducao[0][playerid], 0);
	PlayerTextDrawFont(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid,textIntroducao[0][playerid], 0.230000, 0.799998);
	PlayerTextDrawColor(playerid,textIntroducao[0][playerid], -176);
	PlayerTextDrawSetOutline(playerid,textIntroducao[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textIntroducao[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textIntroducao[0][playerid], 0);

	textIntroducao[1][playerid] = CreatePlayerTextDraw(playerid,437.000000, 246.000000, "Ninguem");
	PlayerTextDrawAlignment(playerid,textIntroducao[1][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textIntroducao[1][playerid], 0);
	PlayerTextDrawFont(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid,textIntroducao[1][playerid], 0.439999, 1.699998);
	PlayerTextDrawColor(playerid,textIntroducao[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid,textIntroducao[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textIntroducao[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textIntroducao[1][playerid], 0);*/
	
	// Player configs
	textPlayerConfig[playerid] = CreatePlayerTextDraw(playerid, 414.000000, 235.000000 - reposition, ": -~n~~n~: -~n~~n~: -");
	PlayerTextDrawBackgroundColor(playerid, textPlayerConfig[playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerConfig[playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerConfig[playerid], 0.240000, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerConfig[playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerConfig[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerConfig[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerConfig[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerConfig[playerid], 0);
	
	// Necessidades e vida
	playerHudTextdraw[0] = CreatePlayerTextDraw(playerid,528.000000, 375.000000, "mdl-1015:INVALID");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[0], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[0], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[0], -156);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[0], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[0], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[0], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[0], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[0], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[0], -55.000000, 19.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[0], 0);

	playerHudTextdraw[1] = CreatePlayerTextDraw(playerid,503.000000, 396.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[1], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[1], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[1], -926365441);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[1], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[1], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[1], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[1], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[1], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[1], 110.000000, 9.300000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[1], 0);

	playerHudTextdraw[2] = CreatePlayerTextDraw(playerid,561.000000, 376.000000, "0");
	PlayerTextDrawAlignment(playerid,playerHudTextdraw[2], 2);
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[2], 0);
	PlayerTextDrawFont(playerid,playerHudTextdraw[2], 2);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[2], 0.199998, 1.600000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[2], -16776961);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[2], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[2], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[2], 1);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[2], 0);

	playerHudTextdraw[3] = CreatePlayerTextDraw(playerid,637.000000, 382.000000, "mdl-1019:down");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[3], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[3], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[3], -106);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[3], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[3], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[3], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[3], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[3], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[3], -16.000000, 46.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[3], 0);

	playerHudTextdraw[4] = CreatePlayerTextDraw(playerid,503.000000, 412.100006, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[4], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[4], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[4], -56);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[4], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[4], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[4], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[4], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[4], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[4], 107.000000, 9.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[4], 0);

	playerHudTextdraw[5] = CreatePlayerTextDraw(playerid,503.000000, 428.500000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[5], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[5], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[5], -56);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[5], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[5], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[5], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[5], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[5], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[5], 57.000000, 9.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[5], 0);

	playerHudTextdraw[6] = CreatePlayerTextDraw(playerid,584.000000, 378.000000, "mdl-1019:b3");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[6], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[6], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[6], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[6], -186);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[6], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[6], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[6], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[6], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[6], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[6], 10.000000, 12.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[6], 0);

	playerHudTextdraw[7] = CreatePlayerTextDraw(playerid,596.000000, 378.000000, "mdl-1019:a3");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[7], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[7], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[7], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[7], -186);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[7], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[7], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[7], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[7], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[7], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[7], 10.000000, 12.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[7], 0);

	playerHudTextdraw[8] = CreatePlayerTextDraw(playerid,608.000000, 378.000000, "mdl-1019:h1");
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[8], 255);
	PlayerTextDrawFont(playerid,playerHudTextdraw[8], 4);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[8], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerHudTextdraw[8], -186);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[8], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[8], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[8], 1);
	PlayerTextDrawUseBox(playerid,playerHudTextdraw[8], 1);
	PlayerTextDrawBoxColor(playerid,playerHudTextdraw[8], 255);
	PlayerTextDrawTextSize(playerid,playerHudTextdraw[8], 10.000000, 12.000000);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[8], 0);

	playerHudTextdraw[9] = CreatePlayerTextDraw(playerid,631.899780, 427.500030, "B6");
	PlayerTextDrawAlignment(playerid,playerHudTextdraw[9], 2);
	PlayerTextDrawBackgroundColor(playerid,playerHudTextdraw[9], 0);
	PlayerTextDrawFont(playerid,playerHudTextdraw[9], 2);
	PlayerTextDrawLetterSize(playerid,playerHudTextdraw[9], 0.155996, 1.409999);
	PlayerTextDrawColor(playerid,playerHudTextdraw[9], -156);
	PlayerTextDrawSetOutline(playerid,playerHudTextdraw[9], 0);
	PlayerTextDrawSetProportional(playerid,playerHudTextdraw[9], 1);
	PlayerTextDrawSetShadow(playerid,playerHudTextdraw[9], 1);
	PlayerTextDrawSetSelectable(playerid,playerHudTextdraw[9], 0);
	
	// Ranks
	textPlayerRanks[playerid][0] = CreatePlayerTextDraw(playerid, 386.000000 + rank_repos, 168.000000, "----");
	PlayerTextDrawAlignment(playerid, textPlayerRanks[playerid][0], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerRanks[playerid][0], 0);
	PlayerTextDrawFont(playerid, textPlayerRanks[playerid][0], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerRanks[playerid][0], 0.159999, 0.999999);
	PlayerTextDrawColor(playerid, textPlayerRanks[playerid][0], 16777120);
	PlayerTextDrawSetOutline(playerid, textPlayerRanks[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerRanks[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerRanks[playerid][0], 1);

	textPlayerRanks[playerid][1] = CreatePlayerTextDraw(playerid, 228.000000 + rank_repos, 200.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, textPlayerRanks[playerid][1], 0);
	PlayerTextDrawFont(playerid, textPlayerRanks[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerRanks[playerid][1], 0.219999, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerRanks[playerid][1], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerRanks[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerRanks[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerRanks[playerid][1], 1);

	textPlayerRanks[playerid][2] = CreatePlayerTextDraw(playerid, 267.000000 + rank_repos, 200.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, textPlayerRanks[playerid][2], 0);
	PlayerTextDrawFont(playerid, textPlayerRanks[playerid][2], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerRanks[playerid][2], 0.189999, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerRanks[playerid][2], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerRanks[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerRanks[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerRanks[playerid][2], 1);

	textPlayerRanks[playerid][3] = CreatePlayerTextDraw(playerid, 369.000000 + rank_repos, 200.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, textPlayerRanks[playerid][3], 0);
	PlayerTextDrawFont(playerid, textPlayerRanks[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerRanks[playerid][3], 0.179999, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerRanks[playerid][3], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerRanks[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerRanks[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerRanks[playerid][3], 1);

	textPlayerRanks[playerid][4] = CreatePlayerTextDraw(playerid, 446.000000 + rank_repos, 178.000000, "--------");
	PlayerTextDrawAlignment(playerid, textPlayerRanks[playerid][4], 3);
	PlayerTextDrawBackgroundColor(playerid, textPlayerRanks[playerid][4], 0);
	PlayerTextDrawFont(playerid, textPlayerRanks[playerid][4], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerRanks[playerid][4], 0.189999, 0.899999);
	PlayerTextDrawColor(playerid, textPlayerRanks[playerid][4], -206);
	PlayerTextDrawSetOutline(playerid, textPlayerRanks[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerRanks[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerRanks[playerid][4], 1);
	
	// status
	PlayerTextDrawStatus[0] = CreatePlayerTextDraw(playerid,496.000000, 207.000000, "Level~n~~n~Kills~n~~n~Mortes~n~~n~Zombie kills~n~~n~Battle royales~n~~n~Battle royale wins~n~~n~Battle royale kills~n~~n~Grupo");
	PlayerTextDrawBackgroundColor(playerid,PlayerTextDrawStatus[0], 0);
	PlayerTextDrawFont(playerid,PlayerTextDrawStatus[0], 1);
	PlayerTextDrawLetterSize(playerid,PlayerTextDrawStatus[0], 0.189998, 0.849999);
	PlayerTextDrawColor(playerid,PlayerTextDrawStatus[0], 11862015);
	PlayerTextDrawSetOutline(playerid,PlayerTextDrawStatus[0], 0);
	PlayerTextDrawSetProportional(playerid,PlayerTextDrawStatus[0], 1);
	PlayerTextDrawSetShadow(playerid,PlayerTextDrawStatus[0], 1);
	PlayerTextDrawSetSelectable(playerid,PlayerTextDrawStatus[0], 0);

	PlayerTextDrawStatus[1] = CreatePlayerTextDraw(playerid,583.000000, 207.000000, "15~n~~n~231~n~~n~120~n~~n~95~n~~n~14~n~~n~4~n~~n~32~n~~n~ScarfaceOwna");
	PlayerTextDrawBackgroundColor(playerid,PlayerTextDrawStatus[1], 0);
	PlayerTextDrawFont(playerid,PlayerTextDrawStatus[1], 1);
	PlayerTextDrawLetterSize(playerid,PlayerTextDrawStatus[1], 0.189998, 0.849999);
	PlayerTextDrawColor(playerid,PlayerTextDrawStatus[1], -1);
	PlayerTextDrawSetOutline(playerid,PlayerTextDrawStatus[1], 0);
	PlayerTextDrawSetProportional(playerid,PlayerTextDrawStatus[1], 1);
	PlayerTextDrawSetShadow(playerid,PlayerTextDrawStatus[1], 1);
	PlayerTextDrawSetSelectable(playerid,PlayerTextDrawStatus[1], 0);

	PlayerTextDrawStatus[2] = CreatePlayerTextDraw(playerid,497.000000, 190.000000, "dimmy_scarface");
	PlayerTextDrawBackgroundColor(playerid,PlayerTextDrawStatus[2], 0);
	PlayerTextDrawFont(playerid,PlayerTextDrawStatus[2], 2);
	PlayerTextDrawLetterSize(playerid,PlayerTextDrawStatus[2], 0.169999, 0.899999);
	PlayerTextDrawColor(playerid,PlayerTextDrawStatus[2], -206);
	PlayerTextDrawSetOutline(playerid,PlayerTextDrawStatus[2], 0);
	PlayerTextDrawSetProportional(playerid,PlayerTextDrawStatus[2], 1);
	PlayerTextDrawSetShadow(playerid,PlayerTextDrawStatus[2], 1);
	PlayerTextDrawUseBox(playerid,PlayerTextDrawStatus[2], 1);
	PlayerTextDrawBoxColor(playerid,PlayerTextDrawStatus[2], 252645375);
	PlayerTextDrawTextSize(playerid,PlayerTextDrawStatus[2], 620.000000, 10.000000);
	PlayerTextDrawSetSelectable(playerid,PlayerTextDrawStatus[2], 1);
	
	// Loot
	textPlayerLoot[playerid] = CreatePlayerTextDraw(playerid,597.000000, 191.000000, "Loot");
	PlayerTextDrawAlignment(playerid,textPlayerLoot[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textPlayerLoot[playerid], 0);
	PlayerTextDrawFont(playerid,textPlayerLoot[playerid], 1);
	PlayerTextDrawLetterSize(playerid,textPlayerLoot[playerid], 0.250000, 0.799998);
	PlayerTextDrawColor(playerid,textPlayerLoot[playerid], 16777215);
	PlayerTextDrawSetOutline(playerid,textPlayerLoot[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerLoot[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerLoot[playerid], 1);
	PlayerTextDrawUseBox(playerid,textPlayerLoot[playerid], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerLoot[playerid], 100);
	PlayerTextDrawTextSize(playerid,textPlayerLoot[playerid], 629.000000, 60.000000);
	
	// Blocked account
	playerTextBlocked[0] = CreatePlayerTextDraw(playerid, 394.000000, 224.000000, "Conta bloqueada");
	PlayerTextDrawAlignment(playerid, playerTextBlocked[0], 2);
	PlayerTextDrawBackgroundColor(playerid, playerTextBlocked[0], 0);
	PlayerTextDrawFont(playerid, playerTextBlocked[0], 1);
	PlayerTextDrawLetterSize(playerid, playerTextBlocked[0], 0.200000, 1.100000);
	PlayerTextDrawColor(playerid, playerTextBlocked[0], -156);
	PlayerTextDrawSetOutline(playerid, playerTextBlocked[0], 0);
	PlayerTextDrawSetProportional(playerid, playerTextBlocked[0], 1);
	PlayerTextDrawSetShadow(playerid, playerTextBlocked[0], 1);

	playerTextBlocked[1] = CreatePlayerTextDraw(playerid, 394.000000, 242.000000, "00:00");
	PlayerTextDrawAlignment(playerid, playerTextBlocked[1], 2);
	PlayerTextDrawBackgroundColor(playerid, playerTextBlocked[1], 0);
	PlayerTextDrawFont(playerid, playerTextBlocked[1], 1);
	PlayerTextDrawLetterSize(playerid, playerTextBlocked[1], 0.349999, 1.899999);
	PlayerTextDrawColor(playerid, playerTextBlocked[1], -1);
	PlayerTextDrawSetOutline(playerid, playerTextBlocked[1], 0);
	PlayerTextDrawSetProportional(playerid, playerTextBlocked[1], 1);
	PlayerTextDrawSetShadow(playerid, playerTextBlocked[1], 1);
	
	// Velocimetro
	textVelocimetro[playerid] = CreatePlayerTextDraw(playerid,17.000000, 276.000000, "Sultan~n~~n~Motor: 0/1~n~Rodas: 0/4~n~Gasolina: 25 litros");
	PlayerTextDrawBackgroundColor(playerid,textVelocimetro[playerid], 0);
	PlayerTextDrawFont(playerid,textVelocimetro[playerid], 2);
	PlayerTextDrawLetterSize(playerid,textVelocimetro[playerid], 0.229999, 1.000000);
	PlayerTextDrawColor(playerid,textVelocimetro[playerid], -106);
	PlayerTextDrawSetOutline(playerid,textVelocimetro[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textVelocimetro[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textVelocimetro[playerid], 1);
	PlayerTextDrawSetSelectable(playerid,textVelocimetro[playerid], 0);

	// Shop Coins

	textPlayerShopCoins[playerid] = CreatePlayerTextDraw(playerid, 318.000000, 372.000000, "0-5");
	PlayerTextDrawAlignment(playerid, textPlayerShopCoins[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopCoins[playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopCoins[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerShopCoins[playerid], 0.370000, 1.299999);
	PlayerTextDrawColor(playerid, textPlayerShopCoins[playerid], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerShopCoins[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopCoins[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopCoins[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopCoins[playerid], 0);

	textPlayerShopModel[0][playerid] = CreatePlayerTextDraw(playerid, 166.000000, 191.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[0][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[0][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[0][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[0][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[0][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[0][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[0][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[0][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[0][playerid], 349);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[0][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[0][playerid], 0);

	textPlayerShopModel[1][playerid] = CreatePlayerTextDraw(playerid, 275.000000, 191.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[1][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[1][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[1][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[1][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[1][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[1][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[1][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[1][playerid], 19559);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[1][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[1][playerid], 0);

	textPlayerShopModel[2][playerid] = CreatePlayerTextDraw(playerid, 386.000000, 191.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[2][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[2][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[2][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[2][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[2][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[2][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[2][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[2][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[2][playerid], 348);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[2][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[2][playerid], 0);

	textPlayerShopModel[3][playerid] = CreatePlayerTextDraw(playerid, 166.000000, 284.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[3][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[3][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[3][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[3][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[3][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[3][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[3][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[3][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[3][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[3][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[3][playerid], 355);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[3][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[3][playerid], 0);

	textPlayerShopModel[4][playerid] = CreatePlayerTextDraw(playerid, 275.000000, 284.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[4][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[4][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[4][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[4][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[4][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[4][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[4][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[4][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[4][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[4][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[4][playerid], 356);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[4][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[4][playerid], 0);

	textPlayerShopModel[5][playerid] = CreatePlayerTextDraw(playerid, 386.000000, 284.000000, "model_view");
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopModel[5][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerShopModel[5][playerid], 5);
	PlayerTextDrawLetterSize(playerid, textPlayerShopModel[5][playerid], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, textPlayerShopModel[5][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopModel[5][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopModel[5][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopModel[5][playerid], 1);
	PlayerTextDrawUseBox(playerid, textPlayerShopModel[5][playerid], 1);
	PlayerTextDrawBoxColor(playerid, textPlayerShopModel[5][playerid], 0);
	PlayerTextDrawTextSize(playerid, textPlayerShopModel[5][playerid], 84.000000, 71.000000);
	PlayerTextDrawSetPreviewModel(playerid, textPlayerShopModel[5][playerid], 358);
	PlayerTextDrawSetPreviewRot(playerid, textPlayerShopModel[5][playerid], -16.000000, 0.000000, -55.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopModel[5][playerid], 0);

	textPlayerShopName[0][playerid] = CreatePlayerTextDraw(playerid, 206.000000, 251.000000, "Calibre 12 x25~n~~n~~g~~h~~h~$425");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[0][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[0][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[0][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[0][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[0][playerid], 0);

	textPlayerShopName[1][playerid] = CreatePlayerTextDraw(playerid, 317.000000, 251.000000, "Mochila Grande x1~n~~n~0.045295");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[1][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[1][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[1][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[1][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[1][playerid], 0);

	textPlayerShopName[2][playerid] = CreatePlayerTextDraw(playerid, 427.000000, 251.000000, "Desert Eagle~n~~n~789 Coins");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[2][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[2][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[2][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[2][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[2][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[2][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[2][playerid], 0);

	textPlayerShopName[3][playerid] = CreatePlayerTextDraw(playerid, 207.000000, 345.000000, "Desert Eagle~n~~n~789 Coins");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[3][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[3][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[3][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[3][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[3][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[3][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[3][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[3][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[3][playerid], 0);

	textPlayerShopName[4][playerid] = CreatePlayerTextDraw(playerid, 316.000000, 345.000000, "Desert Eagle~n~~n~789 Coins");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[4][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[4][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[4][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[4][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[4][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[4][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[4][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[4][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[4][playerid], 0);

	textPlayerShopName[5][playerid] = CreatePlayerTextDraw(playerid, 427.000000, 345.000000, "Desert Eagle~n~~n~789 Coins");
	PlayerTextDrawAlignment(playerid, textPlayerShopName[5][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerShopName[5][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerShopName[5][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerShopName[5][playerid], 0.209998, 0.799996);
	PlayerTextDrawColor(playerid, textPlayerShopName[5][playerid], -1);
	PlayerTextDrawSetOutline(playerid, textPlayerShopName[5][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerShopName[5][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerShopName[5][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerShopName[5][playerid], 0);
	
	// Base craft
	
	textAuthorize[playerid] = CreatePlayerTextDraw(playerid,574.000000, 349.000000, "~r~~h~Construcao bloqueada");
	PlayerTextDrawAlignment(playerid,textAuthorize[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,textAuthorize[playerid], 0);
	PlayerTextDrawFont(playerid,textAuthorize[playerid], 1);
	PlayerTextDrawLetterSize(playerid,textAuthorize[playerid], 0.220000, 1.000000);
	PlayerTextDrawColor(playerid,textAuthorize[playerid], -1);
	PlayerTextDrawSetOutline(playerid,textAuthorize[playerid], 0);
	PlayerTextDrawSetProportional(playerid,textAuthorize[playerid], 1);
	PlayerTextDrawSetShadow(playerid,textAuthorize[playerid], 1);
	PlayerTextDrawUseBox(playerid,textAuthorize[playerid], 1);
	PlayerTextDrawBoxColor(playerid,textAuthorize[playerid], 50);
	PlayerTextDrawTextSize(playerid,textAuthorize[playerid], 164.000000, 97.000000);
	PlayerTextDrawSetSelectable(playerid,textAuthorize[playerid], 0);
	
	// CHAT
	
	textChat[0] = CreatePlayerTextDraw(playerid,317.000000, 386.000000, "_");
	PlayerTextDrawAlignment(playerid,textChat[0], 2);
	PlayerTextDrawBackgroundColor(playerid,textChat[0], 0);
	PlayerTextDrawFont(playerid,textChat[0], 1);
	PlayerTextDrawLetterSize(playerid,textChat[0], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textChat[0], -1);
	PlayerTextDrawSetOutline(playerid,textChat[0], 0);
	PlayerTextDrawSetProportional(playerid,textChat[0], 1);
	PlayerTextDrawSetShadow(playerid,textChat[0], 1);
	PlayerTextDrawUseBox(playerid,textChat[0], 1);
	PlayerTextDrawBoxColor(playerid,textChat[0], 60);
	PlayerTextDrawTextSize(playerid,textChat[0], 0.000000, 35.500030);
	PlayerTextDrawSetSelectable(playerid,textChat[0], 0);

	textChat[1] = CreatePlayerTextDraw(playerid,317.000000, 399.000000, "_");
	PlayerTextDrawAlignment(playerid,textChat[1], 2);
	PlayerTextDrawBackgroundColor(playerid,textChat[1], 0);
	PlayerTextDrawFont(playerid,textChat[1], 1);
	PlayerTextDrawLetterSize(playerid,textChat[1], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textChat[1], -156);
	PlayerTextDrawSetOutline(playerid,textChat[1], 0);
	PlayerTextDrawSetProportional(playerid,textChat[1], 1);
	PlayerTextDrawSetShadow(playerid,textChat[1], 1);
	PlayerTextDrawUseBox(playerid,textChat[1], 1);
	PlayerTextDrawBoxColor(playerid,textChat[1], 168430140);
	PlayerTextDrawTextSize(playerid,textChat[1], 0.000000, 207.799987);
	PlayerTextDrawSetSelectable(playerid,textChat[1], 0);

	textChat[2] = CreatePlayerTextDraw(playerid,317.000000, 412.000000, "_");
	PlayerTextDrawAlignment(playerid,textChat[2], 2);
	PlayerTextDrawBackgroundColor(playerid,textChat[2], 0);
	PlayerTextDrawFont(playerid,textChat[2], 1);
	PlayerTextDrawLetterSize(playerid,textChat[2], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textChat[2], -156);
	PlayerTextDrawSetOutline(playerid,textChat[2], 0);
	PlayerTextDrawSetProportional(playerid,textChat[2], 1);
	PlayerTextDrawSetShadow(playerid,textChat[2], 1);
	PlayerTextDrawUseBox(playerid,textChat[2], 1);
	PlayerTextDrawBoxColor(playerid,textChat[2], 70);
	PlayerTextDrawTextSize(playerid,textChat[2], 0.000000, 75.500030);
	PlayerTextDrawSetSelectable(playerid,textChat[2], 0);

	textChat[3] = CreatePlayerTextDraw(playerid,317.000000, 425.000000, "_");
	PlayerTextDrawAlignment(playerid,textChat[3], 2);
	PlayerTextDrawBackgroundColor(playerid,textChat[3], 0);
	PlayerTextDrawFont(playerid,textChat[3], 1);
	PlayerTextDrawLetterSize(playerid,textChat[3], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textChat[3], -156);
	PlayerTextDrawSetOutline(playerid,textChat[3], 0);
	PlayerTextDrawSetProportional(playerid,textChat[3], 1);
	PlayerTextDrawSetShadow(playerid,textChat[3], 1);
	PlayerTextDrawUseBox(playerid,textChat[3], 1);
	PlayerTextDrawBoxColor(playerid,textChat[3], 60);
	PlayerTextDrawTextSize(playerid,textChat[3], 0.000000, 65.500030);
	PlayerTextDrawSetSelectable(playerid,textChat[3], 0);

	textChat[4] = CreatePlayerTextDraw(playerid,317.000000, 438.000000, "_");
	PlayerTextDrawAlignment(playerid,textChat[4], 2);
	PlayerTextDrawBackgroundColor(playerid,textChat[4], 0);
	PlayerTextDrawFont(playerid,textChat[4], 1);
	PlayerTextDrawLetterSize(playerid,textChat[4], 0.170000, 0.799998);
	PlayerTextDrawColor(playerid,textChat[4], -156);
	PlayerTextDrawSetOutline(playerid,textChat[4], 0);
	PlayerTextDrawSetProportional(playerid,textChat[4], 1);
	PlayerTextDrawSetShadow(playerid,textChat[4], 1);
	PlayerTextDrawUseBox(playerid,textChat[4], 1);
	PlayerTextDrawBoxColor(playerid,textChat[4], 60);
	PlayerTextDrawTextSize(playerid,textChat[4], 0.000000, 65.500030);
	PlayerTextDrawSetSelectable(playerid,textChat[4], 0);
	
	// Membros do grupo
	textGroupMembersList[playerid] = CreatePlayerTextDraw(playerid,2.000000, 165.000000, "_");
	PlayerTextDrawBackgroundColor(playerid,textGroupMembersList[playerid], 0);
	PlayerTextDrawFont(playerid,textGroupMembersList[playerid], 2);
	PlayerTextDrawLetterSize(playerid,textGroupMembersList[playerid], 0.134996, 0.729999);
	PlayerTextDrawColor(playerid,textGroupMembersList[playerid], -226);
	PlayerTextDrawSetOutline(playerid,textGroupMembersList[playerid], 1);
	PlayerTextDrawSetProportional(playerid,textGroupMembersList[playerid], 1);
	
	// Grupos
	textPlayerGroups[0][playerid] = CreatePlayerTextDraw(playerid, 254.000000, 151.000000, "Lider: Ninguem~n~~n~_");
	PlayerTextDrawBackgroundColor(playerid, textPlayerGroups[0][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerGroups[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerGroups[0][playerid], 0.230000, 0.799998);
	PlayerTextDrawColor(playerid, textPlayerGroups[0][playerid], -176);
	PlayerTextDrawSetOutline(playerid, textPlayerGroups[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerGroups[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerGroups[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerGroups[0][playerid], 0);

	textPlayerGroups[1][playerid] = CreatePlayerTextDraw(playerid, 144.000000, 151.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, textPlayerGroups[1][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerGroups[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerGroups[1][playerid], 0.230000, 0.779999);
	PlayerTextDrawColor(playerid, textPlayerGroups[1][playerid], 1694498710);
	PlayerTextDrawSetOutline(playerid, textPlayerGroups[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerGroups[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerGroups[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerGroups[1][playerid], 0);

	textPlayerGroups[2][playerid] = CreatePlayerTextDraw(playerid, 222.000000, 318.000000, "0-0");
	PlayerTextDrawAlignment(playerid, textPlayerGroups[2][playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerGroups[2][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerGroups[2][playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerGroups[2][playerid], 0.239998, 0.980000);
	PlayerTextDrawColor(playerid, textPlayerGroups[2][playerid], -206);
	PlayerTextDrawSetOutline(playerid, textPlayerGroups[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerGroups[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerGroups[2][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerGroups[2][playerid], 0);
	
	// Crate discription
	boxDiscription[0] = CreatePlayerTextDraw(playerid, 205.000000, 188.000000, "DAILY LOGIN CRATE");
	PlayerTextDrawBackgroundColor(playerid, boxDiscription[0], 0);
	PlayerTextDrawFont(playerid, boxDiscription[0], 1);
	PlayerTextDrawLetterSize(playerid, boxDiscription[0], 0.230000, 1.300000);
	PlayerTextDrawColor(playerid, boxDiscription[0], -31);
	PlayerTextDrawSetOutline(playerid, boxDiscription[0], 0);
	PlayerTextDrawSetProportional(playerid, boxDiscription[0], 1);
	PlayerTextDrawSetShadow(playerid, boxDiscription[0], 1);
	PlayerTextDrawSetSelectable(playerid, boxDiscription[0], 0);

	boxDiscription[1] = CreatePlayerTextDraw(playerid, 205.000000, 209.000000, "~t~ Receive a random skin");
	PlayerTextDrawBackgroundColor(playerid, boxDiscription[1], 0);
	PlayerTextDrawFont(playerid, boxDiscription[1], 1);
	PlayerTextDrawLetterSize(playerid, boxDiscription[1], 0.150000, 1.000000);
	PlayerTextDrawColor(playerid, boxDiscription[1], -176);
	PlayerTextDrawSetOutline(playerid, boxDiscription[1], 0);
	PlayerTextDrawSetProportional(playerid, boxDiscription[1], 1);
	PlayerTextDrawSetShadow(playerid, boxDiscription[1], 1);
	PlayerTextDrawSetSelectable(playerid, boxDiscription[1], 0);
	
	// Inventário
	createPlayerInventory(playerid);
	
	// Conquistas
	createPlayerTextsConquistas(playerid);
	
	// login screen
	texPlayerLoginScreen = CreatePlayerTextDraw(playerid, 18.000000, 183.000000, "mdl-1001:login");
	PlayerTextDrawBackgroundColor(playerid, texPlayerLoginScreen, 255);
	PlayerTextDrawFont(playerid, texPlayerLoginScreen, 4);
	PlayerTextDrawLetterSize(playerid, texPlayerLoginScreen, 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, texPlayerLoginScreen, -106);
	PlayerTextDrawSetOutline(playerid, texPlayerLoginScreen, 0);
	PlayerTextDrawSetProportional(playerid, texPlayerLoginScreen, 1);
	PlayerTextDrawSetShadow(playerid, texPlayerLoginScreen, 1);
	PlayerTextDrawUseBox(playerid, texPlayerLoginScreen, 1);
	PlayerTextDrawBoxColor(playerid, texPlayerLoginScreen, 255);
	PlayerTextDrawTextSize(playerid, texPlayerLoginScreen, 92.000000, 112.000000);
	PlayerTextDrawSetSelectable(playerid, texPlayerLoginScreen, 1);
	
	// Fader (Ultimo sempre)
	new tmp[E_PLAYER_FADE_INFO];
	gPlayerFadeInfo[playerid] = tmp;

	new PlayerText:text = CreatePlayerTextDraw(playerid, -20.0, -20.0, "_");
	gPlayerFaderTextId = text;
	gPlayerFadeInfo[playerid][fadeCurrentAlpha] = MAX_TRANSPARENCY;
	// detalhes
	PlayerTextDrawUseBox(playerid, text, 1);
	PlayerTextDrawBoxColor(playerid, text, 0xFFFFFF00);
	PlayerTextDrawLetterSize(playerid, text, 680.0, 500.0);
	PlayerTextDrawTextSize(playerid, text, 680.0, 500.0);
	
	// Exp info
	playerExp[0] = CreatePlayerTextDraw(playerid, 10.000000, 169.000000, "mdl-1043:exp");
	PlayerTextDrawBackgroundColor(playerid, playerExp[0], 255);
	PlayerTextDrawFont(playerid, playerExp[0], 4);
	PlayerTextDrawLetterSize(playerid, playerExp[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, playerExp[0], -76);
	PlayerTextDrawSetOutline(playerid, playerExp[0], 0);
	PlayerTextDrawSetProportional(playerid, playerExp[0], 1);
	PlayerTextDrawSetShadow(playerid, playerExp[0], 1);
	PlayerTextDrawUseBox(playerid, playerExp[0], 1);
	PlayerTextDrawBoxColor(playerid, playerExp[0], 255);
	PlayerTextDrawTextSize(playerid, playerExp[0], 77.000000, 43.000000);

	playerExp[1] = CreatePlayerTextDraw(playerid, 33.000000, 179.000000, "+0 EXPERIENCE");
	PlayerTextDrawBackgroundColor(playerid, playerExp[1], 0);
	PlayerTextDrawFont(playerid, playerExp[1], 1);
	PlayerTextDrawLetterSize(playerid, playerExp[1], 0.159999, 0.799999);
	PlayerTextDrawColor(playerid, playerExp[1], -56);
	PlayerTextDrawSetOutline(playerid, playerExp[1], 0);
	PlayerTextDrawSetProportional(playerid, playerExp[1], 1);
	PlayerTextDrawSetShadow(playerid, playerExp[1], 1);

	playerExp[2] = CreatePlayerTextDraw(playerid, 20.000000, 197.000000, "usebox");
	PlayerTextDrawBackgroundColor(playerid, playerExp[2], 0);
	PlayerTextDrawFont(playerid, playerExp[2], 1);
	PlayerTextDrawLetterSize(playerid, playerExp[2], 0.500000, 0.599999);
	PlayerTextDrawColor(playerid, playerExp[2], 0);
	PlayerTextDrawSetOutline(playerid, playerExp[2], 0);
	PlayerTextDrawSetProportional(playerid, playerExp[2], 1);
	PlayerTextDrawSetShadow(playerid, playerExp[2], 1);
	PlayerTextDrawUseBox(playerid, playerExp[2], 1);
	PlayerTextDrawBoxColor(playerid, playerExp[2], -236);
	PlayerTextDrawTextSize(playerid, playerExp[2], 78.000000, 0.000000);

	playerExp[3] = CreatePlayerTextDraw(playerid, 20.000000, 197.000000, "usebox");
	PlayerTextDrawBackgroundColor(playerid, playerExp[3], 0);
	PlayerTextDrawFont(playerid, playerExp[3], 1);
	PlayerTextDrawLetterSize(playerid, playerExp[3], 0.500000, 0.599999);
	PlayerTextDrawColor(playerid, playerExp[3], 0);
	PlayerTextDrawSetOutline(playerid, playerExp[3], 0);
	PlayerTextDrawSetProportional(playerid, playerExp[3], 1);
	PlayerTextDrawSetShadow(playerid, playerExp[3], 1);
	PlayerTextDrawUseBox(playerid, playerExp[3], 1);
	PlayerTextDrawBoxColor(playerid, playerExp[3], -76);
	PlayerTextDrawTextSize(playerid, playerExp[3], 51.000000, 0.000000);

	playerExp[4] = CreatePlayerTextDraw(playerid, 49.000000, 195.000000, "LVL 1");
	PlayerTextDrawAlignment(playerid, playerExp[4], 2);
	PlayerTextDrawBackgroundColor(playerid, playerExp[4], 0);
	PlayerTextDrawFont(playerid, playerExp[4], 1);
	PlayerTextDrawLetterSize(playerid, playerExp[4], 0.170000, 0.899999);
	PlayerTextDrawColor(playerid, playerExp[4], 2021161215);
	PlayerTextDrawSetOutline(playerid, playerExp[4], 0);
	PlayerTextDrawSetProportional(playerid, playerExp[4], 1);
	PlayerTextDrawSetShadow(playerid, playerExp[4], 1);
	
	return 1;
}

stock createServerInventory() {
	boxDroppedItem1 = TextDrawCreate(327.000000, 258.000000, "F");
	TextDrawBackgroundColor(boxDroppedItem1, 0);
	TextDrawFont(boxDroppedItem1, 1);
	TextDrawLetterSize(boxDroppedItem1, 0.250000, 1.000000);
	TextDrawColor(boxDroppedItem1, 0);
	TextDrawSetOutline(boxDroppedItem1, 0);
	TextDrawSetProportional(boxDroppedItem1, 1);
	TextDrawSetShadow(boxDroppedItem1, 1);
	TextDrawUseBox(boxDroppedItem1, 1);
	TextDrawBoxColor(boxDroppedItem1, -246);
	TextDrawTextSize(boxDroppedItem1, 334.000000, 3.000000);
	TextDrawSetSelectable(boxDroppedItem1, 0);

	boxDroppedItem2 = TextDrawCreate(328.000000, 259.000000, "F");
	TextDrawBackgroundColor(boxDroppedItem2, 0);
	TextDrawFont(boxDroppedItem2, 1);
	TextDrawLetterSize(boxDroppedItem2, 0.240000, 0.799999);
	TextDrawColor(boxDroppedItem2, -1);
	TextDrawSetOutline(boxDroppedItem2, 0);
	TextDrawSetProportional(boxDroppedItem2, 1);
	TextDrawSetShadow(boxDroppedItem2, 1);
	TextDrawUseBox(boxDroppedItem2, 1);
	TextDrawBoxColor(boxDroppedItem2, 150);
	TextDrawTextSize(boxDroppedItem2, 333.000000, 0.000000);
	TextDrawSetSelectable(boxDroppedItem2, 0);

	// Inventário
	textInventory[0] = TextDrawCreate(73.000000, 137.000000, "mdl-1004:inventory_bg");
	TextDrawBackgroundColor(textInventory[0], 255);
	TextDrawFont(textInventory[0], 4);
	TextDrawLetterSize(textInventory[0], 0.500000, 1.000000);
	TextDrawColor(textInventory[0], -26);
	TextDrawSetOutline(textInventory[0], 0);
	TextDrawSetProportional(textInventory[0], 1);
	TextDrawSetShadow(textInventory[0], 1);
	TextDrawUseBox(textInventory[0], 1);
	TextDrawBoxColor(textInventory[0], 255);
	TextDrawTextSize(textInventory[0], 481.000000, 233.000000);
	TextDrawSetSelectable(textInventory[0], 0);

	textInventory[1] = TextDrawCreate(346.000000, 140.000000, "mdl-1004:stats");
	TextDrawBackgroundColor(textInventory[1], 255);
	TextDrawFont(textInventory[1], 4);
	TextDrawLetterSize(textInventory[1], 0.500000, 1.000000);
	TextDrawColor(textInventory[1], -206);
	TextDrawSetOutline(textInventory[1], 0);
	TextDrawSetProportional(textInventory[1], 1);
	TextDrawSetShadow(textInventory[1], 1);
	TextDrawUseBox(textInventory[1], 1);
	TextDrawBoxColor(textInventory[1], 255);
	TextDrawTextSize(textInventory[1], 14.000000, 15.000000);
	TextDrawSetSelectable(textInventory[1], 1);

	textInventory[2] = TextDrawCreate(363.000000, 141.000000, "mdl-1004:condicao");
	TextDrawBackgroundColor(textInventory[2], 255);
	TextDrawFont(textInventory[2], 4);
	TextDrawLetterSize(textInventory[2], 0.500000, 1.000000);
	TextDrawColor(textInventory[2], -206);
	TextDrawSetOutline(textInventory[2], 0);
	TextDrawSetProportional(textInventory[2], 1);
	TextDrawSetShadow(textInventory[2], 1);
	TextDrawUseBox(textInventory[2], 1);
	TextDrawBoxColor(textInventory[2], 255);
	TextDrawTextSize(textInventory[2], 14.000000, 13.000000);
	TextDrawSetSelectable(textInventory[2], 1);

	textInventory[3] = TextDrawCreate(380.000000, 141.000000, "mdl-1004:craft");
	TextDrawBackgroundColor(textInventory[3], 255);
	TextDrawFont(textInventory[3], 4);
	TextDrawLetterSize(textInventory[3], 0.500000, 1.000000);
	TextDrawColor(textInventory[3], -206);
	TextDrawSetOutline(textInventory[3], 0);
	TextDrawSetProportional(textInventory[3], 1);
	TextDrawSetShadow(textInventory[3], 1);
	TextDrawUseBox(textInventory[3], 1);
	TextDrawBoxColor(textInventory[3], 255);
	TextDrawTextSize(textInventory[3], 13.000000, 14.000000);
	TextDrawSetSelectable(textInventory[3], 1);

	textInventory[12] = TextDrawCreate(327.000000, 141.000000, "mdl-1004:book");
	TextDrawBackgroundColor(textInventory[12], 255);
	TextDrawFont(textInventory[12], 4);
	TextDrawLetterSize(textInventory[12], 0.500000, 1.000000);
	TextDrawColor(textInventory[12], -206);
	TextDrawSetOutline(textInventory[12], 0);
	TextDrawSetProportional(textInventory[12], 1);
	TextDrawSetShadow(textInventory[12], 1);
	TextDrawUseBox(textInventory[12], 1);
	TextDrawBoxColor(textInventory[12], 255);
	TextDrawTextSize(textInventory[12], 13.000000, 14.000000);
	TextDrawSetSelectable(textInventory[12], 1);

	textInventory[4] = TextDrawCreate(178.000000, 358.000000, "ld_beat:left");
	TextDrawBackgroundColor(textInventory[4], 255);
	TextDrawFont(textInventory[4], 4);
	TextDrawLetterSize(textInventory[4], 0.500000, 1.000000);
	TextDrawColor(textInventory[4], -206);
	TextDrawSetOutline(textInventory[4], 0);
	TextDrawSetProportional(textInventory[4], 1);
	TextDrawSetShadow(textInventory[4], 1);
	TextDrawUseBox(textInventory[4], 1);
	TextDrawBoxColor(textInventory[4], 255);
	TextDrawTextSize(textInventory[4], 9.000000, 10.000000);
	TextDrawSetSelectable(textInventory[4], 1);

	textInventory[5] = TextDrawCreate(210.000000, 358.000000, "ld_beat:right");
	TextDrawBackgroundColor(textInventory[5], 255);
	TextDrawFont(textInventory[5], 4);
	TextDrawLetterSize(textInventory[5], 0.500000, 1.000000);
	TextDrawColor(textInventory[5], -206);
	TextDrawSetOutline(textInventory[5], 0);
	TextDrawSetProportional(textInventory[5], 1);
	TextDrawSetShadow(textInventory[5], 1);
	TextDrawUseBox(textInventory[5], 1);
	TextDrawBoxColor(textInventory[5], 255);
	TextDrawTextSize(textInventory[5], 9.000000, 10.000000);
	TextDrawSetSelectable(textInventory[5], 1);

	textInventory[6] = TextDrawCreate(407.000000, 358.000000, "ld_beat:left");
	TextDrawBackgroundColor(textInventory[6], 255);
	TextDrawFont(textInventory[6], 4);
	TextDrawLetterSize(textInventory[6], 0.500000, 1.000000);
	TextDrawColor(textInventory[6], -206);
	TextDrawSetOutline(textInventory[6], 0);
	TextDrawSetProportional(textInventory[6], 1);
	TextDrawSetShadow(textInventory[6], 1);
	TextDrawUseBox(textInventory[6], 1);
	TextDrawBoxColor(textInventory[6], 255);
	TextDrawTextSize(textInventory[6], 9.000000, 10.000000);
	TextDrawSetSelectable(textInventory[6], 1);

	textInventory[7] = TextDrawCreate(437.000000, 358.000000, "ld_beat:right");
	TextDrawBackgroundColor(textInventory[7], 255);
	TextDrawFont(textInventory[7], 4);
	TextDrawLetterSize(textInventory[7], 0.500000, 1.000000);
	TextDrawColor(textInventory[7], -206);
	TextDrawSetOutline(textInventory[7], 0);
	TextDrawSetProportional(textInventory[7], 1);
	TextDrawSetShadow(textInventory[7], 1);
	TextDrawUseBox(textInventory[7], 1);
	TextDrawBoxColor(textInventory[7], 255);
	TextDrawTextSize(textInventory[7], 9.000000, 10.000000);
	TextDrawSetSelectable(textInventory[7], 1);

	textInventory[8] = TextDrawCreate(556.000000, 219.000000, "mdl-1004:drop");
	TextDrawBackgroundColor(textInventory[8], 255);
	TextDrawFont(textInventory[8], 4);
	TextDrawLetterSize(textInventory[8], 0.500000, 1.000000);
	TextDrawColor(textInventory[8], -106);
	TextDrawSetOutline(textInventory[8], 0);
	TextDrawSetProportional(textInventory[8], 1);
	TextDrawSetShadow(textInventory[8], 1);
	TextDrawUseBox(textInventory[8], 1);
	TextDrawBoxColor(textInventory[8], 255);
	TextDrawTextSize(textInventory[8], 14.000000, 17.000000);
	TextDrawSetSelectable(textInventory[8], 1);

	textInventory[9] = TextDrawCreate(556.000000, 238.000000, "mdl-1004:split");
	TextDrawBackgroundColor(textInventory[9], 255);
	TextDrawFont(textInventory[9], 4);
	TextDrawLetterSize(textInventory[9], 0.500000, 1.000000);
	TextDrawColor(textInventory[9], -106);
	TextDrawSetOutline(textInventory[9], 0);
	TextDrawSetProportional(textInventory[9], 1);
	TextDrawSetShadow(textInventory[9], 1);
	TextDrawUseBox(textInventory[9], 1);
	TextDrawBoxColor(textInventory[9], 255);
	TextDrawTextSize(textInventory[9], 14.000000, 17.000000);
	TextDrawSetSelectable(textInventory[9], 1);

	textInventory[10] = TextDrawCreate(556.000000, 257.000000, "mdl-1004:info");
	TextDrawBackgroundColor(textInventory[10], 255);
	TextDrawFont(textInventory[10], 4);
	TextDrawLetterSize(textInventory[10], 0.500000, 1.000000);
	TextDrawColor(textInventory[10], -106);
	TextDrawSetOutline(textInventory[10], 0);
	TextDrawSetProportional(textInventory[10], 1);
	TextDrawSetShadow(textInventory[10], 1);
	TextDrawUseBox(textInventory[10], 1);
	TextDrawBoxColor(textInventory[10], 255);
	TextDrawTextSize(textInventory[10], 14.000000, 17.000000);
	TextDrawSetSelectable(textInventory[10], 1);

	textInventory[11] = TextDrawCreate(539.000000, 140.000000, "mdl-1004:close");
	TextDrawBackgroundColor(textInventory[11], 255);
	TextDrawFont(textInventory[11], 4);
	TextDrawLetterSize(textInventory[11], 0.500000, 1.000000);
	TextDrawColor(textInventory[11], -156);
	TextDrawSetOutline(textInventory[11], 0);
	TextDrawSetProportional(textInventory[11], 1);
	TextDrawSetShadow(textInventory[11], 1);
	TextDrawUseBox(textInventory[11], 1);
	TextDrawBoxColor(textInventory[11], 255);
	TextDrawTextSize(textInventory[11], 12.000000, 14.000000);
	TextDrawSetSelectable(textInventory[11], 1);

	// Gas mask / Lanterna
	textGasMask = TextDrawCreate(234.000000, 257.000000, "mdl-1004:mascara");
	TextDrawBackgroundColor(textGasMask, 255);
	TextDrawFont(textGasMask, 4);
	TextDrawLetterSize(textGasMask, 0.500000, 1.000000);
	TextDrawColor(textGasMask, -96);
	TextDrawSetOutline(textGasMask, 0);
	TextDrawSetProportional(textGasMask, 1);
	TextDrawSetShadow(textGasMask, 1);
	TextDrawUseBox(textGasMask, 1);
	TextDrawBoxColor(textGasMask, 255);
	TextDrawTextSize(textGasMask, 17.000000, 19.000000);
	TextDrawSetSelectable(textGasMask, 1);

	textLanterna = TextDrawCreate(234.000000, 284.000000, "mdl-1004:lanterna");
	TextDrawBackgroundColor(textLanterna, 255);
	TextDrawFont(textLanterna, 4);
	TextDrawLetterSize(textLanterna, 0.500000, 1.000000);
	TextDrawColor(textLanterna, -96);
	TextDrawSetOutline(textLanterna, 0);
	TextDrawSetProportional(textLanterna, 1);
	TextDrawSetShadow(textLanterna, 1);
	TextDrawUseBox(textLanterna, 1);
	TextDrawBoxColor(textLanterna, 255);
	TextDrawTextSize(textLanterna, 17.000000, 19.000000);
	TextDrawSetSelectable(textLanterna, 1);
}

stock createPlayerInventory(playerid) {

   	// Verificar se não é um npc
	if (IsPlayerNPC(playerid)) return 1;

	textCameraItem[playerid] = CreatePlayerTextDraw(playerid, 338.000000, 259.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, textCameraItem[playerid], 0);
	PlayerTextDrawFont(playerid, textCameraItem[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textCameraItem[playerid], 0.149998, 0.799996);
	PlayerTextDrawColor(playerid, textCameraItem[playerid], -176);
	PlayerTextDrawSetOutline(playerid, textCameraItem[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textCameraItem[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textCameraItem[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textCameraItem[playerid], 0);

	// Itens do dropados
	p_DropInventory[0] = CreatePlayerTextDraw(playerid, 77.000000, 162.000000, "mdl-1005:8");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[0], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[0], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[0], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[0], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[0], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[0], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[0], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[0], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[0], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[0], 1);

	p_DropInventory[1] = CreatePlayerTextDraw(playerid, 77.000000, 186.000000, "mdl-1005:9");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[1], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[1], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[1], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[1], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[1], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[1], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[1], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[1], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[1], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[1], 1);

	p_DropInventory[2] = CreatePlayerTextDraw(playerid, 77.000000, 210.000000, "mdl-1005:18");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[2], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[2], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[2], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[2], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[2], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[2], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[2], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[2], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[2], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[2], 1);

	p_DropInventory[3] = CreatePlayerTextDraw(playerid, 77.000000, 234.000000, "mdl-1005:4");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[3], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[3], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[3], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[3], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[3], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[3], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[3], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[3], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[3], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[3], 1);

	p_DropInventory[4] = CreatePlayerTextDraw(playerid, 77.000000, 258.000000, "mdl-1005:24");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[4], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[4], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[4], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[4], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[4], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[4], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[4], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[4], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[4], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[4], 1);

	p_DropInventory[5] = CreatePlayerTextDraw(playerid, 77.000000, 282.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[5], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[5], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[5], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[5], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[5], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[5], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[5], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[5], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[5], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[5], 1);

	p_DropInventory[6] = CreatePlayerTextDraw(playerid, 77.000000, 306.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[6], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[6], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[6], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[6], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[6], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[6], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[6], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[6], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[6], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[6], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[6], 1);

	p_DropInventory[7] = CreatePlayerTextDraw(playerid, 77.000000, 330.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_DropInventory[7], 255);
	PlayerTextDrawFont(playerid, p_DropInventory[7], 4);
	PlayerTextDrawLetterSize(playerid, p_DropInventory[7], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_DropInventory[7], -1);
	PlayerTextDrawSetOutline(playerid, p_DropInventory[7], 0);
	PlayerTextDrawSetProportional(playerid, p_DropInventory[7], 1);
	PlayerTextDrawSetShadow(playerid, p_DropInventory[7], 1);
	PlayerTextDrawUseBox(playerid, p_DropInventory[7], 1);
	PlayerTextDrawBoxColor(playerid, p_DropInventory[7], 255);
	PlayerTextDrawTextSize(playerid, p_DropInventory[7], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_DropInventory[7], 1);

	// Itens do inventario
	p_ItensInventory[0] = CreatePlayerTextDraw(playerid, 409.000000, 162.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[0], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[0], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[0], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[0], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[0], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[0], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[0], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[0], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[0], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[0], 1);

	p_ItensInventory[1] = CreatePlayerTextDraw(playerid, 409.000000, 186.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[1], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[1], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[1], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[1], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[1], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[1], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[1], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[1], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[1], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[1], 1);

	p_ItensInventory[2] = CreatePlayerTextDraw(playerid, 409.000000, 210.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[2], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[2], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[2], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[2], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[2], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[2], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[2], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[2], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[2], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[2], 1);

	p_ItensInventory[3] = CreatePlayerTextDraw(playerid, 409.000000, 234.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[3], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[3], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[3], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[3], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[3], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[3], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[3], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[3], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[3], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[3], 1);

	p_ItensInventory[4] = CreatePlayerTextDraw(playerid, 409.000000, 258.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[4], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[4], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[4], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[4], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[4], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[4], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[4], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[4], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[4], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[4], 1);

	p_ItensInventory[5] = CreatePlayerTextDraw(playerid, 409.000000, 282.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[5], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[5], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[5], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[5], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[5], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[5], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[5], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[5], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[5], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[5], 1);

	p_ItensInventory[6] = CreatePlayerTextDraw(playerid, 409.000000, 306.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[6], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[6], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[6], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[6], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[6], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[6], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[6], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[6], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[6], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[6], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[6], 1);

	p_ItensInventory[7] = CreatePlayerTextDraw(playerid, 409.000000, 330.000000, "mdl-1005:34");
	PlayerTextDrawBackgroundColor(playerid, p_ItensInventory[7], 255);
	PlayerTextDrawFont(playerid, p_ItensInventory[7], 4);
	PlayerTextDrawLetterSize(playerid, p_ItensInventory[7], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid, p_ItensInventory[7], -1);
	PlayerTextDrawSetOutline(playerid, p_ItensInventory[7], 0);
	PlayerTextDrawSetProportional(playerid, p_ItensInventory[7], 1);
	PlayerTextDrawSetShadow(playerid, p_ItensInventory[7], 1);
	PlayerTextDrawUseBox(playerid, p_ItensInventory[7], 1);
	PlayerTextDrawBoxColor(playerid, p_ItensInventory[7], 255);
	PlayerTextDrawTextSize(playerid, p_ItensInventory[7], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid, p_ItensInventory[7], 1);

	// Player itens
	textPlayerItens[0][playerid] = CreatePlayerTextDraw(playerid, 433.000000, 169.000000, "Remedio pequeno~n~~n~~n~Remedio pequeno");
	PlayerTextDrawBackgroundColor(playerid, textPlayerItens[0][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerItens[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerItens[0][playerid], 0.170000, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerItens[0][playerid], -76);
	PlayerTextDrawSetOutline(playerid, textPlayerItens[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerItens[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerItens[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerItens[0][playerid], 0);

	textPlayerItens[1][playerid] = CreatePlayerTextDraw(playerid, 530.000000, 169.000000, "1000~n~~n~~n~3");
	PlayerTextDrawBackgroundColor(playerid, textPlayerItens[1][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerItens[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerItens[1][playerid], 0.170000, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerItens[1][playerid], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerItens[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerItens[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerItens[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerItens[1][playerid], 0);

	textPlayerItemHealth[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 176.000000, "100%~n~~n~~n~95%");
	PlayerTextDrawBackgroundColor(playerid, textPlayerItemHealth[playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerItemHealth[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerItemHealth[playerid], 0.129997, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerItemHealth[playerid], -221);
	PlayerTextDrawSetOutline(playerid, textPlayerItemHealth[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerItemHealth[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerItemHealth[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerItemHealth[playerid], 0);

	// Itens no chão
	textPlayerDrop[0][playerid] = CreatePlayerTextDraw(playerid, 101.000000, 169.000000, "item1~n~~n~~n~item2");
	PlayerTextDrawBackgroundColor(playerid, textPlayerDrop[0][playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerDrop[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerDrop[0][playerid], 0.170000, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerDrop[0][playerid], -76);
	PlayerTextDrawSetOutline(playerid, textPlayerDrop[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerDrop[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerDrop[0][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerDrop[0][playerid], 0);

	textPlayerDrop[1][playerid] = CreatePlayerTextDraw(playerid, 198.000000, 169.000000, "0~n~~n~~n~0");
	PlayerTextDrawBackgroundColor(playerid, textPlayerDrop[1][playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerDrop[1][playerid], 1);
	PlayerTextDrawLetterSize(playerid, textPlayerDrop[1][playerid], 0.170000, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerDrop[1][playerid], -106);
	PlayerTextDrawSetOutline(playerid, textPlayerDrop[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerDrop[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerDrop[1][playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerDrop[1][playerid], 0);

	textPlayerDropHealth[playerid] = CreatePlayerTextDraw(playerid, 101.000000, 176.000000, "100%~n~~n~~n~100%");
	PlayerTextDrawBackgroundColor(playerid, textPlayerDropHealth[playerid], 0);
	PlayerTextDrawFont(playerid, textPlayerDropHealth[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerDropHealth[playerid], 0.129997, 0.889998);
	PlayerTextDrawColor(playerid, textPlayerDropHealth[playerid], -221);
	PlayerTextDrawSetOutline(playerid, textPlayerDropHealth[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerDropHealth[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerDropHealth[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerDropHealth[playerid], 0);
	
	// Página atual - Itens
	textPlayerPage[playerid] = CreatePlayerTextDraw(playerid, 426.000000, 358.000000, "1-2");
	PlayerTextDrawAlignment(playerid, textPlayerPage[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerPage[playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerPage[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerPage[playerid], 0.170000, 0.989997);
	PlayerTextDrawColor(playerid, textPlayerPage[playerid], -196);
	PlayerTextDrawSetOutline(playerid, textPlayerPage[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerPage[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerPage[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerPage[playerid], 0);
	
	// Página atual - Drops
	textPlayerPageDrop[playerid] = CreatePlayerTextDraw(playerid, 198.000000, 358.000000, "1-2");
	PlayerTextDrawAlignment(playerid, textPlayerPageDrop[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, textPlayerPageDrop[playerid], 50);
	PlayerTextDrawFont(playerid, textPlayerPageDrop[playerid], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerPageDrop[playerid], 0.170000, 0.989997);
	PlayerTextDrawColor(playerid, textPlayerPageDrop[playerid], -196);
	PlayerTextDrawSetOutline(playerid, textPlayerPageDrop[playerid], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerPageDrop[playerid], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerPageDrop[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerPageDrop[playerid], 0);
	
// Outros
	textPlayerInventory[0] = CreatePlayerTextDraw(playerid, 344.000000, 262.000000, "100%~n~~n~100%~n~~n~100%");
	PlayerTextDrawBackgroundColor(playerid, textPlayerInventory[0], 0);
	PlayerTextDrawFont(playerid, textPlayerInventory[0], 2);
	PlayerTextDrawLetterSize(playerid, textPlayerInventory[0], 0.149998, 0.829998);
	PlayerTextDrawColor(playerid, textPlayerInventory[0], -176);
	PlayerTextDrawSetOutline(playerid, textPlayerInventory[0], 0);
	PlayerTextDrawSetProportional(playerid, textPlayerInventory[0], 1);
	PlayerTextDrawSetShadow(playerid, textPlayerInventory[0], 1);
	PlayerTextDrawSetSelectable(playerid, textPlayerInventory[0], 0);

	textPlayerInventory[1] = CreatePlayerTextDraw(playerid,336.000000, 177.000000, "mdl-1015:9");
	PlayerTextDrawBackgroundColor(playerid,textPlayerInventory[1], 255);
	PlayerTextDrawFont(playerid,textPlayerInventory[1], 4);
	PlayerTextDrawLetterSize(playerid,textPlayerInventory[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textPlayerInventory[1], -206);
	PlayerTextDrawSetOutline(playerid,textPlayerInventory[1], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerInventory[1], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerInventory[1], 1);
	PlayerTextDrawUseBox(playerid,textPlayerInventory[1], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerInventory[1], 255);
	PlayerTextDrawTextSize(playerid,textPlayerInventory[1], 43.000000, 14.000000);
	PlayerTextDrawSetSelectable(playerid,textPlayerInventory[1], 1);

	textPlayerInventory[2] = CreatePlayerTextDraw(playerid,336.000000, 192.000000, "mdl-1015:23");
	PlayerTextDrawBackgroundColor(playerid,textPlayerInventory[2], 255);
	PlayerTextDrawFont(playerid,textPlayerInventory[2], 4);
	PlayerTextDrawLetterSize(playerid,textPlayerInventory[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textPlayerInventory[2], -206);
	PlayerTextDrawSetOutline(playerid,textPlayerInventory[2], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerInventory[2], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerInventory[2], 1);
	PlayerTextDrawUseBox(playerid,textPlayerInventory[2], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerInventory[2], 255);
	PlayerTextDrawTextSize(playerid,textPlayerInventory[2], 43.000000, 14.000000);
	PlayerTextDrawSetSelectable(playerid,textPlayerInventory[2], 1);

	textPlayerInventory[3] = CreatePlayerTextDraw(playerid,336.000000, 207.000000, "mdl-1015:33");
	PlayerTextDrawBackgroundColor(playerid,textPlayerInventory[3], 255);
	PlayerTextDrawFont(playerid,textPlayerInventory[3], 4);
	PlayerTextDrawLetterSize(playerid,textPlayerInventory[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textPlayerInventory[3], -206);
	PlayerTextDrawSetOutline(playerid,textPlayerInventory[3], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerInventory[3], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerInventory[3], 1);
	PlayerTextDrawUseBox(playerid,textPlayerInventory[3], 1);
	PlayerTextDrawBoxColor(playerid,textPlayerInventory[3], 255);
	PlayerTextDrawTextSize(playerid,textPlayerInventory[3], 43.000000, 14.000000);
	PlayerTextDrawSetSelectable(playerid,textPlayerInventory[3], 1);

	textPlayerInventory[4] = CreatePlayerTextDraw(playerid,376.000000, 181.000000, "1~n~~n~23~n~~n~5~n~");
	PlayerTextDrawBackgroundColor(playerid,textPlayerInventory[4], 0);
	PlayerTextDrawFont(playerid,textPlayerInventory[4], 2);
	PlayerTextDrawLetterSize(playerid,textPlayerInventory[4], 0.149998, 0.829998);
	PlayerTextDrawColor(playerid,textPlayerInventory[4], -226);
	PlayerTextDrawSetOutline(playerid,textPlayerInventory[4], 0);
	PlayerTextDrawSetProportional(playerid,textPlayerInventory[4], 1);
	PlayerTextDrawSetShadow(playerid,textPlayerInventory[4], 1);
	PlayerTextDrawSetSelectable(playerid,textPlayerInventory[4], 0);
	
	// Itens equip
	playerItemsEquip[0] = CreatePlayerTextDraw(playerid,299.000000, 166.000000, "mdl-1004:h3");
	PlayerTextDrawBackgroundColor(playerid,playerItemsEquip[0], 255);
	PlayerTextDrawFont(playerid,playerItemsEquip[0], 4);
	PlayerTextDrawLetterSize(playerid,playerItemsEquip[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerItemsEquip[0], -96);
	PlayerTextDrawSetOutline(playerid,playerItemsEquip[0], 0);
	PlayerTextDrawSetProportional(playerid,playerItemsEquip[0], 1);
	PlayerTextDrawSetShadow(playerid,playerItemsEquip[0], 1);
	PlayerTextDrawUseBox(playerid,playerItemsEquip[0], 1);
	PlayerTextDrawBoxColor(playerid,playerItemsEquip[0], 255);
	PlayerTextDrawTextSize(playerid,playerItemsEquip[0], 21.000000, 24.000000);
	PlayerTextDrawSetSelectable(playerid,playerItemsEquip[0], 1);

	playerItemsEquip[1] = CreatePlayerTextDraw(playerid,299.000000, 198.000000, "mdl-1004:a3");
	PlayerTextDrawBackgroundColor(playerid,playerItemsEquip[1], 255);
	PlayerTextDrawFont(playerid,playerItemsEquip[1], 4);
	PlayerTextDrawLetterSize(playerid,playerItemsEquip[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerItemsEquip[1], -96);
	PlayerTextDrawSetOutline(playerid,playerItemsEquip[1], 0);
	PlayerTextDrawSetProportional(playerid,playerItemsEquip[1], 1);
	PlayerTextDrawSetShadow(playerid,playerItemsEquip[1], 1);
	PlayerTextDrawUseBox(playerid,playerItemsEquip[1], 1);
	PlayerTextDrawBoxColor(playerid,playerItemsEquip[1], 255);
	PlayerTextDrawTextSize(playerid,playerItemsEquip[1], 21.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerItemsEquip[1], 1);

	playerItemsEquip[2] = CreatePlayerTextDraw(playerid,274.000000, 198.000000, "mdl-1004:b3");
	PlayerTextDrawBackgroundColor(playerid,playerItemsEquip[2], 255);
	PlayerTextDrawFont(playerid,playerItemsEquip[2], 4);
	PlayerTextDrawLetterSize(playerid,playerItemsEquip[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerItemsEquip[2], -96);
	PlayerTextDrawSetOutline(playerid,playerItemsEquip[2], 0);
	PlayerTextDrawSetProportional(playerid,playerItemsEquip[2], 1);
	PlayerTextDrawSetShadow(playerid,playerItemsEquip[2], 1);
	PlayerTextDrawUseBox(playerid,playerItemsEquip[2], 1);
	PlayerTextDrawBoxColor(playerid,playerItemsEquip[2], 255);
	PlayerTextDrawTextSize(playerid,playerItemsEquip[2], 21.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerItemsEquip[2], 1);
	
	playerHealthProtect = CreatePlayerTextDraw(playerid,317.000000, 181.000000, "000~n~~n~~n~~n~000~n~");
	PlayerTextDrawAlignment(playerid,playerHealthProtect, 3);
	PlayerTextDrawBackgroundColor(playerid,playerHealthProtect, 0);
	PlayerTextDrawFont(playerid,playerHealthProtect, 2);
	PlayerTextDrawLetterSize(playerid,playerHealthProtect, 0.119999, 0.889998);
	PlayerTextDrawColor(playerid,playerHealthProtect, -196);
	PlayerTextDrawSetOutline(playerid,playerHealthProtect, 0);
	PlayerTextDrawSetProportional(playerid,playerHealthProtect, 1);
	PlayerTextDrawSetShadow(playerid,playerHealthProtect, 1);
	PlayerTextDrawSetSelectable(playerid,playerHealthProtect, 0);
	
	// Craft
	playerTextDrawsCraft[0] = CreatePlayerTextDraw(playerid,231.000000, 161.000000, "ld_dual:white");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[0], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[0], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[0], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[0], 168430335);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[0], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[0], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[0], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[0], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[0], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[0], 163.000000, 199.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[0], 0);

	playerTextDrawsCraft[1] = CreatePlayerTextDraw(playerid,243.000000, 172.000000, "mdl-1005:-1006");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[1], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[1], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[1], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[1], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[1], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[1], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[1], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[1], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[1], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[1], 1);

	playerTextDrawsCraft[2] = CreatePlayerTextDraw(playerid,243.000000, 202.000000, "mdl-1005:-1006");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[2], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[2], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[2], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[2], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[2], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[2], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[2], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[2], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[2], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[2], 1);

	playerTextDrawsCraft[3] = CreatePlayerTextDraw(playerid,243.000000, 232.000000, "mdl-1005:-1006");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[3], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[3], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[3], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[3], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[3], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[3], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[3], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[3], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[3], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[3], 1);

	playerTextDrawsCraft[4] = CreatePlayerTextDraw(playerid,243.000000, 262.000000, "mdl-1005:-1006");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[4], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[4], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[4], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[4], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[4], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[4], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[4], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[4], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[4], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[4], 1);

	playerTextDrawsCraft[5] = CreatePlayerTextDraw(playerid,243.000000, 303.000000, "mdl-1005:-1006");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[5], 255);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[5], 4);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[5], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[5], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[5], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[5], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[5], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[5], 255);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[5], 140.000000, 23.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[5], 0);

	playerTextDrawsCraft[6] = CreatePlayerTextDraw(playerid,233.000000, 178.000000, "+~n~~n~~n~+~n~~n~~n~+~n~~n~~n~+");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[6], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[6], 1);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[6], 0.300000, 1.100000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[6], -1);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[6], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[6], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[6], 1);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[6], 0);

	playerTextDrawsCraft[7] = CreatePlayerTextDraw(playerid,306.000000, 293.000000, "~d~ Resultado ~d~");
	PlayerTextDrawAlignment(playerid,playerTextDrawsCraft[7], 2);
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[7], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[7], 2);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[7], 0.170000, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[7], -156);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[7], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[7], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[7], 1);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[7], 0);

	playerTextDrawsCraft[8] = CreatePlayerTextDraw(playerid,268.000000, 178.000000, "Remedio pequeno~n~~n~~n~AAAAA~n~~n~~n~AAAAA1~n~~n~~n~rfwfwger~n~~n~~n~~n~Test");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[8], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[8], 1);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[8], 0.200000, 1.120000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[8], -176);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[8], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[8], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[8], 1);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[8], 0);

	playerTextDrawsCraft[9] = CreatePlayerTextDraw(playerid,298.000000, 341.000000, "  CRAFT");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[9], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[9], 2);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[9], 0.159997, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[9], -156);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[9], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[9], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[9], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[9], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[9], 505290495);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[9], 328.000000, 15.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[9], 1);

	playerTextDrawsCraft[10] = CreatePlayerTextDraw(playerid,259.000000, 341.000000, "RECEITAS");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[10], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[10], 2);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[10], 0.159997, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[10], -206);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[10], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[10], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[10], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[10], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[10], 336860310);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[10], 291.000000, 15.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[10], 1);

	playerTextDrawsCraft[11] = CreatePlayerTextDraw(playerid,335.000000, 341.000000, "   RESET");
	PlayerTextDrawBackgroundColor(playerid,playerTextDrawsCraft[11], 0);
	PlayerTextDrawFont(playerid,playerTextDrawsCraft[11], 2);
	PlayerTextDrawLetterSize(playerid,playerTextDrawsCraft[11], 0.159997, 1.000000);
	PlayerTextDrawColor(playerid,playerTextDrawsCraft[11], -206);
	PlayerTextDrawSetOutline(playerid,playerTextDrawsCraft[11], 0);
	PlayerTextDrawSetProportional(playerid,playerTextDrawsCraft[11], 1);
	PlayerTextDrawSetShadow(playerid,playerTextDrawsCraft[11], 1);
	PlayerTextDrawUseBox(playerid,playerTextDrawsCraft[11], 1);
	PlayerTextDrawBoxColor(playerid,playerTextDrawsCraft[11], 336860310);
	PlayerTextDrawTextSize(playerid,playerTextDrawsCraft[11], 368.000000, 15.000000);
	PlayerTextDrawSetSelectable(playerid,playerTextDrawsCraft[11], 1);
	// Info box
	
	textInfoBox[0][playerid] = CreatePlayerTextDraw(playerid,236.000000, 186.000000, "usebox");
	PlayerTextDrawBackgroundColor(playerid,textInfoBox[0][playerid], 0);
	PlayerTextDrawFont(playerid,textInfoBox[0][playerid], 1);
	PlayerTextDrawLetterSize(playerid,textInfoBox[0][playerid], 0.519999, 12.000000);
	PlayerTextDrawColor(playerid,textInfoBox[0][playerid], 0);
	PlayerTextDrawSetOutline(playerid,textInfoBox[0][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textInfoBox[0][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textInfoBox[0][playerid], 1);
	PlayerTextDrawUseBox(playerid,textInfoBox[0][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textInfoBox[0][playerid], 252645375);
	PlayerTextDrawTextSize(playerid,textInfoBox[0][playerid], 399.000000, -2.000000);

	textInfoBox[1][playerid] = CreatePlayerTextDraw(playerid,391.000000, 188.000000, "x");
	PlayerTextDrawBackgroundColor(playerid,textInfoBox[1][playerid], 0);
	PlayerTextDrawFont(playerid,textInfoBox[1][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textInfoBox[1][playerid], 0.219999, 0.899999);
	PlayerTextDrawColor(playerid,textInfoBox[1][playerid], -6946561);
	PlayerTextDrawSetOutline(playerid,textInfoBox[1][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textInfoBox[1][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textInfoBox[1][playerid], 1);
	PlayerTextDrawUseBox(playerid,textInfoBox[1][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textInfoBox[1][playerid], 168430335);
	PlayerTextDrawTextSize(playerid,textInfoBox[1][playerid], 397.000000, 10.000000);
	PlayerTextDrawSetSelectable(playerid,textInfoBox[1][playerid], 1);

	textInfoBox[2][playerid] = CreatePlayerTextDraw(playerid,239.000000, 202.000000, "Descricao do item");
	PlayerTextDrawBackgroundColor(playerid,textInfoBox[2][playerid], 0);
	PlayerTextDrawFont(playerid,textInfoBox[2][playerid], 2);
	PlayerTextDrawLetterSize(playerid,textInfoBox[2][playerid], 0.150000, 0.899999);
	PlayerTextDrawColor(playerid,textInfoBox[2][playerid], -136);
	PlayerTextDrawSetOutline(playerid,textInfoBox[2][playerid], 0);
	PlayerTextDrawSetProportional(playerid,textInfoBox[2][playerid], 1);
	PlayerTextDrawSetShadow(playerid,textInfoBox[2][playerid], 1);
	PlayerTextDrawUseBox(playerid,textInfoBox[2][playerid], 1);
	PlayerTextDrawBoxColor(playerid,textInfoBox[2][playerid], 0);
	PlayerTextDrawTextSize(playerid,textInfoBox[2][playerid], 396.000000, 30.000000);
	
	// Condições
	textInventoryCondicao = CreatePlayerTextDraw(playerid, 237.000000, 164.000000, "Vida: 0%~n~~n~Fome: 0%~n~~n~Sede: 0%~n~~n~Radiacao: 0%~n~~n~Corpo: Nenhum problema~n~~n~Sangramento: 0%~n~~n~Virus Zombie: 0%");
	PlayerTextDrawBackgroundColor(playerid, textInventoryCondicao, 0);
	PlayerTextDrawFont(playerid, textInventoryCondicao, 2);
	PlayerTextDrawLetterSize(playerid, textInventoryCondicao, 0.159999, 0.899999);
	PlayerTextDrawColor(playerid, textInventoryCondicao, -7786);
	PlayerTextDrawSetOutline(playerid, textInventoryCondicao, 0);
	PlayerTextDrawSetProportional(playerid, textInventoryCondicao, 1);
	PlayerTextDrawSetShadow(playerid, textInventoryCondicao, 1);
	PlayerTextDrawSetSelectable(playerid, textInventoryCondicao, 0);
	return 1;
}
