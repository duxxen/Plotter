#pragma once
#include <assert.h>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

namespace Plotter
{
#define AUTO 1

	static inline uint32_t	DEFAULT_WIN_WIDTH		{ 640 };
	static inline uint32_t	DEFAULT_WIN_HEIGHT		{ 480 };
	static inline uint32_t	DEFAULT_WIN_INDENT		{ 10 };
	static inline uint32_t	DEFAULT_TEXT_INDENT		{ 10 };
	static inline uint32_t	DEFAULT_POINT_COUNT		{ 4000 };

	static inline uint8_t  DEFAULT_VOL_TRANSPARENCY	{ 64 };

	enum class PlotErrors
	{
		OK,
		INVALID_SIZE,
		INVALID_RESULT
	};
}
