#include "popup_dialog.h"

PopupDialog::PopupDialog()
{
}

void PopupDialog::build(std::string message, std::vector<ButtonDesc> buttons)
{
  m_message = message;
  m_messageVec = splitString(message); 
  m_buttonDescs = buttons;

  int maxLen = 0;
  for (std::string line : m_messageVec) {
    maxLen = std::max(maxLen, int(line.length()));
  }
  
  m_sizeInPatches = { maxLen + 4, int(m_messageVec.size() + 4) };  
}

std::vector<std::string> PopupDialog::splitString(std::string msg)
{
  std::string workingString = msg;
  std::vector<std::string> outVec;

  size_t pos;
  while ((pos = workingString.find('\n')) != std::string::npos) {
    std::string left = workingString.substr(0, pos);
    outVec.push_back(left);
    workingString.erase(0, pos + 1);
  }
  outVec.push_back(workingString);
  return outVec;  
}

void PopupDialog::draw(int x, int y, olc::PixelGameEngine* pge, olc::Sprite* menuSprite)
{
  olc::vi2d vScreenOffset(x,y);

  // === Draw Panel

  // Record current pixel mode user is using
  olc::Pixel::Mode currentPixelMode = pge->GetPixelMode();
  pge->SetPixelMode(olc::Pixel::MASK);

  int nPatch = 8;
  olc::vi2d vPatchSize = { nPatch, nPatch };

  // Draw Panel & Border
  olc::vi2d vPatchPos = { 0,0 };
  for (vPatchPos.x = 0; vPatchPos.x < m_sizeInPatches.x; vPatchPos.x++) {
      for (vPatchPos.y = 0; vPatchPos.y < m_sizeInPatches.y; vPatchPos.y++) {
	// Determine position in screen space
	olc::vi2d vScreenLocation = vPatchPos * nPatch + vScreenOffset;

	// Calculate which patch is needed
	olc::vi2d vSourcePatch = { 0, 0 };
	if (vPatchPos.x > 0) vSourcePatch.x = 1;
	if (vPatchPos.x == m_sizeInPatches.x - 1) vSourcePatch.x = 2;
	if (vPatchPos.y > 0) vSourcePatch.y = 1;
	if (vPatchPos.y == m_sizeInPatches.y - 1) vSourcePatch.y = 2;

	// Draw Actual Patch
	pge->DrawPartialSprite(vScreenLocation, menuSprite,
			       vSourcePatch * nPatch, vPatchSize);
      }
  }

  for (int lineNum = 0; lineNum < m_messageVec.size(); ++lineNum) {
    olc::vi2d linePos = {2 * nPatch + x,
      2 * nPatch + y + nPatch * lineNum};
      
    pge->DrawString(linePos, m_messageVec[lineNum], olc::WHITE);
  }
    

  pge->SetPixelMode(currentPixelMode);  
}
