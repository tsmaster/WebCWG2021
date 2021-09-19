#ifndef BDG_MATH_H
#define BDG_MATH_H

float degToRad(float degrees);
float radToDeg(float radians);

const float PI = 3.141592654f;
const float TAU = PI * 2.0f;

float fmap(float val, float inMin, float inMax, float outMin, float outMax);

// returns value in [min, max)
int clamp(int val, int min, int max);

class Vec2f
{
 public:
  Vec2f(float x, float y);

  float x;
  float y;
};

class Vec2i
{
 public:
  Vec2i(int ix, int iy) { x=ix; y=iy; }
  Vec2i() {x=0; y=0;}

  int x;
  int y;

  bool lessThan(const Vec2i& other) const;
  
  bool operator < (const Vec2i &other) const { return lessThan(other); }

  bool operator == (const Vec2i &other) const { return ((x == other.x) &&
							(y == other.y)); }

  Vec2i operator+ (const Vec2i& other) const { return Vec2i(x + other.x,
							     y + other.y); }

  float distEuclid(const Vec2i& other) const;

  int distManhattan(const Vec2i& other) const;
};

#endif //BDG_MATH_H



