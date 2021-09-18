// mode_highway.h

// Reference ../PyCWG2021/fractal.py

#ifndef MODE_HIGHWAY_H
#define MODE_HIGHWAY_H

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

#include "coord.h"
#include "gameclock.h"
#include "nodemgr.h"
#include "popup_dialog.h"

class CarsWithGuns;
class GameClock;

class HighwayGameMode
{
 public:
  HighwayGameMode();

  void init(olc::Sprite *menuSprite);

  void destroy();

  bool update(CarsWithGuns* pge, float elapsedSeconds);

  void draw(CarsWithGuns* pge);

  Vec2f screenToTileCoord(CarsWithGuns* pge, Vec2f screenCoord);
  Vec2f tileToScreenCoord(CarsWithGuns* pge, Vec2f tileCoord);

  float getTileScale() {return m_tileScale;}

protected:
  void move(int x, int y);

  bool tryEnterCity(CarsWithGuns* pge);

  bool handleUserInput(CarsWithGuns* pge, bool& outSwitched);

  
private:
  Coord m_centerCoord;
  GameClock* m_gameClock;
  NodeMgr* m_nodeMgr;

  float m_tileScale;
  float m_viewRadius;

  PopupDialog m_popupLocationPanel;
  olc::Sprite* m_menuSprite;
};

#endif // MODE_HIGHWAY_H
