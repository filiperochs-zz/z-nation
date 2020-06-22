// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 
// Download > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - > www.dominiosamp.net - 

stock banAccount(name[], banip[], admin[], reason[], unban = 0) {

	new sql_string[256],
		sql_today[6],
		sql_data[75];
		
	getdate(sql_today[2], sql_today[1], sql_today[0]);
	gettime(sql_today[3], sql_today[4], sql_today[5]);
	
	format(sql_data, sizeof (sql_data), "%02d/%02d/%04d - %02d:%02d:%02d", sql_today[0], sql_today[1], sql_today[2], sql_today[3], sql_today[4], sql_today[5]);

	format(sql_string, sizeof (sql_string), "INSERT INTO `ban` (`name`,`ip`,`admin`,`reason`,`date`,`unban`) VALUES ('%s','%s','%s','%s','%s','%d')",
	name, banip, admin, reason, sql_data, unban);
	
	db_free_result(db_query(serverDB, sql_string));
	return 1;
}

stock unbanAccount(name[]) {

	new sql_string[75];

	format(sql_string, sizeof (sql_string), "DELETE FROM `ban` WHERE `name` = '%s'", name);
	db_free_result(db_query(serverDB, sql_string));
	
	return 1;
}

stock unbanIp(name[]) {

	new sql_string[75];

	format(sql_string, sizeof (sql_string), "DELETE FROM `ban` WHERE `ip` = '%s'", name);
	db_free_result(db_query(serverDB, sql_string));

	return 1;
}

stock isAccoundBanned(name[]) {

	new sql_string[128], DBResult:sql_result;
	
	format(sql_string, sizeof (sql_string), "SELECT * FROM `ban` WHERE `name` = '%s' LIMIT 1", name);
	sql_result = db_query(serverDB, sql_string);
	
	new sql_rows = db_num_rows(sql_result);
	
	db_free_result(sql_result);

	return sql_rows;
}

stock isIpBanned(banip[]) {

	new sql_string[128], DBResult:sql_result;

	format(sql_string, sizeof (sql_string), "SELECT * FROM `ban` WHERE `ip` = '%s' LIMIT 1", banip);
	sql_result = db_query(serverDB, sql_string);

	new sql_rows = db_num_rows(sql_result);

	db_free_result(sql_result);

	return sql_rows;
}

stock checkBannedAccount(playerid) {

    new
	    sql_string[128], DBResult:sql_result;

	// Checar se o nick está banido
	if (isAccoundBanned(getNome(playerid))) {
	
		format(sql_string, sizeof (sql_string), "SELECT * FROM `ban` WHERE `name` = '%s' LIMIT 1", getNome(playerid));
	
		sql_result = db_query(serverDB, sql_string);
	
	    new unban = db_get_field_assoc_int(sql_result, "unban");
	
	    printf("NAME: unban: %d  gettime: %d", unban, gettime());
	
	    if (unban != 0 && gettime() > unban) {
	    
	        db_free_result(sql_result);
	        
	        unbanAccount(getNome(playerid));
	        
	        SendClientMessage(playerid, corVermelhoClaro, "Você foi desbanido do servidor.");
	    
	        return 0;
	    }
	    
	    stringGlobal[0] = EOS;
	    
	    strcat(stringGlobal, "{FF3300}| ----------------  Você está banido do servidor  --------------- |\n");
	    format(sql_string, sizeof (sql_string), "| Nome: %s\n", sql_getstring(sql_result, "name"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| IP: %s\n", sql_getstring(sql_result, "ip"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| Admin: %s\n", sql_getstring(sql_result, "admin"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| Motivo: %s\n", sql_getstring(sql_result, "reason"));
	    strcat(stringGlobal, sql_string);
	    if (unban == 0) {
	        format(sql_string, sizeof (sql_string), "| Desban: Nunca\n");
	    } else {
	    	format(sql_string, sizeof (sql_string), "| Desban: %s\n", ConvertBanDate(unban - gettime()));
		}
	    strcat(stringGlobal, sql_string);
	    strcat(stringGlobal, "{FF3300}| --------------------------------------------------------------- |\n");
	
	    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Fechar", "");
	
		db_free_result(sql_result);
	
	    return 1;
	}

	// Checar se o IP está banido
	else if (isIpBanned(getIp(playerid))) {
	
		format(sql_string, sizeof (sql_string), "SELECT * FROM `ban` WHERE `ip` = '%s' LIMIT 1", getIp(playerid));

		sql_result = db_query(serverDB, sql_string);

	    new unban = db_get_field_assoc_int(sql_result, "unban");

        printf("IP: unban: %d  gettime: %d", unban, gettime());

	    if (unban != 0 && gettime() > unban) {

	        db_free_result(sql_result);

	        unbanAccount(getNome(playerid));

            SendClientMessage(playerid, corInfo, "Você foi desbanido do servidor.");

	        return 0;
	    }

	    stringGlobal[0] = EOS;

	    strcat(stringGlobal, "{FF3300}| ----------------  Você está banido do servidor  --------------- |\n");
	    format(sql_string, sizeof (sql_string), "| Nome: %s\n", sql_getstring(sql_result, "name"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| IP: %s\n", sql_getstring(sql_result, "ip"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| Admin: %s\n", sql_getstring(sql_result, "admin"));
	    strcat(stringGlobal, sql_string);
	    format(sql_string, sizeof (sql_string), "| Motivo: %s\n", sql_getstring(sql_result, "reason"));
	    strcat(stringGlobal, sql_string);
	    if (unban == 0) {
	        format(sql_string, sizeof (sql_string), "| Desban: Nunca\n");
	    } else {
	    	format(sql_string, sizeof (sql_string), "| Desban: %s\n", ConvertBanDate(unban - gettime()));
		}
	    strcat(stringGlobal, sql_string);
	    strcat(stringGlobal, "{FF3300}| --------------------------------------------------------------- |\n");

	    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, " ", stringGlobal, "Fechar", "");

		db_free_result(sql_result);
	
	    return 1;
	}
	
	return 0;
}







