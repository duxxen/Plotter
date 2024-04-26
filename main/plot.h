#pragma once
#include "style/plot-style.hpp"
#include "plot-object/plot-object.hpp"

namespace Plotter
{
	class Plot
	{
		friend class Axis;
		friend class Cursor;
		friend class Graph;
		friend class Grid;
		friend class Title;

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
		void setStyle(size_t index, GraphStyle style);
		void setStyle(GridStyle style);
		void setStyle(AxisStyle style);
		void setStyle(TextStyle style);
		void setStyle(CursorStyle style);

		//----------------- BUILD PLOT FUNCTION ------------------------------------------------------------------------------------------
		// Graph of Function
		void plot(Func func);											// Builds	[new] Plot   (Style: AUTO)	
		void plot(size_t index, Func func);								// Rebuilds [index] Plot (Style: AUTO)
		void plot(Func func, GraphStyle style);							// Builds	[new] Plot	 (Style: style)		
		void plot(size_t index, Func func, GraphStyle style);			// Rebuilds	[index] Plot (Style: style)		<- main

		// Graph of Points
		void plot(vector<Vec2> points);									// Builds	[new] Plot   (Style: AUTO)	
		void plot(size_t index, vector<Vec2> points);					// Rebuilds [index] Plot (Style: AUTO)
		void plot(vector<Vec2> points, GraphStyle style);				// Builds	[new] Plot	 (Style: style)		
		void plot(size_t index, vector<Vec2> points, GraphStyle style);	// Rebuilds	[index] Plot (Style: style)		<- main

		// Update function which must be called from loop
		void update();

	private:

		//----------------- TRANSFORM FUNCTIONS ---------------------------------------------------------------------------------------

		Coords toCoords(float vx, float vy) const;
		Coords toCoords(Values value) const;
		Coords toCoordsRanged(float vx, float vy) const;
		Coords toCoordsRanged(Values value) const;

		Values toValues(float cx, float cy) const;
		Values toValues(Coords coord) const;

		Coords range(float cx, float cy) const;
		Coords range(Coords coord) const;

		//----------------- PLOT VARIABLES ----------------------------------------------------------------------------------------

		// Style
		PlotStyle	style;

		// Transforms
		RectCoords	bounds;
		Values		scale;

		// Graph Variables
		Values		start;
		Values		end;
		bool		yAuto;

		// Plot objects
		Axis		axis;
		Cursor		mouseCursor;
		Cursor		leftCursor;
		Cursor		rightCursor;


		
	};
}