
#pragma once
#include "../plot-object.hpp"
#include "../../style/graph-style.hpp"

namespace Plotter
{
	class Graph : public PlotObject
	{
		friend class Plot;
	public:

		Graph(Plot* layout);
		Graph(Plot* layout, GraphStyle style);

		void graph(Func func, float vfrom, float vto);
		void graph(vector<Values> points);

	private:

		void recompute() override;
		void onStyleChanged() override;

		// Style
		GraphStyle			style;

		// Function & Values
		Func				func;
		vector<Values>		points;
		Values				min;
		Values				max;

		// Render Objects
		Vertices			gLines;
		Vertices			vTriangles;
	};
}
