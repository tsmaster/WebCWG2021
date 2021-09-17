#include <cstdio>
#include <math.h>
#include <stdlib.h>

unsigned int makeSeedKey(int x, int y, int h, const char* str)
{
  unsigned int k = 0xDEADBEEF;
  k ^= (unsigned int) x;
  unsigned int chunk1 = k & 0x7f;
  k = k >> 7;
  k = k | (chunk1 << 25);
  k ^= (unsigned int) y;
  unsigned int chunk2 = k & 0x7f;
  k = k >> 7;
  k = k | (chunk2 << 25);
  k ^= (unsigned int) h;
  unsigned int chunk3 = k & 0x7f;
  k = k >> 7;
  k = k | (chunk3 << 25);

  for (const char* c = str; *c != '\0'; ++c) {
    k ^= (unsigned int) (*c);

    unsigned int chunk = k & 0xff;
    k = k >> 8;
    k = k | (chunk << 24);
  }

  return k;
}

int randomrange(int low, int high)
{
  return (rand() % (high-low)) + low;
}


int rand_range(int min, int max)
{
  int r = max - min + 1;
  int v = rand() % r;
  return min + v;
}

float rand_frange(float min, float max)
{
  const int r = 10000;
  float v = (rand() % r) / ((float) r);
  return min + (max - min) * v;
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
