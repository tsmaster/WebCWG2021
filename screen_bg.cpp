#include "screen_bg.h"

ScreenBackgroundComponent::ScreenBackgroundComponent(std::string filename) {
  x = 0;
  y = 0;

  m_bIsLoaded = false;

  olc::Sprite* spr = new olc::Sprite();
  if (filename.length() == 0 ) {
    m_bIsLoaded = false;
    m_screenDecal = nullptr;
  } else {
    olc::rcode loadRet = spr->LoadFromFile(filename);
    if (loadRet != olc::rcode::OK) {
      m_bIsLoaded = false;
      m_screenDecal = NULL;
      printf("failure to load screen %s\n", filename.c_str());

      m_bSolidColor = true;
      m_solidColor = olc::Pixel(255, 0 , 255);
    } else {
      m_bIsLoaded = true;
      m_screenDecal = new olc::Decal(spr);
      m_screenSprite = spr;
      m_bSolidColor = false;
    }
  }
}

ScreenBackgroundComponent::ScreenBackgroundComponent(olc::Pixel bgColor) {
  x = 0;
  y = 0;

  m_bIsLoaded = false;
  m_screenSprite = nullptr;
  m_screenDecal = nullptr;

  m_bSolidColor = true;
  m_solidColor = bgColor;
}



bool ScreenBackgroundComponent::DrawBG(olc::PixelGameEngine* game) const {
  //if (!m_bIsActive) {
  //  return false;
  //}
  
  if (m_bSolidColor) {
    game->Clear(m_solidColor);
    return true;
  }
  
  if (!m_bIsLoaded) {
    game->Clear(olc::Pixel(0, 255, 255));
    return false;
  }

  olc::vf2d drawPos = {x, y};
  //game->DrawDecal(drawPos, m_screenDecal);
  game->DrawSprite(drawPos, m_screenSprite);
  return true;
}
