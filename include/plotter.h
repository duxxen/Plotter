#pragma once
#include "common.hpp"
#include "window.h"
#include "plot/plot.h"
#include "plot/locator.h"

class Plotter : 
	public Singleton
{
public:

	static PlotterTuple& plot();
	static void show();

	static void setAxisColor(sf::Color color);
	static void setGridColor(sf::Color color);

	static void setGridCountX(size_t count);
	static void setGridCountY(size_t count);
	static void setGridCount(sf::Vector2u count);

private:

	static Plot*							current;
	static std::map<size_t, PlotterTuple>	plotters;
};