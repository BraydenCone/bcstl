#pragma once

#include "bcstl/math.h"

namespace bcstl
{
	struct color
	{
	private:
		rgba data;
	public:
		color()
		{
			data = 0;
		}

		color(uint8 r, uint8 g, uint8 b, uint8 a)
		{
			data = (((rgba)(a) << 24) | ((rgba)(b) << 16) | ((rgba)(g) << 8) | ((rgba)(r) << 0));
		}

		color(rgba color)
		{
			data = color;
		}
	};
}
