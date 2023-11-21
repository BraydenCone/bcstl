#pragma once

#include "bcstl/types.h"

#define BCSTL_ALLOC(size) bcstl_memory::allocation_internal(size)
#define BCSTL_FREE(ptr) bcstl_memory::deallocation_internal(ptr)

#define BCSTL_MEMSET(dest, value, size) bcstl_memory::set_memory_internal((bcstl::byte*)dest, (bcstl::byte)value, size)
#define BCSTL_MEMCPY(dest, src, size) bcstl_memory::copy_memory_internal((bcstl::byte*)dest, (bcstl::byte*)src, size)

namespace bcstl_memory
{
	typedef void* (*memory_allocation_callback_template)(unsigned int size);
	typedef void(*memory_deallocation_callback_template)(void* ptr);

	void* allocation_internal(unsigned int size);
	void deallocation_internal(void* ptr);

	void* set_memory_internal(bcstl::byte* dest, bcstl::byte value, bcstl::uint64 size);
	void* copy_memory_internal(bcstl::byte* dest, const bcstl::byte* src, bcstl::uint64 size);
}

namespace bcstl
{
	void set_memory_allocation_callback(bcstl_memory::memory_allocation_callback_template func);
	void set_memory_deallocation_callback(bcstl_memory::memory_deallocation_callback_template func);
}
