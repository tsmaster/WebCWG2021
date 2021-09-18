#ifndef main_h
#define main_h

#include "entt.hpp"

#include "modes.h"
#include "mode_city.h"
#include "mode_highway.h"

class Button;


class CarsWithGuns : public olc::PixelGameEngine
{
 public:
  CarsWithGuns();

  bool OnUserCreate() override;

  bool OnUserDestroy() override;

  bool OnUserUpdate(float seconds) override;

  void setGameMode(GameMode newMode);
  
 protected:
  void updateGame(float seconds);

  void drawBackground();

  void drawGame();

  void drawCurrentMode();
  void updateCurrentMode(float seconds);

  entt::entity findEntityForMode(GameMode queryMode);

  void initMainMenuMode();
  void destroyMainMenuMode();

  void initHighwayMode();
  void destroyHighwayMode();
  void drawHighwayMode();
  bool updateHighwayMode(float seconds);

  void initCityMode();
  void destroyCityMode();
  void drawCityMode();
  bool updateCityMode(float seconds);

  void initInstructionsMode();
  void updateInstructionsMode(float seconds);

  bool updateButtons();


private:
  std::vector<Button> m_buttons;
  entt::entity m_selectedEntity;
  bool m_bAnySelected;

  entt::registry m_registry;

  float m_elapsedTime;

  bool m_showDecal = true;

  //int m_sndPickupID = -1;
  //int m_sndDropID = -1;

  entt::entity m_currentMode = entt::null;

  HighwayGameMode m_highwayGameMode;

  CityGameMode m_cityGameMode;

  bool m_bIsPlaying = true;

  olc::Sprite* m_menuSprite;
  olc::popup::Menu m_menu;
  olc::popup::Manager m_menuMgr;  
};

#endif // main_h
