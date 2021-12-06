#ifndef arena_ai_controller_h
#define arena_ai_controller_h

#include "bicycle_car_physics.h"

class ArenaGameMode;
class Bdg_Car;

class ArenaAiContextCarController : public CarController
{
 public:
  virtual float getSteer() { return m_steering; }
  virtual float getThrottle() { return m_throttle; }
  virtual float getBrake() { return m_brake; }

  virtual void tick(float dt);

  virtual void setMode(ArenaGameMode* mode) {m_mode = mode;}
  virtual void setCar(Bdg_Car* car) {m_car = car;}
  
 private:
  void steerToPos(const Vec2f& target);
  
  
  ArenaGameMode* m_mode;
  Bdg_Car* m_car;

  float m_steering;
  float m_throttle;
  float m_brake;
};

#endif //arena_ai_controller_h
