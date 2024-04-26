#pragma once
#include "style/plot-style.hpp"
#include "../utility/tostring.hpp"
#include "../utility/inputs.hpp"

//#include "plot-object/axis/axis.h"
//#include "plot-object/cursor/cursor.h"
//#include "plot-object/graph/graph.h"
//#include "plot-object/grid/grid.h"
//#include "plot-object/title/title.h"
#include "plot-object/plot-object.hpp"

namespace Plotter
{
	class Plot
	{
		friend class Graph;
		friend class Grid;
		friend class Axis;
		friend class Title;
		friend class Cursor;


	public:
		Plot(std::string name = "Plot",
			PlotStyle pStyle = PSTYLE_PRESETS[STYLE_DEFAULT],
			GridStyle gStyle = GSTYLE_PRESETS[STYLE_DEFAULT],
			AxisStyle aStyle = ASTYLE_PRESETS[STYLE_DEFAULT],
			TextStyle tStyle = TSTYLE_PRESETS[STYLE_DEFAULT],
			CursorStyle cstyle = CSTYLE_PRESETS[STYLE_DEFAULT]
		);

		//----------------- VALUES BOUNDARIES CHANGE --------------------------------------------------------------------------------------
		
		void setBoundariesX(float startX, float endX);
		void setBoundariesY(float startY, float endY);
		void setBoundaries(float startX, float endX, float startY, float endY);
		void setBoundaries(Vec2 start, Vec2 end);

		//----------------- STYLES SETTERS -----------------------------------------------------------------------------------------------

		void setStyle(PlotStyle style);
		void setStyle(size_t index, LineStyle style);
		void setStyle(GridStyle style);
		void setStyle(AxisStyle style);
		void setStyle(TextStyle style);
		void setStyle(CursorStyle style);

		//----------------- BUILD PLOT FUNCTION ------------------------------------------------------------------------------------------
		// Graph of Function
		void plot(Func func);									// Builds	[new] Plot   (Style: AUTO)	
		void plot(size_t index, Func func);						// Rebuilds [index] Plot (Style: AUTO)
		void plot(Func func, LineStyle style);					// Builds	[new] Plot	 (Style: style)		
		void plot(size_t index, Func func, LineStyle style);	// Rebuilds	[index] Plot (Style: style)		<- main

		// Graph of Points
		void plot(vector<Vec2> points);									// Builds	[new] Plot   (Style: AUTO)	
		void plot(size_t index, vector<Vec2> points);					// Rebuilds [index] Plot (Style: AUTO)
		void plot(vector<Vec2> points, LineStyle style);				// Builds	[new] Plot	 (Style: style)		
		void plot(size_t index, vector<Vec2> points, LineStyle style);	// Rebuilds	[index] Plot (Style: style)		<- main

		void update();

	private:

		//----------------- TRANSFORM FUNCTIONS ---------------------------------------------------------------------------------------
		
		Vec2 toCoords(float vx, float vy) const;
		Vec2 toCoords(Vec2 value) const;
		Vec2 toCoordsRanged(float vx, float vy) const;
		Vec2 toCoordsRanged(Vec2 value) const;

		Vec2 toValues(float cx, float cy) const;
		Vec2 toValues(Vec2 coord) const;
		
		Vec2 range(float cx, float cy) const;
		Vec2 range(Vec2 coord) const;

		//----------------- RECOMPUTE FUNCTIONS ---------------------------------------------------------------------------------------

		void rebuild();
		void recompute();

		//----------------- PLOT MANIPULATIONS ----------------------------------------------------------------------------------------

		

		//----------------- USER INPUT ------------------------------------------------------------------------------------------------

		void onMouseMoved();
		void onMousePressed();
		void onMouseReleased();
		void onKeyPressed();
		void onKeyReleased();

		//----------------- GRAPHICS FUNCTIONS ----------------------------------------------------------------------------------------

		void initWindow();		// init Render Target
		void updateMouse();		// update mouseCoords and pressedRMB, pressedLMB
		void pollEvent();		// events update
		void render();			// render stuff

		// Style
		PlotStyle			style;

		// Transforms
		Rect				bounds;
		Vec2				vScale;
		
		// Graph variables
		Vec2				vStart;
		Vec2				vEnd;
		bool				vAuto;

		// Render Target
		Window				window;

		// Plot manipulators
		Graph*				chosen;

		// User input
		Mouse				mouse;
		Keyboard			key;

		// Render Objects
		std::vector<Graph>	graphs;
		Grid				grid;
		Axis				axis;
		Title				title;
		Cursor				cursor;
	};
}