#include "bdg_math.h"

#include <random>


float degToRad(float degrees) {
  return PI * degrees / 180.0f;
}

float radToDeg(float radians) {
  return 180.0f * radians / PI;
}


float fmap(float t, float in_min, float in_max, float out_min, float out_max)
{
  float frac = (t - in_min) / (in_max - in_min);
  return frac * (out_max - out_min) + out_min;
}


Vec2f::Vec2f(float ix, float iy) {
  x = ix;
  y = iy;
}
