#ifndef nodemgr_h
#define nodemgr_h

class GameClock;

class NodeMgr
{
 public:
  NodeMgr(unsigned int cacheSize, GameClock* gameClock);

 private:
  unsigned int m_baseCacheSize;
  GameClock* m_gameClock;  
};


#endif //nodemgr_h
