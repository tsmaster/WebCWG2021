// node.cpp

#include "node.h"

#include <algorithm>
#include <random>
#include <stdlib.h>

#include "bdg_random.h"
#include "city.h"
#include "constants.h"
#include "coord.h"
#include "kruskal.h"
#include "mode_highway.h"


Node::Node(int x, int y, int h, NodeMgr* nodeMgr)
{
  m_nodeMgr = nodeMgr;
  m_coord = new Coord(x, y, h);
  m_color = olc::Pixel(0, 0, 200);
  m_isCity = false;
  m_city = NULL;
  m_populatedLayer = TileLayer::EMPTY;
}

void Node::destroy()
{
  delete m_coord;
}

void Node::draw(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  int xLeft, yBottom, xRight, yTop;
  getBaseExtents(xLeft, yBottom, xRight, yTop);

  Vec2f screenBottomLeft = mode->tileToScreenCoord(pge, Vec2f(xLeft, yBottom));
  Vec2f screenTopRight = mode->tileToScreenCoord(pge, Vec2f(xRight, yTop));

  int sLeft = int(screenBottomLeft.x);
  int sBottom = int(screenBottomLeft.y);
  int sRight = int(screenTopRight.x);
  int sTop = int(screenTopRight.y);

  //printf("sl: %d sb: %d sr: %d st: %d\n", sLeft, sBottom, sRight, sTop);

  if (m_coord->h == 0) {
    pge->FillRect(sLeft, sTop, sRight-sLeft, sBottom-sTop, m_color);
    drawRoads(pge, mode);
    if (m_isCity) {
      pge->FillCircle((sRight + sLeft) / 2,
		      (sTop + sBottom) / 2,
		      (mode->getTileScale() * 3) / 8,
		      olc::Pixel(50, 50, 50));
    }      
  } else {
    //printf("drawing node at %s\n", m_coord->toString().c_str());
    //printf("l: %d, b: %d r: %d t: %d\n", xLeft, yBottom, xRight, yTop);
    
    pge->DrawRect(sLeft, sTop, sRight-sLeft, sBottom-sTop, m_color);
  }
}

void Node::drawLabel(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  if (m_isCity) {
    int xLeft, yBottom, xRight, yTop;
    getBaseExtents(xLeft, yBottom, xRight, yTop);

    Vec2f screenBottomLeft = mode->tileToScreenCoord(pge, Vec2f(xLeft, yBottom));

    olc::Pixel color = olc::Pixel(0, 0, 150);
    std::string cityName = std::string("C");
    if (m_city != NULL) {
      cityName = m_city->getName();
    }
    pge->DrawString(int(screenBottomLeft.x), int(screenBottomLeft.y),
		    cityName, color);
  }
}

void Node::drawRoads(olc::PixelGameEngine* pge, HighwayGameMode* mode)
{
  if (m_coord->h != 0) {
    return;
  }

  int xLeft, yBottom, xRight, yTop;
  getBaseExtents(xLeft, yBottom, xRight, yTop);

  Vec2f screenBottomLeft = mode->tileToScreenCoord(pge, Vec2f(xLeft, yBottom));
  Vec2f screenTopRight = mode->tileToScreenCoord(pge, Vec2f(xRight, yTop));

  int sLeft = int(screenBottomLeft.x);
  int sBottom = int(screenBottomLeft.y);
  int sRight = int(screenTopRight.x);
  int sTop = int(screenTopRight.y);

  int sMidX = (sRight + sLeft) / 2;
  int sMidY = (sTop + sBottom) / 2;

  int offset = std::max(1, int(mode->getTileScale() * 0.2));

  olc::Pixel color = olc::Pixel(90, 90, 90);

  if (m_pavedLinksH0.find(0) != m_pavedLinksH0.end()) {
    pge->FillRect(sMidX - offset, sMidY - offset,
		  sRight - sMidX + offset, 2 * offset, color);
  }
  if (m_pavedLinksH0.find(1) != m_pavedLinksH0.end()) {
    pge->FillRect(sMidX - offset, sTop,
		  2 * offset, sMidY - sTop + offset, color);
  }
  if (m_pavedLinksH0.find(2) != m_pavedLinksH0.end()) {
    pge->FillRect(sLeft, sMidY - offset,
		  sMidX - sLeft + offset, 2 * offset, color);
  }
  if (m_pavedLinksH0.find(3) != m_pavedLinksH0.end()) {
    pge->FillRect(sMidX - offset, sMidY - offset,
		  2 * offset, sBottom - sMidY + offset, color);
  }
}


