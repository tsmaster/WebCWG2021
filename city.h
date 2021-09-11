// CITY.H

#ifndef city_h
#define city_h

#include <string>

#include "coord.h"

class City
{
 public:
  City(int x, int y);

  std::string getName();
  
 private:
  Coord m_coord;
  std::string makeName();
  

  std::string m_name;
};

#endif //city_h
