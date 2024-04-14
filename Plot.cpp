#include "Plot.hpp"

void Plotter::Plot::run()
{
	if (window.isOpen())
	{
		processEvents();
		render();
	}
}

void Plotter::Plot::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		default:
			break;
		}
	}
}

void Plotter::Plot::render()
{
	window.clear();
	window.display();
}
