#pragma once

class Vec2 {
public:
    float x, y;

    Vec2();
    Vec2(float x, float y);

    float Abs() const;
    float Angle() const;
    Vec2 Norm() const;
    void Rotate(float angle);
    float Dist(const Vec2& other) const;

    // Operator overloading
    Vec2 operator+(const Vec2& other) const;
    Vec2 operator-(const Vec2& other) const;
    Vec2 operator*(float scalar) const;
};
