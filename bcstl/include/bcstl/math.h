#pragma once

#include "bcstl/memory.h"
#include <math.h>

namespace bcstl
{
	#define PI 3.14159265358979323846f
	
	#define MIN(a, b)         ((a) < (b) ? (a) : (b))
	#define MAX(a, b)         ((a) > (b) ? (a) : (b))
	#define CLAMP(x, a, b)    MIN(b, MAX(a, x))
	
	#define DEG_TO_RAD        (PI / 180.0f)
	#define RAD_TO_DEG        (180.0f / PI)

	float clamp_float(float value, float min, float max);
	float lerp_float(float start, float end, float amount);
	float normalize_float(float value, float start, float end);
}