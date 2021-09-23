#ifndef citymap_h
#define citymap_h

#include <map>
#include <set>
#include <vector>

#include "olcPixelGameEngine.h"

#include "bdg_math.h"


class CarsWithGuns;

class Building
{
public:
  int x, y, width, height;
};

class CityMap
{
 public:
  void populate(int x, int y, int population, bool eE, bool eN, bool eW, bool eS, olc::Sprite* citySprite);

  void destroy();

  void draw(CarsWithGuns* game);

  bool isLocationPaved(Vec2i loc);

  Vec2i getCityCenterLocn() { return m_cityCenter; }

  Vec2f screenToTileCoord(CarsWithGuns* game, Vec2f screenCoord);
  Vec2f tileToScreenCoord(CarsWithGuns* game, Vec2f tileCoord);

  std::vector<Building> getBuildings() { return m_buildings; }
  
 protected:
  int radiusForPopulation(int population);

  void setTileAt(int wx, int wy, int tx, int ty);

  std::vector<Vec2i> makePeoplePosns(std::set<Vec2i> pavedTiles, int desiredNumPeople,
				     int minX, int minY,
				     int maxX, int maxY);

  std::vector<Vec2i> randBres(int sx, int sy, int ex, int ey);

  Vec2i findNearestPos(Vec2i p, std::set<Vec2i> posSet);

  bool canPlaceBuilding(int x, int y, int w, int h, std::set<Vec2i> pavedSet, int cityRadius);

  void placeBuilding(int x, int y, int w, int h);

 private:
  
  std::map<Vec2i, Vec2i> m_tileMap;
  olc::Sprite* m_citySprite;

  int m_x;
  int m_y;

  Vec2i m_cityCenter;

  std::set<Vec2i> m_pavedLocations;

  std::vector<Building> m_buildings;
};

#endif // citymap_h
