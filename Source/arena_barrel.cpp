#include "arena_barrel.h"

#include "bdg_car.h"

ArenaBarrel::ArenaBarrel(Vec2f inPosn, olc::Decal* inDecal) : m_posn(inPosn), m_decal(inDecal)
{
  m_upstreamCar = NULL;
  m_upstreamBarrel = NULL;
  m_downstreamBarrel = NULL;
}

void ArenaBarrel::draw(CarsWithGuns* game, const Camera& inCam) const
{
  if (!m_bIsAlive) {
    return;
  }
  
  Vec2f diagonal(m_radius, m_radius);
  Vec2f llScreen = inCam.worldPosToScreenPos(m_posn - diagonal);
  Vec2f urScreen = inCam.worldPosToScreenPos(m_posn + diagonal);

  float left = llScreen.x;
  float right = urScreen.x;
  float bottom = llScreen.y;
  float top = urScreen.y;

  std::vector<Vec2f> cornerVecs;
  cornerVecs.push_back(Vec2f(left, top));
  cornerVecs.push_back(Vec2f(right, top));
  cornerVecs.push_back(Vec2f(right, bottom));
  cornerVecs.push_back(Vec2f(left, bottom));
  
  std::vector<olc::vf2d> cornerScratch;
  for (Vec2f v : cornerVecs) {
    cornerScratch.push_back(olc::vf2d(v.x, v.y));
  }

  olc::vf2d uvArray[] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1}};

  olc::Pixel color = olc::WHITE;
  
  olc::Pixel colorArray[] = {
    color,
    color,
    color,
    color
  };
  
  game->DrawExplicitDecal(m_decal,
			  &(cornerScratch[0]),
			  uvArray,
			  colorArray,
			  4);
}

void ArenaBarrel::tickPhysics(float dt)
{
  if ((!m_bIsAlive) || (!hasUpstreamAttachment())) {
    return;
  }
  
  Vec2f destination(0,0);
  bool isLinked = false;
  
  if (m_upstreamCar != NULL) {
    // move to car
    destination = m_upstreamCar->getTowPoint();
    isLinked = true;
  }

  if (m_upstreamBarrel != NULL) {
    // move to barrel
    destination = m_upstreamBarrel->getPosition();
    isLinked = true;    
  }

  if (!isLinked) {
    return;
  }

  Vec2f toDestVec = destination - m_posn;
  if (toDestVec.len() > m_towLength) {
    m_posn = destination - (toDestVec.normalized() * m_towLength);
  }
}

Bdg_Car* ArenaBarrel::getOwningCar()
{
  ArenaBarrel* b = this;
  while (b->getUpstreamBarrel() != NULL) {
    b = b->getUpstreamBarrel();
  }
  return b->getUpstreamCar();
}

void ArenaBarrel::detach(bool propagate)
{
  if (m_upstreamCar != NULL) {
    m_upstreamCar->detachBarrelChain();
  }

  if (m_upstreamBarrel) {
    m_upstreamBarrel->setDownstreamBarrel(NULL);
  }
  
  m_upstreamCar = NULL; m_upstreamBarrel = NULL;

  ArenaBarrel* oldDownstream = m_downstreamBarrel;
  m_downstreamBarrel = NULL;

  if ((propagate) && (oldDownstream != NULL)) {
    oldDownstream->detach(true);
  }
}
