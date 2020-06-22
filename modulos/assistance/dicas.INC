// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 

new PlayerText:textAsssit1;
new PlayerText:textAsssit2;

stock const assistPlayerGame[][] = {
	{ "Nenhuma" },
	{ "Aperte a tecla ~b~~h~Y ~w~~h~para abrir seu inventario. Clique duas vezes rapidamente no item para usa-lo ou mover para sua mochila." },
	{ "Ao pressionar a tecla ~b~~h~N ~w~~h~voce vera um menu com varias opcoes, cada botao com uma funcao unica." },
	{ "Voce ganha experiencia passivamente, coletando recursos, cacando, matando zombies ou players entre varias outras formas." },
	{ "Para criar uma base, basta apertar a tecla ~b~~h~N ~w~~h~e escolher a opcao CRAFT. Certifique-se de ter os recursos necessarios para adicionar objetos." },
	{ "Use o comando ~b~~h~/ajuda ~w~~h~para ver os principais comandos do servidor. Caso precise de ajuda administrativa use ~b~~h~/suporte ~w~~h~e aguarde um admin lhe atender." }
};

stock ASSIST_Next(playerid)
{
	if (PlayerData[playerid][dAssistId] < sizeof assistPlayerGame - 1)
	{
	    PlayerData[playerid][dAssistId] ++;
	    
	    PlayerTextDrawSetString(playerid, textAsssit2, assistPlayerGame[PlayerData[playerid][dAssistId]]);
	    
	    PlayerTextDrawShow(playerid, textAsssit1);
	    PlayerTextDrawShow(playerid, textAsssit2);
	    
	    // timer
	    SetTimerEx("hidePlayerAssistance", 10000, false, "d", playerid);
	}
}

callback hidePlayerAssistance(playerid)
{
	PlayerTextDrawHide(playerid, textAsssit1);
	PlayerTextDrawHide(playerid, textAsssit2);
}

stock ASSIST_CreateTextDraws(playerid)
{
	textAsssit1 = CreatePlayerTextDraw(playerid,12.000000, 183.000000, "mdl-1019:v1");
	PlayerTextDrawBackgroundColor(playerid,textAsssit1, 255);
	PlayerTextDrawFont(playerid,textAsssit1, 4);
	PlayerTextDrawLetterSize(playerid,textAsssit1, 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,textAsssit1, -1);
	PlayerTextDrawSetOutline(playerid,textAsssit1, 0);
	PlayerTextDrawSetProportional(playerid,textAsssit1, 1);
	PlayerTextDrawSetShadow(playerid,textAsssit1, 1);
	PlayerTextDrawUseBox(playerid,textAsssit1, 1);
	PlayerTextDrawBoxColor(playerid,textAsssit1, 255);
	PlayerTextDrawTextSize(playerid,textAsssit1, 139.000000, 74.000000);
	PlayerTextDrawSetSelectable(playerid,textAsssit1, 0);

	textAsssit2 = CreatePlayerTextDraw(playerid,45.000000, 203.000000, "Aperte a tecla Y para abrir seu inventario. Clique rapidamente duas vezes no item para usa-lo ou mover para seu inventario.");
	PlayerTextDrawBackgroundColor(playerid,textAsssit2, 0);
	PlayerTextDrawFont(playerid,textAsssit2, 1);
	PlayerTextDrawLetterSize(playerid,textAsssit2, 0.170000, 0.899999);
	PlayerTextDrawColor(playerid,textAsssit2, -76);
	PlayerTextDrawSetOutline(playerid,textAsssit2, 0);
	PlayerTextDrawSetProportional(playerid,textAsssit2, 1);
	PlayerTextDrawSetShadow(playerid,textAsssit2, 1);
	PlayerTextDrawUseBox(playerid,textAsssit2, 1);
	PlayerTextDrawBoxColor(playerid,textAsssit2, -256);
	PlayerTextDrawTextSize(playerid,textAsssit2, 147.000000, 5.000000);
	PlayerTextDrawSetSelectable(playerid,textAsssit2, 0);
}
