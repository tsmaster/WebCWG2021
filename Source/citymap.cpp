
#include "citymap.h"

#include <cmath>

#include "olcPixelGameEngine.h"

#include "bdg_random.h"
#include "carswithguns.h"


void CityMap::populate(int x, int y, int population, bool eE, bool eN, bool eW, bool eS, olc::Sprite* citySprite)
{
  printf("populating %d %d %d\n", x, y, population);
  m_citySprite = citySprite;
  unsigned int seed = makeSeedKey(x, y, population, "CITY MAP");
  srand(seed);
  
  int radius = radiusForPopulation(population);

  printf("radius: %d\n", radius);

  int hr = radius / 2;

  int cx = randomrange(-hr, hr+1) +
    randomrange(-hr, hr+1) +
    randomrange(-hr, hr+1);

  int cy = randomrange(-hr, hr+1) +
    randomrange(-hr, hr+1) +
    randomrange(-hr, hr+1);

  cx = clamp(cx, -radius + 1, radius);
  cy = clamp(cy, -radius + 1, radius);

  printf("city center: %d %d\n", cx, cy);

  std::vector<Vec2i> groundTiles = {
    Vec2i(1, 1),
    Vec2i(1, 1),
    Vec2i(1, 1),
    
    Vec2i(1, 4),
    Vec2i(9, 1),
    Vec2i(9, 4),
    Vec2i(18, 2),
    Vec2i(21, 2),
    Vec2i(18, 6),
    Vec2i(21, 6),

    Vec2i(9, 7), // water
    Vec2i(9, 7),
    Vec2i(9, 7),

    Vec2i(19, 9), // forest gr
    Vec2i(19, 12), // forest br

    Vec2i(21, 10), // tree gr
    Vec2i(22, 8),
    Vec2i(22, 9),
    Vec2i(22, 10),
    
    Vec2i(21, 13), // tree br
    Vec2i(22, 11),
    Vec2i(22, 12),
    Vec2i(22, 13),

    
  };
  
  for (int gx = - radius; gx <= radius; ++gx) {
    for (int gy = - radius; gy <= radius; ++gy) {
      int chosenTileIndex = randomrange(0, groundTiles.size());
      Vec2i chosenTile = groundTiles[chosenTileIndex];
      setTileAt(gx, gy, chosenTile.x, chosenTile.y);
    }    
  }

  setTileAt(cx-1, cy+1, 8, 11); // mailbox
  setTileAt(cx, cy+1, 3, 14);  // bench n
  setTileAt(cx-1, cy, 3, 13);  // bench w
  setTileAt(cx+1, cy, 3, 12);  // bench e  
  setTileAt(cx+1, cy+1, 9, 9); // trash can?
  
  if (eE) {
    int exitY = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(radius, exitY, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
    }

    setTileAt(radius, exitY, 1, 16);
  }

  if (eN) {
    int exitX = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(exitX, radius, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
    }
    
    setTileAt(exitX, radius, 3, 17);
  }

  if (eW) {
    int exitY = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(-radius, exitY, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
    }

    setTileAt(-radius, exitY, 1, 16);
  }
  
  if (eS) {
    int exitX = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(exitX, -radius, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
    }
    
    setTileAt(exitX, -radius, 3, 17);
  }

  setTileAt(cx, cy, 2, 15); // plus
  
}

std::vector<Vec2i> CityMap::randBres(int sx, int sy, int ex, int ey)
{
  std::vector<Vec2i> outVec;

  while (true) {
    outVec.push_back(Vec2i(sx, sy));

    if ((sx == ex) &&
	(sy == ey)) {
      return outVec;
    }

    int dx = ex - sx;
    int dy = ey - sy;

    int adx = abs(dx);
    int ady = abs(dy);

    int stepX = clamp(dx, -1, 2);
    int stepY = clamp(dy, -1, 2);

    int stepRand = randomrange(0, adx + ady);
    if (stepRand < adx) {
      sx += stepX;
    } else {
      sy += stepY;
    }
  }
}

void CityMap::destroy()
{
  m_tileMap.clear();
  m_citySprite = NULL;
}

int CityMap::radiusForPopulation(int population)
{
  return int(ceil(log(population)));
}

void CityMap::setTileAt(int wx, int wy, int tx, int ty)
{
  Vec2i worldCoord = Vec2i(wx, wy);
  Vec2i tileCoord = Vec2i(tx, ty);

  m_tileMap[worldCoord] = tileCoord;
}

void CityMap::draw(CarsWithGuns* game)
{
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  int scx = 320;
  int scy = 240;
  
  for(auto mapIter : m_tileMap) {
    Vec2i wc = mapIter.first;
    Vec2i tc = mapIter.second;

    olc::vi2d vScreenLocation = { scx + 16 * wc.x, scy - 16 * wc.y };
    olc::vi2d vTileLocation = {16 * tc.x, 16 * tc.y};
    olc::vi2d vTileSize = {16, 16};
    
    game->DrawPartialSprite(vScreenLocation, m_citySprite,
			    vTileLocation, vTileSize);
  }

  game->SetPixelMode(currentPixelMode);
}
