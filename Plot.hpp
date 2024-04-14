#pragma once
#include <SFML/Graphics.hpp> 

#include "main/Common.hpp"
#include "main/LineStyle.hpp"
#include "main/PlotStyle.hpp"

namespace Plotter
{
	class Plot
	{
	public:

		Plot(std::string name = "Plot");

		void plot(std::vector<float> vx, std::vector<float> vy);
		void plot(std::function<float(float)> func);

	private:

		void recomputePlot();
		void recomputeGrid();
		void recomputeFrame();

		void run();
		void processEvents();
		void render();

		LineProperties		lStyle;
		PlotProperties		pStyle;

		sf::RenderWindow	window;
		std::thread			thread;

		sf::VertexArray		gLinesV; // Grid lines
		sf::VertexArray		gLinesH;
		sf::VertexArray		aLines;
		sf::VertexArray		fLines;
		sf::VertexArray		pLines;
		sf::VertexArray		vLines;
	};
}

Plotter::Plot::Plot(std::string name)
{
	window.create(sf::VideoMode(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT), name);
	gLinesV.setPrimitiveType(sf::Lines);
	gLinesH.setPrimitiveType(sf::Lines);
	fLines.setPrimitiveType(sf::LineStrip);
	pLines.setPrimitiveType(sf::LineStrip);
	vLines.setPrimitiveType(sf::TriangleStrip);
}

inline void Plotter::Plot::plot(std::vector<float> vx, std::vector<float> vy)
{
}

inline void Plotter::Plot::plot(std::function<float(float)> func)
{
}
