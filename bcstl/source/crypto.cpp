#include "bcstl/crypto.h"

bcstl::uint32 bcstl::murmur::hash(const void* key, int len, bcstl::uint32 seed)
{
	const bcstl::uint8* data = (const bcstl::uint8*)key;
	const int nblocks = len / 4;

	bcstl::uint32 h1 = seed;

	const bcstl::uint32 c1 = 0xcc9e2d51;
	const bcstl::uint32 c2 = 0x1b873593;

	//----------
	// body

	const bcstl::uint32* blocks = (const bcstl::uint32*)(data + nblocks * 4);

	for (int i = -nblocks; i; i++)
	{
		bcstl::uint32 k1 = get_block_32(blocks, i);

		k1 *= c1;
		k1 = rotl32(k1, 15);
		k1 *= c2;

		h1 ^= k1;
		h1 = rotl32(h1, 13);
		h1 = h1 * 5 + 0xe6546b64;
	}

	//----------
	// tail

	const bcstl::uint8* tail = (const bcstl::uint8*)(data + nblocks * 4);

	bcstl::uint32 k1 = 0;

	switch (len & 3)
	{
	case 3: k1 ^= tail[2] << 16;
	case 2: k1 ^= tail[1] << 8;
	case 1: k1 ^= tail[0];
		k1 *= c1; k1 = rotl32(k1, 15); k1 *= c2; h1 ^= k1;
	};

	//----------
	// finalization

	h1 ^= len;

	h1 = fmix32(h1);

	return h1;
}
