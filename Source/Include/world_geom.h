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

  bool pointInside(Vec2f p) const;
  
  Vec2f projectToOutside(Vec2f p) const;

  static WorldQuad MakeFromAABB(Vec2f ul, Vec2f lr, olc::Decal* inDecal, olc::Pixel inColor, int inLayerIndex);

 protected:
  bool pointInsideAABB(Vec2f p) const;
  bool pointInsidePolygon(Vec2f p) const;

  Vec2f projectToOutsideAABB(Vec2f p) const;
  Vec2f projectToOutsidePolygon(Vec2f p) const;
  
 private:
  std::vector<Vec2f> m_corners;

  float xMin, xMax, yMin, yMax;

  olc::Decal* m_decal;
  olc::Pixel m_color;
  int m_layerIndex;

  bool m_bIsAxisAlignedRectangle = false;
};



#endif //world_geom_h
