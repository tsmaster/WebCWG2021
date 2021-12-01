#ifndef bdg_random_h
#define bdg_random_h

#include <vector>

unsigned int makeSeedKey(int x, int y, int h, const char* str);

int randomrange(int low, int high);

int rand_range(int min, int max);

float rand_frange(float min, float max);

// returns a random value [a,b] inclusive on both ends
void rand_sphere_point(float& outX, float& outY, float& outZ);


std::vector<float> normalizeProbabilities(std::vector<float> probs);

int randomFromDistribution(std::vector<float> probs);

#endif // bdg_random_h
