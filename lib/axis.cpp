#include "../include/axis.h"
#include "../include/plot.h"

Axis::Axis(Plot* layout, bool isX) :
	layout		(layout),
	horizontal	(isX),
	orientation	(isX ? sf::Transform(1, 0, 1, 0, 1, 1, 0, 0, 1) : sf::Transform(0, 1, -1, 1, 1, 0, 0, 0, 1)),
	locator		(this, 5, 5)
{
}

void Axis::recompute()
{
	length = horizontal ? layout->frame.getSize().x : layout->frame.getSize().y;
	locator.recompute();
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= orientation;
	target.draw(locator, states);
}
