#pragma once
#include "../object.hpp"
#include "../title/title.h"

namespace Plotter
{
	class Axis : Object
	{
		friend class Plot;
		friend class Grid;

	public:

		static inline const struct AxisStyle : Style
		{
			bool	centered;
			Color	color;
			sf::String	nameX;
			sf::String	nameY;

			AxisStyle(
				Color color = Color::White,
				bool centered = true,
				sf::String nameX = "Axis X",
				sf::String nameY = "Axis Y"
			);
		}
		DEFAULT_AXIS_STYLE;

	private:

		Axis(Plot* layout, AxisStyle style = DEFAULT_AXIS_STYLE, Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE);

		void onStyleChanged(AxisStyle nstyle);

		void init() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void recompute() override;

		AxisStyle		style;

		Coords			intersection;

		Title			nameX;
		Title			nameY;
		sf::VertexArray lines;
	};
}