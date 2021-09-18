#include "modemgr.h"


ModeChangeRequest ModeChangeRequest::modeChangeRequestFactory(GameMode newGameMode)
{
  ModeChangeRequest mcm;
  mcm.newGameMode = newGameMode;
  return mcm;
}

ModeMgr::ModeMgr()
{
}

void ModeMgr::requestMode()
{
}
