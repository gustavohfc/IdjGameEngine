#include "pch.h"
#include "Rect.h"


Rect::Rect():
    x(0),
    y(0),
    w(0),
    h(0) {}


Rect::Rect(float x, float y, float w, float h):
    x(x),
    y(y),
    w(w),
    h(h) {}


void Rect::Reset() {
    x = 0;
    y = 0;
    w = 0;
    h = 0;
}


Vec2 Rect::GetCenter() const {
    return {
        x + (w / 2),
        y + (h / 2)
    };
}


void Rect::SetCenter(float centerX, float centerY) {
    x = centerX - (w / 2);
    y = centerY - (h / 2);
}


float Rect::Dist(const Rect& other) const {
    return this->GetCenter().Dist(other.GetCenter());
}


float Rect::Dist(const Vec2& vec) const {
    return this->GetCenter().Dist(vec);
}


bool Rect::Contains(const Vec2& v) const {
    return
        v.x >= x &&
        v.y >= y &&
        v.x <= x + w &&
        v.y <= y + h;
}


bool Rect::Move(float dt, int speedAbs, const Vec2& dest) {
    Vec2 speed = Vec2::GetUnitVectorBetweenTwoPoints(this->GetCenter(), dest) * dt * speedAbs;

    auto distance = this->Dist(dest);
    auto displacement = speed.Abs();

    if (displacement >= distance) {
        this->SetCenter(dest.x, dest.y);
        return true;
    }

    auto center = this->GetCenter();
    this->SetCenter(center.x + speed.x, center.y + speed.y);
    return false;
}
