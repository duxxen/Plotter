#pragma once
#include "../object.hpp"

namespace Plotter
{
	class Graph : Object
	{
		friend class Plot;

	public:

		static inline const struct GraphStyle : Style
		{
			enum Flags
			{
				SHOW_NONE = 0,
				SHOW_LINE = 1,
				SHOW_VOLUME = SHOW_LINE << 1,
				SHOW_POINTS = SHOW_LINE << 2,
				SHOW_ALL = SHOW_LINE | SHOW_VOLUME | SHOW_POINTS
			};

			Color	color;
			Flags	flags;
			uint8_t	transparency;

			GraphStyle(
				Color color = Color::Red,
				Flags flags = Flags::SHOW_LINE,
				uint8_t transparecny = 0x40
			);
		}
		DEFAULT_GRAPH_STYLE;

	private:

		Graph(Plot* layout, GraphStyle style = DEFAULT_GRAPH_STYLE);

		void graph(Func func, float start, float end);
		void graph(const vector<Values>& points);

		void rebuild();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void onStyleChanged() override;
		void recompute() override;

		GraphStyle		style;

		Values			min;	// { argument, value }
		Values			max;

		vector<Values>	points;
		Func			function;

		sf::VertexArray	line;
		sf::VertexArray volume;
	};
}