#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct LineStyle : Style
	{
		uint8_t vAlpha	{ 64U };

		LineStyle() :
			Style	{ Color(255, 0, 0) }
		{
		}
		LineStyle(Color color, uint8_t valpha = 64U) :
			Style	{ color },
			vAlpha	{ valpha }
		{
		}

	} LSTYLE_PRESETS[]{
		LineStyle(Color(255, 0, 0)),
		LineStyle(Color(0, 255, 0)),
		LineStyle(Color(0, 0, 255)),
		LineStyle(Color(0, 255, 0)),
		LineStyle(Color(0, 255, 0)),
		LineStyle(Color(0, 255, 0))
	};
}