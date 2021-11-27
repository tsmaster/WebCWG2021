

// see http://kidscancode.org/godot_recipes/2d/car_steering/

#include "bicycle_car_physics.h"

#include "olcPixelGameEngine.h"

void BicycleCarPhysics::tick(float dt, const std::vector<WorldQuad>& inWalls) {
  // "_physics_process" in the related webpage tutorial
  m_acceleration = Vec2f(0.0f, 0.0f);
  getInput();
  applyFriction();
  calculateSteering(dt);

  moveConstrained(dt, inWalls);
}

void BicycleCarPhysics::moveConstrained(float dt, const std::vector<WorldQuad>& inWalls) {
  Vec2f oldPosition = m_position;
  m_velocity = m_velocity + m_acceleration * dt;
  m_position = m_position + m_velocity * dt;

  float particleOffsetLen = 1.0f;
  float particleRadius = 1.0f;
  Vec2f particleOffsetVec = Vec2f::makeAngleLength(m_heading, particleOffsetLen);

  std::vector<Vec2f> particles;
  particles.push_back(m_position + particleOffsetVec);
  particles.push_back(m_position - particleOffsetVec);

  bool hasConstrained = false;

  for (const WorldQuad& wall : inWalls) {
    for (int particleIndex = 0; particleIndex < particles.size(); ++particleIndex) {
      Vec2f p = particles[particleIndex];
      
      if (wall.constrainsParticle(p, particleRadius)) {
	Vec2f newPos = wall.pushOut(p, particleRadius);
	particles[particleIndex] = newPos;
	hasConstrained = true;
      }
    }
  }

  if (hasConstrained) {
    Vec2f newCenter = (particles[0] + particles[1]) * 0.5f;
    Vec2f newVelocity = (newCenter - oldPosition) * (1.0f / dt);
    m_position = newCenter;
    m_velocity = newVelocity;
    m_heading = (particles[0] - particles[1]).angle();
  }
}

void BicycleCarPhysics::getInput()
{
  float turn = 0.0f;
  if (m_controller != NULL) {
    // flip this, as our controls have left as -1 and right as 1
    // while heading is positive CCW
    turn = -m_controller->getSteer();
  }

  m_steeringAngleRadCurr = turn * degToRad(m_steerAngleDegMax);

  float throttle = 0.0f;
  float brake = 0.0f;
  if (m_controller != NULL) {
    throttle = m_controller->getThrottle();
    brake = m_controller->getBrake();
  }

  m_acceleration = Vec2f::makeAngleLength(m_heading, m_enginePower * (throttle-brake));
}

void BicycleCarPhysics::applyFriction()
{
  if (m_velocity.len() < 0.01) {
    m_velocity = Vec2f(0.0f, 0.0f);
  }
  Vec2f frictionForce = m_velocity * m_friction;
  Vec2f dragForce = m_velocity * m_velocity.len() * m_drag;
  if (m_velocity.len() < 1) {
    frictionForce = frictionForce * 3.0f;
  }
  m_acceleration = m_acceleration + dragForce + frictionForce;
}

void BicycleCarPhysics::calculateSteering(float dt)
{
  Vec2f halfBaseVec = Vec2f::makeAngleLength(m_heading, m_wheelBase * 0.5f);
  Vec2f rearWheelPos = m_position - halfBaseVec;
  Vec2f frontWheelPos = m_position + halfBaseVec;

  Vec2f newRearWheel = rearWheelPos + m_velocity * dt;
  Vec2f newFrontWheel = frontWheelPos + Vec2f::makeAngleLength(m_heading +m_steeringAngleRadCurr, m_velocity.len()) * dt;
  
  Vec2f newForward = (newFrontWheel - newRearWheel).normalized();

  float traction = m_velocity.len() > m_slipSpeed ? m_tractionFast : m_tractionSlow;
  
  float dot = newForward.dot(m_velocity.normalized());
  if (dot > 0) {
    m_velocity = m_velocity.lerp(newForward * m_velocity.len(), traction);
  } else if (dot < 0) {
    m_velocity = newForward * -1.0f * std::min(m_velocity.len(), m_maxSpeedReverse);
  }
  m_heading = newForward.angle();
}


float PlayerGamepadCarController::getSteer()
{
  if (m_gamepad == NULL) {
    return 0.0f;
  }
  return m_gamepad->getAxis(olc::GPAxes::LX);
}

float PlayerGamepadCarController::getThrottle()
{
  if (m_gamepad == NULL) {
    return 0.0f;
  }
  return m_gamepad->getAxis(olc::GPAxes::TR);
}

float PlayerGamepadCarController::getBrake()
{
  if (m_gamepad == NULL) {
    return 0.0f;
  }
  return m_gamepad->getAxis(olc::GPAxes::TL);
}

