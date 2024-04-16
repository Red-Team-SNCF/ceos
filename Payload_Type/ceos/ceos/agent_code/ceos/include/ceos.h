#pragma once
#ifndef CEOS_H
#define CEOS_H



#include <windows.h>
#include "Command.h"
#include "Package.h"

#include "Parser.h"
#include "Utils.h"
#include "Checkin.h"


typedef struct
{
	// UUID
	PCHAR agentID;

	// HTTP 
	PWCHAR hostName;
	DWORD httpPort;
	PWCHAR endPoint;
	PWCHAR userAgent;
	PWCHAR httpMethod;

	BOOL isSSL;
	BOOL isProxyEnabled;
	PWCHAR proxyURL;


} CONFIG_CEOS, * PCONFIG_CEOS;

extern PCONFIG_CEOS ceosConfig;


VOID setUUID(PCHAR newUUID);
VOID ceosMain();

#endif
