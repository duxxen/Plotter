#pragma once
#include "plot-object.hpp"

namespace Plotter
{
	class Grid : public PlotObject
	{
		friend class Plot;
	public:

		Grid(Plot* layout);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		GridStyle	style;

		// Render Objects
		Vertices	linesV;
		Vertices	linesH;

	};
}