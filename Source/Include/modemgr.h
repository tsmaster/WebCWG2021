#ifndef modemgr_h
#define modemgr_h

#include <string>

#include "entt.hpp"

#include "modes.h"

class City;
class Person;

class ModeChangeRequest
{
 public:
  GameMode newGameMode;

  // -- CITY ARGS --
  // (ugh, so gross)

  std::string cityName;
  int x, y;
  int population;

  bool exitEast, exitNorth, exitWest, exitSouth;

  City* city;
  int buildingIndex;
  Person* buildingOwner;

  static ModeChangeRequest modeChangeRequestFactory(GameMode newGameMode);  
};




class ModeMgr
{
 public:
  ModeMgr();

  void requestMode();

  entt::entity getCurrentMode() { return m_currentMode; }
  void setCurrentMode(entt::entity newMode) { m_currentMode = newMode; }


 private:
  entt::entity m_currentMode = entt::null;

};

#endif //modemgr_H
