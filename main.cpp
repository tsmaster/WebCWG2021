#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#ifdef __EMSCRIPTEN__
#define USE_SOUND 0
#else
#define USE_SOUND 1
#define USE_OPENAL
#endif //__EMSCRIPTEN__

#if USE_SOUND
#define OLC_PGEX_SOUND
#include "olc_pgex_sound.h"
#endif //USE_SOUND


#include "entt.hpp"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <random>

#include "bdg_math.h"
#include "button.h"
#include "hsv.h"
#include "screen_bg.h"
#include "modes.h"
#include "mode_highway.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class CarsWithGuns : public olc::PixelGameEngine
{

public:
  CarsWithGuns()
  {
    sAppName = "carswithguns_2021";
    m_bAnySelected = false;
    m_elapsedTime = 0.0f;
  }

public:
  
  bool OnUserCreate() override
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

    setGameMode(GameMode::GM_BDG);

    return true;
  }

  bool OnUserDestroy() override
  {
#if USE_SOUND
    olc::SOUND::DestroyAudio();
#endif // USE_SOUND
    
    return true;
  }


  float fmap(float t, float in_min, float in_max, float out_min, float out_max)
  {
    float frac = (t - in_min) / (in_max - in_min);
    return frac * (out_max - out_min) + out_min;
  }

  void updateGame(float fElapsedSeconds)
  {
    float lastTime = m_elapsedTime;
    m_elapsedTime += fElapsedSeconds;

    //updateAnim(m_elapsedTime);    
  }

  void drawBackground()
  {
    auto view = m_registry.view<const ScreenBackgroundComponent>();

    auto pGame = this;
    
    for (auto [entity, bg]: view.each()) {
      bg.DrawBG(pGame);
    }
  }
  
  void drawGame()
  {    
    // draw the UI
    for (Button b : m_buttons) {
      b.draw(this);
    }

    //char scoreBuf[24];
    //sprintf(scoreBuf, "SCORE:%04d", m_score);

    //DrawString(550, 25, scoreBuf, olc::BLACK);
  }

  void drawCurrentMode() {
    auto [mode, bg] = m_registry.get<GameModeComponent,
				     ScreenBackgroundComponent>(m_currentMode);

    bg.DrawBG(this);

    //printf("drawing buttons\n");
    // draw the UI
    // TODO make UI data driven
    for (Button b : m_buttons) {
      b.draw(this);
    }

    if (mode.modeID == GM_HIGHWAY) {
      //printf("drawing highway(?!)\n");
      drawHighwayMode();
    }

    //printf("done drawing current mode\n");
  }

  void updateCurrentMode(float fElapsedSeconds)
  {
    auto &mode = m_registry.get<GameModeComponent>(m_currentMode);

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

    switch (mode.modeID) {
    case GM_HIGHWAY:
      updateHighwayMode(fElapsedSeconds);
      break;
    }
  }

  entt::entity findEntityForMode(GameMode queryMode)
  {
    auto view = m_registry.view<GameModeComponent>();

    for (auto [entity, mode]: view.each()) {
      if (mode.modeID == queryMode) {
	return entity;
      }
    }

    return entt::null;
  }

  void setGameMode(GameMode newMode)
  {
    if (m_currentMode != entt::null) {
      auto oldMode = m_registry.get<GameModeComponent>(m_currentMode);
    
      // clean up current game mode
      switch(oldMode.modeID) {
      case GameMode::GM_MAIN_MENU:
	destroyMainMenuMode();
	break;
      case GameMode::GM_HIGHWAY:
	destroyHighwayMode();
	break;
      }
    }

    m_currentMode = findEntityForMode(newMode);
    assert(m_currentMode != entt::null);

    // set up new game mode

    auto &mode = m_registry.get<GameModeComponent>(m_currentMode);

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
    default:
      // do nothing
      break;
    }
  }

  void initMainMenuMode()
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

  void destroyMainMenuMode()
  {
    printf("clearing main menu buttons\n");
    m_buttons.clear();
  }

  int rand_range(int min, int max)
  {
    int r = max - min + 1;
    int v = rand() % r;
    return min + v;
  }

  float rand_frange(float min, float max)
  {
    const int r = 10000;
    float v = (rand() % r) / ((float) r);
    return min + (max - min) * v;
  }

  void initHighwayMode()
  {
    m_highwayGameMode.init();
  }

  void destroyHighwayMode()
  {
    printf("clearing highway buttons\n");
    m_buttons.clear();

    m_highwayGameMode.destroy();
  }

  void drawHighwayMode()
  {
    m_highwayGameMode.draw();
  }

  void updateHighwayMode(float elapsedSeconds)
  {
    m_highwayGameMode.update(elapsedSeconds);
  }

  bool updateButtons() {
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

  bool OnUserUpdate(float fElapsedSeconds) override
  {
    //printf("---OnUserUpdate---\n");
    updateCurrentMode(fElapsedSeconds);
    //updateGame(fElapsedSeconds);
    
    // called once per frame
    drawCurrentMode();
    return m_bIsPlaying;
  }


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

  bool m_bIsPlaying = true;
};


int main()
{
  CarsWithGuns game;
  if (game.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 2, 2))
    game.Start();
  
  return 0;
}
