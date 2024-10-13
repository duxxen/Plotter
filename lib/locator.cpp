#include "../include/locator.h"
#include "../include/axis.h"
#include "../include/plot.h"

Locator::Locator(Axis* layout, size_t majorCount, size_t minorCount) :
	layout		(layout),
	majorCount	(majorCount),
	minorCount	(minorCount),
	majores		(sf::Lines, 2 * (majorCount + 1)),
	minores		(sf::Lines, 2 * (majorCount * minorCount + 1)),
	majorLabels	( majorCount + 1, sf::Text("", DEFAULT_FONT, 16U)),
	minorLabels	( majorCount * minorCount + 1, sf::Text("", DEFAULT_FONT, 8U))
{
	for (auto& label : majorLabels)
		label.setFillColor(sf::Color::Black);
	for (auto& label : minorLabels)
		label.setFillColor(sf::Color::Black);
}

void Locator::setMajorCount(size_t count)
{
	majorCount = count;
	majores.resize(2 * (count + 1));
	majorLabels.resize(count + 1);
	recompute();
}

void Locator::setMinorCount(size_t count)
{
	minorCount = count;
	minores.resize(2 * (majorCount * count + 1));
	minorLabels.resize(majorCount * count + 1);
	recomputeMinores();
}

void Locator::recompute()
{
	recomputeMajores();
	recomputeMinores();
}

void Locator::recomputeMajores()
{
	auto pptr = layout->layout;
	auto alength = layout->length;
	auto mstep = alength / majorCount;
	for (auto i = 0; i <= majorCount; i++)
	{
		auto mposition = i * mstep;
		majores[2 * i] = sf::Vertex(sf::Vector2f(mposition, 0), sf::Color::Black);
		majores[2 * i + 1] = sf::Vertex(sf::Vector2f(mposition, -DEFAULT_LOCATOR_MAJOR_LENGHT), sf::Color::Black);
	
		majorLabels[i].setString(std::to_string(layout->horizontal ? pptr->toValuesX(mposition) : pptr->toValuesY(mposition)));
		majorLabels[i].setPosition(mposition, DEFAULT_LOCATOR_MAJOR_LENGHT);
	}
}

void Locator::recomputeMinores()
{
	auto alength = layout->length;
	auto mlength = alength / majorCount;
	auto mstep = mlength / minorCount;
	for (auto i = 0; i <= minorCount * majorCount; i++)
	{
		auto mposition = i * mstep;
		minores[2 * i] = sf::Vertex(sf::Vector2f(mposition, 0.f), sf::Color::Black);
		minores[2 * i + 1] = sf::Vertex(sf::Vector2f(mposition, -DEFAULT_LOCATOR_MINOR_LENGHT), sf::Color::Black);
	}
}

void Locator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(majores, states);
	for (auto& label : majorLabels)
		target.draw(label, states);
	target.draw(minores, states);
}
