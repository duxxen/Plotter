#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <vector>
#include <string>

#include "../utility/to-string.hpp"

namespace Plotter
{
	using std::string;
	using std::vector;
	using std::function;
	
	using sf::Color;

	typedef	sf::Vector2f			Coords;
	typedef	sf::Vector2f			Values;
	typedef function<float(float)>	Func;

	static inline const Color DEFAULT_COLORS_ARRAY[] = {
		Color::Red,
		Color::Green,
		Color::Blue,
		Color::Cyan,
		Color::Magenta,
		Color::Yellow
	};

	static inline const uint16_t	DEFAULT_WIN_WIDTH			{ 640U };
	static inline const uint16_t	DEFAULT_WIN_HEIGHT			{ 480U };
	static inline const uint16_t	DEFAULT_WIN_INDENT			{ 15U };
	static inline const uint16_t	DEFAULT_FRAME_INDENT_LEFT	{ 40U };
	static inline const uint16_t	DEFAULT_TEXT_INDENT			{ 5U };
	static inline const uint32_t	DEFAULT_POINT_COUNT			{ 32000U };
}