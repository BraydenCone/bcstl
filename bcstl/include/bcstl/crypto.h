#pragma once

#include "bcstl/types.h"

namespace bcstl
{
	namespace murmur
	{
		inline uint32 rotl32(uint32 x, uint8 r)
		{
			return (x << r) | (x >> (32 - r));
		}

		inline uint32 get_block_32(const uint32* p, int i)
		{
			return p[i];
		}

		inline uint32 fmix32(uint32 h)
		{
			h ^= h >> 16;
			h *= 0x85ebca6b;
			h ^= h >> 13;
			h *= 0xc2b2ae35;
			h ^= h >> 16;

			return h;
		}

		uint32 hash(const void* key, int len, uint32 seed);
	}
}
