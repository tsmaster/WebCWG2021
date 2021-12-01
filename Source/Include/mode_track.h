#ifndef mode_track_h
#define mode_track_h

#include "olcPixelGameEngine.h"

class CarsWithGuns;
class City;

class TrackGameMode
{
 public:
  void init(olc::Sprite* car_00_sprite,
	    olc::Sprite* car_01_sprite,
	    olc::Sprite* car_02_sprite,
	    olc::Sprite* car_03_sprite,
	    olc::Sprite* car_04_sprite,
	    olc::Sprite* car_05_sprite,
	    olc::Sprite* car_06_sprite,
	    olc::Sprite* car_07_sprite);

  bool update(CarsWithGuns* game, float elapsedSeconds);

  void draw(CarsWithGuns* game);

 protected:
  void handleUserInput(CarsWithGuns* game);  

 private:
  std::vector<olc::Sprite*> m_spriteVec;
  std::vector<olc::Decal*> m_decalVec;
};



#endif //mode_track_h
