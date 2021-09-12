// COORD.H
#ifndef COORD_H
#define COORD_H

#include <string>

class Coord
{
 public:
  Coord(int x, int y, int h);
  Coord() : Coord(0, 0, 0) {}

  std::string toString();

  bool isEqual(Coord& other);

  bool lessThan(const Coord& other) const;

  int manhattanDist(Coord& other);

  bool operator < (const Coord &other) const { return lessThan(other); }

  int x;
  int y;
  int h;
};

#endif // COORD_H
