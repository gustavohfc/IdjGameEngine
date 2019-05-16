#pragma once

class Vec2 {
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);

	float Abs() const;
	float Angle() const;
	Vec2 Norm() const;
	Vec2 GetRotated(float angle) const;
	float Dist(const Vec2& other) const;

	/**
	 * \brief Calculates the vector connecting the point A to B.
	 */
	static Vec2 GetVectorBetweenTwoPoints(Vec2 A, Vec2 B);

	/**
	  * \brief Calculates the unit vector from the point A to B.
	  */
	static Vec2 GetUnitVectorBetweenTwoPoints(Vec2 A, Vec2 B);

	// Operator overloading
	Vec2 operator+(const Vec2& other) const;
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator*(float scalar) const;
	Vec2& operator+=(const Vec2& other);
};
