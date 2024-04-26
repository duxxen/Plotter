#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct GraphStyle : Style
	{
		// Bit flags
		enum Flags
		{
			SHOW_NONE = 0,
			SHOW_LINE = 1,
			SHOW_VOLUME = SHOW_LINE << 1,
			SHOW_ALL = SHOW_LINE | SHOW_VOLUME
		};

		// Plot properties
		uint8_t			vAlpha	{ 64U };
		Flags			show	{ SHOW_ALL };
		PrimitiveType	type	{ PrimitiveType::Lines };

		GraphStyle() :
			Style	{ Color(255, 0, 0) }
		{
		}
		GraphStyle(Flags flags) :
			Style	{ Color(255, 0, 0) },
			show	{ flags }
		{
		}
		GraphStyle(Color color, Flags flags = SHOW_ALL, uint8_t valpha = 64U) :
			Style	{ color },
			show	{ flags },
			vAlpha	{ valpha }
		{
		}

	} LSTYLE_PRESETS[]{
		GraphStyle(Color(255, 0, 0)),
		GraphStyle(Color(0, 255, 0)),
		GraphStyle(Color(0, 0, 255)),
		GraphStyle(Color(255, 255, 0)),
		GraphStyle(Color(255, 0, 255)),
		GraphStyle(Color(0, 255, 255)),
	};
}