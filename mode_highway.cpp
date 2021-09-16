// mode_highway.cpp

#include "mode_highway.h"

#include "city.h"
#include "constants.h"
#include "coord.h"
#include "gameclock.h"
#include "layers.h"
#include "node.h"

HighwayGameMode::HighwayGameMode()
{
  m_tileScale = START_TILE_SCALE;
  m_viewRadius = START_VIEW_RADIUS;
}

void HighwayGameMode::init(olc::Sprite* menuSprite)
{
  m_centerCoord = Coord(0, 0, 0);
  m_gameClock = new GameClock();
  m_nodeMgr = new NodeMgr(BASE_CACHE_SIZE, m_gameClock);
  m_menuSprite = menuSprite;
}

void HighwayGameMode::destroy()
{
  delete(m_gameClock);
  m_gameClock = NULL;

  delete(m_nodeMgr);
  m_nodeMgr = NULL;
}

bool HighwayGameMode::update(olc::PixelGameEngine* pge, float elapsedSeconds)
{
  bool bContinue = handleUserInput(pge);

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

  m_centerCoord = Coord(nx, ny, 0);

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

bool HighwayGameMode::handleUserInput(olc::PixelGameEngine* pge)
{
  bool bTicked = false;

  bool bContinue = true;

  if (pge->GetKey(olc::Key::ESCAPE).bPressed) {
    bContinue = false;
  }

  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;
  
  if (pge->GetKey(olc::Key::LEFT).bPressed) {
    move(-1, 0);
    bTicked = true;
  }

  if (pge->GetKey(olc::Key::RIGHT).bPressed) {
    move(1, 0);
    bTicked = true;
  }

  if (pge->GetKey(olc::Key::DOWN).bPressed) {
    move(0, -1);
    bTicked = true;
  }

  if (pge->GetKey(olc::Key::UP).bPressed) {
    move(0, 1);
    bTicked = true;
  }

  if (pge->GetKey(olc::Key::PGUP).bPressed) {
    m_tileScale = std::min((m_tileScale * 3) / 2, 64.0f);
  }

  if (pge->GetKey(olc::Key::PGDN).bPressed) {
    m_tileScale = std::max((m_tileScale * 2) / 3, 2.0f);
  }
  
  if (pge->GetKey(olc::Key::NP_ADD).bPressed) {
    m_viewRadius = std::min(m_viewRadius + 0.25f, 32.0f);
  }

  if (pge->GetKey(olc::Key::NP_SUB).bPressed) {
    m_viewRadius = std::min(m_viewRadius - 0.25f, 1.0f);
  }
  
  if (pge->GetKey(olc::Key::K1).bPressed) {
    printf("center: %s\n", m_centerCoord.toString().c_str());
  }

  if (bTicked) {
    m_gameClock->increment();
  }

  return bContinue;
}

void HighwayGameMode::draw(olc::PixelGameEngine* pge)
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
    //printf("Drawing node at coord %s\n", n->getCoord()->toString().c_str());
    n->draw(pge, this);
  }

  for (Node* n : nodeVec) {
    n->drawLabel(pge, this);
  }

  olc::Pixel crossHairsColor = olc::Pixel(125, 0, 0);
  pge->DrawLine(pcx - 5, pcy,
		pcx + 5, pcy, crossHairsColor);
  pge->DrawLine(pcx, pcy - 5,
		pcx, pcy + 5, crossHairsColor);


  m_popupLocationPanel.draw(4, 4, pge, m_menuSprite);  
}


Vec2f HighwayGameMode::screenToTileCoord(olc::PixelGameEngine* pge, Vec2f screenCoord)
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

Vec2f HighwayGameMode::tileToScreenCoord(olc::PixelGameEngine* pge, Vec2f tileCoord)
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
