#pragma once
#ifndef CEOS_H
#define CEOS_H
#include <ws2tcpip.h>
#include <lm.h>
#include <lmwksta.h>
#include <windows.h>
#include "Command.h"
#include "Package.h"
#include "Transport.h"
#include "Parser.h"
#include "Config.h"
#include "Utils.h"
#include "Checkin.h"

#include <iostream>

typedef struct
{
	PCHAR agentID;
} CONFIG_CEOS, * PCONFIG_CEOS;

extern PCONFIG_CEOS ceosConfig;


PCHAR getUUID();
VOID setUUID(PCHAR newUUID);


#endif
