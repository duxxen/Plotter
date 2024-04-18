#pragma once
#include "../common.hpp"

namespace Plotter
{
	inline static struct GridStyle : Style
	{
		// Properties
		size_t	countX	{ 10 };
		size_t	countY	{ 10 };

		GridStyle() :
			Style		{ Color(64, 64, 64) }
		{
		}
		GridStyle(size_t countX, size_t countY, Color color) :
			Style	{ color },
			countX	{ countX },
			countY	{ countY }
		{
		}

	} GSTYLE_PRESETS[]{
		GridStyle()
	};
}