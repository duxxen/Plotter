#pragma once
#include "../common.hpp"

#define DEFAULT_STYLE 0

namespace Plotter
{
	struct Style
	{
		// Style Properties
		Color color;

		Style(Color color) :
			color{ color }
		{
		}
	};
}