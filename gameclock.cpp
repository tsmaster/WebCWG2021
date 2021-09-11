#include "gameclock.h"

GameClock::GameClock()
{
  m_counter = 0;
}

void GameClock::increment()
{
  ++m_counter;
}

unsigned int GameClock::getTime() const
{
  return m_counter;
}
