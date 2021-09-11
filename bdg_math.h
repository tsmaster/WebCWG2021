#ifndef BDG_MATH_H
#define BDG_MATH_H

// returns a random value [a,b] inclusive on both ends
int rand_range(int a, int b);
float rand_frange(float a, float b);

void rand_sphere_point(float& outX, float& outY, float& outZ);

float degToRad(float degrees);
float radToDeg(float radians);

const float PI = 3.141592654f;
const float TAU = PI * 2.0f;

#endif //BDG_MATH_H



