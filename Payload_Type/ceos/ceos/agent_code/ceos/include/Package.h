#pragma once
#include <windows.h>
#include "Utils.h"

typedef struct {
	PVOID buffer;
	SIZE_T length;
} Package, *PPackage;

PPackage newPackage(BYTE commandId, BOOL init);
VOID freePackage(PPackage package);

BOOL addByte(PPackage package, BYTE byte);
BOOL addInt32(PPackage package, UINT32 value);
BOOL addInt64(PPackage package, UINT64 value);
BOOL addBytes(PPackage package, PBYTE data, SIZE_T size, BOOL copySize);
BOOL addString(PPackage package, PCHAR data, BOOL copySize);
BOOL addWString(PPackage package, PWCHAR data, BOOL copySize);