void Node::getBaseExtents(int& outLeft, int& outBottom,
			  int& outRight, int& outTop)
{
  Node::calcExtents(m_coord->x,
		    m_coord->y,
		    m_coord->h,
		    outLeft, outBottom,
		    outRight, outTop);
}

/// outLeft is left
/// outRight is outside
void Node::calcExtents(int x, int y, int h,
		       int& outLeft, int& outBottom,
		       int& outRight, int& outTop)
{
  if (h == 0) {
    outLeft = x;
    outBottom = y;
    outRight = x+1;
    outTop = y+1;
    return;
  }

  //printf("calcing extents for x %d y %d h %d\n", x, y, h);
  // TODO handle odd and even height offset correctly
  int newH = h - 1;
  int newLeft = x * SCALE_FACTOR - ODD_HEIGHT_OFFSET;
  int newBottom = y * SCALE_FACTOR - ODD_HEIGHT_OFFSET;

  int newRight = newLeft + SCALE_FACTOR;
  int newTop = newBottom + SCALE_FACTOR;

  int newBLL, newBLB, newBLR, newBLT;
  int newTRL, newTRB, newTRR, newTRT;
  
  calcExtents(newLeft, newBottom, newH, newBLL, newBLB, newBLR, newBLT);
  calcExtents(newRight, newTop, newH, newTRL, newTRB, newTRR, newTRT);

  outLeft = newBLL;
  outBottom = newBLB;
  outRight = newTRL;
  outTop = newTRB;

  //printf("outLeft: %d outRight: %d\n", outLeft, outRight);
}


void Node::populate(TileLayer newLayer)
{
  if (m_populatedLayer >= newLayer) {
    return;
  }

  TileLayer oldLayer = m_populatedLayer;

  printf("populating x %d y %d h %d l %d\n",
	 m_coord->x,
	 m_coord->y,
	 m_coord->h,
	 int(newLayer));
  printf("old layer: %d\n", (int)oldLayer);

  // cities
  if ((oldLayer < TileLayer::H1_CITY_CANDIDATE_LOCN) &&
      (newLayer >= TileLayer::H1_CITY_CANDIDATE_LOCN) &&
      (m_coord->h == 1)) {
    // choose n candidate locations
    printf("picking h1 city candidate locations for %s\n", m_coord->toString().c_str());
    pickH1CandidateLocations();
    
    m_populatedLayer = TileLayer::H1_CITY_CANDIDATE_LOCN;
    //printf("H1 city candidate locations complete\n");
  }

  if ((oldLayer < TileLayer::H2_CITY_POPULATION_DISTRIBUTION) &&
      (newLayer >= TileLayer::H2_CITY_POPULATION_DISTRIBUTION) &&
      (m_coord->h == 2)) {
    distributeH2CityPopulation();
      
    m_populatedLayer = TileLayer::H2_CITY_POPULATION_DISTRIBUTION;
    printf("H2 city pop dist complete\n");
  }

  if ((oldLayer < TileLayer::H0_CITY_LOCN_NAME_POP) &&
      (newLayer >= TileLayer::H0_CITY_LOCN_NAME_POP) &&
      (m_coord->h == 0)) {
    populateCityLocationNamePopulation();
      
    m_populatedLayer = TileLayer::H0_CITY_LOCN_NAME_POP;
    printf("H0 locn name pop complete\n");
  }

  // roads
  if ((oldLayer < TileLayer::H1_LOCAL_ROADS) &&
      (newLayer >= TileLayer::H1_LOCAL_ROADS) &&
      (m_coord->h == 1)) {
    generateH1TileRoads();
    
    m_populatedLayer = TileLayer::H1_LOCAL_ROADS;
    //printf("local roads complete\n");
  }
  
  if ((oldLayer < TileLayer::H1_CROSS_TILE_ROADS) &&
      (newLayer >= TileLayer::H1_CROSS_TILE_ROADS)) {
    if (m_coord->h == 1) {
      paveCrossTileRoads();
    }
    
    m_populatedLayer = TileLayer::H1_CROSS_TILE_ROADS;
    //printf("cross tile roads complete\n");
  }

  if ((oldLayer < TileLayer::H0_ROAD) &&
      (newLayer >= TileLayer::H0_ROAD)) {
    if (m_coord->h == 0) {
      collectH0Roads();
    }
    
    m_populatedLayer = TileLayer::H0_ROAD;
    //printf("cross tile roads complete\n");
  }

  if ((oldLayer < TileLayer::FRACTAL_LAND_COLOR) &&
      (newLayer >= TileLayer::FRACTAL_LAND_COLOR)) {
    printf("doing fractal for %s\n", m_coord->toString().c_str());
    if (isOrigin()) {
      if (m_coord->h == 0) {
	printf("constraining from nothing\n");
	constrainFromNothing();
      } else {
	Coord childCoord = Coord(m_coord->x,
				 m_coord->y,
				 m_coord->h - 1);
      
	printf("constraining from child %s\n", childCoord.toString().c_str());
	Node* childNode = m_nodeMgr->getNode(childCoord, TileLayer::FRACTAL_LAND_COLOR);
	constrainFromChild(*childNode);
      }
    } else {
      Coord parentCoord = getParentCoord();
      printf("constraining from parent %s\n", parentCoord.toString().c_str());
      Node* parentNode = m_nodeMgr->getNode(parentCoord, TileLayer::FRACTAL_LAND_COLOR);
      constrainFromParent(*parentNode);
    }
    
    m_populatedLayer = TileLayer::FRACTAL_LAND_COLOR;
    printf("fractal portion complete for %s\n", m_coord->toString().c_str());
  }
  
  if ((oldLayer < TileLayer::H0_FINAL) &&
      (newLayer >= TileLayer::H0_FINAL)) {
    if (m_coord->h == 0) {
      finalizeH0();
    }
    
    m_populatedLayer = TileLayer::H0_FINAL;
    //printf("finalized\n");
  }
}

