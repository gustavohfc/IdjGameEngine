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
		abs != 0 ? x / abs : 0,
		abs != 0 ? y / abs : 0
	};
}


Vec2 Vec2::GetRotated(float angle) const {
	auto sin = std::sin(angle);
	auto cos = std::cos(angle);

	return {
		x * cos - y * sin,
		y * cos + x * sin
	};
}


float Vec2::Dist(const Vec2& other) const {
	return (*this - other).Abs();
}


Vec2 Vec2::GetVectorBetweenTwoPoints(Vec2 A, Vec2 B) {
	return B - A;
}


Vec2 Vec2::GetUnitVectorBetweenTwoPoints(Vec2 A, Vec2 B) {
	return GetVectorBetweenTwoPoints(A, B).Norm();
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


Vec2& Vec2::operator+=(const Vec2& other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}
