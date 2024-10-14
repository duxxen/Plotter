#pragma once
#include "common.hpp"

class Window :
	public Layout
{
	friend class Plotter;
public:
	Window(size_t id, sf::Vector2f size = { 4.f, 3.f }, float dpi = 100.f);

	void resize(sf::Vector2f size);
	void resize(float dpi);

	sf::Vector2f getSize() const;
	sf::Vector2f getWindowSize() const;

private:

	bool processEvents();
	void show();

	std::vector<Plot*>	plots;
	sf::RenderWindow	window;
	sf::Vector2f		size;
	float				dpi;
	const size_t		id;
	sf::Color			layoutColor{ sf::Color::White };
};