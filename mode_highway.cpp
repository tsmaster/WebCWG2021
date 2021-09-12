// mode_highway.cpp

#include "mode_highway.h"

#include "constants.h"
#include "coord.h"
#include "gameclock.h"

// Reference ../PyCWG2021/fractal.py

// TODO finish porting HighwayGameMode from fractal.py

HighwayGameMode::HighwayGameMode()
{
}

void HighwayGameMode::init()
{
  m_centerCoord = Coord(0, 0, 0);
  m_gameClock = new GameClock();
  m_nodeMgr = new NodeMgr(BASE_CACHE_SIZE, m_gameClock);
}

void HighwayGameMode::destroy()
{
  delete(m_gameClock);
  m_gameClock = NULL;

  delete(m_nodeMgr);
  m_nodeMgr = NULL;
}

bool HighwayGameMode::update(float elapsedSeconds)
{
  return true;
}

void HighwayGameMode::draw()
{
}
