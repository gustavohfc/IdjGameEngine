#include "pch.h"
#include "Rect.h"


Rect::Rect() :
    x(0),
    y(0),
    w(0),
    h(0) {}


Rect::Rect(float x, float y, float w, float h) :
    x(x),
    y(y),
    w(w),
    h(h) {}


bool Rect::Contains(Vec2 v) {
    return v.x >= x &&
        v.y >= y &&
        v.x <= x + w &&
        v.y <= y + h;
}