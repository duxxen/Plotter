#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct LineStyle : Style
	{
		// Bit flags
		enum Flags
		{
			SHOW_NONE = 0,
			SHOW_LINE = 1,
			SHOW_VOLUME = SHOW_LINE << 1,
			SHOW_ALL = SHOW_LINE | SHOW_VOLUME
		};

		// Volume Transparency
		uint8_t vAlpha	{ 64U };

		// Show flags
		Flags	show	{ SHOW_ALL };

		LineStyle() :
			Style	{ Color(255, 0, 0) }
		{
		}
		LineStyle(Flags flags) :
			Style	{ Color(255, 0, 0) },
			show	{ flags }
		{
		}
		LineStyle(Color color, Flags flags = SHOW_ALL, uint8_t valpha = 64U) :
			Style	{ color },
			show	{ flags },
			vAlpha	{ valpha }
		{
		}

	} LSTYLE_PRESETS[]{
		LineStyle(Color(255, 0, 0)),
		LineStyle(Color(0, 255, 0)),
		LineStyle(Color(0, 0, 255)),
		LineStyle(Color(255, 255, 0)),
		LineStyle(Color(255, 0, 255)),
		LineStyle(Color(0, 255, 255)),
	};
}