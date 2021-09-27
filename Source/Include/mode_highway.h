// mode_highway.h

// Reference ../PyCWG2021/fractal.py

#ifndef MODE_HIGHWAY_H
#define MODE_HIGHWAY_H

#include "olcPixelGameEngine.h"

#include "astar.h"
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

  void init(olc::Sprite* menuSprite, olc::Sprite* carSprite,
	    GameClock* gameClock, NodeMgr* nodeMgr);

  bool update(CarsWithGuns* pge, float elapsedSeconds);

  void draw(CarsWithGuns* pge);

  Vec2f screenToTileCoord(CarsWithGuns* pge, Vec2f screenCoord);
  Vec2f tileToScreenCoord(CarsWithGuns* pge, Vec2f tileCoord);

  float getTileScale() {return m_tileScale;}

  void setPos(int x, int y) { m_centerCoord = Coord(x, y, 0);
    m_carPos = Vec2f(x, y);
  }

protected:
  void move(int x, int y);

  bool tryEnterCity(CarsWithGuns* pge);

  bool handleUserInput(CarsWithGuns* pge, bool& outSwitched);

  void drawCar(CarsWithGuns* game);

  std::vector<bdg_astar::Link> expandPosn(Vec2i);
  
private:
  Coord m_centerCoord;
  
  float m_tileScale;
  float m_viewRadius;

  PopupDialog m_popupLocationPanel;
  olc::Sprite* m_menuSprite;
  olc::Sprite* m_carSprite;

  Vec2f m_carPos = Vec2f(0.0f, 0.0f);
  int m_carHeading; //0-7, 0:E

  Vec2i m_destTile = Vec2i(0, 0);
  bdg_astar::AStar m_astar;
  bool m_isFindingPath = false;
  bool m_isFollowingPath = false;

  std::vector<Vec2i> m_path;
  float m_timeRemainingBeforeMove;
  float m_timeToMove = 0.2f;

  GameClock* m_gameClock;
  NodeMgr* m_nodeMgr;
};

#endif // MODE_HIGHWAY_H
