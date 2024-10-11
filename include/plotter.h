#pragma once
#include "plot.h"
#include "window-frame.h"

class Plotter
{
public:

	static void loadFont(std::string path);

	static PlotterTuple& plot();
	static void show();

private:

	static sf::Font							font;
	static std::unique_ptr<PlotterTuple>	current;
	static std::map<size_t, PlotterTuple>	plots;
};