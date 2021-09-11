// node.h

#ifndef node_h
#define node_h

#include <vector>

#include "olcPixelGameEngine.h"

class NodeMgr;
class City;
class Coord;

class Node
{
 public:
  Node(int x, int y, int h, NodeMgr* nodeMgr);
  Node(Coord c, NodeMgr* nodeMgr);

  static void calcExtents(int x, int y, int h,
			  int& outLeft, int& outBottom,
			  int& outRight, int& outTop);

  bool isOrigin() const;

  void populate(int newLayer);

  Coord getParentCoord();

  void constrainFromNothing();

  void constrainFromParent(Node& parentNode);

  void constrainFromChild(Node& childNode);
  
  void draw();
  void drawLabels();

  void getBaseExtents();

  void paveRoads();

  void paveTo();

  void paveCrossTileRoad(Node& neighborNode);

  bool isLocnInNodesExtents(Coord coord);

 private:
  void drawRoads();

  
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
  int m_populatedLayer; 
};

#endif // node_h
