#include "olcPixelGameEngine.h"
#include "olcPopupMenu.h"

#ifdef __EMSCRIPTEN__
#define USE_SOUND 0
#else
#define USE_SOUND 1
#define USE_OPENAL
#endif //__EMSCRIPTEN__

#include "olc_pgex_sound.h"

#include "carswithguns.h"

#include "entt.hpp"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <random>

#include "bdg_math.h"
#include "button.h"
#include "city.h"
#include "hsv.h"
#include "screen_bg.h"
#include "modes.h"
#include "mode_city.h"
#include "mode_highway.h"
#include "modemgr.h"

CarsWithGuns::CarsWithGuns()
{
  sAppName = "carswithguns_2021";
  m_bAnySelected = false;
  m_elapsedTime = 0.0f;
}

bool CarsWithGuns::OnUserCreate()
{
  srand(time(NULL));


#if USE_SOUND
  olc::SOUND::InitialiseAudio();

    //m_sndPickupID = olc::SOUND::LoadAudioSample(std::string("Assets/Sounds/pickup.wav"));
    //m_sndDropID = olc::SOUND::LoadAudioSample(std::string("Assets/Sounds/drop.wav"));

    //printf("pickup id: %d drop id %d\n", m_sndPickupID, m_sndDropID);
#endif // USE_SOUND

  entt::entity eBdgMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eBdgMode,
						  std::string("Assets/Screens/bigdicegames.png"));
  m_registry.emplace<GameModeComponent>(eBdgMode,
					GameMode::GM_BDG,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					4.0f,
					4.0f,
					GameMode::GM_TITLE,
					GameMode::GM_MAIN_MENU);

  entt::entity eTitleMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eTitleMode,
						std::string("Assets/Screens/title.png"));

  m_registry.emplace<GameModeComponent>(eTitleMode,
					GameMode::GM_TITLE,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					4.0f,
					4.0f,
					GameMode::GM_MAIN_MENU,
					GameMode::GM_MAIN_MENU);

  entt::entity eMainMenuMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eMainMenuMode,
						std::string("Assets/Screens/mainmenu.png"));

  m_registry.emplace<GameModeComponent>(eMainMenuMode,
					GameMode::GM_MAIN_MENU,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					-1.0f,
					0.0f,
					GameMode::GM_NONE,
					GameMode::GM_NONE);

  entt::entity eInstMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eInstMode,
						std::string("Assets/Screens/instructions.png"));

  m_registry.emplace<GameModeComponent>(eInstMode,
					GameMode::GM_INSTRUCTIONS,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					8.0f,
					8.0f,
					GameMode::GM_MAIN_MENU,
					GameMode::GM_MAIN_MENU);

  entt::entity eAboutMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eAboutMode,
						std::string("Assets/Screens/about.png"));

  m_registry.emplace<GameModeComponent>(eAboutMode,
					GameMode::GM_ABOUT,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					4.0f,
					4.0f,
					GameMode::GM_MAIN_MENU,
					GameMode::GM_MAIN_MENU);

  entt::entity eGameMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eGameMode,
						olc::Pixel(0, 128, 0));

  m_registry.emplace<GameModeComponent>(eGameMode,
					GameMode::GM_HIGHWAY,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					-1.0f,
					-1.0f,
					GameMode::GM_NONE,
					GameMode::GM_MAIN_MENU);

  entt::entity eCityMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eCityMode,
						olc::Pixel(64, 80, 64));

  m_registry.emplace<GameModeComponent>(eCityMode,
					GameMode::GM_CITY,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					-1.0f,
					-1.0f,
					GameMode::GM_NONE,
					GameMode::GM_NONE);

  entt::entity eSettingsMode = m_registry.create();
  m_registry.emplace<ScreenBackgroundComponent>(eSettingsMode,
						olc::Pixel(128, 255, 0));

  m_registry.emplace<GameModeComponent>(eSettingsMode,
					GameMode::GM_SETTINGS,
					std::string(""),
					olc::nDefaultPixel,
					0.0f,
					-1.0f,
					-1.0f,
					GameMode::GM_MAIN_MENU,
					GameMode::GM_MAIN_MENU);


	
  // Construction (root menu is a 1x5 table)
  m_menu.SetTable(1, 5);

  // Add first item  to root menu (A 1x5 submenu)
  m_menu["Menu1"].SetTable(1, 5);

  // Add items to first item
  m_menu["Menu1"]["Item1"];
  m_menu["Menu1"]["Item2"];

  // Add a 4x3 submenu
  m_menu["Menu1"]["Item3"].SetTable(4, 3);
  m_menu["Menu1"]["Item3"]["Option1"];
  m_menu["Menu1"]["Item3"]["Option2"];

  // Set properties of specific item
  m_menu["Menu1"]["Item3"]["Option3"].Enable(false);
  m_menu["Menu1"]["Item3"]["Option4"];
  m_menu["Menu1"]["Item3"]["Option5"];
  m_menu["Menu1"]["Item4"];

  // Add second item to root menu
  m_menu["Menu2"].SetTable(3, 3);
  m_menu["Menu2"]["Item1"];
  m_menu["Menu2"]["Item2"].SetID(1001).Enable(true);
  m_menu["Menu2"]["Item3"];
  
  m_menu["Pew Pew"].SetTable(1,2);
  m_menu["Pew Pew"]["With Guns"].SetID(1002).Enable(true);
  m_menu["Pew Pew"]["Without Guns"].SetID(1003).Enable(true);
  
  // Construct the menu structure
  m_menu.Build();

  m_menuSprite = new olc::Sprite("Assets/Sprites/retroMenu.png");

  m_citySprite = new olc::Sprite("Assets/Sprites/kenney_rpgurbanpack/Tilemap/tilemap_32.png");

  m_carSprite = new olc::Sprite("Assets/Sprites/WhiteCar/white-car-sprite.png");

  setGameMode(GameMode::GM_BDG);

  return true;
}

