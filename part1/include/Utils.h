#ifndef UTILS_H
#define UTILS_H

#include <cmath>

// The function is actually defined in camth within C++20,
// but not compilers are all up to date and compatible to 
// this function
// PURPOSE: Linear change to get the number in between
// a and b
float lerp(float a, float b, float t);
// Produce y coordinate of a customized sin curve
// m - period, c - phase shift
// PURPOSE: Used for wave effect generation
float sinCurve(float x, float m, float c);

#endif // !UTILS_H
