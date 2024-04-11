#pragma once

#ifndef CHECKIN
#define CHECKIN
#include <ws2tcpip.h>
#include <lm.h>
#include <lmwksta.h>
#include "Package.h"
#include "Transport.h"
#include "Parser.h"

#include "Config.h"

#pragma comment(lib, "netapi32.lib")

BOOL checkin();
#endif