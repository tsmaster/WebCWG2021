// mode_city.h

#ifndef MODE_CITY_H
#define MODE_CITY_H

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

#include "astar.h"
#include "city.h"
#include "citymap.h"
#include "constants.h"
#include "coord.h"
#include "gameclock.h"
#include "nodemgr.h"
#include "popup_dialog.h"

class CarsWithGuns;
class GameClock;

class CityGameMode
{
 public:
  CityGameMode();

  void init(olc::Sprite* menuSprite, olc::Sprite* citySprite, olc::Sprite* carSprite);

  void destroy();

  bool update(CarsWithGuns* game, float elapsedSeconds);

  void draw(CarsWithGuns* game);

  Vec2f screenToTileCoord(CarsWithGuns* game, Vec2f screenCoord);
  Vec2f tileToScreenCoord(CarsWithGuns* game, Vec2f tileCoord);

  bool handleUserInput(CarsWithGuns* game);

  float getTileScale() {return m_tileScale;}

  void setCity(City c);

protected:
  void move(int x, int y);

  void rebuildDisplay();

  void drawCar(CarsWithGuns* game);

  void drawCursor(CarsWithGuns* game, int cursorStyle);

  void drawPathPos(CarsWithGuns* game, Vec2i pathPos);

  std::vector<bdg_astar::Link> expandPosn(Vec2i posn);

  int findBuilding(int x, int y);

  std::set<Vec2i> getDestinationsForBuilding(int buildingIndex);
private:
  City m_city = City(0, 0);
  Coord m_centerCoord;
  GameClock* m_gameClock;

  float m_tileScale;
  float m_viewRadius;

  CityMap m_cityMap;

  PopupDialog m_popupLocationPanel;
  
  olc::Sprite* m_menuSprite;
  olc::Sprite* m_citySprite;
  olc::Sprite* m_carSprite;

  int m_carHeading; // 0 = east, 2 = north, 4 = west, 6 = south
  Vec2i m_carPos;

  bdg_astar::AStar m_astar;
  bool m_isFindingPath;
  bool m_isFollowingPath;
  std::vector<Vec2i> m_path;

  Vec2i m_destTile;

  float m_timeToMove = MOVEMENT_SPEED;
  float m_timeRemainingBeforeMove;
};

#endif // MODE_CITY_H
