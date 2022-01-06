#include "bdg_car.h"

#include "bdg_math.h"
#include "camera.h"
#include "part_phys_syst.h"
#include "world_geom.h"

Bdg_Car::Bdg_Car(Vec2f in_pos, float in_heading, olc::Decal* in_decal, const char* in_name):
  m_position(in_pos), m_velocity(Vec2f(0.0f, 0.0f)), m_speed(0.0f), m_heading(in_heading),
  m_decal(in_decal), m_name(std::string(in_name)), m_targetPos(0.0f, 0.0f)
{
  Vec2f forward = Vec2f::makeAngleLength(in_heading, 2.0f);
  Vec2f left = Vec2f::makeAngleLength(in_heading + PIOVER2, 1.0f);

  m_bicyclePhysics.setPosition(in_pos);
  m_bicyclePhysics.setHeading(in_heading);
}

void Bdg_Car::updatePhysics(float dt,
			    const std::vector<WorldQuad>& inWalls,
			    ArenaGameMode* inGameMode)
{
  m_bicyclePhysics.tick(dt, inWalls);

  m_position = m_bicyclePhysics.getPosition();
  m_heading = m_bicyclePhysics.getHeading();
  m_velocity = m_bicyclePhysics.getVelocity();
  m_speed = m_velocity.len();

  for (ArenaBarrel* b : inGameMode->getBarrels()) {
    if (!b->getIsAlive()) {
      continue;
    }
    if (inPickupRange(b->getPosition()) && (b->getOwningCar() != this)) {
      Bdg_Car* oldOwningCar = b->getOwningCar();
      
      if ((oldOwningCar == NULL) ||
	  (oldOwningCar->canBeStolenFrom())) {
	b->detach(false);
	addBarrel(b);
	startStolenFromTimer();
	if (oldOwningCar != NULL) {
	  oldOwningCar->startStolenFromTimer();
	}
      }
    }
  }

  if (m_barrelDropoffTimer > 0) {
    m_barrelDropoffTimer = std::max(0.0f, m_barrelDropoffTimer - dt);
  }

  if (m_stolenFromTimer > 0) {
    m_stolenFromTimer = std::max(0.0f, m_stolenFromTimer - dt);
  }
}

void Bdg_Car::draw(CarsWithGuns* game, const Camera& inCam) const
{
  Vec2f forwardToNose = Vec2f(m_carLength * 0.5f, 0.0f).rotate(m_heading);
  Vec2f backwardToTail = forwardToNose * -1.0f;

  Vec2f leftToSide = Vec2f(0.0f, m_carWidth * 0.5f).rotate(m_heading);
  Vec2f rightToSide = leftToSide * -1.0f;

  Vec2f frontLeft   = m_position + forwardToNose + leftToSide;
  Vec2f frontRight  = m_position + forwardToNose + rightToSide;
  Vec2f backLeft    = m_position + backwardToTail + leftToSide;
  Vec2f backRight   = m_position + backwardToTail + rightToSide;

  std::vector<Vec2f> cornerVecs;
  cornerVecs.push_back(inCam.worldPosToScreenPos(backLeft));
  cornerVecs.push_back(inCam.worldPosToScreenPos(frontLeft));
  cornerVecs.push_back(inCam.worldPosToScreenPos(frontRight));
  cornerVecs.push_back(inCam.worldPosToScreenPos(backRight));
  
  std::vector<olc::vf2d> cornerScratch;
  for (Vec2f v : cornerVecs) {
    cornerScratch.push_back(olc::vf2d(v.x, v.y));
  }

  olc::vf2d wallUVArray[] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1}};

  olc::Pixel color = olc::WHITE;
  
  olc::Pixel wallColorArray[] = {
    color,
    color,
    color,
    color
  };
  
  game->DrawExplicitDecal(m_decal,
			  &(cornerScratch[0]),
			  wallUVArray,
			  wallColorArray,
			  4);
}

void Bdg_Car::setController(CarController* inCtrl)
{
  m_controller = inCtrl;
  m_bicyclePhysics.setController(inCtrl);
}

Vec2f Bdg_Car::getTowPoint() const
{
  return m_position - Vec2f::makeAngleLength(m_heading, m_carLength * 0.5);
}

void Bdg_Car::addBarrel(ArenaBarrel* barrel)
{
  ArenaBarrel* lastBarrel = NULL;

  barrel->setUpstreamBarrel(NULL);
  barrel->setUpstreamCar(NULL);

  if (m_downstreamBarrel != NULL) {
    // determine last barrel
    for (lastBarrel = m_downstreamBarrel; lastBarrel->getDownstreamBarrel() != NULL; lastBarrel = lastBarrel->getDownstreamBarrel());
  }

  if (lastBarrel != NULL) {
    lastBarrel->setDownstreamBarrel(barrel);
    barrel->setUpstreamBarrel(lastBarrel);
  } else {
    m_downstreamBarrel = barrel;
    barrel->setUpstreamCar(this);
  }
}

void Bdg_Car::dropBarrel()
{
  m_barrelDropoffTimer = m_barrelDropoffTimerLength;

  printf("car %s dropping barrel\n", m_name.c_str());

  if (m_downstreamBarrel != NULL) {
    ArenaBarrel* nextBarrel = m_downstreamBarrel->getDownstreamBarrel();
    m_downstreamBarrel->setIsAlive(false);
    m_downstreamBarrel->detach(false);
    m_downstreamBarrel = nextBarrel;
    if (m_downstreamBarrel != NULL) {
      m_downstreamBarrel->setUpstreamBarrel(NULL);
      m_downstreamBarrel->setUpstreamCar(this);
    }
  }
}

bool Bdg_Car::canDropBarrel()
{
  return ((m_downstreamBarrel != NULL) && (m_barrelDropoffTimer == 0.0f));
}

bool Bdg_Car::canBeStolenFrom()
{
  return ((m_downstreamBarrel != NULL) && (m_stolenFromTimer == 0.0f));  
}

void Bdg_Car::startStolenFromTimer()
{
  m_stolenFromTimer = m_stolenFromTimerLength;
}
