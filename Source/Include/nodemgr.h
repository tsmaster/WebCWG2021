#ifndef nodemgr_h
#define nodemgr_h

#include <map>
#include <vector>

#include "layers.h"

class Coord;
class GameClock;
class Node;

using NodeCache = std::map<Coord, Node*>;

class NodeMgr
{
 public:
  void init(unsigned int cacheSize, GameClock* gameClock);

  std::vector<Node*> getNodes();

  void update();

  void populate(Coord c, TileLayer layer);

  Node* getNode(Coord c, TileLayer layer);

  std::vector<Node*> getCityNodesInRadius(Coord center, float radius);

 protected:
  int getCacheSizeForHeight(int height);
  void pruneCacheForHeight(int height);

 private:
  unsigned int m_baseCacheSize;
  GameClock* m_gameClock;

  std::vector<NodeCache> m_nodesByHeight;
};


#endif //nodemgr_h
