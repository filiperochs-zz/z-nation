
new logStringServer[256];

#define Log::(%0,%1) \
		serverLogEx(%0, (format(logStringServer, 256, %1), logStringServer))

stock serverLogEx(namelog[], logtext[]) {

	new File:fileLog;
	new fileString[256];
	
	format(fileString, sizeof (fileString), pastaLogs, namelog);
	
	fileLog = fopen(fileString, io_append);
	
	if (fileLog)
	{
	    static date[3];
	    static hour[3];
	    
	    getdate(date[2], date[1], date[0]);
	    gettime(hour[0], hour[1], hour[2]);
	
	    format(fileString, sizeof (fileString), "%02d-%02d-%04d %02d:%02d:%02d|%s\t\t|%s\r\n", date[0], date[1], date[2], hour[0], hour[1], hour[2], namelog, logtext);
	    fwrite(fileLog, fileString);
	    fclose(fileLog);
	}
}
