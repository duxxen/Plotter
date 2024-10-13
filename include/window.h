#pragma once
#include "common.hpp"

class Window
{
	friend class Plot;
	friend class Plotter;
public:

	Window(size_t id, sf::Vector2f size = { 4.f, 3.f }, float dpi = 100.f);

	void resize(sf::Vector2f size);
	void resize(float dpi);

private:

	void init();
	bool processEvents();
	void show();

	sf::RenderWindow	window;
	Plot*				plot;
	sf::Vector2f		size;
	float				dpi;
	const size_t		id;
};