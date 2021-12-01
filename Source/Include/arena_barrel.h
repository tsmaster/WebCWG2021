#ifndef arena_barrel
#define arena_barrel

#include "bdg_math.h"
#include "camera.h"
#include "olcPixelGameEngine.h"

class Bdg_Car;
class CarsWithGuns;

class ArenaBarrel
{
 public:
  ArenaBarrel(Vec2f posn, olc::Decal* inDecal);
  void draw(CarsWithGuns* game, const Camera& inCam) const;
  void tickPhysics(float dt);

  void attachToCar(Bdg_Car* inUpstreamCar) { m_upstreamCar = inUpstreamCar; }
  void attachToBarrel(ArenaBarrel* inUpstreamBarrel) { m_upstreamBarrel = inUpstreamBarrel; }
  void detach(bool propagate);

  bool hasUpstreamAttachment() { return ((m_upstreamCar != NULL) || (m_upstreamBarrel != NULL)); }

  const Vec2f& getPosition() const { return m_posn; }

  ArenaBarrel* getDownstreamBarrel() const { return m_downstreamBarrel; }
  ArenaBarrel* getUpstreamBarrel() const { return m_upstreamBarrel; }

  void setDownstreamBarrel(ArenaBarrel* inBarrel) { m_downstreamBarrel = inBarrel; }
  void setUpstreamBarrel(ArenaBarrel* inBarrel) { m_upstreamBarrel = inBarrel; }

  void setUpstreamCar(Bdg_Car* inCar) { m_upstreamCar = inCar; }
  Bdg_Car* getUpstreamCar() { return m_upstreamCar; }

  Bdg_Car* getOwningCar();

  void setIsAlive(bool isAlive) { m_bIsAlive = isAlive; }
  bool getIsAlive() const { return m_bIsAlive; }

 private:
  
  Vec2f m_posn;

  olc::Decal* m_decal;
  
  Bdg_Car* m_upstreamCar = NULL;
  ArenaBarrel* m_upstreamBarrel = NULL;
  ArenaBarrel* m_downstreamBarrel = NULL;
  const float m_towLength = 2.5f;
  const float m_radius = 0.75f;

  bool m_bIsAlive = true;
};

#endif //arena_barrel
