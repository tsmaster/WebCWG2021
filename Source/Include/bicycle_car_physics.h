#ifndef bicycle_car_physics_h
#define bicycle_car_physics_h

/*
 Bicycle Car Physics for arcade-feeling car mechanics

 See http://kidscancode.org/godot_recipes/2d/car_steering/

*/

#include "bdg_math.h"

#include "olcPixelGameEngine.h"
#include "olc_pgex_gamepad.h"

class CarController
{
public:
  virtual float getSteer() = 0;
  virtual float getThrottle() = 0;
  virtual float getBrake() = 0;
};

class PlayerGamepadCarController : public CarController
{
public:
  virtual float getSteer();
  virtual float getThrottle();
  virtual float getBrake();

  void setGamepad(olc::GamePad* gamepad) { m_gamepad = gamepad; }

private:
  olc::GamePad* m_gamepad = NULL;
};

class BicycleCarPhysics
{
public:
  void tick(float dt); // update the physics
  
  void getInput();

  void applyFriction();

  void calculateSteering(float dt);

  void setController(CarController* inController) {m_controller = inController;}

  void setPosition(Vec2f pos) {m_position = pos;}
  void setHeading(float rad) {m_heading = rad;}

  const Vec2f& getPosition() const { return m_position; }
  float getHeading() const { return m_heading; }

  const Vec2f& getVelocity() const { return m_velocity; }

private:
  // parameters
  float m_wheelBase = 3.5f; // distance (m) from rear wheel to front wheel
  float m_steerAngleDegMax = 30.0f; // how far the front wheels turn from straight
  // ahead to max rotation
  float m_enginePower = 30.0f; // m/s^2 max acceleration
  float m_brakingPower = -15.0f;
  float m_maxSpeedReverse = 10.0f; // maximum speed in reverse

  float m_friction = -0.9f; // velocity term
  float m_drag = -0.0015f; // vel^2 term

  float m_slipSpeed = 20.0f; // speed where drifting begins to be possible
  float m_tractionFast = 0.1f; // sliding traction when going fast
  float m_tractionSlow = 0.7f; // sliding traction when going slow
  
  // state
  Vec2f m_velocity = Vec2f(0.0f, 0.0f);
  Vec2f m_acceleration = Vec2f(0.0f, 0.0f);
  float m_steeringAngleRadCurr = 0.0f; // relative steering of wheels

  float m_heading=0.0f;
  Vec2f m_position= Vec2f(0.0f, 0.0f);
  
  CarController* m_controller = NULL;
};


#endif //bicycle_car_physics_h
