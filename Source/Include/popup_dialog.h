#ifndef popup_dialog_h
#define popup_dialog_h


#include <string>
#include <vector>

#include "olcPixelGameEngine.h"
#include "olcPopupMenu.h"


class ButtonDesc
{
public:
  std::string msg;
  int value;
};

class PopupDialog
{
 public:
  PopupDialog();

  void build(std::string message, std::vector<ButtonDesc> buttons);
  
  void draw(int x, int y, olc::PixelGameEngine* pge, olc::Sprite* menuSprite);

protected:
  std::vector<std::string> splitString(std::string msg);

private:
  std::string m_message;
  std::vector<std::string> m_messageVec;
  std::vector<ButtonDesc> m_buttonDescs;

  olc::vi2d m_sizeInPatches;
};

#endif // popup_dialog_h
