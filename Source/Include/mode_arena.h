#ifndef mode_arena_h
#define mode_arena_h

#include "olcPixelGameEngine.h"
#include "olc_pgex_gamepad.h"

#include "bdg_math.h"
#include "camera.h"
#include "world_geom.h"

#include "bicycle_car_physics.h"

class Bdg_Car;
class CarsWithGuns;
class City;

class ArenaGameMode
{
 public:
  void init(olc::Sprite* car_00_sprite,
	    olc::Sprite* car_01_sprite,
	    olc::Sprite* car_02_sprite,
	    olc::Sprite* car_03_sprite,
	    olc::Sprite* car_04_sprite,
	    olc::Sprite* car_05_sprite,
	    olc::Sprite* car_06_sprite,
	    olc::Sprite* car_07_sprite,
	    olc::Sprite* arena_floor_sprite);

  bool update(CarsWithGuns* game, float elapsedSeconds);

  void draw(CarsWithGuns* game);

 protected:
  void handleUserInput(CarsWithGuns* game, float elapsedSeconds);  

 private:
  void setPlayerCar(int carNum);

  
  
  std::vector<olc::Sprite*> m_spriteVec;
  std::vector<olc::Decal*> m_decalVec;

  olc::Sprite* m_arenaFloorSprite;
  olc::Decal* m_arenaFloorDecal;

  olc::GamePad* m_gamepad = NULL;

  int m_playerControlledCarIndex = 0;

  std::vector<Bdg_Car*> m_cars;

  std::vector<WorldQuad> m_floors;
  std::vector<WorldQuad> m_walls;

  Camera m_camera;

  float m_physicsJuice = 0.0f;
  const float m_physicsFrameRate = 300.0f;
  const float m_physicsFrameTime = 1.0f / m_physicsFrameRate;

  PlayerGamepadCarController m_gamepadController;
};



#endif //mode_arena_h
