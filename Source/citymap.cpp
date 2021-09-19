
#include "citymap.h"

#include <algorithm>
#include <cmath>
#include <random>

#include "olcPixelGameEngine.h"

#include "bdg_random.h"
#include "carswithguns.h"


void CityMap::populate(int x, int y, int population, bool eE, bool eN, bool eW, bool eS, olc::Sprite* citySprite)
{
  printf("populating %d %d %d\n", x, y, population);
  m_citySprite = citySprite;
  m_x = x;
  m_y = y;
  
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
    //Vec2i(9, 1),
    Vec2i(9, 4),
    //Vec2i(18, 2),
    //Vec2i(21, 2),
    //Vec2i(18, 6),
    //Vec2i(21, 6),

    Vec2i(9, 7), // water
    Vec2i(9, 7),
    Vec2i(9, 7),

    Vec2i(19, 9), // forest gr
    //Vec2i(19, 12), // forest br

    Vec2i(21, 10), // tree gr
    Vec2i(22, 8),
    Vec2i(22, 9),
    Vec2i(22, 10),
    
    //Vec2i(21, 13), // tree br
    //Vec2i(22, 11),
    //Vec2i(22, 12),
    //Vec2i(22, 13),
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

  std::set<Vec2i> pavedTiles;
  
  if (eE) {
    int exitY = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(radius, exitY, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
      pavedTiles.insert(b);
    }

    setTileAt(radius, exitY, 1, 16);
  }

  if (eN) {
    int exitX = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(exitX, radius, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
      pavedTiles.insert(b);
    }
    
    setTileAt(exitX, radius, 3, 17);
  }

  if (eW) {
    int exitY = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(-radius, exitY, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
      pavedTiles.insert(b);
    }

    setTileAt(-radius, exitY, 1, 16);
  }
  
  if (eS) {
    int exitX = randomrange(-radius/2, radius/2+1);

    for (Vec2i b : randBres(exitX, -radius, cx, cy)) {
      setTileAt(b.x, b.y, 9, 16);
      pavedTiles.insert(b);
    }
    
    setTileAt(exitX, -radius, 3, 17);
  }

  setTileAt(cx, cy, 2, 15); // plus

  int desiredNumBuildings = int(floor((population / 1000.0f) + 0.5f));

  int passesUsed = 0;
  int maxPasses = 10;

  std::vector<Vec2i> peoplePosns;
  
  while (true) {
    peoplePosns = makePeoplePosns(pavedTiles, desiredNumBuildings,
				  -radius, -radius,
				  radius, radius);

    if ((peoplePosns.size() >= desiredNumBuildings) || (passesUsed >= maxPasses)) {
      break;
    }
    ++passesUsed;

    float longestDist = -1.0f;
    Vec2i newLoc;
    Vec2i nearestPos;
    
    for (int i = 0; i < 16; ++i) {
      int rx = randomrange(-radius, radius + 1);
      int ry = randomrange(-radius, radius + 1);

      Vec2i rPos = Vec2i(rx, ry);
      Vec2i nearPos = findNearestPos(rPos, pavedTiles);
      float dist = rPos.distEuclid(nearPos);
      if ((longestDist < 0.0f) || (dist > longestDist)) {
	longestDist = dist;
	newLoc = rPos;
	nearestPos = nearPos;
      }
    }

    for (Vec2i hackTile : randBres(newLoc.x, newLoc.y, nearestPos.x, nearestPos.y)) {
      pavedTiles.insert(hackTile);
      setTileAt(hackTile.x, hackTile.y, 9, 16);
    }
  }

  /*
  printf("desired Num buildings: %d\n", desiredNumBuildings);
  printf("populated people: %d\n", (int)peoplePosns.size());
  printf("passes used: %d\n", passesUsed);
  for (Vec2i ppos : peoplePosns) {
    printf("pos: %d %d\n", ppos.x, ppos.y);
  }
  */

  std::vector<Vec2i> personTiles = {
    Vec2i(24, 0),
    Vec2i(24, 3),
    Vec2i(24, 6),
    Vec2i(24, 9),
    Vec2i(24, 12),
    Vec2i(24, 15),
  };
  
  for (Vec2i personPosn : peoplePosns) {
    int personTileIndex = randomrange(0, personTiles.size());
    Vec2i pt = personTiles[personTileIndex];
    
    setTileAt(personPosn.x, personPosn.y,
	      pt.x, pt.y);
  }
}

Vec2i CityMap::findNearestPos(Vec2i p, std::set<Vec2i> vecSet)
{
  float nearestDist = -1.0f;
  Vec2i closestLoc;

  for (Vec2i v : vecSet) {
    float dist = p.distEuclid(v);
    if ((nearestDist < 0.0f) || (dist < nearestDist)) {
      closestLoc = v;
      nearestDist = dist;
    }
  }
  return closestLoc;
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

std::vector<Vec2i> generateCoordsInEuclideanRadius(Vec2i center, float radius)
{
  int cx = center.x;
  int cy = center.y;

  int minX = int(floor(cx - radius));
  int maxX = int(ceil(cx + radius));
  int minY = int(floor(cy - radius));
  int maxY = int(ceil(cy + radius));

  std::vector<Vec2i> outVec;

  float radSqr = radius * radius;

  for (int x = minX; x <= maxX; ++x) {
    for (int y = minY; y <= maxY; ++y) {
      int dx = x - cx;
      int dy = y - cy;

      int distSqr = dx*dx + dy*dy;
      if (distSqr <= radSqr) {
	outVec.push_back(Vec2i(x,y));
      }
    }
  }
  return outVec;
}

std::vector<Vec2i> CityMap::makePeoplePosns(std::set<Vec2i> pavedTiles,
					    int desiredNumPeople,
					    int minX, int minY,
					    int maxX, int maxY)
{
  float closeToRoadDist = 1.1f;
  float closeToPersonDist = 3.7f;
  
  std::vector<Vec2i> nearRoadTiles;

  for (Vec2i tilePos : pavedTiles) {
    for (Vec2i roadPos : generateCoordsInEuclideanRadius(tilePos, closeToRoadDist)) {
      if ((roadPos.x < minX) ||
	  (roadPos.x > maxX) ||
	  (roadPos.y < minY) ||
	  (roadPos.y > maxY)) {
	// out of bounds
	continue;
      }
      if (pavedTiles.find(roadPos) != pavedTiles.end()) {
	// already paved
	continue;
      }
      nearRoadTiles.push_back(roadPos);
    }
  }

  unsigned int seed = makeSeedKey(m_x,
				  m_y,
				  desiredNumPeople,
				  "CITY CITIZEN SHUFFLE");
  
  std::shuffle(nearRoadTiles.begin(),
	       nearRoadTiles.end(),
	       std::default_random_engine(seed));

  std::vector<Vec2i> outPosns;
  
  while ((nearRoadTiles.size() > 0) && (outPosns.size() < desiredNumPeople)) {
    Vec2i candidateTile = nearRoadTiles.back();
    nearRoadTiles.pop_back();

    bool isClose = false;
    for (Vec2i exOutPos : outPosns) {
      if (exOutPos.distEuclid(candidateTile) <= closeToPersonDist) {
	isClose = true;
	break;
      }
    }
    if (!isClose) {
      outPosns.push_back(candidateTile);
    }
  }
  return outPosns;
}
