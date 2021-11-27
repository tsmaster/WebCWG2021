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

float fclamp(float val, float min, float max)
{
  return std::min(std::max(min, val), max);
}

Vec2f::Vec2f(float ix, float iy) {
  x = ix;
  y = iy;
}

Vec2f Vec2f::rotate(float radiansCCW) const {
  return Vec2f(x * cos(radiansCCW) - y * sin(radiansCCW),
	       x * sin(radiansCCW) + y * cos(radiansCCW));		       
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

float Vec2i::distEuclid(const Vec2i& other) const
{
  int dx = x - other.x;
  int dy = y - other.y;

  int distSqr = dx * dx + dy * dy;
  return sqrt(distSqr);
}
