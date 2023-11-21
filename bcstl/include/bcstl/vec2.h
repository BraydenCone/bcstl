#pragma once

#include "bcstl/math.h"

namespace bcstl
{
	template<typename T>
	union vec2_base
	{
		T elements[2];
		struct { T x, y; };
		struct { T u, v; };

		vec2_base()
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
		}

		vec2_base(T v0, T v1)
		{
			elements[0] = v0;
			elements[1] = v1;
		}

		inline T& operator[](uint64 index)
		{
			return elements[index];
		}

		inline vec2_base<T> operator*(const T right)
		{
			return vec2_base<T>(x * right, y * right);
		}

		inline vec2_base operator/(const T right)
		{
			return vec2_base<T>(x / right, y / right);
		}

		inline vec2_base<T> operator+(const vec2_base<T>& right)
		{
			return vec2_base<T>(x + right.x, y + right.y);
		}

		inline vec2_base<T> operator-(const vec2_base<T>& right)
		{
			return vec2_base<T>(x - right.x, y - right.y);
		}

		inline vec2_base<T> operator*(const vec2_base<T>& right)
		{
			return vec2_base<T>(x * right.x, y * right.y);
		}

		inline vec2_base<T> operator/(const vec2_base<T>& right)
		{
			return vec2_base<T>(x / right.x, y / right.y);
		}

		inline vec2_base<T>& operator*=(const T right)
		{
			x *= right;
			y *= right;
			return *this;
		}

		inline vec2_base<T>& operator/=(const T right)
		{
			x /= right;
			y /= right;
			return *this;
		}

		T distance_to(vec2_base<T> v)
		{
			T var1 = v.x - x;
			T var2 = v.y - y;
			return (T)sqrt((double)(var1 * var1 + var2 * var2));
		}

		T direction_to(vec2_base<T> v)
		{
			float radians = atan2f(y - v.y, x - v.x);
			return (radians * 180.0f) / PI;
		}

		vec2_base<T> rotate(vec2_base<T> point, T angle)
		{
			T _cos = (T)cos(angle);
			T _sin = (T)sin(angle);

			T _x = ((x - point.x) * _cos - (y - point.y) * _sin) + point.x;
			T _y = ((x - point.x) * _sin + (y - point.y) * _cos) + point.y;

			return vec2_base<T>(_x, _y);
		}
	};

	typedef vec2_base<uint8>	vec2_ui8;
	typedef vec2_base<uint16>	vec2_ui16;
	typedef vec2_base<uint32>	vec2_ui32;
	typedef vec2_base<uint64>	vec2_ui64;
	typedef vec2_base<float>	vec2_f;
	typedef vec2_base<double>	vec2_d;
}
