#pragma once
#include "../plot-object.hpp"
#include "../../style/cursor-style.hpp"

namespace Plotter
{
	class Cursor : public PlotObject
	{
		friend class Plot;

	public:

		Cursor(Plot* layout, CursorStyle style);

	private:

		void recompute() override;
		void onStyleChanged() override;

		Values		position;
		Vertices	lines;
	};
}