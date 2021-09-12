#include <stdlib.h>

unsigned int makeSeedKey(int x, int y, int h, const char* str)
{
  unsigned int k = 0xDEADBEEF;
  k ^= (unsigned int) x;
  k ^= (unsigned int) y;
  k ^= (unsigned int) h;

  int offset = 0;
  for (const char* c = str; *c != '\0'; ++c) {
    k ^= ((unsigned int) (*c) << offset);

    offset += 8;
    offset %= 32;
  }

  return k;
}

int randomrange(int low, int high)
{
  return (rand() % (high-low)) + low;
}
