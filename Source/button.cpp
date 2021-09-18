#include "button.h"


Button::Button(int x, int y, int w, int h, std::string label)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  this->m_label = label;

  this->bgColor = olc::Pixel(0, 0, 0);
  this->textColor = olc::WHITE;
}

void Button::setCallbackFunction(std::function<void()> callback)
{
  this->m_callback = callback;
}

void Button::draw(olc::PixelGameEngine* drawer)
{
  //printf("drawing button %s at %d %d\n", m_label.c_str(), x, y);
  drawer->FillRect(x, y, w, h, bgColor);
  drawer->DrawString(x+2, y+2, m_label, textColor);  
}
