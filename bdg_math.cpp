#include "bdg_math.h"

#include <random>

int rand_range(int a, int b) {
  int rangeSize = b - a + 1;
  int roll = random() % rangeSize;
  return a + roll;
}

float rand_frange(float a, float b) {
  int r = random() % 1000;

  return a + (b - a) * r / 1000.0f;  
}


void rand_sphere_point(float& outX, float& outY, float& outZ)
{
  while (true) {
    outX = rand_frange(-1.0f, 1.0f);
    outY = rand_frange(-1.0f, 1.0f);
    outZ = rand_frange(-1.0f, 1.0f);

    float magSqr = outX * outX + outY * outY + outZ * outZ;
    if (magSqr > 1.0f) {
      continue;
    }

    float mag = sqrt(magSqr);
    outX /= mag;
    outY /= mag;
    outZ /= mag;

    return;
  }
}

float degToRad(float degrees) {
  return PI * degrees / 180.0f;
}

float radToDeg(float radians) {
  return 180.0f * radians / PI;
}



Vec2f::Vec2f(float ix, float iy) {
  x = ix;
  y = iy;
}
