#ifndef bdg_car_h
#define bdg_car_h

#include "bicycle_car_physics.h"
#include "bdg_math.h"
#include "carswithguns.h"
//#include "part_phys_syst.h"

#include "gen_barrelSimple.h"

class Camera;
class WorldQuad;
class CarController;

class Bdg_Car
{
 public:
  /**
     in_pos, position in a x-east, y-north coordinate system
     in_heading, rotation in radians where 0 is east
     in_decal, a decal to draw the car
   **/
  Bdg_Car(Vec2f in_pos, float in_heading, olc::Decal* in_decal, const char* name);

  // sets steering between -1.0f (full left) to 1.0f (full right)
  void setSteer(float steer);

  // sets engine throttle from 0.0f(no gas) to 1.0f (full throttle!)
  void setThrottle(float throttle);

  // sets brake from 0.0f (no brakes) to 1.0f (full brakes)
  void setBrake(float brake);

  // calculate the effect of controls (steering/throttle/brake) on
  // the physical state (acceleration, velocity, position, heading)
  void updatePhysics(float elapsedSeconds, const std::vector<WorldQuad>& walls, ArenaGameMode* in_mode);

  // draw the car to the screen
  void draw(CarsWithGuns* game, const Camera& inCam) const;

  Vec2f& getPosition() { return m_position; }
  float getSpeed() { return m_speed; }
  float getHeading() { return m_heading; }

  void stop();

  void setController(CarController* inCtrl);
  CarController* getController() { return m_controller; }

  Vec2f getTowPoint() const;

  bool inPickupRange(Vec2f target) const { return (target - m_position).len() < m_pickupRange; }

  void addBarrel(ArenaBarrel* b);
  void dropBarrel();
  void detachBarrelChain() { m_downstreamBarrel = NULL; }

  bool hasBarrel() { return m_downstreamBarrel != NULL; }

  bool canDropBarrel();

  bool canBeStolenFrom();
  void startStolenFromTimer();

  void setName(std::string name) { m_name = name; }
  const std::string& getName() const { return m_name; }

  // Should this be part of a brain class?
  Vec2f getTargetPos() { return m_targetPos; }
  void setTargetPos(Vec2f targetPos) { m_targetPos = targetPos; }
  
 private:
  std::string m_name = std::string("Car");
  
  Vec2f m_position;

  Vec2f m_velocity;
  float m_speed = 0.0f;
  float m_heading = 0.0f;
  olc::Decal* m_decal;

  const float m_carLength = 4.0f;
  const float m_carWidth = 2.0f;
  
  const float m_pickupRange = 5.0f;

  ArenaBarrel* m_downstreamBarrel = NULL;

  float m_barrelDropoffTimer = 0.0f;
  const float m_barrelDropoffTimerLength = 0.5f;

  float m_stolenFromTimer = 0.0f;
  const float m_stolenFromTimerLength = 0.2f;
  
  /*  
  float m_topSpeed;
  float m_acceleration;
  float m_braking;


  float m_ctrlSteer = 0.0f;
  float m_ctrlThrottle = 0.0f;
  float m_ctrlBrake = 0.0f;

  ParticlePhysicsSystem m_particles;

  const float m_throttleFactor = 20.0f;
  const float m_steerFactor = 0.05f;

  */

  CarController* m_controller = NULL;
  BicycleCarPhysics m_bicyclePhysics;

  Vec2f m_targetPos;
};

#endif // bdg_car_h
