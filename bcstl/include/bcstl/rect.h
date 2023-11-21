#pragma once

#include "types.h"
#include "vec2.h"

namespace bcstl
{
	template<typename T>
	union rect_base
	{
		T elements[4];
		struct { T x, y, w, h; };

		rect_base() { BCSTL_MEMSET(this, 0, sizeof(*this)); }
		rect_base(T v0, T v1, T v2, T v3) { elements[0] = v0; elements[1] = v1;  elements[2] = v2; elements[3] = v3; }

		inline T& operator[](uint64 index) { return elements[index]; }

		inline bool collision_point(vec2_base<T>& point)
		{
			return point.x > x
				&& point.y > y
				&& point.x < (x + w)
				&& point.y < (y + h);
		}

		// returns how many points are in the collision
		inline uint64 collision_rect(rect_base<T>& rect)
		{
			T x2, y2;
			int points;

			x2 = rect.x + rect.w;
			y2 = rect.y + rect.h;

			points += (uint64)collision_point(vec2_base<T>(rect.x, rect.y));
			points += (uint64)collision_point(vec2_base<T>(x2, rect.y));
			points += (uint64)collision_point(vec2_base<T>(rect.x, y2));
			points += (uint64)collision_point(vec2_base<T>(x2, y2));

			return points;
		}
	};

	typedef rect_base<uint8>	rect_ui8;
	typedef rect_base<uint16>	rect_ui16;
	typedef rect_base<uint32>	rect_ui32;
	typedef rect_base<uint64>	rect_ui64;
	typedef rect_base<float>	rect_f;
	typedef rect_base<double>	rect_d;
}
