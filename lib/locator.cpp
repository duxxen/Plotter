#include "../include/plot/locator.h"
#include "../include/plotter.h"

Locator::Locator(Orientation orientation, size_t majorCount, size_t minorCount) :
	orientation	(orientation),
	gridEnabled	(true),
	majorCount	(majorCount),
	minorCount	(minorCount),
	grid		(sf::Lines, 2 * (majorCount - 1)),
	majores		(sf::Lines, 2 * majorCount),
	minores		(sf::Lines, 2 * (majorCount - 1) * minorCount),
	majorLabels	(2 * majorCount, Label()),
	minorLabels	(2 * majorCount * minorCount, Label())
{
}

void Locator::setColor(sf::Color color)
{
	Plotter::setAxisColor(color);
}

void Locator::setMajorCount(size_t count)
{
	majorCount = count;
	recompute();
}

void Locator::setMinorCount(size_t count)
{
	minorCount = count;
}

size_t Locator::getMajorCount() const
{
	return majorCount;
}

size_t Locator::getMinorCount() const
{
	return minorCount;
}

void Locator::recompute()
{
	auto m = majorCount - 1;
	auto n = minorCount;
	majores.resize(2 * majorCount);
	minores.resize(2 * m * n);
	majorLabels.resize(majorCount, Label());
	minorLabels.resize(m * n);

	auto stepmjv = 1.f / m;
	auto stepmnv = 1.f / (m * (n + 1));
	auto lengthmjv = -0.04f;
	auto lengthmnv = -0.02f;

	auto stepmj = orientation == HORIZONTAL ? sf::Vector2f(stepmjv, 0) : sf::Vector2f(0, stepmjv);
	auto stepmn = orientation == HORIZONTAL ? sf::Vector2f(stepmnv, 0) : sf::Vector2f(0, stepmnv);
	auto lengthmj = orientation == HORIZONTAL ? sf::Vector2f(0, lengthmjv) : sf::Vector2f(lengthmjv, 0);
	auto lengthmn = orientation == HORIZONTAL ? sf::Vector2f(0, lengthmnv) : sf::Vector2f(lengthmnv, 0);
	auto lengthg = orientation == HORIZONTAL ? sf::Vector2f(0, 1) : sf::Vector2f(1, 0);

	auto pos0 = (float)m * stepmj;
	auto pos1 = pos0 + lengthmj;
	majores[2 * m] = sf::Vertex(pos0, sf::Color::Black);
	majores[2 * m + 1] = sf::Vertex(pos1, sf::Color::Black);
	for (int i = m - 1; i >= 0; i--)
	{
		pos0 = majores[2 * (i + 1)].position - stepmj;
		pos1 = pos0 + lengthmj;
		majores[2 * i] = sf::Vertex(pos0, sf::Color::Black);
		majores[2 * i + 1] = sf::Vertex(pos1, sf::Color::Black);

		auto posg0 = pos0;
		auto posg1 = posg0 + lengthg;

		pos0 = majores[2 * (i + 1)].position - stepmn;
		pos1 = pos0 + lengthmn;
		minores[2 * n * (i + 1) - 2] = sf::Vertex(pos0, sf::Color::Black);
		minores[2 * n * (i + 1) - 1] = sf::Vertex(pos1, sf::Color::Black);
		for (int j = n - 2; j >= 0; j--)
		{
			pos0 = pos0 - stepmn;
			pos1 = pos0 + lengthmn;
			minores[2 * (n * i + j)] = sf::Vertex(pos0, sf::Color::Black);
			minores[2 * (n * i + j) + 1] = sf::Vertex(pos1, sf::Color::Black);
		}

		if (i == 0) continue;
		grid[2 * i] = sf::Vertex(posg0, sf::Color(0x808080ff));
		grid[2 * i + 1] = sf::Vertex(posg1, sf::Color(0x808080ff));
	}
}

void Locator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(majores, states);
	//for (auto i = 0; i < majorCount; i++)
		//target.draw(majorLabels[i], states);
	target.draw(minores, states);

	if (gridEnabled)	
		target.draw(grid, states);
}
