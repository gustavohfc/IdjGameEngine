#include "pch.h"
#include "Vec2.h"


Vec2::Vec2():
    x(0),
    y(0) {}


Vec2::Vec2(float x, float y):
    x(x),
    y(y) {}


float Vec2::Abs() const {
    return sqrt(x * x + y * y);
}


float Vec2::Angle() const {
    return atan2(y, x);
}


Vec2 Vec2::Norm() const {
    auto abs = Abs();
    return {
        x / abs,
        y / abs
    };
}

void Vec2::Rotate(float angle) {
    auto sin = std::sin(angle);
    auto cos = std::cos(angle);
    x = x * cos - y * sin;
    y = y * cos - x * sin;
}


float Vec2::Dist(const Vec2& other) const {
    return (*this - other).Abs();
}


Vec2 Vec2::operator+(const Vec2& other) const {
    return {
        x + other.x,
        y + other.y
    };
}


Vec2 Vec2::operator-(const Vec2& other) const {
    return {
        x - other.x,
        y - other.y
    };
}


Vec2 Vec2::operator*(const float scalar) const {
    return {
        x * scalar,
        y * scalar
    };
}
