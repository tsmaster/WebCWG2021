// mode_city.h

#ifndef MODE_CITY_H
#define MODE_CITY_H

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

#include "city.h"
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

  void init(olc::Sprite *menuSprite);

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
private:
  City m_city = City(0, 0);
  Coord m_centerCoord;
  GameClock* m_gameClock;

  float m_tileScale;
  float m_viewRadius;

  PopupDialog m_popupLocationPanel;
  olc::Sprite* m_menuSprite;
};

#endif // MODE_CITY_H
