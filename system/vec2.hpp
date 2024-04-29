#pragma once
#include "math.h"

namespace System
{
	struct Vec2
	{
		Vec2();
		Vec2(float x, float y);

		float abs() const;
		Vec2 normalized() const;

		float x;
		float y;
	};

	Vec2 operator+(Vec2 v1, Vec2 v2) {
		return Vec2(v1.x + v2.x, v1.y + v2.y);
	}

	Vec2 operator-(Vec2 v1, Vec2 v2) {
		return Vec2(v1.x - v2.x, v1.y - v2.y);
	}

	bool operator==(Vec2 v1, Vec2 v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}

	bool operator!=(Vec2 v1, Vec2 v2) {
		return !(v1 == v2);
	}

	Vec2::Vec2() :
		x{ 0 },
		y{ 0 }
	{
	}

	Vec2::Vec2(float x, float y) :
		x{ x },
		y{ y }
	{
	}

	inline float Vec2::abs() const
	{
		return sqrt(x * x + y * y);
	}

	inline Vec2 Vec2::normalized() const
	{
		auto a = abs();
		return Vec2(x / a, y / a);
	}

}