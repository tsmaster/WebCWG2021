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

bool WorldQuad::raycast(const Vec2f& rayOrigin,
			const Vec2f& rayDirection,
			Vec2f& outIntersection) const
{
  if (m_bIsAxisAlignedRectangle) {
    return raycastAABB(rayOrigin, rayDirection, outIntersection);
  } else {
    return raycastPolygon(rayOrigin, rayDirection, outIntersection);
  }  
}

bool WorldQuad::raycastAABB(const Vec2f& rayOrigin,
			    const Vec2f& rayDirection,
			    Vec2f& outIntersection) const
{
  // adapted from https://noonat.github.io/intersect/#aabb-vs-segment
  
  bool hasIntersectionX = true;
  bool hasIntersectionY = true;

  float xMid = (xMin + xMax) * 0.5f;
  float yMid = (yMin + yMax) * 0.5f;

  float xHalf = xMax - xMid;
  float yHalf = yMax - yMid;
  
  if (rayDirection.x == 0.0f) {
    hasIntersectionX = false;
  }
  if (rayDirection.y == 0.0f) {
    hasIntersectionY = false;
  }

  float nearTimeX, nearTimeY, farTimeX, farTimeY;

  if (hasIntersectionX) {
    float scaleX = 1.0 / rayDirection.x;
    float signX = scaleX < 0.0f ? -1.0f : 1.0f;
    nearTimeX = (xMid - signX * xHalf - rayOrigin.x) * scaleX;
    farTimeX = (xMid + signX * xHalf - rayOrigin.x) * scaleX;
  }

  if (hasIntersectionY) {
    float scaleY = 1.0 / rayDirection.y;
    float signY = scaleY < 0.0f ? -1.0f : 1.0f;
    nearTimeY = (yMid - signY * yHalf - rayOrigin.y) * scaleY;
    farTimeY = (yMid + signY * yHalf - rayOrigin.y) * scaleY;
  }

  //printf("hix %d hiy %d\n", hasIntersectionX, hasIntersectionY);
  //printf("ntx %f ftx %f\n", nearTimeX, farTimeX);
  //printf("nty %f fty %f\n", nearTimeY, farTimeY);

  if ((hasIntersectionX && hasIntersectionY) &&
      (nearTimeX > farTimeY || nearTimeY > farTimeX)) {
    return false;
  }

  float nearTime, farTime;

  if (hasIntersectionX) {
    if (hasIntersectionY) {
      nearTime = nearTimeX > nearTimeY ? nearTimeX : nearTimeY;
      farTime = farTimeX < farTimeY ? farTimeX : farTimeY;
    } else {
      // no y intersection

      if ((rayOrigin.y < yMin) || (rayOrigin.y > yMax)) {
	// outside in y
	return false;
      }      
      nearTime = nearTimeX;
      farTime = farTimeX;
    }
  } else {
    // no x intersection

    if ((rayOrigin.x < xMin) || (rayOrigin.x > xMax)) {
      // outside in x
      return false;
    }      
    nearTime = nearTimeY;
    farTime = farTimeY;
  }

  if (nearTime >= 1 || farTime <= 0) {
    return false;
  }

  if (nearTime < 0) {
    outIntersection = rayOrigin;
    return true;
  }

  outIntersection = rayOrigin + rayDirection * nearTime;
  return true;
}

