#pragma once
#include <string>
#include <vector>
#include <functional>
#include "../system/system.hpp"

namespace Plotter
{
	using std::string;
	using std::vector;
	using std::function;

	using namespace System;

	typedef Vec2					Coords;
	typedef Vec2					Values;
	typedef Rect					RectCoords;
	typedef Rect					RectValues;
	typedef function<float(float)>	Func;

	static inline uint32_t	DEFAULT_WIN_WIDTH		{ 640 };
	static inline uint32_t	DEFAULT_WIN_HEIGHT		{ 480 };
	static inline uint32_t	DEFAULT_WIN_INDENT		{ 40 };
	static inline uint32_t	DEFAULT_TEXT_INDENT		{ 5 };
	static inline uint32_t	DEFAULT_POINT_COUNT		{ 4000 };

	static inline uint8_t	DEFAULT_VOL_TRANSPARENCY{ 64 };

	enum class PlotErrors
	{
		OK,
		INVALID_SIZE,
		INVALID_RESULT
	};
}
