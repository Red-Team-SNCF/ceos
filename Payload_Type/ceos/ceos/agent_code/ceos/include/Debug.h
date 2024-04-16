#pragma once

#include <stdio.h>

#if defined(_DEBUG)


#define DBG "DBG"
#define ERR "ERR"
#define WRN "WRN"
#define INF "INF"

#define _log(level, format, ...) printf("[%s] %s:%d - " format "\n", level, __FUNCTION__, __LINE__, ## __VA_ARGS__);
#define _dbg(format, ...) _log(DBG, format, ## __VA_ARGS__)
#define _err(format, ...) _log(ERR, format, ## __VA_ARGS__)
#define _wrn(format, ...) _log(WRN, format, ## __VA_ARGS__)
#define _inf(format, ...) _log(INF, format, ## __VA_ARGS__)
#elif defined(_DEBUG_RELEASE)
#define DBG
#define ERR
#define WRN
#define INF
#define _log(level, format, ...) {HANDLE debugFile = CreateFileA("C:\\Temp\\Ra.log", FILE_APPEND_DATA , 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);\
CHAR out[200] = { 0 };\
sprintf(out, format"\n", ## __VA_ARGS__);\
WriteFile(debugFile, out, strlen(out), NULL, NULL);\
CloseHandle(debugFile);}
#define _dbg(format, ...) _log(DBG, format, ## __VA_ARGS__)
#define _err(format, ...) _log(ERR, format, ## __VA_ARGS__)
#define _wrn(format, ...) _log(WRN, format, ## __VA_ARGS__)
#define _inf(format, ...) _log(INF, format, ## __VA_ARGS__)
#else
#define DBG
#define ERR
#define WRN
#define INF
#define _log(level, format, ...)
#define _dbg(format, ...)
#define _err(format, ...)
#define _wrn(format, ...)
#define _inf(format, ...)
#endif
