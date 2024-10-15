#include "../include/plot/axis.h"
#include "../include/plot/plot.h"
#include "../include/plotter.h"

Axis::Axis(Orientation orientation, Label label) :
	locator		(orientation),
	label		(label),
	orientation	(orientation)
{
}

void Axis::setColor(sf::Color color)
{
	Plotter::setAxisColor(color);
}

void Axis::recompute()
{
	locator.recompute();
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(locator, states);
}

