#pragma once
#include <windows.h>
#include "Utils.h"

typedef struct 
{
	PBYTE original;
	PBYTE buffer;
	SIZE_T length;
	SIZE_T originalLength;
} Parser, *PParser;


PParser newParser(PBYTE buffer, SIZE_T size);
VOID freeParser(PParser parser);

BYTE getByte(PParser parser);
UINT32 getInt32(PParser parser);
UINT64 getInt64(PParser parser);
PBYTE getBytes(PParser parser, PSIZE_T size);
PCHAR getString(PParser parser, PSIZE_T size);
PWCHAR getWString(PParser parser, PSIZE_T size);
