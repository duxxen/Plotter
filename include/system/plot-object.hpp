#pragma once
#include <SFML/Graphics.hpp>

enum Orientation
{
	HORIZONTAL,
	VERTICAL
};

class PlotObject :
	public sf::Transformable,
	public sf::Drawable
{
public:
	virtual void recompute() = 0;
};