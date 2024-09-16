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
			Color		frameColor;

			uint32_t	pointCount;

			PlotStyle(
				string windowName = "Plot", 
				Coords windowSize = Coords(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT),
				Color backgroundColor = Color::Black,
				Color frameColor = Color::White,
				uint32_t pointCount = DEFAULT_POINT_COUNT
			);
		} 
		DEFAULT_PLOT_STYLE;

		Plot(
			PlotStyle pstyle = DEFAULT_PLOT_STYLE,
			Axis::AxisStyle astyle = Axis::DEFAULT_AXIS_STYLE,
			Grid::GridStyle gstyle = Grid::DEFAULT_GRID_STYLE,
			Cursor::CursorStyle cstyle = Cursor::DEFAULT_CURSOR_STYLE,
			Title::TitleStyle tstyle = Title::DEFAULT_TITLE_STYLE
		);

		void setStyle(PlotStyle newStyle);
		void setStyle(Axis::AxisStyle newStyle);
		void setStyle(Grid::GridStyle newStyle);
		void setStyle(Cursor::CursorStyle newStyle);
		void setStyle(Title::TitleStyle newStyle);

		void setBoundsX(float start = -10, float end = 10);
		void setBoundsY(float start, float end);
		void setBounds(Values start, Values end);

		void plot(Func func, Graph::GraphStyle style = Graph::DEFAULT_GRAPH_STYLE);
		void plot(size_t index, Func func);

		void plot(Func func, float start, float end, Graph::GraphStyle style = Graph::DEFAULT_GRAPH_STYLE);
		void plot(size_t index, Func func, float start, float end);

		bool processEvents();
		void update();
		void render();

	private:
		
		// -------------------------------------- TRANSFORMATION ------------------------------------------
		Coords toCoords(Values point) const;
		Values toValues(Coords point) const;
		Coords toCoords(float vx, float vy) const;
		Values toValues(float cx, float cy) const;

		Coords rangeCoords(Coords point) const;
		Coords rangeCoords(float cx, float cy) const;

		// -------------------------------------- ??? ------------------------------------------

		void onStyleChanged(PlotStyle style);
		void onWindowResize(float width, float height);
		void onFrameResize(float width, float height);
		void onAxisMove();

		// ---------------------------------------- OVERRIDES --------------------------------------------

		void init() override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
		void recompute() override;

		PlotStyle			style;

		Coords				frameSize;
		Values				scale;		// Used for Value <-> Coords transform
		Values				start;
		Values				end;

		float				max		{ 0 };
		float				min		{ 0 };
		bool				yAuto	{ true };	// auto ordinate axis scale

		vector<Graph>		graphs;
		Cursor				cursor;
		Axis				axis;
		Grid				grid;

		sf::RectangleShape	frameShape;
		sf::RenderWindow	window;
	};
}