#include "cma_util.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define _1GB (1024ull * 1024ull * 1024ull)
#define GB(x) ((x) * _1GB)

int CmaGetReservedHugePagesCount(void)
{
	MEMORYSTATUSEX mem_status;
	mem_status.dwLength = sizeof(mem_status);
	GlobalMemoryStatusEx(&mem_status);

	return static_cast<int>(mem_status.ullAvailPhys / GB(2));
}