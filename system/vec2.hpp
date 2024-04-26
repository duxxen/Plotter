#pragma once

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