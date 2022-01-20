#include "Utils.h"

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float sinCurve(float x, float m, float c) {
	return std::sin(m * x + c);
}