/*
bool WorldQuad::raycastAABB(const Vec2f& rayOrigin,
			const Vec2f& rayDirection,
			Vec2f& outIntersection) const
{
  // from https://github.com/erich666/GraphicsGems/blob/master/gems/RayBox.c

  enum Quadrants {
    LEFT,
    MIDDLE,
    RIGHT};

  bool inside = true;
  int quadrant[2];
  float maxT[2];
  float candidatePlane[2];
  float rayOriginArray[] = {rayOrigin.x, rayOrigin.y};
  float rayDirectionArray[] = {rayDirection.x, rayDirection.y};
  float boxMin[] = {xMin, yMin};
  float boxMax[] = {xMax, yMax};
  float coord[2];

  printf("top of raycast AABB\n");
  for (int i = 0; i < 2; ++i) {
    printf("testing index %d\n", i);
    if (rayOriginArray[i] < boxMin[i]) {
      printf("origin[%d]: %f boxMin[%d]: %f\n", i, rayOriginArray[i], i, boxMin[i]);
      quadrant[i] = Quadrants::LEFT;
      printf("left\n");
      candidatePlane[i] = boxMin[i];
      inside = false;
    } else if (rayOriginArray[i] > boxMax[i]) {
      printf("origin[%d]: %f boxMax[%d]: %f\n", i, rayOriginArray[i], i, boxMax[i]);
      quadrant[i] = Quadrants::RIGHT;
      printf("right\n");
      candidatePlane[i] = boxMax[i];
      inside = false;
    } else {
      quadrant[i] = Quadrants::MIDDLE;
      printf("middle\n");
    }
  }

  if (inside) {
    printf("origin inside\n");
    outIntersection = rayOrigin;
    return true;
  }

  // calculate T distances to candidate planes
  for (int i = 0; i < 2; ++i) {
    if (quadrant[i] != Quadrants::MIDDLE && rayDirectionArray[i] != 0.0f) {
      maxT[i] = (candidatePlane[i] - rayOriginArray[i]) / rayDirectionArray[i];
    } else {
      maxT[i] = -1;
    }
    printf("maxT[%d]: %f\n", i, maxT[i]);
  }

  // get largest of the maxTs for final choice of intersection

  int whichPlane = 0;
  for (int i = 1; i < 2; ++i) {
    if (maxT[whichPlane] < maxT[i]) {
      whichPlane = i;
    }
  }

  printf("which plane?: %d\n", whichPlane);

  // check final candidate actually inside box
  if (maxT[whichPlane] < 0.0f) {
    printf("maxT[%d]: %f\n", whichPlane, maxT[whichPlane]);
    printf("no intersection\n");
    printf("---\n");
    return false;
  }

  for (int i = 0; i < 2; ++i) {
    printf("index: %d\n", i);
    if (whichPlane != i) {
      coord[i] = rayOriginArray[i] + maxT[whichPlane] * rayDirectionArray[i];
      if (coord[i] < boxMin[i] || coord[i] > boxMax[i]) {
	printf("c[%d]: %f boxMin %f boxMax %f\nno collision\n", i, coord[i], boxMin[i], boxMax[i]);
	printf("---\n");
	return false;
      }
    } else {
      coord[i] = candidatePlane[i];
      printf("c[%d]: %f boxMin %f boxMax %f\ninside\n", i, coord[i], boxMin[i], boxMax[i]);
    }    
  }

  printf("coords <%f %f>\n", coord[0], coord[1]);

  outIntersection = Vec2f(coord[0], coord[1]);
  return true;
}
*/

bool lineIntersect(const Vec2f& p, // first point
		   const Vec2f& r, // DIRECTION from p
		   const Vec2f& q, // second point
		   const Vec2f& s, // direction from q
		   Vec2f& outIntersection)
{
  // based on https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
  // and https://ideone.com/PnPJgb
  
  Vec2f cmp = q - p;
 
  float cmpXr = cmp.x * r.y - cmp.y * r.x;
  float cmpXs = cmp.x * s.y - cmp.y * s.x;
  float rXs = r.x * s.y - r.y * s.x;
 
  if (cmpXr == 0.0f) {
    // Lines are collinear, and so intersect if they have any overlap

    if (((q.x - p.x < 0.0f) != (q.x - (p.x + r.x) < 0.0f))
	|| ((q.y - p.y < 0.0f) != (q.y - (p.y + r.y) < 0.0f))) {
      outIntersection = p;
      return true;
    } else {
      return false;
    }
  }
  
  if (rXs == 0.0f) {
    return false; // Lines are parallel.
  }
 
  float rXsr = 1.0f / rXs;
  float t = cmpXs * rXsr;
  float u = cmpXr * rXsr;

  if ((t >= 0.0f) && (t <= 1.0f) && (u >= 0.0f) && (u <= 1.0f)) {
    outIntersection = p + r * t;
    return true;
  }
  return false;  
}

bool WorldQuad::raycastPolygon(const Vec2f& rayOrigin,
			       const Vec2f& rayDirection,
			       Vec2f& outIntersection) const
{
  if (pointInside(rayOrigin)) {
    outIntersection = rayOrigin;
    return true;
  }

  for (int i = 0; i < m_corners.size(); ++i) {
    int j = (i + (m_corners.size() - 1)) % m_corners.size();
    const Vec2f& e0 = m_corners[i];
    const Vec2f& e1 = m_corners[j];

    Vec2f intersection(0, 0);
    
    if (lineIntersect(rayOrigin, rayDirection,
		      e0, e1-e0, intersection)) {
      outIntersection = intersection;
      return true;
    }
  }

  return false;
}

void WorldQuad::print() const
{
  if (m_bIsAxisAlignedRectangle) {
    printf("wall xMin %f xMax %f yMin %f yMax %f\n", xMin, xMax, yMin, yMax);
  } else {
    printf("wall ");
    for (const Vec2f& c : m_corners) {
      printf("<%f %f> ", c.x, c.y);
    }
    printf("\n");
  }
}
