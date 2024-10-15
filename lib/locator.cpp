#include "../include/plot/locator.h"
#include "../include/plotter.h"

Locator::Locator(Orientation orientation, size_t majorCount, size_t minorCount) :
	gridEnable	(false),
	majorCount	(majorCount),
	minorCount	(minorCount),
	majorLabels	(2 * majorCount, Label()),
	majores		(sf::Lines, 2 * majorCount),
	minorLabels	(2 * majorCount * minorCount, Label()),
	minores		(sf::Lines, 2 * (majorCount - 1) * minorCount)
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

void Locator::recomputeMajores()
{
	majores.resize(2 * majorCount);
	majorLabels.resize(majorCount, Label());

	auto step = 1.f / (majorCount - 1);
	auto mlength = -0.04f;
	for (auto i = 0; i < majorCount; i++)
	{
		auto mposition = sf::Vector2f(0, 0);
		orientation == HORIZONTAL ? mposition.x = step * i : mposition.y = step * i;
		orientation == HORIZONTAL ? mposition.y = 0 : mposition.x = 0;
		majores[2 * i] = sf::Vertex(mposition, sf::Color::Black);
		orientation == HORIZONTAL ? mposition.y = mlength : mposition.x = mlength;
		majores[2 * i + 1] = sf::Vertex(mposition, sf::Color::Black);
	}
}

void Locator::recomputeMinores()
{
	auto m = majorCount - 1;
	auto n = minorCount;
	minores.resize(2 * m * n);
	minorLabels.resize(m * n, Label());

	auto step = 1.f / (m * (n + 1));
	for (auto i = 0; i < m; i++)
	{
		for (auto j = 0; j < n; j++)
		{
			auto index = 2 * (n * i + j);
			auto next = 2 * (n * i + j) + 1;
			auto mposition = majores[2 * i].position.x + step * (j + 1);
			minores[index] = sf::Vertex(sf::Vector2f(mposition, 0), sf::Color::Black);
			minores[next] = sf::Vertex(sf::Vector2f(mposition, -0.02f), sf::Color::Black);
		}
	}
}

void Locator::recompute()
{
	recomputeMajores();
	recomputeMinores();
}

void Locator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(majores, states);
	//for (auto i = 0; i < majorCount; i++)
		//target.draw(majorLabels[i], states);
	target.draw(minores, states);
}
