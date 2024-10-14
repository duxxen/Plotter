#include "../include/plot/axis.h"
#include "../include/plot/plot.h"
#include "../include/plotter.h"

Axis::Axis(Plot* layout, Orientation orientation, Label label) :
	PlotObject	(layout),
	locator		(this),
	label		(label),
	length		(0.f),
	orientation	(orientation)
{
}

void Axis::setColor(sf::Color color)
{
	Plotter::setAxisColor(color);
}

Axis::Orientation Axis::getOrientation() const
{
	return orientation;
}

float Axis::getLength() const
{
	return length;
}

void Axis::recompute()
{
	auto plot = static_cast<Plot*>(toLayout());
	length = orientation == HORIZONTAL ? plot->getSize().x : plot->getSize().y;
	locator.recompute();
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(locator, states);
}

