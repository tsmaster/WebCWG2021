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


int clamp(int val, int min, int max)
{
  return std::min(std::max(min, val), max-1);
}

Vec2f::Vec2f(float ix, float iy) {
  x = ix;
  y = iy;
}


bool Vec2i::lessThan(const Vec2i& other) const
{
  if (y < other.y) {
    return true;
  }  
  if (y > other.y) {
    return false;
  }
  
  if (x < other.x) {
    return true;
  }
  
  return false;  
}

