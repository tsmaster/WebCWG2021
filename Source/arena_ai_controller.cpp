#include "arena_ai_controller.h"

#include "bdg_car.h"

void ArenaAiContextCarController::tick(float dt)
{
  float closestDistance = -1.0f;
  Vec2f closestPos = Vec2f(0, 0);

  Vec2f myPos = m_car->getPosition();
  
  for (ArenaBarrel* b : m_mode->getBarrels()) {
    if (!b->getIsAlive()) {
      continue;
    }
    if (b->getOwningCar() == m_car) {
      continue;
    }
    Vec2f deltaToBarrel = myPos - b->getPosition();
    
    float dist = deltaToBarrel.len();
    if ((closestDistance < 0.0f) ||
	(dist < closestDistance)) {
      closestDistance = dist;
      closestPos = b->getPosition();
    }
  }

  steerToPos(closestPos);
}

void ArenaAiContextCarController::steerToPos(const Vec2f& target)
{
  Vec2f delta = target - m_car->getPosition();
  float absHeading = delta.angle();

  float relHeading = wrapAngle(absHeading - m_car->getHeading());

  m_steering = fmap(relHeading, -PI, PI, 1.0f, -1.0f);
  m_throttle = 1.0f;
  m_brake = 0.0f;

}
