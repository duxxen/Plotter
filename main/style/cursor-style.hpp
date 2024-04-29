#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct CursorStyle : Style
	{
		enum Flags
		{
			SHOW_NONE = 0,
			SHOW_LINES = 1,
			SHOW_TITLE = SHOW_LINES << 1,
			SHOW_ALL = SHOW_LINES | SHOW_TITLE
		};

		// Cursor Properties

		Flags	show	{ SHOW_ALL };

		CursorStyle() :
			Style		{ Color(128, 128, 128) }
		{
		}

		CursorStyle(Color color, Flags flags) :
			Style		{ color },
			show		{ flags }
		{
		}

	} CSTYLE_PRESETS[] = {
		CursorStyle(),
		CursorStyle(Color(64, 64, 64), CursorStyle::SHOW_ALL)
	};
}