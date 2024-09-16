#pragma once
#include "object.hpp"
#include "graph/graph.h"
#include "cursor/cursor.h"
#include "axis/axis.h"
#include "grid/grid.h"

namespace Plotter
{
	class Plot : Object
	{
		friend class Axis;
		friend class Grid;
		friend class Graph;
		friend class Cursor;

	public:

		static inline const struct PlotStyle : Style
		{
			string		windowName;
			Coords		windowSize;
			Color		backgroundColor;

			Coords		frameSize;
			Coords		framePosition;
			Color		frameColor;

			uint32_t	pointCount;

			PlotStyle(
				string windowName = "Plot", 
				Coords windowSize = Coords(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT),
				Color backgroundColor = Color::Black,
				Coords frameSize = Coords(DEFAULT_WIN_WIDTH - 2 * DEFAULT_WIN_INDENT, DEFAULT_WIN_HEIGHT - 2 * DEFAULT_WIN_INDENT),
				Coords framePosition = Coords(DEFAULT_WIN_INDENT, DEFAULT_WIN_INDENT),
				Color frameColor = Color::White,
				uint32_t pointCount = DEFAULT_POINT_COUNT
			);
		} 
		DEFAULT_PLOT_STYLE;

		Plot(
			PlotStyle pstyle = DEFAULT_PLOT_STYLE,
			Axis::AxisStyle astyle = Axis::DEFAULT_AXIS_STYLE,
			Grid::GridStyle gstyle = Grid::DEFAULT_GRID_STYLE,
			Graph::GraphStyle lstyle = Graph::DEFAULT_GRAPH_STYLE,
			Cursor::CursorStyle cstyle = Cursor::DEFAULT_CURSOR_STYLE,
			Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE
		);

		void init(
			PlotStyle pstyle = DEFAULT_PLOT_STYLE,
			Axis::AxisStyle astyle = Axis::DEFAULT_AXIS_STYLE,
			Grid::GridStyle gstyle = Grid::DEFAULT_GRID_STYLE,
			Graph::GraphStyle lstyle = Graph::DEFAULT_GRAPH_STYLE,
			Cursor::CursorStyle cstyle = Cursor::DEFAULT_CURSOR_STYLE,
			Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE
		);

		void setPointCount(size_t pointCount);

		void setStyle(PlotStyle style);
		void setStyle(Axis::AxisStyle style);
		void setStyle(Grid::GridStyle style);
		void setStyle(Graph::GraphStyle style);
		void setStyle(Cursor::CursorStyle style);
		void setStyle(Title::TitleStyle style);

		bool processEvents();
		void update();
		void render();

		void plot(Func func, float start, float end);

	private:

		void initWindow();
		
		Coords toCoords(Values point) const;
		Values toValues(Coords point) const;
		Coords toCoords(float vx, float vy) const;
		Values toValues(float cx, float cy) const;

		Coords rangeCoords(Coords point) const;
		Coords rangeCoords(float cx, float cy) const;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void onStyleChanged() override;
		void recompute() override;

		PlotStyle			style;

		Values				scale; // Used for Value <-> Coords transform
		Values				start;
		Values				end;

		Graph				graph;
		Cursor				cursor;
		Axis				axis;
		Grid				grid;

		sf::RectangleShape	frameShape;
		sf::RenderWindow	window;
	};
}