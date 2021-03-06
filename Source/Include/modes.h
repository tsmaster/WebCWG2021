#ifndef MODES_H
#define MODES_H

#include "olcPixelGameEngine.h"

enum GameMode {
  GM_NONE,
  
  GM_BDG,
  GM_TITLE,
  GM_MAIN_MENU,
  GM_INSTRUCTIONS,
  GM_ABOUT,
  GM_HIGHWAY,
  GM_CITY,
  GM_ESC_MENU,
  GM_SETTINGS,
  GM_BUILDING,
  GM_ARENA,
  GM_TRACK,

  GM_LAST,
};


struct GameModeComponent {
public:
  GameMode modeID;
  std::string text;
  olc::Pixel textColor;

  float timeInMode;
  
  float timeoutSeconds;

  float secondsRemaining;

  GameMode modeNext;

  GameMode escMode;
};



#endif //MODES_H
