#include "part_phys_syst.h"

#include "bdg_math.h"

#include <cstdio>

ParticlePhysicsSystem::ParticlePhysicsSystem()
{
  
}

void ParticlePhysicsSystem::addParticle(Vec2f pos, float invMass)
{
  Particle p;
  p.m_currentPos = pos;
  p.m_prevPos = pos;
  p.m_invMass = invMass;
  m_particles.push_back(p);
}

void ParticlePhysicsSystem::linkParticles(int i0, int i1, float dist)
{
  StickConstraint c;
  c.m_index0 = i0;
  c.m_index1 = i1;
  c.m_distance = dist;
  m_stickConstraints.push_back(c);
}

int ParticlePhysicsSystem::countParticles() const
{
  return m_particles.size();
}

void ParticlePhysicsSystem::updatePhysics(float elapsedSeconds)
{
  float e2 = elapsedSeconds * elapsedSeconds;
  
  // verlet step

  for (Particle& p : m_particles) {
    Vec2f deltaPos = p.m_currentPos - p.m_prevPos;
    Vec2f acceleration = p.m_forces * p.m_invMass;
    float invFriction = 1.0f - p.m_friction;

    Vec2f newPos = p.m_currentPos + deltaPos * invFriction + acceleration * e2;
    p.m_prevPos = p.m_currentPos;
    p.m_currentPos = newPos;
  }
}

void ParticlePhysicsSystem::draw(CarsWithGuns* game, const Camera& inCam) const
{
  
}

Vec2f ParticlePhysicsSystem::getParticlePosition(int index) const
{
  return m_particles[index].m_currentPos;
}

void ParticlePhysicsSystem::setParticlePosition(int index, Vec2f newVec)
{
  m_particles[index].m_currentPos = newVec;
}

int ParticlePhysicsSystem::countConstraints() const
{
  return m_stickConstraints.size();
}

const StickConstraint& ParticlePhysicsSystem::getConstraint(int i) const
{
  return m_stickConstraints[i];
}

void ParticlePhysicsSystem::applyForce(int i, Vec2f f)
{
  m_particles[i].m_forces = m_particles[i].m_forces + f;
}

void ParticlePhysicsSystem::clearForces()
{
  for (Particle& p : m_particles) {
    p.m_forces = Vec2f(0.0f, 0.0f);
  }
}

void ParticlePhysicsSystem::setAllFriction(float f)
{
  for (Particle& p : m_particles) {
    p.m_friction = f;
  }
}

void ParticlePhysicsSystem::setFriction(int i, float f)
{
  m_particles[i].m_friction = f;
}

void ParticlePhysicsSystem::stop()
{
  Vec2f z(0, 0);
  for (Particle& p : m_particles) {
    p.m_prevPos = p.m_currentPos;
    p.m_forces = z;
  }
}
