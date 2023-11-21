#include "bcstl/random.h"

#include "bcstl/crypto.h"

static bcstl::uint32 g_seed = 0;
static bcstl::uint32 g_counter = 0;

bcstl::uint32 bcstl::next_seed()
{
	bcstl::uint32 seed = murmur::hash(&g_seed, sizeof(uint32), g_counter);
	g_counter++;
	return seed;
}

void bcstl::seed_random(bcstl::uint32 seed)
{
	g_seed = seed;
	g_counter = 0;
}

bcstl::uint32 bcstl::random()
{
	uint32 random_number = next_seed();
	random_number ^= random_number << 13;
	random_number ^= random_number >> 17;
	random_number ^= random_number << 5;
	return random_number;
}
