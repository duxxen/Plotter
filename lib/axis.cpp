#include "../include/axis.h"
#include "../include/plot.h"
#include "../include/plotter.h"

Axis::Axis(Plot* layout) :
	layout	(layout),
	marksX	(sf::Lines, 2 * (layout->gridSize.x + 1)),
	marksY	(sf::Lines, 2 * (layout->gridSize.y + 1)),
	valuesX	(2 * (layout->gridSize.x + 1)),
	valuesY	(2 * (layout->gridSize.x + 1))
{
	for (auto& text : valuesX)
		text.setCharacterSize(8U);
	for (auto& text : valuesY)
		text.setCharacterSize(8U);
}

void Axis::recompute()
{
	auto moffset = sf::Vector2f(0, -1.f);
	auto fsize = layout->frame.getSize();
	auto minch = sf::Vector2f(
		fsize.x / layout->gridSize.x,
		fsize.y / layout->gridSize.y
	);

	for (auto x = 0; x <= layout->gridSize.x; x++)
	{
		if (x == layout->gridSize.x)
			moffset.x = 1.f;
		auto mposition = sf::Vector2f(x * minch.x + moffset.x, fsize.y);

		marksX[2 * x] = sf::Vertex(mposition, sf::Color::Black);
		marksX[2 * x + 1] = sf::Vertex(sf::Vector2f(mposition.x, mposition.y + 5.f), sf::Color::Black);
	}

	for (auto y = 0; y <= layout->gridSize.y; y++)
	{
		if (y > 0)
			moffset.y = 0.f;
		auto mposition = sf::Vector2f(0.f, y * minch.y + moffset.y);

		marksY[2 * y] = sf::Vertex(mposition, sf::Color::Black);
		marksY[2 * y + 1] = sf::Vertex(sf::Vector2f(mposition.x - 5.f, mposition.y), sf::Color::Black);
	}
}

void Axis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(marksX, states);
	target.draw(marksY, states);
}
