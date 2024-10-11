#pragma once
#include "plot.h"
#include "window-frame.h"

class Plotter
{
public:

	static PlotterTuple& plot();
	static void show();

private:

	static std::unique_ptr<PlotterTuple>	current;
	static std::map<size_t, PlotterTuple>	plots;
};