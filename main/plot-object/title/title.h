#pragma once
#include "../plot-object.hpp"
#include "../../style/text-style.hpp"

namespace Plotter
{
	class Title : public PlotObject
	{
		friend class Axis;
		friend class Cursor;
		friend class Grid;
		friend class Plot;

	public:
		Title(Plot* layout, TextStyle style);

	private:
		TextStyle	style;	
	};
}