#include "../include/window.h"
#include "../include/plot/plot.h"

Window::Window(size_t id, sf::Vector2f size, float dpi) :
	id		(id),
	dpi		(dpi),
	size	(size),
	window	(sf::VideoMode(size.x * dpi, size.y * dpi), "Frame " + std::to_string(id))
{
}

void Window::resize(sf::Vector2f size)
{

}

void Window::resize(float dpi)
{

}

sf::Vector2f Window::getSize() const
{
	return size;
}

sf::Vector2f Window::getWindowSize() const
{
	return size * dpi;
}

bool Window::processEvents()
{
	auto opened = window.isOpen();
	if (opened)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				opened = false;
				window.close();
				break;

			default:
				break;
			}
		}
	}

	return opened;
}

void Window::show()
{
	if (window.isOpen())
	{
		window.clear(layoutColor);
		for (auto& plot : plots)
			if (plot)	window.draw(*plot);
		window.display();
	}
}