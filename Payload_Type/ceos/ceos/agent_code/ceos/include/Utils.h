#pragma once
#ifndef UTILS
#define UTILS
#include <windows.h>
#include "Debug.h"


#ifdef __MINGW64__
#define BYTESWAP32(x) __builtin_bswap32( x )
#define BYTESWAP64(x) __builtin_bswap64( x )
#endif
#ifdef _MSC_VER
#define BYTESWAP32(x) _byteswap_ulong(x)
#define BYTESWAP64(x) _byteswap_uint64(x)
#endif

SIZE_T b64DecodedSize(const char* in);
int b64Decode(const char* in, unsigned char* out, SIZE_T outlen);
char* b64Encode(const unsigned char* in, SIZE_T len);
size_t b64EncodedSize(size_t inlen);


VOID addInt64ToBuffer(PBYTE buffer, UINT64 value);
VOID addInt32ToBuffer(PBYTE buffer, UINT32 value);
#endif