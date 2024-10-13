#pragma once
#include "window.h"
#include "plot.h"
#include "axis.h"
#include "locator.h"

extern class Plotter
{
public:

	Plotter();
	~Plotter();

	void loadFont(std::string path);
	PlotterTuple& plot();
	void show();

private:

	sf::Font						font;
	std::map<size_t, PlotterTuple>	plotters;
}
plt;