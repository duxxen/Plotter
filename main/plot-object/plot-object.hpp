#pragma once

namespace Plotter
{
	class Plot;

	class PlotObject
	{
	protected:
		PlotObject(Plot* layout) :
			layout{ layout }
		{
		}

		virtual void recompute() = 0;
		virtual void onStyleChanged() {}

		Plot* layout;
	};
}

#include "axis/axis.h"
#include "cursor/cursor.h"
#include "graph/graph.h"
#include "grid/grid.h"
#include "titles/titles.h"