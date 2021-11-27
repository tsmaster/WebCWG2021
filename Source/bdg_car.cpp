#include "bdg_car.h"

#include "bdg_math.h"
#include "camera.h"
#include "part_phys_syst.h"
#include "world_geom.h"

Bdg_Car::Bdg_Car(Vec2f in_pos, float in_heading, olc::Decal* in_decal):
  m_position(in_pos), m_velocity(Vec2f(0.0f, 0.0f)), m_speed(0.0f), m_heading(in_heading),
  m_decal(in_decal)
  // m_topSpeed(100.0f), m_acceleration(10.0f), m_braking(30.0f), 
{
  Vec2f forward = Vec2f::makeAngleLength(in_heading, 2.0f);
  Vec2f left = Vec2f::makeAngleLength(in_heading + PIOVER2, 1.0f);

  /* move to particle physics system 
  
  m_particles.addParticle(in_pos - forward + left, 1.0f);
  m_particles.addParticle(in_pos + forward, 1.0f);
  m_particles.addParticle(in_pos - forward - left, 1.0f);

  float diag = (float)sqrt(4*4 + 1*1);
  m_particles.linkParticles(0, 1, diag);
  m_particles.linkParticles(1, 2, diag);
  m_particles.linkParticles(2, 0, 2.0f);
  */

  m_bicyclePhysics.setPosition(in_pos);
  m_bicyclePhysics.setHeading(in_heading);
}


/* now part of controller
void Bdg_Car::setSteer(float steer)
{
  m_ctrlSteer = steer;
}

void Bdg_Car::setThrottle(float throttle)
{
  m_ctrlThrottle = throttle;
  if (m_ctrlThrottle < 0.01f) {
    m_ctrlThrottle = 0.0f;
  }
}

void Bdg_Car::setBrake(float brake)
{
  m_ctrlBrake = brake;
  if (m_ctrlBrake < 0.01f) {
    m_ctrlBrake = 0.0f;
  }
}

*/

/*
void oldPhysics()
{
  if (abs(m_ctrlThrottle - m_ctrlBrake) < 0.01f) {
    const float coastDecel = 5.0f; // meters per second per second
    m_speed -= coastDecel * elapsedSeconds;
  } else {    
    m_speed += (m_acceleration * m_ctrlThrottle - m_braking * m_ctrlBrake) * elapsedSeconds;
  }
  if (m_speed < 0.0f) {
    m_speed = 0.0f;
  }

  if (m_speed > m_topSpeed) {
    m_speed = m_topSpeed;
  }

  const float degreesPerSecond = 90.0f;

  // this is not how cars work

  float deltaDegrees = degreesPerSecond * elapsedSeconds * m_ctrlSteer;

  m_heading -= degToRad(deltaDegrees);

  m_velocity = {float(cos(m_heading) * m_speed),
    float(sin(m_heading) * m_speed)};

  m_position = {m_position.x + m_velocity.x * elapsedSeconds,
    m_position.y + m_velocity.y * elapsedSeconds};
  
    }*/

