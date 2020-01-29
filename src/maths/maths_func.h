#pragma once

#include <math.h>

#define PI 3.14159265358979323846264338327950288f

namespace ferrari {
	namespace maths {
		
		inline float toRadians(float degrees)
		{
			return (float)(degrees * (PI / 180.0f));
		}

		inline float toDegrees(float radians)
		{
			return (float)(radians * (180.0f / PI));
		}

		inline float rsqrt(float value)
		{
			return 1.0f / ::sqrt(value);
		}

		inline float atan2(float y, float x)
		{
			return ::atan2(y, x);
		}

		inline float asin(float value)
		{
			return ::asin(value);
		}

		inline int sign(float value)
		{
			return (value > 0) - (value < 0);
		}
	}
}