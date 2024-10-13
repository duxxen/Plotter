#include "../include/window.h"
#include "../include/plot.h"

Window::Window(size_t id, sf::Vector2f size, float dpi) :
	id	(id),
	dpi (dpi),
	size(size)
{
	init();
}

void Window::resize(sf::Vector2f size)
{
}

void Window::resize(float dpi)
{
}

void Window::init()
{
	window.create(sf::VideoMode(size.x * dpi, size.y * dpi), "Frame " + std::to_string(id));
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
	window.clear(DEFAULT_BACKGROUND_COLOR);
	if (plot) window.draw(*plot);
	window.display();
}
