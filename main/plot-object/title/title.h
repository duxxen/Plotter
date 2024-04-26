#pragma once
#include "../plot-object.hpp"
#include "../../style/text-style.hpp"

namespace Plotter
{
	class Title : public PlotObject
	{
		friend class Plot;
		friend class Axis;
		friend class Grid;
		friend class Cursor;

	public:
		Title(Plot* layout, TextStyle style);

	private:

		// Values
		struct Text
		{
			string	value;
			Vec2	coords;
		};

		void recompute() override;
		void onStyleChanged() override;

		// Style
		TextStyle		style;

		// Font
		sf::Font		font;

		// Cursor values
		Text			valuesC;

		// Grid values
		vector<Text>	valuesX;
		vector<Text>	valuesY;
	};
}