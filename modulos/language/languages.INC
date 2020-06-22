/*  language.inc
 *
 *  (c) Copyright 2012, Emilijo "Correlli" Lovrich
 *
 *  Credits: 
			 - whoever created StripNewLine (DracoBlue?) & SplitChar functions.
*/

#if !defined MAX_LANGUAGES
	#define MAX_LANGUAGES (3)
#endif

new playerLanguageName[MAX_PLAYERS][24];

/*
native SendLanguageMessageEx(playerid, color, message[], {Float,_}:...);
native SendLanguageMessageToAllEx(color, message[], {Float,_}:...);
native SetPlayerLanguage(playerid, langname[]);
native GetPlayerLanguage(playerid);
native SendLanguageMessage(playerid, color, langkey[]);
native SendLanguageMessageToAll(color, langkey[]);
native LoadLanguageTexts(langname[]);
native GetLanguageKey(langname[], langkey[]);
native LanguageFile(langname[]);
*/

#define SendLanguageMessagef(%0,%1,%2,%3) SendClientMessagef(%0, %1, GetLanguageKey(GetPlayerLanguage(%0), %2), %3)

#define SendLanguageMessageToAllf(%0,%1,%2)\
	foreach(new i : Player) SendLanguageMessagef(i, %0,%1,%2)

#define LoadLanguage(%0) LoadLanguageTexts(%0)

new
		languageID = -1;

/* ----- */

stock SetPlayerLanguage(playerid, langname[])
{
	new
			File:langFile = fopen(LanguageFile(langname), io_read);
	if(!langFile)
	{
		format(playerLanguageName[playerid], 24, "Portugues");
		return printf("Error: File for language \"%s\" doesn't exist, setting the default language (Portugues)!", langname);
	}
	fclose(langFile);
	
	format(playerLanguageName[playerid], 24, "%s", langname);
	format(PlayerData[playerid][dLanguage], 24, "%s", langname);
	
	#if defined OnPlayerChangeLanguage
	    OnPlayerChangeLanguage(playerid, langname);
	#endif
	
	return 1;
}

stock GetPlayerLanguage(playerid) {
	return playerLanguageName[playerid];
}

stock SendLanguageMessage(playerid, color, langkey[])
	return SendClientMessage(playerid, color, GetLanguageKey(GetPlayerLanguage(playerid), langkey));

stock SendLanguageMessageToAll(color, langkey[])
{
	foreach(Player, u)
		SendLanguageMessage(u, color, langkey);
	return true;
}

stock LoadLanguageTexts(langname[])
{
	languageID++;
	if(languageID == MAX_LANGUAGES)
	{
		languageID--;
		return printf("Error: Limit of languages exceeded. Open the language.inc and change the \"MAX_LANGUAGES\" define to bigger value if you want to have more languages.");
	}
	if(strlen(langname) > 24)
	{
		languageID--;
		return printf("Error: Name of language \"%s\" is too long, name limit is 24 characters!", langname);
	}
	new
			File:langFile = fopen(LanguageFile(langname), io_read);
	if(!langFile)
	{
		languageID--;
		return printf("Error: File for language \"%s\" doesn't exist!", langname);
	}
	new
			string[256 + 24 + 2], data[2][256];
	while(fread(langFile, string))
	{
		StripNewLineEx(string);
		if(strlen(string) != 0 && strfind(string, "//", true) == -1)
		{
			SplitChar(string, data, '=');
			format(data[0], 50, "%s_%s", langname, data[0]);
			SetSVarString(data[0], data[1]);
			
			// Debug
			//printf("Lang: %s, loaded: %s", langname, data[1]);
		}
	}
	fclose(langFile);
	printf("Loaded language: %s\n", langname);
	return true;
}

stock DeleteLanguageTexts(langname[])
{
	if(strlen(langname) > 24)
	{
		languageID--;
		return printf("Error: Name of language \"%s\" is too long, name limit is 24 characters!", langname);
	}
	new
			File:langFile = fopen(LanguageFile(langname), io_read);
	if(!langFile)
	{
		languageID--;
		return printf("Error: File for language \"%s\" doesn't exist!", langname);
	}
	new
			string[256 + 24 + 2], data[2][256];
	while(fread(langFile, string))
	{
		StripNewLineEx(string);
		if(strlen(string) != 0 && strfind(string, "//", true) == -1)
		{
			SplitChar(string, data, '=');
			format(data[0], 50, "%s_%s", langname, data[0]);
			DeleteSVar(data[0]);

			// Debug
			printf("Lang: %s, deleted: %s", langname, data[0]);
		}
	}
	fclose(langFile);
	printf("Deleted language: %s\n", langname);
	return true;
}

stock GetLanguageKey(langname[], langkey[])
{
	new
			string[128];
	format(string, 50, "%s_%s", langname, langkey);
	GetSVarString(string, string, 128);
	return string;
}


stock GetPlayerLanguageKey(playerid, langkey[])
{
	new
			string[144], string2[256];
	format(string, 50, "%s_%s", GetPlayerLanguage(playerid), langkey);
	GetSVarString(string, string2, 256);
	return string2;
}

stock LanguageFile(langname[])
{
	new
			path[55];
	format(path, 55, "ZNation/Languages/%s.lng", langname);
	return path;
}

/* ----- */

stock StripNewLineEx(string[])
{
	new
			strLength = strlen(string);
			
	for(new len; len < strLength; len++)
	{
	    if (string[len] == '\\' && string[len + 1] == 't')
		{
			string[len] = '\t';
			string[len + 1] = ' ';
		}
	}
			
	if(!string[0]) return;
	if(string[strLength - 1] == '\n' || string[strLength - 1] == '\r')
	{
		string[strLength - 1] = 0;
		if(!string[0]) return;
		if(string[strLength - 2] == '\n' || string[strLength - 2] == '\r') string[strLength - 2] = 0;
	}
}

stock SplitChar(const strsrc[], strdest[][], delimiter)
{
	new
			i, li, aNum, len;
	while(i <= strlen(strsrc))
	{
		if(strsrc[i] == delimiter || i == strlen(strsrc))
		{
			len = strmid(strdest[aNum], strsrc, li, i, 256);
			strdest[aNum][len] = 0;
			li = i + 1;
			aNum++;
		}
		i++;
	}
	return true;
}
