// kruskal.h

#ifndef kruskal_h
#define kruskal_h

#include <vector>

class Coord;

#define KruskPair std::pair<int, int>

std::vector<KruskPair> computeKruskal(std::vector<Coord> points/*, distfunc*/);

#endif // kruskal_h
