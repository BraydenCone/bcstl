#include "bcstl/random.h"

#include "bcstl/crypto.h"

static bcstl::uint32 g_seed = 0;
static bcstl::uint32 g_counter = 0;

namespace bcstl
{
	__forceinline bcstl::uint32 random_hash()
	{
		g_counter++;
		return murmur::hash(&g_seed, sizeof(uint32), g_counter);
	}
}

void bcstl::seed_random(uint32 seed)
{
	g_seed = seed;
	g_counter = 0;
}

bcstl::uint32 bcstl::random()
{
	uint32 random_number = random_hash();
	random_number ^= random_number << 13;
	random_number ^= random_number >> 17;
	random_number ^= random_number << 5;
	return random_number;
}
