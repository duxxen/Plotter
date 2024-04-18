#pragma once
#include "plot-object.hpp"

namespace Plotter
{
	class Graph : public PlotObject
	{
		friend class Plot;
	public:

		Graph(Plot* layout);

		void graph(Func func, float startX, float startY);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		LineStyle			style;

		// Function & Values
		Func				func;
		std::vector<Vec2>	points;
		Vec2				min;
		Vec2				max;

		// Render Objects
		Vertices			gLines;
		Vertices			vTriangles;
	};
}