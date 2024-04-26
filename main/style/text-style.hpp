#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct TextStyle : Style
	{
		// Text properties
		string		fontPath	{ "src/assets/arial.ttf" };
		uint32_t	indent		{ DEFAULT_TEXT_INDENT };
		uint32_t	charSize	{ 10 };

		TextStyle() :
			Style	{ Color(255, 255, 255) }
		{
		}
		TextStyle(Color color) :
			Style	{ color }
		{
		}
		TextStyle(string font_path, uint32_t indent, uint32_t char_size, Color color) :
			Style	{ color },
			fontPath{ font_path },
			indent	{ indent },
			charSize{ char_size }
		{
		}

	} TSTYLE_PRESETS[]{
		TextStyle(),
		TextStyle(Color(0, 0, 0))
	};
}