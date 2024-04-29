#pragma once
#include "../plot-object.hpp"
#include "../../style/cursor-style.hpp"

#define MOUSE_CURSOR	0
#define LEFT_CURSOR		1
#define RIGHT_CURSOR	2

namespace Plotter
{
	class Cursor : public PlotObject
	{
		friend class Plot;
		friend void render();
	public:

		Cursor(Plot* layout, CursorStyle style);

	private:

		void recompute() override;
		void onStyleChanged() override;

		CursorStyle	style;

		Values		position;
		Vertices	lines;
	};
}