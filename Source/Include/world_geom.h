#ifndef world_geom_h
#define world_geom_h

#include "olcPixelGameEngine.h"

#include "bdg_math.h"

class Camera;
class CarsWithGuns;

class WorldQuad
{
 public:
  WorldQuad(Vec2f ul, Vec2f ur, Vec2f lr, Vec2f ll, olc::Decal* inDecal, olc::Pixel inColor, int inLayerIndex);

  void draw(CarsWithGuns* game, const Camera& inCam);

  bool pointInside(const Vec2f& p) const;
  
  Vec2f closestPoint(const Vec2f& p) const;

  Vec2f centerPoint() const;

  static WorldQuad MakeFromAABB(Vec2f ul, Vec2f lr, olc::Decal* inDecal, olc::Pixel inColor, int inLayerIndex);

  bool constrainsParticle(const Vec2f& p, float r) const;
  Vec2f pushOut(const Vec2f& p, float r) const;
  float distanceToWall(const Vec2f& p) const;

  bool raycast(const Vec2f& rayOrigin,
	       const Vec2f& rayDirection,
	       Vec2f& outIntersection) const;

  void print() const;
  
 protected:
  Vec2f closestPointAABB(const Vec2f& p) const;
  Vec2f closestPointPolygon(const Vec2f& p) const;

  float distToWallAABB(const Vec2f& p) const;
  float distToWallPolygon(const Vec2f& p) const;

  bool raycastAABB(const Vec2f& rayOrigin,
		   const Vec2f& rayDirection,
		   Vec2f& outIntersection) const;

  bool raycastPolygon(const Vec2f& rayOrigin,
		      const Vec2f& rayDirection,
		      Vec2f& outIntersection) const;

 private:
  std::vector<Vec2f> m_corners;

  float xMin, xMax, yMin, yMax;

  olc::Decal* m_decal;
  olc::Pixel m_color;
  int m_layerIndex;

  bool m_bIsAxisAlignedRectangle = false;
};



#endif //world_geom_h
