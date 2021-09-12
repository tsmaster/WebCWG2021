#include "nodemgr.h"

#include "node.h"

// TODO port nodemgr

NodeMgr::NodeMgr(unsigned int cacheSize, GameClock* gameClock)
{
  m_baseCacheSize = cacheSize;
  m_gameClock = gameClock;
}


std::vector<Node*> NodeMgr::getNodes()
{
  std::vector<Node*> outNodes;

  // TODO generate vector of nodes

  return outNodes;
}
