// CITY.H

#ifndef city_h
#define city_h

#include <string>

#include "coord.h"

class City
{
 public:
  City(int x, int y);

  std::string getName() { return m_name; }

  void setPopulation(int pop) { m_population = pop; }
  int getPopulation() { return m_population; }
  
 private:
  Coord m_coord;
  
  std::string makeName();
  std::string makeAltName();
  std::string m_name;

  int m_population;
};

#endif //city_h