bool CarsWithGuns::OnUserDestroy()
{
#if USE_SOUND
  olc::SOUND::DestroyAudio();
#endif // USE_SOUND
    
  return true;
}


void CarsWithGuns::updateGame(float fElapsedSeconds)
{
  float lastTime = m_elapsedTime;
  m_elapsedTime += fElapsedSeconds;

  //updateAnim(m_elapsedTime);    
}

void CarsWithGuns::drawBackground()
{
  auto view = m_registry.view<const ScreenBackgroundComponent>();

  auto pGame = this;
    
  for (auto [entity, bg]: view.each()) {
    bg.DrawBG(pGame);
  }
}
  
void CarsWithGuns::drawGame()
{    
  // draw the UI
  for (Button b : m_buttons) {
    b.draw(this);
  }
}

void CarsWithGuns::drawCurrentMode() {
  auto [mode, bg] = m_registry.get<GameModeComponent,
				   ScreenBackgroundComponent>(m_modeMgr.getCurrentMode());

  bg.DrawBG(this);

  //printf("drawing buttons\n");
  // draw the UI
  // TODO make UI data driven
  for (Button b : m_buttons) {
    b.draw(this);
  }

  if (mode.modeID == GM_HIGHWAY) {
    drawHighwayMode();
  } else if (mode.modeID == GM_CITY) {
    drawCityMode();
  } else if (mode.modeID == GM_INSTRUCTIONS) {
    m_menuMgr.Draw(m_menuSprite, {30, 30});
  }
}

void CarsWithGuns::updateCurrentMode(float fElapsedSeconds)
{
  auto &mode = m_registry.get<GameModeComponent>(m_modeMgr.getCurrentMode());

  mode.timeInMode += fElapsedSeconds;

  if (mode.timeoutSeconds > 0) {
    float newSeconds = mode.secondsRemaining - fElapsedSeconds;

    if (newSeconds < 0) {
      setGameMode(mode.modeNext);
      return;
    }

    mode.secondsRemaining = newSeconds;
  }

  if (updateButtons()) {
    return;
  }

  if ((mode.escMode != GameMode::GM_NONE) &&
      (GetKey(olc::Key::ESCAPE).bPressed)) {
    setGameMode(mode.escMode);
    return;
  }

  if (mode.modeNext != GameMode::GM_NONE) {
    if ((GetKey(olc::Key::SPACE).bPressed) ||
	(GetMouse(0).bPressed)) {
      setGameMode(mode.modeNext);
      return;
    }
  }

  //printf("current mode: %d\n", mode.modeID);

  switch (mode.modeID) {
  case GM_HIGHWAY:
    {
      bool cont = updateHighwayMode(fElapsedSeconds);
      if (!cont) {
	setGameMode(mode.escMode);
      }
    }
    break;
  case GM_CITY:
    {
      bool cont = updateCityMode(fElapsedSeconds);
      if (!cont) {
	setGameMode(mode.escMode);
      }
    }
    break;
  case GM_INSTRUCTIONS:
    updateInstructionsMode(fElapsedSeconds);
    break;
  }
}

