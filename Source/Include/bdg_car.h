#ifndef bdg_car_h
#define bdg_car_h

#include "bdg_math.h"
#include "carswithguns.h"
#include "part_phys_syst.h"

class Camera;
class WorldQuad;

class Bdg_Car
{
 public:
  /**
     in_pos, position in a x-east, y-north coordinate system
     in_heading, rotation in radians where 0 is east
     in_decal, a decal to draw the car
   **/
  Bdg_Car(Vec2f in_pos, float in_heading, olc::Decal* in_decal);

  // sets steering between -1.0f (full left) to 1.0f (full right)
  void setSteer(float steer);

  // sets engine throttle from 0.0f(no gas) to 1.0f (full throttle!)
  void setThrottle(float throttle);

  // sets brake from 0.0f (no brakes) to 1.0f (full brakes)
  void setBrake(float brake);

  // calculate the effect of controls (steering/throttle/brake) on
  // the physical state (acceleration, velocity, position, heading)
  void updatePhysics(float elapsedSeconds, const std::vector<WorldQuad>& walls);

  // draw the car to the screen
  void draw(CarsWithGuns* game, const Camera& inCam) const;

  Vec2f getPosition() { return m_position; }
  float getSpeed() { return m_speed; }
  float getHeading() { return m_heading; }

  void stop();
  
 private:
  Vec2f m_position;

  Vec2f m_velocity;
  float m_speed = 0.0f;
  float m_heading = 0.0f;

  float m_topSpeed;
  float m_acceleration;
  float m_braking;

  olc::Decal* m_decal;

  float m_ctrlSteer = 0.0f;
  float m_ctrlThrottle = 0.0f;
  float m_ctrlBrake = 0.0f;

  const float m_carLength = 4.0f;
  const float m_carWidth = 2.0f;

  ParticlePhysicsSystem m_particles;

  const float m_throttleFactor = 20.0f;
  const float m_steerFactor = 0.05f;
};

#endif // bdg_car_h
