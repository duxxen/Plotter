#include "../include/plot/locator.h"
#include "../include/plot/axis.h"
#include "../include/plot/plot.h"
#include "../include/plotter.h"

Locator::Locator(Axis* layout, size_t majorCount, size_t minorCount) :
	PlotObject	(layout),
	gridEnable	(false),
	majorCount	(majorCount),
	minorCount	(minorCount),
	majorLabels	(2 * majorCount, Label()),
	majores		(sf::Lines, 2 * majorCount),
	minorLabels	(2 * majorCount * minorCount, Label()),
	minores		(sf::Lines, 2 * majorCount * minorCount)
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

	auto axis = static_cast<Axis*>(toLayout());
	auto plot = static_cast<Plot*>(axis->toLayout());
	auto step = axis->getLength() / (majorCount - 1);
	for (auto i = 0; i < majorCount; i++)
	{
		auto mposition = step * i;
		majores[2 * i] = sf::Vertex(sf::Vector2f(mposition, 0), sf::Color::Black);
		majores[2 * i + 1] = sf::Vertex(sf::Vector2f(mposition, 8), sf::Color::Black);
		
		majorLabels[i].setString(axis->getOrientation() == Axis::HORIZONTAL ? plot->toValuesX(mposition) : plot->toValuesY(mposition));
		auto lposition = mposition - majorLabels[i].getLocalBounds().width;
		majorLabels[i].setPosition(lposition, 8);
	}
}

void Locator::recomputeMinores()
{
}

void Locator::recompute()
{
	recomputeMajores();
	recomputeMinores();
}

void Locator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(majores, states);
	for (auto i = 0; i < majorCount; i++)
		target.draw(majorLabels[i], states);
	//target.draw(minores, states);
}
