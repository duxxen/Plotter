#include "../include/plotter.h"

Plotter::Plotter()
{
	loadFont(DEFAULT_FONTS_FOLDER + DEFAULT_FONT_NAME);
}

Plotter::~Plotter()
{
	for (auto it = plotters.begin(); it != plotters.end(); it++)
	{
		auto& [window, plot] = it->second;
		delete window;
		delete plot;
		it = plotters.erase(it);
		if (it == plotters.end())
			break;
	}
}

void Plotter::loadFont(std::string path)
{
	font.loadFromFile(path);
	for (auto& node : plotters)
	{
		auto& [window, plot] = node.second;
	}
}

PlotterTuple* Plotter::plot()
{
	auto newID = plotters.size() + 1;
	auto newWindow = new Window(newID);
	auto newPlot = new Plot(newWindow);
	auto [it, success] = plotters.insert(std::make_pair(newID, PlotterTuple(newWindow, newPlot)));
	if (!success)
	{
		delete newWindow;
		delete newPlot;
		throw std::exception("Bad insertion!");
	}
	auto& [frame, plot] = it->second;
	frame->plot = plot;
	
	return &it->second;
}

void Plotter::show()
{
	while (!plotters.empty())
	{
		for (auto it = plotters.begin(); it != plotters.end(); it++)
		{
			auto& [window, plot] = it->second;
			auto opened = it->second.wptr->processEvents();
			it->second.wptr->show();
			if (opened == false)
			{
				it = plotters.erase(it);
				if (it == plotters.end())
					break;
			}
		}
	}
}
