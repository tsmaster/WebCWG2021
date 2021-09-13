#include <stdlib.h>
#include <cstdio>

unsigned int makeSeedKey(int x, int y, int h, const char* str)
{
  //printf("making seed %d %d %d %s\n", x, y, h, str);
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

  //printf("generated k [1]: %u\n", k);

  for (const char* c = str; *c != '\0'; ++c) {
    k ^= (unsigned int) (*c);

    unsigned int chunk = k & 0xff;
    k = k >> 8;
    k = k | (chunk << 24);
  }

  //printf("generated k [2]: %u\n", k);
  
  return k;
}

int randomrange(int low, int high)
{
  return (rand() % (high-low)) + low;
}
