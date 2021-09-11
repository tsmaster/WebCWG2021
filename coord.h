// COORD.H
#ifndef COORD_H
#define COORD_H

#include <string>

class Coord
{
 public:
  Coord(int x, int y, int h);

  std::string toString();

  bool isEqual(Coord& other);

  bool lessThan(Coord& other);

  int manhattanDist(Coord& other);

  int x;
  int y;
  int h;
};

#endif // COORD_H
