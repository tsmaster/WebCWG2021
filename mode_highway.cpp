// mode_highway.cpp

#include "mode_highway.h"

#include "constants.h"
#include "coord.h"
#include "gameclock.h"

// Reference ../PyCWG2021/fractal.py

// TODO finish porting HighwayGameMode from fractal.py

HighwayGameMode::HighwayGameMode()
{
  m_tileScale = 10.0f;
}

void HighwayGameMode::init()
{
  m_centerCoord = Coord(0, 0, 0);
  m_gameClock = new GameClock();
  m_nodeMgr = new NodeMgr(BASE_CACHE_SIZE, m_gameClock);
}

void HighwayGameMode::destroy()
{
  delete(m_gameClock);
  m_gameClock = NULL;

  delete(m_nodeMgr);
  m_nodeMgr = NULL;
}

bool HighwayGameMode::update(float elapsedSeconds)
{
  return true;
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

  // TODO draw the tiles from the nodeMgr
  /*
        nodeList = list(self.nodeMgr.getNodes())
        for n in nodeList:
            n.draw(self)

        for n in nodeList:
            n.drawLabels(self)
   */

  olc::Pixel crossHairsColor = olc::Pixel(125, 0, 0);
  pge->DrawLine(pcx - 5, pcy,
		pcx + 5, pcy, crossHairsColor);
  pge->DrawLine(pcx, pcy - 5,
		pcx, pcy + 5, crossHairsColor);
  
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