entt::entity CarsWithGuns::findEntityForMode(GameMode queryMode)
{
  auto view = m_registry.view<GameModeComponent>();
  
  for (auto [entity, mode]: view.each()) {
    if (mode.modeID == queryMode) {
      return entity;
    }
  }
  
  return entt::null;
}

void CarsWithGuns::setGameMode(GameMode newMode)
{
  if (m_modeMgr.getCurrentMode() != entt::null) {
    auto oldMode = m_registry.get<GameModeComponent>(m_modeMgr.getCurrentMode());
    
    // clean up current game mode
    switch(oldMode.modeID) {
    case GameMode::GM_MAIN_MENU:
      destroyMainMenuMode();
      break;
    case GameMode::GM_HIGHWAY:
      destroyHighwayMode();
      break;
    case GameMode::GM_CITY:
      destroyCityMode();
      break;
    }
  }

  auto newModeEntity = findEntityForMode(newMode);
  assert(newModeEntity != entt::null);  
  m_modeMgr.setCurrentMode(newModeEntity);

  // set up new game mode

  auto &mode = m_registry.get<GameModeComponent>(newModeEntity);

  mode.timeInMode = 0.0f;
    
  if (mode.timeoutSeconds > 0) {
    mode.secondsRemaining = mode.timeoutSeconds;
  }
  
  switch(newMode) {
  case GameMode::GM_MAIN_MENU:
    initMainMenuMode();
    break;
  case GameMode::GM_HIGHWAY:
    initHighwayMode();
    break;
  case GameMode::GM_CITY:
    printf("initing city\n");
    initCityMode();
    break;
  case GameMode::GM_INSTRUCTIONS:
    initInstructionsMode();
    break;
  default:
    // do nothing
    break;
  }
}

void CarsWithGuns::initMainMenuMode()
{
  // TODO put buttons in the registry?

  int button_width = 100;
  int button_height = 20;
  int button_left = 500;
  int button_top = 40;

  int button_advance = 25;
    
  Button buttonContinue(button_left, button_top, button_width, button_height, "continue");
  button_top += button_advance;
  Button buttonLoad(button_left, button_top, button_width, button_height, "load");
  button_top += button_advance;    
  Button buttonNew(button_left, button_top, button_width, button_height, "new");
  button_top += button_advance;    
  Button buttonInstructions(button_left, button_top, button_width, button_height, "instructions");
  button_top += button_advance;    
  Button buttonSettings(button_left, button_top, button_width, button_height, "settings");
  button_top += button_advance;    
  Button buttonAbout(button_left, button_top, button_width, button_height, "about");
  button_top += button_advance;    
  Button buttonQuit(button_left, button_top, button_width, button_height, "quit");

  buttonContinue.setCallbackFunction([this] {setGameMode(GM_HIGHWAY);});
  buttonLoad.setCallbackFunction([this] {printf("TODO: loading\n");});
  buttonNew.setCallbackFunction([this] {setGameMode(GM_HIGHWAY);});
  buttonInstructions.setCallbackFunction([this] {setGameMode(GM_INSTRUCTIONS);});
  buttonSettings.setCallbackFunction([this] {setGameMode(GM_SETTINGS);});
  buttonAbout.setCallbackFunction([this] {setGameMode(GM_ABOUT);});
  buttonQuit.setCallbackFunction([this] {this->m_bIsPlaying = false; printf("done\n");});

  printf("adding main menu buttons\n");
    
  m_buttons.clear();

  m_buttons.push_back(buttonContinue);
  m_buttons.push_back(buttonLoad);
  m_buttons.push_back(buttonNew);
  m_buttons.push_back(buttonInstructions);
  m_buttons.push_back(buttonSettings);
  m_buttons.push_back(buttonAbout);
  m_buttons.push_back(buttonQuit);    
}

