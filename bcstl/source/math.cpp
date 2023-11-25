#include "bcstl/math.h"

float bcstl::clamp_float(float value, float min, float max)
{
    return CLAMP(value, min, max);
}

float bcstl::lerp_float(float start, float end, float amount)
{
    return start + amount * (end - start);
}

float bcstl::normalize_float(float value, float start, float end)
{
    return (value - start) / (end - start);
}
