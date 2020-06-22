
stock AddNicknameToWhitelist(nickname[], adminname[])
{
	new query[128];
	format(query, sizeof (query), "UPDATE accounts SET whitelist = 1 WHERE nome = '%s'", nickname, adminname);
	db_free_result(db_query(serverDB, query));
}

stock RemoveNicknameFromWhitelist(nickname[])
{
	new query[95];
	format(query, sizeof (query), "UPDATE accounts SET whitelist = 0 WHERE nome = '%s'", nickname);
	db_free_result(db_query(serverDB, query));
}

stock IsNicknameInWhitelist(nickname[])
{
	new query[95];
	new bool:return_result = false;
	format(query, sizeof (query), "SELECT id FROM accounts WHERE nome = '%s' AND whitelist = 1", nickname);
	new DBResult:db_whitelist = db_query(serverDB, query);
	
	if (db_num_rows(db_whitelist) > 0)
	{
	    return_result = true;
	}
	db_free_result(db_whitelist);
	return return_result;
}

stock checkWhitelistAccount(playerid)
{
	if (!serverWhitelistActive)
	    return 1;
	    
	if (IsNicknameInWhitelist(getNome(playerid)))
		return 1;

	WhitelistDialog(playerid);

	return 0;
}

stock WhitelistDialog(playerid)
{
	stringGlobal[0] = EOS;

	if (!strcmp(GetPlayerLanguage(playerid), "Portugues")) {
		strcat(stringGlobal, "{FFFF00}WHITELIST ATIVADA:\n\n");
		strcat(stringGlobal, "{FFFFFF}Para jogar neste servidor seu nick precisa estar adicionado à whitelist.\n");
		strcat(stringGlobal, "{FFFFFF}Acesse nosso discord e comente seu nick no canal {00BBFF}whitelist{FFFFFF} para ser aceito.\n");
		strcat(stringGlobal, "{FFFFFF}Caso você já esteja adicionado a whitelist, tente alguma das opções abaixo:\n\n");

		strcat(stringGlobal, "{777777}\t× Verifique se você digitou seu nick corretamente\n");
		strcat(stringGlobal, "{777777}\t× Lembrando que letras maiúsculas diferenciam de minúsculas\n");
		strcat(stringGlobal, "{777777}\t× Entre em contato com algum administrador em nosso fórum\n");
		strcat(stringGlobal, "{777777}\t× Reconecte e tente fazer login novamente no servidor\n\n");
	}
	else if (!strcmp(GetPlayerLanguage(playerid), "English")) {
		strcat(stringGlobal, "{FFFF00}WHITELIST ON:\n\n");
		strcat(stringGlobal, "{FFFFFF}To play on this server your nick must be added to the whitelist.\n");
		strcat(stringGlobal, "{FFFFFF}Access our discord and comment your nick on channel {00BBFF}whitelist{FFFFFF} to be accepted.\n");
		strcat(stringGlobal, "{FFFFFF}If you're already added to the whitelist, try one of the options below:\n\n");

		strcat(stringGlobal, "{777777}\t× Make sure you entered your nick correctly\n");
		strcat(stringGlobal, "{777777}\t× Remembering that upper case letters are case sensitive\n");
		strcat(stringGlobal, "{777777}\t× Contact any administrator in our forum\n");
		strcat(stringGlobal, "{777777}\t× Reconnect and try to log back on the server\n\n");
	}
	else if (!strcmp(GetPlayerLanguage(playerid), "Espanhol")) {
		strcat(stringGlobal, "{FFFF00}WHITELIST ACTIVADA:\n\n");
		strcat(stringGlobal, "{FFFFFF}Para jugar en este servidor su nick necesita ser agregado a whitelist.\n");
		strcat(stringGlobal, "{FFFFFF}Accede a nuestro discord y comente su nick en el canal {00BBFF}whitelist{FFFFFF} para ser aceptado.\n");
		strcat(stringGlobal, "{FFFFFF}Si ya está agregado a whitelist, pruebe alguna de las siguientes opciones:\n\n");

		strcat(stringGlobal, "{777777}\t× Compruebe que ha introducido su nick correctamente\n");
		strcat(stringGlobal, "{777777}\t× Recordando que las letras mayúsculas difieren de minúsculas\n");
		strcat(stringGlobal, "{777777}\t× Contacta con algún administrador en nuestro foro\n");
		strcat(stringGlobal, "{777777}\t× Vuelva a conectar e intente iniciar sesión de nuevo en el servidor\n\n");
	}

	strcat(stringGlobal, "{FFFFFF}Link do DISCORD: {00BBFF}discord.gg/Bvux5T6");

	ShowPlayerDialog(playerid, 145, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Ok", "");
}

