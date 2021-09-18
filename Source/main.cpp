#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_POPUPMENU
#include "olcPopupMenu.h"

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

#include "carswithguns.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int main()
{
  CarsWithGuns game;
  if (game.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 2, 2))
    game.Start();
  
  return 0;
}
