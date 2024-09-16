#pragma once
#include "../object.hpp"
#include "../title/title.h"

namespace Plotter
{
	class Grid : Object
	{
		friend class Plot;

	public:

		static inline const struct GridStyle : Style
		{
			size_t	countX;
			size_t	countY;
			Color	color;

			GridStyle(
				size_t countX = 10,
				size_t countY = 10,
				Color color = Color(0x404040ff)
			);
		}
		DEFAULT_GRID_STYLE;

	private:

		Grid(Plot* layout, GridStyle style = DEFAULT_GRID_STYLE, Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE);

		void onStyleChanged(GridStyle nstyle);
		void onStyleChanged(Title::TitleStyle nstyle);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void init() override;
		void recompute() override;

		GridStyle			style;

		Title				example;
		vector<Title>		titles;

		sf::VertexArray		linesH;
		sf::VertexArray		linesV;
	};
}