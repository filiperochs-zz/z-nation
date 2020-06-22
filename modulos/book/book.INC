// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
#define MAX_BOOK_PAGES 8

stock const Float: spawnsBookPages[MAX_BOOK_PAGES][3] = {
//{0.00000, 0.0000000, 0.000000},
{274.32031, 1879.09058, -31.36900},
{-789.22888, 2767.77539, 47.28980},
{-1852.19019, -1699.29224, 39.91370},
{715.83801, -1700.48877, 1.46560},
{2262.80688, -757.16980, 37.04920},
{2323.65186, 35.12900, 30.52090},
{1270.94849, 298.18921, 18.59340},
{-1248.56580, 499.67801, 17.26870}
};

stock const spawnsBookPagesNames[MAX_BOOK_PAGES][] = {
{ "mdl-1029:page1" },
{ "mdl-1029:page2" },
{ "mdl-1030:page3" },
{ "mdl-1030:page4" },
{ "mdl-1031:page5" },
{ "mdl-1031:page6" },
{ "mdl-1032:page7" },
{ "mdl-1032:page8" }
};

stock playerBookPages[MAX_PLAYERS][MAX_BOOK_PAGES];

stock playerBookObject[MAX_PLAYERS][MAX_BOOK_PAGES];

stock playerBookArea[MAX_PLAYERS][MAX_BOOK_PAGES];

stock playerBookCurrentPage[MAX_PLAYERS];

stock PlayerText:bookPlayerTextdraw[8];

stock bookResetForPlayer(playerid)
{
	for(new index; index < MAX_BOOK_PAGES; index++)
	{
	    playerBookPages [playerid] [index]  = 0 ;
	    
		playerBookObject [playerid] [index] = -1 ;

		playerBookArea [playerid] [index] = -1 ;
	}
}

stock bookSpawnForPlayer(player)
{
	for(new index; index < MAX_BOOK_PAGES; index++)
	{
	    if ( !playerBookPages [player] [index] )
	    {
	        playerBookObject [player] [index] = CreateDynamicObject(-1033, spawnsBookPages[index][0], spawnsBookPages[index][1], spawnsBookPages[index][2] + 0.1, 0.0, 0.0, random(360), .worldid = 0, .playerid = player);

            playerBookArea [player] [index] = CreateDynamicSphere(spawnsBookPages[index][0], spawnsBookPages[index][1], spawnsBookPages[index][2], 1.8, .worldid = 0, .playerid = player);
		}
	}
}

stock bookDestroyForPlayer(playerid, index)
{
	DestroyDynamicObject(playerBookObject [playerid] [index]);
	
	DestroyDynamicArea(playerBookArea [playerid] [index]);
	
	playerBookObject [playerid] [index] = -1 ;

	playerBookArea [playerid] [index] = -1 ;
}

stock bookDestroyAllForPlayer(playerid)
{
	for(new index; index < MAX_BOOK_PAGES; index++)
	{
	    if ( !playerBookPages [playerid] [index] )
	    {
	        bookDestroyForPlayer(playerid, index);
		}
	}
}

