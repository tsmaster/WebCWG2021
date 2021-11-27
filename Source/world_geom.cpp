#include "world_geom.h"

#include "bdg_math.h"
#include "camera.h"
#include "carswithguns.h"


WorldQuad::WorldQuad(Vec2f ul, Vec2f ur, Vec2f lr, Vec2f ll, olc::Decal* inDecal, olc::Pixel inColor, int inLayerIndex) : m_decal(inDecal), m_color(inColor), m_layerIndex(inLayerIndex)
{
  m_corners.push_back(ul);
  m_corners.push_back(ur);
  m_corners.push_back(lr);
  m_corners.push_back(ll);

  xMin = xMax = ul.x;
  yMin = yMax = ul.y;

  for (Vec2f v : m_corners) {
    xMin = std::min(xMin, v.x);
    xMax = std::max(xMax, v.x);
    yMin = std::min(yMin, v.y);
    yMax = std::max(yMax, v.y);
  }

  m_bIsAxisAlignedRectangle = ((ul.y == ur.y) &&
			       (ll.y == lr.y) &&
			       (ul.x == ll.x) &&
			       (ur.x == lr.x));
}

void WorldQuad::draw(CarsWithGuns* game, const Camera& inCam)
{
  std::vector<olc::vf2d> cornerScratch;
  for (int i = 0; i < 4; ++i) {
    Vec2f sp = inCam.worldPosToScreenPos(m_corners[i]);
    olc::vf2d c = {sp.x, sp.y};
    cornerScratch.push_back(c);
  }

  olc::vf2d wallUVArray[] = {
    {0, 0},
    {1, 0},
    {1, 1},
    {0, 1}};

  olc::Pixel wallColorArray[] = {
    m_color,
    m_color,
    m_color,
    m_color
  };
  game->DrawExplicitDecal(m_decal,
			  &(cornerScratch[0]),
			  wallUVArray,
			  wallColorArray,
			  4);

}

float WorldQuad::distToWallAABB(const Vec2f& v) const {
  // using SDF for box-exact https://iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
  float cx = (xMax + xMin) * 0.5f;
  float cy = (yMax + yMin) * 0.5f;
  float bx = xMax - cx;
  float by = yMax - cy;

  float px = v.x - cx;
  float py = v.y - cy;

  float dx = abs(px) - bx;
  float dy = abs(py) - by;

  Vec2f maxVec(std::max(dx, 0.0f),
	       std::max(dy, 0.0f));
    
  float dist = maxVec.len() + std::min(std::max(dx, dy), 0.0f);

  return dist;  
}

float WorldQuad::distToWallPolygon(const Vec2f& v) const {
  // using "Polygon - exact" from https://iquilezles.org/www/articles/distfunctions2d/distfunctions2d.htm
  float d = (v - m_corners[0]).lenSqr();
  int s = 1;

  for (int i = 0; i < 4; i++) {
    int j = (i + 3) % 4;
    Vec2f e = m_corners[j] - m_corners[i];
    Vec2f w = v - m_corners[i];
    Vec2f b = w - e * fclamp(w.dot(e) / e.lenSqr(), 0.0f, 1.0f);
    d = std::min(d, b.lenSqr());

    bool c0 = v.y >= m_corners[i].y;
    bool c1 = v.y <  m_corners[j].y;
    bool c2 = e.x*w.y > e.y * w.x;

    if ((c0 && c1 && c2) ||
	((!c0) && (!c1) && (!c2))) {
      s *= -1;
    }
  }

  float dist = float(s * sqrt(d));
  return dist;
}

float WorldQuad::distanceToWall(const Vec2f& v) const {
  if (m_bIsAxisAlignedRectangle) {
    return distToWallAABB(v);
  } else {
    return distToWallPolygon(v);
  }  
}

bool WorldQuad::pointInside(const Vec2f& v) const {
  return distanceToWall(v) < 0.0f;
}

Vec2f WorldQuad::closestPointAABB(const Vec2f& v) const {
  float cx = (xMax + xMin) * 0.5f;
  float cy = (yMax + yMin) * 0.5f;
  float bx = xMax - cx;
  float by = yMax - cy;

  // find x projection

  float px = v.x;
  float py = v.y;

  float xpx = px;
  float xpy = py;
  
  if (v.x < cx) {
    xpx = cx - bx;
  } else {
    xpx = cx + bx;
  }

  float ypx = px;
  float ypy = py;

  if (v.y < cy) {
    ypy = cy - by;
  } else {
    ypy = cy + by;
  }

  Vec2f projX(xpx, xpy);
  Vec2f projY(ypx, ypy);

  float projXd = (projX - v).len();
  float projYd = (projY - v).len();

  if (projXd < projYd) {
    return projX;
  } else {
    return projY;
  }
}

Vec2f WorldQuad::closestPointPolygon(const Vec2f& v) const {
  float d = (v - m_corners[0]).lenSqr();
  Vec2f bestPoint = m_corners[0];

  for (int i = 0; i < 4; i++) {
    int j = (i + 3) % 4;
    Vec2f e = m_corners[j] - m_corners[i];
    Vec2f w = v - m_corners[i];
    Vec2f b = w - e * fclamp(w.dot(e) / e.lenSqr(), 0.0f, 1.0f);

    float bLenSqr = b.lenSqr();
    if (bLenSqr < d) {
      d = bLenSqr;
      bestPoint = v - b;
    }
  }

  return bestPoint;
}

Vec2f WorldQuad::closestPoint(const Vec2f& v) const {
  if (m_bIsAxisAlignedRectangle) {
    return closestPointAABB(v);
  } else {
    return closestPointPolygon(v);
  }
}

WorldQuad WorldQuad::MakeFromAABB(Vec2f ul, Vec2f lr, olc::Decal* inDecal, olc::Pixel inColor, int inLayerIndex)
{
  float left = std::min(ul.x, lr.x);
  float right = std::max(ul.x, lr.x);
  float upper = std::max(ul.y, lr.y);
  float lower = std::min(ul.y, lr.y);
  
  return WorldQuad(Vec2f(left, upper), Vec2f(right, upper),
		   Vec2f(right, lower), Vec2f(left, lower),
		   inDecal, inColor, inLayerIndex);
}

bool WorldQuad::constrainsParticle(const Vec2f& p, float r) const
{
  return distanceToWall(p) < r;
}

Vec2f WorldQuad::pushOut(const Vec2f& p, float r) const
{
  float distToEdge = distanceToWall(p);
  Vec2f pointOnEdge = closestPoint(p);

  Vec2f outVec = p - pointOnEdge;
  if (distToEdge < 0.0f) {
    outVec = outVec * -1.0f;
  }

  Vec2f clearVec = pointOnEdge + outVec * r;
  return clearVec;
}
