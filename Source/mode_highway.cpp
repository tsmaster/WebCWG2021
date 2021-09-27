// mode_highway.cpp

#include "mode_highway.h"

#include "carswithguns.h"
#include "city.h"
#include "constants.h"
#include "coord.h"
#include "gameclock.h"
#include "layers.h"
#include "main.h"
#include "node.h"

HighwayGameMode::HighwayGameMode()
{
  m_tileScale = START_TILE_SCALE;
  m_viewRadius = START_VIEW_RADIUS;
}

void HighwayGameMode::init(olc::Sprite* menuSprite, olc::Sprite* carSprite,
			   GameClock* gameClock, NodeMgr* nodeMgr)
{
  m_centerCoord = Coord(0, 0, 0);
  m_menuSprite = menuSprite;
  m_carSprite = carSprite;
  m_carPos = Vec2f(0.0f, 0.0f);
  m_carHeading = 0;
  m_gameClock = gameClock;
  m_nodeMgr = nodeMgr;
}

bool HighwayGameMode::update(CarsWithGuns* pge, float elapsedSeconds)
{
  bool modeSwitched = false;
  bool bContinue = handleUserInput(pge, modeSwitched);

  if (modeSwitched) {
    return true;
  }

  if (m_isFindingPath) {
    for (int i = 0; i < 10; ++i) {
      bool isComplete = m_astar.tick();
      if (isComplete) {
	m_isFindingPath = false;
	m_isFollowingPath = true;
	m_path = m_astar.getSolution();
	m_timeRemainingBeforeMove = m_timeToMove;
	break;
      }
    }
  }

  if (m_isFollowingPath) {
    if (m_path.size() == 0) {
      m_isFollowingPath = false;
    } else {
      if (elapsedSeconds >= m_timeRemainingBeforeMove) {
      
	Vec2i nextPosn = m_path[0];
	m_path.erase(m_path.begin());

	int dx = nextPosn.x - m_carPos.x;
	int dy = nextPosn.y - m_carPos.y;
	if ((dx == 0) && (dy == 0)) {
	  //printf("actually not moving\n");
	} else {
	  //printf ("moving on path dx %d dy %d\n", dx, dy);
	  move(dx, dy);
	  m_gameClock->increment();
	}

	m_timeRemainingBeforeMove = m_timeToMove;
      } else {
	m_timeRemainingBeforeMove -= elapsedSeconds;
      }
    }
  }

  float vrSqr = m_viewRadius * m_viewRadius;

  for (int px = int(floor(m_centerCoord.x - m_viewRadius));
       px <= int(ceil(m_centerCoord.x + m_viewRadius));
       ++px) {
    int dx = m_centerCoord.x - px;
    for (int py = int(floor(m_centerCoord.y - m_viewRadius));
	 py <= int(ceil(m_centerCoord.y + m_viewRadius));
	 ++py) {
      int dy = m_centerCoord.y - py;
      int distSqr = dx*dx + dy*dy;
      if (distSqr <= vrSqr) {
	m_nodeMgr->populate(Coord(px, py, 0), TileLayer::H0_FINAL);
      }
    }
  }

  m_nodeMgr->update();
  
  return bContinue;
}

void HighwayGameMode::move(int dx, int dy)
{
  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;

  int nx = cx + dx;
  int ny = cy + dy;

  if (dx == 1) {
    m_carHeading = 0;
  }
  else if (dx == -1) {
    m_carHeading = 4;
  }
  else if (dy == 1) {
    m_carHeading = 2;
  }
  else if (dy == -1) {
    m_carHeading = 6;
  }

  m_centerCoord = Coord(nx, ny, 0);
  m_carPos = Vec2f(nx, ny);

  Node* centerNode = m_nodeMgr->getNode(m_centerCoord, TileLayer::H0_FINAL);
  if (centerNode->isCity()) {
    City* c = centerNode->getCity();
    std::string name = c->getName();
    int population = c->getPopulation();
    printf("city name: %s pop %d\n", name.c_str(), population);

    // todo better formatting
    std::string msg = name + std::string("\npop: ") +std::to_string(population);
    std::vector<ButtonDesc> buttons;
    m_popupLocationPanel.build(msg, buttons);
  } else {
    std::vector<ButtonDesc> buttons;
    m_popupLocationPanel.build("driving", buttons);
  }
}

bool HighwayGameMode::tryEnterCity(CarsWithGuns* game)
{
  Node* centerNode = m_nodeMgr->getNode(m_centerCoord, TileLayer::H0_CITY_LOCN_NAME_POP);
  if (centerNode->isCity()) {
    City* c = centerNode->getCity();

    ModeChangeRequest mcr = ModeChangeRequest::modeChangeRequestFactory(GameMode::GM_CITY);
    mcr.cityName = c->getName();
    mcr.x = m_centerCoord.x;
    mcr.y = m_centerCoord.y;
    mcr.population = c->getPopulation();

    PaveDirSet pavedDirs = centerNode->getSelfPavedDirsH0();
    
    mcr.exitEast = pavedDirs.find(0) != pavedDirs.end();
    mcr.exitNorth = pavedDirs.find(1) != pavedDirs.end();;
    mcr.exitWest = pavedDirs.find(2) != pavedDirs.end();;
    mcr.exitSouth = pavedDirs.find(3) != pavedDirs.end();;

    game->requestGameMode(mcr);
    return true;
  }
  return false;
}

