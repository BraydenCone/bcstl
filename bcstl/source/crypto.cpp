#include "bcstl/crypto.h"

#define C1 0xcc9e2d51
#define C2 0x1b873593

bcstl::uint32 bcstl::murmur::hash(const void* key, int32 len, uint32 seed)
{
	const uint8* data = (const uint8*)key;
	const int32 number_blocks = len / 4;

	uint32 h1 = seed;

	const uint32* blocks = (const uint32*)(data + number_blocks * 4);

	for (int32 i = -number_blocks; i; i++)
	{
		uint32 k1 = blocks[i];

		k1 *= C1;
		k1 = rotl32(k1, 15);
		k1 *= C2;

		h1 ^= k1;
		h1 = rotl32(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}

	const uint8* tail = (const uint8*)(data + number_blocks * 4);

	uint32 k1 = 0;

	switch (len & 3)
	{
	case 3: k1 ^= tail[2] << 16;
	case 2: k1 ^= tail[1] << 8;
	case 1: k1 ^= tail[0];
		k1 *= C1; k1 = rotl32(k1, 15); k1 *= C2; h1 ^= k1;
	};

	h1 ^= len;

	h1 = fmix32(h1);

	return h1;
}
