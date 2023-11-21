#include "bcstl/memory.h"

#include <stdlib.h>

namespace bcstl_memory
{
	static void* default_memory_allocation(unsigned int size) { return malloc(size); }
	static void default_memory_deallocation(void* ptr) { free(ptr); }

	static memory_allocation_callback_template g_allocation_callback = default_memory_allocation;
	static memory_deallocation_callback_template g_deallocation_callback = default_memory_deallocation;

	void* allocation_internal(unsigned int size)
	{
		return g_allocation_callback(size);
	}

	void deallocation_internal(void* ptr)
	{
		g_deallocation_callback(ptr);
	}

	void* set_memory_internal(bcstl::byte* dest, bcstl::byte value, bcstl::uint64 size)
	{
		for (bcstl::uint64 i = 0; i < size; ++i)
		{
			dest[i] = value;
		}
		return dest;
	}

	void* copy_memory_internal(bcstl::byte* dest, const bcstl::byte* src, bcstl::uint64 size)
	{
		for (bcstl::uint64 i = 0; i < size; ++i)
		{
			dest[i] = src[i];
		}
		return dest;
	}
}

namespace bcstl
{
	void set_memory_allocation_callback(bcstl_memory::memory_allocation_callback_template func)
	{
		if (!func)
		{
			return;
		}
		bcstl_memory::g_allocation_callback = func;
	}

	void set_memory_deallocation_callback(bcstl_memory::memory_deallocation_callback_template func)
	{
		if (!func)
		{
			return;
		}
		bcstl_memory::g_deallocation_callback = func;
	}
}
