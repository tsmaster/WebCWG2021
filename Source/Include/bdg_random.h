#ifndef bdg_random_h
#define bdg_random_h

unsigned int makeSeedKey(int x, int y, int h, const char* str);

int randomrange(int low, int high);

float frandomrange(float low, float high);

int rand_range(int min, int max);

float rand_frange(float min, float max);

// returns a random value [a,b] inclusive on both ends
void rand_sphere_point(float& outX, float& outY, float& outZ);


#endif // bdg_random_h
