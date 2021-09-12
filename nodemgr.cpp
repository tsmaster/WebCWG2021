#include "nodemgr.h"

// TODO port nodemgr

NodeMgr::NodeMgr(unsigned int cacheSize, GameClock* gameClock)
{
  m_baseCacheSize = cacheSize;
  m_gameClock = gameClock;
}
