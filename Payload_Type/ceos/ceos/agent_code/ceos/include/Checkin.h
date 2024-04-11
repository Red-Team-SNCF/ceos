#pragma once

#ifndef CHECKIN_H
#define CHECKIN_H
#include <ws2tcpip.h>
#include <lm.h>
#include <lmwksta.h>
#include "Package.h"
#include "Transport.h"
#include "Parser.h"

#pragma comment(lib, "netapi32.lib")

PParser checkin();
#endif
