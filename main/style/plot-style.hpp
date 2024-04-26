#pragma once
#include "style.hpp"

namespace Plotter
{
	inline static struct PlotStyle : Style
	{
		// Bit flag
		enum Flags
		{
			SHOW_NONE = 0,
			SHOW_GRID = 1,
			SHOW_AXIS = SHOW_GRID << 1,
			SHOW_CURSOR = SHOW_GRID << 2,
			SHOW_ALL = SHOW_GRID | SHOW_AXIS | SHOW_CURSOR
		};

		// Window properties
		Vec2		size		{ Vec2(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT) };
		Vec2		indent		{ Vec2(DEFAULT_WIN_INDENT, DEFAULT_WIN_INDENT) };
		string		name		{ "Plot" };

		// Flags
		Flags		show		{ SHOW_ALL };
		
		// Point count
		uint32_t	pointCount	{ DEFAULT_POINT_COUNT };
		
		PlotStyle() :
			Style(Color(0, 0, 0))
		{
		}
		PlotStyle(Flags flags) :
			Style	{ Color(0, 0, 0) },
			show	{flags}
		{
		}

		PlotStyle(Color bg) :
			Style	{ bg }
		{
		}
		PlotStyle(Flags flags, Color bg) :
			Style	{ bg },
			show	{ flags }
		{
		}

	} PSTYLE_PRESETS[]{
		PlotStyle(),
		PlotStyle(Color(255, 255, 255))
	};
}