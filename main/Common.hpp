#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <stdint.h>
#include <set>

namespace Plotter
{
	using std::vector;
	using std::string;

	using Vec2 = sf::Vector2f;
	using Rect = sf::FloatRect;
	using Color = sf::Color;
	using Window = sf::RenderWindow;
	using Vertex = sf::Vertex;
	using Vertices = sf::VertexArray;

	using Func = std::function<float(float)>;

	static inline uint32_t	DEFAULT_WIN_WIDTH		{ 640 };
	static inline uint32_t	DEFAULT_WIN_HEIGHT		{ 480 };
	static inline uint32_t	DEFAULT_WIN_INDENT		{ 40 };
	static inline uint32_t	DEFAULT_TEXT_INDENT		{ 8 };
	static inline uint32_t	DEFAULT_POINT_COUNT		{ 4000 };

	enum class PlotErrors
	{
		OK,
		INVALID_SIZE,
		INVALID_INDEX,
		INVALID_RESULT
	};
}
