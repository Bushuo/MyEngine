#ifndef TESTER_HELPER_FUNCTIONS_H
#define TESTER_HELPER_FUNCTIONS_H
#include <cmath>

inline bool closeEnough(
	float left, float right,
	float threshold = 0.0000001f)
{
	return abs(left - right) < threshold;
}

#endif

