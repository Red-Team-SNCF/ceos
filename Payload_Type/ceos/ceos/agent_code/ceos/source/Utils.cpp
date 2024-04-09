#include "Utils.h"

VOID addInt32ToBuffer(PBYTE buffer, UINT32 value)
{
    (buffer)[0] = (value >> 24) & 0xFF;
    (buffer)[1] = (value >> 16) & 0xFF;
    (buffer)[2] = (value >> 8) & 0xFF;
    (buffer)[3] = (value) & 0xFF;
}

VOID addInt64ToBuffer(PBYTE buffer, UINT64 value)
{
    buffer[7] = value & 0xFF;
    value >>= 8;

    buffer[6] = value & 0xFF;
    value >>= 8;

    buffer[5] = value & 0xFF;
    value >>= 8;

    buffer[4] = value & 0xFF;
    value >>= 8;

    buffer[3] = value & 0xFF;
    value >>= 8;

    buffer[2] = value & 0xFF;
    value >>= 8;

    buffer[1] = value & 0xFF;
    value >>= 8;

    buffer[0] = value & 0xFF;
}

