// mode_highway.h

// Reference ../PyCWG2021/fractal.py

#ifndef MODE_HIGHWAY_H
#define MODE_HIGHWAY_H

#include "coord.h"
#include "gameclock.h"
#include "nodemgr.h"

class GameClock;

class HighwayGameMode
{
 public:
  HighwayGameMode();

  void init();

  void destroy();

  bool update(float elapsedSeconds);

  void draw();

private:
  Coord m_centerCoord;
  GameClock* m_gameClock;
  NodeMgr* m_nodeMgr;  
};

#endif // MODE_HIGHWAY_H
