#include "cma_api.h"
#include "cma_util.h"
#include <mimalloc.h>
#include <mimalloc-internal.h>
#include <cma_util.h>

size_t __stdcall MemTotalCommitted(void)
{
	return _mi_stats_main.committed.current;
}

size_t __stdcall MemTotalReserved(void)
{
	return _mi_stats_main.reserved.current;
}

size_t __stdcall MemFlushCache(size_t)
{
	size_t before = _mi_stats_main.committed.current;
	mi_collect(false);
	size_t after = _mi_stats_main.committed.current;
	return before > after ? before - after : 0;
}

void __stdcall MemFlushCacheAll(void)
{
	mi_collect(true);
}

size_t __stdcall MemSize(void* Mem)
{
	return mi_usable_size(Mem);
}

size_t __stdcall MemSizeA(void* Mem, size_t)
{
	return mi_usable_size(Mem);
}

void* __stdcall MemAlloc(size_t Size)
{
	return mi_malloc(Size);
}

void* __stdcall MemAllocA(size_t Size, size_t Align)
{
	return mi_malloc_aligned(Size, Align);
}

void __stdcall MemFree(void* Mem)
{
	mi_free(Mem);
}

void __stdcall MemFreeA(void* Mem)
{
	mi_free(Mem);
}

void __stdcall EnableHugePages(void)
{
	mi_option_enable(mi_option_large_os_pages);
	if (mi_option_is_enabled(mi_option_large_os_pages)) {
		mi_option_set(mi_option_reserve_huge_os_pages, CmaGetReservedHugePagesCount());
	}
}