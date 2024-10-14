#pragma once
#include <SFML/Graphics.hpp>

class Layout
{
public:
	Layout(Layout* layout) : layout(layout) {}
	Layout* toLayout() { return layout; }
private:
	Layout* layout;
};

class PlotObject :
	public sf::Transformable,
	public sf::Drawable, 
	public Layout
{
public:
	PlotObject(Layout* layout) : Layout(layout) {}
	virtual void recompute() = 0;
};