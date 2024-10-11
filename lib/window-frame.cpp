#include "../include/window-frame.h"
#include "../include/plot.h"

WindowFrame::WindowFrame(size_t id) :
	id		(id)
{
	window.create(sf::VideoMode(size.x * dpi, size.y * dpi), "Frame " + std::to_string(id));
}

WindowFrame::WindowFrame(size_t id, sf::Vector2f size, float dpi) :
	id		(id),
	size	(size),
	dpi		(dpi),
	window	(sf::VideoMode(size.x * dpi, size.y * dpi), "Frame " + std::to_string(id))
{
}

WindowFrame::WindowFrame(const WindowFrame&& obj) noexcept :
	id		(id),
	size	(obj.size),
	dpi		(obj.dpi),
	window	(sf::VideoMode(obj.window.getSize().x, obj.window.getSize().y), "Frame " + std::to_string(id))
{
}

bool WindowFrame::processEvents()
{
	bool opened = window.isOpen();
	if (opened)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				opened = false;
				break;

			default:
				break;
			}
		}
	}

	return opened;
}

void WindowFrame::show()
{
	if (window.isOpen())
	{
		window.clear(sf::Color::White);
		if (plot)	window.draw(*plot);
		window.display();
	}
}
