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
		friend void init(Plot*);
		friend void render();
		friend void fontChanged();

	public:
		Titles(Plot* layout, TextStyle style);

	private:

		void recompute() override;
		void onStyleChanged() override;

		TextStyle		style;

		// Grid-Axis Values
		vector<Text>	valuesX;
		vector<Text>	valuesY;

		// Cursor Values
		vector<Text>	valuesC;
	};
}