/*
void Bdg_Car::oldUpdatePhysics(float elapsedSeconds, const std::vector<WorldQuad>& walls)
{
  Vec2f oldCenter = m_position;

  float throttleForceMag = 0.0f;
  if (m_speed < m_topSpeed) {
    throttleForceMag = m_throttleFactor * m_ctrlThrottle;
  }

  Vec2f engineForce = Vec2f::makeAngleLength(m_heading, throttleForceMag);
  //printf("applying engine force %f %f\n", engineForce.x, engineForce.y);

  float carMovementDirection = m_velocity.angle();
  float carAngleOfAttack = wrapAngle(carMovementDirection - m_heading);  
  //printf("car aoa: %f\n", carAngleOfAttack);

  const float BASE_FRICTION = 0.01f;
  
  m_particles.setAllFriction(BASE_FRICTION * abs(sin(carAngleOfAttack)));
  
  float frontTireDirectionRel = fmap(m_ctrlSteer, -1, 1, PI/4.0, -PI/4.0);
  float frontTireHeading = m_heading + frontTireDirectionRel;

  float frontTireAngleOfAttack = wrapAngle(carMovementDirection - frontTireHeading);
  //printf("ft aoa: %f\n", frontTireAngleOfAttack);

  m_particles.setFriction(1, BASE_FRICTION * abs(sin(frontTireAngleOfAttack)));

  m_particles.clearForces();
  m_particles.applyForce(0, engineForce);
  m_particles.applyForce(2, engineForce);

  Vec2f frontWheelForce = Vec2f::makeAngleLength(frontTireHeading, throttleForceMag);
  m_particles.applyForce(1, frontWheelForce);
  
  m_particles.updatePhysics(elapsedSeconds);

  const int NUM_CONSTRAINT_ITERATIONS = 3;
  
  for (int constraintIter = 0; constraintIter < NUM_CONSTRAINT_ITERATIONS; ++constraintIter) {
    for (int constraintIndex = 0; constraintIndex < m_particles.countConstraints(); ++constraintIndex) {
      const StickConstraint& sc = m_particles.getConstraint(constraintIndex);
      Vec2f vc0 = m_particles.getParticlePosition(sc.m_index0);
      Vec2f vc1 = m_particles.getParticlePosition(sc.m_index1);
      Vec2f delta = vc1-vc0;
      float deltaLength = delta.len();
      float diff = (sc.m_distance-deltaLength) / deltaLength;

      Vec2f newVC0 = vc0 - delta * (0.5f * diff);
      Vec2f newVC1 = vc1 + delta * (0.5f * diff);

      Vec2f newDelta = newVC1 - newVC0;

      m_particles.setParticlePosition(sc.m_index0, newVC0);
      m_particles.setParticlePosition(sc.m_index1, newVC1);
    }

    for (int particleIndex = 0; particleIndex < m_particles.countParticles(); ++particleIndex) {
      for (int wallIndex = 0; wallIndex < walls.size(); ++wallIndex) {
	Vec2f curPos = m_particles.getParticlePosition(particleIndex);
	const WorldQuad& q = walls[wallIndex];
	if (q.pointInside(curPos)) {
	  Vec2f newPos = q.projectToOutside(curPos);
	  m_particles.setParticlePosition(particleIndex, newPos);
	}
      }
    }
  }
  Vec2f backLeft = m_particles.getParticlePosition(0);
  Vec2f backRight = m_particles.getParticlePosition(2);
  Vec2f frontCenter = m_particles.getParticlePosition(1);

  Vec2f backCenter = (backLeft + backRight) * 0.5f;

  Vec2f center = (backCenter + frontCenter) * 0.5f;

  m_position = center;
  m_velocity = (m_position - oldCenter) * (1.0f / elapsedSeconds);
  m_speed = m_velocity.len();
  m_heading = (frontCenter-backCenter).angle();

  if ((m_speed < 0.5f) && (m_ctrlThrottle < 0.1f) && (abs(m_ctrlSteer) < 0.1f)) {
    stop();
  }
}
*/

void Bdg_Car::updatePhysics(float dt, const std::vector<WorldQuad>& inWalls)
{
  m_bicyclePhysics.tick(dt, inWalls);

  m_position = m_bicyclePhysics.getPosition();
  m_heading = m_bicyclePhysics.getHeading();
  m_velocity = m_bicyclePhysics.getVelocity();
  m_speed = m_velocity.len();
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

  // show particles

  /*
  std::vector<Vec2f> particlePosns;

  for (int i = 0; i < m_particles.countParticles(); ++i) {
    Vec2f particleScreenPosition = inCam.worldPosToScreenPos(m_particles.getParticlePosition(i));
    particlePosns.push_back(particleScreenPosition);
  }

  for (int i = 0; i < m_particles.countConstraints(); ++i) {
    const StickConstraint& c = m_particles.getConstraint(i);

    Vec2f& v0 = particlePosns[c.m_index0];
    Vec2f& v1 = particlePosns[c.m_index1];
    game->DrawLineDecal({v0.x, v0.y},
			{v1.x, v1.y},
			olc::GREEN);
  }  
  
  for (int i = 0; i < particlePosns.size(); ++i) {
    float dotSz = 4.0f;
    
    olc::vf2d ul = {particlePosns[i].x - dotSz * 0.5f,
      particlePosns[i].y - dotSz * 0.5f};
    olc::vf2d sz = {dotSz, dotSz};
    
    game->GradientFillRectDecal(ul, sz,
				olc::GREEN,
				olc::GREEN,
				olc::GREEN,
				olc::GREEN);
  }
  */
}

void Bdg_Car::stop()
{
  /*
  m_particles.stop();
  */
}


void Bdg_Car::setController(CarController* inCtrl)
{
  m_bicyclePhysics.setController(inCtrl);
}
