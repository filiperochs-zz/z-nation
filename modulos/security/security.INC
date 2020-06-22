
#include <a_http>

stock CheckGamemodeAuthorize() {

    print("\n\n---------------------------------------------------------------------");
	print("  * PH Nation 2020");
	print("  * Checando autorização do gamemode...");
	// get http response
    HTTP(0, HTTP_GET, "znation-dayz.esy.es/auth.php", "", "securityGamemodeRequest1");
    
    serverSecurity = true;

	return 1;
}

callback securityGamemodeRequest1(index, response_code, data[])
{
	if (!strcmp(data, "Authorized") && strlen(data) > 3) {
	    serverSecurity = false;
	    print("  * Checagem de autorização concluída!");
	    print("  * O gamemode está pronto para uso.");
	    print("\n\n---------------------------------------------------------------------");
	} else {
		HTTP(0, HTTP_GET, "znation-dayz.esy.es/auth.php", "", "securityGamemodeRequest2");
		print("  * Checagem 1/3 falhou, fazendo uma nova...");
	}
	return 1;
}

callback securityGamemodeRequest2(index, response_code, data[])
{
	if (!strcmp(data, "Authorized") && strlen(data) > 3) {
	    serverSecurity = false;
	    print("  * Checagem de autorização concluída!");
	    print("  * O gamemode está pronto para uso.");
	    print("\n\n---------------------------------------------------------------------");
	} else {
		HTTP(0, HTTP_GET, "znation-dayz.esy.es/auth.php", "", "securityGamemodeRequest3");
		print("  * Checagem 2/3 falhou, fazendo uma nova...");
	}
	return 1;
}

callback securityGamemodeRequest3(index, response_code, data[])
{
	if (!strcmp(data, "Authorized") && strlen(data) > 3) {
	    serverSecurity = false;
	    print("  * Checagem de autorização concluída!");
	    print("  * O gamemode está pronto para uso.");
	    print("\n\n---------------------------------------------------------------------");
	} else {
	    print("  * Checagem 3/3 falhou!");
	    print("  * ATENÇÃO: Este gamemode não está autorizado!");
	    print("  * Entre em contato com o criador do mesmo para pedir autorização.");
	    print("  * E-mail: dimmy_cn@hotmail.com.");
	    print("\n\n---------------------------------------------------------------------");
	    
	    // kill all timers
	    for(new timer; timer < 100000; timer++)
	        KillTimer(timer);
	    // exit gamemode
	    SendRconCommand("exit");
	    GameModeExit();
	}
	/*
    serverSecurity = false;
    print("  * Checagem de autorização concluída!");
    print("  * O gamemode está pronto para uso.");
    print("\n\n---------------------------------------------------------------------");*/
	return 1;
}
