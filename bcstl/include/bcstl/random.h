#pragma once

#include "bcstl/types.h"

namespace bcstl
{
	uint32 next_seed();
	void seed_random(uint32 seed);
	uint32 random();
}
