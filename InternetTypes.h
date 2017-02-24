#ifndef INTERNET_TYPES_HEADER
#define INTERNET_TYPES_HEADER

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

#include <stdio.h> //_vsprintf_l(), va_list, __crt_va_start(), __crt_va_end()

template<typename T>
T Select(void * source, int * index)
{
	int i = *index;

	*index += sizeof(T);

	return *(T *)&((byte *)source)[i];
}

int sprintfi(char * buffer, int * index, char * format, ...)
{
	va_list argumentList;
	__crt_va_start(argumentList, format);

	#pragma warning(push)
	#pragma warning(disable: 4996) // Deprecation
	int result = _vsprintf_l(&buffer[*index], format, NULL, argumentList);
	#pragma warning(pop)

	*index += result;

	__crt_va_end(argumentList);

	return result;
}

#endif