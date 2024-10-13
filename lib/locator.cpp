#include "../include/locator.h"
#include "../include/axis.h"
#include "../include/plot.h"

Locator::Locator(Axis* layout, size_t majorCount, size_t minorCount) :
	layout		(layout),
	majorCount	(majorCount),
	minorCount	(minorCount),
	majores		(sf::Lines, 2 * (majorCount + 1)),
	minores		(sf::Lines, 2 * (minorCount + 1))
{
}

void Locator::setMajorCount(size_t count)
{
	majorCount = count;
	majores.resize(2 * (count + 1));
	recompute();
}

void Locator::setMinorCount(size_t count)
{
	minorCount = count;
	minores.resize(2 * (count + 1));
	recomputeMinores();
}

void Locator::recompute()
{
	recomputeMajores();
	recomputeMinores();
}

void Locator::recomputeMajores()
{
	auto alength = layout->length;
	auto offset = layout->layout->frame.getSize().y;
	auto mstep = alength / majorCount;
	for (auto i = 0; i <= majorCount; i++)
	{
		auto mpositions = i * mstep;
		majores[2 * i] = sf::Vertex(sf::Vector2f(mpositions, 0), sf::Color::Black);
		majores[2 * i + 1] = sf::Vertex(sf::Vector2f(mpositions, -DEFAULT_LOCATOR_MAJOR_LENGHT), sf::Color::Black);
	}
}

void Locator::recomputeMinores()
{
	auto alength = layout->length;
	auto mlength = alength / majorCount;
	auto mstep = mlength / minorCount;
	for (auto i = 0; i <= majorCount; i++)
	{
		auto mpositions = i * mstep;
		minores[2 * i] = sf::Vertex(sf::Vector2f(mpositions, 0.f), sf::Color::Black);
		minores[2 * i + 1] = sf::Vertex(sf::Vector2f(mpositions, DEFAULT_LOCATOR_MINOR_LENGHT), sf::Color::Black);
	}
}

void Locator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(majores, states);
	//target.draw(minores, states);
}
