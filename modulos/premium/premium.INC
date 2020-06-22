
#define SHOP_TYPE_PREMIUM  	(1)
#define SHOP_TYPE_BOOST_2X  (2)
#define SHOP_TYPE_BOOST_3X  (3)
#define SHOP_TYPE_BOOST_4X  (4)
#define SHOP_TYPE_BOOST_5X  (5)

const
	per_day_premium 	= 800,
	per_day_boost_2x 	= 400,
	per_day_boost_3x 	= 500,
	per_day_boost_4x 	= 700,
	per_day_boost_5x 	= 1000
	;

stock const p_PremiumAccount[] = {
//  days
	5,
	10,
	15,
	20,
	25,
	30
};

CMD:menuzp(playerid) {
    ShowPlayerDialogPremium(playerid);
	return 1;
}
stock ShowPlayerDialogPremium(playerid) {

	stringGlobal[0] = EOS;
	
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Conta premium\n");
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Boost de xp (2x)\n");
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Boost de xp (3x)\n");
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Boost de xp (4x)\n");
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Boost de xp (5x)\n");
	strcat(stringGlobal, "{AA0000}Z Points: {AAAAAA}Transferir\n");
	
	return ShowPlayerDialog(playerid, DIALOG_SHOP_ZP, DIALOG_STYLE_TABLIST, "Z Nation: Shop", stringGlobal, "Selecionar", "Cancelar");
}

stock SetPlayerPremium(playerid, days) {

	new newdate = PlayerData[playerid][dPremium];

	if (newdate < gettime())
	    newdate = gettime();

	if (days >= 5)
	{
	    if (!SHOP_IsPlayerHaveSkinId(playerid, 22007))
	    {
	        SHOP_GiveItem(playerid, 22007, 0, SKIN_RARITY_LEGACY, .gender = SKIN_GENDER_MALE, .time = -1, .legacy = 1, .name = "John Wick");
	    }
	}

	PlayerData[playerid][dPremium] = newdate + (days * 86400);
	
	SavePlayerAccountPremium(playerid);
}

stock SetPlayerXpBoost(playerid, boost, days) {
    if (GetPlayerXpBoost(playerid) >= boost)
        return SendClientMessage(playerid, corError, "ERRO: {999999}Você já tem um bônus de XP igual ou maior ativado, aguarde acabar para ativar outro."), 0;
        
	new newdate = PlayerData[playerid][dBoostExpire];

	if (newdate < gettime() || PlayerData[playerid][dBoostXp] < boost)
	    newdate = gettime();
        
    PlayerData[playerid][dBoostXp]     = boost;
    PlayerData[playerid][dBoostExpire] = newdate + (days * 86400);
        
    SavePlayerAccountPremium(playerid);
        
	return 1;
}

stock IsPlayerPremium(playerid) {
	return (PlayerData[playerid][dPremium] > gettime());
}

stock GetPlayerXpBoost(playerid) {
	if (gettime() < PlayerData[playerid][dBoostExpire]) {
	    return PlayerData[playerid][dBoostXp];
	}
	else if (IsPlayerPremium(playerid)) {
	    return 2;
	}
	return 1;
}

stock GetPlayerExpireBoost(playerid) {
	new string[75] = "Nunca";

	if (GetPlayerXpBoost(playerid) > 1) {
	    format(string, sizeof string, ConvertBanDate(PlayerData[playerid][dBoostExpire] - gettime()));
	} 

	return string;
}

stock GetPlayerExpirePremium(playerid) {
	new string[75] = "Nunca";

	if (IsPlayerPremium(playerid)) {
	    format(string, sizeof string, ConvertBanDate(PlayerData[playerid][dPremium] - gettime()));
	}

	return string;
}

stock SavePlayerAccountPremium(playerid) {
	new query[185];
	format(query, sizeof query, "UPDATE accounts SET boostxp = '%d', boostexpire = '%d', premium = '%d' WHERE nome = '%s'", PlayerData[playerid][dBoostXp],
	PlayerData[playerid][dBoostExpire], PlayerData[playerid][dPremium], getNome(playerid));
	db_free_result(db_query(serverDB, query));
}

stock LoadPlayerAccountPremium(playerid) {
	new query[95], DBResult:query_result;
	format(query, sizeof query, "SELECT boostxp,boostexpire,premium FROM accounts WHERE nome = '%s'", getNome(playerid));
	// query
	query_result = db_query(serverDB, query);
	
	if (db_num_rows(query_result)) {
	    PlayerData[playerid][dBoostXp] 		= db_get_field_assoc_int(query_result, "boostxp");
	    PlayerData[playerid][dBoostExpire] 	= db_get_field_assoc_int(query_result, "boostexpire");
	    PlayerData[playerid][dPremium] 		= db_get_field_assoc_int(query_result, "premium");
	}
	
	db_free_result(query_result);
}



















