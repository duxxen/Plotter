#pragma once
#include "../color.hpp"
#include "../vec2.hpp"

namespace System
{
	struct Vertex
	{
		Color	color;
		Vec2	position;

		Vertex();
		Vertex(const Vec2& position);
		Vertex(const Vec2& position, const Color& color);
	};

	Vertex::Vertex()
	{
	}

	Vertex::Vertex(const Vec2& position) :
		position{ position }
	{
	}

	Vertex::Vertex(const Vec2& position, const Color& color) :
		position{ position },
		color	{ color }
	{
	}
}