bool Node::isOrigin() const
{
  return ((m_coord->x == 0) &&
	  (m_coord->y == 0));
}

void Node::constrainFromNothing()
{
  m_color = olc::Pixel(50, 150, 50);
}

void Node::constrainFromChild(Node& childNode)
{
  unsigned int seed = makeSeedKey(m_coord->x, m_coord->y, m_coord->h, "COLOR");
  srand(seed);
  olc::Pixel cp = childNode.m_color;
  
  int cr = std::clamp(cp.r + randomrange(-5, 6), 0, 255);
  int cg = std::clamp(cp.g + randomrange(-5, 6), 0, 255);
  int cb = std::clamp(cp.b + randomrange(-5, 6), 0, 255);
  m_color = olc::Pixel(cr, cg, cb);
}

void Node::constrainFromParent(Node& parentNode)
{
  unsigned int seed = makeSeedKey(m_coord->x, m_coord->y, m_coord->h, "COLOR");
  srand(seed);
  olc::Pixel pp = parentNode.m_color;

  int variance = 25;
  int cr = std::clamp(pp.r + randomrange(-variance, variance + 1), 0, 255);
  int cg = std::clamp(pp.g + randomrange(-variance, variance + 1), 0, 255);
  int cb = std::clamp(pp.b + randomrange(-variance, variance + 1), 0, 255);
  m_color = olc::Pixel(cr, cg, cb);
}

Coord Node::getParentCoord()
{
  // TODO handle odd height offset
  int px = int(floor((m_coord->x + ODD_HEIGHT_OFFSET) / float(SCALE_FACTOR)));
  int py = int(floor((m_coord->y + ODD_HEIGHT_OFFSET) / float(SCALE_FACTOR)));
  return Coord(px, py, m_coord->h + 1);
}

void Node::pickH1CandidateLocations()
{
  printf("making H1 city candidates for x: %d y: %d h: %d\n",
	 m_coord->x, m_coord->y, m_coord->h);
  
  unsigned int seedKey = makeSeedKey(m_coord->x, m_coord->y, m_coord->h, "ISCITY");

  int left, bottom, right, top;
  getBaseExtents(left, bottom, right, top);

  while (m_childCityCoords.size() < CITY_COUNT_PER_CELL) {
    int rx = randomrange(left, right);
    int ry = randomrange(bottom, top);
    Coord rCoord = Coord(rx, ry, 0);

    bool tooClose = false;
    for (auto existingCoord : m_childCityCoords) {
      int dist = existingCoord.manhattanDist(rCoord);
      if (dist < MIN_CITY_SPACE) {
	tooClose = true;
	break;
      }
    }
    if (tooClose) {
      continue;
    }
    m_childCityCoords.push_back(rCoord);
  }
}

std::vector<Coord> Node::getCityCoords()
{
  return m_childCityCoords;
}

void Node::setIsCity(bool isCity)
{
  m_isCity = isCity;
  if (isCity) {
    printf("making new city in setIsCity\n");
    m_city = new City(m_coord->x, m_coord->y);    
  } else {
    m_city = NULL;
  }   
}

