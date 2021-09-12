// mode_highway.h

// Reference ../PyCWG2021/fractal.py

#ifndef MODE_HIGHWAY_H
#define MODE_HIGHWAY_H

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

#include "coord.h"
#include "gameclock.h"
#include "nodemgr.h"

class GameClock;

class HighwayGameMode
{
 public:
  HighwayGameMode();

  void init();

  void destroy();

  bool update(olc::PixelGameEngine* pge, float elapsedSeconds);

  void draw(olc::PixelGameEngine* pge);

  Vec2f screenToTileCoord(olc::PixelGameEngine* pge, Vec2f screenCoord);
  Vec2f tileToScreenCoord(olc::PixelGameEngine* pge, Vec2f tileCoord);

  bool handleUserInput(olc::PixelGameEngine* pge);

  float getTileScale() {return m_tileScale;}

private:
  Coord m_centerCoord;
  GameClock* m_gameClock;
  NodeMgr* m_nodeMgr;

  float m_tileScale;
  float m_viewRadius;
};

#endif // MODE_HIGHWAY_H
