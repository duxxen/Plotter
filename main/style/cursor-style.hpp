#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct CursorStyle : Style
	{
		CursorStyle() :
			Style{ Color(128, 128, 128) }
		{
		}

		CursorStyle(Color color) :
			Style(color)
		{
		}
	
	} CSTYLE_PRESETS[] = {
		CursorStyle(),
		CursorStyle(Color(64, 64, 64))
	};
}