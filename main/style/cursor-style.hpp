#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct CursorStyle : Style
	{
		bool	showTitle	{ true };

		CursorStyle() :
			Style		{ Color(128, 128, 128) }
		{
		}

		CursorStyle(Color color, bool showTitle) :
			Style		{ color },
			showTitle	{ showTitle }
		{
		}

	} CSTYLE_PRESETS[] = {
		CursorStyle(),
		CursorStyle(Color(64, 64, 64), true)
	};
}