bool HighwayGameMode::handleUserInput(CarsWithGuns* game, bool& outSwitched)
{
  bool bTicked = false;

  bool bContinue = true;

  if (game->GetKey(olc::Key::ESCAPE).bPressed) {
    bContinue = false;
  }

  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;
  
  if (game->GetKey(olc::Key::LEFT).bPressed) {
    move(-1, 0);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::RIGHT).bPressed) {
    move(1, 0);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::DOWN).bPressed) {
    move(0, -1);
    bTicked = true;
  }

  if (game->GetKey(olc::Key::UP).bPressed) {
    move(0, 1);
    bTicked = true;
  }

  if ((game->GetKey(olc::Key::RETURN).bPressed) ||
      (game->GetKey(olc::Key::ENTER).bPressed)) {
    if (tryEnterCity(game)) {
      outSwitched = true;
    }
  }

  if (game->GetKey(olc::Key::PGUP).bPressed) {
    m_tileScale = std::min((m_tileScale * 3) / 2, 64.0f);
  }

  if (game->GetKey(olc::Key::PGDN).bPressed) {
    m_tileScale = std::max((m_tileScale * 2) / 3, 2.0f);
  }
  
  if (game->GetKey(olc::Key::NP_ADD).bPressed) {
    m_viewRadius = std::min(m_viewRadius + 0.25f, 32.0f);
  }

  if (game->GetKey(olc::Key::NP_SUB).bPressed) {
    m_viewRadius = std::min(m_viewRadius - 0.25f, 1.0f);
  }
  
  if (game->GetKey(olc::Key::K1).bPressed) {
    printf("center: %s\n", m_centerCoord.toString().c_str());
  }

  if (game->GetKey(olc::Key::M).bPressed) {
    printf("making mission from highway\n");
    Coord carCoord(m_carPos.x,
		   m_carPos.y,
		   0);
    game->generateMissionSequence(carCoord,
				  3,
				  5.0, 10.0);
  }  

  if (game->GetMouse(olc::Mouse::LEFT).bPressed) {
    int mx = game->GetMouseX();
    int my = game->GetMouseY();

    Vec2f tileDestFloat = screenToTileCoord(game, Vec2f(mx, my));

    m_destTile = Vec2i(int(floor(tileDestFloat.x)),
		       int(floor(tileDestFloat.y)));

    printf("dest tile: %d %d\n", m_destTile.x, m_destTile.y);
    
    std::set<Vec2i> destSet;
    destSet.insert(m_destTile);

    auto expandFunc = [=](Vec2i v){return expandPosn(v);};
    m_astar = bdg_astar::AStar();
    Vec2i intCarPos = Vec2i(int(m_carPos.x),
			    int(m_carPos.y));
    m_astar.requestPath(intCarPos,
			destSet,
			expandFunc,
			80);
    m_isFindingPath = true;
    m_isFollowingPath = false;
  }    

  if (bTicked) {
    m_gameClock->increment();
  }

  return bContinue;
}

std::vector<bdg_astar::Link> HighwayGameMode::expandPosn(Vec2i posn)
{
  const float ROAD_COST = 1;
  const float OFFROAD_COST = 1000;
  
  std::vector<bdg_astar::Link> outLinks;

  Node* centerNode = m_nodeMgr->getNode(Coord(posn.x, posn.y, 0), TileLayer::H0_ROAD);

  PaveDirSet nodePDS = centerNode->getSelfPavedDirsH0();

  bdg_astar::Link eastLink = bdg_astar::Link(Vec2i(posn.x + 1, posn.y), 
					     (nodePDS.find(0) != nodePDS.end()) ? ROAD_COST : OFFROAD_COST);
  outLinks.push_back(eastLink);
  
  bdg_astar::Link northLink = bdg_astar::Link(Vec2i(posn.x, posn.y + 1), 
					      (nodePDS.find(1) != nodePDS.end()) ? ROAD_COST : OFFROAD_COST);
  outLinks.push_back(northLink);
  
  bdg_astar::Link westLink = bdg_astar::Link(Vec2i(posn.x - 1, posn.y), 
					     (nodePDS.find(2) != nodePDS.end()) ? ROAD_COST : OFFROAD_COST);
  outLinks.push_back(westLink);
  
  bdg_astar::Link southLink = bdg_astar::Link(Vec2i(posn.x, posn.y - 1), 
					      (nodePDS.find(3) != nodePDS.end()) ? ROAD_COST : OFFROAD_COST);
  outLinks.push_back(southLink);
  
  return outLinks;
}

