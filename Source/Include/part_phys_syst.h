#ifndef part_phys_syst_h
#define part_phys_syst_h

#include <vector>
#include "bdg_math.h"

class Camera;
class CarsWithGuns;

struct Particle {
 public:
  Vec2f m_currentPos = Vec2f(0, 0);
  Vec2f m_prevPos = Vec2f(0, 0);
  float m_invMass;
  Vec2f m_forces = Vec2f(0, 0);
  float m_friction = 0.0f;
};

struct StickConstraint {
public:
  int m_index0, m_index1;
  float m_distance;
};

class ParticlePhysicsSystem {
 public:
  ParticlePhysicsSystem();

  void addParticle(Vec2f pos, float invMass);
  void removeParticle(int index);
  int countParticles() const;
  void linkParticles(int p1, int p2, float distance);
  int countConstraints() const;

  void updatePhysics(float elapsedSeconds);
  void draw(CarsWithGuns* game, const Camera& inCam) const;

  Vec2f getParticlePosition(int particleIndex) const;
  void setParticlePosition(int particleIndex, Vec2f pos);

  void clearForces();
  void applyForce(int index, Vec2f f);

  void setAllFriction(float f);
  void setFriction(int index, float f);

  const StickConstraint& getConstraint(int index) const;

  void stop();

 private:
  std::vector<Particle> m_particles;
  std::vector<StickConstraint> m_stickConstraints;
};

#endif // part_phys_syst_h
