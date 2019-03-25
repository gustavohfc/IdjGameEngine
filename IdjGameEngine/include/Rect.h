#pragma once
#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    bool Contains(Vec2 p);
};
