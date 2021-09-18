// mode_city.cpp

#include "mode_city.h"

#include "carswithguns.h"
#include "city.h"
#include "constants.h"
#include "coord.h"
#include "gameclock.h"
#include "layers.h"
#include "modemgr.h"
#include "node.h"

CityGameMode::CityGameMode()
{
  m_tileScale = START_TILE_SCALE;
  m_viewRadius = START_VIEW_RADIUS;
}

void CityGameMode::init(olc::Sprite* menuSprite)
{
  m_centerCoord = Coord(0, 0, 0);
  m_gameClock = new GameClock();
  m_menuSprite = menuSprite;
}

void CityGameMode::destroy()
{
  delete(m_gameClock);
  m_gameClock = NULL;
}

bool CityGameMode::update(CarsWithGuns* game, float elapsedSeconds)
{
  bool bContinue = handleUserInput(game);
  
  return bContinue;
}

void CityGameMode::move(int dx, int dy)
{
  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;

  int nx = cx + dx;
  int ny = cy + dy;

  m_centerCoord = Coord(nx, ny, 0);

  /*
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
    }*/
}

bool CityGameMode::handleUserInput(CarsWithGuns* game)
{
  bool bTicked = false;

  bool bContinue = true;

  int cx = m_centerCoord.x;
  int cy = m_centerCoord.y;
    
  if ((game->GetKey(olc::Key::ESCAPE).bPressed)||
      (game->GetKey(olc::Key::Q).bPressed)) {
    ModeChangeRequest mcr = ModeChangeRequest::modeChangeRequestFactory(GameMode::GM_HIGHWAY);
    mcr.x = m_city.getCoord().x;
    mcr.y = m_city.getCoord().y;

    printf("in city, requesting exit to pos %d %d\n", mcr.x, mcr.y);
    
    game->requestGameMode(mcr);
  }

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

  if (bTicked) {
    m_gameClock->increment();
  }

  return bContinue;
}

void CityGameMode::draw(CarsWithGuns* game)
{
  game->Clear(olc::DARK_GRAY);

  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

  int pcx = sw / 2;
  int pcy = sh / 2;

  olc::Pixel lineColor = olc::Pixel(25, 150, 25);

  Vec2f topLeftTileCoord = screenToTileCoord(game, Vec2f(0,0));
  Vec2f bottomRightTileCoord = screenToTileCoord(game, Vec2f(sw, sh));

  float leftTileCoord = topLeftTileCoord.x;
  float topTileCoord = topLeftTileCoord.y;

  float rightTileCoord = bottomRightTileCoord.x;
  float bottomTileCoord = bottomRightTileCoord.y;

  for (int x = ceil(leftTileCoord);
       x <= floor(rightTileCoord);
       ++x) {
    Vec2f projVec = tileToScreenCoord(game, Vec2f(x, 0));
    int sx = int(projVec.x);
    game->DrawLine(sx, 0, sx, sh, lineColor);
  }

  for (int y = ceil(bottomTileCoord);
       y <= floor(topTileCoord);
       ++y) {
    Vec2f projVec = tileToScreenCoord(game, Vec2f(0, y));
    int sy = int(projVec.y);
    game->DrawLine(0, sy, sw, sy, lineColor);
  }

  olc::Pixel crossHairsColor = olc::Pixel(125, 0, 0);
  game->DrawLine(pcx - 5, pcy,
		pcx + 5, pcy, crossHairsColor);
  game->DrawLine(pcx, pcy - 5,
		pcx, pcy + 5, crossHairsColor);


  m_popupLocationPanel.draw(4, 4, game, m_menuSprite);  
}


Vec2f CityGameMode::screenToTileCoord(CarsWithGuns* game, Vec2f screenCoord)
{
  // When sc is 0, 0, there is a scale x scale unit box centered
  // at the center of the screen.

  float screenX = screenCoord.x;
  float screenY = screenCoord.y;

  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

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

Vec2f CityGameMode::tileToScreenCoord(CarsWithGuns* game, Vec2f tileCoord)
{
  // When screen center is 0, 0, there is a scale x scale unit box centered
  // at the center of the screen.
  
  float tileX = tileCoord.x;
  float tileY = tileCoord.y;
  
  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

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

void CityGameMode::setCity(City c)
{
  m_city = c;
  rebuildDisplay();
}

void CityGameMode::rebuildDisplay()
{
  std::string name = m_city.getName();
  int population = m_city.getPopulation();
  printf("city name: %s pop %d\n", name.c_str(), population);

  // todo better formatting
  std::string msg = name + std::string("\npop: ") +std::to_string(population);
  std::vector<ButtonDesc> buttons;
  m_popupLocationPanel.build(msg, buttons);
}
