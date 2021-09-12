#include "nodemgr.h"

#include <vector>

#include "coord.h"
#include "node.h"

NodeMgr::NodeMgr(unsigned int cacheSize, GameClock* gameClock)
{
  m_baseCacheSize = cacheSize;
  m_gameClock = gameClock;
}

std::vector<Node*> NodeMgr::getNodes()
{
  // TODO can probably cache this for better performance
  std::vector<Node*> outNodes;

  for (auto h_iter = m_nodesByHeight.rbegin();
       h_iter != m_nodesByHeight.rend();
       ++h_iter) {
    for (auto m_iter = h_iter->begin();
	 m_iter != h_iter->end();
	 ++m_iter) {
      outNodes.push_back(m_iter->second);
    }
  }

  return outNodes;
}

int NodeMgr::getCacheSizeForHeight(int h)
{
  int hCounter = 0;
  int retSize = m_baseCacheSize;

  while (hCounter < h) {
    retSize = retSize / 2;
    ++hCounter;
  }
  return std::max(1, retSize);
}

void NodeMgr::update()
{
  for (int h = 0; h < m_nodesByHeight.size(); ++h) {
    int cacheSize = getCacheSizeForHeight(h);

    int nbhs = m_nodesByHeight[h].size();
    //printf("h: %d cs: %d nbhs: %d\n", h, cacheSize, nbhs);

    if (m_nodesByHeight[h].size() > cacheSize) {
      pruneCacheForHeight(h);
    }
  }
}

void NodeMgr::pruneCacheForHeight(int h)
{
  int cacheSize = getCacheSizeForHeight(h);

  NodeCache& nc = m_nodesByHeight[h];

  std::vector<Node*> nodePtrs;
  
  for (auto np = nc.begin();
       np != nc.end();
       ++np) {
    nodePtrs.push_back(np->second);
  }
  
  std::sort(nodePtrs.begin(), nodePtrs.end(), [](Node* np1, Node* np2) {
    return np1->getLastUsed() < np2->getLastUsed();
  });

  for (int i = 0; i < nc.size() - cacheSize; ++i) {
    Node* n = nodePtrs[i];
    Coord* c = n->getCoord();
    nc.erase(*c);
    n->destroy();
  }
}

void NodeMgr::populate(Coord c, TileLayer layer)
{
  getNode(c, layer);
}

Node* NodeMgr::getNode(Coord c, TileLayer layer)
{
  if (c.h >= m_nodesByHeight.size()) {
    m_nodesByHeight.resize(c.h + 1);
  }

  NodeCache& nc = m_nodesByHeight[c.h];

  auto node_it = nc.find(c);
  Node* nodePtr;
  if (node_it != nc.end()) {
    nodePtr = node_it->second;
  } else {
    nodePtr = new Node(c, this);
    nc[c] = nodePtr;
  }
  nodePtr->populate(layer);
  
  nodePtr->updateLastUsed(m_gameClock->getTime());
  //printf("returning node for %s\n", c.toString().c_str());
  return nodePtr;
}
