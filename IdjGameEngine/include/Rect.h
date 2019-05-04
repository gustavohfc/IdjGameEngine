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
    float Dist(const Vec2& vec) const;
    bool Contains(const Vec2& v) const;

    /**
     * \brief Moves the Rect in the direction of dest in a constant speed.
     * \return Returns true if the rect arrived in the destination.
     */
    bool Move(const Vec2& speed, const Vec2& dest);
};
