// node.h

#ifndef node_h
#define node_h

#include <vector>

#include "olcPixelGameEngine.h"

#include "coord.h"
#include "gameclock.h"
#include "layers.h"

class City;
class HighwayGameMode;
class NodeMgr;

class Node
{
 public:
  Node(int x, int y, int h, NodeMgr* nodeMgr);
  Node(Coord c, NodeMgr* nodeMgr) : Node(c.x, c.y, c.h, nodeMgr) {}

  void destroy();

  static void calcExtents(int x, int y, int h,
			  int& outLeft, int& outBottom,
			  int& outRight, int& outTop);

  bool isOrigin() const;

  void populate(TileLayer newLayer);

  Coord* getCoord() { return m_coord; }
  Coord getParentCoord();

  void constrainFromNothing();

  void constrainFromParent(Node& parentNode);

  void constrainFromChild(Node& childNode);
  
  void draw(olc::PixelGameEngine* pge, HighwayGameMode* mode);
  void drawLabel(olc::PixelGameEngine* pge, HighwayGameMode* mode);

  void getBaseExtents(int& outLeft, int& outBottom,
		      int& outRight, int& outTop);

  void paveRoads();

  void paveTo();

  void paveCrossTileRoad(Node& neighborNode);

  bool isLocnInNodesExtents(Coord coord);

  void updateLastUsed(unsigned int tm) { m_lastAccessed = tm; }
  unsigned int getLastUsed() { return m_lastAccessed; }

  bool isCoordInChildCities(Coord& childCoord);

 private:
  void drawRoads(olc::PixelGameEngine* pge, HighwayGameMode* mode);

  void pickH1CandidateLocations();

  void getH0CityFromParent();
  
  NodeMgr* m_nodeMgr;

  Coord* m_coord;
  olc::Pixel m_color = olc::Pixel(0, 0, 200);
  unsigned int m_lastAccessed;

  bool m_isCity;
  City* m_city;

  std::vector<Coord> m_childCityCoords;
  std::vector<Coord> m_connectedCities;
  
  // pavedLinks
  // pavedDirs

  // the layer to which this tile has been populated  
  TileLayer m_populatedLayer; 
};

#endif // node_h
