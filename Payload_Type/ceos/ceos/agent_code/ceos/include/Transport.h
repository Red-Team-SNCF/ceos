#pragma once
#include <windows.h>
#include <winhttp.h>
#include "Parser.h"

#pragma comment(lib, "winhttp.lib")

Parser* sendAndReceive(PBYTE data, SIZE_T size);