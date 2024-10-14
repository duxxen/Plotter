#include "../include/plotter.h"

Plot*							Plotter::current;
std::map<size_t, PlotterTuple>	Plotter::plotters;

PlotterTuple& Plotter::plot()
{
	size_t newID = plotters.size() + 1;
	Window* newWindow = new Window(newID);
	Plot* newPlot = new Plot(newWindow);
	auto [it, success] = plotters.insert(std::make_pair(newID, PlotterTuple(newWindow, newPlot)));
	
	if (success == false)
		throw std::exception("Bad insertion!");

	newWindow->plots.push_back(newPlot);
	current = newPlot;
	return it->second;
}

void Plotter::show()
{
	while (!plotters.empty())
	{
		for (auto it = plotters.begin(); it != plotters.end(); it++)
		{
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

void Plotter::setAxisColor(sf::Color color)
{
	auto pframe = current->frame;
	auto lmajoresx = current->axisX.locator.majores;
	auto lminoresx = current->axisX.locator.minores;
	auto lmajoresy = current->axisY.locator.majores;
	auto lminoresy = current->axisY.locator.minores;

	for (auto i = 0; i < pframe.getVertexCount(); i++)
		pframe[i].color = color;
	for (auto i = 0; i < lmajoresx.getVertexCount(); i++)
		pframe[i].color = color;
	for (auto i = 0; i < lminoresx.getVertexCount(); i++)
		pframe[i].color = color;
	for (auto i = 0; i < lmajoresy.getVertexCount(); i++)
		pframe[i].color = color;
	for (auto i = 0; i < lminoresy.getVertexCount(); i++)
		pframe[i].color = color;
}

void Plotter::setGridColor(sf::Color color)
{
}

void Plotter::setGridCountX(size_t count)
{
}

void Plotter::setGridCountY(size_t count)
{
}

void Plotter::setGridCount(sf::Vector2u count)
{
}
