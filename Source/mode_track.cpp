#include "mode_track.h"

#include "bdg_random.h"
#include "carswithguns.h"


void TrackGameMode::init(olc::Sprite* car_00_Sprite,
			 olc::Sprite* car_01_Sprite,
			 olc::Sprite* car_02_Sprite,
			 olc::Sprite* car_03_Sprite,
			 olc::Sprite* car_04_Sprite,
			 olc::Sprite* car_05_Sprite,
			 olc::Sprite* car_06_Sprite,
			 olc::Sprite* car_07_Sprite)
{
}

bool TrackGameMode::update(CarsWithGuns* game, float elapsedSeconds)
{
  handleUserInput(game);
  return true;
}

void TrackGameMode::handleUserInput(CarsWithGuns* game)
{
}

void TrackGameMode::draw(CarsWithGuns* game)
{
  game->Clear(olc::GREEN);

  int sw = game->ScreenWidth();
  int sh = game->ScreenHeight();

  int pcx = sw / 2;
  int pcy = sh / 2;
}

