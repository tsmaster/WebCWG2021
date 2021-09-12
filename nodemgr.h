#ifndef nodemgr_h
#define nodemgr_h

#include <vector>

class GameClock;
class Node;

class NodeMgr
{
 public:
  NodeMgr(unsigned int cacheSize, GameClock* gameClock);

  std::vector<Node*> getNodes();

 private:
  unsigned int m_baseCacheSize;
  GameClock* m_gameClock;  
};


#endif //nodemgr_h
