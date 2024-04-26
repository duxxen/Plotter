#pragma once
#include "../plot-object.hpp"
#include "../../style/text-style.hpp"

namespace Plotter
{
	class Titles : public PlotObject
	{
		friend class Axis;
		friend class Cursor;
		friend class Grid;
		friend class Plot;

	public:
		Titles(Plot* layout, TextStyle style);

	private:

		void recompute() override;
		void onStyleChanged() override;

		TextStyle	style;
	};
}