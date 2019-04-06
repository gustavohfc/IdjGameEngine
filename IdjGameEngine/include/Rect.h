#pragma once
#include "Vec2.h"

class Rect {
public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);

    void Reset();
    Vec2 GetCenter() const;
    void SetCenter(float centerX, float centerY);
    float Dist(const Rect& other) const;
    bool Contains(const Vec2& v) const;
};
