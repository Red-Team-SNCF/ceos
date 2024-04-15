#include "Parser.h"


PParser newParser(PBYTE buffer, SIZE_T size)
{
	PParser pParser = (PParser)LocalAlloc(LPTR, sizeof(Parser));
	pParser->buffer = NULL;
	pParser->length = size;
	pParser->originalLength = size;
	pParser->original = (PBYTE)LocalAlloc(LPTR, size);

	if (!pParser->original)
		return NULL;

	memcpy(pParser->original, buffer, size);
	pParser->buffer = pParser->original;

	return pParser;

}

VOID freeParser(PParser parser)
{
	parser->original = nullptr;
	parser->buffer = nullptr;
	LocalFree(parser);
}

BYTE getByte(PParser parser)
{
	BYTE intByte = 0;

	if (parser->length < 1)
		return 0;

	memcpy(&intByte, parser->buffer, 1);
	parser->buffer += 1;
	parser->length -= 1;

	return intByte;

}

UINT32 getInt32(PParser parser)
{
	UINT32 intByte = 0;

	if (parser->length < 4)
		return 0;

	memcpy(&intByte, parser->buffer, 4);
	parser->buffer += 4;
	parser->length -= 4;

	return BYTESWAP32(intByte);
}

UINT64 getInt64(PParser parser)
{
	UINT64 intByte = 0;

	if (parser->length < 8)
		return 0;

	memcpy(&intByte, parser->buffer, 8);
	parser->buffer += 8;
	parser->length -= 8;

	return BYTESWAP64(intByte);
}

PBYTE getBytes(PParser parser, PSIZE_T size)
{
	SIZE_T length = 0;

	if (*size == 0)
	{
		length = getInt32(parser);
		*size = length;
	}
	else
		length = *size;


	PBYTE outData = (PBYTE)LocalAlloc(LPTR, length);
	if (!outData)
		return NULL;

	memcpy(outData, parser->buffer, length);
	parser->buffer += length;
	parser->length -= length;

	return outData;
}

PCHAR getString(PParser parser, PSIZE_T size)
{
	return (PCHAR)getBytes(parser, size);
}

PWCHAR getWString(PParser parser, PSIZE_T size)
{
	return (PWCHAR)getBytes(parser, size);
}