#pragma once

#include "bcstl/math.h"

namespace bcstl
{
	template<typename T>
	union vec4_base
	{
		T elements[4];
		struct { T x1, y1, x2, y2; };
		struct { T u0, v0, u1, v1; };
		struct { T x, y, width, height; };
		struct { T x, y, z, w; };
		struct { T r, g, b, a; };

		vec4_base()
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
		}
		
		vec4_base(T v0, T v1, T v2, T v3)
		{
			elements[0] = v0;
			elements[1] = v1;
			elements[2] = v2;
			elements[3] = v3;
		}

		inline T& operator[](uint64 index)
		{
			return elements[index];
		}

		T distance(vec4_base<T> v)
		{
			T var1 = v.x - x;
			T var2 = v.y - y;
			T var3 = v.z - z;
			T var4 = v.w - w;
			return (T)sqrt((double)(var1 * var1 + var2 * var2 + var3 * var3 + var4 * var4));
		}
	};

	typedef vec4_base<uint8>	vec4_ui8;
	typedef vec4_base<uint16>	vec4_ui16;
	typedef vec4_base<uint32>	vec4_ui32;
	typedef vec4_base<uint64>	vec4_ui64;
	typedef vec4_base<float>	vec4_f;
	typedef vec4_base<double>	vec4_d;
}
