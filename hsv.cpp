#include <cassert>
#include "olcPixelGameEngine.h"
#include "hsv.h"

olc::Pixel HSVToRGB(float h, float s, float v)
{
  //printf("H: %f S: %f V: %f\n", h, s, v);
  while (h < 0) {
    h += 360;
  }
  while (h >= 360) {
    h -= 360;
  }

  assert(0 <= s);
  assert(s <= 1);

  assert(0 <= v);
  assert(v <= 1);

  float c = v * s;
  float hd60 = h / 60.0f;
  while (hd60 >= 2) {
    hd60 -= 2;
  }
  while (hd60 < 0) {
    hd60 += 2;
  }
    
  //float x = c * (1 - abs(hd60 - 1));
  float x = c * (1 - fabs(fmod(h/60.0f, 2) - 1));
  float m = v - c;

  float r1, g1, b1;

  if (h < 60) {
    r1 = c;
    g1 = x;
    b1 = 0;
  } else if (h < 120) {
    r1 = x;
    g1 = c;
    b1 = 0;
  } else if (h < 180) {
    r1 = 0;
    g1 = c;
    b1 = x;
  } else if (h < 240) {
    r1 = 0;
    g1 = x;
    b1 = c;
  } else if (h < 300) {
    r1 = x;
    g1 = 0;
    b1 = c;
  } else if (h < 360) {
    r1 = c;
    g1 = 0;
    b1 = x;
  } else {
    assert(false);
  }

  int r = int((r1 + m) * 255);
  int g = int((g1 + m) * 255);
  int b = int((b1 + m) * 255);

  //printf("R: %d G: %d B: %d\n", r, g, b);

  return olc::Pixel(r, g, b);
}
