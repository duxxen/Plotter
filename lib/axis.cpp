#include "../include/axis.h"
#include "../include/plot.h"

Axis::Axis(Plot* layout) :
	layout	(layout),
	marksX	(sf::Lines, 2 * (layout->gridSpacing.x + 1)),
	marksY	(sf::Lines, 2 * (layout->gridSpacing.y + 1))
{
}

void Axis::recompute()
{
	auto fthickness = layout->frame.getOutlineThickness();
	auto foffset = sf::Vector2f(fthickness, fthickness);
	auto fsize = layout->frame.getSize() + 2.f * foffset;
	auto mlength = -fthickness + 5.f;
	auto ainch = sf::Vector2f(
		fsize.x / layout->gridSpacing.x,
		fsize.y / layout->gridSpacing.y
	);

	for (auto x = 0; x <= layout->gridSpacing.x; x++)
	{
		auto aposition = sf::Vector2f(x * ainch.x, fsize.y) - foffset;
		marksX[2 * x] = sf::Vertex(sf::Vector2f(aposition.x, aposition.y), sf::Color::Black);
		marksX[2 * x + 1] = sf::Vertex(sf::Vector2f(aposition.x, aposition.y + mlength), sf::Color::Black);
	}
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(marksX, states);
}
