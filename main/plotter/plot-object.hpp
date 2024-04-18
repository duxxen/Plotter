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