void CarsWithGuns::destroyMainMenuMode()
{
  printf("clearing main menu buttons\n");
  m_buttons.clear();
}

void CarsWithGuns::initHighwayMode()
{
  m_highwayGameMode.init(m_menuSprite, m_carSprite);
}

void CarsWithGuns::destroyHighwayMode()
{
  printf("clearing highway buttons\n");
  m_buttons.clear();
  
  m_highwayGameMode.destroy();
}

void CarsWithGuns::drawHighwayMode()
{
  m_highwayGameMode.draw(this);
}

bool CarsWithGuns::updateHighwayMode(float elapsedSeconds)
{
  return m_highwayGameMode.update(this, elapsedSeconds);
}

void CarsWithGuns::initCityMode()
{
  m_cityGameMode.init(m_menuSprite, m_citySprite, m_carSprite);
}

void CarsWithGuns::destroyCityMode()
{
  printf("clearing city buttons\n");
  m_buttons.clear();
  
  m_cityGameMode.destroy();
}

void CarsWithGuns::drawCityMode()
{
  m_cityGameMode.draw(this);
}

bool CarsWithGuns::updateCityMode(float elapsedSeconds)
{
  return m_cityGameMode.update(this, elapsedSeconds);
}

void CarsWithGuns::initInstructionsMode()
{
  m_menuMgr.Open(&m_menu);
}

void CarsWithGuns::updateInstructionsMode(float elapsedSeconds)
{
  if (GetKey(olc::Key::UP).bPressed)    m_menuMgr.OnUp();
  if (GetKey(olc::Key::DOWN).bPressed)  m_menuMgr.OnDown();
  if (GetKey(olc::Key::LEFT).bPressed)  m_menuMgr.OnLeft();
  if (GetKey(olc::Key::RIGHT).bPressed) m_menuMgr.OnRight();
  if (GetKey(olc::Key::Z).bPressed)     m_menuMgr.OnBack();
  if (GetKey(olc::Key::X).bPressed)     m_menuMgr.OnConfirm();
}

bool CarsWithGuns::updateButtons() {
  // process mouse clicks
  if (GetMouse(0).bPressed) {
    int mx = GetMouseX();
    int my = GetMouseY();
    
    for (Button b : m_buttons) {
      if ((mx >= b.x) &&
	  (my >= b.y) &&
	  (mx <= b.x + b.w) &&
	  (my <= b.y + b.h)) {
	if (b.m_callback != NULL) {
	  b.m_callback();
	  return true;
	}
	}
    }
  }
  return false;
}

void CarsWithGuns::applyModeArguments(ModeChangeRequest mcr)
{
  switch (mcr.newGameMode) {
  case GameMode::GM_HIGHWAY:
    {
      printf("setting pos %d %d\n", mcr.x, mcr.y);
      m_highwayGameMode.setPos(mcr.x, mcr.y);
    }
    break;
  case GameMode::GM_CITY:
    {
      City c(mcr.x, mcr.y);
      c.setName(mcr.cityName);
      c.setPopulation(mcr.population);
      c.setExits(mcr.exitEast,
		 mcr.exitNorth,
		 mcr.exitWest,
		 mcr.exitSouth);
      
      m_cityGameMode.setCity(c);
    }
  }
}

bool CarsWithGuns::OnUserUpdate(float fElapsedSeconds)
{
  for (auto rq : m_modeChangeRequests) {
    setGameMode(rq.newGameMode);
    applyModeArguments(rq);
  }
  m_modeChangeRequests.clear();
  
  //printf("---OnUserUpdate---\n");
  updateCurrentMode(fElapsedSeconds);
  //updateGame(fElapsedSeconds);
    
  // called once per frame
  drawCurrentMode();
  return m_bIsPlaying;
}

void CarsWithGuns::requestGameMode(ModeChangeRequest mcr)
{
  m_modeChangeRequests.push_back(mcr);
}
