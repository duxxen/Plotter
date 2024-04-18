#pragma once
#include "plot-object.hpp"

namespace Plotter
{
	class Axis : public PlotObject
	{
		friend class Plot;
	public:

		Axis(Plot* layout);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		AxisStyle	style;

		// Render Objects
		Vertices	lines;
	};
}