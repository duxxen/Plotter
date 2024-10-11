#include "../include/plotter.h"

sf::Font						Plotter::font;
std::unique_ptr<PlotterTuple>	Plotter::current;
std::map<size_t, PlotterTuple>	Plotter::plots;

void Plotter::loadFont(std::string path)
{
	font.loadFromFile(path);
	for (auto& node : plots)
	{
		auto& [frame, plot] = node.second;
		for (auto& text : plot.axis.valuesX)
			text.setFont(font);
		for (auto& text : plot.axis.valuesY)
			text.setFont(font);
	}
}

PlotterTuple& Plotter::plot()
{
	size_t newID = plots.size() + 1;

	WindowFrame* newFrame = new WindowFrame(newID);
	Plot* newPlot = new Plot(newFrame);
	auto [it, success] = plots.insert(std::make_pair(newID, PlotterTuple(*newFrame, *newPlot)));
	
	if (!success)
		throw std::exception("Bad insertion!");

	auto& [frame, plot] = it->second;
	frame.plot.reset(newPlot);

	for (auto& text : plot.axis.valuesX)
		text.setFont(font);
	for (auto& text : plot.axis.valuesY)
		text.setFont(font);

	current = std::make_unique<PlotterTuple>(it->second);
	return it->second;
}

void Plotter::show()
{
	bool opened;
	do
	{
		opened = false;
		for (auto& node : plots)
		{
			auto& [frame, plot] = node.second;
			opened |= frame.processEvents();
			frame.show();
		}
	} while (opened);
}
