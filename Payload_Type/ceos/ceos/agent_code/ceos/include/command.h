#pragma once

#ifndef COMMAND
#define COMMAND

#include "Parser.h"
#include "Package.h"
#include "Shell.h"


#define SHELL_CMD 0x54
#define GET_TASKING 0x00
#define POST_RESPONSE 0x01
#define CHECKIN 0xf1

BOOL routine();
BOOL parseCheckin(PParser ResponseParser);



#endif