public OnPlayerEnterDynamicArea(playerid, areaid) {

	for(new index; index < MAX_BOOK_PAGES; index++)
	{
	    if ( playerBookArea [playerid] [index] == areaid ) {

		    if ( !playerBookPages [playerid] [index] )
		    {
		        bookDestroyForPlayer(playerid, index);

		       	playerBookPages [playerid] [index] = 1 ;

		      	bookShowForPlayer(playerid, bookCountPagesDiscover(playerid)) ;

		      	bookSavePlayerAccount(playerid) ;

	       		// set facing to point and apply animation
		       	SetPlayerFaceToPoint(playerid, spawnsBookPages[index][0], spawnsBookPages[index][1]);

                ApplyAnimation(playerid, "BOMBER","BOM_Plant_2Idle",4.1,0,1,1,0,0);
	     	}
	     	break ;
	    }
	}

	#if defined boOnPlayerEnterDynamicArea
	    return boOnPlayerEnterDynamicArea(playerid, areaid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerEnterDynamicArea
	#undef OnPlayerEnterDynamicArea
#else
	#define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea boOnPlayerEnterDynamicArea
#if defined boOnPlayerEnterDynamicArea
	forward boOnPlayerEnterDynamicArea(playerid, areaid);
#endif

stock bookSavePlayerAccount(playerid)
{
	new fileAccount[115];
	new pagesResult[95];

	// Encryptar a senha
	format(pagesResult, sizeof pagesResult, "%d,%d,%d,%d,%d,%d,%d,%d", playerBookPages [playerid] [0], playerBookPages [playerid] [1], playerBookPages [playerid] [2],
	playerBookPages [playerid] [3], playerBookPages [playerid] [4], playerBookPages [playerid] [5], playerBookPages [playerid] [6], playerBookPages [playerid] [7]);

	format(fileAccount, sizeof fileAccount, "UPDATE accounts SET book = '%s' WHERE nome = '%s'", pagesResult, getNome(playerid));

	db_free_result(db_query(serverDB, fileAccount));
}

stock bookCountPagesDiscover(playerid)
{
	new count = -1;
	
	for(new index; index < MAX_BOOK_PAGES; index++)
	{
	    if ( playerBookPages [playerid] [index] )
	    {
	        count ++;
		}
	}
	
	return count;
}

stock bookSetPageForPlayer(playerid)
{
	new currentBookPage = playerBookCurrentPage[playerid];
	new currentPagesDiscover = bookCountPagesDiscover(playerid);

    if ( currentBookPage > -1 ) {
        PlayerTextDrawSetString (playerid, bookPlayerTextdraw [3], currentPagesDiscover >= currentBookPage ? ( spawnsBookPagesNames[currentBookPage] ) : ( "mdl-1029:discover" )) ;
    } else {
        PlayerTextDrawSetString (playerid, bookPlayerTextdraw [3], "mdl-1029:page0") ;
    }

    if ( (currentBookPage - 1) < -1 ) {
    	PlayerTextDrawSetString (playerid, bookPlayerTextdraw [1], "mdl-0000:none" ) ;
    } else {
      	if ( (currentBookPage - 1) > -1 ) {
      		PlayerTextDrawSetString (playerid, bookPlayerTextdraw [1], currentPagesDiscover >= (currentBookPage - 1) ? ( spawnsBookPagesNames[currentBookPage - 1] ) : ( "mdl-1029:discover" )) ;
		} else {
		    PlayerTextDrawSetString (playerid, bookPlayerTextdraw [1], "mdl-1029:page0" ) ;
		}
    }

    if ( (currentBookPage + 1) >= MAX_BOOK_PAGES ) {
       	PlayerTextDrawSetString (playerid, bookPlayerTextdraw [2], "mdl-0000:none" ) ;
    } else {
     	PlayerTextDrawSetString (playerid, bookPlayerTextdraw [2], currentPagesDiscover >= (currentBookPage + 1) ? ( spawnsBookPagesNames[currentBookPage + 1] ) : ( "mdl-1029:discover" )) ;
   	}

   	if (currentBookPage == -1) {
   	    PlayerTextDrawSetString(playerid, bookPlayerTextdraw[6], "capa do livro");
   	} else {
   	    new bookPageString[25];
   	    format(bookPageString, sizeof bookPageString, "%d-%d", currentBookPage + 1, MAX_BOOK_PAGES);
   	    PlayerTextDrawSetString(playerid, bookPlayerTextdraw[6], bookPageString);
	}
}

stock bookShowForPlayer(playerid, page = -1)
{
	if (GetPVarInt(playerid, "bPlayerBookShow"))
	    return 0;
	    
	hideInventory(playerid, .cancelselect = 0);
	    
    playerBookCurrentPage [playerid] = page ;
	    
	for(new textdraw; textdraw < sizeof bookPlayerTextdraw; textdraw++)
	{
	    PlayerTextDrawShow (playerid, bookPlayerTextdraw [textdraw] ) ;
	}
	
	bookSetPageForPlayer (playerid ) ;
	
	SelectTextDraw (playerid, 0xFFFFFF55 ) ;
	
	SetPVarInt (playerid, "bPlayerBookShow", 1 ) ;
	
	return 1;
}

stock bookHideForPlayer(playerid)
{
	if (!GetPVarInt(playerid, "bPlayerBookShow"))
	    return 0;

	for(new textdraw; textdraw < sizeof bookPlayerTextdraw; textdraw++)
	{
	    PlayerTextDrawHide (playerid, bookPlayerTextdraw [textdraw] ) ;
	}
	
	CancelSelectTextDraw(playerid);
	
	DeletePVar (playerid, "bPlayerBookShow" ) ;
	
	return 1;
}

stock bookCreatePlayerTextDraws(playerid)
{
	bookPlayerTextdraw[0] = CreatePlayerTextDraw(playerid,-10.000000, -10.000000, "usebox");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[0], 0);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[0], 1);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[0], 0.500000, 54.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[0], 0);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[0], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[0], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[0], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[0], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[0], 245);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[0], 680.000000, 0.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[0], 0);

	bookPlayerTextdraw[1] = CreatePlayerTextDraw(playerid,129.000000, 160.000000, "mdl-1030:page4");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[1], 255);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[1], 4);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[1], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[1], 842150655);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[1], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[1], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[1], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[1], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[1], 255);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[1], 180.000000, 220.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[1], 0);

	bookPlayerTextdraw[2] = CreatePlayerTextDraw(playerid,319.000000, 160.000000, "mdl-1030:page3");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[2], 255);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[2], 4);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[2], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[2], 842150655);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[2], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[2], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[2], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[2], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[2], 255);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[2], 180.000000, 220.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[2], 0);

	bookPlayerTextdraw[3] = CreatePlayerTextDraw(playerid,205.000000, 140.000000, "mdl-1032:page8");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[3], 255);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[3], 4);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[3], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[3], -1);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[3], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[3], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[3], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[3], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[3], 255);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[3], 223.000000, 275.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[3], 0);

	bookPlayerTextdraw[4] = CreatePlayerTextDraw(playerid,102.000000, 251.000000, "ld_beat:left");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[4], 255);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[4], 4);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[4], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[4], -226);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[4], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[4], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[4], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[4], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[4], 255);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[4], 23.000000, 38.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[4], 1);

	bookPlayerTextdraw[5] = CreatePlayerTextDraw(playerid,503.000000, 251.000000, "ld_beat:right");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[5], 255);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[5], 4);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[5], 0.500000, 1.000000);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[5], -226);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[5], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[5], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[5], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[5], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[5], 255);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[5], 23.000000, 38.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[5], 1);
	
	bookPlayerTextdraw[6] = CreatePlayerTextDraw(playerid,319.000000, 418.000000, "2-8");
	PlayerTextDrawAlignment(playerid,bookPlayerTextdraw[6], 2);
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[6], 0);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[6], 0);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[6], 0.349999, 1.499999);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[6], -156);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[6], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[6], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[6], 1);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[6], 0);

	bookPlayerTextdraw[7] = CreatePlayerTextDraw(playerid,479.000000, 128.000000, " X");
	PlayerTextDrawBackgroundColor(playerid,bookPlayerTextdraw[7], 0);
	PlayerTextDrawFont(playerid,bookPlayerTextdraw[7], 2);
	PlayerTextDrawLetterSize(playerid,bookPlayerTextdraw[7], 0.260000, 1.499999);
	PlayerTextDrawColor(playerid,bookPlayerTextdraw[7], -226);
	PlayerTextDrawSetOutline(playerid,bookPlayerTextdraw[7], 0);
	PlayerTextDrawSetProportional(playerid,bookPlayerTextdraw[7], 1);
	PlayerTextDrawSetShadow(playerid,bookPlayerTextdraw[7], 1);
	PlayerTextDrawUseBox(playerid,bookPlayerTextdraw[7], 1);
	PlayerTextDrawBoxColor(playerid,bookPlayerTextdraw[7], 252645375);
	PlayerTextDrawTextSize(playerid,bookPlayerTextdraw[7], 492.000000, 15.000000);
	PlayerTextDrawSetSelectable(playerid,bookPlayerTextdraw[7], 1);
}
