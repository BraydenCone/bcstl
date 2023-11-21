#pragma once

#include "bcstl/math.h"

namespace bcstl
{
	template<typename T>
	union vec3_base
	{
		T elements[3];
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T pitch, yaw, roll; };

		vec3_base()
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
		}

		vec3_base(T v0, T v1, T v2)
		{
			elements[0] = v0;
			elements[1] = v1;
			elements[2] = v2;
		}

		inline T& operator[](uint64 index)
		{
			return elements[index];
		}

		T distance(vec3_base<T> v)
		{
			T var1 = v.x - x;
			T var2 = v.y - y;
			T var3 = v.z - z;
			return (T)sqrt((double)(var1 * var1 + var2 * var2 + var3 * var3));
		}
	};

	typedef vec3_base<uint8>	vec3_ui8;
	typedef vec3_base<uint16>	vec3_ui16;
	typedef vec3_base<uint32>	vec3_ui32;
	typedef vec3_base<uint64>	vec3_ui64;
	typedef vec3_base<float>	vec3_f;
	typedef vec3_base<double>	vec3_d;
}
