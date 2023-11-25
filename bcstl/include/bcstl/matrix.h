#pragma once

#include "bcstl/types.h"

namespace bcstl
{
	template<typename T>
	union matrix_base
	{
		T elements[16];
		struct
		{
			T m0, m4, m8,  m12;
			T m1, m5, m9,  m13;
			T m2, m6, m10, m14;
			T m3, m7, m11, m15;
		};
		struct
		{
			T layout[4][4];
		};

		inline T& operator[](uint64 index)
		{
			return elements[index];
		}
	};

	typedef matrix_base<float>	matrix_f;
}
