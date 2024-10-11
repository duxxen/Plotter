#include "../include/plot.h"
#include "../include/window-frame.h"

Plot::Plot(WindowFrame* layout) :
	layout(layout),
	axis(this)
{
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Black);
	frame.setOutlineThickness(1.f);

	adjust(.125, .12, .9, .9);
}

void Plot::adjust(float aleft, float atop, float aright, float abottom)
{
	auto size = layout->size * layout->dpi;
	auto fposition = sf::Vector2f(
		aleft * size.x,
		atop * size.y
	);
	auto fsize = sf::Vector2f(
		aright * size.x - fposition.x,
		abottom * size.y - fposition.y
	);
	valuesScale = sf::Vector2f(
		(valuesEnd.x - valuesStart.x) / fsize.x,
		-(valuesEnd.y - valuesStart.y) / fsize.y
	);

	setPosition(fposition);
	frame.setSize(fsize);
	axis.recompute();
}

float Plot::toCoordsX(float vx) const
{
	return 0.0f;
}

float Plot::toCoordsY(float vx) const
{
	return 0.0f;
}

float Plot::toValuesX(float cx) const
{
	return 0.0f;
}

float Plot::toValuesY(float cx) const
{
	return 0.0f;
}

sf::Vector2f Plot::toCoords(sf::Vector2f values) const
{
	return sf::Vector2f();
}

sf::Vector2f Plot::toValues(sf::Vector2f coords) const
{
	return sf::Vector2f();
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(frame, states);
	target.draw(axis, states);
}
