#pragma once

#include "../common.hpp"
#include "../style/axis-style.hpp"
#include "../style/grid-style.hpp"
#include "../style/line-style.hpp"
#include "../style/plot-style.hpp"
#include "../style/text-style.hpp"
#include "../style/cursor-style.hpp"

#include "../../utility/tostring.hpp"

#include "graph.h"
#include "grid.h"
#include "axis.h"
#include "title.h"
#include "cursor.h"

namespace Plotter
{
	

	

	class Plot
	{
	public:
		

		Plot(std::string name = "Plot",
			PlotStyle pStyle = PSTYLE_PRESETS[STYLE_DEFAULT],
			GridStyle gStyle = GSTYLE_PRESETS[STYLE_DEFAULT],
			AxisStyle aStyle = ASTYLE_PRESETS[STYLE_DEFAULT],
			TextStyle tStyle = TSTYLE_PRESETS[STYLE_DEFAULT]
		);

		//----------------- VALUES BOUNDARIES CHANGE --------------------------------------------------------------------------------------------
		
		void setBoundariesX(float startX, float endX);
		void setBoundariesY(float startY, float endY);
		void setBoundaries(float startX, float endX, float startY, float endY);
		void setBoundaries(Vec2 start, Vec2 end);

		//----------------- BUILD PLOT FUNCTION ------------------------------------------------------------------------------------------

		void plot(Func func);								// Builds	[new] Plot   (Style: AUTO)	
		void plot(size_t index, Func func);					// Rebuilds [index] Plot (Style: AUTO)
		void plot(Func func, LineStyle style);				// Builds	[new] Plot	 (Style: style)		
		void plot(size_t index, Func func, LineStyle style);// Rebuilds	[index] Plot (Style: style)		<- main

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

		//----------------- GRAPHICS FUNCTIONS ----------------------------------------------------------------------------------------

		void initWindow();
		void updateMouse();
		void pollEvent();
		void render();

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

		// Mouse
		Vec2				mouseCoords;

		// Render Objects
		std::vector<Graph>	graphs;
		Grid				grid;
		Axis				axis;
		Title				titles;
		Cursor				cursor;
	};
}