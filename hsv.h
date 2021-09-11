#ifndef HSV_H
#define HSV_H

#include "olcPixelGameEngine.h"

olc::Pixel HSVToRGB(float h, float s, float v);

static const olc::Pixel HSV_BLACK = HSVToRGB(0, 0, 0);


#endif //HSV_H


