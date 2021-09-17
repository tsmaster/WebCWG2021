#ifndef BDG_MATH_H
#define BDG_MATH_H

float degToRad(float degrees);
float radToDeg(float radians);

const float PI = 3.141592654f;
const float TAU = PI * 2.0f;

float fmap(float val, float inMin, float inMax, float outMin, float outMax);


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

  int x;
  int y;
};

#endif //BDG_MATH_H



