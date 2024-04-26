#pragma once
#include "../common.hpp"

#define STYLE_DEFAULT 0

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

#include "axis-style.hpp"
#include "cursor-style.hpp"
#include "graph-style.hpp"
#include "grid-style.hpp"
#include "plot-style.hpp"
#include "text-style.hpp"