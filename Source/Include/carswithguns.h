#ifndef carswithguns_h
#define carswithguns_h


#include "entt.hpp"

#include "button.h"
#include "mission.h"
#include "modes.h"
#include "mode_arena.h"
#include "mode_building.h"
#include "mode_city.h"
#include "mode_highway.h"
#include "mode_track.h"
#include "modemgr.h"

class CarsWithGuns : public olc::PixelGameEngine
{
 public:
  CarsWithGuns();

  bool OnUserCreate() override;

  bool OnUserDestroy() override;

  bool OnUserUpdate(float seconds) override;

  void requestGameMode(ModeChangeRequest mcr);

  void generateMissionSequence(Coord startingCoord, int length,
			       float beginningRadius, float endingRadius);

  void progressMissionSequence();

  NodeMgr* getNodeMgr() { return &m_nodeMgr; }
  
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

  void initBuildingMode();
  void destroyBuildingMode();
  void drawBuildingMode();
  bool updateBuildingMode(float seconds);

  void initArenaMode();
  void destroyArenaMode();
  void drawArenaMode();
  bool updateArenaMode(float seconds);
  
  void initTrackMode();
  void destroyTrackMode();
  void drawTrackMode();
  bool updateTrackMode(float seconds);
  
  
  void initInstructionsMode();
  void updateInstructionsMode(float seconds);

  bool updateButtons();

  void setGameMode(GameMode newMode);
  void applyModeArguments(ModeChangeRequest mcr);

private:
  std::vector<Button> m_buttons;
  entt::entity m_selectedEntity;
  bool m_bAnySelected;

  entt::registry m_registry;

  float m_elapsedTime;

  bool m_showDecal = true;

  ModeMgr m_modeMgr;
  HighwayGameMode m_highwayGameMode;
  CityGameMode m_cityGameMode;
  BuildingGameMode m_buildingGameMode;
  ArenaGameMode m_arenaGameMode;
  TrackGameMode m_trackGameMode;

  bool m_bIsPlaying = true;

  olc::Sprite* m_menuSprite;
  olc::Sprite* m_citySprite;
  olc::Sprite* m_carSprite;
  olc::Sprite* m_missionSprite;
  olc::Sprite* m_faceSprite;
  olc::Sprite* m_hairSprite;
  olc::Sprite* m_pantsSprite;
  olc::Sprite* m_shirtsSprite;
  olc::Sprite* m_shoesSprite;
  olc::Sprite* m_skinSprite;

  olc::Sprite* m_car_00_sprite;
  olc::Sprite* m_car_01_sprite;
  olc::Sprite* m_car_02_sprite;
  olc::Sprite* m_car_03_sprite;
  olc::Sprite* m_car_04_sprite;
  olc::Sprite* m_car_05_sprite;
  olc::Sprite* m_car_06_sprite;
  olc::Sprite* m_car_07_sprite;

  olc::Sprite* m_arena_floor_sprite;
  
  olc::popup::Menu m_menu;
  olc::popup::Manager m_menuMgr;

  std::vector<ModeChangeRequest> m_modeChangeRequests;

  MissionMgr m_missionMgr;

  NodeMgr m_nodeMgr;
  GameClock m_gameClock;
};


#endif //carswithguns_h
