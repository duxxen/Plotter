#include "../include/plot.h"
#include "../include/window-frame.h"

Plot::Plot(WindowFrame* layout) :
	layout(layout),
	axis(this)
{
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineColor(sf::Color::Black);
	frame.setOutlineThickness(-1.f);

	adjust(.125, .12, .9, .9);
	axis.recompute();
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

	setPosition(fposition);
	frame.setSize(fsize);
}

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(frame, states);
	target.draw(axis, states);
}
