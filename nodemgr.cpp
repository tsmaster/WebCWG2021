#include "nodemgr.h"

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

void NodeMgr::update()
{
  // TODO port LRU flushing
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
  //printf("returning node for %s\n", c.toString().c_str());
  return nodePtr;
}
