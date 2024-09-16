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

			AxisStyle(
				Color color = Color::White,
				bool centered = false
			);
		}
		DEFAULT_AXIS_STYLE;

	private:

		Axis(Plot* layout, AxisStyle style = DEFAULT_AXIS_STYLE);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void onStyleChanged() override;
		void recompute() override;

		AxisStyle		style;

		Coords			intersection;

		sf::VertexArray lines;
	};
}