bool Node::isCoordInChildCities(Coord& childCoord)
{
  auto coord_it = std::find(m_childCityCoords.begin(),
			    m_childCityCoords.end(),
			    childCoord);

  return coord_it != m_childCityCoords.end();
}

void Node::populateCityLocationNamePopulation()
{
  Coord h1Coord = getParentCoord();
  Node* h1Node = m_nodeMgr->getNode(h1Coord, TileLayer::H1_CITY_CANDIDATE_LOCN);
  Coord h2Coord = h1Node->getParentCoord();
  Node* h2Node = m_nodeMgr->getNode(h2Coord, TileLayer::H2_CITY_POPULATION_DISTRIBUTION);

  if (h1Node->isCoordInChildCities(*m_coord)) {
    setIsCity(true);
    m_city->setPopulation(h2Node->getPopulationForCoord(*m_coord));
  }
}

int Node::getPopulationForCoord(Coord coord)
{
  auto pop_iter = m_popForCoord.find(coord);
  if (pop_iter == m_popForCoord.end()) {
    return -1;
  }
  return pop_iter->second;
}

void Node::generateH1TileRoads()
{
  // kruskal up some connections
  std::vector<KruskPair> pairs = computeKruskal(m_childCityCoords);
  
  // foreach connection, pave the connection
  for (auto pair : pairs) {
    int i0 = pair.first;
    int i1 = pair.second;

    //printf("connecting %d to %d\n", i0, i1);

    paveTo(m_childCityCoords[i0],
	   m_childCityCoords[i1],
	   NULL);
  }
}

void Node::paveTo(Coord startCoord, Coord endCoord, Node* neighborNode)
{
  unsigned int paveSeed = makeSeedKey(m_coord->x, m_coord->y, m_coord->h, "PAVE LOCAL");
  srand(paveSeed);

  while (!(startCoord == endCoord)) {
    int bestDist = -1;
    std::vector<Coord> bestCandidates;

    Vec2i deltas[] = {
      Vec2i(-1, 0),
      Vec2i(1, 0),
      Vec2i(0, -1),
      Vec2i(0, 1)};
      
    for (Vec2i delta : deltas) {
      int dx = delta.x;
      int dy = delta.y;

      int nx = startCoord.x + dx;
      int ny = startCoord.y + dy;

      Coord newCoord = Coord(nx, ny, 0);
      int newDist = newCoord.manhattanDist(endCoord);

      if ((bestDist < 0) ||
	  (newDist < bestDist)) {
	bestDist = newDist;
	bestCandidates.clear();
	bestCandidates.push_back(newCoord);
      } else if (newDist == bestDist) {
	bestCandidates.push_back(newCoord);
      }
    }

    int newIndex = randomrange(0, bestCandidates.size());
    Coord newStartCoord = bestCandidates[newIndex];

    using IntPair = std::pair<int, int>;
    IntPair dirs;
    
    if (newStartCoord.x == startCoord.x) {
      if (newStartCoord.y > startCoord.y) {
	dirs = IntPair(1, 3);
      } else {
	dirs = IntPair(3, 1);
      }
    } else {
      if (newStartCoord.x > startCoord.x) {
	dirs = IntPair(0, 2);
      } else {
	dirs = IntPair(2, 0);
      }
    }

    std::vector<Node*> nodesToPave;
    nodesToPave.push_back(this);
    if (neighborNode != NULL) {
      nodesToPave.push_back(neighborNode);
    }

    for (Node* paveNode : nodesToPave) {
      if (paveNode->isInNodeExtents(startCoord)) {
	paveNode->pave(startCoord, dirs.first);
      }
      if (paveNode->isInNodeExtents(newStartCoord)) {
	paveNode->pave(newStartCoord, dirs.second);
      }
    }

    startCoord = newStartCoord;
  }
}

void Node::pave(Coord startCoord, int direction) {
  //printf("paving from %s in dir %d\n", startCoord.toString().c_str(), direction);
  auto pd_it = m_pavedDirs.find(startCoord);

  if (pd_it == m_pavedDirs.end()) {
    // not found
    PaveDirSet newSet;
    newSet.insert(direction);
    m_pavedDirs[startCoord] = newSet;
  } else {
    pd_it->second.insert(direction);
  }
}

bool Node::isInNodeExtents(Coord c) {
  int left, bottom, right, top;
  getBaseExtents(left, bottom, right, top);

  return ((c.x >= left) &&
	  (c.y >= bottom) &&
	  (c.x < right) &&
	  (c.y < top));
}

void Node::finalizeH0() {
}

