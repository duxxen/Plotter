#include "../include/axis.h"
#include "../include/plot.h"

Axis::Axis(Plot* layout, bool isX) :
	layout		(layout),
	horizontal	(isX),
	length		(1.f),
	locator		(this, 5, 0)
{
	if (!horizontal)
	{
		setRotation(90);
		setScale(1, -1);
	}
}

void Axis::recompute()
{
	length = horizontal ? layout->size.x : layout->size.y;
	locator.recompute();
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(locator, states);
}
