#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct AxisStyle : Style
	{
		// Properties
		bool	centered	{ false };

		AxisStyle() :
			Style	{ Color(255, 255, 255) }
		{
		}
		AxisStyle(Color color, bool centered = false) :
			Style	{ color },
			centered{ centered }
		{
		}

	} ASTYLE_PRESETS[]{
		AxisStyle(),
		AxisStyle(Color(0, 0, 0))
	};
}