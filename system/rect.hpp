#pragma once
#include "vec2.hpp"

namespace System
{
	struct Rect
	{
		Rect();
		Rect(Vec2 position, Vec2 size);
		Rect(float left, float top, float width, float height);

		Vec2 position() const;
		Vec2 size() const;

		float right() const;
		float bottom() const;

		Vec2 center() const;
		Vec2 rightBottom() const;

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

	inline Vec2 Rect::position() const
	{
		return Vec2(left, top);
	}

	inline Vec2 Rect::size() const
	{
		return Vec2(width, height);
	}

	inline float Rect::right() const
	{
		return left + width;
	}

	inline float Rect::bottom() const
	{
		return top + height;
	}

	inline Vec2 Rect::center() const
	{
		return Vec2(left + width / 2, top + height / 2);
	}

	inline Vec2 Rect::rightBottom() const
	{
		return Vec2(right(), bottom());
	}
}