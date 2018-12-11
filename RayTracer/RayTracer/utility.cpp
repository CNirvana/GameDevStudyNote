#include "utility.h"

float clamp(float value, float min, float max)
{
	if (min > max)
	{
		std::swap(min, max);
	}

	return std::min(std::max(value, min), max);
}

float clamp01(float value)
{
	return clamp(value, 0, 1);
}