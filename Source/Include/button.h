#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>

#include "olcPixelGameEngine.h"

class Button
{
 public:
  Button(int x, int y, int w, int h, std::string label);

  void setCallbackFunction(std::function<void()> callback);

  void draw(olc::PixelGameEngine* drawer);

  int x;
  int y;

  int w;
  int h;

  olc::Pixel bgColor;
  olc::Pixel textColor;
  
  std::string m_label;

  std::function<void()> m_callback;
};

#endif //BUTTON_H
