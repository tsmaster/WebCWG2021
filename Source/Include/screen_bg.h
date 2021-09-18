#ifndef SCREEN_BG_H
#define SCREEN_BG_H

#include <string>

#include "olcPixelGameEngine.h"
#include "entt.hpp"

class ScreenBackgroundComponent
{
 public:
  ScreenBackgroundComponent(std::string filename);
  ScreenBackgroundComponent(olc::Pixel bgColor);

  bool DrawBG(olc::PixelGameEngine* game) const;


  olc::Sprite* m_screenSprite;
  olc::Decal* m_screenDecal;

  olc::Pixel m_solidColor;

  bool m_bSolidColor;

  bool m_bIsLoaded;

  float x;
  float y;

  bool m_bIsActive;

  // todo, move this to a "slideshow" component?
  entt::entity m_eNextScreen;
};


#endif // SCREEN_BG_H
