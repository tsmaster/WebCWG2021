#ifndef citymap_h
#define citymap_h

#include <map>
#include <set>
#include <vector>

#include "olcPixelGameEngine.h"

#include "bdg_math.h"


class CarsWithGuns;

class CityMap
{
 public:
  void populate(int x, int y, int population, bool eE, bool eN, bool eW, bool eS, olc::Sprite* citySprite);

  void destroy();

  void draw(CarsWithGuns* game);
  
 protected:
  int radiusForPopulation(int population);

  void setTileAt(int wx, int wy, int tx, int ty);

  std::vector<Vec2i> makePeoplePosns(std::set<Vec2i> pavedTiles, int desiredNumPeople,
				     int minX, int minY,
				     int maxX, int maxY);

  std::vector<Vec2i> randBres(int sx, int sy, int ex, int ey);

  Vec2i findNearestPos(Vec2i p, std::set<Vec2i> posSet);

  std::map<Vec2i, Vec2i> m_tileMap;
  olc::Sprite* m_citySprite;
 private:
  int m_x;
  int m_y;
};

#endif // citymap_h
