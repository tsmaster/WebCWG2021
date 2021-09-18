// COORD.CPP

#include "coord.h"

#include <cassert>
#include <sstream>

Coord::Coord(int ix, int iy, int ih)
{
  x = ix;
  y = iy;
  h = ih;
}

std::string Coord::toString()
{
  std::ostringstream stringStream;
  stringStream << "<";
  stringStream << x;
  stringStream << ", ";
  stringStream << y;
  stringStream << " / ";
  stringStream << h;
  stringStream << ">";
  return stringStream.str();
}

bool Coord::isEqual(Coord& other)
{
  return ((x == other.x) &&
	  (y == other.y) &&
	  (h == other.h));
}

bool Coord::lessThan(const Coord& other) const
{
  if (h < other.h) {
    return true;
  }  
  if (h > other.h) {
    return false;
  }

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

int Coord::manhattanDist(Coord& other)
{
  assert(h == 0);
  assert(other.h == 0);

  int dx = x - other.x;
  int dy = y - other.y;

  return abs(dx) + abs(dy);
}
