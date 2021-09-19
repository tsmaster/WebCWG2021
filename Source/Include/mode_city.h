// mode_city.h

#ifndef MODE_CITY_H
#define MODE_CITY_H

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

#include "city.h"
#include "citymap.h"
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
};

#endif // MODE_CITY_H