PaveDirSet Node::getPavedLinks(Coord childCoord)
{
  auto pd_it = m_pavedDirs.find(childCoord);
  
  if (pd_it == m_pavedDirs.end()) {
    // not found;
    PaveDirSet empty;
    return empty;
  } else {
    return pd_it->second;
  }
}

void Node::paveCrossTileRoads()
{
  Vec2i deltas[] = {
    Vec2i(-1, 0),
    Vec2i(1, 0),
    Vec2i(0, -1),
    Vec2i(0, 1)};
      
  for (Vec2i delta : deltas) {
    int nx = m_coord->x + delta.x;
    int ny = m_coord->y + delta.y;

    Coord newCoord = Coord(nx, ny, m_coord->h);
    Node* neighborNode = m_nodeMgr->getNode(newCoord, TileLayer::H1_LOCAL_ROADS);

    paveCrossTileRoad(neighborNode);
  }    
}

void Node::paveCrossTileRoad(Node* neighborNode)
{
  int closestApproachDistance = -1;

  using CoordPair = std::pair<Coord, Coord>;

  std::vector<CoordPair> closestCoordPairs;

  for (Coord thisCoord : getPavedCoords()) {
    for (Coord neighborCoord : neighborNode->getPavedCoords()) {
      int dist = neighborCoord.manhattanDist(thisCoord);

      if ((closestApproachDistance < 0) ||
	  (dist < closestApproachDistance)) {
	closestApproachDistance = dist;
	closestCoordPairs.clear();
	CoordPair newCoordPair(thisCoord, neighborCoord);
	closestCoordPairs.push_back(newCoordPair);
      } else if (dist == closestApproachDistance) {
	CoordPair newCoordPair(thisCoord, neighborCoord);
	closestCoordPairs.push_back(newCoordPair);
      }
    }
  }

  Coord* nc = neighborNode->getCoord();
  unsigned int seedKey = makeSeedKey(m_coord->x + nc->x,
				     m_coord->y + nc->y,
				     m_coord->h, "CROSS TILE ROAD");
  srand(seedKey);

  CoordPair chosenPair = closestCoordPairs[randomrange(0, closestCoordPairs.size())];

  if (chosenPair.first < chosenPair.second) {
    paveTo(chosenPair.first, chosenPair.second, neighborNode);
  } else {
    neighborNode->paveTo(chosenPair.second, chosenPair.first, this);
  }
}


std::vector<Coord> Node::getPavedCoords()
{
  std::vector<Coord> outCoords;

  for (auto paveMapItem : m_pavedDirs) {
    if (paveMapItem.second.size() > 0) {
      outCoords.push_back(paveMapItem.first);
    }
  }
  return outCoords;
}

void Node::collectH0Roads()
{
  Coord parentCoord = getParentCoord();
  Node* parentNode = m_nodeMgr->getNode(parentCoord, TileLayer::H1_CROSS_TILE_ROADS);

  m_pavedLinksH0 = parentNode->getPavedLinks(*m_coord);  
}

void Node::distributeH2CityPopulation()
{
  std::vector<Coord> cityCoords;

  int xLeft, yBottom, xRight, yTop;
  getBaseExtents(xLeft, yBottom, xRight, yTop);
  printf("distributing population %d %d %d %d\n", xLeft, yBottom, xRight, yTop);

  for (int x = xLeft; x < xRight; x += SCALE_FACTOR) {
    for (int y = yBottom; y < yTop; y += SCALE_FACTOR) {
      Coord childCoord(x, y, 0);
      Node* childNode = m_nodeMgr->getNode(childCoord, TileLayer::EMPTY);
      Coord h1Coord = childNode->getParentCoord();
      Node* h1Node = m_nodeMgr->getNode(h1Coord, TileLayer::H1_CITY_CANDIDATE_LOCN);

      for (Coord cityCoord : h1Node->getCityCoords()) {
	cityCoords.push_back(cityCoord);
      }
    }
  }

  printf("collected cities\n");

  unsigned int seed = makeSeedKey(m_coord->x,
				  m_coord->y,
				  m_coord->h,
				  "H2 ZIPF DISTR");
  
  std::shuffle(cityCoords.begin(),
	       cityCoords.end(),
	       std::default_random_engine(seed));

  int primaryCityPopulation = randomrange(MIN_PRIMARY_CITY_POPULATION,
					  MAX_PRIMARY_CITY_POPULATION);

  for (int i = 0; i < cityCoords.size(); ++i) {
    int zipf_pop = primaryCityPopulation / (i+1);

    m_popForCoord[cityCoords[i]] = zipf_pop;
  }
}
