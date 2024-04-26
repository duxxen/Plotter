#pragma once
#include "../plot-object.hpp"
#include "../../style/line-style.hpp"

namespace Plotter
{
	class Graph : public PlotObject
	{
		friend class Plot;
	public:

		Graph(Plot* layout);
		Graph(Plot* layout, LineStyle style);

		void graph(Func func, float startX, float startY);
		void graph(vector<Vec2> points);

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