void HighwayGameMode::draw(CarsWithGuns* pge)
{
  pge->Clear(olc::DARK_GREEN);

  int sw = pge->ScreenWidth();
  int sh = pge->ScreenHeight();

  int pcx = sw / 2;
  int pcy = sh / 2;

  olc::Pixel lineColor = olc::Pixel(25, 150, 25);

  Vec2f topLeftTileCoord = screenToTileCoord(pge, Vec2f(0,0));
  Vec2f bottomRightTileCoord = screenToTileCoord(pge, Vec2f(sw, sh));

  float leftTileCoord = topLeftTileCoord.x;
  float topTileCoord = topLeftTileCoord.y;

  float rightTileCoord = bottomRightTileCoord.x;
  float bottomTileCoord = bottomRightTileCoord.y;

  for (int x = ceil(leftTileCoord);
       x <= floor(rightTileCoord);
       ++x) {
    Vec2f projVec = tileToScreenCoord(pge, Vec2f(x, 0));
    int sx = int(projVec.x);
    pge->DrawLine(sx, 0, sx, sh, lineColor);
  }

  for (int y = ceil(bottomTileCoord);
       y <= floor(topTileCoord);
       ++y) {
    Vec2f projVec = tileToScreenCoord(pge, Vec2f(0, y));
    int sy = int(projVec.y);
    pge->DrawLine(0, sy, sw, sy, lineColor);
  }

  std::vector<Node *> nodeVec = m_nodeMgr->getNodes();

  for (Node* n : nodeVec) {
    n->draw(pge, this);
  }

  drawCar(pge);

  for (Node* n : nodeVec) {
    n->drawLabel(pge, this);
  }

  m_popupLocationPanel.draw(4, 4, pge, m_menuSprite);  
}

void HighwayGameMode::drawCar(CarsWithGuns* game)
{
  Vec2f lowerLeftScreenCoord = tileToScreenCoord(game, m_carPos);
  Vec2f upperRightScreenCoord = tileToScreenCoord(game, m_carPos + Vec2f(1.0f, 1.0f));

  Vec2i midScreenCoord = Vec2i(int((lowerLeftScreenCoord.x + upperRightScreenCoord.x)/2.0f),
			       int((lowerLeftScreenCoord.y + upperRightScreenCoord.y)/2));
  
  olc::Pixel::Mode currentPixelMode = game->GetPixelMode();
  game->SetPixelMode(olc::Pixel::MASK);

  Vec2i tc = Vec2i(16 * (m_carHeading & 0x3),
		   16 * (m_carHeading / 4));

  olc::vi2d vScreenLocation = {
    midScreenCoord.x - 8,
    midScreenCoord.y - 8};
  olc::vi2d vTileLocation = {tc.x, tc.y};
  olc::vi2d vTileSize = {16, 16};
    
  game->DrawPartialSprite(vScreenLocation, m_carSprite,
			  vTileLocation, vTileSize);
  
  game->SetPixelMode(currentPixelMode);
}

Vec2f HighwayGameMode::screenToTileCoord(CarsWithGuns* pge, Vec2f screenCoord)
{
  // When sc is 0, 0, there is a scale x scale unit box centered
  // at the center of the screen.

  float screenX = screenCoord.x;
  float screenY = screenCoord.y;

  int sw = pge->ScreenWidth();
  int sh = pge->ScreenHeight();

  float screenCenterX = sw / 2.0f;
  float screenCenterY = sh / 2.0f;

  int cameraX = m_centerCoord.x;
  int cameraY = m_centerCoord.y;

  float worldOriginScreenX = screenCenterX -
    cameraX * m_tileScale -
    m_tileScale / 2.0f;

  float worldOriginScreenY = screenCenterY +
    cameraY * m_tileScale +
    m_tileScale / 2.0f;

  float tx = (screenX - worldOriginScreenX) / m_tileScale;
  float ty = (worldOriginScreenY - screenY) / m_tileScale;

  return Vec2f(tx, ty);
}

Vec2f HighwayGameMode::tileToScreenCoord(CarsWithGuns* pge, Vec2f tileCoord)
{
  // When screen center is 0, 0, there is a scale x scale unit box centered
  // at the center of the screen.
  
  float tileX = tileCoord.x;
  float tileY = tileCoord.y;
  
  int sw = pge->ScreenWidth();
  int sh = pge->ScreenHeight();

  float screenCenterX = sw / 2.0f;
  float screenCenterY = sh / 2.0f;

  int cameraX = m_centerCoord.x;
  int cameraY = m_centerCoord.y;

  float worldOriginScreenX = screenCenterX -
    cameraX * m_tileScale -
    m_tileScale / 2.0f;

  float worldOriginScreenY = screenCenterY +
    cameraY * m_tileScale +
    m_tileScale / 2.0f;

  float sx = worldOriginScreenX + tileX * m_tileScale;
  float sy = worldOriginScreenY - tileY * m_tileScale;

  return Vec2f(sx, sy);
}
