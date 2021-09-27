// CITY.H

#ifndef city_h
#define city_h

#include <string>

#include "coord.h"
#include "person.h"

class CityMap;

class City
{
 public:
  City(int x, int y);

  void setName(std::string name) { m_name = name; }
  std::string getName() { return m_name; }

  void setPopulation(int pop) {
    m_population = pop;
    populatePeople();
  }
  
  int getPopulation() { return m_population; }

  Coord getCoord() { return m_coord; }

  void setExits(bool e, bool n, bool w, bool s) {
    m_exitEast = e;
    m_exitNorth = n;
    m_exitWest = w;
    m_exitSouth = s;
  }

  bool hasExit(int dir);

  CityMap* getCityMap() { return m_cityMap; }

  std::vector<Person*> getPeople();
  
 private:
  Coord m_coord;
  
  std::string makeName();
  std::string makeAltName();
  std::string makeMarkovName();
  void populatePeople();
  
  std::string m_name;

  int m_population;

  bool m_exitEast;
  bool m_exitNorth;
  bool m_exitWest;
  bool m_exitSouth;

  CityMap* m_cityMap;

  std::vector<Person> m_people;
};

#endif //city_h
