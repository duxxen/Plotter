#pragma once
#include "plot-object.hpp"

namespace Plotter
{
	class Cursor : public PlotObject
	{
		friend class Plot;
	public:

		Cursor(Plot* layout);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		CursorStyle style;

		// Render Objects
		Vertices	lines;
	};
}