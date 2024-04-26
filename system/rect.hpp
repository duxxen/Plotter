#pragma once
#include "vec2.hpp"

namespace System
{
	struct Rect
	{
		Rect();
		Rect(Vec2 position, Vec2 size);
		Rect(float left, float top, float width, float height);

		Vec2 position();
		Vec2 size();

		float right();
		float bottom();

		Vec2 center();
		Vec2 rightBottom();

		float left	{ 0 };
		float top	{ 0 };
		float width	{ 0 };
		float height{ 0 };
	};

	Rect::Rect()
	{
	}

	Rect::Rect(Vec2 position, Vec2 size) :
		left	{ position.x },
		top		{ position.y },
		width	{ size.x },
		height	{ size.y }
	{
	}

	Rect::Rect(float left, float top, float width, float height) :
		left	{ left },
		top		{ top },
		width	{ width },
		height	{ height }
	{
	}

	inline Vec2 Rect::position()
	{
		return Vec2(left, top);
	}

	inline Vec2 Rect::size()
	{
		return Vec2(width, height);
	}

	inline float Rect::right()
	{
		return left + width;
	}

	inline float Rect::bottom()
	{
		return top + height;
	}

	inline Vec2 Rect::center()
	{
		return Vec2(left + width / 2, top + height / 2);
	}

	inline Vec2 Rect::rightBottom()
	{
		return Vec2(right(), bottom());
	}
}