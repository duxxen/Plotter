#pragma once
#include "../plot-object.hpp"
#include "../../style/axis-style.hpp"

namespace Plotter
{
	class Axis : public PlotObject
	{
		friend class Plot;
	public:

		Axis(Plot* layout, AxisStyle style);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		AxisStyle	style;

		// Render Objects
		Vertices	aLines;
	};
}

