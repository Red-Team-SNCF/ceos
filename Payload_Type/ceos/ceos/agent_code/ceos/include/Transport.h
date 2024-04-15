#pragma once
#ifndef TRANSPORT
#define TRANSPORT

#include "ceos.h"
#include <windows.h>
#include <winhttp.h>
#include "Parser.h"

#pragma comment(lib, "winhttp.lib")

#define HTTP_TRANSPORT

Parser* sendAndReceive(PBYTE data, SIZE_T size);
#endif