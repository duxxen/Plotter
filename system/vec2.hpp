#pragma once

namespace System
{
	struct Vec2
	{
		Vec2();
		Vec2(float x, float y);

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

}