#include "arena_ai_controller.h"

#include "bdg_car.h"

void ArenaAiContextCarController::tick(float dt)
{
  m_simpleAi.tick(NULL, m_mode, m_car, dt);
}

void ArenaAiContextCarController::steerToPos(const Vec2f& target)
{
  Vec2f delta = target - m_car->getPosition();
  float absHeading = delta.angle();

  float relHeading = wrapAngle(absHeading - m_car->getHeading());

  m_steering = fmap(relHeading, -PI, PI, 1.0f, -1.0f);

  float distToTarget = delta.len();

  if ((distToTarget < m_tooCloseRadius) &&
      (abs(radToDeg(relHeading)) > m_tooCloseDegrees)) {
    m_throttle = -1.0f;
    if (relHeading < 0.0f) {
      m_steering = -1.0f;
    } else {
      m_steering = 1.0f;
    }
  } else {
    m_throttle = 1.0f;
  }
  
  m_brake = 0.0f;
}
